/***************************************************************************
 *   Nipper - The network infrastructure parser                            *
 *   Copyright (C) 2006 - 2008 by Ian Ventura-Whiting                      *
 *   fizz@titania.co.uk                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version. However, there are a number of    *
 *   exceptions listed below.                                              *
 *                                                                         *
 *   EXCEPTIONS TO THE GPL License:                                        *
 *      1. This code cannot be used as part of a commercial product. If a  *
 *         commercial license is required, contact fizz@titania.co.uk for  *
 *         licensing information.                                          *
 *      2. Any code that integrates Nipper MUST display the copyright      *
 *         information below with the programs own copyright information.  *
 *                                                                         *
 *         "Nipper Copyright (C) 2006 - 2008 by Ian Ventura-Whiting"       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/

// This file contains the code that handles the input processing for this config type


struct firewall1Config
{
	struct policyCollection *policies;				// Policy Collections...

	// Service Counts
	int serviceCount;
	int serviceGroupCount;

	// Object Counts
	int groupObjectCount;
	int gatewayObjectCount;
	int gatewayClusterObjectCount;
	int clusterMemberObjectCount;
	int networkObjectCount;
	int dynamicNetObjectCount;
	int machinesRangeObjectCount;
	int hostObjectCount;
};


// FW1 Unhandled Processing (Recursive...)
void processFW1Unknown(struct nipperConfig *nipper, char *line)
{
	// Variables...
	struct ciscoCommand command;

	// Split the command line up
	command = splitLine(line);

	// If it is a section end...
	if (strcmp(command.part[0], ")") == 0)
	{}

	// If item with no data...
	else if (strcmp(command.part[1], "()") == 0)
	{}

	// If item that has a little data...
	else if ((command.part[1][0] == '(') && (command.part[command.parts - 1][strlen(command.part[command.parts - 1]) - 1] == ')'))
	{}

	// If item has a lot more data...
	else if (command.part[1][0] == '(')
	{
		while ((feof(nipper->input) == 0) && (strcmp(command.part[0], ")") != 0))
		{
			// Read line
			memset(line, 0, LINE_SIZE + 1);
			readLine(nipper->input, line, LINE_SIZE);

			// Debug (lines not processed)
			if (nipper->linesnotprocessed == true)
				printf("%s\n", line);

			// Init...
			command = splitLine(line);

			processFW1Unknown(nipper, line);
		}
	}
}


// Processing Firewall-1 includes...
#include "process-objects.c"
#include "process-policycollections.c"
#include "process-rules.c"
#include "process-rulebases.c"
#include "process-services.c"


// Process FW1 Input (Excluding Rules)
void processFW1Input(struct nipperConfig *nipper, char *line)
{
	// Variables...
	struct ciscoCommand command;

	// Split the command line up
	command = splitLine(line);

	// Process objects...
	if (((strcmp(command.part[0], ":netobj") == 0) || (strcmp(command.part[0], ":network_objects") == 0)) && (strcmp(command.part[1], "()") != 0))
		processFW1Objects(line, nipper);

	// Process Services...
	else if (((strcmp(command.part[0], ":servobj") == 0) || (strcmp(command.part[0], ":services") == 0)) && (strcmp(command.part[1], "()") != 0))
		processFW1Services(line, nipper);

	// Process Policy Collections...
	else if ((strcmp(command.part[0], ":policies_collections") == 0) && (strcmp(command.part[1], "()") != 0))
		processFW1PolicyCollections(line, nipper);

	// Debug (lines not processed)
	else if (nipper->linesnotprocessed == true)
		printf("%s\n", line);
}


// Process FW1 Rules...
void processFW1RulesInput(struct nipperConfig *nipper, char *line)
{
	// Variables...
	struct ciscoCommand command;
	struct filterListConfig *filterListPointer = 0;

	// Init...
	filterListPointer = getFilterList(nipper, "Firewall-1", "", false);

	// Split the command line up
	command = splitLine(line);

	// Process lines
	while (feof(nipper->input) == 0)
	{
		// Read line
		memset(line, 0, LINE_SIZE + 1);
		readLine(nipper->input, line, LINE_SIZE);

		// Init...
		command = splitLine(line);

		// Process Rules...
		if ((strcmp(command.part[0], ":rules") == 0) && (strcmp(command.part[1], "()") != 0) && (filterListPointer != 0))
		{
			while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0))
			{
				// Read line
				memset(line, 0, LINE_SIZE + 1);
				readLine(nipper->input, line, LINE_SIZE);
		
				// Init...
				command = splitLine(line);

				if ((strcmp(command.part[0], ":") == 0) && (strcmp(command.part[1], "()") != 0))
					processFW1Rule(line, nipper, filterListPointer);
			}
		}
	}
}


// Process FW1 Rules...
void processFW1RuleInput(struct nipperConfig *nipper, char *line)
{
	// Variables...
	struct ciscoCommand command;
	struct filterListConfig *filterListPointer = 0;

	// Split the command line up
	command = splitLine(line);

	// Process lines
	while (feof(nipper->input) == 0)
	{
		// Read line
		memset(line, 0, LINE_SIZE + 1);
		readLine(nipper->input, line, LINE_SIZE);

		// Init...
		command = splitLine(line);

		// Debug output
		if (nipper->debugMode == true)
			printf("Policy Collection Line: %s\n", line);

		// Process Rules...
		if ((strcmp(command.part[0], ":rule") == 0) && (strcmp(command.part[1], "()") != 0) && (filterListPointer != 0))
			processFW1Rule(line, nipper, filterListPointer);
	
		else if ((strcmp(command.part[0], ":collection") == 0) && (strcmp(command.part[1], "()") != 0))
			filterListPointer = processFW1RuleCollection(line, nipper);

		else if ((strcmp(command.part[0], ":rule-base") == 0) && (strncmp(command.part[1], "(\"##", 4) == 0))
			processFW1Rulebase(line, nipper);
	}
}



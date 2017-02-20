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


void processFW1Rulebase(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct filterListConfig *filterListPointer = 0;
	struct filterConfig *filterPointer = 0;
	struct ciscoCommand command;
	char tempString[nipper->maxSize];
	int tempInt = false;

	// Init...
	command = splitLine(line);

	// Get Filter List Pointer...
	command.part[1][strlen(command.part[1]) - 1] = 0;
	filterListPointer = getFilterList(nipper, command.part[1] + 4, "", false);

	// Does the list already exist?
	if (filterListPointer->filter != 0)
	{
		filterPointer = filterListPointer->filter;

		// Process lines
		while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0) && (filterPointer != 0))
		{
			// Read line
			memset(line, 0, LINE_SIZE + 1);
			readLine(nipper->input, line, LINE_SIZE);
	
			// Init...
			command = splitLine(line);
	
			// Debug output
			if (nipper->debugMode == true)
				printf("Rulebase Line: %s\n", line);

			// Process Rules...
			if ((strcmp(command.part[0], ":rule") == 0) && (strcmp(command.part[1], "()") != 0))
			{
				while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0) && (filterPointer != 0))
				{
					// Read line
					memset(line, 0, LINE_SIZE + 1);
					readLine(nipper->input, line, LINE_SIZE);
			
					// Init...
					command = splitLine(line);
			
					// Debug output
					if (nipper->debugMode == true)
						printf("Rulebase Line: %s\n", line);

					// Comments...
					if ((strcasecmp(command.part[0], ":comments") == 0) && (strcasecmp(command.part[1], "()") != 0))
					{
						command.part[1][strlen(command.part[1]) - 1] = 0;
						stripQuotes(command.part[1] + 1, filterPointer->remark, sizeof(filterPointer->remark) -1);
					}

					// Header Text...
					else if ((strcasecmp(command.part[0], ":header_text") == 0) && (strcasecmp(command.part[1], "()") != 0))
					{
						command.part[1][strlen(command.part[1]) - 1] = 0;
						stripQuotes(command.part[1] + 1, tempString, sizeof(tempString) -1);
						insertFilterRemark(filterListPointer, filterPointer, true, tempString);
						tempInt = true;
					}

					// Process Unknown...
					else
						processFW1Unknown(nipper, line);
				}
				command.part[0][0] = 0;
				if (tempInt == false)
					filterPointer = filterPointer->next;
				else
					tempInt = false;
			}

			// Process Unknown...
			else
				processFW1Unknown(nipper, line);
		}
		command.part[0][0] = 0;
	}

	// List already exists...
	else
	{

		// Process lines
		while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0))
		{
			// Read line
			memset(line, 0, LINE_SIZE + 1);
			readLine(nipper->input, line, LINE_SIZE);
	
			// Init...
			command = splitLine(line);
	
			// Debug output
			if (nipper->debugMode == true)
				printf("Rulebase Line: %s\n", line);

			// Process Rules...
			if ((strcmp(command.part[0], ":rule") == 0) && (strcmp(command.part[1], "()") != 0))
				processFW1Rule(line, nipper, filterListPointer);

			// Process Unknown...
			else
				processFW1Unknown(nipper, line);
		}
	}
}


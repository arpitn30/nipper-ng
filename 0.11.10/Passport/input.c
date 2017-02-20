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


struct passportConfig
{
	char boxType[16];
	char monitorVersion[16];
	struct passportFilter *filter;
	struct passportFilterSet *filterSet;
};


// Processing Nortel Passport includes...
#include "process-filters.c"
#include "process-general.c"


void processPASInput(struct nipperConfig *nipper, char *line)
{
	// Variables...
	struct ciscoCommand command;

	// Split the command line up
	command = splitLine(line);

	// Software Version
	if ((strcmp(command.part[0], "#") == 0) && (strcmp(command.part[1], "software") == 0) && (strcmp(command.part[2], "version") == 0) && (strcmp(command.part[3], ":") == 0))
		processSoftwarePAS(line, nipper);

	// Box Type
	else if ((strcmp(command.part[0], "#") == 0) && (strcmp(command.part[1], "box") == 0) && (strcmp(command.part[2], "type") == 0) && (strcmp(command.part[3], ":") == 0))
		processBoxTypePAS(line, nipper);

	// Monitor Version
	else if ((strcmp(command.part[0], "#") == 0) && (strcmp(command.part[1], "monitor") == 0) && (strcmp(command.part[2], "version") == 0) && (strcmp(command.part[3], ":") == 0))
		processMonitorPAS(line, nipper);

	// IP Commands...
	else if (strcmp(command.part[0], "ip") == 0)
	{

		// Traffic Filter Commands...
		if (strcmp(command.part[1], "traffic-filter") == 0)
		{

			// Create ...
			if (strcmp(command.part[2], "create") == 0)
				processCreateFilterPAS(line, nipper);

			// Filter ...
			else if (strcmp(command.part[2], "filter") == 0)
				processFilterPAS(line, nipper);

			// Filter Set...
			else if ((strcmp(command.part[2], "set") == 0) || (strcmp(command.part[2], "global-set") == 0))
				processFilterSetPAS(line, nipper);
		}
	}

	// Debug (lines not processed)
	else if (nipper->linesnotprocessed == true)
		printf("%s\n", line);
}

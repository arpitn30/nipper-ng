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


// CDP
void processNMPCDP(char *line, struct nipperConfig *nipper)
{
	// Variables
	int offset = 0;
	int offsetStart = 0;
	int range = 0;
	int module = 0;
	int port = 0;
	int tempInt = 0;
	struct portConfig *portNMPPointer = 0;
	struct ciscoCommand command;

	// Debug output
	if (nipper->debugMode == true)
		printf("CDP Line: %s\n", line);

	// Init
	offset = 0;
	command = splitLine(line);


	// Global Enable / Disable
	if (((strcmp(command.part[2], "enable") == 0) || (strcmp(command.part[2], "disable") == 0)) && (command.parts == 3))
	{
		if (strcmp(command.part[2], "enable") == 0)
			nipper->nmp->cdp = true;
		else
			nipper->nmp->cdp = false;
	}

	// Interval
	else if (strcmp(command.part[2], "interval") == 0)
		nipper->nmp->cdpInterval = atoi(command.part[3]);

	// Holdtime
	else if (strcmp(command.part[2], "holdtime") == 0)
		nipper->nmp->cdpHoldtime = atoi(command.part[3]);

	// Version
	else if (strcmp(command.part[2], "version") == 0)
	{
		if (strcmp(command.part[3], "v1") == 0)
			nipper->nmp->cdpVersion = 1;
		else
			nipper->nmp->cdpVersion = 2;
	}

	// Individual Port Enable / Disable
	else if (((strcmp(command.part[2], "enable") == 0) || (strcmp(command.part[2], "disable") == 0)) && (command.parts == 4))
	{
		if (strcmp(command.part[2], "enable") == 0)
			tempInt = true;
		else
			tempInt = false;

		while (command.part[3][offset] != 0)
		{
			// Get Module number
			offsetStart = offset;
			while ((command.part[3][offset] != 0) && (command.part[3][offset] != '/'))
				offset++;
			command.part[3][offset] = 0;
			module = atoi(command.part[3] + offsetStart);
			offset++;

			// Get Port number
			offsetStart = offset;
			while ((command.part[3][offset] != 0) && (command.part[3][offset] != '-') && (command.part[3][offset] != ','))
				offset++;
			if (command.part[3][offset] == '-')
				range = true;
			else
				range = false;
			command.part[3][offset] = 0;
			port = atoi(command.part[3] + offsetStart);

			// Create Port
			portNMPPointer = createNMPPort(module, port, nipper->nmp);

			// Set CDP
			portNMPPointer->cdp = tempInt;

			// If it is a range
			if (range == true)
			{
				// Set End Port
				offset++;
				offsetStart = offset;
				while ((command.part[3][offset] != 0) && (command.part[3][offset] != ','))
					offset++;
				command.part[3][offset] = 0;

				// Add each port in range
				while (port < atoi(command.part[3] + offsetStart))
				{
					port++;
					portNMPPointer = createNMPPort(module, port, nipper->nmp);

					// Set CDP
					portNMPPointer->cdp = tempInt;
				}
			}

			// Move offset
			offset++;
		}
	}
}

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


struct routePIX
{
	char interface[32];
	char ipAddress[64];
	char netMask[16];
	char gateway[64];
	int metric;
	int track;
	int tunneled;
	struct routePIX *next;
};


// Process enable
void processRoutePIX(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct ciscoCommand command;
	struct routePIX *routePIXPointer = 0;
	int tempInt = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Route Line: %s\n", line);
	}

	// Is this the first?
	if (nipper->pix->route == 0)
	{
		nipper->pix->route = malloc(sizeof(struct routePIX));
		routePIXPointer = nipper->pix->route;
	}
	else
	{
		routePIXPointer = nipper->pix->route;
		while (routePIXPointer->next != 0)
			routePIXPointer = routePIXPointer->next;
		routePIXPointer->next = malloc(sizeof(struct routePIX));
		routePIXPointer = routePIXPointer->next;
	}

	// Init Structure
	command = splitLine(line);
	memset(routePIXPointer, 0, sizeof(struct routePIX));
	routePIXPointer->metric = 1;
	routePIXPointer->track = 0;
	routePIXPointer->tunneled = false;

	// Interface Name
	strncpy(routePIXPointer->interface, command.part[1], sizeof(routePIXPointer->interface) - 1);

	// IP Address
	strncpy(routePIXPointer->ipAddress, command.part[2], sizeof(routePIXPointer->ipAddress) - 1);

	// Net Mask
	strncpy(routePIXPointer->netMask, command.part[3], sizeof(routePIXPointer->netMask) - 1);

	// Gateway
	strncpy(routePIXPointer->gateway, command.part[4], sizeof(routePIXPointer->gateway) - 1);

	// Options
	if (command.parts > 5)
	{
		
		// Tunneled
		if (strcmp(command.part[5], "tunneled") == 0)
			routePIXPointer->tunneled = true;

		// Metric / Track
		else
		{
			tempInt = 5;

			// Metric
			if (strcmp(command.part[tempInt], "track") != 0)
			{
				routePIXPointer->metric = atoi(command.part[tempInt]);
				tempInt++;
			}

			// Track?
			if (strcmp(command.part[tempInt], "track") == 0)
				routePIXPointer->track = atoi(command.part[tempInt + 1]);
		}
	}
}

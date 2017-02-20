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


// Route Map
struct routeMapConfig
{
	char mapTag[64];
	int sequenceNo;
	int permission;						// perm_allow (default) or perm_deny
	struct routeMapConfig *next;
};


// Process Route Map
void processRouteMap(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct routeMapConfig *routeMapPointer = 0;
	fpos_t filePosition;
	int tempInt = 0;
	struct ciscoCommand command;

	while ((line[0] != '!') && (feof(nipper->input) == 0))
	{
		// Debug
		if (nipper->debugMode == true)
		{
			printf("Route Map Line: %s\n", line);
		}

		// Init
		command = splitLine(line);

		// If it is a new route map
		if (strcmp(command.part[0], "route-map") == 0)
		{
			// If this is the first route map...
			if (nipper->ios->routeMap == 0)
			{
				nipper->ios->routeMap = malloc(sizeof(struct routeMapConfig));
				routeMapPointer = nipper->ios->routeMap;
			}

			// Else find last route map...
			else
			{
				routeMapPointer = nipper->ios->routeMap;
				while (routeMapPointer->next != 0)
					routeMapPointer = routeMapPointer->next;
				routeMapPointer->next = malloc(sizeof(struct routeMapConfig));
				routeMapPointer = routeMapPointer->next;
			}

			// Init the new line structure
			memset(routeMapPointer, 0, sizeof(struct routeMapConfig));

			// Set the new route map to the default settings
			routeMapPointer->permission = perm_permit;

			// Set map tag...
			strncpy(routeMapPointer->mapTag, command.part[1], sizeof(routeMapPointer->mapTag) - 1);

			// Set optional parameters
			for (tempInt = 2; tempInt < command.parts; tempInt++)
			{
				// Permit
				if (strcmp(command.part[tempInt], "permit") == 0)
					routeMapPointer->permission = perm_permit;

				// Deny
				else if (strcmp(command.part[tempInt], "deny") == 0)
					routeMapPointer->permission = perm_deny;

				// Sequence no
				else
					routeMapPointer->sequenceNo = atoi(command.part[tempInt]);
			}
		}

		// Debug (route map lines not processed)
		else if (nipper->linesnotprocessed == true)
			printf("%s\n", line);

		// Get next line...
		fgetpos(nipper->input, &filePosition);
		readLine(nipper->input, line, nipper->maxSize);
	}

	// Set to previous position...
	fsetpos(nipper->input, &filePosition);
}



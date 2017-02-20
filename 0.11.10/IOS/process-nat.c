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

#define nat_static 0
#define nat_dynamic_acl 1
#define nat_dynamic_route 2
#define nat_port 3
#define nat_network 4

// NAT
struct natConfig
{
	int inside;						// true or false - if false then it is outside)
	int type;						// nat_static
	char local[64];					// local
	int localPort;
	char global[64];				// global
	int globalPort;
	char mask[16];					// Mask
	int interNumber;				// global number / interface number
	int pool;						// true or false (default)
	int ipSecESP;					// true or false (default)
	int routeMap;					// true or false (default)
	int tcp;						// true (default) or false
	int inter;						// true or false (default)
	struct natConfig *next;
};


// Process NAT
void processNAT(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct natConfig *natPointer = 0;
	struct ciscoCommand command;
	int tempInt = 0;

	// Init
	command = splitLine(line);

	// if it is a source or nat line
	if (((strcmp(command.part[2], "inside") == 0) || (strcmp(command.part[2], "outside") == 0)) && (command.parts > 3) && (strcmp(command.part[3], "source") == 0))
	{
		// Debug
		if (nipper->debugMode == true)
		{
			printf("NAT inside/outside source Line: %s\n", line);
		}

		// Is this the first nat line?
		if (nipper->ios->nat == 0)
		{
			nipper->ios->nat = malloc(sizeof(struct natConfig));
			natPointer = nipper->ios->nat;
		}

		// Else find last line...
		else
		{
			natPointer = nipper->ios->nat;
			while (natPointer->next != 0)
				natPointer = natPointer->next;
			natPointer->next = malloc(sizeof(struct natConfig));
			natPointer = natPointer->next;
		}

		// Init the new line structure
		memset(natPointer, 0, sizeof(struct natConfig));

		// Defaults...
		natPointer->ipSecESP = false;
		natPointer->routeMap = false;
		natPointer->pool = false;
		natPointer->tcp = true;
		natPointer->inter = false;

		// Set inside / outside
		if (strcmp(command.part[2], "inside") == 0)
			natPointer->inside = true;
		else
			natPointer->inside = false;

		// Set type
		if ((strcmp(command.part[4], "static") == 0) && (strcmp(command.part[5], "network") == 0))
			natPointer->type = nat_network;
		else if ((strcmp(command.part[4], "static") == 0) && ((strcmp(command.part[5], "tcp") == 0) || (strcmp(command.part[5], "udp") == 0)))
			natPointer->type = nat_port;
		else if (strcmp(command.part[4], "list") == 0)
			natPointer->type = nat_dynamic_acl;
		else if (strcmp(command.part[4], "route-map") == 0)
			natPointer->type = nat_dynamic_route;
		else if (strcmp(command.part[4], "static") == 0)
			natPointer->type = nat_static;

		// Process the different nat types...
		switch (natPointer->type)
		{
			// Static NAT
			case nat_static:
				if (strcmp(command.part[5], "esp") == 0)
				{
					natPointer->ipSecESP = true;
					strncpy(natPointer->local, command.part[6], sizeof(natPointer->local) - 1);
					strncpy(natPointer->global, command.part[8], sizeof(natPointer->global) - 1);
					natPointer->interNumber = atoi(command.part[9]);
					tempInt = 10;
				}
				else
				{
					strncpy(natPointer->local, command.part[5], sizeof(natPointer->local) - 1);
					strncpy(natPointer->global, command.part[6], sizeof(natPointer->global) - 1);
					tempInt = 7;
				}
				break;

			// Dynamic NAT (ACL / Route Map)
			case nat_dynamic_route:
			case nat_dynamic_acl:
				strncpy(natPointer->local, command.part[5], sizeof(natPointer->local) - 1);
				if (strcmp(command.part[6], "pool") == 0)
				{
					natPointer->pool = true;
					strncpy(natPointer->global, command.part[7], sizeof(natPointer->global) - 1);
				}
				else
				{
					strncpy(natPointer->global, command.part[7], sizeof(natPointer->global) - 1);
					natPointer->interNumber = atoi(command.part[8]);
				}
				break;

			// Port Static NAT
			case nat_port:
				if (strcmp(command.part[5], "tcp") == 0)
					natPointer->tcp = true;
				else
					natPointer->tcp = false;
				if (strcmp(command.part[6], "interface") == 0)
				{
					natPointer->inter = true;
					natPointer->globalPort = atoi(command.part[7]);
				}
				else
				{
					strncpy(natPointer->local, command.part[6], sizeof(natPointer->local) - 1);
					natPointer->localPort = atoi(command.part[7]);
					strncpy(natPointer->global, command.part[8], sizeof(natPointer->global) - 1);
					natPointer->globalPort = atoi(command.part[9]);
				}
				break;

			// Network NAT
			case nat_network:
				strncpy(natPointer->local, command.part[6], sizeof(natPointer->local) - 1);
				strncpy(natPointer->global, command.part[7], sizeof(natPointer->global) - 1);
				strncpy(natPointer->mask, command.part[8], sizeof(natPointer->mask) - 1);
				break;
		}
	}

	// Debug (lines not processed)
	else if (nipper->linesnotprocessed == true)
		printf("%s\n", line);
}



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

struct vlanConfig
{
	int vlan;
	char name[32];
	char type[16];
	int active;
	int firewall;
	int mtu;
	int spanTreeMaxHops;
	int allRoutesMaxHops;
	int said;
	struct vlanConfig *next;
};


void initNMPVLAN(struct vlanConfig *vlanNMPPointer)
{
	vlanNMPPointer->active = true;
	strcpy(vlanNMPPointer->type, "ethernet");
	vlanNMPPointer->firewall = -1;
	vlanNMPPointer->mtu = 1500;
	vlanNMPPointer->spanTreeMaxHops = 7;
	vlanNMPPointer->allRoutesMaxHops = 7;
	vlanNMPPointer->said = vlanNMPPointer->vlan + 100000;
}


// VLAN
void processNMPVlan(char *line, struct nipperConfig *nipper)
{
	// Variables
	int vlan = 0;
	int tempInt = 0;
	int offset = 0;
	int offsetStart = 0;
	int module = 0;
	int port = 0;
	int range = 0;
	struct vlanConfig *vlanNMPPointer = 0;
	struct vlanConfig *vlanNMPPreviousPointer = 0;
	struct portConfig *portNMPPointer = 0;
	struct ciscoCommand command;

	// Debug output
	if (nipper->debugMode == true)
		printf("VLAN Line: %s\n", line);

	// Init
	command = splitLine(line);

	// Set VLAN
	vlan = atoi(command.part[2]);

	// Now for the VLAN options

	// If it is not vlan ports
	if ((command.parts != 4) || (strcmp(command.part[3], "rspan") == 0))
	{

		// Is this the first VLAN
		if (nipper->nmp->vlan == 0)
		{
			// Create
			vlanNMPPointer = malloc(sizeof(struct vlanConfig));
			memset(vlanNMPPointer, 0 , sizeof(struct vlanConfig));
			// Set Pointer
			nipper->nmp->vlan = vlanNMPPointer;
			//init
			initNMPVLAN(vlanNMPPointer);
		}
		else
		{
			// Search for VLAN
			vlanNMPPointer = nipper->nmp->vlan;
			vlanNMPPreviousPointer = 0;
			while ((vlanNMPPointer->next != 0) && (vlanNMPPointer->vlan < vlan))
			{
				vlanNMPPreviousPointer = vlanNMPPointer;
				vlanNMPPointer = vlanNMPPointer->next;
			}

			// If it comes before
			if (vlanNMPPointer->vlan > vlan)
			{
				// If there is no previous
				if (vlanNMPPreviousPointer == 0)
				{
					// Create
					nipper->nmp->vlan = malloc(sizeof(struct vlanConfig));
					memset(nipper->nmp->vlan, 0 , sizeof(struct vlanConfig));
					// Pointers
					nipper->nmp->vlan->next = vlanNMPPointer;
					vlanNMPPointer = nipper->nmp->vlan;
					//init
					initNMPVLAN(vlanNMPPointer);
				}
				else
				{
					// Create
					vlanNMPPreviousPointer->next = malloc(sizeof(struct vlanConfig));
					memset(vlanNMPPreviousPointer->next, 0 , sizeof(struct vlanConfig));
					// Pointers
					vlanNMPPreviousPointer = vlanNMPPreviousPointer->next;
					vlanNMPPreviousPointer->next = vlanNMPPointer;
					vlanNMPPointer = vlanNMPPreviousPointer;
					//init
					initNMPVLAN(vlanNMPPointer);
				}
			}
			// It is greater
			else if (vlanNMPPointer->vlan < vlan)
			{
				// Create
				vlanNMPPointer->next = malloc(sizeof(struct vlanConfig));
				memset(vlanNMPPointer->next, 0 , sizeof(struct vlanConfig));
				// Pointers
				vlanNMPPointer = vlanNMPPointer->next;
				//init
				initNMPVLAN(vlanNMPPointer);
			}
		}

		// Set VLAN number
		vlanNMPPointer->vlan = vlan;

		// Loop through options
		tempInt = 3;
		while (tempInt < command.parts)
		{

			// Name
			if (strcmp(command.part[tempInt], "name") == 0)
			{
				tempInt++;
				strncpy(vlanNMPPointer->name, command.part[tempInt], sizeof(vlanNMPPointer->name) - 1);
			}

			// Type
			else if (strcmp(command.part[tempInt], "type") == 0)
			{
				tempInt++;
				strncpy(vlanNMPPointer->type, command.part[tempInt], sizeof(vlanNMPPointer->type) - 1);
			}

			// State
			else if (strcmp(command.part[tempInt], "state") == 0)
			{
				tempInt++;
				if (strcmp(command.part[tempInt], "active") == 0)
					vlanNMPPointer->active = true;
				else
					vlanNMPPointer->active = false;
			}

			// Firewall VLAN?
			else if (strcmp(command.part[tempInt], "firewall-vlan") == 0)
			{
				tempInt++;
				vlanNMPPointer->firewall = atoi(command.part[tempInt]);
			}

			// MTU
			else if (strcmp(command.part[tempInt], "mtu") == 0)
			{
				tempInt++;
				vlanNMPPointer->mtu = atoi(command.part[tempInt]);
			}

			// MTU
			else if (strcmp(command.part[tempInt], "said") == 0)
			{
				tempInt++;
				vlanNMPPointer->said = atoi(command.part[tempInt]);
			}

			// Spanning Tree Maximum Hops
			else if (strcmp(command.part[tempInt], "stemaxhop") == 0)
			{
				tempInt++;
				vlanNMPPointer->spanTreeMaxHops = atoi(command.part[tempInt]);
			}

			// Spanning Tree Maximum Hops
			else if (strcmp(command.part[tempInt], "aremaxhop") == 0)
			{
				tempInt++;
				vlanNMPPointer->allRoutesMaxHops = atoi(command.part[tempInt]);
			}

			// Increment loop
			tempInt++;
		}
	}

	// Set Port VLAN
	else
	{

		// Get VLAN
		tempInt = atoi(command.part[2]);

		offset = 0;
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

			// Set VLAN
			portNMPPointer->vlan = tempInt;

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

					// Set VLAN
					portNMPPointer->vlan = tempInt;
				}
			}

			// Move offset
			offset++;
		}

	}
}


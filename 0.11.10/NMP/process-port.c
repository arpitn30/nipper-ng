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

struct moduleConfig
{
	int module;
	char name[32];
	int portSecurity;
	struct portConfig *ports;
	struct moduleConfig *next;
};


#define port_speed_auto 0
#define port_speed_10 1
#define port_speed_100 2
#define port_speed_1000 3
#define port_speed_auto_10_100 4
#define port_duplex_auto 0
#define port_duplex_half 1
#define port_duplex_full 2
#define port_trunk_auto 0
#define port_trunk_nonegotiate 1
#define port_trunk_on 2
#define port_trunk_off 3
#define port_trunk_desirable 4
#define port_guard_none 0
#define port_guard_default 1
#define port_guard_loop 2
#define port_guard_root 3

struct portConfig
{
	int port;
	char name[32];
	int speed;
	int duplex;
	int vlan;
	int enabled;
	int spantreeGuard;
	int trunk;
	int vtp;
	int portSecurity;
	int cdp;
	struct portConfig *next;
};


// Init Port
void initNMPPort(struct portConfig *portNMPPointer)
{
	portNMPPointer->enabled = true;
	portNMPPointer->vlan = 1;
	portNMPPointer->speed = port_speed_auto;
	portNMPPointer->duplex = port_duplex_auto;
	portNMPPointer->trunk = port_trunk_auto;
	portNMPPointer->vtp = true;
	portNMPPointer->cdp = true;
	portNMPPointer->portSecurity = false;
	portNMPPointer->spantreeGuard = port_guard_none;
}


// Add port / module
struct portConfig *createNMPPort(int module, int port, struct ciscoNMPConfig *configNMP)
{
	// Variables
	struct moduleConfig *moduleNMPPointer = 0;
	struct moduleConfig *previousModuleNMPPointer = 0;
	struct portConfig *portNMPPointer = 0;
	struct portConfig *previousPortNMPPointer = 0;

	// If first module
	if (configNMP->module == 0)
	{
		// Create
		configNMP->module = malloc(sizeof(struct moduleConfig));
		memset(configNMP->module, 0 , sizeof(struct moduleConfig));
		// Pointers
		moduleNMPPointer = configNMP->module;
		// Init
		moduleNMPPointer->portSecurity = false;
	}
	else
	{
		// Search for module
		previousModuleNMPPointer = 0;
		moduleNMPPointer = configNMP->module;
		while ((moduleNMPPointer->module < module) && (moduleNMPPointer->next != 0))
		{
			previousModuleNMPPointer = moduleNMPPointer;
			moduleNMPPointer = moduleNMPPointer->next;
		}

		// If should be before
		if (moduleNMPPointer->module > module)
		{
			// If it should be first
			if (previousModuleNMPPointer == 0)
			{
				// Create
				configNMP->module = malloc(sizeof(struct moduleConfig));
				memset(configNMP->module, 0 , sizeof(struct moduleConfig));
				// Pointers
				configNMP->module->next = moduleNMPPointer;
				moduleNMPPointer = configNMP->module;
				// Init
				moduleNMPPointer->portSecurity = false;
			}
			else
			{
				// Create
				previousModuleNMPPointer->next = malloc(sizeof(struct moduleConfig));
				memset(previousModuleNMPPointer->next, 0 , sizeof(struct moduleConfig));
				// Pointers
				previousModuleNMPPointer->next->next = moduleNMPPointer;
				moduleNMPPointer = previousModuleNMPPointer->next;
				// Init
				moduleNMPPointer->portSecurity = false;
			}
		}
		// Should be after
		else if (moduleNMPPointer->module < module)
		{
			// Create
			moduleNMPPointer->next = malloc(sizeof(struct moduleConfig));
			memset(moduleNMPPointer->next, 0 , sizeof(struct moduleConfig));
			// Pointers
			moduleNMPPointer = moduleNMPPointer->next;
			// Init
			moduleNMPPointer->portSecurity = false;
		}
	}

	// Set module number
	moduleNMPPointer->module = module;

	// If first port
	if (moduleNMPPointer->ports == 0)
	{
		// Create
		moduleNMPPointer->ports = malloc(sizeof(struct portConfig));
		memset(moduleNMPPointer->ports, 0 , sizeof(struct portConfig));
		// Pointers
		portNMPPointer = moduleNMPPointer->ports;
		// Init
		initNMPPort(portNMPPointer);
	}
	else
	{
		// Search for port
		previousPortNMPPointer = 0;
		portNMPPointer = moduleNMPPointer->ports;
		while ((portNMPPointer->port < port) && (portNMPPointer->next != 0))
		{
			previousPortNMPPointer = portNMPPointer;
			portNMPPointer = portNMPPointer->next;
		}

		// If port should be before
		if (portNMPPointer->port > port)
		{
			// If it should be first
			if (previousPortNMPPointer == 0)
			{
				// Create
				moduleNMPPointer->ports = malloc(sizeof(struct portConfig));
				memset(moduleNMPPointer->ports, 0 , sizeof(struct portConfig));
				// Pointers
				moduleNMPPointer->ports->next = portNMPPointer;
				portNMPPointer = moduleNMPPointer->ports;
				// Init
				initNMPPort(portNMPPointer);
			}
			else
			{
				// Create
				previousPortNMPPointer->next = malloc(sizeof(struct portConfig));
				memset(previousPortNMPPointer->next, 0 , sizeof(struct portConfig));
				// Pointers
				previousPortNMPPointer->next->next = portNMPPointer;
				portNMPPointer = previousPortNMPPointer->next;
				// Init
				initNMPPort(portNMPPointer);
			}
		}
		// Should be after
		else if (portNMPPointer->port < port)
		{
			// Create
			portNMPPointer->next = malloc(sizeof(struct portConfig));
			memset(portNMPPointer->next, 0 , sizeof(struct portConfig));
			// Pointers
			portNMPPointer = portNMPPointer->next;
			// Init
			initNMPPort(portNMPPointer);
		}
	}

	// Set port number
	portNMPPointer->port = port;

	// Return port pointer
	return portNMPPointer;
}


// Ports
void processNMPPort(char *line, struct nipperConfig *nipper)
{
	// Variables
	int offset;
	int offsetStart;
	int range;
	int module;
	int port;
	int tempInt;
	struct portConfig *portNMPPointer;
	struct moduleConfig *moduleNMPPointer;
	struct ciscoCommand command;

	// Debug output
	if (nipper->debugMode == true)
		printf("Port Line: %s\n", line);

	// Init
	offset = 0;
	command = splitLine(line);

	// Name
	if (strcmp(command.part[2], "name") == 0)
	{
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

			// Set Name
			strncpy(portNMPPointer->name, command.part[4], sizeof(portNMPPointer->name) - 1);

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

					// Set Name
					strncpy(portNMPPointer->name, command.part[4], sizeof(portNMPPointer->name) - 1);
				}
			}

			// Move offset
			offset++;
		}
	}

	// Port Security Auto-Configure
	else if ((strcmp(command.part[2], "security") == 0) && (strcmp(command.part[3], "auto-configure") == 0))
	{
		if (strcmp(command.part[4], "enable") == 0)
			nipper->nmp->portSecurityAuto = true;
		else
			nipper->nmp->portSecurityAuto = false;
	}

	// Port Security
	else if ((strcmp(command.part[2], "security") == 0) && ((strcmp(command.part[4], "enable") == 0) || (strcmp(command.part[4], "disable") == 0)))
	{
		if (strcmp(command.part[4], "enable") == 0)
			tempInt = true;
		else
			tempInt = false;

		while (command.part[3][offset] != 0)
		{
			// Get Module number
			offsetStart = offset;
			while ((command.part[3][offset] != 0) && (command.part[3][offset] != '/') && (command.part[3][offset] != ','))
				offset++;
			if (command.part[3][offset] == '/')
				range = false;
			else
				range = true;
			command.part[3][offset] = 0;
			module = atoi(command.part[3] + offsetStart);
			offset++;

			// Module Port Security
			if (range == true)
			{
				if (nipper->nmp->module != 0)
				{
					moduleNMPPointer = nipper->nmp->module;
					while ((moduleNMPPointer != 0) && (moduleNMPPointer->module != module))
						moduleNMPPointer = moduleNMPPointer->next;
					if (moduleNMPPointer != 0)
						moduleNMPPointer->portSecurity = tempInt;
				}
			}

			else
			{
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

				// Set Port Security
				portNMPPointer->portSecurity = tempInt;

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

						// Set Port Security
						portNMPPointer->portSecurity = tempInt;
					}
				}
			}

			// Move offset
			offset++;
		}
	}

	// Enable / Disable
	else if ((strcmp(command.part[2], "enable") == 0) || ((strcmp(command.part[2], "disable") == 0)))
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

			// Set Enabled
			portNMPPointer->enabled = tempInt;

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

					// Set Enabled
					portNMPPointer->enabled = tempInt;
				}
			}

			// Move offset
			offset++;
		}
	}

	// VTP
	else if (strcmp(command.part[2], "vtp") == 0)
	{
		if (strcmp(command.part[4], "enable") == 0)
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

			// Set VTP
			portNMPPointer->vtp = tempInt;

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

					// Set VTP
					portNMPPointer->vtp = tempInt;
				}
			}

			// Move offset
			offset++;
		}
	}

	// Speed
	else if (strcmp(command.part[2], "speed") == 0)
	{
		// Set Speed
		if (strcmp(command.part[4], "10") == 0)
			tempInt = port_speed_10;
		else if (strcmp(command.part[4], "100") == 0)
			tempInt = port_speed_100;
		else if (strcmp(command.part[4], "1000") == 0)
			tempInt = port_speed_1000;
		else if (strcmp(command.part[4], "auto-10-100") == 0)
			tempInt = port_speed_auto_10_100;
		else
			tempInt = port_speed_auto;

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

			// Set Speed
			portNMPPointer->speed = tempInt;

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

					// Set Speed
					portNMPPointer->speed = tempInt;
				}
			}

			// Move offset
			offset++;
		}
	}

	// Duplex
	else if (strcmp(command.part[2], "duplex") == 0)
	{
		// Set Speed
		if (strcmp(command.part[4], "full") == 0)
			tempInt = port_duplex_full;
		else if (strcmp(command.part[4], "half") == 0)
			tempInt = port_duplex_half;
		else
			tempInt = port_duplex_auto;

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

			// Set Duplex
			portNMPPointer->duplex = tempInt;

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

					// Set Duplex
					portNMPPointer->duplex = tempInt;
				}
			}

			// Move offset
			offset++;
		}
	}
}


// Trunk
void processNMPTrunk(char *line, struct nipperConfig *nipper)
{
	// Variables
	int offset;
	int offsetStart;
	int range;
	int module;
	int port;
	int tempInt;
	struct portConfig *portNMPPointer;
	struct ciscoCommand command;

	// Debug output
	if (nipper->debugMode == true)
		printf("Trunk Line: %s\n", line);

	// Init
	offset = 0;
	command = splitLine(line);

	// Get Trunk mode
	if (strcmp(command.part[3], "nonegotiate") == 0)
		tempInt = port_trunk_nonegotiate;
	else if (strcmp(command.part[3], "on") == 0)
		tempInt = port_trunk_on;
	else if (strcmp(command.part[3], "off") == 0)
		tempInt = port_trunk_off;
	else if (strcmp(command.part[3], "desirable") == 0)
		tempInt = port_trunk_desirable;
	else
		tempInt = port_trunk_auto;

	// Get Port Pointer
	while (command.part[2][offset] != 0)
	{
		// Get Module number
		offsetStart = offset;
		while ((command.part[2][offset] != 0) && (command.part[2][offset] != '/'))
			offset++;
		command.part[2][offset] = 0;
		module = atoi(command.part[2] + offsetStart);
		offset++;

		// Get Port number
		offsetStart = offset;
		while ((command.part[2][offset] != 0) && (command.part[2][offset] != '-') && (command.part[2][offset] != ','))
			offset++;
		if (command.part[2][offset] == '-')
			range = true;
		else
			range = false;
		command.part[2][offset] = 0;
		port = atoi(command.part[2] + offsetStart);

		// Create Port
		portNMPPointer = createNMPPort(module, port, nipper->nmp);

		// Trunk
		portNMPPointer->trunk = tempInt;

		// If it is a range
		if (range == true)
		{
			// Set End Port
			offset++;
			offsetStart = offset;
			while ((command.part[2][offset] != 0) && (command.part[2][offset] != ','))
				offset++;
			command.part[2][offset] = 0;

			// Add each port in range
			while (port < atoi(command.part[2] + offsetStart))
			{
				port++;
				portNMPPointer = createNMPPort(module, port, nipper->nmp);

				// Trunk
				portNMPPointer->trunk = tempInt;
			}
		}

		// Move offset
		offset++;
	}
}


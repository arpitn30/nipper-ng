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

struct interfacePIXConfig
{
	// Standard...
	char interface[32];
	char name[32];
	char ipAddress[64];
	char netMask[32];

	// Options
	int security;
	int uRPF;
	int shutdown;			// true or false

	// Access Lists
	char in[32];
	int inOverride;			// true or false
	char out[32];
	int outOverride;		// true or false

	struct interfacePIXConfig *next;
};


// Init interface...
void initPIXInterface(struct interfacePIXConfig *interfacePIXPointer)
{
	memset(interfacePIXPointer, 0, sizeof(struct interfacePIXConfig));
	interfacePIXPointer->inOverride = false;
	interfacePIXPointer->outOverride = false;
	interfacePIXPointer->shutdown = false;
	interfacePIXPointer->uRPF = false;
}


// Process Interface
void processPIXInterface(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct interfacePIXConfig *interfacePIXPointer = 0;
	struct ciscoCommand command;
	fpos_t filePosition;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Interface Line: %s\n", line);
	}

	// Init
	command = splitLine(line);

	// Unsupported
	if ((strcmp(command.part[0], "interface") == 0) && ((strcmp(command.part[1], "lbprivate") == 0) || (strcmp(command.part[1], "lbpublic") == 0)))
	{
	}

	// new interface line(s) (PIX7+)
	else if ((strcmp(command.part[0], "interface") == 0) && (command.parts == 2))
	{
		// If this is the first interface
		if (nipper->pix->interface == 0)
		{
			// Create structure
			nipper->pix->interface = malloc(sizeof(struct interfacePIXConfig));
			memset(nipper->pix->interface, 0 , sizeof(struct interfacePIXConfig));
			interfacePIXPointer = nipper->pix->interface;
			initPIXInterface(interfacePIXPointer);
		}
		else
		{
			// Search for interface...
			interfacePIXPointer = nipper->pix->interface;
			while ((interfacePIXPointer->next != 0) && (strcmp(interfacePIXPointer->name, command.part[1]) != 0))
				interfacePIXPointer = interfacePIXPointer->next;

			// If it hasn't been found
			if (strcmp(interfacePIXPointer->name, command.part[1]) != 0)
			{
				// Create structure
				interfacePIXPointer->next = malloc(sizeof(struct interfacePIXConfig));
				memset(interfacePIXPointer->next, 0 , sizeof(struct interfacePIXConfig));
				interfacePIXPointer = interfacePIXPointer->next;
				initPIXInterface(interfacePIXPointer);
			}
		}

		// Init
		strncpy(interfacePIXPointer->interface, command.part[1], sizeof(interfacePIXPointer->interface) - 1);

		// Loop through the interface lines
		fgetpos(nipper->input, &filePosition);
		readLine(nipper->input, line, nipper->maxSize);
		while ((feof(nipper->input) == 0) && (line[0] == ' '))
		{
			// Debug
			if (nipper->debugMode == true)
			{
				printf("Line Line: %s\n", line);
			}

			// Init
			command = splitLine(line);

			// nameif
			if (strcmp(command.part[0], "nameif") == 0)
				strncpy(interfacePIXPointer->name, command.part[1], sizeof(interfacePIXPointer->name) - 1);

			// IP Address
			else if ((strcmp(command.part[0], "ip") == 0) && (strcmp(command.part[1], "address") == 0))
			{
				if (strcmp(command.part[2], "dhcp") == 0)
				{
					strcpy(interfacePIXPointer->ipAddress, "dhcp");
					strcpy(interfacePIXPointer->netMask, "dhcp");
				}
				else
				{
					strncpy(interfacePIXPointer->ipAddress, command.part[2], sizeof(interfacePIXPointer->ipAddress) - 1);
					strncpy(interfacePIXPointer->netMask, command.part[3], sizeof(interfacePIXPointer->netMask) - 1);
				}
			}

			// No shutdown
			else if ((strcmp(command.part[0], "no") == 0) && (strcmp(command.part[1], "shutdown") == 0))
				interfacePIXPointer->shutdown = false;

			// Shutdown
			else if (strcmp(command.part[0], "shutdown") == 0)
				interfacePIXPointer->shutdown = true;

			// Security Level
			else if (strcmp(command.part[0], "security-level") == 0)
				interfacePIXPointer->security = atoi(command.part[1]);

			// Read next line
			fgetpos(nipper->input, &filePosition);
			readLine(nipper->input, line, nipper->maxSize);
		}
		fsetpos(nipper->input, &filePosition);
	}

	// nameif...
	else if (strcmp(command.part[0], "nameif") == 0)
	{
		if (nipper->pix->interface == 0)
		{
			// Create structure
			nipper->pix->interface = malloc(sizeof(struct interfacePIXConfig));
			interfacePIXPointer = nipper->pix->interface;
			initPIXInterface(interfacePIXPointer);
		}
		else
		{
			// Search for interface (just in case)
			interfacePIXPointer = nipper->pix->interface;
			while ((interfacePIXPointer->next != 0) && ((strcmp(interfacePIXPointer->name, command.part[2]) != 0) && (strcmp(interfacePIXPointer->interface, command.part[1]) != 0)))
				interfacePIXPointer = interfacePIXPointer->next;

			// If it has not been found (probable), then create a new struct...
			if ((strcmp(interfacePIXPointer->name, command.part[2]) != 0) && (strcmp(interfacePIXPointer->interface, command.part[1]) != 0))
			{
				// Create structure
				interfacePIXPointer->next = malloc(sizeof(struct interfacePIXConfig));
				interfacePIXPointer = interfacePIXPointer->next;
				initPIXInterface(interfacePIXPointer);
			}
		}

		// Copy the info into the structure
		strncpy(interfacePIXPointer->interface, command.part[1], sizeof(interfacePIXPointer->interface) - 1);
		strncpy(interfacePIXPointer->name, command.part[2], sizeof(interfacePIXPointer->name) - 1);
		interfacePIXPointer->security = atoi(command.part[3] + 8);
	}

	// old interface line...
	else if (strcmp(command.part[0], "interface") == 0)
	{
		// Check to see if an interface has already been created
		if (nipper->pix->interface == 0)
		{
			// Create structure
			nipper->pix->interface = malloc(sizeof(struct interfacePIXConfig));
			interfacePIXPointer = nipper->pix->interface;
			initPIXInterface(interfacePIXPointer);
		}

		else
		{
			// Search for interface...
			interfacePIXPointer = nipper->pix->interface;
			while ((interfacePIXPointer->next != 0) && (strcmp(interfacePIXPointer->interface, command.part[1]) != 0))
				interfacePIXPointer = interfacePIXPointer->next;

			// If it hasn't been found
			if (strcmp(interfacePIXPointer->interface, command.part[1]) != 0)
			{
				// Create structure
				interfacePIXPointer->next = malloc(sizeof(struct interfacePIXConfig));
				interfacePIXPointer = interfacePIXPointer->next;
				initPIXInterface(interfacePIXPointer);
			}
		}

		// Copy the info into the structure
		strncpy(interfacePIXPointer->interface, command.part[1], sizeof(interfacePIXPointer->interface) - 1);

		// Interface shutdown?
		if (strcmp(command.part[command.parts - 1], "shutdown") == 0)
			interfacePIXPointer->shutdown = true;
	}

	// IP Address...
	else if ((strcmp(command.part[0], "ip") == 0) && (strcmp(command.part[1], "address") == 0))
	{
		// Check to see if an interface has already been created
		if (nipper->pix->interface == 0)
		{
			// Create structure
			nipper->pix->interface = malloc(sizeof(struct interfacePIXConfig));
			interfacePIXPointer = nipper->pix->interface;
			initPIXInterface(interfacePIXPointer);
		}

		else
		{
			// Search for interface...
			interfacePIXPointer = nipper->pix->interface;
			while ((interfacePIXPointer->next != 0) && (strcmp(interfacePIXPointer->name, command.part[2]) != 0))
				interfacePIXPointer = interfacePIXPointer->next;

			// If it hasn't been found
			if (strcmp(interfacePIXPointer->name, command.part[2]) != 0)
			{
				// Create structure
				interfacePIXPointer->next = malloc(sizeof(struct interfacePIXConfig));
				interfacePIXPointer = interfacePIXPointer->next;
				initPIXInterface(interfacePIXPointer);
			}
		}

		// Copy the info into the structure
		strncpy(interfacePIXPointer->name, command.part[2], sizeof(interfacePIXPointer->name) - 1);
		strncpy(interfacePIXPointer->ipAddress, command.part[3], sizeof(interfacePIXPointer->ipAddress) - 1);
		strncpy(interfacePIXPointer->netMask, command.part[4], sizeof(interfacePIXPointer->netMask) - 1);
	}

	// Access Group...
	else if (strcmp(command.part[0], "access-group") == 0)
	{
		// Increment counter
		nipper->pix->interfaceAccessList++;

		// Check to see if an interface has already been created
		if (nipper->pix->interface == 0)
		{
			// Create structure
			nipper->pix->interface = malloc(sizeof(struct interfacePIXConfig));
			interfacePIXPointer = nipper->pix->interface;
			initPIXInterface(interfacePIXPointer);
		}

		else
		{
			// Search for interface...
			interfacePIXPointer = nipper->pix->interface;
			while ((interfacePIXPointer->next != 0) && (strcmp(interfacePIXPointer->name, command.part[4]) != 0))
				interfacePIXPointer = interfacePIXPointer->next;

			// If it hasn't been found
			if (strcmp(interfacePIXPointer->name, command.part[4]) != 0)
			{
				// Create structure
				interfacePIXPointer->next = malloc(sizeof(struct interfacePIXConfig));
				interfacePIXPointer = interfacePIXPointer->next;
				initPIXInterface(interfacePIXPointer);
			}
		}

		// Interface Name
		strncpy(interfacePIXPointer->name, command.part[4], sizeof(interfacePIXPointer->name) - 1);

		// In...
		if (strcmp(command.part[2], "in") == 0)
			strncpy(interfacePIXPointer->in, command.part[1], sizeof(interfacePIXPointer->in) - 1);

		// Out...
		else 
			if (strcmp(command.part[2], "out") == 0)
			strncpy(interfacePIXPointer->out, command.part[1], sizeof(interfacePIXPointer->out) - 1);

		// User Override
		if (command.parts > 5)
		{
			if ((strcmp(command.part[2], "in") == 0) && (strcmp(command.part[5], "per-user-override") == 0))
				interfacePIXPointer->inOverride = true;
			else if ((strcmp(command.part[2], "out") == 0) && (strcmp(command.part[5], "per-user-override") == 0))
				interfacePIXPointer->outOverride = true;
		}
	}
}


// Process uRPF
void processPIXuRPF(char *line, struct nipperConfig *nipper)
{
	// Variables..
	struct interfacePIXConfig *interfacePIXPointer = 0;
	struct ciscoCommand command;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("uRPF Line: %s\n", line);
	}

	// Init
	command = splitLine(line);

	// Set Interface...
	interfacePIXPointer = nipper->pix->interface;
	while (interfacePIXPointer != 0)
	{
		if (strcmp(interfacePIXPointer->name, command.part[4]) == 0)
			interfacePIXPointer->uRPF = true;
		interfacePIXPointer = interfacePIXPointer->next;
	}
}

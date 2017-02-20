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


// Process Small Servers
void processSmallServers(char *line, struct nipperConfig *nipper)
{
	// Debug output
	if (nipper->debugMode == true)
		printf("Small Servers Line: %s\n", line);
	
	// Get setting
	if (strncmp("service tcp-small-servers", line, 25) == 0)
		nipper->ios->tcpSmallServers = true;

	else if (strncmp("service udp-small-servers", line, 25) == 0)
		nipper->ios->udpSmallServers = true;

	else if (strncmp("no service tcp-small-servers", line, 28) == 0)
		nipper->ios->tcpSmallServers = false;

	else if (strncmp("no service udp-small-servers", line, 28) == 0)
		nipper->ios->udpSmallServers = false;
}


// Process Bootp
void processBootp(char *line, struct nipperConfig *nipper)
{
	// Debug output
	if (nipper->debugMode == true)
		printf("Bootp Line: %s\n", line);
	
	// Get setting
	if (strncmp("no ip bootp server", line, 18) == 0)
		nipper->ios->bootp = false;

	else if (strncmp("ip bootp server", line, 15) == 0)
		nipper->ios->bootp = true;
}


// Process Domain Loopup
void processDomainLookup(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct ciscoCommand command;

	// Split the command line up
	command = splitLine(line);

	// Debug output
	if (nipper->debugMode == true)
		printf("Domain Lookup Line: %s\n", line);
	
	// Get setting
	if (strcmp(command.part[0], "no") == 0)
		nipper->ios->domainLookup = false;
	else
		nipper->ios->domainLookup = true;
}


// Process Boot Network
void processBootNetwork(char *line, struct nipperConfig *nipper)
{
	// Debug
	if (nipper->debugMode == true)
	{
		printf("Boot Network Line: %s\n", line);
	}

	// Enabled
	if (strncmp(line, "boot network", 12) == 0)
		nipper->ios->bootNetwork = true;

	// Disabled
	if (strncmp(line, "no boot network", 15) == 0)
		nipper->ios->bootNetwork = false;
}


// Process Service Config
void processServiceConfig(char *line, struct nipperConfig *nipper)
{
	// Debug
	if (nipper->debugMode == true)
	{
		printf("Service Config Line: %s\n", line);
	}

	// Enabled
	if (strncmp(line, "service config", 14) == 0)
		nipper->ios->serviceConfig = true;

	// Disabled
	if (strncmp(line, "no service config", 17) == 0)
		nipper->ios->serviceConfig = false;
}


// Privilage Levels
struct privilageLevels
{
	char command[64];
	int level;
	struct privilageLevels *next;
};


// Process privilage
void processPrivilage(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct privilageLevels *privilagePointer = 0;
	struct ciscoCommand command;
	char tempString[sizeof(line)];

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Privilage Line: %s\n", line);
	}

	// Is this the first privilage
	if (nipper->ios->privilage == 0)
	{
		// Create storage for enable...
		privilagePointer = malloc(sizeof(struct privilageLevels));
		memset(privilagePointer, 0, sizeof(struct privilageLevels));

		// Sort out pointers...
		privilagePointer->next = nipper->ios->privilage;
		nipper->ios->privilage = privilagePointer;
	}
	else
	{
		// Get last privilage
		privilagePointer = nipper->ios->privilage;
		while (privilagePointer->next != 0)
			privilagePointer = privilagePointer->next;

		// Create structure
		privilagePointer->next = malloc(sizeof(struct privilageLevels));
		memset(privilagePointer->next, 0, sizeof(struct privilageLevels));
		privilagePointer = privilagePointer->next;

		// Init
		privilagePointer->next = 0;
	}

	// Init
	command = splitLine(line);
	strcpy(tempString, "");

	// Privilage Level
	privilagePointer->level = atoi(command.part[3]);

	// Command Access
	int loop;
	for (loop = 4; loop < command.parts; loop++)
	{
		sprintf(tempString, "%s %s", tempString, command.part[loop]);
	}
	strncpy(privilagePointer->command, tempString, sizeof(privilagePointer->command));
}


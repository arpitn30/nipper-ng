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


struct snmpSOS
{
	char contact[64];
	char location[64];
	char systemName[64];
	int listenPort;
	int trapPort;
	int authTrap;
	struct snmpCommunitySOS *community;
	struct snmpHostSOS *host;
};


struct snmpCommunitySOS
{
	char community[64];
	int weak;
	int dictionary;
	int readOnly;
	int enableTraps;
	int trafficTraps;
	int version;
	struct snmpCommunitySOS *next;
};


struct snmpHostSOS
{
	char community[64];
	int weak;
	int dictionary;
	char host[32];
	char sourceInterface[32];
	int version;
	struct snmpHostSOS *next;
};


// Process admin lines
void processSOSSNMP(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct ciscoCommand command;
	struct snmpCommunitySOS *communityPointer = 0;
	struct snmpHostSOS *snmpHostPointer = 0;
	int tempInt;

	if (nipper->debugMode == true)
		printf("SNMP Line: %s\n", line);

	// Init
	command = splitLine(line);

	// Create SNMP Struct if required.
	if (nipper->sos->snmp == 0)
	{
		nipper->sos->snmp = malloc(sizeof(struct snmpSOS));
		memset(nipper->sos->snmp, 0 , sizeof(struct snmpSOS));
		nipper->sos->snmp->listenPort = 161;
		nipper->sos->snmp->trapPort = 162;
		nipper->sos->snmp->authTrap = false;
	}

	// SNMP Contact...
	if (strcasecmp(command.part[2], "contact") == 0)
		stripQuotes(command.part[3], nipper->sos->snmp->contact, sizeof(nipper->sos->snmp->contact));

	// SNMP location...
	else if (strcasecmp(command.part[2], "location") == 0)
		stripQuotes(command.part[3], nipper->sos->snmp->location, sizeof(nipper->sos->snmp->location));

	// SNMP System Name...
	else if (strcasecmp(command.part[2], "name") == 0)
		stripQuotes(command.part[3], nipper->sos->snmp->systemName, sizeof(nipper->sos->snmp->systemName));

	// SNMP Listen Port...
	else if ((strcasecmp(command.part[2], "port") == 0) && (strcmp(command.part[3], "listen") == 0))
		nipper->sos->snmp->listenPort = atoi(command.part[4]);

	// SNMP Trap Port...
	else if ((strcasecmp(command.part[2], "port") == 0) && (strcmp(command.part[3], "trap") == 0))
		nipper->sos->snmp->trapPort = atoi(command.part[4]);

	// Authentication Traps...
	else if ((strcasecmp(command.part[2], "auth-trap") == 0) && (strcmp(command.part[3], "enable") == 0))
		nipper->sos->snmp->authTrap = true;

	// Community
	else if ((strcasecmp(command.part[2], "community") == 0) && (strcmp(command.part[0], "set") == 0))
	{
		// If first community...
		if (nipper->sos->snmp->community == 0)
		{
			nipper->sos->snmp->community = malloc(sizeof(struct snmpCommunitySOS));
			memset(nipper->sos->snmp->community, 0 , sizeof(struct snmpCommunitySOS));
			communityPointer = nipper->sos->snmp->community;
		}
		else
		{
			communityPointer = nipper->sos->snmp->community;
			while (communityPointer->next != 0)
				communityPointer = communityPointer->next;
			communityPointer->next = malloc(sizeof(struct snmpCommunitySOS));
			memset(communityPointer->next, 0 , sizeof(struct snmpCommunitySOS));
			communityPointer = communityPointer->next;
		}

		// Init...
		communityPointer->enableTraps = false;
		communityPointer->trafficTraps = false;
		communityPointer->version = snmp1_2;
		communityPointer->weak = false;
		communityPointer->dictionary = false;

		// Community
		stripQuotes(command.part[3], communityPointer->community, sizeof(communityPointer->community));

		// Check strength / dictionary...
		if (simplePassword(communityPointer->community, nipper) == true)
		{
			nipper->simplePasswords++;
			communityPointer->dictionary = true;
		}
		if (passwordStrength(communityPointer->community, nipper) == false)
		{
			nipper->passwordStrengths++;
			communityPointer->weak = true;
		}

		// Get other parameters...
		tempInt = 4;
		while (tempInt < command.parts)
		{
			// version
			if (strcasecmp(command.part[tempInt], "version") == 0)
			{
				tempInt++;
				if (strcasecmp(command.part[tempInt], "any") == 0)
					communityPointer->version = snmp1_2;
				else if (strcasecmp(command.part[tempInt], "v1") == 0)
					communityPointer->version = snmp1;
				else if ((strcasecmp(command.part[tempInt], "v2") == 0) || (strcmp(command.part[tempInt], "v2c") == 0))
					communityPointer->version = snmp2c;
			}

			// Trap On
			else if (strcasecmp(command.part[tempInt], "trap-on") == 0)
				communityPointer->enableTraps = true;

			// Trap Off
			else if (strcasecmp(command.part[tempInt], "trap-off") == 0)
				communityPointer->enableTraps = false;

			// Trap On
			else if (strcasecmp(command.part[tempInt], "traffic") == 0)
				communityPointer->trafficTraps = true;

			tempInt++;
		}
	}

	// Host
	else if (strcasecmp(command.part[2], "host") == 0)
	{
		// If first community...
		if (nipper->sos->snmp->host == 0)
		{
			nipper->sos->snmp->host = malloc(sizeof(struct snmpHostSOS));
			memset(nipper->sos->snmp->host, 0 , sizeof(struct snmpHostSOS));
			snmpHostPointer = nipper->sos->snmp->host;
		}
		else
		{
			snmpHostPointer = nipper->sos->snmp->host;
			while (snmpHostPointer->next != 0)
				snmpHostPointer = snmpHostPointer->next;
			snmpHostPointer->next = malloc(sizeof(struct snmpHostSOS));
			memset(snmpHostPointer->next, 0 , sizeof(struct snmpHostSOS));
			snmpHostPointer = snmpHostPointer->next;
		}

		// Init
		strcpy(snmpHostPointer->sourceInterface, "Any");
		snmpHostPointer->weak = false;
		snmpHostPointer->dictionary = false;

		// Community
		stripQuotes(command.part[3], snmpHostPointer->community, sizeof(snmpHostPointer->community));

		// Check strength / dictionary...
		if (simplePassword(snmpHostPointer->community, nipper) == true)
		{
			nipper->simplePasswords++;
			snmpHostPointer->dictionary = true;
		}
		if (passwordStrength(snmpHostPointer->community, nipper) == false)
		{
			nipper->passwordStrengths++;
			snmpHostPointer->weak = true;
		}

		// Host
		stripQuotes(command.part[4], snmpHostPointer->host, sizeof(snmpHostPointer->host));

		// Options and Trap version
		tempInt = 5;
		while (tempInt < command.parts)
		{
			// Source Interface...
			if (strcasecmp(command.part[tempInt], "src-interface") == 0)
			{
				tempInt++;
				stripQuotes(command.part[tempInt], snmpHostPointer->sourceInterface, sizeof(snmpHostPointer->sourceInterface));
			}

			// trap...
			else if (strcasecmp(command.part[tempInt], "trap") == 0)
			{
				tempInt++;
				if (strcasecmp(command.part[tempInt], "v1") == 0)
					snmpHostPointer->version = snmp1;
				else if ((strcasecmp(command.part[tempInt], "v2") == 0) || (strcasecmp(command.part[tempInt], "v2c") == 0))
					snmpHostPointer->version = snmp2c;
			}

			tempInt++;
		}
	}
}


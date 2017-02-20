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


#define snmp_nmp_readonly 0
#define snmp_nmp_readwrite 1
#define snmp_nmp_readwrite_all 2

#define snmp_nmp_standard 0
#define snmp_nmp_extended 1


// SNMP Community
struct snmpNMPCommunity
{
	int type;					// snmp_nmp_standard...
	char community[64];
	int weak;
	int dictionary;
	int access;					// snmp_nmp_readonly...
	struct snmpNMPCommunity *next;
};


// SNMP Host
struct snmpNMPHost
{
	char host[32];
	char community[64];
	int weak;
	int dictionary;
	int version;
	int port;
	char owner[32];
	int index;
	struct snmpNMPHost *next;
};


// SNMP
struct snmpNMP
{
	struct snmpNMPCommunity *community;
	struct snmpNMPHost *host;
	struct snmpTrap *trap;
};


// Process SNMP
void processNMPSnmp(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct snmpNMPCommunity *communityPointer = 0;
	struct snmpTrap *snmpTrapPointer = 0;
	struct snmpNMPHost *snmpHostPointer = 0;
	struct ciscoCommand command;
	int tempInt = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("SNMP Line: %s\n", line);
	}

	// Init
	command = splitLine(line);

	// Check to see if SNMP already exists
	if (nipper->nmp->snmp == 0)
	{
		nipper->nmp->snmp = malloc(sizeof(struct snmpNMP));
		memset(nipper->nmp->snmp, 0 , sizeof(struct snmpNMP));
	}

	// SNMP Community
	if (strncmp(line, "set snmp community ", 19) == 0)
	{
		// Is first community...
		if (nipper->nmp->snmp->community == 0)
		{
			nipper->nmp->snmp->community = malloc(sizeof(struct snmpNMPCommunity));
			communityPointer = nipper->nmp->snmp->community;
		}
		else
		{
			communityPointer = nipper->nmp->snmp->community;
			while (communityPointer->next != 0)
				communityPointer = communityPointer->next;
			communityPointer->next = malloc(sizeof(struct snmpNMPCommunity));
			communityPointer = communityPointer->next;
		}

		// Init
		memset(communityPointer, 0, sizeof(struct snmpNMPCommunity));
		communityPointer->type = snmp_nmp_standard;

		// Access
		if (strcmp(command.part[3], "read-only") == 0)
			communityPointer->access = snmp_nmp_readonly;
		else if (strcmp(command.part[3], "read-write") == 0)
			communityPointer->access = snmp_nmp_readwrite;
		else if (strcmp(command.part[3], "read-write-all") == 0)
			communityPointer->access = snmp_nmp_readwrite_all;

		// Community
		strncpy(communityPointer->community, command.part[4], sizeof(communityPointer->community) - 1);

		// Password Strength
		if (passwordStrength(communityPointer->community, nipper) == false)
		{
			communityPointer->weak = true;
			nipper->passwordStrengths++;
		}
		else
			communityPointer->weak = false;

		// Password Dictionary
		communityPointer->dictionary = simplePassword(communityPointer->community, nipper);
		if (communityPointer->dictionary == true)
			nipper->simplePasswords++;
	}

	// SNMP Trap
	else if ((strncmp(line, "set snmp trap enable ", 21) == 0) || (strncmp(line, "set snmp trap disable ", 22) == 0))
	{
		// Is first trap...
		if (nipper->nmp->snmp->trap == 0)
		{
			nipper->nmp->snmp->trap = malloc(sizeof(struct snmpTrap));
			snmpTrapPointer = nipper->nmp->snmp->trap;
		}
		else
		{
			snmpTrapPointer = nipper->nmp->snmp->trap;
			while (snmpTrapPointer->next != 0)
				snmpTrapPointer = snmpTrapPointer->next;
			snmpTrapPointer->next = malloc(sizeof(struct snmpTrap));
			snmpTrapPointer = snmpTrapPointer->next;
		}

		// Init
		memset(snmpTrapPointer, 0, sizeof(struct snmpTrap));

		// Is enable?
		if (strcmp(command.part[3], "enable") == 0)
		{
			snmpTrapPointer->enabled = true;
			tempInt = 21;
		}
		else
		{
			snmpTrapPointer->enabled = false;
			tempInt = 22;
		}

		// Traps
		while (line[tempInt] == ' ')
			tempInt++;
		strncpy(snmpTrapPointer->trap, line + tempInt, sizeof(snmpTrapPointer->trap) - 1);
	}

	// SNMP Host
	else if (strncmp(line, "set snmp trap ", 14) == 0)
	{
		// Is first host...
		if (nipper->nmp->snmp->host == 0)
		{
			nipper->nmp->snmp->host = malloc(sizeof(struct snmpNMPHost));
			snmpHostPointer = nipper->nmp->snmp->host;
		}
		else
		{
			snmpHostPointer = nipper->nmp->snmp->host;
			while (snmpHostPointer->next != 0)
				snmpHostPointer = snmpHostPointer->next;
			snmpHostPointer->next = malloc(sizeof(struct snmpNMPHost));
			snmpHostPointer = snmpHostPointer->next;
		}

		// Init
		memset(snmpHostPointer, 0, sizeof(struct snmpNMPHost));

		// Host
		strncpy(snmpHostPointer->host, command.part[3], sizeof(snmpHostPointer->host) - 1);

		// Community
		strncpy(snmpHostPointer->community, command.part[4], sizeof(snmpHostPointer->community) - 1);

		// Password Strength
		if (passwordStrength(snmpHostPointer->community, nipper) == false)
		{
			nipper->passwordStrengths++;
			snmpHostPointer->weak = true;
		}
		else
			snmpHostPointer->weak = false;

		// Password Dictionary
		snmpHostPointer->dictionary = simplePassword(snmpHostPointer->community, nipper);
		if (snmpHostPointer->dictionary == true)
			nipper->simplePasswords++;

		// Get other options...
		tempInt = 5;
		while (tempInt < command.parts)
		{
			// Version
			if (strcmp(command.part[tempInt], "version") == 0)
				snmpHostPointer->version = atoi(command.part[tempInt + 1]);

			// Port
			else if (strcmp(command.part[tempInt], "port") == 0)
				snmpHostPointer->port = atoi(command.part[tempInt + 1]);

			// Owner
			else if (strcmp(command.part[tempInt], "owner") == 0)
				strncpy(snmpHostPointer->owner, command.part[tempInt + 1], sizeof(snmpHostPointer->owner) - 1);

			// Index
			else if (strcmp(command.part[tempInt], "index") == 0)
				snmpHostPointer->index = atoi(command.part[tempInt + 1]);

			tempInt = tempInt + 2;
		}
	}
}

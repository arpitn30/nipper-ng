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


// SNMP Community
struct snmpCSSCommunity
{
	char community[32];
	int readOnly;
	struct snmpCSSCommunity *next;
};

// SNMP Host
struct snmpCSSHost
{
	char host[64];
	char community[13];
	int snmpType;			// snmp1 (default) or snmp2c
	struct snmpCSSHost *next;
};


// SNMP Config
struct snmpCSS
{
	char name[128];
	char contact[128];
	char location[128];
	int reloadEnabled;				// true or false (default)
	struct snmpCSSCommunity *community;
	struct snmpCSSHost *host;
};


// Process SNMP
void processCSSSNMP(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct ciscoCommand command;
	struct snmpCSSCommunity *snmpCSSCommunityPointer = 0;
	struct snmpCSSHost *snmpCSSHostPointer = 0;
	int tempInt = 0;
	int setting = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("SNMP Line: %s\n", line);
	}

	// Init
	command = splitLine(line);
	if (strcmp(command.part[0], "no") == 0)
	{
		setting = false;
		tempInt = 2;
	}
	else
	{
		setting = true;
		tempInt = 1;
	}

	// Check to see if SNMP already exists
	if (nipper->css->snmp == 0)
	{
		nipper->css->snmp = malloc(sizeof(struct snmpCSS));
		memset(nipper->css->snmp, 0, sizeof(struct snmpCSS));
		nipper->css->snmp->reloadEnabled = false;
	}

	// Community
	if (strcmp(command.part[tempInt], "community") == 0)
	{
		tempInt++;

		// Create Community
		if (nipper->css->snmp->community == 0)
		{
			snmpCSSCommunityPointer = malloc(sizeof(struct snmpCSSCommunity));
			nipper->css->snmp->community = snmpCSSCommunityPointer;
		}
		else
		{
			snmpCSSCommunityPointer = nipper->css->snmp->community;
			while (snmpCSSCommunityPointer->next != 0)
				snmpCSSCommunityPointer = snmpCSSCommunityPointer->next;
			snmpCSSCommunityPointer->next = malloc(sizeof(struct snmpCSSCommunity));
			snmpCSSCommunityPointer = snmpCSSCommunityPointer->next;
		}

		// Init
		memset(snmpCSSCommunityPointer, 0, sizeof(struct snmpCSSCommunity));

		// Community
		strncpy(snmpCSSCommunityPointer->community, command.part[tempInt], sizeof(snmpCSSCommunityPointer->community) -1);
		tempInt++;

		// Read / Read+Write
		if (strcmp(command.part[tempInt], "read-only") == 0)
			snmpCSSCommunityPointer->readOnly = true;
		else
			snmpCSSCommunityPointer->readOnly = false;
	}

	// Contact
	else if (strcmp(command.part[tempInt], "contact") == 0)
		stripQuotes(command.part[tempInt+1], nipper->css->snmp->contact, sizeof(nipper->css->snmp->contact) -1);

	// Location
	else if (strcmp(command.part[tempInt], "location") == 0)
		stripQuotes(command.part[tempInt+1], nipper->css->snmp->location, sizeof(nipper->css->snmp->location) -1);

	// Name
	else if (strcmp(command.part[tempInt], "name") == 0)
	{
		stripQuotes(command.part[tempInt+1], nipper->css->snmp->name, sizeof(nipper->css->snmp->name) -1);
		if (strlen(nipper->hostname) == 0)
			stripQuotes(command.part[tempInt+1], nipper->hostname, sizeof(nipper->hostname) -1);
	}

	// Reload Enable
	else if (strcmp(command.part[tempInt], "reload-enable") == 0)
		nipper->css->snmp->reloadEnabled = setting;

	// Trap Host
	else if (strcmp(command.part[tempInt], "trap-host") == 0)
	{
		tempInt++;

		// Create Host
		if (nipper->css->snmp->host == 0)
		{
			snmpCSSHostPointer = malloc(sizeof(struct snmpCSSHost));
			nipper->css->snmp->host = snmpCSSHostPointer;
		}
		else
		{
			snmpCSSHostPointer = nipper->css->snmp->host;
			while (snmpCSSHostPointer->next != 0)
				snmpCSSHostPointer = snmpCSSHostPointer->next;
			snmpCSSHostPointer->next = malloc(sizeof(struct snmpCSSHost));
			snmpCSSHostPointer = snmpCSSHostPointer->next;
		}

		// Init
		memset(snmpCSSHostPointer, 0, sizeof(struct snmpCSSHost));

		// Host
		strncpy(snmpCSSHostPointer->host, command.part[tempInt], sizeof(snmpCSSHostPointer->host) -1);
		tempInt++;

		// Community
		strncpy(snmpCSSHostPointer->community, command.part[tempInt], sizeof(snmpCSSHostPointer->community) -1);
		tempInt++;

		// SNMP Version
		if (strcmp(command.part[tempInt], "snmpv2") == 0)
			snmpCSSHostPointer->snmpType = snmp2c;
		else
			snmpCSSHostPointer->snmpType = snmp1;
	}

	// Debug (lines not processed)
	else if (nipper->linesnotprocessed == true)
		printf("%s\n", line);
}

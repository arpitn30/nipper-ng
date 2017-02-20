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


struct interfaceSOS
{
	char name[32];
	int enabled;
	char zone[32];
	char ipAddress[32];
									// Manage (unconfigured, true, false)
	int manageIdent;					// Ident Reset
	int manageMtrace;					// Mtrace
	int manageNsmgmt;					// NetScreen Managment
	int managePing;						// Ping
	int manageSnmp;						// SNMP
	int manageSsh;						// SSH
	int manageSsl;						// SSL
	int manageTelnet;					// Telnet
	int manageWeb;						// Web

	struct interfaceSOS *next;
};


// Process Interface
void processSOSInterface(char *line, struct nipperConfig *nipper)
{
	// Variables
	char tempString[nipper->maxSize];
	struct ciscoCommand command;
	struct interfaceSOS *interfaceSOSPointer = 0;


	if (nipper->debugMode == true)
		printf("Interface Line: %s\n", line);

	// Init
	command = splitLine(line);

	// Has Auth Server structure been created?
	if (nipper->sos->interface == 0)
	{
		// Create
		nipper->sos->interface = malloc(sizeof(struct interfaceSOS));

		// Init
		memset(nipper->sos->interface, 0 , sizeof(struct interfaceSOS));
		interfaceSOSPointer = nipper->sos->interface;
		strcpy(interfaceSOSPointer->ipAddress, "None");
		interfaceSOSPointer->enabled = true;
		interfaceSOSPointer->manageIdent = unconfigured;
		interfaceSOSPointer->manageMtrace = unconfigured;
		interfaceSOSPointer->manageNsmgmt = unconfigured;
		interfaceSOSPointer->managePing = unconfigured;
		interfaceSOSPointer->manageSnmp = unconfigured;
		interfaceSOSPointer->manageSsh = unconfigured;
		interfaceSOSPointer->manageSsl = unconfigured;
		interfaceSOSPointer->manageTelnet = unconfigured;
		interfaceSOSPointer->manageWeb = unconfigured;
	}

	// Search for server
	else
	{
		interfaceSOSPointer = nipper->sos->interface;
		stripQuotes(command.part[2], tempString, nipper->maxSize);
		while ((interfaceSOSPointer->next != 0) && (strcmp(tempString, interfaceSOSPointer->name) != 0))
			interfaceSOSPointer = interfaceSOSPointer->next;

		// If not found
		if (strcmp(tempString, interfaceSOSPointer->name) != 0)
		{
			// Create
			interfaceSOSPointer->next = malloc(sizeof(struct interfaceSOS));

			// Init
			memset(interfaceSOSPointer->next, 0 , sizeof(struct interfaceSOS));
			interfaceSOSPointer = interfaceSOSPointer->next;
			strcpy(interfaceSOSPointer->ipAddress, "None");
			interfaceSOSPointer->enabled = true;
			interfaceSOSPointer->manageIdent = unconfigured;
			interfaceSOSPointer->manageMtrace = unconfigured;
			interfaceSOSPointer->manageNsmgmt = unconfigured;
			interfaceSOSPointer->managePing = unconfigured;
			interfaceSOSPointer->manageSnmp = unconfigured;
			interfaceSOSPointer->manageSsh = unconfigured;
			interfaceSOSPointer->manageSsl = unconfigured;
			interfaceSOSPointer->manageTelnet = unconfigured;
			interfaceSOSPointer->manageWeb = unconfigured;
		}
	}

	// Set auth-server name
	stripQuotes(command.part[2], interfaceSOSPointer->name, sizeof(interfaceSOSPointer->name));

	// Disabled?
	if (strcasecmp(command.part[3], "disable") == 0)
		interfaceSOSPointer->enabled = false;

	// Zone
	else if (strcasecmp(command.part[3], "zone") == 0)
		stripQuotes(command.part[4], interfaceSOSPointer->zone, sizeof(interfaceSOSPointer->zone));

	// IP Address
	else if ((strcasecmp(command.part[0], "set") == 0) && (strcasecmp(command.part[3], "ip") == 0) && (strcasecmp(command.part[4], "manageable") != 0) && (strcasecmp(command.part[4], "unnumbered") != 0))
		stripQuotes(command.part[4], interfaceSOSPointer->ipAddress, sizeof(interfaceSOSPointer->ipAddress));

	// IP Address Unnumbered
	else if ((strcasecmp(command.part[0], "set") == 0) && (strcasecmp(command.part[3], "ip") == 0) && (strcasecmp(command.part[4], "unnumbered") == 0))
		stripQuotes(command.part[6], interfaceSOSPointer->ipAddress, sizeof(interfaceSOSPointer->ipAddress));

	// Manage
	else if (strcasecmp(command.part[3], "manage") == 0)
	{
		if (strcasecmp(command.part[4], "ident-reset") == 0)
		{
			if (strcasecmp(command.part[0], "set") == 0)
				interfaceSOSPointer->manageIdent = true;
			else
				interfaceSOSPointer->manageIdent = false;
		}
		else if (strcasecmp(command.part[4], "mtrace") == 0)
		{
			if (strcasecmp(command.part[0], "set") == 0)
				interfaceSOSPointer->manageMtrace = true;
			else
				interfaceSOSPointer->manageMtrace = false;
		}
		else if (strcasecmp(command.part[4], "nsmgmt") == 0)
		{
			if (strcasecmp(command.part[0], "set") == 0)
				interfaceSOSPointer->manageNsmgmt = true;
			else
				interfaceSOSPointer->manageNsmgmt = false;
		}
		else if (strcasecmp(command.part[4], "ping") == 0)
		{
			if (strcasecmp(command.part[0], "set") == 0)
				interfaceSOSPointer->managePing = true;
			else
				interfaceSOSPointer->managePing = false;
		}
		else if (strcasecmp(command.part[4], "snmp") == 0)
		{
			if (strcasecmp(command.part[0], "set") == 0)
				interfaceSOSPointer->manageSnmp = true;
			else
				interfaceSOSPointer->manageSnmp = false;
		}
		else if (strcasecmp(command.part[4], "ssh") == 0)
		{
			if (strcasecmp(command.part[0], "set") == 0)
				interfaceSOSPointer->manageSsh = true;
			else
				interfaceSOSPointer->manageSsh = false;
		}
		else if (strcasecmp(command.part[4], "ssl") == 0)
		{
			if (strcasecmp(command.part[0], "set") == 0)
				interfaceSOSPointer->manageSsl = true;
			else
				interfaceSOSPointer->manageSsl = false;
		}
		else if (strcasecmp(command.part[4], "telnet") == 0)
		{
			if (strcasecmp(command.part[0], "set") == 0)
				interfaceSOSPointer->manageTelnet = true;
			else
				interfaceSOSPointer->manageTelnet = false;
		}
		else if (strcasecmp(command.part[4], "web") == 0)
		{
			if (strcasecmp(command.part[0], "set") == 0)
				interfaceSOSPointer->manageWeb = true;
			else
				interfaceSOSPointer->manageWeb = false;
		}
	}
}


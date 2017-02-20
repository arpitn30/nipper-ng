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


struct permitConfig
{
	int telnet;							// true, false or unconfigured
	struct hostNMP *telnetHost;
	int snmp;							// true, false or unconfigured
	struct hostNMP *snmpHost;
	int ssh;							// true, false or unconfigured
	struct hostNMP *sshHost;
	struct portConfig *next;
};


// Permit
void processNMPPermit(char *line, struct nipperConfig *nipper)
{
	// Variables
	int tempInt = 0;
	struct ciscoCommand command;
	struct hostNMP *hostNMPPointer = 0;

	// Debug output
	if (nipper->debugMode == true)
		printf("Permit Line: %s\n", line);

	// Init
	command = splitLine(line);

	// If permit doesn't exist...
	if (nipper->nmp->permit == 0)
	{
		// Create
		nipper->nmp->permit = malloc(sizeof(struct permitConfig));
		memset(nipper->nmp->permit, 0 , sizeof(struct permitConfig));
		// Init
		nipper->nmp->permit->telnet = unconfigured;
		nipper->nmp->permit->snmp = unconfigured;
		nipper->nmp->permit->ssh = unconfigured;
	}

	// Enable / Disable permit lists
	if ((strcmp(command.part[3], "enable") == 0) || (strcmp(command.part[3], "disable") == 0))
	{
		// Is it enable
		if (strcmp(command.part[3], "enable") == 0)
			tempInt = true;
		else
			tempInt = false;

		// If all are enabled / disabled
		if (command.parts == 4)
		{
			nipper->nmp->permit->telnet = tempInt;
			nipper->nmp->permit->snmp = tempInt;
			nipper->nmp->permit->ssh = tempInt;
		}

		// If it is telnet
		else if (strcmp(command.part[4], "telnet") == 0)
			nipper->nmp->permit->telnet = tempInt;

		// If it is snmp
		else if (strcmp(command.part[4], "snmp") == 0)
			nipper->nmp->permit->snmp = tempInt;

		// If it is ssh
		else if (strcmp(command.part[4], "ssh") == 0)
			nipper->nmp->permit->ssh = tempInt;
	}

	// If a permit host
	else
	{

		// Is it a telnet host
		if ((strcmp(command.part[command.parts - 1], "telnet") == 0) || (strcmp(command.part[command.parts - 1], "all") == 0))
		{
			// Create structure
			hostNMPPointer = malloc(sizeof(struct hostNMP));
			memset(hostNMPPointer, 0 , sizeof(struct hostNMP));

			// IP / Hostname
			strncpy(hostNMPPointer->host, command.part[3], sizeof(hostNMPPointer->host) - 1);

			// Net Mask?
			if (command.parts == 6)
				strncpy(hostNMPPointer->netMask, command.part[4], sizeof(hostNMPPointer->netMask) - 1);

			// Pointers
			hostNMPPointer->next = nipper->nmp->permit->telnetHost;
			nipper->nmp->permit->telnetHost = hostNMPPointer;
		}

		// Is it a ssh host
		if ((strcmp(command.part[command.parts - 1], "ssh") == 0) || (strcmp(command.part[command.parts - 1], "all") == 0))
		{
			// Create structure
			hostNMPPointer = malloc(sizeof(struct hostNMP));
			memset(hostNMPPointer, 0 , sizeof(struct hostNMP));

			// IP / Hostname
			strncpy(hostNMPPointer->host, command.part[3], sizeof(hostNMPPointer->host) - 1);

			// Net Mask?
			if (command.parts == 6)
				strncpy(hostNMPPointer->netMask, command.part[4], sizeof(hostNMPPointer->netMask) - 1);

			// Pointers
			hostNMPPointer->next = nipper->nmp->permit->sshHost;
			nipper->nmp->permit->sshHost = hostNMPPointer;
		}

		// Is it a snmp host
		if ((strcmp(command.part[command.parts - 1], "snmp") == 0) || (strcmp(command.part[command.parts - 1], "all") == 0))
		{
			// Create structure
			hostNMPPointer = malloc(sizeof(struct hostNMP));
			memset(hostNMPPointer, 0 , sizeof(struct hostNMP));

			// IP / Hostname
			strncpy(hostNMPPointer->host, command.part[3], sizeof(hostNMPPointer->host) - 1);

			// Net Mask?
			if (command.parts == 6)
				strncpy(hostNMPPointer->netMask, command.part[4], sizeof(hostNMPPointer->netMask) - 1);

			// Pointers
			hostNMPPointer->next = nipper->nmp->permit->snmpHost;
			nipper->nmp->permit->snmpHost = hostNMPPointer;
		}
	}
}





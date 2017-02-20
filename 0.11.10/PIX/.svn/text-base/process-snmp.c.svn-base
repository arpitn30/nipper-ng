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

// This file contains the code to process PIX SNMP

struct snmpPIXConfig
{
	int enabled;
	char community[64];
	int weak;
	int dictionary;
	char contact[128];
	char location[128];
	int port;
	struct snmpTrapPIX *trap;
	struct snmpPIXHost *host;
};

struct snmpPIXHost
{
	char interface[64];
	char address[64];
	char community[64];
	int mode;
	int port;
	int version;
	struct snmpPIXHost *next;
};

struct snmpTrapPIX
{
	char section[16];
	char trap[32];
	struct snmpTrapPIX *next;
};

#define snmp_mode_both 0
#define snmp_mode_poll 1
#define snmp_mode_trap 2


// Modify the traps...
void modifyPIXTraps(struct nipperConfig *nipper, char *trapSection, char *trapSubSection, int add)
{
	// Variables...
	struct snmpTrapPIX *trapPIXPointer = 0;
	struct snmpTrapPIX *trapPIXPointer2 = 0;

	// Is it an add?
	if (add == true)
	{
		// Reserve memory...
		if (nipper->pix->snmp->trap == 0)
		{
			nipper->pix->snmp->trap = malloc(sizeof(struct snmpTrapPIX));
			memset(nipper->pix->snmp->trap, 0, sizeof(struct snmpTrapPIX));
			trapPIXPointer = nipper->pix->snmp->trap;
		}
		else
		{
			trapPIXPointer = nipper->pix->snmp->trap;
			while (trapPIXPointer->next != 0)
				trapPIXPointer = trapPIXPointer->next;
			trapPIXPointer->next = malloc(sizeof(struct snmpTrapPIX));
			memset(trapPIXPointer->next, 0, sizeof(struct snmpTrapPIX));
			trapPIXPointer = trapPIXPointer->next;
		}

		// Copy data
		strncpy(trapPIXPointer->section, trapSection, sizeof(trapPIXPointer->section) - 1);
		strncpy(trapPIXPointer->trap, trapSubSection, sizeof(trapPIXPointer->trap) - 1);
	}

	// Remove trap...
	else
	{
		trapPIXPointer = nipper->pix->snmp->trap;
		trapPIXPointer2 = 0;
		while (trapPIXPointer != 0)
		{
			if (((strcmp(trapSection, trapPIXPointer->section) == 0) && (strcmp(trapSubSection, trapPIXPointer->trap) == 0)) || ((strcmp(trapSection, trapPIXPointer->section) == 0) && (strcmp(trapSubSection, "") == 0)))
			{
				if (trapPIXPointer2 == 0)
				{
					nipper->pix->snmp->trap = trapPIXPointer->next;
					free(trapPIXPointer);
					trapPIXPointer = nipper->pix->snmp->trap;
				}
				else
				{
					trapPIXPointer2->next = trapPIXPointer->next;
					free(trapPIXPointer);
					trapPIXPointer = trapPIXPointer2->next;
				}
			}
			else
			{
				trapPIXPointer2 = trapPIXPointer;
				trapPIXPointer = trapPIXPointer->next;
			}
		}
	}
}

// Process SNMP
void processSnmpPIX(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct ciscoCommand command;
	struct snmpPIXHost *snmpHostPIXPointer = 0;
	int tempInt;
	int tempInt2;
	int setting;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("SNMP Line: %s\n", line);
	}

	// Init
	command = splitLine(line);
	if (nipper->pix->snmp == 0)
	{
		nipper->pix->snmp = malloc(sizeof(struct snmpPIXConfig));
		memset(nipper->pix->snmp, 0, sizeof(struct snmpPIXConfig));

		// Defaults...
		nipper->pix->snmp->enabled = true;
		nipper->pix->snmp->port = 161;
		strcpy(nipper->pix->snmp->community, "public");
		modifyPIXTraps(nipper, "snmp", "authentication", true);
		modifyPIXTraps(nipper, "snmp", "linkup", true);
		modifyPIXTraps(nipper, "snmp", "linkdown", true);
		modifyPIXTraps(nipper, "snmp", "coldstart", true);
		nipper->pix->snmp->weak = true;
		nipper->pix->snmp->dictionary = true;
		nipper->simplePasswords++;
		nipper->passwordStrengths++;
	}
	if (strcmp("no", command.part[0]) == 0)
	{
		setting = false;
		tempInt = 2;
	}
	else
	{
		setting = true;
		tempInt = 1;
	}

	// Community
	if (strcmp("community", command.part[tempInt]) == 0)
	{
		tempInt++;
		strncpy(nipper->pix->snmp->community, command.part[tempInt], sizeof(nipper->pix->snmp->community) - 1);

		// Check strength / dictionary...
		if (simplePassword(nipper->pix->snmp->community, nipper) == true)
		{
			if (nipper->pix->snmp->dictionary == false)
			{
				nipper->simplePasswords++;
				nipper->pix->snmp->dictionary = true;
			}
		}
		else if (nipper->pix->snmp->dictionary == true)
		{
			nipper->simplePasswords--;
			nipper->pix->snmp->dictionary = false;
		}
		if (passwordStrength(nipper->pix->snmp->community, nipper) == false)
		{
			if (nipper->pix->snmp->weak == false)
			{
				nipper->passwordStrengths++;
				nipper->pix->snmp->weak = true;
			}
		}
		else if (nipper->pix->snmp->weak == true)
		{
			nipper->passwordStrengths--;
			nipper->pix->snmp->weak = false;
		}
	}

	// Contact
	else if (strcmp("contact", command.part[tempInt]) == 0)
	{
		tempInt++;
		strncpy(nipper->pix->snmp->contact, command.part[tempInt], sizeof(nipper->pix->snmp->contact) - 1);
	}

	// Location
	else if (strcmp("location", command.part[tempInt]) == 0)
	{
		tempInt++;
		strncpy(nipper->pix->snmp->location, command.part[tempInt], sizeof(nipper->pix->snmp->location) - 1);
	}

	// Traps...
	else if ((strcmp("enable", command.part[tempInt]) == 0) && (strcmp("traps", command.part[tempInt + 1]) == 0))
	{

		// If no traps are specified...
		if (command.parts == tempInt + 2)
			modifyPIXTraps(nipper, "syslog", "", setting);

		// If only the trap catagory is specified...
		else if (command.parts == tempInt + 3)
			modifyPIXTraps(nipper, command.part[tempInt + 2], "", setting);

		// Do all the other traps...
		else
		{
			tempInt2 = tempInt + 3;
			while (tempInt2 < command.parts)
			{
				modifyPIXTraps(nipper, command.part[tempInt + 2], command.part[tempInt2], setting);
				tempInt2++;
			}
		}
	}

	// Listen Port
	else if (strcmp("port", command.part[tempInt]) == 0)
	{
		tempInt++;
		nipper->pix->snmp->port = atoi(command.part[tempInt]);
	}

	// Server Enable
	else if (strcmp("enable", command.part[tempInt]) == 0)
		nipper->pix->snmp->enabled = setting;

	// SNMP Host
	else if (strcmp("host", command.part[tempInt]) == 0)
	{
		// Reserve Memory...
		if (nipper->pix->snmp->host == 0)
		{
			nipper->pix->snmp->host = malloc(sizeof(struct snmpPIXHost));
			memset(nipper->pix->snmp->host, 0, sizeof(struct snmpPIXHost));
			snmpHostPIXPointer = nipper->pix->snmp->host;
		}
		else
		{
			snmpHostPIXPointer = nipper->pix->snmp->host;
			while (snmpHostPIXPointer->next != 0)
				snmpHostPIXPointer = snmpHostPIXPointer->next;
			snmpHostPIXPointer->next = malloc(sizeof(struct snmpPIXHost));
			memset(snmpHostPIXPointer->next, 0, sizeof(struct snmpPIXHost));
			snmpHostPIXPointer = snmpHostPIXPointer->next;
		}

		// Init...
		snmpHostPIXPointer->port = 161;
		snmpHostPIXPointer->mode = snmp_mode_both;

		// Interface...
		strncpy(snmpHostPIXPointer->interface, command.part[2], sizeof(snmpHostPIXPointer->interface) - 1);

		// Address...
		strncpy(snmpHostPIXPointer->address, command.part[3], sizeof(snmpHostPIXPointer->address) - 1);
		tempInt = 4;

		// Options...
		while (tempInt < command.parts)
		{
			// Poll
			if (strcmp("poll", command.part[tempInt]) == 0)
				snmpHostPIXPointer->mode = snmp_mode_poll;

			// Trap
			else if (strcmp("trap", command.part[tempInt]) == 0)
				snmpHostPIXPointer->mode = snmp_mode_trap;

			// Community
			else if (strcmp("community", command.part[tempInt]) == 0)
			{
				tempInt++;
				strncpy(snmpHostPIXPointer->community, command.part[tempInt], sizeof(snmpHostPIXPointer->community) - 1);
			}

			// Version
			else if (strcmp("version", command.part[tempInt]) == 0)
			{
				tempInt++;
				if ('1' == command.part[tempInt][0])
					snmpHostPIXPointer->version = 1;
				else if ('2' == command.part[tempInt][0])
					snmpHostPIXPointer->version = 2;
			}

			// UDP Port
			else if (strcmp("udp-port", command.part[tempInt]) == 0)
			{
				tempInt++;
				snmpHostPIXPointer->port = atoi(command.part[tempInt]);
			}

			tempInt++;
		}
	}
}


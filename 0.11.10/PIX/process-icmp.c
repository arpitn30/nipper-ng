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


// ICMP Access Structure
struct icmpAccess
{
	int permission;				// perm_permit or perm_deny
	char source[64];
	int sourceType;				// access_type_host...
	char icmpType[16];
	char interface[32];
	struct icmpAccess *next;
};


// Process ICMP
void processICMPPIX(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct ciscoCommand command;
	struct icmpAccess *icmpPIXPointer = 0;
	char tempString[nipper->maxSize];
	int tempInt = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("ICMP Line: %s\n", line);
	}

	// if first
	if (nipper->pix->icmp == 0)
	{
		nipper->pix->icmp = malloc(sizeof(struct icmpAccess));
		icmpPIXPointer = nipper->pix->icmp;
	}
	else
	{
		icmpPIXPointer = nipper->pix->icmp;
		while (icmpPIXPointer->next != 0)
			icmpPIXPointer = icmpPIXPointer->next;
		icmpPIXPointer->next = malloc(sizeof(struct icmpAccess));
		icmpPIXPointer = icmpPIXPointer->next;
	}

	// Init
	command = splitLine(line);
	memset(icmpPIXPointer, 0, sizeof(struct icmpAccess));

	// Permission
	if (strcmp(command.part[1], "permit") == 0)
		icmpPIXPointer->permission = perm_permit;
	else
		icmpPIXPointer->permission = perm_deny;

	// Source
	if (strcmp(command.part[2], "host") == 0)
	{
		icmpPIXPointer->sourceType = object_type_host;
		tempInt = 4;
		strncpy(icmpPIXPointer->source, command.part[3], sizeof(icmpPIXPointer->source) - 1);
	}
	else if (strcmp(command.part[2], "any") == 0)
	{
		icmpPIXPointer->sourceType = object_type_any;
		tempInt = 3;
		strcpy(icmpPIXPointer->source, "any");
	}
	else
	{
		icmpPIXPointer->sourceType = object_type_network;
		tempInt = 4;
		sprintf(tempString, "%s %s", command.part[2], command.part[3]);
		strncpy(icmpPIXPointer->source, tempString, sizeof(icmpPIXPointer->source) - 1);
	}

	// ICMP Type?
	if (command.parts == tempInt + 2)
	{
		strncpy(icmpPIXPointer->icmpType, command.part[tempInt], sizeof(icmpPIXPointer->icmpType) - 1);
		tempInt++;
	}

	// Interface
	strncpy(icmpPIXPointer->interface, command.part[tempInt], sizeof(icmpPIXPointer->interface) - 1);
}


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

// This file contains the code that handles the input processing for this config type


struct ciscoNMPConfig			// Cisco NMP Configuration
{
	// Configuration settings...
	char location[64];
	char contact[64];
	int timeout;
	char coreFile[32];
	char syslogFile[32];
	char password[32];
	char enablePassword[32];
	int cdp;
	int cdpInterval;
	int cdpHoldtime;
	int cdpVersion;
	int portSecurityAuto;
	struct switchNMPConfig *switchConfig;
	struct snmpNMP *snmp;
	struct moduleConfig *module;
	struct permitConfig *permit;
	struct vlanConfig *vlan;
};


struct hostNMP				// NMP Host Struct
{
	char host[32];
	char netMask[16];
	struct hostNMP *next;
};


// Processing NMP includes...
#include "process-general.c"
#include "process-permit.c"
#include "process-port.c"
#include "process-snmp.c"
#include "process-spantree.c"
#include "process-vlan.c"
#include "process-cdp.c"


void processNMPInput(struct nipperConfig *nipper, char *line)
{
	// Variables...
	struct ciscoCommand command;
	int setting = 0;
	int tempInt = 0;

	// Split the command line up
	command = splitLine(line);

	// Init
	if (strcmp(command.part[0], "clear") == 0)
	{
		tempInt = 1;
		setting = false;
	}
	else if (strcmp(command.part[0], "set") == 0)
	{
		tempInt = 1;
		setting = true;
	}
	else
		tempInt = 0;

	// System lines...
	if (strcmp(command.part[tempInt], "system") == 0)
	{
		tempInt++;

		// Hostname
		if (strcmp(command.part[tempInt], "name") == 0)
		{
			if (nipper->debugMode == true)
				printf("Hostname Line: %s\n", line);
			strncpy(nipper->hostname, command.part[tempInt+1], sizeof(nipper->hostname) - 1);
		}

		// Location...
		else if (strcmp(command.part[tempInt], "location") == 0)
		{
			if (nipper->debugMode == true)
				printf("Location Line: %s\n", line);
			tempInt = 20;
			while (line[tempInt] == ' ')
				tempInt++;
			strncpy(nipper->nmp->location, line + tempInt, sizeof(nipper->nmp->location) - 1);
		}

		// Contact...
		else if (strcmp(command.part[tempInt], "contact") == 0)
		{
			if (nipper->debugMode == true)
				printf("Contact Line: %s\n", line);
			tempInt = 19;
			while (line[tempInt] == ' ')
				tempInt++;
			strncpy(nipper->nmp->contact, line + tempInt, sizeof(nipper->nmp->contact) - 1);
		}

		// Corefile...
		else if (strcmp(command.part[tempInt], "core-file") == 0)
		{
			if (nipper->debugMode == true)
				printf("Core-file Line: %s\n", line);
			strncpy(nipper->nmp->coreFile, command.part[tempInt+1], sizeof(nipper->nmp->coreFile) - 1);
		}

		// Syslog file...
		else if (strcmp(command.part[tempInt], "syslog-file") == 0)
		{
			if (nipper->debugMode == true)
				printf("Syslog-file Line: %s\n", line);
			strncpy(nipper->nmp->syslogFile, command.part[tempInt+1], sizeof(nipper->nmp->syslogFile) - 1);
		}

		// Debug (lines not processed)
		else if (nipper->linesnotprocessed == true)
			printf("%s\n", line);
	}

	// IP lines...
	else if (strcmp(command.part[tempInt], "ip") == 0)
	{
		tempInt++;

		// Permit List
		if (strcmp(command.part[tempInt], "permit") == 0)
			processNMPPermit(line, nipper);

		// ICMP IP Unreachables
		else if (strcmp(command.part[tempInt], "unreachable") == 0)
			processNMPUnreachable(line, nipper);

		// IP Redirects
		else if (strcmp(command.part[tempInt], "redirect") == 0)
			processNMPRedirect(line, nipper);

		// IP Fragmentation
		else if (strcmp(command.part[tempInt], "fragmentation") == 0)
			processNMPFragmentation(line, nipper);

		// Debug (lines not processed)
		else if (nipper->linesnotprocessed == true)
			printf("%s\n", line);
	}

	// Version
	else if (strcmp(command.part[tempInt], "#version") == 0)
	{
		if (nipper->debugMode == true)
			printf("Version Line: %s\n", line);
		strncpy(nipper->version, command.part[tempInt+1], sizeof(nipper->version) - 1);
		nipper->versionMajor = atoi(nipper->version);
		nipper->versionMinor = atoi(strchr(nipper->version, '.') + 1);
		nipper->versionRevision = atoi(strchr(nipper->version, '(') + 1);
	}

	// Logout Timeout...
	else if (strcmp(command.part[tempInt], "logout") == 0)
	{
		if (nipper->debugMode == true)
			printf("Logout Line: %s\n", line);
		nipper->nmp->timeout = atoi(command.part[tempInt+1]);
	}

	// Enable Passwords
	else if ((strcmp(command.part[tempInt], "password") == 0) || (strcmp(command.part[tempInt], "enablepass") == 0))
		processEnablePass(line, nipper);

	// CDP...
	else if (strcmp(command.part[tempInt], "cdp") == 0)
		processNMPCDP(line, nipper);

	// SNMP...
	else if (strcmp(command.part[tempInt], "snmp") == 0)
		processNMPSnmp(line, nipper);

	// Ports
	else if (strcmp(command.part[tempInt], "port") == 0)
		processNMPPort(line, nipper);

	// Trunk
	else if (strcmp(command.part[tempInt], "trunk") == 0)
		processNMPTrunk(line, nipper);

	// Spanning Tree
	else if (strcmp(command.part[tempInt], "spantree") == 0)
		processNMPSpantree(line, nipper);

	// VLAN
	else if (strcmp(command.part[tempInt], "vlan") == 0)
		processNMPVlan(line, nipper);

	// Debug (lines not processed)
	else if (nipper->linesnotprocessed == true)
		printf("%s\n", line);
}

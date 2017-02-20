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


struct ciscoCSSConfig			// Cisco CSS Configuration
{
	// Services
	int snmpAccess;				// true (default) or false
	int ftpAccess;				// true (default) or false
	int telnetAccess;			// true (default) or false
	int sshAccess;				// true (default) or false
	int consoleAccess;			// true (default) or false
	int webManagementAccess;	// true or false (default)

	// Device Settings
	int aclEnabled;				// true or false (default)

	// Configuration structures
	struct snmpCSS *snmp;
};


// Processing CSS includes...
#include "process-access-list.c"
#include "process-restrict.c"
#include "process-snmp.c"


void processCSSInput(struct nipperConfig *nipper, char *line)
{
	// Variables...
	struct ciscoCommand command;
	int setting = 0;
	int tempInt = 0;

	// Split the command line up
	command = splitLine(line);

	// Init
	if (strcmp(command.part[0], "no") == 0)
	{
		tempInt = 1;
		setting = false;
	}
	else
	{
		tempInt = 0;
		setting = true;
	}

	// Version
	if ((strcmp(command.part[0], "!Active") == 0) && (strcmp(command.part[1], "version:") == 0))
	{
		if (nipper->debugMode == true)
			printf("Version Line: %s\n", line);
		strncpy(nipper->version, command.part[2] + 2, 2);
		nipper->versionMajor = atoi(nipper->version);
		strncpy(nipper->version, command.part[2] + 4, 2);
		nipper->versionMinor = atoi(nipper->version);
		strncpy(nipper->version, command.part[2] + 6, 3);
		nipper->versionRevision = atoi(nipper->version);
		sprintf(nipper->version, "%d.%d(%d)", nipper->versionMajor, nipper->versionMinor, nipper->versionRevision);
	}

	// Name (Config doesn't include a name, this is a little bit of a hack.)
	else if ((nipper->hostname[0] == 0) && (strncmp(command.part[0] + strlen(command.part[0]) - 1, "#", 1) == 0) && (strncmp(command.part[1], "sh", 2) == 0) && (strncmp(command.part[2], "run", 3) == 0))
	{
		if (nipper->debugMode == true)
			printf("Hostname Line: %s\n", line);
		strncpy(nipper->hostname, command.part[0], sizeof(nipper->hostname) - 1);
		nipper->hostname[strlen(nipper->hostname) - 1] = 0;
	}

	// Restrict
	else if (strcmp(command.part[tempInt], "restrict") == 0)
		processCSSRestrict(line, nipper);

	// SNMP
	else if (strcmp(command.part[tempInt], "snmp") == 0)
		processCSSSNMP(line, nipper);

	// ACL
	else if (strcmp(command.part[tempInt], "acl") == 0)
		processCSSACL(line, nipper);

	// Debug (lines not processed)
	else if (nipper->linesnotprocessed == true)
		printf("%s\n", line);
}

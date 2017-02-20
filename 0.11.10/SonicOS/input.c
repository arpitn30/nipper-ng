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


struct sonicosConfig			// SonicWall SonicOS Configuration
{
	char ipAddress[16];
	char netMask[16];
	char serialNo[18];

	int enhanced;
};


// Processing SonicWall SonicOS includes...
#include "process-rules.c"
#include "process-policy.c"
#include "process-services.c"


void processSonicOSInput(struct nipperConfig *nipper, char *line)
{
	// Variables...
	struct ciscoCommand command;

	// Split the command line up
	command = splitLine(line);

	// Device name...
	if (strcmp(command.part[0], "firewallName") == 0)
	{
		if (nipper->debugMode == true)
			printf("Hostname Line: %s\n", line);
		strncpy(nipper->hostname, line + 13, sizeof(nipper->hostname) - 1);
	}

	// IP address...
	else if (strcmp(command.part[0], "ipAddr") == 0)
	{
		if (nipper->debugMode == true)
			printf("IP Address Line: %s\n", line);
		strncpy(nipper->sonicos->ipAddress, command.part[1], sizeof(nipper->sonicos->ipAddress) - 1);
	}

	// Network Mask...
	else if (strcmp(command.part[0], "ipSubnetMask") == 0)
	{
		if (nipper->debugMode == true)
			printf("IP Net Mask Line: %s\n", line);
		strncpy(nipper->sonicos->netMask, command.part[1], sizeof(nipper->sonicos->netMask) - 1);
	}

	// Serial number...
	else if (strcmp(command.part[0], "serialNumber") == 0)
	{
		if (nipper->debugMode == true)
			printf("Serial Number Line: %s\n", line);
		strncpy(nipper->sonicos->serialNo, command.part[1], sizeof(nipper->sonicos->serialNo) - 1);
	}

	// Firewall Rules...
	else if (strncmp(command.part[0], "prefs_rule", 10) == 0)
		processSonicOSRule(line, nipper);

	// Firewall Policies...
	else if (strncmp(command.part[0], "policy", 6) == 0)
		processSonicOSPolicy(line, nipper);

	// Services...
	else if ((strncmp(command.part[0], "prefs_svc", 9) == 0) || (strncmp(command.part[0], "svcObj", 6) == 0))
		processSonicOSService(line, nipper);

	// Debug (lines not processed)
	else if (nipper->linesnotprocessed == true)
		printf("%s\n", line);
}

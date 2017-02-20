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


struct ciscoPIXConfig		// Cisco PIX configuration
{
	// Counters
	int oldAccessList;
	int standardAccessList;
	int extendedAccessList;
	int interfaceAccessList;

	// Configuration settings...
	char password[32];
	int transparent;						// Transparent Firewall (true or false)
	int accessListAlertInterval;
	int accessListDenyFlowMax;
	int floodguard;

	// Configuration structures...
	struct enablePIXPassword *enable;		// Enable Passwords
	struct httpPIXConfig *http;				// HTTP
	struct interfacePIXConfig *interface;	// Interfaces
	struct sshPIXConfig *ssh;				// SSH Configuration
	struct usernamePIX *username;			// Users
	struct fixupList *fixup;				// Protocol Analysis
	struct icmpAccess *icmp;				// ICMP to interfaces
	struct staticPIX *staticNAT;			// Static NAT
	struct staticPIX *staticPAT;			// Static PAT
	struct routePIX *route;					// Static Routes
	struct snmpPIXConfig *snmp;				// SNMP
};


// Processing PIX includes...
#include "process-access-list.c"
#include "process-enable.c"
#include "process-general.c"
#include "process-http.c"
#include "process-icmp.c"
#include "process-interface.c"
#include "process-nat.c"
#include "process-objects.c"
#include "process-protocols.c"
#include "process-route.c"
#include "process-snmp.c"
#include "process-ssh.c"


void processPIXInput(struct nipperConfig *nipper, char *line)
{
	// Variables...
	struct ciscoCommand command;
	int tempInt = 0;
	int setting = 0;

	// Split the command line up
	command = splitLine(line);

	// No?
	if (strcmp(command.part[0], "no") == 0)
	{
		setting = false;
		tempInt = 1;
	}
	else
	{
		setting = true;
		tempInt = 0;
	}

	// Hostname
	if (strcmp(command.part[0], "hostname") == 0)
	{
		if (nipper->debugMode == true)
			printf("Hostname Line: %s\n", line);
		strncpy(nipper->hostname, command.part[1], sizeof(nipper->hostname) - 1);
	}

	// Version
	else if (((strcmp(command.part[0], "PIX") == 0) || (strcmp(command.part[0], "ASA") == 0) || (strcmp(command.part[0], "FWSM") == 0)) && (strcmp(command.part[1], "Version") == 0))
	{
		if (nipper->debugMode == true)
			printf("Version Line: %s\n", line);
		strncpy(nipper->version, command.part[2], sizeof(nipper->version) - 1);
		nipper->versionMajor = atoi(nipper->version);
		if (strchr(nipper->version, '.') != 0)
			nipper->versionMinor = atoi(strchr(nipper->version, '.') + 1);
		if (strchr(nipper->version, '(') != 0)
			nipper->versionRevision = atoi(strchr(nipper->version, '(') + 1);
		if (strcmp(command.part[0], "PIX") == 0)
			nipper->deviceType = type_pix_firewall;
		else if (strcmp(command.part[0], "ASA") == 0)
			nipper->deviceType = type_asa_firewall;
		else if (strcmp(command.part[0], "FWSM") == 0)
			nipper->deviceType = type_fwsm_firewall;
	}

	// Flood Guard
	else if (strcmp(command.part[tempInt], "floodguard") == 0)
	{
		if (strcmp(command.part[1], "enable") == 0)
			nipper->pix->floodguard = true;
		else if (strcmp(command.part[1], "disable") == 0)
			nipper->pix->floodguard = false;
		else if (strcmp(command.part[tempInt + 1], "enable") == 0)
			nipper->pix->floodguard = setting;
	}

	// IP
	else if (strcmp(command.part[tempInt], "ip") == 0)
	{
		tempInt++;

		// Address
		if (strcmp(command.part[tempInt], "address") == 0)
			processPIXInterface(line, nipper);

		// uRFP
		else if ((strcmp(command.part[tempInt], "verify") == 0) && (strcmp(command.part[tempInt + 1], "reverse-path") == 0) && (strcmp(command.part[tempInt + 2], "interface") == 0))
			processPIXuRPF(line, nipper);
	}

	// Transparent Firewall?
	else if ((strcmp(command.part[0], "firewall") == 0) && (strcmp(command.part[1], "transparent") == 0))
	{
		if (nipper->debugMode == true)
			printf("Transparent Line: %s\n", line);
		nipper->pix->transparent = true;
	}

	// ICMP Access...
	else if (strcmp(command.part[tempInt], "icmp") == 0)
		processICMPPIX(line, nipper);

	// Enable Password
	else if (((strcmp(command.part[tempInt], "enable") == 0) && (strcmp(command.part[tempInt + 1], "password") == 0)) || (strcmp(command.part[tempInt], "passwd") == 0))
		processEnablePIX(line, nipper);

	// Usernames...
	else if ((strcmp(command.part[tempInt], "username") == 0) && (strcmp(command.part[tempInt+2], "password") == 0))
		processPIXUsername(line, nipper);

	// Route...
	else if (strcmp(command.part[tempInt], "route") == 0)
		processRoutePIX(line, nipper);

	// Interfaces...
	else if ((strcmp(command.part[tempInt], "interface") == 0) || (strcmp(command.part[tempInt], "nameif") == 0) || (strcmp(command.part[tempInt], "access-group") == 0))
		processPIXInterface(line, nipper);

	// Object Group...
	else if (strcmp(command.part[tempInt], "object-group") == 0)
		processObjectGroup(line, nipper);

	// Protocol Inspection...
	else if ((strcmp(command.part[tempInt], "fixup") == 0) && (strcmp(command.part[tempInt + 1], "protocol") == 0))
		processFixupPIX(line, nipper);

	// Name...
	else if (strcmp(command.part[tempInt], "name") == 0)
		processPIXName(line, nipper);

	// Domain Name
	else if (strcmp(command.part[tempInt], "domain-name") == 0)
		strncpy(nipper->domainName, line + 12, sizeof(nipper->domainName) - 1);

	// Access Lists...
	else if (strcmp(command.part[tempInt], "access-list") == 0)
		processPIXAccessList(line, nipper);

	// Static NAT / PAT
	else if (strcmp(command.part[tempInt], "static") == 0)
		processStaticPIX(line, nipper);

	// SNMP
	else if (strcmp(command.part[tempInt], "snmp-server") == 0)
		processSnmpPIX(line, nipper);

	// SSH
	else if (strcmp(command.part[tempInt], "ssh") == 0)
		processPIXSSH(line, nipper);

	// HTTP
	else if ((strcmp(command.part[tempInt], "http") == 0) && (strcmp(command.part[tempInt + 1], "server") == 0) && (strcmp(command.part[tempInt + 2], "enable") == 0))
		processPIXHTTP(line, nipper);

	// Debug (lines not processed)
	else if (nipper->linesnotprocessed == true)
		printf("%s\n", line);
}

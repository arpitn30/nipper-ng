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


struct screenOSConfig					// Juniper ScreenOS Configuration
{
	struct adminSOS *admin;				// Admin settings
	struct authServerSOS *authServer;	// Authentication settings
	struct interfaceSOS *interface;		// Interfaces
	struct snmpSOS *snmp;				// SNMP Settings
	struct zoneSOS *zone;				// Zone Settings
	struct adminUsersSOS *users;		// Administrative users

	// General
	int defaultFirewallMode;			// The default mode is to deny everything

	// SSH Settings
	int sshVersion;						// SSH Server Protocol Version
	int sshEnabled;						// SSH Server Enabled/Disabled true or false
	int sshKeyGenTime;					// Mins for Key Gen - SSH V1 Only
	char sshPublicKey[128];				// Public Key - SSH v2 Only
	
	// Admin Settings
	int accessAttempts;					// Login attempts allowed
	int mailAlert;						// Mail admin alerts
	int authTimeout;					// Connection timeout
	char authenticationServer[64];				// Authentication server
	int adminFormat;					// Format of config file (default, dos or unix)
	int httpRedirect;					// Redirect Admin HTTP traffic to HTTPS
	char email[64];						// Admin email address
	char email1[64];					// Admin additional email address
	char email2[64];					// Admin additional email address
	char emailServer[32];				// Email Server Name
	char name[32];						// Admin username
	char password[32];					// Admin password
	int restrictLength;					// Restrict Minimum Password Length (Between 1 and 31)
	int privilege;						// Admin privilege (default, read-write or get external)
	char adminIP[16];					// Administration IP address (default 0.0.0.0)
	char adminNetMask[16];				// Administration Netmask (default 255.255.255.255)
	int consoleOnly;					// Restrict admin access to only the console
	int nameMappings;					// Set to true if address name mappings exist
	int nameGroupMappings;				// Set to true if group address name mappings exist

	// Zone Settings
	int asymmetricVPN;					// Allow multiple paths for VPN traffic
};


struct listSOS				// NetScreenOS List
{
	char name[32];
	struct listSOS *next;
};


// Processing ScreenOS includes...
#include "process-address.c"
#include "process-admin.c"
#include "process-auth-server.c"
#include "process-interface.c"
#include "process-policy.c"
#include "process-snmp.c"
#include "process-ssh.c"
#include "process-zone.c"


void processSOSInput(struct nipperConfig *nipper, char *line)
{
	// Variables...
	struct ciscoCommand command;

	// Split the command line up
	command = splitLine(line);

	if ((strcasecmp(command.part[0], "set") == 0) || (strcasecmp(command.part[0], "unset") == 0))
	{
		// Hostname
		if (strcasecmp(command.part[1], "hostname") == 0)
		{
			if (nipper->debugMode == true)
				printf("Hostname Line: %s\n", line);
			stripQuotes(command.part[2], nipper->hostname, sizeof(nipper->hostname));
		}

		// Admin
		else if (strcasecmp(command.part[1], "admin") == 0)
			processSOSAdmin(line, nipper);

		// Auth Server
		else if (strcasecmp(command.part[1], "auth-server") == 0)
			processSOSAuthServer(line, nipper);

		// Addresses
		else if (strcasecmp(command.part[1], "address") == 0)
			processSOSAddress(line, nipper);

		// Group Addresses
		else if ((strcasecmp(command.part[1], "group") == 0) && (strcasecmp(command.part[2], "address") == 0))
			processSOSGroupAddress(line, nipper);

		// Interface
		else if (strcasecmp(command.part[1], "interface") == 0)
			processSOSInterface(line, nipper);

		// Policy Default Permit All
		else if ((strcasecmp(command.part[1], "policy") == 0) && (strcasecmp(command.part[2], "default-permit-all") == 0))
		{
			if (nipper->debugMode == true)
				printf("Default Policy Line: %s\n", line);
			nipper->sos->defaultFirewallMode = false;
		}

		// Policy
		else if (strcasecmp(command.part[1], "policy") == 0)
			processSOSPolicy(line, nipper);

		// SSH
		else if (strcasecmp(command.part[1], "ssh") == 0)
			processSOSSSH(line, nipper);

		// SNMP
		else if (strcasecmp(command.part[1], "snmp") == 0)
			processSOSSNMP(line, nipper);

		// Zones
		else if (strcasecmp(command.part[1], "zone") == 0)
			processSOSZone(line, nipper);

		// Debug (lines not processed)
		else if (nipper->linesnotprocessed == true)
			printf("%s\n", line);
	}
}

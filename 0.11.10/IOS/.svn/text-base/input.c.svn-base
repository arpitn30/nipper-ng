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


struct ciscoIOSConfig					// Cisco IOS configuration
{
	// Configuration settings...
	int sourceRouting;					// true or false
	int tcpSmallServers;				// true, false, unconfigured
	int udpSmallServers;				// true, false, unconfigured
	int finger;							// true, false, unconfigured
	int cdp;							// true or false
	int cef;							// true or false
	int bootp;							// true or false
	int servicePasswordEncryption;		// true or false
	int bootNetwork;					// true or false
	int serviceConfig;					// true or false
	int pad;							// true or false
	int domainLookup;					// true or false
	int classlessRouting;				// true or false
	int keepAlivesIn;					// true or false
	int keepAlivesOut;					// true or false
	int gratuitousArps;					// true or false
	int calendarValid;					// true (default) or false
	char summerTimeZone[8];				// Empty is disabled
	char timeZone[8];					// default (UTC)
	int timeOffsetHours;
	int timeOffsetMins;
	int passwordMinLength;				// 6 is default on IOS 12.3(1)+, otherwise it doesn't exist
	int vtpMode;						// vtp_mode_server (default)...
	char vtpDomain[34];					// VTP Domain
	struct host *dns;					// DNS Servers
	struct ntpConfig *ntp;				// NTP
	struct enablePassword *enable;		// Enable Passwords
	struct snmpConfig *snmp;			// SNMP
	struct ftpConfig *ftp;				// FTP
	struct usernameList *username;		// Users
	struct privilageLevels *privilage;	// Privilege Levels
	struct loggingConfig *logging;		// Logging
	struct tacacsConfig *tacacs;		// TACACS
	struct aaaConfig *aaa;				// AAA
	struct httpConfig *http;			// HTTP
	struct sshConfig *ssh;				// SSH
	struct interfaceConfig *interface;	// Interfaces
	struct routeMapConfig *routeMap;	// Routing - Route Maps
	struct staticRoute *route;			// Routing - Static
	struct ripConfig *rip;				// Routing - RIP
	struct ospfConfig *ospf;			// Routing - OSPF
	struct eigrpConfig *eigrp;			// Routing - EIGRP
	struct isisConfig *isis;			// Routing - ISIS
	struct bgpConfig *bgp;				// Routing - BGP
	struct keyChain *chain;				// Key Chain
	struct lineConfig *line;			// Local / Remote Administration Lines
	struct bannerConfig *banner;		// Logon Banner
	struct natConfig *nat;				// NAT
};


struct netInterface					// Interfaces
{
	char interface[32];
	struct netInterface *next;
};


#define vtp_mode_server 0
#define vtp_mode_client 1
#define vtp_mode_transparent 2
#define vtp_mode_none 3


// Processing IOS includes...
#include "process-aaa.c"
#include "process-access-list.c"
#include "process-banner.c"
#include "process-cef.c"
#include "process-clock.c"
#include "process-dns.c"
#include "process-enable.c"
#include "process-ftp.c"
#include "process-general.c"
#include "process-http.c"
#include "process-interface.c"
#include "process-keychain.c"
#include "process-line.c"
#include "process-logging.c"
#include "process-nat.c"
#include "process-ntp.c"
#include "process-route-map.c"
#include "process-router.c"
#include "process-snmp.c"
#include "process-ssh.c"
#include "process-tacacs.c"
#include "process-username.c"
#include "process-vtp.c"


void processIOSInput(struct nipperConfig *nipper, char *line)
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

	if (strncmp("!", line, 1) == 0)
	{ }

	// Hostname
	else if (strcmp(command.part[tempInt], "hostname") == 0)
	{
		if (nipper->debugMode == true)
			printf("Hostname Line: %s\n", line);
		strncpy(nipper->hostname, command.part[tempInt+1], sizeof(nipper->hostname) - 1);
	}

	// Version
	else if (strcmp(command.part[tempInt], "version") == 0)
	{
		if (nipper->debugMode == true)
			printf("Version Line: %s\n", line);
		strncpy(nipper->version, command.part[tempInt+1], sizeof(nipper->version) - 1);
		nipper->versionMajor = atoi(nipper->version);
		if (strchr(nipper->version, '.') != 0)
			nipper->versionMinor = atoi(strchr(nipper->version, '.') + 1);
	}

	// Service lines...
	else if (strcmp(command.part[tempInt], "service") == 0)
	{
		tempInt++;

		// Service Password Encryption...
		if (strcmp(command.part[tempInt], "password-encryption") == 0)
		{
			if (nipper->debugMode == true)
				printf("Service Password-Encryption Line: %s\n", line);
			nipper->ios->servicePasswordEncryption = setting;
		}

		// TCP keep alives in
		else if (strcmp(command.part[tempInt], "tcp-keepalives-in") == 0)
		{
			if (nipper->debugMode == true)
				printf("TCP Keep Alives In Line: %s\n", line);
			nipper->ios->keepAlivesIn = setting;
		}

		// TCP keep alives out
		else if (strcmp(command.part[tempInt], "tcp-keepalives-out") == 0)
		{
			if (nipper->debugMode == true)
				printf("TCP Keep Alives Out Line: %s\n", line);
			nipper->ios->keepAlivesOut = setting;
		}

		// Service Config
		else if (strcmp(command.part[tempInt], "config") == 0)
			processServiceConfig(line, nipper);

		// PAD Service...
		else if (strcmp(command.part[tempInt], "pad") == 0)
		{
			if (nipper->debugMode == true)
				printf("PAD Line: %s\n", line);
			nipper->ios->pad = setting;
		}

		// TCP Small Servers...
		else if (strcmp(command.part[tempInt], "tcp-small-servers") == 0)
			processSmallServers(line, nipper);

		// UDP Small Servers...
		else if (strcmp(command.part[tempInt], "udp-small-servers") == 0)
			processSmallServers(line, nipper);

		// Finger...
		else if (strcmp(command.part[tempInt], "finger") == 0)
		{
			if (nipper->debugMode == true)
				printf("Finger Line: %s\n", line);
			nipper->ios->finger = setting;
		}

		// Debug (lines not processed)
		else if (nipper->linesnotprocessed == true)
			printf("%s\n", line);
	}

	// IP lines...
	else if (strcmp(command.part[tempInt], "ip") == 0)
	{
		tempInt++;

		// Cisco Express Forwarding
		if (strcmp(command.part[tempInt], "cef") == 0)
			processCEF(line, nipper);

		// IP Classless Routing
		else if (strcmp(command.part[tempInt], "classless") == 0)
		{
			if (nipper->debugMode == true)
				printf("Classless Routing Line: %s\n", line);
			nipper->ios->classlessRouting = setting;
		}

		// Access Lists...
		else if (strcmp(command.part[tempInt], "access-list") == 0)
			processIPAccessList(line, nipper);

		// Gratuitous ARPs
		else if (strcmp(command.part[tempInt], "gratuitous-arps") == 0)
		{
			if (nipper->debugMode == true)
				printf("Gratuitous ARPs Line: %s\n", line);
			nipper->ios->gratuitousArps = setting;
		}

		// SSH
		else if (strcmp(command.part[tempInt], "ssh") == 0)
			processSsh(line, nipper);

		// Name Servers
		else if (strcmp(command.part[tempInt], "name-server") == 0)
			processNameServer(line, nipper);

		// Domain Name
		else if (strcmp(command.part[tempInt], "domain-name") == 0)
		{
			if (nipper->debugMode == true)
				printf("Domain Name Line: %s\n", line);
			strncpy(nipper->domainName, command.part[tempInt+1], sizeof(nipper->domainName) - 1);
		}
		else if ((strcmp(command.part[tempInt], "domain") == 0) && (strcmp(command.part[tempInt+1], "name") == 0))
		{
			if (nipper->debugMode == true)
				printf("Domain Name Line: %s\n", line);
			strncpy(nipper->domainName, command.part[tempInt+2], sizeof(nipper->domainName) - 1);
		}

		// Domain Lookup
		else if ((strcmp(command.part[tempInt], "domain-lookup") == 0) || ((strcmp(command.part[tempInt], "domain") == 0) && (strcmp(command.part[tempInt+1], "lookup") == 0)))
			processDomainLookup(line, nipper);

		// Source routing...
		else if (strcmp(command.part[tempInt], "source-route") == 0)
		{
			if (nipper->debugMode == true)
				printf("IP Source Route Line: %s\n", line);
			nipper->ios->sourceRouting = setting;
		}

		// Bootp...
		else if ((strcmp(command.part[tempInt], "bootp") == 0) && (strcmp(command.part[tempInt+1], "server") == 0))
			processBootp(line, nipper);

		// HTTP...
		else if (strcmp(command.part[tempInt], "http") == 0)
			processHttp(line, nipper);

		// FTP username / password...
		else if (strcmp(command.part[tempInt], "ftp") == 0)
			processFtp(line, nipper);

		// IP Route...
		else if ((strcmp(command.part[tempInt], "route") == 0) && (strcmp(command.part[tempInt+1], "vrf") != 0))
			processRoute(line, nipper);

		// IP NAT...
		else if (strcmp(command.part[tempInt], "nat") == 0)
			processNAT(line, nipper);

		// Debug (lines not processed)
		else if (nipper->linesnotprocessed == true)
			printf("%s\n", line);
	}

	// Security
	else if (strcmp(command.part[tempInt], "security") == 0)
	{
		tempInt++;

		// Passwords Minimum Length
		if ((strcmp(command.part[tempInt], "passwords") == 0) && (strcmp(command.part[tempInt+1], "min-length") == 0))
		{
			if (nipper->debugMode == true)
				printf("Password Length Line: %s\n", line);
			if (setting == false)
				nipper->ios->passwordMinLength = 0;
			else
				nipper->ios->passwordMinLength = atoi(command.part[tempInt+2]);
		}

		// Debug (lines not processed)
		else if (nipper->linesnotprocessed == true)
			printf("%s\n", line);
	}

	// Enable Passwords
	else if (strcmp(command.part[tempInt], "enable") == 0)
		processEnable(line, nipper);

	// Usernames...
	else if (strcmp(command.part[tempInt], "username") == 0)
		processUsername(line, nipper);

	// Interfaces
	else if (strcmp(command.part[tempInt], "interface") == 0)
		processInterface(line, nipper);

	// Banner...
	else if (strcmp(command.part[tempInt], "banner") == 0)
		processBanner(line, nipper);

	// CDP...
	else if ((strcmp(command.part[tempInt], "cdp") == 0) && (strcmp(command.part[tempInt+1], "run") == 0))
	{
		if (nipper->debugMode == true)
			printf("CDP Line: %s\n", line);
		nipper->ios->cdp = setting;
	}

	// Access Lists...
	else if (strcmp(command.part[tempInt], "access-list") == 0)
		processAccessList(line, nipper);

	// Line...
	else if (strcmp(command.part[tempInt], "line") == 0)
		processLine(line, nipper);

	// VTP...
	else if (strcmp(command.part[tempInt], "vtp") == 0)
		processVTP(line, nipper);

	// Key chain...
	else if ((strcmp(command.part[tempInt], "key") == 0) && (strcmp(command.part[tempInt+1], "chain") == 0))
		processKeyChain(line, nipper);

	// Routing...
	else if (strcmp(command.part[tempInt], "router") == 0)
		processRouter(line, nipper);

	// Route Map...
	else if (strcmp(command.part[tempInt], "route-map") == 0)
		processRouteMap(line, nipper);

	// TACACS...
	else if (strcmp(command.part[tempInt], "tacacs-server") == 0)
		processTacacs(line, nipper);

	// AAA...
	else if (strcmp(command.part[tempInt], "aaa") == 0)
		processAaa(line, nipper);

	// NTP...
	else if (strcmp(command.part[tempInt], "ntp") == 0)
		processNtp(line, nipper);

	// Privilage Levels...
	else if ((strcmp(command.part[tempInt], "privilage") == 0) && (strcmp(command.part[tempInt+1], "exec") == 0) && (strcmp(command.part[tempInt+2], "level") == 0))
		processPrivilage(line, nipper);

	// SNMP...
	else if (strcmp(command.part[tempInt], "snmp-server") == 0)
		processSnmp(line, nipper);

	// Logging...
	else if (strcmp(command.part[tempInt], "logging") == 0)
		processLogging(line, nipper);

	// Clock...
	else if (strcmp(command.part[tempInt], "clock") == 0)
		processClock(line, nipper);

	// Boot Network
	else if ((strcmp(command.part[tempInt], "boot") == 0) && (strcmp(command.part[tempInt+1], "network") == 0))
		processBootNetwork(line, nipper);

	// Debug (lines not processed)
	else if (nipper->linesnotprocessed == true)
		printf("%s\n", line);
}

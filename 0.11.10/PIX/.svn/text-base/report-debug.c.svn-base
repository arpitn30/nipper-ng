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


void reportPIXDebug(struct nipperConfig *nipper)
{
	// Variables
	struct johnPassword *johnPointer = 0;
	struct interfacePIXConfig *interfacePIXPointer = 0;
	struct enablePIXPassword *enablePIXPointer = 0;
	struct usernamePIX *usernamePIXPointer = 0;
	struct fixupList *fixupPIXPointer = 0;
	struct icmpAccess *icmpPIXPointer = 0;
	struct staticPIX *staticPIXPointer = 0;
	struct routePIX *routePIXPointer = 0;
	struct snmpPIXHost *snmpHostPIXPointer = 0;
	struct snmpTrapPIX *trapPIXPointer = 0;
	struct mgmtHostsPIX *mgmtHostsPointer = 0;
	struct sshAccessConfig *sshPointer = 0;

	// Setting info
	printf("\n\nFor some debug settings...\n");
	printf("  True or Enabled = %d\n", true);
	printf("  False or Disabled = %d\n", false);
	printf("  Unconfigured = %d\n\n", unconfigured);

	// General Info
	printf("\n%sInformation Collected\n=====================%s\n", COL_BLUE, RESET);
	printf("Hostname: %s\n", nipper->hostname);
	printf("Domain Name: %s\n", nipper->domainName);
	printf("Version: %s\n", nipper->version);
	printf("Version: %d.%d(%d)\n", nipper->versionMajor, nipper->versionMinor, nipper->versionRevision);
	printf("Type: %d\n", nipper->deviceType);
	printf("Transparent: %d\n", nipper->pix->transparent);
	printf("Floodguard: %d\n", nipper->pix->floodguard);

	// HTTP Server
	if (nipper->pix->http != 0)
	{
		printf("HTTPS Server: %d\n", nipper->pix->http->httpServer);
		printf("HTTPS Server Port: %d\n", nipper->pix->http->httpServerPort);
		printf("Require Certificate: %d\n", nipper->pix->http->requireCert);
		printf("HTTP Redirect: %d\n", nipper->pix->http->httpRedirect);
		printf("HTTP Redirect Port: %d\n", nipper->pix->http->httpRedirectPort);
		mgmtHostsPointer = nipper->pix->http->host;
		while (mgmtHostsPointer != 0)
		{
			printf("HTTP Management Host:\n");
			printf("  IP Address: %s\n", mgmtHostsPointer->ipAddress);
			printf("  Net Mask: %s\n", mgmtHostsPointer->netMask);
			printf("  Interface: %s\n", mgmtHostsPointer->interface);
			mgmtHostsPointer = mgmtHostsPointer->next;
		}
	}

	// Users and Passwords
	printf("Password: %s\n", nipper->pix->password);
	enablePIXPointer = nipper->pix->enable;
	while (enablePIXPointer != 0)
	{
		printf("Enable Password: %s\n", enablePIXPointer->passwordEncrypted);
		printf("  Enable Level: %d\n", enablePIXPointer->level);
		enablePIXPointer = enablePIXPointer->next;
	}
	usernamePIXPointer = nipper->pix->username;
	while (usernamePIXPointer != 0)
	{
		printf("Username: %s\n", usernamePIXPointer->username);
		printf("  Encrypted Password: %s\n", usernamePIXPointer->passwordEncrypted);
		printf("  Encryption: %d\n", usernamePIXPointer->encryption);
		printf("  Level: %d\n", usernamePIXPointer->level);
		usernamePIXPointer = usernamePIXPointer->next;
	}

	// SSH
	if (nipper->pix->ssh != 0)
	{
		printf("SSH Config:\n");
		printf("  SSH Version: %d\n", nipper->pix->ssh->version);
		printf("  Timeout: %d\n", nipper->pix->ssh->timeout);
		sshPointer = nipper->pix->ssh->access;
		while (sshPointer != 0)
		{
			printf("  IP Address: %s\n", sshPointer->ipAddress);
			printf("  Net Mask: %s\n", sshPointer->netMask);
			printf("  Interface: %s\n", sshPointer->interface);
			sshPointer = sshPointer->next;
		}
	}

	// SNMP
	if (nipper->pix->snmp != 0)
	{
		printf("SNMP Config:\n");
		printf("  Enabled: %d\n", nipper->pix->snmp->enabled);
		printf("  Community: %s\n", nipper->pix->snmp->community);
		printf("  Contact: %s\n", nipper->pix->snmp->contact);
		printf("  Location: %s\n", nipper->pix->snmp->location);
		printf("  Port: %d\n", nipper->pix->snmp->port);
		snmpHostPIXPointer = nipper->pix->snmp->host;
		while (snmpHostPIXPointer != 0)
		{
			printf("  SNMP Host:\n");
			printf("    Interface: %s\n", snmpHostPIXPointer->interface);
			printf("    Address: %s\n", snmpHostPIXPointer->address);
			printf("    Community: %s\n", snmpHostPIXPointer->community);
			printf("    Mode: %d\n", snmpHostPIXPointer->mode);
			printf("    UDP Port: %d\n", snmpHostPIXPointer->port);
			printf("    SNMP Version: %d\n", snmpHostPIXPointer->version);
			snmpHostPIXPointer = snmpHostPIXPointer->next;
		}
		trapPIXPointer = nipper->pix->snmp->trap;
		while (trapPIXPointer != 0)
		{
			printf("  SNMP Trap:\n");
			printf("    Trap Type: %s\n", trapPIXPointer->section);
			printf("    Trap: %s\n", trapPIXPointer->trap);
			trapPIXPointer = trapPIXPointer->next;
		}
	}

	// Interfaces
	interfacePIXPointer = nipper->pix->interface;
	while (interfacePIXPointer != 0)
	{
		printf("Interface: %s\n", interfacePIXPointer->interface);
		printf("  Name: %s\n", interfacePIXPointer->name);
		printf("  Shutdown: %d\n", interfacePIXPointer->shutdown);
		printf("  IP Address: %s\n", interfacePIXPointer->ipAddress);
		printf("  IP Mask: %s\n", interfacePIXPointer->netMask);
		printf("  Security: %d\n", interfacePIXPointer->security);
		printf("  uRPF: %d\n", interfacePIXPointer->uRPF);
		printf("  In ACL: %s\n", interfacePIXPointer->in);
		printf("  In Override: %d\n", interfacePIXPointer->inOverride);
		printf("  Out ACL: %s\n", interfacePIXPointer->out);
		printf("  Out Override: %d\n", interfacePIXPointer->outOverride);
		interfacePIXPointer = interfacePIXPointer->next;
	}

	// ICMP Access
	icmpPIXPointer = nipper->pix->icmp;
	while (icmpPIXPointer != 0)
	{
		printf("ICMP Access: %d\n", icmpPIXPointer->permission);
		printf("  Source: %s\n", icmpPIXPointer->source);
		printf("  Source Type: %d\n", icmpPIXPointer->sourceType);
		printf("  ICMP Type: %s\n", icmpPIXPointer->icmpType);
		printf("  Interface: %s\n", icmpPIXPointer->interface);
		icmpPIXPointer = icmpPIXPointer->next;
	}

	// Protocol Analysis
	fixupPIXPointer = nipper->pix->fixup;
	while (fixupPIXPointer != 0)
	{
		printf("Fixup Protocol: %s\n", fixupPIXPointer->protocol);
		printf("  Fixup Options: %s\n", fixupPIXPointer->options);
		printf("  Enabled: %d\n", fixupPIXPointer->enabled);
		fixupPIXPointer = fixupPIXPointer->next;
	}

	// Static NAT / PAT
	staticPIXPointer = nipper->pix->staticNAT;
	while (staticPIXPointer != 0)
	{
		printf("Static NAT Configuration\n");
		printf("  Real Interface: %s\n", staticPIXPointer->interfaceReal);
		printf("  Mapped Interface: %s\n", staticPIXPointer->interfaceMapped);
		printf("  Mapped IP: %s\n", staticPIXPointer->ipMapped);
		printf("  Real IP: %s\n", staticPIXPointer->ipReal);
		printf("  Real IP Mask: %s\n", staticPIXPointer->ipNetMaskReal);
		printf("  Access List: %s\n", staticPIXPointer->accessList);
		printf("  Interface: %d\n", staticPIXPointer->interface);
		printf("  DNS: %d\n", staticPIXPointer->dns);
		printf("  Nailed: %d\n", staticPIXPointer->nailed);
		printf("  Random Sequence Numbers: %d\n", staticPIXPointer->randomseq);
		printf("  Max TCP Connections: %d\n", staticPIXPointer->tcpMaxConnections);
		printf("  Max UDP Connections: %d\n", staticPIXPointer->udpMaxConnections);
		printf("  Max Embrionic Connections: %d\n", staticPIXPointer->embrionicConnections);
		staticPIXPointer = staticPIXPointer->next;
	}
	staticPIXPointer = nipper->pix->staticPAT;
	while (staticPIXPointer != 0)
	{
		printf("Static PAT Configuration\n");
		printf("  Real Interface: %s\n", staticPIXPointer->interfaceReal);
		printf("  Mapped Interface: %s\n", staticPIXPointer->interfaceMapped);
		printf("  TCP Protocol: %d\n", staticPIXPointer->protocolTcp);
		printf("  Mapped IP: %s\n", staticPIXPointer->ipMapped);
		printf("  Mapped Port: %s\n", staticPIXPointer->portMapped);
		printf("  Real IP: %s\n", staticPIXPointer->ipReal);
		printf("  Real Port: %s\n", staticPIXPointer->portReal);
		printf("  Real IP Mask: %s\n", staticPIXPointer->ipNetMaskReal);
		printf("  Access List: %s\n", staticPIXPointer->accessList);
		printf("  Interface: %d\n", staticPIXPointer->interface);
		printf("  DNS: %d\n", staticPIXPointer->dns);
		printf("  Nailed: %d\n", staticPIXPointer->nailed);
		printf("  Random Sequence Numbers: %d\n", staticPIXPointer->randomseq);
		printf("  Max TCP Connections: %d\n", staticPIXPointer->tcpMaxConnections);
		printf("  Max UDP Connections: %d\n", staticPIXPointer->udpMaxConnections);
		printf("  Max Embrionic Connections: %d\n", staticPIXPointer->embrionicConnections);
		staticPIXPointer = staticPIXPointer->next;
	}

	// Static Route
	routePIXPointer = nipper->pix->route;
	while (routePIXPointer != 0)
	{
		printf("Static Route\n");
		printf("  Interface: %s\n", routePIXPointer->interface);
		printf("  IP Address: %s\n", routePIXPointer->ipAddress);
		printf("  Net Mask: %s\n", routePIXPointer->netMask);
		printf("  Gateway: %s\n", routePIXPointer->gateway);
		printf("  Metric: %d\n", routePIXPointer->metric);
		printf("  Track: %d\n", routePIXPointer->track);
		printf("  Tunneled: %d\n", routePIXPointer->tunneled);
		routePIXPointer = routePIXPointer->next;
	}

	// Filter Rules...
	reportRulesDebug(nipper);

	// Name Mappings / Objects
	reportObjectsDebug(nipper);

	// John-the-ripper
	if (nipper->john != 0)
	{
		printf("\n%sJohn-the-ripper Output\n======================%s\n", COL_BLUE, RESET);
		johnPointer = nipper->john;
		while (johnPointer != 0)
		{
			printf("Username: %s\n", johnPointer->username);
			printf("  Password: %s\n", johnPointer->password);
			johnPointer = johnPointer->next;
		}
	}
}



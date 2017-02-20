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


void reportNMPDebug(struct nipperConfig *nipper)
{
	// Variables
	struct johnPassword *johnPointer = 0;
	struct snmpNMPCommunity *communityNMPPointer = 0;
	struct snmpNMPHost *snmpNMPHostPointer = 0;
	struct snmpTrap *snmpTrapPointer = 0;
	struct hostNMP *hostNMPPointer = 0;
	struct vlanConfig *vlanNMPPointer = 0;
	struct moduleConfig *moduleNMPPointer = 0;
	struct portConfig *portNMPPointer = 0;

	// Setting info
	printf("\n\nFor some debug settings...\n");
	printf("  True or Enabled = %d\n", true);
	printf("  False or Disabled = %d\n", false);
	printf("  Unconfigured = %d\n\n", unconfigured);

	// General Info
	printf("\n%sInformation Collected\n=====================%s\n", COL_BLUE, RESET);
	printf("Hostname: %s\n", nipper->hostname);
	printf("NMP Version: %s\n", nipper->version);
	printf("NMP Version: %d.%d(%d)\n", nipper->versionMajor, nipper->versionMinor, nipper->versionRevision);
	printf("Location: %s\n", nipper->nmp->location);
	printf("Contact: %s\n", nipper->nmp->contact);
	printf("Idle Session Timeout: %d\n", nipper->nmp->timeout);
	printf("Core File: %s\n", nipper->nmp->coreFile);
	printf("Syslog File: %s\n", nipper->nmp->syslogFile);
	printf("CDP: %d\n", nipper->nmp->cdp);
	printf("CDP Interval %d\n", nipper->nmp->cdpInterval);
	printf("CDP Holdtime %d\n", nipper->nmp->cdpHoldtime);
	printf("CDP Version %d\n", nipper->nmp->cdpVersion);
	printf("Port Security Auto: %d\n", nipper->nmp->portSecurityAuto);

	// Switch configuration
	if (nipper->nmp->switchConfig != 0)
	{
		printf("ICMP Unreachable: %d\n", nipper->nmp->switchConfig->ipUnreachable);
		printf("ICMP Redirects: %d\n", nipper->nmp->switchConfig->ipRedirect);
		printf("IP Fragmentation: %d\n", nipper->nmp->switchConfig->ipFragmentation);
	}

	// Authentication
	printf("Enable Password: %s\n", nipper->nmp->enablePassword);
	printf("Password: %s\n", nipper->nmp->password);

	if (nipper->nmp->permit != 0)
	{
		printf("Permit Telnet: %d\n", nipper->nmp->permit->telnet);
		hostNMPPointer = nipper->nmp->permit->telnetHost;
		while (hostNMPPointer != 0)
		{
			printf("  Host: %s\n", hostNMPPointer->host);
			printf("  Net Mask: %s\n", hostNMPPointer->netMask);
			hostNMPPointer = hostNMPPointer->next;
		}
		printf("Permit SSH: %d\n", nipper->nmp->permit->ssh);
		hostNMPPointer = nipper->nmp->permit->sshHost;
		while (hostNMPPointer != 0)
		{
			printf("  Host: %s\n", hostNMPPointer->host);
			printf("  Net Mask: %s\n", hostNMPPointer->netMask);
			hostNMPPointer = hostNMPPointer->next;
		}
		printf("Permit SNMP: %d\n", nipper->nmp->permit->snmp);
		hostNMPPointer = nipper->nmp->permit->snmpHost;
		while (hostNMPPointer != 0)
		{
			printf("  Host: %s\n", hostNMPPointer->host);
			printf("  Net Mask: %s\n", hostNMPPointer->netMask);
			hostNMPPointer = hostNMPPointer->next;
		}
	}

	// SNMP
	if (nipper->nmp->snmp != 0)
	{
		communityNMPPointer = nipper->nmp->snmp->community;
		while (communityNMPPointer != 0)
		{
			printf("SNMP Type: %d\n", communityNMPPointer->type);
			printf("  SNMP Community: %s\n", communityNMPPointer->community);
			printf("  SNMP Weak: %d\n", communityNMPPointer->weak);
			printf("  SNMP Simple: %d\n", communityNMPPointer->dictionary);
			printf("  SNMP Access: %d\n", communityNMPPointer->access);
			communityNMPPointer = communityNMPPointer->next;
		}
		snmpTrapPointer = nipper->nmp->snmp->trap;
		while (snmpTrapPointer != 0)
		{
			printf("SNMP Trap: %s\n", snmpTrapPointer->trap);
			printf("  Enabled: %d\n", snmpTrapPointer->enabled);
			snmpTrapPointer = snmpTrapPointer->next;
		}
		snmpNMPHostPointer = nipper->nmp->snmp->host;
		while (snmpNMPHostPointer != 0)
		{
			printf("SNMP Host: %s\n", snmpNMPHostPointer->host);
			printf("SNMP Community: %s\n", snmpNMPHostPointer->community);
			printf("  SNMP Weak: %d\n", snmpNMPHostPointer->weak);
			printf("  SNMP Simple: %d\n", snmpNMPHostPointer->dictionary);
			printf("  SNMP Version: %d\n", snmpNMPHostPointer->version);
			printf("  SNMP Port: %d\n", snmpNMPHostPointer->port);
			printf("  SNMP Owner: %s\n", snmpNMPHostPointer->owner);
			printf("  SNMP Index: %d\n", snmpNMPHostPointer->index);
			snmpNMPHostPointer = snmpNMPHostPointer->next;
		}
	}

	// VLANS
	vlanNMPPointer = nipper->nmp->vlan;
	while(vlanNMPPointer != 0)
	{
		printf("VLAN: %d\n", vlanNMPPointer->vlan);
		printf("  Name: %s\n", vlanNMPPointer->name);
		printf("  Active: %d\n", vlanNMPPointer->active);
		printf("  Type: %s\n", vlanNMPPointer->type);
		printf("  Firewall: %d\n", vlanNMPPointer->firewall);
		printf("  MTU: %d\n", vlanNMPPointer->mtu);
		printf("  Spanning Tree Max Hops: %d\n", vlanNMPPointer->spanTreeMaxHops);
		printf("  All Routes Max Hops: %d\n", vlanNMPPointer->allRoutesMaxHops);
		printf("  Security Association ID: %d\n", vlanNMPPointer->said);
		vlanNMPPointer = vlanNMPPointer->next;
	}

	// Modules / Ports
	moduleNMPPointer = nipper->nmp->module;
	while (moduleNMPPointer != 0)
	{
		printf("Module: %d\n", moduleNMPPointer->module);
		printf("  Name: %s\n", moduleNMPPointer->name);
		printf("  Port Security: %d\n", moduleNMPPointer->portSecurity);
		portNMPPointer = moduleNMPPointer->ports;
		while (portNMPPointer != 0)
		{
			printf("  Port: %d\n", portNMPPointer->port);
			printf("    Name: %s\n", portNMPPointer->name);
			printf("    VLAN: %d\n", portNMPPointer->vlan);
			printf("    Enabled: %d\n", portNMPPointer->enabled);
			printf("    Speed: %d\n", portNMPPointer->speed);
			printf("    Duplex: %d\n", portNMPPointer->duplex);
			printf("    Spanning Tree Guard: %d\n", portNMPPointer->spantreeGuard);
			printf("    Trunk: %d\n", portNMPPointer->trunk);
			printf("    VLAN Trunking: %d\n", portNMPPointer->vtp);
			printf("    Port Security: %d\n", portNMPPointer->portSecurity);
			printf("    CDP: %d\n", portNMPPointer->cdp);
			portNMPPointer = portNMPPointer->next;
		}
		moduleNMPPointer = moduleNMPPointer->next;
	}

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



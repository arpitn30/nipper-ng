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


void reportSOSDebug(struct nipperConfig *nipper)
{
	// Variables
	struct adminUsersSOS *userSOSPointer = 0;
	struct authServerSOS *authServerPointer = 0;
	struct interfaceSOS *interfaceSOSPointer = 0;
	struct snmpCommunitySOS *communityPointer = 0;
	struct snmpHostSOS *snmpHostPointer = 0;
	struct zoneSOS *zonePointer = 0;
	struct johnPassword *johnPointer = 0;

	// Setting info
	printf("\n\nFor some debug settings...\n");
	printf("  True or Enabled = %d\n", true);
	printf("  False or Disabled = %d\n", false);
	printf("  Unconfigured = %d\n\n", unconfigured);

	// General Info
	printf("\n%sInformation Collected\n=====================%s\n", COL_BLUE, RESET);
	printf("Hostname: %s\n", nipper->hostname);
	printf("SSH Version: %d\n", nipper->sos->sshVersion);
	printf("SSH Enabled: %d\n", nipper->sos->sshEnabled);
	printf("SSH v1 Key Gen Time: %d\n", nipper->sos->sshKeyGenTime);
	printf("SSH v2 Public Key: %s\n", nipper->sos->sshPublicKey);

	// Admin Settings
	printf("Admin Settings\n");
	printf("  Admin Name: %s\n", nipper->sos->name);
	printf("  Admin Password: %s\n", nipper->sos->password);
	printf("  Restrict Password Length: %d\n", nipper->sos->restrictLength);
	printf("  Access Attempts: %d\n", nipper->sos->accessAttempts);
	printf("  Privilege: %d\n", nipper->sos->privilege);
	printf("  Admin IP: %s\n", nipper->sos->adminIP);
	printf("  Admin Net Mask: %s\n", nipper->sos->adminNetMask);
	printf("  Console Only Access: %d\n", nipper->sos->consoleOnly);
	printf("  Mail Alerts: %d\n", nipper->sos->mailAlert);
	printf("  E-Mail to: %s\n", nipper->sos->email);
	printf("  E-Mail(1) to: %s\n", nipper->sos->email1);
	printf("  E-Mail(2) to: %s\n", nipper->sos->email2);
	printf("  E-Mail Server: %s\n", nipper->sos->emailServer);
	printf("  Auth Timeout: %d\n", nipper->sos->authTimeout);
	printf("  Auth Server: %s\n", nipper->sos->authenticationServer);
	printf("  Format: %d\n", nipper->sos->adminFormat);
	printf("  HTTP Redirect: %d\n", nipper->sos->httpRedirect);

	// Users
	userSOSPointer = nipper->sos->users;
	while (userSOSPointer != 0)
	{
		printf("  Username: %s\n", userSOSPointer->username);
		printf("    Password: %s\n", userSOSPointer->password);
		printf("    Privilege: %d\n", userSOSPointer->privilege);
		printf("    Trustee: %d\n", userSOSPointer->trustee);
		userSOSPointer = userSOSPointer->next;
	}

	// Auth Servers
	authServerPointer = nipper->sos->authServer;
	while (authServerPointer != 0)
	{
		printf("Auth Server: %s\n", authServerPointer->name);
		printf("  Type: %d\n", authServerPointer->type);
		printf("  ID: %d\n", authServerPointer->id);
		printf("  Server Name: %s\n", authServerPointer->serverName);
		printf("  Backup Server 1: %s\n", authServerPointer->backup1);
		printf("  Backup Server 2: %s\n", authServerPointer->backup2);
		printf("  Timeout: %d\n", authServerPointer->timeout);
		printf("  Forced Timeout: %d\n", authServerPointer->forcedTimeout);
		printf("  Source Interface: %s\n", authServerPointer->sourceInterface);
		printf("  Radius Secret: %s\n", authServerPointer->radiusSecret);
		authServerPointer = authServerPointer->next;
	}

	// Interfaces
	interfaceSOSPointer = nipper->sos->interface;
	while (interfaceSOSPointer != 0)
	{
		printf("Interface: %s\n", interfaceSOSPointer->name);
		printf("  Enabled: %d\n", interfaceSOSPointer->enabled);
		printf("  Zone: %s\n", interfaceSOSPointer->zone);
		printf("  IP Address: %s\n", interfaceSOSPointer->ipAddress);
		printf("  Manage / Monitor\n");
		printf("    Ident-Reset: %d\n", interfaceSOSPointer->manageIdent);
		printf("    MTrace: %d\n", interfaceSOSPointer->manageMtrace);
		printf("    NS Management: %d\n", interfaceSOSPointer->manageNsmgmt);
		printf("    Ping: %d\n", interfaceSOSPointer->managePing);
		printf("    SNMP: %d\n", interfaceSOSPointer->manageSnmp);
		printf("    SSH: %d\n", interfaceSOSPointer->manageSsh);
		printf("    SSL: %d\n", interfaceSOSPointer->manageSsl);
		printf("    Telnet: %d\n", interfaceSOSPointer->manageTelnet);
		printf("    Wen: %d\n", interfaceSOSPointer->manageWeb);
		interfaceSOSPointer = interfaceSOSPointer->next;
	}

	// Zones
	zonePointer = nipper->sos->zone;
	while (zonePointer != 0)
	{
		printf("Zone: %s\n", zonePointer->name);
		printf("  ID: %d\n", zonePointer->id);	
		printf("  VLAN: %d\n", zonePointer->vlan);
		printf("  Block: %d\n", zonePointer->block);
		printf("  Policy Based Routing: %s\n", zonePointer->pbr);
		printf("  Tunnel: %s\n", zonePointer->tunnel);
		printf("  TCP Reset: %d\n", zonePointer->tcpReset);
		printf("  VRouter: %s\n", zonePointer->vrouter);
		printf("  DHCP Relay: %d\n", zonePointer->dhcpRelay);
		printf("  Reasemble for ALG: %d\n", zonePointer->reasembleForALG);
		printf("  Alarm without Drop: %d\n", zonePointer->alarmWithoutDrop);
		printf("  Block Frag: %d\n", zonePointer->blockFrag);
		printf("  ActiveX: %d\n", zonePointer->activeX);
		printf("  Java: %d\n", zonePointer->java);
		printf("  Exe: %d\n", zonePointer->exe);
		printf("  Zip: %d\n", zonePointer->zip);
		printf("  Frag Drop: %d\n", zonePointer->flagDrop);
		printf("  ICMP Flood: %ld\n", zonePointer->icmpFlood);	
		printf("  ICMP Frag: %d\n", zonePointer->icmpFrag);
		printf("  ICMP Large: %d\n", zonePointer->icmpLarge);
		printf("  IP Bad Options: %d\n", zonePointer->ipBadOptions);
		printf("  IP Source Route: %d\n", zonePointer->ipSourceRoute);
		printf("  IP Loose Source: %d\n", zonePointer->ipLooseSource);
		printf("  IP Record Route: %d\n", zonePointer->ipRecordRoute);
		printf("  IP Security Option: %d\n", zonePointer->ipSecurityOption);
		printf("  IP Spoofing: %d\n", zonePointer->ipSpoofing);	
		printf("  IP Stream: %d\n", zonePointer->ipStream);
		printf("  Strict Source: %d\n", zonePointer->strictSource);
		printf("  IP Sweep: %ld\n", zonePointer->ipSweep);
		printf("  IP Timestamp: %d\n", zonePointer->ipTimestamp);
		printf("  Land: %d\n", zonePointer->land);
		printf("  Limit Sessions: %d\n", zonePointer->limitSessions);
		printf("  Malformed URL: %d\n", zonePointer->malformedUrl);
		printf("  Ping of Death: %d\n", zonePointer->pingOfDeath);
		printf("  Port Scan: %ld\n", zonePointer->portScan);
		printf("  SYN ACK ACK: %d\n", zonePointer->synAckAck);
		printf("  SYN FIN: %d\n", zonePointer->synFin);	
		printf("  SYN Flood: %d\n", zonePointer->synFlood);
		printf("  SYN Frags: %d\n", zonePointer->synFrags);
		printf("  No Flags: %d\n", zonePointer->noFlag);	
		printf("  Tear Drop: %d\n", zonePointer->tearDrop);
		printf("  UDP Flood: %d\n", zonePointer->udpFlood);
		printf("  Unknown Protocol: %d\n", zonePointer->unknownProtocol);	
		printf("  Win Nuke: %d\n", zonePointer->winNuke);
		printf("  Apply To Tunnel?: %d\n", zonePointer->onTunnel);
		zonePointer = zonePointer->next;
	}

	// SNMP
	if (nipper->sos->snmp != 0)
	{
		printf("SNMP:\n");
		printf("  Contact: %s\n", nipper->sos->snmp->contact);
		printf("  Location: %s\n", nipper->sos->snmp->location);
		printf("  System Name: %s\n", nipper->sos->snmp->systemName);
		printf("  Listen Port: %d\n", nipper->sos->snmp->listenPort);
		printf("  Trap Port: %d\n", nipper->sos->snmp->trapPort);
		printf("  Authentication Traps: %d\n", nipper->sos->snmp->authTrap);
		communityPointer = nipper->sos->snmp->community;
		while (communityPointer != 0)
		{
			printf("  SNMP Community: %s\n", communityPointer->community);
			printf("    Weak: %d\n", communityPointer->weak);
			printf("    Dictionary: %d\n", communityPointer->dictionary);
			printf("    Read Only?: %d\n", communityPointer->readOnly);
			printf("    Traps?: %d\n", communityPointer->enableTraps);
			printf("    Traffic Traps: %d\n", communityPointer->trafficTraps);
			printf("    SNMP Version: %d\n", communityPointer->version);
			communityPointer = communityPointer->next;
		}
		snmpHostPointer = nipper->sos->snmp->host;
		while (snmpHostPointer != 0)
		{
			printf("  SNMP Host: %s\n", snmpHostPointer->host);
			printf("    SNMP Community: %s\n", snmpHostPointer->community);
			printf("    Weak: %d\n", snmpHostPointer->weak);
			printf("    Dictionary: %d\n", snmpHostPointer->dictionary);
			printf("    Source Interface: %s\n", snmpHostPointer->sourceInterface);
			printf("    SNMP Version: %d\n", snmpHostPointer->version);
			snmpHostPointer = snmpHostPointer->next;
		}
	}

	// Filter Rules...
	reportRulesDebug(nipper);

	// Name Mappings
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



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


void reportIOSDebug(struct nipperConfig *nipper)
{
	// Variables
	struct enablePassword *enablePointer = 0;
	struct ntpKey *ntpKeyPointer = 0;
	struct ntpHost *ntpHostPointer = 0;
	struct ntpAccessGroup *ntpAccessPointer = 0;
	struct snmpCommunity *communityPointer = 0;
	struct snmpViewItem *snmpViewItemPointer = 0;
	struct snmpView *snmpViewPointer = 0;
	struct snmpGroup *snmpGroupPointer = 0;
	struct snmpUser *snmpUserPointer = 0;
	struct snmpTrap *snmpTrapPointer = 0;
	struct snmpHost *snmpHostPointer = 0;
	struct johnPassword *johnPointer = 0;
	struct usernameList *usernamePointer = 0;
	struct privilageLevels *privilagePointer = 0;
	struct host *logServerPointer = 0;
	struct host *tacacsHostPointer = 0;
	struct aaaGroupServer *aaaGroupServerPointer = 0;
	struct aaaServer *aaaServerPointer = 0;
	struct netInterface *interfacePointer = 0;
	struct interfaceConfig *interfaceConfigPointer = 0;
	struct bgpNeighbor *neighborPointer = 0;
	struct keyChain *keyChainPointer = 0;
	struct keyConfig *keyPointer = 0;
	struct lineConfig *linePointer = 0;
	struct bannerConfig *bannerPointer = 0;
	struct ospfNetworkConfig *ospfNetworkPointer = 0;
	struct ospfAreaConfig *ospfAreaPointer = 0;
	struct ospfNeighbor *ospfNeighborPointer = 0;
	struct ospfConfig *ospfPointer = 0;
	struct ospfInterStruct *ospfInterPointer = 0;
	struct staticRoute *routePointer = 0;
	struct host *dnsPointer = 0;
	struct routeMapConfig *routeMapPointer = 0;
	struct natConfig *natPointer = 0;
	struct host *hostPointer = 0;
	struct passiveStruct *passivePointer = 0;
	struct eigrpConfig *eigrpPointer = 0;
	struct eigrpAutonStruct *eigrpAutonPointer = 0;
	struct eigrpNetwork *eigrpNetworkPointer = 0;
	struct eigrpNeighbor *eigrpNeighborPointer = 0;
	struct bgpConfig *bgpPointer = 0;
	struct bgpInterStruct *bgpInterPointer = 0;
	struct vrrpStruct *vrrpPointer = 0;

	// Setting info
	printf("\n\nFor some debug settings...\n");
	printf("True or Enabled = %d\n", true);
	printf("False or Disabled = %d\n", false);
	printf("Unconfigured = %d\n\n", unconfigured);

	// General Info
	printf("\n%sInformation Collected\n=====================%s\n", COL_BLUE, RESET);
	printf("Hostname: %s\n", nipper->hostname);
	printf("Domain Name: %s\n", nipper->domainName);
	printf("IOS Version: %s\n", nipper->version);
	printf("IOS Version: %d.%d\n", nipper->versionMajor, nipper->versionMinor);
	printf("IP Source Routing: %d\n", nipper->ios->sourceRouting);
	printf("Service Password Encryption: %d\n", nipper->ios->servicePasswordEncryption);
	printf("TCP Small Servers: %d\n", nipper->ios->tcpSmallServers);
	printf("UDP Small Servers: %d\n", nipper->ios->udpSmallServers);
	printf("Finger: %d\n", nipper->ios->finger);
	printf("CDP: %d\n", nipper->ios->cdp);
	printf("PAD: %d\n", nipper->ios->pad);
	printf("CEF: %d\n", nipper->ios->cef);
	printf("Bootp: %d\n", nipper->ios->bootp);
	printf("Network Boot: %d\n", nipper->ios->bootNetwork);
	printf("Service Config: %d\n", nipper->ios->serviceConfig);
	printf("IP Classless Routing: %d\n", nipper->ios->classlessRouting);
	printf("TCP Keep Alives In: %d\n", nipper->ios->keepAlivesIn);
	printf("TCP Keep Alives Out: %d\n", nipper->ios->keepAlivesOut);
	printf("Domain Lookup: %d\n", nipper->ios->domainLookup);
	printf("Gratuitous ARPs: %d\n", nipper->ios->gratuitousArps);
	printf("Clock Authorative: %d\n", nipper->ios->calendarValid);
	printf("Summer Time Zone: %s\n", nipper->ios->summerTimeZone);
	printf("Time Zone: %s\n", nipper->ios->timeZone);
	printf("UTC Offset (Hours): %d\n", nipper->ios->timeOffsetHours);
	printf("UTC Offset (Mins): %d\n", nipper->ios->timeOffsetMins);
	printf("Minimum Password Length: %d\n", nipper->ios->passwordMinLength);
	printf("VTP Mode: %d\n", nipper->ios->vtpMode);
	printf("VTP Domain: %s\n", nipper->ios->vtpDomain);
	printf("Number of weak passwords / keys: %d\n", nipper->passwordStrengths);
	printf("Number of dictionary-based passwords / keys: %d\n", nipper->simplePasswords);

	// DNS Servers
	dnsPointer = nipper->ios->dns;
	while (dnsPointer != 0)
	{
		printf("DNS Server: %s\n", dnsPointer->server);
		dnsPointer = dnsPointer->next;
	}

	// SSH
	if (nipper->ios->ssh != 0)
	{
		printf("SSH Enabled: %d\n", nipper->ios->ssh->enabled);
		printf("  SSH Protocol Version: %d\n", nipper->ios->ssh->protocolVersion);
		printf("  SSH Login Timeout: %d\n", nipper->ios->ssh->timeout);
		printf("  SSH Login Retries: %d\n", nipper->ios->ssh->retries);
		interfacePointer = nipper->ios->ssh->interface;
		while (interfacePointer != 0)
		{
			printf("  SSH Server Interface: %s\n", interfacePointer->interface);
			interfacePointer = interfacePointer->next;
		}
	}

	// NAT
	natPointer = nipper->ios->nat;
	while (natPointer != 0)
	{
		printf("NAT Inside: %d\n", natPointer->inside);
		printf("  NAT Type: %d\n", natPointer->type);
		printf("  NAT From: %s\n", natPointer->local);
		printf("  NAT From Port: %d\n", natPointer->localPort);
		printf("  NAT To: %s\n", natPointer->global);
		printf("  NAT To Port: %d\n", natPointer->globalPort);
		printf("  NAT Mask: %s\n", natPointer->mask);
		printf("  NAT Interface No.: %d\n", natPointer->interNumber);
		printf("  NAT Pool: %d\n", natPointer->pool);
		printf("  NAT IPSec-ESP: %d\n", natPointer->ipSecESP);
		printf("  NAT Route Map: %d\n", natPointer->routeMap);
		printf("  NAT TCP: %d\n", natPointer->tcp);
		printf("  NAT Interface: %d\n", natPointer->inter);
		natPointer = natPointer->next;
	}

	// HTTP
	if (nipper->ios->http != 0)
	{
		printf("HTTP Enabled: %d\n", nipper->ios->http->enabled);
		printf("  HTTP Authentication: %d\n", nipper->ios->http->authentication);
		printf("  HTTP Access-Class: %s\n", nipper->ios->http->accessClass);
	}

	// Enable
	enablePointer = nipper->ios->enable;
	while (enablePointer != 0)
	{
		printf("Enable Level: %d\n", enablePointer->level);
		printf("  Encryption Type: %d\n", enablePointer->encryption);
		printf("  Secret?: %d\n", enablePointer->secret);
		printf("  Password: %s\n", enablePointer->password);
		printf("  Password Encrypted: %s\n", enablePointer->passwordEncrypted);
		printf("  Weak Password: %d\n", enablePointer->weak);
		printf("  Dictionary Password: %d\n", enablePointer->dictionary);
		enablePointer = enablePointer->next;
	}

	// Username
	usernamePointer = nipper->ios->username;
	while (usernamePointer != 0)
	{
		printf("Username: %s\n", usernamePointer->username);
		printf("  Encryption Type: %d\n", usernamePointer->encryption);
		printf("  Secret?: %d\n", usernamePointer->secret);
		printf("  Privilage Level: %d\n", usernamePointer->privilage);
		printf("  Password: %s\n", usernamePointer->password);
		printf("  Password Encrypted: %s\n", usernamePointer->passwordEncrypted);
		printf("  Weak Password: %d\n", usernamePointer->weak);
		printf("  Dictionary Password: %d\n", usernamePointer->dictionary);
		usernamePointer = usernamePointer->next;
	}

	// Privilage
	privilagePointer = nipper->ios->privilage;
	while (privilagePointer != 0)
	{
		printf("Privilage Level: %d\n", privilagePointer->level);
		printf("  Privilage Command: %s\n", privilagePointer->command);
		privilagePointer = privilagePointer->next;
	}

	// Banner
	bannerPointer = nipper->ios->banner;
	while (bannerPointer != 0)
	{
		printf("Banner: %s\n", bannerPointer->line);
		bannerPointer = bannerPointer->next;
	}

	// Logging
	if (nipper->ios->logging != 0)
	{
		printf("Logging: %d\n", nipper->ios->logging->logging);
		printf("  Log Enable: %d\n", nipper->ios->logging->logEnable);
		printf("  Console Logging: %d\n", nipper->ios->logging->consoleLogging);
		printf("  Console Level: %d\n", nipper->ios->logging->consoleLevel);
		printf("  Monitor Logging: %d\n", nipper->ios->logging->monitorLogging);
		printf("  Monitor Level: %d\n", nipper->ios->logging->monitorLevel);
		printf("  Buffered Logging: %d\n", nipper->ios->logging->bufferedLogging);
		printf("  Buffered Level: %d\n", nipper->ios->logging->bufferLevel);
		printf("  Buffered Size: %d\n", nipper->ios->logging->bufferSize);
		printf("  Syslog Level: %d\n", nipper->ios->logging->loggingTrap);
		printf("  Syslog Facility: %s\n", nipper->ios->logging->facility);
		printf("  Syslog Count: %d\n", nipper->ios->logging->logCount);
		printf("  Syslog Origin ID: %s\n", nipper->ios->logging->originId);
		printf("  Syslog Source Interface: %s\n", nipper->ios->logging->sourceInterface);
		logServerPointer = nipper->ios->logging->logServer;
		while (logServerPointer != 0)
		{
			printf("  Syslog Logging Server: %s\n", logServerPointer->server);
			logServerPointer = logServerPointer->next;
		}
	}

	// Routing
	if (nipper->ios->route != 0)
	{
		routePointer = nipper->ios->route;
		while (routePointer != 0)
		{
			printf("Static Route\n");
			printf("  IP Address: %s\n", routePointer->ipAddress);
			printf("  Net Mask: %s\n", routePointer->netMask);
			printf("  Gateway: %s\n", routePointer->gateway);
			routePointer = routePointer->next;
		}
	}
	routeMapPointer = nipper->ios->routeMap;
	while (routeMapPointer != 0)
	{
		printf("Route Map: %s\n", routeMapPointer->mapTag);
		printf("  Sequence No.: %d\n", routeMapPointer->sequenceNo);
		printf("  Permission: %d\n", routeMapPointer->permission);
		routeMapPointer = routeMapPointer->next;
	}
	eigrpPointer = nipper->ios->eigrp;
	while (eigrpPointer != 0)
	{
		printf("EIGRP Autonomous No: %d\n", eigrpPointer->process);
		printf("  EIGRP Router ID: %s\n", eigrpPointer->routerId);
		printf("  EIGRP Maximum Hops: %d\n", eigrpPointer->maximumHops);
		printf("  EIGRP Stub: %d\n", eigrpPointer->stub);
		printf("  EIGRP Auto Summary: %d\n", eigrpPointer->autoSummary);
		printf("  EIGRP Internal Distance: %d\n", eigrpPointer->internalDistance);
		printf("  EIGRP External Distance: %d\n", eigrpPointer->externalDistance);
		printf("  EIGRP Log Neighbor Changes: %d\n", eigrpPointer->logNeighborChanges);
		printf("  EIGRP Log Neighbor Warnings: %d\n", eigrpPointer->logNeighborWarnings);
		eigrpNetworkPointer = eigrpPointer->network;
		while (eigrpNetworkPointer != 0)
		{
			printf("  EIGRP Network IP Address: %s\n", eigrpNetworkPointer->ipAddress);
			printf("    EIGRP NetMask: %s\n", eigrpNetworkPointer->netMask);
			eigrpNetworkPointer = eigrpNetworkPointer->next;
		}
		eigrpNeighborPointer = eigrpPointer->neighbor;
		while (eigrpNeighborPointer != 0)
		{
			printf("  EIGRP Neighbor IP Address: %s\n", eigrpNeighborPointer->ipAddress);
			printf("    EIGRP NetMask: %s\n", eigrpNeighborPointer->interface);
			eigrpNeighborPointer = eigrpNeighborPointer->next;
		}
		passivePointer = eigrpPointer->passive;
		while (passivePointer != 0)
		{
			printf("  EIGRP Passive Interface: %s\n", passivePointer->interface);
			printf("    Passive: %d\n", passivePointer->passive);
			passivePointer = passivePointer->next;
		}
		eigrpPointer = eigrpPointer->next;
	}
	bgpPointer = nipper->ios->bgp;
	while (bgpPointer != 0)
	{
		printf("BGP Autonomous No: %d\n", bgpPointer->autonomousNo);
		printf("  BGP Log Changes: %d\n", bgpPointer->logNeighborChanges);
		printf("  BGP Dampening: %d\n", bgpPointer->dampening);
		printf("  BGP Default Passive: %d\n", bgpPointer->defaultPassive);
		passivePointer = bgpPointer->passive;
		while (passivePointer != 0)
		{
			printf("  BGP Passive Interface: %s\n", passivePointer->interface);
			printf("    Passive: %d\n", passivePointer->passive);
			passivePointer = passivePointer->next;
		}
		neighborPointer = bgpPointer->neighbor;
		while (neighborPointer != 0)
		{
			printf("  BGP Neighbor: %s\n", neighborPointer->host);
			printf("    BGP Neighbor Description: %s\n", neighborPointer->description);
			printf("    BGP Password Encryption Type: %d\n", neighborPointer->encryption);
			printf("    BGP Password: %s\n", neighborPointer->password);
			printf("    BGP Password Encrypted: %s\n", neighborPointer->passwordEncrypted);
			printf("    BGP Neighbor Password: %s\n", neighborPointer->password);
			printf("    BGP Weak Password: %d\n", neighborPointer->weak);
			printf("    BGP Dictionary Password: %d\n", neighborPointer->dictionary);
			printf("    BGP Neighbor Autonomous No: %d\n", neighborPointer->autonomousNo);
			printf("    BGP Neighbor TTL Hops: %d\n", neighborPointer->ttlHops);
			neighborPointer = neighborPointer->next;
		}
		bgpPointer = bgpPointer->next;
	}
	if (nipper->ios->rip != 0)
	{
		printf("RIP Version: %d\n", nipper->ios->rip->version);
		printf("RIP Auto Summary: %d\n", nipper->ios->rip->autoSummary);
		printf("RIP Default Route: %d\n", nipper->ios->rip->defaultRoute);
		printf("RIP Default Route Map: %s\n", nipper->ios->rip->defaultRouteMap);
		printf("RIP Default Metric: %d\n", nipper->ios->rip->defaultMetric);
		printf("RIP Input Queue: %d\n", nipper->ios->rip->inputQueue);
		printf("RIP Output Delay: %d\n", nipper->ios->rip->outputDelay);
		printf("RIP Validate Update Source: %d\n", nipper->ios->rip->validateUpdateSource);
		printf("RIP Default Passive: %d\n", nipper->ios->rip->defaultPassive);
		hostPointer = nipper->ios->rip->neighbor;
		while (hostPointer != 0)
		{
			printf("RIP Neighbor: %s\n", hostPointer->server);
			hostPointer = hostPointer->next;
		}
		hostPointer = nipper->ios->rip->network;
		while (hostPointer != 0)
		{
			printf("RIP Network: %s\n", hostPointer->server);
			hostPointer = hostPointer->next;
		}
		passivePointer = nipper->ios->rip->passive;
		while (passivePointer != 0)
		{
			printf("RIP Passive Interface: %s\n", passivePointer->interface);
			printf("  Passive: %d\n", passivePointer->passive);
			passivePointer = passivePointer->next;
		}
	}
	ospfPointer = nipper->ios->ospf;
	while (ospfPointer != 0)
	{
		printf("OSPF Process ID: %d\n", ospfPointer->processID);
		ospfNetworkPointer = nipper->ios->ospf->ospfNetwork;
		while (ospfNetworkPointer != 0)
		{
			printf("  OSPF Network: %s\n", ospfNetworkPointer->network);
			printf("    OSPF Network Mask: %s\n", ospfNetworkPointer->networkMask);
			printf("    OSPF Area ID: %s\n", ospfNetworkPointer->areaID);
			ospfNetworkPointer = ospfNetworkPointer->next;
		}
		ospfAreaPointer = nipper->ios->ospf->ospfArea;
		while (ospfNetworkPointer != 0)
		{
			printf("  OSPF Area ID: %s\n", ospfAreaPointer->areaID);
			printf("    OSPF Area Authentication: %d\n", ospfAreaPointer->areaAuth);
			printf("    OSPF Area Default Cost: %d\n", ospfAreaPointer->defaultCost);
			ospfAreaPointer = ospfAreaPointer->next;
		}
		ospfNeighborPointer = nipper->ios->ospf->neighbor;
		while (ospfNeighborPointer != 0)
		{
			printf("  OSPF Neighbor: %s\n", ospfNeighborPointer->host);
			printf("    OSPF Neighbor Priority: %d\n", ospfNeighborPointer->priority);
			printf("    OSPF Neighbor Poll Interval: %d\n", ospfNeighborPointer->pollInterval);
			printf("    OSPF Neighbor Cost: %d\n", ospfNeighborPointer->costNumber);
			printf("    OSPF Neighbor Database Filter: %d\n", ospfNeighborPointer->databaseFilter);
			ospfNeighborPointer = ospfNeighborPointer->next;
		}
		ospfPointer = ospfPointer->next;
	}

	// TACACS
	if (nipper->ios->tacacs != 0)
	{
		printf("TACACS Key: %s\n", nipper->ios->tacacs->key);
		printf("  TACACS Encrypted Key: %s\n", nipper->ios->tacacs->keyEncrypted);
		printf("  TACACS Encryption Type: %d\n", nipper->ios->tacacs->encryption);
		printf("  TACACS Weak Password: %d\n", nipper->ios->tacacs->weak);
		printf("  TACACS Dictionary Password: %d\n", nipper->ios->tacacs->dictionary);
		tacacsHostPointer = nipper->ios->tacacs->host;
		while (tacacsHostPointer != 0)
		{
			printf("TACACS Server: %s\n", tacacsHostPointer->server);
			tacacsHostPointer = tacacsHostPointer->next;
		}
	}

	// AAA
	if (nipper->ios->aaa != 0)
	{
		aaaGroupServerPointer = nipper->ios->aaa->groupServer;
		while (aaaGroupServerPointer != 0)
		{
			printf("AAA Group Server Type: %d\n", aaaGroupServerPointer->type);
			printf("AAA Group Server Username: %s\n", aaaGroupServerPointer->username);
			aaaServerPointer = aaaGroupServerPointer->server;
			while (aaaServerPointer != 0)
			{
				printf("  AAA Server: %s\n", aaaServerPointer->server);
				printf("  AAA Auth Port: %d\n", aaaServerPointer->authPort);
				printf("  AAA Acct Port: %d\n", aaaServerPointer->acctPort);
				printf("  AAA Key: %s\n", aaaServerPointer->key);
				printf("  AAA Encrypted Key: %s\n", aaaServerPointer->keyEncrypted);
				printf("  AAA Encryption: %d\n", aaaServerPointer->encryption);
				printf("  AAA Weak Password: %d\n", aaaServerPointer->weak);
				printf("  AAA Dictionary Password: %d\n", aaaServerPointer->dictionary);
				aaaServerPointer = aaaServerPointer->next;
			}
			aaaGroupServerPointer = aaaGroupServerPointer->next;
		}
	}

	// NTP
	if (nipper->ios->ntp != 0)
	{
		printf("NTP Enabled: %d\n", nipper->ios->ntp->enabled);
		printf("  NTP Master: %d\n", nipper->ios->ntp->master);
		ntpHostPointer = nipper->ios->ntp->server;
		while (ntpHostPointer != 0)
		{
			printf("  NTP Server: %s\n", ntpHostPointer->ntpHost);
			printf("  NTP Server Key Num: %d\n", ntpHostPointer->keyNum);
			ntpHostPointer = ntpHostPointer->next;
		}
		ntpHostPointer = nipper->ios->ntp->peer;
		while (ntpHostPointer != 0)
		{
			printf("  NTP Peer: %s\n", ntpHostPointer->ntpHost);
			printf("  NTP Peer Key Num: %d\n", ntpHostPointer->keyNum);
			ntpHostPointer = ntpHostPointer->next;
		}
		ntpAccessPointer = nipper->ios->ntp->access;
		while (ntpAccessPointer != 0)
		{
			printf("  Access Type: %d\n", ntpAccessPointer->accessType);
			printf("  Access List: %s\n", ntpAccessPointer->accessList);
			ntpAccessPointer = ntpAccessPointer->next;
		}
		ntpKeyPointer = nipper->ios->ntp->key;
		while (ntpKeyPointer != 0)
		{
			printf("NTP Key Num: %d\n", ntpKeyPointer->keyNum);
			printf("  NTP Key: %s\n", ntpKeyPointer->key);
			printf("  NTP Key Trusted: %d\n", ntpKeyPointer->trusted);
			printf("  NTP Weak Password: %d\n", ntpKeyPointer->weak);
			printf("  NTP Dictionary Password: %d\n", ntpKeyPointer->dictionary);
			ntpKeyPointer = ntpKeyPointer->next;
		}
	}

	// SNMP
	if (nipper->ios->snmp != 0)
	{
		printf("SNMP Enabled: %d\n", nipper->ios->snmp->enabled);
		printf("SNMP TFTP Server Access List: %s\n", nipper->ios->snmp->tftpServerList);
		printf("SNMP Contact: %s\n", nipper->ios->snmp->contact);
		printf("SNMP Location: %s\n", nipper->ios->snmp->location);
		printf("SNMP Trap Timeout: %d\n", nipper->ios->snmp->trapTimeout);
		printf("SNMP Trap Source: %s\n", nipper->ios->snmp->trapSource);
		communityPointer = nipper->ios->snmp->community;
		while (communityPointer != 0)
		{
			printf("SNMP Community String: %s\n", communityPointer->community);
			printf("  SNMP Weak Password: %d\n", communityPointer->weak);
			printf("  SNMP Dictionary Password: %d\n", communityPointer->dictionary);
			printf("  SNMP Read-Only: %d\n", communityPointer->readonly);
			printf("  SNMP Community Enabled: %d\n", communityPointer->enabled);
			printf("  SNMP Access List: %s\n", communityPointer->accessList);
			communityPointer = communityPointer->next;
		}
		snmpGroupPointer = nipper->ios->snmp->group;
		while (snmpGroupPointer != 0)
		{
			printf("SNMP Group: %s\n", snmpGroupPointer->groupName);
			printf("  SNMP Version: %d\n", snmpGroupPointer->version);
			printf("  SNMP Read View: %s\n", snmpGroupPointer->readView);
			printf("  SNMP Write View: %s\n", snmpGroupPointer->writeView);
			printf("  SNMP Notify View: %s\n", snmpGroupPointer->writeView);
			printf("  SNMP Context: %s\n", snmpGroupPointer->context);
			printf("  SNMP ACL: %s\n", snmpGroupPointer->acl);
			snmpGroupPointer = snmpGroupPointer->next;
		}
		snmpUserPointer = nipper->ios->snmp->user;
		while (snmpUserPointer != 0)
		{
			printf("SNMP User: %s\n", snmpUserPointer->userName);
			printf("  SNMP User Auth Pass: %s\n", snmpUserPointer->authPass);
			printf("  SNMP User Priv Pass: %s\n", snmpUserPointer->privPass);
			printf("  SNMP Group Name: %s\n", snmpUserPointer->groupName);
			printf("  In Group: %d\n", snmpUserPointer->group);
			snmpUserPointer = snmpUserPointer->next;
		}
		snmpViewPointer = nipper->ios->snmp->view;
		while (snmpViewPointer != 0)
		{
			printf("SNMP View: %s\n", snmpViewPointer->viewName);
			snmpViewItemPointer = snmpViewPointer->viewItem;
			while (snmpViewItemPointer != 0)
			{
				printf("  SNMP View MIB Item: %s\n", snmpViewItemPointer->mibId);
				printf("  SNMP View Item Include: %d\n", snmpViewItemPointer->include);
				snmpViewItemPointer = snmpViewItemPointer->next;
			}
			snmpViewPointer = snmpViewPointer->next;
		}
		snmpTrapPointer = nipper->ios->snmp->trap;
		while (snmpTrapPointer != 0)
		{
			printf("SNMP Trap: %s\n", snmpTrapPointer->trap);
			snmpTrapPointer = snmpTrapPointer->next;
		}
		snmpHostPointer = nipper->ios->snmp->host;
		while (snmpHostPointer != 0)
		{
			printf("SNMP Host: %s\n", snmpHostPointer->host);
			printf("  SNMP Host Community: %s\n", snmpHostPointer->community);
			printf("  SNMP Host Version: %d\n", snmpHostPointer->version);
			printf("  SNMP Weak Password: %d\n", snmpHostPointer->weak);
			printf("  SNMP Dictionary Password: %d\n", snmpHostPointer->dictionary);
			snmpHostPointer = snmpHostPointer->next;
		}
	}

	// Key Chains and Keys
	keyChainPointer = nipper->ios->chain;
	while (keyChainPointer != 0)
	{
		printf("KEY CHAIN: %s\n", keyChainPointer->name);
		keyPointer = keyChainPointer->key;
		while (keyPointer != 0)
		{
			printf("  KEY NUMBER: %d\n", keyPointer->keyNumber);
			printf("  KEY: %s\n", keyPointer->key);
			printf("  KEY Weak Password: %d\n", keyPointer->weak);
			printf("  KEY Dictionary Password: %d\n", keyPointer->dictionary);
			keyPointer = keyPointer->next;
		}
		keyChainPointer = keyChainPointer->next;
	}

	// FTP
	if (nipper->ios->ftp != 0)
	{
		printf("FTP Username: %s\n", nipper->ios->ftp->username);
		printf("  FTP Password: %s\n", nipper->ios->ftp->password);
		printf("  FTP Password Encrypted: %s\n", nipper->ios->ftp->passwordEncrypted);
		printf("  FTP Encryption: %d\n", nipper->ios->ftp->encryption);
		printf("  FTP Weak Password: %d\n", nipper->ios->ftp->weak);
		printf("  FTP Dictionary Password: %d\n", nipper->ios->ftp->dictionary);
		interfacePointer = nipper->ios->ftp->interface;
		while (interfacePointer != 0)
		{
			printf("FTP Server Interface: %s\n", interfacePointer->interface);
			interfacePointer = interfacePointer->next;
		}
	}

	// Line
	linePointer = nipper->ios->line;
	while (linePointer != 0)
	{
		printf("Line Start: %d\n", linePointer->lineNumberStart);
		printf("Line End: %d\n", linePointer->lineNumberEnd);
		printf("  Line Type: %d\n", linePointer->lineType);
		printf("  Line Login: %d\n", linePointer->login);
		printf("  Line Authorization: %d\n", linePointer->authorization);
		printf("  Line Accounting: %d\n", linePointer->accounting);
		printf("  Line ACL In: %s\n", linePointer->aclIn);
		printf("  Line ACL Out: %s\n", linePointer->aclOut);
		printf("  Line Timeout: %d\n", linePointer->timeout);
		printf("  Line Exec Timeout: %d\n", linePointer->execTimeout);
		printf("  Line Session Timeout: %d\n", linePointer->sessionTimeout);
		printf("  Line Absolute Timeout: %d\n", linePointer->absoluteTimeout);
		printf("  Line Exec: %d\n", linePointer->exec);
		printf("  Line Callback: %d\n", linePointer->callback);
		printf("  Line Password: %s\n", linePointer->password);
		printf("  Line Password Encrypted: %s\n", linePointer->passwordEncrypted);
		printf("  Line Password Encryption: %d\n", linePointer->encryption);
		printf("  Line Weak Password: %d\n", linePointer->weak);
		printf("  Line Dictionary Password: %d\n", linePointer->dictionary);
		printf("  Line Transport SSH: %d\n", linePointer->ssh);
		printf("  Line Transport Telnet: %d\n", linePointer->telnet);
		linePointer = linePointer->next;
	}

	// Interfaces
	interfaceConfigPointer = nipper->ios->interface;
	while (interfaceConfigPointer != 0)
	{
		printf("Interface: %s\n", interfaceConfigPointer->name);
		printf("  Description: %s\n", interfaceConfigPointer->description);
		printf("  IP Address: %s\n", interfaceConfigPointer->ipAddress);
		printf("  Access Group (In): %s\n", interfaceConfigPointer->accessGroupIn);
		printf("  Access Group (Out): %s\n", interfaceConfigPointer->accessGroupOut);
		printf("  Proxy ARP: %d\n", interfaceConfigPointer->proxyArp);
		printf("  NTP: %d\n", interfaceConfigPointer->ntp);
		printf("  MOP: %d\n", interfaceConfigPointer->mop);
		printf("  IP Unreachables: %d\n", interfaceConfigPointer->ipUnreachables);
		printf("  IP Redirects: %d\n", interfaceConfigPointer->ipRedirects);
		printf("  IP Mask Reply: %d\n", interfaceConfigPointer->ipMaskReply);
		printf("  IP Direct Broadcast: %d\n", interfaceConfigPointer->ipDirectBroadcast);
		printf("  CDP: %d\n", interfaceConfigPointer->cdp);
		printf("  uRPF: %d\n", interfaceConfigPointer->uRPF);
		printf("  Shutdown: %d\n", interfaceConfigPointer->shutdown);
		printf("  RIP Auth Mode: %d\n", interfaceConfigPointer->ripAuthMode);
		printf("  RIP Key Chain: %s\n", interfaceConfigPointer->ripKeyChain);
		printf("  RIP Send Version: %d\n", interfaceConfigPointer->ripSendVersion);
		printf("  RIP Receive Version: %d\n", interfaceConfigPointer->ripReceiveVersion);
		printf("  RIP Triggered: %d\n", interfaceConfigPointer->ripTriggered);
		printf("  RIP v2 Broadcast: %d\n", interfaceConfigPointer->ripV2Broadcast);
		printf("  RIP Passive: %d\n", interfaceConfigPointer->ripPassive);
		eigrpAutonPointer = interfaceConfigPointer->eigrp;
		while (eigrpAutonPointer != 0)
		{
			printf("  EIGRP Auto No: %d\n", eigrpAutonPointer->autonomousNo);
			printf("    Key Chain: %s\n", eigrpAutonPointer->keyChain);
			printf("    MD5 Auth: %d\n", eigrpAutonPointer->md5Auth);
			printf("    Bandwidth: %d\n", eigrpAutonPointer->bandwidth);
			printf("    Passive: %d\n", eigrpAutonPointer->passive);
			eigrpAutonPointer = eigrpAutonPointer->next;
		}
		bgpInterPointer = interfaceConfigPointer->bgp;
		while (bgpInterPointer != 0)
		{
			printf("  BGP Auto No: %d\n", bgpInterPointer->autonomousNo);
			printf("    Passive: %d\n", bgpInterPointer->passive);
			bgpInterPointer = bgpInterPointer->next;
		}
		ospfInterPointer = interfaceConfigPointer->ospf;
		while (ospfInterPointer != 0)
		{
			printf("  OSPF Process ID: %d\n", ospfInterPointer->processID);
			printf("    Passive: %d\n", ospfInterPointer->passive);
			ospfInterPointer = ospfInterPointer->next;
		}
		vrrpPointer = interfaceConfigPointer->vrrp;
		while (vrrpPointer != 0)
		{
			printf("  VRRP Group: %d\n", vrrpPointer->group);
			printf("    Description: %s\n", vrrpPointer->description);
			printf("    Authentication: %d\n", vrrpPointer->authentication);
			printf("    Key Chain: %d\n", vrrpPointer->keyChain);
			printf("    Auth String: %s\n", vrrpPointer->authString);
			printf("    Encrypted Auth String: %s\n", vrrpPointer->authStringEnc);
			printf("    Weak Password: %d\n", vrrpPointer->weak);
			printf("    Dictionay Password: %d\n", vrrpPointer->dictionary);
			printf("    IP Address: %s\n", vrrpPointer->ipAddress);
			printf("    IP Address (Secondary): %s\n", vrrpPointer->ipAddress2);
			printf("    Priority Level: %d\n", vrrpPointer->priorityLevel);
			printf("    Shutdown: %d\n", vrrpPointer->shutdown);
			vrrpPointer = vrrpPointer->next;
		}
		printf("  Switchport Mode: %d\n", interfaceConfigPointer->switchportMode);
		printf("  Switchport VLAN: %d\n", interfaceConfigPointer->switchportVLAN);
		printf("  Switchport Port Security: %d\n", interfaceConfigPointer->switchportSecurity);
		printf("  Switchport Port Security Violation: %d\n", interfaceConfigPointer->switchportViolation);
		printf("  OSPF Auth: %d\n", interfaceConfigPointer->ospfAuthentication);
		printf("  OSPF Auth Key: %s\n", interfaceConfigPointer->ospfKey);
		printf("  OSPF Flood Reduction: %d\n", interfaceConfigPointer->ospfFloodReduction);
		printf("  OSPF Network: %d\n", interfaceConfigPointer->ospfNetwork);
		interfaceConfigPointer = interfaceConfigPointer->next;
	}

	// Filter Rules...
	reportRulesDebug(nipper);

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



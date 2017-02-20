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


void processDefaults(struct nipperConfig *nipper)
{
	// Variables...
	struct lineConfig *linePointer = 0;
	struct interfaceConfig *interfacePointer = 0;
	struct passiveStruct *passivePointer = 0;
	struct eigrpConfig *eigrpPointer = 0;
	struct eigrpAutonStruct *eigrpAutonPointer = 0;
	struct bgpInterStruct *bgpInterPointer = 0;
	struct bgpConfig *bgpPointer = 0;
	struct ospfInterStruct *ospfInterPointer = 0;
	struct ospfConfig *ospfPointer = 0;
	struct filterConfig *filterPointer = 0;
	struct filterConfig *filterSearchPointer = 0;
	struct filterListConfig *filterListPointer = 0;
	struct filterListConfig *filterListMovePointer = 0;
	struct filterObjectConfig *filterObjectPointer = 0;
	struct interfaceSOS *interfaceSOSPointer = 0;
	int setting = 0;
	int setting2 = 0;

	// Remove Passport device, assigned filters first, doing it after would be a waste of CPU/Memory...
	if ((nipper->deviceType == type_passport) && (nipper->filterList != 0))
	{
		// Get unassigned list...
		filterListPointer = getFilterList(nipper, "**UNASSIGNED**", "", false);

		// Move the unassigned list to being the last one...
		if ((nipper->filterList == filterListPointer) && (nipper->filterList->next != 0))
		{
			filterListMovePointer = nipper->filterList->next;
			while (filterListMovePointer->next != 0)
				filterListMovePointer = filterListMovePointer->next;
			filterListMovePointer->next = filterListPointer;
			nipper->filterList = filterListPointer->next;
			filterListPointer->next = 0;
		}
		else if (nipper->filterList != filterListPointer)
		{
			filterListMovePointer = nipper->filterList;
			while (filterListMovePointer->next != filterListPointer)
				filterListMovePointer = filterListMovePointer->next;
			filterListMovePointer->next = filterListPointer->next;
			while (filterListMovePointer->next != 0)
				filterListMovePointer = filterListMovePointer->next;
			filterListMovePointer->next = filterListPointer;
			filterListPointer->next = 0;
		}

		// Remove all assigned filters in the unassigned set...
		filterPointer = filterListPointer->filter;
		filterSearchPointer = 0;
		while (filterPointer != 0)
		{
			// If filter should be removed...
			if (filterPointer->inSet == true)
			{
				// Sort out pointers first...
				if (filterSearchPointer == 0)
					filterListPointer->filter = filterPointer->next;
				else
					filterSearchPointer->next = filterPointer->next;

				// Free sub structures...
				while (filterPointer->source != 0)
				{
					filterObjectPointer = filterPointer->source->next;
					free (filterPointer->source);
					filterPointer->source = filterObjectPointer;
				}
				while (filterPointer->sourceService != 0)
				{
					filterObjectPointer = filterPointer->sourceService->next;
					free (filterPointer->sourceService);
					filterPointer->sourceService = filterObjectPointer;
				}
				while (filterPointer->destination != 0)
				{
					filterObjectPointer = filterPointer->destination->next;
					free (filterPointer->destination);
					filterPointer->destination = filterObjectPointer;
				}
				while (filterPointer->destinationService != 0)
				{
					filterObjectPointer = filterPointer->destinationService->next;
					free (filterPointer->destinationService);
					filterPointer->destinationService = filterObjectPointer;
				}
				while (filterPointer->through != 0)
				{
					filterObjectPointer = filterPointer->through->next;
					free (filterPointer->through);
					filterPointer->through = filterObjectPointer;
				}
				while (filterPointer->install != 0)
				{
					filterObjectPointer = filterPointer->install->next;
					free (filterPointer->install);
					filterPointer->install = filterObjectPointer;
				}
				free (filterPointer);

				// Sort out pointers...
				if (filterSearchPointer == 0)
					filterPointer = filterListPointer->filter;
				else
					filterPointer = filterSearchPointer->next;
			}

			// Update Pointers...
			else
			{
				filterSearchPointer = filterPointer;
				filterPointer = filterPointer->next;
			}
		}

		// If unset filter list has no more filters, remove it...
		if (filterListPointer->filter == 0)
		{
			if (nipper->filterList == filterListPointer)
				nipper->filterList = 0;
			else
			{
				filterListMovePointer = nipper->filterList;
				while (filterListMovePointer != filterListPointer)
					filterListMovePointer = filterListMovePointer->next;
				filterListMovePointer->next = 0;
			}
			free (filterListPointer);
		}
	}


	// Add the "Any" to filters that are blank...
	filterListPointer = nipper->filterList;
	while (filterListPointer != 0)
	{
		filterPointer = filterListPointer->filter;
		while (filterPointer != 0)
		{
			if (filterPointer->protocol[0] == 0)
				strcpy(filterPointer->protocol, "Any");
			if (filterPointer->source == 0)
			{
				filterObjectPointer = getFilterMember(filterPointer, "Any", object_filter_source);
				filterObjectPointer->type = object_type_any;
			}
			if (filterPointer->sourceService == 0)
			{
				filterObjectPointer = getFilterMember(filterPointer, "Any", object_filter_sourceService);
				filterObjectPointer->type = object_type_any;
				filterObjectPointer->serviceOp = service_oper_any;
			}
			if (filterPointer->destination == 0)
			{
				filterObjectPointer = getFilterMember(filterPointer, "Any", object_filter_destination);
				filterObjectPointer->type = object_type_any;
			}
			if (filterPointer->destinationService == 0)
			{
				filterObjectPointer = getFilterMember(filterPointer, "Any", object_filter_service);
				filterObjectPointer->type = object_type_any;
				filterObjectPointer->serviceOp = service_oper_any;
			}
			if (filterPointer->through == 0)
			{
				filterObjectPointer = getFilterMember(filterPointer, "Any", object_filter_through);
				filterObjectPointer->type = object_type_any;
			}
			if (filterPointer->install == 0)
			{
				filterObjectPointer = getFilterMember(filterPointer, "Any", object_filter_install);
				filterObjectPointer->type = object_type_any;
			}
			filterPointer = filterPointer->next;
		}
		filterListPointer = filterListPointer->next;
	}

	switch(nipper->deviceType)
	{
		// Switch / Router / IOS
		case type_ios_switch:
		case type_ios_router:
		case type_ios_catalyst:

			// CEF...
			if (nipper->ios->cef == unconfigured)
			{
				if (nipper->deviceModel == 0)
					nipper->ios->cef = false;
				else if ((strncmp(nipper->deviceModel, "71", 2) == 0) && (strlen(nipper->deviceModel) > 3))
					nipper->ios->cef = true;
				else if ((strncmp(nipper->deviceModel, "72", 2) == 0) && (strlen(nipper->deviceModel) > 3))
					nipper->ios->cef = true;
				else if ((strncmp(nipper->deviceModel, "75", 2) == 0) && (strlen(nipper->deviceModel) > 3))
					nipper->ios->cef = true;
				else if ((strncmp(nipper->deviceModel, "65", 2) == 0) && (strlen(nipper->deviceModel) > 3))
					nipper->ios->cef = true;
				else if ((strncmp(nipper->deviceModel, "120", 3) == 0) && (strlen(nipper->deviceModel) > 4))
					nipper->ios->cef = true;
				else
					nipper->ios->cef = false;
			}

			// Time Zones...
			if (nipper->timeZones == unconfigured)
				nipper->timeZones = true;

			// Minimum Password Length
			if (nipper->ios->passwordMinLength == -1)
			{
				if ((nipper->versionMajor == 12) && (nipper->versionMinor > 2))
					nipper->ios->passwordMinLength = 6;
			}

			// BGP Passive
			if (nipper->ios->bgp != 0)
			{
				bgpPointer = nipper->ios->bgp;
				while (bgpPointer != 0)
				{
					interfacePointer = nipper->ios->interface;
					while (interfacePointer != 0)
					{
						bgpInterPointer = bgpInterfaceConfig(interfacePointer, bgpPointer->autonomousNo);
						passivePointer = bgpPointer->passive;
						while (passivePointer != 0)
						{
							if (strcmp(passivePointer->interface, interfacePointer->name) == 0)
								bgpInterPointer->passive = passivePointer->passive;
							passivePointer = passivePointer->next;
						}
						interfacePointer = interfacePointer->next;
					}
					bgpPointer = bgpPointer->next;
				}
				bgpPointer = nipper->ios->bgp;
				while (bgpPointer != 0)
				{
					interfacePointer = nipper->ios->interface;
					while (interfacePointer != 0)
					{
						bgpInterPointer = bgpInterfaceConfig(interfacePointer, bgpPointer->autonomousNo);
						if (bgpInterPointer->passive == unconfigured)
							bgpInterPointer->passive = bgpPointer->defaultPassive;
						interfacePointer = interfacePointer->next;
					}
					bgpPointer = bgpPointer->next;
				}
			}

			// EIGRP Passive
			if (nipper->ios->eigrp != 0)
			{
				eigrpPointer = nipper->ios->eigrp;
				while (eigrpPointer != 0)
				{
					interfacePointer = nipper->ios->interface;
					while (interfacePointer != 0)
					{
						eigrpAutonPointer = eigrpInterfaceConfig(interfacePointer, eigrpPointer->process);
						passivePointer = eigrpPointer->passive;
						while (passivePointer != 0)
						{
							if (strcmp(passivePointer->interface, interfacePointer->name) == 0)
								eigrpAutonPointer->passive = passivePointer->passive;
							passivePointer = passivePointer->next;
						}
						interfacePointer = interfacePointer->next;
					}
					eigrpPointer = eigrpPointer->next;
				}
				eigrpPointer = nipper->ios->eigrp;
				while (eigrpPointer != 0)
				{
					interfacePointer = nipper->ios->interface;
					while (interfacePointer != 0)
					{
						eigrpAutonPointer = eigrpInterfaceConfig(interfacePointer, eigrpPointer->process);
						if (eigrpAutonPointer->passive == unconfigured)
							eigrpAutonPointer->passive = eigrpPointer->defaultPassive;
						interfacePointer = interfacePointer->next;
					}
					eigrpPointer = eigrpPointer->next;
				}
			}

			// OSPF Passive
			if (nipper->ios->ospf != 0)
			{
				ospfPointer = nipper->ios->ospf;
				while (ospfPointer != 0)
				{
					interfacePointer = nipper->ios->interface;
					while (interfacePointer != 0)
					{
						ospfInterPointer = ospfInterfaceConfig(interfacePointer, ospfPointer->processID);
						passivePointer = ospfPointer->passive;
						while (passivePointer != 0)
						{
							if (strcmp(passivePointer->interface, interfacePointer->name) == 0)
								ospfInterPointer->passive = passivePointer->passive;
							passivePointer = passivePointer->next;
						}
						interfacePointer = interfacePointer->next;
					}
					ospfPointer = ospfPointer->next;
				}
				ospfPointer = nipper->ios->ospf;
				while (ospfPointer != 0)
				{
					interfacePointer = nipper->ios->interface;
					while (interfacePointer != 0)
					{
						ospfInterPointer = ospfInterfaceConfig(interfacePointer, ospfPointer->processID);
						if (ospfInterPointer->passive == unconfigured)
							ospfInterPointer->passive = ospfPointer->defaultPassive;
						interfacePointer = interfacePointer->next;
					}
					ospfPointer = ospfPointer->next;
				}
			}

			// RIP Version and Passive
			if (nipper->ios->rip != 0)
			{
				switch (nipper->ios->rip->version)
				{
					case rip_version1:
						setting = rip_version1;			// Send
						setting2 = rip_version1;		// Receive
						break;
					case rip_version2:
						setting = rip_version2;			// Send
						setting2 = rip_version2;		// Receive
						break;
					default:
						setting = rip_version1;			// Send
						setting2 = rip_version1and2;	// Receive
						break;
				}
				interfacePointer = nipper->ios->interface;
				while (interfacePointer != 0)
				{
					passivePointer = nipper->ios->rip->passive;
					while (passivePointer != 0)
					{
						if (strcmp(passivePointer->interface, interfacePointer->name) == 0)
							interfacePointer->ripPassive = passivePointer->passive;
						passivePointer = passivePointer->next;
					}
					if (interfacePointer->ripSendVersion == rip_version_global)
						interfacePointer->ripSendVersion = setting;
					if (interfacePointer->ripReceiveVersion == rip_version_global)
						interfacePointer->ripReceiveVersion = setting2;
					interfacePointer = interfacePointer->next;
				}
				interfacePointer = nipper->ios->interface;
				while (interfacePointer != 0)
				{
					if (interfacePointer->ripPassive == unconfigured)
						interfacePointer->ripPassive = nipper->ios->rip->defaultPassive;
					interfacePointer = interfacePointer->next;
				}
			}

			// Finger
			if (nipper->ios->finger == unconfigured)
			{
				if (((nipper->versionMajor > 11) || ((nipper->versionMajor == 11) && (nipper->versionMinor > 2))) && ((nipper->versionMajor < 12) || ((nipper->versionMajor == 12) && (nipper->versionMinor < 1))))
					nipper->ios->finger = true;
				else
					nipper->ios->finger = false;
			}

			// TCP Small Servers
			if (nipper->ios->tcpSmallServers == unconfigured)
			{
				if ((nipper->versionMajor < 11) || ((nipper->versionMajor == 11) && (nipper->versionMinor < 3)))
					nipper->ios->tcpSmallServers = true;
				else
					nipper->ios->tcpSmallServers = false;
			}

			// UDP Small Servers
			if (nipper->ios->udpSmallServers == unconfigured)
			{
				if ((nipper->versionMajor < 11) || ((nipper->versionMajor == 11) && (nipper->versionMinor < 3)))
					nipper->ios->udpSmallServers = true;
				else
					nipper->ios->udpSmallServers = false;
			}

			// Transport Input Lines Telnet...
			if ((nipper->versionMajor < 11) || ((nipper->versionMajor == 11) && (nipper->versionMinor == 0)))
				setting = true;
			else
				setting = false;
			linePointer = nipper->ios->line;
			while (linePointer != 0)
			{
				if (linePointer->telnet == unconfigured)
					linePointer->telnet = setting;
				linePointer = linePointer->next;
			}
			break;

		// Firewall / PIX
		case type_pix_firewall:
		case type_asa_firewall:
			// SNMP
			if (nipper->pix->snmp == 0)
			{
				nipper->pix->snmp = malloc(sizeof(struct snmpPIXConfig));
				memset(nipper->pix->snmp, 0, sizeof(struct snmpPIXConfig));
				nipper->pix->snmp->enabled = true;
				nipper->pix->snmp->port = 161;
				strcpy(nipper->pix->snmp->community, "public");
				modifyPIXTraps(nipper, "snmp", "authentication", true);
				modifyPIXTraps(nipper, "snmp", "linkup", true);
				modifyPIXTraps(nipper, "snmp", "linkdown", true);
				modifyPIXTraps(nipper, "snmp", "coldstart", true);
				nipper->pix->snmp->weak = true;
				nipper->pix->snmp->dictionary = true;
				nipper->simplePasswords++;
				nipper->passwordStrengths++;
			}
			// SSH Version
			if (nipper->pix->ssh != 0)
			{
				if ((nipper->pix->ssh->version == 0) && ((nipper->versionMajor < 7) || ((nipper->versionMajor == 7) && (nipper->versionMinor == 0) && (nipper->versionRevision == 0))))
					nipper->pix->ssh->version = 1;
			}
		case type_fwsm_firewall:
			break;

		// Catalyst / NMP
		case type_nmp_catalyst:
		case type_cos_catalyst:
			break;

		// Cisco CSS
		case type_css_filter:
			break;

		// ScreenOS
		case type_sos_firewall:
			// Set all unconfigured management services for the management and trust zones, and disabled on all others
			interfaceSOSPointer = nipper->sos->interface;
			while (interfaceSOSPointer != 0)
			{
				if ((strcasecmp(interfaceSOSPointer->zone, "MGT") == 0) || (strcasecmp(interfaceSOSPointer->zone, "Management") == 0) || (strcasecmp(interfaceSOSPointer->zone, "Trust") == 0))
					setting = true;
				else
					setting = false;

				if (interfaceSOSPointer->manageIdent == unconfigured)
					interfaceSOSPointer->manageIdent = setting;
				if (interfaceSOSPointer->manageMtrace == unconfigured)
					interfaceSOSPointer->manageMtrace = setting;
				if (interfaceSOSPointer->manageNsmgmt == unconfigured)
					interfaceSOSPointer->manageNsmgmt = setting;
				if (interfaceSOSPointer->managePing == unconfigured)
					interfaceSOSPointer->managePing = setting;
				if (interfaceSOSPointer->manageSnmp == unconfigured)
					interfaceSOSPointer->manageSnmp = setting;
				if (interfaceSOSPointer->manageSsh == unconfigured)
					interfaceSOSPointer->manageSsh = setting;
				if (interfaceSOSPointer->manageSsl == unconfigured)
					interfaceSOSPointer->manageSsl = setting;
				if (interfaceSOSPointer->manageTelnet == unconfigured)
					interfaceSOSPointer->manageTelnet = setting;
				if (interfaceSOSPointer->manageWeb == unconfigured)
					interfaceSOSPointer->manageWeb = setting;

				interfaceSOSPointer = interfaceSOSPointer->next;
			}
			break;

		// Passport
		case type_passport:
			// Sort out hostname...
			if (nipper->hostname[0] == 0)
				strncpy(nipper->hostname, nipper->pas->boxType, sizeof(nipper->hostname) - 1);
			break;
	}
}

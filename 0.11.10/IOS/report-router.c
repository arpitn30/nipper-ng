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

// This file contains the code for IOS reporting

void iosRoutingConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct interfaceConfig *interfaceConfigPointer = 0;
	struct bgpNeighbor *neighborPointer = 0;
	struct ospfNetworkConfig *ospfNetworkPointer = 0;
	struct ospfAreaConfig *ospfAreaPointer = 0;
	struct ospfNeighbor *ospfNeighborPointer = 0;
	struct ospfConfig *ospfPointer = 0;
	struct ospfInterStruct *ospfInterPointer = 0;
	struct bgpConfig *bgpPointer = 0;
	struct bgpInterStruct *bgpInterPointer = 0;
	struct eigrpConfig *eigrpPointer = 0;
	struct eigrpAutonStruct *eigrpAutonPointer = 0;
	struct eigrpNetwork *eigrpNetworkPointer = 0;
	struct eigrpNeighbor *eigrpNeighborPointer = 0;
	struct staticRoute *routePointer = 0;
	struct routeMapConfig *routeMapPointer = 0;
	struct vrrpStruct *vrrpPointer = 0;
	struct host *hostPointer = 0;
	char tempString[nipper->maxSize];
	char tempString2[nipper->maxSize];

	output_parseText(settings_routing_desc, nipper, section_none, rate_none, 0, 0);

	// Static Routes
	if (nipper->ios->route != 0)
	{
		output_table(nipper, true, settings_static_route_table, &settings_routeIOS_heading);
		routePointer = nipper->ios->route;
		while (routePointer != 0)
		{
			outputFriendly(routePointer->ipAddress, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
			outputFriendly(routePointer->netMask, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
			outputFriendly(routePointer->gateway, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_end);
			routePointer = routePointer->next;
		}
		output_table(nipper, false, settings_static_route_table, &settings_routeIOS_heading);
	}

	// Route Maps
	if (nipper->ios->routeMap != 0)
	{
		output_parseText(settings_routemap_desc, nipper, section_none, rate_none, 0, 0);
		output_table(nipper, true, settings_routemap_table, &settings_routeMap_heading);
		routeMapPointer = nipper->ios->routeMap;
		while (routeMapPointer != 0)
		{
			outputFriendly(routeMapPointer->mapTag, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
			if (routeMapPointer->sequenceNo == 0)
				fprintf(nipper->reportFile, " %s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "%d%s", routeMapPointer->sequenceNo, nipper->tablerow_mid);
			if (routeMapPointer->permission == perm_permit)
				fprintf(nipper->reportFile, "Permit%s", nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "Deny%s", nipper->tablerow_end);
			routeMapPointer = routeMapPointer->next;
		}
		output_table(nipper, false, settings_routemap_table, &settings_routeMap_heading);
	}

	// VRRP
	if (nipper->vrrpIssues != 0)
	{
		output_parseText(settings_vrrp_desc, nipper, section_none, rate_none, 0, 0);
		output_table(nipper, true, settings_vrrp_table, &settings_vrrp_interface_heading);
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			vrrpPointer = interfaceConfigPointer->vrrp;
			while (vrrpPointer != 0)
			{
				outputFriendly(interfaceConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s%d%s", nipper->tablerow_start, tempString, nipper->tablerow_mid, vrrpPointer->group, nipper->tablerow_mid);
				if (vrrpPointer->shutdown == false)
					fprintf(nipper->reportFile, "Active%s", nipper->tablerow_mid);
				else
					fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
				outputFriendly(vrrpPointer->description, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
				fprintf(nipper->reportFile, "%s%s", vrrpPointer->ipAddress, nipper->tablerow_mid);
				if (vrrpPointer->ipAddress2[0] == 0)
					fprintf(nipper->reportFile, " %s", nipper->tablerow_mid);
				else
					fprintf(nipper->reportFile, "%s%s", vrrpPointer->ipAddress2, nipper->tablerow_mid);
				fprintf(nipper->reportFile, "%d%s", vrrpPointer->priorityLevel, nipper->tablerow_mid);
				switch (vrrpPointer->authentication)
				{
					case vrrp_auth_none:
						fprintf(nipper->reportFile, "None%s", nipper->tablerow_mid);
						break;
					case vrrp_auth_text:
						fprintf(nipper->reportFile, "Clear Text%s", nipper->tablerow_mid);
						break;
					case vrrp_auth_md5:
						if (vrrpPointer->keyChain == false)
							fprintf(nipper->reportFile, "MD5%s", nipper->tablerow_mid);
						else
							fprintf(nipper->reportFile, "MD5 Key%s", nipper->tablerow_mid);
						break;
				}
				if (nipper->passwords == true)
				{
					if (vrrpPointer->authString[0] == 0)
						fprintf(nipper->reportFile, " %s", nipper->tablerow_mid);
					else
					{
						outputFriendly(vrrpPointer->authString, tempString, nipper->maxSize, nipper->outputFormat);
						fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
					}
				}
				if (interfaceConfigPointer->shutdown == true)
					fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
				else
					fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
				vrrpPointer = vrrpPointer->next;
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		output_table(nipper, false, settings_vrrp_table, &settings_vrrp_interface_heading);
	}

	// RIP
	if (nipper->ios->rip != 0)
	{
		output_parseText(settings_rip_desc, nipper, section_none, rate_none, 0, 0);
		output_table(nipper, true, settings_rip_table, &settings_general_heading);
		if (nipper->ios->rip->version == rip_version1)
			fprintf(nipper->reportFile, "%sRIP Version%s1%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else if (nipper->ios->rip->version == rip_version2)
			fprintf(nipper->reportFile, "%sRIP Version%s2%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else if (nipper->ios->rip->version == rip_version1and2)
			fprintf(nipper->reportFile, "%sRIP Version%s1 and 2%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		if (nipper->ios->rip->autoSummary == true)
			fprintf(nipper->reportFile, "%sRoute Auto Summarisation%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "%sRoute Auto Summarisation%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		if (nipper->ios->rip->defaultRoute == true)
			fprintf(nipper->reportFile, "%sDefault Route Generation%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "%sDefault Route Generation%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		if (nipper->ios->rip->defaultRouteMap[0] != 0)
		{
			outputFriendly(nipper->ios->rip->defaultRouteMap, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%sDefault Route Route-Map%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
		}
		if (nipper->ios->rip->defaultMetric == -1)
			fprintf(nipper->reportFile, "%sDefault Metric%sAutomatic%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "%sDefault Metric%s%d%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->ios->rip->defaultMetric, nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sInput Queue Depth%s%d%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->ios->rip->inputQueue, nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sRIP Update Delay%s%d milliseconds%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->ios->rip->outputDelay, nipper->tablerow_end);
		if (nipper->ios->rip->validateUpdateSource == true)
			fprintf(nipper->reportFile, "%sValidate Update Source%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "%sValidate Update Source%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		output_table(nipper, false, settings_rip_table, &settings_general_heading);

		// RIP Interfaces
		if (nipper->ios->interface !=0)
		{
			output_table(nipper, true, settings_rip_interface_table, &settings_rip_interface_heading);
			interfaceConfigPointer = nipper->ios->interface;
			while (interfaceConfigPointer != 0)
			{
				// Check interface is valid for OSPF
				if ((interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0) && (interfaceConfigPointer->ripPassive == false))
				{
					outputFriendly(interfaceConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
					outputFriendly(interfaceConfigPointer->description, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
					outputFriendly(interfaceConfigPointer->ipAddress, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
					switch (interfaceConfigPointer->ripAuthMode)
					{
						case rip_auth_none:
							fprintf(nipper->reportFile, "None%s", nipper->tablerow_mid);
							break;
						case rip_auth_text:
							fprintf(nipper->reportFile, "Clear Text%s", nipper->tablerow_mid);
							break;
						case rip_auth_md5:
							fprintf(nipper->reportFile, "MD5%s", nipper->tablerow_mid);
							break;
						default:
							fprintf(nipper->reportFile, " %s", nipper->tablerow_mid);
							break;
					}
					if (interfaceConfigPointer->ripKeyChain[0] == 0)
						fprintf(nipper->reportFile, " %s", nipper->tablerow_mid);
					else
					{
						outputFriendly(interfaceConfigPointer->ripKeyChain, tempString, nipper->maxSize, nipper->outputFormat);
						fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
					}
					switch (interfaceConfigPointer->ripSendVersion)
					{
						case rip_version1:
							fprintf(nipper->reportFile, "1%s", nipper->tablerow_mid);
							break;
						case rip_version2:
							fprintf(nipper->reportFile, "2%s", nipper->tablerow_mid);
							break;
						case rip_version1and2:
							fprintf(nipper->reportFile, "1 and 2%s", nipper->tablerow_mid);
							break;
						case rip_version_global:
							switch (nipper->ios->rip->version)
							{
								case rip_version1:
									fprintf(nipper->reportFile, "1%s", nipper->tablerow_mid);
									break;
								case rip_version2:
									fprintf(nipper->reportFile, "2%s", nipper->tablerow_mid);
									break;
								case rip_version1and2:
									fprintf(nipper->reportFile, "1 and 2%s", nipper->tablerow_mid);
									break;
							}
							break;
					}
					switch (interfaceConfigPointer->ripReceiveVersion)
					{
						case rip_version1:
							fprintf(nipper->reportFile, "1%s", nipper->tablerow_mid);
							break;
						case rip_version2:
							fprintf(nipper->reportFile, "2%s", nipper->tablerow_mid);
							break;
						case rip_version1and2:
							fprintf(nipper->reportFile, "1 and 2%s", nipper->tablerow_mid);
							break;
						case rip_version_global:
							switch (nipper->ios->rip->version)
							{
								case rip_version1:
									fprintf(nipper->reportFile, "1%s", nipper->tablerow_mid);
									break;
								case rip_version2:
									fprintf(nipper->reportFile, "2%s", nipper->tablerow_mid);
									break;
								case rip_version1and2:
									fprintf(nipper->reportFile, "1 and 2%s", nipper->tablerow_mid);
									break;
							}
							break;
					}
					switch (interfaceConfigPointer->ripV2Broadcast)
					{
						case true:
							fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
							break;
						case false:
							fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
							break;
					}
					switch (interfaceConfigPointer->ripTriggered)
					{
						case true:
							fprintf(nipper->reportFile, "On%s", nipper->tablerow_end);
							break;
						case false:
							fprintf(nipper->reportFile, "Off%s", nipper->tablerow_end);
							break;
					}
				}
				interfaceConfigPointer = interfaceConfigPointer->next;
			}
			output_table(nipper, false, settings_rip_interface_table, &settings_rip_interface_heading);
		}

		if (nipper->ios->rip->neighbor != 0)
		{
			hostPointer = nipper->ios->rip->neighbor;
			output_table(nipper, true, settings_rip_neightbor_table, &settings_rip_neightbor_heading);
			while (hostPointer != 0)
			{
				outputFriendly(hostPointer->server, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_end);
				hostPointer = hostPointer->next;
			}
			output_table(nipper, false, settings_rip_neightbor_table, &settings_rip_neightbor_heading);
		}

		if (nipper->ios->rip->network != 0)
		{
			hostPointer = nipper->ios->rip->network;
			output_table(nipper, true, settings_rip_networks_table, &settings_rip_networks_heading);
			while (hostPointer != 0)
			{
				outputFriendly(hostPointer->server, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_end);
				hostPointer = hostPointer->next;
			}
			output_table(nipper, false, settings_rip_networks_table, &settings_rip_networks_heading);
		}
		addAbbreviation("RIP", false);
	}

	// EIGRP
	if (nipper->ios->eigrp != 0)
	{
		output_parseText(settings_eigrp_desc, nipper, section_none, rate_none, 0, 0);

		// EIGRP Configuration
		eigrpPointer = nipper->ios->eigrp;
		while (eigrpPointer != 0)
		{
			sprintf(tempString, "EIGRP autonomous number %d configuration", eigrpPointer->process);
			output_table(nipper, true, tempString, &settings_general_heading);
			fprintf(nipper->reportFile, "%sRouter ID%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, eigrpPointer->routerId, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sMaximum Hops%s%d%s", nipper->tablerow_start, nipper->tablerow_mid, eigrpPointer->maximumHops, nipper->tablerow_end);
			switch (eigrpPointer->stub)
			{
				case eigrp_stub_disabled:
					fprintf(nipper->reportFile, "%sEIGRP Stub Router%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
				case eigrp_stub_enabled:
					fprintf(nipper->reportFile, "%sEIGRP Stub Router%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
				case eigrp_stub_receive:
					fprintf(nipper->reportFile, "%sEIGRP Stub Router%sReceive Only%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
				case eigrp_stub_connected:
					fprintf(nipper->reportFile, "%sEIGRP Stub Router%sAdvertise Connected Routes%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
				case eigrp_stub_static:
					fprintf(nipper->reportFile, "%sEIGRP Stub Router%sAdvertise Static Routes%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
				case eigrp_stub_summary:
					fprintf(nipper->reportFile, "%sEIGRP Stub Router%sAdvertise Summary Routes%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
				case eigrp_stub_redist:
					fprintf(nipper->reportFile, "%sEIGRP Stub Router%sAdvertise Redistributed Routes%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
			}
			if (eigrpPointer->autoSummary == true)
				fprintf(nipper->reportFile, "%sAuto Summary%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "%sAuto Summary%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sInternal Administrative Distance%s%d%s", nipper->tablerow_start, nipper->tablerow_mid, eigrpPointer->internalDistance, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sExternal Administrative Distance%s%d%s", nipper->tablerow_start, nipper->tablerow_mid, eigrpPointer->externalDistance, nipper->tablerow_end);
			if (eigrpPointer->logNeighborChanges == true)
				fprintf(nipper->reportFile, "%sLog Neighbor Changes%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "%sLog Neighbor Changes%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			if (eigrpPointer->logNeighborWarnings == true)
				fprintf(nipper->reportFile, "%sLog Neighbor Warnings%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "%sLog Neighbor Warnings%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			eigrpNetworkPointer = eigrpPointer->network;
			while (eigrpNetworkPointer != 0)
			{
				fprintf(nipper->reportFile, "%sNetwork IP Address%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, eigrpNetworkPointer->ipAddress, nipper->tablerow_end);
				if (eigrpNetworkPointer->netMask[0] != 0)
					fprintf(nipper->reportFile, "%sNetwork Netmask%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, eigrpNetworkPointer->netMask, nipper->tablerow_end);
				eigrpNetworkPointer = eigrpNetworkPointer->next;
			}
			eigrpNeighborPointer = eigrpPointer->neighbor;
			while (eigrpNeighborPointer != 0)
			{
				fprintf(nipper->reportFile, "%sNetwork IP Address%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, eigrpNeighborPointer->ipAddress, nipper->tablerow_end);
				if (eigrpNeighborPointer->interface[0] != 0)
					fprintf(nipper->reportFile, "%sNetwork Interface%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, eigrpNeighborPointer->interface, nipper->tablerow_end);
				eigrpNeighborPointer = eigrpNeighborPointer->next;
			}
			output_table(nipper, false, tempString, &settings_general_heading);

			// Interfaces
			sprintf(tempString2, "EIGRP autonomous number %d interface configuration", eigrpPointer->process);
			output_table(nipper, true, tempString2, &settings_eigrp_interface_heading);
			interfaceConfigPointer = nipper->ios->interface;
			while (interfaceConfigPointer != 0)
			{
				eigrpAutonPointer = eigrpInterfaceConfig(interfaceConfigPointer, eigrpPointer->process);
				outputFriendly(interfaceConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
				outputFriendly(interfaceConfigPointer->description, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
				outputFriendly(interfaceConfigPointer->ipAddress, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
				if (interfaceConfigPointer->shutdown == true)
					fprintf(nipper->reportFile, "No%s", nipper->tablerow_mid);
				else
					fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_mid);
				if (eigrpAutonPointer->passive == true)
					fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_mid);
				else
					fprintf(nipper->reportFile, "No%s", nipper->tablerow_mid);
				if (eigrpAutonPointer->md5Auth == true)
					fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_mid);
				else
					fprintf(nipper->reportFile, "No%s", nipper->tablerow_mid);
				if (eigrpAutonPointer->keyChain[0] == 0)
					fprintf(nipper->reportFile, " %s", nipper->tablerow_mid);
				else
					fprintf(nipper->reportFile, "%s%s", eigrpAutonPointer->keyChain, nipper->tablerow_mid);
				fprintf(nipper->reportFile, "%d%%%s", eigrpAutonPointer->bandwidth, nipper->tablerow_end);
				interfaceConfigPointer = interfaceConfigPointer->next;
			}
			output_table(nipper, false, tempString2, &settings_eigrp_interface_heading);

			// Increment EIGRP Autonomous No.
			eigrpPointer = eigrpPointer->next;
		}
	}

	// BGP
	if (nipper->ios->bgp != 0)
	{
		output_parseText(settings_bgp_desc, nipper, section_none, rate_none, 0, 0);
		bgpPointer = nipper->ios->bgp;
		while (bgpPointer != 0)
		{
			sprintf(tempString, "BGP autonomous number %d configuration", bgpPointer->autonomousNo);
			output_table(nipper, true, tempString, &settings_general_heading);
			fprintf(nipper->reportFile, "%sAutonomous Number%s%d%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->ios->bgp->autonomousNo, nipper->tablerow_end);
			if (bgpPointer->logNeighborChanges == true)
				fprintf(nipper->reportFile, "%sLog Neighbor Changes%sYes%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "%sLog Neighbor Changes%sNo%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			if (bgpPointer->dampening == true)
				fprintf(nipper->reportFile, "%sRoute Flap Dampening%sOn%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "%sRoute Flap Dampening%sOff%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			output_table(nipper, false, tempString, &settings_general_heading);

			if (bgpPointer->neighbor != 0)
			{
				sprintf(tempString2, "BGP autonomous number %d neighbors", bgpPointer->autonomousNo);
				output_table(nipper, true, tempString2, &settings_bgp_heading);
				neighborPointer = bgpPointer->neighbor;
				while (neighborPointer != 0)
				{
					outputFriendly(neighborPointer->host, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
					outputFriendly(neighborPointer->description, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
					if (nipper->passwords == true)
					{
						outputFriendly(neighborPointer->password, tempString, nipper->maxSize, nipper->outputFormat);
						fprintf(nipper->reportFile, "%s %s", tempString, nipper->tablerow_mid);
					}
					switch (neighborPointer->encryption)
					{
						case encrypt_type7:
							fprintf(nipper->reportFile, "Type-7%s", nipper->tablerow_mid);
							break;
						case encrypt_md5:
							fprintf(nipper->reportFile, "MD5%s", nipper->tablerow_mid);
							addAbbreviation("MD5", false);
							break;
						case encrypt_none:
							if (neighborPointer->password[0] == 0)
								fprintf(nipper->reportFile, " %s", nipper->tablerow_mid);
							else
								fprintf(nipper->reportFile, "None%s", nipper->tablerow_mid);
							break;
						case encrypt_unknown:
							fprintf(nipper->reportFile, "Unknown%s", nipper->tablerow_mid);
							break;
					}
					if (neighborPointer->autonomousNo != -1)
						fprintf(nipper->reportFile, "%d%s", neighborPointer->autonomousNo, nipper->tablerow_mid);
					else
						fprintf(nipper->reportFile, " %s", nipper->tablerow_mid);
					if (neighborPointer->ttlHops == -1)
						fprintf(nipper->reportFile, "Off%s", nipper->tablerow_end);
					else
						fprintf(nipper->reportFile, "%d%s", neighborPointer->ttlHops, nipper->tablerow_end);
					neighborPointer = neighborPointer->next;
				}
				output_table(nipper, false, tempString2, &settings_bgp_heading);
			}

			// Interfaces
			sprintf(tempString2, "BGP autonomous number %d interface configuration", bgpPointer->autonomousNo);
			output_table(nipper, true, tempString2, &settings_bgp_interface_heading);
			interfaceConfigPointer = nipper->ios->interface;
			while (interfaceConfigPointer != 0)
			{
				bgpInterPointer = bgpInterfaceConfig(interfaceConfigPointer, bgpPointer->autonomousNo);
				outputFriendly(interfaceConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
				outputFriendly(interfaceConfigPointer->description, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
				outputFriendly(interfaceConfigPointer->ipAddress, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
				if (interfaceConfigPointer->shutdown == true)
					fprintf(nipper->reportFile, "No%s", nipper->tablerow_mid);
				else
					fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_mid);
				if (bgpInterPointer->passive == true)
					fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
				else
					fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
				interfaceConfigPointer = interfaceConfigPointer->next;
			}
			output_table(nipper, false, tempString2, &settings_bgp_interface_heading);

			bgpPointer = bgpPointer->next;
		}
		addAbbreviation("BGP", false);
		addAbbreviation("TTL", false);
	}

	// OSPF
	if (nipper->ios->ospf != 0)
	{
		output_parseText(settings_ospf_desc, nipper, section_none, rate_none, 0, 0);

		ospfPointer = nipper->ios->ospf;
		while (ospfPointer != 0)
		{
			// OSPF Network
			if (nipper->ios->ospf->ospfNetwork != 0)
			{
				sprintf(tempString2, "OSPF process ID %d network areas", ospfPointer->processID);
				output_table(nipper, true, tempString2, &settings_ospf_network_heading);
				ospfNetworkPointer = nipper->ios->ospf->ospfNetwork;
				while (ospfNetworkPointer != 0)
				{
					fprintf(nipper->reportFile, "%s%s%s%s%s%s%s", nipper->tablerow_start, ospfNetworkPointer->network, nipper->tablerow_mid, ospfNetworkPointer->networkMask, nipper->tablerow_mid, ospfNetworkPointer->areaID, nipper->tablerow_end);
					ospfNetworkPointer = ospfNetworkPointer->next;
				}
				output_table(nipper, false, tempString2, &settings_ospf_network_heading);
			}

			// OSPF Areas
			if (nipper->ios->ospf->ospfArea != 0)
			{
				sprintf(tempString2, "OSPF process ID %d area configuration", ospfPointer->processID);
				output_table(nipper, true, tempString2, &settings_ospf_area_heading);
				ospfAreaPointer = nipper->ios->ospf->ospfArea;
				while (ospfAreaPointer != 0)
				{
					switch (ospfAreaPointer->areaAuth)
					{
						case auth_none:
							fprintf(nipper->reportFile, "%s%s%s%d%sNone%s", nipper->tablerow_start, ospfAreaPointer->areaID, nipper->tablerow_mid, ospfAreaPointer->defaultCost, nipper->tablerow_mid, nipper->tablerow_end);
							break;
						case auth_clear:
							fprintf(nipper->reportFile, "%s%s%s%d%sClear-text%s", nipper->tablerow_start, ospfAreaPointer->areaID, nipper->tablerow_mid, ospfAreaPointer->defaultCost, nipper->tablerow_mid, nipper->tablerow_end);
							break;
						case auth_md5:
							fprintf(nipper->reportFile, "%s%s%s%d%sMD5%s", nipper->tablerow_start, ospfAreaPointer->areaID, nipper->tablerow_mid, ospfAreaPointer->defaultCost, nipper->tablerow_mid, nipper->tablerow_end);
							break;
					}
					ospfAreaPointer = ospfAreaPointer->next;
				}
				output_table(nipper, false, tempString2, &settings_ospf_area_heading);
			}

			// OSPF Interfaces
			if (nipper->ios->interface !=0)
			{
				sprintf(tempString2, "OSPF process ID %d interface configuration", ospfPointer->processID);
				output_table(nipper, true, tempString2, &settings_ospf_interface_heading);
				interfaceConfigPointer = nipper->ios->interface;
				while (interfaceConfigPointer != 0)
				{
					// Check interface is valid for OSPF
					ospfInterPointer = ospfInterfaceConfig(interfaceConfigPointer, ospfPointer->processID);
					if ((interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0) && (ospfInterPointer->passive == false) && (ospfInterPointer->processID == ospfPointer->processID))
					{
						outputFriendly(interfaceConfigPointer->description, tempString, nipper->maxSize, nipper->outputFormat);
						fprintf(nipper->reportFile, "%s%s%s%s%s%s%s", nipper->tablerow_start, interfaceConfigPointer->name, nipper->tablerow_mid, tempString, nipper->tablerow_mid, interfaceConfigPointer->ipAddress, nipper->tablerow_mid);
						switch (interfaceConfigPointer->ospfAuthentication)
						{
							case auth_none:
								fprintf(nipper->reportFile, "None%s", nipper->tablerow_mid);
								break;
							case auth_clear:
								fprintf(nipper->reportFile, "Clear-Text%s", nipper->tablerow_mid);
								break;
							case auth_md5:
								fprintf(nipper->reportFile, "MD5%s", nipper->tablerow_mid);
								addAbbreviation("MD5", false);
								break;
						}
						if (nipper->passwords == true)
						{
							outputFriendly(interfaceConfigPointer->ospfKey, tempString, nipper->maxSize, nipper->outputFormat);
							fprintf(nipper->reportFile, "%s %s", tempString, nipper->tablerow_mid);
						}
						switch (interfaceConfigPointer->ospfKeyEncryption)
						{
							case encrypt_type7:
								fprintf(nipper->reportFile, "Type-7%s", nipper->tablerow_mid);
								break;
							case encrypt_md5:
								fprintf(nipper->reportFile, "MD5%s", nipper->tablerow_mid);
								addAbbreviation("MD5", false);
								break;
							case encrypt_none:
								fprintf(nipper->reportFile, "None%s", nipper->tablerow_mid);
								break;
							case encrypt_unknown:
								fprintf(nipper->reportFile, "Unknown%s", nipper->tablerow_mid);
								break;
						}
						switch (interfaceConfigPointer->ospfFloodReduction)
						{
							case true:
								fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
								break;
							case false:
								fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
								break;
							case unconfigured:
								fprintf(nipper->reportFile, "N/A%s", nipper->tablerow_mid);
								break;
						}
						switch (interfaceConfigPointer->ospfNetwork)
						{
							case ospf_default:
								fprintf(nipper->reportFile, "Default");
								break;
							case ospf_broadcast:
								fprintf(nipper->reportFile, "Broadcast");
								break;
							case ospf_nonbroadcast:
								fprintf(nipper->reportFile, "Non-Broadcast");
								break;
							case ospf_p2p:
								fprintf(nipper->reportFile, "Point to Point");
								addAbbreviation("PPP", false);
								break;
							case ospf_p2multi:
								fprintf(nipper->reportFile, "Point to Multipoint");
								break;
							case ospf_p2multinon:
								fprintf(nipper->reportFile, "Point to Multipoint (Non-Broadcast)");
								break;
						}
						fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
					}
					interfaceConfigPointer = interfaceConfigPointer->next;
				}
				output_table(nipper, false, tempString2, &settings_ospf_interface_heading);
			}

			// OSPF Neighbors
			if (nipper->ios->ospf->neighbor != 0)
			{
				sprintf(tempString2, "OSPF process ID %d neighbor configuration", ospfPointer->processID);
				output_table(nipper, true, tempString2, &settings_ospf_neighbor_heading);
				ospfNeighborPointer = nipper->ios->ospf->neighbor;
				while (ospfNeighborPointer != 0)
				{
					fprintf(nipper->reportFile, "%s%s%s%d%s%d%s%d%s", nipper->tablerow_start, ospfNeighborPointer->host, nipper->tablerow_mid, ospfNeighborPointer->priority, nipper->tablerow_mid, ospfNeighborPointer->pollInterval, nipper->tablerow_mid, ospfNeighborPointer->costNumber, nipper->tablerow_mid);
					if (ospfNeighborPointer->databaseFilter == false)
						fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
					else
						fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
					ospfNeighborPointer = ospfNeighborPointer->next;
				}
				output_table(nipper, false, tempString2, &settings_ospf_neighbor_heading);
			}

			ospfPointer = ospfPointer->next;
		}
	}
}


void iosBGPDampeningIssue(struct nipperConfig *nipper)
{
	output_parseText(report_bgpdamp_obs, nipper, section_obs, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_bgpdamp_impact, nipper, section_imp, rate_high, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_bgpdamp_ease, nipper, section_ease, rate_moderate, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_bgpdamp_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosOSPFAuthenticationIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct ospfAreaConfig *ospfAreaPointer = 0;
	struct ospfConfig *ospfPointer = 0;

	output_parseText(report_ospfauth_obs1, nipper, section_obs, rate_none, 0, nipper->tableNum);
	if (nipper->ospfAuthMD5 > 0)
		output_parseText(report_ospfauth_obs2, nipper, section_none, rate_none, nipper->ospfAuthNoneIssues, nipper->tableNum);
	if ((nipper->ospfAuthNoneIssues > 0) && (nipper->ospfAuthClearIssues > 0))
		output_parseText(report_ospfauth_obs3, nipper, section_none, rate_none, nipper->ospfAuthNoneIssues + nipper->ospfAuthClearIssues, nipper->tableNum);
	else if (nipper->ospfAuthNoneIssues > 0)
		output_parseText(report_ospfauth_obs4, nipper, section_none, rate_none, nipper->ospfAuthNoneIssues, nipper->tableNum);
	else
		output_parseText(report_ospfauth_obs5, nipper, section_none, rate_none, nipper->ospfAuthClearIssues, nipper->tableNum);
	if (nipper->ospfAuthNoneIssues + nipper->ospfAuthClearIssues > 1)
	{
		output_table(nipper, true, report_ospfauth_table, &report_ospfauth_heading);
		ospfPointer = nipper->ios->ospf;
		while (ospfPointer != 0)
		{
			ospfAreaPointer = ospfPointer->ospfArea;
			if (ospfAreaPointer == 0)
				fprintf(nipper->reportFile, "%s%d%sN/A%sNo Authentication%s", nipper->tablerow_start, ospfPointer->processID, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			while (ospfAreaPointer != 0)
			{
				if (ospfAreaPointer->areaAuth == auth_none)
					fprintf(nipper->reportFile, "%s%d%s%s%sNo Authentication%s", nipper->tablerow_start, ospfPointer->processID, nipper->tablerow_mid, ospfAreaPointer->areaID, nipper->tablerow_mid, nipper->tablerow_end);
				else if (ospfAreaPointer->areaAuth == auth_clear)
					fprintf(nipper->reportFile, "%s%d%s%s%sClear-text Authentication%s", nipper->tablerow_start, ospfPointer->processID, nipper->tablerow_mid, ospfAreaPointer->areaID, nipper->tablerow_mid, nipper->tablerow_end);
				ospfAreaPointer = ospfAreaPointer->next;
			}
			ospfPointer = ospfPointer->next;
		}
		output_table(nipper, false, report_ospfauth_table, &report_ospfauth_heading);
	}
	else
	{
		ospfPointer = nipper->ios->ospf;
		while (ospfPointer != 0)
		{
			ospfAreaPointer = ospfPointer->ospfArea;
			if (ospfAreaPointer == 0)
				fprintf(nipper->reportFile, "%d.", ospfPointer->processID);
			while (ospfAreaPointer != 0)
			{
				if (ospfAreaPointer->areaAuth == auth_none)
					fprintf(nipper->reportFile, "%d area %s.", ospfPointer->processID, ospfAreaPointer->areaID);
				else if (ospfAreaPointer->areaAuth == auth_clear)
					fprintf(nipper->reportFile, "%d area %s.", ospfPointer->processID, ospfAreaPointer->areaID);
				ospfAreaPointer = ospfAreaPointer->next;
			}
			ospfPointer = ospfPointer->next;
		}
		output_parseText(endottext, nipper, section_none, rate_none, nipper->ospfAuthNoneIssues, nipper->tableNum);
	}
	output_endsection(nipper, section_obs);
	output_parseText(report_ospfauth_impact, nipper, section_imp, rate_high, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_ospfauth_ease, nipper, section_ease, rate_moderate, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_ospfauth_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosEIGRPIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct interfaceConfig *interfaceConfigPointer = 0;
	struct eigrpAutonStruct *eigrpAutonPointer = 0;
	//struct eigrpConfig *eigrpPointer = 0;
	int tempInt = 0;
	int tempInt2 = 0;
	char tempString[nipper->maxSize];

	output_parseText(report_eigrpauth_obs1, nipper, section_obs, rate_none, nipper->eigrpIssues, nipper->tableNum);
	tempInt2 = 0;
	//eigrpPointer = nipper->ios->eigrp;
	//while (eigrpPointer != 0)
	//{
	//	tempInt2++;
	//	eigrpPointer = eigrpPointer->next;
	//}
	if (nipper->eigrpIssues > 1)
	{
		output_table(nipper, true, report_eigrpauth_table, &report_interface_heading);
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
			{
				tempInt = tempInt2;
				eigrpAutonPointer = interfaceConfigPointer->eigrp;
				while (eigrpAutonPointer != 0)
				{
					if ((eigrpAutonPointer->md5Auth == false) && (eigrpAutonPointer->passive != true))
					{
						outputFriendly(interfaceConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
						fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
						outputFriendly(interfaceConfigPointer->description, tempString, nipper->maxSize, nipper->outputFormat);
						fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_end);
					}
					eigrpAutonPointer = eigrpAutonPointer->next;
				}
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		output_table(nipper, false, report_eigrpauth_table, &report_interface_heading);
	}
	else
	{
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
			{
				tempInt = tempInt2;
				eigrpAutonPointer = interfaceConfigPointer->eigrp;
				while (eigrpAutonPointer != 0)
				{
					if ((eigrpAutonPointer->md5Auth == false) && (eigrpAutonPointer->passive != true))
					{
						outputFriendly(interfaceConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
						fprintf(nipper->reportFile, "%s", tempString);
						output_parseText(report_eigrpauth_obs2, nipper, section_none, rate_none, nipper->eigrpIssues, 0);
					}
					eigrpAutonPointer = eigrpAutonPointer->next;
				}
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
	}
	output_endsection(nipper, section_obs);
	output_parseText(report_eigrpauth_impact, nipper, section_imp, rate_high, nipper->eigrpIssues, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_eigrpauth_ease, nipper, section_ease, rate_moderate, nipper->eigrpIssues, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_eigrpauth_rec, nipper, section_rec, rate_none, nipper->eigrpIssues, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosRIPIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct interfaceConfig *interfaceConfigPointer = 0;
	char tempString[nipper->maxSize];

	output_parseText(report_rip_obs, nipper, section_obs, rate_none, nipper->ripIssues, nipper->tableNum);
	if (nipper->ripIssues == 1)
	{
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if (((interfaceConfigPointer->ripKeyChain[0] == 0) || (interfaceConfigPointer->ripAuthMode != rip_auth_md5) || (interfaceConfigPointer->ripSendVersion != rip_version2) || (interfaceConfigPointer->ripReceiveVersion != rip_version2)) && (interfaceConfigPointer->ripPassive == false) && (interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
				fprintf(nipper->reportFile, "%s.", interfaceConfigPointer->name);
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		output_newPara(nipper);
	}
	else
	{
		output_table(nipper, true, report_rip_table, &report_interface_heading);
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if (((interfaceConfigPointer->ripKeyChain[0] == 0) || (interfaceConfigPointer->ripAuthMode != rip_auth_md5) || (interfaceConfigPointer->ripSendVersion != rip_version2) || (interfaceConfigPointer->ripReceiveVersion != rip_version2)) && (interfaceConfigPointer->ripPassive == false) && (interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
			{
				outputFriendly(interfaceConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
				if ((interfaceConfigPointer->ripKeyChain[0] == 0) && (interfaceConfigPointer->ripAuthMode != rip_auth_md5))
					fprintf(nipper->reportFile, "%s%s", report_rip_tab_desc1, nipper->tablerow_end);
				else if (interfaceConfigPointer->ripKeyChain[0] == 0)
					fprintf(nipper->reportFile, "%s%s", report_rip_tab_desc2, nipper->tablerow_end);
				else if (interfaceConfigPointer->ripAuthMode != rip_auth_md5)
					fprintf(nipper->reportFile, "%s%s", report_rip_tab_desc3, nipper->tablerow_end);
				else if ((interfaceConfigPointer->ripSendVersion != rip_version2) && (interfaceConfigPointer->ripReceiveVersion != rip_version2))
					fprintf(nipper->reportFile, "%s %s", report_rip_tab_desc4, nipper->tablerow_end);
				else if (interfaceConfigPointer->ripSendVersion != rip_version2)
					fprintf(nipper->reportFile, "%s %s", report_rip_tab_desc5, nipper->tablerow_end);
				else
					fprintf(nipper->reportFile, "%s %s", report_rip_tab_desc6, nipper->tablerow_end);
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		output_table(nipper, false, report_rip_table, &report_interface_heading);
	}
	output_endsection(nipper, section_obs);
	output_parseText(report_rip_impact, nipper, section_imp, rate_high, nipper->ripIssues, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_rip_ease, nipper, section_ease, rate_moderate, nipper->ripIssues, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_rip_rec, nipper, section_rec, rate_none, nipper->ripIssues, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosVRRPIssue(struct nipperConfig *nipper)
{
	output_parseText(report_vrrp_obs, nipper, section_obs, rate_none, nipper->vrrpIssues, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_vrrp_impact, nipper, section_imp, rate_high, nipper->vrrpIssues, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_vrrp_ease, nipper, section_ease, rate_moderate, nipper->vrrpIssues, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_vrrp_rec, nipper, section_rec, rate_none, nipper->vrrpIssues, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosSourceRoutingIssue(struct nipperConfig *nipper)
{
	output_parseText(report_source_obs, nipper, section_obs, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_source_impact, nipper, section_imp, rate_med, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_source_ease, nipper, section_ease, rate_trivial, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_source_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosRedirectsIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct interfaceConfig *interfaceConfigPointer = 0;
	char tempString[nipper->maxSize];

	output_parseText(report_redirects_obs, nipper, section_obs, rate_none, nipper->redirectsIssues, nipper->tableNum);
	if (nipper->redirectsIssues == 1)
	{
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->ipRedirects == true) && (interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
				fprintf(nipper->reportFile, "%s.", interfaceConfigPointer->name);
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		output_newPara(nipper);
	}
	else
	{
		output_table(nipper, true, report_redirects_table, &report_interface_heading);
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->ipRedirects == true) && (interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
			{
				outputFriendly(interfaceConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
				outputFriendly(interfaceConfigPointer->description, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s %s", tempString, nipper->tablerow_end);
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		output_table(nipper, false, report_redirects_table, &report_interface_heading);
	}
	output_endsection(nipper, section_obs);
	output_parseText(report_redirects_impact, nipper, section_imp, rate_med, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_redirects_ease, nipper, section_ease, rate_trivial, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_redirects_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosURPFIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct interfaceConfig *interfaceConfigPointer = 0;
	char tempString[nipper->maxSize];

	output_parseText(report_urpf_obs, nipper, section_obs, rate_none, nipper->uRPFIssues, nipper->tableNum);
	if (nipper->uRPFIssues > 1)
	{
		interfaceConfigPointer = nipper->ios->interface;
		output_table(nipper, true, report_urpf_table, &report_interface_heading);
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->uRPF == false) && (interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
			{
				outputFriendly(interfaceConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
				outputFriendly(interfaceConfigPointer->description, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s %s", tempString, nipper->tablerow_end);
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		output_table(nipper, false, report_urpf_table, &report_interface_heading);
	}
	else if (nipper->uRPFIssues > 0)
	{
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->uRPF == false) && (interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
			{
				outputFriendly(interfaceConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s.", tempString);
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		output_newPara(nipper);
	}
	output_endsection(nipper, section_obs);
	output_parseText(report_urpf_impact, nipper, section_imp, rate_med, nipper->uRPFIssues, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_urpf_ease, nipper, section_ease, rate_noease, nipper->uRPFIssues, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_urpf_rec, nipper, section_rec, rate_none, nipper->uRPFIssues, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosClasslessRoutingIssue(struct nipperConfig *nipper)
{
	output_parseText(report_classless_obs, nipper, section_obs, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_classless_impact, nipper, section_imp, rate_low, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_classless_ease, nipper, section_ease, rate_noease, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_classless_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}



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


void cleanupIOS(struct nipperConfig *nipper)
{
	// Pointers...
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
	struct staticRoute *routePointer = 0;
	struct routeMapConfig *routeMapPointer = 0;
	struct natConfig *natPointer = 0;
	struct host *hostPointer = 0;
	struct passiveStruct *passivePointer = 0;
	struct eigrpConfig *eigrpPointer = 0;
	struct eigrpNetwork *eigrpNetworkPointer = 0;
	struct eigrpNeighbor *eigrpNeighborPointer = 0;
	struct eigrpAutonStruct *eigrpAutonPointer = 0;
	struct ospfInterStruct *ospfInterPointer = 0;
	struct bgpInterStruct *bgpInterPointer = 0;
	struct bgpConfig *bgpPointer = 0;
	struct vrrpStruct *vrrpPointer = 0;

	// Cleanup EIGRP
	while (nipper->ios->eigrp != 0)
	{
		eigrpPointer = nipper->ios->eigrp->next;
		while (nipper->ios->eigrp->network != 0)
		{
			eigrpNetworkPointer = nipper->ios->eigrp->network->next;
			free (nipper->ios->eigrp->network);
			nipper->ios->eigrp->network = eigrpNetworkPointer;
		}
		while (nipper->ios->eigrp->neighbor != 0)
		{
			eigrpNeighborPointer = nipper->ios->eigrp->neighbor->next;
			free (nipper->ios->eigrp->neighbor);
			nipper->ios->eigrp->neighbor = eigrpNeighborPointer;
		}
		while (nipper->ios->eigrp->passive != 0)
		{
			passivePointer = nipper->ios->eigrp->passive->next;
			free(nipper->ios->eigrp->passive);
			nipper->ios->eigrp->passive = passivePointer;
		}
		free (nipper->ios->eigrp);
		nipper->ios->eigrp = eigrpPointer;
	}

	// Cleanup NAT
	while (nipper->ios->nat != 0)
	{
		natPointer = nipper->ios->nat->next;
		free (nipper->ios->nat);
		nipper->ios->nat = natPointer;
	}

	// Cleanup Route Map
	while (nipper->ios->routeMap != 0)
	{
		routeMapPointer = nipper->ios->routeMap->next;
		free (nipper->ios->routeMap);
		nipper->ios->routeMap = routeMapPointer;
	}

	// Cleanup enable passwords
	while (nipper->ios->enable != 0)
	{
		enablePointer = nipper->ios->enable->next;
		free(nipper->ios->enable);
		nipper->ios->enable = enablePointer;
	}

	// Cleanup usernames
	while (nipper->ios->username != 0)
	{
		usernamePointer = nipper->ios->username->next;
		free(nipper->ios->username);
		nipper->ios->username = usernamePointer;
	}

	// Cleanup DNS servers
	while (nipper->ios->dns != 0)
	{
		logServerPointer = nipper->ios->dns->next;
		free(nipper->ios->dns);
		nipper->ios->dns = logServerPointer;
	}

	// Cleanup Privilages
	while (nipper->ios->privilage != 0)
	{
		privilagePointer = nipper->ios->privilage->next;
		free(nipper->ios->privilage);
		nipper->ios->privilage = privilagePointer;
	}

	// Cleanup Route
	while (nipper->ios->route != 0)
	{
		routePointer = nipper->ios->route->next;
		free(nipper->ios->route);
		nipper->ios->route = routePointer;
	}

	// Cleanup HTTP
	if (nipper->ios->http != 0)
		free(nipper->ios->http);

	// Cleanup Key Chain
	while (nipper->ios->chain != 0)
	{
		while (nipper->ios->chain->key != 0)
		{
			keyPointer = nipper->ios->chain->key->next;
			free (nipper->ios->chain->key);
			nipper->ios->chain->key = keyPointer;
		}
		keyChainPointer = nipper->ios->chain->next;
		free (nipper->ios->chain);
		nipper->ios->chain = keyChainPointer;
	}

	// Cleanup SSH
	if (nipper->ios->ssh != 0)
	{
		while (nipper->ios->ssh->interface != 0)
		{
			interfacePointer = nipper->ios->ssh->interface->next;
			free(nipper->ios->ssh->interface);
			nipper->ios->ssh->interface = interfacePointer;
		}
		free(nipper->ios->ssh);
	}

	// Cleanup Line
	while (nipper->ios->line != 0)
	{
		linePointer = nipper->ios->line->next;
		free(nipper->ios->line);
		nipper->ios->line = linePointer;
	}

	// Cleanup BGP
	while (nipper->ios->bgp != 0)
	{
		bgpPointer = nipper->ios->bgp->next;
		while (nipper->ios->bgp->neighbor != 0)
		{
			neighborPointer = nipper->ios->bgp->neighbor->next;
			free(nipper->ios->bgp->neighbor);
			nipper->ios->bgp->neighbor = neighborPointer;
		}
		while (nipper->ios->bgp->passive != 0)
		{
			passivePointer = nipper->ios->bgp->passive->next;
			free(nipper->ios->bgp->passive);
			nipper->ios->bgp->passive = passivePointer;
		}
		free(nipper->ios->bgp);
		nipper->ios->bgp = bgpPointer;
	}

	// Cleanup RIP
	if (nipper->ios->rip != 0)
	{
		while (nipper->ios->rip->neighbor != 0)
		{
			hostPointer = nipper->ios->rip->neighbor->next;
			free(nipper->ios->rip->neighbor);
			nipper->ios->rip->neighbor = hostPointer;
		}
		while (nipper->ios->rip->network != 0)
		{
			hostPointer = nipper->ios->rip->network->next;
			free(nipper->ios->rip->network);
			nipper->ios->rip->network = hostPointer;
		}
		while (nipper->ios->rip->passive != 0)
		{
			passivePointer = nipper->ios->rip->passive->next;
			free(nipper->ios->rip->passive);
			nipper->ios->rip->passive = passivePointer;
		}
		free(nipper->ios->rip);
	}

	// Interfaces
	while (nipper->ios->interface != 0)
	{
		interfaceConfigPointer = nipper->ios->interface->next;
		while (nipper->ios->interface->eigrp != 0)
		{
			eigrpAutonPointer = nipper->ios->interface->eigrp->next;
			free(nipper->ios->interface->eigrp);
			nipper->ios->interface->eigrp = eigrpAutonPointer;
		}
		while (nipper->ios->interface->bgp != 0)
		{
			bgpInterPointer = nipper->ios->interface->bgp->next;
			free(nipper->ios->interface->bgp);
			nipper->ios->interface->bgp = bgpInterPointer;
		}
		while (nipper->ios->interface->ospf != 0)
		{
			ospfInterPointer = nipper->ios->interface->ospf->next;
			free(nipper->ios->interface->ospf);
			nipper->ios->interface->ospf = ospfInterPointer;
		}
		while (nipper->ios->interface->vrrp != 0)
		{
			vrrpPointer = nipper->ios->interface->vrrp->next;
			free(nipper->ios->interface->vrrp);
			nipper->ios->interface->vrrp = vrrpPointer;
		}
		free(nipper->ios->interface);
		nipper->ios->interface = interfaceConfigPointer;
	}

	// Banner
	while (nipper->ios->banner != 0)
	{
		bannerPointer = nipper->ios->banner->next;
		free(nipper->ios->banner->line);
		free(nipper->ios->banner);
		nipper->ios->banner = bannerPointer;
	}

	// Cleanup AAA
	if (nipper->ios->aaa != 0)
	{
		while (nipper->ios->aaa->groupServer != 0)
		{
			while (nipper->ios->aaa->groupServer->server != 0)
			{
				aaaServerPointer = nipper->ios->aaa->groupServer->server->next;
				free (nipper->ios->aaa->groupServer->server);
				nipper->ios->aaa->groupServer->server = aaaServerPointer;
			}
			aaaGroupServerPointer = nipper->ios->aaa->groupServer->next;
			free (nipper->ios->aaa->groupServer);
			nipper->ios->aaa->groupServer = aaaGroupServerPointer;
		}
		free (nipper->ios->aaa);
	}

	// Cleanup Logging
	if (nipper->ios->logging != 0)
	{
		while (nipper->ios->logging->logServer != 0)
		{
			logServerPointer = nipper->ios->logging->logServer->next;
			free(nipper->ios->logging->logServer);
			nipper->ios->logging->logServer = logServerPointer;
		}
		free(nipper->ios->logging);
	}

	// Cleanup TACACS
	if (nipper->ios->tacacs != 0)
	{
		while (nipper->ios->tacacs->host != 0)
		{
			tacacsHostPointer = nipper->ios->tacacs->host->next;
			free(nipper->ios->tacacs->host);
			nipper->ios->tacacs->host = tacacsHostPointer;
		}
		free(nipper->ios->tacacs);
	}

	// OSPF
	while (nipper->ios->ospf != 0)
	{
		ospfPointer = nipper->ios->ospf->next;
		// Cleanup OSPF Area
		while (nipper->ios->ospf->ospfArea != 0)
		{
			ospfAreaPointer = nipper->ios->ospf->ospfArea->next;
			free(nipper->ios->ospf->ospfArea);
			nipper->ios->ospf->ospfArea = ospfAreaPointer;
		}
		// Cleanup OSPF Network
		while (nipper->ios->ospf->ospfNetwork != 0)
		{
			ospfNetworkPointer = nipper->ios->ospf->ospfNetwork->next;
			free(nipper->ios->ospf->ospfNetwork);
			nipper->ios->ospf->ospfNetwork = ospfNetworkPointer;
		}
		// Cleanup OSPF Neighbor
		while (nipper->ios->ospf->neighbor != 0)
		{
			ospfNeighborPointer = nipper->ios->ospf->neighbor->next;
			free(nipper->ios->ospf->neighbor);
			nipper->ios->ospf->neighbor = ospfNeighborPointer;
		}
		free(nipper->ios->ospf);
		nipper->ios->ospf = ospfPointer;
	}

	// Cleanup ftp
	if (nipper->ios->ftp != 0)
	{
		while (nipper->ios->ftp->interface != 0)
		{
			interfacePointer = nipper->ios->ftp->interface->next;
			free(nipper->ios->ftp->interface);
			nipper->ios->ftp->interface = interfacePointer;
		}
		free(nipper->ios->ftp);
	}

	// Cleanup ntp
	if (nipper->ios->ntp != 0)
	{
		while (nipper->ios->ntp->key != 0)
		{
			ntpKeyPointer = nipper->ios->ntp->key->next;
			free(nipper->ios->ntp->key);
			nipper->ios->ntp->key = ntpKeyPointer;
		}
		while (nipper->ios->ntp->server != 0)
		{
			ntpHostPointer = nipper->ios->ntp->server->next;
			free(nipper->ios->ntp->server);
			nipper->ios->ntp->server = ntpHostPointer;
		}
		while (nipper->ios->ntp->peer != 0)
		{
			ntpHostPointer = nipper->ios->ntp->peer->next;
			free(nipper->ios->ntp->peer);
			nipper->ios->ntp->peer = ntpHostPointer;
		}
		while (nipper->ios->ntp->access != 0)
		{
			ntpAccessPointer = nipper->ios->ntp->access->next;
			free(nipper->ios->ntp->access);
			nipper->ios->ntp->access = ntpAccessPointer;
		}
		free(nipper->ios->ntp);
	}

	// Cleanup snmp
	if (nipper->ios->snmp != 0)
	{
		while (nipper->ios->snmp->community != 0)
		{
			communityPointer = nipper->ios->snmp->community->next;
			free(nipper->ios->snmp->community);
			nipper->ios->snmp->community = communityPointer;
		}
		while (nipper->ios->snmp->trap != 0)
		{
			snmpTrapPointer = nipper->ios->snmp->trap->next;
			free(nipper->ios->snmp->trap);
			nipper->ios->snmp->trap = snmpTrapPointer;
		}
		while (nipper->ios->snmp->host != 0)
		{
			snmpHostPointer = nipper->ios->snmp->host->next;
			free(nipper->ios->snmp->host);
			nipper->ios->snmp->host = snmpHostPointer;
		}
		while (nipper->ios->snmp->view != 0)
		{
			while (nipper->ios->snmp->view->viewItem != 0)
			{
				snmpViewItemPointer = nipper->ios->snmp->view->viewItem->next;
				free(nipper->ios->snmp->view->viewItem);
				nipper->ios->snmp->view->viewItem = snmpViewItemPointer;
			}
			snmpViewPointer = nipper->ios->snmp->view->next;
			free(nipper->ios->snmp->view);
			nipper->ios->snmp->view = snmpViewPointer;
		}
		while (nipper->ios->snmp->group != 0)
		{
			snmpGroupPointer = nipper->ios->snmp->group->next;
			free(nipper->ios->snmp->group);
			nipper->ios->snmp->group = snmpGroupPointer;
		}
		while (nipper->ios->snmp->user != 0)
		{
			snmpUserPointer = nipper->ios->snmp->user->next;
			free(nipper->ios->snmp->user);
			nipper->ios->snmp->user = snmpUserPointer;
		}
		free(nipper->ios->snmp);
	}

	// Cleanup IOS config
	free(nipper->ios);
}


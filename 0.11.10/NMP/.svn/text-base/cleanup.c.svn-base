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


void cleanupNMP(struct nipperConfig *nipper)
{
	// Pointers
	struct snmpNMPCommunity *communityNMPPointer = 0;
	struct snmpNMPHost *snmpNMPHostPointer = 0;
	struct snmpTrap *snmpTrapPointer = 0;
	struct hostNMP *hostNMPPointer = 0;
	struct vlanConfig *vlanNMPPointer = 0;
	struct moduleConfig *moduleNMPPointer = 0;
	struct portConfig *portNMPPointer = 0;

	// Cleanup SNMP
	if (nipper->nmp->snmp != 0)
	{
		while (nipper->nmp->snmp->community != 0)
		{
			communityNMPPointer = nipper->nmp->snmp->community->next;
			free(nipper->nmp->snmp->community);
			nipper->nmp->snmp->community = communityNMPPointer;
		}
		while (nipper->nmp->snmp->trap != 0)
		{
			snmpTrapPointer = nipper->nmp->snmp->trap->next;
			free(nipper->nmp->snmp->trap);
			nipper->nmp->snmp->trap = snmpTrapPointer;
		}
		while (nipper->nmp->snmp->host != 0)
		{
			snmpNMPHostPointer = nipper->nmp->snmp->host->next;
			free(nipper->nmp->snmp->host);
			nipper->nmp->snmp->host = snmpNMPHostPointer;
		}
		free(nipper->nmp->snmp);
	}

	// Cleanup Modules & Ports
	while (nipper->nmp->module != 0)
	{
		while (nipper->nmp->module->ports != 0)
		{
			portNMPPointer = nipper->nmp->module->ports->next;
			free(nipper->nmp->module->ports);
			nipper->nmp->module->ports = portNMPPointer;
		}
		moduleNMPPointer = nipper->nmp->module->next;
		free(nipper->nmp->module);
		nipper->nmp->module = moduleNMPPointer;
	}

	// Cleanup VLANS
	while (nipper->nmp->vlan != 0)
	{
		vlanNMPPointer = nipper->nmp->vlan->next;
		free(nipper->nmp->vlan);
		nipper->nmp->vlan = vlanNMPPointer;
	}

	// Cleanup Permit Lists
	if (nipper->nmp->permit != 0)
	{
		while (nipper->nmp->permit->telnetHost != 0)
		{
			hostNMPPointer = nipper->nmp->permit->telnetHost->next;
			free(nipper->nmp->permit->telnetHost);
			nipper->nmp->permit->telnetHost = hostNMPPointer;
		}
		while (nipper->nmp->permit->sshHost != 0)
		{
			hostNMPPointer = nipper->nmp->permit->sshHost->next;
			free(nipper->nmp->permit->sshHost);
			nipper->nmp->permit->sshHost = hostNMPPointer;
		}
		while (nipper->nmp->permit->snmpHost != 0)
		{
			hostNMPPointer = nipper->nmp->permit->snmpHost->next;
			free(nipper->nmp->permit->snmpHost);
			nipper->nmp->permit->snmpHost = hostNMPPointer;
		}
		free(nipper->nmp->permit);
	}

	// Cleanup switch config
	if (nipper->nmp->switchConfig != 0)
		free (nipper->nmp->switchConfig);

	// Cleanup NMP config
	free(nipper->nmp);
}


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


void cleanupPIX(struct nipperConfig *nipper)
{
	// Pointers
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

	// Cleanup Interfaces
	while (nipper->pix->interface != 0)
	{
		interfacePIXPointer = nipper->pix->interface->next;
		free(nipper->pix->interface);
		nipper->pix->interface = interfacePIXPointer;
	}

	// Cleanup HTTP
	if (nipper->pix->http != 0)
	{
		while (nipper->pix->http->host != 0)
		{
			mgmtHostsPointer = nipper->pix->http->host->next;
			free(nipper->pix->http->host);
			nipper->pix->http->host = mgmtHostsPointer;
		}
		free(nipper->pix->http);
	}

	// Cleanup Static NAT / PAT
	while (nipper->pix->staticNAT != 0)
	{
		staticPIXPointer = nipper->pix->staticNAT->next;
		free(nipper->pix->staticNAT);
		nipper->pix->staticNAT = staticPIXPointer;
	}
	while (nipper->pix->staticPAT != 0)
	{
		staticPIXPointer = nipper->pix->staticPAT->next;
		free(nipper->pix->staticPAT);
		nipper->pix->staticPAT = staticPIXPointer;
	}

	// Cleanup SNMP
	if (nipper->pix->snmp != 0)
	{
		while (nipper->pix->snmp->host != 0)
		{
			snmpHostPIXPointer = nipper->pix->snmp->host->next;
			free(nipper->pix->snmp->host);
			nipper->pix->snmp->host = snmpHostPIXPointer;
		}
		while (nipper->pix->snmp->trap != 0)
		{
			trapPIXPointer = nipper->pix->snmp->trap->next;
			free(nipper->pix->snmp->trap);
			nipper->pix->snmp->trap = trapPIXPointer;
		}
		free(nipper->pix->snmp);
	}

	// Cleanup SSH
	if (nipper->pix->ssh != 0)
	{
		while (nipper->pix->ssh->access != 0)
		{
			sshPointer = nipper->pix->ssh->access->next;
			free(nipper->pix->ssh->access);
			nipper->pix->ssh->access = sshPointer;
		}
		free(nipper->pix->ssh);
	}

	// Free route
	while (nipper->pix->route != 0)
	{
		routePIXPointer = nipper->pix->route->next;
		free (nipper->pix->route);
		nipper->pix->route = routePIXPointer;
	}

	// Free Enable Passwords
	while (nipper->pix->enable != 0)
	{
		enablePIXPointer = nipper->pix->enable->next;
		free (nipper->pix->enable);
		nipper->pix->enable = enablePIXPointer;
	}

	// Free Usernames
	while (nipper->pix->username != 0)
	{
		usernamePIXPointer = nipper->pix->username->next;
		free (nipper->pix->username);
		nipper->pix->username = usernamePIXPointer;
	}

	// Fixup
	while (nipper->pix->fixup != 0)
	{
		fixupPIXPointer = nipper->pix->fixup->next;
		free (nipper->pix->fixup);
		nipper->pix->fixup = fixupPIXPointer;
	}

	// ICMP Access
	while (nipper->pix->icmp != 0)
	{
		icmpPIXPointer = nipper->pix->icmp->next;
		free (nipper->pix->icmp);
		nipper->pix->icmp = icmpPIXPointer;
	}

	// Cleanup PIX config
	free(nipper->pix);
}


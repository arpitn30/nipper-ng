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


void cleanupSOS(struct nipperConfig *nipper)
{
	// Pointers
	struct adminUsersSOS *userSOSPointer = 0;
	struct authServerSOS *authServerPointer = 0;
	struct interfaceSOS *interfaceSOSPointer = 0;
	struct snmpCommunitySOS *communityPointer = 0;
	struct snmpHostSOS *snmpHostPointer = 0;
	struct zoneSOS *zonePointer = 0;

	// SNMP
	if (nipper->sos->snmp != 0)
	{
		while (nipper->sos->snmp->community != 0)
		{
			communityPointer = nipper->sos->snmp->community->next;
			free (nipper->sos->snmp->community);
			nipper->sos->snmp->community = communityPointer;
		}
		while (nipper->sos->snmp->host != 0)
		{
			snmpHostPointer = nipper->sos->snmp->host->next;
			free (nipper->sos->snmp->host);
			nipper->sos->snmp->host = snmpHostPointer;
		}
		free (nipper->sos->snmp);
	}

	// Cleanup Admin Users
	while (nipper->sos->users != 0)
	{
		userSOSPointer = nipper->sos->users->next;
		free(nipper->sos->users);
		nipper->sos->users = userSOSPointer;
	}

	// Cleanup auth server
	while (nipper->sos->authServer != 0)
	{
		authServerPointer = nipper->sos->authServer->next;
		free (nipper->sos->authServer);
		nipper->sos->authServer = authServerPointer;
	}

	// Cleanup Interfaces
	while (nipper->sos->interface != 0)
	{
		interfaceSOSPointer = nipper->sos->interface->next;
		free (nipper->sos->interface);
		nipper->sos->interface = interfaceSOSPointer;
	}

	// Cleanup Zones
	while (nipper->sos->zone != 0)
	{
		zonePointer = nipper->sos->zone->next;
		free (nipper->sos->zone);
		nipper->sos->zone = zonePointer;
	}

	// Cleanup SOS config
	free(nipper->sos);
}


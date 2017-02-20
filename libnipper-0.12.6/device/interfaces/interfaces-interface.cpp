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

// Includes...
#include <cstring>

#include "../../globaldefs.h"
#include "../device.h"
#include "interfaces.h"


Interfaces::interfaceListConfig *Interfaces::addInterfaceList()
{
	// Variables...
	interfaceListConfig *interfaceListPointer = 0;

	// Create...
	if (interfaceList == 0)
	{
		interfaceList = new (interfaceListConfig);
		interfaceListPointer = interfaceList;
	}
	else
	{
		interfaceListPointer = interfaceList;
		while (interfaceListPointer->next != 0)
			interfaceListPointer = interfaceListPointer->next;
		interfaceListPointer->next = new (interfaceListConfig);
		interfaceListPointer = interfaceListPointer->next;
	}

	// Init...
	interfaceListPointer->title = i18n("Physical Network Interfaces");
	interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices physical network interfaces.");
	interfaceListPointer->tableTitle = i18n("Physical network interfaces");
	interfaceListPointer->label = "PHYSINTERFACES";
	interfaceListPointer->interface = 0;
	interfaceListPointer->vlanSupported = false;						// Use VLAN
	interfaceListPointer->useSecurityLevel = false;
	interfaceListPointer->useStandbyAddress = false;
	interfaceListPointer->proxyArpSupported = false;
	interfaceListPointer->mopSupported = false;
	interfaceListPointer->unreachablesSupported = false;
	interfaceListPointer->redirectsSupported = false;
	interfaceListPointer->ipMaskReplySupported = false;
	interfaceListPointer->informationReplySupported = false;
	interfaceListPointer->ipDirectBroadcastSupported = false;
	interfaceListPointer->cdpSupported = false;
	interfaceListPointer->portModeSupported = false;					// Is switch port mode supported?
	interfaceListPointer->portSecuritySupported = false;				// Is the switch port security supported (mac-based)?
	interfaceListPointer->interfaceDisableSupport = false;				// Is it possible to disable interfaces?
	interfaceListPointer->ipAddressSupported = false;					// Are addresses supported?
	interfaceListPointer->inboundFilterSupported = false;				// Is the inbound filtering supported?
	interfaceListPointer->outboudFilterSupported = false;				// Is the outbound filtering supported?
	interfaceListPointer->next = 0;

	return interfaceListPointer;
}


Interfaces::interfaceListConfig *Interfaces::getInterfaceList(const char *label)
{
	// Variables...
	interfaceListConfig *interfaceListPointer = 0;

	interfaceListPointer = interfaceList;
	while (interfaceListPointer != 0)
	{
		if (strcmp(interfaceListPointer->label, label) == 0)
			return interfaceListPointer;
		else
			interfaceListPointer = interfaceListPointer->next;
	}

	return interfaceListPointer;
}


Interfaces::interfaceConfig *Interfaces::getInterface(interfaceListConfig *interfaceListPointer, const char *name, int module, int port)
{
	// Variables...
	interfaceConfig *interfacePointer = 0;
	interfaceConfig *previousPointer = 0;
	bool found = false;

	if (interfaceListPointer->interface == 0)
	{
		interfaceListPointer->interface = new (interfaceConfig);
		interfacePointer = interfaceListPointer->interface;
		interfacePointer->next = 0;
	}
	else
	{
		if ((useModuleAndPort == false) || (strlen(name) > 0))
		{
			interfacePointer = interfaceListPointer->interface;
			while (interfacePointer->next != 0)
			{
				if ((strcmp(interfacePointer->name.c_str(), name) == 0) && (interfacePointer->module == module) && (interfacePointer->port == port))
					return interfacePointer;
				interfacePointer = interfacePointer->next;
			}
			if ((strcmp(interfacePointer->name.c_str(), name) == 0) && (interfacePointer->module == module) && (interfacePointer->port == port))
				return interfacePointer;
			interfacePointer->next = new (interfaceConfig);
			interfacePointer = interfacePointer->next;
			interfacePointer->next = 0;
		}
		else
		{
			interfacePointer = interfaceListPointer->interface;

			while ((interfacePointer->next != 0) && (found == false))
			{
				// Found existing one...
				if ((interfacePointer->module == module) && (interfacePointer->port == port))
					return interfacePointer;

				// Should go before this one...
				else if ((interfacePointer->module > module) || ((interfacePointer->module == module) && (interfacePointer->port > port)))
						found = true;

				// Nothing...next...
				else
				{
					previousPointer = interfacePointer;
					interfacePointer = interfacePointer->next;
				}
			}

			if ((interfacePointer->module == module) && (interfacePointer->port == port))
				return interfacePointer;

			// A new one has to be created...
			else
			{
				// Before...
				if ((interfacePointer->module > module) || ((interfacePointer->module == module) && (interfacePointer->port > port)))
				{
					// If first in list...
					if (previousPointer == 0)
					{
						previousPointer = new (interfaceConfig);
						previousPointer->next = interfaceListPointer->interface;
						interfaceListPointer->interface = previousPointer;
					}

					// not first in list...
					else
					{
						previousPointer->next = new (interfaceConfig);
						previousPointer = previousPointer->next;
						previousPointer->next = interfacePointer;
					}

					interfacePointer = previousPointer;
				}

				// else after...
				else
				{
					interfacePointer->next = new (interfaceConfig);
					interfacePointer = interfacePointer->next;
					interfacePointer->next = 0;
				}
			}
		}
	}

	// Init...
	interfacePointer->name.assign(name);
	interfacePointer->module = module;
	interfacePointer->port = port;
	interfacePointer->securityLevel = 0;
	interfacePointer->enabled = true;
	interfacePointer->dhcp = false;
	interfacePointer->filterIn = 0;
	interfacePointer->filterOut = 0;
	interfacePointer->vlan = 0;
	interfacePointer->proxyARP = false;
	interfacePointer->ntp = false;
	interfacePointer->mop = false;
	interfacePointer->ipUnreachables = false;
	interfacePointer->ipRedirects = false;
	interfacePointer->ipMaskReply = false;
	interfacePointer->infoReply = false;
	interfacePointer->ipDirectBroadcast.assign(i18n("Off"));
	interfacePointer->cdp = false;
	interfacePointer->uRPF = false;
	interfacePointer->switchportMode = portModeAccess;
	interfacePointer->switchportSecurity = false;
	interfacePointer->switchportViolation = onViolationShutdown;

	return interfacePointer;
}


Interfaces::interfaceConfig *Interfaces::getOnlyInterface(interfaceListConfig *interfaceListPointer, const char *name, int module, int port)
{
	// Variables...
	interfaceConfig *interfacePointer = 0;

	interfacePointer = interfaceListPointer->interface;
	while (interfacePointer != 0)
	{
		if ((strcmp(interfacePointer->name.c_str(), name) == 0) && (interfacePointer->module == module) && (interfacePointer->port == port))
			return interfacePointer;
		interfacePointer = interfacePointer->next;
	}

	return interfacePointer;
}


Interfaces::interfaceConfig *Interfaces::getInterfaceByZone(interfaceListConfig *interfaceListPointer, const char *zone)
{
	// Variables...
	interfaceConfig *interfacePointer = 0;

	interfacePointer = interfaceListPointer->interface;
	while (interfacePointer != 0)
	{
		if (strcmp(interfacePointer->zone.c_str(), zone) == 0)
			return interfacePointer;
		interfacePointer = interfacePointer->next;
	}

	return interfacePointer;
}


int Interfaces::addFilterList(interfaceConfig *interfacePointer, const char *filterList, bool in)
{
	// Variables...
	Device::listStruct *listPointer = 0;

	// inbound...
	if (in == true)
	{
		if (interfacePointer->filterIn == 0)
		{
			interfacePointer->filterIn = new (Device::listStruct);
			listPointer = interfacePointer->filterIn;
		}
		else
		{
			listPointer = interfacePointer->filterIn;
			while (listPointer->next != 0)
				listPointer = listPointer->next;
			listPointer->next = new (Device::listStruct);
			listPointer = listPointer->next;
		}
	}
	else
	{
		if (interfacePointer->filterOut == 0)
		{
			interfacePointer->filterOut = new (Device::listStruct);
			listPointer = interfacePointer->filterOut;
		}
		else
		{
			listPointer = interfacePointer->filterOut;
			while (listPointer->next != 0)
				listPointer = listPointer->next;
			listPointer->next = new (Device::listStruct);
			listPointer = listPointer->next;
		}
	}

	listPointer->listItem.assign(filterList);
	listPointer->next = 0;

	return 0;
}


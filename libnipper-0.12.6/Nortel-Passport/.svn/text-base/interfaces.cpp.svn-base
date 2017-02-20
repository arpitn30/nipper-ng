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
#include <cstdlib>

#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "device.h"
#include "interfaces.h"


PassportInterfaces::PassportInterfaces()
{
	// Interface Options...
	useModuleAndPort = true;						// Use the module / port instead of the name
	useInterfaceZone = false;						// Use the interface zone
	zoneName = i18n("Zone");						// The name for zone field
	filterIn = i18n("Filter");						// The filter in table title text
	filterOut = i18n("Filter Out");					// The filter out table title text
	showDescription = false;						// Show the interface description
	cdpGlobalRequired = false;						// If CDP needs to be enabled globally as well
	disableCDPText = i18n("");						// The text and commands to disable CDP
	cdpSupported = false;							// Is CDP supported on interfaces
	disableProxyARPText = i18n("Proxy *ABBREV*ARP*-ABBREV* can be disabled on *ABBREV*VLAN*-ABBREV* interfaces with the following command:*CODE**COMMAND*vlan *CMDUSER*vlan-id*-CMDUSER* ip proxy disable*-COMMAND**-CODE*");					// The text and commands to disable Proxy ARP
	disableUnreachablesText = i18n("");				// The text and commands to disable ICMP unreachable messages
	disableInformationText = i18n("");				// The text and commands to disable ICMP information messages
	disableMaskText = i18n("");						// The text and commands to disable ICMP mask messages
	disableRedirectText = i18n("");					// The text and commands to disable ICMP redirect messages
	disableDirectedText = i18n("");					// The text and commands to disable directed broadcasts
	disableMOPText = i18n("");						// The text and commands to disable MOP
	disableActiveText = i18n("");					// The text and commands to disable potentially unused interfaces
	filterName = i18n("filter lists");				// The filter list name for use in the filter issue text
	configFilterText = i18n("");					// The text and commands to configure network filtering
	defaultAutoTrunk = false;						// Default to automatically trunk
	disableTrunkText = i18n("");					// The text and commands to disable trunking on a port
	enablePortSecurityText = i18n("");				// The text and commands to enable port security
}


int PassportInterfaces::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	interfaceListConfig *interfaceListPointer = 0;
	interfaceConfig *interfacePointer = 0;
	string tempString;

	// ethernet...
	if (strcmp(command->part(0), "ethernet") == 0)
	{

		interfaceListPointer = getInterfaceList("ETHERINTERFACES");
		if (interfaceListPointer == 0)
		{
			interfaceListPointer = addInterfaceList();
			interfaceListPointer->title = i18n("Ethernet Interfaces");
			interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices ethernet interfaces.");
			interfaceListPointer->tableTitle = i18n("Ethernet interfaces");
			interfaceListPointer->label = "ETHERINTERFACES";
			interfaceListPointer->vlanSupported = true;
			interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
			interfaceListPointer->inboundFilterSupported = true;					// Is the inbound filtering supported?
			interfaceListPointer->outboudFilterSupported = false;					// Is the outbound filtering supported?
		}
		tempString.assign(command->part(1));
		interfacePointer = getInterface(interfaceListPointer, "", atoi(command->part(1)), atoi(tempString.substr(tempString.find("/") + 1).c_str()));

		// State
		if (strcmp(command->part(2), "state") == 0)
		{
		
			if (device->config->reportFormat == Config::Debug)
				printf("%sEthernet State Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			if (strcasecmp(command->part(3), "disable") == 0)
				interfacePointer->enabled = false;
		}

		// name
		else if (strcmp(command->part(2), "name") == 0)
		{
		
			if (device->config->reportFormat == Config::Debug)
				printf("%sEthernet Description Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			interfacePointer->description.assign(command->part(3));
		}

		else if ((strcmp(command->part(2), "ip") == 0) && (strcmp(command->part(3), "traffic-filter") == 0) &&  (strcmp(command->part(4), "add") == 0) &&  (strcmp(command->part(5), "set") == 0))
		{
		
			if (device->config->reportFormat == Config::Debug)
				printf("%sEthernet Filter Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			addFilterList(interfacePointer, command->part(6), true);
		}

		else if (strcmp(command->part(2), "default-vlan-id") == 0)
		{
		
			if (device->config->reportFormat == Config::Debug)
				printf("%sEthernet VLAN Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			addVLAN(interfacePointer, command->part(3));
		}

		// All others...
		else
			device->lineNotProcessed(line);
	}

	// vlan...
	if (strcmp(command->part(0), "vlan") == 0)
	{

		interfaceListPointer = getInterfaceList("VLANINTERFACES");
		if (interfaceListPointer == 0)
		{
			interfaceListPointer = addInterfaceList();
			interfaceListPointer->title = i18n("*ABBREV*VLAN*-ABBREV* Interfaces");
			interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices *ABBREV*VLAN*-ABBREV* interfaces.");
			interfaceListPointer->tableTitle = i18n("*ABBREV*VLAN*-ABBREV* interfaces");
			interfaceListPointer->label = "VLANINTERFACES";
			interfaceListPointer->proxyArpSupported = true;
			interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
		}
		interfacePointer = getInterface(interfaceListPointer, command->part(1));

		if ((strcmp(command->part(2), "ip") == 0) && (strcmp(command->part(3), "create") == 0))
		{
		
			if (device->config->reportFormat == Config::Debug)
				printf("%sVLAN IP Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			tempString.assign(command->part(4));
			interfacePointer->address.assign(tempString.substr(0, tempString.find("/") - 1));
			interfacePointer->netmask.assign(tempString.substr(tempString.find("/") + 1).c_str());
		}

		else if ((strcmp(command->part(2), "ip") == 0) && (strcmp(command->part(3), "proxy") == 0))
		{
		
			if (device->config->reportFormat == Config::Debug)
				printf("%sVLAN IP Proxy Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			if (strcmp(command->part(4), "enable") == 0)
				interfacePointer->proxyARP = true;
			else
				interfacePointer->proxyARP = false;
		}

		// All others...
		else
			device->lineNotProcessed(line);
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int PassportInterfaces::processDefaults(Device *device)
{
	return 0;
}


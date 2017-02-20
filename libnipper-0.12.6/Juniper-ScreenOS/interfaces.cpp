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

#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "device.h"
#include "interfaces.h"


ScreenOSInterfaces::ScreenOSInterfaces()
{
	// Interface Options...
	useModuleAndPort = false;						// Use the module / port instead of the name
	useInterfaceZone = true;						// Use the interface zone
	zoneName = i18n("Zone");						// The name for zone field
	filterIn = i18n("Filter In");					// The filter in table title text
	filterOut = i18n("Filter Out");					// The filter out table title text
	showDescription = true;							// Show the interface description
	cdpGlobalRequired = false;						// If CDP needs to be enabled globally as well
	disableCDPText = i18n("");						// The text and commands to disable CDP
	cdpSupported = false;							// Is CDP supported on interfaces
	disableProxyARPText = i18n("");					// The text and commands to disable Proxy ARP
	disableUnreachablesText = i18n("");				// The text and commands to disable ICMP unreachable messages
	disableInformationText = i18n("");				// The text and commands to disable ICMP information messages
	disableMaskText = i18n("");						// The text and commands to disable ICMP mask messages
	disableRedirectText = i18n("");					// The text and commands to disable ICMP redirect messages
	disableDirectedText = i18n("");					// The text and commands to disable directed broadcasts
	disableMOPText = i18n("");						// The text and commands to disable MOP
	disableActiveText = i18n("Interfaces can be disabled on *DEVICETYPE* devices with the following command:*CODE**COMMAND*set interface *CMDUSER*interface*-CMDUSER* disable*-COMMAND**-CODE*");					// The text and commands to disable potentially unused interfaces
	filterName = i18n("filter lists");				// The filter list name for use in the filter issue text
	configFilterText = i18n("");					// The text and commands to configure network filtering
	defaultAutoTrunk = false;						// Default to automatically trunk
	disableTrunkText = i18n("");					// The text and commands to disable trunking on a port
	enablePortSecurityText = i18n("");				// The text and commands to enable port security
}


int ScreenOSInterfaces::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	interfaceListConfig *interfaceListPointer = 0;
	interfaceConfig *interfacePointer = 0;
	string tempString;
	int tempInt = 0;

	// Init
	tempInt = 2;
	if (strcasecmp(command->part(0), "set") == 0)
	{
		// Get the correct list for the type of interface...
		if (strncasecmp(command->part(tempInt), "ethernet", 8) == 0)
		{
			interfaceListPointer = getInterfaceList("ETHERINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("Ethernet Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices ethernet interfaces.");
				interfaceListPointer->tableTitle = i18n("Ethernet interfaces");
				interfaceListPointer->label = "ETHERINTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(tempInt) + 8);
		}
		else if (strncasecmp(command->part(tempInt), "wireless", 8) == 0)
		{
			interfaceListPointer = getInterfaceList("WIREINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("Wireless Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices wireless interfaces.");
				interfaceListPointer->tableTitle = i18n("Wireless interfaces");
				interfaceListPointer->label = "WIREINTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(tempInt) + 8);
		}
		else if (strncasecmp(command->part(tempInt), "serial", 6) == 0)
		{
			interfaceListPointer = getInterfaceList("SERIALINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("Serial Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices serial interfaces.");
				interfaceListPointer->tableTitle = i18n("Serial interfaces");
				interfaceListPointer->label = "SERIALINTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(tempInt) + 6);
		}
		else if (strncasecmp(command->part(tempInt), "vlan", 4) == 0)
		{
			interfaceListPointer = getInterfaceList("VLANINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("*ABBREV*VLAN*-ABBREV* Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices *ABBREV*VLAN*-ABBREV* interfaces.");
				interfaceListPointer->tableTitle = i18n("*ABBREV*VLAN*-ABBREV* interfaces");
				interfaceListPointer->label = "VLANINTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(tempInt) + 4);
		}
		else if (strncasecmp(command->part(tempInt), "bri", 3) == 0)
		{
			interfaceListPointer = getInterfaceList("BRIINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("*ABBREV*ISDN*-ABBREV* Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices *ABBREV*ISDN*-ABBREV* interfaces.");
				interfaceListPointer->tableTitle = i18n("*ABBREV*ISDN*-ABBREV* interfaces");
				interfaceListPointer->label = "BRIINTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(tempInt) + 3);
		}
		else if (strncasecmp(command->part(tempInt), "tunnel", 6) == 0)
		{
			interfaceListPointer = getInterfaceList("TUNINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("Tunnel Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices tunnel interfaces.");
				interfaceListPointer->tableTitle = i18n("Tunnel interfaces");
				interfaceListPointer->label = "TUNINTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(tempInt) + 6);
		}
		else if ((strncasecmp(command->part(tempInt), "shdsl", 5) == 0) || (strncasecmp(command->part(tempInt), "adsl", 4) == 0))
		{
			interfaceListPointer = getInterfaceList("DSLINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("*ABBREV*DSL*-ABBREV* Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices *ABBREV*DSL*-ABBREV* interfaces.");
				interfaceListPointer->tableTitle = i18n("*ABBREV*DSL*-ABBREV* interfaces");
				interfaceListPointer->label = "DSLINTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(tempInt));
		}
		else if (strncasecmp(command->part(tempInt), "bgroup", 6) == 0)
		{
			interfaceListPointer = getInterfaceList("BGROUPINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("Bridge group Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices bridge group interfaces.");
				interfaceListPointer->tableTitle = i18n("Bridge group interfaces");
				interfaceListPointer->label = "BGROUPINTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(tempInt) + 6);
		}
		else
		{
			interfaceListPointer = getInterfaceList("INTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices interfaces.");
				interfaceListPointer->tableTitle = i18n("Interfaces");
				interfaceListPointer->label = "INTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(tempInt));
		}
		tempInt++;

		if ((strcasecmp(command->part(tempInt), "ip") == 0) && (strcasecmp(command->part(tempInt + 1), "manageable") != 0) && (strcasecmp(command->part(tempInt + 1), "unnumbered") != 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sInterface IP Address Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			tempInt++;
			if (command->parts > 4)
			{
				tempString.assign(command->part(tempInt));
				if (tempString.find("/") == string::npos)
				{
					interfacePointer->address.assign(command->part(tempInt));
					interfacePointer->netmask.assign(command->part(tempInt + 1));
				}
				else
				{
					interfacePointer->address.assign(tempString.substr(0, tempString.find("/") - 1));
					interfacePointer->netmask.assign(device->cidrToNetmask(tempString.substr(tempString.find("/") + 1).c_str()));
				}
			}
		}

		else if (strcasecmp(command->part(tempInt), "zone") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sInterface Zone Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			tempInt++;
			if (command->parts > 4)
			{
				interfacePointer->zone.assign(command->part(tempInt));
			}
		}

		else if (strcasecmp(command->part(tempInt), "description") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sInterface Description Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			tempInt++;
			if (command->parts > 4)
			{
				interfacePointer->description.assign(command->part(tempInt));
			}
		}

		else if ((strcasecmp(command->part(tempInt), "disable") == 0) || (strcasecmp(command->part(tempInt), "shutdown") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sInterface Disable Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			tempInt++;
			if (command->parts > 4)
			{
				interfacePointer->enabled = false;
			}
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


int ScreenOSInterfaces::processDefaults(Device *device)
{
	return 0;
}


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


ProCurveInterfaces::ProCurveInterfaces()
{
	// Interface Options...
	useModuleAndPort = false;						// Use the module / port instead of the name
	useInterfaceZone = false;						// Use the interface zone
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
	disableActiveText = i18n("");					// The text and commands to disable potentially unused interfaces
	filterName = i18n("filter lists");				// The filter list name for use in the filter issue text
	configFilterText = i18n("");					// The text and commands to configure network filtering
	defaultAutoTrunk = false;						// Default to automatically trunk
	disableTrunkText = i18n("");					// The text and commands to disable trunking on a port
	enablePortSecurityText = i18n("");				// The text and commands to enable port security
}


int ProCurveInterfaces::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	interfaceListConfig *interfaceListPointer = 0;
	interfaceConfig *interfacePointer = 0;
	int tempInt = 0;
	bool setting = false;

	// VLAN...
	if (strcasecmp(command->part(0), "vlan") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sVLAN Interface Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		// Sort out the interface list first...
		interfaceListPointer = getInterfaceList("VLANINTERFACES");
		if (interfaceListPointer == 0)
		{
			interfaceListPointer = addInterfaceList();
			interfaceListPointer->title = i18n("*ABBREV*VLAN*-ABBREV* Interfaces");
			interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices *ABBREV*VLAN*-ABBREV* interfaces.");
			interfaceListPointer->tableTitle = i18n("*ABBREV*VLAN*-ABBREV* interfaces");
			interfaceListPointer->label = "VLANINTERFACES";
			interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
		}
		interfacePointer = getInterface(interfaceListPointer, command->part(1));

		// Read a line from the config...
		device->readLine(line, lineSize);

		// Split it up into parts...
		command->setConfigLine(line);

		while ((strcasecmp(command->part(0), "exit") != 0) && (feof(device->inputFile) == 0))
		{

			// Init
			if (strcmp(command->part(0), "no") == 0)
			{
				tempInt = 1;
				setting = false;
			}
			else
			{
				tempInt = 0;
				setting = true;
			}

			// Name
			if (strcasecmp(command->part(0), "name") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sVLAN Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				interfacePointer->name.assign(command->part(1));
			}

			// address
			if ((strcasecmp(command->part(0), "ip") == 0) && (strcasecmp(command->part(1), "address") == 0))
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sVLAN Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				interfacePointer->address.assign(command->part(2));
				interfacePointer->netmask.assign(command->part(3));
			}

			// All others...
			else
				device->lineNotProcessed(line);

			// Read a line from the config...
			device->readLine(line, lineSize);

			// Split it up into parts...
			command->setConfigLine(line);
		}
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int ProCurveInterfaces::processDefaults(Device *device)
{
	return 0;
}


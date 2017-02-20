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


CiscoCSSInterfaces::CiscoCSSInterfaces()
{
	// Interface Options...
	useModuleAndPort = false;						// Use the module / port instead of the name
	useInterfaceZone = false;						// Use the interface zone
	zoneName = i18n("Zone");						// The name for zone field
	filterIn = i18n("*ABBREV*ACL*-ABBREV*");		// The filter in table title text
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
	disableActiveText = i18n("Interfaces can be disabled on *DEVICETYPE* devices with the following command:*CODE**COMMAND*shut*-COMMAND**-CODE*");					// The text and commands to disable potentially unused interfaces
	filterName = i18n("filter lists");				// The filter list name for use in the filter issue text
	configFilterText = i18n("An *ABBREV*ACL*-ABBREV* can be configured for a particular circuit with the following *ABBREV*ACL*-ABBREV* command:*CODE**COMMAND*apply circuit-(*CMDUSER*name*-CMDUSER*)*-COMMAND**-CODE*");					// The text and commands to configure network filtering
	defaultAutoTrunk = false;						// Default to automatically trunk
	disableTrunkText = i18n("");					// The text and commands to disable trunking on a port
	enablePortSecurityText = i18n("");				// The text and commands to enable port security
}


int CiscoCSSInterfaces::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	interfaceListConfig *interfaceListPointer = 0;
	interfaceConfig *interfacePointer = 0;

	if (strcmp(command->part(0), "interface") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sInterface Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		// Sort out the interface list first...
		interfaceListPointer = getInterfaceList("INTERFACES");
		if (interfaceListPointer == 0)
		{
			interfaceListPointer = addInterfaceList();
			interfaceListPointer->title = i18n("Network Interfaces");
			interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices network interfaces.");
			interfaceListPointer->tableTitle = i18n("Network interfaces");
			interfaceListPointer->label = "INTERFACES";
			interfaceListPointer->vlanSupported = true;
			interfaceListPointer->portModeSupported = true;
			interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
		}
		interfacePointer = getInterface(interfaceListPointer, command->part(1));

		// Read a line from the config...
		device->readLine(line, lineSize);

		// Split it up into parts...
		command->setConfigLine(line);

		while ((command->parts > 0) && (feof(device->inputFile) == 0))
		{

			// Description...
			if (strcmp(command->part(0), "description") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sInterface Description Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				interfacePointer->description.assign(command->part(1));
			}

			// Shut...
			else if ((strcmp(command->part(0), "shut") == 0) || (strcmp(command->part(0), "admin-shutdown") == 0))
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sInterface Shutdown Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				interfacePointer->enabled = false;
			}

			// VLAN...
			else if (strcmp(command->part(0), "vlan") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sInterface VLAN Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				addVLAN(interfacePointer, command->part(1));
			}

			// VLAN...
			else if ((strcmp(command->part(0), "bridge") == 0) && (strcmp(command->part(1), "vlan") == 0))
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sInterface VLAN Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				addVLAN(interfacePointer, command->part(2));
			}

			// Trunk...
			else if (strcmp(command->part(0), "trunk") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sInterface VLAN Trunking Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				interfacePointer->switchportMode = portModeTrunk;
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

	else if (strcmp(command->part(0), "circuit") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sCircuit Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		// Sort out the interface list first...
		interfaceListPointer = getInterfaceList("CIRCUIT");
		if (interfaceListPointer == 0)
		{
			interfaceListPointer = addInterfaceList();
			interfaceListPointer->title = i18n("Circuit Interfaces");
			interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices circuit interfaces.");
			interfaceListPointer->tableTitle = i18n("Circuit interfaces");
			interfaceListPointer->label = "CIRCUIT";
			interfaceListPointer->ipAddressSupported = true;				// Is it possible to disable interfaces?
			interfaceListPointer->inboundFilterSupported = true;			// Is the inbound filtering supported?
		}
		interfacePointer = getInterface(interfaceListPointer, command->part(1));

		// Read a line from the config...
		device->readLine(line, lineSize);

		// Split it up into parts...
		command->setConfigLine(line);

		while ((command->parts > 0) && (feof(device->inputFile) == 0))
		{

			// Description...
			if (strcmp(command->part(0), "description") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sCircuit Description Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				interfacePointer->description.assign(command->part(1));
			}

			// Address...
			if ((strcmp(command->part(0), "ip") == 0) && (strcmp(command->part(1), "address") == 0))
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sCircuit IP Address Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

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


int CiscoCSSInterfaces::processDefaults(Device *device)
{
	return 0;
}


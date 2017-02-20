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


CatalystInterfaces::CatalystInterfaces()
{
	// Interface Options...
	useModuleAndPort = true;						// Use the module / port instead of the name
	useInterfaceZone = false;						// Use the interface zone
	zoneName = i18n("Zone");						// The name for zone field
	filterIn = i18n("Filter In");					// The filter in table title text
	filterOut = i18n("Filter Out");					// The filter out table title text
	showDescription = true;							// Show the interface description
	cdpGlobalRequired = false;						// If CDP needs to be enabled globally as well
	disableCDPText = i18n("*ABBREV*CDP*-ABBREV* cab be disabled on individual ports with the following command:*CODE**COMMAND*set cdp disable *CMDUSER*module*-CMDUSER*/*CMDUSER*port*-CMDUSER**-COMMAND**-CODE*");						// The text and commands to disable CDP
	cdpSupported = true;							// Is CDP supported on interfaces
	disableProxyARPText = i18n("");					// The text and commands to disable Proxy ARP
	globalIPUnreachableSupported = true;
	globalUnreachableEnabled = true;
	disableUnreachablesText = i18n("*ABBREV*ICMP*-ABBREV* unreachable messages can be disabled with the following command:*CODE**COMMAND*set ip unreachable disable*-COMMAND**-CODE*");				// The text and commands to disable ICMP unreachable messages
	disableInformationText = i18n("");				// The text and commands to disable ICMP information messages
	disableMaskText = i18n("");						// The text and commands to disable ICMP mask messages
	disableRedirectText = i18n("");					// The text and commands to disable ICMP redirect messages
	globalRedirectSupported = true;					// Globally rather than on interfaces
	globalRedirectEnabled = true;					// Globally rather than on interfaces
	disableDirectedText = i18n("");					// The text and commands to disable directed broadcasts
	disableMOPText = i18n("");						// The text and commands to disable MOP
	disableActiveText = i18n("A port can be disabled on *DEVICETYPE* devices with the following command:*CODE**COMMAND*set port disable *CMDUSER*module*-CMDUSER*/*CMDUSER*port*-CMDUSER**-COMMAND**-CODE*");					// The text and commands to disable potentially unused interfaces
	filterName = i18n("filter lists");				// The filter list name for use in the filter issue text
	configFilterText = i18n("");					// The text and commands to configure network filtering
	defaultAutoTrunk = true;						// Default to automatically trunk
	disableTrunkText = i18n("Trunking can be disabled on *DEVICETYPE* device ports with the following command:*CODE**COMMAND*set trunk *CMDUSER*module*-CMDUSER*/*CMDUSER*port*-CMDUSER* off*-COMMAND**-CODE*");					// The text and commands to disable trunking on a port
	enablePortSecurityText = i18n("");				// The text and commands to enable port security

	switchportMode = portModeDynamic;
	cdpGlobal = true;
}


int CatalystInterfaces::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	interfaceListConfig *interfaceListPointer = 0;
	interfaceConfig *interfacePointer = 0;
	int tempInt = 0;
	Device::listStruct *tempList = 0;
	Device::listStruct *listPointer = 0;
	Device::listStruct *tempVLANList = 0;
	Device::listStruct *listVLANPointer = 0;

	// Interface...
	if ((strcmp(command->part(0), "set") == 0) && (strcmp(command->part(1), "vlan") == 0) && (strcmp(command->part(3), "firewall-vlan") != 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sVLAN Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		interfaceListPointer = getInterfaceList("VLANINTERFACES");
		if (interfaceListPointer == 0)
		{
			interfaceListPointer = addInterfaceList();
			interfaceListPointer->title = i18n("*ABBREV*VLAN*-ABBREV* Interfaces");
			interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices *ABBREV*VLAN*-ABBREV* interfaces.");
			interfaceListPointer->tableTitle = i18n("*ABBREV*VLAN*-ABBREV* interfaces");
			interfaceListPointer->label = "VLANINTERFACES";
			interfaceListPointer->interfaceDisableSupport = true;			// Is it possible to disable interfaces?
			interfaceListPointer->ipAddressSupported = false;
		}

		tempList = device->createPortList(command->part(2));
		listPointer = tempList;
		while (listPointer != 0)
		{
			if (command->parts == 4)
			{
				interfaceListPointer = getInterfaceList("PORTINTERFACES");
				if (interfaceListPointer == 0)
				{
					interfaceListPointer = addInterfaceList();
					interfaceListPointer->title = i18n("Module Ports");
					interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices module ports.");
					interfaceListPointer->tableTitle = i18n("Module ports");
					interfaceListPointer->label = "PORTINTERFACES";
					interfaceListPointer->vlanSupported = true;
					interfaceListPointer->portModeSupported = true;
					interfaceListPointer->interfaceDisableSupport = true;
					interfaceListPointer->cdpSupported = true;
				}

				tempVLANList = device->createPortList(command->part(3));
				listVLANPointer = tempVLANList;
				while (listVLANPointer != 0)
				{
					interfacePointer = getOnlyInterface(interfaceListPointer, "", atoi(listVLANPointer->listItem.c_str()), atoi(listVLANPointer->listItem.substr(listVLANPointer->listItem.find("/") + 1).c_str()));
					if (interfacePointer == 0)
					{
						interfacePointer = getInterface(interfaceListPointer, "", atoi(listVLANPointer->listItem.c_str()), atoi(listVLANPointer->listItem.substr(listVLANPointer->listItem.find("/") + 1).c_str()));
						interfacePointer->switchportMode = switchportMode;
						interfacePointer->cdp = cdpGlobal;
					}
					addVLAN(interfacePointer, listPointer->listItem.c_str());
					listVLANPointer = listVLANPointer->next;
				}

				// Delete list
				while (tempVLANList != 0)
				{
					listVLANPointer = tempVLANList->next;
					delete tempVLANList;
					tempVLANList = listVLANPointer;
				}
			}

			else
			{
				interfacePointer = getInterface(interfaceListPointer, listPointer->listItem.c_str());

				tempInt = 3;
				while (tempInt < command->parts)
				{
					if (strcmp(command->part(tempInt), "name") == 0)
					{
						tempInt++;
						interfacePointer->description.assign(command->part(tempInt));
					}
					else if (strcmp(command->part(tempInt), "state") == 0)
					{
						tempInt++;
						if (strcmp(command->part(tempInt), "active") == 0)
							interfacePointer->enabled = true;
						else
							interfacePointer->enabled = false;
					}

					tempInt++;
				}
			}

			listPointer = listPointer->next;
		}

		// Delete list
		while (tempList != 0)
		{
			listPointer = tempList->next;
			delete tempList;
			tempList = listPointer;
		}
	}

	// unreachable...
	else if ((strcmp(command->part(0), "set") == 0) && (strcmp(command->part(1), "ip") == 0) && (strcmp(command->part(2), "unreachable") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sUnreachables Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (strcmp(command->part(3), "disable") == 0)
			globalUnreachableEnabled = false;
		else
			globalUnreachableEnabled = true;
	}

	// redirect...
	else if ((strcmp(command->part(0), "set") == 0) && (strcmp(command->part(1), "ip") == 0) && (strcmp(command->part(2), "redirect") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sRedirect Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (strcmp(command->part(3), "disable") == 0)
			globalRedirectEnabled = false;
		else
			globalRedirectEnabled = true;
	}

	// CDP Globally...
	else if ((strcmp(command->part(0), "set") == 0) && (strcmp(command->part(1), "cdp") == 0) && (command->parts == 3))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sCDP Global Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (strcmp(command->part(2), "disable") == 0)
			cdpGlobal = false;
		else
			cdpGlobal = true;
		interfaceListPointer = getInterfaceList("PORTINTERFACES");
		if (interfaceListPointer != 0)
		{
			interfacePointer = interfaceListPointer->interface;
			while (interfacePointer != 0)
			{
				interfacePointer->cdp = cdpGlobal;
				interfacePointer = interfacePointer->next;
			}
		}
	}

	// CDP Individually...
	else if ((strcmp(command->part(0), "set") == 0) && (strcmp(command->part(1), "cdp") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sCDP Individual Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		interfaceListPointer = getInterfaceList("PORTINTERFACES");
		tempList = device->createPortList(command->part(3));
		listPointer = tempList;
		while (listPointer != 0)
		{
			interfacePointer = getOnlyInterface(interfaceListPointer, "", atoi(listPointer->listItem.c_str()), atoi(listPointer->listItem.substr(listPointer->listItem.find("/") + 1).c_str()));
			if (interfacePointer == 0)
			{
				interfacePointer = getInterface(interfaceListPointer, "", atoi(listPointer->listItem.c_str()), atoi(listPointer->listItem.substr(listPointer->listItem.find("/") + 1).c_str()));
				interfacePointer->switchportMode = switchportMode;
				interfacePointer->cdp = cdpGlobal;
			}

			if (strcmp(command->part(2), "disable") == 0)
				interfacePointer->cdp = false;
			else
				interfacePointer->cdp = true;

			listPointer = listPointer->next;
		}

		// Delete list
		while (tempList != 0)
		{
			listPointer = tempList->next;
			delete tempList;
			tempList = listPointer;
		}
	}

	// Trunk all...
	else if ((strcmp(command->part(0), "set") == 0) && (strcmp(command->part(1), "trunk") == 0) && (strcmp(command->part(2), "all") == 0) && (strcmp(command->part(3), "off") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sPort Trunking Off Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		switchportMode = portModeAccess;
		interfaceListPointer = getInterfaceList("PORTINTERFACES");
		if (interfaceListPointer != 0)
		{
			interfacePointer = interfaceListPointer->interface;
			while (interfacePointer != 0)
			{
				interfacePointer->switchportMode = switchportMode;
				interfacePointer = interfacePointer->next;
			}
		}
	}

	// Trunk...
	else if ((strcmp(command->part(0), "set") == 0) && (strcmp(command->part(1), "trunk") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sPort Trunking Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		interfaceListPointer = getInterfaceList("PORTINTERFACES");
		if (interfaceListPointer == 0)
		{
			interfaceListPointer = addInterfaceList();
			interfaceListPointer->title = i18n("Module Ports");
			interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices module ports.");
			interfaceListPointer->tableTitle = i18n("Module ports");
			interfaceListPointer->label = "PORTINTERFACES";
			interfaceListPointer->vlanSupported = true;
			interfaceListPointer->portModeSupported = true;
			interfaceListPointer->interfaceDisableSupport = true;
			interfaceListPointer->cdpSupported = true;
		}

		tempList = device->createPortList(command->part(2));
		listPointer = tempList;
		while (listPointer != 0)
		{
			interfacePointer = getOnlyInterface(interfaceListPointer, "", atoi(listPointer->listItem.c_str()), atoi(listPointer->listItem.substr(listPointer->listItem.find("/") + 1).c_str()));
			if (interfacePointer == 0)
			{
				interfacePointer = getInterface(interfaceListPointer, "", atoi(listPointer->listItem.c_str()), atoi(listPointer->listItem.substr(listPointer->listItem.find("/") + 1).c_str()));
				interfacePointer->switchportMode = switchportMode;
				interfacePointer->cdp = cdpGlobal;
			}

			if ((strcmp(command->part(3), "on") == 0) || (strcmp(command->part(3), "nonegotiate") == 0))
				interfacePointer->switchportMode = portModeTrunk;

			else if (strcmp(command->part(3), "off") == 0)
				interfacePointer->switchportMode = portModeAccess;

			else
				interfacePointer->switchportMode = portModeDynamic;

			listPointer = listPointer->next;
		}

		// Delete list
		while (tempList != 0)
		{
			listPointer = tempList->next;
			delete tempList;
			tempList = listPointer;
		}
	}

	// Port...
	else if ((strcmp(command->part(0), "set") == 0) && (strcmp(command->part(1), "port") == 0)&& (strcmp(command->part(3), "all") != 0))
	{

		interfaceListPointer = getInterfaceList("PORTINTERFACES");
		if (interfaceListPointer == 0)
		{
			interfaceListPointer = addInterfaceList();
			interfaceListPointer->title = i18n("Module Ports");
			interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices module ports.");
			interfaceListPointer->tableTitle = i18n("Module ports");
			interfaceListPointer->label = "PORTINTERFACES";
			interfaceListPointer->vlanSupported = true;
			interfaceListPointer->portModeSupported = true;
			interfaceListPointer->interfaceDisableSupport = true;
			interfaceListPointer->cdpSupported = true;
		}

		tempList = device->createPortList(command->part(3));
		listPointer = tempList;
		while (listPointer != 0)
		{
			interfacePointer = getOnlyInterface(interfaceListPointer, "", atoi(listPointer->listItem.c_str()), atoi(listPointer->listItem.substr(listPointer->listItem.find("/") + 1).c_str()));
			if (interfacePointer == 0)
			{
				interfacePointer = getInterface(interfaceListPointer, "", atoi(listPointer->listItem.c_str()), atoi(listPointer->listItem.substr(listPointer->listItem.find("/") + 1).c_str()));
				interfacePointer->switchportMode = switchportMode;
				interfacePointer->cdp = cdpGlobal;
			}

			if (strcmp(command->part(2), "name") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sPort Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				interfacePointer->description.assign(strstr(line, command->part(3)));
			}

			else if (strcmp(command->part(2), "disable") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sPort Disable Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				interfacePointer->enabled = false;
			}

			else if (strcmp(command->part(2), "description") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sPort Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				interfacePointer->description.assign(strstr(line, command->part(3)));
			}

			// All others...
			else
				device->lineNotProcessed(line);

			listPointer = listPointer->next;
		}

		// Delete list
		while (tempList != 0)
		{
			listPointer = tempList->next;
			delete tempList;
			tempList = listPointer;
		}
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int CatalystInterfaces::processDefaults(Device *device)
{
	return 0;
}


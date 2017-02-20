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
#include "general.h"


CiscoSecInterfaces::CiscoSecInterfaces()
{
	// Interface Options...
	useModuleAndPort = false;						// Use the module / port instead of the name
	useInterfaceZone = true;						// Use the interface zone
	zoneName = i18n("Name");						// The name for zone field
	filterIn = i18n("*ABBREV*ACL*-ABBREV*");		// The filter in table title text
	filterOut = i18n("*ABBREV*ACL*-ABBREV* Out");	// The filter out table title text
	showDescription = false;						// Show the interface description
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
	disableActiveText = i18n("Interfaces can be disabled *DEVICETYPE* device using the following command:*CODE**COMMAND*interface *CMDUSER*interface-name*-CMDUSER* shutdown*-COMMAND**-CODE*");					// The text and commands to disable potentially unused interfaces
	filterName = i18n("*ABBREV*ACL*-ABBREV*");		// The filter list name for use in the filter issue text
	configFilterText = i18n("An *ABBREV*ACL*-ABBREV* can be configured on an interface with the following command:*CODE**COMMAND*access-group *CMDUSER*acl*-CMDUSER* in interface *CMDUSER*interface-name*-CMDUSER**-COMMAND**-CODE*");					// The text and commands to configure network filtering
	defaultAutoTrunk = false;						// Default to automatically trunk
	disableTrunkText = i18n("");					// The text and commands to disable trunking on a port
	enablePortSecurityText = i18n("");				// The text and commands to enable port security
}


int CiscoSecInterfaces::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	interfaceListConfig *interfaceListPointer = 0;
	interfaceConfig *interfacePointer = 0;
	fpos_t filePosition;
	int tempInt = 0;

	// Sort out the interface list first...
	interfaceListPointer = getInterfaceList("PHYSINTERFACES");
	if (interfaceListPointer == 0)
	{
		interfaceListPointer = addInterfaceList();
		interfaceListPointer->title = i18n("Physical Network Interfaces");
		interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices physical network interfaces.");
		interfaceListPointer->tableTitle = i18n("Physical network interfaces");
		interfaceListPointer->label = "PHYSINTERFACES";
		interfaceListPointer->useSecurityLevel = true;
		interfaceListPointer->useStandbyAddress = true;
		interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
		interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
		interfaceListPointer->inboundFilterSupported = true;					// Is the inbound filtering supported?
		interfaceListPointer->outboudFilterSupported = false;					// Is the outbound filtering supported?
	}

	// nameif...
	if (strcmp(command->part(0), "nameif") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sInterface Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		interfacePointer = getInterface(interfaceListPointer, command->part(1));
		interfacePointer->zone.assign(command->part(2));
		interfacePointer->securityLevel = atoi(command->part(3) + 8);
	}

	// IP address...
	else if ((strcmp(command->part(0), "ip") == 0) && (strcmp(command->part(1), "address") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sInterface Address Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		interfacePointer = getInterfaceByZone(interfaceListPointer, command->part(2));
		if (interfacePointer != 0)
		{
			interfacePointer->address.assign(command->part(3));
			if (command->parts > 4)
				interfacePointer->netmask.assign(command->part(4));
		}
	}

	// failover...
	else if ((strcmp(command->part(0), "failover") == 0) && (strcmp(command->part(1), "ip") == 0) && (strcmp(command->part(2), "address") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sFailover IP Address Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		interfacePointer = getInterfaceByZone(interfaceListPointer, command->part(3));
		if (interfacePointer != 0)
			interfacePointer->standbyAddress.assign(command->part(4));
	}

	// Interface...
	else if (strcmp(command->part(0), "interface") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sInterface Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		interfacePointer = getOnlyInterface(interfaceListPointer, command->part(1));
		if (interfacePointer != 0)
		{
			if (strcmp(command->part(command->parts - 1), "shutdown") == 0)
				interfacePointer->enabled = false;
		}

		else
		{
			interfacePointer = getInterface(interfaceListPointer, command->part(1));

			// Read a line from the config...
			fgetpos(device->inputFile, &filePosition);
			device->readLine(line, lineSize);

			// Split it up into parts...
			command->setConfigLine(line);

			while ((line[0] == ' ') && (feof(device->inputFile) == 0))
			{

				// Name...
				if (strcmp(command->part(0), "nameif") == 0)
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sInterface Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					interfacePointer->zone.assign(command->part(1));
				}

				// security-level...
				else if (strcmp(command->part(0), "security-level") == 0)
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sInterface Security Level Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					interfacePointer->securityLevel = atoi(command->part(1));
				}

				// description...
				else if (strcmp(command->part(0), "description") == 0)
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sInterface Descriptionl Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					if (command->parts > 1)
						interfacePointer->description.assign(strstr(line, command->part(1)));
				}

				// shutdown...
				else if (strcmp(command->part(0), "shutdown") == 0)
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sInterface Shutdown Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					interfacePointer->enabled = false;
				}

				// ip address...
				else if ((strcmp(command->part(0), "ip") == 0) && (strcmp(command->part(1), "address") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sInterface IP Address Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					interfacePointer->address.assign(command->part(2));
					if ((command->parts > 3) && (strcmp(command->part(3), "standby") != 0))
					{
						interfacePointer->netmask.assign(command->part(3));
						tempInt = 4;
					}
					else
						tempInt = 3;
					if (strcmp(command->part(tempInt), "standby") == 0)
						interfacePointer->standbyAddress.assign(command->part(tempInt + 1));
				}

				// All others...
				else
					device->lineNotProcessed(line);

				// Read a line from the config...
				fgetpos(device->inputFile, &filePosition);
				device->readLine(line, lineSize);

				// Split it up into parts...
				command->setConfigLine(line);
			}

			// Set file position back
			fsetpos(device->inputFile, &filePosition);
		}
	}

	// Access Group...
	else if (strcmp(command->part(0), "access-group") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sAccess Group Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		// Old style...
		interfacePointer = getInterfaceByZone(interfaceListPointer, command->part(4));
		if (interfacePointer != 0)
		{
			if (strcmp(command->part(2), "in") == 0)
				addFilterList(interfacePointer, command->part(1), true);
			else
			{
				addFilterList(interfacePointer, command->part(1), false);
				interfaceListPointer->outboudFilterSupported = true;
			}
		}
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int CiscoSecInterfaces::processDefaults(Device *device)
{
	// Variables...
	interfaceListConfig *interfaceListPointer = 0;

	if (device->general != 0)
	{
		if (device->general->versionMajor > 6)
		{
			filterIn = i18n("*ABBREV*ACL*-ABBREV* In");		// The filter in table title text
			interfaceListPointer = interfaceList;
			while (interfaceListPointer != 0)
			{
				interfaceListPointer->outboudFilterSupported = true;					// Is the outbound filtering supported?
				interfaceListPointer = interfaceListPointer->next;
			}
		}
	}
	return 0;
}


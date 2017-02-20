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
 *      2. Any code that makes use of this library MUST display the        *
 *         returned text of the Nipper::getVersion() method. Since the     *
 *         text returned includes the version details and copyright of     *
 *         the library, the sugested place to show it would be with the    *
 *         callers "about program" information.                            *
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


// Include...
#include <cstring>
#include <sstream>
#include <string>
#include <cstdlib>

#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "device.h"
#include "general.h"
#include "administration.h"
#include "snmp.h"

using namespace std;


ScreenOSSNMP::ScreenOSSNMP()
{
	// Init SNMP support options...
	deviceSNMPSupportText = i18n("*DEVICETYPE* devices do not support *ABBREV*SNMP*-ABBREV* version 3. ");		// Intro Config section device specific text.
	supportSNMP3 = false;					// Does this device support SNMPv3?
	// N/A - supportSNMP3Upgrade = false;			// Do you have to upgrade to get support for SNMPv3
	// N/A - supportSNMP3UpgText = i18n("");			// SNMP 3 is supported from OS version ...
	disableSNMPCmdText = i18n("*ABBREV*SNMP*-ABBREV* access to *DEVICENAME* can be disabled by removing the community string configuration. This can be done with the following command:*CODE**COMMAND*unset snmp community *CMDUSER*community-string*-CMDUSER**-COMMAND**-CODE*");			// The text and command(s) to disable SNMP support
	configSNMPCommunityText = i18n("*ABBREV*SNMP*-ABBREV* community string access can be configured using the following commands:*CODE**COMMAND*set snmp community *CMDUSER*community-string*-CMDUSER* *CMDREQUIRE*read-only *CMDOR* read-write*-CMDREQUIRE**-COMMAND**COMMAND*set snmp host *CMDUSER*community-string*-CMDUSER* *CMDUSER*ip-address/cidr*-CMDUSER**-COMMAND**-CODE*");		// The text and command(s) to configure a community string
	// N/A - configSNMP3Text = i18n("");				// The text and command(s) to configure SNMP version 3
	// N/A - configSNMPViewText = i18n("");			// The text and command(s) to configure SNMP views
	configSNMPTrapsText = i18n("*ABBREV*SNMP*-ABBREV* traps can be configured using the following commands:*CODE**COMMAND*set snmp community *CMDUSER*community-string*-CMDUSER* *CMDREQUIRE*read-only *CMDOR* read-write*-CMDREQUIRE* trap-on*-COMMAND**COMMAND*set snmp host *CMDUSER*community-string*-CMDUSER* *CMDUSER*ip-address/cidr*-CMDUSER**-COMMAND**-CODE*");			// The text and command(s) to configure SNMP traps
	// N/A - configSNMPInformsText = i18n("");		// The text and command(s) to configure SNMP informs
	configSNMPReadOnlyText = i18n("*ABBREV*SNMP*-ABBREV* read only community string access can be configured using the following commands:*CODE**COMMAND*set snmp community *CMDUSER*community-string*-CMDUSER* read-only*-COMMAND**COMMAND*set snmp host *CMDUSER*community-string*-CMDUSER* *CMDUSER*ip-address/cidr*-CMDUSER**-COMMAND**-CODE*");		// The text and command(s) to configure SNMP read only access
	// N/A - configSNMPFilterText = i18n("");		// The text and command(s) to configure SNMP filtering

	// Community Options...
	communityView = false;				// SNMP view for the community
	communityFilter = false;			// SNMP Network Filtering
	communityIPv6Filter = false;		// SNMP IPv6 Network Filtering
	communitySpecificFilters = true;	// If the device uses an SNMP specific list. If false, it is std device filters
	communityRequiresHosts = true;		// If the SNMP community will not work without a list of those who can access it

	// Default communities...
	defaultReadOnly = "";				// Default read only community
	defaultReadWrite = "";				// Default read/write community
	defaultReadWriteAll = "";			// Default read/write all community

	// SNMP Trap/Inform Host Options...
	trapsOnly = true;					// Only Traps are supported
	trapsSNMPv3 = false;				// SNMP v3 support for traps
	trapsShowPort = false;				// Show Trap Host Port in Table
	trapsInterface = true;				// Show Interface in Table
	trapsInterfaceText = i18n("Interface");		// The Traps/Informs Host Table Interface Column Title
	trapsShowNotifications = false;		// Show Notifications in the Table
	trapsShowEventLevel = false;		// Show Notification Event Level in the Table

	// Traps/Informs Options...
	trapsShowExcluded = false;			// Show excluded traps
	trapsShowOptions = false;			// Show trap options

	// Host Options...
	hostShowInterface = true;			// Show the Interface in the Table
	hostShowCommunity = true;			// Show the Community in the Table
	hostShowFilterID = false;			// Show a filter ID if used
	hostFilterText = i18n("Filter");	// The Table column title for the filter text

	// Device specific settings...
	trapPort = 162;
}


int ScreenOSSNMP::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	snmpCommunity *communityPointer = 0;
	snmpHostStruct *snmpHostPointer = 0;
	snmpTrapHost *snmpTrapHostPointer = 0;
	snmpTrap *snmpTrapPointer = 0;
	int tempInt = 0;
	int tempVersion = 1;
	string tempString;
	string tempHost;
	string tempNetwork;
	string tempCommunity;
	string tempInterface;
	bool trapsOn = false;
	bool setting = false;

	// Init
	tempInt = 2;
	if (strcasecmp(command->part(0), "unset") == 0)
		setting = false;
	else
		setting = true;

	// Contact...
	if (strcasecmp(command->part(tempInt), "contact") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Contact Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		if (setting == true)
			contact.assign(command->part(tempInt));
	}

	// Location...
	else if (strcasecmp(command->part(tempInt), "location") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Location Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		if (setting == true)
			location.assign(command->part(tempInt));
	}

	// Trap port...
	else if ((strcasecmp(command->part(tempInt), "port") == 0) && (strcasecmp(command->part(tempInt + 1), "trap") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Trap Port Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 2;
		if (setting == true)
			trapPort = atoi(command->part(tempInt));
	}

	// Listen port...
	else if ((strcasecmp(command->part(tempInt), "port") == 0) && (strcasecmp(command->part(tempInt + 1), "listen") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Listen Port Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 2;
		if (setting == true)
			listenPort = atoi(command->part(tempInt));
	}

	// Name...
	else if (strcasecmp(command->part(tempInt), "name") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP System Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		if (setting == true)
		{
			name.assign(command->part(tempInt));
			if (device->general != 0)
			{
				if (device->general->hostname.empty())
					device->general->hostname.assign(command->part(tempInt));
			}
		}
	}

	// Authentication Traps...
	else if (strcasecmp(command->part(tempInt), "auth-trap") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Authentication Traps Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		snmpTrapPointer = addSNMPTrap();
		snmpTrapPointer->trap.assign("Authentication");
	}

	// Community...
	else if (strcasecmp(command->part(tempInt), "community") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Community Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		communityPointer = addSNMPCommunity();
		communityPointer->community.assign(command->part(tempInt));
		tempInt++;

		// Read-only / read/write
		if (strcasecmp(command->part(tempInt), "read-only") == 0)
			communityPointer->type = communityReadOnly;
		else
			communityPointer->type = communityReadWrite;
		tempInt++;

		while (tempInt < command->parts)
		{

			// Traps On / Off...
			if (strcasecmp(command->part(tempInt), "trap-off") == 0)
				communityPointer->trapsOn = false;
			else if (strcasecmp(command->part(tempInt), "trap-on") == 0)
				communityPointer->trapsOn = true;
			else if (strcasecmp(command->part(tempInt), "traffic") == 0)
			{
				snmpTrapPointer = addSNMPTrap();
				snmpTrapPointer->trap.assign("Traffic");
			}

			// Version...
			else if (strcasecmp(command->part(tempInt), "version") == 0)
			{
				tempInt++;
				if (strcasecmp(command->part(tempInt), "any") == 0)
					communityPointer->version = 0;
				else if (strcasecmp(command->part(tempInt), "v1") == 0)
					communityPointer->version = 1;
				else if ((strcasecmp(command->part(tempInt), "v2") == 0) || (strcasecmp(command->part(tempInt), "v2c") == 0))
					communityPointer->version = 2;
			}

			tempInt++;
		}
	}

	// SNMP Host...
	else if (strcmp(command->part(tempInt), "host") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Host Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		tempCommunity.assign(command->part(tempInt));
		tempInt++;
		tempHost.assign(command->part(tempInt));
		if (tempHost.find("/") != string::npos)
		{
			tempString.assign(tempHost.substr(tempHost.find("/") + 1));
			tempNetwork.assign(device->cidrToNetmask(tempString.c_str()));
			tempHost.erase(tempHost.find("/"));
		}
		else
		{
			tempInt++;
			tempNetwork.assign(command->part(tempInt));
		}
		tempInt++;
		while (tempInt < command->parts)
		{
			if (strcasecmp(command->part(tempInt), "src-interface") == 0)
			{
				tempInt++;
				tempInterface.assign(command->part(tempInt));
			}
			else if (strcasecmp(command->part(tempInt), "trap") == 0)
			{
				trapsOn = true;
				tempInt++;
				if ((strcasecmp(command->part(tempInt), "v2") == 0) || (strcasecmp(command->part(tempInt), "v2c") == 0))
					tempVersion = 2;
				else
					tempVersion = 1;
			}
			tempInt++;
		}

		// Add to NMS hosts...
		snmpHostPointer = addHost();
		snmpHostPointer->host.assign(tempHost);
		snmpHostPointer->networkMask.assign(tempNetwork);
		snmpHostPointer->interface.assign(tempInterface);
		snmpHostPointer->community.assign(tempCommunity);

		// Add to Trap Hosts...
		communityPointer = getSNMPCommunity(tempCommunity.c_str());
		if (communityPointer != 0)
		{
			if (communityPointer->trapsOn == true)
				trapsOn = true;
		}
		if (tempNetwork.compare("255.255.255.255") != 0)
			trapsOn = false;
		if (trapsOn == true)
		{
			snmpTrapHostPointer = addSNMPTrapHost();
			snmpTrapHostPointer->host.assign(tempHost);
			snmpTrapHostPointer->trap = true;
			snmpTrapHostPointer->version = tempVersion;	
			snmpTrapHostPointer->community.assign(tempCommunity);
			snmpTrapHostPointer->interface.assign(tempInterface);
		}
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int ScreenOSSNMP::generateConfigSpecificReport(Device *device)
{
	// Variables...
	ScreenOSAdministration::interfaceManagementConfig *interfacePointer = 0;
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	stringstream tempStream;
	string tempString;
	int errorCode = 0;

	// Get Config Report Section...
	configReportPointer = device->getConfigSection("CONFIG-SNMP");

	// Get Paragraph Pointer...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-SNMP-TABLE");

	// Trap Port...
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*SNMP*-ABBREV* Trap Port"));
	tempStream.str("");
	tempStream << trapPort;
	device->addTableData(paragraphPointer->table, tempStream.str().c_str());

	if (enabled == true)
	{
		paragraphPointer = device->addParagraph(configReportPointer);
		paragraphPointer->paragraph.assign(i18n("Access to the *ABBREV*SNMP*-ABBREV* service can be enabled on individual interfaces on *DEVICETYPE* devices. Table *TABLEREF* lists the interfaces with the *ABBREV*SNMP*-ABBREV* service enabled."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINSNMPINTER-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("*ABBREV*SNMP*-ABBREV* service interfaces");

		// Headings...
		device->addTableHeading(paragraphPointer->table, i18n("Interface"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Zone"), false);

		interfacePointer = dynamic_cast<ScreenOSAdministration *>(device->administration)->interfaces;
		while (interfacePointer != 0)
		{
			if ((interfacePointer->enabled == true) && (interfacePointer->snmp == true))
			{
				device->addTableData(paragraphPointer->table, interfacePointer->interface.c_str());
				device->addTableData(paragraphPointer->table, interfacePointer->zone.c_str());
			}
			interfacePointer = interfacePointer->next;
		}
	}

	return errorCode;
}


int ScreenOSSNMP::processDefaults(Device *device)
{
	// Variables...
	ScreenOSAdministration::interfaceManagementConfig *interfacePointer = 0;
	snmpCommunity *communityPointer = 0;
	bool enableSNMP = false;

	// Enable SNMP?
	communityPointer = community;
	while ((communityPointer != 0) && (enabled == false))
	{
		if ((communityPointer->enabled == true) && (hostCommunityExists(communityPointer->community.c_str()) == true))
		{
			enabled = true;
			snmp12Enabled = true;
		}
		communityPointer = communityPointer->next;
	}

	if (enabled == true)
	{
		interfacePointer = dynamic_cast<ScreenOSAdministration *>(device->administration)->interfaces;
		while (interfacePointer != 0)
		{
			if (interfacePointer->snmp == true)
				enableSNMP = true;
			interfacePointer = interfacePointer->next;
		}
		enabled = enableSNMP;
	}

	return 0;
}


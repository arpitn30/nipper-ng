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

#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "device.h"
#include "general.h"
#include "snmp.h"


using namespace std;


SonicOSSNMP::SonicOSSNMP()
{
	// Init SNMP support options...
	deviceSNMPSupportText = i18n("*ABBREV*SNMP*-ABBREV* version 1 can be configured on *DEVICETYPE* devices to provide remote management capabilities. Furthermore, *ABBREV*SNMP*-ABBREV* traps can be sent to a *ABBREV*NMS*-ABBREV*.");		// Intro Config section device specific text.
	supportSNMP3 = false;					// Does this device support SNMPv3?
	supportSNMP3Upgrade = false;			// Do you have to upgrade to get support for SNMPv3
	supportSNMP3UpgText = i18n("");			// SNMP 3 is supported from OS version ...
	disableSNMPCmdText = i18n("*ABBREV*SNMP*-ABBREV* can be disabled using the *DEVICETYPE* device web management interface.");			// The text and command(s) to disable SNMP support
	configSNMPCommunityText = i18n("The *ABBREV*SNMP*-ABBREV* community string can be configured using the *DEVICETYPE* device web management interface.");		// The text and command(s) to configure a community string
	configSNMP3Text = i18n("");				// The text and command(s) to configure SNMP version 3
	configSNMPViewText = i18n("");			// The text and command(s) to configure SNMP views
	configSNMPTrapsText = i18n("");			// The text and command(s) to configure SNMP traps
	configSNMPInformsText = i18n("");		// The text and command(s) to configure SNMP informs
	configSNMPReadOnlyText = i18n("");		// The text and command(s) to configure SNMP read only access
	configSNMPFilterText = i18n("");		// The text and command(s) to configure SNMP filtering

	enabled = false;						// Is the SNMP server enabled?
	snmp12Enabled = false;					// Is SNMP versions 1 or 2 configured?
	snmp3Enabled = false;					// Is SNMP version 3 configured?
	listenPort = 161;						// The UDP port SNMP will listen on

	snmpFilterText = i18n("Access Rule List");		// The device specific description of a filter (i.e. Cisco called them ACL)
	snmpFilterIPv6Text = i18n("*ABBREV*IPv6*-ABBREV* Filter");

	// Community Options...
	communityView = false;					// SNMP view for the community
	communityFilter = false;				// SNMP Network Filtering
	communityIPv6Filter = false;			// SNMP IPv6 Network Filtering
	communitySpecificFilters = false;		// If the device uses an SNMP specific list. If false, it is std device filters
	communityRequiresHosts = false;			// If the SNMP community will not work without a list of those who can access it

	// Default communities...
	defaultReadOnly = "public";				// Default read only community
	defaultReadWrite = "";					// Default read/write community
	defaultReadWriteAll = "";				// Default read/write all community

	// SNMP Trap/Inform Host Options...
	trapsOnly = true;						// Only Traps are supported
	trapsSNMPv3 = false;					// SNMP v3 support for traps
	trapsShowPort = false;					// Show Trap Host Port in Table
	trapsInterface = false;					// Show Interface in Table
	trapsInterfaceText = i18n("Interface");	// The Traps/Informs Host Table Interface Column Title
	trapsShowNotifications = false;			// Show Notifications in the Table
	trapsShowEventLevel = false;			// Show Notification Event Level in the Table

	// Traps/Informs Options...
	trapsShowExcluded = false;				// Show excluded traps
	trapsShowOptions = false;				// Show trap options

	// Host Options...
	hostShowInterface = false;				// Show the Interface in the Table
	hostShowCommunity = true;				// Show the Community in the Table
	hostShowFilterID = false;				// Show a filter ID if used
	hostFilterText = i18n("Filter");		// The Table column title for the filter text
}


int SonicOSSNMP::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	snmpCommunity *communityPointer = 0;
	snmpHostStruct *trapHostPointer = 0;

	// Enabled...
	if (strcmp(command->part(0), "snmp_Enable") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Enable Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (strcmp(command->part(1), "on") == 0)
		{
			enabled = true;
			snmp12Enabled = true;
		}
	}

	// Name...
	else if (strcmp(command->part(0), "snmp_Mib2SysName") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (command->parts > 1)
			name.assign(strstr(line, command->part(1)));
	}

	// Location...
	else if (strcmp(command->part(0), "snmp_Mib2SysLocation") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Location Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (command->parts > 1)
			location.assign(strstr(line, command->part(1)));
	}

	// Contact...
	else if (strcmp(command->part(0), "snmp_Mib2SysContact") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Contact Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (command->parts > 1)
			contact.assign(strstr(line, command->part(1)));
	}

	// Community...
	else if (strcmp(command->part(0), "snmp_GetCommunity") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Community Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (command->parts > 1)
		{
			communityPointer = addSNMPCommunity();
			communityPointer->enabled = true;
			communityPointer->community.assign(strstr(line, command->part(1)));
			communityPointer->type = communityReadOnly;
			communityPointer->version = 1;
		}
	}

	// Trap Community...
	else if (strcmp(command->part(0), "snmp_TrapCommunity") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Trap Community Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (command->parts > 1)
			trapCommunity.assign(strstr(line, command->part(1)));
	}

	// Trap Hosts...
	else if (strncmp(command->part(0), "snmp_HostIP", 11) == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Trap Host Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (command->parts > 1)
		{
			trapHostPointer = addHost();
			trapHostPointer->community.assign(trapCommunity);
			trapHostPointer->host.assign(strstr(line, command->part(1)));
		}
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int SonicOSSNMP::generateConfigSpecificReport(Device *device)
{
	// Device specific code for the config report goes here

	return 0;
}


int SonicOSSNMP::processDefaults()
{
	// Any default setting post processing code goes here...

	return 0;
}


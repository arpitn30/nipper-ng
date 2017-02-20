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
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>

#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "device.h"
#include "general.h"
#include "snmp.h"

using namespace std;


CiscoCSSSNMP::CiscoCSSSNMP()
{
	// Init SNMP support options...
	deviceSNMPSupportText = i18n("*DEVICETYPE* support only *ABBREV*SNMP*-ABBREV* versions 1 and 2c. ");		// Intro Config section device specific text.
	supportSNMP3 = false;					// Does this device support SNMPv3?
	supportSNMP3Upgrade = false;			// Do you have to upgrade to get support for SNMPv3
	// N/A - supportSNMP3UpgText = i18n("");			// SNMP 3 is supported from OS version ...
	disableSNMPCmdText = i18n("*ABBREV*SNMP*-ABBREV* can be disabled on *DEVICETYPE* with the following command:*CODE**COMMAND*restrict snmp*-COMMAND**-CODE*");			// The text and command(s) to disable SNMP support
	configSNMPCommunityText = i18n("*ABBREV*SNMP*-ABBREV* community strings can be configured with the following command:*CODE**COMMAND*snmp community *CMDUSER*community-string*-CMDUSER* *CMDREQUIRE*read-only *CMDOR* read-write*-CMDREQUIRE**-COMMAND**-CODE*");		// The text and command(s) to configure a community string
	// N/A - configSNMP3Text = i18n("");				// The text and command(s) to configure SNMP version 3
	// N/A - configSNMPViewText = i18n("");			// The text and command(s) to configure SNMP views
	configSNMPTrapsText = i18n("*ABBREV*SNMP*-ABBREV* trap hosts can be configured using the following command:*CODE**COMMAND*snmp trap-host *CMDUSER*ip-address*-CMDUSER* *CMDUSER*community-string*-CMDUSER* *CMDOPTION*snmpv2*-CMDOPTION**-COMMAND**-CODE*");			// The text and command(s) to configure SNMP traps
	// N/A - configSNMPInformsText = i18n("");		// The text and command(s) to configure SNMP informs
	configSNMPReadOnlyText = i18n("*ABBREV*SNMP*-ABBREV* read only community strings can be configured with the following command:*CODE**COMMAND*snmp community *CMDUSER*community-string*-CMDUSER* read-only*-COMMAND**-CODE*");		// The text and command(s) to configure SNMP read only access
	// N/A - configSNMPFilterText = i18n("");		// The text and command(s) to configure SNMP filtering

	enabled = true;

	// Community Options...
	communityView = false;				// SNMP view for the community
	communityFilter = false;			// SNMP Network Filtering
	communityIPv6Filter = false;		// SNMP IPv6 Network Filtering
	communitySpecificFilters = false;	// If the device uses an SNMP specific list. If false, it is std device filters
	communityRequiresHosts = false;		// If the SNMP community will not work without a list of those who can access it

	// Default communities...
	defaultReadOnly = "";				// Default read only community
	defaultReadWrite = "";				// Default read/write community
	defaultReadWriteAll = "";			// Default read/write all community

	// SNMP Trap/Inform Host Options...
	trapsOnly = true;					// Only Traps are supported
	trapsSNMPv3 = false;				// SNMP v3 support for traps
	trapsShowPort = false;				// Show Trap Host Port in Table
	trapsInterface = false;				// Show Interface in Table
	trapsInterfaceText = i18n("Interface");		// The Traps/Informs Host Table Interface Column Title
	trapsShowNotifications = false;		// Show Notifications in the Table
	trapsShowEventLevel = false;		// Show Notification Event Level in the Table

	// Traps/Informs Options...
	trapsShowExcluded = false;			// Show excluded traps
	trapsShowOptions = true;			// Show trap options

	// Device specific SNMP settings...
	reloadAllowed = false;
	trapSource.assign("Management");
}


int CiscoCSSSNMP::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	snmpCommunity *communityPointer = 0;
	snmpTrapHost *trapHostPointer = 0;
	snmpTrap *snmpTrapPointer = 0;
	int tempInt = 0;
	bool setting = false;

	// Init
	if (strcmp(command->part(0), "no") == 0)
	{
		tempInt = 2;
		setting = false;
	}
	else
	{
		tempInt = 1;
		setting = true;
	}

	// Restrict SNMP
	if ((strcmp(command->part(0), "restrict") == 0) && (strcmp(command->part(1), "snmp") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Restrict Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		enabled = false;
	}

	// snmp community?
	else if (strcmp(command->part(tempInt), "community") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Community Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		communityPointer = addSNMPCommunity();
		communityPointer->community.assign(command->part(tempInt));
		communityPointer->enabled = setting;
		tempInt++;
		if (strcasecmp(command->part(tempInt), "read-only") == 0)
			communityPointer->type = communityReadOnly;
		else
			communityPointer->type = communityReadWrite;
	}

	// Name
	else if (strcmp(command->part(tempInt), "name") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		name.assign(command->part(tempInt));
	}

	// Location...
	else if (strcmp(command->part(tempInt), "location") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Location Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		if (setting == true)
			location.assign(command->part(tempInt));
	}

	// Contact...
	else if (strcmp(command->part(tempInt), "contact") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Contact Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		if (setting == true)
			contact.assign(command->part(tempInt));
	}

	// Reload...
	else if (strcmp(command->part(tempInt), "reload-enable") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Reload Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		if (setting == true)
		{
			tempInt++;
			if (atoi(command->part(tempInt)) > 0)
				reloadAllowed = true;
		}
	}

	// SNMP Host...
	else if (strcmp(command->part(tempInt), "trap-host") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Trap Host Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		trapHostPointer = addSNMPTrapHost();
		trapHostPointer->host.assign(command->part(tempInt));
		tempInt++;
		trapHostPointer->community.assign(command->part(tempInt));
		tempInt++;
		if (strcmp(command->part(tempInt), "snmpv2") == 0)
			trapHostPointer->version = 2;
	}

	// Trap Source Address...
	else if (strcmp(command->part(tempInt), "trap-source") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Trap Source Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		if (setting == true)
		{
			tempInt++;
			if (strcmp(command->part(tempInt), "egress-port") == 0)
				trapSource.assign("*ABBREV*VLAN*-ABBREV* Egress");
			else if (strcmp(command->part(tempInt), "management") == 0)
				trapSource.assign("Management");
			else
				trapSource.assign(command->part(tempInt + 1));
		}
	}

	// Auth Traps...
	else if (strcmp(command->part(tempInt), "auth-traps") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Auth Traps Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		snmpTrapPointer = addSNMPTrap();
		snmpTrapPointer->trap.assign("Authentication");
	}

	// Generic Traps...
	else if ((strcmp(command->part(tempInt), "trap-type") == 0) && (strcmp(command->part(tempInt + 1), "generic") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Generic Traps Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		snmpTrapPointer = addSNMPTrap();
		snmpTrapPointer->trap.assign("cold start");
		snmpTrapPointer = addSNMPTrap();
		snmpTrapPointer->trap.assign("warm start");
		snmpTrapPointer = addSNMPTrap();
		snmpTrapPointer->trap.assign("link down");
		snmpTrapPointer = addSNMPTrap();
		snmpTrapPointer->trap.assign("link up");
	}

	// Enterprise Traps...
	else if ((strcmp(command->part(tempInt), "trap-type") == 0) && (strcmp(command->part(tempInt + 1), "enterprise") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Enterprise Traps Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		snmpTrapPointer = addSNMPTrap();
		snmpTrapPointer->trap.assign(command->part(tempInt));
		tempInt++;
		snmpTrapPointer->options.assign(command->part(tempInt));
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int CiscoCSSSNMP::processDefaults(Device *device)
{
	// Variables...
	snmpCommunity *communityPointer = community;

	// Enable SNMP Service...
	while ((communityPointer != 0) && (snmp12Enabled == false))
	{
		if (communityPointer->enabled == true)
			snmp12Enabled = true;
		communityPointer = communityPointer->next;
	}
	if (enabled == true)
		enabled = snmp12Enabled;

	return 0;
}

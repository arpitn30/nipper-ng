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


CiscoSecSNMP::CiscoSecSNMP()
{
	// Init SNMP support options...
	deviceSNMPSupportText = i18n("*DEVICETYPE* do not support version 3 of the *ABBREV*SNMP*-ABBREV*. ");		// Intro Config section device specific text.
	supportSNMP3 = false;					// Does this device support SNMPv3?
	supportSNMP3Upgrade = false;			// Do you have to upgrade to get support for SNMPv3
	supportSNMP3UpgText = i18n("");			// SNMP 3 is supported from OS version ...
	// The following is set in the defaults section, due to slight differences between software versions
	//disableSNMPCmdText = i18n("");			// The text and command(s) to disable SNMP support
	configSNMPCommunityText = i18n("*ABBREV*SNMP*-ABBREV* community strings can be configured with the following command:*CODE**COMMAND*snmp-server community *CMDUSER*community-string*-CMDUSER**-COMMAND**-CODE*");		// The text and command(s) to configure a community string
	// Not supported - configSNMP3Text = i18n("");				// The text and command(s) to configure SNMP version 3
	// Not supported - configSNMPViewText = i18n("");			// The text and command(s) to configure SNMP views
	configSNMPTrapsText = i18n("*ABBREV*SNMP*-ABBREV* trap hosts can be configured with the following command:*CODE**COMMAND*snmp-server host *CMDUSER*interface*-CMDUSER* *CMDUSER*ip-address*-CMDUSER* trap community *CMDUSER*community-string*-CMDUSER* *CMDOPTION*version *CMDREQUIRE*1 *CMDOR* 2c*-CMDREQUIRE**-CMDOPTION**-COMMAND**-CODE*");			// The text and command(s) to configure SNMP traps
	// Not supported - configSNMPInformsText = i18n("");		// The text and command(s) to configure SNMP informs
	// N/A - configSNMPReadOnlyText = i18n("");		// The text and command(s) to configure SNMP read only access
	configSNMPFilterText = i18n("Access to *ABBREV*SNMP*-ABBREV* from a *ABBREV*NMS*-ABBREV* or *ABBREV*SNMP*-ABBREV* management host can be configured using the following command:*CODE**COMMAND*snmp-server host *CMDUSER*ip-address*-CMDUSER**-COMMAND**-CODE*");		// The text and command(s) to configure SNMP filtering

	enabled = false;						// Is the SNMP server enabled?
	snmp12Enabled = false;					// Is SNMP versions 1 or 2 configured?
	snmp3Enabled = false;					// Is SNMP version 3 configured?


	// Community Options...
	communitySpecificFilters = true;	// If the device uses an SNMP specific list. If false, it is std device filters
	communityRequiresHosts = true;		// If the SNMP community will not work without a list of those who can access it

	// Default communities...
	defaultReadOnly = "public";			// Default read only community

	// SNMP Trap/Inform Host Options...
	trapsOnly = true;					// Only Traps are supported
	trapsSNMPv3 = false;				// SNMP v3 support for traps
	trapsShowPort = true;				// Show Trap Host Port in Table
	trapsInterface = true;				// Show Interface in Table
	trapsInterfaceText = i18n("Interface");		// The Traps/Informs Host Table Interface Column Title
	trapsShowNotifications = false;		// Show Notifications in the Table
	trapsShowEventLevel = false;		// Show Notification Event Level in the Table

	// Traps/Informs Options...
	trapsShowExcluded = false;			// Show excluded traps
	trapsShowOptions = true;			// Show trap options

	// Host Options...
	hostShowInterface = false;			// Show the Interface in the Table
	hostShowCommunity = false;			// Show the Community in the Table
	hostShowFilterID = false;			// Show a filter ID if used
	hostFilterText = i18n("Filter");	// The Table column title for the filter text
}


int CiscoSecSNMP::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	snmpCommunity *communityPointer = 0;
	snmpTrapHost *trapHostPointer = 0;
	snmpHostStruct *snmpHostPointer = 0;
	snmpTrap *snmpTrapPointer = 0;
	int tempInt = 0;
	int tempInt2 = 0;
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

	// Disable SNMP...
	if (strcmp(command->part(tempInt), "enable") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Enable Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		enabled = setting;
	}

	// Location...
	else if (strcmp(command->part(tempInt), "location") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Location Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		if (setting == true)
			location.assign(line + 9 + string(line).find("location"));
	}

	// Contact...
	else if (strcmp(command->part(tempInt), "contact") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Contact Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		if (setting == true)
			contact.assign(line + 8 + string(line).find("contact"));
	}

	// Listen Port...
	else if (strcmp(command->part(tempInt), "listen-port") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Listen Port Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		if (setting == true)
			listenPort = atoi(command->part(tempInt + 1));
		else
			listenPort = 161;
	}

	// snmp community?
	else if (strcmp(command->part(tempInt), "community") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Community Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		communityPointer = addSNMPCommunity();
		communityPointer->community.assign(command->part(tempInt));
		communityPointer->type = communityReadOnly;
		communityPointer->enabled = setting;
	}

	// SNMP Trap Host...
	else if ((strcmp(command->part(tempInt), "host") == 0) && (strcmp(command->part(tempInt + 3), "trap") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Trap Host Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		trapHostPointer = addSNMPTrapHost();
		trapHostPointer->version = 1;
		trapHostPointer->port = 162;
		trapHostPointer->trap = false;
		trapHostPointer->interface.assign(command->part(tempInt));
		tempInt++;
		trapHostPointer->host.assign(command->part(tempInt));
		tempInt += 2;

		while (tempInt < command->parts)
		{
			// Community?
			if (strcmp(command->part(tempInt), "community") == 0)
			{
				tempInt++;
				trapHostPointer->community.assign(command->part(tempInt));
			}

			// Version?
			else if (strcmp(command->part(tempInt), "version") == 0)
			{
				tempInt++;
				if (strcmp(command->part(tempInt), "2c") == 0)
					trapHostPointer->version = 2;
				else
					trapHostPointer->version = 1;
			}

			// UDP Port?
			else if (strcmp(command->part(tempInt), "udp-port") == 0)
			{
				tempInt++;
				trapHostPointer->port = atoi(command->part(tempInt));
			}

			tempInt++;
		}
	}

	// SNMP NMS Host...
	else if (strcmp(command->part(tempInt), "host") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP NMS Host Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		snmpHostPointer = addHost();
		snmpHostPointer->interface.assign(command->part(tempInt));
		tempInt++;
		snmpHostPointer->host.assign(command->part(tempInt));
		tempInt++;
		while (tempInt < command->parts)
		{
			if (strcmp(command->part(tempInt), "community") == 0)
			{
				tempInt++;
				snmpHostPointer->community.assign(command->part(tempInt));
			}
			tempInt++;
		}
	}

	// SNMP Trap...
	else if ((strcmp(command->part(tempInt), "enable") == 0) && (strcmp(command->part(tempInt + 1), "traps") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Traps Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (setting == true)
		{
			tempInt += 2;
			snmpTrapPointer = addSNMPTrap();
			snmpTrapPointer->trap.assign(command->part(tempInt));
			tempInt2 = tempInt;
			tempInt++;
			if (tempInt < command->parts)
			{
				snmpTrapPointer->options.assign(command->part(tempInt));
				tempInt++;
			}

			while (tempInt < command->parts)
			{
				snmpTrapPointer = addSNMPTrap();
				snmpTrapPointer->trap.assign(command->part(tempInt2));
				snmpTrapPointer->options.assign(command->part(tempInt));
				tempInt++;
			}
		}
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int CiscoSecSNMP::processDefaults(Device *device)
{
	// Variables...
	snmpCommunity *communityPointer = 0;

	// Enable SNMP support?
	communityPointer = community;
	while (communityPointer != 0)
	{
		if ((communityPointer->enabled == true) && (hostCommunityExists(communityPointer->community.c_str()) == true))
		{
			enabled = true;
			snmp12Enabled = true;
		}
		communityPointer = communityPointer->next;
	}

	// Set disable SNMP text...
	if (device->general->versionMajor > 6)
		disableSNMPCmdText = i18n("*ABBREV*SNMP*-ABBREV* can be disabled with the following command:*CODE**COMMAND*no snmp-server enable*-COMMAND**-CODE*");			// The text and command(s) to disable SNMP support
	else
		disableSNMPCmdText = i18n("*ABBREV*SNMP*-ABBREV* can be disabled with the following command:*CODE**COMMAND*no snmp-server*-COMMAND**-CODE*");			// The text and command(s) to disable SNMP support

	return 0;
}


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

#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "device.h"
#include "general.h"
#include "snmp.h"

using namespace std;


ProCurveSNMP::ProCurveSNMP()
{
	// Init SNMP support options...
	deviceSNMPSupportText = i18n("*DEVICETYPE* support all three versions of the *ABBREV*SNMP*-ABBREV*. ");		// Intro Config section device specific text.
	supportSNMP3 = true;					// Does this device support SNMPv3?
	// N/A - supportSNMP3Upgrade = false;			// Do you have to upgrade to get support for SNMPv3
	// N/A - supportSNMP3UpgText = i18n("");			// SNMP 3 is supported from OS version ...
	disableSNMPCmdText = i18n("*ABBREV*SNMP*-ABBREV* versions 1 and 2 can be disabled on *DEVICETYPE* devices with the following command:*CODE**COMMAND*no snmp-server enable*-COMMAND**-CODE*");			// The text and command(s) to disable SNMP support
	configSNMPCommunityText = i18n("*ABBREV*SNMP*-ABBREV* community strings can be configured with the following command:*CODE**COMMAND*snmp-server community *CMDUSER*community-string*-CMDUSER* *CMDOPTION*manager *CMDOR* operator*-CMDOPTION* *CMDOPTION*restricted *CMDOR* unrestricted*-CMDOPTION**-COMMAND**-CODE*");		// The text and command(s) to configure a community string
	configSNMP3Text = i18n("*ABBREV*SNMP*-ABBREV* version 3 access can be configured by creating a user and adding the user to a group. This can be configured using the following commands:*CODE**COMMAND*snmpv3 user *CMDUSER*username*-CMDUSER* *CMDOPTION*auth *CMDREQUIRE*md5 *CMDOR* sha*-CMDREQUIRE* *CMDUSER*auth-password*-CMDUSER**-CMDOPTION* *CMDOPTION*priv *CMDREQUIRE*des *CMDOR* aes*-CMDREQUIRE* *CMDUSER*priv-password*-CMDUSER**-CMDOPTION**-COMMAND**COMMAND*snmpv3 group *CMDUSER*groupname*-CMDUSER* user *CMDUSER*username*-CMDUSER* sec-model ver3*-COMMAND**-CODE*");				// The text and command(s) to configure SNMP version 3
	// N/A - configSNMPViewText = i18n("");			// The text and command(s) to configure SNMP views
	configSNMPTrapsText = i18n("*ABBREV*SNMP*-ABBREV* trap hosts can be configured using the following command:*CODE**COMMAND*snmp-server host *CMDUSER*ip-address*-CMDUSER* *CMDUSER*community-string*-CMDUSER* *CMDOPTION*none *CMDOR* debug *CMDOR* all *CMDOR* not-info *CMDOR* critical*-CMDOPTION**-COMMAND**-CODE*");			// The text and command(s) to configure SNMP traps
	// N/A - configSNMPInformsText = i18n("");		// The text and command(s) to configure SNMP informs
	configSNMPReadOnlyText = i18n("Read only community string access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* can be configured using the following command:*CODE**COMMAND*snmp-server community *CMDUSER*community-string*-CMDUSER* *CMDOPTION*manager *CMDOR* operator*-CMDOPTION* restricted*-COMMAND**-CODE*");		// The text and command(s) to configure SNMP read only access
	// N/A - configSNMPFilterText = i18n("");		// The text and command(s) to configure SNMP filtering

	enabled = false;						// Is the SNMP server enabled?
	snmp12Enabled = true;					// Is SNMP versions 1 or 2 configured?
	snmp3Enabled = false;					// Is SNMP version 3 configured?

	// Community Options...
	communityView = true;				// SNMP view for the community
	communityFilter = false;			// SNMP Network Filtering
	communityIPv6Filter = false;		// SNMP IPv6 Network Filtering
	communitySpecificFilters = false;	// If the device uses an SNMP specific list. If false, it is std device filters
	communityRequiresHosts = false;		// If the SNMP community will not work without a list of those who can access it

	// Default communities...
	defaultReadOnly = "";				// Default read only community
	defaultReadWrite = "";				// Default read/write community
	defaultReadWriteAll = "";			// Default read/write all community

	// View support options...
	viewSeperated = false;				// Separate the views into different tables
	viewExcludes = false;				// Show the Include/Exclude View Table column
	viewMIBText = i18n("Description");		// What the MIB column title in the table should be called

	// SNMP Trap/Inform Host Options...
	trapsOnly = true;					// Only Traps are supported
	trapsSNMPv3 = false;				// SNMP v3 support for traps
	trapsShowPort = false;				// Show Trap Host Port in Table
	trapsInterface = false;				// Show Interface in Table
	trapsInterfaceText = i18n("Interface");		// The Traps/Informs Host Table Interface Column Title
	trapsShowNotifications = false;		// Show Notifications in the Table
	trapsShowEventLevel = true;		// Show Notification Event Level in the Table

	// Traps/Informs Options...
	trapsShowExcluded = false;			// Show excluded traps
	trapsShowOptions = true;			// Show trap options

	// SNMP User Options...
	showUserRemote = false;				// Show the remote host/port setting
	showUserPriv = true;				// Show the privacy settings
	showUserFilter = false;				// Show the Filter column in the table
	showUserIPv6Filter = false;			// Show the IPv6 Filter column in the table
	userFilterText = i18n("Filter");	// The Text for the Filter table column title
	userIPv6FilterText = i18n("*ABBREV*IPv6*-ABBREV* Filter");	// The Text for the IPv6 Filter table column title

	// SNMP Group Options...
	snmpGroupShowType = false;			// Enable/Disable SNMPv3 type in table
	snmpGroupReadView = false;			// Enable/Disable Read Views
	snmpGroupWriteView = false;			// Enable/Disable Write Views
	snmpGroupNotifyView = false;		// Enable/Disable Notify Views
	snmpGroupFilter = false;			// Enable/Disable Filter support
	snmpGroupIPv6Filter = false;		// Enable/Disable IPv6 Filter support
	groupFilterText = i18n("Filter");	// The Text for the Filter table column title
	groupIPv6FilterText = i18n("*ABBREV*IPv6*-ABBREV* Filter");		// The Text for the IPv6 Filter table column title

	// Device specific options...
	authenticationMIB = false;
}


int ProCurveSNMP::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	snmpCommunity *communityPointer = 0;
	snmpTrapHost *trapHostPointer = 0;
	snmpView *viewPointer = 0;
	snmpTrap *snmpTrapPointer = 0;
	snmpUserStruct *snmpUserPointer = 0;
	snmpGroupStruct *snmpGroupPointer = 0;
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

	// Location...
	if (strcasecmp(command->part(tempInt), "location") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Location Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		if (setting == true)
			location.assign(command->part(tempInt));
	}

	// Contact...
	else if (strcasecmp(command->part(tempInt), "contact") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Contact Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		if (setting == true)
			location.assign(command->part(tempInt));
	}

	// Community...
	else if (strcasecmp(command->part(tempInt), "community") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Community Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		communityPointer = addSNMPCommunity();
		communityPointer->community.assign(command->part(tempInt));
		communityPointer->enabled = setting;
		communityPointer->type = communityReadOnly;
		communityPointer->view.assign("Operator");
		tempInt++;
		while (tempInt < command->parts)
		{
			if (strcasecmp(command->part(tempInt), "manager") == 0)
				communityPointer->view.assign("Manager");
			else if (strcasecmp(command->part(tempInt), "operator") == 0)
				communityPointer->view.assign("Operator");
			else if (strcasecmp(command->part(tempInt), "restricted") == 0)
				communityPointer->type = communityReadOnly;
			else if (strcasecmp(command->part(tempInt), "unrestricted") == 0)
				communityPointer->type = communityReadWrite;

			tempInt++;
		}

		// Create view for the community...
		if (getSNMPView(communityPointer->view.c_str()) == 0)
		{
			if (communityPointer->view.compare("Operator") == 0)
				addSNMPView(communityPointer->view.c_str(), i18n("Access to all *ABBREV*MIB*-ABBREV* objects except CONFIG."));
			else
			{
				addSNMPView(communityPointer->view.c_str(), i18n("Access to all *ABBREV*MIB*-ABBREV* objects."));
				viewPointer = getSNMPView(communityPointer->view.c_str());
				viewPointer->everything = true;
			}
		}
	}

	// SNMP Host...
	else if (strcmp(command->part(tempInt), "host") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Host Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		trapHostPointer = addSNMPTrapHost();
		trapHostPointer->trap = true;
		trapHostPointer->version = 1;
		trapHostPointer->host.assign(command->part(tempInt));
		tempInt++;
		trapHostPointer->community.assign(command->part(tempInt));
		tempInt++;
		if (tempInt < command->parts)
			trapHostPointer->eventLevel.assign(command->part(tempInt));
	}

	// SNMP Traps...
	else if ((strcmp(command->part(tempInt), "enable") == 0) && (strcmp(command->part(tempInt), "traps") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Traps Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 2;
		snmpTrapPointer = addSNMPTrap();
		snmpTrapPointer->include = setting;
		snmpTrapPointer->trap.assign(command->part(tempInt));
		tempInt++;
		if (tempInt < command->parts)
			snmpTrapPointer->options.assign(command->part(tempInt));
	}

	// SNMP Enable...
	else if (strcmp(command->part(tempInt), "enable") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Enable Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		snmp12Enabled = setting;
	}

	// SNMP User...
	else if (strcmp(command->part(tempInt), "user") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMPv3 User Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		snmpUserPointer = addSNMPUser();
		snmpUserPointer->user.assign(command->part(tempInt));
		snmpUserPointer->snmpv3 = snmpV3NoAuth;
		snmpUserPointer->version = 3;
		tempInt++;
		while (tempInt < command->parts)
		{
			if (strcmp(command->part(tempInt), "auth") == 0)
			{
				snmpUserPointer->snmpv3 = snmpV3Auth;
				tempInt++;
				if (strcmp(command->part(tempInt), "sha") == 0)
					snmpUserPointer->auth = snmpV3AuthSHA;
				else
					snmpUserPointer->auth = snmpV3AuthMD5;
				tempInt++;
				snmpUserPointer->authPassword.assign(command->part(tempInt));
			}
			else if (strcmp(command->part(tempInt), "priv") == 0)
			{
				snmpUserPointer->snmpv3 = snmpV3Auth;
				tempInt++;
				if (strcmp(command->part(tempInt), "aes") == 0)
				{
					snmpUserPointer->priv = snmpV3PrivAES128;
					tempInt++;
				}
				else if (strcmp(command->part(tempInt), "des") == 0)
				{
					snmpUserPointer->priv = snmpV3PrivDES;
					tempInt++;
				}
				snmpUserPointer->privPassword.assign(command->part(tempInt));
			}
			tempInt++;
		}
	}

	// SNMP Group...
	else if (strcmp(command->part(tempInt), "group") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMPv3 Group Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		snmpGroupPointer = addSNMPGroup();
		snmpGroupPointer->group.assign(command->part(tempInt));
		snmpGroupPointer->version = 3;
		tempInt++;
		while (tempInt < command->parts)
		{
			if (strcmp(command->part(tempInt), "user") == 0)
			{
				tempInt++;
				snmpUserPointer = getSNMPUser(command->part(tempInt));
				if (snmpUserPointer != 0)
					snmpUserPointer->group.assign(snmpGroupPointer->group);
			}
			else if (strcmp(command->part(tempInt), "sec-model") == 0)
			{
				tempInt++;
				if (strcmp(command->part(tempInt), "ver3") == 0)
					snmpGroupPointer->version = 3;
				else if (strcmp(command->part(tempInt), "ver2c") == 0)
					snmpGroupPointer->version = 2;
				else if (strcmp(command->part(tempInt), "ver1") == 0)
					snmpGroupPointer->version = 1;
			}
			tempInt++;
		}
	}

	// Authentication MIB...
	else if ((strcasecmp(command->part(tempInt), "mib") == 0) && (strcasecmp(command->part(tempInt + 1), "hpSwitchAuthMIB") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Authentication MIB Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 2;
		if (strcasecmp(command->part(tempInt), "included") == 0)
			authenticationMIB = true;
		else
			authenticationMIB = false;
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int ProCurveSNMP::processDefaults(Device *device)
{
	// Variables...
	snmpCommunity *communityPointer = 0;

	// Enable SNMP server...
	if (snmp12Enabled == true)
	{
		communityPointer = community;
		while ((communityPointer != 0) && (enabled == false))
		{
			if (communityPointer->enabled == true)
				enabled = true;
			communityPointer = communityPointer->next;
		}
	}

	return 0;
}


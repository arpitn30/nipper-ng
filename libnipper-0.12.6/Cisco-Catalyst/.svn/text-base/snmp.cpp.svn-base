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
#include "general.h"
#include "device.h"
#include "snmp.h"

using namespace std;


CatalystSNMP::CatalystSNMP()
{
	// Init SNMP support options...
	deviceSNMPSupportText = i18n("All *DEVICETYPE* support *ABBREV*SNMP*-ABBREV* versions 1 and 2, *ABBREV*SNMP*-ABBREV* version 3 is supported from *DEVICEOS* 6.");		// Intro Config section device specific text.
	supportSNMP3 = false;					// Does this device support SNMPv3?
	supportSNMP3Upgrade = false;			// Do you have to upgrade to get support for SNMPv3
	supportSNMP3UpgText = i18n("*ABBREV*SNMP*-ABBREV* version 3 is supported from *DEVICEOS* 6.");			// SNMP 3 is supported from OS version ...
	disableSNMPCmdText = i18n("*ABBREV*SNMP*-ABBREV* can be disabled with the following command:*CODE**COMMAND*set snmp disable*-COMMAND**-CODE*");			// The text and command(s) to disable SNMP support
	configSNMPCommunityText = i18n("*ABBREV*SNMP*-ABBREV* community strings can be configured with the following command:*CODE**COMMAND*set snmp community *CMDREQUIRE*read-only *CMDOR* read-write *CMDOR* read-write-all*-CMDREQUIRE* *CMDUSER*community-string*-CMDUSER**-COMMAND**-CODE*");		// The text and command(s) to configure a community string
	configSNMP3Text = i18n("*ABBREV*SNMP*-ABBREV* version 3 can be configured by creating a user then adding that user to a group. This can be configured using the following commands:*CODE**COMMAND*set snmp user *CMDUSER*username*-CMDUSER* remote *CMDUSER*engineid*-CMDUSER* *CMDOPTION*authentication *CMDREQUIRE*md5 *CMDOR* sha*-CMDREQUIRE* auth-password*-CMDOPTION* *CMDOPTION*privacy *CMDOPTION*des *CMDOR* 3des *CMDOR* aes *CMDREQUIRE*128 *CMDOR* 192 *CMDOR* 256*-CMDREQUIRE**-CMDOPTION* *CMDUSER*priv-password*-CMDUSER**-CMDOPTION**-COMMAND**COMMAND*set snmp group *CMDUSER*groupname*-CMDUSER* user *CMDUSER*username*-CMDUSER* security-model v3*-COMMAND**-CODE*");				// The text and command(s) to configure SNMP version 3
	configSNMPViewText = i18n("*ABBREV*SNMP*-ABBREV* views can be configured and assigned to a community string using the following commands:*CODE**COMMAND*set snmp view *CMDUSER*viewname*-CMDUSER* *CMDUSER*mib*-CMDUSER* *CMDOPTION*mask*-CMDOPTION* *CMDOPTION*included *CMDOR* excluded*-CMDOPTION**-COMMAND**COMMAND*set snmp community-ext *CMDUSER*community-string*-CMDUSER* *CMDREQUIRE*read-only *CMDOR* read-write *CMDOR* read-write-all*-CMDREQUIRE* view *CMDUSER*viewname*-CMDUSER* *CMDOPTION*access *CMDUSER*access-number*-CMDUSER**-CMDOPTION**-COMMAND**-CODE*");			// The text and command(s) to configure SNMP views
	configSNMPTrapsText = i18n("*ABBREV*SNMP*-ABBREV* traps can be configured with the following command:*CODE**COMMAND*set snmp trap *CMDUSER*ip-address*-CMDUSER* *CMDUSER*community-string*-CMDUSER**-COMMAND**-CODE*");			// The text and command(s) to configure SNMP traps
	configSNMPInformsText = i18n("*ABBREV*SNMP*-ABBREV* informs can be configuerd with the following command:*CODE**COMMAND*set snmp inform *CMDUSER*ip-address*-CMDUSER* *CMDUSER*community-string*-CMDUSER**-COMMAND**-CODE*");		// The text and command(s) to configure SNMP informs
	configSNMPReadOnlyText = i18n("*ABBREV*SNMP*-ABBREV* read-write access can be disabled by clearing the community strings with the following command:*CODE**COMMAND*clear snmp community-ext *CMDUSER*community-string*-CMDUSER**-COMMAND**-CODE*");		// The text and command(s) to configure SNMP read only access
	configSNMPFilterText = i18n("*ABBREV*SNMP*-ABBREV* access list can be configured and assigned to a community string using the following commands:*CODE**COMMAND*set snmp access-list *CMDUSER*access-number*-CMDUSER* *CMDUSER*ip-address*-CMDUSER* *CMDOPTION*ipmask *CMDUSER*network-mask*-CMDUSER**-CMDOPTION**-COMMAND**COMMAND*set snmp community-ext *CMDUSER*community-string*-CMDUSER* *CMDREQUIRE*read-only *CMDOR* read-write *CMDOR* read-write-all*-CMDREQUIRE* *CMDOPTION*view *CMDUSER*viewname*-CMDUSER**-CMDOPTION* access *CMDUSER*access-number*-CMDUSER**-COMMAND**-CODE*");		// The text and command(s) to configure SNMP filtering

	enabled = true;							// Is the SNMP server enabled?
	snmp12Enabled = false;					// Is SNMP versions 1 or 2 configured?
	snmp3Enabled = false;					// Is SNMP version 3 configured?

	snmpFilterText = i18n("Access List");	// The device specific description of a filter (i.e. Cisco called them ACL)

	// Community Options...
	communityView = true;				// SNMP view for the community
	communityFilter = true;				// SNMP Network Filtering
	communityIPv6Filter = false;		// SNMP IPv6 Network Filtering
	communitySpecificFilters = true;	// If the device uses an SNMP specific list. If false, it is std device filters
	communityRequiresHosts = false;		// If the SNMP community will not work without a list of those who can access it

	// Default communities...
	defaultReadOnly = "public";			// Default read only community
	defaultReadWrite = "private";		// Default read/write community
	defaultReadWriteAll = "secret";		// Default read/write all community

	// View support options...
	viewSeperated = false;				// Separate the views into different tables
	viewExcludes = false;				// Show the Include/Exclude View Table column
	viewMIBText = i18n("*ABBREV*MIB*-ABBREV*");		// What the MIB column title in the table should be called

	// SNMP Trap/Inform Host Options...
	trapsOnly = false;					// Only Traps are supported
	trapsSNMPv3 = false;				// SNMP v3 support for traps
	trapsShowPort = true;				// Show Trap Host Port in Table
	trapsInterface = false;				// Show Interface in Table
	trapsInterfaceText = i18n("Interface");		// The Traps/Informs Host Table Interface Column Title
	trapsShowNotifications = false;		// Show Notifications in the Table
	trapsShowEventLevel = false;		// Show Notification Event Level in the Table

	// Traps/Informs Options...
	trapsShowExcluded = true;			// Show excluded traps
	trapsShowOptions = false;			// Show trap options

	// Host Options...
	hostShowInterface = false;			// Show the Interface in the Table
	hostShowCommunity = false;			// Show the Community in the Table
	hostShowFilterID = true;			// Show a filter ID if used
	hostFilterText = i18n("Access List");	// The Table column title for the filter text

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

	// Device Specific settings...
	buffer = 95;
	rmonMemory = 85;
	rmonSupport = false;
}


int CatalystSNMP::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	snmpCommunity *communityPointer = 0;
	snmpTrapHost *trapHostPointer = 0;
	snmpHostStruct *snmpHostPointer = 0;
	snmpTrap *snmpTrapPointer = 0;
	snmpUserStruct *snmpUserPointer = 0;
	snmpGroupStruct *snmpGroupPointer = 0;
	int tempInt = 0;
	bool setting = false;

	// Init
	tempInt = 2;
	if (strcmp(command->part(0), "set") == 0)
		setting = true;
	else
		setting = false;

	// Enable/Disable...
	if (strcmp(command->part(tempInt), "enable") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Enable Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		enabled = true;
	}
	else if (strcmp(command->part(tempInt), "disable") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Disable Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		enabled = false;
	}

	// Buffer...
	else if (strcmp(command->part(tempInt), "buffer") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Buffer Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		buffer = atoi(command->part(tempInt));
	}

	// Chassis Alias...
	else if (strcmp(command->part(tempInt), "chassis-alias") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Chassis Alias Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		if (tempInt < command->parts)
			chassis.assign(strstr(line, command->part(tempInt)));
	}

	// Community...
	else if ((strcmp(command->part(tempInt), "community") == 0) && (strcmp(command->part(tempInt + 1), "index") != 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Community Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		if (tempInt + 1 < command->parts)
		{
			communityPointer = addSNMPCommunity();
			communityPointer->enabled = setting;
			
			if (strcmp(command->part(tempInt), "read-only") == 0)
				communityPointer->type = communityReadOnly;
			else if (strcmp(command->part(tempInt), "read-write") == 0)
				communityPointer->type = communityReadWrite;
			else if (strcmp(command->part(tempInt), "read-write-all") == 0)
				communityPointer->type = communityReadWriteAll;

			tempInt++;
			communityPointer->community.assign(command->part(tempInt));
		}
	}

	// Community-Ext...
	else if (strcmp(command->part(tempInt), "community-ext") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Community-Ext Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		communityPointer = getSNMPCommunity(command->part(tempInt));
		if (communityPointer == 0)
		{
			communityPointer = addSNMPCommunity();
			communityPointer->community.assign(command->part(tempInt));
		}
		tempInt++;
		if (strcmp(command->part(tempInt), "read-only") == 0)
			communityPointer->type = communityReadOnly;
		else if (strcmp(command->part(tempInt), "read-write") == 0)
			communityPointer->type = communityReadWrite;
		else if (strcmp(command->part(tempInt), "read-write-all") == 0)
			communityPointer->type = communityReadWriteAll;
		tempInt++;
		while (tempInt < command->parts)
		{
			if (strcmp(command->part(tempInt), "view") == 0)
			{
				tempInt++;
				communityPointer->view.assign(command->part(tempInt));
			}
			else if (strcmp(command->part(tempInt), "access") == 0)
			{
				tempInt++;
				communityPointer->filter.assign(command->part(tempInt));
			}
			tempInt++;
		}
	}

	// RMON Support...
	else if (strcmp(command->part(tempInt), "rmon") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP RMON Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		if (strcmp(command->part(tempInt), "enable") == 0)
			rmonSupport = true;
		else
			rmonSupport = false;
	}

	// RMON Memory Limit...
	else if (strcmp(command->part(tempInt), "rmonmemory") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP RMON Memory Limit Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		rmonMemory = atoi(command->part(tempInt));
	}

	// View...
	else if (strcasecmp(command->part(tempInt), "view") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP View Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		if (strcasecmp(command->part(tempInt), "-hex") == 0)
			tempInt++;
		if (strcasecmp(command->part(tempInt + 2), "mask") != 0)
		{
			if (strcasecmp(command->part(tempInt + 2), "included") == 0)
				addSNMPView(command->part(tempInt), command->part(tempInt + 1), true);
			else
				addSNMPView(command->part(tempInt), command->part(tempInt + 1), false);
		}
		else
		{
			if (strcasecmp(command->part(tempInt + 3), "included") == 0)
				addSNMPView(command->part(tempInt), command->part(tempInt + 1), true);
			else
				addSNMPView(command->part(tempInt), command->part(tempInt + 1), false);
		}
	}

	// Access List...
	else if (strcasecmp(command->part(tempInt), "access-list") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Access List Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		snmpHostPointer = addHost();
		snmpHostPointer->filter.assign(command->part(tempInt));
		tempInt++;
		snmpHostPointer->host.assign(command->part(tempInt));
		tempInt++;
		if (strcasecmp(command->part(tempInt), "ipmask") == 0)
		{
			tempInt++;
			snmpHostPointer->networkMask.assign(command->part(tempInt));
		}
	}

	// SNMP Informs...
	else if ((strcasecmp(command->part(tempInt), "inform") == 0) && (command->parts > 4))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Informs Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		trapHostPointer = addSNMPTrapHost();
		trapHostPointer->trap = false;
		trapHostPointer->host.assign(command->part(tempInt));
		tempInt++;
		trapHostPointer->community.assign(command->part(tempInt));
		tempInt++;
		while (tempInt < command->parts)
		{
			if (strcasecmp(command->part(tempInt), "port") == 0)
			{
				tempInt++;
				trapHostPointer->port = atoi(command->part(tempInt));
			}
			else if (strcasecmp(command->part(tempInt), "port") == 0)
			{
				tempInt++;
				if ((strcasecmp(command->part(tempInt), "2") == 0) || (strcasecmp(command->part(tempInt), "2c") == 0))
					trapHostPointer->version = 2;
				else
					trapHostPointer->version = 1;
			}
			tempInt++;
		}
	}

	// Trap hosts...
	else if ((strcasecmp(command->part(tempInt), "trap") == 0) && (strcasecmp(command->part(tempInt + 1), "enable") != 0) && (strcasecmp(command->part(tempInt + 1), "disable") != 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Trap Host Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		trapHostPointer = addSNMPTrapHost();
		trapHostPointer->trap = true;
		trapHostPointer->host.assign(command->part(tempInt));
		tempInt++;
		trapHostPointer->community.assign(command->part(tempInt));
		tempInt++;
		while (tempInt < command->parts)
		{
			if (strcasecmp(command->part(tempInt), "port") == 0)
			{
				tempInt++;
				trapHostPointer->port = atoi(command->part(tempInt));
			}
			tempInt++;
		}
	}

	// Traps...
	else if (strcasecmp(command->part(tempInt), "trap") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Trap Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		snmpTrapPointer = addSNMPTrap();
		tempInt++;
		if (strcasecmp(command->part(tempInt), "enable") == 0)
			snmpTrapPointer->include = true;
		else
			snmpTrapPointer->include = false;
		tempInt++;
		snmpTrapPointer->trap.assign(command->part(tempInt));
	}

	// Users...
	else if (strcasecmp(command->part(tempInt), "user") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP User Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		if (strcasecmp(command->part(tempInt), "-hex") == 0)
			tempInt++;
		snmpUserPointer = getSNMPUser(command->part(tempInt));
		if (snmpUserPointer == 0)
		{
			snmpUserPointer = addSNMPUser();
			snmpUserPointer->snmpv3 = snmpV3NoAuth;
			snmpUserPointer->priv = snmpV3PrivDES;
			snmpUserPointer->user.assign(command->part(tempInt));
		}
		tempInt++;
		while (tempInt < command->parts)
		{
			if (strcasecmp(command->part(tempInt), "authentication") == 0)
			{
				snmpUserPointer->snmpv3 = snmpV3Auth;
				tempInt++;
				if (strcasecmp(command->part(tempInt), "sha") == 0)
					snmpUserPointer->auth = snmpV3AuthSHA;
				else
					snmpUserPointer->auth = snmpV3AuthMD5;
				tempInt++;
				snmpUserPointer->authPassword.assign(command->part(tempInt));
			}

			else if (strcasecmp(command->part(tempInt), "privacy") == 0)
			{
				snmpUserPointer->snmpv3 = snmpV3Priv;
				tempInt++;
				if (strcasecmp(command->part(tempInt), "des") == 0)
				{
					snmpUserPointer->priv = snmpV3PrivDES;
					tempInt++;
				}
				else if (strcasecmp(command->part(tempInt), "3des") == 0)
				{
					snmpUserPointer->priv = snmpV3Priv3DES;
					tempInt++;
				}
				else if (strcasecmp(command->part(tempInt), "aes") == 0)
				{
					tempInt++;
					if (strcasecmp(command->part(tempInt), "128") == 0)
						snmpUserPointer->priv = snmpV3PrivAES128;
					else if (strcasecmp(command->part(tempInt), "192") == 0)
						snmpUserPointer->priv = snmpV3PrivAES192;
					else
						snmpUserPointer->priv = snmpV3PrivAES256;
					tempInt++;
					snmpUserPointer->privPassword.assign(command->part(tempInt));
				}
			}

			tempInt++;
		}
	}

	// Groups...
	else if (strcasecmp(command->part(tempInt), "group") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Group Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		if (strcasecmp(command->part(tempInt), "-hex") == 0)
			tempInt++;
		snmpGroupPointer = getSNMPGroup(command->part(tempInt));
		if (snmpGroupPointer == 0)
		{
			snmpGroupPointer = addSNMPGroup();
			snmpGroupPointer->group.assign(command->part(tempInt));
		}
		tempInt += 2;
		if (strcasecmp(command->part(tempInt), "-hex") == 0)
			tempInt++;
		snmpUserPointer = getSNMPUser(command->part(tempInt));
		if (snmpUserPointer == 0)
		{
			snmpUserPointer = addSNMPUser();
			snmpUserPointer->snmpv3 = snmpV3NoAuth;
			snmpUserPointer->priv = snmpV3PrivDES;
			snmpUserPointer->user.assign(command->part(tempInt));
		}
		snmpUserPointer->group.assign(snmpGroupPointer->group);
		tempInt += 2;
		if (strcasecmp(command->part(tempInt), "v1") == 0)
			snmpGroupPointer->version = 1;
		else if ((strcasecmp(command->part(tempInt), "v2c") == 0) || (strcasecmp(command->part(tempInt), "v2") == 0))
			snmpGroupPointer->version = 2;
		else
			snmpGroupPointer->version = 3;
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int CatalystSNMP::generateConfigSpecificReport(Device *device)
{
	// Variables...
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;
	int errorCode = 0;

	// Get Paragraph Pointer...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-SNMP-TABLE");

	// RMON Support
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*RMON*-ABBREV* Support"));
	if (rmonSupport == true)
	{
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
		device->addTableData(paragraphPointer->table, i18n("*ABBREV*RMON*-ABBREV* Memory Limit"));
		tempString.assign(device->intToString(rmonMemory));
		tempString.append(i18n(" percent"));
		device->addTableData(paragraphPointer->table, tempString.c_str());
	}
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));

	// Buffer...
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*UDP*-ABBREV* Receive Buffer Size"));
	tempString.assign(device->intToString(buffer));
	tempString.append(i18n(" packets"));
	device->addTableData(paragraphPointer->table, tempString.c_str());

	return errorCode;
}


int CatalystSNMP::processDefaults(Device *device)
{
	// Variables...
	snmpCommunity *communityPointer = 0;
	bool readFound = false;
	bool writeFound = false;
	bool writeAllFound = true;

	// SNMP v3 supported?
	if (device->general->versionMajor > 5)
		supportSNMP3 = true;
	else
		supportSNMP3Upgrade = true;

	// Add missing default SNMP communities...
	communityPointer = community;
	while (communityPointer != 0)
	{
		if (communityPointer->type == communityReadOnly)
			readFound = true;
		else if (communityPointer->type == communityReadWrite)
			writeFound = true;
		else
			writeAllFound = true;
		communityPointer = communityPointer->next;
	}
	if (readFound == false)
	{
		communityPointer = addSNMPCommunity();
		communityPointer->type = communityReadOnly;
		communityPointer->community.assign(defaultReadOnly);
	}
	if (writeFound == false)
	{
		communityPointer = addSNMPCommunity();
		communityPointer->type = communityReadWrite;
		communityPointer->community.assign(defaultReadWrite);
	}
	if (writeAllFound == false)
	{
		communityPointer = addSNMPCommunity();
		communityPointer->type = communityReadWriteAll;
		communityPointer->community.assign(defaultReadWriteAll);
	}

	// SNMP v1 & 2 Active?
	communityPointer = community;
	while ((communityPointer != 0) && (snmp12Enabled == false))
	{
		if (communityPointer->enabled == true)
			snmp12Enabled = true;
		communityPointer = communityPointer->next;
	}

	return 0;
}


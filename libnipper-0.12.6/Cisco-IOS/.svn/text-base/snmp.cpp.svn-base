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

#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "iosdevice.h"
#include "general.h"
#include "snmp.h"

using namespace std;


IOSSNMP::IOSSNMP()
{

	// Init SNMP support options...
	deviceSNMPSupportText = i18n("*DEVICETYPE* support *ABBREV*SNMP*-ABBREV* from *ABBREV*IOS*-ABBREV* version 10 and *ABBREV*SNMP*-ABBREV* version 3 from *ABBREV*IOS*-ABBREV* version 12.");		// Intro Config section device specific text.
	supportSNMP3 = false;					// Does this device support SNMPv3?
	supportSNMP3Upgrade = false;			// Do you have to upgrade to get support for SNMPv3
	supportSNMP3UpgText = i18n("*ABBREV*SNMP*-ABBREV* version 3 is supported from *ABBREV*IOS*-ABBREV* version 12.");			// SNMP 3 is supported from OS version ...
	disableSNMPCmdText = i18n("*ABBREV*SNMP*-ABBREV* can be disabled with the following command:*CODE**COMMAND*no snmp-server*-COMMAND**-CODE*");			// The text and command(s) to disable SNMP support
	configSNMPCommunityText = i18n("A *ABBREV*SNMP*-ABBREV* community string can be configured with the following command:*CODE**COMMAND*snmp-server community *CMDUSER*community-string*-CMDUSER* *CMDOPTION*view *CMDUSER*view-name*-CMDUSER**-CMDOPTION* *CMDOPTION*ro *CMDOR* rw*-CMDOPTION* *CMDOPTION**CMDUSER*acl-number*-CMDUSER**-CMDOPTION**-COMMAND**-CODE*");		// The text and command(s) to configure a community string
	configSNMP3Text = i18n("To configure *ABBREV*SNMP*-ABBREV* version 3, you configure a group and then add users to the group. The following commands can be used to create a group and add a user to it:*CODE**COMMAND*snmp-server group *CMDUSER*group-name*-CMDUSER* v3 *CMDREQUIRE*noauth *CMDOR* auth *CMDOR* priv*-CMDREQUIRE* *CMDOPTION*read *CMDUSER*read-view*-CMDUSER**-CMDOPTION* *CMDOPTION*write *CMDUSER*write-view*-CMDUSER**-CMDOPTION* *CMDOPTION*notify *CMDUSER*notify-view*-CMDUSER**-CMDOPTION* *CMDOPTION*access *CMDUSER*acl*-CMDUSER**-CMDOPTION**-COMMAND**COMMAND*snmp-server user *CMDUSER*username*-CMDUSER* *CMDUSER*group-name*-CMDUSER* v3 *CMDOPTION*auth *CMDREQUIRE*md5 *CMDOR* sha*-CMDREQUIRE* *CMDUSER*auth-password*-CMDUSER**-CMDOPTION* *CMDOPTION*access *CMDUSER*acl*-CMDUSER**-CMDOPTION**-COMMAND**-CODE*");				// The text and command(s) to configure SNMP version 3
	configSNMPViewText = i18n("A *ABBREV*SNMP*-ABBREV* view can be configured and then assigned to a community string with the following commands:*CODE**COMMAND*snmp-server view *CMDUSER*view-name*-CMDUSER* *CMDUSER*oid*-CMDUSER* *CMDREQUIRE*included *CMDOR* excluded*-CMDREQUIRE**-COMMAND**COMMAND*snmp-server community *CMDUSER*community-string*-CMDUSER* *CMDOPTION*view *CMDUSER*view-name*-CMDUSER**-CMDOPTION* *CMDOPTION*ro *CMDOR* rw*-CMDOPTION* *CMDOPTION**CMDUSER*acl-number*-CMDUSER**-CMDOPTION**-COMMAND**-CODE*");			// The text and command(s) to configure SNMP views
	configSNMPTrapsText = i18n("A *ABBREV*SNMP*-ABBREV* trap can be configured with the following command:*CODE*snmp-server host *CMDUSER*ip-address*-CMDUSER* traps *CMDOPTION*version *CMDREQUIRE*1 *CMDOR* 2c *CMDOR* 3 *CMDOPTION*noauth *CMDOR* auth *CMDOR* priv*-CMDOPTION**-CMDREQUIRE**-CMDOPTION* *CMDUSER*community-string*-CMDUSER**-CODE*");			// The text and command(s) to configure SNMP traps
	configSNMPInformsText = i18n("A *ABBREV*SNMP*-ABBREV* inform can be configured with the following command:*CODE*snmp-server host *CMDUSER*ip-address*-CMDUSER* informs *CMDOPTION*version *CMDREQUIRE*1 *CMDOR* 2c *CMDOR* 3 *CMDOPTION*noauth *CMDOR* auth *CMDOR* priv*-CMDOPTION**-CMDREQUIRE**-CMDOPTION* *CMDUSER*community-string*-CMDUSER**-CODE*");		// The text and command(s) to configure SNMP informs
	configSNMPReadOnlyText = i18n("Read only *ABBREV*SNMP*-ABBREV* community strings can be configured with the following command:*CODE**COMMAND*snmp-server community *CMDUSER*community-string*-CMDUSER* *CMDOPTION*view *CMDUSER*view-name*-CMDUSER**-CMDOPTION* ro *CMDOPTION**CMDUSER*acl-number*-CMDUSER**-CMDOPTION**-COMMAND**-CODE*");		// The text and command(s) to configure SNMP read only access
	configSNMPFilterText = i18n("The following commands can be used to configure an *ABBREV*ACL*-ABBREV* and assign it to a community string:*CODE**COMMAND*access-list *CMDUSER*acl-number*-CMDUSER* permit *CMDUSER*ip-address*-CMDUSER* *CMDUSER*network-mask*-CMDUSER* log*-COMMAND**COMMAND*access-list *CMDUSER*acl-number*-CMDUSER* deny any log*-COMMAND**COMMAND*snmp-server community *CMDUSER*community-string*-CMDUSER* *CMDOPTION*view *CMDUSER*view-name*-CMDUSER**-CMDOPTION* *CMDOPTION*ro *CMDOR* rw*-CMDOPTION* *CMDOPTION**CMDUSER*acl-number*-CMDUSER**-CMDOPTION**-COMMAND**-CODE*");		// The text and command(s) to configure SNMP filtering

	snmpFilterText = i18n("*ABBREV*ACL*-ABBREV*");	// The device specific description of a filter (i.e. Cisco called them ACL)
	snmpFilterIPv6Text = i18n("*ABBREV*IPv6*-ABBREV* *ABBREV*ACL*-ABBREV*");

	// Community Options...
	communityView = true;				// SNMP view for the community
	communityFilter = true;				// SNMP Network Filtering
	communityIPv6Filter = true;			// SNMP IPv6 Network Filtering
	communitySpecificFilters = false;	// If the device uses an SNMP specific list. If false, it is std device filters
	communityRequiresHosts = false;		// If the SNMP community will not work without a list of those who can access it

	// View Options...
	viewSeperated = true;				// Separate the views into different tables
	viewExcludes = true;				// Show the Include/Exclude View Table column

	// SNMP Trap/Inform Host Options...
	trapsOnly = false;					// Only Traps are supported
	trapsSNMPv3 = true;					// SNMP v3 support for traps
	trapsShowPort = true;				// Show Trap Host Port in Table
	trapsInterface = true;				// Show Interface in Table
	trapsInterfaceText = i18n("*ABBREV*VRF*-ABBREV*");		// The Traps/Informs Host Table Interface Column Title
	trapsShowNotifications = true;		// Show Notifications in the Table
	trapsShowEventLevel = false;		// Show Notification Event Level in the Table

	// Traps/Informs Options...
	trapsShowExcluded = true;			// Show excluded traps
	trapsShowOptions = true;			// Show trap options

	// SNMP User Options...
	showUserRemote = true;				// Show the remote host/port setting
	showUserPriv = false;				// Show the privacy settings
	showUserFilter = true;				// Show the Filter column in the table
	showUserIPv6Filter = true;			// Show the IPv6 Filter column in the table
	userFilterText = i18n("*ABBREV*ACL*-ABBREV*");	// The Text for the Filter table column title
	userIPv6FilterText = i18n("*ABBREV*IPv6*-ABBREV* *ABBREV*ACL*-ABBREV*");	// The Text for the IPv6 Filter table column title

	// SNMP Group Options...
	snmpGroupShowType = true;			// Enable/Disable SNMPv3 type in table
	snmpGroupReadView = true;			// Enable/Disable Read Views
	snmpGroupWriteView = true;			// Enable/Disable Write Views
	snmpGroupNotifyView = true;			// Enable/Disable Notify Views
	snmpGroupFilter = true;				// Enable/Disable Filter support
	snmpGroupIPv6Filter = true;			// Enable/Disable IPv6 Filter support
	groupFilterText = i18n("*ABBREV*ACL*-ABBREV*");	// The Text for the Filter table column title
	groupIPv6FilterText = i18n("*ABBREV*IPv6*-ABBREV* *ABBREV*ACL*-ABBREV*");		// The Text for the IPv6 Filter table column title

	// Device specific stuff...
	managerEnabled = false;
	managerTimeout = 600;
	packetSize = 1500;
	trapQueueLength = 10;
	systemShutdown = false;
	trapTimeout = 30;
}


int IOSSNMP::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	snmpCommunity *communityPointer = 0;
	snmpTrapHost *trapHostPointer = 0;
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

	// Server...
	if (command->parts == tempInt + 1)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		enabled = setting;
		snmp12Enabled = setting;
		snmp3Enabled = setting;
	}

	// Location...
	else if (strcmp(command->part(tempInt), "location") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Location Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		location.assign(line + 9 + string(line).find("location"));
	}

	// Contact...
	else if (strcmp(command->part(tempInt), "contact") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Contact Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		contact.assign(line + 8 + string(line).find("contact"));
	}

	// TFTP Server List...
	else if (strcmp(command->part(tempInt), "tftp-server-list") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP TFTP Server List Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tftpServerList.assign(command->part(tempInt + 1));
	}

	// Chassis ID...
	else if (strcmp(command->part(tempInt), "chassis-id") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Chassis ID Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		chassis.assign(command->part(tempInt + 1));
	}

	// SNMP Manager Timeout...
	else if ((strcmp(command->part(tempInt), "manager") == 0) && (strcmp(command->part(tempInt + 1), "session-timeout") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Manager Session Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 2;
		managerTimeout = atoi(command->part(tempInt));
	}

	// SNMP Manager...
	else if (strcmp(command->part(tempInt), "manager") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Manager Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		managerEnabled = setting;
	}

	// SNMP Packet Size...
	else if (strcmp(command->part(tempInt), "packetsize") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Packet Size Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		packetSize = atoi(command->part(tempInt));
	}

	// SNMP Trap Queue Length...
	else if (strcmp(command->part(tempInt), "queue-length") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Trap Queue Length Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		trapQueueLength = atoi(command->part(tempInt));
	}

	// SNMP Trap Tiemout...
	else if (strcmp(command->part(tempInt), "trap-timeout") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Trap Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		trapTimeout = atoi(command->part(tempInt));
	}

	// SNMP System Shutdown...
	else if (strcmp(command->part(tempInt), "system-shutdown") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP System Shutdown Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		systemShutdown = setting;
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
		snmp12Enabled = setting;

		// Get options...
		tempInt++;
		while (tempInt < command->parts)
		{

			// RO
			if (strcasecmp(command->part(tempInt), "ro") == 0)
				communityPointer->type = communityReadOnly;

			// RW
			else if (strcasecmp(command->part(tempInt), "rw") == 0)
				communityPointer->type = communityReadWrite;

			// View
			else if (strcasecmp(command->part(tempInt), "view") == 0)
			{
				tempInt++;
				communityPointer->view.assign(command->part(tempInt));
			}

			// IP v6 Filter
			else if (strcasecmp(command->part(tempInt), "ipv6") == 0)
			{
				tempInt++;
				communityPointer->ipv6Filter.assign(command->part(tempInt));
			}

			// Filter
			else if (tempInt == command->parts - 1)
				communityPointer->filter.assign(command->part(tempInt));

			tempInt++;
		}
	}

	// SNMP View...
	else if (strcmp(command->part(tempInt), "view") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP View Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		if (strcmp(command->part(tempInt + 2), "excluded") == 0)
			addSNMPView(command->part(tempInt), command->part(tempInt + 1), false);
		else
			addSNMPView(command->part(tempInt), command->part(tempInt + 1), true);
	}

	// SNMP Host...
	else if (strcmp(command->part(tempInt), "host") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Host Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		trapHostPointer = addSNMPTrapHost();
		trapHostPointer->host.assign(command->part(tempInt));
		trapHostPointer->version = 1;
		trapHostPointer->snmpv3 = snmpV3NoAuth;
		trapHostPointer->port = 162;
		trapHostPointer->trap = true;
		tempInt++;

		// VRF...
		if (strcmp(command->part(tempInt), "vrf") == 0)
		{
			tempInt++;
			trapHostPointer->interface.assign(command->part(tempInt));
			tempInt++;
		}

		// Traps...
		if (strcmp(command->part(tempInt), "traps") == 0)
		{
			trapHostPointer->trap = true;
			tempInt++;
		}

		// Informs...
		if (strcmp(command->part(tempInt), "informs") == 0)
		{
			trapHostPointer->trap = false;
			tempInt++;
		}

		// Version...
		if (strcmp(command->part(tempInt), "version") == 0)
		{
			tempInt++;
			if (strcmp(command->part(tempInt), "1") == 0)
			{
				tempInt++;
				trapHostPointer->version = 1;
			}
			else if (strcmp(command->part(tempInt), "2c") == 0)
			{
				trapHostPointer->version = 2;
				tempInt++;
			}
			else if (strcmp(command->part(tempInt), "3") == 0)
			{
				trapHostPointer->version = 3;
				tempInt++;
				if (strcmp(command->part(tempInt), "auth") == 0)
				{
					trapHostPointer->snmpv3 = snmpV3Auth;
					tempInt++;
				}
				else if (strcmp(command->part(tempInt), "noauth") == 0)
				{
					trapHostPointer->snmpv3 = snmpV3NoAuth;
					tempInt++;
				}
				else if (strcmp(command->part(tempInt), "priv") == 0)
				{
					trapHostPointer->snmpv3 = snmpV3Priv;
					tempInt++;
				}
			}
		}

		// Community
		trapHostPointer->community.assign(command->part(tempInt));
		tempInt++;

		// UDP Port...
		if (strcmp(command->part(tempInt), "udp-port") == 0)
		{
			trapHostPointer->port = atoi(command->part(tempInt));
			tempInt++;
		}

		// Notifications...
		while (tempInt < command->parts)
		{

			// VRRP...
			if (strcmp(command->part(tempInt), "vrrp") == 0)
			{ }

			// Notification...
			if (!trapHostPointer->notification.empty())
			{
				trapHostPointer->notification.append(" ");
				trapHostPointer->notification.append(command->part(tempInt));
			}
			else
				trapHostPointer->notification.assign(command->part(tempInt));

			tempInt++;
		}

		// If no notifications were configured...
		if (trapHostPointer->notification.empty())
			trapHostPointer->notification.assign(i18n("All"));
	}

	// SNMP Traps...
	else if ((strcmp(command->part(tempInt), "enable") == 0) && (strcmp(command->part(tempInt + 1), "traps") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Traps Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 2;
		snmpTrapPointer = addSNMPTrap();
		snmpTrapPointer->include = setting;

		// All traps...
		if ((strcmp(command->part(tempInt), "vrrp") == 0) || (command->parts == tempInt))
			snmpTrapPointer->trap.assign("All");

		// Traps + options...
		else if (command->parts > tempInt + 1)
		{
			snmpTrapPointer->trap.assign(command->part(tempInt));
			snmpTrapPointer->options.assign(line + 1 + string(line).find(command->part(tempInt)) + strlen(command->part(tempInt)));
		}

		// Trap only...
		else
			snmpTrapPointer->trap.assign(command->part(tempInt));
	}
	else if (strcmp(command->part(tempInt), "trap") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Traps Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		snmpTrapPointer = addSNMPTrap();
		snmpTrapPointer->include = setting;
		snmpTrapPointer->trap.assign(command->part(tempInt));
		if (command->parts > tempInt + 1)
			snmpTrapPointer->options.assign(line + 1 + string(line).find(command->part(tempInt)) + strlen(command->part(tempInt)));
	}
	else if (strcmp(command->part(tempInt), "trap-authentication") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Traps Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		snmpTrapPointer = addSNMPTrap();
		snmpTrapPointer->include = setting;
		snmpTrapPointer->trap.assign("Authentication");
	}

	// SNMP Trap Source Interface...
	else if (strcmp(command->part(tempInt), "trap-source") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Trap Source Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		trapSource.assign(command->part(tempInt));
	}

	// snmp group?
	else if (strcmp(command->part(tempInt), "group") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP Group Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		snmp3Enabled = setting;
		snmpGroupPointer = addSNMPGroup();
		snmpGroupPointer->group.assign(command->part(tempInt));
		tempInt++;

		// SNMP version...
		if (strcmp(command->part(tempInt), "v1") == 0)
			snmpGroupPointer->version = 1;
		else if (strcmp(command->part(tempInt), "v2c") == 0)
			snmpGroupPointer->version = 2;
		else if (strcmp(command->part(tempInt), "v3") == 0)
		{
			snmpGroupPointer->version = 3;
			tempInt++;
			if (strcmp(command->part(tempInt), "noauth") == 0)
				snmpGroupPointer->snmpv3 = snmpV3NoAuth;
			else if (strcmp(command->part(tempInt), "auth") == 0)
				snmpGroupPointer->snmpv3 = snmpV3Auth;
			else if (strcmp(command->part(tempInt), "priv") == 0)
				snmpGroupPointer->snmpv3 = snmpV3Priv;
		}
		tempInt++;

		// Options...
		while (tempInt < command->parts)
		{

			// Read view...
			if (strcmp(command->part(tempInt), "read") == 0)
			{
				tempInt++;
				snmpGroupPointer->readView.assign(command->part(tempInt));
			}

			// Write View...
			else if (strcmp(command->part(tempInt), "write") == 0)
			{
				tempInt++;
				snmpGroupPointer->writeView.assign(command->part(tempInt));
			}

			// Notify View...
			else if (strcmp(command->part(tempInt), "notify") == 0)
			{
				tempInt++;
				snmpGroupPointer->notifyView.assign(command->part(tempInt));
			}

			// Filtering...
			else if (strcmp(command->part(tempInt), "access") == 0)
			{
				tempInt++;
				if (strcmp(command->part(tempInt), "ipv6") == 0)
				{
					tempInt++;
					snmpGroupPointer->ipv6Filter.assign(command->part(tempInt));
					tempInt++;
				}
				snmpGroupPointer->filter.assign(command->part(tempInt));
			}

			tempInt++;
		}
	}

	// snmp user?
	else if (strcmp(command->part(tempInt), "user") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSNMP User Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		snmp3Enabled = setting;
		tempInt++;
		snmpUserPointer = addSNMPUser();
		snmpUserPointer->user.assign(command->part(tempInt));
		tempInt++;

		// Group...
		snmpUserPointer->group.assign(command->part(tempInt));
		tempInt++;

		// Remote...
		if (strcmp(command->part(tempInt), "remote") == 0)
		{
			tempInt++;
			snmpUserPointer->host.assign(command->part(tempInt));
			tempInt++;
			if (strcmp(command->part(tempInt), "udp-port") == 0)
			{
				tempInt++;
				snmpUserPointer->port = atoi(command->part(tempInt));
				tempInt++;
			}
		}

		// SNMP version...
		if (strcmp(command->part(tempInt), "v1") == 0)
		{
			snmpUserPointer->version = 1;
			tempInt++;
		}
		else if (strcmp(command->part(tempInt), "v2c") == 0)
		{
			snmpUserPointer->version = 2;
			tempInt++;
		}
		else if (strcmp(command->part(tempInt), "v3") == 0)
		{
			snmpUserPointer->version = 3;
			snmpUserPointer->snmpv3 = snmpV3NoAuth;
			tempInt++;

			// Encrypted...
			if (strcmp(command->part(tempInt), "encrypted") == 0)
				tempInt++;

			// Auth...
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
				tempInt++;
			}
		}

		// Access...
		if (strcmp(command->part(tempInt), "access") == 0)
		{
			tempInt++;
			if (strcmp(command->part(tempInt), "ipv6") == 0)
			{
				tempInt++;
				snmpUserPointer->ipv6Filter.assign(command->part(tempInt));
				tempInt++;
			}
			snmpUserPointer->filter.assign(command->part(tempInt));
		}
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int IOSSNMP::processDefaults(Device *device)
{
	// Variables...
	snmpTrapHost *trapHostPointer = 0;
	snmpCommunity *communityPointer = 0;

	// Enable SNMP Service...
	if ((enabled == false) && (snmp12Enabled == true))
	{
		communityPointer = community;
		while ((communityPointer != 0) && (enabled == false))
		{
			enabled = communityPointer->enabled;
			communityPointer = communityPointer->next;
		}
	}
	if ((enabled == false) && (snmp3Enabled == true))
		enabled = true;

	// SNMP v3 supported?
	if (device->general->versionMajor > 11)
		supportSNMP3 = true;
	else
		supportSNMP3Upgrade = true;

	// Check IOS version for Trap Hosts...
	// Plus add default communities if they don't already exist (default on IOS 12.0(3)+)...
	if (device->general->versionMajor < 12)
		trapsSNMPv3 = false;
	else if ((device->general->versionMajor == 12) && (device->general->versionMinor == 0) && (device->general->versionRevision < 3))
		trapsSNMPv3 = false;
	else
	{

		trapHostPointer = trapHost;
		while (trapHostPointer != 0)
		{
			communityPointer = getSNMPCommunity(trapHostPointer->community.c_str());
			if (communityPointer == 0)
			{
				communityPointer = addSNMPCommunity();
				communityPointer->community.assign(trapHostPointer->community);
				communityPointer->type = communityReadOnly;
			}
			trapHostPointer = trapHostPointer->next;
		}
	}

	return 0;
}


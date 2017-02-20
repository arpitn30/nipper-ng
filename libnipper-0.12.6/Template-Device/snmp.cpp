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


TemplateSNMP::TemplateSNMP()
{
	// Init SNMP support options...
	deviceSNMPSupportText = i18n("");		// Intro Config section device specific text.
	supportSNMP3 = false;					// Does this device support SNMPv3?
	supportSNMP3Upgrade = false;			// Do you have to upgrade to get support for SNMPv3
	supportSNMP3UpgText = i18n("");			// SNMP 3 is supported from OS version ...
	disableSNMPCmdText = i18n("");			// The text and command(s) to disable SNMP support
	configSNMPCommunityText = i18n("");		// The text and command(s) to configure a community string
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

	snmpFilterText = i18n("Filter");		// The device specific description of a filter (i.e. Cisco called them ACL)
	snmpFilterIPv6Text = i18n("*ABBREV*IPv6*-ABBREV* Filter");

	// Community Options...
	communityView = false;					// SNMP view for the community
	communityFilter = false;				// SNMP Network Filtering
	communityIPv6Filter = false;			// SNMP IPv6 Network Filtering
	communitySpecificFilters = false;		// If the device uses an SNMP specific list. If false, it is std device filters
	communityRequiresHosts = false;		// If the SNMP community will not work without a list of those who can access it

	// Default communities...
	defaultReadOnly = "";					// Default read only community
	defaultReadWrite = "";					// Default read/write community
	defaultReadWriteAll = "";				// Default read/write all community

	// View support options...
	viewSeperated = false;					// Separate the views into different tables
	viewExcludes = false;					// Show the Include/Exclude View Table column
	viewMIBText = i18n("*ABBREV*MIB*-ABBREV*");	// What the MIB column title in the table should be called

	// SNMP Trap/Inform Host Options...
	trapsOnly = true;						// Only Traps are supported
	trapsSNMPv3 = false;					// SNMP v3 support for traps
	trapsShowPort = false;					// Show Trap Host Port in Table
	trapsInterface = false;				// Show Interface in Table
	trapsInterfaceText = i18n("Interface");		// The Traps/Informs Host Table Interface Column Title
	trapsShowNotifications = false;		// Show Notifications in the Table
	trapsShowEventLevel = false;			// Show Notification Event Level in the Table

	// Traps/Informs Options...
	trapsShowExcluded = false;				// Show excluded traps
	trapsShowOptions = false;				// Show trap options

	// Host Options...
	hostShowInterface = false;				// Show the Interface in the Table
	hostShowCommunity = false;				// Show the Community in the Table
	hostShowFilterID = false;				// Show a filter ID if used
	hostFilterText = i18n("Filter");		// The Table column title for the filter text

	// SNMP User Options...
	showUserRemote = false;				// Show the remote host/port setting
	showUserPriv = false;					// Show the privacy settings
	showUserFilter = false;				// Show the Filter column in the table
	showUserIPv6Filter = false;			// Show the IPv6 Filter column in the table
	userFilterText = i18n("Filter");		// The Text for the Filter table column title
	userIPv6FilterText = i18n("*ABBREV*IPv6*-ABBREV* Filter");	// The Text for the IPv6 Filter table column title

	// SNMP Group Options...
	snmpGroupShowType = false;				// Enable/Disable SNMPv3 type in table
	snmpGroupReadView = false;				// Enable/Disable Read Views
	snmpGroupWriteView = false;			// Enable/Disable Write Views
	snmpGroupNotifyView = false;			// Enable/Disable Notify Views
	snmpGroupFilter = false;				// Enable/Disable Filter support
	snmpGroupIPv6Filter = false;			// Enable/Disable IPv6 Filter support
	groupFilterText = i18n("Filter");		// The Text for the Filter table column title
	groupIPv6FilterText = i18n("*ABBREV*IPv6*-ABBREV* Filter");	// The Text for the IPv6 Filter table column title
}


int TemplateSNMP::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// This is where the SNMP processing code goes...

	/* // Variables...
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

	// Community processing...
	if (strcmp(command->part(tempInt), "community") == 0)
	{
	}

	// All others...
	else
		device->lineNotProcessed(line);*/

	return 0;
}


int TemplateSNMP::generateConfigSpecificReport(Device *device)
{
	// Device specific code for the config report goes here

	return 0;
}


int TemplateSNMP::processDefaults()
{
	// Any default setting post processing code goes here...

	return 0;
}


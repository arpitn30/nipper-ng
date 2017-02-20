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

// Includes...
#include <sstream>
#include <string>
#include <cstring>


#include "../../globaldefs.h"
#include "../device.h"
#include "snmp.h"


SNMP::SNMP()
{
	// Init Pointers...
	community = 0;							// Community
	view = 0;								// View
	trapHost = 0;							// Trap/Inform Hosts
	snmpHost = 0;							// SNMP Host
	traps = 0;								// Traps
	snmpUser = 0;							// Users
	snmpGroup = 0;							// SNMP Group

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


SNMP::~SNMP()
{
	// Variables...
	snmpCommunity *communityPointer = 0;
	snmpView *viewPointer = 0;
	snmpMIB *mibPointer = 0;
	snmpTrapHost *trapHostPointer = 0;
	snmpHostStruct *snmpHostPointer = 0;
	snmpTrap *snmpTrapPointer = 0;
	snmpUserStruct *snmpUserPointer = 0;
	snmpGroupStruct *snmpGroupPointer = 0;

	// Delete group structures...
	while (snmpGroup != 0)
	{
		snmpGroupPointer = snmpGroup->next;
		delete (snmpGroup);
		snmpGroup = snmpGroupPointer;
	}

	// Delete user structures...
	while (snmpUser != 0)
	{
		snmpUserPointer = snmpUser->next;
		delete (snmpUser);
		snmpUser = snmpUserPointer;
	}

	// Delete community structures...
	while (community != 0)
	{
		communityPointer = community->next;
		delete (community);
		community = communityPointer;
	}

	// Delete trap/inform host structures...
	while (trapHost != 0)
	{
		trapHostPointer = trapHost->next;
		delete (trapHost);
		trapHost = trapHostPointer;
	}

	// Delete trap/inform structures...
	while (traps != 0)
	{
		snmpTrapPointer = traps->next;
		delete (traps);
		traps = snmpTrapPointer;
	}

	// Delete SNMP Hosts...
	while (snmpHost != 0)
	{
		snmpHostPointer = snmpHost->next;
		delete (snmpHost);
		snmpHost = snmpHostPointer;
	}

	// Delete View/MIB structures...
	while (view != 0)
	{
		while (view->mib != 0)
		{
			mibPointer = view->mib->next;
			delete (view->mib);
			view->mib = mibPointer;
		}
		viewPointer = view->next;
		delete (view);
		view = viewPointer;
	}
}


int SNMP::generateConfigReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s SNMP Settings\n", device->config->COL_BLUE, device->config->COL_RESET);

	// Add service to the services list...
	configReportPointer = device->getConfigSection("CONFIG-SERVICES");
	paragraphPointer = device->getTableParagraphPointer("CONFIG-SERVICES-TABLE");
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*SNMP*-ABBREV* Service"));
	if (enabled == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));

	// Create Config Report Section...
	configReportPointer = device->getConfigSection("CONFIG-SNMP");
	configReportPointer->title = i18n("*ABBREV*SNMP*-ABBREV* Settings");
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraph.assign(i18n("*ABBREV*SNMP*-ABBREV* is used to assist network administrators in monitoring and managing a wide variety of network devices. There are three main versions of *ABBREV*SNMP*-ABBREV* in use. Versions 1 and 2 of *ABBREV*SNMP*-ABBREV* are both secured with a community string and authenticate and transmit network packets without any form of encryption. *ABBREV*SNMP*-ABBREV* version 3 provides several levels of authentication and encryption. The most basic level provides a similar protection to that of the earlier protocol versions. However, *ABBREV*SNMP*-ABBREV* version 3 can be configured to provide encrypted authentication (auth) and secured further with support for encrypted data communications (priv)."));
	paragraphPointer = device->addParagraph(configReportPointer);
	if (strlen(deviceSNMPSupportText) > 0)
		paragraphPointer->paragraph.assign(deviceSNMPSupportText);
	paragraphPointer->paragraph.append(i18n("This section describes the *DEVICENAME* *ABBREV*SNMP*-ABBREV* configuration settings."));

	// Create table...
	errorCode = device->addTable(paragraphPointer, "CONFIG-SNMP-TABLE");
	if (errorCode != 0)
		return errorCode;
	paragraphPointer->table->title = i18n("*ABBREV*SNMP*-ABBREV* settings");
	device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Setting"), false);

	// SNMP Server Enabled...
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*SNMP*-ABBREV* Service"));
	if (enabled == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));

	device->addTableData(paragraphPointer->table, i18n("*ABBREV*SNMP*-ABBREV* Service *ABBREV*UDP*-ABBREV* Port"));
	tempString.assign(device->intToString(listenPort));
	device->addTableData(paragraphPointer->table, tempString.c_str());

	// Add Name...
	if (!name.empty())
	{
		device->addTableData(paragraphPointer->table, i18n("Device Name"));
		device->addTableData(paragraphPointer->table, name.c_str());
	}

	// Add Chassis...
	if (!chassis.empty())
	{
		device->addTableData(paragraphPointer->table, i18n("Chassis"));
		device->addTableData(paragraphPointer->table, chassis.c_str());
	}

	// Add Contact...
	if (!contact.empty())
	{
		device->addTableData(paragraphPointer->table, i18n("Contact"));
		device->addTableData(paragraphPointer->table, contact.c_str());
	}

	// Add Location...
	if (!location.empty())
	{
		device->addTableData(paragraphPointer->table, i18n("Location"));
		device->addTableData(paragraphPointer->table, location.c_str());
	}

	// Generate different SNMP config sections...
	if (community != 0)
		generateCommunityConfigReport(device);
	if (snmpHost != 0)
		generateHostConfigReport(device);
	if ((trapHost != 0) || (traps != 0))
		generateTrapHostConfigReport(device);
	if ((snmpUser != 0) || (snmpGroup != 0))
	{
		generateGroupConfigReport(device);
		generateUserConfigReport(device);
	}
	if (view != 0)
		generateViewConfigReport(device);

	errorCode = generateConfigSpecificReport(device);

	return errorCode;
}


int SNMP::generateSecurityReport(Device *device)
{
	// Variables...
	snmpCommunity *snmpCommunityPointer = 0;
	snmpHostStruct *snmpHostPointer = 0;
	snmpTrapHost *snmpTrapPointer = 0;
	string tempString;
	bool found = false;
	int errorCode = 0;

	// Counter Variables...
	int defaultCommunityCount = 0;				// Community/password counters on rack up 1 of each, so if
	int dictionaryCommunityCount = 0;			// a default password is highlighted, it is not reported as a
	int weakCommunityCount = 0;				// dictionary password or a weak one, even though it is likely.
	int defaultWithWriteCount = 0;
	int defaultWithWriteAllCount = 0;
	int dictionaryWithWriteCount = 0;
	int dictionaryWithWriteAllCount = 0;
	int weakWithWriteCount = 0;
	int weakWithWriteAllCount = 0;
	int writeAccessCount = 0;
	int noViewCount = 0;
	int noFilteringCount = 0;
	int noNMSFilteringCount = 0;
	int dictionaryTrapCount = 0;
	int dictionaryInformCount = 0;
	int weakTrapCount = 0;
	int weakInformCount = 0;
	int accessFromAnySource = 0;
	int accessFromNetSource = 0;
	bool clearTextSNMP = false;
	bool clearTextWriteAccess = false;
	bool clearTextView = false;
	bool clearTextFilter = false;


	// ---------------------------------------------------------------
	// Security Checks...
	// ---------------------------------------------------------------

	if ((enabled == true) && (snmp12Enabled == true))
	{

		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s SNMP Community Checks\n", device->config->COL_BLUE, device->config->COL_RESET);
	
		// Check Community...
		snmpCommunityPointer = community;
		while (snmpCommunityPointer != 0)
		{
			found = false;
	
			// Check for default community...
			if ((snmpCommunityPointer->enabled == true) && (((communityRequiresHosts == true) && (hostCommunityExists(snmpCommunityPointer->community.c_str()) == true)) || (communityRequiresHosts == false)))
			{
				clearTextSNMP = true;
				if ((strlen(defaultReadOnly) > 0) || (strlen(defaultReadWrite) > 0) || (strlen(defaultReadWriteAll) > 0))
				{
					switch (snmpCommunityPointer->type)
					{
						case communityReadOnly:
							if (strcasecmp(snmpCommunityPointer->community.c_str(), defaultReadOnly) == 0)
							{
								found = true;
								defaultCommunityCount++;
								snmpCommunityPointer->communityDefault = true;
							}
							break;
						case communityReadWrite:
							if (strcasecmp(snmpCommunityPointer->community.c_str(), defaultReadWrite) == 0)
							{
								found = true;
								defaultCommunityCount++;
								defaultWithWriteCount++;
								snmpCommunityPointer->communityDefault = true;
							}
							break;
						default:
							if (strcasecmp(snmpCommunityPointer->community.c_str(), defaultReadWriteAll) == 0)
							{
								found = true;
								defaultCommunityCount++;
								defaultWithWriteAllCount++;
								snmpCommunityPointer->communityDefault = true;
							}
							break;
					}
				}

				// Check for dictionary based...
				if (found == false)
				{
					snmpCommunityPointer->communityInDict = device->isDictionaryPassword(snmpCommunityPointer->community.c_str());
					if (snmpCommunityPointer->communityInDict == true)
					{
						found = true;
						dictionaryCommunityCount++;
						if (snmpCommunityPointer->type == communityReadWrite)
							dictionaryWithWriteCount++;
						else if (snmpCommunityPointer->type == communityReadWriteAll)
							dictionaryWithWriteAllCount++;
					}
				}
	
				// Check for weak community...
				if (found == false)
				{
					snmpCommunityPointer->communityWeak = device->isPasswordWeak(snmpCommunityPointer->community.c_str());
					if (snmpCommunityPointer->communityWeak != Device::passwordPassed)
					{
						found = true;
						weakCommunityCount++;
						if (snmpCommunityPointer->type == communityReadWrite)
							weakWithWriteCount++;
						else if (snmpCommunityPointer->type == communityReadWriteAll)
							weakWithWriteAllCount++;
					}
				}
	
				// Write Check...
				if (snmpCommunityPointer->type != communityReadOnly)
					writeAccessCount++;
	
				// Community View Check...
				if ((communityView == true) && (snmpCommunityPointer->view.empty()))
					noViewCount++;
	
				// Community Filtering Check...
				if ((communityFilter == true) && (snmpCommunityPointer->filter.empty()))
					noFilteringCount++;
			}
	
			snmpCommunityPointer = snmpCommunityPointer->next;
		}
	
		// Check NMS hosts...
		if ((communityRequiresHosts == false) && (hostShowCommunity == true))
		{
			snmpHostPointer = snmpHost;
			while (snmpHostPointer != 0)
			{
				clearTextSNMP = true;
	
				// Check for dictionary based...
				snmpHostPointer->communityInDict = device->isDictionaryPassword(snmpHostPointer->community.c_str());
				if (snmpHostPointer->communityInDict == true)
					dictionaryCommunityCount++;
				else
				{
	
					// Check for weak community...
					snmpHostPointer->communityWeak = device->isPasswordWeak(snmpHostPointer->community.c_str());
					if (snmpHostPointer->communityWeak != Device::passwordPassed)
						weakCommunityCount++;
				}
	
				// Community Filtering Check...
				if ((hostShowFilterID == true) && (snmpHostPointer->filter.empty()))
					noNMSFilteringCount++;
	
				snmpHostPointer = snmpHostPointer->next;
			}
		}

		// Check NMS Hosts for ACL issues...
		snmpHostPointer = snmpHost;
		while (snmpHostPointer != 0)
		{
			// Any source
			if ((snmpHostPointer->networkMask.compare("0.0.0.0") == 0) && (device->config->checkFilterForAnySource == true))
				accessFromAnySource++;
			if ((snmpHostPointer->networkMask.compare("255.255.255.255") != 0) && (device->config->checkFilterForNetworkSource == true))
				accessFromNetSource++;
			snmpHostPointer = snmpHostPointer->next;
		}
	}

	// Trap Hosts...
	snmpTrapPointer = trapHost;
	while (snmpTrapPointer != 0)
	{
		clearTextSNMP = true;

		// Check for dictionary based...
		snmpTrapPointer->communityInDict = device->isDictionaryPassword(snmpTrapPointer->community.c_str());
		if (snmpTrapPointer->communityInDict == true)
		{
			if (snmpTrapPointer->trap == true)
				dictionaryTrapCount++;
			else
				dictionaryInformCount++;
		}
		else
		{

			// Check for weak community...
			snmpTrapPointer->communityWeak = device->isPasswordWeak(snmpTrapPointer->community.c_str());
			if (snmpTrapPointer->communityWeak != Device::passwordPassed)
			{
				if (snmpTrapPointer->trap == true)
					weakTrapCount++;
				else
					weakInformCount++;
			}
		}

		snmpTrapPointer = snmpTrapPointer->next;
	}


	// ---------------------------------------------------------------
	// Security Issues...
	// ---------------------------------------------------------------

	// Default Community String
	if (defaultCommunityCount > 0)
	{
		errorCode = snmpCommunityIssue(device, communityIssueDefault, defaultCommunityCount, defaultWithWriteCount, defaultWithWriteAllCount);
		if (errorCode != 0)
			return errorCode;
	}

	// Dictionary-based Community String
	if (dictionaryCommunityCount > 0)
	{
		errorCode = snmpCommunityIssue(device, communityIssueDict, dictionaryCommunityCount, dictionaryWithWriteCount, dictionaryWithWriteAllCount);
		if (errorCode != 0)
			return errorCode;
	}

	// Weak Community String
	if (weakCommunityCount > 0)
	{
		errorCode = snmpCommunityIssue(device, communityIssueWeak, weakCommunityCount, weakWithWriteCount, weakWithWriteAllCount);
		if (errorCode != 0)
			return errorCode;
	}

	// Dictionary-based Trap/Inform Host Community...
	if ((dictionaryTrapCount > 0) || (dictionaryInformCount > 0))
	{
		errorCode = snmpTrapIssue(device, communityIssueDict, dictionaryTrapCount, dictionaryInformCount);
		if (errorCode != 0)
			return errorCode;
	}

	// Weak Trap/Inform Host Community...
	if ((weakTrapCount > 0) || (weakInformCount > 0))
	{
		errorCode = snmpTrapIssue(device, communityIssueWeak, weakTrapCount, weakInformCount);
		if (errorCode != 0)
			return errorCode;
	}

	// SNMP Write Access
	if (writeAccessCount > 0)
	{
		errorCode = snmpWriteAccess(device, writeAccessCount);
		if (errorCode != 0)
			return errorCode;
	}

	// SNMP with no filtering
	if ((noFilteringCount > 0) || (noNMSFilteringCount > 0))
	{
		errorCode = snmpWithoutFiltering(device, noFilteringCount, noNMSFilteringCount);
		if (errorCode != 0)
			return errorCode;
	}

	// SNMP with no views
	if (noViewCount > 0)
	{
		errorCode = snmpWithoutView(device, noViewCount);
		if (errorCode != 0)
			return errorCode;
	}

	// Weak SNMP Custom Filtering
	if ((accessFromAnySource > 0) || (accessFromNetSource > 0))
	{
		errorCode = snmpWeakFiltering(device, accessFromAnySource, accessFromNetSource);
		if (errorCode != 0)
			return errorCode;
	}

	// Clear-text SNMP Support
	if (clearTextSNMP == true)
	{
		if (writeAccessCount > 0)
			clearTextWriteAccess = true;
		else
			clearTextWriteAccess = false;
		if (noViewCount > 0)
			clearTextView = false;
		else
			clearTextView = true;
		if ((noFilteringCount > 0) || (noNMSFilteringCount > 0))
			clearTextFilter = false;
		else
			clearTextFilter = true;
		errorCode = snmpClearTextVersion(device, clearTextWriteAccess, clearTextView, clearTextFilter);
		if (errorCode != 0)
			return errorCode;
	}

	errorCode = generateSecuritySpecificReport(device);

	return errorCode;
}


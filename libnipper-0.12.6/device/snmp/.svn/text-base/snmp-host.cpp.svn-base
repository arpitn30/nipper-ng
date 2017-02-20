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
#include "../../globaldefs.h"
#include "../device.h"
#include "snmp.h"


SNMP::snmpHostStruct *SNMP::addHost()							// Adds an SNMP Host
{
	// Variables...
	snmpHostStruct *snmpHostPointer = 0;

	// Create...
	if (snmpHost == 0)
	{
		snmpHost = new (snmpHostStruct);
		snmpHostPointer = snmpHost;
	}
	else
	{
		snmpHostPointer = snmpHost;
		while (snmpHostPointer->next != 0)
			snmpHostPointer = snmpHostPointer->next;
		snmpHostPointer->next = new (snmpHostStruct);
		snmpHostPointer = snmpHostPointer->next;
	}

	// Init...
	snmpHostPointer->next = 0;
	snmpHostPointer->networkMask.assign("255.255.255.255");
	snmpHostPointer->communityInDict = false;
	snmpHostPointer->communityWeak = Device::passwordPassed;

	return snmpHostPointer;
}


SNMP::snmpHostStruct *SNMP::getHost(const char *hostName)		// Gets an SNMP Host
{
	// Variables...
	snmpHostStruct *snmpHostPointer = snmpHost;
	bool found = false;

	// Search...
	while ((snmpHostPointer != 0) && (found == false))
	{
		if (snmpHostPointer->host.compare(hostName) == 0)
			found = true;
		else
			snmpHostPointer = snmpHostPointer->next;
	}

	return snmpHostPointer;
}


bool SNMP::hostCommunityExists(const char *community)
{
	// Variables...
	snmpHostStruct *snmpHostPointer = snmpHost;

	if ((hostShowCommunity == false) && (snmpHostPointer != 0))
		return true;

	// Search...
	while (snmpHostPointer != 0)
	{
		if (snmpHostPointer->community.compare(community) == 0)
			return true;
		else
			snmpHostPointer = snmpHostPointer->next;
	}

	return false;
}


int SNMP::generateHostConfigReport(Device *device)			// Generate Host Configuration Report
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	snmpHostStruct *snmpHostPointer = snmpHost;
	string tempString;
	string filterString;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s SNMP Management Hosts\n", device->config->COL_BLUE, device->config->COL_RESET);

	// Init pointers...
	configReportPointer = device->getConfigSection("CONFIG-SNMP");
	paragraphPointer = device->addParagraph(configReportPointer);

	// Set subsection title...
	paragraphPointer->paragraphTitle.assign(i18n("*ABBREV*SNMP*-ABBREV* *ABBREV*NMS*-ABBREV* Host"));
	if (hostShowFilterID == true)
	{
		paragraphPointer->paragraphTitle.append(" ");
		paragraphPointer->paragraphTitle.append(hostFilterText);
		device->addString(paragraphPointer, hostFilterText);
		device->addString(paragraphPointer, hostFilterText);
		paragraphPointer->paragraph.assign(i18n("Access to the *DEVICETYPE* *ABBREV*SNMP*-ABBREV* agent can be restrict to specific *ABBREV*NMS*-ABBREV* hosts using a *DATA*. This section lists the configured *DATA*."));
	}
	else
		paragraphPointer->paragraph.assign(i18n("Access to the *DEVICETYPE* *ABBREV*SNMP*-ABBREV* agent is restrict to the configured *ABBREV*NMS*-ABBREV* hosts listed in Table *TABLEREF*."));

	// Create Table for SNMP Hosts...
	if (hostShowFilterID == false)
	{
		errorCode = device->addTable(paragraphPointer, "CONFIG-SNMPHOSTS-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("*ABBREV*SNMP*-ABBREV* *ABBREV*NMS*-ABBREV* hosts");
		if (hostShowCommunity == true)
			device->addTableHeading(paragraphPointer->table, i18n("Community"), true);
		if (hostShowInterface == true)
			device->addTableHeading(paragraphPointer->table, i18n("Interface"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Host"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Network Mask"), false);
	}

	// Output views...
	while (snmpHostPointer != 0)
	{
		if ((hostShowFilterID == true) && (filterString.compare(snmpHostPointer->filter) != 0))
		{
			filterString.assign(snmpHostPointer->filter);
			paragraphPointer = device->addParagraph(configReportPointer);
			tempString.assign("CONFIG-SNMPHOSTS-");
			tempString.append(filterString);
			tempString.append("-TABLE");
			errorCode = device->addTable(paragraphPointer, tempString.c_str());
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title.assign(i18n("*ABBREV*SNMP*-ABBREV* *ABBREV*NMS*-ABBREV* "));
			paragraphPointer->table->title.append(hostFilterText);
			paragraphPointer->table->title.append(" ");
			paragraphPointer->table->title.append(filterString);
			if (hostShowCommunity == true)
				device->addTableHeading(paragraphPointer->table, i18n("Community"), true);
			if (hostShowInterface == true)
				device->addTableHeading(paragraphPointer->table, i18n("Interface"), false);
			device->addTableHeading(paragraphPointer->table, i18n("Host"), false);
			device->addTableHeading(paragraphPointer->table, i18n("Network Mask"), false);
		}

		// Table Data...
		if (hostShowCommunity == true)
		{
			if (snmpHostPointer->community.empty())
				device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
			else
				device->addTableData(paragraphPointer->table, snmpHostPointer->community.c_str());
		}
		if (hostShowInterface == true)
		{
			if (snmpHostPointer->interface.empty())
				device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
			else
				device->addTableData(paragraphPointer->table, snmpHostPointer->interface.c_str());
		}
		device->addTableData(paragraphPointer->table, snmpHostPointer->host.c_str());
		device->addTableData(paragraphPointer->table, snmpHostPointer->networkMask.c_str());

		snmpHostPointer = snmpHostPointer->next;
	}

	return errorCode;
}


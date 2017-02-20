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


SNMP::snmpGroupStruct *SNMP::addSNMPGroup()							// Add a group
{
	// Variables...
	snmpGroupStruct *snmpGroupPointer = 0;

	// Create...
	if (snmpGroup == 0)
	{
		snmpGroup = new (snmpGroupStruct);
		snmpGroupPointer = snmpGroup;
	}
	else
	{
		snmpGroupPointer = snmpGroup;
		while (snmpGroupPointer->next != 0)
			snmpGroupPointer = snmpGroupPointer->next;
		snmpGroupPointer->next = new (snmpGroupStruct);
		snmpGroupPointer = snmpGroupPointer->next;
	}

	// Init...
	snmpGroupPointer->version = 3;				// SNMP Version
	snmpGroupPointer->snmpv3 = snmpV3NoAuth;	// SNMP version 3 auth type
	snmpGroupPointer->next = 0;

	return snmpGroupPointer;
}


SNMP::snmpGroupStruct *SNMP::getSNMPGroup(const char *groupname)		// Get a group
{
	// Variables...
	snmpGroupStruct *snmpGroupPointer = snmpGroup;
	bool found = false;

	while ((snmpGroupPointer != 0) && (found == false))
	{
		if (snmpGroupPointer->group.compare(groupname) == 0)
			found = true;
		else
			snmpGroupPointer = snmpGroupPointer->next;
	}

	return snmpGroupPointer;
}


int SNMP::generateGroupConfigReport(Device *device)						// Generate Group Configuration Report
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	snmpGroupStruct *snmpGroupPointer = 0;
	bool showIPv6 = false;
	int errorCode = 0;

	// Init pointers...
	configReportPointer = device->getConfigSection("CONFIG-SNMP");
	paragraphPointer = device->addParagraph(configReportPointer);

	// Set subsection title...
	if ((snmpUser != 0) && (snmpGroup != 0))
		paragraphPointer->paragraphTitle.assign(i18n("*ABBREV*SNMP*-ABBREV* Users And Groups"));
	else if (snmpGroup != 0)
		paragraphPointer->paragraphTitle.assign(i18n("*ABBREV*SNMP*-ABBREV* Groups"));
	else
		paragraphPointer->paragraphTitle.assign(i18n("*ABBREV*SNMP*-ABBREV* Users"));
	paragraphPointer->paragraph.assign(i18n("*ABBREV*SNMP*-ABBREV* v3 access to *DEVICETYPE* can be configured using Users and Groups. This section details those configuration settings."));

	if (snmpGroup != 0)
	{

		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s SNMP Groups\n", device->config->COL_BLUE, device->config->COL_RESET);

		// Should we show the IPv6 column?
		if (snmpGroupIPv6Filter == true)
		{
			snmpGroupPointer = snmpGroup;
			while ((snmpGroupPointer != 0) && (showIPv6 == false))
			{
				if (!snmpGroupPointer->ipv6Filter.empty())
					showIPv6 = true;
				else
					snmpGroupPointer = snmpGroupPointer->next;
			}
		}

		// Create Table...
		errorCode = device->addTable(paragraphPointer, "CONFIG-SNMPGROUP-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("*ABBREV*SNMP*-ABBREV* groups");
		device->addTableHeading(paragraphPointer->table, i18n("Group"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Version"), false);
		if (snmpGroupShowType == true)
			device->addTableHeading(paragraphPointer->table, i18n("Security"), false);
		if (snmpGroupReadView == true)
			device->addTableHeading(paragraphPointer->table, i18n("Read View"), false);
		if (snmpGroupWriteView == true)
			device->addTableHeading(paragraphPointer->table, i18n("Write View"), false);
		if (snmpGroupNotifyView == true)
			device->addTableHeading(paragraphPointer->table, i18n("Notify View"), false);
		if (snmpGroupFilter == true)
			device->addTableHeading(paragraphPointer->table, groupFilterText, false);
		if (showIPv6 == true)
			device->addTableHeading(paragraphPointer->table, groupIPv6FilterText, false);

		// Table Data...
		snmpGroupPointer = snmpGroup;
		while (snmpGroupPointer != 0)
		{
			device->addTableData(paragraphPointer->table, snmpGroupPointer->group.c_str());
			switch (snmpGroupPointer->version)
			{
				case 1:
					device->addTableData(paragraphPointer->table, i18n("1"));
					break;
				case 2:
					device->addTableData(paragraphPointer->table, i18n("2c"));
					break;
				case 3:
					device->addTableData(paragraphPointer->table, i18n("3"));
					break;
				default:
					device->addTableData(paragraphPointer->table, i18n("1 and 2c"));
					break;
			}
			if (snmpGroupShowType == true)
			{
				switch (snmpGroupPointer->snmpv3)
				{
					case snmpV3Auth:
						device->addTableData(paragraphPointer->table, i18n("Auth"));
						break;
					case snmpV3Priv:
						device->addTableData(paragraphPointer->table, i18n("Auth+Priv"));
						break;
					default:
						device->addTableData(paragraphPointer->table, i18n("No Auth"));
						break;
				}
			}
			if (snmpGroupReadView == true)
			{
				if (snmpGroupPointer->readView.empty())
					device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
				else
					device->addTableData(paragraphPointer->table, snmpGroupPointer->readView.c_str());
			}
			if (snmpGroupWriteView == true)
			{
				if (snmpGroupPointer->writeView.empty())
					device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
				else
					device->addTableData(paragraphPointer->table, snmpGroupPointer->writeView.c_str());
			}
			if (snmpGroupNotifyView == true)
			{
				if (snmpGroupPointer->notifyView.empty())
					device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
				else
					device->addTableData(paragraphPointer->table, snmpGroupPointer->notifyView.c_str());
			}
			if (snmpGroupFilter == true)
			{
				if (snmpGroupPointer->filter.empty())
					device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
				else
					device->addTableData(paragraphPointer->table, snmpGroupPointer->filter.c_str());
			}
			if (showIPv6 == true)
			{
				if (snmpGroupPointer->ipv6Filter.empty())
					device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
				else
					device->addTableData(paragraphPointer->table, snmpGroupPointer->ipv6Filter.c_str());
			}
			snmpGroupPointer = snmpGroupPointer->next;
		}
	}

	return errorCode;
}


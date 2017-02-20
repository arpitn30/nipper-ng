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
 *      2. Any code that integrates Nipper MUST display the copyright      *
 *         information below with the programs own copyright information.  *
 *                                                                         *
 *         "Nipper Copyright (C) 2006 - 2008 by Ian Ventura-Whiting"       *
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
#include <cstring>
#include <cstdlib>

#include "../globaldefs.h"
#include "device.h"
#include "administration.h"


int ScreenOSAdministration::generateDeviceTelnetConfig(Device *device)		// A device specific config report output
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	interfaceManagementConfig *interfacePointer = 0;
	int errorCode = 0;

	if (telnetEnabled == true)
	{
		configReportPointer = device->getConfigSection("CONFIG-ADMIN");
		paragraphPointer = device->addParagraph(configReportPointer);
		paragraphPointer->paragraph.assign(i18n("Access to the Telnet service can be enabled on individual interfaces on *DEVICETYPE* devices. Table *TABLEREF* lists the interfaces with the Telnet service enabled."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINTELNETINTER-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("Telnet service interfaces");

		// Headings...
		device->addTableHeading(paragraphPointer->table, i18n("Interface"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Zone"), false);

		interfacePointer = interfaces;
		while (interfacePointer != 0)
		{
			if ((interfacePointer->enabled == true) && (interfacePointer->telnet == true))
			{
				device->addTableData(paragraphPointer->table, interfacePointer->interface.c_str());
				device->addTableData(paragraphPointer->table, interfacePointer->zone.c_str());
			}
			interfacePointer = interfacePointer->next;
		}
	}

	return errorCode;
}


int ScreenOSAdministration::generateDeviceSSHConfig(Device *device)			// A device specific config report output
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	interfaceManagementConfig *interfacePointer = 0;
	int errorCode = 0;

	if (sshEnabled == true)
	{
		configReportPointer = device->getConfigSection("CONFIG-ADMIN");
		paragraphPointer = device->addParagraph(configReportPointer);
		paragraphPointer->paragraph.assign(i18n("Access to the *ABBREV*SSH*-ABBREV* service can be enabled on individual interfaces on *DEVICETYPE* devices. Table *TABLEREF* lists the interfaces with the *ABBREV*SSH*-ABBREV* service enabled."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINSSHINTER-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("*ABBREV*SSH*-ABBREV* service interfaces");

		// Headings...
		device->addTableHeading(paragraphPointer->table, i18n("Interface"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Zone"), false);

		interfacePointer = interfaces;
		while (interfacePointer != 0)
		{
			if ((interfacePointer->enabled == true) && (interfacePointer->ssh == true))
			{
				device->addTableData(paragraphPointer->table, interfacePointer->interface.c_str());
				device->addTableData(paragraphPointer->table, interfacePointer->zone.c_str());
			}
			interfacePointer = interfacePointer->next;
		}
	}

	return errorCode;
}


int ScreenOSAdministration::generateDeviceHTTPConfig(Device *device)		// A device specific config report output
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	interfaceManagementConfig *interfacePointer = 0;
	int errorCode = 0;

	if ((httpEnabled == true) || (httpsEnabled == true))
	{
		configReportPointer = device->getConfigSection("CONFIG-ADMIN");
		paragraphPointer = device->addParagraph(configReportPointer);
		paragraphPointer->paragraph.assign(i18n("Access to the *ABBREV*HTTP*-ABBREV* and *ABBREV*HTTPS*-ABBREV* services can be enabled on individual interfaces on *DEVICETYPE* devices. Table *TABLEREF* lists the interfaces with these services enabled."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINHTTPINTER-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("*ABBREV*HTTP*-ABBREV* service interfaces");

		// Headings...
		device->addTableHeading(paragraphPointer->table, i18n("Interface"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Zone"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*HTTP*-ABBREV*"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*HTTPS*-ABBREV*"), false);

		interfacePointer = interfaces;
		while (interfacePointer != 0)
		{
			if ((interfacePointer->enabled == true) && ((interfacePointer->web == true) || (interfacePointer->ssl == true)))
			{
				device->addTableData(paragraphPointer->table, interfacePointer->interface.c_str());
				device->addTableData(paragraphPointer->table, interfacePointer->zone.c_str());
				if (interfacePointer->web == true)
					device->addTableData(paragraphPointer->table, i18n("Enabled"));
				else
					device->addTableData(paragraphPointer->table, i18n("Disabled"));
				if (interfacePointer->ssl == true)
					device->addTableData(paragraphPointer->table, i18n("Enabled"));
				else
					device->addTableData(paragraphPointer->table, i18n("Disabled"));
			}
			interfacePointer = interfacePointer->next;
		}
	}

	return errorCode;
}


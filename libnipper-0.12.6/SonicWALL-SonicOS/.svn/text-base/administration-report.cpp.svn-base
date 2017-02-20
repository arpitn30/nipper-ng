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
#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "administration.h"
#include "device.h"


int SonicOSAdministration::generateDeviceSSHConfig(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	managementInterface *interfacePointer = 0;
	string tempString;
	int errorCode = 0;

	if ((sonicosInterfaces != 0) && (sshEnabled == true))
	{
		configReportPointer = device->getConfigSection("CONFIG-ADMIN");
		paragraphPointer = device->addParagraph(configReportPointer);
		paragraphPointer->paragraph.assign(i18n("Access to the *ABBREV*SSH*-ABBREV* service on *DEVICETYPE* devices is configured on individual interfaces. Table *TABLEREF* details the *ABBREV*SSH*-ABBREV* interface configuration."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINSSHINTER-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("*ABBREV*SSH*-ABBREV* service interfaces");

		// Headings...
		device->addTableHeading(paragraphPointer->table, i18n("Interface"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Name"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Zone"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Comment"), false);

		interfacePointer = sonicosInterfaces;
		while (interfacePointer != 0)
		{
			if (interfacePointer->ssh == true)
			{
				tempString.assign(device->intToString(interfacePointer->interface));
				device->addTableData(paragraphPointer->table, tempString.c_str());
				device->addTableData(paragraphPointer->table, interfacePointer->name.c_str());
				device->addTableData(paragraphPointer->table, interfacePointer->zone.c_str());
				device->addTableData(paragraphPointer->table, interfacePointer->comment.c_str());
			}
			interfacePointer = interfacePointer->next;
		}
	}

	return errorCode;
}


int SonicOSAdministration::generateDeviceHTTPConfig(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	managementInterface *interfacePointer = 0;
	string tempString;
	int errorCode = 0;

	if ((sonicosInterfaces != 0) && ((httpEnabled == true) || (httpsEnabled == true)))
	{
		configReportPointer = device->getConfigSection("CONFIG-ADMIN");
		paragraphPointer = device->addParagraph(configReportPointer);
		paragraphPointer->paragraph.assign(i18n("Access to the *ABBREV*HTTP*-ABBREV* service on *DEVICETYPE* devices is configured on individual interfaces. Table *TABLEREF* details the *ABBREV*HTTP*-ABBREV* interface configuration."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINHTTPINTER-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("*ABBREV*HTTP*-ABBREV* service interfaces");

		// Headings...
		device->addTableHeading(paragraphPointer->table, i18n("Interface"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Name"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Zone"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*HTTP*-ABBREV*"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*HTTP*-ABBREV* Redirect"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*HTTPS*-ABBREV*"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Comment"), false);

		interfacePointer = sonicosInterfaces;
		while (interfacePointer != 0)
		{
			if ((interfacePointer->http == true) || (interfacePointer->https == true) || (interfacePointer->httpRedirect == true))
			{
				tempString.assign(device->intToString(interfacePointer->interface));
				device->addTableData(paragraphPointer->table, tempString.c_str());
				device->addTableData(paragraphPointer->table, interfacePointer->name.c_str());
				device->addTableData(paragraphPointer->table, interfacePointer->zone.c_str());
				if (interfacePointer->http == true)
					device->addTableData(paragraphPointer->table, i18n("On"));
				else
					device->addTableData(paragraphPointer->table, i18n("Off"));
				if (interfacePointer->httpRedirect == true)
					device->addTableData(paragraphPointer->table, i18n("On"));
				else
					device->addTableData(paragraphPointer->table, i18n("Off"));
				if (interfacePointer->https == true)
					device->addTableData(paragraphPointer->table, i18n("On"));
				else
					device->addTableData(paragraphPointer->table, i18n("Off"));
				device->addTableData(paragraphPointer->table, interfacePointer->comment.c_str());
			}
			interfacePointer = interfacePointer->next;
		}
	}

	return errorCode;
}


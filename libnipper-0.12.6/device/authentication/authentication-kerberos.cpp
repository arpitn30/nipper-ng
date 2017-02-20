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
#include "../../globaldefs.h"
#include "authentication.h"
#include "../device.h"


Authentication::kerberosServerConfig *Authentication::addKerberosServer()
{
	// Variables...
	kerberosServerConfig *kerberosPointer = 0;

	// Create...
	if (kerberosServer == 0)
	{
		kerberosServer = new (kerberosServerConfig);
		kerberosPointer = kerberosServer;
	}
	else
	{
		kerberosPointer = kerberosServer;
		while (kerberosPointer->next != 0)
			kerberosPointer = kerberosPointer->next;
		kerberosPointer->next = new (kerberosServerConfig);
		kerberosPointer = kerberosPointer->next;
	}

	// Init...
	kerberosPointer->timeout = 0;
	kerberosPointer->retries = 0;
	kerberosPointer->port = 750;
	kerberosPointer->next = 0;

	return kerberosPointer;
}


int Authentication::generateConfigKerberosReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	kerberosServerConfig *kerberosPointer = 0;
	string tempString;
	int errorCode = 0;

	configReportPointer = device->getConfigSection("CONFIG-AUTH");
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraphTitle.assign(i18n("Kerberos Configuration"));
	paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices support authentication with Kerberos servers. This section details the configuration."));

	// RADIUS Table...
	errorCode = device->addTable(paragraphPointer, "CONFIG-AUTHKERBEROS-TABLE");
	if (errorCode != 0)
		return errorCode;
	paragraphPointer->table->title = i18n("Kerberos servers");
	if (showKerberosGroupName == true)
		device->addTableHeading(paragraphPointer->table, i18n("Server Group"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Address"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Port"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Realm"), false);
	if (showKerberosTimeout == true)
		device->addTableHeading(paragraphPointer->table, i18n("Timeout"), false);
	if (showKerberosRetries == true)
		device->addTableHeading(paragraphPointer->table, i18n("Retries"), false);

	kerberosPointer = kerberosServer;
	while (kerberosPointer != 0)
	{
		if (showKerberosGroupName == true)
			device->addTableData(paragraphPointer->table, kerberosPointer->groupName.c_str());
		device->addTableData(paragraphPointer->table, kerberosPointer->description.c_str());
		device->addTableData(paragraphPointer->table, kerberosPointer->address.c_str());
		tempString.assign(device->intToString(kerberosPointer->port));
		device->addTableData(paragraphPointer->table, tempString.c_str());
		device->addTableData(paragraphPointer->table, kerberosPointer->realm.c_str());
		if (showKerberosTimeout == true)
		{
			tempString.assign(device->timeToString(kerberosPointer->timeout));
			device->addTableData(paragraphPointer->table, tempString.c_str());
		}
		if (showKerberosRetries == true)
		{
			tempString.assign(device->intToString(kerberosPointer->retries));
			device->addTableData(paragraphPointer->table, tempString.c_str());
		}
		kerberosPointer = kerberosPointer->next;
	}

	return 0;
}



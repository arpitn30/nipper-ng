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


Authentication::securidServerConfig *Authentication::addSecurIDServer()
{
	// Variables...
	securidServerConfig *securidPointer = 0;

	// Create...
	if (securidServer == 0)
	{
		securidServer = new (securidServerConfig);
		securidPointer = securidServer;
	}
	else
	{
		securidPointer = securidServer;
		while (securidPointer->next != 0)
			securidPointer = securidPointer->next;
		securidPointer->next = new (securidServerConfig);
		securidPointer = securidPointer->next;
	}

	// Init...
	securidPointer->timeout = 0;
	securidPointer->retries = 0;
	securidPointer->port = 5500;
	securidPointer->next = 0;

	return securidPointer;
}


int Authentication::generateConfigSecurIDReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	securidServerConfig *securidPointer = 0;
	string tempString;
	int errorCode = 0;

	configReportPointer = device->getConfigSection("CONFIG-AUTH");
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraphTitle.assign(i18n("*ABBREV*RSA*-ABBREV* SecurID Configuration"));
	paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices support authentication with *ABBREV*RSA*-ABBREV* SecurID servers. This section details the configuration."));

	// SecurID Table...
	errorCode = device->addTable(paragraphPointer, "CONFIG-AUTHSECURID-TABLE");
	if (errorCode != 0)
		return errorCode;
	paragraphPointer->table->title = i18n("*ABBREV*RSA*-ABBREV* SecurID servers");
	if (showSecurIDGroupName == true)
		device->addTableHeading(paragraphPointer->table, i18n("Server Group"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Address"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Port"), false);
	if (showSecurIDDuress == true)
		device->addTableHeading(paragraphPointer->table, i18n("Duress"), false);
	if (showSecurIDEncryption == true)
		device->addTableHeading(paragraphPointer->table, i18n("Encryption"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Timeout"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Retries"), false);

	securidPointer = securidServer;
	while (securidPointer != 0)
	{
		if (showSecurIDGroupName == true)
			device->addTableData(paragraphPointer->table, securidPointer->groupName.c_str());
		device->addTableData(paragraphPointer->table, securidPointer->description.c_str());
		device->addTableData(paragraphPointer->table, securidPointer->address.c_str());
		tempString.assign(device->intToString(securidPointer->port));
		device->addTableData(paragraphPointer->table, tempString.c_str());
		if (showSecurIDDuress == true)
			device->addTableData(paragraphPointer->table, securidPointer->duress.c_str());
		if (showSecurIDEncryption == true)
			device->addTableData(paragraphPointer->table, securidPointer->encryption.c_str());
		tempString.assign(device->timeToString(securidPointer->timeout));
		device->addTableData(paragraphPointer->table, tempString.c_str());
		tempString.assign(device->intToString(securidPointer->retries));
		device->addTableData(paragraphPointer->table, tempString.c_str());
		securidPointer = securidPointer->next;
	}

	return 0;
}



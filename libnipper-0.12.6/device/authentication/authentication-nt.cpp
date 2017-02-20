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


Authentication::ntServerConfig *Authentication::addNTServer()
{
	// Variables...
	ntServerConfig *ntPointer = 0;

	// Create...
	if (ntServer == 0)
	{
		ntServer = new (ntServerConfig);
		ntPointer = ntServer;
	}
	else
	{
		ntPointer = ntServer;
		while (ntPointer->next != 0)
			ntPointer = ntPointer->next;
		ntPointer->next = new (ntServerConfig);
		ntPointer = ntPointer->next;
	}

	// Init...
	ntPointer->timeout = 0;
	ntPointer->next = 0;

	return ntPointer;
}


int Authentication::generateConfigNTReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	ntServerConfig *ntPointer = 0;
	string tempString;
	int errorCode = 0;

	configReportPointer = device->getConfigSection("CONFIG-AUTH");
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraphTitle.assign(i18n("*ABBREV*NT*-ABBREV* Configuration"));
	paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices support authentication with *ABBREV*NT*-ABBREV* servers. This section details the configuration."));

	// NT Table...
	errorCode = device->addTable(paragraphPointer, "CONFIG-AUTHNT-TABLE");
	if (errorCode != 0)
		return errorCode;
	paragraphPointer->table->title = i18n("*ABBREV*NT*-ABBREV* servers");
	if (showNTGroupName == true)
		device->addTableHeading(paragraphPointer->table, i18n("Server Group"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
	device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*PDC*-ABBREV*"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Address"), false);

	ntPointer = ntServer;
	while (ntPointer != 0)
	{
		if (showNTGroupName == true)
			device->addTableData(paragraphPointer->table, ntPointer->groupName.c_str());
		device->addTableData(paragraphPointer->table, ntPointer->description.c_str());
		device->addTableData(paragraphPointer->table, ntPointer->pdc.c_str());
		device->addTableData(paragraphPointer->table, ntPointer->address.c_str());
		ntPointer = ntPointer->next;
	}

	return 0;
}



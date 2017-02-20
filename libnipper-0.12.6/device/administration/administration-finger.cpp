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

#include "../../globaldefs.h"
#include "../device.h"
#include "administration.h"


int Administration::generateFingerConfig(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;
	int errorCode = 0;

	// Add service to the services list...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-SERVICES-TABLE");
	device->addTableData(paragraphPointer->table, i18n("Finger Service"));
	if (fingerServiceEnabled == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));

	// Console Settings section...
	configReportPointer = device->getConfigSection("CONFIG-ADMIN");
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraphTitle.assign(i18n("Finger Service Settings"));
	paragraphPointer->paragraph.assign(i18n("The Finger service enables network users to query *DEVICETYPE* devices for information on users. This section details the Finger services configuration."));

	// Console Settings Table...
	errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINFINGER-TABLE");
	if (errorCode != 0)
		return errorCode;
	paragraphPointer->table->title = i18n("Finger service settings");
	device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Setting"), false);
	device->addTableData(paragraphPointer->table, i18n("Finger Service"));
	if (fingerServiceEnabled == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));
	device->addTableData(paragraphPointer->table, i18n("Service *ABBREV*TCP*-ABBREV* Port"));
	device->addTableData(paragraphPointer->table, i18n("79"));

	return 0;
}


int Administration::generateFingerSecurityIssue(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] Finger Service Enabled\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("Finger Service Enabled"));
	securityIssuePointer->reference.assign("GEN.ADMIFING.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("The Finger service was traditionally installed by default on UNIX-based operating systems. The Finger service enables remote users to query *DEVICETYPE* devices for information about the devices users."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the Finger service was enabled on *DEVICENAME*."));

	// Issue impact...
	securityIssuePointer->impactRating = 5;			// MEDIUM
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("A malicious user or attacker could use the Finger service to gain information about users logged in to the device."));

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 7;				// EASY
	paragraphPointer->paragraph.assign(i18n("Tools for querying the Finger service are widely available on the Internet and some *ABBREV*OS*-ABBREV* include Finger query tools by default."));

	// Issue recommendation...
	securityIssuePointer->fixRating = 2;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("Users who do not have authenticated access to the device do not normally need to know who is logged in to the device. *COMPANY* recommends that, if not required, the Finger service should be disabled."));
	if (strlen(configDisableFinger) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configDisableFinger);
	}

	// Conclusions text...
	securityIssuePointer->conLine.append(i18n("the Finger service was enabled"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Disable the Finger service"));

	return 0;
}



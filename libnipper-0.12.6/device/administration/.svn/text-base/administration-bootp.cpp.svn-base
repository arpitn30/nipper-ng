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


int Administration::generateBootPConfig(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;
	int errorCode = 0;

	// Add service to the services list...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-SERVICES-TABLE");
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*BOOTP*-ABBREV* Service"));
	if (bootPEnabled == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));

	// Console Settings section...
	configReportPointer = device->getConfigSection("CONFIG-ADMIN");
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraphTitle.assign(i18n("*ABBREV*BOOTP*-ABBREV* Service Settings"));
	paragraphPointer->paragraph.assign(i18n("The *ABBREV*BOOTP*-ABBREV* service allows remote hosts to load their operating system over the network. This section details the *ABBREV*BOOTP*-ABBREV* services configuration."));

	// Console Settings Table...
	errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINBOOTP-TABLE");
	if (errorCode != 0)
		return errorCode;
	paragraphPointer->table->title = i18n("*ABBREV*BOOTP*-ABBREV* service settings");
	device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Setting"), false);
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*BOOTP*-ABBREV* Service"));
	if (bootPEnabled == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));
	device->addTableData(paragraphPointer->table, i18n("Service *ABBREV*UDP*-ABBREV* Port"));
	device->addTableData(paragraphPointer->table, i18n("67"));

	return errorCode;
}


int Administration::generateBootPSecurityIssue(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] BOOTP Service Enabled\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("*ABBREV*BOOTP*-ABBREV* Service Enabled"));
	securityIssuePointer->reference.assign("GEN.ADMIBOTP.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*ABBREV*BOOTP*-ABBREV* is a datagram protocol that allows compatible hosts to load their operating system over the network from a *ABBREV*BOOTP*-ABBREV* server. *DEVICETYPE* devices are capable of acting as *ABBREV*BOOTP*-ABBREV* servers for other devices. However, *ABBREV*BOOTP*-ABBREV* is rarely used and may represent a security risk."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *ABBREV*BOOTP*-ABBREV* was not disabled. However, it is worth noting that not all *DEVICETYPE* devices support *ABBREV*BOOTP*-ABBREV*."));

	// Issue impact...
	securityIssuePointer->impactRating = 4;			// LOW
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("An attacker could use the *ABBREV*BOOTP*-ABBREV* service to download a copy of the device's *ABBREV*OS*-ABBREV* software."));

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 7;				// EASY
	paragraphPointer->paragraph.assign(i18n("Tools are available on the Internet to access *ABBREV*BOOTP*-ABBREV* servers."));

	// Issue recommendation...
	securityIssuePointer->fixRating = 2;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if not required, the *ABBREV*BOOTP*-ABBREV* service should be disabled."));
	if (strlen(configDisableBootP) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configDisableBootP);
	}

	// Conclusions text...
	securityIssuePointer->conLine.append(i18n("the *ABBREV*BOOTP*-ABBREV* service was enabled"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Disable the *ABBREV*BOOTP*-ABBREV* service"));

	return 0;
}

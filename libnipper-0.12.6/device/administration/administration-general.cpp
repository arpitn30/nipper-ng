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


int Administration::generateGeneralConfig(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;
	int errorCode = 0;

	// General Settings section...
	configReportPointer = device->getConfigSection("CONFIG-ADMIN");
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraphTitle.assign(i18n("General Administration Settings"));
	paragraphPointer->paragraph.assign(i18n("This section describes some general *DEVICETYPE* device settings."));

	// General Settings Table...
	errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINGENERAL-TABLE");
	if (errorCode != 0)
		return errorCode;
	paragraphPointer->table->title = i18n("General administration settings");
	device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Setting"), false);
	if (consoleSupported == true)
	{
		device->addTableData(paragraphPointer->table, i18n("Console Port"));
		if (consoleEnabled == true)
			device->addTableData(paragraphPointer->table, i18n("Enabled"));
		else
			device->addTableData(paragraphPointer->table, i18n("Disabled"));
	}
	if (consoleTimeoutSupported == true)
	{
		device->addTableData(paragraphPointer->table, i18n("Console Connection Timeout"));
		if (consoleTimeout == 0)
			device->addTableData(paragraphPointer->table, i18n("No Timeout"));
		else
		{
			tempString.assign(device->timeToString(consoleTimeout));
			device->addTableData(paragraphPointer->table, tempString.c_str());
		}
	}
	if (cdpSupported == true)
	{
		device->addTableData(paragraphPointer->table, i18n("*ABBREV*CDP*-ABBREV*"));
		if (cdpEnabled == true)
			device->addTableData(paragraphPointer->table, i18n("Enabled"));
		else
			device->addTableData(paragraphPointer->table, i18n("Disabled"));
		if (cdpVersionSupported == true)
		{
			device->addTableData(paragraphPointer->table, i18n("*ABBREV*CDP*-ABBREV* Version"));
			tempString.assign(device->intToString(cdpVersion));
			device->addTableData(paragraphPointer->table, tempString.c_str());
		}
	}
	if (auxSupported == true)
	{
		device->addTableData(paragraphPointer->table, i18n("*ABBREV*AUX*-ABBREV* Port"));
		if (auxEnabled == true)
			device->addTableData(paragraphPointer->table, i18n("Enabled"));
		else
			device->addTableData(paragraphPointer->table, i18n("Disabled"));
	}
	if (connectionTimeoutSupported == true)
	{
		device->addTableData(paragraphPointer->table, i18n("Service Connection Timeout"));
		if (connectionTimeout == 0)
			device->addTableData(paragraphPointer->table, i18n("No Timeout"));
		else
		{
			tempString.assign(device->timeToString(connectionTimeout));
			device->addTableData(paragraphPointer->table, tempString.c_str());
		}
	}

	// Device specific stuff...
	errorCode = generateDeviceGeneralConfig(device);

	return 0;
}


int Administration::generateDeviceGeneralConfig(Device *device)
{
	return 0;
}


int Administration::generateCDPSecurityIssue(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] CDP Service Enabled\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("*ABBREV*CDP*-ABBREV* Service Enabled"));
	securityIssuePointer->reference.assign("GEN.INTECDPE.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*ABBREV*CDP*-ABBREV* is a proprietary protocol that was developed and is primarily used by Cisco. A *ABBREV*CDP*-ABBREV* enabled device can be configured to broadcast *ABBREV*CDP*-ABBREV* packets on the network enabling network management applications and *ABBREV*CDP*-ABBREV* aware devices to identify each other. *ABBREV*CDP*-ABBREV* packets include information about the sender, such as *ABBREV*OS*-ABBREV* version and *ABBREV*IP*-ABBREV* address information."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *ABBREV*CDP*-ABBREV* service was enabled on *DEVICENAME*"));

	// Issue impact...
	securityIssuePointer->impactRating = 4;			// LOW
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("*ABBREV*CDP*-ABBREV* packets contain information about the sender, such as hardware model information, operating system version and *ABBREV*IP*-ABBREV* address details. This information would give an attacker valuable information about the *DEVICE*. The attacker could then use this information as part of a targetted attack."));

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 7;				// Easy
	paragraphPointer->paragraph.assign(i18n("*ABBREV*CDP*-ABBREV* packets are broadcast to an entire network segment. The attacker or malicious user would require access to a network segment on which the *ABBREV*CDP*-ABBREV* packets are broadcast and network monitoring software. A wide variety of network monitoring, packet capture and analysis tools are available on the Internet."));

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if not required, *ABBREV*CDP*-ABBREV* should be disabled."));
	if (strlen(disableCDPText) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(disableCDPText);
	}
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("In some configurations with *ABBREV*IP*-ABBREV* phones, deployed using either Auto Discovery or *ABBREV*DHCP*-ABBREV*, the *ABBREV*CDP*-ABBREV* service may need to be enabled. In this situation *ABBREV*CDP*-ABBREV* should be disabled on all interfaces for which it is not required."));

	// Conclusions text...
	securityIssuePointer->conLine.append(i18n("the *ABBREV*CDP*-ABBREV* service was enabled"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Disable *ABBREV*CDP*-ABBREV*"), true);	

	return errorCode;
}

int Administration::generateAUXSecurityIssue(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] AUX Port Enabled\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("*ABBREV*AUX*-ABBREV* Port Enabled"));
	securityIssuePointer->reference.assign("GEN.ADMIAUXE.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("The *ABBREV*AUX*-ABBREV* port's primary purpose is to provide a remote administration capability. With a modem connected to the *ABBREV*AUX*-ABBREV* port, a remote administrator could dial into *DEVICENAME* in order to perform remote administration."));
	if (callbackSupported == true)
		paragraphPointer->paragraph.assign(i18n(" To enhance security, *DEVICETYPE* devices can be configured with a callback facility. When configured, the callback facility drops an incoming call and dials the administrator back."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	if ((callbackSupported == true) && (callbackEnabled == false))
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *ABBREV*AUX*-ABBREV* port was not disabled on *DEVICENAME* and no callback facility was configured. However, it is worth noting that not all *DEVICETYPE* devices are configured with an *ABBREV*AUX*-ABBREV* port, therefore this issue could have been falsely determined."));
	else
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *ABBREV*AUX*-ABBREV* port was not disabled on *DEVICENAME*. However, it is worth noting that not all *DEVICETYPE* devices are configured with an *ABBREV*AUX*-ABBREV* port, therefore this issue could have been falsely determined."));

	// Issue impact...
	securityIssuePointer->impactRating = 7;			// HIGH
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("If an attacker was able to connect to the device remotely, then they may be able to brute-force the login to gain remote administrative access to the *DEVICENAME*. An attacker with physical access to *DEVICENAME* could attach a modem to the *ABBREV*AUX*-ABBREV* port in order to attack the device from a remote location."));

	// Issue ease...
	securityIssuePointer->easeRating = 2;				// CHALLENGING
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	paragraphPointer->paragraph.assign(i18n("In order to successfully exploit this issue, *DEVICENAME* would require a modem to be attached to the *ABBREV*AUX*-ABBREV* port. If a modem is already attached, an attacker may discover the modem's telephone number during a war-dial. Furthermore, war dial software is freely available on the Internet."));

	// Issue recommendation...
	securityIssuePointer->fixRating = 2;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if not required, the *ABBREV*AUX*-ABBREV* port should be disabled."));
	if (callbackSupported == true)
		paragraphPointer->paragraph.append(i18n(" If the *ABBREV*AUX*-ABBREV* port is required, *COMPANY* recommends that the callback facility should be configured."));
	if (strlen(configAuxPort) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configAuxPort);
	}
	if ((callbackSupported == true) && (strlen(configCallback) > 0))
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configCallback);
	}

	// Conclusions text...
	if (callbackSupported == true)
		securityIssuePointer->conLine.append(i18n("the *ABBREV*AUX*-ABBREV* port was enabled and no callback facility was configured"));
	else
		securityIssuePointer->conLine.append(i18n("the *ABBREV*AUX*-ABBREV* port was enabled"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Disable the *ABBREV*AUX*-ABBREV* port"), true);
	if (callbackSupported == true)
		device->addRecommendation(securityIssuePointer, i18n("Configure the callback facility"), true);

	return errorCode;
}


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

// Include...
#include <cstring>

#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "banner.h"
#include "general.h"
#include "device.h"


CatalystBanner::CatalystBanner()
{
	preLogonBanner = true;				// Support Banner(s) Before Logon?
	postLogonBanner = false;			// Support Banner(s) After Logon?

	configPreLogonBanner = i18n("The *ABBREV*MOTD*-ABBREV* banner is shown when a user connects to *DEVICETYPE* devices. It is configured using a delimiting character, the delimeter is used to mark the start and the end of the banner message. The banner can be configured with the following command:*CODE**COMMAND*set banner motd *CMDUSER*delimeter*-CMDUSER* *CMDUSER*banner-message*-CMDUSER* *CMDUSER*delimeter*-CMDUSER**-COMMAND**-CODE*");		// The text that explains how to config a prelogon banner, with commands...
	//configPostLogonBanner;			// The text that explains how to config a post logon banner, with commands...

	telnetMessage = true;				// Is the Telnet message enabled?
	telnetMessageSupported = false;		// Is the Telnet message option available?
}


int CatalystBanner::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	bannerStruct *bannerPointer = 0;
	int tempInt = 0;
	bool setting = true;
	char delimeter[3] = {0,0,0};
	string tempString;
	int position = 0;
	bool end = false;

	// Init
	tempInt = 2;
	if (strcmp(command->part(0), "set") == 0)
		setting = true;
	else
		setting = false;

	// Telnet banner...
	if (strcmp(command->part(tempInt), "telnet") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sTelnet Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		if (strcmp(command->part(tempInt), "enable") == 0)
			telnetMessage = true;
		else
			telnetMessage = false;
		telnetMessageSupported = true;
	}

	// MOTD...
	else if (strcmp(command->part(tempInt), "motd") == 0)
	{
		tempInt++;

		// The setup...
		if (command->part(tempInt)[0] != '^')
		{
			delimeter[0] = command->part(tempInt)[0];
			position = 1;
		}
		else if (strlen(command->part(tempInt)) > 1)
		{
			delimeter[0] = command->part(tempInt)[0];
			delimeter[1] = command->part(tempInt)[1];
			position = 2;
		}
		if (strlen(command->part(tempInt) + position) > 0)
		{
			if (strncmp(command->part(tempInt) + position, (const char *)&delimeter, position) == 0)
				end = true;
		}

		// Get banner...
		if (end == false)
		{
			bannerPointer = addBanner();
			bannerPointer->banner = preLogon;
			bannerPointer->name.assign(i18n("*ABBREV*MOTD*-ABBREV*"));
			bannerPointer->description.assign(i18n("The *ABBREV*MOTD*-ABBREV* banner message is presented to users before they logon. The *ABBREV*MOTD*-ABBREV* banner configured on *DEVICENAME* follows:"));
			bannerPointer->connectionType = anyConnection;
			tempString.assign(strstr(line, (const char *)&delimeter) + position);

			// Get the lines...
			while ((end == false) && (feof(device->inputFile) == 0))
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sMOTD Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (tempString.find((const char *)&delimeter) != tempString.npos)
				{
					end = true;
					tempString.erase(tempString.find((const char *)&delimeter));
				}

				addBannerLine(bannerPointer, tempString.c_str());

				// Read a line from the config...
				if (end == false)
				{
					device->readLine(line, lineSize);
					tempString.assign(line);
				}
			}
		}
		else
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sMOTD Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		}
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int CatalystBanner::processDefaults(Device *device)
{
	if ((telnetMessageSupported == false) && (device->general->versionMajor > 6))
		telnetMessageSupported = true;

	return 0;
}


int CatalystBanner::generateConfigSpecificReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;

	if (banner == 0)
		generateConfigBannerReport(device);

	configReportPointer = device->getConfigSection("CONFIG-BANNER");
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraphTitle.assign(i18n("Telnet Banner Message"));
	if (telnetMessageSupported == true)
	{
		paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices are configured with a Telnet banner message by default. Unlike the *ABBREV*MOTD*-ABBREV* banner, the Telnet banner message cannot be defined, it is either switched on or off. The Telnet banner message is \"Cisco Systems Console\"."));
		if (telnetMessage == true)
			paragraphPointer->paragraph.append(i18n(" This message is enabled on *DEVICENAME*."));
		else
			paragraphPointer->paragraph.append(i18n(" This message is disabled on *DEVICENAME*."));
	}
	else
		paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices display a \"Cisco Systems Console\" message, or something similar depending on the *DEVICEOS* version. Unlike the *ABBREV*MOTD*-ABBREV* banner, this message cannot be changed and it cannot be disabled on *DEVICEVERSIONFULL*."));

	return 0;
}


int CatalystBanner::generateSecuritySpecificReport(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;
	int errorCode = 0;

	if ((telnetMessage == true) || (telnetMessageSupported = false))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Fixed Telnet Banner Message Enabled\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("Fixed Telnet Banner Message Enabled"));
		securityIssuePointer->reference.assign("COS.BANNTELN.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("The *DEVICETYPE* devices Telnet banner message is different from the *ABBREV*MOTD*-ABBREV* banner message in that it cannot be configured. If enabled, the Telnet banner message \"Cisco Systems Console\", or something similar depending on the *DEVICEOS* version, will be displayed."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the Telnet banner message was enabled on *DEVICENAME*."));

		// Issue impact...
		securityIssuePointer->impactRating = 2;			// Informational
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("Because the Telnet banner message cannot be changed and includes the manufacturer, it could help an attacker to identify the device. An attacker will look for any information from a device in order to help determine the type of the device. The information could then be used as part of a targeted attack against *DEVICENAME*."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 9;				// Trivial
		paragraphPointer->paragraph.assign(i18n("The Telnet banner message is returned when a user connects to start a new session."));

		// Issue recommendation...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that the Telnet banner should be disabled."));
		if (telnetMessageSupported == false)
		{
			securityIssuePointer->fixRating = 8;				// Involved
			paragraphPointer->paragraph.append(i18n(" However, the banner message cannot be disabled on *DEVICEVERSION*. *COMPANY* recommends that the device *ABBREV*OS*-ABBREV* should be upgraded so that the banner message can be disabled."));
		}
		else
		{
			securityIssuePointer->fixRating = 2;				// Trivial
			paragraphPointer->paragraph.append(i18n(" The Telnet banner message can be disabled with the following command:*CODE**COMMAND*set banner telnet disable*-COMMAND**-CODE*"));
		}

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("the fixed Telnet banner message is enabled"));

		// Recommendation list text...
		if (telnetMessageSupported == false)
			device->addRecommendation(securityIssuePointer, i18n("Upgrade the *DEVICEOS* version"));
		device->addRecommendation(securityIssuePointer, i18n("Disable the Telnet banner message"));
	}

	return errorCode;
}


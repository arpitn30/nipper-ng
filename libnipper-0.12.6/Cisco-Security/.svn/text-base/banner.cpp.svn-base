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

#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "device.h"
#include "banner.h"


CiscoSecBanner::CiscoSecBanner()
{
	// Banner settings...
	preLogonBanner = true;						// Support Banner(s) Before Logon?
	postLogonBanner = true;						// Support Banner(s) After Logon?
	configPreLogonBanner = i18n("The *ABBREV*MOTD*-ABBREV* banner message is displayed before logon for connections to *DEVICENAME*. The *ABBREV*MOTD*-ABBREV* banner message can be configured with the following command:*CODE**COMMAND*banner motd *CMDUSER*message-text*-CMDUSER**-COMMAND**-CODE*");			// The text that explains how to config a prelogon banner, with commands...
	configPostLogonBanner = i18n("The Exec banner message is displayed once a successful logon has occured, before the enable prompt. The Exec banner message can be configured with the following command:*CODE**COMMAND*banner exec *CMDUSER*message-text*-CMDUSER**-COMMAND**-CODE*");			// The text that explains how to config a post logon banner, with commands...
}


int CiscoSecBanner::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	bannerStruct *bannerPointer = 0;
	int errorCode = 0;
	int tempInt = 0;
	bool setting = false;

	// Init
	if (strcmp(command->part(0), "no") == 0)
	{
		tempInt = 2;
		setting = false;
	}
	else
	{
		tempInt = 1;
		setting = true;
	}

	// Exec...
	if (strcmp(command->part(tempInt), "exec") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sExec Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		if (setting == true)
		{
			bannerPointer = getBanner("Exec");
			if (bannerPointer == 0)
			{
				bannerPointer = addBanner();
				bannerPointer->banner = postLogon;
				bannerPointer->name.assign("Exec");	
				bannerPointer->description.assign(i18n("The Exec banner is displayed after a connection logon has occured and before the enable prompt."));
				bannerPointer->connectionType = anyConnection;
				bannerPointer->bannerFile = false;
			}
			addBannerLine(bannerPointer, strstr(line, "exec") + 5);
		}
	}

	// MOTD...
	else if (strcmp(command->part(tempInt), "motd") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sMOTD Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		if (setting == true)
		{
			bannerPointer = getBanner("*ABBREV*MOTD*-ABBREV*");
			if (bannerPointer == 0)
			{
				bannerPointer = addBanner();
				bannerPointer->banner = preLogon;
				bannerPointer->name.assign("*ABBREV*MOTD*-ABBREV*");	
				bannerPointer->description.assign(i18n("The *ABBREV*MOTD*-ABBREV* banner is displayed when a user connects, before the logon prompt."));
				bannerPointer->connectionType = anyConnection;
				bannerPointer->bannerFile = false;
			}
			addBannerLine(bannerPointer, strstr(line, "motd") + 5);
		}
	}

	// Login...
	else if (strcmp(command->part(tempInt), "login") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sLogin Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		if (setting == true)
		{
			bannerPointer = getBanner("Login");
			if (bannerPointer == 0)
			{
				bannerPointer = addBanner();
				bannerPointer->banner = preLogon;
				bannerPointer->name.assign("Login");	
				bannerPointer->description.assign(i18n("The Login banner is displayed when a Telnet user connects, before the logon prompt but after any configured *ABBREV*MOTD*-ABBREV* banner message."));
				bannerPointer->connectionType = telnetConnection;
				bannerPointer->bannerFile = false;
			}
			addBannerLine(bannerPointer, strstr(line, "login") + 6);
		}
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return errorCode;
}


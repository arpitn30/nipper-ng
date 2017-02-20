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


PassportBanner::PassportBanner()
{
	// Banner settings...
	preLogonBanner = true;						// Support Banner(s) Before Logon?
	postLogonBanner = true;						// Support Banner(s) After Logon?
	configPreLogonBanner = i18n("The pre-logon banner message is configured on *DEVICETYPE* devices by adding banner message lines and then enabling the custom banner message. This can be done with the following commands:*CODE**COMMAND*cli banner add *CMDUSER*banner-message*-CMDUSER**-COMMAND**COMMAND*cli banner defaultbanner false*-COMMAND**-CODE*");		// The text that explains how to config a prelogon banner, with commands...
	configPostLogonBanner = i18n("The *ABBREV*MOTD*-ABBREV* banner message is configured on *DEVICETYPE* devices by adding message lines and then enabling the custom message. This can be done with the following command:*CODE**COMMAND*cli motd add *CMDUSER*banner-message*-CMDUSER**-COMMAND**COMMAND*cli motd defaultbanner false*-COMMAND**-CODE*");			// The text that explains how to config a post logon banner, with commands...
}


int PassportBanner::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	bannerStruct *bannerPointer = 0;

	// motd banner add...
	if ((strcmp(command->part(1), "motd") == 0) && (strcmp(command->part(2), "add") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sMOTD Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		bannerPointer = getBanner("*ABBREV*MOTD*-ABBREV*");
		if (bannerPointer == 0)
		{
			bannerPointer = addBanner();
			bannerPointer->banner = postLogon;
			bannerPointer->enabled = false;
			bannerPointer->name.assign(i18n("*ABBREV*MOTD*-ABBREV*"));
			bannerPointer->description.assign(i18n("The *ABBREV*MOTD*-ABBREV* banner message is presented to users after they logon. The *ABBREV*MOTD*-ABBREV* banner configured on *DEVICENAME* follows:"));
			bannerPointer->connectionType = anyConnection;
		}
		addBannerLine(bannerPointer, command->part(3));
	}

	// motd default...
	else if ((strcmp(command->part(1), "motd") == 0) && (strcmp(command->part(2), "defaultbanner") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sMOTD Banner On/Off Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		bannerPointer = getBanner("*ABBREV*MOTD*-ABBREV*");
		if (bannerPointer != 0)
		{
			if (strcmp(command->part(3), "true") == 0)
				bannerPointer->enabled = false;
			else
				bannerPointer->enabled = true;
		}
	}

	// banner banner add...
	else if ((strcmp(command->part(1), "banner") == 0) && (strcmp(command->part(2), "add") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sBanner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		bannerPointer = getBanner("Logon");
		if (bannerPointer == 0)
		{
			bannerPointer = addBanner();
			bannerPointer->banner = preLogon;
			bannerPointer->enabled = false;
			bannerPointer->name.assign(i18n("Logon"));
			bannerPointer->description.assign(i18n("The logon banner message is presented to users before they logon. The logon banner configured on *DEVICENAME* follows:"));
			bannerPointer->connectionType = anyConnection;
		}
		addBannerLine(bannerPointer, command->part(3));
	}

	// banner default...
	else if ((strcmp(command->part(1), "banner") == 0) && (strcmp(command->part(2), "defaultbanner") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sBanner On/Off Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		bannerPointer = getBanner("Logon");
		if (bannerPointer != 0)
		{
			if (strcmp(command->part(3), "true") == 0)
				bannerPointer->enabled = false;
			else
				bannerPointer->enabled = true;
		}
	}

	return 0;
}


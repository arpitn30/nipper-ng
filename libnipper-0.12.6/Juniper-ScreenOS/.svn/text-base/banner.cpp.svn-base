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


ScreenOSBanner::ScreenOSBanner()
{
	// Banner settings...
	preLogonBanner = true;						// Support Banner(s) Before Logon?
	postLogonBanner = true;					// Support Banner(s) After Logon?
	configPreLogonBanner = i18n("A pre-logon banner message for remote connections to *DEVICETYPE* devices can be configured with the following command:*CODE**COMMAND*set admin auth banner telnet login \"*CMDUSER*banner-message*-CMDUSER*\"*-COMMAND**-CODE*");			// The text that explains how to config a prelogon banner, with commands...
	configPostLogonBanner = i18n("A post logon message for administrative connections to *DEVICETYPE* devices can be configured with the following command:*CODE**COMMAND*set admin auth banner secondary \"*CMDUSER*banner-message*-CMDUSER*\"*-COMMAND**-CODE*");			// The text that explains how to config a post logon banner, with commands...
}


int ScreenOSBanner::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	bannerStruct *bannerPointer = 0;
	string tempBanner;
	string tempString;

	if (strcmp(command->part(0), "unset") != 0)
	{

		// Telnet... 
		if ((strcmp(command->part(1), "admin") == 0) && (strcmp(command->part(2), "auth") == 0) && (strcmp(command->part(3), "banner") == 0) && (strcmp(command->part(4), "telnet") == 0) && (strcmp(command->part(5), "login") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sTelnet Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			bannerPointer = addBanner();
			bannerPointer->banner = preLogon;
			bannerPointer->name.assign(i18n("Telnet"));
			bannerPointer->description.assign(i18n("The Telnet banner message is presented to Telnet users before they logon and *ABBREV*SSH*-ABBREV* users after logon. The Telnet banner message configured on *DEVICENAME* is:"));
			bannerPointer->connectionType = (telnetConnection & sshConnection);
			addBannerLine(bannerPointer, command->part(6));
		}

		// Console... 
		else if ((strcmp(command->part(1), "admin") == 0) && (strcmp(command->part(2), "auth") == 0) && (strcmp(command->part(3), "banner") == 0) && (strcmp(command->part(4), "console") == 0) && (strcmp(command->part(5), "login") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sConsole Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			bannerPointer = addBanner();
			bannerPointer->banner = preLogon;
			bannerPointer->name.assign(i18n("Console"));
			bannerPointer->description.assign(i18n("The Console banner message is presented to users before they logon. The message configured on *DEVICENAME* is:"));
			bannerPointer->connectionType = (consoleConnection);
			addBannerLine(bannerPointer, command->part(6));
		}

		// Secondary... 
		else if ((strcmp(command->part(1), "admin") == 0) && (strcmp(command->part(2), "auth") == 0) && (strcmp(command->part(3), "banner") == 0) && (strcmp(command->part(4), "secondary") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sSecondary Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			bannerPointer = addBanner();
			bannerPointer->banner = postLogon;
			bannerPointer->name.assign(i18n("Secondary"));
			bannerPointer->description.assign(i18n("The secondary banner message is presented to users after they logon for Telnet *ABBREV*SSH*-ABBREV* and Console connections. The message configured on *DEVICENAME* is:"));
			bannerPointer->connectionType = (telnetConnection & sshConnection & consoleConnection);

			tempBanner.assign(command->part(5));
			while (tempBanner.find("\\n") != tempBanner.npos)
			{
				tempString.assign(tempBanner.substr(0, tempBanner.find_first_of("\\n")));
				tempBanner.erase(0, tempBanner.find_first_of("\\n") + 2);
				addBannerLine(bannerPointer, tempString.c_str());
			}
			addBannerLine(bannerPointer, tempBanner.c_str());
		}

		// All others...
		else
			device->lineNotProcessed(line);
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


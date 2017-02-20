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


ProCurveBanner::ProCurveBanner()
{
	// Banner settings...
	preLogonBanner = true;					// Support Banner(s) Before Logon?
	postLogonBanner = false;					// Support Banner(s) After Logon?
	configPreLogonBanner = i18n("The *ABBREV*MOTD*-ABBREV* banner message is shown before users logon. The *ABBREV*MOTD*-ABBREV* banner message can be configured by entering the following command:*CODE**COMMAND*banner motd *CMDUSER*delimiter*-CMDUSER**-COMMAND**-CODE*");			// The text that explains how to config a prelogon banner, with commands...
	configPostLogonBanner = i18n("");			// The text that explains how to config a post logon banner, with commands...
}


int ProCurveBanner::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	bannerStruct *bannerPointer = 0;
	string tempString;
	bool end = false;

	// Telnet banner...
	if ((strcmp(command->part(0), "banner") == 0) && (strcmp(command->part(1), "motd") == 0))
	{
		if (strlen(command->part(2)) == 2)
		{
			if (command->part(2)[1] == '\"')
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
			tempString.assign(strstr(line, command->part(2) + 1));

			// Get the lines...
			while ((end == false) && (feof(device->inputFile) == 0))
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sMOTD Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (tempString.find("\"") != tempString.npos)
				{
					end = true;
					tempString.erase(tempString.find("\""));
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


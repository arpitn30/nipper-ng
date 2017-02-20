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
#include "iosdevice.h"
#include "banner.h"


IOSBanner::IOSBanner()
{
	// Banner settings...
	preLogonBanner = true;						// Support Banner(s) Before Logon?
	postLogonBanner = true;						// Support Banner(s) After Logon?
	configPreLogonBanner = i18n("The *ABBREV*MOTD*-ABBREV* banner message is shown to all connections to *DEVICETYPE* devices prior to the logon. The *ABBREV*MOTD*-ABBREV* banner message can be configured with the following command:*CODE**COMMAND*banner motd *CMDUSER*delimeter*-CMDUSER* *CMDUSER*banner-message*-CMDUSER* *CMDUSER*delimeter*-CMDUSER**-COMMAND**-CODE*");			// The text that explains how to config a prelogon banner, with commands...
	configPostLogonBanner = i18n("The Exec banner is shown to remote and console users after a logon occurs. The Exec banner can be configured with the following command:*CODE**COMMAND*banner exec *CMDUSER*delimeter*-CMDUSER* *CMDUSER*banner-message*-CMDUSER* *CMDUSER*delimeter*-CMDUSER**-COMMAND**-CODE*");			// The text that explains how to config a post logon banner, with commands...
}


int IOSBanner::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	bannerStruct *bannerPointer = 0;
	char delimeter[3] = {0,0,0};
	string tempString;
	int position = 0;
	bool end = false;

	// Init
	if (strcmp(command->part(0), "no") != 0)
	{

		// MOTD...
		if (strcmp(command->part(1), "motd") == 0)
		{

			// The setup...
			if (command->part(2)[0] != '^')
			{
				delimeter[0] = command->part(2)[0];
				position = 1;
			}
			else if (strlen(command->part(2)) > 1)
			{
				delimeter[0] = command->part(2)[0];
				delimeter[1] = command->part(2)[1];
				position = 2;
			}
			if (strlen(command->part(2) + position) > 0)
			{
				if (strncmp(command->part(2) + position, (const char *)&delimeter, position) == 0)
					end = true;
			}

			// Get banner...
			if (end == false)
			{
				bannerPointer = addBanner();
				bannerPointer->banner = preLogon;
				bannerPointer->name.assign(i18n("*ABBREV*MOTD*-ABBREV*"));
				bannerPointer->description.assign(i18n("The *ABBREV*MOTD*-ABBREV* banner message is presented to users before they logon to *DEVICETYPE* devices. The *ABBREV*MOTD*-ABBREV* banner message configured on *DEVICENAME* follows:"));
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

		// Login...
		else if (strcmp(command->part(1), "login") == 0)
		{

			// The setup...
			if (command->part(2)[0] != '^')
			{
				delimeter[0] = command->part(2)[0];
				position = 1;
			}
			else if (strlen(command->part(2)) > 1)
			{
				delimeter[0] = command->part(2)[0];
				delimeter[1] = command->part(2)[1];
				position = 2;
			}
			if (strlen(command->part(2) + position) > 0)
			{
				if (strncmp(command->part(2) + position, (const char *)&delimeter, position) == 0)
					end = true;
			}

			// Get banner...
			if (end == false)
			{
				bannerPointer = addBanner();
				bannerPointer->banner = preLogon;
				bannerPointer->name.assign(i18n("Login"));
				bannerPointer->description.assign(i18n("The Login banner message is presented to users before they logon to *DEVICETYPE* devices. The Login banner message configured on *DEVICENAME* follows:"));
				bannerPointer->connectionType = anyConnection;
				tempString.assign(strstr(line, (const char *)&delimeter) + position);

				// Get the lines...
				while ((end == false) && (feof(device->inputFile) == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sLogin Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

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
					printf("%sLogin Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			}
		}

		// Exec...
		else if (strcmp(command->part(1), "exec") == 0)
		{

			// The setup...
			if (command->part(2)[0] != '^')
			{
				delimeter[0] = command->part(2)[0];
				position = 1;
			}
			else if (strlen(command->part(2)) > 1)
			{
				delimeter[0] = command->part(2)[0];
				delimeter[1] = command->part(2)[1];
				position = 2;
			}
			if (strlen(command->part(2) + position) > 0)
			{
				if (strncmp(command->part(2) + position, (const char *)&delimeter, position) == 0)
					end = true;
			}

			// Get banner...
			if (end == false)
			{
				bannerPointer = addBanner();
				bannerPointer->banner = postLogon;
				bannerPointer->name.assign(i18n("Exec"));
				bannerPointer->description.assign(i18n("The Exec banner message is presented to users after they logon to *DEVICETYPE* devices (excluding reverse Telnet users). The Exec banner message configured on *DEVICENAME* follows:"));
				bannerPointer->connectionType = anyConnection;
				tempString.assign(strstr(line, (const char *)&delimeter) + position);

				// Get the lines...
				while ((end == false) && (feof(device->inputFile) == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sExec Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

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
					printf("%sExec Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			}
		}

		// Incoming...
		else if (strcmp(command->part(1), "incoming") == 0)
		{

			// The setup...
			if (command->part(2)[0] != '^')
			{
				delimeter[0] = command->part(2)[0];
				position = 1;
			}
			else if (strlen(command->part(2)) > 1)
			{
				delimeter[0] = command->part(2)[0];
				delimeter[1] = command->part(2)[1];
				position = 2;
			}
			if (strlen(command->part(2) + position) > 0)
			{
				if (strncmp(command->part(2) + position, (const char *)&delimeter, position) == 0)
					end = true;
			}

			// Get banner...
			if (end == false)
			{
				bannerPointer = addBanner();
				bannerPointer->banner = postLogon;
				bannerPointer->name.assign(i18n("Incoming"));
				bannerPointer->description.assign(i18n("The Incoming banner message is presented to reverse Telnet users after they logon to *DEVICETYPE* devices. The Incoming banner message configured on *DEVICENAME* follows:"));
				bannerPointer->connectionType = reverseTelnetConnection;
				tempString.assign(strstr(line, (const char *)&delimeter) + position);

				// Get the lines...
				while ((end == false) && (feof(device->inputFile) == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sIncoming Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

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
					printf("%sIncoming Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			}
		}

		// PPP/SLIP...
		else if (strcmp(command->part(1), "slip-ppp") == 0)
		{

			// The setup...
			if (command->part(2)[0] != '^')
			{
				delimeter[0] = command->part(2)[0];
				position = 1;
			}
			else if (strlen(command->part(2)) > 1)
			{
				delimeter[0] = command->part(2)[0];
				delimeter[1] = command->part(2)[1];
				position = 2;
			}
			if (strlen(command->part(2) + position) > 0)
			{
				if (strncmp(command->part(2) + position, (const char *)&delimeter, position) == 0)
					end = true;
			}

			// SLIP/PPP banner...
			if (end == false)
			{
				bannerPointer = addBanner();
				bannerPointer->banner = preLogon;
				bannerPointer->name.assign(i18n("*ABBREV*SLIP*-ABBREV*-*ABBREV*PPP*-ABBREV*"));
				bannerPointer->description.assign(i18n("The *ABBREV*SLIP*-ABBREV*-*ABBREV*PPP*-ABBREV* banner message is presented to users connecting to *DEVICETYPE* devices using *ABBREV*SLIP*-ABBREV* or *ABBREV*PPP*-ABBREV*. The *ABBREV*SLIP*-ABBREV*-*ABBREV*PPP*-ABBREV* banner message configured on *DEVICENAME* follows:"));
				bannerPointer->connectionType = pppConnection;
				tempString.assign(strstr(line, (const char *)&delimeter) + position);

				// Get the lines...
				while ((end == false) && (feof(device->inputFile) == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sSLIP-PPP Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

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
					printf("%sSLIP-PPP Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			}
		}



		// Exec...
		else if (strcmp(command->part(1), "aaa") == 0)
		{

			// The setup...
			if (command->part(3)[0] != '^')
			{
				delimeter[0] = command->part(3)[0];
				position = 1;
			}
			else if (strlen(command->part(3)) > 1)
			{
				delimeter[0] = command->part(3)[0];
				delimeter[1] = command->part(3)[1];
				position = 2;
			}
			if (strlen(command->part(3) + position) > 0)
			{
				if (strncmp(command->part(3) + position, (const char *)&delimeter, position) == 0)
					end = true;
			}

			// Get banner...
			if (end == false)
			{
				bannerPointer = addBanner();
				bannerPointer->banner = preLogon;
				bannerPointer->name.assign(i18n("*ABBREV*AAA*-ABBREV*"));
				bannerPointer->description.assign(i18n("The *ABBREV*AAA*-ABBREV* banner message is presented to users before they logon to *DEVICETYPE* devices (except in cases where *ABBREV*TACACS+*-ABBREV* is the first authentication method). The *ABBREV*AAA*-ABBREV* banner message configured on *DEVICENAME* follows:"));
				bannerPointer->connectionType = anyConnection;
				tempString.assign(strstr(line, (const char *)&delimeter) + position);

				// Get the lines...
				while ((end == false) && (feof(device->inputFile) == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sAAA Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

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
					printf("%sAAA Banner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			}
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


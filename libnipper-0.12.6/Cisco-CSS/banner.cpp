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

CiscoCSSBanner::CiscoCSSBanner()
{
	// Banner settings...
	preLogonBanner = true;						// Support Banner(s) Before Logon?
	configPreLogonBanner = i18n("On *DEVICETYPE* devices, a banner message must be created with a text editor and then the file transfered to the script directory on the device. Once the banner message file is on the device, it can be configured with the following command:*CODE**COMMAND*prelogin-banner \"*CMDUSER*filename*-CMDUSER*\"*-COMMAND**-CODE*");			// The text that explains how to config a prelogon banner, with commands...
}


int CiscoCSSBanner::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	bannerStruct *bannerPointer = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("%sBanner Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

	if (strcmp(command->part(0), "no") != true)
	{
		bannerPointer = addBanner();
		bannerPointer->banner = preLogon;
		bannerPointer->bannerFile = true;
		bannerPointer->connectionType = anyConnection;
		bannerPointer->name.assign("PreLogin");
		bannerPointer->description.assign(i18n("The Pre-Login banner message is presented to a user before they logon to the *DEVICETYPE* device."));
		bannerPointer->filename.assign(command->part(1));
	}

	return 0;
}



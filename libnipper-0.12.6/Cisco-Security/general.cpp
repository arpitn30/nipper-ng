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

// Include
#include <cstdlib>
#include <cstring>

#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "device.h"
#include "general.h"


// Initialisation...
CiscoSecGeneral::CiscoSecGeneral()
{
}


int CiscoSecGeneral::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	int tempInt = 0;
	bool setting = false;

	// Init
	if (strcmp(command->part(0), "no") == 0)
	{
		tempInt = 1;
		setting = false;
	}
	else
	{
		tempInt = 0;
		setting = true;
	}

	// Hostname
	if (strcmp(command->part(tempInt), "hostname") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sHostname Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		hostname = command->part(tempInt + 1);
	}

	return 0;
}


int CiscoSecGeneral::processDefaults(Device *device)
{
	// Split Version Numbers...
	if ((!version.empty()) && (versionMajor == 0))
	{
		versionMajor = atoi(version.c_str());
		versionMinor = atoi(strchr(version.c_str(), '.') + 1);
		versionRevision = atoi(strchr(version.c_str(), '(') + 1);
		noMinor = false;
		noRevision = false;
	}

	return 0;
}


int CiscoSecGeneral::processSpecificDefaults()
{
	return 0;
}


int CiscoSecGeneral::generateConfigSpecificReport(Device *device)
{
	// Variables...
	int errorCode = 0;

	return errorCode;
}


int CiscoSecGeneral::generateSecuritySpecificReport(Device *device)
{
	// Variables...
	int errorCode = 0;

	return errorCode;
}

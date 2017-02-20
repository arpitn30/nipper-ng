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

// Includes...
#include <cstdlib>
#include <cstring>

#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "device.h"
#include "general.h"


// Initialisation...
CatalystGeneral::CatalystGeneral()
{
}


int CatalystGeneral::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	int tempInt = 0;
	bool setting = false;

	// Init
	tempInt = 1;
	if (strcmp(command->part(0), "set") == 0)
		setting = true;
	else
		setting = false;

	// Version
	if (strcmp(command->part(0), "#version") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sVersion Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		version.assign(command->part(1));
	}

	else if (strcmp(command->part(tempInt), "system") == 0)
	{
		tempInt++;

		// Hostname...
		if (strcmp(command->part(tempInt), "name") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sHostname Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			tempInt++;
			hostname.assign(command->part(tempInt));
		}

		// Location...
		else if (strcmp(command->part(tempInt), "location") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sLocation Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			tempInt++;
			location.assign(strstr(line, command->part(tempInt)));
		}

		// Contact...
		else if (strcmp(command->part(tempInt), "contact") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sContact Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			tempInt++;
			contact.assign(strstr(line, command->part(tempInt)));
		}

		// Core File...
		else if (strcmp(command->part(tempInt), "core-file") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sCore File Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			tempInt++;
			coreFile.assign(command->part(tempInt));
		}

		// Syslog File...
		else if (strcmp(command->part(tempInt), "syslog-file") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sSyslog File Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			tempInt++;
			syslogFile.assign(command->part(tempInt));
		}
	}

	// Prompt
	if (strcmp(command->part(tempInt), "prompt") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sPrompt Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		cliPrompt.assign(command->part(tempInt));
	}

	return 0;
}


int CatalystGeneral::processDefaults(Device *device)
{
	// Split Version Numbers...
	if (!version.empty())
	{
		versionMajor = atoi(version.c_str());
		versionMinor = atoi(strchr(version.c_str(), '.') + 1);
		versionRevision = atoi(strchr(version.c_str(), '(') + 1);
	}

	return 0;
}


int CatalystGeneral::generateConfigSpecificReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	int errorCode = 0;

	// Get Config Report Section...
	configReportPointer = device->getConfigSection("CONFIG-GENERAL");

	// Get Paragraph Pointer...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-GENERAL-TABLE");

	// Core File...
	if (!coreFile.empty())
	{
		device->addTableData(paragraphPointer->table, i18n("Core File"));
		device->addTableData(paragraphPointer->table, coreFile.c_str());
	}

	// Syslog File...
	if (!syslogFile.empty())
	{
		device->addTableData(paragraphPointer->table, i18n("Syslog File"));
		device->addTableData(paragraphPointer->table, syslogFile.c_str());
	}

	// CLI Prompt...
	if (!cliPrompt.empty())
	{
		device->addTableData(paragraphPointer->table, i18n("*ABBREV*CLI*-ABBREV* Prompt Text"));
		device->addTableData(paragraphPointer->table, cliPrompt.c_str());
	}

	return errorCode;
}


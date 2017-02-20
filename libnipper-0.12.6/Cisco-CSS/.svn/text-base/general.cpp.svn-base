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
CiscoCSSGeneral::CiscoCSSGeneral()
{
	coreDumpsEnabled = true;				// Core Dumps Enabled?
}


int CiscoCSSGeneral::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Version (in general)...
	if ((strcmp(command->part(0), "!Active") == 0) && (strcmp(command->part(1), "version:") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sVersion Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		version = command->part(2);
	}

	// Potential hostname...
	else if ((command->part(0)[strlen(command->part(0)) - 1] == '#') && (strncmp(command->part(1), "sh", 2) == 0) && (strncmp(command->part(2), "run", 3) == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sPotential Hostname Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempHostname.assign(command->part(0));
		tempHostname.erase(tempHostname.find_last_of("#"));
	}

	// SNMP name...
	else if ((strcmp(command->part(0), "snmp") == 0) && (strcmp(command->part(1), "name") == 0))
	{
		if (hostname.empty())
			hostname.assign(command->part(2));
	}

	// dump...
	else if (strcmp(command->part(0), "dump") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sCore Dump Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		if (strcmp(command->part(1), "enable") == 0)
			coreDumpsEnabled = true;
		else
			coreDumpsEnabled = false;
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int CiscoCSSGeneral::processDefaults(Device *device)
{
	// Variables...
	string tempString;

	// Set hostname...
	if ((hostname.empty()) && (!tempHostname.empty()))
		hostname.assign(tempHostname);

	// Split Version Numbers...
	if ((!version.empty()) && (version.length() > 8))
	{
		tempString = version.substr(2, 2);
		versionMajor = atoi(tempString.c_str());
		tempString = version.substr(4, 2);
		versionMinor = atoi(tempString.c_str());
		tempString = version.substr(6, 1);
		versionRevision = atoi(tempString.c_str());
		tempString = version.substr(7, 2);
		versionTweak = atoi(tempString.c_str());
	}

	return 0;
}


int CiscoCSSGeneral::generateConfigSpecificReport(Device *device)
{
		// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	int errorCode = 0;

	// Get Config Report Section...
	configReportPointer = device->getConfigSection("CONFIG-GENERAL");

	// Get Paragraph Pointer...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-GENERAL-TABLE");

	// Core Dumps...
	device->addTableData(paragraphPointer->table, i18n("Core Dumps"));
	if (coreDumpsEnabled == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));

	return errorCode;
}


int CiscoCSSGeneral::generateSecuritySpecificReport(Device *device)
{
		// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	int errorCode = 0;

	// Service Password Encryption...
	if (coreDumpsEnabled == true)
	{

		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Core Dumps Enabled\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("Core Dumps Enabled"));
		securityIssuePointer->reference.assign("CSS.COREDUMP.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices have a debug option that causes the memory of the device to be written to the disk (to a core file) when a fatal error occurs. The core file enables developers and technical support to analyse what happened at the time of the fatal error. This functionality is similar to that found on UNIX systems and is enabled by default. After the fatal error has occured, *DEVICETYPE* devices will reboot automatically."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that core dumps were enabled on *DEVICENAME*."));

		// Issue impact...
		securityIssuePointer->impactRating = 3;			// LOW
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("An attacker who was able to repeatedly cause fatal errors on *DEVICENAME* may be able to fill the available disk space with core files. A full disk may cause *DEVICENAME* further unexpected problems."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 2;			// Challenge
		paragraphPointer->paragraph.assign(i18n("The attacker would have to find a vulnerability to cause the fatal errors on the device. However, if *DEVICENAME* is not adequately maintained it may fill with core files over time on its own."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 1;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("Core files are rarely examined by network administrators and are of more use to Cisco technicians when analysing software or hardware faults. Therefore *COMPANY* recommends that, if not used, core dumps should be disabled."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("Core dumps can be disabled on *DEVICETYPE* devices with the following command:*CODE**COMMAND*dump disable*-COMMAND**-CODE*"));

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("core dumps were enabled"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Disable core dumps"));
	}

	return errorCode;
}



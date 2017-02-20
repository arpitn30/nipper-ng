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
#include <cstdlib>
#include <cstring>

#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "iosdevice.h"
#include "general.h"


//vulnerabilityConfig ios-vuln6  {i18n("Multiple DLSw Denial of Service"), true, false, "CVE-2008-1152", "28465", "cisco-amb-20080326-dlsw", &ios-vuln6-ver, false, 0};
//vulnerabilityConfig ios-vuln5  {i18n("Dual-stack Router IPv6 Denial Of Service"), true, false, "CVE-2008-1153", "28461", "cisco-sa-20080326-IPv4IPv6", &ios-vuln5-ver, false, &ios-vuln6};
//vulnerabilityConfig ios-vuln4  {i18n("SSH Multiple Denial of Service"), true, false, "CVE-2008-1159", "29314", "cisco-sa-20080521-ssh", &ios-vuln4-ver, false, &ios-vuln5};
//vulnerabilityConfig ios-vuln3  {i18n("Failure to Handle Exceptional Conditions"), true, false, "CVE-2006-3906", "19176", "cisco-sr-20060726-ike", &ios-vuln3-ver, false, &ios-vuln4};
//vulnerabilityConfig ios-vuln2  {i18n("FTP Server Multiple Vulnerabilities"), false, true, "", "23885", "cisco-sa-20070509-iosftp", &ios-vuln2-ver, false, &ios-vuln3};
//vulnerabilityConfig ios-vuln1  {i18n("SNMP Remote Authentication Bypass"), false, true, "CVE-2008-0960", "29623", "cisco-sa-20080610-snmpv3", &ios-vuln1-ver, false, &ios-vuln2};
/*
	struct vulnVersionConfig ios_vuln_ver3 {12, 3, 0, 0, 12, 3, 13, 0, 0};
	struct vulnVersionConfig ios_vuln_ver2 {12, 2, 0, 0, 12, 2, 7, 0, &ios_vuln_ver3};
	struct vulnVersionConfig ios_vuln_ver1 {12, 1, 0, 0, 12, 1, 21, 0, &ios_vuln_ver2};
	struct vulnVersionConfig ios_vuln_ver {12, 0, 7, 0, 12, 0, 7, 0, &ios_vuln_ver1};
	struct vulnerabilityConfig ios_vuln   {"DNS Protocol Insufficient Transaction ID Randomization DNS Spoofing", false, false, "CVE-2008-1447", "30131", "cisco-sa-20080708-dns", &ios_vuln_ver, false, 0};//&ios-vuln1};
*/

// Initialisation...
IOSGeneral::IOSGeneral()
{
	servicePasswordEncryption = true;
}


int IOSGeneral::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
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

	// Version
	else if (strcmp(command->part(tempInt), "version") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sVersion Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		if (versionMajor == 0)
		{
			version = command->part(tempInt + 1);
			if (!version.empty())
			{
				versionMajor = atoi(version.c_str());
				if ((version.find_first_of('.') != string::npos) && (version.length() > version.find_first_of('.') + 1))
					versionMinor = atoi(version.c_str() + version.find_first_of('.') + 1);
			}
			noMinor = false;
		}
	}

	// Service lines...
	else if (strcmp(command->part(tempInt), "service") == 0)
	{
		tempInt++;

		// Password Encryption...
		if (strcmp(command->part(tempInt), "password-encryption") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sService Password-Encryption Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			if (setting == false)
				servicePasswordEncryption = off;
			else
				servicePasswordEncryption = on;
		}
	}

	return 0;
}


int IOSGeneral::processDefaults(Device *device)
{
	// Password Encryption
	if (servicePasswordEncryption == unconfigured)
	{
		// No version, default to off
		if (version.empty())
			servicePasswordEncryption = off;
		else if (versionMajor >= 10)
			servicePasswordEncryption = off;
	}

	return 0;
}

int IOSGeneral::generateConfigSpecificReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	int errorCode = 0;

	// Get Config Report Section...
	configReportPointer = device->getConfigSection("CONFIG-GENERAL");

	// Get Paragraph Pointer...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-GENERAL-TABLE");

	// Password Encryption...
	if (servicePasswordEncryption != unconfigured)
	{
		device->addTableData(paragraphPointer->table, i18n("Service Password Encryption"));
		if (servicePasswordEncryption == on)
			device->addTableData(paragraphPointer->table, i18n("Enabled"));
		else
			device->addTableData(paragraphPointer->table, i18n("Disabled"));
	}

	return errorCode;
}


int IOSGeneral::generateSecuritySpecificReport(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	int errorCode = 0;

	// Service Password Encryption...
	if (servicePasswordEncryption == off)
	{

		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Service Password Encryption Disabled\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("Service Password Encryption Disabled"));
		securityIssuePointer->reference.assign("IOS.PASSENCR.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("The *DEVICETYPE* service password encryption option instructs *DEVICENAME* to store the passwords using Cisco type-7 encryption. By default on *DEVICETYPE* devices the passwords are stored in the configuration file in their clear text form. *COMPANY* determined that encrypted password storage had not been enabled on *DEVICENAME*."));

		// Issue impact...
		securityIssuePointer->impactRating = 5;			// MEDIUM
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("A malicious user or an attacker with access to the device's configuration could quickly extract clear text passwords without having to decode or brute-force them. Alternatively, a malicious user could gain a clear text password if they were closely watching a network administrator. The attacker could then make use of the stolen credentials to gain a level of access to *DEVICENAME*."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 2;			// Challenge
		paragraphPointer->paragraph.assign(i18n("An attacker would require access to the device configuration or would have to be closely watching a network administrator. This issue may require the attacker to have access to the device or a backup copy of the configuration for *DEVICENAME*."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 1;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("Although Cisco type-7 passwords are easily reversed and there are a number of programs that reverse them, they do provide an effective barrier against a casual observer. Therefore, *COMPANY* recommends that password encryption should be enabled. This can be done with the following Cisco *ABBREV*IOS*-ABBREV* command:"));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*CODE**COMMAND*service password-encryption*-COMMAND**-CODE*"));

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("service password encryption was disabled"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Enable service password encryption"));
	}
	return errorCode;
}

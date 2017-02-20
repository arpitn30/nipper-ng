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


#include "../../globaldefs.h"
#include "../device.h"
#include "general.h"


General::General()
{
	versionMajor = 0;
	versionMinor = 0;
	versionRevision = 0;
	versionTweak = 0;
	modules = 0;
	vulnerabilities = 0;

	noMinor = true;
	noRevision = true;
	noTweak = true;
}


General::~General()
{
	// Variables...
	deviceModuleStruct *modulePointer;

	while (modules != 0)
	{
		modulePointer = modules->next;
		delete (modules);
		modules = modulePointer;
	}
}


void General::addDeviceModule(int slot, const char *module, const char *options)
{
	// Variables...
	deviceModuleStruct *modulePointer;

	// Add module struct...
	if (modules == 0)
	{
		modules = new (deviceModuleStruct);
		modulePointer = modules;
	}
	else
	{
		modulePointer = modules;
		while (modulePointer->next != 0)
			modulePointer = modulePointer->next;
		modulePointer->next = new (deviceModuleStruct);
		modulePointer = modulePointer->next;
	}

	// Init...
	modulePointer->next = 0;
	modulePointer->slot = slot;
	modulePointer->description.assign(module);
	if (options != 0)
		modulePointer->options.assign(options);
}


int General::generateConfigReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	deviceModuleStruct *modulePointer;
	string tempString;
	bool showModuleOptions = false;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s General Device Settings\n", device->config->COL_BLUE, device->config->COL_RESET);

	// Get Config Report Section...
	configReportPointer = device->getConfigSection("CONFIG-GENERAL");

	// Section title...
	configReportPointer->title = i18n("General Device Settings");

	// Paragraph...
	paragraphPointer = device->addParagraph(configReportPointer);

	// Table...
	errorCode = device->addTable(paragraphPointer, "CONFIG-GENERAL-TABLE");
	if (errorCode != 0)
		return errorCode;

	// Set Table title...
	paragraphPointer->table->title = i18n("General device settings");

	// Set Table headings
	device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Setting"), false);

	// Add hostname...
	if (!hostname.empty())
	{
		device->addTableData(paragraphPointer->table, i18n("Hostname"));
		device->addTableData(paragraphPointer->table, hostname.c_str());
	}

	// Add device model/type...
	if (!deviceModel.empty())
	{
		device->addTableData(paragraphPointer->table, i18n("Model"));
		device->addTableData(paragraphPointer->table, deviceModel.c_str());
	}

	// Add version...
	if (versionMajor != 0)
	{
		device->addTableData(paragraphPointer->table, i18n("*DEVICEOS* Version"));
		device->addTableData(paragraphPointer->table, version.c_str());
	}

	// Add location...
	if (!location.empty())
	{
		device->addTableData(paragraphPointer->table, i18n("Location"));
		device->addTableData(paragraphPointer->table, location.c_str());
	}

	// Add contact...
	if (!contact.empty())
	{
		device->addTableData(paragraphPointer->table, i18n("Contact"));
		device->addTableData(paragraphPointer->table, contact.c_str());
	}

	// Device specific stuff...
	errorCode = generateConfigSpecificReport(device);

	// Modules?
	if (modules != 0)
	{
		paragraphPointer = device->addParagraph(configReportPointer);
		errorCode = device->addTable(paragraphPointer, "CONFIG-MODULES-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("*DEVICETYPE* modules");
		device->addTableHeading(paragraphPointer->table, i18n("Slot"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Module"), false);
		modulePointer = modules;
		while (modulePointer != 0)
		{
			if (!modulePointer->options.empty())
				showModuleOptions = true;
			modulePointer = modulePointer->next;
		}
		if (showModuleOptions == true)
			device->addTableHeading(paragraphPointer->table, i18n("Module Details"), false);
		modulePointer = modules;
		while (modulePointer != 0)
		{
			tempString.assign(device->intToString(modulePointer->slot));
			device->addTableData(paragraphPointer->table, tempString.c_str());
			device->addTableData(paragraphPointer->table, modulePointer->description.c_str());
			if ((showModuleOptions == true) && (!modulePointer->options.empty()))
				device->addTableData(paragraphPointer->table, modulePointer->options.c_str());
			else if (showModuleOptions == true)
				device->addTableData(paragraphPointer->table, "-");
			modulePointer = modulePointer->next;
		}
	}

	return errorCode;
}


int General::generateSecurityReport(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	int errorCode = 0;
	int vulnCount = 0;
	vulnerabilityConfig *vulnerabilityPointer = 0;
	vulnVersionConfig *versionPointer = 0;
	bool found = false;
	bool dos = false;
	bool remote = false;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s Software Vulnerability Checks\n", device->config->COL_BLUE, device->config->COL_RESET);

	if ((versionMajor != 0) && (vulnerabilities != 0))
	{
		vulnerabilityPointer = vulnerabilities;
		while (vulnerabilityPointer != 0)
		{
			found = false;
			versionPointer = vulnerabilityPointer->versions;
			while ((versionPointer != 0) && (found == false))
			{

				// Lower Version
				if ((versionMajor > versionPointer->versionMajor) || ((versionMajor == versionPointer->versionMajor) && ((versionMinor > versionPointer->versionMinor) || (noMinor == true))) || ((versionMajor == versionPointer->versionMajor) && (versionMinor == versionPointer->versionMinor) && ((versionRevision > versionPointer->versionRevision) || (noRevision == true))) || ((versionMajor == versionPointer->versionMajor) && (versionMinor == versionPointer->versionMinor) && (versionRevision == versionPointer->versionRevision) && ((versionTweak >= versionPointer->versionTweak) || (noTweak == true))))
				{
					// Upper Version
					if ((versionMajor < versionPointer->endVersionMajor) || ((versionMajor == versionPointer->endVersionMajor) && ((versionMinor < versionPointer->endVersionMinor) || (noMinor == true))) || ((versionMajor == versionPointer->endVersionMajor) && (versionMinor == versionPointer->endVersionMinor) && ((versionRevision < versionPointer->endVersionRevision) || (noRevision == true))) || ((versionMajor == versionPointer->endVersionMajor) && (versionMinor == versionPointer->endVersionMinor) && (versionRevision == versionPointer->endVersionRevision) && ((versionTweak <= versionPointer->endVersionTweak) || (noTweak == true))))
					{
						vulnerabilityPointer->vulnerable = true;
						vulnCount = true;
						found = true;
						if (vulnerabilityPointer->dos == true)
							dos = true;
						if (vulnerabilityPointer->remote == true)
							remote = true;
					}
				}

				versionPointer = versionPointer->next;
			}
			vulnerabilityPointer = vulnerabilityPointer->next;
		}
	}

	if (vulnCount > 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Software Vulnerabilities Exist\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		if (vulnCount > 1)
			securityIssuePointer->title.assign(i18n("Software Vulnerabilities"));
		else
			securityIssuePointer->title.assign(i18n("Software Vulnerability"));
		securityIssuePointer->reference.assign("GEN.GENEVULN.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("It is critically important that software should be regularly maintained with patches and upgrades in order to help mitigate the risk of an attacker exploiting a known software vulnerability. In addition to security features and fixes, software updates will often include additional functionality and features."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		if (vulnCount > 1)
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *DEVICEVERSIONFULL* running on *DEVICENAME* contains the vulnerabilities listed in *TABLEREF*."));
		else
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *DEVICEVERSIONFULL* running on *DEVICENAME* contains the vulnerability shown in *TABLEREF*."));
		if ((dos == true) && (remote == true))
			paragraphPointer->paragraph.append(i18n(" The vulnerabilities include *ABBREV*DoS*-ABBREV* and remote command execution vulnerabilities."));
		else if (dos == true)
			paragraphPointer->paragraph.append(i18n(" The vulnerabilities include *ABBREV*DoS*-ABBREV* vulnerabilities."));
		else if (remote == true)
			paragraphPointer->paragraph.append(i18n(" The vulnerabilities include remote command execution vulnerabilities."));

		errorCode = device->addTable(paragraphPointer, "SEC-VULNERABILITY-TABLE");
		if (errorCode != 0)
			return errorCode;
		if (vulnCount > 1)
			paragraphPointer->table->title = i18n("Potential software vulnerabilities");
		else
			paragraphPointer->table->title = i18n("Potential software vulnerability");
		device->addTableHeading(paragraphPointer->table, i18n("Vulnerability"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*CVE*-ABBREV*"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*BID*-ABBREV*"), false);
		device->addTableHeading(paragraphPointer->table, device->deviceMake, false);

		vulnerabilityPointer = vulnerabilities;
		while (vulnerabilityPointer != 0)
		{
			if (vulnerabilityPointer->vulnerable == true)
			{
				device->addTableData(paragraphPointer->table, vulnerabilityPointer->description);
				device->addTableData(paragraphPointer->table, vulnerabilityPointer->cveReference);
				device->addTableData(paragraphPointer->table, vulnerabilityPointer->bidReference);
				device->addTableData(paragraphPointer->table, vulnerabilityPointer->otherReference);
			}
			vulnerabilityPointer = vulnerabilityPointer->next;
		}

		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("It is worth noting that *COMPANY* used the version number in order to identify the potential vulnerabilities, patches may have already been applied to resolve the issues. Furthermore, a specific device configuration may be required in order for the device to become vulnerable."));

		// Issue impact...
		if (remote == true)
			securityIssuePointer->impactRating = 10;			// Critical
		else if (dos == true)
			securityIssuePointer->impactRating = 8;				// High
		else
			securityIssuePointer->impactRating = 7;				// High
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		if ((dos == true) && (remote == true))
			paragraphPointer->paragraph.assign(i18n("The identified vulnerabilities could enable a remote attacker to gain access unauthorise access to *DEVICENAME*. Furthermore, the vulnerabilities could also enable an attacker to perform a *ABBREV*DoS*-ABBREV* disrupting network services."));
		else if (dos == true)
			paragraphPointer->paragraph.assign(i18n("The identified vulnerabilities include *ABBREV*DoS*-ABBREV* vulnerabilities, enabling an attacker to disrupt network services."));
		else if (remote == true)
			paragraphPointer->paragraph.assign(i18n("The identified vulnerabilities could enable a remote attacker to gain access unauthorise access to *DEVICENAME*"));
		paragraphPointer->paragraph.append(i18n(" More information on the vulnerabilities can be obtained from the following web sites:"));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		device->addListItem(paragraphPointer, i18n("*ABBREV*CVE*-ABBREV*: *URL*http://cve.mitre.org*-URL*"));
		device->addListItem(paragraphPointer, i18n("*ABBREV*BID*-ABBREV: *URL*http://www.securityfocus.com*-URL*"));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 8;				// Easy
		paragraphPointer->paragraph.assign(i18n("Exploit code is widely available on the Internet for known *DEVICETYPE* vulnerabilities."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 8;				// Involved
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* strongly recommends that the *DEVICEOS* should be patched / upgraded to the latest software version."));

		// Conclusions text...
		if (vulnCount > 1)
			securityIssuePointer->conLine.append(i18n("the *DEVICEOS* software contains known vulnerabilities"));
		else
			securityIssuePointer->conLine.append(i18n("the *DEVICEOS* software contains a known vulnerability"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("patch the *DEVICEOS* software to the latest version"));
	}

	// Device specific stuff...
	errorCode = generateSecuritySpecificReport(device);

	return errorCode;
}



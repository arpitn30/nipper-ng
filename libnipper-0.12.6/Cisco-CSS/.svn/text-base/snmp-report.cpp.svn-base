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
#include "../globaldefs.h"
#include "device.h"
#include "general.h"
#include "snmp.h"


int CiscoCSSSNMP::generateConfigSpecificReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	int errorCode = 0;

	// Get Config Report Section...
	configReportPointer = device->getConfigSection("CONFIG-SNMP");

	// Get Paragraph Pointer...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-SNMP-TABLE");

	// Trap Source...
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*SNMP*-ABBREV* Trap Source"));
	device->addTableData(paragraphPointer->table, trapSource.c_str());

	// Server Reload...
	device->addTableData(paragraphPointer->table, i18n("Server Reloads"));
	if (reloadAllowed == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));

	return errorCode;
}


int CiscoCSSSNMP::generateSecuritySpecificReport(Device *device)
{
	// Variables...
	snmpCommunity *snmpCommunityPointer = 0;
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	bool dictionaryCommunity = false;
	bool weakCommunity = false;
	bool writeAccess = false;
	int errorCode = 0;

	// Searching for issues...
	snmpCommunityPointer = community;
	while (snmpCommunityPointer != 0)
	{
		if ((snmpCommunityPointer->enabled == true) && (snmpCommunityPointer->type != communityReadOnly) && (((communityRequiresHosts == true) && (hostCommunityExists(snmpCommunityPointer->community.c_str()) == true)) || (communityRequiresHosts == false)))
		{
			writeAccess = true;
			if (snmpCommunityPointer->communityInDict == true)
				dictionaryCommunity = true;
			else if (snmpCommunityPointer->communityWeak != Device::passwordPassed)
				weakCommunity = true;
		}
		snmpCommunityPointer = snmpCommunityPointer->next;
	}

	// System Shutdown via SNMP...
	if ((reloadAllowed == true) && (writeAccess == true))
	{

		// Write Access...
		securityIssuePointer = device->getSecurityIssue("GEN.SNMPWRIT.1");
		if (securityIssuePointer != 0)
		{
			securityIssuePointer->impactRating++;
			paragraphPointer = securityIssuePointer->impact;
			while (paragraphPointer->next != 0)
				paragraphPointer = paragraphPointer->next;
			device->addString(paragraphPointer, "CSS.SNMPRELO.1");
			paragraphPointer->paragraph.append(i18n(" Additionally, the attacker could cause a *ABBREV*DoS*-ABBREV* condition by causing *DEVICENAME* to reload (see section *SECTIONNO*).")); 
			device->addRelatedIssue(securityIssuePointer, "CSS.SNMPRELO.1");
		}

		// Clear-text SNMP...
		securityIssuePointer = device->getSecurityIssue("GEN.SNMPCLEA.1");
		if (securityIssuePointer != 0)
		{
			securityIssuePointer->impactRating++;
			paragraphPointer = securityIssuePointer->impact;
			device->addString(paragraphPointer, "CSS.SNMPRELO.1");
			paragraphPointer->paragraph.append(i18n(" Additionally, the attacker could cause a *ABBREV*DoS*-ABBREV* condition by causing *DEVICENAME* to reload (see section *SECTIONNO*).")); 
			device->addRelatedIssue(securityIssuePointer, "CSS.SNMPRELO.1");
		}

		// Dictionary-based Community Strings...
		if (dictionaryCommunity == true)
		{
			securityIssuePointer = device->getSecurityIssue("GEN.SNMPDICT.1");
			if (securityIssuePointer != 0)
			{
				securityIssuePointer->impactRating++;
				paragraphPointer = securityIssuePointer->impact;
				while (paragraphPointer->next != 0)
					paragraphPointer = paragraphPointer->next;
				device->addString(paragraphPointer, "CSS.SNMPRELO.1");
				paragraphPointer->paragraph.append(i18n(" Additionally, the attacker could cause a *ABBREV*DoS*-ABBREV* condition by causing *DEVICENAME* to reload (see section *SECTIONNO*).")); 
				device->addRelatedIssue(securityIssuePointer, "CSS.SNMPRELO.1");
			}
		}

		// Weak Community Strings...
		if (weakCommunity == true)
		{
			securityIssuePointer = device->getSecurityIssue("GEN.SNMPWEAK.1");
			if (securityIssuePointer != 0)
			{
				securityIssuePointer->impactRating++;
				paragraphPointer = securityIssuePointer->impact;
				while (paragraphPointer->next != 0)
					paragraphPointer = paragraphPointer->next;
				device->addString(paragraphPointer, "CSS.SNMPRELO.1");
				paragraphPointer->paragraph.append(i18n(" Additionally, the attacker could cause a *ABBREV*DoS*-ABBREV* condition by causing *DEVICENAME* to reload (see section *SECTIONNO*).")); 
				device->addRelatedIssue(securityIssuePointer, "CSS.SNMPRELO.1");
			}
		}

		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] SNMP System Reload\n", device->config->COL_BLUE, device->config->COL_RESET);
		
		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("*ABBREV*SNMP*-ABBREV* Reload Option Enabled"));
		securityIssuePointer->reference.assign("CSS.SNMPRELO.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addString(paragraphPointer, snmpFilterText);
		paragraphPointer->paragraph.assign(i18n("A *ABBREV*SNMP*-ABBREV* system reload facility can be configured for *DEVICETYPE* so that network administrators can remotely reset the devices. *COMPANY* determined that the *ABBREV*SNMP*-ABBREV* system reload option was enabled on *DEVICENAME*."));

		// Issue impact...
		securityIssuePointer->impactRating = 7;			// High
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("An attacker who had *ABBREV*SNMP*-ABBREV* write access could cause a *ABBREV*DoS*-ABBREV* condition by causing *DEVICENAME* to reload."));

		// Issue ease...
		securityIssuePointer->easeRating = 4;				// Moderate
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.assign(i18n("For an attacker to exploit this issue they would require *ABBREV*SNMP*-ABBREV* query tools, a community string with write access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* and the reload value. *ABBREV*SNMP*-ABBREV* query tools are available on the Internet and some *ABBREV*OS*-ABBREV* install them by default."));
		if (dictionaryCommunity == true)
		{
			securityIssuePointer->easeRating = 7;				// Easy
			device->addString(paragraphPointer, "GEN.SNMPDICT.1");
			paragraphPointer->paragraph.append(i18n(" Furthermore, the attacker could make use of a dictionary attack against the *ABBREV*SNMP*-ABBREV* service in order to gain access to a community string (see section *SECTIONNO*)."));
		}
		else if (weakCommunity == true)
		{
			securityIssuePointer->easeRating = 5;				// Moderate
			device->addString(paragraphPointer, "GEN.SNMPWEAK.1");
			paragraphPointer->paragraph.append(i18n(" Furthermore, the attacker could make use of a brute-force attack against the *ABBREV*SNMP*-ABBREV* service in order to gain access to a community string (see section *SECTIONNO*)."));
		}
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.append(i18n("The reload number is between 1 to 2*POWER*32*-POWER* and the attacker will require this value in order to reboot *DEVICENAME*. Unless the attacker is aware of what the value could be, they would have to attempt to brute-forece the value as it cannot be read from the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV*."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 3;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, unless required, the *ABBREV*SNMP*-ABBREV* reload option should be disabled. This can be done with the following command:*CODE**COMMAND*no snmp reload-enable*-COMMAND**-CODE*"));

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("*ABBREV*SNMP*-ABBREV* system reload was enabled"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Disable *ABBREV*SNMP*-ABBREV* system reload"));

		// Dependent issues...
		device->addDependency(securityIssuePointer, "GEN.SNMPCLEA.1");
		device->addDependency(securityIssuePointer, "GEN.SNMPWRIT.1");

		// Related issues...
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPDICT.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWEAK.1");
	}

	return errorCode;
}


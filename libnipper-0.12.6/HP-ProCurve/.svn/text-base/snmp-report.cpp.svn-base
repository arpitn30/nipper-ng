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


int ProCurveSNMP::generateConfigSpecificReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;
	int errorCode = 0;

	// Get Config Report Section...
	configReportPointer = device->getConfigSection("CONFIG-SNMP");

	// Get Paragraph Pointer...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-SNMP-TABLE");

	// Authentication MIB
	device->addTableData(paragraphPointer->table, i18n("Authentication *ABBREV*MIB*-ABBREV*"));
	if (authenticationMIB == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));

	return errorCode;
}


int ProCurveSNMP::generateSecuritySpecificReport(Device *device)
{
	// Variables...
	snmpCommunity *snmpCommunityPointer = 0;
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	const char *snmpAuthAccessIssue = i18n("Additionally, the attacker would have read/write access to the *DEVICETYPE* authentication *ABBREV*MIB*-ABBREV* (see section *SECTIONNO*).");
	const char *snmpManagerIssue = i18n(" With a Manager view of the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV*, an attacker would be able to extract a large quantity of configuration information from *DEVICENAME* (see section *SECTIONNO*).");
	bool managerAccess = false;
	bool managerDictionary = false;
	bool managerWeak = false;
	bool managerUnrest = false;
	bool managerUnrestDict = false;
	bool managerUnrestWeak = false;
	int errorCode = 0;

	// Searching for issues...
	snmpCommunityPointer = community;
	while (snmpCommunityPointer != 0)
	{
		if ((snmpCommunityPointer->enabled == true) && (snmpCommunityPointer->view.compare("Manager") == 0))
		{
			managerAccess = true;
			if (snmpCommunityPointer->communityInDict == true)
				managerDictionary = true;
			else if (snmpCommunityPointer->communityWeak != Device::passwordPassed)
				managerWeak = true;
			if (snmpCommunityPointer->type != communityReadOnly)
			{
				managerUnrest = true;
				if (snmpCommunityPointer->communityInDict == true)
					managerUnrestDict = true;
				else if (snmpCommunityPointer->communityWeak != Device::passwordPassed)
					managerUnrestWeak = true;
			}
		}
		snmpCommunityPointer = snmpCommunityPointer->next;
	}

	// Manager View...
	if (managerAccess == true)
	{

		// Write Access...
		securityIssuePointer = device->getSecurityIssue("GEN.SNMPWRIT.1");
		if (securityIssuePointer != 0)
		{
			securityIssuePointer->impactRating++;
			paragraphPointer = securityIssuePointer->impact;
			while (paragraphPointer->next != 0)
				paragraphPointer = paragraphPointer->next;
			device->addString(paragraphPointer, "HPP.SNMPMANA.1");
			paragraphPointer->paragraph.append(snmpManagerIssue); 
			device->addRelatedIssue(securityIssuePointer, "HPP.SNMPMANA.1");
		}

		// Clear-text SNMP...
		securityIssuePointer = device->getSecurityIssue("GEN.SNMPCLEA.1");
		if (securityIssuePointer != 0)
		{
			securityIssuePointer->impactRating++;
			paragraphPointer = securityIssuePointer->impact;
			device->addString(paragraphPointer, "HPP.SNMPMANA.1");
			paragraphPointer->paragraph.append(snmpManagerIssue); 
			device->addRelatedIssue(securityIssuePointer, "HPP.SNMPMANA.1");
		}

		// Dictionary-based Community Strings...
		if (managerUnrestDict == true)
		{
			securityIssuePointer = device->getSecurityIssue("GEN.SNMPDICT.1");
			if (securityIssuePointer != 0)
			{
				securityIssuePointer->impactRating++;
				paragraphPointer = securityIssuePointer->impact;
				while (paragraphPointer->next != 0)
					paragraphPointer = paragraphPointer->next;
				device->addString(paragraphPointer, "HPP.SNMPMANA.1");
				paragraphPointer->paragraph.append(snmpManagerIssue); 
				device->addRelatedIssue(securityIssuePointer, "HPP.SNMPMANA.1");
			}
		}

		// Weak Community Strings...
		if (managerUnrestWeak == true)
		{
			securityIssuePointer = device->getSecurityIssue("GEN.SNMPWEAK.1");
			if (securityIssuePointer != 0)
			{
				securityIssuePointer->impactRating++;
				paragraphPointer = securityIssuePointer->impact;
				while (paragraphPointer->next != 0)
					paragraphPointer = paragraphPointer->next;
				device->addString(paragraphPointer, "HPP.SNMPMANA.1");
				paragraphPointer->paragraph.append(snmpManagerIssue); 
				device->addRelatedIssue(securityIssuePointer, "HPP.SNMPMANA.1");
			}
		}

		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] SNMP Manager Access\n", device->config->COL_BLUE, device->config->COL_RESET);
		
		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("*ABBREV*SNMP*-ABBREV* Access To All *ABBREV*MIB*-ABBREV* Objects"));
		securityIssuePointer->reference.assign("HPP.SNMPMANA.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* community strings can be configured with either a Manager or Operator view of the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV*. A community string with a Manager view can access all *ABBREV*MIB*-ABBREV* objects, while a community string with a Operator view can access all *ABBREV*MIB*-ABBREV* objects except the configuration *ABBREV*MIB*-ABBREV*."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that a Manager view of the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* was configured on *DEVICENAME*."));

		// Issue impact...
		securityIssuePointer->impactRating = 6;			// Medium
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("An attacker who has *ABBREV*SNMP*-ABBREV* access to the *DEVICETYPE* using a community string with a Manager view of the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* could extract a large quantity of configuration information from *DEVICENAME*."));
		if (managerUnrest == true)
		{
			securityIssuePointer->impactRating = 7;			// High
			paragraphPointer->paragraph.append(i18n(" With write *ABBREV*SNMP*-ABBREV* access to *DEVICENAME*, an attacker could modify the devices configuration."));
			if (authenticationMIB == true)
			{
				securityIssuePointer->impactRating = 8;			// High
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
				device->addString(paragraphPointer, "HPP.SNMPAUTH.1");
				paragraphPointer->paragraph.append(i18n("Additionally, the attacker could access and modify the authentication information stored on *DEVICENAME* (see section *SECTIONNO*)."));
			}
		}

		// Issue ease...
		securityIssuePointer->easeRating = 4;				// Moderate
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.assign(i18n("For an attacker to exploit this issue they would require *ABBREV*SNMP*-ABBREV* query tools, a community string with a Manager view of the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV*. *ABBREV*SNMP*-ABBREV* query tools are available on the Internet and some *ABBREV*OS*-ABBREV* install them by default."));
		if (managerDictionary == true)
		{
			securityIssuePointer->easeRating = 8;				// Easy
			device->addString(paragraphPointer, "GEN.SNMPDICT.1");
			paragraphPointer->paragraph.append(i18n(" Furthermore, the attacker could make use of a dictionary attack against the *ABBREV*SNMP*-ABBREV* service in order to gain access to a community string (see section *SECTIONNO*)."));
		}
		else if (managerWeak == true)
		{
			securityIssuePointer->easeRating = 6;				// Easy
			device->addString(paragraphPointer, "GEN.SNMPWEAK.1");
			paragraphPointer->paragraph.append(i18n(" Furthermore, the attacker could make use of a brute-force attack against the *ABBREV*SNMP*-ABBREV* service in order to gain access to a community string (see section *SECTIONNO*)."));
		}

		// Issue recommendation...
		securityIssuePointer->fixRating = 2;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, unless required, access to the configuration *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* should be disabled. This can be done with the following command:*CODE**COMMAND*snmp-server community *CMDUSER*community-string*-CMDUSER* operator *CMDOPTION*restricted *CMDOR* unrestricted*-CMDOPTION**-COMMAND**-CODE*"));

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("access to configuration information was possible using *ABBREV*SNMP*-ABBREV*"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Disable access to configuration information using *ABBREV*SNMP*-ABBREV*"));

		// Dependent issues...
		device->addDependency(securityIssuePointer, "GEN.SNMPCLEA.1");

		// Related issues...
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPDICT.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWEAK.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWRIT.1");
		device->addRelatedIssue(securityIssuePointer, "HPP.SNMPAUTH.1");
	}

	// Authentication MIB...
	if ((managerUnrest == true) && (authenticationMIB == true))
	{

		// Write Access...
		securityIssuePointer = device->getSecurityIssue("GEN.SNMPWRIT.1");
		if (securityIssuePointer != 0)
		{
			securityIssuePointer->impactRating++;
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			device->addString(paragraphPointer, "HPP.SNMPAUTH.1");
			paragraphPointer->paragraph.assign(snmpAuthAccessIssue); 
			device->addRelatedIssue(securityIssuePointer, "HPP.SNMPAUTH.1");
		}

		// Clear-text SNMP...
		securityIssuePointer = device->getSecurityIssue("GEN.SNMPCLEA.1");
		if (securityIssuePointer != 0)
		{
			securityIssuePointer->impactRating++;
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			device->addString(paragraphPointer, "HPP.SNMPAUTH.1");
			paragraphPointer->paragraph.assign(snmpAuthAccessIssue);  
			device->addRelatedIssue(securityIssuePointer, "HPP.SNMPAUTH.1");
		}

		// Dictionary-based Community Strings...
		if (managerUnrestDict == true)
		{
			securityIssuePointer = device->getSecurityIssue("GEN.SNMPDICT.1");
			if (securityIssuePointer != 0)
			{
				securityIssuePointer->impactRating++;
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
				device->addString(paragraphPointer, "HPP.SNMPAUTH.1");
				paragraphPointer->paragraph.assign(snmpAuthAccessIssue);  
				device->addRelatedIssue(securityIssuePointer, "HPP.SNMPAUTH.1");
			}
		}

		// Weak Community Strings...
		if (managerUnrestWeak == true)
		{
			securityIssuePointer = device->getSecurityIssue("GEN.SNMPWEAK.1");
			if (securityIssuePointer != 0)
			{
				securityIssuePointer->impactRating++;
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
				device->addString(paragraphPointer, "HPP.SNMPAUTH.1");
				paragraphPointer->paragraph.assign(snmpAuthAccessIssue); 
				device->addRelatedIssue(securityIssuePointer, "HPP.SNMPAUTH.1");
			}
		}

		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] SNMP Authentication MIB Access\n", device->config->COL_BLUE, device->config->COL_RESET);
		
		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("*ABBREV*SNMP*-ABBREV* Access To The Authentication *ABBREV*MIB*-ABBREV*"));
		securityIssuePointer->reference.assign("HPP.SNMPAUTH.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addString(paragraphPointer, snmpFilterText);
		paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices can be configured to allow access to authentication information using *ABBREV*SNMP*-ABBREV*. *COMPANY* determined that the access to the authentication information in the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* was allowed on *DEVICENAME*."));

		// Issue impact...
		securityIssuePointer->impactRating = 8;			// High
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("An attacker who has *ABBREV*SNMP*-ABBREV* access to the *DEVICETYPE* authentication *ABBREV*MIB*-ABBREV* could extract authentication details, and with write access they could modify the authentication information."));

		// Issue ease...
		securityIssuePointer->easeRating = 4;				// Moderate
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.assign(i18n("For an attacker to exploit this issue they would require *ABBREV*SNMP*-ABBREV* query tools, a community string in the Manager group. *ABBREV*SNMP*-ABBREV* query tools are available on the Internet and some *ABBREV*OS*-ABBREV* install them by default."));
		if (managerUnrestDict == true)
		{
			securityIssuePointer->easeRating = 8;				// Easy
			device->addString(paragraphPointer, "GEN.SNMPDICT.1");
			paragraphPointer->paragraph.append(i18n(" Furthermore, the attacker could make use of a dictionary attack against the *ABBREV*SNMP*-ABBREV* service in order to gain access to a community string (see section *SECTIONNO*)."));
		}
		else if (managerUnrestWeak == true)
		{
			securityIssuePointer->easeRating = 6;				// Easy
			device->addString(paragraphPointer, "GEN.SNMPWEAK.1");
			paragraphPointer->paragraph.append(i18n(" Furthermore, the attacker could make use of a brute-force attack against the *ABBREV*SNMP*-ABBREV* service in order to gain access to a community string (see section *SECTIONNO*)."));
		}

		// Issue recommendation...
		securityIssuePointer->fixRating = 2;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, unless required, access to the authentication information using *ABBREV*SNMP*-ABBREV* should be disabled. This can be done with the following command:*CODE**COMMAND*snmp-server mib hpSwitchAuthMIB excluded*-COMMAND**-CODE*"));

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("access to authentication information was possible using *ABBREV*SNMP*-ABBREV*"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Disable access to authentication information using *ABBREV*SNMP*-ABBREV*"));

		// Dependent issues...
		device->addDependency(securityIssuePointer, "GEN.SNMPCLEA.1");
		device->addDependency(securityIssuePointer, "GEN.SNMPWRIT.1");
		device->addDependency(securityIssuePointer, "HPP.SNMPMANA.1");

		// Related issues...
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPDICT.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWEAK.1");
	}

	return errorCode;
}

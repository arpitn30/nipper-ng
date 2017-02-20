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
#include "iosdevice.h"
#include "general.h"
#include "snmp.h"


int IOSSNMP::generateConfigSpecificReport(Device *device)
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

	// System Shutdown...
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*SNMP*-ABBREV* System Shutdown"));
	if (systemShutdown == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));

	// SNMP Server Manager...
	if (device->general != 0)
	{
		if ((device->general->versionMajor > 11) || ((device->general->versionMajor == 11) && (device->general->versionMinor > 2)) || (device->general->versionMajor == 0))
		{
			device->addTableData(paragraphPointer->table, i18n("Manager"));
			if (managerEnabled == true)
			{
				device->addTableData(paragraphPointer->table, i18n("Enabled"));
				device->addTableData(paragraphPointer->table, i18n("Manager Session Timeout"));
				tempString.assign(device->intToString(managerTimeout));
				device->addTableData(paragraphPointer->table, tempString.c_str());
			}
			else
				device->addTableData(paragraphPointer->table, i18n("Disabled"));
		}
	}

	// TFTP Server List ACL...
	if (!tftpServerList.empty())
	{
		device->addTableData(paragraphPointer->table, i18n("*ABBREV*TFTP*-ABBREV* Server List *ABBREV*ACL*-ABBREV*"));
		device->addTableData(paragraphPointer->table, tftpServerList.c_str());
	}

	// Trap Source Interface...
	if (!trapSource.empty())
	{
		device->addTableData(paragraphPointer->table, i18n("Trap Source Interface"));
		device->addTableData(paragraphPointer->table, trapSource.c_str());
	}

	// Trap Queue Length...
	device->addTableData(paragraphPointer->table, i18n("Maximum Trap Queue Length"));
	tempString.assign(device->intToString(trapQueueLength));
	device->addTableData(paragraphPointer->table, tempString.c_str());

	// Trap Timeout...
	device->addTableData(paragraphPointer->table, i18n("Trap Timeout"));
	tempString.assign(device->intToString(trapTimeout));
	tempString.append(i18n(" seconds"));
	device->addTableData(paragraphPointer->table, tempString.c_str());

	// Packet Size...
	device->addTableData(paragraphPointer->table, i18n("Maximum Packet Size"));
	tempString.assign(device->intToString(packetSize));
	tempString.append(i18n(" bytes"));
	device->addTableData(paragraphPointer->table, tempString.c_str());

	return errorCode;
}


int IOSSNMP::generateSecuritySpecificReport(Device *device)
{
	// Variables...
	snmpCommunity *snmpCommunityPointer = 0;
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	bool dictionaryCommunity = false;
	bool weakCommunity = false;
	bool writeAccess = false;
	bool noCommunityFilter = false;
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
			if ((communityFilter == true) && (snmpCommunityPointer->filter.empty()))
				noCommunityFilter = true;
		}
		snmpCommunityPointer = snmpCommunityPointer->next;
	}

	// System Shutdown via SNMP...
	if ((systemShutdown == true) && (writeAccess == true))
	{

		// Write Access...
		securityIssuePointer = device->getSecurityIssue("GEN.SNMPWRIT.1");
		if (securityIssuePointer != 0)
		{
			securityIssuePointer->impactRating++;
			paragraphPointer = securityIssuePointer->impact;
			while (paragraphPointer->next != 0)
				paragraphPointer = paragraphPointer->next;
			device->addString(paragraphPointer, "IOS.SNMPSHUT.1");
			paragraphPointer->paragraph.append(i18n(" Additionally, the attacker could cause a *ABBREV*DoS*-ABBREV* condition by causing *DEVICENAME* to reload (see section *SECTIONNO*).")); 
			device->addRelatedIssue(securityIssuePointer, "IOS.SNMPSHUT.1");
		}

		// Clear-text SNMP...
		securityIssuePointer = device->getSecurityIssue("GEN.SNMPCLEA.1");
		if (securityIssuePointer != 0)
		{
			securityIssuePointer->impactRating++;
			paragraphPointer = securityIssuePointer->impact;
			device->addString(paragraphPointer, "IOS.SNMPSHUT.1");
			paragraphPointer->paragraph.append(i18n(" Additionally, the attacker could cause a *ABBREV*DoS*-ABBREV* condition by causing *DEVICENAME* to reload (see section *SECTIONNO*).")); 
			device->addRelatedIssue(securityIssuePointer, "IOS.SNMPSHUT.1");
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
				device->addString(paragraphPointer, "IOS.SNMPSHUT.1");
				paragraphPointer->paragraph.append(i18n(" Additionally, the attacker could cause a *ABBREV*DoS*-ABBREV* condition by causing *DEVICENAME* to reload (see section *SECTIONNO*).")); 
				device->addRelatedIssue(securityIssuePointer, "IOS.SNMPSHUT.1");
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
				device->addString(paragraphPointer, "IOS.SNMPSHUT.1");
				paragraphPointer->paragraph.append(i18n(" Additionally, the attacker could cause a *ABBREV*DoS*-ABBREV* condition by causing *DEVICENAME* to reload (see section *SECTIONNO*).")); 
				device->addRelatedIssue(securityIssuePointer, "IOS.SNMPSHUT.1");
			}
		}

		// No Filtering...
		if (noCommunityFilter == true)
		{
			securityIssuePointer = device->getSecurityIssue("GEN.SNMPFILT.1");
			if (securityIssuePointer != 0)
			{
				securityIssuePointer->impactRating++;
				paragraphPointer = securityIssuePointer->impact;
				device->addString(paragraphPointer, "IOS.SNMPSHUT.1");
				paragraphPointer->paragraph.append(i18n(" Additionally, the attacker could cause a *ABBREV*DoS*-ABBREV* condition by causing *DEVICENAME* to reload (see section *SECTIONNO*).")); 
				device->addRelatedIssue(securityIssuePointer, "IOS.SNMPSHUT.1");
			}
		}

		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] SNMP Shutdown Configured\n", device->config->COL_BLUE, device->config->COL_RESET);
		
		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("*ABBREV*SNMP*-ABBREV* System Shutdown Enabled"));
		securityIssuePointer->reference.assign("IOS.SNMPSHUT.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addString(paragraphPointer, snmpFilterText);
		paragraphPointer->paragraph.assign(i18n("A *ABBREV*SNMP*-ABBREV* system shutdown facility can be configured for *DEVICETYPE* so that network administrators can remotely reset the devices. *COMPANY* determined that the *ABBREV*SNMP*-ABBREV* system shutdown option was enabled on *DEVICENAME*."));

		// Issue impact...
		securityIssuePointer->impactRating = 8;			// High
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("An attacker who had *ABBREV*SNMP*-ABBREV* write access could cause a *ABBREV*DoS*-ABBREV* condition by causing *DEVICENAME* to reload."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.assign(i18n("For an attacker to exploit this issue they would require *ABBREV*SNMP*-ABBREV* query tools and a community string with write access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV*. *ABBREV*SNMP*-ABBREV* query tools are available on the Internet and some *ABBREV*OS*-ABBREV* install them by default."));
		if (dictionaryCommunity == true)
		{
			securityIssuePointer->easeRating = 8;				// Easy
			device->addString(paragraphPointer, "GEN.SNMPDICT.1");
			paragraphPointer->paragraph.append(i18n(" Furthermore, the attacker could make use of a dictionary attack against the *ABBREV*SNMP*-ABBREV* service in order to gain access to a community string (see section *SECTIONNO*)."));
		}
		else if (weakCommunity == true)
		{
			securityIssuePointer->easeRating = 5;				// Moderate
			device->addString(paragraphPointer, "GEN.SNMPWEAK.1");
			paragraphPointer->paragraph.append(i18n(" Furthermore, the attacker could make use of a brute-force attack against the *ABBREV*SNMP*-ABBREV* service in order to gain access to a community string (see section *SECTIONNO*)."));
		}
		if (noCommunityFilter == true)
		{
			device->addString(paragraphPointer, "GEN.SNMPFILT.1");
			paragraphPointer->paragraph.append(i18n(" *ABBREV*ACL*-ABBREV* were not fully configured to restrict access to specific *ABBREV*NMS*-ABBREV* or *ABBREV*SNMP*-ABBREV* management hosts (see section *SECTIONNO*)."));
		}
		else
		{
			securityIssuePointer->easeRating = 2;				// Challenging
			paragraphPointer->paragraph.append(i18n(" Although *ABBREV*ACL*-ABBREV* were configured to restrict *ABBREV*SNMP*-ABBREV* access from specific host, although a skilled attacker may be able to bypass any host-based access restrictions."));
		}

		// Issue recommendation...
		securityIssuePointer->fixRating = 3;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("Generally the *ABBREV*SNMP*-ABBREV* system shutdown is not saved to the *DEVICETYPE* configuration file. *COMPANY* recommends that the *ABBREV*SNMP*-ABBREV* system shutdown facility should be disabled. This can be done with the following command:*CODE**COMMAND*no snmp-server system-shutdown*-COMMAND**-CODE*"));

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("*ABBREV*SNMP*-ABBREV* system shutdown was enabled"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Disable *ABBREV*SNMP*-ABBREV* system shutdown"));

		// Dependent issues...
		device->addDependency(securityIssuePointer, "GEN.SNMPCLEA.1");
		device->addDependency(securityIssuePointer, "GEN.SNMPWRIT.1");

		// Related issues...
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPDICT.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWEAK.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPFILT.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWEFI.1");
	}

	if ((tftpServerList.empty()) && (writeAccess == true))
	{
		// Write Access...
		securityIssuePointer = device->getSecurityIssue("GEN.SNMPWRIT.1");
		if (securityIssuePointer != 0)
		{
			securityIssuePointer->impactRating++;
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			device->addString(paragraphPointer, "IOS.SNMPTFTP.1");
			paragraphPointer->paragraph.append(i18n("On *DEVICETYPE*, an attacker with write access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* could remotely obtain a copy of the *DEVICENAME* configuration using *ABBREV*TFTP*-ABBREV* (see section *SECTIONNO*).")); 
			device->addRelatedIssue(securityIssuePointer, "IOS.SNMPTFTP.1");
		}

		// Clear-text SNMP...
		securityIssuePointer = device->getSecurityIssue("GEN.SNMPCLEA.1");
		if (securityIssuePointer != 0)
		{
			securityIssuePointer->impactRating++;
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			device->addString(paragraphPointer, "IOS.SNMPTFTP.1");
			paragraphPointer->paragraph.append(i18n("On *DEVICETYPE*, an attacker with write access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* could remotely obtain a copy of the *DEVICENAME* configuration using *ABBREV*TFTP*-ABBREV* (see section *SECTIONNO*).")); 
			device->addRelatedIssue(securityIssuePointer, "IOS.SNMPTFTP.1");
		}

		// Dictionary-based Community Strings...
		if (dictionaryCommunity == true)
		{
			securityIssuePointer = device->getSecurityIssue("GEN.SNMPDICT.1");
			if (securityIssuePointer != 0)
			{
				securityIssuePointer->impactRating++;
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
				device->addString(paragraphPointer, "IOS.SNMPTFTP.1");
				paragraphPointer->paragraph.append(i18n("On *DEVICETYPE*, an attacker with write access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* could remotely obtain a copy of the *DEVICENAME* configuration using *ABBREV*TFTP*-ABBREV* (see section *SECTIONNO*).")); 
				device->addRelatedIssue(securityIssuePointer, "IOS.SNMPTFTP.1");
			}
		}

		// Weak Community Strings...
		if (weakCommunity == true)
		{
			securityIssuePointer = device->getSecurityIssue("GEN.SNMPWEAK.1");
			if (securityIssuePointer != 0)
			{
				securityIssuePointer->impactRating++;
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
				device->addString(paragraphPointer, "IOS.SNMPTFTP.1");
				paragraphPointer->paragraph.append(i18n("On *DEVICETYPE*, an attacker with write access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* could remotely obtain a copy of the *DEVICENAME* configuration using *ABBREV*TFTP*-ABBREV* (see section *SECTIONNO*).")); 
				device->addRelatedIssue(securityIssuePointer, "IOS.SNMPTFTP.1");
			}
		}

		// No Filtering...
		if (noCommunityFilter == true)
		{
			if (securityIssuePointer != 0)
			{
				securityIssuePointer->impactRating++;
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
				device->addString(paragraphPointer, "IOS.SNMPTFTP.1");
				paragraphPointer->paragraph.append(i18n("On *DEVICETYPE*, an attacker with write access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* could remotely obtain a copy of the *DEVICENAME* configuration using *ABBREV*TFTP*-ABBREV* (see section *SECTIONNO*).")); 
				device->addRelatedIssue(securityIssuePointer, "IOS.SNMPTFTP.1");
			}
		}

		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] SNMP TFTP Server List ACL\n", device->config->COL_BLUE, device->config->COL_RESET);
		
		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("No *ABBREV*SNMP*-ABBREV* *ABBREV*TFTP*-ABBREV* Server List *ABBREV*ACL*-ABBREV* Configured"));
		securityIssuePointer->reference.assign("IOS.SNMPTFTP.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("Using *ABBREV*SNMP*-ABBREV*, a *DEVICETYPE* can be instructed to save its configuration to a file on a *ABBREV*TFTP*-ABBREV* server. This feature enables network administrators and management software to quickly obtain a copy of the *DEVICETYPE* configuration. An *ABBREV*ACL*-ABBREV* can be configured on *DEVICETYPE* from *ABBREV*IOS*-ABBREV* version 10.2 to help secure access to this functionality."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that no *ABBREV*TFTP*-ABBREV* server *ABBREV*ACL*-ABBREV* had been configured on *DEVICENAME*."));

		// Issue impact...
		securityIssuePointer->impactRating = 6;			// Medium
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("An attacker who had *ABBREV*SNMP*-ABBREV* write access could remotely obtain the *DEVICENAME* configuration. The configuration would include any passwords for *DEVICENAME*."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.assign(i18n("For an attacker to exploit this issue they would require *ABBREV*SNMP*-ABBREV* query tools, a *ABBREV*TFTP*-ABBREV* server and a community string with write access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV*. *ABBREV*SNMP*-ABBREV* query tools and *ABBREV*TFTP*-ABBREV* server software are available on the Internet and some *ABBREV*OS*-ABBREV* install them by default."));
		if (dictionaryCommunity == true)
		{
			securityIssuePointer->easeRating = 5;				// Moderate
			device->addString(paragraphPointer, "GEN.SNMPDICT.1");
			paragraphPointer->paragraph.append(i18n(" Furthermore, the attacker could make use of a dictionary attack against the *ABBREV*SNMP*-ABBREV* service in order to gain access to a community string (see section *SECTIONNO*)."));
		}
		else if (weakCommunity == true)
		{
			securityIssuePointer->easeRating = 3;				// Moderate
			device->addString(paragraphPointer, "GEN.SNMPWEAK.1");
			paragraphPointer->paragraph.append(i18n(" Furthermore, the attacker could make use of a brute-force attack against the *ABBREV*SNMP*-ABBREV* service in order to gain access to a community string (see section *SECTIONNO*)."));
		}
		if (noCommunityFilter == true)
		{
			device->addString(paragraphPointer, "GEN.SNMPFILT.1");
			paragraphPointer->paragraph.append(i18n(" *ABBREV*ACL*-ABBREV* were not fully configured to restrict access to specific *ABBREV*NMS*-ABBREV* or *ABBREV*SNMP*-ABBREV* management hosts (see section *SECTIONNO*)."));
		}
		else
		{
			securityIssuePointer->easeRating = 2;				// Challenging
			paragraphPointer->paragraph.append(i18n(" Although *ABBREV*ACL*-ABBREV* were configured to restrict *ABBREV*SNMP*-ABBREV* access from specific host, although a skilled attacker may be able to bypass any host-based access restrictions."));
		}

		// Issue recommendation...
		securityIssuePointer->fixRating = 2;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that a *ABBREV*SNMP*-ABBREV* *ABBREV*TFTP*-ABBREV* server list *ABBREV*ACL*-ABBREV* should be configured to ensure that configurations are only saved to specific hosts."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("The following example configures *ABBREV*ACL*-ABBREV* number 20 for use as a *ABBREV*SNMP*-ABBREV* *ABBREV*TFTP*-ABBREV* server list and gives access to a single host with logging.*CODE**COMMAND*access-list 20 permit 192.168.0.50 255.255.255.255 log*-COMMAND**COMMAND*access-list 20 deny any log*-COMMAND**-CODE*"));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("The *ABBREV*ACL*-ABBREV* can then be assigned as the *ABBREV*SNMP*-ABBREV* *ABBREV*TFTP*-ABBREV* server list with the following command:*CODE**COMMAND*snmp-server tftp-server-list 20*-COMMAND**-CODE*"));

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("a *ABBREV*SNMP*-ABBREV* *ABBREV*TFTP*-ABBREV* server list was not configured"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Configure a *ABBREV*SNMP*-ABBREV* *ABBREV*TFTP*-ABBREV* server list"));

		// Dependent issues...
		device->addDependency(securityIssuePointer, "GEN.SNMPCLEA.1");
		device->addDependency(securityIssuePointer, "GEN.SNMPWRIT.1");

		// Related issues...
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPDICT.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWEAK.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPFILT.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWEFI.1");
	}

	return errorCode;
}



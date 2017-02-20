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
#include <cstring>

#include "../../globaldefs.h"
#include "../device.h"
#include "snmp.h"

int SNMP::snmpWriteAccess(Device *device, int writeCount)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	snmpCommunity *snmpCommunityPointer = 0;
	bool ipv6 = false;
	bool writeAll = false;
	bool filtering = true;
	bool inDict = false;
	bool weak = false;
	bool found = true;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] SNMP Write Access\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("*ABBREV*SNMP*-ABBREV* Write Access Was Enabled"));
	securityIssuePointer->reference.assign("GEN.SNMPWRIT.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*ABBREV*SNMP*-ABBREV* is used for the remote monitoring and management of a variety of network devices. Access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* with protocol versions 1 and 2 is restricted using a community string. Whilst read access enables a remote user to read information from the *DEVICENAME* *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV*, write access enables *DEVICENAME* to be configured remotely."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

	// Multiple found...
	if (writeCount > 1)
	{
		snmpCommunityPointer = community;
		while (snmpCommunityPointer != 0)
		{
			if ((snmpCommunityPointer->enabled == true) && (((communityRequiresHosts == true) && (hostCommunityExists(snmpCommunityPointer->community.c_str()) == true)) || (communityRequiresHosts == false)))
			{
				if (snmpCommunityPointer->type != communityReadOnly)
				{
					if ((!snmpCommunityPointer->ipv6Filter.empty()) && (communityIPv6Filter == true))
						ipv6 = true;
					if ((communityView == true) && (snmpCommunityPointer->view.empty()))
						found = false;
					if ((communityFilter == true) && (snmpCommunityPointer->filter.empty()))
						filtering = false;
					if (snmpCommunityPointer->communityInDict == true)
						inDict = true;
					if (snmpCommunityPointer->communityWeak != Device::passwordPassed)
						weak = true;
				}
				if (snmpCommunityPointer->type == communityReadWriteAll)
					writeAll = true;
			}
			snmpCommunityPointer = snmpCommunityPointer->next;
		}

		device->addValue(paragraphPointer, writeCount);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *NUMBER* community strings listed in Table *TABLEREF* allowed write access to the *DEVICENAME* *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV*."));
		errorCode = device->addTable(paragraphPointer, "GEN-SNMPWRIT-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("*ABBREV*SNMP*-ABBREV* community strings with write access");

		device->addTableHeading(paragraphPointer->table, i18n("Type"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Community"), true);
		if (writeAll == true)
			device->addTableHeading(paragraphPointer->table, i18n("Access"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Version"), false);
		if (communityView == true)
			device->addTableHeading(paragraphPointer->table, i18n("View"), false);
		if (communityFilter == true)
			device->addTableHeading(paragraphPointer->table, snmpFilterText, false);
		if (ipv6 == true)
			device->addTableHeading(paragraphPointer->table, snmpFilterIPv6Text, false);

		snmpCommunityPointer = community;
		while (snmpCommunityPointer != 0)
		{
			if ((snmpCommunityPointer->enabled == true) && (((communityRequiresHosts == true) && (hostCommunityExists(snmpCommunityPointer->community.c_str()) == true)) || (communityRequiresHosts == false)))
			{
				if (snmpCommunityPointer->type != communityReadOnly)
				{
					device->addTableData(paragraphPointer->table, i18n("Community"));
					device->addTableData(paragraphPointer->table, snmpCommunityPointer->community.c_str());
					if (writeAll == true)
					{
						switch (snmpCommunityPointer->type)
						{
							case communityReadOnly:
								device->addTableData(paragraphPointer->table, i18n("Read Only"));
								break;
							case communityReadWrite:
								device->addTableData(paragraphPointer->table, i18n("Read/Write"));
								break;
							default:
								device->addTableData(paragraphPointer->table, i18n("Read/Write All"));
								break;
						}
					}
					switch (snmpCommunityPointer->version)
					{
						case 1:
							device->addTableData(paragraphPointer->table, i18n("1"));
							break;
						case 2:
							device->addTableData(paragraphPointer->table, i18n("2c"));
							break;
						case 3:
							device->addTableData(paragraphPointer->table, i18n("3"));
							break;
						default:
							device->addTableData(paragraphPointer->table, i18n("1 and 2c"));
							break;
					}
					if (communityView == true)
					{
						if (!snmpCommunityPointer->view.empty())
							device->addTableData(paragraphPointer->table, snmpCommunityPointer->view.c_str());
						else
							device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
					}
					if (communityFilter == true)
					{
						if (!snmpCommunityPointer->filter.empty())
							device->addTableData(paragraphPointer->table, snmpCommunityPointer->filter.c_str());
						else
							device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
					}
					if (ipv6 == true)
					{
						if (!snmpCommunityPointer->ipv6Filter.empty())
							device->addTableData(paragraphPointer->table, snmpCommunityPointer->ipv6Filter.c_str());
						else
							device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
					}
				}
			}
			snmpCommunityPointer = snmpCommunityPointer->next;
		}
	}

	// One found...
	else
	{
		snmpCommunityPointer = community;
		while (snmpCommunityPointer != 0)
		{
			if ((snmpCommunityPointer->enabled == true) && (((communityRequiresHosts == true) && (hostCommunityExists(snmpCommunityPointer->community.c_str()) == true)) || (communityRequiresHosts == false)))
			{
				if (snmpCommunityPointer->type != communityReadOnly)
				{
					paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that write access to the *DEVICENAME* *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* was configured."));
					if ((communityView == true) && (snmpCommunityPointer->view.empty()))
						found = false;
					if ((communityFilter == true) && (snmpCommunityPointer->filter.empty()))
						filtering = false;
					if (snmpCommunityPointer->communityInDict == true)
						inDict = true;
					if (snmpCommunityPointer->communityWeak != Device::passwordPassed)
						weak = true;
				}
			}
			snmpCommunityPointer = snmpCommunityPointer->next;
		}
	}

	// Issue impact...
	securityIssuePointer->impactRating = 7;		// High
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("An attacker with write access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* could modify the configuration of *DEVICENAME*."));
	if ((found == true) && (communityView == true))
	{
		paragraphPointer->paragraph.append(i18n(" However, write access to the *DEVICENAME* *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* was restricted with the configuration of views."));
		securityIssuePointer->impactRating = 5;		// Medium
	}

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 3;				// Moderate
	paragraphPointer->paragraph.assign(i18n("An attacker who wanted to modify the configuration of *DEVICENAME* using *ABBREV*SNMP*-ABBREV* would require a tool that could write to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* and a community string with write access. *ABBREV*SNMP*-ABBREV* tools that can write to a *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* are available on the Internet and some *ABBREV*OS*-ABBREV* install them by default."));
	if (inDict == true)
	{
		securityIssuePointer->easeRating = 8;				// Easy
		device->addString(paragraphPointer, "GEN.SNMPDICT.1");
		paragraphPointer->paragraph.append(i18n(" The attacker could make use of a dictionary attack against the *ABBREV*SNMP*-ABBREV* service in order to gain access to a community string with write access (see section *SECTIONNO*)."));
	}
	else if (weak == true)
	{
		securityIssuePointer->easeRating = 4;				// Moderate
		device->addString(paragraphPointer, "GEN.SNMPWEAK.1");
		paragraphPointer->paragraph.append(i18n(" The attacker could make use of a brute-force attack against the *ABBREV*SNMP*-ABBREV* service in order to gain access to a community string with write access (see section *SECTIONNO*)."));
	}
	if ((communityFilter == true) && (filtering == false))
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		errorCode = device->addString(paragraphPointer, snmpFilterText);
		if (errorCode != 0)
			return errorCode;
		securityIssuePointer->easeRating = 2;			// Challenging
		paragraphPointer->paragraph.assign(i18n("*DATA* help to restrict *ABBREV*SNMP*-ABBREV* access from unauthorised network hosts. However, a skilled attacker may be able bypass any configured network filtering."));
	}

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if not required, *ABBREV*SNMP*-ABBREV* should be disabled."));
	if (supportSNMP3 == true)
		paragraphPointer->paragraph.append(i18n(" However if *ABBREV*SNMP*-ABBREV* is required, *COMPANY* recommends that only *ABBREV*SNMP*-ABBREV* version 3 should be configured."));
	else if (supportSNMP3Upgrade == true)
	{
		paragraphPointer->paragraph.append(i18n(" However if *ABBREV*SNMP*-ABBREV* is required, *COMPANY* recommends that *DEVICETYPE* *ABBREV*OS*-ABBREV* should be upgraded and that only support for *ABBREV*SNMP*-ABBREV* version 3 is configured. "));
		paragraphPointer->paragraph.append(supportSNMP3UpgText);
		securityIssuePointer->fixRating = 8;			// Involved
	}
	else
		paragraphPointer->paragraph.append(i18n(" It is not possible to configure support for *ABBREV*SNMP*-ABBREV* version 3 on *DEVICETYPE* devices."));
	paragraphPointer->paragraph.append(i18n(" If read only access using community strings is required, *COMPANY* recommends that read only community string access should be configured."));
	if (strlen(disableSNMPCmdText) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(disableSNMPCmdText);
	}
	if ((supportSNMP3 == true) && (strlen(configSNMP3Text) > 0))
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configSNMP3Text);
	}
	if (strlen(configSNMPReadOnlyText) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configSNMPReadOnlyText);
	}
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("It is worth noting that *ABBREV*SNMP*-ABBREV* community string authentication is not encrypted. Therefore *COMPANY* recommends that any configured community strings should not be similar to the authentication password for any other system or service."));

	// Conclusions text...
	securityIssuePointer->conLine.append(i18n("*ABBREV*SNMP*-ABBREV* write access was enabled"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Replace all write access community strings with read only community strings."));

	// Dependent issues...
	device->addDependency(securityIssuePointer, "GEN.SNMPCLEA.1");

	// Related issues...
	if (inDict == true)
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPDICT.1");
	else if (weak == true)
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWEAK.1");
	if ((communityFilter == true) && (filtering == false))
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPFILT.1");
	if ((found == false) && (communityView == true))
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPVIEW.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWEFI.1");

	return errorCode;
}


int SNMP::snmpWithoutFiltering(Device *device, int filterCount, int nmsFilterCount)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	snmpCommunity *snmpCommunityPointer = 0;
	snmpHostStruct *snmpHostPointer = 0;
	string tempString;
	string issueString;
	bool writeAll = false;
	bool inDict = false;
	bool weak = false;
	bool viewUsed = true;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] SNMP With No Filtering\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("*ABBREV*SNMP*-ABBREV* Access Without Network Filtering"));
	securityIssuePointer->reference.assign("GEN.SNMPFILT.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	device->addString(paragraphPointer, snmpFilterText);
	paragraphPointer->paragraph.assign(i18n("*ABBREV*SNMP*-ABBREV* is used for the remote monitoring and management of a variety of network devices. *DATA* can be configured to restrict access to the *ABBREV*SNMP*-ABBREV* service from specific *ABBREV*NMS*-ABBREV* or *ABBREV*SNMP*-ABBREV* management hosts"));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

	// Multiple found...
	if (filterCount + nmsFilterCount > 1)
	{
		snmpCommunityPointer = community;
		while (snmpCommunityPointer != 0)
		{
			if ((snmpCommunityPointer->enabled == true) && (((communityRequiresHosts == true) && (hostCommunityExists(snmpCommunityPointer->community.c_str()) == true)) || (communityRequiresHosts == false)))
			{
				if (snmpCommunityPointer->filter.empty())
				{
					if ((communityView == true) && (snmpCommunityPointer->view.empty()))
						viewUsed = false;
					if (snmpCommunityPointer->communityInDict == true)
						inDict = true;
					if (snmpCommunityPointer->communityWeak != Device::passwordPassed)
						weak = true;
					if (snmpCommunityPointer->type != communityReadOnly)
						writeAll = true;
				}
			}
			snmpCommunityPointer = snmpCommunityPointer->next;
		}
		if ((communityRequiresHosts == false) && (hostShowCommunity == true) && (nmsFilterCount > 0))
		{
			snmpHostPointer = snmpHost;
			while (snmpHostPointer != 0)
			{
				if (snmpHostPointer->filter.empty())
				{
					if (snmpHostPointer->communityInDict == true)
						inDict = true;
					if (snmpHostPointer->communityWeak != Device::passwordPassed)
						weak = true;
				}
				snmpHostPointer = snmpHostPointer->next;
			}
		}

		device->addValue(paragraphPointer, filterCount + nmsFilterCount);
		if ((filterCount > 0) && (nmsFilterCount > 0))
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *DEVICENAME* was configured to allow unfiltered access to the *ABBREV*SNMP*-ABBREV* service using the *NUMBER* community strings and *ABBREV*NMS*-ABBREV* hosts listed in Table *TABLEREF*."));
		else if (filterCount > 0)
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *DEVICENAME* was configured to allow unfiltered access to the *ABBREV*SNMP*-ABBREV* service using the *NUMBER* community strings listed in Table *TABLEREF*."));
		else
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *DEVICENAME* was configured to allow unfiltered access to the *ABBREV*SNMP*-ABBREV* service from the *ABBREV*NMS*-ABBREV* hosts listed in Table *TABLEREF*."));
		errorCode = device->addTable(paragraphPointer, "GEN-SNMPFILT-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("*ABBREV*SNMP*-ABBREV* without access restrictions");
		device->addTableHeading(paragraphPointer->table, i18n("Type"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Community"), true);
		if (writeAll == true)
			device->addTableHeading(paragraphPointer->table, i18n("Access"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Version"), false);
		if (communityView == true)
			device->addTableHeading(paragraphPointer->table, i18n("View"), false);

		snmpCommunityPointer = community;
		while (snmpCommunityPointer != 0)
		{
			if ((snmpCommunityPointer->enabled == true) && (((communityRequiresHosts == true) && (hostCommunityExists(snmpCommunityPointer->community.c_str()) == true)) || (communityRequiresHosts == false)))
			{
				if (snmpCommunityPointer->filter.empty())
				{
					device->addTableData(paragraphPointer->table, i18n("Community"));
					device->addTableData(paragraphPointer->table, snmpCommunityPointer->community.c_str());
					if (writeAll == true)
					{
						switch (snmpCommunityPointer->type)
						{
							case communityReadOnly:
								device->addTableData(paragraphPointer->table, i18n("Read Only"));
								break;
							case communityReadWrite:
								device->addTableData(paragraphPointer->table, i18n("Read/Write"));
								break;
							default:
								device->addTableData(paragraphPointer->table, i18n("Read/Write All"));
								break;
						}
					}
					switch (snmpCommunityPointer->version)
					{
						case 1:
							device->addTableData(paragraphPointer->table, i18n("1"));
							break;
						case 2:
							device->addTableData(paragraphPointer->table, i18n("2c"));
							break;
						case 3:
							device->addTableData(paragraphPointer->table, i18n("3"));
							break;
						default:
							device->addTableData(paragraphPointer->table, i18n("1 and 2c"));
							break;
					}
					if (communityView == true)
					{
						if (!snmpCommunityPointer->view.empty())
							device->addTableData(paragraphPointer->table, snmpCommunityPointer->view.c_str());
						else
							device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
					}
				}
			}
			snmpCommunityPointer = snmpCommunityPointer->next;
		}
		if ((communityRequiresHosts == false) && (hostShowCommunity == true) && (nmsFilterCount > 0))
		{
			snmpHostPointer = snmpHost;
			while (snmpHostPointer != 0)
			{
				if (snmpHostPointer->filter.empty())
				{
					device->addTableData(paragraphPointer->table, i18n("*ABBREV*NMS*-ABBREV* Host"));
					device->addTableData(paragraphPointer->table, snmpHostPointer->community.c_str());
					tempString.assign(snmpHostPointer->host);
					tempString.append(" ");
					tempString.append(snmpHostPointer->networkMask);
					device->addTableData(paragraphPointer->table, tempString.c_str());
					device->addTableData(paragraphPointer->table, i18n("N/A"));
					if (communityView == true)
						device->addTableData(paragraphPointer->table, i18n("N/A"));
				}
				snmpHostPointer = snmpHostPointer->next;
			}
		}
	}

	// One found...
	else
	{
		snmpCommunityPointer = community;
		while (snmpCommunityPointer != 0)
		{
			if ((snmpCommunityPointer->enabled == true) && (((communityRequiresHosts == true) && (hostCommunityExists(snmpCommunityPointer->community.c_str()) == true)) || (communityRequiresHosts == false)))
			{
				if (snmpCommunityPointer->filter.empty())
				{
					switch (snmpCommunityPointer->type)
					{
						case communityReadOnly:
							device->addString(paragraphPointer, i18n("read only"));
							break;
						case communityReadWrite:
							device->addString(paragraphPointer, i18n("read/write"));
							break;
						default:
							device->addString(paragraphPointer, i18n("read/write all"));
							break;
					}
					device->addString(paragraphPointer, snmpCommunityPointer->community.c_str());
					paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that unfiltered access to the *DEVICENAME* *ABBREV*SNMP*-ABBREV* agent was allowed using the *DATA* community string*PASSWORD*."));
					if ((communityView == true) && (snmpCommunityPointer->view.empty()))
						viewUsed = false;
					if (snmpCommunityPointer->communityInDict == true)
						inDict = true;
					if (snmpCommunityPointer->communityWeak != Device::passwordPassed)
						weak = true;
					if (snmpCommunityPointer->type != communityReadOnly)
						writeAll = true;
				}
			}
			snmpCommunityPointer = snmpCommunityPointer->next;
		}
		if ((communityRequiresHosts == false) && (hostShowCommunity == true) && (nmsFilterCount > 0))
		{
			snmpHostPointer = snmpHost;
			while (snmpHostPointer != 0)
			{
				if (snmpHostPointer->filter.empty())
				{
					tempString.assign(snmpHostPointer->host);
					tempString.append(" ");
					tempString.append(snmpHostPointer->networkMask);
					device->addString(paragraphPointer, tempString.c_str());
					paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that unfiltered access to the *DEVICENAME* *ABBREV*SNMP*-ABBREV* agent was allowed from the *ABBREV*NMS*-ABBREV* host *HOST*."));
					if (snmpHostPointer->communityInDict == true)
						inDict = true;
					if (snmpHostPointer->communityWeak != Device::passwordPassed)
						weak = true;
				}
				snmpHostPointer = snmpHostPointer->next;
			}
		}
	}

	// Issue impact...
	securityIssuePointer->impactRating = 4;			// Low
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("If an attacker or malicious user had determined a community string for the *ABBREV*SNMP*-ABBREV* agent, without any network filtering the attacker could query the service for configuration information."));
	if (writeAll == true)
	{
		securityIssuePointer->impactRating = 5;		// Medium
		paragraphPointer->paragraph.append(i18n(" Furthermore, with write access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV*, an attacker could modify the configuration of *DEVICENAME*."));
	}
	if ((viewUsed == true) && (communityView == true))
	{
		paragraphPointer->paragraph.append(i18n(" However, access to the *DEVICENAME* *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* was restricted with the configuration of views."));
		securityIssuePointer->impactRating--;
	}

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 3;				// Moderate
	paragraphPointer->paragraph.assign(i18n("For an attacker or malicious user to gain access to the *DEVICENAME* *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* they would require an *ABBREV*SNMP*-ABBREV* query tool and a community string. *ABBREV*SNMP*-ABBREV* tools are available on the Internet and some *ABBREV*OS*-ABBREV* install them by default."));
	if (inDict == true)
	{
		securityIssuePointer->easeRating = 8;				// Easy
		device->addString(paragraphPointer, "GEN.SNMPDICT.1");
		paragraphPointer->paragraph.append(i18n(" Furthermore, the attacker could make use of a dictionary attack against the *ABBREV*SNMP*-ABBREV* agent in order to gain access to a community string (see section *SECTIONNO*)."));
	}
	else if (weak == true)
	{
		securityIssuePointer->easeRating = 4;				// Moderate
		device->addString(paragraphPointer, "GEN.SNMPWEAK.1");
		paragraphPointer->paragraph.append(i18n(" Furthermore, the attacker could make use of a brute-force attack against the *ABBREV*SNMP*-ABBREV* agent in order to gain access to a community string (see section *SECTIONNO*)."));
	}

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if not required, *ABBREV*SNMP*-ABBREV* should be disabled."));
	if (supportSNMP3 == true)
		paragraphPointer->paragraph.append(i18n(" However if *ABBREV*SNMP*-ABBREV* is required, *COMPANY* recommends that only *ABBREV*SNMP*-ABBREV* version 3 should be configured."));
	else if (supportSNMP3Upgrade == true)
	{
		paragraphPointer->paragraph.append(i18n(" However if *ABBREV*SNMP*-ABBREV* is required, *COMPANY* recommends that *DEVICETYPE* *ABBREV*OS*-ABBREV* should be upgraded and that only support for *ABBREV*SNMP*-ABBREV* version 3 is configured. "));
		paragraphPointer->paragraph.append(supportSNMP3UpgText);
		securityIssuePointer->fixRating = 8;			// Involved
	}
	else
		paragraphPointer->paragraph.append(i18n(" It is not possible to configure support for *ABBREV*SNMP*-ABBREV* version 3 on *DEVICETYPE* devices."));
	paragraphPointer->paragraph.append(i18n(" If access using community strings is required, *COMPANY* recommends that network filtering should be configured to restrict access."));
	if (strlen(disableSNMPCmdText) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(disableSNMPCmdText);
	}
	if ((supportSNMP3 == true) && (strlen(configSNMP3Text) > 0))
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configSNMP3Text);
	}
	if (strlen(configSNMPFilterText) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configSNMPFilterText);
	}
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("It is worth noting that *ABBREV*SNMP*-ABBREV* community string authentication is not encrypted. Therefore *COMPANY* recommends that any configured community strings should not be similar to the authentication password for any other system or service."));

	// Conclusions text...
	tempString.assign(snmpFilterText);
	tempString.append(i18n(" were not configured to restrict *ABBREV*SNMP*-ABBREV* access"));
	securityIssuePointer->conLine.append(tempString.c_str());

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Configure *ABBREV*SNMP*-ABBREV* network host access restrictions."));

	// Dependent issues...
	device->addDependency(securityIssuePointer, "GEN.SNMPCLEA.1");

	// Related issues...
	if (inDict == true)
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPDICT.1");
	else if (weak == true)
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWEAK.1");
	if (writeAll == true)
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWRIT.1");
	if ((viewUsed == false) && (communityView == true))
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPVIEW.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWEFI.1");

	return errorCode;
}


int SNMP::snmpClearTextVersion(Device *device, bool writeAccess, bool viewConfigured, bool filteringConfigured)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] Clear Text SNMP In Use\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("Clear Text *ABBREV*SNMP*-ABBREV* In Use"));
	securityIssuePointer->reference.assign("GEN.SNMPCLEA.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	device->addString(paragraphPointer, snmpFilterText);
	paragraphPointer->paragraph.assign(i18n("*ABBREV*SNMP*-ABBREV* versions 1 and 2c are known as clear text protocol services. They provide no encryption for either the authentication or the data sent between the *ABBREV*SNMP*-ABBREV* agent and the *ABBREV*NMS*-ABBREV* or *ABBREV*SNMP*-ABBREV* management hosts. *COMPANY* determined that *DEVICENAME* was configured to use clear-text *ABBREV*SNMP*-ABBREV*."));

	// Issue impact...
	securityIssuePointer->impactRating = 5;			// Medium
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("An attacker or malicious user who can monitor the unencrypted *ABBREV*SNMP*-ABBREV* network traffic would capture the *ABBREV*SNMP*-ABBREV* community string used to authenticate access to the *ABBREV*SNMP*-ABBREV* agent service."));
	if (writeAccess == true)
	{
		securityIssuePointer->impactRating = 7;		// High
		device->addString(paragraphPointer, "GEN.SNMPWRIT.1");
		paragraphPointer->paragraph.append(i18n(" Furthermore, with write access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV*, an attacker could modify the configuration of *DEVICENAME* (see section *SECTIONNO*)."));
	}
	if ((viewConfigured == false) && (communityView == true))
	{
		device->addString(paragraphPointer, "GEN.SNMPVIEW.1");
		paragraphPointer->paragraph.append(i18n(" Without a view for each community string, an attackers access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* would be unrestricted (see section *SECTIONNO*)."));
	}
	else
		securityIssuePointer->impactRating -= 2;

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 6;				// Easy
	paragraphPointer->paragraph.assign(i18n("Network packet capture tools are available on the Internet that can allow an attacker to monitor the network traffic. In a modern network environment, switches are typically deployed to connect the network infrastructure devices rather than hubs. With a network switch devices, the attacker should only be able to see broadcast network traffic or traffic sent directly to or from the attackers host. However, a skilled attacker could bypass this restriction by performing an attack such *ABBREV*ARP*-ABBREV* spoofing or exploiting a vulnerability with the network routing. Tools for bypassing a network switching environments restrictions are available on the Internet."));
	device->addString(paragraphPointer, snmpFilterText);
	if ((filteringConfigured == false) && (communityFilter == true))
	{
		paragraphPointer->paragraph.append(i18n(" *DATA* were not fully configured to restrict access to specific *ABBREV*NMS*-ABBREV* or *ABBREV*SNMP*-ABBREV* management hosts."));
	}
	else if (communityFilter == true)
	{
		securityIssuePointer->easeRating = 2;				// Challenge
		paragraphPointer->paragraph.append(i18n(" *DATA* were configured to restrict *ABBREV*SNMP*-ABBREV* access from specific host, although a skilled attacker may be able to bypass any host-based access restrictions."));
	}

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if not required, *ABBREV*SNMP*-ABBREV* should be disabled."));
	if (supportSNMP3 == true)
		paragraphPointer->paragraph.append(i18n(" However if *ABBREV*SNMP*-ABBREV* is required, *COMPANY* recommends that only *ABBREV*SNMP*-ABBREV* version 3 should be configured."));
	else if (supportSNMP3Upgrade == true)
	{
		paragraphPointer->paragraph.append(i18n(" However if *ABBREV*SNMP*-ABBREV* is required, *COMPANY* recommends that the *DEVICETYPE* *ABBREV*OS*-ABBREV* should be upgraded and that only support for *ABBREV*SNMP*-ABBREV* version 3 should be configured. "));
		paragraphPointer->paragraph.append(supportSNMP3UpgText);
		securityIssuePointer->fixRating = 8;			// Involved
	}
	else
		paragraphPointer->paragraph.append(i18n(" It is not possible to configure support for *ABBREV*SNMP*-ABBREV* version 3 on *DEVICETYPE* devices."));
	if (strlen(disableSNMPCmdText) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(disableSNMPCmdText);
	}
	if ((supportSNMP3 == true) && (strlen(configSNMP3Text) > 0))
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configSNMP3Text);
	}

	// Conclusions text...
	securityIssuePointer->conLine.append(i18n("clear text *ABBREV*SNMP*-ABBREV* was configured"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("If *ABBREV*SNMP*-ABBREV* is not required, disable it"));
	if (supportSNMP3Upgrade == true)
	{
		device->addRecommendation(securityIssuePointer, i18n("Upgrade the *DEVICETYPE* *ABBREV*OS*-ABBREV*"), true);
		if (supportSNMP3 == true)
			device->addRecommendation(securityIssuePointer, i18n("Configure *ABBREV*SNMP*-ABBREV* version 3"));		
	}
	else if (supportSNMP3 == true)
		device->addRecommendation(securityIssuePointer, i18n("Configure *ABBREV*SNMP*-ABBREV* version 3"), true);	

	// Related issues...
	device->addRelatedIssue(securityIssuePointer, "GEN.SNMPDEFT.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.SNMPDICT.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWEAK.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.SNMPTRDI.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.SNMPTRWE.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWRIT.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.SNMPFILT.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.SNMPVIEW.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWEFI.1");

	return errorCode;
}


int SNMP::snmpWeakFiltering(Device *device, int accessFromAnySource, int accessFromNetSource)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	snmpCommunity *snmpCommunityPointer = 0;
	snmpHostStruct *snmpHostPointer = 0;
	bool writeAccess = false;
	bool viewConfigured = true;
	bool weakCommunity = false;
	bool dictionaryCommunity = false;
	bool defaultCommunity = false;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] Weak SNMP NMS Access Restrictions\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("Weak *ABBREV*SNMP*-ABBREV* *ABBREV*NMS*-ABBREV* Access Restrictions"));
	securityIssuePointer->reference.assign("GEN.SNMPWEFI.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	device->addString(paragraphPointer, snmpFilterText);
	paragraphPointer->paragraph.assign(i18n("Remote access to the *ABBREV*SNMP*-ABBREV* agent from *ABBREV*NMS*-ABBREV* and *ABBREV*SNMP*-ABBREV* management hosts can be restricted to specific network hosts. "));
	if (accessFromAnySource + accessFromNetSource > 1)
	{
		device->addValue(paragraphPointer, accessFromAnySource + accessFromNetSource);
		paragraphPointer->paragraph.append(i18n("*COMPANY* identified the *NUMBER* weak *ABBREV*NMS*-ABBREV* and *ABBREV*SNMP*-ABBREV* management host network restrictions listed in Table *TABLEREF*."));

		errorCode = device->addTable(paragraphPointer, "GEN-SNMPWEFI-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("*ABBREV*SNMP*-ABBREV* with weak access restrictions");

		if (hostShowFilterID == true)
			device->addTableHeading(paragraphPointer->table, hostFilterText, false);
		if (hostShowCommunity == true)
			device->addTableHeading(paragraphPointer->table, i18n("Community"), true);
		if (hostShowInterface == true)
			device->addTableHeading(paragraphPointer->table, i18n("Interface"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Host"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Netmask"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Issue Description"), false);

		snmpHostPointer = snmpHost;
		while (snmpHostPointer != 0)
		{
			if ((snmpHostPointer->networkMask.compare("0.0.0.0") == 0) || (snmpHostPointer->networkMask.compare("255.255.255.255") != 0))
			{
				if (hostShowFilterID == true)
					device->addTableData(paragraphPointer->table, snmpHostPointer->filter.c_str());
				if (hostShowCommunity == true)
					device->addTableData(paragraphPointer->table, snmpHostPointer->community.c_str());
				if (hostShowInterface == true)
					device->addTableData(paragraphPointer->table, snmpHostPointer->interface.c_str());
				device->addTableData(paragraphPointer->table, snmpHostPointer->host.c_str());
				device->addTableData(paragraphPointer->table, snmpHostPointer->networkMask.c_str());
				if ((snmpHostPointer->networkMask.compare("0.0.0.0") == 0) && (device->config->checkFilterForAnySource == true))
					device->addTableData(paragraphPointer->table, i18n("Access allowed from any source address."));
				else
					device->addTableData(paragraphPointer->table, i18n("Access allowed from a network range."));

				// Tests...
				if (hostShowCommunity == true)
					snmpCommunityPointer = getSNMPCommunity(snmpHostPointer->community.c_str());
				else if (hostShowFilterID == true)
					snmpCommunityPointer = getSNMPCommunityACL(snmpHostPointer->filter.c_str());
				if (snmpCommunityPointer != 0)
				{
					if (snmpCommunityPointer->communityDefault == true)
						defaultCommunity = true;
					if (snmpCommunityPointer->communityInDict == true)
						dictionaryCommunity = true;
					if (snmpCommunityPointer->communityWeak != Device::passwordPassed)
						weakCommunity = true;
					if ((communityView == true) && (snmpCommunityPointer->view.empty()))
						viewConfigured = false;
					if (snmpCommunityPointer->type != communityReadOnly)
						writeAccess = true;
				}
				else
				{
					if (snmpHostPointer->communityInDict == true)
						dictionaryCommunity = true;
					if (snmpHostPointer->communityWeak != Device::passwordPassed)
						weakCommunity = true;
				}
			}
			snmpHostPointer = snmpHostPointer->next;
		}
	}
	else
	{
		snmpHostPointer = snmpHost;
		while (snmpHostPointer != 0)
		{
			if (snmpHostPointer->networkMask.compare("0.0.0.0") == 0)
			{
				if (hostShowFilterID == true)
				{
					device->addString(paragraphPointer, snmpHostPointer->filter.c_str());
					paragraphPointer->paragraph.append(i18n("*COMPANY* determined that *DATA* permitted access to the *DEVICENAME* *ABBREV*SNMP*-ABBREV* agent from any source address."));
				}
				else if (hostShowInterface == true)
				{
					device->addString(paragraphPointer, snmpHostPointer->interface.c_str());
					paragraphPointer->paragraph.append(i18n("*COMPANY* determined that access was permitted to the *DEVICENAME* *ABBREV*SNMP*-ABBREV* agent from any source address on interface *DATA*."));
				}
				else
					paragraphPointer->paragraph.append(i18n("*COMPANY* determined that access was permitted to the *DEVICENAME* *ABBREV*SNMP*-ABBREV* agent from any source address."));
			}
			else if (snmpHostPointer->networkMask.compare("255.255.255.255") != 0)
			{
				if (hostShowFilterID == true)
				{
					device->addString(paragraphPointer, snmpHostPointer->filter.c_str());
					paragraphPointer->paragraph.append(i18n("*COMPANY* determined that *DATA* permitted access to the *DEVICENAME* *ABBREV*SNMP*-ABBREV* agent from a network range."));
				}
				else if (hostShowInterface == true)
				{
					device->addString(paragraphPointer, snmpHostPointer->interface.c_str());
					paragraphPointer->paragraph.append(i18n("*COMPANY* determined that access was permitted to the *DEVICENAME* *ABBREV*SNMP*-ABBREV* agent from a network range on interface *DATA*."));
				}
				else
					paragraphPointer->paragraph.append(i18n("*COMPANY* determined that access was permitted to the *DEVICENAME* *ABBREV*SNMP*-ABBREV* agent from a network range."));

				// Tests...
				if (hostShowCommunity == true)
					snmpCommunityPointer = getSNMPCommunity(snmpHostPointer->community.c_str());
				else if (hostShowFilterID == true)
					snmpCommunityPointer = getSNMPCommunityACL(snmpHostPointer->filter.c_str());
				if (snmpCommunityPointer != 0)
				{
					if (snmpCommunityPointer->communityDefault == true)
						defaultCommunity = true;
					if (snmpCommunityPointer->communityInDict == true)
						dictionaryCommunity = true;
					if (snmpCommunityPointer->communityWeak != Device::passwordPassed)
						weakCommunity = true;
					if ((communityView == true) && (snmpCommunityPointer->view.empty()))
						viewConfigured = false;
					if (snmpCommunityPointer->type != communityReadOnly)
						writeAccess = true;
				}
				else
				{
					if (snmpHostPointer->communityInDict == true)
						dictionaryCommunity = true;
					if (snmpHostPointer->communityWeak != Device::passwordPassed)
						weakCommunity = true;
				}
			}
			snmpHostPointer = snmpHostPointer->next;
		}
	}

	// Issue impact...
	securityIssuePointer->impactRating = 5;			// Medium
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("A unauthorised user or attacker who knew a community string could access the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* due to the weak access restrictions."));
	if (writeAccess == true)
	{
		securityIssuePointer->impactRating = 7;		// High
		paragraphPointer->paragraph.append(i18n(" Furthermore, with write access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV*, an attacker could modify the configuration of *DEVICENAME*."));
	}
	if ((viewConfigured == false) && (communityView == true))
		paragraphPointer->paragraph.append(i18n(" Without a view for each community string, the attackers access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* would be unrestricted."));
	else
		securityIssuePointer->impactRating -= 2;

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 4;				// Moderate
	paragraphPointer->paragraph.assign(i18n("To exploit this issue an attacker would require *ABBREV*SNMP*-ABBREV* query tools and a *ABBREV*SNMP*-ABBREV* community string. *ABBREV*SNMP*-ABBREV* query tools are available on the Internet and some *ABBREV*OS*-ABBREV* install them by default."));
	if (defaultCommunity == true)
	{
		securityIssuePointer->easeRating = 7;				// Easy
		device->addString(paragraphPointer, "GEN.SNMPDEFT.1");
		paragraphPointer->paragraph.append(i18n(" Furthermore, a default community string was configured so the attacker could simply guess the *ABBREV*SNMP*-ABBREV* community string in order to gain access (see section *SECTIONNO*)."));
	}
	else if (dictionaryCommunity == true)
	{
		securityIssuePointer->easeRating = 6;				// Easy
		device->addString(paragraphPointer, "GEN.SNMPDICT.1");
		paragraphPointer->paragraph.append(i18n(" Furthermore, the attacker could make use of a dictionary attack against the *ABBREV*SNMP*-ABBREV* service in order to gain access to a community string (see section *SECTIONNO*)."));
	}
	else if (weakCommunity == true)
	{
		securityIssuePointer->easeRating = 5;				// Moderate
		device->addString(paragraphPointer, "GEN.SNMPWEAK.1");
		paragraphPointer->paragraph.append(i18n(" Furthermore, the attacker could make use of a brute-force attack against the *ABBREV*SNMP*-ABBREV* service in order to gain access to a community string (see section *SECTIONNO*)."));
	}

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if not required, *ABBREV*SNMP*-ABBREV* should be disabled."));
	if (supportSNMP3 == true)
		paragraphPointer->paragraph.append(i18n(" However if *ABBREV*SNMP*-ABBREV* is required, *COMPANY* recommends that only *ABBREV*SNMP*-ABBREV* version 3 should be configured."));
	else if (supportSNMP3Upgrade == true)
	{
		paragraphPointer->paragraph.append(i18n(" However if *ABBREV*SNMP*-ABBREV* is required, *COMPANY* recommends that the *DEVICETYPE* *ABBREV*OS*-ABBREV* should be upgraded and that only support for *ABBREV*SNMP*-ABBREV* version 3 should be configured. "));
		paragraphPointer->paragraph.append(supportSNMP3UpgText);
		securityIssuePointer->fixRating = 8;			// Involved
	}
	else
		paragraphPointer->paragraph.append(i18n(" It is not possible to configure support for *ABBREV*SNMP*-ABBREV* version 3 on *DEVICETYPE* devices."));
	paragraphPointer->paragraph.append(i18n(" If access using community strings is required, *COMPANY* recommends that access is restricted to specific *ABBREV*NMS*-ABBREV* and *ABBREV*SNMP*-ABBREV* management hosts."));
	if (strlen(disableSNMPCmdText) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(disableSNMPCmdText);
	}
	if ((supportSNMP3 == true) && (strlen(configSNMP3Text) > 0))
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configSNMP3Text);
	}
	if (strlen(configSNMPFilterText) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configSNMPFilterText);
	}

	// Conclusions text...
	securityIssuePointer->conLine.append(i18n("weak *ABBREV*SNMP*-ABBREV* *ABBREV*NMS*-ABBREV* access restrictions were configured"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Restrict *ABBREV*SNMP*-ABBREV* access to specific *ABBREV*NMS*-ABBREV* and *ABBREV*SNMP*-ABBREV* management hosts."), true);	

	// Dependent issues...
	device->addDependency(securityIssuePointer, "GEN.SNMPCLEA.1");

	// Related issues...
	if (defaultCommunity == true)
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPDEFT.1");
	else if (dictionaryCommunity == true)
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPDICT.1");
	else if (weakCommunity == true)
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWEAK.1");
	if (writeAccess == true)
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWRIT.1");
	if ((viewConfigured == false) && (communityView == true))
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPVIEW.1");

	return errorCode;
}

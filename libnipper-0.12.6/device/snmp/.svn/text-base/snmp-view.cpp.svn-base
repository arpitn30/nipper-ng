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


int SNMP::addSNMPView(const char *viewName, const char *mibName, bool include)
{
	// Variables...
	SNMP::snmpView *viewPointer = 0;
	SNMP::snmpMIB *mibPointer = 0;
	int errorCode = 0;
	bool found = true;

	// Get / Create View...
	if (view == 0)
	{
		view = new (snmpView);
		viewPointer = view;
		found = false;
	}
	else
	{
		viewPointer = view;
		while ((viewPointer->next != 0) && (viewPointer->view.compare(viewName) != 0))
			viewPointer = viewPointer->next;
		if (viewPointer->view.compare(viewName) != 0)
		{
			viewPointer->next = new (snmpView);
			viewPointer = viewPointer->next;
			found = false;
		}
	}

	// If the view needs initing...
	if (found == false)
	{
		viewPointer->view.assign(viewName);
		viewPointer->mib = 0;
		viewPointer->everything = false;
		viewPointer->next = 0;
	}

	// Add MIB to the view...
	if (viewPointer->mib == 0)
	{
		viewPointer->mib = new (snmpMIB);
		mibPointer = viewPointer->mib;
	}
	else
	{
		mibPointer = viewPointer->mib;
		while (mibPointer->next != 0)
			mibPointer = mibPointer->next;
		mibPointer->next = new (snmpMIB);
		mibPointer = mibPointer->next;
	}

	// Init MIB...
	mibPointer->mib.assign(mibName);
	mibPointer->include = include;
	mibPointer->next = 0;

	return errorCode;
}


SNMP::snmpView *SNMP::getSNMPView(const char *viewName)
{
	// Variables...
	SNMP::snmpView *viewPointer = view;
	bool found = false;

	while ((viewPointer != 0) && (found == false))
	{
		if (viewPointer->view.compare(viewName) == 0)
			found = true;
		else
			viewPointer = viewPointer->next;
	}

	return viewPointer;
}


int SNMP::generateViewConfigReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	snmpView *viewPointer = view;
	snmpMIB *mibPointer = 0;
	string tempString;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s SNMP Views\n", device->config->COL_BLUE, device->config->COL_RESET);

	// Init pointers...
	configReportPointer = device->getConfigSection("CONFIG-SNMP");
	paragraphPointer = device->addParagraph(configReportPointer);

	// Set subsection title...
	paragraphPointer->paragraphTitle.assign(i18n("*ABBREV*SNMP*-ABBREV* Views"));
	paragraphPointer->paragraph.assign(i18n("*ABBREV*SNMP*-ABBREV* views are used to restrict the areas of the *ABBREV*MIB*-ABBREV* a *ABBREV*NMS*-ABBREV* can access."));

	// Create Table for non-seperated views...
	if (viewSeperated == false)
	{
		errorCode = device->addTable(paragraphPointer, "CONFIG-SNMPVIEW-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("*ABBREV*SNMP*-ABBREV* view configuration");
		device->addTableHeading(paragraphPointer->table, i18n("View"), false);
		device->addTableHeading(paragraphPointer->table, viewMIBText, false);
		if (viewExcludes == true)
			device->addTableHeading(paragraphPointer->table, i18n("Action"), false);
	}

	// Output views...
	while (viewPointer != 0)
	{

		// if separate view tables are required...
		if (viewSeperated == true)
		{
			paragraphPointer = device->addParagraph(configReportPointer);
			tempString.assign("CONFIG-SNMPVIEW-");
			tempString.append(viewPointer->view);
			tempString.append("-TABLE");
			errorCode = device->addTable(paragraphPointer, tempString.c_str());
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title.assign(viewPointer->view);
			paragraphPointer->table->title.append(i18n(" *ABBREV*SNMP*-ABBREV* view configuration"));
			device->addTableHeading(paragraphPointer->table, viewMIBText, false);
			if (viewExcludes == true)
				device->addTableHeading(paragraphPointer->table, i18n("Action"), false);
		}

		// MIB data...
		mibPointer = view->mib;
		while (mibPointer != 0)
		{
			if (viewSeperated == false)
				device->addTableData(paragraphPointer->table, viewPointer->view.c_str());
			device->addTableData(paragraphPointer->table, mibPointer->mib.c_str());
			if (viewExcludes == true)
			{
				if (mibPointer->include == true)
					device->addTableData(paragraphPointer->table, i18n("Include"));
				else
					device->addTableData(paragraphPointer->table, i18n("Include"));
			}

			mibPointer = mibPointer->next;
		}

		viewPointer = viewPointer->next;
	}

	return errorCode;
}


int SNMP::snmpWithoutView(Device *device, int noViewCount)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	snmpCommunity *snmpCommunityPointer = 0;
	string tempString;
	bool ipv6 = false;
	bool found = false;
	int defaultCommunity = 0;
	int dictionaryCommunity = 0;
	int weakCommunity = 0;
	int filterApplied = 0;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] SNMP With No View\n", device->config->COL_BLUE, device->config->COL_RESET);

	// Issue heading and ratings...
	securityIssuePointer = device->addSecurityIssue();
	if (noViewCount > 1)
		securityIssuePointer->title.assign(i18n("*ABBREV*SNMP*-ABBREV* Community Strings Without A View"));
	else
		securityIssuePointer->title.assign(i18n("*ABBREV*SNMP*-ABBREV* Community String Without A View"));
	securityIssuePointer->reference.assign("GEN.SNMPVIEW.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("Views are used to restrict access to specific sections of the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV*. This enables an administrator to restrict *ABBREV*SNMP*-ABBREV* access to only the information that the caller requires."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	if (noViewCount > 1)
	{
		device->addValue(paragraphPointer, noViewCount);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *NUMBER* *ABBREV*SNMP*-ABBREV* community strings listed in Table *TABLEREF* were configured without a view."));
		errorCode = device->addTable(paragraphPointer, "GEN-SNMPVIEW-TABLE");
		if (errorCode != 0)
			return errorCode;
		// IPv6 filters?
		while ((snmpCommunityPointer != 0) && (found == false))
		{
			if ((snmpCommunityPointer->communityInDict == true) && (snmpCommunityPointer->enabled == true) && (((communityRequiresHosts == true) && (hostCommunityExists(snmpCommunityPointer->community.c_str()) == true)) || (communityRequiresHosts == false)))
			{
				found = true;
				if ((!snmpCommunityPointer->ipv6Filter.empty()) && (communityIPv6Filter == true))
					ipv6 = true;
			}
			else
				snmpCommunityPointer = snmpCommunityPointer->next;
		}
		paragraphPointer->table->title = i18n("*ABBREV*SNMP*-ABBREV* community strings with no view");
		device->addTableHeading(paragraphPointer->table, i18n("Type"), true);
		device->addTableHeading(paragraphPointer->table, i18n("Community"), true);
		device->addTableHeading(paragraphPointer->table, i18n("Access"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Version"), false);
		if (communityFilter == true)
			device->addTableHeading(paragraphPointer->table, snmpFilterText, false);
		if (ipv6 == true)
			device->addTableHeading(paragraphPointer->table, snmpFilterIPv6Text, false);
		snmpCommunityPointer = community;
		found = false;
		while (snmpCommunityPointer != 0)
		{
			if ((snmpCommunityPointer->enabled == true) && (snmpCommunityPointer->view.empty()) && (((communityRequiresHosts == true) && (hostCommunityExists(snmpCommunityPointer->community.c_str()) == true)) || (communityRequiresHosts == false)))
			{
				device->addTableData(paragraphPointer->table, i18n("Community"));
				device->addTableData(paragraphPointer->table, snmpCommunityPointer->community.c_str());
				switch (snmpCommunityPointer->type)
				{
					case communityReadOnly:
						device->addTableData(paragraphPointer->table, i18n("Read Only"));
						break;
					case communityReadWrite:
						device->addTableData(paragraphPointer->table, i18n("Read/Write"));
						found = true;
						break;
					default:
						device->addTableData(paragraphPointer->table, i18n("Read/Write All"));
						found = true;
						break;
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
				if (snmpCommunityPointer->communityDefault == true)
					defaultCommunity++;
				else if (snmpCommunityPointer->communityInDict == true)
					dictionaryCommunity++;
				else if (snmpCommunityPointer->communityWeak == true)
					weakCommunity++;
				if ((communityFilter == true) && (snmpCommunityPointer->filter.empty()))
					filterApplied++;
			}
			snmpCommunityPointer = snmpCommunityPointer->next;
		}
	}
	else
	{
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the*PASSWORD* *DATA* community string did not have a view."));
		snmpCommunityPointer = community;
		while (snmpCommunityPointer != 0)
		{
			if ((snmpCommunityPointer->enabled == true) && (snmpCommunityPointer->view.empty()) && (((communityRequiresHosts == true) && (hostCommunityExists(snmpCommunityPointer->community.c_str()) == true)) || (communityRequiresHosts == false)))
			{
				device->addString(paragraphPointer, snmpCommunityPointer->community.c_str());
				switch (snmpCommunityPointer->type)
				{
					case communityReadOnly:
						device->addString(paragraphPointer, i18n("read only"));
						break;
					case communityReadWrite:
						device->addString(paragraphPointer, i18n("read/write"));
						found = true;
						break;
					default:
						device->addString(paragraphPointer, i18n("read/write all"));
						found = true;
						break;
				}
				if (snmpCommunityPointer->communityDefault == true)
					defaultCommunity++;
				else if (snmpCommunityPointer->communityInDict == true)
					dictionaryCommunity++;
				else if (snmpCommunityPointer->communityWeak == true)
					weakCommunity++;
				if ((communityFilter == true) && (snmpCommunityPointer->filter.empty()))
					filterApplied++;
			}
			snmpCommunityPointer = snmpCommunityPointer->next;
		}
	}

	// Issue impact...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("An attacker or malicious user who has *ABBREV*SNMP*-ABBREV* access using a community string for which no view had been configured would have unrestricted access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV*."));
	if (found == true)
	{
		securityIssuePointer->impactRating = 4;		// Low
		paragraphPointer->paragraph.append(i18n(" Furthermore, with write access to the *ABBREV*MIB*-ABBREV*, the attacker or malicious user could modify the configuration of *DEVICENAME*."));
	}
	else
		securityIssuePointer->impactRating = 3;		// Low

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	paragraphPointer->paragraph.assign(i18n("For an attacker or malicious user to gain unrestricted access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* they would require a community string that had not been restricted with a view and *ABBREV*SNMP*-ABBREV* query tools."));
	if (defaultCommunity > 0)
	{
		device->addString(paragraphPointer, "GEN.SNMPDEFT.1");
		if (defaultCommunity > 1)
			paragraphPointer->paragraph.append(i18n(" *COMPANY* determined that *DEVICENAME* was configured with default community strings (see section *SECTIONNO*) that were not restricted by a view."));
		else
			paragraphPointer->paragraph.append(i18n(" *COMPANY* determined that *DEVICENAME* was configured with a default community string (see section *SECTIONNO*) that is not restricted by a view."));
		securityIssuePointer->easeRating = 7;			// Easy
	}
	else if (dictionaryCommunity > 0)
	{
		device->addString(paragraphPointer, "GEN.SNMPDICT.1");
		if (dictionaryCommunity > 1)
			paragraphPointer->paragraph.append(i18n(" *COMPANY* determined that *DEVICENAME* was configured with dictionary-based community strings (see section *SECTIONNO*) that were not restricted by a view."));
		else
			paragraphPointer->paragraph.append(i18n(" *COMPANY* determined that *DEVICENAME* was configured with a dictionary-based community string (see section *SECTIONNO*) that is not restricted by a view."));
		securityIssuePointer->easeRating = 6;			// Easy
	}
	else if (weakCommunity > 0)
	{
		device->addString(paragraphPointer, "GEN.SNMPWEAK.1");
		if (weakCommunity > 1)
			paragraphPointer->paragraph.append(i18n(" *COMPANY* determined that *DEVICENAME* was configured with weak community strings (see section *SECTIONNO*) that were not restricted by a view."));
		else
			paragraphPointer->paragraph.append(i18n(" *COMPANY* determined that *DEVICENAME* was configured with a weak community string (see section *SECTIONNO*) that is not restricted by a view."));
		securityIssuePointer->easeRating = 5;			// Moderate
	}
	else
		securityIssuePointer->easeRating = 4;			// Moderate
	paragraphPointer->paragraph.append(i18n(" A number of *ABBREV*SNMP*-ABBREV* query tools are available on the Internet and *ABBREV*SNMP*-ABBREV* tools are installed by default on some *ABBREV*OS*-ABBREV*."));
	if (filterApplied == noViewCount)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		device->addString(paragraphPointer, snmpFilterText);
		if (filterApplied > 1)
			paragraphPointer->paragraph.append(i18n("*DATA* were not configured for any of the community strings identified, making it easier for an attacker to gain access the service."));
		else
			paragraphPointer->paragraph.append(i18n("*DATA* had not been configured for the community string identified, making it easier for an attacker to gain access the service."));
	}
	else if (filterApplied > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		device->addString(paragraphPointer, snmpFilterText);
		if (filterApplied > 1)
		{
			device->addValue(paragraphPointer, filterApplied);
			paragraphPointer->paragraph.append(i18n("*DATA* had not been configured for *NUMBER* of the community strings identified, making it easier for an attacker to gain access the service using those community strings."));
		}
		else
			paragraphPointer->paragraph.append(i18n("*DATA* had not been configured for one community string identified, making it easier for an attacker to gain access the service using that community string."));
	}
	else if ((filterApplied == 0) && (communityFilter == true))
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 2;			// Challenging
		device->addString(paragraphPointer, snmpFilterText);
		paragraphPointer->paragraph.append(i18n("*DATA* were configured to help restrict access to the service, but a skilled attacker may be able to bypass any configured network filtering."));
	}

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if not required, *ABBREV*SNMP*-ABBREV* should be disabled."));
	if (supportSNMP3 == true)
		paragraphPointer->paragraph.append(i18n(" However if *ABBREV*SNMP*-ABBREV* is required, *COMPANY* recommends that only *ABBREV*SNMP*-ABBREV* version 3 is configured."));
	else if (supportSNMP3Upgrade == true)
	{
		paragraphPointer->paragraph.append(i18n(" However if *ABBREV*SNMP*-ABBREV* is required, *COMPANY* recommends that *DEVICETYPE* *ABBREV*OS*-ABBREV* is upgraded and that only support for *ABBREV*SNMP*-ABBREV* version 3 is configured. "));
		paragraphPointer->paragraph.append(supportSNMP3UpgText);
		securityIssuePointer->fixRating = 8;			// Involved
	}
	else
		paragraphPointer->paragraph.append(i18n(" It is not possible to configure support for *ABBREV*SNMP*-ABBREV* version 3 on *DEVICETYPE* devices."));
	paragraphPointer->paragraph.append(i18n(" If access using community strings is required, *COMPANY* recommends that a view is configured for every community string in order to limit the access to only those sections of the *ABBREV*MIB*-ABBREV* that are required."));
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
	if (strlen(configSNMPViewText) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configSNMPViewText);
	}
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("It is worth noting that *ABBREV*SNMP*-ABBREV* community string authentication is not encrypted. Therefore *COMPANY* recommends that any configured community strings should not be similar to the authentication password for any other system or service."));

	// Conclusions text...
	if (noViewCount > 1)
		securityIssuePointer->conLine.assign(i18n("*ABBREV*SNMP*-ABBREV* community strings were configured without a view"));
	else
		securityIssuePointer->conLine.assign(i18n("a *ABBREV*SNMP*-ABBREV* community string was configured without a view"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Configure a view to limit access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV*."));

	// Dependent issues...
	device->addDependency(securityIssuePointer, "GEN.SNMPCLEA.1");

	// Related issues...
	device->addRelatedIssue(securityIssuePointer, "GEN.SNMPDEFT.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.SNMPDICT.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWEAK.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWRIT.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.SNMPFILT.1");

	return errorCode;
}


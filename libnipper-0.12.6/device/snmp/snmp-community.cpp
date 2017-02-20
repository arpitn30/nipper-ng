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


SNMP::snmpCommunity *SNMP::addSNMPCommunity()								// Add a new community
{
	// Variables...
	snmpCommunity *communityPointer = 0;

	// Create struct...
	if (community == 0)
	{
		community = new (snmpCommunity);
		communityPointer = community;
	}
	else
	{
		communityPointer = community;
		while (communityPointer->next != 0)
			communityPointer = communityPointer->next;
		communityPointer->next = new (snmpCommunity);
		communityPointer = communityPointer->next;
	}

	// Init...
	communityPointer->enabled = true;
	communityPointer->type = communityReadOnly;
	communityPointer->version = 1;
	communityPointer->trapsOn = false;
	communityPointer->communityDefault = false;
	communityPointer->communityInDict = false;
	communityPointer->communityWeak = Device::passwordPassed;
	communityPointer->next = 0;

	return communityPointer;
}


SNMP::snmpCommunity *SNMP::getSNMPCommunity(const char *communityString)		// Get an existing community
{
	// Variables...
	bool found = false;
	snmpCommunity *communityPointer = community;

	while ((communityPointer != 0) && (found == false))
	{
		if (strcmp(communityString, communityPointer->community.c_str()) == 0)
			found = true;
		else
			communityPointer = communityPointer->next;
	}

	return communityPointer;
}
SNMP::snmpCommunity *SNMP::getSNMPCommunityACL(const char *filterString)		// Get an existing community
{
	// Variables...
	bool found = false;
	snmpCommunity *communityPointer = community;

	while ((communityPointer != 0) && (found == false))
	{
		if (strcmp(filterString, communityPointer->filter.c_str()) == 0)
			found = true;
		else
			communityPointer = communityPointer->next;
	}

	return communityPointer;
}


int SNMP::generateCommunityConfigReport(Device *device)					// Generate Community Configuration Report
{
	// Variables...
	snmpCommunity *communityPointer = community;
	int errorCode = 0;
	bool found = false;
	bool ipv6 = false;
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;

	// Better just check to make sure that there are enabled community strings to report...
	while ((communityPointer != 0) && (found == false))
	{
		if (communityPointer->enabled == true)
		{
			found = true;
			if ((!communityPointer->ipv6Filter.empty()) && (communityIPv6Filter == true))
				ipv6 = true;
		}
		else
			communityPointer = communityPointer->next;
	}
	if (found == true)
	{

		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s SNMP Community\n", device->config->COL_BLUE, device->config->COL_RESET);

		// Init pointers...
		configReportPointer = device->getConfigSection("CONFIG-SNMP");
		paragraphPointer = device->addParagraph(configReportPointer);

		// Set subsection title...
		paragraphPointer->paragraphTitle.assign(i18n("*ABBREV*SNMP*-ABBREV* Community"));
		paragraphPointer->paragraph.assign(i18n("*ABBREV*SNMP*-ABBREV* community strings are used to authenticate access between a *ABBREV*NMS*-ABBREV* and the *DEVICETYPE* *ABBREV*SNMP*-ABBREV* agent. A connecting *ABBREV*NMS*-ABBREV*, using *ABBREV*SNMP*-ABBREV* protocol versions 1 or 2c, must provide the *ABBREV*SNMP*-ABBREV* agent with a valid community string when making a *ABBREV*MIB*-ABBREV* read or write request."));

		// Create Table...
		errorCode = device->addTable(paragraphPointer, "CONFIG-SNMPCOMMUNITY-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("*ABBREV*SNMP*-ABBREV* community configuration");
		device->addTableHeading(paragraphPointer->table, i18n("Community"), true);
		device->addTableHeading(paragraphPointer->table, i18n("Access"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Version"), false);
		if (communityView == true)
			device->addTableHeading(paragraphPointer->table, i18n("View"), false);
		if (communityFilter == true)
			device->addTableHeading(paragraphPointer->table, snmpFilterText, false);
		if (ipv6 == true)
			device->addTableHeading(paragraphPointer->table, snmpFilterIPv6Text, false);

		// Add table data...
		communityPointer = community;
		while (communityPointer != 0)
		{
			if (communityPointer->enabled == true)
			{
				device->addTableData(paragraphPointer->table, communityPointer->community.c_str());
				switch (communityPointer->type)
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
				switch (communityPointer->version)
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
					device->addTableData(paragraphPointer->table, communityPointer->view.c_str());
				if (communityFilter == true)
					device->addTableData(paragraphPointer->table, communityPointer->filter.c_str());
				if (ipv6 == true)
					device->addTableData(paragraphPointer->table, communityPointer->ipv6Filter.c_str());
			}

			communityPointer = communityPointer->next;
		}
	}

	return errorCode;
}


int SNMP::snmpCommunityIssue(Device *device, snmpCommunitySec communityIssue, int totalCommunityCount, int withWriteCount, int withWriteAllCount)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	snmpCommunity *snmpCommunityPointer = 0;
	snmpHostStruct *snmpHostPointer = 0;
	string tempString;
	string issueString;
	bool ipv6 = false;
	bool found = false;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
	{
		switch (communityIssue)
		{
			case communityIssueDict:
				printf("    %s*%s [ISSUE] Dictionary-based SNMP Community\n", device->config->COL_BLUE, device->config->COL_RESET);
				break;
			case communityIssueWeak:
				printf("    %s*%s [ISSUE] Weak SNMP Community\n", device->config->COL_BLUE, device->config->COL_RESET);
				break;
			default:
				printf("    %s*%s [ISSUE] Default SNMP Community\n", device->config->COL_BLUE, device->config->COL_RESET);
				break;
		}
	}

	// Issue heading and ratings...
	securityIssuePointer = device->addSecurityIssue();
	if (totalCommunityCount > 1)
	{
		switch (communityIssue)
		{
			case communityIssueDict:
				securityIssuePointer->title.assign(i18n("Dictionary-Based *ABBREV*SNMP*-ABBREV* Community Strings Were Configured"));
				break;
			case communityIssueWeak:
				securityIssuePointer->title.assign(i18n("Weak *ABBREV*SNMP*-ABBREV* Community Strings Were Configured"));
				break;
			default:
				securityIssuePointer->title.assign(i18n("Default *ABBREV*SNMP*-ABBREV* Community Strings Were Configured"));
				break;
		}
	}
	else
	{
		switch (communityIssue)
		{
			case communityIssueDict:
				securityIssuePointer->title.assign(i18n("A Dictionary-Based *ABBREV*SNMP*-ABBREV* Community String Was Configured"));
				break;
			case communityIssueWeak:
				securityIssuePointer->title.assign(i18n("A Weak *ABBREV*SNMP*-ABBREV* Community String Was Configured"));
				break;
			default:
				securityIssuePointer->title.assign(i18n("A Default *ABBREV*SNMP*-ABBREV* Community String Was Configured"));
				break;
		}
	}
	switch (communityIssue)
	{
		case communityIssueDict:
			securityIssuePointer->reference.assign("GEN.SNMPDICT.1");
			issueString.assign("dictionary-based");
			break;
		case communityIssueWeak:
			securityIssuePointer->reference.assign("GEN.SNMPWEAK.1");
			issueString.assign("weak");
			break;
		default:
			securityIssuePointer->reference.assign("GEN.SNMPDEFT.1");
			issueString.assign("default");
			break;
	}

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*ABBREV*SNMP*-ABBREV* is used for the remote monitoring and management of a variety of network devices. Access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* with protocol versions 1 and 2 is restricted using a community string."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

	// Multiple found...
	if (totalCommunityCount > 1)
	{
		device->addValue(paragraphPointer, totalCommunityCount);
		switch (communityIssue)
		{
			case communityIssueDict:
			case communityIssueWeak:
				device->addString(paragraphPointer, issueString.c_str());
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *NUMBER* community strings listed in Table *TABLEREF* were *DATA*."));
				if (communityIssue == communityIssueDict)
					errorCode = device->addTable(paragraphPointer, "GEN-SNMPWEAK-TABLE");
				else
					errorCode = device->addTable(paragraphPointer, "GEN-SNMPDICT-TABLE");
				break;
			default:
				paragraphPointer->paragraph.assign(i18n("*COMPANY* identified the *NUMBER* default community strings listed in Table *TABLEREF*."));
				errorCode = device->addTable(paragraphPointer, "GEN-SNMPDEFT-TABLE");
				break;
		}
		if (errorCode != 0)
			return errorCode;

		// IPv6 filters?
		while ((snmpCommunityPointer != 0) && (found == false))
		{
			if ((snmpCommunityPointer->enabled == true) && (((communityRequiresHosts == true) && (hostCommunityExists(snmpCommunityPointer->community.c_str()) == true)) || (communityRequiresHosts == false)))
			{
				if (((snmpCommunityPointer->communityWeak != Device::passwordPassed) && (communityIssue == communityIssueWeak)) || ((snmpCommunityPointer->communityInDict == true) && (communityIssue == communityIssueDict)) || ((snmpCommunityPointer->communityDefault == true) && (communityIssue == communityIssueDefault)))
				{
					found = true;
					if ((!snmpCommunityPointer->ipv6Filter.empty()) && (communityIPv6Filter == true))
						ipv6 = true;
				}
			}
			else
				snmpCommunityPointer = snmpCommunityPointer->next;
		}

		switch (communityIssue)
		{
			case communityIssueDict:
				paragraphPointer->table->title = i18n("Dictionary-based *ABBREV*SNMP*-ABBREV* community strings");
				break;
			case communityIssueWeak:
				paragraphPointer->table->title = i18n("Weak *ABBREV*SNMP*-ABBREV* community strings");
				break;
			default:
				paragraphPointer->table->title = i18n("Default *ABBREV*SNMP*-ABBREV* community strings");
				break;
		}
		device->addTableHeading(paragraphPointer->table, i18n("Type"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Community"), true);
		device->addTableHeading(paragraphPointer->table, i18n("Access"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Version"), false);
		if (communityView == true)
			device->addTableHeading(paragraphPointer->table, i18n("View"), false);
		if (communityFilter == true)
			device->addTableHeading(paragraphPointer->table, snmpFilterText, false);
		if (ipv6 == true)
			device->addTableHeading(paragraphPointer->table, snmpFilterIPv6Text, false);
		if (communityIssue == communityIssueWeak)
			device->addTableHeading(paragraphPointer->table, i18n("Issue"), false);

		snmpCommunityPointer = community;
		while (snmpCommunityPointer != 0)
		{
			if ((snmpCommunityPointer->enabled == true) && (((communityRequiresHosts == true) && (hostCommunityExists(snmpCommunityPointer->community.c_str()) == true)) || (communityRequiresHosts == false)))
			{
				if (((snmpCommunityPointer->communityWeak != Device::passwordPassed) && (communityIssue == communityIssueWeak)) || ((snmpCommunityPointer->communityInDict == true) && (communityIssue == communityIssueDict)) || ((snmpCommunityPointer->communityDefault == true) && (communityIssue == communityIssueDefault)))
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
							break;
						default:
							device->addTableData(paragraphPointer->table, i18n("Read/Write All"));
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
					if (communityView == true)
						device->addTableData(paragraphPointer->table, snmpCommunityPointer->view.c_str());
					if (communityFilter == true)
						device->addTableData(paragraphPointer->table, snmpCommunityPointer->filter.c_str());
					if (ipv6 == true)
						device->addTableData(paragraphPointer->table, snmpCommunityPointer->ipv6Filter.c_str());
					if (communityIssue == communityIssueWeak)
					{
						switch (snmpCommunityPointer->communityWeak)
						{
							case Device::passwordShort:
								device->addTableData(paragraphPointer->table, i18n("The community string was too short"));
								break;
							case Device::passwordRepeatChars:
								device->addTableData(paragraphPointer->table, i18n("Characters were repeated too often"));
								break;
							case Device::passwordMakeup:
								device->addTableData(paragraphPointer->table, i18n("The community string did not meet the minimum complexity requirements"));
								break;
							case Device::passwordUsername:
								device->addTableData(paragraphPointer->table, i18n("The username was part of the community string"));
								break;
							case Device::passwordHostname:
								device->addTableData(paragraphPointer->table, i18n("The hostname was part of the community string"));
								break;
							case Device::passwordDictSubst:
								device->addTableData(paragraphPointer->table, i18n("The community string was dictionary-based with character substitution"));
								break;
							case Device::passwordDictAppend:
								device->addTableData(paragraphPointer->table, i18n("The community string was dictionary-based with characters appended"));
								break;
							default:
								device->addTableData(paragraphPointer->table, i18n("The community string contains a common character sequence"));
								break;
						}
					}
				}
			}
			snmpCommunityPointer = snmpCommunityPointer->next;
		}
		if ((communityRequiresHosts == false) && (hostShowCommunity == true))
		{
			snmpHostPointer = snmpHost;
			while (snmpHostPointer != 0)
			{
				if (((snmpHostPointer->communityWeak != Device::passwordPassed) && (communityIssue == communityIssueWeak)) || ((snmpHostPointer->communityInDict == true) && (communityIssue == communityIssueDict)))
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
					if (communityFilter == true)
						device->addTableData(paragraphPointer->table, snmpHostPointer->filter.c_str());
					if (ipv6 == true)
						device->addTableData(paragraphPointer->table, i18n("N/A"));
					if (communityIssue == communityIssueWeak)
					{
						switch (snmpHostPointer->communityWeak)
						{
							case Device::passwordShort:
								device->addTableData(paragraphPointer->table, i18n("The community string was too short"));
								break;
							case Device::passwordRepeatChars:
								device->addTableData(paragraphPointer->table, i18n("Characters were repeated too often"));
								break;
							case Device::passwordMakeup:
								device->addTableData(paragraphPointer->table, i18n("The community string did not meet the minimum complexity requirements"));
								break;
							case Device::passwordUsername:
								device->addTableData(paragraphPointer->table, i18n("The community string was based on the username"));
								break;
							case Device::passwordHostname:
								device->addTableData(paragraphPointer->table, i18n("The community string was based on the hostname"));
								break;
							case Device::passwordDictSubst:
								device->addTableData(paragraphPointer->table, i18n("The community string was dictionary-based with character substitution"));
								break;
							case Device::passwordDictAppend:
								device->addTableData(paragraphPointer->table, i18n("The community string was dictionary-based with characters appended"));
								break;
							default:
								device->addTableData(paragraphPointer->table, i18n("The community string contains a common character sequence"));
								break;
						}
					}
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
				if (((snmpCommunityPointer->communityWeak != Device::passwordPassed) && (communityIssue == communityIssueWeak)) || ((snmpCommunityPointer->communityInDict == true) && (communityIssue == communityIssueDict)) || ((snmpCommunityPointer->communityDefault == true) && (communityIssue == communityIssueDefault)))
				{
					switch (snmpCommunityPointer->type)
					{
						case communityReadOnly:
							errorCode = device->addString(paragraphPointer, i18n("read-only"));
							break;
						case communityReadWrite:
							errorCode = device->addString(paragraphPointer, i18n("read/write"));
							break;
						default:
							errorCode = device->addString(paragraphPointer, i18n("read/write all"));
							break;
					}
					if (errorCode != 0)
						return errorCode;
					errorCode = device->addString(paragraphPointer, snmpCommunityPointer->community.c_str());
					if (errorCode != 0)
						return errorCode;
					switch (communityIssue)
					{
						case communityIssueDict:
							paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *DATA* community string*PASSWORD* was dictionary-based."));
							break;
						case communityIssueWeak:
							switch (snmpCommunityPointer->communityWeak)
							{
								case Device::passwordShort:
									paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *DATA* community string*PASSWORD* was too short."));
									break;
								case Device::passwordRepeatChars:
									paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *DATA* community string*PASSWORD* contained too many repeated characters."));
									break;
								case Device::passwordMakeup:
									paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *DATA* community string*PASSWORD* did not meet the complexity requirements."));
									break;
								case Device::passwordUsername:
									paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *DATA* community string*PASSWORD* was based on the username."));
									break;
								case Device::passwordHostname:
									paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *DATA* community string*PASSWORD* was based on the device name."));
									break;
								case Device::passwordDictSubst:
									paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *DATA* community string*PASSWORD* was dictionary-based with common character substitution."));
									break;
								case Device::passwordDictAppend:
									paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *DATA* community string*PASSWORD* was dictionary-based with characters appended."));
									break;
								default:
									paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *DATA* community string*PASSWORD* contained a common character sequence."));
									break;
							}
							break;
						default:
							paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the default *DATA* community string*PASSWORD* was configured."));
							break;
					}
				}
			}
			snmpCommunityPointer = snmpCommunityPointer->next;
		}
		if ((communityRequiresHosts == false) && (hostShowCommunity == true))
		{
			snmpHostPointer = snmpHost;
			while (snmpHostPointer != 0)
			{
				if (((snmpHostPointer->communityWeak != Device::passwordPassed) && (communityIssue == communityIssueWeak)) || ((snmpHostPointer->communityInDict == true) && (communityIssue == communityIssueDict)))
				{
					errorCode = device->addString(paragraphPointer, snmpHostPointer->host.c_str());
					if (errorCode != 0)
						return errorCode;
					errorCode = device->addString(paragraphPointer, snmpHostPointer->networkMask.c_str());
					if (errorCode != 0)
						return errorCode;
					errorCode = device->addString(paragraphPointer, snmpHostPointer->community.c_str());
					if (errorCode != 0)
						return errorCode;
					switch (communityIssue)
					{
						case communityIssueDict:
							paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *ABBREV*NMS*-ABBREV* Host *DATA* *DATA* community string*PASSWORD* was dictionary-based."));
							break;
						default:
							switch (snmpCommunityPointer->communityWeak)
							{
								case Device::passwordShort:
									paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *ABBREV*NMS*-ABBREV* Host *DATA* *DATA* community string*PASSWORD* was too short."));
									break;
								case Device::passwordRepeatChars:
									paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *ABBREV*NMS*-ABBREV* Host *DATA* *DATA* community string*PASSWORD* contained too many repeated characters."));
									break;
								case Device::passwordMakeup:
									paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *ABBREV*NMS*-ABBREV* Host *DATA* *DATA* community string*PASSWORD* did not meet the complexity requirements."));
									break;
								case Device::passwordUsername:
									paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *ABBREV*NMS*-ABBREV* Host *DATA* *DATA* community string*PASSWORD* was based on the username."));
									break;
								case Device::passwordHostname:
									paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *ABBREV*NMS*-ABBREV* Host *DATA* *DATA* community string*PASSWORD* was based on the device name."));
									break;
								case Device::passwordDictSubst:
									paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *ABBREV*NMS*-ABBREV* Host *DATA* *DATA* community string*PASSWORD* was dictionary-based with common character substitution."));
									break;
								case Device::passwordDictAppend:
									paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *ABBREV*NMS*-ABBREV* Host *DATA* *DATA* community string*PASSWORD* was dictionary-based with characters appended."));
									break;
								default:
									paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *ABBREV*NMS*-ABBREV* Host *DATA* *DATA* community string*PASSWORD* contained a common character sequence."));
									break;
							}
							break;
					}
				}
				snmpHostPointer = snmpHostPointer->next;
			}
		}
	}

	// Issue impact...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("An attacker would find the information contained within the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* extremely useful as part of a targeted attack against *DEVICENAME* or the network. For example, the *ABBREV*MIB*-ABBREV* could provide the attacker with the exact *DEVICETYPE* *ABBREV*OS*-ABBREV* version which could then be compared against a vulnerability database, a specific exploit downloaded and the vulnerability exploited."));
	if ((withWriteCount > 0) || (withWriteAllCount > 0))
		paragraphPointer->paragraph.append(i18n(" Furthermore, with write access to the *ABBREV*SNMP*-ABBREV* *ABBREV*MIB*-ABBREV* an attacker could modify the devices configuration."));
	found = false;
	snmpCommunityPointer = community;
	while (snmpCommunityPointer != 0)
	{
		if ((((snmpCommunityPointer->communityWeak != Device::passwordPassed) && (communityIssue == communityIssueWeak)) || ((snmpCommunityPointer->communityInDict == true) && (communityIssue == communityIssueDict)) || ((snmpCommunityPointer->communityDefault == true) && (communityIssue == communityIssueDefault))) && (snmpCommunityPointer->enabled == true))
		{
			// Read/Write without view...
			if ((snmpCommunityPointer->type != communityReadOnly) && (securityIssuePointer->impactRating < 7) && (snmpCommunityPointer->view.empty()))
			{
				securityIssuePointer->impactRating = 7;		// High
				found = true;
			}

			// Read/Write with view...
			else if ((snmpCommunityPointer->type != communityReadOnly) && (securityIssuePointer->impactRating < 5))
			{
				securityIssuePointer->impactRating = 5;		// Medium
			}

			// Read Only without view...
			else if ((snmpCommunityPointer->type == communityReadOnly) && (securityIssuePointer->impactRating < 5) && (snmpCommunityPointer->view.empty()))
			{
				securityIssuePointer->impactRating = 5;		// Medium
				found = true;
			}

			// Read Only with view...
			else if ((snmpCommunityPointer->type == communityReadOnly) && (securityIssuePointer->impactRating < 4))
			{
				securityIssuePointer->impactRating = 3;		// Low
			}
		}
		snmpCommunityPointer = snmpCommunityPointer->next;
	}
	if ((communityRequiresHosts == false) && (hostShowCommunity == true))
	{
		snmpHostPointer = snmpHost;
		while (snmpHostPointer != 0)
		{
			if ((((snmpHostPointer->communityWeak != Device::passwordPassed) && (communityIssue == communityIssueWeak)) || ((snmpHostPointer->communityInDict == true) && (communityIssue == communityIssueDict))) && (securityIssuePointer->impactRating < 5))
				securityIssuePointer->impactRating = 5; // Medium
			snmpHostPointer = snmpHostPointer->next;
		}
	}

	if ((communityView == true) && (found == true))
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("Without an *ABBREV*SNMP*-ABBREV* view being configured for each community string, an attacker would not have a restricted view of the *ABBREV*MIB*-ABBREV*."));
	}

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	switch (communityIssue)
	{
		case communityIssueDict:
			paragraphPointer->paragraph.assign(i18n("The community strings were tested against a list of passwords that would typically be found in most attacker's password dictionaries. These password dictionaries can be downloaded from a number of different Internet sites. A number of the *ABBREV*SNMP*-ABBREV* service testing tools are capable of using a dictionary to guess a community string. Alternatively, an attacker could manually attempt to guess the community string using the *ABBREV*SNMP*-ABBREV* tools provided with their *ABBREV*OS*-ABBREV*."));
			securityIssuePointer->easeRating = 7;			// Easy
			break;
		case communityIssueWeak:
			paragraphPointer->paragraph.assign(i18n("The strength of the community strings were tested to ensure that they meet the minimum complexity requirements outlined in the recommendation. An attackers initial attempts to gain access to the *ABBREV*SNMP*-ABBREV* service would likely be with a dictionary attack using a dictionary of commonly used passwords and defaults. Once the attackers dictionary has been exhausted, a persistent attacker could attempt a brute-force attack in order to gain access. A number of *ABBREV*SNMP*-ABBREV* service testing tools are capable of performing a community string brute-force attack."));
			securityIssuePointer->easeRating = 5;			// Moderate
			break;
		default:
			securityIssuePointer->easeRating = 7;			// Easy
			paragraphPointer->paragraph.assign(i18n("Lists of default passwords, including community strings are widely available on the Internet and manufacturers will often detail default community strings in the documentation for their devices. Furthermore, a number of network scanning tools attempt to access *ABBREV*SNMP*-ABBREV* services using default community strings."));
			break;
	}
	found = false;
	if (communityFilter == true)
	{
		found = true;
		snmpCommunityPointer = community;
		while (snmpCommunityPointer != 0)
		{
			if ((((snmpCommunityPointer->communityWeak != Device::passwordPassed) && (communityIssue == communityIssueWeak)) || ((snmpCommunityPointer->communityInDict == true) && (communityIssue == communityIssueDict)) || ((snmpCommunityPointer->communityDefault == true) && (communityIssue == communityIssueDefault))) && (snmpCommunityPointer->enabled == true))
			{
				if (snmpCommunityPointer->filter.empty())
					found = false;
			}
			snmpCommunityPointer = snmpCommunityPointer->next;
		}
	}
	if ((communityRequiresHosts == false) && (hostShowCommunity == true) && (found == false) && (hostShowFilterID == true))
	{
		snmpHostPointer = snmpHost;
		while (snmpHostPointer != 0)
		{
			if (((snmpHostPointer->communityWeak != Device::passwordPassed) && (communityIssue == communityIssueWeak)) || ((snmpHostPointer->communityInDict == true) && (communityIssue == communityIssueDict)))
			{
				if (snmpHostPointer->filter.empty() == true)
					found = true;
			}
			snmpHostPointer = snmpHostPointer->next;
		}
	}
	if ((found == true) && (communityFilter == true))
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		errorCode = device->addString(paragraphPointer, snmpFilterText);
		if (errorCode != 0)
			return errorCode;
		securityIssuePointer->easeRating = 2;			// Challenging
		paragraphPointer->paragraph.append(i18n("*DATA* help to restrict *ABBREV*SNMP*-ABBREV* access from unauthorised network hosts. However, a skilled attacker may be able bypass any configured network filtering."));
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
	paragraphPointer->paragraph.append(i18n(" If access using community strings is required, *COMPANY* recommends that strong community strings should be configured, that is the community strings:"));
	errorCode = device->addPasswordRequirements(paragraphPointer);
	if (errorCode != 0)
		return errorCode;
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
	if (strlen(configSNMPCommunityText) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configSNMPCommunityText);
	}
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("It is worth noting that *ABBREV*SNMP*-ABBREV* community string authentication is not encrypted. Therefore *COMPANY* recommends that any configured community strings should not be similar to the authentication password for any other system or service."));

	// Conclusions text...
	if (totalCommunityCount > 1)
	{
		switch (communityIssue)
		{
			case communityIssueDict:
				securityIssuePointer->conLine.append(i18n("dictionary-based *ABBREV*SNMP*-ABBREV* community strings were configured"));
				break;
			case communityIssueWeak:
				securityIssuePointer->conLine.append(i18n("weak *ABBREV*SNMP*-ABBREV* community strings were configured"));
				break;
			default:
				securityIssuePointer->conLine.append(i18n("default *ABBREV*SNMP*-ABBREV* community strings were configured"));
				break;
		}
	}
	else
	{
		switch (communityIssue)
		{
			case communityIssueDict:
				securityIssuePointer->conLine.append(i18n("a dictionary-based *ABBREV*SNMP*-ABBREV* community string was configured"));
				break;
			case communityIssueWeak:
				securityIssuePointer->conLine.append(i18n("a weak *ABBREV*SNMP*-ABBREV* community string was configured"));
				break;
			default:
				securityIssuePointer->conLine.append(i18n("a default *ABBREV*SNMP*-ABBREV* community string was configured"));
				break;
		}
	}

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Configure strong community strings."));

	// Dependent issues...
	device->addDependency(securityIssuePointer, "GEN.SNMPCLEA.1");

	// Related issues...
	device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWRIT.1");
	if ((found == false) && (communityFilter == true))
		device->addRelatedIssue(securityIssuePointer, "GEN.SNMPFILT.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.SNMPWEFI.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.SNMPVIEW.1");

	return errorCode;
}


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


SNMP::snmpTrapHost *SNMP::addSNMPTrapHost()							// Add a new trap/inform host
{
	// Variables...
	snmpTrapHost *trapHostPointer = 0;

	// Create
	if (trapHost == 0)
	{
		trapHost = new (snmpTrapHost);
		trapHostPointer = trapHost;
	}
	else
	{
		trapHostPointer = trapHost;
		while (trapHostPointer->next != 0)
			trapHostPointer = trapHostPointer->next;
		trapHostPointer->next = new (snmpTrapHost);
		trapHostPointer = trapHostPointer->next;
	}

	// Init...
	trapHostPointer->trap = true;					// Trap (true) or Inform (false)
	trapHostPointer->version = 1;					// SNMP version
	trapHostPointer->snmpv3 = snmpV3NoAuth;		// SNMP version 3 auth type
	trapHostPointer->port = 162;					// UDP port to send to	
	trapHostPointer->communityInDict = false;		// Is it a dictionary-based community
	trapHostPointer->communityWeak = Device::passwordPassed;		// Is it a weak community
	trapHostPointer->next = 0;

	return trapHostPointer;
}


SNMP::snmpTrapHost *SNMP::getSNMPTrapHost(const char *hostName)		// Get a trap/inform host
{
	// Variables...
	snmpTrapHost *trapHostPointer = 0;
	bool found = false;

	// Find...
	trapHostPointer = trapHost;
	while ((trapHostPointer != 0) && (found == false))
	{
		if (trapHostPointer->host.compare(hostName) == 0)
			found = true;
		else
			trapHostPointer = trapHostPointer->next;
	}

	return trapHostPointer;
}


SNMP::snmpTrap *SNMP::addSNMPTrap()									// Add a Trap
{
	// Variables...
	snmpTrap *snmpTrapPointer = 0;

	// Create...
	if (traps == 0)
	{
		traps = new (snmpTrap);
		snmpTrapPointer = traps;
	}
	else
	{
		snmpTrapPointer = traps;
		while (snmpTrapPointer->next != 0)
			snmpTrapPointer = snmpTrapPointer->next;
		snmpTrapPointer->next = new (snmpTrap);
		snmpTrapPointer = snmpTrapPointer->next;
	}

	// Init...
	snmpTrapPointer->include = true;
	snmpTrapPointer->next = 0;

	return snmpTrapPointer;
}


SNMP::snmpTrap *SNMP::getSNMPTrap(const char *trapName)				// Get a trap
{
	// Variables...
	snmpTrap *snmpTrapPointer = traps;
	bool found = false;

	// Search...
	while ((snmpTrapPointer != 0) && (found == false))
	{
		if (snmpTrapPointer->trap.compare(trapName) == 0)
			found = true;
		else
			snmpTrapPointer = snmpTrapPointer->next;
	}

	return snmpTrapPointer;
}


int SNMP::generateTrapHostConfigReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	snmpTrapHost *trapHostPointer = trapHost;
	snmpTrap *snmpTrapPointer = traps;
	string tempString;
	int errorCode = 0;

	device->addPort("SNMP-Trap");

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s SNMP Traps And Informs\n", device->config->COL_BLUE, device->config->COL_RESET);

	// Init pointers...
	configReportPointer = device->getConfigSection("CONFIG-SNMP");
	paragraphPointer = device->addParagraph(configReportPointer);

	// Set subsection title...
	if (trapsOnly == true)
		paragraphPointer->paragraphTitle.assign(i18n("*ABBREV*SNMP*-ABBREV* Traps"));
	else
		paragraphPointer->paragraphTitle.assign(i18n("*ABBREV*SNMP*-ABBREV* Traps And Informs"));
	paragraphPointer->paragraph.assign(i18n("The *DEVICETYPE* *ABBREV*SNMP*-ABBREV* agent can be configured to send trap notifications to a *ABBREV*NMS*-ABBREV* or *ABBREV*SNMP*-ABBREV* manager host. Once a trap is sent, the *DEVICETYPE* agent assumes that the receiving host received the notification, no confirmation is expected."));
	if (trapsOnly == false)
		paragraphPointer->paragraph.append(i18n(" Inform notifications are similar to traps, but the receiving host is expected to confirm receipt of the notification. If a confirmation is not received the *DEVICETYPE* *ABBREV*SNMP*-ABBREV* agent can retry."));

	// Trap Host Table...
	if (trapHost != 0)
	{
		errorCode = device->addTable(paragraphPointer, "CONFIG-SNMPTRAPHOST-TABLE");
		if (errorCode != 0)
			return errorCode;
		if (trapsOnly == true)
			paragraphPointer->table->title = i18n("*ABBREV*SNMP*-ABBREV* trap hosts");
		else
			paragraphPointer->table->title = i18n("*ABBREV*SNMP*-ABBREV* trap and inform hosts");
		device->addTableHeading(paragraphPointer->table, i18n("Host"), false);
		if (trapsOnly == false)
			device->addTableHeading(paragraphPointer->table, i18n("Type"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Version"), false);
		if (trapsSNMPv3 == true)
			device->addTableHeading(paragraphPointer->table, i18n("Security"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Community"), true);
		if (trapsShowNotifications == true)
			device->addTableHeading(paragraphPointer->table, i18n("Notifications"), false);
		if (trapsShowEventLevel == true)
			device->addTableHeading(paragraphPointer->table, i18n("Events"), false);
		if (trapsShowPort == true)
			device->addTableHeading(paragraphPointer->table, i18n("Port"), false);
		if (trapsInterface == true)
			device->addTableHeading(paragraphPointer->table, trapsInterfaceText, false);

		while (trapHostPointer != 0)
		{
			device->addTableData(paragraphPointer->table, trapHostPointer->host.c_str());
			if (trapsOnly == false)
			{
				if (trapHostPointer->trap == true)
					device->addTableData(paragraphPointer->table, i18n("Trap"));
				else
					device->addTableData(paragraphPointer->table, i18n("Inform"));
			}
			switch (trapHostPointer->version)
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
			if (trapsSNMPv3 == true)
			{
				if (trapHostPointer->version < 3)
					device->addTableData(paragraphPointer->table, i18n("Community"));
				else
				{
					switch (trapHostPointer->snmpv3)
					{
						case snmpV3Auth:
							device->addTableData(paragraphPointer->table, i18n("Auth"));
							break;
						case snmpV3Priv:
							device->addTableData(paragraphPointer->table, i18n("Auth+Priv"));
							break;
						default:
							device->addTableData(paragraphPointer->table, i18n("No Auth"));
							break;
					}
				}
			}
			device->addTableData(paragraphPointer->table, trapHostPointer->community.c_str());
			if (trapsShowNotifications == true)
				device->addTableData(paragraphPointer->table, trapHostPointer->notification.c_str());
			if (trapsShowEventLevel == true)
				device->addTableData(paragraphPointer->table, trapHostPointer->eventLevel.c_str());
			if (trapsShowPort == true)
			{
				tempString.assign(device->intToString(trapHostPointer->port));
				device->addTableData(paragraphPointer->table, tempString.c_str());
			}
			if (trapsInterface == true)
				device->addTableData(paragraphPointer->table, trapHostPointer->interface.c_str());
			trapHostPointer = trapHostPointer->next;
		}
	}

	// Traps...
	if (traps != 0)
	{

		// Table headings...
		paragraphPointer = device->addParagraph(configReportPointer);
		errorCode = device->addTable(paragraphPointer, "CONFIG-SNMPTRAPS-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("*ABBREV*SNMP*-ABBREV* notifications");
		device->addTableHeading(paragraphPointer->table, i18n("Notification"), false);
		if (trapsShowOptions == true)
			device->addTableHeading(paragraphPointer->table, i18n("Options"), false);
		if (trapsShowExcluded == true)
			device->addTableHeading(paragraphPointer->table, i18n("Action"), false);

		// Table data...
		while (snmpTrapPointer != 0)
		{
			device->addTableData(paragraphPointer->table, snmpTrapPointer->trap.c_str());
			if (trapsShowOptions == true)
				device->addTableData(paragraphPointer->table, snmpTrapPointer->options.c_str());
			if (trapsShowExcluded == true)
			{
				if (snmpTrapPointer->include == true)
					device->addTableData(paragraphPointer->table, i18n("Include"));
				else
					device->addTableData(paragraphPointer->table, i18n("Exclude"));
			}
			snmpTrapPointer = snmpTrapPointer->next;
		}
	}

	return errorCode;
}


int SNMP::snmpTrapIssue(Device *device, snmpCommunitySec communityIssue, int trapCount, int informCount)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	snmpTrapHost *trapHostPointer = 0;
	string tempString;
	string trapString;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
	{
		if (communityIssue == communityIssueDict)
			printf("    %s*%s [ISSUE] Dictionary-based SNMP Trap/Inform\n", device->config->COL_BLUE, device->config->COL_RESET);
		else
			printf("    %s*%s [ISSUE] Weak SNMP Trap/Inform\n", device->config->COL_BLUE, device->config->COL_RESET);
	}

	// Issue heading and ratings...
	securityIssuePointer = device->addSecurityIssue();
	if (communityIssue == communityIssueDict)
	{
		if ((trapCount > 0) && (informCount > 0))
			securityIssuePointer->title.assign(i18n("Dictionary-Based *ABBREV*SNMP*-ABBREV* Traps And Informs"));
		else if (trapCount > 1)
			securityIssuePointer->title.assign(i18n("Dictionary-Based *ABBREV*SNMP*-ABBREV* Traps"));
		else if (trapCount > 0)
			securityIssuePointer->title.assign(i18n("Dictionary-Based *ABBREV*SNMP*-ABBREV* Trap"));
		else if (informCount > 1)
			securityIssuePointer->title.assign(i18n("Dictionary-Based *ABBREV*SNMP*-ABBREV* Informs"));
		else
			securityIssuePointer->title.assign(i18n("Dictionary-Based *ABBREV*SNMP*-ABBREV* Inform"));
		securityIssuePointer->reference.assign("GEN.SNMPTRDI.1");
		trapString.assign(i18n("dictionary-based"));
	}
	else
	{
		if ((trapCount > 0) && (informCount > 0))
			securityIssuePointer->title.assign(i18n("Weak *ABBREV*SNMP*-ABBREV* Traps And Informs"));
		else if (trapCount > 1)
			securityIssuePointer->title.assign(i18n("Weak *ABBREV*SNMP*-ABBREV* Traps"));
		else if (trapCount > 0)
			securityIssuePointer->title.assign(i18n("Weak *ABBREV*SNMP*-ABBREV* Trap"));
		else if (informCount > 1)
			securityIssuePointer->title.assign(i18n("Weak *ABBREV*SNMP*-ABBREV* Informs"));
		else
			securityIssuePointer->title.assign(i18n("Weak *ABBREV*SNMP*-ABBREV* Inform"));
		securityIssuePointer->reference.assign("GEN.SNMPTRWE.1");
		trapString.assign(i18n("weak"));
	}

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*ABBREV*SNMP*-ABBREV* traps and informs can be configured to send notifications to a *ABBREV*NMS*-ABBREV* or *ABBREV*SNMP*-ABBREV* management host. Trap notifications are sent without any confirmation of receipt from the receiving host, whilst with inform notifications the receiving host sends a confirmation of receipt. Community strings can be configured for traps and inform notifications to provide a method of authentication."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

	// Multiple...
	if ((trapCount + informCount) > 1)
	{
		if ((trapCount > 0) && (informCount > 0))
		{
			device->addValue(paragraphPointer, trapCount + informCount);
			device->addString(paragraphPointer, trapString.c_str());
			paragraphPointer->paragraph.assign(i18n("*COMPANY* identified *NUMBER* *DATA* trap and inform *ABBREV*SNMP*-ABBREV* community strings. These are listed in Table *TABLEREF*."));
		}
		else if (trapCount > 0)
		{
			device->addValue(paragraphPointer, trapCount);
			device->addString(paragraphPointer, trapString.c_str());
			paragraphPointer->paragraph.assign(i18n("*COMPANY* identified *NUMBER* *DATA* trap *ABBREV*SNMP*-ABBREV* community strings. These are listed in Table *TABLEREF*."));
		}
		else
		{
			device->addValue(paragraphPointer, informCount);
			device->addString(paragraphPointer, trapString.c_str());
			paragraphPointer->paragraph.assign(i18n("*COMPANY* identified *NUMBER* *DATA* inform *ABBREV*SNMP*-ABBREV* community strings. These are listed in Table *TABLEREF*."));
		}

		if (communityIssue == communityIssueDict)
			errorCode = device->addTable(paragraphPointer, "GEN-SNMPTRDI-TABLE");
		else
			errorCode = device->addTable(paragraphPointer, "GEN-SNMPTRWE-TABLE");
		if (errorCode != 0)
			return errorCode;

		if (communityIssue == communityIssueDict)
		{
			if ((trapCount > 0) && (informCount > 0))
				paragraphPointer->table->title.assign(i18n("Dictionary-Based *ABBREV*SNMP*-ABBREV* traps and informs"));
			else if (trapCount > 0)
				paragraphPointer->table->title.assign(i18n("Dictionary-Based *ABBREV*SNMP*-ABBREV* traps"));
			else
				paragraphPointer->table->title.assign(i18n("Dictionary-Based *ABBREV*SNMP*-ABBREV* informs"));
		}
		else
		{
			if ((trapCount > 0) && (informCount > 0))
				paragraphPointer->table->title.assign(i18n("Weak *ABBREV*SNMP*-ABBREV* traps And informs"));
			else if (trapCount > 0)
				paragraphPointer->table->title.assign(i18n("Weak *ABBREV*SNMP*-ABBREV* traps"));
			else
				paragraphPointer->table->title.assign(i18n("Weak *ABBREV*SNMP*-ABBREV* informs"));
		}

		device->addTableHeading(paragraphPointer->table, i18n("Host"), false);
		if (trapsOnly == false)
			device->addTableHeading(paragraphPointer->table, i18n("Type"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Version"), false);
		if (trapsSNMPv3 == true)
			device->addTableHeading(paragraphPointer->table, i18n("Security"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Community"), true);
		if (trapsShowNotifications == true)
			device->addTableHeading(paragraphPointer->table, i18n("Notifications"), false);
		if (trapsShowEventLevel == true)
			device->addTableHeading(paragraphPointer->table, i18n("Events"), false);
		if (trapsShowPort == true)
			device->addTableHeading(paragraphPointer->table, i18n("Port"), false);
		if (trapsInterface == true)
			device->addTableHeading(paragraphPointer->table, trapsInterfaceText, false);
		if (communityIssue == communityIssueWeak)
			device->addTableHeading(paragraphPointer->table, i18n("Issue"), false);

		trapHostPointer = trapHost;
		while (trapHostPointer != 0)
		{
			if (((communityIssue == communityIssueDict) && (trapHostPointer->communityInDict == true)) || ((communityIssue == communityIssueWeak) && (trapHostPointer->communityWeak != Device::passwordPassed)))
			{
				device->addTableData(paragraphPointer->table, trapHostPointer->host.c_str());
				if (trapsOnly == false)
				{
					if (trapHostPointer->trap == true)
						device->addTableData(paragraphPointer->table, i18n("Trap"));
					else
						device->addTableData(paragraphPointer->table, i18n("Inform"));
				}
				switch (trapHostPointer->version)
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
				if (trapsSNMPv3 == true)
				{
					if (trapHostPointer->version < 3)
						device->addTableData(paragraphPointer->table, i18n("Community"));
					else
					{
						switch (trapHostPointer->snmpv3)
						{
							case snmpV3Auth:
								device->addTableData(paragraphPointer->table, i18n("Auth"));
								break;
							case snmpV3Priv:
								device->addTableData(paragraphPointer->table, i18n("Auth+Priv"));
								break;
							default:
								device->addTableData(paragraphPointer->table, i18n("No Auth"));
								break;
						}
					}
				}
				device->addTableData(paragraphPointer->table, trapHostPointer->community.c_str());
				if (trapsShowNotifications == true)
					device->addTableData(paragraphPointer->table, trapHostPointer->notification.c_str());
				if (trapsShowEventLevel == true)
					device->addTableData(paragraphPointer->table, trapHostPointer->eventLevel.c_str());
				if (trapsShowPort == true)
				{
					tempString.assign(device->intToString(trapHostPointer->port));
					device->addTableData(paragraphPointer->table, tempString.c_str());
				}
				if (trapsInterface == true)
					device->addTableData(paragraphPointer->table, trapHostPointer->interface.c_str());
				if (communityIssue == communityIssueWeak)
				{
					switch (trapHostPointer->communityWeak)
					{
						case Device::passwordShort:
							device->addTableData(paragraphPointer->table, i18n("The community string was too short"));
							break;
						case Device::passwordRepeatChars:
							device->addTableData(paragraphPointer->table, i18n("Characters were repeated too often"));
							break;
						case Device::passwordMakeup:
							device->addTableData(paragraphPointer->table, i18n("The community string did not meet the complexity requirements"));
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
			trapHostPointer = trapHostPointer->next;
		}
	}

	// Single...
	else
	{
		if (trapCount > 0)
			device->addString(paragraphPointer, i18n("trap"));
		else
			device->addString(paragraphPointer, i18n("inform"));
		trapHostPointer = trapHost;
		while (trapHostPointer != 0)
		{
			if (((communityIssue == communityIssueDict) && (trapHostPointer->communityInDict == true)) || ((communityIssue == communityIssueWeak) && (trapHostPointer->communityWeak != Device::passwordPassed)))
			{
				device->addString(paragraphPointer, trapHostPointer->community.c_str());
				device->addString(paragraphPointer, trapHostPointer->host.c_str());
				if (communityIssue != communityIssueWeak)
					paragraphPointer->paragraph.assign(i18n("*COMPANY* determined the *DATA* community string*PASSWORD* for *HOST* was dictionary-based."));
				else
				{
					if (communityIssue == communityIssueWeak)
					{
						switch (trapHostPointer->communityWeak)
						{
							case Device::passwordShort:
								paragraphPointer->paragraph.assign(i18n("*COMPANY* determined the *DATA* community string*PASSWORD* for *HOST* was too short."));
								break;
							case Device::passwordRepeatChars:
								paragraphPointer->paragraph.assign(i18n("*COMPANY* determined the *DATA* community string*PASSWORD* for *HOST* was repeated too many characters."));
								break;
							case Device::passwordMakeup:
								paragraphPointer->paragraph.assign(i18n("*COMPANY* determined the *DATA* community string*PASSWORD* for *HOST* did not meet the complexity requirements."));
								break;
							case Device::passwordUsername:
								paragraphPointer->paragraph.assign(i18n("*COMPANY* determined the *DATA* community string*PASSWORD* for *HOST* was username-based."));
								break;
							case Device::passwordHostname:
								paragraphPointer->paragraph.assign(i18n("*COMPANY* determined the *DATA* community string*PASSWORD* for *HOST* was hostname-based"));
								break;
							case Device::passwordDictSubst:
								paragraphPointer->paragraph.assign(i18n("*COMPANY* determined the *DATA* community string*PASSWORD* for *HOST* was dictionary-based with character substitution."));
								break;
							case Device::passwordDictAppend:
								paragraphPointer->paragraph.assign(i18n("*COMPANY* determined the *DATA* community string*PASSWORD* for *HOST* was dictionary-based with characters appended."));
								break;
							default:
								paragraphPointer->paragraph.assign(i18n("*COMPANY* determined the *DATA* community string*PASSWORD* for *HOST* contained a common character sequence."));
								break;
						}
					}
				}
			}
			trapHostPointer = trapHostPointer->next;
		}
	}

	// Issue impact...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	device->addString(paragraphPointer, trapString.c_str());
	paragraphPointer->paragraph.assign(i18n("An attacker who had identified a *DATA* community string could flood the *ABBREV*NMS*-ABBREV* or *ABBREV*SNMP*-ABBREV* management host with false notification messages. The false notification messages could be used by an attacker to hide an attack within a flood of false notifications or as part of a *ABBREV*DoS*-ABBREV* attack."));
	securityIssuePointer->impactRating = 3;		// Low

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	paragraphPointer->paragraph.assign(i18n("*ABBREV*SNMP*-ABBREV* management tools are available on the Internet and some *ABBREV*OS*-ABBREV* install *ABBREV*SNMP*-ABBREV* management tools by default. Although the sending of notification messages is not usually the primary purpose of most of these tools, the configuration of these tools for sending notification messages is usually detailed in the tools documentation.")); 
	if (communityIssue == communityIssueDict)
		securityIssuePointer->easeRating = 6;				// Easy
	else
		securityIssuePointer->easeRating = 5;				// Moderate

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;					// Quick
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	if ((trapCount > 0) && (informCount > 0))
		tempString.assign(i18n("traps and informs"));
	else if (trapCount > 0)
		tempString.assign(i18n("traps"));
	else
		tempString.assign(i18n("informs"));
	device->addString(paragraphPointer, tempString.c_str());
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if not required, *ABBREV*SNMP*-ABBREV* should be disabled. However if the sending of *DATA* is required, *COMPANY* recommends that a strong community string should be configured to authenticate all notification messages with a *ABBREV*NMS*-ABBREV* or *ABBREV*SNMP*-ABBREV* management host. *COMPANY* recommends that the community strings:"));
	errorCode = device->addPasswordRequirements(paragraphPointer);
	if (errorCode != 0)
		return errorCode;
	if ((strlen(configSNMPTrapsText) > 0) && (trapCount > 0))
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configSNMPTrapsText);
	}
	if ((strlen(configSNMPInformsText) > 0) && (informCount > 0))
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configSNMPTrapsText);
	}
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("It is worth noting that *ABBREV*SNMP*-ABBREV* community string authentication is not encrypted. Therefore *COMPANY* recommends that any configured community strings should not be similar to the authentication password for any other system or service."));

	// Conclusions text...
	if (communityIssue == communityIssueDict)
	{
		if ((trapCount > 0) && (informCount > 0))
			securityIssuePointer->conLine.assign(i18n("Dictionary-based *ABBREV*SNMP*-ABBREV* traps and informs community strings were configured"));
		else if (trapCount > 1)
			securityIssuePointer->conLine.assign(i18n("Dictionary-based *ABBREV*SNMP*-ABBREV* trap community strings were configured"));
		else if (trapCount > 0)
			securityIssuePointer->conLine.assign(i18n("A dictionary-based *ABBREV*SNMP*-ABBREV* trap community string was configured"));
		else if (informCount > 1)
			securityIssuePointer->conLine.assign(i18n("Dictionary-based *ABBREV*SNMP*-ABBREV* inform community strings were configured"));
		else
			securityIssuePointer->conLine.assign(i18n("A dictionary-based *ABBREV*SNMP*-ABBREV* inform community string was configured"));
	}
	else
	{
		if ((trapCount > 0) && (informCount > 0))
			securityIssuePointer->conLine.assign(i18n("Weak *ABBREV*SNMP*-ABBREV* traps and informs community strings were configured"));
		else if (trapCount > 1)
			securityIssuePointer->conLine.assign(i18n("Weak *ABBREV*SNMP*-ABBREV* trap community strings were configured"));
		else if (trapCount > 0)
			securityIssuePointer->conLine.assign(i18n("A weak *ABBREV*SNMP*-ABBREV* trap community string was configured"));
		else if (informCount > 1)
			securityIssuePointer->conLine.assign(i18n("Weak *ABBREV*SNMP*-ABBREV* inform community strings were configured"));
		else
			securityIssuePointer->conLine.assign(i18n("A weak *ABBREV*SNMP*-ABBREV* inform community string was configured"));
	}

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Configure strong *ABBREV*SNMP*-ABBREV* notification community strings."));

	// Dependent issues...
	device->addDependency(securityIssuePointer, "GEN.SNMPCLEA.1");

	return errorCode;
}


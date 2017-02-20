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
 *      2. Any code that integrates Nipper MUST display the copyright      *
 *         information below with the programs own copyright information.  *
 *                                                                         *
 *         "Nipper Copyright (C) 2006 - 2008 by Ian Ventura-Whiting"       *
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
#include "authentication.h"
#include "../device.h"


Authentication::ldapServerConfig *Authentication::addLDAPServer()
{
	// Variables...
	ldapServerConfig *ldapPointer = 0;

	// Create...
	if (ldapServer == 0)
	{
		ldapServer = new (ldapServerConfig);
		ldapPointer = ldapServer;
	}
	else
	{
		ldapPointer = ldapServer;
		while (ldapPointer->next != 0)
			ldapPointer = ldapPointer->next;
		ldapPointer->next = new (ldapServerConfig);
		ldapPointer = ldapPointer->next;
	}

	// Init...
	ldapPointer->timeout = 0;
	ldapPointer->retries = 0;
	ldapPointer->port = 389;
	ldapPointer->encryption = clearText;
	ldapPointer->dictionaryPassword = false;
	ldapPointer->weakPassword = Device::passwordPassed;
	ldapPointer->next = 0;

	return ldapPointer;
}


int Authentication::generateConfigLDAPReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	ldapServerConfig *ldapPointer = 0;
	string tempString;
	int errorCode = 0;

	configReportPointer = device->getConfigSection("CONFIG-AUTH");
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraphTitle.assign(i18n("*ABBREV*LDAP*-ABBREV* Configuration"));
	paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices support authentication with *ABBREV*LDAP*-ABBREV* servers. This section details the configuration."));

	// Local Users Table...
	errorCode = device->addTable(paragraphPointer, "CONFIG-AUTHLDAP-TABLE");
	if (errorCode != 0)
		return errorCode;
	paragraphPointer->table->title = i18n("*ABBREV*LDAP*-ABBREV* servers");
	if (showLDAPGroupName == true)
		device->addTableHeading(paragraphPointer->table, i18n("Server Group"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Address"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Port"), false);
	device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*CN*-ABBREV*"), false);
	device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*DN*-ABBREV*"), false);
	if (showLDAPPassword == true)
		device->addTableHeading(paragraphPointer->table, i18n("Password"), true);
	device->addTableHeading(paragraphPointer->table, i18n("Timeout"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Retries"), false);

	ldapPointer = ldapServer;
	while (ldapPointer != 0)
	{
		if (showLDAPGroupName == true)
			device->addTableData(paragraphPointer->table, ldapPointer->groupName.c_str());
		device->addTableData(paragraphPointer->table, ldapPointer->description.c_str());
		device->addTableData(paragraphPointer->table, ldapPointer->address.c_str());
		tempString.assign(device->intToString(ldapPointer->port));
		device->addTableData(paragraphPointer->table, tempString.c_str());
		device->addTableData(paragraphPointer->table, ldapPointer->cn.c_str());
		device->addTableData(paragraphPointer->table, ldapPointer->dn.c_str());
		if (showLDAPPassword == true)
			device->addTableData(paragraphPointer->table, ldapPointer->password.c_str());
		tempString.assign(device->timeToString(ldapPointer->timeout));
		device->addTableData(paragraphPointer->table, tempString.c_str());
		tempString.assign(device->intToString(ldapPointer->retries));
		device->addTableData(paragraphPointer->table, tempString.c_str());
		ldapPointer = ldapPointer->next;
	}

	return 0;
}


int Authentication::generateLDAPSecurityReport(Device *device, int dictionary, int weak)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	ldapServerConfig *ldapPointer = 0;
	string tempString;
	int errorCode = 0;

	if (dictionary > 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] LDAP Server With Dictionary Based Passwords\n", device->config->COL_BLUE, device->config->COL_RESET);
		securityIssuePointer = device->addSecurityIssue();
		if (dictionary > 1)
			securityIssuePointer->title.assign(i18n("Dictionary Based *ABBREV*LDAP*-ABBREV* Server Passwords"));
		else
			securityIssuePointer->title.assign(i18n("Dictionary Based *ABBREV*LDAP*-ABBREV* Server Password"));
		securityIssuePointer->reference.assign("GEN.AUTHDLDA.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("A *ABBREV*LDAP*-ABBREV* server provides remote authentication services for network connected devices such as *DEVICETYPE* devices. Authentication requests are sent to the *ABBREV*LDAP*-ABBREV* server and a access response is returned to the device."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

		// Multiple found...
		if (dictionary > 1)
		{
			device->addValue(paragraphPointer, dictionary);
			paragraphPointer->paragraph.assign(i18n("The *ABBREV*LDAP*-ABBREV* server authentication password was checked against a dictionary of common passwords. *COMPANY* determined that *NUMBER* *ABBREV*LDAP*-ABBREV* server passwords were dictionary-based. These servers are listed in Table *TABLEREF*."));

			errorCode = device->addTable(paragraphPointer, "SECURITY-DICTLDAPPASS-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("Dictionary based *ABBREV*LDAP*-ABBREV* server passwords");
		}

		// One found...
		else
		{
			device->addValue(paragraphPointer, dictionary);
			paragraphPointer->paragraph.assign(i18n("The *ABBREV*LDAP*-ABBREV* server authentication password was checked against a dictionary of common passwords. *COMPANY* determined that *NUMBER* *ABBREV*LDAP*-ABBREV* server password was dictionary-based. This server is shown in Table *TABLEREF*."));

			errorCode = device->addTable(paragraphPointer, "SECURITY-DICTLDAPPASS-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("Dictionary based *ABBREV*LDAP*-ABBREV* server password");
		}

		if (showLDAPGroupName == true)
			device->addTableHeading(paragraphPointer->table, i18n("Server Group"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Address"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Port"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*CN*-ABBREV*"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*DN*-ABBREV*"), false);
		if (showLDAPPassword == true)
			device->addTableHeading(paragraphPointer->table, i18n("Password"), true);
		device->addTableHeading(paragraphPointer->table, i18n("Timeout"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Retries"), false);

		ldapPointer = ldapServer;
		while (ldapPointer != 0)
		{
			if (ldapPointer->dictionaryPassword == true)
			{
				if (showLDAPGroupName == true)
					device->addTableData(paragraphPointer->table, ldapPointer->groupName.c_str());
				device->addTableData(paragraphPointer->table, ldapPointer->description.c_str());
				device->addTableData(paragraphPointer->table, ldapPointer->address.c_str());
				tempString.assign(device->intToString(ldapPointer->port));
				device->addTableData(paragraphPointer->table, tempString.c_str());
				device->addTableData(paragraphPointer->table, ldapPointer->cn.c_str());
				device->addTableData(paragraphPointer->table, ldapPointer->dn.c_str());
				if (showLDAPPassword == true)
					device->addTableData(paragraphPointer->table, ldapPointer->password.c_str());
				tempString.assign(device->timeToString(ldapPointer->timeout));
				device->addTableData(paragraphPointer->table, tempString.c_str());
				tempString.assign(device->intToString(ldapPointer->retries));
				device->addTableData(paragraphPointer->table, tempString.c_str());
			}
			ldapPointer = ldapPointer->next;
		}

		// Issue impact...
		securityIssuePointer->impactRating = 7;				// High
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("An attacker who was able to access the *ABBREV*LDAP*-ABBREV* server may be able to gain access using a dictionary-based attack."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 4;				// Moderate
		paragraphPointer->paragraph.assign(i18n("A variety of tools are available on the Internet that are specifically designed attack *ABBREV*LDAP*-ABBREV* servers."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 4;				// Planned
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that a strong *ABBREV*LDAP*-ABBREV* server password should be configured. *COMPANY* recommends that the password:"));
		errorCode = device->addPasswordRequirements(paragraphPointer);
		if (errorCode != 0)
			return errorCode;
		if (strlen(configLDAPPassword) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(configLDAPPassword);
		}

		// Conclusions text...
		if (dictionary > 1)
			securityIssuePointer->conLine.append(i18n("*ABBREV*LDAP*-ABBREV* servers were configured with dictionary-based password"));
		else
			securityIssuePointer->conLine.append(i18n("a *ABBREV*LDAP*-ABBREV* server was configured with a dictionary-based password"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Configure strong *ABBREV*LDAP*-ABBREV* server passwords for all *ABBREV*LDAP*-ABBREV* servers"));

		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHNPAS.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHDPAS.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHWPAS.1");
	}


	if (weak > 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] LDAP Server With Weak Passwords\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		if (weak > 1)
			securityIssuePointer->title.assign(i18n("Weak *ABBREV*LDAP*-ABBREV* Server Passwords"));
		else
			securityIssuePointer->title.assign(i18n("Weak *ABBREV*LDAP*-ABBREV* Server Password"));
		securityIssuePointer->reference.assign("GEN.AUTHWLDA.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("A *ABBREV*LDAP*-ABBREV* server provides remote authentication services for network connected devices such as *DEVICETYPE* devices. Authentication requests are sent to the *ABBREV*LDAP*-ABBREV* server and a access response is returned to the device."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

		// Multiple found...
		if (weak > 1)
		{
			device->addValue(paragraphPointer, weak);
			paragraphPointer->paragraph.assign(i18n("The *ABBREV*LDAP*-ABBREV* server authentication password strength was checked against the password criteria outlined in the recommendations. *COMPANY* determined that *NUMBER* *ABBREV*LDAP*-ABBREV* server passwords were weak. These servers are listed in Table *TABLEREF*."));

			errorCode = device->addTable(paragraphPointer, "SECURITY-WEAKLDAPPASS-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("Weak *ABBREV*LDAP*-ABBREV* server passwords");
		}

		// One found...
		else
		{
			device->addValue(paragraphPointer, weak);
			paragraphPointer->paragraph.assign(i18n("The *ABBREV*LDAP*-ABBREV* server authentication password strength was checked against the password criteria outlined in the recommendations. *COMPANY* determined that *NUMBER* *ABBREV*LDAP*-ABBREV* server password was weak. This server is shown in Table *TABLEREF*."));

			errorCode = device->addTable(paragraphPointer, "SECURITY-WEAKLDAPPASS-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("Weak *ABBREV*LDAP*-ABBREV* server password");
		}

		if (showLDAPGroupName == true)
			device->addTableHeading(paragraphPointer->table, i18n("Server Group"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Address"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Port"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*CN*-ABBREV*"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*DN*-ABBREV*"), false);
		if (showLDAPPassword == true)
			device->addTableHeading(paragraphPointer->table, i18n("Password"), true);
		device->addTableHeading(paragraphPointer->table, i18n("Description"), false);

		ldapPointer = ldapServer;
		while (ldapPointer != 0)
		{
			if (ldapPointer->weakPassword != Device::passwordPassed)
			{
				if (showLDAPGroupName == true)
					device->addTableData(paragraphPointer->table, ldapPointer->groupName.c_str());
				device->addTableData(paragraphPointer->table, ldapPointer->description.c_str());
				device->addTableData(paragraphPointer->table, ldapPointer->address.c_str());
				tempString.assign(device->intToString(ldapPointer->port));
				device->addTableData(paragraphPointer->table, tempString.c_str());
				device->addTableData(paragraphPointer->table, ldapPointer->cn.c_str());
				device->addTableData(paragraphPointer->table, ldapPointer->dn.c_str());
				if (showLDAPPassword == true)
					device->addTableData(paragraphPointer->table, ldapPointer->password.c_str());
				switch (ldapPointer->weakPassword)
				{
					case Device::passwordShort:
						device->addTableData(paragraphPointer->table, i18n("The password was too short"));
						break;
					case Device::passwordRepeatChars:
						device->addTableData(paragraphPointer->table, i18n("The passwords characters were repeated too often"));
						break;
					case Device::passwordMakeup:
						device->addTableData(paragraphPointer->table, i18n("The password did not meet the minimum complexity requirements"));
						break;
					case Device::passwordUsername:
						device->addTableData(paragraphPointer->table, i18n("The username was part of the password"));
						break;
					case Device::passwordHostname:
						device->addTableData(paragraphPointer->table, i18n("The device hostname was part of the password"));
						break;
					case Device::passwordDictSubst:
						device->addTableData(paragraphPointer->table, i18n("The password was dictionary-based with character substitution"));
						break;
					case Device::passwordDictAppend:
						device->addTableData(paragraphPointer->table, i18n("The password was dictionary-based with characters appended"));
						break;
					default:
						device->addTableData(paragraphPointer->table, i18n("The password contains a common character sequence"));
						break;
				}
			}
			ldapPointer = ldapPointer->next;
		}

		// Issue impact...
		securityIssuePointer->impactRating = 7;				// High
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("An attacker who was able to access the *ABBREV*LDAP*-ABBREV* server may be able to gain access using a brute-force attack."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 5;				// Moderate
		paragraphPointer->paragraph.assign(i18n("A variety of tools are available on the Internet that are specifically designed attack *ABBREV*LDAP*-ABBREV* servers. Although brute-forcing passwords can be time consuming, stronger passwords take exponentially longer to break than weaker ones."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 4;				// Planned
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that a strong *ABBREV*LDAP*-ABBREV* server password should be configured. *COMPANY* recommends that the password:"));
		errorCode = device->addPasswordRequirements(paragraphPointer);
		if (errorCode != 0)
			return errorCode;
		if (strlen(configLDAPPassword) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(configLDAPPassword);
		}

		// Conclusions text...
		if (weak > 1)
			securityIssuePointer->conLine.append(i18n("*ABBREV*LDAP*-ABBREV* servers were configured with dictionary-based password"));
		else
			securityIssuePointer->conLine.append(i18n("a *ABBREV*LDAP*-ABBREV* server was configured with a dictionary-based password"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Configure strong *ABBREV*LDAP*-ABBREV* server passwords for all *ABBREV*LDAP*-ABBREV* servers"));

		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHNPAS.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHDPAS.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHWPAS.1");
	}

	return 0;
}

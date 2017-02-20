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


Authentication::radiusServerConfig *Authentication::addRadiusServer()
{
	// Variables...
	radiusServerConfig *radiusPointer = 0;

	// Create...
	if (radiusServer == 0)
	{
		radiusServer = new (radiusServerConfig);
		radiusPointer = radiusServer;
	}
	else
	{
		radiusPointer = radiusServer;
		while (radiusPointer->next != 0)
			radiusPointer = radiusPointer->next;
		radiusPointer->next = new (radiusServerConfig);
		radiusPointer = radiusPointer->next;
	}

	// Init...
	radiusPointer->timeout = 0;
	radiusPointer->retries = 0;
	radiusPointer->port = 1645;
	radiusPointer->encryption = clearText;
	radiusPointer->dictionaryKey = false;
	radiusPointer->weakKey = Device::passwordPassed;
	radiusPointer->next = 0;

	return radiusPointer;
}


int Authentication::generateConfigRadiusReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	radiusServerConfig *radiusPointer = 0;
	string tempString;
	int errorCode = 0;

	configReportPointer = device->getConfigSection("CONFIG-AUTH");
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraphTitle.assign(i18n("*ABBREV*RADIUS*-ABBREV* Configuration"));
	paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices support authentication with *ABBREV*RADIUS*-ABBREV* servers. This section details the configuration."));

	// RADIUS Table...
	errorCode = device->addTable(paragraphPointer, "CONFIG-AUTHRADIUS-TABLE");
	if (errorCode != 0)
		return errorCode;
	paragraphPointer->table->title = i18n("*ABBREV*RADIUS*-ABBREV* servers");
	if (showRadiusGroupName == true)
		device->addTableHeading(paragraphPointer->table, i18n("Server Group"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Address"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Port"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Secret"), true);
	device->addTableHeading(paragraphPointer->table, i18n("Timeout"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Retries"), false);

	radiusPointer = radiusServer;
	while (radiusPointer != 0)
	{
		if (showRadiusGroupName == true)
			device->addTableData(paragraphPointer->table, radiusPointer->groupName.c_str());
		device->addTableData(paragraphPointer->table, radiusPointer->description.c_str());
		device->addTableData(paragraphPointer->table, radiusPointer->address.c_str());
		tempString.assign(device->intToString(radiusPointer->port));
		device->addTableData(paragraphPointer->table, tempString.c_str());
		device->addTableData(paragraphPointer->table, radiusPointer->key.c_str());
		tempString.assign(device->timeToString(radiusPointer->timeout));
		device->addTableData(paragraphPointer->table, tempString.c_str());
		tempString.assign(device->intToString(radiusPointer->retries));
		device->addTableData(paragraphPointer->table, tempString.c_str());
		radiusPointer = radiusPointer->next;
	}

	return 0;
}


int Authentication::generateRadiusSecurityReport(Device *device, int empty, int dictionary, int weak)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	radiusServerConfig *radiusPointer = 0;
	string tempString;
	int errorCode = 0;

	if (empty > 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] RADIUS Servers With No Shared Secret\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		if (empty > 1)
			securityIssuePointer->title.assign(i18n("*ABBREV*RADIUS*-ABBREV* Servers Configured With No Key"));
		else
			securityIssuePointer->title.assign(i18n("*ABBREV*RADIUS*-ABBREV* Server Configured With No Key"));
		securityIssuePointer->reference.assign("GEN.AUTHNRAD.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("A *ABBREV*RADIUS*-ABBREV* server provides *ABBREV*AAA*-ABBREV* services for network connected devices such as *DEVICETYPE* devices. Authentication requests are sent to the *ABBREV*RADIUS*-ABBREV* server and a access response is returned to the device. A *ABBREV*RADIUS*-ABBREV* key can be configured to encrypt the traffic between the service and requesting device."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

		// Multiple found...
		if (empty > 1)
		{
			device->addValue(paragraphPointer, empty);
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *ABBREV*RADIUS*-ABBREV* servers were configured without a key to encrypt the authentication traffic. These servers are listed in Table *TABLEREF*."));

			errorCode = device->addTable(paragraphPointer, "SECURITY-NORADIUSKEYS-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("*ABBREV*RADIUS*-ABBREV* servers with no encryption key");
		}

		// One found...
		else
		{
			device->addValue(paragraphPointer, empty);
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *ABBREV*RADIUS*-ABBREV* server was configured without a key to encrypt the authentication traffic. This server is shown in Table *TABLEREF*."));

			errorCode = device->addTable(paragraphPointer, "SECURITY-NORADIUSKEY-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("*ABBREV*RADIUS*-ABBREV* server with no encryption key");
		}

		if (showTacacsGroupName == true)
			device->addTableHeading(paragraphPointer->table, i18n("Server Group"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Address"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Port"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Timeout"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Retries"), false);

		radiusPointer = radiusServer;
		while (radiusPointer != 0)
		{
			if (radiusPointer->key.empty())
			{
				if (showTacacsGroupName == true)
					device->addTableData(paragraphPointer->table, radiusPointer->groupName.c_str());
				device->addTableData(paragraphPointer->table, radiusPointer->description.c_str());
				device->addTableData(paragraphPointer->table, radiusPointer->address.c_str());
				tempString.assign(device->intToString(radiusPointer->port));
				device->addTableData(paragraphPointer->table, tempString.c_str());
				tempString.assign(device->timeToString(radiusPointer->timeout));
				device->addTableData(paragraphPointer->table, tempString.c_str());
				tempString.assign(device->intToString(radiusPointer->retries));
				device->addTableData(paragraphPointer->table, tempString.c_str());
			}
			radiusPointer = radiusPointer->next;
		}

		// Issue impact...
		securityIssuePointer->impactRating = 8;				// High
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("An attacker who is able to monitor the network traffic between the *ABBREV*RADIUS*-ABBREV* server and *DEVICENAME* could extract authentication credentials from the traffic. The attacker could then use the authentication credentials in order to gain a level of access to *DEVICENAME*."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 6;				// Ease
		paragraphPointer->paragraph.assign(i18n("Network packet and password sniffing tools are widely available on the Internet. In a switched environment an attacker may not be able to capture network traffic destined for other devices without performing an additional attack, such as exploiting *ABBREV*ARP*-ABBREV* or routing vulnerabilities."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 4;				// Planned
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that a strong *ABBREV*RADIUS*-ABBREV* server key should be configured to encrypt the authentication traffic between the device and the *ABBREV*RADIUS*-ABBREV* server. This key will have to be configured on the *ABBREV*RADIUS*-ABBREV* server and *DEVICENAME*. *COMPANY* recommends that passwords:"));
		errorCode = device->addPasswordRequirements(paragraphPointer);
		if (errorCode != 0)
			return errorCode;
		if (strlen(configRadiusKey) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(configRadiusKey);
		}

		// Conclusions text...
		if (empty > 1)
			securityIssuePointer->conLine.append(i18n("*ABBREV*RADIUS*-ABBREV* servers were configured with no keys"));
		else
			securityIssuePointer->conLine.append(i18n("a *ABBREV*RADIUS*-ABBREV* server was configured with no key"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Configure strong *ABBREV*RADIUS*-ABBREV* server keys for all *ABBREV*RADIUS*-ABBREV* servers"));

		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHNPAS.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHDPAS.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHWPAS.1");
	}

	if (dictionary > 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] RADIUS Servers With Dictionary Based Shared Secret\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		if (dictionary > 1)
			securityIssuePointer->title.assign(i18n("Dictionary Based *ABBREV*RADIUS*-ABBREV* Server Keys"));
		else
			securityIssuePointer->title.assign(i18n("Dictionary Based *ABBREV*RADIUS*-ABBREV* Server Key"));
		securityIssuePointer->reference.assign("GEN.AUTHDTAC.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("A *ABBREV*RADIUS*-ABBREV* server provides *ABBREV*AAA*-ABBREV* services for network connected devices such as *DEVICETYPE* devices. Authentication requests are sent to the *ABBREV*RADIUS*-ABBREV* server and a access response is returned to the device. A *ABBREV*RADIUS*-ABBREV* key can be configured to encrypt the traffic between the service and requesting device."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

		// Multiple found...
		if (dictionary > 1)
		{
			device->addValue(paragraphPointer, dictionary);
			paragraphPointer->paragraph.assign(i18n("The *ABBREV*RADIUS*-ABBREV* server key was checked against a dictionary of common passwords. *COMPANY* determined that *NUMBER* *ABBREV*RADIUS*-ABBREV* server keys were dictionary-based. These servers are listed in Table *TABLEREF*."));

			errorCode = device->addTable(paragraphPointer, "SECURITY-DICTRADIUSKEYS-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("Dictionary based *ABBREV*RADIUS*-ABBREV* server keys");
		}

		// One found...
		else
		{
			device->addValue(paragraphPointer, dictionary);
			paragraphPointer->paragraph.assign(i18n("The *ABBREV*RADIUS*-ABBREV* server key was checked against a dictionary of common passwords. *COMPANY* determined that *NUMBER* *ABBREV*RADIUS*-ABBREV* server key was dictionary-based. This server is shown in Table *TABLEREF*."));

			errorCode = device->addTable(paragraphPointer, "SECURITY-DICTRADIUSKEY-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("Dictionary based *ABBREV*RADIUS*-ABBREV* server key");
		}

		if (showTacacsGroupName == true)
			device->addTableHeading(paragraphPointer->table, i18n("Server Group"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Address"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Port"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Key"), true);
		device->addTableHeading(paragraphPointer->table, i18n("Timeout"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Retries"), false);

		radiusPointer = radiusServer;
		while (radiusPointer != 0)
		{
			if (radiusPointer->dictionaryKey == true)
			{
				if (showTacacsGroupName == true)
					device->addTableData(paragraphPointer->table, radiusPointer->groupName.c_str());
				device->addTableData(paragraphPointer->table, radiusPointer->description.c_str());
				device->addTableData(paragraphPointer->table, radiusPointer->address.c_str());
				tempString.assign(device->intToString(radiusPointer->port));
				device->addTableData(paragraphPointer->table, tempString.c_str());
				device->addTableData(paragraphPointer->table, radiusPointer->key.c_str());
				tempString.assign(device->timeToString(radiusPointer->timeout));
				device->addTableData(paragraphPointer->table, tempString.c_str());
				tempString.assign(device->intToString(radiusPointer->retries));
				device->addTableData(paragraphPointer->table, tempString.c_str());
			}
			radiusPointer = radiusPointer->next;
		}

		// Issue impact...
		securityIssuePointer->impactRating = 8;				// High
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("An attacker who was able to monitor the authentication traffic could attempt to break the encryption using a dictionary-based attack. If the attack is able to decrypt the encryption they could extract authentication credentials from the traffic. The attacker could then use the authentication credentials in order to gain a level of access to *DEVICENAME*."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 4;				// Moderate
		paragraphPointer->paragraph.assign(i18n("A variety of tools are available on the Internet that are specifically designed to break encryption. Furthermore, Open Source *ABBREV*RADIUS*-ABBREV* code could be used as the basis of a custom encryption breaking routine. Network packet and password sniffing tools are widely available on the Internet. In a switched environment an attacker may not be able to capture network traffic destined for other devices without performing an additional attack, such as exploiting *ABBREV*ARP*-ABBREV* or routing vulnerabilities."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 4;				// Planned
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that a strong *ABBREV*RADIUS*-ABBREV* server key should be configured to encrypt the authentication traffic between the device and the *ABBREV*RADIUS*-ABBREV* server. This key will have to be configured on the *ABBREV*RADIUS*-ABBREV* server and *DEVICENAME*. *COMPANY* recommends that passwords:"));
		errorCode = device->addPasswordRequirements(paragraphPointer);
		if (errorCode != 0)
			return errorCode;
		if (strlen(configRadiusKey) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(configRadiusKey);
		}

		// Conclusions text...
		if (dictionary > 1)
			securityIssuePointer->conLine.append(i18n("*ABBREV*RADIUS*-ABBREV* servers were configured with dictionary-based keys"));
		else
			securityIssuePointer->conLine.append(i18n("a *ABBREV*RADIUS*-ABBREV* server was configured with a dictionary-based key"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Configure strong *ABBREV*RADIUS*-ABBREV* server keys for all *ABBREV*RADIUS*-ABBREV* servers"));

		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHNPAS.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHDPAS.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHWPAS.1");
	}

	if (weak > 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] RADIUS Servers With Weak Shared Secret\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		if (weak > 1)
			securityIssuePointer->title.assign(i18n("Weak *ABBREV*RADIUS*-ABBREV* Server Keys"));
		else
			securityIssuePointer->title.assign(i18n("Weak *ABBREV*RADIUS*-ABBREV* Server Key"));
		securityIssuePointer->reference.assign("GEN.AUTHWTAC.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("A *ABBREV*RADIUS*-ABBREV* server provides *ABBREV*AAA*-ABBREV* services for network connected devices such as *DEVICETYPE* devices. Authentication requests are sent to the *ABBREV*RADIUS*-ABBREV* server and a access response is returned to the device. A *ABBREV*RADIUS*-ABBREV* key can be configured to encrypt the traffic between the service and requesting device."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

		// Multiple found...
		if (weak > 1)
		{
			device->addValue(paragraphPointer, weak);
			paragraphPointer->paragraph.assign(i18n("The *ABBREV*RADIUS*-ABBREV* server keys were tested to check their strength against the criteria outlined in the recommendations. *COMPANY* determined that *NUMBER* *ABBREV*RADIUS*-ABBREV* server keys were weak. These servers are listed in Table *TABLEREF*."));

			errorCode = device->addTable(paragraphPointer, "SECURITY-WEAKRADIUSKEYS-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("Weak *ABBREV*RADIUS*-ABBREV* server keys");
		}

		// One found...
		else
		{
			device->addValue(paragraphPointer, weak);
			paragraphPointer->paragraph.assign(i18n("The *ABBREV*RADIUS*-ABBREV* server keys were tested to check their strength against the criteria outlined in the recommendations. *COMPANY* determined that *NUMBER* *ABBREV*RADIUS*-ABBREV* server key was weak. This server is shown in Table *TABLEREF*."));

			errorCode = device->addTable(paragraphPointer, "SECURITY-WEAKRADIUSKEY-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("Weak *ABBREV*RADIUS*-ABBREV* server key");
		}

		if (showTacacsGroupName == true)
			device->addTableHeading(paragraphPointer->table, i18n("Server Group"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Address"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Port"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Key"), true);
		device->addTableHeading(paragraphPointer->table, i18n("Description"), false);

		radiusPointer = radiusServer;
		while (radiusPointer != 0)
		{
			if (radiusPointer->weakKey != Device::passwordPassed)
			{
				if (showTacacsGroupName == true)
					device->addTableData(paragraphPointer->table, radiusPointer->groupName.c_str());
				device->addTableData(paragraphPointer->table, radiusPointer->description.c_str());
				device->addTableData(paragraphPointer->table, radiusPointer->address.c_str());
				tempString.assign(device->intToString(radiusPointer->port));
				device->addTableData(paragraphPointer->table, tempString.c_str());
				device->addTableData(paragraphPointer->table, radiusPointer->key.c_str());
				switch (radiusPointer->weakKey)
				{
					case Device::passwordShort:
						device->addTableData(paragraphPointer->table, i18n("The key was too short"));
						break;
					case Device::passwordRepeatChars:
						device->addTableData(paragraphPointer->table, i18n("The keys characters were repeated too often"));
						break;
					case Device::passwordMakeup:
						device->addTableData(paragraphPointer->table, i18n("The key did not meet the minimum complexity requirements"));
						break;
					case Device::passwordUsername:
						device->addTableData(paragraphPointer->table, i18n("The service name was part of the key"));
						break;
					case Device::passwordHostname:
						device->addTableData(paragraphPointer->table, i18n("The device hostname was part of the key"));
						break;
					case Device::passwordDictSubst:
						device->addTableData(paragraphPointer->table, i18n("The key was dictionary-based with character substitution"));
						break;
					case Device::passwordDictAppend:
						device->addTableData(paragraphPointer->table, i18n("The key was dictionary-based with characters appended"));
						break;
					default:
						device->addTableData(paragraphPointer->table, i18n("The key contains a common character sequence"));
						break;
				}
			}
			radiusPointer = radiusPointer->next;
		}

		// Issue impact...
		securityIssuePointer->impactRating = 8;				// High
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("An attacker who was able to monitor the authentication traffic could attempt to break the encryption using a brute-force attack. Simple keys tend to be exponentially quicker to break than stronger keys during a brute-force of the encryption. If the attack is able to decrypt the encryption they could extract authentication credentials from the traffic. The attacker could then use the authentication credentials in order to gain a level of access to *DEVICENAME*."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 2;				// Challenging
		paragraphPointer->paragraph.assign(i18n("A variety of tools are available on the Internet that are specifically designed to break encryption. Furthermore, Open Source *ABBREV*RADIUS*-ABBREV* code could be used as the basis of a custom encryption breaking routine. Network packet and password sniffing tools are widely available on the Internet. In a switched environment an attacker may not be able to capture network traffic destined for other devices without performing an additional attack, such as exploiting *ABBREV*ARP*-ABBREV* or routing vulnerabilities."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 4;				// Planned
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that a strong *ABBREV*RADIUS*-ABBREV* server key should be configured to encrypt the authentication traffic between the device and the *ABBREV*RADIUS*-ABBREV* server. This key will have to be configured on the *ABBREV*RADIUS*-ABBREV* server and *DEVICENAME*. *COMPANY* recommends that passwords:"));
		errorCode = device->addPasswordRequirements(paragraphPointer);
		if (errorCode != 0)
			return errorCode;
		if (strlen(configRadiusKey) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(configRadiusKey);
		}

		// Conclusions text...
		if (weak > 1)
			securityIssuePointer->conLine.append(i18n("*ABBREV*RADIUS*-ABBREV* servers were configured with weak keys"));
		else
			securityIssuePointer->conLine.append(i18n("a *ABBREV*RADIUS*-ABBREV* server was configured with a weak key"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Configure strong *ABBREV*RADIUS*-ABBREV* server keys for all *ABBREV*RADIUS*-ABBREV* servers"));

		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHNPAS.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHDPAS.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHWPAS.1");
	}

	return errorCode;
}

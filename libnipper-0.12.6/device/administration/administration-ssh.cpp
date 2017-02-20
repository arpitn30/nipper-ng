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
#include "../device.h"
#include "administration.h"


int Administration::generateSSHConfig(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	hostFilter *serviceHostPointer = 0;
	string tempString;
	int errorCode = 0;

	// Add service to the services list...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-SERVICES-TABLE");
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*SSH*-ABBREV* Service"));
	if (sshEnabled == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));

	// SSH Settings section...
	configReportPointer = device->getConfigSection("CONFIG-ADMIN");
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraphTitle.assign(i18n("*ABBREV*SSH*-ABBREV* Service Settings"));
	paragraphPointer->paragraph.assign(i18n("The SSH service enables a remote administrator to access a *ABBREV*CLI*-ABBREV* on *DEVICENAME*. The *ABBREV*SSH*-ABBREV* protocol provides complete encryption of the network packets between the connecting client and the server. There are two main versions of the *ABBREV*SSH*-ABBREV* protocol."));
	if (strlen(sshConfigProtocolSupport) > 0)
	{
		paragraphPointer = device->addParagraph(configReportPointer);
		paragraphPointer->paragraph.append(sshConfigProtocolSupport);
	}
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraph.assign(i18n("This section details the *ABBREV*SSH*-ABBREV* service settings."));

	// SSH Settings Table...
	errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINSSH-TABLE");
	if (errorCode != 0)
		return errorCode;
	paragraphPointer->table->title = i18n("*ABBREV*SSH*-ABBREV* service settings");
	device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Setting"), false);
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*SSH*-ABBREV* Service"));
	if (sshEnabled == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));
	device->addTableData(paragraphPointer->table, i18n("Service *ABBREV*TCP*-ABBREV* Port"));
	tempString.assign(device->intToString(sshPort));
	device->addTableData(paragraphPointer->table, tempString.c_str());
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*SSH*-ABBREV* Protocol Version(s)"));
	switch (sshVersion)
	{
		case 1:
			device->addTableData(paragraphPointer->table, "1");
			break;
		case 2:
			device->addTableData(paragraphPointer->table, "2");
			break;
		default:
			device->addTableData(paragraphPointer->table, "1 and 2");
			break;
	}
	if (scpSupported == true)
	{
		device->addTableData(paragraphPointer->table, i18n("*ABBREV*SCP*-ABBREV*"));
		if (scpEnabled == true)
			device->addTableData(paragraphPointer->table, i18n("Enabled"));
		else
			device->addTableData(paragraphPointer->table, i18n("Disabled"));
	}
	if (sftpSupported == true)
	{
		device->addTableData(paragraphPointer->table, i18n("*ABBREV*SFTP*-ABBREV*"));
		if (sftpEnabled == true)
			device->addTableData(paragraphPointer->table, i18n("Enabled"));
		else
			device->addTableData(paragraphPointer->table, i18n("Disabled"));
	}
	if (sshSpecificTimeout == true)
	{
		device->addTableData(paragraphPointer->table, i18n("Connection Timeout"));
		if (sshTimeout == 0)
			device->addTableData(paragraphPointer->table, i18n("No Timeout"));
		else
		{
			tempString.assign(device->timeToString(sshTimeout));
			device->addTableData(paragraphPointer->table, tempString.c_str());
		}
	}

	errorCode = generateDeviceSSHConfig(device);

	if (sshHosts != 0)
	{
		paragraphPointer = device->addParagraph(configReportPointer);
		if (sshHostsRequired == true)
			paragraphPointer->paragraph.assign(i18n("On *DEVICETYPE* devices the addresses of the management hosts that are allowed to access the *ABBREV*SSH*-ABBREV* service must be specified. Table *TABLEREF* lists those management hosts."));
		else
			paragraphPointer->paragraph.assign(i18n("On *DEVICETYPE* devices the addresses of the management hosts that are allowed to access the *ABBREV*SSH*-ABBREV* service can be specified. Table *TABLEREF* lists those management hosts."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINSSHHOSTS-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("*ABBREV*SSH*-ABBREV* service management hosts");
		device->addTableHeading(paragraphPointer->table, i18n("Host"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Netmask"), false);
		if (showSSHHostInterface == true)
			device->addTableHeading(paragraphPointer->table, i18n("Interface"), false);
		if (showSSHHostAccess == true)
			device->addTableHeading(paragraphPointer->table, i18n("Access"), false);

		serviceHostPointer = sshHosts;
		while (serviceHostPointer != 0)
		{
			device->addTableData(paragraphPointer->table, serviceHostPointer->host.c_str());
			device->addTableData(paragraphPointer->table, serviceHostPointer->netmask.c_str());
			if (showSSHHostInterface == true)
				device->addTableData(paragraphPointer->table, serviceHostPointer->interface.c_str());
			if (showSSHHostAccess == true)
				device->addTableData(paragraphPointer->table, serviceHostPointer->access.c_str());
			serviceHostPointer = serviceHostPointer->next;
		}
	}

	return errorCode;
}


int Administration::generateSSHVersionSecurityIssue(Device *device, bool noWeakSSHHosts)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] SSH Protocol Version 1 Supported\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("*ABBREV*SSH*-ABBREV* Protocol Version 1 Supported"));
	securityIssuePointer->reference.assign("GEN.ADMISSH1.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("The *ABBREV*SSH*-ABBREV* service is commonly used for encrypted command-based remote device management. There are two main versions of the *ABBREV*SSH*-ABBREV* protocol and *ABBREV*SSH*-ABBREV* servers will often support multiple versions in order to maintain backwards compatibility. *ABBREV*SSH*-ABBREV* protocol version 2 was developed to extend the functionality and resolve the security issues that were present in protocol version 1"));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that support for *ABBREV*SSH*-ABBREV* protocol version 1 was enabled on *DEVICENAME*."));

	// Issue impact...
	securityIssuePointer->impactRating = 7;			// HIGH
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("Although flaws have been identified with *ABBREV*SSH*-ABBREV* protocol version 2, fundamental flaws exist in protocol version 1. An attacker could, for example, exploit a vulnerability in the protocol to perform a man-in-the-middle style attack and possibly gain command execution capabilities on *DEVICENAME*."));

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 5;				// Moderate
	paragraphPointer->paragraph.assign(i18n("Even though the vulnerabilities with *ABBREV*SSH*-ABBREV* protocol version 1 are widely known, exploiting the vulnerabilities can be difficult. Unless the attacker is highly motivated they are more likely to seek alternative vulnerabilities."));
	if (noWeakSSHHosts == false)
	{
		securityIssuePointer->easeRating = 3;				// MODERATE
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		if (sshHosts != 0)
			device->addString(paragraphPointer, "GEN.ADMISSHW.1");
		else
			device->addString(paragraphPointer, "GEN.ADMIHOWE.1");
		paragraphPointer->paragraph.assign(i18n("Although access to the *ABBREV*SSH*-ABBREV* service has been restricted to specific management hosts, *COMPANY* determined that the restricted management host configuration was weak (see section *SECTIONNO*)."));
	}
	else if ((sshHosts != 0) || (serviceHosts != 0))
	{
		securityIssuePointer->easeRating = 2;				// CHALLENGING
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.assign(i18n("Access to the *ABBREV*SSH*-ABBREV* service on *DEVICENAME* is made more difficult for an attacker due to the configured administrative host restrictions. However, it may still be possible for a skilled attacker to bypass those restrictions."));
	}

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that the *ABBREV*SSH*-ABBREV* service should be reconfigured to support only protocol version 2."));
	if ((ssh2Supported != true) && (ssh2upgrade == true))
	{
		securityIssuePointer->fixRating = 8;				// Involved
		paragraphPointer->paragraph.append(i18n(" However, the *DEVICETYPE* *ABBREV*OS*-ABBREV* needs to be upgraded before the *ABBREV*SSH*-ABBREV* service can be reconfigured to support only protocol version 2."));
	}
	else if ((ssh2Supported != true) && (ssh2upgrade != true))
	{
		securityIssuePointer->fixRating = 10;				// Involved
		paragraphPointer->paragraph.append(i18n(" Unfortunately *DEVICETYPE* devices do not support *ABBREV*SSH*-ABBREV* protocol version 2."));
	}
	if ((ssh2Supported == true) && (strlen(configSSHv2Support) > 0))
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configSSHv2Support);
	}

	// Conclusions text...
	securityIssuePointer->conLine.append(i18n("*ABBREV*SSH*-ABBREV* protocol version 1 was supported"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Reconfigure *ABBREV*SSH*-ABBREV* to support only version 2 of the protocol."));

	// Related issues...
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMISSHF.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMISSHW.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMIHOWE.1");

	return 0;
}


int Administration::generateSSHHostSecurityIssue(Device *device, bool sshVersion1)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] No SSH Administrative Host Access Restrictions\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("No SSH Administrative Host Access Restrictions"));
	securityIssuePointer->reference.assign("GEN.ADMISSHF.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices can be remotely managed using *ABBREV*SSH*-ABBREV*. To help prevent unauthorised access to *ABBREV*SSH*-ABBREV* from a malicious user or an attacker, management host addresses can be specified. Once the management host addresses have been configured, *DEVICETYPE* devices will prevent access from an unauthorised host address."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that no management host addresses were configured for the *ABBREV*SSH*-ABBREV* service on *DEVICENAME*."));

	// Issue impact...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("Without management host address restrictions, an attacker or malicious user with authentication credentials would be able to connect to the *ABBREV*SSH*-ABBREV* service and logon. Furthermore, if a vulnerability were to be identified in the *ABBREV*SSH*-ABBREV* service the attacker would not be prevented from connecting by *DEVICENAME*."));
	if (sshVersion1 == true)
	{
		device->addString(paragraphPointer, "GEN.ADMISSH1.1");
		paragraphPointer->paragraph.assign(i18n(" However, this issue is made more serious due to *ABBREV*SSH*-ABBREV* protocol version 1 being enabled (see section *SECTIONNO*)."));
		securityIssuePointer->impactRating = 5;			// Medium
	}
	else
		securityIssuePointer->impactRating = 4;			// Low

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 8;				// EASY
	paragraphPointer->paragraph.assign(i18n("For an attacker to gain access to the *ABBREV*SSH*-ABBREV* service, they would simply have to connect to it using an *ABBREV*SSH*-ABBREV* client. *ABBREV*SSH*-ABBREV* client software can be downloaded from the Internet some *ABBREV*OS*-ABBREV* install *ABBREV*SSH*-ABBREV* client by default."));

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that access to the *ABBREV*SSH*-ABBREV* service should be restricted to specific management hosts."));
	if (strlen(configSSHHostAccess) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configSSHHostAccess);
	}

	// Conclusions text...
	securityIssuePointer->conLine.append(i18n("no *ABBREV*SSH*-ABBREV* service management host address access restrictions were configured"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Configure *ABBREV*SSH*-ABBREV* service management host addresses for only those hosts that require access."));

	// Related issues...
	if (sshVersion1 == true)
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMISSH1.1");

	return 0;
}


int Administration::generateSSHWeakHostSecurityIssue(Device *device, int weakCount, bool sshVersion1)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	hostFilter *serviceHostPointer = 0;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] Weak SSH Administrative Host Access Restrictions\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("Weak SSH Administrative Host Access Restrictions"));
	securityIssuePointer->reference.assign("GEN.ADMISSHW.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices can be remotely managed using *ABBREV*SSH*-ABBREV*. To help prevent unauthorised access to *ABBREV*SSH*-ABBREV* from a malicious user or an attacker, management host addresses can be specified. Once the management host addresses have been configured, *DEVICETYPE* devices will prevent access from an unauthorised host address."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	if (weakCount > 1)
	{
		device->addValue(paragraphPointer, weakCount);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* network subnets were allowed access to the *ABBREV*SSH*-ABBREV* service on *DEVICENAME*. These are listed in Table *TABLEREF*."));
		// Table...
		errorCode = device->addTable(paragraphPointer, "GEN-ADMINWEAKSSHHOSTS-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("Weak *ABBREV*SSH*-ABBREV* service management hosts");
		device->addTableHeading(paragraphPointer->table, i18n("Host"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Netmask"), false);

		serviceHostPointer = sshHosts;
		while (serviceHostPointer != 0)
		{
			if (serviceHostPointer->netmask.compare("255.255.255.255") != 0)
			{
				device->addTableData(paragraphPointer->table, serviceHostPointer->host.c_str());
				device->addTableData(paragraphPointer->table, serviceHostPointer->netmask.c_str());
			}
			serviceHostPointer = serviceHostPointer->next;
		}
	}
	else
	{
		serviceHostPointer = serviceHosts;
		while (serviceHostPointer != 0)
		{
			if (serviceHostPointer->netmask.compare("255.255.255.255") != 0)
			{
				device->addString(paragraphPointer, serviceHostPointer->host.c_str());
				device->addString(paragraphPointer, serviceHostPointer->netmask.c_str());
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the management host configuration *DATA* / *DATA* allows access to the *ABBREV*SSH*-ABBREV* service from a network address range."));
			}
			serviceHostPointer = serviceHostPointer->next;
		}
	}

	// Issue impact...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("With weak management host address restrictions, an attacker or malicious user with authentication credentials would be able to connect to the *ABBREV*SSH*-ABBREV* service and logon. Furthermore, if a vulnerability was to be identified in a service the attacker would not be prevented from connecting by *DEVICENAME*."));
	if (sshVersion1 == true)
	{
		device->addString(paragraphPointer, "GEN.ADMISSH1.1");
		paragraphPointer->paragraph.assign(i18n(" However, this issue is made more serious due to *ABBREV*SSH*-ABBREV* protocol version 1 being enabled (see section *SECTIONNO*)."));
		securityIssuePointer->impactRating = 4;			// LOW
	}
	else
		securityIssuePointer->impactRating = 3;			// LOW

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 5;				// Moderate
	paragraphPointer->paragraph.assign(i18n("Although management host address restrictions have been implemented, an attacker connected within the configured administrative host network address space would be able to gain access to the *ABBREV*SSH*-ABBREV* service on *DEVICENAME*."));

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that specific addresses for those hosts that require access to the *ABBREV*SSH*-ABBREV* service should be configured."));
	if (strlen(configSSHHostAccess) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configSSHHostAccess);
	}

	// Conclusions text...
	securityIssuePointer->conLine.append(i18n("weak *ABBREV*SSH*-ABBREV* service management host restrictions were configured"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Configure *ABBREV*SSH*-ABBREV* service management host addresses for only those hosts that require access."));

	if (sshVersion1 == true)
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMISSH1.1");

	return 0;
}


int Administration::generateDeviceSSHConfig(Device *device)
{
	return 0;
}

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


int Administration::generateTelnetConfig(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	hostFilter *serviceHostPointer = 0;
	string tempString;
	int errorCode = 0;

	device->addPort("telnet");

	// Add service to the services list...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-SERVICES-TABLE");
	device->addTableData(paragraphPointer->table, i18n("Telnet Service"));
	if (telnetEnabled == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));

	// Telnet Settings section...
	configReportPointer = device->getConfigSection("CONFIG-ADMIN");
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraphTitle.assign(i18n("Telnet Service Settings"));
	paragraphPointer->paragraph.assign(i18n("The Telnet service enables remote administrative access to a *ABBREV*CLI*-ABBREV* on *DEVICENAME*. The Telnet protocol implemented by the service is simple and provides no encryption of the network communications between the client and the server. This section details the Telnet service settings."));

	// Telnet Settings Table...
	errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINTELNET-TABLE");
	if (errorCode != 0)
		return errorCode;
	paragraphPointer->table->title = i18n("Telnet service settings");
	device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Setting"), false);
	device->addTableData(paragraphPointer->table, i18n("Telnet Service"));
	if (telnetEnabled == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));
	device->addTableData(paragraphPointer->table, i18n("Service *ABBREV*TCP*-ABBREV* Port"));
	tempString.assign(device->intToString(telnetPort));
	device->addTableData(paragraphPointer->table, tempString.c_str());
	if (telnetSpecificTimeout == true)
	{
		device->addTableData(paragraphPointer->table, i18n("Connection Timeout"));
		if (telnetTimeout == 0)
			device->addTableData(paragraphPointer->table, i18n("No Timeout"));
		else
		{
			tempString.assign(device->timeToString(telnetTimeout));
			device->addTableData(paragraphPointer->table, tempString.c_str());
		}
	}

	// Device specific stuff...
	errorCode = generateDeviceTelnetConfig(device);

	if (telnetHosts != 0)
	{
		paragraphPointer = device->addParagraph(configReportPointer);
		if (telnetHostsRequired == true)
			paragraphPointer->paragraph.assign(i18n("On *DEVICETYPE* devices the addresses of the management hosts that are allowed to access the Telnet service must be specified. Table *TABLEREF* lists those management hosts."));
		else
			paragraphPointer->paragraph.assign(i18n("On *DEVICETYPE* devices the addresses of the management hosts that are allowed to access the Telnet service can be specified. Table *TABLEREF* lists those management hosts."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINTELNETHOSTS-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("Telnet service management hosts");
		device->addTableHeading(paragraphPointer->table, i18n("Host"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Netmask"), false);
		if (showTelnetHostInterface == true)
			device->addTableHeading(paragraphPointer->table, i18n("Interface"), false);
		if (showTelnetHostAccess == true)
			device->addTableHeading(paragraphPointer->table, i18n("Access"), false);

		serviceHostPointer = telnetHosts;
		while (serviceHostPointer != 0)
		{
			device->addTableData(paragraphPointer->table, serviceHostPointer->host.c_str());
			device->addTableData(paragraphPointer->table, serviceHostPointer->netmask.c_str());
			if (showTelnetHostInterface == true)
				device->addTableData(paragraphPointer->table, serviceHostPointer->interface.c_str());
			if (showTelnetHostAccess == true)
				device->addTableData(paragraphPointer->table, serviceHostPointer->access.c_str());
			serviceHostPointer = serviceHostPointer->next;
		}
	}

	return errorCode;
}


int Administration::generateTelnetSecurityIssue(Device *device, bool noWeakTelnetHosts)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] Clear Text Telnet Service Enabled\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("Clear Text Telnet Service Enabled"));
	securityIssuePointer->reference.assign("GEN.ADMITELN.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("Telnet is widely used to provide remote command-based access to a variety of devices and is commonly used on network devices for remote administration. Telnet is a simple protocol and was developed long before computer network security was an issue. The protocol provides no encryption or encoding, so all network traffic, including the authentication, is transmitted between the client and the server in clear text."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the Telnet service was enabled on *DEVICENAME*."));

	// Issue impact...
	securityIssuePointer->impactRating = 8;			// HIGH
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("An attacker or malicious user who was able to monitor the network traffic between a Telnet server and client would be able to capture the authentication credentials and any data. Furthermore, the attacker could then use the authentication credentials to gain a level of access to *DEVICENAME*."));

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 7;				// EASY
	paragraphPointer->paragraph.assign(i18n("Network packet and password sniffing tools are widely available on the Internet and some of the tools are specifically designed to capture clear-text protocol authentication credentials. In a switched environment an attacker may not be able to capture network traffic destined for other devices without performing an additional attack, such as exploiting *ABBREV*ARP*-ABBREV* or routing vulnerabilities."));
	if (noWeakTelnetHosts == false)
	{
		securityIssuePointer->easeRating = 4;				// MODERATE
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		if (telnetHosts != 0)
			device->addString(paragraphPointer, "GEN.ADMITELW.1");
		else
			device->addString(paragraphPointer, "GEN.ADMIHOWE.1");
		paragraphPointer->paragraph.assign(i18n("Although access to the Telnet service has been restricted to specific management hosts, *COMPANY* determined that the restricted management host configuration was weak (see section *SECTIONNO*)."));
	}
	else if ((telnetHosts != 0) || (serviceHosts != 0))
	{
		securityIssuePointer->easeRating = 2;				// CHALLENGING
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.assign(i18n("Access to the Telnet service on *DEVICENAME* is made more difficult for an attacker due to the configured administrative host restrictions. However, it may still be possible for a skilled attacker to bypass those restrictions."));
	}

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if possible, Telnet should be disabled."));
	if (sshEnabled == true)
		paragraphPointer->paragraph.append(i18n(" The *ABBREV*SSH*-ABBREV* service is already configured on *DEVICENAME*. *COMPANY* recommends that this should be used as a cryptographically secure alternative to Telnet."));
	else if (sshSupported == true)
		paragraphPointer->paragraph.append(i18n(" *DEVICETYPE* devices support the *ABBREV*SSH*-ABBREV* service, which is a cryptographically secure alternative to Telnet. *COMPANY* recommends that this service should be used as an alternative."));
	else if (sshUpgrade == true)
	{
		securityIssuePointer->fixRating = 8;				// Involved
		paragraphPointer->paragraph.append(i18n(" *COMPANY* recommends that the *ABBREV*SSH*-ABBREV* service is used as a cryptographically secure alternative to Telnet. However, the *DEVICEOS* will need to be upgraded to a version that supports the *ABBREV*SSH*-ABBREV* service."));
	}
	else
	{
		securityIssuePointer->fixRating = 10;				// Involved
		paragraphPointer->paragraph.append(i18n(" Unfortunately *DEVICETYPE* does not support the *ABBREV*SSH*-ABBREV* service, which would normally be recommended as more secure replacement for Telnet. However, *COMPANY* recommends that an alternative remote administration solution is implemented that supports encryption. The solution could be to use a device management server connected directly to the *DEVICENAME* and offering only encrypted services."));
	}
	if (strlen(disableTelnet) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(disableTelnet);
	}
	if ((strlen(configSSHSupport) > 0) && (sshSupported == true) && (sshEnabled == false))
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configSSHSupport);
	}

	// Conclusions text...
	securityIssuePointer->conLine.append(i18n("the clear text Telnet protocol was configured"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Replace Telnet with a cryptographically secure alternative."));

	// Related issues...
	if ((telnetSpecificHost == true) && (telnetHosts == 0))
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMITELH.1");
	if ((telnetSpecificHost == true) && (telnetHosts != 0))
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMITELW.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMIHOWE.1");

	return 0;
}


int Administration::generateTelnetHostSecurityIssue(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] No Telnet Host Restrictions\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("No Telnet Host Restrictions"));
	securityIssuePointer->reference.assign("GEN.ADMITELH.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("Telnet is used for the remote administration of *DEVICENAME*. To help prevent unauthorised access from a malicious user or an attacker to the Telnet service, management host addresses can be specified. Once the management host addresses have been configured, *DEVICETYPE* devices will prevent access from an unauthorised host address."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that no administrative host addresses were configured for the Telnet service."));

	// Issue impact...
	securityIssuePointer->impactRating = 5;			// Medium
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("Without management host address restrictions, an attacker or malicious user with authentication credentials, would be able to connect to the Telnet service and logon. Furthermore, if a vulnerability was to be identified in the service the attacker would not be prevented from connecting by *DEVICENAME*."));

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 9;				// TRIVIAL
	paragraphPointer->paragraph.assign(i18n("For an attacker to gain access to the Telnet service, they would simply have to connect to it using their Telnet client. Due to the unencrypted nature of the Telnet protocol, if an attacker was able to monitor the network traffic of a Telnet session, they would gain the authentication credentials which could then be used to login to the device. Telnet clients are available on the Internet and are installed by default on most *ABBREV*OS*-ABBREV*."));

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if possible, Telnet should be disabled. However, if Telnet is required, *COMPANY* recommends that specific addresses for those hosts that require administrative access should be configured."));
	if (strlen(disableTelnet) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(disableTelnet);
	}
	if (strlen(configTelnetHostAccess) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configTelnetHostAccess);
	}

	// Conclusions text...
	securityIssuePointer->conLine.append(i18n("no Telnet administrative host addresses were configured"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Configure management host addresses for only those hosts that require access."));

	// Dependent issues...
	device->addDependency(securityIssuePointer, "GEN.ADMITELN.1");

	return 0;
}


int Administration::generateTelnetWeakHostSecurityIssue(Device *device, int weakCount)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	hostFilter *serviceHostPointer = 0;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] Weak Telnet Host Restrictions\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("Weak Telnet Host Restrictions"));
	securityIssuePointer->reference.assign("GEN.ADMITELW.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("Telnet is used for the remote administration of *DEVICENAME*. To help prevent unauthorised access from a malicious user or an attacker, management host addresses can be specified for the Telnet service. Once the management host addresses have been configured, *DEVICETYPE* devices will prevent access from any unauthorised host address."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	if (weakCount > 1)
	{
		device->addValue(paragraphPointer, weakCount);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* network subnets were allowed access to the Telnet service. These are listed in Table *TABLEREF*."));
		// Table...
		errorCode = device->addTable(paragraphPointer, "GEN-ADMINTELNETWEAKHOSTS-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("Weak Telnet service management hosts");
		device->addTableHeading(paragraphPointer->table, i18n("Host"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Netmask"), false);

		serviceHostPointer = telnetHosts;
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
		serviceHostPointer = telnetHosts;
		while (serviceHostPointer != 0)
		{
			if (serviceHostPointer->netmask.compare("255.255.255.255") != 0)
			{
				device->addString(paragraphPointer, serviceHostPointer->host.c_str());
				device->addString(paragraphPointer, serviceHostPointer->netmask.c_str());
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the management host configuration *DATA* / *DATA* allows access from a network address range."));
			}
			serviceHostPointer = serviceHostPointer->next;
		}
	}

	// Issue impact...
	securityIssuePointer->impactRating = 5;			// Medium
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("With weak management host address restrictions, an attacker or malicious user with authentication credentials would be able to connect to the Telnet service and logon. Furthermore, if a vulnerability was to be identified in the service the attacker would not be prevented from connecting by *DEVICENAME*."));

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 5;				// Moderate
	paragraphPointer->paragraph.assign(i18n("Although management host address restrictions have been implemented, an attacker connected within the configured Telnet management host network address space would be able to gain access to the Telnet service."));

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if possible, Telnet should be disabled. However, if Telnet is required, *COMPANY* recommends that specific addresses for those hosts that require administrative access should be configured."));
	if (strlen(disableTelnet) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(disableTelnet);
	}
	if (strlen(configTelnetHostAccess) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configTelnetHostAccess);
	}

	// Conclusions text...
	securityIssuePointer->conLine.append(i18n("weak Telnet management host network addresses were configured"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Configure Telnet management host addresses for only those hosts that require access."));

	// Dependent issues...
	device->addDependency(securityIssuePointer, "GEN.ADMITELN.1");

	return 0;
}


int Administration::generateDeviceTelnetConfig(Device *device)
{
	return 0;
}

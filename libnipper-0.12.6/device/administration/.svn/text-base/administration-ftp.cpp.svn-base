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


int Administration::generateFTPConfig(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	hostFilter *serviceHostPointer = 0;
	string tempString;
	int errorCode = 0;

	// Add service to the services list...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-SERVICES-TABLE");
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*FTP*-ABBREV* Service"));
	if (ftpEnabled == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));

	// Console Settings section...
	configReportPointer = device->getConfigSection("CONFIG-ADMIN");
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraphTitle.assign(i18n("*ABBREV*FTP*-ABBREV* Service Settings"));
	paragraphPointer->paragraph.assign(i18n("The *ABBREV*FTP*-ABBREV* service enables a remote administrators to transfer files to and from *DEVICENAME*. The authentication and transfer of files between the *ABBREV*FTP*-ABBREV* service and client are unencrypted. This section details the *ABBREV*FTP*-ABBREV* service settings."));

	// Console Settings Table...
	errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINFTP-TABLE");
	if (errorCode != 0)
		return errorCode;
	paragraphPointer->table->title = i18n("*ABBREV*FTP*-ABBREV* service settings");
	device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Setting"), false);
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*FTP*-ABBREV* Service"));
	if (ftpEnabled == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));
	device->addTableData(paragraphPointer->table, i18n("Service *ABBREV*TCP*-ABBREV* Port"));
	tempString.assign(device->intToString(ftpPort));
	device->addTableData(paragraphPointer->table, tempString.c_str());
	if (ftpSpecificTimeout == true)
	{
		device->addTableData(paragraphPointer->table, i18n("Connection Timeout"));
		if (ftpTimeout == 0)
			device->addTableData(paragraphPointer->table, i18n("No Timeout"));
		else
		{
			tempString.assign(device->timeToString(ftpTimeout));
			device->addTableData(paragraphPointer->table, tempString.c_str());
		}
	}

	// Device specific stuff...
	errorCode = generateDeviceFTPConfig(device);

	if (ftpHosts != 0)
	{
		paragraphPointer = device->addParagraph(configReportPointer);
		if (ftpHostsRequired == true)
			paragraphPointer->paragraph.assign(i18n("On *DEVICETYPE* devices the addresses of the management hosts that are allowed to access the *ABBREV*FTP*-ABBREV* service must be specified. Table *TABLEREF* lists those management hosts."));
		else
			paragraphPointer->paragraph.assign(i18n("On *DEVICETYPE* devices the addresses of the management hosts that are allowed to access the *ABBREV*FTP*-ABBREV* service can be specified. Table *TABLEREF* lists those management hosts."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINFTPHOSTS-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("*ABBREV*FTP*-ABBREV* service management hosts");
		device->addTableHeading(paragraphPointer->table, i18n("Host"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Netmask"), false);
		if (showFTPHostInterface == true)
			device->addTableHeading(paragraphPointer->table, i18n("Interface"), false);
		if (showFTPHostAccess == true)
			device->addTableHeading(paragraphPointer->table, i18n("Access"), false);

		serviceHostPointer = ftpHosts;
		while (serviceHostPointer != 0)
		{
			device->addTableData(paragraphPointer->table, serviceHostPointer->host.c_str());
			device->addTableData(paragraphPointer->table, serviceHostPointer->netmask.c_str());
			if (showFTPHostInterface == true)
				device->addTableData(paragraphPointer->table, serviceHostPointer->interface.c_str());
			if (showFTPHostAccess == true)
				device->addTableData(paragraphPointer->table, serviceHostPointer->access.c_str());
			serviceHostPointer = serviceHostPointer->next;
		}
	}

	return errorCode;
}


int Administration::generateFTPSecurityIssue(Device *device, bool noWeakFTPHosts)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] Clear Text FTP Service Enabled\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("Clear Text *ABBREV*FTP*-ABBREV* Service Enabled"));
	securityIssuePointer->reference.assign("GEN.ADMIFTPC.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*ABBREV*FTP*-ABBREV* is widely used to provide file transfer services. The *ABBREV*FTP*-ABBREV* service implemented on *DEVICETYPE* devices provides no encryption or encoding, so all network traffic, including the authentication, is transmitted between the client and the server in clear text."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *ABBREV*FTP*-ABBREV* service was enabled on *DEVICENAME*."));

	// Issue impact...
	securityIssuePointer->impactRating = 7;			// HIGH
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("An attacker or malicious user who is able to monitor the network traffic between a *ABBREV*FTP*-ABBREV* server and client would be able to capture the authentication credentials and any data. Furthermore, the attacker could then use the authentication credentials to gain a level of access to *DEVICENAME*. The attacker may find that the credentials may work with other services that may give a greater level of access to *DEVICENAME*."));

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 7;				// EASY
	paragraphPointer->paragraph.assign(i18n("Network packet and password sniffing tools are widely available on the Internet and some of the tools are specifically designed to capture clear-text protocol authentication credentials. In a switched environment an attacker may not be able to capture network traffic destined for other devices without performing an additional attack, such as exploiting *ABBREV*ARP*-ABBREV* or routing vulnerabilities."));
	if (noWeakFTPHosts == false)
	{
		securityIssuePointer->easeRating = 4;				// MODERATE
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		if (ftpHosts != 0)
			device->addString(paragraphPointer, "GEN.ADMIFTPW.1");
		else
			device->addString(paragraphPointer, "GEN.ADMIFTPE.1");
		paragraphPointer->paragraph.assign(i18n("Although access to the *ABBREV*FTP*-ABBREV* service has been restricted to specific management hosts, *COMPANY* determined that the restricted management host configuration was weak (see section *SECTIONNO*)."));
	}
	else if ((ftpHosts != 0) || (serviceHosts != 0))
	{
		securityIssuePointer->easeRating = 2;				// CHALLENGING
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.assign(i18n("Access to the *ABBREV*FTP*-ABBREV* service on *DEVICENAME* is made more difficult for an attacker due to the configured administrative host restrictions. However, it may still be possible for a skilled attacker to bypass those restrictions."));
	}

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if possible, *ABBREV*FTP*-ABBREV* should be disabled."));
	if (sftpEnabled == true)
		paragraphPointer->paragraph.append(i18n(" *DEVICETYPE* devices support *ABBREV*SFTP*-ABBREV*, which is a cryptographically secure alternative to *ABBREV*FTP*-ABBREV*. Furthermore, *ABBREV*SFTP*-ABBREV* is already configured on *DEVICENAME*."));
	else if (sftpSupported == true)
		paragraphPointer->paragraph.append(i18n(" *DEVICETYPE* devices support *ABBREV*SFTP*-ABBREV*, which is a cyrptographically secure alternative to *ABBREV*FTP*-ABBREV*. *COMPANY* recommends that *ABBREV*SFTP*-ABBREV* should be used as an alternative to using *ABBREV*FTP*-ABBREV*."));
	else if (sftpUpgrade == true)
	{
		securityIssuePointer->fixRating = 8;				// Involved
		paragraphPointer->paragraph.append(i18n(" *COMPANY* recommends that the *ABBREV*SFTP*-ABBREV* is used as a cryptographically secure alternative to *ABBREV*FTP*-ABBREV*. However, the *DEVICEOS* will need to be upgraded to a version that supports *ABBREV*SFTP*-ABBREV*."));
	}
	if (strlen(disableFTP) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(disableFTP);
	}
	if ((sftpSupported == true) && (sftpEnabled == false) && (strlen(configSFTP) > 0))
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configSFTP);
	}

	// Conclusions text...
	securityIssuePointer->conLine.append(i18n("the clear text *ABBREV*FTP*-ABBREV* protocol was configured"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Disable the *ABBREV*FTP*-ABBREV* service"));

	// Related issues...
	if ((ftpSpecificHost == true) && (ftpHosts == 0))
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMIFTPH.1");
	if ((ftpSpecificHost == true) && (ftpHosts != 0))
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMIFTPW.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMIHOWE.1");

	return 0;
}


int Administration::generateFTPHostSecurityIssue(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] No FTP Host Restrictions\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("No *ABBREV*FTP*-ABBREV* Host Restrictions"));
	securityIssuePointer->reference.assign("GEN.ADMIFTPH.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("The *ABBREV*FTP*-ABBREV* service is used for the remote administration of *DEVICENAME*, providing an easy method of transfering files between the device and a management host. To help prevent unauthorised access from a malicious user or an attacker to the *ABBREV*FTP*-ABBREV* service, management host addresses can be specified. Once the management host addresses have been configured, *DEVICETYPE* devices will prevent access from an unauthorised host address."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that no administrative host addresses were configured for the *ABBREV*FTP*-ABBREV* service."));

	// Issue impact...
	securityIssuePointer->impactRating = 5;			// Medium
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("Without management host address restrictions, an attacker or malicious user with authentication credentials, would be able to connect to the *ABBREV*FTP*-ABBREV* service, logon and transfer configuration files. Furthermore, if a vulnerability was to be identified in the service the attacker would not be prevented from connecting by *DEVICENAME*."));

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 9;				// TRIVIAL
	paragraphPointer->paragraph.assign(i18n("With no configured management host address restrictions, an attacker could simply connect to the *ABBREV*FTP*-ABBREV* service. However, in order for an attacker to gain access to the *ABBREV*FTP*-ABBREV* service they would require authentication credentials. Due to the unencrypted nature of *ABBREV*FTP*-ABBREV* an attacker monitoring the network traffic of an *ABBREV*FTP*-ABBREV* session would gain the authentication credentials. The attacker could then use the authentication credentials to authenticate."));

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if possible, *ABBREV*FTP*-ABBREV* should be disabled. However, if *ABBREV*FTP*-ABBREV* is required, *COMPANY* recommends that specific addresses for those management hosts that require access should be configured."));
	if (strlen(disableFTP) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(disableFTP);
	}
	if (strlen(configFTPHostAccess) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configFTPHostAccess);
	}

	// Conclusions text...
	securityIssuePointer->conLine.append(i18n("no *ABBREV*FTP*-ABBREV* administrative host addresses were configured"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Configure management host addresses for only those hosts that require access"));

	// Dependent issues...
	device->addDependency(securityIssuePointer, "GEN.ADMIFTPC.1");

	return 0;
}


int Administration::generateFTPWeakHostSecurityIssue(Device *device, int weakCount)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	hostFilter *serviceHostPointer = 0;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] Weak FTP Host Restrictions\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("Weak *ABBREV*FTP*-ABBREV* Host Restrictions"));
	securityIssuePointer->reference.assign("GEN.ADMIFTPW.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*ABBREV*FTP*-ABBREV* is used for the remote administration of *DEVICENAME*. To help prevent unauthorised access from a malicious user or an attacker to the *ABBREV*FTP*-ABBREV* service, management host addresses can be specified. Once the management host addresses have been configured, *DEVICETYPE* devices will prevent access from an unauthorised host address."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	if (weakCount > 1)
	{
		device->addValue(paragraphPointer, weakCount);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* network subnets were allowed access to the *ABBREV*FTP*-ABBREV* service. These are listed in Table *TABLEREF*."));
		// Table...
		errorCode = device->addTable(paragraphPointer, "GEN-ADMINFTPWEAKHOSTS-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("Weak *ABBREV*FTP*-ABBREV* service management hosts");
		device->addTableHeading(paragraphPointer->table, i18n("Host"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Netmask"), false);

		serviceHostPointer = ftpHosts;
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
		serviceHostPointer = ftpHosts;
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
	paragraphPointer->paragraph.assign(i18n("With weak management host address restrictions, an attacker or malicious user with authentication credentials, would be able to connect to the *ABBREV*FTP*-ABBREV* service, logon and transfer configuration files. Furthermore, if a vulnerability was to be identified in the service the attacker within the configured management host range would not be prevented from connecting."));

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 5;				// Moderate
	paragraphPointer->paragraph.assign(i18n("An attacker within the configured management host address range could simply connect to the *ABBREV*FTP*-ABBREV* service. However, in order for an attacker to gain access to the *ABBREV*FTP*-ABBREV* service they would require authentication credentials. Due to the unencrypted nature of *ABBREV*FTP*-ABBREV* an attacker monitoring the network traffic of an *ABBREV*FTP*-ABBREV* session would gain the authentication credentials. The attacker could then use the authentication credentials to authenticate."));

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if possible, the *ABBREV*FTP*-ABBREV* service should be disabled. However, if the *ABBREV*FTP*-ABBREV* service is required, *COMPANY* recommends that specific addresses for those hosts that require administrative access should be configured."));
	if (strlen(disableFTP) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(disableFTP);
	}
	if (strlen(configFTPHostAccess) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configFTPHostAccess);
	}

	// Conclusions text...
	securityIssuePointer->conLine.append(i18n("weak *ABBREV*FTP*-ABBREV* management host network addresses were configured"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Configure *ABBREV*FTP*-ABBREV* management host addresses for only those hosts that require access"));

	// Dependent issues...
	device->addDependency(securityIssuePointer, "GEN.ADMIFTPC.1");

	return 0;
}


int Administration::generateDeviceFTPConfig(Device *device)
{
	return 0;
}

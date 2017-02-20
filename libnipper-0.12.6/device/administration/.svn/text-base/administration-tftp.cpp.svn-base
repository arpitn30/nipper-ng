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


int Administration::generateTFTPConfig(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	hostFilter *serviceHostPointer = 0;
	string tempString;
	int errorCode = 0;

	// Add service to the services list...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-SERVICES-TABLE");
	device->addTableData(paragraphPointer->table, i18n("TFTP Service"));
	if (tftpEnabled == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));

	// TFTP Settings section...
	configReportPointer = device->getConfigSection("CONFIG-ADMIN");
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraphTitle.assign(i18n("*ABBREV*TFTP*-ABBREV* Service Settings"));
	paragraphPointer->paragraph.assign(i18n("The *ABBREV*TFTP*-ABBREV* provides a simple method of transfering files to and from *DEVICETYPE* devices. *ABBREV*TFTP*-ABBREV* does not provide any method of authentication and all communications are unencrypted. *ABBREV*TFTP*-ABBREV* services provide security by obscurity, that is the person accessing a file must know the exact filename and path, no directory listing capabilities are provided."));
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraph.assign(i18n("This section details the *ABBREV*TFTP*-ABBREV* service settings."));

	// Telnet Settings Table...
	errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINTFTP-TABLE");
	if (errorCode != 0)
		return errorCode;
	paragraphPointer->table->title = i18n("*ABBREV*TFTP*-ABBREV* service settings");
	device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Setting"), false);
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*TFTP*-ABBREV* Service"));
	if (tftpEnabled == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));
	device->addTableData(paragraphPointer->table, i18n("Service Port"));
	tempString.assign(device->intToString(tftpPort));
	device->addTableData(paragraphPointer->table, tempString.c_str());

	// Device specific stuff...
	errorCode = generateDeviceTFTPConfig(device);

	if (tftpHosts != 0)
	{
		paragraphPointer = device->addParagraph(configReportPointer);
		if (tftpHostsRequired == true)
			paragraphPointer->paragraph.assign(i18n("On *DEVICETYPE* devices the addresses of the management hosts that are allowed to access the *ABBREV*TFTP*-ABBREV* service must be specified. Table *TABLEREF* lists those management hosts."));
		else
			paragraphPointer->paragraph.assign(i18n("On *DEVICETYPE* devices the addresses of the management hosts that are allowed to access the *ABBREV*TFTP*-ABBREV* service can be specified. Table *TABLEREF* lists those management hosts."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINTFTPHOSTS-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("*ABBREV*TFTP*-ABBREV* service management hosts");
		device->addTableHeading(paragraphPointer->table, i18n("Host"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Netmask"), false);
		if (showTFTPHostInterface == true)
			device->addTableHeading(paragraphPointer->table, i18n("Interface"), false);
		if (showTFTPHostAccess == true)
			device->addTableHeading(paragraphPointer->table, i18n("Access"), false);

		serviceHostPointer = tftpHosts;
		while (serviceHostPointer != 0)
		{
			device->addTableData(paragraphPointer->table, serviceHostPointer->host.c_str());
			device->addTableData(paragraphPointer->table, serviceHostPointer->netmask.c_str());
			if (showTFTPHostInterface == true)
				device->addTableData(paragraphPointer->table, serviceHostPointer->interface.c_str());
			if (showTFTPHostAccess == true)
				device->addTableData(paragraphPointer->table, serviceHostPointer->access.c_str());
			serviceHostPointer = serviceHostPointer->next;
		}
	}

	return errorCode;
}


int Administration::generateTFTPSecurityIssue(Device *device, bool noWeakTFTPHosts)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] TFTP Service Enabled\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("Clear Text *ABBREV*TFTP*-ABBREV* Service Enabled"));
	securityIssuePointer->reference.assign("GEN.ADMITFTP.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*ABBREV*TFTP*-ABBREV* is used for transfering files between networked devices. *ABBREV*TFTP*-ABBREV* was developed in the early days of computer network protocols and remains popular due to its simplicity. However, *ABBREV*TFTP*-ABBREV* provides no authentication or encryption of the network traffic."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *ABBREV*TFTP*-ABBREV* service was enabled on *DEVICENAME*."));

	// Issue impact...
	securityIssuePointer->impactRating = 6;			// MEDIUM
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("An attacker may be able to use the *ABBREV*TFTP*-ABBREV* service to transfer files to and from *DEVICENAME*. The files could include the devices configuration or firmware files."));

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 7;				// EASY
	paragraphPointer->paragraph.assign(i18n("*ABBREV*TFTP*-ABBREV* services do not provide an attacker with directory listings, If files were provided by the *ABBREV*TFTP*-ABBREV* service an attacker would have to guess the file names and directories. The attacker could make use of *ABBREV*TFTP*-ABBREV* file brute-force tools available on the Internet. However, due to the unencrypted nature of *ABBREV*TFTP*-ABBREV*, an attacker may attempt to gain files by mnitoring any connections to the service."));
	if (noWeakTFTPHosts == false)
	{
		securityIssuePointer->easeRating = 4;				// MODERATE
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		if (tftpHosts != 0)
			device->addString(paragraphPointer, "GEN.ADMITFTW.1");
		else
			device->addString(paragraphPointer, "GEN.ADMIHOWE.1");
		paragraphPointer->paragraph.assign(i18n("Although access to the *ABBREV*TFTP*-ABBREV* service has been restricted to specific management hosts, *COMPANY* determined that the restricted management host configuration was weak (see section *SECTIONNO*)."));
	}
	else if ((tftpHosts != 0) || (serviceHosts != 0))
	{
		securityIssuePointer->easeRating = 2;				// CHALLENGING
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.assign(i18n("Access to the *ABBREV*TFTP*-ABBREV* service on *DEVICENAME* is made more difficult for an attacker due to the configured administrative host restrictions. However, it may still be possible for a skilled attacker to bypass those restrictions."));
	}

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if possible, *ABBREV*TFTP*-ABBREV* should be disabled."));
	if (sftpEnabled == true)
		paragraphPointer->paragraph.append(i18n(" *DEVICETYPE* devices support *ABBREV*SFTP*-ABBREV*, which is an authenticated and a cryptographically secure alternative to *ABBREV*TFTP*-ABBREV*. Furthermore, *ABBREV*SFTP*-ABBREV* is already configured on *DEVICENAME*."));
	else if (sftpSupported == true)
		paragraphPointer->paragraph.append(i18n(" *DEVICETYPE* devices support the *ABBREV*SFTP*-ABBREV*, which is a cyrptographically secure with authentication alternative to *ABBREV*TFTP*-ABBREV*. *COMPANY* recommends that this should be used as an alternative."));
	else if (sftpUpgrade == true)
	{
		securityIssuePointer->fixRating = 8;				// Involved
		paragraphPointer->paragraph.append(i18n(" *COMPANY* recommends that the *ABBREV*SFTP*-ABBREV* is used as a cryptographically secure alternative to *ABBREV*TFTP*-ABBREV*. However, the *DEVICEOS* will need to be upgraded to a version that supports *ABBREV*SFTP*-ABBREV*."));
	}
	if (strlen(disableTFTP) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(disableTFTP);
	}
	if ((sftpSupported == true) && (sftpEnabled == false) && (strlen(configSFTP) > 0))
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configSFTP);
	}

	// Conclusions text...
	securityIssuePointer->conLine.append(i18n("the *ABBREV*TFTP*-ABBREV* protocol was configured"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Disable *ABBREV*TFTP*-ABBREV*."));

	// Related issues...
	if ((tftpSpecificHost == true) && (tftpHosts == 0))
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMITFTH.1");
	if ((tftpSpecificHost == true) && (tftpHosts != 0))
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMITFTW.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMIHOWE.1");

	return 0;
}


int Administration::generateTFTPHostSecurityIssue(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] No TFTP Host Restrictions\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("No *ABBREV*TFTP*-ABBREV* Host Restrictions"));
	securityIssuePointer->reference.assign("GEN.ADMITFTH.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*ABBREV*TFTP*-ABBREV* is used as a simple way of transfering files between networked devices. To help prevent unauthorised access from a malicious user or an attacker to the *ABBREV*TFTP*-ABBREV* service, management host addresses can be specified. Once the management host addresses have been configured, *DEVICETYPE* devices will prevent access from an unauthorised host address."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that no administrative host addresses were configured for the *ABBREV*TFTP*-ABBREV* service."));

	// Issue impact...
	securityIssuePointer->impactRating = 4;			// LOW
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("Without management host address restrictions, an attacker or malicious user with authentication credentials, would be able to connect to the *ABBREV*TFTP*-ABBREV* service and possibly transfer files. Furthermore, if a vulnerability was to be identified in the service the attacker would not be prevented from connecting by *DEVICENAME*."));

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 9;				// TRIVIAL
	paragraphPointer->paragraph.assign(i18n("For an attacker to gain access to the *ABBREV*TFTP*-ABBREV* service, they would simply have to connect to it using their *ABBREV*TFTP*-ABBREV* client. *ABBREV*TFTP*-ABBREV* clients are available on the Internet and are installed by default on most *ABBREV*OS*-ABBREV*."));

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if possible, the *ABBREV*TFTP*-ABBREV* service should be disabled. However, if *ABBREV*TFTP*-ABBREV* is required, *COMPANY* recommends that specific addresses for those hosts that require administrative access should be configured."));
	if (strlen(disableTFTP) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(disableTFTP);
	}
	if (strlen(configTFTPHostAccess) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configTFTPHostAccess);
	}

	// Conclusions text...
	securityIssuePointer->conLine.append(i18n("no *ABBREV*TFTP*-ABBREV* administrative host addresses were configured"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Configure management host addresses for only those hosts that require access."));

	// Dependent issues...
	device->addDependency(securityIssuePointer, "GEN.ADMITFTP.1");

	return 0;
}


int Administration::generateTFTPWeakHostSecurityIssue(Device *device, int weakCount)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	hostFilter *serviceHostPointer = 0;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] Weak TFTP Host Restrictions\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("Weak *ABBREV*TFTP*-ABBREV* Host Restrictions"));
	securityIssuePointer->reference.assign("GEN.ADMITFTW.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*ABBREV*TFTP*-ABBREV* is used as a simple way of transfering files between networked devices. To help prevent unauthorised access from a malicious user or an attacker to the *ABBREV*TFTP*-ABBREV* service, management host addresses can be specified. Once the management host addresses have been configured, *DEVICETYPE* devices will prevent access from an unauthorised host address."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	if (weakCount > 1)
	{
		device->addValue(paragraphPointer, weakCount);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* network subnets were allowed access to the *ABBREV*TFTP*-ABBREV* service. These are listed in Table *TABLEREF*."));
		// Table...
		errorCode = device->addTable(paragraphPointer, "GEN-ADMINTFTPWEAKHOSTS-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("Weak *ABBREV*TFTP*-ABBREV* service management hosts");
		device->addTableHeading(paragraphPointer->table, i18n("Host"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Netmask"), false);

		serviceHostPointer = tftpHosts;
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
		serviceHostPointer = tftpHosts;
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
	paragraphPointer->paragraph.assign(i18n("With weak management host address restrictions, an attacker or malicious user with authentication credentials would be able to connect to the *ABBREV*TFTP*-ABBREV* service and possibly transfer files. Furthermore, if a vulnerability was to be identified in the *ABBREV*TFTP*-ABBREV* service the attacker would not be prevented from connecting by *DEVICENAME*."));

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 5;				// Moderate
	paragraphPointer->paragraph.assign(i18n("Although management host address restrictions have been implemented, an attacker connected within the configured *ABBREV*TFTP*-ABBREV* management host network address space would be able to gain access to the *ABBREV*TFTP*-ABBREV* service."));

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if possible, *ABBREV*TFTP*-ABBREV* should be disabled. However, if *ABBREV*TFTP*-ABBREV* is required, *COMPANY* recommends that specific addresses for those hosts that require administrative access should be configured."));
	if (strlen(disableTFTP) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(disableTFTP);
	}
	if (strlen(configTFTPHostAccess) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configTFTPHostAccess);
	}

	// Conclusions text...
	securityIssuePointer->conLine.append(i18n("weak *ABBREV*TFTP*-ABBREV* management host network addresses were configured"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Configure *ABBREV*TFTP*-ABBREV* management host addresses for only those hosts that require access."));

	// Dependent issues...
	device->addDependency(securityIssuePointer, "GEN.ADMITFTN.1");

	return 0;
}


int Administration::generateDeviceTFTPConfig(Device *device)
{
	return 0;
}

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


int Administration::generateHostsConfig(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	int errorCode = 0;
	hostFilter *serviceHostPointer = 0;

	// Admin Hosts Settings section...
	configReportPointer = device->getConfigSection("CONFIG-ADMIN");
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraphTitle.assign(i18n("Administration Services Management Hosts"));
	paragraphPointer->paragraph.assign(i18n("It is possible to specify the addresses of the management hosts that are allowed to access the administrative services. Table *TABLEREF* lists those management hosts."));

	// Table...
	errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINHOSTS-TABLE");
	if (errorCode != 0)
		return errorCode;
	paragraphPointer->table->title = i18n("Management hosts");
	device->addTableHeading(paragraphPointer->table, i18n("Host"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Netmask"), false);
	if (showHostInterface == true)
		device->addTableHeading(paragraphPointer->table, i18n("Interface"), false);
	if (showHostAccess == true)
		device->addTableHeading(paragraphPointer->table, i18n("Access"), false);

	serviceHostPointer = serviceHosts;
	while (serviceHostPointer != 0)
	{
		device->addTableData(paragraphPointer->table, serviceHostPointer->host.c_str());
		device->addTableData(paragraphPointer->table, serviceHostPointer->netmask.c_str());
		if (showHostInterface == true)
			device->addTableData(paragraphPointer->table, serviceHostPointer->interface.c_str());
		if (showHostAccess == true)
			device->addTableData(paragraphPointer->table, serviceHostPointer->access.c_str());

		serviceHostPointer = serviceHostPointer->next;
	}

	return errorCode;
}


int Administration::generateServiceHostSecurityIssue(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] No Administrative Host Access Restrictions\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("No Administrative Host Access Restrictions"));
	securityIssuePointer->reference.assign("GEN.ADMIHOST.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices can be remotely managed using one of different administration services that can be configured. To help prevent unauthorised access from a malicious user or an attacker to the administrative services, management host addresses can be specified. Once the management host addresses have been configured, *DEVICETYPE* devices will prevent access from an unauthorised host address."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that no management host addresses were configured for *DEVICENAME* administrative services."));

	// Issue impact...
	securityIssuePointer->impactRating = 5;			// Medium
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("Without management host address restrictions, an attacker or malicious user with authentication credentials would be able to connect to the administrative service and logon. Furthermore, if a vulnerability were to be identified in an administrative service the attacker would not be prevented from connecting by *DEVICENAME*."));

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 9;				// TRIVIAL
	paragraphPointer->paragraph.assign(i18n("For an attacker to gain access to an administrative service, they would simply have to connect to it using the relevant client software. Client software for most administrative services are available on the Internet and some are installed by default on most *ABBREV*OS*-ABBREV*."));

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that access to the administration services offered by *DEVICENAME* should be restricted to specific management hosts."));
	if (strlen(serviceConfigHosts) > 0)
		paragraphPointer->paragraph.append(serviceConfigHosts);

	// Conclusions text...
	securityIssuePointer->conLine.append(i18n("no administrative host address access restrictions were configured"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Configure administrative management host addresses for only those hosts that require access."));

	// Related issues
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMITELH.1");

	return 0;
}


int Administration::generateWeakHostSecurityIssue(Device *device, int weakCount)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	hostFilter *serviceHostPointer = 0;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] Weak Administrative Host Access Restrictions\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	securityIssuePointer->title.assign(i18n("Weak Administrative Host Access Restrictions"));
	securityIssuePointer->reference.assign("GEN.ADMIHOWE.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices can be remotely managed using one of different administration services that can be configured. To help prevent unauthorised access from a malicious user or an attacker to the administrative services, management host addresses can be specified. Once the management host addresses have been configured, *DEVICETYPE* devices will prevent access from an unauthorised host address."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	if (weakCount > 1)
	{
		device->addValue(paragraphPointer, weakCount);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* network subnets were allowed access to the administrative services on *DEVICENAME*. These are listed in Table *TABLEREF*."));
		// Table...
		errorCode = device->addTable(paragraphPointer, "GEN-ADMINWEAKHOSTS-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("Weak administrative access hosts");
		device->addTableHeading(paragraphPointer->table, i18n("Host"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Netmask"), false);

		serviceHostPointer = serviceHosts;
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
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the management host configuration *DATA* / *DATA* allows access from a network address range."));
			}
			serviceHostPointer = serviceHostPointer->next;
		}
	}

	// Issue impact...
	securityIssuePointer->impactRating = 5;			// Medium
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("With weak management host address restrictions, an attacker or malicious user with authentication credentials would be able to connect to an administrative service and logon. Furthermore, if a vulnerability was to be identified in a service the attacker would not be prevented from connecting by *DEVICENAME*."));

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 5;				// Moderate
	paragraphPointer->paragraph.assign(i18n("Although management host address restrictions have been implemented, an attacker connected within the configured administrative host network address space would be able to gain access to any administrative services on *DEVICENAME*."));

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that specific addresses for those hosts that require administrative access should be configured."));
	if (strlen(serviceConfigHosts) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(serviceConfigHosts);
	}

	// Conclusions text...
	securityIssuePointer->conLine.append(i18n("administrative management host network addresses were configured"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Configure administrative management host addresses for only those hosts that require access."));

	// Related issues...
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMITELN.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMIFTPC.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMITFTP.1");

	return 0;
}


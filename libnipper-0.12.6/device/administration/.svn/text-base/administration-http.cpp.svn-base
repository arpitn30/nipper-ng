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


int Administration::generateHTTPConfig(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	hostFilter *serviceHostPointer = 0;
	cipherConfig *cipherPointer = 0;
	string tempString;
	int errorCode = 0;

	// Add service to the services list...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-SERVICES-TABLE");
	if (httpSupported == true)
	{
		tempString.assign(httpLabel);
		tempString.append(i18n(" Service"));
		device->addTableData(paragraphPointer->table, tempString.c_str());
		if (httpEnabled == true)
			device->addTableData(paragraphPointer->table, i18n("Enabled"));
		else
			device->addTableData(paragraphPointer->table, i18n("Disabled"));
	}
	if (httpsSupported == true)
	{
		tempString.assign(httpsLabel);
		tempString.append(i18n(" Service"));
		device->addTableData(paragraphPointer->table, tempString.c_str());
		if (httpsEnabled == true)
			device->addTableData(paragraphPointer->table, i18n("Enabled"));
		else
			device->addTableData(paragraphPointer->table, i18n("Disabled"));
	}

	// HTTP Settings section...
	configReportPointer = device->getConfigSection("CONFIG-ADMIN");
	paragraphPointer = device->addParagraph(configReportPointer);
	if (httpSupported == true)
		tempString.assign(httpLabel);
	else if (httpsSupported == true)
		tempString.assign(httpsLabel);
	tempString.append(i18n(" Service Settings"));
	paragraphPointer->paragraphTitle.assign(tempString);
	paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices can provide web-based administrative access."));
	if (httpSupported == true)
	{
		device->addString(paragraphPointer, httpLabel);
		paragraphPointer->paragraph.append(i18n(" The *DATA* service provides no encryption between the client and server."));
	}
	else if (httpsSupported == true)
	{
		device->addString(paragraphPointer, httpsLabel);
		paragraphPointer->paragraph.append(i18n(" The *DATA* service provides full encryption of communications between the client and server."));
	}
	paragraphPointer->paragraph.append(i18n(" This section details the web service settings:"));

	// HTTP Settings Table...
	errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINHTTP-TABLE");
	if (errorCode != 0)
		return errorCode;
	if (httpSupported == true)
	{
		tempString.assign(httpLabel);
		tempString.append(i18n(" service settings"));
		paragraphPointer->table->title.assign(tempString);
	}
	else
	{
		tempString.assign(httpsLabel);
		tempString.append(i18n(" service settings"));
		paragraphPointer->table->title.assign(tempString);
	}
	device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Setting"), false);
	if (httpSupported == true)
	{
		tempString.assign(httpLabel);
		tempString.append(i18n(" Service"));
		device->addTableData(paragraphPointer->table, tempString.c_str());
		if (httpEnabled == true)
			device->addTableData(paragraphPointer->table, i18n("Enabled"));
		else
			device->addTableData(paragraphPointer->table, i18n("Disabled"));
	}
	if (httpsSupported == true)
	{
		tempString.assign(httpsLabel);
		tempString.append(i18n(" Service"));
		device->addTableData(paragraphPointer->table, tempString.c_str());
		if (httpsEnabled == true)
			device->addTableData(paragraphPointer->table, i18n("Enabled"));
		else
			device->addTableData(paragraphPointer->table, i18n("Disabled"));
	}
	if (httpSupported == true)
	{
		tempString.assign(httpLabel);
		tempString.append(i18n(" Service *ABBREV*TCP*-ABBREV* Port"));
		device->addTableData(paragraphPointer->table, tempString.c_str());
		tempString.assign(device->intToString(httpPort));
		device->addTableData(paragraphPointer->table, tempString.c_str());
	}
	if (httpsSupported == true)
	{
		tempString.assign(httpsLabel);
		tempString.append(i18n(" Service *ABBREV*TCP*-ABBREV* Port"));
		device->addTableData(paragraphPointer->table, tempString.c_str());
		tempString.assign(device->intToString(httpsPort));
		device->addTableData(paragraphPointer->table, tempString.c_str());
	}
	if (httpSpecificTimeout == true)
	{
		device->addTableData(paragraphPointer->table, i18n("Connection Timeout"));
		if (httpTimeout == 0)
			device->addTableData(paragraphPointer->table, i18n("No Timeout"));
		else
		{
			tempString.assign(device->timeToString(httpTimeout));
			device->addTableData(paragraphPointer->table, tempString.c_str());
		}
	}

	// Device specific stuff...
	errorCode = generateDeviceHTTPConfig(device);

	if (ciphers != 0)
	{
		paragraphPointer = device->addParagraph(configReportPointer);
		device->addString(paragraphPointer, httpsLabel);
		paragraphPointer->paragraph.assign(i18n("Table *TABLEREF* lists the configured *DATA* service encryption cyphers."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINHTTPHOSTS-TABLE");
		if (errorCode != 0)
			return errorCode;

		tempString.assign(httpsLabel);
		tempString.append(i18n(" service encryption ciphers"));
		paragraphPointer->table->title.assign(tempString);
		device->addTableHeading(paragraphPointer->table, i18n("Encryption"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Authentication"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Key Length"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*SSL*-ABBREV* v2"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*SSL*-ABBREV* v3"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*TLS*-ABBREV* v1"), false);

		cipherPointer = ciphers;
		while (cipherPointer != 0)
		{
			device->addTableData(paragraphPointer->table, cipherPointer->encryption.c_str());
			device->addTableData(paragraphPointer->table, cipherPointer->authenticaton.c_str());
			tempString.assign(device->intToString(cipherPointer->bits));
			tempString.append(i18n(" bits"));
				device->addTableData(paragraphPointer->table, tempString.c_str());
			if (cipherPointer->ssl2 == true)
				device->addTableData(paragraphPointer->table, i18n("Yes"));
			else
				device->addTableData(paragraphPointer->table, i18n("No"));
			if (cipherPointer->ssl3 == true)
				device->addTableData(paragraphPointer->table, i18n("Yes"));
			else
				device->addTableData(paragraphPointer->table, i18n("No"));
			if (cipherPointer->tls1 == true)
				device->addTableData(paragraphPointer->table, i18n("Yes"));
			else
				device->addTableData(paragraphPointer->table, i18n("No"));
			cipherPointer = cipherPointer->next;
		}

		if (defaultCiphers == true)
		{
			paragraphPointer = device->addParagraph(configReportPointer);
			paragraphPointer->paragraph.assign(i18n("It is worth noting that the ciphers were determined using the defaults that *DEVICETYPE* devices are typically configured with. However, these can differ between different models."));
		}
	}

	if (httpHosts != 0)
	{
		paragraphPointer = device->addParagraph(configReportPointer);
		if (httpsSupported == true)
			device->addString(paragraphPointer, httpsLabel);
		else
			device->addString(paragraphPointer, httpLabel);
		if (httpHostsRequired == true)
			paragraphPointer->paragraph.assign(i18n("On *DEVICETYPE* devices the addresses of the management hosts that are allowed to access the *DATA* service must be specified. Table *TABLEREF* lists those management hosts."));
		else
			paragraphPointer->paragraph.assign(i18n("On *DEVICETYPE* devices the addresses of the management hosts that are allowed to access the *DATA* service can be specified. Table *TABLEREF* lists those management hosts."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINHTTPHOSTS-TABLE");
		if (errorCode != 0)
			return errorCode;
		tempString.assign(httpsLabel);
		tempString.append(i18n(" service management hosts"));
		paragraphPointer->table->title.assign(tempString);
		device->addTableHeading(paragraphPointer->table, i18n("Host"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Netmask"), false);
		if (showHTTPHostInterface == true)
			device->addTableHeading(paragraphPointer->table, i18n("Interface"), false);
		if (showHTTPHostAccess == true)
			device->addTableHeading(paragraphPointer->table, i18n("Access"), false);

		serviceHostPointer = httpHosts;
		while (serviceHostPointer != 0)
		{
			device->addTableData(paragraphPointer->table, serviceHostPointer->host.c_str());
			device->addTableData(paragraphPointer->table, serviceHostPointer->netmask.c_str());
			if (showHTTPHostInterface == true)
				device->addTableData(paragraphPointer->table, serviceHostPointer->interface.c_str());
			if (showHTTPHostAccess == true)
				device->addTableData(paragraphPointer->table, serviceHostPointer->access.c_str());
			serviceHostPointer = serviceHostPointer->next;
		}
	}

	return errorCode;
}


int Administration::generateHTTPSecurityIssue(Device *device, bool noWeakHTTPHosts)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] Clear Text HTTP Service Enabled\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	tempString.assign(i18n("Clear Text "));
	tempString.append(httpLabel);
	tempString.append(i18n(" Service Enabled"));
	securityIssuePointer->title.assign(tempString);
	securityIssuePointer->reference.assign("GEN.ADMIHTTP.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	device->addString(paragraphPointer, httpLabel);
	device->addString(paragraphPointer, httpLabel);
	paragraphPointer->paragraph.assign(i18n("The *DATA* service is used on *DEVICETYPE* devices to provide remote administration. *DATA* is a widely used on the Internet and the service provides no encryption of authentication or the transfer of data."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	device->addString(paragraphPointer, httpLabel);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *DATA* service was enabled on *DEVICENAME*."));

	// Issue impact...
	securityIssuePointer->impactRating = 7;			// HIGH
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	device->addString(paragraphPointer, httpLabel);
	paragraphPointer->paragraph.assign(i18n("An attacker or malicious user who was able to monitor the network traffic between a *DATA* server and client would be able to capture the authentication credentials and any data. Furthermore, the attacker could then use the authentication credentials to gain a level of access to *DEVICENAME*."));

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 7;				// EASY
	paragraphPointer->paragraph.assign(i18n("Network packet and password sniffing tools are widely available on the Internet and some of the tools are specifically designed to capture clear-text protocol authentication credentials. In a switched environment an attacker may not be able to capture network traffic destined for other devices without performing an additional attack, such as exploiting *ABBREV*ARP*-ABBREV* or routing vulnerabilities."));
	if (noWeakHTTPHosts == false)
	{
		securityIssuePointer->easeRating = 4;				// MODERATE
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		device->addString(paragraphPointer, httpLabel);
		if (httpHosts != 0)
			device->addString(paragraphPointer, "GEN.ADMIHTTW.1");
		else
			device->addString(paragraphPointer, "GEN.ADMIHTTE.1");
		paragraphPointer->paragraph.assign(i18n("Although access to the *DATA* service has been restricted to specific management hosts, *COMPANY* determined that the restricted management host configuration was weak (see section *SECTIONNO*)."));
	}
	else if ((httpHosts != 0) || (serviceHosts != 0))
	{
		securityIssuePointer->easeRating = 2;				// CHALLENGING
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		device->addString(paragraphPointer, httpLabel);
		paragraphPointer->paragraph.assign(i18n("Access to the *DATA* service on *DEVICENAME* is made more difficult for an attacker due to the configured administrative host restrictions. However, it may still be possible for a skilled attacker to bypass those restrictions."));
	}

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	device->addString(paragraphPointer, httpLabel);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if possible, *DATA* should be disabled."));
	if (httpsEnabled == true)
	{
		device->addString(paragraphPointer, httpsLabel);
		device->addString(paragraphPointer, httpLabel);
		paragraphPointer->paragraph.append(i18n(" The *DATA* service is already configured on *DEVICENAME*. *COMPANY* recommends that this should be used as the cyrptographically secure alternative to *DATA*."));
	}
	else if (httpsSupported == true)
	{
		device->addString(paragraphPointer, httpsLabel);
		device->addString(paragraphPointer, httpLabel);
		paragraphPointer->paragraph.append(i18n(" *DEVICETYPE* devices support the *DATA* service, which is a cyrptographically secure alternative to *DATA*. *COMPANY* recommends that this service should be used as an alternative."));
	}
	else if (httpsUpgrade == true)
	{
		securityIssuePointer->fixRating = 8;				// Involved
		device->addString(paragraphPointer, httpsLabel);
		device->addString(paragraphPointer, httpLabel);
		device->addString(paragraphPointer, httpsLabel);
		paragraphPointer->paragraph.append(i18n(" *COMPANY* recommends that the *DATA* service is used as a cryptographically secure alternative to *DATA*. However, the *DEVICEOS* will need to be upgraded to a version that supports the *DATA* service."));
	}
	else
	{
		securityIssuePointer->fixRating = 10;				// Involved
		device->addString(paragraphPointer, httpsLabel);
		device->addString(paragraphPointer, httpLabel);
		paragraphPointer->paragraph.append(i18n(" Unfortunately *DEVICETYPE* does not support the *DATA* service, which would normally be recommended as more secure replacement for *DATA*. However, *COMPANY* recommends that an alternative remote administration solution is implemented that supports encryption. The solution could be to use a device management server connected directly to the *DEVICENAME* and offering only encrypted services."));
	}
	if (strlen(disableHTTP) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(disableHTTP);
	}
	if ((strlen(configHTTPSSupport) > 0) && (httpsSupported == true))
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configHTTPSSupport);
	}

	// Conclusions text...
	tempString.assign(i18n("the clear text "));
	tempString.append(httpLabel);
	tempString.append(i18n(" service was configured"));
	securityIssuePointer->conLine.append(tempString);

	// Recommendation list text...
	tempString.assign(i18n("Replace the "));
	tempString.append(httpLabel);
	tempString.append(i18n(" service with a cryptographically secure alternative."));
	device->addRecommendation(securityIssuePointer, tempString.c_str());

	// Related issues...
	if ((httpSpecificHost == true) && (httpHosts == 0))
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMIHTTH.1");
	if ((httpSpecificHost == true) && (httpHosts != 0))
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMIHTTW.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMIHOWE.1");

	return 0;
}


int Administration::generateHTTPHostSecurityIssue(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	string protoString;
	string tempString;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] No HTTP Host Restrictions\n", device->config->COL_BLUE, device->config->COL_RESET);

	if ((httpEnabled == false) || ((httpEnabled == true) && (httpsRedirect == true)))
		protoString.assign(httpsLabel);
	else
		protoString.assign(httpLabel);

	securityIssuePointer = device->addSecurityIssue();
	tempString.assign(i18n("No "));
	tempString.append(protoString);
	tempString.append(i18n(" Management Host Restrictions"));
	securityIssuePointer->title.assign(tempString);
	securityIssuePointer->reference.assign("GEN.ADMIHTTF.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	device->addString(paragraphPointer, protoString.c_str());
	device->addString(paragraphPointer, protoString.c_str());
	paragraphPointer->paragraph.assign(i18n("The *DATA* service is used for the remote web-based administration of *DEVICENAME*. To help prevent unauthorised access from a malicious user or an attacker to the *DATA* service, management host addresses can be specified. Once the management host addresses have been configured, *DEVICETYPE* devices will prevent access from an unauthorised host address."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	device->addString(paragraphPointer, protoString.c_str());
	paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that no administrative host addresses were configured for the *DATA* service."));

	// Issue impact...
	securityIssuePointer->impactRating = 4;			// LOW
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	device->addString(paragraphPointer, protoString.c_str());
	paragraphPointer->paragraph.assign(i18n("Without management host address restrictions, an attacker or malicious user with authentication credentials, would be able to connect to the *DATA* service and logon. Furthermore, if a vulnerability was to be identified in the service the attacker would not be prevented from connecting to the service."));
	if ((httpEnabled == false) || ((httpEnabled == true) && (httpsRedirect == true)))
	{
		securityIssuePointer->impactRating = 6;			// MEDIUM
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("Due to the unencrypted nature of the service, an attacker monitoring the connection would gain access to any authentication credentials and data transfered between the client and the device."));
	}

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 9;				// TRIVIAL
	device->addString(paragraphPointer, protoString.c_str());
	paragraphPointer->paragraph.assign(i18n("For an attacker to gain access to the *DATA* service, they would simply have to connect to it using their web browser. Web browsers are available on the Internet and are installed by default on most *ABBREV*OS*-ABBREV*."));

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	device->addString(paragraphPointer, protoString.c_str());
	device->addString(paragraphPointer, protoString.c_str());
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that specific addresses for those hosts that require administrative access should be configured."));
	if (strlen(configHTTPHostAccess) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configHTTPHostAccess);
	}

	// Conclusions text...
	tempString.assign(i18n("no "));
	tempString.append(protoString);
	tempString.append(i18n(" service management host addresses were configured"));
	securityIssuePointer->conLine.assign(tempString);

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Configure management host addresses for only those hosts that require access."));

	// Dependent issues...
	device->addDependency(securityIssuePointer, "GEN.ADMIHTTP.1");

	return 0;
}


int Administration::generateHTTPWeakHostSecurityIssue(Device *device, int weakCount)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	hostFilter *serviceHostPointer = 0;
	string protoString;
	string tempString;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] Weak HTTP Host Restrictions\n", device->config->COL_BLUE, device->config->COL_RESET);

	if ((httpEnabled == false) || ((httpEnabled == true) && (httpsRedirect == true)))
		protoString.assign(httpsLabel);
	else
		protoString.assign(httpLabel);

	securityIssuePointer = device->addSecurityIssue();
	tempString.assign(i18n("Weak "));
	tempString.append(protoString);
	tempString.append(i18n(" Service Host Restrictions"));
	securityIssuePointer->title.assign(tempString);
	securityIssuePointer->reference.assign("GEN.ADMIHTTW.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	device->addString(paragraphPointer, protoString.c_str());
	device->addString(paragraphPointer, protoString.c_str());
	paragraphPointer->paragraph.assign(i18n("The *DATA* service is used for the remote web-based administration of *DEVICENAME*. To help prevent unauthorised access from a malicious user or an attacker, management host addresses can be specified for the *DATA* service. Once the management host addresses have been configured, *DEVICETYPE* devices will prevent access from any unauthorised host address."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	if (weakCount > 1)
	{
		device->addValue(paragraphPointer, weakCount);
		device->addString(paragraphPointer, protoString.c_str());
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* network subnets were allowed access to the *DATA* service. These are listed in Table *TABLEREF*."));
		// Table...
		errorCode = device->addTable(paragraphPointer, "GEN-ADMINHTTPWEAKHOSTS-TABLE");
		if (errorCode != 0)
			return errorCode;
		tempString.assign(i18n("Weak "));
		tempString.append(protoString);
		tempString.append(i18n(" service management hosts"));
		paragraphPointer->table->title.assign(tempString);
		device->addTableHeading(paragraphPointer->table, i18n("Host"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Netmask"), false);

		serviceHostPointer = httpHosts;
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
		serviceHostPointer = httpHosts;
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
	securityIssuePointer->impactRating = 4;			// LOW
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	device->addString(paragraphPointer, protoString.c_str());
	paragraphPointer->paragraph.assign(i18n("With weak management host address restrictions, an attacker or malicious user with authentication credentials would be able to connect to the *DATA* service and logon. Furthermore, if a vulnerability was to be identified in the service the attacker would not be prevented from connecting to the service."));
	if ((httpEnabled == true) && (httpsRedirect == false))
	{
		securityIssuePointer->impactRating = 6;			// MEDIUM
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("Due to the unencrypted nature of the service, an attacker monitoring the connection would gain access to any authentication credentials and data transfered between the client and the device."));
	}

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 5;				// Moderate
	device->addString(paragraphPointer, protoString.c_str());
	paragraphPointer->paragraph.assign(i18n("For an attacker who was within the configured management host address range to gain access to the *DATA* service, they would simply have to connect to the service using their web browser. Web browsers are available on the Internet and are installed by default on most *ABBREV*OS*-ABBREV*."));

	// Issue recommendation...
	securityIssuePointer->fixRating = 3;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	device->addString(paragraphPointer, protoString.c_str());
	device->addString(paragraphPointer, protoString.c_str());
	if ((httpEnabled == true) && (httpsRedirect == false))
	{
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if possible, the *DATA* service should be disabled and replaced with a cryptographically secure alternative. However, if the *DATA* service is required, *COMPANY* recommends that access should be restricted to only those host addresses that require administrative access."));
		if (strlen(configHTTPHostAccess) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(configHTTPHostAccess);
		}
	}
	else
	{
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that access should be restricted to only those host addresses that require administrative access."));
	}

	// Conclusions text...
	tempString.assign(i18n("weak "));
	tempString.append(protoString);
	tempString.append(i18n(" management host network addresses were configured"));
	securityIssuePointer->conLine.assign(tempString);

	// Recommendation list text...
	tempString.assign(i18n("Configure "));
	tempString.append(protoString);
	tempString.append(i18n(" management host addresses for only those hosts that require access."));
	device->addRecommendation(securityIssuePointer, tempString.c_str());

	// Dependent issues...
	device->addDependency(securityIssuePointer, "GEN.ADMIHTTP.1");

	return 0;
}


int Administration::generateWeakCipherSecurityIssue(Device *device, int weakCipherCount)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	cipherConfig *cipherPointer = 0;
	string tempString;
	bool weakProtocol = false;
	bool weakBits = false;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] Weak SSL Ciphers Supported\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	if (weakCipherCount > 1)
		securityIssuePointer->title.assign(i18n("Weak *ABBREV*SSL*-ABBREV* Ciphers Supported"));
	else
		securityIssuePointer->title.assign(i18n("Weak *ABBREV*SSL*-ABBREV* Cipher Supported"));
	securityIssuePointer->reference.assign("GEN.ADMIWECI.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices support a range of different encryption, authentication ciphers and cryptographic protocols. *DEVICETYPE* devices support *ABBREV*SSL*-ABBREV* protocol versions 2 and 3, and *ABBREV*TLS*-ABBREV* protocol version 1 cryptographic protocols."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	if (weakCipherCount > 1)
	{
		device->addValue(paragraphPointer, weakCipherCount);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *NUMBER* weak ciphers listed in Table *TABLEREF* were configured on *DEVICENAME*."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "SEC-WEAKHTTPSCIPHERS-TABLE");
		if (errorCode != 0)
			return errorCode;

		paragraphPointer->table->title.assign(i18n("Weak encryption ciphers"));
		device->addTableHeading(paragraphPointer->table, i18n("Encryption"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Authentication"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Key Length"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*SSL*-ABBREV* v2"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*SSL*-ABBREV* v3"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*TLS*-ABBREV* v1"), false);

		cipherPointer = ciphers;
		while (cipherPointer != 0)
		{
			if ((cipherPointer->bits < 128) || (cipherPointer->ssl2 == true))
			{
				device->addTableData(paragraphPointer->table, cipherPointer->encryption.c_str());
				device->addTableData(paragraphPointer->table, cipherPointer->authenticaton.c_str());
				tempString.assign(device->intToString(cipherPointer->bits));
				tempString.append(i18n(" bits"));
					device->addTableData(paragraphPointer->table, tempString.c_str());
				if (cipherPointer->ssl2 == true)
					device->addTableData(paragraphPointer->table, i18n("Yes"));
				else
					device->addTableData(paragraphPointer->table, i18n("No"));
				if (cipherPointer->ssl3 == true)
					device->addTableData(paragraphPointer->table, i18n("Yes"));
				else
					device->addTableData(paragraphPointer->table, i18n("No"));
				if (cipherPointer->tls1 == true)
					device->addTableData(paragraphPointer->table, i18n("Yes"));
				else
					device->addTableData(paragraphPointer->table, i18n("No"));

				if (cipherPointer->bits < 128)
					weakBits = true;
				if (cipherPointer->ssl2 == true)
					weakProtocol = true;
				
			}
			cipherPointer = cipherPointer->next;
		}
	}
	else
	{
		cipherPointer = ciphers;
		while (cipherPointer != 0)
		{
			if ((cipherPointer->bits < 128) && (cipherPointer->ssl2 == true))
			{
				weakProtocol = true;
				weakBits = true;
				device->addString(paragraphPointer, cipherPointer->encryption.c_str());
				device->addString(paragraphPointer, cipherPointer->authenticaton.c_str());
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the configured *DATA*-*DATA* cipher supports *ABBREV*SSL*-ABBREV* protocol version 2 and has a key length of less than 128 bits."));
			}
			else if (cipherPointer->bits < 128)
			{
				weakBits = true;
				device->addString(paragraphPointer, cipherPointer->encryption.c_str());
				device->addString(paragraphPointer, cipherPointer->authenticaton.c_str());
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the configured *DATA*-*DATA* cipher has a key length of less than 128 bits."));
			}
			else if (cipherPointer->ssl2 == true)
			{
				weakProtocol = true;
				device->addString(paragraphPointer, cipherPointer->encryption.c_str());
				device->addString(paragraphPointer, cipherPointer->authenticaton.c_str());
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the weak *ABBREV*SSL*-ABBREV* protocol version 2 cipher *DATA*-*DATA* was configured."));
			}
			cipherPointer = cipherPointer->next;
		}
	}
	if (defaultCiphers == true)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("It is worth noting that the ciphers were determined using the defaults that *DEVICETYPE* devices are typically configured with. However, these can differ between different models."));
	}

	// Issue impact...
	securityIssuePointer->impactRating = 7;			// HIGH
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	device->addString(paragraphPointer, httpsLabel);
	paragraphPointer->paragraph.assign(i18n("The *DATA* connections to *DEVICENAME* are used for remote administration. If an attacker is able to gain access to the connection, the attacker would gain administrative access to *DEVICENAME*."));
	if (weakProtocol == true)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("Although encrypted connections provide a significant security improvement over clear text protocols, *ABBREV*SSL*-ABBREV* protocol versions 2 contains a number of significant flaws. The protocol vulnerabilities include; cryptographic keys that are used for both authentication and encryption, truncation attacks and a man in the middle vulnerability."));
	}
	if (weakBits == true)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("If the cipher bit length is not sufficiently large, an attacker may be able to break the cipher given enough time."));
	}

	// Issue ease...
	securityIssuePointer->easeRating = 2;				// CHALLENGING
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	paragraphPointer->paragraph.assign(i18n("Although the vulnerabilities with weak ciphers are widely known, exploiting the vulnerabilities can be difficult and time consuming. An attacker who was able to monitor a connection, could require a significant amount of time before even one of the weaker encryption ciphers is broken."));

	// Issue recommendation...
	securityIssuePointer->fixRating = 2;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that only strong encryption ciphers and protocols should be configured. *COMPANY* recommends that *ABBREV*SSL*-ABBREV* version 2 should not used and a cipher with a key length of at least 128 bits should be used."));
	if (strlen(configCipherText) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configCipherText);
	}

	// Conclusions text...
	if (weakCipherCount > 1)
		securityIssuePointer->conLine.append(i18n("weak encryption ciphers were configured"));
	else
		securityIssuePointer->conLine.append(i18n("a weak encryption cipher was configured"));

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Configure only strong encryption ciphers"));

	return errorCode;
}


int Administration::generateDeviceHTTPConfig(Device *device)
{
	return 0;
}


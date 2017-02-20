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
#include "dns.h"


int DNS::generateConfigReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	hostNameConfig *hostNamePointer = 0;
	dnsRecordConfig *dnsRecordPointer = 0;
	dnsConfig *dnsPointer = 0;
	string tempString;
	bool found = false;
	int errorCode = 0;

	if ((hostNameList != 0) || (dnsClientSupported == true) || (dnsServerSupported == true) || (dnsProxySupported == true))
	{

		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s Name Resolution\n", device->config->COL_BLUE, device->config->COL_RESET);

		// Create Config Report Section...
		configReportPointer = device->getConfigSection("CONFIG-DNS");
		configReportPointer->title = i18n("Name Resolution Settings");
		if (strlen(nameMappingConfig) > 0)
		{
			paragraphPointer = device->addParagraph(configReportPointer);
			paragraphPointer->paragraph.assign(nameMappingConfig);
		}

		// DNS Client Configuration Settings...
		if (dnsClientSupported == true)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s DNS Client Settings\n", device->config->COL_BLUE, device->config->COL_RESET);

			// Init pointers...
			paragraphPointer = device->addParagraph(configReportPointer);

			// Set subsection title...
			paragraphPointer->paragraphTitle.assign(i18n("*ABBREV*DNS*-ABBREV* Client Configuration"));
			paragraphPointer->paragraph.assign(i18n("The *ABBREV*DNS*-ABBREV* service stores information about mappings between a devices *ABBREV*IP*-ABBREV* address and a name, which is easier for humans to recognise and remember. *DEVICETYPE* devices can be configured to query a *ABBREV*DNS*-ABBREV* in order to resolve names to addresses. This section details those configuration settings."));

			// Create Table...
			errorCode = device->addTable(paragraphPointer, "CONFIG-DNSCLIENT-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("*ABBREV*DNS*-ABBREV* client configuration");
			device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
			device->addTableHeading(paragraphPointer->table, i18n("Setting"), false);

			// Data...
			if (!dnsDomain.empty())
			{
				device->addTableData(paragraphPointer->table, i18n("Domain"));
				device->addTableData(paragraphPointer->table, dnsDomain.c_str());
			}
			device->addTableData(paragraphPointer->table, i18n("*ABBREV*DNS*-ABBREV* Lookups"));
			if (dnsLookupEnabled == true)
				device->addTableData(paragraphPointer->table, i18n("Enabled"));
			else
				device->addTableData(paragraphPointer->table, i18n("Disabled"));
			if (dnsRetriesSupported == true)
			{
				device->addTableData(paragraphPointer->table, i18n("*ABBREV*DNS*-ABBREV* Query Retry Limit"));
				if (dnsRetries == 0)
					device->addTableData(paragraphPointer->table, i18n("None"));
				else
				{
					tempString.assign(device->intToString(dnsRetries));
					device->addTableData(paragraphPointer->table, tempString.c_str());
				}
			}
			if (dnsTimeoutSupported == true)
			{
				device->addTableData(paragraphPointer->table, i18n("*ABBREV*DNS*-ABBREV* Query Timeout"));
				if (dnsTimeout == 0)
					device->addTableData(paragraphPointer->table, i18n("None"));
				else
				{
					tempString.assign(device->timeToString(dnsTimeout));
					device->addTableData(paragraphPointer->table, tempString.c_str());
				}
			}
			if (dnsRoundRobinSupported == true)
			{
				device->addTableData(paragraphPointer->table, i18n("Round Robin"));
				if (dnsRoundRobin == true)
					device->addTableData(paragraphPointer->table, i18n("Enabled"));
				else
					device->addTableData(paragraphPointer->table, i18n("Disabled"));
			}

			if (dnsServer != 0)
			{
				found = false;
				dnsPointer = dnsServer;
				while ((dnsPointer != 0) && (found == false))
				{
					if (!dnsPointer->description.empty())
						found = true;
					else
						dnsPointer = dnsPointer->next;
				}

				paragraphPointer = device->addParagraph(configReportPointer);
				errorCode = device->addTable(paragraphPointer, "CONFIG-DNSCLIENTSERVERS-TABLE");
				if (errorCode != 0)
					return errorCode;
				paragraphPointer->table->title = i18n("*ABBREV*DNS*-ABBREV* servers");
				if (found == true)
					device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
				device->addTableHeading(paragraphPointer->table, i18n("Server *ABBREV*IP*-ABBREV* Address"), false);
				if (showInterface == true)
					device->addTableHeading(paragraphPointer->table, i18n("Interface"), false);
				dnsPointer = dnsServer;
				while (dnsPointer != 0)
				{
					if (found == true)
						device->addTableData(paragraphPointer->table, dnsPointer->description.c_str());
					device->addTableData(paragraphPointer->table, dnsPointer->name.c_str());
					if (showInterface == true)
						device->addTableData(paragraphPointer->table, dnsPointer->interface.c_str());
					dnsPointer = dnsPointer->next;
				}
			}

			if (domainName != 0)
			{
				found = false;
				dnsPointer = domainName;
				while ((dnsPointer != 0) && (found == false))
				{
					if (!dnsPointer->description.empty())
						found = true;
					else
						dnsPointer = dnsPointer->next;
				}

				paragraphPointer = device->addParagraph(configReportPointer);
				errorCode = device->addTable(paragraphPointer, "CONFIG-DNSCLIENTDOMAINS-TABLE");
				if (errorCode != 0)
					return errorCode;
				paragraphPointer->table->title = i18n("Domain completion list");
				if (found == true)
					device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
				device->addTableHeading(paragraphPointer->table, i18n("Domain"), false);
				dnsPointer = domainName;
				while (dnsPointer != 0)
				{
					if (found == true)
						device->addTableData(paragraphPointer->table, dnsPointer->description.c_str());
					device->addTableData(paragraphPointer->table, dnsPointer->name.c_str());
					dnsPointer = dnsPointer->next;
				}
			}
		}

		// DNS Server...
		if ((dnsServerSupported == true) || (dnsProxySupported == true))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s DNS Server Configuration\n", device->config->COL_BLUE, device->config->COL_RESET);

			paragraphPointer = device->getTableParagraphPointer("CONFIG-SERVICES-TABLE");
			if ((dnsServerSupported == true) && (dnsProxyEnabled == false))
			{
				device->addTableData(paragraphPointer->table, i18n("*ABBREV*DNS*-ABBREV* Service"));
				if (dnsServiceEnabled == true)
					device->addTableData(paragraphPointer->table, i18n("Enabled"));
				else
					device->addTableData(paragraphPointer->table, i18n("Disabled"));
			}
			if (dnsProxySupported == true)
			{
				device->addTableData(paragraphPointer->table, i18n("*ABBREV*DNS*-ABBREV* Proxy Service"));
				if (dnsProxyEnabled == true)
					device->addTableData(paragraphPointer->table, i18n("Enabled"));
				else
					device->addTableData(paragraphPointer->table, i18n("Disabled"));
			}

			// Init pointers...
			paragraphPointer = device->addParagraph(configReportPointer);

			// Set subsection title...
			paragraphPointer->paragraphTitle.assign(i18n("*ABBREV*DNS*-ABBREV* Server Configuration"));
			paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices can be configured to offer the *ABBREV*DNS*-ABBREV* service to hosts on the network. This section details the *ABBREV*DNS*-ABBREV* service."));

			// Create Table...
			errorCode = device->addTable(paragraphPointer, "CONFIG-DNSSERVER-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("*ABBREV*DNS*-ABBREV* server configuration");
			device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
			device->addTableHeading(paragraphPointer->table, i18n("Setting"), false);

			// Data
			if ((dnsServerSupported == true) && (dnsProxyEnabled == false))
			{
				device->addTableData(paragraphPointer->table, i18n("*ABBREV*DNS*-ABBREV* Service"));
				if (dnsServiceEnabled == true)
					device->addTableData(paragraphPointer->table, i18n("Enabled"));
				else
					device->addTableData(paragraphPointer->table, i18n("Disabled"));
			}
			if (dnsProxySupported == true)
			{
				device->addTableData(paragraphPointer->table, i18n("*ABBREV*DNS*-ABBREV* Proxy Service"));
				if (dnsProxyEnabled == true)
					device->addTableData(paragraphPointer->table, i18n("Enabled"));
				else
					device->addTableData(paragraphPointer->table, i18n("Disabled"));
			}
			if (dynamicDNSSupported == true)
			{
				device->addTableData(paragraphPointer->table, i18n("Dynamic *ABBREV*DNS*-ABBREV*"));
				if (dynamicDNSEnabled == true)
					device->addTableData(paragraphPointer->table, i18n("Enabled"));
				else
					device->addTableData(paragraphPointer->table, i18n("Disabled"));
			}
			device->addTableData(paragraphPointer->table, i18n("*ABBREV*DNS*-ABBREV* Service Port"));
			tempString.assign(device->intToString(dnsPort));
			device->addTableData(paragraphPointer->table, tempString.c_str());

			// DNS Forwarders
			if (dnsForwarders != 0)
			{
				found = false;
				dnsPointer = dnsForwarders;
				while ((dnsPointer != 0) && (found == false))
				{
					if (!dnsPointer->description.empty())
						found = true;
					else
						dnsPointer = dnsPointer->next;
				}

				paragraphPointer = device->addParagraph(configReportPointer);
				errorCode = device->addTable(paragraphPointer, "CONFIG-DNSSERVERFWRD-TABLE");
				if (errorCode != 0)
					return errorCode;
				paragraphPointer->table->title = i18n("*ABBREV*DNS*-ABBREV* server forwarders");
				if (found == true)
					device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
				device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*DNS*-ABBREV* Server *ABBREV*IP*-ABBREV* Address"), false);
				dnsPointer = dnsForwarders;
				while (dnsPointer != 0)
				{
					if (found == true)
						device->addTableData(paragraphPointer->table, dnsPointer->description.c_str());
					device->addTableData(paragraphPointer->table, dnsPointer->name.c_str());
					dnsPointer = dnsPointer->next;
				}
			}

			// DNS Records
			if (dnsRecord != 0)
			{
				paragraphPointer = device->addParagraph(configReportPointer);
				errorCode = device->addTable(paragraphPointer, "CONFIG-DNSSERVERRECS-TABLE");
				if (errorCode != 0)
					return errorCode;
				paragraphPointer->table->title = i18n("*ABBREV*DNS*-ABBREV* server records");
				device->addTableHeading(paragraphPointer->table, i18n("Type"), false);
				device->addTableHeading(paragraphPointer->table, i18n("Hostname"), false);
				device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*IP*-ABBREV* Address"), false);
				if (dnsRecordKeepAliveSupported == true)
					device->addTableHeading(paragraphPointer->table, i18n("Keep Alive"), false);
				if (returnRecordsSupported == true)
					device->addTableHeading(paragraphPointer->table, i18n("Multi Reply"), false);

				dnsRecordPointer = dnsRecord;
				while (dnsRecordPointer != 0)
				{
					device->addTableData(paragraphPointer->table, dnsRecordPointer->recordType.c_str());
					device->addTableData(paragraphPointer->table, dnsRecordPointer->name.c_str());
					device->addTableData(paragraphPointer->table, dnsRecordPointer->address.c_str());
					if (dnsRecordKeepAliveSupported == true)
						device->addTableData(paragraphPointer->table, dnsRecordPointer->keepAlive.c_str());
					if ((returnRecordsSupported == true) && (dnsRecordPointer->singleRecord == true))
						device->addTableData(paragraphPointer->table, i18n("Yes"));
					else if (returnRecordsSupported == true)
						device->addTableData(paragraphPointer->table, i18n("No"));
					dnsRecordPointer = dnsRecordPointer->next;
				}
			}
		}

		// Hostname mappings...
		if (hostNameList != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s Hostname Mappings\n", device->config->COL_BLUE, device->config->COL_RESET);

			// Init pointers...
			paragraphPointer = device->addParagraph(configReportPointer);

			// Set subsection title...
			paragraphPointer->paragraphTitle.assign(i18n("Hostname mappings"));
			paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices can be configured with hostname to *ABBREV*IP*-ABBREV* address mappings for use with the device. This section details those hostname to *ABBREV*IP*-ABBREV* address mappings."));

			paragraphPointer = device->addParagraph(configReportPointer);
			errorCode = device->addTable(paragraphPointer, "CONFIG-HOSTNAMEMAPPINGS-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("Hostname *ABBREV*IP*-ABBREV* address mappings");
			device->addTableHeading(paragraphPointer->table, i18n("Hostname"), false);
			device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*IP*-ABBREV* Address"), false);

			hostNamePointer = hostNameList;
			while (hostNamePointer != 0)
			{
				device->addTableData(paragraphPointer->table, hostNamePointer->name.c_str());
				device->addTableData(paragraphPointer->table, hostNamePointer->address.c_str());
				hostNamePointer = hostNamePointer->next;
			}
		}
	}

	return 0;
}


int DNS::generateSecurityReport(Device *device)
{
	// Variables...
	dnsConfig *dnsPointer = 0;
	int count = 0;
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s DNS Checks\n", device->config->COL_BLUE, device->config->COL_RESET);

	if ((dnsLookupEnabled == true) && (dnsClientSupported == true))
	{

		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Domain Lookups Enabled\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("*ABBREV*DNS*-ABBREV* Lookups Enabled"));
		securityIssuePointer->reference.assign("GEN.DNSCLOOK.1");

		dnsPointer = dnsServer;
		while (dnsPointer != 0)
		{
			count++;
			dnsPointer = dnsPointer->next;
		}

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices can make use host names rather than the *ABBREV*IP*-ABBREV* by looking up the address using *ABBREV*DNS*-ABBREV* services."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addValue(paragraphPointer, count);
		if (count > 1)
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that name lookups were configured on *DEVICENAME* with *NUMBER* *ABBREV*DNS*-ABBREV* servers configured."));
		else
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that name lookups were configured on *DEVICENAME* with *NUMBER* *ABBREV*DNS*-ABBREV* server configured."));

		// Issue impact...
		securityIssuePointer->impactRating = 2;			// Medium
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("An attacker who was able to capture network traffic could monitor *ABBREV*DNS*-ABBREV* queries from the *DEVICETYPE* devices. Furthermore, vulnerabilities have been previously identified where mistyped commands on some devices are interpreted as an attempt to contact a Telnet server. An attacker listening for such connections could create a connection back to the device in order to perform a man in the middle attack."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 6;				// Easy
		paragraphPointer->paragraph.assign(i18n("Network packet capture tools are available on the Internet that can allow an attacker to monitor the network traffic. In a modern network environment, switches are typically deployed to connect the network infrastructure devices rather than hubs. With a network switch devices, the attacker should only be able to see broadcast network traffic or traffic sent directly to or from the attackers host. However, a skilled attacker could bypass this restriction by performing an attack such *ABBREV*ARP*-ABBREV* spoofing or exploiting a vulnerability with the network routing. Tools for bypassing a network switching environments restrictions are available on the Internet."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 3;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if not required, domain lookups should be disabled."));
		if (strlen(disableLookup) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(disableLookup);
		}

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("domain lookups were enabled"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Disable domain lookups"));
	}

	return generateDeviceSpecificSecurityReport(device);
}


int DNS::generateDeviceSpecificSecurityReport(Device *device)
{
	return 0;
}



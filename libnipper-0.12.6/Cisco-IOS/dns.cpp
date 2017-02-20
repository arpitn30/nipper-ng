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

// Include...
#include <cstdlib>
#include <cstring>

#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "iosdevice.h"
#include "dns.h"
#include "general.h"


IOSDNS::IOSDNS()
{
	nameMappingConfig = i18n("*DEVICETYPE* devices can be configured to resolve name to address mappings. This section details those settings.");			// The text paragraph in the config section

	// Host configuration
	showInterface = false;					// Are interfaces supported?

	// DNS Client Settings
	dnsClientSupported = true;				// DNS Client Supported?
	dnsLookupEnabled = true;				// DNS lookups enabled?
	disableLookup = "Domain lookups can be disabled on *DEVICETYPE* devices with the following commands (the last command is for *DEVICEOS* 12.1 and older):*CODE**COMMAND*no ip domain lookup*-COMMAND**COMMAND*no ip domain-lookup*-COMMAND**-CODE*";						// The text and commands to disable DNS lookup
	dnsRetries = 2;							// DNS lookup retries
	dnsRetriesSupported = false;			// DNS lookup retries Supported?
	dnsTimeout = 3;							// DNS timeout
	dnsTimeoutSupported = false;			// DNS timeout Supported?
	dnsRoundRobin = false;					// DNS Round Robin
	dnsRoundRobinSupported = false;			// DNS Round Robin Supported?

	// DNS Server Options...
	dnsRecordKeepAliveSupported = false;	// Is the DNS keep Alive message type supported?
	returnRecordsSupported = false;			// Is the single/multiple record field supported?
	dynamicDNSSupported = false;			// Is Dynamic DNS Supported?
	dnsServerSupported = false;				// Is DNS Server Supported?
	dnsServiceEnabled = false;				// Is the DNS service enabled?
	dynamicDNSEnabled = false;				// Is dynamic DNS enabled?
	dnsProxySupported = false;				// Is DNS Proxy Server Supported?
	dnsProxyEnabled = false;				// Is the DNS Proxy service enabled?
	dnsPort = 53;							// DNS Server Port

	broadcastLookups = true;
}


int IOSDNS::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	dnsConfig *dnsPointer = 0;
	int tempInt = 0;
	bool setting = false;
	bool first = false;

	// Init
	if (strcmp(command->part(0), "no") == 0)
	{
		tempInt = 2;
		setting = false;
	}
	else
	{
		tempInt = 1;
		setting = true;
	}

	// Proxy Server...
	if ((strcmp(command->part(tempInt), "dns") == 0) && (strcmp(command->part(tempInt + 1), "spoofing") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Spoofing(Proxy) Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (setting == true)
			dnsProxyEnabled = true;
		dnsProxySupported = true;
		dnsServerSupported = true;
	}

	// DNS Server...
	else if ((strcmp(command->part(tempInt), "dns") == 0) && (strcmp(command->part(tempInt + 1), "server") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		dnsServiceEnabled = setting;
		dnsServerSupported = true;
	}

	// domain list...
	else if (((strcmp(command->part(tempInt), "domain") == 0) && (strcmp(command->part(tempInt + 1), "list") == 0)) || (strcmp(command->part(tempInt), "domain-list") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Domain List Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		if (strcmp(command->part(tempInt), "list") == 0)
			tempInt++;

		if (setting == true)
		{
			dnsPointer = addDomainName(command->part(tempInt));
		}
	}

	// domain lookup...
	else if (((strcmp(command->part(tempInt), "domain") == 0) && (strcmp(command->part(tempInt + 1), "lookup") == 0)) || (strcmp(command->part(tempInt), "domain-lookup") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Domain Lookup Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		if (strcmp(command->part(tempInt), "lookup") == 0)
			tempInt++;

		dnsLookupEnabled = setting;
		broadcastLookups = setting;
	}

	// domain name...
	else if (((strcmp(command->part(tempInt), "domain") == 0) && (strcmp(command->part(tempInt + 1), "name") == 0)) || (strcmp(command->part(tempInt), "domain-name") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Domain Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;
		if (strcmp(command->part(tempInt), "name") == 0)
			tempInt++;

		if (setting == true)
			dnsDomain.assign(command->part(tempInt));
	}

	// domain retry...
	else if ((strcmp(command->part(tempInt), "domain") == 0) && (strcmp(command->part(tempInt + 1), "retry") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDomain Retries Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 2;

		dnsRetriesSupported = true;

		if (setting == true)
			dnsRetries = atoi(command->part(tempInt));
	}

	// round robin...
	else if ((strcmp(command->part(tempInt), "domain") == 0) && (strcmp(command->part(tempInt + 1), "round-robin") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Round Robin Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 2;

		dnsRoundRobinSupported = true;
		dnsRoundRobin = setting;
	}

	// timeout...
	else if ((strcmp(command->part(tempInt), "domain") == 0) && (strcmp(command->part(tempInt + 1), "timeout") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 2;

		dnsTimeoutSupported = true;
		if (setting == true)
			dnsTimeout = atoi(command->part(tempInt));
	}

	// dns name-server...
	else if (strcmp(command->part(tempInt), "name-server") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Name Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;

		if (dnsServer == 0)
			first = true;
		while (tempInt < command->parts)
		{
			if (first == true)
			{
				dnsPointer = addDNSServer(command->part(tempInt));
				dnsPointer->description.assign(i18n("Primary"));
				first = false;
			}
			else
			{
				dnsPointer = addDNSServer(command->part(tempInt));
				dnsPointer->description.assign(i18n("Secondary"));
			}
			tempInt++;
		}
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int IOSDNS::processDefaults(Device *device)
{
	// Enable features...
	if (device->general != 0)
	{
		if ((device->general->versionMajor > 12) || ((device->general->versionMajor == 12) && (device->general->versionMinor > 3)) || ((device->general->versionMajor == 12) && (device->general->versionMinor == 3) && (device->general->versionRevision > 2)))
		{
			if (device->isRouter == true)
			{
				dnsProxySupported = true;
				dnsServerSupported = true;
			}
			dnsRetriesSupported = true;
			dnsTimeoutSupported = true;
			dnsRoundRobinSupported = true;
		}
		else if ((device->general->versionMajor > 12) || ((device->general->versionMajor == 12) && (device->general->versionMinor > 2)) || ((device->general->versionMajor == 12) && (device->general->versionMinor == 2) && (device->general->versionRevision > 3)))
		{
			if (device->isRouter == true)
				dnsServerSupported = true;
			dnsRetriesSupported = true;
			dnsTimeoutSupported = true;
			dnsRoundRobinSupported = true;
		}
		else if ((device->general->versionMajor > 12) || ((device->general->versionMajor == 12) && (device->general->versionMinor > 2)))
		{
			dnsRetriesSupported = true;
			dnsTimeoutSupported = true;
			dnsRoundRobinSupported = true;
		}
		else if ((device->general->versionMajor > 12) || ((device->general->versionMajor == 12) && (device->general->versionMinor > 0)))
		{
			dnsRoundRobinSupported = true;
		}
	}

	// Disable domain lookups if there are no servers to lookup with...
	if (dnsServer == 0)
		dnsLookupEnabled = false;

	return 0;
}


int IOSDNS::generateDeviceSpecificSecurityReport(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;

	if ((dnsLookupEnabled == false) && (broadcastLookups == true) && (dnsClientSupported == true))
	{

		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Broadcast Domain Lookups Enabled\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("Broadcast Domain Lookups Enabled"));
		securityIssuePointer->reference.assign("IOS.DNSCLOOK.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices can make use host names rather than the *ABBREV*IP*-ABBREV* by looking up the address using *ABBREV*DNS*-ABBREV* services. If no *ABBREV*DNS*-ABBREV* servers are configured, the lookups are broadcast on *DEVICETYPE* devices rather than sent directly to a *ABBREV*DNS*-ABBREV* server."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that name lookups were configured to broadcast from *DEVICENAME*."));

		// Issue impact...
		securityIssuePointer->impactRating = 2;			// Medium
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("An attacker who was able to capture network traffic could monitor *ABBREV*DNS*-ABBREV* queries from the *DEVICETYPE* devices. Furthermore, vulnerabilities have been previously identified  where mistyped commands on *DEVICETYPE* devices are interpreted as an attempt to contact a Telnet server. An attacker listening for such connections could create a connection back to the device in order to perform a man in the middle attack."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 8;				// Easy
		paragraphPointer->paragraph.assign(i18n("Network packet capture tools are available on the Internet that can allow an attacker to monitor the network traffic. The attack is made easier due to the lookups being broadcast on the network."));

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

	return 0;
}


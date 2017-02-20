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
#include "device.h"
#include "dns.h"


ProCurveDNS::ProCurveDNS()
{
	nameMappingConfig = i18n("*DEVICETYPE* devices can be configured to resolve name to address mappings. This section details those settings.");			// The text paragraph in the config section

	// Host configuration
	showInterface = false;					// Are interfaces supported?

	// DNS Client Settings
	dnsClientSupported = false;				// DNS Client Supported?
	dnsLookupEnabled = false;				// DNS lookups enabled?
	disableLookup = "*ABBREV*DNS*-ABBREV* lookups can be disabled on *DEVICETYPE* devices by removing all the configured *ABBREV*DNS*-ABBREV* servers. This can be done with the following command:*CODE**COMMAND*no ip dns server-address priority *CMDUSER*priority*-CMDUSER* *CMDUSER*ip-address*-CMDUSER**-COMMAND**-CODE*";						// The text and commands to disable DNS lookup
	dnsRetries = 0;							// DNS lookup retries
	dnsRetriesSupported = false;			// DNS lookup retries Supported?
	dnsTimeout = 0;							// DNS timeout
	dnsTimeoutSupported = false;			// DNS timeout Supported?

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

	// Internal HP Procurve...
	dnsSupported = false;
}


int ProCurveDNS::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	dnsConfig *dnsPointer = 0;
	int tempInt = 0;
	bool setting = false;

	dnsSupported = true;

	// Init
	if (strcmp(command->part(0), "no") == 0)
	{
		tempInt = 3;
		setting = false;
	}
	else
	{
		tempInt = 2;
		setting = true;
	}

	// domain name...
	if (strcasecmp(command->part(tempInt), "domain-name") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDomain Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;

		if (setting == true)
			dnsDomain.assign(command->part(tempInt));
	}

	// dns server...
	else if (strcasecmp(command->part(tempInt), "server-address") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;

		if (setting == true)
		{
			dnsPointer = addDNSServer(command->part(5));
			dnsPointer->description.assign(i18n("Priority: "));
			dnsPointer->description.append(command->part(4));
		}
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int ProCurveDNS::processDefaults(Device *device)
{
	// Enable DNS support (not all ProCurves support DNS)
	if (dnsSupported == true)
	{
		dnsClientSupported = true;
		if (dnsServer != 0)
			dnsLookupEnabled = true;
	}

	return 0;
}


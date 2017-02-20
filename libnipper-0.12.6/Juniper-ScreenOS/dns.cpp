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


ScreenOSDNS::ScreenOSDNS()
{
	nameMappingConfig = i18n("*DEVICETYPE* devices can be configured to resolve name to address mappings. This section details those settings.");			// The text paragraph in the config section

	// Host configuration
	showInterface = true;					// Are interfaces supported?

	// DNS Client Settings
	dnsClientSupported = true;				// DNS Client Supported?
	dnsLookupEnabled = false;				// DNS lookups enabled?
	disableLookup = "";						// The text and commands to disable DNS lookup
	dnsRetries = 0;							// DNS lookup retries
	dnsRetriesSupported = false;			// DNS lookup retries Supported?
	dnsTimeout = 0;							// DNS timeout
	dnsTimeoutSupported = false;			// DNS timeout Supported?

	// DNS Server Options...
	dnsRecordKeepAliveSupported = false;	// Is the DNS keep Alive message type supported?
	returnRecordsSupported = false;			// Is the single/multiple record field supported?
	dynamicDNSSupported = true;				// Is Dynamic DNS Supported?
	dnsServerSupported = true;				// Is DNS Server Supported?
	dnsServiceEnabled = false;				// Is the DNS service enabled?
	dynamicDNSEnabled = false;				// Is dynamic DNS enabled?
	dnsProxySupported = true;				// Is DNS Proxy Server Supported?
	dnsProxyEnabled = false;				// Is the DNS Proxy service enabled?
	dnsPort = 53;							// DNS Server Port
}


int ScreenOSDNS::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	dnsRecordConfig *recordPointer = 0;
	dnsConfig *dnsPointer = 0;
	bool setting = false;
	int tempInt = 0;

	// Init
	tempInt = 2;
	if (strcasecmp(command->part(0), "unset") == 0)
		setting = false;
	else
		setting = true;

	// Domain...
	if (strcasecmp(command->part(1), "domain") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDomain Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (setting == true)
			dnsDomain.assign(command->part(2));
	}

	// DNS Host Record...
	else if ((strcasecmp(command->part(tempInt), "host") == 0) && (strcasecmp(command->part(tempInt + 1), "name") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Record Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 2;

		if (setting == true)
		{
			recordPointer = addDNSRecord();
			recordPointer->recordType.assign("A");
			recordPointer->address.assign(command->part(5));
			recordPointer->name.assign(command->part(4));
		}
	}

	// DNS server...
	else if ((strcasecmp(command->part(2), "host") == 0) && (strncasecmp(command->part(3), "dns", 3) == 0) && (strcasecmp(command->part(4), "0.0.0.0") != 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (setting == true)
		{
			dnsPointer = addDNSServer(command->part(4));
			switch (command->part(3)[3])
			{
				case '1':
					dnsPointer->description.assign(i18n("Primary"));
					break;
				case '2':
					dnsPointer->description.assign(i18n("Secondary"));
					break;
				default:
					dnsPointer->description.assign(i18n("Tertiary"));
					break;
			}
			if (strcasecmp(command->part(5), "src-interface") == 0)
				dnsPointer->interface.assign(command->part(6));
		}
	}

	// Proxy...
	else if ((strcasecmp(command->part(2), "proxy") == 0) && (strcasecmp(command->part(3), "enable") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Proxy Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (setting == true)
			dnsProxyEnabled = true;
	}

	// Dynamic DNS...
	else if ((strcasecmp(command->part(2), "ddns") == 0) && (strcasecmp(command->part(3), "enable") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDynamic DNS Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (setting == true)
			dynamicDNSEnabled = true;
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int ScreenOSDNS::processDefaults(Device *device)
{
	if ((dnsProxyEnabled == true) || (dnsRecord != 0))
		dnsServiceEnabled = true;

	return 0;
}


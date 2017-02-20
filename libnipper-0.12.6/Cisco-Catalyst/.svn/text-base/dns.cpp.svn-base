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


CatalystDNS::CatalystDNS()
{
	nameMappingConfig = i18n("*DEVICETYPE* devices can be configured to resolve name to address mappings. This section details those settings.");			// The text paragraph in the config section

	// Host configuration
	showInterface = false;					// Are interfaces supported?

	// DNS Client Options...
	dnsClientSupported = true;				// DNS Client Supported?
	disableLookup = "*ABBREV*DNS*-ABBREV* lookups can be disabled on *DEVICETYPE* devices with the following command:*CODE**COMMAND*set ip dns disable*-COMMAND**-CODE*";						// The text and commands to disable DNS lookup
	dnsLookupEnabled = false;				// DNS lookups enabled?
	dnsRetries = 0;							// DNS lookup retries
	dnsTimeout = 0;							// DNS timeout

	// DNS Server Options...
	dnsRecordKeepAliveSupported = false;	// Is the DNS keep Alive message type supported?
	returnRecordsSupported = false;			// Is the single/multiple record field supported?
	dynamicDNSSupported = false;			// Is Dynamic DNS Supported?
	dnsServerSupported = false;				// Is DNS Server Supported?
	dnsServiceEnabled = false;				// Is the DNS service enabled?
	dynamicDNSEnabled = false;				// Is dynamic DNS enabled?
	dnsPort = 53;							// DNS Server Port
}


int CatalystDNS::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	dnsConfig *dnsPointer = 0;
	bool setting = false;

	// Init
	if (strcmp(command->part(0), "set") == 0)
		setting = true;
	else
		setting = false;

	// DNS Server...
	if (strcmp(command->part(3), "server") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		dnsPointer = addDNSServer(command->part(4));
		if (command->parts == 6)
			dnsPointer->description.assign(command->part(5));
		else
			dnsPointer->description.assign(i18n("Secondary"));
	}

	// DNS Domain...
	else if (strcmp(command->part(3), "domain") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Domain Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		dnsPointer = addDomainName(command->part(4));
	}

	// DNS...
	else if (strcmp(command->part(2), "dns") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Lookups Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (setting == true)
		{
			if (strcmp(command->part(3), "enable") == 0)
				dnsLookupEnabled = true;
			else
				dnsLookupEnabled = false;
		}
		else
			dnsLookupEnabled = false;
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int CatalystDNS::processDefaults()
{
	return 0;
}


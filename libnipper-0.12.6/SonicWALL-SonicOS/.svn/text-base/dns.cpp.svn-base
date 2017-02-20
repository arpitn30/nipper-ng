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


SonicOSDNS::SonicOSDNS()
{
	nameMappingConfig = i18n("*DEVICETYPE* devices can be configured with a list of *ABBREV*DNS*-ABBREV* servers. This section details those settings.");			// The text paragraph in the config section

	// Host configuration
	showInterface = false;					// Are interfaces supported?

	// DNS Client Settings
	dnsClientSupported = true;				// DNS Client Supported?
	dnsLookupEnabled = false;				// DNS lookups enabled?
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
	dnsPort = 53;							// DNS Server Port
}


int SonicOSDNS::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	dnsConfig *dnsPointer = 0;

	// DNS Server Address...
	if ((strcmp(command->part(0), "dnsSrvAddr") == 0) && (command->parts > 1))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		dnsPointer = addDNSServer(command->part(1));
		dnsPointer->description.assign(i18n("Primary"));
	}
	else if ((strncmp(command->part(0), "dnsServer", 9) == 0) && (command->parts > 1))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		dnsPointer = addDNSServer(command->part(1));
		dnsPointer->description.assign(i18n("Secondary"));
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int SonicOSDNS::processDefaults()
{
	return 0;
}


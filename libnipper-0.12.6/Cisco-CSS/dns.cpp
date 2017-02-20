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


CiscoCSSDNS::CiscoCSSDNS()
{
	nameMappingConfig = i18n("*DEVICETYPE* devices have can be configured to act as a *ABBREV*DNS*-ABBREV* server and perform name lookups. This section details the domain naming settings.");			// The text paragraph in the config section

	// Host configuration
	showInterface = false;					// Are interfaces supported?

	// DNS Client Settings
	dnsClientSupported = true;				// DNS Client Supported?
	dnsLookupEnabled = false;				// DNS lookups enabled?
	disableLookup = "*ABBREV*DNS*-ABBREV* server name lookups can be disabled on *DEVICETYPE* devices by removing all *ABBREV*DNS*-ABBREV* servers from the configuration. This can be done with the following command:*CODE**COMMAND*no dns *CMDREQUIRE*primary *CMDOR* secondary*-CMDREQUIRE**-COMMAND**-CODE*";						// The text and commands to disable DNS lookup
	dnsRetries = 0;							// DNS lookup retries
	dnsRetriesSupported = false;			// DNS lookup retries Supported?
	dnsTimeout = 0;							// DNS timeout
	dnsTimeoutSupported = false;			// DNS timeout Supported?

	// DNS Server Options...
	dnsRecordKeepAliveSupported = true;		// Is the DNS keep Alive message type supported?
	returnRecordsSupported = true;			// Is the single/multiple record field supported?
	dynamicDNSSupported = false;			// Is Dynamic DNS Supported?
	dnsServerSupported = true;				// Is DNS Server Supported?
	dnsServiceEnabled = false;				// Is the DNS service enabled?
	dynamicDNSEnabled = false;				// Is dynamic DNS enabled?
	dnsProxySupported = false;				// Is DNS Proxy Server Supported?
	dnsProxyEnabled = false;				// Is the DNS Proxy service enabled?
	dnsPort = 53;							// DNS Server Port
}


int CiscoCSSDNS::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	dnsConfig *dnsPointer = 0;
	dnsRecordConfig *recordPointer = 0;
	int tempInt = 0;
	bool setting = false;

	// Init
	if (strcmp(command->part(0), "no") == 0)
	{
		tempInt = 1;
		setting = false;
	}
	else
	{
		tempInt = 0;
		setting = true;
	}

	// DNS servers...
	if ((strcmp(command->part(tempInt), "dns") == 0) && (strcmp(command->part(tempInt + 1), "suffix") != 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;

		if (setting == true)
		{
			dnsPointer = addDNSServer(command->part(tempInt + 1));
			dnsPointer->description.assign(command->part(tempInt));
		}
	}

	// DNS domain...
	else if ((strcmp(command->part(tempInt), "dns") == 0) && (strcmp(command->part(tempInt + 1), "suffix") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Domain Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 2;

		if (setting == true)
		{
			dnsDomain.assign(command->part(tempInt));
		}
	}

	// DNS Records...
	else if ((strcmp(command->part(tempInt), "dns-record") == 0) && (strcmp(command->part(tempInt + 1), "zero") != 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Record Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;

		if (setting == true)
		{
			recordPointer = addDNSRecord();
			recordPointer->recordType.assign(command->part(tempInt));
			tempInt++;
			recordPointer->name.assign(command->part(tempInt));
			tempInt++;
			recordPointer->address.assign(command->part(tempInt));
			tempInt++;
			recordPointer->keepAlive.assign("0");
			recordPointer->singleRecord = true;
			if (command->parts > tempInt)
			{
				recordPointer->keepAlive.assign(command->part(tempInt));
				tempInt++;
				if (command->parts > tempInt)
				{
					if (strcmp(command->part(tempInt), "multiple") == 0)
						recordPointer->singleRecord = false;
				}
			}
		}
	}

	// DNS server forwarders...
	else if ((strcmp(command->part(tempInt), "dns-server") == 0) && (strcmp(command->part(tempInt + 1), "forwarder") == 0) && (strcmp(command->part(tempInt + 2), "zero") != 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Forwarder Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt +=2;

		if (setting == true)
		{
			dnsPointer = addForwarder(command->part(tempInt + 1));
			dnsPointer->description.assign(command->part(tempInt));
		}
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int CiscoCSSDNS::processDefaults(Device *device)
{
	return 0;
}


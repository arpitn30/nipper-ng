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
#include "general.h"


CiscoSecDNS::CiscoSecDNS()
{
	nameMappingConfig = i18n("*DEVICETYPE* devices can be configured with a list of host name to *ABBREV*IP*-ABBREV* address mappings for use within the configuration. This section details those settings.");			// The text paragraph in the config section

	// Host configuration
	showInterface = false;					// Are interfaces supported?

	// DNS Client Settings
	dnsClientSupported = false;				// DNS Client Supported?
	dnsLookupEnabled = false;				// DNS lookups enabled?
	disableLookup = "*ABBREV*DNS*-ABBREV* lookups are disabled or enabled on specific interfaces on *DEVICETYPE* devices. The following command can be used to disable *ABBREV*DNS*-ABBREV* lookups:*CODE**COMMAND*no dns domain-lookup *CMDUSER*interface*-CMDUSER**-COMMAND**-CODE*";						// The text and commands to disable DNS lookup
	dnsRetries = 2;							// DNS lookup retries
	dnsRetriesSupported = false;			// DNS lookup retries Supported?
	dnsTimeout = 2;							// DNS timeout
	dnsTimeoutSupported = false;			// DNS timeout Supported?

	// DNS Server Options...
	dnsRecordKeepAliveSupported = false;	// Is the DNS keep Alive message type supported?
	returnRecordsSupported = false;			// Is the single/multiple record field supported?
	dynamicDNSSupported = false;			// Is Dynamic DNS Supported?
	dnsServerSupported = false;				// Is DNS Server Supported?
	dnsServiceEnabled = false;				// Is the DNS service enabled?
	dynamicDNSEnabled = false;				// Is dynamic DNS enabled?
	dnsPort = 53;							// DNS Server Port


	// Device specific...
	dnsClientUsed = false;
}


int CiscoSecDNS::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	dnsConfig *dnsPointer = 0;
	hostNameConfig *namePointer = 0;
	fpos_t filePosition;
	int tempInt = 0;
	bool setting = false;
	bool first = false;

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
 
	// name...
	if (strcmp(command->part(tempInt), "name") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sName Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;

		if (setting == true)
			namePointer = addHostName(command->part(tempInt + 1), command->part(tempInt));
	}

	// domain name...
	else if (strcmp(command->part(tempInt), "domain-name") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDomain Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;

		if (setting == true)
			dnsDomain.assign(command->part(tempInt));
	}

	// dns lookups...
	else if ((strcmp(command->part(tempInt), "dns") == 0) && (strcmp(command->part(tempInt + 1), "domain-lookup") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Domain Lookup Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		dnsClientUsed = true;

		if (setting == true)
			dnsLookupEnabled = true;
	}

	// dns name-server...
	else if ((strcmp(command->part(tempInt), "dns") == 0) && (strcmp(command->part(tempInt + 1), "name-server") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Name Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 2;
		dnsClientUsed = true;

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

	// dns retries...
	else if ((strcmp(command->part(tempInt), "dns") == 0) && (strcmp(command->part(tempInt + 1), "retries") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Retries Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 2;
		dnsClientUsed = true;

		if (setting == true)
			dnsRetries = atoi(command->part(tempInt));
	}

	// dns timeout...
	else if ((strcmp(command->part(tempInt), "dns") == 0) && (strcmp(command->part(tempInt + 1), "timeout") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 2;
		dnsClientUsed = true;

		if (setting == true)
			dnsTimeout = atoi(command->part(tempInt));
	}

	// dns server groupt...
	else if ((strcmp(command->part(tempInt), "dns") == 0) && (strcmp(command->part(tempInt + 1), "server-group") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDNS Server Group Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		dnsClientUsed = true;

		fgetpos(device->inputFile, &filePosition);

		while (((line[0] == ' ') || (strcmp(command->part(0), "server-group") == 0)) && (feof(device->inputFile) == 0))
		{

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

			// Domain-name
			if (strcmp(command->part(tempInt), "domain-name") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sDomain Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				tempInt++;

				if (setting == true)
					dnsDomain.assign(command->part(tempInt));
			}

			else if (strcmp(command->part(tempInt), "name-server") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sDNS Name Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				tempInt += 2;

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

			// dns retries...
			else if (strcmp(command->part(tempInt), "retries") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sDNS Retries Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				tempInt++;

				if (setting == true)
					dnsRetries = atoi(command->part(tempInt));
			}

			// dns timeout...
			else if (strcmp(command->part(tempInt), "timeout") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sDNS Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				tempInt++;

				if (setting == true)
					dnsTimeout = atoi(command->part(tempInt));
			}

			// NOT PROCESSED...
			else
				device->lineNotProcessed(line);

			// Read a line from the config...
			fgetpos(device->inputFile, &filePosition);
			device->readLine(line, lineSize);

			// Split it up into parts...
			command->setConfigLine(line);
		}

		// Set file position back
		fsetpos(device->inputFile, &filePosition);
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int CiscoSecDNS::processDefaults(Device *device)
{
	// Enable DNS client?
	if (dnsClientUsed == false)
	{
		if (device->general != 0)
		{
			if ((device->general->versionMajor > 7) || ((device->general->versionMajor == 7) && (device->general->versionMinor > 0)) || ((device->general->versionMajor == 7) && (device->general->versionMinor == 0) && (device->general->versionRevision > 0)))
				dnsClientUsed = true;
		}
	}
	if (dnsClientUsed == true)
	{
		dnsClientSupported = true;
		dnsRetriesSupported = true;
		dnsTimeoutSupported = true;
		nameMappingConfig = i18n("*DEVICETYPE* devices can be configured with a list of host name to *ABBREV*IP*-ABBREV* address mappings for use within the configuration. Additionally, *DEVICETYPE* devices from *DEVICEOS* version 7.0(1) can be configured to make use of *ABBREV*DNS*-ABBREV* servers to perform name lookups. This section details those settings.");			// The text paragraph in the config section
	}

	// If there are no name servers, how can there be any lookups?
	if (dnsServer == 0)
		dnsLookupEnabled = false;

	return 0;
}


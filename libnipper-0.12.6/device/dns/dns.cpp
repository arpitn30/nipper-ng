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


DNS::DNS()
{
	hostNameList = 0;
	domainName = 0;							// The configured domain name(s)
	dnsServer = 0;							// DNS server list
	dnsForwarders = 0;						// DNS server forwarder list
	dnsRecord = 0;							// The DNS records

	nameMappingConfig = i18n("*DEVICETYPE* devices can be configured to resolve name to address mappings. This section details those settings.");			// The text paragraph in the config section

	// Host configuration
	showInterface = false;					// Are interfaces supported?

	// DNS Client Options...
	dnsClientSupported = false;				// DNS Client Supported?
	dnsLookupEnabled = false;				// DNS lookups enabled?
	disableLookup = "";						// The text and commands to disable DNS lookup
	dnsRetries = 0;							// DNS lookup retries
	dnsRetriesSupported = false;			// DNS lookup retries Supported?
	dnsTimeout = 0;							// DNS timeout
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
}


DNS::~DNS()
{
	// Variables...
	hostNameConfig *hostNamePointer = 0;
	dnsConfig *dnsPointer = 0;
	dnsRecordConfig *dnsRecordPointer = 0;

	// Host Name
	while (hostNameList != 0)
	{
		hostNamePointer = hostNameList->next;
		delete hostNameList;
		hostNameList = hostNamePointer;
	}

	// Domain Name
	while (domainName != 0)
	{
		dnsPointer = domainName->next;
		delete domainName;
		domainName = dnsPointer;
	}

	// DNS Servers
	while (dnsServer != 0)
	{
		dnsPointer = dnsServer->next;
		delete dnsServer;
		dnsServer = dnsPointer;
	}

	// DNS Forwarder Servers
	while (dnsServer != 0)
	{
		dnsPointer = dnsForwarders->next;
		delete dnsForwarders;
		dnsForwarders = dnsPointer;
	}

	// DNS Server Records
	while (dnsRecord != 0)
	{
		dnsRecordPointer = dnsRecord->next;
		delete dnsRecord;
		dnsRecord = dnsRecordPointer;
	}
}


DNS::hostNameConfig *DNS::addHostName(const char *name, const char *address)
{
	// Variables...
	hostNameConfig *hostNamePointer = 0;

	// Create
	if (hostNameList == 0)
	{
		hostNameList = new (hostNameConfig);
		hostNamePointer = hostNameList;
	}
	else
	{
		hostNamePointer = hostNameList;
		while (hostNamePointer->next != 0)
			hostNamePointer = hostNamePointer->next;
		hostNamePointer->next = new (hostNameConfig);
		hostNamePointer = hostNamePointer->next;
	}

	// Init
	hostNamePointer->name.assign(name);
	hostNamePointer->address.assign(address);
	hostNamePointer->next = 0;
	
	// Return
	return hostNamePointer;
}


DNS::dnsConfig *DNS::addDomainName(const char *name)
{
	// Variables...
	dnsConfig *dnsPointer = 0;

	// Create
	if (domainName == 0)
	{
		domainName = new (dnsConfig);
		dnsPointer = domainName;
	}
	else
	{
		dnsPointer = domainName;
		while (dnsPointer->next != 0)
		{
			if (strcasecmp(dnsPointer->name.c_str(), name) == 0)
				return dnsPointer;
			else
				dnsPointer = dnsPointer->next;
		}
		if (strcasecmp(dnsPointer->name.c_str(), name) == 0)
			return dnsPointer;
		dnsPointer->next = new (dnsConfig);
		dnsPointer = dnsPointer->next;
	}

	// Init
	dnsPointer->name.assign(name);
	dnsPointer->next = 0;

	return dnsPointer;
}


DNS::dnsConfig *DNS::addDNSServer(const char *server)
{
	// Variables...
	dnsConfig *dnsPointer = 0;

	// Create
	if (dnsServer == 0)
	{
		dnsServer = new (dnsConfig);
		dnsPointer = dnsServer;
	}
	else
	{
		dnsPointer = dnsServer;
		while (dnsPointer->next != 0)
		{
			if (strcasecmp(dnsPointer->name.c_str(), server) == 0)
				return dnsPointer;
			else
				dnsPointer = dnsPointer->next;
		}
		if (strcasecmp(dnsPointer->name.c_str(), server) == 0)
			return dnsPointer;
		dnsPointer->next = new (dnsConfig);
		dnsPointer = dnsPointer->next;
	}

	// Init
	dnsPointer->name.assign(server);
	dnsPointer->next = 0;

	return dnsPointer;
}


DNS::dnsConfig *DNS::addForwarder(const char *name)
{
	// Variables...
	dnsConfig *dnsPointer = 0;

	// Create
	if (dnsForwarders == 0)
	{
		dnsForwarders = new (dnsConfig);
		dnsPointer = dnsForwarders;
	}
	else
	{
		dnsPointer = dnsForwarders;
		while (dnsPointer->next != 0)
		{
			if (strcasecmp(dnsPointer->name.c_str(), name) == 0)
				return dnsPointer;
			else
				dnsPointer = dnsPointer->next;
		}
		if (strcasecmp(dnsPointer->name.c_str(), name) == 0)
			return dnsPointer;
		dnsPointer->next = new (dnsConfig);
		dnsPointer = dnsPointer->next;
	}

	// Init
	dnsPointer->name.assign(name);
	dnsPointer->next = 0;

	return dnsPointer;
}


DNS::dnsRecordConfig *DNS::addDNSRecord()				// Add a DNS Server DNS record
{
	// Variables
	dnsRecordConfig *dnsRecordPointer = 0;

	// Create
	if (dnsRecord == 0)
	{
		dnsRecord = new (dnsRecordConfig);
		dnsRecordPointer = dnsRecord;
	}
	else
	{
		dnsRecordPointer = dnsRecord;
		while (dnsRecordPointer->next != 0)
			dnsRecordPointer = dnsRecordPointer->next;
		dnsRecordPointer->next = new (dnsRecordConfig);
		dnsRecordPointer = dnsRecordPointer->next;
	}

	// Init
	dnsRecordPointer->singleRecord = false;
	dnsRecordPointer->next = 0;

	return dnsRecordPointer;
}


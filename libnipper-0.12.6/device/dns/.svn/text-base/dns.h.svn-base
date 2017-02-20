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

#ifndef deviceDNS_H
#define deviceDNS_H


#include "../common/deviceconfig.h"


class DNS : public DeviceConfig
{
	public:

		DNS();
		virtual ~DNS();


	// -----------------------------------------------------------------------
	// Standard Device Class Methods...
	// -----------------------------------------------------------------------

		virtual int generateConfigReport(Device *device);
		virtual int generateSecurityReport(Device *device);
		virtual int generateDeviceSpecificSecurityReport(Device *device);


	protected:

		const char *nameMappingConfig;			// The text paragraph in the config section

	// -----------------------------------------------------------------------
	// Host Name List Support...
	// -----------------------------------------------------------------------

		struct hostNameConfig
		{
			string name;
			string address;
			struct hostNameConfig *next;
		};
		hostNameConfig *hostNameList;

		// Methods...
		hostNameConfig *addHostName(const char *name, const char *address);

		// Name list options...
		bool showInterface;					// Are interfaces supported?


	// -----------------------------------------------------------------------
	// DNS Client Support...
	// -----------------------------------------------------------------------

		struct dnsConfig
		{
			string name;
			string description;
			string interface;
			struct dnsConfig *next;
		};
		dnsConfig *domainName;					// The configured domain name(s)
		dnsConfig *dnsServer;					// DNS server list

		// DNS client options...
		bool dnsClientSupported;				// DNS Client Supported?
		string dnsDomain;						// The DNS domain for the device		
		bool dnsLookupEnabled;					// DNS lookups enabled?
		const char *disableLookup;				// The text and commands to disable DNS lookup
		int dnsRetries;							// DNS lookup retries
		bool dnsRetriesSupported;				// DNS lookup retries supported?
		int dnsTimeout;							// DNS timeout
		int dnsTimeoutSupported;				// DNS timeout supported?
		bool dnsRoundRobin;						// DNS Round Robin
		bool dnsRoundRobinSupported;			// DNS Round Robin Supported?

		dnsConfig *addDomainName(const char *name);
		dnsConfig *addDNSServer(const char *server);


	// -----------------------------------------------------------------------
	// DNS Server Support...
	// -----------------------------------------------------------------------

		struct dnsRecordConfig
		{
			string recordType;					// DNS record Type
			string address;						// DNS record address
			string name;						// DNS record name
			string keepAlive;					// Keep alive message type
			bool singleRecord;					// Whether a single record or multiple are returned
			struct dnsRecordConfig *next;
		};
		dnsRecordConfig *dnsRecord;				// The DNS records
		dnsConfig *dnsForwarders;				// DNS server forwarder list

		dnsRecordConfig *addDNSRecord();		// Add a DNS Server DNS record
		dnsConfig *addForwarder(const char *name);	// Add a DNS forwarder

		// DNS Server options...
		bool dnsRecordKeepAliveSupported;		// Is the DNS keep Alive message type supported?
		bool returnRecordsSupported;			// Is the single/multiple record field supported?
		bool dynamicDNSSupported;				// Is Dynamic DNS Supported?
		bool dnsServerSupported;				// Is DNS Server Supported?
		bool dnsServiceEnabled;					// Is the DNS service enabled?
		bool dynamicDNSEnabled;					// Is dynamic DNS enabled?
		bool dnsProxySupported;					// Is DNS Proxy Server Supported?
		bool dnsProxyEnabled;					// Is the DNS Proxy service enabled?
		int dnsPort;							// DNS Server Port
};


#endif

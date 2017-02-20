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
 *      2. Any code that makes use of this library MUST display the        *
 *         returned text of the Nipper::getVersion() method. Since the     *
 *         text returned includes the version details and copyright of     *
 *         the library, the sugested place to show it would be with the    *
 *         callers "about program" information.                            *
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
#include <cstring>
#include <cstdlib>

#include "../globaldefs.h"
#include "device.h"
#include "../device/common/configline.h"
#include "general.h"
#include "administration.h"
#include "banner.h"
#include "snmp.h"
#include "filter.h"
#include "dns.h"
#include "authentication.h"
#include "interfaces.h"


CiscoSecDevice::CiscoSecDevice()
{
	deviceMake = "Cisco";
	deviceType = "Security Appliance Generic";
	deviceOS = "PIX";

	general = new (CiscoSecGeneral);
	banner = new (CiscoSecBanner);
	snmp = new (CiscoSecSNMP);
	filter = new (CiscoSecFilter);
	dns = new (CiscoSecDNS);
	authentication = new (CiscoSecAuthentication);
	interfaces = new (CiscoSecInterfaces);
}


CiscoSecDevice::~CiscoSecDevice()
{
	delete general;
	delete banner;
	delete snmp;
	delete filter;
	delete dns;
	delete authentication;
	delete interfaces;
}


Device::encryptDictionaryStruct builtincsencdict8  = {"7S8ePYKfPDzMXKcC", "network", 0};
Device::encryptDictionaryStruct builtincsencdict7  = {"BGogFIdB6jmwTyg7", "secret", &builtincsencdict8};
Device::encryptDictionaryStruct builtincsencdict6  = {"Owo3Y8stBKQ1SpVk", "administrator", &builtincsencdict7};
Device::encryptDictionaryStruct builtincsencdict5  = {"F2J0OlM3WTw7kVED", "supervisor", &builtincsencdict6};
Device::encryptDictionaryStruct builtincsencdict4  = {"PVSASRJovmamnVkD", "admin", &builtincsencdict5};
Device::encryptDictionaryStruct builtincsencdict3  = {"9jNfZuG3TC5tCVH0", "cisco123", &builtincsencdict4};
Device::encryptDictionaryStruct builtincsencdict2  = {"XejxZFfyt2wxqfff", "Cisco", &builtincsencdict3};
Device::encryptDictionaryStruct builtincsencdict1  = {"2KFQnbNIdI.2KYOU", "cisco", &builtincsencdict2};
Device::encryptDictionaryStruct builtincsencdict   = {"NuLKvvWGg.x9HEKO", "password", &builtincsencdict1}; 


int CiscoSecDevice::processDevice()
{
	// Variables...
	char line[1024];
	ConfigLine command;
	unsigned int tempInt = 0;
	int tempVersion = 0;
	bool setting = false;

	// Set encrypted dictionary...
	encryptedDictionary = &builtincsencdict;

	// The process device configuration file loop...
	while (feof(inputFile) == 0)
	{

		// Read a line from the config...
		readLine(line, sizeof(line));

		// Split it up into parts...
		command.setConfigLine(line);

		// Init
		if (strcmp(command.part(0), "no") == 0)
		{
			tempInt = 1;
			setting = false;
		}
		else
		{
			tempInt = 0;
			setting = true;
		}

		if (line[0] == '!')
		{ }

		// Object Group...
		else if (strcmp(command.part(tempInt), "object-group") == 0)
			filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Access List...
		else if (strcmp(command.part(tempInt), "access-list") == 0)
			filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Conduit...
		else if (strcmp(command.part(tempInt), "conduit") == 0)
			filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Outbound...
		else if (strcmp(command.part(tempInt), "outbound") == 0)
			filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Time Range...
		else if (strcmp(command.part(tempInt), "time-range") == 0)
			filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Enable...
		else if (strcmp(command.part(tempInt), "enable") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Username...
		else if (strcmp(command.part(tempInt), "username") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// aaa authentication...
		else if ((strcmp(command.part(tempInt), "aaa") == 0) && (strcmp(command.part(tempInt + 1), "authentication") == 0))
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// auth server...
		else if (strcmp(command.part(tempInt), "aaa-server") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Password...
		else if (strcmp(command.part(tempInt), "password") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Passwd...
		else if (strcmp(command.part(tempInt), "passwd") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// nameif...
		else if (strcmp(command.part(tempInt), "nameif") == 0)
			interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// interface...
		else if (strcmp(command.part(tempInt), "interface") == 0)
			interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// ip address...
		else if ((strcmp(command.part(tempInt), "ip") == 0) && (strcmp(command.part(tempInt + 1), "address") == 0))
			interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// failover...
		else if (strcmp(command.part(tempInt), "failover") == 0)
			interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Access Group...
		else if (strcmp(command.part(tempInt), "access-group") == 0)
			interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Hostname (in general)...
		else if (strcmp(command.part(tempInt), "hostname") == 0)
			general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// SNMP (in SNMP)...
		else if (strcmp(command.part(tempInt), "snmp-server") == 0)
			snmp->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Console...
		else if ((strcmp(command.part(tempInt), "console") == 0) && (strcmp(command.part(tempInt + 1), "timeout") == 0))
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// HTTP...
		else if (strcmp(command.part(tempInt), "http") == 0)
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Name...
		else if (strcmp(command.part(tempInt), "name") == 0)
			dns->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// domain-name...
		else if (strcmp(command.part(tempInt), "domain-name") == 0)
			dns->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// dns...
		else if (strcmp(command.part(tempInt), "dns") == 0)
			dns->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// SSH...
		else if (strcmp(command.part(tempInt), "ssh") == 0)
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Telnet...
		else if (strcmp(command.part(tempInt), "telnet") == 0)
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Banner...
		else if ((strcmp(command.part(tempInt), "banner") == 0) && ((strcmp(command.part(tempInt + 1), "exec") == 0) || (strcmp(command.part(tempInt + 1), "login") == 0) || (strcmp(command.part(tempInt + 1), "exec") == 0)))
			banner->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// SSL...
		else if (strcmp(command.part(tempInt), "ssl") == 0)
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// All others...
		else
			processDeviceSpecific(&command, (char *)&line, sizeof(line));
	}

	if ((general->version.empty()) && (config->deviceTypeChecks == true))
		return libnipper_error_wrongdevice;

	// Sort out any specified version...
	if (config->osVersion != 0)
	{
		if (strlen(config->osVersion) > 0)
		{
			general->version.assign(config->osVersion);

			// Version Major...
			tempVersion = atoi(config->osVersion);
			if ((tempVersion != 0) || (config->osVersion[0] == '0'))
			{
				general->versionMajor = tempVersion;
				tempInt = 0;
				while ((tempInt < strlen(config->osVersion)) && (config->osVersion[tempInt] > '/') && (config->osVersion[tempInt] < ':'))
					tempInt++;

				// Version Minor...
				if (tempInt < strlen(config->osVersion))
				{
					tempInt++;
					tempVersion = atoi(config->osVersion + tempInt);
					if ((tempVersion != 0) || (config->osVersion[tempInt] == '0'))
					{
						general->versionMinor = tempVersion;
						general->noMinor = false;

						while ((tempInt < strlen(config->osVersion)) && (config->osVersion[tempInt] > '/') && (config->osVersion[tempInt] < ':'))
							tempInt++;

						// Version Revision...
						if (tempInt < strlen(config->osVersion))
						{
							tempInt++;
							tempVersion = atoi(config->osVersion + tempInt);
							if ((tempVersion != 0) || (config->osVersion[tempInt] == '0'))
							{
								general->versionRevision = tempVersion;
								general->noRevision = false;

								while ((tempInt < strlen(config->osVersion)) &&(config->osVersion[tempInt] > '/') && (config->osVersion[tempInt] < ':'))
									tempInt++;

								// Version Tweak...
								if (tempInt < strlen(config->osVersion))
								{
									tempInt++;
									tempVersion = atoi(config->osVersion + tempInt);
									if ((tempVersion != 0) || (config->osVersion[tempInt] == '0'))
									{
										general->versionTweak = tempVersion;
										general->noTweak = false;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return 0;
}


int CiscoSecDevice::processDeviceSpecific(ConfigLine *command, char *line, int lineSize)
{
	lineNotProcessed(line);
	return 0;
}


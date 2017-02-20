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

// Include
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


ScreenOSDevice::ScreenOSDevice()
{
	deviceMake = "Juniper";
	deviceType = "NetScreen";
	deviceOS = "ScreenOS";

	general = new (ScreenOSGeneral);
	administration = new (ScreenOSAdministration);
	banner = new (ScreenOSBanner);
	snmp = new (ScreenOSSNMP);
	filter = new (ScreenOSFilter);
	dns = new (ScreenOSDNS);
	authentication = new (ScreenOSAuthentication);
	interfaces = new (ScreenOSInterfaces);

	isFirewall = true;							// Set to true if it is a firewall
}


ScreenOSDevice::~ScreenOSDevice()
{
	delete general;
	delete administration;
	delete banner;
	delete snmp;
	delete filter;
	delete dns;
	delete authentication;
	delete interfaces;
}

Device::encryptDictionaryStruct builtinencdict13 = {"nBh1JgrWI8BMcxVE1sfD3ZHtPvNqOn", "administrator", 0};
Device::encryptDictionaryStruct builtinencdict12 = {"nIEXLGrQKPGFclpK2srC+GItLBIaYn", "administrator", &builtinencdict13};
Device::encryptDictionaryStruct builtinencdict11 = {"nEgTC0rULyNDcfOHZsFDJSAtfiPqWn", "password", &builtinencdict12};
Device::encryptDictionaryStruct builtinencdict10 = {"nJBnMRrmG7cFc3ALdsWMLIKtWHC4ln", "administrator", &builtinencdict11};
Device::encryptDictionaryStruct builtinencdict9  = {"nL1kB1ryFpdIcuHBksgKNQLttDFjCn", "supervisor", &builtinencdict10};
Device::encryptDictionaryStruct builtinencdict8  = {"nA0XKervNIgBctzLBsjNKyEtOcM5an", "admin", &builtinencdict9};
Device::encryptDictionaryStruct builtinencdict7  = {"nFR1M7r3PBEHcA0FWs1JJ8LtBTOHIn", "netscreen", &builtinencdict8};
Device::encryptDictionaryStruct builtinencdict6  = {"nDQFBzrfECTDcLFD7sRA2kMtP4FNwn", "password", &builtinencdict7};
Device::encryptDictionaryStruct builtinencdict5  = {"nH/vDirbE5GBcjdGoslAEBBtHFA6En", "admin", &builtinencdict6};
Device::encryptDictionaryStruct builtinencdict4  = {"nMjFM0rdC9iOc+xIFsGEm3LtAeGZhn", "password", &builtinencdict5};
Device::encryptDictionaryStruct builtinencdict3  = {"nO8gOKrtJ/YMclhNlsoJCrCtllAL7n", "admin", &builtinencdict4};
Device::encryptDictionaryStruct builtinencdict2  = {"nDC0GjreNnlGcIPHTsGOUAFt6BJZdn", "password", &builtinencdict3};
Device::encryptDictionaryStruct builtinencdict1  = {"nKv3LvrdAVtOcE5EcsGIpYBtniNbUn", "netscreen", &builtinencdict2};
Device::encryptDictionaryStruct builtinencdict   = {"nKVUM2rwMUzPcrkG5sWIHdCtqkAibn", "netscreen", &builtinencdict1}; 


int ScreenOSDevice::processDevice()
{
	// Variables...
	char line[1024];
	ConfigLine command;
	unsigned int tempInt = 0;
	int tempVersion = 0;

	// Set encrypted dictionary...
	encryptedDictionary = &builtinencdict;

	// The process device configuration file loop...
	while (feof(inputFile) == 0)
	{

		// Read a line from the config...
		readLine(line, sizeof(line));

		// Split it up into parts...
		command.setConfigLine(line);

		// Hostname (in general)...
		if (strcasecmp(command.part(1), "hostname") == 0)
			general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Admin...
		else if (strcasecmp(command.part(1), "admin") == 0)
		{

			// Auth...
			if (strcasecmp(command.part(2), "auth") == 0)
			{

				// Banners...
				if (strcasecmp(command.part(3), "banner") == 0)
					banner->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

				// Server...
				if (strcasecmp(command.part(3), "server") == 0)
					authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

				// All others...
				else
					lineNotProcessed(line);
			}

			// HTTP Redirect...
			else if ((strcasecmp(command.part(2), "http") == 0) && (strcasecmp(command.part(3), "redirect") == 0))
				administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// Manager IP...
			else if (strcasecmp(command.part(2), "manager-ip") == 0)
				administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// Access Attempts...
			else if (strcasecmp(command.part(2), "access") == 0)
				authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// Admin logon...
			else if (strcasecmp(command.part(2), "name") == 0)
				authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// Password logon...
			else if (strcasecmp(command.part(2), "password") == 0)
				authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// Users...
			else if (strcasecmp(command.part(2), "user") == 0)
				authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// SSH...
			else if ((strcasecmp(command.part(2), "ssh") == 0) && (strcasecmp(command.part(3), "password") == 0))
			{

				// SSH server port...
				if (strcasecmp(command.part(4), "port") == 0)
					administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

				// All others...
				else
					lineNotProcessed(line);
			}

			// Telnet Port...
			else if ((strcasecmp(command.part(2), "telnet") == 0) && (strcasecmp(command.part(3), "port") == 0))
				administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// All others...
			else
				lineNotProcessed(line);
		}

		// Address...
		else if (strcasecmp(command.part(1), "address") == 0)
			filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Service...
		else if (strcasecmp(command.part(1), "service") == 0)
			filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Group...
		else if (strcasecmp(command.part(1), "group") == 0)
			filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Policy...
		else if (strcasecmp(command.part(1), "policy") == 0)
			filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Auth Server...
		else if (strcasecmp(command.part(1), "auth-server") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Auth Default...
		else if ((strcasecmp(command.part(1), "auth") == 0) && (strcasecmp(command.part(2), "default") == 0))
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// SNMP (in SNMP)...
		else if (strcasecmp(command.part(1), "snmp") == 0)
			snmp->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Interfaces...
		else if (strcasecmp(command.part(1), "interface") == 0)
		{

			// zone...
			if (strcasecmp(command.part(3), "zone") == 0)
			{
				administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));
				interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));
			}

			// disable...
			else if ((strcasecmp(command.part(3), "disable") == 0) || (strcasecmp(command.part(3), "shutdown") == 0))
			{
				administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));
				interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));
			}

			// ip...
			else if (strcasecmp(command.part(3), "ip") == 0)
				interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// description...
			else if (strcasecmp(command.part(3), "description") == 0)
				interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// manage...
			else if (strcasecmp(command.part(3), "manage") == 0)
				administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// All others...
			else
				lineNotProcessed(line);
		}

		// SSH...
		else if (strcasecmp(command.part(1), "ssh") == 0)
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// SSL...
		else if (strcasecmp(command.part(1), "ssl") == 0)
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Console...
		else if (strcasecmp(command.part(1), "console") == 0)
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// SCP...
		else if (strcasecmp(command.part(1), "scp") == 0)
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// NetScreen Security Manager...
		else if (strcasecmp(command.part(1), "nsmgmt") == 0)
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Domain...
		else if (strcasecmp(command.part(1), "domain") == 0)
			dns->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// DNS...
		else if (strcasecmp(command.part(1), "dns") == 0)
			dns->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Possible hostname...
		else if ((command.part(0)[strlen(command.part(0)) -2] == '-') && (command.part(0)[strlen(command.part(0)) - 1] == '>'))
			general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// All others...
		else
			lineNotProcessed(line);
	}

	if ((authentication->localUser == 0) && (config->deviceTypeChecks == true))
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


bool ScreenOSDevice::isDeviceType()
{
	// Variables...
	ConfigLine command;
	char line[1024];
	int count = 0;
	int returnCode = 0;

	// Open and check the contents of the file...
	returnCode = openInput();
	if (returnCode != 0)
		return false;

	// The process device configuration file loop...
	while ((feof(inputFile) == 0) && (count < 2))
	{

		// Read a line from the config...
		readLine(line, sizeof(line));

		// Split it up into parts...
		command.setConfigLine(line);

		if (strcmp(command.part(0), "set") == 0)
		{
			if (strcmp(command.part(1), "admin") == 0)
			{
				if (strcmp(command.part(2), "name") == 0)
					count++;

				else if (strcmp(command.part(2), "password") == 0)
					count++;
			}
		}
	}
	fclose(inputFile);

	if (count == 2)
		return true;
	else
		return false;
}


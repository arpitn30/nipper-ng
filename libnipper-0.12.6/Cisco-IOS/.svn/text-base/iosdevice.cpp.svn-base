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
#include "iosdevice.h"
#include "../device/common/configline.h"
#include "general.h"
#include "administration.h"
#include "authentication.h"
#include "banner.h"
#include "snmp.h"
#include "filter.h"
#include "dns.h"
#include "interfaces.h"


IOSDevice::IOSDevice()
{
	general = new (IOSGeneral);
	administration = new (IOSAdministration);
	authentication = new (IOSAuthentication);
	banner = new (IOSBanner);
	snmp = new (IOSSNMP);
	filter = new (IOSFilter);
	dns = new (IOSDNS);
	interfaces = new (IOSInterfaces);

	deviceMake = "Cisco";
	deviceType = "IOS Generic";
	deviceOS = "IOS";
}


IOSDevice::~IOSDevice()
{
	delete general;
	delete administration;
	delete authentication;
	delete banner;
	delete snmp;
	delete filter;
	delete dns;
	delete interfaces;
}


int IOSDevice::processDevice()
{
	// Variables...
	char line[MAX_SIZE];
	ConfigLine command;
	unsigned int tempInt = 0;
	int tempVersion = 0;
	bool setting = false;

	// The process device configuration file loop...
	while (feof(inputFile) == 0)
	{

		// Read a line from the config...
		readLine(line, MAX_SIZE);

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

		// Hostname (in general)...
		else if (strcmp(command.part(tempInt), "hostname") == 0)
			general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Version (in general)...
		else if (strcmp(command.part(tempInt), "version") == 0)
			general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Enable...
		else if (strcmp(command.part(tempInt), "enable") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Usernames...
		else if (strcmp(command.part(tempInt), "username") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Interface...
		else if (strcmp(command.part(tempInt), "interface") == 0)
			interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// aaa authentication...
		else if ((strcmp(command.part(tempInt), "aaa") == 0) && (strcmp(command.part(tempInt + 1), "authentication") == 0) && (strcmp(command.part(tempInt + 2), "banner") != 0))
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// aaa authentication...
		else if ((strcmp(command.part(tempInt), "aaa") == 0) && (strcmp(command.part(tempInt + 1), "group") == 0))
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// radius...
		else if (strcmp(command.part(tempInt), "radius-server") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// tacacs...
		else if (strcmp(command.part(tempInt), "tacacs-server") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// kerberos...
		else if ((strcmp(command.part(tempInt), "kerberos") == 0) && (strcmp(command.part(tempInt + 1), "server") == 0))
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Service lines...
		else if (strcmp(command.part(tempInt), "service") == 0)
		{
			tempInt++;

			// Password Encryption (in general)...
			if (strcmp(command.part(tempInt), "password-encryption") == 0)
				general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// Finger...
			else if (strcmp(command.part(tempInt), "finger") == 0)
				administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// NOT PROCESSED...
			else
				lineNotProcessed(line);
		}

		// IP lines...
		else if (strcmp(command.part(tempInt), "ip") == 0)
		{
			tempInt++;

			// ACL...
			if (strcmp(command.part(tempInt), "access-list") == 0)
				filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// SSH...
			else if (strcmp(command.part(tempInt), "ssh") == 0)
				administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// HTTP...
			else if (strcmp(command.part(tempInt), "http") == 0)
				administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// dns...
			else if (strcmp(command.part(tempInt), "dns") == 0)
				dns->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// dns...
			else if (strcmp(command.part(tempInt), "domain") == 0)
				dns->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// dns...
			else if (strcmp(command.part(tempInt), "domain-list") == 0)
				dns->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// dns...
			else if (strcmp(command.part(tempInt), "domain-lookup") == 0)
				dns->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// dns...
			else if (strcmp(command.part(tempInt), "domain-name") == 0)
				dns->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// dns...
			else if (strcmp(command.part(tempInt), "name-server") == 0)
				dns->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// BootP...
			else if (strcmp(command.part(tempInt), "bootp") == 0)
				administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// Finger...
			else if (strcmp(command.part(tempInt), "finger") == 0)
				administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// NOT PROCESSED...
			else
				lineNotProcessed(line);
		}

		// SNMP (in snmp)...
		else if (strcmp(command.part(tempInt), "snmp-server") == 0)
			snmp->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Banner...
		else if (strcmp(command.part(tempInt), "banner") == 0)
			banner->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// aaa authentication...
		else if ((strcmp(command.part(tempInt), "aaa") == 0) && (strcmp(command.part(tempInt + 1), "authentication") == 0) && (strcmp(command.part(tempInt + 2), "banner") == 0))
			banner->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Access List...
		else if (strcmp(command.part(tempInt), "access-list") == 0)
			filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Line (in Administration)...
		else if (strcmp(command.part(tempInt), "line") == 0)
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// CDP...
		else if ((strcmp(command.part(tempInt), "cdp") == 0) && (strcmp(command.part(tempInt), "run") == 0))
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// NOT PROCESSED...
		else
			lineNotProcessed(line);
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


void IOSDevice::setPostDefaults()
{
}


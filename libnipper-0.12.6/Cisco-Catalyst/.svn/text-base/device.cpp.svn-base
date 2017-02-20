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

#include "../globaldefs.h"
#include "device.h"
#include "../device/common/configline.h"
#include "general.h"
#include "administration.h"
#include "banner.h"
#include "snmp.h"
#include "dns.h"
#include "authentication.h"
#include "interfaces.h"


CatalystDevice::CatalystDevice()
{
	deviceMake = "Cisco";
	deviceType = "Catalyst";
	deviceOS = "CatOS";

	general = new (CatalystGeneral);
	administration = new (CatalystAdministration);
	banner = new (CatalystBanner);
	snmp = new (CatalystSNMP);
	dns = new (CatalystDNS);
	authentication = new (CatalystAuthentication);
	interfaces = new (CatalystInterfaces);
}


CatalystDevice::~CatalystDevice()
{
	delete general;
	delete administration;
	delete banner;
	delete snmp;
	delete dns;
	delete authentication;
	delete interfaces;
}


int CatalystDevice::processDevice()
{
	// Variables...
	char line[1024];
	ConfigLine command;
	int tempInt = 0;
	bool setting = false;

	// The process device configuration file loop...
	while (feof(inputFile) == 0)
	{

		// Read a line from the config...
		readLine(line, sizeof(line));

		// Split it up into parts...
		command.setConfigLine(line);

		// Init
		tempInt = 1;
		if (strcmp(command.part(0), "set") == 0)
			setting = true;
		else
			setting = false;

		// Version (in general)...
		if (strcmp(command.part(0), "#version") == 0)
			general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// System...
		else if (strcmp(command.part(tempInt), "system") == 0)
		{
			tempInt++;

			// Hostname (in general)...
			if (strcmp(command.part(tempInt), "name") == 0)
				general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// Location (in general)...
			else if (strcmp(command.part(tempInt), "location") == 0)
				general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// Contact (in general)...
			else if (strcmp(command.part(tempInt), "contact") == 0)
				general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// Core File (in general)...
			else if (strcmp(command.part(tempInt), "core-file") == 0)
				general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// Syslog File (in general)...
			else if (strcmp(command.part(tempInt), "syslog-file") == 0)
				general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// All others...
			else
				lineNotProcessed(line);
		}

		// SNMP...
		else if (strcmp(command.part(tempInt), "snmp") == 0)
			snmp->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Set SSH...
		else if ((strcmp(command.part(tempInt), "ssh") == 0) && (strcmp(command.part(tempInt + 1), "mode") == 0))
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// VLAN...
		else if (strcmp(command.part(tempInt), "vlan") == 0)
			interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Port...
		else if (strcmp(command.part(tempInt), "port") == 0)
			interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// trunking...
		else if (strcmp(command.part(tempInt), "trunk") == 0)
			interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// CDP...
		else if ((strcmp(command.part(tempInt), "cdp") == 0) && ((strcmp(command.part(tempInt + 1), "enable") == 0) || (strcmp(command.part(tempInt + 1), "disable") == 0)))
			interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Interface...
		else if (strcmp(command.part(tempInt), "interface") == 0)
			interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// IP...
		else if (strcmp(command.part(tempInt), "ip") == 0)
		{
			tempInt++;

			// Telnet...
			if (strcmp(command.part(tempInt), "telnet") == 0)
				administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// HTTP...
			else if (strcmp(command.part(tempInt), "http") == 0)
				administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// DNS...
			else if (strcmp(command.part(tempInt), "dns") == 0)
				dns->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// unreachable...
			else if (strcmp(command.part(tempInt), "unreachable") == 0)
				interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// redirect...
			else if (strcmp(command.part(tempInt), "redirect") == 0)
				interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// All others...
			else
				lineNotProcessed(line);
		}

		// Banner...
		else if (strcmp(command.part(tempInt), "banner") == 0)
			banner->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Authentication...
		else if (strcmp(command.part(tempInt), "authentication") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// TACACS...
		else if (strcmp(command.part(tempInt), "tacacs") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Kerberos...
		else if (strcmp(command.part(tempInt), "kerberos") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Radius...
		else if (strcmp(command.part(tempInt), "radius") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// enablepass...
		else if (strcmp(command.part(tempInt), "enablepass") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// password...
		else if (strcmp(command.part(tempInt), "password") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Prompt (in general)...
		else if (strcmp(command.part(tempInt), "prompt") == 0)
			general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// All others...
		else
			lineNotProcessed(line);
	}

	if ((general->version.empty()) && (config->deviceTypeChecks == true))
		return libnipper_error_wrongdevice;

	return 0;
}

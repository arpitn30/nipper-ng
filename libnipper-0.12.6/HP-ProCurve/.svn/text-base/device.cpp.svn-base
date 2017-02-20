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


ProCurveDevice::ProCurveDevice()
{
	deviceMake = "HP";
	deviceType = "ProCurve";
	deviceOS = "ProCurve *ABBREV*OS*-ABBREV*";

	isSwitch = true;

	general = new (ProCurveGeneral);
	administration = new (ProCurveAdministration);
	banner = new (ProCurveBanner);
	snmp = new (ProCurveSNMP);
	dns = new (ProCurveDNS);
	authentication = new (ProCurveAuthentication);
	interfaces = new (ProCurveInterfaces);
}


ProCurveDevice::~ProCurveDevice()
{
	delete general;
	delete administration;
	delete banner;
	delete snmp;
	delete dns;
	delete authentication;
	delete interfaces;
}


int ProCurveDevice::processDevice()
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

		// Hostname (in general)...
		if (strcasecmp(command.part(tempInt), "hostname") == 0)
			general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));


		// Device Model / Version...
		else if ((strcmp(command.part(tempInt), ";") == 0) && (strcasecmp(command.part(tempInt + 2), "Configuration") == 0) && (strcasecmp(command.part(tempInt + 3), "Editor;") == 0))
			general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Modules...
		else if ((strcmp(command.part(tempInt), "module") == 0) && (strcasecmp(command.part(tempInt + 2), "type") == 0))
			general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// IP...
		else if (strcmp(command.part(tempInt), "ip") == 0)
		{
			tempInt++;

			// SSH...
			if (strcmp(command.part(tempInt), "ssh") == 0)
				administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// Authorised Managers...
			else if (strcmp(command.part(tempInt), "authorized-managers") == 0)
				administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// DNS...
			else if (strcmp(command.part(tempInt), "dns") == 0)
				dns->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// All others...
			else
				lineNotProcessed(line);
		}

		// VLAN...
		else if (strcmp(command.part(tempInt), "vlan") == 0)
			interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Telnet...
		else if ((strcasecmp(command.part(tempInt), "telnet-server") == 0) || (strcasecmp(command.part(tempInt), "telnet6-server") == 0))
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// TFTP Server...
		else if ((strcasecmp(command.part(tempInt), "tftp") == 0) && (strcasecmp(command.part(tempInt + 1), "server") == 0))
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// TACACS+ Server...
		else if (strcasecmp(command.part(tempInt), "tacacs-server") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// RADIUS Server...
		else if (strcasecmp(command.part(tempInt), "radius-server") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// AAA Authentication...
		else if ((strcasecmp(command.part(tempInt), "aaa") == 0) && (strcasecmp(command.part(tempInt + 1), "authentication") == 0))
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Password...
		else if (strcasecmp(command.part(tempInt), "password") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// SNMP...
		else if ((strcasecmp(command.part(tempInt), "snmp-server") == 0) || (strcasecmp(command.part(tempInt), "snmpv3") == 0))
			snmp->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Web Management...
		else if (strcasecmp(command.part(tempInt), "web-management") == 0)
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Banner MOTD...
		else if ((strcmp(command.part(0), "banner") == 0) && (strcmp(command.part(1), "motd") == 0))
			banner->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Console...
		else if ((strcmp(command.part(tempInt), "console") == 0) && (strcmp(command.part(tempInt + 1), "events") != 0))
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// All others...
		else
			lineNotProcessed(line);
	}

	if ((general->version.empty()) && (config->deviceTypeChecks == true))
		return libnipper_error_wrongdevice;

	return 0;
}


bool ProCurveDevice::isDeviceType()
{
	// Variables...
	char line[1024];
	bool found = false;
	int readCount = 0;
	int returnCode = 0;

	// Open and check the contents of the file...
	returnCode = openInput();
	if (returnCode != 0)
		return false;

	// The process device configuration file loop...
	while ((feof(inputFile) == 0) && (found == false) && (readCount < 5))
	{

		// Read a line from the config...
		readLine(line, sizeof(line));

		if ((strncmp(line, "; J", 3) == 0) && (strstr(line, "Configuration Editor; Created on release") != 0))
			found = true;

		readCount++;
	}
	fclose(inputFile);

	return found;
}

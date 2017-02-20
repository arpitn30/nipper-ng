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
#include "filter.h"
#include "authentication.h"
#include "interfaces.h"


CiscoCSSDevice::CiscoCSSDevice()
{
	deviceMake = "Cisco";
	deviceType = "*ABBREV*CSS*-ABBREV*";
	deviceOS = "*ABBREV*CSS*-ABBREV* *ABBREV*OS*-ABBREV*";

	general = new (CiscoCSSGeneral);
	administration = new (CiscoCSSAdministration);
	banner = new (CiscoCSSBanner);
	snmp = new (CiscoCSSSNMP);
	dns = new (CiscoCSSDNS);
	filter = new (CiscoCSSFilter);
	authentication = new (CiscoCSSAuthentication);
	interfaces = new (CiscoCSSInterfaces);
}


CiscoCSSDevice::~CiscoCSSDevice()
{
	delete general;
	delete administration;
	delete banner;
	delete snmp;
	delete dns;
	delete filter;
	delete authentication;
	delete interfaces;
}


int CiscoCSSDevice::processDevice()
{
	// Variables...
	char line[1024];
	int tempInt = 0;
	bool setting = true;
	bool deviceOk = false;
	ConfigLine command;

	// The process device configuration file loop...
	while (feof(inputFile) == 0)
	{

		// Read a line from the config...
		readLine(line, sizeof(line));

		// Split it up into parts...
		command.setConfigLine(line);

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

		// Version (in general)...
		if ((strcmp(command.part(0), "!Active") == 0) && (strcmp(command.part(1), "version:") == 0))
			general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Potential hostname...
		else if ((command.part(0)[strlen(command.part(0)) - 1] == '#') && (strncmp(command.part(1), "sh", 2) == 0) && (strncmp(command.part(2), "run", 3) == 0))
			general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// SNMP...
		else if (strcmp(command.part(tempInt), "snmp") == 0)
		{
			snmp->processDeviceConfig(this, &command, (char *)&line, sizeof(line));
			tempInt++;
			if (strcmp(command.part(tempInt), "name") == 0)
				general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));
		}
		else if ((strcmp(command.part(tempInt), "restrict") == 0) && (strcmp(command.part(tempInt + 1), "snmp") == 0))
			snmp->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Restrict other things...
		else if (strcmp(command.part(tempInt), "restrict") == 0)
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Interfaces...
		else if (strcmp(command.part(tempInt), "interface") == 0)
			interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Circuites...
		else if (strcmp(command.part(tempInt), "circuit") == 0)
			interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// SSHD...
		else if (strcmp(command.part(tempInt), "sshd") == 0)
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Web-mgmt...
		else if (strcmp(command.part(tempInt), "web-mgmt") == 0)
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// ACL...
		else if (strcmp(command.part(tempInt), "acl") == 0)
			filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// NQL...
		else if (strcmp(command.part(tempInt), "nql") == 0)
			filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Banner...
		else if (strcmp(command.part(tempInt), "prelogin-banner") == 0)
			banner->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// DNS...
		else if (strcmp(command.part(tempInt), "dns") == 0)
			dns->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// DNS Records...
		else if (strcmp(command.part(tempInt), "dns-record") == 0)
			dns->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// DNS Server...
		else if (strcmp(command.part(tempInt), "dns-server") == 0)
			dns->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// TACACS+...
		else if (strcmp(command.part(tempInt), "tacacs-server") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// RADIUS...
		else if (strcmp(command.part(tempInt), "radius-server") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Virtual...
		else if (strcmp(command.part(tempInt), "virtual") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Console...
		else if (strcmp(command.part(tempInt), "console") == 0)
			authentication->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Core Dumps...
		else if (strcmp(command.part(tempInt), "dump") == 0)
			general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		else if (strncmp(line, "!*************************** GLOBAL ***************************", 63) == 0)
			deviceOk = true;

		// All others...
		else
			lineNotProcessed(line);
	}

	if ((deviceOk == false) && (config->deviceTypeChecks == true))
		return libnipper_error_wrongdevice;

	return 0;
}


bool CiscoCSSDevice::isDeviceType()
{
	// Variables...
	char line[1024];
	bool found = false;
	int count = 0;
	int returnCode = 0;

	// Open and check the contents of the file...
	returnCode = openInput();
	if (returnCode != 0)
		return false;

	// The process device configuration file loop...
	while ((feof(inputFile) == 0) && (found == false) && (count < 15))
	{

		// Read a line from the config...
		readLine(line, sizeof(line));

		if (strncmp(line, "!*************************** GLOBAL ***************************", 63) == 0)
			found = true;

		count++;
	}
	fclose(inputFile);

	return found;
}


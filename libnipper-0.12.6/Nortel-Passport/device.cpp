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

// Includes...
#include <cstring>

#include "../globaldefs.h"
#include "device.h"
#include "../device/common/configline.h"
#include "general.h"
#include "administration.h"
#include "banner.h"
#include "snmp.h"
#include "filter.h"
#include "interfaces.h"


PassportDevice::PassportDevice()
{
	deviceMake = "Nortel";
	deviceType = "Passport";
	deviceOS = "Passport OS";

	general = new (PassportGeneral);
	administration = new (PassportAdministration);
	banner = new (PassportBanner);
	snmp = new (PassportSNMP);
	filter = new (PassportFilter);
	interfaces = new (PassportInterfaces);
}


PassportDevice::~PassportDevice()
{
	delete general;
	delete administration;
	delete banner;
	delete snmp;
	delete filter;
	delete interfaces;
}


int PassportDevice::processDevice()
{
	// Variables...
	char line[1024];
	ConfigLine command;
	int tempInt = 0;

	// The process device configuration file loop...
	while (feof(inputFile) == 0)
	{
		tempInt = 0;

		// Read a line from the config...
		readLine(line, sizeof(line));

		// Split it up into parts...
		command.setConfigLine(line);

		// Hostname (in general)...
		if (strcmp(command.part(tempInt), "#") == 0)
		{
			tempInt++;

			// Box type...
			if ((strcmp(command.part(tempInt), "box") == 0) && (strcmp(command.part(tempInt + 1), "type") == 0) && (strcmp(command.part(tempInt + 2), ":") == 0))
				general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// Software Version...
			else if ((strcmp(command.part(tempInt), "software") == 0) && (strcmp(command.part(tempInt + 1), "version") == 0) && (strcmp(command.part(tempInt + 2), ":") == 0))
				general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// Monitor Version...
			else if ((strcmp(command.part(tempInt), "monitor") == 0) && (strcmp(command.part(tempInt + 1), "version") == 0) && (strcmp(command.part(tempInt + 2), ":") == 0))
				general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// Modules
			else if (strcmp(command.part(tempInt), "Slot") == 0)
				general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			else
				lineNotProcessed(line);
		}

		// Ethernet
		else if (strcmp(command.part(0), "ethernet") == 0)
			interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// VLAN
		else if (strcmp(command.part(0), "vlan") == 0)
			interfaces->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Traffic Filtering
		else if ((strcmp(command.part(tempInt), "ip") == 0) && (strcmp(command.part(tempInt + 1), "traffic-filter") == 0))
			filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		else if ((strcmp(command.part(tempInt), "sys") == 0) && (strcmp(command.part(tempInt + 1), "set") == 0))
		{
			tempInt += 2;

			// contact...
			if (strcmp(command.part(tempInt), "contact") == 0)
				general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// location...
			if (strcmp(command.part(tempInt), "location") == 0)
				general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// SNMP...
			if (strcmp(command.part(tempInt), "snmp") == 0)
				snmp->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			else
				lineNotProcessed(line);
		}

		else if (strcmp(command.part(tempInt), "cli") == 0)
		{
			tempInt++;

			// banner...
			if (strcmp(command.part(tempInt), "banner") == 0)
				banner->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			// motd...
			else if (strcmp(command.part(tempInt), "motd") == 0)
				banner->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

			else
				lineNotProcessed(line);
		}

		// All others...
		else
			lineNotProcessed(line);
	}

	if ((general->version.empty()) && (config->deviceTypeChecks == true))
		return libnipper_error_wrongdevice;

	return 0;
}


bool PassportDevice::isDeviceType()
{
	// Variables...
	ConfigLine command;
	char line[1024];
	bool found = false;
	int lineCount = 0;
	int returnCode = 0;

	// Open and check the contents of the file...
	returnCode = openInput();
	if (returnCode != 0)
		return false;

	// The process device configuration file loop...
	while ((feof(inputFile) == 0) && (found == false) && (lineCount < 15))
	{

		// Read a line from the config...
		readLine(line, sizeof(line));

		// Split it up into parts...
		command.setConfigLine(line);

		if ((strcmp(command.part(0), "#") == 0) && (strcmp(command.part(1), "box") == 0) && (strcmp(command.part(2), "type") == 0) && (strcmp(command.part(3), ":") == 0))
			found = true;

		else if ((strcmp(command.part(0), "#") == 0) && (strcmp(command.part(1), "software") == 0) && (strcmp(command.part(2), "version") == 0) && (strcmp(command.part(3), ":") == 0))
			found = true;
	}
	fclose(inputFile);

	return found;
}


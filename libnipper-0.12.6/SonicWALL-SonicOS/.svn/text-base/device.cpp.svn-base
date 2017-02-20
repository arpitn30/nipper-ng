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

// Includes
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>
#include <cstdlib>

#include "../globaldefs.h"
#include "../device/errortext.h"
#include "device.h"
#include "../device/common/configline.h"
#include "general.h"
#include "filter.h"
#include "snmp.h"
#include "administration.h"
#include "dns.h"


SonicOSDevice::SonicOSDevice()
{
	deviceMake = "SonicWALL";
	deviceType = "Internet Security Applicance";
	deviceOS = "SonicOS";

	isFirewall = true;

	general = new (SonicOSGeneral);
	administration = new (SonicOSAdministration);
	filter = new (SonicOSFilter);
	snmp = new (SonicOSSNMP);
	dns = new (SonicOSDNS);
}


SonicOSDevice::~SonicOSDevice()
{
	delete general;
	delete filter;
	delete snmp;
	delete administration;
	delete dns;
}


int SonicOSDevice::process()
{
	// Variables...
	string tempString;
	string unencodedFile;
	struct stat *fileStats = 0;
	char *buffer = 0;
	int returnCode = 0;

	// Open Input...
	returnCode = openInput();
	if (returnCode == 0)
	{

		// Get file size...
		fileStats = new (struct stat);
		memset(fileStats, 0, sizeof(struct stat));
		stat(config->inputSource, fileStats);

		// Reserve Base64 decode buffer...
		buffer = new (nothrow) char [fileStats->st_size + 1];
		memset (buffer, 0, fileStats->st_size + 1);

		// Read in the whole configuration...
		fread(buffer, 1, fileStats->st_size, inputFile);

		// Close Input...
		fclose(inputFile);

		// Base64/URL decode...
		tempString.assign(urlDecode(base64Decode(buffer), true));

		// Free Buffer...
		delete[] buffer;

		// Open New Temporary File and save decoded config to it
		unencodedFile.assign(TEMP_DIR);
		unencodedFile.append("delete-me");
		unencodedFile.append(intToString(rand()));	
		inputFile = fopen(unencodedFile.c_str(), "w");
		if (inputFile == NULL)
			return deviceerror_openingfile;
		fwrite(tempString.c_str(), 1, tempString.length(), inputFile);
		fclose(inputFile);

		// Open Input...
		config->inputSource = unencodedFile.c_str();
		returnCode = openInput();
		if (returnCode == 0)
		{

			returnCode = processDevice();

			// Close Input...
			fclose(inputFile);
	
			// Post processing defaults...
			setPostCommonDefaults();

			// Post device specific processing defaults...
			setPostDefaults();
		}
	}

	return returnCode;
}


int SonicOSDevice::processDevice()
{
	// Variables...
	char line[1024];
	ConfigLine command;

	// The process device configuration file loop...
	while (feof(inputFile) == 0)
	{

		// Read a line from the config...
		readLine(line, sizeof(line));

		// Split it up into parts...
		command.setConfigLine(line);

		// Hostname (in general)...
		if (strcmp(command.part(0), "firewallName") == 0)
			general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Serial Number
		else if (strcmp(command.part(0), "serialNumber") == 0)
			general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Firewall Policies...
		else if (strncmp(command.part(0), "policy", 6) == 0)
			filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Firewall Rules...
		else if (strncmp(command.part(0), "prefs_rule", 10) == 0)
			filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Addresses...
		else if (strncmp(command.part(0), "addrObj", 7) == 0)
			filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Address Groups...
		else if ((strncmp(command.part(0), "addro_grpToGrp_", 15) == 0) || (strncmp(command.part(0), "addro_atomToGrp_", 16) == 0))
			filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Services...
		else if ((strncmp(command.part(0), "svcObj", 6) == 0) || (strncmp(command.part(0), "prefs_svc", 9) == 0))
			filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Service Groups...
		else if ((strncmp(command.part(0), "so_atomToGrp_", 13) == 0) || (strncmp(command.part(0), "so_grpToGrp_", 12) == 0))
			filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// SNMP...
		else if (strncmp(command.part(0), "snmp_", 5) == 0)
			snmp->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Administration HTTP...
		else if (strncmp(command.part(0), "http", 4) == 0)
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// DNS...
		else if (strcmp(command.part(0), "dnsSrvAddr") == 0)
			dns->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// DNS...
		else if (strncmp(command.part(0), "dnsServer", 9) == 0)
			dns->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// Administration Interfaces...
		else if ((strncmp(command.part(0), "iface_", 6) == 0) || (strncmp(command.part(0), "interface_Zone_", 15) == 0))
			administration->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

		// All others...
		else
			lineNotProcessed(line);
	}

	return 0;
}


bool SonicOSDevice::isDeviceType()
{
	// Variables...
	string tempString;
	string unencodedFile;
	struct stat *fileStats = 0;
	char *buffer = 0;
	int returnCode = 0;

	// Open Input...
	returnCode = openInput();
	if (returnCode == 0)
	{

		// Get file size...
		fileStats = new (struct stat);
		memset(fileStats, 0, sizeof(struct stat));
		stat(config->inputSource, fileStats);

		// Reserve Base64 decode buffer...
		buffer = new (nothrow) char [fileStats->st_size + 1];
		memset (buffer, 0, fileStats->st_size + 1);

		// Read in the whole configuration...
		fread(buffer, 1, fileStats->st_size, inputFile);

		// Close Input...
		fclose(inputFile);

		// Base64/URL decode...
		tempString.assign(urlDecode(base64Decode(buffer), true));

		// Free Buffer...
		delete[] buffer;

		if (tempString.find("firewallName") != string::npos)
			return true;
	}

	return false;
}



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
#include <cstring>

#include "../globaldefs.h"
#include "device.h"
#include "../device/common/configline.h"


CiscoCatalystNMPDevice::CiscoCatalystNMPDevice()
{
	deviceMake = "Cisco";
	deviceType = "Catalyst";
	deviceOS = "NMP";
}


bool CiscoCatalystNMPDevice::isDeviceType()
{
	// Variables...
	ConfigLine command;
	char line[1024];
	int count = 0;
	int lineCount = 0;
	int returnCode = 0;

	// Open and check the contents of the file...
	returnCode = openInput();
	if (returnCode != 0)
		return false;

	// The process device configuration file loop...
	while ((feof(inputFile) == 0) && (count < 3) && (lineCount < 50))
	{

		// Read a line from the config...
		readLine(line, sizeof(line));

		// Split it up into parts...
		command.setConfigLine(line);

		if (strcmp(command.part(0), "#version") == 0)
			count++;

		else if (strcmp(command.part(0), "#system") == 0)
			count++;

		else if (strstr(line, "NmpSW") != 0)
			count++;
	}
	fclose(inputFile);

	if (count > 2)
		return true;
	else
		return false;
}

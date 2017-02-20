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


#include "../globaldefs.h"
#include "device.h"
#include "../device/common/configline.h"
#include "general.h"


TemplateDevice::TemplateDevice()
{
	deviceMake = "Template Manufacturer";
	deviceType = "Template Device";
	deviceOS = "Template OS";
}


int TemplateDevice::processDevice()
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
/*		tempInt = 1;
		if (strcmp(command.part(0), "unset") == 0)
			setting = false;
		else if (strcmp(command.part(0), "set") == 0)
			setting = true;

		// Hostname (in general)...
		if (strcmp(command.part(tempInt), "hostname") == 0)
		{
			if (general == 0)
				general = new ScreenOSGeneral;
			general->processDeviceConfig(this, &command, (char *)&line, sizeof(line));
		}*/

		// All others...
		else
			lineNotProcessed(line);
	}

	return 0;
}

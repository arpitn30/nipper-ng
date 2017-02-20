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
 *      2. Any code that integrates Nipper MUST display the copyright      *
 *         information below with the programs own copyright information.  *
 *                                                                         *
 *         "Nipper Copyright (C) 2006 - 2008 by Ian Ventura-Whiting"       *
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


// Process Restrict
void processCSSRestrict(char *line, struct nipperConfig *nipper)
{
	// Variables
	int tempInt = 0;
	int setting = 0;
	struct ciscoCommand command;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Restrict Line: %s\n", line);
	}

	// Init
	command = splitLine(line);

	// No line?
	if (strcmp(command.part[0], "no") == 0)
	{
		tempInt = 2;
		setting = true;
	}
	else
	{
		tempInt = 1;
		setting = false;
	}

	// FTP
	if (strcmp(command.part[tempInt], "ftp") == 0)
		nipper->css->ftpAccess = setting;

	// Telnet
	else if (strcmp(command.part[tempInt], "telnet") == 0)
		nipper->css->telnetAccess = setting;

	// SNMP
	else if (strcmp(command.part[tempInt], "snmp") == 0)
		nipper->css->snmpAccess = setting;

	// SSH
	else if (strcmp(command.part[tempInt], "ssh") == 0)
		nipper->css->sshAccess = setting;

	// Console
	else if (strcmp(command.part[tempInt], "console") == 0)
		nipper->css->consoleAccess = setting;

	// Web Management
	else if (strcmp(command.part[tempInt], "web-mgmt") == 0)
		nipper->css->webManagementAccess = setting;

	// Debug (lines not processed)
	else if (nipper->linesnotprocessed == true)
		printf("%s\n", line);
}



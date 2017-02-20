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
#include "../globaldefs.h"
#include "iosdevice.h"
#include "administration.h"


IOSAdministration::lineConfig *IOSAdministration::addLine()
{
	// Variables...
	lineConfig *linePointer = 0;

	// Create...
	if (line == 0)
	{
		line = new (lineConfig);
		linePointer = line;
	}
	else
	{
		linePointer = line;
		while (linePointer->next != 0)
			linePointer = linePointer->next;
		linePointer->next = new (lineConfig);
		linePointer = linePointer->next;
	}

	// Init...
	linePointer->type = lineConsole;				// line_console...
	linePointer->lineStart = 0;					// i.e. VTY - 0
	linePointer->lineEnd = 0;						// i.e. VTY - 4
	linePointer->login = loginLinePassword;		// login_disabled...
	linePointer->exec = true;						// true (default) or false
	linePointer->privilege = 1;					// Privilege level
	linePointer->callback = false;					// true or false (default)
	linePointer->encryption = false;				// password encrypted?...
	linePointer->passwordInDict = false;			// password in the dictionary?
	linePointer->passwordWeak = Device::passwordPassed;	// password weak?
	linePointer->accounting = false;
	linePointer->authorization = false;
	linePointer->defaultSettings = true;			// true if no transport line has been set
	linePointer->output = true;
	linePointer->ssh = true;						// true, false
	linePointer->telnet = true;					// true, false
	linePointer->rlogin = true;					// true, false
	linePointer->all = true;						// true, false
	linePointer->execTimeout = 600;				// Exec timeout in seconds, 0 = no timeout (default)
	linePointer->absoluteTimeout = 0;
	linePointer->sessionTimeout = 0;
	linePointer->loginTimeout = 30;
	linePointer->next = 0;

	return linePointer;
}


int IOSAdministration::generateDeviceSpecificConfig(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	lineConfig *linePointer = 0;
	string tempString;
	int errorCode = 0;

	if (device->isRouter == true)
	{
		device->addPort("rlogin");

		// Add service to the services list...
		paragraphPointer = device->getTableParagraphPointer("CONFIG-SERVICES-TABLE");
		device->addTableData(paragraphPointer->table, i18n("Rlogin Service"));
		if (rloginEnabled == true)
			device->addTableData(paragraphPointer->table, i18n("Enabled"));
		else
			device->addTableData(paragraphPointer->table, i18n("Disabled"));

		// Rlogin Settings section...
		configReportPointer = device->getConfigSection("CONFIG-ADMIN");
		paragraphPointer = device->addParagraph(configReportPointer);
		paragraphPointer->paragraphTitle.assign(i18n("Rlogin Service Settings"));
		paragraphPointer->paragraph.assign(i18n("The Rlogin service enables remote administrative access to a *ABBREV*CLI*-ABBREV* on *DEVICETYPE* devices. The Telnet protocol implemented by the service is simple and provides no encryption of the network communications between the client and the server. This section details the Rlogin service settings."));

		// Rlogin Settings Table...
		errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINRLOGIN-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("Rlogin service settings");
		device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Setting"), false);
		device->addTableData(paragraphPointer->table, i18n("Rlogin Service"));
		if (rloginEnabled == true)
			device->addTableData(paragraphPointer->table, i18n("Enabled"));
		else
			device->addTableData(paragraphPointer->table, i18n("Disabled"));
		device->addTableData(paragraphPointer->table, i18n("Service *ABBREV*TCP*-ABBREV* Port"));
		device->addTableData(paragraphPointer->table, "513");

		paragraphPointer = device->addParagraph(configReportPointer);
		paragraphPointer->paragraph.assign(i18n("Access using the Rlogin service is configured using lines on *DEVICETYPE* devices. These lines are listed in Table *TABLEREF*."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "IOS-RLOGINLINE-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title.assign(i18n("Rlogin line configuration"));
		device->addTableHeading(paragraphPointer->table, i18n("Line"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Exec"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Login"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Level"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Password"), true);
		device->addTableHeading(paragraphPointer->table, i18n("Authorisation"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Accounting"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*ACL*-ABBREV*"), false);

		linePointer = line;
		while (linePointer != 0)
		{

			// If line is used...
			if ((linePointer->type == lineVTY) && (linePointer->rlogin == true) && (linePointer->exec == true) && !((linePointer->password.empty()) && (linePointer->login == loginLinePassword)))
			{
				switch (linePointer->type)
				{
					case lineConsole:
						device->addTableData(paragraphPointer->table, i18n("Console"));
						break;
					case lineVTY:
						tempString.assign(i18n("*ABBREV*VTY*-ABBREV* "));
						tempString.append(device->intToString(linePointer->lineStart));
						if (linePointer->lineEnd != 0)
						{
							tempString.append(" - ");
							tempString.append(device->intToString(linePointer->lineEnd));
						}
						device->addTableData(paragraphPointer->table, tempString.c_str());
						break;
					case lineAUX:
						device->addTableData(paragraphPointer->table, i18n("Auxillary"));
						break;
					default:
						tempString.assign(i18n("*ABBREV*TTY*-ABBREV* "));
						tempString.append(device->intToString(linePointer->lineStart));
						if (linePointer->lineEnd != 0)
						{
							tempString.append(" - ");
							tempString.append(device->intToString(linePointer->lineEnd));	
						}
						device->addTableData(paragraphPointer->table, tempString.c_str());
						break;
				}
				if (linePointer->exec == true)
				{
					device->addTableData(paragraphPointer->table, i18n("Yes"));
					switch (linePointer->login)
					{
						case loginWithNoPassword:
							device->addTableData(paragraphPointer->table, i18n("No Authentication"));
							break;
						case loginLinePassword:
							device->addTableData(paragraphPointer->table, i18n("Line Password"));
							break;
						case loginLocal:
							device->addTableData(paragraphPointer->table, i18n("Local Users"));
							break;
						case loginTACACS:
							device->addTableData(paragraphPointer->table, i18n("*ABBREV*TACACS*-ABBREV* Style"));
							break;
						default:
							device->addTableData(paragraphPointer->table, i18n("*ABBREV*AAA*-ABBREV* Authentication"));
							break;
					}
				}
				else
				{
					device->addTableData(paragraphPointer->table, i18n("No"));
					device->addTableData(paragraphPointer->table, i18n("N/A"));
				}
				tempString.assign(device->intToString(linePointer->privilege));
				device->addTableData(paragraphPointer->table, tempString.c_str());
				device->addTableData(paragraphPointer->table, linePointer->password.c_str());
				if (linePointer->accounting == false)
					device->addTableData(paragraphPointer->table, i18n("Off"));
				else
				{
					tempString.assign(i18n("On"));
					tempString.append(" (");
					tempString.append(linePointer->accList);
					tempString.append(")");
					device->addTableData(paragraphPointer->table, tempString.c_str());
				}
				if (linePointer->authorization == false)
					device->addTableData(paragraphPointer->table, i18n("Off"));
				else
				{
					tempString.assign(i18n("On"));
					tempString.append(" (");
					tempString.append(linePointer->authList);
					tempString.append(")");
					device->addTableData(paragraphPointer->table, tempString.c_str());
				}
				device->addTableData(paragraphPointer->table, linePointer->aclIn.c_str());
			}
			linePointer = linePointer->next;
		}
	}


	// Line Settings section...
	configReportPointer = device->getConfigSection("CONFIG-ADMIN");
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraphTitle.assign(i18n("Line Settings"));
	paragraphPointer->paragraph.assign(i18n("The line settings are used on *DEVICETYPE* devices to configure inbound and outbound administrative access using a number of different services. The previous sections have covered the specific administration services and their authentication configurations. This section details all the lines configured on *DEVICENAME* and the timeouts and *ABBREV*ACLs*-ABBREV* configured for inbound and outbound connections."));

	// Table...
	errorCode = device->addTable(paragraphPointer, "IOS-LINES-TABLE");
	if (errorCode != 0)
		return errorCode;
	paragraphPointer->table->title.assign(i18n("Line timeout and *ABBREV*ACL*-ABBREV* configuration"));
	device->addTableHeading(paragraphPointer->table, i18n("Line"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Exec"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Absolute"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Session"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Login"), true);
	device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*ACL*-ABBREV* In"), false);
	device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*ACL*-ABBREV* Out"), false);

	linePointer = line;
	while (linePointer != 0)
	{

		switch (linePointer->type)
		{
			case lineConsole:
				device->addTableData(paragraphPointer->table, i18n("Console"));
				break;
			case lineVTY:
				tempString.assign(i18n("*ABBREV*VTY*-ABBREV* "));
				tempString.append(device->intToString(linePointer->lineStart));
				if (linePointer->lineEnd != 0)
				{
					tempString.append(" - ");
					tempString.append(device->intToString(linePointer->lineEnd));
				}
				device->addTableData(paragraphPointer->table, tempString.c_str());
				break;
			case lineAUX:
				device->addTableData(paragraphPointer->table, i18n("Auxillary"));
				break;
			default:
				tempString.assign(i18n("*ABBREV*TTY*-ABBREV* "));
				tempString.append(device->intToString(linePointer->lineStart));
				if (linePointer->lineEnd != 0)
				{
					tempString.append(" - ");
					tempString.append(device->intToString(linePointer->lineEnd));	
				}
				device->addTableData(paragraphPointer->table, tempString.c_str());
				break;
		}
		if (linePointer->execTimeout == 0)
			device->addTableData(paragraphPointer->table, i18n("None"));
		else
		{
			tempString.assign(device->timeToString(linePointer->execTimeout));
			device->addTableData(paragraphPointer->table, tempString.c_str());
		}
		if (linePointer->absoluteTimeout == 0)
			device->addTableData(paragraphPointer->table, i18n("None"));
		else
		{
			tempString.assign(device->timeToString(linePointer->absoluteTimeout));
			device->addTableData(paragraphPointer->table, tempString.c_str());
		}
		if (linePointer->sessionTimeout == 0)
			device->addTableData(paragraphPointer->table, i18n("None"));
		else
		{
			tempString.assign(device->timeToString(linePointer->sessionTimeout));
			device->addTableData(paragraphPointer->table, tempString.c_str());
		}
		if (linePointer->loginTimeout == 0)
			device->addTableData(paragraphPointer->table, i18n("None"));
		else
		{
			tempString.assign(device->timeToString(linePointer->loginTimeout));
			device->addTableData(paragraphPointer->table, tempString.c_str());
		}
		device->addTableData(paragraphPointer->table, linePointer->aclIn.c_str());
		device->addTableData(paragraphPointer->table, linePointer->aclOut.c_str());
		linePointer = linePointer->next;
	}

	return errorCode;
}


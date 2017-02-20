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


int IOSAdministration::generateDeviceTelnetConfig(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	lineConfig *linePointer = line;
	string tempString;
	bool found = false;
	int errorCode = 0;

	if ((linePointer != 0) && (telnetEnabled == true))
	{

		configReportPointer = device->getConfigSection("CONFIG-ADMIN");
		paragraphPointer = device->addParagraph(configReportPointer);
		paragraphPointer->paragraph.assign(i18n("Access to the Telnet service on *DEVICETYPE* devices is configured using lines. Table *TABLEREF* details the Telnet line configuration."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINTELNETLINE-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("Telnet service lines");

		// Headings...
		device->addTableHeading(paragraphPointer->table, i18n("Line"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Exec"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Login"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Level"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Password"), true);
		device->addTableHeading(paragraphPointer->table, i18n("Authorisation"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Accounting"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*ACL*-ABBREV*"), false);

		// Data...
		while (linePointer != 0)
		{
			if ((linePointer->telnet == true) && (linePointer->type == lineVTY) && (linePointer->exec == true) && !((linePointer->password.empty()) && (linePointer->login == loginLinePassword)))
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
							if (linePointer->password.empty())
								found = true;
							break;
						case loginLocal:
							device->addTableData(paragraphPointer->table, i18n("Local Users"));
							break;
						case loginTACACS:
							device->addTableData(paragraphPointer->table, i18n("TACACS Style"));
							break;
						default:
							device->addTableData(paragraphPointer->table, i18n("AAA Authentication"));
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

		if (found == true)
		{
			paragraphPointer = device->addParagraph(configReportPointer);
			paragraphPointer->paragraph.assign(i18n("It is worth noting that if a line password has not been configured and the line is set to authenticate using the password, an error message is displayed and the connection will be terminated."));
		}
	}
	return errorCode;
}


int IOSAdministration::generateDeviceHTTPConfig(Device *device)
{
	// Variables...
	Device::paragraphStruct *paragraphPointer = 0;

	// additional SSH settings...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-ADMINHTTP-TABLE");
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*HTTP*-ABBREV* *ABBREV*ACL*-ABBREV*"));
	if (httpAcl.empty())
		device->addTableData(paragraphPointer->table, "");
	else
		device->addTableData(paragraphPointer->table, httpAcl.c_str());

	return 0;
}


int IOSAdministration::generateDeviceSSHConfig(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	lineConfig *linePointer = line;
	string tempString;
	bool found = false;
	int errorCode = 0;

	if ((linePointer != 0) && (sshEnabled == true))
	{

		// additional SSH settings...
		paragraphPointer = device->getTableParagraphPointer("CONFIG-ADMINSSH-TABLE");
		device->addTableData(paragraphPointer->table, i18n("*ABBREV*SSH*-ABBREV* Authentication Retries"));
		tempString.assign(device->intToString(sshRetries));
		device->addTableData(paragraphPointer->table, tempString.c_str());
		device->addTableData(paragraphPointer->table, i18n("*ABBREV*SSH*-ABBREV* Negotiation Timeout"));
		tempString.assign(device->timeToString(sshNegTimeout));
		device->addTableData(paragraphPointer->table, tempString.c_str());

		configReportPointer = device->getConfigSection("CONFIG-ADMIN");
		paragraphPointer = device->addParagraph(configReportPointer);
		paragraphPointer->paragraph.assign(i18n("Access to the *ABBREV*SSH*-ABBREV* service on *DEVICETYPE* devices is configured using lines. Table *TABLEREF* details the *ABBREV*SSH*-ABBREV* line configuration."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "CONFIG-ADMINSSHLINE-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("*ABBREV*SSH*-ABBREV* service lines");

		// Headings...
		device->addTableHeading(paragraphPointer->table, i18n("Line"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Exec"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Login"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Level"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Password"), true);
		device->addTableHeading(paragraphPointer->table, i18n("Authorisation"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Accounting"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*ACL*-ABBREV*"), false);

		// Data...
		while (linePointer != 0)
		{
			if ((linePointer->ssh == true) && (linePointer->type == lineVTY) && (linePointer->exec == true) && !((linePointer->password.empty()) && (linePointer->login == loginLinePassword)))
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
							if (linePointer->password.empty())
								found = true;
							break;
						case loginLocal:
							device->addTableData(paragraphPointer->table, i18n("Local Users"));
							break;
						case loginTACACS:
							device->addTableData(paragraphPointer->table, i18n("TACACS Style"));
							break;
						default:
							device->addTableData(paragraphPointer->table, i18n("AAA Authentication"));
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

		if (found == true)
		{
			paragraphPointer = device->addParagraph(configReportPointer);
			paragraphPointer->paragraph.assign(i18n("It is worth noting that if a line password has not been configured and the line is set to authenticate using the password, an error message is displayed and the connection will be terminated."));
		}
	}
	return errorCode;
}

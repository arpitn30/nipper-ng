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
#include "../../globaldefs.h"
#include "../device.h"
#include "snmp.h"


SNMP::snmpUserStruct *SNMP::addSNMPUser()							// Add a user
{
	// Variables...
	snmpUserStruct *snmpUserPointer = 0;

	// Create...
	if (snmpUser == 0)
	{
		snmpUser = new (snmpUserStruct);
		snmpUserPointer = snmpUser;
	}
	else
	{
		snmpUserPointer = snmpUser;
		while (snmpUserPointer->next != 0)
			snmpUserPointer = snmpUserPointer->next;
		snmpUserPointer->next = new (snmpUserStruct);
		snmpUserPointer = snmpUserPointer->next;
	}

	// Init...
	snmpUserPointer->version = 3;				// SNMP Version
	snmpUserPointer->snmpv3 = snmpV3NoAuth;		// SNMP version 3 auth type
	snmpUserPointer->auth = snmpV3AuthMD5;		// Auth Crypto
	snmpUserPointer->priv = snmpV3PrivDES;		// Priv Crypto
	snmpUserPointer->port = 162;
	snmpUserPointer->next = 0;

	return snmpUserPointer;
}


SNMP::snmpUserStruct *SNMP::getSNMPUser(const char *username)		// Get a user
{
	// Variables...
	snmpUserStruct *snmpUserPointer = snmpUser;
	bool found = false;

	while ((snmpUserPointer != 0) && (found == false))
	{
		if (snmpUserPointer->user.compare(username) == 0)
			found = true;
		else
			snmpUserPointer = snmpUserPointer->next;
	}

	return snmpUserPointer;
}


int SNMP::generateUserConfigReport(Device *device)			// Generate User Configuration Report
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	snmpGroupStruct *snmpGroupPointer = 0;
	snmpUserStruct *snmpUserPointer = 0;
	string tempString;
	bool found = false;
	bool remoteHost = false;
	bool ipv6 = false;
	int errorCode = 0;

	if (snmpUser != 0)
	{

		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s SNMP Users\n", device->config->COL_BLUE, device->config->COL_RESET);

		// Init...
		configReportPointer = device->getConfigSection("CONFIG-SNMP");

		// Go through groups first...
		snmpGroupPointer = snmpGroup;
		while (snmpGroupPointer != 0)
		{
			// Look for users in this group...
			found = false;
			remoteHost = false;
			ipv6 = false;
			snmpUserPointer = snmpUser;
			while (snmpUserPointer != 0)
			{
				if (snmpUserPointer->group.compare(snmpGroupPointer->group) == 0)
				{
					found = true;
					if ((showUserIPv6Filter == true) && (!snmpUserPointer->ipv6Filter.empty()))
						ipv6 = true;
					if ((showUserRemote == true) && (!snmpUserPointer->host.empty()))
						remoteHost = true;
				}
				snmpUserPointer = snmpUserPointer->next;
			}

			// If found, build the table...
			if (found == true)
			{
				paragraphPointer = device->addParagraph(configReportPointer);

				// Create Table...
				tempString.assign("CONFIG-SNMPUSER-");
				tempString.append(snmpGroupPointer->group);
				tempString.append("-TABLE");
				errorCode = device->addTable(paragraphPointer, tempString.c_str());
				if (errorCode != 0)
					return errorCode;
				tempString.assign(snmpGroupPointer->group);
				tempString.append(i18n(" *ABBREV*SNMP*-ABBREV* group users"));
				paragraphPointer->table->title.assign(tempString);
				device->addTableHeading(paragraphPointer->table, i18n("User"), false);
				if (remoteHost == true)
				{
					device->addTableHeading(paragraphPointer->table, i18n("Host"), false);
					device->addTableHeading(paragraphPointer->table, i18n("Port"), false);
				}
				device->addTableHeading(paragraphPointer->table, i18n("Version"), false);
				device->addTableHeading(paragraphPointer->table, i18n("Security"), false);
				device->addTableHeading(paragraphPointer->table, i18n("Auth"), false);
				device->addTableHeading(paragraphPointer->table, i18n("Auth Password"), true);
				if (showUserPriv == true)
				{
					device->addTableHeading(paragraphPointer->table, i18n("Priv"), false);
					device->addTableHeading(paragraphPointer->table, i18n("Priv Password"), true);
				}
				if (showUserFilter == true)
					device->addTableHeading(paragraphPointer->table, userFilterText, false);
				if (ipv6 == true)
					device->addTableHeading(paragraphPointer->table, userIPv6FilterText, false);

				// Table Data...
				snmpUserPointer = snmpUser;
				while (snmpUserPointer != 0)
				{
					if (snmpUserPointer->group.compare(snmpGroupPointer->group) == 0)
					{
						device->addTableData(paragraphPointer->table, snmpUserPointer->user.c_str());
						if (remoteHost == true)
						{
							if (snmpUserPointer->host.empty())
							{
								device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
								device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
							}
							else
							{
								device->addTableData(paragraphPointer->table, snmpUserPointer->host.c_str());
								tempString.assign(device->intToString(snmpUserPointer->port));
								device->addTableData(paragraphPointer->table, tempString.c_str());
							}
						}
						switch (snmpUserPointer->version)
						{
							case 1:
								device->addTableData(paragraphPointer->table, i18n("1"));
								break;
							case 2:
								device->addTableData(paragraphPointer->table, i18n("2c"));
								break;
							case 3:
								device->addTableData(paragraphPointer->table, i18n("3"));
								break;
							default:
								device->addTableData(paragraphPointer->table, i18n("1 and 2c"));
								break;
						}
						switch (snmpUserPointer->snmpv3)
						{
							case snmpV3Auth:
								device->addTableData(paragraphPointer->table, i18n("Auth"));
								break;
							case snmpV3Priv:
								device->addTableData(paragraphPointer->table, i18n("Auth+Priv"));
								break;
							default:
								device->addTableData(paragraphPointer->table, i18n("No Auth"));
								break;
						}
						if (snmpUserPointer->snmpv3 != snmpV3NoAuth)
						{
							switch (snmpUserPointer->auth)
							{
								case snmpV3AuthSHA:
									device->addTableData(paragraphPointer->table, i18n("*ABBREV*SHA*-ABBREV*"));
									break;
								default:
									device->addTableData(paragraphPointer->table, i18n("*ABBREV*MD5*-ABBREV*"));
									break;
							}
							if (snmpUserPointer->authPassword.empty())
								device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
							else
								device->addTableData(paragraphPointer->table, snmpUserPointer->authPassword.c_str());
						}
						else
						{
							device->addTableData(paragraphPointer->table, i18n("N/A"));
							device->addTableData(paragraphPointer->table, i18n("N/A"));
						}
						if (showUserPriv == true)
						{
							if (snmpUserPointer->snmpv3 == snmpV3Priv)
							{
								switch (snmpUserPointer->priv)
								{
									case snmpV3Priv3DES:
										device->addTableData(paragraphPointer->table, i18n("*ABBREV*3DES*-ABBREV*"));
										break;
									case snmpV3PrivAES128:
										device->addTableData(paragraphPointer->table, i18n("*ABBREV*AES*-ABBREV*-128"));
										break;
									case snmpV3PrivAES192:
										device->addTableData(paragraphPointer->table, i18n("*ABBREV*AES*-ABBREV*-192"));
										break;
									case snmpV3PrivAES256:
										device->addTableData(paragraphPointer->table, i18n("*ABBREV*AES*-ABBREV*-256"));
										break;
									default:
										device->addTableData(paragraphPointer->table, i18n("*ABBREV*DES*-ABBREV*"));
										break;
								}
								if (snmpUserPointer->privPassword.empty())
									device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
								else
									device->addTableData(paragraphPointer->table, snmpUserPointer->privPassword.c_str());
							}
							else
							{
								device->addTableData(paragraphPointer->table, i18n("N/A"));
								device->addTableData(paragraphPointer->table, i18n("N/A"));
							}
						}
						if (showUserFilter == true)
						{
							if (snmpUserPointer->filter.empty())
								device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
							else
								device->addTableData(paragraphPointer->table, snmpUserPointer->filter.c_str());
						}
						if (ipv6 == true)
						{
							if (snmpUserPointer->ipv6Filter.empty())
								device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
							else
								device->addTableData(paragraphPointer->table, snmpUserPointer->ipv6Filter.c_str());
						}
					}
					snmpUserPointer = snmpUserPointer->next;
				}
			}

			snmpGroupPointer = snmpGroupPointer->next;
		}

		// Now do the same for users for which no group exists...
		// Find if there are any users in this catagory...
		found = false;
		remoteHost = false;
		ipv6 = false;
		snmpUserPointer = snmpUser;
		while (snmpUserPointer != 0)
		{
			if (getSNMPGroup(snmpUserPointer->group.c_str()) == 0)
			{
				found = true;
				if ((showUserIPv6Filter == true) && (!snmpUserPointer->ipv6Filter.empty()))
					ipv6 = true;
				if ((showUserRemote == true) && (!snmpUserPointer->host.empty()))
					remoteHost = true;
			}
			snmpUserPointer = snmpUserPointer->next;
		}

		// If there are some users without a valid group...
		if (found == true)
		{
			paragraphPointer = device->addParagraph(configReportPointer);

			// Create Table...
			errorCode = device->addTable(paragraphPointer, "CONFIG-SNMPUSERS-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title.assign(i18n("*ABBREV*SNMP*-ABBREV* users"));
			device->addTableHeading(paragraphPointer->table, i18n("User"), false);
			if (remoteHost == true)
			{
				device->addTableHeading(paragraphPointer->table, i18n("Host"), false);
				device->addTableHeading(paragraphPointer->table, i18n("Port"), false);
			}
			device->addTableHeading(paragraphPointer->table, i18n("Version"), false);
			device->addTableHeading(paragraphPointer->table, i18n("Security"), false);
			device->addTableHeading(paragraphPointer->table, i18n("Auth"), false);
			device->addTableHeading(paragraphPointer->table, i18n("Auth Password"), true);
			if (showUserPriv == true)
			{
				device->addTableHeading(paragraphPointer->table, i18n("Priv"), false);
				device->addTableHeading(paragraphPointer->table, i18n("Priv Password"), true);
			}
			if (showUserFilter == true)
				device->addTableHeading(paragraphPointer->table, userFilterText, false);
			if (ipv6 == true)
				device->addTableHeading(paragraphPointer->table, userIPv6FilterText, false);

			// Table Data...
			snmpUserPointer = snmpUser;
			while (snmpUserPointer != 0)
			{
				if (getSNMPGroup(snmpUserPointer->group.c_str()) == 0)
				{
					device->addTableData(paragraphPointer->table, snmpUserPointer->user.c_str());
					if (remoteHost == true)
					{
						if (snmpUserPointer->host.empty())
						{
							device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
							device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
						}
						else
						{
							device->addTableData(paragraphPointer->table, snmpUserPointer->host.c_str());
							tempString.assign(device->intToString(snmpUserPointer->port));
							device->addTableData(paragraphPointer->table, tempString.c_str());
						}
					}
					switch (snmpUserPointer->version)
					{
						case 1:
							device->addTableData(paragraphPointer->table, i18n("1"));
							break;
						case 2:
							device->addTableData(paragraphPointer->table, i18n("2c"));
							break;
						case 3:
							device->addTableData(paragraphPointer->table, i18n("3"));
							break;
						default:
							device->addTableData(paragraphPointer->table, i18n("1 and 2c"));
							break;
					}
					switch (snmpUserPointer->snmpv3)
					{
						case snmpV3Auth:
							device->addTableData(paragraphPointer->table, i18n("Auth"));
							break;
						case snmpV3Priv:
							device->addTableData(paragraphPointer->table, i18n("Auth+Priv"));
							break;
						default:
							device->addTableData(paragraphPointer->table, i18n("No Auth"));
							break;
					}
					if (snmpUserPointer->snmpv3 != snmpV3NoAuth)
					{
						switch (snmpUserPointer->auth)
						{
							case snmpV3AuthSHA:
								device->addTableData(paragraphPointer->table, i18n("*ABBREV*SHA*-ABBREV*"));
								break;
							default:
								device->addTableData(paragraphPointer->table, i18n("*ABBREV*MD5*-ABBREV*"));
								break;
						}
						if (snmpUserPointer->authPassword.empty())
							device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
						else
							device->addTableData(paragraphPointer->table, snmpUserPointer->authPassword.c_str());
					}
					else
					{
						device->addTableData(paragraphPointer->table, i18n("N/A"));
						device->addTableData(paragraphPointer->table, i18n("N/A"));
					}
					if (showUserPriv == true)
					{
						if (snmpUserPointer->snmpv3 == snmpV3Priv)
						{
							switch (snmpUserPointer->priv)
							{
								case snmpV3Priv3DES:
									device->addTableData(paragraphPointer->table, i18n("*ABBREV*3DES*-ABBREV*"));
									break;
								case snmpV3PrivAES128:
									device->addTableData(paragraphPointer->table, i18n("*ABBREV*AES*-ABBREV*-128"));
									break;
								case snmpV3PrivAES192:
									device->addTableData(paragraphPointer->table, i18n("*ABBREV*AES*-ABBREV*-192"));
									break;
								case snmpV3PrivAES256:
									device->addTableData(paragraphPointer->table, i18n("*ABBREV*AES*-ABBREV*-256"));
									break;
								default:
									device->addTableData(paragraphPointer->table, i18n("*ABBREV*DES*-ABBREV*"));
									break;
							}
							if (snmpUserPointer->privPassword.empty())
								device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
							else
								device->addTableData(paragraphPointer->table, snmpUserPointer->privPassword.c_str());
						}
						else
						{
							device->addTableData(paragraphPointer->table, i18n("N/A"));
							device->addTableData(paragraphPointer->table, i18n("N/A"));
						}
					}
					if (showUserFilter == true)
					{
						if (snmpUserPointer->filter.empty())
							device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
						else
							device->addTableData(paragraphPointer->table, snmpUserPointer->filter.c_str());
					}
					if (ipv6 == true)
					{
						if (snmpUserPointer->ipv6Filter.empty())
							device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
						else
							device->addTableData(paragraphPointer->table, snmpUserPointer->ipv6Filter.c_str());
					}
				}
				snmpUserPointer = snmpUserPointer->next;
			}
		}
	}

	return errorCode;
}



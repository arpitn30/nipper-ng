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

// Includes...
#include "../../globaldefs.h"
#include "authentication.h"
#include "../device.h"


int Authentication::generateConfigReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	int errorCode = 0;

	if ((localUser != 0) || (radiusServer != 0) || (tacacsServer != 0) || (kerberosServer != 0) || (securidServer != 0) || (ldapServer != 0) || (ntServer != 0))
	{

		if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s Authentication Settings\n", device->config->COL_BLUE, device->config->COL_RESET);

		// Create Config Report Section...
		configReportPointer = device->getConfigSection("CONFIG-AUTH");
		configReportPointer->title = i18n("Authentication Settings");
		paragraphPointer = device->addParagraph(configReportPointer);
		paragraphPointer->paragraph.assign(authenticationConfigIntro);

		// Output General?
		if ((loginAttemptsSupported == true) || (authMethods != 0) || ((authMethodSupported == true)))
			errorCode = generateConfigGeneralReport(device);

		// Output users?
		if (localUser != 0)
			errorCode = generateConfigLocalUserReport(device);

		// Output TACACS+?
		if (tacacsServer != 0)
			errorCode = generateConfigTacacsReport(device);

		// Output radius?
		if (radiusServer != 0)
			errorCode = generateConfigRadiusReport(device);

		// Output kerberos?
		if (kerberosServer != 0)
			errorCode = generateConfigKerberosReport(device);

		// Output SecurID?
		if (securidServer != 0)
			errorCode = generateConfigSecurIDReport(device);

		// Output LDAP?
		if (ldapServer != 0)
			errorCode = generateConfigLDAPReport(device);

		// Output NT?
		if (ntServer != 0)
			errorCode = generateConfigNTReport(device);
	}

	return errorCode;
}


int Authentication::generateSecurityReport(Device *device)
{
	// Variables...
	localUserConfig *localUserPointer = 0;
	tacacsServerConfig *tacacsPointer = 0;
	radiusServerConfig *radiusPointer = 0;
	ldapServerConfig *ldapPointer = 0;

	// Performing checks...
	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s Authentication Checks\n", device->config->COL_BLUE, device->config->COL_RESET);

	// Local users...
	localUserPointer = localUser;
	while (localUserPointer != 0)
	{
		if ((localUserPointer->encryption == clearText) || (localUserPointer->encryption == cisco7Encryption))
		{
			if (localUserPointer->password.empty())
				emptyUserPassword++;
			else if (device->isDictionaryPassword(localUserPointer->password.c_str()))
			{
				localUserPointer->dictionaryPassword = true;
				dictionaryUserPassword++;
			}
			else
			{
				localUserPointer->weakPassword = device->isPasswordWeak(localUserPointer->password.c_str(), localUserPointer->username.c_str());
				if (localUserPointer->weakPassword != Device::passwordPassed)
					weakUserPassword++;
			}
		}
		localUserPointer = localUserPointer->next;
	}

	// TACACS+
	tacacsPointer = tacacsServer;
	while (tacacsPointer != 0)
	{
		if ((tacacsPointer->encryption == clearText) || (tacacsPointer->encryption == cisco7Encryption))
		{
			if (tacacsPointer->key.empty())
			{
				noTacacsKey++;
			}
			else if (device->isDictionaryPassword(tacacsPointer->key.c_str()))
			{
				tacacsPointer->dictionaryKey = true;
				dictionaryTacacsKey++;
			}
			else
			{
				tacacsPointer->weakKey = device->isPasswordWeak(tacacsPointer->key.c_str(), "tacacs");
				if (tacacsPointer->weakKey != Device::passwordPassed)
					weakTacacsKey++;
			}
		}
		tacacsPointer = tacacsPointer->next;
	}

	// RADIUS
	radiusPointer = radiusServer;
	while (radiusPointer != 0)
	{
		if ((radiusPointer->encryption == clearText) || (radiusPointer->encryption == cisco7Encryption))
		{
			if (radiusPointer->key.empty())
				noRadiusKey++;
			else if (device->isDictionaryPassword(radiusPointer->key.c_str()))
			{
				radiusPointer->dictionaryKey = true;
				dictionaryTacacsKey++;
			}
			else
			{
				radiusPointer->weakKey = device->isPasswordWeak(radiusPointer->key.c_str(), "radius");
				if (radiusPointer->weakKey != Device::passwordPassed)
					weakRadiusKey++;
			}
		}
		radiusPointer = radiusPointer->next;
	}

	// LDAP
	if (showLDAPPassword == true)
	{
		ldapPointer = ldapServer;
		while (ldapPointer != 0)
		{
			if (((ldapPointer->encryption == clearText) || (ldapPointer->encryption == cisco7Encryption)) && (!ldapPointer->password.empty()))
			{
				if (device->isDictionaryPassword(ldapPointer->password.c_str()))
				{
					ldapPointer->dictionaryPassword = true;
					dictionaryLDAPPassword++;
				}
				else
				{
					ldapPointer->weakPassword = device->isPasswordWeak(ldapPointer->password.c_str(), ldapPointer->cn.c_str());
					if (ldapPointer->weakPassword != Device::passwordPassed)
						weakLDAPPassword++;
				}
			}
			ldapPointer = ldapPointer->next;
		}
	}

	generateUserSecurityReport(device, emptyUserPassword, dictionaryUserPassword, weakUserPassword);
	generateTacacsSecurityReport(device, noTacacsKey, dictionaryTacacsKey, weakTacacsKey);
	generateRadiusSecurityReport(device, noRadiusKey, dictionaryRadiusKey, weakRadiusKey);
	generateLDAPSecurityReport(device, dictionaryLDAPPassword, weakLDAPPassword);

	return 0;
}


Authentication::authConfig *Authentication::addMethod()
{
	// Variables...
	authConfig *authPointer = 0;

	// Create...
	if (authMethods == 0)
	{
		authMethods = new (authConfig);
		authPointer = authMethods;
	}
	else
	{
		authPointer = authMethods;
		while (authPointer->next != 0)
			authPointer = authPointer->next;
		authPointer->next = new (authConfig);
		authPointer = authPointer->next;
	}

	// Init...
	authPointer->method = localAuth;					// Authentication method (local, tacacs+...)
	authPointer->next = 0;

	return authPointer;
}


int Authentication::generateConfigGeneralReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	authConfig *authPointer = 0;
	string tempString;
	int errorCode = 0;

	configReportPointer = device->getConfigSection("CONFIG-AUTH");
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraphTitle.assign(i18n("General"));
	paragraphPointer->paragraph.assign(i18n("This section details the general authentication configuration settings on *DEVICENAME*."));

	// General Table...
	if (loginAttemptsSupported == true)
	{
		paragraphPointer = device->addParagraph(configReportPointer);

		// General Table...
		errorCode = device->addTable(paragraphPointer, "CONFIG-AUTHGENERAL-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("General authentication settings");
		device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Setting"), true);

		device->addTableData(paragraphPointer->table, i18n("Login Attempts"));
		tempString.assign(device->intToString(loginAttempts));
		device->addTableData(paragraphPointer->table, tempString.c_str());
	}

	// Authentication Methods...
	if ((authMethods != 0) && (authMethodSupported == true))
	{
		paragraphPointer = device->addParagraph(configReportPointer);

		// Authentication Methods Table...
		errorCode = device->addTable(paragraphPointer, "CONFIG-AUTHMETHODS-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("Authentication Methods");
		if (namedAuthSupport == true)
			device->addTableHeading(paragraphPointer->table, i18n("Name"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Type"), false);
		if (showAuthLevel == true)
			device->addTableHeading(paragraphPointer->table, i18n("Access"), false);
		if (appliesToSupported == true)
			device->addTableHeading(paragraphPointer->table, i18n("For"), false);

		authPointer = authMethods;
		while (authPointer != 0)
		{
			if (namedAuthSupport == true)
				device->addTableData(paragraphPointer->table, authPointer->name.c_str());
			switch (authPointer->method)
			{
				case localAuth:
					device->addTableData(paragraphPointer->table, i18n("Local Users Database"));
					break;
				case radiusAuth:
					device->addTableData(paragraphPointer->table, i18n("*ABBREV*RADIUS*-ABBREV* Server"));
					break;
				case tacacsAuth:
					device->addTableData(paragraphPointer->table, i18n("*ABBREV*TACACS+*-ABBREV* Server"));
					break;
				case ldapAuth:
					device->addTableData(paragraphPointer->table, i18n("*ABBREV*LDAP*-ABBREV* Server"));
					break;
				case securidAuth:
					device->addTableData(paragraphPointer->table, i18n("*ABBREV*RSA*-ABBREV* SecurID Server"));
					break;
				case kerberosAuth:
					device->addTableData(paragraphPointer->table, i18n("Kerberos Server"));
					break;
				case ntAuth:
					device->addTableData(paragraphPointer->table, i18n("*ABBREV*NT*-ABBREV* Server"));
					break;
				case noAuthRequired:
					device->addTableData(paragraphPointer->table, i18n("No Authentication"));
					break;
				case lineAuth:
					device->addTableData(paragraphPointer->table, i18n("Line Password"));
					break;
				case enableAuth:
					device->addTableData(paragraphPointer->table, i18n("Enable Password"));
					break;
				case serverGroupAuth:
					device->addTableData(paragraphPointer->table, i18n("Auth Server Group"));
					break;
			}
			if (showAuthLevel == true)
				device->addTableData(paragraphPointer->table, authPointer->level.c_str());
			if (appliesToSupported == true)
				device->addTableData(paragraphPointer->table, authPointer->appliesTo.c_str());
			authPointer = authPointer->next;
		}
	}

	return errorCode;
}

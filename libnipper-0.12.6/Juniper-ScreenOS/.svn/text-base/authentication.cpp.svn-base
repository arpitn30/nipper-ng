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
#include <cstring>
#include <cstdlib>

#include "../globaldefs.h"
#include "device.h"
#include "authentication.h"
#include "../device/common/configline.h"


ScreenOSAuthentication::ScreenOSAuthentication()
{
	// General...
	authenticationConfigIntro = i18n("*DEVICETYPE* devices support local and remote authentication services. This section details the configuration of the authentication settings.");		// Introduction text to the whole section
	loginAttemptsSupported = true;						// Login attempts supported
	loginAttempts = 3;									// Login attempts allowed (0 =  infinite)
	configAccessAuthentication = i18n("The following commands can be used on *DEVICETYPE* devices to configure the administrator accounts password and an administrative user accounts password:*CODE**COMMAND*set admin password *CMDUSER*password*-CMDUSER**-COMMAND**COMMAND*set admin user *CMDUSER*username*-CMDUSER* password *CMDUSER*password*-CMDUSER**-COMMAND**-CODE*");

	// Authentication Methods...
	authMethodSupported = true;							// Authentication Method Supported
	appliesToSupported = true;							// Applies To Supported
	namedAuthSupport = true;							// Are auth servers named?

	// Local User Options...
	encryptionSupported = true;							// Show encryption
	readOnlySupported = false;							// Is read only supported?
	outboundACLSupported = false;						// Are outbound filtering ACL supported?
	privilegeLevelSupported = true;						// Are privilege levels supported?
	privilegeLevelText = i18n("Access");				// The table title privilege level text
	configDeviceSpecificLocalUsers = i18n("The administrative users on *DEVICETYPE* devices can be granted read/write (all) or read only access to the device. The primary device administrator has full read write access to the device configuration.");			// Text for the config report local user section.
	filterText = i18n("Policy");						// The table filter column title text

	// TACACS Options...
	showTacacsGroupName = true;							// Show the TACACS group 
	showTacacsRetries = true;							// Show the TACACS retries
	configTacacsKey = i18n("The *ABBREV*TACACS+*-ABBREV* server shared secret can be configured using the following command:*CODE**COMMAND*set auth-server *CMDUSER*label*-CMDUSER* tacacs secret *CMDUSER*key*-CMDUSER**-COMMAND**-CODE*");							// The text and commands to configure a TACACS+ key

	// RADIUS Options...
	showRadiusGroupName = true;							// Show the RADIUS group
	configRadiusKey = i18n("The *ABBREV*RADIUS*-ABBREV* server shared secret can be configured using the following command:*CODE**COMMAND*set auth-server *CMDUSER*label*-CMDUSER* radius secret *CMDUSER*key*-CMDUSER**-COMMAND**-CODE*");

	// LDAP Options...
	showLDAPGroupName = true;							// Show the LDAP group

	// SecurID Options...
	showSecurIDGroupName = true;						// Show the SecurID group
	showSecurIDDuress = true;							// Show the SecurID Duress
	showSecurIDEncryption = true;						// Show the SecurID Encryption


	// Internal...
	retries = 3;
	timeout = 3;
	port = 0;
}


int ScreenOSAuthentication::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	localUserConfig *localUserPointer = 0;
	radiusServerConfig *radiusPointer = 0;
	tacacsServerConfig *tacacsPointer = 0;
	ldapServerConfig *ldapPointer = 0;
	securidServerConfig *securidPointer = 0;
	authConfig *authPointer = 0;
	string tempString;
	bool setting = false;
	int errorCode = 0;

	// Init
	if (strcasecmp(command->part(0), "unset") == 0)
		setting = false;
	else
		setting = true;

	// Admin name...
	if (strcmp(command->part(2), "name") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sAdministrator Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		localUserPointer = getUser(command->part(3));
		localUserPointer->privilegeLevel.assign(i18n("Primary Admin"));
	}

	// Admin password...
	else if (strcmp(command->part(2), "password") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sAdministrator Password Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		// Will be the first user...
		if (localUser != 0)
		{
			localUserPointer = localUser;
			localUserPointer->adminAccess = true;
			localUserPointer->password.assign(device->isEncryptedDictionaryPassword(command->part(3)));
			if (localUserPointer->password.empty())
			{
				localUserPointer->encryption = netscreenEncryption;
				localUserPointer->password.assign(command->part(3));
				device->addJohnPassword(localUserPointer->username.c_str(), localUserPointer->password.c_str());
			}
			else
				localUserPointer->encryption = clearText;
		}
	}

	// Users...
	else if ((strcmp(command->part(2), "user") == 0) && (strcmp(command->part(4), "password") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sUser Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		localUserPointer = getUser(command->part(3));
		localUserPointer->password.assign(device->isEncryptedDictionaryPassword(command->part(5)));
		if (localUserPointer->password.empty())
		{
			localUserPointer->encryption = netscreenEncryption;
			localUserPointer->password.assign(command->part(5));
			device->addJohnPassword(localUserPointer->username.c_str(), localUserPointer->password.c_str());
		}
		else
			localUserPointer->encryption = clearText;

		if (strcmp(command->part(6), "privilege") == 0)
		{
			localUserPointer->privilegeLevel.assign(command->part(7));
			if (strcasecmp(command->part(7), "all") == 0)
				localUserPointer->adminAccess = true;
		}
		else
			localUserPointer->privilegeLevel.assign("read-only");
	}

	// Access Attempts...
	else if ((strcmp(command->part(2), "access") == 0) && (strcmp(command->part(3), "attempts") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sAccess Attempts Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		loginAttempts = atoi(command->part(4));	
	}

	// Auth Server...
	else if (strcmp(command->part(1), "auth-server") == 0)
	{

		// Server name...
		if (strcmp(command->part(3), "server-name") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sServer Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			serverName.assign(command->part(2));
			address.assign(command->part(4));
		}

		// Backup 1...
		else if (strcmp(command->part(3), "backup1") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sBackup1 Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			serverName.assign(command->part(2));
			backup1.assign(command->part(4));
		}

		// Backup 2...
		else if (strcmp(command->part(3), "backup2") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sBackup2 Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			serverName.assign(command->part(2));
			backup2.assign(command->part(4));
		}

		// Port...
		else if ((strcmp(command->part(4), "port") == 0) || (strcmp(command->part(4), "auth-port") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sPort Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			port = atoi(command->part(5));
		}

		// SecurID Encryption...
		else if (strcmp(command->part(4), "encr") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sSecurID Encryption Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			serverName.assign(command->part(2));
			if (strcmp(command->part(5), "0") == 0)
				cn.assign(i18n("*ABBREV*SDI*-ABBREV*"));
			else
				cn.assign(i18n("*ABBREV*DES*-ABBREV*"));
		}

		// LDAP CN...
		else if ((strcmp(command->part(3), "ldap") == 0) && (strcmp(command->part(4), "cn") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sLDAP CN Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			serverName.assign(command->part(2));
			cn.assign(command->part(5));
		}

		// SecurID Duress...
		else if ((strcmp(command->part(3), "securid") == 0) && (strcmp(command->part(4), "duress") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sSecurID Duress Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			securidPointer = addSecurIDServer();
			securidPointer->groupName.assign(serverName);						// If a name is used to group servers...
			securidPointer->description.assign(i18n("Primary"));					// Primary / Backup...
			securidPointer->address.assign(address);								// The address
			securidPointer->encryption.assign(cn);
			if (strcmp(command->part(5), "0") == 0)
				securidPointer->duress.assign(i18n("Off"));
			else
				securidPointer->duress.assign(i18n("On"));
			securidPointer->timeout = timeout;									// Timeout
			securidPointer->retries = retries;
			if (port != 0)
				securidPointer->port = port;
			else
				securidPointer->port = 5500;

			if (!backup1.empty())
			{
				securidPointer = addSecurIDServer();
				securidPointer->groupName.assign(serverName);						// If a name is used to group servers...
				securidPointer->description.assign(i18n("Backup 1"));					// Primary / Backup...
				securidPointer->address.assign(address);								// The address
				securidPointer->encryption.assign(cn);
				if (strcmp(command->part(5), "0") == 0)
					securidPointer->duress.assign(i18n("Off"));
				else
					securidPointer->duress.assign(i18n("On"));
				securidPointer->timeout = timeout;									// Timeout
				securidPointer->retries = retries;
				if (port != 0)
					securidPointer->port = port;
				else
					securidPointer->port = 5500;
			}

			if (!backup2.empty())
			{
				securidPointer = addSecurIDServer();
				securidPointer->groupName.assign(serverName);						// If a name is used to group servers...
				securidPointer->description.assign(i18n("Backup 2"));					// Primary / Backup...
				securidPointer->address.assign(address);								// The address
				securidPointer->encryption.assign(cn);
				if (strcmp(command->part(5), "0") == 0)
					securidPointer->duress.assign(i18n("Off"));
				else
					securidPointer->duress.assign(i18n("On"));
				securidPointer->timeout = timeout;									// Timeout
				securidPointer->retries = retries;
				if (port != 0)
					securidPointer->port = port;
				else
					securidPointer->port = 5500;
			}

			serverName.assign("");
			address.assign("");
			backup1.assign("");
			backup2.assign("");
			cn.assign("");
			retries = 0;
			timeout = 0;
			port = 0;
		}

		// LDAP...
		else if ((strcmp(command->part(3), "ldap") == 0) && (strcmp(command->part(4), "dn") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sLDAP DN Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			ldapPointer = addLDAPServer();
			ldapPointer->groupName.assign(serverName);						// If a name is used to group servers...
			ldapPointer->description.assign(i18n("Primary"));					// Primary / Backup...
			ldapPointer->address.assign(address);								// The address
			ldapPointer->cn.assign(cn);
			ldapPointer->dn.assign(command->part(5));
			ldapPointer->timeout = timeout;									// Timeout
			ldapPointer->retries = retries;
			if (port != 0)
				ldapPointer->port = port;
			else
				ldapPointer->port = 389;

			if (!backup1.empty())
			{
				ldapPointer = addLDAPServer();
				ldapPointer->groupName.assign(serverName);						// If a name is used to group servers...
				ldapPointer->description.assign(i18n("Backup 1"));					// Primary / Backup...
				ldapPointer->address.assign(address);								// The address
				ldapPointer->cn.assign(cn);
				ldapPointer->dn.assign(command->part(5));
				ldapPointer->timeout = timeout;									// Timeout
				ldapPointer->retries = retries;
				if (port != 0)
					ldapPointer->port = port;
				else
					ldapPointer->port = 389;
			}

			if (!backup2.empty())
			{
				ldapPointer = addLDAPServer();
				ldapPointer->groupName.assign(serverName);						// If a name is used to group servers...
				ldapPointer->description.assign(i18n("Backup 2"));					// Primary / Backup...
				ldapPointer->address.assign(address);								// The address
				ldapPointer->cn.assign(cn);
				ldapPointer->dn.assign(command->part(5));
				ldapPointer->timeout = timeout;									// Timeout
				ldapPointer->retries = retries;
				if (port != 0)
					ldapPointer->port = port;
				else
					ldapPointer->port = 389;
			}

			serverName.assign("");
			address.assign("");
			backup1.assign("");
			backup2.assign("");
			cn.assign("");
			retries = 0;
			timeout = 0;
			port = 0;
		}

		// TACACS+ Secret...
		else if ((strcmp(command->part(3), "tacacs") == 0) && (strcmp(command->part(4), "secret") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sTACACS+ Secret Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			tacacsPointer = addTacacsServer();
			tacacsPointer->encryption = netscreenEncryption;
			tacacsPointer->groupName.assign(serverName);						// If a name is used to group servers...
			tacacsPointer->description.assign(i18n("Primary"));					// Primary / Backup...
			tacacsPointer->address.assign(address);								// The address
			tacacsPointer->key.assign(command->part(5));						// Shared secret
			tacacsPointer->timeout = timeout;									// Timeout
			tacacsPointer->retries = retries;
			if (port != 0)
				tacacsPointer->port = port;
			else
				tacacsPointer->port = 49;
			device->addJohnPassword("tacacs+", tacacsPointer->key.c_str());

			if (!backup1.empty())
			{
				tacacsPointer = addTacacsServer();
				tacacsPointer->encryption = netscreenEncryption;
				tacacsPointer->groupName.assign(serverName);						// If a name is used to group servers...
				tacacsPointer->description.assign(i18n("Backup 1"));					// Primary / Backup...
				tacacsPointer->address.assign(backup1);								// The address
				tacacsPointer->key.assign(command->part(5));						// Shared secret
				tacacsPointer->timeout = timeout;									// Timeout
				tacacsPointer->retries = retries;
				if (port != 0)
					tacacsPointer->port = port;
				else
					tacacsPointer->port = 49;
			}

			if (!backup2.empty())
			{
				tacacsPointer = addTacacsServer();
				tacacsPointer->encryption = netscreenEncryption;
				tacacsPointer->groupName.assign(serverName);						// If a name is used to group servers...
				tacacsPointer->description.assign(i18n("Backup 2"));					// Primary / Backup...
				tacacsPointer->address.assign(backup2);								// The address
				tacacsPointer->key.assign(command->part(5));						// Shared secret
				tacacsPointer->timeout = timeout;									// Timeout
				tacacsPointer->retries = retries;
				if (port != 0)
					tacacsPointer->port = port;
				else
					tacacsPointer->port = 49;
			}

			serverName.assign("");
			address.assign("");
			backup1.assign("");
			backup2.assign("");
			retries = 0;
			timeout = 0;
			port = 0;
		}

		// RADIUS Secret...
		else if ((strcmp(command->part(3), "radius") == 0) && (strcmp(command->part(4), "secret") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sRADIUS Secret Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			radiusPointer = addRadiusServer();
			radiusPointer->encryption = netscreenEncryption;
			radiusPointer->groupName.assign(serverName);						// If a name is used to group servers...
			radiusPointer->description.assign(i18n("Primary"));					// Primary / Backup...
			radiusPointer->address.assign(address);								// The address
			radiusPointer->key.assign(command->part(5));						// Shared secret
			radiusPointer->timeout = timeout;									// Timeout
			radiusPointer->retries = retries;
			if (port != 0)
				radiusPointer->port = port;
			else
				radiusPointer->port = 1645;
			device->addJohnPassword("radius", radiusPointer->key.c_str());

			if (!backup1.empty())
			{
				radiusPointer = addRadiusServer();
				radiusPointer->encryption = netscreenEncryption;
				radiusPointer->groupName.assign(serverName);						// If a name is used to group servers...
				radiusPointer->description.assign(i18n("Backup 1"));					// Primary / Backup...
				radiusPointer->address.assign(backup1);								// The address
				radiusPointer->key.assign(command->part(5));						// Shared secret
				radiusPointer->timeout = timeout;									// Timeout
				radiusPointer->retries = retries;
				if (port != 0)
					radiusPointer->port = port;
				else
					radiusPointer->port = 1645;
			}

			if (!backup2.empty())
			{
				radiusPointer = addRadiusServer();
				radiusPointer->encryption = netscreenEncryption;
				radiusPointer->groupName.assign(serverName);						// If a name is used to group servers...
				radiusPointer->description.assign(i18n("Backup 2"));					// Primary / Backup...
				radiusPointer->address.assign(backup2);								// The address
				radiusPointer->key.assign(command->part(5));						// Shared secret
				radiusPointer->timeout = timeout;									// Timeout
				radiusPointer->retries = retries;
				if (port != 0)
					radiusPointer->port = port;
				else
					radiusPointer->port = 1645;
			}

			serverName.assign("");
			address.assign("");
			backup1.assign("");
			backup2.assign("");
			retries = 0;
			timeout = 0;
			port = 0;
		}

		// NOT PROCESSED...
		else
			device->lineNotProcessed(line);
	}

	// Auth Default Server...
	else if ((strcmp(command->part(1), "auth") == 0) && (strcmp(command->part(2), "default") == 0) && (strcmp(command->part(3), "auth") == 0) && (strcmp(command->part(4), "server") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sDefault Auth Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		authPointer = addMethod();
		authPointer->name.assign(command->part(5));
		authPointer->appliesTo.assign(i18n("Default"));

		if (strcasecmp(command->part(5), "Local") == 0)
			authPointer->method = localAuth;
		radiusPointer = radiusServer;
		while (radiusPointer != 0)
		{
			if (strcmp(command->part(5), radiusPointer->groupName.c_str()) == 0)
				authPointer->method = radiusAuth;
			radiusPointer = radiusPointer->next;
		}
		tacacsPointer = tacacsServer;
		while (tacacsPointer != 0)
		{
			if (strcmp(command->part(5), tacacsPointer->groupName.c_str()) == 0)
				authPointer->method = tacacsAuth;
			tacacsPointer = tacacsPointer->next;
		}
		securidPointer = securidServer;
		while (securidPointer != 0)
		{
			if (strcmp(command->part(5), securidPointer->groupName.c_str()) == 0)
				authPointer->method = securidAuth;
			securidPointer = securidPointer->next;
		}
		ldapPointer = ldapServer;
		while (ldapPointer != 0)
		{
			if (strcmp(command->part(5), ldapPointer->groupName.c_str()) == 0)
				authPointer->method = ldapAuth;
			ldapPointer = ldapPointer->next;
		}
	}

	// Auth Admin Server...
	else if ((strcmp(command->part(1), "admin") == 0) && (strcmp(command->part(2), "auth") == 0) && (strcmp(command->part(3), "server") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sAdmin Auth Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		authPointer = addMethod();
		authPointer->name.assign(command->part(4));
		authPointer->appliesTo.assign(i18n("Administration"));

		if (strcasecmp(command->part(4), "Local") == 0)
			authPointer->method = localAuth;
		radiusPointer = radiusServer;
		while (radiusPointer != 0)
		{
			if (strcmp(command->part(4), radiusPointer->groupName.c_str()) == 0)
				authPointer->method = radiusAuth;
			radiusPointer = radiusPointer->next;
		}
		tacacsPointer = tacacsServer;
		while (tacacsPointer != 0)
		{
			if (strcmp(command->part(4), tacacsPointer->groupName.c_str()) == 0)
				authPointer->method = tacacsAuth;
			tacacsPointer = tacacsPointer->next;
		}
		ldapPointer = ldapServer;
		while (ldapPointer != 0)
		{
			if (strcmp(command->part(4), ldapPointer->groupName.c_str()) == 0)
				authPointer->method = ldapAuth;
			ldapPointer = ldapPointer->next;
		}
		securidPointer = securidServer;
		while (securidPointer != 0)
		{
			if (strcmp(command->part(4), securidPointer->groupName.c_str()) == 0)
				authPointer->method = securidAuth;
			securidPointer = securidPointer->next;
		}
	}

	// NOT PROCESSED...
	else
		device->lineNotProcessed(line);

	return errorCode;
}


int ScreenOSAuthentication::processDefaults(Device *device)
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
		while ((authPointer->next != 0) && (authPointer->method != localAuth))
			authPointer = authPointer->next;
		if (authPointer->method != localAuth)
		{
			authPointer->next = new (authConfig);
			authPointer = authPointer->next;
		}
		else
			authPointer = 0;
	}

	if (authPointer != 0)
	{
		authPointer->name.assign(i18n("Local"));
		authPointer->method = localAuth;					// Authentication method (local, tacacs+...)
		authPointer->appliesTo.assign(i18n("Default"));
		authPointer->next = 0;
	}

	return 0;
}

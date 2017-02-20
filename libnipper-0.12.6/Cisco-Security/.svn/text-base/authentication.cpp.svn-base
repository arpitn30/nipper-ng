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


CiscoSecAuthentication::CiscoSecAuthentication()
{
	// General...
	authenticationConfigIntro = i18n("This section describes the various *DEVICETYPE* device authentication settings.");		// Introduction text to the whole section
	loginAttemptsSupported = false;						// Login attempts supported
	loginAttempts = 0;									// Login attempts allowed (0 =  infinite)
	accessWithoutAuthentication = true;					// Set to true if access is allowed without authentication
	configAccessAuthentication = i18n("The following commands can be used on *DEVICETYPE* devices to configure the initial password, enable password and a user account with a password:*CODE**COMMAND*password *CMDUSER*password*-CMDUSER**-COMMAND**COMMAND*enable password *CMDUSER*password*-CMDUSER**-COMMAND**COMMAND*username *CMDUSER*name*-CMDUSER* password *CMDUSER*password*-CMDUSER**-COMMAND**-CODE*");					// The text and commands to configure access authentication with a password

	// Authentication Methods...
	authMethodSupported = true;							// Authentication Method Supported
	appliesToSupported = true;							// Applies To Supported
	namedAuthSupport = true;							// Are auth servers named?

	// Local User Options...
	encryptionSupported = true;							// Show encryption
	readOnlySupported = false;							// Is read only supported?
	outboundACLSupported = false;						// Are outbound filtering ACL supported?
	privilegeLevelSupported = true;						// Are privilege levels supported?
	privilegeLevelText = i18n("Privilege Level");		// The table title privilege level text
	configDeviceSpecificLocalUsers = i18n("");			// Text for the config report local user section.
	filterText = i18n("*ABBREV*ACL*-ABBREV*");			// The table filter column title text

	// TACACS Options...
	showTacacsGroupName = true;							// Show the TACACS group 
	showTacacsRetries = true;							// Show the TACACS retries
	configTacacsKey = i18n("The *ABBREV*TACACS+*-ABBREV* server key can be configured with the following command:*CODE**COMMAND*aaa-server *CMDUSER*server-tag*-CMDUSER* *CMDOPTION**CMDUSER*interface*-CMDUSER**-CMDOPTION* host *CMDUSER*address*-CMDUSER* *CMDUSER*key*-CMDUSER**-COMMAND**-CODE*");							// The text and commands to configure a TACACS+ key

	// RADIUS Options...
	showRadiusGroupName = true;							// Show the RADIUS group
	configRadiusKey = i18n("The *ABBREV*TACACS+*-ABBREV* server key can be configured with the following command:*CODE**COMMAND*aaa-server *CMDUSER*server-tag*-CMDUSER* *CMDOPTION**CMDUSER*interface*-CMDUSER**-CMDOPTION* host *CMDUSER*address*-CMDUSER* *CMDUSER*key*-CMDUSER**-COMMAND**-CODE*");

	// KERBEROS Options...
	showKerberosGroupName = true;						// Show the KERBEROS group
	showKerberosTimeout = true;							// Show Kerberos timeout
	showKerberosRetries = true;							// Show Kerberos retries

	// LDAP Options...
	showLDAPGroupName = true;							// Show the LDAP group
	configLDAPPassword = i18n("The *ABBREV*TACACS+*-ABBREV* password can be configured using the following command in the aaa-server group command mode:*CODE**COMMAND*ldap-login-password *CMDUSER*password*-CMDUSER**-COMMAND**-CODE*");						// The text and commands to configure an LDAP server password

	// SecurID Options...
	showSecurIDGroupName = true;						// Show the SecurID group

	// NT Options...
	showNTGroupName = true;							// Show the NT group


	serverProtocol = tacacsAuth;
	serverAdded = false;
	timeout = 10;
}


int CiscoSecAuthentication::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	localUserConfig *userPointer = 0;
	tacacsServerConfig *tacacsPointer = 0;
	radiusServerConfig *radiusPointer = 0;
	kerberosServerConfig *kerberosPointer = 0;
	ldapServerConfig *ldapPointer = 0;
	securidServerConfig *securidPointer = 0;
	ntServerConfig *ntPointer = 0;
	authConfig *authPointer = 0;
	fpos_t filePosition;
	bool setting = false;
	int tempInt = 0;
	int errorCode = 0;
	string tempString;

	// Init
	if (strcmp(command->part(0), "no") == 0)
	{
		tempInt = 1;
		setting = false;
	}
	else
	{
		tempInt = 0;
		setting = true;
	}

	// username...
	if ((strcmp(command->part(tempInt), "username") == 0) && ((strcmp(command->part(tempInt + 2), "password") == 0) || (strcmp(command->part(tempInt + 2), "nopassword") == 0)))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sUsername Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;

		if (setting == true)
		{
			userPointer = getUser(command->part(tempInt));
			userPointer->privilegeLevel.assign("2");
			userPointer->encryption = clearText;
			tempInt++;
			if (strcmp(command->part(tempInt), "password") == 0)
			{
				tempInt++;
				userPointer->password.assign(command->part(tempInt));
				if (strcmp(command->part(tempInt + 1), "encrypted") == 0)
				{
					userPointer->password.assign(device->isEncryptedDictionaryPassword(command->part(tempInt)));
					if (userPointer->password.length() == 0)
					{
						device->addJohnPassword(userPointer->username.c_str(), command->part(tempInt));
						userPointer->password.assign(command->part(tempInt));
						userPointer->encryption = md5Encryption;
					}
					tempInt += 2;
				}
				else if (strcmp(command->part(tempInt + 1), "mschap") == 0)
				{
					userPointer->password.assign(device->isEncryptedDictionaryPassword(command->part(tempInt)));
					if (userPointer->password.length() == 0)
					{
						device->addJohnPassword(userPointer->username.c_str(), command->part(tempInt));
						userPointer->encryption = md4Encryption;
					}
					tempInt += 2;
				}
				else if (strcmp(command->part(tempInt + 1), "nt-encrypted") == 0)
				{
					userPointer->password.assign(device->isEncryptedDictionaryPassword(command->part(tempInt)));
					if (userPointer->password.length() == 0)
					{
						device->addJohnPassword(userPointer->username.c_str(), command->part(tempInt));
						userPointer->encryption = ntEncryption;
					}
					tempInt += 2;
				}
			}
			else if (strcmp(command->part(tempInt), "nopassword") == 0)
				tempInt++;

			if  (strcmp(command->part(tempInt), "privilege") == 0)
			{
				tempInt++;
				userPointer->privilegeLevel.assign(command->part(tempInt));
				if (strcmp(command->part(tempInt), "15") == 0)
					userPointer->adminAccess = true;
			}
		}
	}

	// enable...
	else if ((strcmp(command->part(tempInt), "enable") == 0) && (strcmp(command->part(tempInt + 1), "password") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sEnable Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 2;

		if (setting == true)
		{
			userPointer = getUser("enable");
			userPointer->privilegeLevel.assign("15");
			userPointer->encryption = clearText;
			userPointer->adminAccess = true;
			userPointer->password.assign(command->part(tempInt));
			tempInt++;

			while (tempInt < command->parts)
			{
				if (strcmp(command->part(tempInt), "encrypted") == 0)
				{
					tempString.assign(device->isEncryptedDictionaryPassword(userPointer->password.c_str()));
					if (tempString.length() == 0)
					{
						device->addJohnPassword(userPointer->username.c_str(), userPointer->password.c_str());
						userPointer->encryption = md5Encryption;
					}
					else
						userPointer->password.assign(tempString.c_str());
				}

				else if (strcmp(command->part(tempInt), "level") == 0)
				{
					tempInt++;
					userPointer->privilegeLevel.assign(command->part(tempInt));
				}

				tempInt++;
			}
		}
	}

	// password...
	else if ((strcmp(command->part(tempInt), "password") == 0) || (strcmp(command->part(tempInt), "passwd") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sPassword Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		accessWithoutAuthentication = false;
		tempInt++;

		if (setting == true)
		{
			userPointer = getUser("password");
			userPointer->encryption = clearText;
			userPointer->password.assign(command->part(tempInt));
			tempInt++;

			if (strcmp(command->part(tempInt), "encrypted") == 0)
			{
				tempString.assign(device->isEncryptedDictionaryPassword(userPointer->password.c_str()));
				if (tempString.length() == 0)
				{
					device->addJohnPassword(userPointer->username.c_str(), userPointer->password.c_str());
					userPointer->encryption = md5Encryption;
				}
				else
					userPointer->password.assign(tempString.c_str());
			}
		}
	}

	// aaa authentication...
	else if ((strcmp(command->part(tempInt), "aaa") == 0) && (strcmp(command->part(tempInt + 1), "authentication") == 0) && ((strcmp(command->part(tempInt + 2), "serial") == 0) || (strcmp(command->part(tempInt + 2), "enable") == 0) || (strcmp(command->part(tempInt + 2), "http") == 0) || (strcmp(command->part(tempInt + 2), "ssh") == 0) || (strcmp(command->part(tempInt + 2), "telnet") == 0)))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sAAA Authentication Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 2;

		authPointer = addMethod();
		authPointer->name.assign(command->part(tempInt + 2));
		authPointer->appliesTo.assign(command->part(tempInt));

		tempInt += 2;
		if (strcasecmp(command->part(tempInt), "LOCAL") != 0)
		{
			radiusPointer = radiusServer;
			while (radiusPointer != 0)
			{
				if (strcmp(command->part(tempInt), radiusPointer->groupName.c_str()) == 0)
					authPointer->method = radiusAuth;
				radiusPointer = radiusPointer->next;
			}
			tacacsPointer = tacacsServer;
			while (tacacsPointer != 0)
			{
				if (strcmp(command->part(tempInt), tacacsPointer->groupName.c_str()) == 0)
					authPointer->method = tacacsAuth;
				tacacsPointer = tacacsPointer->next;
			}
			kerberosPointer = kerberosServer;
			while (kerberosPointer != 0)
			{
				if (strcmp(command->part(tempInt), kerberosPointer->groupName.c_str()) == 0)
					authPointer->method = kerberosAuth;
				kerberosPointer = kerberosPointer->next;
			}
			securidPointer = securidServer;
			while (securidPointer != 0)
			{
				if (strcmp(command->part(tempInt), securidPointer->groupName.c_str()) == 0)
					authPointer->method = securidAuth;
				securidPointer = securidPointer->next;
			}
			ntPointer = ntServer;
			while (ntPointer != 0)
			{
				if (strcmp(command->part(tempInt), ntPointer->groupName.c_str()) == 0)
					authPointer->method = ntAuth;
				ntPointer = ntPointer->next;
			}
			ldapPointer = ldapServer;
			while (ldapPointer != 0)
			{
				if (strcmp(command->part(tempInt), ldapPointer->groupName.c_str()) == 0)
					authPointer->method = ldapAuth;
				ldapPointer = ldapPointer->next;
			}
		}
	}

	// auth protocol...
	else if ((strcmp(command->part(tempInt), "aaa-server") == 0) && (strcmp(command->part(tempInt + 2), "protocol") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sAAA Server Protocol Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;

		if (serverGroup.compare(command->part(tempInt)) != 0)
		{
			serverAdded = false;
			timeout = 10;
			key.assign("");
		}

		serverGroup.assign(command->part(tempInt));
		if (strcmp(command->part(tempInt + 2), "tacacs+") == 0)
		{
			serverProtocol = tacacsAuth;
		}
		else if (strcmp(command->part(tempInt + 2), "radius") == 0)
		{
			serverProtocol = radiusAuth;
		}
		else if (strcmp(command->part(tempInt + 2), "kerberos") == 0)
		{
			serverProtocol = kerberosAuth;
		}
		else if (strcmp(command->part(tempInt + 2), "sdi") == 0)
		{
			serverProtocol = securidAuth;
		}
		else if (strcmp(command->part(tempInt + 2), "ldap") == 0)
		{
			serverProtocol = ldapAuth;
		}
		else if (strcmp(command->part(tempInt + 2), "nt") == 0)
		{
			serverProtocol = ntAuth;
		}
	}

	// auth host...
	else if ((strcmp(command->part(tempInt), "aaa-server") == 0) && ((strcmp(command->part(tempInt + 2), "host") == 0) || (strcmp(command->part(tempInt + 3), "host") == 0)))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sAAA Server Host Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt++;

		if ((setting == true) && (strcmp(command->part(tempInt), serverGroup.c_str()) == 0))
		{
			tempInt++;
			if (strcmp(command->part(tempInt), "host") == 0)
				tempInt++;
			else
				tempInt += 2;
			switch (serverProtocol)
			{
				case radiusAuth:
					radiusPointer = addRadiusServer();
					radiusPointer->groupName.assign(serverGroup);
					radiusPointer->key.assign(key);
					radiusPointer->address.assign(command->part(tempInt));
					if (serverAdded == false)
					{
						radiusPointer->description.assign(i18n("Primary"));
					}
					else
					{
						radiusPointer->description.assign(i18n("Secondary"));
					}
					serverAdded = true;
					radiusPointer->timeout = 10;
					radiusPointer->retries = 10;
					tempInt++;
					while (tempInt < command->parts)
					{
						if (strcmp(command->part(tempInt), "timeout") != 0)
						{
							radiusPointer->key.assign(command->part(tempInt));
							key.assign(command->part(tempInt));
						}
						else
						{
							tempInt++;
							timeout = atoi(command->part(tempInt));
							radiusPointer->timeout = timeout;
						}

						tempInt++;
					}

					// Read a line from the config...
					fgetpos(device->inputFile, &filePosition);
					device->readLine(line, lineSize);

					while ((line[0] == ' ') && (feof(device->inputFile) == 0))
					{
						// Split it up into parts...
						command->setConfigLine(line);

						if (strcmp(command->part(0), "key") == 0)
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sKey Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							radiusPointer->key.assign(command->part(1));
						}
						else if (strcmp(command->part(0), "retry-interval") == 0)
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sRetry Interval Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							radiusPointer->retries = atoi(command->part(1));
						}
						else if (strcmp(command->part(0), "timeout") == 0)
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sTimeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							radiusPointer->timeout = atoi(command->part(1));
						}

						// NOT PROCESSED...
						else
							device->lineNotProcessed(line);

						// Read a line from the config...
						fgetpos(device->inputFile, &filePosition);
						device->readLine(line, lineSize);
					}
					// Set file position back
					fsetpos(device->inputFile, &filePosition);
					break;

				case tacacsAuth:
					tacacsPointer = addTacacsServer();
					tacacsPointer->groupName.assign(serverGroup);
					tacacsPointer->key.assign(key);
					tacacsPointer->address.assign(command->part(tempInt));
					if (serverAdded == false)
					{
						tacacsPointer->description.assign(i18n("Primary"));
					}
					else
					{
						tacacsPointer->description.assign(i18n("Secondary"));
					}
					serverAdded = true;
					tacacsPointer->timeout = 10;
					tacacsPointer->retries = 10;
					tempInt++;
					while (tempInt < command->parts)
					{
						if (strcmp(command->part(tempInt), "timeout") != 0)
						{
							tacacsPointer->key.assign(command->part(tempInt));
							key.assign(command->part(tempInt));
						}
						else
						{
							tempInt++;
							timeout = atoi(command->part(tempInt));
							tacacsPointer->timeout = timeout;
						}

						tempInt++;
					}

					// Read a line from the config...
					fgetpos(device->inputFile, &filePosition);
					device->readLine(line, lineSize);

					while ((line[0] == ' ') && (feof(device->inputFile) == 0))
					{
						// Split it up into parts...
						command->setConfigLine(line);

						if (strcmp(command->part(0), "key") == 0)
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sKey Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							tacacsPointer->key.assign(command->part(1));
						}
						else if (strcmp(command->part(0), "retry-interval") == 0)
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sRetry Interval Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							tacacsPointer->retries = atoi(command->part(1));
						}
						else if (strcmp(command->part(0), "timeout") == 0)
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sTimeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							tacacsPointer->timeout = atoi(command->part(1));
						}

						// NOT PROCESSED...
						else
							device->lineNotProcessed(line);

						// Read a line from the config...
						fgetpos(device->inputFile, &filePosition);
						device->readLine(line, lineSize);
					}
					// Set file position back
					fsetpos(device->inputFile, &filePosition);
					break;

				case ldapAuth:
					ldapPointer = addLDAPServer();
					ldapPointer->groupName.assign(serverGroup);
					ldapPointer->password.assign(key);
					ldapPointer->address.assign(command->part(tempInt));
					if (serverAdded == false)
					{
						ldapPointer->description.assign(i18n("Primary"));
					}
					else
					{
						ldapPointer->description.assign(i18n("Secondary"));
					}
					serverAdded = true;
					ldapPointer->timeout = 10;
					ldapPointer->retries = 10;
					tempInt++;
					while (tempInt < command->parts)
					{
						if (strcmp(command->part(tempInt), "timeout") == 0)
						{
							tempInt++;
							timeout = atoi(command->part(tempInt));
							ldapPointer->timeout = timeout;
						}

						tempInt++;
					}

					// Read a line from the config...
					fgetpos(device->inputFile, &filePosition);
					device->readLine(line, lineSize);

					while ((line[0] == ' ') && (feof(device->inputFile) == 0))
					{
						// Split it up into parts...
						command->setConfigLine(line);

						if (strcmp(command->part(0), "ldap-login-password") == 0)
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sPassword Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							ldapPointer->password.assign(command->part(1));
						}
						else if (strcmp(command->part(0), "ldap-naming-attribute") == 0)
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sCN Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							ldapPointer->cn.assign(command->part(1));
						}
						else if (strcmp(command->part(0), "ldap-login-dn") == 0)
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sDN Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							ldapPointer->dn.assign(command->part(1));
						}
						else if (strcmp(command->part(0), "ldap-dn") == 0)
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sDN Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							ldapPointer->dn.assign(command->part(1));
						}
						else if (strcmp(command->part(0), "retry-interval") == 0)
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sRetry Interval Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							ldapPointer->retries = atoi(command->part(1));
						}
						else if (strcmp(command->part(0), "timeout") == 0)
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sTimeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							ldapPointer->timeout = atoi(command->part(1));
						}

						// NOT PROCESSED...
						else
							device->lineNotProcessed(line);

						// Read a line from the config...
						fgetpos(device->inputFile, &filePosition);
						device->readLine(line, lineSize);
					}
					// Set file position back
					fsetpos(device->inputFile, &filePosition);
					break;

				case securidAuth:
					securidPointer = addSecurIDServer();
					securidPointer->groupName.assign(serverGroup);
					securidPointer->address.assign(command->part(tempInt));
					if (serverAdded == false)
					{
						securidPointer->description.assign(i18n("Primary"));
					}
					else
					{
						securidPointer->description.assign(i18n("Secondary"));
					}
					serverAdded = true;
					securidPointer->timeout = 10;
					securidPointer->retries = 10;
					tempInt++;
					while (tempInt < command->parts)
					{
						if (strcmp(command->part(tempInt), "timeout") == 0)
						{
							tempInt++;
							timeout = atoi(command->part(tempInt));
							securidPointer->timeout = timeout;
						}

						tempInt++;
					}

					// Read a line from the config...
					fgetpos(device->inputFile, &filePosition);
					device->readLine(line, lineSize);

					while ((line[0] == ' ') && (feof(device->inputFile) == 0))
					{
						// Split it up into parts...
						command->setConfigLine(line);

						if (strcmp(command->part(0), "retry-interval") == 0)
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sRetry Interval Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							securidPointer->retries = atoi(command->part(1));
						}
						else if (strcmp(command->part(0), "timeout") == 0)
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sTimeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							securidPointer->timeout = atoi(command->part(1));
						}

						// NOT PROCESSED...
						else
							device->lineNotProcessed(line);

						// Read a line from the config...
						fgetpos(device->inputFile, &filePosition);
						device->readLine(line, lineSize);
					}
					// Set file position back
					fsetpos(device->inputFile, &filePosition);
					break;

				case kerberosAuth:
					kerberosPointer = addKerberosServer();
					kerberosPointer->groupName.assign(serverGroup);
					kerberosPointer->address.assign(command->part(tempInt));
					if (serverAdded == false)
					{
						kerberosPointer->description.assign(i18n("Primary"));
					}
					else
					{
						kerberosPointer->description.assign(i18n("Secondary"));
					}
					serverAdded = true;
					kerberosPointer->timeout = 10;
					kerberosPointer->retries = 10;
					tempInt++;
					while (tempInt < command->parts)
					{
						if (strcmp(command->part(tempInt), "timeout") != 0)
						{
							kerberosPointer->realm.assign(command->part(tempInt));
							key.assign(command->part(tempInt));
						}
						else
						{
							tempInt++;
							timeout = atoi(command->part(tempInt));
							kerberosPointer->timeout = timeout;
						}

						tempInt++;
					}

					// Read a line from the config...
					fgetpos(device->inputFile, &filePosition);
					device->readLine(line, lineSize);

					while ((line[0] == ' ') && (feof(device->inputFile) == 0))
					{
						// Split it up into parts...
						command->setConfigLine(line);

						if (strcmp(command->part(0), "kerberos-realm") == 0)
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sRealm Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							kerberosPointer->realm.assign(command->part(1));
						}
						else if (strcmp(command->part(0), "retry-interval") == 0)
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sRetry Interval Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							kerberosPointer->retries = atoi(command->part(1));
						}
						else if (strcmp(command->part(0), "timeout") == 0)
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sTimeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							kerberosPointer->timeout = atoi(command->part(1));
						}

						// NOT PROCESSED...
						else
							device->lineNotProcessed(line);

						// Read a line from the config...
						fgetpos(device->inputFile, &filePosition);
						device->readLine(line, lineSize);
					}
					// Set file position back
					fsetpos(device->inputFile, &filePosition);
					break;

				default:
					ntPointer = addNTServer();
					ntPointer->groupName.assign(serverGroup);
					ntPointer->address.assign(command->part(tempInt));
					if (serverAdded == false)
					{
						ntPointer->description.assign(i18n("Primary"));
					}
					else
					{
						ntPointer->description.assign(i18n("Secondary"));
					}
					serverAdded = true;
					ntPointer->timeout = 10;
					tempInt++;
					while (tempInt < command->parts)
					{
						if (strcmp(command->part(tempInt), "timeout") != 0)
						{
							ntPointer->pdc.assign(command->part(tempInt));
							key.assign(command->part(tempInt));
						}
						else
						{
							tempInt++;
							timeout = atoi(command->part(tempInt));
							ntPointer->timeout = timeout;
						}

						tempInt++;
					}

					// Read a line from the config...
					fgetpos(device->inputFile, &filePosition);
					device->readLine(line, lineSize);

					while ((line[0] == ' ') && (feof(device->inputFile) == 0))
					{
						// Split it up into parts...
						command->setConfigLine(line);

						if (strcmp(command->part(0), "nt-auth-domain-controller") == 0)
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sNT Auth Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							ntPointer->pdc.assign(command->part(1));
						}
						else if (strcmp(command->part(0), "timeout") == 0)
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sTimeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							ntPointer->timeout = atoi(command->part(1));
						}

						// NOT PROCESSED...
						else
							device->lineNotProcessed(line);

						// Read a line from the config...
						fgetpos(device->inputFile, &filePosition);
						device->readLine(line, lineSize);
					}
					// Set file position back
					fsetpos(device->inputFile, &filePosition);
					break;
			}
		}
	}

	// NOT PROCESSED...
	else
		device->lineNotProcessed(line);

	return errorCode;
}


int CiscoSecAuthentication::processDefaults(Device *device)
{
	return 0;
}

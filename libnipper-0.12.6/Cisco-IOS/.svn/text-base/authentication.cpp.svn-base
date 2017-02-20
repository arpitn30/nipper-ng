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
#include "iosdevice.h"
#include "authentication.h"
#include "administration.h"
#include "../device/common/configline.h"


IOSAuthentication::IOSAuthentication()
{
	// General...
	authenticationConfigIntro = i18n("This section describes the various *DEVICETYPE* device authentication settings.");		// Introduction text to the whole section
	loginAttemptsSupported = false;						// Login attempts supported
	loginAttempts = 0;									// Login attempts allowed (0 =  infinite)
	accessWithoutAuthentication = false;				// Set to true if access is allowed without authentication
	configAccessAuthentication = "The following commands can be used on *DEVICETYPE* devices to configure the enable password and a local user:*CODE**COMMAND*enable secret *CMDUSER*password*-CMDUSER**-COMMAND**COMMAND*username *CMDUSER*user*-CMDUSER* secret *CMDUSER*password*-CMDUSER**-COMMAND**-CODE*";					// The text and commands to configure access authentication with a password

	// Authentication Methods...
	authMethodSupported = true;							// Authentication Method Supported
	appliesToSupported = true;							// Applies To Supported
	namedAuthSupport = true;							// Are auth servers named?
	showAuthLevel = true;								// Show auth level

	// Local User Options...
	encryptionSupported = true;							// Show encryption
	readOnlySupported = false;							// Is read only supported?
	outboundACLSupported = true;						// Are outbound filtering ACL supported?
	privilegeLevelSupported = true;						// Are privilege levels supported?
	privilegeLevelText = i18n("Privilege Level");		// The table title privilege level text
	configDeviceSpecificLocalUsers = "The users can be assigned to different privilege levels which are configurable and determine the level of access granted. A level 15 user is the highest level and is typically reserved for management of the device. The enable user password is typically used for performing administration on *DEVICETYPE* devices. However if an enable user password has not been configured, a line password will be used instead.";				// Text for the config report local user section.
	filterText = i18n("*ABBREV*ACL*-ABBREV*");			// The table filter column title text

	// TACACS Options...
	showTacacsGroupName = true;							// Show the TACACS group 
	showTacacsRetries = false;							// Show the TACACS retries
	configTacacsKey = i18n("The following command can be used to set the global *ABBREV*TACACS+*-ABBREV* server key:*CODE*tacacs-server key *CMDUSER*key*-CMDUSER**-CODE*");							// The text and commands to configure a TACACS+ key

	// RADIUS Options...
	showRadiusGroupName = true;							// Show the RADIUS group
	configRadiusKey = i18n("The following command can be used to set the global *ABBREV*RADIUS*-ABBREV* server key:*CODE*radius-server key *CMDUSER*key*-CMDUSER**-CODE*");							// The text and commands to configure a RADIUS key

	// KERBEROS Options...
	showKerberosGroupName = false;						// Show the KERBEROS group
	showKerberosTimeout = false;						// Show Kerberos timeout
	showKerberosRetries = false;						// Show Kerberos retries

	// LDAP Options...
	showLDAPGroupName = false;							// Show the LDAP group
	showLDAPPassword = false;							// Show LDAP password
	configLDAPPassword = i18n("");						// The text and commands to configure an LDAP server password

	// SecurID Options...
	showSecurIDGroupName = false;						// Show the SecurID group
	showSecurIDDuress = false;							// Show the SecurID Duress
	showSecurIDEncryption = false;						// Show the SecurID Encryption

	// NT Options...
	showNTGroupName = false;							// Show the NT group


	tacacsPort = 49;
	tacacsTimeout = 5;
	radiusPort = 1645;
	radiusTimeout = 5;
	radiusRetries = 3;
	tacacsKeyEnc = clearText;
	radiusKeyEnc = clearText;
}


int IOSAuthentication::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	localUserConfig *localUserPointer = 0;
	tacacsServerConfig *tacacsPointer = 0;
	radiusServerConfig *radiusPointer = 0;
	kerberosServerConfig *kerberosPointer = 0;
	authConfig *authPointer = 0;
	string tempString;
	bool setting = false;
	int tempInt = 0;
	int errorCode = 0;

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

	// AAA
	if (strcmp(command->part(0), "aaa") == 0)
	{
		((IOSAdministration *)device->administration)->aaaUsed = true;

		if ((strcmp(command->part(2), "enable") == 0) || (strcmp(command->part(2), "login") == 0) || (strcmp(command->part(2), "dot1x") == 0) || (strcmp(command->part(2), "ppp") == 0) || (strcmp(command->part(2), "arap") == 0) || (strcmp(command->part(2), "eou") == 0) || (strcmp(command->part(2), "sgbp") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sAAA Authentication Method Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			tempInt = 4;
			while (tempInt < command->parts)
			{
				authPointer = addMethod();
				authPointer->level.assign(command->part(2));
				if (strcmp(command->part(3), "default") != 0)
					authPointer->appliesTo.assign(command->part(3));
				if (strcmp(command->part(tempInt), "none") == 0)
					authPointer->method = noAuthRequired;
				else if (strcmp(command->part(tempInt), "local") == 0)
					authPointer->method = localAuth;
				else if (strcmp(command->part(tempInt), "local-case") == 0)
					authPointer->method = localAuth;
				else if (strcmp(command->part(tempInt), "krb5") == 0)
					authPointer->method = kerberosAuth;
				else if (strcmp(command->part(tempInt), "krb5-telnet") == 0)
					authPointer->method = kerberosAuth;
				else if (strcmp(command->part(tempInt), "line") == 0)
					authPointer->method = lineAuth;
				else if (strcmp(command->part(tempInt), "enable") == 0)
					authPointer->method = enableAuth;
				else if (strcmp(command->part(tempInt), "group") == 0)
				{
					tempInt++;
					if (strcmp(command->part(tempInt), "radius") == 0)
						authPointer->method = radiusAuth;
					else if (strcmp(command->part(tempInt), "tacacs+") == 0)
						authPointer->method = tacacsAuth;
					else
					{
						authPointer->method = serverGroupAuth;
						authPointer->name.assign(command->part(tempInt));
					}
				}
				tempInt++;
			}
		}

		else if ((strcmp(command->part(1), "group") == 0) && (strcmp(command->part(3), "tacacs+") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sAAA TACACS+ Group Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			groupName.assign(command->part(4));

			// Read a line from the config...
			device->readLine(line, lineSize);

			// Split it up into parts...
			command->setConfigLine(line);

			while ((feof(device->inputFile) == 0) && (line[0] != '!'))
			{

				// Server
				if (strcmp(command->part(0), "server") == 0)
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sAAA Group Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					tacacsPointer = addTacacsServer();
					tacacsPointer->groupName.assign(groupName);
					tacacsPointer->address.assign(command->part(1));
					tacacsPointer->timeout = tacacsTimeout;
					tacacsPointer->port = tacacsPort;
					tacacsPointer->key.assign(tacacsKey);
					tacacsPointer->encryption = tacacsKeyEnc;
				}

				// Private Server
				else if (strcmp(command->part(0), "server-private") == 0)
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sAAA Group Server Private Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					tacacsPointer = addTacacsServer();
					tacacsPointer->groupName.assign(groupName);
					tacacsPointer->address.assign(command->part(1));
					tacacsPointer->timeout = tacacsTimeout;
					tacacsPointer->port = tacacsPort;
					tacacsPointer->key.assign(tacacsKey);
					tacacsPointer->encryption = tacacsKeyEnc;
					tempInt = 2;
					while (tempInt < command->parts)
					{
						if (strcmp(command->part(tempInt), "key") == 0)
						{
							tempInt++;
							if (strcmp(command->part(tempInt), "0") == 0)
							{
								tempInt++;
								tacacsPointer->key.assign(command->part(tempInt));
								tacacsPointer->encryption = clearText;
							}
							else if (strcmp(command->part(tempInt), "7") == 0)
							{
								tempInt++;
								tacacsPointer->key.assign(device->ciscoType7Decode(command->part(tempInt)));
								tacacsPointer->encryption = cisco7Encryption;
								if (tacacsPointer->key.empty())
								{
									tacacsPointer->key.assign(command->part(tempInt));
									tempString.assign("tacacs-");
									tempString.append(tacacsPointer->address);
									device->addJohnPassword(tempString.c_str(), command->part(tempInt));
									tacacsPointer->encryption = md5Encryption;
								}
							}
							else
							{
								tacacsPointer->key.assign(command->part(tempInt));
								tacacsPointer->encryption = clearText;
							}
						}
						else if (strcmp(command->part(tempInt), "port") == 0)
						{
							tempInt++;
							tacacsPointer->port = atoi(command->part(tempInt));
						}
						else if (strcmp(command->part(tempInt), "timeout") == 0)
						{
							tempInt++;
							tacacsPointer->timeout = atoi(command->part(tempInt));
						}
						tempInt++;
					}
				}

				// NOT PROCESSED...
				else
					device->lineNotProcessed(line);

				// Read a line from the config...
				device->readLine(line, lineSize);

				// Split it up into parts...
				command->setConfigLine(line);
			}
		}

		else if ((strcmp(command->part(1), "group") == 0) && (strcmp(command->part(3), "radius") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sAAA RADIUS Group Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			groupName.assign(command->part(4));

			// Read a line from the config...
			device->readLine(line, lineSize);

			// Split it up into parts...
			command->setConfigLine(line);

			while ((feof(device->inputFile) == 0) && (line[0] != '!'))
			{

				// Server
				if (strcmp(command->part(0), "server") == 0)
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sAAA Group Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					radiusPointer = addRadiusServer();
					radiusPointer->groupName.assign(groupName);
					radiusPointer->address.assign(command->part(1));
					radiusPointer->timeout = radiusTimeout;
					radiusPointer->port = radiusPort;
					radiusPointer->retries = radiusRetries;
					if (strcmp(command->part(2), "auth-port") == 0)
						radiusPointer->port = atoi(command->part(3));
				}

				// Private Server
				else if (strcmp(command->part(0), "server-private") == 0)
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sAAA Group Server Private Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					radiusPointer = addRadiusServer();
					radiusPointer->groupName.assign(groupName);
					radiusPointer->address.assign(command->part(1));
					radiusPointer->timeout = radiusTimeout;
					radiusPointer->port = radiusPort;
					radiusPointer->retries = radiusRetries;
					tempInt = 2;
					while (tempInt < command->parts)
					{
						if (strcmp(command->part(tempInt), "key") == 0)
						{
							tempInt++;
							if (strcmp(command->part(tempInt), "0") == 0)
							{
								tempInt++;
								radiusPointer->key.assign(command->part(tempInt));
								radiusPointer->encryption = clearText;
							}
							else if (strcmp(command->part(tempInt), "7") == 0)
							{
								tempInt++;
								radiusPointer->key.assign(device->ciscoType7Decode(command->part(tempInt)));
								radiusPointer->encryption = cisco7Encryption;
								if (radiusPointer->key.empty())
								{
									radiusPointer->key.assign(command->part(tempInt));
									radiusPointer->encryption = md5Encryption;
									tempString.assign("radius-");
									tempString.append(radiusPointer->address);
									device->addJohnPassword(tempString.c_str(), command->part(tempInt));
								}
							}
							else
							{
								radiusPointer->key.assign(command->part(tempInt));
								radiusPointer->encryption = clearText;
							}
						}
						else if (strcmp(command->part(tempInt), "auth-port") == 0)
						{
							tempInt++;
							radiusPointer->port = atoi(command->part(tempInt));
						}
						else if (strcmp(command->part(tempInt), "retransmit") == 0)
						{
							tempInt++;
							radiusPointer->retries = atoi(command->part(tempInt));
						}
						else if (strcmp(command->part(tempInt), "timeout") == 0)
						{
							tempInt++;
							radiusPointer->timeout = atoi(command->part(tempInt));
						}
						tempInt++;
					}
				}

				// NOT PROCESSED...
				else
					device->lineNotProcessed(line);

				// Read a line from the config...
				device->readLine(line, lineSize);

				// Split it up into parts...
				command->setConfigLine(line);
			}
		}

		// NOT PROCESSED...
		else
			device->lineNotProcessed(line);
	}

	// TACACS Key
	else if ((strcmp(command->part(0), "tacacs-server") == 0) && (strcmp(command->part(1), "key") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sTACACS+ Key Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (strcmp(command->part(2), "0") == 0)
		{
			tacacsKey.assign(command->part(3));
			tacacsKeyEnc = clearText;
		}
		else if (strcmp(command->part(2), "7") == 0)
		{
			tacacsKey.assign(device->ciscoType7Decode(command->part(3)));
			tacacsKeyEnc = cisco7Encryption;
			if (tacacsKey.empty())
			{
				tacacsKey.assign(command->part(3));
				device->addJohnPassword("tacacs", command->part(3));
				tacacsKeyEnc = md5Encryption;
			}
		}
		else
		{
			tacacsKey.assign(command->part(2));
			tacacsKeyEnc = clearText;
		}
	}

	// TACACS+ Host
	else if ((strcmp(command->part(0), "tacacs-server") == 0) && (strcmp(command->part(1), "host") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sTACACS+ Host Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		tacacsPointer = addTacacsServer();
		tacacsPointer->groupName.assign(groupName);
		tacacsPointer->address.assign(command->part(2));
		tacacsPointer->timeout = tacacsTimeout;
		tacacsPointer->port = tacacsPort;
		tacacsPointer->key.assign(tacacsKey);
		tacacsPointer->encryption = tacacsKeyEnc;
		tempInt = 3;
		while (tempInt < command->parts)
		{
			if (strcmp(command->part(tempInt), "key") == 0)
			{
				tempInt++;
				if (strcmp(command->part(tempInt), "0") == 0)
				{
					tempInt++;
					tacacsPointer->key.assign(command->part(tempInt));
					tacacsPointer->encryption = clearText;
				}
				else if (strcmp(command->part(tempInt), "7") == 0)
				{
					tempInt++;
					tacacsPointer->key.assign(device->ciscoType7Decode(command->part(tempInt)));
					tacacsPointer->encryption = cisco7Encryption;
					if (tacacsPointer->key.empty())
					{
						tacacsPointer->key.assign(command->part(tempInt));
						tempString.assign("tacacs-");
						tempString.append(tacacsPointer->address);
						device->addJohnPassword(tempString.c_str(), command->part(tempInt));
						tacacsPointer->encryption = md5Encryption;
					}
				}
				else
				{
					tacacsPointer->key.assign(command->part(tempInt));
					tacacsPointer->encryption = clearText;
				}
			}
			else if (strcmp(command->part(tempInt), "port") == 0)
			{
				tempInt++;
				tacacsPointer->port = atoi(command->part(tempInt));
			}
			else if (strcmp(command->part(tempInt), "timeout") == 0)
			{
				tempInt++;
				tacacsPointer->timeout = atoi(command->part(tempInt));
			}
			tempInt++;
		}
	}

	// TACACS+ Timeout
	else if ((strcmp(command->part(0), "tacacs-server") == 0) && (strcmp(command->part(1), "timeout") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sTACACS+ Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		tacacsTimeout = atoi(command->part(2));
	}

	// Kerberos
	else if ((strcmp(command->part(0), "kerberos") == 0) && (strcmp(command->part(1), "server") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sKerberos Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		kerberosPointer = addKerberosServer();
		kerberosPointer->address.assign(command->part(3));
		kerberosPointer->realm.assign(command->part(2));
		if (command->parts == 5)
			kerberosPointer->port = atoi(command->part(4));
		else
			kerberosPointer->port = 88;
	}

	// RADIUS Timeout
	else if ((strcmp(command->part(0), "radius-server") == 0) && (strcmp(command->part(1), "timeout") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sRADIUS Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		radiusTimeout = atoi(command->part(2));
	}

	// RADIUS Retransmit
	else if ((strcmp(command->part(0), "radius-server") == 0) && (strcmp(command->part(1), "retransmit") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sRADIUS Retransmit Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		radiusRetries= atoi(command->part(2));
	}

	// RADIUS Key
	else if ((strcmp(command->part(0), "radius-server") == 0) && (strcmp(command->part(1), "key") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sRADIUS Key Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (strcmp(command->part(2), "0") == 0)
		{
			radiusKey.assign(command->part(3));
			radiusKeyEnc = clearText;
		}
		else if (strcmp(command->part(2), "7") == 0)
		{
			radiusKey.assign(device->ciscoType7Decode(command->part(3)));
			radiusKeyEnc = cisco7Encryption;
			if (radiusKey.empty())
			{
				radiusKey.assign(command->part(3));
				device->addJohnPassword("radius", command->part(3));
				radiusKeyEnc = md5Encryption;
			}
		}
		else
		{
			radiusKey.assign(command->part(2));
			radiusKeyEnc = clearText;
		}
	}

	// RADIUS Host
	else if ((strcmp(command->part(0), "radius-server") == 0) && (strcmp(command->part(1), "host") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sRADIUS Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		radiusPointer = addRadiusServer();
		radiusPointer->groupName.assign(groupName);
		radiusPointer->address.assign(command->part(2));
		radiusPointer->timeout = radiusTimeout;
		radiusPointer->port = radiusPort;
		radiusPointer->retries = radiusRetries;
		tempInt = 3;
		while (tempInt < command->parts)
		{
			if (strcmp(command->part(tempInt), "key") == 0)
			{
				tempInt++;
				if (strcmp(command->part(tempInt), "0") == 0)
				{
					tempInt++;
					radiusPointer->key.assign(command->part(tempInt));
					radiusPointer->encryption = clearText;
				}
				else if (strcmp(command->part(tempInt), "7") == 0)
				{
					tempInt++;
					radiusPointer->key.assign(device->ciscoType7Decode(command->part(tempInt)));
					radiusPointer->encryption = cisco7Encryption;
					if (radiusPointer->key.empty())
					{
						radiusPointer->key.assign(command->part(tempInt));
						radiusPointer->encryption = md5Encryption;
						device->addJohnPassword("radius", command->part(tempInt));
					}
				}
				else
				{
					radiusPointer->key.assign(command->part(tempInt));
					radiusPointer->encryption = clearText;
				}
			}
			else if (strcmp(command->part(tempInt), "auth-port") == 0)
			{
				tempInt++;
				radiusPointer->port = atoi(command->part(tempInt));
			}
			else if (strcmp(command->part(tempInt), "retransmit") == 0)
			{
				tempInt++;
				radiusPointer->retries = atoi(command->part(tempInt));
			}
			else if (strcmp(command->part(tempInt), "timeout") == 0)
			{
				tempInt++;
				radiusPointer->timeout = atoi(command->part(tempInt));
			}
			tempInt++;
		}
	}

	// Enable
	else if (strcmp(command->part(tempInt), "enable") == 0)
	{
		tempInt++;
		if (device->config->reportFormat == Config::Debug)
			printf("%sEnable Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		// Create user...
		if (strcmp(command->part(tempInt), "secret") == 0)
			localUserPointer = getUser("enable (secret)");
		else
			localUserPointer = getUser("enable (password)");
		tempInt++;

		localUserPointer->adminAccess = true;
		// Add level...
		if ((strcmp(command->part(tempInt), "level") == 0) || (strcmp(command->part(tempInt), "privilege") == 0))
		{
			tempInt++;
			localUserPointer->privilegeLevel.assign(command->part(tempInt));
			tempInt++;
		}
		else
			localUserPointer->privilegeLevel.assign("15");

		// Password...
		if (strcmp(command->part(tempInt), "0") == 0)
		{
			tempInt++;
			localUserPointer->encryption = clearText;
			localUserPointer->password.assign(command->part(tempInt));
		}
		else if (strcmp(command->part(tempInt), "5") == 0)
		{
			tempInt++;
			localUserPointer->encryption = md5Encryption;
			localUserPointer->password.assign(command->part(tempInt));
		}
		else if (strcmp(command->part(tempInt), "6") == 0)
		{
			tempInt++;
			localUserPointer->encryption = aesEncryption;
			localUserPointer->password.assign(command->part(tempInt));
		}
		else if (strcmp(command->part(tempInt), "7") == 0)
		{
			tempInt++;
			localUserPointer->encryption = cisco7Encryption;
			localUserPointer->password.assign(device->ciscoType7Decode(command->part(tempInt)));
		}
		else
		{
			localUserPointer->encryption = clearText;
			localUserPointer->password.assign(command->part(tempInt));
		}
	}

	// Usernames...
	else if (strcmp(command->part(tempInt), "username") == 0)
	{
		tempInt++;

		if (device->config->reportFormat == Config::Debug)
			printf("%sUsername Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		localUserPointer = getUser(command->part(tempInt));
		if (localUserPointer->privilegeLevel.empty())
			localUserPointer->privilegeLevel.assign("1");
		tempInt++;

		while (tempInt < command->parts)
		{

			// Add level...
			if (strcmp(command->part(tempInt), "privilege") == 0)
			{
				tempInt++;
				localUserPointer->privilegeLevel.assign(command->part(tempInt));
				if (strcmp(command->part(tempInt), "15") == 0)
					localUserPointer->adminAccess = true;
			}

			// Access Class...
			else if (strcmp(command->part(tempInt), "access-class") == 0)
			{
				tempInt++;
				localUserPointer->outboundACL.assign(command->part(tempInt));
				localUserPointer->aclSupported = true;
			}

			// Password...
			else if ((strcmp(command->part(tempInt), "password") == 0) || (strcmp(command->part(tempInt), "secret") == 0))
			{
				tempInt++;

				if (strcmp(command->part(tempInt), "0") == 0)
				{
					tempInt++;
					localUserPointer->encryption = clearText;
					localUserPointer->password.assign(command->part(tempInt));
				}
				else if (strcmp(command->part(tempInt), "5") == 0)
				{
					tempInt++;
					localUserPointer->encryption = md5Encryption;
					localUserPointer->password.assign(command->part(tempInt));
				}
				else if (strcmp(command->part(tempInt), "6") == 0)
				{
					tempInt++;
					localUserPointer->encryption = aesEncryption;
					localUserPointer->password.assign(command->part(tempInt));
				}
				else if (strcmp(command->part(tempInt), "7") == 0)
				{
					tempInt++;
					localUserPointer->encryption = cisco7Encryption;
					localUserPointer->password.assign(device->ciscoType7Decode(command->part(tempInt)));
				}
				else
				{
					localUserPointer->encryption = clearText;
					localUserPointer->password.assign(command->part(tempInt));
				}
			}

			tempInt++;
		}
	}

	// NOT PROCESSED...
	else
		device->lineNotProcessed(line);

	return errorCode;
}


int IOSAuthentication::processDefaults(Device *device)
{
	// Variables...
	tacacsServerConfig *tacacsPointer = 0;
	radiusServerConfig *radiusPointer = 0;

	// Populate keys...
	if (!tacacsKey.empty())
	{
		tacacsPointer = tacacsServer;
		while (tacacsPointer != 0)
		{
			if (tacacsPointer->key.empty())
			{
				tacacsPointer->key.assign(tacacsKey);
				tacacsPointer->encryption = tacacsKeyEnc;
			}
			tacacsPointer = tacacsPointer->next;
		}
	}
	if (!radiusKey.empty())
	{
		radiusPointer = radiusServer;
		while (radiusPointer != 0)
		{
			if (radiusPointer->key.empty())
			{
				radiusPointer->key.assign(radiusKey);
				radiusPointer->encryption = radiusKeyEnc;
			}
			radiusPointer = radiusPointer->next;
		}
	}

	return 0;
}

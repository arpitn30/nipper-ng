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


CatalystAuthentication::CatalystAuthentication()
{
	// General...
	authenticationConfigIntro = i18n("This section describes the various *DEVICETYPE* device authentication settings.");		// Introduction text to the whole section
	loginAttemptsSupported = false;						// Login attempts supported
	loginAttempts = 0;									// Login attempts allowed (0 =  infinite)
	accessWithoutAuthentication = false;				// Set to true if access is allowed without authentication
	configAccessAuthentication = i18n("The following commands can be used to set the initial password and the enable password:*CODE**COMMAND*set password*-COMMAND**COMMAND*set enablepass*-COMMAND**-CODE*");				// The text and commands to configure access authentication with a password

	// Authentication Methods...
	authMethodSupported = true;						// Authentication Method Supported
	appliesToSupported = true;							// Applies To Supported
	namedAuthSupport = false;							// Are auth servers named?
	showAuthLevel = true;								// Show auth level

	// Local User Options...
	encryptionSupported = false;						// Show encryption
	readOnlySupported = false;							// Is read only supported?
	outboundACLSupported = false;						// Are outbound filtering ACL supported?
	privilegeLevelSupported = false;					// Are privilege levels supported?
	privilegeLevelText = i18n("Privilege Level");		// The table title privilege level text
	configDeviceSpecificLocalUsers = i18n("");			// Text for the config report local user section.
	filterText = i18n("*ABBREV*ACL*-ABBREV*");			// The table filter column title text

	// TACACS Options...
	showTacacsGroupName = false;						// Show the TACACS group 
	showTacacsRetries = true;							// Show the TACACS retries
	configTacacsKey = i18n("A *ABBREV*TACACS+*-ABBREV* server key can be configured with the following command:*CODE**COMMAND*set tacacs key *CMDUSER*key*-CMDUSER**-COMMAND**-CODE*");							// The text and commands to configure a TACACS+ key

	// RADIUS Options...
	showRadiusGroupName = false;						// Show the RADIUS group
	configRadiusKey = i18n("A *ABBREV*RADIUS*-ABBREV* server key can be configured with the following command:*CODE**COMMAND*set radius key *CMDUSER*key*-CMDUSER**-COMMAND**-CODE*");							// The text and commands to configure a 

	// KERBEROS Options...
	showKerberosGroupName = false;						// Show the KERBEROS group

	// LDAP Options...
	showLDAPGroupName = false;							// Show the LDAP group

	// SecurID Options...
	showSecurIDGroupName = false;						// Show the SecurID group
	showSecurIDDuress = false;							// Show the SecurID Duress
	showSecurIDEncryption = false;						// Show the SecurID Encryption

	// NT Options...
	showNTGroupName = false;							// Show the NT group



	firstServer = true;
}


int CatalystAuthentication::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	localUserConfig *userPointer = 0;
	tacacsServerConfig *tacacsPointer = 0;
	radiusServerConfig *radiusPointer = 0;
	kerberosServerConfig *kerberosPointer = 0;
	authConfig *authPointer = 0;
	int errorCode = 0;
	bool setting = false;

	// Init
	if (strcmp(command->part(0), "set") == 0)
		setting = true;
	else
		setting = false;

	// password...
	if (strcmp(command->part(1), "password") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sPassword Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		userPointer = getUser("password");
		userPointer->password.assign(command->part(2));
		userPointer->encryption = md5Encryption;
	}

	// enable...
	else if (strcmp(command->part(1), "enablepass") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sEnable Password Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		userPointer = getUser("enablepass");
		userPointer->password.assign(command->part(2));
		userPointer->encryption = md5Encryption;
		userPointer->adminAccess = true;
	}

	// authentication...
	else if ((strcmp(command->part(1), "authentication") == 0) && (strcmp(command->part(4), "enable") == 0) && ((strcmp(command->part(3), "kerberos") == 0) || (strcmp(command->part(3), "tacacs") == 0) || (strcmp(command->part(3), "local") == 0) || (strcmp(command->part(3), "radius") == 0)))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sAuthentication Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		authPointer = addMethod();
		authPointer->level.assign(command->part(2));
		authPointer->appliesTo.assign(command->part(5));
		if (strcmp(command->part(3), "kerberos") == 0)
			authPointer->method = kerberosAuth;
		else if (strcmp(command->part(3), "tacacs") == 0)
			authPointer->method = tacacsAuth;
		else if (strcmp(command->part(3), "radius") == 0)
			authPointer->method = radiusAuth;
		else if (strcmp(command->part(3), "local") == 0)
			authPointer->method = localAuth;
	}

	// tacacs...
	else if ((strcmp(command->part(1), "tacacs") == 0) && (strcmp(command->part(2), "server") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sTACACS+ Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		tacacsPointer = addTacacsServer();
		tacacsPointer->address.assign(command->part(3));
		tacacsPointer->timeout = 5;
		tacacsPointer->retries = 3;
		if (strcmp(command->part(4), "primary") == 0)
			tacacsPointer->description.assign(i18n("Primary"));
		else
			tacacsPointer->description.assign(i18n("Secondary"));
	}

	// tacacs key...
	else if ((strcmp(command->part(1), "tacacs") == 0) && (strcmp(command->part(2), "key") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sTACACS+ Key Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		tacacsPointer = tacacsServer;
		while (tacacsPointer != 0)
		{
			tacacsPointer->key.assign(strstr(line, command->part(3)));
			tacacsPointer = tacacsPointer->next;
		}
	}

	// tacacs timeout...
	else if ((strcmp(command->part(1), "tacacs") == 0) && (strcmp(command->part(2), "timeout") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sTACACS+ Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		tacacsPointer = tacacsServer;
		while (tacacsPointer != 0)
		{
			tacacsPointer->timeout = atoi(command->part(3));
			tacacsPointer = tacacsPointer->next;
		}
	}

	// tacacs attempts...
	else if ((strcmp(command->part(1), "tacacs") == 0) && (strcmp(command->part(2), "attempts") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sTACACS+ Attempts Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		tacacsPointer = tacacsServer;
		while (tacacsPointer != 0)
		{
			tacacsPointer->retries = atoi(command->part(3));
			tacacsPointer = tacacsPointer->next;
		}
	}

	// kerberos...
	else if ((strcmp(command->part(1), "kerberos") == 0) && (strcmp(command->part(2), "server") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sKerberos Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		kerberosPointer = addKerberosServer();
		kerberosPointer->realm.assign(command->part(3));
		kerberosPointer->address.assign(command->part(4));
		if (command->parts == 6)
			kerberosPointer->port = atoi(command->part(5));
		if (firstServer == true)
		{
			kerberosPointer->description.assign(i18n("Primary"));
			firstServer = false;
		}
		else
			kerberosPointer->description.assign(i18n("Secondard"));
	}

	// radius...
	else if ((strcmp(command->part(1), "radius") == 0) && (strcmp(command->part(2), "server") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sRADIUS Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		radiusPointer = addRadiusServer();
		radiusPointer->address.assign(command->part(3));
		radiusPointer->timeout = 5;
		radiusPointer->retries = 3;
		if (strcmp(command->part(4), "primary") == 0)
			radiusPointer->description.assign(i18n("Primary"));
		else
			radiusPointer->description.assign(i18n("Secondary"));
	}

	// radius key...
	else if ((strcmp(command->part(1), "radius") == 0) && (strcmp(command->part(2), "key") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sRADIUS Key Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		radiusPointer = radiusServer;
		while (tacacsPointer != 0)
		{
			radiusPointer->key.assign(strstr(line, command->part(3)));
			radiusPointer = radiusPointer->next;
		}
	}

	// radius timeout...
	else if ((strcmp(command->part(1), "radius") == 0) && (strcmp(command->part(2), "timeout") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sRADIUS Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		radiusPointer = radiusServer;
		while (radiusPointer != 0)
		{
			radiusPointer->timeout = atoi(command->part(3));
			radiusPointer = radiusPointer->next;
		}
	}

	// radius attempts...
	else if ((strcmp(command->part(1), "radius") == 0) && (strcmp(command->part(2), "retransmit") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sRADIUS Attempts Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		radiusPointer = radiusServer;
		while (radiusPointer != 0)
		{
			radiusPointer->retries = atoi(command->part(3));
			radiusPointer = radiusPointer->next;
		}
	}

	// NOT PROCESSED...
	else
		device->lineNotProcessed(line);

	return errorCode;
}


int CatalystAuthentication::processDefaults(Device *device)
{
	return 0;
}

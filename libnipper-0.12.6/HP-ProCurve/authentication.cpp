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


ProCurveAuthentication::ProCurveAuthentication()
{
	// General...
	authenticationConfigIntro = i18n("This section describes the various *DEVICETYPE* device authentication settings.");		// Introduction text to the whole section
	loginAttemptsSupported = false;						// Login attempts supported
	loginAttempts = 0;									// Login attempts allowed (0 =  infinite)
	accessWithoutAuthentication = false;				// Set to true if access is allowed without authentication
	configAccessAuthentication = "The manager and operator passwords can be configured with the following commands:*CODE**COMMAND*password manager*-COMMAND**COMMAND*password operator*-COMMAND**-CODE*";					// The text and commands to configure access authentication with a password

	// Authentication Methods...
	authMethodSupported = true;							// Authentication Method Supported
	appliesToSupported = true;							// Applies To Supported
	namedAuthSupport = false;							// Are auth servers named?
	showAuthLevel = true;								// Show auth level

	// Local User Options...
	encryptionSupported = false;						// Show encryption
	readOnlySupported = false;							// Is read only supported?
	outboundACLSupported = false;						// Are outbound filtering ACL supported?
	privilegeLevelSupported = false;					// Are privilege levels supported?
	privilegeLevelText = i18n("Privilege Level");		// The table title privilege level text
	configDeviceSpecificLocalUsers = "*DEVICETYPE* device local users are not listed in the configuration file. However, if the configuration does indicate as to whether the manager or operator users have had their passwords set. If the respective passwords have not been configured, the users are listed in this section.";				// Text for the config report local user section.
	filterText = i18n("*ABBREV*ACL*-ABBREV*");			// The table filter column title text

	// TACACS Options...
	showTacacsGroupName = false;						// Show the TACACS group 
	showTacacsRetries = false;							// Show the TACACS retries
	configTacacsKey = i18n("On *DEVICETYPE* devices a *ABBREV*TACACS+*-ABBREV* server key can be configured with the following command:*CODE**COMMAND*tacacs-server key *CMDUSER*key*-CMDUSER**-COMMAND**-CODE*");							// The text and commands to configure a TACACS+ key

	// RADIUS Options...
	showRadiusGroupName = false;						// Show the RADIUS group
	configRadiusKey = i18n("On *DEVICETYPE* devices a *ABBREV*RADIUS*-ABBREV* server key can be configured with the following command:*CODE**COMMAND*radius-server key *CMDUSER*key*-CMDUSER**-COMMAND**-CODE*");							// The text and commands to configure a RADIUS key

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


	tacacsTimeout = 5;
	tacacsFirst = true;
	radiusTimeout = 5;
	radiusRetransmit = 3;
	radiusFirst = true;
	operatorPresent = false;
	managerPresent = false;
}


int ProCurveAuthentication::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	authConfig *authPointer = 0;
	tacacsServerConfig *tacacsPointer = 0;
	radiusServerConfig *radiusPointer = 0;
	int tempInt = 0;
	int errorCode = 0;

	// tacacs...
	if (strcasecmp(command->part(0), "tacacs-server") == 0)
	{

		// key...
		if (strcasecmp(command->part(1), "key") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sTACACS+ Key Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			tacacsKey.assign(command->part(2));
		}

		// timeout...
		else if (strcasecmp(command->part(1), "timeout") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sTACACS+ Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			tacacsTimeout = atoi(command->part(2));
		}

		// host...
		else if (strcasecmp(command->part(1), "host") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sTACACS+ Host Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			tacacsPointer = addTacacsServer();
			tacacsPointer->address.assign(command->part(2));
			if (strcasecmp(command->part(3), "key") == 0)
				tacacsPointer->key.assign(command->part(4));
			else
				tacacsPointer->key.assign(tacacsKey);
			tacacsPointer->timeout = tacacsTimeout;
			if (tacacsFirst == true)
				tacacsPointer->description.assign(i18n("Primary"));
			else
				tacacsPointer->description.assign(i18n("Backup"));
			tacacsFirst = false;
		}

		// NOT PROCESSED...
		else
			device->lineNotProcessed(line);
	}

	// radius...
	else if (strcasecmp(command->part(0), "radius-server") == 0)
	{

		// key...
		if (strcasecmp(command->part(1), "key") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sRADIUS Key Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			radiusKey.assign(command->part(2));
		}

		// timeout...
		else if (strcasecmp(command->part(1), "timeout") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sRADIUS Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			radiusTimeout = atoi(command->part(2));
		}

		// host...
		else if (strcasecmp(command->part(1), "host") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sRADIUS Host Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			radiusPointer = addRadiusServer();
			radiusPointer->address.assign(command->part(2));
			radiusPointer->key.assign(radiusKey);
			tempInt = 3;
			while (tempInt < command->parts)
			{
				if (strcasecmp(command->part(3), "key") == 0)
				{
					tempInt++;
					radiusPointer->key.assign(command->part(tempInt));
				}
				tempInt++;
			}
			radiusPointer->timeout = radiusTimeout;
			if (radiusFirst == true)
				radiusPointer->description.assign(i18n("Primary"));
			else
				radiusPointer->description.assign(i18n("Backup"));
			radiusFirst = false;
		}

		// NOT PROCESSED...
		else
			device->lineNotProcessed(line);
	}

	// password manager...
	else if ((strcasecmp(command->part(0), "password") == 0) && (strcasecmp(command->part(1), "manager") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sManager Password Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		managerPresent = true;
	}

	// password operator...
	else if ((strcasecmp(command->part(0), "password") == 0) && (strcasecmp(command->part(1), "operator") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sOperator Password Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		operatorPresent = true;
	}

	// aaa authentication...
	else if ((strcasecmp(command->part(0), "aaa") == 0) && (strcasecmp(command->part(1), "authentication") == 0) && ((strcasecmp(command->part(3), "login") == 0) || (strcasecmp(command->part(3), "enable") == 0)))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sAAA Authentication Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		authPointer = addMethod();
		authPointer->appliesTo.assign(command->part(2));
		authPointer->level.assign(command->part(3));
		if (strcasecmp(command->part(4), "local") == 0)
			authPointer->method = localAuth;
		else if (strcasecmp(command->part(4), "radius") == 0)
			authPointer->method = radiusAuth;
		else if (strcasecmp(command->part(4), "tacacs") == 0)
			authPointer->method = tacacsAuth;

		if (command->parts == 6)
		{
			authPointer = addMethod();
			authPointer->appliesTo.assign(command->part(2));
			authPointer->level.assign(command->part(3));
			if (strcasecmp(command->part(5), "local") == 0)
				authPointer->method = localAuth;
			else if (strcasecmp(command->part(5), "radius") == 0)
				authPointer->method = radiusAuth;
			else if (strcasecmp(command->part(5), "tacacs") == 0)
				authPointer->method = tacacsAuth;
		}
	}

	// NOT PROCESSED...
	else
		device->lineNotProcessed(line);

	return errorCode;
}


int ProCurveAuthentication::processDefaults(Device *device)
{
	// Variables...
	localUserConfig *userPointer;

	if (operatorPresent == false)
	{
		userPointer = getUser("operator");
		userPointer->adminAccess = false;
	}

	if (managerPresent == false)
	{
		userPointer = getUser("manager");
		userPointer->adminAccess = true;
	}

	return 0;
}

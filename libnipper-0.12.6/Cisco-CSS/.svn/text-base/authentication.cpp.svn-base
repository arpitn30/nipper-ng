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


CiscoCSSAuthentication::CiscoCSSAuthentication()
{
	// General...
	authenticationConfigIntro = i18n("This section describes the various *DEVICETYPE* device authentication settings.");		// Introduction text to the whole section
	loginAttemptsSupported = false;						// Login attempts supported
	loginAttempts = 0;									// Login attempts allowed (0 =  infinite)
	accessWithoutAuthentication = false;				// Set to true if access is allowed without authentication
	configAccessAuthentication = "";					// The text and commands to configure access authentication with a password

	// Authentication Methods...
	authMethodSupported = true;							// Authentication Method Supported
	appliesToSupported = true;							// Applies To Supported
	namedAuthSupport = false;							// Are auth servers named?
	showAuthLevel = false;								// Show auth level

	// Local User Options...
	encryptionSupported = false;						// Show encryption
	readOnlySupported = false;							// Is read only supported?
	outboundACLSupported = false;						// Are outbound filtering ACL supported?
	privilegeLevelSupported = false;					// Are privilege levels supported?
	privilegeLevelText = i18n("Privilege Level");		// The table title privilege level text
	configDeviceSpecificLocalUsers = "";				// Text for the config report local user section.
	filterText = i18n("*ABBREV*ACL*-ABBREV*");			// The table filter column title text

	// TACACS Options...
	showTacacsGroupName = false;						// Show the TACACS group 
	showTacacsRetries = false;							// Show the TACACS retries
	configTacacsKey = i18n("*ABBREV*TACACS+*-ABBREV* encryption keys can be configured on *DEVICETYPE* devices with the following command:*CODE**COMMAND*tacacs-server key *CMDUSER*key*-CMDUSER**-COMMAND**-CODE*");							// The text and commands to configure a TACACS+ key

	// RADIUS Options...
	showRadiusGroupName = false;						// Show the RADIUS group
	configRadiusKey = i18n("*ABBREV*RADIUS*-ABBREV* encryption keys can be configured on *DEVICETYPE* devices with the following command:*CODE**COMMAND*radius-server *CMDOPTION*primary *CMDOR* secondary*-CMDOPTION* *CMDUSER*address*-CMDUSER* secret *CMDUSER*key*-CMDUSER**-COMMAND**-CODE*");							// The text and commands to configure a RADIUS key

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
	radiusRetransmit = 3;
	radiusTimeout = 10;
}


int CiscoCSSAuthentication::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	authConfig *authPointer = 0;
	authConfig *previousPointer = 0;
	tacacsServerConfig *tacacsPointer = 0;
	radiusServerConfig *radiusPointer = 0;
	int tempInt = 0;
	int errorCode = 0;
	bool found = false;

	// Virtual...
	if ((strcmp(command->part(0), "virtual") == 0) && (strcmp(command->part(1), "authentication") == 0) && (strcmp(command->part(3), "disallowed") != 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sVirtual Authentication Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if ((strcmp(command->part(1), "primary") == 0) && (authMethods != 0))
		{
			previousPointer = 0;
			authPointer = authMethods;
			while ((authPointer != 0) && (found == false))
			{
				if (authPointer->appliesTo.compare(i18n("Virtual")) == 0)
				{
					found = true;
					if (previousPointer == 0)
					{
						previousPointer = new (authConfig);
						previousPointer->next = authMethods;
						authPointer = previousPointer;
					}
					else
					{
						previousPointer->next = new (authConfig);
						previousPointer->next->next = authPointer;
						authPointer = previousPointer->next;
					}
				}
				else
				{
					previousPointer = authPointer;
					authPointer = authPointer->next;
				}
			}
		}
		else
		{
			authPointer = addMethod();
		}
		authPointer->appliesTo.assign(i18n("Virtual"));
		if (strcmp(command->part(2), "local") == 0)
			authPointer->method = localAuth;
		else if (strcmp(command->part(2), "tacacs") == 0)
			authPointer->method = tacacsAuth;
		else if (strcmp(command->part(2), "radius") == 0)
			authPointer->method = radiusAuth;
	}

	// Console...
	if ((strcmp(command->part(0), "console") == 0) && (strcmp(command->part(1), "authentication") == 0) && (strcmp(command->part(3), "disallowed") != 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sConsole Authentication Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if ((strcmp(command->part(1), "primary") == 0) && (authMethods != 0))
		{
			previousPointer = 0;
			authPointer = authMethods;
			while ((authPointer != 0) && (found == false))
			{
				if (authPointer->appliesTo.compare(i18n("Console")) == 0)
				{
					found = true;
					if (previousPointer == 0)
					{
						previousPointer = new (authConfig);
						previousPointer->next = authMethods;
						authPointer = previousPointer;
					}
					else
					{
						previousPointer->next = new (authConfig);
						previousPointer->next->next = authPointer;
						authPointer = previousPointer->next;
					}
				}
				else
				{
					previousPointer = authPointer;
					authPointer = authPointer->next;
				}
			}
		}
		else
		{
			authPointer = addMethod();
		}
		authPointer->appliesTo.assign(i18n("Console"));
		if (strcmp(command->part(2), "local") == 0)
			authPointer->method = localAuth;
		else if (strcmp(command->part(2), "tacacs") == 0)
			authPointer->method = tacacsAuth;
		else if (strcmp(command->part(2), "radius") == 0)
			authPointer->method = radiusAuth;
	}

	// tacacs-server...
	else if (strcmp(command->part(0), "tacacs-server") == 0)
	{

		if (strcmp(command->part(1), "key") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sTACACS+ Key Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			tacacsKey.assign(command->part(2));
			tacacsPointer = tacacsServer;
			while (tacacsPointer != 0)
			{
				if (tacacsPointer->key.empty())
					tacacsPointer->key.assign(tacacsKey);
				tacacsPointer = tacacsPointer->next;
			}
		}

		else if (strcmp(command->part(1), "timeout") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sTACACS+ Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			tacacsTimeout = atoi(command->part(2));
			tacacsPointer = tacacsServer;
			while (tacacsPointer != 0)
			{
				tacacsPointer->timeout = tacacsTimeout;
				tacacsPointer = tacacsPointer->next;
			}
		}

		else if ((strcmp(command->part(1), "account") != 0) && (strcmp(command->part(1), "authorize") != 0) && (strcmp(command->part(1), "frequency") != 0) && (strcmp(command->part(1), "send-full-command") != 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sTACACS+ Host Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			tacacsPointer = addTacacsServer();
			tacacsPointer->encryption = desEncryption;
			tacacsPointer->address.assign(command->part(1));
			tacacsPointer->port = atoi(command->part(2));
			tacacsPointer->description.assign(i18n("Backup"));
			tempInt = atoi(command->part(3));
			if ((tempInt != 0) || (strcmp(command->part(3), "0") == 0))
			{
				tacacsPointer->timeout = tempInt;
				tempInt = 4;
			}
			else
			{
				tacacsPointer->timeout = tacacsTimeout;
				tempInt = 3;
			}
			tacacsPointer->key.assign(tacacsKey);
			while (tempInt < command->parts)
			{
				if (strcmp(command->part(tempInt), "primary") == 0)
					tacacsPointer->description.assign(i18n("Primary"));
				else if (strcmp(command->part(tempInt), "frequency") == 0)
					tempInt++;
				else
					tacacsPointer->key.assign(command->part(tempInt));
				tempInt++;
			}
		}

		// NOT PROCESSED...
		else
			device->lineNotProcessed(line);
	}


	// radius-server...
	if (strcmp(command->part(0), "radius-server") == 0)
	{

		if (strcmp(command->part(1), "retransmit") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sRADIUS Retransmit Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			radiusRetransmit = atoi(command->part(2));
			radiusPointer = radiusServer;
			while (radiusPointer != 0)
			{
				radiusPointer->retries = radiusRetransmit;
				radiusPointer = radiusPointer->next;
			}
		}

		else if (strcmp(command->part(1), "timeout") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sRADIUS Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			radiusTimeout = atoi(command->part(2));
			radiusPointer = radiusServer;
			while (radiusPointer != 0)
			{
				radiusPointer->timeout = radiusTimeout;
				radiusPointer = radiusPointer->next;
			}
		}

		else if (strcmp(command->part(1), "primary") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sRADIUS Primary Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			radiusPointer = addRadiusServer();
			radiusPointer->timeout = radiusTimeout;
			radiusPointer->retries = radiusRetransmit;
			radiusPointer->description.assign(i18n("Primary"));
			radiusPointer->address.assign(command->part(2));
			radiusPointer->key.assign(command->part(4));
			if (command->parts == 7)
				radiusPointer->port = atoi(command->part(6));
		}

		else if (strcmp(command->part(1), "secondary") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sRADIUS Secondary Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			radiusPointer = addRadiusServer();
			radiusPointer->timeout = radiusTimeout;
			radiusPointer->retries = radiusRetransmit;
			radiusPointer->description.assign(i18n("Secondary"));
			radiusPointer->address.assign(command->part(2));
			radiusPointer->key.assign(command->part(4));
			if (command->parts == 7)
				radiusPointer->port = atoi(command->part(6));
		}

		// NOT PROCESSED...
		else
			device->lineNotProcessed(line);
	}


	// NOT PROCESSED...
	else
		device->lineNotProcessed(line);

	return errorCode;
}


int CiscoCSSAuthentication::processDefaults(Device *device)
{
	// Variables...
	authConfig *authPointer = 0;
	bool foundConsole = false;
	bool foundVirtual = false;

	authPointer = authMethods;
	while (authPointer != 0)
	{
		if (authPointer->appliesTo.compare(i18n("Virtual")) == 0)
			foundVirtual = true;
		else if (authPointer->appliesTo.compare(i18n("Console")) == 0)
			foundConsole = true;
		authPointer = authPointer->next;
	}

	if (foundConsole == false)
	{
		authPointer = addMethod();
		authPointer->appliesTo.assign(i18n("Console"));
		authPointer->method = localAuth;
	}

	if (foundVirtual == false)
	{
		authPointer = addMethod();
		authPointer->appliesTo.assign(i18n("Virtual"));
		authPointer->method = localAuth;
	}

	return 0;
}

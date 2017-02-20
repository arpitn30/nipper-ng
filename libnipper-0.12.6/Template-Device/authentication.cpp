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


<Device>Authentication::<Device>Authentication()
{
	// General...
	authenticationConfigIntro = i18n("This section describes the various *DEVICETYPE* device authentication settings.");		// Introduction text to the whole section
	loginAttemptsSupported = false;						// Login attempts supported
	loginAttempts = 0;									// Login attempts allowed (0 =  infinite)
	accessWithoutAuthentication = false;				// Set to true if access is allowed without authentication
	configAccessAuthentication = "";					// The text and commands to configure access authentication with a password

	// Authentication Methods...
	authMethodSupported = false;						// Authentication Method Supported
	appliesToSupported = false;							// Applies To Supported
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
	configTacacsKey = i18n("");							// The text and commands to configure a TACACS+ key

	// RADIUS Options...
	showRadiusGroupName = false;						// Show the RADIUS group
	configRadiusKey = i18n("");							// The text and commands to configure a RADIUS key

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
}


int <Device>Authentication::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
/*
	// NOT PROCESSED...
	else
		device->lineNotProcessed(line);

	return errorCode;*/
}


int <Device>Authentication::processDefaults(Device *device)
{
	return 0;
}

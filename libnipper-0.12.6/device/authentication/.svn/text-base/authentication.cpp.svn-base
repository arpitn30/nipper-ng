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
#include "../device.h"
#include "authentication.h"


Authentication::Authentication()
{
	localUser = 0;										// List of local users
	radiusServer = 0;									// Radius server list
	tacacsServer = 0;									// TACACS+ server list
	ldapServer = 0;										// LDAP server list
	securidServer = 0;									// RSA SecurID server list
	kerberosServer = 0;									// KERBEROS server list
	ntServer = 0;										// NT Server list
	authMethods = 0;									// Authentication Methods list
	// Check counters...
	emptyUserPassword = 0;
	dictionaryUserPassword = 0;
	weakUserPassword = 0;
	noTacacsKey = 0;
	dictionaryTacacsKey = 0;
	weakTacacsKey = 0;
	noRadiusKey = 0;
	dictionaryRadiusKey = 0;
	weakRadiusKey = 0;
	dictionaryLDAPPassword = 0;
	weakLDAPPassword = 0;

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


Authentication::~Authentication()
{
	// Variables...
	localUserConfig *localUserPointer = 0;
	tacacsServerConfig *tacacsPointer = 0;
	radiusServerConfig *radiusPointer = 0;
	kerberosServerConfig *kerberosPointer = 0;
	ldapServerConfig *ldapPointer = 0;
	securidServerConfig *securidPointer = 0;
	ntServerConfig *ntPointer = 0;
	authConfig *authPointer = 0;

	// Auth Methods...
	while (authMethods != 0)
	{
		authPointer = authMethods->next;
		delete authMethods;
		authMethods = authPointer;
	}

	// Delete local users
	while (localUser != 0)
	{
		localUserPointer = localUser->next;
		delete localUser;
		localUser = localUserPointer;
	}

	// Delete TACACS+
	while (tacacsServer != 0)
	{
		tacacsPointer = tacacsServer->next;
		delete tacacsServer;
		tacacsServer = tacacsPointer;
	}

	// Delete Radius
	while (radiusServer != 0)
	{
		radiusPointer = radiusServer->next;
		delete radiusServer;
		radiusServer = radiusPointer;
	}

	// Delete KERBEROS
	while (kerberosServer != 0)
	{
		kerberosPointer = kerberosServer->next;
		delete kerberosServer;
		kerberosServer = kerberosPointer;
	}

	// Delete LDAP
	while (ldapServer != 0)
	{
		ldapPointer = ldapServer->next;
		delete ldapServer;
		ldapServer = ldapPointer;
	}

	// Delete Securid
	while (securidServer != 0)
	{
		securidPointer = securidServer->next;
		delete securidServer;
		securidServer = securidPointer;
	}

	// Delete NT
	while (ntServer != 0)
	{
		ntPointer = ntServer->next;
		delete ntServer;
		ntServer = ntPointer;
	}
}



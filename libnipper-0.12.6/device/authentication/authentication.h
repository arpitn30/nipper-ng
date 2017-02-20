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

#ifndef deviceauthentication_H
#define deviceauthentication_H


#include "../common/deviceconfig.h"
#include "../device.h"
#include <string>

using namespace std;


class Authentication : public DeviceConfig
{
	public:

		Authentication();
		virtual ~Authentication();


	// -----------------------------------------------------------------------
	// Standard Device Class Methods...
	// -----------------------------------------------------------------------

		virtual int generateConfigReport(Device *device);
		virtual int generateSecurityReport(Device *device);
		virtual int generateUserSecurityReport(Device *device, int empty, int dictionary, int weak);
		virtual int generateTacacsSecurityReport(Device *device, int empty, int dictionary, int weak);
		virtual int generateRadiusSecurityReport(Device *device, int empty, int dictionary, int weak);
		virtual int generateLDAPSecurityReport(Device *device, int dictionary, int weak);


	// -----------------------------------------------------------------------
	// General Configuration...
	// -----------------------------------------------------------------------

		bool loginAttemptsSupported;				// Login attempts supported
		int loginAttempts;							// Login attempts allowed (0 =  infinite)
		const char *authenticationConfigIntro;		// Introduction text to the whole section
		bool accessWithoutAuthentication;			// Set to true if access is allowed without authentication
		const char *configAccessAuthentication;		// The text and commands to configure access authentication with a password


	// -----------------------------------------------------------------------
	// Authentication Ordering...
	// -----------------------------------------------------------------------

		enum authMethodEnum
		{
			localAuth = 0,
			radiusAuth = 1,
			tacacsAuth = 2,
			ldapAuth = 3,
			securidAuth = 4,
			kerberosAuth = 5,
			ntAuth = 6,
			noAuthRequired = 7,
			lineAuth = 8,
			enableAuth = 9,
			serverGroupAuth = 10
		};

		// Add these in the authentication method order!
		struct authConfig
		{
			string name;							// If auth servers are named
			authMethodEnum method;					// Authentication method (local, tacacs+...)
			string level;
			string appliesTo;
			struct authConfig *next;
		};

		authConfig *authMethods;

		// Authentication Methods...
		bool authMethodSupported;					// Authentication Method Supported
		bool appliesToSupported;					// Applies To Supported
		bool namedAuthSupport;						// Are auth servers named?
		bool showAuthLevel;							// Show auth level

		// Methods...
		authConfig *addMethod();
		int generateConfigGeneralReport(Device *device);


	// -----------------------------------------------------------------------
	// User Configuration...
	// -----------------------------------------------------------------------

		enum passwordEncryption
		{
			clearText = 0,
			md5Encryption = 1,
			aesEncryption = 2,
			cisco7Encryption = 3,
			netscreenEncryption = 4,
			md4Encryption = 5,
			ntEncryption = 6,
			desEncryption = 7
		};

		struct localUserConfig
		{
			string username;						// The username
			string password;						// The password (encrypted of unencrypted)
			passwordEncryption encryption;			// Is the password encrypted?
			bool readOnly;							// Is it read/only access?
			bool dictionaryPassword;
			Device::weakPasswordEnum weakPassword;
			string outboundACL;						// An outbound ACL for making use of the devices client utils
			bool aclSupported;
			string privilegeLevel;					// A privilege level for the user
			bool adminAccess;						// Set to true if administrative level user
			struct localUserConfig *next;
		};

		localUserConfig *localUser;					// List of local users

		localUserConfig *getUser(const char *username);


	protected:

		// Local User Options...
		bool encryptionSupported;					// Show encryption
		bool readOnlySupported;						// Is read only supported?
		bool outboundACLSupported;					// Are outbound filtering ACL supported?
		bool privilegeLevelSupported;				// Are privilege levels supported?
		const char *privilegeLevelText;				// The table title privilege level text
		const char *configDeviceSpecificLocalUsers;	// Text for the config report local user section.
		const char *filterText;						// The table filter column title text

		// Methods...
		int generateConfigLocalUserReport(Device *device);


	// -----------------------------------------------------------------------
	// TACACS+ Configuration...
	// -----------------------------------------------------------------------

		struct tacacsServerConfig
		{
			string groupName;						// If a name is used to group servers...
			string description;						// Primary / Backup...
			string address;							// The address
			int port;								// TACACS+ port
			string key;
			passwordEncryption encryption;
			int timeout;							// Timeout
			int retries;							// Retries
			// Key checks...
			bool dictionaryKey;
			Device::weakPasswordEnum weakKey;
			struct tacacsServerConfig *next;
		};

		tacacsServerConfig *tacacsServer;

		// TACACS Options...
		bool showTacacsGroupName;					// Show the TACACS group
		bool showTacacsRetries;						// Show the TACACS retries
		const char *configTacacsKey;				// The text and commands to configure a TACACS+ key

		// Methods...
		tacacsServerConfig *addTacacsServer();
		int generateConfigTacacsReport(Device *device);


	// -----------------------------------------------------------------------
	// RADIUS Configuration...
	// -----------------------------------------------------------------------

		struct radiusServerConfig
		{
			string groupName;						// If a name is used to group servers...
			string description;						// Primary / Backup...
			string address;							// The address
			int port;								// Radius port
			string key;								// Shared secret
			passwordEncryption encryption;
			int timeout;							// Timeout
			int retries;							// Retries
			// Key checks...
			bool dictionaryKey;
			Device::weakPasswordEnum weakKey;
			struct radiusServerConfig *next;
		};

		radiusServerConfig *radiusServer;

		// RADIUS Options...
		bool showRadiusGroupName;					// Show the RADIUS group
		const char *configRadiusKey;				// The text and commands to configure a RADIUS key

		// Methods...
		radiusServerConfig *addRadiusServer();
		int generateConfigRadiusReport(Device *device);


	// -----------------------------------------------------------------------
	// KERBEROS Configuration...
	// -----------------------------------------------------------------------

		struct kerberosServerConfig
		{
			string groupName;						// If a name is used to group servers...
			string description;						// Primary / Backup...
			string address;							// The address
			int port;								// port
			string realm;							// Kerberos Realm
			int timeout;							// Timeout
			int retries;							// Retries
			struct kerberosServerConfig *next;
		};

		kerberosServerConfig *kerberosServer;

		// KERBEROS Options...
		bool showKerberosGroupName;					// Show the KERBEROS group
		bool showKerberosTimeout;					// Show Kerberos timeout
		bool showKerberosRetries;					// Show Kerberos retries

		// Methods...
		kerberosServerConfig *addKerberosServer();
		int generateConfigKerberosReport(Device *device);


	// -----------------------------------------------------------------------
	// LDAP Configuration...
	// -----------------------------------------------------------------------

		struct ldapServerConfig
		{
			string groupName;						// If a name is used to group servers...
			string description;						// Primary / Backup...
			string address;							// The address
			int port;								// LDAP port
			string cn;								// CN
			string dn;								// DN
			string password;						// LDAP password
			passwordEncryption encryption;
			int timeout;							// Timeout
			int retries;							// Retries
			// Key checks...
			bool dictionaryPassword;
			Device::weakPasswordEnum weakPassword;
			struct ldapServerConfig *next;
		};

		ldapServerConfig *ldapServer;

		// LDAP Options...
		bool showLDAPGroupName;						// Show the LDAP group
		bool showLDAPPassword;						// Show LDAP password
		const char *configLDAPPassword;				// The text and commands to configure an LDAP server password

		// Methods...
		ldapServerConfig *addLDAPServer();
		int generateConfigLDAPReport(Device *device);


	// -----------------------------------------------------------------------
	// RSA SecurID Configuration...
	// -----------------------------------------------------------------------

		struct securidServerConfig
		{
			string groupName;						// If a name is used to group servers...
			string description;						// Primary / Backup...
			string address;							// The address
			int port;								// SecurID port
			string duress;							// Duress
			string encryption;						// Encryption
			int timeout;							// Timeout
			int retries;							// Retries
			struct securidServerConfig *next;
		};

		securidServerConfig *securidServer;

		// SecurID Options...
		bool showSecurIDGroupName;					// Show the SecurID group
		bool showSecurIDDuress;						// Show the SecurID Duress
		bool showSecurIDEncryption;					// Show the SecurID Encryption

		// Methods...
		securidServerConfig *addSecurIDServer();
		int generateConfigSecurIDReport(Device *device);


	// -----------------------------------------------------------------------
	// NT Configuration...
	// -----------------------------------------------------------------------

		struct ntServerConfig
		{
			string groupName;						// If a name is used to group servers...
			string description;						// 
			string pdc;								// NT PDC...
			string address;							// The address
			int timeout;							// Timeout
			struct ntServerConfig *next;
		};

		ntServerConfig *ntServer;

		// NT Options...
		bool showNTGroupName;						// Show the NT group

		// Methods...
		ntServerConfig *addNTServer();
		int generateConfigNTReport(Device *device);


	private:
		// Check counters...
		int emptyUserPassword;
		int dictionaryUserPassword;
		int weakUserPassword;
		int dictionaryTacacsKey;
		int noTacacsKey;
		int weakTacacsKey;
		int noRadiusKey;
		int dictionaryRadiusKey;
		int weakRadiusKey;
		int dictionaryLDAPPassword;
		int weakLDAPPassword;
};


#endif

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
 *      2. Any code that makes use of this library MUST display the        *
 *         returned text of the Nipper::getVersion() method. Since the     *
 *         text returned includes the version details and copyright of     *
 *         the library, the sugested place to show it would be with the    *
 *         callers "about program" information.                            *
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

#ifndef iosdeviceadministration_H
#define iosdeviceadministration_H

#include "../device/administration/administration.h"


class IOSAdministration : public Administration
{
	public:
		IOSAdministration();

		// Device specific methods...
		int generateSecuritySpecificReport(Device *device);
		int processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize);
		int processDefaults(Device *device);
		int generateDeviceTelnetConfig(Device *device);		// A device specific config report output
		int generateDeviceSSHConfig(Device *device);			// A device specific config report output


	// -----------------------------------------------------------------------
	// Misc Device Specific Support...
	// -----------------------------------------------------------------------

		virtual int generateDeviceHTTPConfig(Device *device);		// A device specific config report output
		virtual int generateDeviceSpecificConfig(Device *device);

		bool telnetLoginAllowed;	// Are people allowed to login
		bool configIncludesSSH;		// Set to true if in the lines mention SSH or there is an ssh line
		bool httpConfigured;		// Has http-server been configured already?
		int sshRetries;				// The SSH login retries
		int sshNegTimeout;			// The SSH negotiation timeout
		bool rloginEnabled;			// Is the Rlogin service enabled?
		string httpAcl;				// The HTTP server ACL

		bool aaaUsed;				// If aaa is used, it overrides the line configuration...
		

	// -----------------------------------------------------------------------
	// Lines Support...
	// -----------------------------------------------------------------------

		enum lineType
		{
			lineConsole = 0,
			lineVTY = 1,
			lineAUX = 2,
			lineTTY = 3
		};

		enum loginType
		{
			loginWithNoPassword = 0,			// Oh no (doesn't apply to VTY - they need a password)
			loginLinePassword = 1,				// The Line password (ouch)
			loginLocal = 2,						// Local Security Database (i.e. username)
			loginTACACS = 3,					// TACACS-style
			loginAuthentication = 4				// AAA (recommended)
		};

		struct lineConfig
		{
			// Basics...
			enum lineType type;				// line_console...
			int lineStart;					// i.e. VTY - 0
			int lineEnd;					// i.e. VTY - 4
			// Security...
			enum loginType login;			//
			bool exec;						// true (default) or false
			int privilege;					// The privilege level for the line (0..15)
			bool callback;					// true or false (default)
			string password;				// A Line password (if configured)
			bool encryption;				// true or false for the password
			bool passwordInDict;			// Is it a dictionary-based password
			Device::weakPasswordEnum passwordWeak;		// Is it a weak password
			string aclIn;
			string aclOut;
			// AAA...
			bool accounting;
			string accList;
			bool authorization;
			string authList;
			// Access Services...
			bool output;					// Output allowed
			bool defaultSettings;			// true if no transport line has been set
			bool ssh;						// true, false
			bool telnet;					// true, false
			bool rlogin;					// true, false
			bool all;						// true, false
			// Timeouts...
			int execTimeout;				// Exec timeout in seconds, 0 = no timeout (default)
			int absoluteTimeout;
			int sessionTimeout;
			int loginTimeout;
			struct lineConfig *next;
		};

		lineConfig *line;

		lineConfig *addLine();				// Add a new line...
};


#endif

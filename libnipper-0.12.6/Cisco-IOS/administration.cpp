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

// Includes...
#include <cstdlib>
#include <cstring>

#include "../globaldefs.h"
#include "iosdevice.h"
#include "general.h"
#include "administration.h"
#include "authentication.h"
#include "../device/common/configline.h"

IOSAdministration::IOSAdministration()
{
	// Device specific options...
	rloginEnabled = false;
	httpConfigured = false;					// Has http-server been configured already?
	configIncludesSSH = false;				// Set to true if in the lines mention SSH or there is an ssh line
	cdpSupported = true;					// Is CDP supported (globally, see interfaces for per interface activation)
	cdpEnabled = true;						// Is CDP enabled
	cdpVersionSupported = false;			// Is CDP version supported
	cdpVersion = 2;							// CDP version

	// General...
	generalSettings = true;					// Show the general settings section?

	// Telnet...
	telnetSupported = true;					// Is telnet supported?
	disableTelnet = i18n("Telnet must be disabled on *DEVICETYPE* devices for each line that the service is enabled. If supported, the *ABBREV*SSH*-ABBREV* protocol can also be enabled using the same command. This can be done using the following command:*CODE**COMMAND*transport input *CMDOPTION*none *CMDOR* ssh*-CMDOPTION**-COMMAND**-CODE*");			// How to disable telnet text...

	// Device specific options...
	sshSupported = false;					// Does this device support SSH?
	ssh2Supported = false;					// Does the device support SSH version 2?
	sshUpgrade = true;						// Do you have to upgrade?
	ssh2upgrade = true;
	sshRetries = 3;							// The SSH login retries
	sshNegTimeout = 120;					// The SSH negotiation timeout
	configSSHSupport = i18n("The *ABBREV*SSH*-ABBREV* service can be configured on each line with the following command:*CODE**COMMAND*transport input ssh*-COMMAND**-CODE*");			// How to configure SSH...
	configSSHv2Support = i18n("When *ABBREV*SSH*-ABBREV* protocol version 2 support is configured on *DEVICETYPE* devices, support for version 1 will be disabled. This can be configured with the following command:*CODE**COMMAND*ip ssh version 2*-COMMAND**-CODE*");			// How to configure protocol version 2 support only
	sshConfigProtocolSupport = i18n("*DEVICETYPE* devices support both *ABBREV*SSH*-ABBREV* protocol versions 1 and 2. Support for *ABBREV*SSH*-ABBREV* was introduced in *ABBREV*IOS*-ABBREV* version 12.0(5) and support for *ABBREV*SSH*-ABBREV* protocol version 2 was added from *ABBREV*IOS*-ABBREV* version 12.3(2). *ABBREV*IOS*-ABBREV* devices that support both versions of the *ABBREV*SSH*-ABBREV* protocol default to allowing connections from clients using either version.");

	// HTTP(S) options...
	httpSupported = false;					// Does this device support HTTP
	httpsSupported = false;					// Does this device support HTTPS
	httpsUpgrade = false;					// Do you have to upgrade for HTTPS?
	httpEnabled = false;					// Is the HTTP service enabled?
	httpPort = 80;							// HTTP port
	httpsEnabled = false;					// Is the HTTPS service enabled?
	httpsPort = 443;						// HTTPS port
	httpSpecificTimeout = true;				// A HTTP Specific Timeout?
	httpTimeout = 180;						// The HTTP Timeout (secs)
	configHTTPTimeout = i18n("The *ABBREV*HTTP*-ABBREV* server timeout can be configured with the following command:*CODE**COMMAND*ip http timeout-policy idle *CMDUSER*seconds*-CMDUSER* life *CMDUSER*seconds*-CMDUSER* requests *CMDUSER*number*-CMDUSER**-COMMAND**-CODE*");			// The text and commands to configure the timeout
	httpLabel = i18n("*ABBREV*HTTP*-ABBREV*");		// The label given to the HTTP service (e.g. HTTP)
	httpsLabel = i18n("*ABBREV*HTTPS*-ABBREV*");	// The label given to the HTTPS service (e.g. HTTPS)
	httpSpecificHost = true;				// Does HTTP have its own access list?
	httpHostsRequired = false;				// Is the host configuration required?
	showHTTPHostInterface = false;			// Show the Interface column in the host table?
	showHTTPHostAccess = false;				// Show the Access column in the host table?
	configHTTPHostAccess = i18n("Management hosts can be configured by applying an *ABBREV*ACL*-ABBREV*. An *ABBREV*ACL*-ABBREV* can be configured and applied using the following commands:*CODE**COMMAND*ip access-list standard *CMDUSER*access-list-number*-CMDUSER**-COMMAND**COMMAND*remark *CMDUSER*description*-CMDUSER**-COMMAND**COMMAND*permit *CMDUSER*ip-address*-CMDUSER* *CMDUSER*wildcard*-CMDUSER* *CMDOPTION*log*-CMDOPTION**-COMMAND**COMMAND*ip http access-class *CMDUSER*acl-number*-CMDUSER**-COMMAND**-CODE*");		// How to configure HTTP Management hosts...
	disableHTTP = i18n("The *ABBREV*HTTP*-ABBREV* server can be disabled using the following command:*CODE**COMMAND*no ip http server*-COMMAND**-CODE*");					// How to disable HTTP text...
	configHTTPSSupport = i18n("The *ABBREV*HTTPS*-ABBREV* server can be enabled using the following command:*CODE**COMMAND*ip http secure-server*-COMMAND**-CODE*");			// How to configure HTTPS...
	cipherConfigSupported = true;			// Can the Ciphers be configured?
	configCipherText = i18n("The most secure cipher suite supported by *DEVICETYPE* devices can be configured with the following command:*CODE**COMMAND*ip http secure-ciphersuite 3des-ede-cbc-sha*-COMMAND**-CODE*");			// The text to configure a strong cipher.

	// BOOTP Support...
	bootPServerSupported = false;			// Is BOOTP supported?
	bootPEnabled = true;					// Is BOOTP enabled?
	configDisableBootP = i18n("The *ABBREV*BOOTP*-ABBREV* service can be disabled with the following command:*CODE**COMMAND*no ip bootp server*-COMMAND**-CODE*");			// Config report text to disable bootp

	// Finger Support...
	fingerServiceSupported = true;			// Is the finger service supported?
	fingerServiceEnabled = false;			// Is the finger service enabled?
	configDisableFinger = i18n("");			// Config report text to disable finger

	// Device specific inits...
	line = 0;


	aaaUsed = false;				// If aaa is used, it overrides the line configuration...
}


int IOSAdministration::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	lineConfig *linePointer = 0;
	cipherConfig *cipherPointer = 0;
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

	// IP
	if (strcmp(command->part(tempInt), "ip") == 0)
	{
		tempInt++;

		// HTTP...
		if (strcmp(command->part(tempInt), "http") == 0)
		{
			tempInt++;
			httpSupported = true;

			// Server...
			if (strcmp(command->part(tempInt), "server") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sHTTP Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				httpConfigured = true;
				httpEnabled = setting;
			}

			// Server port...
			else if (strcmp(command->part(tempInt), "port") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sHTTP Server Port Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (setting == false)
					httpPort = 80;
				else
					httpPort = atoi(command->part(tempInt + 1));
			}

			// Server ACL...
			else if (strcmp(command->part(tempInt), "access-class") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sHTTP ACL Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				httpSpecificHost = false;
				httpAcl.assign(command->part(tempInt + 1));
			}

			// sercure Server...
			else if (strcmp(command->part(tempInt), "secure-server") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sHTTPS Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				httpsSupported = true;
				httpsEnabled = setting;
			}

			// sercure Server port...
			else if (strcmp(command->part(tempInt), "secure-port") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sHTTPS Server Port Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				httpsSupported = true;
				if (setting == false)
					httpsPort = 443;
				else
					httpsPort = atoi(command->part(tempInt + 1));
			}

			// sercure Server ciphers...
			else if (strcmp(command->part(tempInt), "secure-ciphersuite") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sHTTPS Server Ciphers Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				httpsSupported = true;
				if (setting != false)
				{
					tempInt += 2;
					while (tempInt < command->parts)
					{
						if (strcmp(command->part(tempInt), "3des-ede-cbc-sha") == 0)
						{
							cipherPointer = addCipher();
							cipherPointer->encryption.assign("*ABBREV*3DES*-ABBREV*");
							cipherPointer->authenticaton.assign("*ABBREV*SHA1*-ABBREV*");
							cipherPointer->bits = 168;
							cipherPointer->ssl3 = true;
						}

						else if (strcmp(command->part(tempInt), "rc4-128-sha") == 0)
						{
							cipherPointer = addCipher();
							cipherPointer->encryption.assign("*ABBREV*RC4*-ABBREV*");
							cipherPointer->authenticaton.assign("*ABBREV*SHA1*-ABBREV*");
							cipherPointer->bits = 128;
							cipherPointer->ssl3 = true;
						}

						else if (strcmp(command->part(tempInt), "rc4-128-md5") == 0)
						{
							cipherPointer = addCipher();
							cipherPointer->encryption.assign("*ABBREV*RC4*-ABBREV*");
							cipherPointer->authenticaton.assign("*ABBREV*MD5*-ABBREV*");
							cipherPointer->bits = 128;
							cipherPointer->ssl3 = true;
						}

						else if (strcmp(command->part(tempInt), "des-cbc-sha") == 0)
						{
							cipherPointer = addCipher();
							cipherPointer->encryption.assign("*ABBREV*DES*-ABBREV*");
							cipherPointer->authenticaton.assign("*ABBREV*SHA1*-ABBREV*");
							cipherPointer->bits = 56;
							cipherPointer->ssl3 = true;
						}
						tempInt++;
					}
				}
			}

			// NOT PROCESSED...
			else
				device->lineNotProcessed(line);
		}

		// SSH...
		else if (strcmp(command->part(tempInt), "ssh") == 0)
		{
			tempInt++;
			sshSupported = true;

			// Version...
			if (strcmp(command->part(tempInt), "version") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sSSH Version Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				ssh2Supported = true;
				if (setting == false)
					sshVersion = 0;
				else if (strcmp(command->part(tempInt + 1), "1") == 0)
					sshVersion = 1;
				else
					sshVersion = 2;
			}

			// Port...
			else if (strcmp(command->part(tempInt), "port") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sSSH Port Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (setting == false)
					sshPort = 22;
				else
					sshPort = atoi(command->part(tempInt + 1));
			}

			// auth retries...
			else if (strcmp(command->part(tempInt), "authentication-retries") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sSSH Auth Retry Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (setting == false)
					sshRetries = 3;
				else
					sshRetries = atoi(command->part(tempInt + 1));
			}

			// negotiation timeout...
			else if (strcmp(command->part(tempInt), "timeout") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sSSH Neg timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (setting == false)
					sshNegTimeout = 120;
				else
					sshNegTimeout = atoi(command->part(tempInt + 1));
			}

			// NOT PROCESSED...
			else
				device->lineNotProcessed(line);
		}


		// BootP...
		else if ((strcmp(command->part(tempInt), "bootp") == 0) && (strcmp(command->part(tempInt + 1), "server") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sBOOTP Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			bootPEnabled = setting;
			bootPServerSupported = true;
		}

		// Finger...
		else if (strcmp(command->part(tempInt), "finger") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sFinger Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			fingerServiceEnabled = setting;
			fingerServiceSupported = true;
		}

		// NOT PROCESSED...
		else
			device->lineNotProcessed(line);
	}

	// CDP
	else if ((strcmp(command->part(tempInt), "cdp") == 0) && (strcmp(command->part(tempInt + 1), "run") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sCDP Run Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		cdpEnabled = setting;
	}

	// Service...
	else if (strcmp(command->part(tempInt), "service") == 0)
	{
		tempInt++;

		if (strcmp(command->part(tempInt), "finger") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sFinger Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			fingerServiceEnabled = setting;
			fingerServiceSupported = true;
		}

		// NOT PROCESSED...
		else
			device->lineNotProcessed(line);
	}


	// Lines...
	else if (strcmp(command->part(tempInt), "line") == 0)
	{
		while ((strcmp(command->part(0), "!") != 0) && (feof(device->inputFile) == 0))
		{

			// New line...
			if (strcmp(command->part(tempInt), "line") == 0)
			{
				tempInt++;
				if (device->config->reportFormat == Config::Debug)
					printf("%sLine Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				linePointer = addLine();

				if ((strcmp(command->part(tempInt), "con") == 0) || (strcmp(command->part(tempInt), "concole") == 0))
				{
					linePointer->type = lineConsole;
					linePointer->defaultSettings = false;
					linePointer->ssh = false;
					linePointer->telnet = false;
					linePointer->rlogin = false;
					linePointer->all = false;
				}
				else if ((strcmp(command->part(tempInt), "aux") == 0) || (strcmp(command->part(tempInt), "auxiliary") == 0))
				{
					linePointer->type = lineAUX;
					linePointer->defaultSettings = false;
					linePointer->ssh = false;
					linePointer->telnet = false;
					linePointer->rlogin = false;
					linePointer->all = false;
				}
				else if (strcmp(command->part(tempInt), "tty") == 0)
					linePointer->type = lineTTY;
				else
					linePointer->type = lineVTY;
				tempInt++;

				linePointer->lineStart = atoi(command->part(tempInt));
				tempInt++;
				linePointer->lineEnd = atoi(command->part(tempInt));
			}

			// Exec...
			else if ((strcmp(command->part(tempInt), "exec") == 0) && (linePointer != 0))
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sLine Exec Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				linePointer->exec = setting;
			}

			// Login Timeout
			else if ((strcmp(command->part(tempInt), "login") == 0) && (strcmp(command->part(tempInt + 1), "timeout") == 0) && (strcmp(command->part(tempInt + 2), "response") == 0))
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sLine Session Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				tempInt += 3;
				linePointer->loginTimeout = atoi(command->part(tempInt));
			}

			// Login...
			else if ((strcmp(command->part(tempInt), "login") == 0) && (linePointer != 0))
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sLine Login Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				tempInt++;

				if (setting == false)
					linePointer->login = loginWithNoPassword;
				else if (command->parts == tempInt)
					linePointer->login = loginLinePassword;
				else if (strcmp(command->part(tempInt), "local") == 0)
					linePointer->login = loginLocal;
				else if (strcmp(command->part(tempInt), "authentication") == 0)
					linePointer->login = loginAuthentication;
				else if (strcmp(command->part(tempInt), "tacacs") == 0)
					linePointer->login = loginTACACS;
			}

			// Password
			else if (strcmp(command->part(tempInt), "password") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sLine Password Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				tempInt++;

				if (setting == false)
					linePointer->password.erase();
				else
				{
					// If just password...
					if (tempInt + 1 == command->parts)
						linePointer->password.assign(command->part(tempInt));
					else if (strcmp(command->part(tempInt), "0") == 0)
					{
						tempInt++;
						linePointer->password.assign(command->part(tempInt));
					}
					else if (strcmp(command->part(tempInt), "7") == 0)
					{
						tempInt++;
						linePointer->password.assign(device->ciscoType7Decode(command->part(tempInt)));
					}
					else
					{
						tempInt++;
						linePointer->encryption = true;
						linePointer->password.assign(command->part(tempInt));
					}
				}
			}

			// Access-Class In
			else if ((strcmp(command->part(tempInt), "access-class") == 0) && (strcmp(command->part(tempInt + 2), "in") == 0))
			{
				tempInt++;
				if (device->config->reportFormat == Config::Debug)
					printf("%sLine Access Class In Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				linePointer->aclIn.assign(command->part(tempInt));
			}

			// Access-Class Out
			else if ((strcmp(command->part(tempInt), "access-class") == 0) && (strcmp(command->part(tempInt + 2), "out") == 0))
			{
				tempInt++;
				if (device->config->reportFormat == Config::Debug)
					printf("%sLine Access Class Out Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				linePointer->aclOut.assign(command->part(tempInt));
			}

			// Callback
			else if (strcmp(command->part(tempInt), "callback") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sLine Call Back Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				linePointer->callback = setting;
			}

			// Transport Input...
			else if ((strcmp(command->part(tempInt), "transport") == 0) && (strcmp(command->part(tempInt + 1), "input") == 0))
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sLine Transport Input Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				linePointer->defaultSettings = false;
				tempInt += 2;
				if (strcmp(command->part(tempInt), "none") == 0)
				{
					linePointer->ssh = false;
					linePointer->telnet = false;
					linePointer->rlogin = false;
					linePointer->all = false;
				}
				else if (strcmp(command->part(tempInt), "all") == 0)
				{
					linePointer->ssh = true;
					linePointer->telnet = true;
					linePointer->rlogin = true;
					linePointer->all = true;
				}
				else
				{
					linePointer->ssh = false;
					linePointer->telnet = false;
					linePointer->rlogin = false;
					linePointer->all = false;
					while (tempInt < command->parts)
					{
						if (strcmp(command->part(tempInt), "ssh") == 0)
						{
							linePointer->ssh = true;
							configIncludesSSH = true;
							sshSupported = true;
						}
						else if (strcmp(command->part(tempInt), "telnet") == 0)
							linePointer->telnet = true;
						else if (strcmp(command->part(tempInt), "rlogin") == 0)
							linePointer->rlogin = true;
						tempInt++;
					}
				}
			}

			// Transport Output...
			else if ((strcmp(command->part(tempInt), "transport") == 0) && (strcmp(command->part(tempInt + 1), "output") == 0))
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sLine Transport Output Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				if (strcmp(command->part(tempInt + 2), "none") == 0)
					linePointer->output = false;
				else
					linePointer->output = true;
			}

			// Privilege Level...
			else if ((strcmp(command->part(tempInt), "privilege") == 0) && (strcmp(command->part(tempInt + 1), "level") == 0))
			{
				tempInt += 2;
				if (device->config->reportFormat == Config::Debug)
					printf("%sLine Privilege Level Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				if (setting != false)
					linePointer->privilege = atoi(command->part(tempInt));
			}

			// AAA - Accounting
			else if (strcmp(command->part(tempInt), "accounting") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sLine Accounting Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				tempInt++;
				linePointer->accounting = true;
				if (strcmp(command->part(tempInt), "commands") == 0)
					tempInt++;
				tempInt++;
				linePointer->accList.assign(command->part(tempInt));
			}

			// AAA - Authorization
			else if (strcmp(command->part(tempInt), "authorization") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sLine Authorization Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				tempInt++;
				linePointer->authorization = true;
				if (strcmp(command->part(tempInt), "commands") == 0)
					tempInt++;
				tempInt++;
				linePointer->authList.assign(command->part(tempInt));
			}

			// Exec Timeout
			else if (strcmp(command->part(tempInt), "exec-timeout") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sLine Exec Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				tempInt++;
				linePointer->execTimeout = atoi(command->part(tempInt)) * 60;
				tempInt++;
				if (tempInt < command->parts)
					linePointer->execTimeout = linePointer->execTimeout + atoi(command->part(tempInt));
			}

			// Absolute Timeout
			else if (strcmp(command->part(tempInt), "absolute-timeout") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sLine Absolute Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				tempInt++;
				linePointer->absoluteTimeout = atoi(command->part(tempInt)) * 60;
			}

			// Session Timeout
			else if (strcmp(command->part(tempInt), "session-timeout") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sLine Session Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				tempInt++;
				linePointer->sessionTimeout = atoi(command->part(tempInt)) * 60;
			}

			// NOT PROCESSED...
			else
				device->lineNotProcessed(line);

			// Read a line from the config...
			device->readLine(line, lineSize);
	
			// Split it up into parts...
			command->setConfigLine(line);

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
		}
	}

	// NOT PROCESSED...
	else
		device->lineNotProcessed(line);

	return errorCode;
}


int IOSAdministration::processDefaults(Device *device)
{
	// Variables...
	Authentication::localUserConfig *localPointer = 0;
	lineConfig *linePointer = 0;
	cipherConfig *cipherPointer = 0;
	string tempString;

	// Disable services by default...
	telnetEnabled = false;
	sshEnabled = false;
	rloginEnabled = false;

	// Sort out CDP verison...
	if (device->general != 0)
	{
		if (device->general->versionMajor < 12)
			cdpVersion = 1;
	}

	// Is this an IOS version that is LIKELY to have SSH?
	if (device->general != 0)
	{
		if (device->general->versionMajor == 0)
		{ }
		else if ((device->general->versionMajor > 12) || ((device->general->versionMajor == 12) && (device->general->versionMinor > 0)) || ((device->general->versionMajor == 12) && (device->general->versionMinor == 0) && (device->general->versionRevision > 0)))
		{
			configIncludesSSH = true;
			sshSupported = true;
			if ((device->general->versionMajor > 12) || ((device->general->versionMajor == 12) && ((device->general->versionMinor > 3) || ((device->general->versionMinor == 3) && (device->general->versionRevision > 1)))))
				ssh2Supported = true;
		}
	}

	// BootP
	if ((device->general != 0) && (bootPServerSupported == false))
	{
		if (device->general->versionMajor == 0)
		{ }
		else if ((device->general->versionMajor > 11) || ((device->general->versionMajor == 11) && (device->general->versionMinor > 1)))
			bootPServerSupported = true;
	}

	// Finger
	if ((device->general != 0) && (fingerServiceSupported == false))
	{
		if (device->general->versionMajor == 0)
		{ }
		else if ((device->general->versionMajor > 12) || ((device->general->versionMajor == 12) && (device->general->versionMinor > 1)) || ((device->general->versionMajor == 12) && (device->general->versionMinor == 1) && (device->general->versionRevision > 4)))
		{
			fingerServiceSupported = true;
			fingerServiceEnabled = false;
		}
		else if ((device->general->versionMajor > 11) || ((device->general->versionMajor == 11) && (device->general->versionMinor > 2)))
		{
			fingerServiceSupported = true;
			fingerServiceEnabled = true;
		}
	}

	// Is this an IOS version that is LIKELY to have HTTP(S)?
	if (device->general != 0)
	{
		if (device->general->versionMajor == 0)
		{ }
		else if ((device->general->versionMajor > 11) || ((device->general->versionMajor == 11) && (device->general->versionMinor > 1)))
		{
			httpSupported = true;
			httpsUpgrade = true;
			if (httpConfigured == false)
				httpEnabled = true;
			if ((device->general->versionMajor > 12) || ((device->general->versionMajor == 12) && ((device->general->versionMinor > 3) || ((device->general->versionMinor == 3) && (device->general->versionRevision > 14)))))
				httpsSupported = true;
		}
	}

	// HTTPS ciphers...
	if (httpsSupported == true)
	{
		cipherPointer = addCipher();
		cipherPointer->encryption.assign("*ABBREV*3DES*-ABBREV*");
		cipherPointer->authenticaton.assign("*ABBREV*SHA1*-ABBREV*");
		cipherPointer->bits = 168;
		cipherPointer->ssl3 = true;
		cipherPointer = addCipher();
		cipherPointer->encryption.assign("*ABBREV*RC4*-ABBREV*");
		cipherPointer->authenticaton.assign("*ABBREV*SHA1*-ABBREV*");
		cipherPointer->bits = 128;
		cipherPointer->ssl3 = true;
		cipherPointer = addCipher();
		cipherPointer->encryption.assign("*ABBREV*RC4*-ABBREV*");
		cipherPointer->authenticaton.assign("*ABBREV*MD5*-ABBREV*");
		cipherPointer->bits = 128;
		cipherPointer->ssl3 = true;
		cipherPointer = addCipher();
		cipherPointer->encryption.assign("*ABBREV*DES*-ABBREV*");
		cipherPointer->authenticaton.assign("*ABBREV*SHA1*-ABBREV*");
		cipherPointer->bits = 56;
		cipherPointer->ssl3 = true;
	}

	// Fixup the line and service defaults...
	linePointer = line;
	while (linePointer != 0)
	{

		// If AAA is used, the login must be handled by AAA
		if (aaaUsed == true)
			linePointer->login = loginAuthentication;

		// Add line password to local authentication list...
		if (!linePointer->password.empty())
		{
			switch (linePointer->type)
			{
				case lineConsole:
					tempString.assign(i18n("Console Line"));
					break;
				case lineVTY:
					tempString.assign(i18n("*ABBREV*VTY*-ABBREV* "));
					tempString.append(device->intToString(linePointer->lineStart));
					if (linePointer->lineEnd != 0)
					{
						tempString.append(" - ");
						tempString.append(device->intToString(linePointer->lineEnd));
					}
					tempString.append(i18n(" Line"));
					break;
				case lineAUX:
					tempString.assign(i18n("Auxillary"));
					break;
				default:
					tempString.assign(i18n("*ABBREV*TTY*-ABBREV* "));
					tempString.append(device->intToString(linePointer->lineStart));
					if (linePointer->lineEnd != 0)
					{
						tempString.append(" - ");
						tempString.append(device->intToString(linePointer->lineEnd));	
					}
					tempString.append(i18n(" Line"));
					break;
			}

			localPointer = device->authentication->getUser(tempString.c_str());
			if (linePointer->privilege == 15)
				localPointer->adminAccess = true;
			tempString.assign(device->intToString(linePointer->privilege));
			localPointer->privilegeLevel.assign(tempString);
			localPointer->aclSupported = true;
			localPointer->outboundACL.assign(linePointer->aclOut);
			localPointer->password.assign(linePointer->password);
			if (linePointer->encryption == true)
				localPointer->encryption = Authentication::md5Encryption;
			else
				localPointer->encryption = Authentication::clearText;
		}

		// If default...
		if (linePointer->defaultSettings == true)
		{
			if ((device->general->versionMajor < 11) || ((device->general->versionMajor == 11) && (device->general->versionMinor == 0)))
			{
				linePointer->telnet = true;
				linePointer->rlogin = true;
				linePointer->all = true;
			}
			else
			{
				linePointer->telnet = true;
				linePointer->rlogin = true;
				linePointer->all = false;
			}
		}

		// If not a router, terminate the rlogon...
		if (device->isRouter == false)
			linePointer->rlogin = false;

		// If Nipper THINKS that SSH is not available...
		if (configIncludesSSH == false)
			linePointer->ssh = false;

		// Telnet...
		if ((linePointer->telnet == true) && (linePointer->exec == true))
			telnetEnabled = true;
		if ((linePointer->telnet == true) && (linePointer->exec == true) && !((linePointer->password.empty()) && (linePointer->login == loginLinePassword)))
			telnetLoginAllowed = true;

		// SSH...
		if ((linePointer->ssh == true) && (linePointer->exec == true) && !((linePointer->password.empty()) && (linePointer->login == loginLinePassword)))
			sshEnabled = true;

		// Rlogin...
		if (linePointer->rlogin == true)
			rloginEnabled = true;

		linePointer = linePointer->next;
	}

	return 0;
}


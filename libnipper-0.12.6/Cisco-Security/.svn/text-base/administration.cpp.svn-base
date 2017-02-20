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
#include <cstdlib>
#include <cstring>

#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "device.h"
#include "administration.h"


CiscoSecAdministration::CiscoSecAdministration()
{
	sslCiphers = 0;
	sslProtocolVersion.assign("any");


	// -----------------------------------------------------------------------
	// Device Specific Settings...
	// -----------------------------------------------------------------------

	// General...
	generalSettings = true;					// Show the general settings section?
	consoleEnabled = true;					// Is the Console port enabled?
	consoleSupported = true;				// Is a console port supported?
	consoleTimeoutSupported = true;			// Is a console timeout supported?
	consoleTimeout = 0;						// Console timeout
	configConsoleTimeout = i18n("The console timeout can be configured with the following command:*CODE**COMMAND*console timeout *CMDUSER*timeout-minutes*-CMDUSER**-COMMAND**-CODE*");		// The text and commands to configure the timeout

	// Host restrictions...
	serviceWideHosts = false;				// Do all the admin services share a common host restrictions?
	serviceConfigHosts = i18n("");			// Text, how to configure administrative host restrictions.

	// Telnet options...
	telnetSupported = true;					// Is telnet supported?
	telnetEnabled = false;					// Is Telnet enabled?
	telnetPort = 23;						// The telnet service port
	telnetSpecificHost = true;				// Does Telnet have its own access list?
	telnetHostsRequired = true;				// Is the host configuration required?
	showTelnetHostInterface = true;			// Show the Interface column in the host table?
	configTelnetHostAccess = i18n("Telnet management hosts can be configured with the following command:*CODE**COMMAND*telnet *CMDREQUIRE**CMDUSER*hostname*-CMDUSER* *CMROR* *CMDUSER*ip-address*-CMDUSER* *CMDUSER*interface*-CMDUSER**-CMDREQUIRE**-COMMAND**-CODE*");		// How access lists are configured for the telnet service
	disableTelnet = i18n("Telnet access to *DEVICENAME* can be disabled by removing access from all the configured management hosts. This can be done with the following command:*CODE**COMMAND*no telnet *CMDREQUIRE**CMDUSER*hostname*-CMDUSER* *CMROR* *CMDUSER*ip-address*-CMDUSER* *CMDUSER*interface*-CMDUSER**-CMDREQUIRE**-COMMAND**-CODE*");				// How to disable telnet text...
	telnetSpecificTimeout = true;			// A Telnet Specific Timeout?
	telnetTimeout = 300;					// The Telnet Timeout (secs)
	configTelnetTimeout = i18n("Telnet connection timeouts can be configured with the following command:*CODE**COMMAND*telnet timeout *CMDUSER*timeout-minutes*-CMDUSER**-COMMAND**-CODE*");			// The text and commands to configure the timeout

	// SSH options...
	sshPort = 22;							// The SSH port number
	configSSHSupport = i18n("*ABBREV*SSH*-ABBREV* is enabled on *DEVICETYPE* devices by adding management hosts. This can be done with the following command:*CODE**COMMAND*ssh *CMDUSER*ip-address*-CMDUSER* *CMDUSER*netmask*-CMDUSER* *CMDUSER*interface*-CMDUSER**-COMMAND**-CODE*");			// How to configure SSH...
	sshSpecificHost = true;					// Does SSH have its own access list?
	sshHostsRequired = true;				// Is the host configuration required?
	showSSHHostInterface = true;			// Show the Interface column in the host table?
	configSSHHostAccess = i18n("*ABBREV*SSH*-ABBREV* management hosts can be configured with the following command:*CODE**COMMAND*ssh *CMDUSER*ip-address*-CMDUSER* *CMDUSER*netmask*-CMDUSER* *CMDUSER*interface*-CMDUSER**-COMMAND**-CODE*");			// How to configure SSH...
	scpSupported = false;					// Is SCP supported?
	sshSpecificTimeout = true;				// A SSH Specific Timeout?
	sshTimeout = 300;						// The SSH Timeout (secs)
	configSSHTimeout = i18n("The *ABBREV*SSH*-ABBREV* connection timeout can be configured with the following command:*CODE**COMMAND*ssh timeout *CMDUSER*timeout-minutes*-CMDUSER**-COMMAND**-CODE*");			// The text and commands to configure the timeout

	// SSH 2 support...
	configSSHv2Support = i18n("*DEVICETYPE* devices can be configured to support only *ABBREV*SSH*-ABBREV* protocol version 2 with the following command:*CODE**COMMAND*ssh version 2*-COMMAND**-CODE*");			// How to configure protocol version 2 support only

	// HTTP(S) options...
	httpPort = 80;							// HTTP port
	httpsPort = 443;						// HTTPS port
	httpSpecificTimeout = false;			// A HTTP Specific Timeout?
	httpTimeout = 0;						// The HTTP Timeout (secs)
	configHTTPTimeout = i18n("");			// The text and commands to configure the timeout
	httpLabel = i18n("*ABBREV*HTTP*-ABBREV*");		// The label given to the HTTP service (e.g. HTTP)
	httpsLabel = i18n("*ABBREV*HTTPS*-ABBREV*");	// The label given to the HTTPS service (e.g. HTTPS)
	httpSpecificHost = true;				// Does HTTP have its own access list?
	httpHostsRequired = true;				// Is the host configuration required?
	showHTTPHostInterface = true;			// Show the Interface column in the host table?
	configHTTPHostAccess = i18n("Web-based management hosts can be added with the following command:*CODE**COMMAND*http *CMDUSER*ip-address*-CMDUSER* *CMDUSER*netmask*-CMDUSER* *CMDUSER*interface*-CMDUSER**-COMMAND**-CODE*");		// How to configure HTTP Management hosts...
	disableHTTP = i18n("*ABBREV*HTTP*-ABBREV* access to *DEVICENAME* can be disabled by removing the configured management hosts. This can be done with the following command:*CODE**COMMAND*no http *CMDUSER*ip-address*-CMDUSER* *CMDUSER*netmask*-CMDUSER* *CMDUSER*interface*-CMDUSER**-COMMAND**-CODE*");					// How to disable HTTP text...
	configHTTPSSupport = i18n("*ABBREV*HTTPS*-ABBREV* access to *DEVICENAME* can be configured by adding management hosts. This can be done with the following command:*CODE**COMMAND*http *CMDUSER*ip-address*-CMDUSER* *CMDUSER*netmask*-CMDUSER* *CMDUSER*interface*-CMDUSER**-COMMAND**-CODE*");			// How to configure HTTPS...
	cipherConfigSupported = true;			// Can the Ciphers be configured?
	configCipherText = i18n("The *ABBREV*SSL*-ABBREV* encryption protocol can be restricted to the more secure *ABBREV*SSL*-ABBREV* version 2 and *ABBREV*TLS*-ABBREV* version 1. Furthermore, the ciphers can be configured to the more secure ciphers with key lengths of at least 128 bits. This can be done with the following commands:*CODE**COMMAND*ssl server-version *CMDREQUIRE*sslv3-only *CMDOR* tlsv1-only*-CMDREQUIRE**-COMMAND**COMMAND*ssl encryption *CMDREQUIRE*3des-sha1 *CMDOR* aes128-sha1 *CMDOR* aes256-sha1*-CMDREQUIRE**-COMMAND**-CODE*");			// The text to configure a strong cipher.
}


CiscoSecAdministration::~CiscoSecAdministration()
{
	if (sslCiphers != 0)
		delete sslCiphers;
}


void CiscoSecAdministration::addCipherProtocol(cipherConfig *cipherPointer)
{
	// Protocols...
	if (sslProtocolVersion.compare("sslv3") == 0)
	{
		cipherPointer->ssl2 = true;
		cipherPointer->ssl3 = true;
	}
	else if (sslProtocolVersion.compare("tlsv1") == 0)
	{
		cipherPointer->ssl2 = true;
		cipherPointer->tls1 = true;
	}
	else if (sslProtocolVersion.compare("sslv3-only") == 0)
		cipherPointer->ssl3 = true;
	else if (sslProtocolVersion.compare("tlsv1-only") == 0)
		cipherPointer->tls1 = true;
	else
	{
		cipherPointer->ssl2 = true;
		cipherPointer->ssl3 = true;
		cipherPointer->tls1 = true;
	}
}


int CiscoSecAdministration::processDefaults(Device *device)
{
	// Variables...
	cipherConfig *cipherPointer = 0;
	int errorCode = 0;
	int totalCiphers = sslCiphers->parts - 2;

	errorCode = processDeviceSpecificDefaults(device);

	// Telnet...
	if (telnetHosts != 0)
		telnetEnabled = true;

	// SSH...
	if (sshHosts != 0)
		sshEnabled = true;

	// HTTP...
	if (httpHosts != 0)
	{
		if (httpsSupported == true)
		{
			httpsEnabled = true;
			if (httpsRedirect == true)
				httpEnabled = true;
		}
		else
			httpEnabled = true;
	}

	// Ciphers...
	if (sslCiphers != 0)
	{
		defaultCiphers = false;

		for (totalCiphers = sslCiphers->parts - 2; totalCiphers < sslCiphers->parts; totalCiphers++)
		{

			// 3DES-SHA1...
			if (strcmp(sslCiphers->part(totalCiphers), "3des-sha1") == 0)
			{
				cipherPointer = addCipher();
				cipherPointer->encryption.assign("*ABBREV*3DES*-ABBREV*");
				cipherPointer->authenticaton.assign("*ABBREV*SHA1*-ABBREV*");
				cipherPointer->bits = 168;
				addCipherProtocol(cipherPointer);
			}

			// DES-SHA1...
			else if (strcmp(sslCiphers->part(totalCiphers), "3des-sha1") == 0)
			{
				cipherPointer = addCipher();
				cipherPointer->encryption.assign("*ABBREV*3DES*-ABBREV*");
				cipherPointer->authenticaton.assign("*ABBREV*SHA1*-ABBREV*");
				cipherPointer->bits = 56;
				addCipherProtocol(cipherPointer);
			}

			// RC4-MD5...
			else if (strcmp(sslCiphers->part(totalCiphers), "rc4-md5") == 0)
			{
				cipherPointer = addCipher();
				cipherPointer->encryption.assign("*ABBREV*RC4*-ABBREV*");
				cipherPointer->authenticaton.assign("*ABBREV*MD5*-ABBREV*");
				cipherPointer->bits = 40;
				addCipherProtocol(cipherPointer);
				cipherPointer = addCipher();
				cipherPointer->encryption.assign("*ABBREV*RC4*-ABBREV*");
				cipherPointer->authenticaton.assign("*ABBREV*MD5*-ABBREV*");
				cipherPointer->bits = 56;
				addCipherProtocol(cipherPointer);
				cipherPointer = addCipher();
				cipherPointer->encryption.assign("*ABBREV*RC4*-ABBREV*");
				cipherPointer->authenticaton.assign("*ABBREV*MD5*-ABBREV*");
				cipherPointer->bits = 64;
				addCipherProtocol(cipherPointer);
				cipherPointer = addCipher();
				cipherPointer->encryption.assign("*ABBREV*RC4*-ABBREV*");
				cipherPointer->authenticaton.assign("*ABBREV*MD5*-ABBREV*");
				cipherPointer->bits = 128;
				addCipherProtocol(cipherPointer);
			}

			// AES128-SHA1...
			else if (strcmp(sslCiphers->part(totalCiphers), "aes128-sha1") == 0)
			{
				cipherPointer = addCipher();
				cipherPointer->encryption.assign("*ABBREV*AES*-ABBREV*");
				cipherPointer->authenticaton.assign("*ABBREV*SHA1*-ABBREV*");
				cipherPointer->bits = 128;
				addCipherProtocol(cipherPointer);
			}

			// AES192-SHA1...
			else if (strcmp(sslCiphers->part(totalCiphers), "aes192-sha1") == 0)
			{
				cipherPointer = addCipher();
				cipherPointer->encryption.assign("*ABBREV*AES*-ABBREV*");
				cipherPointer->authenticaton.assign("*ABBREV*SHA1*-ABBREV*");
				cipherPointer->bits = 192;
				addCipherProtocol(cipherPointer);
			}

			// AES256-SHA1...
			else if (strcmp(sslCiphers->part(totalCiphers), "aes256-sha1") == 0)
			{
				cipherPointer = addCipher();
				cipherPointer->encryption.assign("*ABBREV*AES*-ABBREV*");
				cipherPointer->authenticaton.assign("*ABBREV*SHA1*-ABBREV*");
				cipherPointer->bits = 256;
				addCipherProtocol(cipherPointer);
			}
		}
	}
	else
	{
		defaultCiphers = true;

		cipherPointer = addCipher();
		cipherPointer->encryption.assign("*ABBREV*3DES*-ABBREV*");
		cipherPointer->authenticaton.assign("*ABBREV*SHA1*-ABBREV*");
		cipherPointer->bits = 168;
		addCipherProtocol(cipherPointer);

		cipherPointer = addCipher();
		cipherPointer->encryption.assign("*ABBREV*3DES*-ABBREV*");
		cipherPointer->authenticaton.assign("*ABBREV*SHA1*-ABBREV*");
		cipherPointer->bits = 56;
		addCipherProtocol(cipherPointer);

		cipherPointer = addCipher();
		cipherPointer->encryption.assign("*ABBREV*RC4*-ABBREV*");
		cipherPointer->authenticaton.assign("*ABBREV*MD5*-ABBREV*");
		cipherPointer->bits = 40;
		addCipherProtocol(cipherPointer);

		cipherPointer = addCipher();
		cipherPointer->encryption.assign("*ABBREV*RC4*-ABBREV*");
		cipherPointer->authenticaton.assign("*ABBREV*MD5*-ABBREV*");
		cipherPointer->bits = 56;
		addCipherProtocol(cipherPointer);

		cipherPointer = addCipher();
		cipherPointer->encryption.assign("*ABBREV*RC4*-ABBREV*");
		cipherPointer->authenticaton.assign("*ABBREV*MD5*-ABBREV*");
		cipherPointer->bits = 64;
		addCipherProtocol(cipherPointer);

		cipherPointer = addCipher();
		cipherPointer->encryption.assign("*ABBREV*RC4*-ABBREV*");
		cipherPointer->authenticaton.assign("*ABBREV*MD5*-ABBREV*");
		cipherPointer->bits = 128;
		addCipherProtocol(cipherPointer);

		cipherPointer = addCipher();
		cipherPointer->encryption.assign("*ABBREV*AES*-ABBREV*");
		cipherPointer->authenticaton.assign("*ABBREV*SHA1*-ABBREV*");
		cipherPointer->bits = 128;
		addCipherProtocol(cipherPointer);

		cipherPointer = addCipher();
		cipherPointer->encryption.assign("*ABBREV*AES*-ABBREV*");
		cipherPointer->authenticaton.assign("*ABBREV*SHA1*-ABBREV*");
		cipherPointer->bits = 192;
		addCipherProtocol(cipherPointer);

		cipherPointer = addCipher();
		cipherPointer->encryption.assign("*ABBREV*AES*-ABBREV*");
		cipherPointer->authenticaton.assign("*ABBREV*SHA1*-ABBREV*");
		cipherPointer->bits = 256;
		addCipherProtocol(cipherPointer);
	}

	return errorCode;
}


int CiscoSecAdministration::processDeviceSpecificDefaults(Device *device)
{
	return 0;
}


int CiscoSecAdministration::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	hostFilter *hostPointer = 0;
	int errorCode = 0;
	int tempInt = 0;
	bool setting = false;

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
 
	// console timeout...
	if ((strcmp(command->part(tempInt), "console") == 0) && (strcmp(command->part(tempInt + 1), "timeout") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sConsole Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 2;
		if (setting == true)
			consoleTimeout = atoi(command->part(tempInt)) * 60;
		else
			consoleTimeout = 0;
	}

	// SSL...
	else if (strcmp(command->part(tempInt), "ssl") == 0)
	{
		tempInt++;

		// version...
		if (strcmp(command->part(tempInt), "server-version") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sSSL Server Version Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			tempInt++;
			sslProtocolVersion.assign(command->part(tempInt));
		}

		// encryption...
		else if (strcmp(command->part(tempInt), "encryption") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sSSL Encryption Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			if (setting == true)
			{
				tempInt++;
				sslCiphers = new (ConfigLine);
				sslCiphers->setConfigLine(line);
			}
		}

		// All others...
		else
			device->lineNotProcessed(line);
	}

	// SSH...
	else if (strcmp(command->part(tempInt), "ssh") == 0)
	{
		tempInt++;

		// version...
		if (strcmp(command->part(tempInt), "version") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sSSH Version Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			tempInt++;
			if (setting == false)
				sshVersion = 0;
			else if (strcmp(command->part(tempInt), "1") == 0)
				sshVersion = 1;
			else
				sshVersion = 2;
			sshSupported = true;
			sshUpgrade = false;
			ssh2Supported = true;
			ssh2upgrade = false;
		}

		// timeout...
		else if (strcmp(command->part(tempInt), "timeout") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sSSH Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			tempInt++;
			if (setting == false)
				sshTimeout = 300;
			else
				sshTimeout = atoi(command->part(tempInt)) * 60;
			sshSupported = true;
			sshUpgrade = false;
		}

		// scopy...
		else if (((strcmp(command->part(tempInt), "scopy") == 0) || (strcmp(command->part(tempInt), "copy") == 0)) && (strcmp(command->part(tempInt + 1), "enable") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sSSH SCP Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			scpSupported = true;
			if (setting == false)
				scpEnabled = false;
			else
				scpEnabled = true;
			sshSupported = true;
			sshUpgrade = false;
		}

		// ssh management hosts...
		else if (command->parts > 2)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sSSH Host Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			hostPointer = addHostFilter(sshService);
			hostPointer->host.assign(command->part(tempInt));
			tempInt++;
			if (command->parts == 4)
			{
				hostPointer->netmask.assign(command->part(tempInt));
				tempInt++;
			}
			hostPointer->interface.assign(command->part(tempInt));
			sshSupported = true;
			sshEnabled = true;
		}

		// All others...
		else
			device->lineNotProcessed(line);
	}

	// Telnet...
	else if (strcmp(command->part(tempInt), "telnet") == 0)
	{
		tempInt++;

		// timeout...
		if (strcmp(command->part(tempInt), "timeout") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sTelnet Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			tempInt++;
			if (setting == false)
				telnetTimeout = 300;
			else
				telnetTimeout = atoi(command->part(tempInt)) * 60;
		}

		// Telnet management hosts...
		else
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sTelnet Host Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			hostPointer = addHostFilter(telnetService);
			hostPointer->host.assign(command->part(tempInt));
			if (command->parts == 3)
			{
				tempInt++;
				hostPointer->interface.assign(command->part(tempInt));
			}
			else if (command->parts == 4)
			{
				tempInt++;
				hostPointer->netmask.assign(command->part(tempInt));
				tempInt++;
				hostPointer->interface.assign(command->part(tempInt));
			}
		}
	}

	// HTTP...
	else if (strcmp(command->part(tempInt), "http") == 0)
	{
		tempInt++;

		// server enable...
		if ((strcmp(command->part(tempInt), "server") == 0) && (strcmp(command->part(tempInt + 1), "enable") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sHTTP Server Enable Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			httpsEnabled = setting;
			httpsSupported = true;
			tempInt += 2;
			if (tempInt < command->parts)
				httpsPort = atoi(command->part(tempInt));
		}

		// Redirect...
		else if (strcmp(command->part(tempInt), "redirect") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sHTTP Redirect Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			httpsRedirect = setting;
			httpsSupported = true;
			httpSupported = true;
			httpEnabled = true;
			tempInt += 2;
			if (tempInt < command->parts)
				httpPort = atoi(command->part(tempInt));
		}

		// Certificate Authentication...
		else if (strcmp(command->part(tempInt), "authentication-certificate") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sHTTP Auth Cert Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			httpsSupported = true;
			httpSupported = true;
			tempInt += 2;
			if (tempInt < command->parts)
				httpPort = atoi(command->part(tempInt));
		}

		// Hosts...
		else if (command->parts == 4)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sHTTP Hosts Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			hostPointer = addHostFilter(httpService);
			hostPointer->host.assign(command->part(tempInt));
			tempInt++;
			hostPointer->netmask.assign(command->part(tempInt));
			tempInt++;
			hostPointer->interface.assign(command->part(tempInt));
		}

		// All others...
		else
			device->lineNotProcessed(line);
	}

	// All others...
	else
		device->lineNotProcessed(line);


	return errorCode;
}


int CiscoSecAdministration::generateDeviceHTTPConfig(Device *device)
{
	// Variables...
	Device::paragraphStruct *paragraphPointer = 0;
	int errorCode = 0;

	// Get Paragraph Pointer...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-ADMINHTTP-TABLE");

	// HTTPS Certificate...
	if (!certificateAuthInterface.empty())
	{
		device->addTableData(paragraphPointer->table, i18n("Authentication certificate required on interface"));
		device->addTableData(paragraphPointer->table, certificateAuthInterface.c_str());
	}

	return errorCode;
}


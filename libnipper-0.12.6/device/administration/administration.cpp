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
#include "administration.h"
#include "../interfaces/interfaces.h"


Administration::Administration()
{
	// Host restrictions...
	serviceHosts = 0;
	telnetHosts = 0;						// Telnet host list
	tftpHosts = 0;							// The TFTP hosts
	ftpHosts = 0;							// The FTP hosts
	sshHosts = 0;							// The SSH host list
	httpHosts = 0;							// The HTTP hosts
	ciphers = 0;							// The SSL ciphers configured
	defaultCiphers = false;

	// -----------------------------------------------------------------------
	// Device Specific Settings...
	// -----------------------------------------------------------------------

	// General...
	generalSettings = false;				// Show the general settings section?
	consoleEnabled = false;					// Is the Console port enabled?
	consoleSupported = false;				// Is a console port supported?
	consoleTimeoutSupported = false;		// Is a console timeout supported?
	consoleTimeout = 0;						// Console timeout
	configConsoleTimeout = i18n("");		// The text and commands to configure the timeout
	auxSupported = false;					// Are AUX port(s) supported?
	auxEnabled = false;						// Is AUX port(s) enabled?
	configAuxPort = i18n("");				// The text and commands to disable the AUX port
	callbackSupported = false;				// Is AUX port callback supported?
	callbackEnabled = false;				// Is AUX port callback enabled?
	configCallback = i18n("");				// The text to configure callback.
	connectionTimeoutSupported = false;		// Is a connection timeout supported?
	connectionTimeout = 0;					// Connection Timeout
	configTimeout = i18n("");				// The text and commands to configure the timeout
	cdpSupported = false;					// Is CDP supported (globally, see interfaces for per interface activation)
	cdpEnabled = false;						// Is CDP enabled
	cdpVersionSupported = false;			// Is CDP version supported
	cdpVersion = 0;							// CDP version
	disableCDPText = i18n("");				// The text and commands to disable CDP

	// Host restrictions...
	serviceWideHosts = false;				// Do all the admin services share a common host restrictions?
	showHostInterface = false;				// Show the Interface column in the host table?
	showHostAccess = false;					// Show the Access column in the host table?
	serviceConfigHosts = i18n("");			// Text, how to configure administrative host restrictions.

	// Telnet options...
	telnetSupported = false;				// Is telnet supported?
	telnetEnabled = false;					// Is Telnet enabled?
	telnetPort = 23;						// The telnet service port
	telnetSpecificHost = false;				// Does Telnet have its own access list?
	telnetHostsRequired = false;			// Is the host configuration required?
	showTelnetHostInterface = false;		// Show the Interface column in the host table?
	showTelnetHostAccess = false;			// Show the Access column in the host table?
	configTelnetHostAccess = i18n("");		// How access lists are configured for the telnet service
	disableTelnet = i18n("");				// How to disable telnet text...
	telnetSpecificTimeout = false;			// A Telnet Specific Timeout?
	telnetTimeout = 0;						// The Telnet Timeout (secs)
	configTelnetTimeout = i18n("");			// The text and commands to configure the timeout

	// TFTP options...
	tftpSupported = false;					// Is TFTP supported?
	tftpEnabled = false;					// Is TFTP enabled?
	tftpPort = 69;							// The TFTP service port
	tftpSpecificHost = false;				// Does TFTP have its own access list?
	tftpHostsRequired = false;				// Is the host configuration required?
	showTFTPHostInterface = false;			// Show the Interface column in the host table?
	showTFTPHostAccess = false;				// Show the Access column in the host table?
	configTFTPHostAccess = i18n("");		// How access lists are configured for the TFTP service
	disableTFTP = i18n("");					// How to disable TFTP text...

	// FTP options...
	ftpSupported = false;					// Is FTP supported?
	ftpEnabled = false;						// Is FTP enabled?
	ftpPort = 21;							// The FTP service port
	ftpSpecificHost = false;				// Does FTP have its own access list?
	ftpHostsRequired = false;				// Is the host configuration required?
	showFTPHostInterface = false;			// Show the Interface column in the host table?
	showFTPHostAccess = false;				// Show the Access column in the host table?
	configFTPHostAccess = i18n("");			// How access lists are configured for the FTP service
	disableFTP = i18n("");					// How to disable FTP text...
	ftpSpecificTimeout = false;				// A FTP Specific Timeout?
	ftpTimeout = 0;							// The FTP Timeout (secs)
	configFTPTimeout = i18n("");			// The text and commands to configure the timeout

	// SSH options...
	sshSupported = false;					// Does this device support SSH?
	sshUpgrade = false;						// Do you have to upgrade?
	sshEnabled = false;						// Is the SSH service enabled?
	sshVersion = 0;							// What is the SSH Protocol version (0 = 1 and 2)
	sshPort = 22;							// The SSH port number
	configSSHSupport = i18n("");			// How to configure SSH...
	sshSpecificHost = false;				// Does SSH have its own access list?
	sshHostsRequired = false;				// Is the host configuration required?
	showSSHHostInterface = false;			// Show the Interface column in the host table?
	showSSHHostAccess = false;				// Show the Access column in the host table?
	configSSHHostAccess = i18n("");			// How to configure SSH...
	sshSpecificTimeout = false;				// A SSH Specific Timeout?
	sshTimeout = 0;							// The SSH Timeout (secs)
	configSSHTimeout = i18n("");			// The text and commands to configure the timeout

	// SSH Options
	sftpEnabled = false;					// Is SFTP enabled?
	sftpSupported = false;					// Is SFTP supported?
	sftpUpgrade = false;					// Upgrade to support SFTP?
	configSFTP = i18n("");					// Text and commands to configure SFTP
	scpSupported = false;					// Is SCP supported?
	scpEnabled = false;						// Is SCP enabled?

	// SSH 2 support...
	ssh2Supported = false;					// Does the device support SSH version 2?
	ssh2upgrade = false;					// Do you have to upgrade...
	configSSHv2Support = i18n("");			// How to configure protocol version 2 support only

	// Config report SSH support text
	sshConfigProtocolSupport = i18n("");	// Config report text on protocol support (e.g. supports both version 1 and 2 of the protocol)

	// HTTP(S) options...
	httpSupported = false;					// Does this device support HTTP
	httpsSupported = false;					// Does this device support HTTPS
	httpsUpgrade = false;					// Do you have to upgrade for HTTPS?
	httpEnabled = false;					// Is the HTTP service enabled?
	httpPort = 80;							// HTTP port
	httpsEnabled = false;					// Is the HTTPS service enabled?
	httpsPort = 443;						// HTTPS port
	httpsRedirect = false;					// Is HTTP to HTTPS redirect enabled?
	httpSpecificTimeout = false;			// A HTTP Specific Timeout?
	httpTimeout = 0;						// The HTTP Timeout (secs)
	configHTTPTimeout = i18n("");			// The text and commands to configure the timeout
	httpLabel = i18n("*ABBREV*HTTP*-ABBREV*");		// The label given to the HTTP service (e.g. HTTP)
	httpsLabel = i18n("*ABBREV*HTTPS*-ABBREV*");	// The label given to the HTTPS service (e.g. HTTPS)
	httpSpecificHost = false;				// Does HTTP have its own access list?
	httpHostsRequired = false;				// Is the host configuration required?
	showHTTPHostInterface = false;			// Show the Interface column in the host table?
	showHTTPHostAccess = false;				// Show the Access column in the host table?
	configHTTPHostAccess = i18n("");		// How to configure HTTP Management hosts...
	disableHTTP = i18n("");					// How to disable HTTP text...
	configHTTPSSupport = i18n("");			// How to configure HTTPS...
	cipherConfigSupported = false;			// Can the Ciphers be configured?
	configCipherText = i18n("");			// The text to configure a strong cipher.

	// BOOTP Support...
	bootPServerSupported = false;			// Is BOOTP supported?
	bootPEnabled = false;					// Is BOOTP enabled?
	configDisableBootP = i18n("");			// Config report text to disable bootp

	// Finger Support...
	fingerServiceSupported = false;			// Is the finger service supported?
	fingerServiceEnabled = false;			// Is the finger service enabled?
	configDisableFinger = i18n("");			// Config report text to disable finger
}


Administration::~Administration()
{
	// Variables...
	hostFilter *hostPointer = 0;
	cipherConfig *cipherPointer = 0;

	while (ciphers != 0)
	{
		cipherPointer = ciphers->next;
		delete ciphers;
		ciphers = cipherPointer;
	}

	while (serviceHosts != 0)
	{
		hostPointer = serviceHosts->next;
		delete serviceHosts;
		serviceHosts = hostPointer;
	}

	while (telnetHosts != 0)
	{
		hostPointer = telnetHosts->next;
		delete telnetHosts;
		telnetHosts = hostPointer;
	}

	while (ftpHosts != 0)
	{
		hostPointer = ftpHosts->next;
		delete ftpHosts;
		ftpHosts = hostPointer;
	}

	while (tftpHosts != 0)
	{
		hostPointer = tftpHosts->next;
		delete tftpHosts;
		tftpHosts = hostPointer;
	}

	while (sshHosts != 0)
	{
		hostPointer = sshHosts->next;
		delete sshHosts;
		sshHosts = hostPointer;
	}

	while (httpHosts != 0)
	{
		hostPointer = httpHosts->next;
		delete httpHosts;
		httpHosts = hostPointer;
	}
}


int Administration::generateConfigReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	int errorCode = 0;

	if ((consoleSupported == true) || (telnetSupported == true) || (sshSupported == true) || (httpSupported == true) || (httpsSupported == true) || (ftpSupported == true) || (tftpSupported == true))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s Administration Settings\n", device->config->COL_BLUE, device->config->COL_RESET);

		// Create Config Report Section...
		configReportPointer = device->getConfigSection("CONFIG-ADMIN");
		configReportPointer->title = i18n("Administration Settings");
		paragraphPointer = device->addParagraph(configReportPointer);
		paragraphPointer->paragraph.assign(i18n("This section describes the services that are supported by *DEVICETYPE* for administration. Each subsection covers a particular service and its configuration settings."));

		if (generalSettings == true)
			errorCode = generateGeneralConfig(device);

		if (telnetSupported == true)
			errorCode = generateTelnetConfig(device);

		if (sshSupported == true)
			errorCode = generateSSHConfig(device);

		if ((httpSupported == true) || (httpsSupported == true))
			errorCode = generateHTTPConfig(device);

		if (ftpSupported == true)
			errorCode = generateFTPConfig(device);

		if (tftpSupported == true)
			errorCode = generateTFTPConfig(device);

		if (bootPServerSupported == true)
			errorCode = generateBootPConfig(device);

		if (fingerServiceSupported == true)
			errorCode = generateFingerConfig(device);

		if (serviceHosts != 0)
			errorCode = generateHostsConfig(device);

		errorCode = generateDeviceSpecificConfig(device);
	}

	return errorCode;
}


int Administration::generateDeviceSpecificConfig(Device *device)
{
	return 0;
}


int Administration::generateSecurityReport(Device *device)
{
	// Variables...
	hostFilter *serviceHostPointer = 0;
	cipherConfig *cipherPointer = 0;
	int weakTelnetHosts = 0;
	bool noWeakTelnetHosts = true;
	int weakTFTPHosts = 0;
	bool noWeakTFTPHosts = true;
	int weakFTPHosts = 0;
	bool noWeakFTPHosts = true;
	int weakSSHHosts = 0;
	bool noWeakSSHHosts = true;
	int weakHTTPHosts = 0;
	bool noWeakHTTPHosts = true;
	int weakHosts = 0;
	int errorCode = 0;
	int cipherIssue = 0;
	bool sshVersion1 = false;

	// Search for issues...

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s Administration Issue Checks\n", device->config->COL_BLUE, device->config->COL_RESET);

	// Find weak hosts...
	serviceHostPointer = serviceHosts;
	while (serviceHostPointer != 0)
	{
		if (serviceHostPointer->netmask.compare("255.255.255.255") != 0)
		{
			weakHosts++;
			noWeakTelnetHosts = false;
			noWeakSSHHosts = false;
		}
		serviceHostPointer = serviceHostPointer->next;
	}

	// Find weak Telnet hosts...
	serviceHostPointer = telnetHosts;
	while (serviceHostPointer != 0)
	{
		if (serviceHostPointer->netmask.compare("255.255.255.255") != 0)
		{
			noWeakTelnetHosts = false;
			weakTelnetHosts++;
		}
		serviceHostPointer = serviceHostPointer->next;
	}

	// Find weak TFTP hosts...
	serviceHostPointer = tftpHosts;
	while (serviceHostPointer != 0)
	{
		if (serviceHostPointer->netmask.compare("255.255.255.255") != 0)
		{
			noWeakTFTPHosts = false;
			weakTFTPHosts++;
		}
		serviceHostPointer = serviceHostPointer->next;
	}

	// Find weak FTP hosts...
	serviceHostPointer = ftpHosts;
	while (serviceHostPointer != 0)
	{
		if (serviceHostPointer->netmask.compare("255.255.255.255") != 0)
		{
			noWeakFTPHosts = false;
			weakFTPHosts++;
		}
		serviceHostPointer = serviceHostPointer->next;
	}

	// Find weak SSH hosts...
	serviceHostPointer = sshHosts;
	while (serviceHostPointer != 0)
	{
		if (serviceHostPointer->netmask.compare("255.255.255.255") != 0)
		{
			weakSSHHosts++;
			noWeakSSHHosts = false;
		}
		serviceHostPointer = serviceHostPointer->next;
	}

	// Find weak HTTP hosts...
	serviceHostPointer = httpHosts;
	while (serviceHostPointer != 0)
	{
		if (serviceHostPointer->netmask.compare("255.255.255.255") != 0)
		{
			weakHTTPHosts++;
			noWeakHTTPHosts = false;
		}
		serviceHostPointer = serviceHostPointer->next;
	}

	// Determine weak ciphers...
	cipherPointer = ciphers;
	while (cipherPointer != 0)
	{
		if ((cipherPointer->bits < 128) || (cipherPointer->ssl2 == true))
			cipherIssue++;
		cipherPointer = cipherPointer->next;
	}


	// Telnet issues...
	if (telnetEnabled == true)
	{
		errorCode = generateTelnetSecurityIssue(device, noWeakTelnetHosts);
		if (errorCode != 0)
			return errorCode;
	}

	if ((telnetEnabled == true) && (telnetHostsRequired == false) && (telnetHosts == 0) && (telnetSpecificHost == true))
	{
		errorCode = generateTelnetHostSecurityIssue(device);
		if (errorCode != 0)
			return errorCode;
	}

	if (weakTelnetHosts > 0)
	{
		errorCode = generateTelnetWeakHostSecurityIssue(device, weakTelnetHosts);
		if (errorCode != 0)
			return errorCode;
	}


	// SSH issues...

	if ((sshEnabled == true) && (sshVersion != 2))
	{
		errorCode = generateSSHVersionSecurityIssue(device, noWeakSSHHosts);
		if (errorCode != 0)
			return errorCode;
		sshVersion1 = true;
	}

	if ((sshEnabled == true) && (sshHostsRequired == false) && (sshHosts == 0) && (sshSpecificHost == true))
	{
		errorCode = generateSSHHostSecurityIssue(device, sshVersion1);
		if (errorCode != 0)
			return errorCode;
	}

	if (weakSSHHosts > 0)
	{
		errorCode = generateSSHWeakHostSecurityIssue(device, weakSSHHosts, sshVersion1);
		if (errorCode != 0)
			return errorCode;
	}


	// HTTP issues...

	if ((httpSupported == true) && (httpEnabled == true) && (httpsRedirect == false))
	{
		errorCode = generateHTTPSecurityIssue(device, noWeakHTTPHosts);
		if (errorCode != 0)
			return errorCode;
	}

	if (((httpEnabled == true) || (httpsEnabled == true)) && (httpHostsRequired == false) && (httpHosts == 0) && (httpSpecificHost == true))
	{
		errorCode = generateHTTPHostSecurityIssue(device);
		if (errorCode != 0)
			return errorCode;
	}

	if (weakHTTPHosts > 0)
	{
		errorCode = generateHTTPWeakHostSecurityIssue(device, weakHTTPHosts);
		if (errorCode != 0)
			return errorCode;
	}

	if ((cipherIssue > 0) && (httpsEnabled == true))
	{
		errorCode = generateWeakCipherSecurityIssue(device, cipherIssue);
		if (errorCode != 0)
			return errorCode;
	}


	// FTP issues...

	if (ftpEnabled == true)
	{
		errorCode = generateFTPSecurityIssue(device, noWeakFTPHosts);
		if (errorCode != 0)
			return errorCode;
	}

	if ((ftpEnabled == true) && (ftpHostsRequired == false) && (ftpHosts == 0) && (ftpSpecificHost == true))
	{
		errorCode = generateFTPHostSecurityIssue(device);
		if (errorCode != 0)
			return errorCode;
	}

	if (weakFTPHosts > 0)
	{
		errorCode = generateFTPWeakHostSecurityIssue(device, weakFTPHosts);
		if (errorCode != 0)
			return errorCode;
	}


	// TFTP issues...

	if (tftpEnabled == true)
	{
		errorCode = generateTFTPSecurityIssue(device, noWeakTFTPHosts);
		if (errorCode != 0)
			return errorCode;
	}

	if ((tftpEnabled == true) && (tftpHostsRequired == false) && (tftpHosts == 0) && (tftpSpecificHost == true))
	{
		errorCode = generateTFTPHostSecurityIssue(device);
		if (errorCode != 0)
			return errorCode;
	}

	if (weakTFTPHosts > 0)
	{
		errorCode = generateTFTPWeakHostSecurityIssue(device, weakTFTPHosts);
		if (errorCode != 0)
			return errorCode;
	}


	// Finger Issue...
	if ((fingerServiceSupported == true) && (fingerServiceEnabled == true))
	{
		errorCode = generateFingerSecurityIssue(device);
		if (errorCode != 0)
			return errorCode;
	}


	// BOOTP Issue...
	if ((bootPServerSupported == true) && (bootPEnabled == true))
	{
		errorCode = generateBootPSecurityIssue(device);
		if (errorCode != 0)
			return errorCode;
	}


	// Management host issues...

	if (((telnetEnabled == true) || (sshEnabled == true) || (tftpEnabled == true) || (ftpEnabled == true) || (httpEnabled == true) || (httpsEnabled == true)) && (serviceWideHosts == true) && (serviceHosts == 0))
	{
		errorCode = generateServiceHostSecurityIssue(device);
		if (errorCode != 0)
			return errorCode;
	}

	if (((telnetEnabled == true) || (sshEnabled == true) || (tftpEnabled == true) || (ftpEnabled == true) || (httpEnabled == true) || (httpsEnabled == true)) && (serviceWideHosts == true) && (weakHosts > 0))
	{
		errorCode = generateWeakHostSecurityIssue(device, weakHosts);
		if (errorCode != 0)
			return errorCode;
	}


	// Find weak timeout issues...

	if ((connectionTimeoutSupported == true) && ((connectionTimeout > device->config->connectionTimeouts) || (connectionTimeout == 0)))
	{
		errorCode = generateTimeoutSecurityIssue(device);
		if (errorCode != 0)
			return errorCode;
	}

	if ((consoleEnabled == true) && (consoleTimeoutSupported == true) && ((consoleTimeout > device->config->connectionTimeouts) || (consoleTimeout == 0)))
	{
		errorCode = generateConsoleTimeoutSecurityIssue(device);
		if (errorCode != 0)
			return errorCode;
	}

	if ((telnetEnabled == true) && (telnetSpecificTimeout == true) && ((telnetTimeout > device->config->connectionTimeouts) || (telnetTimeout == 0)))
	{
		errorCode = generateTelnetTimeoutSecurityIssue(device, weakTelnetHosts);
		if (errorCode != 0)
			return errorCode;
	}

	if ((ftpEnabled == true) && (ftpSpecificTimeout == true) && ((ftpTimeout > device->config->connectionTimeouts) || (ftpTimeout == 0)))
	{
		errorCode = generateFTPTimeoutSecurityIssue(device, weakFTPHosts);
		if (errorCode != 0)
			return errorCode;
	}

	if ((sshEnabled == true) && (sshSpecificTimeout == true) && ((sshTimeout > device->config->connectionTimeouts) || (sshTimeout == 0)))
	{
		errorCode = generateSSHTimeoutSecurityIssue(device, weakSSHHosts);
		if (errorCode != 0)
			return errorCode;
	}

	if (((httpsEnabled == true) || (httpEnabled == true)) && (httpSpecificTimeout == true) && ((httpTimeout > device->config->connectionTimeouts) || (httpTimeout == 0)))
	{
		errorCode = generateHTTPTimeoutSecurityIssue(device, weakHTTPHosts);
		if (errorCode != 0)
			return errorCode;
	}

	if ((auxSupported == true) && (auxEnabled == true) && ((callbackSupported == false) || ((callbackSupported == true) && (callbackEnabled == false))))
	{
		errorCode = generateAUXSecurityIssue(device);
			return errorCode;
	}

	if ((cdpSupported == true) && (cdpEnabled == true))
	{
		if (device->interfaces != 0)
		{
			if (device->interfaces->cdpSupported == false)
			{
				errorCode = generateCDPSecurityIssue(device);
					return errorCode;
			}
		}
	}


	errorCode = generateSecuritySpecificReport(device);

	return errorCode;
}


Administration::hostFilter *Administration::addHostFilter(enum serviceType type)
{
	// Variables...
	hostFilter *hostFilterPointer = 0;

	// Create...
	if ((type == allServices) && (serviceHosts == 0))
	{
		serviceHosts = new (hostFilter);
		hostFilterPointer = serviceHosts;
	}
	else if ((type == telnetService) && (telnetHosts == 0))
	{
		telnetHosts = new (hostFilter);
		hostFilterPointer = telnetHosts;
	}
	else if ((type == tftpService) && (tftpHosts == 0))
	{
		tftpHosts = new (hostFilter);
		hostFilterPointer = tftpHosts;
	}
	else if ((type == ftpService) && (ftpHosts == 0))
	{
		ftpHosts = new (hostFilter);
		hostFilterPointer = ftpHosts;
	}
	else if ((type == sshService) && (sshHosts == 0))
	{
		sshHosts = new (hostFilter);
		hostFilterPointer = sshHosts;
	}
	else if ((type == httpService) && (httpHosts == 0))
	{
		httpHosts = new (hostFilter);
		hostFilterPointer = httpHosts;
	}
	else
	{
		if (type == allServices)
			hostFilterPointer = serviceHosts;
		else if (type == telnetService)
			hostFilterPointer = telnetHosts;
		else if (type == ftpService)
			hostFilterPointer = ftpHosts;
		else if (type == tftpService)
			hostFilterPointer = tftpHosts;
		else if (type == sshService)
			hostFilterPointer = sshHosts;
		else if (type == httpService)
			hostFilterPointer = httpHosts;
		while (hostFilterPointer->next != 0)
			hostFilterPointer = hostFilterPointer->next;
		hostFilterPointer->next = new (hostFilter);
		hostFilterPointer = hostFilterPointer->next;
	}

	// Init...
	hostFilterPointer->next = 0;
	hostFilterPointer->netmask.assign("255.255.255.255");

	return hostFilterPointer;
}


Administration::cipherConfig *Administration::addCipher()
{
	// Variables...
	cipherConfig *cipherPointer = 0;

	// Create...
	if (ciphers == 0)
	{
		ciphers = new (cipherConfig);
		cipherPointer = ciphers;
	}
	else
	{
		cipherPointer = ciphers;
		while (cipherPointer->next != 0)
			cipherPointer = cipherPointer->next;
		cipherPointer->next = new (cipherConfig);
		cipherPointer = cipherPointer->next;
	}

	// Init...
	cipherPointer->bits = 0;
	cipherPointer->ssl2 = false;
	cipherPointer->ssl3 = false;
	cipherPointer->tls1 = false;
	cipherPointer->next = 0;

	return cipherPointer;
}



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

// Include...
#include <cstdlib>
#include <cstring>

#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "device.h"
#include "general.h"
#include "administration.h"


CatalystAdministration::CatalystAdministration()
{
	// General...
	generalSettings = false;				// Show the general settings section?
	consoleEnabled = true;					// Is the Console port enabled?
	consoleSupported = true;				// Is a console port supported?
	consoleTimeoutSupported = false;		// Is a console timeout supported?
	//consoleTimeout = 0;					// Console timeout
	//configConsoleTimeout = i18n("");		// The text and commands to configure the timeout
	connectionTimeoutSupported = false;		// Is a connection timeout supported?
	//connectionTimeout = 0;				// Connection Timeout
	//configTimeout = i18n("");				// The text and commands to configure the timeout

	// Host restrictions...
	serviceWideHosts = false;				// Do all the admin services share a common host restrictions?
	serviceConfigHosts = i18n("");			// Text, how to configure administrative host restrictions.

	// Telnet options...
	telnetSupported = true;					// Is telnet supported?
	telnetEnabled = true;					// Is Telnet enabled?
	telnetPort = 23;						// The telnet service port
	telnetSpecificHost = false;				// Does Telnet have its own access list?
	telnetHostsRequired = false;			// Is the host configuration required?
	configTelnetHostAccess = i18n("Telnet management hosts can be configured using the following commands:*CODE**COMMAND*set ip permit enable telnet*-COMMAND**COMMAND*set ip permit *CMDUSER*ip-address*-CMDUSER* *CMDOPTION**CMDUSER*netmask*-CMDUSER**-CMDOPTION* telnet*-COMMAND**-CODE*");		// How access lists are configured for the telnet service
	disableTelnet = i18n("The Telnet service can be disabled on *DEVICENAME* with the following command:*CODE**COMMAND*set ip telnet server disable*-COMMAND**-CODE*");				// How to disable telnet text...
	//telnetSpecificTimeout = false;		// A Telnet Specific Timeout?
	//telnetTimeout = 0;					// The Telnet Timeout (secs)
	configTelnetTimeout = i18n("");			// The text and commands to configure the timeout

	// TFTP options...
	tftpSupported = false;					// Is TFTP supported?
	//tftpEnabled = false;					// Is TFTP enabled?
	//tftpPort = 69;						// The TFTP service port
	//tftpSpecificHost = false;				// Does TFTP have its own access list?
	//tftpHostsRequired = false;			// Is the host configuration required?
	//configTFTPHostAccess = i18n("");		// How access lists are configured for the TFTP service
	//disableTFTP = i18n("");				// How to disable TFTP text...

	// FTP options...
	ftpSupported = false;					// Is FTP supported?
	//ftpEnabled = false;					// Is FTP enabled?
	//ftpPort = 21;							// The FTP service port
	//ftpSpecificHost = false;				// Does FTP have its own access list?
	//ftpHostsRequired = false;				// Is the host configuration required?
	//configFTPHostAccess = i18n("");		// How access lists are configured for the FTP service
	//disableFTP = i18n("");				// How to disable FTP text...
	//ftpSpecificTimeout = false;			// A FTP Specific Timeout?
	//ftpTimeout = 0;						// The FTP Timeout (secs)
	//configFTPTimeout = i18n("");			// The text and commands to configure the timeout

	// SFTP options...
	sftpSupported = false;					// Is SFTP supported?
	//sftpEnabled = false;					// Is SFTP enabled?
	//sftpPort = 21;						// The SFTP service port
	//sftpUpgrade = false;					// Is an upgrade required to support SFTP?
	//sftpSpecificHost = false;				// Does SFTP have its own access list?
	//sftpHostsRequired = false;			// Is the host configuration required?
	//configSFTPHostAccess = i18n("");		// How access lists are configured for the SFTP service
	//configSFTP = i18n("");				// How to configure SFTP
	//sftpSpecificTimeout = false;			// A SFTP Specific Timeout?
	//sftpTimeout = 0;						// The SFTP Timeout (secs)
	//configSFTPTimeout = i18n("");			// The text and commands to configure the timeout

	// SSH options...
	sshSupported = false;					// Does this device support SSH?
	sshUpgrade = false;						// Do you have to upgrade?
	sshEnabled = false;						// Is the SSH service enabled?
	sshVersion = 0;							// What is the SSH Protocol version (0 = 1 and 2)
	sshPort = 22;							// The SSH port number
	configSSHSupport = i18n("");			// How to configure SSH...
	sshSpecificHost = false;				// Does SSH have its own access list?
	sshHostsRequired = false;				// Is the host configuration required?
	configSSHHostAccess = i18n("*ABBREV*SSH*-ABBREV* management hosts can be configured using the following commands:*CODE**COMMAND*set ip permit enable ssh*-COMMAND**COMMAND*set ip permit *CMDUSER*ip-address*-CMDUSER* *CMDOPTION**CMDUSER*netmask*-CMDUSER**-CMDOPTION* ssh*-COMMAND**-CODE*");			// How to configure SSH...
	scpSupported = false;					// Is SCP supported?
	sshSpecificTimeout = false;				// A SSH Specific Timeout?
	sshTimeout = 0;							// The SSH Timeout (secs)
	configSSHTimeout = i18n("");			// The text and commands to configure the timeout

	// SSH 2 support...
	ssh2Supported = false;					// Does the device support SSH version 2?
	ssh2upgrade = false;					// Do you have to upgrade...
	configSSHv2Support = i18n("Support for *ABBREV*SSH*-ABBREV* protocol version 2 can be configured with the following command:*CODE**COMMAND*set ssh mode v2*-COMMAND**-CODE*");			// How to configure protocol version 2 support only

	sshConfigProtocolSupport = i18n("The *ABBREV*SSH*-ABBREV* protocol service is supported on *DEVICETYPE* from around *DEVICEOS* version 6 onwards. Support for *ABBREV*SSH*-ABBREV* protocol version 2 was introduced around *DEVICEOS* version 8.");		// Config report text on protocol support (e.g. supports both version 1 and 2 of the protocol)

	// HTTP(S) options...
	httpSupported = true;					// Does this device support HTTP
	httpsSupported = false;					// Does this device support HTTPS
	//httpsUpgrade = false;					// Do you have to upgrade for HTTPS?
	httpEnabled = false;					// Is the HTTP service enabled?
	httpPort = 80;							// HTTP port
	//httpsEnabled = false;					// Is the HTTPS service enabled?
	//httpsPort = 443;						// HTTPS port
	//httpsRedirect = false;				// Is HTTP to HTTPS redirect enabled?
	//httpSpecificTimeout = false;			// A HTTP Specific Timeout?
	//httpTimeout = 0;						// The HTTP Timeout (secs)
	//configHTTPTimeout = i18n("");			// The text and commands to configure the timeout
	httpLabel = i18n("*ABBREV*HTTP*-ABBREV*");		// The label given to the HTTP service (e.g. HTTP)
	httpsLabel = i18n("*ABBREV*HTTPS*-ABBREV*");	// The label given to the HTTPS service (e.g. HTTPS)
	//httpSpecificHost = false;				// Does HTTP have its own access list?
	//httpHostsRequired = false;			// Is the host configuration required?
	//configHTTPHostAccess = i18n("");		// How to configure HTTP Management hosts...
	//httpsRedirectSupported = false;		// Is HTTP redirected to HTTPS?
	disableHTTP = i18n("The *ABBREV*HTTP*-ABBREV* service can be disabled on *DEVICENAME* with the following command:*CODE**COMMAND*set ip telnet server disable*-COMMAND**-CODE*");					// How to disable HTTP text...
	//configHTTPSSupport = i18n("");		// How to configure HTTPS...
}


CatalystAdministration::~CatalystAdministration()
{
}


int CatalystAdministration::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	int tempInt = 0;
	bool setting = false;

	// Init
	tempInt = 1;
	if (strcmp(command->part(0), "set") == 0)
		setting = true;
	else
		setting = false;

	// Telnet...
	if ((strcmp(command->part(tempInt), "ip") == 0) && (strcmp(command->part(tempInt + 1), "telnet") == 0) && (strcmp(command->part(tempInt + 2), "server") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sTelnet Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 3;
		if (strcmp(command->part(tempInt), "enable") == 0)
			telnetEnabled = true;
		else
			telnetEnabled = false;
	}

	// HTTP Port...
	else if ((strcmp(command->part(tempInt), "ip") == 0) && (strcmp(command->part(tempInt + 1), "http") == 0) && (strcmp(command->part(tempInt + 2), "port") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sHTTP Server Port Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 3;
		if (strcmp(command->part(tempInt), "default") == 0)
			httpPort = 80;
		else
			httpPort = atoi(command->part(tempInt));
	}

	// HTTP Server...
	else if ((strcmp(command->part(tempInt), "ip") == 0) && (strcmp(command->part(tempInt + 1), "http") == 0) && (strcmp(command->part(tempInt + 2), "server") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sHTTP Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 3;
		if (strcmp(command->part(tempInt), "enable") == 0)
			httpEnabled = true;
		else
			httpEnabled = false;
	}

	else if ((strcmp(command->part(tempInt), "ssh") == 0) && (strcmp(command->part(tempInt + 1), "mode") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSSH Mode Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		sshSupported = true;
		ssh2Supported = true;
		sshEnabled = true;
		tempInt += 2;
		if (strcmp(command->part(tempInt), "v1") == 0)
			sshVersion = 1;
		else
			sshVersion = 2;
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int CatalystAdministration::processDefaults(Device *device)
{
	// SSH Supported...
	if (sshSupported == false)
	{
		if (device->general->versionMajor > 5)
		{
			sshEnabled = true;
			sshSupported = true;					// Does this device support SSH?
		}
		else
			sshUpgrade = true;						// Do you have to upgrade?
	}

	// SSH version 2...
	if (ssh2Supported == false)
	{
		if (device->general->versionMajor > 7)
			ssh2Supported = true;
		else
			ssh2upgrade = true;
	}

	// Default SSH Protocol...
	if ((device->general->versionMajor > 5) && (device->general->versionMajor < 8) && (sshVersion == 0))
		sshVersion = 1;

	return 0;
}



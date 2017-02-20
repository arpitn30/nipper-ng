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
#include "../device/common/configline.h"
#include "device.h"
#include "administration.h"
#include "snmp.h"


SonicOSAdministration::SonicOSAdministration()
{
	sonicosInterfaces = 0;


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
	connectionTimeoutSupported = false;		// Is a connection timeout supported?
	connectionTimeout = 0;					// Connection Timeout
	configTimeout = i18n("");				// The text and commands to configure the timeout

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
	sshVersion = 1;							// What is the SSH Protocol version (0 = 1 and 2)
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
	scpSupported = false;					// Is SCP supported?
	scpEnabled = false;						// Is SCP enabled?

	// SSH 2 support...
	ssh2Supported = false;					// Does the device support SSH version 2?
	ssh2upgrade = false;					// Do you have to upgrade...
	configSSHv2Support = i18n("");			// How to configure protocol version 2 support only

	// Config report SSH support text
	sshConfigProtocolSupport = i18n("");	// Config report text on protocol support (e.g. supports both version 1 and 2 of the protocol)

	// HTTP(S) options...
	httpSupported = true;					// Does this device support HTTP
	httpsSupported = true;					// Does this device support HTTPS
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
}


SonicOSAdministration::~SonicOSAdministration()
{
	// Variables...
	managementInterface *interfacePointer = 0;

	while (sonicosInterfaces != 0)
	{
		interfacePointer = sonicosInterfaces->next;
		delete sonicosInterfaces;
		sonicosInterfaces = interfacePointer;
	}
}


int SonicOSAdministration::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	managementInterface *interfacePointer = 0;

	// HTTP Enabled...
	if (strcmp(command->part(0), "httpEnable") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sHTTP Enable Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (strcmp(command->part(1), "on") == 0)
			httpEnabled = true;
		else
			httpEnabled = false;
	}

	// HTTP Port...
	else if (strcmp(command->part(0), "httpMgmtPort") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sHTTP Port Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (command->parts > 1)
			httpPort = atoi(command->part(1));
		else
			httpPort = 80;
	}

	// HTTPS Enabled...
	else if (strcmp(command->part(0), "httpsEnable") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sHTTPS Enable Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (strcmp(command->part(1), "on") == 0)
			httpsEnabled = true;
		else
			httpsEnabled = false;
	}

	// HTTPS Port...
	else if (strcmp(command->part(0), "httpsMgmtPort") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sHTTPS Port Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (command->parts > 1)
			httpsPort = atoi(command->part(1));
		else
			httpsPort = 443;
	}

	// HTTP Enabled...
	else if (strncmp(command->part(0), "iface_http_mgmt_", 16) == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sInterface HTTP Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		interfacePointer = getInterface(atoi(command->part(0) + 16));
		if (strcmp(command->part(1), "1") == 0)
		{
			interfacePointer->http = true;
			httpEnabled = true;
		}
		else
			interfacePointer->http = false;
	}

	// HTTP USer Login Enabled...
	else if (strncmp(command->part(0), "iface_http_usrLogin_", 20) == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sInterface HTTP Login Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		interfacePointer = getInterface(atoi(command->part(0) + 20));
		if (strcmp(command->part(1), "1") == 0)
			interfacePointer->httpLogin = true;
		else
		{
			interfacePointer->httpLogin = false;
			httpEnabled = false;
		}
	}

	// HTTPS Enabled...
	else if (strncmp(command->part(0), "iface_https_mgmt_", 17) == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sInterface HTTPS Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		interfacePointer = getInterface(atoi(command->part(0) + 17));
		if (strcmp(command->part(1), "1") == 0)
		{
			interfacePointer->https = true;
			httpsEnabled = true;
		}
		else
			interfacePointer->https = false;
	}

	// HTTPS USer Login Enabled...
	else if (strncmp(command->part(0), "iface_https_usrLogin_", 21) == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sInterface HTTPS Login Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		interfacePointer = getInterface(atoi(command->part(0) + 21));
		if (strcmp(command->part(1), "1") == 0)
			interfacePointer->httpsLogin = true;
		else
		{
			interfacePointer->httpsLogin = false;
			httpsEnabled = false;
		}
	}

	// HTTP Redirect Enabled...
	else if (strncmp(command->part(0), "iface_http_redirect_rule_", 25) == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sInterface HTTP Redirect Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		interfacePointer = getInterface(atoi(command->part(0) + 25));
		if (strcmp(command->part(1), "1") == 0)
			interfacePointer->httpRedirect = true;
		else
			interfacePointer->httpRedirect = false;
	}

	// SSH Enabled...
	else if (strncmp(command->part(0), "iface_ssh_mgmt_", 15) == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sInterface SSH Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		interfacePointer = getInterface(atoi(command->part(0) + 15));
		if (strcmp(command->part(1), "1") == 0)
			interfacePointer->ssh = true;
		else
			interfacePointer->ssh = false;
	}

	// SNMP Enabled...
	else if (strncmp(command->part(0), "iface_snmp_mgmt_", 16) == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sInterface SNMP Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		interfacePointer = getInterface(atoi(command->part(0) + 16));
		if (strcmp(command->part(1), "1") == 0)
			interfacePointer->snmp = true;
		else
			interfacePointer->snmp = false;
	}

	// Interface no...
	else if (strncmp(command->part(0), "iface_ifnum_", 12) == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sInterface No. Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		interfacePointer = getInterface(atoi(command->part(0) + 12));
		interfacePointer->interface = atoi(command->part(1));
	}

	// Interface Name...
	else if (strncmp(command->part(0), "iface_name_", 11) == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sInterface Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (command->parts > 1)
		{
			interfacePointer = getInterface(atoi(command->part(0) + 11));
			interfacePointer->name.assign(command->part(1));
		}
	}

	// Interface Comments...
	else if (strncmp(command->part(0), "iface_comment_", 14) == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sInterface Comment Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (command->parts > 1)
		{
			interfacePointer = getInterface(atoi(command->part(0) + 14));
			interfacePointer->comment.assign(strstr(line, command->part(1)));
		}
	}

	// Interface Zone...
	else if (strncmp(command->part(0), "interface_Zone_", 15) == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sInterface Zone Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (command->parts > 1)
		{
			interfacePointer = getInterface(atoi(command->part(0) + 15));
			interfacePointer->zone.assign(strstr(line, command->part(1)));
		}
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int SonicOSAdministration::processDefaults(Device *device)
{
	// Variables...
	managementInterface *interfacePointer = sonicosInterfaces;

	if (strcmp(device->deviceMake, "3Com") == 0)
	{
		httpSupported = true;					// Does this device support HTTP
		httpsSupported = true;					// Does this device support HTTPS
		httpEnabled = true;						// Is the HTTP service enabled?
		httpsEnabled = true;					// Is the HTTPS service enabled?
		disableHTTP = i18n("Unfortunately it is not possible to disable *ABBREV*HTTP*-ABBREV* access to *DEVICETYPE* devices. Therefore *COMPANY* recommends that the firewall is replaced, or if that is not possible, only the *ABBREV*HTTPS*-ABBREV* service should be used for remote administration.");					// How to disable HTTP text...
	}

	else
	{
		if (sonicosInterfaces != 0)
		{
			sshSupported = true;
			if (device->snmp != 0)
				device->snmp->enabled = true;
		}

		while (interfacePointer != 0)
		{
			if ((interfacePointer->http == true) && (interfacePointer->httpRedirect == false))
				httpEnabled = true;
			if (interfacePointer->https == true)
				httpsEnabled = true;
			if (interfacePointer->ssh == true)
				sshEnabled = true;
			interfacePointer = interfacePointer->next;
		}
	}

	return 0;
}


SonicOSAdministration::managementInterface *SonicOSAdministration::getInterface(int number)
{
	// Variables...
	managementInterface *interfacePointer = sonicosInterfaces;
	bool init = false;

	if (sonicosInterfaces == 0)
	{
		sonicosInterfaces = new (managementInterface);
		interfacePointer = sonicosInterfaces;
		init = true;
	}
	else
	{
		interfacePointer = sonicosInterfaces;
		while (interfacePointer->next != 0)
		{
			if (interfacePointer->interface == number)
				return interfacePointer;
			interfacePointer = interfacePointer->next;
		}
		if (interfacePointer->interface != number)
		{
			interfacePointer->next = new (managementInterface);
			interfacePointer = interfacePointer->next;
			init = true;
		}
	}

	if (init == true)
	{
		// Init...
		interfacePointer->interface = 0;
		interfacePointer->http = false;
		interfacePointer->httpLogin = false;
		interfacePointer->httpRedirect = false;
		interfacePointer->https = false;
		interfacePointer->httpsLogin = false;
		interfacePointer->ssh = false;
		interfacePointer->snmp = false;
		interfacePointer->next = 0;
	}

	return interfacePointer;
}


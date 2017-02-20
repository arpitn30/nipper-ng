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
#include "general.h"
#include "administration.h"


ScreenOSAdministration::ScreenOSAdministration()
{
	interfaces = 0;
	consolePageBreaks = 22;
	sshUsed = false;
	scsUsed = false;
	globalProUsed = false;
	nsmgmtUsed = false;
	mtraceUsed = false;


	// -----------------------------------------------------------------------
	// Device Specific Settings...
	// -----------------------------------------------------------------------

	// General...
	generalSettings = true;					// Show the general settings section?
	consoleEnabled = true;					// Is the Console port enabled?
	consoleSupported = true;				// Is a console port supported?
	//consoleTimeoutSupported = true;		// Is a console timeout supported?
	//consoleTimeout = 600;					// Console timeout
	//configConsoleTimeout = i18n("");		// The text and commands to configure the timeout
	auxSupported = true;					// Are AUX port(s) supported?
	auxEnabled = true;						// Is AUX port(s) enabled?
	configAuxPort = i18n("The *ABBREV*AUX*-ABBREV* port can be disabled on *DEVICENAME* with the following command:*CODE**COMMAND*set console aux disable*-COMMAND**-CODE*");
	connectionTimeoutSupported = true;		// Is a connection timeout supported?
	connectionTimeout = 600;				// Connection Timeout
	configTimeout = i18n("The console timeout setting is used to timeout idle connections to *DEVICETYPE* devices using the console port, Telnet or *ABBREV*SSH*-ABBREV*. The timeout can be configured with the following command:*CODE**COMMAND*set console timeout *CMDUSER*timeout-minutes*-CMDUSER**-COMMAND**-CODE*");				// The text and commands to configure the timeout

	// Host restrictions...
	serviceWideHosts = true;				// Do all the admin services share a common host restrictions?
	showHostInterface = false;				// Show the Interface column in the host table?
	showHostAccess = false;					// Show the Access column in the host table?
	serviceConfigHosts = i18n("Management host restrictions to *DEVICETYPE* devices can be configured with the following command:*CODE**COMMAND*set admin manager-ip *CMDUSER*ip-address*-CMDUSER* *CMDOPTION**CMDUSER*netmask*-CMDUSER**-CMDOPTION**-COMMAND**-CODE*");			// Text, how to configure administrative host restrictions.

	// Telnet options...
	telnetSupported = true;					// Is telnet supported?
	telnetEnabled = true;					// Is Telnet enabled?
	telnetPort = 23;						// The telnet service port
	disableTelnet = i18n("The Telnet service can be disabled on individual interfaces using the following command:*CODE**COMMAND*unset interface *CMDUSER*interface*-CMDUSER* manage telnet*-COMMAND**-CODE*");				// How to disable telnet text...

	// SSH options...
	sshSupported = false;					// Does this device support SSH?
	sshUpgrade = false;						// Do you have to upgrade?
	sshEnabled = true;						// Is the SSH service enabled?
	sshVersion = 0;							// What is the SSH Protocol version (0 = 1 and 2)
	sshPort = 22;							// The SSH port number
	configSSHSupport = i18n("*ABBREV*SSH*-ABBREV* can be enabled on individual interfaces using the following command:*CODE**COMMAND*set interface *CMDUSER*interface*-CMDUSER* manage ssh*-COMMAND**-CODE*");			// How to configure SSH...

	// SSH Options
	scpSupported = false;					// Is SCP supported?
	scpEnabled = false;						// Is SCP enabled?

	// SSH 2 support...
	ssh2Supported = false;					// Does the device support SSH version 2?
	configSSHv2Support = i18n("*ABBREV*SSH*-ABBREV* protocol version 2 can be configured using the following command:*CODE**COMMAND*set ssh version v2*-COMMAND**-CODE*");			// How to configure protocol version 2 support only

	// Config report SSH support text
	sshConfigProtocolSupport = i18n("*DEVICETYPE* devices have supported *ABBREV*SSH*-ABBREV* protocol versions 1 and 2 from *DEVICEOS* 5.");	// Config report text on protocol support (e.g. supports both version 1 and 2 of the protocol)

	// HTTP(S) options...
	httpSupported = true;					// Does this device support HTTP
	httpsSupported = true;					// Does this device support HTTPS
	httpsUpgrade = false;					// Do you have to upgrade for HTTPS?
	httpEnabled = true;						// Is the HTTP service enabled?
	httpPort = 80;							// HTTP port
	httpsEnabled = true;					// Is the HTTPS service enabled?
	httpsPort = 443;						// HTTPS port
	httpsRedirect = false;					// Is HTTP to HTTPS redirect enabled?
	httpLabel = i18n("*ABBREV*HTTP*-ABBREV*");		// The label given to the HTTP service (e.g. HTTP)
	httpsLabel = i18n("*ABBREV*HTTPS*-ABBREV*");	// The label given to the HTTPS service (e.g. HTTPS)
	disableHTTP = i18n("*ABBREV*HTTP*-ABBREV* is disabled on individual interfaces, or from *DEVICEOS* 5, *ABBREV*HTTP*-ABBREV* can be redirected to *ABBREV*HTTPS*-ABBREV*. *ABBREV*HTTP*-ABBREV* can be disabled on interfaces with the following command:*CODE**COMMAND*unset interface *CMDUSER*interface*-CMDUSER* manage web*-COMMAND**-CODE*");					// How to disable HTTP text...
	configHTTPSSupport = i18n("*ABBREV*HTTPS*-ABBREV* can be enabled with the following commands:*CODE**COMMAND*set ssl enable*-COMMAND**COMMAND*set interface *CMDUSER*interface*-CMDUSER* manage ssl*-COMMAND**-CODE*");			// How to configure HTTPS...
	cipherConfigSupported = true;			// Can the Ciphers be configured?
	configCipherText = i18n("The 168 bit key length *ABBREV*3DES*-ABBREV*-*ABBREV*SHA1*-ABBREV* cipher can be configured with the following command:*CODE**COMMAND*set ssl encrypt 3des sha-1*-COMMAND**-CODE*");			// The text to configure a strong cipher.
}


ScreenOSAdministration::~ScreenOSAdministration()
{
	// Variables...
	interfaceManagementConfig *interfacePointer = 0;

	// Delete interfaces...
	while (interfaces != 0)
	{
		interfacePointer = interfaces->next;
		delete interfaces;
		interfaces = interfacePointer;
	}
}


int ScreenOSAdministration::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	interfaceManagementConfig *interfacePointer = 0;
	cipherConfig *cipherPointer = 0;
	hostFilter *hostPointer = 0;
	bool setting = false;
	int errorCode = 0;

	// Init
	if (strcasecmp(command->part(0), "unset") == 0)
		setting = false;
	else if (strcasecmp(command->part(0), "set") == 0)
		setting = true;

	// Interfaces...
	if (strcasecmp(command->part(1), "interface") == 0)
	{

		// Zone
		if (strcasecmp(command->part(3), "zone") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sInterface Zone Line (Admin):%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			addInterfaceZone(command->part(2), command->part(4));
		}

		// disable
		else if ((strcasecmp(command->part(3), "disable") == 0) || (strcasecmp(command->part(3), "shutdown") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sInterface Disable Line (Admin):%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			interfacePointer = getInterface(command->part(2));
			interfacePointer->enabled = false;
		}

		// manage
		else if (strcasecmp(command->part(3), "manage") == 0)
		{

			// SSH
			if (strcasecmp(command->part(4), "ssh") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sInterface SSH Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				sshUsed = true;
				interfacePointer = getInterface(command->part(2));
				interfacePointer->ssh = setting;
			}

			// SSL
			else if (strcasecmp(command->part(4), "ssl") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sInterface SSL Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				interfacePointer = getInterface(command->part(2));
				interfacePointer->ssl = setting;
			}

			// Telnet
			else if (strcasecmp(command->part(4), "telnet") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sInterface Telnet Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				interfacePointer = getInterface(command->part(2));
				interfacePointer->telnet = setting;
			}

			// Web
			else if (strcasecmp(command->part(4), "web") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sInterface Web Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				interfacePointer = getInterface(command->part(2));
				interfacePointer->web = setting;
			}

			// Ping
			else if (strcasecmp(command->part(4), "ping") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sInterface Ping Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				interfacePointer = getInterface(command->part(2));
				interfacePointer->ping = setting;
			}

			// snmp
			else if (strcasecmp(command->part(4), "snmp") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sInterface SNMP Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				interfacePointer = getInterface(command->part(2));
				interfacePointer->snmp = setting;
			}

			// mtrace
			else if (strcasecmp(command->part(4), "mtrace") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sInterface mtrace Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				mtraceUsed = true;
				interfacePointer = getInterface(command->part(2));
				interfacePointer->mtrace = setting;
			}

			// ident-reset
			else if (strcasecmp(command->part(4), "ident-reset") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sInterface ident-reser Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				interfacePointer = getInterface(command->part(2));
				interfacePointer->identReset = setting;
			}

			// NSMGMT
			else if (strcasecmp(command->part(4), "nsmgmt") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sInterface NSMGMT Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				nsmgmtUsed = true;
				interfacePointer = getInterface(command->part(2));
				interfacePointer->nsmgmt = setting;
			}

			// SCS
			else if (strcasecmp(command->part(4), "scs") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sInterface SCS Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				scsUsed = true;
				interfacePointer = getInterface(command->part(2));
				interfacePointer->scs = setting;
			}

			// Global Pro
			else if (strcasecmp(command->part(4), "global-pro") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sInterface Global Pro Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				globalProUsed = true;
				interfacePointer = getInterface(command->part(2));
				interfacePointer->globalPro = setting;
			}

			// All others...
			else
				device->lineNotProcessed(line);
		}

		// All others...
		else
			device->lineNotProcessed(line);
	}

	// admin
	else if (strcasecmp(command->part(1), "admin") == 0)
	{

		// HTTP Redirect...
		if ((strcasecmp(command->part(2), "http") == 0) && (strcasecmp(command->part(3), "redirect") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sAdmin HTTP Redirect Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			httpsRedirect = setting;
		}

		// Telnet Port...
		else if ((strcasecmp(command->part(2), "telnet") == 0) && (strcasecmp(command->part(3), "port") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sAdmin Telnet Port Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			if (setting == true)
				telnetPort = atoi(command->part(4));
		}

		// SSH Port...
		else if ((strcasecmp(command->part(2), "ssh") == 0) && (strcasecmp(command->part(3), "password") == 0) && (strcasecmp(command->part(4), "port") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sAdmin SSH Port Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			sshUsed = true;
			if (setting == true)
				sshPort = atoi(command->part(5));
		}

		// Manager IP...
		else if (strcasecmp(command->part(2), "manager-ip") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sAdmin Host IP Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			if (setting == true)
			{
				hostPointer = addHostFilter(allServices);
				hostPointer->host.assign(command->part(3));
				hostPointer->netmask.assign(command->part(4));
			}
		}

		// All others...
		else
			device->lineNotProcessed(line);
	}

	// Console
	else if (strcasecmp(command->part(1), "console") == 0)
	{

		// Timeout...
		if (strcasecmp(command->part(2), "timeout") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sConsole Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			if (setting == true)
				connectionTimeout = atoi(command->part(3)) * 60;
		}

		// console disable...
		else if (strcasecmp(command->part(2), "disable") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sConsole Disable Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			if (setting == true)
				consoleEnabled = false;
			else
				consoleEnabled = true;
		}

		// console page...
		else if (strcasecmp(command->part(2), "page") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sConsole Page Lines Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			if (setting == true)
				consolePageBreaks = atoi(command->part(3));
			else
				consolePageBreaks = 22;
		}

		// AUX disable...
		else if ((strcasecmp(command->part(2), "aux") == 0) && (strcasecmp(command->part(3), "disable") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sConsole AUX Disable Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			if (setting == true)
				auxEnabled = false;
			else
				auxEnabled = true;
		}

		// All others...
		else
			device->lineNotProcessed(line);
	}

	// SSL
	else if (strcasecmp(command->part(1), "ssl") == 0)
	{

		// SSL enable...
		if (strcasecmp(command->part(2), "enable") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sSSL Enable Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			httpsEnabled = setting;
		}

		// SSL port...
		if (strcasecmp(command->part(2), "port") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sSSL Port Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			if (setting == true)
				httpsPort = atoi(command->part(3));
		}

		// SSL encrypt...
		if (strcasecmp(command->part(2), "encrypt") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sSSL Encrypt Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			if (setting == true)
			{
				cipherPointer = addCipher();

				if (strcasecmp(command->part(3), "des") == 0)
				{
					cipherPointer->encryption.assign("*ABBREV*DES*-ABBREV*");
					cipherPointer->bits = 56;
					cipherPointer->ssl3 = true;
					cipherPointer->tls1 = true;
				}
				else if (strcasecmp(command->part(3), "3des") == 0)
				{
					cipherPointer->encryption.assign("*ABBREV*3DES*-ABBREV*");
					cipherPointer->bits = 168;
					cipherPointer->ssl3 = true;
					cipherPointer->tls1 = true;
				}
				else if (strcasecmp(command->part(3), "rc4-40") == 0)
				{
					cipherPointer->encryption.assign("*ABBREV*RC4*-ABBREV*-40");
					cipherPointer->bits = 40;
					cipherPointer->ssl2 = true;
					cipherPointer->ssl3 = true;
					cipherPointer->tls1 = true;
				}
				else if (strcasecmp(command->part(3), "rc4") == 0)
				{
					cipherPointer->encryption.assign("*ABBREV*RC4*-ABBREV*");
					cipherPointer->bits = 128;
					cipherPointer->ssl2 = true;
					cipherPointer->ssl3 = true;
					cipherPointer->tls1 = true;
				}

				if (strcasecmp(command->part(4), "sha-1") == 0)
					cipherPointer->authenticaton.assign("*ABBREV*SHA1*-ABBREV*");
				else if (strcasecmp(command->part(4), "md5") == 0)
					cipherPointer->authenticaton.assign("*ABBREV*MD5*-ABBREV*");
			}
		}

		// All others...
		else
			device->lineNotProcessed(line);
	}

	// SSH
	else if (strcasecmp(command->part(1), "ssh") == 0)
	{
		sshUsed = true;

		// Enabled...
		if (strcasecmp(command->part(2), "enable") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sSSH Enabled Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			sshEnabled = setting;
		}

		// Version...
		else if (strcasecmp(command->part(2), "version") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sSSH Version Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			if (strcasecmp(command->part(3), "v1") == 0)
				sshVersion = 1;
			else
				sshVersion = 2;
		}

		// All others...
		else
			device->lineNotProcessed(line);
	}

	// SCP
	else if ((strcasecmp(command->part(1), "scp") == 0) && (strcasecmp(command->part(2), "enable") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sSCP Enable Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		sshUsed = true;
		scpEnabled = setting;
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return errorCode;
}


int ScreenOSAdministration::processDefaults(Device *device)
{
	// Variables...
	interfaceManagementConfig *interfacePointer = 0;
	cipherConfig *cipherPointer = 0;
	bool ssh = false;
	bool telnet = false;
	bool https = false;
	bool http = false;

	// SSH Used?
	if ((sshUsed == true) || (device->general->versionMajor > 4))
	{
		sshSupported = true;
		ssh2Supported = true;
		scpSupported = true;
	}

	// Enable/Disable services...
	interfacePointer = interfaces;
	while (interfacePointer != 0)
	{
		if (interfacePointer->enabled == true)
		{
			if (interfacePointer->ssh == true)
				ssh = true;
			if (interfacePointer->telnet == true)
				telnet = true;
			if (interfacePointer->ssl == true)
				https = true;
			if (interfacePointer->web == true)
				http = true;
		}
		interfacePointer = interfacePointer->next;
	}

	// Switch off services
	if (ssh == false)
		sshEnabled = false;
	if (http == false)
		httpEnabled = false;
	if (https == false)
		httpsEnabled = false;
	if (telnet == false)
		telnetEnabled = false;

	// If no ciphers have been configured...
	if ((httpsEnabled == true) && (ciphers == 0))
	{
		cipherPointer = addCipher();
		cipherPointer->encryption.assign("*ABBREV*RC4*-ABBREV*");
		cipherPointer->bits = 128;
		cipherPointer->ssl2 = true;
		cipherPointer->ssl3 = true;
		cipherPointer->tls1 = true;
		cipherPointer->authenticaton.assign("*ABBREV*MD5*-ABBREV*");
	}

	return 0;
}


ScreenOSAdministration::interfaceManagementConfig *ScreenOSAdministration::getInterface(const char *interface)
{
	// Variables...
	interfaceManagementConfig *interfacePointer = 0;

	// Create...
	if (interfaces == 0)
	{
		interfaces = new (interfaceManagementConfig);
		interfacePointer = interfaces;
	}
	else
	{
		interfacePointer = interfaces;
		while (interfacePointer->next != 0)
		{
			if (interfacePointer->interface.compare(interface) == 0)
				return interfacePointer;
			interfacePointer = interfacePointer->next;
		}
		interfacePointer->next = new (interfaceManagementConfig);
		interfacePointer = interfacePointer->next;
	}

	// Init...
	interfacePointer->interface.assign(interface);
	interfacePointer->enabled = true;
	interfacePointer->nsmgmt = false;
	interfacePointer->ssh = false;
	interfacePointer->ssl = false;
	interfacePointer->telnet = false;
	interfacePointer->ping = false;
	interfacePointer->mtrace = false;
	interfacePointer->identReset = false;
	interfacePointer->web = false;
	interfacePointer->snmp = false;
	interfacePointer->next = 0;

	return interfacePointer;
}


int ScreenOSAdministration::addInterfaceZone(const char *interface, const char *zone)
{
	// Variables...
	interfaceManagementConfig *interfacePointer = 0;

	// Create...
	if (interfaces == 0)
	{
		interfaces = new (interfaceManagementConfig);
		interfacePointer = interfaces;
	}
	else
	{
		interfacePointer = interfaces;
		while (interfacePointer->next != 0)
			interfacePointer = interfacePointer->next;
		interfacePointer->next = new (interfaceManagementConfig);
		interfacePointer = interfacePointer->next;
	}

	// Init...
	interfacePointer->interface.assign(interface);
	interfacePointer->zone.assign(zone);
	interfacePointer->enabled = true;
	if ((strcasecmp(zone, "Trust") == 0) || (strcasecmp(zone, "vlan1") == 0) || (strcasecmp(zone, "V1-Trust") == 0))
	{
		interfacePointer->nsmgmt = true;
		interfacePointer->ssh = true;
		interfacePointer->ssl = true;
		interfacePointer->telnet = true;
		interfacePointer->ping = true;
		interfacePointer->mtrace = false;
		interfacePointer->identReset = false;
		interfacePointer->web = true;
		interfacePointer->snmp = true;
	}
	else if ((strcasecmp(zone, "DMZ") == 0) || (strcasecmp(zone, "V1-DMZ") == 0))
	{
		interfacePointer->nsmgmt = false;
		interfacePointer->ssh = false;
		interfacePointer->ssl = false;
		interfacePointer->telnet = false;
		interfacePointer->ping = true;
		interfacePointer->mtrace = false;
		interfacePointer->identReset = false;
		interfacePointer->web = false;
		interfacePointer->snmp = false;
	}
	else
	{
		interfacePointer->nsmgmt = false;
		interfacePointer->ssh = false;
		interfacePointer->ssl = false;
		interfacePointer->telnet = false;
		interfacePointer->ping = false;
		interfacePointer->mtrace = false;
		interfacePointer->identReset = false;
		interfacePointer->web = false;
		interfacePointer->snmp = false;
	}
	interfacePointer->next = 0;

	return 0;
}

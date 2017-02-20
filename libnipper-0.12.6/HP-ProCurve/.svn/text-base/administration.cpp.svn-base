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


ProCurveAdministration::ProCurveAdministration()
{

	// -----------------------------------------------------------------------
	// Device Specific Settings...
	// -----------------------------------------------------------------------

	// General...
	generalSettings = true;					// Show the general settings section?
	consoleEnabled = true;					// Is the Console port enabled?
	consoleSupported = true;				// Is a console port supported?
	consoleTimeoutSupported = false;		// Is a console timeout supported?
	consoleTimeout = 0;						// Console timeout
	configConsoleTimeout = i18n("");		// The text and commands to configure the timeout
	connectionTimeoutSupported = true;		// Is a connection timeout supported?
	connectionTimeout = 0;					// Connection Timeout
	configTimeout = i18n("An inactivity timeout can be configured with the following command:*CODE**COMMAND*console inactivity-timer *CMDUSER*timeout-minutes*-CMDUSER**-COMMAND**-CODE*");				// The text and commands to configure the timeout

	// Host restrictions...
	serviceWideHosts = true;				// Do all the admin services share a common host restrictions?
	showHostAccess = true;					// Show the Access column in the host table?
	serviceConfigHosts = i18n("Management hosts can be configured with the following command:*CODE**COMMAND*ip authorized-managers *CMDUSER*ip-address*-CMDUSER* *CMDUSER*netmask*-CMDUSER**-COMMAND**-CODE*");			// Text, how to configure administrative host restrictions.

	// Telnet options...
	telnetSupported = true;					// Is telnet supported?
	telnetEnabled = true;					// Is Telnet enabled?
	telnetPort = 23;						// The telnet service port
	telnetHostsRequired = true;				// Is the host configuration required?
	disableTelnet = i18n("The Telnet service can be disabled on *DEVICETYPE* devices with the following command:*CODE*no telnet-server*-CODE*");				// How to disable telnet text...

	// TFTP options...
	tftpSupported = true;					// Is TFTP supported?
	tftpEnabled = true;						// Is TFTP enabled?
	tftpPort = 69;							// The TFTP service port
	tftpSpecificHost = false;				// Does TFTP have its own access list?
	tftpHostsRequired = false;				// Is the host configuration required?
	showTFTPHostInterface = false;			// Show the Interface column in the host table?
	configTFTPHostAccess = i18n("");		// How access lists are configured for the TFTP service
	disableTFTP = i18n("The *ABBREV*TFTP*-ABBREV* service can be disabled on *DEVICETYPE* devices with the following command:*CODE**COMMAND*no tftp server*-COMMAND**-CODE*");					// How to disable TFTP text...

	// SSH options...
	sshSupported = true;					// Does this device support SSH?
	sshUpgrade = false;						// Do you have to upgrade?
	sshEnabled = false;						// Is the SSH service enabled?
	sshVersion = 2;							// What is the SSH Protocol version (0 = 1 and 2)
	sshPort = 22;							// The SSH port number
	configSSHSupport = i18n("The *ABBREV*SSH*-ABBREV* service can be enabled on *DEVICETYPE* devices with the following command:*CODE**COMMAND*ip ssh*-COMMAND**-CODE*");			// How to configure SSH...
	sshHostsRequired = true;				// Is the host configuration required?

	sftpEnabled = false;					// Is SFTP enabled?
	sftpSupported = true;					// Is SFTP supported?
	configSFTP = i18n("*ABBREV*SFTP*-ABBREV* can be enabled on *DEVICETYPE* devices with the following command:*CODE**COMMAND*ip ssh filetransfer*-COMMAND**-CODE*");							// Text and commands to configure SFTP
	scpSupported = true;					// Is SCP supported?
	scpEnabled = false;						// Is SCP enabled?

	// SSH 2 support...
	ssh2Supported = true;					// Does the device support SSH version 2?
	ssh2upgrade = false;					// Do you have to upgrade...
	configSSHv2Support = i18n("");			// How to configure protocol version 2 support only

	// Config report SSH support text
	sshConfigProtocolSupport = i18n("");	// Config report text on protocol support (e.g. supports both version 1 and 2 of the protocol)

	// HTTP(S) options...
	httpSupported = true;					// Does this device support HTTP
	httpsSupported = true;					// Does this device support HTTPS
	httpsUpgrade = false;					// Do you have to upgrade for HTTPS?
	httpEnabled = true;						// Is the HTTP service enabled?
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
	configHTTPHostAccess = i18n("");		// How to configure HTTP Management hosts...
	disableHTTP = i18n("");					// How to disable HTTP text...
	configHTTPSSupport = i18n("");			// How to configure HTTPS...

	// HP Procurve specific settings...
	consoleBaudRate = 0;					// The console line baud rate
	consoleFlowXONControl = true;			// Flow Control 0 = none, 1 = XON, 2 = XOFF
	consoleLocalType = 0;					// 0 = VT100, 1 = none, 2 = ANSI
	consoleAllType = 0;						// 0 = VT100, 1 = none, 2 = ANSI
	telnet6ServerEnabled = true;			// Telnet IPv6 Server
	tftp6ServerEnabled = true;				// TFTP IPv6 Server
	sshIPProtocol = 0;						// SSH IP (0 = 4 & 6, 4 = 4, 6 =6)
}


int ProCurveAdministration::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	hostFilter *hostPointer = 0;
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

	// Console...
	if (strcmp(command->part(tempInt), "console") == 0)
	{
		tempInt++;

		// timeout...
		if (strcmp(command->part(tempInt), "console") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sConsole Timeout Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			tempInt++;
			connectionTimeout = atoi(command->part(tempInt));
			if (connectionTimeout != 0)
				connectionTimeout = connectionTimeout * 60;
		}

		// baud rate
		else if (strcmp(command->part(tempInt), "baud-rate") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sConsole Baud Rate Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			tempInt++;
			if (strcmp(command->part(tempInt), "speed-sense") == 0)
				consoleBaudRate = 0;
			else
				consoleBaudRate = atoi(command->part(tempInt));
		}

		// flow control
		else if (strcmp(command->part(tempInt), "flow-control") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sFlow Control Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			tempInt++;
			if (strcasecmp(command->part(tempInt), "none") == 0)
				consoleFlowXONControl = false;
			else
				consoleFlowXONControl = true;
		}

		// local terminal
		else if (strcmp(command->part(tempInt), "local-terminal") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sLocal Terminal Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			tempInt++;
			if (strcasecmp(command->part(tempInt), "none") == 0)
				consoleLocalType = 1;
			else if (strcasecmp(command->part(tempInt), "ansi") == 0)
				consoleLocalType = 2;
			else
				consoleLocalType = 0;
		}

		// terminal
		else if (strcmp(command->part(tempInt), "terminal") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sTerminal Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			tempInt++;
			if (strcasecmp(command->part(tempInt), "none") == 0)
				consoleLocalType = 1;
			else if (strcasecmp(command->part(tempInt), "ansi") == 0)
				consoleLocalType = 2;
			else
				consoleLocalType = 0;
			consoleAllType = consoleLocalType;
		}

		// All others...
		else
			device->lineNotProcessed(line);
	}

	// Web Management...
	else if (strcmp(command->part(tempInt), "web-management") == 0)
	{
		tempInt++;

		// Management URL
		if (strcmp(command->part(tempInt), "management-url") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sWeb Manage URL Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			tempInt++;
			webManagementURL.assign(command->part(tempInt));
		}

		// Support URL
		else if (strcmp(command->part(tempInt), "support-url") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sWeb Support URL Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			tempInt++;
			webSupportURL.assign(command->part(tempInt));
		}

		// HTTP
		else if ((strcmp(command->part(tempInt), "plaintext") == 0) || (tempInt == command->parts))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sWeb Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			httpEnabled = setting;
		}

		// HTTPS
		else if (strcmp(command->part(tempInt), "ssl") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sWeb Secure Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			httpsEnabled = setting;
			tempInt++;
			if (tempInt < command->parts)
				httpsPort = atoi(command->part(tempInt));
		}

		// All others...
		else
			device->lineNotProcessed(line);
	}

	// Telnet...
	else if (strcmp(command->part(tempInt), "telnet-server") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sTelnet Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		telnetEnabled = setting;
	}

	// Telnet IPv6...
	else if (strcmp(command->part(tempInt), "telnet6-server") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sTelnet IPv6 Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		telnet6ServerEnabled = setting;
	}

	// TFTP Server...
	else if ((strcmp(command->part(tempInt), "tftp") == 0) && (strcmp(command->part(tempInt + 1), "server") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sTFTP Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tftpEnabled = setting;
	}

	// TFTP6 Server...
	else if ((strcmp(command->part(tempInt), "tftp6") == 0) && (strcmp(command->part(tempInt + 1), "server") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sTFTP 6 Server Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tftp6ServerEnabled = setting;
	}

	else if (strcmp(command->part(tempInt), "ip") == 0)
	{
		tempInt++;

		// Authorised Managers...
		if (strcmp(command->part(tempInt), "authorized-managers") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sManagement Host Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			hostPointer = addHostFilter(allServices);
			hostPointer->access.assign("manager");
			tempInt++;
			hostPointer->host.assign(command->part(tempInt));
			tempInt++;
			while (tempInt < command->parts)
			{
				if (strcmp(command->part(tempInt), "access") == 0)
				{
					tempInt++;
					hostPointer->access.assign(command->part(tempInt));
				}
				else
					hostPointer->netmask.assign(command->part(tempInt));
				tempInt++;
			}
		}

		// SSH
		else if (strcmp(command->part(tempInt), "ssh") == 0)
		{
			tempInt++;

			// filetransfer
			if (strcmp(command->part(tempInt), "filetransfer") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sSSH SCP/SFTP Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				if (setting == true)
				{
					sftpEnabled = true;
					scpEnabled = true;
					tftpEnabled = false;
					tftp6ServerEnabled = false;
				}
				else
				{
					sftpEnabled = false;
					scpEnabled = false;
				}
			}

			// Port
			else if (strcmp(command->part(tempInt), "port") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sSSH Port Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				tempInt++;
				if (strcmp(command->part(tempInt), "default") == 0)
					sshPort = 22;
				else
					sshPort = atoi(command->part(tempInt));
			}

			// SSH IP protocol version
			else if (strcmp(command->part(tempInt), "ip-version") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sSSH IP Protocol Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				tempInt++;
				if (strcmp(command->part(tempInt), "4or6") == 0)
					sshIPProtocol = 0;
				else if (command->part(tempInt)[0] == '4')
					sshIPProtocol = 4;
				else
					sshIPProtocol = 6;
			}

			// SSH
			else if (command->parts == tempInt)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sSSH Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				sshEnabled = setting;
			}

			// All others...
			else
				device->lineNotProcessed(line);
		}

		// All others...
		else
			device->lineNotProcessed(line);
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int ProCurveAdministration::processDefaults(Device *device)
{
	// No administrative hosts?
	if (serviceHosts == 0)
	{
		telnetEnabled = false;
		sshEnabled = false;
	}

	return 0;
}


int ProCurveAdministration::generateDeviceGeneralConfig(Device *device)
{
	// Variables...
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;

	// Get Paragraph Pointer...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-ADMINGENERAL-TABLE");

	// Type...
	device->addTableData(paragraphPointer->table, i18n("Console type"));
	switch (consoleLocalType)
	{
		case 1:
			device->addTableData(paragraphPointer->table, i18n("None"));
			break;
		case 2:
			device->addTableData(paragraphPointer->table, i18n("*ABBREV*ANSI*-ABBREV*"));
			break;
		default:
			device->addTableData(paragraphPointer->table, i18n("VT100"));
			break;
	}

	// Speed...
	device->addTableData(paragraphPointer->table, i18n("Console data transmission speed"));
	if (consoleBaudRate == 0)
		device->addTableData(paragraphPointer->table, i18n("Auto"));
	else
	{
		tempString.assign(device->intToString(consoleBaudRate));
		device->addTableData(paragraphPointer->table, tempString.c_str());
	}

	// Control
	device->addTableData(paragraphPointer->table, i18n("Flow Control"));
	if (consoleFlowXONControl == true)
		device->addTableData(paragraphPointer->table, i18n("XON/XOFF"));
	else
		device->addTableData(paragraphPointer->table, i18n("None"));

	return 0;
}


int ProCurveAdministration::generateDeviceTelnetConfig(Device *device)
{
	// Variables...
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;

	paragraphPointer = device->getTableParagraphPointer("CONFIG-SERVICES-TABLE");
	device->addTableData(paragraphPointer->table, i18n("Telnet *ABBREV*IPv6*-ABBREV* Service"));
	if (telnet6ServerEnabled == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));

	// Get Paragraph Pointer...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-ADMINTELNET-TABLE");

	// IP Protocol Versions...
	device->addTableData(paragraphPointer->table, i18n("Telnet *ABBREV*IPv6*-ABBREV* service"));
	if (telnet6ServerEnabled == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));

	return 0;
}


int ProCurveAdministration::generateDeviceHTTPConfig(Device *device)
{
	// Variables...
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;

	// Get Paragraph Pointer...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-ADMINHTTP-TABLE");

	// URLs
	if (!webManagementURL.empty())
	{
		device->addTableData(paragraphPointer->table, i18n("Management *ABBREV*URL*-ABBREV*"));
		device->addTableData(paragraphPointer->table, webManagementURL.c_str());
	}
	if (!webSupportURL.empty())
	{
		device->addTableData(paragraphPointer->table, i18n("Support *ABBREV*URL*-ABBREV*"));
		device->addTableData(paragraphPointer->table, webSupportURL.c_str());
	}

	return 0;
}


int ProCurveAdministration::generateDeviceTFTPConfig(Device *device)
{
	// Variables...
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;

	paragraphPointer = device->getTableParagraphPointer("CONFIG-SERVICES-TABLE");
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*TFTP*-ABBREV* *ABBREV*IPv6*-ABBREV* Service"));
	if (tftp6ServerEnabled == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));

	// Get Paragraph Pointer...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-ADMINTFTP-TABLE");

	// IP Protocol Versions...
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*TFTP*-ABBREV* *ABBREV*IPv6*-ABBREV* service"));
	if (tftp6ServerEnabled == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));

	return 0;
}


int ProCurveAdministration::generateDeviceSSHConfig(Device *device)
{
	// Variables...
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;

	// Get Paragraph Pointer...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-ADMINSSH-TABLE");

	// IP Protocol Versions...
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*IP*-ABBREV* protocol version(s)"));
	switch (sshIPProtocol)
	{
		case 4:
			device->addTableData(paragraphPointer->table, i18n("*ABBREV*IPv4*-ABBREV*"));
			break;
		case 6:
			device->addTableData(paragraphPointer->table, i18n("*ABBREV*IPv6*-ABBREV*"));
			break;
		default:
			device->addTableData(paragraphPointer->table, i18n("*ABBREV*IPv4*-ABBREV* and *ABBREV*IPv6*-ABBREV*"));
			break;
	}

	return 0;
}

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
#include "general.h"
#include "administration.h"


CiscoCSSAdministration::CiscoCSSAdministration()
{
	// General...
	generalSettings = true;					// Show the general settings section?
	consoleEnabled = false;					// Is the Console port enabled?
	consoleSupported = true;				// Is a console port supported?
	//consoleTimeoutSupported = false;		// Is a console timeout supported?
	//consoleTimeout = 0;					// Console timeout
	//configConsoleTimeout = i18n("");		// The text and commands to configure the timeout
	connectionTimeoutSupported = true;		// Is a connection timeout supported?
	connectionTimeout = 0;					// Connection Timeout
	configTimeout = i18n("The Console, *ABBREV*FTP*-ABBREV*, *ABBREV*SSH*-ABBREV* and Telnet connection timeout can be configured on *DEVICETYPE* with the following command:*CODE**COMMAND*idle timeout *CMDUSER*timeout-minutes*-CMDUSER**-COMMAND**-CODE*");				// The text and commands to configure the timeout

	// Host restrictions...
	//serviceWideHosts = false;				// Do all the admin services share a common host restrictions?
	//serviceConfigHosts = i18n("");		// Text, how to configure administrative host restrictions.

	// Telnet options...
	telnetSupported = true;					// Is telnet supported?
	telnetEnabled = true;					// Is Telnet enabled?
	telnetPort = 23;						// The telnet service port
	//telnetSpecificHost = false;			// Does Telnet have its own access list?
	//telnetHostsRequired = false;			// Is the host configuration required?
	//configTelnetHostAccess = i18n("");	// How access lists are configured for the telnet service
	disableTelnet = i18n("The Telnet service can be disabled on *DEVICETYPE* devices with the following command:*CODE**COMMAND*restrict telnet*-COMMAND**-CODE*");				// How to disable telnet text...
	//telnetSpecificTimeout = false;		// A Telnet Specific Timeout?
	//telnetTimeout = 0;					// The Telnet Timeout (secs)
	//configTelnetTimeout = i18n("");		// The text and commands to configure the timeout

	// TFTP options...
	tftpSupported = false;					// Is TFTP supported?
	//tftpEnabled = false;					// Is TFTP enabled?
	//tftpPort = 69;						// The TFTP service port
	//tftpSpecificHost = false;				// Does TFTP have its own access list?
	//tftpHostsRequired = false;			// Is the host configuration required?
	//configTFTPHostAccess = i18n("");		// How access lists are configured for the TFTP service
	//disableTFTP = i18n("");				// How to disable TFTP text...

	// FTP options...
	ftpSupported = true;					// Is FTP supported?
	ftpEnabled = true;						// Is FTP enabled?
	ftpPort = 21;							// The FTP service port
	ftpSpecificHost = false;				// Does FTP have its own access list?
	//ftpHostsRequired = false;				// Is the host configuration required?
	//configFTPHostAccess = i18n("");		// How access lists are configured for the FTP service
	disableFTP = i18n("The *ABBREV*FTP*-ABBREV* service can be disabled on *DEVICETYPE* devices with the following command:*CODE**COMMAND*restrict ftp*-COMMAND**-CODE*");					// How to disable FTP text...
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
	sshSupported = true;					// Does this device support SSH?
	sshUpgrade = false;						// Do you have to upgrade?
	sshEnabled = true;						// Is the SSH service enabled?
	sshVersion = 0;							// What is the SSH Protocol version (0 = 1 and 2)
	sshPort = 22;							// The SSH port number
	configSSHSupport = i18n("The *ABBREV*SSH*-ABBREV* service can be enabled on *DEVICETYPE* devices with the following command:*CODE**COMMAND*no restrict ssh*-COMMAND**-CODE*");			// How to configure SSH...
	sshSpecificHost = false;				// Does SSH have its own access list?
	//sshHostsRequired = false;				// Is the host configuration required?
	//configSSHHostAccess = i18n("");		// How to configure SSH...
	//scpSupported = false;					// Is SCP supported?
	//sshSpecificTimeout = false;			// A SSH Specific Timeout?
	//sshTimeout = 0;						// The SSH Timeout (secs)
	//configSSHTimeout = i18n("");			// The text and commands to configure the timeout

	// SSH 2 support...
	ssh2Supported = false;					// Does the device support SSH version 2?
	ssh2upgrade = false;					// Do you have to upgrade...
	configSSHv2Support = i18n("The *ABBREV*SSH*-ABBREV* service on *DEVICETYPE* devices can be configured to support only protocol version 2 with the following command:*CODE**COMMAND*sshd version v2*-COMMAND**-CODE*");			// How to configure protocol version 2 support only

	sshConfigProtocolSupport = i18n("*DEVICETYPE* devices support *ABBREV*SSH*-ABBREV* protocol version 1 and from *DEVICEOS* version 7.50 *DEVICETYPE* devices support protocol version 2.");	// Config report text on protocol support (e.g. supports both version 1 and 2 of the protocol)

	// HTTP(S) options...
	httpSupported = true;					// Does this device support HTTP
	httpsSupported = false;					// Does this device support HTTPS
	httpsUpgrade = false;					// Do you have to upgrade for HTTPS?
	httpEnabled = false;					// Is the HTTP service enabled?
	httpPort = 80;							// HTTP port
	httpsEnabled = false;					// Is the HTTPS service enabled?
	httpsPort = 443;						// HTTPS port
	//httpsRedirect = false;				// Is HTTP to HTTPS redirect enabled?
	//httpSpecificTimeout = false;			// A HTTP Specific Timeout?
	//httpTimeout = 0;						// The HTTP Timeout (secs)
	//configHTTPTimeout = i18n("");			// The text and commands to configure the timeout
	httpLabel = i18n("*ABBREV*XML*-ABBREV*");		// The label given to the HTTP service (e.g. HTTP)
	httpsLabel = i18n("*ABBREV*Secure XML*-ABBREV*");	// The label given to the HTTPS service (e.g. HTTPS)
	//httpSpecificHost = false;				// Does HTTP have its own access list?
	//httpHostsRequired = false;				// Is the host configuration required?
	//configHTTPHostAccess = i18n("");		// How to configure HTTP Management hosts...
	//httpsRedirectSupported = false;			// Is HTTP redirected to HTTPS?
	disableHTTP = i18n("The unsecure *ABBREV*XML*-ABBREV* service can be disabled on *DEVICETYPE* devices with the following command:*CODE**COMMAND*restrict xml*-COMMAND**-CODE*");					// How to disable HTTP text...
	configHTTPSSupport = i18n("The secure *ABBREV*XML*-ABBREV* service can be enabled on *DEVICETYPE* devices with the following command:*CODE**COMMAND*no restrict secure-xml*-COMMAND**-CODE*");			// How to configure HTTPS...

	// Device Specific...
	userRestrictions = false;				// The user database setting...
	ciscoViewDeviceManager = false;			// As it says...
	sshdKeepAlives = true;					// SSHD Keep Alive Messages...
	sshServerKeyBits = 768;					// The SSH Server Key bits...
}


int CiscoCSSAdministration::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	int tempInt = 0;
	bool setting = false;

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

	// SSHD...
	if (strcmp(command->part(tempInt), "sshd") == 0)
	{
		tempInt++;

		if (strcmp(command->part(tempInt), "keepalive") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sSSHD Keep Alive Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			sshdKeepAlives = false;
		}

		else if (strcmp(command->part(tempInt), "port") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sSSHD Port Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			tempInt++;
			if (setting == true)
				sshPort = atoi(command->part(tempInt));
			else
				sshPort = 22;
		}

		else if (strcmp(command->part(tempInt), "server-keybits") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sSSHD Server Keybits Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			tempInt++;
			if (setting == true)
				sshServerKeyBits = atoi(command->part(tempInt));
			else
				sshServerKeyBits = 768;
		}

		else if (strcmp(command->part(tempInt), "version") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sSSHD Version Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			tempInt++;
			if (setting == true)
			{
				if (strcmp(command->part(tempInt), "v1") == 0)
					sshVersion = 1;
				else
					sshVersion = 2;
			}
			else
				sshVersion = 0;
		}

		// All others...
		else
			device->lineNotProcessed(line);
	}

	// Restrict lines...
	else if (strcmp(command->part(tempInt), "restrict") == 0)
	{
		tempInt++;

		if (strcmp(command->part(tempInt), "telnet") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sRestrict Telnet Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			if (setting == true)
				telnetEnabled = false;
			else
				telnetEnabled = true;
		}

		else if (strcmp(command->part(tempInt), "ftp") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sRestrict FTP Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			if (setting == true)
				ftpEnabled = false;
			else
				ftpEnabled = true;
		}

		else if (strcmp(command->part(tempInt), "console") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sRestrict Console Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			if (setting == true)
				consoleEnabled = false;
			else
				consoleEnabled = true;
		}

		else if (strcmp(command->part(tempInt), "ssh") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sRestrict SSH Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			if (setting == true)
				sshEnabled = false;
			else
				sshEnabled = true;
		}

		else if (strcmp(command->part(tempInt), "xml") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sRestrict XML Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			if (setting == true)
				httpEnabled = false;
			else
				httpEnabled = true;
		}

		else if (strcmp(command->part(tempInt), "secure-xml") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sRestrict Secure XML Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			if (setting == true)
				httpsEnabled = false;
			else
				httpsEnabled = true;
		}

		else if (strcmp(command->part(tempInt), "user-database") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sRestrict User Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			if (setting == true)
				userRestrictions = false;
			else
				userRestrictions = true;
		}

		else if (strcmp(command->part(tempInt), "web-mgmt") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sRestrict CiscoView Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			if (setting == true)
				ciscoViewDeviceManager = false;
			else
				ciscoViewDeviceManager = true;
		}

		// All others...
		else
			device->lineNotProcessed(line);
	}

	else if ((strcmp(command->part(tempInt), "web-mgmt") == 0) && (strcmp(command->part(tempInt + 1), "state") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sRestrict CiscoView Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
		tempInt += 2;
		if (strcmp(command->part(tempInt), "disable") == 0)
			ciscoViewDeviceManager = false;
		else
			ciscoViewDeviceManager = true;
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int CiscoCSSAdministration::processDefaults(Device *device)
{
	// SSH2 supported...
	if ((ssh2Supported == false) && (device->general->versionMajor != 0))
	{
		if ((device->general->versionMajor > 7) || ((device->general->versionMajor == 7) && (device->general->versionMinor > 49)))
			ssh2Supported = true;
		else
		{
			ssh2upgrade = true;
			sshVersion = 1;
		}

		// Default SSH Protocol...
		if (((device->general->versionMajor < 7) || ((device->general->versionMajor == 7) && (device->general->versionMinor < 50))) && (sshVersion == 0))
			sshVersion = 1;
	}
	else
	{
		ssh2upgrade = true;
		sshVersion = 1;
	}

	// HTTPS supported...
	if ((httpsSupported == false) && (device->general->versionMajor != 0))
	{
		if ((device->general->versionMajor > 7) || ((device->general->versionMajor == 7) && (device->general->versionMinor > 29)))
			httpsSupported = true;
		else
			httpsUpgrade = true;
	}
	else
		httpsUpgrade = true;

	return 0;
}


int CiscoCSSAdministration::generateDeviceGeneralConfig(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;

	// Add service to the services list...
	configReportPointer = device->getConfigSection("CONFIG-SERVICES");
	paragraphPointer = device->getTableParagraphPointer("CONFIG-SERVICES-TABLE");
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*CVDM*-ABBREV* Service"));
	if (ciscoViewDeviceManager == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));

	// Add general stuff...
	configReportPointer = device->getConfigSection("CONFIG-ADMIN");
	paragraphPointer = device->getTableParagraphPointer("CONFIG-ADMINGENERAL-TABLE");
	device->addTableData(paragraphPointer->table, i18n("User Administrative Restrictions"));
	if (userRestrictions == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*CVDM*-ABBREV* Service"));
	if (ciscoViewDeviceManager == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));

	return 0;
}


int CiscoCSSAdministration::generateDeviceSSHConfig(Device *device)
{
	// Variables...
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;

	// SSH table settings...
	paragraphPointer = device->getTableParagraphPointer("CONFIG-ADMINSSH-TABLE");
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*SSH*-ABBREV* Server Key Length"));
	tempString.assign(device->intToString(sshServerKeyBits));
	if (sshServerKeyBits == 1)
		tempString.append(i18n(" bit"));
	else
		tempString.append(i18n(" bits"));
	device->addTableData(paragraphPointer->table, tempString.c_str());
	device->addTableData(paragraphPointer->table, i18n("*ABBREV*SSH*-ABBREV* Keep Alive Messages"));
	if (sshdKeepAlives == true)
		device->addTableData(paragraphPointer->table, i18n("Enabled"));
	else
		device->addTableData(paragraphPointer->table, i18n("Disabled"));

	return 0;
}


int CiscoCSSAdministration::generateSecuritySpecificReport(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;

	if ((userRestrictions == false) && ((telnetEnabled == true) || (sshEnabled == true)))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] User Administrative Restrictions Disabled\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("User Administrative Restrictions Disabled"));
		securityIssuePointer->reference.assign("CSS.ADMIREST.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices support the configuration of different levels of user. This helps to prevent unauthorised users from modifying the devices configuration. *DEVICETYPE* devices have a *COMMAND*user-database*-COMMAND* setting that can restrict users from making some significant changes to the configuration of *DEVICENAME*. By default, users are allowed to make the changes."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the users had not been restricted with the *COMMAND*user-database*-COMMAND* setting on *DEVICENAME*."));

		// Issue impact...
		securityIssuePointer->impactRating = 8;			// HIGH
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("A malicious user would not be prevented from creating or modifying usernames on *DEVICENAME*. Furthermore, without any restrictions the user would be able to clear the running-config."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 3;			// MODERATE
		paragraphPointer->paragraph.assign(i18n("In order for an attacker to exploit this issue the attacker would require access to *DEVICENAME* as a user. The attacker would therefore require authentication credentials and access to an administrative service."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 1;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that *DEVICENAME* should be reconfigured to prevent the devices users from clearing the running-config or creating/modifying usernames. The access restrictions can be modified to prevent all but Administrator and Technician users from performing those tasks. This can be done with the following command:*CODE**COMMAND*restrict user-database*-COMMAND**-CODE*"));

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("user administrative restrictions were disabled"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Restrict users from performing administrative tasks."));
	}


	if ((sshdKeepAlives == false) && (sshEnabled == true))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] SSH Keep Alive Messages Disabled\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("*ABBREV*SSH*-ABBREV* Keep Alive Messages Disabled"));
		securityIssuePointer->reference.assign("CSS.ADMISSHK.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("The *ABBREV*SSH*-ABBREV* service on *DEVICETYPE* devices supports the sending of \"keep alive\" messages. These messages are sent to determine if a connection to the service has become orphaned, the resources can then be freed for any broken connections."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices send \"keep alive\" by default for connections to the *ABBREV*SSH*-ABBREV* service. However, *COMPANY* determined that the sending of \"keep alive\" messages had been disabled on *DEVICENAME*."));

		// Issue impact...
		securityIssuePointer->impactRating = 5;			// MEDIUM
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("An attacker could perform a *ABBREV*DoS*-ABBREV* attack on the *ABBREV*SSH*-ABBREV* service by repeatedly opening connections until no more connections are possible."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 6;			// EASY
		paragraphPointer->paragraph.assign(i18n("Tools are available on the Internet that are capable of opening large numbers of connections to cause a *ABBREV*DoS*-ABBREV* attack."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 1;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that *ABBREV*SSH*-ABBREV* service \"keep alive\" messages are enabled on *DEVICENAME*. This can be configured with the following command:*CODE**COMMAND*sshd keepalive*-COMMAND**-CODE*"));

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("*ABBREV*SSH*-ABBREV* service \"keep alive\" messages were disabled"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Enable the sending of *ABBREV*SSH*-ABBREV* service \"keep alive\" messages."));
	}

	return 0;
}

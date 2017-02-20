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

#include "../../globaldefs.h"
#include "../device.h"
#include "administration.h"


int Administration::generateTimeoutSecurityIssue(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] Long Connection Timeout\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	if (connectionTimeout == 0)
		securityIssuePointer->title.assign(i18n("No Connection Timeout"));
	else
		securityIssuePointer->title.assign(i18n("Long Connection Timeout"));
	securityIssuePointer->reference.assign("GEN.ADMICOTM.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("The connection timeout setting is used by *DEVICETYPE* devices to identify unused connections that can be closed. The system resources used by *DEVICETYPE* devices can then be freed. A connection could become unused for a number of reasons; the network connection may have been disrupted, a connection may not have been properly terminated or an administrator may have left their computer with a connection open."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	if (connectionTimeout == 0)
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that there was no connection timeout configured on *DEVICENAME*."));
	else
	{
		device->addString(paragraphPointer, device->timeToString(connectionTimeout));
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the connection timeout on *DEVICENAME* was *DATA*."));
	}

	// Issue impact...
	securityIssuePointer->impactRating = 7;			// HIGH
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("If a connection is not properly terminated, it may be possible for an attacker to make use of the connection in order to gain access to the device. If successful, the attacker would gain access with the privileges of the previous user."));

	// Issue ease...
	securityIssuePointer->easeRating = 0;
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	paragraphPointer->paragraph.assign(i18n("A malicious user may be able to exploit this issue by taking over an administrators connection if they were to leave it open. For a remote attacker to gain access to a remote connection, they would have to monitor the connection prior to an attempt to take it over. Programs that are capable of monitoring network connections are available on the Internet."));
	if (consoleEnabled == true)
	{
		securityIssuePointer->easeRating = 5;				// Moderate
		paragraphPointer->paragraph.assign(i18n(" For an attacker with physical access to *DEVICENAME*, gaining access through a console port that had not been terminated would be trivial. The attacker, who may legitimately have access to the server room, would simply have to attach a console cable to their computer."));
	}
	if ((telnetEnabled == true) || (tftpEnabled == true) || (ftpEnabled == true) || (httpEnabled == true))
	{
		securityIssuePointer->easeRating = 5;				// Moderate
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.assign(i18n("With clear text protocol services being offered by *DEVICENAME*, monitoring the network traffic would reveal a lot of information about the connection. The attacker may even be able to capture the authentication credentials, so would not have to attempt to take over a connection."));
	}
	if ((sshEnabled == true) || (httpEnabled == true))
	{
		if (securityIssuePointer->easeRating == 0)				// Moderate
			securityIssuePointer->easeRating = 2;				// CHALLENGING
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.assign(i18n("With cryptographically secure services, gaining access to an unterminated connection could prove more difficult. The attacker may have to exploit a weakness in the protocol to gain access."));
	}

	// Issue recommendation...
	securityIssuePointer->fixRating = 2;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	device->addString(paragraphPointer, device->timeToString(device->config->connectionTimeouts));
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that a timeout period of *DATA* should be configured for connections to *DEVICENAME*."));
	if (strlen(configTimeout) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configTimeout);
	}

	// Conclusions text...
	if (connectionTimeout == 0)
		securityIssuePointer->conLine.append(i18n("no connection timeout was configured"));
	else
		securityIssuePointer->conLine.append(i18n("a long connection timeout was configured"));

	// Recommendation list text...
	tempString.assign(i18n("Configure a connection timeout of "));
	tempString.append(device->timeToString(device->config->connectionTimeouts));
	device->addRecommendation(securityIssuePointer, tempString.c_str());

	// Related issues...
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMITELN.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMISSH1.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMIHTTP.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMIFTPC.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMITFTP.1");

	return errorCode;
}


int Administration::generateConsoleTimeoutSecurityIssue(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] Long Console Connection Timeout\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	if (consoleTimeout == 0)
		securityIssuePointer->title.assign(i18n("No Console Connection Timeout"));
	else
		securityIssuePointer->title.assign(i18n("Long Console Connection Timeout"));
	securityIssuePointer->reference.assign("GEN.ADMICNTM.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("The console connection timeout setting is used by *DEVICETYPE* devices to determine if a console connection is no longer being used and can be closed. The console connection could become unused if an administrator has not correctly terminated the connection and still remains logged into the console or they have left their computer without terminating the console connection."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	if (consoleTimeout == 0)
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that there was no console connection timeout was configured on *DEVICENAME*."));
	else
	{
		device->addString(paragraphPointer, device->timeToString(consoleTimeout));
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the console connection timeout on *DEVICENAME* was *DATA*."));
	}

	// Issue impact...
	if (consoleTimeout == 0)
		securityIssuePointer->impactRating = 9;			// CRTICICAL
	else
		securityIssuePointer->impactRating = 7;			// HIGH
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("An attacker with physical access to *DEVICENAME* would be able to connect to the console port and continue using a terminated connection. Due to the nature of the device the user access the attacker would gain is likely to be an administrative level user."));

	// Issue ease...
	securityIssuePointer->easeRating = 2;				// CHALLENGING
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	paragraphPointer->paragraph.assign(i18n("An attacker would require physical access to the device in order to connect to the console port. Although this may seem like a significant barrier, a malicious user or attacker who has legitimate access to the room where *DEVICENAME* is located would be able to access the console port. A locked server rack would provide little barrier to a motivated attacker."));

	// Issue recommendation...
	securityIssuePointer->fixRating = 2;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	device->addString(paragraphPointer, device->timeToString(device->config->connectionTimeouts));
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that a timeout period of *DATA* should be configured for the console connection."));
	if (strlen(configConsoleTimeout) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configConsoleTimeout);
	}

	// Conclusions text...
	if (consoleTimeout == 0)
		securityIssuePointer->conLine.append(i18n("no console connection timeout was configured"));
	else
		securityIssuePointer->conLine.append(i18n("a long console connection timeout was configured"));

	// Recommendation list text...
	tempString.assign(i18n("Configure a console connection timeout of "));
	tempString.append(device->timeToString(device->config->connectionTimeouts));
	device->addRecommendation(securityIssuePointer, tempString.c_str());

	return errorCode;
}


int Administration::generateTelnetTimeoutSecurityIssue(Device *device, bool noWeakTelnetHosts)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] Long Telnet Connection Timeout\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	if (telnetTimeout == 0)
		securityIssuePointer->title.assign(i18n("No Telnet Connection Timeout"));
	else
		securityIssuePointer->title.assign(i18n("Long Telnet Connection Timeout"));
	securityIssuePointer->reference.assign("GEN.ADMITETM.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("The Telnet connection timeout setting is used by *DEVICETYPE* devices to determine if a Telnet connection is no longer being used and can be closed. A Telnet connection to *DEVICENAME* could become unused if; an administrator has not correctly terminated the connection, the network connection has been disrupted or the administrator has left their computer without terminating the connection."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	if (telnetTimeout == 0)
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that there was no Telnet connection timeout was configured on *DEVICENAME*."));
	else
	{
		device->addString(paragraphPointer, device->timeToString(telnetTimeout));
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the Telnet connection timeout on *DEVICENAME* was *DATA*."));
	}

	// Issue impact...
	if (telnetTimeout == 0)
		securityIssuePointer->impactRating = 7;			// HIGH
	else
		securityIssuePointer->impactRating = 5;			// MEDIUM
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("A remote attacker who is able to able to take over an idle Telnet connection would gain access as the user who was previously used the connection. A malicious user could be make use of an unlocked network administrators computer to gain access to an idle Telnet connection to *DEVICENAME*. Due to the nature of the device, the connection is likely to give the attacker administrative privileges on *DEVICENAME*."));

	// Issue ease...
	securityIssuePointer->easeRating = 6;				// EASY
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	paragraphPointer->paragraph.assign(i18n("Telnet is a clear text protocol and is vulnerable to \"man in the middle\" style attacks. Therefore, an attacker who was able to monitor the Telnet connection could take over an idle connection. However, being a clear text protocol, the attacker could capture the authentication credentials used by the administrator to logon to the service and would not have to resort to taking over a non-terminated connection."));
	if (noWeakTelnetHosts == false)
	{
		securityIssuePointer->easeRating = 4;				// MODERATE
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		if (telnetHosts != 0)
			device->addString(paragraphPointer, "GEN.ADMITELW.1");
		else
			device->addString(paragraphPointer, "GEN.ADMIHOWE.1");
		paragraphPointer->paragraph.assign(i18n("Although access to the Telnet service has been restricted to specific management hosts, *COMPANY* determined that the restricted management host configuration was weak (see section *SECTIONNO*)."));
	}
	else if ((telnetHosts != 0) || (serviceHosts != 0))
	{
		securityIssuePointer->easeRating = 2;				// CHALLENGING
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.assign(i18n("Access to the Telnet service on *DEVICENAME* is made more difficult for an attacker due to the configured administrative host restrictions. However, it may still be possible for a skilled attacker to bypass those restrictions."));
	}

	// Issue recommendation...
	securityIssuePointer->fixRating = 2;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	device->addString(paragraphPointer, device->timeToString(device->config->connectionTimeouts));
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that a timeout period of *DATA* should be configured for Telnet connections."));
	if (strlen(configTelnetTimeout) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configTelnetTimeout);
	}

	// Conclusions text...
	if (telnetTimeout == 0)
		securityIssuePointer->conLine.append(i18n("no Telnet connection timeout was configured"));
	else
		securityIssuePointer->conLine.append(i18n("a long Telnet connection timeout was configured"));

	// Recommendation list text...
	tempString.assign(i18n("Configure a Telnet connection timeout of "));
	tempString.append(device->timeToString(device->config->connectionTimeouts));
	device->addRecommendation(securityIssuePointer, tempString.c_str());

	// Dependent issues...
	device->addDependency(securityIssuePointer, "GEN.ADMITELN.1");

	// Related issues...
	if ((telnetSpecificHost == true) && (telnetHosts == 0))
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMITELH.1");
	if ((telnetSpecificHost == true) && (telnetHosts != 0))
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMITELW.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMIHOST.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMIHOWE.1");

	return errorCode;
}


int Administration::generateFTPTimeoutSecurityIssue(Device *device, bool noWeakFTPHosts)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] Long FTP Connection Timeout\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	if (ftpTimeout == 0)
		securityIssuePointer->title.assign(i18n("No *ABBREV*FTP*-ABBREV* Connection Timeout"));
	else
		securityIssuePointer->title.assign(i18n("Long *ABBREV*FTP*-ABBREV* Connection Timeout"));
	securityIssuePointer->reference.assign("GEN.ADMIFTTM.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("The *ABBREV*FTP*-ABBREV* connection timeout setting is used by *DEVICETYPE* devices to determine if an *ABBREV*FTP*-ABBREV* connection is no longer being used and can be closed. An *ABBREV*FTP*-ABBREV* connection to *DEVICENAME* could become unused if; an administrator has not correctly terminated the connection, the network connection has been disrupted or the administrator has left their computer without terminating the connection."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	if (telnetTimeout == 0)
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that there was no *ABBREV*FTP*-ABBREV* connection timeout was configured on *DEVICENAME*."));
	else
	{
		device->addString(paragraphPointer, device->timeToString(ftpTimeout));
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *ABBREV*FTP*-ABBREV* connection timeout on *DEVICENAME* was *DATA*."));
	}

	// Issue impact...
	if (ftpTimeout == 0)
		securityIssuePointer->impactRating = 6;			// MEDIUM
	else
		securityIssuePointer->impactRating = 4;			// LOW
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("A remote attacker who is able to able to take over an idle *ABBREV*FTP*-ABBREV* connection would gain access as the user who was previously used the connection. A malicious user could be make use of an unlocked network administrators computer to gain access to an idle *ABBREV*FTP*-ABBREV* connection to *DEVICENAME*. Due to the nature of the device, the connection is likely to give the attacker the ability to gain a copy of the devices configuration."));

	// Issue ease...
	securityIssuePointer->easeRating = 6;				// EASY
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	paragraphPointer->paragraph.assign(i18n("*ABBREV*FTP*-ABBREV* is a clear text protocol and is vulnerable to \"man in the middle\" style attacks. Therefore, an attacker who was able to monitor the *ABBREV*FTP*-ABBREV* connection could take over an idle connection. However, being a clear text protocol, the attacker could capture the authentication credentials used by the administrator to logon to the service and would not have to resort to taking over a non-terminated connection."));
	if (noWeakFTPHosts == false)
	{
		securityIssuePointer->easeRating = 4;				// MODERATE
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		if (ftpHosts != 0)
			device->addString(paragraphPointer, "GEN.ADMIFTPW.1");
		else
			device->addString(paragraphPointer, "GEN.ADMIHOWE.1");
		paragraphPointer->paragraph.assign(i18n("Although access to the *ABBREV*FTP*-ABBREV* service has been restricted to specific management hosts, *COMPANY* determined that the restricted management host configuration was weak (see section *SECTIONNO*)."));
	}
	else if ((ftpHosts != 0) || (serviceHosts != 0))
	{
		securityIssuePointer->easeRating = 2;				// CHALLENGING
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.assign(i18n("Access to the *ABBREV*FTP*-ABBREV* service on *DEVICENAME* is made more difficult for an attacker due to the configured administrative host restrictions. However, it may still be possible for a skilled attacker to bypass those restrictions."));
	}

	// Issue recommendation...
	securityIssuePointer->fixRating = 2;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	device->addString(paragraphPointer, device->timeToString(device->config->connectionTimeouts));
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that a timeout period of *DATA* should be configured for *ABBREV*FTP*-ABBREV* connections."));
	if (strlen(configFTPTimeout) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configFTPTimeout);
	}

	// Conclusions text...
	if (ftpTimeout == 0)
		securityIssuePointer->conLine.append(i18n("no *ABBREV*FTP*-ABBREV* connection timeout was configured"));
	else
		securityIssuePointer->conLine.append(i18n("a long *ABBREV*FTP*-ABBREV* connection timeout was configured"));

	// Recommendation list text...
	tempString.assign(i18n("Configure a *ABBREV*FTP*-ABBREV* connection timeout of "));
	tempString.append(device->timeToString(device->config->connectionTimeouts));
	device->addRecommendation(securityIssuePointer, tempString.c_str());

	// Dependent issues...
	device->addDependency(securityIssuePointer, "GEN.ADMIFTPC.1");

	// Related issues...
	if ((ftpSpecificHost == true) && (ftpHosts == 0))
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMIFTPH.1");
	if ((ftpSpecificHost == true) && (ftpHosts != 0))
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMIFTPW.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMIHOST.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMIHOWE.1");

	return errorCode;
}


int Administration::generateSSHTimeoutSecurityIssue(Device *device, bool noWeakSSHHosts)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] Long SSH Connection Timeout\n", device->config->COL_BLUE, device->config->COL_RESET);

	securityIssuePointer = device->addSecurityIssue();
	if (sshTimeout == 0)
		securityIssuePointer->title.assign(i18n("No *ABBREV*SSH*-ABBREV* Connection Timeout"));
	else
		securityIssuePointer->title.assign(i18n("Long *ABBREV*SSH*-ABBREV* Connection Timeout"));
	securityIssuePointer->reference.assign("GEN.ADMISSTM.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	paragraphPointer->paragraph.assign(i18n("The *ABBREV*SSH*-ABBREV* connection timeout setting is used by *DEVICETYPE* devices to determine if an *ABBREV*SSH*-ABBREV* connection is no longer being used and can be closed. An *ABBREV*SSH*-ABBREV* connection to *DEVICENAME* could become unused if; an administrator has not correctly terminated the connection, the network connection has been disrupted or the administrator has left their computer without terminating the connection."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	if (sshTimeout == 0)
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that there was no *ABBREV*SSH*-ABBREV* connection timeout was configured on *DEVICENAME*."));
	else
	{
		device->addString(paragraphPointer, device->timeToString(sshTimeout));
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *ABBREV*SSH*-ABBREV* connection timeout on *DEVICENAME* was *DATA*."));
	}

	// Issue impact...
	if (sshTimeout == 0)
		securityIssuePointer->impactRating = 7;			// HIGH
	else
		securityIssuePointer->impactRating = 5;			// MEDIUM
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	paragraphPointer->paragraph.assign(i18n("A remote attacker who is able to able to take over an idle *ABBREV*SSH*-ABBREV* connection would gain access as the user who was previously used the connection. A malicious user could be make use of an unlocked network administrators computer to gain access to an idle *ABBREV*SSH*-ABBREV* connection to *DEVICENAME*. Due to the nature of the device, the connection is likely to give the attacker administrative level user access to the device."));

	// Issue ease...
	securityIssuePointer->easeRating = 2;				// CHALLENGE
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	paragraphPointer->paragraph.assign(i18n("*ABBREV*SSH*-ABBREV* is a cryptographically secure protocol, a remote attacker would have to attempt to exploit an issue with the protocol in order to gain access to an unused connection."));
	if (sshVersion < 2)
	{
		securityIssuePointer->easeRating = 4;				// MODERATE
		device->addString(paragraphPointer, "GEN.ADMISSH1.1");
		paragraphPointer->paragraph.assign(i18n(" However, *ABBREV*SSH*-ABBREV* protocol version 1 is supported on *DEVICENAME*. *ABBREV*SSH*-ABBREV* protocol version 1 is vulnerable to a \"man in the middle\" style attack (see section *SECTIONNO*)."));
	}
	if (noWeakSSHHosts == false)
	{
		securityIssuePointer->easeRating = 2;				// CHALLENGE
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		if (sshHosts != 0)
			device->addString(paragraphPointer, "GEN.ADMISSHW.1");
		else
			device->addString(paragraphPointer, "GEN.ADMIHOWE.1");
		paragraphPointer->paragraph.assign(i18n("Although access to the *ABBREV*SFTP*-ABBREV* service has been restricted to specific management hosts, *COMPANY* determined that the restricted management host configuration was weak (see section *SECTIONNO*)."));
	}
	else if ((sshHosts != 0) || (serviceHosts != 0))
	{
		securityIssuePointer->easeRating = 1;				// CHALLENGING
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.assign(i18n("Access to the *ABBREV*SSH*-ABBREV* service on *DEVICENAME* is made more difficult for an attacker due to the configured administrative host restrictions. However, it may still be possible for a skilled attacker to bypass those restrictions."));
	}

	// Issue recommendation...
	securityIssuePointer->fixRating = 2;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	device->addString(paragraphPointer, device->timeToString(device->config->connectionTimeouts));
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that a timeout period of *DATA* should be configured for *ABBREV*SSH*-ABBREV* connections."));
	if (strlen(configSSHTimeout) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configSSHTimeout);
	}

	// Conclusions text...
	if (sshTimeout == 0)
		securityIssuePointer->conLine.append(i18n("no *ABBREV*SSH*-ABBREV* connection timeout was configured"));
	else
		securityIssuePointer->conLine.append(i18n("a long *ABBREV*SSH*-ABBREV* connection timeout was configured"));

	// Recommendation list text...
	tempString.assign(i18n("Configure a *ABBREV*SSH*-ABBREV* connection timeout of "));
	tempString.append(device->timeToString(device->config->connectionTimeouts));
	device->addRecommendation(securityIssuePointer, tempString.c_str());

	// Related issues...
	if ((sshSpecificHost == true) && (sshHosts == 0))
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMISSHF.1");
	if ((sshSpecificHost == true) && (sshHosts != 0))
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMISSHW.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMIHOST.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMIHOWE.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMISSH1.1");

	return errorCode;
}


int Administration::generateHTTPTimeoutSecurityIssue(Device *device, bool noWeakHTTPHosts)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	string protoString;
	string tempString;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s [ISSUE] Long HTTP Connection Timeout\n", device->config->COL_BLUE, device->config->COL_RESET);

	if ((httpEnabled == false) || ((httpEnabled == true) && (httpsRedirect == true)))
		protoString.assign(httpsLabel);
	else
		protoString.assign(httpLabel);

	securityIssuePointer = device->addSecurityIssue();
	if (httpTimeout == 0)
		tempString.assign(i18n("No "));
	else
		tempString.assign(i18n("Long "));
	tempString.append(protoString);
	tempString.append(i18n(" Connection Timeout"));
	securityIssuePointer->title.assign(tempString);
	securityIssuePointer->reference.assign("GEN.ADMIHTTM.1");

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	device->addString(paragraphPointer, protoString.c_str());
	device->addString(paragraphPointer, protoString.c_str());
	device->addString(paragraphPointer, protoString.c_str());
	paragraphPointer->paragraph.assign(i18n("The *DATA* connection timeout setting is used by *DEVICETYPE* devices to determine if a *DATA* connection is no longer being used and can be closed. A *DATA* connection to *DEVICENAME* could become unused if; an administrator has not correctly terminated the connection, the network connection has been disrupted or the administrator has left their computer without terminating the connection."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	device->addString(paragraphPointer, protoString.c_str());
	if (httpTimeout == 0)
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that there was no *DATA* connection timeout was configured on *DEVICENAME*."));
	else
	{
		device->addString(paragraphPointer, device->timeToString(httpTimeout));
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the *DATA* connection timeout on *DEVICENAME* was *DATA*."));
	}

	// Issue impact...
	if (httpTimeout == 0)
		securityIssuePointer->impactRating = 7;			// HIGH
	else
		securityIssuePointer->impactRating = 5;			// MEDIUM
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	device->addString(paragraphPointer, protoString.c_str());
	device->addString(paragraphPointer, protoString.c_str());
	paragraphPointer->paragraph.assign(i18n("A remote attacker who is able to able to take over an idle *DATA* connection would gain access as the user who was previously used the connection. A malicious user could be make use of an unlocked network administrators computer to gain access to an idle *DATA* connection to *DEVICENAME*. Due to the nature of the device, the connection is likely to give the attacker administrative privileges on *DEVICENAME*."));

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	if ((httpEnabled == false) || ((httpEnabled == true) && (httpsRedirect == true)))
	{
		securityIssuePointer->easeRating = 2;				// CHALLENGING
		device->addString(paragraphPointer, protoString.c_str());
		paragraphPointer->paragraph.assign(i18n("*DATA* is a cryptographically secure protocol, a remote attacker would have to attempt to exploit an issue with the protocol in order to gain access to an unused connection."));
	}
	else
	{
		securityIssuePointer->easeRating = 6;				// EASY
		device->addString(paragraphPointer, protoString.c_str());
		device->addString(paragraphPointer, protoString.c_str());
		paragraphPointer->paragraph.assign(i18n("*DATA* is a clear text protocol and is vulnerable to \"man in the middle\" style attacks. Therefore, an attacker who was able to monitor the *DATA* connection could take over an idle connection. However, being a clear text protocol, the attacker could capture the authentication credentials used by the administrator to logon to the service and would not have to resort to taking over a non-terminated connection."));
	}
	if (noWeakHTTPHosts == false)
	{
		if ((httpEnabled == true) && (httpsRedirect == false))
			securityIssuePointer->easeRating = 4;				// MODERATE
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		if (httpHosts != 0)
			device->addString(paragraphPointer, "GEN.ADMIHTTW.1");
		else
			device->addString(paragraphPointer, "GEN.ADMIHOWE.1");
		device->addString(paragraphPointer, protoString.c_str());
		paragraphPointer->paragraph.assign(i18n("Although access to the *DATA* service has been restricted to specific management hosts, *COMPANY* determined that the restricted management host configuration was weak (see section *SECTIONNO*)."));
	}
	else if ((httpHosts != 0) || (serviceHosts != 0))
	{
		if ((httpEnabled == true) && (httpsRedirect == true))
			securityIssuePointer->easeRating = 2;				// CHALLENGING
		else
			securityIssuePointer->easeRating = 1;				// CHALLENGING
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		device->addString(paragraphPointer, protoString.c_str());
		paragraphPointer->paragraph.assign(i18n("Access to the *DATA* service on *DEVICENAME* is made more difficult for an attacker due to the configured administrative host restrictions. However, it may still be possible for a skilled attacker to bypass those restrictions."));
	}

	// Issue recommendation...
	securityIssuePointer->fixRating = 2;				// Trivial
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	device->addString(paragraphPointer, device->timeToString(device->config->connectionTimeouts));
	device->addString(paragraphPointer, protoString.c_str());
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that a timeout period of *DATA* should be configured for *DATA* connections."));
	if (strlen(configHTTPTimeout) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configHTTPTimeout);
	}

	// Conclusions text...
	if (httpTimeout == 0)
		tempString.assign(i18n("no "));
	else
		tempString.assign(i18n("a long "));
	tempString.append(protoString);
	tempString.append(i18n(" connection timeout was configured"));
	securityIssuePointer->conLine.append(tempString.c_str());

	// Recommendation list text...
	tempString.assign(i18n("Configure a "));
	tempString.append(protoString);
	tempString.append(i18n(" connection timeout of "));
	tempString.append(device->timeToString(device->config->connectionTimeouts));
	device->addRecommendation(securityIssuePointer, tempString.c_str());

	// Dependent issues...
	device->addDependency(securityIssuePointer, "GEN.ADMIHTTP.1");

	// Related issues...
	if ((telnetSpecificHost == true) && (telnetHosts == 0))
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMIHTTF.1");
	if ((telnetSpecificHost == true) && (telnetHosts != 0))
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMIHTTW.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMIHOST.1");
	device->addRelatedIssue(securityIssuePointer, "GEN.ADMIHOWE.1");

	return errorCode;
}




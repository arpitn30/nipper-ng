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
#include "../globaldefs.h"
#include "iosdevice.h"
#include "administration.h"


int IOSAdministration::generateSecuritySpecificReport(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	lineConfig *linePointer = 0;
	string tempString;
	int lineAclInMissingCount = 0;
	int lineWeakExecTimeoutCount = 0;
	int lineWithTACACSCount = 0;
	int lineWithoutAuthorisation = 0;
	int lineWithoutAccounting = 0;
	int lineWithOutputTransport = 0;
	int lineOuputNoAcl = 0;
	int lineLoginWithoutPassword = 0;
	int lineWithTransportInputAll = 0;
	int lineWithRLogin = 0;
	bool found = false;
	bool consoleAccessOnly = false;
	int errorCode = 0;

	// Search for issues...
	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s Administration IOS Issue Checks\n", device->config->COL_BLUE, device->config->COL_RESET);

	linePointer = line;
	while (linePointer != 0)
	{

		// If line is used...
		if (((linePointer->telnet == true) || (linePointer->ssh == true) || (linePointer->rlogin == true)) && (linePointer->exec == true) && !((linePointer->password.empty()) && (linePointer->login == loginLinePassword)))
		{

			// Line ACL In is missing...
			if ((linePointer->type == lineVTY) && (linePointer->aclIn.empty()))
				lineAclInMissingCount++;

			// Line exec timeout is weak...
			if ((linePointer->execTimeout > device->config->connectionTimeouts) || (linePointer->execTimeout == 0))
				lineWeakExecTimeoutCount++;

			// Line RLogin...
			if ((linePointer->type == lineVTY) && (linePointer->rlogin == true))
				lineWithRLogin++;

			// Line input transport all used...
			if ((linePointer->type == lineVTY) && (linePointer->all == true))
				lineWithTransportInputAll++;

			// Line TACACS...
			if (linePointer->login == loginTACACS)
				lineWithTACACSCount++;

			// Line Login with no password...
			if (linePointer->login == loginWithNoPassword)
				lineLoginWithoutPassword++;

			// Line accounting...
			if (linePointer->accounting == false)
				lineWithoutAccounting++;

			// Line authorisation...
			if (linePointer->authorization == false)
				lineWithoutAuthorisation++;
		}

		// Transport Output...
		if ((linePointer->type != lineAUX) && (linePointer->type != lineConsole) && (linePointer->output == true))
		{
			lineWithOutputTransport++;
			if (linePointer->aclOut.empty())
				lineOuputNoAcl++;
		}

		linePointer = linePointer->next;
	}


	// Issues...
	

	// ACL in
	if (lineAclInMissingCount > 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Administration Line Without ACL Configured\n", device->config->COL_BLUE, device->config->COL_RESET);
		
		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("Administration Access With No Host Restrictions"));
		securityIssuePointer->reference.assign("IOS.LINENACL.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("Remote command-based administrative services such as Telnet and *ABBREV*SSH*-ABBREV* are configured using lines on *DEVICETYPE* devices. These lines determine the method of authentication to be used, restrictions such as timeouts and access restriction *ABBREV*ACLs*-ABBREV*. *ABBREV*ACLs*-ABBREV* can be configured for both inbound and outbound connections to *DEVICETYPE* devices. These enable the restriction of administrative access to and from the hosts and networks defined in the *ABBREV*ACLs*-ABBREV*. If no *ABBREV*ACL*-ABBREV* are configured for the lines, no access restrictions are applied."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addValue(paragraphPointer, lineAclInMissingCount);
		if (lineAclInMissingCount > 1)
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* lines were configured with no *ABBREV*ACL*-ABBREV* to restrict administrative access to *DEVICENAME*. These lines are listed in Table *TABLEREF*."));
		else
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* line was configured with no *ABBREV*ACL*-ABBREV* to restrict administrative access to *DEVICENAME*. This line is shown in Table *TABLEREF*."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "SEC-REMOTEADMINLINEACL-TABLE");
		if (errorCode != 0)
			return errorCode;
		if (lineAclInMissingCount > 1)
			paragraphPointer->table->title.assign(i18n("Administration lines without *ABBREV*ACL*-ABBREV*"));
		else
			paragraphPointer->table->title.assign(i18n("Administration line without *ABBREV*ACL*-ABBREV*"));
		device->addTableHeading(paragraphPointer->table, i18n("Line"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Exec"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Login"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Level"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Telnet"), false);
		if (sshSupported == true)
			device->addTableHeading(paragraphPointer->table, i18n("SSH"), false);
		if (device->isRouter == true)
			device->addTableHeading(paragraphPointer->table, i18n("Rlogin"), false);

		linePointer = line;
		found = false;
		while (linePointer != 0)
		{

			// If line is used...
			if (((linePointer->type == lineVTY) && (linePointer->aclIn.empty())) && ((linePointer->telnet == true) || (linePointer->ssh == true) || (linePointer->rlogin == true)) && (linePointer->exec == true) && !((linePointer->password.empty()) && (linePointer->login == loginLinePassword)))
			{
				switch (linePointer->type)
				{
					case lineConsole:
						device->addTableData(paragraphPointer->table, i18n("Console"));
						break;
					case lineVTY:
						tempString.assign(i18n("*ABBREV*VTY*-ABBREV* "));
						tempString.append(device->intToString(linePointer->lineStart));
						if (linePointer->lineEnd != 0)
						{
							tempString.append(" - ");
							tempString.append(device->intToString(linePointer->lineEnd));
						}
						device->addTableData(paragraphPointer->table, tempString.c_str());
						break;
					case lineAUX:
						device->addTableData(paragraphPointer->table, i18n("Auxillary"));
						break;
					default:
						tempString.assign(i18n("*ABBREV*TTY*-ABBREV* "));
						tempString.append(device->intToString(linePointer->lineStart));
						if (linePointer->lineEnd != 0)
						{
							tempString.append(" - ");
							tempString.append(device->intToString(linePointer->lineEnd));	
						}
						device->addTableData(paragraphPointer->table, tempString.c_str());
						break;
				}
				if (linePointer->exec == true)
				{
					device->addTableData(paragraphPointer->table, i18n("Yes"));
					switch (linePointer->login)
					{
						case loginWithNoPassword:
							device->addTableData(paragraphPointer->table, i18n("No Authentication"));
							found = true;
							break;
						case loginLinePassword:
							device->addTableData(paragraphPointer->table, i18n("Line Password"));
							if (linePointer->password.empty())
								found = true;
							break;
						case loginLocal:
							device->addTableData(paragraphPointer->table, i18n("Local Users"));
							break;
						case loginTACACS:
							device->addTableData(paragraphPointer->table, i18n("TACACS Style"));
							break;
						default:
							device->addTableData(paragraphPointer->table, i18n("AAA Authentication"));
							break;
					}
				}
				else
				{
					device->addTableData(paragraphPointer->table, i18n("No"));
					device->addTableData(paragraphPointer->table, i18n("N/A"));
				}
				tempString.assign(device->intToString(linePointer->privilege));
				device->addTableData(paragraphPointer->table, tempString.c_str());
				if (linePointer->telnet == true)
					device->addTableData(paragraphPointer->table, i18n("Yes"));
				else
					device->addTableData(paragraphPointer->table, i18n("No"));
				if (sshSupported == true)
				{
					if (linePointer->ssh == true)
						device->addTableData(paragraphPointer->table, i18n("Yes"));
					else
						device->addTableData(paragraphPointer->table, i18n("No"));
				}
				if (device->isRouter == true)
				{
					if (linePointer->rlogin == true)
						device->addTableData(paragraphPointer->table, i18n("Yes"));
					else
						device->addTableData(paragraphPointer->table, i18n("No"));
				}
			}
			linePointer = linePointer->next;
		}

		// Issue impact...
		if ((lineWithRLogin > 0) || (telnetEnabled == true))
			securityIssuePointer->impactRating = 7;			// High
		else
			securityIssuePointer->impactRating = 5;			// Medium
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("When no *ABBREV*ACL*-ABBREV* has been applied to the line configuration, an attacker or malicious user would not be restricted by *DEVICENAME* from connecting to a line configured administrative service. If a vulnerability were to exist in those services, or the attacker has valid authentication credentials, they could gain full administrative access to *DEVICENAME*."));
		if ((lineWithRLogin > 0) || (telnetEnabled == true))
			paragraphPointer->paragraph.append(i18n(" Furthermore, with clear text protocol services enabled, an attacker could gain the authentication credentials by monitoring administrative connections to the device."));
		if (found == true)
		{
			securityIssuePointer->impactRating = 9;			// Critical
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			paragraphPointer->paragraph.assign(i18n("To make matters worse, not all the lines require a password in order for an attacker to gain access. The attacker may simply have to connect to the administrative service in order to gain administrative access."));
		}

		// Issue ease...
		securityIssuePointer->easeRating = 9;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.assign(i18n("For an attacker to gain access to an administrative service, they would simply have to connect to it using the relevant client software. Client software for most administrative services is available on the Internet and some are installed by default on most *ABBREV*OS*-ABBREV*."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 2;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that an *ABBREV*ACL*-ABBREV* is configured and then applied to the line in order to restrict access."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("A *ABBREV*ACL*-ABBREV* can be configured with the following commands:*CODE**COMMAND*ip access-list standard *CMDUSER*access-list-number*-CMDUSER**-COMMAND**COMMAND*remark *CMDUSER*description*-CMDUSER**-COMMAND**COMMAND*permit *CMDUSER*ip-address*-CMDUSER* *CMDUSER*wildcard*-CMDUSER* *CMDOPTION*log*-CMDOPTION**-COMMAND**-CODE*"));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("The *ABBREV*ACL*-ABBREV* can then be applied to a line, from line configuration mode, using the following command:*CODE**COMMAND*access-class *CMDUSER*access-list-number*-CMDUSER* in*-COMMAND**-CODE*"));

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("all active lines were not configured with an *ABBREV*ACL*-ABBREV* to restrict access"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Configure an *ABBREV*ACL*-ABBREV* to restrict access"));
		device->addRecommendation(securityIssuePointer, i18n("Apply the *ABBREV*ACL*-ABBREV* to the relevant lines"));

		// Related issues...
		device->addRelatedIssue(securityIssuePointer, "IOS.LINENOPA.1");
		device->addRelatedIssue(securityIssuePointer, "IOR.LINERLOG.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMITELN.1");
	}


	// Weak Line Exec Timeout
	if (lineWeakExecTimeoutCount > 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Weak Exec Line Timeout\n", device->config->COL_BLUE, device->config->COL_RESET);
		
		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("Weak Exec Line Timeout Configured"));
		securityIssuePointer->reference.assign("IOS.LINETMOT.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("The line exec timeout setting is used by *DEVICETYPE* devices to identify unused connections that can be terminated. The system resources used by *DEVICETYPE* devices can then be freed and session terminated. A connection could become unused for a number of reasons; the network connection may have been disrupted, a connection may not of been properly terminated or an administrator may have left their computer with a connection open. In the case of console connections, the administrator may have disconnected the console cable without properly terminating a session."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addValue(paragraphPointer, lineAclInMissingCount);
		if (lineWeakExecTimeoutCount > 1)
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* lines were configured with a weak exec timeout. These lines are listed in Table *TABLEREF*."));
		else
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* line was configured with no exec timeout. This line is shown in Table *TABLEREF*."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "SEC-LINEEXECTIMEOUT-TABLE");
		if (errorCode != 0)
			return errorCode;
		if (lineWeakExecTimeoutCount > 1)
			paragraphPointer->table->title.assign(i18n("Administration lines with weak exec timeouts"));
		else
			paragraphPointer->table->title.assign(i18n("Administration line with a weak exec timeout"));
		device->addTableHeading(paragraphPointer->table, i18n("Line"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Telnet"), false);
		if (sshSupported == true)
			device->addTableHeading(paragraphPointer->table, i18n("SSH"), false);
		if (device->isRouter == true)
			device->addTableHeading(paragraphPointer->table, i18n("Rlogin"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Exec Timeout"), false);

		linePointer = line;
		found = false;
		while (linePointer != 0)
		{

			// If line is used...
			if (((linePointer->execTimeout > device->config->connectionTimeouts) || (linePointer->execTimeout == 0)) && ((linePointer->telnet == true) || (linePointer->ssh == true) || (linePointer->rlogin == true)) && (linePointer->exec == true) && !((linePointer->password.empty()) && (linePointer->login == loginLinePassword)))
			{
				switch (linePointer->type)
				{
					case lineConsole:
						device->addTableData(paragraphPointer->table, i18n("Console"));
						break;
					case lineVTY:
						tempString.assign(i18n("*ABBREV*VTY*-ABBREV* "));
						tempString.append(device->intToString(linePointer->lineStart));
						if (linePointer->lineEnd != 0)
						{
							tempString.append(" - ");
							tempString.append(device->intToString(linePointer->lineEnd));
						}
						device->addTableData(paragraphPointer->table, tempString.c_str());
						found = true;
						break;
					case lineAUX:
						device->addTableData(paragraphPointer->table, i18n("Auxillary"));
						break;
					default:
						tempString.assign(i18n("*ABBREV*TTY*-ABBREV* "));
						tempString.append(device->intToString(linePointer->lineStart));
						if (linePointer->lineEnd != 0)
						{
							tempString.append(" - ");
							tempString.append(device->intToString(linePointer->lineEnd));	
						}
						device->addTableData(paragraphPointer->table, tempString.c_str());
						found = true;
						break;
				}
				if ((linePointer->type == lineConsole) || (linePointer->type == lineAUX))
				{
					device->addTableData(paragraphPointer->table, i18n("N/A"));
					if (sshSupported == true)
						device->addTableData(paragraphPointer->table, i18n("N/A"));
					if (device->isRouter == true)
						device->addTableData(paragraphPointer->table, i18n("N/A"));
				}
				else
				{
					if (linePointer->telnet == true)
						device->addTableData(paragraphPointer->table, i18n("Yes"));
					else
						device->addTableData(paragraphPointer->table, i18n("No"));
					if (sshSupported == true)
					{
						if (linePointer->ssh == true)
							device->addTableData(paragraphPointer->table, i18n("Yes"));
						else
							device->addTableData(paragraphPointer->table, i18n("No"));
					}
					if (device->isRouter == true)
					{
						if (linePointer->rlogin == true)
							device->addTableData(paragraphPointer->table, i18n("Yes"));
						else
							device->addTableData(paragraphPointer->table, i18n("No"));
					}
				}
				if (linePointer->execTimeout == 0)
					device->addTableData(paragraphPointer->table, i18n("None"));
				else
				{
					tempString.assign(device->timeToString(linePointer->execTimeout));
					device->addTableData(paragraphPointer->table, tempString.c_str());
				}
			}
			linePointer = linePointer->next;
		}

		// Issue impact...
		securityIssuePointer->impactRating = 7;			// High
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("If a connection is not properly terminated, it may be possible for an attacker to make use of the connection in order to gain access to the device. If successful, the attacker would gain access with the privileges of the previous user."));

		// Issue ease...
		securityIssuePointer->easeRating = 7;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.assign(i18n("There are a number of different ways that an attacker could exploit this issue, some are dependent on the service protocol or connection type. To remotely exploit this issue, the attacker would normally have to be able to monitor the remote connection unless the administrators management host is part of the attack. A number of tools are available on the Internet that can monitor network traffic or perform a man in the middle attacks."));
		if (found == false)
		{
			securityIssuePointer->easeRating = 3;
			paragraphPointer->paragraph.append(i18n(" For a console connection to *DEVICENAME*, an attacker would require physical access to the device."));
		}

		// Issue recommendation...
		securityIssuePointer->fixRating = 2;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		device->addString(paragraphPointer, device->timeToString(device->config->connectionTimeouts));
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that a timeout period of *DATA* should be configured for exec connections to *DEVICENAME*."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("An exec timeout can be configured on a line with the following line mode command:*CODE**COMMAND*exec-timeout *CMDUSER*minutes*-CMDUSER* *CMDOPTION*seconds*-CMDOPTION**-COMMAND**-CODE*"));

		// Conclusions text...
		if (lineAclInMissingCount > 1)
			securityIssuePointer->conLine.append(i18n("weak exec line timeouts were configured"));
		else
			securityIssuePointer->conLine.append(i18n("a weak exec line timeouts was configured"));

		// Recommendation list text...
		tempString.assign(i18n("Configure an exec line connection timeout of "));
		tempString.append(device->timeToString(device->config->connectionTimeouts));
		device->addRecommendation(securityIssuePointer, tempString.c_str());

		// Related issues...
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMITELN.1");
	}


	if (lineWithTACACSCount > 0)
	{
	}


	if (lineWithoutAuthorisation > 0)
	{ }


	if (lineWithoutAccounting > 0)
	{ }


	// Output protocol transport support...
	if (lineWithOutputTransport > 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Outbound Administrative Access Configured\n", device->config->COL_BLUE, device->config->COL_RESET);
		
		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("Outbound Administrative Access Configured"));
		securityIssuePointer->reference.assign("IOS.LINETROT.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("It is possible to remotely connect to other devices from *DEVICENAME* using Telnet and other protocols using the built in client software. This enables an administrator who is connected to *DEVICENAME* to quickly connect to other devices on the network, it could be that it is the only way an administrator can connect to the other devices if the network filtering on those devices only allows access from *DEVICENAME*."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addValue(paragraphPointer, lineWithOutputTransport);
		if (lineWithOutputTransport > 1)
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* lines were configured to enable outbound administration. These lines are listed in Table *TABLEREF*."));
		else
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* line was configured to enable outbound administration. This line is shown in Table *TABLEREF*."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "SEC-LINEOUTPUTENABLED-TABLE");
		if (errorCode != 0)
			return errorCode;
		if (lineWithOutputTransport > 1)
			paragraphPointer->table->title.assign(i18n("Lines with outbound administration enabled"));
		else
			paragraphPointer->table->title.assign(i18n("Line with outbound administration enabled"));
		device->addTableHeading(paragraphPointer->table, i18n("Line"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Outbound *ABBREV*ACL*-ABBREV*"), false);

		linePointer = line;
		found = true;
		consoleAccessOnly = true;
		while (linePointer != 0)
		{

			// If line is used...
			if ((linePointer->type != lineAUX) && (linePointer->type != lineConsole) && (linePointer->output == true))
			{
				switch (linePointer->type)
				{
					case lineVTY:
						tempString.assign(i18n("*ABBREV*VTY*-ABBREV* "));
						tempString.append(device->intToString(linePointer->lineStart));
						if (linePointer->lineEnd != 0)
						{
							tempString.append(" - ");
							tempString.append(device->intToString(linePointer->lineEnd));
						}
						device->addTableData(paragraphPointer->table, tempString.c_str());
						break;
					default:
						tempString.assign(i18n("*ABBREV*TTY*-ABBREV* "));
						tempString.append(device->intToString(linePointer->lineStart));
						if (linePointer->lineEnd != 0)
						{
							tempString.append(" - ");
							tempString.append(device->intToString(linePointer->lineEnd));	
						}
						device->addTableData(paragraphPointer->table, tempString.c_str());
						break;
				}
				device->addTableData(paragraphPointer->table, linePointer->aclOut.c_str());
			}
			linePointer = linePointer->next;
		}

		// Issue impact...
		securityIssuePointer->impactRating = 2;				// Information
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("If an attacker were able to gain a level of access to *DEVICENAME* they could use the device to attack and potentially gain access to other network hosts. If the attacker had administrative access to *DEVICENAME* they could reconfigure this level of access themselves. However, if they were to have a lower level of access, they would require *DEVICENAME* to already be configured to alow access to other devices."));
		if (lineOuputNoAcl > 0)
		{
			securityIssuePointer->easeRating = 1;
			paragraphPointer->paragraph.append(i18n(" Furthermore, without assigning an *ABBREV*ACL*-ABBREV* for outbound connections the attacker would not be prevented by *DEVICENAME* from connecting to any network host."));
		}

		// Issue ease...
		securityIssuePointer->easeRating = 2;				// Challenging
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.assign(i18n("In order to use *DEVICENAME* to attack other network devices the attacker would already need to have access to *DEVICENAME*."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 2;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, unless require, *DEVICETYPE* devices should be configured to prevent using the device to access other network devices."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("Administrative outbound access to other network devices can be disabled on *DEVICETYPE* devices with the following line command:*CODE**COMMAND*transport output none*-COMMAND**-CODE*"));

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("outbound administration was enabled"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Disable outbound administration"));

		// Related issues...
		device->addRelatedIssue(securityIssuePointer, "IOS.LINEACLO.1");
	}


	// Output protocol transport support without acl...
	if (lineOuputNoAcl > 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Unrestricted Outbound Administrative Access\n", device->config->COL_BLUE, device->config->COL_RESET);
		
		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("Unrestricted Outbound Administrative Access"));
		securityIssuePointer->reference.assign("IOS.LINEACLO.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("It is possible to remotely connect to other devices from *DEVICENAME* using Telnet and other protocols using the built in client software. This access can be restricted to specific hosts with the use of an *ABBREV*ACL*-ABBREV* in order to permit access to only a limited number of hosts."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addValue(paragraphPointer, lineOuputNoAcl);
		if (lineOuputNoAcl > 1)
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* lines were configured to enable outbound administration without an *ABBREV*ACL*-ABBREV* to restrict host access. These lines are listed in Table *TABLEREF*."));
		else
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* line was configured to enable outbound administration without an *ABBREV*ACL*-ABBREV* to restrict host access. This line is shown in Table *TABLEREF*."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "SEC-LINEOUTPUTNOACL-TABLE");
		if (errorCode != 0)
			return errorCode;
		if (lineOuputNoAcl > 1)
			paragraphPointer->table->title.assign(i18n("Lines with outbound administration enabled"));
		else
			paragraphPointer->table->title.assign(i18n("Line with outbound administration enabled"));
		device->addTableHeading(paragraphPointer->table, i18n("Line"), false);

		linePointer = line;
		found = true;
		consoleAccessOnly = true;
		while (linePointer != 0)
		{

			// If line is used...
			if ((linePointer->type != lineAUX) && (linePointer->type != lineConsole) && (linePointer->output == true) && (linePointer->aclOut.empty()))
			{
				switch (linePointer->type)
				{
					case lineVTY:
						tempString.assign(i18n("*ABBREV*VTY*-ABBREV* "));
						tempString.append(device->intToString(linePointer->lineStart));
						if (linePointer->lineEnd != 0)
						{
							tempString.append(" - ");
							tempString.append(device->intToString(linePointer->lineEnd));
						}
						device->addTableData(paragraphPointer->table, tempString.c_str());
						break;
					default:
						tempString.assign(i18n("*ABBREV*TTY*-ABBREV* "));
						tempString.append(device->intToString(linePointer->lineStart));
						if (linePointer->lineEnd != 0)
						{
							tempString.append(" - ");
							tempString.append(device->intToString(linePointer->lineEnd));	
						}
						device->addTableData(paragraphPointer->table, tempString.c_str());
						break;
				}
			}
			linePointer = linePointer->next;
		}

		// Issue impact...
		securityIssuePointer->impactRating = 2;				// Information
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("If an attacker were able to gain a level of access to *DEVICENAME* they could use the device to attack and potentially gain access to other network hosts. With no *ABBREV*ACL*-ABBREV*, the attacker would not be restricted to specific hosts."));

		// Issue ease...
		securityIssuePointer->easeRating = 2;				// Challenging
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.assign(i18n("In order to use *DEVICENAME* to attack other network devices the attacker would already need to have access to *DEVICENAME*."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 2;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, unless require, *DEVICETYPE* devices should be configured to prevent using the device to access other network devices. However, if outbound administrative access is required, *COMPANY* recommends that an *ABBREV*ACL*-ABBREV* is configured to restrict access to specific hosts."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("Administrative outbound access to other network devices can be disabled on *DEVICETYPE* devices with the following line command:*CODE**COMMAND*transport output none*-COMMAND**-CODE*"));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("A *ABBREV*ACL*-ABBREV* can be configured with the following commands:*CODE**COMMAND*ip access-list standard *CMDUSER*access-list-number*-CMDUSER**-COMMAND**COMMAND*remark *CMDUSER*description*-CMDUSER**-COMMAND**COMMAND*permit *CMDUSER*ip-address*-CMDUSER* *CMDUSER*wildcard*-CMDUSER* *CMDOPTION*log*-CMDOPTION**-COMMAND**-CODE*"));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("The *ABBREV*ACL*-ABBREV* can then be applied to a line, from line configuration mode, using the following command:*CODE**COMMAND*access-class *CMDUSER*access-list-number*-CMDUSER* out*-COMMAND**-CODE*"));

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("outbound administration was enabled without access restrictions"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Disable outbound administration"), true);
		device->addRecommendation(securityIssuePointer, i18n("Configure a *ABBREV*ACL*-ABBREV*"));
		device->addRecommendation(securityIssuePointer, i18n("Apply the *ABBREV*ACL*-ABBREV* to the outbound line configuration"));

		// Dependent issues...
		device->addDependency(securityIssuePointer, "IOS.LINETROT.1");
	}


	// Lines not requiring a password to login
	if (lineLoginWithoutPassword > 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Administrative Service Login With No Password\n", device->config->COL_BLUE, device->config->COL_RESET);
		
		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("Administrative Service Login With No Password"));
		securityIssuePointer->reference.assign("IOS.LINENOPA.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("The Telnet, *ABBREV*SSH*-ABBREV* and console-based access to *DEVICETYPE* devices are configured using the line configuration. It is possible to configure different authentication methods to the device, including not requiring any authentication."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addValue(paragraphPointer, lineLoginWithoutPassword);
		if (lineLoginWithoutPassword > 1)
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* lines were configured in a way that no authentication is required. These lines are listed in Table *TABLEREF*."));
		else
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* line was configured in a way that no authentication is required. This line is shown in Table *TABLEREF*."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "SEC-LINENOAUTH-TABLE");
		if (errorCode != 0)
			return errorCode;
		if (lineLoginWithoutPassword > 1)
			paragraphPointer->table->title.assign(i18n("Administration lines that do not require authentication"));
		else
			paragraphPointer->table->title.assign(i18n("Administration line that does not require authentication"));
		device->addTableHeading(paragraphPointer->table, i18n("Line"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Exec"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Login"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Level"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Telnet"), false);
		if (sshSupported == true)
			device->addTableHeading(paragraphPointer->table, i18n("SSH"), false);
		if (device->isRouter == true)
			device->addTableHeading(paragraphPointer->table, i18n("Rlogin"), false);

		linePointer = line;
		found = true;
		consoleAccessOnly = true;
		while (linePointer != 0)
		{

			// If line is used...
			if ((linePointer->login == loginWithNoPassword) && ((linePointer->telnet == true) || (linePointer->ssh == true) || (linePointer->rlogin == true)) && (linePointer->exec == true) && !((linePointer->password.empty()) && (linePointer->login == loginLinePassword)))
			{
				switch (linePointer->type)
				{
					case lineConsole:
						device->addTableData(paragraphPointer->table, i18n("Console"));
						break;
					case lineVTY:
						tempString.assign(i18n("*ABBREV*VTY*-ABBREV* "));
						tempString.append(device->intToString(linePointer->lineStart));
						if (linePointer->lineEnd != 0)
						{
							tempString.append(" - ");
							tempString.append(device->intToString(linePointer->lineEnd));
						}
						device->addTableData(paragraphPointer->table, tempString.c_str());
						break;
					case lineAUX:
						device->addTableData(paragraphPointer->table, i18n("Auxillary"));
						break;
					default:
						tempString.assign(i18n("*ABBREV*TTY*-ABBREV* "));
						tempString.append(device->intToString(linePointer->lineStart));
						if (linePointer->lineEnd != 0)
						{
							tempString.append(" - ");
							tempString.append(device->intToString(linePointer->lineEnd));	
						}
						device->addTableData(paragraphPointer->table, tempString.c_str());
						break;
				}
				if (linePointer->exec == true)
				{
					device->addTableData(paragraphPointer->table, i18n("Yes"));
					switch (linePointer->login)
					{
						case loginWithNoPassword:
							device->addTableData(paragraphPointer->table, i18n("No Authentication"));
							found = true;
							break;
						case loginLinePassword:
							device->addTableData(paragraphPointer->table, i18n("Line Password"));
							break;
						case loginLocal:
							device->addTableData(paragraphPointer->table, i18n("Local Users"));
							break;
						case loginTACACS:
							device->addTableData(paragraphPointer->table, i18n("TACACS Style"));
							break;
						default:
							device->addTableData(paragraphPointer->table, i18n("AAA Authentication"));
							break;
					}
				}
				else
				{
					device->addTableData(paragraphPointer->table, i18n("No"));
					device->addTableData(paragraphPointer->table, i18n("N/A"));
				}
				tempString.assign(device->intToString(linePointer->privilege));
				device->addTableData(paragraphPointer->table, tempString.c_str());
				if (linePointer->telnet == true)
					device->addTableData(paragraphPointer->table, i18n("Yes"));
				else
					device->addTableData(paragraphPointer->table, i18n("No"));
				if (sshSupported == true)
				{
					if (linePointer->ssh == true)
						device->addTableData(paragraphPointer->table, i18n("Yes"));
					else
						device->addTableData(paragraphPointer->table, i18n("No"));
				}
				if (device->isRouter == true)
				{
					if (linePointer->rlogin == true)
						device->addTableData(paragraphPointer->table, i18n("Yes"));
					else
						device->addTableData(paragraphPointer->table, i18n("No"));
				}
				if ((linePointer->type != lineConsole) && (!linePointer->aclIn.empty()))
					found = false;
				if (linePointer->type != lineConsole)
					consoleAccessOnly = false;
			}
			linePointer = linePointer->next;
		}

		// Issue impact...
		securityIssuePointer->impactRating = 9;			// Critical
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("With no authentication required, an attacker or malicious user who is able to access one of the administration interfaces configured on the lines detailed above would gain access without authenticating."));

		// Issue ease...
		securityIssuePointer->easeRating = 8;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.assign(i18n("The attacker or malicious user would simply have to connect to *DEVICENAME*, no authentication would be requested."));
		if (consoleAccessOnly == true)
		{
			securityIssuePointer->easeRating = 3;
			paragraphPointer->paragraph.append(i18n(" However, for console access the attacker would require physical access to the device."));
		}
		else if (found == true)
		{
			securityIssuePointer->easeRating = 4;
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			paragraphPointer->paragraph.append(i18n("*ABBREV*ACL*-ABBREV* have been configured on the lines in order to restrict administrative access to *DEVICENAME*. However, a skilled attacker may be able to bypass any network access restrictions."));
		}

		// Issue recommendation...
		securityIssuePointer->fixRating = 3;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that all administrative access should require authentication."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("Authentication can be configured on lines using the following line mode command:*CODE**COMMAND*login *CMDOPTION*tacacs *CMDOR* local*-CMDOPTION**-COMMAND**-CODE*"));

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("authentication was not required for all administrative access"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Configure authentication only access for all administrative lines"));

		// Related issues...
		device->addRelatedIssue(securityIssuePointer, "GEN.ADMITELN.1");
		device->addRelatedIssue(securityIssuePointer, "IOS.LINENACL.1");
	}


	if (lineWithTransportInputAll > 0)
	{ }


	if (lineWithRLogin > 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Clear Text Rlogin Protocol Service\n", device->config->COL_BLUE, device->config->COL_RESET);
		
		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("Clear Text Rlogin Protocol Service"));
		securityIssuePointer->reference.assign("IOR.LINERLOG.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("The Rlogin service enables network administrators to remotely manage *DEVICETYPE* devices. However, the protocol provides no encryption or encoding, so all network traffic, including the authentication, is transmitted between the client and the server in clear text."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addValue(paragraphPointer, lineWithRLogin);
		if (lineWithRLogin > 1)
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* lines had the Rlogin service enabled. These lines are listed in Table *TABLEREF*."));
		else
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* line had the Rlogin service enabled. This line is shown in Table *TABLEREF*."));

		// Table...
		errorCode = device->addTable(paragraphPointer, "SEC-LINERLOGIN-TABLE");
		if (errorCode != 0)
			return errorCode;
		if (lineWithRLogin > 1)
			paragraphPointer->table->title.assign(i18n("Administration lines that have the Rlogin service enabled"));
		else
			paragraphPointer->table->title.assign(i18n("Administration line that has the Rlogin service enabled"));
		device->addTableHeading(paragraphPointer->table, i18n("Line"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Exec"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Login"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Level"), false);
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*ACL*-ABBREV*"), false);

		linePointer = line;
		found = true;
		while (linePointer != 0)
		{

			// If line is used...
			if ((linePointer->type == lineVTY) && (linePointer->rlogin == true) && (linePointer->exec == true) && !((linePointer->password.empty()) && (linePointer->login == loginLinePassword)))
			{
				switch (linePointer->type)
				{
					case lineConsole:
						device->addTableData(paragraphPointer->table, i18n("Console"));
						break;
					case lineVTY:
						tempString.assign(i18n("*ABBREV*VTY*-ABBREV* "));
						tempString.append(device->intToString(linePointer->lineStart));
						if (linePointer->lineEnd != 0)
						{
							tempString.append(" - ");
							tempString.append(device->intToString(linePointer->lineEnd));
						}
						device->addTableData(paragraphPointer->table, tempString.c_str());
						break;
					case lineAUX:
						device->addTableData(paragraphPointer->table, i18n("Auxillary"));
						break;
					default:
						tempString.assign(i18n("*ABBREV*TTY*-ABBREV* "));
						tempString.append(device->intToString(linePointer->lineStart));
						if (linePointer->lineEnd != 0)
						{
							tempString.append(" - ");
							tempString.append(device->intToString(linePointer->lineEnd));	
						}
						device->addTableData(paragraphPointer->table, tempString.c_str());
						break;
				}
				if (linePointer->exec == true)
				{
					device->addTableData(paragraphPointer->table, i18n("Yes"));
					switch (linePointer->login)
					{
						case loginWithNoPassword:
							device->addTableData(paragraphPointer->table, i18n("No Authentication"));
							break;
						case loginLinePassword:
							device->addTableData(paragraphPointer->table, i18n("Line Password"));
							break;
						case loginLocal:
							device->addTableData(paragraphPointer->table, i18n("Local Users"));
							break;
						case loginTACACS:
							device->addTableData(paragraphPointer->table, i18n("TACACS Style"));
							break;
						default:
							device->addTableData(paragraphPointer->table, i18n("AAA Authentication"));
							break;
					}
				}
				else
				{
					device->addTableData(paragraphPointer->table, i18n("No"));
					device->addTableData(paragraphPointer->table, i18n("N/A"));
				}
				tempString.assign(device->intToString(linePointer->privilege));
				device->addTableData(paragraphPointer->table, tempString.c_str());
				device->addTableData(paragraphPointer->table, linePointer->aclIn.c_str());
				if (linePointer->aclIn.empty())
					found = false;
			}
			linePointer = linePointer->next;
		}

		// Issue impact...
		securityIssuePointer->impactRating = 8;			// HIGH
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("An attacker or malicious user who was able to monitor the network traffic between a Rlogin server and client would be able to capture the authentication credentials and any data. Furthermore, the attacker could then use the authentication credentials to gain a level of access to *DEVICENAME*."));

		// Issue ease...
		securityIssuePointer->easeRating = 7;				// EASY
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		paragraphPointer->paragraph.assign(i18n("Network packet and password sniffing tools are widely available on the Internet and some of the tools are specifically designed to capture clear-text protocol authentication credentials. In a switched environment an attacker may not be able to capture network traffic destined for other devices without performing an additional attack, such as exploiting *ABBREV*ARP*-ABBREV* or routing vulnerabilities."));
		if (found == true)
		{
			securityIssuePointer->easeRating = 4;
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			paragraphPointer->paragraph.append(i18n("Although access to the Rlogin service has been restricted with the use of *ABBREV*ACLs*-ABBREV*, a skilled attacker may be able to bypass any network filtering in order to gain access."));
		}

		// Issue recommendation...
		securityIssuePointer->fixRating = 3;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that all clear text protocol services should be replaced by their cryptographically secure counterparts."));
		if (sshEnabled == true)
		{
			paragraphPointer->paragraph.append(i18n(" The *ABBREV*SSH*-ABBREV* service is already configured on *DEVICENAME*. *COMPANY* recommends that this should be used as a cryptographically secure alternative to Rlogin."));
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(i18n("The Rlogin and *ABBREV*SSH*-ABBREV* services are both configured or disabled using the same line command. To disable Rlogin and enable *ABBREV*SSH*-ABBREV* use the following line mode command:*CODE**COMMAND*transport input ssh*-COMMAND**-CODE*"));
		}
		else if (sshSupported == true)
		{
			paragraphPointer->paragraph.append(i18n(" *DEVICETYPE* devices support the *ABBREV*SSH*-ABBREV* service, which is a cryptographically secure alternative to Rlogin. *COMPANY* recommends that this service should be used as an alternative."));
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(i18n("The Rlogin and *ABBREV*SSH*-ABBREV* services are both configured or disabled using the same line command. To disable Rlogin and enable *ABBREV*SSH*-ABBREV* use the following line mode command:*CODE**COMMAND*transport input ssh*-COMMAND**-CODE*"));
		}
		else
		{
			securityIssuePointer->fixRating = 8;				// Involved
			paragraphPointer->paragraph.append(i18n(" *COMPANY* recommends that the *ABBREV*SSH*-ABBREV* service is used as a cryptographically secure alternative to Rlogin. However, the *DEVICEOS* will need to be upgraded to a version that supports the *ABBREV*SSH*-ABBREV* service."));
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(i18n("Rlogin can be disabled with the following line mode command:*CODE**COMMAND*transport input none*-COMMAND**-CODE*"));
		}

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("the Rlogin service was enabled"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Disable the Rlogin service"));

		// Related issues...
		device->addRelatedIssue(securityIssuePointer, "IOS.LINENACL.1");
	}

	return errorCode;
}

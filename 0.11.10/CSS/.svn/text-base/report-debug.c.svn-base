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


void reportCSSDebug(struct nipperConfig *nipper)
{
	// Variables
	struct snmpCSSCommunity *snmpCSSCommunityPointer = 0;
	struct snmpCSSHost *snmpCSSHostPointer = 0;

	// Setting info
	printf("\n\nFor some debug settings...\n");
	printf("True or Enabled = %d\n", true);
	printf("False or Disabled = %d\n", false);
	printf("Unconfigured = %d\n\n", unconfigured);

	// General Info
	printf("\n%sInformation Collected\n=====================%s\n", COL_BLUE, RESET);
	printf("Hostname: %s\n", nipper->hostname);
	printf("IOS Version: %s\n", nipper->version);
	printf("IOS Version: %d.%d(%d)\n", nipper->versionMajor, nipper->versionMinor, nipper->versionRevision);
	printf("SNMP Access: %d\n", nipper->css->snmpAccess);
	printf("FTP Access: %d\n", nipper->css->ftpAccess);
	printf("Telnet Access: %d\n", nipper->css->telnetAccess);
	printf("SSH Access: %d\n", nipper->css->sshAccess);
	printf("Console Access: %d\n", nipper->css->consoleAccess);
	printf("Web Management Access: %d\n", nipper->css->webManagementAccess);
	printf("ACL Enabled: %d\n", nipper->css->aclEnabled);

	// Filter Rules...
	reportRulesDebug(nipper);

	// SNMP
	if (nipper->css->snmp != 0)
	{
		printf("SNMP Host Name: %s\n", nipper->css->snmp->name);
		printf("SNMP Contact: %s\n", nipper->css->snmp->contact);
		printf("SNMP Location: %s\n", nipper->css->snmp->location);
		printf("SNMP Reload Enabled: %d\n", nipper->css->snmp->reloadEnabled);
		snmpCSSCommunityPointer = nipper->css->snmp->community;
		while (snmpCSSCommunityPointer != 0)
		{
			printf("SNMP Community: %s\n", snmpCSSCommunityPointer->community);
			printf("  Read Only: %d\n", snmpCSSCommunityPointer->readOnly);
			snmpCSSCommunityPointer = snmpCSSCommunityPointer->next;
		}
		snmpCSSHostPointer = nipper->css->snmp->host;
		while (snmpCSSHostPointer != 0)
		{
			printf("SNMP Host: %s\n", snmpCSSHostPointer->host);
			printf("  SNMP Community: %s\n", snmpCSSHostPointer->community);
			printf("  Host Type: %d\n", snmpCSSHostPointer->snmpType);
			snmpCSSHostPointer = snmpCSSHostPointer->next;
		}
	}
}

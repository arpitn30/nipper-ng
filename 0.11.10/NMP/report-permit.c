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

// This file contains the code for NMP / CatOS reporting

void nmpPermitConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct hostNMP *hostNMPPointer = 0;
	char tempString[nipper->maxSize];

	output_table(nipper, true, settings_permit_table, &settings_permit_heading);
	if (nipper->nmp->permit->telnet == true)
		fprintf(nipper->reportFile, "%sTelnet%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else if (nipper->nmp->permit->telnet == false)
		fprintf(nipper->reportFile, "%sTelnet%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sTelnet%sDefault%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->nmp->permit->ssh == true)
		fprintf(nipper->reportFile, "%sSSH%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else if (nipper->nmp->permit->ssh == false)
		fprintf(nipper->reportFile, "%sSSH%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sSSH%sDefault%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->nmp->permit->snmp == true)
		fprintf(nipper->reportFile, "%sSNMP%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else if (nipper->nmp->permit->snmp == false)
		fprintf(nipper->reportFile, "%sSNMP%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sSNMP%sDefault%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	output_table(nipper, false, settings_permit_table, &settings_permit_heading);
	addAbbreviation("SNMP", false);
	addAbbreviation("SSH", false);

	// Telnet Permission List
	if (nipper->nmp->permit->telnet == true)
	{
		output_table(nipper, true, "Telnet permit list", &settings_permitlist_heading);
		hostNMPPointer = nipper->nmp->permit->telnetHost;
		while (hostNMPPointer != 0)
		{
			outputFriendly(hostNMPPointer->host, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid, hostNMPPointer->netMask, nipper->tablerow_end);
			hostNMPPointer = hostNMPPointer->next;
		}
		output_table(nipper, false, "Telnet permit list", &settings_permitlist_heading);
	}

	// SSH Permission List
	if (nipper->nmp->permit->ssh == true)
	{
		output_table(nipper, true, "SSH permit list", &settings_permitlist_heading);
		hostNMPPointer = nipper->nmp->permit->sshHost;
		while (hostNMPPointer != 0)
		{
			outputFriendly(hostNMPPointer->host, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid, hostNMPPointer->netMask, nipper->tablerow_end);
			hostNMPPointer = hostNMPPointer->next;
		}
		output_table(nipper, false, "SSH permit list", &settings_permitlist_heading);
	}

	// SNMP Permission List
	if (nipper->nmp->permit->snmp == true)
	{
		output_table(nipper, true, "SNMP permit list", &settings_permitlist_heading);
		hostNMPPointer = nipper->nmp->permit->snmpHost;
		while (hostNMPPointer != 0)
		{
			outputFriendly(hostNMPPointer->host, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid, hostNMPPointer->netMask, nipper->tablerow_end);
			hostNMPPointer = hostNMPPointer->next;
		}
		output_table(nipper, false, "SNMP permit list", &settings_permitlist_heading);
	}
}

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

// This file contains code for ScreenOS SNMP reporting


void sosSNMPConfig(struct nipperConfig *nipper)
{
	// Variables...
	char tempString[nipper->maxSize];
	struct snmpCommunitySOS *communityPointer = 0;
	struct snmpHostSOS *snmpHostPointer = 0;
	
	// General SNMP Settings...
	output_table(nipper, true, settings_snmp_sos_table, &settings_general_heading);
	if (nipper->sos->snmp->systemName[0] != 0)
	{
		outputFriendly(nipper->sos->snmp->systemName, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%sSystem Name%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
	}
	if (nipper->sos->snmp->contact[0] != 0)
	{
		outputFriendly(nipper->sos->snmp->contact, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%sContact%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
	}
	if (nipper->sos->snmp->location[0] != 0)
	{
		outputFriendly(nipper->sos->snmp->location, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%sLocation%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
	}
	fprintf(nipper->reportFile, "%sSNMP Port%s%d%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->sos->snmp->listenPort, nipper->tablerow_end);
	fprintf(nipper->reportFile, "%sSNMP Trap Port%s%d%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->sos->snmp->trapPort, nipper->tablerow_end);
	if (nipper->sos->snmp->authTrap == true)
		fprintf(nipper->reportFile, "%sAuthentication Traps%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sAuthentication Traps%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	output_table(nipper, false, settings_snmp_sos_table, &settings_general_heading);

	// SNMP Communities...
	if (nipper->sos->snmp->community != 0)
	{
		output_table(nipper, true, settings_snmpstring_table, &settings_snmpstring_sos_heading);
		communityPointer = nipper->sos->snmp->community;
		while (communityPointer != 0)
		{
			fprintf(nipper->reportFile, "%s", nipper->tablerow_start);
			if (nipper->passwords == true)
			{
				outputFriendly(communityPointer->community, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
			}
			switch (communityPointer->version)
			{
				case snmp1_2:
					fprintf(nipper->reportFile, "1 and 2%s", nipper->tablerow_mid);
					break;
				case snmp1:
					fprintf(nipper->reportFile, "1%s", nipper->tablerow_mid);
					break;
				case snmp2c:
					fprintf(nipper->reportFile, "2%s", nipper->tablerow_mid);
					break;
			}
			if (communityPointer->readOnly == true)
				fprintf(nipper->reportFile, "Read Only%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "Read/Write%s", nipper->tablerow_mid);
			if (communityPointer->enableTraps == true)
				fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
			if (communityPointer->trafficTraps == true)
				fprintf(nipper->reportFile, "On%s", nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "Off%s", nipper->tablerow_end);
			communityPointer = communityPointer->next;
		}
		output_table(nipper, false, settings_snmpstring_table, &settings_snmpstring_sos_heading);
	}
	
	// SNMP Hosts...
	if (nipper->sos->snmp->host != 0)
	{
		output_table(nipper, true, settings_snmphost_table, &settings_snmphost_sos_heading);
		snmpHostPointer = nipper->sos->snmp->host;
		while (snmpHostPointer != 0)
		{
			outputFriendly(snmpHostPointer->host, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
			if (nipper->passwords == true)
			{
				outputFriendly(snmpHostPointer->community, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
			}
			switch (snmpHostPointer->version)
			{
				case snmp1_2:
					fprintf(nipper->reportFile, "1 and 2%s", nipper->tablerow_mid);
					break;
				case snmp1:
					fprintf(nipper->reportFile, "1%s", nipper->tablerow_mid);
					break;
				case snmp2c:
					fprintf(nipper->reportFile, "2%s", nipper->tablerow_mid);
					break;
			}
			outputFriendly(snmpHostPointer->sourceInterface, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_end);
			snmpHostPointer = snmpHostPointer->next;
		}
		output_table(nipper, false, settings_snmphost_table, &settings_snmphost_sos_heading);
	}
}


void sosSNMPIssue(struct nipperConfig *nipper)
{
	if (nipper->sos->snmp->host == 0)
		output_parseText(report_snmp_css_obs, nipper, section_obs, rate_none, 0, nipper->tableNum);
	else
		output_parseText(report_snmp_css_obs, nipper, section_obs, rate_none, -1, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_snmp_impact, nipper, section_imp, rate_med, 0, 0);
	output_endsection(nipper, section_imp);
	output_parseText(report_snmp_ease, nipper, section_ease, rate_difficult, 0, 0);
	output_endsection(nipper, section_ease);
	if (nipper->sos->snmp->host == 0)
		output_parseText(report_snmp_sos_rec, nipper, section_obs, rate_none, 0, nipper->tableNum);
	else
		output_parseText(report_snmp_sos_rec, nipper, section_obs, rate_none, -1, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


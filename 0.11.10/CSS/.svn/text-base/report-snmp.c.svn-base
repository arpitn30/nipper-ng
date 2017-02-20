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

// This file contains code for CSS SNMP reporting

void cssSNMPIssue(struct nipperConfig *nipper)
{
	output_parseText(settings_snmp_desc, nipper, section_obs, rate_none, 0, nipper->tableNum);
	if (nipper->css->snmp != 0)
	{
		if (nipper->css->snmp->host != 0)
			output_parseText(report_snmp_css_obs, nipper, section_none, rate_none, -1, nipper->tableNum);
		else
			output_parseText(report_snmp_css_obs, nipper, section_none, rate_none, 0, nipper->tableNum);
	}
	else
		output_parseText(report_snmp_css_obs, nipper, section_none, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_snmp_impact, nipper, section_imp, rate_med, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_snmp_ease, nipper, section_ease, rate_trivial, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	if (nipper->css->snmp != 0)
	{
		if (nipper->css->snmp->host != 0)
			output_parseText(report_snmp_css_rec, nipper, section_rec, rate_none, -1, nipper->tableNum);
		else
			output_parseText(report_snmp_css_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	}
	else
		output_parseText(report_snmp_css_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void cssSNMPConfig(struct nipperConfig *nipper)
{
	// Variables...
	char tempString[nipper->maxSize];
	struct snmpCSSCommunity *snmpCSSCommunityPointer = 0;
	struct snmpCSSHost *snmpCSSHostPointer = 0;

	output_parseText(settings_snmp_desc, nipper, section_none, rate_none, -1, 0);

	// SNMP Settings
	output_table(nipper, true, settings_snmp_table, &settings_general_heading);
	outputFriendly(nipper->css->snmp->name, tempString, nipper->maxSize, nipper->outputFormat);
	fprintf(nipper->reportFile, "%sHostname%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
	outputFriendly(nipper->css->snmp->contact, tempString, nipper->maxSize, nipper->outputFormat);
	fprintf(nipper->reportFile, "%sContact%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
	outputFriendly(nipper->css->snmp->location, tempString, nipper->maxSize, nipper->outputFormat);
	fprintf(nipper->reportFile, "%sLocation%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
	if (nipper->css->snmp->reloadEnabled == true)
		fprintf(nipper->reportFile, "%sSNMP Device Reload%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sSNMP Device Reload%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	output_table(nipper, false, settings_snmp_table, &settings_general_heading);

	// SNMP Community
	if (nipper->passwords == true)
	{
		snmpCSSCommunityPointer = nipper->css->snmp->community;
		output_table(nipper, true, settings_snmpstring_table, &settings_snmp_css_heading);
		while (snmpCSSCommunityPointer != 0)
		{
			outputFriendly(snmpCSSCommunityPointer->community, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
			if (snmpCSSCommunityPointer->readOnly)
				fprintf(nipper->reportFile, "Read Only%s", nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "Read-Write%s", nipper->tablerow_end);
			snmpCSSCommunityPointer = snmpCSSCommunityPointer->next;
		}
		output_table(nipper, false, settings_snmpstring_table, &settings_snmp_css_heading);
	}

	snmpCSSHostPointer = nipper->css->snmp->host;
	output_table(nipper, true, settings_snmphost_table, &settings_snmphost_heading);
	while (snmpCSSHostPointer != 0)
	{
		outputFriendly(snmpCSSHostPointer->host, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
		if (snmpCSSHostPointer->snmpType == snmp1)
			fprintf(nipper->reportFile, "SNMP v1");
		else
			fprintf(nipper->reportFile, "SNMP v2c");
		if (nipper->passwords == true)
		{
			outputFriendly(snmpCSSHostPointer->community, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, tempString);
		}
		fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
		snmpCSSHostPointer = snmpCSSHostPointer->next;
	}
	output_table(nipper, false, settings_snmphost_table, &settings_snmphost_heading);
}

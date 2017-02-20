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

// This file contains the code for IOS reporting

void iosSSHConfig(struct nipperConfig *nipper)
{
	// Variables...
	int tempInt = 0;
	char tempString[nipper->maxSize];
	struct lineConfig *linePointer = 0;
	struct netInterface *interfacePointer = 0;

	output_table(nipper, true, settings_ssh_table, &settings_general_heading);
	if (nipper->ios->line != 0)
	{
		tempInt = 0;
		linePointer = nipper->ios->line;
		while (linePointer != 0)
		{
			if (linePointer->ssh == true)
				tempInt++;
			linePointer = linePointer->next;
		}
	}
	switch (tempInt)
	{
		case 0:
			fprintf(nipper->reportFile, "%sSSH%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
		default:
			fprintf(nipper->reportFile, "%sSSH%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
	}
	switch (nipper->ios->ssh->protocolVersion)
	{
		case ssh_ver_1:
			fprintf(nipper->reportFile, "%sProtocol version%s1%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
		case ssh_ver_2:
			fprintf(nipper->reportFile, "%sProtocol version%s2%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
		default:
			fprintf(nipper->reportFile, "%sProtocol version%sDefault%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
	}
	if (nipper->ios->ssh->timeout > -1)
		fprintf(nipper->reportFile, "%sLogin time-out%s%d%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->ios->ssh->timeout, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sLogin time-out%sDefault%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->ios->ssh->retries > -1)
		fprintf(nipper->reportFile, "%sLogin retries%s%d%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->ios->ssh->retries, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sLogin retries%sDefault%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	output_table(nipper, false, settings_ssh_table, &settings_general_heading);
	addAbbreviation("SSH", false);

	// Show SSH interfaces
	if (nipper->ios->ssh->interface != 0)
	{
		output_table(nipper, true, settings_sshint_table, &settings_sshint_heading);
		fprintf(nipper->reportFile, "<table><caption>Table %d: %s.</caption><thead>\n<tr><th>Network Interface</th></tr></thead><tbody>\n", nipper->tableNum, settings_sshint_table);
		interfacePointer = nipper->ios->ssh->interface;
		while (interfacePointer != 0)
		{
			outputFriendly(interfacePointer->interface, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_end);
			interfacePointer = interfacePointer->next;
		}
		output_table(nipper, false, settings_sshint_table, &settings_sshint_heading);
	}
}


void iosSSHProtocolIssue(struct nipperConfig *nipper)
{
	output_parseText(report_sshproto_obs, nipper, section_obs, rate_none, nipper->sshIssue, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_sshproto_impact, nipper, section_imp, rate_med, nipper->sshIssue, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_sshproto_ease, nipper, section_ease, rate_difficult, nipper->sshIssue, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_sshproto_rec2, nipper, section_rec, rate_none, nipper->sshIssue, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


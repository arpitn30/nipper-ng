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

void nmpGeneralConfig(struct nipperConfig *nipper)
{
	output_table(nipper, true, settings_general_table, &settings_general_heading);
	fprintf(nipper->reportFile, "%sHostname%s%s %s", nipper->tablerow_start, nipper->tablerow_mid, nipper->friendlyHostname, nipper->tablerow_end);
	if (nipper->version[0] != 0)
		fprintf(nipper->reportFile, "%sNMP Version%s%s %s", nipper->tablerow_start, nipper->tablerow_mid, nipper->version, nipper->tablerow_end);
	if (nipper->nmp->location[0] != 0)
		fprintf(nipper->reportFile, "%sLocation%s%s %s", nipper->tablerow_start, nipper->tablerow_mid, nipper->nmp->location, nipper->tablerow_end);
	if (nipper->nmp->contact[0] != 0)
		fprintf(nipper->reportFile, "%sContact%s%s %s", nipper->tablerow_start, nipper->tablerow_mid, nipper->nmp->contact, nipper->tablerow_end);
	if (nipper->nmp->coreFile[0] != 0)
		fprintf(nipper->reportFile, "%sCore File%s%s %s", nipper->tablerow_start, nipper->tablerow_mid, nipper->nmp->coreFile, nipper->tablerow_end);
	if (nipper->nmp->syslogFile[0] != 0)
		fprintf(nipper->reportFile, "%sSyslog File%s%s %s", nipper->tablerow_start, nipper->tablerow_mid, nipper->nmp->syslogFile, nipper->tablerow_end);
	if (nipper->nmp->timeout == 0)
		fprintf(nipper->reportFile, "%sIdle Session Timeout%sNone%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
	{
		fprintf(nipper->reportFile, "%sIdle Session Timeout%s", nipper->tablerow_start, nipper->tablerow_mid);
		numToWord(nipper->reportFile, nipper->nmp->timeout);
		fprintf(nipper->reportFile, " minutes%s", nipper->tablerow_end);
	}
	if (nipper->nmp->portSecurityAuto == true)
		fprintf(nipper->reportFile, "%sPort Security Auto Configure%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sPort Security Auto Configure%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	output_table(nipper, false, settings_general_table, &settings_general_heading);
	addAbbreviation("NMP", false);
	addAbbreviation("CDP", false);
}


void nmpSwitchConfig(struct nipperConfig *nipper)
{
	output_table(nipper, true, settings_switch_table, &settings_general_heading);
	if (nipper->nmp->switchConfig->ipRedirect == true)
		fprintf(nipper->reportFile, "%sICMP Redirects%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sICMP Redirects%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->nmp->switchConfig->ipUnreachable == true)
		fprintf(nipper->reportFile, "%sICMP Unreachables%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sICMP Unreachables%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->nmp->switchConfig->ipFragmentation == true)
		fprintf(nipper->reportFile, "%sIP Fragmentation%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sIP Fragmentation%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	output_table(nipper, false, settings_switch_table, &settings_general_heading);
	addAbbreviation("IP", false);
	addAbbreviation("ICMP", false);
}


void nmpCDPIssue(struct nipperConfig *nipper)
{
	output_parseText(report_cdp_obs, nipper, section_none, rate_none, -1, 0);
	output_endsection(nipper, section_obs);
	output_parseText(report_cdp_impact, nipper, section_imp, rate_low, 0, 0);
	output_endsection(nipper, section_imp);
	output_parseText(report_cdp_ease, nipper, section_ease, rate_trivial, 0, 0);
	output_endsection(nipper, section_ease);
	output_parseText(report_cdp_rec2, nipper, section_rec, rate_none, 0, 0);
	output_endsection(nipper, section_rec);
}


void nmpTimeoutIssue(struct nipperConfig *nipper)
{
	output_parseText(report_timeout_obs1, nipper, section_obs, rate_none, nipper->insecureTimeouts, nipper->tableNum);
	if ((nipper->connectionTimeout % 60) == 0)
	{
		numToWord(nipper->reportFile, (nipper->connectionTimeout / 60));
		fprintf(nipper->reportFile, " minutes");
	}
	else
	{
		numToWord(nipper->reportFile, nipper->connectionTimeout / 60);
		fprintf(nipper->reportFile, " minutes and ");
		numToWord(nipper->reportFile, nipper->connectionTimeout % 60);
		fprintf(nipper->reportFile, " seconds");
	}
	output_parseText(report_timeout_obs2, nipper, section_none, rate_none, nipper->insecureTimeouts, nipper->tableNum);
	if (nipper->insecureTimeouts > 1)
	{
		output_table(nipper, true, report_timeout_table, &report_timeout_heading);
		if (nipper->nmp->timeout * 60 > nipper->connectionTimeout)
		{
			fprintf(nipper->reportFile, "%sSession Timeout%s", nipper->tablerow_start, nipper->tablerow_mid);
			numToWord(nipper->reportFile, nipper->nmp->timeout);
			if (nipper->nmp->timeout > 1)
				fprintf(nipper->reportFile, " minutes%s", nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, " minute%s", nipper->tablerow_end);
		}
		output_table(nipper, false, report_timeout_table, &report_timeout_heading);
	}
	else
	{
		if (nipper->nmp->timeout * 60 > nipper->connectionTimeout)
		{
			fprintf(nipper->reportFile, "The session timeout was ");
			numToWord(nipper->reportFile, nipper->nmp->timeout);
			if (nipper->nmp->timeout > 1)
				fprintf(nipper->reportFile, " minutes.");
			else
				fprintf(nipper->reportFile, " minute.");
		}
		output_newPara(nipper);
	}
	output_endsection(nipper, section_obs);
	output_parseText(report_timeout_impact, nipper, section_imp, rate_high, 0, 0);
	output_endsection(nipper, section_imp);
	output_parseText(report_timeout_ease, nipper, section_ease, rate_difficult, 0, 0);
	output_endsection(nipper, section_ease);
	output_parseText(report_timeout_rec1, nipper, section_rec, rate_none, 0, 0);
	if ((nipper->connectionTimeout % 60) == 0)
	{
		numToWord(nipper->reportFile, (nipper->connectionTimeout / 60));
		fprintf(nipper->reportFile, " minutes");
	}
	else
	{
		numToWord(nipper->reportFile, nipper->connectionTimeout / 60);
		fprintf(nipper->reportFile, " minutes and ");
		numToWord(nipper->reportFile, (nipper->connectionTimeout % 60));
		fprintf(nipper->reportFile, " seconds");
	}
	output_parseText(report_timeout_rec2, nipper, section_none, rate_none, 0, 0);
	output_endsection(nipper, section_rec);
}

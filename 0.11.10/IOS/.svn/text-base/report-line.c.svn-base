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

void iosLinesConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct lineConfig *linePointer = 0;

	output_parseText(settings_lines_text, nipper, section_none, rate_none, 0, 0);
	output_table(nipper, true, settings_lines_table, &settings_lines_heading);
	linePointer = nipper->ios->line;
	while (linePointer != 0)
	{
		switch (linePointer->lineType)
		{
			case line_console:
				fprintf(nipper->reportFile, "%sConsole%s", nipper->tablerow_start, nipper->tablerow_mid);
				break;
			case line_aux:
				fprintf(nipper->reportFile, "%sAuxiliary%s", nipper->tablerow_start, nipper->tablerow_mid);
				break;
			case line_vty:
				fprintf(nipper->reportFile, "%sVTY%s", nipper->tablerow_start, nipper->tablerow_mid);
				addAbbreviation("VTY", false);
				break;
			case line_tty:
				fprintf(nipper->reportFile, "%sTTY%s", nipper->tablerow_start, nipper->tablerow_mid);
				addAbbreviation("TTY", false);
				break;
		}
		fprintf(nipper->reportFile, "%d%s", linePointer->lineNumberStart, nipper->tablerow_mid);
		if (linePointer->lineNumberEnd == 0)
			fprintf(nipper->reportFile, " %s", nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "%d%s", linePointer->lineNumberEnd, nipper->tablerow_mid);
		switch (linePointer->login)
		{
			case login_allowed:
				fprintf(nipper->reportFile, "Allowed%s", nipper->tablerow_mid);
				break;
			case login_disabled:
				fprintf(nipper->reportFile, "Denied%s", nipper->tablerow_mid);
				break;
			case login_local:
				fprintf(nipper->reportFile, "Local%s", nipper->tablerow_mid);
				break;
			case login_authentication:
				fprintf(nipper->reportFile, "AAA%s", nipper->tablerow_mid);
				break;
		}
		switch (linePointer->exec)
		{
			case true:
				fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
				break;
			case false:
				fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
				break;
		}
		switch (linePointer->authorization)
		{
			case true:
				fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
				break;
			case false:
				fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
				break;
		}
		switch (linePointer->accounting)
		{
			case true:
				fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
				break;
			case false:
				fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
				break;
		}
		switch (linePointer->telnet)
		{
			case true:
				fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
				break;
			case false:
				fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
				break;
		}
		switch (linePointer->ssh)
		{
			case true:
				fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
				break;
			case false:
				fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
				break;
		}
		fprintf(nipper->reportFile, "%ds%s%ds%s%ds%s%ds%s", linePointer->timeout, nipper->tablerow_mid, linePointer->execTimeout, nipper->tablerow_mid, linePointer->sessionTimeout, nipper->tablerow_mid, linePointer->absoluteTimeout, nipper->tablerow_mid);
		if (nipper->passwords == true)
			fprintf(nipper->reportFile, "%s%s", linePointer->password, nipper->tablerow_mid);
		if (linePointer->encryption == encrypt_type7)
			fprintf(nipper->reportFile, "Type-7%s", nipper->tablerow_end);
		else if (linePointer->encryption == encrypt_md5)
		{
			fprintf(nipper->reportFile, "MD5%s", nipper->tablerow_end);
			addAbbreviation("MD5", false);
		}
		else if (linePointer->encryption == encrypt_unknown)
			fprintf(nipper->reportFile, "Unknown%s", nipper->tablerow_end);
		else
		{
			if (linePointer->password[0] == 0)
				fprintf(nipper->reportFile, " %s", nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "None%s", nipper->tablerow_end);
		}
		linePointer = linePointer->next;
	}
	output_table(nipper, false, settings_lines_table, &settings_lines_heading);
}


void iosAUXPortIssue(struct nipperConfig *nipper)
{
	output_parseText(report_aux_obs, nipper, section_obs, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_aux_impact, nipper, section_imp, rate_high, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_aux_ease, nipper, section_ease, rate_difficult, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_aux_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosTelnetIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct lineConfig *linePointer = 0;
	int tempInt = 0;

	output_parseText(report_telnet_obs, nipper, section_obs, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_telnet_impact, nipper, section_imp, rate_med, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_telnet_ease, nipper, section_ease, rate_trivial, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_telnet_rec1, nipper, section_rec, rate_none, 0, nipper->tableNum);
	tempInt = 0;
	linePointer = nipper->ios->line;
	while (linePointer != 0)
	{
		if ((linePointer->telnet == true) && (linePointer->exec == true) && (linePointer->login != login_disabled) && (linePointer->aclIn == 0))
			tempInt++;
		linePointer = linePointer->next;
	}
	if (tempInt > 0)
		output_parseText(report_telnet_rec2, nipper, section_none, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}



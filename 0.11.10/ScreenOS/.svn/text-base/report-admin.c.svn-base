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

// This file contains code for ScreenOS Admin reporting


void sosAdminConfig(struct nipperConfig *nipper)
{
	// Variables...
	char tempString[nipper->maxSize];
	struct adminUsersSOS *userSOSPointer = 0;

	output_table(nipper, true, settings_admin_table, &settings_general_heading);
	if (nipper->sos->name[0] != 0)
	{
		outputFriendly(nipper->sos->name, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%sAdministrative User%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
	}
	if ((nipper->sos->password[0] != 0) && (nipper->passwords == true))
	{
		outputFriendly(nipper->sos->password, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%sEncrypted Administrative Password%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
	}
	if (nipper->sos->restrictLength == 0)
		fprintf(nipper->reportFile, "%sAdmin Password Length%sAny Length (upto 31 characters)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sAdmin Password Length%s%d%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->sos->restrictLength, nipper->tablerow_end);
	fprintf(nipper->reportFile, "%sAdmin Login Attempts%s%d%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->sos->accessAttempts, nipper->tablerow_end);
	if (nipper->sos->privilege == adminpriv_default)
		fprintf(nipper->reportFile, "%sAdmin Privilages%sDefault%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else if (nipper->sos->privilege == adminpriv_rw)
		fprintf(nipper->reportFile, "%sAdmin Privilages%sRead / Write%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else if (nipper->sos->privilege == adminpriv_ext)
		fprintf(nipper->reportFile, "%sAdmin Privilages%sGet Externally%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (strcmp(nipper->sos->adminIP, "0.0.0.0") == 0)
		fprintf(nipper->reportFile, "%sAdmin Management IP%sAny%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sAdmin Management IP%s%s %s%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->sos->adminIP, nipper->sos->adminNetMask, nipper->tablerow_end);
	addAbbreviation("IP", false);
	if (nipper->sos->consoleOnly == true)
		fprintf(nipper->reportFile, "%sConsole Only Administration%sYes%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sConsole Only Administration%sNo%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->sos->authenticationServer[0] != 0)
		fprintf(nipper->reportFile, "%sAuthentication Server%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->sos->authenticationServer, nipper->tablerow_end);
	if (nipper->sos->authTimeout == 0)
		fprintf(nipper->reportFile, "%sAdministration Timeout%sNone%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sAdministration Timeout%s%d mins%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->sos->authTimeout, nipper->tablerow_end);
	if (nipper->sos->httpRedirect == true)
		fprintf(nipper->reportFile, "%sHTTP Redirection%sYes%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else if (nipper->sos->httpRedirect == false)
		fprintf(nipper->reportFile, "%sHTTP Redirection%sNo%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sHTTP Redirection%sUnconfigured%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	addAbbreviation("HTTP", false);
	if (nipper->sos->mailAlert == true)
		fprintf(nipper->reportFile, "%sMail Alerts%sYes%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sMail Alerts%sNo%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->sos->email[0] != 0)
		fprintf(nipper->reportFile, "%sMail Alerts Address%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->sos->email, nipper->tablerow_end);
	if (nipper->sos->email1[0] != 0)
		fprintf(nipper->reportFile, "%sMail Alerts Address%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->sos->email1, nipper->tablerow_end);
	if (nipper->sos->email2[0] != 0)
		fprintf(nipper->reportFile, "%sMail Alerts Address%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->sos->email2, nipper->tablerow_end);
	if (nipper->sos->emailServer[0] != 0)
		fprintf(nipper->reportFile, "%sMail Server%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->sos->emailServer, nipper->tablerow_end);
	if (nipper->sos->adminFormat == adminfmt_default)
		fprintf(nipper->reportFile, "%sConfiguration Format%sDefault%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else if (nipper->sos->adminFormat == adminfmt_dos)
	{
		addAbbreviation("DOS", false);
		fprintf(nipper->reportFile, "%sConfiguration Format%sDOS%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	}
	else if (nipper->sos->adminFormat == adminfmt_unix)
		fprintf(nipper->reportFile, "%sConfiguration Format%sUnix%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);

	output_table(nipper, false, settings_admin_table, &settings_general_heading);

	if (nipper->sos->users != 0)
	{
		output_table(nipper, true, settings_admins_table, &settings_admins_heading);
		userSOSPointer = nipper->sos->users;
		while (userSOSPointer != 0)
		{
			outputFriendly(userSOSPointer->username, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
			if (nipper->passwords == true)
				fprintf(nipper->reportFile, "%s%s", userSOSPointer->password, nipper->tablerow_mid);
			switch (userSOSPointer->privilege)
			{
				case adminpriv_default:
					fprintf(nipper->reportFile, "Default%s", nipper->tablerow_mid);
					break;
				case adminpriv_all:
					fprintf(nipper->reportFile, "All%s", nipper->tablerow_mid);
					break;
				case adminpriv_read:
					fprintf(nipper->reportFile, "Read Only%s", nipper->tablerow_mid);
					break;
			}
			if (userSOSPointer->trustee == trustee_none)
				fprintf(nipper->reportFile, "None%s", nipper->tablerow_end);
			else if (userSOSPointer->trustee == trustee_modem)
				fprintf(nipper->reportFile, "Modem%s", nipper->tablerow_end);
			else if (userSOSPointer->trustee == trustee_inter)
				fprintf(nipper->reportFile, "Interface%s", nipper->tablerow_end);
			userSOSPointer = userSOSPointer->next;
		}
		output_table(nipper, false, settings_admins_table, &settings_admins_heading);
	}
}


void sosHTTPRedirectIssue(struct nipperConfig *nipper)
{
	output_parseText(report_httpred_obs, nipper, section_obs, rate_none, 0, 0);
	output_endsection(nipper, section_obs);
	output_parseText(report_httpred_impact, nipper, section_imp, rate_med, 0, 0);
	output_endsection(nipper, section_imp);
	output_parseText(report_httpred_ease, nipper, section_ease, rate_trivial, 0, 0);
	output_endsection(nipper, section_ease);
	output_parseText(report_httpred_rec, nipper, section_rec, rate_none, 0, 0);
	output_endsection(nipper, section_rec);
}


void sosManagementRIPIssue(struct nipperConfig *nipper)
{
	output_parseText(report_mngrip_obs, nipper, section_obs, rate_none, 0, 0);
	output_endsection(nipper, section_obs);
	output_parseText(report_mngrip_impact, nipper, section_imp, rate_med, 0, 0);
	output_endsection(nipper, section_imp);
	output_parseText(report_mngrip_ease, nipper, section_ease, rate_noease, 0, 0);
	output_endsection(nipper, section_ease);
	output_parseText(report_mngrip_rec, nipper, section_rec, rate_none, 0, 0);
	output_endsection(nipper, section_rec);
}


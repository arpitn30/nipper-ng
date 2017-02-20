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


void pixSSHConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct sshAccessConfig *sshPointer = 0;

	output_table(nipper, true, settings_ssh_table, &settings_general_heading);
	if (nipper->pix->ssh->version == 0)
		fprintf(nipper->reportFile, "%sProtocol Version%s1 and 2%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sProtocol Version%s%d%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->pix->ssh->version, nipper->tablerow_end);
	fprintf(nipper->reportFile, "%sSession Timeout%s", nipper->tablerow_start, nipper->tablerow_mid);
	numToWord(nipper->reportFile, nipper->pix->ssh->timeout);
	fprintf(nipper->reportFile, " minutes%s", nipper->tablerow_end);
	output_table(nipper, false, settings_ssh_table, &settings_general_heading);

	sshPointer = nipper->pix->ssh->access;
	if (sshPointer != 0)
	{
		output_table(nipper, true, settings_sshman_table, &settings_sshman_heading);
		while (sshPointer != 0)
		{
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, sshPointer->ipAddress, nipper->tablerow_mid);
			fprintf(nipper->reportFile, "%s%s", sshPointer->netMask, nipper->tablerow_mid);
			fprintf(nipper->reportFile, "%s%s", sshPointer->interface, nipper->tablerow_end);
			sshPointer = sshPointer->next;
		}
		output_table(nipper, false, settings_sshman_table, &settings_sshman_heading);
	}
	addAbbreviation("SSH", false);
}


void pixSSHIssue(struct nipperConfig *nipper)
{
	// Variables...
	int tempInt = 0;

	if ((nipper->versionMajor < 7) || ((nipper->versionMajor == 7) && (nipper->versionMinor == 0) && (nipper->versionRevision == 0)))
		tempInt = -1;
	else
		tempInt = 0;
	output_parseText(report_sshproto_obs, nipper, section_obs, rate_none, tempInt, 0);
	output_endsection(nipper, section_obs);
	output_parseText(report_sshproto_impact, nipper, section_imp, rate_med, tempInt, 0);
	output_endsection(nipper, section_imp);
	output_parseText(report_sshproto_ease, nipper, section_ease, rate_difficult, tempInt, 0);
	output_endsection(nipper, section_ease);
	output_parseText(report_sshproto_rec1, nipper, section_rec, rate_none, tempInt, 0);
	output_endsection(nipper, section_rec);
}


void sshManIssue(struct nipperConfig *nipper)
{
	output_parseText(report_sshman_obs, nipper, section_obs, rate_none, 0, 0);
	output_endsection(nipper, section_obs);
	output_parseText(report_sshman_impact, nipper, section_imp, rate_med, 0, 0);
	output_endsection(nipper, section_imp);
	output_parseText(report_sshman_ease, nipper, section_ease, rate_noease, 0, 0);
	output_endsection(nipper, section_ease);
	output_parseText(report_sshman_rec, nipper, section_rec, rate_none, 0, 0);
	output_endsection(nipper, section_rec);
}


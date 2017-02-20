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

// This file contains code for ScreenOS Timeout reporting


void sosTimeoutIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct authServerSOS *authServerPointer = 0;

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
		if ((nipper->sos->authTimeout * 60) > nipper->connectionTimeout)
		{
			fprintf(nipper->reportFile, "%sWeb Administration%s", nipper->tablerow_start, nipper->tablerow_mid);
			numToWord(nipper->reportFile, nipper->sos->authTimeout);
			fprintf(nipper->reportFile, " minutes%s", nipper->tablerow_end);
		}
		authServerPointer = nipper->sos->authServer;
		while (authServerPointer != 0)
		{
			if ((authServerPointer->timeout * 60 ) > nipper->connectionTimeout)
			{
				switch (authServerPointer->type)
				{
					case authtype_builtin:
						fprintf(nipper->reportFile, "%sBuiltin Authentication%s", nipper->tablerow_start, nipper->tablerow_mid);
						break;
					case authtype_radius:
						fprintf(nipper->reportFile, "%sRADIUS Authentication%s", nipper->tablerow_start, nipper->tablerow_mid);
						break;
					case authtype_ldap:
						fprintf(nipper->reportFile, "%sLDAP Authentication%s", nipper->tablerow_start, nipper->tablerow_mid);
						break;
					case authtype_securid:
						fprintf(nipper->reportFile, "%sSecurId Authentication%s", nipper->tablerow_start, nipper->tablerow_mid);
						break;
				}
				numToWord(nipper->reportFile, authServerPointer->timeout);
				fprintf(nipper->reportFile, " minutes%s", nipper->tablerow_end);
			}
			authServerPointer = authServerPointer->next;
		}
		output_table(nipper, false, report_timeout_table, &report_timeout_heading);
	}
	else
	{
		if ((nipper->sos->authTimeout * 60) > nipper->connectionTimeout)
		{
			fprintf(nipper->reportFile, "Web Administration had a timeout of ");
			numToWord(nipper->reportFile, nipper->sos->authTimeout);
			fprintf(nipper->reportFile, " minutes.");
		}
		authServerPointer = nipper->sos->authServer;
		while (authServerPointer != 0)
		{
			if ((authServerPointer->timeout * 60 ) > nipper->connectionTimeout)
			{
				switch (authServerPointer->type)
				{
					case authtype_builtin:
						fprintf(nipper->reportFile, "Builtin Authentication had a timeout of ");
						break;
					case authtype_radius:
						fprintf(nipper->reportFile, "RADIUS Authentication had a timeout of ");
						break;
					case authtype_ldap:
						fprintf(nipper->reportFile, "LDAP Authentication had a timeout of ");
						break;
					case authtype_securid:
						fprintf(nipper->reportFile, "SecurId Authentication had a timeout of ");
						break;
				}
				numToWord(nipper->reportFile, authServerPointer->timeout);
				fprintf(nipper->reportFile, " minutes.");
			}
			authServerPointer = authServerPointer->next;
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


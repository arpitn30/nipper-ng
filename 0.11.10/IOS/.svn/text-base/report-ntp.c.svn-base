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

void iosNTPConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct ntpHost *ntpHostPointer = 0;
	struct ntpKey *ntpKeyPointer = 0;
	struct ntpAccessGroup *ntpGroupPointer = 0;
	char tempString[nipper->maxSize];

	output_table(nipper, true, settings_ntp_table, &settings_general_heading);
	if (nipper->ios->ntp->enabled == true)
		fprintf(nipper->reportFile, "%sNTP Server%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sNTP Server%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->ios->ntp->master == true)
		fprintf(nipper->reportFile, "%sNTP Master%sYes%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sNTP Master%sNo%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->ios->ntp->authentication == true)
		fprintf(nipper->reportFile, "%sNTP Authentication%sYes%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sNTP Authentication%sNo%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	output_table(nipper, false, settings_ntp_table, &settings_general_heading);
	addAbbreviation("NTP", false);

	if (nipper->ios->ntp->server != 0)
	{
		output_table(nipper, true, settings_ntpserv_table, &settings_ntpserv_heading);
		ntpHostPointer = nipper->ios->ntp->server;
		while (ntpHostPointer != 0)
		{
			outputFriendly(ntpHostPointer->ntpHost, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
			if (ntpHostPointer->keyNum == -1)
				fprintf(nipper->reportFile, "None%s", nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "%d%s", ntpHostPointer->keyNum, nipper->tablerow_end);
			ntpHostPointer = ntpHostPointer->next;
		}
		output_table(nipper, false, settings_ntpserv_table, &settings_ntpserv_heading);
	}

	if (nipper->ios->ntp->peer != 0)
	{
		output_table(nipper, true, settings_ntppeer_table, &settings_ntppeer_heading);
		ntpHostPointer = nipper->ios->ntp->peer;
		while (ntpHostPointer != 0)
		{
			outputFriendly(ntpHostPointer->ntpHost, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s%d%s", nipper->tablerow_start, tempString, nipper->tablerow_mid, ntpHostPointer->keyNum, nipper->tablerow_end);
			ntpHostPointer = ntpHostPointer->next;
		}
		output_table(nipper, false, settings_ntppeer_table, &settings_ntppeer_heading);
	}

	if ((nipper->ios->ntp->key != 0) && (nipper->passwords == true))
	{
		output_table(nipper, true, settings_ntpkeys_table, &settings_ntpkeys_heading);
		ntpKeyPointer = nipper->ios->ntp->key;
		while (ntpKeyPointer != 0)
		{
			fprintf(nipper->reportFile, "%s%d%s", nipper->tablerow_start, ntpKeyPointer->keyNum, nipper->tablerow_mid);
			if (ntpKeyPointer->trusted == false)
				fprintf(nipper->reportFile, "No");
			else
				fprintf(nipper->reportFile, "Yes");
			if (nipper->passwords == true)
			{
				outputFriendly(ntpKeyPointer->key, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, tempString);
			}
			fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
			ntpKeyPointer = ntpKeyPointer->next;
		}
		output_table(nipper, false, settings_ntpkeys_table, &settings_ntpkeys_heading);
	}

	if (nipper->ios->ntp->access != 0)
	{
		output_table(nipper, true, settings_ntpaccess_table, &settings_ntpaccess_heading);
		ntpGroupPointer = nipper->ios->ntp->access;
		while (ntpGroupPointer != 0)
		{
			switch (ntpGroupPointer->accessType)
			{
				case ntp_peer:
					fprintf(nipper->reportFile, "%sPeer%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, ntpGroupPointer->accessList, nipper->tablerow_end);
					break;
				case ntp_serve:
					fprintf(nipper->reportFile, "%sServe%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, ntpGroupPointer->accessList, nipper->tablerow_end);
					break;
				case ntp_serve_only:
					fprintf(nipper->reportFile, "%sServe-Only%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, ntpGroupPointer->accessList, nipper->tablerow_end);
					break;
				case ntp_query_only:
					fprintf(nipper->reportFile, "%sQuery-Only%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, ntpGroupPointer->accessList, nipper->tablerow_end);
					break;
			}
			ntpGroupPointer = ntpGroupPointer->next;
		}
		output_table(nipper, false, settings_ntpaccess_table, &settings_ntpaccess_heading);
	}
}


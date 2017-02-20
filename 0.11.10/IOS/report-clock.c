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

void iosTimeZoneConfig(struct nipperConfig *nipper)
{
	output_table(nipper, true, settings_timezone_table, &settings_general_heading);
	fprintf(nipper->reportFile, "%sTime Zone%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->ios->timeZone, nipper->tablerow_end);
	if ((nipper->ios->timeOffsetHours != 0) || (nipper->ios->timeOffsetMins != 0))
	{
		fprintf(nipper->reportFile, "%sUTC Offset%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (nipper->ios->timeOffsetHours != 0)
		{
			if (nipper->ios->timeOffsetHours > 0)
				fprintf(nipper->reportFile, "+");
			fprintf(nipper->reportFile, "%d hour", nipper->ios->timeOffsetHours);
			if ((nipper->ios->timeOffsetHours > 1) || (nipper->ios->timeOffsetHours < -1))
				fprintf(nipper->reportFile, "s");
			if (nipper->ios->timeOffsetMins != 0)
				fprintf(nipper->reportFile, " ");
		}
		if (nipper->ios->timeOffsetMins != 0)
		{
			fprintf(nipper->reportFile, "%d min", nipper->ios->timeOffsetMins);
			if ((nipper->ios->timeOffsetMins > 1) || (nipper->ios->timeOffsetMins < -1))
				fprintf(nipper->reportFile, "s");
		}
		fprintf(nipper->reportFile,"%s", nipper->tablerow_end);
	}
	else
		fprintf(nipper->reportFile, "%sUTC Offset%sNone%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->ios->summerTimeZone[0] != 0)
		fprintf(nipper->reportFile, "%sSummer Time Zone%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->ios->timeZone, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sSummer Time Zone%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->ios->calendarValid == true)
		fprintf(nipper->reportFile, "%sAuthorative Time Source%sYes%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sAuthorative Time Source%sNo%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	output_table(nipper, false, settings_timezone_table, &settings_general_heading);
}


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

void iosVTPConfig(struct nipperConfig *nipper)
{
	// Variables...
	char tempString[nipper->maxSize];

	output_table(nipper, true, settings_vtp_table, &settings_general_heading);
	switch (nipper->ios->vtpMode)
	{
		case vtp_mode_server:
			fprintf(nipper->reportFile, "%sVTP Mode%sServer%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
		case vtp_mode_client:
			fprintf(nipper->reportFile, "%sVTP Mode%sClient%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
		case vtp_mode_transparent:
			fprintf(nipper->reportFile, "%sVTP Mode%sTransparent%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
		case vtp_mode_none:
			fprintf(nipper->reportFile, "%sVTP Mode%sNone%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
	}
	if (nipper->ios->vtpDomain[0] != 0)
	{
		outputFriendly(nipper->ios->vtpDomain, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%sVTP Domain%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
	}
	output_table(nipper, false, settings_vtp_table, &settings_general_heading);
	addAbbreviation("VTP", false);
}


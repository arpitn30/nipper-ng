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

void iosTACACSConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct host *hostPointer = 0;
	char tempString[nipper->maxSize];

	output_table(nipper, true, settings_tacacs_table, &settings_general_heading);
	if (nipper->passwords == true)
	{
		outputFriendly(nipper->ios->tacacs->key, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%sTACACS Key%s%s %s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
	}
	switch(nipper->ios->tacacs->encryption)
	{
		case encrypt_type7:
			fprintf(nipper->reportFile, "%sKey Encryption Type%sType-7%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
		case encrypt_md5:
			fprintf(nipper->reportFile, "%sKey Encryption Type%sMD5%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			addAbbreviation("MD5", false);
			break;
		case encrypt_none:
			fprintf(nipper->reportFile, "%sKey Encryption Type%sNone%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
		case encrypt_unknown:
			fprintf(nipper->reportFile, "%sKey Encryption Type%sUnknown%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
	}
	output_table(nipper, false, settings_tacacs_table, &settings_general_heading);
	addAbbreviation("TACACS", false);

	if (nipper->ios->tacacs->host != 0)
	{
		output_table(nipper, true, settings_tacacsserv_table, &settings_tacacsserv_heading);
		hostPointer = nipper->ios->tacacs->host;
		while (hostPointer != 0)
		{
			outputFriendly(hostPointer->server, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_end);
			hostPointer = hostPointer->next;
		}
		output_table(nipper, false, settings_tacacsserv_table, &settings_tacacsserv_heading);
	}
}

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

void iosAAAConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct aaaGroupServer *aaaGroupPointer = 0;
	struct aaaServer *aaaServerPointer = 0;
	char tempString[nipper->maxSize];
	char tempString2[nipper->maxSize];

	aaaGroupPointer = nipper->ios->aaa->groupServer;
	while (aaaGroupPointer != 0)
	{
		switch (aaaGroupPointer->type)
		{
			case aaa_radius:
				sprintf(tempString, "%s %s %s", settings_aaa_table1, aaaGroupPointer->username, settings_aaa_table2);
				addAbbreviation("RADIUS", false);
				break;
			case aaa_tacacs:
				sprintf(tempString, "%s %s %s", settings_aaa_table1, aaaGroupPointer->username, settings_aaa_table3);
				addAbbreviation("TACACS", false);
				break;
			case aaa_kerberos:
				sprintf(tempString, "%s %s %s", settings_aaa_table1, aaaGroupPointer->username, settings_aaa_table4);
				break;
		}
		outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
		output_table(nipper, true, tempString2, &settings_aaa_heading);
		aaaServerPointer = aaaGroupPointer->server;
		while (aaaServerPointer != 0)
		{
			outputFriendly(aaaServerPointer->server, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s%d%s%d%s", nipper->tablerow_start, tempString, nipper->tablerow_mid, aaaServerPointer->authPort, nipper->tablerow_mid, aaaServerPointer->acctPort, nipper->tablerow_mid);
			if (nipper->passwords == true)
			{
				outputFriendly(aaaServerPointer->key, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s %s", tempString, nipper->tablerow_mid);
			}
			switch(aaaServerPointer->encryption)
			{
				case encrypt_type7:
					fprintf(nipper->reportFile, "Type-7%s", nipper->tablerow_end);
					break;
				case encrypt_md5:
					fprintf(nipper->reportFile, "MD5%s", nipper->tablerow_end);
					addAbbreviation("MD5", false);
					break;
				case encrypt_none:
					fprintf(nipper->reportFile, "None%s", nipper->tablerow_end);
					break;
				case encrypt_unknown:
					fprintf(nipper->reportFile, "Unknown%s", nipper->tablerow_end);
					break;
			}
			aaaServerPointer = aaaServerPointer->next;
		}
		output_table(nipper, false, tempString2, &settings_aaa_heading);
		aaaGroupPointer = aaaGroupPointer->next;
	}
	addAbbreviation("AAA", false);
}

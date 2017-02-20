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

void iosUsersConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct enablePassword *enablePointer = 0;
	struct usernameList *usernamePointer = 0;
	struct privilageLevels *privilagePointer = 0;
	struct bannerConfig *bannerPointer = 0;
	char tempString[nipper->maxSize];

	// Enable Password
	if (nipper->ios->enable != 0)
	{
		output_table(nipper, true, settings_enable_table, &report_enable_heading);
		enablePointer = nipper->ios->enable;
		while (enablePointer != 0)
		{
			fprintf(nipper->reportFile, "%s%d%s", nipper->tablerow_start, enablePointer->level, nipper->tablerow_mid);
			if (nipper->passwords == true)
			{
				outputFriendly(enablePointer->password, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s %s", tempString, nipper->tablerow_mid);
			}
			switch (enablePointer->encryption)
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
			enablePointer = enablePointer->next;
		}
		output_table(nipper, false, settings_enable_table, &report_enable_heading);
	}

	// Usernames
	if (nipper->ios->username != 0)
	{
		output_table(nipper, true, settings_users_table, &report_users_heading);
		usernamePointer = nipper->ios->username;
		while (usernamePointer != 0)
		{
			outputFriendly(usernamePointer->username, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s%d%s", nipper->tablerow_start, tempString, nipper->tablerow_mid, usernamePointer->privilage, nipper->tablerow_mid);
			if (nipper->passwords == true)
			{
				outputFriendly(usernamePointer->password, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s %s", tempString, nipper->tablerow_mid);
			}
			switch (usernamePointer->encryption)
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
			usernamePointer = usernamePointer->next;
		}
		output_table(nipper, false, settings_users_table, &report_users_heading);
	}

	// Privilage
	if (nipper->ios->privilage != 0)
	{
		output_parseText(settings_privs_desc, nipper, section_none, rate_none, 0, 0);
		output_table(nipper, true, settings_privs_table, &report_privs_heading);
		privilagePointer = nipper->ios->privilage;
		while (privilagePointer != 0)
		{
			printf("%s%d%s%s%s", nipper->tablerow_start, privilagePointer->level, nipper->tablerow_mid, privilagePointer->command, nipper->tablerow_end);
			privilagePointer = privilagePointer->next;
		}
		output_table(nipper, false, settings_privs_table, &report_privs_heading);
	}

	// Banner
	if (nipper->ios->banner != 0)
	{
		output_parseText(settings_banner_desc, nipper, section_none, rate_none, 0, 0);
		bannerPointer = nipper->ios->banner;
		switch (nipper->outputFormat)
		{
			case output_html:
				fprintf(nipper->reportFile, "<quote>\n");
				break;
			case output_xml:
				fprintf(nipper->reportFile, "   <code>");
				break;
		}
		while (bannerPointer != 0)
		{
			fprintf(nipper->reportFile, "%s", bannerPointer->line);
			switch (nipper->outputFormat)
			{
				case output_html:
					fprintf(nipper->reportFile, "<br>\n");
					break;
				default:
					fprintf(nipper->reportFile, "\n");
					break;
			}
			bannerPointer = bannerPointer->next;
		}
		switch (nipper->outputFormat)
		{
			case output_html:
				fprintf(nipper->reportFile, "</quote>");
				break;
			case output_xml:
				fprintf(nipper->reportFile, "</code>\n");
				break;
		}
		output_newPara(nipper);
	}
}


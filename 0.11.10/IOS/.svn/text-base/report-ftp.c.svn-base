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

void iosFTPConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct netInterface *interfacePointer = 0;
	char tempString[nipper->maxSize];

	if (nipper->ios->ftp->username[0] != 0)
	{
		output_table(nipper, true, settings_ftp_table, &settings_general_heading);
		outputFriendly(nipper->ios->ftp->username, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%sFTP Username%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
		if (nipper->passwords == true)
		{
			outputFriendly(nipper->ios->ftp->password, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%sFTP Password%s%s %s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
		}
		switch(nipper->ios->ftp->encryption)
		{
			case encrypt_type7:
				fprintf(nipper->reportFile, "%sPassword Encryption Type%sType-7%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
			case encrypt_md5:
				fprintf(nipper->reportFile, "%sPassword Encryption Type%sMD5%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
			case encrypt_none:
				fprintf(nipper->reportFile, "%sPassword Encryption Type%sNone%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
			case encrypt_unknown:
				fprintf(nipper->reportFile, "%sPassword Encryption Type%sUnknown%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
		}
		output_table(nipper, false, settings_ftp_table, &settings_general_heading);
	}
	addAbbreviation("FTP", false);

	// Show FTP interfaces
	if (nipper->ios->ftp->interface != 0)
	{
		output_table(nipper, true, settings_ftpint_table, &settings_sshint_heading);
		interfacePointer = nipper->ios->ftp->interface;
		while (interfacePointer != 0)
		{
			outputFriendly(interfacePointer->interface, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_end);
			interfacePointer = interfacePointer->next;
		}
		output_table(nipper, false, settings_ftpint_table, &settings_sshint_heading);
	}
}

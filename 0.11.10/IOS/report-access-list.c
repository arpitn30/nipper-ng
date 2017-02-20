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


void iosACLConfig(struct nipperConfig *nipper)
{
	// Variables...
	int tempInt = 0;
	struct interfaceConfig *interfaceConfigPointer = 0;
	struct lineConfig *linePointer = 0;

	output_parseText(settings_accesslists1, nipper, section_none, rate_none, 0, 0);
	output_parseText(settings_accesslists2, nipper, section_none, rate_none, 0, 0);

	// Interfaces with ACL applied
	tempInt = 0;
	interfaceConfigPointer = nipper->ios->interface;
	while (interfaceConfigPointer != 0)
	{
		if ((interfaceConfigPointer->accessGroupIn[0] != 0) || (interfaceConfigPointer->accessGroupOut[0] != 0))
			tempInt++;
		interfaceConfigPointer = interfaceConfigPointer->next;
	}
	if (tempInt > 0)
	{
		output_table(nipper, true, settings_acl_int_table, &settings_aclinter_heading);
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->accessGroupIn[0] != 0) || (interfaceConfigPointer->accessGroupOut[0] != 0))
			{
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, interfaceConfigPointer->name, nipper->tablerow_mid);
				if (interfaceConfigPointer->shutdown == true)
					fprintf(nipper->reportFile, "No%s%s%s", nipper->tablerow_mid, interfaceConfigPointer->ipAddress, nipper->tablerow_mid);
				else
					fprintf(nipper->reportFile, "Yes%s%s%s", nipper->tablerow_mid, interfaceConfigPointer->ipAddress, nipper->tablerow_mid);
				if (interfaceConfigPointer->accessGroupIn[0] != 0)
					fprintf(nipper->reportFile, "%s%s", interfaceConfigPointer->accessGroupIn, nipper->tablerow_mid);
				else
					fprintf(nipper->reportFile, " %s", nipper->tablerow_mid);
				if (interfaceConfigPointer->accessGroupOut[0] != 0)
					fprintf(nipper->reportFile, "%s%s", interfaceConfigPointer->accessGroupOut, nipper->tablerow_end);
				else
					fprintf(nipper->reportFile, " %s", nipper->tablerow_end);
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		output_table(nipper, false, settings_acl_int_table, &settings_aclinter_heading);
	}

	// Lines with ACL applied
	tempInt = 0;
	linePointer = nipper->ios->line;
	while (linePointer != 0)
	{
		if ((linePointer->aclIn[0] != 0) || (linePointer->aclOut[0] != 0))
			tempInt++;
		linePointer = linePointer->next;
	}
	if (tempInt > 0)
	{
		output_table(nipper, true, settings_acl_line_table, &settings_aclline_heading);
		linePointer = nipper->ios->line;
		while (linePointer != 0)
		{
			if ((linePointer->aclIn[0] != 0) || (linePointer->aclOut[0] != 0))
			{
				switch (linePointer->lineType)
				{
					case line_console:
						fprintf(nipper->reportFile, "%sConsole%s", nipper->tablerow_start, nipper->tablerow_mid);
						break;
					case line_aux:
						fprintf(nipper->reportFile, "%sAuxiliary%s", nipper->tablerow_start, nipper->tablerow_mid);
						break;
					case line_vty:
						fprintf(nipper->reportFile, "%sVTY%s", nipper->tablerow_start, nipper->tablerow_mid);
						addAbbreviation("VTY", false);
						break;
					case line_tty:
						fprintf(nipper->reportFile, "%sTTY%s", nipper->tablerow_start, nipper->tablerow_mid);
						addAbbreviation("TTY", false);
						break;
				}
				fprintf(nipper->reportFile, "%d%s", linePointer->lineNumberStart, nipper->tablerow_mid);
				if (linePointer->lineNumberEnd == 0)
					fprintf(nipper->reportFile, " %s", nipper->tablerow_mid);
				else
					fprintf(nipper->reportFile, "%d%s", linePointer->lineNumberEnd, nipper->tablerow_mid);
				switch (linePointer->login)
				{
					case login_allowed:
						fprintf(nipper->reportFile, "Allowed%s", nipper->tablerow_mid);
						break;
					case login_disabled:
						fprintf(nipper->reportFile, "Denied%s", nipper->tablerow_mid);
						break;
					case login_local:
						fprintf(nipper->reportFile, "Local%s", nipper->tablerow_mid);
						break;
					case login_authentication:
						fprintf(nipper->reportFile, "AAA%s", nipper->tablerow_mid);
						break;
				}
				switch (linePointer->exec)
				{
					case true:
						fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
						break;
					case false:
						fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
						break;
				}
				switch (linePointer->telnet)
				{
					case true:
						fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
						break;
					case false:
						fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
						break;
				}
				switch (linePointer->ssh)
				{
					case true:
						fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
						break;
					case false:
						fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
						break;
				}
				if (linePointer->aclIn[0] != 0)
					fprintf(nipper->reportFile, "%s%s", linePointer->aclIn, nipper->tablerow_mid);
				else
					fprintf(nipper->reportFile, " %s", nipper->tablerow_mid);
				if (linePointer->aclOut[0] != 0)
					fprintf(nipper->reportFile, "%s%s", linePointer->aclOut, nipper->tablerow_end);
				else
					fprintf(nipper->reportFile, " %s", nipper->tablerow_end);
			}
			linePointer = linePointer->next;
		}
		output_table(nipper, false, settings_acl_line_table, &settings_aclline_heading);
	}

	// ACL
	reportRules(nipper);
}


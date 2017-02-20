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

// This file contains code for CSS General reporting


void cssGeneralConfig(struct nipperConfig *nipper)
{
	output_table(nipper, true, settings_general_table, &settings_general_heading);
	fprintf(nipper->reportFile, "%sHostname%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->friendlyHostname, nipper->tablerow_end);
	if (nipper->version[0] != 0)
		fprintf(nipper->reportFile, "%sCSS Version%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->version, nipper->tablerow_end);
	output_table(nipper, false, settings_general_table, &settings_general_heading);
	addAbbreviation("CSS", false);
}


void cssServicesConfig(struct nipperConfig *nipper)
{
	output_table(nipper, true, settings_services_table, &report_services_heading);
	if (nipper->css->ftpAccess == true)
		fprintf(nipper->reportFile, "%sFTP Server%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sFTP Server%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->css->snmpAccess == true)
		fprintf(nipper->reportFile, "%sSNMP Server%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sSNMP Server%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->css->sshAccess == true)
		fprintf(nipper->reportFile, "%sSSH Server%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sSSH Server%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->css->telnetAccess == true)
		fprintf(nipper->reportFile, "%sTelnet Server%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sTelnet Server%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->css->webManagementAccess == true)
		fprintf(nipper->reportFile, "%sWeb Management Server%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sWeb Management Server%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	output_table(nipper, false, settings_services_table, &report_services_heading);
	addAbbreviation("FTP", false);
	addAbbreviation("SNMP", false);
	addAbbreviation("SSH", false);
}


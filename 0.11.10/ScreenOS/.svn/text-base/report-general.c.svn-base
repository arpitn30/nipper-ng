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

// This file contains code for ScreenOS General reporting


void sosGeneralConfig(struct nipperConfig *nipper)
{
	output_table(nipper, true, settings_general_table, &settings_general_heading);
	fprintf(nipper->reportFile, "%sHostname%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->friendlyHostname, nipper->tablerow_end);
	fprintf(nipper->reportFile, "%sDefault Firewall Policy%s", nipper->tablerow_start, nipper->tablerow_mid);
	if (nipper->sos->defaultFirewallMode == true)
		fprintf(nipper->reportFile, "Deny%s", nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "Permit%s", nipper->tablerow_end);
	output_table(nipper, false, settings_general_table, &settings_general_heading);
}


void sosServicesConfig(struct nipperConfig *nipper)
{
	output_table(nipper, true, settings_services_table, &report_services_heading);
	if (nipper->sos->sshEnabled == true)
		fprintf(nipper->reportFile, "%sSSH%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sSSH%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	output_table(nipper, false, settings_services_table, &report_services_heading);
	addAbbreviation("SSH", false);
}

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

// This file contains code for ScreenOS SSH reporting


void sosSSHConfig(struct nipperConfig *nipper)
{
	output_table(nipper, true, settings_ssh_table, &settings_general_heading);
	fprintf(nipper->reportFile, "%sSSH Service%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	fprintf(nipper->reportFile, "%sSSH Protocol Version%s%d%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->sos->sshVersion, nipper->tablerow_end);
	fprintf(nipper->reportFile, "%sSSH V1 Key Generation Time%s%d mins%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->sos->sshKeyGenTime, nipper->tablerow_end);
	fprintf(nipper->reportFile, "%sSSH V2 Public Key%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->sos->sshPublicKey, nipper->tablerow_end);
	output_table(nipper, false, settings_ssh_table, &settings_general_heading);
}


void sosSSHProtocolIssue(struct nipperConfig *nipper)
{
	output_parseText(report_sshproto_obs, nipper, section_obs, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_sshproto_impact, nipper, section_imp, rate_med, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_sshproto_ease, nipper, section_ease, rate_difficult, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_sshproto_sos_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


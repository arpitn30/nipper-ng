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

// This file contains the code for NMP / CatOS reporting

// Report NMP includes...
#include "report-debug.c"
#include "report-general.c"
#include "report-passwords.c"
#include "report-permit.c"
#include "report-port.c"
#include "report-snmp.c"
#include "report-vlan.c"


void generateNMPReport(struct nipperConfig *nipper)
{
	// Security Issues section 
	if (nipper->fullReport == true)
	{
		// Simple Passwords
		if (nipper->simplePasswords > 1)
			addReportSection(nipper, section_security, report_dict_title1, report_dict_context, report_dict_rectext, 10, 8, 5, 3, nmpDictionaryIssue);
		else if (nipper->simplePasswords > 0)
			addReportSection(nipper, section_security, report_dict_title2, report_dict_context, report_dict_rectext, 10, 8, 5, 3, nmpDictionaryIssue);

		// Password Strength
		if (nipper->passwordStrengths > 1)
			addReportSection(nipper, section_security, report_strength_title1, report_strength_context, report_strength_rectext, 10, 8, 5, 3, nmpStrengthIssue);
		else if (nipper->passwordStrengths > 0)
			addReportSection(nipper, section_security, report_strength_title2, report_strength_context, report_strength_rectext, 10, 8, 5, 3, nmpStrengthIssue);

		// Timeout
		if (nipper->nmp->timeout * 60 > nipper->connectionTimeout)
			nipper->insecureTimeouts++;
		if (nipper->insecureTimeouts > 0)
			addReportSection(nipper, section_security, report_timeout_title, report_timeout_context, report_timeout_rectext, 10, 8, 5, 3, nmpTimeoutIssue);

		// IP Redirects
		if (nipper->nmp->switchConfig != 0)
		{
			if (nipper->nmp->switchConfig->ipRedirect == true)
				addReportSection(nipper, section_security, report_redirects_title, report_redirects_context, report_redirects_rectext, 10, 8, 5, 3, nmpRedirectsIssue);
		}

		// CDP
		if (nipper->nmp->cdp == true)
			addReportSection(nipper, section_security, report_cdp_title, report_cdp_context, report_cdp_rectext, 10, 8, 5, 3, nmpCDPIssue);

		// IP Unreachables
		if (nipper->nmp->switchConfig != 0)
		{
			if (nipper->nmp->switchConfig->ipUnreachable == true)
				addReportSection(nipper, section_security, report_icmpunreach_title, report_icmpunreach_context, report_icmpunreach_rectext, 10, 8, 5, 3, nmpUnreachablesIssue);
		}
	}


	// In Configuration Index
	addReportSection(nipper, section_config, settings_general_title, 0, 0, 0, 0, 0, 0, nmpGeneralConfig);
	if (nipper->nmp->switchConfig != 0)
		addReportSection(nipper, section_config, settings_switch_title, 0, 0, 0, 0, 0, 0, nmpSwitchConfig);
	if (nipper->nmp->permit != 0)
		addReportSection(nipper, section_config, settings_permit_title, 0, 0, 0, 0, 0, 0, nmpPermitConfig);
	if (((nipper->nmp->enablePassword != 0) || (nipper->nmp->password != 0)) && (nipper->passwords == true))
		addReportSection(nipper, section_config, settings_passwords_title, 0, 0, 0, 0, 0, 0, nmpPasswordsConfig);
	addReportSection(nipper, section_config, settings_cdp_title, 0, 0, 0, 0, 0, 0, nmpCDPConfig);
	if (nipper->nmp->snmp != 0)
		addReportSection(nipper, section_config, settings_snmp_title, 0, 0, 0, 0, 0, 0, nmpSNMPConfig);
	if (nipper->nmp->vlan != 0)
		addReportSection(nipper, section_config, settings_vlan_title, 0, 0, 0, 0, 0, 0, nmpVLANConfig);
	if (nipper->nmp->module != 0)
		addReportSection(nipper, section_config, settings_ports_title, 0, 0, 0, 0, 0, 0, nmpPortsConfig);

	// Generate Report...
	generateReport(nipper);
}


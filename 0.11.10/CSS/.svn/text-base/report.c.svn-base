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

// This file contains code for CSS reporting

// Report CSS includes...
#include "report-access-list.c"
#include "report-debug.c"
#include "report-general.c"
#include "report-restrict.c"
#include "report-snmp.c"


void generateCSSReport(struct nipperConfig *nipper)
{
	// Security Issues...
	if (nipper->fullReport == true)
	{
		// SNMP
		if (nipper->css->snmpAccess == true)
			addReportSection(nipper, section_security, report_snmp_title, report_snmp_context, report_snmp_css_rectext, 10, 8, 5, 3, cssSNMPIssue);

		// Telnet
		if (nipper->css->telnetAccess == true)
			addReportSection(nipper, section_security, report_telnet_title, report_telnet_context, report_telnet_rectext, 10, 8, 5, 3, cssTelnetIssue);

		// ACL
		if (nipper->filterList == 0)
			nipper->aclIssues = -1;
		else
			rulesAudit(nipper);
		if (nipper->aclIssues != 0)
			addReportSection(nipper, section_security, report_accesslist_title, report_accesslist_context, report_accesslist_rectext, 10, 8, 5, 3, cssACLIssue);

		// ACL Disabled
		if (nipper->css->aclEnabled == false)
			addReportSection(nipper, section_security, report_accesslist_noacl_title, report_accesslist_noacl_context, report_accesslist_noacl_rectext, 10, 8, 5, 3, cssACLDisabledIssue);
	}

	// In Configuration Index
	addReportSection(nipper, section_config, settings_general_title, 0, 0, 0, 0, 0, 0, cssGeneralConfig);
	addReportSection(nipper, section_config, settings_services_title, 0, 0, 0, 0, 0, 0, cssServicesConfig);
	if (nipper->css->snmp != 0)
		addReportSection(nipper, section_config, settings_snmp_title, 0, 0, 0, 0, 0, 0, cssSNMPConfig);
	addReportSection(nipper, section_config, settings_accesslists_title, 0, 0, 0, 0, 0, 0, cssACLConfig);

	// Generate Report...
	generateReport(nipper);
}



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

// This file contains ScreenOS reporting code...

// Report SOS includes...
#include "report-address.c"
#include "report-admin.c"
#include "report-auth-server.c"
#include "report-debug.c"
#include "report-general.c"
#include "report-interface.c"
#include "report-passwords.c"
#include "report-policy.c"
#include "report-snmp.c"
#include "report-ssh.c"
#include "report-timeout.c"
#include "report-zone.c"


void generateSOSReport(struct nipperConfig *nipper)
{
	// Variables
	struct authServerSOS *authServerPointer = 0;

	// Security Issues...
	if (nipper->fullReport == true)
	{

		// Simple Passwords
		if (nipper->simplePasswords > 1)
			addReportSection(nipper, section_security, report_dict_title1, report_dict_context, report_dict_rectext, 10, 8, 5, 3, sosDictionaryIssue);
		else if (nipper->simplePasswords > 0)
			addReportSection(nipper, section_security, report_dict_title2, report_dict_context, report_dict_rectext, 10, 8, 5, 3, sosDictionaryIssue);

		// Password Strength
		if (nipper->passwordStrengths > 1)
			addReportSection(nipper, section_security, report_strength_title1, report_strength_context, report_strength_rectext, 10, 8, 5, 3, sosStrengthIssue);
		else if (nipper->passwordStrengths > 0)
			addReportSection(nipper, section_security, report_strength_title2, report_strength_context, report_strength_rectext, 10, 8, 5, 3, sosStrengthIssue);

		// SNMP
		if (nipper->sos->snmp != 0)
		{
			if ((nipper->sos->snmp->community != 0) || (nipper->sos->snmp->host != 0))
				addReportSection(nipper, section_security, report_snmp_title, report_snmp_context, report_snmp_css_rectext, 10, 8, 5, 3, sosSNMPIssue);
		}

		// Default Policy is allow
		if (nipper->sos->defaultFirewallMode == false)
			addReportSection(nipper, section_security, report_defaultpolicy_title, report_defaultpolicy_context, report_defaultpolicy_rectext, 10, 8, 5, 3, sosDefaultPolicyIssue);

		// Policy Issues
		if (nipper->filterList == 0)
			addReportSection(nipper, section_security, report_policy_title, report_nopolicy_context, report_nopolicy_rectext, 10, 8, 5, 3, sosNoPolicyIssue);
		else
		{
			rulesAudit(nipper);
			if (nipper->aclIssues > 0)
				addReportSection(nipper, section_security, report_policy_title, report_policy_context, report_policy_rectext, 10, 8, 5, 3, sosPolicyIssue);
		}

		// Timeout
		if ((nipper->sos->authTimeout * 60) > nipper->connectionTimeout)
			nipper->insecureTimeouts++;
		authServerPointer = nipper->sos->authServer;
		while (authServerPointer != 0)
		{
			if ((authServerPointer->timeout * 60 ) > nipper->connectionTimeout)
				nipper->insecureTimeouts++;
			authServerPointer = authServerPointer->next;
		}
		if (nipper->insecureTimeouts > 0)
			addReportSection(nipper, section_security, report_timeout_title, report_timeout_context, report_timeout_rectext, 10, 8, 5, 3, sosTimeoutIssue);

		// Administrative HTTP Redirect
		if (nipper->sos->httpRedirect != true)
			addReportSection(nipper, section_security, report_httpred_title, report_httpred_context, report_httpred_rectext, 10, 8, 5, 3, sosHTTPRedirectIssue);

		// Management IP
		if (strcmp(nipper->sos->adminIP, "0.0.0.0") == 0)
			addReportSection(nipper, section_security, report_mngrip_title, report_mngrip_context, report_mngrip_rectext, 10, 8, 5, 3, sosManagementRIPIssue);

		// SSH Protocol Version
		if ((nipper->sos->sshEnabled == true) && (nipper->sos->sshVersion == 1))
			addReportSection(nipper, section_security, report_sshproto_title, report_sshproto_context, report_sshproto_rectext, 10, 8, 5, 3, sosSSHProtocolIssue);
	}

	// In Configuration Index
	addReportSection(nipper, section_config, settings_general_title, 0, 0, 0, 0, 0, 0, sosGeneralConfig);
	addReportSection(nipper, section_config, settings_services_title, 0, 0, 0, 0, 0, 0, sosServicesConfig);
	addReportSection(nipper, section_config, settings_admin_title, 0, 0, 0, 0, 0, 0, sosAdminConfig);
	if (nipper->sos->authServer != 0)
		addReportSection(nipper, section_config, settings_authservers_title, 0, 0, 0, 0, 0, 0, sosAuthServerConfig);
	if (nipper->sos->snmp != 0)
		addReportSection(nipper, section_config, settings_snmp_title, 0, 0, 0, 0, 0, 0, sosSNMPConfig);
	if (nipper->sos->sshEnabled == true)
		addReportSection(nipper, section_config, settings_ssh_title, 0, 0, 0, 0, 0, 0, sosSSHConfig);
	if (nipper->sos->interface !=0)
		addReportSection(nipper, section_config, settings_inter_title, 0, 0, 0, 0, 0, 0, sosInterfaceConfig);
	if (nipper->sos->zone != 0)
		addReportSection(nipper, section_config, settings_zone_title, 0, 0, 0, 0, 0, 0, sosZoneConfig);
	if (nipper->filterList != 0)
		addReportSection(nipper, section_config, settings_policies_title, 0, 0, 0, 0, 0, 0, sosPolicyConfig);
	if (nipper->sos->nameGroupMappings == true)
		addReportSection(nipper, section_config, settings_namegroupmap_title, 0, 0, 0, 0, 0, 0, sosNameGroupMapConfig);
	if (nipper->sos->nameMappings == true)
		addReportSection(nipper, section_config, settings_namemap_title, 0, 0, 0, 0, 0, 0, sosNameMapConfig);

	// Generate Report...
	generateReport(nipper);
}


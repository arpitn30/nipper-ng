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

// This file contains code for PIX/ASA reporting...

// Report PIX includes...
#include "report-access-list.c"
#include "report-debug.c"
#include "report-enable.c"
#include "report-general.c"
#include "report-http.c"
#include "report-icmp.c"
#include "report-interface.c"
#include "report-nat.c"
#include "report-passwords.c"
#include "report-protocols.c"
#include "report-route.c"
#include "report-snmp.c"
#include "report-ssh.c"


void generatePIXReport(struct nipperConfig *nipper)
{
	// Variables
	struct interfacePIXConfig *interfacePIXConfigPointer = 0;
	struct vulnerability *vulnPointer = 0;
	struct objectListConfig *objectListPointer = 0;
	struct sshAccessConfig *sshPointer = 0;

	// Security Section Issues
	if (nipper->fullReport == true)
	{

		// Software Version
		nipper->vulnIssues = 0;
		nipper->vulnIssueDos = false;
		nipper->vulnIssueRemote = false;
		if (nipper->deviceType == type_fwsm_firewall)
			vulnPointer = &report_vuln_fwsm;
		else
			vulnPointer = &report_vuln_pix;
		while (vulnPointer->next != 0)
		{
			checkVulnVersion(nipper, vulnPointer);
			vulnPointer = vulnPointer->next;
		}
		if (nipper->vulnIssues > 0)
			addReportSection(nipper, section_security, report_osver_title, report_osver_context, report_osver_rectext, 10, 8, 5, 3, pixVulnerabilityIssue);

		// Simple Passwords
		if (nipper->simplePasswords > 1)
			addReportSection(nipper, section_security, report_dict_title1, report_dict_context, report_dict_rectext, 10, 8, 5, 3, pixDictionaryIssue);
		else if (nipper->simplePasswords > 0)
			addReportSection(nipper, section_security, report_dict_title2, report_dict_context, report_dict_rectext, 10, 8, 5, 3, pixDictionaryIssue);

		// Password Strength
		if (nipper->passwordStrengths > 1)
			addReportSection(nipper, section_security, report_strength_title1, report_strength_context, report_strength_rectext, 10, 8, 5, 3, pixStrengthIssue);
		else if (nipper->passwordStrengths > 0)
			addReportSection(nipper, section_security, report_strength_title2, report_strength_context, report_strength_rectext, 10, 8, 5, 3, pixStrengthIssue);

		// Timeout
		if (nipper->pix->ssh != 0)
		{
			if (nipper->pix->ssh->timeout * 60 > nipper->connectionTimeout)
				nipper->insecureTimeouts++;
		}
		if (nipper->insecureTimeouts > 0)
			addReportSection(nipper, section_security, report_timeout_title, report_timeout_context, report_timeout_rectext, 10, 8, 5, 3, pixTimeoutIssue);

		// SNMP
		if (nipper->pix->snmp != 0)
		{
			if ((nipper->pix->snmp->enabled == true) && (nipper->pix->snmp->host != 0))
				nipper->snmpIssue = 2;
			else if (nipper->pix->snmp->enabled == true)
				nipper->snmpIssue = 1;
			else if (nipper->pix->snmp->host != 0)
				nipper->snmpIssue = -1;
		}
		if (nipper->snmpIssue != 0)
			addReportSection(nipper, section_security, report_snmp_title, report_snmp_context, report_snmp_css_rectext, 10, 8, 5, 3, pixSNMPIssue);

		// Access Lists
		rulesAudit(nipper);
		if (nipper->aclIssues > 0)
			addReportSection(nipper, section_security, report_accesslist_title, report_accesslist_context, report_accesslist_rectext, 10, 8, 5, 3, ciscoACLIssue);

		// SSH Remote Management Hosts
		if (nipper->pix->ssh != 0)
		{
			sshPointer = nipper->pix->ssh->access;
			while (sshPointer != 0)
			{
				if (strcmp(sshPointer->netMask, "255.255.255.255") != 0)
					nipper->sshManIssues++;
				sshPointer = sshPointer->next;
			}
		}
		if (nipper->sshManIssues > 0)
			addReportSection(nipper, section_security, report_sshman_title, report_sshman_context, report_sshman_rectext, 10, 8, 5, 3, sshManIssue);

		// FloodGuard
		if (nipper->pix->floodguard == false)
			addReportSection(nipper, section_security, report_floodguard_title, report_floodguard_context, report_floodguard_rectext, 10, 8, 5, 3, pixFloodGuardIssue);

		// uRPF verification
		if ((nipper->deviceType != type_fwsm_firewall) && (nipper->deviceUse == use_edge))
		{
			interfacePIXConfigPointer = nipper->pix->interface;
			while (interfacePIXConfigPointer != 0)
			{
				if ((interfacePIXConfigPointer->uRPF == false) && (interfacePIXConfigPointer->shutdown == false) && (strcmp(interfacePIXConfigPointer->ipAddress, "") != 0))
					nipper->uRPFIssues++;
				interfacePIXConfigPointer = interfacePIXConfigPointer->next;
			}
		}
		if (nipper->uRPFIssues != 0)
			addReportSection(nipper, section_security, report_urpf_title, report_urpf_context, report_urpf_rectext, 10, 8, 5, 3, pixURPFIssue);

		// SSH Protocol Version
		if ((nipper->pix->ssh != 0) && (nipper->deviceType != type_fwsm_firewall))
		{
			if (nipper->pix->ssh->version < 2)
				addReportSection(nipper, section_security, report_sshproto_title, report_sshproto_context, report_sshproto_rectext, 10, 8, 5, 3, pixSSHIssue);
		}
	}

	// Configuration Reporting...
	addReportSection(nipper, section_config, settings_general_title, 0, 0, 0, 0, 0, 0, pixGeneralConfig);
	addReportSection(nipper, section_config, settings_services_title, 0, 0, 0, 0, 0, 0, pixServicesConfig);
	if (((nipper->pix->enable != 0) || (nipper->pix->password[0] != 0)) && (nipper->passwords == true))
		addReportSection(nipper, section_config, settings_users_title, 0, 0, 0, 0, 0, 0, pixUsersConfig);
	if (nipper->pix->snmp != 0)
		addReportSection(nipper, section_config, settings_snmp_title, 0, 0, 0, 0, 0, 0, pixSNMPConfig);
	if (nipper->pix->ssh != 0)
		addReportSection(nipper, section_config, settings_ssh_title, 0, 0, 0, 0, 0, 0, pixSSHConfig);
	if (nipper->pix->http != 0)
		addReportSection(nipper, section_config, settings_http_title, 0, 0, 0, 0, 0, 0, pixHTTPConfig);
	if (nipper->pix->interface != 0)
		addReportSection(nipper, section_config, settings_inter_title, 0, 0, 0, 0, 0, 0, pixInterfaceConfig);
	if ((nipper->pix->staticNAT !=0) || (nipper->pix->staticPAT !=0))
		addReportSection(nipper, section_config, settings_natpat_title, 0, 0, 0, 0, 0, 0, pixNATPATConfig);
	if (nipper->pix->route !=0)
		addReportSection(nipper, section_config, settings_routing_title, 0, 0, 0, 0, 0, 0, pixRoutingConfig);
	if ((nipper->pix->standardAccessList > 0) || (nipper->pix->extendedAccessList > 0) || (nipper->pix->oldAccessList > 0))
		addReportSection(nipper, section_config, settings_accesslists_title, 0, 0, 0, 0, 0, 0, pixACLConfig);
	if (nipper->pix->icmp != 0)
		addReportSection(nipper, section_config, settings_icmpaccess_title, 0, 0, 0, 0, 0, 0, pixICMPConfig);
	if (nipper->pix->fixup != 0)
		addReportSection(nipper, section_config, settings_protoinspect_title, 0, 0, 0, 0, 0, 0, pixProtocolConfig);
	objectListPointer = nipper->objectList;
	while (objectListPointer != 0)
	{
		if (strcmp(objectListPointer->name, "OBJECTLIST") == 0)
			addReportSection(nipper, section_config, settings_objects_title, 0, 0, 0, 0, 0, 0, pixObjectConfig);
		objectListPointer = objectListPointer->next;
	}
	objectListPointer = nipper->objectList;
	while (objectListPointer != 0)
	{
		if (strcmp(objectListPointer->name, "NAMELIST") == 0)
			addReportSection(nipper, section_config, settings_namemap_title, 0, 0, 0, 0, 0, 0, nameMapConfig);
		objectListPointer = objectListPointer->next;
	}

	// Generate Report...
	generateReport(nipper);
}

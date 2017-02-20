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

// This file contains code for Firewall-1 reporting

// Report Firewall-1 includes...
#include "report-debug.c"
#include "report-objects.c"
#include "report-rules.c"
#include "report-services.c"


void generateFW1Report(struct nipperConfig *nipper)
{
	// Security Issues...
	if (nipper->fullReport == true)
	{

		// Firewall Rule Issues
		if (nipper->filterList == 0)
			nipper->aclIssues = -1;
		else
			rulesAudit(nipper);
		if (nipper->aclIssues != 0)
			addReportSection(nipper, section_security, report_fw1policy_title, report_fw1policy_context, report_fw1policy_rectext, 10, 8, 5, 3, fw1RulesIssue);
	}

	// Configuration Output
	if (nipper->filterList != 0)
		addReportSection(nipper, section_config, settings_policycol_title, 0, 0, 0, 0, 0, 0, fw1RulesConfig);
	if (nipper->fw1->gatewayClusterObjectCount > 0)
		addReportSection(nipper, section_config, settings_objects_gatewaycluster_title, 0, 0, 0, 0, 0, 0, fw1GatewayClusterConfig);
	if (nipper->fw1->clusterMemberObjectCount > 0)
		addReportSection(nipper, section_config, settings_objects_gatewayclustermem_title, 0, 0, 0, 0, 0, 0, fw1GatewayClusterMemberConfig);
	if (nipper->fw1->gatewayObjectCount > 0)
		addReportSection(nipper, section_config, settings_objects_gateway_title, 0, 0, 0, 0, 0, 0, fw1GatewayConfig);
	if (nipper->fw1->groupObjectCount > 0)
		addReportSection(nipper, section_config, settings_objects_groups_title, 0, 0, 0, 0, 0, 0, fw1GroupObjectsConfig);
	if (nipper->fw1->hostObjectCount > 0)
		addReportSection(nipper, section_config, settings_objects_hosts_title, 0, 0, 0, 0, 0, 0, fw1HostsConfig);
	if (nipper->fw1->networkObjectCount > 0)
		addReportSection(nipper, section_config, settings_objects_network_title, 0, 0, 0, 0, 0, 0, fw1NetworksConfig);
	if (nipper->fw1->dynamicNetObjectCount > 0)
		addReportSection(nipper, section_config, settings_objects_dynnet_title, 0, 0, 0, 0, 0, 0, fw1DynamicNetworkConfig);
	if (nipper->fw1->machinesRangeObjectCount > 0)
		addReportSection(nipper, section_config, settings_objects_machrange_title, 0, 0, 0, 0, 0, 0, fw1MachRangeConfig);
	if (nipper->fw1->serviceGroupCount > 0)
		addReportSection(nipper, section_config, settings_fw1servicegroup_title, 0, 0, 0, 0, 0, 0, fw1ServiceGroupConfig);
	if (nipper->fw1->serviceCount > 0)
		addReportSection(nipper, section_config, settings_fw1services_title, 0, 0, 0, 0, 0, 0, fw1ServiceConfig);

	// Generate Report...
	generateReport(nipper);
}


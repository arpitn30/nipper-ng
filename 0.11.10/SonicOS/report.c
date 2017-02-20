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

// This file contains code for SonicWall reporting

// Report SonicWall includes...
#include "report-general.c"
#include "report-debug.c"
#include "report-rules.c"
#include "report-services.c"


void generateSonicOSReport(struct nipperConfig *nipper)
{
	// Set ACL logging for different SonicOS devices
	// Could not set it in the usual place
	if (nipper->sonicos->enhanced == false)
	{
		nipper->logDenyRulesIssue = false;
		nipper->allRulesLogIssue = false;
		nipper->denyLogIssue = false;
	}

	// Security Issues...
	if (nipper->fullReport == true)
	{
		// Access Lists
		rulesAudit(nipper);
		nipper->aclIssues = nipper->anySource + nipper->networkSource + nipper->rejectRules + nipper->logDenyRules + nipper->anySourceService + nipper->anyDestination + nipper->networkDestination + nipper->anyDestinationService + nipper->filtersWithNoLogging + nipper->denyAllAndLog + nipper->disabledRules;
		if (nipper->aclIssues > 0)
			addReportSection(nipper, section_security, report_sonicosrules_title, report_sonicosrules_context, report_sonicosrules_rectext, 10, 8, 5, 3, sonicosRulesIssue);
	};

	// In Configuration Index
	addReportSection(nipper, section_config, settings_general_title, 0, 0, 0, 0, 0, 0, sonicosGeneralConfig);
	if (nipper->filterList != 0)
		addReportSection(nipper, section_config, settings_accessrules_title, 0, 0, 0, 0, 0, 0, sonicosRulesConfig);
	if (nipper->objectList != 0)
		addReportSection(nipper, section_config, settings_sonicosservices_title, 0, 0, 0, 0, 0, 0, sonicosServicesConfig);

	// Generate Report...
	generateReport(nipper);
}



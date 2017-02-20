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

// This file contains code for **<PLATFORM>** reporting

// Report **<PLATFORM>** includes...


void generate**<PLATFORM>**Report(struct nipperConfig *nipper)
{
	// Variables

	// Security Issues...
	if (nipper->fullReport == true)
	{
		// Access Lists
		rulesAudit(nipper);
		nipper->aclIssues = nipper->anySource + nipper->networkSource + nipper->rejectRules + nipper->logDenyRules + nipper->anySourceService + nipper->anyDestination + nipper->networkDestination + nipper->anyDestinationService + nipper->filtersWithNoLogging + nipper->denyAllAndLog + nipper->disabledRules;
		if (nipper->aclIssues > 0)
			addReportSection(nipper, section_security, report_**<PLATFORM>**_title, report_**<PLATFORM>**_context, report_**<PLATFORM>**_rectext, 10, 8, 5, 3, pix**<PLATFORM>**Issue);
	}

	// In Configuration Index
	addReportSection(nipper, section_config, settings_general_title, 0, 0, 0, 0, 0, 0, **<PLATFORM>**GeneralConfig);

	// Generate Report...
	generateReport(nipper);
}



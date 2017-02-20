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

// This file contains code for Passport reporting

// Report Passport includes...
#include "report-debug.c"
#include "report-filters.c"
#include "report-general.c"


void generatePASReport(struct nipperConfig *nipper)
{
	// Security Issues...
	if (nipper->fullReport == true)
	{

		// Filter Issues
		if (nipper->filterList == 0)
			nipper->aclIssues = -1;
		else
			rulesAudit(nipper);
		if (nipper->aclIssues != 0)
			addReportSection(nipper, section_security, report_pasfilter_title, report_pasfilter_context, report_pasfilter_rectext, 10, 8, 5, 3, pasFilterIssue);
	}

	// Configuration Output
	addReportSection(nipper, section_config, settings_general_title, 0, 0, 0, 0, 0, 0, pasGeneralConfig);
	if (nipper->filterList != 0)
		addReportSection(nipper, section_config, settings_filter_title, 0, 0, 0, 0, 0, 0, pasFilterConfig);

	// Generate Report...
	generateReport(nipper);
}


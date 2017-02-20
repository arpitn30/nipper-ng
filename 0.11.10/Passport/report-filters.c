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


void pasFilterConfig(struct nipperConfig *nipper)
{
	// ACL
	reportRules(nipper);
}


void pasFilterIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct filterConfig *filterPointer = 0;
	struct filterListConfig *filterListPointer = 0;
	char tempString[128];
	int ruleNumber = 0;

	output_parseText(report_pasfilter_obs, nipper, section_obs, rate_none, nipper->aclIssues, nipper->tableNum);
	
	// One Access List issue...
	if (nipper->aclIssues == 1)
	{
		filterListPointer = nipper->filterList;
		while (filterListPointer != 0)
		{
			ruleNumber = 1;

			// Set filter set name...
			if (strcmp(filterListPointer->name, "**UNASSIGNED**") == 0)
				strcpy(tempString, "Unassigned");
			else
				strcpy(tempString, filterListPointer->name);

			filterPointer = filterListPointer->filter;
			while (filterPointer != 0)
			{
				if (filterPointer->action != filter_action_remark)
				{
					reportCommonFilterIssues(nipper, tempString, "IP filter set", "filter ID", filterPointer, ruleNumber, filterListPointer);
					ruleNumber++;
				}
				filterPointer = filterPointer->next;
			}

			// If it was a deny all and log issue...
			if (filterListPointer->denyAllAndLog == true)
				fprintf(nipper->reportFile, "IP filter set %s %s", tempString, report_pasfilter_denylog);

			filterListPointer = filterListPointer->next;
		}
		output_newPara(nipper);
	}

	// More than one issue...
	else if (nipper->aclIssues > 1)
	{
		output_table(nipper, true, report_pasfilter_table, &report_pasfilter_table_heading);
		filterListPointer = nipper->filterList;
		while (filterListPointer != 0)
		{
			ruleNumber = 1;
			// Set filter set name...
			if (strcmp(filterListPointer->name, "**UNASSIGNED**") == 0)
				strcpy(tempString, "Unassigned");
			else
				strcpy(tempString, filterListPointer->name);

			filterPointer = filterListPointer->filter;
			while (filterPointer != 0)
			{
				if (filterPointer->action != filter_action_remark)
				{
					reportCommonFilterTableIssues(nipper, tempString, filterPointer, ruleNumber, filterListPointer);
	
					ruleNumber++;
				}
				filterPointer = filterPointer->next;
			}

			// If it was a deny all and log issue...
			if (filterListPointer->denyAllAndLog == true)
				fprintf(nipper->reportFile, "%s%s%sN/A%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid, nipper->tablerow_mid, report_pasfilter_denylog, nipper->tablerow_end);

			filterListPointer = filterListPointer->next;
		}
		output_table(nipper, false, report_pasfilter_table, &report_pasfilter_table_heading);
	}
	output_endsection(nipper, section_obs);
	output_parseText(report_pasfilter_impact, nipper, section_imp, rate_med, nipper->aclIssues, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_pasfilter_ease, nipper, section_ease, rate_noease, nipper->aclIssues, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_pasfilter_rec, nipper, section_rec, rate_none, nipper->aclIssues, nipper->tableNum);
	set_aclrec_list(nipper, &report_pasfilter_heading);
	output_list(nipper, &report_pasfilter_heading);
	output_parseText(report_fw1policy_rec2, nipper, section_none, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}

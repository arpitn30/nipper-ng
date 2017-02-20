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

// This file contains code for ScreenOS Policy reporting


void sosDefaultPolicyIssue(struct nipperConfig *nipper)
{
	output_parseText(report_defaultpolicy_obs, nipper, section_obs, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_defaultpolicy_impact, nipper, section_imp, rate_med, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_defaultpolicy_ease, nipper, section_ease, rate_noease, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_defaultpolicy_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void sosNoPolicyIssue(struct nipperConfig *nipper)
{
	output_parseText(report_policy_obs, nipper, section_obs, rate_none, -1, nipper->tableNum);
	output_endsection(nipper, section_obs);
	if (nipper->sos->defaultFirewallMode == false)
		output_parseText(report_nopolicy_impact, nipper, section_imp, rate_med, -1, nipper->tableNum);
	else
		output_parseText(report_nopolicy_impact, nipper, section_imp, rate_med, 1, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_policy_ease, nipper, section_ease, rate_noease, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_nopolicy_rec1, nipper, section_rec, rate_none, 0, nipper->tableNum);
	nipper->anySourceServiceIssue = false;
	nipper->bypassRulesIssue = false;
	nipper->defaultRulesIssue = false;
	set_aclrec_list(nipper, &report_issues_heading);
	output_list(nipper, &report_issues_heading);
	output_parseText(report_nopolicy_rec2, nipper, section_none, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void sosPolicyIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct filterConfig *filterPointer = 0;
	struct filterListConfig *filterListPointer = 0;
	char tempString[nipper->maxSize];

	output_parseText(report_policy_obs, nipper, section_obs, rate_none, nipper->aclIssues, nipper->tableNum);

	// One issue...
	if (nipper->aclIssues == 1)
	{
		filterListPointer = nipper->filterList;
		while (filterListPointer != 0)
		{
			memset(tempString, 0, sizeof(tempString));
			if (filterListPointer->global == true)
				strcpy(tempString, "global");
			else
				sprintf(tempString, "%s to %s", filterListPointer->fromZone, filterListPointer->toZone);
			filterPointer = filterListPointer->filter;
			while (filterPointer != 0)
			{
				if (filterPointer->action != filter_action_remark)
					reportCommonFilterIssues(nipper, tempString, "The", "policy ID", filterPointer, 0, filterListPointer);
				filterPointer = filterPointer->next;
			}

			// If it was a deny all and log issue...
			if (filterListPointer->denyAllAndLog == true)
				fprintf(nipper->reportFile, "The %s %s", filterListPointer->name, report_sospolicy_denylog);
			filterListPointer = filterListPointer->next;
		}
		output_newPara(nipper);
	}

	// More than one issue...
	else
	{
		output_table(nipper, true, report_policy_table, &report_policy_heading);

		filterListPointer = nipper->filterList;
		while (filterListPointer != 0)
		{

			memset(tempString, 0, sizeof(tempString));
			if (filterListPointer->global == false)
				sprintf(tempString, "%s%s%s%sNo", filterListPointer->fromZone, nipper->tablerow_mid, filterListPointer->toZone, nipper->tablerow_mid);
			else
				sprintf(tempString, "N/A%sN/A%sYes", nipper->tablerow_mid, nipper->tablerow_mid);

			filterPointer = filterListPointer->filter;
			while (filterPointer != 0)
			{
				if (filterPointer->action != filter_action_remark)
					reportCommonFilterTableIssues(nipper, tempString, filterPointer, 0, filterListPointer);
				filterPointer = filterPointer->next;
			}

			// If it was a deny all and log issue...
			if (filterListPointer->denyAllAndLog == true)
				fprintf(nipper->reportFile, "%s%s%sN/A%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid, nipper->tablerow_mid, report_sospolicyt_denylog, nipper->tablerow_end);

			filterListPointer = filterListPointer->next;
		}

		output_table(nipper, false, report_policy_table, &report_policy_heading);
	}
	output_endsection(nipper, section_obs);
	if (nipper->rejectIssue == true)
		output_parseText(report_policy_impact, nipper, section_imp, rate_med, 2, 0);
	else
		output_parseText(report_policy_impact, nipper, section_imp, rate_med, 1, 0);
	output_endsection(nipper, section_imp);
	output_parseText(report_policy_ease, nipper, section_ease, rate_noease, 0, 0);
	output_endsection(nipper, section_ease);
	output_parseText(report_policy_rec1, nipper, section_rec, rate_none, 0, nipper->tableNum);
	set_aclrec_list(nipper, &report_issues_heading);
	output_list(nipper, &report_issues_heading);
	output_parseText(report_fw1policy_rec2, nipper, section_none, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void sosPolicyConfig(struct nipperConfig *nipper)
{
	output_parseText(settings_policies_text, nipper, section_none, rate_none, 0, 0);
	output_list(nipper, &settings_sospolicy_heading);
	reportRules(nipper);
}


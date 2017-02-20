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

void ciscoACLIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct filterConfig *filterPointer = 0;
	struct filterListConfig *filterListPointer = 0;
	int ruleNumber = 0;

	output_parseText(report_accesslist_obs1, nipper, section_obs, rate_none, nipper->aclIssues, nipper->tableNum);
	
	// One Access List issue...
	if (nipper->aclIssues == 1)
	{
		filterListPointer = nipper->filterList;
		while (filterListPointer != 0)
		{
			ruleNumber = 1;
			filterPointer = filterListPointer->filter;
			while (filterPointer != 0)
			{
				if (filterPointer->action != filter_action_remark)
				{
					if (filterListPointer->type != access_std)
						reportCommonFilterIssues(nipper, filterListPointer->name, "ACL", "line", filterPointer, ruleNumber, filterListPointer);
					else
						reportCommonStandardFilterIssues(nipper, filterListPointer->name, "ACL", "line", filterPointer, ruleNumber, filterListPointer);
					ruleNumber++;
				}
				filterPointer = filterPointer->next;
			}

			// If it was a deny all and log issue...
			if (filterListPointer->denyAllAndLog == true)
			{
				if (filterListPointer->type != access_std)
					fprintf(nipper->reportFile, "The %s %s", filterListPointer->name, report_accesslist_denylog);
				else
					fprintf(nipper->reportFile, "The %s %s", filterListPointer->name, report_accesslist_std_denylog);
			}

			filterListPointer = filterListPointer->next;
		}
		output_newPara(nipper);
	}

	// More than one issue...
	else if (nipper->aclIssues > 1)
	{
		output_table(nipper, true, report_accesslist_table1, &report_accesslists_heading);
		filterListPointer = nipper->filterList;
		while (filterListPointer != 0)
		{
			ruleNumber = 1;

			filterPointer = filterListPointer->filter;
			while (filterPointer != 0)
			{
				if (filterPointer->action != filter_action_remark)
				{
					if (filterListPointer->type != access_std)
						reportCommonFilterTableIssues(nipper, filterListPointer->name, filterPointer, ruleNumber, filterListPointer);
					else
						reportCommonStandardFilterTableIssues(nipper, filterListPointer->name, filterPointer, ruleNumber, filterListPointer);
					ruleNumber++;
				}
				filterPointer = filterPointer->next;
			}

			// If it was a deny all and log issue...
			if (filterListPointer->denyAllAndLog == true)
			{
				if (filterListPointer->type != access_std)
					fprintf(nipper->reportFile, "%s%s%sN/A%s%s%s", nipper->tablerow_start, filterListPointer->name, nipper->tablerow_mid, nipper->tablerow_mid, report_accesslist_denylog, nipper->tablerow_end);
				else
					fprintf(nipper->reportFile, "%s%s%sN/A%s%s%s", nipper->tablerow_start, filterListPointer->name, nipper->tablerow_mid, nipper->tablerow_mid, report_accesslist_std_denylog, nipper->tablerow_end);
			}

			filterListPointer = filterListPointer->next;
		}
		output_table(nipper, false, report_accesslist_table1, &report_accesslists_heading);
	}
	output_endsection(nipper, section_obs);
	if ((nipper->deviceType == type_pix_firewall) && (nipper->deviceType == type_asa_firewall) && (nipper->deviceType == type_fwsm_firewall) && (nipper->aclIssues == -1))
		output_parseText(report_accesslist_noacl_pix_impact, nipper, section_imp, rate_med, nipper->aclIssues, 0);
	else
		output_parseText(report_accesslist_impact, nipper, section_imp, rate_med, nipper->aclIssues, 0);
	output_endsection(nipper, section_imp);
	output_parseText(report_accesslist_ease, nipper, section_ease, rate_noease, nipper->aclIssues, 0);
	output_endsection(nipper, section_ease);
	output_parseText(report_accesslist_rec, nipper, section_rec, rate_none, nipper->aclIssues, 0);
	set_aclrec_list(nipper, &report_aclrec_heading);
	output_list(nipper, &report_aclrec_heading);
	output_parseText(report_fw1policy_rec2, nipper, section_none, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}



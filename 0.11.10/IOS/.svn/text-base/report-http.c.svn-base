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

// This file contains the code for IOS reporting

void iosHTTPConfig(struct nipperConfig *nipper)
{
	output_table(nipper, true, settings_http_table, &settings_general_heading);
	if (nipper->ios->http->enabled == true)
		fprintf(nipper->reportFile, "%sHTTP Server%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sHTTP Server%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	switch(nipper->ios->http->authentication)
	{
		case http_auth_enable:
			fprintf(nipper->reportFile, "%sAuthentication Type%sEnable Password%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
		case http_auth_aaa:
			fprintf(nipper->reportFile, "%sAuthentication Type%sAAA%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			addAbbreviation("AAA", false);
			break;
		case http_auth_tacacs:
			fprintf(nipper->reportFile, "%sAuthentication Type%sTACACS%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			addAbbreviation("TACACS", false);
			break;
		case http_auth_local:
			fprintf(nipper->reportFile, "%sAuthentication Type%sLocal Users%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
	}
	if (nipper->ios->http->accessClass[0] == 0)
		fprintf(nipper->reportFile, "%sAccess Class (Access List Number)%sUnconfigured%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sAccess Class (Access List Number)%s%s%sn", nipper->tablerow_start, nipper->tablerow_mid, nipper->ios->http->accessClass, nipper->tablerow_end);
	output_table(nipper, false, settings_http_table, &settings_general_heading);
	addAbbreviation("HTTP", false);
}


void iosHTTPIssue(struct nipperConfig *nipper)
{
	output_parseText(report_http_obs1, nipper, section_obs, rate_none, 0, nipper->tableNum);
	if (nipper->ios->http == 0)
		output_parseText(report_http_obs2, nipper, section_none, rate_none, 0, nipper->tableNum);
	else if ((nipper->ios->http->authentication == http_auth_enable) && (nipper->ios->http->accessClass == 0))
		output_parseText(report_http_obs3, nipper, section_none, rate_none, 0, nipper->tableNum);
	else if (nipper->ios->http->accessClass == 0)
		output_parseText(report_http_obs4, nipper, section_none, rate_none, 0, nipper->tableNum);
	else if (nipper->ios->http->authentication != http_auth_enable)
		output_parseText(report_http_obs5, nipper, section_none, rate_none, 0, nipper->tableNum);
	else
		output_parseText(report_http_obs6, nipper, section_none, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_http_impact1, nipper, section_imp, rate_med, 0, nipper->tableNum);
	if (nipper->ios->http != 0)
	{
		if (nipper->ios->http->authentication == http_auth_enable)
			output_parseText(report_http_impact2, nipper, section_none, rate_med, 0, nipper->tableNum);
	}
	else
	{
		if (nipper->outputFormat == output_xml)
			fprintf(nipper->reportFile, "</text>\n");
	}
	if (nipper->ios->http != 0)
	{
		if (nipper->ios->http->accessClass[0] != 0)
			output_parseText(report_http_impact3, nipper, section_none, rate_med, 0, nipper->tableNum);
		else
		{
			if (nipper->outputFormat == output_xml)
				fprintf(nipper->reportFile, "</text>\n");
		}
	}
	output_newPara(nipper);
	output_endsection(nipper, section_imp);
	output_parseText(report_http_ease1, nipper, section_ease, rate_trivial, 0, nipper->tableNum);
	if (nipper->ios->http != 0)
	{
		if (nipper->ios->http->accessClass[0] != 0)
			output_parseText(report_http_ease2, nipper, section_none, rate_none, 0, nipper->tableNum);
		else
		{
			if (nipper->outputFormat == output_xml)
				fprintf(nipper->reportFile, "</text>\n");
		}
	}
	else
	{
		if (nipper->outputFormat == output_xml)
			fprintf(nipper->reportFile, "</text>\n");
	}
	output_endsection(nipper, section_ease);
	output_newPara(nipper);
	output_parseText(report_http_rec1, nipper, section_rec, rate_none, 0, nipper->tableNum);
	if (nipper->ios->http == 0)
		output_parseText(report_http_rec2, nipper, section_none, rate_none, 0, nipper->tableNum);
	else if (nipper->ios->http->accessClass[0] != 0)
		output_parseText(report_http_rec2, nipper, section_none, rate_none, 0, nipper->tableNum);
	else if (nipper->outputFormat == output_xml)
		fprintf(nipper->reportFile, "</text>\n");
	if (nipper->ios->http == 0)
		output_parseText(report_http_rec3, nipper, section_none, rate_none, 0, nipper->tableNum);
	else if (nipper->ios->http->authentication == http_auth_enable)
		output_parseText(report_http_rec3, nipper, section_none, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}



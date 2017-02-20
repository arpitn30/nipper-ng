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

// This file contains code for CSS Telnet reporting

void cssTelnetIssue(struct nipperConfig *nipper)
{
	// Table Pointers
	const char *tablerow_start;
	const char *tablerow_mid;
	const char *tablerow_end;
	switch (nipper->outputFormat)
	{
		case output_html:
			tablerow_start = table_html_rowstart;
			tablerow_mid = table_html_rowmid;
			tablerow_end = table_html_rowend;
			break;
		case output_xml:
			tablerow_start = table_xml_rowstart;
			tablerow_mid = table_xml_rowmid;
			tablerow_end = table_xml_rowend;
			break;
		case output_text:
			tablerow_start = table_text_rowstart;
			tablerow_mid = table_text_rowmid;
			tablerow_end = table_text_rowend;
			break;
		case output_latex:
			tablerow_start = table_latex_rowstart;
			tablerow_mid = table_latex_rowmid;
			tablerow_end = table_latex_rowend;
			break;
	}

	output_parseText(report_telnet_obs, nipper, section_obs, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_telnet_impact, nipper, section_imp, rate_med, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_telnet_ease, nipper, section_ease, rate_trivial, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_css_telnet_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}

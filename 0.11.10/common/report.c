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


void generateReport(struct nipperConfig *nipper)
{
	// Variables...
	int securityIssues = 0;
	char tempString[nipper->maxSize];
	int tempInt = 0;
	FILE *cssFile;
	struct reportText *reportTextPointer = 0;
	struct tableHeading *conclusionsList = 0;
	struct tableHeading *conclusionsPointer = 0;

	// Table Pointers
	switch (nipper->outputFormat)
	{
		case output_html:
			nipper->tablerow_start = table_html_rowstart;
			nipper->tablerow_mid = table_html_rowmid;
			nipper->tablerow_end = table_html_rowend;
			nipper->tablerow_itemsep = table_html_itemsep;
			break;
		case output_xml:
			nipper->tablerow_start = table_xml_rowstart;
			nipper->tablerow_mid = table_xml_rowmid;
			nipper->tablerow_end = table_xml_rowend;
			nipper->tablerow_itemsep = table_xml_itemsep;
			break;
		case output_text:
			nipper->tablerow_start = table_text_rowstart;
			nipper->tablerow_mid = table_text_rowmid;
			nipper->tablerow_end = table_text_rowend;
			nipper->tablerow_itemsep = table_text_itemsep;
			break;
		case output_latex:
			nipper->tablerow_start = table_latex_rowstart;
			nipper->tablerow_mid = table_latex_rowmid;
			nipper->tablerow_end = table_latex_rowend;
			nipper->tablerow_itemsep = table_latex_itemsep;
			break;
	}

	// Get number of security issues...
	reportTextPointer = nipper->report;
	while (reportTextPointer != 0)
	{
		if (reportTextPointer->section == section_security)
			securityIssues++;
		reportTextPointer = reportTextPointer->next;
	}

	// Create / open file for output
	if (nipper->outputFile == 0)
		nipper->reportFile = stdout;
	else
	{
		nipper->reportFile = fopen(nipper->outputFile, "w");
		if (nipper->reportFile == NULL)
		{
			nipper->nipperMode = mode_help;
			nipper->helpMode = help_error_report_file;
			return;
		}
	}

	// If CSV file specified...
	if (nipper->csvFilename != 0)
		nipper->csvFile = fopen(nipper->csvFilename, "w");

	// Set output friendly hostname
	outputFriendly(nipper->hostname, nipper->friendlyHostname, nipper->maxSize, nipper->outputFormat);

	switch (nipper->outputFormat)
	{
		case output_html:
			fprintf(nipper->reportFile, "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n<html>\n <head>\n  <title>");
			switch (nipper->deviceType)
			{
				case type_ios_switch:
					fprintf(nipper->reportFile, "Cisco Switch");
					break;
				case type_ios_router:
					fprintf(nipper->reportFile, "Cisco Router");
					break;
				case type_nmp_catalyst:
				case type_cos_catalyst:
				case type_ios_catalyst:
					fprintf(nipper->reportFile, "Cisco Catalyst");
					break;
				case type_asa_firewall:
				case type_fwsm_firewall:
				case type_pix_firewall:
					fprintf(nipper->reportFile, "Cisco Firewall");
					break;
				case type_css_filter:
					fprintf(nipper->reportFile, "Cisco CSS");
					break;
				case type_sos_firewall:
					fprintf(nipper->reportFile, "Juniper NetScreen Firewall");
					break;
				case type_passport:
					fprintf(nipper->reportFile, "Nortel Passport");
					break;
				case type_bayaccelar:
					fprintf(nipper->reportFile, "Bay Networks Accelar");
					break;
				case type_fw1_firewall:
					fprintf(nipper->reportFile, "CheckPoint Firewall-1");
					break;
				case type_nokiaip:
					fprintf(nipper->reportFile, "Nokia IP Firewall");
					break;
				case type_sonicwall:
					fprintf(nipper->reportFile, "SonicWall Firewall");
					break;
			}
			if ((nipper->deviceType == type_fw1_firewall) || (nipper->deviceType == type_nokiaip))
			{
				if (nipper->fullReport == true)
					fprintf(nipper->reportFile, " Security Report");
				else
					fprintf(nipper->reportFile, " Configuration Report");
			}
			else
			{
				if (nipper->fullReport == true)
					fprintf(nipper->reportFile, " %s Security Report", nipper->friendlyHostname);
				else
					fprintf(nipper->reportFile, " %s Configuration Report", nipper->friendlyHostname);
			}
			fprintf(nipper->reportFile, "</title>\n  <style type='text/css'>\n  <!--\n  ");
			if (nipper->cssFile == 0)
				fprintf(nipper->reportFile, "%s", html_css);
			else
			{
				cssFile = fopen(nipper->cssFile, "r");
				// Read line
				readLine(cssFile, tempString, nipper->maxSize);
				while (feof(cssFile) == 0)
				{
					fprintf(nipper->reportFile, "%s\n", tempString);
					// Read line, then write
					readLine(cssFile, tempString, nipper->maxSize);
				}
				fclose(cssFile);
			}
			fprintf(nipper->reportFile, "\n  \n  --></style>\n </head>\n <body class=\"mainbody\">\n <div class=\"pagebody\">\n<div id=\"title_header\" align=\"center\"><h2>%s</h2><br>\n<h2>", nipper->companyName);
			switch (nipper->deviceType)
			{
				case type_ios_switch:
					fprintf(nipper->reportFile, "Cisco Switch");
					break;
				case type_ios_router:
					fprintf(nipper->reportFile, "Cisco Router");
					break;
				case type_nmp_catalyst:
				case type_cos_catalyst:
				case type_ios_catalyst:
					fprintf(nipper->reportFile, "Cisco Catalyst");
					break;
				case type_asa_firewall:
				case type_fwsm_firewall:
				case type_pix_firewall:
					fprintf(nipper->reportFile, "Cisco Firewall");
					break;
				case type_css_filter:
					fprintf(nipper->reportFile, "Cisco CSS");
					break;
				case type_sos_firewall:
					fprintf(nipper->reportFile, "Juniper NetScreen Firewall");
					break;
				case type_passport:
					fprintf(nipper->reportFile, "Nortel Passport");
					break;
				case type_bayaccelar:
					fprintf(nipper->reportFile, "Bay Networks Accelar");
					break;
				case type_fw1_firewall:
					fprintf(nipper->reportFile, "CheckPoint Firewall-1");
					break;
				case type_nokiaip:
					fprintf(nipper->reportFile, "Nokia IP Firewall");
					break;
				case type_sonicwall:
					fprintf(nipper->reportFile, "SonicWall Firewall");
					break;
			}
			if ((nipper->deviceType == type_fw1_firewall) || (nipper->deviceType == type_nokiaip))
			{
				if (nipper->fullReport == true)
					fprintf(nipper->reportFile, " Security Report</h2></div>\n");
				else
					fprintf(nipper->reportFile, " Configuration Report</h2></div>\n");
			}
			else
			{
				if (nipper->fullReport == true)
					fprintf(nipper->reportFile, " Security Report</h2>\n<h4>of the</h4>\n<h2>%s ", nipper->friendlyHostname);
				else
					fprintf(nipper->reportFile, " Configuration Report</h2>\n<h4>of the</h4>\n<h2>%s ", nipper->friendlyHostname);
				switch (nipper->deviceType)
				{
					case type_ios_switch:
						fprintf(nipper->reportFile, "Cisco Switch");
						break;
					case type_ios_router:
						fprintf(nipper->reportFile, "Cisco Router");
						break;
					case type_nmp_catalyst:
					case type_cos_catalyst:
					case type_ios_catalyst:
						fprintf(nipper->reportFile, "Cisco Catalyst");
						break;
					case type_asa_firewall:
					case type_fwsm_firewall:
					case type_pix_firewall:
						fprintf(nipper->reportFile, "Cisco Firewall");
						break;
					case type_css_filter:
						fprintf(nipper->reportFile, "Cisco CSS");
						break;
					case type_sos_firewall:
						fprintf(nipper->reportFile, "Juniper NetScreen Firewall");
						break;
					case type_passport:
						fprintf(nipper->reportFile, "Nortel Passport");
						break;
					case type_bayaccelar:
						fprintf(nipper->reportFile, "Bay Networks Accelar");
						break;
					case type_sonicwall:
						fprintf(nipper->reportFile, "SonicWall Firewall");
						break;
				}
				fprintf(nipper->reportFile, "</h2></div>\n");
			}
			break;

		case output_xml:
			fprintf(nipper->reportFile, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<document title=\"");
			switch (nipper->deviceType)
			{
				case type_ios_switch:
					fprintf(nipper->reportFile, "Cisco Switch");
					break;
				case type_ios_router:
					fprintf(nipper->reportFile, "Cisco Router");
					break;
				case type_nmp_catalyst:
				case type_cos_catalyst:
				case type_ios_catalyst:
					fprintf(nipper->reportFile, "Cisco Catalyst");
					break;
				case type_asa_firewall:
				case type_fwsm_firewall:
				case type_pix_firewall:
					fprintf(nipper->reportFile, "Cisco Firewall");
					break;
				case type_css_filter:
					fprintf(nipper->reportFile, "Cisco CSS");
					break;
				case type_sos_firewall:
					fprintf(nipper->reportFile, "Juniper NetScreen Firewall");
					break;
				case type_passport:
					fprintf(nipper->reportFile, "Nortel Passport");
					break;
				case type_bayaccelar:
					fprintf(nipper->reportFile, "Bay Networks Accelar");
					break;
				case type_fw1_firewall:
					fprintf(nipper->reportFile, "CheckPoint Firewall-1");
					break;
				case type_nokiaip:
					fprintf(nipper->reportFile, "Nokia IP Firewall");
					break;
				case type_sonicwall:
					fprintf(nipper->reportFile, "SonicWall Firewall");
					break;
			}
			if ((nipper->deviceType == type_fw1_firewall) || (nipper->deviceType == type_nokiaip))
			{
				if (nipper->fullReport == true)
					fprintf(nipper->reportFile, " Security Report\">\n");
				else
					fprintf(nipper->reportFile, " Configuration Report\">\n");
			}
			else
			{
				if (nipper->fullReport == true)
					fprintf(nipper->reportFile, " %s Security Report\" device=\"%s\">\n", nipper->friendlyHostname, nipper->friendlyHostname);
				else
					fprintf(nipper->reportFile, " %s Configuration Report\" device=\"%s\">\n", nipper->friendlyHostname, nipper->friendlyHostname);
			}
			break;

		case output_text:
			switch (nipper->deviceType)
			{
				case type_ios_switch:
					fprintf(nipper->reportFile, "Cisco Switch");
					tempInt = 12;
					break;
				case type_ios_router:
					fprintf(nipper->reportFile, "Cisco Router");
					tempInt = 12;
					break;
				case type_nmp_catalyst:
				case type_cos_catalyst:
				case type_ios_catalyst:
					fprintf(nipper->reportFile, "Cisco Catalyst");
					tempInt = 14;
					break;
				case type_asa_firewall:
				case type_fwsm_firewall:
				case type_pix_firewall:
					fprintf(nipper->reportFile, "Cisco Firewall");
					tempInt = 14;
					break;
				case type_css_filter:
					fprintf(nipper->reportFile, "Cisco CSS");
					tempInt = 9;
					break;
				case type_sos_firewall:
					fprintf(nipper->reportFile, "Juniper NetScreen Firewall");
					tempInt = 26;
					break;
				case type_passport:
					fprintf(nipper->reportFile, "Nortel Passport");
					tempInt = 15;
					break;
				case type_bayaccelar:
					fprintf(nipper->reportFile, "Bay Networks Accelar");
					tempInt = 20;
					break;
				case type_fw1_firewall:
					fprintf(nipper->reportFile, "CheckPoint Firewall-1");
					tempInt = 21;
					break;
				case type_nokiaip:
					fprintf(nipper->reportFile, "Nokia IP Firewall");
					tempInt = 17;
					break;
				case type_sonicwall:
					fprintf(nipper->reportFile, "SonicWall Firewall");
					tempInt = 18;
					break;
			}
			if ((nipper->deviceType == type_fw1_firewall) || (nipper->deviceType == type_nokiaip))
			{
				if (nipper->fullReport == true)
				{
					tempInt = tempInt + 16;
					fprintf(nipper->reportFile, " Security Report\n");
				}
				else
				{
					tempInt = tempInt + 21;
					fprintf(nipper->reportFile, " Configuration Report\n");
				}
			}
			else
			{
				if (nipper->fullReport == true)
				{
					tempInt = tempInt + 17 + strlen(nipper->hostname);
					fprintf(nipper->reportFile, " %s Security Report\n", nipper->hostname);
				}
				else
				{
					tempInt = tempInt + 22 + strlen(nipper->hostname);
					fprintf(nipper->reportFile, " %s Configuration Report\n", nipper->hostname);
				}
			}
			while (tempInt > 0)
			{
				fprintf(nipper->reportFile, "=");
				tempInt--;
			}
			fprintf(nipper->reportFile, "\n\n");
			break;

		case output_latex:
			fprintf(nipper->reportFile, "\\documentclass[%s]{%s}\n\n\\begin{document}\n\n", nipper->paperSize, nipper->documentClass);
			break;
	}

	// Reset Counters...
	nipper->sectionCount = 0;
	nipper->subSectionCount = 0;

	if ((nipper->outputFormat != output_xml) && (nipper->outputFormat != output_latex))
	{
		// Contents
		output_parseTitle("Contents", nipper, section_contents);
		output_parseSectionIndex("About This Report", nipper);
		output_parseIndex("Organisation", nipper, section_about);
		output_parseIndex("Conventions", nipper, section_about);

		// -------------------------
		// Security Section Contents
		// -------------------------
		if (nipper->fullReport == true)
		{
			output_parseSectionIndex(report_security_title, nipper);
	
			output_parseIndex("Introduction", nipper, section_security);
	
			// Output Section Titles...
			reportTextPointer = nipper->report;
			while (reportTextPointer != 0)
			{
				if (reportTextPointer->section == section_security)
					output_parseIndex(reportTextPointer->sectionTitle, nipper, reportTextPointer->section);
				reportTextPointer = reportTextPointer->next;
			}

			output_parseIndex("Conclusions", nipper, section_security);

			// End of security index
			switch (nipper->outputFormat)
			{
				case output_text:
					fprintf(nipper->reportFile, "\n");
					break;
			}
		}
	
		// ------------------------------
		// Configuration Section Contents
		// ------------------------------
		if (nipper->configReport == true)
		{
			output_parseSectionIndex(report_config_title, nipper);

			output_parseIndex("Introduction", nipper, section_config);

			// Output Section Titles...
			reportTextPointer = nipper->report;
			while (reportTextPointer != 0)
			{
				if (reportTextPointer->section == section_config)
					output_parseIndex(reportTextPointer->sectionTitle, nipper, reportTextPointer->section);
				reportTextPointer = reportTextPointer->next;
			}

			switch (nipper->outputFormat)
			{
				case output_text:
					fprintf(nipper->reportFile, "\n");
					break;
			}
		}
	
		// End of index
		output_abbrevContents(nipper);
		output_endsection(nipper, subsection_end);
	}

	// Reset Counters...
	nipper->sectionCount = 0;
	nipper->subSectionCount = 0;


// ---------------------------------------------------------------------------------------------------------
// About this Report Section

	output_parseTitle("About This Report", nipper, section_main_abt);

	// Document Organisation...
	output_parseTitle("Organisation", nipper, section_about);
	if ((nipper->deviceType == type_fw1_firewall) || (nipper->deviceType == type_nokiaip))
		output_parseText(report_organisation_fw1, nipper, section_none, rate_none, tempInt, 0);
	else
		output_parseText(report_organisation, nipper, section_none, rate_none, tempInt, 0);
	conclusionsList = &report_organisation_heading;
	if (nipper->fullReport == false)
		conclusionsList->password = true;
	conclusionsList = conclusionsList->next;
	if (nipper->configReport == false)
		conclusionsList->password = true;
	conclusionsList = conclusionsList->next;
	if ((nipper->appendix == false) || (nipper->abs == false))
		conclusionsList->password = true;
	conclusionsList = conclusionsList->next;
	if ((nipper->appendix == false) || (nipper->commonPorts == false))
		conclusionsList->password = true;
	conclusionsList = conclusionsList->next;
	if ((nipper->appendix == false) || (nipper->loggingLevels == false))
		conclusionsList->password = true;
	conclusionsList = conclusionsList->next;
	if ((nipper->appendix == false) || (nipper->timeZones == false))
		conclusionsList->password = true;
	conclusionsList = conclusionsList->next;
	if ((nipper->appendix == false) || (nipper->nipperVersion == false))
		conclusionsList->password = true;
	conclusionsList = 0;
	output_list(nipper, &report_organisation_heading);

	output_endsection(nipper, subsection_end);

	// Document conventions...
	output_parseTitle("Conventions", nipper, section_about);
	output_parseText(report_conventions, nipper, section_none, rate_none, 0, nipper->tableNum);
	output_table(nipper, true, report_conventions_table, &report_conventions_heading);
	fprintf(nipper->reportFile, "%s", nipper->tablerow_start);
	output_parseText(report_conventions1_1, nipper, section_none, rate_none, 0, 0);
	fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
	output_parseText(report_conventions1_2, nipper, section_none, rate_none, 0, 0);
	fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
	fprintf(nipper->reportFile, "%s", nipper->tablerow_start);
	output_parseText(report_conventions2_1, nipper, section_none, rate_none, 0, 0);
	fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
	output_parseText(report_conventions2_2, nipper, section_none, rate_none, 0, 0);
	fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
	fprintf(nipper->reportFile, "%s", nipper->tablerow_start);
	output_parseText(report_conventions3_1, nipper, section_none, rate_none, 0, 0);
	fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
	output_parseText(report_conventions3_2, nipper, section_none, rate_none, 0, 0);
	fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
	fprintf(nipper->reportFile, "%s", nipper->tablerow_start);
	output_parseText(report_conventions4_1, nipper, section_none, rate_none, 0, 0);
	fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
	output_parseText(report_conventions4_2, nipper, section_none, rate_none, 0, 0);
	fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
	fprintf(nipper->reportFile, "%s", nipper->tablerow_start);
	output_parseText(report_conventions5_1, nipper, section_none, rate_none, 0, 0);
	fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
	output_parseText(report_conventions5_2, nipper, section_none, rate_none, 0, 0);
	fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
	output_table(nipper, false, report_conventions_table, &report_conventions_heading);
	output_endsection(nipper, subsection_end);

	output_endsection(nipper, section_end);


// ---------------------------------------------------------------------------------------------------------
// Security Report Section

	// Security Report section
	if (nipper->fullReport == true)
	{
		// Introduction
		output_parseTitle(report_security_title, nipper, section_main_sec);
		output_parseTitle("Introduction", nipper, section_security);
		if ((nipper->deviceType == type_fw1_firewall) || (nipper->deviceType == type_nokiaip))
			output_parseText(report_security_intro_fw1, nipper, section_none, rate_none, securityIssues, 0);
		else
			output_parseText(report_security_intro, nipper, section_none, rate_none, securityIssues, 0);
		output_endsection(nipper, subsection_end);

		// Issue Sections...
		reportTextPointer = nipper->report;
		while (reportTextPointer != 0)
		{
			if (reportTextPointer->section == section_security)
			{
				output_parseTitle(reportTextPointer->sectionTitle, nipper, section_security);
				reportTextPointer->writeSection(nipper);
				output_endsection(nipper, subsection_end);
			}
			reportTextPointer = reportTextPointer->next;
		}

		// Conclusions...
		output_parseTitle("Conclusions", nipper, section_security);
		if (securityIssues > 0)
		{
			if ((nipper->deviceType == type_fw1_firewall) || (nipper->deviceType == type_nokiaip))
				output_parseText(report_security_concl_fw1, nipper, section_none, rate_none, securityIssues, 0);
			else
				output_parseText(report_security_concl, nipper, section_none, rate_none, securityIssues, 0);
			reportTextPointer = nipper->report;
			while (reportTextPointer != 0)
			{
				if (reportTextPointer->section == section_security)
					conclusionsList = newListItem(conclusionsList, reportTextPointer->shortConText);
				reportTextPointer = reportTextPointer->next;
			}
			output_list(nipper, conclusionsList);
			while (conclusionsList != 0)
			{
				conclusionsPointer = conclusionsList->next;
				free (conclusionsList);
				conclusionsList = conclusionsPointer;
			}
		}
		else
		{
			if ((nipper->deviceType == type_fw1_firewall) || (nipper->deviceType == type_nokiaip))
				output_parseText(report_security_concl_fw1, nipper, section_none, rate_none, securityIssues, 0);
			else
				output_parseText(report_security_concl, nipper, section_none, rate_none, securityIssues, 0);
		}
		output_endsection(nipper, subsection_end);

		// End Section
		output_endsection(nipper, section_end);
	}


// ---------------------------------------------------------------------------------------------------------
// Configuration Report Section

	// Output report introduction
	if (nipper->configReport == true)
	{
		output_parseTitle(report_config_title, nipper, section_main_con);
		output_parseTitle("Introduction", nipper, section_config);
		if ((nipper->deviceType == type_fw1_firewall) || (nipper->deviceType == type_nokiaip))
			output_parseText(report_config_intro_fw1, nipper, section_none, rate_none, 0, 0);
		else
			output_parseText(report_config_intro, nipper, section_none, rate_none, 0, 0);
		output_endsection(nipper, subsection_end);

		// Output Report Configuration Sections...
		reportTextPointer = nipper->report;
		while (reportTextPointer != 0)
		{
			if (reportTextPointer->section == section_config)
			{
				output_parseTitle(reportTextPointer->sectionTitle, nipper, section_config);
				reportTextPointer->writeSection(nipper);
				output_endsection(nipper, subsection_end);
			}
			reportTextPointer = reportTextPointer->next;
		}

		// End Section
		output_endsection(nipper, section_end);
	}


// ---------------------------------------------------------------------------------------------------------
// Appendix Report Section

	// Appendix
	if (nipper->appendix == true)
		generateAppendix(nipper);

	// Output file end
	switch (nipper->outputFormat)
	{
		case output_html:
			fprintf(nipper->reportFile, "</div>\n</body>\n</html>\n");
			break;

		case output_latex:
			fprintf(nipper->reportFile, "\\end{document}\n");
			break;

		case output_xml:
			fprintf(nipper->reportFile, "</document>\n");
			break;
	}

	// If CSV file specified...
	if (nipper->csvFilename != 0)
		fclose(nipper->csvFile);

	// Close file
	if (nipper->outputFile != 0)
		fclose(nipper->reportFile);
}


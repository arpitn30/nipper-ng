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

#define section_none 0
#define section_obs 1
#define section_imp 2
#define section_ease 3
#define section_rec 4
#define subsection_end 5
#define section_end 6

#define rate_none 0
#define rate_low 1
#define rate_lowmed 2
#define rate_med 3
#define rate_medhigh 4
#define rate_high 5
#define rate_noease 6
#define rate_trivial 7
#define rate_moderate 8
#define rate_difficult 9


// Make text format friendly
// -------------------------
// This routing will convert the text into a version that
// is friendly to whatever format the report is to be
// output in.
void outputFriendly(char *line, char *output, int maxSize, int outputFormat)
{
	switch (outputFormat)
	{
		case output_xml:
		case output_html:
			htmlFriendly(line, output, maxSize);
			break;

		case output_latex:
			latexFriendly(line, output, maxSize);
			break;

		default:
			sprintf(output, "%s", line);
			break;
	}
}


// Insert Bullet List
void output_list(struct nipperConfig *nipper, struct tableHeading *listitems)
{
	// Variables
	struct tableHeading *listPointer = 0;
	int itemCount = 0;
	
	// Get Item Count...
	listPointer = listitems;
	while (listPointer != 0)
	{
		if (listPointer->password == false)
			itemCount++;
		listPointer = listPointer->next;
	}

	if (itemCount > 0)
	{
		// Draw list start
		switch (nipper->outputFormat)
		{
			case output_html:
				fprintf(nipper->reportFile, "<ul>\n");
				break;
			case output_latex:
				fprintf(nipper->reportFile, "\\begin{itemize}\n");
				break;
			case output_xml:
				fprintf(nipper->reportFile, "   <list>\n");
				break;
		}

		// Draw list items
		listPointer = listitems;
		while (listPointer != 0)
		{
			if (listPointer->password == false)
			{
				if (itemCount == 1)
				{
					switch (nipper->outputFormat)
					{
						case output_html:
							fprintf(nipper->reportFile, "<li>%s.</li>\n", listPointer->heading);
							break;
						case output_latex:
							fprintf(nipper->reportFile, "\\item %s.\n", listPointer->heading);
							break;
						case output_text:
							fprintf(nipper->reportFile, "  * %s.\n", listPointer->heading);
							break;
						case output_xml:
							fprintf(nipper->reportFile, "    <listitem>%s.</listitem>\n", listPointer->heading);
							break;
					}
				}
				else
				{
					switch (nipper->outputFormat)
					{
						case output_html:
							fprintf(nipper->reportFile, "<li>%s;</li>\n", listPointer->heading);
							break;
						case output_latex:
							fprintf(nipper->reportFile, "\\item %s;\n", listPointer->heading);
							break;
						case output_text:
							fprintf(nipper->reportFile, "  * %s;\n", listPointer->heading);
							break;
						case output_xml:
							fprintf(nipper->reportFile, "    <listitem>%s;</listitem>\n", listPointer->heading);
							break;
					}
				}
				itemCount--;
			}
			listPointer = listPointer->next;
		}
	
		// Draw list end
		switch (nipper->outputFormat)
		{
			case output_html:
				fprintf(nipper->reportFile, "</ul>\n");
				break;
			case output_latex:
				fprintf(nipper->reportFile, "\\end{itemize}\n");
				break;
			case output_text:
				fprintf(nipper->reportFile, "\n");
				break;
			case output_xml:
				fprintf(nipper->reportFile, "   </list>\n");
				break;
		}
	}
}


void set_aclrec_list(struct nipperConfig *nipper, struct tableHeading *listitems)
{
	// Variables
	struct tableHeading *listPointer = 0;

	listPointer = listitems;

	// If Any Source...
	if (nipper->anySourceIssue == false)
		listPointer->password = true;
	else
		listPointer->password = false;

	// If Network Source...
	listPointer = listPointer->next;
	if (nipper->networkSourceIssue == false)
		listPointer->password = true;
	else
		listPointer->password = false;

	// If Source Service...
	listPointer = listPointer->next;
	if (nipper->anySourceServiceIssue == false)
		listPointer->password = true;
	else
		listPointer->password = false;

	// If Any Destination...
	listPointer = listPointer->next;
	if (nipper->anyDestinationIssue == false)
		listPointer->password = true;
	else
		listPointer->password = false;

	// If Network Destination...
	listPointer = listPointer->next;
	if (nipper->networkDestinationIssue == false)
		listPointer->password = true;
	else
		listPointer->password = false;

	// If Destination Service...
	listPointer = listPointer->next;
	if (nipper->anyDestinationServiceIssue == false)
		listPointer->password = true;
	else
		listPointer->password = false;

	// If Log Denied...
	listPointer = listPointer->next;
	if (nipper->logDenyRulesIssue == false)
		listPointer->password = true;
	else
		listPointer->password = false;

	// If Disabled...
	listPointer = listPointer->next;
	if (nipper->disabledRulesIssue == false)
		listPointer->password = true;
	else
		listPointer->password = false;

	// If Reject...
	listPointer = listPointer->next;
	if (nipper->rejectRulesIssue == false)
		listPointer->password = true;
	else
		listPointer->password = false;

	// If Bypass...
	listPointer = listPointer->next;
	if (nipper->bypassRulesIssue == false)
		listPointer->password = true;
	else
		listPointer->password = false;

	// If Default...
	listPointer = listPointer->next;
	if (nipper->defaultRulesIssue == false)
		listPointer->password = true;
	else
		listPointer->password = false;

	// If Log Everything...
	listPointer = listPointer->next;
	if (nipper->allRulesLogIssue == false)
		listPointer->password = true;
	else
		listPointer->password = false;

	// If Deny All and Log...
	listPointer = listPointer->next;
	if (nipper->denyLogIssue == false)
		listPointer->password = true;
	else
		listPointer->password = false;
}


void table_row_span(struct nipperConfig *nipper, struct tableHeading *heading, char *text)
{
	// Variables...
	int spanCount = 0;
	char tempString[nipper->maxSize];
	struct tableHeading *headingPointer = 0;

	// Get the number of columns to span
	headingPointer = heading;
	while (headingPointer != 0)
	{
		spanCount++;
		headingPointer = headingPointer->next;
	}

	// Sanitise the text for the report format...
	outputFriendly(text, tempString, nipper->maxSize, nipper->outputFormat);

	// Output the table row...
	switch (nipper->outputFormat)
	{
		case output_html:
			fprintf(nipper->reportFile, "<tr><td colspan=\"%d\">%s</td></tr>\n", spanCount, tempString);
			break;
		case output_xml:
			fprintf(nipper->reportFile, "      <tablerow>\n       <tableentry colspan=\"%d\"><item>%s</item></tableentry>\n      </tablerow>\n", spanCount, tempString);
			break;
		case output_latex:
			fprintf(nipper->reportFile, "\\multicolumn{%d}{|c|}{%s} \\\\", spanCount, tempString);
			break;
		case output_text:
			fprintf(nipper->reportFile, "%s\n", tempString);
			break;
	}
}


// Insert Start / End of Table
// ---------------------------
// This code inserts the start of end of a table into the
// report output.
void output_table(struct nipperConfig *nipper, int tableStart, const char *tableTitle, struct tableHeading *heading)
{
	// Variables
	struct tableHeading *headingPointer = 0;
	int tempInt = 0;
	int total = 0;
	int remainder = 0;
	char friendlyCaption[nipper->maxSize];

	outputFriendly((char *)tableTitle, friendlyCaption, nipper->maxSize, nipper->outputFormat);

	// Table start...
	if (tableStart == true)
	{
		switch (nipper->outputFormat)
		{
			case output_html:
				fprintf(nipper->reportFile, "<table class=\"table\">\n <caption>Table %d: %s</caption>\n <thead>\n  <tr>", nipper->tableNum, friendlyCaption);
				headingPointer = heading;
				while (headingPointer != 0)
				{
					if ((nipper->passwords == true) || (headingPointer->password == false))
						fprintf(nipper->reportFile, "\n   <th>%s</th>", headingPointer->heading);
					headingPointer = headingPointer->next;
				}
				fprintf(nipper->reportFile, "\n  </tr>\n</thead>\n <tbody>\n");
				break;

			case output_xml:
				fprintf(nipper->reportFile, "    <table number=\"%d\" ref=\"TABLEREF%d\">\n", nipper->tableNum, nipper->tableNum);
				fprintf(nipper->reportFile, "     <caption>%s</caption>\n     <tableheadings>\n", friendlyCaption);
				headingPointer = heading;
				while (headingPointer != 0)
				{
					if ((nipper->passwords == true) || (headingPointer->password == false))
						fprintf(nipper->reportFile, "      <tableheading>%s</tableheading>\n", headingPointer->heading);
					headingPointer = headingPointer->next;
				}
				fprintf(nipper->reportFile, "     </tableheadings>\n     <tablebody>\n");
				break;

			case output_latex:
				// Print start of table
				fprintf(nipper->reportFile, "\\begin{table}[h!]\n");
				fprintf(nipper->reportFile, "\\begin{tabular}{|");
				headingPointer = heading;
				while (headingPointer != 0)
				{
					if ((nipper->passwords == true) || (headingPointer->password == false))
						fprintf(nipper->reportFile, " c |");
					headingPointer = headingPointer->next;
				}
				fprintf(nipper->reportFile, "}\n\\hline\n");
				headingPointer = heading;
				while (headingPointer != 0)
				{
					if ((nipper->passwords == true) || (headingPointer->password == false))
					{
						if (headingPointer->next != 0)
							fprintf(nipper->reportFile, "%s&", headingPointer->heading);
						else
							fprintf(nipper->reportFile, "%s\\\\\n", headingPointer->heading);
					}
					headingPointer = headingPointer->next;
				}
				fprintf(nipper->reportFile, "\\hline\n");
				break;

			case output_text:
				total = 0;
				tempInt = 0;
				// Count headings length
				headingPointer = heading;
				while (headingPointer != 0)
				{
					if ((nipper->passwords == true) || (headingPointer->password == false))
					{
						total += strlen(headingPointer->heading);
						tempInt++;
					}
					headingPointer = headingPointer->next;
				}
				if (nipper->tableNum < 10)
					remainder = 1;
				else if (nipper->tableNum < 100)
					remainder = 2;
				else if (nipper->tableNum < 1000)
					remainder = 3;
				else
					remainder = 4;
				total += (tempInt * 2) - 2;
				// Is table title or headings longest
				if ((strlen(tableTitle) + 8 + remainder) > total)
					total = strlen(tableTitle) + 8 + remainder;
				// Print start of table
				for (tempInt = 0; tempInt < total; tempInt++)
				{
					fprintf(nipper->reportFile, "-");
				}
				fprintf(nipper->reportFile, "\n");
				headingPointer = heading;
				while (headingPointer != 0)
				{
					if ((nipper->passwords == true) || (headingPointer->password == false))
					{
						if (headingPointer->next != 0)
							fprintf(nipper->reportFile, "%s, ", headingPointer->heading);
						else
							fprintf(nipper->reportFile, "%s", headingPointer->heading);
					}
					headingPointer = headingPointer->next;
				}
				fprintf(nipper->reportFile, "\n");
				for (tempInt = 0; tempInt < total; tempInt++)
				{
					fprintf(nipper->reportFile, "-");
				}
				fprintf(nipper->reportFile, "\n");
				break;
		}
	}

	// Table end...
	else
	{
		switch (nipper->outputFormat)
		{
			case output_html:
				fprintf(nipper->reportFile, " </tbody>\n</table>\n&nbsp;<br>\n\n");
				break;

			case output_xml:
				fprintf(nipper->reportFile, "     </tablebody>\n    </table>\n");
				break;

			case output_latex:
				fprintf(nipper->reportFile, "\\end{tabular}\n");
				fprintf(nipper->reportFile, "\\caption{%s}\n", friendlyCaption);
				fprintf(nipper->reportFile, "\\end{table}\n\n");
				break;

			case output_text:
				total = 0;
				tempInt = 0;
				// Count headings length
				headingPointer = heading;
				while (headingPointer != 0)
				{
					if ((nipper->passwords == true) || (headingPointer->password == false))
					{
						total += strlen(headingPointer->heading);
						tempInt++;
					}
					headingPointer = headingPointer->next;
				}
				if (nipper->tableNum < 10)
					remainder = 1;
				else if (nipper->tableNum < 100)
					remainder = 2;
				else if (nipper->tableNum < 1000)
					remainder = 3;
				else
					remainder = 4;
				total += (tempInt * 2) - 2;
				// Is table title or headings longest
				if ((strlen(tableTitle) + 8 + remainder) > total)
					total = strlen(tableTitle) + 8 + remainder;
				for (tempInt = 0; tempInt < total; tempInt++)
				{
					fprintf(nipper->reportFile, "-");
				}
				fprintf(nipper->reportFile, "\nTable %d: %s\n\n", nipper->tableNum, friendlyCaption);
				break;
		}
		nipper->tableNum++;
	}
}


// Insert New Paragrapgh
// ---------------------
// This code simply inserts a new paragraph.
void output_newPara(struct nipperConfig *nipper)
{
	switch (nipper->outputFormat)
	{
		case output_html:
			fprintf(nipper->reportFile, "<br>\n&nbsp;<br>\n");
			break;
		case output_latex:
		case output_text:
			fprintf(nipper->reportFile, "\n\n");
			break;
	}
}


#define section_main 0
#define section_main_sec 1
#define section_main_con 2
#define section_main_app 3
#define section_main_abt 4
#define section_security 5
#define section_config 6
#define section_appendix 7
#define section_about 8
#define section_contents 20

// Report Index Parsing and Output
// -------------------------------
// This code will output the index text and create hyperlinks (where required) for
// the different output formats.
void output_parseIndex(const char *theText, struct nipperConfig *nipper, int section)
{
	// Variables...
	int textLoop = 0;

	// Increment Count...
	nipper->subSectionCount++;

	switch (nipper->outputFormat)
	{
		case output_html:
			if (section == section_security)
				fprintf(nipper->reportFile, "&nbsp;&nbsp;&nbsp;&nbsp;%d.%d. <a href=\"#sec_", nipper->sectionCount, nipper->subSectionCount);
			else if (section == section_config)
				fprintf(nipper->reportFile, "&nbsp;&nbsp;&nbsp;&nbsp;%d.%d. <a href=\"#con_", nipper->sectionCount, nipper->subSectionCount);
			else if (section == section_appendix)
				fprintf(nipper->reportFile, "&nbsp;&nbsp;&nbsp;&nbsp;%d.%d. <a href=\"#app_", nipper->sectionCount, nipper->subSectionCount);
			else if (section == section_about)
				fprintf(nipper->reportFile, "&nbsp;&nbsp;&nbsp;&nbsp;%d.%d. <a href=\"#abt_", nipper->sectionCount, nipper->subSectionCount);
			else
				fprintf(nipper->reportFile, "&nbsp;&nbsp;&nbsp;&nbsp;%d.%d. <a href=\"#", nipper->sectionCount, nipper->subSectionCount);
			for (textLoop = 0; textLoop < strlen(theText); textLoop++)
			{
				if (theText[textLoop] != ' ')
					fprintf(nipper->reportFile, "%c", theText[textLoop]);
			}
			fprintf(nipper->reportFile, "\">%s</a><br>\n", theText);
			break;

		case output_text:
			fprintf(nipper->reportFile, "  %d.%d. %s\n", nipper->sectionCount, nipper->subSectionCount, theText);
			break;
	}
}


// Report Index Parsing and Output
// -------------------------------
// This code will output the index text and create hyperlinks (where required) for
// the different output formats.
void output_parseSectionIndex(const char *theText, struct nipperConfig *nipper)
{
	// Variables...
	int textLoop = 0;

	// Init Sub Section
	nipper->sectionCount++;
	nipper->subSectionCount = 0;

	switch (nipper->outputFormat)
	{
		case output_html:
			fprintf(nipper->reportFile, "<b>%d. <a href=\"#", nipper->sectionCount);
			for (textLoop = 0; textLoop < strlen(theText); textLoop++)
			{
				if (theText[textLoop] != ' ')
					fprintf(nipper->reportFile, "%c", theText[textLoop]);
			}
			fprintf(nipper->reportFile, "\">%s</a></b><br>\n", theText);
			break;

		case output_text:
			fprintf(nipper->reportFile, "%d. %s\n", nipper->sectionCount, theText);
			break;
	}
}


// Report Title Parsing and Output
// -------------------------------
// This code will output the section title and create a link destination (where
// required) for the different output formats.
void output_parseTitle(const char *theText, struct nipperConfig *nipper, int section)
{
	// Variables...
	int textLoop = 0;
	int length = 0;
	char tempChar;

	// Sort out section counters...
	if ((section == section_main_sec) || (section == section_main_con) || (section == section_main_app) || (section == section_main_abt) || (section == section_main))
	{
		nipper->sectionCount++;
		nipper->subSectionCount = 0;
	}
	else if (section != section_contents)
		nipper->subSectionCount++;

	switch (nipper->outputFormat)
	{
		case output_latex:
			if ((section == section_contents) || (section == section_main_sec) || (section == section_main_con) || (section == section_main_abt) || (section == section_main_app) || (section == section_main))
				fprintf(nipper->reportFile, "\\section[");
			else
				fprintf(nipper->reportFile, "\\subsection[");
			for (textLoop = 0; textLoop < strlen(theText); textLoop++)
			{
				if (theText[textLoop] != ' ')
					fprintf(nipper->reportFile, "%c", theText[textLoop]);
			}
			fprintf(nipper->reportFile, "%s]\n  {%s}\n\n", nipper->hostname, theText);
			break;

		case output_html:
			if (section == section_contents)
				fprintf(nipper->reportFile, "<hr><h2><a name=\"");
			else if ((section == section_main_sec) || (section == section_main_con) || (section == section_main_abt) || (section == section_main_app) || (section == section_main))
				fprintf(nipper->reportFile, "<hr><h2>%d. <a name=\"", nipper->sectionCount);
			else if (section == section_security)
				fprintf(nipper->reportFile, "<h3>%d.%d. <a name=\"sec_", nipper->sectionCount, nipper->subSectionCount);
			else if (section == section_config)
				fprintf(nipper->reportFile, "<h3>%d.%d. <a name=\"con_", nipper->sectionCount, nipper->subSectionCount);
			else if (section == section_appendix)
				fprintf(nipper->reportFile, "<h3>%d.%d. <a name=\"app_", nipper->sectionCount, nipper->subSectionCount);
			else if (section == section_about)
				fprintf(nipper->reportFile, "<h3>%d.%d. <a name=\"abt_", nipper->sectionCount, nipper->subSectionCount);
			else
				fprintf(nipper->reportFile, "<h3>%d.%d. <a name=\"", nipper->sectionCount, nipper->subSectionCount);
			for (textLoop = 0; textLoop < strlen(theText); textLoop++)
			{
				if (theText[textLoop] != ' ')
					fprintf(nipper->reportFile, "%c", theText[textLoop]);
			}
			if ((section == section_main_sec) || (section == section_contents) || (section == section_main_con) || (section == section_main_app) || (section == section_main))
				fprintf(nipper->reportFile, "\">%s</a></h2>\n", theText);
			else
				fprintf(nipper->reportFile, "\">%s</a></h3>\n", theText);
			break;

		case output_xml:
			if ((section == section_main) || (section == section_contents))
				fprintf(nipper->reportFile, " <section type=\"report\"");
			else if (section == section_main_sec)
				fprintf(nipper->reportFile, " <section type=\"security\"");
			else if (section == section_main_con)
				fprintf(nipper->reportFile, " <section type=\"configuration\"");
			else if (section == section_main_app)
				fprintf(nipper->reportFile, " <section type=\"appendix\"");
			else if (section == section_main_abt)
				fprintf(nipper->reportFile, " <section type=\"about\"");
			else if (section == section_about)
				fprintf(nipper->reportFile, " <subsection type=\"about\"");
			else if (section == section_security)
			{
				fprintf(nipper->reportFile, "  <subsection type=\"security\"");
			}
			else if (section == section_config)
				fprintf(nipper->reportFile, "  <subsection type=\"configuration\"");
			else if (section == section_appendix)
				fprintf(nipper->reportFile, "  <subsection type=\"appendix\"");

			fprintf(nipper->reportFile, " title=\"%s\" ref=\"", theText);
			for (textLoop = 0; textLoop < strlen(theText); textLoop++)
			{
				if (theText[textLoop] != ' ')
					fprintf(nipper->reportFile, "%c", theText[textLoop]);
			}
			fprintf(nipper->reportFile, "%d%s\">\n", section + 48, nipper->hostname);
			break;

		case output_text:
			if ((section == section_main_sec) || (section == section_main_con) || (section == section_main_abt) || (section == section_main_app))
				tempChar = '~';
			else
				tempChar = '-';
			length = strlen(theText);
			if (section == section_contents)
				fprintf(nipper->reportFile, "%s\n", theText);
			else if ((section == section_main_sec) || (section == section_main_con) || (section == section_main_abt) || (section == section_main_app) || (section == section_main))
			{
				fprintf(nipper->reportFile, "%d. %s\n", nipper->sectionCount, theText);
				length += 3;
				if (nipper->sectionCount > 9)
					length++;
				if (nipper->sectionCount > 99)
					length++;
			}
			else
			{
				fprintf(nipper->reportFile, "%d.%d. %s\n", nipper->sectionCount, nipper->subSectionCount, theText);
				length += 5;
				if (nipper->sectionCount > 9)
					length++;
				if (nipper->sectionCount > 99)
					length++;
				if (nipper->subSectionCount > 9)
					length++;
				if (nipper->subSectionCount > 99)
					length++;
			}
			for (textLoop = 0; textLoop < length; textLoop++)
			{
				fprintf(nipper->reportFile, "%c", tempChar);
			}
			fprintf(nipper->reportFile, "\n\n");
			break;
	}
}


// Report End of Section
// ---------------------
// This routine outputs an end of section.
void output_endsection(struct nipperConfig *nipper, int reportSection)
{
	// Format...
	switch (nipper->outputFormat)
	{
		case output_xml:
			switch (reportSection)
			{
				case section_obs:
				case section_imp:
				case section_ease:
				case section_rec:
					fprintf(nipper->reportFile, "   </textsection>\n");
					break;

				case subsection_end:
					fprintf(nipper->reportFile, "  </subsection>\n");
					break;

				case section_end:
					fprintf(nipper->reportFile, " </section>\n");
					break;
			}
			break;
	}
}


// Report Text Parsing and Output
// ------------------------------
// This code outputs text to the report. The text could be a security report
// paragraph or just plain text. It will use the embeded codes to format the
// text for each output type. The current codes include:
//     COMPANY           - Company name
//     DEVICENAME        - The device name
//     ABBREV ^          - Abbreviation
//     COMMAND ^         - A command
//     CMDOPTION ^       - A command option
//     CMDREQUIRE ^      - A command requirement
//     CMDOR             - Command alternatives
//     CMDUSER ^         - User supplied command entry
//     NEWLINE           - A newline
//                       - The data parameter is:
//     SINGULA ^         -    * equal to 1
//     PLAURAL ^         -    * more than 1
//     POSITIVE ^        -    * positive
//     NEGATIVE ^        -    * negative
//     ZERO ^            -    * zero
//     TABLEREF          - Insert Table Reference
//     NUMBER            - Insert Number (provided by data)
//     NONEWPARA         - No new paragraph at the end
//     NEWPARA           - Insert New Paragraph
//     DEVICETYPE        - Insert device type
//     DEVICEVERSION     - Device version details
//     NOTEXTSTART       - XML Only - Do not start with a <text>
//     DATE              - Insert the current date
//     INDENT            - Text indentation
//     TABLEITEM ^       - Text is used in a table cell
// Each code is encolsed in * and codes that have a start and end [^} use the
// same code with a - prepending it.
void output_parseText(const char *theText, struct nipperConfig *nipper, int reportSection, int rating, int data, int reference)
{
	// Variables...
	int offset = 0;
	int textLength = 0;
	int abbreviationStatus = 0;
	char *charPointer;
	char tempString[nipper->maxSize];
	int dayType;
	time_t tempTime;
	const char *abbreviation;

	// Section...
	if (strncmp(theText, "*TABLEITEM*", 11) != 0)
	{
		switch (reportSection)
		{
			case section_obs:
				switch (nipper->outputFormat)
				{
					case output_xml:
						fprintf(nipper->reportFile, "   <textsection type=\"observation\">\n    <text>");
						break;
					case output_html:
						fprintf(nipper->reportFile, "<b>Observation:</b> ");
						break;
					case output_latex:
					case output_text:
						fprintf(nipper->reportFile, "OBSERVATION: ");
						break;
				}
				break;
	
			case section_imp:
				switch (nipper->outputFormat)
				{
					case output_xml:
						fprintf(nipper->reportFile, "   <textsection type=\"impact\" rate=\"");
						switch (rating)
						{
							case rate_low:
								fprintf(nipper->reportFile, "low");
								break;
							case rate_lowmed:
								fprintf(nipper->reportFile, "lowmed");
								break;
							case rate_med:
								fprintf(nipper->reportFile, "med");
								break;
							case rate_medhigh:
								fprintf(nipper->reportFile, "medhigh");
								break;
							case rate_high:
								fprintf(nipper->reportFile, "high");
								break;
						}
						fprintf(nipper->reportFile, "\">\n    <text>");
						break;
					case output_html:
						fprintf(nipper->reportFile, "<b>Impact:</b> ");
						break;
					case output_latex:
					case output_text:
						fprintf(nipper->reportFile, "IMPACT: ");
						break;
				}
				break;
	
			case section_ease:
				switch (nipper->outputFormat)
				{
					case output_xml:
						fprintf(nipper->reportFile, "   <textsection type=\"ease\" rate=\"");
						switch (rating)
						{
							case rate_noease:
								fprintf(nipper->reportFile, "noease ");
								break;
							case rate_trivial:
								fprintf(nipper->reportFile, "trivial");
								break;
							case rate_moderate:
								fprintf(nipper->reportFile, "moderate");
								break;
							case rate_difficult:
								fprintf(nipper->reportFile, "difficult");
								break;
						}
						fprintf(nipper->reportFile, "\">\n    <text>");
						break;
					case output_html:
						if (rating == rate_noease)
							fprintf(nipper->reportFile, "<b>Ease:</b> N/A");
						else
							fprintf(nipper->reportFile, "<b>Ease:</b> ");
						break;
					case output_latex:
					case output_text:
						if (rating == rate_noease)
							fprintf(nipper->reportFile, "EASE: N/A");
						else
							fprintf(nipper->reportFile, "EASE: ");
						break;
				}
				break;
	
			case section_rec:
				switch (nipper->outputFormat)
				{
					case output_html:
						fprintf(nipper->reportFile, "<b>Recommendation:</b> ");
						break;
					case output_xml:
						fprintf(nipper->reportFile, "   <textsection type=\"recommendation\">\n    <text>");
						break;
					case output_latex:
					case output_text:
						fprintf(nipper->reportFile, "RECOMMENDATION: ");
						break;
				}
				break;
	
			default:
				switch (nipper->outputFormat)
				{
					case output_xml:
						if (strncmp(theText, "*NOTEXTSTART*", 13) != 0)
							fprintf(nipper->reportFile, "    <text>");
						break;
				}
				break;
		}
	}

	// Parse the text
	textLength = strlen(theText);
	for (offset = 0; offset < textLength; offset++)
	{
		// Init...
		memset(tempString, 0, sizeof(tempString));

		// Company name...
		if (strncmp("*COMPANY*", theText + offset, 9) == 0)
		{
			switch (nipper->outputFormat)
			{
				default:
					fprintf(nipper->reportFile, "%s", nipper->companyName);
					break;
			}
			offset += 8;
		}

		// Table Item...
		else if (strncmp("*TABLEITEM*", theText + offset, 11) == 0)
			offset += 10;
		else if (strncmp("*-TABLEITEM*", theText + offset, 12) == 0)
			return;

		// Device name...
		else if (strncmp("*DEVICENAME*", theText + offset, 12) == 0)
		{
			switch (nipper->outputFormat)
			{
				default:
					fprintf(nipper->reportFile, "%s", nipper->hostname);
					break;
			}
			offset += 11;
		}

		// Device type...
		else if (strncmp("*DEVICETYPE*", theText + offset, 12) == 0)
		{
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
				case type_passport:
					fprintf(nipper->reportFile, "Bay Networks Accelar");
					break;
				case type_bayaccelar:
					fprintf(nipper->reportFile, "Nortel Passport");
					break;
				case type_asa_firewall:
					fprintf(nipper->reportFile, "Cisco ");
					strcpy(tempString, "ASA");
					break;
				case type_fwsm_firewall:
					fprintf(nipper->reportFile, "Cisco ");
					strcpy(tempString, "FWSM");
					break;
				case type_pix_firewall:
					fprintf(nipper->reportFile, "Cisco ");
					strcpy(tempString, "PIX");
					break;
				case type_css_filter:
					fprintf(nipper->reportFile, "Cisco ");
					abbreviation = getAbbreviation("CSS");
					if (nipper->outputFormat == output_xml)
					{
						if (addAbbreviation("CSS", true) == abbrev_expand)
							fprintf(nipper->reportFile, "<abbrev expand=\"true\" long=\"%s\" short=\"CSS\" />", abbreviation);
						else
							fprintf(nipper->reportFile, "<abbrev expand=\"false\" long=\"%s\" short=\"CSS\" />", abbreviation);
					}
					else
					{
						if (addAbbreviation("CSS", true) == abbrev_expand)
							fprintf(nipper->reportFile, "%s (CSS)", abbreviation);
						else
							fprintf(nipper->reportFile, "CSS");
					}
					break;
				case type_sos_firewall:
					fprintf(nipper->reportFile, "Juniper NetScreen Firewall");
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
			switch (nipper->deviceType)
			{
				case type_asa_firewall:
				case type_pix_firewall:
				case type_fwsm_firewall:
					abbreviation = getAbbreviation(&tempString[0]);
					if (nipper->outputFormat == output_xml)
					{
						if (addAbbreviation(tempString, true) == abbrev_expand)
							fprintf(nipper->reportFile, "<abbrev expand=\"true\" long=\"%s\" short=\"%s\" /> Firewall", abbreviation, tempString);
						else
							fprintf(nipper->reportFile, "<abbrev expand=\"false\" long=\"%s\" short=\"%s\" /> Firewall", abbreviation, tempString);
					}
					else
					{
						if (addAbbreviation(tempString, true) == abbrev_expand)
							fprintf(nipper->reportFile, "%s (%s) Firewall", abbreviation, tempString);
						else
							fprintf(nipper->reportFile, "%s Firewall", tempString);
					}
					break;
			}
			offset += 11;
		}

		// Device type...
		else if (strncmp("*DEVICEVERSION*", theText + offset, 15) == 0)
		{
			switch (nipper->deviceType)
			{
				case type_ios_switch:
				case type_ios_router:
				case type_ios_catalyst:
					strcpy(tempString, "IOS");
					break;
				case type_nmp_catalyst:
					strcpy(tempString, "NMP");
					break;
				case type_cos_catalyst:
					strcpy(tempString, "CatOS");
					break;
				case type_asa_firewall:
					strcpy(tempString, "ASA");
					break;
				case type_fwsm_firewall:
					strcpy(tempString, "FWSM");
					break;
				case type_pix_firewall:
					strcpy(tempString, "PIX");
					break;
				case type_css_filter:
					strcpy(tempString, "CSS");
					break;
			}
			switch (nipper->deviceType)
			{
				case type_ios_switch:
				case type_ios_router:
				case type_ios_catalyst:
				case type_nmp_catalyst:
				case type_cos_catalyst:
				case type_asa_firewall:
				case type_fwsm_firewall:
				case type_pix_firewall:
				case type_css_filter:
					abbreviation = getAbbreviation(&tempString[0]);
					if (nipper->outputFormat == output_xml)
					{
						if (addAbbreviation(tempString, true) == abbrev_expand)
							fprintf(nipper->reportFile, "<abbrev expand=\"true\" long=\"%s\" short=\"%s\" /> version %s", abbreviation, tempString, nipper->version);
						else
							fprintf(nipper->reportFile, "<abbrev expand=\"false\" long=\"%s\" short=\"%s\" /> version %s", abbreviation, tempString, nipper->version);
					}
					else
					{
						if (addAbbreviation(tempString, true) == abbrev_expand)
							fprintf(nipper->reportFile, "%s (%s) version %s", abbreviation, tempString, nipper->version);
						else
							fprintf(nipper->reportFile, "%s version %s", tempString, nipper->version);
					}
					break;
				case type_passport:
					fprintf(nipper->reportFile, "Passport software version %s", nipper->version);
					break;
				case type_bayaccelar:
					fprintf(nipper->reportFile, "Accelar software version %s", nipper->version);
					break;
				case type_fw1_firewall:
					fprintf(nipper->reportFile, "Firewall-1 version %s", nipper->version);
					break;
				case type_nokiaip:
					fprintf(nipper->reportFile, "Nokia IP version %s", nipper->version);
					break;
				case type_sonicwall:
					fprintf(nipper->reportFile, "SonicOS version %s", nipper->version);
					break;
			}
			offset += 14;
		}

		// Newline...
		else if (strncmp("*NEWLINE*", theText + offset, 9) == 0)
		{
			switch (nipper->outputFormat)
			{
				case output_html:
					fprintf(nipper->reportFile, "&nbsp;<br>\n");
					break;
				default:
					fprintf(nipper->reportFile, "\n");
					break;
			}
			offset += 8;
		}

		// New paragraph...
		else if (strncmp("*NEWPARA*", theText + offset, 9) == 0)
		{
			switch (nipper->outputFormat)
			{
				case output_html:
					fprintf(nipper->reportFile, "<br>\n&nbsp;<br>\n");
					break;
				case output_xml:
					fprintf(nipper->reportFile, "</text>\n    <text>");
					break;
				default:
					fprintf(nipper->reportFile, "\n\n");
					break;
			}
			offset += 8;
		}

		// Indentation...
		else if (strncmp("*INDENT*", theText + offset, 8) == 0)
		{
			switch (nipper->outputFormat)
			{
				case output_html:
					fprintf(nipper->reportFile, "&nbsp;&nbsp;&nbsp;&nbsp;");
					break;
				default:
					fprintf(nipper->reportFile, "    ");
					break;
			}
			offset += 7;
		}

		// Singula...
		else if (strncmp("*SINGULA*", theText + offset, 9) == 0)
		{
			// If not singula, skip the entire section
			if (data != 1)
			{
				charPointer = strstr(theText + offset, "*-SINGULA*");
				if (charPointer != 0)
					offset = charPointer - theText + 9;
			}
			else
				offset += 8;
		}
		else if (strncmp("*-SINGULA*", theText + offset, 10) == 0)
			offset += 9;

		// Plaural...
		else if (strncmp("*PLAURAL*", theText + offset, 9) == 0)
		{
			// If not plaural, skip the entire section
			if (data < 2)
			{
				charPointer = strstr(theText + offset, "*-PLAURAL*");
				if (charPointer != 0)
					offset = charPointer - theText + 9;
			}
			else
				offset += 8;
		}
		else if (strncmp("*-PLAURAL*", theText + offset, 10) == 0)
			offset += 9;

		// Positive...
		else if (strncmp("*POSITIVE*", theText + offset, 10) == 0)
		{
			// If not positive, skip the entire section
			if (data < 1)
			{
				charPointer = strstr(theText + offset, "*-POSITIVE*");
				if (charPointer != 0)
					offset = charPointer - theText + 10;
			}
			else
				offset += 9;
		}
		else if (strncmp("*-POSITIVE*", theText + offset, 11) == 0)
			offset += 10;

		// Negative...
		else if (strncmp("*NEGATIVE*", theText + offset, 10) == 0)
		{
			// If not negative, skip the entire section
			if (data >= 0)
			{
				charPointer = strstr(theText + offset, "*-NEGATIVE*");
				if (charPointer != 0)
					offset = charPointer - theText + 10;
			}
			else
				offset += 9;
		}
		else if (strncmp("*-NEGATIVE*", theText + offset, 11) == 0)
			offset += 10;

		// Zero...
		else if (strncmp("*ZERO*", theText + offset, 6) == 0)
		{
			// If not zero, skip the entire section
			if (data != 0)
			{
				charPointer = strstr(theText + offset, "*-ZERO*");
				if (charPointer != 0)
					offset = charPointer - theText + 6;
			}
			else
				offset += 5;
		}
		else if (strncmp("*-ZERO*", theText + offset, 7) == 0)
			offset += 6;

		// Date...
		else if (strncmp("*DATE*", theText + offset, 6) == 0)
		{
			tempTime = time(NULL);

			// Day of week...
			strftime(tempString, nipper->maxSize, "%A", localtime(&tempTime));
			fprintf(nipper->reportFile, "%s ", tempString);

			// Day of month...
			strftime(tempString, nipper->maxSize, "%d", localtime(&tempTime));
			dayType = tempString[1] - 48;
			if (tempString[0] == '0')
			{
				tempString[0] = tempString[1];
				tempString[1] = 0;
			}
			switch (dayType)
			{
				case 1:
					fprintf(nipper->reportFile, "%sst ", tempString);
					break;
				case 2:
					fprintf(nipper->reportFile, "%snd ", tempString);
					break;
				case 3:
					fprintf(nipper->reportFile, "%srd ", tempString);
					break;
				default:
					fprintf(nipper->reportFile, "%sth ", tempString);
					break;
			}

			// Month + Year
			strftime(tempString, nipper->maxSize, "%B %Y", localtime(&tempTime));
			fprintf(nipper->reportFile, "%s", tempString);
			offset += 5;
		}

		// Command...
		else if (strncmp("*COMMAND*", theText + offset, 9) == 0)
		{
			switch (nipper->outputFormat)
			{
				case output_html:
					fprintf(nipper->reportFile, "<div class=\"command\">");
					break;
				case output_latex:
					fprintf(nipper->reportFile, "\\texttt{");
					break;
				case output_xml:
					fprintf(nipper->reportFile, "<command>");
					break;
				default:
					fprintf(nipper->reportFile, "\"");
					break;
			}
			offset += 8;
		}
		else if (strncmp("*-COMMAND*", theText + offset, 10) == 0)
		{
			switch (nipper->outputFormat)
			{
				case output_html:
					fprintf(nipper->reportFile, "</div>");
					break;
				case output_latex:
					fprintf(nipper->reportFile, "}");
					break;
				case output_xml:
					fprintf(nipper->reportFile, "</command>");
					break;
				default:
					fprintf(nipper->reportFile, "\"");
					break;
			}
			offset += 9;
		}

		// Command Requirement...
		else if (strncmp("*CMDREQUIRE*", theText + offset, 12) == 0)
		{
			switch (nipper->outputFormat)
			{
				case output_xml:
					fprintf(nipper->reportFile, "<cmdrequire>");
					break;
				default:
					fprintf(nipper->reportFile, "{");
					break;
			}
			offset += 11;
		}
		else if (strncmp("*-CMDREQUIRE*", theText + offset, 13) == 0)
		{
			switch (nipper->outputFormat)
			{
				case output_xml:
					fprintf(nipper->reportFile, "</cmdrequire>");
					break;
				default:
					fprintf(nipper->reportFile, "}");
					break;
			}
			offset += 12;
		}

		// Command Option...
		else if (strncmp("*CMDOPTION*", theText + offset, 11) == 0)
		{
			switch (nipper->outputFormat)
			{
				case output_xml:
					fprintf(nipper->reportFile, "<cmdoption>");
					break;
				default:
					fprintf(nipper->reportFile, "[");
					break;
			}
			offset += 10;
		}
		else if (strncmp("*-CMDOPTION*", theText + offset, 12) == 0)
		{
			switch (nipper->outputFormat)
			{
				case output_xml:
					fprintf(nipper->reportFile, "</cmdoption>");
					break;
				default:
					fprintf(nipper->reportFile, "]");
					break;
			}
			offset += 11;
		}

		// Command Alternative...
		else if (strncmp("*CMDOR*", theText + offset, 7) == 0)
		{
			switch (nipper->outputFormat)
			{
				default:
					fprintf(nipper->reportFile, "|");
					break;
			}
			offset += 6;
		}

		// Command Text...
		else if (strncmp("*CMDUSER*", theText + offset, 9) == 0)
		{
			switch (nipper->outputFormat)
			{
				case output_html:
					fprintf(nipper->reportFile, "<i>");
					break;
			}
			offset += 8;
		}
		else if (strncmp("*-CMDUSER*", theText + offset, 10) == 0)
		{
			switch (nipper->outputFormat)
			{
				case output_html:
					fprintf(nipper->reportFile, "</i>");
					break;
			}
			offset += 9;
		}

		// Table Reference...
		else if (strncmp("*TABLEREF*", theText + offset, 10) == 0)
		{
			switch (nipper->outputFormat)
			{
				case output_xml:
					fprintf(nipper->reportFile, "<reference name=\"TABLEREF%d\"/>", reference);
					break;
				default:
					fprintf(nipper->reportFile, "%d", reference);
					break;
			}
			offset += 9;
		}

		// Number...
		else if (strncmp("*NUMBER*", theText + offset, 8) == 0)
		{
			numToWord(nipper->reportFile, data);
			offset += 7;
		}

		// No XML Text start...
		else if (strncmp("*NOTEXTSTART*", theText + offset, 13) == 0)
			offset += 12;

		// Abbreviation...
		else if (strncmp("*ABBREV*", theText + offset, 8) == 0)
		{
			// Get abbreviation...
			offset += 8;
			charPointer = strstr(theText + offset, "*-ABBREV*");
			if (charPointer != 0)
			{
				strncpy(tempString, theText + offset, charPointer - theText - offset);
				offset = charPointer - theText + 8;
				abbreviationStatus = addAbbreviation(&tempString[0], true);

				// Process
				switch (nipper->outputFormat)
				{
					case output_xml:
						abbreviation = getAbbreviation(&tempString[0]);
						if (abbreviationStatus == abbrev_expand)
							fprintf(nipper->reportFile, "<abbrev expand=\"true\" long=\"%s\" short=\"%s\" />", abbreviation, tempString);
						else
							fprintf(nipper->reportFile, "<abbrev expand=\"false\" long=\"%s\" short=\"%s\" />", abbreviation, tempString);
						break;
					default:
						switch (abbreviationStatus)
						{
							case abbrev_expand:
								abbreviation = getAbbreviation(&tempString[0]);
								// If ACLs or ACEs
								if (strcmp(tempString, "ACLs") == 0)
									sprintf(tempString, "ACL");
								else if (strcmp(tempString, "ACEs") == 0)
									sprintf(tempString, "ACE");
								if (abbreviation != 0)
									fprintf(nipper->reportFile, "%s (%s)", abbreviation, tempString);
								else
									fprintf(nipper->reportFile, "%s", tempString);
								break;
							default:
								fprintf(nipper->reportFile, "%s", tempString);
								break;
						}
						break;
				}
			}
		}
		else if (strncmp("*-ABBREV*", theText + offset, 9) == 0)
		{
			offset += 8;
		}

		// No new paragraph at end
		else if (strncmp("*NONEWPARA*", theText + offset, 11) == 0)
			return;

		// Output text
		else
		{
			fprintf(nipper->reportFile, "%c", theText[offset]);
		}
	}

	// End text
	switch (nipper->outputFormat)
	{
		case output_xml:
			fprintf(nipper->reportFile, "</text>\n");
			break;
	}
	output_newPara(nipper);
}


// Generate Appendix
// -----------------
// This code generates the appendix section.
void generateAppendix(struct nipperConfig *nipper)
{
	// Variables
	int tempInt = 0;
	struct abbrev *abbrevPointer = 0;
	struct ports *portPointer = 0;

	// Check that there is something to show
	if ((nipper->abs == true) || (nipper->commonPorts == true) || (nipper->loggingLevels == true) || (nipper->glossary == true) || (nipper->nipperVersion == true))
	{

		// Display Section Start
		output_parseTitle(appendix_title, nipper, section_main_app);

		// Abbreviations
		abbrevPointer = &ab_append;
		while ((abbrevPointer->next != 0) && (abbrevPointer->add == false))
			abbrevPointer = abbrevPointer->next;
		if ((nipper->abs == true) && (abbrevPointer->add == true))
		{
			output_parseTitle(appendix_abbrev_title, nipper, section_appendix);

			// Display Start of abbreviations
			switch (nipper->outputFormat)
			{
				case output_html:
					fprintf(nipper->reportFile, "<table class=\"table\">\n<tbody>\n");
					break;
				case output_xml:
					fprintf(nipper->reportFile, "   <abbreviations>\n");
					break;
				case output_text:
					fprintf(nipper->reportFile, "-------------\nAbbreviations\n-------------\n");
					break;
				case output_latex:
					fprintf(nipper->reportFile, "\\begin{quote}\n\\begin{tabular}{ll}\n");
					break;
			}

			// Display Abbreviations
			while (abbrevPointer != 0)
			{
				if (abbrevPointer->add == true)
				{
					switch (nipper->outputFormat)
					{
						case output_html:
							fprintf(nipper->reportFile, "<tr><td><b>%s</b></td><td>%s</td></tr>\n", abbrevPointer->ab, abbrevPointer->desc);
							break;
						case output_xml:
							fprintf(nipper->reportFile, "    <abbreviation short=\"%s\">%s</abbreviation>\n", abbrevPointer->ab, abbrevPointer->desc);
							break;
						case output_text:
							fprintf(nipper->reportFile, "  %s", abbrevPointer->ab);
							if (strlen(abbrevPointer->ab) < 10)
								tempInt = 10 - strlen(abbrevPointer->ab);
							else
								tempInt = 1;
							while (tempInt != 0)
							{
								fprintf(nipper->reportFile, " ");
								tempInt--;
							}
							fprintf(nipper->reportFile, ": %s\n", abbrevPointer->desc);
							break;
						case output_latex:
							fprintf(nipper->reportFile, "%s&%s\\\\\n", abbrevPointer->ab, abbrevPointer->desc);
							break;
					}
				}
				abbrevPointer = abbrevPointer->next;
			}

			// Display End of Abbreviations
			switch (nipper->outputFormat)
			{
				case output_html:
					fprintf(nipper->reportFile, "</tbody>\n</table>\n&nbsp;<br>\n\n");
					break;
				case output_xml:
					fprintf(nipper->reportFile, "   </abbreviations>\n");
					break;
				case output_text:
					fprintf(nipper->reportFile, "-------------\n\n");
					break;
				case output_latex:
					fprintf(nipper->reportFile, "\\end{tabular}\n\\end{quote}\n\n");
					break;
			}

			// Output the end of the abbreviations section
			output_endsection(nipper, subsection_end);
		}

		// Common Ports
		portPointer = &ap_port;
		while ((portPointer->next != 0) && (portPointer->add == false))
			portPointer = portPointer->next;
		if ((nipper->commonPorts == true) && (portPointer->add == true))
		{
			output_parseTitle(appendix_ports_title, nipper, section_appendix);

			// Display Ports
			output_table(nipper, true, appendix_ports_table, &appendix_ports_heading);
			while (portPointer != 0)
			{
				if (portPointer->add == true)
					fprintf(nipper->reportFile, "%s%s%s%d%s", nipper->tablerow_start, portPointer->text, nipper->tablerow_mid, portPointer->port, nipper->tablerow_end);
				portPointer = portPointer->next;
			}
			output_table(nipper, false, appendix_ports_table, &appendix_ports_heading);

			// Output the end of the ports section
			output_endsection(nipper, subsection_end);
		}

		// Logging Levels
		if (nipper->loggingLevels == true)
		{
			output_parseTitle(appendix_logging_title, nipper, section_appendix);
			output_table(nipper, true, appendix_logging_table, &appendix_logging_heading);
			fprintf(nipper->reportFile, "%s0%sEmergencies%sSystem is unstable%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%s1%sAlerts%sImmediate action is required%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%s2%sCritical%sCritical conditions%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%s3%sErrors%sError conditions%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%s4%sWarnings%sWarning conditions%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%s5%sNotifications%sSignificant conditions%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%s6%sInformational%sInformational messages%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%s7%sDebugging%sDebugging messages%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			output_table(nipper, false, appendix_logging_table, &appendix_logging_heading);
			output_endsection(nipper, subsection_end);
		}

		// Time Zones
		if (nipper->timeZones == true)
		{
			output_parseTitle(appendix_timezones_title, nipper, section_appendix);
			output_table(nipper, true, appendix_timezones_table, &appendix_timezones_heading);
			fprintf(nipper->reportFile, "%sAustralia%sCST%sCentral Standard Time%s+9.5 hours%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sAustralia%sEST%sEastern Standard/Summer Time%s+10 hours%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sAustralia%sWST%sWestern Standard Time%s+8 hours%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sEurope%sBST%sBritish Summer Time%s+1 hour%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sEurope%sCEST%sCentral Europe Summer Time%s+2 hours%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sEurope%sCET%sCentral Europe Time%s+1 hour%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sEurope%sEEST%sEastern Europe Summer Time%s+3 hours%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sEurope%sEST%sEastern Europe Time%s+2 hours%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sEurope%sGMT%sGreenwich Mean Time%s %s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sEurope%sIST%sIrish Summer Time%s+1 hour%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sEurope%sMSK%sMoscow Time%s+3 hours%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sEurope%sWEST%sWestern Europe Summer Time%s+1 hour%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sEurope%sWET%sWestern Europe Time%s+1 hour%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sUSA and Canada%sADT%sAtlantic Daylight Time%s-3 hours%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sUSA and Canada%sAKDT%sAlaska Standard Daylight Saving Time%s-8 hours%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sUSA and Canada%sAKST%sAlaska Standard Time%s-9 hours%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sUSA and Canada%sAST%sAtlantic Standard Time%s-4 hours%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sUSA and Canada%sCDT%sCentral Daylight Saving Time%s-5 hours%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sUSA and Canada%sCST%sCentral Standard Time%s-6 hours%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sUSA and Canada%sEDT%sEastern Daylight Time%s-4 hours%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sUSA and Canada%sEST%sEastern Standard Time%s-5 hours%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sUSA and Canada%sHST%sHawaiian Standard Time%s-10 hours%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sUSA and Canada%sMDT%sMountain Daylight Time%s-6 hours%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sUSA and Canada%sMST%sMountain Standard Time%s-7 hours%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sUSA and Canada%sPDT%sPacific Daylight Time%s-7 hours%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sUSA and Canada%sPST%sPacific Standard Time%s-3 hours%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
			output_table(nipper, false, appendix_timezones_table, &appendix_timezones_heading);
			output_endsection(nipper, subsection_end);
		}

		// Nipper Version Details
		if (nipper->nipperVersion == true)
		{
			output_parseTitle(appendix_version_title, nipper, section_appendix);
			output_parseText(appendix_version_desc1, nipper, section_none, rate_none, 0, 0);
			fprintf(nipper->reportFile, "%s", program_version);
			output_parseText(appendix_version_desc2, nipper, section_none, rate_none, 0, 0);
			output_endsection(nipper, subsection_end);
		}

		// Output section end
		output_endsection(nipper, section_end);
	}
}

// Abbreviation Contents
// ---------------------
// This code inserts abbreviation contents
void output_abbrevContents(struct nipperConfig *nipper)
{
	if ((nipper->appendix == true) && ((nipper->abs == true) || (nipper->commonPorts == true) || (nipper->loggingLevels == true) || (nipper->glossary == true) || (nipper->nipperVersion == true)))
	{
		output_parseSectionIndex(appendix_title, nipper);
	
		// Abbreviations
		if (nipper->abs == true)
			output_parseIndex(appendix_abbrev_title, nipper, section_appendix);
	
		// Common Ports
		if (nipper->commonPorts == true)
			output_parseIndex(appendix_ports_title, nipper, section_appendix);
	
		// Logging
		if (nipper->loggingLevels == true)
			output_parseIndex(appendix_logging_title, nipper, section_appendix);
	
		// Time Zones
		if (nipper->timeZones == true)
			output_parseIndex(appendix_timezones_title, nipper, section_appendix);

		// Nipper Version
		if (nipper->nipperVersion == true)
			output_parseIndex(appendix_version_title, nipper, section_appendix);
	}

	// End of security index
	switch (nipper->outputFormat)
	{
		case output_html:
			fprintf(nipper->reportFile, "</ul><br>\n");
			break;
		case output_text:
			fprintf(nipper->reportFile, "\n\n");
			break;
	}
}


// Add an item to a heading
struct tableHeading *newListItem(struct tableHeading *list, const char *text)
{
	// Variables...
	struct tableHeading *listPointer;

	// If first one...
	if (list == 0)
		listPointer = malloc(sizeof(struct tableHeading));
	else
	{
		listPointer = list;
		while (listPointer->next != 0)
			listPointer = listPointer->next;
		listPointer->next = malloc(sizeof(struct tableHeading));
		listPointer = listPointer->next;
	}

	// Init...
	memset(listPointer, 0 , sizeof(struct tableHeading));
	listPointer->password = false;
	listPointer->width = 1;
	listPointer->heading = text;

	// Return...
	if (list == 0)
		return listPointer;
	else
		return list;
}


// Add Report Section
void addReportSection(struct nipperConfig *nipper, int section, const char *sectionTitle, const char *shortConText, const char *shortRecText, int overall, int impact, int ease, int rec, void (*sectionWriter)(struct nipperConfig *nipper))
{
	// Variables...
	struct reportText *reportTextPointer = 0;

	// Create new report text struct...
	if (nipper->report == 0)
	{
		nipper->report = malloc(sizeof(struct reportText));
		reportTextPointer = nipper->report;
	}
	else
	{
		reportTextPointer = nipper->report;
		while (reportTextPointer->next != 0)
			reportTextPointer = reportTextPointer->next;
		reportTextPointer->next = malloc(sizeof(struct reportText));
		reportTextPointer = reportTextPointer->next;
	}

	// Init...
	memset(reportTextPointer, 0 , sizeof(struct reportText));

	// Copy...
	reportTextPointer->section = section;
	reportTextPointer->sectionTitle = sectionTitle;
	reportTextPointer->shortConText = shortConText;
	reportTextPointer->shortRecText = shortRecText;
	reportTextPointer->scoreOverall = overall;
	reportTextPointer->scoreOverall = impact;
	reportTextPointer->scoreOverall = ease;
	reportTextPointer->scoreOverall = rec;
	reportTextPointer->writeSection = sectionWriter;
}



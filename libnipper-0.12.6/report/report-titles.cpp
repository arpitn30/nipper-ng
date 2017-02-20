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
 *      2. Any code that makes use of this library MUST display the        *
 *         returned text of the Nipper::getVersion() method. Since the     *
 *         text returned includes the version details and copyright of     *
 *         the library, the sugested place to show it would be with the    *
 *         callers "about program" information.                            *
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

// Includes...
#include "../globaldefs.h"
#include "../device/general/general.h"
#include <cstring>
#include "report.h"


string tempTitleString;
const char *Report::reportTitle()
{
	tempTitleString.assign(device->deviceMake);
	tempTitleString.append(" ");
	if (config->deviceModel != 0)
	{
		tempTitleString.append(config->deviceModel);
		tempTitleString.append(" ");
	}
	else if (device->deviceModel != 0)
	{
		tempTitleString.append(device->deviceModel);
		tempTitleString.append(" ");
	}
	tempTitleString.append(device->deviceType);
	if (config->deviceName != 0)
	{
		tempTitleString.append(" ");
		tempTitleString.append(outputFriendly(config->deviceName));
	}
	else if (device->general != 0)
	{
		tempTitleString.append(" ");
		tempTitleString.append(outputFriendly(device->general->hostname.c_str()));
	}
	if (config->includeSecurityAudit == true)
		tempTitleString.append(" Security Report");
	else
		tempTitleString.append(" Configuration Report");

	return tempTitleString.c_str();
}


void Report::writeSectionTitle(int sectionNumber, sectionEnumerator section)
{
	switch (config->reportFormat)
	{
		case Config::HTML:
			switch (section)
			{
				case Report::contentsSection:
					fprintf(outFile, "<div id=\"contents\">\n <h2>%s</h2><br>\n", i18n("Contents"));
					break;
				case Report::tableIndexSection:
					fprintf(outFile, "<div id=\"tableindex\">\n <h2>%s</h2><br>\n", i18n("Index Of Tables"));
					break;
				case Report::introductionSection:
					fprintf(outFile, "<div id=\"about\">\n <h2>%d. <a name=\"ABOUTYOURREPORTSECTION\">%s</a></h2><br>\n", sectionNumber, i18n("About Your Report"));
					break;
				case Report::securitySection:
					fprintf(outFile, "<div id=\"security\">\n <h2>%d. <a name=\"SECURITYSECTION\">%s</a></h2><br>\n", sectionNumber, i18n("Security Audit"));
					break;
				case Report::complianceSection:
					fprintf(outFile, "<div id=\"compliance\">\n <h2>%d. <a name=\"COMPLIANCESECTION\">%s</a></h2><br>\n", sectionNumber, i18n("Compliance Testing"));
					break;
				case Report::configurationSection:
					fprintf(outFile, "<div id=\"configuration\">\n <h2>%d. <a name=\"CONFIGURATIONSECTION\">%s</a></h2><br>\n", sectionNumber, i18n("Device Configuration"));
					break;
				default:
					fprintf(outFile, "<div id=\"appendix\">\n <h2>%d. <a name=\"APPENDIXSECTION\">%s</a></h2><br>\n", sectionNumber, i18n("Appendix"));
					break;
			}
			break;

		case Config::XML:
			switch (section)
			{
				case Report::contentsSection:
					fprintf(outFile, "<section type=\"contents\" title=\"%s\" ref=\"CONTENTSSECTION\">\n", i18n("Contents"));
					break;
				case Report::tableIndexSection:
					fprintf(outFile, "<section type=\"tableindex\" title=\"%s\" ref=\"TABLEINDEXSECTION\">\n", i18n("Index Of Tables"));
					break;
				case Report::introductionSection:
					fprintf(outFile, " <section type=\"about\" title=\"%s\" ref=\"ABOUTYOURREPORTSECTION\">\n", i18n("About Your Report"));
					break;
				case Report::securitySection:
					fprintf(outFile, " <section type=\"security\" title=\"%s\" ref=\"SECURITYSECTION\">\n", i18n("Security Audit"));
					break;
				case Report::complianceSection:
					fprintf(outFile, " <section type=\"compliance\" title=\"%s\" ref=\"COMPLIANCESECTION\">\n", i18n("Compliance Testing"));
					break;
				case Report::configurationSection:
					fprintf(outFile, " <section type=\"configuration\" title=\"%s\" ref=\"CONFIGURATIONSECTION\">\n", i18n("Device Configuration"));
					break;
				default:
					fprintf(outFile, " <section type=\"appendix\" title=\"%s\" ref=\"APPENDIXSECTION\">\n", i18n("Appendix"));
					break;
			}
			break;

		case Config::Latex:
			switch (section)
			{
				case Report::introductionSection:
					fprintf(outFile, "\\section[ABOUTYOURREPORTSECTION] {%s}\n", i18n("About Your Report"));
					break;
				case Report::securitySection:
					fprintf(outFile, "\\section[SECURITYSECTION] {%s}\n", i18n("Security Audit"));
					break;
				case Report::complianceSection:
					fprintf(outFile, "\\section[COMPLIANCESECTION] {%s}\n", i18n("Compliance Testing"));
					break;
				case Report::configurationSection:
					fprintf(outFile, "\\section[CONFIGURATIONSECTION] {%s}\n", i18n("Device Configuration"));
					break;
				default:
					fprintf(outFile, "\\section[APPENDIXSECTION] {%s}\n", i18n("Appendix"));
					break;
			}
			break;

		default:
			switch (section)
			{
				case Report::contentsSection:
					fprintf(outFile, "%s\n========\n\n", i18n("Contents"));
					break;
				case Report::tableIndexSection:
					fprintf(outFile, "%s\n===============\n\n", i18n("Index Of Tables"));
					break;
				case Report::introductionSection:
					fprintf(outFile, "%d. %s\n====================\n\n", sectionNumber, i18n("About Your Report"));
					break;
				case Report::securitySection:
					fprintf(outFile, "%d. %s\n=================\n\n", sectionNumber, i18n("Security Audit"));
					break;
				case Report::complianceSection:
					fprintf(outFile, "%d. %s\n=====================\n\n", sectionNumber, i18n("Compliance Testing"));
					break;
				case Report::configurationSection:
					fprintf(outFile, "%d. %s\n=======================\n\n", sectionNumber, i18n("Device Configuration"));
					break;
				default:
					fprintf(outFile, "%d. %s\n===========\n\n", sectionNumber, i18n("Appendix"));
					break;
			}
			break;
	}
}


int Report::writeSubSectionTitle(int sectionNumber, int subSectionNumber, const char *title, const char *reference, sectionEnumerator section)
{
	// Variables...
	int length = 0;
	int errorCode = 0;

	switch (config->reportFormat)
	{
		case Config::HTML:
			fprintf(outFile, "<div id=\"%s\">\n <h3>%d.%d. ", reference, sectionNumber, subSectionNumber);
			errorCode = writeText(title, 0, false);
			if (errorCode != 0)
				return errorCode;
			fprintf(outFile, "</h3><br>\n");
			break;

		case Config::XML:
			switch (section)
			{
				case Report::introductionSection:
					fprintf(outFile, "  <subsection type=\"about");
					break;
				case Report::securitySection:
					fprintf(outFile, "  <subsection type=\"security");
					break;
				case Report::complianceSection:
					fprintf(outFile, "  <subsection type=\"compliance");
					break;
				case Report::configurationSection:
					fprintf(outFile, "  <subsection type=\"configuration");
					break;
				default:
					fprintf(outFile, "  <subsection type=\"appendix");
					break;
			}
			fprintf(outFile, "\" title=\"");
			errorCode = writeText(title, 0, false, true);
			if (errorCode != 0)
				return errorCode;
			fprintf(outFile, "\" ref=\"%s\">\n", reference);
			break;

		case Config::Latex:
			fprintf(outFile, "\\subsection[%s] {", reference);
			errorCode = writeText(title, 0, false);
			if (errorCode != 0)
				return errorCode;
			fprintf(outFile, "}\n");
			break;

		default:
			fprintf(outFile, "%d.%d. ", sectionNumber, subSectionNumber);
			errorCode = writeText(title, 0, false);
			if (errorCode != 0)
				return errorCode;
			fprintf(outFile, "\n");
			length = strlen(title);
			length += 5;
			if (subSectionNumber > 9)
				length++;
			else if (subSectionNumber > 99)
				length += 2;
			while (length != 0)
			{
				fprintf(outFile, "~");
				length--;
			}
			fprintf(outFile, "\n\n");
			break;
	}

	return errorCode;
}


// Write the end of the report (as per writeReportStart)...
void Report::writeReportEnd()
{
	switch (config->reportFormat)
	{
		case Config::HTML:
			fprintf(outFile, "</body>\n</html>\n");
			break;
		case Config::XML:
			fprintf(outFile, "</document>\n");
			break;
		case Config::Latex:
			fprintf(outFile, "\\end{document}\n");
			break;
		default:
			break;
	}
}


void Report::writeSectionEnd()
{
	switch (config->reportFormat)
	{
		case Config::XML:
			fprintf(outFile, " </section>\n");
			break;
		case Config::HTML:
			fprintf(outFile, "</div>\n");
			break;
		default:
			break;
	}
}


void Report::writeSubSectionEnd()
{
	// Format...
	switch (config->reportFormat)
	{
		case Config::XML:
			fprintf(outFile, "  </subsection>\n");
			break;
		case Config::HTML:
			fprintf(outFile, "</div>\n");
			break;
		default:
			break;
	}
}



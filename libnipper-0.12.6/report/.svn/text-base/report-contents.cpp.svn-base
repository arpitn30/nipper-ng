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


#include "../globaldefs.h"
#include "report.h"
#include "../config.h"


int Report::writeContentsPage()
{
	// Variables...
	Device::securityIssueStruct *securityPointer = 0;
	Device::configReportStruct *configPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	int errorCode = 0;

	// If not Latex, generate the contents...
	if (config->reportFormat != Config::Latex)
	{
		// Content page title...
		writeSectionTitle(0, Report::contentsSection);

		// About your report contents...
		if (device->reportIntro != 0)
		{
			writeContentsSectionTitle(device->reportIntro->section, Report::introductionSection);
			configPointer = device->reportIntro;
			while (configPointer != 0)
			{
				errorCode = writeContentsSubSectionTitle(configPointer->section, configPointer->subsection, configPointer->title.c_str(), configPointer->reference.c_str());
				if (errorCode != 0)
					return errorCode;
				configPointer = configPointer->next;
			}
		}

		// Security audit contents...
		if ((config->includeSecurityAudit == true) && (device->securityReport != 0))
		{
			securityPointer = device->securityReport;
			writeContentsSectionTitle(securityPointer->section, Report::securitySection);
			while (securityPointer != 0)
			{
				errorCode = writeContentsSubSectionTitle(securityPointer->section, securityPointer->subsection, securityPointer->title.c_str(), securityPointer->reference.c_str());
				if (errorCode != 0)
					return errorCode;
				securityPointer = securityPointer->next;
			}
		}

		// Compliancy testing contents...
		if (config->includeComplianceCheck == true)
			writeContentsSectionTitle(0, Report::complianceSection);

		// Device Configuration contents...
		if ((config->includeConfigurationReport == true) && (device->configReport != 0))
		{
			configPointer = device->configReport;
			writeContentsSectionTitle(configPointer->section, Report::configurationSection);
			while (configPointer != 0)
			{
				errorCode = writeContentsSubSectionTitle(configPointer->section, configPointer->subsection, configPointer->title.c_str(), configPointer->reference.c_str());
				if (errorCode != 0)
					return errorCode;
				configPointer = configPointer->next;
			}
		}

		// Appendix section contents...
		if ((config->includeAppendixSection == true) && (device->appendixReport != 0))
		{
			configPointer = device->appendixReport;
			writeContentsSectionTitle(configPointer->section, Report::appendixSection);
			while (configPointer != 0)
			{
				errorCode = writeContentsSubSectionTitle(configPointer->section, configPointer->subsection, configPointer->title.c_str(), configPointer->reference.c_str());
				if (errorCode != 0)
					return errorCode;
				configPointer = configPointer->next;
			}
		}

		// End of contents section...
		writeSectionEnd();

		// Index of Tables...
		writeSectionTitle(0, Report::tableIndexSection);

		configPointer = device->reportIntro;
		while (configPointer != 0)
		{
			paragraphPointer = configPointer->config;
			while (paragraphPointer != 0)
			{
				if (paragraphPointer->table != 0)
				{
					errorCode = writeContentsTableIndex(paragraphPointer->table->number, paragraphPointer->table->title.c_str(), paragraphPointer->table->reference.c_str());
					if (errorCode != 0)
						return errorCode;
				}
				paragraphPointer = paragraphPointer->next;
			}

			configPointer = configPointer->next;
		}

		// Security Audit Tables...
		if (config->includeSecurityAudit == true)
		{
			securityPointer = device->securityReport;
			while (securityPointer != 0)
			{
				// Finding...
				paragraphPointer = securityPointer->finding;
				while (paragraphPointer != 0)
				{
					if (paragraphPointer->table != 0)
					{
						errorCode = writeContentsTableIndex(paragraphPointer->table->number, paragraphPointer->table->title.c_str(), paragraphPointer->table->reference.c_str());
						if (errorCode != 0)
							return errorCode;
					}
					paragraphPointer = paragraphPointer->next;
				}
		
				// Impact...
				paragraphPointer = securityPointer->impact;
				while (paragraphPointer != 0)
				{
					if (paragraphPointer->table != 0)
					{
						errorCode = writeContentsTableIndex(paragraphPointer->table->number, paragraphPointer->table->title.c_str(), paragraphPointer->table->reference.c_str());
						if (errorCode != 0)
							return errorCode;
					}
					paragraphPointer = paragraphPointer->next;
				}
		
				// Recommendation...
				paragraphPointer = securityPointer->recommendation;
				while (paragraphPointer != 0)
				{
					if (paragraphPointer->table != 0)
					{
						errorCode = writeContentsTableIndex(paragraphPointer->table->number, paragraphPointer->table->title.c_str(), paragraphPointer->table->reference.c_str());
						if (errorCode != 0)
							return errorCode;
					}
					paragraphPointer = paragraphPointer->next;
				}
		
				securityPointer = securityPointer->next;
			}
		}

		// Configuration report tables...
		if (config->includeConfigurationReport == true)
		{
			configPointer = device->configReport;
			while (configPointer != 0)
			{
				paragraphPointer = configPointer->config;
				while (paragraphPointer != 0)
				{
					if (paragraphPointer->table != 0)
					{
						errorCode = writeContentsTableIndex(paragraphPointer->table->number, paragraphPointer->table->title.c_str(), paragraphPointer->table->reference.c_str());
						if (errorCode != 0)
							return errorCode;
					}
					paragraphPointer = paragraphPointer->next;
				}
	
				configPointer = configPointer->next;
			}
		}

		// Appendix report tables...
		if (config->includeAppendixSection == true)
		{
			configPointer = device->appendixReport;
			while (configPointer != 0)
			{
				paragraphPointer = configPointer->config;
				while (paragraphPointer != 0)
				{
					if (paragraphPointer->table != 0)
					{
						errorCode = writeContentsTableIndex(paragraphPointer->table->number, paragraphPointer->table->title.c_str(), paragraphPointer->table->reference.c_str());
						if (errorCode != 0)
							return errorCode;
					}
					paragraphPointer = paragraphPointer->next;
				}
	
				configPointer = configPointer->next;
			}
		}

		// End of table index...
		writeSectionEnd();
	}

	return errorCode;
}


void Report::writeContentsSectionTitle(int sectionNumber, sectionEnumerator section)
{
	switch (config->reportFormat)
	{
		case Config::HTML:
			switch (section)
			{
				case Report::introductionSection:
					fprintf(outFile, "<b>%d. <a href=\"#ABOUTYOURREPORTSECTION\">%s</a></b><br>\n", sectionNumber, i18n("About Your Report"));
					break;
				case Report::securitySection:
					fprintf(outFile, "<b>%d. <a href=\"#SECURITYSECTION\">%s</a></b><br>\n", sectionNumber, i18n("Security Audit"));
					break;
				case Report::complianceSection:
					fprintf(outFile, "<b>%d. <a href=\"#COMPLIANCESECTION\">%s</a></b><br>\n", sectionNumber, i18n("Compliance Testing"));
					break;
				case Report::configurationSection:
					fprintf(outFile, "<b>%d. <a href=\"#CONFIGURATIONSECTION\">%s</a></b><br>\n", sectionNumber, i18n("Device Configuration"));
					break;
				default:
					fprintf(outFile, "<b>%d. <a href=\"#APPENDIXSECTION\">%s</a></b><br>\n", sectionNumber, i18n("Appendix"));
					break;
			}
			break;

		case Config::XML:
			switch (section)
			{
				case Report::introductionSection:
					fprintf(outFile, " <content type=\"section\" index=\"%d.\" title=\"%s\" ref=\"ABOUTYOURREPORTSECTION\" />\n", sectionNumber, i18n("About Your Report"));
					break;
				case Report::securitySection:
					fprintf(outFile, " <content type=\"section\" index=\"%d.\" title=\"%s\" ref=\"SECURITYSECTION\" />\n", sectionNumber, i18n("Security Audit"));
					break;
				case Report::complianceSection:
					fprintf(outFile, " <content type=\"section\" index=\"%d.\" title=\"%s\" ref=\"COMPLIANCESECTION\" />\n", sectionNumber, i18n("Compliance Testing"));
					break;
				case Report::configurationSection:
					fprintf(outFile, " <content type=\"section\" index=\"%d.\" title=\"%s\" ref=\"CONFIGURATIONSECTION\" />\n", sectionNumber, i18n("Device Configuration"));
					break;
				default:
					fprintf(outFile, " <content type=\"section\" index=\"%d.\" title=\"%s\" ref=\"APPENDIXSECTION\" />\n", sectionNumber, i18n("Appendix"));
					break;
			}
			break;

		default:
			switch (section)
			{
				case Report::introductionSection:
					fprintf(outFile, "%d. %s\n", sectionNumber, i18n("About Your Report"));
					break;
				case Report::securitySection:
					fprintf(outFile, "%d. %s\n", sectionNumber, i18n("Security Audit"));
					break;
				case Report::complianceSection:
					fprintf(outFile, "%d. %s\n", sectionNumber, i18n("Compliance Testing"));
					break;
				case Report::configurationSection:
					fprintf(outFile, "%d. %s\n", sectionNumber, i18n("Device Configuration"));
					break;
				default:
					fprintf(outFile, "%d. %s\n", sectionNumber, i18n("Appendix"));
					break;
			}
			break;
	}
}


int Report::writeContentsSubSectionTitle(int sectionNumber, int subSectionNumber, const char *title, const char *reference)
{
	// Variables...
	int errorCode = 0;

	switch (config->reportFormat)
	{
		case Config::HTML:
			fprintf(outFile, "&nbsp;&nbsp;&nbsp;&nbsp;%d.%d. <a href=\"#%s\">", sectionNumber, subSectionNumber, reference);
			errorCode = writeText(title, 0, false);
			if (errorCode != 0)
				return errorCode;
			fprintf(outFile, "</a><br>\n");
			break;

		case Config::XML:
			fprintf(outFile, "  <content type=\"subsection\" index=\"%d.%d\" title=\"", sectionNumber, subSectionNumber);
			errorCode = writeText(title, 0, false, true);
			if (errorCode != 0)
				return errorCode;
			fprintf(outFile, "\" ref=\"%s\" />\n", reference);
			break;

		default:
			fprintf(outFile, "  %d.%d. ", sectionNumber, subSectionNumber);
			errorCode = writeText(title, 0, false);
			if (errorCode != 0)
				return errorCode;
			fprintf(outFile, "\n");
			break;
	}

	return errorCode;
}


int Report::writeContentsTableIndex(int tableNumber, const char *title, const char *reference)
{
	// Variables...
	int errorCode = 0;

	switch (config->reportFormat)
	{
		case Config::HTML:
			fprintf(outFile, "%s %d. <a href=\"#%s\">", i18n("Table"), tableNumber, reference);
			errorCode = writeText(title, 0, false);
			if (errorCode != 0)
				return errorCode;
			fprintf(outFile, "</a><br>\n");
			break;

		case Config::XML:
			fprintf(outFile, "  <content type=\"tablereference\" index=\"%d\" title=\"", tableNumber);
			errorCode = writeText(title, 0, false, true);
			if (errorCode != 0)
				return errorCode;
			fprintf(outFile, "\" ref=\"%s\" />\n", reference);
			break;

		default:
			fprintf(outFile, "%s %d. ", i18n("Table"), tableNumber);
			errorCode = writeText(title, 0, false);
			if (errorCode != 0)
				return errorCode;
			fprintf(outFile, "\n");
			break;
	}

	return errorCode;
}


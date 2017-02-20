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
#include "report.h"


// Write a paragraph...
int Report::writeParagraph(Device::paragraphStruct *paragraph, int section, int subsection)
{
	// Variables...
	Device::paragraphStruct *paragraphPointer;
	int subsubsection = 1;
	int errorCode = 0;

	paragraphPointer = paragraph;
	while (paragraphPointer != 0)
	{

		// If paragraph title...
		if (!paragraphPointer->paragraphTitle.empty())
		{
			// Start of paragraph...
			switch (config->reportFormat)
			{
				case Config::HTML:
					fprintf(outFile, "<h5>%d.%d.%d. ", section, subsection, subsubsection);
					errorCode = writeText(paragraphPointer->paragraphTitle.c_str(), paragraphPointer, false);
					if (errorCode != 0)
						return errorCode;
					fprintf(outFile, "</h5>\n");
					break;
				case Config::XML:
					fprintf(outFile, "<subsubsectiontitle title=\"");
					errorCode = writeText(paragraphPointer->paragraphTitle.c_str(), paragraphPointer, false, true);
					if (errorCode != 0)
						return errorCode;
					fprintf(outFile, "\" />");
					break;
				case Config::Latex:
					fprintf(outFile, "\\subsubsection[] {");
					errorCode = writeText(paragraphPointer->paragraphTitle.c_str(), paragraphPointer, false, true);
					if (errorCode != 0)
						return errorCode;
					fprintf(outFile, "}\n");
					break;
				default:
					errorCode = writeText(paragraphPointer->paragraphTitle.c_str(), paragraphPointer, false);
					if (errorCode != 0)
						return errorCode;
					fprintf(outFile, ":\n");
					break;
			}
			subsubsection++;
		}

		// Start of paragraph...
		switch (config->reportFormat)
		{
			case Config::HTML:
				fprintf(outFile, "<p>");
				break;
			case Config::XML:
				fprintf(outFile, "<text>");
				break;
			default:
				break;
		}

		// Write the paragraph text...
		if (!paragraphPointer->paragraph.empty())
		{
			errorCode = writeText(paragraphPointer->paragraph.c_str(), paragraphPointer, true);
			if (errorCode != 0)
				return errorCode;
		}

		// Write bullet list...
		if (paragraphPointer->list != 0)
		{
			errorCode = writeList(paragraphPointer);
			if (errorCode != 0)
				return errorCode;
		}

		// Write table...
		if (paragraphPointer->table != 0)
		{
			errorCode = writeTable(paragraphPointer);
			if (errorCode != 0)
				return errorCode;
		}

		// End of paragraph...
		switch (config->reportFormat)
		{
			case Config::HTML:
				fprintf(outFile, "</p>\n");
				break;
			case Config::XML:
				fprintf(outFile, "</text>\n");
				break;
			default:
				fprintf(outFile, "\n\n");
				break;
		}

		paragraphPointer = paragraphPointer->next;
	}

	return errorCode;
}


// Make the output text friendly for the report format...
string tempOutString;
const char *Report::outputFriendly(const char *theText)
{
	// Variables...
	size_t position = 0;

	tempOutString.assign(theText);
	switch (config->reportFormat)
	{
		case Config::HTML:
		case Config::XML:
			// Find characters that should be replaced...
			position = tempOutString.find('<');
			while (position != tempOutString.npos)
			{
				tempOutString.replace(position, 1, "&lt;");
				position = tempOutString.find('<', position + 4);
			}
			position = tempOutString.find('>');
			while (position != tempOutString.npos)
			{
				tempOutString.replace(position, 1, "&gt;");
				position = tempOutString.find('>', position + 4);
			}
			position = tempOutString.find('&');
			while (position != tempOutString.npos)
			{
				tempOutString.replace(position, 1, "&amp;");
				position = tempOutString.find('&', position + 5);
			}
			break;

		case Config::Latex:
			// Find characters that should be escaped...
			position = tempOutString.find('\\');
			while (position != tempOutString.npos)
			{
				tempOutString.insert(position + 1, "textbackslash");
				position = tempOutString.find('\\', position + 14);
			}
			position = tempOutString.find('_');
			while (position != tempOutString.npos)
			{
				tempOutString.insert(position, "\\");
				position = tempOutString.find('_', position + 2);
			}
			position = tempOutString.find('$');
			while (position != tempOutString.npos)
			{
				tempOutString.insert(position, "\\");
				position = tempOutString.find('$', position + 2);
			}
			position = tempOutString.find('#');
			while (position != tempOutString.npos)
			{
				tempOutString.insert(position, "\\");
				position = tempOutString.find('#', position + 2);
			}
			position = tempOutString.find('&');
			while (position != tempOutString.npos)
			{
				tempOutString.insert(position, "\\");
				position = tempOutString.find('&', position + 2);
			}
			position = tempOutString.find('^');
			while (position != tempOutString.npos)
			{
				tempOutString.replace(position, 1, "\\^{}");
				position = tempOutString.find('^', position + 4);
			}
			position = tempOutString.find('~');
			while (position != tempOutString.npos)
			{
				tempOutString.replace(position, 1, "\\~{}");
				position = tempOutString.find('~', position + 4);
			}
			position = tempOutString.find("...");
			while (position != tempOutString.npos)
			{
				tempOutString.replace(position, 3, "\\ldots");
				position = tempOutString.find("...", position + 6);
			}
			position = tempOutString.find("|");
			while (position != tempOutString.npos)
			{
				tempOutString.replace(position, 1, "\\textbar");
				position = tempOutString.find("|", position + 8);
			}
			position = tempOutString.find('%');
			while (position != tempOutString.npos)
			{
				tempOutString.insert(position, "\\");
				position = tempOutString.find('%', position + 2);
			}
			break;

		default:
			break;
	}

	return tempOutString.c_str();
}


string tempReference;
const char *Report::getReferenceNumber(const char *reference)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::configReportStruct *configReportPointer = 0;
	bool found = false;

	// Search Security Issues first...
	securityIssuePointer = device->securityReport;
	while ((securityIssuePointer != 0) && (found == false))
	{
		if (securityIssuePointer->reference.compare(reference) == 0)
		{
			tempReference.assign(device->intToString(securityIssuePointer->section));
			tempReference.append(".");
			tempReference.append(device->intToString(securityIssuePointer->subsection));
			found = true;
		}
		else
			securityIssuePointer = securityIssuePointer->next;
	}

	// Search Configuration Section...
	configReportPointer = device->configReport;
	while ((configReportPointer != 0) && (found == false))
	{
		if (configReportPointer->reference.compare(reference) == 0)
		{
			tempReference.assign(device->intToString(configReportPointer->section));
			tempReference.append(".");
			tempReference.append(device->intToString(configReportPointer->subsection));
			found = true;
		}
		else
			configReportPointer = configReportPointer->next;
	}

	// Search Appendix Section...
	configReportPointer = device->appendixReport;
	while ((configReportPointer != 0) && (found == false))
	{
		if (configReportPointer->reference.compare(reference) == 0)
		{
			tempReference.assign(device->intToString(configReportPointer->section));
			tempReference.append(".");
			tempReference.append(device->intToString(configReportPointer->subsection));
			found = true;
		}
		else
			configReportPointer = configReportPointer->next;
	}

	// Search Introduction Section...
	configReportPointer = device->reportIntro;
	while ((configReportPointer != 0) && (found == false))
	{
		if (configReportPointer->reference.compare(reference) == 0)
		{
			tempReference.assign(device->intToString(configReportPointer->section));
			tempReference.append(".");
			tempReference.append(device->intToString(configReportPointer->subsection));
			found = true;
		}
		else
			configReportPointer = configReportPointer->next;
	}

	if (found == false)
		tempReference.assign("");

	return tempReference.c_str();
}


string tempStringItem;
const char *Report::getStringListItem(Device::paragraphStruct *paragraph)
{
	// Variables...
	Device::listStruct *listPointer = 0;

	// Get string...
	if (paragraph == 0)
		tempStringItem.erase();
	else if (paragraph->strings == 0)
		tempStringItem.erase();
	else
	{
		listPointer = paragraph->strings->next;
		tempStringItem.assign(paragraph->strings->listItem);
		delete paragraph->strings;
		paragraph->strings = listPointer;
	}

	return tempStringItem.c_str();
}


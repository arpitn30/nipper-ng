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
#include "report.h"


int Report::writeText(const char *theText, Device::paragraphStruct *paragraph, bool expandAbbreviations, bool hideMarkup)
{
	// Variables...
	string outputString(outputFriendly(theText));
	Device::valueList *valuePointer = 0;
	string tempString;
	string tempString2;
	size_t position = 0;
	size_t position2 = 0;
	char buffer[64];
	int dayType = 0;
	time_t tempTime;
	bool updated = true;

	// init...
	if (paragraph != 0)
		valuePointer = paragraph->values;

	// Repeat until no more changes are made...
	position = outputString.find("*");
	while (position != outputString.npos)
	{

		// Company name...
		if (outputString.compare(position, 9, "*COMPANY*") == 0)
			outputString.replace(position, 9, config->companyName);

		// Abbreviation...
		else if (outputString.compare(position, 8, "*ABBREV*") == 0)
		{
			// Find abbreviation...
			position2 = outputString.find("*-ABBREV*", position);
			tempString2.assign(outputString.substr(position + 8, position2 - position - 8).c_str());

			// Output abbreviation...
			switch (device->addAbbreviation(tempString2.c_str(), expandAbbreviations))
			{
				case Device::abbrevExpand:
					switch (config->reportFormat)
					{
						case Config::XML:
							if (hideMarkup == true)
								tempString.assign(device->getAbbreviation(tempString2.c_str()));
							else
							{
								tempString.assign("<abbrev expand=\"true\" long=\"");
								tempString.append(device->getAbbreviation(tempString2.c_str()));
								tempString.append("\" short=\"");
								tempString.append(tempString2);
								tempString.append("\" />"); 
							}
							break;
						default:
							if (hideMarkup == true)
								tempString.assign(device->getAbbreviation(tempString2.c_str()));
							else
							{
								tempString.assign(device->getAbbreviation(tempString2.c_str()));
								tempString.append(" (");
								tempString.append(tempString2);
								tempString.append(")");
							}
							break;
					}
					break;
				case Device::abbrevFound:
					switch (config->reportFormat)
					{
						case Config::XML:
							if (hideMarkup == true)
								tempString.assign(tempString2);
							else
							{
								tempString.assign("<abbrev expand=\"false\" long=\"");
								tempString.append(device->getAbbreviation(tempString2.c_str()));
								tempString.append("\" short=\"");
								tempString.append(tempString2);
								tempString.append("\" />"); 
							}
							break;
						default:
							tempString.assign(tempString2);
							break;
					}
					break;
				default:
					tempString.assign(tempString2);
					break;
			}
			// Replace...
			outputString.replace(position, position2 - position + 9, tempString.c_str());
		}

		// Command option...
		else if (outputString.compare(position, 11, "*CMDOPTION*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					outputString.replace(position, 11, "<span class=\"cmdoption\">[");
					break;
				case Config::XML:
					outputString.replace(position, 11, "<cmdoption>[");
					break;
				default:
					outputString.replace(position, 11, "[");
					break;
			}
			position2 = outputString.find("*-CMDOPTION*", position);
			if (position2 != outputString.npos)
			{
				switch (config->reportFormat)
				{
					case Config::HTML:
						outputString.replace(position2, 12, "]</span>");
						break;
					case Config::XML:
						outputString.replace(position2, 12, "]</cmdoption>");
						break;
					default:
						outputString.replace(position2, 12, "]");
						break;
				}
			}
		}

		// Command requirement...
		else if (outputString.compare(position, 12, "*CMDREQUIRE*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					outputString.replace(position, 12, "<span class=\"cmdrequire\">{");
					break;
				case Config::XML:
					outputString.replace(position, 12, "<cmdrequire>{");
					break;
				default:
					outputString.replace(position, 12, "{");
					break;
			}
			position2 = outputString.find("*-CMDREQUIRE*", position);
			if (position2 != outputString.npos)
			{
				switch (config->reportFormat)
				{
					case Config::HTML:
						outputString.replace(position2, 13, "}</span>");
						break;
					case Config::XML:
						outputString.replace(position2, 13, "}</cmdrequire>");
						break;
					default:
						outputString.replace(position2, 13, "}");
						break;
				}
			}
		}

		// Command alternative...
		else if (outputString.compare(position, 7, "*CMDOR*") == 0)
			outputString.replace(position, 7, "|");

		// Command user supplied command information...
		else if (outputString.compare(position, 9, "*CMDUSER*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					outputString.replace(position, 9, "<span class=\"cmduser\">");
					break;
				case Config::XML:
					outputString.replace(position, 9, "<cmduser>");
					break;
				default:
					outputString.replace(position, 9, "");
					break;
			}
			position2 = outputString.find("*-CMDUSER*", position);
			if (position2 != outputString.npos)
			{
				switch (config->reportFormat)
				{
					case Config::HTML:
						outputString.replace(position2, 10, "</span>");
						break;
					case Config::XML:
						outputString.replace(position2, 10, "</cmduser>");
						break;
					default:
						outputString.replace(position2, 10, "");
						break;
				}
			}
		}

		// Date...
		else if (outputString.compare(position, 6, "*DATE*") == 0)
		{
			tempTime = time(NULL);

			// Day of week...
			strftime(buffer, sizeof(buffer), "%A ", localtime(&tempTime));
			tempString.assign(buffer);

			// Day of month...
			strftime(buffer, sizeof(buffer), "%d", localtime(&tempTime));
			dayType = buffer[1] - 48;
			if (buffer[0] == '0')
			{
				buffer[0] = buffer[1];
				buffer[1] = 0;
			}
			tempString.append(buffer);
			switch (dayType)
			{
				case 1:
					tempString.append("st ");
					break;
				case 2:
					tempString.append("nd ");
					break;
				case 3:
					tempString.append("rd ");
					break;
				default:
					tempString.append("th ");
					break;
			}

			// Month + Year
			strftime(buffer, sizeof(buffer), "%B %Y", localtime(&tempTime));
			tempString.append(buffer);
			outputString.replace(position, 6, tempString.c_str());
		}

		// Device name...
		else if (outputString.compare(position, 12, "*DEVICENAME*") == 0)
		{
			if (config->deviceName != 0)
			{
				tempString.assign(outputFriendly(config->deviceName));
				outputString.replace(position, 12, tempString.c_str());
			}
			else if (device->general != 0)
			{
				tempString.assign(outputFriendly(device->general->hostname.c_str()));
				outputString.replace(position, 12, tempString.c_str());
			}
		}

		// Device type...
		else if (outputString.compare(position, 12, "*DEVICETYPE*") == 0)
		{
			tempString.assign(device->deviceMake);
			tempString.append(" ");
			if (config->deviceModel != 0)
			{
				tempString.append(config->deviceModel);
				tempString.append(" ");
				tempString.append(device->deviceType);
			}
			else if (device->deviceModel != 0)
			{
				tempString.append(device->deviceModel);
				tempString.append(" ");
				tempString.append(device->deviceType);
			}
			else
				tempString.append(device->deviceType);
			outputString.replace(position, 12, tempString.c_str());
		}

		// Device version...
		else if (outputString.compare(position, 15, "*DEVICEVERSION*") == 0)
		{
			tempString.assign(device->deviceOS);
			tempString.append(" ");
			tempString.append(outputFriendly(device->general->version.c_str()));
			outputString.replace(position, 15, tempString.c_str());
		}

		// Device OS...
		else if (outputString.compare(position, 10, "*DEVICEOS*") == 0)
			outputString.replace(position, 10, device->deviceOS);

		// Device full version...
		else if (outputString.compare(position, 19, "*DEVICEVERSIONFULL*") == 0)
		{
			tempString.assign(device->deviceMake);
			tempString.append(" ");
			tempString.append(device->deviceOS);
			tempString.append(" ");
			tempString.append(outputFriendly(device->general->version.c_str()));
			outputString.replace(position, 19, tempString.c_str());
		}

		// Table Reference...
		else if (outputString.compare(position, 10, "*TABLEREF*") == 0)
		{
			if (paragraph == 0)
				return libnipper_error_noparagraph;
			if (paragraph->table == 0)
				return libnipper_error_notable;

			switch (config->reportFormat)
			{
				case Config::HTML:
					tempString.assign("<a href=\"#");
					tempString.append(paragraph->table->reference);
					tempString.append("\">");
					tempString.append(device->intToString(paragraph->table->number));
					tempString.append("</a>");
					break;
				case Config::XML:
					tempString.assign("<linktotable ref=\"");
					tempString.append(paragraph->table->reference);
					tempString.append("\">");
					tempString.append(device->intToString(paragraph->table->number));
					tempString.append("</linktotable>");
					break;
				default:
					tempString.assign(device->intToString(paragraph->table->number));
					break;
			}
			outputString.replace(position, 10, tempString.c_str());
		}

		// Number...
		else if (outputString.compare(position, 8, "*NUMBER*") == 0)
		{
			if (valuePointer == 0)
				return libnipper_error_outofvalues;
			switch (valuePointer->item)
			{
				case 0:
					outputString.replace(position, 8, i18n("zero"));
					break;
				case 1:
					outputString.replace(position, 8, i18n("one"));
					break;
				case 2:
					outputString.replace(position, 8, i18n("two"));
					break;
				case 3:
					outputString.replace(position, 8, i18n("three"));
					break;
				case 4:
					outputString.replace(position, 8, i18n("four"));
					break;
				case 5:
					outputString.replace(position, 8, i18n("five"));
					break;
				case 6:
					outputString.replace(position, 8, i18n("six"));
					break;
				case 7:
					outputString.replace(position, 8, i18n("seven"));
					break;
				case 8:
					outputString.replace(position, 8, i18n("eight"));
					break;
				case 9:
					outputString.replace(position, 8, i18n("nine"));
					break;
				case 10:
					outputString.replace(position, 8, i18n("ten"));
					break;
				default:
					tempString.assign(device->intToString(valuePointer->item));
					outputString.replace(position, 8, tempString.c_str());
					break;
			}
			valuePointer = valuePointer->next;
		}

		// SECTIONLINK...
		else if (outputString.compare(position, 13, "*SECTIONLINK*") == 0)
		{
			if (paragraph == 0)
				return libnipper_error_noparagraph;
			if (paragraph->strings == 0)
				return libnipper_error_outofstrings;

			switch (config->reportFormat)
			{
				case Config::HTML:
					tempString.assign("<a href=\"#");
					tempString.append(getStringListItem(paragraph));
					tempString.append("\">");
					break;
				case Config::XML:
					tempString.assign("<sectionlink ref=\"");
					tempString.append(getStringListItem(paragraph));
					tempString.append("\">");
					break;
				case Config::Latex:
					tempString.assign("\\ref{");
					tempString.append(getStringListItem(paragraph));
					tempString.append("}");
					break;
				default:
					tempString.erase();
					break;
			}
			outputString.replace(position2, 13, tempString.c_str());
			position2 = outputString.find("*-SECTIONLINK*", position);
			if (position2 != outputString.npos)
			{
				switch (config->reportFormat)
				{
					case Config::HTML:
						outputString.replace(position2, 14, "</a>");
						break;
					case Config::XML:
						outputString.replace(position2, 14, "</sectionlink>");
						break;
					default:
						outputString.erase(position2, 14);
						break;
				}
			}
		}

		// Section Number...
		else if (outputString.compare(position, 11, "*SECTIONNO*") == 0)
		{

			if (paragraph == 0)
				return libnipper_error_noparagraph;
			if (paragraph->strings == 0)
				return libnipper_error_outofstrings;

			tempString2.assign(getStringListItem(paragraph));
			switch (config->reportFormat)
			{
				case Config::Latex:
					tempString.assign("\\ref{");
					tempString.append(getReferenceNumber(tempString2.c_str()));
					tempString.append("}");
					break;
				case Config::XML:
					tempString.assign("<sectionno ref=\"");
					tempString.append(getReferenceNumber(tempString2.c_str()));
					tempString.append("\" />");
					break;
				case Config::HTML:
					tempString.assign("<a href=\"#");
					tempString.append(tempString2);
					tempString.append("\">");
					tempString.append(getReferenceNumber(tempString2.c_str()));
					tempString.append("</a>");
					break;
				default:
					tempString.assign(getReferenceNumber(tempString2.c_str()));
					break;
			}
			outputString.replace(position, 11, tempString);
		}

		// URL...
		else if (outputString.compare(position, 5, "*URL*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					tempString.assign("<a href=\"");
					tempString.append(outputString.substr(position + 5, outputString.find("*-URL*") - 5 - position));
					tempString.append("\">");
					break;
				case Config::XML:
					tempString.assign("<weblink>");
					break;
				case Config::Latex:
					tempString.assign("\\url{");
					break;
				default:
					tempString.erase();
					break;
			}
			outputString.replace(position, 5, tempString.c_str());
			position2 = outputString.find("*-URL*", position);
			if (position2 != outputString.npos)
			{
				switch (config->reportFormat)
				{
					case Config::HTML:
						outputString.replace(position2, 6, "</a>");
						break;
					case Config::XML:
						outputString.replace(position2, 6, "</weblink>");
						break;
					case Config::Latex:
						outputString.replace(position2, 6, "}");
						break;
					default:
						outputString.erase(position2, 6);
						break;
				}
			}
		}

		// Password...
		else if (outputString.compare(position, 10, "*PASSWORD*") == 0)
		{

			if (paragraph == 0)
				return libnipper_error_noparagraph;
			if (paragraph->strings == 0)
				return libnipper_error_outofstrings;

			if (config->includePasswordsInReport == false)
				outputString.erase(position, 10);
			else
			{
				outputString.replace(position, 10, getStringListItem(paragraph));
				outputString.insert(position, " ");
			}
		}

		// Data...
		else if (outputString.compare(position, 6, "*DATA*") == 0)
		{

			if (paragraph == 0)
				return libnipper_error_noparagraph;
			if (paragraph->strings == 0)
				return libnipper_error_outofstrings;

			outputString.replace(position, 6, getStringListItem(paragraph));
		}

		// Host...
		else if (outputString.compare(position, 6, "*HOST*") == 0)
		{

			if (paragraph == 0)
				return libnipper_error_noparagraph;
			if (paragraph->strings == 0)
				return libnipper_error_outofstrings;

			switch (config->reportFormat)
			{
				case Config::HTML:
					tempString.assign("<font class=\"host\">");
					tempString.append(getStringListItem(paragraph));
					tempString.append("</font>");
					break;
				case Config::XML:
					tempString.assign("<host>");
					tempString.append(getStringListItem(paragraph));
					tempString.append("</host>");
					break;
				default:
					tempString.assign(getStringListItem(paragraph));
					break;
			}
			outputString.replace(position, 6, tempString.c_str());
		}

		// Code...
		else if (outputString.compare(position, 6, "*CODE*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					outputString.replace(position, 6, "\n<pre class=\"code\">\n");
					break;
				case Config::XML:
					outputString.replace(position, 6, "\n<code>\n");
					break;
				default:
					outputString.replace(position, 6, "\n");
					break;
			}
			position2 = outputString.find("*-CODE*", position);
			if (position2 != outputString.npos)
			{
				updated = true;
				switch (config->reportFormat)
				{
					case Config::HTML:
						outputString.replace(position2, 7, "\n</pre>\n");
						break;
					case Config::XML:
						outputString.replace(position2, 7, "\n</code>\n");
						break;
					default:
						outputString.replace(position2, 7, "\n");
						break;
				}
			}
		}

		// Code line...
		else if (outputString.compare(position, 10, "*CODELINE*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::XML:
					outputString.replace(position, 10, "<codeline>");
					break;
				case Config::Latex:
					outputString.replace(position, 10, "\\texttt{");
					break;
				default:
					outputString.erase(position, 10);
					break;
			}
			position2 = outputString.find("*-CODELINE*", position);
			if (position2 != outputString.npos)
			{
				switch (config->reportFormat)
				{
					case Config::XML:
						outputString.replace(position2, 11, "</codeline>");
						break;
					case Config::Latex:
						outputString.replace(position2, 11, "}");
						break;
					default:
						outputString.replace(position2, 11, "\n");
						break;
				}
			}
		}

		// Command...
		else if (outputString.compare(position, 9, "*COMMAND*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					outputString.erase(position, 9);
					break;
				case Config::XML:
					outputString.replace(position, 9, "<command>");
					break;
				case Config::Latex:
					outputString.replace(position, 9, "\\texttt{");
					break;
				default:
					outputString.replace(position, 9, "\"");
					break;
			}
			position2 = outputString.find("*-COMMAND*", position);
			if (position2 != outputString.npos)
			{
				switch (config->reportFormat)
				{
					case Config::HTML:
						outputString.replace(position2, 10, "\n");
						break;
					case Config::XML:
						outputString.replace(position2, 10, "</command>");
						break;
					case Config::Latex:
						outputString.replace(position2, 10, "}");
						break;
					default:
						outputString.replace(position2, 10, "\"\n");
						break;
				}
			}
		}

		// Power...
		else if (outputString.compare(position, 7, "*POWER*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					outputString.replace(position, 7, "<sup>");
					break;
				case Config::XML:
					outputString.replace(position, 7, "<superscript>");
					break;
				case Config::Latex:
					outputString.replace(position, 7, "^\\{");
					break;
				default:
					outputString.replace(position, 7, "^");
					break;
			}
			position2 = outputString.find("*-POWER*", position);
			if (position2 != outputString.npos)
			{
				switch (config->reportFormat)
				{
					case Config::HTML:
						outputString.replace(position2, 8, "</sup>");
						break;
					case Config::XML:
						outputString.replace(position2, 8, "</superscript>");
						break;
					case Config::Latex:
						outputString.replace(position2, 8, "}");
						break;
					default:
						outputString.erase(position2, 8);
						break;
				}
			}
		}

		// Colours...
		else if (outputString.compare(position, 10, "*CRITICAL*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					tempString.assign("<font class=\"critical\">");
					tempString.append(i18n("Critical"));
					tempString.append("</font>");
					outputString.replace(position, 10, tempString);
					break;
				default:
					outputString.replace(position, 10, i18n("Critical"));
					break;
			}
		}
		else if (outputString.compare(position, 6, "*HIGH*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					tempString.assign("<font class=\"high\">");
					tempString.append(i18n("High"));
					tempString.append("</font>");
					outputString.replace(position, 6, tempString);
					break;
				default:
					outputString.replace(position, 6, i18n("High"));
					break;
			}
		}
		else if (outputString.compare(position, 8, "*MEDIUM*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					tempString.assign("<font class=\"medium\">");
					tempString.append(i18n("Medium"));
					tempString.append("</font>");
					outputString.replace(position, 8, tempString);
					break;
				default:
					outputString.replace(position, 8, i18n("Medium"));
					break;
			}
		}
		else if (outputString.compare(position, 5, "*LOW*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					tempString.assign("<font class=\"low\">");
					tempString.append(i18n("Low"));
					tempString.append("</font>");
					outputString.replace(position, 5, tempString);
					break;
				default:
					outputString.replace(position, 5, i18n("Low"));
					break;
			}
		}
		else if (outputString.compare(position, 15, "*INFORMATIONAL*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					tempString.assign("<font class=\"informational\">");
					tempString.append(i18n("Info"));
					tempString.append("</font>");
					outputString.replace(position, 15, tempString);
					break;
				default:
					outputString.replace(position, 15, i18n("Info"));
					break;
			}
		}
		else if (outputString.compare(position, 9, "*TRIVIAL*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					tempString.assign("<font class=\"trivial\">");
					tempString.append(i18n("Trivial"));
					tempString.append("</font>");
					outputString.replace(position, 9, tempString);
					break;
				default:
					outputString.replace(position, 9, i18n("Trivial"));
					break;
			}
		}
		else if (outputString.compare(position, 6, "*EASY*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					tempString.assign("<font class=\"easy\">");
					tempString.append(i18n("Easy"));
					tempString.append("</font>");
					outputString.replace(position, 6, tempString);
					break;
				default:
					outputString.replace(position, 6, i18n("Easy"));
					break;
			}
		}
		else if (outputString.compare(position, 10, "*MODERATE*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					tempString.assign("<font class=\"moderate\">");
					tempString.append(i18n("Moderate"));
					tempString.append("</font>");
					outputString.replace(position, 10, tempString);
					break;
				default:
					outputString.replace(position, 10, i18n("Moderate"));
					break;
			}
		}
		else if (outputString.compare(position, 13, "*CHALLENGING*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					tempString.assign("<font class=\"challenging\">");
					tempString.append(i18n("Challenge"));
					tempString.append("</font>");
					outputString.replace(position, 13, tempString);
					break;
				default:
					outputString.replace(position, 13, i18n("Challenge"));
					break;
			}
		}
		else if (outputString.compare(position, 15, "*NOTAPPLICABLE*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					tempString.assign("<font class=\"notapplicable\">");
					tempString.append(i18n("N/A"));
					tempString.append("</font>");
					outputString.replace(position, 15, tempString);
					break;
				default:
					outputString.replace(position, 15, i18n("N/A"));
					break;
			}
		}
		else if (outputString.compare(position, 10, "*INVOLVED*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					tempString.assign("<font class=\"involved\">");
					tempString.append(i18n("Involved"));
					tempString.append("</font>");
					outputString.replace(position, 10, tempString);
					break;
				default:
					outputString.replace(position, 10, i18n("Involved"));
					break;
			}
		}
		else if (outputString.compare(position, 9, "*PLANNED*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					tempString.assign("<font class=\"planned\">");
					tempString.append(i18n("Planned"));
					tempString.append("</font>");
					outputString.replace(position, 9, tempString);
					break;
				default:
					outputString.replace(position, 9, i18n("Planned"));
					break;
			}
		}
		else if (outputString.compare(position, 7, "*QUICK*") == 0)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					tempString.assign("<font class=\"quick\">");
					tempString.append(i18n("Quick"));
					tempString.append("</font>");
					outputString.replace(position, 7, tempString);
					break;
				default:
					outputString.replace(position, 7, i18n("Quick"));
					break;
			}
		}

		else if (outputString.compare(position, 1, "*") == 0)
			position++;
		position = outputString.find("*", position);
	}

	// Write the modified text to the report...
	fprintf(outFile, "%s", outputString.c_str());
	return 0;
}

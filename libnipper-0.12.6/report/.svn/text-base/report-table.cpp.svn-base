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


// Write Table...
int Report::writeTable(Device::paragraphStruct *paragraph)
{
	// Variables...
	Device::headingStruct *headingPointer = 0;
	Device::bodyStruct *cellPointer = 0;
	int columns = 0;
	bool odd = true;
	unsigned int textTableWidth = 0;
	int tempInt = 0;
	int password = -1;
	int errorCode = 0;
	string tempString;
	bool endOfTableRow = false;

	// Check...
	if (paragraph == 0)
		return libnipper_error_noparagraph;
	if (paragraph->table == 0)
		return libnipper_error_notable;

	// Init...
	headingPointer = paragraph->table->headings;
	cellPointer = paragraph->table->body;

	// Table beginning...
	switch (config->reportFormat)
	{
		case Config::HTML:
			fprintf(outFile, "<a name=\"%s\"></a><table class=\"reporttable\">\n <caption>Table %d: ", paragraph->table->reference.c_str(), paragraph->table->number);
			errorCode = writeText(paragraph->table->title.c_str(), paragraph, false);
			if (errorCode != 0)
				return errorCode;
			fprintf(outFile, "</caption>\n <thead>\n  <tr>");
			while (headingPointer != 0)
			{
				if ((config->includePasswordsInReport == true) || (headingPointer->password == false))
				{
					fprintf(outFile, "\n   <th>");
					errorCode = writeText(headingPointer->heading.c_str(), paragraph);
					if (errorCode != 0)
						return errorCode;
					fprintf(outFile, "</th>");
					columns++;
				}
				else
					password = columns;
				headingPointer = headingPointer->next;
			}
			fprintf(outFile, "\n  </tr>\n</thead>\n <tbody>\n");
			break;

		case Config::XML:
			fprintf(outFile, "    <table number=\"%d\" ref=\"%s\">\n", paragraph->table->number, paragraph->table->reference.c_str());
			fprintf(outFile, "     <caption>");
			errorCode = writeText(paragraph->table->title.c_str(), paragraph);
			if (errorCode != 0)
				return errorCode;
			fprintf(outFile, "</caption>\n     <tableheadings>\n");
			while (headingPointer != 0)
			{
				if ((config->includePasswordsInReport == true) || (headingPointer->password == false))
				{
					fprintf(outFile, "      <tableheading>");
					errorCode = writeText(headingPointer->heading.c_str(), paragraph);
					if (errorCode != 0)
						return errorCode;
					fprintf(outFile, "</tableheading>\n");
					columns++;
				}
				else
					password = columns;
				headingPointer = headingPointer->next;
			}
			fprintf(outFile, "     </tableheadings>\n     <tablebody>\n");
			break;

		case Config::Latex:
			fprintf(outFile, "\\begin{table}[h!]\n");
			fprintf(outFile, "\\begin{tabular}{|");
			while (headingPointer != 0)
			{
				if ((config->includePasswordsInReport == true) || (headingPointer->password == false))
					fprintf(outFile, " c |");
				else
					password = columns;
				headingPointer = headingPointer->next;
			}
			fprintf(outFile, "}\n\\hline\n");
			headingPointer = paragraph->table->headings;
			while (headingPointer != 0)
			{
				if ((config->includePasswordsInReport == true) || (headingPointer->password == false))
				{
					columns++;
					errorCode = writeText(headingPointer->heading.c_str(), paragraph);
					if (errorCode != 0)
						return errorCode;
					if (headingPointer->next != 0)
						fprintf(outFile, "&");
					else
						fprintf(outFile, "\\\\\n");
				}
				headingPointer = headingPointer->next;
			}
			fprintf(outFile, "\\hline\n");
			break;

		default:
			while (headingPointer != 0)
			{
				if ((config->includePasswordsInReport == true) || (headingPointer->password == false))
				{
					textTableWidth += headingPointer->heading.length();
					columns++;
				}
				else
					password = columns;
				headingPointer = headingPointer->next;
			}
			if (paragraph->table->number < 10)
				tempInt = 9;
			else if (paragraph->table->number < 100)
				tempInt = 10;
			else if (paragraph->table->number < 1000)
				tempInt = 11;
			else
				tempInt = 12;
			textTableWidth += (columns * 2) - 2;
			if ((paragraph->table->title.length() + tempInt) > textTableWidth)
				textTableWidth = paragraph->table->title.length() + tempInt;
			tempString.assign(textTableWidth, '-');
			fprintf(outFile, "\n%s", tempString.c_str());
			fprintf(outFile, "\n");
			headingPointer = paragraph->table->headings;
			while (headingPointer != 0)
			{
				if ((config->includePasswordsInReport == true) || (headingPointer->password == false))
				{
					writeText(headingPointer->heading.c_str(), paragraph);
					if (headingPointer->next != 0)
						fprintf(outFile, ", ");
				}
				headingPointer = headingPointer->next;
			}
			fprintf(outFile, "\n");
			fprintf(outFile, "%s", tempString.c_str());
			fprintf(outFile, "\n");
			break;
	}

	// Table contents...
	tempInt = 0;
	while (cellPointer != 0)
	{
		// If the data must span an entire table row...
		if (cellPointer->rowSpan == true)
		{
			switch (config->reportFormat)
			{
				case Config::HTML:
					if (odd == true)
					{
						fprintf(outFile, "<tr><td colspan=\"%d\">", columns);
						odd = false;
					}
					else
					{
						fprintf(outFile, "<tr class=\"evenrow\"><td colspan=\"%d\">", columns);
						odd = true;
					}
					if (!cellPointer->reference.empty())
					{
						if (cellPointer->referencer == true)
							fprintf(outFile, "<a href=\"#");
						else
							fprintf(outFile, "<a name=\"");
						errorCode = writeText(cellPointer->reference.c_str(), paragraph);
						if (errorCode != 0)
							return errorCode;
						fprintf(outFile, "\">");
					}
					errorCode = writeText(cellPointer->cellData.c_str(), paragraph);
					if (errorCode != 0)
						return errorCode;
					if (!cellPointer->reference.empty())
						fprintf(outFile, "</a>");
					fprintf(outFile, "</td></tr>\n");
					break;

				case Config::XML:
					fprintf(outFile, "      <tablerow>\n       <tableentry colspan=\"%d\"><item", columns);
					if (!cellPointer->reference.empty())
					{
						if (cellPointer->referencer == true)
							fprintf(outFile, " linkto=\"");
						else
							fprintf(outFile, " ref=\"");
						errorCode = writeText(cellPointer->reference.c_str(), paragraph);
						if (errorCode != 0)
							return errorCode;
						fprintf(outFile, "\">");
					}
					else
						fprintf(outFile, ">");
					errorCode = writeText(cellPointer->cellData.c_str(), paragraph);
					if (errorCode != 0)
						return errorCode;
					fprintf(outFile, "</item></tableentry>\n      </tablerow>\n");
					break;

				case Config::Latex:
					fprintf(outFile, "\\multicolumn{%d}{|c|}{", columns);
					errorCode = writeText(cellPointer->cellData.c_str(), paragraph);
					if (errorCode != 0)
						return errorCode;
					fprintf(outFile, "} \\\\");
					break;

				default:
					errorCode = writeText(cellPointer->cellData.c_str(), paragraph);
					if (errorCode != 0)
						return errorCode;
					fprintf(outFile, "\n");
					break;
			}
		}

		// If single cell data...
		else
		{
			if (tempInt != password)
			{
				// Start of a new table row...
				if ((tempInt == 0) && (cellPointer->newCell == true))
				{
					switch (config->reportFormat)
					{
						case Config::HTML:
							if (odd == true)
							{
								fprintf(outFile, "<tr><td>");
								odd = false;
							}
							else
							{
								fprintf(outFile, "<tr class=\"evenrow\"><td>");
								odd = true;
							}
							break;
						case Config::XML:
							fprintf(outFile, "      <tablerow>\n       <tableentry><item");
							break;
						default:
							break;
					}
				}

				// Else if start of a new cell...
				else if (cellPointer->newCell == true)
				{
					switch (config->reportFormat)
					{
						case Config::HTML:
							fprintf(outFile, "</td><td>");
							break;
						case Config::XML:
							fprintf(outFile, "</item></tableentry>\n       <tableentry><item");
							break;
						case Config::Latex:
							fprintf(outFile, "&");
							break;
						default:
							fprintf(outFile, ", ");
							break;
					}
				}
				else
				{
					switch (config->reportFormat)
					{
						case Config::HTML:
							fprintf(outFile, "<br>");
							break;
						case Config::XML:
							fprintf(outFile, "</item><item");
							break;
						default:
							fprintf(outFile, " ");
							break;
					}
				}

				// The cell data...
				if (!cellPointer->reference.empty())
				{
					switch (config->reportFormat)
					{
						case Config::HTML:
							if (cellPointer->referencer == true)
								fprintf(outFile, "<a href=\"#");
							else
								fprintf(outFile, "<a name=\"");
							errorCode = writeText(cellPointer->reference.c_str(), paragraph);
							if (errorCode != 0)
								return errorCode;
							fprintf(outFile, "\">");
							break;
						case Config::XML:
							if (cellPointer->referencer == true)
								fprintf(outFile, " linkto=\"");
							else
								fprintf(outFile, " ref=\"");
							errorCode = writeText(cellPointer->reference.c_str(), paragraph);
							if (errorCode != 0)
								return errorCode;
							fprintf(outFile, "\">");
							break;
						default:
							break;
					}
				}
				else if (config->reportFormat == Config::XML)
					fprintf(outFile, ">");
				if (cellPointer->cellData.empty())
					fprintf(outFile, config->emptyTableCell);
				else
					errorCode = writeText(cellPointer->cellData.c_str(), paragraph);
				if (errorCode != 0)
					return errorCode;
				if ((!cellPointer->reference.empty()) && (config->reportFormat == Config::HTML))
					fprintf(outFile, "</a>");
				if (cellPointer->newCell == true)
					tempInt++;

				// End of a table row...
				if (tempInt == columns)
				{
					endOfTableRow = false;
					if (cellPointer->next != 0)
					{
						if (cellPointer->next->newCell == true)
							endOfTableRow = true;
					}
					else
						endOfTableRow = true;
					if (endOfTableRow == true)
					{
						switch (config->reportFormat)
						{
							case Config::HTML:
								fprintf(outFile, "</td></tr>\n");
								break;
							case Config::XML:
								fprintf(outFile, "</item></tableentry>\n      </tablerow>\n");
								break;
							case Config::Latex:
								fprintf(outFile, "\\\\\n\\hline\n");
								break;
							default:
								fprintf(outFile, "\n");
								break;
						}
						tempInt = 0;
					}
				}
			}
		}

		cellPointer = cellPointer->next;
	}

	// Table end...
	switch (config->reportFormat)
	{
		case Config::HTML:
			fprintf(outFile, " </tbody>\n</table>\n");
			break;

		case Config::XML:
			fprintf(outFile, "     </tablebody>\n    </table>\n");
			break;

		case Config::Latex:
			fprintf(outFile, "\\end{tabular}\n\\caption{");
			errorCode = writeText(paragraph->table->title.c_str(), paragraph);
			if (errorCode != 0)
				return errorCode;
			fprintf(outFile, "}\n\\end{table}\n\n");
			break;

		default:
			tempString.assign(textTableWidth, '-');
			fprintf(outFile, "%s", tempString.c_str());
			fprintf(outFile, "\nTable %d: ", paragraph->table->number);
			errorCode = writeText(paragraph->table->title.c_str(), paragraph);
			if (errorCode != 0)
				return errorCode;
			fprintf(outFile, "\n\n");
			break;
	}

	return errorCode;
}


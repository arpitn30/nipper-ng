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


// Write Bullet Lists...
int Report::writeList(Device::paragraphStruct *paragraph)
{
	// Variables...
	Device::listStruct *listPointer = 0;
	int errorCode = 0;

	// Check...
	if (paragraph == 0)
		return libnipper_error_noparagraph;
	listPointer = paragraph->list;

	// Make sure that there is a list...
	if (listPointer != 0)
	{

		// Draw list start...
		switch (config->reportFormat)
		{
			case Config::HTML:
				fprintf(outFile, "<ul>\n");
				break;
			case Config::Latex:
				fprintf(outFile, "\\begin{itemize}\n");
				break;
			case Config::XML:
				fprintf(outFile, "<list>\n");
				break;
			default:
				fprintf(outFile, "\n");
				break;
		}

		// Draw list items...
		while (listPointer != 0)
		{

			// Start of list item...
			switch (config->reportFormat)
			{
				case Config::HTML:
					fprintf(outFile, "<li>");
					break;
				case Config::Latex:
					fprintf(outFile, "\\item ");
					break;
				case Config::XML:
					fprintf(outFile, "<listitem>");
					break;
				default:
					fprintf(outFile, "  * ");
					break;
			}

			// Write the item text...
			errorCode = writeText(listPointer->listItem.c_str(), paragraph, true);
			if (errorCode != 0)
				return errorCode;

			// End of list item...
			if (listPointer->next != 0)
			{
				switch (config->reportFormat)
				{
					case Config::HTML:
						fprintf(outFile, ";</li>\n");
						break;
					case Config::XML:
						fprintf(outFile, ";</listitem>\n");
						break;
					default:
						fprintf(outFile, ";\n");
						break;
				}
			}

			// Last one?
			else
			{
				switch (config->reportFormat)
				{
					case Config::HTML:
						fprintf(outFile, ".</li>\n</ul>\n");
						break;
					case Config::XML:
						fprintf(outFile, ".</listitem>\n</list>\n");
						break;
					case Config::Latex:
						fprintf(outFile, ".\n\\end{itemize}\n");
						break;
					default:
						fprintf(outFile, ".\n\n");
						break;
				}
			}

			listPointer = listPointer->next;
		}
	}
	else
		return libnipper_error_nolist;

	return errorCode;
}


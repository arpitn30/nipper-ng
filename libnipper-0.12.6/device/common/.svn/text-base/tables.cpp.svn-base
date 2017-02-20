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
#include "../../globaldefs.h"
#include "../device.h"


Device::paragraphStruct *Device::getTableParagraphPointer(const char *reference)
{
	// Variables...
	paragraphStruct *paragraphPointer = 0;
	configReportStruct *configReportPointer = 0;
	bool found = false;

	// Find table...
	configReportPointer = configReport;
	while ((configReportPointer != 0) && (found == false))
	{
		paragraphPointer = configReportPointer->config;
		while ((paragraphPointer != 0) && (found == false))
		{
			if (paragraphPointer->table != 0)
			{
				if (paragraphPointer->table->reference.compare(reference) == 0)
					found = true;
			}
			if (found == false)
				paragraphPointer = paragraphPointer->next;
		}
		configReportPointer = configReportPointer->next;
	}

	// return result...
	if (found == true)
		return paragraphPointer;
	else
		return 0;
}


int Device::addTable(paragraphStruct *paragraphPointer, const char *reference)
{
	// Create...
	paragraphPointer->table = new (tableStruct);
	if (paragraphPointer->table != 0)
	{

		// Init...
		paragraphPointer->table->reference.assign(reference);
		paragraphPointer->table->number = 0;
		paragraphPointer->table->headings = 0;
		paragraphPointer->table->body = 0;
	}
	else
		return 1;

	return 0;
}


int Device::addTableHeading(tableStruct *tablePointer, const char *heading, bool password)
{
	// Variables...
	headingStruct *headingPointer = 0;

	// Create heading...
	if (tablePointer->headings == 0)
	{
		tablePointer->headings = new (headingStruct);
		headingPointer = tablePointer->headings;
	}
	else
	{
		headingPointer = tablePointer->headings;
		while (headingPointer->next != 0)
			headingPointer = headingPointer->next;
		headingPointer->next = new (headingStruct);
		headingPointer = headingPointer->next;
	}

	// Init struct...
	if (headingPointer != 0)
	{
		headingPointer->heading.assign(heading);
		headingPointer->password = password;
		headingPointer->next = 0;

		return 0;
	}
	else
		return 1;
}


Device::bodyStruct *Device::addTableData(tableStruct *tablePointer, const char *data)
{
	// Variables
	bodyStruct *bodyPointer = 0;

	// Create
	if (tablePointer->body == 0)
	{
		tablePointer->body = new (bodyStruct);
		bodyPointer = tablePointer->body;
	}
	else
	{
		bodyPointer = tablePointer->body;
		while (bodyPointer->next != 0)
			bodyPointer = bodyPointer->next;
		bodyPointer->next = new (bodyStruct);
		bodyPointer = bodyPointer->next;
	}

	// Init struct...
	if (bodyPointer != 0)
	{
		bodyPointer->newCell = true;
		bodyPointer->rowSpan = false;
		bodyPointer->cellData.assign(data);
		bodyPointer->referencer = true;
		bodyPointer->next = 0;

		return bodyPointer;
	}
	else
		return 0;
}


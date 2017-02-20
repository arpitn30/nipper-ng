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


int Device::addListItem(paragraphStruct *paragraphPointer, const char *itemText)
{
	// Variables...
	listStruct *listItemPointer = 0;

	// Create list structure...
	if (paragraphPointer->list == 0)
	{
		paragraphPointer->list = new (listStruct);
		listItemPointer = paragraphPointer->list;
	}
	else
	{
		listItemPointer = paragraphPointer->list;
		while (listItemPointer->next != 0)
			listItemPointer = listItemPointer->next;
		listItemPointer->next = new (listStruct);
		listItemPointer = listItemPointer->next;
	}

	// Init and copy...
	listItemPointer->next = 0;
	listItemPointer->listItem.assign(itemText);

	return 0;
}


int Device::addValue(paragraphStruct *paragraph, int value)
{
	// Variables...
	Device::valueList *valuePointer = 0;

	// Reserve...
	if (paragraph->values == 0)
	{
		paragraph->values = new (Device::valueList);
		valuePointer = paragraph->values;
	}
	else
	{
		valuePointer = paragraph->values;
		while (valuePointer->next != 0)
			valuePointer = valuePointer->next;
		valuePointer->next = new (Device::valueList);
		valuePointer = valuePointer->next;
	}

	// Init...
	valuePointer->next = 0;
	valuePointer->item = value;

	return 0;
}


int Device::addString(paragraphStruct *paragraph, const char *item)
{
	// Variables...
	Device::listStruct *stringPointer = 0;

	// Reserve...
	if (paragraph->strings == 0)
	{
		paragraph->strings = new (Device::listStruct);
		stringPointer = paragraph->strings;
	}
	else
	{
		stringPointer = paragraph->strings;
		while (stringPointer->next != 0)
			stringPointer = stringPointer->next;
		stringPointer->next = new (Device::listStruct);
		stringPointer = stringPointer->next;
	}

	// Init...
	stringPointer->next = 0;
	stringPointer->listItem.assign(item);

	return 0;
}


Device::paragraphStruct *Device::addParagraph(securityIssueStruct *securityIssuePointer, paragraphType paragraph)
{
	// Variables...
	paragraphStruct *paragraphPointer = 0;

	// Create Config Report Structure...
	switch (paragraph)
	{
		case Device::Impact:
			if (securityIssuePointer->impact == 0)
			{
				securityIssuePointer->impact = new (Device::paragraphStruct);
				paragraphPointer = securityIssuePointer->impact;
			}
			else
			{
				paragraphPointer = securityIssuePointer->impact;
				while (paragraphPointer->next != 0)
					paragraphPointer = paragraphPointer->next;
				paragraphPointer->next = new (Device::paragraphStruct);
				paragraphPointer = paragraphPointer->next;
			}
			break;
		case Device::Ease:
			if (securityIssuePointer->ease == 0)
			{
				securityIssuePointer->ease = new (Device::paragraphStruct);
				paragraphPointer = securityIssuePointer->ease;
			}
			else
			{
				paragraphPointer = securityIssuePointer->ease;
				while (paragraphPointer->next != 0)
					paragraphPointer = paragraphPointer->next;
				paragraphPointer->next = new (Device::paragraphStruct);
				paragraphPointer = paragraphPointer->next;
			}
			break;
		case Device::Recommendation:
			if (securityIssuePointer->recommendation == 0)
			{
				securityIssuePointer->recommendation = new (Device::paragraphStruct);
				paragraphPointer = securityIssuePointer->recommendation;
			}
			else
			{
				paragraphPointer = securityIssuePointer->recommendation;
				while (paragraphPointer->next != 0)
					paragraphPointer = paragraphPointer->next;
				paragraphPointer->next = new (Device::paragraphStruct);
				paragraphPointer = paragraphPointer->next;
			}
			break;
		default:
			if (securityIssuePointer->finding == 0)
			{
				securityIssuePointer->finding = new (Device::paragraphStruct);
				paragraphPointer = securityIssuePointer->finding;
			}
			else
			{
				paragraphPointer = securityIssuePointer->finding;
				while (paragraphPointer->next != 0)
					paragraphPointer = paragraphPointer->next;
				paragraphPointer->next = new (Device::paragraphStruct);
				paragraphPointer = paragraphPointer->next;
			}
			break;
	}

	// Init...
	paragraphPointer->next = 0;
	paragraphPointer->values = 0;
	paragraphPointer->strings = 0;
	paragraphPointer->table = 0;
	paragraphPointer->list = 0;
	paragraphPointer->paragraph = "";

	return paragraphPointer;
}
Device::paragraphStruct *Device::addParagraph(configReportStruct *configReportPointer)
{
	// Variables...
	paragraphStruct *paragraphPointer = 0;

	// Create Config Report Structure...
	if (configReportPointer->config == 0)
	{
		configReportPointer->config = new (Device::paragraphStruct);
		paragraphPointer = configReportPointer->config;
	}
	else
	{
		paragraphPointer = configReportPointer->config;
		while (paragraphPointer->next != 0)
			paragraphPointer = paragraphPointer->next;
		paragraphPointer->next = new (Device::paragraphStruct);
		paragraphPointer = paragraphPointer->next;
	}

	// Init...
	paragraphPointer->next = 0;
	paragraphPointer->values = 0;
	paragraphPointer->strings = 0;
	paragraphPointer->table = 0;
	paragraphPointer->list = 0;
	paragraphPointer->paragraph = "";

	return paragraphPointer;
}

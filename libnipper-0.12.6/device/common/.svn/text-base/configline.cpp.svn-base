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


#include "../../globaldefs.h"
#include "configline.h"
#include <cstring>


ConfigLine::ConfigLine()
{
	parts = 0;
	command = 0;
}


ConfigLine::~ConfigLine()
{
	deleteParts();
}


void ConfigLine::setConfigLine(char *line)
{
	// Variables...
	int lineLength = 0;
	int linePos = 0;
	bool quotes = false;
	bool gap = false;
	string tempString;
	struct ConfigLinePart *partPointer = 0;

	// Clear class, if data is already in...
	if (parts > 0)
		deleteParts();

	// Loop through the config line and split into parts...
	lineLength = strlen(line);
	for (linePos = 0; linePos < lineLength; linePos++)
	{

		// If a non-space character, or a space under quotes...
		if (((line[linePos] != 9) && (line[linePos] != ' ')) || (quotes == true))
		{

			// If quotes...
			if ((quotes == true) && (line[linePos] == '"'))
				quotes = false;
			else if (line[linePos] == '"')
				quotes = true;

			// Copy next character...
			tempString.push_back(line[linePos]);
			gap = false;
		}
		else
			gap = true;

		// If tempString contains stuff...
		if (((gap == true) && (tempString.empty() == false)) || ((tempString.empty() == false) && (linePos + 1 == lineLength)))
		{

			// Create the config line part struct...
			if (partPointer == 0)
			{
				command = new (ConfigLinePart);
				partPointer = command;
			}
			else
			{
				partPointer->next = new (ConfigLinePart);
				partPointer = partPointer->next;
			}

			// Copy the config part in and clear the tempString...
			partPointer->part = tempString;
			partPointer->next = 0;
			parts++;
			tempString.clear();

			// String braces if they exist...
			if (partPointer->part.length() > 2)
			{
				if ((partPointer->part.c_str()[0] == '(') && (partPointer->part.c_str()[partPointer->part.length() - 1] == ')'))
				{
					partPointer->part.erase(0, 1);
					partPointer->part.resize(partPointer->part.length() - 1);
				}
			}

			// String quotes if they exist...
			if (partPointer->part.length() > 1)
			{
				if ((partPointer->part.c_str()[0] == '"') && (partPointer->part.c_str()[partPointer->part.length() - 1] == '"'))
				{
					partPointer->part.erase(0, 1);
					partPointer->part.resize(partPointer->part.length() - 1);
				}
			}
		}
	}
}


const char *ConfigLine::part(int partNumber)
{
	// Variables...
	int count = 0;
	const char *emptyString = "";
	struct ConfigLinePart *partPointer = 0;

	// Return part...
	if (partNumber < parts)
	{
		partPointer = command;
		while (count < partNumber)
		{
			partPointer = partPointer->next;
			count++;
		}
		return partPointer->part.c_str();
	}

	// Part doesn't exist...
	else
		return emptyString;
}


void ConfigLine::deleteParts()
{
	// Variables...
	struct ConfigLinePart *partPointer = 0;

	while (command != 0)
	{
		partPointer = command->next;
		delete command;
		command = partPointer;
	}

	parts = 0;
}


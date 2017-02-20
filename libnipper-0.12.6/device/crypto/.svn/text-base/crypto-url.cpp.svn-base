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
#include <cstring>

#include "../../globaldefs.h"
#include "../device.h"


string decodedString;
const char *Device::urlDecode(const char *encodedString, bool replaceFirstEquals)
{
	// Variables...
	bool equalsReplaced = false;
	unsigned int offset = 0;
	decodedString.assign(encodedString);

	while (offset < decodedString.length())
	{
		// Equals replaced...
		if ((decodedString[offset] == '=') && (replaceFirstEquals == true) && (equalsReplaced == false))
		{
			decodedString[offset] = ' ';
			equalsReplaced = true;
		}

		// Next Value replaced...
		else if (decodedString[offset] == '&')
		{
			decodedString[offset] = '\n';
			equalsReplaced = false;
		}

		// If % and at lease 2 more characters remain...
		else if ((decodedString[offset] == '%') && (decodedString.length() > offset + 2))
		{
			// Space...
			if (strncmp(decodedString.c_str() + offset, "%20", 3) == 0)
				decodedString.replace(offset, 3, " ");
			// &...
			else if (strncmp(decodedString.c_str() + offset, "%26", 3) == 0)
				decodedString.replace(offset, 3, "&");
			// :...
			else if (strncmp(decodedString.c_str() + offset, "%3a", 3) == 0)
				decodedString.replace(offset, 3, "&");
			// ?...
			else if (strncmp(decodedString.c_str() + offset, "%3f", 3) == 0)
				decodedString.replace(offset, 3, "?");
		}

		offset++;
	}

	return decodedString.c_str();
}


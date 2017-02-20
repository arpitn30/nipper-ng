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


// Decrypt the Cisco password-7 password
string type7Return;
const char *Device::ciscoType7Decode(const char *encodedPassword)
{
	// Declarations...
	const char xlat[] = {
		0x64, 0x73, 0x66, 0x64, 0x3b, 0x6b, 0x66, 0x6f,
		0x41, 0x2c, 0x2e, 0x69, 0x79, 0x65, 0x77, 0x72,
		0x6b, 0x6c, 0x64, 0x4a, 0x4b, 0x44, 0x48, 0x53,
		0x55, 0x42, 0x73, 0x67, 0x76, 0x63, 0x61, 0x36,
		0x39, 0x38, 0x33, 0x34, 0x6e, 0x63, 0x78, 0x76,
		0x39, 0x38, 0x37, 0x33, 0x32, 0x35, 0x34, 0x6b,
		0x3b, 0x66, 0x67, 0x38, 0x37, 0x64, 0x73, 0x66,
		0x64, 0x3b, 0x6b, 0x66, 0x6f, 0x41, 0x2c, 0x2e,
		0x69, 0x79, 0x65, 0x77, 0x72, 0x6b, 0x6c, 0x64,
		0x4a, 0x4b, 0x44, 0x48, 0x53, 0x55, 0x42, 0x73,
		0x67, 0x76, 0x63, 0x61, 0x36, 0x39, 0x38, 0x33,
		0x34, 0x6e, 0x63, 0x78, 0x76, 0x39, 0x38, 0x37,
		0x33, 0x32, 0x35, 0x34, 0x6b, 0x3b, 0x66, 0x67,
		0x38, 0x37};

	// Variables...
	string password(encodedPassword);
	char tempChar;
	unsigned int seed = 0;
	unsigned int i = 0;
	unsigned int val = 0;

	type7Return.assign("");

	// If invalid password size...
	if ((password.length() & 1) || (password.length() < 4))
		return "";

	// If invlaid seed...
	seed = (password[0] - '0') * 10 + password[1] - '0';
	if ((seed > 15) || (!isdigit(password[0])) || (!isdigit(password[1])))
		return "";

	// Decode password...
	for (i = 2 ; i <= password.length(); i++)
	{
		if (i !=2 && !(i & 1))
		{
			tempChar = val ^ xlat[seed++];
			type7Return.append(1, tempChar);
			val = 0;
		}
		val *= 16;

		if (isdigit(password[i] = toupper(password[i])))
		{
			val += password[i] - '0';
			continue;
		}

		if (password[i] >= 'A' && password[i] <= 'F')
		{
			val += password[i] - 'A' + 10;
			continue;
		}

		if (password.length() != i)
			return "";
	}

	return type7Return.c_str();
}


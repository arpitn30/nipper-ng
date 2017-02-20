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
 *      2. Any code that integrates Nipper MUST display the copyright      *
 *         information below with the programs own copyright information.  *
 *                                                                         *
 *         "Nipper Copyright (C) 2006 - 2008 by Ian Ventura-Whiting"       *
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

// See RFC3548 for details of Base64 Encode / Decode standards

static const char base64string[] = {62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, 0, -1, -1, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51};


// Base64 character check
int checkBase64Char(char inputChar)
{
	if (inputChar > 122)
		return -1;
	if (inputChar < 43)
		return -1;
	else
		return base64string[inputChar - 43];
}


// Base64 character strip (gets rid of odd characters at the end)
void base64StringStrip(char *inputString)
{
	// Variables...
	char endChar;

	// Stripped Characters...
	// 32 - Space
	// 10 - Line Feed
	// 13 - Carridge Return
	if (strlen(inputString) != 0)
	{
		// Loop until characters have gone...
		endChar = inputString[strlen(inputString) - 1];
		while (checkBase64Char(endChar) == -1)
		{
			inputString[strlen(inputString) - 1] = 0;
			endChar = inputString[strlen(inputString) - 1];
		}
	}
}


int base64DecodeChars(char *inputString)
{
	// Variables...
	int stringLoop = 0;
	char *outString = inputString;
	int equalsReplaced = false;
	int percentUsed = 0;
	char inter1, inter2, inter3, inter4 = 0;

	// Strip unwanted characters from the end of the string
	base64StringStrip(inputString);

	// Convert from base64 converts every 4 characters to 3. This is due to
	// base64 conversion from 6bit to 8bit characters.
	while (inputString[0] != 0)
	{
		// Decode characters
		inter1 = checkBase64Char(inputString[0]);
		if (inter1 == -1)
			return false;
		inputString++;
		if (inputString[0] != 0)
		{
			inter2 = checkBase64Char(inputString[0]);
			if (inter2 == -1)
				return false;
		}
		else
			inter2 = 0;
		inputString++;
		if (inputString[0] != 0)
		{
			inter3 = checkBase64Char(inputString[0]);
			if (inter3 == -1)
				return false;
		}
		else
			inter3 = 0;
		inputString++;
		if (inputString[0] != 0)
		{
			inter4 = checkBase64Char(inputString[stringLoop]);
			if (inter4 == -1)
				return false;
		}
		else
			inter4 = 0;
		inputString++;

		// Convert 4 6 bit characters into 3 8 bit ones...
		// First char...
		outString[0] = (inter1 << 2) | (inter2 >> 4);
		if ((outString[0] == '=') && (equalsReplaced == false))
		{
			equalsReplaced = true;
			outString[0] = ' ';
		}
		else if (outString[0] == '&')
		{
			equalsReplaced = false;
			outString[0] = '\n';
		}
		else if (percentUsed == 2)
		{
			if (strncmp(outString - 2, "%20", 3) == 0)
			{
				outString -= 2;
				outString[0] = ' ';
			}
			else if (strncmp(outString - 2, "%26", 3) == 0)
			{
				outString -= 2;
				outString[0] = '&';
			}
			else if (strncmp(outString - 2, "%3a", 3) == 0)
			{
				outString -= 2;
				outString[0] = ':';
			}
			else if (strncmp(outString - 2, "%3f", 3) == 0)
			{
				outString -= 2;
				outString[0] = '?';
			}
			percentUsed = 0;
		}
		else if (percentUsed == 1)
			percentUsed = 2;
		else if (outString[0] == '%')
			percentUsed = 1;
		outString++;

		// Second char...
		outString[0] = ((inter2 << 4) & 240) | (inter3 >> 2);
		if ((outString[0] == '=') && (equalsReplaced == false))
		{
			equalsReplaced = true;
			outString[0] = ' ';
		}
		else if (outString[0] == '&')
		{
			equalsReplaced = false;
			outString[0] = '\n';
		}
		else if (percentUsed == 2)
		{
			if (strncmp(outString - 2, "%20", 3) == 0)
			{
				outString -= 2;
				outString[0] = ' ';
			}
			else if (strncmp(outString - 2, "%26", 3) == 0)
			{
				outString -= 2;
				outString[0] = '&';
			}
			else if (strncmp(outString - 2, "%3a", 3) == 0)
			{
				outString -= 2;
				outString[0] = ':';
			}
			else if (strncmp(outString - 2, "%3f", 3) == 0)
			{
				outString -= 2;
				outString[0] = '?';
			}
			percentUsed = 0;
		}
		else if (percentUsed == 1)
			percentUsed = 2;
		else if (outString[0] == '%')
			percentUsed = 1;
		outString++;

		// Third char...
		outString[0] = ((inter3 << 6) & 192)| inter4;
		if ((outString[0] == '=') && (equalsReplaced == false))
		{
			equalsReplaced = true;
			outString[0] = ' ';
		}
		else if (outString[0] == '&')
		{
			equalsReplaced = false;
			outString[0] = '\n';
		}
		else if (percentUsed == 2)
		{
			if (strncmp(outString - 2, "%20", 3) == 0)
			{
				outString -= 2;
				outString[0] = ' ';
			}
			else if (strncmp(outString - 2, "%26", 3) == 0)
			{
				outString -= 2;
				outString[0] = '&';
			}
			else if (strncmp(outString - 2, "%3a", 3) == 0)
			{
				outString -= 2;
				outString[0] = ':';
			}
			else if (strncmp(outString - 2, "%3f", 3) == 0)
			{
				outString -= 2;
				outString[0] = '?';
			}
			percentUsed = 0;
		}
		else if (percentUsed == 1)
			percentUsed = 2;
		else if (outString[0] == '%')
			percentUsed = 1;
		outString++;
	}

	// String end...
	outString[0] = 0;

	return true;
}



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


void preProcessSonicOSConfig(char *inputString)
{
	// Variables...
	int readPos = 0;
	int writePos = 0;

	for (readPos = 0; readPos < strlen(inputString); readPos++)
	{
		// If it is an space character...
		if (strncmp(inputString + readPos, "%20", 3) == 0)
		{
			inputString[writePos] = ' ';
			readPos += 2;
		}

		// If it is an & character...
		else if (strncmp(inputString + readPos, "%26", 3) == 0)
		{
			inputString[writePos] = '&';
			readPos += 2;
		}

		// If it is an : character...
		else if (strncmp(inputString + readPos, "%3a", 3) == 0)
		{
			inputString[writePos] = ':';
			readPos += 2;
		}

		// If it is an ? character...
		else if (strncmp(inputString + readPos, "%3f", 3) == 0)
		{
			inputString[writePos] = '?';
			readPos += 2;
		}

		else
			inputString[writePos] = inputString[readPos];

		writePos++;
	}

	// Set string terminator...
	inputString[writePos] = 0;
}

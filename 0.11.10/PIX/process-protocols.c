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


struct fixupList
{
	char protocol[16];
	char options[32];
	int enabled;			// true or false
	struct fixupList *next;
};


// Process fixup
void processFixupPIX(char *line, struct nipperConfig *nipper)
{
	// Variables...
	int tempInt = 0;
	char tempString[nipper->maxSize];
	struct ciscoCommand command;
	struct fixupList *fixupPIXPointer = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Fixup Line: %s\n", line);
	}

	// Is first structure
	if (nipper->pix->fixup == 0)
	{
		nipper->pix->fixup = malloc(sizeof(struct fixupList));
		fixupPIXPointer = nipper->pix->fixup;
	}
	else
	{
		fixupPIXPointer = nipper->pix->fixup;
		while (fixupPIXPointer->next != 0)
			fixupPIXPointer = fixupPIXPointer->next;
		fixupPIXPointer->next = malloc(sizeof(struct fixupList));
		fixupPIXPointer = fixupPIXPointer->next;
	}

	// Init
	command = splitLine(line);
	memset(fixupPIXPointer, 0, sizeof(struct fixupList));
	memset(&tempString, 0, nipper->maxSize);
	fixupPIXPointer->enabled = true;
	tempInt = 0;

	// Enable Protocol Analysis...
	if (strcmp(command.part[tempInt], "no") == 0)
	{
		fixupPIXPointer->enabled = false;
		tempInt++;
	}

	// Protocol
	tempInt = tempInt + 2;
	strncpy(fixupPIXPointer->protocol, command.part[tempInt], sizeof(fixupPIXPointer->protocol) - 1);
	tempInt++;

	// Options
	while (tempInt < command.parts)
	{
		sprintf(tempString, "%s %s", tempString, command.part[tempInt]);
		tempInt++;
	}
	strncpy(fixupPIXPointer->options, tempString, sizeof(fixupPIXPointer->options) - 1);
}


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


// Process Clock
void processClock(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct ciscoCommand command;
	int tempInt = 0;
	int setting = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Clock Line: %s\n", line);
	}

	//init
	command = splitLine(line);

	// Setting
	if (strcmp(command.part[0], "no") == 0)
	{
		setting = false;
		tempInt = 2;
	}
	else
	{
		setting = true;
		tempInt = 1;
	}

	// Timezone
	if (strcmp(command.part[tempInt], "timezone") == 0)
	{
		if (setting == false)
		{
			strcpy(nipper->ios->timeZone, "UTC");
			nipper->ios->timeOffsetHours = 0;
			nipper->ios->timeOffsetMins = 0;
		}
		else
		{
			tempInt++;
			strncpy(nipper->ios->timeZone, command.part[tempInt], sizeof(nipper->ios->timeZone) -1);
			tempInt++;
			nipper->ios->timeOffsetHours = atoi(command.part[tempInt]);
			tempInt++;
			if (tempInt < command.parts)
				nipper->ios->timeOffsetMins = atoi(command.part[tempInt]);
		}
	}

	// Sumertime Zone
	else if (strcmp(command.part[tempInt], "summer-time") == 0)
	{
		if (setting == false)
			strcpy(nipper->ios->summerTimeZone, "");
		else
		{
			tempInt++;
			strncpy(nipper->ios->summerTimeZone, command.part[tempInt], sizeof(nipper->ios->summerTimeZone) -1);
		}
	}

	// Calendar Valid
	else if (strcmp(command.part[tempInt], "calendar-valid") == 0)
		nipper->ios->calendarValid = setting;

	// Debug (lines not processed)
	else if (nipper->linesnotprocessed == true)
		printf("%s\n", line);
}



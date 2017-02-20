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


// Banner
struct bannerConfig
{
	char *line;
	struct bannerConfig *next;
};


// Process Banner
void processBanner(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct bannerConfig *bannerPointer = 0;
	struct ciscoCommand command;
	char bannerTerminator[3];

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Banner Line: %s\n", line);
	}

	// Only process if banner has not already been set and banner line is made up of 3 parts...
	command = splitLine(line);
	if ((nipper->ios->banner == 0) && (command.parts > 2))
	{
		// init
		if (command.part[2][0] != '^')
		{
			bannerTerminator[0] = command.part[2][0];
			bannerTerminator[1] = 0;
		}
		else
		{
			bannerTerminator[0] = command.part[2][0];
			bannerTerminator[1] = command.part[2][1];
			bannerTerminator[2] = 0;
		}

		// If banner starts on the banner line...
		if ((command.parts > 3) || (strlen(command.part[2]) > 2))
		{
			nipper->ios->banner = malloc(sizeof(struct bannerConfig));
			bannerPointer = nipper->ios->banner;
			memset(bannerPointer, 0, sizeof(struct bannerConfig));
			bannerPointer->line = malloc(strlen(strstr(line, bannerTerminator) - strlen(bannerTerminator)));
			strcpy(bannerPointer->line, strstr(line, bannerTerminator) + strlen(bannerTerminator));
			bannerPointer->next = 0;
		}

		// Read next line
		readLine(nipper->input, line, nipper->maxSize);

		// Get all parts of the banner message...
		while ((strstr(line, bannerTerminator) == 0) && (feof(nipper->input) == 0))
		{
			if (nipper->debugMode == true)
			{
				printf("Banner: %s\n", line);
			}

			// Is this the first line of text...
			if (nipper->ios->banner == 0)
			{
				// create struct
				nipper->ios->banner = malloc(sizeof(struct bannerConfig));
				bannerPointer = nipper->ios->banner;
			}

			// or Add another line...
			else
			{
				// Create structure
				bannerPointer->next = malloc(sizeof(struct bannerConfig));
				bannerPointer = bannerPointer->next;
			}

			// Init structure...
			memset(bannerPointer, 0, sizeof(struct bannerConfig));
			bannerPointer->line = malloc(strlen(line) + 1);
			strcpy(bannerPointer->line, line);
			bannerPointer->next = 0;

			// Read next line
			readLine(nipper->input, line, nipper->maxSize);
		}
	}
}



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


// Process VTP
void processVTP(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct ciscoCommand command;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("VTP Line: %s\n", line);
	}

	// Init
	command = splitLine(line);

	// VTP server
	if ((strcmp(command.part[1], "server") == 0) || ((strcmp(command.part[1], "mode") == 0) && (strcmp(command.part[2], "server") == 0)))
		nipper->ios->vtpMode = vtp_mode_server;

	// VTP client
	else if ((strcmp(command.part[1], "client") == 0) || ((strcmp(command.part[1], "mode") == 0) && (strcmp(command.part[2], "client") == 0)))
		nipper->ios->vtpMode = vtp_mode_client;

	// VTP transparent
	else if ((strcmp(command.part[1], "transparent") == 0) || ((strcmp(command.part[1], "mode") == 0) && (strcmp(command.part[2], "transparent") == 0)))
		nipper->ios->vtpMode = vtp_mode_transparent;

	// No VTP Mode
	else if ((strcmp(command.part[0], "no") == 0) && (strcmp(command.part[1], "vtp") == 0) && (strcmp(command.part[2], "mode") == 0))
		nipper->ios->vtpMode = vtp_mode_none;

	// VTP Domain
	else if (strcmp(command.part[1], "domain") == 0)
		strncpy(nipper->ios->vtpDomain, command.part[2], sizeof(nipper->ios->vtpDomain) -1);

	// Debug (lines not processed)
	else if (nipper->linesnotprocessed == true)
		printf("%s\n", line);
}


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

// This file contains the general processing code for Passport devices


// Software Version...
void processSoftwarePAS(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct ciscoCommand command;
	int tempInt = 0;
	int offset = 0;

	if (nipper->debugMode == true)
		printf("Software Version Line: %s\n", line);

	// Split the command line up
	command = splitLine(line);

	// Copy Box Type
	strncpy(nipper->version, command.part[4], sizeof(nipper->version) - 1);

	// Major...
	while ((command.part[4][tempInt] != '.') && (tempInt < strlen(nipper->version)))
		tempInt++;
	if (command.part[4][tempInt] == '.')
		command.part[4][tempInt] = 0;
	nipper->versionMajor = atoi(command.part[4]);
	tempInt++;

	// Minor...
	if (tempInt < strlen(nipper->version))
	{
		offset = tempInt;
		while ((command.part[4][tempInt] != '.') && (tempInt < strlen(nipper->version)))
			tempInt++;
		if (command.part[4][tempInt] == '.')
			command.part[4][tempInt] = 0;
		nipper->versionMinor = atoi(command.part[4] + offset);
		tempInt++;
	}

	// Revision...
	if (tempInt < strlen(nipper->version))
	{
		offset = tempInt;
		while ((command.part[4][tempInt] != '.') && (tempInt < strlen(nipper->version)))
			tempInt++;
		if (command.part[4][tempInt] == '.')
			command.part[4][tempInt] = 0;
		nipper->versionRevision = atoi(command.part[4] + offset);
		tempInt++;
	}

	// Revision Minor...
	if (tempInt < strlen(nipper->version))
		nipper->versionRevisionMinor = atoi(command.part[4] + tempInt);
}


// Box Type...
void processBoxTypePAS(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct ciscoCommand command;

	if (nipper->debugMode == true)
		printf("Box Type Line: %s\n", line);

	// Split the command line up
	command = splitLine(line);

	// Copy Box Type
	strncpy(nipper->pas->boxType, command.part[4], sizeof(nipper->pas->boxType) - 1);
}


// Monitor Version...
void processMonitorPAS(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct ciscoCommand command;

	if (nipper->debugMode == true)
		printf("Monitor Version Line: %s\n", line);

	// Split the command line up
	command = splitLine(line);

	// Copy Box Type
	strncpy(nipper->pas->monitorVersion, command.part[4], sizeof(nipper->pas->monitorVersion) - 1);
}

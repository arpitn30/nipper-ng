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


// Process SSH Service Lines
void processSOSSSH(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct ciscoCommand command;

	// Debug Output
	if (nipper->debugMode == true)
		printf("SSH Line: %s\n", line);

	// Init
	command = splitLine(line);

	// Version?
	if (strcasecmp(command.part[2], "version") == 0)
	{
		if (strcasecmp(command.part[3], "v1") == 0)
			nipper->sos->sshVersion = 1;
		else if (strcasecmp(command.part[3], "v2") == 0)
			nipper->sos->sshVersion = 2;
	}

	// Enabled?
	else if (strcasecmp(command.part[2], "enable") == 0)
		nipper->sos->sshEnabled = true;

	// SSH v1 Key Gen Time
	else if (strcasecmp(command.part[2], "key-gen-time") == 0)
		nipper->sos->sshKeyGenTime = atoi(command.part[3]);

	// SSH v2 Public Key
	else if (strcasecmp(command.part[2], "pub-key") == 0)
		strncpy(nipper->sos->sshPublicKey, command.part[3], sizeof(nipper->sos->sshPublicKey) - 1);
}


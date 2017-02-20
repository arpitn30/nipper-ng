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

struct sshAccessConfig
{
	char ipAddress[32];
	char netMask[32];
	char interface[32];
	struct sshAccessConfig *next;
};


struct sshPIXConfig
{
	int version;
	int timeout;
	struct sshAccessConfig *access;
};


// Process fixup
void processPIXSSH(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct ciscoCommand command;
	struct sshAccessConfig *sshPointer = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("SSH Line: %s\n", line);
	}

	// If structure doesn't exist
	if (nipper->pix->ssh == 0)
	{
		nipper->pix->ssh = malloc(sizeof(struct sshPIXConfig));
		memset(nipper->pix->ssh, 0, sizeof(struct sshPIXConfig));
		nipper->pix->ssh->timeout = 5;
	}

	// Init
	command = splitLine(line);

	// Timeout
	if (strcmp(command.part[1], "timeout") == 0)
		nipper->pix->ssh->timeout = atoi(command.part[2]);

	// Version
	else if (strcmp(command.part[1], "version") == 0)
		nipper->pix->ssh->version = atoi(command.part[2]);

	// Management IP
	else if (command.parts == 4)
	{
		// Init...
		if (nipper->pix->ssh->access == 0)
		{
			nipper->pix->ssh->access = malloc(sizeof(struct sshAccessConfig));
			sshPointer = nipper->pix->ssh->access;
		}
		else
		{
			sshPointer = nipper->pix->ssh->access;
			while (sshPointer->next != 0)
			  sshPointer = sshPointer->next;
			sshPointer->next = malloc(sizeof(struct sshAccessConfig));
			sshPointer = sshPointer->next;
		}
		memset(sshPointer, 0, sizeof(struct sshAccessConfig));
		strcpy(sshPointer->interface, "Any except outside");

		// Set...
		strncpy(sshPointer->ipAddress, command.part[1], sizeof(sshPointer->ipAddress) - 1);
		strncpy(sshPointer->netMask, command.part[2], sizeof(sshPointer->netMask) - 1);
		if (command.parts == 4)
			strncpy(sshPointer->interface, command.part[3], sizeof(sshPointer->interface) - 1);
	}
}


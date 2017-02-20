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


// Enable password(s)
struct enablePIXPassword
{
	char passwordEncrypted[64];
	int level;
	struct enablePIXPassword *next;
};


struct usernamePIX
{
	char username[16];
	char passwordEncrypted[64];
	int encryption;
	int level;
	struct usernamePIX *next;
};


// Process enable
void processEnablePIX(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct ciscoCommand command;
	struct enablePIXPassword *enablePIXPointer = 0;
	int tempInt = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Enable Line: %s\n", line);
	}

	// Init
	command = splitLine(line);

	// Is it an enable password?
	if (strncmp(line, "enable password ", 16) == 0)
	{
		// Is this the first enable password?
		if (nipper->pix->enable == 0)
		{
			nipper->pix->enable = malloc(sizeof(struct enablePIXPassword));
			enablePIXPointer = nipper->pix->enable;
		}
		else
		{
			enablePIXPointer = nipper->pix->enable;
			while (enablePIXPointer->next != 0)
				enablePIXPointer = enablePIXPointer->next;
			enablePIXPointer->next = malloc(sizeof(struct enablePIXPassword));
			enablePIXPointer = enablePIXPointer->next;
		}

		// Init
		memset(enablePIXPointer, 0, sizeof(struct enablePIXPassword));
		enablePIXPointer->level = 15;

		// Password
		strncpy(enablePIXPointer->passwordEncrypted, command.part[2], sizeof(enablePIXPointer->passwordEncrypted) - 1);
		addJohnPassword(nipper, "Enable", enablePIXPointer->passwordEncrypted);

		// Get options
		tempInt = 3;
		if (tempInt < command.parts)
		{
			// Level
			if (strcmp(command.part[tempInt], "level") == 0)
			{
				tempInt++;
				enablePIXPointer->level = atoi(command.part[tempInt]);
			}

			tempInt++;
		}
	}

	// If it is a passwd
	else if (strncmp("passwd ", line, 7) == 0)
	{
		strncpy(nipper->pix->password, command.part[1], sizeof(nipper->pix->password) - 1);
		addJohnPassword(nipper, "LoginPassword", nipper->pix->password);
	}
}


// Process Username
void processPIXUsername(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct ciscoCommand command;
	struct usernamePIX *usernamePIXPointer = 0;
	int tempInt = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Username Line: %s\n", line);
	}

	// Is it the first?
	if (nipper->pix->username == 0)
	{
		nipper->pix->username = malloc(sizeof(struct usernamePIX));
		usernamePIXPointer = nipper->pix->username;
	}
	else
	{
		usernamePIXPointer = nipper->pix->username;
		while (usernamePIXPointer->next != 0)
			usernamePIXPointer = usernamePIXPointer->next;
		usernamePIXPointer->next = malloc(sizeof(struct usernamePIX));
		usernamePIXPointer = usernamePIXPointer->next;
	}

	// Init
	memset(usernamePIXPointer, 0, sizeof(struct usernamePIX));
	command = splitLine(line);
	usernamePIXPointer->level = 2;

	// Username
	strncpy(usernamePIXPointer->username, command.part[1], sizeof(usernamePIXPointer->username) - 1);

	// Other options...
	tempInt = 2;
	while (tempInt < command.parts)
	{
		// No password
		if (strcmp(command.part[tempInt], "nopassword") == 0)
			usernamePIXPointer->encryption = encrypt_none;
		
		// Password
		else if (strcmp(command.part[tempInt], "password") == 0)
		{
			strncpy(usernamePIXPointer->passwordEncrypted, command.part[tempInt +1], sizeof(usernamePIXPointer->passwordEncrypted) - 1);
			tempInt++;
		}

		// Encrypted
		else if (strcmp(command.part[tempInt], "encrypted") == 0)
			usernamePIXPointer->encryption = encrypt_pix;

		// MSChap
		else if (strcmp(command.part[tempInt], "mschap") == 0)
			usernamePIXPointer->encryption = encrypt_mschap;

		// NT Encrypted
		else if (strcmp(command.part[tempInt], "nt-encrypted") == 0)
			usernamePIXPointer->encryption = encrypt_ntenc;

		// Level
		else if (strcmp(command.part[tempInt], "privilege") == 0)
			usernamePIXPointer->level = atoi(command.part[tempInt +1]);

		tempInt++;
	}

	// If password is encrypted
	if (usernamePIXPointer->encryption == encrypt_pix)
		addJohnPassword(nipper, usernamePIXPointer->username, usernamePIXPointer->passwordEncrypted);
}


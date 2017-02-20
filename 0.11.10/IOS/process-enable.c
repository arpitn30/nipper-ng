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
struct enablePassword
{
	char password[128];
	char passwordEncrypted[128];
	int secret;						// true or false
	int level;
	int encryption;					// encrypt_type7, encrypt_md5...
	int weak;						// true or false
	int dictionary;					// true or false
	struct enablePassword *next;
};


// Process enable
void processEnable(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct enablePassword *enablePointer = 0;
	struct ciscoCommand command;
	int tempInt = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Enable Line: %s\n", line);
	}

	// Create storage for enable...
	enablePointer = malloc(sizeof(struct enablePassword));
	memset(enablePointer, 0, sizeof(struct enablePassword));

	// Sort out pointers...
	enablePointer->next = nipper->ios->enable;
	nipper->ios->enable = enablePointer;

	// Init
	command = splitLine(line);
	tempInt = 1;
	enablePointer->weak = false;
	enablePointer->dictionary = false;
	enablePointer->secret = false;
	enablePointer->level = 15;

	// secret
	if (strncmp(command.part[tempInt], "secret", 6) == 0)
	{
		enablePointer->secret = true;
		tempInt++;
	}

	// password
	if (strncmp(command.part[tempInt], "password", 8) == 0)
		tempInt++;

	if (strncmp(command.part[tempInt], "level ", 6) == 0)
	{
		tempInt++;
		enablePointer->level = atoi(command.part[tempInt]);
		tempInt++;
	}

	// Password type
	switch (command.part[tempInt][0])
	{
		case '7':
			enablePointer->encryption = encrypt_type7;
			if (password7(command.part[tempInt + 1], enablePointer->password, sizeof(enablePointer->password), nipper->debugMode) != 0)
				strcpy(enablePointer->password, "<unknown>");
			strncpy(enablePointer->passwordEncrypted, command.part[tempInt + 1], sizeof(enablePointer->passwordEncrypted));
			break;

		case '5':
			enablePointer->encryption = encrypt_md5;
			strcpy(enablePointer->password, "<unknown>");
			strncpy(enablePointer->passwordEncrypted, command.part[tempInt + 1], sizeof(enablePointer->passwordEncrypted));
			addJohnPassword(nipper, "enable" , enablePointer->passwordEncrypted);
			break;

		case '0':
			enablePointer->encryption = encrypt_none;
			strncpy(enablePointer->password, command.part[tempInt + 1], sizeof(enablePointer->password));
			strcpy(enablePointer->passwordEncrypted, "");
			break;

		default:
			if (command.parts == tempInt + 1)
			{
				enablePointer->encryption = encrypt_none;
				strncpy(enablePointer->password, command.part[command.parts - 1], sizeof(enablePointer->password));
				strcpy(enablePointer->passwordEncrypted, "");
			}
			else
			{
				enablePointer->encryption = encrypt_unknown;
				strcpy(enablePointer->password, "<unknown>");
				strncpy(enablePointer->passwordEncrypted, command.part[command.parts - 1], sizeof(enablePointer->passwordEncrypted));
			}
			break;
	}

	// Check Passwords...
	if ((strcmp(enablePointer->password, "<unknown>") != 0) && (strlen(enablePointer->password) != 0))
	{
		if (simplePassword(enablePointer->password, nipper) == true)
		{
			nipper->simplePasswords++;
			enablePointer->dictionary = true;
		}
		if (passwordStrength(enablePointer->password, nipper) == false)
		{
			nipper->passwordStrengths++;
			enablePointer->weak = true;
		}
	}
}



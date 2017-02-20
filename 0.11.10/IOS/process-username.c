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


// Username
struct usernameList
{
	char username[128];
	char password[128];
	char passwordEncrypted[128];
	int secret;						// true or false
	int privilage;
	int encryption;					// encrypt_type7, encrypt_md5...
	int weak;
	int dictionary;
	struct usernameList *next;
};


// Process Username
void processUsername(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct ciscoCommand command;
	struct usernameList *usernamePointer = 0;
	int tempInt = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Username Line: %s\n", line);
	}

	// Create structure
	usernamePointer = malloc(sizeof(struct usernameList));
	memset(usernamePointer, 0, sizeof(struct usernameList));

	// Sort out pointers
	usernamePointer->next = nipper->ios->username;
	nipper->ios->username = usernamePointer;

	// Init
	command = splitLine(line);
	tempInt = 1;
	usernamePointer->weak = false;
	usernamePointer->dictionary = false;

	// username
	strncpy(usernamePointer->username, command.part[tempInt], sizeof(usernamePointer->username));
	tempInt++;

	// privilage
	if (strncmp(command.part[tempInt], "privilege", 9) == 0)
	{
		tempInt++;
		usernamePointer->privilage = atoi(command.part[tempInt]);
		tempInt++;
	}
	else
		usernamePointer->privilage = 1;

	// secret
	if (strncmp(command.part[tempInt], "secret", 6) == 0)
		usernamePointer->secret = true;

	else
		usernamePointer->secret = false;
	tempInt++;

	switch(command.part[tempInt][0])
	{
		case '7':
			usernamePointer->encryption = encrypt_type7;
			if (password7(command.part[command.parts - 1], usernamePointer->password, sizeof(usernamePointer->password), nipper->debugMode) != 0)
				strcpy(usernamePointer->password, "<unknown>");
			strncpy(usernamePointer->passwordEncrypted, command.part[command.parts - 1], sizeof(usernamePointer->passwordEncrypted));
			break;
		case '5':
			usernamePointer->encryption = encrypt_md5;
			strcpy(usernamePointer->password, "<unknown>");
			strncpy(usernamePointer->passwordEncrypted, command.part[command.parts - 1], sizeof(usernamePointer->passwordEncrypted));
			addJohnPassword(nipper, usernamePointer->username , usernamePointer->passwordEncrypted);
			break;
		case '0':
			usernamePointer->encryption = encrypt_none;
			strncpy(usernamePointer->password, command.part[command.parts - 1], sizeof(usernamePointer->password));
			strcpy(usernamePointer->passwordEncrypted, "");
			break;
		default:
			if (command.parts == 4)
			{
				usernamePointer->encryption = encrypt_none;
				strncpy(usernamePointer->password, command.part[command.parts - 1], sizeof(usernamePointer->password));
				strcpy(usernamePointer->passwordEncrypted, "");
			}
			else
			{
				usernamePointer->encryption = encrypt_unknown;
				strcpy(usernamePointer->password, "<unknown>");
				strncpy(usernamePointer->passwordEncrypted, command.part[command.parts - 1], sizeof(usernamePointer->passwordEncrypted));
			}
			break;
	}
	if ((strcmp(usernamePointer->password, "<unknown>") != 0) && (strlen(usernamePointer->password) != 0))
	{
		if (simplePassword(usernamePointer->password, nipper) == true)
		{
			nipper->simplePasswords++;
			usernamePointer->dictionary = true;
		}
		if (passwordStrength(usernamePointer->password, nipper) == false)
		{
			nipper->passwordStrengths++;
			usernamePointer->weak = true;
		}
	}
}



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


struct keyConfig
{
	int keyNumber;
	char key[64];
	int weak;
	int dictionary;
	struct keyConfig *next;
};


struct keyChain
{
	char name[32];
	struct keyConfig *key;
	struct keyChain *next;
};


// Process Key Chain
void processKeyChain(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct keyChain *keyChainPointer = 0;
	struct keyConfig *keyPointer = 0;
	struct ciscoCommand command;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Key Chain Line: %s\n", line);
	}

	// Init
	command = splitLine(line);

	// Is this the first key chain?
	if (nipper->ios->chain == 0)
	{
		keyChainPointer = malloc(sizeof(struct keyChain));
		memset(keyChainPointer, 0, sizeof(struct keyChain));

		// Pointers
		nipper->ios->chain = keyChainPointer;
		keyChainPointer->next = 0;

		// Init
		strncpy(keyChainPointer->name, command.part[2], sizeof(keyChainPointer->name));
		keyChainPointer->key = 0;
	}

	// other key chains already exist
	else
	{
		// Find last key chain
		keyChainPointer = nipper->ios->chain;
		while (keyChainPointer->next != 0)
			keyChainPointer = keyChainPointer->next;

		// create new
		keyChainPointer->next = malloc(sizeof(struct keyChain));
		memset(keyChainPointer->next, 0, sizeof(struct keyChain));

		// Pointers
		keyChainPointer = keyChainPointer->next;
		keyChainPointer->next = 0;

		// Init
		strncpy(keyChainPointer->name, command.part[2], sizeof(keyChainPointer->name));
		keyChainPointer->key = 0;
	}

	// Get keys
	readLine(nipper->input, line, nipper->maxSize);
	while ((feof(nipper->input) == 0) && (line[0] == ' '))
	{
		// Debug
		if (nipper->debugMode == true)
		{
			printf("Key Chain Line: %s\n", line);
		}

		// Init
		command = splitLine(line);

		// Key
		if (strcmp(command.part[0], "key") == 0)
		{
			// Is it the first key?
			if (keyChainPointer->key == 0)
			{
				keyPointer = malloc(sizeof(struct keyConfig));

				// Pointers
				keyChainPointer->key = keyPointer;
			}

			// Other keys exist
			else
			{
				keyPointer = keyChainPointer->key;
				while (keyPointer->next != 0)
					keyPointer = keyPointer->next;
				keyPointer->next = malloc(sizeof(struct keyConfig));

				// Pointers
				keyPointer = keyPointer->next;
			}

			// Init
			memset(keyPointer, 0, sizeof(struct keyConfig));
			keyPointer->keyNumber = atoi(command.part[1]);
			strcpy(keyPointer->key, "");
			keyPointer->weak = false;
			keyPointer->dictionary = false;
		}

		// Key String
		else if (strcmp(command.part[0], "key-string") == 0)
		{
			strncpy(keyPointer->key, command.part[1], sizeof(keyPointer->key));
			if (simplePassword(keyPointer->key, nipper) == true)
			{
				nipper->simplePasswords++;
				keyPointer->dictionary = true;
			}
			if (passwordStrength(keyPointer->key, nipper) == false)
			{
				nipper->passwordStrengths++;
				keyPointer->weak = true;
			}
		}

		// Get next line
		readLine(nipper->input, line, nipper->maxSize);
	}
}



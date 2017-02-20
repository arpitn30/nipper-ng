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


// TACACS config
struct tacacsConfig
{
	char key[128];
	char keyEncrypted[128];
	int encryption;
	int weak;
	int dictionary;
	struct host *host;
};


// Process TACACS
void processTacacs(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct host *tacacsHostPointer = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("TACACS Line: %s\n", line);
	}

	// Create logging structure
	if (nipper->ios->tacacs == 0)
	{
		nipper->ios->tacacs = malloc(sizeof(struct tacacsConfig));
		memset(nipper->ios->tacacs, 0, sizeof(struct tacacsConfig));

		// init
		strcpy(nipper->ios->tacacs->key, "");
		nipper->ios->tacacs->host = 0;
		nipper->ios->tacacs->dictionary = false;
		nipper->ios->tacacs->weak = false;
	}

	// Key...
	if (strncmp("tacacs-server key ", line, 18) == 0)
	{
		switch (line[18])
		{
			case '7':
				nipper->ios->tacacs->encryption = encrypt_type7;
				if (password7(line+20, nipper->ios->tacacs->key, sizeof(nipper->ios->tacacs->key), nipper->debugMode) != 0)
					strcpy(nipper->ios->tacacs->key, "<unknown>");
				strncpy(nipper->ios->tacacs->keyEncrypted, line + 20, sizeof(nipper->ios->tacacs->keyEncrypted));
				break;

			case '5':
				nipper->ios->tacacs->encryption = encrypt_md5;
				strcpy(nipper->ios->tacacs->key, "<unknown>");
				strncpy(nipper->ios->tacacs->keyEncrypted, line + 20, sizeof(nipper->ios->tacacs->keyEncrypted));
				addJohnPassword(nipper, "tacacs", nipper->ios->tacacs->keyEncrypted);
				break;

			case '0':
				nipper->ios->tacacs->encryption = encrypt_none;
				strncpy(nipper->ios->tacacs->key, line + 20, sizeof(nipper->ios->tacacs->key));
				strcpy(nipper->ios->tacacs->keyEncrypted, "");
				break;

			default:
				nipper->ios->tacacs->encryption = encrypt_none;
				strncpy(nipper->ios->tacacs->key, line + 18, sizeof(nipper->ios->tacacs->key));
				strcpy(nipper->ios->tacacs->keyEncrypted, "");
				break;
		}
		if ((strcmp(nipper->ios->tacacs->key, "<unknown>") != 0) && (strlen(nipper->ios->tacacs->key) != 0))
		{
			if (simplePassword(nipper->ios->tacacs->key, nipper) == true)
			{
				nipper->simplePasswords++;
				nipper->ios->tacacs->dictionary = true;
			}
			if (passwordStrength(nipper->ios->tacacs->key, nipper) == false)
			{
				nipper->passwordStrengths++;
				nipper->ios->tacacs->weak = true;
			}
		}
	}

	// Host...
	else if (strncmp("tacacs-server host ", line, 19) == 0)
	{
		// Create struct
		tacacsHostPointer = malloc(sizeof(struct host));
		memset(tacacsHostPointer, 0, sizeof(struct host));

		// Pointers
		tacacsHostPointer->next = nipper->ios->tacacs->host;
		nipper->ios->tacacs->host = tacacsHostPointer;

		// Copy host
		strncpy(tacacsHostPointer->server, line + 19, sizeof(tacacsHostPointer->server));
	}
}

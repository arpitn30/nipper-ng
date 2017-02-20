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


#define aaa_radius 0
#define aaa_tacacs 1
#define aaa_kerberos 2


// AAA Server
struct aaaServer
{
	char server[32];
	int authPort;
	int acctPort;
	char key[128];
	char keyEncrypted[128];
	int encryption;
	int weak;
	int dictionary;
	struct aaaServer *next;
};


// AAA Group Server
struct aaaGroupServer
{
	int type;						// aaa_radius, aaa_tacacs or aaa_kerberos
	char username[64];
	struct aaaServer *server;
	struct aaaGroupServer *next;
};


// AAA
struct aaaConfig
{
	struct aaaGroupServer *groupServer;
};


// Process AAA
void processAaa(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct ciscoCommand command;
	struct aaaGroupServer *groupServerPointer = 0;
	struct aaaServer *serverPointer = 0;
	int tempInt = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("AAA Line: %s\n", line);
	}

	// If there is no aaa config, create one
	if (nipper->ios->aaa == 0)
	{
		// Create
		nipper->ios->aaa = malloc(sizeof(struct aaaConfig));

		// Init
		memset(nipper->ios->aaa, 0, sizeof(struct aaaConfig));
	}

	// Init
	command = splitLine(line);

	// If group server line
	if (strncmp("aaa group server ", line, 17) == 0)
	{
		// Create
		groupServerPointer = malloc(sizeof(struct aaaGroupServer));
		memset(groupServerPointer, 0, sizeof(struct aaaGroupServer));

		// Sort out pointers
		groupServerPointer->next = nipper->ios->aaa->groupServer;
		nipper->ios->aaa->groupServer = groupServerPointer;

		// Init
		groupServerPointer->server = 0;

		// Type of group server
		if (strncmp(command.part[3], "radius", 6) == 0)
			groupServerPointer->type = aaa_radius;
		else if (strncmp(command.part[3], "tacacs", 6) == 0)
			groupServerPointer->type = aaa_tacacs;
		else if (strncmp(command.part[3], "kerberos", 8) == 0)
			groupServerPointer->type = aaa_kerberos;

		// Username
		strncpy(groupServerPointer->username, command.part[command.parts - 1], sizeof(groupServerPointer->username));

		// Loop through aaa group server lines
		readLine(nipper->input, line, nipper->maxSize);
		while ((feof(nipper->input) == 0) && (line[0] == ' '))
		{
			// Debug
			if (nipper->debugMode == true)
			{
				printf("AAA Line: %s\n", line);
			}

			// Init
			command = splitLine(line);

			// Get server-private line
			if (strncmp(command.part[0], "server-private", 14) == 0)
			{
				// Create structure
				serverPointer = malloc(sizeof(struct aaaServer));
				memset(serverPointer, 0, sizeof(struct aaaServer));

				// Sort out pointers
				serverPointer->next = groupServerPointer->server;
				groupServerPointer->server = serverPointer;

				// Init
				strcpy(serverPointer->server, "");
				serverPointer->authPort = -1;
				serverPointer->acctPort = -1;
				strcpy(serverPointer->key, "");
				strcpy(serverPointer->keyEncrypted, "");
				serverPointer->weak = false;
				serverPointer->dictionary = false;
				serverPointer->encryption = -1;

				// Get server
				strncpy(serverPointer->server, command.part[1], sizeof(serverPointer->server));
				tempInt = 2;

				// Get parameters
				while (tempInt < command.parts)
				{
					// Auth port
					if (strncmp(command.part[tempInt], "auth-port", 9) == 0)
					{
						tempInt++;
						serverPointer->authPort = atoi(command.part[tempInt]);
					}

					// Acct Port
					else if ((strncmp(command.part[tempInt], "acct-port", 9) == 0) && (command.parts > tempInt))
					{
						tempInt++;
						serverPointer->acctPort = atoi(command.part[tempInt]);
					}

					// Key
					else if ((strncmp(command.part[tempInt], "key", 3) == 0) && (command.parts > tempInt))
					{
						tempInt++;
						// Password type
						switch (command.part[tempInt][0])
						{
							case '7':
								serverPointer->encryption = encrypt_type7;
								if (password7(command.part[tempInt + 1], serverPointer->key, sizeof(serverPointer->key), nipper->debugMode) != 0)
									strcpy(serverPointer->key, "<unknown>");
								strncpy(serverPointer->keyEncrypted, command.part[tempInt + 1], sizeof(serverPointer->keyEncrypted));
								break;

							case '5':
								serverPointer->encryption = encrypt_md5;
								strcpy(serverPointer->key, "<unknown>");
								strncpy(serverPointer->keyEncrypted, command.part[tempInt + 1], sizeof(serverPointer->keyEncrypted));
								addJohnPassword(nipper, serverPointer->server , serverPointer->keyEncrypted);
								break;

							case '0':
								serverPointer->encryption = encrypt_none;
								strncpy(serverPointer->key, command.part[tempInt + 1], sizeof(serverPointer->key));
								strcpy(serverPointer->keyEncrypted, "");
								break;

							default:
								if (command.parts == tempInt + 2)
								{
									serverPointer->encryption = encrypt_none;
									strncpy(serverPointer->key, command.part[command.parts - 1], sizeof(serverPointer->key));
									strcpy(serverPointer->keyEncrypted, "");
								}
								else
								{
									serverPointer->encryption = encrypt_unknown;
									strcpy(serverPointer->key, "<unknown>");
									strncpy(serverPointer->keyEncrypted, command.part[command.parts - 1], sizeof(serverPointer->keyEncrypted));
								}
								break;
						}
						if ((strcmp(serverPointer->key, "<unknown>") != 0) && strlen(serverPointer->key) != 0)
						{
							if (simplePassword(serverPointer->key, nipper) == true)
							{
								nipper->simplePasswords++;
								serverPointer->dictionary = true;
							}
							if (passwordStrength(serverPointer->key, nipper) == false)
							{
								nipper->passwordStrengths++;
								serverPointer->weak = true;
							}
						}
					}

					// Increment
					tempInt++;
				}
			}

			// Read next line
			readLine(nipper->input, line, nipper->maxSize);
		}
	}
}

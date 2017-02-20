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

#define line_console 0
#define line_vty 1
#define line_aux 2
#define line_tty 3

#define login_allowed 0
#define login_disabled 1
#define login_local 2
#define login_authentication 3

// Line
struct lineConfig
{
	// Basics...
	int lineType;					// line_console...
	int lineNumberStart;
	int lineNumberEnd;

	// Security...
	int login;						// login_disabled...
	int exec;						// true (default) or false
	int authorization;				// true or false (default)
	int callback;					// true or false (default)
	char password[81];
	char passwordEncrypted[128];
	int encryption;					// encrypt_type7, encrypt_md5...
	char aclIn[65];
	char aclOut[65];

	// Accounting / Logging...
	int accounting;					// true or false (default)

	// Access Types...
	int ssh;						// true or false (default)
	int telnet;						// true (default) or false 

	// Timeouts...
	int execTimeout;				// Exec timeout in seconds, 0 = no timeout (default)
	int absoluteTimeout;
	int sessionTimeout;
	int timeout;

	// Flags...
	int weak;
	int dictionary;

	struct lineConfig *next;
};


// Process Line
void processLine(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct lineConfig *linePointer = 0;
	struct ciscoCommand command;
	fpos_t filePosition;
	int tempInt = 0;

	while ((line[0] != '!') && (feof(nipper->input) == 0))
	{
		// Debug
		if (nipper->debugMode == true)
		{
			printf("Line Line: %s\n", line);
		}

		// Init
		command = splitLine(line);

		// If it is a new line
		if (strcmp(command.part[0], "line") == 0)
		{
			// If this is the first line...
			if (nipper->ios->line == 0)
			{
				nipper->ios->line = malloc(sizeof(struct lineConfig));
				linePointer = nipper->ios->line;
			}

			// Else find last line...
			else
			{
				linePointer = nipper->ios->line;
				while (linePointer->next != 0)
					linePointer = linePointer->next;
				linePointer->next = malloc(sizeof(struct lineConfig));
				linePointer = linePointer->next;
			}

			// Init the new line structure
			memset(linePointer, 0, sizeof(struct lineConfig));

			// Set the new line to the default settings
			linePointer->login = login_allowed;
			linePointer->exec = true;
			linePointer->authorization = false;
			linePointer->callback = false;
			linePointer->encryption = encrypt_none;
			linePointer->accounting = false;
			linePointer->ssh = false;
			linePointer->telnet = true;

			// Set line type
			if (strcmp(command.part[1], "tty") == 0)
				linePointer->lineType = line_tty;
			else if (strcmp(command.part[1], "vty") == 0)
				linePointer->lineType = line_vty;
			else if ((strcmp(command.part[1], "aux") == 0) || (strcmp(command.part[1], "auxiliary") == 0))
				linePointer->lineType = line_aux;
			else if ((strcmp(command.part[1], "con") == 0) || (strcmp(command.part[1], "console") == 0))
				linePointer->lineType = line_console;

			// Set line start
			linePointer->lineNumberStart = atoi(command.part[2]);
			if (command.parts == 4)
				linePointer->lineNumberEnd = atoi(command.part[3]);
		}

		// Exec
		else if (strcmp(command.part[0], "exec") == 0)
			linePointer->exec = true;

		// No Exec
		else if ((strcmp(command.part[0], "no") == 0) && (strcmp(command.part[1], "exec") == 0))
			linePointer->exec = false;

		// Local Login
		else if ((strcmp(command.part[0], "login") == 0) && (strcmp(command.part[1], "local") == 0))
			linePointer->login = login_local;

		// Authentication Login
		else if ((strcmp(command.part[0], "login") == 0) && (strcmp(command.part[1], "authentication") == 0))
			linePointer->login = login_authentication;

		// Login
		else if (strcmp(command.part[0], "login") == 0)
			linePointer->login = login_allowed;

		// No Login
		else if ((strcmp(command.part[0], "no") == 0) && (strcmp(command.part[1], "login") == 0))
		{
			linePointer->login = login_allowed;
			memset(linePointer->password, 0, sizeof(linePointer->password));
			memset(linePointer->passwordEncrypted, 0, sizeof(linePointer->passwordEncrypted));
			linePointer->encryption = encrypt_none;
		}

		// Password
		else if (strcmp(command.part[0], "password") == 0)
		{
			switch(command.part[1][0])
			{
				case '7':
					linePointer->encryption = encrypt_type7;
					if (password7(command.part[command.parts - 1], linePointer->password, sizeof(linePointer->password), nipper->debugMode) != 0)
						strcpy(linePointer->password, "<unknown>");
					strncpy(linePointer->passwordEncrypted, command.part[command.parts - 1], sizeof(linePointer->passwordEncrypted));
					break;
				case '5':
					linePointer->encryption = encrypt_md5;
					strcpy(linePointer->password, "<unknown>");
					strncpy(linePointer->passwordEncrypted, command.part[command.parts - 1], sizeof(linePointer->passwordEncrypted));
					addJohnPassword(nipper, "line", linePointer->passwordEncrypted);
					break;
				case '0':
					linePointer->encryption = encrypt_none;
					strncpy(linePointer->password, command.part[command.parts - 1], sizeof(linePointer->password));
					strcpy(linePointer->passwordEncrypted, "");
					break;
				default:
					if (command.parts == 2)
					{
						linePointer->encryption = encrypt_none;
						strncpy(linePointer->password, command.part[command.parts - 1], sizeof(linePointer->password));
						strcpy(linePointer->passwordEncrypted, "");
					}
					else
					{
						linePointer->encryption = encrypt_unknown;
						strcpy(linePointer->password, "<unknown>");
						strncpy(linePointer->passwordEncrypted, command.part[command.parts - 1], sizeof(linePointer->passwordEncrypted));
					}
					break;
			}
			if ((strcmp(linePointer->password, "<unknown>") != 0) && (strlen(linePointer->password) != 0))
			{
				if (simplePassword(linePointer->password, nipper) == true)
				{
					nipper->simplePasswords++;
					linePointer->dictionary = true;
				}
				if (passwordStrength(linePointer->password, nipper) == false)
				{
					nipper->passwordStrengths++;
					linePointer->weak = true;
				}
			}
		}

		// No Password
		else if ((strcmp(command.part[0], "no") == 0) && (strcmp(command.part[1], "password") == 0))
		{
			linePointer->login = login_disabled;
			memset(linePointer->password, 0, sizeof(linePointer->password));
			memset(linePointer->passwordEncrypted, 0, sizeof(linePointer->passwordEncrypted));
			linePointer->encryption = encrypt_none;
		}

		// Access-Class In
		else if ((strcmp(command.part[0], "access-class") == 0) && (strcmp(command.part[2], "in") == 0))
			strncpy(linePointer->aclIn, command.part[1], sizeof(linePointer->aclIn) -1);

		// Access-Class Out
		else if ((strcmp(command.part[0], "access-class") == 0) && (strcmp(command.part[2], "out") == 0))
			strncpy(linePointer->aclOut, command.part[1], sizeof(linePointer->aclOut) -1);

		// Callback
		else if (strcmp(command.part[0], "callback") == 0)
			linePointer->callback = true;

		// No Callback
		else if ((strcmp(command.part[0], "no") == 0) && (strcmp(command.part[1], "callback") == 0))
			linePointer->callback = false;

		// Transport input
		else if ((strcmp(command.part[0], "transport") == 0) && (strcmp(command.part[1], "input") == 0))
		{
			tempInt = 2;
			linePointer->telnet = false;
			linePointer->ssh = false;
			while (tempInt < command.parts)
			{
				if (strcmp(command.part[tempInt], "all") == 0)
				{
					linePointer->telnet = true;
					linePointer->ssh = true;
				}
				else if (strcmp(command.part[tempInt], "ssh") == 0)
					linePointer->ssh = true;
				else if (strcmp(command.part[tempInt], "telnet") == 0)
					linePointer->telnet = true;
				tempInt++;
			}
		}

		// timeout
		else if (strcmp(command.part[0], "timeout") == 0)
		{
			linePointer->timeout = atoi(command.part[1]) * 60;
			if (command.parts == 3)
				linePointer->timeout = linePointer->timeout + atoi(command.part[2]);
		}

		// No Timeout
		else if ((strcmp(command.part[0], "no") == 0) && (strcmp(command.part[1], "timeout") == 0))
			linePointer->timeout = 0;

		// Exec-timeout
		else if (strcmp(command.part[0], "exec-timeout") == 0)
		{
			linePointer->execTimeout = atoi(command.part[1]) * 60;
			if (command.parts == 3)
				linePointer->execTimeout = linePointer->execTimeout + atoi(command.part[2]);
		}

		// No Exec Timeout
		else if ((strcmp(command.part[0], "no") == 0) && (strcmp(command.part[1], "exec-timeout") == 0))
			linePointer->execTimeout = 0;

		// session-timeout
		else if (strcmp(command.part[0], "session-timeout") == 0)
		{
			linePointer->sessionTimeout = atoi(command.part[1]) * 60;
			if (command.parts == 3)
				linePointer->sessionTimeout = linePointer->sessionTimeout + atoi(command.part[2]);
		}

		// No session Timeout
		else if ((strcmp(command.part[0], "no") == 0) && (strcmp(command.part[1], "session-timeout") == 0))
			linePointer->sessionTimeout = 0;

		// Absolute-timeout
		else if (strcmp(command.part[0], "absolute-timeout") == 0)
		{
			linePointer->absoluteTimeout = atoi(command.part[1]) * 60;
			if (command.parts == 3)
				linePointer->absoluteTimeout = linePointer->absoluteTimeout + atoi(command.part[2]);
		}

		// No Absolute Timeout
		else if ((strcmp(command.part[0], "no") == 0) && (strcmp(command.part[1], "absolute-timeout") == 0))
			linePointer->absoluteTimeout = 0;

		// Debug (lines not processed)
		else if (nipper->linesnotprocessed == true)
			printf("%s\n", line);

		// Get next line...
		fgetpos(nipper->input, &filePosition);
		readLine(nipper->input, line, nipper->maxSize);
	}

	// Set to previous position...
	fsetpos(nipper->input, &filePosition);
}



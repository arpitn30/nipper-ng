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


// FTP
struct ftpConfig
{
	char username[128];
	char password[128];
	char passwordEncrypted[128];
	int encryption;
	int weak;
	int dictionary;
	struct netInterface *interface;
};


// Process FTP
void processFtp(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct netInterface *interfacePointer = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("FTP Line: %s\n", line);
	}

	// Check to see if FTP already exists
	if (nipper->ios->ftp == 0)
	{
		// Create struct
		nipper->ios->ftp = malloc(sizeof(struct ftpConfig));
		memset(nipper->ios->ftp, 0, sizeof(struct ftpConfig));

		// Init
		nipper->ios->ftp->encryption = -1;
		nipper->ios->ftp->weak = false;
		nipper->ios->ftp->dictionary = false;
	}

	// Check for username
	if (strncmp(line, "ip ftp username ", 16) == 0)
	{
		strncpy(nipper->ios->ftp->username, line + 16, sizeof(nipper->ios->ftp->username));
	}

	// Check for interface
	if (strncmp(line, "ip ftp source-interface ", 24) == 0)
	{
		// Allocate struct
		interfacePointer = malloc(sizeof(struct netInterface));
		memset(interfacePointer, 0, sizeof(struct netInterface));

		// Pointers
		interfacePointer->next = nipper->ios->ftp->interface;
		nipper->ios->ftp->interface = interfacePointer;

		// Copy interface
		strncpy(interfacePointer->interface, line + 24, sizeof(interfacePointer->interface));
	}

	// Check for password
	else if (strncmp("ip ftp password ", line, 16) == 0)
	{
		switch (line[16])
		{
			case '7':
				nipper->ios->ftp->encryption = encrypt_type7;
				if (password7(line+18, nipper->ios->ftp->password, sizeof(nipper->ios->ftp->password), nipper->debugMode) != 0)
					strcpy(nipper->ios->ftp->password, "<unknown>");
				strncpy(nipper->ios->ftp->passwordEncrypted, line+18, sizeof(nipper->ios->ftp->passwordEncrypted));
				break;

			case '5':
				nipper->ios->ftp->encryption = encrypt_md5;
				strcpy(nipper->ios->ftp->password, "<unknown>");
				strncpy(nipper->ios->ftp->passwordEncrypted, line+18, sizeof(nipper->ios->ftp->passwordEncrypted));
				addJohnPassword(nipper, nipper->ios->ftp->username, nipper->ios->ftp->passwordEncrypted);
				break;

			case '0':
				nipper->ios->ftp->encryption = encrypt_none;
				strncpy(nipper->ios->ftp->password, line+18, sizeof(nipper->ios->ftp->password));
				strcpy(nipper->ios->enable->passwordEncrypted, "");
				break;

			default:
				nipper->ios->ftp->encryption = encrypt_unknown;
				strcpy(nipper->ios->ftp->password, "<unknown>");
				strncpy(nipper->ios->ftp->passwordEncrypted, line+18, sizeof(nipper->ios->ftp->passwordEncrypted));
				break;
		}
		if ((strcmp(nipper->ios->ftp->password, "<unknown>") != 0) && (strlen(nipper->ios->ftp->password) != 0))
		{
			if (simplePassword(nipper->ios->ftp->password, nipper) == true)
			{
				nipper->simplePasswords++;
				nipper->ios->ftp->dictionary = true;
			}
			if (passwordStrength(nipper->ios->ftp->password, nipper) == false)
			{
				nipper->passwordStrengths++;
				nipper->ios->ftp->weak = true;
			}
		}
	}
}



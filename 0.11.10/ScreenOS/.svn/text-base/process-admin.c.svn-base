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


#define adminfmt_default 0
#define adminfmt_dos 1
#define adminfmt_unix 2

#define adminpriv_default 0
#define adminpriv_rw 1
#define adminpriv_ext 2
#define adminpriv_all 3
#define adminpriv_read 4

#define trustee_none 0
#define trustee_modem 1
#define trustee_inter 2


struct adminUsersSOS
{
	char username[32];
	char password[32];
	int trustee;
	int privilege;
	struct adminUsersSOS *next;
};


// Process admin lines
void processSOSAdmin(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct ciscoCommand command;
	struct adminUsersSOS *userSOSPointer = 0;

	if (nipper->debugMode == true)
		printf("Admin Line: %s\n", line);

	// Init
	command = splitLine(line);

	// Access Attempts
	if ((strcasecmp(command.part[2], "access") == 0) && (strcasecmp(command.part[3], "attempts") == 0))
	{
		if (strcasecmp(command.part[1], "unset") == 0)
			nipper->sos->accessAttempts = 3;
		else
			nipper->sos->accessAttempts = atoi(command.part[4]);
	}

	// Users
	else if ((strcasecmp(command.part[0], "set") == 0) && (strcasecmp(command.part[2], "user") == 0))
	{
		// Is this the first user?
		if (nipper->sos->users == 0)
		{
			// Create
			nipper->sos->users = malloc(sizeof(struct adminUsersSOS));

			// Init
			memset(nipper->sos->users, 0 , sizeof(struct adminUsersSOS));
			userSOSPointer = nipper->sos->users;
			userSOSPointer->trustee = trustee_none;
			userSOSPointer->privilege = adminpriv_default;
		}

		// Find users
		else
		{
			userSOSPointer = nipper->sos->users;
			while ((userSOSPointer->next != 0) && (strcmp(userSOSPointer->username, command.part[3]) != 0))
				userSOSPointer = userSOSPointer->next;

			// If not found
			if (strcmp(userSOSPointer->username, command.part[3]) != 0)
			{
				// Create
				userSOSPointer->next = malloc(sizeof(struct adminUsersSOS));

				// Init
				memset(userSOSPointer->next, 0 , sizeof(struct adminUsersSOS));
				userSOSPointer = userSOSPointer->next;
				userSOSPointer->trustee = trustee_none;
				userSOSPointer->privilege = adminpriv_default;
			}
		}

		// Set username
		strncpy(userSOSPointer->username, command.part[3], sizeof(userSOSPointer->username) - 1);

		// Is it a password?
		if (strcasecmp(command.part[4], "password") == 0)
		{
			stripQuotes(command.part[5], userSOSPointer->password, sizeof(userSOSPointer->password));
			addJohnPassword(nipper, userSOSPointer->username, userSOSPointer->password);

			// Is there a privilege set?
			if (command.parts > 7)
			{
				if ((strcasecmp(command.part[6], "privilege") == 0) && (strcasecmp(command.part[7], "all") == 0))
					userSOSPointer->privilege = adminpriv_all;
				else if ((strcasecmp(command.part[6], "privilege") == 0) && (strcasecmp(command.part[7], "read-only") == 0))
					userSOSPointer->privilege = adminpriv_read;
			}
		}

		// Is it a trustee?
		else if (strcasecmp(command.part[4], "trustee") == 0)
		{
			if (command.parts > 5)
			{
				if (strcasecmp(command.part[5], "interface") == 0)
					userSOSPointer->trustee = trustee_inter;
				else if (strcasecmp(command.part[5], "modem") == 0)
					userSOSPointer->trustee = trustee_modem;
			}
			else
				userSOSPointer->trustee = trustee_none;
		}
	}

	// Auth Timeout
	else if ((strcasecmp(command.part[2], "auth") == 0) && (strcasecmp(command.part[3], "timeout") == 0))
	{
		if (strcasecmp(command.part[0], "unset") == 0)
			nipper->sos->authTimeout = 0;
		else
			nipper->sos->authTimeout = atoi(command.part[4]);
	}

	// Auth Server
	else if ((strcasecmp(command.part[2], "auth") == 0) && (strcasecmp(command.part[3], "server") == 0))
	{
		if (strcasecmp(command.part[0], "unset") == 0)
			nipper->sos->authenticationServer[0] = 0;
		else
			stripQuotes(command.part[4], nipper->sos->authenticationServer, sizeof(nipper->sos->authenticationServer));
	}

	// Name
	else if (strcasecmp(command.part[2], "name") == 0)
	{
		if (strcasecmp(command.part[0], "unset") == 0)
			nipper->sos->name[0] = 0;
		else
			stripQuotes(command.part[3], nipper->sos->name, sizeof(nipper->sos->name));
	}

	// Password Length
	else if ((strcasecmp(command.part[2], "password") == 0) && (strcasecmp(command.part[3], "restrict") == 0) && (strcasecmp(command.part[4], "length") == 0))
	{
		if (strcasecmp(command.part[0], "unset") == 0)
			nipper->sos->restrictLength = 0;
		else
			nipper->sos->restrictLength = atoi(command.part[5]);
	}

	// Password
	else if (strcasecmp(command.part[2], "password") == 0)
	{
		if (strcasecmp(command.part[0], "unset") == 0)
			nipper->sos->password[0] = 0;
		else
		{
			stripQuotes(command.part[3], nipper->sos->password, sizeof(nipper->sos->password));
			addJohnPassword(nipper, nipper->sos->name, nipper->sos->password);
		}
	}

	// Admin Privilege
	else if (strcasecmp(command.part[2], "privilege") == 0)
	{
		if (strcasecmp(command.part[0], "unset") == 0)
			nipper->sos->privilege = adminpriv_default;
		else if (strcasecmp(command.part[3], "read-write") == 0)
			nipper->sos->privilege = adminpriv_rw;
		else if (strcasecmp(command.part[3], "get-external") == 0)
			nipper->sos->privilege = adminpriv_ext;
	}

	// Management IP
	else if (strcasecmp(command.part[2], "manager-ip") == 0)
	{
		if (strcasecmp(command.part[0], "unset") == 0)
			nipper->sos->name[0] = 0;
		else
		{
			stripQuotes(command.part[3], nipper->sos->adminIP, sizeof(nipper->sos->adminIP));
			if (command.parts > 4)
				stripQuotes(command.part[4], nipper->sos->adminNetMask, sizeof(nipper->sos->adminNetMask));
		}
	}

	// Admin Format
	else if (strcasecmp(command.part[2], "format") == 0)
	{
		if (strcasecmp(command.part[0], "unset") == 0)
			nipper->sos->adminFormat = adminfmt_default;
		else if (strcasecmp(command.part[3], "dos") == 0)
			nipper->sos->adminFormat = adminfmt_dos;
		else if (strcasecmp(command.part[3], "unix") == 0)
			nipper->sos->adminFormat = adminfmt_unix;
	}

	// Admin HTTP Redirect
	else if ((strcasecmp(command.part[2], "http") == 0) && (strcasecmp(command.part[3], "redirect") == 0))
	{
		if (strcasecmp(command.part[0], "unset") == 0)
			nipper->sos->httpRedirect = false;
		else
			nipper->sos->httpRedirect = true;
	}

	// Console only access
	else if ((strcasecmp(command.part[2], "root") == 0) && (strcasecmp(command.part[3], "access") == 0) && (strcasecmp(command.part[4], "console") == 0))
	{
		if (strcasecmp(command.part[0], "unset") == 0)
			nipper->sos->consoleOnly = false;
		else
			nipper->sos->consoleOnly = true;
	}

	// Mail Alerts
	else if ((strcasecmp(command.part[2], "mail") == 0) && (strcasecmp(command.part[3], "alert") == 0))
	{
		if (strcasecmp(command.part[0], "unset") == 0)
			nipper->sos->mailAlert = false;
		else
			nipper->sos->mailAlert = true;
	}

	// Mail Server Name / IP
	else if ((strcasecmp(command.part[2], "mail") == 0) && (strcasecmp(command.part[3], "server-name") == 0))
	{
		if (strcasecmp(command.part[0], "unset") == 0)
			nipper->sos->emailServer[0] = 0;
		else
			stripQuotes(command.part[4], nipper->sos->emailServer, sizeof(nipper->sos->emailServer));
	}

	// Mail email address - additional 1
	else if ((strcasecmp(command.part[2], "mail") == 0) && (strcasecmp(command.part[3], "mail-addr1") == 0))
	{
		if (strcasecmp(command.part[0], "unset") == 0)
			nipper->sos->email1[0] = 0;
		else
			stripQuotes(command.part[4], nipper->sos->email1, sizeof(nipper->sos->email1));
	}

	// Mail email address - additional 2
	else if ((strcasecmp(command.part[2], "mail") == 0) && (strcasecmp(command.part[3], "mail-addr2") == 0))
	{
		if (strcasecmp(command.part[0], "unset") == 0)
			nipper->sos->email2[0] = 0;
		else
			stripQuotes(command.part[4], nipper->sos->email2, sizeof(nipper->sos->email2));
	}

	// Admin email address (this should be the last mail entry!)
	else if ((strcasecmp(command.part[2], "mail") == 0) && (strcasecmp(command.part[3], "traffic-log") == 0))
	{
		if (strcasecmp(command.part[0], "unset") == 0)
			nipper->sos->email[0] = 0;
		else
			stripQuotes(command.part[3], nipper->sos->email, sizeof(nipper->sos->email));
	}
}


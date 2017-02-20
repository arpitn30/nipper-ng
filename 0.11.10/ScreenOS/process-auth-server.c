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


#define authtype_builtin 0
#define authtype_radius 1
#define authtype_ldap 2
#define authtype_securid 3


struct authServerSOS
{
	int type;						// Type of Auth Server (radius (default), ldap, securid)
	char name[32];					// Auth Server name
	int id;							// ID
	char serverName[32];			// Server Name
	char backup1[32];				// Backup Server Name 1
	char backup2[32];				// Backup Server Name 2
	int timeout;					// Server timeout
	int forcedTimeout;				// Forced Timeout
	char radiusSecret[32];			// Radius Secret
	int weak;
	int dictionary;
	char sourceInterface[32];		// Source Interface

	struct authServerSOS *next;
};


// Process Auth Server
void processSOSAuthServer(char *line, struct nipperConfig *nipper)
{
	// Variables
	char tempString[nipper->maxSize];
	struct ciscoCommand command;
	struct authServerSOS *authServerPointer = 0;
	int init = false;


	if (nipper->debugMode == true)
		printf("Auth-Server Line: %s\n", line);

	// Init
	command = splitLine(line);

	if (strcasecmp(command.part[0], "set") == 0)
	{

		// Has Auth Server structure been created?
		if (nipper->sos->authServer == 0)
		{
			// Create
			nipper->sos->authServer = malloc(sizeof(struct authServerSOS));
			authServerPointer = nipper->sos->authServer;
			init = true;
		}

		// Search for server
		else
		{
			authServerPointer = nipper->sos->authServer;
			stripQuotes(command.part[2], tempString, nipper->maxSize);
			while ((authServerPointer->next != 0) && (strcmp(tempString, authServerPointer->name) != 0))
				authServerPointer = authServerPointer->next;

			// If not found
			if (strcmp(tempString, authServerPointer->name) != 0)
			{
				// Create
				authServerPointer->next = malloc(sizeof(struct authServerSOS));
				authServerPointer = authServerPointer->next;
				init = true;
			}
		}
		
		if (init == true)
		{
			memset(authServerPointer, 0 , sizeof(struct authServerSOS));
			authServerPointer->type = authtype_builtin;
			authServerPointer->timeout = 10;
			authServerPointer->dictionary = false;
			authServerPointer->weak = false;
		}

		// Set auth-server name
		stripQuotes(command.part[2], authServerPointer->name, sizeof(authServerPointer->name));

		// Timeout
		if (strcasecmp(command.part[3], "timeout") == 0)
			authServerPointer->timeout = atoi(command.part[4]);

		// Forced Timeout
		else if (strcasecmp(command.part[3], "forced-timeout") == 0)
			authServerPointer->forcedTimeout = atoi(command.part[4]);

		// ID
		else if (strcasecmp(command.part[3], "id") == 0)
			authServerPointer->id = atoi(command.part[4]);

		// Server Name
		else if (strcasecmp(command.part[3], "server-name") == 0)
			stripQuotes(command.part[4], authServerPointer->serverName, sizeof(authServerPointer->serverName));

		// Backup Server Name 1
		else if (strcasecmp(command.part[3], "backup1") == 0)
			stripQuotes(command.part[4], authServerPointer->backup1, sizeof(authServerPointer->backup1));

		// Backup Server Name 2
		else if (strcasecmp(command.part[3], "backup2") == 0)
			stripQuotes(command.part[4], authServerPointer->backup2, sizeof(authServerPointer->backup2));

		// Source Interface
		else if ((strcasecmp(command.part[3], "src_interface") == 0) || (strcasecmp(command.part[3], "src-interface") == 0))
			stripQuotes(command.part[4], authServerPointer->sourceInterface, sizeof(authServerPointer->sourceInterface));

		// Radius
		else if (strcasecmp(command.part[3], "radius") == 0)
		{
			authServerPointer->type = authtype_radius;
			// Secret
			if (strcasecmp(command.part[4], "secret") == 0)
			{
				stripQuotes(command.part[5], authServerPointer->radiusSecret, sizeof(authServerPointer->radiusSecret));
				
				// Check strength / dictionary...
				if (simplePassword(authServerPointer->radiusSecret, nipper) == true)
				{
					nipper->simplePasswords++;
					authServerPointer->dictionary = true;
				}
				if (passwordStrength(authServerPointer->radiusSecret, nipper) == false)
				{
					nipper->passwordStrengths++;
					authServerPointer->weak = true;
				}
			}
		}

		// LDAP
		else if (strcasecmp(command.part[3], "ldap") == 0)
		{
			authServerPointer->type = authtype_ldap;
		}

		// SecureID
		else if (strcasecmp(command.part[3], "securid") == 0)
		{
			authServerPointer->type = authtype_securid;
		}
	}
}


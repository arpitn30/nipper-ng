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


#define ntp_peer 0
#define ntp_serve 1
#define ntp_serve_only 2
#define ntp_query_only 3


// NTP Server / Peer
struct ntpHost
{
	char ntpHost[32];
	int keyNum;
	struct ntpHost *next;
};

// NTP Authentication Key
struct ntpKey
{
	int keyNum;
	int trusted;					// true or false
	char key[128];
	int weak;
	int dictionary;
	struct ntpKey *next;
};

// NTP Access Group
struct ntpAccessGroup
{
	int accessType;					// ntp_peer, ntp_serve...
	char accessList[65];
	struct ntpAccessGroup *next;
};

// NTP
struct ntpConfig
{
	int enabled;					// true or false
	int master;						// true or false
	int authentication;				// true or false
	struct ntpAccessGroup *access;
	struct ntpKey *key;
	struct ntpHost *server;
	struct ntpHost *peer;
};


// Process NTP
void processNtp(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct ntpKey *ntpKeyPointer = 0;
	struct ntpHost *ntpHostPointer = 0;
	struct ntpAccessGroup *ntpAccessPointer = 0;
	int tempInt = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("NTP Line: %s\n", line);
	}

	// Check to see if NTP already exists
	if (nipper->ios->ntp == 0)
	{
		nipper->ios->ntp = malloc(sizeof(struct ntpConfig));
		memset(nipper->ios->ntp, 0, sizeof(struct ntpConfig));

		// Init
		nipper->ios->ntp->enabled = true;
		nipper->ios->ntp->master = false;
		nipper->ios->ntp->authentication = false;
	}

	// ntp disable?
	if (strncmp(line, "ntp disable", 11) == 0)
		nipper->ios->ntp->enabled = false;

	// ntp master?
	else if (strncmp(line, "ntp master", 10) == 0)
		nipper->ios->ntp->master = true;

	// ntp server / peer?
	else if ((strncmp(line, "ntp server ", 11) == 0) || (strncmp(line, "ntp peer ", 9) == 0))
	{
		// create ntp host struct
		ntpHostPointer = malloc(sizeof(struct ntpHost));
		memset(ntpHostPointer, 0, sizeof(struct ntpHost));

		// Sort out Pointers
		if (strncmp(line, "ntp server ", 11) == 0)
		{
			ntpHostPointer->next = nipper->ios->ntp->server;
			nipper->ios->ntp->server = ntpHostPointer;
		}
		else
		{
			ntpHostPointer->next = nipper->ios->ntp->peer;
			nipper->ios->ntp->peer = ntpHostPointer;
		}

		// Init
		ntpHostPointer->keyNum = -1;

		// Get info
		tempInt = nextSpace(line + 11);
		if (line[11 + tempInt] == 0)
		{
			strncpy(ntpHostPointer->ntpHost, line + 11, sizeof(ntpHostPointer->ntpHost));
		}
		else
		{
			line[11 + tempInt] = 0;
			strncpy(ntpHostPointer->ntpHost, line + 11, sizeof(ntpHostPointer->ntpHost));

			// If key exists
			if (strncmp(line + 11 + tempInt, "key ", 4) == 0)
			{
				ntpHostPointer->keyNum = atoi(line + 15 + tempInt);
			}
		}
	}

	// ntp authentication?
	else if (strncmp(line, "ntp authenticate", 16) == 0)
		nipper->ios->ntp->authentication = true;

	// ntp authentication key?
	else if (strncmp(line, "ntp authentication-key ", 23) == 0)
	{
		// create ntp key struct
		ntpKeyPointer = malloc(sizeof(struct ntpKey));
		memset(ntpKeyPointer, 0, sizeof(struct ntpKey));

		// Sort out Pointers
		ntpKeyPointer->next = nipper->ios->ntp->key;
		nipper->ios->ntp->key = ntpKeyPointer;

		// Init
		ntpKeyPointer->trusted = false;
		ntpKeyPointer->weak = false;
		ntpKeyPointer->dictionary = false;

		tempInt = nextSpace(line + 23);
		line[23 + tempInt] = 0;
		ntpKeyPointer->keyNum = atoi(line + 23);
		strncpy(ntpKeyPointer->key, line + 27 + tempInt, sizeof(ntpKeyPointer->key));
		if (simplePassword(ntpKeyPointer->key, nipper) == true)
		{
			nipper->simplePasswords++;
			ntpKeyPointer->dictionary = true;
		}
		if (passwordStrength(ntpKeyPointer->key, nipper) == false)
		{
			nipper->passwordStrengths++;
			ntpKeyPointer->weak = true;
		}
	}

	// ntp authentication key trusted?
	else if (strncmp(line, "ntp trusted-key ", 16) == 0)
	{
		// Init
		ntpKeyPointer = nipper->ios->ntp->key;
		tempInt = atoi(line + 16);

		// Find key
		while ((ntpKeyPointer != 0) && (ntpKeyPointer->keyNum != tempInt))
		{
			ntpKeyPointer = ntpKeyPointer->next;
		}

		// Set trusted if found
		if (ntpKeyPointer->keyNum == tempInt)
			ntpKeyPointer->trusted = true;
	}

	// ntp access-group?
	else if (strncmp(line, "ntp access-group ", 17) == 0)
	{
		// create ntp access-group struct
		ntpAccessPointer = malloc(sizeof(struct ntpAccessGroup));
		memset(ntpAccessPointer, 0, sizeof(struct ntpAccessGroup));

		// Sort out Pointers
		ntpAccessPointer->next = nipper->ios->ntp->access;
		nipper->ios->ntp->access = ntpAccessPointer;

		// Get access type
		if (strncmp(line + 17, "peer ", 5) == 0)
			ntpAccessPointer->accessType = ntp_peer;
		else if (strncmp(line + 17, "serve ", 6) == 0)
			ntpAccessPointer->accessType = ntp_serve;
		else if (strncmp(line + 17, "serve-only ", 11) == 0)
			ntpAccessPointer->accessType = ntp_serve_only;
		else
			ntpAccessPointer->accessType = ntp_query_only;

		// Get access-list num
		tempInt = nextSpace(line + 17);
		strncpy(ntpAccessPointer->accessList, line + 18 + tempInt, sizeof(ntpAccessPointer->accessList) - 1);
	}
}


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


#define ssh_ver_unconfigured 0
#define ssh_ver_1 1
#define ssh_ver_2 2


// SSH
struct sshConfig
{
	int enabled;					// true, false
	int protocolVersion;			// ssh_ver_unconfigured, ssh_ver_1, ssh_ver_2
	int timeout;
	int retries;
	struct netInterface *interface;
};


// Process SSH
void processSsh(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct netInterface *interfacePointer = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("SSH Line: %s\n", line);
	}

	// Check to see if SSH already exists
	if (nipper->ios->ssh == 0)
	{
		nipper->ios->ssh = malloc(sizeof(struct sshConfig));
		memset(nipper->ios->ssh, 0, sizeof(struct sshConfig));

		// Init
		nipper->ios->ssh->enabled = true;
		nipper->ios->ssh->protocolVersion = ssh_ver_unconfigured;
		nipper->ios->ssh->timeout = -1;
		nipper->ios->ssh->retries = -1;
		nipper->ios->ssh->interface = 0;
	}

	// No SSH :-(
	if (strncmp(line, "no ip ssh", 9) == 0)
		nipper->ios->ssh->enabled = false;

	// Retries
	else if (strncmp(line, "ip ssh authentication-retries ", 30) == 0)
		nipper->ios->ssh->retries = atoi(line + 30);

	// Timeout
	else if (strncmp(line, "ip ssh time-out ", 16) == 0)
		nipper->ios->ssh->timeout = atoi(line + 16);

	// Protocol Version
	else if (strncmp(line, "ip ssh version ", 15) == 0)
	{
		switch (atoi(line + 15))
		{
			case 1:
				nipper->ios->ssh->protocolVersion = ssh_ver_1;
				break;

			case 2:
				nipper->ios->ssh->protocolVersion = ssh_ver_2;
				break;

			default:
				nipper->ios->ssh->protocolVersion = ssh_ver_unconfigured;
				break;
		}
	}

	// Check for interface
	else if (strncmp(line, "ip ssh source-interface ", 24) == 0)
	{
		// Allocate struct
		interfacePointer = malloc(sizeof(struct netInterface));
		memset(interfacePointer, 0, sizeof(struct netInterface));

		// Pointers
		interfacePointer->next = nipper->ios->ssh->interface;
		nipper->ios->ssh->interface = interfacePointer;

		// Copy interface
		strncpy(interfacePointer->interface, line + 24, sizeof(interfacePointer->interface));
	}
}


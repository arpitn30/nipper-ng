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


// Process EnablePass / Password
void processEnablePass(char *line, struct nipperConfig *nipper)
{
	// Enable Password?
	if (strncmp("set enablepass ", line, 15) == 0)
	{
		// Debug output
		if (nipper->debugMode == true)
			printf("Enable Password Line: %s\n", line);

		strncpy(nipper->nmp->enablePassword, line + 15, sizeof(nipper->nmp->enablePassword) - 1);
		addJohnPassword(nipper, "Enable", nipper->nmp->enablePassword);
	}

	// Password
	else if (strncmp("set password ", line, 13) == 0)
	{
		// Debug output
		if (nipper->debugMode == true)
			printf("Login Password Line: %s\n", line);

		strncpy(nipper->nmp->password, line + 13, sizeof(nipper->nmp->password) - 1);
		addJohnPassword(nipper, "LoginPassword", nipper->nmp->password);
	}
}


struct switchNMPConfig
{
	int ipRedirect;					// true or false
	int ipUnreachable;				// true or false
	int ipFragmentation;			// true or false
};


// ICMP IP Unreachable
void processNMPUnreachable(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct ciscoCommand command;

	// Debug output
	if (nipper->debugMode == true)
		printf("ICMP IP Unrachable Line: %s\n", line);

	// Is switch configuration is not set
	if (nipper->nmp->switchConfig == 0)
	{
		nipper->nmp->switchConfig = malloc(sizeof(struct switchNMPConfig));
		memset(nipper->nmp->switchConfig, 0 , sizeof(struct switchNMPConfig));
		nipper->nmp->switchConfig->ipRedirect = true;
		nipper->nmp->switchConfig->ipUnreachable = true;
		nipper->nmp->switchConfig->ipFragmentation = true;
	}

	// Init
	command = splitLine(line);

	if (strcmp(command.part[3], "enable") == 0)
		nipper->nmp->switchConfig->ipUnreachable = true;
	else
		nipper->nmp->switchConfig->ipUnreachable = false;
}


// IP Redirects
void processNMPRedirect(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct ciscoCommand command;

	// Debug output
	if (nipper->debugMode == true)
		printf("IP Redirect Line: %s\n", line);

	// Is switch configuration is not set
	if (nipper->nmp->switchConfig == 0)
	{
		nipper->nmp->switchConfig = malloc(sizeof(struct switchNMPConfig));
		memset(nipper->nmp->switchConfig, 0 , sizeof(struct switchNMPConfig));
		nipper->nmp->switchConfig->ipRedirect = true;
		nipper->nmp->switchConfig->ipUnreachable = true;
		nipper->nmp->switchConfig->ipFragmentation = true;
	}

	// Init
	command = splitLine(line);

	if (strcmp(command.part[3], "enable") == 0)
		nipper->nmp->switchConfig->ipRedirect = true;
	else
		nipper->nmp->switchConfig->ipRedirect = false;
}


// Fragmentation
void processNMPFragmentation(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct ciscoCommand command;

	// Debug output
	if (nipper->debugMode == true)
		printf("IP Fragmentation Line: %s\n", line);

	// Is switch configuration is not set
	if (nipper->nmp->switchConfig == 0)
	{
		nipper->nmp->switchConfig = malloc(sizeof(struct switchNMPConfig));
		memset(nipper->nmp->switchConfig, 0 , sizeof(struct switchNMPConfig));
		nipper->nmp->switchConfig->ipRedirect = true;
		nipper->nmp->switchConfig->ipUnreachable = true;
		nipper->nmp->switchConfig->ipFragmentation = true;
	}

	// Init
	command = splitLine(line);

	if (strcmp(command.part[3], "enable") == 0)
		nipper->nmp->switchConfig->ipFragmentation = true;
	else
		nipper->nmp->switchConfig->ipFragmentation = false;
}



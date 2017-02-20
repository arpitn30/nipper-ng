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

// This file contains the code to process PIX HTTP

struct httpPIXConfig
{
	int httpServer;							// HTTPS server (true or false)
	int httpServerPort;						// HTTPS server Port
	int requireCert;						// Require Certificate
	int httpRedirect;						// Redirect HTTP to HTTPS
	int httpRedirectPort;					// The HTTP redirect port
	struct mgmtHostsPIX *host;				// Hosts that can access the HTTP server
};

struct mgmtHostsPIX
{
	char interface[32];
	char ipAddress[32];
	char netMask[32];
	struct mgmtHostsPIX *next;
};


// Process HTTP...
void processPIXHTTP(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct ciscoCommand command;
	struct mgmtHostsPIX *mgmtHostsPointer = 0;
	int tempInt = 0;
	int setting = 0;

	// Init
	command = splitLine(line);

	// No?
	if (strcmp(command.part[0], "no") == 0)
	{
		setting = false;
		tempInt = 1;
	}
	else
	{
		setting = true;
		tempInt = 0;
	}

	// Debug
	if (nipper->debugMode == true)
	{
		printf("HTTP Line: %s\n", line);
	}

	// Init...
	if (nipper->pix->http == 0)
	{
		nipper->pix->http = malloc(sizeof(struct httpPIXConfig));
		memset(nipper->pix->http, 0, sizeof(struct httpPIXConfig));
		nipper->pix->http->httpServerPort = 443;
		nipper->pix->http->httpServer = false;
		nipper->pix->http->requireCert = false;
		nipper->pix->http->httpRedirectPort = 80;
	}

	// Enable HTTP Server...
	if ((strcmp(command.part[tempInt], "http") == 0) && (strcmp(command.part[tempInt + 1], "server") == 0) && (strcmp(command.part[tempInt + 2], "enable") == 0))
	{
		nipper->pix->http->httpServer = setting;
		// Check for port...
		if (command.parts == tempInt + 4)
		{
			if (setting == false)
				nipper->pix->http->httpServerPort = atoi(command.part[tempInt + 3]);
			else
				nipper->pix->http->httpServerPort = 443;
		}
	}

	// Require Cert...
	else if ((strcmp(command.part[tempInt], "http") == 0) && (strcmp(command.part[tempInt + 1], "authentication-certificate") == 0))
		nipper->pix->http->requireCert = setting;

	// HTTP Redirect...
	else if ((strcmp(command.part[tempInt], "http") == 0) && (strcmp(command.part[tempInt + 1], "redirect") == 0))
	{
		nipper->pix->http->httpRedirect = setting;
		if (command.parts == tempInt + 4)
			nipper->pix->http->httpRedirectPort = atoi(command.part[tempInt + 3]);
	}

	// HTTP Remote Access host...
	else if ((strcmp(command.part[tempInt], "http") == 0) && (command.parts == tempInt + 4))
	{
		// Create new mgmt host...
		if (nipper->pix->http->host == 0)
		{
			nipper->pix->http->host = malloc(sizeof(struct mgmtHostsPIX));
			memset(nipper->pix->http->host, 0, sizeof(struct mgmtHostsPIX));
			mgmtHostsPointer = nipper->pix->http->host;
		}
		else
		{
			mgmtHostsPointer = nipper->pix->http->host;
			while (mgmtHostsPointer->next != 0)
				mgmtHostsPointer = mgmtHostsPointer->next;
			mgmtHostsPointer->next = malloc(sizeof(struct mgmtHostsPIX));
			memset(mgmtHostsPointer->next, 0, sizeof(struct mgmtHostsPIX));
			mgmtHostsPointer = mgmtHostsPointer->next;
		}

		// IP Address...
		tempInt++;
		strncpy(mgmtHostsPointer->ipAddress, command.part[tempInt], sizeof(mgmtHostsPointer->ipAddress) - 1);

		// Net Mask...
		tempInt++;
		strncpy(mgmtHostsPointer->netMask, command.part[tempInt], sizeof(mgmtHostsPointer->netMask) - 1);

		// Interface...
		tempInt++;
		strncpy(mgmtHostsPointer->interface, command.part[tempInt], sizeof(mgmtHostsPointer->interface) - 1);
	}
}


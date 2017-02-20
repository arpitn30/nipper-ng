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

#define http_auth_enable 0
#define http_auth_local 1
#define http_auth_tacacs 2
#define http_auth_aaa 3


// HTTP
struct httpConfig
{
	int enabled;					// true, false
	int authentication;				// http_auth_enable...
	char accessClass[65];
};


// Process HTTP
void processHttp(char *line, struct nipperConfig *nipper)
{
	// Debug
	if (nipper->debugMode == true)
	{
		printf("HTTP Line: %s\n", line);
	}

	// Create struct?
	if (nipper->ios->http == 0)
	{
		nipper->ios->http = malloc(sizeof(struct httpConfig));
		memset(nipper->ios->http, 0, sizeof(struct httpConfig));
		nipper->ios->http->enabled = true;
		nipper->ios->http->authentication = http_auth_enable;	// default auth method
	}

	// HTTP server enabled
	if (strncmp(line, "ip http server", 14) == 0)
		nipper->ios->http->enabled = true;

	// HTTP server disabled
	if (strncmp(line, "no ip http server", 17) == 0)
		nipper->ios->http->enabled = false;

	// HTTP Access Class (Access List)
	if (strncmp(line, "ip http access-class", 20) == 0)
		strncpy(nipper->ios->http->accessClass, line + 21, sizeof(nipper->ios->http->accessClass) -1);

	// HTTP Authentication method
	if (strncmp(line, "ip http authentication", 22) == 0)
	{
		if (strncmp(line + 23, "aaa", 3) == 0)
			nipper->ios->http->authentication = http_auth_aaa;

		else if (strncmp(line + 23, "local", 5) == 0)
			nipper->ios->http->authentication = http_auth_local;

		else if (strncmp(line + 23, "tacacs", 6) == 0)
			nipper->ios->http->authentication = http_auth_tacacs;

		else if (strncmp(line + 23, "enable", 6) == 0)
			nipper->ios->http->authentication = http_auth_enable;
	}

	// HTTP Authentication method 2
	if (strncmp(line, "ip http auth", 12) == 0)
	{
		if (strncmp(line + 13, "aaa", 3) == 0)
			nipper->ios->http->authentication = http_auth_aaa;

		else if (strncmp(line + 13, "local", 5) == 0)
			nipper->ios->http->authentication = http_auth_local;

		else if (strncmp(line + 13, "tacacs", 6) == 0)
			nipper->ios->http->authentication = http_auth_tacacs;

		else if (strncmp(line + 13, "enable", 6) == 0)
			nipper->ios->http->authentication = http_auth_enable;
	}
}



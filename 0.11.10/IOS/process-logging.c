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


// Logging config
struct loggingConfig
{
	int logging;					// true (default), false
	// Logging to Console
	int consoleLogging;				// true, false, unconfigured (default)
	int consoleLevel;				// -1 (default)
	// Logging to Terminal Lines
	int monitorLogging;				// true (default) or false
	int monitorLevel;				// 7 (default)
	// Buffer Logging
	int bufferedLogging;			// true, false, unconfigured (default)
	int bufferSize;					// -1 (default)
	int bufferLevel;				// Buffer Severity level (-1 default)
	// Syslog
	int loggingTrap;				// 6 (default)
	char facility[8];				// Syslog facility (default is local7)
	char originId[64];				// Syslog Origin ID
	char sourceInterface[32];		// Source Interface
	int logCount;					// true or false (default)
	// Logging Options
	int logEnable;					// true or false (default)
	struct host *logServer;			// Logging hosts (command is "logging" or "logging host"
};


// Process Logging
void processLogging(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct host *logServerPointer = 0;
	struct ciscoCommand command;
	char tempString[nipper->maxSize];
	int tempInt = 0;
	int setting = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Logging Line: %s\n", line);
	}

	// Create logging structure
	if (nipper->ios->logging == 0)
	{
		nipper->ios->logging = malloc(sizeof(struct loggingConfig));
		memset(nipper->ios->logging, 0, sizeof(struct loggingConfig));

		// init
		nipper->loggingLevels = true;
		nipper->ios->logging->logging = true;
		nipper->ios->logging->consoleLogging = unconfigured;
		nipper->ios->logging->consoleLevel = -1;
		nipper->ios->logging->bufferedLogging = unconfigured;
		nipper->ios->logging->bufferSize = -1;
		nipper->ios->logging->bufferLevel = 7;
		nipper->ios->logging->logCount = false;
		nipper->ios->logging->logEnable = false;
		nipper->ios->logging->monitorLogging = true;
		nipper->ios->logging->monitorLevel = 7;
		nipper->ios->logging->loggingTrap = 6;
		strcpy(nipper->ios->logging->facility, "local7");
	}

	// Init...
	command = splitLine(line);

	// Setting
	if (strcmp(command.part[0], "no") == 0)
	{
		setting = false;
		tempInt = 2;
	}
	else
	{
		setting = true;
		tempInt = 1;
	}

	// Buffered
	if (strcmp(command.part[tempInt], "buffered") == 0)
	{
		nipper->ios->logging->bufferedLogging = setting;

		// Buffered options
		if (tempInt < command.parts)
		{
			tempInt++;
			// Levels
			if ((strcmp(command.part[tempInt], "0") == 0) || (strcmp(command.part[tempInt], "emergencies") == 0))
				nipper->ios->logging->bufferLevel = 0;
			else if ((strcmp(command.part[tempInt], "1") == 0) || (strcmp(command.part[tempInt], "alerts") == 0))
				nipper->ios->logging->bufferLevel = 1;
			else if ((strcmp(command.part[tempInt], "2") == 0) || (strcmp(command.part[tempInt], "critical") == 0))
				nipper->ios->logging->bufferLevel = 2;
			else if ((strcmp(command.part[tempInt], "3") == 0) || (strcmp(command.part[tempInt], "errors") == 0))
				nipper->ios->logging->bufferLevel = 3;
			else if ((strcmp(command.part[tempInt], "4") == 0) || (strcmp(command.part[tempInt], "warnings") == 0))
				nipper->ios->logging->bufferLevel = 4;
			else if ((strcmp(command.part[tempInt], "5") == 0) || (strcmp(command.part[tempInt], "notifications") == 0))
				nipper->ios->logging->bufferLevel = 5;
			else if ((strcmp(command.part[tempInt], "6") == 0) || (strcmp(command.part[tempInt], "informational") == 0))
				nipper->ios->logging->bufferLevel = 6;
			else if ((strcmp(command.part[tempInt], "7") == 0) || (strcmp(command.part[tempInt], "debugging") == 0))
				nipper->ios->logging->bufferLevel = 7;

			// Buffer Size
			else
				nipper->ios->logging->bufferSize = atoi(command.part[tempInt]);
			tempInt++;
		}
		if (tempInt < command.parts)
		{
			// Levels
			if ((strcmp(command.part[tempInt], "0") == 0) || (strcmp(command.part[tempInt], "emergencies") == 0))
				nipper->ios->logging->bufferLevel = 0;
			else if ((strcmp(command.part[tempInt], "1") == 0) || (strcmp(command.part[tempInt], "alerts") == 0))
				nipper->ios->logging->bufferLevel = 1;
			else if ((strcmp(command.part[tempInt], "2") == 0) || (strcmp(command.part[tempInt], "critical") == 0))
				nipper->ios->logging->bufferLevel = 2;
			else if ((strcmp(command.part[tempInt], "3") == 0) || (strcmp(command.part[tempInt], "errors") == 0))
				nipper->ios->logging->bufferLevel = 3;
			else if ((strcmp(command.part[tempInt], "4") == 0) || (strcmp(command.part[tempInt], "warnings") == 0))
				nipper->ios->logging->bufferLevel = 4;
			else if ((strcmp(command.part[tempInt], "5") == 0) || (strcmp(command.part[tempInt], "notifications") == 0))
				nipper->ios->logging->bufferLevel = 5;
			else if ((strcmp(command.part[tempInt], "6") == 0) || (strcmp(command.part[tempInt], "informational") == 0))
				nipper->ios->logging->bufferLevel = 6;
			else if ((strcmp(command.part[tempInt], "7") == 0) || (strcmp(command.part[tempInt], "debugging") == 0))
				nipper->ios->logging->bufferLevel = 7;
		}
	}

	// Console
	else if (strcmp(command.part[tempInt], "console") == 0)
	{
		nipper->ios->logging->consoleLogging = setting;

		// Options
		if (tempInt < command.parts)
		{
			tempInt++;
			// Levels
			if ((strcmp(command.part[tempInt], "0") == 0) || (strcmp(command.part[tempInt], "emergencies") == 0))
				nipper->ios->logging->consoleLevel = 0;
			else if ((strcmp(command.part[tempInt], "1") == 0) || (strcmp(command.part[tempInt], "alerts") == 0))
				nipper->ios->logging->consoleLevel = 1;
			else if ((strcmp(command.part[tempInt], "2") == 0) || (strcmp(command.part[tempInt], "critical") == 0))
				nipper->ios->logging->consoleLevel = 2;
			else if ((strcmp(command.part[tempInt], "3") == 0) || (strcmp(command.part[tempInt], "errors") == 0))
				nipper->ios->logging->consoleLevel = 3;
			else if ((strcmp(command.part[tempInt], "4") == 0) || (strcmp(command.part[tempInt], "warnings") == 0))
				nipper->ios->logging->consoleLevel = 4;
			else if ((strcmp(command.part[tempInt], "5") == 0) || (strcmp(command.part[tempInt], "notifications") == 0))
				nipper->ios->logging->consoleLevel = 5;
			else if ((strcmp(command.part[tempInt], "6") == 0) || (strcmp(command.part[tempInt], "informational") == 0))
				nipper->ios->logging->consoleLevel = 6;
			else if ((strcmp(command.part[tempInt], "7") == 0) || (strcmp(command.part[tempInt], "debugging") == 0))
				nipper->ios->logging->consoleLevel = 7;
		}
	}

	// Trap
	else if (strcmp(command.part[tempInt], "trap") == 0)
	{
		if (setting == false)
			nipper->ios->logging->loggingTrap = 6;

		// Levels
		else
		{
			tempInt++;
			// Levels
			if ((strcmp(command.part[tempInt], "0") == 0) || (strcmp(command.part[tempInt], "emergencies") == 0))
				nipper->ios->logging->loggingTrap = 0;
			else if ((strcmp(command.part[tempInt], "1") == 0) || (strcmp(command.part[tempInt], "alerts") == 0))
				nipper->ios->logging->loggingTrap = 1;
			else if ((strcmp(command.part[tempInt], "2") == 0) || (strcmp(command.part[tempInt], "critical") == 0))
				nipper->ios->logging->loggingTrap = 2;
			else if ((strcmp(command.part[tempInt], "3") == 0) || (strcmp(command.part[tempInt], "errors") == 0))
				nipper->ios->logging->loggingTrap = 3;
			else if ((strcmp(command.part[tempInt], "4") == 0) || (strcmp(command.part[tempInt], "warnings") == 0))
				nipper->ios->logging->loggingTrap = 4;
			else if ((strcmp(command.part[tempInt], "5") == 0) || (strcmp(command.part[tempInt], "notifications") == 0))
				nipper->ios->logging->loggingTrap = 5;
			else if ((strcmp(command.part[tempInt], "6") == 0) || (strcmp(command.part[tempInt], "informational") == 0))
				nipper->ios->logging->loggingTrap = 6;
			else if ((strcmp(command.part[tempInt], "7") == 0) || (strcmp(command.part[tempInt], "debugging") == 0))
				nipper->ios->logging->loggingTrap = 7;
		}
	}

	// Monitor
	else if (strcmp(command.part[tempInt], "monitor") == 0)
	{
		nipper->ios->logging->monitorLogging = setting;

		// Options
		if (tempInt < command.parts)
		{
			tempInt++;
			// Levels
			if ((strcmp(command.part[tempInt], "0") == 0) || (strcmp(command.part[tempInt], "emergencies") == 0))
				nipper->ios->logging->monitorLevel = 0;
			else if ((strcmp(command.part[tempInt], "1") == 0) || (strcmp(command.part[tempInt], "alerts") == 0))
				nipper->ios->logging->monitorLevel = 1;
			else if ((strcmp(command.part[tempInt], "2") == 0) || (strcmp(command.part[tempInt], "critical") == 0))
				nipper->ios->logging->monitorLevel = 2;
			else if ((strcmp(command.part[tempInt], "3") == 0) || (strcmp(command.part[tempInt], "errors") == 0))
				nipper->ios->logging->monitorLevel = 3;
			else if ((strcmp(command.part[tempInt], "4") == 0) || (strcmp(command.part[tempInt], "warnings") == 0))
				nipper->ios->logging->monitorLevel = 4;
			else if ((strcmp(command.part[tempInt], "5") == 0) || (strcmp(command.part[tempInt], "notifications") == 0))
				nipper->ios->logging->monitorLevel = 5;
			else if ((strcmp(command.part[tempInt], "6") == 0) || (strcmp(command.part[tempInt], "informational") == 0))
				nipper->ios->logging->monitorLevel = 6;
			else if ((strcmp(command.part[tempInt], "7") == 0) || (strcmp(command.part[tempInt], "debugging") == 0))
				nipper->ios->logging->monitorLevel = 7;
		}
	}

	// Origin ID
	else if (strcmp(command.part[tempInt], "origin-id") == 0)
	{
		tempInt++;
		if (strcmp(command.part[tempInt], "string") == 0)
			tempInt++;
		strncpy(nipper->ios->logging->originId, command.part[tempInt], sizeof(nipper->ios->logging->originId) - 1);
	}

	// Source Interface
	else if (strcmp(command.part[tempInt], "source-interface") == 0)
	{
		tempInt++;
		if (setting == true)
		{
			if (tempInt + 1 == command.parts)
				strncpy(nipper->ios->logging->sourceInterface, command.part[tempInt], sizeof(nipper->ios->logging->sourceInterface) -1);
			else
			{
				sprintf(tempString, "%s%s", command.part[tempInt], command.part[tempInt+1]);
				strncpy(nipper->ios->logging->sourceInterface, tempString, sizeof(nipper->ios->logging->sourceInterface) -1);
			}
		}
	}

	// Count
	else if (strcmp(command.part[tempInt], "count") == 0)
		nipper->ios->logging->logCount = setting;

	// Enable
	else if (strcmp(command.part[tempInt], "enable") == 0)
		nipper->ios->logging->logEnable = setting;

	// On
	else if (strcmp(command.part[tempInt], "on") == 0)
		nipper->ios->logging->logging = setting;

	// Facility
	else if (strcmp(command.part[tempInt], "facility") == 0)
		strncpy(nipper->ios->logging->facility, command.part[tempInt+1], sizeof(nipper->ios->logging->facility) - 1);

	// Unsupported logging lines..
	else if ((strcmp(command.part[tempInt], "userinfo") == 0) || (strcmp(command.part[tempInt], "synchronous") == 0) || (strcmp(command.part[tempInt], "size") == 0) || (strcmp(command.part[tempInt], "rate-limit") == 0) || (strcmp(command.part[tempInt], "monitor") == 0) || (strcmp(command.part[tempInt], "linecard") == 0) || (strcmp(command.part[tempInt], "history") == 0) || (strcmp(command.part[tempInt], "filter") == 0) || (strcmp(command.part[tempInt], "buffered") == 0) || (strcmp(command.part[tempInt], "console") == 0))
	{
		// Debug (lines not processed)
		if (nipper->linesnotprocessed == true)
			printf("%s\n", line);
	}

	// Logging Host
	else 
	{
		if (strcmp(command.part[tempInt], "host") == 0)
			tempInt++;
		// If first logging host
		if (nipper->ios->logging->logServer == 0)
		{
			// create structure
			nipper->ios->logging->logServer = malloc(sizeof(struct host));
			logServerPointer = nipper->ios->logging->logServer;
		}
		else
		{
			logServerPointer = nipper->ios->logging->logServer;
			while (logServerPointer->next != 0)
				logServerPointer = logServerPointer->next;
			logServerPointer->next = malloc(sizeof(struct host));
			logServerPointer = logServerPointer->next;
		}
		memset(logServerPointer, 0, sizeof(struct host));
		// add server
		strncpy(logServerPointer->server, command.part[tempInt], sizeof(logServerPointer->server) -1);
	}
}



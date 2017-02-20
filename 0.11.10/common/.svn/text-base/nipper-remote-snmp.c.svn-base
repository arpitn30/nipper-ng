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

#if !defined(__WIN32__)
void getRemoteConfig(struct nipperConfig *nipper, char *tempFile, int tempFileSize, char *localSave)
{
	// Variables...
	int tempInt = 0;
	int tempInt2 = 0;
	struct stat *fileStats = 0;
	char tempCommand[nipper->maxSize];

	// Get remote config?
	if (getuid() == 0)
	{

		// Create tftp file
		tempInt = rand();
		if (nipper->remoteTftp[strlen(nipper->remoteTftp) -1] != '/')
			nipper->remoteTftp[strlen(nipper->remoteTftp)] = '/';
		sprintf(tempCommand, "touch %s%d.config", nipper->remoteTftp, tempInt);
		system(tempCommand);

		// Set tftp file writable
		sprintf(tempCommand, "chmod 666 %s%d.config", nipper->remoteTftp, tempInt);
		system(tempCommand);

		// Old method?
		if (nipper->oldCisco == true)
		{
			// http://www.cisco.com/en/US/tech/tk648/tk362/technologies_tech_note09186a008009463e.shtml
			// Write to SNMP server
			sprintf(tempCommand, "snmpset -c %s -v 1 %s 1.3.6.1.4.1.9.2.1.55.%s s \"%d.config\"", nipper->remoteSnmp, nipper->remoteIP, nipper->localIP, tempInt);
			if (nipper->debugMode == true)
				printf("SNMP Command: %s\n", tempCommand);
			system(tempCommand);
		}

		// new method#if !defined(__WIN32__)
		else
		{
			// http://www.cisco.com/en/US/tech/tk648/tk362/technologies_tech_note09186a0080094aa6.shtml
			// Write to SNMP server
			tempInt2 = rand();
			sprintf(tempCommand, "snmpset -c %s -v 1 %s .1.3.6.1.4.1.9.9.96.1.1.1.1.2.%d i 1 .1.3.6.1.4.1.9.9.96.1.1.1.1.3.%d i 4 .1.3.6.1.4.1.9.9.96.1.1.1.1.4.%d i 1 .1.3.6.1.4.1.9.9.96.1.1.1.1.5.%d a \"%s\" .1.3.6.1.4.1.9.9.96.1.1.1.1.6.%d s \"%d.config\" .1.3.6.1.4.1.9.9.96.1.1.1.1.14.%d i 4", nipper->remoteSnmp, nipper->remoteIP, tempInt2, tempInt2, tempInt2, tempInt2, nipper->localIP, tempInt2, tempInt, tempInt2);
			if (nipper->debugMode == true)
				printf("SNMP Command: %s\n", tempCommand);
			system(tempCommand);
		}

		// Wait for a couple of secs (for file to arrive)
		system("sleep 3");

		// Check the file has content
		fileStats = malloc(sizeof(struct stat));
		memset(tempCommand, 0, sizeof(tempCommand));
		sprintf(tempCommand, "%s%d.config", nipper->remoteTftp, tempInt);
		stat(tempCommand, fileStats);

		// Cleanup SNMP if new...
		if (nipper->oldCisco == false)
		{
			memset(tempCommand, 0, sizeof(tempCommand));
			sprintf(tempCommand, "snmpset -c %s -v 1 %s .1.3.6.1.4.1.9.9.96.1.1.1.1.14.%d i 6", nipper->remoteSnmp, nipper->remoteIP, tempInt2);
			system(tempCommand);
		}

		// Exit if file has nothing in it...
		if (fileStats->st_size == 0)
		{
			free(fileStats);
			unlink(tempCommand);
			nipper->nipperMode = mode_help;
			nipper->helpMode = help_error_snmp_failure;
		}
		else
		{

			// If file is to called something...
			if (nipper->localSave != 0)
			{
				memset(tempCommand, 0, sizeof(tempCommand));
				sprintf(tempCommand, "mv %s%d.config %s", nipper->remoteTftp, tempInt, localSave);
				system(tempCommand);
				memset(tempCommand, 0, sizeof(tempCommand));
				sprintf(tempCommand, "%s", localSave);
				nipper->inputName = tempCommand;
			}
			else
			{
				sprintf(tempCommand, "%s%d.config", nipper->remoteTftp, tempInt);
				strncpy(tempFile, tempCommand, tempFileSize);
				nipper->inputName = tempFile;
			}
		}
		free(fileStats);
	}
	else
	{
		nipper->nipperMode = mode_help;
		nipper->helpMode = help_error_snmp_root;
	}
}
#endif

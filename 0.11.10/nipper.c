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

/*
The following files should be provided with this source code (as a minimum):

* INSTALL   - The compilation and installation guide
* LICENCE   - The licence covering all the files
* Changelog - A listing of all source code changes
* Readme    - Information about Nipper

*/


// Standard Includes...
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>


// Global Constants...
const char *program_banner = "                     _                           ____\n"
                             "               _ __ (_)_ __  _ __   ___ _ __    / ->/|\n"
                             "              | '_ \\| | '_ \\| '_ \\ / _ \\ '__|  /<-_/ |\n"
                             "              | | | | | |_) | |_) |  __/ |     |   | /\n"
                             "              |_| |_|_| .__/| .__/ \\___|_|     |___|/\n"
                             "                      |_|   |_|\n\n"
                             "                           Version 0.11.10\n"
                             "                     http://nipper.titania.co.uk\n"
                             "             Copyright (C) 2006-2008 Ian Ventura-Whiting\n";
const char *program_version_banner = "nipper version 0.11.10\nhttp://nipper.titania.co.uk\nCopyright (C) 2006-2008 Ian Ventura-Whiting";
const char *program_version = "0.11.10";


// Common structure/def includes...
#include "common/nipper-defs.c"
#include "common/nipper-struct.c"

// Program function includes...
#include "common/nipper-base64.c"
#include "common/nipper-common.c"
#include "common/nipper-config.c"
#include "common/nipper-cmdoptions.c"
#include "common/nipper-help.c"
#include "common/nipper-remote-snmp.c"

// Reporting function includes...
#include "common/report-appendix.c"
#include "common/report-text.c"
#include "common/report-functions.c"
#include "common/report-vulns.c"
#include "common/report.c"

// Common Device Code...
#include "common/nipper-objects.c"
#include "common/nipper-acl.c"

// Common Reporting Code...
#include "common/report-acl.c"
#include "common/report-debug.c"

// Cisco Common Support Code...
#include "cisco/report-acl.c"

// Cisco IOS Support...
#include "IOS/input.c"
#include "IOS/report.c"
#include "IOS/cleanup.c"

// Cisco NMP/CatOS Support...
#include "NMP/input.c"
#include "NMP/report.c"
#include "NMP/cleanup.c"

// Cisco PIX/ASA/FWSM Support...
#include "PIX/input.c"
#include "PIX/report.c"
#include "PIX/cleanup.c"

// Cisco CSS Support...
#include "CSS/input.c"
#include "CSS/report.c"
#include "CSS/cleanup.c"

// Juniper ScreenOS Support...
#include "ScreenOS/input.c"
#include "ScreenOS/report.c"
#include "ScreenOS/cleanup.c"

// Nortel Passport Support...
#include "Passport/input.c"
#include "Passport/report.c"
#include "Passport/cleanup.c"

// CheckPoint Firewall-1 Support...
#include "FW1/input.c"
#include "FW1/report.c"
#include "FW1/cleanup.c"

// SonicWall SonicOS Support...
#include "SonicOS/input.c"
#include "SonicOS/report.c"
#include "SonicOS/cleanup.c"

// Processing includes...
#include "common/nipper-defaults.c"
#include "common/nipper-input.c"
#include "common/nipper-namemappings.c"
#include "common/nipper-cleanup.c"


// ----------------------------------------------------
// PART 1: Program parameters & initialization

int main(int argc, char *argv[])
{
	// Program variables...
	int tempInt = 0;
	char buffer[LINE_SIZE];
	int sizeRead = 0;
	char temporaryFileName[64] = "";
	FILE *tempFileHandle = 0;
	FILE *inputFileHandle = 0;
	struct debugAbbrev *debugAbPointer = 0;
	struct johnPassword *johnPointer = 0;

	// Nipper Configuration...
	struct nipperConfig *nipper = createNipperConfig();

	// Get the command-line options...
	getCommandOptions(argc, argv, nipper);

	// Show on-line help?
	if (nipper->nipperMode == mode_help)
		showHelp(argc, argv, nipper);

	// Show version?
	else if (nipper->nipperMode == mode_version)
		printf("%s\n\n", program_version_banner);

// ----------------------------------------------------
// PART 2: Process Configuration File

	else if (nipper->nipperMode == mode_process)
	{

		// Get SNMP if it has been specified...
#if !defined(__WIN32__)
		if ((nipper->remoteIP[0] != 0) && (nipper->localIP[0] != 0) && (nipper->inputName == 0))
			getRemoteConfig(nipper, temporaryFileName, sizeof(temporaryFileName), argv[nipper->localSave]+13);

		// Get stdin if input has not been specified...
		else if (nipper->inputName == 0)
#else
		if (nipper->inputName == 0)
#endif
		{
			// Init...
			signal(14, stdinTimeout);
			inputFileHandle = stdin;

			// Read stdin...
			while (feof(inputFileHandle) == 0)
			{
				// Read...
				memset(buffer, 0, LINE_SIZE);
#if !defined(__WIN32__)
				alarm(2);
#endif
				sizeRead = fread(buffer, 1, LINE_SIZE, inputFileHandle);
#if !defined(__WIN32__)
				alarm(0);
#endif

				// Write to file...
				if (tempFileHandle == 0)
				{
					sprintf(temporaryFileName, "%sdelete-me-%d", tmpDir, rand());
					tempFileHandle = fopen(temporaryFileName, "w");
					fwrite(buffer, 1, sizeRead, tempFileHandle);
				}
				else
					fwrite(buffer, 1, sizeRead, tempFileHandle);
			}
			fclose(tempFileHandle);
			nipper->inputName = temporaryFileName;
		}

		// Debug Output?
		if ((nipper->debugMode == true) && (nipper->nipperMode == mode_process))
		{
			printf("%s\n", program_banner);

			printf("\n%sCommand Line Options\n====================%s\nCommand:", COL_BLUE, RESET);
			for (tempInt = 0; tempInt < argc; tempInt++)
			{
				printf(" %s", argv[tempInt]);
			}
			printf("\n\n");
		}

		// Process input file(s)/stdin/snmp...
		if (nipper->nipperMode == mode_process)
		{
			if (processInput(nipper) == true)
			{
				// Check that version has been identified for relevent configs...
				nipper->nipperMode = mode_process;
				if (nipper->force == false)
				{
					switch (nipper->deviceType)
					{
						case type_ios_switch:
						case type_ios_router:
						case type_ios_catalyst:
							if (nipper->versionMajor == 0)
							{
								nipper->nipperMode = mode_help;
								nipper->helpMode = help_error_wrong_type;
							}
							break;
			
						case type_nmp_catalyst:
						case type_cos_catalyst:
							if (nipper->versionMajor == 0)
							{
								nipper->nipperMode = mode_help;
								nipper->helpMode = help_error_wrong_type;
							}
							break;
			
						case type_pix_firewall:
						case type_asa_firewall:
						case type_fwsm_firewall:
							if (nipper->versionMajor == 0)
							{
								nipper->nipperMode = mode_help;
								nipper->helpMode = help_error_wrong_type;
							}
							break;
			
						case type_css_filter:
							if (nipper->versionMajor == 0)
							{
								nipper->nipperMode = mode_help;
								nipper->helpMode = help_error_wrong_type;
							}
							break;
			
						case type_sos_firewall:
						case type_sonicwall:
							if (nipper->hostname[0] == 0)
							{
								nipper->nipperMode = mode_help;
								nipper->helpMode = help_error_wrong_type;
							}
							break;
							
						case type_passport:
						case type_bayaccelar:
							if (nipper->pas->boxType[0] == 0)
							{
								nipper->nipperMode = mode_help;
								nipper->helpMode = help_error_wrong_type;
							}
							break;
					}
				}
			}
		}
		if (nipper->nipperMode == mode_help)
		{
			showHelp(argc, argv, nipper);
			cleanup(nipper);
			return 1;
		}


// ----------------------------------------------------
// PART 3: Report Pre-parsing

		// Default Settings...
		processDefaults(nipper);

		// Convert Names to IP Addresses...
		if (nipper->names == true)
			processNameMappings(nipper);

// ----------------------------------------------------
// PART 4: Reporting

		// Output debug information?
		if (nipper->debugMode == true)
		{
			switch (nipper->deviceType)
			{
				case type_ios_router:
				case type_ios_switch:
				case type_ios_catalyst:
					reportIOSDebug(nipper);
					break;

				case type_pix_firewall:
				case type_asa_firewall:
				case type_fwsm_firewall:
					reportPIXDebug(nipper);
					break;

				case type_nmp_catalyst:
				case type_cos_catalyst:
					reportNMPDebug(nipper);
					break;

				case type_css_filter:
					reportCSSDebug(nipper);
					break;

				case type_sos_firewall:
					reportSOSDebug(nipper);
					break;

				case type_passport:
				case type_bayaccelar:
					reportPASDebug(nipper);
					break;

				case type_fw1_firewall:
				case type_nokiaip:
					reportFW1Debug(nipper);
					break;

				case type_sonicwall:
					reportSonicOSDebug(nipper);
					break;
			}
		}

		// Output report & john (if specified)
		else
		{
			// Output john?
			if ((nipper->johnFile != 0) && (nipper->john != 0))
			{
				// Variables
				FILE *johnFile;

				// Create file
				johnFile = fopen(nipper->johnFile, "w");
				if (johnFile == NULL)
				{
					nipper->nipperMode = mode_help;
					nipper->helpMode = help_error_john_file;
				}
				else
				{

					// Write file contents
					johnPointer = nipper->john;
					while (johnPointer != 0)
					{
						fprintf(johnFile, "%s:%s\n", johnPointer->username, johnPointer->password);
						johnPointer = johnPointer->next;
					}
	
					// Close file
					fclose(johnFile);
				}
			}

			if (nipper->nipperMode == mode_help)
			{
				showHelp(argc, argv, nipper);
				cleanup(nipper);
				return 1;
			}

			// Generate the report
			switch (nipper->deviceType)
			{
				case type_ios_router:
				case type_ios_switch:
				case type_ios_catalyst:
					generateIOSReport(nipper);
					break;

				case type_pix_firewall:
				case type_asa_firewall:
				case type_fwsm_firewall:
					generatePIXReport(nipper);
					break;

				case type_cos_catalyst:
				case type_nmp_catalyst:
					generateNMPReport(nipper);
					break;

				case type_css_filter:
					generateCSSReport(nipper);
					break;

				case type_sos_firewall:
					generateSOSReport(nipper);
					break;

				case type_passport:
				case type_bayaccelar:
					generatePASReport(nipper);
					break;

				case type_fw1_firewall:
				case type_nokiaip:
					generateFW1Report(nipper);
					break;

				case type_sonicwall:
					generateSonicOSReport(nipper);
					break;
			}

			if (nipper->nipperMode == mode_help)
			{
				showHelp(argc, argv, nipper);
				cleanup(nipper);
				return 1;
			}

			// Output Debug Abbreviations
			if (nipper->debugAbbrev == true)
			{
				printf("\n%sUnknown Abbreviations\n=====================%s\n", COL_BLUE, RESET);
				debugAbPointer = debugAb;
				while (debugAbPointer != 0)
				{
					printf("  %s (%d)\n", debugAbPointer->ab, debugAbPointer->count);
					debugAbPointer = debugAbPointer->next;
				}
			}
		}


// ----------------------------------------------------
// PART 5: Cleanup

		// Stdin temporary file...
		if (temporaryFileName[0] != 0)
		{
			unlink(temporaryFileName);
		}
	}

	cleanup(nipper);

	return 0;
}

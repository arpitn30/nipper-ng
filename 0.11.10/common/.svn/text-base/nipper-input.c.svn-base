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

// This file contains all the code to get input from file/directory/snmp/stdin...


// Process a file...
int processFile(struct nipperConfig *nipper, void (processLine)(struct nipperConfig *nipper, char *line))
{
	// Variables...
	struct stat *fileStats = 0;
	char line[LINE_SIZE + 1];

	// Check the file has some contents...
	fileStats = malloc(sizeof(struct stat));
	memset(fileStats, 0, sizeof(struct stat));
	stat(nipper->inputName, fileStats);
	if (fileStats->st_size == 0)
	{
		free(fileStats);
		nipper->nipperMode = mode_help;
		nipper->helpMode = help_error_empty_file;
		return false;
	}
	free(fileStats);

	nipper->input = fopen(nipper->inputName, "r");
	if (nipper->input == NULL)
	{
		nipper->nipperMode = mode_help;
		nipper->helpMode = help_error_opening_file;
		return false;
	}
	setvbuf(nipper->input, 0, _IONBF, 0);

	if (nipper->debugMode == true)
	{
		printf("\n%sConfig Lines Examined\n=====================%s\n", COL_BLUE, RESET);
	}

	// Read in input and process...
	while (feof(nipper->input) == 0)
	{
		// Read line
		memset(line, 0, LINE_SIZE + 1);
		readLine(nipper->input, line, LINE_SIZE);

		// Process the line...
		processLine(nipper, line);
	}

	// Close input file...
	fclose(nipper->input);

	return true;
}


// Process the input...
int processInput(struct nipperConfig *nipper)
{
	// Variables...
	struct policyCollection *policyCollectionPointer = 0;
	struct stat *fileStats = 0;
	const char *dirname = 0;
	char *buffer = 0;
	char fullname[512];
	FILE *tempFile = 0;
	char temporaryFileName[64] = "";
	int returnValue = 0;
#if !defined(__WIN32__)
	const char slashChar = '/';
#else
	const char slashChar = '\\';
#endif
	int addSlash = false;

	switch (nipper->deviceType)
	{
		// IOS devices
		case type_ios_router:
		case type_ios_switch:
		case type_ios_catalyst:
			// Create IOS Structure...
			nipper->ios = malloc(sizeof(struct ciscoIOSConfig));

			// Init...
			memset(nipper->ios, 0, sizeof(struct ciscoIOSConfig));
			nipper->ios->sourceRouting = true;
			nipper->ios->tcpSmallServers = unconfigured;
			nipper->ios->udpSmallServers = unconfigured;
			nipper->ios->finger = unconfigured;
			nipper->ios->cdp = true;
			nipper->ios->cef = unconfigured;
			nipper->ios->servicePasswordEncryption = false;
			nipper->ios->bootp = true;
			nipper->ios->bootNetwork = false;
			nipper->ios->serviceConfig = false;
			nipper->ios->pad = true;
			nipper->ios->domainLookup = true;
			nipper->ios->classlessRouting = true;
			nipper->ios->keepAlivesIn = false;
			nipper->ios->keepAlivesOut = false;
			nipper->ios->gratuitousArps = false;
			nipper->ios->calendarValid = false;
			nipper->ios->passwordMinLength = -1;
			nipper->ios->vtpMode = vtp_mode_server;
			strcpy(nipper->ios->timeZone, "UTC");

			// Process...
			return processFile(nipper, processIOSInput);
			break;


		// NMP devices
		case type_nmp_catalyst:
		case type_cos_catalyst:
			// Create NMP/CatOS Structure...
			nipper->nmp = malloc(sizeof(struct ciscoNMPConfig));

			// Init...
			memset(nipper->nmp, 0, sizeof(struct ciscoNMPConfig));
			nipper->nmp->cdp = true;
			nipper->nmp->cdpInterval = 60;
			nipper->nmp->cdpHoldtime = 180;
			nipper->nmp->cdpVersion = 2;
			nipper->nmp->timeout = 20;
			nipper->nmp->portSecurityAuto = false;

			// Process...
			return processFile(nipper, processNMPInput);
			break;


		// PIX devices
		case type_pix_firewall:
		case type_asa_firewall:
		case type_fwsm_firewall:
			// Create PIX/ASA/FWSM Structure...
			nipper->pix = malloc(sizeof(struct ciscoPIXConfig));

			// Init...
			memset(nipper->pix, 0, sizeof(struct ciscoPIXConfig));
			nipper->pix->transparent = false;
			nipper->pix->floodguard = true;
			nipper->pix->accessListAlertInterval = 300;
			nipper->pix->accessListDenyFlowMax = 4096;

			// Process..
			return processFile(nipper, processPIXInput);
			break;


		// Cisco CSS devices
		case type_css_filter:
			// Create CSS Structure...
			nipper->css = malloc(sizeof(struct ciscoCSSConfig));

			// Init...
			memset(nipper->css, 0, sizeof(struct ciscoCSSConfig));
			nipper->css->snmpAccess = true;
			nipper->css->ftpAccess = true;
			nipper->css->telnetAccess = true;
			nipper->css->sshAccess = true;
			nipper->css->consoleAccess = true;
			nipper->css->webManagementAccess = false;
			nipper->css->aclEnabled = false;

			// Process...
			return processFile(nipper, processCSSInput);
			break;


		// ScreenOS devices
		case type_sos_firewall:
			// Create ScreenOS Structure...
			nipper->sos = malloc(sizeof(struct screenOSConfig));

			// Init...
			memset(nipper->sos, 0, sizeof(struct screenOSConfig));
			nipper->sos->sshEnabled = false;
			nipper->sos->sshKeyGenTime = 60;
			nipper->sos->asymmetricVPN = false;
			nipper->sos->accessAttempts = 3;
			nipper->sos->mailAlert = false;
			nipper->sos->adminFormat = adminfmt_default;
			nipper->sos->httpRedirect = unconfigured;
			nipper->sos->privilege = adminpriv_default;
			strcpy(nipper->sos->adminIP, "0.0.0.0");
			strcpy(nipper->sos->adminNetMask, "0.0.0.0");
			strcpy(nipper->sos->name, "netscreen");
			strcpy(nipper->sos->password, "");
			nipper->sos->nameMappings = false;
			nipper->sos->nameGroupMappings = false;
			nipper->sos->defaultFirewallMode = true;
			nipper->sos->consoleOnly = false;

			// Process...
			return processFile(nipper, processSOSInput);
			break;


		// Nortel Passport Devices
		case type_bayaccelar:
		case type_passport:
			// Create Nortel Passport Structure...
			nipper->pas = malloc(sizeof(struct passportConfig));

			// Init...
			memset(nipper->pas, 0, sizeof(struct passportConfig));

			// Process...
			return processFile(nipper, processPASInput);
			break;


		// CheckPoint Firewall-1 Devices
		case type_nokiaip:
		case type_fw1_firewall:
			// Create Structure...
			nipper->fw1 = malloc(sizeof(struct firewall1Config));
			fileStats = malloc(sizeof(struct stat));

			// Init...
			memset(nipper->fw1, 0, sizeof(struct firewall1Config));
			memset(fileStats, 0, sizeof(struct stat));

			if (nipper->showACLComments == true)
				settings_policycol_heading8.next = &settings_policycol_heading9;

			// Check that the Config directory is a directory...
			stat(nipper->inputName, fileStats);

			// Process as a single file...
			if ((fileStats->st_mode & S_IFMT) != S_IFDIR)
			{
				free(fileStats);
				return processFile(nipper, processFW1Input);
			}

			// Process as a directory...
			else
			{
				free(fileStats);

				// Set Directory name...
				dirname = nipper->inputName;

				// Slash Char?
#if !defined(__WIN32__)
				if (dirname[strlen(dirname) - 1] == '/')
#else
				if (dirname[strlen(dirname) - 1] == '\\')
#endif
					addSlash = false;
				else
					addSlash = true;

				// ------------------------
				// Process Objects Files...

				// Process objects_5_0.C
				memset(fullname, 0, sizeof(fullname));
				if (addSlash == false)
					sprintf(fullname, "%sobjects_5_0.C", dirname);
				else
					sprintf(fullname, "%s%cobjects_5_0.C", dirname, slashChar);
				nipper->inputName = fullname;
				returnValue = processFile(nipper, processFW1Input);

				if (returnValue == false)
				{
					// Process objects.C_41
					memset(fullname, 0, sizeof(fullname));
					if (addSlash == false)
						sprintf(fullname, "%sobjects.C_41", dirname);
					else
						sprintf(fullname, "%s%cobjects.C_41", dirname, slashChar);
					nipper->inputName = fullname;
					returnValue = processFile(nipper, processFW1Input);

					// Process objects.C
					if (returnValue == false)
					{
						memset(fullname, 0, sizeof(fullname));
						if (addSlash == false)
							sprintf(fullname, "%sobjects.C", dirname);
						else
							sprintf(fullname, "%s%cobjects.C", dirname, slashChar);
						nipper->inputName = fullname;
						returnValue = processFile(nipper, processFW1Input);
						if (returnValue == false)
						{
							if (addSlash == false)
								sprintf(fullname, "%sobjects.c", dirname);
							else
								sprintf(fullname, "%s%cobjects.c", dirname, slashChar);
							nipper->inputName = fullname;
							returnValue = processFile(nipper, processFW1Input);
						}
					}
				}

				// ---------------------
				// Process Rule Files...

				// Process the Rules files...
				policyCollectionPointer = nipper->fw1->policies;
				while (policyCollectionPointer != 0)
				{
					memset(fullname, 0, sizeof(fullname));
					if (addSlash == false)
						sprintf(fullname, "%s%s.W", dirname, policyCollectionPointer->name);
					else
						sprintf(fullname, "%s%c%s.W", dirname, slashChar, policyCollectionPointer->name);
					nipper->inputName = fullname;
					returnValue = processFile(nipper, processFW1RuleInput);
					policyCollectionPointer = policyCollectionPointer->next;
				}

				// Process rules.C file...
				memset(fullname, 0, sizeof(fullname));
				if (addSlash == false)
					sprintf(fullname, "%srules.C", dirname);
				else
					sprintf(fullname, "%s%crules.C", dirname, slashChar);
				nipper->inputName = fullname;
				returnValue = processFile(nipper, processFW1RulesInput);
				if (returnValue == false)
				{
					if (addSlash == false)
						sprintf(fullname, "%srules.c", dirname);
					else
						sprintf(fullname, "%s%crules.c", dirname, slashChar);
					nipper->inputName = fullname;
					returnValue = processFile(nipper, processFW1RulesInput);
				}

				// Process the Rulebase files (for comments mostly)...
				memset(fullname, 0, sizeof(fullname));
				if (addSlash == false)
					sprintf(fullname, "%srulebases_5_0.fws", dirname);
				else
					sprintf(fullname, "%s%crulebases_5_0.fws", dirname, slashChar);
				nipper->inputName = fullname;
				returnValue = processFile(nipper, processFW1RuleInput);

				if (returnValue == false)
				{
					// Oh well, try this one then...
					memset(fullname, 0, sizeof(fullname));
					if (addSlash == false)
						sprintf(fullname, "%srulebases.fws", dirname);
					else
						sprintf(fullname, "%s%crulebases.fws", dirname, slashChar);
					nipper->inputName = fullname;
					returnValue = processFile(nipper, processFW1Input);
				}

				return true;
			}
			break;

		// Sonic Wall devices...
		case type_sonicwall:
			// SonicWall configs are base64 encoded. The file needs to be decoded first...

			// Check the file has some contents...
			fileStats = malloc(sizeof(struct stat));
			stat(nipper->inputName, fileStats);
			if (fileStats->st_size == 0)
			{
				free(fileStats);
				nipper->nipperMode = mode_help;
				nipper->helpMode = help_error_empty_file;
				return false;
			}

			// Set buffer to the size of the file...
			buffer = malloc(fileStats->st_size + 1);
			memset (buffer, 0, fileStats->st_size + 1);
			tempFile = fopen(nipper->inputName, "r");
			fread(buffer, 1, fileStats->st_size, tempFile);
			fclose(tempFile);
			returnValue = base64DecodeChars(buffer);
			if (returnValue == true)
			{
				sprintf(temporaryFileName, "%sdelete-me-%d", tmpDir, rand());
				tempFile = fopen(temporaryFileName, "w");
				fwrite(buffer, 1, strlen(buffer), tempFile);
				fclose(tempFile);
				nipper->inputName = temporaryFileName;
			}
			free(buffer);
			free(fileStats);

			// If base64 decode failed...
			if (returnValue == false)
			{
				nipper->nipperMode = mode_help;
				nipper->helpMode = help_error_base64_decode;
				return false;
			}

			// Create Structure...
			nipper->sonicos = malloc(sizeof(struct sonicosConfig));

			// Init...
			memset(nipper->sonicos, 0, sizeof(struct sonicosConfig));
			nipper->sonicos->enhanced = false;

			// Process...
			returnValue = processFile(nipper, processSonicOSInput);

			// Cleanup
			unlink(temporaryFileName);
			break;
	}

	return false;
}


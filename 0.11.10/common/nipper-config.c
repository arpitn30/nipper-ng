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

// This file contains all the code for nipper configuration...


// External default settings file...
#if !defined(__WIN32__)
char *configFilename = "/etc/nipper.conf";
#else
char *configFilename = "nipper.ini";
#endif


// Get setting...
// Parameters
//    section : should include the square braces (E.g. "[passwords]")
//    setting : is the setting that you are looking for
//    default setting : will return 
//    size : The size of the default storage space (incl null termination).
// Returns
//    True or False
//    The defaultSetting is replaced by new setting
int getSettingString(char *section, char *setting, char *defaultSetting, int size)
{
	// Variables...
	struct stat *fileStats = 0;
	FILE *configFile = 0;
	char line[LINE_SIZE + 1];
	char *tempString = 0;

	// Check that the file exists and is not empty...
	fileStats = malloc(sizeof(struct stat));
	memset(fileStats, 0, sizeof(struct stat));
	stat(configFilename, fileStats);
	if (fileStats->st_size != 0)
	{
		free(fileStats);

		// Open Config...
		configFile = fopen(configFilename, "r");
		if (configFile != NULL)
		{

			// Search for section...
			do
			{
				// Read line
				memset(line, 0, LINE_SIZE + 1);
				readLine(configFile, line, LINE_SIZE);
			}
			while ((feof(configFile) == 0) && (strncasecmp(section, line, strlen(section)) != 0));
		
			// if not found, return...
			if (strncasecmp(section, line, strlen(section)) != 0)
			{
				fclose(configFile);
				return false;
			}

			// Search for setting...
			do
			{
				// Read line
				memset(line, 0, LINE_SIZE + 1);
				readLine(configFile, line, LINE_SIZE);
			}
			while ((feof(configFile) == 0) && (strncasecmp(setting, line, strlen(setting)) != 0) && (line[0] != '['));
			fclose(configFile);

			// If not found, return...
			if (strncasecmp(setting, line, strlen(setting)) != 0)
				return false;
		
			// Search for the =...
			tempString = strchr(line, '=');
			if (tempString == NULL)
				return false;
			tempString++;
		
			// Search for the first character...
			while ((tempString[0] != 0) && (tempString[0] == ' '))
				tempString++;
		
			// If there is a setting, return it...
			if (tempString[0] != 0)
			{
				memset(defaultSetting, 0, size);
				strncpy(defaultSetting, tempString, size - 1);
				return true;
			}
			else
				return false;
		}
	}
	else
		free(fileStats);

	return false;
}


// Gets the setting as Int, same as above...
//   For on/off or true/false it will return true or false
//   This one returns the default setting
int getSettingInt(char *section, char *setting, int defaultSetting)
{
	// Variables...
	char tempString[] = "false";
	int tempInt;

	// Get Setting...
	tempInt = getSettingString(section, setting, tempString, sizeof(tempString));

	// If error, return default
	if (tempInt == false)
		return defaultSetting;

	// If false or off
	if ((strncasecmp(tempString, "no", 2) == 0) || (strncasecmp(tempString, "off", 3) == 0) || (strncasecmp(tempString, "false", 5) == 0))
		return false;

	// If true or on
	if ((strncasecmp(tempString, "yes", 3) == 0) || (strncasecmp(tempString, "on", 2) == 0) || (strncasecmp(tempString, "true", 4) == 0))
		return true;

	return atoi(tempString);
}


// Create the Nipper configuration structure...
struct nipperConfig *createNipperConfig()
{
	// Variables...
	struct nipperConfig *nipper;
	char tempString[LINE_SIZE];

	// Reserve Memory...
	nipper = malloc(sizeof(struct nipperConfig));
	memset(nipper, 0, sizeof(struct nipperConfig));

	// nipper Program Option Defaults...
	nipper->maxSize = LINE_SIZE;
	nipper->tableNum = 1;
	nipper->nipperMode = mode_process;
	nipper->deviceUse = use_all;
	nipper->doCSV = false;
	nipper->showACLComments = false;

	// General
	strcpy(tempString, "Cisco Router (IOS)");
	getSettingString("[General]", "Device Type", tempString, sizeof(tempString));
	if (strncasecmp(tempString, "Cisco Switch (IOS)", 18) == 0)
		nipper->deviceType = type_ios_switch;
	else if (strncasecmp(tempString, "Cisco Catalyst (IOS)", 20) == 0)
		nipper->deviceType = type_ios_catalyst;
	else if (strncasecmp(tempString, "Cisco Catalyst (NMP)", 20) == 0)
		nipper->deviceType = type_nmp_catalyst;
	else if (strncasecmp(tempString, "Cisco Catalyst (CatOS)", 22) == 0)
		nipper->deviceType = type_cos_catalyst;
	else if (strncasecmp(tempString, "Cisco Firewall (PIX)", 20) == 0)
		nipper->deviceType = type_pix_firewall;
	else if (strncasecmp(tempString, "Cisco Firewall (ASA)", 20) == 0)
		nipper->deviceType = type_asa_firewall;
	else if (strncasecmp(tempString, "Cisco Firewall (FWSM)", 21) == 0)
		nipper->deviceType = type_fwsm_firewall;
	else if (strncasecmp(tempString, "Cisco Content Services Switch (CSS)", 35) == 0)
		nipper->deviceType = type_css_filter;
	else if (strncasecmp(tempString, "Juniper ScreenOS Firewall", 25) == 0)
		nipper->deviceType = type_sos_firewall;
	else if (strncasecmp(tempString, "Nortel Passport", 15) == 0)
		nipper->deviceType = type_passport;
	else if (strncasecmp(tempString, "Checkpoint Firewall-1", 21) == 0)
		nipper->deviceType = type_fw1_firewall;
	else if (strncasecmp(tempString, "SonicWall SonicOS Firewall", 26) == 0)
		nipper->deviceType = type_sonicwall;
	else
		nipper->deviceType = type_ios_router;
	strcpy(tempString, "Internal");
	getSettingString("[General]", "Location", tempString, sizeof(tempString));
	if (strncasecmp(tempString, "Edge", 4) == 0)
		nipper->deviceUse = use_edge;
	else if (strncasecmp(tempString, "Internal", 4) == 0)
		nipper->deviceUse = use_internal;
	else
		nipper->deviceUse = use_all;
	strcpy(tempString, "");
	getSettingString("[General]", "Model", tempString, sizeof(tempString));
	if (tempString[0] != 0)
	{
		nipper->deviceModelInt = malloc(strlen(tempString) + 1);
		strcpy(nipper->deviceModelInt, tempString);
		nipper->deviceModel = nipper->deviceModelInt;
	}
	nipper->force = getSettingInt("[General]", "Force Type", false);

	// HTML...
	strcpy(tempString, "");
	getSettingString("[HTML]", "Style Sheet File", tempString, sizeof(tempString));
	if (tempString[0] != 0)
	{
		nipper->cssFromConfig = malloc(strlen(tempString) + 1);
		strcpy(nipper->cssFromConfig, tempString);
		nipper->cssFile = nipper->cssFromConfig;
	}

	// Latex Report Defaults...
	strcpy(nipper->paperSize, "a4paper");
	getSettingString("[Latex]", "Paper Size", nipper->paperSize, sizeof(nipper->paperSize));
	strcpy(nipper->documentClass, "article");
	getSettingString("[Latex]", "Document Class", nipper->documentClass, sizeof(nipper->documentClass));

	// SNMP Defaults...
	strcpy(nipper->remoteSnmp, "private");
	getSettingString("[SNMP]", "Community String", nipper->remoteSnmp, sizeof(nipper->remoteSnmp));
	nipper->oldCisco = getSettingInt("[SNMP]", "Old Cisco Method", false);
	strcpy(nipper->remoteTftp, "/tftproot/");
	getSettingString("[SNMP]", "TFTP Server Root", nipper->remoteTftp, sizeof(nipper->remoteTftp));
	getSettingString("[SNMP]", "Local IP Address", nipper->localIP, sizeof(nipper->localIP));
	getSettingString("[SNMP]", "Remote IP Address", nipper->remoteIP, sizeof(nipper->remoteIP));

	// Report Defaults...
	strcpy(nipper->companyName, "Nipper");
	getSettingString("[Report]", "Company Name", nipper->companyName, sizeof(nipper->companyName));
	strcpy(tempString, "HTML");
	getSettingString("[Report]", "Report Format", tempString, sizeof(tempString));
	if (strncasecmp(tempString, "text", 4) == 0)
		nipper->outputFormat = output_text;
	else if (strncasecmp(tempString, "latex", 5) == 0)
		nipper->outputFormat = output_latex;
	else if (strncasecmp(tempString, "xml", 3) == 0)
		nipper->outputFormat = output_xml;
	else
		nipper->outputFormat = output_html;
	nipper->passwords = getSettingInt("[Report]", "Show Passwords In Report", true);
	nipper->expandACL = getSettingInt("[Report]", "Expand ACL In Report", false);
	nipper->names = getSettingInt("[Report]", "Convert Names To IP Addresses", false);

	// Debug settings (internal only)...
	nipper->debugMode = false;
	nipper->linesnotprocessed = false;
	nipper->debugAbbrev = false;

	// Report Section Defaults...
	nipper->abs = getSettingInt("[Report Sections]", "Abbreviations", true);
	nipper->appendix = getSettingInt("[Report Sections]", "Appendix", true);
	nipper->loggingLevels = getSettingInt("[Report Sections]", "Logging Levels", true);
	nipper->timeZones = getSettingInt("[Report Sections]", "Time Zones", true);
	nipper->glossary = getSettingInt("[Report Sections]", "Glossary", true);
	nipper->nipperVersion = getSettingInt("[Report Sections]", "Nipper Details", true);
	nipper->commonPorts = getSettingInt("[Report Sections]", "Common Ports", true);
	nipper->fullReport = getSettingInt("[Report Sections]", "Security Audit", true);
	nipper->configReport = getSettingInt("[Report Sections]", "Configuration Report", true);

	// Password Audit Defaults...
	strcpy(tempString, "");
	getSettingString("[Audit]", "Dictionary File", tempString, sizeof(tempString));
	if (tempString[0] != 0)
	{
		nipper->dictionaryFilename = malloc(strlen(tempString) + 1);
		strcpy(nipper->dictionaryFilename, tempString);
		nipper->dictionaryFile = nipper->dictionaryFilename;
	}
	nipper->passwordLength = getSettingInt("[Audit]", "Minimum Password Length", 8);
	nipper->passwordUppers = getSettingInt("[Audit]", "Passwords Must Include Uppercase", false);
	nipper->passwordLowers = getSettingInt("[Audit]", "Passwords Must Include Lowercase", false);
	nipper->passwordEither = getSettingInt("[Audit]", "Passwords Must Include Lowercase or Uppercase", false);
	nipper->passwordNumbers = getSettingInt("[Audit]", "Passwords Must Include Numbers", true);
	nipper->passwordSpecials = getSettingInt("[Audit]", "Passwords Must Include Special Characters", false);
	// Timeout Audit Defaults...
	nipper->connectionTimeout = getSettingInt("[Audit]", "Minimum Timeout (Seconds)", 600);
	// ACL Audit Defaults...
	nipper->anySourceIssue = getSettingInt("[Audit]", "Check For Any Source", true);
	nipper->networkSourceIssue = getSettingInt("[Audit]", "Check Source Rules Do Not Include Networks", true);
	nipper->anySourceServiceIssue = getSettingInt("[Audit]", "Check For Any Source Service", false);
	nipper->anyDestinationIssue = getSettingInt("[Audit]", "Check For Any Destination", true);
	nipper->networkDestinationIssue = getSettingInt("[Audit]", "Check Destination Rules Do Not Include Networks", true);
	nipper->anyDestinationServiceIssue = getSettingInt("[Audit]", "Check For Any Destination Service", true);
	nipper->allRulesLogIssue = getSettingInt("[Audit]", "Check That All Rules Log", false);
	nipper->logDenyRulesIssue = getSettingInt("[Audit]", "Check That All Deny Rules Log", true);
	nipper->rejectRulesIssue = getSettingInt("[Audit]", "Check For Reject Rules", true);
	nipper->bypassRulesIssue = getSettingInt("[Audit]", "Check For Bypass Rules", true);
	nipper->defaultRulesIssue = getSettingInt("[Audit]", "Check For Default Rules", true);
	nipper->disabledRulesIssue = getSettingInt("[Audit]", "Check For Disabled Rules", true);
	nipper->denyLogIssue = getSettingInt("[Audit]", "Check Rule Lists End With Deny All And Log", true);

	return nipper;
}

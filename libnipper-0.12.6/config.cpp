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
 *      2. Any code that makes use of this library MUST display the        *
 *         returned text of the Nipper::getVersion() method. Since the     *
 *         text returned includes the version details and copyright of     *
 *         the library, the sugested place to show it would be with the    *
 *         callers "about program" information.                            *
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


// Includes...
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "globaldefs.h"
#include "config.h"

using namespace std;

// Default console colours...
const char *CONSOLE_COL_RESET = "[0m";
const char *CONSOLE_COL_RED = "[31m";
const char *CONSOLE_COL_BLUE = "[34m";
const char *CONSOLE_COL_GREEN = "[32m";
const char *CONSOLE_COL_EMPTY = "";


// Internal settings...
int internalError = 0;
const char *configFilename = 0;
FILE *configFile = 0;

// Internal setting strings...
string internDeviceModel;
string internDeviceName;
string internSNMPAddress;
string internSNMPCommunity;
string internCompanyName;
string internHTMLStylesheet;
string internLatexPaper;
string internLatexDocumentClass;
string internPasswordDictionary;


// Constructor...
Config::Config()
{
	// Colour Console Output...
#if !defined(__WIN32__)
	COL_RESET = CONSOLE_COL_RESET;
	COL_RED = CONSOLE_COL_RED;
	COL_BLUE = CONSOLE_COL_BLUE;
	COL_GREEN = CONSOLE_COL_GREEN;
#else
	COL_RESET = CONSOLE_COL_EMPTY;
	COL_RED = CONSOLE_COL_EMPTY;
	COL_BLUE = CONSOLE_COL_EMPTY;
	COL_GREEN = CONSOLE_COL_EMPTY;
#endif

	// Set the Nipper internal defaults...
	clearTextService = 0;
	dangerousService = 0;
	unnecessaryService = 0;
	complianceCheckList = 0;
	deviceType = Config::AutodetectDevice;
	deviceTypeChecks = true;
	internDeviceModel = "";
	deviceModel = 0;
	osVersion = 0;
	internDeviceName = "";
	deviceName = 0;
	deviceLocation = Config::Internal;
	inputSource = 0;
	outputDestination = 0;
	internSNMPAddress = "";
	snmpAddress = 0;
	internSNMPCommunity = "private";
	snmpCommunity = internSNMPCommunity.c_str();
	johnFile = 0;
	reportFormat = Config::HTML;
	internCompanyName = "Nipper";
	companyName = internCompanyName.c_str();
	internHTMLStylesheet = "";
	htmlStylesheet = 0;
	internLatexPaper = "a4paper";
	latexPaper = internLatexPaper.c_str();
	internLatexDocumentClass = "article";
	latexDocumentClass = internLatexDocumentClass.c_str();
	includePasswordsInReport = true;
	includeFilterRuleComments = false;
	convertNamesToAddresses = false;
	includeSecurityAudit = true;
	includeConfigurationReport = true;
	includeComplianceCheck = false;
	includeAppendixSection = true;
	includeGlossary = true;
	includeNetworkPorts = true;
	includeIPProtocols = true;
	includeICMPTypes = true;
	includeNipperVersion = true;
	includeLoggingLevels = true;
	includeTimeZones = true;
	includeAbbreviations = true;
	includeAuditorInformation = false;
	debugLinesNotProcessed = false;
	debugAbbreviations = false;
	issueOrdering = byOverallRating;
	
	// Password Strength Auditing...
	minimumPasswordLength = 8;						// Minimum password length
	maximumRepeatedChars = 3;						// Maximum number of repeated characters
	passwordsMustIncludeUppers = true;				// Passwords must include uppercase (A-Z)
	passwordsMustIncludeLowers = true;				// Passwords must include lowercase (a-z)
	passwordsMustIncludeEitherCase = false;			// Passwords must include alphabetical (a-zA-Z)
	passwordsMustIncludeNumbers = true;				// Passwords must include numbers
	passwordsMustIncludeSpecials = true;			// Passwords must include non alphanumeric characters
	differentFromUsername = true;					// Passwords should not match the username
	differentFromHostname = true;					// Passwords should not match the hostname
	noDeviceInformationInPasswords =true;			// Passwords should not be based on any device information (such as model, make...)
	noDictionaryCharacterSubst = true;				// Passwords should not be dictionary-based with character substitution
	noCharacterSequences = true;					// Passwords should not contain character sequences (e.g. qwerty or 1234)
	noCommonDictionaryAppends = true;				// Passwords should not be dictionary-based with common appends (e.g. !, 123 and so on)
	internPasswordDictionary = "";					// A dictionary file to test the passwords against
	passwordDictionary = 0;

	// Misc Audit settings...
	connectionTimeouts = 600;

	// Network Filtering Auditing...
	ignoreNonTCPUDPFilters = false;					// Ignore filters that are not for TCP/UDP protocols
	checkFilteringIsConfigured = true;				// Checks that filtering is configured
	checkFilterDefaultAllowAction = true;			// Checks for default allow filtering configuration
	checkFilterForAnySource = true;					// Checks for Any Source rules
	checkFilterForNetworkSource = true;				// Checks for Network Source rules
	checkFilterForAnySourcePort = true;				// Checks for Any Source port rules
	checkFilterForRangeSourcePort = true;			// Checks for Range Source port rules
	checkFilterForAnyDestination = true;			// Checks for any desintation rules
	checkFilterForNetworkDestination = true;		// Checks for network destination rules
	checkFilterForAnyDestinationPort = true;		// Checks for any destination port rules
	checkFilterForRangeDestinationPort = true;		// Checks for range destination port rules
	checkFilterLogsAllowedRules = true;				// Checks that allowed rules log
	checkFilterForLogDeniedRules = true;			// Checks that denied rules log
	checkFilterEndsWithDenyAllAndLog = true;		// Checks that a rules list ends with a deny all and log
	checkFilterForRejectRules = true;				// Checks for reject rules
	checkFilterForBypassRules = true;				// Checks for bypass rules
	checkFilterForDefaultRules = true;				// Checks for rules that allow a default action (i.e. passport ports)
	checkFilterForRulesWithoutComments = false;		// Checks for rules with no comments
	checkFilterForDisabledRules = true;				// Checks for disabled rules
	checkFilterForUnusedRulesAtListEnd = true;		// Checks for unused rules at the end of a list (i.e. after a deny all)
	checkFilterForClearTextRules = true;			// Checks for rules that allow clear-text protocols through
	checkFilterForDangerousRules = true;			// Checks for rules that allow dangerous services through
	checkFilterForUnnecessaryRules = true;			// Checks for rules that allow unnecessary services through
	checkFilterForDuplicateRules = true;			// Checks for rules that overlap/duplicates
	checkFilterForContradictRules = true;			// Checks for rules that contradict other rules
	checkFilterForUnusedRuleLists = true;			// Checks for unused rules

	emptyTableCell = "-";
}


// Destructor...
Config::~Config()
{
	// Variables...
	protocolServiceList *protocolServicePointer = 0;

	while (clearTextService != 0)
	{
		protocolServicePointer = clearTextService->next;
		delete [] clearTextService->service;
		delete clearTextService;
		clearTextService = protocolServicePointer;
	}

	while (dangerousService != 0)
	{
		protocolServicePointer = dangerousService->next;
		delete [] dangerousService->service;
		delete dangerousService;
		dangerousService = protocolServicePointer;
	}

	while (unnecessaryService != 0)
	{
		protocolServicePointer = unnecessaryService->next;
		delete [] unnecessaryService->service;
		delete unnecessaryService;
		unnecessaryService = protocolServicePointer;
	}
}


// Get a string setting from a configration file...
string tempSettingString;
const char *Config::getSettingString(const char *section, const char *setting, const char *defaultSetting)
{
	// Variables...
	int tempInt = 0;
	char line[256];
	char *settingPointer = 0;

	rewind(configFile);

	// Search for section...
	do
	{
		// Read line
		memset(line, 0, sizeof(line));
		fgets(line, sizeof(line), configFile);
	}
	while ((feof(configFile) == 0) && (strncasecmp(section, line, strlen(section)) != 0));
		
	// If not found, return the default...
	if (strncasecmp(section, line, strlen(section)) != 0)
		tempSettingString.assign(defaultSetting);
	else
	{

		// Search for setting...
		do
		{
			// Read line
			memset(line, 0, sizeof(line));
			fgets(line, sizeof(line), configFile);
		}
		while ((feof(configFile) == 0) && (strncasecmp(setting, line, strlen(setting)) != 0) && (line[0] != '['));

		// If not found, return the default...
		if (strncasecmp(setting, line, strlen(setting)) != 0)
			tempSettingString.assign(defaultSetting);
		else
		{

			// Clear the end-of-line stuff...
			tempInt = strlen(line) - 1;
			while ((line[tempInt] == '\r') || (line[tempInt] == '\n') || (line[tempInt] == ' '))
			{
				line[tempInt] = 0;
				tempInt--;
			}

			// Search for the =...
			settingPointer = strchr(line, '=');
			if (settingPointer == NULL)
				tempSettingString.assign(defaultSetting);
			else
			{
				settingPointer++;
	
				// Search for the first character...
				while ((settingPointer[0] != 0) && (settingPointer[0] == ' '))
					settingPointer++;
	
				// If there is a setting, return it...
				if (settingPointer[0] != 0)
					tempSettingString.assign(settingPointer);
				else
					tempSettingString.assign(defaultSetting);
			}
		}
	}

	// Return...
	return tempSettingString.c_str();
}


// Gets a setting from the configuration file as an integer...
int Config::getSettingInt(const char *section, const char *setting, int defaultSetting)
{
	// Variables...
	string tempString;
	string defaultString("%d", defaultSetting);

	// Get Setting...
	tempString = getSettingString(section, setting, defaultString.c_str());

	return atoi(tempString.c_str());
}


// Gets a setting from the configuration file as a boolean...
bool Config::getSettingBool(const char *section, const char *setting, bool defaultSetting)
{
	// Variables...
	string tempString;
	string defaultString;

	// Set default string...
	if (defaultSetting == true)
		defaultString = "true";
	else
		defaultString = "false";

	// Get Setting...
	tempString.assign(getSettingString(section, setting, defaultString.c_str()));

	// If false or off
	if ((strncasecmp(tempString.c_str(), "no", 2) == 0) || (strncasecmp(tempString.c_str(), "off", 3) == 0) || (strncasecmp(tempString.c_str(), "false", 5) == 0))
		return false;

	// If true or on
	else if ((strncasecmp(tempString.c_str(), "yes", 3) == 0) || (strncasecmp(tempString.c_str(), "on", 2) == 0) || (strncasecmp(tempString.c_str(), "true", 4) == 0))
		return true;

	else
		return defaultSetting;
}


int Config::setConfigFile(const char *config)
{
	// Variables...
	int tempInt = 0;
	char line[256];
	char *settingPointer = 0;
	string tempString;
	struct stat *fileStats = 0;

	// Init...
	configFilename = config;
	internalError = 0;

	// Check that the file exists and is not empty...
	fileStats = new (struct stat);
	if (fileStats == 0)
		internalError = libnipper_error_memoryalloc;
	memset(fileStats, 0, sizeof(struct stat));
	stat(configFilename, fileStats);
	if (fileStats->st_size != 0)
	{

		// Open Config...
		configFile = fopen(configFilename, "r");
		if (configFile != NULL)
		{

			// Device types...
			switch (deviceType)
			{
				case Config::CiscoIOSRouter:
					tempString = getSettingString("[General]", "Device Type", "Cisco Router (IOS)");
					break;
				case Config::CiscoIOSCatalyst:
					tempString = getSettingString("[General]", "Device Type", "Cisco Catalyst (IOS)");
					break;
				case Config::CiscoNMPCatalyst:
					tempString = getSettingString("[General]", "Device Type", "Cisco Catalyst (NMP)");
					break;
				case Config::CiscoCatOSCatalyst:
					tempString = getSettingString("[General]", "Device Type", "Cisco Catalyst (CatOS)");
					break;
				case Config::CiscoPIXFirewall:
					tempString = getSettingString("[General]", "Device Type", "Cisco Firewall (PIX)");
					break;
				case Config::CiscoASAFirewall:
					tempString = getSettingString("[General]", "Device Type", "Cisco Firewall (ASA)");
					break;
				case Config::CiscoFWSMFirewall:
					tempString = getSettingString("[General]", "Device Type", "Cisco Firewall (FWSM)");
					break;
				case Config::CiscoCSS:
					tempString = getSettingString("[General]", "Device Type", "Cisco Content Services Switch (CSS)");
					break;
				case Config::JuniperScreenOS:
					tempString = getSettingString("[General]", "Device Type", "Juniper ScreenOS Firewall");
					break;
				case Config::NortelPassport:
					tempString = getSettingString("[General]", "Device Type", "Nortel Passport");
					break;
				case Config::NortelRoutingSwitch:
					tempString = getSettingString("[General]", "Device Type", "Nortel Ethernet Routing Switch");
					break;
				case Config::BayAccelar:
					tempString = getSettingString("[General]", "Device Type", "Bay Networks Accelar");
					break;
				case Config::CheckPointFirewall:
					tempString = getSettingString("[General]", "Device Type", "Checkpoint Firewall Module");
					break;
				case Config::CheckPointManagement:
					tempString = getSettingString("[General]", "Device Type", "Checkpoint Management Module");
					break;
				case Config::NokiaIP:
					tempString = getSettingString("[General]", "Device Type", "Nokia IP");
					break;
				case Config::SonicWALLSonicOS:
					tempString = getSettingString("[General]", "Device Type", "SonicWall SonicOS Firewall");
					break;
				case Config::HPProCurve:
					tempString = getSettingString("[General]", "Device Type", "HP ProCurve Switch");
					break;
				case Config::ThreeComSuperStackFW:
					tempString = getSettingString("[General]", "Device Type", "3Com SuperStack 3 Firewall");
					break;
				case Config::AutodetectDevice:
					tempString = getSettingString("[General]", "Device Type", "Auto");
					break;
			}
			if (strncasecmp(tempString.c_str(), "Cisco Switch (IOS)", 18) == 0)
				deviceType = Config::CiscoIOSCatalyst;
			else if (strncasecmp(tempString.c_str(), "Cisco Router (IOS)", 18) == 0)
				deviceType = Config::CiscoIOSRouter;
			else if (strncasecmp(tempString.c_str(), "Cisco Catalyst (IOS)", 20) == 0)
				deviceType = Config::CiscoIOSCatalyst;
			else if (strncasecmp(tempString.c_str(), "Cisco Catalyst (NMP)", 20) == 0)
				deviceType = Config::CiscoNMPCatalyst;
			else if (strncasecmp(tempString.c_str(), "Cisco Catalyst (CatOS)", 22) == 0)
				deviceType = Config::CiscoCatOSCatalyst;
			else if (strncasecmp(tempString.c_str(), "Cisco Firewall (PIX)", 20) == 0)
				deviceType = Config::CiscoPIXFirewall;
			else if (strncasecmp(tempString.c_str(), "Cisco Firewall (ASA)", 20) == 0)
				deviceType = Config::CiscoASAFirewall;
			else if (strncasecmp(tempString.c_str(), "Cisco Firewall (FWSM)", 21) == 0)
				deviceType = Config::CiscoFWSMFirewall;
			else if (strncasecmp(tempString.c_str(), "Cisco Content Services Switch (CSS)", 35) == 0)
				deviceType = Config::CiscoCSS;
			else if (strncasecmp(tempString.c_str(), "Juniper ScreenOS Firewall", 25) == 0)
				deviceType = Config::JuniperScreenOS;
			else if (strncasecmp(tempString.c_str(), "Nortel Passport", 15) == 0)
				deviceType = Config::NortelPassport;
			else if (strncasecmp(tempString.c_str(), "Nortel Ethernet Routing Switch", 30) == 0)
				deviceType = Config::NortelRoutingSwitch;
			else if (strncasecmp(tempString.c_str(), "Bay Networks Accelar", 20) == 0)
				deviceType = Config::BayAccelar;
			else if (strncasecmp(tempString.c_str(), "Checkpoint Firewall-1", 21) == 0) // Left in to support legacy configs
				deviceType = Config::CheckPointFirewall;
			else if (strncasecmp(tempString.c_str(), "Checkpoint Firewall Module", 26) == 0)
				deviceType = Config::CheckPointFirewall;
			else if (strncasecmp(tempString.c_str(), "Checkpoint Management Module", 28) == 0)
				deviceType = Config::CheckPointManagement;
			else if (strncasecmp(tempString.c_str(), "Nokia IP", 8) == 0)
				deviceType = Config::NokiaIP;
			else if (strncasecmp(tempString.c_str(), "SonicWall SonicOS Firewall", 26) == 0)
				deviceType = Config::SonicWALLSonicOS;
			else if (strncasecmp(tempString.c_str(), "HP ProCurve", 11) == 0)
				deviceType = Config::HPProCurve;
			else if (strncasecmp(tempString.c_str(), "3Com SuperStack 3 Firewall", 26) == 0)
				deviceType = Config::ThreeComSuperStackFW;
			else
				deviceType = Config::AutodetectDevice;

			// Force device type...
			deviceTypeChecks = getSettingBool("[General]", "Force Type", deviceTypeChecks);

			// Device model...
			if (deviceModel != 0)
				internDeviceModel = getSettingString("[General]", "Model", deviceModel);
			else
				internDeviceModel = getSettingString("[General]", "Model", "");
			if (internDeviceModel.empty())
				deviceModel = 0;
			else
				deviceModel = internDeviceModel.c_str();

			// Device name...
			if (deviceName != 0)
				internDeviceName = getSettingString("[General]", "Name", deviceName);
			else
				internDeviceName = getSettingString("[General]", "Name", "");
			if (internDeviceName.empty())
				deviceName = 0;
			else
				deviceName = internDeviceName.c_str();

			// Device location...
			if (deviceLocation == Config::Internal)
				tempString = getSettingString("[General]", "Location", "Internal");
			else
				tempString = getSettingString("[General]", "Location", "Edge");
			if (strncasecmp(tempString.c_str(), "Edge", 4) == 0)
				deviceLocation = Config::Edge;
			else
				deviceLocation = Config::Internal;

			// SNMP Address...
			if (snmpAddress != 0)
				internSNMPAddress = getSettingString("[SNMP]", "IP Address", snmpAddress);
			else
				internSNMPAddress = getSettingString("[SNMP]", "IP Address", "");
			if (internSNMPAddress.empty())
				snmpAddress = 0;
			else
				snmpAddress = internSNMPAddress.c_str();

			// SNMP Community...
			if (snmpCommunity != 0)
				internSNMPCommunity = getSettingString("[SNMP]", "Community String", snmpCommunity);
			else
				internSNMPCommunity = getSettingString("[SNMP]", "Community String", "");
			if (internSNMPCommunity.empty())
				snmpCommunity = 0;
			else
				snmpCommunity = internSNMPCommunity.c_str();

			// SNMP Community...
			if (snmpCommunity != 0)
				internSNMPCommunity = getSettingString("[SNMP]", "Community String", snmpCommunity);
			else
				internSNMPCommunity = getSettingString("[SNMP]", "Community String", "");
			if (internSNMPCommunity.empty())
				snmpCommunity = 0;
			else
				snmpCommunity = internSNMPCommunity.c_str();

			// Report Format...
			switch (reportFormat)
			{
				case Config::XML:
					tempString = getSettingString("[Report]", "Report Format", "XML");
					break;
				case Config::Latex:
					tempString = getSettingString("[Report]", "Report Format", "Latex");
					break;
				case Config::Text:
					tempString = getSettingString("[Report]", "Report Format", "Text");
					break;
				default:
					tempString = getSettingString("[Report]", "Report Format", "HTML");
					break;
			}
			if (strncasecmp(tempString.c_str(), "XML", 3) == 0)
				reportFormat = Config::XML;
			else if (strncasecmp(tempString.c_str(), "Latex", 5) == 0)
				reportFormat = Config::Latex;
			else if (strncasecmp(tempString.c_str(), "Text", 4) == 0)
				reportFormat = Config::Text;
			else
				reportFormat = Config::HTML;

			// Company Name...
			if (companyName != 0)
				internCompanyName = getSettingString("[Report]", "Company Name", companyName);
			else
				internCompanyName = getSettingString("[Report]", "Company Name", "Nipper");
			companyName = internCompanyName.c_str();

			// Security Issue Ordering...
			if (issueOrdering == byOverallRating)
				tempString = getSettingString("[Report]", "Security Issues Ordering", "Overall Rating");
			else
				tempString = getSettingString("[Report]", "Security Issues Ordering", "Related Configuration");
			if (strncasecmp(tempString.c_str(), "Overall Rating", 14) == 0)
				issueOrdering = byOverallRating;
			else
				issueOrdering = byRelatedConfiguration;

			// HTML Stylesheet...
			if (htmlStylesheet != 0)
				internHTMLStylesheet = getSettingString("[HTML]", "Style Sheet File", htmlStylesheet);
			else
				internHTMLStylesheet = getSettingString("[HTML]", "Style Sheet File", "");
			if (internHTMLStylesheet.empty())
				htmlStylesheet = 0;
			else
				htmlStylesheet = internHTMLStylesheet.c_str();

			// Latex Paper...
			if (latexPaper != 0)
				internLatexPaper = getSettingString("[Latex]", "Paper Size", latexPaper);
			else
				internLatexPaper = getSettingString("[Latex]", "Paper Size", "");
			if (internLatexPaper.empty())
				latexPaper = 0;
			else
				latexPaper = internLatexPaper.c_str();

			// Latex Document Class...
			if (latexDocumentClass != 0)
				internLatexDocumentClass = getSettingString("[Latex]", "Document Class", latexDocumentClass);
			else
				internLatexDocumentClass = getSettingString("[Latex]", "Document Class", "");
			if (internLatexDocumentClass.empty())
				latexDocumentClass = 0;
			else
				latexDocumentClass = internLatexDocumentClass.c_str();

			// Passwords in report...
			includePasswordsInReport = getSettingBool("[Report]", "Show Passwords In Report", includePasswordsInReport);

			// Show filter rule comments in the report output...
			includeFilterRuleComments = getSettingBool("[Report]", "Show Filter Rule Comments", includeFilterRuleComments);

			// Convert names to IP addresses...
			convertNamesToAddresses = getSettingBool("[Report]", "Convert Names To IP Addresses", convertNamesToAddresses);

			// Report sections...
			includeSecurityAudit = getSettingBool("[Report Sections]", "Security Audit", includeSecurityAudit);
			includeConfigurationReport = getSettingBool("[Report Sections]", "Configuration Report", includeConfigurationReport);
			includeComplianceCheck = getSettingBool("[Report Sections]", "Compliance Report", includeComplianceCheck);
			includeAppendixSection = getSettingBool("[Report Sections]", "Appendix", includeAppendixSection);
			includeGlossary = getSettingBool("[Report Sections]", "Glossary", includeGlossary);
			includeNetworkPorts = getSettingBool("[Report Sections]", "Common Ports", includeNetworkPorts);
			includeIPProtocols = getSettingBool("[Report Sections]", "IP Protocols", includeIPProtocols);
			includeICMPTypes = getSettingBool("[Report Sections]", "ICMP Types", includeICMPTypes);
			includeNipperVersion = getSettingBool("[Report Sections]", "Nipper Details", includeNipperVersion);
			includeAuditorInformation = getSettingBool("[Report Sections]", "Auditor Information", includeAuditorInformation);
			includeLoggingLevels = getSettingBool("[Report Sections]", "Logging Levels", includeLoggingLevels);
			includeTimeZones = getSettingBool("[Report Sections]", "Time Zones", includeTimeZones);
			includeAbbreviations = getSettingBool("[Report Sections]", "Abbreviations", includeAbbreviations);

			// Password Policy...
			minimumPasswordLength = getSettingInt("[Audit]", "Minimum Password Length", minimumPasswordLength);
			passwordsMustIncludeUppers = getSettingBool("[Audit]", "Passwords Must Include Uppercase", passwordsMustIncludeUppers);
			passwordsMustIncludeLowers = getSettingBool("[Audit]", "Passwords Must Include Lowercase", passwordsMustIncludeLowers);
			passwordsMustIncludeEitherCase = getSettingBool("[Audit]", "Passwords Must Include Lowercase or Uppercase", passwordsMustIncludeEitherCase);
			passwordsMustIncludeNumbers = getSettingBool("[Audit]", "Passwords Must Include Numbers", passwordsMustIncludeNumbers);
			passwordsMustIncludeSpecials = getSettingBool("[Audit]", "Passwords Must Include Special Characters", passwordsMustIncludeSpecials);
			maximumRepeatedChars = getSettingInt("[Audit]", "Maximum number of repeated characters", maximumRepeatedChars);
			differentFromUsername = getSettingBool("[Audit]", "Passwords should not be username-based", differentFromUsername);
			differentFromHostname = getSettingBool("[Audit]", "Passwords should not be hostname-based", differentFromHostname);
			noDeviceInformationInPasswords = getSettingBool("[Audit]", "Passwords should not be based on device information", noDeviceInformationInPasswords);
			noDictionaryCharacterSubst = getSettingBool("[Audit]", "Passwords should not be dictionary-based with character substitution", noDictionaryCharacterSubst);
			noCharacterSequences = getSettingBool("[Audit]", "Passwords should not contain character sequences", noCharacterSequences);
			noCommonDictionaryAppends = getSettingBool("[Audit]", "Passwords should not be dictionary-based with characters appended", noCommonDictionaryAppends);
			if (passwordDictionary != 0)
				internPasswordDictionary = getSettingString("[Audit]", "Dictionary File", passwordDictionary);
			else
				internPasswordDictionary = getSettingString("[Audit]", "Dictionary File", "");
			if (internPasswordDictionary.empty())
				passwordDictionary = 0;
			else
				passwordDictionary = internPasswordDictionary.c_str();

			// Connection Timeouts...
			connectionTimeouts = getSettingInt("[Audit]", "Minimum Timeout (Seconds)", connectionTimeouts);

			// ACL auditing...
			ignoreNonTCPUDPFilters = getSettingBool("[Audit]", "Ignore Non TCP / UDP filters", ignoreNonTCPUDPFilters);
			checkFilteringIsConfigured = getSettingBool("[Audit]", "Check that network filtering is enabled", checkFilteringIsConfigured);
			checkFilterDefaultAllowAction = getSettingBool("[Audit]", "Check for a default filtering action to allow traffic", checkFilterDefaultAllowAction);
			checkFilterForAnySource = getSettingBool("[Audit]", "Check for allowing rules from any source address", checkFilterForAnySource);
			checkFilterForNetworkSource = getSettingBool("[Audit]", "Check for allowing rules from a source network address", checkFilterForNetworkSource);
			checkFilterForAnySourcePort = getSettingBool("[Audit]", "Check for allowing any source port rules", checkFilterForAnySourcePort);
			checkFilterForRangeSourcePort = getSettingBool("[Audit]", "Check for allowing a range of source ports rules", checkFilterForRangeSourcePort);
			checkFilterForAnyDestination = getSettingBool("[Audit]", "Check for allowing any network destination address rules", checkFilterForAnyDestination);
			checkFilterForNetworkDestination = getSettingBool("[Audit]", "Check for allowing network destination rules", checkFilterForNetworkDestination);
			checkFilterForAnyDestinationPort = getSettingBool("[Audit]", "Check for rules allowing any destination ports", checkFilterForAnyDestinationPort);
			checkFilterForRangeDestinationPort = getSettingBool("[Audit]", "Check for rules allowing a range of destination ports", checkFilterForRangeDestinationPort);
			checkFilterLogsAllowedRules = getSettingBool("[Audit]", "Check that allow rules log", checkFilterLogsAllowedRules);
			checkFilterForLogDeniedRules = getSettingBool("[Audit]", "Check that denied rules log", checkFilterForLogDeniedRules);
			checkFilterEndsWithDenyAllAndLog = getSettingBool("[Audit]", "Check that rule lists end with a deny all and log", checkFilterEndsWithDenyAllAndLog);
			checkFilterForRejectRules = getSettingBool("[Audit]", "Check for rules that reject", checkFilterForRejectRules);
			checkFilterForBypassRules = getSettingBool("[Audit]", "Check for rules that bypass the filtering", checkFilterForBypassRules);
			checkFilterForDefaultRules = getSettingBool("[Audit]", "Check for rules that allow a default action", checkFilterForDefaultRules);
			checkFilterForRulesWithoutComments = getSettingBool("[Audit]", "Check for rules with comments", checkFilterForRulesWithoutComments);
			checkFilterForDisabledRules = getSettingBool("[Audit]", "Check for disabled rules", checkFilterForDisabledRules);
			checkFilterForUnusedRulesAtListEnd = getSettingBool("[Audit]", "Check for unused rules at the end of a rules list", checkFilterForUnusedRulesAtListEnd);
			checkFilterForClearTextRules = getSettingBool("[Audit]", "Check for rules allowing clear text protocol services", checkFilterForClearTextRules);
			checkFilterForDangerousRules = getSettingBool("[Audit]", "Check for rules allowing potentially dangerous services", checkFilterForDangerousRules);
			checkFilterForUnnecessaryRules = getSettingBool("[Audit]", "Check for rules allowing potentially unnecessary services", checkFilterForUnnecessaryRules);
			checkFilterForDuplicateRules = getSettingBool("[Audit]", "Check for rules that duplicate other rules", checkFilterForDuplicateRules);
			checkFilterForContradictRules = getSettingBool("[Audit]", "Check for rules that contradict other rules", checkFilterForContradictRules);
			checkFilterForUnusedRuleLists = getSettingBool("[Audit]", "Check for unused rule lists", checkFilterForUnusedRuleLists);

			// Get the Clear-Text / Dangerous / Unnecessary services
			rewind(configFile);
			do
			{
				memset(line, 0, sizeof(line));
				fgets(line, sizeof(line), configFile);
			}
			while ((feof(configFile) == 0) && (strncasecmp("[Audit]", line, strlen("[Audit]")) != 0));

			// If not found, return the default...
			if (strncasecmp("[Audit]", line, strlen("[Audit]")) == 0)
			{
				memset(line, 0, sizeof(line));
				fgets(line, sizeof(line), configFile);

				// Search for setting...
				while ((feof(configFile) == 0) && (line[0] != '['))
				{

					if (strncasecmp("Unnecessary Service", line, 19) == 0)
					{
						// Clear the end-of-line stuff...
						tempInt = strlen(line) - 1;
						while ((line[tempInt] == '\r') || (line[tempInt] == '\n') || (line[tempInt] == ' '))
						{
							line[tempInt] = 0;
							tempInt--;
						}

						// Search for the =...
						settingPointer = strchr(line, '=');
						if (settingPointer != NULL)
						{
							settingPointer++;
				
							// Search for the first character...
							while ((settingPointer[0] != 0) && (settingPointer[0] == ' '))
								settingPointer++;
				
							// If there is a setting, return it...
							if (settingPointer[0] != 0)
								addUnnecessaryService(settingPointer);
						}
					}

					else if (strncasecmp("Dangerous Service", line, 17) == 0)
					{
						// Clear the end-of-line stuff...
						tempInt = strlen(line) - 1;
						while ((line[tempInt] == '\r') || (line[tempInt] == '\n') || (line[tempInt] == ' '))
						{
							line[tempInt] = 0;
							tempInt--;
						}

						// Search for the =...
						settingPointer = strchr(line, '=');
						if (settingPointer != NULL)
						{
							settingPointer++;
				
							// Search for the first character...
							while ((settingPointer[0] != 0) && (settingPointer[0] == ' '))
								settingPointer++;
				
							// If there is a setting, return it...
							if (settingPointer[0] != 0)
								addDangerousService(settingPointer);
						}
					}

					else if (strncasecmp("Clear Text Service", line, 18) == 0)
					{
						// Clear the end-of-line stuff...
						tempInt = strlen(line) - 1;
						while ((line[tempInt] == '\r') || (line[tempInt] == '\n') || (line[tempInt] == ' '))
						{
							line[tempInt] = 0;
							tempInt--;
						}

						// Search for the =...
						settingPointer = strchr(line, '=');
						if (settingPointer != NULL)
						{
							settingPointer++;
				
							// Search for the first character...
							while ((settingPointer[0] != 0) && (settingPointer[0] == ' '))
								settingPointer++;
				
							// If there is a setting, return it...
							if (settingPointer[0] != 0)
								addClearTextService(settingPointer);
						}
					}

					// Read line
					memset(line, 0, sizeof(line));
					fgets(line, sizeof(line), configFile);
				}
			}

			fclose(configFile);
		}
		else
			internalError = libnipper_error_configfileopen;

	}
	else
		internalError = libnipper_error_fileempty;

	// Free...
	delete fileStats;

	// If clear text services have not been added, add the default ones...
	if (clearTextService == 0)
	{
		addClearTextService("21");
		addClearTextService("23");
		addClearTextService("25");
		addClearTextService("49");
		addClearTextService("69");
		addClearTextService("80");
		addClearTextService("107");
		addClearTextService("109");
		addClearTextService("110");
		addClearTextService("111");
		addClearTextService("119");
		addClearTextService("389");
		addClearTextService("512");
		addClearTextService("513");
		addClearTextService("514");
		addClearTextService("873");
	}

	// If dangerous services have not been added, add the default ones...
	if (dangerousService == 0)
	{
		addDangerousService("137");
		addDangerousService("138");
		addDangerousService("139");
		addDangerousService("161");
		addDangerousService("162");
		addDangerousService("445");
		addDangerousService("1241");
		addDangerousService("1433");
		addDangerousService("1434");
		addDangerousService("1521");
		addDangerousService("1812");
		addDangerousService("3306");
		addDangerousService("3389");
		addDangerousService("6000");
		addDangerousService("6001");
		addDangerousService("6002");
		addDangerousService("6003");
		addDangerousService("8080");
	}

	// If unnecessary services have not been added, add the default ones...
	if (unnecessaryService == 0)
	{
		addUnnecessaryService("7");
		addUnnecessaryService("9");
		addUnnecessaryService("13");
		addUnnecessaryService("17");
		addUnnecessaryService("19");
		addUnnecessaryService("63");
		addUnnecessaryService("70");
		addUnnecessaryService("79");
	}

	return internalError;
}


void Config::addClearTextService(const char *service)
{
	// Variables...
	protocolServiceList *protocolServicePointer = 0;

	// Create...
	if (clearTextService == 0)
	{
		clearTextService = new (protocolServiceList);
		protocolServicePointer = clearTextService;
	}
	else
	{
		protocolServicePointer = clearTextService;
		while (protocolServicePointer->next != 0)
		{
			if (strcasecmp(protocolServicePointer->service, service) == 0)
				return;
			protocolServicePointer = protocolServicePointer->next;
		}
		if (strcasecmp(protocolServicePointer->service, service) == 0)
			return;
		protocolServicePointer->next = new (protocolServiceList);
		protocolServicePointer = protocolServicePointer->next;
	}

	// Init...
	protocolServicePointer->service = new (nothrow) char [strlen(service) + 1];
	strcpy(protocolServicePointer->service, service);
	protocolServicePointer->port = 0;
	protocolServicePointer->next = 0;
}


void Config::addDangerousService(const char *service)
{
	// Variables...
	protocolServiceList *protocolServicePointer = 0;

	// Create...
	if (dangerousService == 0)
	{
		dangerousService = new (protocolServiceList);
		protocolServicePointer = dangerousService;
	}
	else
	{
		protocolServicePointer = dangerousService;
		while (protocolServicePointer->next != 0)
		{
			if (strcasecmp(protocolServicePointer->service, service) == 0)
				return;
			protocolServicePointer = protocolServicePointer->next;
		}
		if (strcasecmp(protocolServicePointer->service, service) == 0)
			return;
		protocolServicePointer->next = new (protocolServiceList);
		protocolServicePointer = protocolServicePointer->next;
	}

	// Init...
	protocolServicePointer->service = new (nothrow) char [strlen(service) + 1];
	strcpy(protocolServicePointer->service, service);
	protocolServicePointer->port = 0;
	protocolServicePointer->next = 0;
}


void Config::addUnnecessaryService(const char *service)
{
	// Variables...
	protocolServiceList *protocolServicePointer = 0;

	// Create...
	if (unnecessaryService == 0)
	{
		unnecessaryService = new (protocolServiceList);
		protocolServicePointer = unnecessaryService;
	}
	else
	{
		protocolServicePointer = unnecessaryService;
		while (protocolServicePointer->next != 0)
		{
			if (strcasecmp(protocolServicePointer->service, service) == 0)
				return;
			protocolServicePointer = protocolServicePointer->next;
		}
		if (strcasecmp(protocolServicePointer->service, service) == 0)
			return;
		protocolServicePointer->next = new (protocolServiceList);
		protocolServicePointer->port = 0;
		protocolServicePointer = protocolServicePointer->next;
	}

	// Init...
	protocolServicePointer->service = new (nothrow) char [strlen(service) + 1];
	strcpy(protocolServicePointer->service, service);
	protocolServicePointer->next = 0;
}

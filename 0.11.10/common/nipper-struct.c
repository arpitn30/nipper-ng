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


struct nipperConfig					// Global Configuration
{
	// Program options...
	int nipperMode;
	int helpMode;					// The help page to show, see codes above
	int force;						// Force configuration type (bypass type checking)
	char companyName[128];			// Company name to output in a report
	struct johnPassword *john;		// The encrypted passwords to crack with john-the-ripper

	int sectionCount;
	int subSectionCount;

	// Latex report output options
	char paperSize[32];
	char documentClass[32];

	// SNMP Options
	char remoteIP[16];				// Retrival of Config remotely - IP
	char localIP[16];				// Retrival of Config remotely - IP (local)
	char remoteTftp[128];			// Retrival of Config remotely - TFTP root
	char remoteSnmp[128];			// Retrival of Config remotely - SNMP community
	int localSave;					// Retrival of Config remotely - Config Save Name
	int oldCisco;					// Retrival of Config remotely - Old or new methods

	// Reporting
	struct reportText *report;		// Reporting config

	// Table Structure Pointers, used for report writing
	const char *tablerow_start;
	const char *tablerow_mid;
	const char *tablerow_end;
	const char *tablerow_itemsep;

	// Report Output Options
	int outputFormat;				// Output file format output_text...
	int abs;						// Abbreviation output
	int loggingLevels;				// Logging Levels output
	int timeZones;					// Time Zone output
	int appendix;					// Appendix output
	int glossary;					// Glossary output
	int commonPorts;				// Common Ports output
	int fullReport;					// Include Security Audit
	int configReport;				// Include configuration report
	int expandACL;					// Expand an ACL's object definitions.
	int names;						// Show hostnames instead of IP addresses (where possible)
	int passwords;					// Output passwords?
	int nipperVersion;				// Output nipper appendix version details

	// Debug Options
	int debugMode;					// Show debug output
	int linesnotprocessed;			// Print the lines that were not processed (true or false)
	int debugAbbrev;				// Output Abbreviations that were not found

	// File Handles / File Names
	char *outputFile;				// Argument that contains output file, if specified.
	char *johnFile;					// John the ripper file name
	FILE *input;					// Input file
	char *inputName;				// Input name from command line
	FILE *reportFile;				// Report file
	char *dictionaryFilename;		// The Dictionary Filename
	char *dictionaryFile;			// Dictionary file
	FILE *dictFile;					// The Dictionary File handle
	char *cssFile;					// HTML CSS file
	char *cssFromConfig;			// CSS filename from config file
	int doCSV;						// Do CSV?
	char *csvFilename;				// ACL output CSV filename
	FILE *csvFile;
	int showACLComments;

	// Default Password Settings
	int passwordLength;
	int passwordUppers;
	int passwordLowers;
	int passwordEither;
	int passwordNumbers;
	int passwordSpecials;

	// Connection settings
	int connectionTimeout;			// The Connection Timeout

	// Issue Counters...
	int aclIssues;
	int denyIssue;
	int rejectIssue;
	int simplePasswords;
	int passwordStrengths;
	int insecureTimeouts;
	int vulnIssues;
	int vulnIssueDos;
	int vulnIssueRemote;
	int ipDirectedIssues;
	int switchportModeIssues;
	int switchportIssues;
	int proxyArpIssues;
	int unreachIssues;
	int maskReplyIssues;
	int loggingIssue;
	int enableIssues;
	int vrrpIssues;
	int ospfAuthMD5;
	int ospfAuthNoneIssues;
	int ospfAuthClearIssues;
	int eigrpIssues;
	int ripIssues;
	int redirectsIssues;
	int uRPFIssues;
	int snmpIssue;
	int sshIssue;
	int sshManIssues;

	// Misc Variables...
	int maxSize;					// Maximum Variable Size
	int tableNum;					// Current Table Number for Report Writing

	// Device Details...
	int deviceType;					// type_screenos...
	char *deviceModel;				// Model series
	char *deviceModelInt;				// * Do not use *
	int deviceUse;					// use_edge, use_internal, use_all (default)
	char hostname[128];
	char domainName[128];
	char friendlyHostname[148];		// Hostname processed for report output
	char version[16];				// Version string
	int versionMajor;
	int versionMinor;
	int versionRevision;
	int versionRevisionMinor;

	// Device Specific Configuration
	struct ciscoIOSConfig *ios;
	struct ciscoPIXConfig *pix;
	struct ciscoNMPConfig *nmp;
	struct ciscoCSSConfig *css;
	struct screenOSConfig *sos;
	struct passportConfig *pas;
	struct firewall1Config *fw1;
	struct sonicosConfig *sonicos;

	// Common Device Specific Configuration
	struct filterListConfig *filterList;
	struct objectListConfig *objectList;

	// Filtering options
	int denyLogIssue;				// Check for deny all and log at the end of filtering rules
	int anySourceIssue;				// Any Source
	int networkSourceIssue;			// Network Source
	int anySourceServiceIssue;		// Any Source Service
	int anyDestinationIssue;		// Any Destination
	int networkDestinationIssue;	// Network Destination
	int anyDestinationServiceIssue;	// Any Destination Service
	int allRulesLogIssue;			// All Rules Log
	int disabledRulesIssue;			// Disabled Rules
	int rejectRulesIssue;			// Reject Rules
	int logDenyRulesIssue;			// Log Deny Rules
	int bypassRulesIssue;			// Bypass Rules
	int defaultRulesIssue;			// Default Rules

	// Filter Issue Counters
	int anySource;
	int networkSource;
	int anySourceService;
	int anyDestination;
	int networkDestination;
	int anyDestinationService;
	int filtersWithNoLogging;
	int denyAllAndLog;
	int disabledRules;
	int rejectRules;
	int logDenyRules;
	int bypassRules;
	int defaultRules;
};


struct host							// Host
{
	char server[32];
	struct host *next;
};


// Used to break each line up
struct ciscoCommand
{
	int parts;
	char part[40][128];
};


// Encrypted passwords for john
struct johnPassword
{
	char username[128];
	char password[128];
	struct johnPassword *next;
};


// Reporting
struct reportText
{
	int section;							// Section
	const char *sectionTitle;				// Section Title
	const char *shortConText;				// Short Conculsions text
	const char *shortRecText;				// Short Recommendations text
											// All scores are between 1 and 10 (0 is off or N/A)
	int scoreOverall;						// Overall Score
	int scoreImpact;						// Impact of issue
	int scoreEase;							// Ease of exploitation
	int scoreRec;							// How easy to fix
	void (*writeSection)(struct nipperConfig *nipper);
	struct reportText *next;
};


// SNMP Traps
struct snmpTrap
{
	char trap[128];
	int enabled;
	struct snmpTrap *next;
};


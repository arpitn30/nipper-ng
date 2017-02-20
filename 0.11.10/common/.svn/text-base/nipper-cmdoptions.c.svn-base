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

// This file contains all the code to get the command-line options...

void getCommandOptions(int argc, char *argv[], struct nipperConfig *nipper)
{
	// Variables...
	int argLoop;

	// Get program parameters
	for (argLoop = 1; argLoop < argc; argLoop++)
	{
		// Output format specified
		if ((strncmp("--output-format=", argv[argLoop], 16) == 0) || (strncmp("--report-format=", argv[argLoop], 16) == 0))
		{
			if (strcmp("text", argv[argLoop]+16) == 0)
				nipper->outputFormat = output_text;
			else if (strcmp("html", argv[argLoop]+16) == 0)
				nipper->outputFormat = output_html;
			else if (strcmp("latex", argv[argLoop]+16) == 0)
				nipper->outputFormat = output_latex;
			else if (strcmp("xml", argv[argLoop]+16) == 0)
				nipper->outputFormat = output_xml;
			else
				nipper->nipperMode = mode_help;
		}
		else if (strncmp("--text", argv[argLoop], 6) == 0)
			nipper->outputFormat = output_text;
		else if (strncmp("--html", argv[argLoop], 6) == 0)
			nipper->outputFormat = output_html;
		else if (strncmp("--latex", argv[argLoop], 7) == 0)
			nipper->outputFormat = output_latex;
		else if (strncmp("--xml", argv[argLoop], 5) == 0)
			nipper->outputFormat = output_xml;

		// Input file (defaults to stdin)
		else if ((strncmp("--input=", argv[argLoop], 8) == 0) && (strlen(argv[argLoop]) > 8))
			nipper->inputName = argv[argLoop] + 8;

		// Output file (defaults to stdout)
		else if (((strncmp("--output=", argv[argLoop], 9) == 0) || (strncmp("--report=", argv[argLoop], 9) == 0)) && (strlen(argv[argLoop]) > 9))
			nipper->outputFile = argv[argLoop] + 9;

		// Configuration File
		else if ((strncmp("--config=", argv[argLoop], 9) == 0) && (strlen(argv[argLoop]) > 9))
			configFilename = argv[argLoop] + 9;

		// CSV File...
		else if ((strncmp("--csv=", argv[argLoop], 6) == 0) && (strlen(argv[argLoop]) > 6))
			nipper->csvFilename = argv[argLoop] + 6;

		// Password output
		else if (strcmp("--no-passwords", argv[argLoop]) == 0)
			nipper->passwords = false;

		// Force
		else if (strcmp("--force", argv[argLoop]) == 0)
			nipper->force = true;

		// Do not perform a security audit
		else if (strcmp("--no-audit", argv[argLoop]) == 0)
			nipper->fullReport = false;

		// Do include a configuration report
		else if (strcmp("--no-config", argv[argLoop]) == 0)
			nipper->configReport = false;

		// Expand ACL object definitions
		else if (strcmp("--expand-acl", argv[argLoop]) == 0)
			nipper->expandACL = true;

		// Rule Comments
		else if (strcmp("--rule-comments", argv[argLoop]) == 0)
			nipper->showACLComments = true;

		// Debug output
		else if (strcmp("--debug", argv[argLoop]) == 0)
			nipper->debugMode = true;
		else if (strcmp("--debug-lnp", argv[argLoop]) == 0)
			nipper->linesnotprocessed = true;

		// Router
		else if ((strcmp("--ios-router", argv[argLoop]) == 0) || (strcmp("--ios", argv[argLoop]) == 0))
			nipper->deviceType = type_ios_router;

		// Cisco Router
		else if (strcmp("--ios-switch", argv[argLoop]) == 0)
			nipper->deviceType = type_ios_switch;

		// Cisco Catalyst
		else if (strcmp("--ios-catalyst", argv[argLoop]) == 0)
			nipper->deviceType = type_ios_catalyst;
		else if (strcmp("--catos", argv[argLoop]) == 0)
			nipper->deviceType = type_cos_catalyst;
		else if (strcmp("--nmp", argv[argLoop]) == 0)
			nipper->deviceType = type_nmp_catalyst;

		// Cisco Firewall
		else if (strcmp("--pix", argv[argLoop]) == 0)
			nipper->deviceType = type_pix_firewall;
		else if (strcmp("--asa", argv[argLoop]) == 0)
			nipper->deviceType = type_asa_firewall;
		else if (strcmp("--fwsm", argv[argLoop]) == 0)
			nipper->deviceType = type_fwsm_firewall;

		// Cisco CSS
		else if (strcmp("--css", argv[argLoop]) == 0)
			nipper->deviceType = type_css_filter;

		// CheckPoint Firewall-1
		else if ((strcmp("--fw1", argv[argLoop]) == 0) || (strcmp("--firewall1", argv[argLoop]) == 0))
			nipper->deviceType = type_fw1_firewall;

		// Nokia IP
		else if ((strcmp("--nokia", argv[argLoop]) == 0) || (strcmp("--nokiaip", argv[argLoop]) == 0))
			nipper->deviceType = type_nokiaip;

		// SonicWall Firewall
		else if ((strcmp("--sonicwall", argv[argLoop]) == 0) || (strcmp("--sonicos", argv[argLoop]) == 0))
			nipper->deviceType = type_sonicwall;

		// Nortel Passport
		else if (strcmp("--passport", argv[argLoop]) == 0)
			nipper->deviceType = type_passport;

		// Bay Networks Accelar
		else if (strcmp("--accelar", argv[argLoop]) == 0)
			nipper->deviceType = type_bayaccelar;

		// Juniper ScreenOS
		else if ((strcmp("--netscreen", argv[argLoop]) == 0) || (strcmp("--screenos", argv[argLoop]) == 0))
			nipper->deviceType = type_sos_firewall;

		// Device Model...
		else if (strncmp("--model=", argv[argLoop], 8) == 0)
			nipper->deviceModel = argv[argLoop] + 8;

		// Set Timeout
		else if (strncmp("--timeout=", argv[argLoop], 10) == 0)
		{
			if (atoi(argv[argLoop] + 10) != 0)
				nipper->connectionTimeout = atoi(argv[argLoop] + 10);
		}

		// Dictionary supplied
		else if (strncmp("--stylesheet=", argv[argLoop], 13) == 0)
			nipper->cssFile = argv[argLoop] + 13;

		// Company name specified
		else if (strncmp("--company-name=", argv[argLoop], 15) == 0)
			strncpy(nipper->companyName, argv[argLoop] + 15, sizeof(nipper->companyName) - 1);

		// Company name specified
		else if (strncmp("--device-name=", argv[argLoop], 14) == 0)
			strncpy(nipper->hostname, argv[argLoop] + 14, sizeof(nipper->hostname) - 1);

		// Password Length
		else if (strncmp("--pass-length=", argv[argLoop], 14) == 0)
			nipper->passwordLength = atoi(argv[argLoop] + 14);

		// Password Uppers
		else if (strcmp("--pass-uppers=yes", argv[argLoop]) == 0)
			nipper->passwordUppers = true;
		else if (strcmp("--pass-uppers=no", argv[argLoop]) == 0)
			nipper->passwordUppers = false;

		// Password Lowers
		else if (strcmp("--pass-lowers=yes", argv[argLoop]) == 0)
			nipper->passwordLowers = true;
		else if (strcmp("--pass-lowers=no", argv[argLoop]) == 0)
			nipper->passwordLowers = false;

		// Password Either
		else if (strcmp("--pass-either=yes", argv[argLoop]) == 0)
			nipper->passwordEither = true;
		else if (strcmp("--pass-either=no", argv[argLoop]) == 0)
			nipper->passwordEither = false;

		// Password Numbers
		else if (strcmp("--pass-numbers=yes", argv[argLoop]) == 0)
			nipper->passwordNumbers = true;
		else if (strcmp("--pass-numbers=no", argv[argLoop]) == 0)
			nipper->passwordNumbers = false;

		// Password Specials
		else if (strcmp("--pass-specials=yes", argv[argLoop]) == 0)
			nipper->passwordSpecials = true;
		else if (strcmp("--pass-specials=no", argv[argLoop]) == 0)
			nipper->passwordSpecials = false;

		// Deny all and log filtering
		else if (strcmp("--deny-log", argv[argLoop]) == 0)
			nipper->denyLogIssue = true;
		else if (strcmp("--no-deny-log", argv[argLoop]) == 0)
			nipper->denyLogIssue = false;

		// Any Source
		else if (strcmp("--no-any-source", argv[argLoop]) == 0)
			nipper->anySourceIssue = false;
		else if (strcmp("--any-source", argv[argLoop]) == 0)
			nipper->anySourceIssue = true;

		// Network Source
		else if (strcmp("--no-network-source", argv[argLoop]) == 0)
			nipper->networkSourceIssue = false;
		else if (strcmp("--network-source", argv[argLoop]) == 0)
			nipper->networkSourceIssue = true;

		// Source Service
		else if (strcmp("--no-source-service", argv[argLoop]) == 0)
			nipper->anySourceServiceIssue = false;
		else if (strcmp("--source-service", argv[argLoop]) == 0)
			nipper->anySourceServiceIssue = true;

		// Any Destination
		else if (strcmp("--no-any-destination", argv[argLoop]) == 0)
			nipper->anyDestinationIssue = false;
		else if (strcmp("--any-destination", argv[argLoop]) == 0)
			nipper->anyDestinationIssue = true;

		// Network Destination
		else if (strcmp("--no-network-destination", argv[argLoop]) == 0)
			nipper->networkDestinationIssue = false;
		else if (strcmp("--network-destination", argv[argLoop]) == 0)
			nipper->networkDestinationIssue = true;

		// Destination Service
		else if (strcmp("--no-destination-service", argv[argLoop]) == 0)
			nipper->anyDestinationServiceIssue = false;
		else if (strcmp("--destination-service", argv[argLoop]) == 0)
			nipper->anyDestinationServiceIssue = true;

		// Log Rules
		else if (strcmp("--no-log-rules", argv[argLoop]) == 0)
			nipper->allRulesLogIssue = false;
		else if (strcmp("--log-rules", argv[argLoop]) == 0)
			nipper->allRulesLogIssue = true;

		// Disabled Rules
		else if (strcmp("--no-disabled-rules", argv[argLoop]) == 0)
			nipper->disabledRulesIssue = false;
		else if (strcmp("--disabled-rules", argv[argLoop]) == 0)
			nipper->disabledRulesIssue = true;

		// Reject Rules
		else if (strcmp("--no-reject-rules", argv[argLoop]) == 0)
			nipper->rejectRulesIssue = false;
		else if (strcmp("--reject-rules", argv[argLoop]) == 0)
			nipper->rejectRulesIssue = true;

		// Bypass Rules
		else if (strcmp("--no-bypass-rules", argv[argLoop]) == 0)
			nipper->bypassRulesIssue = false;
		else if (strcmp("--bypass-rules", argv[argLoop]) == 0)
			nipper->bypassRulesIssue = true;

		// Default Rules
		else if (strcmp("--no-default-rules", argv[argLoop]) == 0)
			nipper->defaultRulesIssue = false;
		else if (strcmp("--default-rules", argv[argLoop]) == 0)
			nipper->defaultRulesIssue = true;

		// Log Deny Rules
		else if (strcmp("--no-log-deny-rules", argv[argLoop]) == 0)
			nipper->logDenyRulesIssue = false;
		else if (strcmp("--log-deny-rules", argv[argLoop]) == 0)
			nipper->logDenyRulesIssue = true;

		// Latex paper size
		else if (strncmp("--paper=", argv[argLoop], 8) == 0)
			strncpy(nipper->paperSize, argv[argLoop]+8, sizeof(nipper->paperSize) - 1);

		// Latex document class
		else if (strncmp("--documentclass=", argv[argLoop], 16) == 0)
			strncpy(nipper->documentClass, argv[argLoop]+16, sizeof(nipper->documentClass) - 1);

		// Appendix
		else if (strcmp("--no-appendix", argv[argLoop]) == 0)
			nipper->appendix = false;

		// Glossary
		else if (strcmp("--no-glossary", argv[argLoop]) == 0)
			nipper->glossary = false;

		// Common Ports
		else if (strcmp("--no-ports", argv[argLoop]) == 0)
			nipper->commonPorts = false;

		// Nipper Version Appendix
		else if (strcmp("--no-version", argv[argLoop]) == 0)
			nipper->nipperVersion = false;

		// Edge device
		else if (strcmp("--location=edge", argv[argLoop]) == 0)
			nipper->deviceUse = use_edge;

		// Internal device
		else if (strcmp("--location=internal", argv[argLoop]) == 0)
			nipper->deviceUse = use_internal;

		// Logging Levels Appendix
		else if (strcmp("--no-logging", argv[argLoop]) == 0)
			nipper->loggingLevels = false;

		// Time Zone Appendix
		else if (strcmp("--no-timezones", argv[argLoop]) == 0)
			nipper->timeZones = false;

		// Abbreviations
		else if (strcmp("--no-abbreviations", argv[argLoop]) == 0)
			nipper->abs = false;

		// Show host / network names instead of IP addresses (where possible)
		else if (strcmp("--no-names", argv[argLoop]) == 0)
			nipper->names = true;

		// Show host / network names instead of IP addresses (where possible)
		else if (strcmp("--debug-abbreviations", argv[argLoop]) == 0)
			nipper->debugAbbrev = true;

		// John the ripper output
		else if ((strncmp("--john=", argv[argLoop], 7) == 0) && (strlen(argv[argLoop]) > 7))
			nipper->johnFile = argv[argLoop] + 7;

		// Dictionary supplied
		else if (strncmp("--dictionary=", argv[argLoop], 13) == 0)
			nipper->dictionaryFile = argv[argLoop] + 13;

#if !defined(__WIN32__)
		// Remote Cisco Device IP
		else if (strncmp("--cisco-ip=", argv[argLoop], 11) == 0)
			strncpy(nipper->remoteIP, argv[argLoop] + 11, sizeof(nipper->remoteIP) - 1);

		// Remote Cisco Device IP (Local)
		else if (strncmp("--local-ip=", argv[argLoop], 11) == 0)
			strncpy(nipper->localIP, argv[argLoop] + 11, sizeof(nipper->localIP) - 1);

		// Remote Cisco Device SNMP read/write community
		else if (strncmp("--snmp=", argv[argLoop], 7) == 0)
			strncpy(nipper->remoteSnmp, argv[argLoop] + 7, sizeof(nipper->remoteSnmp) - 1);

		// Local TFTP server to use
		else if (strncmp("--tftproot=", argv[argLoop], 11) == 0)
			strncpy(nipper->remoteTftp, argv[argLoop] + 11, sizeof(nipper->remoteTftp) - 1);

		// Local Cisco Config file to save to
		else if (strncmp("--cisco-file=", argv[argLoop], 13) == 0)
			nipper->localSave = argLoop;

		// Cisco retrival method (old or new)
		else if (strcmp("--cisco=old", argv[argLoop]) == 0)
			nipper->oldCisco = true;
		else if (strcmp("--cisco=new", argv[argLoop]) == 0)
			nipper->oldCisco = false;
#endif

		// Version
		else if (strcmp("--version", argv[argLoop]) == 0)
			nipper->nipperMode = mode_version;

		// Help
		else if ((strcasecmp("--help", argv[argLoop]) == 0) || (strcasecmp("/?", argv[argLoop]) == 0) || (strcasecmp("--help=general", argv[argLoop]) == 0))
		{
			nipper->nipperMode = mode_help;
			nipper->helpMode = help_general;
		}
		else if (strcasecmp("--help=devices", argv[argLoop]) == 0)
		{
			nipper->nipperMode = mode_help;
			nipper->helpMode = help_device_types;
		}
		else if (strcasecmp("--help=SNMP", argv[argLoop]) == 0)
		{
			nipper->nipperMode = mode_help;
			nipper->helpMode = help_snmp;
		}
		else if (strcasecmp("--help=devices-adv", argv[argLoop]) == 0)
		{
			nipper->nipperMode = mode_help;
			nipper->helpMode = help_device_usage;
		}
		else if (strcasecmp("--help=REPORT", argv[argLoop]) == 0)
		{
			nipper->nipperMode = mode_help;
			nipper->helpMode = help_report_formats;
		}
		else if (strcasecmp("--help=REPORT-ADV", argv[argLoop]) == 0)
		{
			nipper->nipperMode = mode_help;
			nipper->helpMode = help_report_options;
		}
		else if (strcasecmp("--help=REPORT-SECT", argv[argLoop]) == 0)
		{
			nipper->nipperMode = mode_help;
			nipper->helpMode = help_report_appendix;
		}
		else if (strcasecmp("--help=REPORT-HTML", argv[argLoop]) == 0)
		{
			nipper->nipperMode = mode_help;
			nipper->helpMode = help_report_html;
		}
		else if (strcasecmp("--help=REPORT-LATEX", argv[argLoop]) == 0)
		{
			nipper->nipperMode = mode_help;
			nipper->helpMode = help_report_latex;
		}
		else if (strcasecmp("--help=AUDIT-ACL", argv[argLoop]) == 0)
		{
			nipper->nipperMode = mode_help;
			nipper->helpMode = help_audit_acl;
		}
		else if (strcasecmp("--help=AUDIT-PASS", argv[argLoop]) == 0)
		{
			nipper->nipperMode = mode_help;
			nipper->helpMode = help_audit_password;
		}
		else if (strcasecmp("--help=AUDIT-ADV", argv[argLoop]) == 0)
		{
			nipper->nipperMode = mode_help;
			nipper->helpMode = help_audit_misc;
		}
		else if (strcasecmp("--help=DEBUG", argv[argLoop]) == 0)
		{
			nipper->nipperMode = mode_help;
			nipper->helpMode = help_debug;
		}
		else if (strcasecmp("--help=CONFIG-FILE", argv[argLoop]) == 0)
		{
			nipper->nipperMode = mode_help;
			nipper->helpMode = help_config_file;
		}

		// If all else fails, display the help
		else
		{
			nipper->nipperMode = mode_help;
			nipper->helpMode = help_error_params;
		}
	}
}

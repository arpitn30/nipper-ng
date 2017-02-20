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

#ifndef libnipper_config_H
#define libnipper_config_H


extern "C"
{

/**
 * @short The class that configures Nipper.
 *
 * This class is used to configure Nipper. It is worth noting that not all of these settings
 * will apply to all devices, they will only apply if the device being processed supports them.
 */
class Config
{
	public:

	/**
	 * This method makes nipper load a Nipper configuration file. Nipper configuration
	 * is performed in the following order, with each overwriting the previous settings:
	 *
	 *   @li Nipper built-in defaults
	 *   @li The default Nipper configuration file
	 *   @li The configuration file supplied using the setConfigFile method
	 *   @li The configuration settings set using the various set methods
	 *
	 * This should mean, depending on the client implementation, commandline
	 * arguements will take precedence over a configuration file, which will take
	 * precedence over the built-in defaults.
	 *
	 * \param config   The name of an external configuration file to use. The
	 *                 format of the file should match that as defined elsewhere. 
	 * \return         Returns 0 on success, otherwise an error code is returned.
	 */
	int setConfigFile(const char *config);


	// The following properties are post device configuration processing settings...

	enum DeviceTypes
	{
		CiscoIOSRouter = 0,			/*!<  Cisco IOS-based Router  */
		CiscoIOSCatalyst = 1,		/*!<  Cisco IOS-based Catalyst/Switch  */
		CiscoPIXFirewall = 2,		/*!<  Cisco PIX Firewall  */
		CiscoASAFirewall = 3,		/*!<  Cisco ASA Firewall  */
		CiscoFWSMFirewall = 4,		/*!<  Cisco FWSM Firewall  */
		CiscoCatOSCatalyst = 5,		/*!<  Cisco CatOS-based Catalyst  */
		CiscoNMPCatalyst = 6,		/*!<  Cisco NMP-based Catalyst  */
		CiscoCSS = 7,				/*!<  Cisco Content Services Switch  */
		CheckPointFirewall = 8,		/*!<  CheckPoint Firewall Module  */
		CheckPointManagement = 9,	/*!<  CheckPoint Management Module  */
		NokiaIP = 10, 				/*!<  Nokia IP Firewall  */
		SonicWALLSonicOS = 11,		/*!<  SonicWALL SonicOS-based Firewall  */
		NortelPassport = 12,		/*!<  Nortel Passport  */
		NortelRoutingSwitch = 13, 	/*!<  Nortel Ethernet Routing Switch (8300)  */
		//NortelAlteon = 14,		/*!<  Nortel Alteon  */
		BayAccelar = 15,			/*!<  Bay Networks Accelar  */
		//BayStack = 16,*/			/*!<  Bay Networks BayStack  */
		JuniperScreenOS = 17,		/*!<  Juniper ScreenOS-based NetScreen Firewall  */
		//HPAdvacedStack = 18,		/*!<  HP Advanced Stack Switch  */
		HPProCurve = 19,			/*!<  HP ProCurve Switch  */
		//ThreeComRAS = 20,			/*!<  3Com Remote Access System  */
		//ThreeComSuperStack = 21,	/*!<  3Com SuperStack 3 Switch  */
		ThreeComSuperStackFW = 22,	/*!<  3Com SuperStack 3 Firewall  */
		//FortinetFortigate = 23,	/*!<  Fortinet FortiGate Firewall  */
		//Watchguard = 24,			/*!<  WatchGuard Firewall  */
		//NortelContivity = 25		/*!<  Nortel Contivity  */
		AutodetectDevice = 1000		/*!<  Automatically detect the device type (I would recommend that it is specified rather than using this option)  */
	};

	/**
	 * This property identifies the type of device that Nipper will attempt to process.
	 */
	DeviceTypes deviceType;

	/**
	 * This property determines whether Nipper will confirm that the right
	 * device type is being processed. If the device type checks fail
	 * Nipper will stop the processing and return an error code.
	 */
	bool deviceTypeChecks;

	/**
	 * This property holds the device configuration input source for Nipper, this
	 * could be a file (such as a Cisco PIX config) or a directory (such as
	 * a CheckPoint Firewall-1 conf directory).
	 *
	 * Input is processed in a particular order of preference:
	 *   @li Input from file/directory (if inputSource is set)
	 *   @li Input using SNMP (if snmpAddress and snmpCommunity are both set)
	 *   @li Input from stdin
	 */
	const char *inputSource;

	/**
	 * DO NOT USE!
	 * 
	 * This property holds the remote device IP address to be used as part of a
	 * remote grab of the device configuration. This will only work for those
	 * devices for which this is possible.
	 *
	 * Input is processed in a particular order of preference:
	 *   @li Input from file/directory (if inputSource is set)
	 *   @li Input using SNMP (if snmpAddress is set)
	 *   @li Input from stdin
	 */
	const char *snmpAddress;

	/**
	 * DO NOT USE!
	 * 
	 * This property holds the SNMP community to be used as part of a remote
	 * grab of a device configuration. If not set, this is assumed to be
	 * private.
	 *
	 * Input is processed in a particular order of preference:
	 *   @li Input from file/directory (if inputSource is set)
	 *   @li Input using SNMP (if snmpAddress is set)
	 *   @li Input from stdin
	 */
	const char *snmpCommunity;


	// The following are post report generation settings...

	/**
	 * This property holds the device model, as the processing could change
	 * depending on the device model.
	 */
	const char *deviceModel;

	/**
	 * This property holds the device os version, the version identified within the
	 * configuration is not always acurate enough.
	 */
	const char *osVersion;

	/**
	 * This property holds the device name, not all device configuration files include
	 * a name for the device. Sometimes Nipper has to try to guess a device name
	 * based on the configuration file. Specifying a name means that Nipper does
	 * not have to guess. This will override any device name identified in the configuration.
	 */
	const char *deviceName;

	enum DeviceLocation
	{
		Internal = 0,			/*!<  An internal network device, such as a router/firewall between internal networks  */
		Edge = 1				/*!<  An edge device, such as an Internet facing router/firewall  */
	};

	/**
	 * This property specifies the devices location, as the security audit checks could
	 * depend on where the device is used. I.e. an Internal firewall/router or one
	 * that is located on the networks edge (such as Internet facing devices).
	 */
	DeviceLocation deviceLocation;

	/**
	 * This property holds the report output destination. If not set, output is
	 * assumed to be stdout.
	 */
	const char *outputDestination;

	/**
	 * Order the identified security issues another way. These are the sorting options.
	 */
	enum securityIssueOrdering
	{
		byOverallRating = 0,			/*!<  Sort using the overall rating (high to low)  */
		byRelatedConfiguration = 1		/*!<  Sort by related configuration settings (e.g. group all SNMP issues together)  */
	};

	/**
	 * Set the security issue ordering.
	 */
	securityIssueOrdering issueOrdering;

	/**
	 * Show filter rule comments if they exist. This also enables other extra descriptions/comments throughout the report.
	 */
	bool includeFilterRuleComments;

	/**
	 * This property determines whether names should be converted to IP addresses (where possible)
	 * in the report output. Only the device configuration is used to convert these names,
	 * no name lookups are performed.
	 */
	bool convertNamesToAddresses;

	/**
	 * This method sets whether a security audit will be performed of the
	 * device configuration.
	 */
	bool includeSecurityAudit;

	/**
	 * This property determines whether a device configuration report will be included in
	 * the report output.
	 */
	bool includeConfigurationReport;

	/**
	 * This property determines whether a compliance check will be performed on the device
	 * configuration.
	 */
	bool includeComplianceCheck;

	/**
	 * This property determines whether an appendix section will be included in the report
	 * output. Specific parts of the appendix can be individually switched on or off. However,
	 * if there are no appendix sections to include, this will have no effect regardless of
	 * this setting.
	 */
	bool includeAppendixSection;

	/**
	 * This property determines whether a glossary appendix section will be included in the
	 * report output.
	 */
	bool includeGlossary;

	/**
	 * This property determines whether an appendix network ports section will be included in the
	 * report output. However, network services also have to be identified in the report output
	 * otherwise the section will not be included regardless of this setting.
	 */
	bool includeNetworkPorts;

	/**
	 * This property determines whether an appendix IP Protocols section will be included in the
	 * report output. However, IP Protocols also have to be identified in the report output
	 * otherwise the section will not be included regardless of this setting.
	 */
	bool includeIPProtocols;

	/**
	 * This property determines whether an appendix ICMP Types section will be included in the
	 * report output. However, ICMP Types also have to be identified in the report output
	 * otherwise the section will not be included regardless of this setting.
	 */
	bool includeICMPTypes;

	/**
	 * This property determines whether an appendix Nipper program version section will be included in the
	 * report output.
	 */
	bool includeNipperVersion;

	/**
	 * This property determines whether a logging levels appendix section will be included in the
	 * report output. However, if the device configuration is not configured with logging
	 * levels then this section will not appear, regardless of this setting.
	 */
	bool includeLoggingLevels;

	/**
	 * This property determines whether a common time zones appendix section will be included in the
	 * report output. However, if the device does not make use of timezones then this section will
	 * not appear, regardless of this setting.
	 */
	bool includeTimeZones;

	/**
	 * This property determines whether an abbreviations section will be included in the
	 * report output. However, if no abbreviations are identified with the device then this section
	 * will not appear regardless of this setting.
	 */
	bool includeAbbreviations;

	/**
	 * This property determines whether an auditors section will be included in the report
	 * output.
	 */
	bool includeAuditorInformation;

	/**
	 * These properties configure the password and authentication key strength auditing checks.
	 * It is worth noting that only those passwords/keys that can be determined are checked,
	 * all encrypted strings that cannot be determined are not processed.
	 *
	 *   @li minimumPasswordLength - Minimum password length (0 = off)
	 *   @li maximumRepeatedChars - Maximum number of repeated characters (0 = off)
	 *   @li passwordsMustIncludeUppers - Passwords must include uppercase (A-Z)
	 *   @li passwordsMustIncludeLowers - Passwords must include lowercase (a-z)
	 *   @li passwordsMustIncludeEitherCase - Passwords must include alphabetical (a-zA-Z)
	 *   @li passwordsMustIncludeNumbers - Passwords must include numbers
	 *   @li passwordsMustIncludeSpecials - Passwords must include non alphanumeric characters
	 *   @li differentFromUsername - Passwords should not be username-based
	 *   @li differentFromHostname - Passwords should not be hostname-based
	 *   @li noDeviceInformationInPasswords - Passwords should not be based on any device information (such as model, make...)
	 *   @li noDictionaryCharacterSubst - Passwords should not be dictionary-based with character substitution
	 *   @li noCharacterSequences - Passwords should not contain character sequences (e.g. qwerty or 1234)
	 *   @li noCommonDictionaryAppends - Passwords should not be dictionary-based with common appends (e.g. !, 123 and so on)
	 *
	 * A password dictionary can be specified, but a small internal dictionary will be used if
	 * this is not specified.
	 *
	 *   @li passwordDictionary - A dictionary file to test the passwords against
	 */
	unsigned int minimumPasswordLength;			// Minimum password length
	unsigned int maximumRepeatedChars;			// Maximum number of repeated characters
	bool passwordsMustIncludeUppers;			// Passwords must include uppercase (A-Z)
	bool passwordsMustIncludeLowers;			// Passwords must include lowercase (a-z)
	bool passwordsMustIncludeEitherCase;		// Passwords must include alphabetical (a-zA-Z)
	bool passwordsMustIncludeNumbers;			// Passwords must include numbers
	bool passwordsMustIncludeSpecials;			// Passwords must include non alphanumeric characters
	bool differentFromUsername;					// Passwords should not be username-based
	bool differentFromHostname;					// Passwords should not be hostname-based
	bool noDeviceInformationInPasswords;		// Passwords should not be based on any device information (such as model, make...)
	bool noDictionaryCharacterSubst;			// Passwords should not be dictionary-based with character substitution
	bool noCharacterSequences;					// Passwords should not contain character sequences (e.g. qwerty or 1234)
	bool noCommonDictionaryAppends;				// Passwords should not be dictionary-based with common appends (e.g. !, 123 and so on)
	const char *passwordDictionary;				// A dictionary file to test the passwords against

	/**
	 * This property contains the connection timeout limit used as part of the security audit checks. The
	 * value is specified in seconds and applies to all timeouts.
	 */
	int connectionTimeouts;

	/**
	 * The following properties are used to check the network filtering capabilities of a
	 * device. Not all these settings are used for all devices, so they will only apply where
	 * it is applicable. If set to TRUE, the checks WILL be performed.
	 *
	 * The following are not issues with the rule list content, but with the filtering
	 * setup:
	 *
	 *   @li checkFilteringIsConfigured - Checks that filtering is configured
	 *   @li checkFilterDefaultAllowAction - Checks for default allow filtering configuration
	 *
	 * The following change how the checks are performed:
	 *
	 *   @li ignoreNonTCPUDPFilters - Ignores filters that do not use TCP or UDP
	 *
	 * The following are non-analytical checks with the rule list content:
	 *
	 *   @li checkFilterForAnySource - Checks for Any Source rules
	 *   @li checkFilterForNetworkSource - Checks for Network Source rules
	 *   @li checkFilterForAnySourcePort - Checks for Any Source port rules
	 *   @li checkFilterForRangeSourcePort - Checks for Range Source port rules
	 *   @li checkFilterForAnyDestination - Checks for any desintation rules
	 *   @li checkFilterForNetworkDestination - Checks for network destination rules
	 *   @li checkFilterForAnyDestinationPort - Checks for any destination port rules
	 *   @li checkFilterForRangeDestinationPort - Checks for range destination port rules
	 *   @li checkFilterLogsAllowedRules - Checks that allowed rules log
	 *   @li checkFilterForLogDeniedRules - Checks that denied rules log
	 *   @li checkFilterEndsWithDenyAllAndLog - Checks that a rules list ends with a deny all and log
	 *   @li checkFilterForRejectRules - Checks for reject rules
	 *   @li checkFilterForBypassRules - Checks for bypass rules
	 *   @li checkFilterForDefaultRules - Checks for rules that allow a default action (i.e. passport ports)
	 *   @li checkFilterForRulesWithoutComments - Checks for rules with no comments
	 *   @li checkFilterForDisabledRules - Checks for disabled rules
	 *
	 * The following are analytical checks with the rule list content and the lists themselves:
	 *
	 *   @li checkFilterForUnusedRulesAtListEnd - Checks for unused rules at the end of a list (i.e. after a deny all)
	 *   @li checkFilterForClearTextRules - Checks for rules that allow clear-text services through
	 *   @li checkFilterForDangerousRules - Checks for rules that allow dangerous services through
	 *   @li checkFilterForUnnecessaryRules - Checks for rules that allow unnecessary services through
	 *   @li checkFilterForDuplicateRules - Checks for rules that overlap or are duplicates
	 *   @li checkFilterForContradictRules - Checks for rules that contradict other rules
	 *   @li checkFilterForUnusedRuleLists - Checks for rule lists that are not used (or assigned to anything)
	 */
	bool ignoreNonTCPUDPFilters;				// Ignores filters that do not use TCP or UDP
	bool checkFilteringIsConfigured;			// Checks that filtering is configured
	bool checkFilterDefaultAllowAction;			// Checks for default allow filtering configuration
	bool checkFilterForAnySource;				// Checks for Any Source rules
	bool checkFilterForNetworkSource;			// Checks for Network Source rules
	bool checkFilterForAnySourcePort;			// Checks for Any Source port rules
	bool checkFilterForRangeSourcePort;			// Checks for Range Source port rules
	bool checkFilterForAnyDestination;			// Checks for any desintation rules
	bool checkFilterForNetworkDestination;		// Checks for network destination rules
	bool checkFilterForAnyDestinationPort;		// Checks for any destination port rules
	bool checkFilterForRangeDestinationPort;	// Checks for range destination port rules
	bool checkFilterLogsAllowedRules;			// Checks that allowed rules log
	bool checkFilterForLogDeniedRules;			// Checks that denied rules log
	bool checkFilterEndsWithDenyAllAndLog;		// Checks that a rules list ends with a deny all and log
	bool checkFilterForRejectRules;				// Checks for reject rules
	bool checkFilterForBypassRules;				// Checks for bypass rules
	bool checkFilterForDefaultRules;			// Checks for rules that allow a default action (i.e. passport ports)
	bool checkFilterForRulesWithoutComments;	// Checks for rules with no comments
	bool checkFilterForDisabledRules;			// Checks for disabled rules
	bool checkFilterForUnusedRulesAtListEnd;	// Checks for unused rules at the end of a list (i.e. after a deny all)
	bool checkFilterForClearTextRules;			// Checks for rules that allow clear-text Services through
	bool checkFilterForDangerousRules;			// Checks for rules that allow dangerous services through
	bool checkFilterForUnnecessaryRules;		// Checks for rules that allow unnecessary services through
	bool checkFilterForDuplicateRules;			// Checks for rules that overlap/duplicates
	bool checkFilterForContradictRules;			// Checks for rules that contradict other rules
	bool checkFilterForUnusedRuleLists;			// Checks for rule lists that are not used (or assigned to anything)

	/**
	 * The following methods add to the list of protocol services to
	 * check for. Add service port numbers and service names here, for
	 * example "http" and "80".
	 * If not specified Nipper will include a default list of clear text
	 * protocol services.
	 *
	 * \param service       The service to add (e.g. "telnet")
	 */
	void addClearTextService(const char *service);
	void addDangerousService(const char *service);
	void addUnnecessaryService(const char *service);

	struct protocolServiceList
	{
		char *service;
		int port;
		struct protocolServiceList *next;
	};
	protocolServiceList *clearTextService;
	protocolServiceList *dangerousService;
	protocolServiceList *unnecessaryService;

	/**
	 * The XML compliance check list for the device. Do not use.
	 */
	const char *complianceCheckList;

	// The following are report writing settings...

	enum ReportFormat
	{
		HTML = 0,				/*!<  HTML report  */
		XML = 1,				/*!<  XML report  */
		Latex = 2,				/*!<  Latex report  */
		Text = 3,				/*!<  Text report  */
		Debug = 100				/*!<  DO NOT USE  */
	};
	/**
	 * This property contains the report format to be used by Nipper when
	 * generating the report output.
	 */
	ReportFormat reportFormat;

	/**
	 * This property contains the company name to be used within the report output, the default is
	 * to use Nipper.
	 */
	const char *companyName;

	/**
	 * This property contains the name of a file to include as a HTML stylesheet in a the report output.
	 */
	const char *htmlStylesheet;

	/**
	 * This property contains the Latex paper type to be used in the Latex report output. The
	 * default paper type is "a4paper".
	 */
	const char *latexPaper;

	/**
	 * This property contains the Latex document class to be used in the Latex report output.
	 * The default document class is "article".
	 */
	const char *latexDocumentClass;

	/**
	 * This property holds the name of a john-the-ripper style file to output encypted passwords
	 * to.
	 */
	const char *johnFile;

	/**
	 * This property is used to determine whether passwords will be included in the
	 * report output.
	 */
	bool includePasswordsInReport;

	/**
	 * This property contains the text that will be used to populate any empty table cells. (default is -)
	 */
	const char *emptyTableCell;

	/**
	 * Debugging use, do not use.
	 */
	bool debugLinesNotProcessed;

	/**
	 * Debugging use, do not use.
	 */
	bool debugAbbreviations;

	/**
	 * The following are console colour output properties.
	 */
	const char *COL_RESET;
	const char *COL_RED;
	const char *COL_BLUE;
	const char *COL_GREEN;

	/**
	 * Constructor.
	 */
	Config();

	/**
	 * Destructor.
	 */
	~Config();


	private:

																// Get string setting from config file
	const char *getSettingString(const char *section, const char *setting, const char *defaultSetting);	
																// Get integer setting from config file
	int getSettingInt(const char *section, const char *setting, int defaultSetting);	
																// Get boolean setting from config file
	bool getSettingBool(const char *section, const char *setting, bool defaultSetting);
};

}

#endif

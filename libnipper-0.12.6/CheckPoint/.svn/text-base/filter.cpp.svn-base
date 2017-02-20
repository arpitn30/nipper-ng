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

// Includes...
#include <cstring>
#include <cstdlib>

#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "device.h"
#include "filter.h"


CheckPointFilter::CheckPointFilter()
{
	// Object options...
	networkObjectName = i18n("Network Objects");			// The name for the object (used in config report)
	networkObjectDescription = i18n("");					// The description for the object (config report)
	protocolObjectName = i18n("Protocol Objects");			// The name for the object (used in config report)
	protocolObjectDescription = i18n("");					// The description for the object (config report)
	icmpObjectName = i18n("*ABBREV*ICMP*-ABBREV* Objects");	// The name for the object (used in config report)
	icmpObjectDescription = i18n("");						// The description for the object (config report)
	serviceObjectName = i18n("Service Objects");			// The name for the object (used in config report)
	serviceObjectDescription = i18n("");					// The description for the object (config report)

	// Filter device options...
	denyAllAndLogDefault = false;							// Does it deny all and log by default?
	logOnlyDenySupported = false;							// Is only Drop rule logging supported
	defaultFilterActionSupported = false;					// Default action supported on the device
	allowByDefault = false;									// Allow by default?
	defaultActionIsAllow = false;							// Is the default action to allow
	logLevelsSupported = false;								// Are log Levels supported
	noAccessWithoutFilters = true;							// Is access not granted if no filters are configured
	filterSupportsInstalled = true;							// If filtering supports installed (i.e. CheckPoint)
	filterSupportsThrough = true;							// If a filtering supports through (i.e. CheckPoint)
	rejectRulesSupported = false;							// If reject rules are supported
	bypassRulesSupported = false;							// If bypass rules are supported
	defaultRulesSupported = false;							// If default rules are supported
	ruleListsAreAssigned = false;							// Rule lists are assigned to specific elements
	allowName = i18n("Accept");								// The name given to an allowed filter
	denyName = i18n("Drop");								// The name given to a denied filter
	rejectName = i18n("Reject");							// The name given to a rejected filter
	filterConfigTitle = i18n("Policy Collection Configuration");			// The Title for the configuration report section
	filterConfigText = i18n("A policy determines which network traffic are allowed to pass through the networks managed by the *DEVICETYPE* device, or if it is to be dropped. The policy is processed one rule at a time with the first rule that matches the network packet applying.");							// The device specific configuration report section text
	filterConfigText2 = i18n("");							// The device specific configuration report section text2
	useFilterID = false;									// Use the filter ID to identify a filter (otherwise a line no. is used)
	filterIDTitle = i18n("Rule");							// The title for the filter ID/line no. table column
	filterListName = i18n("policy");						// The name of the filter list, for use in text paragraphs
	filterListNameTitle = i18n("Policy");					// The name of the filter list, for use in titles
	filterListNamePlaural = i18n("policies");				// The name of the filter list, for use in text paragraphs
	filterTitle = i18n("Rule");								// The name of a filter, for use in titles
	filterTitlePlaural = i18n("Rules");						// The name of a filter, for use in titles
	filterName = i18n("rule");								// The name of a filter, for use use in text paragraph
	filterNamePlaural = i18n("rules");						// The name of a filter, for use use in text paragraph

	// Issue titles...
	allowAndNotLogIssue = i18n("Not All Accept Rules Log Access");	// The title text for the "All Allow Rules Do Not Log" issue
	allowAndNotLogTable = i18n("Accept rules that do not log");		// The table title text for the "All Allow Rules Do Not Log" issue
	allowAndNotLogConcl = i18n("not all accept rules log access");	// The conclusions text for the "All Allow Rules Do Not Log" issue
	allowAndNotLogReco = i18n("Configure logging for all rules");	// The recommendations text for "All Allow Rules Do Not Log" (and deny) issue
	denyAndNotLogIssue = i18n("Not All Drop Rules Log Access");		// The title text for the "All Allow Rules Do Not Log" issue
	denyAndNotLogTable = i18n("Drop rules that do not log");		// The table title text for the "All Allow Rules Do Not Log" issue
	denyAndNotLogConcl = i18n("not all deny rules log access");		// The conclusions text for the "All Allow Rules Do Not Log" issue
	configRuleLogging = i18n("Logging can be enabled for each rule individually using the standard *DEVICETYPE* device management tools.");								// The text describing how to configure logging for filter rules
	noFilteringIssue = i18n("No Policies Were Configured");	// The title text for the "No filtering" issue
	noFilteringRec = i18n("Configure policies to restict access");		// The title text for the "No filtering" recommendation
	noFilteringCon = i18n("no policies were configured");		// The title text for the "No filtering" conclusion
	legacyIssueFinding = i18n("");								// The finding for the legacy issue
	legacyIssueImpact = i18n("");								// The impact for the legacy issue
	legacyIssueEase = i18n("");									// The ease for the legacy issue
	legacyIssueRec = i18n("");									// The recommendation for the legacy issue
	allowAnythingTable = i18n("Rules accept any access");		// The allow anything table title text
	allowWeakTable = i18n("Rules provide weak filtering");		// Weak source/service/destination/service table title text
	allowAnyAnyAnyTable = i18n("Rules accept any host to access any destination and service");			// The allow any source, destination and service table title text
	allowWeakWeakWeakTable = i18n("Rules provide weak filtering of source, destination and service");	// The allow weak source, destination and service table title text
	allowAnyServiceAnyTable = i18n("Rules allow any source port to any destination and service");		// The allow any source port, destination and service table title text
	allowWeakServiceAnyTable = i18n("Rules provide weak filtering of source port to destination and service");	// The allow weak source, destination and service table title text
	allowAnyAnyTable = i18n("Rules accept any source to any destination");					// The allow any source, destination table title text
	allowAnyAnyServiceTable = i18n("Rules accept any source to any destination service");	// The allow any source, destination service table title text
	allowAnyDestServiceTable = i18n("Rules accept any destination and service");			// The allow any destination and service table title text
	allowAnyPortDestTable = i18n("Rules accept any source port to any destination address");			// The allow any source port to any destination table title text
	allowAnyPortServiceTable = i18n("Rules accept any source port to any destination service");			// The allow any source port to any dest service table title text
	allowWeakWeakTable = i18n("Rules accept weak filtering of source and destination addresses");		// The allow weak source, destination addresses
	allowWeakWeakServiceTable = i18n("Rules accept weak source addresses and destination services");	// The allow weak source, destination service table title text
	allowDestAndServiceTable = i18n("Rules accept weak destination addresses and services");// The allow weak destination and service table title text
	allowWeakPortDestTable = i18n("Rules accept weak source ports and destination");		// The allow weak source port to Destination table title text
	allowWeakPortServiceTable = i18n("Rules accept weak source ports and destination services");		// The allow weak source port to service table title text
	allowAnySourceTable = i18n("Rules accept from any source address");						// The allow any source address table title text
	allowNetSourceTable = i18n("Rules accept from a network source address");				// The allow a network source address table title text
	allowAnyPortTable = i18n("Rules accept from any source port");							// The allow any source port table title text
	allowRangePortTable = i18n("Rules accept from a source port range");					// The allow range source port table title text
	allowAnyDestTable = i18n("Rules accept to any destination");							// The allow any destination table title text
	allowNetDestTable = i18n("Rules accept to a network destination");						// The allow a network destination table title text
	allowToAnyDestServiceTable = i18n("Rules accept to any destination service");			// The allow any destination service table title text
	allowToNetDestServiceTable = i18n("Rules accept to a destination service range");		// The allow a destination service range table title text
	bypassContentFilterCon = i18n("Rules were configured that bypass the content filtering");			// Bypass filter conclusion text
	bypassContentFilterRec = i18n("Connfigure rules that do not bypass the content filtering");	// Bypass filter recommendation text
	defaultFilterCon = i18n("Rules were configured that default to the ports filtering action");		// Default filter conclusion text
	defaultFilterRec = i18n("Configure Rules that do not default to the ports filtering action");		// Default filter recommendation text
	rejectSecurityIssueTitle = i18n("Reject Rules Were Configured");							// Reject filter title text
	securityRejectTextCon = i18n("Rules were configured that reject network traffic");			// Reject filter conclusion text
	securityRejectTextRec = i18n("Configure rules to drop rather than reject network traffic");	// Reject filter recommendation text
	clearTextServiceCon = i18n("Rules were configured that accept access to clear text protocol services");		// Clear Text Service conclusions text
	clearTextServiceRec = i18n("Configure rules to drop access to any clear text protocol services");			// Clear Text Service recommendations text2
	configureFilterListRecIssueText = i18n("");												// The text and commands to configure a filter list
	configureFilterRecIssueText = i18n("");													// The text and commands to configure a filter
	unnecessaryServiceCon = i18n("Rules were configured that accept access to potentially unnecessary services");			// Unnecessary Service conclusions text
	unnecessaryServiceRec = i18n("Configure rules to drop access to any unnecessary services");	// Unnecessary Service recommendations text2
	filtersWithNoCommentsTitle = i18n("Not All Rules Include Comments");	// Filters with no comments title text
	noFilterCommentsCon = i18n("not all rules include comment text indicating their purpose");	// The no comments conclusion text
	noFilterCommentsRec = i18n("Configure comment text for all rules");		// The no comments recommendation text
	configureFilterCommentText = i18n("");													// The text and commands to configure a filters comment text
	disabledFiltersTitle = i18n("Disabled Rules Were Configured");			// The disabled filter issues title text
	removeFilterText = i18n("");															// The commands and text to delete a filter
	disabledFilterCon = i18n("disabled rules were configured");				// The disabled filter conclusion text
	disabledFilterRec = i18n("Remove all disabled rules");					// The disabled filter recommendation text
	defaultActionIssueTitle = i18n("The Default Network Filtering Action Accepts Access");	// The default filter action issue title
	defaultActionIssueCon = i18n("the default Policy action was configured to accept access when a rule does not match");	// The default filter action conclusion text
	defaultActionIssueRec = i18n("Set the default policy action to drop network traffic");		// The default filter action recommendation text
	configureDefaultActionText = i18n("");													// The text and commands to configure the default action
	unusedFiltersIssueTitle = i18n("Unused Rules Were Configured At The Policies End");	// Unused filters at the end of the filter list title
	unusedFiltersIssueCon = i18n("unused rules were configured at the end of the Policies");		// Unused filters issue conclusions text
	unusedFiltersIssueRec = i18n("Remove all unused rules");				// Unused filters issue recommendation text
	denyAllLogIssueTitle = i18n("Policy Does Not End with Drop All And Log");	// Drop All And Log Issue title
	denyAllLogConfigure = i18n("");															// The text and commands to add a deny all and log line
	denyAllLogIssueCon = i18n("not all policies end with a deny all and log ");		// The deny all and log conclusions text
	denyAllLogIssueRec = i18n("Configure a deny all and log rule as the last rule in each policy");			// The deny all and log recommendations text
	contradictIssueTitle = i18n("Contradicting Rules Were Configured");		// The contradict issue title
	contradictIssueTable = i18n("contradictions of rule");					// The contradict table issue title
	contradictIssueCon = i18n("Rules were configured that contradict other rules");				// The contradict issue conclusion
	contradictIssueRec = i18n("Reconfigure the rules so they do not contradict other rules");	// The contradict issue recommendation
	duplicateIssueTitle = i18n("Duplicate Rules Were Configured");			// The duplicate/overlapping issue title
	duplicateIssueTable = i18n("duplicates of rule");										// The duplicate/overlapping issue title
	duplicateIssueCon = i18n("Rules were configured that duplicate the configuration of other rules");	// The duplicate/overlapping issue title
	duplicateIssueRec = i18n("Reconfigure the Rules so that the rules do not duplicate other rules");						// The duplicate/overlapping issue title
}


CheckPointFilter::~CheckPointFilter()
{
}


int CheckPointFilter::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	int errorCode = 0;

	// If objects...
	if ((strcmp(command->part(0), ":netobj") == 0) || (strcmp(command->part(0), ":network_objects") == 0))
		errorCode = processDeviceObjectConfig(device, command, line, lineSize);

	// Services Start...
	else if ((strcmp(command->part(0), ":servobj") == 0) || (strcmp(command->part(0), ":services") == 0))
		errorCode = processDeviceServicesConfig(device, command, line, lineSize);

	return errorCode;
}


int CheckPointFilter::processWRulesDevice(Device *device, const char *policyList, bool active)
{
	// Variables...
	Filter::filterListConfig *filterListPointer = 0;
	char line[1024];
	ConfigLine command;

	// Read a line from the config...
	device->readLine(line, sizeof(line));

	// Split it up into parts...
	command.setConfigLine(line);

	if (device->config->reportFormat == Config::Debug)
		printf("%sPolicy Collection Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

	filterListPointer = getFilterList(policyList);
	filterListPointer->active = active;
	filterListPointer->type = i18n("Policy");
	filterListPointer->typeDescription = i18n("A policy is a collection of rules that determine whether traffic managed by the *DEVICETYPE* device is accepted or dropped. This section details the policy collection rules.");

	filterListPointer->legacyType = false;				// Is the filter list a legacy type?
	filterListPointer->sourceOnly = false;				// The type of filter
	filterListPointer->loggingSupport = true;			// Does the filter list support logging
	filterListPointer->supportsTime = true;				// Filter support time (dest only)
	filterListPointer->supportsFragments = false;			// Filter support fragments (dest only)
	filterListPointer->supportsEstablished = false;		// Filter support established (dest only)
	filterListPointer->sourceServiceSupported = false;	// If source services are supported
	filterListPointer->disabledFilterSupport = true;		// Is it possible to disable filters?
	filterListPointer->filterCommentsSupported = true;	// Are filter comments supported
	filterListPointer->showProtocol = false;				// Show the protocol? (some devices use a configured service)
	filterListPointer->showFilterZones = false;			// Does the filter use filter-based zones (i.e. SonicWALL)
	filterListPointer->showStop = false;					// Does the filter have a stop status (i.e. Passport devices)
	filterListPointer->showFilterType = false;			// Does the filter have a type (i.e. like on Passport devices)

	// The process device configuration file loop...
	while ((feof(device->inputFile) == 0) && (strcmp(command.part(0), ")") != 0))
	{

		// Read a line from the config...
		device->readLine(line, sizeof(line));

		// Split it up into parts...
		command.setConfigLine(line);

		// Rules Start...
		if ((strcmp(command.part(0), ":rule") == 0) && (strcmp(command.part(1), "()") != 0))
			processDeviceRuleConfig(device, &command, (char *)line, sizeof(line), filterListPointer);

		// Unknown CheckPoint Structure...
		else if ((strncmp(command.part(0), ":", 1) == 0) && (strcmp(command.part(1), "()") != 0) && (command.part(1)[0] == '('))
			((CheckPointDevice *)device)->processUnknownCheckPointConfig(&command, (char *)&line, sizeof(line));

		// All others...
		else if (command.part(0)[0] != ')')
			device->lineNotProcessed(line);
	}

	if (device->config->reportFormat == Config::Debug)
		printf("%sPolicy Collection End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

	return 0;
}


int CheckPointFilter::processRRulesDevice(Device *device)
{
	// Variables...
	Filter::filterListConfig *filterListPointer = 0;
	char line[1024];
	ConfigLine command;

	// Read a line from the config...
	device->readLine(line, sizeof(line));

	// Split it up into parts...
	command.setConfigLine(line);

	if (device->config->reportFormat == Config::Debug)
		printf("%sRules File Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

	filterListPointer = getFilterList(device->deviceMake);
	filterListPointer->active = true;
	filterListPointer->type = i18n("Policy");
	filterListPointer->typeDescription = i18n("A policy is a collection of rules that determine whether traffic managed by the *DEVICETYPE* device is accepted or dropped. This section details the policy collection rules.");

	filterListPointer->legacyType = false;				// Is the filter list a legacy type?
	filterListPointer->sourceOnly = false;				// The type of filter
	filterListPointer->loggingSupport = true;			// Does the filter list support logging
	filterListPointer->supportsTime = true;				// Filter support time (dest only)
	filterListPointer->supportsFragments = false;			// Filter support fragments (dest only)
	filterListPointer->supportsEstablished = false;		// Filter support established (dest only)
	filterListPointer->sourceServiceSupported = false;	// If source services are supported
	filterListPointer->disabledFilterSupport = true;		// Is it possible to disable filters?
	filterListPointer->filterCommentsSupported = true;	// Are filter comments supported
	filterListPointer->showProtocol = false;				// Show the protocol? (some devices use a configured service)
	filterListPointer->showFilterZones = false;			// Does the filter use filter-based zones (i.e. SonicWALL)
	filterListPointer->showStop = false;					// Does the filter have a stop status (i.e. Passport devices)
	filterListPointer->showFilterType = false;			// Does the filter have a type (i.e. like on Passport devices)

	// The process device configuration file loop...
	while ((feof(device->inputFile) == 0) && (strcmp(command.part(0), ")") != 0))
	{

		// Read a line from the config...
		device->readLine(line, sizeof(line));

		// Split it up into parts...
		command.setConfigLine(line);

		// Rules Start...
		if ((strcmp(command.part(0), ":rules") == 0) && (strcmp(command.part(1), "()") != 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sRules Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			// The process device configuration file loop...
			while ((feof(device->inputFile) == 0) && (strcmp(command.part(0), ")") != 0))
			{

				// Read a line from the config...
				device->readLine(line, sizeof(line));

				// Split it up into parts...
				command.setConfigLine(line);

				// Rule Start...
				if ((strcmp(command.part(0), ":") == 0) && (strcmp(command.part(1), "()") != 0))
					processDeviceRuleConfig(device, &command, (char *)line, sizeof(line), filterListPointer);

				// Unknown CheckPoint Structure...
				else if ((strncmp(command.part(0), ":", 1) == 0) && (strcmp(command.part(1), "()") != 0) && (command.part(1)[0] == '('))
					((CheckPointDevice *)device)->processUnknownCheckPointConfig(&command, (char *)&line, sizeof(line));

				// All others...
				else if (command.part(0)[0] != ')')
					device->lineNotProcessed(line);

			}

			if (device->config->reportFormat == Config::Debug)
				printf("%sRules End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			command.setConfigLine((char *)"");
		}

		// Unknown CheckPoint Structure...
		else if ((strncmp(command.part(0), ":", 1) == 0) && (strcmp(command.part(1), "()") != 0) && (command.part(1)[0] == '('))
			((CheckPointDevice *)device)->processUnknownCheckPointConfig(&command, (char *)&line, sizeof(line));

		// All others...
		else if (command.part(0)[0] != ')')
			device->lineNotProcessed(line);
	}

	if (device->config->reportFormat == Config::Debug)
		printf("%sRules File End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

	return 0;
}


int CheckPointFilter::processFRulesDevice(Device *device)
{
	// Variables...
	Filter::filterListConfig *filterListPointer = 0;
	Filter::filterConfig *filterPointer = 0;
	char line[1024];
	string policyName;
	bool listAlreadyExists = false;
	bool incrementPointer = false;
	ConfigLine command;

	// Read a line from the config...
	device->readLine(line, sizeof(line));

	// Split it up into parts...
	command.setConfigLine(line);

	if (device->config->reportFormat == Config::Debug)
		printf("%sRulebases File Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

	// The process device configuration file loop...
	while ((feof(device->inputFile) == 0) && (strcmp(command.part(0), ")") != 0))
	{

		// Read a line from the config...
		device->readLine(line, sizeof(line));

		// Split it up into parts...
		command.setConfigLine(line);

		// Rulebase Start...
		if ((strcmp(command.part(0), ":rule-base") == 0) && (strcmp(command.part(1), "()") != 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sRulebase Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			policyName.assign(command.part(1) + 4);
			policyName.resize(policyName.size() - 1);
			filterPointer = 0;

			filterListPointer = getOnlyFilterList(policyName.c_str());
			if (filterListPointer == 0)
			{
				listAlreadyExists = false;
				filterListPointer = getFilterList(policyName.c_str());
				filterListPointer->type = i18n("Policy");
				filterListPointer->typeDescription = i18n("A policy is a collection of rules that determine whether traffic managed by the *DEVICETYPE* device is accepted or dropped. This section details the policy collection rules.");

				filterListPointer->legacyType = false;				// Is the filter list a legacy type?
				filterListPointer->sourceOnly = false;				// The type of filter
				filterListPointer->loggingSupport = true;			// Does the filter list support logging
				filterListPointer->supportsTime = true;				// Filter support time (dest only)
				filterListPointer->supportsFragments = false;			// Filter support fragments (dest only)
				filterListPointer->supportsEstablished = false;		// Filter support established (dest only)
				filterListPointer->sourceServiceSupported = false;	// If source services are supported
				filterListPointer->disabledFilterSupport = true;		// Is it possible to disable filters?
				filterListPointer->filterCommentsSupported = true;	// Are filter comments supported
				filterListPointer->showProtocol = false;				// Show the protocol? (some devices use a configured service)
				filterListPointer->showFilterZones = false;			// Does the filter use filter-based zones (i.e. SonicWALL)
				filterListPointer->showStop = false;					// Does the filter have a stop status (i.e. Passport devices)
				filterListPointer->showFilterType = false;			// Does the filter have a type (i.e. like on Passport devices)
			}
			else
			{
				listAlreadyExists = true;
				filterPointer = filterListPointer->filter;
			}

			// The process device configuration file loop...
			while ((feof(device->inputFile) == 0) && (strcmp(command.part(0), ")") != 0))
			{

				// Read a line from the config...
				device->readLine(line, sizeof(line));

				// Split it up into parts...
				command.setConfigLine(line);

				// Default Line...
				if (strcmp(command.part(0), ":default") == 0)
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sRulebase Default Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					if (listAlreadyExists == false)
					{
						if (command.part(1)[0] == '1')
							filterListPointer->active = true;
						else
							filterListPointer->active = false;
					}
				}

				// Rule Start...
				else if ((strcmp(command.part(0), ":rule") == 0) && (strcmp(command.part(1), "()") != 0))
				{
					incrementPointer = processDeviceRuleConfig(device, &command, (char *)line, sizeof(line), filterListPointer, filterPointer);
					if ((incrementPointer == true) && (filterPointer != 0))
						filterPointer = filterPointer->next;
				}

				// Unknown CheckPoint Structure...
				else if ((strncmp(command.part(0), ":", 1) == 0) && (strcmp(command.part(1), "()") != 0) && (command.part(1)[0] == '('))
					((CheckPointDevice *)device)->processUnknownCheckPointConfig(&command, (char *)&line, sizeof(line));

				// All others...
				else if (command.part(0)[0] != ')')
					device->lineNotProcessed(line);

			}

			if (device->config->reportFormat == Config::Debug)
				printf("%sRulebase End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			command.setConfigLine((char *)"");
		}

		// Unknown CheckPoint Structure...
		else if ((strncmp(command.part(0), ":", 1) == 0) && (strcmp(command.part(1), "()") != 0) && (command.part(1)[0] == '('))
			((CheckPointDevice *)device)->processUnknownCheckPointConfig(&command, (char *)&line, sizeof(line));

		// All others...
		else if (command.part(0)[0] != ')')
			device->lineNotProcessed(line);
	}

	if (device->config->reportFormat == Config::Debug)
		printf("%sRulebases File End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

	return 0;
}


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

#include "../device/common/configline.h"
#include "../globaldefs.h"
#include "device.h"
#include "filter.h"


SonicOSFilter::SonicOSFilter()
{
	// Filter device options...
	denyAllAndLogDefault = false;							// Does it deny all and log by default?
	defaultFilterActionSupported = false;					// Default action supported on the device
	allowByDefault = false;									// Allow by default?
	defaultActionIsAllow = false;							// Is the default action to allow
	logLevelsSupported = false;								// Are log Levels supported
	logOnlyDenySupported = false;							// Is only Deny rule logging supported
	noAccessWithoutFilters = false;							// Is access not granted if no filters are configured
	filterSupportsInstalled = false;						// If filtering supports installed (i.e. CheckPoint)
	filterSupportsThrough = false;							// If a filtering supports through (i.e. CheckPoint)
	rejectRulesSupported = true;							// If reject rules are supported
	bypassRulesSupported = false;							// If bypass rules are supported
	defaultRulesSupported = false;							// If default rules are supported
	ruleListsAreAssigned = false;							// Rule lists are assigned to specific elements
	allowName = i18n("Allow");								// The name given to an allowed filter
	denyName = i18n("Deny");								// The name given to a denied filter
	rejectName = i18n("Reject");							// The name given to a rejected filter
	filterConfigTitle = i18n("Access Rules Configuration");			// The Title for the configuration report section
	filterConfigText = i18n("");							// The device specific configuration report section text
	filterConfigText2 = i18n("");							// The device specific configuration report section text2
	useFilterID = false;									// Use the filter ID to identify a filter (otherwise a line no. is used)
	filterIDTitle = i18n("Line");							// The title for the filter ID/line no. table column
	filterListName = i18n("access rule list");				// The name of the filter list, for use in text paragraphs
	filterListNameTitle = i18n("Access Rule List");			// The name of the filter list, for use in titles
	filterListNamePlaural = i18n("Access Rule List");		// The name of the filter list, for use in text paragraphs
	filterTitle = i18n("Access Rule");						// The name of a filter, for use in titles
	filterTitlePlaural = i18n("Access Rules");				// The name of a filter, for use in titles
	filterName = i18n("access rule");						// The name of a filter, for use use in text paragraph
	filterNamePlaural = i18n("access rules");				// The name of a filter, for use use in text paragraph

	// Issue titles...
	allowAndNotLogIssue = i18n("Not All Allow Access Rules Log Access");	// The title text for the "All Allow Rules Do Not Log" issue
	allowAndNotLogTable = i18n("Allow Access Rules that do not log");		// The table title text for the "All Allow Rules Do Not Log" issue
	allowAndNotLogConcl = i18n("not all allow access rules log access");	// The conclusions text for the "All Allow Rules Do Not Log" issue
	allowAndNotLogReco = i18n("Configure logging for all allow access rules");	// The recommendations text for "All Allow Rules Do Not Log" (and deny) issue
	denyAndNotLogIssue = i18n("Not All Deny Access Rules Log Access");		// The title text for the "All Allow Rules Do Not Log" issue
	denyAndNotLogTable = i18n("Deny access rules that do not log");			// The table title text for the "All Allow Rules Do Not Log" issue
	denyAndNotLogConcl = i18n("not all deny access rules log access");		// The conclusions text for the "All Allow Rules Do Not Log" issue
	configRuleLogging = i18n("Access rule logging can be configured using the SonicWALL web management interface.");								// The text describing how to configure logging for filter rules
	noFilteringIssue = i18n("No Access Rule Lists Were Configured");		// The title text for the "No filtering" issue
	noFilteringRec = i18n("Configure access rule lists to restict access");	// The title text for the "No filtering" recommendation
	noFilteringCon = i18n("no access rule lists were configured");			// The title text for the "No filtering" conclusion
	legacyIssueFinding = i18n("");								// The finding for the legacy issue
	legacyIssueImpact = i18n("");								// The impact for the legacy issue
	legacyIssueEase = i18n("");									// The ease for the legacy issue
	legacyIssueRec = i18n("");									// The recommendation for the legacy issue
	allowAnythingTable = i18n("Access rules allow any access");	// The allow anything table title text
	allowWeakTable = i18n("Access rules provide weak filtering");		// Weak source/service/destination/service table title text
	allowAnyAnyAnyTable = i18n("Access rules allow any host to access any destination and service");			// The allow any source, destination and service table title text
	allowWeakWeakWeakTable = i18n("Access rules provide weak filtering of source, destination and service");	// The allow weak source, destination and service table title text
	allowAnyServiceAnyTable = i18n("Access rules allow any source port to any destination and service");		// The allow any source port, destination and service table title text
	allowWeakServiceAnyTable = i18n("Access rules provide weak filtering of source port to destination and service");	// The allow weak source, destination and service table title text
	allowAnyAnyTable = i18n("Access rules allow any source to any destination");				// The allow any source, destination table title text
	allowAnyAnyServiceTable = i18n("Access rules allow any source to any destination service");	// The allow any source, destination service table title text
	allowAnyDestServiceTable = i18n("Access rules allow any destination and service");			// The allow any destination and service table title text
	allowAnyPortDestTable = i18n("Access rules allow any source port to any destination address");			// The allow any source port to any destination table title text
	allowAnyPortServiceTable = i18n("Access rules allow any source port to any destination service");		// The allow any source port to any dest service table title text
	allowWeakWeakTable = i18n("Access rules allow weak filtering of source and destination addresses");		// The allow weak source, destination addresses
	allowWeakWeakServiceTable = i18n("Access rules allow weak source addresses and destination services");	// The allow weak source, destination service table title text
	allowDestAndServiceTable = i18n("Access rules allow weak destination addresses and services");// The allow weak destination and service table title text
	allowWeakPortDestTable = i18n("Access rules allow weak source ports and destination");		// The allow weak source port to Destination table title text
	allowWeakPortServiceTable = i18n("Access rules allow weak source ports and destination services");		// The allow weak source port to service table title text
	allowAnySourceTable = i18n("Access rules allow from any source address");					// The allow any source address table title text
	allowNetSourceTable = i18n("Access rules allow from a network source address");				// The allow a network source address table title text
	allowAnyPortTable = i18n("Access rules allow from any source port");						// The allow any source port table title text
	allowRangePortTable = i18n("Access rules allow from a source port range");					// The allow range source port table title text
	allowAnyDestTable = i18n("Access rules allow to any destination");							// The allow any destination table title text
	allowNetDestTable = i18n("Access rules allow to a network destination");					// The allow a network destination table title text
	allowToAnyDestServiceTable = i18n("Access rules allow to any destination service");			// The allow any destination service table title text
	allowToNetDestServiceTable = i18n("Access rules allow to a destination service range");		// The allow a destination service range table title text
	bypassContentFilterCon = i18n("Access rules were configured that bypass the content filtering");			// Bypass filter conclusion text
	bypassContentFilterRec = i18n("Connfigure access rules that do not bypass the content filtering");	// Bypass filter recommendation text
	defaultFilterCon = i18n("Access rules were configured that default to the ports filtering action");		// Default filter conclusion text
	defaultFilterRec = i18n("Configure access rules that do not default to the ports filtering action");		// Default filter recommendation text
	rejectSecurityIssueTitle = i18n("Reject Access Rules Were Configured");						// Reject filter title text
	securityRejectTextCon = i18n("Access Rules were configured that reject network traffic");	// Reject filter conclusion text
	securityRejectTextRec = i18n("Configure access rules to deny rather than reject network traffic");	// Reject filter recommendation text
	clearTextServiceCon = i18n("Access rules were configured that allow access to clear text protocol services");		// Clear Text Service conclusions text
	clearTextServiceRec = i18n("Configure access rules to deny access to any clear text protocol services");			// Clear Text Service recommendations text2
	configureFilterListRecIssueText = i18n("");												// The text and commands to configure a filter list
	configureFilterRecIssueText = i18n("");													// The text and commands to configure a filter
	unnecessaryServiceCon = i18n("Access rules were configured that allow access to potentially unnecessary services");			// Unnecessary Service conclusions text
	unnecessaryServiceRec = i18n("Configure access rules to deny access to any unnecessary services");	// Unnecessary Service recommendations text2
	filtersWithNoCommentsTitle = i18n("Not All Access Rules Include Comments");	// Filters with no comments title text
	noFilterCommentsCon = i18n("not all access rules include comment text indicating their purpose");	// The no comments conclusion text
	noFilterCommentsRec = i18n("Configure comment text for all access rules");		// The no comments recommendation text
	configureFilterCommentText = i18n("");													// The text and commands to configure a filters comment text
	disabledFiltersTitle = i18n("Disabled Access Rules Were Configured");			// The disabled filter issues title text
	removeFilterText = i18n("");															// The commands and text to delete a filter
	disabledFilterCon = i18n("disabled access rules were configured");				// The disabled filter conclusion text
	disabledFilterRec = i18n("Remove all disabled access rules");					// The disabled filter recommendation text
	defaultActionIssueTitle = i18n("The Default Network Filtering Action Permits Access");	// The default filter action issue title
	defaultActionIssueCon = i18n("the default filtering action was configured to allow access when a access rule does not match");	// The default filter action conclusion text
	defaultActionIssueRec = i18n("Set the default filtering action to deny network traffic");		// The default filter action recommendation text
	configureDefaultActionText = i18n("");													// The text and commands to configure the default action
	unusedFiltersIssueTitle = i18n("Unused Access Rules Were Configured At The Access Rule List End");	// Unused filters at the end of the filter list title
	unusedFiltersIssueCon = i18n("unused access rules were configured at the end of the access rule list");		// Unused filters issue conclusions text
	unusedFiltersIssueRec = i18n("Remove all unused access rules");				// Unused filters issue recommendation text
	denyAllLogIssueTitle = i18n("Access Rule List Does Not End with Deny All And Log");	// Deny All And Log Issue title
	denyAllLogConfigure = i18n("");															// The text and commands to add a deny all and log line
	denyAllLogIssueCon = i18n("not all access rule lists end with a deny all and log ");		// The deny all and log conclusions text
	denyAllLogIssueRec = i18n("Configure a deny all and log access rule as the last access rule in the access rule list");			// The deny all and log recommendations text
	contradictIssueTitle = i18n("Contradicting Access Rules Were Configured");		// The contradict issue title
	contradictIssueTable = i18n("contradictions of access rules");					// The contradict table issue title
	contradictIssueCon = i18n("Access rules were configured that contradict other access rules");				// The contradict issue conclusion
	contradictIssueRec = i18n("Reconfigure the access rules so they do not contradict other access rules");	// The contradict issue recommendation
	duplicateIssueTitle = i18n("Duplicate Access Rules Were Configured");			// The duplicate/overlapping issue title
	duplicateIssueTable = i18n("duplicates of access rules");										// The duplicate/overlapping issue title
	duplicateIssueCon = i18n("Access rules were configured that duplicate the configuration of other access rules");	// The duplicate/overlapping issue title
	duplicateIssueRec = i18n("Reconfigure the access rules so that the rules do not duplicate other access rules");						// The duplicate/overlapping issue title
}


SonicOSFilter::~SonicOSFilter()
{
}


int SonicOSFilter::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	netObjectListConfig *objectListPointer = 0;
	netObjectListConfig *tempListPointer = 0;
	filterObjectConfig *objectPointer = 0;
	filterObjectConfig *subObjectPointer = 0;
	filterConfig *filterPointer = 0;
	filterListConfig *filterListPointer = 0;
	fpos_t filePosition;
	string tempString;
	int tempInt = 0;
	int tempCounter = 0;
	int errorCode = 0;
	int currentObject = 9999;

	// Firewall Policy
	if (strncmp(command->part(0), "policy", 6) == 0)
	{

		filterListPointer = getFilterList("Access Rules");
		filterListPointer->type = i18n("Access Rules");				// The filter list type name (used in the config report)
		filterListPointer->typeDescription = i18n("Access rules are used to filter the network traffic passing through *DEVICETYPE* devices. This section details those rules.");	// The filter list type description for the report (used in config report)
		filterListPointer->legacyType = false;				// Is the filter list a legacy type?
		filterListPointer->sourceOnly = false;				// The type of filter
		filterListPointer->loggingSupport = true;			// Does the filter list support logging
		filterListPointer->supportsTime = false;				// Filter support time (dest only)
		filterListPointer->supportsFragments = true;			// Filter support fragments (dest only)
		filterListPointer->supportsEstablished = false;		// Filter support established (dest only)
		filterListPointer->sourceServiceSupported = false;	// If source services are supported
		filterListPointer->disabledFilterSupport = true;		// Is it possible to disable filters?
		filterListPointer->filterCommentsSupported = true;	// Are filter comments supported
		filterListPointer->showProtocol = false;				// Show the protocol? (some devices use a configured service)
		filterListPointer->showFilterZones = true;			// Does the filter use filter-based zones (i.e. SonicWALL)
		filterPointer = addFilter(filterListPointer);

		while ((feof(device->inputFile) == 0) && (strncmp(command->part(0), "policy", 6) == 0))
		{

			// Action...
			if (strncmp(command->part(0), "policyAction_", 13) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sPolicy Action Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (filterPointer == 0)
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 13);
				}
				else if (filterPointer->id != atoi(command->part(0) + 13))
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 13);
				}

				if (strcasecmp(command->part(1), "2") == 0)
					filterPointer->action = allowAction;
				else if (strcasecmp(command->part(1), "1") == 0)
					filterPointer->action = rejectAction;
				else
					filterPointer->action = denyAction;
			}

			// Service
			else if ((strncmp(command->part(0), "policyDstSvc_", 13) == 0) && (command->parts > 1))
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sPolicy Destination Service Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (filterPointer == 0)
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 13);
				}
				else if (filterPointer->id != atoi(command->part(0) + 13))
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 13);
				}

				objectPointer = addFilterObject(filterPointer, destinationService);
				if (command->parts > 1)
				{
					objectPointer->name.assign(strstr(line, command->part(1)));
					objectPointer->type = groupObject;
					objectPointer->serviceOper = serviceOperEqual;
				}
				else
				{
					objectPointer->name.assign(i18n("Any"));
					objectPointer->type = anyObject;
					objectPointer->serviceOper = serviceOperAny;
				}
			}

			// Source Zone
			else if (strncmp(command->part(0), "policySrcZone_", 14) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sPolicy Source Zone Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (filterPointer == 0)
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 14);
				}
				else if (filterPointer->id != atoi(command->part(0) + 14))
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 14);
				}

				if (command->parts == 1)
					filterPointer->sourceZone.assign(i18n("Any"));
				else
					filterPointer->sourceZone.assign(command->part(1));
			}

			// Destination Zone
			else if (strncmp(command->part(0), "policyDstZone_", 14) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sPolicy Destination Zone Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (filterPointer == 0)
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 14);
				}
				else if (filterPointer->id != atoi(command->part(0) + 14))
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 14);
				}

				if (command->parts == 1)
					filterPointer->destZone.assign(i18n("Any"));
				else
					filterPointer->destZone.assign(command->part(1));
			}

			// Source
			else if (strncmp(command->part(0), "policySrcNet_", 13) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sPolicy Source Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (filterPointer == 0)
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 13);
				}
				else if (filterPointer->id != atoi(command->part(0) + 13))
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 13);
				}

				objectPointer = addFilterObject(filterPointer, source);
				if (command->parts > 1)
				{
					objectPointer->name.assign(strstr(line, command->part(1)));
					objectPointer->type = groupObject;
					objectPointer->serviceOper = serviceOperEqual;
				}
				else
				{
					objectPointer->name.assign(i18n("Any"));
					objectPointer->type = anyObject;
					objectPointer->serviceOper = serviceOperAny;
				}
			}

			// Destination
			else if (strncmp(command->part(0), "policyDstNet_", 13) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sPolicy Destination Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (filterPointer == 0)
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 13);
				}
				else if (filterPointer->id != atoi(command->part(0) + 13))
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 13);
				}

				objectPointer = addFilterObject(filterPointer, destination);
				if (command->parts > 1)
				{
					objectPointer->name.assign(strstr(line, command->part(1)));
					objectPointer->type = groupObject;
					objectPointer->serviceOper = serviceOperEqual;
				}
				else
				{
					objectPointer->name.assign(i18n("Any"));
					objectPointer->type = anyObject;
					objectPointer->serviceOper = serviceOperAny;
				}
			}

			// Policy Enabled
			else if (strncmp(command->part(0), "policyEnabled_", 14) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sPolicy Enabled Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (filterPointer == 0)
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 14);
				}
				else if (filterPointer->id != atoi(command->part(0) + 14))
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 14);
				}

				if (strcmp(command->part(1), "1") == 0)
					filterPointer->enabled = true;
				else
					filterPointer->enabled = false;
			}

			// Logging Enabled
			else if (strncmp(command->part(0), "policyLog_", 10) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sPolicy Logging Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (filterPointer == 0)
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 10);
				}
				else if (filterPointer->id != atoi(command->part(0) + 10))
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 10);
				}

				if (strcmp(command->part(1), "1") == 0)
					filterPointer->log = true;
				else
					filterPointer->log = false;
			}

			// Fragmentation
			else if (strncmp(command->part(0), "policyFrag_", 11) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sPolicy Fragments Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (filterPointer == 0)
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 11);
				}
				else if (filterPointer->id != atoi(command->part(0) + 11))
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 11);
				}

				if (strcmp(command->part(1), "0") == 0)
					filterPointer->fragments = false;
				else
					filterPointer->fragments = true;
			}

			// Comments
			else if (strncmp(command->part(0), "policyComment_", 14) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sPolicy Comment Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (filterPointer == 0)
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 14);
				}
				else if (filterPointer->id != atoi(command->part(0) + 14))
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 14);
				}

				filterPointer->comment.assign(strstr(line, command->part(1)));
			}

			// All others...
			else
				device->lineNotProcessed(line);

			// Read a line from the config...
			fgetpos(device->inputFile, &filePosition);
			device->readLine(line, lineSize);

			// Split it up into parts...
			command->setConfigLine(line);
		}

		// Set file position back
		fsetpos(device->inputFile, &filePosition);
	}


	// Firewall Rules
	else if ((strncmp(command->part(0), "prefs_rule", 10) == 0) || (strncmp(command->part(0), "serviceNameInRule_", 18) == 0))
	{

		filterListPointer = getFilterList("Access Rules");
		filterListPointer->type = i18n("Access Rules");			// The filter list type name (used in the config report)
		filterListPointer->typeDescription = i18n("Access rules are used to filter the network traffic passing through *DEVICETYPE* devices. This section details those rules.");	// The filter list type description for the report (used in config report)
		filterListPointer->legacyType = false;					// Is the filter list a legacy type?
		filterListPointer->sourceOnly = false;					// The type of filter
		filterListPointer->loggingSupport = false;				// Does the filter list support logging
		filterListPointer->supportsTime = false;				// Filter support time (dest only)
		filterListPointer->supportsFragments = true;			// Filter support fragments (dest only)
		filterListPointer->supportsEstablished = false;			// Filter support established (dest only)
		filterListPointer->sourceServiceSupported = false;		// If source services are supported
		filterListPointer->disabledFilterSupport = true;		// Is it possible to disable filters?
		filterListPointer->filterCommentsSupported = true;		// Are filter comments supported
		filterListPointer->showProtocol = false;				// Show the protocol? (some devices use a configured service)
		filterListPointer->showFilterZones = true;				// Does the filter use filter-based zones (i.e. SonicWALL)
		filterPointer = addFilter(filterListPointer);

		objectListPointer = getOnlyObjectList(i18n("Service definition list"));

		while ((feof(device->inputFile) == 0) && ((strncmp(command->part(0), "prefs_rule", 10) == 0) || (strncmp(command->part(0), "ruleComment_", 12) == 0) || (strncmp(command->part(0), "serviceNameInRule_", 18) == 0)))
		{

			// Rule Action...
			if (strncmp(command->part(0), "prefs_ruleAction_", 17) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sRule Action Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (filterPointer == 0)
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 17);
				}
				else if (filterPointer->id != atoi(command->part(0) + 17))
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 17);
				}

				if (strcasecmp(command->part(1), "allow") == 0)
					filterPointer->action = allowAction;
				else if (strcasecmp(command->part(1), "deny") == 0)
					filterPointer->action = denyAction;
				else
					filterPointer->action = rejectAction;
			}

			// Service ID
			else if (strncmp(command->part(0), "prefs_ruleSvcID_", 16) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sRule Service Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (filterPointer == 0)
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 16);
				}
				else if (filterPointer->id != atoi(command->part(0) + 16))
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 16);
				}

				if ((objectListPointer != 0) && (command->parts > 1))
				{
					subObjectPointer = objectListPointer->object;
					tempCounter = 0;
					tempInt = atoi(command->part(1));
					while (subObjectPointer !=0)
					{
						if (tempCounter == tempInt)
						{
							objectPointer = addFilterObject(filterPointer, destinationService);
							objectPointer->name.assign(subObjectPointer->label);
							objectPointer->type = groupObject;
							objectPointer->serviceOper = serviceOperEqual;
							subObjectPointer = 0;
						}
						else
							subObjectPointer = subObjectPointer->next;
						tempCounter++;
					}
				}
				else
				{
					objectPointer = addFilterObject(filterPointer, destinationService);
					objectPointer->name.assign(i18n("any"));
					objectPointer->type = anyObject;
					objectPointer->serviceOper = serviceOperAny;
				}
			}

			// Source Ethernet
			else if (strncmp(command->part(0), "prefs_ruleSrcEnet_", 18) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sRule Source Ethernet Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (filterPointer == 0)
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 18);
				}
				else if (filterPointer->id != atoi(command->part(0) + 18))
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 18);
				}

				if (command->parts == 1)
					filterPointer->sourceZone.assign(i18n("Any"));
				else
				{
					tempInt = atoi(command->part(1));
					switch (tempInt)
					{
						case 0:
							filterPointer->sourceZone.assign(i18n("*ABBREV*LAN*-ABBREV*"));
							break;
						default:
							filterPointer->sourceZone.assign(command->part(1));
							break;
					}
					
				}
			}

			// Destination Ethernet
			else if (strncmp(command->part(0), "prefs_ruleDstEnet_", 18) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sRule Destination Ethernet Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (filterPointer == 0)
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 18);
				}
				else if (filterPointer->id != atoi(command->part(0) + 18))
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 18);
				}

				if (command->parts == 1)
					filterPointer->destZone.assign(i18n("Any"));
				else
				{
					tempInt = atoi(command->part(1));
					switch (tempInt)
					{
						case 0:
							filterPointer->destZone.assign(i18n("*ABBREV*LAN*-ABBREV*"));
							break;
						default:
							filterPointer->destZone.assign(command->part(1));
							break;
					}
				}
			}

			// Source Begin
			else if (strncmp(command->part(0), "prefs_ruleSrcBegin_", 19) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sRule Source Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (filterPointer == 0)
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 19);
				}
				else if (filterPointer->id != atoi(command->part(0) + 19))
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 19);
				}

				objectPointer = addFilterObject(filterPointer, source);
				if (command->parts > 1)
				{
					objectPointer->name.assign(strstr(line, command->part(1)));
					objectPointer->type = hostObject;
					objectPointer->serviceOper = serviceOperEqual;
				}
				else
				{
					objectPointer->name.assign(i18n("Any"));
					objectPointer->type = anyObject;
					objectPointer->serviceOper = serviceOperAny;
				}
			}

			// Source End
			else if (strncmp(command->part(0), "prefs_ruleSrcEnd_", 17) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sRule Source End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (filterPointer == 0)
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 17);
				}
				else if (filterPointer->id != atoi(command->part(0) + 17))
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 17);
				}

				if (objectPointer != 0)
				{
					objectPointer->netmask.assign(strstr(line, command->part(1)));
					if ((objectPointer->name.compare("0.0.0.0") == 0) && (objectPointer->netmask.compare("255.255.255.255") == 0))
					{
						objectPointer->type = anyObject;
						objectPointer->serviceOper = serviceOperAny;
					}
					else if (objectPointer->name.compare(objectPointer->netmask) != 0)
					{
						objectPointer->type = networkObject;
						objectPointer->serviceOper = serviceOperEqual;
					}
					else
					{
						objectPointer->type = hostObject;
						objectPointer->netmask.assign("255.255.255.255");
					}
				}
			}

			// Destination Begin
			else if (strncmp(command->part(0), "prefs_ruleDstBegin_", 19) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sRule Destination Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (filterPointer == 0)
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 19);
				}
				else if (filterPointer->id != atoi(command->part(0) + 19))
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 19);
				}

				objectPointer = addFilterObject(filterPointer, destination);
				if (command->parts > 1)
				{
					objectPointer->name.assign(strstr(line, command->part(1)));
					objectPointer->type = hostObject;
					objectPointer->serviceOper = serviceOperEqual;
				}
				else
				{
					objectPointer->name.assign(i18n("Any"));
					objectPointer->type = anyObject;
					objectPointer->serviceOper = serviceOperAny;
				}
			}

			// Destination End
			else if (strncmp(command->part(0), "prefs_ruleDstEnd_", 17) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sRule Destination End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (filterPointer == 0)
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 17);
				}
				else if (filterPointer->id != atoi(command->part(0) + 17))
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 17);
				}

				if (objectPointer != 0)
				{
					objectPointer->netmask.assign(strstr(line, command->part(1)));
					if ((objectPointer->name.compare("0.0.0.0") == 0) && (objectPointer->netmask.compare("255.255.255.255") == 0))
					{
						objectPointer->type = anyObject;
						objectPointer->serviceOper = serviceOperAny;
					}
					else if (objectPointer->name.compare(objectPointer->netmask) != 0)
					{
						objectPointer->type = networkObject;
						objectPointer->serviceOper = serviceOperEqual;
					}
					else
					{
						objectPointer->type = hostObject;
						objectPointer->netmask.assign("255.255.255.255");
					}
				}
			}

			// Rule Enabled
			else if (strncmp(command->part(0), "prefs_ruleEnabled_", 18) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sRule Enabled Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (filterPointer == 0)
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 18);
				}
				else if (filterPointer->id != atoi(command->part(0) + 18))
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 18);
				}

				if (strcmp(command->part(1), "1") == 0)
					filterPointer->enabled = true;
				else
					filterPointer->enabled = false;
			}

			// Fragmentation
			else if (strncmp(command->part(0), "prefs_ruleAllowFrags_", 21) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sRule Fragmentation Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (filterPointer == 0)
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 21);
				}
				else if (filterPointer->id != atoi(command->part(0) + 21))
				{
					filterPointer = addFilter(filterListPointer);
					filterPointer->id = atoi(command->part(0) + 21);
				}

				if (strcmp(command->part(1), "off") == 0)
					filterPointer->fragments = false;
				else
					filterPointer->fragments = true;
			}

			// All others...
			else
				device->lineNotProcessed(line);

			// Read a line from the config...
			fgetpos(device->inputFile, &filePosition);
			device->readLine(line, lineSize);

			// Split it up into parts...
			command->setConfigLine(line);
		}

		// Set file position back
		fsetpos(device->inputFile, &filePosition);
	}


	// Addresses
	else if (strncmp(command->part(0), "addrObj", 7) == 0)
	{

		objectListPointer = getObjectList(i18n("Global Address List"));
		objectListPointer->type = addressBookObject;
		objectListPointer->protocolSupported = false;
		objectListPointer->title = i18n("Address List");								// Pointer to the object name text
		objectListPointer->description = i18n("This section details the host and network definitions configured on *DEVICENAME*.");						// Pointer to the description text
		currentObject = 1000;

		while ((feof(device->inputFile) == 0) && (strncmp(command->part(0), "addrObj", 7) == 0))
		{

			// Name...
			if (strncmp(command->part(0), "addrObjIdDisp_", 14) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sAddress Object Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (currentObject != atoi(command->part(0) + 14))
				{
					objectPointer = addObject(objectListPointer);
					objectPointer->type = hostObject;
					objectPointer->serviceOper = serviceOperEqual;
					currentObject = atoi(command->part(0) + 14);
				}

				objectPointer->label.assign(strstr(line, command->part(1)));
			}

			// IP1...
			else if (strncmp(command->part(0), "addrObjIp1_", 11) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sObject Address Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (currentObject != atoi(command->part(0) + 11))
				{
					objectPointer = addObject(objectListPointer);
					objectPointer->type = hostObject;
					objectPointer->serviceOper = serviceOperEqual;
					currentObject = atoi(command->part(0) + 11);
				}

				objectPointer->name.assign(command->part(1));
			}

			// IP2...
			else if (strncmp(command->part(0), "addrObjIp2_", 11) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sObject Netmask Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (currentObject != atoi(command->part(0) + 11))
				{
					objectPointer = addObject(objectListPointer);
					objectPointer->type = hostObject;
					objectPointer->serviceOper = serviceOperEqual;
					currentObject = atoi(command->part(0) + 11);
				}

				objectPointer->netmask.assign(command->part(1));
				if (objectPointer->name.compare("0.0.0.0") == 0)
				{
					objectPointer->type = anyObject;
					objectPointer->serviceOper = serviceOperAny;
				}
				else if (objectPointer->netmask.compare("0.0.0.0") == 0)
				{
					objectPointer->type = hostObject;
					objectPointer->netmask.compare("255.255.255.255");
				}
				else if (objectPointer->netmask.compare("255.255.255.255") != 0)
					objectPointer->type = networkObject;
			}

			// Zone...
			else if (strncmp(command->part(0), "addrObjZone_", 12) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sObject Netmask Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (currentObject != atoi(command->part(0) + 12))
				{
					objectPointer = addObject(objectListPointer);
					objectPointer->type = hostObject;
					objectPointer->serviceOper = serviceOperEqual;
					currentObject = atoi(command->part(0) + 12);
				}

				if (strlen(command->part(1)) > 0)
				{
					tempListPointer = getObjectList(command->part(1));
					tempListPointer->type = addressBookObject;
					tempListPointer->protocolSupported = false;
					tempListPointer->title = i18n("Address List");								// Pointer to the object name text
					tempListPointer->description = i18n("This section details the host and network definitions configured on *DEVICENAME*.");	

					subObjectPointer = addObject(tempListPointer);
					copySourceToDestinationObjects(objectPointer, subObjectPointer);
					objectPointer->deleteMe = true;
					objectPointer = subObjectPointer;
				}
			}

			// All others...
			else
				device->lineNotProcessed(line);

			// Read a line from the config...
			fgetpos(device->inputFile, &filePosition);
			device->readLine(line, lineSize);

			// Split it up into parts...
			command->setConfigLine(line);
		}

		// Set file position back
		fsetpos(device->inputFile, &filePosition);
	}


	// Services
	else if ((strncmp(command->part(0), "svcObj", 6) == 0) || (strncmp(command->part(0), "prefs_svc", 9) == 0) || (strncmp(command->part(0), "serviceInternalName", 19) == 0))
	{

		objectListPointer = getObjectList(i18n("Service definition list"));
		objectListPointer->type = serviceListObject;
		objectListPointer->protocolSupported = true;
		objectListPointer->title = i18n("Service Definition List");								// Pointer to the object name text
		objectListPointer->description = i18n("This section details the services definitions configured on *DEVICENAME*.");						// Pointer to the description text
		currentObject = 1000;

		while ((feof(device->inputFile) == 0) && ((strncmp(command->part(0), "svcObj", 6) == 0) || (strncmp(command->part(0), "prefs_svc", 9) == 0) || (strncmp(command->part(0), "serviceInternalName", 19) == 0)))
		{

			// Service Port (start)...
			if (strncmp(command->part(0), "svcObjPort1_", 12) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sService Start Port Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (currentObject != atoi(command->part(0) + 12))
				{
					objectPointer = addObject(objectListPointer);
					objectPointer->type = serviceObject;
					objectPointer->serviceOper = serviceOperEqual;
					currentObject = atoi(command->part(0) + 12);
				}

				objectPointer->name.assign(command->part(1));
			}
			else if (strncmp(command->part(0), "prefs_svcPortNum_", 17) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sService Start Port Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (currentObject != atoi(command->part(0) + 17))
				{
					objectPointer = addObject(objectListPointer);
					objectPointer->type = serviceObject;
					objectPointer->serviceOper = serviceOperEqual;
					currentObject = atoi(command->part(0) + 17);
				}

				objectPointer->name.assign(command->part(1));
			}

			// Service Port (end)...
			else if (strncmp(command->part(0), "svcObjPort2_", 12) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sService End Port Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (currentObject != atoi(command->part(0) + 12))
				{
					objectPointer = addObject(objectListPointer);
					objectPointer->type = serviceObject;
					objectPointer->serviceOper = serviceOperEqual;
					currentObject = atoi(command->part(0) + 12);
				}

				objectPointer->netmask.assign(command->part(1));
				if (atoi(objectPointer->netmask.c_str()) < atoi(objectPointer->name.c_str()))
				{
					objectPointer->netmask.assign(objectPointer->name);
				}
				else if (objectPointer->netmask.compare(objectPointer->name) != 0)
					objectPointer->serviceOper = serviceOperRange;
				else if ((strcmp(objectPointer->netmask.c_str(), "65535") == 0) && (strcmp(objectPointer->name.c_str(), "65535") == 0))
					objectPointer->serviceOper = serviceOperAny;
			}
			else if (strncmp(command->part(0), "prefs_svcPortEnd_", 17) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sService Start End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (currentObject != atoi(command->part(0) + 17))
				{
					objectPointer = addObject(objectListPointer);
					objectPointer->type = serviceObject;
					objectPointer->serviceOper = serviceOperEqual;
					currentObject = atoi(command->part(0) + 17);
				}

				objectPointer->netmask.assign(command->part(1));
				if (atoi(objectPointer->netmask.c_str()) < atoi(objectPointer->name.c_str()))
				{
					objectPointer->netmask.assign(objectPointer->name);
				}
				else if (objectPointer->netmask.compare(objectPointer->name) != 0)
					objectPointer->serviceOper = serviceOperRange;
				else if ((strcmp(objectPointer->netmask.c_str(), "65535") == 0) && (strcmp(objectPointer->name.c_str(), "65535") == 0))
					objectPointer->serviceOper = serviceOperAny;
			}

			// Service Object Type...
			else if (strncmp(command->part(0), "svcObjType_", 11) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sService Object Type Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (currentObject != atoi(command->part(0) + 11))
				{
					objectPointer = addObject(objectListPointer);
					objectPointer->type = serviceObject;
					objectPointer->serviceOper = serviceOperEqual;
					currentObject = atoi(command->part(0) + 11);
				}

				if (strcmp(command->part(1), "2") == 0)
					objectPointer->deleteMe = true;
			}


			// Service IP Type...
			else if (strncmp(command->part(0), "svcObjIpType_", 13) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sService IP Type Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (currentObject != atoi(command->part(0) + 13))
				{
					objectPointer = addObject(objectListPointer);
					objectPointer->type = serviceObject;
					objectPointer->serviceOper = serviceOperEqual;
					currentObject = atoi(command->part(0) + 13);
				}

				subObjectPointer = addObject(objectPointer, protocol);
				if (strcmp(command->part(1), "0") == 0)
				{
					subObjectPointer->name.assign(i18n("Any"));
					subObjectPointer->type = anyObject;
					objectPointer->serviceOper = serviceOperAny;
				}
				else
				{
					tempString.assign(device->getProtocol(atoi(command->part(1))));
					if (tempString.empty())
						subObjectPointer->name.assign(command->part(1));
					else
						subObjectPointer->name.assign(tempString);
				}
			}
			else if (strncmp(command->part(0), "prefs_svcIPType_", 16) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sService IP Type Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (currentObject != atoi(command->part(0) + 16))
				{
					objectPointer = addObject(objectListPointer);
					objectPointer->type = serviceObject;
					objectPointer->serviceOper = serviceOperEqual;
					currentObject = atoi(command->part(0) + 16);
				}

				subObjectPointer = addObject(objectPointer, protocol);
				if (strcmp(command->part(1), "255") == 0)
				{
					subObjectPointer->name.assign(i18n("Any"));
					subObjectPointer->type = anyObject;
					objectPointer->serviceOper = serviceOperAny;
				}
				else
				{
					tempString.assign(device->getProtocol(atoi(command->part(1))));
					if (tempString.empty())
						subObjectPointer->name.assign(command->part(1));
					else
						subObjectPointer->name.assign(tempString);
				}
			}

			// Service Name...
			else if (strncmp(command->part(0), "svcObjId_", 9) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sService Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (currentObject != atoi(command->part(0) + 9))
				{
					objectPointer = addObject(objectListPointer);
					objectPointer->type = serviceObject;
					objectPointer->serviceOper = serviceOperEqual;
					currentObject = atoi(command->part(0) + 9);
				}

				objectPointer->label.assign(strstr(line, command->part(1)));
			}
			else if (strncmp(command->part(0), "prefs_svcName_", 14) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sService Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (currentObject != atoi(command->part(0) + 14))
				{
					objectPointer = addObject(objectListPointer);
					objectPointer->type = serviceObject;
					objectPointer->serviceOper = serviceOperEqual;
					currentObject = atoi(command->part(0) + 14);
				}

				objectPointer->label.assign(strstr(line, command->part(1)));
			}

			// All others...
			else
				device->lineNotProcessed(line);

			// Read a line from the config...
			fgetpos(device->inputFile, &filePosition);
			device->readLine(line, lineSize);

			// Split it up into parts...
			command->setConfigLine(line);
		}

		// Set file position back
		fsetpos(device->inputFile, &filePosition);
	}


	// Service Groups...
	else if ((strncmp(command->part(0), "so_atomToGrp_", 13) == 0) || (strncmp(command->part(0), "so_grpToGrp_", 12) == 0))
	{

		while ((strncmp(command->part(0), "so_atomToGrp_", 13) == 0) || (strncmp(command->part(0), "so_grpToGrp_", 12) == 0))
		{

			// Service to add to a group...
			if (strncmp(command->part(0), "so_atomToGrp_", 13) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sGroup Item Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				tempString.assign(strstr(line, command->part(1)));
			}

			// Service to add to a group...
			else if (strncmp(command->part(0), "so_grpToGrp_", 12) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sGroup Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				objectListPointer = getObjectList(strstr(line, command->part(1)));
				objectListPointer->type = serviceObject;
				objectListPointer->title = i18n("Service Group Definitions");								// Pointer to the object name text
				objectListPointer->description = i18n("It is possible on *DEVICETYPE* devices to group service definitions in order to ease administration. This section details those service groups.");						// Pointer to the description text

				objectPointer = addObject(objectListPointer);
				objectPointer->name.assign(tempString);
				objectPointer->type = groupObject;
				objectPointer->serviceOper = serviceOperEqual;
			}


			// All others...
			else
				device->lineNotProcessed(line);

			// Read a line from the config...
			fgetpos(device->inputFile, &filePosition);
			device->readLine(line, lineSize);

			// Split it up into parts...
			command->setConfigLine(line);
		}

		// Set file position back
		fsetpos(device->inputFile, &filePosition);
	}


	// address Groups...
	else if ((strncmp(command->part(0), "addro_grpToGrp_", 15) == 0) || (strncmp(command->part(0), "addro_atomToGrp_", 16) == 0))
	{

		while ((strncmp(command->part(0), "addro_grpToGrp_", 15) == 0) || (strncmp(command->part(0), "addro_atomToGrp_", 16) == 0))
		{

			// Service to add to a group...
			if (strncmp(command->part(0), "addro_atomToGrp_", 16) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sAddress Group Item Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				tempString.assign(strstr(line, command->part(1)));
			}

			// Service to add to a group...
			else if (strncmp(command->part(0), "addro_grpToGrp_", 15) == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sAddress Group Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				objectListPointer = getObjectList(strstr(line, command->part(1)));
				objectListPointer->type = hostObject;
				objectListPointer->title = i18n("Address Groups");								// Pointer to the object name text
				objectListPointer->description = i18n("It is possible on *DEVICETYPE* devices to group host and network definitions in order to ease administration. This section details those groups.");						// Pointer to the description text

				objectPointer = addObject(objectListPointer);
				objectPointer->name.assign(tempString);
				objectPointer->type = groupObject;
				objectPointer->serviceOper = serviceOperEqual;
			}


			// All others...
			else
				device->lineNotProcessed(line);

			// Read a line from the config...
			fgetpos(device->inputFile, &filePosition);
			device->readLine(line, lineSize);

			// Split it up into parts...
			command->setConfigLine(line);
		}

		// Set file position back
		fsetpos(device->inputFile, &filePosition);
	}


	// All others...
	else
		device->lineNotProcessed(line);

	return errorCode;
}


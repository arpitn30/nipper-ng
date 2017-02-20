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

#include "../device/common/configline.h"
#include "../globaldefs.h"
#include "device.h"
#include "filter.h"


<Template>Filter::<Template>Filter()
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
	defaultFilterActionSupported = false;					// Default action supported on the device
	allowByDefault = false;									// Allow by default?
	defaultActionIsAllow = false;							// Is the default action to allow
	logLevelsSupported = false;								// Are log Levels supported
	logOnlyDenySupported = false;							// Is only Deny rule logging supported
	noAccessWithoutFilters = false;							// Is access not granted if no filters are configured
	filterSupportsInstalled = false;						// If filtering supports installed (i.e. CheckPoint)
	filterSupportsThrough = false;							// If a filtering supports through (i.e. CheckPoint)
	rejectRulesSupported = false;							// If reject rules are supported
	bypassRulesSupported = false;							// If bypass rules are supported
	defaultRulesSupported = false;							// If default rules are supported
	ruleListsAreAssigned = false;							// Rule lists are assigned to specific elements
	allowName = i18n("Permit");								// The name given to an allowed filter
	denyName = i18n("Deny");								// The name given to a denied filter
	rejectName = i18n("Reject");							// The name given to a rejected filter
	filterConfigTitle = i18n("*ABBREV*ACL*-ABBREV* Configuration");			// The Title for the configuration report section
	filterConfigText = i18n("");							// The device specific configuration report section text
	filterConfigText2 = i18n("");							// The device specific configuration report section text2
	useFilterID = false;									// Use the filter ID to identify a filter (otherwise a line no. is used)
	filterIDTitle = i18n("Line");							// The title for the filter ID/line no. table column
	filterListName = i18n("*ABBREV*ACL*-ABBREV*");			// The name of the filter list, for use in text paragraphs
	filterListNameTitle = i18n("*ABBREV*ACL*-ABBREV*");		// The name of the filter list, for use in titles
	filterListNamePlaural = i18n("*ABBREV*ACLs*-ABBREV*");	// The name of the filter list, for use in text paragraphs
	filterTitle = i18n("*ABBREV*ACE*-ABBREV*");				// The name of a filter, for use in titles
	filterTitlePlaural = i18n("*ABBREV*ACEs*-ABBREV*");		// The name of a filter, for use in titles
	filterName = i18n("*ABBREV*ACE*-ABBREV*");				// The name of a filter, for use use in text paragraph
	filterNamePlaural = i18n("*ABBREV*ACEs*-ABBREV*");		// The name of a filter, for use use in text paragraph

	// Issue titles...
	allowAndNotLogIssue = i18n("Not All Permit *ABBREV*ACEs*-ABBREV* Log Access");	// The title text for the "All Allow Rules Do Not Log" issue
	allowAndNotLogTable = i18n("Permit *ABBREV*ACEs*-ABBREV* that do not log");		// The table title text for the "All Allow Rules Do Not Log" issue
	allowAndNotLogConcl = i18n("not all permit *ABBREV*ACEs*-ABBREV* log access");	// The conclusions text for the "All Allow Rules Do Not Log" issue
	allowAndNotLogReco = i18n("Configure logging for all *ABBREV*ACEs*-ABBREV*");	// The recommendations text for "All Allow Rules Do Not Log" (and deny) issue
	denyAndNotLogIssue = i18n("Not All Deny *ABBREV*ACEs*-ABBREV* Log Access");		// The title text for the "All Allow Rules Do Not Log" issue
	denyAndNotLogTable = i18n("Deny *ABBREV*ACEs*-ABBREV* that do not log");		// The table title text for the "All Allow Rules Do Not Log" issue
	denyAndNotLogConcl = i18n("not all deny *ABBREV*ACEs*-ABBREV* log access");		// The conclusions text for the "All Allow Rules Do Not Log" issue
	configRuleLogging = i18n("");								// The text describing how to configure logging for filter rules
	noFilteringIssue = i18n("No *ABBREV*ACLs*-ABBREV* Were Configured");	// The title text for the "No filtering" issue
	noFilteringRec = i18n("Configure *ABBREV*ACLs*-ABBREV* to restict access");		// The title text for the "No filtering" recommendation
	noFilteringCon = i18n("no *ABBREV*ACLs*-ABBREV* were configured");		// The title text for the "No filtering" conclusion
	legacyIssueFinding = i18n("");								// The finding for the legacy issue
	legacyIssueImpact = i18n("");								// The impact for the legacy issue
	legacyIssueEase = i18n("");									// The ease for the legacy issue
	legacyIssueRec = i18n("");									// The recommendation for the legacy issue
	allowAnythingTable = i18n("*ABBREV*ACEs*-ABBREV* permit any access");		// The allow anything table title text
	allowWeakTable = i18n("*ABBREV*ACEs*-ABBREV* provide weak filtering");		// Weak source/service/destination/service table title text
	allowAnyAnyAnyTable = i18n("*ABBREV*ACEs*-ABBREV* permit any host to access any destination and service");			// The allow any source, destination and service table title text
	allowWeakWeakWeakTable = i18n("*ABBREV*ACEs*-ABBREV* provide weak filtering of source, destination and service");	// The allow weak source, destination and service table title text
	allowAnyServiceAnyTable = i18n("*ABBREV*ACEs*-ABBREV* allow any source port to any destination and service");		// The allow any source port, destination and service table title text
	allowWeakServiceAnyTable = i18n("*ABBREV*ACEs*-ABBREV* provide weak filtering of source port to destination and service");	// The allow weak source, destination and service table title text
	allowAnyAnyTable = i18n("*ABBREV*ACEs*-ABBREV* permit any source to any destination");					// The allow any source, destination table title text
	allowAnyAnyServiceTable = i18n("*ABBREV*ACEs*-ABBREV* permit any source to any destination service");	// The allow any source, destination service table title text
	allowAnyDestServiceTable = i18n("*ABBREV*ACEs*-ABBREV* permit any destination and service");			// The allow any destination and service table title text
	allowAnyPortDestTable = i18n("*ABBREV*ACEs*-ABBREV* permit any source port to any destination address");			// The allow any source port to any destination table title text
	allowAnyPortServiceTable = i18n("*ABBREV*ACEs*-ABBREV* permit any source port to any destination service");			// The allow any source port to any dest service table title text
	allowWeakWeakTable = i18n("*ABBREV*ACEs*-ABBREV* permit weak filtering of source and destination addresses");		// The allow weak source, destination addresses
	allowWeakWeakServiceTable = i18n("*ABBREV*ACEs*-ABBREV* permit weak source addresses and destination services");	// The allow weak source, destination service table title text
	allowDestAndServiceTable = i18n("*ABBREV*ACEs*-ABBREV* permit weak destination addresses and services");// The allow weak destination and service table title text
	allowWeakPortDestTable = i18n("*ABBREV*ACEs*-ABBREV* permit weak source ports and destination");		// The allow weak source port to Destination table title text
	allowWeakPortServiceTable = i18n("*ABBREV*ACEs*-ABBREV* permit weak source ports and destination services");		// The allow weak source port to service table title text
	allowAnySourceTable = i18n("*ABBREV*ACEs*-ABBREV* permit from any source address");						// The allow any source address table title text
	allowNetSourceTable = i18n("*ABBREV*ACEs*-ABBREV* permit from a network source address");				// The allow a network source address table title text
	allowAnyPortTable = i18n("*ABBREV*ACEs*-ABBREV* permit from any source port");							// The allow any source port table title text
	allowRangePortTable = i18n("*ABBREV*ACEs*-ABBREV* permit from a source port range");					// The allow range source port table title text
	allowAnyDestTable = i18n("*ABBREV*ACEs*-ABBREV* permit to any destination");							// The allow any destination table title text
	allowNetDestTable = i18n("*ABBREV*ACEs*-ABBREV* permit to a network destination");						// The allow a network destination table title text
	allowToAnyDestServiceTable = i18n("*ABBREV*ACEs*-ABBREV* permit to any destination service");			// The allow any destination service table title text
	allowToNetDestServiceTable = i18n("*ABBREV*ACEs*-ABBREV* permit to a destination service range");		// The allow a destination service range table title text
	bypassContentFilterCon = i18n("*ABBREV*ACEs*-ABBREV* were configured that bypass the content filtering");			// Bypass filter conclusion text
	bypassContentFilterRec = i18n("Connfigure *ABBREV*ACEs*-ABBREV* that do not bypass the content filtering");	// Bypass filter recommendation text
	defaultFilterCon = i18n("*ABBREV*ACEs*-ABBREV* were configured that default to the ports filtering action");		// Default filter conclusion text
	defaultFilterRec = i18n("Configure *ABBREV*ACEs*-ABBREV* that do not default to the ports filtering action");		// Default filter recommendation text
	rejectSecurityIssueTitle = i18n("Reject *ABBREV*ACEs*-ABBREV* Were Configured");							// Reject filter title text
	securityRejectTextCon = i18n("*ABBREV*ACEs*-ABBREV* were configured that reject network traffic");			// Reject filter conclusion text
	securityRejectTextRec = i18n("Configure *ABBREV*ACEs*-ABBREV* to deny rather than reject network traffic");	// Reject filter recommendation text
	clearTextServiceCon = i18n("*ABBREV*ACEs*-ABBREV* were configured that permit access to clear text protocol services");		// Clear Text Service conclusions text
	clearTextServiceRec = i18n("Configure *ABBREV*ACEs*-ABBREV* to deny access to any clear text protocol services");			// Clear Text Service recommendations text2
	configureFilterListRecIssueText = i18n("");												// The text and commands to configure a filter list
	configureFilterRecIssueText = i18n("");													// The text and commands to configure a filter
	unnecessaryServiceCon = i18n("*ABBREV*ACEs*-ABBREV* were configured that permit access to potentially unnecessary services");			// Unnecessary Service conclusions text
	unnecessaryServiceRec = i18n("Configure *ABBREV*ACEs*-ABBREV* to deny access to any unnecessary services");	// Unnecessary Service recommendations text2
	filtersWithNoCommentsTitle = i18n("Not All *ABBREV*ACEs*-ABBREV* Include Comments");	// Filters with no comments title text
	noFilterCommentsCon = i18n("not all *ABBREV*ACEs*-ABBREV* include comment text indicating their purpose");	// The no comments conclusion text
	noFilterCommentsRec = i18n("Configure comment text for all *ABBREV*ACEs*-ABBREV*");		// The no comments recommendation text
	configureFilterCommentText = i18n("");													// The text and commands to configure a filters comment text
	disabledFiltersTitle = i18n("Disabled *ABBREV*ACEs*-ABBREV* Were Configured");			// The disabled filter issues title text
	removeFilterText = i18n("");															// The commands and text to delete a filter
	disabledFilterCon = i18n("disabled *ABBREV*ACEs*-ABBREV* were configured");				// The disabled filter conclusion text
	disabledFilterRec = i18n("Remove all disabled *ABBREV*ACEs*-ABBREV*");					// The disabled filter recommendation text
	defaultActionIssueTitle = i18n("The Default Network Filtering Action Permits Access");	// The default filter action issue title
	defaultActionIssueCon = i18n("the default *ABBREV*ACL*-ABBREV* action was configured to permit access when a *ABBREV*ACE*-ABBREV* does not match");	// The default filter action conclusion text
	defaultActionIssueRec = i18n("Set the default *ABBREV*ACL*-ABBREV* action to deny network traffic");		// The default filter action recommendation text
	configureDefaultActionText = i18n("");													// The text and commands to configure the default action
	unusedFiltersIssueTitle = i18n("Unused *ABBREV*ACEs*-ABBREV* Were Configured At The *ABBREV*ACLs*-ABBREV* End");	// Unused filters at the end of the filter list title
	unusedFiltersIssueCon = i18n("unused *ABBREV*ACEs*-ABBREV* were configured at the end of the *ABBREV*ACLs*-ABBREV*");		// Unused filters issue conclusions text
	unusedFiltersIssueRec = i18n("Remove all unused *ABBREV*ACEs*-ABBREV*");				// Unused filters issue recommendation text
	denyAllLogIssueTitle = i18n("*ABBREV*ACL*-ABBREV* Does Not End with Deny All And Log");	// Deny All And Log Issue title
	denyAllLogConfigure = i18n("");															// The text and commands to add a deny all and log line
	denyAllLogIssueCon = i18n("not all *ABBREV*ACLs*-ABBREV* end with a deny all and log ");		// The deny all and log conclusions text
	denyAllLogIssueRec = i18n("Configure a deny all and log *ABBREV*ACE*-ABBREV* as the last *ABBREV*ACE*-ABBREV* in each *ABBREV*ACL*-ABBREV*");			// The deny all and log recommendations text
	contradictIssueTitle = i18n("Contradicting *ABBREV*ACEs*-ABBREV* Were Configured");		// The contradict issue title
	contradictIssueTable = i18n("contradictions of *ABBREV*ACE*-ABBREV*");					// The contradict table issue title
	contradictIssueCon = i18n("*ABBREV*ACEs*-ABBREV* were configured that contradict other *ABBREV*ACEs*-ABBREV*");				// The contradict issue conclusion
	contradictIssueRec = i18n("Reconfigure the *ABBREV*ACEs*-ABBREV* so they do not contradict other *ABBREV*ACE*-ABBREV*");	// The contradict issue recommendation
	duplicateIssueTitle = i18n("Duplicate *ABBREV*ACEs*-ABBREV* Were Configured");			// The duplicate/overlapping issue title
	duplicateIssueTable = i18n("duplicates of *ABBREV*ACE*-ABBREV*");										// The duplicate/overlapping issue title
	duplicateIssueCon = i18n("*ABBREV*ACEs*-ABBREV* were configured that duplicate the configuration of other *ABBREV*ACEs*-ABBREV*");	// The duplicate/overlapping issue title
	duplicateIssueRec = i18n("Reconfigure the *ABBREV*ACEs*-ABBREV* so that the rules do not duplicate other *ABBREV*ACEs*-ABBREV*");						// The duplicate/overlapping issue title
}


<Template>Filter::~<Template>Filter()
{
}


int <Template>Filter::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	return 0;
}


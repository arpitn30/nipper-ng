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

#include "../../globaldefs.h"
#include "../device.h"
#include "filter.h"


Filter::Filter()
{
	filterList = 0;
	netObjectList = 0;										// NetObjects
	containsClearText = false;
	containsDangerous = false;
	containsUnnecessary = false;

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

	// Filtering Issue Lists...
	anyAnyAnyAny = 0;			// GEN.FILTAAAA.1   Access Allowed From Any Source And Service To Any Destination And Service
	weakWeakWeakWeak = 0;		// GEN.FILTWAAA.1   Weak Access Allowed From Source And Service To Weak Destination And Service
	anyAnyAny = 0;				// GEN.FILTAAAN.1   Access Allowed From Any Source To Any Destination And Service
	weakWeakWeak = 0;			// GEN.FILTWAAN.1   Weak Access Allowed From Source To Weak Destination And Service
	anyServiceAnyAny = 0;		// GEN.FILTSAAN.1   Access Allowed From Any Source Service to Any Destination And Service
	weakServiceAnyAny = 0;		// GEN.FILTWSAN.1   Access Allowed From Weak Source Service to Weak Destination And Service
	anyAny = 0;					// GEN.FILTANAN.1   Access Allowed From Any Source To Any Destination
	anyAnyDestService = 0;		// GEN.FILTANAS.1   Access Allowed From Any Source To Any Destination Service
	destHostAndService = 0;		// GEN.FILTANDS.1   Access Allowed To Any Destination Host And Service
	anyServiceAny = 0;			// GEN.FILTSNAN.1   Access Allowed From Any source Service To Any Destination
	anyServiceAnyService = 0;	// GEN.FILTASDS.1   Access Allowed From Any Source Service to Any Destination Service
	weakWeak = 0;				// GEN.FILTWNAN.1   Weak Access Allowed From Weak Source To Weak Destination
	weakDestService = 0;		// GEN.FILTWNAS.1   Weak Access Allowed From Weak Source To Weak Destination Service
	weakDestHostAndService = 0;	// GEN.FILTWNDS.1   Weak Access Allowed To Weak Destination Host And Service
	weakServiceAny = 0;			// GEN.FILTWSNN.1   Weak Access Allowed From Weak source Service To Weak Destination
	weakServiceAnyService = 0;	// GEN.FILTWSDS.1   Weak Access Allowed From Weak Source Service to Weak Destination Service
	anySourceHost = 0;			// GEN.FILTANSO.1   Access Allowed From Any Source Host
	netSourceHost = 0;			// GEN.FILTNESO.1   Access Allowed From A Network Source
	anySourceService = 0;		// GEN.FILTANSS.1   Access Allowed From Any Source Service
	rangeSourceService = 0;		// GEN.FILTRASS.1   Access Allowed From A Range Of Source Services
	anyDestination = 0;			// GEN.FILTANDE.1   Access Allowed To Any Destination Host
	netDestination = 0;			// GEN.FILTNEDE.1   Access Allowed To A Network Destination
	anyDestService = 0;			// GEN.FILTANSE.1   Access Allowed To Any Destination Service
	rangeDestService = 0;		// GEN.FILTRDSS.1   Access Allowed To A Range Of Destination Services
	allowedLogging = 0;			// GEN.FILTALLO.1   Allowed Rules Do Not Log
	deniedLogging = 0;			// GEN.FILTDELO.1   Denied Rules Do Not Log
	denyAllAndLog = 0;			// GEN.FILTDAAL.1   Filter List Does Not End With A Deny All And Log
	filterRejects = 0;			// GEN.FILTREJE.1   Filter Rule Rejects
	filterBypasses = 0;			// GEN.FILTBYPA.1   Filter Rule Bypasses Filtering
	filterDefault = 0;			// GEN.FILTDEFT.1   Filter Uses The Default Action
	filterNoComment = 0;		// GEN.FILTCOMM.1   Filter Rule Is Not Commented
	filterDisabled = 0;			// GEN.FILTDISA.1   Disabled Filter Rules
	filterClearText = 0;		// GEN.FILTCLEA.1   Access To Clear Text Protocol Services Allowed
	filterDangerous = 0;		// GEN.FILTDANG.1   Access To Dangerous Protocol Services Allowed
	filterUnnecessary = 0;		// GEN.FILTUNNE.1   Access To Unnecessary Protocol Services Allowed
	weakLoggingLevel = 0;		// GEN.FILTLGLE.1   Weak Filter Logging Levels
	legacyLists = 0;			// GEN.FILTLEGA.1   Legacy Filtering Configuration
	filterUnused = 0;			// GEN.FILTUNUS.1   Unused Filter Rules
	filterDuplicate = 0;		// GEN.FILTDUPL.1   Duplicate Filter Rules Are Configured
	filterContradict = 0;		// GEN.FILTCONT.1   Contradict Filter Rules Are Configured
}


Filter::~Filter()
{
	// Variables...
	filterListConfig *filterListPointer = 0;
	filterConfig *filterPointer = 0;
	netObjectListConfig *objectListPointer = 0;
	filterIssueConfig *filterIssuePointer = 0;
	filterListIssueConfig *filterListIssuePointer = 0;
	filterDuplConfig *filterDuplPointer = 0;

	// Delete Issue lists
	while (denyAllAndLog != 0)
	{
		filterListIssuePointer = denyAllAndLog->next;
		delete denyAllAndLog;
		denyAllAndLog = filterListIssuePointer;
	}
	while (legacyLists != 0)
	{
		filterListIssuePointer = legacyLists->next;
		delete legacyLists;
		legacyLists = filterListIssuePointer;
	}
	while (filterDuplicate != 0)
	{
		if (filterDuplicate->duplicates != 0)
		{
			if (filterDuplicate->duplicates->filter != 0)
				delete filterDuplicate->duplicates->filter;
		}
		while (filterDuplicate->duplicates != 0)
		{
			filterIssuePointer = filterDuplicate->duplicates->next;
			delete filterDuplicate->duplicates;
			filterDuplicate->duplicates = filterIssuePointer;
		}
		filterDuplPointer = filterDuplicate->next;
		delete filterDuplicate;
		filterDuplicate = filterDuplPointer;
	}
	while (filterContradict != 0)
	{
		if (filterContradict->duplicates != 0)
		{
			if (filterContradict->duplicates->filter != 0)
				delete filterContradict->duplicates->filter;
		}
		while (filterContradict->duplicates != 0)
		{
			filterIssuePointer = filterContradict->duplicates->next;
			delete filterContradict->duplicates;
			filterContradict->duplicates = filterIssuePointer;
		}
		filterDuplPointer = filterContradict->next;
		delete filterContradict;
		filterContradict = filterDuplPointer;
	}
	while (anyAnyAnyAny != 0)
	{
		filterIssuePointer = anyAnyAnyAny->next;
		delete anyAnyAnyAny;
		anyAnyAnyAny = filterIssuePointer;
	}
	while (weakWeakWeakWeak != 0)
	{
		filterIssuePointer = weakWeakWeakWeak->next;
		delete weakWeakWeakWeak;
		weakWeakWeakWeak = filterIssuePointer;
	}
	while (anyAnyAny != 0)
	{
		filterIssuePointer = anyAnyAny->next;
		delete anyAnyAny;
		anyAnyAny = filterIssuePointer;
	}
	while (weakWeakWeak != 0)
	{
		filterIssuePointer = weakWeakWeak->next;
		delete weakWeakWeak;
		weakWeakWeak = filterIssuePointer;
	}
	while (anyServiceAnyAny != 0)
	{
		filterIssuePointer = anyServiceAnyAny->next;
		delete anyServiceAnyAny;
		anyServiceAnyAny = filterIssuePointer;
	}
	while (weakServiceAnyAny != 0)
	{
		filterIssuePointer = weakServiceAnyAny->next;
		delete weakServiceAnyAny;
		weakServiceAnyAny = filterIssuePointer;
	}
	while (anyAny != 0)
	{
		filterIssuePointer = anyAny->next;
		delete anyAny;
		anyAny = filterIssuePointer;
	}
	while (anyAnyDestService != 0)
	{
		filterIssuePointer = anyAnyDestService->next;
		delete anyAnyDestService;
		anyAnyDestService = filterIssuePointer;
	}
	while (destHostAndService != 0)
	{
		filterIssuePointer = destHostAndService->next;
		delete destHostAndService;
		destHostAndService = filterIssuePointer;
	}
	while (anyServiceAny != 0)
	{
		filterIssuePointer = anyServiceAny->next;
		delete anyServiceAny;
		anyServiceAny = filterIssuePointer;
	}
	while (anyServiceAnyService != 0)
	{
		filterIssuePointer = anyServiceAnyService->next;
		delete anyServiceAnyService;
		anyServiceAnyService = filterIssuePointer;
	}
	while (weakWeak != 0)
	{
		filterIssuePointer = weakWeak->next;
		delete weakWeak;
		weakWeak = filterIssuePointer;
	}
	while (weakDestService != 0)
	{
		filterIssuePointer = weakDestService->next;
		delete weakDestService;
		weakDestService = filterIssuePointer;
	}
	while (weakDestHostAndService != 0)
	{
		filterIssuePointer = weakDestHostAndService->next;
		delete weakDestHostAndService;
		weakDestHostAndService = filterIssuePointer;
	}
	while (weakServiceAny != 0)
	{
		filterIssuePointer = weakServiceAny->next;
		delete weakServiceAny;
		weakServiceAny = filterIssuePointer;
	}
	while (weakServiceAnyService != 0)
	{
		filterIssuePointer = weakServiceAnyService->next;
		delete weakServiceAnyService;
		weakServiceAnyService = filterIssuePointer;
	}
	while (anySourceHost != 0)
	{
		filterIssuePointer = anySourceHost->next;
		delete anySourceHost;
		anySourceHost = filterIssuePointer;
	}
	while (netSourceHost != 0)
	{
		filterIssuePointer = netSourceHost->next;
		delete netSourceHost;
		netSourceHost = filterIssuePointer;
	}
	while (anySourceService != 0)
	{
		filterIssuePointer = anySourceService->next;
		delete anySourceService;
		anySourceService = filterIssuePointer;
	}
	while (rangeSourceService != 0)
	{
		filterIssuePointer = rangeSourceService->next;
		delete rangeSourceService;
		rangeSourceService = filterIssuePointer;
	}
	while (anyDestination != 0)
	{
		filterIssuePointer = anyDestination->next;
		delete anyDestination;
		anyDestination = filterIssuePointer;
	}
	while (netDestination != 0)
	{
		filterIssuePointer = netDestination->next;
		delete netDestination;
		netDestination = filterIssuePointer;
	}
	while (anyDestService != 0)
	{
		filterIssuePointer = anyDestService->next;
		delete anyDestService;
		anyDestService = filterIssuePointer;
	}
	while (rangeDestService != 0)
	{
		filterIssuePointer = rangeDestService->next;
		delete rangeDestService;
		rangeDestService = filterIssuePointer;
	}
	while (allowedLogging != 0)
	{
		filterIssuePointer = allowedLogging->next;
		delete allowedLogging;
		allowedLogging = filterIssuePointer;
	}
	while (deniedLogging != 0)
	{
		filterIssuePointer = deniedLogging->next;
		delete deniedLogging;
		deniedLogging = filterIssuePointer;
	}
	while (filterRejects != 0)
	{
		filterIssuePointer = filterRejects->next;
		delete filterRejects;
		filterRejects = filterIssuePointer;
	}
	while (filterBypasses != 0)
	{
		filterIssuePointer = filterBypasses->next;
		delete filterBypasses;
		filterBypasses = filterIssuePointer;
	}
	while (filterDefault != 0)
	{
		filterIssuePointer = filterDefault->next;
		delete filterDefault;
		filterDefault = filterIssuePointer;
	}
	while (filterNoComment != 0)
	{
		filterIssuePointer = filterNoComment->next;
		delete filterNoComment;
		filterNoComment = filterIssuePointer;
	}
	while (filterDisabled != 0)
	{
		filterIssuePointer = filterDisabled->next;
		delete filterDisabled;
		filterDisabled = filterIssuePointer;
	}
	while (filterClearText != 0)
	{
		filterIssuePointer = filterClearText->next;
		delete filterClearText;
		filterClearText = filterIssuePointer;
	}
	while (filterDangerous != 0)
	{
		filterIssuePointer = filterDangerous->next;
		delete filterDangerous;
		filterDangerous = filterIssuePointer;
	}
	while (filterUnnecessary != 0)
	{
		filterIssuePointer = filterUnnecessary->next;
		delete filterUnnecessary;
		filterUnnecessary = filterIssuePointer;
	}
	while (weakLoggingLevel != 0)
	{
		filterIssuePointer = weakLoggingLevel->next;
		delete weakLoggingLevel;
		weakLoggingLevel = filterIssuePointer;
	}
	while (filterUnused != 0)
	{
		filterIssuePointer = filterUnused->next;
		delete filterUnused;
		filterUnused = filterIssuePointer;
	}

	// Delete objects...
	while (netObjectList != 0)
	{
		if (netObjectList->object != 0)
			deleteFilterObject(netObjectList->object);
		objectListPointer = netObjectList->next = 0;
		delete netObjectList;
		netObjectList = objectListPointer;
	}

	// Delete filters...
	while (filterList != 0)
	{
		while (filterList->filter != 0)
		{
			if (filterList->filter->protocol != 0)
				deleteFilterObject(filterList->filter->protocol);

			if (filterList->filter->source != 0)
				deleteFilterObject(filterList->filter->source);

			if (filterList->filter->sourceService != 0)
				deleteFilterObject(filterList->filter->sourceService);

			if (filterList->filter->destination != 0)
				deleteFilterObject(filterList->filter->destination);

			if (filterList->filter->destinationService != 0)
				deleteFilterObject(filterList->filter->destinationService);

			if (filterList->filter->through != 0)
				deleteFilterObject(filterList->filter->through);

			if (filterList->filter->install != 0)
				deleteFilterObject(filterList->filter->install);

			if (filterList->filter->time != 0)
				deleteFilterObject(filterList->filter->time);

			filterPointer = filterList->filter->next;
			delete filterList->filter;
			filterList->filter = filterPointer;
		}
		filterListPointer = filterList->next;
		delete filterList;
		filterList = filterListPointer;
	}
}


int Filter::generateConfigReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	int errorCode = 0;

	if ((filterList != 0) || (netObjectList != 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s Filter Settings\n", device->config->COL_BLUE, device->config->COL_RESET);

		// Create Config Report Section...
		configReportPointer = device->getConfigSection("CONFIG-FILTER");
		configReportPointer->title.assign(filterConfigTitle);
		if (strlen(filterConfigText) > 0)
		{
			paragraphPointer = device->addParagraph(configReportPointer);
			paragraphPointer->paragraph.assign(filterConfigText);
		}
		if (strlen(filterConfigText2) > 0)
		{
			paragraphPointer = device->addParagraph(configReportPointer);
			paragraphPointer->paragraph.assign(filterConfigText2);
		}
		paragraphPointer = device->addParagraph(configReportPointer);
		device->addString(paragraphPointer, filterListName);
		paragraphPointer->paragraph.assign(i18n("This section describes the *DATA* configuration."));

		if (filterList != 0)
		{
			errorCode = generateConfigFilterReport(device);
			if (errorCode != 0)
				return errorCode;
		}

		if (netObjectList != 0)
			errorCode = generateConfigObjectReport(device);
	}

	return errorCode;
}


int Filter::deleteFilterObject(filterObjectConfig *filterObjectPointer)
{
	if (filterObjectPointer == 0)
		return 0;

	// Delete protocol
	if (filterObjectPointer->protocol != 0)
		deleteFilterObject(filterObjectPointer->protocol);

	// Delete source port
	if (filterObjectPointer->sourcePort != 0)
		deleteFilterObject(filterObjectPointer->sourcePort);

	// Delete destination port
	if (filterObjectPointer->destinationPort != 0)
		deleteFilterObject(filterObjectPointer->destinationPort);

	// Delete interfaces port
	if (filterObjectPointer->interfaces != 0)
		deleteFilterObject(filterObjectPointer->interfaces);

	// Delete members port
	if (filterObjectPointer->members != 0)
		deleteFilterObject(filterObjectPointer->members);

	// Delete next...
	if (filterObjectPointer->next != 0)
		deleteFilterObject(filterObjectPointer->next);

	// Delete itself...
	delete filterObjectPointer;

	return 0;
}


int Filter::processDefaults(Device *device)
{
	// Variables...
	filterListConfig *filterListPointer = 0;
	filterListConfig *previousFilterListPointer = 0;
	filterConfig *filterPointer = 0;
	filterConfig *previousFilterPointer = 0;
	filterObjectConfig *filterObjectPointer = 0;
	filterObjectConfig *objectPreviousPointer = 0;
	netObjectListConfig *objectListPointer = 0;

	// Delete all objects marked to be deleted.
	objectListPointer = netObjectList;
	while (objectListPointer != 0)
	{
		objectPreviousPointer = 0;
		filterObjectPointer = objectListPointer->object;
		while (filterObjectPointer != 0)
		{
			if (filterObjectPointer->deleteMe == true)
			{
				if (objectPreviousPointer == 0)
				{
					if (filterObjectPointer->protocol != 0)
						deleteFilterObject(filterObjectPointer->protocol);

					if (filterObjectPointer->sourcePort != 0)
						deleteFilterObject(filterObjectPointer->sourcePort);

					if (filterObjectPointer->destinationPort != 0)
						deleteFilterObject(filterObjectPointer->destinationPort);

					objectListPointer->object = filterObjectPointer->next;
					delete filterObjectPointer;
					filterObjectPointer = objectListPointer->object;
				}
				else
				{
					if (filterObjectPointer->protocol != 0)
						deleteFilterObject(filterObjectPointer->protocol);

					if (filterObjectPointer->sourcePort != 0)
						deleteFilterObject(filterObjectPointer->sourcePort);

					if (filterObjectPointer->destinationPort != 0)
						deleteFilterObject(filterObjectPointer->destinationPort);

					objectPreviousPointer->next = filterObjectPointer->next;
					delete filterObjectPointer;
					filterObjectPointer = objectPreviousPointer->next;
				}
			}
			else
			{
				objectPreviousPointer = filterObjectPointer;
				filterObjectPointer = filterObjectPointer->next;
			}
		}
		objectListPointer = objectListPointer->next;
	}

	// Delete any filters that are marked to be deleted (and any filter lists that do not have any filters...
	filterListPointer = filterList;
	previousFilterListPointer = 0;
	while (filterListPointer != 0)
	{

		previousFilterPointer = 0;
		filterPointer = filterListPointer->filter;
		while (filterPointer != 0)
		{
			if (filterPointer->deleteMe == true)
			{

				if (filterPointer->protocol != 0)
					deleteFilterObject(filterPointer->protocol);

				if (filterPointer->source != 0)
					deleteFilterObject(filterPointer->source);

				if (filterPointer->sourceService != 0)
					deleteFilterObject(filterPointer->sourceService);

				if (filterPointer->destination != 0)
					deleteFilterObject(filterPointer->destination);

				if (filterPointer->destinationService != 0)
					deleteFilterObject(filterPointer->destinationService);

				if (filterPointer->through != 0)
					deleteFilterObject(filterPointer->through);

				if (filterPointer->install != 0)
					deleteFilterObject(filterPointer->install);

				if (filterPointer->time != 0)
					deleteFilterObject(filterPointer->time);

				if (previousFilterPointer == 0)
				{
					filterListPointer->filter = filterPointer->next;
					delete filterPointer;
					filterPointer = filterListPointer->filter;
				}
				else
				{
					previousFilterPointer->next = filterPointer->next;
					delete filterPointer;
					filterPointer = previousFilterPointer->next;
				}
			}
			else
			{
				previousFilterPointer = filterPointer;
				filterPointer = filterPointer->next;
			}
		}

		if (filterListPointer->filter == 0)
		{
			if (previousFilterListPointer == 0)
			{
				filterList = filterListPointer->next;
				delete filterListPointer;
				filterListPointer = filterList;
			}
			else
			{
				previousFilterListPointer->next = filterListPointer->next;
				delete filterListPointer;
				filterListPointer = previousFilterListPointer->next;
			}
		}
		else
		{
			previousFilterListPointer = filterListPointer;
			filterListPointer = filterListPointer->next;
		}
	}

	// Add "Any" objects to all those filters that dont have specific objects configured
	filterListPointer = filterList;
	while (filterListPointer != 0)
	{

		filterPointer = filterListPointer->filter;
		while (filterPointer != 0)
		{

			if (filterPointer->protocol == 0)
			{
				filterObjectPointer = addFilterObject(filterPointer, protocol);
				filterObjectPointer->type = anyObject;
			}

			if (filterPointer->source == 0)
			{
				filterObjectPointer = addFilterObject(filterPointer, source);
				filterObjectPointer->type = anyObject;
			}

			if (filterPointer->sourceService == 0)
			{
				filterObjectPointer = addFilterObject(filterPointer, sourceService);
				filterObjectPointer->type = anyObject;
				filterObjectPointer->serviceOper = serviceOperAny;
			}

			if (filterPointer->destination == 0)
			{
				filterObjectPointer = addFilterObject(filterPointer, destination);
				filterObjectPointer->type = anyObject;
			}

			if (filterPointer->destinationService == 0)
			{
				filterObjectPointer = addFilterObject(filterPointer, destinationService);
				filterObjectPointer->type = anyObject;
				filterObjectPointer->serviceOper = serviceOperAny;
			}

			if (filterPointer->through == 0)
			{
				filterObjectPointer = addFilterObject(filterPointer, through);
				filterObjectPointer->type = anyObject;
			}

			if (filterPointer->install == 0)
			{
				filterObjectPointer = addFilterObject(filterPointer, installed);
				filterObjectPointer->type = anyObject;
			}

			if (filterPointer->time == 0)
			{
				filterObjectPointer = addFilterObject(filterPointer, timeLimit);
				filterObjectPointer->type = anyObject;
			}

			filterPointer = filterPointer->next;
		}

		filterListPointer = filterListPointer->next;
	}

	return processDeviceSpecificDefaults(device);
}


int Filter::processDeviceSpecificDefaults(Device *device)
{
	return 0;
}

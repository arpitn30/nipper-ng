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
#include "interfaces.h"


CiscoCSSFilter::CiscoCSSFilter()
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
	bypassRulesSupported = true;							// If bypass rules are supported
	defaultRulesSupported = false;							// If default rules are supported
	ruleListsAreAssigned = true;							// Rule lists are assigned to specific elements
	allowName = i18n("Permit");								// The name given to an allowed filter
	denyName = i18n("Deny");								// The name given to a denied filter
	rejectName = i18n("Reject");							// The name given to a rejected filter
	filterConfigTitle = i18n("*ABBREV*ACL*-ABBREV* Configuration");			// The Title for the configuration report section
	filterConfigText = i18n("This section details the configuration of the network filtering *ABBREV*ACL*-ABBREV* on *DEVICENAME*.");							// The device specific configuration report section text
	filterConfigText2 = i18n("");							// The device specific configuration report section text2
	useFilterID = true;									// Use the filter ID to identify a filter (otherwise a line no. is used)
	filterIDTitle = i18n("Clause");							// The title for the filter ID/line no. table column
	filterListName = i18n("*ABBREV*ACL*-ABBREV*");			// The name of the filter list, for use in text paragraphs
	filterListNameTitle = i18n("*ABBREV*ACL*-ABBREV*");		// The name of the filter list, for use in titles
	filterListNamePlaural = i18n("*ABBREV*ACLs*-ABBREV*");	// The name of the filter list, for use in text paragraphs
	filterTitle = i18n("Clause");							// The name of a filter, for use in titles
	filterTitlePlaural = i18n("Clauses");					// The name of a filter, for use in titles
	filterName = i18n("clause");							// The name of a filter, for use use in text paragraph
	filterNamePlaural = i18n("clauses");					// The name of a filter, for use use in text paragraph

	// Issue titles...
	allowAndNotLogIssue = i18n("Not All Permit Clauses Log Access");	// The title text for the "All Allow Rules Do Not Log" issue
	allowAndNotLogTable = i18n("Permit clauses that do not log");		// The table title text for the "All Allow Rules Do Not Log" issue
	allowAndNotLogConcl = i18n("not all permit clauses log access");	// The conclusions text for the "All Allow Rules Do Not Log" issue
	allowAndNotLogReco = i18n("Configure logging for all clauses");		// The recommendations text for "All Allow Rules Do Not Log" (and deny) issue
	denyAndNotLogIssue = i18n("Not All Deny Clauses Log Access");		// The title text for the "All Allow Rules Do Not Log" issue
	denyAndNotLogTable = i18n("Deny clauses that do not log");			// The table title text for the "All Allow Rules Do Not Log" issue
	denyAndNotLogConcl = i18n("not all deny clauses log access");		// The conclusions text for the "All Allow Rules Do Not Log" issue
	configRuleLogging = i18n("A clause can be configured with logging on *DEVICETYPE* devices with the following command:*CODE**COMMAND*clause *CMDUSER*number*-CMDUSER* log enable *CMDREQUIRE*permit *CMDOR* deny*-CMDREQUIRE* *CMDUSER*source*-CMDUSER* detination *CMDUSER*destination*-CMDUSER**-COMMAND**-CODE*");								// The text describing how to configure logging for filter rules
	noFilteringIssue = i18n("No *ABBREV*ACLs*-ABBREV* Were Configured");// The title text for the "No filtering" issue
	noFilteringRec = i18n("Configure *ABBREV*ACLs*-ABBREV* to restict access");		// The title text for the "No filtering" recommendation
	noFilteringCon = i18n("no *ABBREV*ACLs*-ABBREV* were configured");		// The title text for the "No filtering" conclusion
	legacyIssueFinding = i18n("");								// The finding for the legacy issue
	legacyIssueImpact = i18n("");								// The impact for the legacy issue
	legacyIssueEase = i18n("");									// The ease for the legacy issue
	legacyIssueRec = i18n("");									// The recommendation for the legacy issue
	allowAnythingTable = i18n("Clauses permit any access");		// The allow anything table title text
	allowWeakTable = i18n("Clauses provide weak filtering");		// Weak source/service/destination/service table title text
	allowAnyAnyAnyTable = i18n("Clauses permit any host to access any destination and service");			// The allow any source, destination and service table title text
	allowWeakWeakWeakTable = i18n("Clauses provide weak filtering of source, destination and service");	// The allow weak source, destination and service table title text
	allowAnyServiceAnyTable = i18n("Clauses allow any source port to any destination and service");		// The allow any source port, destination and service table title text
	allowWeakServiceAnyTable = i18n("Clauses provide weak filtering of source port to destination and service");	// The allow weak source, destination and service table title text
	allowAnyAnyTable = i18n("Clauses permit any source to any destination");					// The allow any source, destination table title text
	allowAnyAnyServiceTable = i18n("Clauses permit any source to any destination service");	// The allow any source, destination service table title text
	allowAnyDestServiceTable = i18n("Clauses permit any destination and service");			// The allow any destination and service table title text
	allowAnyPortDestTable = i18n("Clauses permit any source port to any destination address");			// The allow any source port to any destination table title text
	allowAnyPortServiceTable = i18n("Clauses permit any source port to any destination service");			// The allow any source port to any dest service table title text
	allowWeakWeakTable = i18n("Clauses permit weak filtering of source and destination addresses");		// The allow weak source, destination addresses
	allowWeakWeakServiceTable = i18n("Clauses permit weak source addresses and destination services");	// The allow weak source, destination service table title text
	allowDestAndServiceTable = i18n("Clauses permit weak destination addresses and services");// The allow weak destination and service table title text
	allowWeakPortDestTable = i18n("Clauses permit weak source ports and destination");		// The allow weak source port to Destination table title text
	allowWeakPortServiceTable = i18n("Clauses permit weak source ports and destination services");		// The allow weak source port to service table title text
	allowAnySourceTable = i18n("Clauses permit from any source address");						// The allow any source address table title text
	allowNetSourceTable = i18n("Clauses permit from a network source address");				// The allow a network source address table title text
	allowAnyPortTable = i18n("Clauses permit from any source port");							// The allow any source port table title text
	allowRangePortTable = i18n("Clauses permit from a source port range");					// The allow range source port table title text
	allowAnyDestTable = i18n("Clauses permit to any destination");							// The allow any destination table title text
	allowNetDestTable = i18n("Clauses permit to a network destination");						// The allow a network destination table title text
	allowToAnyDestServiceTable = i18n("Clauses permit to any destination service");			// The allow any destination service table title text
	allowToNetDestServiceTable = i18n("Clauses permit to a destination service range");		// The allow a destination service range table title text
	bypassContentFilterCon = i18n("Clauses were configured that bypass the content filtering");			// Bypass filter conclusion text
	bypassContentFilterRec = i18n("Connfigure clauses that do not bypass the content filtering");	// Bypass filter recommendation text
	defaultFilterCon = i18n("Clauses were configured that default to the ports filtering action");		// Default filter conclusion text
	defaultFilterRec = i18n("Configure clauses that do not default to the ports filtering action");		// Default filter recommendation text
	rejectSecurityIssueTitle = i18n("Reject Clauses Were Configured");							// Reject filter title text
	securityRejectTextCon = i18n("Clauses were configured that reject network traffic");			// Reject filter conclusion text
	securityRejectTextRec = i18n("Configure clauses to deny rather than reject network traffic");	// Reject filter recommendation text
	clearTextServiceCon = i18n("Clauses were configured that permit access to clear text protocol services");		// Clear Text Service conclusions text
	clearTextServiceRec = i18n("Configure clauses to deny access to any clear text protocol services");			// Clear Text Service recommendations text2
	configureFilterListRecIssueText = i18n("An *ABBREV*ACL*-ABBREV* can be configured with the following command:*CODE**COMMAND*acl *CMDUSER*index*-CMDUSER**-COMMAND**-CODE*");												// The text and commands to configure a filter list
	configureFilterRecIssueText = i18n("A clause can be configured on *DEVICETYPE* devices with the following command:*CODE**COMMAND*clause *CMDUSER*number*-CMDUSER* *CMDREQUIRE*permit *CMDOR* deny*-CMDREQUIRE* *CMDUSER*protocol*-CMDUSER* *CMDUSER*source*-CMDUSER* detination *CMDUSER*destination*-CMDUSER**-COMMAND**-CODE*");													// The text and commands to configure a filter
	unnecessaryServiceCon = i18n("Clauses were configured that permit access to potentially unnecessary services");			// Unnecessary Service conclusions text
	unnecessaryServiceRec = i18n("Configure clauses to deny access to any unnecessary services");	// Unnecessary Service recommendations text2
	filtersWithNoCommentsTitle = i18n("Not All Clauses Include Comments");	// Filters with no comments title text
	noFilterCommentsCon = i18n("not all clauses include comment text indicating their purpose");	// The no comments conclusion text
	noFilterCommentsRec = i18n("Configure comment text for all clauses");		// The no comments recommendation text
	configureFilterCommentText = i18n("");													// The text and commands to configure a filters comment text
	disabledFiltersTitle = i18n("Disabled Clauses Were Configured");			// The disabled filter issues title text
	removeFilterText = i18n("A disabled clause can be removed with the following command:*CODE**COMMAND*no clause *CMDUSER*number*-CMDUSER**-COMMAND**-CODE*");															// The commands and text to delete a filter
	disabledFilterCon = i18n("disabled clauses were configured");				// The disabled filter conclusion text
	disabledFilterRec = i18n("Remove all disabled clauses");					// The disabled filter recommendation text
	defaultActionIssueTitle = i18n("The Default Network Filtering Action Permits Access");	// The default filter action issue title
	defaultActionIssueCon = i18n("the default *ABBREV*ACL*-ABBREV* action was configured to permit access when a clause does not match");	// The default filter action conclusion text
	defaultActionIssueRec = i18n("Set the default *ABBREV*ACL*-ABBREV* action to deny network traffic");		// The default filter action recommendation text
	configureDefaultActionText = i18n("");													// The text and commands to configure the default action
	unusedFiltersIssueTitle = i18n("Unused Clauses Were Configured At The *ABBREV*ACLs*-ABBREV* End");	// Unused filters at the end of the filter list title
	unusedFiltersIssueCon = i18n("unused clauses were configured at the end of the *ABBREV*ACLs*-ABBREV*");		// Unused filters issue conclusions text
	unusedFiltersIssueRec = i18n("Remove all unused clauses");				// Unused filters issue recommendation text
	denyAllLogIssueTitle = i18n("*ABBREV*ACL*-ABBREV* Does Not End with Deny All And Log");	// Deny All And Log Issue title
	denyAllLogConfigure = i18n("A clause to deny everything and log can be added to a *ABBREV*ACL*-ABBREV* with the following command:*CODE**COMMAND*clause *CMDUSER*number*-CMDUSER* log enable deny any any detination any*-COMMAND**-CODE*");															// The text and commands to add a deny all and log line
	denyAllLogIssueCon = i18n("not all *ABBREV*ACLs*-ABBREV* end with a deny all and log ");		// The deny all and log conclusions text
	denyAllLogIssueRec = i18n("Configure a deny all and log Clause as the last Clause in each *ABBREV*ACL*-ABBREV*");			// The deny all and log recommendations text
	contradictIssueTitle = i18n("Contradicting Clauses Were Configured");		// The contradict issue title
	contradictIssueTable = i18n("contradictions of clause");					// The contradict table issue title
	contradictIssueCon = i18n("Clauses were configured that contradict other clauses");				// The contradict issue conclusion
	contradictIssueRec = i18n("Reconfigure the clauses so they do not contradict other clause");	// The contradict issue recommendation
	duplicateIssueTitle = i18n("Duplicate Clauses Were Configured");			// The duplicate/overlapping issue title
	duplicateIssueTable = i18n("duplicates of clause");										// The duplicate/overlapping issue title
	duplicateIssueCon = i18n("Clauses were configured that duplicate the configuration of other clauses");	// The duplicate/overlapping issue title
	duplicateIssueRec = i18n("Reconfigure the clauses so that the rules do not duplicate other clauses");						// The duplicate/overlapping issue title
}


int CiscoCSSFilter::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	filterObjectConfig *filterObjectPointer = 0;
	netObjectListConfig *objectListPointer = 0;
	filterListConfig *filterListPointer = 0;
	filterConfig *filterPointer = 0;
	Interfaces::interfaceConfig *interfacePointer = 0;
	Interfaces::interfaceListConfig *interfaceListPointer = 0;
	fpos_t filePosition;
	string tempString;
	int tempInt = 0;
	int protocolInt = 0;

	// If enabled/disable ...
	if ((strcmp(command->part(1), "enable") == 0) || (strcmp(command->part(1), "disable") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sACL Enabled/Disabled Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		if (strcmp(command->part(1), "enable") == 0)
			noAccessWithoutFilters = false;
		else
			noAccessWithoutFilters = true;
	}

	// ACL...
	else if (strcmp(command->part(0), "acl") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sACL Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		filterListPointer = getFilterList(command->part(1));
		filterListPointer->type = i18n("*ABBREV*ACL*-ABBREV* Configuration");				// The filter list type name (used in the config report)
		filterListPointer->typeDescription = i18n("*DEVICETYPE* device *ABBREV*ACL*-ABBREV* are sequential lists of permit, deny or bypass clauses that are applied to a *ABBREV*VLAN*-ABBREV* circuit. An *ABBREV*ACL*-ABBREV* is processed sequentially with the first clause that matches the incoming traffic applying. If the entire *ABBREV*ACL*-ABBREV* has been processed without a clause matching, then the traffic is denied by a hidden deny all rule. However, *ABBREV*ACL*-ABBREV* have to be enabled on *DEVICETYPE* otherwise all traffic will be permitted regardless of the *ABBREV*ACL*-ABBREV*. Once enabled, any *ABBREV*VLAN*-ABBREV* circuits without an*ABBREV*ACL*-ABBREV* applied will be denied by the hidden deny all rule.");	// The filter list type description for the report (used in config report)
		filterListPointer->legacyType = false;				// Is the filter list a legacy type?
		filterListPointer->sourceOnly = false;				// The type of filter
		filterListPointer->loggingSupport = true;			// Does the filter list support logging
		filterListPointer->supportsTime = false;				// Filter support time (dest only)
		filterListPointer->supportsFragments = false;			// Filter support fragments (dest only)
		filterListPointer->supportsEstablished = false;		// Filter support established (dest only)
		filterListPointer->sourceServiceSupported = true;	// If source services are supported
		filterListPointer->disabledFilterSupport = false;		// Is it possible to disable filters?
		filterListPointer->filterCommentsSupported = false;	// Are filter comments supported
		filterListPointer->showProtocol = true;				// Show the protocol? (some devices use a configured service)
		filterListPointer->showFilterZones = false;			// Does the filter use filter-based zones (i.e. SonicWALL)
		filterListPointer->showStop = false;					// Does the filter have a stop status (i.e. Passport devices)
		filterListPointer->showFilterType = false;			// Does the filter have a type (i.e. like on Passport devices)
		filterListPointer->active = true;					// Is the filter list used? (for CheckPoint devices)

		// Read a line from the config...
		fgetpos(device->inputFile, &filePosition);
		device->readLine(line, lineSize);

		// Split it up into parts...
		command->setConfigLine(line);

		while ((line[0] == ' ') && (feof(device->inputFile) == 0))
		{

			// Clause...
			if (strcasecmp(command->part(0), "clause") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sClause Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				filterPointer = addFilter(filterListPointer);
				tempInt = 1;

				// number
				filterPointer->id = atoi(command->part(tempInt));
				tempInt++;

				// Log?
				if (strcasecmp(command->part(0), "log") == 0)
				{
					tempInt++;
					if (strcasecmp(command->part(0), "enable") == 0)
						filterPointer->log = true;
					else
						filterPointer->log = false;
					tempInt++;
				}

				// Action
				if (strcasecmp(command->part(0), "bypass") == 0)
					filterPointer->action = bypassAction;
				else if (strcasecmp(command->part(0), "deny") == 0)
					filterPointer->action = denyAction;
				else
					filterPointer->action = allowAction;
				tempInt++;

				// Protocol
				filterObjectPointer = addFilterObject(filterPointer, protocol);
				if (strcasecmp(command->part(tempInt), "any") == 0)
					filterObjectPointer->type = anyObject;
				else
					filterObjectPointer->type = protocolObject;
				filterObjectPointer->serviceOper = serviceOperEqual;
				protocolInt = atoi(command->part(tempInt));
				if ((protocolInt != 0) || (strcmp(command->part(tempInt), "0") == 0))
					filterObjectPointer->name.assign(device->getProtocol(protocolInt));
				else
					filterObjectPointer->name.assign(command->part(tempInt));
				tempInt++;

				// Source
				filterObjectPointer = addFilterObject(filterPointer, source);
				filterObjectPointer->serviceOper = serviceOperEqual;
				if (strcasecmp(command->part(tempInt), "nql") == 0)
				{
					tempInt++;
					filterObjectPointer->type = groupObject;
					filterObjectPointer->name.assign(command->part(tempInt));
					tempInt++;
				}
				else if (strcasecmp(command->part(tempInt), "any") == 0)
				{
					tempInt++;
					filterObjectPointer->type = anyObject;
					filterObjectPointer->serviceOper = serviceOperAny;
					filterObjectPointer->name.assign(i18n("Any"));
				}
				else
				{
					filterObjectPointer->type = hostObject;
					filterObjectPointer->name.assign(command->part(tempInt));
					tempInt++;
					if ((strcmp(command->part(tempInt), "destination") != 0) && (strcmp(command->part(tempInt), "range") != 0) && (strcmp(command->part(tempInt), "neq") != 0) && (strcmp(command->part(tempInt), "gt") != 0) && (strcmp(command->part(tempInt), "lt") != 0) && (strcmp(command->part(tempInt), "eq") != 0))
					{
						filterObjectPointer->netmask.assign(command->part(tempInt));
						if (strcmp(filterObjectPointer->netmask.c_str(), "255.255.255.255") != 0)
							filterObjectPointer->type = networkObject;
						tempInt++;
					}
				}

				// Source port
				if (strcmp(command->part(tempInt), "destination") != 0)
				{
					filterObjectPointer = addFilterObject(filterPointer, sourceService);
					filterObjectPointer->type = portObject;

					// Equal...
					if (strcmp(command->part(tempInt), "eq") == 0)
					{
						tempInt++;
						filterObjectPointer->name.assign(command->part(tempInt));
						filterObjectPointer->serviceOper = serviceOperEqual;
					}

					// Less than
					else if (strcmp(command->part(tempInt), "lt") == 0)
					{
						tempInt++;
						filterObjectPointer->name.assign(command->part(tempInt));
						filterObjectPointer->serviceOper = serviceOperLessThan;
					}

					// Greater than
					else if (strcmp(command->part(tempInt), "gt") == 0)
					{
						tempInt++;
						filterObjectPointer->name.assign(command->part(tempInt));
						filterObjectPointer->serviceOper = serviceOperGreaterThan;
					}

					// Not equal to...
					else if (strcmp(command->part(tempInt), "neq") == 0)
					{
						tempInt++;
						filterObjectPointer->name.assign(command->part(tempInt));
						filterObjectPointer->serviceOper = serviceOperNotEqual;
					}

					// Range
					else if (strcmp(command->part(tempInt), "range") == 0)
					{
						tempInt++;
						filterObjectPointer->name.assign(command->part(tempInt));
						filterObjectPointer->serviceOper = serviceOperRange;
						tempInt++;
						filterObjectPointer->netmask.assign(command->part(tempInt));
					}
					tempInt++;
				}

				// destination
				tempInt++;
				filterObjectPointer = addFilterObject(filterPointer, destination);
				filterObjectPointer->serviceOper = serviceOperEqual;
				if (strcasecmp(command->part(tempInt), "nql") == 0)
				{
					tempInt++;
					filterObjectPointer->type = groupObject;
					filterObjectPointer->name.assign(command->part(tempInt));
					tempInt++;
				}
				else if (strcasecmp(command->part(tempInt), "any") == 0)
				{
					tempInt++;
					filterObjectPointer->type = anyObject;
					filterObjectPointer->serviceOper = serviceOperAny;
					filterObjectPointer->name.assign(i18n("Any"));
				}
				else
				{
					filterObjectPointer->type = hostObject;
					filterObjectPointer->name.assign(command->part(tempInt));
					tempInt++;
					if ((tempInt < command->parts) && (strcmp(command->part(tempInt), "prefer") != 0) && (strcmp(command->part(tempInt), "sourcegroup") != 0) && (strcmp(command->part(tempInt), "range") != 0) && (strcmp(command->part(tempInt), "neq") != 0) && (strcmp(command->part(tempInt), "gt") != 0) && (strcmp(command->part(tempInt), "lt") != 0) && (strcmp(command->part(tempInt), "eq") != 0))
					{
						filterObjectPointer->netmask.assign(command->part(tempInt));
						if (strcmp(filterObjectPointer->netmask.c_str(), "255.255.255.255") != 0)
							filterObjectPointer->type = networkObject;
						tempInt++;
					}
				}

				// destination port
				if ((strcmp(command->part(tempInt), "range") == 0) || (strcmp(command->part(tempInt), "neq") == 0) || (strcmp(command->part(tempInt), "gt") == 0) || (strcmp(command->part(tempInt), "lt") == 0) || (strcmp(command->part(tempInt), "eq") == 0))
				{
					filterObjectPointer = addFilterObject(filterPointer, destinationService);
					filterObjectPointer->type = portObject;

					// Equal...
					if (strcmp(command->part(tempInt), "eq") == 0)
					{
						tempInt++;
						filterObjectPointer->name.assign(command->part(tempInt));
						filterObjectPointer->serviceOper = serviceOperEqual;
					}

					// Less than
					else if (strcmp(command->part(tempInt), "lt") == 0)
					{
						tempInt++;
						filterObjectPointer->name.assign(command->part(tempInt));
						filterObjectPointer->serviceOper = serviceOperLessThan;
					}

					// Greater than
					else if (strcmp(command->part(tempInt), "gt") == 0)
					{
						tempInt++;
						filterObjectPointer->name.assign(command->part(tempInt));
						filterObjectPointer->serviceOper = serviceOperGreaterThan;
					}

					// Not equal to...
					else if (strcmp(command->part(tempInt), "neq") == 0)
					{
						tempInt++;
						filterObjectPointer->name.assign(command->part(tempInt));
						filterObjectPointer->serviceOper = serviceOperNotEqual;
					}

					// Range
					else if (strcmp(command->part(tempInt), "range") == 0)
					{
						tempInt++;
						filterObjectPointer->name.assign(command->part(tempInt));
						filterObjectPointer->serviceOper = serviceOperRange;
						tempInt++;
						filterObjectPointer->netmask.assign(command->part(tempInt));
					}
					tempInt++;
				}
			}

			// Apply circuit
			else if ((strcmp(command->part(0), "apply") == 0) && (strncmp(command->part(1), "circuit-(", 9) == 0))
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sApply To Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				interfaceListPointer = device->interfaces->getInterfaceList("CIRCUIT");
				if ((interfaceListPointer != 0) && (filterListPointer != 0))
				{
					tempString.assign(command->part(1) + 9);
					tempString.resize(tempString.length() - 1);
					interfacePointer = device->interfaces->getOnlyInterface(interfaceListPointer, tempString.c_str());
					if (interfacePointer != 0)
					{
						device->interfaces->addFilterList(interfacePointer, filterListPointer->name.c_str(), true);
					}
				}
			}

			// NOT PROCESSED...
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

	// NQL...
	else if (strcmp(command->part(0), "nql") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sNQL Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		objectListPointer = getObjectList(command->part(1));
		objectListPointer->title = i18n("*ABBREV*NQL*-ABBREV* Configuration");								// Pointer to the object name text
		objectListPointer->description = i18n("*ABBREV*NQL*-ABBREV* are lists of *ABBREV*IP*-ABBREV* addresses and networks that are grouped together to ease administration. The *ABBREV*NQL*-ABBREV* can then be used in an *ABBREV*ACL*-ABBREV*.");						// Pointer to the description text
		objectListPointer->objectCommentSupported = false;					// Enabled object comments
		objectListPointer->protocolSupported = false;							// Only applies if enhancedServiceObject is not the type

		// Read a line from the config...
		fgetpos(device->inputFile, &filePosition);
		device->readLine(line, lineSize);

		// Split it up into parts...
		command->setConfigLine(line);

		while ((line[0] == ' ') && (feof(device->inputFile) == 0))
		{

			// Description...
			if (strcasecmp(command->part(0), "description") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sNQL Description Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				objectListPointer->comment.assign(command->part(1));
			}

			// IP Address...
			else if ((strcasecmp(command->part(0), "ip") == 0) && (strcasecmp(command->part(1), "address") == 0))
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sNQL IP Address Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				filterObjectPointer = addObject(objectListPointer);
				filterObjectPointer->type = hostObject;
				filterObjectPointer->serviceOper = serviceOperEqual;

				tempString.assign(command->part(2));
				if (tempString.find("/") == string::npos)
				{
					filterObjectPointer->name.assign(command->part(2));
					filterObjectPointer->netmask.assign(command->part(3));
					if (filterObjectPointer->netmask.compare("255.255.255.255") != 0)
						filterObjectPointer->type = networkObject;
				}
				else
				{
					filterObjectPointer->name.assign(tempString.substr(0, tempString.find("/") - 1));
					filterObjectPointer->netmask.assign(device->cidrToNetmask(tempString.substr(tempString.find("/") + 1).c_str()));
					if (filterObjectPointer->netmask.compare("255.255.255.255") != 0)
						filterObjectPointer->type = networkObject;
				}
			}

			// NOT PROCESSED...
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

	// NOT PROCESSED...
	else
		device->lineNotProcessed(line);

	return 0;
}


int CiscoCSSFilter::processDeviceSpecificDefaults(Device *device)
{
	if ((filterList == 0) && (noAccessWithoutFilters == false))
		filterConfigText2 = i18n("No *ABBREV*ACL*-ABBREV* have been configured on *DEVICENAME* and *ABBREV*ACL*-ABBREV* processing is disabled, so all network traffic will be permitted.");
	else if ((filterList != 0) && (noAccessWithoutFilters == false))
		filterConfigText2 = i18n("Although *ABBREV*ACL*-ABBREV* have been configured on *DEVICENAME*, *ABBREV*ACL*-ABBREV* processing is disabled, so all network traffic will be permitted regardless.");
	else if ((filterList == 0) && (noAccessWithoutFilters == true))
		filterConfigText2 = i18n("No *ABBREV*ACL*-ABBREV* have been configured on *DEVICENAME* and *ABBREV*ACL*-ABBREV* processing is enabled, so all network traffic will be denied.");
	else
		filterConfigText2 = i18n("*ABBREV*ACL*-ABBREV* processing is enabled on *DEVICENAME*, so all network traffic that does not match an *ABBREV*ACL*-ABBREV* clause will be denied.");

	return 0;
}


int CiscoCSSFilter::generateDeviceSpecificFilterSecurityIssues(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;

	if (noAccessWithoutFilters == false)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] ACL Were Not Active\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("*ABBREV*ACL*-ABBREV* Were Not Active"));
		securityIssuePointer->reference.assign("CSS.FILTNOAC.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*ABBREV*ACLs*-ABBREV* are sequential lists of allow, deny and bypass clauses that determine whether network traffic is permitted or dropped. All *ABBREV*ACLs*-ABBREV* have a hidden deny all clause as the final clause, clause 255. Regardless of whether *ABBREV*ACLs*-ABBREV* are configured, if *ABBREV*ACLs*-ABBREV* are not enabled on *DEVICETYPE* devices then all traffic will be allowed."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *ABBREV*ACLs*-ABBREV* are disabled."));

		// Issue impact...
		securityIssuePointer->impactRating = 6;			// Medium
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("With *ABBREV*ACLs*-ABBREV* disabled, an attacker could gain access to hosts and services for which they should not be able to access."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 0;			// N/A
		paragraphPointer->paragraph.assign(i18n("Network traffic will not be blocked by *DEVICENAME*."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 5;			// Planned
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that *ABBREV*ACL*-ABBREV* should be enabled. Once enabled, all traffic is denied by default, so an *ABBREV*ACL*-ABBREV* should be configured to permit traffic to the device prior to enabling *ABBREV*ACLs*-ABBREV*."));

		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*ABBREV*ACL*-ABBREV* can be enabled with the following command:*CODE**COMMAND*acl enable*-COMMAND**-CODE*"));

		// Conclusions text...
		securityIssuePointer->conLine.assign(i18n("*ABBREV*ACL*-ABBREV* was disabled"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("enable *ABBREV*ACLs*-ABBREV*"), true);
	}

	return 0;
}


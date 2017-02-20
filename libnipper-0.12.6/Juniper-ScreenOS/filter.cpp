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


ScreenOSFilter::ScreenOSFilter()
{
	// Policy list type descriptions...
	intrazoneTitle = i18n("Intrazone Policy");
	intrazoneDescription = i18n("An intrazone policy defines the network traffic that is permitted between two seperate interfaces bound to the same zone.");
	interzoneTitle = i18n("Interzone Policy");
	interzoneDescription = i18n("An interzone policy defines the network traffic that is permitted between different zones.");
	globalzoneTitle = i18n("Global Policy");
	globalzoneDescription = i18n("The global policy defines the network traffic that is permitted between addresses in the global zone.");
	serviceObjectTitle = i18n("Service Objects");
	serviceObjectDescription = i18n("Service objects are used to defined specific protocols, source and destination ports for a named service. The service objects can then be used in a policy rule, either directly or through a service group definition. *DEVICETYPE* devices have a number of predefined service objects, or custom service objects can be created. This section details the custom service objects and any predefined objects that are used in the firewall policy rules.");
	serviceGroupObjectTitle = i18n("Service Object Group");
	serviceGroupObjectDescription = i18n("Service object groups are used to group service objects. Once service objects have been grouped they can be used within policy rules using the service group name.");
	addressGroupObjectTitle = i18n("Address Object Group");
	addressGroupObjectDescription = i18n("Address object groups are used to group a zones address book entries. When policy rules are defined, to ease administration, multiple addresses can be referenced using the address group name rather than individually.");
	addressObjectListTitle = i18n("Security Zone Address Book");
	addressObjectListDescription = i18n("The security zone address books define hosts and networks for a security zone. These addresses can then be used within the policy rule configuration.");

	// Filter device options...
	logLevelsSupported = false;								// Are log Levels supported
	logOnlyDenySupported = false;							// Is only Deny rule logging supported
	noAccessWithoutFilters = true;							// Is access not granted if no filters are configured
	filterSupportsInstalled = false;						// If filtering supports installed (i.e. CheckPoint)
	filterSupportsThrough = false;							// If a filtering supports through (i.e. CheckPoint)
	rejectRulesSupported = true;							// If reject rules are supported
	bypassRulesSupported = false;							// If bypass rules are supported
	defaultRulesSupported = false;							// If default rules are supported
	ruleListsAreAssigned = false;							// Rule lists are assigned to specific elements
	allowName = i18n("Permit");								// The name given to an allowed filter
	denyName = i18n("Deny");								// The name given to a denied filter
	rejectName = i18n("Reject");							// The name given to a rejected filter
	filterConfigTitle = i18n("Security Zone Policy Configuration");		// The Title for the configuration report section
	filterConfigText = i18n("A policy is a set of rules that will determine whether traffic between security zones (interzone), between interfaces in the same zone (intrazone) or between addresses in the global zone are permitted or denied. Each interface can be assigned to a different security zone, and multiple interfaces can be assigned to a single security zone.");							// The device specific configuration report section text
	filterConfigText2 = i18n("The policy is processed by *DEVICETYPE* devices from the top to the bottom with the first policy rule that applies taking effect. If no rule matches, the default policy will take effect, which is set to deny by default on *DEVICETYPE*. Policies are applied in the following order:");							// The device specific configuration report section text2
	useFilterID = true;									// Use the filter ID to identify a filter (otherwise a line no. is used)
	filterIDTitle = i18n("Rule");							// The title for the filter ID/line no. table column
	filterListName = i18n("policy list");					// The name of the filter list, for use in text paragraphs
	filterListNameTitle = i18n("Policy list");				// The name of the filter list, for use in titles
	filterListNamePlaural = i18n("policy lists");			// The name of the filter list, for use in text paragraphs
	filterTitle = i18n("Rule");								// The name of a filter, for use in titles
	filterTitlePlaural = i18n("Rules");						// The name of a filter, for use in titles
	filterName = i18n("rule");								// The name of a filter, for use use in text paragraph
	filterNamePlaural = i18n("rules");						// The name of a filter, for use use in text paragraph

	// Issue titles...
	allowAndNotLogIssue = i18n("All Permit Rules Do Not Log");	// The title text for the "All Allow Rules Do Not Log" issue
	allowAndNotLogTable = i18n("Permit rules that do not log");	// The table title text for the "All Allow Rules Do Not Log" issue
	allowAndNotLogConcl = i18n("all permit rules do not log");	// The conclusions text for the "All Allow Rules Do Not Log" issue
	allowAndNotLogReco = i18n("Configure logging for all rules");	// The recommendations text for the "All Allow Rules Do Not Log" issue
	denyAndNotLogIssue = i18n("All Deny Rules Do Not Log");		// The title text for the "All Allow Rules Do Not Log" issue
	denyAndNotLogTable = i18n("Deny rules that do not log");	// The table title text for the "All Allow Rules Do Not Log" issue
	denyAndNotLogConcl = i18n("all deny rules do not log");		// The conclusions text for the "All Allow Rules Do Not Log" issue
	configRuleLogging = i18n("");								// The text describing how to configure logging for filter rules
	noFilteringIssue = i18n("No Filtering Rules Were Configured");	// The title text for the "No filtering" issue
	noFilteringRec = i18n("Configure network filtering");		// The title text for the "No filtering" recommendation
	noFilteringCon = i18n("no network filtering was configured");	// The title text for the "No filtering" conclusion
	legacyIssueFinding = i18n("");								// The finding for the legacy issue
	legacyIssueImpact = i18n("");								// The impact for the legacy issue
	legacyIssueEase = i18n("");									// The ease for the legacy issue
	legacyIssueRec = i18n("");									// The recommendation for the legacy issue
	allowAnythingTable = i18n("rules allow any access");		// The allow anything table title text
	allowWeakTable = i18n("rules provide weak filtering");		// Weak source/service/destination/service table title text
	allowAnyAnyAnyTable = i18n("rules allow any host to any destination and service");		// The allow any source, destination and service table title text
	allowWeakWeakWeakTable = i18n("rules provide weak filtering of source, destination and service");			// The allow weak source, destination and service table title text
	allowAnyServiceAnyTable = i18n("rules allow any source port to any destination and service");				// The allow any source port, destination and service table title text
	allowWeakServiceAnyTable = i18n("rules provide weak filtering of source port to destination and service");	// The allow weak source, destination and service table title text
	allowAnyAnyTable = i18n("rules allow any source to any destination");					// The allow any source, destination table title text
	allowAnyAnyServiceTable = i18n("rules allow any source to any destination service");	// The allow any source, destination service table title text
	allowAnyDestServiceTable = i18n("rules allow any destination and service");				// The allow any destination and service table title text
	allowAnyPortDestTable = i18n("rules allow any source port to any destination address");	// The allow any source port to any destination table title text
	allowAnyPortServiceTable = i18n("rules allow any source port to any destination service");					// The allow any source port to any dest service table title text
	allowWeakWeakTable = i18n("rules permit weak filtering of source and destination addresses");				// The allow weak source, destination addresses
	allowWeakWeakServiceTable = i18n("rules permit weak source addresses and destination services");			// The allow weak source, destination service table title text
	allowDestAndServiceTable = i18n("rules permit weak destination addresses and services");// The allow weak destination and service table title text
	allowWeakPortDestTable = i18n("rules permit weak source ports and destination");		// The allow weak source port to Destination table title text
	allowWeakPortServiceTable = i18n("rules permit weak source ports and destination services");				// The allow weak source port to service table title text
	allowAnySourceTable = i18n("rules permit from any source address");						// The allow any source address table title text
	allowNetSourceTable = i18n("rules permit from a network source address");				// The allow a network source address table title text
	allowAnyPortTable = i18n("rules permit from any source port");							// The allow any source port table title text
	allowRangePortTable = i18n("rules permit from a source port range");					// The allow range source port table title text
	allowAnyDestTable = i18n("rules permit to any destination");							// The allow any destination table title text
	allowNetDestTable = i18n("rules permit to a network destination");						// The allow a network destination table title text
	allowToAnyDestServiceTable = i18n("rules permit to any destination service");			// The allow any destination service table title text
	allowToNetDestServiceTable = i18n("rules permit to a destination service range");		// The allow a destination service range table title text
	bypassContentFilterCon = i18n("rules are configured that bypass the content filtering");					// Bypass filter conclusion text
	bypassContentFilterRec = i18n("Connfigure rules not to bypass the content filtering");	// Bypass filter recommendation text
	defaultFilterCon = i18n("rules are configured to default to the ports filtering action");					// Default filter conclusion text
	defaultFilterRec = i18n("Configure rules not to default to the ports filtering action");// Default filter recommendation text
	rejectSecurityIssueTitle = i18n("Reject rules Are Configured");							// Reject filter title text
	securityRejectTextCon = i18n("rules are configured that reject network traffic");		// Reject filter conclusion text
	securityRejectTextRec = i18n("Configure rules to deny rather than reject network traffic");					// Reject filter recommendation text
	clearTextServiceCon = i18n("rules were configured that permit access to clear text protocol services");		// Clear Text Service conclusions text
	clearTextServiceRec = i18n("Configure rules to deny access to any clear text protocol services");			// Clear Text Service recommendations text2
	configureFilterListRecIssueText = i18n("");												// The text and commands to configure a filter list
	configureFilterRecIssueText = i18n("A *DEVICETYPE* device policy rule can be configured with the following command:*CODE**COMMAND*set policy from *CMDUSER*src-zone*-CMDUSER* to *CMDUSER*dst-zone*-CMDUSER* *CMDUSER*source*-CMDUSER* *CMDUSER*dest*-CMDUSER* *CMDUSER*service*-CMDUSER* *CMDOPTION*permit *CMDOR* deny*-CMDOPTION**-COMMAND**-CODE*");													// The text and commands to configure a filter
	unnecessaryServiceCon = i18n("rules were configured that permit access to potentially unnecessary services");			// Unnecessary Service conclusions text
	unnecessaryServiceRec = i18n("Configure rules to deny access to any unnecessary services");	// Unnecessary Service recommendations text2
	filtersWithNoCommentsTitle = i18n("Not All Rules Include Comments");	// Filters with no comments title text
	noFilterCommentsCon = i18n("not all rules include comment text indicating their purpose");	// The no comments conclusion text
	noFilterCommentsRec = i18n("Configure comment text for all rules");		// The no comments recommendation text
	configureFilterCommentText = i18n("");													// The text and commands to configure a filters comment text
	disabledFiltersTitle = i18n("Disabled Rules Were Configured");			// The disabled filter issues title text
	removeFilterText = i18n("");															// The commands and text to delete a filter
	disabledFilterCon = i18n("disabled rules were configured");				// The disabled filter conclusion text
	disabledFilterRec = i18n("Remove all disabled rules");					// The disabled filter recommendation text
	defaultActionIssueTitle = i18n("The Default Network Filtering Action Permits Access");	// The default filter action issue title
	defaultActionIssueCon = i18n("the default policy list action was configured to permit access when a rule does not match");	// The default filter action conclusion text
	defaultActionIssueRec = i18n("Set the default policy list action to deny network traffic");		// The default filter action recommendation text
	configureDefaultActionText = i18n("");													// The text and commands to configure the default action
	unusedFiltersIssueTitle = i18n("Unused Rules Were Configured At The Policy Lists End");	// Unused filters at the end of the filter list title
	unusedFiltersIssueCon = i18n("unused Rules were configured at the end of the policy lists");		// Unused filters issue conclusions text
	unusedFiltersIssueRec = i18n("Remove all unused rules");				// Unused filters issue recommendation text
	denyAllLogIssueTitle = i18n("Policy List Does Not End with Deny All And Log");	// Deny All And Log Issue title
	denyAllLogConfigure = i18n("");															// The text and commands to add a deny all and log line
	denyAllLogIssueCon = i18n("not all Policy Lists end with a deny all and log ");		// The deny all and log conclusions text
	denyAllLogIssueRec = i18n("Configure a deny all and log rule as the last rule in each policy list");			// The deny all and log recommendations text
	contradictIssueTitle = i18n("Contradicting Rules Were Configured");		// The contradict issue title
	contradictIssueTable = i18n("contradictions of rule");					// The contradict table issue title
	contradictIssueCon = i18n("rules were configured that contradict other rules");				// The contradict issue conclusion
	contradictIssueRec = i18n("Reconfigure the rules so they do not contradict other rule");	// The contradict issue recommendation
	duplicateIssueTitle = i18n("Duplicate Rules Were Configured");			// The duplicate/overlapping issue title
	duplicateIssueTable = i18n("duplicates of rule");										// The duplicate/overlapping issue title
	duplicateIssueCon = i18n("rules were configured that duplicate the configuration of other rules");	// The duplicate/overlapping issue title
	duplicateIssueRec = i18n("Reconfigure the Rules so that the rules do not duplicate other Rules");						// The duplicate/overlapping issue title

}


ScreenOSFilter::~ScreenOSFilter()
{
}


int ScreenOSFilter::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	filterListConfig *filterListPointer = 0;
	filterConfig *filterPointer = 0;
	filterObjectConfig *objectPointer = 0;
	filterObjectConfig *objectSubPointer = 0;
	netObjectListConfig *objectListPointer = 0;
	int tempInt = 0;
	int policyId = 0;
	bool globalzone = false;
	string policyName;
	string tempString;

	// Policy...
	if (strcasecmp(command->part(1), "policy") == 0)
	{
		tempInt = 2;

		// Global
		if (strcasecmp(command->part(tempInt), "global") == 0)
		{
			globalzone = true;
			tempInt++;
		}

		// Policy id
		if (strcasecmp(command->part(tempInt), "id") == 0)
		{
			tempInt++;
			policyId = atoi(command->part(tempInt));
			tempInt++;
		}

		// Policy name
		if (strcasecmp(command->part(tempInt), "name") == 0)
		{
			tempInt++;
			policyName.assign(command->part(tempInt));
			tempInt++;
		}

		// From / To...
		if ((strcasecmp(command->part(tempInt), "from") == 0) && (strcasecmp(command->part(tempInt + 2), "to") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sPolicy From/To Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			tempInt++;

			// Create list and filter...
			filterListPointer = getFilterList(command->part(tempInt), command->part(tempInt + 2));
			filterListPointer->name.assign(command->part(tempInt));
			tempInt += 2;
			filterListPointer->to.assign(command->part(tempInt));
			if (globalzone == true)
			{
				filterListPointer->globalFilter = true;
				filterListPointer->type = globalzoneTitle;
				filterListPointer->typeDescription = globalzoneDescription;
			}
			else if (strcasecmp(command->part(tempInt), command->part(tempInt + 2)) == 0)
			{
				filterListPointer->type = intrazoneTitle;
				filterListPointer->typeDescription = intrazoneDescription;
			}
			else
			{
				filterListPointer->type = interzoneTitle;
				filterListPointer->typeDescription = interzoneDescription;
			}
			filterListPointer->loggingSupport = true;
			filterListPointer->supportsTime = true;
			filterListPointer->sourceServiceSupported = false;
			filterListPointer->disabledFilterSupport = true;
			filterListPointer->showProtocol = false;
			tempInt++;
			filterPointer = getFilter(policyId, filterListPointer);

			// Source...
			objectPointer = addFilterObject(filterPointer, source);
			if (strcasecmp(command->part(tempInt), "Any") == 0)
			{
				objectPointer->name.assign(i18n("Any"));
				objectPointer->type = anyObject;
			}
			else
			{
				objectPointer->name.assign(command->part(tempInt));
				objectPointer->type = groupObject;
				objectPointer->serviceOper = Filter::serviceOperEqual;
			}
			tempInt++;

			// Destination...
			objectPointer = addFilterObject(filterPointer, destination);
			if (strcasecmp(command->part(tempInt), "Any") == 0)
			{
				objectPointer->name.assign(i18n("Any"));
				objectPointer->type = anyObject;
			}
			else
			{
				objectPointer->name.assign(command->part(tempInt));
				objectPointer->type = groupObject;
				objectPointer->serviceOper = Filter::serviceOperEqual;
			}
			tempInt++;

			// Destination Service...
			objectPointer = addFilterObject(filterPointer, destinationService);
				if (strcasecmp(command->part(tempInt), "ANY") == 0)
			{
				objectPointer->name.assign(i18n("Any"));
				objectPointer->type = anyObject;
			}
			else
			{
				objectPointer->name.assign(command->part(tempInt));
				objectPointer->serviceOper = Filter::serviceOperEqual;
				objectPointer->type = groupObject;
			}
			tempInt++;

			// Action...
			if (strcasecmp(command->part(tempInt), "permit") == 0)
				filterPointer->action = allowAction;
			else if (strcasecmp(command->part(tempInt), "deny") == 0)
				filterPointer->action = denyAction;
			else if (strcasecmp(command->part(tempInt), "reject") == 0)
				filterPointer->action = rejectAction;
			else if (strcasecmp(command->part(tempInt), "nat") == 0)
			{
				filterPointer->action = natAction;
				return 0;
			}
			else if (strcasecmp(command->part(tempInt), "tunnel") == 0)
			{
				filterPointer->action = tunnelAction;
				return 0;
			}
			tempInt++;

			while (tempInt < command->parts)
			{

				// Log
				if (strcasecmp(command->part(tempInt), "log") == 0)
					filterPointer->log = true;

				tempInt++;
			}
		}

		// Disable
		else if (strcasecmp(command->part(tempInt), "disable") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sPolicy Disable Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			filterPointer = getFilter(policyId);
			if (filterPointer != 0)
				filterPointer->enabled = false;
		}

		// Policy Context
		else if (tempInt == command->parts)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sPolicy Context Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			filterPointer = getFilter(policyId);
			if (filterPointer != 0)
			{
				while ((strcasecmp(command->part(0), "exit") != 0) && (feof(device->inputFile) == 0))
				{

					// Read a line from the config...
					device->readLine(line, lineSize);

					// Split it up into parts...
					command->setConfigLine(line);

					// Name
					if (strcasecmp(command->part(1), "name") == 0)
					{
						if (device->config->reportFormat == Config::Debug)
							printf("%sPolicy Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

						filterPointer->name.assign(command->part(2));
					}

					// Log
					else if (strcasecmp(command->part(1), "log") == 0)
					{
						if (device->config->reportFormat == Config::Debug)
							printf("%sPolicy Log Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

						filterPointer->log = true;
					}

					// Destination
					else if (strcasecmp(command->part(1), "dst-address") == 0)
					{
						if (device->config->reportFormat == Config::Debug)
							printf("%sPolicy Destination Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

						objectPointer = addFilterObject(filterPointer, destination);
						objectPointer->name.assign(command->part(2));
						objectPointer->type = groupObject;
						objectPointer->serviceOper = Filter::serviceOperEqual;
					}

					// Source
					else if (strcasecmp(command->part(1), "src-address") == 0)
					{
						if (device->config->reportFormat == Config::Debug)
							printf("%sPolicy Source Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

						objectPointer = addFilterObject(filterPointer, source);
						objectPointer->name.assign(command->part(2));
						objectPointer->type = groupObject;
						objectPointer->serviceOper = Filter::serviceOperEqual;
					}

					// Service
					else if (strcasecmp(command->part(1), "service") == 0)
					{
						if (device->config->reportFormat == Config::Debug)
							printf("%sPolicy Service Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

						objectPointer = addFilterObject(filterPointer, destinationService);
						objectPointer->name.assign(command->part(2));
						objectPointer->type = groupObject;
						objectPointer->serviceOper = Filter::serviceOperEqual;
					}

					else if (strcasecmp(command->part(0), "exit") == 0)
					{
						if (device->config->reportFormat == Config::Debug)
							printf("%sPolicy Context End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
					}

					// NOT PROCESSED...
					else
						device->lineNotProcessed(line);
				}
			}
		}

		// All others...
		else
			device->lineNotProcessed(line);
	}

	// Service...
	else if ((strcasecmp(command->part(1), "service") == 0) && (strcasecmp(command->part(3), "timeout") != 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sService Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		objectListPointer = getObjectList("Custom service objects");
		objectListPointer->type = enhancedServiceObject;
		objectListPointer->title = serviceObjectTitle;
		objectListPointer->description = serviceObjectDescription;
		if (strcasecmp(command->part(3), "protocol") == 0)
			tempInt = 4;
		else
			tempInt = 3;

		// Add service object
		objectPointer = addObject(objectListPointer);
		objectPointer->name.assign(command->part(2));
		objectPointer->type = enhancedServiceObject;

		// Add protocol
		objectSubPointer = addObject(objectPointer, protocol);
		if (strcasecmp(command->part(tempInt), "icmp") == 0)
		{
			objectSubPointer->type = icmpObject;
			tempInt += 2;
			objectSubPointer->name.assign(command->part(tempInt));
			tempInt += 2;
			objectSubPointer->netmask.assign(command->part(tempInt));
		}
		else if (strcasecmp(command->part(tempInt), "ms-rpc") == 0)
		{
			objectSubPointer->type = rpcObject;
			tempInt += 2;
			objectSubPointer->name.assign(i18n("*ABBREV*MS*-ABBREV*-*ABBREV*RPC*-ABBREV*"));
			objectSubPointer->netmask.assign(command->part(tempInt));
		}
		else if (strcasecmp(command->part(tempInt), "sun-rpc") == 0)
		{
			objectSubPointer->type = rpcObject;
			tempInt += 2;
			objectSubPointer->name.assign(i18n("*ABBREV*RPC*-ABBREV*"));
			objectSubPointer->netmask.assign(command->part(tempInt));
		}
		else
		{
			objectSubPointer->type = protocolObject;
			if (strcasecmp(command->part(tempInt), "tcp") == 0)
				objectSubPointer->name.assign(i18n("*ABBREV*TCP*-ABBREV*"));
			else if (strcasecmp(command->part(tempInt), "udp") == 0)
				objectSubPointer->name.assign(i18n("*ABBREV*UDP*-ABBREV*"));
			else
			{
				objectSubPointer->name.assign(device->getProtocol(atoi(command->part(tempInt))));
				if (objectSubPointer->name.empty())
					objectSubPointer->name.assign(command->part(tempInt));
			}
			tempInt++;

			while (tempInt < command->parts)
			{
				if (strcasecmp(command->part(tempInt), "src-port") == 0)
				{
					objectSubPointer = addObject(objectPointer, sourceService);
					objectSubPointer->type = portObject;
					tempInt++;
					tempString.assign(command->part(tempInt));
					if (tempString.compare("0-65535") == 0)
					{
						objectSubPointer->name.assign("0");
						objectSubPointer->netmask.assign("65535");
						objectSubPointer->serviceOper = serviceOperAny;
					}
					else
					{
						objectSubPointer->name.assign(tempString.substr(0, tempString.find("-")));
						objectSubPointer->netmask.assign(tempString.substr(tempString.find("-") + 1));
						if (objectSubPointer->name.compare(objectSubPointer->netmask) != 0)
							objectSubPointer->serviceOper = serviceOperRange;
						else
						{
							objectSubPointer->serviceOper = Filter::serviceOperEqual;
							objectSubPointer->netmask.assign("");
						}
					}
				}

				else if (strcasecmp(command->part(tempInt), "dst-port") == 0)
				{
					objectSubPointer = addObject(objectPointer, destinationService);
					objectSubPointer->type = portObject;
					tempInt++;
					tempString.assign(command->part(tempInt));
					if (tempString.compare("0-65535") == 0)
					{
						objectSubPointer->name.assign("0");
						objectSubPointer->netmask.assign("65535");
						objectSubPointer->serviceOper = serviceOperAny;
					}
					else
					{
						objectSubPointer->name.assign(tempString.substr(0, tempString.find("-")));
						objectSubPointer->netmask.assign(tempString.substr(tempString.find("-") + 1));
						if (objectSubPointer->name.compare(objectSubPointer->netmask) != 0)
							objectSubPointer->serviceOper = serviceOperRange;
						else
						{
							objectSubPointer->serviceOper = Filter::serviceOperEqual;
							objectSubPointer->netmask.assign("");
						}
					}
				}

				tempInt++;
			}
		}
	}

	// Address...
	else if ((strcasecmp(command->part(1), "group") == 0) && (strcasecmp(command->part(2), "address") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sGroup Address Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		objectListPointer = getObjectList(command->part(4), command->part(3));
		objectListPointer->type = groupObject;
		objectListPointer->title = addressGroupObjectTitle;
		objectListPointer->description = addressGroupObjectDescription;

		tempInt = 5;
		while (tempInt < command->parts)
		{
			if (strcasecmp(command->part(tempInt), "add") == 0)
			{
				tempInt++;
				objectPointer = addObject(objectListPointer);
				objectPointer->type = addressObject;
				objectPointer->serviceOper = Filter::serviceOperEqual;
				objectPointer->name.assign(command->part(tempInt));
			}

			else if (strcasecmp(command->part(tempInt), "comment") == 0)
			{
				tempInt++;
				if (objectPointer != 0)
				{
					objectPointer->comment.assign(command->part(tempInt));
					objectListPointer->objectCommentSupported = true;
				}
				else
					objectListPointer->comment.assign(command->part(tempInt));
			}

			tempInt++;
		}
	}

	// Service...
	else if ((strcasecmp(command->part(1), "group") == 0) && (strcasecmp(command->part(2), "service") == 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sGroup Service Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		objectListPointer = getObjectList(command->part(3));
		objectListPointer->type = serviceObject;
		objectListPointer->title = serviceGroupObjectTitle;
		objectListPointer->description = serviceGroupObjectDescription;

		tempInt = 4;
		while (tempInt < command->parts)
		{
			if (strcasecmp(command->part(tempInt), "add") == 0)
			{
				tempInt++;
				objectPointer = addObject(objectListPointer);
				objectPointer->type = enhancedServiceObject;
				objectPointer->name.assign(command->part(tempInt));
				objectPointer->serviceOper = Filter::serviceOperEqual;
			}

			else if (strcasecmp(command->part(tempInt), "comment") == 0)
			{
				tempInt++;
				if (objectPointer != 0)
				{
					objectPointer->comment.assign(command->part(tempInt));
					objectListPointer->objectCommentSupported = true;
				}
				else
					objectListPointer->comment.assign(command->part(tempInt));
			}

			tempInt++;
		}
	}

	// Address...
	else if (strcasecmp(command->part(1), "address") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sAddress Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		// Get Object List
		objectListPointer = getObjectList(command->part(2));
		objectListPointer->type = addressBookObject;
		objectListPointer->title = addressObjectListTitle;
		objectListPointer->description = addressObjectListDescription;

		// Set list entry
		objectPointer = addObject(objectListPointer);
		objectPointer->type = hostObject;
		objectPointer->label.assign(command->part(3));
		tempString.assign(command->part(4));
		if (tempString.find("/") == string::npos)
		{
			tempInt = 6;
			objectPointer->name.assign(command->part(4));
			objectPointer->netmask.assign(command->part(5));
			if (objectPointer->netmask.compare("255.255.255.255") != 0)
				objectPointer->type = networkObject;
		}
		else
		{
			tempInt = 5;
			objectPointer->name.assign(tempString.substr(0, tempString.find("/") - 1));
			objectPointer->netmask.assign(device->cidrToNetmask(tempString.substr(tempString.find("/") + 1).c_str()));
			if (objectPointer->netmask.compare("255.255.255.255") != 0)
				objectPointer->type = networkObject;
		}

		if (tempInt < command->parts)
		{
			objectListPointer->objectCommentSupported = true;
			objectPointer->comment.assign(command->part(tempInt));
		}
		objectPointer->serviceOper = Filter::serviceOperEqual;
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


struct Builtin
{
	bool added;
	const char *name;
	const char *protocol;
	const char *source;
	Filter::serviceOperType sourceType;
	const char *dest;
	const char *destEnd;
	Filter::serviceOperType destType;
	struct Builtin *next;
};

// last 123
struct Builtin builtin122 = {false, "LPR", "TCP", "Any", Filter::serviceOperAny, "515", "", Filter::serviceOperEqual, 0};
struct Builtin builtin121 = {false, "LDAP", "TCP", "Any", Filter::serviceOperAny, "389", "", Filter::serviceOperEqual, &builtin122};
struct Builtin builtin120 = {false, "L2TP", "UDP", "Any", Filter::serviceOperAny, "1701", "", Filter::serviceOperEqual, &builtin121};
struct Builtin builtin119 = {false, "IRC", "TCP", "Any", Filter::serviceOperAny, "6660", "6669", Filter::serviceOperRange, &builtin120};
struct Builtin builtin118 = {false, "IKE-NAT", "UDP", "500", Filter::serviceOperEqual, "500", "", Filter::serviceOperEqual, &builtin119};
struct Builtin builtin117 = {false, "Internet Locator Service", "", "", Filter::serviceOperNotEqual, "636", "", Filter::serviceOperEqual, &builtin118};
struct Builtin builtin116 = {false, "Internet Locator Service", "", "", Filter::serviceOperNotEqual, "522", "", Filter::serviceOperEqual, &builtin117};
struct Builtin builtin115 = {false, "Internet Locator Service", "TCP", "Any", Filter::serviceOperAny, "389", "", Filter::serviceOperEqual, &builtin116};
struct Builtin builtin114 = {false, "IMAP", "TCP", "Any", Filter::serviceOperAny, "143", "", Filter::serviceOperEqual, &builtin115};
struct Builtin builtin113 = {false, "IKE", "UDP", "Any", Filter::serviceOperAny, "500", "", Filter::serviceOperEqual, &builtin114};
struct Builtin builtin112 = {false, "IDENT", "TCP", "Any", Filter::serviceOperAny, "113", "", Filter::serviceOperEqual, &builtin113};
struct Builtin builtin111 = {false, "HTTPS", "TCP", "Any", Filter::serviceOperAny, "443", "", Filter::serviceOperEqual, &builtin112};
struct Builtin builtin110 = {false, "HTTP-EXT", "", "", Filter::serviceOperNotEqual, "9080", "", Filter::serviceOperEqual, &builtin111};
struct Builtin builtin109 = {false, "HTTP-EXT", "", "", Filter::serviceOperNotEqual, "8888", "", Filter::serviceOperEqual, &builtin110};
struct Builtin builtin108 = {false, "HTTP-EXT", "", "", Filter::serviceOperNotEqual, "8200", "", Filter::serviceOperEqual, &builtin109};
struct Builtin builtin107 = {false, "HTTP-EXT", "", "", Filter::serviceOperNotEqual, "8100", "", Filter::serviceOperEqual, &builtin108};
struct Builtin builtin106 = {false, "HTTP-EXT", "", "", Filter::serviceOperNotEqual, "8081", "", Filter::serviceOperEqual, &builtin107};
struct Builtin builtin105 = {false, "HTTP-EXT", "", "", Filter::serviceOperNotEqual, "8001", "", Filter::serviceOperEqual, &builtin106};
struct Builtin builtin104 = {false, "HTTP-EXT", "TCP", "Any", Filter::serviceOperAny, "7001", "", Filter::serviceOperEqual, &builtin105};
struct Builtin builtin103 = {false, "HTTP", "TCP", "Any", Filter::serviceOperAny, "80", "", Filter::serviceOperEqual, &builtin104};
struct Builtin builtin102 = {false, "H.323", "", "", Filter::serviceOperNotEqual, "1719", "", Filter::serviceOperEqual, &builtin103};
struct Builtin builtin101 = {false, "H.323", "", "", Filter::serviceOperNotEqual, "1731", "", Filter::serviceOperEqual, &builtin102};
struct Builtin builtin100 = {false, "H.323", "", "", Filter::serviceOperNotEqual, "522", "", Filter::serviceOperEqual, &builtin101};
struct Builtin builtin99 = {false, "H.323", "", "", Filter::serviceOperNotEqual, "389", "", Filter::serviceOperEqual, &builtin100};
struct Builtin builtin98 = {false, "H.323", "UDP", "", Filter::serviceOperNotEqual, "1503", "", Filter::serviceOperEqual, &builtin99};
struct Builtin builtin97 = {false, "H.323", "TCP", "Any", Filter::serviceOperAny, "1720", "", Filter::serviceOperEqual, &builtin98};
struct Builtin builtin96 = {false, "GOPHER", "TCP", "Any", Filter::serviceOperAny, "70", "", Filter::serviceOperEqual, &builtin97};
struct Builtin builtin95 = {false, "GNUTELLA", "TCP", "", Filter::serviceOperNotEqual, "", "", Filter::serviceOperEqual, &builtin96};
struct Builtin builtin94 = {false, "GNUTELLA", "UDP", "Any", Filter::serviceOperAny, "6346", "6347", Filter::serviceOperRange, &builtin95};
struct Builtin builtin93 = {false, "FTP-PUT", "TCP", "Any", Filter::serviceOperAny, "21", "", Filter::serviceOperEqual, &builtin94};
struct Builtin builtin92 = {false, "FTP-GET", "TCP", "Any", Filter::serviceOperAny, "21", "", Filter::serviceOperEqual, &builtin93};
struct Builtin builtin91 = {false, "FTP", "TCP", "Any", Filter::serviceOperAny, "21", "", Filter::serviceOperEqual, &builtin92};
struct Builtin builtin90 = {false, "FINGER", "TCP", "Any", Filter::serviceOperAny, "79", "", Filter::serviceOperEqual, &builtin91};
struct Builtin builtin89 = {false, "ECHO", "TCP", "", Filter::serviceOperNotEqual, "", "", Filter::serviceOperEqual, &builtin90};
struct Builtin builtin88 = {false, "ECHO", "UDP", "Any", Filter::serviceOperAny, "7", "", Filter::serviceOperEqual, &builtin89};
struct Builtin builtin87 = {false, "DNS", "TCP", "", Filter::serviceOperNotEqual, "", "", Filter::serviceOperEqual, &builtin88};
struct Builtin builtin86 = {false, "DNS", "UDP", "Any", Filter::serviceOperAny, "53", "", Filter::serviceOperEqual, &builtin87};
struct Builtin builtin85 = {false, "DISCARD", "TCP", "", Filter::serviceOperNotEqual, "", "", Filter::serviceOperEqual, &builtin86};
struct Builtin builtin84 = {false, "DISCARD", "UDP", "Any", Filter::serviceOperAny, "9", "", Filter::serviceOperEqual, &builtin85};
struct Builtin builtin83 = {false, "DHCP-RELAY", "", "", Filter::serviceOperNotEqual, "68", "", Filter::serviceOperEqual, &builtin84};
struct Builtin builtin82 = {false, "DHCP-RELAY", "UDP", "Any", Filter::serviceOperAny, "67", "", Filter::serviceOperEqual, &builtin83};
struct Builtin builtin81 = {false, "CHARGEN", "UDP", "", Filter::serviceOperNotEqual, "", "", Filter::serviceOperEqual, &builtin82};
struct Builtin builtin80 = {false, "CHARGEN", "TCP", "Any", Filter::serviceOperAny, "19", "", Filter::serviceOperEqual, &builtin81};
struct Builtin builtin79 = {false, "BGP", "TCP", "Any", Filter::serviceOperAny, "179", "", Filter::serviceOperEqual, &builtin80};
struct Builtin builtin78 = {false, "AOL", "TCP", "Any", Filter::serviceOperAny, "5190", "5194", Filter::serviceOperRange, &builtin79};
struct Builtin builtin77 = {false, "GTP", "", "", Filter::serviceOperNotEqual, "2152", "", Filter::serviceOperEqual, &builtin78};
struct Builtin builtin76 = {false, "GTP", "TCP", "", Filter::serviceOperNotEqual, "3386", "", Filter::serviceOperEqual, &builtin77};
struct Builtin builtin75 = {false, "GTP", "UDP", "Any", Filter::serviceOperAny, "2123", "", Filter::serviceOperEqual, &builtin76};
struct Builtin builtin74 = {false, "MGCP-CA", "UDP", "Any", Filter::serviceOperAny, "2727", "", Filter::serviceOperEqual, &builtin75};
struct Builtin builtin123 = {false, "MGCP", "UDP", "Any", Filter::serviceOperAny, "2427", "", Filter::serviceOperEqual, &builtin74};
struct Builtin builtin73 = {false, "MGCP-UA", "UDP", "Any", Filter::serviceOperAny, "2427", "", Filter::serviceOperEqual, &builtin123};
struct Builtin builtin72 = {false, "SCCP", "TCP", "Any", Filter::serviceOperAny, "2000", "", Filter::serviceOperEqual, &builtin73};
struct Builtin builtin71 = {false, "INCOMING-DIP", "TCP", "", Filter::serviceOperNotEqual, "", "", Filter::serviceOperEqual, &builtin72};
struct Builtin builtin70 = {false, "INCOMING-DIP", "UDP", "0", Filter::serviceOperEqual, "0", "", Filter::serviceOperEqual, &builtin71};
struct Builtin builtin69 = {false, "YMSG", "TCP", "Any", Filter::serviceOperAny, "5050", "", Filter::serviceOperEqual, &builtin70};
struct Builtin builtin68 = {false, "X-WINDOWS", "TCP", "Any", Filter::serviceOperAny, "6000", "6063", Filter::serviceOperRange, &builtin69};
struct Builtin builtin67 = {false, "WINFRAME", "TCP", "Any", Filter::serviceOperAny, "1494", "", Filter::serviceOperEqual, &builtin68};
struct Builtin builtin66 = {false, "WHOIS", "TCP", "Any", Filter::serviceOperAny, "43", "", Filter::serviceOperEqual, &builtin67};
struct Builtin builtin65 = {false, "WAIS", "TCP", "Any", Filter::serviceOperAny, "210", "", Filter::serviceOperEqual, &builtin66};
struct Builtin builtin64 = {false, "VNC", "", "", Filter::serviceOperNotEqual, "5900", "", Filter::serviceOperEqual, &builtin65};
struct Builtin builtin63 = {false, "VNC", "TCP", "Any", Filter::serviceOperAny, "5800", "", Filter::serviceOperEqual, &builtin64};
struct Builtin builtin62 = {false, "VDO Live", "TCP", "Any", Filter::serviceOperAny, "7000", "7010", Filter::serviceOperRange, &builtin63};
struct Builtin builtin61 = {false, "UUCP", "UDP", "Any", Filter::serviceOperAny, "540", "", Filter::serviceOperEqual, &builtin62};
struct Builtin builtin60 = {false, "UDP-ANY", "UDP", "Any", Filter::serviceOperAny, "Any", "", Filter::serviceOperNotEqual, &builtin61};
struct Builtin builtin59 = {false, "TRACEROUTE", "UDP", "Any", Filter::serviceOperAny, "33400", "34000", Filter::serviceOperRange, &builtin60};
struct Builtin builtin58 = {false, "TFTP", "UDP", "Any", Filter::serviceOperAny, "69", "", Filter::serviceOperEqual, &builtin59};
struct Builtin builtin57 = {false, "Telnet", "TCP", "Any", Filter::serviceOperAny, "23", "", Filter::serviceOperEqual, &builtin58};
struct Builtin builtin56 = {false, "TCP-ANY", "TCP", "Any", Filter::serviceOperAny, "Any", "", Filter::serviceOperNotEqual, &builtin57};
struct Builtin builtin55 = {false, "TALK", "", "", Filter::serviceOperNotEqual, "518", "", Filter::serviceOperEqual, &builtin56};
struct Builtin builtin54 = {false, "TALK", "UDP", "Any", Filter::serviceOperAny, "517", "", Filter::serviceOperEqual, &builtin55};
struct Builtin builtin53 = {false, "SYSLOG", "UDP", "Any", Filter::serviceOperAny, "514", "", Filter::serviceOperEqual, &builtin54};
struct Builtin builtin52 = {false, "SUN-RPC-PORTMAPPER", "UDP", "", Filter::serviceOperNotEqual, "", "", Filter::serviceOperEqual, &builtin53};
struct Builtin builtin51 = {false, "SUN-RPC-PORTMAPPER", "TCP", "Any", Filter::serviceOperAny, "111", "", Filter::serviceOperEqual, &builtin52};
struct Builtin builtin50 = {false, "SSH", "TCP", "Any", Filter::serviceOperAny, "22", "", Filter::serviceOperEqual, &builtin51};
struct Builtin builtin49 = {false, "SQL*NetV2", "TCP", "Any", Filter::serviceOperAny, "1521", "", Filter::serviceOperEqual, &builtin50};
struct Builtin builtin48 = {false, "SQL*NetV1", "TCP", "Any", Filter::serviceOperAny, "1525", "", Filter::serviceOperEqual, &builtin49};
struct Builtin builtin47 = {false, "SQL Monitor", "UDP", "Any", Filter::serviceOperAny, "1434", "", Filter::serviceOperEqual, &builtin48};
struct Builtin builtin46 = {false, "SMTP", "TCP", "Any", Filter::serviceOperAny, "25", "", Filter::serviceOperEqual, &builtin47};
struct Builtin builtin45 = {false, "SMB", "", "", Filter::serviceOperNotEqual, "445", "", Filter::serviceOperEqual, &builtin46};
struct Builtin builtin44 = {false, "SMB", "TCP", "Any", Filter::serviceOperAny, "139", "", Filter::serviceOperEqual, &builtin45};
struct Builtin builtin43 = {false, "SNMP", "UDP", "Any", Filter::serviceOperAny, "162", "", Filter::serviceOperEqual, &builtin44};
struct Builtin builtin42 = {false, "SNMP", "TCP", "Any", Filter::serviceOperAny, "161", "", Filter::serviceOperEqual, &builtin43};
struct Builtin builtin41 = {false, "SIP", "TCP", "", Filter::serviceOperNotEqual, "", "", Filter::serviceOperEqual, &builtin42};
struct Builtin builtin40 = {false, "SIP", "UDP", "", Filter::serviceOperNotEqual, "5060", "", Filter::serviceOperEqual, &builtin41};
struct Builtin builtin39 = {false, "RTSP", "TCP", "Any", Filter::serviceOperAny, "554", "", Filter::serviceOperEqual, &builtin40};
struct Builtin builtin38 = {false, "RSH", "TCP", "Any", Filter::serviceOperAny, "514", "", Filter::serviceOperEqual, &builtin39};
struct Builtin builtin37 = {false, "RLOGIN", "TCP", "Any", Filter::serviceOperAny, "513", "", Filter::serviceOperEqual, &builtin38};
struct Builtin builtin36 = {false, "RIP", "UDP", "Any", Filter::serviceOperAny, "520", "", Filter::serviceOperEqual, &builtin37};
struct Builtin builtin35 = {false, "REXEC", "TCP", "Any", Filter::serviceOperAny, "512", "", Filter::serviceOperEqual, &builtin36};
struct Builtin builtin34 = {false, "Real Media", "", "", Filter::serviceOperNotEqual, "554", "", Filter::serviceOperEqual, &builtin35};
struct Builtin builtin33 = {false, "Real Media", "TCP", "Any", Filter::serviceOperAny, "7070", "", Filter::serviceOperEqual, &builtin34};
struct Builtin builtin32 = {false, "Radius", "", "", Filter::serviceOperNotEqual, "1813", "", Filter::serviceOperEqual, &builtin33};
struct Builtin builtin31 = {false, "Radius", "UDP", "Any", Filter::serviceOperAny, "1812", "", Filter::serviceOperEqual, &builtin32};
struct Builtin builtin30 = {false, "PPTP", "TCP", "Any", Filter::serviceOperAny, "1723", "", Filter::serviceOperEqual, &builtin31};
struct Builtin builtin29 = {false, "POP3", "TCP", "Any", Filter::serviceOperAny, "110", "", Filter::serviceOperEqual, &builtin30};
struct Builtin builtin28 = {false, "PC Anywhere", "", "", Filter::serviceOperNotEqual, "5631", "", Filter::serviceOperEqual, &builtin29};
struct Builtin builtin27 = {false, "PC Anywhere", "UDP", "", Filter::serviceOperNotEqual, "22", "", Filter::serviceOperEqual, &builtin28};
struct Builtin builtin26 = {false, "PC Anywhere", "TCP", "Any", Filter::serviceOperAny, "5632", "", Filter::serviceOperEqual, &builtin27};
struct Builtin builtin25 = {false, "NTP", "UDP", "Any", Filter::serviceOperAny, "123", "", Filter::serviceOperEqual, &builtin26};
struct Builtin builtin24 = {false, "NSM", "", "", Filter::serviceOperNotEqual, "15400", "", Filter::serviceOperEqual, &builtin25};
struct Builtin builtin23 = {false, "NSM", "", "", Filter::serviceOperNotEqual, "11122", "", Filter::serviceOperEqual, &builtin24};
struct Builtin builtin22 = {false, "NSM", "", "", Filter::serviceOperNotEqual, "7800", "", Filter::serviceOperEqual, &builtin23};
struct Builtin builtin21 = {false, "NSM", "UDP", "", Filter::serviceOperNotEqual, "7204", "", Filter::serviceOperEqual, &builtin22};
struct Builtin builtin20 = {false, "NSM", "TCP", "Any", Filter::serviceOperAny, "69", "", Filter::serviceOperEqual, &builtin21};
struct Builtin builtin19 = {false, "NS Global Pro", "TCP", "", Filter::serviceOperNotEqual, "15400", "15403", Filter::serviceOperRange, &builtin20};
struct Builtin builtin18 = {false, "NS Global Pro", "UDP", "Any", Filter::serviceOperAny, "15397", "", Filter::serviceOperEqual, &builtin19};
struct Builtin builtin17 = {false, "NS Global", "UDP", "", Filter::serviceOperNotEqual, "", "", Filter::serviceOperEqual, &builtin18};
struct Builtin builtin16 = {false, "NS Global", "TCP", "Any", Filter::serviceOperAny, "15397", "", Filter::serviceOperEqual, &builtin17};
struct Builtin builtin15 = {false, "NNTP", "TCP", "Any", Filter::serviceOperAny, "119", "", Filter::serviceOperEqual, &builtin16};
struct Builtin builtin14 = {false, "NFS", "UDP", "", Filter::serviceOperNotEqual, "2049", "", Filter::serviceOperEqual, &builtin15};
struct Builtin builtin13 = {false, "NFS", "TCP", "Any", Filter::serviceOperAny, "111", "", Filter::serviceOperEqual, &builtin14};
struct Builtin builtin12 = {false, "NetMeeting", "", "", Filter::serviceOperNotEqual, "1719", "", Filter::serviceOperEqual, &builtin13};
struct Builtin builtin11 = {false, "NetMeeting", "", "", Filter::serviceOperNotEqual, "1731", "", Filter::serviceOperEqual, &builtin12};
struct Builtin builtin10 = {false, "NetMeeting", "", "", Filter::serviceOperNotEqual, "522", "", Filter::serviceOperEqual, &builtin11};
struct Builtin builtin9  = {false, "NetMeeting", "", "", Filter::serviceOperNotEqual, "389", "", Filter::serviceOperEqual, &builtin10};
struct Builtin builtin8  = {false, "NetMeeting", "TCP", "", Filter::serviceOperNotEqual, "1503", "", Filter::serviceOperEqual, &builtin9};
struct Builtin builtin7  = {false, "NetMeeting", "UDP", "Any", Filter::serviceOperAny, "1720", "", Filter::serviceOperEqual, &builtin8};
struct Builtin builtin6  = {false, "NBDB", "UDP", "Any", Filter::serviceOperAny, "138", "", Filter::serviceOperEqual, &builtin7};
struct Builtin builtin5  = {false, "NBNAME", "UDP", "Any", Filter::serviceOperAny, "137", "", Filter::serviceOperEqual, &builtin6};
struct Builtin builtin4  = {false, "MS-SQL", "TCP", "Any", Filter::serviceOperAny, "1433", "", Filter::serviceOperEqual, &builtin5};
struct Builtin builtin3  = {false, "MS-RPC-EPM", "UDP", "", Filter::serviceOperNotEqual, "", "", Filter::serviceOperEqual, &builtin4};
struct Builtin builtin2  = {false, "MS-RPC-EPM", "TCP", "Any", Filter::serviceOperAny, "135", "", Filter::serviceOperEqual, &builtin3};
struct Builtin builtin1  = {false, "MSN", "TCP", "Any", Filter::serviceOperAny, "1863", "", Filter::serviceOperEqual, &builtin2};
struct Builtin builtin   = {false, "MAIL", "TCP", "Any", Filter::serviceOperAny, "25", "", Filter::serviceOperEqual, &builtin1};


int ScreenOSFilter::processDeviceSpecificDefaults(Device *device)
{
	// Variables...
	filterListConfig *filterListPointer = 0;
	filterConfig *filterPointer = 0;
	filterObjectConfig *objectPointer = 0;
	filterObjectConfig *objectSubPointer = 0;
	netObjectListConfig *serviceListPointer = 0;
	netObjectListConfig *builtinListPointer = 0;
	Builtin *builtinPointer = 0;

	// Init service list...
	serviceListPointer = getOnlyObjectList("Service Objects");

	// Add any builtin predefined objects that are used...
	filterListPointer = filterList;
	while (filterListPointer != 0)
	{
		filterPointer = filterListPointer->filter;
		while (filterPointer != 0)
		{
			objectPointer = 0;
			if (filterPointer->destinationService != 0)
			{
				if (filterPointer->destinationService->type != anyObject)
				{
					if (serviceListPointer != 0)
						objectPointer = getObject(filterPointer->destinationService->name.c_str(), serviceListPointer);

					// If this object has not been found, check the builtin service list...
					if (objectPointer == 0)
					{
						builtinPointer = &builtin;
						while (builtinPointer != 0)
						{
							if (strcasecmp(builtinPointer->name, filterPointer->destinationService->name.c_str()) == 0)
							{
								if (builtinPointer->added == true)
									builtinPointer = 0;
								else
								{
									if (builtinListPointer == 0)
									{
										builtinListPointer = getObjectList(i18n("Predefined service objects"));
										builtinListPointer->title = serviceObjectTitle;
										builtinListPointer->description = serviceObjectDescription;
										builtinListPointer->type = enhancedServiceObject;
									}
									builtinPointer->added = true;

									// Create object...
									objectPointer = getObject(filterPointer->destinationService->name.c_str(), builtinListPointer);
									if (objectPointer == 0)
									{
										objectPointer = addObject(builtinListPointer);
										objectPointer->name.assign(filterPointer->destinationService->name.c_str());
										objectPointer->type = enhancedServiceObject;
										objectPointer->serviceOper= serviceOperEqual;
									}

									// Add protocol...
									if (strcmp(builtinPointer->protocol, "") != 0)
									{
										objectSubPointer = addObject(objectPointer, protocol);
										objectSubPointer->type = protocolObject;
										objectSubPointer->name.assign(builtinPointer->protocol);
									}

									// Add source port...
									if (strcmp(builtinPointer->source, "") != 0)
									{
										objectSubPointer = addObject(objectPointer, sourceService);
										objectSubPointer->type = portObject;
										objectSubPointer->name.assign(builtinPointer->source);
										objectSubPointer->serviceOper = builtinPointer->sourceType;
									}

									// Add destination port...
									if (strcmp(builtinPointer->dest, "") != 0)
									{
										objectSubPointer = addObject(objectPointer, destinationService);
										objectSubPointer->type = portObject;
										objectSubPointer->name.assign(builtinPointer->dest);
										objectSubPointer->netmask.assign(builtinPointer->destEnd);
										objectSubPointer->serviceOper = builtinPointer->destType;
									}
								}
							}
							if (builtinPointer != 0)
								builtinPointer = builtinPointer->next;
						}
					}
				}
			}

			filterPointer = filterPointer->next;
		}

		filterListPointer = filterListPointer->next;
	}

	return 0;
}

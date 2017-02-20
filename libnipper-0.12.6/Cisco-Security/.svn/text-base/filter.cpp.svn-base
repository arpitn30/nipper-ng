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


CiscoSecFilter::CiscoSecFilter()
{
	// Filter text...
	standardACLText = i18n("Standard *ABBREV*ACL*-ABBREV*");
	standardACLDescription = i18n("Standard *ABBREV*ACLs*-ABBREV* only define the source address and process the packet solely based on that, they are typically used to restrict access to device services or protocols.");
	extendedACLText = i18n("Extended *ABBREV*ACL*-ABBREV*");
	extendedACLDescription = i18n("Extended *ABBREV*ACLs*-ABBREV* permit or deny network traffic based on the source and destination addresses and network ports. Extended *ABBREV*ACLs*-ABBREV* are used for checks on traffic passing through the *DEVICENAME*.");
	conduitText = i18n("Conduit");
	conduitDescription = i18n("Conduit rules permit or deny network traffic based on the source and destination addresses and network ports. Conduit rules are used for checks on incoming external traffic passing through the *DEVICENAME*. It is worth noting that conduit configurations should be considered legacy and have been replaced with extended *ABBREV*ACL*-ABBREV*");
	outboundText = i18n("Outbound");
	outboundDescription = i18n("Outbound rules permit or deny network traffic based on the address, network port(s) and protocol used. Outbound rules are used for checks on outgoing external traffic and act differently to other network filtering configurations where the first rule that matches is the one that takes precedence. Exception rules can be configured to exclude addresses and ports from the previous permit or deny rule . It is worth noting that outbound configurations should be considered legacy and have been replaced with *ABBREV*ACL*-ABBREV*");

	// Object options...
	networkObjectName = i18n("Network Objects");			// The name for the object (used in config report)
	networkObjectDescription = i18n("Network object groups are used to define a group of hosts and networks in order to ease the management of the *DEVICETYPE* device. Additionally, object groups can be added to other object groups.");					// The description for the object (config report)
	protocolObjectName = i18n("Protocol Objects");			// The name for the object (used in config report)
	protocolObjectDescription = i18n("Protocol object groups are used to define a group of network protocols to ease the management of the *DEVICETYPE* device. Additionally, object groups can be added to other object groups.");					// The description for the object (config report)
	icmpObjectName = i18n("*ABBREV*ICMP*-ABBREV* Objects");	// The name for the object (used in config report)
	icmpObjectDescription = i18n("*ABBREV*ICMP*-ABBREV* object groups are used to define a group of *ABBREV*ICMP*-ABBREV* message types in order to ease the management of the *DEVICETYPE* device. Additionally, object groups can be added to other object groups.");						// The description for the object (config report)
	serviceObjectName = i18n("Service Objects");			// The name for the object (used in config report)
	serviceObjectDescription = i18n("Service object groups are used to define a group of network services in order to ease the management of the *DEVICETYPE* device. Additionally, object groups can be added to other object groups.");					// The description for the object (config report)

	// Filter device options...
	logLevelsSupported = true;								// Are log Levels supported
	logOnlyDenySupported = true;							// Is only Deny rule logging supported
	noAccessWithoutFilters = true;							// Is access not granted if no filters are configured
	allowName = i18n("Permit");								// The name given to an allowed filter
	denyName = i18n("Deny");								// The name given to a denied filter
	ruleListsAreAssigned = true;							// Rule lists are assigned to specific elements
	filterConfigTitle = i18n("*ABBREV*ACL*-ABBREV* Configuration");		// The Title for the configuration report section
	filterConfigText = i18n("*ABBREV*ACL*-ABBREV* are sequential lists of apply or deny *ABBREV*ACEs*-ABBREV* that a *DEVICETYPE* device will apply to the network traffic. The *DEVICETYPE* device will check network traffic against the *ABBREV*ACL*-ABBREV* and the first *ABBREV*ACE*-ABBREV* that matches will determine whether the network traffic is permited or denied. If the *DEVICETYPE* device does not have an *ABBREV*ACE*-ABBREV* that applies then the packet is denied.");							// The device specific configuration report section text
	filterConfigText2 = i18n("There are two different types of *ABBREV*ACLs*-ABBREV* on modern Cisco security appliances, standard and extended.");							// The device specific configuration report section text2
	filterIDTitle = i18n("Line");							// The title for the filter ID/line no. table column
	filterListName = i18n("*ABBREV*ACL*-ABBREV*");			// The name of the filter list, for use in text paragraphs
	filterListNamePlaural = i18n("*ABBREV*ACLs*-ABBREV*");	// The name of the filter list, for use in text paragraphs
	filterName = i18n("*ABBREV*ACE*-ABBREV*");				// The name of a filter, for use use in text paragraph
	filterNamePlaural = i18n("*ABBREV*ACEs*-ABBREV*");		// The name of a filter, for use use in text paragraph

	// Issue titles...
	allowAndNotLogIssue = i18n("All Permit *ABBREV*ACE*-ABBREV* Do Not Log");	// The title text for the "All Allow Rules Do Not Log" issue
	allowAndNotLogTable = i18n("permit *ABBREV*ACE*-ABBREV* that do not log");	// The table title text for the "All Allow Rules Do Not Log" issue
	allowAndNotLogConcl = i18n("all permit *ABBREV*ACE*-ABBREV* do not log");	// The conclusions text for the "All Allow Rules Do Not Log" issue
	allowAndNotLogReco = i18n("Configure logging for all *ABBREV*ACE*-ABBREV*");// The recommendations text for the "All Allow Rules Do Not Log" issue
	denyAndNotLogIssue = i18n("All Deny *ABBREV*ACE*-ABBREV* Do Not Log");		// The title text for the "All Allow Rules Do Not Log" issue
	denyAndNotLogTable = i18n("deny *ABBREV*ACE*-ABBREV* that do not log");		// The table title text for the "All Allow Rules Do Not Log" issue
	denyAndNotLogConcl = i18n("all deny *ABBREV*ACE*-ABBREV* do not log");		// The conclusions text for the "All Allow Rules Do Not Log" issue
	configRuleLogging = i18n("Logging can be enabled on extended *COMMAND*access-list*-COMMAND* with the following command:*CODE**COMMAND*access-list *CMDUSER*list-id*-CMDUSER* *CMDREQUIRE*deny *CMDOR* permit*-CMDREQUIRE* *CMDUSER*protocol*-CMDUSER* *CMDUSER*source*-CMDUSER* *CMDUSER*destination*-CMDUSER* log*-COMMAND**-CODE*");								// The text describing how to configure logging for filter rules
	noFilteringIssue = i18n("No *ABBREV*ACL*-ABBREV* Were Configured");			// The title text for the "No filtering" issue
	noFilteringRec = i18n("Configure *ABBREV*ACL*-ABBREV* to restrict access");	// The title text for the "No filtering" recommendation
	noFilteringCon = i18n("no *ABBREV*ACL*-ABBREV* were configured");			// The title text for the "No filtering" conclusion
	legacyIssueFinding = i18n("*DEVICETYPE* device network filtering used to be configured using *COMMAND*conduit*-COMMAND* commands to configure incoming connections and *COMMAND*outbound*-COMMAND* commands to configure users access. Those commands have since been replaced with *ABBREV*ACLs*-ABBREV* which offer additional facilities and greater flexibility, although some *DEVICEOS* versions still support the commands for backwards compatability. *COMPANY* determined that legacy network filtering was configured on *DEVICENAME*.");								// The finding for the legacy issue
	legacyIssueImpact = i18n("Although the legacy configuration does not pose a direct security issue, they don't offer the more advanced configuration options.");								// The impact for the legacy issue
	legacyIssueEase = i18n("The legacy configuration applies to incoming and outbound network traffic.");									// The ease for the legacy issue
	legacyIssueRec = i18n("*COMPANY* recommends that the legacy network filtering is moved to *ABBREV*ACLs*-ABBREV* as soon as possible. Cisco provides documentation  and procedures for the transfer of the network filtering to *ABBREV*ACLs*-ABBREV*.");									// The recommendation for the legacy issue
}


int CiscoSecFilter::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	filterObjectConfig *filterObjectPointer = 0;
	filterConfig *filterPointer = 0;
	filterListConfig *filterListPointer = 0;
	netObjectListConfig *objectListPointer = 0;
	fpos_t filePosition;
	string tempString;
	int tempInt = 0;
	int tempInt2 = 0;
	bool create = false;

	// Extended ACL...
	if (strcmp(command->part(0), "access-list") == 0)
	{
		if ((strcmp(command->part(2), "extended") == 0) || (strcmp(command->part(2), "permit") == 0) || (strcmp(command->part(2), "deny") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sExtended ACL Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			filterListPointer = getFilterList(command->part(1));
			filterListPointer->type = extendedACLText;
			filterListPointer->typeDescription = extendedACLDescription;
			filterListPointer->sourceOnly = false;
			filterListPointer->loggingSupport = true;
			filterListPointer->supportsTime = true;
			filterListPointer->disabledFilterSupport = true;
			filterListPointer->sourceServiceSupported = true;
			filterPointer = addFilter(filterListPointer);

			if (strcmp(command->part(2), "extended") == 0)
				tempInt = 3;
			else
				tempInt = 2;

			// Permit/Deny
			if (strcmp(command->part(tempInt), "permit") == 0)
				filterPointer->action = allowAction;
			else
			{
				filterPointer->action = denyAction;
				filterPointer->log = true;
			}
			filterPointer->logLevel = 6;
			tempInt++;

			// Protocol
			filterObjectPointer = addFilterObject(filterPointer, protocol);
			if (strcmp(command->part(tempInt), "object-group") == 0)
			{
				tempInt++;
				filterObjectPointer->type = groupObject;
				tempInt2 = atoi(command->part(tempInt));
				if ((tempInt2 > 0) || (strcmp(command->part(tempInt), "0") == 0))
				{
					filterObjectPointer->name.assign(device->getProtocol(tempInt2));
					if (filterObjectPointer->name.empty())
						filterObjectPointer->name.assign(command->part(tempInt));
				}
				else
					filterObjectPointer->name.assign(command->part(tempInt));
				filterObjectPointer->serviceOper = serviceOperEqual;
			}
			else
			{
				filterObjectPointer->type = protocolObject;
				tempInt2 = atoi(command->part(tempInt));
				if ((tempInt2 > 0) || (strcmp(command->part(tempInt), "0") == 0))
				{
					filterObjectPointer->name.assign(device->getProtocol(tempInt2));
					if (filterObjectPointer->name.empty())
						filterObjectPointer->name.assign(command->part(tempInt));
				}
				else
					filterObjectPointer->name.assign(command->part(tempInt));
				filterObjectPointer->serviceOper = serviceOperEqual;
			}
			tempInt++;

			// Source
			filterObjectPointer = addFilterObject(filterPointer, source);
			if (strcasecmp(command->part(tempInt), "any") == 0)
			{
				filterObjectPointer->name.assign(i18n("Any"));
				filterObjectPointer->type = anyObject;
				filterObjectPointer->serviceOper = serviceOperEqual;
			}
			else if (strcasecmp(command->part(tempInt), "host") == 0)
			{
				tempInt++;
				filterObjectPointer->name.assign(command->part(tempInt));
				filterObjectPointer->type = hostObject;
				filterObjectPointer->serviceOper = serviceOperEqual;
			}
			else if (strcasecmp(command->part(tempInt), "interface") == 0)
			{
				tempInt++;
				filterObjectPointer->name.assign(command->part(tempInt));
				filterObjectPointer->type = interfaceObject;
				filterObjectPointer->serviceOper = serviceOperEqual;
			}
			else if (strcasecmp(command->part(tempInt), "object-group") == 0)
			{
				tempInt++;
				filterObjectPointer->name.assign(command->part(tempInt));
				filterObjectPointer->type = groupObject;
				filterObjectPointer->serviceOper = serviceOperEqual;
			}
			else
			{
				filterObjectPointer->name.assign(command->part(tempInt));
				tempInt++;
				filterObjectPointer->netmask.assign(command->part(tempInt));
				filterObjectPointer->type = networkObject;
				filterObjectPointer->serviceOper = serviceOperEqual;
			}
			tempInt++;

			// Source Service
			if (strcmp(command->part(tempInt), "lt") == 0)
			{
				tempInt++;
				filterObjectPointer = addFilterObject(filterPointer, sourceService);
				filterObjectPointer->name.assign(command->part(tempInt));
				filterObjectPointer->serviceOper = serviceOperLessThan;
				filterObjectPointer->type = serviceObject;
				tempInt++;
			}
			else if (strcmp(command->part(tempInt), "gt") == 0)
			{
				tempInt++;
				filterObjectPointer = addFilterObject(filterPointer, sourceService);
				filterObjectPointer->name.assign(command->part(tempInt));
				filterObjectPointer->serviceOper = serviceOperGreaterThan;
				filterObjectPointer->type = serviceObject;
				tempInt++;
			}
			else if (strcmp(command->part(tempInt), "eq") == 0)
			{
				tempInt++;
				filterObjectPointer = addFilterObject(filterPointer, sourceService);
				filterObjectPointer->name.assign(command->part(tempInt));
				filterObjectPointer->serviceOper = serviceOperEqual;
				filterObjectPointer->type = serviceObject;
				tempInt++;
			}
			else if (strcmp(command->part(tempInt), "neq") == 0)
			{
				tempInt++;
				filterObjectPointer = addFilterObject(filterPointer, sourceService);
				filterObjectPointer->name.assign(command->part(tempInt));
				filterObjectPointer->serviceOper = serviceOperNotEqual;
				filterObjectPointer->type = serviceObject;
				tempInt++;
			}
			else if (strcmp(command->part(tempInt), "range") == 0)
			{
				tempInt++;
				filterObjectPointer = addFilterObject(filterPointer, sourceService);
				filterObjectPointer->name.assign(command->part(tempInt));
				tempInt++;
				filterObjectPointer->netmask.assign(command->part(tempInt));
				filterObjectPointer->serviceOper = serviceOperRange;
				filterObjectPointer->type = serviceObject;
				tempInt++;
			}
			else if (strcmp(command->part(tempInt), "object-group") == 0)
			{
				create = false;
				filterObjectPointer = getObject(command->part(tempInt + 1));
				if (filterObjectPointer != 0)
				{
					if (filterObjectPointer->type == serviceObject)
						create = true;
				}
				if (create == true)
				{
					tempInt++;
					filterObjectPointer = addFilterObject(filterPointer, sourceService);
					filterObjectPointer->name.assign(command->part(tempInt));
					filterObjectPointer->serviceOper = serviceOperEqual;
					filterObjectPointer->type = serviceObject;
					tempInt++;
				}
			}

			// Destination...
			filterObjectPointer = addFilterObject(filterPointer, destination);
			if (strcasecmp(command->part(tempInt), "any") == 0)
			{
				filterObjectPointer->name.assign(i18n("Any"));
				filterObjectPointer->type = anyObject;
				filterObjectPointer->serviceOper = serviceOperEqual;
			}
			else if (strcasecmp(command->part(tempInt), "host") == 0)
			{
				tempInt++;
				filterObjectPointer->name.assign(command->part(tempInt));
				filterObjectPointer->type = hostObject;
				filterObjectPointer->serviceOper = serviceOperEqual;
			}
			else if (strcasecmp(command->part(tempInt), "interface") == 0)
			{
				tempInt++;
				filterObjectPointer->name.assign(command->part(tempInt));
				filterObjectPointer->type = interfaceObject;
				filterObjectPointer->serviceOper = serviceOperEqual;
			}
			else if (strcasecmp(command->part(tempInt), "object-group") == 0)
			{
				tempInt++;
				filterObjectPointer->name.assign(command->part(tempInt));
				filterObjectPointer->type = groupObject;
				filterObjectPointer->serviceOper = serviceOperEqual;
			}
			else
			{
				filterObjectPointer->name.assign(command->part(tempInt));
				tempInt++;
				filterObjectPointer->netmask.assign(command->part(tempInt));
				filterObjectPointer->type = networkObject;
				filterObjectPointer->serviceOper = serviceOperEqual;
			}
			tempInt++;

			// Destination service...
			if (strcmp(command->part(tempInt), "lt") == 0)
			{
				tempInt++;
				filterObjectPointer = addFilterObject(filterPointer, destinationService);
				filterObjectPointer->name.assign(command->part(tempInt));
				filterObjectPointer->serviceOper = serviceOperLessThan;
				filterObjectPointer->type = serviceObject;
				tempInt++;
			}
			else if (strcmp(command->part(tempInt), "gt") == 0)
			{
				tempInt++;
				filterObjectPointer = addFilterObject(filterPointer, destinationService);
				filterObjectPointer->name.assign(command->part(tempInt));
				filterObjectPointer->serviceOper = serviceOperGreaterThan;
				filterObjectPointer->type = serviceObject;
				tempInt++;
			}
			else if (strcmp(command->part(tempInt), "eq") == 0)
			{
				tempInt++;
				filterObjectPointer = addFilterObject(filterPointer, destinationService);
				filterObjectPointer->name.assign(command->part(tempInt));
				filterObjectPointer->serviceOper = serviceOperEqual;
				filterObjectPointer->type = serviceObject;
				tempInt++;
			}
			else if (strcmp(command->part(tempInt), "neq") == 0)
			{
				tempInt++;
				filterObjectPointer = addFilterObject(filterPointer, destinationService);
				filterObjectPointer->name.assign(command->part(tempInt));
				filterObjectPointer->serviceOper = serviceOperNotEqual;
				filterObjectPointer->type = serviceObject;
				tempInt++;
			}
			else if (strcmp(command->part(tempInt), "range") == 0)
			{
				tempInt++;
				filterObjectPointer = addFilterObject(filterPointer, destinationService);
				filterObjectPointer->name.assign(command->part(tempInt));
				tempInt++;
				filterObjectPointer->netmask.assign(command->part(tempInt));
				filterObjectPointer->serviceOper = serviceOperRange;
				filterObjectPointer->type = serviceObject;
				tempInt++;
			}
			else if (strcmp(command->part(tempInt), "object-group") == 0)
			{
				tempInt++;
				filterObjectPointer = addFilterObject(filterPointer, destinationService);
				filterObjectPointer->name.assign(command->part(tempInt));
				filterObjectPointer->serviceOper = serviceOperEqual;
				filterObjectPointer->type = serviceObject;
				tempInt++;
			}

			while (tempInt < command->parts)
			{
				// Inactive
				if (strcmp(command->part(tempInt), "inactive") == 0)
					filterPointer->enabled = false;

				// Time
				else if (strcmp(command->part(tempInt), "time-range") == 0)
				{
					tempInt++;
					filterObjectPointer = addFilterObject(filterPointer, timeLimit);
					filterObjectPointer->name.assign(command->part(tempInt));
					filterObjectPointer->serviceOper = serviceOperEqual;
					filterObjectPointer->type = timeObject;
				}

				// Log
				else if (strcmp(command->part(tempInt), "log") == 0)
				{
					tempInt++;
					if ((strcmp(command->part(tempInt), "interval") != 0) || (strcmp(command->part(tempInt), "disable") != 0) || (strcmp(command->part(tempInt), "default") != 0))
					{
						filterPointer->logLevel = atoi(command->part(tempInt));
						tempInt++;
					}
					if (strcmp(command->part(tempInt), "disable") == 0)
						filterPointer->log = false;
				}

				tempInt++;
			}
		}

		// Standard ACL...
		else if (strcmp(command->part(2), "standard") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sStandard ACL Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			filterListPointer = getFilterList(command->part(1));
			filterListPointer->sourceOnly = true;
			filterListPointer->type = standardACLText;
			filterListPointer->typeDescription = standardACLDescription;
			filterPointer = addFilter(filterListPointer);

			// Permit/Deny
			if (strcmp(command->part(3), "permit") == 0)
				filterPointer->action = allowAction;
			else
			{
				filterPointer->action = denyAction;
				filterPointer->log = true;
			}

			// Address
			filterObjectPointer = addFilterObject(filterPointer, source);
			filterObjectPointer->serviceOper = serviceOperEqual;
			if (strcasecmp(command->part(4), "any") == 0)
			{
				filterObjectPointer->name.assign(i18n("Any"));
				filterObjectPointer->type = anyObject;
				filterObjectPointer->serviceOper = serviceOperEqual;
			}
			else if (strcasecmp(command->part(4), "host") == 0)
			{
				filterObjectPointer->name.assign(command->part(5));
				filterObjectPointer->type = hostObject;
			}
			else
			{
				filterObjectPointer->name.assign(command->part(4));
				filterObjectPointer->netmask.assign(command->part(5));
				filterObjectPointer->type = networkObject;
			}
		}

		// Remark ACL...
		else if (strcmp(command->part(2), "remark") == 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sRemark ACL Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			filterListPointer = getFilterList(command->part(1));
			filterPointer = addFilter(filterListPointer);
			filterPointer->remarkFilter = true;
			filterPointer->number--;
			filterPointer->comment.assign(strstr(line, command->part(3)));
		}

		// All others...
		else
			device->lineNotProcessed(line);
	}

	// Conduit...
	else if (strcmp(command->part(0), "conduit") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sConduit Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		filterListPointer = getFilterList("incoming");
		filterListPointer->type = conduitText;
		filterListPointer->typeDescription = conduitDescription;
		filterListPointer->legacyType = true;
		filterListPointer->sourceOnly = false;
		filterListPointer->sourceServiceSupported = true;
		filterListPointer->loggingSupport = false;
		filterListPointer->supportsTime = false;
		filterPointer = addFilter(filterListPointer);
		tempInt = 1;

		// Permit/Deny
		if (strcmp(command->part(tempInt), "permit") == 0)
			filterPointer->action = allowAction;
		else
			filterPointer->action = denyAction;
		tempInt++;

		// Protocol
		filterObjectPointer = addFilterObject(filterPointer, protocol);
		if (strcmp(command->part(tempInt), "object-group") == 0)
		{
			tempInt++;
			filterObjectPointer->type = groupObject;
			filterObjectPointer->name.assign(command->part(tempInt));
			filterObjectPointer->serviceOper = serviceOperEqual;
		}
		else
		{
			filterObjectPointer->type = protocolObject;
			tempInt2 = atoi(command->part(tempInt));
			if ((tempInt2 != 0) ||( strcmp(command->part(tempInt), "0") == 0))
				filterObjectPointer->name.assign(device->getProtocol(tempInt2));
			else
				filterObjectPointer->name.assign(command->part(tempInt));
			filterObjectPointer->serviceOper = serviceOperEqual;
		}
		tempInt++;

		// Destination
		filterObjectPointer = addFilterObject(filterPointer, destination);
		if (strcasecmp(command->part(tempInt), "any") == 0)
		{
			filterObjectPointer->name.assign(i18n("Any"));
			filterObjectPointer->type = anyObject;
			filterObjectPointer->serviceOper = serviceOperEqual;
		}
		else if (strcasecmp(command->part(tempInt), "host") == 0)
		{
			tempInt++;
			filterObjectPointer->name.assign(command->part(tempInt));
			filterObjectPointer->type = hostObject;
			filterObjectPointer->serviceOper = serviceOperEqual;
		}
		else if (strcasecmp(command->part(tempInt), "object-group") == 0)
		{
			tempInt++;
			filterObjectPointer->name.assign(command->part(tempInt));
			filterObjectPointer->type = groupObject;
			filterObjectPointer->serviceOper = serviceOperEqual;
		}
		else
		{
			filterObjectPointer->name.assign(command->part(tempInt));
			tempInt++;
			filterObjectPointer->netmask.assign(command->part(tempInt));
			filterObjectPointer->type = networkObject;
			filterObjectPointer->serviceOper = serviceOperEqual;
			if (((filterObjectPointer->name.compare("0.0.0.0") == 0) || (filterObjectPointer->name.compare("0") == 0)) && ((filterObjectPointer->netmask.compare("0.0.0.0") == 0) || (filterObjectPointer->netmask.compare("0") == 0)))
			{
				filterObjectPointer->type = anyObject;
				filterObjectPointer->serviceOper = serviceOperEqual;
			}
			else if (filterObjectPointer->name.compare("255.255.255.255") == 0)
				filterObjectPointer->type = hostObject;
		}
		tempInt++;

		// Destination Service
		if (strcmp(command->part(tempInt), "lt") == 0)
		{
			tempInt++;
			filterObjectPointer = addFilterObject(filterPointer, destinationService);
			filterObjectPointer->name.assign(command->part(tempInt));
			filterObjectPointer->serviceOper = serviceOperLessThan;
			filterObjectPointer->type = serviceObject;
			tempInt++;
		}
		else if (strcmp(command->part(tempInt), "gt") == 0)
		{
			tempInt++;
			filterObjectPointer = addFilterObject(filterPointer, destinationService);
			filterObjectPointer->name.assign(command->part(tempInt));
			filterObjectPointer->serviceOper = serviceOperGreaterThan;
			filterObjectPointer->type = serviceObject;
			tempInt++;
		}
		else if (strcmp(command->part(tempInt), "eq") == 0)
		{
			tempInt++;
			filterObjectPointer = addFilterObject(filterPointer, destinationService);
			filterObjectPointer->name.assign(command->part(tempInt));
			filterObjectPointer->serviceOper = serviceOperEqual;
			filterObjectPointer->type = serviceObject;
			tempInt++;
		}
		else if (strcmp(command->part(tempInt), "neq") == 0)
		{
			tempInt++;
			filterObjectPointer = addFilterObject(filterPointer, destinationService);
			filterObjectPointer->name.assign(command->part(tempInt));
			filterObjectPointer->serviceOper = serviceOperNotEqual;
			filterObjectPointer->type = serviceObject;
			tempInt++;
		}
		else if (strcmp(command->part(tempInt), "range") == 0)
		{
			tempInt++;
			filterObjectPointer = addFilterObject(filterPointer, destinationService);
			filterObjectPointer->name.assign(command->part(tempInt));
			tempInt++;
			filterObjectPointer->netmask.assign(command->part(tempInt));
			filterObjectPointer->serviceOper = serviceOperRange;
			filterObjectPointer->type = serviceObject;
			tempInt++;
		}
		else if (strcmp(command->part(tempInt), "object-group") == 0)
		{
			create = false;
			filterObjectPointer = getObject(command->part(tempInt + 1));
			if (filterObjectPointer != 0)
			{
				if (filterObjectPointer->type == serviceObject)
					create = true;
			}
			if (create == true)
			{
				tempInt++;
				filterObjectPointer = addFilterObject(filterPointer, destinationService);
				filterObjectPointer->name.assign(command->part(tempInt));
				filterObjectPointer->serviceOper = serviceOperEqual;
				filterObjectPointer->type = serviceObject;
				tempInt++;
			}
		}

		// Source...
		filterObjectPointer = addFilterObject(filterPointer, source);
		if (strcasecmp(command->part(tempInt), "any") == 0)
		{
			filterObjectPointer->name.assign(i18n("Any"));
			filterObjectPointer->type = anyObject;
			filterObjectPointer->serviceOper = serviceOperEqual;
		}
		else if (strcasecmp(command->part(tempInt), "host") == 0)
		{
			tempInt++;
			filterObjectPointer->name.assign(command->part(tempInt));
			filterObjectPointer->type = hostObject;
			filterObjectPointer->serviceOper = serviceOperEqual;
		}
		else if (strcasecmp(command->part(tempInt), "interface") == 0)
		{
			tempInt++;
			filterObjectPointer->name.assign(command->part(tempInt));
			filterObjectPointer->type = interfaceObject;
			filterObjectPointer->serviceOper = serviceOperEqual;
		}
		else if (strcasecmp(command->part(tempInt), "object-group") == 0)
		{
			tempInt++;
			filterObjectPointer->name.assign(command->part(tempInt));
			filterObjectPointer->type = groupObject;
			filterObjectPointer->serviceOper = serviceOperEqual;
		}
		else
		{
			filterObjectPointer->name.assign(command->part(tempInt));
			tempInt++;
			filterObjectPointer->netmask.assign(command->part(tempInt));
			filterObjectPointer->type = networkObject;
			filterObjectPointer->serviceOper = serviceOperEqual;
			if (((filterObjectPointer->name.compare("0.0.0.0") == 0) || (filterObjectPointer->name.compare("0") == 0)) && ((filterObjectPointer->netmask.compare("0.0.0.0") == 0) || (filterObjectPointer->netmask.compare("0") == 0)))
			{
				filterObjectPointer->type = anyObject;
				filterObjectPointer->serviceOper = serviceOperEqual;
			}
			else if (filterObjectPointer->name.compare("255.255.255.255") == 0)
				filterObjectPointer->type = hostObject;
		}
		tempInt++;

		// Source service...
		if (strcmp(command->part(tempInt), "lt") == 0)
		{
			tempInt++;
			filterObjectPointer = addFilterObject(filterPointer, sourceService);
			filterObjectPointer->name.assign(command->part(tempInt));
			filterObjectPointer->serviceOper = serviceOperLessThan;
			filterObjectPointer->type = serviceObject;
			tempInt++;
		}
		else if (strcmp(command->part(tempInt), "gt") == 0)
		{
			tempInt++;
			filterObjectPointer = addFilterObject(filterPointer, sourceService);
			filterObjectPointer->name.assign(command->part(tempInt));
			filterObjectPointer->serviceOper = serviceOperGreaterThan;
			filterObjectPointer->type = serviceObject;
			tempInt++;
		}
		else if (strcmp(command->part(tempInt), "eq") == 0)
		{
			tempInt++;
			filterObjectPointer = addFilterObject(filterPointer, sourceService);
			filterObjectPointer->name.assign(command->part(tempInt));
			filterObjectPointer->serviceOper = serviceOperEqual;
			filterObjectPointer->type = serviceObject;
			tempInt++;
		}
		else if (strcmp(command->part(tempInt), "neq") == 0)
		{
			tempInt++;
			filterObjectPointer = addFilterObject(filterPointer, sourceService);
			filterObjectPointer->name.assign(command->part(tempInt));
			filterObjectPointer->serviceOper = serviceOperNotEqual;
			filterObjectPointer->type = serviceObject;
			tempInt++;
		}
		else if (strcmp(command->part(tempInt), "range") == 0)
		{
			tempInt++;
			filterObjectPointer = addFilterObject(filterPointer, sourceService);
			filterObjectPointer->name.assign(command->part(tempInt));
			tempInt++;
			filterObjectPointer->netmask.assign(command->part(tempInt));
			filterObjectPointer->serviceOper = serviceOperRange;
			filterObjectPointer->type = serviceObject;
			tempInt++;
		}
		else if (strcmp(command->part(tempInt), "object-group") == 0)
		{
			tempInt++;
			filterObjectPointer = addFilterObject(filterPointer, sourceService);
			filterObjectPointer->name.assign(command->part(tempInt));
			filterObjectPointer->serviceOper = serviceOperEqual;
			filterObjectPointer->type = serviceObject;
			tempInt++;
		}
	}

	// Outbound...
	else if (strcmp(command->part(0), "outbound") == 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sOutbound Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		filterListPointer = getFilterList(command->part(1));
		filterListPointer->type = outboundText;
		filterListPointer->typeDescription = outboundDescription;
		filterListPointer->legacyType = true;
		filterListPointer->sourceOnly = true;
		filterListPointer->loggingSupport = false;
		filterListPointer->supportsTime = false;
		filterListPointer->sourceServiceSupported = true;
		filterPointer = addFilter(filterListPointer);
		tempInt = 2;

		// Permit/Deny/Except
		if (strcmp(command->part(tempInt), "permit") == 0)
			filterPointer->action = allowAction;
		else if (strcmp(command->part(tempInt), "deny") == 0)
			filterPointer->action = denyAction;
		else
			filterPointer->action = exceptAction;
		tempInt++;

		// Source
		filterObjectPointer = addFilterObject(filterPointer, source);
		filterObjectPointer->name.assign(command->part(tempInt));
		tempInt++;
		filterObjectPointer->netmask.assign(command->part(tempInt));
		filterObjectPointer->serviceOper = serviceOperEqual;
		if (((filterObjectPointer->name.compare("0.0.0.0") == 0) || (filterObjectPointer->name.compare("0") == 0)) && ((filterObjectPointer->netmask.compare("0.0.0.0") == 0) || (filterObjectPointer->netmask.compare("0") == 0)))
		{
			filterObjectPointer->name.assign(i18n("Any"));
			filterObjectPointer->type = anyObject;
			filterObjectPointer->serviceOper = serviceOperEqual;
		}
		else if (filterObjectPointer->netmask.compare("255.255.255.255") == 0)
			filterObjectPointer->type = hostObject;
		else
			filterObjectPointer->type = networkObject;
		tempInt++;

		// Source Service
		if (tempInt < command->parts)
		{
			filterObjectPointer = addFilterObject(filterPointer, sourceService);
			filterObjectPointer->type = serviceObject;
			if (strcmp(command->part(tempInt), "0") == 0)
			{
				filterObjectPointer->name.assign(i18n("Any"));
				filterObjectPointer->serviceOper = serviceOperAny;
			}
			else if (strchr(command->part(tempInt), '-') == 0)
			{
				filterObjectPointer->name.assign(command->part(tempInt));
				filterObjectPointer->serviceOper = serviceOperEqual;
			}
			else
			{
				tempString.assign(command->part(tempInt));
				tempString.erase(tempString.find("-"));
				filterObjectPointer->name.assign(command->part(tempInt));
				tempString.assign(command->part(tempInt));
				tempString.erase(0, tempString.find("-"));
				filterObjectPointer->netmask.assign(command->part(tempInt));
				filterObjectPointer->serviceOper = serviceOperRange;
			}
			tempInt++;
		}

		// Protocol...
		if (tempInt < command->parts)
		{
			filterObjectPointer = addFilterObject(filterPointer, protocol);
			filterObjectPointer->type = protocolObject;
			filterObjectPointer->serviceOper = serviceOperEqual;
			filterObjectPointer->name.assign(command->part(tempInt));
		}
	}

	// Object Group...
	else if (strcmp(command->part(0), "object-group") == 0)
	{
		fgetpos(device->inputFile, &filePosition);

		while (((line[0] == ' ') || (strcmp(command->part(0), "object-group") == 0)) && (feof(device->inputFile) == 0))
		{

			// Object Group...
			if (strcmp(command->part(0), "object-group") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sObject Group Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				objectListPointer = getObjectList(command->part(2));

				if (strcmp(command->part(1), "protocol") == 0)
				{
					objectListPointer->type = protocolObject;
					objectListPointer->title = protocolObjectName;
					objectListPointer->description = protocolObjectDescription;
				}
				else if (strcmp(command->part(1), "network") == 0)
				{
					objectListPointer->type = networkObject;
					objectListPointer->title = networkObjectName;
					objectListPointer->description = networkObjectDescription;
				}
				else if (strcmp(command->part(1), "service") == 0)
				{
					objectListPointer->type = serviceObject;
					objectListPointer->title = serviceObjectName;
					objectListPointer->description = serviceObjectDescription;
					if (command->parts == 4)
					{
						if (strcmp(command->part(3), "tcp") == 0)
							objectListPointer->tcp = true;
						else if (strcmp(command->part(3), "udp") == 0)
							objectListPointer->udp = true;
						else
						{
							objectListPointer->tcp = true;
							objectListPointer->udp = true;
						}
					}
				}
				else // ICMP
				{
					objectListPointer->type = icmpObject;
					objectListPointer->title = serviceObjectName;
					objectListPointer->description = serviceObjectDescription;
				}
			}

			// Description
			else if (strcmp(command->part(0), "description") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sObject Group Description Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				objectListPointer->comment.assign(strstr(line, command->part(1)));
			}

			// Group-Object
			else if (strcmp(command->part(0), "group-object") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sObject Group Group Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				filterObjectPointer = addObject(objectListPointer);
				filterObjectPointer->type = groupObject;
				filterObjectPointer->name.assign(command->part(1));
				filterObjectPointer->serviceOper = serviceOperEqual;	
			}

			// ICMP-Object
			else if (strcmp(command->part(0), "icmp-object") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sObject Group ICMP Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				filterObjectPointer = addObject(objectListPointer);
				filterObjectPointer->type = icmpObject;
				tempInt2 = atoi(command->part(1));
				if ((tempInt2 > 0) || (strcmp(command->part(1), "0") == 0))
				{
					filterObjectPointer->name.assign(device->getICMPName(tempInt2));
					if (filterObjectPointer->name.empty())
						filterObjectPointer->name.assign(command->part(1));
				}
				else
					filterObjectPointer->name.assign(command->part(1));
				device->addICMPType(filterObjectPointer->name.c_str());
				filterObjectPointer->serviceOper = serviceOperEqual;	
			}

			// Network-Object
			else if (strcmp(command->part(0), "network-object") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sObject Group Network Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				filterObjectPointer = addObject(objectListPointer);
				filterObjectPointer->type = networkObject;
				if (strcmp(command->part(1), "host") == 0)
				{
					filterObjectPointer->type = hostObject;
					filterObjectPointer->name.assign(command->part(2));
				}
				else
				{
					filterObjectPointer->name.assign(command->part(1));
					filterObjectPointer->netmask.assign(command->part(2));
					if (strcmp(command->part(2), "255.255.255.255") == 0)
						filterObjectPointer->type = hostObject;
				}
				filterObjectPointer->serviceOper = serviceOperEqual;	
			}

			// Protocol-Object
			else if (strcmp(command->part(0), "protocol-object") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sObject Group Protocol Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				filterObjectPointer = addObject(objectListPointer);
				filterObjectPointer->type = protocolObject;
				tempInt2 = atoi(command->part(1));
				if ((tempInt2 > 0) || (strcmp(command->part(1), "0") == 0))
				{
					filterObjectPointer->name.assign(device->getProtocol(tempInt2));
					if (filterObjectPointer->name.empty())
						filterObjectPointer->name.assign(command->part(1));
				}
				else
					filterObjectPointer->name.assign(command->part(1));
				filterObjectPointer->serviceOper = serviceOperEqual;	
			}

			// Port-Object
			else if (strcmp(command->part(0), "port-object") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sObject Group Port Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				filterObjectPointer = addObject(objectListPointer);
				filterObjectPointer->type = portObject;
				if (strcmp(command->part(1), "eq") == 0)
				{
					filterObjectPointer->serviceOper = serviceOperEqual;
					filterObjectPointer->name.assign(command->part(2));
				}
				else
				{
					filterObjectPointer->serviceOper = serviceOperRange;
					filterObjectPointer->name.assign(command->part(2));
					filterObjectPointer->netmask.assign(command->part(3));
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

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


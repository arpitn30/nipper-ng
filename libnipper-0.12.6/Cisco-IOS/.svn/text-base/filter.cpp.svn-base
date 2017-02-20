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
#include "iosdevice.h"
#include "filter.h"


IOSFilter::IOSFilter()
{
	// Filter text...
	standardACLText = i18n("Standard *ABBREV*ACL*-ABBREV*");
	standardACLDescription = i18n("Standard *ABBREV*ACLs*-ABBREV* only define the source address and process the packet solely based on that, they are typically used to restrict access to device services or protocols.");
	extendedACLText = i18n("Extended *ABBREV*ACL*-ABBREV*");
	extendedACLDescription = i18n("Extended *ABBREV*ACLs*-ABBREV* permit or deny network traffic based on the source and destination addresses and network ports. Extended *ABBREV*ACLs*-ABBREV* are used for checks on traffic passing through the *DEVICENAME*.");

	// Filter device options...
	noAccessWithoutFilters = false;							// Is access not granted if no filters are configured
	allowName = i18n("Permit");								// The name given to an allowed filter
	denyName = i18n("Deny");								// The name given to a denied filter
	ruleListsAreAssigned = true;							// Rule lists are assigned to specific elements
	filterConfigTitle = i18n("*ABBREV*ACL*-ABBREV* Configuration");		// The Title for the configuration report section
	filterConfigText = i18n("*ABBREV*ACL*-ABBREV* are sequential lists of apply or deny *ABBREV*ACEs*-ABBREV* that a *DEVICETYPE* device will apply to the network traffic. The *DEVICETYPE* device will check network traffic against the *ABBREV*ACL*-ABBREV* and the first *ABBREV*ACE*-ABBREV* that matches will determine whether the network traffic is permitted or denied. If the *DEVICETYPE* device does not have an *ABBREV*ACE*-ABBREV* that applies then the packet is denied.");							// The device specific configuration report section text
	filterConfigText2 = i18n("There are two different types of *ABBREV*ACLs*-ABBREV* on IOS-based Cisco devices, standard and extended. For numbered *ABBREV*ACLs*-ABBREV*, standard *ABBREV*ACLs*-ABBREV* have an access list number between 1 to 99 or 1300 to 1999, all others are extended *ABBREV*ACLs*-ABBREV*. Standard *ABBREV*ACLs*-ABBREV* only define the source address and process the packet solely based on that, they are typically used to restrict access to device services or protocols. Extended *ABBREV*ACLs*-ABBREV* contain additional checks, such as destination address and network port numbers, and are used for filtering network traffic passing through the device.");							// The device specific configuration report section text2
	filterIDTitle = i18n("Line");							// The title for the filter ID/line no. table column
	filterListName = i18n("*ABBREV*ACL*-ABBREV*");			// The name of the filter list, for use in text paragraphs
	filterListNamePlaural = i18n("*ABBREV*ACLs*-ABBREV*");	// The name of the filter list, for use in text paragraphs
	filterListNameTitle = i18n("*ABBREV*ACL*-ABBREV*");		// The name of the filter list, for use in titles
	filterTitle = i18n("*ABBREV*ACE*-ABBREV*");				// The name of a filter, for use in titles
	filterTitlePlaural = i18n("*ABBREV*ACEs*-ABBREV*");		// The name of a filter, for use in titles
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
	configRuleLogging = i18n("Logging can be enabled on extended *COMMAND*access-list*-COMMAND* with the following command:*CODE**COMMAND*access-list *CMDUSER*list-id*-CMDUSER* extended *CMDREQUIRE*deny *CMDOR* permit*-CMDREQUIRE* *CMDUSER*protocol*-CMDUSER* *CMDUSER*source*-CMDUSER* *CMDUSER*destination*-CMDUSER* log*-COMMAND**-CODE*");								// The text describing how to configure logging for filter rules
	noFilteringIssue = i18n("No *ABBREV*ACL*-ABBREV* Were Configured");			// The title text for the "No filtering" issue
	noFilteringRec = i18n("Configure *ABBREV*ACL*-ABBREV* to restrict access");	// The title text for the "No filtering" recommendation
	noFilteringCon = i18n("no *ABBREV*ACL*-ABBREV* were configured");			// The title text for the "No filtering" conclusion

	// IOS specific
	turboAccessListSupported = false;						// Are turbo ACL supported?
	turboAccessList = false;								// Are turbo ACL enabled?
}


IOSFilter::~IOSFilter()
{
}


int IOSFilter::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	filterObjectConfig *filterObjectPointer = 0;
	filterConfig *filterPointer = 0;
	filterListConfig *filterListPointer = 0;
	int tempInt = 0;
	int tempInt2 = 0;
	bool specificProtocol = false;
	bool icmpProtocol = false;
	fpos_t filePosition;

	if (strcmp(command->part(0), "no") != 0)
	{

		// IP Access List...
		if ((strcmp(command->part(0), "ip") == 0) && (strcmp(command->part(1), "access-list") == 0) && (strcmp(command->part(2), "log-update") != 0))
		{
			while ((strcmp(command->part(0), "!") != 0) && ((line[0] == ' ') || (strcmp(command->part(1), "access-list") == 0)) && (strcmp(command->part(2), "log-update") != 0) && (feof(device->inputFile) == 0))
			{

				// Access-List...
				if ((strcmp(command->part(0), "ip") == 0) && (strcmp(command->part(1), "access-list") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sAccess List Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					filterListPointer = getFilterList(command->part(3));
					if (strcmp(command->part(2), "standard") == 0)
					{
						filterListPointer->sourceOnly = true;
						filterListPointer->type = standardACLText;
						filterListPointer->typeDescription = standardACLDescription;
					}
					else
					{
						filterListPointer->type = extendedACLText;
						filterListPointer->typeDescription = extendedACLDescription;
						filterListPointer->sourceServiceSupported = true;							// If source services are supported
						filterListPointer->sourceOnly = false;
						filterListPointer->supportsTime = true;				// Filter support time (dest only)
						filterListPointer->supportsFragments = true;		// Filter support fragments (dest only)
						filterListPointer->supportsEstablished = true;		// Filter support established (dest only)
					}
					filterListPointer->loggingSupport = true;				// Does the filter list support logging
				}

				// Remark...
				else if ((strcmp(command->part(0), "remark") == 0) && (command->parts > 1))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sRemark Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
					filterPointer = addFilter(filterListPointer);
					filterPointer->remarkFilter = true;
					filterPointer->number--;
					filterPointer->comment.assign(strstr(line, command->part(1)));
				}

				// Permit/Deny...
				else if ((strcmp(command->part(0), "permit") == 0) || (strcmp(command->part(0), "deny") == 0))
				{
					if ((strcmp(command->part(0), "permit") == 0) && (device->config->reportFormat == Config::Debug))
						printf("%sPermit Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
					else if (device->config->reportFormat == Config::Debug)
						printf("%sDeny Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					filterPointer = addFilter(filterListPointer);

					// Permit/Deny
					if (strcmp(command->part(0), "permit") == 0)
						filterPointer->action = allowAction;
					else
						filterPointer->action = denyAction;
					tempInt = 1;

					// Protocol...
					if (filterListPointer->sourceOnly == false)
					{
						filterObjectPointer = addFilterObject(filterPointer, protocol);
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
						tempInt++;
						if (strcmp(command->part(tempInt), "icmp") == 0)
						{
							specificProtocol = true;
							icmpProtocol = true;
						}
						else if (strcmp(command->part(tempInt), "igmp") == 0)
						{
							specificProtocol = true;
							icmpProtocol = false;
						}
					}

					// Source
					filterObjectPointer = addFilterObject(filterPointer, source);
					if (strcasecmp(command->part(tempInt), "any") == 0)
					{
						filterObjectPointer->name.assign(i18n("Any"));
						filterObjectPointer->type = anyObject;
					}
					else if (strcasecmp(command->part(tempInt), "host") == 0)
					{
						tempInt++;
						filterObjectPointer->name.assign(command->part(tempInt));
						filterObjectPointer->type = hostObject;
					}
					else
					{
						filterObjectPointer->name.assign(command->part(tempInt));
						tempInt++;
						if (tempInt < command->parts)
						{
							filterObjectPointer->netmask.assign(wildcardToNetmask(device, command->part(tempInt)));
							filterObjectPointer->type = networkObject;
						}
					}
					tempInt++;

					if (filterListPointer->sourceOnly == false)
					{

						// Is operator used with source?
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

						// Destination
						filterObjectPointer = addFilterObject(filterPointer, destination);
						if (strcasecmp(command->part(tempInt), "any") == 0)
						{
							filterObjectPointer->name.assign(i18n("Any"));
							filterObjectPointer->type = anyObject;
						}
						else if (strcasecmp(command->part(tempInt), "host") == 0)
						{
							tempInt++;
							filterObjectPointer->name.assign(command->part(tempInt));
							filterObjectPointer->type = hostObject;
						}
						else
						{
							filterObjectPointer->name.assign(command->part(tempInt));
							tempInt++;
							filterObjectPointer->netmask.assign(wildcardToNetmask(device, command->part(tempInt)));
							filterObjectPointer->type = networkObject;
						}
						tempInt++;

						// Is operator used with destination?
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

						if (specificProtocol == true)
						{
							// IGMP..
							if (icmpProtocol == false)
							{
								filterObjectPointer = addFilterObject(filterPointer, destinationService);
								filterObjectPointer->name.assign(command->part(tempInt));
								filterObjectPointer->serviceOper = serviceOperEqual;
								filterObjectPointer->type = serviceObject;
								tempInt++;
							}
		
							// ICMP...
							else
							{
								filterObjectPointer = addFilterObject(filterPointer, destinationService);
								tempInt2 = atoi(command->part(tempInt));
								if ((tempInt2 > 0) || (strcmp(command->part(tempInt), "0") == 0))
								{
									filterObjectPointer->name.assign(device->getICMPName(tempInt2));
									if (filterObjectPointer->name.empty())
										filterObjectPointer->name.assign(command->part(tempInt));
								}
								else
									filterObjectPointer->name.assign(command->part(tempInt));
								filterObjectPointer->serviceOper = serviceOperEqual;
								filterObjectPointer->type = serviceObject;
								// If an ICMP CODE is specified...
								if (((atoi(command->part(tempInt + 1)) > 0) && (atoi(command->part(tempInt + 1)) < 256)) || (strcmp(command->part(tempInt + 1), "0") == 0))
								{
									tempInt++;
									filterObjectPointer->netmask.assign(command->part(tempInt));
									device->addICMPType(filterObjectPointer->name.c_str(), atoi(command->part(tempInt)));
								}
								else
									device->addICMPType(filterObjectPointer->name.c_str());
								tempInt++;
							}
						}

						// Other options...
						while (tempInt < command->parts)
						{
							// Fragments...
							if (strcmp(command->part(tempInt), "fragments") == 0)
								filterPointer->fragments = true;

							// Established...
							else if (strcmp(command->part(tempInt), "established") == 0)
								filterPointer->established = true;

							// Log...
							else if (strcmp(command->part(tempInt), "log") == 0)
								filterPointer->log = true;

							// Time...
							else if (strcmp(command->part(tempInt), "time-range") == 0)
							{
								tempInt++;
								filterObjectPointer = addFilterObject(filterPointer, timeLimit);
								filterObjectPointer->name.assign(command->part(tempInt));
								filterObjectPointer->serviceOper = serviceOperEqual;
								filterObjectPointer->type = timeObject;
							}

							tempInt++;
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

		// Compiled Access List...
		else if ((strcmp(command->part(0), "access-list") == 0) && (strcmp(command->part(1), "compiled") == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sCompiled ACL Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			turboAccessListSupported = true;
			turboAccessList = true;	
		}

		// Access List...
		else if ((strcmp(command->part(0), "access-list") == 0) && (command->parts > 2))
		{
			filterListPointer = getFilterList(command->part(1));
			if ((atoi(command->part(1)) < 100) || ((atoi(command->part(1)) > 1299) && (atoi(command->part(1)) < 2000)))
				filterListPointer->sourceOnly = true;
			else
				filterListPointer->sourceOnly = false;
			filterListPointer->loggingSupport = true;			// Does the filter list support logging
			filterPointer = addFilter(filterListPointer);

			// Remark...
			if (strcmp(command->part(2), "remark") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sACL Remark Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				filterPointer->remarkFilter = true;
				filterPointer->number--;
				filterPointer->comment.assign(strstr(line, command->part(2)));
			}

			// Standard ACL
			else if (filterListPointer->sourceOnly == true)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sStandard ACL Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				filterListPointer->type = standardACLText;
				filterListPointer->typeDescription = standardACLDescription;

				// Permit/Deny
				if (strcmp(command->part(2), "permit") == 0)
					filterPointer->action = allowAction;
				else
					filterPointer->action = denyAction;

				// Name
				filterObjectPointer = addFilterObject(filterPointer, source);
				if (strcasecmp(command->part(3), "any") == 0)
				{
					filterObjectPointer->name.assign(i18n("Any"));
					filterObjectPointer->type = anyObject;
				}
				else
				{
					filterObjectPointer->name.assign(command->part(3));

					// Mask/Wildcard
					if ((command->parts > 4) && (strcmp(command->part(4), "log") != 0))
						filterObjectPointer->netmask.assign(wildcardToNetmask(device, command->part(4)));
					else
						filterObjectPointer->netmask.assign("255.255.255.255");

					// Check type...
					if (filterObjectPointer->netmask.compare("255.255.255.255") == 0)
						filterObjectPointer->type = hostObject;
					else
						filterObjectPointer->type = networkObject;
				}

				// Log
				if (strcmp(command->part(command->parts - 1), "log") == 0)
					filterPointer->log = true;
			}

			// Extended ACL
			else
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sExtended ACL Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				specificProtocol = false;

				filterListPointer->type = extendedACLText;
				filterListPointer->typeDescription = extendedACLDescription;
				filterListPointer->supportsTime = true;				// Filter support time (dest only)
				filterListPointer->supportsFragments = true;		// Filter support fragments (dest only)
				filterListPointer->supportsEstablished = true;		// Filter support established (dest only)

				// Permit/Deny
				tempInt = 2;
				while ((strcmp(command->part(tempInt), "permit") != 0) && (strcmp(command->part(tempInt), "deny") != 0) && (tempInt < command->parts))
					tempInt++;
				if (strcmp(command->part(tempInt), "permit") == 0)
					filterPointer->action = allowAction;
				else
					filterPointer->action = denyAction;

				// Protocol...
				tempInt++;
				filterObjectPointer = addFilterObject(filterPointer, protocol);
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
				if (strcmp(command->part(tempInt), "icmp") == 0)
				{
					specificProtocol = true;
					icmpProtocol = true;
				}
				else if (strcmp(command->part(tempInt), "igmp") == 0)
				{
					specificProtocol = true;
					icmpProtocol = false;
				}	

				// Source
				tempInt++;
				filterObjectPointer = addFilterObject(filterPointer, source);
				if (strcasecmp(command->part(tempInt), "any") == 0)
				{
					filterObjectPointer->name.assign(i18n("Any"));
					filterObjectPointer->type = anyObject;
				}
				else if (strcasecmp(command->part(tempInt), "host") == 0)
				{
					tempInt++;
					filterObjectPointer->name.assign(command->part(tempInt));
					filterObjectPointer->type = hostObject;
				}
				else
				{
					filterObjectPointer->name.assign(command->part(tempInt));
					tempInt++;
					filterObjectPointer->netmask.assign(wildcardToNetmask(device, command->part(tempInt)));
					filterObjectPointer->type = networkObject;
				}
				tempInt++;

				// Is operator used with source?
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

				// Destination
				filterObjectPointer = addFilterObject(filterPointer, destination);
				if (strcasecmp(command->part(tempInt), "any") == 0)
				{
					filterObjectPointer->name.assign(i18n("Any"));
					filterObjectPointer->type = anyObject;
				}
				else if (strcasecmp(command->part(tempInt), "host") == 0)
				{
					tempInt++;
					filterObjectPointer->name.assign(command->part(tempInt));
					filterObjectPointer->type = hostObject;
				}
				else
				{
					filterObjectPointer->name.assign(command->part(tempInt));
					tempInt++;
					filterObjectPointer->netmask.assign(wildcardToNetmask(device, command->part(tempInt)));
					filterObjectPointer->type = networkObject;
				}
				tempInt++;

				// Is operator used with destination?
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

				if (specificProtocol == true)
				{
					// IGMP..
					if (icmpProtocol == false)
					{
						filterObjectPointer = addFilterObject(filterPointer, destinationService);
						filterObjectPointer->name.assign(command->part(tempInt));
						filterObjectPointer->serviceOper = serviceOperEqual;
						filterObjectPointer->type = serviceObject;
						tempInt++;
					}

					// ICMP...
					else
					{
						filterObjectPointer = addFilterObject(filterPointer, destinationService);
						tempInt2 = atoi(command->part(tempInt));
						if ((tempInt2 > 0) || (strcmp(command->part(tempInt), "0") == 0))
						{
							filterObjectPointer->name.assign(device->getICMPName(tempInt2));
							if (filterObjectPointer->name.empty())
								filterObjectPointer->name.assign(command->part(tempInt));
						}
						else
							filterObjectPointer->name.assign(command->part(tempInt));
						filterObjectPointer->serviceOper = serviceOperEqual;
						filterObjectPointer->type = serviceObject;
						// If an ICMP CODE is specified...
						if (((atoi(command->part(tempInt + 1)) > 0) && (atoi(command->part(tempInt + 1)) < 256)) || (strcmp(command->part(tempInt + 1), "0") == 0))
						{
							tempInt++;
							filterObjectPointer->netmask.assign(command->part(tempInt));
							device->addICMPType(filterObjectPointer->name.c_str(), atoi(command->part(tempInt)));
						}
						else
							device->addICMPType(filterObjectPointer->name.c_str());
						tempInt++;
					}
				}

				// Other options...
				while (tempInt < command->parts)
				{
					// Fragments...
					if (strcmp(command->part(tempInt), "fragments") == 0)
						filterPointer->fragments = true;

					// Established...
					else if (strcmp(command->part(tempInt), "established") == 0)
						filterPointer->established = true;

					// Log...
					else if ((strcmp(command->part(tempInt), "log") == 0) || (strcmp(command->part(tempInt), "log-input") == 0))
						filterPointer->log = true;

					// Time...
					else if (strcmp(command->part(tempInt), "time-range") == 0)
					{
						tempInt++;
						filterObjectPointer = addFilterObject(filterPointer, timeLimit);
						filterObjectPointer->name.assign(command->part(tempInt));
						filterObjectPointer->serviceOper = serviceOperEqual;
						filterObjectPointer->type = timeObject;
					}

					tempInt++;
				}
			}
		}

		// All others...
		else
			device->lineNotProcessed(line);
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


string tempWildcard;
const char *IOSFilter::wildcardToNetmask(Device *device, const char *wildcard)
{
	// Variables...
	int stringLength = strlen(wildcard);
	const char *tempPointer = wildcard;
	unsigned char octet1 = 0;
	unsigned char octet2 = 0;
	unsigned char octet3 = 0;
	unsigned char octet4 = 0;

	// Obvious Errors...
	if (wildcard == 0)
		return "255.255.255.255";
	if (stringLength < 8)
		return "255.255.255.255";

	// Octet1...
	octet1 = atoi(tempPointer);
	octet1 = ~octet1;

	// Octet2...
	tempPointer = strchr(tempPointer, '.');
	if (tempPointer == 0)
		return "255.255.255.255";
	tempPointer++;
	octet2 = atoi(tempPointer);
	octet2 = ~octet2;

	// Octet3...
	tempPointer = strchr(tempPointer, '.');
	if (tempPointer == 0)
		return "255.255.255.255";
	tempPointer++;
	octet3 = atoi(tempPointer);
	octet3 = ~octet3;

	// Octet4...
	tempPointer = strchr(tempPointer, '.');
	if (tempPointer == 0)
		return "255.255.255.255";
	tempPointer++;
	octet4 = atoi(tempPointer);
	octet4 = ~octet4;

	// Return...
	tempWildcard.assign(device->intToString(octet1));
	tempWildcard.append(".");
	tempWildcard.append(device->intToString(octet2));
	tempWildcard.append(".");
	tempWildcard.append(device->intToString(octet3));
	tempWildcard.append(".");
	tempWildcard.append(device->intToString(octet4));
	return tempWildcard.c_str();
}

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


PassportFilter::PassportFilter()
{
	// Filter device options...
	denyAllAndLogDefault = false;							// Does it deny all and log by default?
	defaultFilterActionSupported = true;					// Default action supported on the device
	allowByDefault = false;									// Forward by default?
	defaultActionIsAllow = false;							// Is the default action to forward
	logLevelsSupported = false;								// Are log Levels supported
	logOnlyDenySupported = false;							// Is only Deny rule logging supported
	noAccessWithoutFilters = false;							// Is access not granted if no filters are configured
	filterSupportsInstalled = false;						// If filtering supports installed (i.e. CheckPoint)
	filterSupportsThrough = false;							// If a filtering supports through (i.e. CheckPoint)
	rejectRulesSupported = false;							// If reject rules are supported
	bypassRulesSupported = false;							// If bypass rules are supported
	defaultRulesSupported = true;							// If default rules are supported
	ruleListsAreAssigned = true;							// Rule lists are assigned to specific elements
	allowName = i18n("Forward");							// The name given to an forwarded filter
	denyName = i18n("Drop");								// The name given to a denied filter
	rejectName = i18n("Reject");							// The name given to a rejected filter
	filterConfigTitle = i18n("*ABBREV*IP*-ABBREV* Filter Configuration");			// The Title for the configuration report section
	filterConfigText = i18n("*ABBREV*IP*-ABBREV* filters are used to restrict access to specific hosts and services and are grouped into filter lists. Typically, *ABBREV*IP*-ABBREV* filters are processed sequentially with the first matching filter taking effect. However, the filter can be configured to not stop at a particular filter when the filter matches the network traffic.");							// The device specific configuration report section text
	filterConfigText2 = i18n("*DEVICETYPE* devices support three different types of filters, source, destination and global.");							// The device specific configuration report section text2
	useFilterID = true;									// Use the filter ID to identify a filter (otherwise a line no. is used)
	filterIDTitle = i18n("*ABBREV*ID*-ABBREV*");						// The title for the filter ID/line no. table column
	filterListName = i18n("*ABBREV*IP*-ABBREV* filter list");			// The name of the filter list, for use in text paragraphs
	filterListNameTitle = i18n("*ABBREV*IP*-ABBREV* Filter List");		// The name of the filter list, for use in titles
	filterListNamePlaural = i18n("*ABBREV*IP*-ABBREV* Filter Lists");	// The name of the filter list, for use in text paragraphs
	filterTitle = i18n("Filter");				// The name of a filter, for use in titles
	filterTitlePlaural = i18n("Filters");		// The name of a filter, for use in titles
	filterName = i18n("filter");				// The name of a filter, for use use in text paragraph
	filterNamePlaural = i18n("filters");		// The name of a filter, for use use in text paragraph

	// Issue titles...
	allowAndNotLogIssue = i18n("Not All Forward Filters Log Access");	// The title text for the "All Forward Rules Do Not Log" issue
	allowAndNotLogTable = i18n("Forward filters that do not log");		// The table title text for the "All Forward Rules Do Not Log" issue
	allowAndNotLogConcl = i18n("not all forward filters log access");	// The conclusions text for the "All Forward Rules Do Not Log" issue
	allowAndNotLogReco = i18n("Configure logging for all forward filters");	// The recommendations text for "All Forward Rules Do Not Log" (and deny) issue
	denyAndNotLogIssue = i18n("Not All Drop Filters Log Access");		// The title text for the "All Forward Rules Do Not Log" issue
	denyAndNotLogTable = i18n("Drop filters that do not log");		// The table title text for the "All Forward Rules Do Not Log" issue
	denyAndNotLogConcl = i18n("not all drop filters log access");		// The conclusions text for the "All Forward Rules Do Not Log" issue
	configRuleLogging = i18n("");								// The text describing how to configure logging for filter rules
	noFilteringIssue = i18n("No *ABBREV*IP*-ABBREV* Filters Were Configured");	// The title text for the "No filtering" issue
	noFilteringRec = i18n("Configure *ABBREV*IP*-ABBREV* Filters to restict access");		// The title text for the "No filtering" recommendation
	noFilteringCon = i18n("no *ABBREV*IP*-ABBREV* filters were configured");		// The title text for the "No filtering" conclusion
	legacyIssueFinding = i18n("");								// The finding for the legacy issue
	legacyIssueImpact = i18n("");								// The impact for the legacy issue
	legacyIssueEase = i18n("");									// The ease for the legacy issue
	legacyIssueRec = i18n("");									// The recommendation for the legacy issue
	allowAnythingTable = i18n("*ABBREV*IP*-ABBREV* filters forward any access");		// The forward anything table title text
	allowWeakTable = i18n("*ABBREV*IP*-ABBREV* filters provide weak filtering");		// Weak source/service/destination/service table title text
	allowAnyAnyAnyTable = i18n("*ABBREV*IP*-ABBREV* filters forward any host to access any destination and service");			// The forward any source, destination and service table title text
	allowWeakWeakWeakTable = i18n("*ABBREV*IP*-ABBREV* filters provide weak filtering of source, destination and service");	// The forward weak source, destination and service table title text
	allowAnyServiceAnyTable = i18n("*ABBREV*IP*-ABBREV* filters forward any source port to any destination and service");		// The forward any source port, destination and service table title text
	allowWeakServiceAnyTable = i18n("*ABBREV*IP*-ABBREV* filters provide weak filtering of source port to destination and service");	// The forward weak source, destination and service table title text
	allowAnyAnyTable = i18n("*ABBREV*IP*-ABBREV* filters forward any source to any destination");					// The forward any source, destination table title text
	allowAnyAnyServiceTable = i18n("*ABBREV*IP*-ABBREV* filters forward any source to any destination service");	// The forward any source, destination service table title text
	allowAnyDestServiceTable = i18n("*ABBREV*IP*-ABBREV* filters forward any destination and service");			// The forward any destination and service table title text
	allowAnyPortDestTable = i18n("*ABBREV*IP*-ABBREV* filters forward any source port to any destination address");			// The forward any source port to any destination table title text
	allowAnyPortServiceTable = i18n("*ABBREV*IP*-ABBREV* filters forward any source port to any destination service");			// The forward any source port to any dest service table title text
	allowWeakWeakTable = i18n("*ABBREV*IP*-ABBREV* filters forward weak filtering of source and destination addresses");		// The forward weak source, destination addresses
	allowWeakWeakServiceTable = i18n("*ABBREV*IP*-ABBREV* filters forward weak source addresses and destination services");	// The forward weak source, destination service table title text
	allowDestAndServiceTable = i18n("*ABBREV*IP*-ABBREV* filters forward weak destination addresses and services");// The forward weak destination and service table title text
	allowWeakPortDestTable = i18n("*ABBREV*IP*-ABBREV* filters forward weak source ports and destination");		// The forward weak source port to Destination table title text
	allowWeakPortServiceTable = i18n("*ABBREV*IP*-ABBREV* filters forward weak source ports and destination services");		// The forward weak source port to service table title text
	allowAnySourceTable = i18n("*ABBREV*IP*-ABBREV* filters forward from any source address");						// The forward any source address table title text
	allowNetSourceTable = i18n("*ABBREV*IP*-ABBREV* filters forward from a network source address");				// The forward a network source address table title text
	allowAnyPortTable = i18n("*ABBREV*IP*-ABBREV* filters forward from any source port");							// The forward any source port table title text
	allowRangePortTable = i18n("*ABBREV*IP*-ABBREV* filters forward from a source port range");					// The forward range source port table title text
	allowAnyDestTable = i18n("*ABBREV*IP*-ABBREV* filters forward to any destination");							// The forward any destination table title text
	allowNetDestTable = i18n("*ABBREV*IP*-ABBREV* filters forward to a network destination");						// The forward a network destination table title text
	allowToAnyDestServiceTable = i18n("*ABBREV*IP*-ABBREV* filters forward to any destination service");			// The forward any destination service table title text
	allowToNetDestServiceTable = i18n("*ABBREV*IP*-ABBREV* filters forward to a destination service range");		// The forward a destination service range table title text
	bypassContentFilterCon = i18n("*ABBREV*IP*-ABBREV* filters were configured that bypass the content filtering");			// Bypass filter conclusion text
	bypassContentFilterRec = i18n("Connfigure *ABBREV*IP*-ABBREV* filters that do not bypass the content filtering");	// Bypass filter recommendation text
	defaultFilterCon = i18n("*ABBREV*IP*-ABBREV* filters were configured that default to the ports filtering action");		// Default filter conclusion text
	defaultFilterRec = i18n("Configure *ABBREV*IP*-ABBREV* filters that do not default to the ports filtering action");		// Default filter recommendation text
	rejectSecurityIssueTitle = i18n("Reject *ABBREV*IP*-ABBREV* filters Were Configured");							// Reject filter title text
	securityRejectTextCon = i18n("*ABBREV*IP*-ABBREV* filters were configured that reject network traffic");			// Reject filter conclusion text
	securityRejectTextRec = i18n("Configure *ABBREV*IP*-ABBREV* filters to deny rather than reject network traffic");	// Reject filter recommendation text
	clearTextServiceCon = i18n("*ABBREV*IP*-ABBREV* filters were configured that forward access to clear text protocol services");		// Clear Text Service conclusions text
	clearTextServiceRec = i18n("Configure *ABBREV*IP*-ABBREV* filters to deny access to any clear text protocol services");			// Clear Text Service recommendations text2
	configureFilterListRecIssueText = i18n("A *ABBREV*IP*-ABBREV* filter list can be created and a filter assigned to it with the following commands:*CODE**COMMAND*ip traffic-filter set *CMDUSER*filter-list-number*-CMDUSER* create *CMDOPTION*name *CMDUSER*\"comment\"*-CMDUSER**-CMDOPTION**-COMMAND**COMMAND*ip traffic-filter set *CMDUSER*filter-list-number*-CMDUSER* add-filter *CMDUSER*filter-number*-CMDUSER**-COMMAND**-CODE*");												// The text and commands to configure a filter list
	configureFilterRecIssueText = i18n("A source *ABBREV*IP*-ABBREV* filter can be created with the following command:*CODE**COMMAND*ip traffic-filter create source src-ip *CMDUSER*source-ip*-CMDUSER* dst-ip *CMDUSER*dest-ip*-CMDUSER* id *CMDUSER*filter-number*-CMDUSER**-COMMAND**-CODE*");													// The text and commands to configure a filter
	unnecessaryServiceCon = i18n("*ABBREV*IP*-ABBREV* filters were configured that forward access to potentially unnecessary services");			// Unnecessary Service conclusions text
	unnecessaryServiceRec = i18n("Configure *ABBREV*IP*-ABBREV* filters to deny access to any unnecessary services");	// Unnecessary Service recommendations text2
	filtersWithNoCommentsTitle = i18n("Not All *ABBREV*IP*-ABBREV* filters Include Comments");	// Filters with no comments title text
	noFilterCommentsCon = i18n("not all *ABBREV*IP*-ABBREV* filters include comment text indicating their purpose");	// The no comments conclusion text
	noFilterCommentsRec = i18n("Configure comment text for all *ABBREV*IP*-ABBREV* filters");		// The no comments recommendation text
	configureFilterCommentText = i18n("*ABBREV*IP*-ABBREV* filter comments can be configured with the following command:*CODE**COMMAND*ip traffic-filter filter *CMDUSER*filter-number*-CMDUSER* name *CMDUSER*\"comment\"*-CMDUSER**-COMMAND**-CODE*");													// The text and commands to configure a filters comment text
	disabledFiltersTitle = i18n("Disabled *ABBREV*IP*-ABBREV* filters Were Configured");			// The disabled filter issues title text
	removeFilterText = i18n("An *ABBREV*IP*-ABBREV* filter can be deleted with the following command:*CODE**COMMAND*ip traffic-filter filter *CMDUSER*filter-number*-CMDUSER* delete*-COMMAND**-CODE*");															// The commands and text to delete a filter
	disabledFilterCon = i18n("disabled *ABBREV*IP*-ABBREV* filters were configured");				// The disabled filter conclusion text
	disabledFilterRec = i18n("Remove all disabled *ABBREV*IP*-ABBREV* filters");					// The disabled filter recommendation text
	defaultActionIssueTitle = i18n("The Default Network Filtering Action Permits Access");	// The default filter action issue title
	defaultActionIssueCon = i18n("the default *ABBREV*IP*-ABBREV* filter list action was configured to forward access when a filter does not match");	// The default filter action conclusion text
	defaultActionIssueRec = i18n("Set the default*ABBREV*IP*-ABBREV* filter list action to drop network traffic");		// The default filter action recommendation text
	configureDefaultActionText = i18n("");													// The text and commands to configure the default action
	unusedFiltersIssueTitle = i18n("Unused *ABBREV*IP*-ABBREV* filters Were Configured At The *ABBREV*IP*-ABBREV* Filter List End");	// Unused filters at the end of the filter list title
	unusedFiltersIssueCon = i18n("unused *ABBREV*IP*-ABBREV* filters were configured at the end of the *ABBREV*IP*-ABBREV* filter list");		// Unused filters issue conclusions text
	unusedFiltersIssueRec = i18n("Remove all unused *ABBREV*IP*-ABBREV* filters");				// Unused filters issue recommendation text
	denyAllLogIssueTitle = i18n("*ABBREV*IP*-ABBREV* Filter List Does Not End with Drop All And Log");	// Deny All And Log Issue title
	denyAllLogConfigure = i18n("");															// The text and commands to add a deny all and log line
	denyAllLogIssueCon = i18n("not all *ABBREV*IP*-ABBREV* filter lists end with a drop all and log ");		// The deny all and log conclusions text
	denyAllLogIssueRec = i18n("Configure a drop all and log *ABBREV*IP*-ABBREV* filter as the last filter in each filter list");			// The deny all and log recommendations text
	contradictIssueTitle = i18n("Contradicting *ABBREV*IP*-ABBREV* filters Were Configured");		// The contradict issue title
	contradictIssueTable = i18n("contradictions of filter");					// The contradict table issue title
	contradictIssueCon = i18n("*ABBREV*IP*-ABBREV* filters were configured that contradict other *ABBREV*IP*-ABBREV* filters");				// The contradict issue conclusion
	contradictIssueRec = i18n("Reconfigure the *ABBREV*IP*-ABBREV* filters so they do not contradict other filters");	// The contradict issue recommendation
	duplicateIssueTitle = i18n("Duplicate *ABBREV*IP*-ABBREV* filters Were Configured");			// The duplicate/overlapping issue title
	duplicateIssueTable = i18n("duplicates of *ABBREV*IP*-ABBREV* filter");										// The duplicate/overlapping issue title
	duplicateIssueCon = i18n("*ABBREV*IP*-ABBREV* filters were configured that duplicate the configuration of other *ABBREV*IP*-ABBREV* filters");	// The duplicate/overlapping issue title
	duplicateIssueRec = i18n("Reconfigure the *ABBREV*IP*-ABBREV* filters so that the rules do not duplicate other *ABBREV*IP*-ABBREV* filters");						// The duplicate/overlapping issue title

}


PassportFilter::~PassportFilter()
{
}


int PassportFilter::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	filterListConfig *destFilterListPointer = 0;
	filterListConfig *filterListPointer = 0;
	filterConfig *destFilterPointer = 0;
	filterConfig *filterPointer = 0;
	filterObjectConfig *objectPointer = 0;
	string tempString;
	fpos_t filePosition;
	int tempInt = 0;

	// IP...
	if (strcmp(command->part(0), "ip") == 0)
	{

		// Traffic Filters
		if (strcmp(command->part(1), "traffic-filter") == 0)
		{

			filterListPointer = getFilterList(i18n("Unassigned"));
			filterListPointer->type = i18n("*ABBREV*IP*-ABBREV* Filters");				// The filter list type name (used in the config report)
			filterListPointer->typeDescription = i18n("*ABBREV*IP*-ABBREV* filters are used on *DEVICETYPE* devices to determine which network traffic should be forwarded and which should be blocked. This section details those filters.");	// The filter list type description for the report (used in config report)
			filterListPointer->legacyType = false;				// Is the filter list a legacy type?
			filterListPointer->sourceOnly = false;				// The type of filter
			filterListPointer->loggingSupport = false;			// Does the filter list support logging
			filterListPointer->supportsTime = false;			// Filter support time (dest only)
			filterListPointer->supportsFragments = true;		// Filter support fragments (dest only)
			filterListPointer->supportsEstablished = false;		// Filter support established (dest only)
			filterListPointer->sourceServiceSupported = true;	// If source services are supported
			filterListPointer->disabledFilterSupport = true;	// Is it possible to disable filters?
			filterListPointer->filterCommentsSupported = true;	// Are filter comments supported
			filterListPointer->showProtocol = true;				// Show the protocol? (some devices use a configured service)
			filterListPointer->showFilterZones = false;			// Does the filter use filter-based zones (i.e. SonicWALL)
			filterListPointer->showStop = true;
			filterListPointer->showFilterType = true;			// Does the filter have a type (i.e. like on Passport devices)

			while ((feof(device->inputFile) == 0) && (strcmp(command->part(1), "traffic-filter") == 0))
			{

				// Create
				if (strcmp(command->part(2), "create") == 0)
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sFilter Create Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					filterPointer = addFilter(filterListPointer);
					filterPointer->stop = true;
					filterPointer->inSet = false;
					filterPointer->action = deftAction;

					// Filter Type
					if (strcmp(command->part(3), "source") == 0)			// Source
						filterPointer->type = sourceFilter;
					else if (strcmp(command->part(3), "destination") == 0)	// Destination
						filterPointer->type = destinationFilter;
					else													// Global
						filterPointer->type = globalFilter;
					tempInt = 4;

					while (tempInt < command->parts)
					{
						// Source / Destination...
						if ((strcmp(command->part(tempInt), "src-ip") == 0) || (strcmp(command->part(tempInt), "dst-ip") == 0))
						{
							if (strcmp(command->part(tempInt), "src-ip") == 0)
							{
								objectPointer = addFilterObject(filterPointer, source);
							}
							else
							{
								objectPointer = addFilterObject(filterPointer, destination);
							}
							tempInt++;

							objectPointer->serviceOper = serviceOperEqual;
							if ((strcasecmp(command->part(tempInt), "default") == 0) || (strcmp(command->part(tempInt), "0.0.0.0/0.0.0.0") == 0))
							{
								objectPointer->type = anyObject;
								objectPointer->name.assign(i18n("Any"));
								objectPointer->serviceOper = serviceOperAny;
							}
							else
							{
								if (strchr(command->part(tempInt), '/') != 0)
								{
									objectPointer->netmask.assign(strchr(command->part(tempInt), '/') + 1);
									objectPointer->name.assign(command->part(tempInt));
									tempString.assign(command->part(tempInt));
									objectPointer->name.erase(tempString.find("/"));
									if (objectPointer->netmask.compare("255.255.255.255") == 0)
										objectPointer->type = hostObject;
									else
										objectPointer->type = networkObject;
								}
								else
								{
									objectPointer->type = hostObject;
									objectPointer->name.assign(command->part(tempInt));
								}
							}
						}

						// Filter Id?
						else if (strcmp(command->part(tempInt), "id") == 0)
						{
							tempInt++;
							filterPointer->id = atoi(command->part(tempInt));
						}

						tempInt++;
					}
				}

				// Filter
				else if (strcmp(command->part(2), "filter") == 0)
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sFilter Filter Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					filterPointer = getFilter(atoi(command->part(3)), filterListPointer);

					// Name...
					if (strcmp(command->part(4), "name") == 0)
						filterPointer->comment.assign(command->part(5));

					// Action...
					else if (strcmp(command->part(4), "action") == 0)
					{

						// Mode...
						if (strcmp(command->part(5), "mode") == 0)
						{
							if (strcmp(command->part(6), "forward") == 0)
								filterPointer->action = allowAction;
							else if (strcmp(command->part(6), "drop") == 0)
								filterPointer->action = denyAction;
							else if (strcmp(command->part(6), "forward-to-next-hop") == 0)
								filterPointer->action = allowAction;
						}

						// Stop on match...
						else if (strcmp(command->part(5), "stop-on-match") == 0)
						{
							if (strcmp(command->part(6), "true") == 0)
								filterPointer->stop = true;
							else
								filterPointer->stop = false;
						}
					}
	
					// Match...
					else if (strcmp(command->part(4), "match") == 0)
					{
	
						// Protocol...
						if (strcmp(command->part(5), "protocol") == 0)
						{
							objectPointer = addFilterObject(filterPointer, protocol);
							objectPointer->type = protocolObject;
							objectPointer->name.assign(command->part(6));
							objectPointer->serviceOper = serviceOperEqual;
						}

						// Source Port / Destination Port...
						else if ((strcmp(command->part(5), "src-port") == 0) || (strcmp(command->part(5), "dst-port") == 0))
						{
							if (strcmp(command->part(5), "src-port") == 0)
								objectPointer = addFilterObject(filterPointer, sourceService);
							else
								objectPointer = addFilterObject(filterPointer, destinationService);
							objectPointer->type = serviceObject;
							objectPointer->name.assign(command->part(6));

							if (command->parts == 9)
							{
	
								// Options...
								if ((strcasecmp(command->part(7), "src-option") == 0) || (strcasecmp(command->part(7), "dst-option") == 0))
								{
									if (strcasecmp(command->part(8), "ignore") == 0)
										objectPointer->serviceOper = serviceOperNotEqual;
									else if (strcasecmp(command->part(8), "equal") == 0)
										objectPointer->serviceOper = serviceOperEqual;
									else if (strcasecmp(command->part(8), "less") == 0)
										objectPointer->serviceOper = serviceOperLessThan;
									else if (strcasecmp(command->part(8), "greater") == 0)
										objectPointer->serviceOper = serviceOperGreaterThan;
									else if (strcasecmp(command->part(8), "notequal") == 0)
										objectPointer->serviceOper = serviceOperNotEqual;
								}
							}
						}
					}
				}

				// Set
				else if (strcmp(command->part(2), "set") == 0)
				{

					// Create
					if (strcmp(command->part(4), "create") == 0)
					{
						if (device->config->reportFormat == Config::Debug)
							printf("%sFilter Set Create Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

						destFilterListPointer = getFilterList(command->part(3));
						destFilterListPointer->type = i18n("*ABBREV*IP*-ABBREV* Filters");				// The filter list type name (used in the config report)
						destFilterListPointer->typeDescription = i18n("*ABBREV*IP*-ABBREV* filters are used on *DEVICETYPE* devices to determine which network traffic should be forwarded and which should be blocked. This section details those filters.");
						destFilterListPointer->legacyType = false;				// Is the filter list a legacy type?
						destFilterListPointer->sourceOnly = false;				// The type of filter
						destFilterListPointer->loggingSupport = false;			// Does the filter list support logging
						destFilterListPointer->supportsTime = false;			// Filter support time (dest only)
						destFilterListPointer->supportsFragments = true;		// Filter support fragments (dest only)
						destFilterListPointer->supportsEstablished = false;		// Filter support established (dest only)
						destFilterListPointer->sourceServiceSupported = true;	// If source services are supported
						destFilterListPointer->disabledFilterSupport = true;	// Is it possible to disable filters?
						destFilterListPointer->filterCommentsSupported = true;	// Are filter comments supported
						destFilterListPointer->showProtocol = true;				// Show the protocol? (some devices use a configured service)
						destFilterListPointer->showFilterZones = false;			// Does the filter use filter-based zones (i.e. SonicWALL)
						destFilterListPointer->showStop = true;
						destFilterListPointer->showFilterType = true;			// Does the filter have a type (i.e. like on Passport devices)
						if (strcmp(command->part(5), "name") == 0)
							destFilterListPointer->listName.assign(command->part(6));
					}

					// Add Filter
					else if (strcmp(command->part(4), "add-filter") == 0)
					{
						if (device->config->reportFormat == Config::Debug)
							printf("%sFilter Set Add Filter Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

						// Source filter...
						filterPointer = getOnlyFilter(atoi(command->part(5)), filterListPointer);
						if (filterPointer != 0)
						{

							destFilterListPointer = getFilterList(command->part(3));
							destFilterPointer = getFilter(atoi(command->part(5)), destFilterListPointer);

							copySourceToDestinationFilters(filterPointer, destFilterPointer);
							filterPointer->deleteMe = true;
						}
					}

					// All others...
					else
						device->lineNotProcessed(line);

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
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int PassportFilter::generateDeviceSpecificFilterSecurityIssues(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	filterListConfig *filterListPointer = 0;
	filterConfig *filterPointer = 0;
	int filterCount = 0;
	bool found = false;
	int errorCode = 0;

	filterListPointer = filterList;
	while ((filterListPointer != 0) && (found == false))
	{
		if (filterListPointer->name.compare(i18n("Unassigned")) == 0)
		{
			filterPointer = filterListPointer->filter;
			while (filterPointer != 0)
			{
				filterCount++;
				filterPointer = filterPointer->next;
			}
			found = true;
		}
		else
			filterListPointer = filterListPointer->next;
	}


	if (found == true)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Unassigned IP Filters\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		if (filterCount > 2)
			securityIssuePointer->title.assign(i18n("Unassigned *ABBREV*IP*-ABBREV* Filters Were Configured"));
		else
			securityIssuePointer->title.assign(i18n("An Unassigned *ABBREV*IP*-ABBREV* Filter Was Configured"));
		securityIssuePointer->reference.assign("PAS.FILTUNAS.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("The *ABBREV*IP*-ABBREV* filters on *DEVICETYPE* devices are configured prior to the filter lists. The filters can then assigned to the various filter lists and the filter lists assigned to interfaces in order to restrict access."));

		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addValue(paragraphPointer, filterCount);
		if (filterCount > 2)
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *ABBREV*IP*-ABBREV* filters were not assigned to any filter lists. These filters are listed in Table *TABLEREF*."));
		else
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *ABBREV*IP*-ABBREV* filter was not assigned to any filter lists. This filter is shown in Table *TABLEREF*."));

		// Create table...
		errorCode = device->addTable(paragraphPointer, "GEN-FILTUNAS-UNASSIGNED-TABLE");
		if (errorCode != 0)
			return errorCode;
		if (filterCount > 2)
			paragraphPointer->table->title.assign(i18n("Unassigned *ABBREV*IP*-ABBREV* filters"));
		else
			paragraphPointer->table->title.assign(i18n("Unassigned *ABBREV*IP*-ABBREV* filter"));

		// Create table headings...
		addFilterTableHeadings(device, paragraphPointer, filterListPointer);

		// Output filter lines...
		filterPointer = filterListPointer->filter;
		while (filterPointer != 0)
		{
			addFilterTableRow(device, paragraphPointer, filterPointer, filterListPointer);
			filterPointer = filterPointer->next;
		}

		// Issue impact...
		securityIssuePointer->impactRating = 3;			// Low
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("Although not a direct threat to security, unassigned filters will not be used and could lead to a duplication of the filters and cause confusion when administering a *DEVICETYPE* device. The clarity of the *ABBREV*IP*-ABBREV* filter lists are paramount as it could lead to a configuration where access to services are overally permissive."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 0;			// N/A
		paragraphPointer->paragraph.assign(i18n("If the filters are not assigned to a filter list, they will not be used to filter any network traffic."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 3;			// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that all unassigned *ABBREV*IP*-ABBREV* should be deleted. The unassigned filters can be deleted with the following command:*CODE**COMMAND*ip traffic-filter filter *CMDUSER*filter-number*-CMDUSER* delete*-COMMAND**-CODE*"));

		// Conclusions text...
		if (filterCount > 2)
			securityIssuePointer->conLine.assign(i18n("unassigned *ABBREV*IP*-ABBREV* filters were configured"));
		else
			securityIssuePointer->conLine.assign(i18n("an unassigned *ABBREV*IP*-ABBREV* filter was configured"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("delete unassigned *ABBREV*IP*-ABBREV* filters"), true);
	}

	return 0;
}


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


Filter::filterConfig *Filter::insertFilter(filterListConfig *filterListPointer, filterConfig *beforePointer)
{
	// Variables...
	filterConfig *filterPointer = 0;

	// If first...
	if (filterListPointer->filter == beforePointer)
	{
		filterListPointer->filter = new (filterConfig);
		filterPointer = filterListPointer->filter;
	}

	// Search
	else
	{
		filterPointer = filterListPointer->filter;
		while ((filterPointer->next != 0) && (filterPointer->next != beforePointer))
			filterPointer = filterPointer->next;
		filterPointer->next = new (filterConfig);
		filterPointer = filterPointer->next;
	}

	filterPointer->id = 0;
	filterPointer->enabled = true;
	filterPointer->remarkFilter = false;
	filterPointer->sourceServiceSupported = false;
	filterPointer->action = allowAction;
	filterPointer->protocol = 0;
	filterPointer->source = 0;
	filterPointer->sourceService = 0;
	filterPointer->destination = 0;
	filterPointer->destinationService = 0;
	filterPointer->through = 0;
	filterPointer->install = 0;
	filterPointer->time = 0;
	filterPointer->log = false;
	filterPointer->logLevel = 0;
	filterPointer->established = false;
	filterPointer->fragments = false;
	filterPointer->type = sourceFilter;
	filterPointer->stop = 0;
	filterPointer->inSet = 0;
	filterPointer->deleteMe = false;
	filterPointer->next = beforePointer;

	return filterPointer;
}


Filter::filterConfig *Filter::getFilter(int id, filterListConfig *filterListPointer)
{
	// Variables...
	filterConfig *filterPointer = 0;
	bool found = true;

	// If the filter list exists...
	if (filterListPointer != 0)
	{
		// Create filter...
		if (filterListPointer->filter == 0)
		{
			filterListPointer->filter = new (filterConfig);
			filterPointer = filterListPointer->filter;
			filterPointer->number = 1;
			found = false;
		}
		else
		{
			filterPointer = filterListPointer->filter;
			while ((filterPointer->next != 0) && (filterPointer->id != id))
				filterPointer = filterPointer->next;
			if (filterPointer->id != id)
			{
				filterPointer->next = new (filterConfig);
				filterPointer->next->number = filterPointer->number + 1;
				filterPointer = filterPointer->next;
				found = false;
			}
		}
	}

	// Just search for and return the filter (a list has to be specified in order to create)
	else
	{
		filterListPointer = filterList;
		while (filterListPointer != 0)
		{
			filterPointer = filterListPointer->filter;
			while (filterPointer != 0)
			{
				if (filterPointer->id == id)
					return filterPointer;
				filterPointer = filterPointer->next;
			}
			filterListPointer = filterListPointer->next;
		}
	}

	// Init...
	if (found == false)
	{
		filterPointer->id = id;
		filterPointer->enabled = true;
		filterPointer->remarkFilter = false;
		filterPointer->sourceServiceSupported = false;
		filterPointer->action = allowAction;
		filterPointer->protocol = 0;
		filterPointer->source = 0;
		filterPointer->sourceService = 0;
		filterPointer->destination = 0;
		filterPointer->destinationService = 0;
		filterPointer->through = 0;
		filterPointer->install = 0;
		filterPointer->time = 0;
		filterPointer->log = false;
		filterPointer->logLevel = 0;
		filterPointer->established = false;
		filterPointer->fragments = false;
		filterPointer->type = sourceFilter;
		filterPointer->stop = 0;
		filterPointer->inSet = 0;
		filterPointer->deleteMe = false;
		filterPointer->next = 0;
	}

	return filterPointer;
}


Filter::filterConfig *Filter::getOnlyFilter(int id, filterListConfig *filterListPointer)
{
	// Variables...
	filterConfig *filterPointer = 0;

	// If the filter list exists...
	if (filterListPointer == 0)
		filterListPointer = filterList;

	while (filterListPointer != 0)
	{
		filterPointer = filterListPointer->filter;
		while (filterPointer != 0)
		{
			if (filterPointer->id == id)
				return filterPointer;
			else
				filterPointer = filterPointer->next;
		}
		filterListPointer = filterListPointer->next;
	}

	return filterPointer;
}


// Create and return a new filter in the specified list
Filter::filterConfig *Filter::addFilter(filterListConfig *filterListPointer)
{
	// Variables...
	filterConfig *filterPointer = 0;

	// Create filter...
	if (filterListPointer->filter == 0)
	{
		filterListPointer->filter = new (filterConfig);
		filterPointer = filterListPointer->filter;
		filterPointer->number = 1;
	}
	else
	{
		filterPointer = filterListPointer->filter;
		while (filterPointer->next != 0)
			filterPointer = filterPointer->next;
		filterPointer->next = new (filterConfig);
		filterPointer->next->number = filterPointer->number + 1;
		filterPointer = filterPointer->next;
	}

	// Init...
	filterPointer->id = 0;
	filterPointer->enabled = true;
	filterPointer->remarkFilter = false;
	filterPointer->sourceServiceSupported = false;
	filterPointer->action = allowAction;
	filterPointer->protocol = 0;
	filterPointer->source = 0;
	filterPointer->sourceService = 0;
	filterPointer->destination = 0;
	filterPointer->destinationService = 0;
	filterPointer->through = 0;
	filterPointer->install = 0;
	filterPointer->time = 0;
	filterPointer->log = false;
	filterPointer->logLevel = 0;
	filterPointer->established = false;
	filterPointer->fragments = false;
	filterPointer->type = sourceFilter;
	filterPointer->stop = 0;
	filterPointer->inSet = 0;
	filterPointer->deleteMe = false;
	filterPointer->next = 0;

	return filterPointer;
}


// Creates a new filter object of the specified type
Filter::filterObjectConfig *Filter::addFilterObject(filterConfig *filterPointer, filterObjectType sourceObject)
{
	// Variables...
	filterObjectConfig *filterObjectPointer = 0;

	// Create...
	switch (sourceObject)
	{
		case protocol:
			if (filterPointer->protocol == 0)
			{
				filterPointer->protocol = new (filterObjectConfig);
				filterObjectPointer = filterPointer->protocol;
			}
			else
			{
				filterObjectPointer = filterPointer->protocol;
				while (filterObjectPointer->next != 0)
					filterObjectPointer = filterObjectPointer->next;
				filterObjectPointer->next = new (filterObjectConfig);
				filterObjectPointer = filterObjectPointer->next;
			}
			filterObjectPointer->type = protocolObject;
			break;
		case source:
			if (filterPointer->source == 0)
			{
				filterPointer->source = new (filterObjectConfig);
				filterObjectPointer = filterPointer->source;
			}
			else
			{
				filterObjectPointer = filterPointer->source;
				while (filterObjectPointer->next != 0)
					filterObjectPointer = filterObjectPointer->next;
				filterObjectPointer->next = new (filterObjectConfig);
				filterObjectPointer = filterObjectPointer->next;
			}
			filterObjectPointer->type = hostObject;
			break;
		case sourceService:
			if (filterPointer->sourceService == 0)
			{
				filterPointer->sourceService = new (filterObjectConfig);
				filterObjectPointer = filterPointer->sourceService;
			}
			else
			{
				filterObjectPointer = filterPointer->sourceService;
				while (filterObjectPointer->next != 0)
					filterObjectPointer = filterObjectPointer->next;
				filterObjectPointer->next = new (filterObjectConfig);
				filterObjectPointer = filterObjectPointer->next;
			}
			filterObjectPointer->type = serviceObject;
			break;
		case destination:
			if (filterPointer->destination == 0)
			{
				filterPointer->destination = new (filterObjectConfig);
				filterObjectPointer = filterPointer->destination;
			}
			else
			{
				filterObjectPointer = filterPointer->destination;
				while (filterObjectPointer->next != 0)
					filterObjectPointer = filterObjectPointer->next;
				filterObjectPointer->next = new (filterObjectConfig);
				filterObjectPointer = filterObjectPointer->next;
			}
			filterObjectPointer->type = hostObject;
			break;
		case destinationService:
			if (filterPointer->destinationService == 0)
			{
				filterPointer->destinationService = new (filterObjectConfig);
				filterObjectPointer = filterPointer->destinationService;
			}
			else
			{
				filterObjectPointer = filterPointer->destinationService;
				while (filterObjectPointer->next != 0)
					filterObjectPointer = filterObjectPointer->next;
				filterObjectPointer->next = new (filterObjectConfig);
				filterObjectPointer = filterObjectPointer->next;
			}
			filterObjectPointer->type = serviceObject;
			break;
		case through:
			if (filterPointer->through == 0)
			{
				filterPointer->through = new (filterObjectConfig);
				filterObjectPointer = filterPointer->through;
			}
			else
			{
				filterObjectPointer = filterPointer->through;
				while (filterObjectPointer->next != 0)
					filterObjectPointer = filterObjectPointer->next;
				filterObjectPointer->next = new (filterObjectConfig);
				filterObjectPointer = filterObjectPointer->next;
			}
			filterObjectPointer->type = gatewayObject;
			break;
		case installed:
			if (filterPointer->install == 0)
			{
				filterPointer->install = new (filterObjectConfig);
				filterObjectPointer = filterPointer->install;
			}
			else
			{
				filterObjectPointer = filterPointer->install;
				while (filterObjectPointer->next != 0)
					filterObjectPointer = filterObjectPointer->next;
				filterObjectPointer->next = new (filterObjectConfig);
				filterObjectPointer = filterObjectPointer->next;
			}
			filterObjectPointer->type = gatewayObject;
			break;
		default:
			if (filterPointer->time == 0)
			{
				filterPointer->time = new (filterObjectConfig);
				filterObjectPointer = filterPointer->time;
			}
			else
			{
				filterObjectPointer = filterPointer->time;
				while (filterObjectPointer->next != 0)
					filterObjectPointer = filterObjectPointer->next;
				filterObjectPointer->next = new (filterObjectConfig);
				filterObjectPointer = filterObjectPointer->next;
			}
			filterObjectPointer->type = timeObject;
			break;
	}

	// Init...
	filterObjectPointer->serviceOper = serviceOperEqual;
	filterObjectPointer->protocol = 0;
	filterObjectPointer->sourcePort = 0;
	filterObjectPointer->destinationPort = 0;
	filterObjectPointer->internal = false;
	filterObjectPointer->firewall = false;
	filterObjectPointer->management = false;
	filterObjectPointer->interfaceIndex = 0;
	filterObjectPointer->dhcp = false;
	filterObjectPointer->interfaces = 0;
	filterObjectPointer->members = 0;
	filterObjectPointer->deleteMe = false;
	filterObjectPointer->next = 0;

	return filterObjectPointer;
}


// Get a filter list by from/to (creates what it cannot find)
Filter::filterListConfig *Filter::getFilterList(const char *from, const char *to, bool global)
{
	// Variables...
	filterListConfig *filterListPointer = 0;
	bool init = false;

	// Create...
	if (filterList == 0)
	{
		filterList = new (filterListConfig);
		filterListPointer = filterList;
		init = true;
	}
	else
	{
		filterListPointer = filterList;
		while (!((filterListPointer->name.compare(from) == 0) && (filterListPointer->to.compare(to) == 0)) && (filterListPointer->next != 0))
			filterListPointer = filterListPointer->next;
		if (!((filterListPointer->name.compare(from) == 0) && (filterListPointer->to.compare(to) == 0)))
		{
			filterListPointer->next = new (filterListConfig);
			filterListPointer = filterListPointer->next;
			init = true;
		}
	}

	// Need Init?
	if (init == true)
	{
		filterListPointer->name.assign(from);
		filterListPointer->to.assign(to);
		filterListPointer->globalFilter = global;
		filterListPointer->filter = 0;
		filterListPointer->type = "";
		filterListPointer->typeDescription = "";
		filterListPointer->legacyType = false;
		filterListPointer->sourceOnly = false;
		filterListPointer->sourceServiceSupported = false;
		filterListPointer->disabledFilterSupport = false;
		filterListPointer->loggingSupport = false;
		filterListPointer->supportsTime = false;
		filterListPointer->supportsFragments = false;	
		filterListPointer->supportsEstablished = false;
		filterListPointer->filterCommentsSupported = false;
		filterListPointer->showProtocol = true;
		filterListPointer->used = false;
		filterListPointer->showFilterZones = false;
		filterListPointer->showStop = false;
		filterListPointer->showFilterType = false;			// Does the filter have a type (i.e. like on Passport devices)
		filterListPointer->active = true;
		filterListPointer->next = 0;
	}

	return filterListPointer;
}


// Get a filter list by name/id (creates what it cannot find)
Filter::filterListConfig *Filter::getFilterList(const char *name)
{
	// Variables...
	filterListConfig *filterListPointer = 0;
	bool init = false;

	// Create...
	if (filterList == 0)
	{
		filterList = new (filterListConfig);
		filterListPointer = filterList;
		init = true;
	}
	else
	{
		filterListPointer = filterList;
		while ((filterListPointer->name.compare(name) != 0) && (filterListPointer->next != 0))
			filterListPointer = filterListPointer->next;
		if (filterListPointer->name.compare(name) != 0)
		{
			filterListPointer->next = new (filterListConfig);
			filterListPointer = filterListPointer->next;
			init = true;
		}
	}

	// Need Init?
	if (init == true)
	{
		filterListPointer->name.assign(name);
		filterListPointer->globalFilter = false;
		filterListPointer->filter = 0;
		filterListPointer->type = "";
		filterListPointer->typeDescription = "";
		filterListPointer->legacyType = false;
		filterListPointer->sourceOnly = false;
		filterListPointer->sourceServiceSupported = false;
		filterListPointer->disabledFilterSupport = false;
		filterListPointer->loggingSupport = false;
		filterListPointer->supportsTime = false;
		filterListPointer->supportsFragments = false;	
		filterListPointer->supportsEstablished = false;
		filterListPointer->filterCommentsSupported = false;
		filterListPointer->showProtocol = true;
		filterListPointer->used = false;
		filterListPointer->showFilterZones = false;
		filterListPointer->showStop = false;
		filterListPointer->showFilterType = false;			// Does the filter have a type (i.e. like on Passport devices)
		filterListPointer->active = true;
		filterListPointer->next = 0;
	}

	return filterListPointer;
}


// Get a filter list by name/id (does not create what it cannot find)
Filter::filterListConfig *Filter::getOnlyFilterList(const char *name)
{
	// Variables...
	filterListConfig *filterListPointer = 0;

	filterListPointer = filterList;
	while (filterListPointer != 0)
	{
		if (filterListPointer->name.compare(name) == 0)
			return filterListPointer;
		else
			filterListPointer = filterListPointer->next;
	}

	return filterListPointer;
}


int Filter::copySourceToDestinationFilters(filterConfig *sourceFilter, filterConfig *destinationFilter)
{
	// Variables...
	filterObjectConfig *sourceObject = 0;
	filterObjectConfig *destinationObject = 0;

	destinationFilter->number = sourceFilter->number;
	destinationFilter->enabled = sourceFilter->enabled;
	destinationFilter->id = sourceFilter->id;
	destinationFilter->name.assign(sourceFilter->name);
	destinationFilter->internalId.assign(sourceFilter->internalId);
	destinationFilter->remarkFilter = sourceFilter->remarkFilter;
	destinationFilter->sourceServiceSupported = sourceFilter->sourceServiceSupported;
	destinationFilter->action = sourceFilter->action;	

	sourceObject = sourceFilter->protocol;
	while (sourceObject != 0)
	{
		destinationObject = addFilterObject(destinationFilter, protocol);
		copySourceToDestinationObjects(sourceObject, destinationObject);
		sourceObject = sourceObject->next;
	}

	sourceObject = sourceFilter->source;
	while (sourceObject != 0)
	{
		destinationObject = addFilterObject(destinationFilter, source);
		copySourceToDestinationObjects(sourceObject, destinationObject);
		sourceObject = sourceObject->next;
	}

	sourceObject = sourceFilter->sourceService;
	while (sourceObject != 0)
	{
		destinationObject = addFilterObject(destinationFilter, sourceService);
		copySourceToDestinationObjects(sourceObject, destinationObject);
		sourceObject = sourceObject->next;
	}

	sourceObject = sourceFilter->destination;
	while (sourceObject != 0)
	{
		destinationObject = addFilterObject(destinationFilter, destination);
		copySourceToDestinationObjects(sourceObject, destinationObject);
		sourceObject = sourceObject->next;
	}

	sourceObject = sourceFilter->destinationService;
	while (sourceObject != 0)
	{
		destinationObject = addFilterObject(destinationFilter, destinationService);
		copySourceToDestinationObjects(sourceObject, destinationObject);
		sourceObject = sourceObject->next;
	}

	sourceObject = sourceFilter->time;
	while (sourceObject != 0)
	{
		destinationObject = addFilterObject(destinationFilter, timeLimit);
		copySourceToDestinationObjects(sourceObject, destinationObject);
		sourceObject = sourceObject->next;
	}

	destinationFilter->log = sourceFilter->log;
	destinationFilter->logLevel = sourceFilter->logLevel;
	destinationFilter->established = sourceFilter->established;
	destinationFilter->fragments = sourceFilter->fragments;
	destinationFilter->sourceZone.assign(sourceFilter->sourceZone);
	destinationFilter->destZone.assign(sourceFilter->destZone);

	sourceObject = sourceFilter->through;
	while (sourceObject != 0)
	{
		destinationObject = addFilterObject(destinationFilter, through);
		copySourceToDestinationObjects(sourceObject, destinationObject);
		sourceObject = sourceObject->next;
	}

	sourceObject = sourceFilter->install;
	while (sourceObject != 0)
	{
		destinationObject = addFilterObject(destinationFilter, installed);
		copySourceToDestinationObjects(sourceObject, destinationObject);
		sourceObject = sourceObject->next;
	}

	destinationFilter->comment.assign(sourceFilter->comment);
	destinationFilter->type = sourceFilter->type;
	destinationFilter->stop = sourceFilter->stop;
	destinationFilter->inSet = sourceFilter->inSet;

	destinationFilter->deleteMe = false;
	destinationFilter->next = 0;

	return 0;
}


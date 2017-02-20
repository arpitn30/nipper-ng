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


Filter::netObjectListConfig *Filter::getObjectList(const char *name, const char *zone)					// Get Object List
{
	// Variables...
	netObjectListConfig *objectListPointer = 0;

	// If none exist...
	if (netObjectList == 0)
	{
		netObjectList = new (netObjectListConfig);
		objectListPointer = netObjectList;
	}

	// Search...
	else
	{
		objectListPointer = netObjectList;
		while ((objectListPointer->next != 0) && !((objectListPointer->name.compare(name) == 0) && (objectListPointer->zone.compare(zone) == 0)))
			objectListPointer = objectListPointer->next;
		if ((objectListPointer->name.compare(name) == 0) && (objectListPointer->zone.compare(zone) == 0))
			return objectListPointer;

		objectListPointer->next = new (netObjectListConfig);
		objectListPointer = objectListPointer->next;
	}

	// Init
	objectListPointer->type = anyObject;
	objectListPointer->name.assign(name);
	objectListPointer->zone.assign(zone);
	objectListPointer->tcp = false;
	objectListPointer->udp = false;
	objectListPointer->objectCommentSupported = false;
	objectListPointer->object = 0;
	objectListPointer->protocolSupported = false;
	objectListPointer->next = 0;

	return objectListPointer;
}


Filter::netObjectListConfig *Filter::getOnlyObjectList(const char *name, const char *zone)					// Get Only Object List
{
	// Variables...
	netObjectListConfig *objectListPointer = 0;

	// If none exist...
	if (netObjectList == 0)
		return 0;

	// Search...
	else
	{
		objectListPointer = netObjectList;
		while ((objectListPointer->next != 0) && !((objectListPointer->name.compare(name) == 0) && (objectListPointer->zone.compare(zone) == 0)))
			objectListPointer = objectListPointer->next;
		if ((objectListPointer->name.compare(name) == 0) && (objectListPointer->zone.compare(zone) == 0))
			return objectListPointer;
	}

	return 0;
}


Filter::filterObjectConfig *Filter::addObject(filterObjectConfig *objectPointer, filterObjectType objectType)	// Add Object to an object
{
	// Variables...
	filterObjectConfig *filterObjectPointer = 0;

	// Create...
	switch (objectType)
	{
		case interfaces:
			if (objectPointer->interfaces == 0)
			{
				objectPointer->interfaces = new (filterObjectConfig);
				filterObjectPointer = objectPointer->interfaces;
			}
			else
			{
				filterObjectPointer = objectPointer->interfaces;
				while (filterObjectPointer->next != 0)
					filterObjectPointer = filterObjectPointer->next;
				filterObjectPointer->next = new (filterObjectConfig);
				filterObjectPointer = filterObjectPointer->next;
			}
			filterObjectPointer->type = interfaceObject;
			break;

		case members:
			if (objectPointer->members == 0)
			{
				objectPointer->members = new (filterObjectConfig);
				filterObjectPointer = objectPointer->members;
			}
			else
			{
				filterObjectPointer = objectPointer->members;
				while (filterObjectPointer->next != 0)
					filterObjectPointer = filterObjectPointer->next;
				filterObjectPointer->next = new (filterObjectConfig);
				filterObjectPointer = filterObjectPointer->next;
			}
			filterObjectPointer->type = clusterMemberObject;
			break;

		case protocol:
			if (objectPointer->protocol == 0)
			{
				objectPointer->protocol = new (filterObjectConfig);
				filterObjectPointer = objectPointer->protocol;
			}
			else
			{
				filterObjectPointer = objectPointer->protocol;
				while (filterObjectPointer->next != 0)
					filterObjectPointer = filterObjectPointer->next;
				filterObjectPointer->next = new (filterObjectConfig);
				filterObjectPointer = filterObjectPointer->next;
			}
			filterObjectPointer->type = protocolObject;
			break;

		case sourceService:
			if (objectPointer->sourcePort == 0)
			{
				objectPointer->sourcePort = new (filterObjectConfig);
				filterObjectPointer = objectPointer->sourcePort;
			}
			else
			{
				filterObjectPointer = objectPointer->sourcePort;
				while (filterObjectPointer->next != 0)
					filterObjectPointer = filterObjectPointer->next;
				filterObjectPointer->next = new (filterObjectConfig);
				filterObjectPointer = filterObjectPointer->next;
			}
			filterObjectPointer->type = portObject;
			break;

		default:
			if (objectPointer->destinationPort == 0)
			{
				objectPointer->destinationPort = new (filterObjectConfig);
				filterObjectPointer = objectPointer->destinationPort;
			}
			else
			{
				filterObjectPointer = objectPointer->destinationPort;
				while (filterObjectPointer->next != 0)
					filterObjectPointer = filterObjectPointer->next;
				filterObjectPointer->next = new (filterObjectConfig);
				filterObjectPointer = filterObjectPointer->next;
			}
			filterObjectPointer->type = portObject;
			break;
	}

	// Init...
	filterObjectPointer->serviceOper = serviceOperAny;
	filterObjectPointer->protocol = 0;
	filterObjectPointer->sourcePort = 0;
	filterObjectPointer->destinationPort = 0;
	filterObjectPointer->internal = true;
	filterObjectPointer->firewall = false;
	filterObjectPointer->management = false;
	filterObjectPointer->interfaces = 0;
	filterObjectPointer->interfaceIndex = 0;
	filterObjectPointer->members = 0;
	filterObjectPointer->dhcp = false;
	filterObjectPointer->deleteMe = false;

	filterObjectPointer->next = 0;

	return filterObjectPointer;
}


Filter::filterObjectConfig *Filter::addObject(netObjectListConfig *objectListPointer)	// Add Object to the object list
{
	// Variables...
	filterObjectConfig *filterObjectPointer = 0;

	// If first...
	if (objectListPointer->object == 0)
	{
		objectListPointer->object = new (filterObjectConfig);
		filterObjectPointer = objectListPointer->object;
	}
	else
	{
		filterObjectPointer = objectListPointer->object;
		while (filterObjectPointer->next != 0)
			filterObjectPointer = filterObjectPointer->next;
		filterObjectPointer->next = new (filterObjectConfig);
		filterObjectPointer = filterObjectPointer->next;
	}

	// Init...
	filterObjectPointer->type = anyObject;
	filterObjectPointer->serviceOper = serviceOperAny;
	filterObjectPointer->protocol = 0;
	filterObjectPointer->sourcePort = 0;
	filterObjectPointer->destinationPort = 0;
	filterObjectPointer->internal = true;
	filterObjectPointer->firewall = false;
	filterObjectPointer->management = false;
	filterObjectPointer->interfaces = 0;
	filterObjectPointer->interfaceIndex = 0;
	filterObjectPointer->members = 0;
	filterObjectPointer->dhcp = false;
	filterObjectPointer->deleteMe = false;

	filterObjectPointer->next = 0;

	return filterObjectPointer;
}


Filter::filterObjectConfig *Filter::getObject(const char *name, netObjectListConfig *inList)
{
	// Variables...
	netObjectListConfig *objectListPointer = 0;
	filterObjectConfig *filterObjectPointer = 0;

	if (inList != 0)
		objectListPointer = inList;
	else
		objectListPointer = netObjectList;
	while (objectListPointer != 0)
	{
		filterObjectPointer = objectListPointer->object;
		while (filterObjectPointer != 0)
		{
			if (filterObjectPointer->name.compare(name) == 0)
				return filterObjectPointer;
			filterObjectPointer = filterObjectPointer->next;
		}
		if (inList != 0)
			objectListPointer = 0;
		else
			objectListPointer = objectListPointer->next;
	}

	return filterObjectPointer;
}


Filter::filterObjectConfig *Filter::getServiceListObject(const char *objectName)
{
	// Variables...
	netObjectListConfig *objectListPointer = netObjectList;
	filterObjectConfig *filterObjectPointer = 0;

	while (objectListPointer != 0)
	{
		if ((objectListPointer->type == enhancedServiceObject) || (objectListPointer->type == serviceListObject))
		{
			filterObjectPointer = objectListPointer->object;
			while (filterObjectPointer != 0)
			{
				if (filterObjectPointer->label.empty())
				{
					if (strcasecmp(filterObjectPointer->name.c_str(), objectName) == 0)
						return filterObjectPointer;
				}
				else
				{
					if (strcasecmp(filterObjectPointer->label.c_str(), objectName) == 0)
						return filterObjectPointer;
				}
				filterObjectPointer = filterObjectPointer->next;
			}
		}

		objectListPointer = objectListPointer->next;
	}

	return 0;
}


Filter::filterObjectConfig *Filter::getAddressListObject(const char *objectName, const char *zone)
{
	// Variables...
	netObjectListConfig *objectListPointer = netObjectList;
	filterObjectConfig *filterObjectPointer = 0;

	objectListPointer = netObjectList;
	while (objectListPointer != 0)
	{
		if ((objectListPointer->type == addressBookObject) && ((objectListPointer->name.compare(zone) == 0) || (strlen(zone) == 0)))
		{
			filterObjectPointer = objectListPointer->object;
			while (filterObjectPointer != 0)
			{
				if (filterObjectPointer->label.empty())
				{
					if (strcasecmp(filterObjectPointer->name.c_str(), objectName) == 0)
						return filterObjectPointer;
				}
				else
				{
					if (strcasecmp(filterObjectPointer->label.c_str(), objectName) == 0)
						return filterObjectPointer;
				}
				filterObjectPointer = filterObjectPointer->next;
			}
		}

		objectListPointer = objectListPointer->next;
	}

	return 0;
}


int Filter::copySourceToDestinationObjects(filterObjectConfig *sourceObject, filterObjectConfig *destinationObject)
{
	// Variables...
	filterObjectConfig *subSourceObject = 0;
	filterObjectConfig *subDestinationObject = 0;

	destinationObject->type = sourceObject->type;
	destinationObject->label.assign(sourceObject->label);
	destinationObject->name.assign(sourceObject->name);
	destinationObject->netmask.assign(sourceObject->netmask);
	destinationObject->comment.assign(sourceObject->comment);
	destinationObject->serviceOper = sourceObject->serviceOper;

	subSourceObject = sourceObject->protocol;
	while (subSourceObject != 0)
	{
		subDestinationObject = addObject(destinationObject, protocol);
		copySourceToDestinationObjects(subSourceObject, subDestinationObject);
		subSourceObject = subSourceObject->next;
	}

	subSourceObject = sourceObject->sourcePort;
	while (subSourceObject != 0)
	{
		subDestinationObject = addObject(destinationObject, sourceService);
		copySourceToDestinationObjects(subSourceObject, subDestinationObject);
		subSourceObject = subSourceObject->next;
	}

	subSourceObject = sourceObject->destinationPort;
	while (subSourceObject != 0)
	{
		subDestinationObject = addObject(destinationObject, destinationService);
		copySourceToDestinationObjects(subSourceObject, subDestinationObject);
		subSourceObject = subSourceObject->next;
	}

	destinationObject->internal = sourceObject->internal;
	destinationObject->firewall = sourceObject->firewall;
	destinationObject->management = sourceObject->management;
	destinationObject->interfaceIndex = sourceObject->interfaceIndex;
	destinationObject->dhcp = sourceObject->dhcp;

	subSourceObject = sourceObject->interfaces;
	while (subSourceObject != 0)
	{
		subDestinationObject = addObject(destinationObject, interfaces);
		copySourceToDestinationObjects(subSourceObject, subDestinationObject);
		subSourceObject = subSourceObject->next;
	}

	subSourceObject = sourceObject->members;
	while (subSourceObject != 0)
	{
		subDestinationObject = addObject(destinationObject, members);
		copySourceToDestinationObjects(subSourceObject, subDestinationObject);
		subSourceObject = subSourceObject->next;
	}

	destinationObject->deleteMe = false;
	destinationObject->next = 0;

	return 0;
}


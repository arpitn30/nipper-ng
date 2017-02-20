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


void processNameMappings(struct nipperConfig *nipper)
{
	// Variables...
	char tempString[nipper->maxSize];
	struct filterObjectConfig *filterObjectPointer = 0;
	struct filterConfig *filterPointer = 0;
	struct filterListConfig *filterListPointer = 0;
	struct objectListConfig *objectListPointer = 0;
	struct objectConfig *objectPointer = 0;

	// Convert filters names to ip addresses
	if ((nipper->filterList != 0) && (nipper->objectList != 0))
	{
		filterListPointer = nipper->filterList;
		while (filterListPointer != 0)
		{
			filterPointer = filterListPointer->filter;
			while (filterPointer != 0)
			{
				// Source...
				filterObjectPointer = filterPointer->source;
				while (filterObjectPointer != 0)
				{
					objectListPointer = nipper->objectList;
					if ((nipper->deviceType == type_sos_firewall) && (objectListPointer != 0))
					{
						while ((strcasecmp(filterListPointer->fromZone, objectListPointer->name) != 0) && (objectListPointer->next != 0))
							objectListPointer = objectListPointer->next;
						if (strcasecmp(filterListPointer->fromZone, objectListPointer->name) != 0)
							objectListPointer = 0;
					}
					while (objectListPointer != 0)
					{
						objectPointer = objectListPointer->object;
						while (objectPointer != 0)
						{
							if (strcasecmp(objectPointer->name, filterObjectPointer->name) == 0)
							{
								if (objectPointer->type == object_type_network)
								{
									sprintf(tempString, "%s %s", objectPointer->address, objectPointer->netMask);
									strncpy(filterObjectPointer->name, tempString, sizeof(filterObjectPointer->name) - 1);
									filterObjectPointer->name[strlen(tempString)] = 0;
								}
								else if (objectPointer->type == object_type_machinesrange)
								{
									sprintf(tempString, "%s - %s", objectPointer->address, objectPointer->netMask);
									strncpy(filterObjectPointer->name, tempString, sizeof(filterObjectPointer->name) - 1);
									filterObjectPointer->name[strlen(tempString)] = 0;
								}
								else if ((objectPointer->type != object_type_group) && (objectPointer->type != object_type_gateway_cluster))
								{
									strncpy(filterObjectPointer->name, objectPointer->address, sizeof(filterObjectPointer->name) - 1);
									filterObjectPointer->name[strlen(objectPointer->address)] = 0;
								}
							}
							objectPointer = objectPointer->next;
						}
						objectListPointer = objectListPointer->next;
					}
					filterObjectPointer = filterObjectPointer->next;
				}

				// Destination...
				filterObjectPointer = filterPointer->destination;
				while (filterObjectPointer != 0)
				{
					objectListPointer = nipper->objectList;
					if ((nipper->deviceType == type_sos_firewall) && (objectListPointer != 0))
					{
						while ((strcasecmp(filterListPointer->toZone, objectListPointer->name) != 0) && (objectListPointer->next != 0))
							objectListPointer = objectListPointer->next;
						if (strcasecmp(filterListPointer->toZone, objectListPointer->name) != 0)
							objectListPointer = 0;
					}
					while (objectListPointer != 0)
					{
						objectPointer = objectListPointer->object;
						while (objectPointer != 0)
						{
							if (strcasecmp(objectPointer->name, filterObjectPointer->name) == 0)
							{
								if (objectPointer->type == object_type_network)
								{
									sprintf(tempString, "%s %s", objectPointer->address, objectPointer->netMask);
									strncpy(filterObjectPointer->name, tempString, sizeof(filterObjectPointer->name) - 1);
									filterObjectPointer->name[strlen(tempString)] = 0;
								}
								else if (objectPointer->type == object_type_machinesrange)
								{
									sprintf(tempString, "%s - %s", objectPointer->address, objectPointer->netMask);
									strncpy(filterObjectPointer->name, tempString, sizeof(filterObjectPointer->name) - 1);
									filterObjectPointer->name[strlen(tempString)] = 0;
								}
								else if ((objectPointer->type != object_type_group) && (objectPointer->type != object_type_gateway_cluster))
								{
									strncpy(filterObjectPointer->name, objectPointer->address, sizeof(filterObjectPointer->name) - 1);
									filterObjectPointer->name[strlen(objectPointer->address)] = 0;
								}
							}
							objectPointer = objectPointer->next;
						}
						objectListPointer = objectListPointer->next;
					}
					filterObjectPointer = filterObjectPointer->next;
				}

				// Through...
				filterObjectPointer = filterPointer->through;
				while (filterObjectPointer != 0)
				{
					objectListPointer = nipper->objectList;
					while (objectListPointer != 0)
					{
						objectPointer = objectListPointer->object;
						while (objectPointer != 0)
						{
							if (strcasecmp(objectPointer->name, filterObjectPointer->name) == 0)
							{
								if (objectPointer->type == object_type_network)
								{
									sprintf(tempString, "%s %s", objectPointer->address, objectPointer->netMask);
									strncpy(filterObjectPointer->name, tempString, sizeof(filterObjectPointer->name) - 1);
									filterObjectPointer->name[strlen(tempString)] = 0;
								}
								else if (objectPointer->type == object_type_machinesrange)
								{
									sprintf(tempString, "%s - %s", objectPointer->address, objectPointer->netMask);
									strncpy(filterObjectPointer->name, tempString, sizeof(filterObjectPointer->name) - 1);
									filterObjectPointer->name[strlen(tempString)] = 0;
								}
								else if ((objectPointer->type != object_type_group) && (objectPointer->type != object_type_gateway_cluster))
								{
									strncpy(filterObjectPointer->name, objectPointer->address, sizeof(filterObjectPointer->name) - 1);
									filterObjectPointer->name[strlen(objectPointer->address)] = 0;
								}
							}
							objectPointer = objectPointer->next;
						}
						objectListPointer = objectListPointer->next;
					}
					filterObjectPointer = filterObjectPointer->next;
				}

				// Installed on...
				filterObjectPointer = filterPointer->install;
				while (filterObjectPointer != 0)
				{
					objectListPointer = nipper->objectList;
					while (objectListPointer != 0)
					{
						objectPointer = objectListPointer->object;
						while (objectPointer != 0)
						{
							if (strcasecmp(objectPointer->name, filterObjectPointer->name) == 0)
							{
								if (objectPointer->type == object_type_network)
								{
									sprintf(tempString, "%s %s", objectPointer->address, objectPointer->netMask);
									strncpy(filterObjectPointer->name, tempString, sizeof(filterObjectPointer->name) - 1);
									filterObjectPointer->name[strlen(tempString)] = 0;
								}
								else if (objectPointer->type == object_type_machinesrange)
								{
									sprintf(tempString, "%s - %s", objectPointer->address, objectPointer->netMask);
									strncpy(filterObjectPointer->name, tempString, sizeof(filterObjectPointer->name) - 1);
									filterObjectPointer->name[strlen(tempString)] = 0;
								}
								else if ((objectPointer->type != object_type_group) && (objectPointer->type != object_type_gateway_cluster))
								{
									strncpy(filterObjectPointer->name, objectPointer->address, sizeof(filterObjectPointer->name) - 1);
									filterObjectPointer->name[strlen(objectPointer->address)] = 0;
								}
							}
							objectPointer = objectPointer->next;
						}
						objectListPointer = objectListPointer->next;
					}
					filterObjectPointer = filterObjectPointer->next;
				}

				filterPointer = filterPointer->next;
			}
			filterListPointer = filterListPointer->next;
		}
	}
}

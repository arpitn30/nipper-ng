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


// Process Access List
void processPIXAccessList(char *line, struct nipperConfig *nipper)
{
	// Variables...
	char tempString[nipper->maxSize];
	char tempString2[nipper->maxSize];
	struct filterConfig *filterPointer = 0;
	struct filterObjectConfig *filterObjectPointer = 0;
	struct filterListConfig *filterListPointer = 0;
	struct objectListConfig *objectListPointer = 0;
	struct objectConfig *objectPointer = 0;
	struct ciscoCommand command;
	int tempInt = 0;

	// Init
	command = splitLine(line);
	memset(tempString, 0, nipper->maxSize);

	// Access Lists standard, extended, remark, ethertype
	if (command.parts > 3)
	{

		// If old, standard or extended access list...
		if ((strcmp(command.part[2], "permit") == 0) || (strcmp(command.part[2], "deny") == 0) || (strcmp(command.part[2], "standard") == 0) || (strcmp(command.part[2], "extended") == 0))
		{
			// Debug
			if (nipper->debugMode == true)
			{
				printf("Access-List Line: %s\n", line);
			}

			// Get / Create pointer to access list...
			filterListPointer = getFilterList(nipper, command.part[1], "", 0);

			// Establish what type of access list it is
			if (strcmp(command.part[2], "standard") == 0)
			{
				filterListPointer->type = access_std;
				nipper->pix->standardAccessList++;
				tempInt = 3;
			}
			else if (strcmp(command.part[2], "extended") == 0)
			{
				filterListPointer->type = access_ext;
				nipper->pix->extendedAccessList++;
				tempInt = 3;
			}
			else
			{
				filterListPointer->type = access_old;
				nipper->pix->oldAccessList++;
				tempInt = 2;
			}

			// Does a permission already exist?
			if (filterListPointer->filter == 0)
			{
				// Create Permission structure
				filterListPointer->filter = malloc(sizeof(struct filterConfig));
				filterPointer = filterListPointer->filter;
			}
			else
			{
				// Search
				filterPointer = filterListPointer->filter;
				while (filterPointer->next != 0)
					filterPointer = filterPointer->next;

				// Create Permission structure
				filterPointer->next = malloc(sizeof(struct filterConfig));
				filterPointer = filterPointer->next;
			}

			// Init Permission struct
			memset(filterPointer, 0, sizeof(struct filterConfig));
			filterPointer->protocolType = object_type_protocol;
			filterPointer->enabled = true;

			// Permit or Deny?
			if (strcmp(command.part[tempInt], "permit") == 0)
			{
				filterPointer->log = false;
				filterPointer->action = filter_action_accept;
			}
			else
			{
				filterPointer->log = true;
				filterPointer->action = filter_action_drop;
			}
			tempInt++;

			// If access list is old type or extended...
			if (filterListPointer->type != access_std)
			{
				// Protocol
				if (strcmp(command.part[tempInt], "object-group") == 0)
				{
					filterPointer->protocolType = object_type_object;
					tempInt++;
				}
				strncpy(filterPointer->protocol, command.part[tempInt], sizeof(filterPointer->protocol) - 1);
				tempInt++;
			}

			// Source
			if (strcmp(command.part[tempInt], "interface") == 0)
			{
				tempInt++;
				filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_source);
				filterObjectPointer->type = object_type_interface;
			}
			else if (strcmp(command.part[tempInt], "object-group") == 0)
			{
				tempInt++;
				filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_source);
				filterObjectPointer->type = object_type_object;
			}
			else if (strcmp(command.part[tempInt], "any") == 0)
			{
				filterObjectPointer = getFilterMember(filterPointer, "Any", object_filter_source);
				filterObjectPointer->type = object_type_any;
			}
			else if (strcmp(command.part[tempInt], "host") == 0)
			{
				tempInt++;
				filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_source);
				filterObjectPointer->type = object_type_host;
			}
			else
			{
				filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_source);
				tempInt++;
				strncpy(filterObjectPointer->netMask, command.part[tempInt], sizeof(filterObjectPointer->netMask) - 1);
				filterObjectPointer->type = object_type_network;
			}
			tempInt++;

			// Is there more
			if ((command.parts > tempInt) && (filterListPointer->type != access_std))
			{
				// Source Service
				if (strcmp(command.part[tempInt], "object-group") == 0)
				{
					// Check to make sure this is a service and not the destination
					if (nipper->objectList != 0)
					{
						objectListPointer = nipper->objectList;
						while ((objectListPointer->next != 0) && (strcmp(objectListPointer->name, "OBJECTLIST") != 0))
							objectListPointer = objectListPointer->next;
						if (strcmp(objectListPointer->name, "OBJECTLIST") == 0)
						{
							objectPointer = objectListPointer->object;
							while ((objectPointer->next != 0) && (strcmp(objectPointer->name, command.part[tempInt + 1]) != 0))
								objectPointer = objectPointer->next;
	
							if ((strcmp(objectPointer->name, command.part[tempInt + 1]) == 0) && (objectPointer->type == object_type_service))
							{
								tempInt++;
								filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
								filterObjectPointer->serviceOp = service_oper_object;
								tempInt++;
							}
						}
					}
				}
				else if (strcmp(command.part[tempInt], "range") == 0)
				{
					tempInt++;
					filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
					filterObjectPointer->serviceOp = service_oper_range;
					tempInt++;
					strncpy(filterObjectPointer->netMask, command.part[tempInt], sizeof(filterObjectPointer->netMask) - 1);
					tempInt++;
				}
				else if (strcmp(command.part[tempInt], "eq") == 0)
				{
					tempInt++;
					filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
					filterObjectPointer->serviceOp = service_oper_eq;
					tempInt++;
				}
				else if (strcmp(command.part[tempInt], "neq") == 0)
				{
					tempInt++;
					filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
					filterObjectPointer->serviceOp = service_oper_neq;
					tempInt++;
				}
				else if (strcmp(command.part[tempInt], "lt") == 0)
				{
					tempInt++;
					filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
					filterObjectPointer->serviceOp = service_oper_lt;
					tempInt++;
				}
				else if (strcmp(command.part[tempInt], "gt") == 0)
				{
					tempInt++;
					filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
					filterObjectPointer->serviceOp = service_oper_gt;
					tempInt++;
				}

				// Destination
				if (strcmp(command.part[tempInt], "interface") == 0)
				{
					tempInt++;
					filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_destination);
					filterObjectPointer->type = object_type_interface;
				}
				else if (strcmp(command.part[tempInt], "object-group") == 0)
				{
					tempInt++;
					filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_destination);
					filterObjectPointer->type = object_type_object;
				}
				else if (strcmp(command.part[tempInt], "any") == 0)
				{
					filterObjectPointer = getFilterMember(filterPointer, "Any", object_filter_destination);
					filterObjectPointer->type = object_type_any;
				}
				else if (strcmp(command.part[tempInt], "host") == 0)
				{
					tempInt++;
					filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_destination);
					filterObjectPointer->type = object_type_host;
				}
				else
				{
					filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_destination);
					filterObjectPointer->type = object_type_network;
					tempInt++;
					strncpy(filterObjectPointer->netMask, command.part[tempInt], sizeof(filterObjectPointer->netMask) - 1);
				}
				tempInt++;

				// Destination Service
				if (command.parts > tempInt)
				{
					if (strcmp(command.part[tempInt], "object-group") == 0)
					{
						tempInt++;
						filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
						filterObjectPointer->serviceOp = service_oper_object;
						tempInt++;
					}
					else if (strcmp(command.part[tempInt], "range") == 0)
					{
						tempInt++;
						filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
						filterObjectPointer->serviceOp = service_oper_range;
						tempInt++;
						strncpy(filterObjectPointer->netMask, command.part[tempInt], sizeof(filterObjectPointer->netMask) - 1);
						tempInt++;
					}
					else if (strcmp(command.part[tempInt], "eq") == 0)
					{
						tempInt++;
						filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
						filterObjectPointer->serviceOp = service_oper_eq;
						tempInt++;
					}
					else if (strcmp(command.part[tempInt], "neq") == 0)
					{
						tempInt++;
						filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
						filterObjectPointer->serviceOp = service_oper_neq;
						tempInt++;
					}
					else if (strcmp(command.part[tempInt], "lt") == 0)
					{
						tempInt++;
						filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
						filterObjectPointer->serviceOp = service_oper_lt;
						tempInt++;
					}
					else if (strcmp(command.part[tempInt], "gt") == 0)
					{
						tempInt++;
						filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
						filterObjectPointer->serviceOp = service_oper_gt;
						tempInt++;
					}
				}

				// Options...
				while (command.parts > tempInt)
				{
					if (filterListPointer->type == access_old)
					{
						filterListPointer->type = access_ext;
						nipper->pix->oldAccessList--;
						nipper->pix->extendedAccessList++;
					}

					// Inactive
					if (strcmp(command.part[tempInt], "inactive") == 0)
						filterPointer->enabled = false;

					// Active Time Range
					else if (strcmp(command.part[tempInt], "time-range") == 0)
						tempInt++;

					// Log
					else if (strcmp(command.part[tempInt], "log") == 0)
					{
						filterPointer->log = true;
						if (command.parts > tempInt + 1)
						{
							tempInt++;
							while (((strcmp(command.part[tempInt], "inactive") != 0) || (strcmp(command.part[tempInt], "time-range") != 0)) && (command.parts > tempInt))
							{
								if (strcmp(command.part[tempInt], "disable") == 0)
									filterPointer->log = false;
								tempInt++;
							}
							tempInt--;
						}
					}

					tempInt++;
				}
			}
		}

		// Access List Remark
		else if (strcmp(command.part[2], "remark") == 0)
		{
			// Debug
			if (nipper->debugMode == true)
			{
				printf("Access-List Remark Line: %s\n", line);
			}

			// Get / Create pointer to access list...
			filterListPointer = getFilterList(nipper, command.part[1], "", 0);

			// Does a permission already exist?
			if (filterListPointer->filter == 0)
			{
				// Create Permission structure
				filterListPointer->filter = malloc(sizeof(struct filterConfig));
				filterPointer = filterListPointer->filter;
			}
			else
			{
				// Search
				filterPointer = filterListPointer->filter;
				while (filterPointer->next != 0)
					filterPointer = filterPointer->next;

				// Create Permission structure
				filterPointer->next = malloc(sizeof(struct filterConfig));
				filterPointer = filterPointer->next;
			}

			// Init Permission struct
			memset(filterPointer, 0, sizeof(struct filterConfig));
			filterPointer->action = filter_action_remark;

			// Set Remark...
			for (tempInt = 3; tempInt < command.parts; tempInt++)
			{
				sprintf(tempString2, "%s%s ",tempString, command.part[tempInt]);
				strcpy(tempString, tempString2);
			}
			tempString[strlen(tempString) - 1] = 0;
			strncpy(filterPointer->remark, tempString, sizeof(filterPointer->remark) - 1);
		}

		// Access List Ethertype
		else if (strcmp(command.part[2], "ethertype") == 0)
		{ }
	}

	// Alert Interval
	else if (strcmp(command.part[1], "alert-interval") == 0)
	{
		// Debug
		if (nipper->debugMode == true)
		{
			printf("Access-List Alert Interval Line: %s\n", line);
		}
		nipper->pix->accessListAlertInterval = atoi(command.part[2]);
	}

	// Deny Flow Max
	else if (strcmp(command.part[1], "alert-interval") == 0)
	{
		// Debug
		if (nipper->debugMode == true)
		{
			printf("Access-List Deny-Flow-Max Line: %s\n", line);
		}
		nipper->pix->accessListDenyFlowMax = atoi(command.part[2]);
	}
}


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

// This file contains the code to process Passport filters


// Process a Filter Set...
void processFilterSetPAS(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct filterListConfig *filterListPointer = 0;
	struct filterListConfig *filterListFromPointer = 0;
	struct filterConfig *filterPointer = 0;
	struct filterConfig *filterSearchPointer = 0;
	struct filterObjectConfig *filterObjectPointer = 0;
	struct filterObjectConfig *filterObjectFromPointer = 0;
	struct ciscoCommand command;
	char tempString[nipper->maxSize];

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Filter Set Line: %s\n", line);
	}

	// Split the command line up
	command = splitLine(line);

	// Get Filter set pointer...
	filterListPointer = getFilterList(nipper, command.part[3], "", false);

	// Filter Set Create?
	if (strcmp(command.part[4], "create") == 0)
	{
		stripQuotes(command.part[6], tempString, nipper->maxSize);
		strncpy(filterListPointer->listName, tempString, sizeof(filterListPointer->listName) - 1);
	}

	// Add filter to the set
	else if (strcmp(command.part[4], "add-filter") == 0)
	{
		// Find filter...
		filterListFromPointer = getFilterList(nipper, "**UNASSIGNED**", "", false);
		filterSearchPointer = filterListFromPointer->filter;
		if (filterSearchPointer != 0)
		{
			while ((filterSearchPointer->next != 0) && (filterSearchPointer->id != atoi(command.part[5])))
				filterSearchPointer = filterSearchPointer->next;
			if (filterSearchPointer->id == atoi(command.part[5]))
			{

				// Set it found...
				filterSearchPointer->inSet = true;

				// If first filter in destination filter set...
				if (filterListPointer->filter == 0)
				{
					filterListPointer->filter = malloc(sizeof(struct filterConfig));
					filterPointer = filterListPointer->filter;
				}
				else
				{
					filterPointer = filterListPointer->filter;
					while (filterPointer->next != 0)
						filterPointer = filterPointer->next;
					filterPointer->next = malloc(sizeof(struct filterConfig));
					filterPointer = filterPointer->next;
				}

				// Copy the settings...
				memset(filterPointer, 0, sizeof(struct filterConfig));
				filterPointer->id = filterSearchPointer->id;
				filterPointer->enabled = filterSearchPointer->enabled;
				filterPointer->action = filterSearchPointer->action;
				filterPointer->log = filterSearchPointer->log;
				strcpy(filterPointer->remark, filterSearchPointer->remark);
				strcpy(filterPointer->protocol, filterSearchPointer->protocol);
				filterPointer->protocolType = filterSearchPointer->protocolType;
				filterPointer->established = filterSearchPointer->established;
				filterPointer->fragments = filterSearchPointer->fragments;
				filterPointer->filterType = filterSearchPointer->filterType;
				filterPointer->stop = filterSearchPointer->stop;
				filterPointer->inSet = filterSearchPointer->inSet;

				// Source Objects...
				filterObjectFromPointer = filterSearchPointer->source;
				while (filterObjectFromPointer != 0)
				{
					// If first object member...
					if (filterPointer->source == 0)
					{
						filterPointer->source = malloc(sizeof(struct filterObjectConfig));
						filterObjectPointer = filterPointer->source;
					}
					else
					{
						filterObjectPointer = filterPointer->source;
						while (filterObjectPointer->next != 0)
							filterObjectPointer = filterObjectPointer->next;
						filterObjectPointer->next = malloc(sizeof(struct filterObjectConfig));
						filterObjectPointer = filterObjectPointer->next;
					}

					// Copy data...
					memset(filterObjectPointer, 0, sizeof(struct filterObjectConfig));
					strcpy(filterObjectPointer->name, filterObjectFromPointer->name);
					strcpy(filterObjectPointer->netMask, filterObjectFromPointer->netMask);
					filterObjectPointer->serviceOp = filterObjectFromPointer->serviceOp;
					filterObjectPointer->type = filterObjectFromPointer->type;

					filterObjectFromPointer = filterObjectFromPointer->next;
				}

				// Source ServiceObjects...
				filterObjectFromPointer = filterSearchPointer->sourceService;
				while (filterObjectFromPointer != 0)
				{
					// If first object member...
					if (filterPointer->sourceService == 0)
					{
						filterPointer->sourceService = malloc(sizeof(struct filterObjectConfig));
						filterObjectPointer = filterPointer->sourceService;
					}
					else
					{
						filterObjectPointer = filterPointer->sourceService;
						while (filterObjectPointer->next != 0)
							filterObjectPointer = filterObjectPointer->next;
						filterObjectPointer->next = malloc(sizeof(struct filterObjectConfig));
						filterObjectPointer = filterObjectPointer->next;
					}

					// Copy data...
					memset(filterObjectPointer, 0, sizeof(struct filterObjectConfig));
					strcpy(filterObjectPointer->name, filterObjectFromPointer->name);
					strcpy(filterObjectPointer->netMask, filterObjectFromPointer->netMask);
					filterObjectPointer->serviceOp = filterObjectFromPointer->serviceOp;
					filterObjectPointer->type = filterObjectFromPointer->type;

					filterObjectFromPointer = filterObjectFromPointer->next;
				}

				// Destination Objects...
				filterObjectFromPointer = filterSearchPointer->destination;
				while (filterObjectFromPointer != 0)
				{
					// If first object member...
					if (filterPointer->destination == 0)
					{
						filterPointer->destination = malloc(sizeof(struct filterObjectConfig));
						filterObjectPointer = filterPointer->destination;
					}
					else
					{
						filterObjectPointer = filterPointer->destination;
						while (filterObjectPointer->next != 0)
							filterObjectPointer = filterObjectPointer->next;
						filterObjectPointer->next = malloc(sizeof(struct filterObjectConfig));
						filterObjectPointer = filterObjectPointer->next;
					}

					// Copy data...
					memset(filterObjectPointer, 0, sizeof(struct filterObjectConfig));
					strcpy(filterObjectPointer->name, filterObjectFromPointer->name);
					strcpy(filterObjectPointer->netMask, filterObjectFromPointer->netMask);
					filterObjectPointer->serviceOp = filterObjectFromPointer->serviceOp;
					filterObjectPointer->type = filterObjectFromPointer->type;

					filterObjectFromPointer = filterObjectFromPointer->next;
				}

				// Destination Service Objects...
				filterObjectFromPointer = filterSearchPointer->destinationService;
				while (filterObjectFromPointer != 0)
				{
					// If first object member...
					if (filterPointer->destinationService == 0)
					{
						filterPointer->destinationService = malloc(sizeof(struct filterObjectConfig));
						filterObjectPointer = filterPointer->destinationService;
					}
					else
					{
						filterObjectPointer = filterPointer->destinationService;
						while (filterObjectPointer->next != 0)
							filterObjectPointer = filterObjectPointer->next;
						filterObjectPointer->next = malloc(sizeof(struct filterObjectConfig));
						filterObjectPointer = filterObjectPointer->next;
					}

					// Copy data...
					memset(filterObjectPointer, 0, sizeof(struct filterObjectConfig));
					strcpy(filterObjectPointer->name, filterObjectFromPointer->name);
					strcpy(filterObjectPointer->netMask, filterObjectFromPointer->netMask);
					filterObjectPointer->serviceOp = filterObjectFromPointer->serviceOp;
					filterObjectPointer->type = filterObjectFromPointer->type;

					filterObjectFromPointer = filterObjectFromPointer->next;
				}
			}
		}
	}
}


// Add a source / destination...
struct filterObjectConfig *addPASFilterSourceDestination(struct filterConfig *filterPointer, char *address, int objectType)
{
	// Variables...
	struct filterObjectConfig *filterObjectPointer = 0;
	char *slashChar;
	int size = 0;

	// Check that if it is default...
	if ((strcasecmp(address, "default") == 0) || (strcmp(address, "0.0.0.0/0.0.0.0") == 0))
	{
		filterObjectPointer = getFilterMember(filterPointer, "Any", objectType);
		filterObjectPointer->type = object_type_any;
	}

	else
	{
		// Get size...
		size = strlen(address);
	
		// Find the / character (if one exists)
		slashChar = strchr(address, '/');
	
		// Set string terminator...
		if (slashChar != NULL)
			slashChar[0] = 0;
	
		// Create object
		filterObjectPointer = getFilterMember(filterPointer, address, objectType);
	
		// Set mask...
		if (slashChar != NULL)
		{
			if (strlen(slashChar + 1) < 3)
				setMaskFromCIDR(filterObjectPointer->netMask, atoi(slashChar + 1));
			else
				strncpy(filterObjectPointer->netMask, slashChar + 1, sizeof(filterObjectPointer->netMask) - 1);
			if (strcmp(filterObjectPointer->netMask, "255.255.255.255") == 0)
				filterObjectPointer->type = object_type_host;
			else
				filterObjectPointer->type = object_type_network;
		}
		else
			filterObjectPointer->type = object_type_host;
	}

	return filterObjectPointer;
}


// Process a Create Filter...
void processCreateFilterPAS(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct ciscoCommand command;
	struct filterListConfig *filterListPointer = 0;
	struct filterConfig *filterPointer = 0;
	struct filterObjectConfig *filterObjectPointer = 0;
	int tempInt = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Filter Create Line: %s\n", line);
	}

	// Split the command line up
	command = splitLine(line);

	if ((strcmp(command.part[3], "source") == 0) || (strcmp(command.part[3], "destination") == 0) || (strcmp(command.part[3], "global") == 0))
	{
		// Create & init structure...
		filterListPointer = getFilterList(nipper, "**UNASSIGNED**", "", false);

		// If first filter...
		if (filterListPointer->filter == 0)
		{
			filterListPointer->filter = malloc(sizeof(struct filterConfig));
			filterPointer = filterListPointer->filter;
		}
		else
		{
			filterPointer = filterListPointer->filter;
			while (filterPointer->next != 0)
				filterPointer = filterPointer->next;
			filterPointer->next = malloc(sizeof(struct filterConfig));
			filterPointer = filterPointer->next;
		}

		// Init...
		memset(filterPointer, 0, sizeof(struct filterConfig));
		filterPointer->action = filter_action_default;
		filterPointer->stop = true;
		filterPointer->inSet = false;

		// Source
		if (strcmp(command.part[3], "source") == 0)
			filterPointer->filterType = filter_type_source;
		// Destination
		else if (strcmp(command.part[3], "destination") == 0)
			filterPointer->filterType = filter_type_destination;
		// Global
		else
			filterPointer->filterType = filter_type_global;
		tempInt = 4;

		while (tempInt < command.parts)
		{
			// Source?
			if (strcmp(command.part[tempInt], "src-ip") == 0)
			{
				tempInt++;
				filterObjectPointer = addPASFilterSourceDestination(filterPointer, command.part[tempInt], object_filter_source);
			}

			// Destination?
			else if (strcmp(command.part[tempInt], "dst-ip") == 0)
			{
				tempInt++;
				filterObjectPointer = addPASFilterSourceDestination(filterPointer, command.part[tempInt], object_filter_destination);
			}

			// Filter Id?
			else if (strcmp(command.part[tempInt], "id") == 0)
			{
				tempInt++;
				filterPointer->id = atoi(command.part[tempInt]);
			}

			tempInt++;
		}
	}
}


// Process a Filter...
void processFilterPAS(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct ciscoCommand command;
	struct filterListConfig *filterListPointer = 0;
	struct filterConfig *filterPointer = 0;
	struct filterObjectConfig *filterObjectPointer = 0;
	char tempString[nipper->maxSize];

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Filter Filter Line: %s\n", line);
	}

	// Split the command line up
	command = splitLine(line);

	// Find filter...
	filterListPointer = getFilterList(nipper, "**UNASSIGNED**", "", false);
	if (filterListPointer->filter != 0)
	{
		filterPointer = filterListPointer->filter;
		while ((filterPointer->next != 0) && (filterPointer->id != atoi(command.part[3])))
			filterPointer = filterPointer->next;
		if (filterPointer->id == atoi(command.part[3]))
		{
	
			// Name...
			if (strcmp(command.part[4], "name") == 0)
			{
				stripQuotes(command.part[5], tempString, nipper->maxSize);
				strncpy(filterPointer->remark, tempString, sizeof(filterPointer->remark) - 1);
			}
	
			// Action...
			else if (strcmp(command.part[4], "action") == 0)
			{
	
				// Mode...
				if (strcmp(command.part[5], "mode") == 0)
				{
					if (strcmp(command.part[6], "forward") == 0)
						filterPointer->action = filter_action_accept;
					else if (strcmp(command.part[6], "drop") == 0)
						filterPointer->action = filter_action_drop;
					else if (strcmp(command.part[6], "forward-to-next-hop") == 0)
						filterPointer->action = filter_action_accept;
				}
	
				// Stop on match...
				else if (strcmp(command.part[5], "stop-on-match") == 0)
				{
					if (strcmp(command.part[6], "true") == 0)
						filterPointer->stop = true;
					else
						filterPointer->stop = false;
				}
			}
	
			// Match...
			else if (strcmp(command.part[4], "match") == 0)
			{
	
				// Protocol...
				if (strcmp(command.part[5], "protocol") == 0)
					strncpy(filterPointer->protocol, command.part[6], sizeof(filterPointer->protocol) - 1);
	
				// Source Port...
				else if (strcmp(command.part[5], "src-port") == 0)
				{
					filterObjectPointer = addPASFilterSourceDestination(filterPointer, command.part[6], object_filter_sourceService);
					if (command.parts == 9)
					{
	
						// Options...
						if (strcasecmp(command.part[7], "src-option") == 0)
						{
							if (strcasecmp(command.part[8], "ignore") == 0)
								filterObjectPointer->serviceOp = service_oper_ignore;
							else if (strcasecmp(command.part[8], "equal") == 0)
								filterObjectPointer->serviceOp = service_oper_eq;
							else if (strcasecmp(command.part[8], "less") == 0)
								filterObjectPointer->serviceOp = service_oper_lt;
							else if (strcasecmp(command.part[8], "greater") == 0)
								filterObjectPointer->serviceOp = service_oper_gt;
							else if (strcasecmp(command.part[8], "notequal") == 0)
								filterObjectPointer->serviceOp = service_oper_neq;
						}
					}
				}
	
				// Destination Port...
				else if (strcmp(command.part[5], "dst-port") == 0)
				{
					filterObjectPointer = addPASFilterSourceDestination(filterPointer, command.part[6], object_filter_service);
					if (command.parts == 9)
					{
	
						// Destination Option...
						if (strcasecmp(command.part[7], "dst-option") == 0)
						{
							if (strcasecmp(command.part[8], "ignore") == 0)
								filterObjectPointer->serviceOp = service_oper_ignore;
							else if (strcasecmp(command.part[8], "equal") == 0)
								filterObjectPointer->serviceOp = service_oper_eq;
							else if (strcasecmp(command.part[8], "less") == 0)
								filterObjectPointer->serviceOp = service_oper_lt;
							else if (strcasecmp(command.part[8], "greater") == 0)
								filterObjectPointer->serviceOp = service_oper_gt;
							else if (strcasecmp(command.part[8], "notequal") == 0)
								filterObjectPointer->serviceOp = service_oper_neq;
						}
					}
				}
			}
		}
	}
}


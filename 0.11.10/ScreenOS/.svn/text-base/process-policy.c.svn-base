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


// Process policy lines
void processSOSPolicy(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct filterListConfig *filterListPointer = 0;
	struct filterConfig *filterPointer = 0;
	struct filterConfig *filterPreviousPointer = 0;
	struct filterObjectConfig *filterObjectPointer = 0;
	char policyName[32];
	int policyGlobal = false;
	int policyId = 0;
	int policyTop = false;
	int policyBefore = -1;
	char fromZone[32];
	char toZone[32];
	char tempString[nipper->maxSize];
	int position = 2;
	struct ciscoCommand command;

	if (nipper->debugMode == true)
		printf("Policy Line: %s\n", line);

	// Init
	strcpy(policyName, "");
	strcpy(fromZone, "");
	strcpy(toZone, "");
	command = splitLine(line);

	// Check for Global
	if (strcasecmp(command.part[position], "global") == 0)
	{
		policyGlobal = true;
		position++;
	}

	// Check for ID
	if (strcasecmp(command.part[position], "id") == 0)
	{
		position++;
		policyId = atoi(command.part[position]);
		position++;
	}

	// Check top
	if (strcasecmp(command.part[position], "top") == 0)
	{
		position++;
		policyTop = true;
	}

	// Check Before
	if (strcasecmp(command.part[position], "before") == 0)
	{
		position++;
		policyBefore = atoi(command.part[position]);
		position++;
	}

	// Check for a Name
	if (strcasecmp(command.part[position], "name") == 0)
	{
		position++;
		strncpy(policyName, command.part[position], sizeof(policyName) - 1);
		position++;
	}

	if (position < command.parts)
	{
		// Check for From and to
		if (strcasecmp(command.part[position], "from") == 0)
		{
			position++;
			stripQuotes(command.part[position], tempString, nipper->maxSize);
			strncpy(fromZone, tempString, sizeof(fromZone) - 1);
			position += 2;
			stripQuotes(command.part[position], tempString, nipper->maxSize);
			strncpy(toZone, tempString, sizeof(toZone) - 1);
			position++;
		}

		// If FROM / TO
		if ((fromZone[0] != 0) || (policyGlobal == true))
		{

			// Get Pointer to policy list...
			if (fromZone[0] != 0)
				filterListPointer = getFilterList(nipper, fromZone, toZone, false);
			else if (policyGlobal == true)
				filterListPointer = getFilterList(nipper, "", "", true);

			// Name...
			if (policyName[0] != 0)
				strncpy(filterListPointer->name, policyName, sizeof(filterListPointer->name));

			// Create policy rule
			// If no other rules exist
			if (filterListPointer->filter == 0)
			{
				// Create...
				filterListPointer->filter = malloc(sizeof(struct filterConfig));
				// Pointers...
				filterPointer = filterListPointer->filter;
			}
			// Policy at top
			else if (policyTop == true)
			{
				// Create...
				filterPointer = malloc(sizeof(struct filterConfig));
				// Pointers...
				filterPointer->next = filterListPointer->filter;
				filterListPointer->filter = filterPointer;
			}
			// Policy Before
			else if (policyBefore != -1)
			{
				// If first rule matches
				if (filterListPointer->filter->id == policyBefore)
				{
					// Create...
					filterPointer = malloc(sizeof(struct filterConfig));
					// Pointers...
					filterPointer->next = filterListPointer->filter;
					filterListPointer->filter = filterPointer;
				}
				// Look for rule
				else
				{
					filterPreviousPointer = filterListPointer->filter;
					filterPointer = filterPreviousPointer->next;
					if (filterPointer == 0)
					{
						// Create...
						filterPreviousPointer->next = malloc(sizeof(struct filterConfig));
						// Pointers...
						filterPointer = filterPreviousPointer->next;
					}
					else
					{
						// Search
						while ((filterPointer->next != 0) && (filterPointer->id != policyBefore))
						{
							filterPreviousPointer = filterPointer;
							filterPointer = filterPointer->next;
						}

						// If found
						if (filterPointer->id == policyBefore)
						{
							// Create...
							filterPreviousPointer->next = malloc(sizeof(struct filterConfig));
							// Pointers...
							filterPreviousPointer = filterPreviousPointer->next;
							filterPreviousPointer->next = filterPointer;
							filterPointer = filterPreviousPointer;
						}
						else
						{
							// Create...
							filterPointer->next = malloc(sizeof(struct filterConfig));
							// Pointers...
							filterPointer = filterPointer->next;
						}
					}
				}
			}
			// At the end
			else
			{
				// Search...
				filterPointer = filterListPointer->filter;
				while (filterPointer->next != 0)
					filterPointer = filterPointer->next;
				// Create...
				filterPointer->next = malloc(sizeof(struct filterConfig));
				// Pointers...
				filterPointer = filterPointer->next;
			}

			// Init
			memset(filterPointer, 0 , sizeof(struct filterConfig));
			filterPointer->enabled = true;
			filterPointer->log = false;

			// ID
			filterPointer->id = policyId;

			// Source Address
			stripQuotes(command.part[position], tempString, nipper->maxSize);
			filterObjectPointer = getFilterMember(filterPointer, tempString, object_filter_source);
			if (strcasecmp(filterObjectPointer->name, "Any") == 0)
				filterObjectPointer->type = object_type_any;
			else if (strncasecmp(filterObjectPointer->name, "MIP(", 4) == 0)
				filterObjectPointer->type = object_type_host;
			else
				filterObjectPointer->type = object_type_object;
			position++;

			// Destination Address
			stripQuotes(command.part[position], tempString, nipper->maxSize);
			filterObjectPointer = getFilterMember(filterPointer, tempString, object_filter_destination);
			if (strcasecmp(filterObjectPointer->name, "Any") == 0)
				filterObjectPointer->type = object_type_any;
			else if (strncasecmp(filterObjectPointer->name, "MIP(", 4) == 0)
				filterObjectPointer->type = object_type_host;
			else
				filterObjectPointer->type = object_type_object;
			position++;

			// Service
			stripQuotes(command.part[position], tempString, nipper->maxSize);
			filterObjectPointer = getFilterMember(filterPointer, tempString, object_filter_service);
			if (strcasecmp(filterObjectPointer->name, "Any") == 0)
			{
				filterObjectPointer->type = object_type_any;
				filterObjectPointer->serviceOp = service_oper_any;
			}
			else
			{
				filterObjectPointer->type = object_type_service;
				filterObjectPointer->serviceOp = service_oper_eq;
			}
			position++;

			while (position < command.parts)
			{
				// Permit
				if (strcasecmp(command.part[position], "permit") == 0)
					filterPointer->action = filter_action_accept;

				// Deny
				else if (strcasecmp(command.part[position], "deny") == 0)
					filterPointer->action = filter_action_drop;

				// Reject
				else if (strcasecmp(command.part[position], "reject") == 0)
					filterPointer->action = filter_action_reject;

				// Log
				else if (strcasecmp(command.part[position], "log") == 0)
					filterPointer->log = true;

				position++;
			}
		}

		// Disable?
		else if (strcasecmp(command.part[position], "disable") == 0)
		{
			filterListPointer = nipper->filterList;
			while (filterListPointer != 0)
			{
				filterPointer = filterListPointer->filter;
				while (filterPointer != 0)
				{
					if (filterPointer->id == policyId)
						filterPointer->enabled = false;
					filterPointer = filterPointer->next;
				}
				filterListPointer = filterListPointer->next;
			}
		}
	}

	// If Additional policy settings
	else
	{

		// Loop through the policy additional setting lines
		readLine(nipper->input, line, nipper->maxSize);
		command = splitLine(line);
		while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], "exit") != 0))
		{
			// Debug
			if (nipper->debugMode == true)
				printf("Policy Line: %s\n", line);

			// Source
			if ((strcasecmp(command.part[0], "set") == 0) && (strcasecmp(command.part[1], "src-address") == 0))
			{
				// Find policy ID
				filterListPointer = nipper->filterList;
				while (filterListPointer != 0)
				{
					filterPointer = filterListPointer->filter;
					while ((filterPointer->next != 0) && (filterPointer->id != policyId))
						filterPointer = filterPointer->next;

					// Found, add new entry
					if (filterPointer->id == policyId)
					{
						stripQuotes(command.part[2], tempString, nipper->maxSize);
						filterObjectPointer = getFilterMember(filterPointer, tempString, object_filter_source);
						if (strcasecmp(filterObjectPointer->name, "Any") == 0)
							filterObjectPointer->type = object_type_any;
						else if (strncasecmp(filterObjectPointer->name, "MIP(", 4) == 0)
							filterObjectPointer->type = object_type_host;
						else
							filterObjectPointer->type = object_type_object;
					}
					filterListPointer = filterListPointer->next;
				}
			}

			// Destination
			if ((strcasecmp(command.part[0], "set") == 0) && (strcasecmp(command.part[1], "dst-address") == 0))
			{
				// Find policy ID
				filterListPointer = nipper->filterList;
				while (filterListPointer != 0)
				{
					filterPointer = filterListPointer->filter;
					while ((filterPointer->next != 0) && (filterPointer->id != policyId))
						filterPointer = filterPointer->next;

					// Found, add new entry
					if (filterPointer->id == policyId)
					{
						stripQuotes(command.part[2], tempString, nipper->maxSize);
						filterObjectPointer = getFilterMember(filterPointer, tempString, object_filter_destination);
						if (strcasecmp(filterObjectPointer->name, "Any") == 0)
							filterObjectPointer->type = object_type_any;
						else if (strncasecmp(filterObjectPointer->name, "MIP(", 4) == 0)
							filterObjectPointer->type = object_type_host;
						else
							filterObjectPointer->type = object_type_object;
					}
					filterListPointer = filterListPointer->next;
				}
			}

			// Service
			if ((strcasecmp(command.part[0], "set") == 0) && (strcasecmp(command.part[1], "service") == 0))
			{
				// Find policy ID
				filterListPointer = nipper->filterList;
				while (filterListPointer != 0)
				{
					filterPointer = filterListPointer->filter;
					while ((filterPointer->next != 0) && (filterPointer->id != policyId))
						filterPointer = filterPointer->next;

					// Found, add new entry
					if (filterPointer->id == policyId)
					{
						stripQuotes(command.part[2], tempString, nipper->maxSize);
						filterObjectPointer = getFilterMember(filterPointer, tempString, object_filter_service);
						if (strcasecmp(filterObjectPointer->name, "Any") == 0)
						{
							filterObjectPointer->type = object_type_any;
							filterObjectPointer->serviceOp = service_oper_any;
						}
						else
						{
							filterObjectPointer->type = object_type_service;
							filterObjectPointer->serviceOp = service_oper_eq;
						}
					}
					filterListPointer = filterListPointer->next;
				}
			}

			// Get next line
			readLine(nipper->input, line, nipper->maxSize);
			command = splitLine(line);
		}
	}
}


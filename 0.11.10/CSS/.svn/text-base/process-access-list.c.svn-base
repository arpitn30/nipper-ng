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
void processCSSACL(char *line, struct nipperConfig *nipper)
{
	// Variables...
	int tempInt = 0;
	int setting = 0;
	fpos_t filePosition;
	struct filterListConfig *filterListPointer = 0;
	struct filterConfig *filterPointer = 0;
	struct filterObjectConfig *filterMemberPointer = 0;
	struct ciscoCommand command;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Access-List Line: %s\n", line);
	}

	// Init
	command = splitLine(line);
	if (strcmp(command.part[0], "no") == 0)
	{
		setting = false;
		tempInt = 2;
	}
	else
	{
		setting = true;
		tempInt = 1;
	}

	// If enabled ...
	if (strcmp(command.part[tempInt], "enable") == 0)
		nipper->css->aclEnabled = true;

	// If Disabled
	else if(strcmp(command.part[tempInt], "disable") == 0)
		nipper->css->aclEnabled = false;

	// Else it is a new ACL
	else
	{
		// Create ACL struct
		filterListPointer = getFilterList(nipper, command.part[tempInt], "", false);

		// Get the rules...
		fgetpos(nipper->input, &filePosition);
		readLine(nipper->input, line, nipper->maxSize);
		while ((feof(nipper->input) == 0) && (command.parts != 0))
		{
			// Debug
			if (nipper->debugMode == true)
			{
				printf("Access-List Line: %s\n", line);
			}

			// Init
			command = splitLine(line);

			// Apply
			if (strcmp(command.part[0], "apply") == 0)
				strncpy(filterListPointer->applyTo, command.part[1], sizeof(filterListPointer->applyTo) -1);

			// Clause
			else if (strcmp(command.part[0], "clause") == 0)
			{
				tempInt = 1;

				// Create clause rule...
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

				// Init Structure
				memset(filterPointer, 0, sizeof(struct filterConfig));
				filterPointer->enabled = true;

				// Clause no.
				filterPointer->id = atoi(command.part[tempInt]);
				tempInt++;

				// Log?
				if (strcmp(command.part[tempInt], "log") == 0)
				{
					tempInt++;
					if (strcmp(command.part[tempInt], "enable") == 0)
						filterPointer->log = true;
					else
						filterPointer->log = false;
					tempInt++;
				}
				else
					filterPointer->log = false;

				// Bypass / permit / deny
				if (strcmp(command.part[tempInt], "bypass") == 0)
					filterPointer->action = filter_action_bypass;
				else if (strcmp(command.part[tempInt], "permit") == 0)
					filterPointer->action = filter_action_accept;
				else
					filterPointer->action = filter_action_drop;
				tempInt++;

				// Protocol
				strncpy(filterPointer->protocol, command.part[tempInt], sizeof(filterPointer->protocol) -1);
				tempInt++;

				// Source
				if (strcasecmp(command.part[tempInt], "nql") == 0)
				{
					tempInt++;
					filterMemberPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_source);
					filterMemberPointer->type = object_type_object;
					tempInt++;
				}
				else if (strcasecmp(command.part[tempInt], "any") == 0)
				{
					tempInt++;
					filterMemberPointer = getFilterMember(filterPointer, "Any", object_filter_source);
					filterMemberPointer->type = object_type_any;
				}
				else
				{
					filterMemberPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_source);
					filterMemberPointer->type = object_type_host;
					tempInt++;
					if ((strcmp(command.part[tempInt], "destination") != 0) && (strcmp(command.part[tempInt], "range") != 0) && (strcmp(command.part[tempInt], "neq") != 0) && (strcmp(command.part[tempInt], "gt") != 0) && (strcmp(command.part[tempInt], "lt") != 0) && (strcmp(command.part[tempInt], "eq") != 0))
					{
						strncpy(filterMemberPointer->netMask, command.part[tempInt], sizeof(filterMemberPointer->netMask) - 1);
						if (strcmp(filterMemberPointer->netMask, "255.255.255.255") != 0)
							filterMemberPointer->type = object_type_network;
						tempInt++;
					}
				}

				// Source port
				if (strcmp(command.part[tempInt], "destination") != 0)
				{
					// Equal...
					if (strcmp(command.part[tempInt], "eq") == 0)
					{
						tempInt++;
						filterMemberPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
						filterMemberPointer->serviceOp = service_oper_eq;
					}

					// Less than
					else if (strcmp(command.part[tempInt], "lt") == 0)
					{
						tempInt++;
						filterMemberPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
						filterMemberPointer->serviceOp = service_oper_lt;
					}

					// Greater than
					else if (strcmp(command.part[tempInt], "gt") == 0)
					{
						tempInt++;
						filterMemberPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
						filterMemberPointer->serviceOp = service_oper_gt;
					}

					// Not equal to...
					else if (strcmp(command.part[tempInt], "neq") == 0)
					{
						tempInt++;
						filterMemberPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
						filterMemberPointer->serviceOp = service_oper_neq;
					}

					// Range
					else if (strcmp(command.part[tempInt], "range") == 0)
					{
						tempInt++;
						filterMemberPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
						filterMemberPointer->serviceOp = service_oper_range;
						tempInt++;
						strncpy(filterMemberPointer->netMask, command.part[tempInt], sizeof(filterMemberPointer->netMask) -1);
					}
					tempInt++;
				}

				// destination
				tempInt++;
				if (strcasecmp(command.part[tempInt], "nql") == 0)
				{
					tempInt++;
					filterMemberPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_destination);
					filterMemberPointer->type = object_type_object;
					tempInt++;
				}
				else if (strcasecmp(command.part[tempInt], "any") == 0)
				{
					tempInt++;
					filterMemberPointer = getFilterMember(filterPointer, "Any", object_filter_destination);
					filterMemberPointer->type = object_type_any;
				}
				else
				{
					filterMemberPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_destination);
					filterMemberPointer->type = object_type_host;
					tempInt++;
					if ((tempInt < command.parts) && (strcmp(command.part[tempInt], "prefer") != 0) && (strcmp(command.part[tempInt], "sourcegroup") != 0) && (strcmp(command.part[tempInt], "range") != 0) && (strcmp(command.part[tempInt], "neq") != 0) && (strcmp(command.part[tempInt], "gt") != 0) && (strcmp(command.part[tempInt], "lt") != 0) && (strcmp(command.part[tempInt], "eq") != 0))
					{
						strncpy(filterMemberPointer->netMask, command.part[tempInt], sizeof(filterMemberPointer->netMask) -1);
						if (strcmp(filterMemberPointer->netMask, "255.255.255.255") != 0)
							filterMemberPointer->type = object_type_network;
						tempInt++;
					}
				}

				// Destination port
				if ((strcmp(command.part[tempInt], "range") == 0) || (strcmp(command.part[tempInt], "neq") == 0) || (strcmp(command.part[tempInt], "gt") == 0) || (strcmp(command.part[tempInt], "lt") == 0) || (strcmp(command.part[tempInt], "eq") == 0))
				{
					// Equal...
					if (strcmp(command.part[tempInt], "eq") == 0)
					{
						tempInt++;
						filterMemberPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
						filterMemberPointer->serviceOp = service_oper_eq;
					}

					// Less than
					else if (strcmp(command.part[tempInt], "lt") == 0)
					{
						tempInt++;
						filterMemberPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
						filterMemberPointer->serviceOp = service_oper_lt;
					}

					// Greater than
					else if (strcmp(command.part[tempInt], "gt") == 0)
					{
						tempInt++;
						filterMemberPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
						filterMemberPointer->serviceOp = service_oper_gt;
					}

					// Not equal to...
					else if (strcmp(command.part[tempInt], "neq") == 0)
					{
						tempInt++;
						filterMemberPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
						filterMemberPointer->serviceOp = service_oper_neq;
					}

					// Range
					else if (strcmp(command.part[tempInt], "range") == 0)
					{
						tempInt++;
						filterMemberPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
						filterMemberPointer->serviceOp = service_oper_range;
						tempInt++;
						strncpy(filterMemberPointer->netMask, command.part[tempInt], sizeof(filterMemberPointer->netMask) -1);
					}
				}
			}

			// Get next
			fgetpos(nipper->input, &filePosition);
			readLine(nipper->input, line, nipper->maxSize);
		}

		// Set to previous position...
		fsetpos(nipper->input, &filePosition);
	}
}

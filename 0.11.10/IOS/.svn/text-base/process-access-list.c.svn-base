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
void processAccessList(char *line, struct nipperConfig *nipper)
{
	// Variables...
	int tempInt = 0;
	int loop = 0;
	char tempString[nipper->maxSize];
	char tempString2[nipper->maxSize];
	struct filterConfig *filterPointer = 0;
	struct filterObjectConfig *filterObjectPointer = 0;
	struct filterListConfig *filterListPointer = 0;
	struct ciscoCommand command;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Access-List Line: %s\n", line);
	}

	// Init
	command = splitLine(line);
	tempString[0] = 0;
	if (command.parts < 4)
		return;

	// Get / create access list
	filterListPointer = getFilterList(nipper, command.part[1], "", false);

	// Set ACL type, if not already set...
	if (filterListPointer->type == access_none)
	{
		if (atoi(command.part[1]) < 100)
			filterListPointer->type = access_std;
		else
			filterListPointer->type = access_ext;
	}

	// Is the line a remark?
	if ((strcmp(command.part[2], "remark") == 0) && (command.parts > 3))
	{
		strcpy(tempString, command.part[3]);
		if (command.parts > 4)
		{
			for (loop = 4; loop < command.parts; loop++)
			{
				sprintf(tempString2, "%s %s",tempString, command.part[loop]);
				strcpy(tempString, tempString2);
			}
		}
		insertFilterRemark(filterListPointer, 0, false, tempString);
	}
	else
	{
		tempInt = 2;

		// Is the line a permit / deny line?
		if ((strcmp(command.part[tempInt], "permit") == 0) || (strcmp(command.part[tempInt], "deny") == 0))
		{
			// Is this the first permission
			if (filterListPointer->filter == 0)
			{
				// Create a new permission storage structure
				filterPointer = malloc(sizeof(struct filterConfig));
				// sort out pointer
				filterListPointer->filter = filterPointer;
			}
			else
			{
				filterPointer = filterListPointer->filter;
				while (filterPointer->next != 0)
					filterPointer = filterPointer->next;
				// Create a new permission storage structure
				filterPointer->next = malloc(sizeof(struct filterConfig));
				// Sort out pointer
				filterPointer = filterPointer->next;
			}

			// Init...
			memset(filterPointer, 0, sizeof(struct filterConfig));
			filterPointer->enabled = true;
			filterPointer->established = false;
			filterPointer->fragments = false;
			filterPointer->log = false;

			// Was it a permit line?
			if (strcmp(command.part[tempInt], "permit") == 0)
				filterPointer->action = filter_action_accept;
			else
				filterPointer->action = filter_action_drop;
			tempInt++;

			// Is it an extended access-list?
			if (filterListPointer->type == access_ext)
			{
				strncpy(filterPointer->protocol, command.part[tempInt], sizeof(filterPointer->protocol) -1);
				tempInt++;
			}

			// Get source
			if (strcmp(command.part[tempInt], "host") == 0)
			{
				tempInt++;
				filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_source);
				filterObjectPointer->type = object_type_host;
				tempInt++;
			}
			else if (strcasecmp(command.part[tempInt], "any") == 0)
			{
				filterObjectPointer = getFilterMember(filterPointer, "Any", object_filter_source);
				filterObjectPointer->type = object_type_any;
				tempInt++;
			}
			else
			{
				// Standard access-list?
				if (filterListPointer->type == access_std)
				{
					filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_source);
					filterObjectPointer->type = object_type_host;
					tempInt++;
					if ((tempInt < command.parts) && (strncmp(command.part[tempInt], "log", 3) != 0))
					{
						strncpy(filterObjectPointer->netMask, command.part[tempInt], sizeof(filterObjectPointer->netMask) - 1);
						if (strcmp(filterObjectPointer->netMask, "255.255.255.255") != 0)
							filterObjectPointer->type = object_type_network;
						tempInt++;
					}
				}
				else
				{
					filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_source);
					tempInt++;
					strncpy(filterObjectPointer->netMask, command.part[tempInt], sizeof(filterObjectPointer->netMask) - 1);
					if (strcmp(filterObjectPointer->netMask, "255.255.255.255") == 0)
						filterObjectPointer->type = object_type_host;
					else
						filterObjectPointer->type = object_type_network;
					tempInt++;
				}
			}

			// Standard access-list?
			if (filterListPointer->type == access_std)
			{
				if ((tempInt < command.parts) && (strcmp(command.part[tempInt], "log") == 0))
					filterPointer->log = true;
				return;
			}

			// Is operator used with source?
			if (strncmp(command.part[tempInt], "lt", 2) == 0)
			{
				tempInt++;
				filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
				filterObjectPointer->serviceOp = service_oper_lt;
				tempInt++;
			}
			else if (strncmp(command.part[tempInt], "gt", 2) == 0)
			{
				tempInt++;
				filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
				filterObjectPointer->serviceOp = service_oper_gt;
				tempInt++;
			}
			else if (strncmp(command.part[tempInt], "eq", 2) == 0)
			{
				tempInt++;
				filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
				filterObjectPointer->serviceOp = service_oper_eq;
				tempInt++;
			}
			else if (strncmp(command.part[tempInt], "neq", 3) == 0)
			{
				tempInt++;
				filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
				filterObjectPointer->serviceOp = service_oper_neq;
				tempInt++;
			}
			else if (strncmp(command.part[tempInt], "range", 5) == 0)
			{
				tempInt++;
				filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
				filterObjectPointer->serviceOp = service_oper_range;
				tempInt++;
				strncpy(filterObjectPointer->netMask, command.part[tempInt], sizeof(filterObjectPointer->netMask) - 1);
				tempInt++;
			}

			// Get destination
			if (strncmp(command.part[tempInt], "host", 4) == 0)
			{
				tempInt++;
				filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_destination);
				filterObjectPointer->type = object_type_host;
				tempInt++;
			}
			else if (strcasecmp(command.part[tempInt], "any") == 0)
			{
				filterObjectPointer = getFilterMember(filterPointer, "Any", object_filter_destination);
				filterObjectPointer->type = object_type_any;
				tempInt++;
			}
			else
			{
				tempInt++;
				filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_destination);
				tempInt++;
				strncpy(filterObjectPointer->netMask, command.part[tempInt], sizeof(filterObjectPointer->netMask) - 1);
				if (strcmp(filterObjectPointer->netMask, "255.255.255.255") == 0)
					filterObjectPointer->type = object_type_host;
				else
					filterObjectPointer->type = object_type_network;
				tempInt++;
			}

			// If no more, then exit
			if (tempInt == command.parts)
				return;

			// Is operator used with destination?
			if (strncmp(command.part[tempInt], "lt", 2) == 0)
			{
				tempInt++;
				filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
				filterObjectPointer->serviceOp = service_oper_lt;
				tempInt++;
			}
			else if (strncmp(command.part[tempInt], "gt", 2) == 0)
			{
				tempInt++;
				filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
				filterObjectPointer->serviceOp = service_oper_gt;
				tempInt++;
			}
			else if (strncmp(command.part[tempInt], "eq", 2) == 0)
			{
				tempInt++;
				filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
				filterObjectPointer->serviceOp = service_oper_eq;
				tempInt++;
			}
			else if (strncmp(command.part[tempInt], "neq", 3) == 0)
			{
				tempInt++;
				filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
				filterObjectPointer->serviceOp = service_oper_neq;
				tempInt++;
			}
			else if (strncmp(command.part[tempInt], "range", 5) == 0)
			{
				tempInt++;
				filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
				filterObjectPointer->serviceOp = service_oper_range;
				tempInt++;
				strncpy(filterObjectPointer->netMask, command.part[tempInt], sizeof(filterObjectPointer->netMask) - 1);
				tempInt++;
			}

			// If no more, then exit
			if (tempInt == command.parts)
				return;

			// established?
			if (strncmp(command.part[tempInt], "established", 11) == 0)
			{
				filterPointer->established = true;
				tempInt++;
			}

			// fragments?
			if (strncmp(command.part[tempInt], "fragments", 9) == 0)
			{
				filterPointer->fragments = true;
				tempInt++;
			}

			// If no more, then exit
			if (tempInt == command.parts)
				return;

			// Log?
			if ((strncmp(command.part[tempInt], "log", 3) == 0) || (strncmp(command.part[tempInt], "log-input", 9) == 0))
			{
				filterPointer->log = true;
				tempInt++;
			}
		}
	}
}


// Process IP Access List
void processIPAccessList(char *line, struct nipperConfig *nipper)
{
	// Variables...
	int tempInt = 0;
	int loop;
	char tempString[nipper->maxSize];
	char tempString2[nipper->maxSize];
	fpos_t filePosition;
	struct filterConfig *filterPointer = 0;
	struct filterObjectConfig *filterObjectPointer = 0;
	struct filterListConfig *filterListPointer = 0;
	struct ciscoCommand command;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("IP Access-List Line: %s\n", line);
	}

	// Init
	command = splitLine(line);

	// Get / Create ACL...
	filterListPointer = getFilterList(nipper, command.part[3], "", false);

	// Set type...
	if (filterListPointer->type == access_none)
	{
		if (strcmp(command.part[2], "standard") == 0)
			filterListPointer->type = access_std;
		else
			filterListPointer->type = access_ext;
	}

	// Loop through the interface lines
	fgetpos(nipper->input, &filePosition);
	readLine(nipper->input, line, nipper->maxSize);
	while ((feof(nipper->input) == 0) && (line[0] == ' '))
	{
		// Debug
		if (nipper->debugMode == true)
		{
			printf("IP Access-List Line: %s\n", line);
		}

		// Init
		command = splitLine(line);

		// Permit or deny
		if ((strcmp(command.part[0], "permit") == 0) || (strcmp(command.part[0], "deny") == 0))
		{
			// If first permission
			if (filterListPointer->filter == 0)
			{
				// Create a new permission storage structure
				filterPointer = malloc(sizeof(struct filterConfig));
				// sort out pointer
				filterListPointer->filter = filterPointer;
			}
			else
			{
				filterPointer = filterListPointer->filter;
				while (filterPointer->next != 0)
					filterPointer = filterPointer->next;
				// Create a new permission storage structure
				filterPointer->next = malloc(sizeof(struct filterConfig));
				// Sort out pointer
				filterPointer = filterPointer->next;
			}

			// Init...
			memset(filterPointer, 0, sizeof(struct filterConfig));
			filterPointer->enabled = true;
			filterPointer->established = false;
			filterPointer->fragments = false;
			filterPointer->log = false;

			// Permit or Deny
			if (strcmp(command.part[0], "permit") == 0)
				filterPointer->action = filter_action_accept;
			else
				filterPointer->action = filter_action_drop;

			// Protocol
			if (filterListPointer->type == access_ext)
			{
				strncpy(filterPointer->protocol, command.part[1], sizeof(filterPointer->protocol) -1);
				tempInt = 2;
			}
			else
				tempInt = 1;

			// Source
			if (strncmp(command.part[tempInt], "host", 4) == 0)
			{
				tempInt++;
				filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_source);
				filterObjectPointer->type = object_type_host;
				tempInt++;
			}
			else if (strncmp(command.part[tempInt], "any", 3) == 0)
			{
				filterObjectPointer = getFilterMember(filterPointer, "Any", object_filter_source);
				filterObjectPointer->type = object_type_any;
				tempInt++;
			}
			else
			{
				// Standard access-list?
				if (filterListPointer->type == access_std)
				{
					filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_source);
					tempInt++;
					if ((tempInt < command.parts) && (strncmp(command.part[tempInt], "log", 3) != 0))
					{
						strncpy(filterObjectPointer->netMask, command.part[tempInt], sizeof(filterObjectPointer->netMask) -1);
						if (strcmp(filterObjectPointer->netMask, "255.255.255.255") == 0)
							filterObjectPointer->type = object_type_host;
						else
							filterObjectPointer->type = object_type_network;
						tempInt++;
					}
				}
				else
				{
					filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_source);
					tempInt++;
					strncpy(filterObjectPointer->netMask, command.part[tempInt], sizeof(filterObjectPointer->netMask) -1);
					if (strcmp(filterObjectPointer->netMask, "255.255.255.255") == 0)
						filterObjectPointer->type = object_type_host;
					else
						filterObjectPointer->type = object_type_network;
					tempInt++;
				}
			}

			// Standard ACL only...
			if (filterListPointer->type == access_std)
			{
				// Log?
				if ((strncmp(command.part[tempInt], "log", 3) == 0))
				{
					filterPointer->log = true;
					tempInt++;
				}
			}

			// Extended ACL only...
			if (filterListPointer->type == access_ext)
			{
				// Is operator used with source?
				if (strncmp(command.part[tempInt], "lt", 2) == 0)
				{
					tempInt++;
					filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
					filterObjectPointer->serviceOp = service_oper_lt;
					tempInt++;
				}
				else if (strncmp(command.part[tempInt], "gt", 2) == 0)
				{
					tempInt++;
					filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
					filterObjectPointer->serviceOp = service_oper_gt;
					tempInt++;
				}
				else if (strncmp(command.part[tempInt], "eq", 2) == 0)
				{
					tempInt++;
					filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
					filterObjectPointer->serviceOp = service_oper_eq;
					tempInt++;
				}
				else if (strncmp(command.part[tempInt], "neq", 3) == 0)
				{
					tempInt++;
					filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
					filterObjectPointer->serviceOp = service_oper_neq;
					tempInt++;
				}
				else if (strncmp(command.part[tempInt], "range", 5) == 0)
				{
					tempInt++;
					filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_sourceService);
					filterObjectPointer->serviceOp = service_oper_range;
					tempInt++;
					strncpy(filterObjectPointer->netMask, command.part[tempInt], sizeof(filterObjectPointer->netMask) -1);
					tempInt++;
				}

				// Get destination
				if (strncmp(command.part[tempInt], "host", 4) == 0)
				{
					tempInt++;
					filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_destination);
					filterObjectPointer->type = object_type_host;
					tempInt++;
				}
				else if (strncmp(command.part[tempInt], "any", 3) == 0)
				{
					filterObjectPointer = getFilterMember(filterPointer, "Any", object_filter_destination);
					filterObjectPointer->type = object_type_any;
					tempInt++;
				}
				else
				{
					filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_destination);
					tempInt++;
					strncpy(filterObjectPointer->netMask, command.part[tempInt], sizeof(filterObjectPointer->netMask) -1);
					if (strcmp(filterObjectPointer->netMask, "255.255.255.255") == 0)
						filterObjectPointer->type = object_type_host;
					else
						filterObjectPointer->type = object_type_network;
					tempInt++;
				}

				// Get all the rest...
				while (tempInt < command.parts)
				{
					// Is operator used with destination?
					if (strncmp(command.part[tempInt], "lt", 2) == 0)
					{
						tempInt++;
						filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
						filterObjectPointer->serviceOp = service_oper_lt;
					}
					else if (strncmp(command.part[tempInt], "gt", 2) == 0)
					{
						tempInt++;
						filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
						filterObjectPointer->serviceOp = service_oper_gt;
					}
					else if (strncmp(command.part[tempInt], "eq", 2) == 0)
					{
						tempInt++;
						filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
						filterObjectPointer->serviceOp = service_oper_eq;
					}
					else if (strncmp(command.part[tempInt], "neq", 3) == 0)
					{
						tempInt++;
						filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
						filterObjectPointer->serviceOp = service_oper_neq;
					}
					else if (strncmp(command.part[tempInt], "range", 5) == 0)
					{
						tempInt++;
						filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
						filterObjectPointer->serviceOp = service_oper_range;
						tempInt++;
						strncpy(filterObjectPointer->netMask, command.part[tempInt], sizeof(filterObjectPointer->netMask) -1);
					}

					// established?
					else if (strncmp(command.part[tempInt], "established", 11) == 0)
						filterPointer->established = true;
		
					// fragments?
					else if (strncmp(command.part[tempInt], "fragments", 9) == 0)
						filterPointer->fragments = true;

					// Log?
					else if ((strncmp(command.part[tempInt], "log", 3) == 0) || (strncmp(command.part[tempInt], "log-input", 9) == 0))
						filterPointer->log = true;

					// Others...
					else if ((strcmp(command.part[tempInt], "precendence") == 0) || (strcmp(command.part[tempInt], "tos") == 0) || (strcmp(command.part[tempInt], "reflect") == 0) || (strcmp(command.part[tempInt], "time-range") == 0) || (strcmp(command.part[tempInt], "option") == 0))
						tempInt++;
					else if ((strcmp(command.part[tempInt], "match-any") == 0) || (strcmp(command.part[tempInt], "match-all") == 0))
						tempInt+=2;

					// Else ICMP options...
					else if (strcmp(filterPointer->protocol, "icmp") == 0)
					{
						filterObjectPointer = getFilterMember(filterPointer, command.part[tempInt], object_filter_service);
						filterObjectPointer->serviceOp = service_oper_eq;
					}

					tempInt++;
				}
			}
		}

		// Remark...
		else if (strcmp(command.part[0], "remark") == 0)
		{
			strcpy(tempString, command.part[1]);
			if (command.parts > 2)
			{
				for (loop = 2; loop < command.parts; loop++)
				{
					sprintf(tempString2, "%s %s",tempString, command.part[loop]);
					strcpy(tempString, tempString2);
				}
			}
			insertFilterRemark(filterListPointer, 0, false, tempString);
		}

		// Debug (lines not processed)
		else if (nipper->linesnotprocessed == true)
			printf("%s\n", line);

		// Get next line...
		fgetpos(nipper->input, &filePosition);
		readLine(nipper->input, line, nipper->maxSize);
	}

	// Set to previous position...
	fsetpos(nipper->input, &filePosition);
}

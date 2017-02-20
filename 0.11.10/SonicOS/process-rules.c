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


void processSonicOSRule(char *line, struct nipperConfig *nipper)
{
	// Variables...
	fpos_t filePosition;
	struct ciscoCommand command;
	struct filterListConfig *filterListPointer = 0;
	struct filterConfig *filterPointer = 0;
	struct filterConfig *filterSearchPointer = 0;
	struct filterObjectConfig *servicePointer = 0;
	struct filterObjectConfig *sourcePointer = 0;
	struct filterObjectConfig *destinationPointer = 0;
	int stopReading = false;
	int initialSetup = false;
	char sourceNet[32];

	// Loop through the rule lines
	fgetpos(nipper->input, &filePosition);
	while ((feof(nipper->input) == 0) && (stopReading == false))
	{
		// Debug output
		if (nipper->debugMode == true)
			printf("Rules Line: %s\n", line);

		// Init
		command = splitLine(line);

		// If filter does not yet exist...
		if (filterPointer == 0)
		{
			filterPointer = malloc(sizeof(struct filterConfig));
			memset(filterPointer, 0, sizeof(struct filterConfig));
			filterPointer->enabled = true;
			filterPointer->log = false;
		}

		// Rule Action...
		if (strncmp(command.part[0], "prefs_ruleAction_", 17) == 0)
		{
			if (initialSetup == false)
			{
				filterPointer->id = atoi(command.part[0] + 17);
				initialSetup = true;
			}

			if (filterPointer->id == atoi(command.part[0] + 17))
			{
				if (strcasecmp(command.part[1], "allow") == 0)
					filterPointer->action = filter_action_accept;
				else if (strcasecmp(command.part[1], "deny") == 0)
					filterPointer->action = filter_action_reject;
				else
					filterPointer->action = filter_action_drop;
			}
			else
				stopReading = true;
		}

		// Service ID
		else if (strncmp(command.part[0], "prefs_ruleSvcID_", 16) == 0)
		{
			if (initialSetup == false)
			{
				filterPointer->id = atoi(command.part[0] + 16);
				initialSetup = true;
			}

			if (filterPointer->id == atoi(command.part[0] + 16))
			{
				servicePointer = getFilterMember(filterPointer, command.part[1], object_filter_service);
				servicePointer->type = object_type_object;
				servicePointer->serviceOp = service_oper_eq;
			}
			else
				stopReading = true;
		}

		// Source Ethernet
		else if (strncmp(command.part[0], "prefs_ruleSrcEnet_", 18) == 0)
		{
			if (initialSetup == false)
			{
				filterPointer->id = atoi(command.part[0] + 18);
				initialSetup = true;
			}

			if (filterPointer->id == atoi(command.part[0] + 18))
				strncpy(sourceNet, command.part[1], sizeof(sourceNet) - 1);
			else
				stopReading = true;
		}

		// Destination Ethernet
		else if (strncmp(command.part[0], "prefs_ruleDstEnet_", 18) == 0)
		{
			if (initialSetup == false)
			{
				filterPointer->id = atoi(command.part[0] + 18);
				initialSetup = true;
			}

			if (filterPointer->id == atoi(command.part[0] + 18))
			{
				filterListPointer = getFilterList(nipper, sourceNet, command.part[1], false);
				filterListPointer->type = access_std;
				// If no filters yet...
				if (filterListPointer->filter == 0)
					filterListPointer->filter = filterPointer;
				else
				{
					filterSearchPointer = filterListPointer->filter;
					while (filterSearchPointer->next != 0)
						filterSearchPointer = filterSearchPointer->next;
					filterSearchPointer->next = filterPointer;
				}
			}
			else
				stopReading = true;
		}

		// Source Begin
		else if (strncmp(command.part[0], "prefs_ruleSrcBegin_", 19) == 0)
		{
			if (initialSetup == false)
			{
				filterPointer->id = atoi(command.part[0] + 19);
				initialSetup = true;
			}

			if (filterPointer->id == atoi(command.part[0] + 19))
				sourcePointer = getFilterMember(filterPointer, command.part[1], object_filter_source);
			else
				stopReading = true;
		}

		// Source End
		else if (strncmp(command.part[0], "prefs_ruleSrcEnd_", 17) == 0)
		{
			if (initialSetup == false)
			{
				filterPointer->id = atoi(command.part[0] + 17);
				initialSetup = true;
			}

			if (filterPointer->id == atoi(command.part[0] + 17))
			{
				strncpy(sourcePointer->netMask, command.part[1], sizeof(sourcePointer->netMask) - 1);
				if (strcmp(sourcePointer->name, "0.0.0.0") == 0)
					sourcePointer->type = object_type_any;
				else if (strcmp(sourcePointer->name, sourcePointer->netMask) != 0)
					sourcePointer->type = object_type_network;
				else
					sourcePointer->type = object_type_host;
			}
			else
				stopReading = true;
		}

		// Destination Begin
		else if (strncmp(command.part[0], "prefs_ruleDstBegin_", 19) == 0)
		{
			if (initialSetup == false)
			{
				filterPointer->id = atoi(command.part[0] + 19);
				initialSetup = true;
			}

			if (filterPointer->id == atoi(command.part[0] + 19))
				destinationPointer = getFilterMember(filterPointer, command.part[1], object_filter_destination);
			else
				stopReading = true;
		}

		// Destination End
		else if (strncmp(command.part[0], "prefs_ruleDstEnd_", 17) == 0)
		{
			if (initialSetup == false)
			{
				filterPointer->id = atoi(command.part[0] + 17);
				initialSetup = true;
			}

			if (filterPointer->id == atoi(command.part[0] + 17))
			{
				strncpy(destinationPointer->netMask, command.part[1], sizeof(destinationPointer->netMask) - 1);
				if (strcmp(destinationPointer->name, "0.0.0.0") == 0)
					destinationPointer->type = object_type_any;
				else if (strcmp(destinationPointer->name, destinationPointer->netMask) != 0)
					destinationPointer->type = object_type_network;
				else
					destinationPointer->type = object_type_host;
			}
			else
				stopReading = true;
		}

		// Rule Enabled
		else if (strncmp(command.part[0], "prefs_ruleEnabled_", 18) == 0)
		{
			if (initialSetup == false)
			{
				filterPointer->id = atoi(command.part[0] + 18);
				initialSetup = true;
			}

			if (filterPointer->id == atoi(command.part[0] + 18))
			{
				if (strcmp(command.part[1], "1") == 0)
					filterPointer->enabled = true;
				else
					filterPointer->enabled = false;
			}
			else
				stopReading = true;
		}

		// Fragmentation
		else if (strncmp(command.part[0], "prefs_ruleAllowFrags_", 21) == 0)
		{
			if (initialSetup == false)
			{
				filterPointer->id = atoi(command.part[0] + 21);
				initialSetup = true;
			}

			if (filterPointer->id == atoi(command.part[0] + 21))
			{
				if (strcmp(command.part[1], "off") == 0)
					filterPointer->fragments = false;
				else
					filterPointer->fragments = true;
			}
			else
				stopReading = true;
		}

		// Comments
		else if (strncmp(command.part[0], "ruleComment_", 12) == 0)
		{
			if (initialSetup == false)
			{
				filterPointer->id = atoi(command.part[0] + 12);
				initialSetup = true;
			}

			if (filterPointer->id == atoi(command.part[0] + 12))
				strncpy(filterPointer->remark, line + strlen(command.part[0]) + 1, sizeof(filterPointer->remark) -1);
			else
				stopReading = true;
		}

		else if ((strncmp(command.part[0], "serviceNameInRule_", 18) != 0) || (strncmp(command.part[0], "prefs_rule", 10) == 0))
			stopReading = true;

		if (stopReading == false)
		{
			// Get next line
			fgetpos(nipper->input, &filePosition);
			readLine(nipper->input, line, nipper->maxSize);
		}
	}

	// Set file position back
	fsetpos(nipper->input, &filePosition);

	// If the filter was not added to the list...
	if ((filterListPointer == 0) && (filterPointer != 0))
	{
		if (sourcePointer != 0)
			free(sourcePointer);
		if (destinationPointer != 0)
			free(destinationPointer);
		if (servicePointer != 0)
			free (servicePointer);
		free(filterPointer);
	}
}


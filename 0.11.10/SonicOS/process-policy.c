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


void processSonicOSPolicy(char *line, struct nipperConfig *nipper)
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

	// Set enhanced...
	nipper->sonicos->enhanced = true;

	// Loop through the policy lines
	fgetpos(nipper->input, &filePosition);
	while ((feof(nipper->input) == 0) && (stopReading == false))
	{
		// Debug output
		if (nipper->debugMode == true)
			printf("Policy Line: %s\n", line);

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

		// Action...
		if (strncmp(command.part[0], "policyAction_", 13) == 0)
		{
			if (initialSetup == false)
			{
				filterPointer->id = atoi(command.part[0] + 13);
				initialSetup = true;
			}

			if (filterPointer->id == atoi(command.part[0] + 13))
			{
				if (strcasecmp(command.part[1], "2") == 0)
					filterPointer->action = filter_action_accept;
				else if (strcasecmp(command.part[1], "1") == 0)
					filterPointer->action = filter_action_reject;
				else
					filterPointer->action = filter_action_drop;
			}
			else
				stopReading = true;
		}

		// Service
		else if ((strncmp(command.part[0], "policyDstSvc_", 13) == 0) && (command.part[1][0] != 0))
		{
			if (initialSetup == false)
			{
				filterPointer->id = atoi(command.part[0] + 13);
				initialSetup = true;
			}

			if (filterPointer->id == atoi(command.part[0] + 13))
			{
				servicePointer = getFilterMember(filterPointer, command.part[1], object_filter_service);
				servicePointer->type = object_type_object;
				servicePointer->serviceOp = service_oper_eq;
			}
			else
				stopReading = true;
		}

		// Source Zone
		else if (strncmp(command.part[0], "policySrcZone_", 14) == 0)
		{
			if (initialSetup == false)
			{
				filterPointer->id = atoi(command.part[0] + 14);
				initialSetup = true;
			}

			if ((filterPointer->id == atoi(command.part[0] + 14)) && (command.part[1][0] == 0))
				strcpy(sourceNet, "Any");
			else if (filterPointer->id == atoi(command.part[0] + 14))
				strncpy(sourceNet, command.part[1], sizeof(sourceNet) - 1);
			else
				stopReading = true;
		}

		// Destination Zone
		else if (strncmp(command.part[0], "policyDstZone_", 14) == 0)
		{
			if (initialSetup == false)
			{
				filterPointer->id = atoi(command.part[0] + 14);
				initialSetup = true;
			}

			if (filterPointer->id == atoi(command.part[0] + 14))
			{
				if (command.part[1][0] == 0)
				  filterListPointer = getFilterList(nipper, sourceNet, "Any", false);
				else
				  filterListPointer = getFilterList(nipper, sourceNet, command.part[1], false);
				filterListPointer->type = access_ext;
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

		// Source
		else if (strncmp(command.part[0], "policySrcNet_", 13) == 0)
		{
			if (initialSetup == false)
			{
				filterPointer->id = atoi(command.part[0] + 13);
				initialSetup = true;
			}

			if (filterPointer->id == atoi(command.part[0] + 13))
			{
				if (command.part[1][0] != 0)
				{
					sourcePointer = getFilterMember(filterPointer, line + strlen(command.part[0]) + 1, object_filter_source);
					sourcePointer->type = object_type_object;
				}
			}
			else
				stopReading = true;
		}

		// Destination
		else if (strncmp(command.part[0], "policyDstNet_", 13) == 0)
		{
			if (initialSetup == false)
			{
				filterPointer->id = atoi(command.part[0] + 13);
				initialSetup = true;
			}

			if (filterPointer->id == atoi(command.part[0] + 13))
			{
				if (command.part[1][0] != 0)
				{
					destinationPointer = getFilterMember(filterPointer, line + strlen(command.part[0]) + 1, object_filter_destination);
					destinationPointer->type = object_type_object;
				}
			}
			else
				stopReading = true;
		}

		// Policy Enabled
		else if (strncmp(command.part[0], "policyEnabled_", 14) == 0)
		{
			if (initialSetup == false)
			{
				filterPointer->id = atoi(command.part[0] + 14);
				initialSetup = true;
			}

			if (filterPointer->id == atoi(command.part[0] + 14))
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
		else if (strncmp(command.part[0], "policyFrag_", 11) == 0)
		{
			if (initialSetup == false)
			{
				filterPointer->id = atoi(command.part[0] + 11);
				initialSetup = true;
			}

			if (filterPointer->id == atoi(command.part[0] + 11))
			{
				if (strcmp(command.part[1], "0") == 0)
					filterPointer->fragments = false;
				else
					filterPointer->fragments = true;
			}
			else
				stopReading = true;
		}

		// Comments
		else if (strncmp(command.part[0], "policyComment_", 14) == 0)
		{
			if (initialSetup == false)
			{
				filterPointer->id = atoi(command.part[0] + 14);
				initialSetup = true;
			}

			if (filterPointer->id == atoi(command.part[0] + 14))
				strncpy(filterPointer->remark, line + strlen(command.part[0]) + 1, sizeof(filterPointer->remark) -1);
			else
				stopReading = true;
		}

		// Stop reading...
		else if (strncmp(command.part[0], "policy", 6) != 0)
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


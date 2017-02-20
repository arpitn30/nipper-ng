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

// This file contains the code that handles the input processing for FW1 Rules


void processFW1Rule(char *line, struct nipperConfig *nipper, struct filterListConfig *filterListPointer)
{
	// Variables...
	struct ciscoCommand command;
	struct filterConfig *filterPointer = 0;
	struct filterConfig *filterSearchPointer = 0;
	struct filterObjectConfig *filterObjectPointer = 0;
	char tempString[nipper->maxSize];

	// Debug output
	if (nipper->debugMode == true)
		printf("Rules Line: %s\n", line);

	// If first rule...
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
	filterPointer->enabled = true;
	filterPointer->log = false;
	filterPointer->deleteMe = false;
	filterPointer->anySource = false;
	filterPointer->networkSource = false;
	filterPointer->anySourceService = false;
	filterPointer->anyDestination = false;
	filterPointer->networkDestination = false;
	filterPointer->anyDestinationService = false;
	filterPointer->logging = false;
	filterPointer->logDeny = false;

	// Init...
	command = splitLine(line);

	// Process lines
	while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0))
	{
		// Read line
		memset(line, 0, LINE_SIZE + 1);
		readLine(nipper->input, line, LINE_SIZE);

		// Init...
		command = splitLine(line);

		// Debug output
		if (nipper->debugMode == true)
			printf("Rules Line: %s\n", line);

		// Action...
		if ((strcasecmp(command.part[0], ":action") == 0) && (strcasecmp(command.part[1], "()") != 0))
		{
			// Process lines
			while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0))
			{
				// Read line
				memset(line, 0, LINE_SIZE + 1);
				readLine(nipper->input, line, LINE_SIZE);
		
				// Init...
				command = splitLine(line);
		
				// Debug output
				if (nipper->debugMode == true)
					printf("Rules Action Line: %s\n", line);

				// Action structure
				if (strcasecmp(command.part[0], ":") == 0)
				{
					// Process lines
					while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0))
					{
						// Read line
						memset(line, 0, LINE_SIZE + 1);
						readLine(nipper->input, line, LINE_SIZE);
				
						// Init...
						command = splitLine(line);
				
						// Debug output
						if (nipper->debugMode == true)
							printf("Rules Action Line: %s\n", line);

						// Action Type
						if ((strcasecmp(command.part[0], ":action") == 0) || (strcasecmp(command.part[0], ":type") == 0))
						{
							if (strcasecmp(command.part[1], "(accept)") == 0)
								filterPointer->action = filter_action_accept;
							else if (strcasecmp(command.part[1], "(drop)") == 0)
								filterPointer->action = filter_action_drop;
						}

						// Process Unknown...
						else
							processFW1Unknown(nipper, line);
					}
					command.part[0][0] = 0;
				}

				// Process Unknown...
				else
					processFW1Unknown(nipper, line);
			}
			command.part[0][0] = 0;
		}

		// Admin info (UID)...
		else if ((strcasecmp(command.part[0], ":AdminInfo") == 0) && (strcasecmp(command.part[1], "(") == 0))
		{
			// Process lines
			while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0))
			{
				// Read line
				memset(line, 0, LINE_SIZE + 1);
				readLine(nipper->input, line, LINE_SIZE);
		
				// Init...
				command = splitLine(line);
		
				// Debug output
				if (nipper->debugMode == true)
					printf("Rules Admin Line: %s\n", line);

				if ((strcasecmp(command.part[0], ":chkpf_uid") == 0) && (strcasecmp(command.part[1], "()") != 0))
					strncpy(filterPointer->uid, command.part[1], sizeof(filterPointer->uid) -1);

				// Process Unknown...
				else
					processFW1Unknown(nipper, line);
			}
			command.part[0][0] = 0;
		}

		// Header Text...
		else if ((strcasecmp(command.part[0], ":header_text") == 0) && (strcasecmp(command.part[1], "()") != 0))
		{
			command.part[1][strlen(command.part[1]) - 1] = 0;
			stripQuotes(command.part[1] + 1, tempString, sizeof(tempString) -1);
			insertFilterRemark(filterListPointer, filterPointer, true, tempString);
			filterPointer->deleteMe = true;
		}

		// Comments...
		else if ((strcasecmp(command.part[0], ":comments") == 0) && (strcasecmp(command.part[1], "()") != 0))
		{
			command.part[1][strlen(command.part[1]) - 1] = 0;
			stripQuotes(command.part[1] + 1, filterPointer->remark, sizeof(filterPointer->remark) -1);
		}

		// Disabled...
		else if ((strcasecmp(command.part[0], ":disabled") == 0) && (strcasecmp(command.part[1], "(false)") == 0))
			filterPointer->enabled = true;
		else if ((strcasecmp(command.part[0], ":disabled") == 0) && (strcasecmp(command.part[1], "(true)") == 0))
			filterPointer->enabled = false;

		// Track (Log)...
		else if ((strcasecmp(command.part[0], ":track") == 0) && (strcasecmp(command.part[1], "()") != 0))
		{
			// Process lines
			while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0))
			{
				// Read line
				memset(line, 0, LINE_SIZE + 1);
				readLine(nipper->input, line, LINE_SIZE);
		
				// Init...
				command = splitLine(line);
		
				// Debug output
				if (nipper->debugMode == true)
					printf("Rules Track Line: %s\n", line);

				// Log structure
				if ((strcasecmp(command.part[0], ":") == 0) && (strcasecmp(command.part[1], "log") == 0))
					filterPointer->log = true;

				// If reference object
				else if ((strcasecmp(command.part[0], ":") == 0) && (strcasecmp(command.part[1], "(ReferenceObject") == 0))
				{
					while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0))
					{
						// Read line
						memset(line, 0, LINE_SIZE + 1);
						readLine(nipper->input, line, LINE_SIZE);
				
						// Init...
						command = splitLine(line);
				
						// Debug output
						if (nipper->debugMode == true)
							printf("Rules Track Line: %s\n", line);

						if ((strcasecmp(command.part[0], ":Name") == 0) && (strcasecmp(command.part[1], "(Log)") == 0))
							filterPointer->log = true;
						else if ((strcasecmp(command.part[0], ":Name") == 0) && (strcasecmp(command.part[1], "(None)") == 0))
							filterPointer->log = false;

						// Process Unknown...
						else
							processFW1Unknown(nipper, line);
					}
					command.part[0][0] = 0;
				}

				// Process Unknown...
				else
					processFW1Unknown(nipper, line);
			}
			command.part[0][0] = 0;
		}

		// Destination...
		else if (strcasecmp(command.part[0], ":dst") == 0)
		{
			// Process lines
			while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0))
			{
				// Read line
				memset(line, 0, LINE_SIZE + 1);
				readLine(nipper->input, line, LINE_SIZE);
		
				// Init...
				command = splitLine(line);
		
				// Debug output
				if (nipper->debugMode == true)
					printf("Rules Destination Line: %s\n", line);

				// Member line
				if ((strcasecmp(command.part[0], ":") == 0) && (command.part[1][0] != '('))
				{
					filterObjectPointer = getFilterMember(filterPointer, command.part[1], object_filter_destination);
					filterObjectPointer->type = object_type_object;
				}
				else if ((strcasecmp(command.part[0], ":") == 0) && (strcasecmp(command.part[1], "(ReferenceObject") == 0))
				{
					// Process lines
					while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0))
					{
						// Read line
						memset(line, 0, LINE_SIZE + 1);
						readLine(nipper->input, line, LINE_SIZE);
				
						// Init...
						command = splitLine(line);
				
						// Debug output
						if (nipper->debugMode == true)
							printf("Rules Install Line: %s\n", line);

						// Name
						if (strcasecmp(command.part[0], ":Name") == 0)
						{
							command.part[1][strlen(command.part[1]) -1] = 0;
							filterObjectPointer = getFilterMember(filterPointer, command.part[1] + 1, object_filter_destination);
							filterObjectPointer->type = object_type_object;
						}

						// Process Unknown...
						else
							processFW1Unknown(nipper, line);
					}
					command.part[0][0] = 0;
				}

				// Process Unknown...
				else
					processFW1Unknown(nipper, line);
			}
			command.part[0][0] = 0;
		}

		// Source...
		else if (strcasecmp(command.part[0], ":src") == 0)
		{
			// Process lines
			while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0))
			{
				// Read line
				memset(line, 0, LINE_SIZE + 1);
				readLine(nipper->input, line, LINE_SIZE);
		
				// Init...
				command = splitLine(line);
		
				// Debug output
				if (nipper->debugMode == true)
					printf("Rules Source Line: %s\n", line);

				// Member line
				if ((strcasecmp(command.part[0], ":") == 0) && (command.part[1][0] != '('))
				{
					filterObjectPointer = getFilterMember(filterPointer, command.part[1], object_filter_source);
					filterObjectPointer->type = object_type_object;
				}
				else if ((strcasecmp(command.part[0], ":") == 0) && (strcasecmp(command.part[1], "(ReferenceObject") == 0))
				{
					// Process lines
					while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0))
					{
						// Read line
						memset(line, 0, LINE_SIZE + 1);
						readLine(nipper->input, line, LINE_SIZE);
				
						// Init...
						command = splitLine(line);
				
						// Debug output
						if (nipper->debugMode == true)
							printf("Rules Install Line: %s\n", line);

						// Name
						if (strcasecmp(command.part[0], ":Name") == 0)
						{
							command.part[1][strlen(command.part[1]) -1] = 0;
							filterObjectPointer = getFilterMember(filterPointer, command.part[1] + 1, object_filter_source);
							filterObjectPointer->type = object_type_object;
						}

						// Process Unknown...
						else
							processFW1Unknown(nipper, line);
					}
					command.part[0][0] = 0;
				}

				// Process Unknown...
				else
					processFW1Unknown(nipper, line);
			}
			command.part[0][0] = 0;
		}

		// Install...
		else if (strcasecmp(command.part[0], ":install") == 0)
		{
			// Process lines
			while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0))
			{
				// Read line
				memset(line, 0, LINE_SIZE + 1);
				readLine(nipper->input, line, LINE_SIZE);
		
				// Init...
				command = splitLine(line);
		
				// Debug output
				if (nipper->debugMode == true)
					printf("Rules Install Line: %s\n", line);

				// Member line
				if ((strcasecmp(command.part[0], ":") == 0) && (command.part[1][0] != '('))
				{
					filterObjectPointer = getFilterMember(filterPointer, command.part[1], object_filter_install);
					filterObjectPointer->type = object_type_object;
				}
				else if ((strcasecmp(command.part[0], ":") == 0) && (strcasecmp(command.part[1], "(ReferenceObject") == 0))
				{
					// Process lines
					while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0))
					{
						// Read line
						memset(line, 0, LINE_SIZE + 1);
						readLine(nipper->input, line, LINE_SIZE);
				
						// Init...
						command = splitLine(line);
				
						// Debug output
						if (nipper->debugMode == true)
							printf("Rules Install Line: %s\n", line);

						// Name
						if (strcasecmp(command.part[0], ":Name") == 0)
						{
							command.part[1][strlen(command.part[1]) -1] = 0;
							filterObjectPointer = getFilterMember(filterPointer, command.part[1] + 1, object_filter_install);
							filterObjectPointer->type = object_type_object;
						}

						// Process Unknown...
						else
							processFW1Unknown(nipper, line);
					}
					command.part[0][0] = 0;
				}

				// Process Unknown...
				else
					processFW1Unknown(nipper, line);
			}
			command.part[0][0] = 0;
		}

		// Through...
		else if (strcasecmp(command.part[0], ":through") == 0)
		{
			// Process lines
			while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0))
			{
				// Read line
				memset(line, 0, LINE_SIZE + 1);
				readLine(nipper->input, line, LINE_SIZE);
		
				// Init...
				command = splitLine(line);
		
				// Debug output
				if (nipper->debugMode == true)
					printf("Rules Install Line: %s\n", line);

				// Member line
				if ((strcasecmp(command.part[0], ":") == 0) && (command.part[1][0] != '('))
				{
					filterObjectPointer = getFilterMember(filterPointer, command.part[1], object_filter_through);
					filterObjectPointer->type = object_type_object;
				}
				else if ((strcasecmp(command.part[0], ":") == 0) && (strcasecmp(command.part[1], "(ReferenceObject") == 0))
				{
					// Process lines
					while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0))
					{
						// Read line
						memset(line, 0, LINE_SIZE + 1);
						readLine(nipper->input, line, LINE_SIZE);
				
						// Init...
						command = splitLine(line);
				
						// Debug output
						if (nipper->debugMode == true)
							printf("Rules Install Line: %s\n", line);

						// Name
						if (strcasecmp(command.part[0], ":Name") == 0)
						{
							command.part[1][strlen(command.part[1]) -1] = 0;
							filterObjectPointer = getFilterMember(filterPointer, command.part[1] + 1, object_filter_through);
							filterObjectPointer->type = object_type_object;
						}

						// Process Unknown...
						else
							processFW1Unknown(nipper, line);
					}
					command.part[0][0] = 0;
				}

				// Process Unknown...
				else
					processFW1Unknown(nipper, line);
			}
			command.part[0][0] = 0;
		}

		// Services (destination)...
		else if (strcasecmp(command.part[0], ":services") == 0)
		{
			// Process lines
			while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0))
			{
				// Read line
				memset(line, 0, LINE_SIZE + 1);
				readLine(nipper->input, line, LINE_SIZE);
		
				// Init...
				command = splitLine(line);
		
				// Debug output
				if (nipper->debugMode == true)
					printf("Rules Service Line: %s\n", line);

				// Member line
				if ((strcasecmp(command.part[0], ":") == 0) && (command.part[1][0] != '('))
				{
					filterObjectPointer = getFilterMember(filterPointer, command.part[1], object_filter_service);
					filterObjectPointer->type = object_type_object;
				}
				else if ((strcasecmp(command.part[0], ":") == 0) && (strcasecmp(command.part[1], "(ReferenceObject") == 0))
				{
					// Process lines
					while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0))
					{
						// Read line
						memset(line, 0, LINE_SIZE + 1);
						readLine(nipper->input, line, LINE_SIZE);
				
						// Init...
						command = splitLine(line);
				
						// Debug output
						if (nipper->debugMode == true)
							printf("Rules Install Line: %s\n", line);

						// Name
						if (strcasecmp(command.part[0], ":Name") == 0)
						{
							command.part[1][strlen(command.part[1]) -1] = 0;
							filterObjectPointer = getFilterMember(filterPointer, command.part[1] + 1, object_filter_service);
							filterObjectPointer->type = object_type_object;
						}

						// Process Unknown...
						else
							processFW1Unknown(nipper, line);
					}
					command.part[0][0] = 0;
				}

				// Process Unknown...
				else
					processFW1Unknown(nipper, line);
			}
			command.part[0][0] = 0;
		}

		// Process Unknown...
		else
			processFW1Unknown(nipper, line);
	}

	// If the filter should be deleted...
	if (filterPointer->deleteMe == true)
	{
		// Sort out pointers...
		if (filterPointer == filterListPointer->filter)
			filterListPointer->filter = filterPointer->next;
		else
		{
			filterSearchPointer = filterListPointer->filter;
			while (filterSearchPointer->next != filterPointer)
				filterSearchPointer = filterSearchPointer->next;
			filterSearchPointer->next = filterPointer->next;
		}

		// Delete struct...
		while (filterPointer->source != 0)
		{
			filterObjectPointer = filterPointer->source->next;
			free (filterPointer->source);
			filterPointer->source = filterObjectPointer;
		}
		while (filterPointer->sourceService != 0)
		{
			filterObjectPointer = filterPointer->sourceService->next;
			free (filterPointer->sourceService);
			filterPointer->sourceService = filterObjectPointer;
		}
		while (filterPointer->destination != 0)
		{
			filterObjectPointer = filterPointer->destination->next;
			free (filterPointer->destination);
			filterPointer->destination = filterObjectPointer;
		}
		while (filterPointer->destinationService != 0)
		{
			filterObjectPointer = filterPointer->destinationService->next;
			free (filterPointer->destinationService);
			filterPointer->destinationService = filterObjectPointer;
		}
		while (filterPointer->through != 0)
		{
			filterObjectPointer = filterPointer->through->next;
			free (filterPointer->through);
			filterPointer->through = filterObjectPointer;
		}
		while (filterPointer->install != 0)
		{
			filterObjectPointer = filterPointer->install->next;
			free (filterPointer->install);
			filterPointer->install = filterObjectPointer;
		}
		free (filterPointer);
	}
}


struct filterListConfig *processFW1RuleCollection(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct ciscoCommand command;
	struct filterListConfig *filterListPointer = 0;
	char tempString[nipper->maxSize];
	int init = false;

	// Debug output
	if (nipper->debugMode == true)
		printf("Rule Collection Line: %s\n", line);

	// Init...
	command = splitLine(line);

	// Process lines
	while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0))
	{
		// Read line
		memset(line, 0, LINE_SIZE + 1);
		readLine(nipper->input, line, LINE_SIZE);

		// Init...
		command = splitLine(line);

		// Debug output
		if (nipper->debugMode == true)
			printf("Policy Collection Line: %s\n", line);

		// Policy Collection Name...
		if (strcasecmp(command.part[0], ":Name") == 0)
		{
			command.part[1][strlen(command.part[1]) -1] = 0;
			memset(tempString, 0, nipper->maxSize);
			strncpy(tempString, command.part[1] + 1, nipper->maxSize - 1);

			// If first filter list...
			if (nipper->filterList == 0)
			{
				nipper->filterList = malloc(sizeof(struct filterListConfig));
				filterListPointer = nipper->filterList;
				init = true;
			}
			else
			{
				filterListPointer = nipper->filterList;
				while ((filterListPointer->next != 0) && (strcasecmp(filterListPointer->name, tempString) != 0))
					filterListPointer = filterListPointer->next;
				if (strcasecmp(filterListPointer->name, tempString) != 0)
				{
					filterListPointer->next = malloc(sizeof(struct filterListConfig));
					filterListPointer = filterListPointer->next;
					init = true;
				}
			}

			// Needs initialisation...
			if (init == true)
			{
				memset(filterListPointer, 0, sizeof(struct filterListConfig));
				strncpy(filterListPointer->name, tempString, sizeof(filterListPointer->name) - 1);
				filterListPointer->denyAllAndLog = false;
			}
		}

		// Process Unknown...
		else
			processFW1Unknown(nipper, line);
	}

	return filterListPointer;
}


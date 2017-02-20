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

// This file contains the code that handles the input processing for FW1 Policy Collections

struct policyCollection
{
	char name[32];
	int def;
	int allInternal;
	struct host *targets;
	struct policyCollection *next;
};


struct policyCollection *getFW1PolicyCollection(struct nipperConfig *nipper, char *name)
{
	// Variables...
	struct policyCollection *policyCollectionPointer = 0;
	int init = false;

	// If first...
	if (nipper->fw1->policies == 0)
	{
		nipper->fw1->policies = malloc(sizeof(struct policyCollection));
		policyCollectionPointer = nipper->fw1->policies;
		init = true;
	}
	else
	{
		policyCollectionPointer = nipper->fw1->policies;
		while ((policyCollectionPointer->next != 0) && (strcmp(policyCollectionPointer->name, name) != 0))
			policyCollectionPointer = policyCollectionPointer->next;
		if (strcmp(policyCollectionPointer->name, name) != 0)
		{
			policyCollectionPointer->next = malloc(sizeof(struct policyCollection));
			policyCollectionPointer = policyCollectionPointer->next;
			init = true;
		}
	}

	// Init?
	if (init == true)
	{
		memset(policyCollectionPointer, 0, sizeof(struct policyCollection));
		strncpy(policyCollectionPointer->name, name, sizeof(policyCollectionPointer->name) - 1);
	}

	return policyCollectionPointer;
}


void addFW1InstallableTarget(struct policyCollection *policyCollectionPointer, char *target)
{
	// Variables...
	struct host *targetPointer;
	int init = false;

	// If first...
	if (policyCollectionPointer->targets == 0)
	{
		policyCollectionPointer->targets = malloc(sizeof(struct host));
		targetPointer = policyCollectionPointer->targets;
		init = true;
	}
	else
	{
		targetPointer = policyCollectionPointer->targets;
		while ((targetPointer->next != 0) && (strcmp(targetPointer->server, target) != 0))
			targetPointer = targetPointer->next;
		if (strcmp(targetPointer->server, target) != 0)
		{
			targetPointer->next = malloc(sizeof(struct host));
			targetPointer = targetPointer->next;
			init = true;
		}
	}

	// Init?
	if (init == true)
	{
		memset(targetPointer, 0, sizeof(struct host));
		strncpy(targetPointer->server, target, sizeof(targetPointer->server) - 1);
	}
}


void processFW1PolicyCollections(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct ciscoCommand command;
	struct policyCollection *policyCollectionPointer = 0;

	// Debug output
	if (nipper->debugMode == true)
		printf("Policy Collection Line: %s\n", line);

	// Init...
	command = splitLine(line);

	// Process lines
	while ((feof(nipper->input) == 0) && (strcmp(command.part[0], ")") != 0))
	{
		// Read line
		memset(line, 0, LINE_SIZE + 1);
		readLine(nipper->input, line, LINE_SIZE);

		// Init...
		command = splitLine(line);

		// Debug output
		if (nipper->debugMode == true)
			printf("Policy Collection Line: %s\n", line);

		// Policy Collection
		if ((strcmp(command.part[0], ":") == 0) && (strcmp(command.part[1], "()") != 0))
		{
			policyCollectionPointer = getFW1PolicyCollection(nipper, command.part[1] + 1);

			// Process lines
			while ((feof(nipper->input) == 0) && (strcmp(command.part[0], ")") != 0))
			{
				// Read line
				memset(line, 0, LINE_SIZE + 1);
				readLine(nipper->input, line, LINE_SIZE);
		
				// Init...
				command = splitLine(line);
		
				// Debug output
				if (nipper->debugMode == true)
					printf("Policy Collection Line: %s\n", line);

				// Default...
				if (strcmp(command.part[0], ":default") == 0)
				{
					command.part[1][strlen(command.part[1]) -1] = 0;
					policyCollectionPointer->def = atoi(command.part[1] + 1);
				}
	
				// All Internal Modules...
				else if ((strcmp(command.part[0], ":all_internal_modules") == 0) && (strcmp(command.part[1], "(true)") == 0))
					policyCollectionPointer->allInternal = true;
				else if ((strcmp(command.part[0], ":all_internal_modules") == 0) && (strcmp(command.part[1], "(false)") == 0))
					policyCollectionPointer->allInternal = false;

				// Installable Targets...
				else if ((strcmp(command.part[0], ":installable_targets") == 0) && (strcmp(command.part[1], "()") != 0))
				{
					// Process lines
					while ((feof(nipper->input) == 0) && (strcmp(command.part[0], ")") != 0))
					{
						// Read line
						memset(line, 0, LINE_SIZE + 1);
						readLine(nipper->input, line, LINE_SIZE);
				
						// Init...
						command = splitLine(line);
				
						// Debug output
						if (nipper->debugMode == true)
							printf("Installable Targets Line: %s\n", line);
	
						// If reference object...
						if ((strcmp(command.part[0], ":") == 0) && (strcmp(command.part[1], "(ReferenceObject") == 0))
						{
							// Process lines
							while ((feof(nipper->input) == 0) && (strcmp(command.part[0], ")") != 0))
							{
								// Read line
								memset(line, 0, LINE_SIZE + 1);
								readLine(nipper->input, line, LINE_SIZE);
						
								// Init...
								command = splitLine(line);
						
								// Debug output
								if (nipper->debugMode == true)
									printf("Reference Object Line: %s\n", line);
	
								// Name...
								if ((strcmp(command.part[0], ":Name") == 0) && (strcmp(command.part[1], "()") != 0))
								{
									command.part[1][strlen(command.part[1]) -1] = 0;
									addFW1InstallableTarget(policyCollectionPointer, command.part[1] + 1);
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
			policyCollectionPointer = 0;
			command.part[0][0] = 0;
		}

		// Process Unknown...
		else
			processFW1Unknown(nipper, line);
	}
}

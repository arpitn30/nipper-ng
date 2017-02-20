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

// This file contains the code that handles the input processing for FW1 Objects


// Get pointer to interface (or create a new one)...
struct hostInterfaces *getFW1HostInterface(struct nipperConfig *nipper, struct objectConfig *objectPointer, int interface)
{
	// Variables...
	struct hostInterfaces *fw1InterfacePointer = 0;
	int init = false;

	// Is it the first one?
	if (objectPointer->interfaces == 0)
	{
		objectPointer->interfaces = malloc(sizeof(struct hostInterfaces));
		fw1InterfacePointer = objectPointer->interfaces;
		init = true;
	}
	else
	{
		fw1InterfacePointer = objectPointer->interfaces;
		while ((fw1InterfacePointer->next != 0) && (fw1InterfacePointer->interface != interface))
			fw1InterfacePointer = fw1InterfacePointer->next;
		if (fw1InterfacePointer->interface != interface)
		{
			fw1InterfacePointer->next = malloc(sizeof(struct hostInterfaces));
			fw1InterfacePointer = fw1InterfacePointer->next;
			init = true;
		}
	}

	// Does the structure need initing?
	if (init == true)
	{
		memset(fw1InterfacePointer, 0, sizeof(struct hostInterfaces));
		fw1InterfacePointer->interface = interface;
		fw1InterfacePointer->dynamicIP = false;
	}

	return fw1InterfacePointer;
}


// Process an object interface...
void processFW1ObjectsInterfaces(char *line, struct nipperConfig *nipper, struct objectConfig *objectPointer)
{
	// Variables...
	struct ciscoCommand command;
	struct hostInterfaces *fw1InterfacePointer = 0;

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
		printf("Object Interface Line: %s\n", line);

		// New Interface...
		if ((command.part[0][0] == ':') && (strcasecmp(command.part[1], "()") != 0))
		{
			// Create Interface...
			fw1InterfacePointer = getFW1HostInterface(nipper, objectPointer, atoi(command.part[0] + 1));

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
					printf("Object Interface Line: %s\n", line);

				// IP Address...
				if (strcasecmp(command.part[0], ":ipaddr") == 0)
				{
					command.part[1][strlen(command.part[1]) -1] = 0;
					strncpy(fw1InterfacePointer->address, command.part[1] + 1, sizeof(fw1InterfacePointer->address) - 1);
				}
	
				// Net Mask...
				else if (strcasecmp(command.part[0], ":netmask") == 0)
				{
					command.part[1][strlen(command.part[1]) -1] = 0;
					strncpy(fw1InterfacePointer->netMask, command.part[1] + 1, sizeof(fw1InterfacePointer->netMask) - 1);
				}
	
				// Dynamic IP...
				else if ((strcasecmp(command.part[0], ":dynamic_ip") == 0) && (strcasecmp(command.part[1], "(true)") == 0))
					fw1InterfacePointer->dynamicIP = true;
				else if ((strcasecmp(command.part[0], ":dynamic_ip") == 0) && (strcasecmp(command.part[1], "(false)") == 0))
					fw1InterfacePointer->dynamicIP = false;
	
				// Dynamic IP...
				else if (strcasecmp(command.part[0], ":officialname") == 0)
				{
					command.part[1][strlen(command.part[1]) -1] = 0;
					strncpy(fw1InterfacePointer->name, command.part[1] + 1, sizeof(fw1InterfacePointer->name) - 1);
				}

				// Process Unknown...
				else
					processFW1Unknown(nipper, line);
			}
			fw1InterfacePointer = 0;
			command.part[0][0] = 0;
		}

		// Process Unknown...
		else
			processFW1Unknown(nipper, line);
	}
}


// Process Firewall-1 objects...
void processFW1Objects(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct ciscoCommand command;
	struct objectMember *memberPointer = 0;
	struct objectConfig *objectPointer = 0;
	struct hostInterfaces *fw1InterfacePointer = 0;
	struct objectListConfig *objectListPointer = 0;
	int tempInt = 0;

	// Debug output
	if (nipper->debugMode == true)
		printf("Object Line: %s\n", line);

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
			printf("Object Line: %s\n", line);

		// If it is a new object
		if (strcasecmp(command.part[0], ":") == 0)
		{
			// If the object list has not been created
			if (objectListPointer == 0)
				objectListPointer = getObjectListPointer(nipper, "FW1-Objects");
			objectPointer = getObjectPointer(objectListPointer, command.part[1] + 1);

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
					printf("Object Line: %s\n", line);

				// IP Address...
				if ((strcasecmp(command.part[0], ":ipaddr") == 0) || (strcasecmp(command.part[0], ":ipaddr_first") == 0))
				{
					command.part[1][strlen(command.part[1]) -1] = 0;
					strncpy(objectPointer->address, command.part[1] + 1, sizeof(objectPointer->address) - 1);
				}
	
				// Net Mask...
				else if ((strcasecmp(command.part[0], ":netmask") == 0) || (strcasecmp(command.part[0], ":ipaddr_last") == 0))
				{
					command.part[1][strlen(command.part[1]) -1] = 0;
					strncpy(objectPointer->netMask, command.part[1] + 1, sizeof(objectPointer->netMask) - 1);
				}
	
				// Firewall...
				else if ((strcasecmp(command.part[0], ":firewall") == 0) && (strcasecmp(command.part[1], "(installed)") == 0))
					objectPointer->firewall = true;
	
				// Location...
				else if ((strcasecmp(command.part[0], ":location") == 0) && (strcasecmp(command.part[1], "(external)") == 0))
					objectPointer->internal = false;
	
				// CP Version...
				else if (strcasecmp(command.part[0], ":cpver") == 0)
				{
					command.part[1][strlen(command.part[1]) -1] = 0;
					strncpy(objectPointer->cpVersion, command.part[1] + 1, sizeof(objectPointer->cpVersion) - 1);
					objectPointer->cpVersionMajor = atoi(objectPointer->cpVersion);
					objectPointer->cpVersionMinor = atoi(strchr(objectPointer->cpVersion, '.') + 1);
				}
	
				// Interfaces...
				else if ((strcasecmp(command.part[0], ":interfaces") == 0) && (strcasecmp(command.part[1], "()") != 0))
					processFW1ObjectsInterfaces(line, nipper, objectPointer);
	
				// Management...
				else if ((strcasecmp(command.part[0], ":management") == 0) && (strcasecmp(command.part[1], "(true)") == 0))
					objectPointer->management = true;
	
				// Type...
				else if (strcasecmp(command.part[0], ":type") == 0)
				{
					if (strcasecmp(command.part[1], "(host)") == 0)
					{
						nipper->fw1->hostObjectCount++;
						objectPointer->type = object_type_host;
					}
					else if (strcasecmp(command.part[1], "(machines_range)") == 0)
					{
						nipper->fw1->machinesRangeObjectCount++;
						objectPointer->type = object_type_machinesrange;
					}
					else if (strcasecmp(command.part[1], "(dynamic_net_obj)") == 0)
					{
						nipper->fw1->dynamicNetObjectCount++;
						objectPointer->type = object_type_dynamicnet;
					}
					else if (strcasecmp(command.part[1], "(group)") == 0)
					{
						nipper->fw1->groupObjectCount++;
						objectPointer->type = object_type_group;
					}
					else if (strcasecmp(command.part[1], "(network)") == 0)
					{
						nipper->fw1->networkObjectCount++;
						objectPointer->type = object_type_network;
					}
					else if (strcasecmp(command.part[1], "(gateway)") == 0)
					{
						nipper->fw1->gatewayObjectCount++;
						objectPointer->type = object_type_gateway;
					}
					else if (strcasecmp(command.part[1], "(gateway_cluster)") == 0)
					{
						nipper->fw1->gatewayClusterObjectCount++;
						objectPointer->type = object_type_gateway_cluster;
					}
					else if (strcasecmp(command.part[1], "(cluster_member)") == 0)
					{
						nipper->fw1->clusterMemberObjectCount++;
						objectPointer->type = object_type_cluster_member;
					}
	
					// Create a delete me object...
					else
						objectPointer->type = object_type_delete_me;
				}

				// Cluster Members...
				else if ((strcasecmp(command.part[0], ":cluster_members") == 0) && (strcasecmp(command.part[1], "(") == 0))
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
							printf("Object Line: %s\n", line);
	
						// New member...
						if ((command.part[0][0] == ':') && (strcasecmp(command.part[1], "(ReferenceObject") == 0))
						{
							tempInt = atoi(command.part[0] + 1);
							while ((feof(nipper->input) == 0) && (strcasecmp(command.part[0], ")") != 0))
							{
								// Read line
								memset(line, 0, LINE_SIZE + 1);
								readLine(nipper->input, line, LINE_SIZE);
		
								// Init...
								command = splitLine(line);
						
								// Debug output
								if (nipper->debugMode == true)
									printf("Object Line: %s\n", line);
									
								if (strcasecmp(command.part[0], ":Name") == 0)
								{
									command.part[1][strlen(command.part[1]) -1] = 0;
									memberPointer = getObjectMember(objectPointer, command.part[1] + 1);
									memberPointer->type = object_type_object;
									memberPointer->number = tempInt;
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

				// Group Members...
				else if ((strcasecmp(command.part[0], ":") == 0) && (strcasecmp(command.part[1], "(ReferenceObject") != 0) && (strncmp(line, "\t\t\t:", 4) == 0))
				{
					memberPointer = getObjectMember(objectPointer, command.part[1]);
					memberPointer->type = object_type_object;
				}
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
							printf("Object Line: %s\n", line);
	
						// Name...
						if (strcasecmp(command.part[0], ":Name") == 0)
						{
							command.part[1][strlen(command.part[1]) -1] = 0;
							memberPointer = getObjectMember(objectPointer, command.part[1] + 1);
							memberPointer->type = object_type_object;
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

			// If delete me object...
			if (objectPointer->type == object_type_delete_me)
			{
				if (objectListPointer->object->type == object_type_delete_me)
				{
					while (objectListPointer->object->interfaces != 0)
					{
						fw1InterfacePointer = objectListPointer->object->interfaces->next;
						free(objectListPointer->object->interfaces);
						objectListPointer->object->interfaces = fw1InterfacePointer;
					}
					while (objectListPointer->object->members != 0)
					{
						memberPointer = objectListPointer->object->members->next;
						free(objectListPointer->object->members);
						objectListPointer->object->members = memberPointer;
					}
					free(objectListPointer->object);
					objectListPointer->object = 0;
				}
				else
				{
					objectPointer = objectListPointer->object;
					while (objectPointer->next->type != object_type_delete_me)
						objectPointer = objectPointer->next;
					while (objectPointer->next->interfaces != 0)
					{
						fw1InterfacePointer = objectPointer->next->interfaces->next;
						free(objectPointer->next->interfaces);
						objectPointer->next->interfaces = fw1InterfacePointer;
					}
					while (objectPointer->next->members != 0)
					{
						memberPointer = objectPointer->next->members->next;
						free(objectPointer->next->members);
						objectPointer->next->members = memberPointer;
					}
					free(objectPointer->next);
					objectPointer->next = 0;
				}
			}
			objectPointer = 0;
			command.part[0][0] = 0;
		}
	
		// Process Unknown...
		else
			processFW1Unknown(nipper, line);
	}
}

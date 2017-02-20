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


void processFW1Services(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct ciscoCommand command;
	struct objectListConfig *objectListPointer = 0;
	struct objectConfig *objectPointer = 0;
	struct objectMember *memberPointer = 0;

	// Debug output
	if (nipper->debugMode == true)
		printf("Service Line: %s\n", line);

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
			printf("Service Line: %s\n", line);

		// If it is a new object
		if (strcasecmp(command.part[0], ":") == 0)
		{
			// If the object list has not been created
			if (objectListPointer == 0)
				objectListPointer = getObjectListPointer(nipper, "FW1-Services");
			objectPointer = getObjectPointer(objectListPointer, command.part[1] + 1);
			objectPointer->type = object_type_service;
			nipper->fw1->serviceCount++;

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

				// Protocol...
				if ((strcasecmp(command.part[0], ":protocol") == 0) && (strcasecmp(command.part[1], "()") != 0))
				{
					command.part[1][strlen(command.part[1]) - 2] = 0;
					objectPointer->serviceType = atoi(command.part[1] + 1);
				}

				// Port...
				else if ((strcasecmp(command.part[0], ":port") == 0) && (strcasecmp(command.part[1], "()") != 0))
				{
					command.part[1][strlen(command.part[1]) - 1] = 0;
					stripQuotes(command.part[1] + 1, objectPointer->address, sizeof(objectPointer->address) -1);
				}

				// Type...
				else if (strcasecmp(command.part[0], ":type") == 0)
				{
					if (strcasecmp(command.part[1], "(tcp)") == 0)
						objectPointer->serviceType = service_protocol_tcp;
					else if (strcasecmp(command.part[1], "(udp)") == 0)
						objectPointer->serviceType = service_protocol_udp;
					else if (strcasecmp(command.part[1], "(other)") == 0)
						objectPointer->serviceType = service_protocol_other;
					else if (strcasecmp(command.part[1], "(group)") == 0)
					{
						nipper->fw1->serviceCount--;
						nipper->fw1->serviceGroupCount++;
						objectPointer->type = object_type_group;
						objectPointer->serviceType = service_protocol_none;
					}
					else if (strcasecmp(command.part[1], "(DceRpc)") == 0)
						objectPointer->serviceType = service_protocol_dcerpc;
					else if (strcasecmp(command.part[1], "(Rpc)") == 0)
						objectPointer->serviceType = service_protocol_rpc;
					else if (strcasecmp(command.part[1], "(Icmp)") == 0)
						objectPointer->serviceType = service_protocol_icmp;
					else if (strcasecmp(command.part[1], "(Tcp_subservice)") == 0)
						objectPointer->serviceType = service_protocol_tcpsub;
					else if (strcasecmp(command.part[1], "(gtp)") == 0)
						objectPointer->serviceType = service_protocol_gtp0;
					else if (strcasecmp(command.part[1], "(gtp_v1)") == 0)
						objectPointer->serviceType = service_protocol_gtp1;
					else
						objectPointer->serviceType = service_protocol_unknown;
				}

				// Comments...
				else if ((strcasecmp(command.part[0], ":comments") == 0) && (strcasecmp(command.part[1], "()") != 0))
				{
					command.part[1][strlen(command.part[1]) - 1] = 0;
					stripQuotes(command.part[1] + 1, objectPointer->comment, sizeof(objectPointer->comment) -1);
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
							printf("Service Line: %s\n", line);
	
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
				nipper->fw1->serviceCount--;
				if (objectListPointer->object->type == object_type_delete_me)
				{
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




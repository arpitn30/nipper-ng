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


// Process Object Groups
void processObjectGroup(char *line, struct nipperConfig *nipper)
{
	// Variables...
	int tempInt = 0;
	fpos_t filePosition;
	char tempString[nipper->maxSize];
	char tempString2[nipper->maxSize];
	struct ciscoCommand command;
	struct objectListConfig *objectListPointer = 0;
	struct objectConfig *objectPointer = 0;
	struct objectMember *memberPointer = 0;

	// Debug output
	if (nipper->debugMode == true)
		printf("Object Group Line: %s\n", line);

	// Init Struct
	command = splitLine(line);

	// Get pointer to object list...
	objectListPointer = getObjectListPointer(nipper, "OBJECTLIST");

	// Get pointer to object group...
	objectPointer = getObjectPointer(objectListPointer, command.part[2]);

	// Object Type
	if (strcmp(command.part[1], "network") == 0)
		objectPointer->type = object_type_group;
	else if (strcmp(command.part[1], "protocol") == 0)
		objectPointer->type = object_type_protocol;
	else if (strcmp(command.part[1], "service") == 0)
		objectPointer->type = object_type_service;
	else if (strcmp(command.part[1], "icmp-type") == 0)
		objectPointer->type = object_type_icmp;

	// Service object group type...
	if ((command.parts == 4) && (objectPointer->type == object_type_service))
	{
		if (strcmp(command.part[3], "tcp") == 0)
			objectPointer->serviceType = service_protocol_tcp;
		else if (strcmp(command.part[3], "udp") == 0)
			objectPointer->serviceType = service_protocol_udp;
		else if (strcmp(command.part[3], "tcp-udp") == 0)
			objectPointer->serviceType = service_protocol_both;
	}

	// Loop through the object lines
	fgetpos(nipper->input, &filePosition);
	readLine(nipper->input, line, nipper->maxSize);
	while ((feof(nipper->input) == 0) && (line[0] == ' '))
	{
		// Debug
		if (nipper->debugMode == true)
		{
			printf("Object Group Line: %s\n", line);
		}

		// Init
		command = splitLine(line);

		// Description
		if (strcmp(command.part[0], "description") == 0)
		{
			memset(tempString, 0, nipper->maxSize);
			memset(tempString2, 0, nipper->maxSize);
			for (tempInt = 1; tempInt < command.parts; tempInt++)
			{
				sprintf(tempString, "%s%s ", tempString2, command.part[tempInt]);
				strncpy(tempString2, tempString, nipper->maxSize);
			}
			tempString2[strlen(tempString2) - 1] = 0;
			strncpy(objectPointer->comment, tempString2, sizeof(objectPointer->comment) - 1);
		}
		else
		{

			if (strcmp(command.part[0], "network-object") == 0)
			{
				if (strcmp(command.part[1], "host") == 0)
				{
					memberPointer = getObjectMember(objectPointer, command.part[2]);
					memberPointer->type = object_type_host;
				}
				else
				{
					memberPointer = getObjectMember(objectPointer, command.part[1]);
					if (command.parts > 2)
						strncpy(memberPointer->netMask, command.part[2], sizeof(memberPointer->netMask) - 1);
					if (strcmp(memberPointer->netMask, "255.255.255.255") != 0)
						memberPointer->type = object_type_network;
					else
						memberPointer->type = object_type_host;
				}
			}
			else if (strcmp(command.part[0], "group-object") == 0)
			{
				memberPointer = getObjectMember(objectPointer, command.part[1]);
				memberPointer->type = object_type_group;
			}
			else if (strcmp(command.part[0], "port-object") == 0)
			{
				if (strcmp(command.part[1], "eq") == 0)
				{
					memberPointer = getObjectMember(objectPointer, command.part[2]);
					memberPointer->type = object_type_port;
					memberPointer->serviceOp = service_oper_eq;
				}
				else if (strcmp(command.part[1], "range") == 0)
				{
					memberPointer = getObjectMember(objectPointer, command.part[2]);
					memberPointer->type = object_type_port;
					memberPointer->serviceOp = service_oper_eq;
					if (command.parts > 3)
					{
						strncpy(memberPointer->netMask, command.part[3], sizeof(memberPointer->netMask) - 1);
						memberPointer->serviceOp = service_oper_range;
					}
				}
				else
				{
					memberPointer = getObjectMember(objectPointer, command.part[1]);
					memberPointer->type = object_type_port;
					memberPointer->serviceOp = service_oper_eq;
					if (command.parts > 2)
					{
						strncpy(memberPointer->netMask, command.part[2], sizeof(memberPointer->netMask) - 1);
						memberPointer->serviceOp = service_oper_range;
					}
				}
				memberPointer->type = object_type_port;
			}
			else if (strcmp(command.part[0], "icmp-object") == 0)
			{
				memberPointer = getObjectMember(objectPointer, command.part[1]);
				memberPointer->type = object_type_icmp;
			}
			else if (strcmp(command.part[0], "protocol-object") == 0)
			{
				memberPointer = getObjectMember(objectPointer, command.part[1]);
				memberPointer->type = object_type_protocol;
			}
		}

		// Get next line
		fgetpos(nipper->input, &filePosition);
		readLine(nipper->input, line, nipper->maxSize);
	}

	// Set file position back
	fsetpos(nipper->input, &filePosition);
}



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


void processSonicOSService(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct objectListConfig *objectListPointer = 0;
	struct objectConfig *objectPointer = 0;
	struct ciscoCommand command;

	// Debug output
	if (nipper->debugMode == true)
		printf("Service Line: %s\n", line);

	// Init
	command = splitLine(line);

	// Service Port (start)...
	if (strncmp(command.part[0], "svcObjPort1_", 12) == 0)
	{
		objectListPointer = getObjectListPointer(nipper, "SERVICES");
		objectPointer = getObjectPointer(objectListPointer, command.part[0] + 12);
		strncpy(objectPointer->address, command.part[1], sizeof(objectPointer->address) - 1);
		objectPointer->type = object_type_service;
	}
	else if (strncmp(command.part[0], "prefs_svcPortNum_", 17) == 0)
	{
		objectListPointer = getObjectListPointer(nipper, "SERVICES");
		objectPointer = getObjectPointer(objectListPointer, command.part[0] + 17);
		strncpy(objectPointer->address, command.part[1], sizeof(objectPointer->address) - 1);
		objectPointer->type = object_type_service;
	}

	// Service Port (end)...
	else if (strncmp(command.part[0], "svcObjPort2_", 12) == 0)
	{
		objectListPointer = getObjectListPointer(nipper, "SERVICES");
		objectPointer = getObjectPointer(objectListPointer, command.part[0] + 12);
		strncpy(objectPointer->netMask, command.part[1], sizeof(objectPointer->netMask) - 1);
		if (strcmp(objectPointer->netMask, objectPointer->address) != 0)
			objectPointer->type = object_type_servicerange;
		else if ((strcmp(objectPointer->netMask, "65535") == 0) && (strcmp(objectPointer->address, "65535") == 0))
			objectPointer->type = object_type_any;
	}
	else if (strncmp(command.part[0], "prefs_svcPortEnd_", 17) == 0)
	{
		objectListPointer = getObjectListPointer(nipper, "SERVICES");
		objectPointer = getObjectPointer(objectListPointer, command.part[0] + 17);
		strncpy(objectPointer->netMask, command.part[1], sizeof(objectPointer->netMask) - 1);
		if (strcmp(objectPointer->netMask, objectPointer->address) != 0)
			objectPointer->type = object_type_servicerange;
		else if ((strcmp(objectPointer->netMask, "65535") == 0) && (strcmp(objectPointer->address, "65535") == 0))
			objectPointer->type = object_type_any;
	}

	// Service IP Type...
	else if (strncmp(command.part[0], "svcObjIpType_", 13) == 0)
	{
		objectListPointer = getObjectListPointer(nipper, "SERVICES");
		objectPointer = getObjectPointer(objectListPointer, command.part[0] + 13);
		objectPointer->serviceType = atoi(command.part[1]);
	}
	else if (strncmp(command.part[0], "prefs_svcIPType_", 16) == 0)
	{
		objectListPointer = getObjectListPointer(nipper, "SERVICES");
		objectPointer = getObjectPointer(objectListPointer, command.part[0] + 16);
		objectPointer->serviceType = atoi(command.part[1]);
	}

	// Service Name...
	else if (strncmp(command.part[0], "svcObjId_", 9) == 0)
	{
		objectListPointer = getObjectListPointer(nipper, "SERVICES");
		objectPointer = getObjectPointer(objectListPointer, command.part[0] + 9);
		if (objectPointer->type == object_type_any)
			strcpy(objectPointer->comment, "Any");
		else
			strncpy(objectPointer->comment, line + strlen(command.part[0]) + 1, sizeof(objectPointer->comment) - 1);
	}
	else if (strncmp(command.part[0], "prefs_svcName_", 14) == 0)
	{
		objectListPointer = getObjectListPointer(nipper, "SERVICES");
		objectPointer = getObjectPointer(objectListPointer, command.part[0] + 14);
		if (objectPointer->type == object_type_any)
			strcpy(objectPointer->comment, "Any");
		else
			strncpy(objectPointer->comment, line + strlen(command.part[0]) + 1, sizeof(objectPointer->comment) - 1);
	}
}

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


// Process address lines
void processSOSAddress(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct objectListConfig *objectListPointer = 0;
	struct objectConfig *objectPointer = 0;
	char tempString[nipper->maxSize];
	int position = 0;
	char *stringPointer = 0;
	struct ciscoCommand command;

	// Debug Mode
	if (nipper->debugMode == true)
		printf("Address Line: %s\n", line);

	// Init
	position = 2;
	command = splitLine(line);

	// Get Name List
	stripQuotes(command.part[position], tempString, nipper->maxSize);
	objectListPointer = getObjectListPointer(nipper, tempString);
	position++;

	// Add Name Mapping
	stripQuotes(command.part[position], tempString, nipper->maxSize);
	objectPointer = getObjectPointer(objectListPointer, tempString);
	position++;

	// Get Mapping Address / FQDN
	stripQuotes(command.part[position], tempString, nipper->maxSize);
	stringPointer = strchr(tempString, '/');
	
	// Address and Name Mask
	if (stringPointer == NULL)
	{
		strncpy(objectPointer->address, tempString, sizeof(objectPointer->address) - 1);
		position++;
		// Get netmask
		stripQuotes(command.part[position], tempString, nipper->maxSize);
		strncpy(objectPointer->netMask, tempString, sizeof(objectPointer->netMask) - 1);
	}
	else
	{
		stringPointer[0] = 0;
		strncpy(objectPointer->address, tempString, sizeof(objectPointer->address) - 1);
		setMaskFromCIDR(objectPointer->netMask, atoi(stringPointer + 1));
	}
	if (strcmp(objectPointer->netMask, "255.255.255.255") == 0)
		objectPointer->type = object_type_host;
	else
		objectPointer->type = object_type_network;
	position++;

	// If there is a comment
	if (position < command.parts)
	{
		stripQuotes(command.part[position], tempString, nipper->maxSize);
		strncpy(objectPointer->comment, tempString, sizeof(objectPointer->comment) - 1);
	}

	nipper->sos->nameMappings = true;
}


// Process group address lines
void processSOSGroupAddress(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct objectListConfig *objectListPointer = 0;
	struct objectConfig *objectPointer = 0;
	struct objectMember *memberPointer = 0;
	char tempString[nipper->maxSize];
	char tempString2[nipper->maxSize];
	int position = 0;
	struct ciscoCommand command;

	// Debug Mode
	if (nipper->debugMode == true)
		printf("Group Address Line: %s\n", line);

	// Init
	position = 3;
	command = splitLine(line);

	// Get Address Name List
	stripQuotes(command.part[position], tempString2, nipper->maxSize);
	sprintf(tempString, "**ADDR-GRP**%s", tempString2);
	objectListPointer = getObjectListPointer(nipper, tempString);
	position++;

	// Add Name Mapping
	stripQuotes(command.part[position], tempString, nipper->maxSize);
	objectPointer = getObjectPointer(objectListPointer, tempString);
	objectPointer->type = object_type_group;
	position++;

	// Create the mapping...
	if (command.parts == position)
		objectPointer->type = object_type_group;

	// Add an entry to it...
	else if (strcasecmp(command.part[position], "add") == 0)
	{
		position++;

		// Add entry
		stripQuotes(command.part[position], tempString, nipper->maxSize);
		memberPointer = getObjectMember(objectPointer, tempString);
		memberPointer->type = object_type_object;
	}

	nipper->sos->nameGroupMappings = true;
}


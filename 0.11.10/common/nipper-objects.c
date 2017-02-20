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

// This file contains all the code for objects...


struct objectListConfig
{
	char name[64];

	struct objectConfig *object;

	// Next list...
	struct objectListConfig *next;
};


struct objectConfig
{
	char name[64];
	char address[64];
	char netMask[16];
	int type;							// object_type_network...
	char comment[128];					// Used by ScreenOS and is Description with PIX
	
	// Cisco PIX (also used by SonicOS and FW1)...
	int serviceType;					// object_service_tcp...

	// Used by FW1...
	int firewall;						// Is the object a firewall? (FW1)
	int internal;						// Is the object internal? (FW1)
	int management;						// Is management firewall?
	char cpVersion[8];					// CheckPoint Version
	int cpVersionMajor;					//      Major
	int cpVersionMinor;					//      Minor
	struct objectMember *members;		// Group members
	struct hostInterfaces *interfaces;	// Interfaces

	struct objectConfig *next;
};


struct objectMember
{
	int number;							// Used for cluster members
	char name[64];
	char netMask[16];
	int type;
	int serviceOp;
	struct objectMember *next;
};


// Interface config used by Firewall-1
struct hostInterfaces
{
	int interface;						// Interface No.
	int dynamicIP;
	char name[16];						// Interface name
	char address[16];
	char netMask[16];
	struct hostInterfaces *next;
};


// Get pointer to object list (or create a new one)...
struct objectListConfig *getObjectListPointer(struct nipperConfig *nipper, char *name)
{
	// Variables...
	struct objectListConfig *objectListPointer = 0;
	int init = false;

	// If first object list...
	if (nipper->objectList == 0)
	{
		nipper->objectList = malloc(sizeof(struct objectListConfig));
		objectListPointer = nipper->objectList;
		init = true;
	}
	else
	{
		objectListPointer = nipper->objectList;
		while ((objectListPointer->next != 0) && (strcmp(objectListPointer->name, name) != 0))
			objectListPointer = objectListPointer->next;
		if (strcmp(objectListPointer->name, name) != 0)
		{
			objectListPointer->next = malloc(sizeof(struct objectListConfig));
			objectListPointer = objectListPointer->next;
			init = true;
		}
	}

	// Init...
	if (init == true)
	{
		memset(objectListPointer, 0, sizeof(struct objectListConfig));
		strncpy(objectListPointer->name, name, sizeof(objectListPointer->name) - 1);
	}

	return objectListPointer;
}


// Get pointer to object (or create a new one)...
struct objectConfig *getObjectPointer(struct objectListConfig *objectListPointer, char *name)
{
	// Variables...
	struct objectConfig *objectPointer = 0;
	int init = false;

	// If first object
	if (objectListPointer->object == 0)
	{
		objectListPointer->object = malloc(sizeof(struct objectConfig));
		objectPointer = objectListPointer->object;
		init = true;
	}
	else
	{
		objectPointer = objectListPointer->object;
		while ((objectPointer->next != 0) && (strcmp(objectPointer->name, name) != 0))
			objectPointer = objectPointer->next;
		if (strcmp(objectPointer->name, name) != 0)
		{
			objectPointer->next = malloc(sizeof(struct objectConfig));
			objectPointer = objectPointer->next;
			init = true;
		}
	}

	// Init...
	if (init == true)
	{
		memset(objectPointer, 0, sizeof(struct objectConfig));
		strncpy(objectPointer->name, name, sizeof(objectPointer->name) - 1);
		objectPointer->firewall = false;
		objectPointer->internal = true;
		objectPointer->management = false;
	}

	return objectPointer;
}


// Get a pointer to an object member (or add one)...
struct objectMember *getObjectMember(struct objectConfig *objectPointer, char *member)
{
	// Variables...
	struct objectMember *memberPointer = 0;
	int init = false;

	// If first...
	if (objectPointer->members == 0)
	{
		objectPointer->members = malloc(sizeof(struct objectMember));
		memberPointer = objectPointer->members;
		init = true;
	}
	else
	{
		memberPointer = objectPointer->members;
		while ((memberPointer->next != 0) && (strcmp(memberPointer->name, member) != 0))
			memberPointer = memberPointer->next;
		if (strcmp(memberPointer->name, member) != 0)
		{
			memberPointer->next = malloc(sizeof(struct objectMember));
			memberPointer = memberPointer->next;
			init = true;
		}
	}

	// Init?
	if (init == true)
	{
		memset(memberPointer, 0, sizeof(struct objectMember));
		strncpy(memberPointer->name, member, sizeof(memberPointer->name) - 1);
		memberPointer->type = object_type_notset;
	}

	return memberPointer;
}


// Set netmask from CIDR...
void setMaskFromCIDR(char *netmask, int cidr)
{
	const char netmasks[][16] = { "0.0.0.0", "128.0.0.0", "192.0.0.0", "224.0.0.0", "240.0.0.0",
	                              "248.0.0.0", "252.0.0.0", "254.0.0.0", "255.0.0.0", "255.128.0.0",
	                              "255.192.0.0", "255.224.0.0", "255.240.0.0", "255.248.0.0",
	                              "255.252.0.0", "255.254.0.0", "255.255.0.0", "255.255.128.0",
	                              "255.255.192.0", "255.255.224.0", "255.255.240.0", "255.255.248.0",
	                              "255.255.252.0", "255.255.254.0", "255.255.255.0", "255.255.255.128",
	                              "255.255.255.192", "255.255.255.224", "255.255.255.240",
	                              "255.255.255.248", "255.255.255.252", "255.255.255.254",
	                              "255.255.255.255" };

	strcpy(netmask, netmasks[cidr]);
}


// Output the ACL debug information...
void reportObjectsDebug(struct nipperConfig *nipper)
{
	// Variables...
	struct objectListConfig *objectListPointer = 0;
	struct objectConfig *objectPointer = 0;
	struct hostInterfaces *fw1InterfacePointer = 0;
	struct objectMember *memberPointer = 0;

	objectListPointer = nipper->objectList;
	while (objectListPointer != 0)
	{
		printf("Object List: %s\n", objectListPointer->name);
		objectPointer = objectListPointer->object;
		while (objectPointer != 0)
		{
			printf("  Object: %s\n", objectPointer->name);
			printf("    Address: %s\n", objectPointer->address);
			printf("    Netmask: %s\n", objectPointer->netMask);
			printf("    Comment: %s\n", objectPointer->comment);
			printf("    Type: %d\n", objectPointer->type);
			printf("    Service Type: %d\n", objectPointer->serviceType);
			printf("    Firewall: %d\n", objectPointer->firewall);
			printf("    Internal: %d\n", objectPointer->internal);
			printf("    Management: %d\n", objectPointer->management);
			printf("    CP Version: %s\n", objectPointer->cpVersion);
			printf("    CP Version Major: %d\n", objectPointer->cpVersionMajor);
			printf("    CP Version Minor: %d\n", objectPointer->cpVersionMinor);
			fw1InterfacePointer = objectPointer->interfaces;
			while (fw1InterfacePointer != 0)
			{
				printf("    Interface: %d\n", fw1InterfacePointer->interface);
				printf("      Name: %s\n", fw1InterfacePointer->name);
				printf("      Dynamic IP: %d\n", fw1InterfacePointer->dynamicIP);
				printf("      Address: %s\n", fw1InterfacePointer->address);
				printf("      Net Mask: %s\n", fw1InterfacePointer->netMask);
				fw1InterfacePointer = fw1InterfacePointer->next;
			}
			memberPointer = objectPointer->members;
			while (memberPointer != 0)
			{
				printf("      Member: %s\n", memberPointer->name);
				printf("        Number: %d\n", memberPointer->number);
				printf("        Mask: %s\n", memberPointer->netMask);
				printf("        Type: %d\n", memberPointer->type);
				memberPointer = memberPointer->next;
			}
			objectPointer = objectPointer->next;
		}
		objectListPointer = objectListPointer->next;
	}
}


// Report name mappings...
void nameMapConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct objectListConfig *objectListPointer = 0;
	struct objectConfig *objectPointer = 0;

	objectListPointer = nipper->objectList;
	while (strcmp(objectListPointer->name, "NAMELIST") != 0)
		objectListPointer = objectListPointer->next;

	output_table(nipper, true, settings_namemap_table, &settings_namemap_heading);
	objectPointer = objectListPointer->object;
	while (objectPointer != 0)
	{
		fprintf(nipper->reportFile, "%s%s%s%s%s", nipper->tablerow_start, objectPointer->name, nipper->tablerow_mid, objectPointer->address, nipper->tablerow_end);
		objectPointer = objectPointer->next;
	}
	output_table(nipper, false, settings_namemap_table, &settings_namemap_heading);
}



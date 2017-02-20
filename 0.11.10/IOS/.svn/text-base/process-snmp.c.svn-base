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


// SNMP Community
struct snmpCommunity
{
	char community[64];
	int weak;
	int dictionary;
	int readonly;					// true (default) or false
	int enabled;					// true (default) or false
	char accessList[65];
	char viewName[65];
	struct snmpCommunity *next;
};

// SNMP View Item
struct snmpViewItem
{
	char mibId[128];
	int include;					// true or false
	struct snmpViewItem *next;
};

// SNMP View
struct snmpView
{
	char viewName[65];
	struct snmpViewItem *viewItem;
	struct snmpView *next;
};

#define snmp3_none 0
#define snmp3_des 1
#define snmp3_3des 2
#define snmp3_aes128 3
#define snmp3_aes192 4
#define snmp3_aes256 5
#define snmp3_md5 6
#define snmp3_sha 7
#define snmp3_des56 8

// SNMP User
struct snmpUser
{
	char groupName[65];
	char userName[65];
	int version;
	int encryption;					// true of false
	int snmp3auth;					// snmp3_none, snmp3_md5 or snmp3_sha
	char authPass[128];
	int snmp3priv;					// snmp3_none, snmp3_des, snmp3_3des, snmp3_aes123(192 or 256)
	char privPass[128];
	char acl[65];
	int group;
	struct snmpUser *next;
};

// SNMP Group
struct snmpGroup
{
	char groupName[65];
	int version;					// snmp1, snmp2c...
	char readView[65];
	char writeView[65];
	char notifyView[65];
	char context[65];
	char acl[65];
	struct snmpGroup *next;
};


// SNMP Host
struct snmpHost
{
	char host[32];
	char community[64];
	int version;					// snmp1, snmp2c...
	int weak;
	int dictionary;
	struct snmpHost *next;
};

// SNMP
struct snmpConfig
{
	int enabled;					// true or false
	char tftpServerList[32];
	char contact[64];
	char location[64];
	int trapTimeout;
	char trapSource[32];
	struct snmpCommunity *community;
	struct snmpGroup *group;
	struct snmpUser *user;
	struct snmpView *view;
	struct snmpTrap *trap;
	struct snmpHost *host;
};


// Process SNMP
void processSnmp(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct snmpCommunity *communityPointer = 0;
	struct snmpViewItem *snmpViewItemPointer = 0;
	struct snmpView *snmpViewPointer = 0;
	struct snmpGroup *snmpGroupPointer = 0;
	struct snmpUser *snmpUserPointer = 0;
	struct snmpTrap *snmpTrapPointer = 0;
	struct snmpHost *snmpHostPointer = 0;
	struct ciscoCommand command;
	char tempString[nipper->maxSize];
	int tempInt = 0;
	int setting = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("SNMP Line: %s\n", line);
	}

	// Init
	command = splitLine(line);
	if (strcmp(command.part[0], "no") == 0)
	{
		setting = false;
		tempInt = 2;
	}
	else
	{
		setting = true;
		tempInt = 1;
	}

	// Check to see if SNMP already exists
	if (nipper->ios->snmp == 0)
	{
		nipper->ios->snmp = malloc(sizeof(struct snmpConfig));
		memset(nipper->ios->snmp, 0, sizeof(struct snmpConfig));

		// Init
		nipper->ios->snmp->enabled = true;
		nipper->ios->snmp->trapTimeout = 30;
	}

	// Is SNMP disabled / enabled?
	if (command.parts == tempInt)
		nipper->ios->snmp->enabled = setting;

	// snmp contact info?
	else if (strcmp(command.part[tempInt], "contact") == 0)
		strncpy(nipper->ios->snmp->contact, line + 20, sizeof(nipper->ios->snmp->contact));

	// snmp location info?
	else if (strcmp(command.part[tempInt], "location") == 0)
		strncpy(nipper->ios->snmp->location, line + 21, sizeof(nipper->ios->snmp->location));

	// Trap Timeout
	else if (strcmp(command.part[tempInt], "trap-timeout") == 0)
		nipper->ios->snmp->trapTimeout = atoi(command.part[tempInt+1]);

	// Trap Interface
	else if (strcmp(command.part[tempInt], "trap-source") == 0)
		strncpy(nipper->ios->snmp->trapSource, command.part[tempInt+1], sizeof(nipper->ios->snmp->trapSource) - 1);

	// tftp server access list?
	else if (strcmp(command.part[tempInt], "tftp-server-list") == 0)
		strncpy(nipper->ios->snmp->tftpServerList, command.part[tempInt+1], sizeof(nipper->ios->snmp->tftpServerList) - 1);

	// snmp view?
	else if (strcmp(command.part[tempInt], "view") == 0)
	{
		tempInt++;

		// Is this the first view?
		if (nipper->ios->snmp->view == 0)
		{
			// create structure...
			nipper->ios->snmp->view = malloc(sizeof(struct snmpView));
			memset(nipper->ios->snmp->view, 0, sizeof(struct snmpView));
			snmpViewPointer = nipper->ios->snmp->view;

			// init
			snmpViewPointer->viewItem = 0;
			strncpy(snmpViewPointer->viewName, command.part[tempInt], sizeof(snmpViewPointer->viewName) - 1);
		}

		else
		{
			// Search for existing view name
			snmpViewPointer = nipper->ios->snmp->view;
			while ((snmpViewPointer->next != 0) && (strcmp(snmpViewPointer->viewName, command.part[tempInt]) != 0))
				snmpViewPointer = snmpViewPointer->next;

			// Do we need to create a new view?
			if (strcmp(snmpViewPointer->viewName, command.part[tempInt]) != 0)
			{
				// create structure...
				snmpViewPointer->next = malloc(sizeof(struct snmpView));
				memset(snmpViewPointer->next, 0, sizeof(struct snmpView));

				// Sort out pointers
				snmpViewPointer = snmpViewPointer->next;

				// init
				snmpViewPointer->viewItem = 0;
				strncpy(snmpViewPointer->viewName, command.part[tempInt], sizeof(snmpViewPointer->viewName) - 1);
			}
		}
		tempInt++;

		// Is it the first view item?
		if (snmpViewPointer->viewItem == 0)
		{
			snmpViewPointer->viewItem = malloc(sizeof(struct snmpViewItem));
			memset(snmpViewPointer->viewItem, 0, sizeof(struct snmpViewItem));
			snmpViewItemPointer = snmpViewPointer->viewItem;
		}
		else
		{
			// Find last view item
			snmpViewItemPointer = snmpViewPointer->viewItem;
			while (snmpViewItemPointer->next != 0)
				snmpViewItemPointer = snmpViewItemPointer->next;

			// create view item structure & sort pointers
			snmpViewItemPointer->next = malloc(sizeof(struct snmpViewItem));
			memset(snmpViewItemPointer->next, 0, sizeof(struct snmpViewItem));
			snmpViewItemPointer = snmpViewItemPointer->next;
		}

		// Set view item
		strncpy(snmpViewItemPointer->mibId, command.part[tempInt], sizeof(snmpViewItemPointer->mibId) - 1);
		tempInt++;

		// Include?
		if ((strcmp(command.part[tempInt], "include") == 0) || (strcmp(command.part[tempInt], "included") == 0))
			snmpViewItemPointer->include = true;
		else
			snmpViewItemPointer->include = false;
	}

	// snmp community?
	else if (strcmp(command.part[tempInt], "community") == 0)
	{
		tempInt++;

		// If first community...
		if (nipper->ios->snmp->community == 0)
		{
			// Reserve memory...
			nipper->ios->snmp->community = malloc(sizeof(struct snmpCommunity));
			communityPointer = nipper->ios->snmp->community;
		}
		else
		{
			// Find last...
			communityPointer = nipper->ios->snmp->community;
			while (communityPointer->next != 0)
				communityPointer = communityPointer->next;

			// Reserve memory...
			communityPointer->next = malloc(sizeof(struct snmpCommunity));
			communityPointer = communityPointer->next;
		}

		// Init community struct...
		memset(communityPointer, 0, sizeof(struct snmpCommunity));
		communityPointer->readonly = true;
		communityPointer->enabled = setting;
		communityPointer->weak = false;
		communityPointer->dictionary = false;

		// Set community string...
		strncpy(communityPointer->community, command.part[tempInt], sizeof(communityPointer->community) - 1);
		tempInt++;

		// Check strength / dictionary...
		if (simplePassword(communityPointer->community, nipper) == true)
		{
			nipper->simplePasswords++;
			communityPointer->dictionary = true;
		}
		if (passwordStrength(communityPointer->community, nipper) == false)
		{
			nipper->passwordStrengths++;
			communityPointer->weak = true;
		}

		// Get options...
		while (tempInt < command.parts)
		{

			// If view exists, get it...
			if (strcmp(command.part[tempInt], "view") == 0)
			{
				tempInt++;
				// Get view name...
				strncpy(communityPointer->viewName, command.part[tempInt], sizeof(communityPointer->viewName) - 1);
			}

			// RO
			else if (strcasecmp(command.part[tempInt], "ro") == 0)
				communityPointer->readonly = true;

			// RW
			else if (strcasecmp(command.part[tempInt], "rw") == 0)
				communityPointer->readonly = false;

			// IPV6
			else if (strcmp(command.part[tempInt], "ipv6") == 0)
				tempInt++;

			// ACL
			else
				strncpy(communityPointer->accessList, command.part[tempInt], sizeof(communityPointer->accessList) - 1);

			// Increment part pointer...
			tempInt++;
		}
	}

	// snmp trap?
	else if ((strcmp(command.part[tempInt], "enable") == 0) && (strcmp(command.part[tempInt+1], "traps") == 0))
	{
		tempInt += 2;

		// Is the first trap
		if (nipper->ios->snmp->trap == 0)
		{
			// Create...
			nipper->ios->snmp->trap = malloc(sizeof(struct snmpTrap));
			snmpTrapPointer = nipper->ios->snmp->trap;
		}
		else
		{
			// Find last trap
			snmpTrapPointer = nipper->ios->snmp->trap;
			while (snmpTrapPointer->next != 0)
				snmpTrapPointer = snmpTrapPointer->next;

			// Create...
			snmpTrapPointer->next = malloc(sizeof(struct snmpTrap));
			snmpTrapPointer = snmpTrapPointer->next;
		}

		// Init...
		memset(snmpTrapPointer, 0, sizeof(struct snmpTrap));

		// Get traps...
		sprintf(tempString, "%s", command.part[tempInt]);
		tempInt++;
		while (tempInt < command.parts)
		{
			if (strcmp(command.part[tempInt], "vrrp") != 0)
				sprintf(tempString, "%s %s", tempString, command.part[tempInt]);
			tempInt++;
		}
		strncpy(snmpTrapPointer->trap, tempString, sizeof(snmpTrapPointer->trap) - 1);
		snmpTrapPointer->enabled = setting;
	}

	// snmp host?
	else if (strcmp(command.part[tempInt], "host") == 0)
	{
		tempInt++;

		// First host...
		if (nipper->ios->snmp->host == 0)
		{
			// Create...
			nipper->ios->snmp->host = malloc(sizeof(struct snmpHost));
			snmpHostPointer = nipper->ios->snmp->host;
		}
		else
		{
			// Find last host...
			snmpHostPointer = nipper->ios->snmp->host;
			while (snmpHostPointer->next != 0)
				snmpHostPointer = snmpHostPointer->next;

			// Create...
			snmpHostPointer->next = malloc(sizeof(struct snmpHost));
			snmpHostPointer = snmpHostPointer->next;
		}

		// Init...
		memset(snmpHostPointer, 0, sizeof(struct snmpHost));
		snmpHostPointer->version = snmp1;
		snmpHostPointer->dictionary = false;
		snmpHostPointer->weak = false;

		// Host / IP
		strncpy(snmpHostPointer->host, command.part[tempInt], sizeof(snmpHostPointer->host) - 1);
		tempInt++;

		// Get remaining options and community string
		setting = false;
		while ((tempInt < command.parts) && (setting == false))
		{

			// VRF...
			if (strcmp(command.part[tempInt], "vrf") == 0)
				tempInt++;

			// TRAPS / INFORMS...
			else if ((strcmp(command.part[tempInt], "traps") == 0) || (strcmp(command.part[tempInt], "informs") == 0))
			{ }

			// SNMP version...
			else if (strcmp(command.part[tempInt], "version") == 0)
			{
				tempInt++;

				// Version 1
				if (strcmp(command.part[tempInt], "1") == 0)
					snmpHostPointer->version = snmp1;

				// Version 2c
				else if (strcmp(command.part[tempInt], "2c") == 0)
					snmpHostPointer->version = snmp2c;

				// Version 3
				else if (strcmp(command.part[tempInt], "3") == 0)
				{
					snmpHostPointer->version = snmp3_no_auth;

					// SNMP auth option
					if (strcmp(command.part[tempInt+1], "auth") == 0)
					{
						snmpHostPointer->version = snmp3_auth;
						tempInt++;
					}
					else if (strcmp(command.part[tempInt+1], "noauth") == 0)
					{
						snmpHostPointer->version = snmp3_no_auth;
						tempInt++;
					}
					else if (strcmp(command.part[tempInt+1], "priv") == 0)
					{
						snmpHostPointer->version = snmp3_priv;
						tempInt++;
					}
				}
			}

			else
			{
				setting = true;
				strncpy(snmpHostPointer->community, command.part[tempInt], sizeof(snmpHostPointer->host) - 1);
			}

			// Increment part pointer
			tempInt++;
		}

		// Check strength / dictionary
		if (simplePassword(snmpHostPointer->community, nipper) == true)
		{
			nipper->simplePasswords++;
			snmpHostPointer->dictionary = true;
		}
		if (passwordStrength(snmpHostPointer->community, nipper) == false)
		{
			nipper->passwordStrengths++;
			snmpHostPointer->weak = true;
		}
	}

	// SNMP Group...
	else if (strcmp(command.part[tempInt], "group") == 0)
	{
		tempInt++;

		// If this is the first...
		if (nipper->ios->snmp->group == 0)
		{
			// Create...
			nipper->ios->snmp->group = malloc(sizeof(struct snmpGroup));
			snmpGroupPointer = nipper->ios->snmp->group;
		}
		else
		{
			// Find last group...
			snmpGroupPointer = nipper->ios->snmp->group;
			while (snmpGroupPointer->next != 0)
				snmpGroupPointer = snmpGroupPointer->next;

			// Create...
			snmpGroupPointer->next = malloc(sizeof(struct snmpGroup));
			snmpGroupPointer = snmpGroupPointer->next;
		}

		// Init...
		memset(snmpGroupPointer, 0, sizeof(struct snmpGroup));
		strcpy(snmpGroupPointer->readView, "MIB OID 1.3.6.1");

		// Group Name...
		strncpy(snmpGroupPointer->groupName, command.part[tempInt], sizeof(snmpGroupPointer->groupName) - 1);
		tempInt++;

		// Version...
		if (strcmp(command.part[tempInt], "v1") == 0)
			snmpGroupPointer->version = snmp1;
		else if (strcmp(command.part[tempInt], "v2c") == 0)
			snmpGroupPointer->version = snmp2c;
		else if (strcmp(command.part[tempInt], "v3") == 0)
		{
			tempInt++;
			if (strcmp(command.part[tempInt], "auth") == 0)
				snmpGroupPointer->version = snmp3_auth;
			else if (strcmp(command.part[tempInt], "noauth") == 0)
				snmpGroupPointer->version = snmp3_no_auth;
			else if (strcmp(command.part[tempInt], "priv") == 0)
				snmpGroupPointer->version = snmp3_priv;
		}
		tempInt++;

		// Get Options
		while (tempInt < command.parts)
		{
			// Read
			if (strcmp(command.part[tempInt], "read") == 0)
			{
				tempInt++;
				strncpy(snmpGroupPointer->readView, command.part[tempInt], sizeof(snmpGroupPointer->readView) - 1);
			}

			// Write
			else if (strcmp(command.part[tempInt], "write") == 0)
			{
				tempInt++;
				strncpy(snmpGroupPointer->writeView, command.part[tempInt], sizeof(snmpGroupPointer->writeView) - 1);
			}

			// Notify
			else if (strcmp(command.part[tempInt], "notify") == 0)
			{
				tempInt++;
				strncpy(snmpGroupPointer->notifyView, command.part[tempInt], sizeof(snmpGroupPointer->notifyView) - 1);
			}

			// Context
			else if (strcmp(command.part[tempInt], "context") == 0)
			{
				tempInt++;
				strncpy(snmpGroupPointer->context, command.part[tempInt], sizeof(snmpGroupPointer->context) - 1);
			}

			// ACL
			else if (strcmp(command.part[tempInt], "access") == 0)
			{
				tempInt++;
				if (strcmp(command.part[tempInt], "ipv6") == 0)
					tempInt += 2;
				strncpy(snmpGroupPointer->acl, command.part[tempInt], sizeof(snmpGroupPointer->acl) - 1);
			}

			// Increment part pointer
			tempInt++;
		}
	}

	// SNMP User...
	else if (strcmp(command.part[tempInt], "user") == 0)
	{
		tempInt++;

		// If this is the first user in the group
		if (nipper->ios->snmp->user == 0)
		{
			// Create...
			nipper->ios->snmp->user = malloc(sizeof(struct snmpUser));
			snmpUserPointer = nipper->ios->snmp->user;
		}
		else
		{
			// Find last group...
			snmpUserPointer = nipper->ios->snmp->user;
			while (snmpUserPointer->next != 0)
				snmpUserPointer = snmpUserPointer->next;

			// Create...
			snmpUserPointer->next = malloc(sizeof(struct snmpUser));
			snmpUserPointer = snmpUserPointer->next;
		}

		// Init...
		memset(snmpUserPointer, 0, sizeof(struct snmpUser));
		snmpUserPointer->encryption = false;
		snmpUserPointer->snmp3priv = snmp3_none;
		snmpUserPointer->snmp3auth = snmp3_none;

		// User
		strncpy(snmpUserPointer->userName, command.part[tempInt], sizeof(snmpUserPointer->userName) - 1);
		tempInt++;

		// Group
		strncpy(snmpUserPointer->groupName, command.part[tempInt], sizeof(snmpUserPointer->groupName) - 1);
		tempInt++;

		// Skip some options
		while ((tempInt < command.parts) && (strcmp(command.part[tempInt], "v1") != 0) && (strcmp(command.part[tempInt], "v2c") != 0) && (strcmp(command.part[tempInt], "v3") != 0))
			tempInt++;

		// SNMP version
		if (strcmp(command.part[tempInt], "v1") == 0)
			snmpUserPointer->version = snmp1;
		else if (strcmp(command.part[tempInt], "v2c") == 0)
			snmpUserPointer->version = snmp2c;
		else if (strcmp(command.part[tempInt], "v3") == 0)
			snmpUserPointer->version = snmp3_no_auth;
		tempInt++;

		while (tempInt < command.parts)
		{
			// Encrypted?
			if (strcmp(command.part[tempInt], "encrypted") == 0)
				snmpUserPointer->encryption = true;

			// Auth?
			else if (strcmp(command.part[tempInt], "auth") == 0)
			{
				snmpUserPointer->version = snmp3_auth;
				tempInt++;

				// Algo...
				if (strcmp(command.part[tempInt], "md5") == 0)
					snmpUserPointer->snmp3auth = snmp3_md5;
				else if (strcmp(command.part[tempInt], "sha") == 0)
					snmpUserPointer->snmp3auth = snmp3_sha;
				tempInt++;

				// Auth Password
				strncpy(snmpUserPointer->authPass, command.part[tempInt], sizeof(snmpUserPointer->authPass) - 1);
			}

			// Access?
			else if (strcmp(command.part[tempInt], "access") == 0)
			{
				tempInt++;

				// Check for ipv6
				if (strcmp(command.part[tempInt], "ipv6") == 0)
					tempInt +=2;

				// Check for Priv
				if (strcmp(command.part[tempInt], "priv") == 0)
				{
					snmpUserPointer->version = snmp3_priv;
					tempInt++;

					// Enc...
					if (strcmp(command.part[tempInt], "des") == 0)
						snmpUserPointer->snmp3priv = snmp3_des;
					else if (strcmp(command.part[tempInt], "3des") == 0)
						snmpUserPointer->snmp3priv = snmp3_3des;
					else if (strcmp(command.part[tempInt], "des56") == 0)
						snmpUserPointer->snmp3priv = snmp3_des56;
					else if (strcmp(command.part[tempInt], "aes") == 0)
					{
						tempInt++;
						if (strcmp(command.part[tempInt], "128") == 0)
							snmpUserPointer->snmp3priv = snmp3_aes128;
						else if (strcmp(command.part[tempInt], "192") == 0)
							snmpUserPointer->snmp3priv = snmp3_aes192;
						else if (strcmp(command.part[tempInt], "256") == 0)
							snmpUserPointer->snmp3priv = snmp3_aes256;
					}
					tempInt++;

					// Priv Password
					strncpy(snmpUserPointer->privPass, command.part[tempInt], sizeof(snmpUserPointer->privPass) - 1);
					tempInt++;
				}

				// ACL
				strncpy(snmpUserPointer->acl, command.part[tempInt], sizeof(snmpUserPointer->acl) - 1);
			}

			// Increment part pointer
			tempInt++;
		}
	}
}

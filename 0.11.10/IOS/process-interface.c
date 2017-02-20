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


#define rip_auth_default 0
#define rip_auth_text 1
#define rip_auth_md5 2
#define rip_auth_none 3
#define rip_auth_unknown 4

#define rip_version_default 0
#define rip_version1 1
#define rip_version2 2
#define rip_version1and2 3
#define rip_version_global 4

#define sp_mode_access 0
#define sp_mode_trunk 1
#define sp_mode_dynamic 2
#define sp_mode_dot1qtunnel 3
#define sp_mode_pvlan_host 4
#define sp_mode_pvlan_promiscuous 5

#define sp_violation_shutdown 0
#define sp_violation_restrict 1
#define sp_violation_protect 2

#define ospf_default 0
#define ospf_broadcast 1
#define ospf_nonbroadcast 2
#define ospf_p2p 3
#define ospf_p2multi 4
#define ospf_p2multinon 5

struct eigrpAutonStruct
{
	int autonomousNo;
	char keyChain[32];
	int md5Auth;					// true or false (default)
	int bandwidth;					// default is 50%
	int passive;					// true, false or unconfigured (default)
	struct eigrpAutonStruct *next;
};

struct bgpInterStruct
{
	int autonomousNo;
	int passive;					// true, false or unconfigured (default)
	struct bgpInterStruct *next;
};

struct ospfInterStruct
{
	int processID;
	int passive;					// true, false or unconfigured (default)
	struct ospfInterStruct *next;
};

#define vrrp_auth_none 0
#define vrrp_auth_text 1
#define vrrp_auth_md5 2

struct vrrpStruct
{
	int group;
	char description[81];
	int authentication;				// vrrp_auth_none (default)
	int keyChain;					// false (default) or true
	char authString[65];
	char authStringEnc[65];
	int weak;						// true or false (default)
	int dictionary;					// true or false (default)
	char ipAddress[32];
	char ipAddress2[32];
	int priorityLevel;				// 100 (default)
	int shutdown;					// true (default), false when ip address is configured.
	struct vrrpStruct *next;
};


struct interfaceConfig
{
	// Standard...
	char name[48];
	char description[128];
	char ipAddress[32];
	int shutdown;					// true, false

	// Interface Options...
	int proxyArp;					// true, false
	int ntp;						// true, false
	int mop;						// true, false
	int ipUnreachables;				// true, false
	int ipRedirects;				// true, false
	int ipMaskReply;				// true, false
	int ipDirectBroadcast;			// true, false, unconfigured
	int cdp;						// true, false
	int uRPF;						// true, false

	// Access Control Lists
	char accessGroupIn[65];
	char accessGroupOut[65];

	// Switchport
	int switchportMode;				// sp_mode_access...
	int switchportModePVLAN;		// sp_mode_pvlan_host...
	int switchportVLAN;				// VLAN number
	int switchportSecurity;			// true or false
	int switchportViolation;		// sp_violation_shutdown...

	// Routing Protocols...
	struct eigrpAutonStruct *eigrp;	// EIGRP
	struct vrrpStruct *vrrp;		// VRRP
	struct bgpInterStruct *bgp;		// BGP
	struct ospfInterStruct *ospf;	// OSPF

	// RIP Configuration...
	int ripAuthMode;				// rip_auth_default, rip_auth_text...
	char ripKeyChain[32];
	int ripSendVersion;				// rip_version1...
	int ripReceiveVersion;			// rip_version1...
	int ripTriggered;				// true or false (default)
	int ripV2Broadcast;				// true or false (default)
	int ripPassive;					// true, false, unconfigured (default)

	// OSPF Configuration...
	int ospfAuthentication;			// auth_none...
	char ospfKey[128];
	int ospfKeyEncryption;
	char ospfKeyEncrypted[128];
	int ospfDictionary;				// true, false
	int ospfWeak;					// true, false
	int ospfFloodReduction;			// true, false
	int ospfNetwork;				// ospf_broadcast...

	struct interfaceConfig *next;
};


// Returns pointer to vrrp struct
struct vrrpStruct *getVRRPPointer(struct interfaceConfig *interfacePointer, int groupId)
{
	// Variables
	struct vrrpStruct *vrrpPointer = 0;

	// No VRRP struct
	if (interfacePointer->vrrp == 0)
	{
		// create struct
		interfacePointer->vrrp = malloc(sizeof(struct vrrpStruct));
		// Pointers
		vrrpPointer = interfacePointer->vrrp;

		// Init VRRP config
		memset(vrrpPointer, 0, sizeof(struct vrrpStruct));
		vrrpPointer->group = groupId;
		vrrpPointer->authentication = vrrp_auth_none;
		vrrpPointer->keyChain = false;
		vrrpPointer->priorityLevel = 100;
		vrrpPointer->shutdown = true;
		vrrpPointer->weak = false;
		vrrpPointer->dictionary = false;
	}
	else
	{
		// Find
		vrrpPointer = interfacePointer->vrrp;
		while ((vrrpPointer->next != 0) && (vrrpPointer->group != groupId))
			vrrpPointer = vrrpPointer->next;
		if (vrrpPointer->group != groupId)
		{
			// Create struct
			vrrpPointer->next = malloc(sizeof(struct vrrpStruct));
			// Pointers
			vrrpPointer = vrrpPointer->next;

			// Init VRRP config
			memset(vrrpPointer, 0, sizeof(struct vrrpStruct));
			vrrpPointer->group = groupId;
			vrrpPointer->authentication = vrrp_auth_none;
			vrrpPointer->keyChain = false;
			vrrpPointer->priorityLevel = 100;
			vrrpPointer->shutdown = true;
			vrrpPointer->weak = false;
			vrrpPointer->dictionary = false;
		}
	}
	return vrrpPointer;
}


// Returns BGP Interface Config (creates a new one if it doesn't exist)
struct bgpInterStruct *bgpInterfaceConfig(struct interfaceConfig *interfacePointer, int autonomousNo)
{
	// Variables...
	struct bgpInterStruct *bgpInterPointer = 0;

	// If this is the first auth mode
	if (interfacePointer->bgp == 0)
	{
		interfacePointer->bgp = malloc(sizeof(struct bgpInterStruct));
		bgpInterPointer = interfacePointer->bgp;
		memset(bgpInterPointer, 0, sizeof(struct bgpInterStruct));
		bgpInterPointer->autonomousNo = autonomousNo;
		bgpInterPointer->passive = unconfigured;
	}

	// If this is not the first
	else
	{
		bgpInterPointer = interfacePointer->bgp;
		while ((bgpInterPointer->next != 0) && (autonomousNo != bgpInterPointer->autonomousNo))
			bgpInterPointer = bgpInterPointer->next;
		if (autonomousNo != bgpInterPointer->autonomousNo)
		{
			bgpInterPointer->next = malloc(sizeof(struct bgpInterStruct));
			bgpInterPointer = bgpInterPointer->next;
			memset(bgpInterPointer, 0, sizeof(struct bgpInterStruct));
			bgpInterPointer->autonomousNo = autonomousNo;
			bgpInterPointer->passive = unconfigured;
		}
	}

	return bgpInterPointer;
}


// Returns OSPF Interface Config (creates a new one if it doesn't exist)
struct ospfInterStruct *ospfInterfaceConfig(struct interfaceConfig *interfacePointer, int processID)
{
	// Variables...
	struct ospfInterStruct *ospfInterPointer = 0;

	// If this is the first auth mode
	if (interfacePointer->ospf == 0)
	{
		interfacePointer->ospf = malloc(sizeof(struct ospfInterStruct));
		ospfInterPointer = interfacePointer->ospf;
		memset(ospfInterPointer, 0, sizeof(struct ospfInterStruct));
		ospfInterPointer->processID = processID;
		ospfInterPointer->passive = unconfigured;
	}

	// If this is not the first
	else
	{
		ospfInterPointer = interfacePointer->ospf;
		while ((ospfInterPointer->next != 0) && (processID != ospfInterPointer->processID))
			ospfInterPointer = ospfInterPointer->next;
		if (processID != ospfInterPointer->processID)
		{
			ospfInterPointer->next = malloc(sizeof(struct ospfInterStruct));
			ospfInterPointer = ospfInterPointer->next;
			memset(ospfInterPointer, 0, sizeof(struct ospfInterStruct));
			ospfInterPointer->processID = processID;
			ospfInterPointer->passive = unconfigured;
		}
	}

	return ospfInterPointer;
}


// Returns EIGRP Interface Config (creates a new one if it doesn't exist)
struct eigrpAutonStruct *eigrpInterfaceConfig(struct interfaceConfig *interfacePointer, int autonomousNo)
{
	// Variables...
	struct eigrpAutonStruct *eigrpAutonPointer = 0;

	// If this is the first auth mode
	if (interfacePointer->eigrp == 0)
	{
		interfacePointer->eigrp = malloc(sizeof(struct eigrpAutonStruct));
		eigrpAutonPointer = interfacePointer->eigrp;
		memset(eigrpAutonPointer, 0, sizeof(struct eigrpAutonStruct));
		eigrpAutonPointer->autonomousNo = autonomousNo;
		eigrpAutonPointer->md5Auth = false;
		eigrpAutonPointer->passive = unconfigured;
		eigrpAutonPointer->bandwidth = 50;
	}

	// If this is not the first
	else
	{
		eigrpAutonPointer = interfacePointer->eigrp;
		while ((eigrpAutonPointer->next != 0) && (autonomousNo != eigrpAutonPointer->autonomousNo))
			eigrpAutonPointer = eigrpAutonPointer->next;
		if (autonomousNo != eigrpAutonPointer->autonomousNo)
		{
			eigrpAutonPointer->next = malloc(sizeof(struct eigrpAutonStruct));
			eigrpAutonPointer = eigrpAutonPointer->next;
			memset(eigrpAutonPointer, 0, sizeof(struct eigrpAutonStruct));
			eigrpAutonPointer->autonomousNo = autonomousNo;
			eigrpAutonPointer->md5Auth = false;
			eigrpAutonPointer->passive = unconfigured;
			eigrpAutonPointer->bandwidth = 50;
		}
	}

	return eigrpAutonPointer;
}


// Process Interface
void processInterface(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct interfaceConfig *interfacePointer = 0;
	struct eigrpAutonStruct *eigrpAutonPointer = 0;
	struct vrrpStruct *vrrpPointer = 0;
	struct ciscoCommand command;
	char tempString[nipper->maxSize];
	int setting = 0;
	int tempInt = 0;
	int partPointer = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Interface Line: %s\n", line);
	}

	// First interface
	if (nipper->ios->interface == 0)
	{
		// create struct
		nipper->ios->interface = malloc(sizeof(struct interfaceConfig));

		// Pointers
		interfacePointer = nipper->ios->interface;
	}
	else
	{
		// Find last interface
		interfacePointer = nipper->ios->interface;
		while (interfacePointer->next != 0)
			interfacePointer = interfacePointer->next;

		// Create struct
		interfacePointer->next = malloc(sizeof(struct interfaceConfig));

		// Pointers
		interfacePointer = interfacePointer->next;
	}

	// Init
	command = splitLine(line);
	memset(interfacePointer, 0, sizeof(struct interfaceConfig));
	if (command.parts == 2)
		strncpy(interfacePointer->name, command.part[1], sizeof(interfacePointer->name));
	else
	{
		if ((strcmp(command.part[2], "point-to-point") == 0) || (strcmp(command.part[2], "multipoint") == 0))
			sprintf(tempString, "%s %s", command.part[1], command.part[2]);
		else
			sprintf(tempString, "%s%s", command.part[1], command.part[2]);
		strncpy(interfacePointer->name, tempString, sizeof(interfacePointer->name) - 1);
	}
	strcpy(interfacePointer->ipAddress, "None");
	interfacePointer->proxyArp = true;
	interfacePointer->ntp = true;
	if ((strncmp(interfacePointer->name, "GigabitEthernet", 15) == 0) || (strncmp(interfacePointer->name, "FastEthernet", 12)) || (strncmp(interfacePointer->name, "Ethernet", 8) == 0))
		interfacePointer->mop = true;
	else
		interfacePointer->mop = false;
	interfacePointer->ipUnreachables = true;
	interfacePointer->ipRedirects = true;
	interfacePointer->ipMaskReply = false;
	if ((nipper->versionMajor < 11) || ((nipper->versionMajor == 11) && (nipper->versionMinor < 4)))
		interfacePointer->ipDirectBroadcast = true;
	else
		interfacePointer->ipDirectBroadcast = false;
	interfacePointer->cdp = true;
	interfacePointer->uRPF = false;
	interfacePointer->shutdown = false;
	interfacePointer->ripAuthMode = rip_auth_none;
	interfacePointer->ripSendVersion = rip_version_global;
	interfacePointer->ripReceiveVersion = rip_version_global;
	interfacePointer->ripTriggered = false;
	interfacePointer->ripV2Broadcast = false;
	interfacePointer->ripPassive = unconfigured;
	if (nipper->deviceType == type_ios_catalyst)
		interfacePointer->switchportMode = sp_mode_dynamic;
	else
		interfacePointer->switchportMode = sp_mode_access;
	interfacePointer->switchportVLAN = 1;
	interfacePointer->switchportSecurity = false;
	interfacePointer->switchportViolation = sp_violation_shutdown;
	interfacePointer->ospfAuthentication = auth_none;
	interfacePointer->ospfKeyEncryption = encrypt_none;
	interfacePointer->ospfDictionary = false;
	interfacePointer->ospfWeak = false;
	if ((nipper->versionMajor < 12) || ((nipper->versionMajor == 12) && (nipper->versionMinor < 1)))
		interfacePointer->ospfFloodReduction = false;
	else
		interfacePointer->ospfFloodReduction = unconfigured;
	interfacePointer->ospfNetwork = ospf_default;

	// Loop through the interface lines
	readLine(nipper->input, line, nipper->maxSize);
	while ((feof(nipper->input) == 0) && (line[0] == ' '))
	{
		// Debug
		if (nipper->debugMode == true)
		{
			printf("Interface Line: %s\n", line);
		}

		// Init
		command = splitLine(line);

		// If no
		if (strcmp(command.part[0], "no") == 0)
		{
			setting = false;
			partPointer = 1;
		}
		else
		{
			setting = true;
			partPointer = 0;
		}

		// Description
		if ((strcmp(command.part[0], "description") == 0) && (command.parts > 1))
		{
			int loop;
			strncpy(interfacePointer->description, command.part[1], sizeof(interfacePointer->description) - 1);
			tempString[0] = 0;
			for (loop = 2; loop < command.parts; loop++)
			{
				sprintf(tempString, "%s %s", interfacePointer->description, command.part[loop]);
				strncpy(interfacePointer->description, tempString, sizeof(interfacePointer->description) - 1);
			}
		}

		// IP
		else if (strcmp(command.part[partPointer], "ip") == 0)
		{
			partPointer++;

			// IP Address
			if ((strcmp(command.part[partPointer], "address") == 0) && (setting == true) && (command.parts > 2))
			{
				int loop;
				strncpy(interfacePointer->ipAddress, command.part[2], sizeof(interfacePointer->ipAddress) - 1);
				tempString[0] = 0;
				for (loop = 3; loop < command.parts; loop++)
				{
					sprintf(tempString, "%s %s", interfacePointer->ipAddress, command.part[loop]);
					strncpy(interfacePointer->ipAddress, tempString, sizeof(interfacePointer->ipAddress) - 1);
				}
			}

			// Access Group
			else if (strcmp(command.part[partPointer], "access-group") == 0)
			{
				// In
				if (strcmp(command.part[partPointer + 2], "in") == 0)
					strncpy(interfacePointer->accessGroupIn, command.part[partPointer + 1], sizeof(interfacePointer->accessGroupIn) -1);
				else if (strcmp(command.part[partPointer + 2], "out") == 0)
					strncpy(interfacePointer->accessGroupOut, command.part[partPointer + 1], sizeof(interfacePointer->accessGroupOut) -1);
			}

			// uRPF verification
			else if ((strcmp(command.part[partPointer], "verify") == 0) && (strcmp(command.part[partPointer+1], "unicast") == 0) && (strcmp(command.part[partPointer+2], "reverse-path") == 0))
				interfacePointer->uRPF = setting;

			// ARP Proxy
			else if (strcmp(command.part[partPointer], "proxy-arp") == 0)
				interfacePointer->proxyArp = setting;

			// IP Unreachables
			else if (strcmp(command.part[partPointer], "unreachables") == 0)
				interfacePointer->ipUnreachables = setting;

			// IP Redirects
			else if (strcmp(command.part[partPointer], "redirects") == 0)
				interfacePointer->ipRedirects = setting;

			// IP Mask-reply
			else if (strcmp(command.part[partPointer], "mask-reply") == 0)
				interfacePointer->ipMaskReply = setting;

			// IP Direct Broadcast
			else if (strcmp(command.part[partPointer], "directed-broadcast") == 0)
				interfacePointer->ipDirectBroadcast = setting;

			// EIGRP Key Chain
			else if ((strcmp(command.part[partPointer], "authentication") == 0) && (strcmp(command.part[partPointer+1], "key-chain") == 0) && (strcmp(command.part[partPointer+2], "eigrp") == 0))
			{
				// Get Pointer...
				eigrpAutonPointer = eigrpInterfaceConfig(interfacePointer, atoi(command.part[partPointer+3]));

				// Key Chain
				strncpy(eigrpAutonPointer->keyChain, command.part[partPointer+4], sizeof(eigrpAutonPointer->keyChain) - 1);
			}

			// EIGRP Authentication Mode
			else if ((strcmp(command.part[partPointer], "authentication") == 0) && (strcmp(command.part[partPointer+1], "mode") == 0) && (strcmp(command.part[partPointer+2], "eigrp") == 0))
			{
				// Get Pointer...
				eigrpAutonPointer = eigrpInterfaceConfig(interfacePointer, atoi(command.part[partPointer+3]));

				// Set MD5 Auth
				eigrpAutonPointer->md5Auth = true;
			}

			// EIGRP Bandwidth Percentage
			else if ((strcmp(command.part[partPointer], "bandwidth-percent") == 0) && (strcmp(command.part[partPointer+1], "eigrp") == 0))
			{
				// Get Pointer...
				eigrpAutonPointer = eigrpInterfaceConfig(interfacePointer, atoi(command.part[partPointer+2]));

				// Set Bandwidth
				eigrpAutonPointer->bandwidth = atoi(command.part[partPointer+3]);
			}

			// RIP Authentication
			else if (strcmp(command.part[partPointer], "rip") == 0)
			{
				partPointer++;

				// Authentication...
				if (strcmp(command.part[partPointer], "authentication") == 0)
				{
					partPointer++;

					// Mode
					if (strcmp(command.part[partPointer], "mode") == 0)
					{
						partPointer++;
						if (setting == false)
							interfacePointer->ripAuthMode = rip_auth_none;
						else if (strcmp(command.part[partPointer], "md5") == 0)
							interfacePointer->ripAuthMode = rip_auth_md5;
						else if (strcmp(command.part[partPointer], "text") == 0)
							interfacePointer->ripAuthMode = rip_auth_text;
						else
							interfacePointer->ripAuthMode = rip_auth_unknown;
					}

					// Key Chain
					else if (strcmp(command.part[partPointer], "key-chain") == 0)
					{
						strncpy(interfacePointer->ripKeyChain, command.part[partPointer + 1], sizeof(interfacePointer->ripAuthMode) - 1);
						if (interfacePointer->ripAuthMode == rip_auth_none)
							interfacePointer->ripAuthMode = rip_auth_text;
					}
				}

				// Triggered
				else if (strcmp(command.part[partPointer], "triggered") == 0)
					interfacePointer->ripTriggered = setting;

				// V2 Broadcast
				else if (strcmp(command.part[partPointer], "v2-broadcast") == 0)
					interfacePointer->ripV2Broadcast = setting;

				// Version...
				else if (strcmp(command.part[partPointer + 1], "version") == 0)
				{
					// Receive...
					if (strcmp(command.part[partPointer], "receive") == 0)
					{
						if (setting == true)
						{
							interfacePointer->ripReceiveVersion = rip_version_global;
							if (command.parts == 5)
							{
								if (strcmp(command.part[4], "1") == 0)
									interfacePointer->ripReceiveVersion = rip_version1;
								else
									interfacePointer->ripReceiveVersion = rip_version2;
							}
							else if (command.parts == 6)
								interfacePointer->ripReceiveVersion = rip_version1and2;
						}
						else
							interfacePointer->ripReceiveVersion = rip_version_default;
					}

					// Send
					else if (strcmp(command.part[partPointer], "send") == 0)
					{
						if (setting == true)
						{
							interfacePointer->ripSendVersion = rip_version_global;
							if (command.parts == 5)
							{
								if (strcmp(command.part[4], "1") == 0)
									interfacePointer->ripSendVersion = rip_version1;
								else
									interfacePointer->ripSendVersion = rip_version2;
							}
							else if (command.parts == 6)
								interfacePointer->ripSendVersion = rip_version1and2;
						}
						else
							interfacePointer->ripSendVersion = rip_version_default;
					}
				}
			}

			else if (strcmp(command.part[partPointer], "ospf") == 0)
			{
				// OSPF Clear-text Authentication
				if (strcmp(command.part[partPointer + 1], "authentication-key") == 0)
				{
					interfacePointer->ospfAuthentication = auth_clear;
					if (strcmp(command.part[partPointer + 2], "7") == 0)
					{
						strncpy(interfacePointer->ospfKeyEncrypted, command.part[partPointer + 3], sizeof(interfacePointer->ospfKeyEncrypted) - 1);
						interfacePointer->ospfKeyEncryption = encrypt_type7;
						if (password7(command.part[partPointer + 3], interfacePointer->ospfKey, sizeof(interfacePointer->ospfKey), nipper->debugMode) != 0)
							strcpy(interfacePointer->ospfKey, "<unknown>");
						if (simplePassword(interfacePointer->ospfKey, nipper) == true)
						{
							nipper->simplePasswords++;
							interfacePointer->ospfDictionary = true;
						}
						if (passwordStrength(interfacePointer->ospfKey, nipper) == false)
						{
							nipper->passwordStrengths++;
							interfacePointer->ospfWeak = true;
						}
					}
					else if (strcmp(command.part[partPointer + 2], "5") == 0)
					{
						strncpy(interfacePointer->ospfKeyEncrypted, command.part[partPointer + 3], sizeof(interfacePointer->ospfKeyEncrypted) - 1);
						interfacePointer->ospfKeyEncryption = encrypt_md5;
						strcpy(interfacePointer->ospfKey, "unknown");
					}
					else if (strcmp(command.part[partPointer + 2], "0") == 0)
					{
						strncpy(interfacePointer->ospfKey, command.part[partPointer + 3], sizeof(interfacePointer->ospfKey) - 1);
						if (simplePassword(interfacePointer->ospfKey, nipper) == true)
						{
							nipper->simplePasswords++;
							interfacePointer->ospfDictionary = true;
						}
						if (passwordStrength(interfacePointer->ospfKey, nipper) == false)
						{
							nipper->passwordStrengths++;
							interfacePointer->ospfWeak = true;
						}
					}
					else
					{
						strncpy(interfacePointer->ospfKey, command.part[partPointer + 2], sizeof(interfacePointer->ospfKey) - 1);
						if (simplePassword(interfacePointer->ospfKey, nipper) == true)
						{
							nipper->simplePasswords++;
							interfacePointer->ospfDictionary = true;
						}
						if (passwordStrength(interfacePointer->ospfKey, nipper) == false)
						{
							nipper->passwordStrengths++;
							interfacePointer->ospfWeak = true;
						}
					}
				}

				// OSPF MD5 Authentication
				else if (strcmp(command.part[partPointer + 1], "message-digest-key") == 0)
				{
					interfacePointer->ospfAuthentication = auth_md5;
					strncpy(interfacePointer->ospfKey, command.part[command.parts - 1], sizeof(interfacePointer->ospfKey) - 1);
					sprintf(tempString, "ospf-int-%s", interfacePointer->name);
						addJohnPassword(nipper, tempString, interfacePointer->ospfKey);
				}

				// OSPF Flood reduction
				else if (strcmp(command.part[partPointer + 1], "flood-reduction") == 0)
					interfacePointer->ospfFloodReduction = setting;

				// OSPF Network
				else if (strcmp(command.part[partPointer + 1], "network") == 0)
				{
					if (strcmp(command.part[partPointer + 2], "broadcast") == 0)
						interfacePointer->ospfNetwork = ospf_broadcast;
					else if (strcmp(command.part[partPointer + 2], "non-broadcast") == 0)
						interfacePointer->ospfNetwork = ospf_nonbroadcast;
					else if (strcmp(command.part[partPointer + 2], "point-to-point") == 0)
						interfacePointer->ospfNetwork = ospf_p2p;
					else if (strcmp(command.part[partPointer + 2], "point-to-multipoint") == 0)
					{
						interfacePointer->ospfNetwork = ospf_p2multi;
						if (command.parts > partPointer + 3)
						{
							if (strcmp(command.part[partPointer + 3], "non-broadcast") == 0)
								interfacePointer->ospfNetwork = ospf_p2multinon;
						}
					}
					if (setting == false)
						interfacePointer->ospfNetwork = ospf_default;
				}
			} 
		}

		// MOP
		else if ((strcmp(command.part[partPointer], "mop") == 0) && (strncmp(command.part[partPointer + 1], "enable", 6) == 0))
			interfacePointer->mop = setting;

		// CDP
		else if ((strcmp(command.part[partPointer], "cdp") == 0) && (strcmp(command.part[partPointer + 1], "enable") == 0))
			interfacePointer->cdp = setting;

		// NTP
		else if ((strcmp(command.part[0], "ntp") == 0) && (strcmp(command.part[1], "disable") == 0))
			interfacePointer->ntp = false;

		// Switchport Security Violation
		else if ((strcmp(command.part[0], "switchport") == 0) && (strcmp(command.part[1], "port-security") == 0) && (strcmp(command.part[2], "violation") == 0))
		{
			if (strcmp(command.part[3], "shutdown") == 0)
				interfacePointer->switchportViolation = sp_violation_shutdown;
			else if (strcmp(command.part[3], "restrict") == 0)
				interfacePointer->switchportViolation = sp_violation_restrict;
			else if (strcmp(command.part[3], "protect") == 0)
				interfacePointer->switchportViolation = sp_violation_protect;
		}

		// Switchport Security
		else if ((strcmp(command.part[partPointer], "switchport") == 0) && (strcmp(command.part[partPointer + 1], "port-security") == 0) && (command.parts == partPointer + 2))
			interfacePointer->switchportSecurity = setting;

		// Switchport Mode
		else if ((strcmp(command.part[0], "switchport") == 0) && (strcmp(command.part[1], "mode") == 0))
		{
			if (strcmp(command.part[2], "access") == 0)
				interfacePointer->switchportMode = sp_mode_access;
			else if (strcmp(command.part[2], "trunk") == 0)
				interfacePointer->switchportMode = sp_mode_trunk;
			else if (strcmp(command.part[2], "dynamic") == 0)
				interfacePointer->switchportMode = sp_mode_dynamic;
			else if (strcmp(command.part[2], "dot1q-tunnel") == 0)
				interfacePointer->switchportMode = sp_mode_dot1qtunnel;
			else if ((strcmp(command.part[2], "private-vlan") == 0) && (strcmp(command.part[3], "host") == 0))
				interfacePointer->switchportModePVLAN = sp_mode_pvlan_host;
			else if (strcmp(command.part[2], "private-vlan") == 0)
				interfacePointer->switchportModePVLAN = sp_mode_pvlan_promiscuous;
		}

		// Switchport VLAN
		else if ((strcmp(command.part[0], "switchport") == 0) && (strcmp(command.part[1], "access") == 0) && (strcmp(command.part[2], "vlan") == 0))
			interfacePointer->switchportVLAN = atoi(command.part[3]);

		// VRRP
		else if (strcmp(command.part[0], "vrrp") == 0)
		{
			// Get / Create VRRP Struct
			vrrpPointer = getVRRPPointer(interfacePointer, atoi(command.part[1]));

			// Authentication
			if (strcmp(command.part[2], "authentication") == 0)
			{
				// Text
				if (strcmp(command.part[3], "text") == 0)
				{
					vrrpPointer->authentication = vrrp_auth_text;
					strncpy(vrrpPointer->authString, command.part[4], sizeof(vrrpPointer->authString) -1);
				}

				// MD5
				else if (strcmp(command.part[3], "md5") == 0)
				{
					vrrpPointer->authentication = vrrp_auth_md5;
					if (strcmp(command.part[4], "key-chain") == 0)
					{
						vrrpPointer->keyChain = true;
						strncpy(vrrpPointer->authString, command.part[5], sizeof(vrrpPointer->authString) -1);
					}
					else if (strcmp(command.part[4], "key-string") == 0)
					{
						tempInt = 5;
						if (strcmp(command.part[5], "0") == 0)
							strncpy(vrrpPointer->authString, command.part[6], sizeof(vrrpPointer->authString) -1);
						else if (strcmp(command.part[5], "7") == 0)
						{
							strncpy(vrrpPointer->authStringEnc, command.part[5], sizeof(vrrpPointer->authStringEnc) -1);
							if (password7(vrrpPointer->authStringEnc, vrrpPointer->authString, sizeof(vrrpPointer->authString) - 1, nipper->debugMode) != 0)
							{
								strcpy(vrrpPointer->authString, "<unknown>");
								addJohnPassword(nipper, "VRRP", vrrpPointer->authStringEnc);
							}
						}
						else
							strncpy(vrrpPointer->authString, command.part[5], sizeof(vrrpPointer->authString) -1);
					}
				}

				// Text
				{
					vrrpPointer->authentication = vrrp_auth_text;
					strncpy(vrrpPointer->authString, command.part[3], sizeof(vrrpPointer->authString) -1);
				}

				// Check Passwords...
				if ((strcmp(vrrpPointer->authString, "<unknown>") != 0) && (strlen(vrrpPointer->authString) != 0) && (vrrpPointer->keyChain != true))
				{
					if (simplePassword(vrrpPointer->authString, nipper) == true)
					{
						nipper->simplePasswords++;
						vrrpPointer->dictionary = true;
					}
					if (passwordStrength(vrrpPointer->authString, nipper) == false)
					{
						nipper->passwordStrengths++;
						vrrpPointer->weak = true;
					}
				}
			}

			// Description
			else if (strcmp(command.part[2], "description") == 0)
			{
				if (command.parts == 4)
					strncpy(vrrpPointer->description, command.part[3], sizeof(vrrpPointer->description) -1);
				else
				{
					strcpy(tempString, command.part[3]);
					tempInt = 4;
					while (tempInt < command.parts)
					{
						sprintf(tempString, "%s %s", tempString, command.part[tempInt]);
						tempInt++;
					}
					strncpy(vrrpPointer->description, tempString, sizeof(vrrpPointer->description) -1);
				}
			}

			// IP
			else if (strcmp(command.part[2], "ip") == 0)
			{
				vrrpPointer->shutdown = false;
				if (command.parts == 5)
					strncpy(vrrpPointer->ipAddress2, command.part[3], sizeof(vrrpPointer->ipAddress2) -1);
				else
					strncpy(vrrpPointer->ipAddress, command.part[3], sizeof(vrrpPointer->ipAddress) -1);
			}

			// Priority Level
			else if (strcmp(command.part[2], "priority") == 0)
				vrrpPointer->priorityLevel = atoi(command.part[3]);

			// shutdown
			else if (strcmp(command.part[2], "shutdown") == 0)
				vrrpPointer->shutdown = true;
		}

		// Shutdown
		else if (strcmp(command.part[0], "shutdown") == 0)
			interfacePointer->shutdown = true;

		// Read next line
		readLine(nipper->input, line, nipper->maxSize);
	}
}


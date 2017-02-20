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

struct passiveStruct
{
	char interface[32];
	int passive;
	struct passiveStruct *next;
};

struct ripConfig
{
	int version;
	int autoSummary;
	int defaultRoute;
	char defaultRouteMap[57];
	int defaultMetric;
	int inputQueue;
	int outputDelay;
	int validateUpdateSource;
	int defaultPassive;
	struct host *neighbor;
	struct host *network;
	struct passiveStruct *passive;
};

struct ospfNetworkConfig
{
	char	network[16];
	char	networkMask[16];
	char	areaID[16];
	struct ospfNetworkConfig *next;
};

struct ospfAreaConfig
{
	char	areaID[16];
	int		areaAuth;
	int		defaultCost;
	struct ospfAreaConfig *next;
};

struct ospfNeighbor
{
	char	host[16];
	int		priority;
	int		pollInterval;
	int		costNumber;
	int		databaseFilter;
	struct ospfNeighbor *next;
};

struct ospfConfig
{
	int processID;
	int defaultPassive;
	struct passiveStruct *passive;
	struct ospfNetworkConfig *ospfNetwork;
	struct ospfAreaConfig *ospfArea;
	struct ospfNeighbor *neighbor;
	struct ospfConfig *next;
};

struct isisConfig
{
};

#define eigrp_stub_disabled 0
#define eigrp_stub_enabled 1
#define eigrp_stub_receive 2
#define eigrp_stub_connected 3
#define eigrp_stub_static 4
#define eigrp_stub_summary 5
#define eigrp_stub_redist 6

struct eigrpNeighbor
{
	char ipAddress[32];
	char interface[32];
	struct eigrpNeighbor *next;
};

struct eigrpNetwork
{
	char ipAddress[32];
	char netMask[32];
	struct eigrpNetwork *next;
};

struct eigrpConfig
{
	int process;					// EIGRP Autonomous No.
	char routerId[32];				// If not set, it is automatic
	int maximumHops;				// default is 100
	int stub;						// default is eigrp_stub_disabled
	int autoSummary;				// true or false (default)
	int internalDistance;			// default 90
	int externalDistance;			// default 170
	int logNeighborChanges;			// true (default) or false
	int logNeighborWarnings;		// true (default) or false
	int defaultPassive;				// false (default)
	struct passiveStruct *passive;
	struct eigrpNetwork *network;
	struct eigrpNeighbor *neighbor;
	struct eigrpConfig *next;
};

struct bgpNeighbor
{
	char host[32];
	int encryption;					// encrypt_type7, encrypt_md5...
	char password[128];
	char passwordEncrypted[128];
	int dictionary;
	int weak;
	char description[128];
	int autonomousNo;
	int ttlHops;
	struct bgpNeighbor *next;
};

struct bgpConfig
{
	int autonomousNo;
	int logNeighborChanges;
	int dampening;
	int defaultPassive;
	struct passiveStruct *passive;
	struct bgpNeighbor *neighbor;
	struct bgpConfig *next;
};

struct staticRoute
{
	char ipAddress[20];
	char netMask[16];
	char gateway[20];
	struct staticRoute *next;
};


// Process Static Route
void processRoute(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct ciscoCommand command;
	struct staticRoute *routePointer = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Static Route Line: %s\n", line);
	}

	// If first?
	if (nipper->ios->route == 0)
	{
		nipper->ios->route = malloc(sizeof(struct staticRoute));
		routePointer = nipper->ios->route;
	}
	else
	{
		routePointer = nipper->ios->route;
		while (routePointer->next != 0)
			routePointer = routePointer->next;
		routePointer->next = malloc(sizeof(struct staticRoute));
		routePointer = routePointer->next;
	}

	//init
	command = splitLine(line);
	memset(routePointer, 0, sizeof(struct staticRoute));

	// IP Address
	strncpy(routePointer->ipAddress, command.part[2], sizeof(routePointer->ipAddress) - 1);

	// Net Mask
	strncpy(routePointer->netMask, command.part[3], sizeof(routePointer->netMask) - 1);

	// Gateway
	strncpy(routePointer->gateway, command.part[4], sizeof(routePointer->gateway) - 1);
}


// Process Router
void processRouter(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct ciscoCommand command;
	struct bgpNeighbor *neighborPointer = 0;
	struct ospfNetworkConfig *ospfNetworkPointer = 0;
	struct ospfAreaConfig *ospfAreaPointer = 0;
	struct ospfNeighbor *ospfNeighborPointer = 0;
	struct ospfConfig *ospfPointer = 0;
	struct host *hostPointer = 0;
	struct passiveStruct *passivePointer = 0;
	struct eigrpConfig *eigrpPointer = 0;
	struct eigrpNetwork *eigrpNetworkPointer = 0;
	struct eigrpNeighbor *eigrpNeighborPointer = 0;
	struct bgpConfig *bgpPointer = 0;
	fpos_t filePosition;
	char tempString[nipper->maxSize];
	int tempInt = 0;
	int setting = 0;

	// Debug
	if (nipper->debugMode == true)
	{
		printf("Router Line: %s\n", line);
	}

	//init
	command = splitLine(line);

	// What type of routing protocol was it?
	// ISIS
	if (strncmp(line+7, "isis", 4) == 0)
	{
		readLine(nipper->input, line, nipper->maxSize);
		while ((feof(nipper->input) == 0) && (line[0] == ' '))
		{
			// Debug
			if (nipper->debugMode == true)
			{
				printf("ISIS Router Line: %s\n", line);
			}

			// Get next
			readLine(nipper->input, line, nipper->maxSize);
		}
	}

	// EIGRP
	else if (strcmp(command.part[1], "eigrp") == 0)
	{
		// if struct doesn't exist
		if (nipper->ios->eigrp == 0)
		{
			nipper->ios->eigrp = malloc(sizeof(struct eigrpConfig));
			eigrpPointer = nipper->ios->eigrp;
		}
		else
		{
			eigrpPointer = nipper->ios->eigrp;
			while (eigrpPointer->next != 0)
				eigrpPointer = eigrpPointer->next;
			eigrpPointer->next = malloc(sizeof(struct eigrpConfig));
			eigrpPointer = eigrpPointer->next;
		}

		// Init
		memset(nipper->ios->eigrp, 0, sizeof(struct eigrpConfig));
		strcpy(eigrpPointer->routerId, "Automatic");
		eigrpPointer->maximumHops = 100;
		eigrpPointer->stub = eigrp_stub_disabled;
		eigrpPointer->autoSummary = false;
		eigrpPointer->internalDistance = 90;
		eigrpPointer->externalDistance = 170;
		eigrpPointer->logNeighborChanges = true;
		eigrpPointer->logNeighborWarnings = true;
		eigrpPointer->defaultPassive = false;

		// Process ID
		if (command.parts == 3)
			eigrpPointer->process = atoi(command.part[2]);

		// Get Routing options...
		readLine(nipper->input, line, nipper->maxSize);
		while ((line[0] != '!') && (feof(nipper->input) == 0))
		{
			// Debug...
			if (nipper->debugMode == true)
				printf("EIGRP Router Line: %s\n", line);

			// Init...
			command = splitLine(line);

			// Setting
			if (strcmp(command.part[0], "no") == 0)
			{
				setting = false;
				tempInt = 1;
			}
			else
			{
				setting = true;
				tempInt = 0;
			}

			// Auto Summary
			if (strcmp(command.part[tempInt], "auto-summary") == 0)
				eigrpPointer->autoSummary = setting;

			// Default Passive Interface
			else if ((strcmp(command.part[0], "passive-interface") == 0) && (strcmp(command.part[1], "default") == 0))
				eigrpPointer->defaultPassive = true;

			// Passive
			else if (strcmp(command.part[tempInt], "passive-interface") == 0)
			{
				tempInt++;
				// If first passive interface...
				if (eigrpPointer->passive == 0)
				{
					eigrpPointer->passive = malloc(sizeof(struct passiveStruct));
					memset(eigrpPointer->passive, 0, sizeof(struct passiveStruct));
					passivePointer = eigrpPointer->passive;
				}
				else
				{
					passivePointer = eigrpPointer->passive;
					while (passivePointer->next != 0)
						passivePointer = passivePointer->next;
					passivePointer->next = malloc(sizeof(struct passiveStruct));
					memset(passivePointer->next, 0, sizeof(struct passiveStruct));
					passivePointer = passivePointer->next;
				}
				passivePointer->passive = setting;
				if (tempInt + 1 == command.parts)
					strncpy(passivePointer->interface, command.part[tempInt], sizeof(passivePointer->interface) - 1);
				else
				{
					sprintf(tempString, "%s%s", command.part[tempInt], command.part[tempInt+1]);
					strncpy(passivePointer->interface, tempString, sizeof(passivePointer->interface) - 1);
				}
			}

			// Administrative Distances
			else if ((strcmp(command.part[tempInt], "distance") == 0) && (strcmp(command.part[tempInt+1], "eigrp") == 0))
			{
				if (setting == false)
				{
					eigrpPointer->internalDistance = atoi(command.part[tempInt+2]);
					eigrpPointer->externalDistance = atoi(command.part[tempInt+3]);
				}
				else
				{
					eigrpPointer->internalDistance = 90;
					eigrpPointer->externalDistance = 170;
				}
			}

			// Log Neighbor Changes
			else if ((strcmp(command.part[tempInt], "eigrp") == 0) && (strcmp(command.part[tempInt+1], "log-neighbor-changes") == 0))
				eigrpPointer->logNeighborChanges = setting;

			// Log Neighbor Warnings
			else if ((strcmp(command.part[tempInt], "eigrp") == 0) && (strcmp(command.part[tempInt+1], "log-neighbor-warnings") == 0))
				eigrpPointer->logNeighborWarnings = setting;

			// Router ID
			else if ((strcmp(command.part[tempInt], "eigrp") == 0) && (strcmp(command.part[tempInt+1], "router-id") == 0))
				strncpy(eigrpPointer->routerId, command.part[tempInt+2], sizeof(eigrpPointer->routerId) - 1);

			// Stub
			else if ((strcmp(command.part[tempInt], "eigrp") == 0) && (strcmp(command.part[tempInt+1], "router-id") == 0))
			{
				if (setting == false)
					eigrpPointer->stub = eigrp_stub_disabled;
				else
				{
					eigrpPointer->stub = eigrp_stub_enabled;
					if (command.parts > 2)
					{
						if (strcmp(command.part[tempInt+2], "receive-only") == 0)
							eigrpPointer->stub = eigrp_stub_receive;
						else if (strcmp(command.part[tempInt+2], "connected") == 0)
							eigrpPointer->stub = eigrp_stub_connected;
						else if (strcmp(command.part[tempInt+2], "static") == 0)
							eigrpPointer->stub = eigrp_stub_static;
						else if (strcmp(command.part[tempInt+2], "summary") == 0)
							eigrpPointer->stub = eigrp_stub_summary;
						else if (strcmp(command.part[tempInt+2], "redistribted") == 0)
							eigrpPointer->stub = eigrp_stub_redist;
					}
				}
			}

			// Maximum Hops
			else if ((strcmp(command.part[tempInt], "metric") == 0) && (strcmp(command.part[tempInt+1], "maximum-hops") == 0))
			{
				if (setting == false)
					eigrpPointer->maximumHops = 100;
				else
					eigrpPointer->maximumHops = atoi(command.part[tempInt+2]);
			}

			// Neighbor
			else if (strcmp(command.part[tempInt], "neighbor") == 0)
			{
				tempInt++;

				// Create struct
				if (eigrpPointer->neighbor == 0)
				{
					eigrpPointer->neighbor = malloc(sizeof(struct eigrpNeighbor));
					eigrpNeighborPointer = eigrpPointer->neighbor;
				}
				else
				{
					eigrpNeighborPointer = eigrpPointer->neighbor;
					while (eigrpNeighborPointer->next != 0)
						eigrpNeighborPointer = eigrpNeighborPointer->next;
					eigrpNeighborPointer->next = malloc(sizeof(struct eigrpNeighbor));
					eigrpNeighborPointer = eigrpNeighborPointer->next;
				}

				// Init
				memset(eigrpNeighborPointer, 0, sizeof(struct eigrpNeighbor));

				// IP Address
				strncpy(eigrpNeighborPointer->ipAddress, command.part[tempInt], sizeof(eigrpNeighborPointer->ipAddress) - 1);
				tempInt++;

				// Interface
				if (command.parts == tempInt + 1)
					strncpy(eigrpNeighborPointer->interface, command.part[tempInt], sizeof(eigrpNeighborPointer->interface) - 1);
				else if (command.parts == tempInt + 2)
				{
					sprintf(tempString, "%s%s", command.part[tempInt], command.part[tempInt+1]);
					strncpy(eigrpNeighborPointer->interface, tempString, sizeof(eigrpNeighborPointer->interface) - 1);
				}
			}

			// Network
			else if (strcmp(command.part[tempInt], "network") == 0)
			{
				tempInt++;

				// Create struct
				if (eigrpPointer->network == 0)
				{
					eigrpPointer->network = malloc(sizeof(struct eigrpNetwork));
					eigrpNetworkPointer = eigrpPointer->network;
				}
				else
				{
					eigrpNetworkPointer = eigrpPointer->network;
					while (eigrpNetworkPointer->next != 0)
						eigrpNetworkPointer = eigrpNetworkPointer->next;
					eigrpNetworkPointer->next = malloc(sizeof(struct eigrpNetwork));
					eigrpNetworkPointer = eigrpNetworkPointer->next;
				}

				// Init
				memset(eigrpNetworkPointer, 0, sizeof(struct eigrpNetwork));

				// IP Address
				strncpy(eigrpNetworkPointer->ipAddress, command.part[tempInt], sizeof(eigrpNetworkPointer->ipAddress) - 1);
				tempInt++;

				// Netmask
				if (tempInt < command.parts)
					strncpy(eigrpNetworkPointer->netMask, command.part[tempInt], sizeof(eigrpNetworkPointer->netMask) - 1);
			}

			// Get next line...
			fgetpos(nipper->input, &filePosition);
			readLine(nipper->input, line, nipper->maxSize);
		}

		// Set to previous position...
		fsetpos(nipper->input, &filePosition);
	}

	// BGP
	else if (strncmp(line+7, "bgp", 3) == 0)
	{
		// If struct doesn't exist
		if (nipper->ios->bgp == 0)
		{
			nipper->ios->bgp = malloc(sizeof(struct bgpConfig));
			memset(nipper->ios->bgp, 0, sizeof(struct bgpConfig));
			bgpPointer = nipper->ios->bgp;
		}
		else
		{
			bgpPointer = nipper->ios->bgp;
			while (bgpPointer->next != 0)
				bgpPointer = bgpPointer->next;
			bgpPointer->next = malloc(sizeof(struct bgpConfig));
			memset(bgpPointer->next, 0, sizeof(struct bgpConfig));
			bgpPointer = bgpPointer->next;
		}

		// Init
		bgpPointer->autonomousNo = atoi(command.part[2]);
		bgpPointer->logNeighborChanges = false;
		bgpPointer->dampening = false;
		bgpPointer->defaultPassive = false;

		readLine(nipper->input, line, nipper->maxSize);
		while ((feof(nipper->input) == 0) && (line[0] == ' '))
		{
			// Debug
			if (nipper->debugMode == true)
				printf("BGP Router Line: %s\n", line);

			// Init
			command = splitLine(line);

			// Setting
			if (strcmp(command.part[0], "no") == 0)
			{
				setting = false;
				tempInt = 1;
			}
			else
			{
				setting = true;
				tempInt = 0;
			}

			if (strcmp(command.part[0], "neighbor") == 0)
			{
				// If this is the first neighbor
				if (bgpPointer->neighbor == 0)
				{
					neighborPointer = malloc(sizeof(struct bgpNeighbor));
					memset(neighborPointer, 0, sizeof(struct bgpNeighbor));

					// Init
					bgpPointer->neighbor = neighborPointer;
					strncpy(neighborPointer->host, command.part[1], sizeof(neighborPointer->host));
					neighborPointer->encryption = encrypt_none;
					neighborPointer->autonomousNo = -1;
					neighborPointer->ttlHops = -1;
					neighborPointer->weak = false;
					neighborPointer->dictionary = false;
				}

				// neighbors already exist
				else
				{
					// Search
					neighborPointer = bgpPointer->neighbor;
					while ((neighborPointer->next != 0) && (strcmp(command.part[1], neighborPointer->host) != 0))
						neighborPointer = neighborPointer->next;

					// If not found
					if (strcmp(command.part[1], neighborPointer->host) != 0)
					{
						neighborPointer->next = malloc(sizeof(struct bgpNeighbor));
						memset(neighborPointer->next, 0, sizeof(struct bgpNeighbor));

						// Sort out pointers
						neighborPointer = neighborPointer->next;

						// Init
						strncpy(neighborPointer->host, command.part[1], sizeof(neighborPointer->host));
						neighborPointer->encryption = encrypt_none;
						neighborPointer->autonomousNo = -1;
						neighborPointer->ttlHops = -1;
						neighborPointer->weak = false;
						neighborPointer->dictionary = false;
					}
				}

				if (command.parts > 2)
				{
					// Description?
					if (strncmp(command.part[2], "description", 11) == 0)
					{
						int loop;
						strncpy(neighborPointer->description, command.part[3], sizeof(neighborPointer->description));
						tempString[0] = 0;
						for (loop = 4; loop < command.parts; loop++)
						{
							sprintf(tempString, "%s %s", neighborPointer->description, command.part[loop]);
							strncpy(neighborPointer->description, tempString, sizeof(neighborPointer->description));
						}
					}

					// Password?
					else if (strncmp(command.part[2], "password", 8) == 0)
					{
						switch(command.part[3][0])
						{
							case '7':
								neighborPointer->encryption = encrypt_type7;
								if (password7(command.part[4], neighborPointer->password, sizeof(neighborPointer->password), nipper->debugMode) != 0)
									strcpy(neighborPointer->password, "<unknown>");
								strncpy(neighborPointer->passwordEncrypted, command.part[4], sizeof(neighborPointer->passwordEncrypted));
								break;
							case '5':
								neighborPointer->encryption = encrypt_md5;
								strcpy(neighborPointer->password, "<unknown>");
								strncpy(neighborPointer->passwordEncrypted, command.part[4], sizeof(neighborPointer->passwordEncrypted));
								addJohnPassword(nipper, "bgp", neighborPointer->passwordEncrypted);
								break;
							case '0':
								neighborPointer->encryption = encrypt_none;
								strncpy(neighborPointer->password, command.part[4], sizeof(neighborPointer->password));
								strcpy(neighborPointer->passwordEncrypted, "");
								break;
							default:
								if (command.parts == 3)
								{
									neighborPointer->encryption = encrypt_none;
									strncpy(neighborPointer->password, command.part[3], sizeof(neighborPointer->password));
									strcpy(neighborPointer->passwordEncrypted, "");
								}
								else
								{
									neighborPointer->encryption = encrypt_unknown;
									strcpy(neighborPointer->password, "<unknown>");
									strncpy(neighborPointer->passwordEncrypted, command.part[command.parts - 1], sizeof(neighborPointer->passwordEncrypted));
								}
								break;
						}
						if ((strcmp(neighborPointer->password, "<unknown>") != 0) && (strlen(neighborPointer->password) != 0))
						{
							if (simplePassword(neighborPointer->password, nipper) == true)
							{
								nipper->simplePasswords++;
								neighborPointer->dictionary = true;
							}
							if (passwordStrength(neighborPointer->password, nipper) == false)
							{
								nipper->passwordStrengths++;
								neighborPointer->weak = true;
							}
						}
					}

					// Autonomous No?
					else if (strncmp(command.part[2], "remote-as", 9) == 0)
						neighborPointer->autonomousNo = atoi(command.part[3]);

					// TTL Hops?
					else if ((strncmp(command.part[2], "ttl-security", 12) == 0) && (strncmp(command.part[3], "hops", 4) == 0))
						neighborPointer->ttlHops = atoi(command.part[4]);
				}
			}

			// Default Passive Interface
			else if ((strcmp(command.part[0], "passive-interface") == 0) && (strcmp(command.part[1], "default") == 0))
				bgpPointer->defaultPassive = true;

			// Passive
			else if (strcmp(command.part[tempInt], "passive-interface") == 0)
			{
				tempInt++;
				// If first passive interface...
				if (bgpPointer->passive == 0)
				{
					bgpPointer->passive = malloc(sizeof(struct passiveStruct));
					memset(bgpPointer->passive, 0, sizeof(struct passiveStruct));
					passivePointer = bgpPointer->passive;
				}
				else
				{
					passivePointer = bgpPointer->passive;
					while (passivePointer->next != 0)
						passivePointer = passivePointer->next;
					passivePointer->next = malloc(sizeof(struct passiveStruct));
					memset(passivePointer->next, 0, sizeof(struct passiveStruct));
					passivePointer = passivePointer->next;
				}
				passivePointer->passive = setting;
				if (tempInt + 1 == command.parts)
					strncpy(passivePointer->interface, command.part[tempInt], sizeof(passivePointer->interface) - 1);
				else
				{
					sprintf(tempString, "%s%s", command.part[tempInt], command.part[tempInt+1]);
					strncpy(passivePointer->interface, tempString, sizeof(passivePointer->interface) - 1);
				}
			}

			else if ((strcmp(command.part[0], "bgp") == 0) && (strcmp(command.part[1], "log-neighbor-changes") == 0))
				bgpPointer->logNeighborChanges = true;

			else if ((strcmp(command.part[0], "bgp") == 0) && (strcmp(command.part[1], "dampening") == 0))
				bgpPointer->dampening = true;

			// Get next
			readLine(nipper->input, line, nipper->maxSize);
		}
	}

	// RIP
	else if (strcmp(command.part[1], "rip") == 0)
	{

		// If rip config doesn't exist...
		if (nipper->ios->rip == 0)
		{
			// Create...
			nipper->ios->rip = malloc(sizeof(struct ripConfig));

			// Init...
			memset(nipper->ios->rip, 0, sizeof(struct ripConfig));
			nipper->ios->rip->version = rip_version_default;
			nipper->ios->rip->autoSummary = true;
			nipper->ios->rip->defaultRoute = false;
			nipper->ios->rip->defaultMetric = -1;
			nipper->ios->rip->inputQueue = 50;
			nipper->ios->rip->defaultPassive = false;
		}

		// Get Routing options...
		readLine(nipper->input, line, nipper->maxSize);
		while ((line[0] != '!') && (feof(nipper->input) == 0))
		{
			// Debug...
			if (nipper->debugMode == true)
				printf("RIP Router Line: %s\n", line);

			// Init...
			command = splitLine(line);

			// Setting
			if (strcmp(command.part[0], "no") == 0)
			{
				setting = false;
				tempInt = 1;
			}
			else
			{
				setting = true;
				tempInt = 0;
			}

			// Auto Summary
			if (strcmp(command.part[tempInt], "auto-summary") == 0)
				nipper->ios->rip->autoSummary = setting;

			// Default Passive Interface
			else if ((strcmp(command.part[0], "passive-interface") == 0) && (strcmp(command.part[1], "default") == 0))
				nipper->ios->rip->defaultPassive = true;

			// Passive
			else if (strcmp(command.part[tempInt], "passive-interface") == 0)
			{
				tempInt++;
				// If first passive interface...
				if (nipper->ios->rip->passive == 0)
				{
					nipper->ios->rip->passive = malloc(sizeof(struct passiveStruct));
					memset(nipper->ios->rip->passive, 0, sizeof(struct passiveStruct));
					passivePointer = nipper->ios->rip->passive;
				}
				else
				{
					passivePointer = nipper->ios->rip->passive;
					while (passivePointer->next != 0)
						passivePointer = passivePointer->next;
					passivePointer->next = malloc(sizeof(struct passiveStruct));
					memset(passivePointer->next, 0, sizeof(struct passiveStruct));
					passivePointer = passivePointer->next;
				}
				passivePointer->passive = setting;
				if (tempInt + 1 == command.parts)
					strncpy(passivePointer->interface, command.part[tempInt], sizeof(passivePointer->interface) - 1);
				else
				{
					sprintf(tempString, "%s%s", command.part[tempInt], command.part[tempInt+1]);
					strncpy(passivePointer->interface, tempString, sizeof(passivePointer->interface) - 1);
				}
			}

			// Default Information Originate
			else if ((strcmp(command.part[0], "default-information") == 0) && (strcmp(command.part[1], "originate") == 0))
			{
				nipper->ios->rip->defaultRoute = true;
				if (command.parts > 2)
				{
					if (strcmp(command.part[2], "route-map") == 0)
					strncpy(nipper->ios->rip->defaultRouteMap, command.part[2], sizeof(nipper->ios->rip->defaultRouteMap) - 1);
				}
			}

			// Default Metric...
			else if (strcmp(command.part[tempInt], "default-metric") == 0)
			{
				if (setting == false)
					nipper->ios->rip->defaultMetric = -1;
				else
					nipper->ios->rip->defaultMetric = atoi(command.part[tempInt+1]);
			}

			// Input Queue...
			else if (strcmp(command.part[tempInt], "input-queue") == 0)
			{
				if (setting == false)
					nipper->ios->rip->inputQueue = -1;
				else
					nipper->ios->rip->inputQueue = atoi(command.part[tempInt+1]);
			}

			// Output Delay...
			else if (strcmp(command.part[tempInt], "output-delay") == 0)
			{
				if (setting == false)
					nipper->ios->rip->outputDelay = 0;
				else
					nipper->ios->rip->outputDelay = atoi(command.part[tempInt+1]);
			}

			// Validate Update Source
			else if (strcmp(command.part[tempInt], "validate-update-source") == 0)
				nipper->ios->rip->validateUpdateSource = setting;

			// Version
			else if (strcmp(command.part[tempInt], "version") == 0)
			{
				if (setting == false)
					nipper->ios->rip->version = rip_version_default;
				else if (strcmp(command.part[tempInt + 1], "1") == 0)
					nipper->ios->rip->version = rip_version1;
				else
					nipper->ios->rip->version = rip_version2;
			}

			// Neighbor
			else if (strcmp(command.part[tempInt], "neighbor") == 0)
			{
				tempInt++;
				if (nipper->ios->rip->neighbor == 0)
				{
					nipper->ios->rip->neighbor = malloc(sizeof(struct host));
					memset(nipper->ios->rip->neighbor, 0, sizeof(struct host));
					hostPointer = nipper->ios->rip->neighbor;
				}
				else
				{
					hostPointer = nipper->ios->rip->neighbor;
					while (hostPointer->next != 0)
						hostPointer = hostPointer->next;
					hostPointer->next = malloc(sizeof(struct host));
					memset(hostPointer->next, 0, sizeof(struct host));
					hostPointer = hostPointer->next;
				}
				strncpy(hostPointer->server, command.part[tempInt], sizeof(hostPointer->server) - 1);
			}

			// Network
			else if (strcmp(command.part[tempInt], "network") == 0)
			{
				tempInt++;
				if (nipper->ios->rip->network == 0)
				{
					nipper->ios->rip->network = malloc(sizeof(struct host));
					memset(nipper->ios->rip->network, 0, sizeof(struct host));
					hostPointer = nipper->ios->rip->network;
				}
				else
				{
					hostPointer = nipper->ios->rip->network;
					while (hostPointer->next != 0)
						hostPointer = hostPointer->next;
					hostPointer->next = malloc(sizeof(struct host));
					memset(hostPointer->next, 0, sizeof(struct host));
					hostPointer = hostPointer->next;
				}
				strncpy(hostPointer->server, command.part[tempInt], sizeof(hostPointer->server) - 1);
			}

			// Get next line...
			fgetpos(nipper->input, &filePosition);
			readLine(nipper->input, line, nipper->maxSize);
		}

		// Set to previous position...
		fsetpos(nipper->input, &filePosition);
	}

	// OSPF
	else if (strcmp(command.part[1], "ospf") == 0)
	{
		// Is first OSPF struct?
		if (nipper->ios->ospf == 0)
		{
			nipper->ios->ospf = malloc(sizeof(struct ospfConfig));
			ospfPointer = nipper->ios->ospf;
		}
		else
		{
			ospfPointer = nipper->ios->ospf;
			while (ospfPointer->next != 0)
				ospfPointer = ospfPointer->next;
			ospfPointer->next = malloc(sizeof(struct ospfConfig));
			ospfPointer = ospfPointer->next;
		}

		// Init...
		memset(ospfPointer, 0, sizeof(struct ospfConfig));
		ospfPointer->defaultPassive = false;
		ospfPointer->processID = atoi(command.part[2]);

		// Get Configuration...
		fgetpos(nipper->input, &filePosition);
		readLine(nipper->input, line, nipper->maxSize);
		while ((feof(nipper->input) == 0) && (line[0] == ' '))
		{
			// Debug
			if (nipper->debugMode == true)
			{
				printf("OSPF Router Line: %s\n", line);
			}

			// Init
			command = splitLine(line);

			// Setting
			if (strcmp(command.part[0], "no") == 0)
			{
				setting = false;
				tempInt = 1;
			}
			else
			{
				setting = true;
				tempInt = 0;
			}

			// Area
			if (strncmp(command.part[0], "area", 4) == 0)
			{
				// No area config exists...
				if (ospfPointer->ospfArea == 0)
				{
					ospfPointer->ospfArea = malloc(sizeof(struct ospfAreaConfig));
					ospfAreaPointer = ospfPointer->ospfArea;

					// Init
					memset(ospfAreaPointer, 0, sizeof(struct ospfAreaConfig));
					strncpy(ospfAreaPointer->areaID, command.part[1], sizeof(ospfAreaPointer->areaID));
					ospfAreaPointer->areaAuth = auth_none;
					ospfAreaPointer->defaultCost = 1;
				}
				else
				{
					// Search for the area...
					ospfAreaPointer = ospfPointer->ospfArea;
					while ((ospfAreaPointer->next != 0) && (strcmp(command.part[1], ospfAreaPointer->areaID) != 0))
						ospfAreaPointer = ospfAreaPointer->next;

					// If area doesn't exists, create...
					if (strcmp(command.part[1], ospfAreaPointer->areaID) != 0)
					{
						ospfAreaPointer->next = malloc(sizeof(struct ospfAreaConfig));
						ospfAreaPointer = ospfAreaPointer->next;

						// Init
						memset(ospfAreaPointer, 0, sizeof(struct ospfAreaConfig));
						strncpy(ospfAreaPointer->areaID, command.part[1], sizeof(ospfAreaPointer->areaID));
						ospfAreaPointer->areaAuth = auth_none;
						ospfAreaPointer->defaultCost = 1;
					}
				}

				// Is authentication?
				if (strcmp(command.part[2], "authentication") == 0)
				{
					ospfAreaPointer->areaAuth = auth_clear;

					// Is message digest used?
					if (command.parts > 3)
					{
						if (strcmp(command.part[3], "message-digest") == 0)
							ospfAreaPointer->areaAuth = auth_md5;
					}
				}

				// Is default cost?
				else if (strcmp(command.part[2], "default-cost") == 0)
					ospfAreaPointer->defaultCost = atoi(command.part[3]);
			}

			// Network
			else if (strncmp(command.part[0], "network", 7) == 0)
			{
				// Reserve memory
				if (ospfPointer->ospfNetwork == 0)
				{
					ospfPointer->ospfNetwork = malloc(sizeof(struct ospfNetworkConfig));
					ospfNetworkPointer = ospfPointer->ospfNetwork;
				}
				else
				{
					ospfNetworkPointer = ospfPointer->ospfNetwork;
					while (ospfNetworkPointer->next != 0)
						ospfNetworkPointer = ospfNetworkPointer->next;
					ospfNetworkPointer->next = malloc(sizeof(struct ospfNetworkConfig));
					ospfNetworkPointer = ospfNetworkPointer->next;
				}

				// Init
				memset(ospfNetworkPointer, 0, sizeof(struct ospfNetworkConfig));
				ospfNetworkPointer->next = 0;
				strncpy(ospfNetworkPointer->network, command.part[1], sizeof(ospfNetworkPointer->network));
				strncpy(ospfNetworkPointer->networkMask, command.part[2], sizeof(ospfNetworkPointer->networkMask));
				strncpy(ospfNetworkPointer->areaID, command.part[4], sizeof(ospfNetworkPointer->areaID));
			}

			// Neighbor
			else if (strncmp(command.part[0], "neighbor", 8) == 0)
			{
				// Reserve memory
				if (ospfPointer->neighbor == 0)
				{
					ospfPointer->neighbor = malloc(sizeof(struct ospfNeighbor));
					ospfNeighborPointer = ospfPointer->neighbor;
				}
				else
				{
					ospfNeighborPointer = ospfPointer->neighbor;
					while (ospfNeighborPointer->next != 0)
						ospfNeighborPointer = ospfNeighborPointer->next;
					ospfNeighborPointer->next = malloc(sizeof(struct ospfNeighbor));
					ospfNeighborPointer = ospfNeighborPointer->next;
				}

				// Init
				memset(ospfNeighborPointer, 0, sizeof(struct ospfNeighbor));
				ospfNeighborPointer->next = 0;
				strncpy(ospfNeighborPointer->host, command.part[1], sizeof(ospfNeighborPointer->host));
				ospfNeighborPointer->priority = 0;
				ospfNeighborPointer->pollInterval = 120;
				ospfNeighborPointer->costNumber = 0;
				ospfNeighborPointer->databaseFilter = false;

				for (tempInt = 2; tempInt < command.parts; tempInt = tempInt + 2)
				{
					if (strncmp(command.part[tempInt], "cost", 4) == 0)
						ospfNeighborPointer->costNumber = atoi(command.part[tempInt + 1]);

					else if (strncmp(command.part[tempInt], "priority", 8) == 0)
						ospfNeighborPointer->priority = atoi(command.part[tempInt + 1]);

					else if (strncmp(command.part[tempInt], "poll-interval", 13) == 0)
						ospfNeighborPointer->pollInterval = atoi(command.part[tempInt + 1]);

					else if ((strncmp(command.part[tempInt], "database-filter", 15) == 0) && (strncmp(command.part[tempInt + 1], "all", 3) == 0))
						ospfNeighborPointer->databaseFilter = true;
				}
			}

			// Default Passive Interface
			else if ((strcmp(command.part[0], "passive-interface") == 0) && (strcmp(command.part[1], "default") == 0))
				ospfPointer->defaultPassive = true;

			// Passive
			else if (strcmp(command.part[tempInt], "passive-interface") == 0)
			{
				tempInt++;
				// If first passive interface...
				if (ospfPointer->passive == 0)
				{
					ospfPointer->passive = malloc(sizeof(struct passiveStruct));
					memset(ospfPointer->passive, 0, sizeof(struct passiveStruct));
					passivePointer = ospfPointer->passive;
				}
				else
				{
					passivePointer = ospfPointer->passive;
					while (passivePointer->next != 0)
						passivePointer = passivePointer->next;
					passivePointer->next = malloc(sizeof(struct passiveStruct));
					memset(passivePointer->next, 0, sizeof(struct passiveStruct));
					passivePointer = passivePointer->next;
				}
				passivePointer->passive = setting;
				if (tempInt + 1 == command.parts)
					strncpy(passivePointer->interface, command.part[tempInt], sizeof(passivePointer->interface) - 1);
				else
				{
					sprintf(tempString, "%s%s", command.part[tempInt], command.part[tempInt+1]);
					strncpy(passivePointer->interface, tempString, sizeof(passivePointer->interface) - 1);
				}
			}

			// Get next line...
			fgetpos(nipper->input, &filePosition);
			readLine(nipper->input, line, nipper->maxSize);
		}

		// Set to previous position...
		fsetpos(nipper->input, &filePosition);
	}
}



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

#define sos_spoofing_off 0
#define sos_spoofing_interface 1
#define sos_spoofing_routing 2
#define sos_spoofing_zone 3

struct zoneSOS
{
	char name[32];						// Zone Name
	int id;								// Zone ID
	int vlan;							// L2 VLAN number
	int block;							// Intra Zone Blocking
	char pbr[32];						// Policy-based Routing
	char tunnel[32];					// The Tunnel out zone for this VPN zone
	int tcpReset;						// Send reset packets back when receiving nosync packets
	char vrouter[32];					// Bind the zone to a Virtual Router
	int dhcpRelay;						// Relay DHCP requests
	int reasembleForALG;				// Reasemble fragmented packets for the ALG

	// Firewall options on the zone...
	int alarmWithoutDrop;				// Generate an attack alarm, but do not drop
	int blockFrag;						// Block IP fragmentation attacks
	int activeX;						// Block ActiveX controls
	int java;							// Block Java
	int exe;							// Block Executables
	int zip;							// Block zip files
	int flagDrop;						// Detects incorrect flags and drops the packets
	long icmpFlood;						// Detect and drop ICMP floods (0 = off)
	int icmpFrag;						// Detect ICMP fragments
	int icmpLarge;						// Detect and drop large ICMP frames
	int ipBadOptions;					// Detect and drop bad IP options
	int ipSourceRoute;					// Detects and drops IP Source Route options
	int ipLooseSource;					// As above, but loose source (does not drop)
	int ipRecordRoute;					// Detect ip record route packets (not drop)
	int ipSecurityOption;				// Detect and record security option (not drop)
	int ipSpoofing;						// Detect and drop spoofing attacks
	int ipStream;						// Detect IP stream (not drop)
	int strictSource;					// Detect IP Strict Source (not drop)
	long ipSweep;						// Detects and prevents IP sweep attack (0 = off)
	int ipTimestamp;					// Detect and record timestamp packets
	int land;							// Detect and prevent land attacks
	int limitSessions;					// Limit no of sessions (default is 128)
	int malformedUrl;					// Detects and prevents malformed URL
	int pingOfDeath;					// Detects and rejects oversized/irregular ICMP
	long portScan;						// Detect and prevent port scan (0 = off)
	int synAckAck;						// Detect and prevent SYN ACK ACK attack
	int synFin;							// Detect illegal flags
	int synFlood;						// Detect and prevent SYN floods
	int synFrags;						// Detect and drop a SYN fragmentation attack
	int noFlag;							// Detects and drops packets with no flags set
	int tearDrop;						// Detect and block the tear drop attack
	int udpFlood;						// Detect and drop UDP floods
	int unknownProtocol;					// Detect and drop protocol numbers greater than 135
	int winNuke;						// Detect and modify Windows attack packets
	int onTunnel;						// Apply to a tunnel

	struct zoneSOS *next;
};


// Get / Create Zone
struct zoneSOS *getZonePointer(struct nipperConfig *nipper, char *zone)
{
	// Variables...
	struct zoneSOS *zonePointer = 0;
	int init = false;

	// If this is the first zone...
	if (nipper->sos->zone == 0)
	{
		nipper->sos->zone = malloc(sizeof(struct zoneSOS));
		zonePointer = nipper->sos->zone;
		init = true;
	}
	else
	{
		zonePointer = nipper->sos->zone;
		while ((zonePointer->next != 0) && (strcmp(zonePointer->name, zone) != 0))
			zonePointer = zonePointer->next;
		if (strcmp(zonePointer->name, zone) != 0)
		{
			zonePointer->next = malloc(sizeof(struct zoneSOS));
			zonePointer = zonePointer->next;
			init = true;
		}
	}

	// Init?
	if (init == true)
	{
		memset(zonePointer, 0, sizeof(struct zoneSOS));
		zonePointer->vlan = 0;
		zonePointer->block = false;
		zonePointer->tcpReset = false;
		if (strcasecmp(zone, "V1-Untrust") == 0)
			zonePointer->dhcpRelay = false;
		else
			zonePointer->dhcpRelay = true;
		strncpy(zonePointer->name, zone, sizeof(zonePointer->name) - 1);
		zonePointer->reasembleForALG = false;
		zonePointer->alarmWithoutDrop = false;	
		zonePointer->blockFrag = false;
		zonePointer->activeX = false;
		zonePointer->java = false;
		zonePointer->exe = false;
		zonePointer->zip = false;
		zonePointer->flagDrop = false;
		zonePointer->icmpFlood = 0;
		zonePointer->icmpFrag = false;
		zonePointer->icmpLarge = false;
		zonePointer->ipBadOptions = false;
		zonePointer->ipSourceRoute = false;
		zonePointer->ipLooseSource = false;
		zonePointer->ipRecordRoute = false;
		zonePointer->ipSecurityOption = false;
		zonePointer->ipSpoofing = sos_spoofing_off;
		zonePointer->ipStream = false;
		zonePointer->strictSource = false;
		zonePointer->ipSweep = 0;
		zonePointer->ipTimestamp = false;
		zonePointer->land = false;
		zonePointer->limitSessions = 128;
		zonePointer->malformedUrl = false;	
		zonePointer->pingOfDeath = false;
		zonePointer->portScan = 5000;
		zonePointer->synAckAck = false;
		zonePointer->synFin = false;
		zonePointer->synFlood = false;	
		zonePointer->synFrags = false;	
		zonePointer->noFlag = false;
		zonePointer->tearDrop = false;
		zonePointer->udpFlood = false;
		zonePointer->unknownProtocol = false;
		zonePointer->winNuke = false;
		zonePointer->onTunnel = false;
	}

	return zonePointer;
}


// Process Zone Lines
void processSOSZone(char *line, struct nipperConfig *nipper)
{
	// Variables
	struct zoneSOS *zonePointer = 0;
	struct ciscoCommand command;
	char tempString[nipper->maxSize];
	int tempInt;
	int setting;

	// Debug Output
	if (nipper->debugMode == true)
		printf("Zone Line: %s\n", line);

	// Init
	command = splitLine(line);

	// Set or Unset
	if (strcasecmp(command.part[0], "set") == 0)
		setting = true;
	else
		setting = false;

	// Zone name...
	if (strcasecmp(command.part[2], "name") == 0)
	{
		stripQuotes(command.part[3], tempString, nipper->maxSize);
		zonePointer = getZonePointer(nipper, tempString);
		tempInt = 4;
		while (tempInt < command.parts)
		{
			// Layer 2 VLAN...
			if (strcasecmp(command.part[tempInt], "L2") == 0)
			{
				tempInt++;
				zonePointer->id = atoi(command.part[tempInt]);
			}

			// Tunnel...
			else if (strcasecmp(command.part[tempInt], "tunnel") == 0)
			{
				tempInt++;
				stripQuotes(command.part[tempInt], zonePointer->tunnel, sizeof(zonePointer->tunnel));
			}

			tempInt++;
		}
	}

	// Zone ID
	else if (strcasecmp(command.part[2], "id") == 0)
	{
		stripQuotes(command.part[4], tempString, nipper->maxSize);
		zonePointer = getZonePointer(nipper, tempString);
		zonePointer->id = atoi(command.part[3]);
	}

	// Asymmetric VPN?
	else if (strcasecmp(command.part[2], "asymmetric-vpn") == 0)
		nipper->sos->asymmetricVPN = setting;

	// Block Zone
	else if (strcasecmp(command.part[3], "block") == 0)
	{
		stripQuotes(command.part[2], tempString, nipper->maxSize);
		zonePointer = getZonePointer(nipper, tempString);
		zonePointer->block = setting;
	}

	// DHCP Relay
	else if (strcasecmp(command.part[3], "no-dhcp-relay") == 0)
	{
		stripQuotes(command.part[2], tempString, nipper->maxSize);
		zonePointer = getZonePointer(nipper, tempString);
		if (setting == true)
			zonePointer->dhcpRelay = false;
		else
			zonePointer->dhcpRelay = true;
	}

	// Policy Based Routing
	else if (strcasecmp(command.part[3], "pbr") == 0)
	{
		stripQuotes(command.part[2], tempString, nipper->maxSize);
		zonePointer = getZonePointer(nipper, tempString);
		stripQuotes(command.part[4], zonePointer->pbr, sizeof(zonePointer->pbr));
	}

	// Reassemble for ALG
	else if (strcasecmp(command.part[3], "reassembly-for-alg") == 0)
	{
		stripQuotes(command.part[2], tempString, nipper->maxSize);
		zonePointer = getZonePointer(nipper, tempString);
		zonePointer->reasembleForALG = setting;
	}

	// Screen Network Traffic (Packet/Traffic Analysis)
	else if (strcasecmp(command.part[3], "screen") == 0)
	{
		stripQuotes(command.part[2], tempString, nipper->maxSize);
		zonePointer = getZonePointer(nipper, tempString);

		if (strcasecmp(command.part[4], "alarm-without-drop") == 0)
			zonePointer->alarmWithoutDrop = setting;

		else if (strcasecmp(command.part[4], "block-frag") == 0)
			zonePointer->blockFrag = setting;

		else if (strcasecmp(command.part[4], "component-block") == 0)
		{
			if (strcasecmp(command.part[5], "activex") == 0)
				zonePointer->activeX = setting;

			else if (strcasecmp(command.part[5], "java") == 0)
				zonePointer->java = setting;

			else if (strcasecmp(command.part[5], "exe") == 0)
				zonePointer->exe = setting;

			else if (strcasecmp(command.part[5], "zip") == 0)
				zonePointer->zip = setting;
		}

		else if (strcasecmp(command.part[4], "fin-no-ack") == 0)
			zonePointer->flagDrop = setting;

		else if (strcasecmp(command.part[4], "icmp-flood") == 0)
		{
			if (setting == false)
				zonePointer->icmpFlood = 0;
			else
			{
				if (command.parts == 7)
					zonePointer->icmpFlood = atol(command.part[6]);
				else
					zonePointer->icmpFlood = 1;
			}
		}

		else if (strcasecmp(command.part[4], "icmp-fragment") == 0)
			zonePointer->icmpFrag = setting;

		else if (strcasecmp(command.part[4], "icmp-large") == 0)
			zonePointer->icmpLarge = setting;

		else if (strcasecmp(command.part[4], "ip-bad-option") == 0)
			zonePointer->ipBadOptions = setting;

		else if (strcasecmp(command.part[4], "ip-filter-src") == 0)
			zonePointer->ipSourceRoute = setting;

		else if (strcasecmp(command.part[4], "ip-loose-src-route") == 0)
			zonePointer->ipLooseSource = setting;

		else if (strcasecmp(command.part[4], "ip-record-route") == 0)
			zonePointer->ipRecordRoute = setting;

		else if (strcasecmp(command.part[4], "ip-security-opt") == 0)
			zonePointer->ipSecurityOption = setting;

		else if (strcasecmp(command.part[4], "ip-spoofing") == 0)
		{
			if (setting == false)
				zonePointer->ipSpoofing = sos_spoofing_off;
			else if (command.parts == 5)
				zonePointer->ipSpoofing = sos_spoofing_interface;
			else if (strcasecmp(command.part[5], "zone-based") != 0)
				zonePointer->ipSpoofing = sos_spoofing_routing;
			else
				zonePointer->ipSpoofing = sos_spoofing_zone;
		}

		else if (strcasecmp(command.part[4], "ip-stream-opt") == 0)
			zonePointer->ipStream = setting;

		else if (strcasecmp(command.part[4], "ip-strict-src-route") == 0)
			zonePointer->strictSource = setting;

		else if (strcasecmp(command.part[4], "ip-sweep") == 0)
		{
			if (setting == false)
				zonePointer->ipSweep = 0;
			else
				zonePointer->ipSweep = atoi(command.part[6]);
		}

		else if (strcasecmp(command.part[4], "ip-timestamp-opt") == 0)
			zonePointer->ipTimestamp = setting;

		else if (strcasecmp(command.part[4], "land") == 0)
			zonePointer->land = setting;

		else if (strcasecmp(command.part[4], "limit-session") == 0)
		{
			if (setting == false)
				zonePointer->limitSessions = 0;
			else
			{
				zonePointer->limitSessions = 128;
				if (command.parts == 7)
					zonePointer->limitSessions = atoi(command.part[6]);
			}
		}

		else if (strcasecmp(command.part[4], "mal-URL") == 0)
			zonePointer->malformedUrl = setting;

		else if (strcasecmp(command.part[4], "mal-URL") == 0)
			zonePointer->onTunnel = setting;

		else if ((strcasecmp(command.part[4], "ping-of-death") == 0) || (strcasecmp(command.part[4], "ping-death") == 0))
			zonePointer->pingOfDeath = setting;

		else if (strcasecmp(command.part[4], "port-scan") == 0)
		{
			if (setting == false)
				zonePointer->portScan = 0;
			else
				zonePointer->portScan = atol(command.part[6]);
		}

		else if (strcasecmp(command.part[4], "syn-ack-ack-proxy") == 0)
			zonePointer->synAckAck = setting;

		else if (strcasecmp(command.part[4], "syn-fin") == 0)
			zonePointer->synFin = setting;

		else if (strcasecmp(command.part[4], "syn-flood") == 0)
			zonePointer->synFlood = setting;

		else if (strcasecmp(command.part[4], "syn-frag") == 0)
			zonePointer->synFrags = setting;

		else if (strcasecmp(command.part[4], "tcp-no-flag") == 0)
			zonePointer->noFlag = setting;

		else if (strcasecmp(command.part[4], "tear-drop") == 0)
			zonePointer->tearDrop = setting;

		else if (strcasecmp(command.part[4], "udp-flood") == 0)
			zonePointer->udpFlood = setting;

		else if (strcasecmp(command.part[4], "unknown-protocol") == 0)
			zonePointer->unknownProtocol = setting;

		else if (strcasecmp(command.part[4], "winnuke") == 0)
			zonePointer->winNuke = setting;
	}

	// Send TCP Reset
	else if (strcasecmp(command.part[3], "tcp-rst") == 0)
	{
		stripQuotes(command.part[2], tempString, nipper->maxSize);
		zonePointer = getZonePointer(nipper, tempString);
		zonePointer->tcpReset = setting;
	}

	// VRouter
	else if (strcasecmp(command.part[3], "vrouter") == 0)
	{
		stripQuotes(command.part[2], tempString, nipper->maxSize);
		zonePointer = getZonePointer(nipper, tempString);
		stripQuotes(command.part[4], zonePointer->vrouter, sizeof(zonePointer->vrouter));
	}
}


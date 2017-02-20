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
 *      2. Any code that makes use of this library MUST display the        *
 *         returned text of the Nipper::getVersion() method. Since the     *
 *         text returned includes the version details and copyright of     *
 *         the library, the sugested place to show it would be with the    *
 *         callers "about program" information.                            *
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

// Includes...
#include <cstring>

#include "../../globaldefs.h"
#include "../device.h"


struct protocols
{
	bool show;					// Show the entry
	int start;					// Protocol no. start
	int end;					// Protocol no. end
	const char *name;			// Name
	const char *description;	// Description
	const char *rfc;			// The last RFC
	struct protocols *next;
};

struct protocols protocol142 = {false, 255, 255, "",           "Reserved",                      "",         0};
struct protocols protocol141 = {false, 253, 254, "",           "Use for Experimentation and Testing", "3692", &protocol142};
struct protocols protocol140 = {false, 140, 252, "",           "Unassigned",                    "",         &protocol141};
struct protocols protocol139 = {false, 139, 139, "HIP",        "Host Identity Protocol",        "5201",  &protocol140};
struct protocols protocol138 = {false, 138, 138, "MANET",      "MANET Protocols",               "",         &protocol139};
struct protocols protocol137 = {false, 137, 137, "MPLS-in-IP", "Encapsulating MPLS in IP",      "4023",  &protocol138};
struct protocols protocol136 = {false, 136, 136, "UDPLite",    "Lightweight UDP",               "3828",  &protocol137};
struct protocols protocol135 = {false, 135, 135, "Mobility Header", "Mobility Support in IPv6", "3775",  &protocol136};
struct protocols protocol134 = {false, 134, 134, "RSVP-E2E-IGNORE", "RSVP for IPv4 and IPv6",   "3175",  &protocol135};
struct protocols protocol133 = {false, 133, 133, "FC",         "Fibre Channel",                 "",         &protocol134};
struct protocols protocol132 = {false, 132, 132, "SCTP",       "Stream Control Transmission Protocol", "",  &protocol133};
struct protocols protocol131 = {false, 131, 131, "PIPE",       "Private IP Encapsulation within IP", "",    &protocol132};
struct protocols protocol130 = {false, 130, 130, "SPS",        "Secure Packet Shield",          "",         &protocol131};
struct protocols protocol129 = {false, 129, 129, "IPLT",       "IPLT",                          "",         &protocol130};
struct protocols protocol128 = {false, 128, 128, "SSCOPMCE",   "SSCOPMCE",                      "",         &protocol129};
struct protocols protocol127 = {false, 127, 127, "CRUDP",      "Combat Radio User Datagram",    "",         &protocol128};
struct protocols protocol126 = {false, 126, 126, "CRTP",       "Combat Radio Transport Protocol", "",       &protocol127};
struct protocols protocol125 = {false, 125, 125, "FIRE",       "FIRE",                          "",         &protocol126};
struct protocols protocol124 = {false, 124, 124, "ISIS over IPv4", "Intermediate System to Intermediate System over IPv4", "", &protocol125};
struct protocols protocol123 = {false, 123, 123, "PTP",        "Performance Transparency Protocol", "",     &protocol124};
struct protocols protocol122 = {false, 122, 122, "SM",         "SM",                            "",         &protocol123};
struct protocols protocol121 = {false, 121, 121, "SMP",        "Simple Message Protocol",       "",         &protocol122};
struct protocols protocol120 = {false, 120, 120, "UTI",        "UTI",                           "",         &protocol121};
struct protocols protocol119 = {false, 119, 119, "SRP",        "SpectraLink Radio Protocol",    "",         &protocol120};
struct protocols protocol118 = {false, 118, 118, "STP",        "Schedule Transfer Protocol",    "",         &protocol119};
struct protocols protocol117 = {false, 117, 117, "IATP",       "Interactive Agent Transfer Protocol", "",   &protocol118};
struct protocols protocol116 = {false, 116, 116, "DDX",        "D-II Data Exchange",            "",         &protocol117};
struct protocols protocol115 = {false, 115, 115, "L2TP",       "Layer Two Tunneling Protocol",  "",         &protocol116};
struct protocols protocol114 = {false, 114, 114, "",           "Any 0 Hop Protocol",            "",         &protocol115};
struct protocols protocol113 = {false, 113, 113, "PGM",        "PGM Reliable Transport Protocol", "",       &protocol114};
struct protocols protocol112 = {false, 112, 112, "VRRP",       "Virtual Router Redundancy Protocol", "3768", &protocol113};
struct protocols protocol111 = {false, 111, 111, "IPX-in-IP",  "IPX in IP",                     "",         &protocol112};
struct protocols protocol110 = {false, 110, 110, "Compaq-Peer","Compaq Peer Protocol",          "",         &protocol111};
struct protocols protocol109 = {false, 109, 109, "SNP",        "Sitara Networks Protocol",      "",         &protocol110};
struct protocols protocol108 = {false, 108, 108, "IPComp",     "IP Payload Compression Protocol", "2393", &protocol109};
struct protocols protocol107 = {false, 107, 107, "A/N",        "Active Networks",               "",         &protocol108};
struct protocols protocol106 = {false, 106, 106, "QNX",        "QNX",                           "",         &protocol107};
struct protocols protocol105 = {false, 105, 105, "SCPS",       "SCPS",                          "",         &protocol106};
struct protocols protocol104 = {false, 104, 104, "ARIS",       "ARIS",                          "",         &protocol105};
struct protocols protocol103 = {false, 103, 103, "PIM",        "Protocol Independent MulticastP", "",       &protocol104};
struct protocols protocol102 = {false, 102, 102, "PNNI",       "PNNI over IP",                  "",         &protocol103};
struct protocols protocol101 = {false, 101, 101, "IFMP",       "Ipsilon Flow Management Protocol", "",      &protocol102};
struct protocols protocol100 = {false, 100, 100, "GMTP",       "GMTP",                          "",         &protocol101};
struct protocols protocol99  = {false,  99,  99, "",           "Any Private Encryption Scheme", "",         &protocol100};
struct protocols protocol98  = {false,  98,  98, "ENCAP",      "Encapsulation Header",          "1241",  &protocol99};
struct protocols protocol97  = {false,  97,  97, "ETHERIP",    "Ethernet-within-IP Encapsulation", "3378", &protocol98};
struct protocols protocol96  = {false,  96,  96, "SCC-SP",     "Semaphore Communications Security Protocol", "", &protocol97};
struct protocols protocol95  = {false,  95,  95, "MICP",       "Mobile Internetworking Control Protocol","", &protocol96};
struct protocols protocol94  = {false,  94,  94, "IPIP",       "IP-within-IP Encapsulation Protocol", "",   &protocol95};
struct protocols protocol93  = {false,  93,  93, "AX.25",      "AX.25 Frames",                  "",         &protocol94};
struct protocols protocol92  = {false,  92,  92, "MTP",        "Multicast Transport Protocol",  "",         &protocol93};
struct protocols protocol91  = {false,  91,  91, "LARP",       "Locus Address Resolution Protocol", "",     &protocol92};
struct protocols protocol90  = {false,  90,  90, "Sprite-RPC", "Sprite RPC Protocol",           "",         &protocol91};
struct protocols protocol89  = {false,  89,  89, "OSPFIGP",    "Open Shortest Path First",      "1583",  &protocol90};
struct protocols protocol88  = {false,  88,  88, "EIGRP",      "Enhanced IGRP",                 "",         &protocol89};
struct protocols protocol87  = {false,  87,  87, "TCF",        "TCF",                           "",         &protocol88};
struct protocols protocol86  = {false,  86,  86, "DGP",        "Dissimilar Gateway Protocol",   "",         &protocol87};
struct protocols protocol85  = {false,  85,  85, "NSFNET-IGP", "NSFNET-IGP",                    "",         &protocol86};
struct protocols protocol84  = {false,  84,  84, "TTP",        "TTP",                           "",         &protocol85};
struct protocols protocol83  = {false,  83,  83, "VINES",      "VINES",                         "",         &protocol84};
struct protocols protocol82  = {false,  82,  82, "SECURE-VMTP","Secure VMTP",                   "",         &protocol83};
struct protocols protocol81  = {false,  81,  81, "VMTP",       "Versatile Message Transaction Protocol", "1045", &protocol82};
struct protocols protocol80  = {false,  80,  80, "ISO-IP",     "ISO Internet Protocol",         "",         &protocol81};
struct protocols protocol79  = {false,  79,  79, "WB-EXPAK",   "WIDEBAND EXPAK",                "",         &protocol80};
struct protocols protocol78  = {false,  78,  78, "WB-MON",     "WIDEBAND Monitoring",           "",         &protocol79};
struct protocols protocol77  = {false,  77,  77, "SUN-ND",     "SUN ND PROTOCOL-Temporary",     "",         &protocol78};
struct protocols protocol76  = {false,  76,  76, "BR-SAT-MON", "Backroom SATNET Monitoring",    "",         &protocol77};
struct protocols protocol75  = {false,  75,  75, "PVP",        "Packet Video Protocol",         "",         &protocol76};
struct protocols protocol74  = {false,  74,  74, "WSN",        "Wang Span Network",             "",         &protocol75};
struct protocols protocol73  = {false,  73,  73, "CPHB",       "Computer Protocol Heart Beat",  "",         &protocol74};
struct protocols protocol72  = {false,  72,  72, "CPNX",       "Computer Protocol Network Executive", "",   &protocol73};
struct protocols protocol71  = {false,  71,  71, "IPCV",       "Internet Packet Core Utility",  "",         &protocol72};
struct protocols protocol70  = {false,  70,  70, "VISA",       "VISA Protocol",                 "",         &protocol71};
struct protocols protocol69  = {false,  69,  69, "SAT-MON",    "SATNET Monitoring",             "",         &protocol70};
struct protocols protocol68  = {false,  68,  68, "",           "Any Distributed File System",   "",         &protocol69};
struct protocols protocol67  = {false,  67,  67, "IPPC",       "Internet Pluribus Packet Core", "",         &protocol68};
struct protocols protocol66  = {false,  66,  66, "RVD",        "MIT Remote Virtual Disk Protocol", "",      &protocol67};
struct protocols protocol65  = {false,  65,  65, "KRYPTOLAN",  "Kryptolan",                     "",         &protocol66};
struct protocols protocol64  = {false,  64,  64, "SAT-EXPAK",  "SATNET and Backroom EXPAK",     "",         &protocol65};
struct protocols protocol63  = {false,  63,  63, "",           "Any Local Network",             "",         &protocol64};
struct protocols protocol62  = {false,  62,  62, "CFTP",       "CFTP",                          "",         &protocol63};
struct protocols protocol61  = {false,  61,  61, "",           "Any Host Internal Protocol",    "",         &protocol62};
struct protocols protocol60  = {false,  60,  60, "IPv6-Opts",  "Destination Options for IPv6",  "1883",  &protocol61};
struct protocols protocol59  = {false,  59,  59, "IPv6-NoNxt", "No Next Header for IPv6",       "1883",  &protocol60};
struct protocols protocol58  = {false,  58,  58, "IPv6-ICMP",  "ICMP for IPv6",                 "1883",  &protocol59};
struct protocols protocol57  = {false,  57,  57, "SKIP",       "SKIP",                          "",         &protocol58};
struct protocols protocol56  = {false,  56,  56, "TLSP",       "Transport Layer Security Protocol", "",     &protocol57};
struct protocols protocol55  = {false,  55,  55, "MOBILE",     "IP Mobility",                   "",         &protocol56};
struct protocols protocol54  = {false,  54,  54, "NARP",       "NBMA Address Resolution Protocol","1735",&protocol55};
struct protocols protocol53  = {false,  53,  53, "SWIPE",      "IP with Encryption",            "",         &protocol54};
struct protocols protocol52  = {false,  52,  52, "I-NLSP",     "Integrated Net Layer Security Protocol", "",&protocol53};
struct protocols protocol51  = {false,  51,  51, "AH",         "Authentication Header",         "2402",  &protocol52};
struct protocols protocol50  = {false,  50,  50, "ESP",        "Encapsulating Security Payload","2406",  &protocol51};
struct protocols protocol49  = {false,  49,  49, "BNA",        "BNA",                           "",         &protocol50};
struct protocols protocol48  = {false,  48,  48, "DSR",        "Dynamic Source Routing Protocol","4728", &protocol49};
struct protocols protocol47  = {false,  47,  47, "GRE",        "General Routing Encapsulation", "",         &protocol48};
struct protocols protocol46  = {false,  46,  46, "RSVP",       "Reservation Protocol",          "",         &protocol47};
struct protocols protocol45  = {false,  45,  45, "IDRP",       "Inter-Domain Routing Protocol", "",         &protocol46};
struct protocols protocol44  = {false,  44,  44, "IPv6-Frag",  "Fragment Header for IPv6",      "",         &protocol45};
struct protocols protocol43  = {false,  43,  43, "IPv6-Route", "Routing Header for IPv6",       "",         &protocol44};
struct protocols protocol42  = {false,  42,  42, "SDRP",       "Source Demand Routing Protocol","",         &protocol43};
struct protocols protocol41  = {false,  41,  41, "IPv6",       "Internet Protocol Version 6",   "",         &protocol42};
struct protocols protocol40  = {false,  40,  40, "IL",         "IL Transport Protocol",         "",         &protocol41};
struct protocols protocol39  = {false,  39,  39, "TP++",       "TP++ Transport Protocol",       "",         &protocol40};
struct protocols protocol38  = {false,  38,  38, "IDPR-CMTP",  "IDPR Control Message Transport Protocol", "", &protocol39};
struct protocols protocol37  = {false,  37,  37, "DDP",        "Datagram Delivery Protocol",    "",         &protocol38};
struct protocols protocol36  = {false,  36,  36, "XTP",        "XTP",                           "",         &protocol37};
struct protocols protocol35  = {false,  35,  35, "IDPR",       "Inter-Domain Policy Routing Protocol", "",  &protocol36};
struct protocols protocol34  = {false,  34,  34, "3PC",        "Third Party Connect Protocol",  "",         &protocol35};
struct protocols protocol33  = {false,  33,  33, "DCCP",       "Datagram Congestion Control Protocol", "4340", &protocol34};
struct protocols protocol32  = {false,  32,  32, "MERIT-INP",  "MERIT Internodal Protocol",     "",         &protocol33};
struct protocols protocol31  = {false,  31,  31, "MFE-NSP",    "MFE Network Services Protocol", "",         &protocol32};
struct protocols protocol30  = {false,  30,  30, "NETBLT",     "Bulk Data Transfer Protocol",   "969",   &protocol31};
struct protocols protocol29  = {false,  29,  29, "ISO-TP4",    "ISO Transport Protocol Class 4","905",   &protocol30};
struct protocols protocol28  = {false,  28,  28, "IRTP",       "Internet Reliable Transactio Protocol", "938",   &protocol29};
struct protocols protocol27  = {false,  27,  27, "RDP",        "Reliable Data Protocol",        "908",   &protocol28};
struct protocols protocol26  = {false,  26,  26, "LEAF-2",     "Leaf-2",                        "",         &protocol27};
struct protocols protocol25  = {false,  25,  25, "LEAF-1",     "Leaf-1",                        "",         &protocol26};
struct protocols protocol24  = {false,  24,  24, "TRUNK-2",    "Trunk-2",                       "",         &protocol25};
struct protocols protocol23  = {false,  23,  23, "TRUNK-1",    "Trunk-1",                       "",         &protocol24};
struct protocols protocol22  = {false,  22,  22, "XNS-IDP",    "XEROX NS IDP",                  "",         &protocol23};
struct protocols protocol21  = {false,  21,  21, "PRM",        "Packet Radio Measurement",      "",         &protocol22};
struct protocols protocol20  = {false,  20,  20, "HMP",        "Host Monitoring Protocol",      "869",   &protocol21};
struct protocols protocol19  = {false,  19,  19, "DCN-MEAS",   "DCN Measurement Subsystems",    "",         &protocol20};
struct protocols protocol18  = {false,  18,  18, "MUX",        "Multiplexing",                  "",         &protocol19};
struct protocols protocol17  = {true ,  17,  17, "UDP",        "User Datagram Protocol",        "768",   &protocol18};
struct protocols protocol16  = {false,  16,  16, "CHAOS",      "Chaos",                         "",         &protocol17};
struct protocols protocol15  = {false,  15,  15, "XNET",       "Cross Net Debugger",            "",         &protocol16};
struct protocols protocol14  = {false,  14,  14, "EMCON",      "EMCON",                         "",         &protocol15};
struct protocols protocol13  = {false,  13,  13, "ARGUS",      "ARGUS",                         "",         &protocol14};
struct protocols protocol12  = {false,  12,  12, "PUP",        "PARC Universal Packet",         "",         &protocol13};
struct protocols protocol11  = {false,  11,  11, "NVP-II",     "Network Voice Protocol",        "741",   &protocol12};
struct protocols protocol10  = {false,  10,  10, "BBN-RCC-MON","BBN RCC Monitoring",            "",         &protocol11};
struct protocols protocol9   = {false,   9,   9, "IGP",        "Interior Gateway Protocol",     "",         &protocol10};
struct protocols protocol8   = {false,   8,   8, "EGP",        "Exterior Gateway Protocol",     "888",   &protocol9};
struct protocols protocol7   = {false,   7,   7, "CBT",        "CBT",                           "",         &protocol8};
struct protocols protocol6   = {true ,   6,   6, "TCP",        "Transmission Control Protocol", "793",   &protocol7};
struct protocols protocol5   = {false,   5,   5, "ST",         "Stream",                        "1819",  &protocol6};
struct protocols protocol4   = {false,   4,   4, "IP",         "IP in IP (encapsulation)",      "2003",  &protocol5};
struct protocols protocol3   = {false,   3,   3, "GGP",        "Gateway-to-Gateway",            "823",   &protocol4};
struct protocols protocol2   = {false,   2,   2, "IGMP",       "Internet Group Management",     "1112",  &protocol3};
struct protocols protocol1   = {true ,   1,   1, "ICMP",       "Internet Control Message",      "792",   &protocol2};
struct protocols protocol    = {false,   0,   0, "HOPOPT",     "IPv6 Hop-by-Hop Option",        "1883",  &protocol1};


void Device::addProtocol(const char *name)
{
	// Variables
	struct protocols *protocolsPointer = 0;

	// Search
	protocolsPointer = &protocol;
	while ((protocolsPointer->next != 0) && (strcasecmp(protocolsPointer->name, name) != 0))
		protocolsPointer = protocolsPointer->next;

	// If found, add
	if (strcasecmp(protocolsPointer->name, name) == 0)
		protocolsPointer->show = true;
}
void Device::addProtocol(int protocolNumber)
{
	// Variables
	struct protocols *protocolsPointer = 0;

	// Search
	protocolsPointer = &protocol;
	while ((protocolsPointer->next != 0) && (protocolNumber < protocolsPointer->start) && (protocolNumber > protocolsPointer->end))
		protocolsPointer = protocolsPointer->next;

	// If found, add
	if ((protocolNumber >= protocolsPointer->start) && (protocolNumber <= protocolsPointer->end))
		protocolsPointer->show = true;
}


const char *Device::getProtocol(int protocolNumber)
{
	// Variables
	struct protocols *protocolsPointer = 0;

	// Search
	protocolsPointer = &protocol;
	while (protocolsPointer->next != 0)
	{
		if ((protocolNumber >= protocolsPointer->start) && (protocolNumber <= protocolsPointer->end))
			return protocolsPointer->name;
		else
			protocolsPointer = protocolsPointer->next;
	}

	// If not found
	return "";
}


int Device::generateAppendixUsedProtocols()
{
	// Variables...
	configReportStruct *configPointer = 0;
	struct protocols *protocolsPointer = 0;
	paragraphStruct *paragraphPointer = 0;
	bodyStruct *bodyPointer = 0;
	string tempString;
	bool generateSection = false;
	int errorCode = 0;

	// Determine if any are used...
	protocolsPointer = &protocol;
	while ((protocolsPointer->next != 0) && (generateSection == false))
	{
		if (protocolsPointer->show == true)
			generateSection = true;
		else
			protocolsPointer = protocolsPointer->next;
	}

	// Generate appendix section...
	if (generateSection == true)
	{
		configPointer = getAppendixSection("APPENDIX-PROTOCOLS");
		configPointer->title = i18n("*ABBREV*IP*-ABBREV* Protocols");
		paragraphPointer = addParagraph(configPointer);
		errorCode = addTable(paragraphPointer, "APPENDIX-PROTOCOL-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("*ABBREV*IP*-ABBREV* protocols");
		addTableHeading(paragraphPointer->table, i18n("Protocol"), false);
		addTableHeading(paragraphPointer->table, i18n("Name"), false);
		addTableHeading(paragraphPointer->table, i18n("Description"), false);
		addTableHeading(paragraphPointer->table, i18n("*ABBREV*RFC*-ABBREV*"), false);
		while (protocolsPointer != 0)
		{
			if (protocolsPointer->show == true)
			{
				if (protocolsPointer->start == protocolsPointer->end)
					tempString.assign(intToString(protocolsPointer->start));
				else
				{
					tempString.assign(intToString(protocolsPointer->start));
					tempString.append(" - ");
					tempString.append(intToString(protocolsPointer->end));
				}
				bodyPointer = addTableData(paragraphPointer->table, tempString.c_str());
				bodyPointer = addTableData(paragraphPointer->table, protocolsPointer->name);
				bodyPointer = addTableData(paragraphPointer->table, protocolsPointer->description);
				if (strlen(protocolsPointer->rfc) == 0)
					tempString.assign("");
				else
				{
					tempString.assign("RFC");
					tempString.append(protocolsPointer->rfc);
				}
				bodyPointer = addTableData(paragraphPointer->table, tempString.c_str());
			}
			protocolsPointer = protocolsPointer->next;
		}
	}

	return errorCode;
}


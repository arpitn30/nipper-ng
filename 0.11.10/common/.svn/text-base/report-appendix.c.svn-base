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


// ----------------------------------------------------------------------------------
// Common Port Assignments...

struct ports
{
	int add;				// true or false
	const char *text;
	int port;				// Port Number
	struct ports *next;
};

// Current: 92
struct ports ap_port91  = {false, "PCAnywhere-Status", 5632, 0};
struct ports ap_port90  = {false, "PCAnywhere-Data", 5631, &ap_port91};
struct ports ap_port89  = {false, "SecureID-UDP", 5510, &ap_port90};
struct ports ap_port88  = {false, "AOL", 5190, &ap_port89};
struct ports ap_port87  = {false, "CTIQBE", 2748, &ap_port88};
struct ports ap_port86  = {false, "PPTP", 1723, &ap_port87};
struct ports ap_port85  = {false, "H323", 1720, &ap_port86};
struct ports ap_port84  = {false, "RADIUS-Acct", 1646, &ap_port85};
struct ports ap_port83  = {false, "RADIUS", 1645, &ap_port84};
struct ports ap_port82  = {false, "SQLNet", 1521, &ap_port83};
struct ports ap_port81  = {false, "Citrix-ICA", 1494, &ap_port82};
struct ports ap_port80  = {false, "LotusNotes", 1352, &ap_port81};
struct ports ap_port79  = {false, "KERBEROS", 750, &ap_port80};
struct ports ap_port78  = {false, "LDAPS", 636, &ap_port79};
struct ports ap_port77  = {false, "KShell", 544, &ap_port78};
struct ports ap_port76  = {false, "KLogin", 543, &ap_port77};
struct ports ap_port75  = {false, "UUCP", 540, &ap_port76};
struct ports ap_port74  = {false, "Timed", 525, &ap_port75};
struct ports ap_port73  = {false, "RIPv2", 520, &ap_port74};
struct ports ap_port72  = {false, "RIP", 520, &ap_port73};
struct ports ap_port71  = {false, "Talk", 517, &ap_port72};
struct ports ap_port70  = {false, "LPD", 515, &ap_port71};
struct ports ap_port69  = {false, "Printer", 515, &ap_port70};
struct ports ap_port68  = {false, "Syslog", 514, &ap_port69};
struct ports ap_port67  = {false, "CMD", 514, &ap_port68};
struct ports ap_port66  = {false, "RSH", 514, &ap_port67};
struct ports ap_port65  = {false, "RWho", 513, &ap_port66};
struct ports ap_port64  = {false, "Who", 513, &ap_port65};
struct ports ap_port63  = {false, "RLogin", 513, &ap_port64};
struct ports ap_port62  = {false, "Login", 513, &ap_port63};
struct ports ap_port61  = {false, "RExec", 512, &ap_port62};
struct ports ap_port60  = {false, "Exec", 512, &ap_port61};
struct ports ap_port59  = {false, "BIFF", 512, &ap_port60};
struct ports ap_port58  = {false, "IKE", 500, &ap_port59};
struct ports ap_port57  = {false, "ISAKMP", 500, &ap_port58};
struct ports ap_port56  = {false, "PIM-Auto-RP", 496, &ap_port57};
struct ports ap_port55  = {false, "HTTPS", 443, &ap_port56};
struct ports ap_port54  = {false, "Mobile-IP", 434, &ap_port55};
struct ports ap_port53  = {false, "LDAP", 389, &ap_port54};
struct ports ap_port52  = {false, "DNSIX", 195, &ap_port53};
struct ports ap_port51  = {false, "IRC", 194, &ap_port52};
struct ports ap_port50  = {false, "BGP", 179, &ap_port51};
struct ports ap_port49  = {false, "XDMCP", 177, &ap_port50};
struct ports ap_port48  = {false, "SNMP-Trap", 162, &ap_port49};
struct ports ap_port47  = {false, "SNMP", 161, &ap_port48};
struct ports ap_port46  = {false, "IMAP4", 143, &ap_port47};
struct ports ap_port45  = {false, "NetBIOS-SSN", 139, &ap_port46};
struct ports ap_port44  = {false, "NetBIOS-DGM", 138, &ap_port45};
struct ports ap_port43  = {false, "NetBIOS-NS", 137, &ap_port44};
//struct ports ap_port42  = {false, "SNMP", 126, &ap_port43};
struct ports ap_port41  = {false, "NTP", 123, &ap_port43};
struct ports ap_port40  = {false, "NNTP", 119, &ap_port41};
struct ports ap_port39  = {false, "UUCP-Path", 117, &ap_port40};
struct ports ap_port38  = {false, "Auth", 113, &ap_port39};
struct ports ap_port37  = {false, "Ident", 113, &ap_port38};
struct ports ap_port36  = {false, "SUNRPC", 111, &ap_port37};
struct ports ap_port35  = {false, "POP3", 110, &ap_port36};
struct ports ap_port34  = {false, "POP2", 109, &ap_port35};
struct ports ap_port33  = {false, "X400-SND", 104, &ap_port34};
struct ports ap_port32  = {false, "X400", 103, &ap_port33};
struct ports ap_port31  = {false, "ISO-TSAP", 102, &ap_port32};
struct ports ap_port30  = {false, "Hostname", 101, &ap_port31};
struct ports ap_port29  = {false, "SUPDUP", 95, &ap_port30};
struct ports ap_port28  = {false, "HTTP", 80, &ap_port29};
struct ports ap_port27  = {false, "WWW", 80, &ap_port28};
struct ports ap_port26  = {false, "Finger", 79, &ap_port27};
struct ports ap_port25  = {false, "Gopher", 70, &ap_port26};
struct ports ap_port24  = {false, "TFTP", 69, &ap_port25};
struct ports ap_port23  = {false, "BOOTPC", 68, &ap_port24};
struct ports ap_port22  = {false, "DHCP", 68, &ap_port23};
struct ports ap_port21  = {false, "DHCP", 67, &ap_port22};
struct ports ap_port20  = {false, "BOOTPS", 67, &ap_port21};
struct ports ap_port19  = {false, "Domain", 53, &ap_port20};
struct ports ap_port18  = {false, "Login", 49, &ap_port19};
struct ports ap_port17  = {false, "TACACS", 49, &ap_port18};
struct ports ap_port16  = {false, "Nicname", 43, &ap_port17};
struct ports ap_port15  = {false, "Whois", 43, &ap_port16};
struct ports ap_port14  = {false, "Nameserver", 42, &ap_port15};
struct ports ap_port13  = {false, "RLP", 39, &ap_port14};
struct ports ap_port12  = {false, "Time", 37, &ap_port13};
struct ports ap_port11  = {false, "SMTP", 25, &ap_port12};
struct ports ap_port10  = {false, "Telnet", 23, &ap_port11};
struct ports ap_port92  = {false, "SSH", 22, &ap_port10};
struct ports ap_port9   = {false, "FTP", 21, &ap_port92};
struct ports ap_port8   = {false, "FTP-Data", 20, &ap_port9};
struct ports ap_port7   = {false, "Chargen", 19, &ap_port8};
struct ports ap_port6   = {false, "Quote", 17, &ap_port7};
struct ports ap_port5   = {false, "Netstat", 15, &ap_port6};
struct ports ap_port4   = {false, "Daytime", 13, &ap_port5};
struct ports ap_port3   = {false, "Users", 11, &ap_port4};
struct ports ap_port2   = {false, "Discard", 9, &ap_port3};
struct ports ap_port1   = {false, "Echo", 7, &ap_port2};
struct ports ap_port    = {false, "AH", 5, &ap_port1};


void addPort(char *port)
{
	// Variables
	struct ports *portPointer = 0;

	// Search for abbreviation
	portPointer = &ap_port;
	while ((portPointer->next != 0) && (strcasecmp(portPointer->text, port) != 0))
		portPointer = portPointer->next;

	// If found, add port
	if (strcasecmp(portPointer->text, port) == 0)
		portPointer->add = true;
}


// ----------------------------------------------------------------------------------
// Abreviations...

struct abbrev
{
	int add;				// true or false
	int expanded;			// true or false
	const char *ab;
	const char *desc;
	struct abbrev *next;
};

// Current: 162

struct abbrev ab_append126 = {false,false, "XDMCP",  "X Display Manager Control Protocol", 0};
struct abbrev ab_append0   = {false,false, "WWW",    "World Wide Web", &ab_append126};
struct abbrev ab_append1   = {false,false, "WAN",    "Wide Area Network", &ab_append0};
struct abbrev ab_append92  = {false,false, "VTY",    "Virtual Teletype", &ab_append1};
struct abbrev ab_append2   = {false,false, "VTP",    "VLAN Trunking Protocol", &ab_append92};
struct abbrev ab_append150 = {false,false, "VRRP",   "Virtual Router Redundancy Protocol", &ab_append2};
struct abbrev ab_append146 = {false,false, "VRF",    "VPN Routing and Forwarding", &ab_append150};
struct abbrev ab_append3   = {false,false, "VPN",    "Virtual Private Network", &ab_append146};
struct abbrev ab_append4   = {false,false, "VoIP",   "Voice over IP", &ab_append3};
struct abbrev ab_append149 = {false,false, "VLANs",  "Virtual Local Area Networks", &ab_append4};
struct abbrev ab_append5   = {false,false, "VLAN",   "Virtual Local Area Network", &ab_append149};
struct abbrev ab_append142 = {false,false, "VIPs",   "Versatile Interface Processors", &ab_append5};
struct abbrev ab_append143 = {false,false, "VIP",    "Versatile Interface Processor", &ab_append142};
struct abbrev ab_append105 = {false,false, "UUCP",   "Unix-to-Unix Copy", &ab_append143};
struct abbrev ab_append147 = {false,false, "UTC",    "Coordinated Universal Time", &ab_append105};
struct abbrev ab_append6   = {false,false, "URL",    "Uniform Resource Locator", &ab_append147};
struct abbrev ab_append7   = {false,false, "UDP",    "User Datagram Protocol", &ab_append6};
struct abbrev ab_append91  = {false,false, "TTY",    "Teletype", &ab_append7};
struct abbrev ab_append90  = {false,false, "TTL",    "Time To Live", &ab_append91};
struct abbrev ab_append103 = {false,false, "TSAP",   "Transport Service Access Point", &ab_append90};
struct abbrev ab_append8   = {false,false, "TFTP",   "Trivial File Transfer Protocol", &ab_append103};
struct abbrev ab_append9   = {false,false, "TDP",    "Tag Distribution Protocol", &ab_append8};
struct abbrev ab_append10  = {false,false, "TCP",    "Transmission Control Protocol", &ab_append9};
struct abbrev ab_append11  = {false,false, "TAPI",   "Telephony Application Programming Interface", &ab_append10};
struct abbrev ab_append12  = {false,false, "TACACS", "Terminal Access Controller Access Control System", &ab_append11};
struct abbrev ab_append104 = {false,false, "SunRPC", "Sun Remote Procedure Call", &ab_append12};
struct abbrev ab_append13  = {false,false, "SSL",    "Secure Sockets Layer", &ab_append104};
struct abbrev ab_append14  = {false,false, "SSH",    "Secure Shell", &ab_append13};
struct abbrev ab_append125 = {false,false, "SQLNet", "Structured Query Language Network", &ab_append14};
struct abbrev ab_append132 = {false,false, "SPAN",   "Switch Port Analyser", &ab_append125};
struct abbrev ab_append15  = {false,false, "SMTP",   "Simple Mail Transfer Protocol", &ab_append132};
struct abbrev ab_append89  = {false,false, "SNTP",   "Simple Network Time Protocol", &ab_append15};
struct abbrev ab_append112 = {false,false, "SNP",    "Sitara Networks Protocol", &ab_append89};
struct abbrev ab_append16  = {false,false, "SNMP",   "Simple Network Management Protocol", &ab_append112};
struct abbrev ab_append17  = {false,false, "SIP",    "Session Initiation Protocol", &ab_append16};
struct abbrev ab_append18  = {false,false, "SDP",    "Session Description Protocol", &ab_append17};
struct abbrev ab_append127 = {false,false, "SAID",   "Security Association Identifier", &ab_append18};
struct abbrev ab_append133 = {false,false, "RPF",    "Reverse Path Forwarding", &ab_append127};
struct abbrev ab_append19  = {false,false, "RPC",    "Remote Procedure Call", &ab_append133};
struct abbrev ab_append100 = {false,false, "RLP",    "Resource Location Protocol", &ab_append19};
struct abbrev ab_append99  = {false,false, "RJE",    "Remote Job Entry", &ab_append100};
struct abbrev ab_append20  = {false,false, "RIP",    "Routing Information Protocol", &ab_append99};
struct abbrev ab_append21  = {false,false, "RADIUS", "Remote Authentication Dial-In User Service", &ab_append20};
struct abbrev ab_append22  = {false,false, "PPTP",   "Point to Point Tunneling Protocol", &ab_append21};
struct abbrev ab_append23  = {false,false, "PPPoE",  "Point to Point Protocol over Ethernet", &ab_append22};
struct abbrev ab_append24  = {false,false, "PPP",    "Point to Point Protocol", &ab_append23};
struct abbrev ab_append98  = {false,false, "POP3",   "Post Office Protocol version 3", &ab_append24};
struct abbrev ab_append97  = {false,false, "POP2",   "Post Office Protocol version 2", &ab_append98};
struct abbrev ab_append25  = {false,false, "POP",    "Post Office Protocol", &ab_append97};
struct abbrev ab_append26  = {false,false, "PKI",    "Public Key Infrastructure", &ab_append25};
struct abbrev ab_append27  = {false,false, "PIX",    "Private Internet Exchange", &ab_append26};
struct abbrev ab_append111 = {false,false, "PIM",    "Protocol Independent Multicast", &ab_append27};
struct abbrev ab_append110 = {false,false, "PCP",    "Payload Compression Protocol", &ab_append111};
struct abbrev ab_append95  = {false,false, "PAT",    "Port Address Translation", &ab_append110};
struct abbrev ab_append28  = {false,false, "PAP",    "Password Authentication Protocol", &ab_append95};
struct abbrev ab_append29  = {false,false, "PAD",    "Packet Assembler / Disassembler", &ab_append28};
struct abbrev ab_append30  = {false,false, "OSPF",   "Open Shortest Path First", &ab_append29};
struct abbrev ab_append144 = {false,false, "OID",    "Object Identifier", &ab_append30};
struct abbrev ab_append31  = {false,false, "NTP",    "Network Time Protocol", &ab_append144};
struct abbrev ab_append93  = {false,true,  "NT",     "New Technology", &ab_append31};
struct abbrev ab_append109 = {false,false, "NOS",    "Network Operating System", &ab_append93};
struct abbrev ab_append32  = {false,false, "NNTP",   "Network News Transfer Protocol", &ab_append109};
struct abbrev ab_append33  = {false,false, "NMP",    "Network Management Processor", &ab_append32};
struct abbrev ab_append34  = {false,false, "NIC",    "Network Interface Center", &ab_append33};
struct abbrev ab_append158 = {false,false, "NFS",    "Network File System", &ab_append34};
struct abbrev ab_append124 = {false,false, "NetBIOS-SSN", "NetBIOS Session Service", &ab_append158};
struct abbrev ab_append123 = {false,false, "NetBIOS-NS",  "NetBIOS Name Service", &ab_append124};
struct abbrev ab_append122 = {false,false, "NetBIOS-DGM", "NetBIOS Datagram Service", &ab_append123};
struct abbrev ab_append35  = {false,false, "NAT",    "Network Address Translation", &ab_append122};
struct abbrev ab_append36  = {false,false, "MTU",    "Maximum Transmission Unit", &ab_append35};
struct abbrev ab_append94  = {false,false, "MS-CHAP","MicroSoft Challenge Handshake Authentication Protocol", &ab_append36};
struct abbrev ab_append86  = {false,false, "MPP",    "Management Plane Protection", &ab_append94};
struct abbrev ab_append37  = {false,false, "MPLS",   "Multi Protocol Label Switching", &ab_append86};
struct abbrev ab_append88  = {false,false, "MOTD",   "Message Of The Day", &ab_append37};
struct abbrev ab_append38  = {false,false, "MOP",    "Maintenance Operations Protocol", &ab_append88};
struct abbrev ab_append156 = {false,false, "MIPs",   "Mapped IPs", &ab_append38};
struct abbrev ab_append155 = {false,false, "MIP",    "Mapped IP", &ab_append156};
struct abbrev ab_append39  = {false,false, "MIB",    "Management Information Base", &ab_append155};
struct abbrev ab_append148 = {false,false, "MAC",    "Media Access Control", &ab_append39};
struct abbrev ab_append40  = {false,true,  "MD5",    "Message Digest 5", &ab_append148};
struct abbrev ab_append41  = {false,false, "LSA",    "Link State Advertisement", &ab_append40};
struct abbrev ab_append121 = {false,false, "LPD",    "Line Printer Daemon", &ab_append41};
struct abbrev ab_append42  = {false,false, "LDP",    "Label Diretribution Protocol", &ab_append121};
struct abbrev ab_append120 = {false,false, "LDAPS",  "Lightweight Directory Access Protocol (SSL)", &ab_append42};
struct abbrev ab_append119 = {false,false, "LDAP",   "Lightweight Directory Access Protocol", &ab_append120};
struct abbrev ab_append43  = {false,false, "LAN",    "Local Area Network", &ab_append119};
struct abbrev ab_append118 = {false,false, "ISAKMP", "Internet Security Association and Key Management Protocol", &ab_append43};
struct abbrev ab_append44  = {false,false, "IRC",    "Internet Relay Chat", &ab_append118};
struct abbrev ab_append45  = {false,false, "IPSec",  "IP Security protocol", &ab_append44};
struct abbrev ab_append108 = {false,false, "IPinIP", "IP-in-IP encapsulation", &ab_append45};
struct abbrev ab_append46  = {false,true,  "IP",     "Internet Protocol", &ab_append108};
struct abbrev ab_append47  = {false,false, "IOS",    "Internet Operating System", &ab_append46};
struct abbrev ab_append117 = {false,false, "IMAP4",  "Internet Message Access Protocol version 4", &ab_append47};
struct abbrev ab_append157 = {false,false, "IMAP3",  "Internet Message Access Protocol version 3", &ab_append117};
struct abbrev ab_append116 = {false,false, "IMAP",   "Internet Message Access Protocol", &ab_append157};
struct abbrev ab_append48  = {false,false, "IKMP",   "Internet Key Management Protocol", &ab_append116};
struct abbrev ab_append49  = {false,false, "IKE",    "Internet Key Exchange", &ab_append48};
struct abbrev ab_append50  = {false,false, "IGRP",   "Interior Gateway Routing Protocol", &ab_append49};
struct abbrev ab_append152 = {false,false, "IGPs",   "Interior Gateway Protocols", &ab_append50};
struct abbrev ab_append51  = {false,false, "IGP",    "Interior Gateway Protocol", &ab_append152};
struct abbrev ab_append52  = {false,false, "IGMP",   "Internet Group Management Protocol", &ab_append51};
struct abbrev ab_append87  = {false,false, "IDS",    "Intruder Detection System", &ab_append52};
struct abbrev ab_append107 = {false,false, "ICMP6",  "Internet Control Message Protocol for IPv6", &ab_append87};
struct abbrev ab_append53  = {false,false, "ICMP",   "Internet Control Message Protocol", &ab_append107};
struct abbrev ab_append114 = {false,false, "ICA",    "Independent Computing Architecture", &ab_append53};
struct abbrev ab_append54  = {false,false, "IANA",   "Internet Assigned Number Authority", &ab_append114};
struct abbrev ab_append55  = {false,true,  "HTTPS",  "HyperText Transfer Protocol over SSL", &ab_append54};
struct abbrev ab_append56  = {false,true,  "HTTP",   "HyperText Transfer Protocol", &ab_append55};
struct abbrev ab_append57  = {false,false, "HSRP",   "Hot Standby Routing Protocol", &ab_append56};
struct abbrev ab_append134 = {false,false, "GTSM",   "Generalised TTL Security Mechanism", &ab_append57};
struct abbrev ab_append161 = {false,false, "GTP",    "GPRS Tunnelling Protocol", &ab_append134};
struct abbrev ab_append58  = {false,false, "GRE",    "Generic Routing Encapsulation protocol", &ab_append161};
struct abbrev ab_append162 = {false,false, "GPRS",   "General Packet Radio Service", &ab_append58};
struct abbrev ab_append59  = {false,false, "FWSM",   "FireWall Service Module", &ab_append162};
struct abbrev ab_append60  = {false,true,  "FTP",    "File Transfer Protocol", &ab_append59};
struct abbrev ab_append106 = {false,false, "ESP",    "Encapsulated Security Payload", &ab_append60};
struct abbrev ab_append61  = {false,false, "FDDI",   "Fibre Disctributed Data Interface", &ab_append106};
struct abbrev ab_append62  = {false,false, "EIGRP",  "Enhanced Interior Gateway Routing Protocol", &ab_append61};
struct abbrev ab_append153 = {false,false, "EGPs",   "Exterior Gateway Protocols", &ab_append62};
struct abbrev ab_append63  = {false,false, "EGP",    "Exterior Gateway Protocol", &ab_append153};
struct abbrev ab_append96  = {false,false, "DOS",    "Disk Operating System", &ab_append63};
struct abbrev ab_append64  = {false,false, "DoS",    "Denial of Service", &ab_append96};
struct abbrev ab_append65  = {false,false, "DNS",    "Domain Name System", &ab_append64};
struct abbrev ab_append66  = {false,false, "DHCP",   "Dynamic Host Configuration Protocol", &ab_append65};
struct abbrev ab_append67  = {false,false, "DH",     "Diffie-Hellman", &ab_append66};
struct abbrev ab_append68  = {false,false, "DES",    "Data Encryption Standard", &ab_append67};
struct abbrev ab_append131 = {false,false, "DDoS",   "Distributed Denial of Service", &ab_append68};
struct abbrev ab_append69  = {false,false, "dCEF",   "Distributed CEF", &ab_append131};
struct abbrev ab_append160 = {false,false, "DCERPC", "Distributed Computing Environment / Remote Procedure Call", &ab_append69};
struct abbrev ab_append159 = {false,false, "DCE",    "Distributed Computing Environment", &ab_append160};
struct abbrev ab_append140 = {false,false, "CVE",    "Common Vulnerabilities and Exposures", &ab_append159};
struct abbrev ab_append115 = {false,false, "CTIQBE", "Computer Telephony Interface Quick Buffer Encoding", &ab_append140};
struct abbrev ab_append70  = {false,false, "CTI",    "Computer Telephony Integration", &ab_append115};
struct abbrev ab_append151 = {false,false, "CSS",    "Content Services Switch", &ab_append70};
struct abbrev ab_append71  = {false,false, "CRL",    "Certificate Revocation List", &ab_append151};
struct abbrev ab_append72  = {false,true,  "CPU",    "Central Processing Unit", &ab_append71};
struct abbrev ab_append73  = {false,false, "CPP",    "Combinet Propietry Protocol", &ab_append72};
struct abbrev ab_append74  = {false,false, "CHAP",   "Challenge Handshake Authentication Protocol", &ab_append73};
struct abbrev ab_append130 = {false,false, "CEF",    "Cisco Express Forwarding", &ab_append74};
struct abbrev ab_append75  = {false,false, "CDP",    "Cisco Discovery Protocol", &ab_append130};
struct abbrev ab_append76  = {false,false, "CA",     "Certificate Authority", &ab_append75};
struct abbrev ab_append139 = {false,false, "BPDU",   "Bridge Protocol Data Unit", &ab_append76};
struct abbrev ab_append102 = {false,false, "BOOTPS", "BOOTstrap Protocol Server", &ab_append139};
struct abbrev ab_append101 = {false,false, "BOOTPC", "BOOTstrap Protocol Client", &ab_append102};
struct abbrev ab_append77  = {false,false, "BOOTP",  "BOOTstrap Protocol", &ab_append101};
struct abbrev ab_append141 = {false,false, "BID",    "Bugtraq ID", &ab_append77};
struct abbrev ab_append78  = {false,false, "BGP",    "Border Gateway Protocol", &ab_append141};
struct abbrev ab_append136 = {false,false, "ATM",    "Asynchronous Transfer Mode", &ab_append78};
struct abbrev ab_append79  = {false,false, "ASBR",   "Autonomous System Boundry Router", &ab_append136};
struct abbrev ab_append80  = {false,false, "ASA",    "Adaptive Security Appliance", &ab_append79};
struct abbrev ab_append81  = {false,false, "ARP",    "Address Resolution Protocol", &ab_append80};
struct abbrev ab_append113 = {false,false, "AOL",    "America Online", &ab_append81};
struct abbrev ab_append138 = {false,false, "AMP",    "Active Monitor Present", &ab_append113};
struct abbrev ab_append154 = {false,false, "ALG",    "Application Layer Gateway", &ab_append138};
struct abbrev ab_append82  = {false,false, "AH",     "Authentication Header", &ab_append154};
struct abbrev ab_append137 = {false,false, "AFI",    "Authority and Format Identifier", &ab_append82};
struct abbrev ab_append83  = {false,false, "ACLs",   "Access Control Lists", &ab_append137};
struct abbrev ab_append129 = {false,false, "ACL",    "Access Control List", &ab_append83};
struct abbrev ab_append128 = {false,false, "ACEs",   "Access Control Entries", &ab_append129};
struct abbrev ab_append84  = {false,false, "ACE",    "Access Control Entry", &ab_append128};
struct abbrev ab_append85  = {false,false, "ABR",    "Area Border Router", &ab_append84};
struct abbrev ab_append135 = {false,false, "AAL",    "ATM Adaptation Layer", &ab_append85};
struct abbrev ab_append145 = {false,false, "AAA",    "Authentication, Authorization and Accounting", &ab_append135};
struct abbrev ab_append    = {false,true,  "3DES",   "Tripple Data Encryption Standard", &ab_append145};


struct debugAbbrev
{
	char ab[20];
	int count;
	struct debugAbbrev *next;
};
struct debugAbbrev *debugAb = 0;

// Adds an abbreviation not found to a list to be shown
// if the debug abbreviations obtion has been set.
void addAbbrevNotFound(char *abbreviation)
{
	// Variables...
	struct debugAbbrev *debugAbPointer = 0;

	// If structure is empty, create
	if (debugAb == 0)
	{
		debugAb = malloc(sizeof(struct debugAbbrev));
		memset(debugAb, 0, sizeof(struct debugAbbrev));
		debugAbPointer = debugAb;
	}
	else
	{

		// Search for matching abbreviations
		debugAbPointer = debugAb;
		while ((debugAbPointer->next != 0) && (strcasecmp(abbreviation, debugAbPointer->ab) != 0))
			debugAbPointer = debugAbPointer->next;

		// If not found
		if (strcasecmp(abbreviation, debugAbPointer->ab) != 0)
		{
			debugAbPointer->next = malloc(sizeof(struct debugAbbrev));
			memset(debugAbPointer->next, 0, sizeof(struct debugAbbrev));
			debugAbPointer = debugAbPointer->next;
		}
	}

	// Set information
	strncpy(debugAbPointer->ab, abbreviation, sizeof(debugAbPointer->ab) - 1);
	debugAbPointer->count++;
}


#define abbrev_notfound 0
#define abbrev_found 1
#define abbrev_expand 2


// Add an abbreviation to the list to be shown in the
// appendix
int addAbbreviation(char *abbreviation, int expand)
{
	// Variables
	struct abbrev *abbrevPointer = 0;

	// Check that it is not something silly
	if ((strlen(abbreviation) > 0) && (strcmp(abbreviation, "any") != 0))
	{

		// Add Service Port
		addPort(abbreviation);

		// If HTTPS is being set, then SSL also needs to be set
		if (strcasecmp(abbreviation, "HTTPS") == 0)
			addAbbreviation("SSL", false);

		// If LDAPS is set, the SSL also needs to be set
		else if (strcasecmp(abbreviation, "LDAPS") == 0)
			addAbbreviation("SSL", false);

		// If GTP is set, the GPRS also needs to be set
		else if (strcasecmp(abbreviation, "GTP") == 0)
			addAbbreviation("GPRS", false);

		// If IPinIP is set, the IP also needs to be set
		else if (strcasecmp(abbreviation, "IPinIP") == 0)
			addAbbreviation("IP", false);

		// If IPSec is set, the IP also needs to be set
		else if (strcasecmp(abbreviation, "IPSec") == 0)
			addAbbreviation("IP", false);

		// If GTSM is set, the TTL also needs to be set
		else if (strcasecmp(abbreviation, "GTSM") == 0)
			addAbbreviation("TTL", false);

		// If ICMPv6 is set, the IP also needs to be set
		else if (strcasecmp(abbreviation, "ICMPv6") == 0)
			addAbbreviation("IP", false);

		// If Citrix-ICA is set, then ICA needs to be set
		else if (strcasecmp(abbreviation, "Citrix-ICA") == 0)
			addAbbreviation("ICA", false);

		// If VTP is set, then VLAN needs to be set
		else if (strcasecmp(abbreviation, "VTP") == 0)
			addAbbreviation("VLAN", false);

		// If VRF is set, then VPN needs to be set
		else if (strcasecmp(abbreviation, "VRF") == 0)
			addAbbreviation("VPN", false);

		// If AAL is set, then ATM needs to be set
		else if (strcasecmp(abbreviation, "AAL") == 0)
			addAbbreviation("ATM", false);

		// If dCEF is set, then CEF needs to be set
		else if (strcasecmp(abbreviation, "dCEF") == 0)
			addAbbreviation("CEF", false);

		// ACL and ACE Plaural
		if (strcmp(abbreviation, "ACLs") == 0)
			return addAbbreviation("ACL", expand);
		else if (strcmp(abbreviation, "ACEs") == 0)
			return addAbbreviation("ACE", expand);

		// VIP Plaural
		else if (strcmp(abbreviation, "VIPs") == 0)
			return addAbbreviation("VIP", expand);

		// VLAN Plaural
		else if (strcmp(abbreviation, "VLANs") == 0)
			return addAbbreviation("VLAN", expand);

		// EGP Plaural
		else if (strcmp(abbreviation, "EGPs") == 0)
			return addAbbreviation("EGP", expand);

		// IGP Plaural
		else if (strcmp(abbreviation, "IGPs") == 0)
			return addAbbreviation("IGP", expand);

		// If not DOS or DoS...
		else if ((strcmp(abbreviation, "DoS") != 0) && (strcmp(abbreviation, "DOS") != 0))
		{
			// Search for abbreviation
			abbrevPointer = &ab_append;
			while ((abbrevPointer->next != 0) && (strcasecmp(abbrevPointer->ab, abbreviation) != 0))
				abbrevPointer = abbrevPointer->next;

			// If found, set enabled and expanded
			if (strcasecmp(abbrevPointer->ab, abbreviation) == 0)
			{
				// Add to abbreviation list
				abbrevPointer->add = true;

				// Expand abbreviation in the text?
				if ((expand == true) && (abbrevPointer->expanded == false))
				{
					abbrevPointer->expanded = true;
					return abbrev_expand;
				}
				else
					return abbrev_found;
			}
		}
		else
		{
			// Search for abbreviation
			abbrevPointer = &ab_append;
			while ((abbrevPointer->next != 0) && (strcmp(abbrevPointer->ab, abbreviation) != 0))
				abbrevPointer = abbrevPointer->next;

			// If found, set enabled and expanded
			if (strcmp(abbrevPointer->ab, abbreviation) == 0)
			{
				// Add to abbreviation list
				abbrevPointer->add = true;

				// Expand abbreviation in the text?
				if ((expand == true) && (abbrevPointer->expanded == false))
				{
					abbrevPointer->expanded = true;
					return abbrev_expand;
				}
				else
					return abbrev_found;
			}
		}

		// Not found
		addAbbrevNotFound(abbreviation);
		return abbrev_notfound;
	}
	else
		return abbrev_notfound;
}


// Returns the expanded abbreviation text.
const char *getAbbreviation(char *abbreviation)
{
	// Variables
	struct abbrev *abbrevPointer = 0;

	// If not DOS or DoS...
	if ((strcmp(abbreviation, "DoS") != 0) && (strcmp(abbreviation, "DOS") != 0))
	{
		// Search for abbreviation
		abbrevPointer = &ab_append;
		while ((abbrevPointer->next != 0) && (strcasecmp(abbrevPointer->ab, abbreviation) != 0))
			abbrevPointer = abbrevPointer->next;

		// if found, return
		if (strcasecmp(abbrevPointer->ab, abbreviation) == 0)
			return abbrevPointer->desc;
		else
			return 0;
	}
	else
	{
		// Search for abbreviation
		abbrevPointer = &ab_append;
		while ((abbrevPointer->next != 0) && (strcmp(abbrevPointer->ab, abbreviation) != 0))
			abbrevPointer = abbrevPointer->next;

		// if found, return
		if (strcmp(abbrevPointer->ab, abbreviation) == 0)
			return abbrevPointer->desc;
		else
			return 0;
	}
}


// ----------------------------------------------------------------------------------
// Glossary...




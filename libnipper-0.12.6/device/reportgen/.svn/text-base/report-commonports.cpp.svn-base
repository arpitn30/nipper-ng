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

struct ports
{
	bool add;				// true or false
	const char *text;
	int port;				// Port Number
	//bool tcp;				// true for TCP, false for UDP
	struct ports *next;
};

// Current: 93
//                         ADD    DESCRIPTION          PORT   PROTOCOL
// ====================================================================
struct ports ap_port91  = {false, "PCAnywhere-Status", 5632, 0};
struct ports ap_port90  = {false, "PCAnywhere-Data",   5631, &ap_port91};
struct ports ap_port89  = {false, "SecureID-UDP",      5510, &ap_port90};
struct ports ap_port88  = {false, "AOL",               5190, &ap_port89};
struct ports ap_port87  = {false, "CTIQBE",            2748, &ap_port88};
struct ports ap_port86  = {false, "PPTP",              1723, &ap_port87};
struct ports ap_port85  = {false, "H323",              1720, &ap_port86};
struct ports ap_port84  = {false, "RADIUS-Acct",       1646, &ap_port85};
struct ports ap_port83  = {false, "RADIUS",            1645, &ap_port84};
struct ports ap_port82  = {false, "SQLNet",            1521, &ap_port83};
struct ports ap_port81  = {false, "Citrix-ICA",        1494, &ap_port82};
struct ports ap_port80  = {false, "LotusNotes",        1352, &ap_port81};
struct ports ap_port79  = {false, "KERBEROS",           750, &ap_port80};
struct ports ap_port78  = {false, "LDAPS",              636, &ap_port79};
struct ports ap_port77  = {false, "KShell",             544, &ap_port78};
struct ports ap_port76  = {false, "KLogin",             543, &ap_port77};
struct ports ap_port75  = {false, "UUCP",               540, &ap_port76};
struct ports ap_port74  = {false, "Timed",              525, &ap_port75};
struct ports ap_port73  = {false, "RIPv2",              520, &ap_port74};
struct ports ap_port72  = {false, "RIP",                520, &ap_port73};
struct ports ap_port71  = {false, "Talk",               517, &ap_port72};
struct ports ap_port70  = {false, "LPD",                515, &ap_port71};
struct ports ap_port69  = {false, "Printer",            515, &ap_port70};
struct ports ap_port68  = {false, "Syslog",             514, &ap_port69};
struct ports ap_port67  = {false, "CMD",                514, &ap_port68};
struct ports ap_port66  = {false, "RSH",                514, &ap_port67};
struct ports ap_port65  = {false, "RWho",               513, &ap_port66};
struct ports ap_port64  = {false, "Who",                513, &ap_port65};
struct ports ap_port63  = {false, "RLogin",             513, &ap_port64};
struct ports ap_port62  = {false, "Login",              513, &ap_port63};
struct ports ap_port61  = {false, "RExec",              512, &ap_port62};
struct ports ap_port60  = {false, "Exec",               512, &ap_port61};
struct ports ap_port59  = {false, "BIFF",               512, &ap_port60};
struct ports ap_port58  = {false, "IKE",                500, &ap_port59};
struct ports ap_port57  = {false, "ISAKMP",             500, &ap_port58};
struct ports ap_port56  = {false, "PIM-Auto-RP",        496, &ap_port57};
struct ports ap_port55  = {false, "HTTPS",              443, &ap_port56};
struct ports ap_port54  = {false, "Mobile-IP",          434, &ap_port55};
struct ports ap_port53  = {false, "LDAP",               389, &ap_port54};
struct ports ap_port52  = {false, "DNSIX",              195, &ap_port53};
struct ports ap_port51  = {false, "IRC",                194, &ap_port52};
struct ports ap_port50  = {false, "BGP",                179, &ap_port51};
struct ports ap_port49  = {false, "XDMCP",              177, &ap_port50};
struct ports ap_port48  = {false, "SNMP-Trap",          162, &ap_port49};
struct ports ap_port47  = {false, "SNMP",               161, &ap_port48};
struct ports ap_port46  = {false, "IMAP4",              143, &ap_port47};
struct ports ap_port45  = {false, "NetBIOS-SSN",        139, &ap_port46};
struct ports ap_port44  = {false, "NetBIOS-DGM",        138, &ap_port45};
struct ports ap_port43  = {false, "NetBIOS-NS",         137, &ap_port44};
struct ports ap_port41  = {false, "NTP",                123, &ap_port43};
struct ports ap_port40  = {false, "NNTP",               119, &ap_port41};
struct ports ap_port39  = {false, "UUCP-Path",          117, &ap_port40};
struct ports ap_port38  = {false, "Auth",               113, &ap_port39};
struct ports ap_port37  = {false, "Ident",              113, &ap_port38};
struct ports ap_port36  = {false, "SUNRPC",             111, &ap_port37};
struct ports ap_port35  = {false, "POP3",               110, &ap_port36};
struct ports ap_port34  = {false, "POP2",               109, &ap_port35};
struct ports ap_port33  = {false, "X400-SND",           104, &ap_port34};
struct ports ap_port32  = {false, "X400",               103, &ap_port33};
struct ports ap_port31  = {false, "ISO-TSAP",           102, &ap_port32};
struct ports ap_port30  = {false, "Hostname",           101, &ap_port31};
struct ports ap_port29  = {false, "SUPDUP",              95, &ap_port30};
struct ports ap_port28  = {false, "HTTP",                80, &ap_port29};
struct ports ap_port27  = {false, "WWW",                 80, &ap_port28};
struct ports ap_port26  = {false, "Finger",              79, &ap_port27};
struct ports ap_port25  = {false, "Gopher",              70, &ap_port26};
struct ports ap_port24  = {false, "TFTP",                69, &ap_port25};
struct ports ap_port23  = {false, "BOOTPC",              68, &ap_port24};
struct ports ap_port22  = {false, "DHCP",                68, &ap_port23};
struct ports ap_port21  = {false, "DHCP",                67, &ap_port22};
struct ports ap_port20  = {false, "BOOTPS",              67, &ap_port21};
struct ports ap_port19  = {false, "Domain",              53, &ap_port20};
struct ports ap_port18  = {false, "Login",               49, &ap_port19};
struct ports ap_port17  = {false, "TACACS",              49, &ap_port18};
struct ports ap_port16  = {false, "Nicname",             43, &ap_port17};
struct ports ap_port15  = {false, "Whois",               43, &ap_port16};
struct ports ap_port14  = {false, "Nameserver",          42, &ap_port15};
struct ports ap_port13  = {false, "RLP",                 39, &ap_port14};
struct ports ap_port12  = {false, "Time",                37, &ap_port13};
struct ports ap_port11  = {false, "SMTP",                25, &ap_port12};
struct ports ap_port10  = {false, "Telnet",              23, &ap_port11};
struct ports ap_port93  = {false, "SFTP",                22, &ap_port10};
struct ports ap_port92  = {false, "SSH",                 22, &ap_port93};
struct ports ap_port9   = {false, "FTP",                 21, &ap_port92};
struct ports ap_port8   = {false, "FTP-Data",            20, &ap_port9};
struct ports ap_port7   = {false, "Chargen",             19, &ap_port8};
struct ports ap_port6   = {false, "Quote",               17, &ap_port7};
struct ports ap_port5   = {false, "Netstat",             15, &ap_port6};
struct ports ap_port4   = {false, "Daytime",             13, &ap_port5};
struct ports ap_port3   = {false, "Users",               11, &ap_port4};
struct ports ap_port2   = {false, "Discard",              9, &ap_port3};
struct ports ap_port1   = {false, "Echo",                 7, &ap_port2};
struct ports ap_port    = {false, "AH",                   5, &ap_port1};


void Device::addPort(const char *portDescription)
{
	// Variables
	struct ports *portPointer = 0;

	// Search for abbreviation
	portPointer = &ap_port;
	while ((portPointer->next != 0) && (strcasecmp(portPointer->text, portDescription) != 0))
		portPointer = portPointer->next;

	// If found, add port
	if (strcasecmp(portPointer->text, portDescription) == 0)
		portPointer->add = true;
}


int Device::getPort(const char *portDescription)
{
	// Variables
	struct ports *portPointer = 0;

	// Search for abbreviation
	portPointer = &ap_port;
	while ((portPointer->next != 0) && (strcasecmp(portPointer->text, portDescription) != 0))
		portPointer = portPointer->next;

	// If found, add port
	if (strcasecmp(portPointer->text, portDescription) == 0)
	{
		//printf("service: %s (%d)\n", portDescription, portPointer->port);
		return portPointer->port;
	}

	return 0;
}


int Device::generateAppendixCommonPorts()
{
	// Variables...
	configReportStruct *configPointer = 0;
	struct ports *portPointer = 0;
	paragraphStruct *paragraphPointer = 0;
	bodyStruct *bodyPointer = 0;
	string tempString;
	bool generateSection = false;
	int errorCode = 0;

	// Determine if any are used...
	portPointer = &ap_port;
	while ((portPointer->next != 0) && (generateSection == false))
	{
		if (portPointer->add == true)
			generateSection = true;
		else
			portPointer = portPointer->next;
	}

	// Generate Common Ports appendix section...
	if (generateSection == true)
	{
		configPointer = getAppendixSection("APPENDIX-PORTS");
		configPointer->title = i18n("Common Network Ports");
		paragraphPointer = addParagraph(configPointer);
		errorCode = addTable(paragraphPointer, "APPENDIX-PORTS-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("Common network ports");
		addTableHeading(paragraphPointer->table, i18n("Port"), false);
		addTableHeading(paragraphPointer->table, i18n("Network Service"), false);
		while (portPointer != 0)
		{
			if (portPointer->add == true)
			{
				tempString.assign(intToString(portPointer->port));
				bodyPointer = addTableData(paragraphPointer->table, tempString.c_str());
				bodyPointer = addTableData(paragraphPointer->table, portPointer->text);
			}
			portPointer = portPointer->next;
		}
	}

	return errorCode;
}


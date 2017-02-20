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


struct icmpType
{
	bool show;					// Show the entry
	unsigned int type;			// ICMP no.
	int code;					// ICMP no. code
	const char *internal;		// Internal Name/Literal
	const char *description;	// Description
	const char *rfc;			// RFC
	struct icmpType *next;
};

struct icmpType icmpList58 = {false, 40,  5, "", "Need Authorization", "2521", 0};
struct icmpType icmpList57 = {false, 40,  4, "", "Need Authentication", "2521", &icmpList58};
struct icmpType icmpList56 = {false, 40,  3, "", "Decryption Failed", "2521", &icmpList57};
struct icmpType icmpList55 = {false, 40,  2, "", "Decompression Failed", "2521", &icmpList56};
struct icmpType icmpList54 = {false, 40,  1, "", "Authentication Failed", "2521", &icmpList55};
struct icmpType icmpList53 = {false, 40,  0, "", "Bad SPI", "2521", &icmpList54};
struct icmpType icmpList52 = {false, 40, -1, "", "Photuris", "2521", &icmpList53};
struct icmpType icmpList51 = {false, 39, -1, "", "SKIP", "", &icmpList52};
struct icmpType icmpList50 = {false, 38, -1, "", "Domain Name Reply", "1788", &icmpList51};
struct icmpType icmpList49 = {false, 37, -1, "", "Domain Name Request", "1788", &icmpList50};
struct icmpType icmpList48 = {false, 36, -1, "", "Mobile Registration Reply", "", &icmpList49};
struct icmpType icmpList47 = {false, 35, -1, "", "Mobile Registration Request", "", &icmpList48};
struct icmpType icmpList46 = {false, 34, -1, "", "*ABBREV*IPv6*-ABBREV* I-Am-Here", "", &icmpList47};
struct icmpType icmpList45 = {false, 33, -1, "", "*ABBREV*IPv6*-ABBREV* Where-Are-You", "", &icmpList46};
struct icmpType icmpList44 = {false, 32, -1, "mobile-redirect", "Mobile Host Redirect", "", &icmpList45};
struct icmpType icmpList43 = {false, 31, -1, "conversion-error", "Datagram Conversion Error", "1475", &icmpList44};
struct icmpType icmpList42 = {false, 30, -1, "", "Traceroute", "1393", &icmpList43};
struct icmpType icmpList41 = {false, 18, -1, "mask-reply", "Address Mask Reply", "950", &icmpList42};
struct icmpType icmpList40 = {false, 17, -1, "mask-request", "Address Mask Request", "950", &icmpList41};
struct icmpType icmpList39 = {false, 16, -1, "information-reply", "Information Reply", "792", &icmpList40};
struct icmpType icmpList38 = {false, 15, -1, "information-request", "Information Request", "792", &icmpList39};
struct icmpType icmpList37 = {false, 14, -1, "timestamp-reply", "Timestamp Reply", "792", &icmpList38};
struct icmpType icmpList36 = {false, 13, -1, "timestamp-request", "Timestamp Request", "792", &icmpList37};
struct icmpType icmpList35 = {false, 12,  2, "parameter-problem", "Bad Length", "1108", &icmpList36};
struct icmpType icmpList34 = {false, 12,  1, "parameter-problem", "Missing a Required Option", "1108", &icmpList35};
struct icmpType icmpList33 = {false, 12,  0, "parameter-problem", "Pointer Indicates the Error", "792", &icmpList34};
struct icmpType icmpList32 = {false, 12, -1, "parameter-problem", "Parameter Problem", "792", &icmpList33};
struct icmpType icmpList31 = {false, 11,  1, "time-exceeded", "Fragment Reassembly Time Exceeded", "792", &icmpList32};
struct icmpType icmpList30 = {false, 11,  0, "time-exceeded", "Time to Live Exceeded in Transit", "792", &icmpList31};
struct icmpType icmpList29 = {false, 11, -1, "time-exceeded", "Time Exceeded", "792", &icmpList30};
struct icmpType icmpList28 = {false, 10, -1, "router-solicitation", "Router Solicitation", "1256", &icmpList29};
struct icmpType icmpList27 = {false,  9, 16, "router-advertisement", "Does Not Route Common Traffic", "2002", &icmpList28};
struct icmpType icmpList26 = {false,  9,  0, "router-advertisement", "Router Advertisement", "1256", &icmpList27};
struct icmpType icmpList25 = {true ,  8, -1, "echo", "Echo", "792", &icmpList26};
struct icmpType icmpList24 = {false,  6, -1, "alternate-address", "Alternate Host Address", "792", &icmpList25};
struct icmpType icmpList23 = {false,  5,  3, "redirect", "Redirect Datagram for the Type of Service and Host", "792", &icmpList24};
struct icmpType icmpList22 = {false,  5,  2, "redirect", "Redirect Datagram for the Type of Service and Network", "792", &icmpList23};
struct icmpType icmpList21 = {false,  5,  1, "redirect", "Redirect Datagram for the Host", "792", &icmpList22};
struct icmpType icmpList20 = {false,  5,  0, "redirect", "Redirect Datagram for the Network (or subnet)", "792", &icmpList21};
struct icmpType icmpList19 = {false,  5, -1, "redirect", "Redirect", "792", &icmpList20};
struct icmpType icmpList18 = {false,  4, -1, "source-quench", "Source Quench", "792", &icmpList19};
struct icmpType icmpList17 = {false,  3, 15, "unreachable", "Precedence Cutoff in Effect", "1812", &icmpList18};
struct icmpType icmpList16 = {false,  3, 14, "unreachable", "Host Precedence Violation", "1812", &icmpList17};
struct icmpType icmpList15 = {false,  3, 13, "unreachable", "Communication Administratively Prohibited", "1812", &icmpList16};
struct icmpType icmpList14 = {false,  3, 12, "unreachable", "Destination Host Unreachable for Type of Service", "1122", &icmpList15};
struct icmpType icmpList13 = {false,  3, 11, "unreachable", "Destination Network Unreachable for Type of Service", "1122", &icmpList14};
struct icmpType icmpList12 = {false,  3, 10, "unreachable", "Communication with Destination Host is Administratively Prohibited", "1122", &icmpList13};
struct icmpType icmpList11 = {false,  3,  9, "unreachable", "Communication with Destination Network is Administratively Prohibited", "1122", &icmpList12};
struct icmpType icmpList10 = {false,  3,  8, "unreachable", "Source Host Isolated", "1122", &icmpList11};
struct icmpType icmpList9  = {false,  3,  7, "unreachable", "Destination Host Unknown", "1122", &icmpList10};
struct icmpType icmpList8  = {false,  3,  6, "unreachable", "Destination Network Unknown", "1122", &icmpList9};
struct icmpType icmpList7  = {false,  3,  5, "unreachable", "Source Route Failed", "792", &icmpList8};
struct icmpType icmpList6  = {false,  3,  4, "unreachable", "Fragementation Needed", "792", &icmpList7};
struct icmpType icmpList5  = {false,  3,  3, "unreachable", "Port Unreachable", "792", &icmpList6};
struct icmpType icmpList4  = {false,  3,  2, "unreachable", "Protocol Unreachable", "792", &icmpList5};
struct icmpType icmpList3  = {false,  3,  1, "unreachable", "Host Unreachable", "792", &icmpList4};
struct icmpType icmpList2  = {false,  3,  0, "unreachable", "Net Unreachable", "792", &icmpList3};
struct icmpType icmpList1  = {false,  3, -1, "unreachable", "Destination Unreachable", "792", &icmpList2};
struct icmpType icmpList   = {true ,  0, -1, "echo-reply", "Echo Reply", "792", &icmpList1};


void Device::addICMPType(unsigned int type, int code)
{
	// Variables
	struct icmpType *icmpTypePointer = 0;

	// Search
	icmpTypePointer = &icmpList;
	while (icmpTypePointer->next != 0)
	{
		if ((icmpTypePointer->type == type) && ((code == -1) || (icmpTypePointer->code == code)))
			icmpTypePointer->show = true;
		icmpTypePointer = icmpTypePointer->next;
	}
}
void Device::addICMPType(const char *name, int code)
{
	// Variables
	struct icmpType *icmpTypePointer = 0;

	// Search
	icmpTypePointer = &icmpList;
	while (icmpTypePointer->next != 0)
	{
		if ((strcmp(icmpTypePointer->internal, name) == 0) && ((code == -1) || (icmpTypePointer->code == code)))
			icmpTypePointer->show = true;
		icmpTypePointer = icmpTypePointer->next;
	}
}


const char *Device::getICMPName(unsigned int type)
{
	// Variables
	struct icmpType *icmpTypePointer = 0;

	// Search
	icmpTypePointer = &icmpList;
	while (icmpTypePointer->next != 0)
	{
		if (icmpTypePointer->type == type)
			return icmpTypePointer->internal;
		else
			icmpTypePointer = icmpTypePointer->next;
	}

	// If not found
	return "";
}


const char *Device::getICMPType(unsigned int type, int code)
{
	// Variables
	struct icmpType *icmpTypePointer = 0;

	// Search
	icmpTypePointer = &icmpList;
	while (icmpTypePointer->next != 0)
	{
		if ((icmpTypePointer->type == type) && ((code == -1) || (icmpTypePointer->code == code)))
			return icmpTypePointer->description;
		else
			icmpTypePointer = icmpTypePointer->next;
	}

	// If not found
	return "Reserved/Unused";
}
const char *Device::getICMPType(const char *name, int code)
{
	// Variables
	struct icmpType *icmpTypePointer = 0;

	// Search
	icmpTypePointer = &icmpList;
	while (icmpTypePointer->next != 0)
	{
		if ((strcmp(icmpTypePointer->internal, name) == 0) && ((code == -1) || (icmpTypePointer->code == code)))
			return icmpTypePointer->description;
		else
			icmpTypePointer = icmpTypePointer->next;
	}

	// If not found
	return "Reserved/Unused";
}


int Device::generateAppendixUsedICMPTypes()
{
	// Variables...
	configReportStruct *configPointer = 0;
	struct icmpType *icmpTypePointer = 0;
	paragraphStruct *paragraphPointer = 0;
	bodyStruct *bodyPointer = 0;
	string tempString;
	bool generateSection = false;
	int errorCode = 0;

	// Determine if any are used...
	icmpTypePointer = &icmpList;
	while ((icmpTypePointer->next != 0) && (generateSection == false))
	{
		if (icmpTypePointer->show == true)
			generateSection = true;
		else
			icmpTypePointer = icmpTypePointer->next;
	}

	// Generate appendix section...
	if (generateSection == true)
	{
		configPointer = getAppendixSection("APPENDIX-ICMPTYPES");
		configPointer->title = i18n("*ABBREV*ICMP*-ABBREV* Types");
		paragraphPointer = addParagraph(configPointer);
		errorCode = addTable(paragraphPointer, "APPENDIX-ICMPTYPES-TABLE");
		if (errorCode != 0)
			return errorCode;
		paragraphPointer->table->title = i18n("*ABBREV*ICMP*-ABBREV* types");
		addTableHeading(paragraphPointer->table, i18n("Type"), false);
		addTableHeading(paragraphPointer->table, i18n("Code"), false);
		addTableHeading(paragraphPointer->table, i18n("Description"), false);
		addTableHeading(paragraphPointer->table, i18n("RFC"), false);
		while (icmpTypePointer != 0)
		{
			if (icmpTypePointer->show == true)
			{
				tempString.assign(intToString(icmpTypePointer->type));
				bodyPointer = addTableData(paragraphPointer->table, tempString.c_str());
				if (icmpTypePointer->code != -1)
				{
					tempString.assign(intToString(icmpTypePointer->code));
					bodyPointer = addTableData(paragraphPointer->table, tempString.c_str());
				}
				else
					bodyPointer = addTableData(paragraphPointer->table, "");
				bodyPointer = addTableData(paragraphPointer->table, icmpTypePointer->description);
				tempString.assign("RFC");
				tempString.append(icmpTypePointer->rfc);
				bodyPointer = addTableData(paragraphPointer->table, tempString.c_str());
			}
			icmpTypePointer = icmpTypePointer->next;
		}
	}

	return errorCode;
}


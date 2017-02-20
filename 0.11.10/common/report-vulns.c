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

#define vuln_req_none 0
#define vuln_req_telnet 1
#define vuln_req_http 2
#define vuln_req_ssh 3
#define vuln_req_tacacs 4
#define vuln_req_tftp 5
#define vuln_req_ospf 6

struct vulnerability
{
	int startVersionMajor;				// Vuln Version from...
	int startVersionMinor;
	int startVersionRevision;
	int endVersionMajor;				// Vuln Version to...
	int endVersionMinor;
	int endVersionRevision;
	char *cve;							// CVE
	char *bid;							// BID
	char *description;					// Description
	int dos;							// Is it a DoS?
	int remote;							// Is it remote code execution?
	int require;						// Requirement (e.g. vuln_req_http)
	int include;						// Include vulnerability?
	struct vulnerability *next;
};

// IOS Vulnerabilities
struct vulnerability report_vuln_ios12 = {12, 0, 0, 12, 4, 0,
                                          "CVE-2007-0480", "22211",
                                          "Crafted IPv4 option remote code execution",
                                          true, true,
                                          vuln_req_none, false, 0};
struct vulnerability report_vuln_ios11 = {9, 0, 0, 12, 4, 0,
                                          "CVE-2007-0479", "22208",
                                          "IPv4 TCP listener denial of service",
                                          true, false,
                                          vuln_req_none, false, &report_vuln_ios12};
struct vulnerability report_vuln_ios10 = {9, 0, 0, 12, 3, 9,
                                          "CVE-2004-1464", "11060",
                                          "Telnet remote denial of service",
                                          true, false,
                                          vuln_req_telnet, false, &report_vuln_ios11};
struct vulnerability report_vuln_ios9  = {12, 0, 0, 12, 1, 0,
                                          "-", "10014",
                                          "HTTP malformed request denial of service",
                                          true, false,
                                          vuln_req_http, false, &report_vuln_ios10};
struct vulnerability report_vuln_ios8  = {10, 3, 3, 12, 2, 17,
                                          "CVE-2003-0647", "8373",
                                          "2GB HTTP GET buffer overflow",
                                          false, true,
                                          vuln_req_http, false, &report_vuln_ios9};
struct vulnerability report_vuln_ios7  = {11, 1, 0, 12, 0, 7,
                                          "CVE-2003-0100", "6895",
                                          "OSPF neighbor buffer overflow",
                                          true, true,
                                          vuln_req_ospf, false, &report_vuln_ios8};
struct vulnerability report_vuln_ios6  = {11, 1, 0, 11, 3, 0,
                                          "CVE-2002-0813", "5328",
                                          "TFTP server long file name buffer overflow",
                                          true, true,
                                          vuln_req_tftp, false, &report_vuln_ios7};
struct vulnerability report_vuln_ios5  = {12, 0, 0, 12, 2, 0,
                                          "CVE-2002-1024", "5114",
                                          "SSH denial of service",
                                          true, false,
                                          vuln_req_ssh, false, &report_vuln_ios6};
struct vulnerability report_vuln_ios4  = {11, 3, 0, 12, 2, 0,
                                          "CVE-2001-0537", "2936",
                                          "HTTP configuration arbitrary administrative access",
                                          false, true,
                                          vuln_req_http, false, &report_vuln_ios5};
struct vulnerability report_vuln_ios3  = {12, 0, 0, 12, 1, 0,
                                          "CVE-2000-0984", "1838",
                                          "?/ HTTP request denial of service",
                                          true, false,
                                          vuln_req_http, false, &report_vuln_ios4};
struct vulnerability report_vuln_ios2  = {11, 1, 0, 12, 0, 7,
                                          "CVE-2000-0380", "1154",
                                          "HTTP %% vulnerability",
                                          true, false,
                                          vuln_req_http, false, &report_vuln_ios3};
struct vulnerability report_vuln_ios1  = {11, 3, 0, 12, 0, 7,
                                          "CVE-2000-0268", "1123",
                                          "Telnet option handling vulnerability",
                                          true, false,
                                          vuln_req_telnet, false, &report_vuln_ios2};
struct vulnerability report_vuln_ios   = {9, 1, 0, 11, 3, 1,
                                          "-", "692",
                                          "Remote denial of service",
                                          true, false,
                                          vuln_req_none, false, &report_vuln_ios1};

// PIX Vulnerabilities
struct vulnerability report_vuln_pix3  = {7, 2, 2, 7, 2, 2,
                                          "CVE-2007-0962", "22562",
                                          "Privilege escalation",
                                          false, false,
                                          vuln_req_none, false, 0};
struct vulnerability report_vuln_pix2  = {6, 3, 0, 7, 0, 5,
                                          "CVE-2007-0962", "22561",
                                          "Multiple remote denial of service",
                                          true, false,
                                          vuln_req_none, false, &report_vuln_pix3};
struct vulnerability report_vuln_pix1  = {5, 2, 0, 6, 2, 0,
                                          "CVE-2002-1024", "5114",
                                          "SSH denial of service",
                                          true, false,
                                          vuln_req_ssh, false, &report_vuln_pix2};
struct vulnerability report_vuln_pix   = {4, 0, 0, 5, 3, 0,
                                          "CVE-2001-0375", "2551",
                                          "TACACS+ denial of service",
                                          true, false,
                                          vuln_req_tacacs, false, &report_vuln_pix1};

// FWSM Vulnerabilities
struct vulnerability report_vuln_fwsm2  = {3, 2, 3, 3, 2, 3,
                                           "CVE-2007-5584", "",
                                           "******************************",
                                           false, false,
                                           vuln_req_none, false, 0};
struct vulnerability report_vuln_fwsm1  = {2, 3, 0, 3, 1, 3,
                                           "CVE-2007-0962", "22561",
                                           "Multiple remote denial of service issues",
                                           true, false,
                                           vuln_req_none, false, 0};
struct vulnerability report_vuln_fwsm   = {1, 1, 2, 1, 1, 2,
                                           "-", "9222",
                                           "Multiple HTTP vulnerabilities",
                                           false, true,
                                           vuln_req_http, false, &report_vuln_fwsm1};

// CatOS / NMP
struct vulnerability report_vuln_nmp4   = {7, 5, 1, 7, 5, 1,
                                          "-", "7424",
                                          "Authentication bypass vulnerability",
                                          false, true,
                                          vuln_req_ssh, false, 0};
struct vulnerability report_vuln_nmp3   = {5, 3, 1, 7, 1, 2,
                                          "CVE-2002-1024", "5114",
                                          "SSH denial of service",
                                          true, false,
                                          vuln_req_ssh, false, &report_vuln_nmp4};
struct vulnerability report_vuln_nmp2   = {4, 5, 2, 7, 1, 0,
                                           "CVE-2001-0554", "3064",
                                           "Telnet buffer overflow",
                                           false, true,
                                           vuln_req_telnet, false, &report_vuln_nmp3};
struct vulnerability report_vuln_nmp1   = {6, 1, 1, 6, 1, 1,
                                           "CVE-2001-0080", "2117",
                                           "SSH protocol mismatch denial of service",
                                           false, false,
                                           vuln_req_ssh, false, &report_vuln_nmp2};
struct vulnerability report_vuln_nmp    = {5, 4, 1, 5, 4, 1,
                                           "CVE-2000-0267", "1122",
                                           "Enable password bypass vulnerability",
                                           false, false,
                                           vuln_req_none, false, &report_vuln_nmp1};

// Check Vulnerability OS Versions
void checkVulnVersion(struct nipperConfig *nipper, struct vulnerability *vulnPointer)
{
	// Check to see if it is older...
	if ((nipper->versionMajor < vulnPointer->startVersionMajor) || ((nipper->versionMajor == vulnPointer->startVersionMajor) && (nipper->versionMinor < vulnPointer->startVersionMinor)))
		return;

	// Check to see if it is newer...
	if ((nipper->versionMajor > vulnPointer->endVersionMajor) || ((nipper->versionMajor == vulnPointer->endVersionMajor) && (nipper->versionMinor > vulnPointer->endVersionMinor)))
		return;

	if ((nipper->deviceType != type_ios_router) && (nipper->deviceType != type_ios_switch) && (nipper->deviceType != type_ios_catalyst))
	{
		// Check to see if revision is older...
		if ((nipper->versionMajor == vulnPointer->startVersionMajor) && (nipper->versionMinor == vulnPointer->startVersionMinor) && (nipper->versionRevision < vulnPointer->startVersionRevision))
			return;

		// Check to see if revision is newer...
		if ((nipper->versionMajor == vulnPointer->endVersionMajor) && (nipper->versionMinor == vulnPointer->endVersionMinor) && (nipper->versionRevision > vulnPointer->endVersionRevision))
			return;
	}

	// Set counters...
	nipper->vulnIssues++;					// Vuln counter
	vulnPointer->include = true;			// Include Vuln
	if (vulnPointer->dos == true)			// Is it a DoS?
		nipper->vulnIssueDos = true;
	if (vulnPointer->remote == true)		// Is it a Remote?
		nipper->vulnIssueRemote = true;
}

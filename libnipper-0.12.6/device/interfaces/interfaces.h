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

#ifndef deviceInterfaces_H
#define deviceInterfaces_H


#include "../common/deviceconfig.h"


class Interfaces : public DeviceConfig
{
	public:

		Interfaces();
		virtual ~Interfaces();

	// -----------------------------------------------------------------------
	// Standard Device Class Methods...
	// -----------------------------------------------------------------------

		int generateConfigReport(Device *device);
		int generateSecurityReport(Device *device);


	// -----------------------------------------------------------------------
	// Interfaces...
	// -----------------------------------------------------------------------

		enum portMode
		{
			portModeAccess = 0,
			portModeTrunk = 1,
			portModeDynamic = 2
		};

		enum portViolation
		{
			onViolationShutdown = 0,
			onViolationRestrict = 1,
			onViolationProtect = 2
		};

		struct interfaceConfig
		{
			// One of two naming systems (port name or module/port numbers)
			string name;							// Port name (e.g. ethernet1/1)
			int module;
			int port;

			// Basic port settings...
			string zone;							// If the port is assigned a zone / name
			string description;						// If the port has been given a descriptive name/comment
			int securityLevel;						// It the port is assigned a security level
			bool enabled;							// Is the port active/disabled
			string address;							// An address assigned to the port
			string netmask;							// The port netmask
			string standbyAddress;					// Standby address for failover
			bool dhcp;								// If the port uses DHCP instead
			Device::listStruct *vlan;				// A list of VLAN's that the port is a member of

			// Filter settings...
			Device::listStruct *filterIn;			// A list of filterlists assigned to the port
			Device::listStruct *filterOut;			// A list of filterlists assigned to the port

			// Features on interface...
			bool proxyARP;
			bool mop;
			bool ipUnreachables;
			bool ipRedirects;
			bool ipMaskReply;
			bool infoReply;
			string ipDirectBroadcast;
			bool cdp;
			bool ntp;
			bool uRPF;

			// Switchport
			enum portMode switchportMode;
			bool switchportSecurity;
			enum portViolation switchportViolation;

			struct interfaceConfig *next;
		};


		// Global Inteface Options...
		bool cdpSupported;							// Is CDP supported on interfaces
		bool useModuleAndPort;						// Use the module / port instead of the name
		bool useInterfaceZone;						// Use the interface zone
		const char *zoneName;						// The name for zone field
		const char *filterOut;						// The filter out table title text
		const char *filterIn;						// The filter in table title text
		bool showDescription;						// Show the interface description
		bool cdpGlobalRequired;						// If CDP needs to be enabled globally as well
		const char *disableCDPText;					// The text and commands to disable CDP
		const char *disableProxyARPText;			// The text and commands to disable Proxy ARP
		const char *disableUnreachablesText;		// The text and commands to disable ICMP unreachable messages
		bool globalIPUnreachableSupported;			// Globally rather than on interfaces
		bool globalUnreachableEnabled;				// Globally rather than on interfaces
		const char *disableInformationText;			// The text and commands to disable ICMP information messages
		const char *disableMaskText;				// The text and commands to disable ICMP mask messages
		const char *disableRedirectText;			// The text and commands to disable ICMP redirect messages
		bool globalRedirectSupported;				// Globally rather than on interfaces
		bool globalRedirectEnabled;					// Globally rather than on interfaces
		const char *disableDirectedText;			// The text and commands to disable directed broadcasts
		const char *disableMOPText;					// The text and commands to disable MOP
		const char *disableActiveText;				// The text and commands to disable potentially unused interfaces
		const char *filterName;						// The filter list name for use in the filter issue text
		const char *configFilterText;				// The text and commands to configure network filtering
		bool defaultAutoTrunk;						// Default to automatically trunk
		const char *disableTrunkText;				// The text and commands to disable trunking on a port
		const char *enablePortSecurityText;			// The text and commands to enable port security


	// -----------------------------------------------------------------------
	// Interface Lists...
	// -----------------------------------------------------------------------

		struct interfaceListConfig
		{
			// Config report stuff...
			const char *title;						// The Interface lists title used in the configuration report
			const char *description;				// The interface lists description used in the configuration report
			const char *tableTitle;					// The table title used in the report.
			const char *label;						// Used for internal nipper purposes.

			// The interfaces...
			interfaceConfig *interface;				// The actual interfaces

			// The interface list options...
			bool interfaceDisableSupport;			// Is it possible to disable interfaces?
			bool ipAddressSupported;				// Are addresses supported?
			bool vlanSupported;						// Use VLAN
			bool useSecurityLevel;					// Use the security Level field
			bool useStandbyAddress;					// Use the standby address field
			bool proxyArpSupported;					// Is Proxy ARP supported?
			bool mopSupported;						// Is MOP supported?
			bool unreachablesSupported;				// Are IP unreachables supported?
			bool redirectsSupported;				// Are IP redirects supported?
			bool ipMaskReplySupported;				// Are IP mask-replies supported?
			bool informationReplySupported;			// Are IP mask-replies supported?
			bool ipDirectBroadcastSupported;		// Are IP Directed Broadcasts supported?
			bool cdpSupported;						// Is CDP supported?
			bool portModeSupported;					// Is switch port mode supported?
			bool portSecuritySupported;				// Is the switch port security supported (mac-based)?
			bool inboundFilterSupported;			// Is the inbound filtering supported?
			bool outboudFilterSupported;			// Is the outbound filtering supported?

			struct interfaceListConfig *next;
		};

		interfaceListConfig *interfaceList;


		// Interface Methods...
		interfaceConfig *getInterface(interfaceListConfig *interfaceListPointer, const char *name, int module = 0, int port = 0);			// Get / Create an interface
		interfaceConfig *getOnlyInterface(interfaceListConfig *interfaceListPointer, const char *name, int module = 0, int port = 0);		// Get an interface
		interfaceConfig *getInterfaceByZone(interfaceListConfig *interfaceListPointer, const char *zone);									// Get an interface
		int addFilterList(interfaceConfig *interfacePointer, const char *filterList, bool in);												// Add a filter list to the interface
		int addVLAN(interfaceConfig *interfacePointer, const char *vlanName);

		// Interface List Methods...
		interfaceListConfig *addInterfaceList();							// Add a new interface list
		interfaceListConfig *getInterfaceList(const char *label);			// Only gets the interface list


	private:

		int outputInterfaceTableHeadings(Device *device, interfaceListConfig *interfaceListPointer, Device::paragraphStruct *paragraphPointer);
		int outputInterfaceTableRow(Device *device, interfaceListConfig *interfaceListPointer, interfaceConfig *interfacePointer, Device::paragraphStruct *paragraphPointer);
		int outputInterfaceTableExplain(Device *device, interfaceListConfig *interfaceListPointer, Device::paragraphStruct *paragraphPointer);
		int addInterfaceIssue(const char *issueRef, interfaceListConfig *interfaceListPointer, interfaceConfig *interfacePointer);

		struct issueLinksConfig
		{
			interfaceListConfig *interfaceList;
			interfaceConfig *interface;
			struct issueLinksConfig *next;
		};

		issueLinksConfig *cdpIssues;
		issueLinksConfig *proxyARPIssues;
		issueLinksConfig *unreachableIssues;
		issueLinksConfig *informationReplyIssues;
		issueLinksConfig *maskReplyIssues;
		issueLinksConfig *redirectsIssues;
		issueLinksConfig *directedIssues;
		issueLinksConfig *mopIssues;
		issueLinksConfig *activeIssues;
		issueLinksConfig *filterIssues;
		issueLinksConfig *trunkingIssues;
		issueLinksConfig *portSecIssues;
};

#endif

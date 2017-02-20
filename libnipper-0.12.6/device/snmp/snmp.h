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

#ifndef devicesnmp_H
#define devicesnmp_H

#include "../common/deviceconfig.h"
#include <string>

using namespace std;

class Device;

class SNMP : public DeviceConfig
{
  public:
	SNMP();
	virtual ~SNMP();

	enum snmpV3TypeEnum
	{
		snmpV3NoAuth = 0,
		snmpV3Auth = 1,
		snmpV3Priv = 2
	};

	// -----------------------------------------------------------------------
	// Standard Device Class Methods...
	// -----------------------------------------------------------------------

	virtual int generateConfigReport(Device *device);
	virtual int generateSecurityReport(Device *device);



	bool enabled;					// Is the SNMP server enabled?

  protected:

	// -----------------------------------------------------------------------
	// SNMP Protocol Support...
	// -----------------------------------------------------------------------

	const char *deviceSNMPSupportText;		// Intro Config section device specific text.
	bool supportSNMP3;						// Does this device support SNMPv3?
	bool supportSNMP3Upgrade;				// Do you have to upgrade to get support for SNMPv3
	const char *supportSNMP3UpgText;		// SNMP is supported from OS version ...

	// System Specific Commands...
	const char *disableSNMPCmdText;			// The text and command(s) to disable SNMP support
	const char *configSNMPCommunityText;	// The text and command(s) to configure a community string
	const char *configSNMP3Text;			// The text and command(s) to configure SNMP version 3
	const char *configSNMPViewText;			// The text and command(s) to configure SNMP views
	const char *configSNMPTrapsText;		// The text and command(s) to configure SNMP traps
	const char *configSNMPInformsText;		// The text and command(s) to configure SNMP informs
	const char *configSNMPReadOnlyText;		// The text and command(s) to configure SNMP read only access
	const char *configSNMPFilterText;		// The text and command(s) to configure SNMP filtering

	bool snmp12Enabled;				// Is SNMP versions 1 or 2 configured?
	bool snmp3Enabled;				// Is SNMP version 3 configured?
	string location;				// The SNMP location string
	string contact;					// The SNMP contact string
	string chassis;					// The SNMP chassis string
	string name;					// The SNMP device name string
	int listenPort;					// The UDP port SNMP will listen on

	const char *snmpFilterText;		// The device specific description of a filter (i.e. Cisco called them ACL)
	const char *snmpFilterIPv6Text;	// Same for IPv6


	// -----------------------------------------------------------------------
	// SNMP Community Support...
	// -----------------------------------------------------------------------

	// Community Structure...
	enum communityTypeEnum
	{
		communityReadOnly = 0,
		communityReadWrite = 1,
		communityReadWriteAll = 2
	};
	struct snmpCommunity
	{
		bool enabled;				// Community enabled?
		string community;			// Community string
		communityTypeEnum type;		// Community type
		int version;				// SNMP version
		// Device specific...
		string view;				// SNMP view for the community
		string filter;				// Network Filtering
		string ipv6Filter;			// IPv6 Network Filtering
		bool trapsOn;				// Are traps enabled for all hosts
		// Community testing...
		bool communityDefault;		// Is it a default community
		bool communityInDict;		// Is it a dictionary-based community
		Device::weakPasswordEnum communityWeak;		// Is it a weak community
		struct snmpCommunity *next;
	};
	snmpCommunity *community;		// Community

	// Community support options...
	bool communityView;				// SNMP view for the community
	bool communityFilter;			// SNMP Network Filtering
	bool communityIPv6Filter;		// SNMP IPv6 Network Filtering
	bool communitySpecificFilters;	// If the device uses an SNMP specific list. If false, it is std device filters
	bool communityRequiresHosts;	// If the SNMP community will not work without a list of those who can access it

	// Default communities...
	const char *defaultReadOnly;		// Default read only community
	const char *defaultReadWrite;		// Default read/write community
	const char *defaultReadWriteAll;	// Default read/write all community

	// Handling Methods...
	snmpCommunity *addSNMPCommunity();								// Add a new community
	snmpCommunity *getSNMPCommunity(const char *communityString);	// Get an existing community
	snmpCommunity *getSNMPCommunityACL(const char *filterString);	// Get an existing community


	// -----------------------------------------------------------------------
	// SNMP NMS Hosts Support...
	// -----------------------------------------------------------------------

	// Host Structure...
	struct snmpHostStruct
	{
		string filter;				// The filter ID (if configured)
		string community;			// The community
		string interface;			// The device Interface
		string host;				// The NMS Host
		string networkMask;			// The NMS Network Mask
		bool communityInDict;		// Is it a dictionary-based community
		Device::weakPasswordEnum communityWeak;			// Is it a weak community
		struct snmpHostStruct *next;
	};

	snmpHostStruct *snmpHost;		// SNMP Host

	// Host Options...
	bool hostShowInterface;			// Show the Interface in the Table
	bool hostShowCommunity;			// Show the Community in the Table
	bool hostShowFilterID;				// Show a filter ID if used
	const char *hostFilterText;		// The Table column title for the filter text

	snmpHostStruct *addHost();								// Adds an SNMP Host
	snmpHostStruct *getHost(const char *hostName);		// Gets an SNMP Host
	bool hostCommunityExists(const char *community);		// Check Community Host Exists


	// -----------------------------------------------------------------------
	// SNMP View Support...
	// -----------------------------------------------------------------------

	// View Structures...
	struct snmpMIB
	{
		string mib;					// SNMP MIB Object
		bool include;				// Include (true) or Exclude (false)
		struct snmpMIB *next;
	};
	struct snmpView
	{
		string view;				// SNMP view name
		snmpMIB *mib;				// SNMP MIBs
		bool everything;			// Everything is allowed (true)
		struct snmpView *next;
	};

	snmpView *view;					// SNMP View

	// View support options...
	bool viewSeperated;				// Separate the views into different tables
	bool viewExcludes;				// Show the Include/Exclude View Table column
	const char *viewMIBText;		// What the MIB column title in the table should be called

	// Methods...
	int addSNMPView(const char *viewName, const char *mibName, bool include = true);	// Adds a view
	snmpView *getSNMPView(const char *viewName);										// Gets a view


	// -----------------------------------------------------------------------
	// SNMP Trap & Inform Hosts Support...
	// -----------------------------------------------------------------------

	// SNMP Trap/Inform hosts...
	struct snmpTrapHost
	{
		string host;				// SNMP Trap/Inform Host
		bool trap;					// Trap (true) or Inform (false)
		int version;				// SNMP version
		snmpV3TypeEnum snmpv3;		// SNMP version 3 auth type
		string community;			// SNMP Community
		string notification;		// Notification Types
		string eventLevel;			// Event level of the traps
		int port;					// UDP port to send to
		string interface;			// Interface to send the traps/notifications from
		bool communityInDict;		// Is it a dictionary-based community
		Device::weakPasswordEnum communityWeak;			// Is it a weak community
		struct snmpTrapHost *next;
	};

	// SNMP Traps/Informs...
	struct snmpTrap
	{
		string trap;
		string options;
		bool include;
		struct snmpTrap *next;
	};

	snmpTrapHost *trapHost;			// SNMP Trap and Inform Hosts
	snmpTrap *traps;				// SNMP Traps and Informs

	// SNMP Trap/Inform Host Options...
	bool trapsOnly;					// Only Traps are supported
	bool trapsSNMPv3;				// No SNMP v3 support for traps
	bool trapsShowPort;				// Show Trap Host Port in Table
	bool trapsInterface;			// Show Interface in Table
	const char *trapsInterfaceText;	// The Traps/Informs Host Table Interface Column Title
	bool trapsShowNotifications;	// Show Notifications in the Table
	bool trapsShowEventLevel;		// Show Notification Event Level in the Table

	// Traps/Informs Options...
	bool trapsShowExcluded;			// Show excluded traps
	bool trapsShowOptions;			// Show trap options

	snmpTrapHost *addSNMPTrapHost();						// Add a new trap/inform host
	snmpTrapHost *getSNMPTrapHost(const char *hostName);	// Get a trap/inform host
	snmpTrap *addSNMPTrap();								// Add a Trap
	snmpTrap *getSNMPTrap(const char *trapName);			// Get a trap


	// -----------------------------------------------------------------------
	// SNMP Users...
	// -----------------------------------------------------------------------

	enum snmpV3AuthEnum
	{
		snmpV3AuthMD5 = 0,
		snmpV3AuthSHA = 1
	};

	enum snmpV3PrivEnum
	{
		snmpV3PrivDES = 0,
		snmpV3Priv3DES = 1,
		snmpV3PrivAES128 = 2,
		snmpV3PrivAES192 = 3,
		snmpV3PrivAES256 = 4,
	};

	// SNMP Users...
	struct snmpUserStruct
	{
		string user;				// Username
		string group;				// Group membership
		string host;				// SNMP Remote Host
		int port;					// SNMP Remote Host Port
		int version;				// SNMP Version
		snmpV3TypeEnum snmpv3;		// SNMP version 3 auth type
		snmpV3AuthEnum auth;		// Auth Crypto
		string authPassword;		// Auth Password
		snmpV3PrivEnum priv;		// Priv Crypto
		string privPassword;		// Priv Password
		string filter;				// Filter
		string ipv6Filter;			// IPv6 Filter
		struct snmpUserStruct *next;
	};

	snmpUserStruct *snmpUser;		// SNMP User

	// SNMP User Options...
	bool showUserRemote;			// Show the remote host/port setting
	bool showUserPriv;				// Show the privacy settings
	bool showUserFilter;			// Show the Filter column in the table
	bool showUserIPv6Filter;		// Show the IPv6 Filter column in the table
	const char *userFilterText;		// The Text for the Filter table column title
	const char *userIPv6FilterText;	// The Text for the IPv6 Filter table column title

	snmpUserStruct *addSNMPUser();								// Add a user
	snmpUserStruct *getSNMPUser(const char *username);		// Get a user


	// -----------------------------------------------------------------------
	// SNMP Group...
	// -----------------------------------------------------------------------

	// Group structure...
	struct snmpGroupStruct
	{
		string group;					// Group
		int version;					// SNMP Version
		snmpV3TypeEnum snmpv3;			// SNMP version 3 auth type
		string readView;				// Read view
		string writeView;				// Write view
		string notifyView;				// Notify view
		string filter;					// Filter
		string ipv6Filter;				// IPv6 Filter
		struct snmpGroupStruct *next;
	};

	snmpGroupStruct *snmpGroup;		// SNMP Group

	// SNMP Group Options...
	bool snmpGroupShowType;			// Enable/Disable SNMPv3 type in table
	bool snmpGroupReadView;			// Enable/Disable Read Views
	bool snmpGroupWriteView;			// Enable/Disable Write Views
	bool snmpGroupNotifyView;			// Enable/Disable Notify Views
	bool snmpGroupFilter;				// Enable/Disable Filter support
	bool snmpGroupIPv6Filter;			// Enable/Disable IPv6 Filter support
	const char *groupFilterText;		// The Text for the Filter table column title
	const char *groupIPv6FilterText;	// The Text for the IPv6 Filter table column title

	snmpGroupStruct *addSNMPGroup();							// Add a group
	snmpGroupStruct *getSNMPGroup(const char *groupname);		// Get a group


	// -----------------------------------------------------------------------
	// Private Class Processing Methods...
	// -----------------------------------------------------------------------

  private:
		// Config Report...
		int generateCommunityConfigReport(Device *device);		// Generate Community Configuration Report
		int generateHostConfigReport(Device *device);			// Generate Host Configuration Report
		int generateViewConfigReport(Device *device);			// Generate View Configuration Report
		int generateTrapHostConfigReport(Device *device);		// Generate Trap/Inform Host Configuration Report
		int generateGroupConfigReport(Device *device);			// Generate Group Configuration Report
		int generateUserConfigReport(Device *device);			// Generate User Configuration Report

		// Security Issues...
		enum snmpCommunitySec
		{
			communityIssueDefault = 0,
			communityIssueDict = 1,
			communityIssueWeak = 2
		};
		int snmpCommunityIssue(Device *device, snmpCommunitySec communityIssue, int totalCommunityCount = 0, int withWriteCount = 0, int withWriteAllCount = 0);
		int snmpTrapIssue(Device *device, snmpCommunitySec communityIssue, int trapCount, int informCount);
		int snmpWithoutView(Device *device, int noViewCount);
		int snmpWriteAccess(Device *device, int writeCount);
		int snmpWithoutFiltering(Device *device, int filterCount, int nmsFilterCount);
		int snmpClearTextVersion(Device *device, bool writeAccess, bool viewConfigured, bool filteringConfigured);
		int snmpWeakFiltering(Device *device, int accessFromAnySource, int accessFromNetSource);
};

#endif

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

#ifndef Filter_H
#define Filter_H


#include "../common/deviceconfig.h"


class Filter : public DeviceConfig
{
	public:
		Filter();
		virtual ~Filter();

	// -----------------------------------------------------------------------
	// Standard Device Class Methods...
	// -----------------------------------------------------------------------

		virtual int generateConfigReport(Device *device);
		virtual int generateSecurityReport(Device *device);
		virtual int processDefaults(Device *device);


		enum serviceOperType
		{
			serviceOperAny = 0,				// Any
			serviceOperEqual = 1,			// Equal
			serviceOperNotEqual = 2,		// Not Equal
			serviceOperLessThan = 3,		// Less Than
			serviceOperGreaterThan = 4,		// Greater Than
			serviceOperRange = 5			// A Range
		};

	protected:

		virtual int processDeviceSpecificDefaults(Device *device);
		virtual int generateDeviceSpecificFilterSecurityIssues(Device *device);


	// -----------------------------------------------------------------------
	// Objects...
	// -----------------------------------------------------------------------

		enum filterObjectType
		{
			protocol = 0,					// Protocol
			source = 1,						// Source
			sourceService = 2,				// Source Port
			destination = 3,				// Destination
			destinationService = 4,			// Destination Port
			through = 5,					// Through (only if a filter goes through a particular gateway)
			installed = 6,					// Installed (if it is to be applied on a particular gateway)
			timeLimit = 7,					// Time Restricted
			interfaces = 8,					// CheckPoint Gateway interfaces
			members = 9						// CheckPoint members
		};

		enum objectType
		{
			anyObject = 0,					// Any object (can be any type - service, host...)
			networkObject = 1,				// A network object
			protocolObject = 2,				// A protocol object
			icmpObject = 3,					// ICMP object
			serviceObject = 4,
			groupObject = 5,				// Group object (used to point to a list of objects)
			portObject = 6,					// A port object
			hostObject = 7,					// A host object (networks should use the network object)
			machinesRangeObject = 8,		// CheckPoint Machines Range
			dynamicnetObject = 9,			// CheckPoint Dynamic Net
			gatewayObject = 10,				// CheckPoint gateway object
			gatewayClusterObject = 11,		// CheckPoint Gateway cluster object
			clusterMemberObject = 12,		// CheckPoint Cluster Member object
			serviceRangeObject = 13,
			interfaceObject = 14,			// Checkpoint gateway interface object
			timeObject = 15,				// A time object (such as time ranges used within filters)
			addressBookObject = 16,			// An address book (like DNS with name/machine/network resolution)
			enhancedServiceObject = 17,		// An enhanced service object, includes protocol, source and dest ports
			rpcObject = 18,					// An RPC Object (name = rpc (or rpc type), netmask = program id or uuid)
			addressObject = 19,				// An address object that refers to an entry in the address book
			serviceListObject = 20,			// A service list object, similar to the address book for host object types
			otherObject = 21,				// The other object type for CheckPoint devices
			compoundObject = 22,			// CheckPoint compond object (such as user group)
			notSetObject = 100
		};

		// A filter object (used by a filter)
		struct filterObjectConfig
		{
			objectType type;								// Object type
			string label;									// Label, such as those used by name lookups
			string name;									// Name / IP Address / Range Start
			string netmask;									// Netmask / Range end
			string comment;									// Comments
			serviceOperType serviceOper;					// Service Type (equal, range...)
			// The following are used for enhanced objects (such as on ScreenOS)
			struct filterObjectConfig *protocol;			// Protocol (also used on SonicWALL)
			struct filterObjectConfig *sourcePort;			// Source Port
			struct filterObjectConfig *destinationPort;		// Destination Port
			// Used for Checkpoint-based configs...
			bool internal;
			bool firewall;
			bool management;
			int interfaceIndex;
			bool dhcp;
			struct filterObjectConfig *interfaces;
			struct filterObjectConfig *members;

			bool deleteMe;									// Should the object be removed!

			struct filterObjectConfig *next;
		};

		// Net Objects (referenced by a filter)
		struct netObjectListConfig
		{
			objectType type;
			string name;
			string zone;
			bool tcp;
			bool udp;
			string comment;
			const char *title;								// Pointer to the object name text
			const char *description;						// Pointer to the description text
			filterObjectConfig *object;
			bool objectCommentSupported;					// Enabled object comments
			bool protocolSupported;							// Only applies if enhancedServiceObject is not the type
			struct netObjectListConfig *next;
		};

		// Settings...
		const char *networkObjectName;						// The name for the object (used in config report)
		const char *networkObjectDescription;				// The description for the object (config report)
		const char *protocolObjectName;						// The name for the object (used in config report)
		const char *protocolObjectDescription;				// The description for the object (config report)
		const char *icmpObjectName;							// The name for the object (used in config report)
		const char *icmpObjectDescription;					// The description for the object (config report)
		const char *serviceObjectName;						// The name for the object (used in config report)
		const char *serviceObjectDescription;				// The description for the object (config report)

		netObjectListConfig *netObjectList;					// NetObjects

		netObjectListConfig *getObjectList(const char *name, const char *zone = "");					// Get/Create Object List
		netObjectListConfig *getOnlyObjectList(const char *name, const char *zone = "");					// Get Object List (not create)
		filterObjectConfig *addObject(netObjectListConfig *objectListPointer);	// Add Object to the object list
		filterObjectConfig *addObject(filterObjectConfig *objectPointer, filterObjectType objectType);	// Add Object to an object
		filterObjectConfig *getObject(const char *name, netObjectListConfig *inList = 0);
		int generateConfigObjectReport(Device *device);
		int generateSecurityObjectReport(Device *device);
		int generateConfigObjectTypeReport(Device *device, objectType type, Device::configReportStruct *configReportPointer);
		int copySourceToDestinationObjects(filterObjectConfig *sourceObject, filterObjectConfig *destinationObject);	// Copy object to another object
		int deleteFilterObject(filterObjectConfig *filterObjectPointer);			// Deletes the object and all child objects


	// -----------------------------------------------------------------------
	// Filter Rules...
	// -----------------------------------------------------------------------

		// This structure represents a filter
		enum actionType
		{
			allowAction = 0,
			denyAction = 1,
			rejectAction = 2,
			bypassAction = 3,
			exceptAction = 4,
			deftAction = 5,
			natAction = 6,
			tunnelAction = 7
		};
		enum filterType
		{
			sourceFilter = 0,
			destinationFilter = 1,
			globalFilter = 2
		};
		struct filterConfig
		{
			int number;										// Rule number (internally created)
			bool enabled;									// Is the filter enabled?
			int id;											// Filter ID (Rule ID (ScreenOS), Clause No. (CSS))
			string name;									// Filter name (if used)
			string internalId;								// Internal ID (OID)

			// filter options...
			bool remarkFilter;								// If true, the filter is only a remark, not a filter.
			bool sourceServiceSupported;					// Is a source service supported (it isn't for ICMP types)

			// filter details...
			actionType action;								// Deny, Accept
			struct filterObjectConfig *protocol;			// Protocol
			struct filterObjectConfig *source;				// Source
			struct filterObjectConfig *sourceService;		// Source Services
			struct filterObjectConfig *destination;			// Destination
			struct filterObjectConfig *destinationService;	// Destination Services
			struct filterObjectConfig *time;				// Time for the filter
			bool log;										// Log traffic
			int logLevel;									// The logging level
			bool established;								// Establish connections
			bool fragments;									// Fragmented packets

			string sourceZone;								// As used on SonicWALL devices
			string destZone;								// As used on SonicWALL devices

			struct filterObjectConfig *through;				// Through which devices (FW1)
			struct filterObjectConfig *install;				// Install onto the following devices (FW1)
			string comment;									// Or name on Passport devices

			struct filterConfig *next;

			// Passport Device Specifics...
			filterType type;
			int stop;										// Should the processing stop at this rule?
			int inSet;

			bool deleteMe;									// If this rule is to be terminated! (Internal only)
		};


	// -----------------------------------------------------------------------
	// Filter Lists...
	// -----------------------------------------------------------------------

		// This structure represents a list of filters
		struct filterListConfig
		{
			string name;					// The filter list name/id/from
			string listName;				// Some devices have a name and an id, this is the name
			bool globalFilter;				// Filter list applies to everything
			string to;						// Filter list applies to (from here to there)
			filterConfig *filter;			// The filters

			// Options...
			const char *type;				// The filter list type name (used in the config report)
			const char *typeDescription;	// The filter list type description for the report (used in config report)
			bool legacyType;				// Is the filter list a legacy type?
			bool sourceOnly;				// The type of filter
			bool loggingSupport;			// Does the filter list support logging
			bool supportsTime;				// Filter support time (dest only)
			bool supportsFragments;			// Filter support fragments (dest only)
			bool supportsEstablished;		// Filter support established (dest only)
			bool sourceServiceSupported;	// If source services are supported
			bool disabledFilterSupport;		// Is it possible to disable filters?
			bool filterCommentsSupported;	// Are filter comments supported
			bool showProtocol;				// Show the protocol? (some devices use a configured service)
			bool showFilterZones;			// Does the filter use filter-based zones (i.e. SonicWALL)
			bool showStop;					// Does the filter have a stop status (i.e. Passport devices)
			bool showFilterType;			// Does the filter have a type (i.e. like on Passport devices)
			bool active;					// Is the filter list used? (for CheckPoint devices)

			struct filterListConfig *next; 	// Next filter list

			// Internal use only
			bool used;
		};

		filterListConfig *filterList;


	// -----------------------------------------------------------------------
	// Filter Methods...
	// -----------------------------------------------------------------------

		int generateConfigFilterReport(Device *device);
		int generateConfigFilterReport(Device *device, const char *listType);
		int generateSecurityFilterReport(Device *device);
		filterConfig *insertFilter(filterListConfig *filterListPointer, filterConfig *filterPointer);			// Inserts a filter into a filter list before the specified filter
		filterConfig *addFilter(filterListConfig *filterListPointer);					// Create and return a new filter in the specified list
		filterConfig *getFilter(int id, filterListConfig *filterListPointer = 0);		// Get or Create and return a filter with the ID (optionally in a specific filter list)
		filterConfig *getOnlyFilter(int id, filterListConfig *filterListPointer = 0);	// Get or Create and return a filter with the ID (optionally in a specific filter list)
		filterObjectConfig *addFilterObject(filterConfig *filterPointer, filterObjectType sourceObject);	// Creates a new filter object of the specified type
		filterListConfig *getFilterList(const char *name);								// Get a filter list by name/id (creates what it cannot find)
		filterListConfig *getOnlyFilterList(const char *name);								// Get a filter list by name/id (does not create what it cannot find)
		filterListConfig *getFilterList(const char *from, const char *to, bool global = false);	// Get a filter list by from/to (creates what it cannot find)
		int copySourceToDestinationFilters(filterConfig *sourceFilter = 0, filterConfig *destinationFilter = 0);


	// -----------------------------------------------------------------------
	// Filter Options...
	// -----------------------------------------------------------------------

		bool denyAllAndLogDefault;							// Does it deny all and log by default?
		bool defaultFilterActionSupported;					// Default action supported on the device
		bool allowByDefault;								// Allow by default?
		bool defaultActionIsAllow;							// Is the default action to allow
		bool logLevelsSupported;							// Are log Levels supported
		bool logOnlyDenySupported;							// Is only Deny rule logging supported
		bool noAccessWithoutFilters;						// Is access not granted if no filters are configured
		bool filterSupportsInstalled;						// If filtering supports installed (i.e. CheckPoint)
		bool filterSupportsThrough;							// If a filtering supports through (i.e. CheckPoint)
		bool rejectRulesSupported;							// If reject rules are supported
		bool bypassRulesSupported;							// If bypass rules are supported
		bool defaultRulesSupported;							// If default rules are supported
		bool ruleListsAreAssigned;							// Rule lists are assigned to specific elements
		const char *allowName;								// The name given to an allowed filter
		const char *denyName;								// The name given to a denied filter
		const char *rejectName;								// The name given to a rejected filter
		const char *filterConfigTitle;						// The Title for the configuration report section
		const char *filterConfigText;						// The device specific configuration report section text
		const char *filterConfigText2;						// The device specific configuration report section text2
		bool useFilterID;									// Use the filter ID to identify a filter (otherwise a line no. is used)
		const char *filterIDTitle;							// The title for the filter ID/line no. table column
		const char *filterListNameTitle;					// The name of the filter list, for use in titles
		const char *filterListName;							// The name of the filter list, for use in text paragraphs
		const char *filterListNamePlaural;					// The name of the filter list, for use in text paragraphs
		const char *filterTitle;							// The name of a filter, for use in titles
		const char *filterTitlePlaural;						// The name of a filter, for use in titles
		const char *filterName;								// The name of a filter, for use in text paragraph
		const char *filterNamePlaural;						// The name of a filter, for use in text paragraph

		// Issues...
		const char *allowAndNotLogIssue;					// The title text for the "All Allow Rules Do Not Log" issue
		const char *allowAndNotLogTable;					// The table title text for the "All Allow Rules Do Not Log" issue
		const char *allowAndNotLogConcl;					// The conclusions text for the "All Allow Rules Do Not Log" issue
		const char *allowAndNotLogReco;						// The recommendations text for the "All Allow Rules Do Not Log" issue
		const char *denyAndNotLogIssue;						// The title text for the "All Deny Rules Do Not Log" issue
		const char *denyAndNotLogTable;						// The table title text for the "All Deny Rules Do Not Log" issue
		const char *denyAndNotLogConcl;						// The conclusions text for the "All Deny Rules Do Not Log" issue
		const char *configRuleLogging;						// The text describing how to configure logging for filter rules
		const char *noFilteringIssue;						// The title text for the "No filtering" issue
		const char *noFilteringRec;							// The title text for the "No filtering" recommendation
		const char *noFilteringCon;							// The title text for the "No filtering" conclusion
		const char *legacyIssueFinding;						// The finding for the legacy issue
		const char *legacyIssueImpact;						// The impact for the legacy issue
		const char *legacyIssueEase;						// The ease for the legacy issue
		const char *legacyIssueRec;							// The recommendation for the legacy issue
		const char *allowAnythingTable;						// The allow anything table title text
		const char *allowWeakTable;							// Weak source/service/destination/service table title text
		const char *allowAnyAnyAnyTable;					// The allow any source, destination and service table title text
		const char *allowWeakWeakWeakTable;					// The allow weak source, destination and service table title text
		const char *allowAnyServiceAnyTable;				// The allow any source port, destination and service table title text
		const char *allowWeakServiceAnyTable;				// The allow weak source, destination and service table title text
		const char *allowAnyAnyTable;						// The allow any source, destination table title text
		const char *allowAnyAnyServiceTable;				// The allow any source, destination service table title text
		const char *allowAnyDestServiceTable;				// The allow any destination and service table title text
		const char *allowAnyPortDestTable;					// The allow any source port to any destination table title text
		const char *allowAnyPortServiceTable;				// The allow any source port to any dest service table title text
		const char *allowWeakWeakTable;						// The allow weak source, destination addresses
		const char *allowWeakWeakServiceTable;				// The allow weak source, destination service table title text
		const char *allowDestAndServiceTable;				// The allow weak destination and service table title text
		const char *allowWeakPortDestTable;					// The allow weak source port to Destination table title text
		const char *allowWeakPortServiceTable;				// The allow weak source port to service table title text
		const char *allowAnySourceTable;					// The allow any source address table title text
		const char *allowNetSourceTable;					// The allow a network source address table title text
		const char *allowAnyPortTable;						// The allow any source port table title text
		const char *allowRangePortTable;					// The allow range source port table title text
		const char *allowAnyDestTable;						// The allow any destination table title text
		const char *allowNetDestTable;						// The allow a network destination table title text
		const char *allowToAnyDestServiceTable;				// The allow any destination service table title text
		const char *allowToNetDestServiceTable;				// The allow a destination service range table title text
		const char *bypassContentFilterCon;					// Bypass filter conclusion text
		const char *bypassContentFilterRec;					// Bypass filter recommendation text
		const char *defaultFilterCon;						// Default filter conclusion text
		const char *defaultFilterRec;						// Default filter recommendation text
		const char *rejectSecurityIssueTitle;				// Reject filter title text
		const char *securityRejectTextCon;					// Reject filter conclusion text
		const char *securityRejectTextRec;					// Reject filter recommendation text
		const char *clearTextServiceCon;					// Clear Text Service conclusions text
		const char *clearTextServiceRec;					// Clear Text Service recommendations text
		const char *configureFilterListRecIssueText;		// The text and commands to configure a filter list
		const char *configureFilterRecIssueText;			// The text and commands to configure a filter
		const char *unnecessaryServiceCon;					// Unnecessary Service conclusions text
		const char *unnecessaryServiceRec;					// Unnecessary Service recommendations text
		const char *filtersWithNoCommentsTitle;				// Filters with no comments title text
		const char *noFilterCommentsCon;					// The no comments conclusion text
		const char *noFilterCommentsRec;					// The no comments recommendation text
		const char *configureFilterCommentText;				// The text and commands to configure a filters comment text
		const char *disabledFiltersTitle;					// The disabled filter issues title text
		const char *removeFilterText;						// The commands and text to delete a filter
		const char *disabledFilterCon;						// The disabled filter conclusion text
		const char *disabledFilterRec;						// The disabled filter recommendation text
		const char *defaultActionIssueTitle;				// The default filter action issue title
		const char *defaultActionIssueCon;					// The default filter action conclusion text
		const char *defaultActionIssueRec;					// The default filter action recommendation text
		const char *configureDefaultActionText;				// The text and commands to configure the default action
		const char *unusedFiltersIssueTitle;				// Unused filters at the end of the filter list title
		const char *unusedFiltersIssueCon;					// Unused filters issue conclusions text
		const char *unusedFiltersIssueRec;					// Unused filters issue recommendation text
		const char *denyAllLogIssueTitle;					// Deny All And Log Issue title
		const char *denyAllLogConfigure;					// The text and commands to add a deny all and log line
		const char *denyAllLogIssueCon;						// The deny all and log conclusions text
		const char *denyAllLogIssueRec;						// The deny all and log recommendations text
		const char *contradictIssueTitle;					// The contradict issue title
		const char *contradictIssueTable;					// The contradict table issue title
		const char *contradictIssueCon;						// The contradict issue conclusion
		const char *contradictIssueRec;						// The contradict issue recommendation
		const char *duplicateIssueTitle;					// The duplicate/overlapping issue title
		const char *duplicateIssueTable;					// The duplicate/overlapping issue title
		const char *duplicateIssueCon;						// The duplicate/overlapping issue title
		const char *duplicateIssueRec;						// The duplicate/overlapping issue title


		int addFilterTableRow(Device *device, Device::paragraphStruct *paragraphPointer, filterConfig *filterPointer, filterListConfig *filterListPointer, bool includeFilterList = false);
		int addFilterTableHeadings(Device *device, Device::paragraphStruct *paragraphPointer, filterListConfig *filterListPointer, bool includeFilterList = false);

	private:

		int outputFilterProtocols(Device *device, Device::tableStruct *tablePointer, filterObjectConfig *filterObjectPointer);
		int outputFilterHosts(Device *device, Device::tableStruct *tablePointer, filterObjectConfig *filterObjectPointer, const char *zoneName = 0);
		int outputFilterHostService(Device *device, Device::tableStruct *tablePointer, filterObjectConfig *filterObjectPointer);
		int outputFilterTime(Device *device, Device::tableStruct *tablePointer, filterObjectConfig *filterObjectPointer);


	// -----------------------------------------------------------------------
	// Security Issue Structures...
	// -----------------------------------------------------------------------

		struct filterListIssueConfig
		{
			filterListConfig *filterRuleList;
			struct filterListIssueConfig *next;
		};

		struct filterIssueConfig
		{
			filterConfig *filter;
			filterListConfig *filterRuleList;
			struct filterIssueConfig *next;
		};

		struct filterDuplConfig
		{
			filterConfig *filter;
			filterListConfig *filterRuleList;
			filterIssueConfig *duplicates;
			struct filterDuplConfig *next;
		};

		filterIssueConfig *anyAnyAnyAny;		// GEN.FILTAAAA.1   Access Allowed From Any Source And Service To Any Destination And Service
		filterIssueConfig *weakWeakWeakWeak;	// GEN.FILTWAAA.1   Weak Access Allowed From Weak Source And Service To Weak Destination And Service
		filterIssueConfig *anyAnyAny;			// GEN.FILTAAAN.1   Access Allowed From Any Source To Any Destination And Service
		filterIssueConfig *weakWeakWeak;		// GEN.FILTWAAN.1   Weak Access Allowed From Weak Source To Weak Destination And Service
		filterIssueConfig *anyServiceAnyAny;	// GEN.FILTSAAN.1   Access Allowed From Any Source Service to Any Destination And Service
		filterIssueConfig *weakServiceAnyAny;	// GEN.FILTWSAN.1   WeakAccess Allowed From Weak Source Service to Weak Destination And Service
		filterIssueConfig *anyAny;				// GEN.FILTANAN.1   Access Allowed From Any Source To Any Destination
		filterIssueConfig *anyAnyDestService;	// GEN.FILTANAS.1   Access Allowed From Any Source To Any Destination Service
		filterIssueConfig *destHostAndService;	// GEN.FILTANDS.1   Access Allowed To Any Destination Host And Service
		filterIssueConfig *anyServiceAny;		// GEN.FILTSNAN.1   Access Allowed From Any source Service To Any Destination
		filterIssueConfig *anyServiceAnyService;// GEN.FILTASDS.1   Access Allowed From Any Source Service to Any Destination Service
		filterIssueConfig *weakWeak;			// GEN.FILTWNAN.1   Weak Access Allowed From Weak Source To Any Destination
		filterIssueConfig *weakDestService;		// GEN.FILTWNAS.1   Weak Access Allowed From Weak Source To Any Destination Service
		filterIssueConfig *weakDestHostAndService;	// GEN.FILTWNDS.1   Weak Access Allowed To Weak Destination Host And Service
		filterIssueConfig *weakServiceAny;		// GEN.FILTWSNN.1   Weak Access Allowed From Weak source Service To Weak Destination
		filterIssueConfig *weakServiceAnyService;	// GEN.FILTWSDS.1   Weak Access Allowed From Weak Source Service to Weak Destination Service
		filterIssueConfig *anySourceHost;		// GEN.FILTANSO.1   Access Allowed From Any Source Host
		filterIssueConfig *netSourceHost;		// GEN.FILTNESO.1   Access Allowed From A Network Source
		filterIssueConfig *anySourceService;	// GEN.FILTANSS.1   Access Allowed From Any Source Service
		filterIssueConfig *rangeSourceService;	// GEN.FILTRASS.1   Access Allowed From A Range Of Source Services
		filterIssueConfig *anyDestination;		// GEN.FILTANDE.1   Access Allowed To Any Destination Host
		filterIssueConfig *netDestination;		// GEN.FILTNEDE.1   Access Allowed To A Network Destination
		filterIssueConfig *anyDestService;		// GEN.FILTANSE.1   Access Allowed To Any Destination Service
		filterIssueConfig *rangeDestService;	// GEN.FILTRDSS.1   Access Allowed To A Range Of Destination Services
		filterIssueConfig *allowedLogging;		// GEN.FILTALLO.1   Allowed Rules Do Not Log
		filterIssueConfig *deniedLogging;		// GEN.FILTDELO.1   Denied Rules Do Not Log
		filterListIssueConfig *denyAllAndLog;	// GEN.FILTDAAL.1   Filter List Does Not End With A Deny All And Log
		filterIssueConfig *filterRejects;		// GEN.FILTREJE.1   Filter Rule Rejects
		filterIssueConfig *filterBypasses;		// GEN.FILTBYPA.1   Filter Rule Bypasses Filtering
		filterIssueConfig *filterDefault;		// GEN.FILTDEFT.1   Filter Uses The Default Action
		filterIssueConfig *filterNoComment;		// GEN.FILTCOMM.1   Filter Rule Is Not Commented
		filterIssueConfig *filterDisabled;		// GEN.FILTDISA.1   Disabled Filter Rules
		filterIssueConfig *filterClearText;		// GEN.FILTCLEA.1   Access To Clear Text Protocol Services Allowed
		filterIssueConfig *filterDangerous;		// GEN.FILTDANG.1   Access To Dangerous Protocol Services Allowed
		filterIssueConfig *filterUnnecessary;	// GEN.FILTUNNE.1   Access To Unnecessary Protocol Services Allowed
		filterIssueConfig *weakLoggingLevel;	// GEN.FILTLGLE.1   Weak Filter Logging Levels
		filterListIssueConfig *legacyLists;		// GEN.FILTLEGA.1   Legacy Filtering Configuration
		filterIssueConfig *filterUnused;		// GEN.FILTUNUS.1   Unused Filter Rules
		filterDuplConfig *filterDuplicate;		// GEN.FILTDUPL.1   Duplicate/Overlap Filter Rules Are Configured
		filterDuplConfig *filterContradict;		// GEN.FILTCONT.1   Contradict Filter Rules Are Configured

		/**
		 * This method adds an issue to the issue lists.
		 *
		 * \param issue            Is the issue reference, e.g. GEN.FILTLGLE.1
		 * \param filter           A pointer to the filter that is at fault
		 * \param duplicate        A pointer to a duplicate filter to that of the filter pointer
		 * \param filterRuleList   A pointer to the filterList that is at fault
		 */
		void addFilterIssue(const char *issue, filterListConfig *filterRuleList);
		void addFilterIssue(const char *issue, filterConfig *filter, filterListConfig *filterRuleList);
		void addFilterIssue(const char *issue, filterConfig *filter, filterConfig *duplicate, filterListConfig *filterRuleList);

		/**
		 * This method adds the recommendations for network filtering.
		 *
		 * \param device           A pointer to the device class
		 * \param paragraph        A pointer to the paragraph
		 */
		void recommendedFiltering(Device *device, Device::securityIssueStruct *securityIssue);

		/**
		 * This method checks the supplied filters service filter object for security issues. The
		 * return value is a host, network or any object, depending on how relaxed the configuration
		 * is.
		 *
		 * \param device           A pointer to the device class
		 * \param filterObject    The object to check
		 * \return                The result of the checks
		 */
		int serviceSourceSecurityChecks(Device *device, filterObjectConfig *filterObject, const char *fromZone = "", const char *toZone = "");
		int serviceDestinationSecurityChecks(Device *device, filterObjectConfig *filterObject, const char *fromZone = "", const char *toZone = "", bool enumerate = true);

		/**
		 * This method checks the supplied filters host filter object for security issues. The
		 * return value is a host, network or any object, depending on how relaxed the configuration
		 * is.
		 *
		 * \param device          A pointer to the device class
		 * \param filterObject    The object to check
		 * \param zone            The network zone (if one exists)
		 * \return                The result of the checks
		 */
		int hostSourceSecurityChecks(Device *device, filterObjectConfig *filterObject, const char *zone = "");
		int hostDestinationSecurityChecks(Device *device, filterObjectConfig *filterObject, const char *zone = "");

		/**
		 * This method searches for the object name in a service list object
		 *
		 * \param objectName      The name of the object to look for
		 * \return                The result object or nothing
		 */
		filterObjectConfig *getServiceListObject(const char *objectName);

		/**
		 * This method searches for the object name in a address list object
		 *
		 * \param objectName      The name of the object to look for
		 * \param zone            The network zone (if one exists)
		 * \return                The result object or nothing
		 */
		filterObjectConfig *getAddressListObject(const char *objectName, const char *zone);

		int writeFilterSecurityIssue(Device *device, Device::securityIssueStruct *securityIssuePointer, filterIssueConfig *filterListIssues, const char *filterIssueFindingText, const char *tableReferenceText, const char *tableTitleText, int impactRating, const char *conclusionsText);

		int generateSecurityReportIssues(Device *device);

		bool enableComments;					// Internal use only!
		objectType sourceDetection;				// Internal use only!
		objectType sourcePortDetection;			// Internal use only!
		objectType destinationDetection;		// Internal use only!
		objectType destinationPortDetection;	// Internal use only!
		bool containsClearText;					// Internal use only!
		bool containsDangerous;					// Internal use only!
		bool containsUnnecessary;				// Internal use only!

		bool isInServiceList(Device *device, Config::protocolServiceList *serviceList, const char *startPort, const char *endPort = "");
		bool portOverlap(Device *device, filterObjectConfig *firstPort, bool enumFirst, filterObjectConfig *secondPort, bool enumSecond, const char *from = "", const char *to = "", bool source = true);
		bool hostOverlap(Device *device, filterObjectConfig *firstHost, bool enumFirst, filterObjectConfig *secondHost, bool enumSecond, const char *zone = "");
		bool compareHostRanges(Device *device, const char *address1, const char *netmask1, const char *address2, const char *netmask2);
		bool comparePortRanges(int firstStart, int firstEnd, int secondStart, int secondEnd);
		const char *filterListNameTextTitle(filterListConfig *filterListPointer);
		const char *filterListTableTitle(filterListConfig *filterListPointer);
};


#endif


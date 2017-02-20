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

// This file contains all the code for filtering...

#define access_none 0
#define access_old 1
#define access_std 2
#define access_ext 3

struct filterListConfig
{
	char name[64];						// List Name (or ID)

	// Cisco ACL...
	int type;							// access_old...

	// Cisco CSS...
	char applyTo[32];

	// ScreenOS List...
	int global;
	char fromZone[32];					// Also used for SonicOS
	char toZone[32];					// Also ussed for SonicOS

	// Passport...
	char listName[64];

	// Filters / Rules...
	struct filterConfig *filter;

	// Filter issue flags
	int denyAllAndLog;

	// Next list...
	struct filterListConfig *next;
};


struct filterConfig
{
	int id;											// Rule ID (ScreenOS), Clause No. (CSS)
	int enabled;
	int action;										// Deny, Accept
	struct filterObjectConfig *source;				// Source
	struct filterObjectConfig *sourceService;		// Source Services
	struct filterObjectConfig *destination;			// Destination
	struct filterObjectConfig *destinationService;	// Destination Services
	struct filterObjectConfig *through;				// Through which devices (FW1)
	struct filterObjectConfig *install;				// Install onto the following devices (FW1)
	int log;										// Log traffic
	char remark[128];								// Or name on Passport devices

	int deleteMe;									// If this rule is to be terminated! (Internal only)

	// Firewall-1
	char uid[48];

	// Cisco...
	char protocol[32];
	int protocolType;								// access_type_protocol...

	// Cisco IOS...
	int established;								// true or false
	int fragments;									// true or false

	// Passport...
	int filterType;
	int stop;
	int inSet;

	// Filter issue flags
	int anySource;
	int networkSource;
	int anySourceService;
	int anyDestination;
	int networkDestination;
	int anyDestinationService;
	int logging;
	int logDeny;
	struct filterConfig *next;
};


struct filterObjectConfig
{
	char name[64];
	char netMask[16];
	int serviceOp;									// access_oper_eq...
	int type;										// access_type_interface...

	struct filterObjectConfig *next;
};


#define object_filter_destination 0
#define object_filter_source 1
#define object_filter_sourceService 2
#define object_filter_service 3
#define object_filter_install 4
#define object_filter_through 5

// Gets the filter list (or creates one) and returns the pointer to it...
struct filterListConfig *getFilterList(struct nipperConfig *nipper, char *name, char *name2, int global)
{
	// Variables...
	struct filterListConfig *filterListPointer = 0;
	int init = false;

	// If this is the first, create...
	if (nipper->filterList == 0)
	{
		nipper->filterList = malloc(sizeof(struct filterListConfig));
		filterListPointer = nipper->filterList;
		init = true;
	}

	// Find / Create Filter List...
	else if ((nipper->deviceType != type_sos_firewall) && (nipper->deviceType != type_sonicwall))
	{
		filterListPointer = nipper->filterList;
		while ((filterListPointer->next != 0) && (strcmp(filterListPointer->name, name) != 0))
			filterListPointer = filterListPointer->next;
		if (strcmp(filterListPointer->name, name) != 0)
		{
			filterListPointer->next = malloc(sizeof(struct filterListConfig));
			filterListPointer = filterListPointer->next;
			init = true;
		}
	}
	else
	{
		if (global == false)
		{
			filterListPointer = nipper->filterList;
			while ((filterListPointer->next != 0) && !((strcmp(filterListPointer->fromZone, name) == 0) && (strcmp(filterListPointer->toZone, name2) == 0)))
				filterListPointer = filterListPointer->next;
			if (!((strcmp(filterListPointer->fromZone, name) == 0) && (strcmp(filterListPointer->toZone, name2) == 0)))
			{
				filterListPointer->next = malloc(sizeof(struct filterListConfig));
				filterListPointer = filterListPointer->next;
				init = true;
			}
		}
		else
		{
			filterListPointer = nipper->filterList;
			while ((filterListPointer->next != 0) && (filterListPointer->global == false))
				filterListPointer = filterListPointer->next;
			if (filterListPointer->global == false)
			{
				filterListPointer->next = malloc(sizeof(struct filterListConfig));
				filterListPointer = filterListPointer->next;
				init = true;
			}
		}
	}

	// Init?
	if (init == true)
	{
		memset(filterListPointer, 0, sizeof(struct filterListConfig));
		if ((nipper->deviceType != type_sos_firewall) && (nipper->deviceType != type_sonicwall))
			strncpy(filterListPointer->name, name, sizeof(filterListPointer->name) - 1);
		else
		{
			strncpy(filterListPointer->fromZone, name, sizeof(filterListPointer->fromZone) - 1);
			strncpy(filterListPointer->toZone, name2, sizeof(filterListPointer->toZone) - 1);
		}
		filterListPointer->denyAllAndLog = false;
		filterListPointer->global = global;
		filterListPointer->type = access_none;
	}

	return filterListPointer;
}


// Code that adds filter objects...
struct filterConfig *getFilter(struct filterListConfig *filterListPointer, int id)
{
	// Variables...
	struct filterConfig *filterPointer;
	int init = false;

	// if not filters exist...
	if (filterListPointer->filter == 0)
	{
		filterListPointer->filter = malloc(sizeof(struct filterConfig));
		filterPointer = filterListPointer->filter;
		init = true;
	}
	else
	{
		filterPointer = filterListPointer->filter;
		while ((filterPointer->next != 0) && (filterPointer->id != id))
			filterPointer = filterPointer->next;
		if (filterPointer->id != id)
		{
			filterPointer->next = malloc(sizeof(struct filterConfig));
			filterPointer = filterPointer->next;
			init = true;
		}
	}

	// Init...
	if (init == true)
	{
		memset(filterPointer, 0, sizeof(struct filterConfig));
		filterPointer->id = id;
	}

	return filterPointer;
}


// Code that adds filter object members...
struct filterObjectConfig *getFilterMember(struct filterConfig *filterPointer, char *name, int objectType)
{
	// Variables...
	struct filterObjectConfig *filterObjectPointer = 0;
	int init = false;

	// Create / Get pointer to object...
	switch (objectType)
	{
		case object_filter_destination:
			if (filterPointer->destination == 0)
			{
				filterPointer->destination = malloc(sizeof(struct filterObjectConfig));
				filterObjectPointer = filterPointer->destination;
				init = true;
			}
			else
			{
				filterObjectPointer = filterPointer->destination;
				while ((filterObjectPointer->next != 0) && (strcasecmp(filterObjectPointer->name, name) != 0))
					filterObjectPointer = filterObjectPointer->next;
				if (strcasecmp(filterObjectPointer->name, name) != 0)
				{
					filterObjectPointer->next = malloc(sizeof(struct filterObjectConfig));
					filterObjectPointer = filterObjectPointer->next;
					init = true;
				}
			}
			break;

		case object_filter_source:
			if (filterPointer->source == 0)
			{
				filterPointer->source = malloc(sizeof(struct filterObjectConfig));
				filterObjectPointer = filterPointer->source;
				init = true;
			}
			else
			{
				filterObjectPointer = filterPointer->source;
				while ((filterObjectPointer->next != 0) && (strcasecmp(filterObjectPointer->name, name) != 0))
					filterObjectPointer = filterObjectPointer->next;
				if (strcasecmp(filterObjectPointer->name, name) != 0)
				{
					filterObjectPointer->next = malloc(sizeof(struct filterObjectConfig));
					filterObjectPointer = filterObjectPointer->next;
					init = true;
				}
			}
			break;

		case object_filter_sourceService:
			if (filterPointer->sourceService == 0)
			{
				filterPointer->sourceService = malloc(sizeof(struct filterObjectConfig));
				filterObjectPointer = filterPointer->sourceService;
				init = true;
			}
			else
			{
				filterObjectPointer = filterPointer->sourceService;
				while ((filterObjectPointer->next != 0) && (strcasecmp(filterObjectPointer->name, name) != 0))
					filterObjectPointer = filterObjectPointer->next;
				if (strcasecmp(filterObjectPointer->name, name) != 0)
				{
					filterObjectPointer->next = malloc(sizeof(struct filterObjectConfig));
					filterObjectPointer = filterObjectPointer->next;
					init = true;
				}
			}
			break;

		case object_filter_service:
			if (filterPointer->destinationService == 0)
			{
				filterPointer->destinationService = malloc(sizeof(struct filterObjectConfig));
				filterObjectPointer = filterPointer->destinationService;
				init = true;
			}
			else
			{
				filterObjectPointer = filterPointer->destinationService;
				while ((filterObjectPointer->next != 0) && (strcasecmp(filterObjectPointer->name, name) != 0))
					filterObjectPointer = filterObjectPointer->next;
				if (strcasecmp(filterObjectPointer->name, name) != 0)
				{
					filterObjectPointer->next = malloc(sizeof(struct filterObjectConfig));
					filterObjectPointer = filterObjectPointer->next;
					init = true;
				}
			}
			break;

		case object_filter_install:
			if (filterPointer->install == 0)
			{
				filterPointer->install = malloc(sizeof(struct filterObjectConfig));
				filterObjectPointer = filterPointer->install;
				init = true;
			}
			else
			{
				filterObjectPointer = filterPointer->install;
				while ((filterObjectPointer->next != 0) && (strcasecmp(filterObjectPointer->name, name) != 0))
					filterObjectPointer = filterObjectPointer->next;
				if (strcasecmp(filterObjectPointer->name, name) != 0)
				{
					filterObjectPointer->next = malloc(sizeof(struct filterObjectConfig));
					filterObjectPointer = filterObjectPointer->next;
					init = true;
				}
			}
			break;

		case object_filter_through:
			if (filterPointer->through == 0)
			{
				filterPointer->through = malloc(sizeof(struct filterObjectConfig));
				filterObjectPointer = filterPointer->through;
				init = true;
			}
			else
			{
				filterObjectPointer = filterPointer->through;
				while ((filterObjectPointer->next != 0) && (strcasecmp(filterObjectPointer->name, name) != 0))
					filterObjectPointer = filterObjectPointer->next;
				if (strcasecmp(filterObjectPointer->name, name) != 0)
				{
					filterObjectPointer->next = malloc(sizeof(struct filterObjectConfig));
					filterObjectPointer = filterObjectPointer->next;
					init = true;
				}
			}
			break;
	}

	// Init...
	if (init == true)
	{
		memset(filterObjectPointer, 0, sizeof(struct filterObjectConfig));
		strncpy(filterObjectPointer->name, name, sizeof(filterObjectPointer->name) - 1);
		filterObjectPointer->serviceOp = service_oper_eq;
	}

	return filterObjectPointer;
}


// Insert a remark into a filter list...
void insertFilterRemark(struct filterListConfig *filterListPointer, struct filterConfig *filterPointer, int before, char *remark)
{
	// Variables...
	struct filterConfig *insertFilterPointer = 0;
	struct filterConfig *searchFilterPointer = 0;

	// Create new filter for the remark and init...
	insertFilterPointer = malloc(sizeof(struct filterConfig));
	memset(insertFilterPointer, 0, sizeof(struct filterConfig));
	insertFilterPointer->action = filter_action_remark;
	strncpy(insertFilterPointer->remark, remark, sizeof(insertFilterPointer->remark) - 1);

	// Put it in the right place in the list...
	if ((before == false) && (filterPointer == 0))
	{
		// if first
		if (filterListPointer->filter == 0)
			filterListPointer->filter = insertFilterPointer;
		else
		{
			searchFilterPointer = filterListPointer->filter;
			while (searchFilterPointer->next != 0)
				searchFilterPointer = searchFilterPointer->next;
			searchFilterPointer->next = insertFilterPointer;
		}
	}
	else if ((before == true) && (filterListPointer->filter == filterPointer))
	{
		insertFilterPointer->next = filterPointer;
		filterListPointer->filter = insertFilterPointer;
	}
	else if (before == true)
	{
		insertFilterPointer->next = filterPointer;
		searchFilterPointer = filterListPointer->filter;
		while (searchFilterPointer->next != filterPointer)
			searchFilterPointer = searchFilterPointer->next;
		searchFilterPointer->next = insertFilterPointer;
	}
	else
	{
		insertFilterPointer->next = filterPointer->next;
		filterPointer->next = insertFilterPointer;
	}
}


// Search for network objects...
int searchForNetworkObjects(struct nipperConfig *nipper, char *name)
{
	// Variables...
	struct objectListConfig *objectListPointer = 0;
	struct objectConfig *objectPointer = 0;
	struct objectMember *memberPointer = 0;
	int foundNetwork = false;

	// Search for network objects...
	objectListPointer = nipper->objectList;
	while ((objectListPointer != 0) && (foundNetwork == false))
	{
		objectPointer = objectListPointer->object;
		while ((objectPointer != 0) && (foundNetwork == false))
		{

			// If object has been found...
			if (strcmp(objectPointer->name, name) == 0)
			{
				// Look at the current object first...
				if ((objectPointer->type == object_type_network) || (objectPointer->type == object_type_machinesrange) || (objectPointer->type == object_type_dynamicnet))
					foundNetwork = true;
	
				// Look at member objects next...
				else
				{
					memberPointer = objectPointer->members;
					while ((memberPointer != 0) && (foundNetwork == false))
					{
	
						if ((memberPointer->type == object_type_network) || (memberPointer->type == object_type_machinesrange) || (memberPointer->type == object_type_dynamicnet))
							foundNetwork = true;
						else if ((memberPointer->type == object_type_group) || (memberPointer->type == object_type_object))
							foundNetwork = searchForNetworkObjects(nipper, memberPointer->name);
	
						// Next member...
						memberPointer = memberPointer->next;
					}
				}
			}

			// Next object...
			objectPointer = objectPointer->next;
		}

		// Next object list...
		objectListPointer = objectListPointer->next;
	}

	return foundNetwork;
}


// The code that looks for audit issues...
void rulesAudit(struct nipperConfig *nipper)
{
	// Variables...
	struct filterObjectConfig *filterObjectPointer = 0;
	struct filterConfig *filterPointer = 0;
	struct filterListConfig *filterListPointer = 0;
	int tempInt = 0;

	// Disable source service checking for those devices that dont support it
	switch (nipper->deviceType)
	{
		case type_fw1_firewall:
		case type_nokiaip:
			nipper->rejectRulesIssue = false;
			nipper->bypassRulesIssue = false;
			nipper->defaultRulesIssue = false;
			nipper->anySourceServiceIssue = false;
			break;
		case type_sos_firewall:
			nipper->anySourceServiceIssue = false;
			nipper->bypassRulesIssue = false;
			nipper->defaultRulesIssue = false;
			break;
		case type_pix_firewall:
		case type_asa_firewall:
		case type_fwsm_firewall:
			nipper->bypassRulesIssue = false;
			nipper->rejectRulesIssue = false;
			nipper->defaultRulesIssue = false;
			break;
		case type_css_filter:
			nipper->rejectRulesIssue = false;
			nipper->disabledRulesIssue = false;
			nipper->defaultRulesIssue = false;
			break;
		case type_ios_router:
		case type_ios_switch:
		case type_ios_catalyst:
			nipper->bypassRulesIssue = false;
			nipper->rejectRulesIssue = false;
			nipper->disabledRulesIssue = false;
			nipper->defaultRulesIssue = false;
			break;
		case type_passport:
		case type_bayaccelar:
			nipper->bypassRulesIssue = false;
			nipper->rejectRulesIssue = false;
			nipper->disabledRulesIssue = false;
			nipper->logDenyRulesIssue = false;
			nipper->allRulesLogIssue = false;
			nipper->denyLogIssue = false;
			break;
		case type_sonicwall:
			nipper->bypassRulesIssue = false;
			nipper->defaultRulesIssue = false;
			break;
	}

	// Check for Any and Log issues...
	filterListPointer = nipper->filterList;
	while (filterListPointer != 0)
	{
		filterPointer = filterListPointer->filter;
		while (filterPointer != 0)
		{
			if (filterPointer->action != filter_action_remark)
			{
				// Check for disabled...
				if ((filterPointer->enabled == false) && (nipper->disabledRulesIssue == true))
					nipper->disabledRules++;

				// Check for reject...
				if ((filterPointer->action == filter_action_reject) && (nipper->rejectRulesIssue == true))
					nipper->rejectRules++;

				// Check for bypass...
				if ((filterPointer->action == filter_action_bypass) && (nipper->bypassRulesIssue == true))
					nipper->bypassRules++;

				// Check for bypass...
				if ((filterPointer->action == filter_action_default) && (nipper->defaultRulesIssue == true))
					nipper->defaultRules++;
	
				// Check for Any source...
				if ((filterPointer->action == filter_action_accept) && (nipper->anySourceIssue == true))
				{
					filterObjectPointer = filterPointer->source;
					while (filterObjectPointer != 0)
					{
						if (filterObjectPointer->type == object_type_any)
							filterPointer->anySource = true;
						filterObjectPointer = filterObjectPointer->next;
					}
					if (filterPointer->anySource == true)
						nipper->anySource++;
				}

				// Check for network source...
				if ((filterPointer->action == filter_action_accept) && (nipper->networkSourceIssue == true))
				{
					filterObjectPointer = filterPointer->source;
					while (filterObjectPointer != 0)
					{
						if (filterObjectPointer->type == object_type_network)
							filterPointer->networkSource = true;
						else if ((filterObjectPointer->type == object_type_group) || (filterObjectPointer->type == object_type_object))
						{
							tempInt = searchForNetworkObjects(nipper, filterObjectPointer->name);
							if (tempInt == true)
								filterPointer->networkSource = true;
						}
						filterObjectPointer = filterObjectPointer->next;
					}
					if (filterPointer->networkSource == true)
						nipper->networkSource++;
				}

				// If not standard ACL (for PIX, IOS...)
				if (filterListPointer->type != access_std)
				{

					// Check for Any source service...
					if ((filterPointer->action == filter_action_accept) && (nipper->anySourceServiceIssue == true))
					{
						filterObjectPointer = filterPointer->sourceService;
						while (filterObjectPointer != 0)
						{
							if (filterObjectPointer->serviceOp == service_oper_any)
								filterPointer->anySourceService = true;
							filterObjectPointer = filterObjectPointer->next;
						}
						if (filterPointer->anySourceService == true)
							nipper->anySourceService++;
					}

					// Check for Any destination...
					if ((filterPointer->action == filter_action_accept) && (nipper->anyDestinationIssue == true))
					{
						filterObjectPointer = filterPointer->destination;
						while (filterObjectPointer != 0)
						{
							if (filterObjectPointer->type == object_type_any)
								filterPointer->anyDestination = true;
							filterObjectPointer = filterObjectPointer->next;
						}
						if (filterPointer->anyDestination == true)
							nipper->anyDestination++;
					}

					// Check for network destination...
					if ((filterPointer->action == filter_action_accept) && (nipper->networkDestinationIssue == true))
					{
						filterObjectPointer = filterPointer->destination;
						while (filterObjectPointer != 0)
						{
							if (filterObjectPointer->type == object_type_network)
								filterPointer->networkDestination = true;
							else if ((filterObjectPointer->type == object_type_group) || (filterObjectPointer->type == object_type_object))
							{
								tempInt = searchForNetworkObjects(nipper, filterObjectPointer->name);
								if (tempInt == true)
									filterPointer->networkDestination = true;
							}
							filterObjectPointer = filterObjectPointer->next;
						}
						if (filterPointer->networkDestination == true)
							nipper->networkDestination++;
					}

					// Check for Any destination service...
					if ((filterPointer->action == filter_action_accept) && (nipper->anyDestinationServiceIssue == true))
					{
						filterObjectPointer = filterPointer->destinationService;
						while (filterObjectPointer != 0)
						{
							if (filterObjectPointer->serviceOp == service_oper_any)
								filterPointer->anyDestinationService = true;
							filterObjectPointer = filterObjectPointer->next;
						}
						if (filterPointer->anyDestinationService == true)
							nipper->anyDestinationService++;
					}

					// Filters with deny and log rules...
					if ((nipper->logDenyRulesIssue == true) && (filterPointer->action != filter_action_accept) && (filterPointer->log == false))
					{
						nipper->logDenyRules++;
						filterPointer->logDeny = true;
					}
				}

				// Not PIX std access lists...
				if (!(((nipper->deviceType == type_pix_firewall) || (nipper->deviceType == type_asa_firewall) || (nipper->deviceType == type_fwsm_firewall)) && (filterListPointer->type == access_std)))
				{
					// Filters with no logging...
					if ((nipper->allRulesLogIssue == true) && (filterPointer->log == false) && (filterPointer->logDeny == false))
					{
						if ((filterPointer->next != 0) || (nipper->denyLogIssue == false))
						{
							filterPointer->logging = true;
							nipper->filtersWithNoLogging++;
						}
					}

					// Filters ending with deny all and log
					tempInt = false;
					if ((nipper->denyLogIssue == true) && (filterPointer->action != filter_action_remark))
					{
						if (filterPointer->next == 0)
							tempInt = true;
						else if ((filterPointer->next->action == filter_action_remark) && (filterPointer->next->next == 0))
							tempInt = true;
					}
					if (tempInt == true)
					{
						tempInt = false;
						if (filterPointer->action != filter_action_drop)
							tempInt = true;
						filterObjectPointer = filterPointer->source;
						while (filterObjectPointer != 0)
						{
							if (filterObjectPointer->type != object_type_any)
								tempInt = true;
							filterObjectPointer = filterObjectPointer->next;
						}
						filterObjectPointer = filterPointer->sourceService;
						while (filterObjectPointer != 0)
						{
							if (filterObjectPointer->serviceOp != service_oper_any)
								tempInt = true;
							filterObjectPointer = filterObjectPointer->next;
						}
						filterObjectPointer = filterPointer->destination;
						while (filterObjectPointer != 0)
						{
							if (filterObjectPointer->type != object_type_any)
								tempInt = true;
							filterObjectPointer = filterObjectPointer->next;
						}
						filterObjectPointer = filterPointer->destinationService;
						while (filterObjectPointer != 0)
						{
							if (filterObjectPointer->serviceOp != service_oper_any)
								tempInt = true;
							filterObjectPointer = filterObjectPointer->next;
						}
						if (tempInt == true)
						{
							nipper->denyAllAndLog++;
							filterListPointer->denyAllAndLog = true;
						}
					}
				}
			}

			filterPointer = filterPointer->next;
		}
		filterListPointer = filterListPointer->next;
	}
	
	// Add to ACL issues...
	nipper->aclIssues += nipper->anySource;
	nipper->aclIssues += nipper->networkSource;
	nipper->aclIssues += nipper->rejectRules;
	nipper->aclIssues += nipper->bypassRules;
	nipper->aclIssues += nipper->defaultRules;
	nipper->aclIssues += nipper->logDenyRules;
	nipper->aclIssues += nipper->anySourceService;
	nipper->aclIssues += nipper->anyDestination;
	nipper->aclIssues += nipper->networkDestination;
	nipper->aclIssues += nipper->anyDestinationService;
	nipper->aclIssues += nipper->filtersWithNoLogging;
	nipper->aclIssues += nipper->denyAllAndLog;
	nipper->aclIssues += nipper->disabledRules;
}



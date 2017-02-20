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

// Includes...
#include "../../globaldefs.h"
#include "../device.h"
#include "interfaces.h"


Interfaces::Interfaces()
{
	// Interface Options...
	useModuleAndPort = false;						// Use the module / port instead of the name
	useInterfaceZone = false;						// Use the interface zone
	zoneName = i18n("Zone");						// The name for zone field
	filterIn = i18n("Filter In");					// The filter in table title text
	filterOut = i18n("Filter Out");					// The filter out table title text
	showDescription = false;						// Show the interface description
	cdpGlobalRequired = false;						// If CDP needs to be enabled globally as well
	disableCDPText = i18n("");						// The text and commands to disable CDP
	cdpSupported = false;							// Is CDP supported on interfaces
	disableProxyARPText = i18n("");					// The text and commands to disable Proxy ARP
	disableUnreachablesText = i18n("");				// The text and commands to disable ICMP unreachable messages
	globalIPUnreachableSupported = false;			// Globally rather than on interfaces
	globalUnreachableEnabled = false;				// Globally rather than on interfaces
	disableInformationText = i18n("");				// The text and commands to disable ICMP information messages
	disableMaskText = i18n("");						// The text and commands to disable ICMP mask messages
	disableRedirectText = i18n("");					// The text and commands to disable ICMP redirect messages
	globalRedirectSupported = false;				// Globally rather than on interfaces
	globalRedirectEnabled = false;					// Globally rather than on interfaces
	disableDirectedText = i18n("");					// The text and commands to disable directed broadcasts
	disableMOPText = i18n("");						// The text and commands to disable MOP
	disableActiveText = i18n("");					// The text and commands to disable potentially unused interfaces
	filterName = i18n("filter lists");				// The filter list name for use in the filter issue text
	configFilterText = i18n("");					// The text and commands to configure network filtering
	defaultAutoTrunk = false;						// Default to automatically trunk
	disableTrunkText = i18n("");					// The text and commands to disable trunking on a port
	enablePortSecurityText = i18n("");				// The text and commands to enable port security

	interfaceList = 0;
	cdpIssues = 0;
	proxyARPIssues = 0;
	unreachableIssues = 0;
	informationReplyIssues = 0;
	maskReplyIssues = 0;
	redirectsIssues = 0;
	directedIssues = 0;
	mopIssues = 0;
	activeIssues = 0;
	filterIssues = 0;
	trunkingIssues = 0;
	portSecIssues = 0;
}


Interfaces::~Interfaces()
{
	// Variables...
	interfaceListConfig *interfaceListPointer = 0;
	interfaceConfig *interfacePointer = 0;
	issueLinksConfig *issueLinksPointer = 0;
	Device::listStruct *listPointer = 0;

	while (cdpIssues != 0)
	{
		issueLinksPointer = cdpIssues->next;
		delete cdpIssues;
		cdpIssues = issueLinksPointer;
	}
	while (proxyARPIssues != 0)
	{
		issueLinksPointer = proxyARPIssues->next;
		delete proxyARPIssues;
		proxyARPIssues = issueLinksPointer;
	}
	while (unreachableIssues != 0)
	{
		issueLinksPointer = unreachableIssues->next;
		delete unreachableIssues;
		unreachableIssues = issueLinksPointer;
	}
	while (informationReplyIssues != 0)
	{
		issueLinksPointer = informationReplyIssues->next;
		delete informationReplyIssues;
		informationReplyIssues = issueLinksPointer;
	}
	while (maskReplyIssues != 0)
	{
		issueLinksPointer = maskReplyIssues->next;
		delete maskReplyIssues;
		maskReplyIssues = issueLinksPointer;
	}
	while (redirectsIssues != 0)
	{
		issueLinksPointer = redirectsIssues->next;
		delete redirectsIssues;
		redirectsIssues = issueLinksPointer;
	}
	while (directedIssues != 0)
	{
		issueLinksPointer = directedIssues->next;
		delete directedIssues;
		directedIssues = issueLinksPointer;
	}
	while (mopIssues != 0)
	{
		issueLinksPointer = mopIssues->next;
		delete mopIssues;
		mopIssues = issueLinksPointer;
	}
	while (activeIssues != 0)
	{
		issueLinksPointer = activeIssues->next;
		delete activeIssues;
		activeIssues = issueLinksPointer;
	}
	while (filterIssues != 0)
	{
		issueLinksPointer = filterIssues->next;
		delete filterIssues;
		filterIssues = issueLinksPointer;
	}
	while (trunkingIssues != 0)
	{
		issueLinksPointer = trunkingIssues->next;
		delete trunkingIssues;
		trunkingIssues = issueLinksPointer;
	}
	while (portSecIssues != 0)
	{
		issueLinksPointer = portSecIssues->next;
		delete portSecIssues;
		portSecIssues = issueLinksPointer;
	}

	// Cleanup...
	while (interfaceList != 0)
	{
		while (interfaceList->interface != 0)
		{
			while (interfaceList->interface->vlan != 0)
			{
				listPointer = interfaceList->interface->vlan->next;
				delete interfaceList->interface->vlan;
				interfaceList->interface->vlan = listPointer;
			}
			while (interfaceList->interface->filterIn != 0)
			{
				listPointer = interfaceList->interface->filterIn->next;
				delete interfaceList->interface->filterIn;
				interfaceList->interface->filterIn = listPointer;
			}
			while (interfaceList->interface->filterOut != 0)
			{
				listPointer = interfaceList->interface->filterOut->next;
				delete interfaceList->interface->filterOut;
				interfaceList->interface->filterOut = listPointer;
			}
			interfacePointer = interfaceList->interface->next;
			delete interfaceList->interface;
			interfaceList->interface = interfacePointer;
		}
		interfaceListPointer = interfaceList->next;
		delete interfaceList;
		interfaceList = interfaceListPointer;
	}
}


int Interfaces::addVLAN(interfaceConfig *interfacePointer, const char *vlanName)
{
	// Variables...
	Device::listStruct *listPointer = 0;

	if (interfacePointer->vlan == 0)
	{
		interfacePointer->vlan = new (Device::listStruct);
		listPointer = interfacePointer->vlan;
	}
	else
	{
		listPointer = interfacePointer->vlan;
		while (listPointer->next != 0)
			listPointer = listPointer->next;
		listPointer->next = new (Device::listStruct);
		listPointer = listPointer->next;
	}

	listPointer->listItem.assign(vlanName);
	listPointer->next = 0;

	return 0;
}


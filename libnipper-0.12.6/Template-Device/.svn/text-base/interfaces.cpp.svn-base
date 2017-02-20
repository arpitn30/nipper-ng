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
#include <cstring>
#include <cstdlib>

#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "device.h"
#include "interfaces.h"


<Template>Interfaces::<Template>Interfaces()
{
	// Interface Options...
	useModuleAndPort = false;						// Use the module / port instead of the name
	useInterfaceZone = false;						// Use the interface zone
	zoneName = i18n("Zone");						// The name for zone field
	inboundFilterSupported = false;					// Is the inbound filtering supported?
	filterIn = i18n("Filter In");					// The filter in table title text
	outboudFilterSupported = false;					// Is the outbound filtering supported?
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
}


int <Template>Interfaces::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	return 0;
}


int <Template>Interfaces::processDefaults(Device *device)
{
	return 0;
}


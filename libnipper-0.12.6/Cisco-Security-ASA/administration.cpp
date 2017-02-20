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
#include "../globaldefs.h"
#include "device.h"
#include "administration.h"
#include "../Cisco-Security/general.h"


CiscoASAAdministration::CiscoASAAdministration()
{

	// -----------------------------------------------------------------------
	// ASA Specific Settings...
	// -----------------------------------------------------------------------

	// SSH options...
	sshSupported = true;					// Does this device support SSH?
	sshUpgrade = false;						// Do you have to upgrade?
	sshEnabled = false;						// Is the SSH service enabled?
	sshVersion = 0;							// What is the SSH Protocol version (0 = 1 and 2)

	// SSH 2 support...
	ssh2Supported = true;					// Does the device support SSH version 2?
	ssh2upgrade = false;					// Do you have to upgrade...
	scpSupported = true;					// Is SCP supported?

	// Config report SSH support text
	sshConfigProtocolSupport = i18n("*DEVICETYPE* devices support both *ABBREV*SSH*-ABBREV* protocol versions 1 and 2.");

	// HTTP(S) options...
	httpSupported = true;					// Does this device support HTTP
	httpsSupported = true;					// Does this device support HTTPS
	httpsUpgrade = false;					// Do you have to upgrade for HTTPS?
	httpEnabled = false;					// Is the HTTP service enabled?
	httpsEnabled = false;					// Is the HTTPS service enabled?
	httpsRedirect = true;					// Is HTTP to HTTPS redirect enabled?
}



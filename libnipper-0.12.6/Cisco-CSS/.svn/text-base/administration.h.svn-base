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

#ifndef device_CiscoCSSAdministration_H
#define device_CiscoCSSAdministration_H


#include "../device/administration/administration.h"


class CiscoCSSAdministration : public Administration
{
	public:

		CiscoCSSAdministration();

		// Device specific methods...
		virtual int processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize);
		virtual int processDefaults(Device *device);
		virtual int generateDeviceGeneralConfig(Device *device);		// A device specific config report output
		virtual int generateSecuritySpecificReport(Device *device);
		virtual int generateDeviceSSHConfig(Device *device);

		// Custom settings...
		bool userRestrictions;					// The user database setting...
		bool ciscoViewDeviceManager;			// As it says...
		bool sshdKeepAlives;					// SSHD Keep Alive Messages...
		int sshServerKeyBits;					// The SSH Server Key bits...
};


#endif

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

#ifndef ProCurveadministration_H
#define ProCurveadministration_H


#include "../device/administration/administration.h"


class ProCurveAdministration : public Administration
{
	public:

		ProCurveAdministration();

		// Device specific methods...
		virtual int processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize);
		virtual int processDefaults(Device *device);

		// Methods
		virtual int generateDeviceGeneralConfig(Device *device);	// A device specific config report output
		virtual int generateDeviceTelnetConfig(Device *device);		// A device specific config report output
		virtual int generateDeviceTFTPConfig(Device *device);		// A device specific config report output
		virtual int generateDeviceSSHConfig(Device *device);		// A device specific config report output
		virtual int generateDeviceHTTPConfig(Device *device);		// A device specific config report output

		// HP Procurve specific settings...
		int consoleBaudRate;				// The console line baud rate
		bool consoleFlowXONControl;			// Flow Control
		int consoleLocalType;				// 0 = VT100, 1 = none, 2 = ANSI
		int consoleAllType;					// 0 = VT100, 1 = none, 2 = ANSI
		bool telnet6ServerEnabled;			// Telnet IPv6 Server
		bool tftp6ServerEnabled;			// TFTP IPv6 Server
		int sshIPProtocol;					// SSH IP (0 = 4 & 6, 4 = 4, 6 =6)
		string webManagementURL;			// The URL to go to when ? is clicked
		string webSupportURL;				// The URL to go to when the support tab is clicked
};


#endif

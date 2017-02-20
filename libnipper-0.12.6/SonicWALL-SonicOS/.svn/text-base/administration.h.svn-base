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

#ifndef SonicOSadministration_H
#define SonicOSadministration_H


// Includes...
#include "../device/administration/administration.h"


class SonicOSAdministration : public Administration
{
	public:

		SonicOSAdministration();
		~SonicOSAdministration();

		// Device specific methods...
		virtual int processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize);
		virtual int processDefaults(Device *device);


		struct managementInterface
		{
			int interface;
			string name;
			string zone;
			string comment;
			bool http;
			bool httpLogin;
			bool httpRedirect;
			bool https;
			bool httpsLogin;
			bool ssh;
			bool snmp;
			struct managementInterface *next;
		};

		managementInterface *sonicosInterfaces;


		// Methods
		int generateDeviceSSHConfig(Device *device);		// A device specific config report output
		int generateDeviceHTTPConfig(Device *device);		// A device specific config report output
		managementInterface *getInterface(int number);
};


#endif

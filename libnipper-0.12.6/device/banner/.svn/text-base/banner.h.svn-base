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

#ifndef devicebanner_H
#define devicebanner_H


#include "../common/deviceconfig.h"

// Connection types...
#define anyConnection 15
#define consoleConnection 1
#define telnetConnection 2
#define sshConnection 4
#define modemConnection 8
#define webvpnConnection 16
#define reverseTelnetConnection 32
#define pppConnection 64


class Banner : public DeviceConfig
{
	public:

		Banner();
		virtual ~Banner();

	// -----------------------------------------------------------------------
	// Standard Device Class Methods...
	// -----------------------------------------------------------------------

		virtual int generateConfigReport(Device *device);
		virtual int generateSecurityReport(Device *device);


	protected:


		virtual int generateConfigBannerReport(Device *device);

	// -----------------------------------------------------------------------
	// Banner Support...
	// -----------------------------------------------------------------------

		bool preLogonBanner;					// Support Banner(s) Before Logon?
		bool postLogonBanner;					// Support Banner(s) After Logon?

		const char *configPreLogonBanner;		// The text that explains how to config a prelogon banner, with commands...
		const char *configPostLogonBanner;		// The text that explains how to config a post logon banner, with commands...

	// -----------------------------------------------------------------------
	// Banner Structures...
	// -----------------------------------------------------------------------

		struct bannerTextStruct
		{
			string bannerLine;
			struct bannerTextStruct *next;
		};

		enum bannerType
		{
			preLogon = 0,
			postLogon = 1,
			levelChange = 2
		};

		enum bannerInfoLeak
		{
			noInfoLeak = 0,
			containsHostname = 1,
			containsMake = 2,
			containsModel = 3,
			containsType = 4,
			containsOS = 5
		};

		struct bannerStruct
		{
			enum bannerType banner;			// Does the banner appear before the logon prompt?
			string name;						// The name of the banner, such as MOTD
			string description;					// For the config report
			bool enabled;						// Is the banner enabled?
			int connectionType;					// The connection type it is for
			enum bannerInfoLeak leak;			// Set if the banner is determined to leak information
			bool noWarning;						// Set if the banner is determined to not contain a warning
			bannerTextStruct *bannerText;		// The banner text
			bool bannerFile;					// The banner is a file
			string filename;					// The banner filename
			struct bannerStruct *next;
		};

		bannerStruct *banner;

		bannerStruct *addBanner();												// Add a new banner...
		bannerStruct *getBanner(const char *name);								// Gets an existing banner...
		int addBannerLine(bannerStruct *bannerPointer, const char *line);		// Add a line to a banner...
};


#endif

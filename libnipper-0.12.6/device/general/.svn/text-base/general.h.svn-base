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

#ifndef devicegeneral_H
#define devicegeneral_H

#include <string>
#include "../common/deviceconfig.h"


using namespace std;

class Device;

class General : public DeviceConfig
{
  public:

	General();
	virtual ~General();

	// Methods...
	virtual int generateConfigReport(Device *device);
	virtual int generateSecurityReport(Device *device);

	// Properties...
	string hostname;
	string deviceModel;
	string version;
	unsigned int versionMajor;
	unsigned int versionMinor;
	unsigned int versionRevision;
	unsigned int versionTweak;

	// Version resolution
	bool noMinor;
	bool noRevision;
	bool noTweak;

	// Vulnerabilities...
	struct vulnVersionConfig
	{
		unsigned int versionMajor;
		unsigned int versionMinor;
		unsigned int versionRevision;
		unsigned int versionTweak;
		unsigned int endVersionMajor;
		unsigned int endVersionMinor;
		unsigned int endVersionRevision;
		unsigned int endVersionTweak;
		struct vulnVersionConfig *next;
	};
	struct vulnerabilityConfig
	{
		const char *description;			// Vulnerability Description
		bool dos;							// Is it a DoS
		bool remote;						// Is it a remote command execution
		const char *cveReference;			// CVE
		const char *bidReference;			// BID
		const char *otherReference;			// Other reference
		vulnVersionConfig *versions;		// Vulnerable versions
		bool vulnerable;					// Is it vulnerable
		struct vulnerabilityConfig *next;	// Next
	};

  protected:

	void addDeviceModule(int slot, const char *module, const char *options = 0);

	// Structures...
	struct deviceModuleStruct
	{
		int slot;
		string description;
		string options;
		struct deviceModuleStruct *next;
	};

	// Properties...
	string location;
	string contact;
	deviceModuleStruct *modules;

	vulnerabilityConfig *vulnerabilities;
};

#endif

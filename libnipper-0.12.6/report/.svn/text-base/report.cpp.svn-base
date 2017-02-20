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

// Includes...
#include "../globaldefs.h"
#include "report.h"
#include "../config.h"
#include "../device/device.h"


// Write the report - it pulls together all the report writing code...
int Report::write()
{
	// Variables...
	Device::johnPasswordStruct *johnPointer = 0;
	FILE *johnOutputFile = 0;
	int errorCode = 0;

	// Check config and device are there...
	if ((config == 0) || (device == 0))
		return libnipper_error_noconfdev;

	// Open output for writing...
	if (config->outputDestination == 0)
		outFile = stdout;
	else
	{
		outFile = fopen(config->outputDestination, "w");
		if (outFile == NULL)
			return libnipper_error_nooutput;
	}

	// Write the start of the report...
	errorCode = writeReportStart();
	if (errorCode != 0)
		return errorCode;

	// Write front page...
	errorCode = writeFrontPage();
	if (errorCode != 0)
		return errorCode;

	// Write contents page...
	errorCode = writeContentsPage();
	if (errorCode != 0)
		return errorCode;

	// Write report introduction pages...
	errorCode = writeIntroductionPage();
	if (errorCode != 0)
		return errorCode;

	// Write security audit section...
	if (config->includeSecurityAudit == true)
	{
		errorCode = writeSecuritySection();
		if (errorCode != 0)
			return errorCode;
	}

	// Write compliancy testing section...
	if (config->includeComplianceCheck == true)
	{
		writeComplianceSection();
	}

	// Write configuration report section...
	if ((config->includeConfigurationReport == true) && (device->configReport != 0))
	{
		errorCode = writeConfigurationSection();
		if (errorCode != 0)
			return errorCode;
	}

	// Write appendix section...
	if (config->includeAppendixSection == true)
	{
		errorCode = writeAppendixSection();
		if (errorCode != 0)
			return errorCode;
	}

	// Write the end of the report...
	writeReportEnd();

	// Close Output...
	if (config->outputDestination != 0)
		fclose(outFile);

	// Write john-the-ripper output if specified and exists...
	if ((config->johnFile != 0) && (device->johnPassword != 0)) 
	{
		johnOutputFile = fopen(config->johnFile, "w");
		if (johnOutputFile == NULL)
			return libnipper_error_nojohn;
		johnPointer = device->johnPassword;
		while (johnPointer != 0)
		{
			fprintf(johnOutputFile, "%s:%s\n", johnPointer->user.c_str(), johnPointer->password.c_str());
			johnPointer = johnPointer->next;
		}
		fclose(johnOutputFile);
	}

	return 0;
}


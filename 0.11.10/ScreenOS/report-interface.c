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

// This file contains code for ScreenOS Interface reporting


void sosInterfaceConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct interfaceSOS *interfaceSOSPointer = 0;
	char tempString[nipper->maxSize];

	output_table(nipper, true, settings_inter_table, &settings_interSOS_heading);
	interfaceSOSPointer = nipper->sos->interface;
	while (interfaceSOSPointer != 0)
	{
		outputFriendly(interfaceSOSPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
		if (interfaceSOSPointer->enabled == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_mid);
		outputFriendly(interfaceSOSPointer->ipAddress, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
		outputFriendly(interfaceSOSPointer->zone, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
		if (interfaceSOSPointer->manageIdent == true)
			fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
		else if (interfaceSOSPointer->manageIdent == false)
			fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "-%s", nipper->tablerow_mid);
		if (interfaceSOSPointer->manageMtrace == true)
			fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
		else if (interfaceSOSPointer->manageMtrace == false)
			fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "-%s", nipper->tablerow_mid);
		if (interfaceSOSPointer->manageNsmgmt == true)
			fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
		else if (interfaceSOSPointer->manageNsmgmt == false)
			fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "-%s", nipper->tablerow_mid);
		if (interfaceSOSPointer->managePing == true)
			fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
		else if (interfaceSOSPointer->managePing == false)
			fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "-%s", nipper->tablerow_mid);
		if (interfaceSOSPointer->manageSnmp == true)
			fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
		else if (interfaceSOSPointer->manageSnmp == false)
			fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "-%s", nipper->tablerow_mid);
		if (interfaceSOSPointer->manageSsh == true)
			fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
		else if (interfaceSOSPointer->manageSsh == false)
			fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "-%s", nipper->tablerow_mid);
		if (interfaceSOSPointer->manageSsl == true)
			fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
		else if (interfaceSOSPointer->manageSsl == false)
			fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "-%s", nipper->tablerow_mid);
		if (interfaceSOSPointer->manageTelnet == true)
			fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
		else if (interfaceSOSPointer->manageTelnet == false)
			fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "-%s", nipper->tablerow_mid);
		if (interfaceSOSPointer->manageWeb == true)
			fprintf(nipper->reportFile, "On%s", nipper->tablerow_end);
		else if (interfaceSOSPointer->manageWeb == false)
			fprintf(nipper->reportFile, "Off%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "-%s", nipper->tablerow_end);
		interfaceSOSPointer = interfaceSOSPointer->next;
	}
	output_table(nipper, false, settings_inter_table, &settings_interSOS_heading);
	addAbbreviation("SNMP", false);
	addAbbreviation("SSL", false);
}


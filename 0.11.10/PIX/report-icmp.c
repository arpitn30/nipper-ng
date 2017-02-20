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


void pixICMPConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct icmpAccess *icmpPIXPointer = 0;
	char tempString[nipper->maxSize];

	// Intro
	output_parseText(settings_icmpaccess_desc, nipper, section_none, rate_none, 0, 0);
	output_table(nipper, true, settings_icmpaccess_table, &settings_icmpaccess_heading);
	icmpPIXPointer = nipper->pix->icmp;
	while (icmpPIXPointer != 0)
	{
		if (icmpPIXPointer->permission == perm_permit)
			fprintf(nipper->reportFile, "%sPermit%s", nipper->tablerow_start, nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "%sDeny%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (strcasecmp(icmpPIXPointer->source, "any") == 0)
			fprintf(nipper->reportFile, "Any%s", nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "%s%s", icmpPIXPointer->source, nipper->tablerow_mid);
		if (icmpPIXPointer->icmpType[0] != 0)
			fprintf(nipper->reportFile, "%s", icmpPIXPointer->icmpType);
		else
			fprintf(nipper->reportFile, "Any");
		outputFriendly(icmpPIXPointer->interface, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, tempString, nipper->tablerow_end);
		icmpPIXPointer = icmpPIXPointer->next;
	}
	output_table(nipper, false, settings_icmpaccess_table, &settings_icmpaccess_heading);
}


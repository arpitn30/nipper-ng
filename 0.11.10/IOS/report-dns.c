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

// This file contains the code for IOS reporting

void iosDNSConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct host *dnsPointer = 0;
	char tempString[nipper->maxSize];
	int tempInt = 0;

	output_table(nipper, true, settings_dns_table, &settings_general_heading);
	if (nipper->domainName[0] != 0)
	{
		outputFriendly(nipper->domainName, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%sDomain Name%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
	}
	if (nipper->ios->domainLookup == false)
		fprintf(nipper->reportFile, "%sDomain Lookup%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sDomain Lookup%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	tempInt = 1;
	dnsPointer = nipper->ios->dns;
	while (dnsPointer != 0)
	{
		fprintf(nipper->reportFile, "%sDNS Server %d%s%s%s", nipper->tablerow_start, tempInt, nipper->tablerow_mid, dnsPointer->server, nipper->tablerow_end);
		tempInt++;
		dnsPointer = dnsPointer->next;
	}
	output_table(nipper, false, settings_dns_table, &settings_general_heading);
}


void iosDomainLookupIssue(struct nipperConfig *nipper)
{
	// Variables...
	int tempInt = 0;

	if (nipper->ios->dns == 0)
		tempInt = 1;
	else
		tempInt = 2;
	output_parseText(report_lookup_obs, nipper, section_obs, rate_none, tempInt, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_lookup_impact, nipper, section_imp, rate_low, tempInt, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_lookup_ease, nipper, section_ease, rate_trivial, tempInt, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_lookup_rec, nipper, section_rec, rate_none, tempInt, nipper->tableNum);
	output_endsection(nipper, section_rec);
}

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

void iosNATConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct natConfig *natPointer = 0;
	int tempInt = 0;
	char tempString[nipper->maxSize];

	output_parseText(settings_natpat_desc, nipper, section_none, rate_none, 2, 0);

	// Static NAT
	tempInt = 0;
	natPointer = nipper->ios->nat;
	while (natPointer != 0)
	{
		if (natPointer->type == nat_static)
			tempInt++;
		natPointer = natPointer->next;
	}
	if (tempInt > 0)
	{
		output_table(nipper, true, settings_nat_static_table, &settings_natstatic_heading);
		natPointer = nipper->ios->nat;
		while (natPointer != 0)
		{
			if (natPointer->type == nat_static)
			{
				if (natPointer->inside == true)
					fprintf(nipper->reportFile, "%sInside Interface%s", nipper->tablerow_start, nipper->tablerow_mid);
				else
					fprintf(nipper->reportFile, "%sOutside Interface%s", nipper->tablerow_start, nipper->tablerow_mid);
				if (natPointer->ipSecESP == true)
					fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_mid);
				else
					fprintf(nipper->reportFile, "No%s", nipper->tablerow_mid);
				outputFriendly(natPointer->local, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
				outputFriendly(natPointer->global, tempString, nipper->maxSize, nipper->outputFormat);
				if (natPointer->ipSecESP == true)
					fprintf(nipper->reportFile, "%s%d%s", tempString, natPointer->interNumber, nipper->tablerow_end);
				else
					fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_end);
			}
			natPointer = natPointer->next;
		}
		output_table(nipper, false, settings_nat_static_table, &settings_natstatic_heading);
	}

	// Dynamic NAT
	tempInt = 0;
	natPointer = nipper->ios->nat;
	while (natPointer != 0)
	{
		if ((natPointer->type == nat_dynamic_acl) || (natPointer->type == nat_dynamic_route))
			tempInt++;
		natPointer = natPointer->next;
	}
	if (tempInt > 0)
	{
		output_table(nipper, true, settings_nat_dynamic_table, &settings_natdynamic_heading);
		natPointer = nipper->ios->nat;
		while (natPointer != 0)
		{
			if ((natPointer->type == nat_dynamic_acl) || (natPointer->type == nat_dynamic_route))
			{
				if (natPointer->inside == true)
					fprintf(nipper->reportFile, "%sInside Interface%s", nipper->tablerow_start, nipper->tablerow_mid);
				else
					fprintf(nipper->reportFile, "%sOutside Interface%s", nipper->tablerow_start, nipper->tablerow_mid);
				if (natPointer->type == nat_dynamic_acl)
					fprintf(nipper->reportFile, "ACL%s", nipper->tablerow_mid);
				else
					fprintf(nipper->reportFile, "Route Map%s", nipper->tablerow_mid);
				outputFriendly(natPointer->local, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
				outputFriendly(natPointer->global, tempString, nipper->maxSize, nipper->outputFormat);
				if (natPointer->pool == true)
				{
					fprintf(nipper->reportFile, "Pool%s", nipper->tablerow_mid);
					fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_end);
				}
				else
				{
					fprintf(nipper->reportFile, "Interface%s", nipper->tablerow_mid);
					fprintf(nipper->reportFile, "%s%d%s", tempString, natPointer->interNumber, nipper->tablerow_end);
				}
			}
			natPointer = natPointer->next;
		}
		output_table(nipper, false, settings_nat_dynamic_table, &settings_natdynamic_heading);
	}

	// Port Static NAT
	tempInt = 0;
	natPointer = nipper->ios->nat;
	while (natPointer != 0)
	{
		if (natPointer->type == nat_port)
			tempInt++;
		natPointer = natPointer->next;
	}
	if (tempInt > 0)
	{
		output_table(nipper, true, settings_nat_portstatic_table, &settings_natportstat_heading);
		natPointer = nipper->ios->nat;
		while (natPointer != 0)
		{
			if (natPointer->type == nat_port)
			{
				if (natPointer->inside == true)
					fprintf(nipper->reportFile, "%sInside Interface%s", nipper->tablerow_start, nipper->tablerow_mid);
				else
					fprintf(nipper->reportFile, "%sOutside Interface%s", nipper->tablerow_start, nipper->tablerow_mid);
				if (natPointer->inter == true)
				{
					fprintf(nipper->reportFile, "%s %s %s %s%d%s", nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, natPointer->globalPort, nipper->tablerow_end);
				}
				else
				{
					outputFriendly(natPointer->local, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
					fprintf(nipper->reportFile, "%d%s", natPointer->localPort, nipper->tablerow_mid);
					outputFriendly(natPointer->global, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s%d%s", tempString, nipper->tablerow_mid, natPointer->globalPort, nipper->tablerow_end);
				}
			}
			natPointer = natPointer->next;
		}
		output_table(nipper, false, settings_nat_portstatic_table, &settings_natportstat_heading);
	}

	// Network Static NAT
	tempInt = 0;
	natPointer = nipper->ios->nat;
	while (natPointer != 0)
	{
		if (natPointer->type == nat_network)
			tempInt++;
		natPointer = natPointer->next;
	}
	if (tempInt > 0)
	{
		output_table(nipper, true, settings_nat_netstatic_table, &settings_natnetstatic_heading);
		natPointer = nipper->ios->nat;
		while (natPointer != 0)
		{
			if (natPointer->type == nat_network)
			{
				if (natPointer->inside == true)
					fprintf(nipper->reportFile, "%sInside Interface%s", nipper->tablerow_start, nipper->tablerow_mid);
				else
					fprintf(nipper->reportFile, "%sOutside Interface%s", nipper->tablerow_start, nipper->tablerow_mid);
					outputFriendly(natPointer->local, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
					outputFriendly(natPointer->global, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
					outputFriendly(natPointer->mask, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_end);
			}
			natPointer = natPointer->next;
		}
		output_table(nipper, false, settings_nat_netstatic_table, &settings_natnetstatic_heading);
	}
}

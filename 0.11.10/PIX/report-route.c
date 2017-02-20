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


void pixRoutingConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct routePIX *routePIXPointer = 0;
	char tempString[nipper->maxSize];

	output_parseText(settings_routing_desc, nipper, section_none, rate_none, 0, 0);
	output_table(nipper, true, settings_static_route_table, &settings_route_heading);
	routePIXPointer = nipper->pix->route;
	while (routePIXPointer != 0)
	{
		outputFriendly(routePIXPointer->interface, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile,"%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
		outputFriendly(routePIXPointer->ipAddress, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
		outputFriendly(routePIXPointer->netMask, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
		outputFriendly(routePIXPointer->gateway, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
		fprintf(nipper->reportFile, "%d%s", routePIXPointer->metric, nipper->tablerow_mid);
		if (routePIXPointer->track == 0)
			fprintf(nipper->reportFile, "-%s", nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "%d%s", routePIXPointer->track, nipper->tablerow_mid);
		if (routePIXPointer->tunneled == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		routePIXPointer = routePIXPointer->next;
	}
	output_table(nipper, false, settings_static_route_table, &settings_route_heading);
}


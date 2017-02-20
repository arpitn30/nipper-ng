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


void sonicosServicesConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct objectListConfig *objectListPointer = 0;
	struct objectConfig *objectPointer = 0;
	char tempString[nipper->maxSize];

	objectListPointer = getObjectListPointer(nipper, "SERVICES");
	output_table(nipper, true, settings_sonicosservices_table, &settings_sonicosservices_heading);
	objectPointer = objectListPointer->object;
	while (objectPointer != 0)
	{
		fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, objectPointer->name, nipper->tablerow_mid);
		addAbbreviation(objectPointer->comment, false);
		outputFriendly(objectPointer->comment, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
		switch (objectPointer->type)
		{
			case object_type_service:
				fprintf(nipper->reportFile, "%s%s", objectPointer->address, nipper->tablerow_mid);
				break;
			case object_type_servicerange:
				fprintf(nipper->reportFile, "%s - %s%s", objectPointer->address, objectPointer->netMask, nipper->tablerow_mid);
				break;
			case object_type_any:
				fprintf(nipper->reportFile, "1 - 65535%s", nipper->tablerow_mid);
				break;
		}
		switch (objectPointer->serviceType)
		{
			case 1:
				fprintf(nipper->reportFile, "ICMP");
				addAbbreviation("ICMP", false);
				break;
			case 6:
				fprintf(nipper->reportFile, "TCP");
				addAbbreviation("TCP", false);
				break;
			case 17:
				fprintf(nipper->reportFile, "UDP");
				addAbbreviation("UDP", false);
				break;
			case 255:
				fprintf(nipper->reportFile, "Any");
				break;
			default:
				fprintf(nipper->reportFile, "%d", objectPointer->serviceType);
				break;
		}
		fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
		objectPointer = objectPointer->next;
	}
	output_table(nipper, false, settings_sonicosservices_table, &settings_sonicosservices_heading);
}


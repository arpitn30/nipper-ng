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

// This file contains code for ScreenOS Policy reporting


void sosNameMapConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct objectListConfig *objectListPointer = 0;
	struct objectConfig *objectPointer = 0;
	char tempString[nipper->maxSize];
	char tempString2[nipper->maxSize];

	objectListPointer = nipper->objectList;
	while (objectListPointer != 0)
	{
		if (strncmp(objectListPointer->name, "**ADDR-GRP**", 12) != 0)
		{
			sprintf(tempString2, "Zone %s name mappings", objectListPointer->name);
			outputFriendly(tempString2, tempString, nipper->maxSize, nipper->outputFormat);
			output_table(nipper, true, tempString, &settings_namemapSOS_heading);
			objectPointer = objectListPointer->object;
			while (objectPointer != 0)
			{
				outputFriendly(objectPointer->name, tempString2, nipper->maxSize, nipper->outputFormat);
				if (nipper->outputFormat == output_html)
					fprintf(nipper->reportFile, "%s<a name=\"object-%s\">%s</a>%s", nipper->tablerow_start, tempString2, tempString2, nipper->tablerow_mid);
				else
					fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString2, nipper->tablerow_mid);
				outputFriendly(objectPointer->address, tempString2, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", tempString2, nipper->tablerow_mid);
				outputFriendly(objectPointer->netMask, tempString2, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", tempString2, nipper->tablerow_mid);
				outputFriendly(objectPointer->comment, tempString2, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", tempString2, nipper->tablerow_end);
				objectPointer = objectPointer->next;
			}
			output_table(nipper, false, tempString, &settings_namemapSOS_heading);
		}
		objectListPointer = objectListPointer->next;
	}
}


void sosNameGroupMapConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct objectListConfig *objectListPointer = 0;
	struct objectConfig *objectPointer = 0;
	struct objectMember *memberPointer = 0;
	char tempString[nipper->maxSize];
	char tempString2[nipper->maxSize];

	objectListPointer = nipper->objectList;
	while (objectListPointer != 0)
	{
		if (strncmp(objectListPointer->name, "**ADDR-GRP**", 12) == 0)
		{

			sprintf(tempString, "Zone %s name mapping groups", objectListPointer->name + 12);
			outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
			if (nipper->outputFormat == output_html)
				fprintf(nipper->reportFile, "<a name=\"object-%s\">", objectListPointer->name + 12);
			output_table(nipper, true, tempString2, &settings_namemapgroup_heading);

			objectPointer = objectListPointer->object;
			while (objectPointer != 0)
			{

				memberPointer = objectPointer->members;
				while (memberPointer != 0)
				{
					outputFriendly(objectPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
					if (nipper->outputFormat == output_html)
						fprintf(nipper->reportFile, "%s<a href=\"object-%s\">%s</a>%s", nipper->tablerow_start, tempString, tempString, nipper->tablerow_mid);
					else
						fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
					outputFriendly(memberPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_end);
					memberPointer = memberPointer->next;
				}

				objectPointer = objectPointer->next;
			}

			output_table(nipper, false, tempString2, &settings_namemapgroup_heading);
			if (nipper->outputFormat == output_html)
				fprintf(nipper->reportFile, "</a>");
		}
		objectListPointer = objectListPointer->next;
	}
}

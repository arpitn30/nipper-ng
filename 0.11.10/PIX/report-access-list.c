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


void pixACLConfig(struct nipperConfig *nipper)
{
	// Intro text
	output_parseText(settings_accesslists1, nipper, section_none, rate_none, 0, 0);
	if (nipper->outputFormat == output_xml)
		fprintf(nipper->reportFile, "</text>\n");
	output_newPara(nipper);
	output_parseText(settings_accesslists3, nipper, section_none, rate_none, 0, 0);

	// General ACL Settings
	output_table(nipper, true, settings_accesslist_table, &settings_general_heading);
	fprintf(nipper->reportFile, "%sAlert Interval%s%d seconds%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->pix->accessListAlertInterval, nipper->tablerow_end);
	fprintf(nipper->reportFile, "%sMaximum Deny Flows%s%d%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->pix->accessListDenyFlowMax, nipper->tablerow_end);
	output_table(nipper, false, settings_accesslist_table, &settings_general_heading);

	// ACL
	reportRules(nipper);
}


void pixObjectConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct objectListConfig *objectListPointer = 0;
	struct objectConfig *objectPointer = 0;
	struct objectMember *memberPointer = 0;
	char tempString[nipper->maxSize];
	char tempString2[nipper->maxSize];

	// Intro
	output_parseText(settings_objects_desc, nipper, section_none, rate_none, 0, 0);
	output_list(nipper, &settings_objects_heading);

	// Get pointer to object list...
	objectListPointer = getObjectListPointer(nipper, "OBJECTLIST");

	objectPointer = objectListPointer->object;
	while (objectPointer != 0)
	{

		if (nipper->outputFormat == output_html)
			fprintf(nipper->reportFile, "<a name=\"object-%s\">", objectPointer->name);

		// Generate Table Heading...
		if (objectPointer->type == object_type_group)
		{
			if (objectPointer->comment[0] == 0)
				sprintf(tempString, "Network %s %s", settings_objects_table, objectPointer->name);
			else
				sprintf(tempString, "Network %s %s (%s)", settings_objects_table, objectPointer->name, objectPointer->comment);
		}
		else if (objectPointer->type == object_type_protocol)
		{
			if (objectPointer->comment[0] == 0)
				sprintf(tempString, "Protocol %s %s", settings_objects_table, objectPointer->name);
			else
				sprintf(tempString, "Protocol %s %s (%s)", settings_objects_table, objectPointer->name, objectPointer->comment);
		}
		else if (objectPointer->type == object_type_service)
		{
			if (objectPointer->comment[0] == 0)
				sprintf(tempString, "Service %s %s", settings_objects_table, objectPointer->name);
			else
				sprintf(tempString, "Service %s %s (%s)", settings_objects_table, objectPointer->name, objectPointer->comment);
		}
		else if (objectPointer->type == object_type_icmp)
		{
			if (objectPointer->comment[0] == 0)
				sprintf(tempString, "ICMP %s %s", settings_objects_table, objectPointer->name);
			else
				sprintf(tempString, "ICMP %s %s (%s)", settings_objects_table, objectPointer->name, objectPointer->comment);
		}
		outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
		output_table(nipper, true, tempString2, &settings_object_heading);

		// Output Table Contents...
		memberPointer = objectPointer->members;
		while (memberPointer != 0)
		{
			switch (memberPointer->type)
			{
				case object_type_group:
					outputFriendly(memberPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%sObject Group%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
					break;
				case object_type_port:
					fprintf(nipper->reportFile, "%sPort%s", nipper->tablerow_start, nipper->tablerow_mid);
					if (memberPointer->serviceOp == service_oper_eq)
						fprintf(nipper->reportFile, "%s%s", memberPointer->name, nipper->tablerow_end);
					else
						fprintf(nipper->reportFile, "%s - %s%s", memberPointer->name, memberPointer->netMask, nipper->tablerow_end);
					addAbbreviation(objectPointer->name, false);
					break;
				case object_type_service:
					fprintf(nipper->reportFile, "%sService%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, memberPointer->name, nipper->tablerow_end);
					addAbbreviation(objectPointer->name, false);
					break;
				case object_type_network:
					fprintf(nipper->reportFile, "%sNetwork%s%s / %s%s", nipper->tablerow_start, nipper->tablerow_mid, memberPointer->name, memberPointer->netMask, nipper->tablerow_end);
					break;
				case object_type_host:
					fprintf(nipper->reportFile, "%sHost%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, memberPointer->name, nipper->tablerow_end);
					break;
				case object_type_protocol:
					addAbbreviation(objectPointer->name, false);
					fprintf(nipper->reportFile, "%sProtocol%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, memberPointer->name, nipper->tablerow_end);
					break;
				case object_type_icmp:
					fprintf(nipper->reportFile, "%sICMP%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, memberPointer->name, nipper->tablerow_end);
					addAbbreviation("ICMP", false);
					break;
			}
			memberPointer = memberPointer->next;
		}
		output_table(nipper, false, tempString2, &settings_object_heading);

		if (nipper->outputFormat == output_html)
			fprintf(nipper->reportFile, "</a>");

		objectPointer = objectPointer->next;
	}
}


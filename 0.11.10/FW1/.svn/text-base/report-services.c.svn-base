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


// Services
void fw1ServiceConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct objectConfig *objectPointer = 0;
	struct objectListConfig *objectListPointer = 0;
	char tempString[nipper->maxSize];

	output_table(nipper, true, settings_fw1services_title, &settings_fw1services_heading);
	objectListPointer = getObjectListPointer(nipper, "FW1-Services");
	objectPointer = objectListPointer->object;
	while (objectPointer != 0)
	{
		if (objectPointer->type != object_type_group)
		{
			outputFriendly(objectPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
			addAbbreviation(objectPointer->name, false);
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
			switch (objectPointer->serviceType)
			{
				case service_protocol_tcp:
					addAbbreviation("TCP", false);
					fprintf(nipper->reportFile, "TCP");
					break;
				case service_protocol_udp:
					addAbbreviation("UDP", false);
					fprintf(nipper->reportFile, "UDP");
					break;
				case service_protocol_other:
					fprintf(nipper->reportFile, "Other");
					break;
				case service_protocol_dcerpc:
					fprintf(nipper->reportFile, "DCE/RPC");
					addAbbreviation("DCERPC", false);
					addAbbreviation("RPC", false);
					addAbbreviation("DCE", false);
					break;
				case service_protocol_rpc:
					fprintf(nipper->reportFile, "RPC");
					addAbbreviation("RPC", false);
					break;
				case service_protocol_icmp:
					fprintf(nipper->reportFile, "ICMP");
					addAbbreviation("ICMP", false);
					break;
				case service_protocol_tcpsub:
					fprintf(nipper->reportFile, "TCP Sub");
					addAbbreviation("TCP", false);
					break;
				case service_protocol_gtp0:
					fprintf(nipper->reportFile, "GTP v0");
					addAbbreviation("GTP", false);
					break;
				case service_protocol_gtp1:
					fprintf(nipper->reportFile, "GTP v1");
					addAbbreviation("GTP", false);
					break;
				default:
					fprintf(nipper->reportFile, "Unknown");
					break;
			}
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, objectPointer->address, nipper->tablerow_mid);
			outputFriendly(objectPointer->comment, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_end);
		}
		objectPointer = objectPointer->next;
	}
	output_table(nipper, false, settings_fw1services_title, &settings_fw1services_heading);
}


// Service Groups
void fw1ServiceGroupConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct objectConfig *objectPointer = 0;
	struct objectListConfig *objectListPointer = 0;
	struct objectMember *memberPointer = 0;
	char tempString[nipper->maxSize];
	char tempString2[nipper->maxSize];

	objectListPointer = getObjectListPointer(nipper, "FW1-Services");
	objectPointer = objectListPointer->object;
	while (objectPointer != 0)
	{
		if (objectPointer->type == object_type_group)
		{
			sprintf(tempString, "%s %s", objectPointer->name, settings_fw1servicegroup_table);
			outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
			output_table(nipper, true, tempString, &settings_fw1servicegroup_heading);
			memberPointer = objectPointer->members;
			while (memberPointer != 0)
			{
				outputFriendly(memberPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_end);
				memberPointer = memberPointer->next;
			}
			output_table(nipper, false, tempString2, &settings_fw1servicegroup_heading);
		}
		objectPointer = objectPointer->next;
	}
}


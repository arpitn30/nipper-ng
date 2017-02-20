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

// This file contains the code that handles the reporting for FW1 Objects


// Object Definitions (Gateway Clusters...)
void fw1GatewayClusterConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct objectConfig *objectPointer = 0;
	struct objectListConfig *objectListPointer = 0;
	struct hostInterfaces *fw1InterfacePointer = 0;
	struct objectMember *memberPointer = 0;
	char tempString[nipper->maxSize];
	char tempString2[nipper->maxSize];

	objectListPointer = getObjectListPointer(nipper, "FW1-Objects");
	objectPointer = objectListPointer->object;
	while (objectPointer != 0)
	{
		if (objectPointer->type == object_type_gateway_cluster)
		{
			// Gateway Configuration Settings...
			if (nipper->outputFormat == output_html)
				fprintf(nipper->reportFile, "<a name=\"object-%s\">", objectPointer->name);
			sprintf(tempString, "%s %s", objectPointer->name, settings_objects_gatewaycluster_table);
			outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
			output_table(nipper, true, tempString2, &settings_general_heading);
			outputFriendly(objectPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%sGateway Cluster Name%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sIP Address%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, objectPointer->address, nipper->tablerow_end);
			if (objectPointer->firewall == true)
				fprintf(nipper->reportFile, "%sFirewall%sYes%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "%sFirewall%sNo%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sCheckPoint Version%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, objectPointer->cpVersion, nipper->tablerow_end);
			if (objectPointer->internal == true)
				fprintf(nipper->reportFile, "%sManaged%sYes%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "%sManaged%sNo%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			output_table(nipper, false, tempString2, &settings_general_heading);
			if (nipper->outputFormat == output_html)
				fprintf(nipper->reportFile, "</a>");

			// Gateway Cluster Interfaces...
			fw1InterfacePointer = objectPointer->interfaces;
			if (fw1InterfacePointer != 0)
			{
				sprintf(tempString, "%s %s", objectPointer->name, settings_objects_gatewaycluster_int_table);
				outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
				output_table(nipper, true, tempString2, &settings_object_gateinter_heading);
				while (fw1InterfacePointer != 0)
				{
					fprintf(nipper->reportFile, "%s%d%s", nipper->tablerow_start, fw1InterfacePointer->interface, nipper->tablerow_mid);
					outputFriendly(fw1InterfacePointer->name, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
					if (fw1InterfacePointer->dynamicIP == true)
						fprintf(nipper->reportFile, "Enabled%sN/A%sN/A%s", nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
					else
						fprintf(nipper->reportFile, "Disabled%s%s%s%s%s", nipper->tablerow_mid, fw1InterfacePointer->address, nipper->tablerow_mid, fw1InterfacePointer->netMask, nipper->tablerow_end);
					fw1InterfacePointer = fw1InterfacePointer->next;
				}
				output_table(nipper, false, tempString2, &settings_object_gateinter_heading);
			}

			// Gateway Cluster Members...
			memberPointer = objectPointer->members;
			if (memberPointer != 0)
			{
				sprintf(tempString, "%s %s", objectPointer->name, settings_objects_gatewaycluster_mem_table);
				outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
				output_table(nipper, true, tempString2, &settings_object_gatemem_heading);
				while (memberPointer != 0)
				{
					fprintf(nipper->reportFile, "%s%d%s", nipper->tablerow_start, memberPointer->number, nipper->tablerow_mid);
					outputFriendly(memberPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
					if (nipper->outputFormat == output_html)
						fprintf(nipper->reportFile, "<a href=\"#object-%s\">", tempString);
					fprintf(nipper->reportFile, "%s", tempString);
					if (nipper->outputFormat == output_html)
						fprintf(nipper->reportFile, "</a>");
					fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
					memberPointer = memberPointer->next;
				}
				output_table(nipper, false, tempString2, &settings_object_gatemem_heading);
			}
		}
		objectPointer = objectPointer->next;
	}
}


// Object Definitions (Gateway Cluster Members...)
void fw1GatewayClusterMemberConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct objectConfig *objectPointer = 0;
	struct objectListConfig *objectListPointer = 0;
	struct hostInterfaces *fw1InterfacePointer = 0;
	char tempString[nipper->maxSize];
	char tempString2[nipper->maxSize];

	objectListPointer = getObjectListPointer(nipper, "FW1-Objects");
	objectPointer = objectListPointer->object;
	while (objectPointer != 0)
	{
		if (objectPointer->type == object_type_cluster_member)
		{
			// Gateway Configuration Settings...
			if (nipper->outputFormat == output_html)
				fprintf(nipper->reportFile, "<a name=\"object-%s\">", objectPointer->name);
			sprintf(tempString, "%s %s", objectPointer->name, settings_objects_gatewayclustermem_table);
			outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
			output_table(nipper, true, tempString2, &settings_general_heading);
			outputFriendly(objectPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%sGateway Cluster Member Name%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sIP Address%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, objectPointer->address, nipper->tablerow_end);
			output_table(nipper, false, tempString2, &settings_general_heading);
			if (nipper->outputFormat == output_html)
				fprintf(nipper->reportFile, "</a>");

			// Gateway Interfaces...
			fw1InterfacePointer = objectPointer->interfaces;
			if (fw1InterfacePointer != 0)
			{
				sprintf(tempString, "%s %s", objectPointer->name, settings_objects_gatewayclustermem_int_table);
				outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
				output_table(nipper, true, tempString2, &settings_object_gateinter_heading);
				while (fw1InterfacePointer != 0)
				{
					fprintf(nipper->reportFile, "%s%d%s", nipper->tablerow_start, fw1InterfacePointer->interface, nipper->tablerow_mid);
					outputFriendly(fw1InterfacePointer->name, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
					if (fw1InterfacePointer->dynamicIP == true)
						fprintf(nipper->reportFile, "Enabled%sN/A%sN/A%s", nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
					else
						fprintf(nipper->reportFile, "Disabled%s%s%s%s%s", nipper->tablerow_mid, fw1InterfacePointer->address, nipper->tablerow_mid, fw1InterfacePointer->netMask, nipper->tablerow_end);
					fw1InterfacePointer = fw1InterfacePointer->next;
				}
				output_table(nipper, false, tempString2, &settings_object_gateinter_heading);
			}
		}
		objectPointer = objectPointer->next;
	}
}


// Object Definitions (Gateways...)
void fw1GatewayConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct objectConfig *objectPointer = 0;
	struct objectListConfig *objectListPointer = 0;
	struct hostInterfaces *fw1InterfacePointer = 0;
	char tempString[nipper->maxSize];
	char tempString2[nipper->maxSize];

	objectListPointer = getObjectListPointer(nipper, "FW1-Objects");
	objectPointer = objectListPointer->object;
	while (objectPointer != 0)
	{
		if (objectPointer->type == object_type_gateway)
		{
			// Gateway Configuration Settings...
			if (nipper->outputFormat == output_html)
				fprintf(nipper->reportFile, "<a name=\"object-%s\">", objectPointer->name);
			sprintf(tempString, "%s %s", objectPointer->name, settings_objects_gateway_table);
			outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
			output_table(nipper, true, tempString2, &settings_general_heading);
			outputFriendly(objectPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%sGateway Name%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sIP Address%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, objectPointer->address, nipper->tablerow_end);
			if (objectPointer->firewall == true)
				fprintf(nipper->reportFile, "%sFirewall%sYes%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "%sFirewall%sNo%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			fprintf(nipper->reportFile, "%sCheckPoint Version%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, objectPointer->cpVersion, nipper->tablerow_end);
			if (objectPointer->internal == true)
				fprintf(nipper->reportFile, "%sManaged%sYes%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "%sManaged%sNo%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			output_table(nipper, false, tempString2, &settings_general_heading);
			if (nipper->outputFormat == output_html)
				fprintf(nipper->reportFile, "</a>");

			// Gateway Interfaces...
			fw1InterfacePointer = objectPointer->interfaces;
			if (fw1InterfacePointer != 0)
			{
				sprintf(tempString, "%s %s", objectPointer->name, settings_objects_gateway_int_table);
				outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
				output_table(nipper, true, tempString2, &settings_object_gateinter_heading);
				while (fw1InterfacePointer != 0)
				{
					fprintf(nipper->reportFile, "%s%d%s", nipper->tablerow_start, fw1InterfacePointer->interface, nipper->tablerow_mid);
					outputFriendly(fw1InterfacePointer->name, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
					if (fw1InterfacePointer->dynamicIP == true)
						fprintf(nipper->reportFile, "Enabled%sN/A%sN/A%s", nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
					else
						fprintf(nipper->reportFile, "Disabled%s%s%s%s%s", nipper->tablerow_mid, fw1InterfacePointer->address, nipper->tablerow_mid, fw1InterfacePointer->netMask, nipper->tablerow_end);
					fw1InterfacePointer = fw1InterfacePointer->next;
				}
				output_table(nipper, false, tempString2, &settings_object_gateinter_heading);
			}
		}
		objectPointer = objectPointer->next;
	}
}


// Object Definitions (Hosts...)
void fw1HostsConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct objectConfig *objectPointer = 0;
	struct objectListConfig *objectListPointer = 0;
	char tempString[nipper->maxSize];

	output_table(nipper, true, settings_objects_hosts_table, &settings_object_host_heading);
	objectListPointer = getObjectListPointer(nipper, "FW1-Objects");
	objectPointer = objectListPointer->object;
	while (objectPointer != 0)
	{
		if (objectPointer->type == object_type_host)
		{
			outputFriendly(objectPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
			if (nipper->outputFormat == output_html)
				fprintf(nipper->reportFile, "%s<a name=\"object-%s\">%s</a>%s", nipper->tablerow_start, tempString, tempString, nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
			fprintf(nipper->reportFile, "%s%s", objectPointer->address, nipper->tablerow_mid);
			if (objectPointer->internal == true)
				fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		}
		objectPointer = objectPointer->next;
	}
	output_table(nipper, false, settings_objects_hosts_table, &settings_object_host_heading);
}


// Object Definitions (Networks...)
void fw1NetworksConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct objectConfig *objectPointer = 0;
	struct objectListConfig *objectListPointer = 0;
	char tempString[nipper->maxSize];

	output_table(nipper, true, settings_objects_network_table, &settings_object_network_heading);
	objectListPointer = getObjectListPointer(nipper, "FW1-Objects");
	objectPointer = objectListPointer->object;
	while (objectPointer != 0)
	{
		if (objectPointer->type == object_type_network)
		{
			outputFriendly(objectPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
			if (nipper->outputFormat == output_html)
				fprintf(nipper->reportFile, "%s<a name=\"object-%s\">%s</a>%s", nipper->tablerow_start, tempString, tempString, nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
			fprintf(nipper->reportFile, "%s%s", objectPointer->address, nipper->tablerow_mid);
			fprintf(nipper->reportFile, "%s%s", objectPointer->netMask, nipper->tablerow_mid);
			if (objectPointer->internal == true)
				fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		}
		objectPointer = objectPointer->next;
	}
	output_table(nipper, false, settings_objects_network_table, &settings_object_network_heading);
}


// Object Definitions (Dynamic Network...)
void fw1DynamicNetworkConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct objectConfig *objectPointer = 0;
	struct objectListConfig *objectListPointer = 0;
	char tempString[nipper->maxSize];

	output_table(nipper, true, settings_objects_dynamicnet_table, &settings_object_dynamicnet_heading);
	objectListPointer = getObjectListPointer(nipper, "FW1-Objects");
	objectPointer = objectListPointer->object;
	while (objectPointer != 0)
	{
		if (objectPointer->type == object_type_dynamicnet)
		{
			outputFriendly(objectPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
			if (nipper->outputFormat == output_html)
				fprintf(nipper->reportFile, "%s<a name=\"object-%s\">%s</a>%s", nipper->tablerow_start, tempString, tempString, nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_end);
		}
		objectPointer = objectPointer->next;
	}
	output_table(nipper, false, settings_objects_dynamicnet_table, &settings_object_dynamicnet_heading);
}


// Machine Range Definitions
void fw1MachRangeConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct objectConfig *objectPointer = 0;
	struct objectListConfig *objectListPointer = 0;
	char tempString[nipper->maxSize];

	output_table(nipper, true, settings_objects_machrange_table, &settings_object_machrange_heading);
	objectListPointer = getObjectListPointer(nipper, "FW1-Objects");
	objectPointer = objectListPointer->object;
	while (objectPointer != 0)
	{
		if (objectPointer->type == object_type_machinesrange)
		{
			outputFriendly(objectPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
			if (nipper->outputFormat == output_html)
				fprintf(nipper->reportFile, "%s<a name=\"object-%s\">%s</a>%s", nipper->tablerow_start, tempString, tempString, nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
			fprintf(nipper->reportFile, "%s%s", objectPointer->address, nipper->tablerow_mid);
			fprintf(nipper->reportFile, "%s%s", objectPointer->netMask, nipper->tablerow_end);
		}
		objectPointer = objectPointer->next;
	}
	output_table(nipper, false, settings_objects_machrange_table, &settings_object_machrange_heading);
}


// Object Definitions (Groups...)
void fw1GroupObjectsConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct objectConfig *objectPointer = 0;
	struct objectConfig *objectPointer2 = 0;
	struct objectMember *memberPointer = 0;
	struct objectListConfig *objectListPointer = 0;
	char tempString[nipper->maxSize];
	char tempString2[nipper->maxSize];

	objectListPointer = getObjectListPointer(nipper, "FW1-Objects");
	objectPointer = objectListPointer->object;
	while (objectPointer != 0)
	{
		if (objectPointer->type == object_type_group)
		{
			sprintf(tempString, "%s %s", objectPointer->name, settings_objects_group_table);
			outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
			if (nipper->outputFormat == output_html)
				fprintf(nipper->reportFile, "<a name=\"object-%s\">", objectPointer->name);
			output_table(nipper, true, tempString2, &settings_object_group_heading);
			memberPointer = objectPointer->members;
			while (memberPointer != 0)
			{
				objectPointer2 = nipper->objectList->object;
				while ((objectPointer2->next != 0) && (strcasecmp(objectPointer2->name, memberPointer->name) != 0))
					objectPointer2 = objectPointer2->next;
				outputFriendly(memberPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
				if ((nipper->outputFormat == output_html) && (objectPointer2->type == object_type_group))
					fprintf(nipper->reportFile, "%s<a href=\"#object-%s\">%s</a>%s", nipper->tablerow_start, tempString, tempString, nipper->tablerow_mid);
				else
					fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
				if (strcasecmp(objectPointer2->name, memberPointer->name) == 0)
				{
					switch (objectPointer2->type)
					{
						case object_type_network:
							fprintf(nipper->reportFile, "Network%s", nipper->tablerow_mid);
							fprintf(nipper->reportFile, "%s%s", objectPointer2->address, nipper->tablerow_mid);
							fprintf(nipper->reportFile, "%s %s", objectPointer2->netMask, nipper->tablerow_mid);
							if (objectPointer2->internal == true)
								fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
							else
								fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
							break;
						case object_type_group:
							fprintf(nipper->reportFile, "Group%s", nipper->tablerow_mid);
							fprintf(nipper->reportFile, "-%s-%s-%s", nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
							break;
						case object_type_host:
							fprintf(nipper->reportFile, "Host%s", nipper->tablerow_mid);
							fprintf(nipper->reportFile, "%s%s", objectPointer2->address, nipper->tablerow_mid);
							fprintf(nipper->reportFile, "-%s", nipper->tablerow_mid);
							if (objectPointer2->internal == true)
								fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
							else
								fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
							break;
						case object_type_machinesrange:
							fprintf(nipper->reportFile, "Range%s", nipper->tablerow_mid);
							fprintf(nipper->reportFile, "%s%s", objectPointer2->address, nipper->tablerow_mid);
							fprintf(nipper->reportFile, "%s %s", objectPointer2->netMask, nipper->tablerow_mid);
							if (objectPointer2->internal == true)
								fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
							else
								fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
							break;
						case object_type_dynamicnet:
							fprintf(nipper->reportFile, "Dynamic Net%s", nipper->tablerow_mid);
							fprintf(nipper->reportFile, "-%s-%s-%s", nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
							break;
						case object_type_gateway:
							fprintf(nipper->reportFile, "Gateway%s", nipper->tablerow_mid);
							fprintf(nipper->reportFile, "%s%s", objectPointer2->address, nipper->tablerow_mid);
							fprintf(nipper->reportFile, "-%s", nipper->tablerow_mid);
							if (objectPointer2->internal == true)
								fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
							else
								fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
							break;
						case object_type_cluster_member:
							fprintf(nipper->reportFile, "Cluster Member%s", nipper->tablerow_mid);
							fprintf(nipper->reportFile, "%s%s", objectPointer2->address, nipper->tablerow_mid);
							fprintf(nipper->reportFile, "-%s", nipper->tablerow_mid);
							if (objectPointer2->internal == true)
								fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
							else
								fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
							break;
						case object_type_gateway_cluster:
							fprintf(nipper->reportFile, "Gateway Cluster%s", nipper->tablerow_mid);
							fprintf(nipper->reportFile, "%s%s", objectPointer2->address, nipper->tablerow_mid);
							fprintf(nipper->reportFile, "%s %s", objectPointer2->netMask, nipper->tablerow_mid);
							if (objectPointer2->internal == true)
								fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
							else
								fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
							break;
						default:
							fprintf(nipper->reportFile, "Unknown%s", nipper->tablerow_mid);
							fprintf(nipper->reportFile, "-%s-%s-%s", nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
							break;
					}
				}
				else
					fprintf(nipper->reportFile, "Unknown%s-%s-%s-%s", nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_mid, nipper->tablerow_end);
				memberPointer = memberPointer->next;
			}
			output_table(nipper, false, tempString2, &settings_object_group_heading);
			if (nipper->outputFormat == output_html)
				fprintf(nipper->reportFile, "</a>");
		}
		objectPointer = objectPointer->next;
	}
}

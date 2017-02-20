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

// Includes...
#include <cstring>

#include "../../globaldefs.h"
#include "../device.h"
#include "filter.h"


int Filter::generateConfigObjectTypeReport(Device *device, objectType type, Device::configReportStruct *configReportPointer)
{
	// Variables...
	Device::paragraphStruct *paragraphPointer = 0;
	string tempString;
	filterObjectConfig *filterObjectPointer = 0;
	netObjectListConfig *objectListPointer = 0;
	Device::bodyStruct *cellPointer = 0;
	int errorCode = 0;
	bool first = true;

	objectListPointer = netObjectList;
	while (objectListPointer != 0)
	{

		if (objectListPointer->type == type)
		{
			paragraphPointer = device->addParagraph(configReportPointer);

			if (first == true)
			{
				paragraphPointer->paragraphTitle.assign(objectListPointer->title);
				if (strlen(objectListPointer->description) > 0)
					paragraphPointer->paragraph.assign(objectListPointer->description);
				paragraphPointer = device->addParagraph(configReportPointer);
				first = false;
			}

			if ((type != gatewayObject) && (type != gatewayClusterObject) && (type != clusterMemberObject))
			{

				// Comment text (if exists)
				if (!objectListPointer->comment.empty())
				{
					tempString.assign(i18n("Table *TABLEREF*: "));
					tempString.append(objectListPointer->comment);
					paragraphPointer->paragraph.assign(tempString.c_str());
				}

				// Create table
				tempString.assign("OBJECT-");
				tempString.append(objectListPointer->name);
				errorCode = device->addTable(paragraphPointer, tempString.c_str());
				if (errorCode != 0)
					return errorCode;

				// Titles
				if ((objectListPointer->tcp == true) && (objectListPointer->tcp == true))
					tempString.assign(i18n("*ABBREV*TCP*-ABBREV* and *ABBREV*UDP*-ABBREV* object group "));
				else if (objectListPointer->tcp == true)
					tempString.assign(i18n("*ABBREV*TCP*-ABBREV* object group "));
				else if (objectListPointer->tcp == true)
					tempString.assign(i18n("*ABBREV*UDP*-ABBREV* object group "));
				else if (objectListPointer->type == addressBookObject)
					tempString.assign("");
				else if (!objectListPointer->zone.empty())
				{
					tempString.assign(i18n("Zone "));
					tempString.append(objectListPointer->zone.c_str());
					tempString.append(i18n(" address object group "));
				}
				else
					tempString.assign(i18n("Object group "));
				if (objectListPointer->type == enhancedServiceObject)
					tempString.assign(objectListPointer->name.c_str());
				else
					tempString.append(objectListPointer->name);
				if (objectListPointer->type == addressBookObject)
					tempString.append(i18n(" address book"));
				paragraphPointer->table->title.assign(tempString);

				switch (objectListPointer->type)
				{
					case addressBookObject:
						device->addTableHeading(paragraphPointer->table, i18n("Type"), false);
						device->addTableHeading(paragraphPointer->table, i18n("Name"), false);
						device->addTableHeading(paragraphPointer->table, i18n("Address"), false);
						break;

					case serviceListObject:
						device->addTableHeading(paragraphPointer->table, i18n("Name"), false);
						device->addTableHeading(paragraphPointer->table, i18n("Protocol"), false);
						device->addTableHeading(paragraphPointer->table, i18n("Port"), false);
						break;

					case enhancedServiceObject:
						device->addTableHeading(paragraphPointer->table, i18n("Name"), false);
						device->addTableHeading(paragraphPointer->table, i18n("Protocol"), false);
						device->addTableHeading(paragraphPointer->table, i18n("Source Port"), false);
						device->addTableHeading(paragraphPointer->table, i18n("Destination Port"), false);
						break;

					default:
						device->addTableHeading(paragraphPointer->table, i18n("Type"), false);
						device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
						break;
				}
				if (objectListPointer->objectCommentSupported == true)
					device->addTableHeading(paragraphPointer->table, i18n("Comment"), false);

				// Data...
				filterObjectPointer = objectListPointer->object;
				while (filterObjectPointer != 0)
				{
					if ((objectListPointer->type != enhancedServiceObject) && (objectListPointer->type != serviceListObject))
					{
						switch (filterObjectPointer->type)
						{
							case networkObject:
								device->addTableData(paragraphPointer->table, i18n("Network"));
								break;
							case protocolObject:
								device->addTableData(paragraphPointer->table, i18n("Protocol"));
								break;
							case icmpObject:
								device->addTableData(paragraphPointer->table, i18n("*ABBREV*ICMP*-ABBREV*"));
								break;
							case serviceObject:
								device->addTableData(paragraphPointer->table, i18n("Service"));
								break;
							case enhancedServiceObject:
								device->addTableData(paragraphPointer->table, i18n("Service"));
								break;
							case addressObject:
								device->addTableData(paragraphPointer->table, i18n("Address Book Entry"));
								break;
							case groupObject:
								device->addTableData(paragraphPointer->table, i18n("Group"));
								break;
							case portObject:
								device->addTableData(paragraphPointer->table, i18n("Port"));
								break;
							case hostObject:
								device->addTableData(paragraphPointer->table, i18n("Host"));
								break;
							case machinesRangeObject:
								device->addTableData(paragraphPointer->table, i18n("Host Range"));
								break;
							case dynamicnetObject:
								device->addTableData(paragraphPointer->table, i18n("Dynamic Net"));
								break;
							/*case serviceRangeObject:
								device->addTableData(paragraphPointer->table, i18n("Service Range"));
								break;
							case timeObject:
								device->addTableData(paragraphPointer->table, i18n("Time"));
								break;
							case objectObject
								device->addTableData(paragraphPointer->table, i18n("Object"));
								break;*/
							default:
								device->addTableData(paragraphPointer->table, "");
								break;
						}

						if (!filterObjectPointer->label.empty())
						{
							cellPointer = device->addTableData(paragraphPointer->table, filterObjectPointer->label.c_str());
							if (objectListPointer->type == addressBookObject)
							{
								cellPointer->referencer = false;
								tempString.assign("OBJECT-");
								tempString.append(filterObjectPointer->label.c_str());
								cellPointer->reference.assign(tempString);
							}
						}

						switch (filterObjectPointer->serviceOper)
						{
							case serviceOperAny:
								cellPointer = device->addTableData(paragraphPointer->table, i18n("Any"));
								break;
							case serviceOperEqual:
								tempString.assign(filterObjectPointer->name.c_str());
								if (filterObjectPointer->type == networkObject)
								{
									tempString.append(" / ");
									tempString.append(filterObjectPointer->netmask);
								}
								cellPointer = device->addTableData(paragraphPointer->table, tempString.c_str());
								if ((filterObjectPointer->type == enhancedServiceObject) || (filterObjectPointer->type == groupObject) || (filterObjectPointer->type == addressObject))
								{
									cellPointer->referencer = true;
									tempString.assign("OBJECT-");
									tempString.append(filterObjectPointer->name.c_str());
									cellPointer->reference.assign(tempString);
								}
								break;
							case serviceOperNotEqual:
								tempString.assign(i18n("Not "));
								tempString.append(filterObjectPointer->name.c_str());
								cellPointer = device->addTableData(paragraphPointer->table, tempString.c_str());
								break;
							case serviceOperLessThan:
								tempString.assign(i18n("Less than "));
								tempString.append(filterObjectPointer->name.c_str());
								cellPointer = device->addTableData(paragraphPointer->table, tempString.c_str());
								break;
							case serviceOperGreaterThan:
								tempString.assign(i18n("Greater than "));
								tempString.append(filterObjectPointer->name.c_str());
								cellPointer = device->addTableData(paragraphPointer->table, tempString.c_str());
								break;
							case serviceOperRange:
								tempString.assign(filterObjectPointer->name.c_str());
								tempString.append(i18n(" - "));
								tempString.append(filterObjectPointer->netmask.c_str());
								cellPointer = device->addTableData(paragraphPointer->table, tempString.c_str());
								break;
							default:
								cellPointer = device->addTableData(paragraphPointer->table, filterObjectPointer->name.c_str());
								break;
						}
						if ((filterObjectPointer->label.empty()) && (objectListPointer->type == addressBookObject))
							cellPointer = device->addTableData(paragraphPointer->table, filterObjectPointer->label.c_str());
					}

					// Service List
					else if (objectListPointer->type == serviceListObject)
					{
						cellPointer = device->addTableData(paragraphPointer->table, filterObjectPointer->label.c_str());
						cellPointer->referencer = false;
						tempString.assign("OBJECT-");
						tempString.append(filterObjectPointer->label.c_str());
						cellPointer->reference.assign(tempString);
						if (filterObjectPointer->protocol == 0)
							cellPointer = device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
						else
							outputFilterProtocols(device, paragraphPointer->table, filterObjectPointer->protocol);
						switch (filterObjectPointer->serviceOper)
						{
							case serviceOperAny:
								cellPointer = device->addTableData(paragraphPointer->table, i18n("Any"));
								break;
							case serviceOperEqual:
								cellPointer = device->addTableData(paragraphPointer->table, filterObjectPointer->name.c_str());
								break;
							default:
								tempString.assign(filterObjectPointer->name.c_str());
								tempString.append(i18n(" - "));
								tempString.append(filterObjectPointer->netmask.c_str());
								cellPointer = device->addTableData(paragraphPointer->table, tempString.c_str());
								break;
						}
					}

					// Enhanced Service Object List
					else
					{
						cellPointer = device->addTableData(paragraphPointer->table, filterObjectPointer->name.c_str());
						cellPointer->referencer = false;
						tempString.assign("OBJECT-");
						tempString.append(filterObjectPointer->name.c_str());
						cellPointer->reference.assign(tempString);
						switch (filterObjectPointer->type)
						{
							case icmpObject:
							case rpcObject:
								if (filterObjectPointer->protocol == 0)
									cellPointer = device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
								else
									outputFilterProtocols(device, paragraphPointer->table, filterObjectPointer->protocol);
								cellPointer = device->addTableData(paragraphPointer->table, i18n("N/A"));
								cellPointer = device->addTableData(paragraphPointer->table, i18n("N/A"));
								break;

							case otherObject:
								if (filterObjectPointer->protocol == 0)
									cellPointer = device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
								else
									outputFilterProtocols(device, paragraphPointer->table, filterObjectPointer->protocol);
								cellPointer = device->addTableData(paragraphPointer->table, i18n("N/A"));
								cellPointer = device->addTableData(paragraphPointer->table, i18n("N/A"));
								break;

							default:
								if (filterObjectPointer->protocol == 0)
									cellPointer = device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
								else
									outputFilterProtocols(device, paragraphPointer->table, filterObjectPointer->protocol);
								if (filterObjectPointer->sourcePort == 0)
									cellPointer = device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
								else
									outputFilterHostService(device, paragraphPointer->table, filterObjectPointer->sourcePort);
								if (filterObjectPointer->destinationPort == 0)
									cellPointer = device->addTableData(paragraphPointer->table, device->config->emptyTableCell);
								else
									outputFilterHostService(device, paragraphPointer->table, filterObjectPointer->destinationPort);
								break;
						}
					}
					if (objectListPointer->objectCommentSupported == true)
						device->addTableData(paragraphPointer->table, filterObjectPointer->comment.c_str());
					filterObjectPointer = filterObjectPointer->next;
				}
			}

			// CheckPoint Clusters/Gateways/Members...
			else if (objectListPointer->object != 0)
			{
				// Create table
				tempString.assign("OBJECT-");
				tempString.append(objectListPointer->name);
				tempString.append("-SETTINGS");
				errorCode = device->addTable(paragraphPointer, tempString.c_str());
				if (errorCode != 0)
					return errorCode;

				// Title
				tempString.assign(objectListPointer->name);
				if (type == clusterMemberObject)
					tempString.append(i18n(" cluster member configuration"));
				else if (type == gatewayClusterObject)
					tempString.append(i18n(" gateway cluster configuration"));
				else
					tempString.append(i18n(" gateway configuration"));
				paragraphPointer->table->title.assign(tempString);

				// Table Columns...
				device->addTableHeading(paragraphPointer->table, i18n("Setting"), false);
				device->addTableHeading(paragraphPointer->table, i18n("Description"), false);

				// Data...
				cellPointer = device->addTableData(paragraphPointer->table, i18n("Name"));
				cellPointer = device->addTableData(paragraphPointer->table, objectListPointer->name.c_str());
				cellPointer = device->addTableData(paragraphPointer->table, i18n("*ABBREV*IP*-ABBREV* Address"));
				cellPointer = device->addTableData(paragraphPointer->table, objectListPointer->object->name.c_str());
				if (!objectListPointer->comment.empty())
				{
					cellPointer = device->addTableData(paragraphPointer->table, i18n("Comment Text"));
					cellPointer = device->addTableData(paragraphPointer->table, objectListPointer->comment.c_str());
				}

				// Interfaces...
				filterObjectPointer = objectListPointer->object->interfaces;
				if (filterObjectPointer != 0)
				{
					paragraphPointer = device->addParagraph(configReportPointer);

					// Create table
					tempString.assign("OBJECT-");
					tempString.append(objectListPointer->name);
					tempString.append("-INTERFACES");
					errorCode = device->addTable(paragraphPointer, tempString.c_str());
					if (errorCode != 0)
						return errorCode;

					// Title
					tempString.assign(objectListPointer->name);
					tempString.append(i18n(" interfaces"));
					paragraphPointer->table->title.assign(tempString);

					// Table Columns...
					device->addTableHeading(paragraphPointer->table, i18n("Interface"), false);
					device->addTableHeading(paragraphPointer->table, i18n("Name"), false);
					device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*IP*-ABBREV* Address"), false);
					device->addTableHeading(paragraphPointer->table, i18n("Netmask"), false);

					while (filterObjectPointer != 0)
					{
						tempString.assign(device->intToString(filterObjectPointer->interfaceIndex));
						cellPointer = device->addTableData(paragraphPointer->table, tempString.c_str());
						cellPointer = device->addTableData(paragraphPointer->table, filterObjectPointer->label.c_str());
						if (filterObjectPointer->dhcp == true)
						{
							cellPointer = device->addTableData(paragraphPointer->table, i18n("*ABBREV*DHCP*-ABBREV*"));
							cellPointer = device->addTableData(paragraphPointer->table, i18n("N/A"));
						}
						else
						{
							cellPointer = device->addTableData(paragraphPointer->table, filterObjectPointer->name.c_str());
							cellPointer = device->addTableData(paragraphPointer->table, filterObjectPointer->netmask.c_str());
						}
						filterObjectPointer = filterObjectPointer->next;
					}
				}

				// Members...
				filterObjectPointer = objectListPointer->object->members;
				if ((filterObjectPointer != 0) && (type == gatewayClusterObject))
				{
					paragraphPointer = device->addParagraph(configReportPointer);

					// Create table
					tempString.assign("OBJECT-");
					tempString.append(objectListPointer->name);
					tempString.append("-MEMBERS");
					errorCode = device->addTable(paragraphPointer, tempString.c_str());
					if (errorCode != 0)
						return errorCode;

					// Title
					tempString.assign(objectListPointer->name);
					tempString.append(i18n(" cluster members"));
					paragraphPointer->table->title.assign(tempString);

					// Table Columns...
					device->addTableHeading(paragraphPointer->table, i18n("Member"), false);
					device->addTableHeading(paragraphPointer->table, i18n("Name"), false);

					while (filterObjectPointer != 0)
					{
						tempString.assign(device->intToString(filterObjectPointer->interfaceIndex));
						cellPointer = device->addTableData(paragraphPointer->table, tempString.c_str());
						cellPointer = device->addTableData(paragraphPointer->table, filterObjectPointer->name.c_str());
						filterObjectPointer = filterObjectPointer->next;
					}
				}
			}
		}
		objectListPointer = objectListPointer->next;
	}

	return errorCode;
}


int Filter::generateConfigObjectReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	netObjectListConfig *objectListPointer = 0;
	bool found = false;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s Filter Object Settings\n", device->config->COL_BLUE, device->config->COL_RESET);

	// Get Config Report Section...
	configReportPointer = device->getConfigSection("CONFIG-FILTER");

	// Gateway Cluster Objects...
	objectListPointer = netObjectList;
	found = false;
	while ((objectListPointer != 0) && (found == false))
	{
		if (objectListPointer->type == gatewayClusterObject)
		{
			errorCode = generateConfigObjectTypeReport(device, gatewayClusterObject, configReportPointer);
			found = true;
		}
		else
			objectListPointer = objectListPointer->next;
	}

	// Cluster Member Objects...
	objectListPointer = netObjectList;
	found = false;
	while ((objectListPointer != 0) && (found == false))
	{
		if (objectListPointer->type == clusterMemberObject)
		{
			errorCode = generateConfigObjectTypeReport(device, clusterMemberObject, configReportPointer);
			found = true;
		}
		else
			objectListPointer = objectListPointer->next;
	}

	// Gateway Objects...
	objectListPointer = netObjectList;
	found = false;
	while ((objectListPointer != 0) && (found == false))
	{
		if (objectListPointer->type == gatewayObject)
		{
			errorCode = generateConfigObjectTypeReport(device, gatewayObject, configReportPointer);
			found = true;
		}
		else
			objectListPointer = objectListPointer->next;
	}

	// Host Objects...
	objectListPointer = netObjectList;
	found = false;
	while ((objectListPointer != 0) && (found == false))
	{
		if (objectListPointer->type == hostObject)
		{
			errorCode = generateConfigObjectTypeReport(device, hostObject, configReportPointer);
			found = true;
		}
		else
			objectListPointer = objectListPointer->next;
	}

	// Network Objects...
	objectListPointer = netObjectList;
	found = false;
	while ((objectListPointer != 0) && (found == false))
	{
		if (objectListPointer->type == networkObject)
		{
			errorCode = generateConfigObjectTypeReport(device, networkObject, configReportPointer);
			found = true;
		}
		else
			objectListPointer = objectListPointer->next;
	}

	// Address Book Objects...
	objectListPointer = netObjectList;
	found = false;
	while ((objectListPointer != 0) && (found == false))
	{
		if (objectListPointer->type == addressBookObject)
		{
			errorCode = generateConfigObjectTypeReport(device, addressBookObject, configReportPointer);
			found = true;
		}
		else
			objectListPointer = objectListPointer->next;
	}

	// Protocol Objects...
	objectListPointer = netObjectList;
	found = false;
	while ((objectListPointer != 0) && (found == false))
	{
		if (objectListPointer->type == protocolObject)
		{
			errorCode = generateConfigObjectTypeReport(device, protocolObject, configReportPointer);
			found = true;
		}
		else
			objectListPointer = objectListPointer->next;
	}

	// ICMP Objects...
	objectListPointer = netObjectList;
	found = false;
	while ((objectListPointer != 0) && (found == false))
	{
		if (objectListPointer->type == icmpObject)
		{
			errorCode = generateConfigObjectTypeReport(device, icmpObject, configReportPointer);
			found = true;
		}
		else
			objectListPointer = objectListPointer->next;
	}

	// Service Objects...
	objectListPointer = netObjectList;
	found = false;
	while ((objectListPointer != 0) && (found == false))
	{
		if (objectListPointer->type == serviceObject)
		{
			errorCode = generateConfigObjectTypeReport(device, serviceObject, configReportPointer);
			found = true;
		}
		else
			objectListPointer = objectListPointer->next;
	}

	// Port Objects...
	objectListPointer = netObjectList;
	found = false;
	while ((objectListPointer != 0) && (found == false))
	{
		if (objectListPointer->type == portObject)
		{
			errorCode = generateConfigObjectTypeReport(device, portObject, configReportPointer);
			found = true;
		}
		else
			objectListPointer = objectListPointer->next;
	}

	// Service Range Objects...
	objectListPointer = netObjectList;
	found = false;
	while ((objectListPointer != 0) && (found == false))
	{
		if (objectListPointer->type == serviceRangeObject)
		{
			errorCode = generateConfigObjectTypeReport(device, serviceRangeObject, configReportPointer);
			found = true;
		}
		else
			objectListPointer = objectListPointer->next;
	}

	// Enhanced Service Objects...
	objectListPointer = netObjectList;
	found = false;
	while ((objectListPointer != 0) && (found == false))
	{
		if (objectListPointer->type == enhancedServiceObject)
		{
			errorCode = generateConfigObjectTypeReport(device, enhancedServiceObject, configReportPointer);
			found = true;
		}
		else
			objectListPointer = objectListPointer->next;
	}

	// Service List Objects...
	objectListPointer = netObjectList;
	found = false;
	while ((objectListPointer != 0) && (found == false))
	{
		if (objectListPointer->type == serviceListObject)
		{
			errorCode = generateConfigObjectTypeReport(device, serviceListObject, configReportPointer);
			found = true;
		}
		else
			objectListPointer = objectListPointer->next;
	}

	// Group Objects...
	objectListPointer = netObjectList;
	found = false;
	while ((objectListPointer != 0) && (found == false))
	{
		if (objectListPointer->type == groupObject)
		{
			errorCode = generateConfigObjectTypeReport(device, groupObject, configReportPointer);
			found = true;
		}
		else
			objectListPointer = objectListPointer->next;
	}

	// Time Objects...
	objectListPointer = netObjectList;
	found = false;
	while ((objectListPointer != 0) && (found == false))
	{
		if (objectListPointer->type == timeObject)
		{
			errorCode = generateConfigObjectTypeReport(device, timeObject, configReportPointer);
			found = true;
		}
		else
			objectListPointer = objectListPointer->next;
	}

	return errorCode;
}


int Filter::generateSecurityObjectReport(Device *device)
{
	return 0;
}


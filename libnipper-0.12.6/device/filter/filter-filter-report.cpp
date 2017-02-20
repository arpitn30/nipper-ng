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


int Filter::generateConfigFilterReport(Device *device, const char *listType)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	filterListConfig *filterListPointer = 0;
	filterConfig *filterPointer = 0;
	string tempString;
	int errorCode = 0;
	bool first = true;

	// Get Config Report Section...
	configReportPointer = device->getConfigSection("CONFIG-FILTER");

	filterListPointer = filterList;
	while (filterListPointer != 0)
	{

		if (filterListPointer->type == listType)
		{
			filterListPointer->used = true;

			paragraphPointer = device->addParagraph(configReportPointer);
			if (first == true)
			{
				first = false;
				paragraphPointer->paragraphTitle.assign(filterListPointer->type);
				if (strlen(filterListPointer->typeDescription) > 0)
					paragraphPointer->paragraph.assign(filterListPointer->typeDescription);
			}

			// New filter list table...
			tempString.assign("CONFIG-FILTER-");
			tempString.append(filterListPointer->name);
			tempString.append("-TABLE");
			errorCode = device->addTable(paragraphPointer, tempString.c_str());
			if (errorCode != 0)
				return errorCode;

			// Filter list table title...
			paragraphPointer->table->title.assign(filterListPointer->type);
			paragraphPointer->table->title.append(" ");
			if (filterListPointer->listName.empty())
			{
				if (filterListPointer->to.empty())
					paragraphPointer->table->title.append(filterListPointer->name);
				else
				{
					paragraphPointer->table->title.append(i18n("from "));
					paragraphPointer->table->title.append(filterListPointer->name);
					paragraphPointer->table->title.append(i18n(" to "));
					paragraphPointer->table->title.append(filterListPointer->to);
				}
			}
			else
			{
				paragraphPointer->table->title.append(filterListPointer->listName);
				paragraphPointer->table->title.append(" (");
				paragraphPointer->table->title.append(filterListPointer->name);
				paragraphPointer->table->title.append(")");
			}

			// Add table headings...
			addFilterTableHeadings(device, paragraphPointer, filterListPointer, false);

			// The table data...
			filterPointer = filterListPointer->filter;
			while (filterPointer != 0)
			{
				addFilterTableRow(device, paragraphPointer, filterPointer, filterListPointer);
				filterPointer = filterPointer->next;
			}
		}

		filterListPointer = filterListPointer->next;
	}

	return errorCode;
}


int Filter::generateConfigFilterReport(Device *device)
{
	// Variables...
	filterListConfig *filterListPointer = 0;
	string tempString;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s Filter Rule Settings\n", device->config->COL_BLUE, device->config->COL_RESET);

	filterListPointer = filterList;
	while (filterListPointer != 0)
	{
		if (filterListPointer->used == false)
			errorCode = generateConfigFilterReport(device, filterListPointer->type);
		filterListPointer = filterListPointer->next;
	}

	return errorCode;
}


int Filter::generateSecurityFilterReport(Device *device)
{
	return 0;
}


int Filter::outputFilterProtocols(Device *device, Device::tableStruct *tablePointer, filterObjectConfig *filterObjectPointer)
{
	// Variables...
	Device::bodyStruct *cellPointer = 0;
	string tempString;
	bool newCell = true;

	while (filterObjectPointer != 0)
	{
		if (filterObjectPointer->type == anyObject)
		{
			cellPointer = device->addTableData(tablePointer, i18n("Any"));
		}
		else
		{
			tempString.assign(filterObjectPointer->name.c_str());
			if (!filterObjectPointer->netmask.empty())
			{
				tempString.append(" ");
				tempString.append(filterObjectPointer->netmask.c_str());
			}
			cellPointer = device->addTableData(tablePointer, tempString.c_str());
			device->addProtocol(filterObjectPointer->name.c_str());
		}

		if (newCell == false)
			cellPointer->newCell = false;
		else
			newCell = false;

		filterObjectPointer = filterObjectPointer->next;
	}

	return 0;
}


int Filter::outputFilterHosts(Device *device, Device::tableStruct *tablePointer, filterObjectConfig *filterObjectPointer, const char *zoneName)
{
	// Variables...
	Device::bodyStruct *cellPointer = 0;
	string tempString;
	bool newCell = true;

	while (filterObjectPointer != 0)
	{
		tempString.assign("");

		if (filterObjectPointer->type == anyObject)
		{
			if (zoneName == 0)
				cellPointer = device->addTableData(tablePointer, i18n("Any"));
			else
			{
				tempString.assign(i18n("Any"));
				tempString.append(" (");
				tempString.append(zoneName);
				tempString.append(")");
				cellPointer = device->addTableData(tablePointer, tempString.c_str());
			}
		}
		else if (filterObjectPointer->type == networkObject)
		{
			if (filterObjectPointer->serviceOper == serviceOperNotEqual)
				tempString.assign(i18n("NOT "));
			tempString.append(filterObjectPointer->name.c_str());
			tempString.append("/");
			tempString.append(filterObjectPointer->netmask.c_str());
			if (zoneName != 0)
			{
				tempString.append(" (");
				tempString.append(zoneName);
				tempString.append(")");
			}
			cellPointer = device->addTableData(tablePointer, tempString.c_str());
		}
		else if (filterObjectPointer->type == groupObject)
		{
			if (filterObjectPointer->serviceOper == serviceOperNotEqual)
				tempString.assign(i18n("NOT "));
			tempString.append(filterObjectPointer->name);
			if (zoneName != 0)
			{
				tempString.append(" (");
				tempString.append(zoneName);
				tempString.append(")");
			}
			cellPointer = device->addTableData(tablePointer, tempString.c_str());
			cellPointer->referencer = true;
			tempString.assign("OBJECT-");
			tempString.append(filterObjectPointer->name.c_str());
			cellPointer->reference.assign(tempString);
		}
		else
		{
			if (filterObjectPointer->serviceOper == serviceOperNotEqual)
				tempString.assign(i18n("NOT "));
			tempString.append(filterObjectPointer->name);
			if (zoneName != 0)
			{
				tempString.append(" (");
				tempString.append(zoneName);
				tempString.append(")");
			}
			cellPointer = device->addTableData(tablePointer, tempString.c_str());
		}

		if (newCell == false)
			cellPointer->newCell = false;
		else
			newCell = false;

		filterObjectPointer = filterObjectPointer->next;
	}

	return 0;
}


int Filter::outputFilterHostService(Device *device, Device::tableStruct *tablePointer, filterObjectConfig *filterObjectPointer)
{
	// Variables...
	Device::bodyStruct *cellPointer = 0;
	string tempString;
	bool newCell = true;

	while (filterObjectPointer != 0)
	{
		if (filterObjectPointer->type == groupObject)
		{
			tempString.assign("");
			if (filterObjectPointer->serviceOper == serviceOperNotEqual)
				tempString.assign(i18n("Not "));
			tempString.append(filterObjectPointer->name);
			cellPointer = device->addTableData(tablePointer, tempString.c_str());
			cellPointer->referencer = true;
			tempString.assign("OBJECT-");
			tempString.append(filterObjectPointer->name.c_str());
			cellPointer->reference.assign(tempString);
		}
		else
		{
			switch (filterObjectPointer->serviceOper)
			{
				case serviceOperAny:
					cellPointer = device->addTableData(tablePointer, i18n("Any"));
					break;
				case serviceOperEqual:
					cellPointer = device->addTableData(tablePointer, filterObjectPointer->name.c_str());
					break;
				case serviceOperNotEqual:
					tempString.assign(i18n("Not "));
					tempString.append(filterObjectPointer->name.c_str());
					cellPointer = device->addTableData(tablePointer, tempString.c_str());
					break;
				case serviceOperLessThan:
					tempString.assign(i18n("Less than "));
					tempString.append(filterObjectPointer->name.c_str());
					cellPointer = device->addTableData(tablePointer, tempString.c_str());
					break;
				case serviceOperGreaterThan:
					tempString.assign(i18n("Greater than "));
					tempString.append(filterObjectPointer->name.c_str());
					cellPointer = device->addTableData(tablePointer, tempString.c_str());
					break;
				case serviceOperRange:
					tempString.assign(filterObjectPointer->name.c_str());
					tempString.append(i18n(" - "));
					tempString.append(filterObjectPointer->netmask.c_str());
					cellPointer = device->addTableData(tablePointer, tempString.c_str());
					break;
				default:
					tempString.assign(i18n("Any"));
					cellPointer = device->addTableData(tablePointer, tempString.c_str());
					break;
			}
		}

		if (newCell == false)
			cellPointer->newCell = false;
		else
			newCell = false;

		filterObjectPointer = filterObjectPointer->next;
	}

	return 0;
}


int Filter::outputFilterTime(Device *device, Device::tableStruct *tablePointer, filterObjectConfig *filterObjectPointer)
{
	// Variables...
	Device::bodyStruct *cellPointer = 0;
	bool newCell = true;

	while (filterObjectPointer != 0)
	{
		if (filterObjectPointer->type == anyObject)
			cellPointer = device->addTableData(tablePointer, i18n("Any"));
		else
			cellPointer = device->addTableData(tablePointer, filterObjectPointer->name.c_str());
		if (newCell == false)
			cellPointer->newCell = false;
		else
			newCell = false;
		filterObjectPointer = filterObjectPointer->next;
	}

	return 0;
}


int Filter::addFilterTableHeadings(Device *device, Device::paragraphStruct *paragraphPointer, filterListConfig *filterListPointer, bool includeFilterList)
{
	// Variables...
	filterConfig *filterPointer = 0;

	// Check if comments should be enabled?
	enableComments = false;
	if ((filterListPointer->filterCommentsSupported == true) && (device->config->includeFilterRuleComments == true))
	{
		filterPointer = filterListPointer->filter;
		while ((filterPointer != 0) && (enableComments == false))
		{
			if (!filterPointer->comment.empty())
				enableComments = true;
			else
				filterPointer = filterPointer->next;
		}
	}

	if (includeFilterList == true)
		device->addTableHeading(paragraphPointer->table, filterListNameTitle, false);

	device->addTableHeading(paragraphPointer->table, filterIDTitle, false);

	if (filterListPointer->disabledFilterSupport == true)
		device->addTableHeading(paragraphPointer->table, i18n("Active"), false);

	if (filterListPointer->showFilterType == true)
		device->addTableHeading(paragraphPointer->table, i18n("Type"), false);

	device->addTableHeading(paragraphPointer->table, i18n("Access"), false);

	if ((filterListPointer->sourceOnly == false) && (filterListPointer->showProtocol == true))
		device->addTableHeading(paragraphPointer->table, i18n("Proto"), false);

	device->addTableHeading(paragraphPointer->table, i18n("Source"), false);

	if (filterListPointer->sourceServiceSupported == true)
		device->addTableHeading(paragraphPointer->table, i18n("Src Port"), false);

	if (filterListPointer->sourceOnly == false)
	{
		device->addTableHeading(paragraphPointer->table, i18n("Destination"), false);

		if (filterListPointer->sourceServiceSupported == true)
			device->addTableHeading(paragraphPointer->table, i18n("Dest Port"), false);
		else
			device->addTableHeading(paragraphPointer->table, i18n("Service"), false);
	}

	if (filterListPointer->supportsTime == true)
		device->addTableHeading(paragraphPointer->table, i18n("Time"), false);

	if (filterListPointer->loggingSupport == true)
		device->addTableHeading(paragraphPointer->table, i18n("Log"), false);

	if (filterListPointer->supportsFragments == true)
		device->addTableHeading(paragraphPointer->table, i18n("Frag"), false);

	if (filterListPointer->supportsEstablished == true)
		device->addTableHeading(paragraphPointer->table, i18n("Estab"), false);

	if (filterSupportsThrough == true)
		device->addTableHeading(paragraphPointer->table, i18n("Through"), false);

	if (filterSupportsInstalled == true)
		device->addTableHeading(paragraphPointer->table, i18n("Install On"), false);

	if (filterListPointer->showStop == true)
		device->addTableHeading(paragraphPointer->table, i18n("Stop"), false);

	if (enableComments == true)
		device->addTableHeading(paragraphPointer->table, i18n("Comment"), false);

	return 0;
}


int Filter::addFilterTableRow(Device *device, Device::paragraphStruct *paragraphPointer, filterConfig *filterPointer, filterListConfig *filterListPointer, bool includeFilterList)
{
	// Variables...
	Device::bodyStruct *cellPointer = 0;
	string tempString;

	if (includeFilterList == true)
		device->addTableData(paragraphPointer->table, filterListPointer->name.c_str());

	if (filterPointer->remarkFilter == true)
	{
		cellPointer = device->addTableData(paragraphPointer->table, filterPointer->comment.c_str());
		cellPointer->rowSpan = true;
	}

	else
	{
		// ID / Line no
		if (useFilterID == true)
		{
			if (filterPointer->name.empty())
				tempString.assign(device->intToString(filterPointer->id));
			else
				tempString.assign(filterPointer->name);
		}
		else
			tempString.assign(device->intToString(filterPointer->number));
		device->addTableData(paragraphPointer->table, tempString.c_str());

		// Enabled/Disabled
		if (filterListPointer->disabledFilterSupport == true)
		{
			if (filterPointer->enabled == true)
				device->addTableData(paragraphPointer->table, i18n("Yes"));
			else
				device->addTableData(paragraphPointer->table, i18n("No"));
		}

		if (filterListPointer->showFilterType == true)
		{
			switch (filterPointer->type)
			{
				case sourceFilter:
					device->addTableData(paragraphPointer->table, i18n("Src"));
					break;
				case destinationFilter:
					device->addTableData(paragraphPointer->table, i18n("Dst"));
					break;
				default:
					device->addTableData(paragraphPointer->table, i18n("Glo"));
					break;
			}
		}

		// Access
		switch (filterPointer->action)
		{
			case allowAction:
				device->addTableData(paragraphPointer->table, allowName);
				break;
			case denyAction:
				device->addTableData(paragraphPointer->table, denyName);
				break;
			case rejectAction:
				device->addTableData(paragraphPointer->table, rejectName);
				break;
			case exceptAction:
				device->addTableData(paragraphPointer->table, i18n("Except"));
				break;
			case bypassAction:
				device->addTableData(paragraphPointer->table, i18n("Bypass"));
				break;
			case natAction:
				device->addTableData(paragraphPointer->table, i18n("*ABBREV*NAT*-ABBREV*"));
				break;
			case tunnelAction:
				device->addTableData(paragraphPointer->table, i18n("Tunnel"));
				break;
			default:
				device->addTableData(paragraphPointer->table, i18n("Default"));
				break;
		}

		// Protocols
		if ((filterListPointer->sourceOnly == false) && (filterListPointer->showProtocol == true))
			outputFilterProtocols(device, paragraphPointer->table, filterPointer->protocol);

		// Source
		if (filterPointer->sourceZone.empty())
			outputFilterHosts(device, paragraphPointer->table, filterPointer->source);
		else
			outputFilterHosts(device, paragraphPointer->table, filterPointer->source, filterPointer->sourceZone.c_str());

		// Source Services
		if (filterListPointer->sourceServiceSupported == true)
			outputFilterHostService(device, paragraphPointer->table, filterPointer->sourceService);

		// Destination
		if (filterListPointer->sourceOnly == false)
		{
			if (filterPointer->destZone.empty())
				outputFilterHosts(device, paragraphPointer->table, filterPointer->destination);
			else
				outputFilterHosts(device, paragraphPointer->table, filterPointer->destination, filterPointer->destZone.c_str());

			// Destination Service
			outputFilterHostService(device, paragraphPointer->table, filterPointer->destinationService);
		}

		// Time
		if (filterListPointer->supportsTime == true)
			outputFilterTime(device, paragraphPointer->table, filterPointer->time);

		// Log
		if (filterListPointer->loggingSupport == true)
		{
			if ((logOnlyDenySupported == true) && (filterPointer->action == allowAction))
				device->addTableData(paragraphPointer->table, i18n("N/A"));
			else if (filterPointer->log == true)
			{
				if (logLevelsSupported == true)
				{
					device->appendixLoggingLevels = true;
					tempString.assign(i18n("Yes (%d)"), filterPointer->logLevel);
					device->addTableData(paragraphPointer->table, tempString.c_str());
				}
				else
					device->addTableData(paragraphPointer->table, i18n("Yes"));
			}
			else
				device->addTableData(paragraphPointer->table, i18n("No"));
		}

		// Fragments
		if (filterListPointer->supportsFragments == true)
		{
			if (filterPointer->fragments == true)
				device->addTableData(paragraphPointer->table, i18n("Yes"));
			else
				device->addTableData(paragraphPointer->table, i18n("No"));
		}

		// Established
		if (filterListPointer->supportsEstablished == true)
		{
			if (filterPointer->established == true)
				device->addTableData(paragraphPointer->table, i18n("Yes"));
			else
				device->addTableData(paragraphPointer->table, i18n("No"));
		}

		// Through
		if (filterSupportsThrough == true)
			outputFilterHosts(device, paragraphPointer->table, filterPointer->through);

		// Installed
		if (filterSupportsInstalled == true)
			outputFilterHosts(device, paragraphPointer->table, filterPointer->install);

		// Stop?
		if (filterListPointer->showStop == true)
		{
			if (filterPointer->stop == true)
				device->addTableData(paragraphPointer->table, i18n("Yes"));
			else
				device->addTableData(paragraphPointer->table, i18n("No"));
		}

		// Comments
		if (enableComments == true)
			device->addTableData(paragraphPointer->table, filterPointer->comment.c_str());
	}

	return 0;
}


string tempFilterListText;
const char *Filter::filterListNameTextTitle(filterListConfig *filterListPointer)
{
	if (filterListPointer == 0)
		return "";

	if (filterListPointer->to.empty())
		return filterListPointer->name.c_str();

	tempFilterListText.assign(filterListPointer->name.c_str());
	tempFilterListText.append(i18n(" zone to "));
	tempFilterListText.append(filterListPointer->to.c_str());
	tempFilterListText.append(i18n(" zone"));
	return tempFilterListText.c_str();
}


const char *Filter::filterListTableTitle(filterListConfig *filterListPointer)
{
	if (filterListPointer == 0)
		return "";

	if (filterListPointer->to.empty())
		return filterListPointer->name.c_str();

	tempFilterListText.assign(filterListPointer->name.c_str());
	tempFilterListText.append(i18n("-"));
	tempFilterListText.append(filterListPointer->to.c_str());
	return tempFilterListText.c_str();
}

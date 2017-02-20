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
#include "../../globaldefs.h"
#include "../device.h"
#include "interfaces.h"


int Interfaces::outputInterfaceTableHeadings(Device *device, interfaceListConfig *interfaceListPointer, Device::paragraphStruct *paragraphPointer)
{
	// Table headings...
	device->addTableHeading(paragraphPointer->table, i18n("Interface"), false);

	if (interfaceListPointer->interfaceDisableSupport == true)
	{
		device->addTableHeading(paragraphPointer->table, i18n("Active"), false);
	}

	if (useInterfaceZone == true)
		device->addTableHeading(paragraphPointer->table, zoneName, false);

	if (interfaceListPointer->useSecurityLevel == true)
		device->addTableHeading(paragraphPointer->table, i18n("Security"), false);

	if (interfaceListPointer->ipAddressSupported == true)
	{
		device->addTableHeading(paragraphPointer->table, i18n("Address"), false);

		if (interfaceListPointer->useStandbyAddress == true)
			device->addTableHeading(paragraphPointer->table, i18n("Standby"), false);
	}

	if (interfaceListPointer->vlanSupported == true)
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*VLAN*-ABBREV*"), false);

	if (interfaceListPointer->portModeSupported == true)
		device->addTableHeading(paragraphPointer->table, i18n("Trunk"), false);

	if (interfaceListPointer->portSecuritySupported == true)
		device->addTableHeading(paragraphPointer->table, i18n("Security"), false);

	if (interfaceListPointer->inboundFilterSupported == true)
		device->addTableHeading(paragraphPointer->table, filterIn, false);

	if (interfaceListPointer->outboudFilterSupported == true)
		device->addTableHeading(paragraphPointer->table, filterOut, false);

	if (interfaceListPointer->proxyArpSupported == true)
		device->addTableHeading(paragraphPointer->table, i18n("P-*ABBREV*ARP*-ABBREV*"), false);

	if (interfaceListPointer->unreachablesSupported == true)
		device->addTableHeading(paragraphPointer->table, i18n("Unrea"), false);

	if (interfaceListPointer->redirectsSupported == true)
		device->addTableHeading(paragraphPointer->table, i18n("Redir"), false);

	if (interfaceListPointer->ipMaskReplySupported == true)
		device->addTableHeading(paragraphPointer->table, i18n("Mask"), false);

	if (interfaceListPointer->informationReplySupported == true)
		device->addTableHeading(paragraphPointer->table, i18n("Info"), false);

	if (interfaceListPointer->ipDirectBroadcastSupported == true)
		device->addTableHeading(paragraphPointer->table, i18n("Direc"), false);

	if (interfaceListPointer->cdpSupported == true)
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*CDP*-ABBREV*"), false);

	if (interfaceListPointer->mopSupported == true)
		device->addTableHeading(paragraphPointer->table, i18n("*ABBREV*MOP*-ABBREV*"), false);

	if ((showDescription == true) && (device->config->includeFilterRuleComments == true))
		device->addTableHeading(paragraphPointer->table, i18n("Description"), false);

	return 0;
}


int Interfaces::outputInterfaceTableRow(Device *device, interfaceListConfig *interfaceListPointer, interfaceConfig *interfacePointer, Device::paragraphStruct *paragraphPointer)
{
	// Variables...
	Device::bodyStruct *cellPointer = 0;
	Device::listStruct *listPointer = 0;
	bool newCell = true;
	string tempString;
	string tempString2;

	if ((useModuleAndPort == false) || (!interfacePointer->name.empty()))
	{
		device->addTableData(paragraphPointer->table, interfacePointer->name.c_str());
	}
	else
	{
		tempString.assign(device->intToString(interfacePointer->module));
		tempString2.assign(tempString);
		tempString2.append("/");
		tempString.assign(device->intToString(interfacePointer->port));
		tempString2.append(tempString);
		device->addTableData(paragraphPointer->table, tempString2.c_str());
	}

	if (interfaceListPointer->interfaceDisableSupport == true)
	{
		if (interfacePointer->enabled == true)
			device->addTableData(paragraphPointer->table, i18n("Yes"));
		else
			device->addTableData(paragraphPointer->table, i18n("No"));
	}

	if (useInterfaceZone == true)
		device->addTableData(paragraphPointer->table, interfacePointer->zone.c_str());
	if (interfaceListPointer->useSecurityLevel == true)
	{
		tempString.assign(device->intToString(interfacePointer->securityLevel));
		device->addTableData(paragraphPointer->table, tempString.c_str());
	}

	if (interfaceListPointer->ipAddressSupported == true)
	{
		if (interfacePointer->dhcp == true)
			device->addTableData(paragraphPointer->table, i18n("*ABBREV*DHCP*-ABBREV*"));
		else
		{
			tempString.assign(interfacePointer->address);
			if (!interfacePointer->netmask.empty())
			{
				tempString.append(" / ");
				tempString.append(interfacePointer->netmask);
			}
			device->addTableData(paragraphPointer->table, tempString.c_str());
		}

		if (interfaceListPointer->useStandbyAddress == true)
			device->addTableData(paragraphPointer->table, interfacePointer->standbyAddress.c_str());
	}

	if (interfaceListPointer->vlanSupported == true)
	{
		if (interfacePointer->vlan != 0)
		{
			listPointer = interfacePointer->vlan;
			while (listPointer != 0)
			{
				device->addTableData(paragraphPointer->table, listPointer->listItem.c_str());
				listPointer = listPointer->next;
			}
		}
		else
			device->addTableData(paragraphPointer->table, "");
	}

	if (interfaceListPointer->portModeSupported == true)
	{
		switch (interfacePointer->switchportMode)
		{
			case portModeAccess:
				device->addTableData(paragraphPointer->table, i18n("No"));
				break;
			case portModeTrunk:
				device->addTableData(paragraphPointer->table, i18n("Yes"));
				break;
			case portModeDynamic:
				device->addTableData(paragraphPointer->table, i18n("Auto"));
				break;
		}
	}

	if (interfaceListPointer->portSecuritySupported == true)
	{
		if (interfacePointer->switchportSecurity == false)
			device->addTableData(paragraphPointer->table, i18n("Off"));
		else
		{
			switch (interfacePointer->switchportViolation)
			{
				case onViolationShutdown:
					device->addTableData(paragraphPointer->table, i18n("Shutdown"));
					break;
				case onViolationRestrict:
					device->addTableData(paragraphPointer->table, i18n("Restrict"));
					break;
				case onViolationProtect:
					device->addTableData(paragraphPointer->table, i18n("Protect"));
					break;
			}
		}
	}

	if (interfaceListPointer->inboundFilterSupported == true)
	{
		if (interfacePointer->filterIn == 0)
			device->addTableData(paragraphPointer->table, "");
		else
		{
			listPointer = interfacePointer->filterIn;
			newCell = true;
			while (listPointer != 0)
			{
				cellPointer = device->addTableData(paragraphPointer->table, listPointer->listItem.c_str());
				cellPointer->referencer = true;
				tempString.assign("CONFIG-FILTER-");
				tempString.append(listPointer->listItem.c_str());
				tempString.append("-TABLE");
				cellPointer->reference.assign(tempString);
				if (newCell == false)
					cellPointer->newCell = false;
				else
					newCell = false;
				listPointer = listPointer->next;
			}
		}
	}

	if (interfaceListPointer->outboudFilterSupported == true)
	{
		if (interfacePointer->filterOut == 0)
			device->addTableData(paragraphPointer->table, "");
		else
		{
			listPointer = interfacePointer->filterOut;
			newCell = true;
			while (listPointer != 0)
			{
				cellPointer = device->addTableData(paragraphPointer->table, listPointer->listItem.c_str());
				cellPointer->referencer = true;
				tempString.assign("CONFIG-FILTER-");
				tempString.append(listPointer->listItem.c_str());
				cellPointer->reference.assign(tempString);
				if (newCell == false)
					cellPointer->newCell = false;
				else
					newCell = false;
				listPointer = listPointer->next;
			}
		}
	}

	if (interfaceListPointer->proxyArpSupported == true)
	{
		if (interfacePointer->proxyARP == true)
			device->addTableData(paragraphPointer->table, i18n("On"));
		else
			device->addTableData(paragraphPointer->table, i18n("Off"));
	}

	if (interfaceListPointer->unreachablesSupported == true)
	{
		if (interfacePointer->ipUnreachables == true)
			device->addTableData(paragraphPointer->table, i18n("On"));
		else
			device->addTableData(paragraphPointer->table, i18n("Off"));
	}

	if (interfaceListPointer->redirectsSupported == true)
	{
		if (interfacePointer->ipRedirects == true)
			device->addTableData(paragraphPointer->table, i18n("On"));
		else
			device->addTableData(paragraphPointer->table, i18n("Off"));
	}

	if (interfaceListPointer->ipMaskReplySupported == true)
	{
		if (interfacePointer->ipMaskReply == true)
			device->addTableData(paragraphPointer->table, i18n("On"));
		else
			device->addTableData(paragraphPointer->table, i18n("Off"));
	}

	if (interfaceListPointer->informationReplySupported == true)
	{
		if (interfacePointer->infoReply == true)
			device->addTableData(paragraphPointer->table, i18n("On"));
		else
			device->addTableData(paragraphPointer->table, i18n("Off"));
	}

	if (interfaceListPointer->ipDirectBroadcastSupported == true)
		device->addTableData(paragraphPointer->table, interfacePointer->ipDirectBroadcast.c_str());

	if (interfaceListPointer->cdpSupported == true)
	{
		if (interfacePointer->cdp == true)
			device->addTableData(paragraphPointer->table, i18n("On"));
		else
			device->addTableData(paragraphPointer->table, i18n("Off"));
	}

	if (interfaceListPointer->mopSupported == true)
	{
		if (interfacePointer->mop == true)
			device->addTableData(paragraphPointer->table, i18n("On"));
		else
			device->addTableData(paragraphPointer->table, i18n("Off"));
	}

	if ((showDescription == true) && (device->config->includeFilterRuleComments == true))
		device->addTableData(paragraphPointer->table, interfacePointer->description.c_str());

	return 0;
}


int Interfaces::outputInterfaceTableExplain(Device *device, interfaceListConfig *interfaceListPointer, Device::paragraphStruct *paragraphPointer)
{
	if ((interfaceListPointer->proxyArpSupported == true) || (interfaceListPointer->mopSupported == true) || (interfaceListPointer->cdpSupported == true) || (interfaceListPointer->ipDirectBroadcastSupported == true) || (interfaceListPointer->informationReplySupported == true) || (interfaceListPointer->ipMaskReplySupported == true) || (interfaceListPointer->redirectsSupported == true) || (interfaceListPointer->unreachablesSupported == true))
	{
		paragraphPointer->paragraph.assign(i18n("In order to provide additional information in the interface settings table, a number of table column headings were truncated or abbreviated. These table column headings were:"));
		if (interfaceListPointer->proxyArpSupported == true)
			device->addListItem(paragraphPointer, i18n("P-ARP : Proxy *ABBREV*ARP*-ABBREV* support"));
		if (interfaceListPointer->unreachablesSupported == true)
			device->addListItem(paragraphPointer, i18n("Unrea : *ABBREV*ICMP*-ABBREV* unreachable messages"));
		if (interfaceListPointer->redirectsSupported == true)
			device->addListItem(paragraphPointer, i18n("Redir : *ABBREV*ICMP*-ABBREV* redirect messages"));
		if (interfaceListPointer->ipMaskReplySupported == true)
			device->addListItem(paragraphPointer, i18n("Redir : *ABBREV*ICMP*-ABBREV* mask reply messages"));
		if (interfaceListPointer->informationReplySupported == true)
			device->addListItem(paragraphPointer, i18n("Info : *ABBREV*ICMP*-ABBREV* information reply messages"));
		if (interfaceListPointer->ipDirectBroadcastSupported == true)
			device->addListItem(paragraphPointer, i18n("Direc : *ABBREV*IP*-ABBREV* directed broadcases"));
		if (interfaceListPointer->cdpSupported == true)
			device->addListItem(paragraphPointer, i18n("CDP : *ABBREV*CDP*-ABBREV* support"));
		if (interfaceListPointer->mopSupported == true)
			device->addListItem(paragraphPointer, i18n("MOP : *ABBREV*MOP*-ABBREV* support"));
	}

	return 0;
}


int Interfaces::generateConfigReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	interfaceListConfig *interfaceListPointer = 0;
	interfaceConfig *interfacePointer = 0;
	string tempString;
	int errorCode = 0;

	// Are there interfaces to report...
	if ((interfaceList != 0) || (globalRedirectSupported == true) || (globalIPUnreachableSupported == true))
	{

		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s Network Interface Settings\n", device->config->COL_BLUE, device->config->COL_RESET);

		// Create Config Report Section...
		configReportPointer = device->getConfigSection("CONFIG-INTERFACE");
		configReportPointer->title = i18n("Network Interface Settings");
		paragraphPointer = device->addParagraph(configReportPointer);
		paragraphPointer->paragraph.assign(i18n("The section details the *DEVICETYPE* devices network interface configuration settings."));

		if ((globalRedirectSupported == true) || (globalIPUnreachableSupported == true))
		{
			// Init pointers...
			paragraphPointer = device->addParagraph(configReportPointer);

			// Set subsection title...
			paragraphPointer->paragraphTitle.assign(i18n("General Settings"));
			paragraphPointer->paragraph.assign(i18n("This section details the general settings relating to the *DEVICETYPE* device interfaces."));

			// Create Table...
			errorCode = device->addTable(paragraphPointer, "CONFIG-GENERALINTER-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("General interface related settings");

			device->addTableHeading(paragraphPointer->table, i18n("Description"), false);
			device->addTableHeading(paragraphPointer->table, i18n("Setting"), false);

			if (globalIPUnreachableSupported == true)
			{
				device->addTableData(paragraphPointer->table, i18n("*ABBREV*ICMP*-ABBREV* Unreachable Message Sending"));
				if (globalUnreachableEnabled == true)
					device->addTableData(paragraphPointer->table, i18n("Enabled"));
				else
					device->addTableData(paragraphPointer->table, i18n("Disabled"));
			}
			if (globalRedirectSupported == true)
			{
				device->addTableData(paragraphPointer->table, i18n("*ABBREV*ICMP*-ABBREV* Redirect Message Sending"));
				if (globalRedirectEnabled == true)
					device->addTableData(paragraphPointer->table, i18n("Enabled"));
				else
					device->addTableData(paragraphPointer->table, i18n("Disabled"));
			}
		}

		interfaceListPointer = interfaceList;
		while (interfaceListPointer != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s %s\n", device->config->COL_BLUE, device->config->COL_RESET, interfaceListPointer->title);

			// Init pointers...
			paragraphPointer = device->addParagraph(configReportPointer);

			// Set subsection title...
			paragraphPointer->paragraphTitle.assign(interfaceListPointer->title);
			paragraphPointer->paragraph.assign(interfaceListPointer->description);

			// Create Table...
			tempString.assign("CONFIG-");
			tempString.append(interfaceListPointer->label);
			tempString.append("-TABLE");
			errorCode = device->addTable(paragraphPointer, tempString.c_str());
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = interfaceListPointer->tableTitle;

			outputInterfaceTableHeadings(device, interfaceListPointer, paragraphPointer);

			interfacePointer = interfaceListPointer->interface;
			while (interfacePointer != 0)
			{
				outputInterfaceTableRow(device, interfaceListPointer, interfacePointer, paragraphPointer);
				interfacePointer = interfacePointer->next;
			}
			paragraphPointer = device->addParagraph(configReportPointer);
			outputInterfaceTableExplain(device, interfaceListPointer, paragraphPointer);

			interfaceListPointer = interfaceListPointer->next;
		}
	}

	return errorCode;
}


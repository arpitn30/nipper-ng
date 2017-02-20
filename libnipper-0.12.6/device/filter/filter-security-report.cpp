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
#include <cmath>

#include "../../globaldefs.h"
#include "../device.h"
#include "filter.h"


int Filter::generateSecurityReportIssues(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	filterIssueConfig *filterIssuePointer = 0;
	filterListIssueConfig *filterListIssuePointer = 0;
	filterListConfig *filterRuleList = 0;
	filterDuplConfig *contradictPointer = 0;
	string tempString;
	int errorCode = 0;
	int tempCount = 0;

	// No Filters...
	if ((filterList == 0) && (device->config->checkFilteringIsConfigured == true))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] No Filters Configured\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(noFilteringIssue);
		securityIssuePointer->reference.assign("GEN.FILTNOFI.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addString(paragraphPointer, filterListName);
		device->addString(paragraphPointer, filterListName);
		paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices can be configured with *DATA* to restrict access to network devices and services. *COMPANY* determined that no *DATA* were configured on *DEVICENAME*."));

		// Issue impact...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		if (noAccessWithoutFilters == false)
		{
			device->addString(paragraphPointer, filterListName);
			paragraphPointer->paragraph.assign(i18n("With no *DATA* configured an attacker or malicious user could gain unauthorised access to services provided by *DEVICENAME* or other network devices."));
			if (device->isFirewall == true)
			{
				securityIssuePointer->impactRating = 9;			// Critical
				paragraphPointer->paragraph.append(i18n(" The primary purpose of *DEVICETYPE* devices is to provide a security barrier against unauthorised access."));
			}
			else
				securityIssuePointer->impactRating = 6;			// Medium
		}
		else
		{
			device->addString(paragraphPointer, filterListName);
			paragraphPointer->paragraph.assign(i18n("With no *DATA* configured an attacker or malicious user would not be able to access network services through the device as all network traffic would be blocked by *DEVICENAME*."));
			securityIssuePointer->impactRating = 3;				// Low
		}

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		if (noAccessWithoutFilters == false)
		{
			securityIssuePointer->easeRating = 0;					// N/A
			device->addString(paragraphPointer, filterListName);
			paragraphPointer->paragraph.assign(i18n("With no *DATA* a user or attacker would not be restricted by *DEVICENAME* when access network services."));
		}
		else
		{
			securityIssuePointer->easeRating = 10;					// N/A
			device->addString(paragraphPointer, filterListName);
			paragraphPointer->paragraph.assign(i18n("With no *DATA* a user or attacker would not be able to access any network services through *DEVICENAME*."));
		}

		// Issue recommendation...
		securityIssuePointer->fixRating = 6;						// Planned
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		device->addString(paragraphPointer, filterListName);
		if (device->isFirewall == true)
			paragraphPointer->paragraph.assign(i18n("The primary purpose of *DEVICETYPE* devices is to restrict access to only authorised hosts and services. "));
		paragraphPointer->paragraph.append(i18n("If *DEVICENAME* is not required, *COMPANY* recommends that *DEVICENAME* is decomissioned. If *DEVICENAME* is required, *COMPANY* recommends that *DATA* are configured."));

		recommendedFiltering(device, securityIssuePointer);

		// Conclusions text...
		securityIssuePointer->conLine.assign(noFilteringCon);

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, noFilteringRec, true);
		device->addRecommendation(securityIssuePointer, i18n("decommision *DEVICENAME*"), true);
	}


	else if (filterList != 0)
	{


		if (anyAnyAnyAny != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed From Any Source And Service To Any Destination And Service\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (anyAnyAnyAny->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Allows Any Access"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTAAAA.1");

			if (anyAnyAnyAny->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allows any access"));
			writeFilterSecurityIssue(device, securityIssuePointer, anyAnyAnyAny, i18n("allowed access to any network address and service from any other network address and service."), "GEN-FILTAAAA-", allowAnythingTable, 10, tempString.c_str());
		}


		if (weakWeakWeakWeak != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed From Weak Source And Service To Weak Destination And Service\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (weakWeakWeakWeak->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Provides Weak Filtering"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTWAAA.1");

			if (weakWeakWeakWeak->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" provides weak filtering"));
			writeFilterSecurityIssue(device, securityIssuePointer, weakWeakWeakWeak, i18n("allowed access between entire network address source and destinations with relaxed source port and destination services."), "GEN-FILTWAAA-", allowWeakTable, 9, tempString.c_str());
		}


		if (anyAnyAny != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed From Any Source To Any Destination And Service\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (anyAnyAny->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Allows Access Between Any Source, Destination And Service"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTAAAN.1");

			if (anyAnyAny->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allows access between any source, destination and service"));
			writeFilterSecurityIssue(device, securityIssuePointer, anyAnyAny, i18n("allowed access from any source address to any destination address and service."), "GEN-FILTAAAN-", allowAnyAnyAnyTable, 9, tempString.c_str());
		}


		if (weakWeakWeak != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed From A Weak Source To A Weak Destination And Service\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			securityIssuePointer->title.assign(i18n("Weak Filtering Of Source, Destination And Services"));
			securityIssuePointer->reference.assign("GEN.FILTWAAN.1");

			if (weakWeakWeak->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" access with weak source, destination and service settings"));
			writeFilterSecurityIssue(device, securityIssuePointer, weakWeakWeak, i18n("allowed access between entire network address source and destinations with a range of destination services."), "GEN-FILTWAAN-", allowWeakWeakWeakTable, 9, tempString.c_str());
		}


		if (anyServiceAnyAny != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed From Any Source Port To Any Destination And Service\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (anyServiceAnyAny->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Allows Access Between Any Source Port, Destination And Service"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTSAAN.1");

			if (anyServiceAnyAny->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allows access between any source port, destination and service"));
			writeFilterSecurityIssue(device, securityIssuePointer, anyServiceAnyAny, i18n("allowed access from any source port to any destination address and service."), "GEN-FILTSAAN-", allowAnyServiceAnyTable, 8, tempString.c_str());
		}


		if (weakServiceAnyAny != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed From A Weak Source Port To A Weak Destination And Service\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			securityIssuePointer->title.assign(i18n("Weak Filtering Of Source Port, Destination And Services"));
			securityIssuePointer->reference.assign("GEN.FILTWSAN.1");

			if (weakServiceAnyAny->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" access with weak source port, destination and service settings"));
			writeFilterSecurityIssue(device, securityIssuePointer, weakServiceAnyAny, i18n("allowed access from any source port to any destination address and service."), "GEN-FILTWSAN-", allowWeakServiceAnyTable, 8, tempString.c_str());
		}


		if (anyAny != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed From Any Source To Any Destination\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (anyAny->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Allows Access Between Any Source And Destination Address"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTANAN.1");

			if (anyAny->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allows access between any source and destination address"));
			writeFilterSecurityIssue(device, securityIssuePointer, anyAny, i18n("allowed access from any source address to any destination address."), "GEN-FILTANAN-", allowAnyAnyTable, 8, tempString.c_str());
		}


		if (anyAnyDestService != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed From Any Source To Any Destination Service\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (anyAnyDestService->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Allows Access Between Any Source Address And Destination Service"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTANAS.1");

			if (anyAnyDestService->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allows access between any source address and destination service"));
			writeFilterSecurityIssue(device, securityIssuePointer, anyAnyDestService, i18n("allowed access from any source address to any destination service."), "GEN-FILTANAS-", allowAnyAnyServiceTable, 8, tempString.c_str());
		}


		if (destHostAndService != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed To Any Destination Host And Service\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (destHostAndService->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Allows Access To Any Destination And Service"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTANDS.1");

			if (destHostAndService->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allows access to any destination and service"));
			writeFilterSecurityIssue(device, securityIssuePointer, destHostAndService, i18n("allowed access to any destination and service."), "GEN-FILTANDS-", allowAnyDestServiceTable, 8, tempString.c_str());
		}


		if (anyServiceAny != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed From Any Source Port To Any Destination Address\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (anyServiceAny->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Allows Access From Any Source Port To Any Destination Address"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTSNAN.1");

			if (anyServiceAny->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allows access from any source port to any destination address"));
			writeFilterSecurityIssue(device, securityIssuePointer, anyServiceAny, i18n("allowed access from any source port to any destination address."), "GEN-FILTSNAN-", allowAnyPortDestTable, 7, tempString.c_str());
		}


		if (anyServiceAnyService != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed From Any Source Port To Any Destination Service\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (anyServiceAnyService->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Allows Access From Any Source Port To Any Destination Service"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTASDS.1");

			if (anyServiceAnyService->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allows access from any source port to any destination service"));
			writeFilterSecurityIssue(device, securityIssuePointer, anyServiceAnyService, i18n("allowed access from any source port to any destination service."), "GEN-FILTASDS-", allowAnyPortServiceTable, 6, tempString.c_str());
		}


		if (weakWeak != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Weak Filtering Of Source And Destination Addresses\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (weakWeak->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Weak Filtering Of Source And Destination Addresses"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTWNAN.1");

			if (weakWeak->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allows entire network source and destination addresses"));
			writeFilterSecurityIssue(device, securityIssuePointer, weakWeak, i18n("allowed entire source network addresses to access entire destination network addresses."), "GEN-FILTWNAN-", allowWeakWeakTable, 6, tempString.c_str());
		}


		if (weakDestService != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed From Weak Source To Weak Destination Service\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (weakDestService->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Weak Filtering Of Source Addresses And Destination Services"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTWNAS.1");

			if (weakDestService->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allows entire network source addresses to access a range of destination services"));
			writeFilterSecurityIssue(device, securityIssuePointer, weakDestService, i18n("allowed entire source network addresses to access a range of destination services."), "GEN-FILTWNAS-", allowWeakWeakServiceTable, 5, tempString.c_str());
		}


		if (weakDestHostAndService != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed To Weak Destination And Service\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (weakDestHostAndService->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" With Weak Destination And Service Configuration"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTWNDS.1");

			if (weakDestHostAndService->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allowed access to entire network destination addresses with a range services"));
			writeFilterSecurityIssue(device, securityIssuePointer, weakDestHostAndService, i18n("allowed access to destination network addresses and a range of services."), "GEN-FILTWNDS-", allowDestAndServiceTable, 5, tempString.c_str());
		}


		if (weakServiceAny != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed From Weak Source Port To Weak Destination\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (weakServiceAny->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Permits Weak Source Port To A Weak Destination"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTWSNN.1");

			if (weakServiceAny->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allowed access from a range of source ports to a network destination addresses"));
			writeFilterSecurityIssue(device, securityIssuePointer, weakServiceAny, i18n("allowed access from a range of source ports to destination network addresses."), "GEN-FILTWSNN-", allowWeakPortDestTable, 5, tempString.c_str());
		}


		if (weakServiceAnyService != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed From Weak Source Service To Weak Destination Service\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (weakServiceAnyService->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Permits Weak Source Port To A Weak Destination Service"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTWSDS.1");

			if (weakServiceAnyService->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allowed access from a range of source ports to a range of destination services"));
			writeFilterSecurityIssue(device, securityIssuePointer, weakServiceAnyService, i18n("allowed access from a range of source ports to a range of destination services."), "GEN-FILTWSDS-", allowWeakPortServiceTable, 5, tempString.c_str());
		}


		if (anySourceHost != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed From Any Source\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (anySourceHost->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Allows Access From Any Source Address"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTANSO.1");

			if (anySourceHost->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allowed access from any source address"));
			writeFilterSecurityIssue(device, securityIssuePointer, anySourceHost, i18n("allowed access from any source address."), "GEN-FILTANSO-", allowAnySourceTable, 4, tempString.c_str());
		}


		if (netSourceHost != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed From A Network Source\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (netSourceHost->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Allows Access From A Network Source Address"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTNESO.1");

			if (netSourceHost->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allowed access from a network source address"));
			writeFilterSecurityIssue(device, securityIssuePointer, netSourceHost, i18n("allowed access from a network source address."), "GEN-FILTNESO-", allowNetSourceTable, 4, tempString.c_str());
		}


		if (anySourceService != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed From Any Source Port\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (anySourceService->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Allows Access From Any Source Port"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTANSS.1");

			if (anySourceService->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allowed access from any source port"));
			writeFilterSecurityIssue(device, securityIssuePointer, anySourceService, i18n("allowed access from any source port."), "GEN-FILTANSS-", allowAnyPortTable, 3, tempString.c_str());
		}


		if (rangeSourceService != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed From A Source Port Range\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (rangeSourceService->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Allows Access From A Source Port Range"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTRASS.1");

			if (rangeSourceService->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allowed access from a source port range"));
			writeFilterSecurityIssue(device, securityIssuePointer, rangeSourceService, i18n("allowed access from a source port range."), "GEN-FILTRASS-", allowRangePortTable, 3, tempString.c_str());
		}


		if (anyDestination != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed To Any Destination\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (anyDestination->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Allows Access To Any Destination Address"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTANDE.1");

			if (anyDestination->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allowed access to any destination address"));
			writeFilterSecurityIssue(device, securityIssuePointer, anyDestination, i18n("allowed access to any destination address."), "GEN-FILTANDE-", allowAnyDestTable, 6, tempString.c_str());
		}


		if (netDestination != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed To A Network Destination\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (netDestination->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Allows Access To A Network Destination Address"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTNEDE.1");

			if (netDestination->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allowed access to a network destination address"));
			writeFilterSecurityIssue(device, securityIssuePointer, netDestination, i18n("allowed access to a network destination address."), "GEN-FILTNEDE-", allowNetDestTable, 5, tempString.c_str());
		}


		if (anyDestService != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed To Any Destination Service\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (anyDestService->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Allows Access To Any Destination Service"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTANSE.1");

			if (anyDestService->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allowed access to any destination service"));
			writeFilterSecurityIssue(device, securityIssuePointer, anyDestService, i18n("allowed access to any destination service."), "GEN-FILTANSE-", allowToAnyDestServiceTable, 5, tempString.c_str());
		}


		if (rangeDestService != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Access Allowed To A Destination Service Range\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			if (rangeDestService->next != 0)
				tempString.assign(filterTitlePlaural);
			else
				tempString.assign(filterTitle);
			tempString.append(i18n(" Allows Access To A Destination Service Range"));
			securityIssuePointer->title.assign(tempString);
			securityIssuePointer->reference.assign("GEN.FILTRDSS.1");

			if (rangeDestService->next != 0)
				tempString.assign(filterNamePlaural);
			else
				tempString.assign(filterName);
			tempString.append(i18n(" allowed access to a destination service range"));
			writeFilterSecurityIssue(device, securityIssuePointer, rangeDestService, i18n("allowed access to a destination service range."), "GEN-FILTRDSS-", allowToNetDestServiceTable, 4, tempString.c_str());
		}


		if (allowedLogging != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] All Allow Rules Do Not Log\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			securityIssuePointer->title.assign(allowAndNotLogIssue);
			securityIssuePointer->reference.assign("GEN.FILTALLO.1");

			tempCount = 0;
			filterIssuePointer = allowedLogging;
			while (filterIssuePointer != 0)
			{
				tempCount++;
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue finding...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			paragraphPointer->paragraph.assign(i18n("The *DEVICETYPE* device network filtering configuration can be configured to log access that is allowed. When this logging facility is enabled, an audit trail will be created which could be useful when tracking access issues or determining who had accessed which service and when."));
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addValue(paragraphPointer, tempCount);
			if (tempCount > 1)
			{
				device->addString(paragraphPointer, filterNamePlaural);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* did not log allowed access. These are listed below."));
			}
			else
			{
				device->addString(paragraphPointer, filterName);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* did not log allowed access, which is shown in Table *TABLEREF*."));
			}

			// Table data...
			filterIssuePointer = allowedLogging;
			filterRuleList = 0;
			while (filterIssuePointer != 0)
			{

				if (filterRuleList != filterIssuePointer->filterRuleList)
				{
					if (filterRuleList != 0)
						paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

					filterRuleList = filterIssuePointer->filterRuleList;

					// Finding table...
					tempString.assign("GEN-FILTALLO-");
					tempString.append(filterRuleList->name);
					tempString.append("-TABLE");
					errorCode = device->addTable(paragraphPointer, tempString.c_str());
					if (errorCode != 0)
						return errorCode;
					tempString.assign(filterListNameTitle);
					tempString.append(" ");
					tempString.append(filterRuleList->name);
					tempString.append(" ");
					tempString.append(allowAndNotLogTable);
					paragraphPointer->table->title.assign(tempString);

					// Table titles...
					addFilterTableHeadings(device, paragraphPointer, filterIssuePointer->filterRuleList);
				}

				addFilterTableRow(device, paragraphPointer, filterIssuePointer->filter, filterIssuePointer->filterRuleList);
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue impact...
			if (device->isFirewall == true)
				securityIssuePointer->impactRating = 3;			// Low
			else
				securityIssuePointer->impactRating = 2;			// Informational
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			paragraphPointer->paragraph.assign(i18n("If an attacker were to gain access to *DEVICENAME* or other network devices, an analysis of logs helps in determining the level of access the attacker gained. The logs could also be used to identify an attacker and as evidence in any legal action taken against the attacker. Without logging allowed access it may be difficult to determine what systems and services an attacker has accessed."));

			// Issue ease...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			securityIssuePointer->easeRating = 0;				// N/A
			paragraphPointer->paragraph.assign(i18n("The access attempts would not be logged by *DEVICENAME*."));

			// Issue recommendation...
			securityIssuePointer->fixRating = 3;				// Trivial
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, where possible, all *DATA* should be configured to log. "));
			if (strlen(configRuleLogging) > 0)
				paragraphPointer->paragraph.append(configRuleLogging);

			// Conclusions text...
			securityIssuePointer->conLine.assign(allowAndNotLogConcl);

			// Recommendation list text...
			device->addRecommendation(securityIssuePointer, allowAndNotLogReco, true);	

			// Related issues...
			if (deniedLogging != 0)
				device->addRelatedIssue(securityIssuePointer, "GEN.FILTDELO.1");
		}


		if (deniedLogging != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] All Deny Rules Do Not Log\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			securityIssuePointer->title.assign(denyAndNotLogIssue);
			securityIssuePointer->reference.assign("GEN.FILTDELO.1");

			tempCount = 0;
			filterIssuePointer = deniedLogging;
			while (filterIssuePointer != 0)
			{
				tempCount++;
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue finding...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			paragraphPointer->paragraph.assign(i18n("The *DEVICETYPE* device network filtering configuration can be configured to log access that is denied. When this logging facility is enabled, an audit trail will be created which could be useful when tracking access issues or determining who has been attempting to access which service and when."));
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addValue(paragraphPointer, tempCount);
			if (tempCount > 1)
			{
				device->addString(paragraphPointer, filterNamePlaural);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* did not log denied access. These are listed below."));
			}
			else
			{
				device->addString(paragraphPointer, filterName);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* did not log denied access, which is shown in Table *TABLEREF*."));
			}

			// Table data...
			filterIssuePointer = deniedLogging;
			filterRuleList = 0;
			while (filterIssuePointer != 0)
			{

				if (filterRuleList != filterIssuePointer->filterRuleList)
				{
					if (filterRuleList != 0)
						paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

					filterRuleList = filterIssuePointer->filterRuleList;

					// Finding table...
					tempString.assign("GEN-FILTDELO-");
					tempString.append(filterRuleList->name);
					tempString.append("-TABLE");
					errorCode = device->addTable(paragraphPointer, tempString.c_str());
					if (errorCode != 0)
						return errorCode;
					tempString.assign(filterListNameTitle);
					tempString.append(" ");
					tempString.append(filterRuleList->name);
					tempString.append(" ");
					tempString.append(denyAndNotLogTable);
					paragraphPointer->table->title.assign(tempString);

					// Table titles...
					addFilterTableHeadings(device, paragraphPointer, filterIssuePointer->filterRuleList);
				}

				addFilterTableRow(device, paragraphPointer, filterIssuePointer->filter, filterIssuePointer->filterRuleList);
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue impact...
			if (device->isFirewall == true)
				securityIssuePointer->impactRating = 3;			// Low
			else
				securityIssuePointer->impactRating = 2;			// Informational
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			paragraphPointer->paragraph.assign(i18n("Typically an attacker will perform network scans in order to enumerate the network services offered by devices on the network. Without adequate logging an attackers attempt to enumerate the network services may remain undetected. The logs could also be used to identify an attacker and as evidence in any legal action taken against the attacker."));

			// Issue ease...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			securityIssuePointer->easeRating = 0;				// N/A
			paragraphPointer->paragraph.assign(i18n("The access attempts would not be logged by *DEVICENAME*."));

			// Issue recommendation...
			securityIssuePointer->fixRating = 3;				// Trivial
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, where possible, all *DATA* should configured to log. "));
			if (strlen(configRuleLogging) > 0)
				paragraphPointer->paragraph.append(configRuleLogging);

			// Conclusions text...
			securityIssuePointer->conLine.assign(denyAndNotLogConcl);

			// Recommendation list text...
			device->addRecommendation(securityIssuePointer, allowAndNotLogReco, true);

			// Related issues...
			if (deniedLogging != 0)
				device->addRelatedIssue(securityIssuePointer, "GEN.FILTALLO.1");
		}


		if (filterRejects != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Reject Filtering Rules Are Configured\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			securityIssuePointer->title.assign(rejectSecurityIssueTitle);
			securityIssuePointer->reference.assign("GEN.FILTREJE.1");

			tempCount = 0;
			filterIssuePointer = filterRejects;
			while (filterIssuePointer != 0)
			{
				tempCount++;
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue finding...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("On *DEVICETYPE* devices *DATA* can be configured to reject the network traffic rather than simple dropped by *DEVICENAME*. When network traffic is rejected by *DEVICENAME*, a *ABBREV*ICMP*-ABBREV* unreachable message is sent to the sender to notify them that the traffic was denied by *DEVICENAME*."));
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addValue(paragraphPointer, tempCount);
			if (tempCount > 1)
			{
				device->addString(paragraphPointer, filterNamePlaural);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* were configured to reject network traffic. These are listed below."));
			}
			else
			{
				device->addString(paragraphPointer, filterName);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* was configured to reject network traffic, this is shown in Table *TABLEREF*."));
			}

			// Table data...
			filterIssuePointer = filterRejects;
			filterRuleList = 0;
			while (filterIssuePointer != 0)
			{

				if (filterRuleList != filterIssuePointer->filterRuleList)
				{
					if (filterRuleList != 0)
						paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

					filterRuleList = filterIssuePointer->filterRuleList;

					// Finding table...
					tempString.assign("GEN-FILTREJE-");
					tempString.append(filterRuleList->name);
					tempString.append("-TABLE");
					errorCode = device->addTable(paragraphPointer, tempString.c_str());
					if (errorCode != 0)
						return errorCode;
					tempString.assign(filterListNameTitle);
					tempString.append(" ");
					tempString.append(filterRuleList->name);
					tempString.append(" ");
					tempString.append(denyAndNotLogTable);
					paragraphPointer->table->title.assign(tempString);

					// Table titles...
					addFilterTableHeadings(device, paragraphPointer, filterIssuePointer->filterRuleList);
				}

				addFilterTableRow(device, paragraphPointer, filterIssuePointer->filter, filterIssuePointer->filterRuleList);
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue impact...
			if (device->isFirewall == true)
				securityIssuePointer->impactRating = 3;			// Low
			else
				securityIssuePointer->impactRating = 3;			// Low
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			device->addString(paragraphPointer, filterName);
			paragraphPointer->paragraph.assign(i18n("Although a *DATA* configured to reject traffic is not a direct threat to security, it does make the attacker life easier. If *DEVICENAME* simply dropped the network traffic, the attackers network scanner would be left waiting for a response that will never arrive. However, with *DEVICENAME* rejecting the network traffic the attackers scans will complete more quickly."));

			// Issue ease...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			securityIssuePointer->easeRating = 0;				// N/A
			paragraphPointer->paragraph.assign(i18n("The access attempt would cause *DEVICENAME* to respond with an *ABBREV*ICMP*-ABBREV* unreachable message."));

			// Issue recommendation...
			securityIssuePointer->fixRating = 3;				// Trivial
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that *DEVICENAME* should be configured to drop network traffic instead of rejecting it."));

			// Conclusions text...
			securityIssuePointer->conLine.assign(securityRejectTextCon);

			// Recommendation list text...
			device->addRecommendation(securityIssuePointer, securityRejectTextRec, true);
		}


		if (filterBypasses != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Bypass Filtering Rules Are In Use\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			securityIssuePointer->title.assign(i18n("Bypass Rules Are In Use"));
			securityIssuePointer->reference.assign("GEN.FILTBYPA.1");

			tempCount = 0;
			filterIssuePointer = filterBypasses;
			while (filterIssuePointer != 0)
			{
				tempCount++;
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue finding...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addString(paragraphPointer, filterName);
			paragraphPointer->paragraph.assign(i18n("The *DEVICETYPE* device *DATA* can be configured to bypass. If bypassed, the traffic is sent directly to the destination bypassing any configured content rules. "));
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addValue(paragraphPointer, tempCount);
			if (tempCount > 1)
			{
				device->addString(paragraphPointer, filterNamePlaural);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* were configured to bypass. These are listed below."));
			}
			else
			{
				device->addString(paragraphPointer, filterName);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* was configured to bypass, which is shown in Table *TABLEREF*."));
			}

			// Table data...
			filterIssuePointer = filterBypasses;
			filterRuleList = 0;
			while (filterIssuePointer != 0)
			{

				if (filterRuleList != filterIssuePointer->filterRuleList)
				{
					if (filterRuleList != 0)
						paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

					filterRuleList = filterIssuePointer->filterRuleList;

					// Finding table...
					tempString.assign("GEN-FILTBYPA-");
					tempString.append(filterRuleList->name);
					tempString.append("-TABLE");
					errorCode = device->addTable(paragraphPointer, tempString.c_str());
					if (errorCode != 0)
						return errorCode;
					tempString.assign(filterListNameTitle);
					tempString.append(" ");
					tempString.append(filterRuleList->name);
					tempString.append(" ");
					tempString.append(denyAndNotLogTable);
					paragraphPointer->table->title.assign(tempString);

					// Table titles...
					addFilterTableHeadings(device, paragraphPointer, filterIssuePointer->filterRuleList);
				}

				addFilterTableRow(device, paragraphPointer, filterIssuePointer->filter, filterIssuePointer->filterRuleList);
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue impact...
			if (device->isFirewall == true)
				securityIssuePointer->impactRating = 4;			// Low
			else
				securityIssuePointer->impactRating = 3;			// Low
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			paragraphPointer->paragraph.assign(i18n("If an attacker was able to make use of the bypass rule and a vulnerability exists in the application, the attacker may be able to exploit the vulnerability in the application by bypassing the content filtering."));

			// Issue ease...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			securityIssuePointer->easeRating = 0;				// N/A
			paragraphPointer->paragraph.assign(i18n("The access attempts would bypass the content filtering on *DEVICENAME*."));

			// Issue recommendation...
			securityIssuePointer->fixRating = 3;				// Trivial
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, where possible, all *DATA* should not be reconfigured to not bypass the content filtering."));

			// Conclusions text...
			securityIssuePointer->conLine.assign(bypassContentFilterCon);

			// Recommendation list text...
			device->addRecommendation(securityIssuePointer, bypassContentFilterRec, true);
		}


		if (filterDefault != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Default Filtering Action Rules Are In Use\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			securityIssuePointer->title.assign(i18n("Default Action Rules Are In Use"));
			securityIssuePointer->reference.assign("GEN.FILTDEFT.1");

			tempCount = 0;
			filterIssuePointer = filterDefault;
			while (filterIssuePointer != 0)
			{
				tempCount++;
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue finding...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addString(paragraphPointer, filterNamePlaural);
			device->addString(paragraphPointer, filterName);
			paragraphPointer->paragraph.assign(i18n("On *DEVICETYPE* devices, *DATA* can be configured to allow or deny the network traffic based on the rule. However, a port can also be configured to allow or deny network traffic and a *DATA* can be configured to accept the default action applied to the port."));
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addValue(paragraphPointer, tempCount);
			if (tempCount > 1)
			{
				device->addString(paragraphPointer, filterNamePlaural);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* were configured to default to the ports filter action. These are listed below."));
			}
			else
			{
				device->addString(paragraphPointer, filterName);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* was configured to default to the ports filter action, this is shown in Table *TABLEREF*."));
			}

			// Table data...
			filterIssuePointer = filterDefault;
			filterRuleList = 0;
			while (filterIssuePointer != 0)
			{

				if (filterRuleList != filterIssuePointer->filterRuleList)
				{
					if (filterRuleList != 0)
						paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

					filterRuleList = filterIssuePointer->filterRuleList;

					// Finding table...
					tempString.assign("GEN-FILTDEFT-");
					tempString.append(filterRuleList->name);
					tempString.append("-TABLE");
					errorCode = device->addTable(paragraphPointer, tempString.c_str());
					if (errorCode != 0)
						return errorCode;
					tempString.assign(filterListNameTitle);
					tempString.append(" ");
					tempString.append(filterRuleList->name);
					tempString.append(" ");
					tempString.append(denyAndNotLogTable);
					paragraphPointer->table->title.assign(tempString);

					// Table titles...
					addFilterTableHeadings(device, paragraphPointer, filterIssuePointer->filterRuleList);
				}

				addFilterTableRow(device, paragraphPointer, filterIssuePointer->filter, filterIssuePointer->filterRuleList);
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue impact...
			if (device->isFirewall == true)
				securityIssuePointer->impactRating = 3;			// Low
			else
				securityIssuePointer->impactRating = 2;			// Informational
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			device->addString(paragraphPointer, filterName);
			device->addString(paragraphPointer, filterListName);
			device->addString(paragraphPointer, filterListName);
			device->addString(paragraphPointer, filterName);
			paragraphPointer->paragraph.assign(i18n("Although a *DATA* configured to accept a ports default action is not a direct threat to security, it makes the *DATA* configuration more difficult to administer. This is made more difficult in situations where a *DATA* has been applied to multiple network ports. This could lead to *DATA* unintentionally allowing network traffic."));

			// Issue ease...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			securityIssuePointer->easeRating = 0;				// N/A
			paragraphPointer->paragraph.assign(i18n("The access attempts would default to the filtering action applied to the port."));

			// Issue recommendation...
			securityIssuePointer->fixRating = 3;				// Trivial
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, where possible, all *DATA* should be reconfigured to not default to the filtering action of the port."));

			// Conclusions text...
			securityIssuePointer->conLine.assign(defaultFilterCon);

			// Recommendation list text...
			device->addRecommendation(securityIssuePointer, defaultFilterRec, true);
		}


		if (filterNoComment != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Not All Filtering Rules Are Commented\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			securityIssuePointer->title.assign(filtersWithNoCommentsTitle);
			securityIssuePointer->reference.assign("GEN.FILTCOMM.1");

			tempCount = 0;
			filterIssuePointer = filterNoComment;
			while (filterIssuePointer != 0)
			{
				tempCount++;
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue finding...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addString(paragraphPointer, filterNamePlaural);
			device->addString(paragraphPointer, filterName);
			device->addString(paragraphPointer, filterName);
			device->addString(paragraphPointer, filterName);
			device->addString(paragraphPointer, filterNamePlaural);
			device->addString(paragraphPointer, filterName);
			paragraphPointer->paragraph.assign(i18n("It is common for *DATA* to initially be configured to allow access to a limited number of services and hosts and gradually grow over time as the business evolves and access to additional services or hosts are required. When access to a service is no longer required that related *DATA* should be modified or removed. However, without adequate tracking or change control, it may not be clear as to which *DATA* applied to that service so the *DATA* is not modified. In order to aid the clarity of *DATA* on *DEVICETYPE* devices, comment text can the included. The comment text is helpful in indicating why the *DATA* exists."));
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addValue(paragraphPointer, tempCount);
			if (tempCount > 1)
			{
				device->addString(paragraphPointer, filterNamePlaural);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* were configured with no comment text. These are listed below."));
			}
			else
			{
				device->addString(paragraphPointer, filterName);
				device->addString(paragraphPointer, filterName);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* was configured with no comment text, this *DATA* is shown in Table *TABLEREF*."));
			}

			// Table data...
			filterIssuePointer = filterNoComment;
			filterRuleList = 0;
			while (filterIssuePointer != 0)
			{

				if (filterRuleList != filterIssuePointer->filterRuleList)
				{
					if (filterRuleList != 0)
						paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

					filterRuleList = filterIssuePointer->filterRuleList;

					// Finding table...
					tempString.assign("GEN-FILTCOMM-");
					tempString.append(filterRuleList->name);
					tempString.append("-TABLE");
					errorCode = device->addTable(paragraphPointer, tempString.c_str());
					if (errorCode != 0)
						return errorCode;
					tempString.assign(filterListNameTitle);
					tempString.append(" ");
					tempString.append(filterRuleList->name);
					tempString.append(i18n(" have no comment text"));
					paragraphPointer->table->title.assign(tempString);

					// Table titles...
					addFilterTableHeadings(device, paragraphPointer, filterIssuePointer->filterRuleList);
				}

				addFilterTableRow(device, paragraphPointer, filterIssuePointer->filter, filterIssuePointer->filterRuleList);
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue impact...
			if (device->isFirewall == true)
				securityIssuePointer->impactRating = 2;			// Informational
			else
				securityIssuePointer->impactRating = 1;			// Informational
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			device->addString(paragraphPointer, filterName);
			device->addString(paragraphPointer, filterListNamePlaural);
			device->addString(paragraphPointer, filterNamePlaural);
			device->addString(paragraphPointer, filterListName);
			device->addString(paragraphPointer, filterName);
			paragraphPointer->paragraph.assign(i18n("Although not a direct threat to security, without comment text for each *DATA*, their purpose can be unclear and make the administration of *DATA* more difficult. This can lead to a situation where *DATA* that are no longer required remain configured, giving an attacker additional access."));

			// Issue ease...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			securityIssuePointer->easeRating = 0;				// N/A
			device->addString(paragraphPointer, filterName);
			device->addString(paragraphPointer, filterName);
			paragraphPointer->paragraph.assign(i18n("With no *DATA* comment text, administration is made more difficult as the purpose of the *DATA* may be unclear."));

			// Issue recommendation...
			securityIssuePointer->fixRating = 3;				// Trivial
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			device->addString(paragraphPointer, filterNamePlaural);
			device->addString(paragraphPointer, filterName);
			paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that all *DATA* should have comment text indicating the purpose of the *DATA*."));
			if (strlen(configureFilterCommentText) > 0)
			{
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
				paragraphPointer->paragraph.assign(configureFilterCommentText);
			}

			// Conclusions text...
			securityIssuePointer->conLine.assign(noFilterCommentsCon);

			// Recommendation list text...
			device->addRecommendation(securityIssuePointer, noFilterCommentsRec, true);
		}


		if (filterDisabled != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Disabled Filtering Rules Are Configured\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			securityIssuePointer->title.assign(disabledFiltersTitle);
			securityIssuePointer->reference.assign("GEN.FILTDISA.1");

			tempCount = 0;
			filterIssuePointer = filterDisabled;
			while (filterIssuePointer != 0)
			{
				tempCount++;
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue finding...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addString(paragraphPointer, filterNamePlaural);
			device->addString(paragraphPointer, filterNamePlaural);
			device->addString(paragraphPointer, filterListName);
			paragraphPointer->paragraph.assign(i18n("On *DEVICETYPE* devices *DATA* can be disabled. This feature is useful for administrators who simply want to disable access to a service temporarily. This could be used for diagnostic purposes or to disable a which is planned to be re-activated again in the immediate future. However, disabled *DATA* should not remain indefinately and can make the *DATA* configuration unclear to network administrators."));
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addValue(paragraphPointer, tempCount);
			if (tempCount > 1)
			{
				device->addString(paragraphPointer, filterNamePlaural);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* were disabled. These are listed below."));
			}
			else
			{
				device->addString(paragraphPointer, filterName);
				device->addString(paragraphPointer, filterName);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* was disabled, this *DATA* is shown in Table *TABLEREF*."));
			}

			// Table data...
			filterIssuePointer = filterDisabled;
			filterRuleList = 0;
			while (filterIssuePointer != 0)
			{

				if (filterRuleList != filterIssuePointer->filterRuleList)
				{
					if (filterRuleList != 0)
						paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

					filterRuleList = filterIssuePointer->filterRuleList;

					// Finding table...
					tempString.assign("GEN-FILTDISA-");
					tempString.append(filterRuleList->name);
					tempString.append("-TABLE");
					errorCode = device->addTable(paragraphPointer, tempString.c_str());
					if (errorCode != 0)
						return errorCode;
					tempString.assign(filterListNameTitle);
					tempString.append(" ");
					tempString.append(filterRuleList->name);
					tempString.append(i18n(" contains disabled "));
					tempString.append(filterNamePlaural);
					paragraphPointer->table->title.assign(tempString);

					// Table titles...
					addFilterTableHeadings(device, paragraphPointer, filterIssuePointer->filterRuleList);
				}

				addFilterTableRow(device, paragraphPointer, filterIssuePointer->filter, filterIssuePointer->filterRuleList);
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue impact...
			if (device->isFirewall == true)
				securityIssuePointer->impactRating = 2;			// Informational
			else
				securityIssuePointer->impactRating = 1;			// Informational
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			device->addString(paragraphPointer, filterNamePlaural);
			device->addString(paragraphPointer, filterNamePlaural);
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("Although not a direct threat to security, disabled *DATA* can make network administration more difficult. This could lead to *DATA* being configured that duplicate disabled *DATA*."));

			// Issue ease...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			securityIssuePointer->easeRating = 0;				// N/A
			device->addString(paragraphPointer, filterName);
			device->addString(paragraphPointer, filterListName);
			paragraphPointer->paragraph.assign(i18n("Disabled *DATA* could potentially lead to mistakes with the *DATA* configuration."));

			// Issue recommendation...
			securityIssuePointer->fixRating = 3;				// Trivial
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if not required, all disabled *DATA* should be removed."));
			if (strlen(removeFilterText) > 0)
			{
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
				paragraphPointer->paragraph.assign(removeFilterText);
			}

			// Conclusions text...
			securityIssuePointer->conLine.assign(disabledFilterCon);

			// Recommendation list text...
			device->addRecommendation(securityIssuePointer, disabledFilterRec, true);
		}


		if (filterClearText != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Filtering Rules Allow Access To Clear Text Services\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			securityIssuePointer->title.assign(i18n("Access Allowed To Clear Text Protocol Services"));
			securityIssuePointer->reference.assign("GEN.FILTCLEA.1");

			tempCount = 0;
			filterIssuePointer = filterClearText;
			while (filterIssuePointer != 0)
			{
				tempCount++;
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue finding...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			paragraphPointer->paragraph.assign(i18n("Clear text protocol services are services that provide no encryption of the network traffic between the service and a connected client. A clear text protocol services could be used to provide specific information that has little impact on security, but some services are used for remote administration and authentication."));
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addValue(paragraphPointer, tempCount);
			if (tempCount > 1)
			{
				device->addString(paragraphPointer, filterNamePlaural);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* were configured to allow access to network ports that are commonly used to provide a service that makes use of a clear text protocol. These are listed below."));
			}
			else
			{
				device->addString(paragraphPointer, filterName);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* was configured to allow access to network ports that are commonly used to provide a service that makes use of a clear text protocol, this is shown in Table *TABLEREF*."));
			}

			// Table data...
			filterIssuePointer = filterClearText;
			filterRuleList = 0;
			while (filterIssuePointer != 0)
			{

				if (filterRuleList != filterIssuePointer->filterRuleList)
				{
					if (filterRuleList != 0)
						paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

					filterRuleList = filterIssuePointer->filterRuleList;

					// Finding table...
					tempString.assign("GEN-FILTCLEA-");
					tempString.append(filterRuleList->name);
					tempString.append("-TABLE");
					errorCode = device->addTable(paragraphPointer, tempString.c_str());
					if (errorCode != 0)
						return errorCode;
					tempString.assign(filterListNameTitle);
					tempString.append(" ");
					tempString.append(filterRuleList->name);
					tempString.append(" ");
					tempString.append(i18n("permits access to clear text services"));
					paragraphPointer->table->title.assign(tempString);

					// Table titles...
					addFilterTableHeadings(device, paragraphPointer, filterIssuePointer->filterRuleList);
				}

				addFilterTableRow(device, paragraphPointer, filterIssuePointer->filter, filterIssuePointer->filterRuleList);
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue impact...
			if (device->isFirewall == true)
				securityIssuePointer->impactRating = 9;			// Critical
			else
				securityIssuePointer->impactRating = 5;			// Medium
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			paragraphPointer->paragraph.assign(i18n("Due to a lack of encryption, an attacker who is able to monitor a clear text protocol service would gain access to the information transmitted. The information could include the authentication credentials used to access the service or any other information transferred. Furthermore, some of the services could be used for remote administration and once accessed could be used to attack other devices on the network, bypassing any configured network filtering. Additionally, clear text protocol services are vulnerable to man in the middle style attack."));

			// Issue ease...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			securityIssuePointer->easeRating = 5;				// Moderate
			paragraphPointer->paragraph.assign(i18n("An attacker or a malicious user would have to be able to monitor a connection between the clear text protocol service and client in order to exploit this issue. The attacker could be able to monitor the connection if they attached to a network hub or were able to control the routing at any point. Tools are available on the Internet that can modify network routing and monitor network traffic. Some tools are specifically designed to extract sensitive information, such as authentication credentials and messages, directly from the network traffic."));

			// Issue recommendation...
			securityIssuePointer->fixRating = 6;				// Planned
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, where possible, all clear text protocol services should be replaced with cryptographic alternatives. Additionally, *COMPANY* recommends that *DATA* should be configured to prevent access to clear text protocol services."));
			if (strlen(configureFilterRecIssueText) > 0)
			{
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
				paragraphPointer->paragraph.assign(configureFilterRecIssueText);
			}

			// Conclusions text...
			securityIssuePointer->conLine.assign(clearTextServiceCon);

			// Recommendation list text...
			device->addRecommendation(securityIssuePointer, i18n("Replace all clear text protocol services with cryptographic alternatives"), true);
			device->addRecommendation(securityIssuePointer, clearTextServiceRec, true);
		}


		if (filterDangerous != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Filtering Rules Allow Access To Potentially Dangerous Services\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			securityIssuePointer->title.assign(i18n("Access Allowed To Potentially Dangerous Services"));
			securityIssuePointer->reference.assign("GEN.FILTDANG.1");

			tempCount = 0;
			filterIssuePointer = filterDangerous;
			while (filterIssuePointer != 0)
			{
				tempCount++;
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue finding...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			paragraphPointer->paragraph.assign(i18n("Some services provide little in that way of information and remote access to devices, whilst others are designed to provide a high level of access. These could be administrative services that enable a remote administrator to configure various settings, file services or database services that are used to store sensitive and business critical information. It is potentially dangerous to offer access to those service regardless of any authentication and protection mechanisms that the services offer."));

			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addValue(paragraphPointer, tempCount);
			if (tempCount > 1)
			{
				device->addString(paragraphPointer, filterNamePlaural);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* were configured to allow access to potentially dangerous services. These are listed below."));
			}
			else
			{
				device->addString(paragraphPointer, filterName);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* was configured to allow access to potentially dangerous services, this is shown in Table *TABLEREF*."));
			}

			// Table data...
			filterIssuePointer = filterDangerous;
			filterRuleList = 0;
			while (filterIssuePointer != 0)
			{

				if (filterRuleList != filterIssuePointer->filterRuleList)
				{
					if (filterRuleList != 0)
						paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

					filterRuleList = filterIssuePointer->filterRuleList;

					// Finding table...
					tempString.assign("GEN-FILTDANG-");
					tempString.append(filterRuleList->name);
					tempString.append("-TABLE");
					errorCode = device->addTable(paragraphPointer, tempString.c_str());
					if (errorCode != 0)
						return errorCode;
					tempString.assign(filterListNameTitle);
					tempString.append(" ");
					tempString.append(filterRuleList->name);
					tempString.append(" ");
					tempString.append(i18n("permit access to dangerous services"));
					paragraphPointer->table->title.assign(tempString);

					// Table titles...
					addFilterTableHeadings(device, paragraphPointer, filterIssuePointer->filterRuleList);
				}

				addFilterTableRow(device, paragraphPointer, filterIssuePointer->filter, filterIssuePointer->filterRuleList);
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue impact...
			if (device->isFirewall == true)
				securityIssuePointer->impactRating = 7;			// High
			else
				securityIssuePointer->impactRating = 4;			// Low
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			paragraphPointer->paragraph.assign(i18n("By their nature, these services offer a high level of access or are used to store potentially sensitive and business critical information. If an attacker or malicious user is able to identify any vulnerabilities in these services, or is able to determine the authentication credentials to gain access, they could pose a significant security threat."));

			// Issue ease...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			securityIssuePointer->easeRating = 5;				// Moderate
			paragraphPointer->paragraph.assign(i18n("Tools are available on the Internet that can exploit vulnerabilities in a range of administrative and database services. Tools are also available that can brute force authentication credentials, or attempt to monitor connections to the services with a man in the middle attack. However, it is also worth noting that often the security provided by well maintained services can provide a significant barrier to an attacker who may not be able to gain access without authentication credentials or knowledge of a specific zero day vulnerability."));

			// Issue recommendation...
			securityIssuePointer->fixRating = 5;				// Planned
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, where possible, access to all potentially dangerous services should be prevented by suitably restrictive *DATA*."));
			if (strlen(configureFilterRecIssueText) > 0)
			{
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
				paragraphPointer->paragraph.assign(configureFilterRecIssueText);
			}

			// Conclusions text...
			securityIssuePointer->conLine.assign(i18n("access was permitted to potentially dangerous services"));

			// Recommendation list text...
			device->addRecommendation(securityIssuePointer, i18n("Restrict access to all potentially dangerous services"), true);
		}


		if (filterUnnecessary != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Filtering Rules Allow Access To Potentially Unnecessary Services\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			securityIssuePointer->title.assign(i18n("Access Allowed To Potentially Unnecessary Services"));
			securityIssuePointer->reference.assign("GEN.FILTUNNE.1");

			tempCount = 0;
			filterIssuePointer = filterUnnecessary;
			while (filterIssuePointer != 0)
			{
				tempCount++;
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue finding...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			paragraphPointer->paragraph.assign(i18n("A number of network services exist that provide little to no functionality. These potentially unnecessary services include:"));
			device->addListItem(paragraphPointer, i18n("the echo service that responds to anything that is sent to it"));
			device->addListItem(paragraphPointer, i18n("the discard service that ignores anything that is sent to it"));
			device->addListItem(paragraphPointer, i18n("the chargen service that responds with various repeating character sequences"));
			device->addListItem(paragraphPointer, i18n("the daytime service that responds with current time"));

			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addValue(paragraphPointer, tempCount);
			if (tempCount > 1)
			{
				device->addString(paragraphPointer, filterNamePlaural);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* were configured to allow access to potentially unnecessary services. These are listed below."));
			}
			else
			{
				device->addString(paragraphPointer, filterName);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* was configured to allow access to potentially unnecessary services, this is shown in Table *TABLEREF*."));
			}

			// Table data...
			filterIssuePointer = filterUnnecessary;
			filterRuleList = 0;
			while (filterIssuePointer != 0)
			{

				if (filterRuleList != filterIssuePointer->filterRuleList)
				{
					if (filterRuleList != 0)
						paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

					filterRuleList = filterIssuePointer->filterRuleList;

					// Finding table...
					tempString.assign("GEN-FILTUNNE-");
					tempString.append(filterRuleList->name);
					tempString.append("-TABLE");
					errorCode = device->addTable(paragraphPointer, tempString.c_str());
					if (errorCode != 0)
						return errorCode;
					tempString.assign(filterListNameTitle);
					tempString.append(" ");
					tempString.append(filterRuleList->name);
					tempString.append(" ");
					tempString.append(i18n("allows access to unnecessary services"));
					paragraphPointer->table->title.assign(tempString);

					// Table titles...
					addFilterTableHeadings(device, paragraphPointer, filterIssuePointer->filterRuleList);
				}

				addFilterTableRow(device, paragraphPointer, filterIssuePointer->filter, filterIssuePointer->filterRuleList);
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue impact...
			if (device->isFirewall == true)
				securityIssuePointer->impactRating = 2;			// Informational
			else
				securityIssuePointer->impactRating = 1;			// Informational
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			paragraphPointer->paragraph.assign(i18n("Each service running on a system increases the risk that a vulnerability is exposed, they consume system resources and they increase the footprint of a device, giving the attacker more information."));

			// Issue ease...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			securityIssuePointer->easeRating = 8;				// Easy
			paragraphPointer->paragraph.assign(i18n("Tools are available on the Internet that can query the services or use the services to help determine information about the device."));

			// Issue recommendation...
			securityIssuePointer->fixRating = 3;				// Trivial
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, where possible, all unnecessary services should be disabled. Furthermore, *COMPANY* recommends that *DATA* should be configured to prevent access to unnecessary services."));
			if (strlen(configureFilterRecIssueText) > 0)
			{
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
				paragraphPointer->paragraph.assign(configureFilterRecIssueText);
			}

			// Conclusions text...
			securityIssuePointer->conLine.assign(unnecessaryServiceCon);

			// Recommendation list text...
			device->addRecommendation(securityIssuePointer, i18n("Disable all services for which there is no business requirement"), true);
			device->addRecommendation(securityIssuePointer, unnecessaryServiceRec, true);
		}


		if (legacyLists != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Legacy Filtering Rule Lists Were Configured\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			securityIssuePointer->title.assign(i18n("Legacy Network Filtering Configured"));
			securityIssuePointer->reference.assign("GEN.FILTLEGA.1");

			// Issue finding...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			paragraphPointer->paragraph.assign(legacyIssueFinding);

			// Issue impact...
			securityIssuePointer->impactRating = 3;			// Low
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			paragraphPointer->paragraph.assign(legacyIssueImpact);

			// Issue ease...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			securityIssuePointer->easeRating = 0;			// N/A
			paragraphPointer->paragraph.assign(legacyIssueEase);

			// Issue recommendation...
			securityIssuePointer->fixRating = 4;			// Planned
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(legacyIssueRec);

			// Conclusions text...
			securityIssuePointer->conLine.assign(i18n("legacy network filtering was configured"));

			// Recommendation list text...
			device->addRecommendation(securityIssuePointer, i18n("Upgrade the network filtering configuration"), true);
		}


		// Default filtering action
		if ((device->config->checkFilterDefaultAllowAction == true) && (defaultFilterActionSupported == true) && (allowByDefault == true) && (filterList != 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Default Filtering Action Allows Access\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			securityIssuePointer->title.assign(defaultActionIssueTitle);
			securityIssuePointer->reference.assign("GEN.FILTDEAC.1");

			// Issue finding...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addString(paragraphPointer, filterListNamePlaural);
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("It is possible to configure a default action for the *DATA* on *DEVICETYPE* devices. This is then the action taken if no *DATA* match the network traffic. "));
			device->addString(paragraphPointer, filterNamePlaural);
			if (defaultActionIsAllow == true)
				paragraphPointer->paragraph.append(i18n("The default action on *DEVICETYPE* devices is to allow access to any traffic that does not match the *DATA*."));
			else
				paragraphPointer->paragraph.append(i18n("The default action on *DEVICETYPE* devices is to deny access to any traffic that does not match the *DATA*."));

			// Issue impact...
			if (device->isFirewall == true)
				securityIssuePointer->impactRating = 9;			// High
			else
				securityIssuePointer->impactRating = 5;			// Medium
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("If access is allowed when network traffic does not match the *DATA*, an attacker could be able to access a large number of services. This could allow an attacker unauthorised access to services which should be denied."));

			// Issue ease...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			securityIssuePointer->easeRating = 7;			// Easy
			paragraphPointer->paragraph.assign(i18n("Network service identification and scanning tools are available on the Internet. Furthermore, some automated scanning tools are designed to automatically identify service vulnerabilities or to enumerate information about the hosts and services."));

			// Issue recommendation...
			securityIssuePointer->fixRating = 4;			// Planned
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			device->addString(paragraphPointer, filterListName);
			device->addString(paragraphPointer, filterName);
			paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that the default *DATA* action should be set to deny network traffic when a *DATA* does not match."));
			if (strlen(configureDefaultActionText) > 0)
			{
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
				paragraphPointer->paragraph.assign(configureDefaultActionText);
			}

			// Conclusions text...
			securityIssuePointer->conLine.assign(defaultActionIssueCon);

			// Recommendation list text...
			device->addRecommendation(securityIssuePointer, defaultActionIssueRec, true);
		}


		if (filterUnused != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Unused Filter Rules Were Configured\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			securityIssuePointer->title.assign(unusedFiltersIssueTitle);
			securityIssuePointer->reference.assign("GEN.FILTUNUS.1");

			// Issue finding...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addString(paragraphPointer, filterNamePlaural);
			device->addString(paragraphPointer, filterName);
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("It is possible to configure *DATA* that will never be used. If a *DATA* prevents blocks all access, any *DATA* that follow will never be used due to a previous match."));

			tempCount = 0;
			filterIssuePointer = filterUnused;
			while (filterIssuePointer != 0)
			{
				tempCount++;
				filterIssuePointer = filterIssuePointer->next;
			}

			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addValue(paragraphPointer, tempCount);
			if (tempCount > 1)
			{
				device->addString(paragraphPointer, filterNamePlaural);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* were unused. These are listed below."));
			}
			else
			{
				device->addString(paragraphPointer, filterName);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* was unused, this is shown in Table *TABLEREF*."));
			}

			// Table data...
			filterIssuePointer = filterUnused;
			filterRuleList = 0;
			while (filterIssuePointer != 0)
			{

				if (filterRuleList != filterIssuePointer->filterRuleList)
				{
					if (filterRuleList != 0)
						paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

					filterRuleList = filterIssuePointer->filterRuleList;

					// Finding table...
					tempString.assign("GEN-FILTUNUS-");
					tempString.append(filterRuleList->name);
					tempString.append("-TABLE");
					errorCode = device->addTable(paragraphPointer, tempString.c_str());
					if (errorCode != 0)
						return errorCode;
					tempString.assign(filterListNameTitle);
					tempString.append(" ");
					tempString.append(filterRuleList->name);
					tempString.append(i18n(" are unused"));
					paragraphPointer->table->title.assign(tempString);

					// Table titles...
					addFilterTableHeadings(device, paragraphPointer, filterIssuePointer->filterRuleList);
				}

				addFilterTableRow(device, paragraphPointer, filterIssuePointer->filter, filterIssuePointer->filterRuleList);
				filterIssuePointer = filterIssuePointer->next;
			}

			// Issue impact...
			if (device->isFirewall == true)
				securityIssuePointer->impactRating = 2;			// Informational
			else
				securityIssuePointer->impactRating = 1;			// Informational
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			device->addString(paragraphPointer, filterNamePlaural);
			device->addString(paragraphPointer, filterListName);
			paragraphPointer->paragraph.assign(i18n("Although not a direct threat to security, the unused *DATA* serves no purpose and could lead to confusion when administering a *DATA*. The clarity of a *DATA* is paramount as it could lead to a configuration where access to services are overally permissive."));

			// Issue ease...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			securityIssuePointer->easeRating = 0;			// N/A
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("Unused *DATA* would not give an attacker any additional access unless they cause an administrator to make a mistake during configuration."));

			// Issue recommendation...
			securityIssuePointer->fixRating = 3;			// Trivial
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that all unused *DATA* should be removed."));
			if (strlen(removeFilterText) > 0)
			{
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
				paragraphPointer->paragraph.assign(removeFilterText);
			}

			// Conclusions text...
			securityIssuePointer->conLine.assign(unusedFiltersIssueCon);

			// Recommendation list text...
			device->addRecommendation(securityIssuePointer, unusedFiltersIssueRec, true);
		}


		if (denyAllAndLog != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Filter Rule List Does Not End With A Deny All And Log\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			securityIssuePointer->title.assign(denyAllLogIssueTitle);
			securityIssuePointer->reference.assign("GEN.FILTDAAL.1");

			// Issue finding...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addString(paragraphPointer, filterListName);
			device->addString(paragraphPointer, filterName);
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("If a *DATA* *DATA* does not match the specified allowed network traffic, it is important that the network traffic is blocked from reaching its destination. However, it is also important that all blocked network traffic is logged, so an attacker or malicious users attempt to enumerate network services can be recorded."));

			tempCount = 0;
			filterListIssuePointer = denyAllAndLog;
			while (filterListIssuePointer != 0)
			{
				tempCount++;
				filterListIssuePointer = filterListIssuePointer->next;
			}

			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addValue(paragraphPointer, tempCount);
			if (tempCount > 1)
			{
				device->addString(paragraphPointer, filterListNamePlaural);
				device->addString(paragraphPointer, filterName);
				device->addString(paragraphPointer, filterListNamePlaural);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* did not end with a deny all and log *DATA*. These *DATA* are listed below."));

				// Table data...
				filterListIssuePointer = denyAllAndLog;
				while (filterListIssuePointer != 0)
				{
					if (filterListIssuePointer->filterRuleList->globalFilter == true)
						tempString.assign("global zone");
					else if (!filterListIssuePointer->filterRuleList->listName.empty())
						tempString.assign(filterListIssuePointer->filterRuleList->listName);
					else if (!filterListIssuePointer->filterRuleList->to.empty())
					{
						tempString.assign(i18n("from zone "));
						tempString.append(filterListIssuePointer->filterRuleList->name);
						tempString.append(i18n(" to zone "));
						tempString.append(filterListIssuePointer->filterRuleList->to);
					}
					else
						tempString.assign(filterListIssuePointer->filterRuleList->name);
					device->addListItem(paragraphPointer, tempString.c_str());

					filterListIssuePointer = filterListIssuePointer->next;
				}
			}
			else
			{
				device->addString(paragraphPointer, filterListName);
				device->addString(paragraphPointer, filterName);
				if (denyAllAndLog->filterRuleList->globalFilter == true)
					tempString.assign("global zone");
				else if (!denyAllAndLog->filterRuleList->listName.empty())
					tempString.assign(denyAllAndLog->filterRuleList->listName);
				else if (!denyAllAndLog->filterRuleList->to.empty())
				{
					tempString.assign(i18n("from zone "));
					tempString.append(denyAllAndLog->filterRuleList->name);
					tempString.append(i18n(" to zone "));
					tempString.append(denyAllAndLog->filterRuleList->to);
				}
				else
					tempString.assign(denyAllAndLog->filterRuleList->name);
				device->addString(paragraphPointer, tempString.c_str());
				device->addString(paragraphPointer, filterListName);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* did not end with a deny all and log *DATA*. The *DATA* *DATA* does not end with a deny all and log."));
			}

			// Issue impact...
			if (device->isFirewall == true)
				securityIssuePointer->impactRating = 5;			// Medium
			else
				securityIssuePointer->impactRating = 3;			// Low
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			device->addString(paragraphPointer, filterNamePlaural);
			device->addString(paragraphPointer, filterListName);
			device->addString(paragraphPointer, filterListName);
			paragraphPointer->paragraph.assign(i18n("Although not a direct threat to security, the unused *DATA* serves no purpose and could lead to confusion when administering a *DATA*. The clarity of a *DATA* is paramount as it could lead to a configuration where access to services are overally permissive."));

			// Issue ease...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			securityIssuePointer->easeRating = 0;			// N/A
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("The access attempts would not be logged by *DEVICENAME*."));

			// Issue recommendation...
			securityIssuePointer->fixRating = 3;			// Trivial
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that all denied access should be logged."));
			if (strlen(denyAllLogConfigure) > 0)
			{
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
				paragraphPointer->paragraph.assign(denyAllLogConfigure);
			}

			// Conclusions text...
			securityIssuePointer->conLine.assign(denyAllLogIssueCon);

			// Recommendation list text...
			device->addRecommendation(securityIssuePointer, denyAllLogIssueRec, true);
		}


		if (filterDuplicate != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Overlapping Or Duplicate Filter Rules Were Configured\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			securityIssuePointer->title.assign(duplicateIssueTitle);
			securityIssuePointer->reference.assign("GEN.FILTDUPL.1");

			// Issue finding...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addString(paragraphPointer, filterNamePlaural);
			device->addString(paragraphPointer, filterName);
			device->addString(paragraphPointer, filterName);
			paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices process the *DATA* sequentially with the first *DATA* that matches the network traffic applying. It is possible to configure additional *DATA* after the one that matches the traffic that contradicts the original but will never apply."));

			tempCount = 0;
			contradictPointer = filterDuplicate;
			while (contradictPointer != 0)
			{
				tempCount++;
				contradictPointer = contradictPointer->next;
			}

			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addValue(paragraphPointer, tempCount);
			if (tempCount > 1)
			{
				device->addString(paragraphPointer, filterNamePlaural);
				device->addString(paragraphPointer, filterNamePlaural);
				device->addString(paragraphPointer, filterNamePlaural);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* were duplicated by other *DATA*. These *DATA* are listed below."));
			}
			else
			{
				device->addString(paragraphPointer, filterName);
				device->addString(paragraphPointer, filterNamePlaural);
				device->addString(paragraphPointer, filterName);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* was duplicated by other *DATA*. This *DATA* is shown below."));
			}

			// Table data...
			contradictPointer = filterDuplicate;
			while (contradictPointer != 0)
			{

				// Add new paragraph...
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

				// Create table...
				tempString.assign("GEN-FILTDUPL-");
				tempString.append(filterListTableTitle(contradictPointer->filterRuleList));
				tempString.append(device->intToString(contradictPointer->filter->number));
				tempString.append("-TABLE");
				errorCode = device->addTable(paragraphPointer, tempString.c_str());
				if (errorCode != 0)
					return errorCode;
				tempString.assign(filterListNameTextTitle(contradictPointer->filterRuleList));
				tempString.append(" ");
				tempString.append(duplicateIssueTable);
				tempString.append(" ");
				tempString.append(device->intToString(contradictPointer->filter->number));
				paragraphPointer->table->title.assign(tempString);

				// Create table headings...
				addFilterTableHeadings(device, paragraphPointer, contradictPointer->filterRuleList);

				// Output first filter line...
				addFilterTableRow(device, paragraphPointer, contradictPointer->filter, contradictPointer->filterRuleList);

				// Output contradicting lines...
				filterIssuePointer = contradictPointer->duplicates;
				while (filterIssuePointer != 0)
				{
					addFilterTableRow(device, paragraphPointer, filterIssuePointer->filter, contradictPointer->filterRuleList);
					filterIssuePointer = filterIssuePointer->next;
				}

				contradictPointer = contradictPointer->next;
			}

			// Issue impact...
			if (device->isFirewall == true)
				securityIssuePointer->impactRating = 5;			// Medium
			else
				securityIssuePointer->impactRating = 3;			// Low
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			device->addString(paragraphPointer, filterNamePlaural);
			device->addString(paragraphPointer, filterListName);
			device->addString(paragraphPointer, filterListName);
			paragraphPointer->paragraph.assign(i18n("Although not a direct threat to security, the duplicate *DATA* serves no purpose and could lead to confusion when administering a *DATA*. The clarity of a *DATA* is paramount as it could lead to a configuration where access to services are overally permissive."));

			// Issue ease...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			securityIssuePointer->easeRating = 0;			// N/A
			device->addString(paragraphPointer, filterName);
			paragraphPointer->paragraph.assign(i18n("The first *DATA* that matches the network traffic applies, all others are not used."));

			// Issue recommendation...
			securityIssuePointer->fixRating = 5;			// Planned
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			device->addString(paragraphPointer, filterNamePlaural);
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, where possible, all *DATA* should not duplicate other *DATA*."));

			// Conclusions text...
			securityIssuePointer->conLine.assign(duplicateIssueCon);

			// Recommendation list text...
			device->addRecommendation(securityIssuePointer, duplicateIssueRec, true);
		}


		if (filterContradict != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Contradicting Filter Rules Were Configured\n", device->config->COL_BLUE, device->config->COL_RESET);

			securityIssuePointer = device->addSecurityIssue();
			securityIssuePointer->title.assign(contradictIssueTitle);
			securityIssuePointer->reference.assign("GEN.FILTCONT.1");

			// Issue finding...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addString(paragraphPointer, filterNamePlaural);
			device->addString(paragraphPointer, filterName);
			device->addString(paragraphPointer, filterName);
			paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices process the *DATA* sequentially with the first *DATA* that matches the network traffic applying. It is possible to configure additional *DATA* after the one that matches the traffic that contradicts the original but will never apply."));

			tempCount = 0;
			contradictPointer = filterContradict;
			while (contradictPointer != 0)
			{
				tempCount++;
				contradictPointer = contradictPointer->next;
			}

			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			device->addValue(paragraphPointer, tempCount);
			if (tempCount > 1)
			{
				device->addString(paragraphPointer, filterNamePlaural);
				device->addString(paragraphPointer, filterNamePlaural);
				device->addString(paragraphPointer, filterNamePlaural);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* were contradicted by other *DATA*. These *DATA* are listed below."));
			}
			else
			{
				device->addString(paragraphPointer, filterName);
				device->addString(paragraphPointer, filterNamePlaural);
				device->addString(paragraphPointer, filterName);
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* *DATA* was contradicted by other *DATA*. This *DATA* is shown below."));
			}

			// Table data...
			contradictPointer = filterContradict;
			while (contradictPointer != 0)
			{

				// Add new paragraph...
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

				// Create table...
				tempString.assign("GEN-FILTCONT-");
				tempString.append(filterListTableTitle(contradictPointer->filterRuleList));
				tempString.append(device->intToString(contradictPointer->filter->number));
				tempString.append("-TABLE");
				errorCode = device->addTable(paragraphPointer, tempString.c_str());
				if (errorCode != 0)
					return errorCode;
				tempString.assign(filterListNameTextTitle(contradictPointer->filterRuleList));
				tempString.append(" ");
				tempString.append(contradictIssueTable);
				tempString.append(" ");
				tempString.append(device->intToString(contradictPointer->filter->number));
				paragraphPointer->table->title.assign(tempString);

				// Create table headings...
				addFilterTableHeadings(device, paragraphPointer, contradictPointer->filterRuleList);

				// Output first filter line...
				addFilterTableRow(device, paragraphPointer, contradictPointer->filter, contradictPointer->filterRuleList);

				// Output contradicting lines...
				filterIssuePointer = contradictPointer->duplicates;
				while (filterIssuePointer != 0)
				{
					addFilterTableRow(device, paragraphPointer, filterIssuePointer->filter, contradictPointer->filterRuleList);
					filterIssuePointer = filterIssuePointer->next;
				}

				contradictPointer = contradictPointer->next;
			}

			// Issue impact...
			if (device->isFirewall == true)
				securityIssuePointer->impactRating = 5;			// Medium
			else
				securityIssuePointer->impactRating = 3;			// Low
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
			device->addString(paragraphPointer, filterNamePlaural);
			device->addString(paragraphPointer, filterListName);
			device->addString(paragraphPointer, filterListName);
			paragraphPointer->paragraph.assign(i18n("Although not a direct threat to security, the contradictory *DATA* serves no purpose and could lead to confusion when administering a *DATA*. The clarity of a *DATA* is paramount as it could lead to a configuration where access to services are overally permissive."));

			// Issue ease...
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			securityIssuePointer->easeRating = 0;			// N/A
			device->addString(paragraphPointer, filterName);
			paragraphPointer->paragraph.assign(i18n("The first *DATA* that matches the network traffic applies, all others are not used."));

			// Issue recommendation...
			securityIssuePointer->fixRating = 5;			// Planned
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			device->addString(paragraphPointer, filterNamePlaural);
			device->addString(paragraphPointer, filterNamePlaural);
			paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, where possible, all *DATA* should not contradict other *DATA*."));

			// Conclusions text...
			securityIssuePointer->conLine.assign(contradictIssueCon);

			// Recommendation list text...
			device->addRecommendation(securityIssuePointer, contradictIssueRec, true);
		}


		if (weakLoggingLevel != 0)
		{
			if (device->config->reportFormat == Config::Debug)
				printf("    %s*%s [ISSUE] Filtering Rules Were Configured With Weak Logging\n", device->config->COL_BLUE, device->config->COL_RESET);
		}
	}

	errorCode = generateDeviceSpecificFilterSecurityIssues(device);

	return errorCode;
}


int Filter::generateDeviceSpecificFilterSecurityIssues(Device *device)
{
	return 0;
}


void Filter::recommendedFiltering(Device *device, Device::securityIssueStruct *securityIssue)
{
	// Variables...
	Device::paragraphStruct *paragraphPointer = 0;
	filterListConfig *filterListPointer = 0;
	bool sourceServiceSupported = false;
	bool loggingSupported = false;
	bool commentsSupported = false;
	bool disabledFiltersSupported = false;
	string tempString;

	// Determine which options are relevant...
	filterListPointer = filterList;
	while (filterListPointer != 0)
	{
		if (filterListPointer->sourceServiceSupported == true)
			sourceServiceSupported = true;
		if (filterListPointer->loggingSupport == true)
			loggingSupported = true;
		if (filterListPointer->filterCommentsSupported == true)
			commentsSupported = true;
		if (filterListPointer->disabledFilterSupport == true)
			disabledFiltersSupported = true;
		filterListPointer = filterListPointer->next;
	}

	paragraphPointer = device->addParagraph(securityIssue, Device::Recommendation);
	device->addString(paragraphPointer, filterListNamePlaural);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that *DATA* are configured to ensure that:"));

	// Source
	if (device->config->checkFilterForAnySource == true)
	{
		device->addString(paragraphPointer, filterName);
		device->addListItem(paragraphPointer, i18n("*DATA* do not allow access from any source"));
	}
	if (device->config->checkFilterForNetworkSource == true)
	{
		device->addString(paragraphPointer, filterName);
		device->addListItem(paragraphPointer, i18n("*DATA* do not allow access from a source network address"));
	}

	// Source Service
	if (sourceServiceSupported == true)
	{
		if (device->config->checkFilterForAnySourcePort == true)
		{
			device->addString(paragraphPointer, filterName);
			device->addListItem(paragraphPointer, i18n("*DATA* do not allow access from any source port"));
		}
		if (device->config->checkFilterForRangeSourcePort == true)
		{
			device->addString(paragraphPointer, filterName);
			device->addListItem(paragraphPointer, i18n("*DATA* do not allow access from a range of source ports"));
		}
	}

	// Destination
	if (device->config->checkFilterForAnyDestination == true)
	{
		device->addString(paragraphPointer, filterName);
		device->addListItem(paragraphPointer, i18n("*DATA* do not allow access to any destination"));
	}
	if (device->config->checkFilterForNetworkDestination == true)
	{
		device->addString(paragraphPointer, filterName);
		device->addListItem(paragraphPointer, i18n("*DATA* do not allow access to a destination network address"));
	}

	// Destination Service
	if (device->config->checkFilterForAnyDestinationPort == true)
	{
		device->addString(paragraphPointer, filterName);
		device->addListItem(paragraphPointer, i18n("*DATA* do not allow access to any destination service"));
	}
	if (device->config->checkFilterForRangeDestinationPort == true)
	{
		device->addString(paragraphPointer, filterName);
		device->addListItem(paragraphPointer, i18n("*DATA* do not allow access to a range of destination services"));
	}

	// Reject
	if ((rejectRulesSupported == true) && (device->config->checkFilterForRejectRules == true))
	{
		device->addString(paragraphPointer, filterName);
		device->addString(paragraphPointer, rejectName);
		device->addListItem(paragraphPointer, i18n("*DATA* do not *DATA* access"));
	}

	// Bypass
	if ((bypassRulesSupported == true) && (device->config->checkFilterForBypassRules == true))
	{
		device->addString(paragraphPointer, filterName);
		device->addListItem(paragraphPointer, i18n("*DATA* do not bypass"));
	}

	// Default
	if ((defaultRulesSupported == true) && (device->config->checkFilterForDefaultRules == true))
	{
		device->addString(paragraphPointer, filterName);
		device->addListItem(paragraphPointer, i18n("*DATA* do not use a ports default action"));
	}

	// Logging
	if (loggingSupported == true)
	{
		if (device->config->checkFilterForLogDeniedRules == true)
		{
			device->addString(paragraphPointer, filterName);
			device->addListItem(paragraphPointer, i18n("*DATA* log all denied access"));
		}
		if ((device->config->checkFilterLogsAllowedRules == true) && (logOnlyDenySupported == false))
		{
			device->addString(paragraphPointer, filterName);
			device->addListItem(paragraphPointer, i18n("*DATA* log all allowed access"));
		}
		if (device->config->checkFilterEndsWithDenyAllAndLog == true)
		{
			device->addString(paragraphPointer, filterListName);
			device->addListItem(paragraphPointer, i18n("*DATA* end with a deny all and log"));
		}
	}

	// Disabled Rules
	if ((disabledFiltersSupported == true) && (device->config->checkFilterForDisabledRules == true))
	{
		device->addString(paragraphPointer, filterName);
		device->addListItem(paragraphPointer, i18n("no disabled *DATA* exist"));
	}

	// Comments
	if ((commentsSupported == true) && (device->config->checkFilterForRulesWithoutComments == true))
	{
		device->addString(paragraphPointer, filterName);
		device->addListItem(paragraphPointer, i18n("all *DATA* are commented"));
	}

	// Clear Text Protocols
	if (device->config->checkFilterForClearTextRules == true)
	{
		device->addString(paragraphPointer, filterName);
		device->addListItem(paragraphPointer, i18n("*DATA* do not allow clear text protocol services"));
	}

	// Duplicate Rules
	if (device->config->checkFilterForDuplicateRules == true)
	{
		device->addString(paragraphPointer, filterName);
		device->addString(paragraphPointer, filterName);
		device->addListItem(paragraphPointer, i18n("*DATA* do not overlap or duplicate other *DATA*"));
	}

	// Contradicting Rules
	if (device->config->checkFilterForContradictRules == true)
	{
		device->addString(paragraphPointer, filterName);
		device->addString(paragraphPointer, filterName);
		device->addListItem(paragraphPointer, i18n("*DATA* do not contradict other *DATA*"));
	}

	// Unused Rules
	if (device->config->checkFilterForUnusedRulesAtListEnd == true)
	{
		device->addString(paragraphPointer, filterName);
		device->addListItem(paragraphPointer, i18n("no unused *DATA* exist"));
	}

	// Unused Rule Lists
	if ((ruleListsAreAssigned == true) && (device->config->checkFilterForUnusedRuleLists == true))
	{
		device->addString(paragraphPointer, filterListName);
		device->addListItem(paragraphPointer, i18n("no unused *DATA* exist"));
	}
}


int Filter::writeFilterSecurityIssue(Device *device, Device::securityIssueStruct *securityIssuePointer, filterIssueConfig *filterListIssues, const char *filterIssueFindingText, const char *tableReferenceText, const char *tableTitleText, int impactRating, const char *conclusionsText)
{
	// Variables...
	Device::paragraphStruct *paragraphPointer = 0;
	filterIssueConfig *filterIssuePointer = 0;
	filterListConfig *filterRuleList = 0;
	string tempString;
	int errorCode = 0;
	int tempCount = 0;
	int logCount = 0;

	tempCount = 0;
	filterIssuePointer = filterListIssues;
	while (filterIssuePointer != 0)
	{
		if (!((filterIssuePointer->filterRuleList->loggingSupport == true) && (logOnlyDenySupported == false) && (filterIssuePointer->filter->log == false)))
			logCount++;
		tempCount++;
		filterIssuePointer = filterIssuePointer->next;
	}

	// Issue finding...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	if (device->isFirewall == true)
		paragraphPointer->paragraph.append(i18n("The primary purpose is of *DEVICETYPE* devices is to be a security barrier, preventing unauthorised access to devices and services by filtering the network traffic. "));
	paragraphPointer->paragraph.append(i18n("The *DEVICETYPE* device network filtering can be configured to allow or deny access from specific network addresses to specific network addresses and services. Best practise dictates that only access to hosts and services should only be configured for those hosts that require access."));
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
	device->addValue(paragraphPointer, tempCount);
	if (tempCount > 1)
		device->addString(paragraphPointer, filterNamePlaural);
	else
		device->addString(paragraphPointer, filterName);
	paragraphPointer->paragraph.append(i18n("*COMPANY* determined that *NUMBER* *DATA* "));
	paragraphPointer->paragraph.append(filterIssueFindingText);

	// Table data...
	filterIssuePointer = filterListIssues;
	filterRuleList = 0;
	while (filterIssuePointer != 0)
	{

		if (filterRuleList != filterIssuePointer->filterRuleList)
		{
			if (filterRuleList != 0)
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

			filterRuleList = filterIssuePointer->filterRuleList;

			// Finding table...
			tempString.assign(tableReferenceText);
			tempString.append(filterRuleList->name);
			tempString.append("-TABLE");
			errorCode = device->addTable(paragraphPointer, tempString.c_str());
			if (errorCode != 0)
				return errorCode;
			tempString.assign(filterListNameTitle);
			tempString.append(" ");
			tempString.append(filterRuleList->name);
			tempString.append(" ");
			tempString.append(tableTitleText);
			paragraphPointer->table->title.assign(tempString);

			// Table titles...
			addFilterTableHeadings(device, paragraphPointer, filterIssuePointer->filterRuleList);
		}

		addFilterTableRow(device, paragraphPointer, filterIssuePointer->filter, filterIssuePointer->filterRuleList);
		filterIssuePointer = filterIssuePointer->next;
	}

	// Issue impact...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
	if (device->isFirewall == true)
		securityIssuePointer->impactRating = impactRating;
	else
		securityIssuePointer->impactRating = (unsigned int)round(impactRating / 2);
	device->addString(paragraphPointer, filterListName);
	paragraphPointer->paragraph.assign(i18n("A weak *DATA* configuration could allow a malicious user or an attacker to gain unauthorised access to network services."));
	if (logCount == 0)
		paragraphPointer->paragraph.append(i18n(" Furthermore, without logging configured to log access, the attackers access to the services may remain undetected."));
	else if (logCount < tempCount)
	{
		device->addString(paragraphPointer, filterNamePlaural);
		paragraphPointer->paragraph.append(i18n(" Furthermore, without logging configured to log access to all the *DATA*, the attackers access to the services may remain undetected."));
	}

	// Issue ease...
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
	securityIssuePointer->easeRating = 0;				// N/A
	paragraphPointer->paragraph.assign(i18n("With a weak network filtering configured, *DEVICENAME* would not prevent access to the network addresses and services detailed in the finding."));

	// Issue recommendation...
	securityIssuePointer->fixRating = 4;				// Planned
	paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
	device->addString(paragraphPointer, filterNamePlaural);
	paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, where possible, all *DATA* should configured to restrict access to network addresses and services from only those hosts that require access."));
	recommendedFiltering(device, securityIssuePointer);
	if (strlen(configureFilterListRecIssueText) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configureFilterListRecIssueText);
	}
	if (strlen(configureFilterRecIssueText) > 0)
	{
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(configureFilterRecIssueText);
	}

	// Conclusions text...
	securityIssuePointer->conLine.assign(conclusionsText);

	// Recommendation list text...
	device->addRecommendation(securityIssuePointer, i18n("Restrict access to services from only those hosts that require access"), true);

	// Related issues...
	if (allowedLogging != 0)
		device->addRelatedIssue(securityIssuePointer, "GEN.FILTALLO.1");

	return errorCode;
}


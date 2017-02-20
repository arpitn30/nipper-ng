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
#include "interfaces.h"
#include "../administration/administration.h"


int Interfaces::generateSecurityReport(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	interfaceListConfig *interfaceListPointer = 0;
	interfaceConfig *interfacePointer = 0;
	issueLinksConfig *issueLinksPointer = 0;
	bool inboundSupported = false;
	bool outboundSupported = false;
	string tempString;
	int count = 0;
	int errorCode = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s Interface Checks\n", device->config->COL_BLUE, device->config->COL_RESET);

	// Security Checks...
	interfaceListPointer = interfaceList;
	while (interfaceListPointer != 0)
	{

		// In/out filtering...
		if (interfaceListPointer->inboundFilterSupported == true)
			inboundSupported = true;
		if (interfaceListPointer->outboudFilterSupported == true)
			outboundSupported = true;

		interfacePointer = interfaceListPointer->interface;
		while (interfacePointer != 0)
		{
			if (interfacePointer->enabled == true)
			{

				// IP Directed Broadcasts
				if ((interfaceListPointer->ipDirectBroadcastSupported == true) && (strcmp(interfacePointer->ipDirectBroadcast.c_str(), i18n("Off")) != 0))
					addInterfaceIssue("GEN.INTEDIRE.1", interfaceListPointer, interfacePointer);

				// CDP
				if ((interfaceListPointer->cdpSupported == true) && (interfacePointer->cdp == true))
				{
					if ((cdpGlobalRequired == true) && (device->administration != 0))
					{
						if (device->administration->cdpEnabled == true)
							addInterfaceIssue("GEN.INTECDPE.1", interfaceListPointer, interfacePointer);
					}
					else
						addInterfaceIssue("GEN.INTECDPE.1", interfaceListPointer, interfacePointer);
				}

				// Filtering...
				if (((interfaceListPointer->inboundFilterSupported == true) && (interfacePointer->filterIn == 0)) || ((interfaceListPointer->outboudFilterSupported == true) && (interfacePointer->filterOut == 0)))
					addInterfaceIssue("GEN.INTEFILT.1", interfaceListPointer, interfacePointer);

				// Trunking...
				if ((interfaceListPointer->portModeSupported == true) && (interfacePointer->switchportMode != portModeAccess))
					addInterfaceIssue("GEN.INTETRUN.1", interfaceListPointer, interfacePointer);

				// Port Security...
				if ((interfaceListPointer->portSecuritySupported == true) && (interfacePointer->switchportSecurity == false))
					addInterfaceIssue("GEN.INTEPOSE.1", interfaceListPointer, interfacePointer);

				if  (!interfacePointer->address.empty())
				{

					// Proxy ARP
					if ((interfaceListPointer->proxyArpSupported == true) && (interfacePointer->proxyARP == true))
						addInterfaceIssue("GEN.INTEPARP.1", interfaceListPointer, interfacePointer);

					// Unreachables...
					if ((interfaceListPointer->unreachablesSupported == true) && (interfacePointer->ipUnreachables == true))
						addInterfaceIssue("GEN.INTEICUN.1", interfaceListPointer, interfacePointer);

					// Mask Reply...
					if ((interfaceListPointer->ipMaskReplySupported == true) && (interfacePointer->ipMaskReply == true))
						addInterfaceIssue("GEN.INTEMASK.1", interfaceListPointer, interfacePointer);

					// Redirects...
					if ((interfaceListPointer->redirectsSupported == true) && (interfacePointer->ipRedirects == true))
						addInterfaceIssue("GEN.INTEREDI.1", interfaceListPointer, interfacePointer);

					// Information Reply...
					if ((interfaceListPointer->informationReplySupported == true) && (interfacePointer->infoReply == true))
						addInterfaceIssue("GEN.INTEINFO.1", interfaceListPointer, interfacePointer);

					// MOP...
					if ((interfaceListPointer->mopSupported == true) && (interfacePointer->mop == true))
						addInterfaceIssue("GEN.INTEMOPE.1", interfaceListPointer, interfacePointer);
				}
				else
				{
					if ((interfaceListPointer->interfaceDisableSupport == true) && (interfaceListPointer->ipAddressSupported == true))
						addInterfaceIssue("GEN.INTEACTI.1", interfaceListPointer, interfacePointer);
					else if ((interfaceListPointer->interfaceDisableSupport == true) && (interfacePointer->vlan == 0) && (interfaceListPointer->vlanSupported == true))
						addInterfaceIssue("GEN.INTEACTI.1", interfaceListPointer, interfacePointer);
				}
			}
			interfacePointer = interfacePointer->next;
		}

		interfaceListPointer = interfaceListPointer->next;
	}


	if (cdpIssues != 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] CDP Enabled On Interfaces\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		if (cdpIssues->next != 0)
			securityIssuePointer->title.assign(i18n("*ABBREV*CDP*-ABBREV* Was Enabled On Multiple Interfaces"));
		else
			securityIssuePointer->title.assign(i18n("*ABBREV*CDP*-ABBREV* Was Enabled On An Interface"));
		securityIssuePointer->reference.assign("GEN.INTECDPE.1");

		count = 0;
		issueLinksPointer = cdpIssues;
		while (issueLinksPointer != 0)
		{
			count++;
			issueLinksPointer = issueLinksPointer->next;
		}

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*ABBREV*CDP*-ABBREV* is a proprietary protocol that was developed and is primarily used by Cisco. A *ABBREV*CDP*-ABBREV* enabled device can be configured to broadcast *ABBREV*CDP*-ABBREV* packets on the network enabling network management applications and *ABBREV*CDP*-ABBREV* aware devices to identify each other. *ABBREV*CDP*-ABBREV* packets include information about the sender, such as *ABBREV*OS*-ABBREV* version and *ABBREV*IP*-ABBREV* address information."));
		if (cdpGlobalRequired == true)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			paragraphPointer->paragraph.assign(i18n("On *DEVICETYPE* devices *ABBREV*CDP*-ABBREV* is enabled and disabled for the entire device and on individual interfaces. If *ABBREV*CDP*-ABBREV* is enabled on the device, it can be disabled for each interfaces that it is not required. If it is disabled on the device, then it is disabled for all interfaces as well."));
		}
		else
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			paragraphPointer->paragraph.assign(i18n("On *DEVICETYPE* devices *ABBREV*CDP*-ABBREV* is enabled and disabled on individual interfaces."));
		}
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addValue(paragraphPointer, count);
		if (cdpIssues->next != 0)
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *ABBREV*CDP*-ABBREV* was enabled on *NUMBER* interfaces. These are listed below."));
		else
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *ABBREV*CDP*-ABBREV* was enabled on *NUMBER* interface. This is detailed below."));

		interfaceListPointer = 0;
		issueLinksPointer = cdpIssues;
		while (issueLinksPointer != 0)
		{
			if (interfaceListPointer != issueLinksPointer->interfaceList)
			{
				interfaceListPointer = issueLinksPointer->interfaceList;

				// Init pointers...
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

				// Create Table...
				tempString.assign("SEC-CDP");
				tempString.append(interfaceListPointer->label);
				tempString.append("-TABLE");
				errorCode = device->addTable(paragraphPointer, tempString.c_str());
				if (errorCode != 0)
					return errorCode;
				tempString.assign(interfaceListPointer->tableTitle);
				tempString.append(i18n(" with *ABBREV*CDP*-ABBREV* enabled"));
				paragraphPointer->table->title.assign(tempString);

				outputInterfaceTableHeadings(device, interfaceListPointer, paragraphPointer);
			}
			outputInterfaceTableRow(device, interfaceListPointer, issueLinksPointer->interface, paragraphPointer);

			issueLinksPointer = issueLinksPointer->next;
		}
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		outputInterfaceTableExplain(device, interfaceListPointer, paragraphPointer);

		// Issue impact...
		securityIssuePointer->impactRating = 4;			// LOW
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("*ABBREV*CDP*-ABBREV* packets contain information about the sender, such as hardware model information, operating system version and *ABBREV*IP*-ABBREV* address details. This information would give an attacker valuable information about the *DEVICE*. The attacker could then use this information as part of a targetted attack."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 7;				// Easy
		paragraphPointer->paragraph.assign(i18n("*ABBREV*CDP*-ABBREV* packets are broadcast to an entire network segment. The attacker or malicious user would require access to a network segment on which the *ABBREV*CDP*-ABBREV* packets are broadcast and network monitoring software. A wide variety of network monitoring, packet capture and analysis tools are available on the Internet."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 3;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if not required, *ABBREV*CDP*-ABBREV* should be completely disabled. If *ABBREV*CDP*-ABBREV* is required, *COMPANY* recommends that *ABBREV*CDP*-ABBREV* should be disabled on all interfaces except those that are explicitly required."));
		if (strlen(disableCDPText) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(disableCDPText);
		}
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("In some configurations with *ABBREV*IP*-ABBREV* phones, deployed using either Auto Discovery or *ABBREV*DHCP*-ABBREV*, the *ABBREV*CDP*-ABBREV* service may need to be enabled. In this situation *ABBREV*CDP*-ABBREV* should be disabled on all interfaces for which it is not required."));

		// Conclusions text...
		if (cdpIssues->next != 0)
			securityIssuePointer->conLine.append(i18n("*ABBREV*CDP*-ABBREV* was enabled on multiple interfaces"));
		else
			securityIssuePointer->conLine.append(i18n("*ABBREV*CDP*-ABBREV* was enabled on an interface"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Disable *ABBREV*CDP*-ABBREV*"), true);
	}


	if (proxyARPIssues != 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Proxy ARP Enabled\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("Proxy *ABBREV*ARP*-ABBREV* Was Enabled"));
		securityIssuePointer->reference.assign("GEN.INTEPARP.1");

		count = 0;
		issueLinksPointer = proxyARPIssues;
		while (issueLinksPointer != 0)
		{
			count++;
			issueLinksPointer = issueLinksPointer->next;
		}

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*ABBREV*ARP*-ABBREV* is a protocol that network hosts use to translate network addresses into media addresses. Under normal circumstances, *ABBREV*ARP*-ABBREV* packets are confined to the sender's network segment. However, a *DEVICETYPE* device with Proxy *ABBREV*ARP*-ABBREV* enabled on network interfaces can act as a proxy for *ABBREV*ARP*-ABBREV*, responding to queries and acting as an intermediary."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addValue(paragraphPointer, count);
		if (proxyARPIssues->next != 0)
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that proxy *ABBREV*ARP*-ABBREV* was enabled on *NUMBER* interfaces. These are listed below."));
		else
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that proxy *ABBREV*ARP*-ABBREV* was enabled on *NUMBER* interface. This is detailed below."));

		interfaceListPointer = 0;
		issueLinksPointer = proxyARPIssues;
		while (issueLinksPointer != 0)
		{
			if (interfaceListPointer != issueLinksPointer->interfaceList)
			{
				interfaceListPointer = issueLinksPointer->interfaceList;

				// Init pointers...
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

				// Create Table...
				tempString.assign("SEC-ARP");
				tempString.append(interfaceListPointer->label);
				tempString.append("-TABLE");
				errorCode = device->addTable(paragraphPointer, tempString.c_str());
				if (errorCode != 0)
					return errorCode;
				tempString.assign(interfaceListPointer->tableTitle);
				tempString.append(i18n(" with proxy *ABBREV*ARP*-ABBREV* enabled"));
				paragraphPointer->table->title.assign(tempString);

				outputInterfaceTableHeadings(device, interfaceListPointer, paragraphPointer);
			}
			outputInterfaceTableRow(device, interfaceListPointer, issueLinksPointer->interface, paragraphPointer);

			issueLinksPointer = issueLinksPointer->next;
		}
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		outputInterfaceTableExplain(device, interfaceListPointer, paragraphPointer);

		// Issue impact...
		securityIssuePointer->impactRating = 3;			// LOW
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("A router that acts as a proxy for *ABBREV*ARP*-ABBREV* requests will extend layer two access across multiple network segments, breaking perimeter security."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 7;				// Easy
		paragraphPointer->paragraph.assign(i18n("A *DEVICETYPE* device with proxy *ABBREV*ARP*-ABBREV* enabled will proxy *ABBREV*ARP*-ABBREV* requests for all hosts on those interfaces. A number of *ABBREV*ARP*-ABBREV* tools are available on the Internet."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 2;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if not required, proxy *ABBREV*ARP*-ABBREV* should be disabled on all interfaces."));
		if (strlen(disableProxyARPText) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(disableProxyARPText);
		}

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("*DEVICENAME* was configured to proxy *ABBREV*APP*-ABBREV* requests"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Disable proxy *ABBREV*ARP*-ABBREV* on all interfaces"), true);	
	}


	if ((unreachableIssues != 0) || ((globalIPUnreachableSupported == true) && (globalUnreachableEnabled == true)))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] ICMP Unreachable Messages Enabled\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("*ABBREV*ICMP*-ABBREV* Unreachable Messages Were Enabled"));
		securityIssuePointer->reference.assign("GEN.INTEICUN.1");

		if (globalIPUnreachableSupported == false)
		{
			count = 0;
			issueLinksPointer = unreachableIssues;
			while (issueLinksPointer != 0)
			{
				count++;
				issueLinksPointer = issueLinksPointer->next;
			}
		}

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices are capable of sending *ABBREV*ICMP*-ABBREV* unreachable messages to hosts. When enabled, a host attempting to access a service which is not available on *DEVICENAME* will be sent a *ABBREV*ICMP*-ABBREV* unreachable message. Likewise, if a network packet is recieved for a host that the device does not know how to reach, a *ABBREV*ICMP*-ABBREV* host unreachable message will be returned."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		if (globalIPUnreachableSupported == true)
		{
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *DEVICENAME* was configured to send *ABBREV*ICMP*-ABBREV* unreachable messages."));
		}
		else
		{
			device->addValue(paragraphPointer, count);
			if (unreachableIssues->next != 0)
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* interfaces were configured to send *ABBREV*ICMP*-ABBREV* unreachable messages. These are listed below."));
			else
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* interface was configured to send *ABBREV*ICMP*-ABBREV* unreachable messages. This is detailed below."));

			interfaceListPointer = 0;
			issueLinksPointer = unreachableIssues;
			while (issueLinksPointer != 0)
			{
				if (interfaceListPointer != issueLinksPointer->interfaceList)
				{
					interfaceListPointer = issueLinksPointer->interfaceList;

					// Init pointers...
					paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

					// Create Table...
					tempString.assign("SEC-UNREACH");
					tempString.append(interfaceListPointer->label);
					tempString.append("-TABLE");
					errorCode = device->addTable(paragraphPointer, tempString.c_str());
					if (errorCode != 0)
						return errorCode;
					tempString.assign(interfaceListPointer->tableTitle);
					tempString.append(i18n(" with *ABBREV*ICMP*-ABBREV* unreachables enabled"));
					paragraphPointer->table->title.assign(tempString);

					outputInterfaceTableHeadings(device, interfaceListPointer, paragraphPointer);
				}
				outputInterfaceTableRow(device, interfaceListPointer, issueLinksPointer->interface, paragraphPointer);

				issueLinksPointer = issueLinksPointer->next;
			}
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			outputInterfaceTableExplain(device, interfaceListPointer, paragraphPointer);
		}

		// Issue impact...
		securityIssuePointer->impactRating = 3;			// LOW
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("An attacker who was performing network scans to determine what services were available would be able to scan a device more quickly. If the device being scanned sends *ABBREV*ICMP*-ABBREV* unreachable messages, informing the attacker that a network or protocol is not supported, the attacker will not have to wait for a connection time-out."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 0;				// N/A
		paragraphPointer->paragraph.assign(i18n("The *ABBREV*ICMP*-ABBREV* messages are automatically returned by *DEVICETYPE* devices. Network scanning tools are available on the Internet that can perform a wide variety of scan types and take into account *ABBREV*ICMP*-ABBREV* unreachable messages."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 2;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("COMPANY* recommends that, if not required, *ABBREV*ICMP*-ABBREV* unreachable messages should be disabled. However, it is important to note that whilst disabling of *ABBREV*ICMP*-ABBREV* unreachable messages will not stop scans, it will make it more time consuming for an attacker to perform network scans."));
		if (strlen(disableUnreachablesText) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(disableUnreachablesText);
		}

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("*ABBREV*ICMP*-ABBREV* unreachable messages were enabled"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Disable the sending of *ABBREV*ICMP*-ABBREV* unreachable messages"), true);	
	}


	if (informationReplyIssues != 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] ICMP Information Reply Messages Enabled\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("*ABBREV*ICMP*-ABBREV* Information Reply Messages Were Enabled"));
		securityIssuePointer->reference.assign("GEN.INTEINFO.1");

		count = 0;
		issueLinksPointer = informationReplyIssues;
		while (issueLinksPointer != 0)
		{
			count++;
			issueLinksPointer = issueLinksPointer->next;
		}

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices are capable of responding to *ABBREV*ICMP*-ABBREV* information requests. *ABBREV*ICMP*-ABBREV* information were intended as part of a solution for the auto-configuration of diskless hosts. The network address is returned when a host makes a *ABBREV*ICMP*-ABBREV* information request."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addValue(paragraphPointer, count);
		if (informationReplyIssues->next != 0)
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* interfaces were configured to send *ABBREV*ICMP*-ABBREV* information reply messages. These are listed below."));
		else
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* interface was configured to send *ABBREV*ICMP*-ABBREV* information reply messages. This is detailed below."));

		interfaceListPointer = 0;
		issueLinksPointer = informationReplyIssues;
		while (issueLinksPointer != 0)
		{
			if (interfaceListPointer != issueLinksPointer->interfaceList)
			{
				interfaceListPointer = issueLinksPointer->interfaceList;

				// Init pointers...
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

				// Create Table...
				tempString.assign("SEC-INFO");
				tempString.append(interfaceListPointer->label);
				tempString.append("-TABLE");
				errorCode = device->addTable(paragraphPointer, tempString.c_str());
				if (errorCode != 0)
					return errorCode;
				tempString.assign(interfaceListPointer->tableTitle);
				tempString.append(i18n(" with *ABBREV*ICMP*-ABBREV* information reply enabled"));
				paragraphPointer->table->title.assign(tempString);

				outputInterfaceTableHeadings(device, interfaceListPointer, paragraphPointer);
			}
			outputInterfaceTableRow(device, interfaceListPointer, issueLinksPointer->interface, paragraphPointer);

			issueLinksPointer = issueLinksPointer->next;
		}
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		outputInterfaceTableExplain(device, interfaceListPointer, paragraphPointer);

		// Issue impact...
		securityIssuePointer->impactRating = 3;			// LOW
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("An attacker could use the *ABBREV*ICMP*-ABBREV* information reply feature to gain additional information about the network configuration."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 8;				// EASY
		paragraphPointer->paragraph.assign(i18n("*ABBREV*ICMP*-ABBREV* scanning tools, that are capably of sending various types of *ABBREV*ICMP*-ABBREV* messages, are available on the Internet. Furthermore, some *ABBREV*OS*-ABBREV* include *ABBREV*ICMP*-ABBREV* tools as standard."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 2;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("COMPANY* recommends that, if not required, *ABBREV*ICMP*-ABBREV* information reply messages should be disabled on all network interfaces."));
		if (strlen(disableInformationText) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(disableInformationText);
		}

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("*ABBREV*ICMP*-ABBREV* information reply messages were enabled"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Disable the sending of *ABBREV*ICMP*-ABBREV* information reply messages on all interfaces"), true);	
	}


	if (maskReplyIssues != 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] ICMP Mask Reply Messages Enabled\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("*ABBREV*ICMP*-ABBREV* Mask Reply Messages Were Enabled"));
		securityIssuePointer->reference.assign("GEN.INTEMASK.1");

		count = 0;
		issueLinksPointer = maskReplyIssues;
		while (issueLinksPointer != 0)
		{
			count++;
			issueLinksPointer = issueLinksPointer->next;
		}

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*ABBREV*ICMP*-ABBREV* mask reply messages inform network hosts of the *ABBREV*TCP*-ABBREV*/*ABBREV*IP*-ABBREV* network mask for a network segment. This protocol can now be regarded as legacy as it has been superseded by protocols such as *ABBREV*DHCP*-ABBREV*, or the network hosts will be configured fixed address information."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addValue(paragraphPointer, count);
		if (maskReplyIssues->next != 0)
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* interfaces were configured to send *ABBREV*ICMP*-ABBREV* mask reply messages. These are listed below."));
		else
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* interface was configured to send *ABBREV*ICMP*-ABBREV* mask reply messages. This is detailed below."));

		interfaceListPointer = 0;
		issueLinksPointer = maskReplyIssues;
		while (issueLinksPointer != 0)
		{
			if (interfaceListPointer != issueLinksPointer->interfaceList)
			{
				interfaceListPointer = issueLinksPointer->interfaceList;

				// Init pointers...
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

				// Create Table...
				tempString.assign("SEC-MASK");
				tempString.append(interfaceListPointer->label);
				tempString.append("-TABLE");
				errorCode = device->addTable(paragraphPointer, tempString.c_str());
				if (errorCode != 0)
					return errorCode;
				tempString.assign(interfaceListPointer->tableTitle);
				tempString.append(i18n(" with *ABBREV*ICMP*-ABBREV* mask reply enabled"));
				paragraphPointer->table->title.assign(tempString);

				outputInterfaceTableHeadings(device, interfaceListPointer, paragraphPointer);
			}
			outputInterfaceTableRow(device, interfaceListPointer, issueLinksPointer->interface, paragraphPointer);

			issueLinksPointer = issueLinksPointer->next;
		}
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		outputInterfaceTableExplain(device, interfaceListPointer, paragraphPointer);

		// Issue impact...
		securityIssuePointer->impactRating = 3;			// LOW
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("An attacker could use the *ABBREV*ICMP*-ABBREV* mask reply feature to gain additional information about the network configuration."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 8;				// EASY
		paragraphPointer->paragraph.assign(i18n("*ABBREV*ICMP*-ABBREV* scanning tools, that are capably of sending various types of *ABBREV*ICMP*-ABBREV* messages, are available on the Internet. Furthermore, some *ABBREV*OS*-ABBREV* include *ABBREV*ICMP*-ABBREV* tools as standard."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 3;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("COMPANY* recommends that, if not required, *ABBREV*ICMP*-ABBREV* mask reply messages should be disabled on all network interfaces."));
		if (strlen(disableMaskText) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(disableMaskText);
		}

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("*ABBREV*ICMP*-ABBREV* mask reply messages were enabled"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Disable the sending of *ABBREV*ICMP*-ABBREV* mask reply messages on all interfaces"), true);	
	}


	if ((redirectsIssues != 0) || ((globalRedirectSupported == true) && (globalRedirectEnabled == true)))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] ICMP Redirect Messages Enabled\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("*ABBREV*ICMP*-ABBREV* Redirect Messages Were Enabled"));
		securityIssuePointer->reference.assign("GEN.INTEREDI.1");

		if (globalRedirectSupported == false)
		{
			count = 0;
			issueLinksPointer = redirectsIssues;
			while (issueLinksPointer != 0)
			{
				count++;
				issueLinksPointer = issueLinksPointer->next;
			}
		}

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("When sending network traffic through a router, *ABBREV*ICMP*-ABBREV* redirect messages could be sent to the router in order to indicate a specific route that the sending host would like the network traffic to take. On a router that accepts *ABBREV*ICMP*-ABBREV* redirect message the network traffic will be forwarded using the specified route. Furthermore, some routers will cache the new routing information for use with future network packets."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addValue(paragraphPointer, count);
		if (globalRedirectSupported == true)
		{
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that the sending of *ABBREV*ICMP*-ABBREV* redirect messages was enabled on *DEVICENAME*."));
		}
		else
		{
			if (redirectsIssues->next != 0)
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* interfaces were configured to send *ABBREV*ICMP*-ABBREV* redirect messages. These are listed below."));
			else
				paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* interface was configured to send *ABBREV*ICMP*-ABBREV* redirect messages. This is detailed below."));

			interfaceListPointer = 0;
			issueLinksPointer = redirectsIssues;
			while (issueLinksPointer != 0)
			{
				if (interfaceListPointer != issueLinksPointer->interfaceList)
				{
					interfaceListPointer = issueLinksPointer->interfaceList;

					// Init pointers...
					paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

					// Create Table...
					tempString.assign("SEC-REDIRECT");
					tempString.append(interfaceListPointer->label);
					tempString.append("-TABLE");
					errorCode = device->addTable(paragraphPointer, tempString.c_str());
					if (errorCode != 0)
						return errorCode;
					tempString.assign(interfaceListPointer->tableTitle);
					tempString.append(i18n(" with *ABBREV*ICMP*-ABBREV* redirects enabled"));
					paragraphPointer->table->title.assign(tempString);

					outputInterfaceTableHeadings(device, interfaceListPointer, paragraphPointer);
				}
				outputInterfaceTableRow(device, interfaceListPointer, issueLinksPointer->interface, paragraphPointer);

				issueLinksPointer = issueLinksPointer->next;
			}
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
			outputInterfaceTableExplain(device, interfaceListPointer, paragraphPointer);
		}

		// Issue impact...
		securityIssuePointer->impactRating = 2;			// Informational
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("It is worth noting that on networks with functional network routing, disabling *ABBREV*ICMP*-ABBREV* redirects will have little to no effect."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 0;				// N/A
		paragraphPointer->paragraph.assign(i18n("*ABBREV*ICMP*-ABBREV* redirect messages are sent automatically."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 2;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("COMPANY* recommends that, if not required, the sending of *ABBREV*ICMP*-ABBREV* redirect messages from *DEVICETYPE* devices should be disabled."));
		if (strlen(disableRedirectText) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(disableRedirectText);
		}

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("*ABBREV*ICMP*-ABBREV* redirect message sending was enabled"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Disable the sending of *ABBREV*ICMP*-ABBREV* redirect messages"), true);
	}


	if (directedIssues != 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Directed Broadcasts Enabled\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("*ABBREV*IP*-ABBREV* Directed Broadcasts Were Enabled"));
		securityIssuePointer->reference.assign("GEN.INTEDIRE.1");

		count = 0;
		issueLinksPointer = directedIssues;
		while (issueLinksPointer != 0)
		{
			count++;
			issueLinksPointer = issueLinksPointer->next;
		}

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*ABBREV*ICMP*-ABBREV* echo requests can be addressed to an entire network or subnet as well as to individual hosts. Disabling directed broadcasts on each individual network interface will help prevent network ping requests."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addValue(paragraphPointer, count);
		if (directedIssues->next != 0)
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that directed broadcasts were enabled on *NUMBER* interfaces. These are listed below."));
		else
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that directed broadcasts were enabled on *NUMBER* interface. This is detailed below."));

		interfaceListPointer = 0;
		issueLinksPointer = directedIssues;
		while (issueLinksPointer != 0)
		{
			if (interfaceListPointer != issueLinksPointer->interfaceList)
			{
				interfaceListPointer = issueLinksPointer->interfaceList;

				// Init pointers...
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

				// Create Table...
				tempString.assign("SEC-DIRECT");
				tempString.append(interfaceListPointer->label);
				tempString.append("-TABLE");
				errorCode = device->addTable(paragraphPointer, tempString.c_str());
				if (errorCode != 0)
					return errorCode;
				tempString.assign(interfaceListPointer->tableTitle);
				tempString.append(i18n(" with directed broadcasts enabled"));
				paragraphPointer->table->title.assign(tempString);

				outputInterfaceTableHeadings(device, interfaceListPointer, paragraphPointer);
			}
			outputInterfaceTableRow(device, interfaceListPointer, issueLinksPointer->interface, paragraphPointer);

			issueLinksPointer = issueLinksPointer->next;
		}
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		outputInterfaceTableExplain(device, interfaceListPointer, paragraphPointer);

		// Issue impact...
		securityIssuePointer->impactRating = 5;			// Medium
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("A *ABBREV*DoS*-ABBREV* attack exists that makes use of network echo requests, known as a smurf attack. An attacker would send an ICMP echo request with the victim hosts *ABBREV*IP*-ABBREV* address spoofed as the source. The hosts on the network would then reply to the echo request, flooding the victim host."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 4;				// Moderate
		paragraphPointer->paragraph.assign(i18n("Tools are available on the Internet that can perform the smurf attack outlined in the issue impact."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 2;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that directed broadcasts should be disabled on all network interfaces."));
		if (strlen(disableDirectedText) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(disableDirectedText);
		}

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("directed broadcasts were enabled"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Disable directed broadcasts on all interfaces"), true);
	}


	if (mopIssues != 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] MOP Enabled\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("*ABBREV*MOP*-ABBREV* Enabled"));
		securityIssuePointer->reference.assign("GEN.INTEMOPE.1");

		count = 0;
		issueLinksPointer = mopIssues;
		while (issueLinksPointer != 0)
		{
			count++;
			issueLinksPointer = issueLinksPointer->next;
		}

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*ABBREV*MOP*-ABBREV* is used with the DECnet protocol suite. *ABBREV*MOP*-ABBREV* is enabled by default on ethernet interfaces on some *DEVICETYPE* device *ABBREV*OS*-ABBREV* versions."));
		device->addValue(paragraphPointer, count);
		if (mopIssues->next != 0)
			paragraphPointer->paragraph.append(i18n(" *COMPANY* determined that *ABBREV*MOP*-ABBREV* was enabled on *NUMBER* interfaces. These are listed below."));
		else
			paragraphPointer->paragraph.append(i18n(" *COMPANY* determined that *ABBREV*MOP*-ABBREV* was enabled on *NUMBER* interface. This is detailed below."));

		interfaceListPointer = 0;
		issueLinksPointer = mopIssues;
		while (issueLinksPointer != 0)
		{
			if (interfaceListPointer != issueLinksPointer->interfaceList)
			{
				interfaceListPointer = issueLinksPointer->interfaceList;

				// Init pointers...
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

				// Create Table...
				tempString.assign("SEC-MOP");
				tempString.append(interfaceListPointer->label);
				tempString.append("-TABLE");
				errorCode = device->addTable(paragraphPointer, tempString.c_str());
				if (errorCode != 0)
					return errorCode;
				tempString.assign(interfaceListPointer->tableTitle);
				tempString.append(i18n(" with *ABBREV*MOP*-ABBREV* enabled"));
				paragraphPointer->table->title.assign(tempString);

				outputInterfaceTableHeadings(device, interfaceListPointer, paragraphPointer);
			}
			outputInterfaceTableRow(device, interfaceListPointer, issueLinksPointer->interface, paragraphPointer);

			issueLinksPointer = issueLinksPointer->next;
		}
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		outputInterfaceTableExplain(device, interfaceListPointer, paragraphPointer);

		// Issue impact...
		securityIssuePointer->impactRating = 1;			// Informational
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("Running unused services increases the chances of an attacker finding a security hole or fingerprinting a device."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 0;				// Moderate
		paragraphPointer->paragraph.assign(i18n("Few tools are available that make use of *ABBREV*MOP*-ABBREV*."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 2;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, if not required, *ABBREV*MOP*-ABBREV* should be disabled on all ethernet interfaces."));
		if (strlen(disableMOPText) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(disableMOPText);
		}

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("*ABBREV*MOP*-ABBREV* was enabled"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Disable *ABBREV*MOP*-ABBREV* on all interfaces"), true);
	}

	if (activeIssues != 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Potentially Unused Network Interfaces\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("Potentially Unused Network Interfaces"));
		securityIssuePointer->reference.assign("GEN.INTEACTI.1");

		count = 0;
		issueLinksPointer = activeIssues;
		while (issueLinksPointer != 0)
		{
			count++;
			issueLinksPointer = issueLinksPointer->next;
		}

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("On *DEVICETYPE* devices it is possible to enable and disable individual network interfaces. It is good security practice to disable unused interfaces to help prevent unauthorised access to the network."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addValue(paragraphPointer, count);
		if (activeIssues->next != 0)
			paragraphPointer->paragraph.assign(i18n(" *COMPANY* determined that *NUMBER* interfaces were active and potentially unused. These are listed below."));
		else
			paragraphPointer->paragraph.assign(i18n(" *COMPANY* determined that *NUMBER* interface was active and potentially unused. This is detailed below."));

		interfaceListPointer = 0;
		issueLinksPointer = activeIssues;
		while (issueLinksPointer != 0)
		{
			if (interfaceListPointer != issueLinksPointer->interfaceList)
			{
				interfaceListPointer = issueLinksPointer->interfaceList;

				// Init pointers...
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

				// Create Table...
				tempString.assign("SEC-ACT");
				tempString.append(interfaceListPointer->label);
				tempString.append("-TABLE");
				errorCode = device->addTable(paragraphPointer, tempString.c_str());
				if (errorCode != 0)
					return errorCode;
				tempString.assign(interfaceListPointer->tableTitle);
				tempString.append(i18n(" were active and potentially unused"));
				paragraphPointer->table->title.assign(tempString);

				outputInterfaceTableHeadings(device, interfaceListPointer, paragraphPointer);
			}
			outputInterfaceTableRow(device, interfaceListPointer, issueLinksPointer->interface, paragraphPointer);

			issueLinksPointer = issueLinksPointer->next;
		}
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		outputInterfaceTableExplain(device, interfaceListPointer, paragraphPointer);

		// Issue impact...
		securityIssuePointer->impactRating = 1;			// Informational
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("If unused interfaces are not disabled, an attacker may be able to gain access with risking detection by unplugging an existing connection."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 2;				// Challenging
		paragraphPointer->paragraph.assign(i18n("The attacker would require physical access to the *DEVICETYPE* device in order to connect to an unused network connection."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 3;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that the list of potentially unused active network connections should be reviewed and any unused interfaces disabled."));
		if (strlen(disableActiveText) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(disableActiveText);
		}

		// Conclusions text...
		if (activeIssues->next != 0)
			securityIssuePointer->conLine.append(i18n("potentially unused interfaces were active"));
		else
			securityIssuePointer->conLine.append(i18n("a potentially unused interface was active"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Disable all unused interfaces"), true);
	}

	if (filterIssues != 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Not All Interfaces Have Filtering\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		if (filterIssues->next != 0)
			securityIssuePointer->title.assign(i18n("Interfaces Were Configured With No Filtering"));
		else
			securityIssuePointer->title.assign(i18n("An Interface Was Configured With No Filtering"));
		securityIssuePointer->reference.assign("GEN.INTEFILT.1");

		count = 0;
		issueLinksPointer = filterIssues;
		while (issueLinksPointer != 0)
		{
			count++;
			issueLinksPointer = issueLinksPointer->next;
		}

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addString(paragraphPointer, filterName);
		paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices can be configured with *DATA* to filter network traffic in order to prevent unauthorised access to hosts and services."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addValue(paragraphPointer, count);
		if ((inboundSupported == true) && (outboundSupported == true))
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* interfaces were configured without either inbound or outbound network filtering. These are listed below."));
		else if (inboundSupported == true)
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* interfaces were configured without inbound network filtering. These are listed below."));
		else
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* interfaces were configured without outbound network filtering. These are listed below."));

		interfaceListPointer = 0;
		issueLinksPointer = filterIssues;
		while (issueLinksPointer != 0)
		{
			if (interfaceListPointer != issueLinksPointer->interfaceList)
			{
				interfaceListPointer = issueLinksPointer->interfaceList;

				// Init pointers...
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

				// Create Table...
				tempString.assign("SEC-FILTER");
				tempString.append(interfaceListPointer->label);
				tempString.append("-TABLE");
				errorCode = device->addTable(paragraphPointer, tempString.c_str());
				if (errorCode != 0)
					return errorCode;
				tempString.assign(interfaceListPointer->tableTitle);
				tempString.append(i18n(" were not configured to filter network traffic"));
				paragraphPointer->table->title.assign(tempString);

				outputInterfaceTableHeadings(device, interfaceListPointer, paragraphPointer);
			}
			outputInterfaceTableRow(device, interfaceListPointer, issueLinksPointer->interface, paragraphPointer);

			issueLinksPointer = issueLinksPointer->next;
		}
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		outputInterfaceTableExplain(device, interfaceListPointer, paragraphPointer);

		// Issue impact...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		device->addString(paragraphPointer, filterName);
		paragraphPointer->paragraph.assign(i18n("With no *DATA* configured on all the active interfaces an attacker would not be prevented by *DEVICENAME* from accessing hosts or services."));
		if (device->isFirewall == true)
		{
			securityIssuePointer->impactRating = 9;			// Critical
			paragraphPointer->paragraph.append(i18n(" Furthermore, the primary purpose of *DEVICETYPE* devices is to provide a security barrier against unauthorised access."));
		}
		else
			securityIssuePointer->impactRating = 6;			// Medium

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 0;				// N/A
		device->addString(paragraphPointer, filterName);
		paragraphPointer->paragraph.assign(i18n("With no *DATA* a user or attacker would not be restricted by *DEVICENAME* when access network services."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 3;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		device->addString(paragraphPointer, filterName);
		if ((inboundSupported == true) && (outboundSupported == true))
			paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that all active interfaces should be configured with *DATA* to filter inbound and outbound network traffic."));
		else if (inboundSupported == true)
			paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that all active interfaces should be configured with *DATA* to filter inbound network traffic."));
		else
			paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that all active interfaces should be configured with *DATA* to filter outbound network traffic."));
		if (strlen(configFilterText) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(configFilterText);
		}

		// Conclusions text...
		if ((inboundSupported == true) && (outboundSupported == true))
			securityIssuePointer->conLine.append(i18n("interfaces were configured without inbound and outbound network filtering"));
		else if (inboundSupported == true)
			securityIssuePointer->conLine.append(i18n("interfaces were configured without inbound network filtering"));
		else
			securityIssuePointer->conLine.append(i18n("interfaces were configured without outbound network filtering"));

		// Recommendation list text...
		if ((inboundSupported == true) && (outboundSupported == true))
			device->addRecommendation(securityIssuePointer, i18n("Configure inbound and outbound network filtering on all interfaces"), true);
		else if (inboundSupported == true)
			device->addRecommendation(securityIssuePointer, i18n("Configure inbound network filtering on all interfaces"), true);
		else
			device->addRecommendation(securityIssuePointer, i18n("Configure outbound network filtering on all interfaces"), true);
	}

	if (trunkingIssues != 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Switch Port Trunking Was Enabled\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("Switch Port Trunking Was Enabled"));
		securityIssuePointer->reference.assign("GEN.INTETRUN.1");

		count = 0;
		issueLinksPointer = trunkingIssues;
		while (issueLinksPointer != 0)
		{
			count++;
			issueLinksPointer = issueLinksPointer->next;
		}

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*DEVICETYPE* devices are able to transfer *ABBREV*VLAN*-ABBREV* packets to different network devices, extending a *ABBREV*VLAN*-ABBREV* across different physical devices. In order to extend a *ABBREV*VLAN*-ABBREV* to a different physical device, a trunk has to be created between the devices."));
		if (defaultAutoTrunk == true)
			paragraphPointer->paragraph.append(i18n(" *DEVICETYPE* devices default to allowing a trunk to be negotiated on a particular switch port if the connected device will also allow the trunk and supports a common trunking protocol."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addValue(paragraphPointer, count);
		if (trunkingIssues->next != 0)
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* interfaces were configured to trunk. These are listed below."));
		else
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* interface was configured to trunk. This is detailed below."));

		interfaceListPointer = 0;
		issueLinksPointer = trunkingIssues;
		while (issueLinksPointer != 0)
		{
			if (interfaceListPointer != issueLinksPointer->interfaceList)
			{
				interfaceListPointer = issueLinksPointer->interfaceList;

				// Init pointers...
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

				// Create Table...
				tempString.assign("SEC-TRUNK");
				tempString.append(interfaceListPointer->label);
				tempString.append("-TABLE");
				errorCode = device->addTable(paragraphPointer, tempString.c_str());
				if (errorCode != 0)
					return errorCode;
				tempString.assign(interfaceListPointer->tableTitle);
				tempString.append(i18n(" that allow trunks"));
				paragraphPointer->table->title.assign(tempString);

				outputInterfaceTableHeadings(device, interfaceListPointer, paragraphPointer);
			}
			outputInterfaceTableRow(device, interfaceListPointer, issueLinksPointer->interface, paragraphPointer);

			issueLinksPointer = issueLinksPointer->next;
		}
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		outputInterfaceTableExplain(device, interfaceListPointer, paragraphPointer);

		// Issue impact...
		securityIssuePointer->impactRating = 8;			// High
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("An attacker who was able to create a trunk would gain direct access to all the *ABBREV*VLANs*-ABBREV* extended over the trunk. This would allow an attacker to bypass any network filtering between the *ABBREV*VLANs*-ABBREV* and capture potentially sensitive information. If a clear text protocols network traffic is transfered over the trunk an attacker would gain immediate access to any authentication credentials transfered."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 6;				// Challenging
		paragraphPointer->paragraph.assign(i18n("Tools are available on the Internet that are capable of creating trunks, or the attacker could use a network switch. The attacker would require a little knowledge of network trunking."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 5;				// Planned
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, where possible, all switch ports should be configured to provide no trunking. If trunking is required on a specific switch port, *COMPANY* recommends that the switch port should be configured to trunk only the required *ABBREV*VLANs*-ABBREV*."));
		if (strlen(disableTrunkText) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(disableTrunkText);
		}

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("trunking was enabled"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Disable trunking where not required"), true);
	}

	if (portSecIssues != 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Switch Port Security Disabled\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("Switch Port Security Disabled"));
		securityIssuePointer->reference.assign("GEN.INTEPOSE.1");

		count = 0;
		issueLinksPointer = portSecIssues;
		while (issueLinksPointer != 0)
		{
			count++;
			issueLinksPointer = issueLinksPointer->next;
		}

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("Switch port security enables a *DEVICETYPE* device to help prevent unauthorised access to the network by limiting the *ABBREV*MAC*-ABBREV* addresses allowed on specific ports. *ABBREV*MAC*-ABBREV* addresses can either be specified for a particular switch port or can be learned by the device. When port security is configured a variety of actions can be taken when a violation occurs, such as automatically disabling the port."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		device->addValue(paragraphPointer, count);
		if (portSecIssues->next != 0)
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* interfaces were configured with no switch port security. These are listed below."));
		else
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* interface was configured with no switch port security. This is detailed below."));

		interfaceListPointer = 0;
		issueLinksPointer = portSecIssues;
		while (issueLinksPointer != 0)
		{
			if (interfaceListPointer != issueLinksPointer->interfaceList)
			{
				interfaceListPointer = issueLinksPointer->interfaceList;

				// Init pointers...
				paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

				// Create Table...
				tempString.assign("SEC-PORTSECURITY");
				tempString.append(interfaceListPointer->label);
				tempString.append("-TABLE");
				errorCode = device->addTable(paragraphPointer, tempString.c_str());
				if (errorCode != 0)
					return errorCode;
				tempString.assign(interfaceListPointer->tableTitle);
				tempString.append(i18n(" that do not have port security"));
				paragraphPointer->table->title.assign(tempString);

				outputInterfaceTableHeadings(device, interfaceListPointer, paragraphPointer);
			}
			outputInterfaceTableRow(device, interfaceListPointer, issueLinksPointer->interface, paragraphPointer);

			issueLinksPointer = issueLinksPointer->next;
		}
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		outputInterfaceTableExplain(device, interfaceListPointer, paragraphPointer);

		// Issue impact...
		securityIssuePointer->impactRating = 6;			// Medium
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("A switch port with no configured port security could allow an attacker to attach an unauthorised device and gain access to the network."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 6;				// Easy
		paragraphPointer->paragraph.assign(i18n("An attacker would have to gain access to a switch port with no security configured. If the switch port is not directly patched to a wall socket, the attacker would have to gain physical access to the device. It is worth noting that an attacker could assume the *ABBREV*MAC*-ABBREV* address of a device already attached to the port in order to gain access and bypass the port security feature."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 4;				// Planned
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that, where possible, port security should be enabled on all switch ports. Furthermore, *COMPANY* recommends that all switch ports that are not used should be shutdown."));
		if (strlen(enablePortSecurityText) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(enablePortSecurityText);
		}

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("port security was disabled"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Enable port security on all switch ports"), true);
	}

	return errorCode;
}


int Interfaces::addInterfaceIssue(const char *issueRef, interfaceListConfig *interfaceListPointer, interfaceConfig *interfacePointer)
{
	// Variables...
	issueLinksConfig *issueLinksPointer = 0;

	if (strcmp(issueRef, "GEN.INTEDIRE.1") == 0)
	{
		if (directedIssues == 0)
		{
			directedIssues = new (issueLinksConfig);
			issueLinksPointer = directedIssues;
		}
		else
		{
			issueLinksPointer = directedIssues;
			while (issueLinksPointer->next != 0)
				issueLinksPointer = issueLinksPointer->next;
			issueLinksPointer->next = new (issueLinksConfig);
			issueLinksPointer = issueLinksPointer->next;
		}
	}
	else if (strcmp(issueRef, "GEN.INTEPARP.1") == 0)
	{
		if (proxyARPIssues == 0)
		{
			proxyARPIssues = new (issueLinksConfig);
			issueLinksPointer = proxyARPIssues;
		}
		else
		{
			issueLinksPointer = proxyARPIssues;
			while (issueLinksPointer->next != 0)
				issueLinksPointer = issueLinksPointer->next;
			issueLinksPointer->next = new (issueLinksConfig);
			issueLinksPointer = issueLinksPointer->next;
		}
	}
	else if (strcmp(issueRef, "GEN.INTEICUN.1") == 0)
	{
		if (unreachableIssues == 0)
		{
			unreachableIssues = new (issueLinksConfig);
			issueLinksPointer = unreachableIssues;
		}
		else
		{
			issueLinksPointer = unreachableIssues;
			while (issueLinksPointer->next != 0)
				issueLinksPointer = issueLinksPointer->next;
			issueLinksPointer->next = new (issueLinksConfig);
			issueLinksPointer = issueLinksPointer->next;
		}
	}
	else if (strcmp(issueRef, "GEN.INTEMASK.1") == 0)
	{
		if (maskReplyIssues == 0)
		{
			maskReplyIssues = new (issueLinksConfig);
			issueLinksPointer = maskReplyIssues;
		}
		else
		{
			issueLinksPointer = maskReplyIssues;
			while (issueLinksPointer->next != 0)
				issueLinksPointer = issueLinksPointer->next;
			issueLinksPointer->next = new (issueLinksConfig);
			issueLinksPointer = issueLinksPointer->next;
		}
	}
	else if (strcmp(issueRef, "GEN.INTEREDI.1") == 0)
	{
		if (redirectsIssues == 0)
		{
			redirectsIssues = new (issueLinksConfig);
			issueLinksPointer = redirectsIssues;
		}
		else
		{
			issueLinksPointer = redirectsIssues;
			while (issueLinksPointer->next != 0)
				issueLinksPointer = issueLinksPointer->next;
			issueLinksPointer->next = new (issueLinksConfig);
			issueLinksPointer = issueLinksPointer->next;
		}
	}
	else if (strcmp(issueRef, "GEN.INTEINFO.1") == 0)
	{
		if (informationReplyIssues == 0)
		{
			informationReplyIssues = new (issueLinksConfig);
			issueLinksPointer = informationReplyIssues;
		}
		else
		{
			issueLinksPointer = informationReplyIssues;
			while (issueLinksPointer->next != 0)
				issueLinksPointer = issueLinksPointer->next;
			issueLinksPointer->next = new (issueLinksConfig);
			issueLinksPointer = issueLinksPointer->next;
		}
	}
	else if (strcmp(issueRef, "GEN.INTEMOPE.1") == 0)
	{
		if (mopIssues == 0)
		{
			mopIssues = new (issueLinksConfig);
			issueLinksPointer = mopIssues;
		}
		else
		{
			issueLinksPointer = mopIssues;
			while (issueLinksPointer->next != 0)
				issueLinksPointer = issueLinksPointer->next;
			issueLinksPointer->next = new (issueLinksConfig);
			issueLinksPointer = issueLinksPointer->next;
		}
	}
	else if (strcmp(issueRef, "GEN.INTECDPE.1") == 0)
	{
		if (cdpIssues == 0)
		{
			cdpIssues = new (issueLinksConfig);
			issueLinksPointer = cdpIssues;
		}
		else
		{
			issueLinksPointer = cdpIssues;
			while (issueLinksPointer->next != 0)
				issueLinksPointer = issueLinksPointer->next;
			issueLinksPointer->next = new (issueLinksConfig);
			issueLinksPointer = issueLinksPointer->next;
		}
	}
	else if (strcmp(issueRef, "GEN.INTEACTI.1") == 0)
	{
		if (activeIssues == 0)
		{
			activeIssues = new (issueLinksConfig);
			issueLinksPointer = activeIssues;
		}
		else
		{
			issueLinksPointer = activeIssues;
			while (issueLinksPointer->next != 0)
				issueLinksPointer = issueLinksPointer->next;
			issueLinksPointer->next = new (issueLinksConfig);
			issueLinksPointer = issueLinksPointer->next;
		}
	}
	else if (strcmp(issueRef, "GEN.INTEFILT.1") == 0)
	{
		if (filterIssues == 0)
		{
			filterIssues = new (issueLinksConfig);
			issueLinksPointer = filterIssues;
		}
		else
		{
			issueLinksPointer = filterIssues;
			while (issueLinksPointer->next != 0)
				issueLinksPointer = issueLinksPointer->next;
			issueLinksPointer->next = new (issueLinksConfig);
			issueLinksPointer = issueLinksPointer->next;
		}
	}
	else if (strcmp(issueRef, "GEN.INTETRUN.1") == 0)
	{
		if (trunkingIssues == 0)
		{
			trunkingIssues = new (issueLinksConfig);
			issueLinksPointer = trunkingIssues;
		}
		else
		{
			issueLinksPointer = trunkingIssues;
			while (issueLinksPointer->next != 0)
				issueLinksPointer = issueLinksPointer->next;
			issueLinksPointer->next = new (issueLinksConfig);
			issueLinksPointer = issueLinksPointer->next;
		}
	}
	else if (strcmp(issueRef, "GEN.INTEPOSE.1") == 0)
	{
		if (portSecIssues == 0)
		{
			portSecIssues = new (issueLinksConfig);
			issueLinksPointer = portSecIssues;
		}
		else
		{
			issueLinksPointer = portSecIssues;
			while (issueLinksPointer->next != 0)
				issueLinksPointer = issueLinksPointer->next;
			issueLinksPointer->next = new (issueLinksConfig);
			issueLinksPointer = issueLinksPointer->next;
		}
	}

	issueLinksPointer->interface = interfacePointer;
	issueLinksPointer->interfaceList = interfaceListPointer;
	issueLinksPointer->next = 0;

	return 0;
}



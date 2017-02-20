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
#include <cstdlib>

#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "iosdevice.h"
#include "interfaces.h"
#include "general.h"


IOSInterfaces::IOSInterfaces()
{
	// Interface Options...
	filterIn = i18n("*ABBREV*ACL*-ABBREV* In");		// The filter in table title text
	filterOut = i18n("*ABBREV*ACL*-ABBREV* Out");	// The filter out table title text
	showDescription = true;							// Show the interface description
	cdpGlobalRequired = true;						// If CDP needs to be enabled globally as well
	disableCDPText = i18n("The following commands can be used to disable *ABBREV*CDP*-ABBREV* on *DEVICETYPE* devices. The first command disables *ABBREV*CDP*-ABBREV* for the entire device, whilst the second can be used to disable *ABBREV*CDP*-ABBREV* on individual interfaces.*CODE**COMMAND*no cdp run*-COMMAND**COMMAND*no cdp enable*-COMMAND**-CODE*");						// The text and commands to disable CDP
	cdpSupported = true;							// Is CDP supported on interfaces
	disableProxyARPText = i18n("Proxy *ABBREV*ARP*-ABBREV* can be disabled on interfaces using the following command:*CODE**COMMAND*no ip proxy-arp*-COMMAND**-CODE*");// The text and commands to disable Proxy ARP
	disableUnreachablesText = i18n("*ABBREV*ICMP*-ABBREV* unreachable message sending can be disabled on network interfaces with the following command:*CODE**COMMAND*no ip unreachables*-COMMAND**-CODE*");				// The text and commands to disable ICMP unreachable messages
	disableInformationText = i18n("*ABBREV*ICMP*-ABBREV* information reply message sending can be disabled on network interfaces with the following command:*CODE**COMMAND*no ip information-reply*-COMMAND**-CODE*");				// The text and commands to disable ICMP information messages
	disableMaskText = i18n("*ABBREV*ICMP*-ABBREV* mask reply message sending can be disabled on network interfaces with the following command:*CODE**COMMAND*no ip mask-reply*-COMMAND**-CODE*");						// The text and commands to disable ICMP mask messages
	disableRedirectText = i18n("*ABBREV*ICMP*-ABBREV* redirect message sending can be disabled on network interfaces with the following command:*CODE**COMMAND*no ip redirects*-COMMAND**-CODE*");					// The text and commands to disable ICMP redirect messages
	disableDirectedText = i18n("Directed broadcases can be disabled on *DEVICETYPE* devices with the following command:*CODE**COMMAND*no ip directed broadcast*-COMMAND**-CODE*");					// The text and commands to disable directed broadcasts
	disableMOPText = i18n("*ABBREV*MOP*-ABBREV* can be disabled on each interface with the following command:*CODE**COMMAND*no mop enabled*-COMMAND**-CODE*");						// The text and commands to disable MOP
	disableActiveText = i18n("Unused interfaces can be disabled with the following command:*CODE**COMMAND*shutdown*-COMMAND**-CODE*");					// The text and commands to disable potentially unused interfaces
	filterName = i18n("*ABBREV*ACL*-ABBREV*");					// The filter list name for use in the filter issue text
	configFilterText = i18n("*DEVICETYPE* device filtering can be configured on interfaces with the following command:*CODE**COMMAND*ip access-group *CMDUSER*ACL*-CMDUSER* *CMDOPTION*in *CMDOR* out*-CMDOPTION**-COMMAND**-CODE*");					// The text and commands to configure network filtering
	defaultAutoTrunk = true;						// Default to automatically trunk
	disableTrunkText = i18n("Switch ports can be configured to provide no trunking on each interface with the following command:*CODE**COMMAND*switchport mode access*-COMMAND**-CODE*");					// The text and commands to disable trunking on a port
	enablePortSecurityText = i18n("Switch port security with *ABBREV*MAC*-ABBREV* address learning and port shutdown on a violation can be configured for each interface with the following commands:*CODE**COMMAND*switchport port-security*-COMMAND**COMMAND*switchport port-security violation shutdown*-COMMAND**COMMAND*switchport port-security mac-address sticky*-COMMAND**-CODE*");				// The text and commands to enable port security
}


int IOSInterfaces::processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	interfaceListConfig *interfaceListPointer = 0;
	interfaceConfig *interfacePointer = 0;
	string tempString;
	bool setting = false;
	int tempInt = 0;

	// Interface...
	if ((strcmp(command->part(0), "interface") == 0) && (strcmp(command->part(1), "service-engine") != 0) && (strcmp(command->part(1), "range") != 0) && (strcmp(command->part(1), "content-engine") != 0))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("%sInterface Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

		// Get the correct list for the type of interface...
		if (strncasecmp(command->part(1), "GigabitEthernet", 15) == 0)
		{
			interfaceListPointer = getInterfaceList("GETHERINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("Gigabit Ethernet Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices gigabit ethernet interfaces.");
				interfaceListPointer->tableTitle = i18n("Gigabit ethernet interfaces");
				interfaceListPointer->label = "GETHERINTERFACES";
				interfaceListPointer->proxyArpSupported = true;
				interfaceListPointer->mopSupported = true;
				interfaceListPointer->unreachablesSupported = true;
				interfaceListPointer->redirectsSupported = true;
				interfaceListPointer->ipMaskReplySupported = true;
				interfaceListPointer->ipDirectBroadcastSupported = true;
				interfaceListPointer->vlanSupported = true;
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
				interfaceListPointer->inboundFilterSupported = true;					// Is the inbound filtering supported?
				interfaceListPointer->outboudFilterSupported = true;					// Is the outbound filtering supported?
				interfaceListPointer->portSecuritySupported = false;
				if (device->isSwitch == true)
				{
					interfaceListPointer->portModeSupported = true;
				}
				if (device->general != 0)
				{
					if ((device->general->versionMajor > 12) || ((device->general->versionMajor == 12) && (device->general->versionMinor > 1)))
					{
						interfaceListPointer->informationReplySupported = true;
						if (device->isSwitch)
						{
							interfaceListPointer->portSecuritySupported = true;
						}
					}
				}
				interfaceListPointer->cdpSupported = true;
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(1) + 15);
			interfacePointer->proxyARP = true;
			interfacePointer->mop = true;
			interfacePointer->ipUnreachables = true;
			interfacePointer->ipRedirects = true;
			interfacePointer->cdp = true;
			if (device->general != 0)
			{
				if (device->general->versionMajor < 12)
					interfacePointer->ipDirectBroadcast.assign(i18n("All"));
			}
			if (device->isSwitch == true)
			{
				if (device->isRouter == true)
					interfacePointer->switchportMode = portModeAccess;
				else
					interfacePointer->switchportMode = portModeDynamic;
			}
		}
		else if (strncasecmp(command->part(1), "FastEthernet", 12) == 0)
		{
			interfaceListPointer = getInterfaceList("FETHERINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("Fast Ethernet Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices fast ethernet interfaces.");
				interfaceListPointer->tableTitle = i18n("Fast Ethernet interfaces");
				interfaceListPointer->label = "FETHERINTERFACES";
				interfaceListPointer->proxyArpSupported = true;
				interfaceListPointer->mopSupported = true;
				interfaceListPointer->unreachablesSupported = true;
				interfaceListPointer->redirectsSupported = true;
				interfaceListPointer->ipMaskReplySupported = true;
				interfaceListPointer->ipDirectBroadcastSupported = true;
				interfaceListPointer->vlanSupported = true;
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
				interfaceListPointer->inboundFilterSupported = true;					// Is the inbound filtering supported?
				interfaceListPointer->outboudFilterSupported = true;					// Is the outbound filtering supported?
				interfaceListPointer->portSecuritySupported = false;
				if (device->isSwitch == true)
				{
					interfaceListPointer->portModeSupported = true;
				}
				if (device->general != 0)
				{
					if ((device->general->versionMajor > 12) || ((device->general->versionMajor == 12) && (device->general->versionMinor > 1)))
					{
						interfaceListPointer->informationReplySupported = true;
						if (device->isSwitch)
						{
							interfaceListPointer->portSecuritySupported = true;
						}
					}
				}
				interfaceListPointer->cdpSupported = true;
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(1) + 12);
			interfacePointer->proxyARP = true;
			interfacePointer->mop = true;
			interfacePointer->ipUnreachables = true;
			interfacePointer->ipRedirects = true;
			interfacePointer->cdp = true;
			if (device->general != 0)
			{
				if (device->general->versionMajor < 12)
					interfacePointer->ipDirectBroadcast.assign(i18n("All"));
			}
			if (device->isSwitch == true)
			{
				if (device->isRouter == true)
					interfacePointer->switchportMode = portModeAccess;
				else
					interfacePointer->switchportMode = portModeDynamic;
			}
		}
		else if (strncasecmp(command->part(1), "Ethernet", 8) == 0)
		{
			interfaceListPointer = getInterfaceList("ETHERINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("Ethernet Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices ethernet interfaces.");
				interfaceListPointer->tableTitle = i18n("Ethernet interfaces");
				interfaceListPointer->label = "ETHERINTERFACES";
				interfaceListPointer->proxyArpSupported = true;
				interfaceListPointer->mopSupported = true;
				interfaceListPointer->unreachablesSupported = true;
				interfaceListPointer->redirectsSupported = true;
				interfaceListPointer->ipMaskReplySupported = true;
				interfaceListPointer->ipDirectBroadcastSupported = true;
				interfaceListPointer->vlanSupported = true;
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
				interfaceListPointer->inboundFilterSupported = true;					// Is the inbound filtering supported?
				interfaceListPointer->outboudFilterSupported = true;					// Is the outbound filtering supported?
				interfaceListPointer->portSecuritySupported = false;
				if (device->isSwitch == true)
				{
					interfaceListPointer->portModeSupported = true;
				}
				if (device->general != 0)
				{
					if ((device->general->versionMajor > 12) || ((device->general->versionMajor == 12) && (device->general->versionMinor > 1)))
					{
						interfaceListPointer->informationReplySupported = true;
						if (device->isSwitch)
						{
							interfaceListPointer->portSecuritySupported = true;
						}
					}
				}
				interfaceListPointer->cdpSupported = true;
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(1) + 8);
			interfacePointer->proxyARP = true;
			interfacePointer->mop = true;
			interfacePointer->ipUnreachables = true;
			interfacePointer->ipRedirects = true;
			interfacePointer->cdp = true;
			if (device->general != 0)
			{
				if (device->general->versionMajor < 12)
					interfacePointer->ipDirectBroadcast.assign(i18n("All"));
			}
			if (device->isSwitch == true)
			{
				if (device->isRouter == true)
					interfacePointer->switchportMode = portModeAccess;
				else
					interfacePointer->switchportMode = portModeDynamic;
			}
		}
		else if (strncasecmp(command->part(1), "Vlan", 4) == 0)
		{
			interfaceListPointer = getInterfaceList("VLANINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("*ABBREV*VLAN*-ABBREV* Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices *ABBREV*VLAN*-ABBREV* interfaces.");
				interfaceListPointer->tableTitle = i18n("*ABBREV*VLAN*-ABBREV* interfaces");
				interfaceListPointer->label = "VLANINTERFACES";
				interfaceListPointer->proxyArpSupported = true;
				interfaceListPointer->unreachablesSupported = true;
				interfaceListPointer->redirectsSupported = true;
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
				interfaceListPointer->inboundFilterSupported = true;					// Is the inbound filtering supported?
				interfaceListPointer->outboudFilterSupported = true;					// Is the outbound filtering supported?
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(1) + 4);
			interfacePointer->proxyARP = true;
			interfacePointer->ipUnreachables = true;
			interfacePointer->ipRedirects = true;
		}
		else if (strncasecmp(command->part(1), "Loopback", 8) == 0)
		{
			interfaceListPointer = getInterfaceList("LOOPBACKINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("Loopback Interfaces");
				interfaceListPointer->description = i18n("Loopback interfaces are virutal interfaces that are handled by software and are always up. This section describes the configuration of the loopback interfaces.");
				interfaceListPointer->tableTitle = i18n("Loopback interfaces");
				interfaceListPointer->label = "LOOPBACKINTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(1) + 8);
		}
		else if (strncasecmp(command->part(1), "Serial", 6) == 0)
		{
			interfaceListPointer = getInterfaceList("SERIALINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("Serial Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices serial interfaces.");
				interfaceListPointer->tableTitle = i18n("Serial interfaces");
				interfaceListPointer->label = "SERIALINTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
				interfaceListPointer->inboundFilterSupported = true;					// Is the inbound filtering supported?
				interfaceListPointer->outboudFilterSupported = true;					// Is the outbound filtering supported?
				if (device->isSwitch == true)
				{
					interfaceListPointer->portModeSupported = true;
				}
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(1) + 6);
			if (device->isSwitch == true)
			{
				if (device->isRouter == true)
					interfacePointer->switchportMode = portModeAccess;
				else
					interfacePointer->switchportMode = portModeDynamic;
			}
		}
		else if (strncasecmp(command->part(1), "hssi", 4) == 0)
		{
			interfaceListPointer = getInterfaceList("HSSIINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("*ABBREV*HSSI*-ABBREV* Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices *ABBREV*HSSI*-ABBREV* interfaces.");
				interfaceListPointer->tableTitle = i18n("*ABBREV*HSSI*-ABBREV* interfaces");
				interfaceListPointer->label = "HSSIINTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
				interfaceListPointer->inboundFilterSupported = true;					// Is the inbound filtering supported?
				interfaceListPointer->outboudFilterSupported = true;					// Is the outbound filtering supported?
				if (device->isSwitch == true)
				{
					interfaceListPointer->portModeSupported = true;
				}
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(1) + 4);
			if (device->isSwitch == true)
			{
				if (device->isRouter == true)
					interfacePointer->switchportMode = portModeAccess;
				else
					interfacePointer->switchportMode = portModeDynamic;
			}
		}
		else if (strncasecmp(command->part(1), "fddi", 4) == 0)
		{
			interfaceListPointer = getInterfaceList("FDDIINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("*ABBREV*FDDI*-ABBREV* Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices *ABBREV*FDDI*-ABBREV* interfaces.");
				interfaceListPointer->tableTitle = i18n("*ABBREV*FDDI*-ABBREV* interfaces");
				interfaceListPointer->label = "FDDIINTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
				interfaceListPointer->inboundFilterSupported = true;					// Is the inbound filtering supported?
				interfaceListPointer->outboudFilterSupported = true;					// Is the outbound filtering supported?
				if (device->isSwitch == true)
				{
					interfaceListPointer->portModeSupported = true;
				}
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(1) + 4);
			if (device->isSwitch == true)
			{
				if (device->isRouter == true)
					interfacePointer->switchportMode = portModeAccess;
				else
					interfacePointer->switchportMode = portModeDynamic;
			}
		}
		else if (strncasecmp(command->part(1), "Dot11Radio", 10) == 0)
		{
			interfaceListPointer = getInterfaceList("WIRELESSINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("Wireless Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices wireless interfaces.");
				interfaceListPointer->tableTitle = i18n("Wireless interfaces");
				interfaceListPointer->label = "WIRELESSINTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
				interfaceListPointer->inboundFilterSupported = true;					// Is the inbound filtering supported?
				interfaceListPointer->outboudFilterSupported = true;					// Is the outbound filtering supported?
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(1) + 10);
		}
		else if (strncasecmp(command->part(1), "Dialer", 6) == 0)
		{
			interfaceListPointer = getInterfaceList("DIALINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("Dialer Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices dialer interfaces.");
				interfaceListPointer->tableTitle = i18n("Dialer interfaces");
				interfaceListPointer->label = "DIALINTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
				interfaceListPointer->inboundFilterSupported = true;					// Is the inbound filtering supported?
				interfaceListPointer->outboudFilterSupported = true;					// Is the outbound filtering supported?
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(1) + 6);
		}
		else if (strncasecmp(command->part(1), "BRI", 3) == 0)
		{
			interfaceListPointer = getInterfaceList("ISDNINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("*ABBREV*ISDN*-ABBREV* Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices *ABBREV*ISDN*-ABBREV* interfaces.");
				interfaceListPointer->tableTitle = i18n("*ABBREV*ISDN*-ABBREV* interfaces");
				interfaceListPointer->label = "ISDNINTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
				interfaceListPointer->inboundFilterSupported = true;					// Is the inbound filtering supported?
				interfaceListPointer->outboudFilterSupported = true;					// Is the outbound filtering supported?
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(1) + 3);
		}
		else if (strncasecmp(command->part(1), "POS", 3) == 0)
		{
			interfaceListPointer = getInterfaceList("POSINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("*ABBREV*POS*-ABBREV* Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices *ABBREV*POS*-ABBREV* interfaces.");
				interfaceListPointer->tableTitle = i18n("*ABBREV*POS*-ABBREV* interfaces");
				interfaceListPointer->label = "POSINTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
				interfaceListPointer->inboundFilterSupported = true;					// Is the inbound filtering supported?
				interfaceListPointer->outboudFilterSupported = true;					// Is the outbound filtering supported?
				if (device->isSwitch == true)
				{
					interfaceListPointer->portModeSupported = true;
				}
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(1) + 3);
			if (device->isSwitch == true)
			{
				if (device->isRouter == true)
					interfacePointer->switchportMode = portModeAccess;
				else
					interfacePointer->switchportMode = portModeDynamic;
			}
		}
		else if (strncasecmp(command->part(1), "ATM", 3) == 0)
		{
			interfaceListPointer = getInterfaceList("ATMINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("*ABBREV*ATM*-ABBREV* Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices *ABBREV*ATM*-ABBREV* interfaces.");
				interfaceListPointer->tableTitle = i18n("*ABBREV*ATM*-ABBREV* interfaces");
				interfaceListPointer->label = "ATMINTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
				interfaceListPointer->inboundFilterSupported = true;					// Is the inbound filtering supported?
				interfaceListPointer->outboudFilterSupported = true;					// Is the outbound filtering supported?
				if (device->isSwitch == true)
				{
					interfaceListPointer->portModeSupported = true;
				}
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(1) + 3);
			if (device->isSwitch == true)
			{
				if (device->isRouter == true)
					interfacePointer->switchportMode = portModeAccess;
				else
					interfacePointer->switchportMode = portModeDynamic;
			}
		}
		else if (strncasecmp(command->part(1), "Tunnel", 6) == 0)
		{
			interfaceListPointer = getInterfaceList("TUNINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("Tunnel Interfaces");
				interfaceListPointer->description = i18n("Tunnel interfaces are virtual interfaces. This section describes the configuration of the tunnel interfaces.");
				interfaceListPointer->tableTitle = i18n("Tunnel interfaces");
				interfaceListPointer->label = "TUNINTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
				interfaceListPointer->inboundFilterSupported = true;					// Is the inbound filtering supported?
				interfaceListPointer->outboudFilterSupported = true;					// Is the outbound filtering supported?
				if (device->isSwitch == true)
				{
					interfaceListPointer->portModeSupported = true;
				}
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(1) + 6);
			if (device->isSwitch == true)
			{
				if (device->isRouter == true)
					interfacePointer->switchportMode = portModeAccess;
				else
					interfacePointer->switchportMode = portModeDynamic;
			}
		}
		else if (strncasecmp(command->part(1), "Port-channel", 12) == 0)
		{
			interfaceListPointer = getInterfaceList("PORTINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("Port Channel Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the port channel interfaces.");
				interfaceListPointer->tableTitle = i18n("Port channel interfaces");
				interfaceListPointer->label = "PORTINTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
				interfaceListPointer->inboundFilterSupported = true;					// Is the inbound filtering supported?
				interfaceListPointer->outboudFilterSupported = true;					// Is the outbound filtering supported?
				if (device->isSwitch == true)
				{
					interfaceListPointer->portModeSupported = true;
				}
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(1) + 12);
			if (device->isSwitch == true)
			{
				if (device->isRouter == true)
					interfacePointer->switchportMode = portModeAccess;
				else
					interfacePointer->switchportMode = portModeDynamic;
			}
		}
		else
		{
			interfaceListPointer = getInterfaceList("OTHERINTERFACES");
			if (interfaceListPointer == 0)
			{
				interfaceListPointer = addInterfaceList();
				interfaceListPointer->title = i18n("Other Interfaces");
				interfaceListPointer->description = i18n("This section describes the configuration of the other interfaces configured on *DEVICENAME*.");
				interfaceListPointer->tableTitle = i18n("Other interfaces");
				interfaceListPointer->label = "OTHERINTERFACES";
				interfaceListPointer->interfaceDisableSupport = true;				// Is it possible to disable interfaces?
				interfaceListPointer->ipAddressSupported = true;					// Are addresses supported?
				interfaceListPointer->inboundFilterSupported = true;					// Is the inbound filtering supported?
				interfaceListPointer->outboudFilterSupported = true;					// Is the outbound filtering supported?
			}
			interfacePointer = getInterface(interfaceListPointer, command->part(1));
		}

		// Read a line from the config...
		device->readLine(line, lineSize);

		// Split it up into parts...
		command->setConfigLine(line);

		while ((line[0] != '!') && (feof(device->inputFile) == 0))
		{

			if (strcmp(command->part(0), "no") == 0)
			{
				setting = false;
				tempInt = 1;
			}
			else
			{
				setting = true;
				tempInt = 0;
			}

			// IP
			if (strcmp(command->part(tempInt), "ip") == 0)
			{
				tempInt++;

				// address...
				if (strcmp(command->part(1), "address") == 0)
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sInterface IP address Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
					interfacePointer->address.assign(command->part(2));
					interfacePointer->netmask.assign(command->part(3));
				}

				else if (strcmp(command->part(1), "access-group") == 0)
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sInterface ACL Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
					if (strcmp(command->part(3), "in") == 0)
						addFilterList(interfacePointer, command->part(2), true);
					else
						addFilterList(interfacePointer, command->part(2), false);
				}

				else if (strcmp(command->part(tempInt), "proxy-arp") == 0)
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sInterface Proxy ARP Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
					interfacePointer->proxyARP = setting;
				}

				else if (strcmp(command->part(tempInt), "unreachables") == 0)
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sInterface IP Unreachables Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
					interfacePointer->ipUnreachables = setting;
				}

				else if (strcmp(command->part(tempInt), "redirects") == 0)
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sInterface IP Redirect Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
					interfacePointer->ipRedirects = setting;
				}

				else if (strcmp(command->part(tempInt), "mask-reply") == 0)
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sInterface IP Mask Reply Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
					interfacePointer->ipMaskReply = setting;
				}

				else if (strcmp(command->part(tempInt), "information-reply") == 0)
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sInterface IP Information Reply Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
					interfacePointer->infoReply = setting;
				}

				else if (strcmp(command->part(tempInt), "directed-broadcast") == 0)
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sInterface IP Directed Broadcast Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
					if (setting == true)
					{
						if (command->parts == 2)
							interfacePointer->ipDirectBroadcast.assign(i18n("On"));
						else
						{
							tempString.assign(i18n("On ("));
							tempString.append(command->part(2));
							tempString.append(")");
							interfacePointer->ipDirectBroadcast.assign(tempString);
						}
					}
				}

				// All others...
				else
					device->lineNotProcessed(line);
			}

			// shutdown...
			else if (strcmp(command->part(0), "shutdown") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sInterface Shutdown Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				interfacePointer->enabled = false;
			}

			// switchport...
			else if ((strcmp(command->part(0), "switchport") == 0) && (strcmp(command->part(1), "mode") == 0) && ((strcmp(command->part(2), "access") == 0) || (strcmp(command->part(2), "dynamic") == 0) || (strcmp(command->part(2), "trunk") == 0)))
			{
				device->isSwitch = true;

				if (device->config->reportFormat == Config::Debug)
					printf("%sSwitchport mode Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (strcmp(command->part(2), "access") == 0)
					interfacePointer->switchportMode = portModeAccess;
				else if (strcmp(command->part(2), "dynamic") == 0)
					interfacePointer->switchportMode = portModeDynamic;
				else
					interfacePointer->switchportMode = portModeTrunk;
			}
			else if ((strcmp(command->part(0), "switchport") == 0) && (strcmp(command->part(1), "port-security") == 0) && (command->parts == 2))
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sSwitchport port-security Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				interfacePointer->switchportSecurity = true;
				interfaceListPointer->portSecuritySupported = true;
			}
			else if ((strcmp(command->part(0), "switchport") == 0) && (strcmp(command->part(1), "access") == 0) && (strcmp(command->part(2), "vlan") == 0))
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sSwitchport VLAN Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				addVLAN(interfacePointer, command->part(3));
			}
			else if ((strcmp(command->part(0), "switchport") == 0) && (strcmp(command->part(1), "port-security") == 0) && (strcmp(command->part(2), "violation") == 0))
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sSwitchport port-security  Violation Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

				if (strcmp(command->part(3), "restrict") == 0)
					interfacePointer->switchportViolation = onViolationRestrict;
				else if (strcmp(command->part(3), "protect") == 0)
					interfacePointer->switchportViolation = onViolationProtect;
				else
					interfacePointer->switchportViolation = onViolationShutdown;
				interfaceListPointer->portSecuritySupported = true;
			}
			else if (strcmp(command->part(tempInt), "switchport") == 0)
			{
				device->isSwitch = true;
				device->lineNotProcessed(line);
			}

			// Description
			else if (strcmp(command->part(0), "description") == 0)
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sInterface Description Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				interfacePointer->description.assign(strstr(line, command->part(1)));
			}

			// mop
			else if ((strcmp(command->part(tempInt), "mop") == 0) && (strncmp(command->part(tempInt + 1), "enable", 6) != 0))
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sInterface MOP Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				interfacePointer->mop = setting;
			}

			// cdp
			else if ((strcmp(command->part(tempInt), "cdp") == 0) && (strcmp(command->part(tempInt + 1), "enable") == 0))
			{
				if (device->config->reportFormat == Config::Debug)
					printf("%sInterface CDP Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
				interfacePointer->cdp = setting;
			}

			// NOT PROCESSED...
			else
				device->lineNotProcessed(line);

			// Read a line from the config...
			device->readLine(line, lineSize);

			// Split it up into parts...
			command->setConfigLine(line);
		}
	}

	// All others...
	else
		device->lineNotProcessed(line);

	return 0;
}


int IOSInterfaces::processDefaults(Device *device)
{
	interfaceListConfig *interfaceListPointer = 0;
	interfaceConfig *interfacePointer = 0;

	interfaceListPointer = interfaceList;
	while (interfaceListPointer != 0)
	{
		interfacePointer = interfaceListPointer->interface;
		while (interfacePointer != 0)
		{
			if (interfacePointer->vlan == 0)
				addVLAN(interfacePointer, "1");
			interfacePointer = interfacePointer->next;
		}
		interfaceListPointer = interfaceListPointer->next;
	}

	return 0;
}


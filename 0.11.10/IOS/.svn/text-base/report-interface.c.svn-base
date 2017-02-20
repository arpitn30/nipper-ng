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

// This file contains the code for IOS reporting

void iosSwitchportConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct interfaceConfig *interfaceConfigPointer = 0;

	output_table(nipper, true, settings_switchport_table, &settings_switchport_heading);
	interfaceConfigPointer = nipper->ios->interface;
	while (interfaceConfigPointer != 0)
	{
		if ((strncasecmp(interfaceConfigPointer->name, "Vlan", 4) != 0) && (strncasecmp(interfaceConfigPointer->name, "Loop", 4) != 0))
		{
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, interfaceConfigPointer->name, nipper->tablerow_mid);
			if (interfaceConfigPointer->shutdown == true)
				fprintf(nipper->reportFile, "No%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_mid);
			fprintf(nipper->reportFile, "%s%s", interfaceConfigPointer->description, nipper->tablerow_mid);
			fprintf(nipper->reportFile, "%d%s", interfaceConfigPointer->switchportVLAN, nipper->tablerow_mid);
			switch (interfaceConfigPointer->switchportMode)
			{
				case sp_mode_access:
					fprintf(nipper->reportFile, "Access%s", nipper->tablerow_mid);
					break;
				case sp_mode_trunk:
					fprintf(nipper->reportFile, "Trunk%s", nipper->tablerow_mid);
					break;
				case sp_mode_dynamic:
					fprintf(nipper->reportFile, "Dynamic%s", nipper->tablerow_mid);
					break;
				case sp_mode_dot1qtunnel:
					fprintf(nipper->reportFile, "802.1q Tunnel%s", nipper->tablerow_mid);
					break;
				case sp_mode_pvlan_host:
					fprintf(nipper->reportFile, "Host%s", nipper->tablerow_mid);
					break;
				case sp_mode_pvlan_promiscuous:
					fprintf(nipper->reportFile, "Promiscuous%s", nipper->tablerow_mid);
					break;
			}
			if (interfaceConfigPointer->switchportSecurity == true)
				fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
			switch (interfaceConfigPointer->switchportViolation)
			{
				case sp_violation_shutdown:
					fprintf(nipper->reportFile, "Shutdown%s", nipper->tablerow_end);
					break;
				case sp_violation_restrict:
					fprintf(nipper->reportFile, "Restrict%s", nipper->tablerow_end);
					break;
				case sp_violation_protect:
					fprintf(nipper->reportFile, "Protect%s", nipper->tablerow_end);
					break;
			}
		}
		interfaceConfigPointer = interfaceConfigPointer->next;
	}
	output_table(nipper, false, settings_switchport_table, &settings_switchport_heading);
	addAbbreviation("PVLAN", false);
	addAbbreviation("VLAN", false);
}


void iosInterfacesConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct interfaceConfig *interfaceConfigPointer = 0;

	if (nipper->deviceType == type_ios_router)
		output_table(nipper, true, settings_inter_table, &settings_interIOS_heading);
	else
		output_table(nipper, true, settings_inter_table, &settings_interIOSswitch_heading);
	interfaceConfigPointer = nipper->ios->interface;
	while (interfaceConfigPointer != 0)
	{
		fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, interfaceConfigPointer->name, nipper->tablerow_mid);
		if (interfaceConfigPointer->shutdown == true)
			fprintf(nipper->reportFile, "No%s%s%s", nipper->tablerow_mid, interfaceConfigPointer->ipAddress, nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "Yes%s%s%s", nipper->tablerow_mid, interfaceConfigPointer->ipAddress, nipper->tablerow_mid);
		if (strcmp(interfaceConfigPointer->ipAddress, "None") != 0)
		{
			if (interfaceConfigPointer->proxyArp == true)
				fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
			if (interfaceConfigPointer->ipUnreachables == true)
				fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
			if (interfaceConfigPointer->ipRedirects == true)
				fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
			if (interfaceConfigPointer->ipMaskReply == true)
				fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
			if (interfaceConfigPointer->ipDirectBroadcast == true)
				fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
			else if (interfaceConfigPointer->ipDirectBroadcast == false)
				fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "Default%s", nipper->tablerow_mid);
			if (interfaceConfigPointer->ntp == true)
				fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
			if ((strncmp(interfaceConfigPointer->name,"Loopback", 8) == 0) || (strncmp(interfaceConfigPointer->name, "Vlan", 4) == 0))
				fprintf(nipper->reportFile, "N/A%s", nipper->tablerow_mid);
			else if (interfaceConfigPointer->cdp == true)
				fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
		}
		else
		{
			fprintf(nipper->reportFile, "N/A%s", nipper->tablerow_mid);
			fprintf(nipper->reportFile, "N/A%s", nipper->tablerow_mid);
			fprintf(nipper->reportFile, "N/A%s", nipper->tablerow_mid);
			fprintf(nipper->reportFile, "N/A%s", nipper->tablerow_mid);
			fprintf(nipper->reportFile, "N/A%s", nipper->tablerow_mid);
			fprintf(nipper->reportFile, "N/A%s", nipper->tablerow_mid);
			fprintf(nipper->reportFile, "N/A%s", nipper->tablerow_mid);
		}
		if (nipper->deviceType == type_ios_router)
		{
			if (interfaceConfigPointer->uRPF == true)
				fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
		}
		if (strcmp(interfaceConfigPointer->ipAddress, "None") != 0)
		{
			if ((strncmp(interfaceConfigPointer->name, "Loopback", 8) == 0) || (strchr(interfaceConfigPointer->name, '.') != 0))
				fprintf(nipper->reportFile, "N/A%s", nipper->tablerow_end);
			else if (interfaceConfigPointer->mop == true)
				fprintf(nipper->reportFile, "On%s", nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "Off%s", nipper->tablerow_end);
		}
		else
			fprintf(nipper->reportFile, "N/A%s", nipper->tablerow_end);
		interfaceConfigPointer = interfaceConfigPointer->next;
	}
	if (nipper->deviceType == type_ios_router)
		output_table(nipper, false, settings_inter_table, &settings_interIOS_heading);
	else
		output_table(nipper, false, settings_inter_table, &settings_interIOSswitch_heading);
	addAbbreviation("ARP", false);
	addAbbreviation("NTP", false);
	addAbbreviation("CDP", false);
	addAbbreviation("MOP", false);
	addAbbreviation("uRPF", false);
}


void iosIPDirectedIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct interfaceConfig *interfaceConfigPointer = 0;
	char tempString[nipper->maxSize];

	output_parseText(report_ipdirected_obs, nipper, section_obs, rate_none, nipper->ipDirectedIssues, nipper->tableNum);
	if (nipper->ipDirectedIssues == 1)
	{
		
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->ipDirectBroadcast == true) && (interfaceConfigPointer->shutdown == false) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
				fprintf(nipper->reportFile, "%s", interfaceConfigPointer->name);
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		fprintf(nipper->reportFile, ".");
		output_newPara(nipper);
	}
	else
	{
		output_table(nipper, true, report_ipdirected_table, &report_interface_heading);
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->ipDirectBroadcast == true) && (interfaceConfigPointer->shutdown == false) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
			{
				outputFriendly(interfaceConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
				outputFriendly(interfaceConfigPointer->description, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_end);
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		output_table(nipper, false, report_ipdirected_table, &report_interface_heading);
	}
	output_endsection(nipper, section_obs);
	output_parseText(report_ipdirected_impact, nipper, section_imp, rate_high, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_ipdirected_ease, nipper, section_ease, rate_trivial, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_ipdirected_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosTrunkingIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct interfaceConfig *interfaceConfigPointer = 0;
	char tempString[nipper->maxSize];

	output_parseText(report_trunking_obs1, nipper, section_obs, rate_none, nipper->switchportModeIssues, nipper->tableNum);
	if (nipper->switchportModeIssues == 1)
	{
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->switchportMode != sp_mode_access) && (interfaceConfigPointer->shutdown == false) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0) && (strncmp(interfaceConfigPointer->name, "Vlan", 4) != 0))
			{
				outputFriendly(interfaceConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s", tempString);
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		output_parseText(report_trunking_obs2, nipper, section_none, rate_none, nipper->switchportModeIssues, nipper->tableNum);
	}
	else
	{
		output_table(nipper, true, report_trunking_table, &report_interface_heading);
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->switchportMode != sp_mode_access) && (interfaceConfigPointer->shutdown == false) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0) && (strncmp(interfaceConfigPointer->name, "Vlan", 4) != 0))
			{
				outputFriendly(interfaceConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
				outputFriendly(interfaceConfigPointer->description, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s %s", tempString, nipper->tablerow_end);
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		output_table(nipper, false, report_trunking_table, &report_interface_heading);
	}
	output_endsection(nipper, section_obs);
	output_parseText(report_trunking_impact, nipper, section_imp, rate_medhigh, nipper->switchportModeIssues, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_trunking_ease, nipper, section_ease, rate_moderate, nipper->switchportModeIssues, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_trunking_rec, nipper, section_rec, rate_none, nipper->switchportModeIssues, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosPortSecurityIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct interfaceConfig *interfaceConfigPointer = 0;
	char tempString[nipper->maxSize];

	output_parseText(report_portsecurity_obs1, nipper, section_obs, rate_none, nipper->switchportIssues, nipper->tableNum);
	if (nipper->switchportIssues == 1)
	{
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->switchportSecurity == false) && (interfaceConfigPointer->shutdown == false) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0) && (strncmp(interfaceConfigPointer->name, "Vlan", 4) != 0))
			{
				outputFriendly(interfaceConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s", tempString);
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		output_parseText(report_portsecurity_obs2, nipper, section_none, rate_none, nipper->switchportIssues, nipper->tableNum);
	}
	else
	{
		output_table(nipper, true, report_portsecurity_table, &report_interface_heading);
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->switchportSecurity == false) && (interfaceConfigPointer->shutdown == false) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0) && (strncmp(interfaceConfigPointer->name, "Vlan", 4) != 0))
			{
				outputFriendly(interfaceConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
				outputFriendly(interfaceConfigPointer->description, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s %s", tempString, nipper->tablerow_end);
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		output_table(nipper, false, report_portsecurity_table, &report_interface_heading);
	}
	output_endsection(nipper, section_obs);
	output_parseText(report_portsecurity_impact, nipper, section_imp, rate_medhigh, nipper->switchportIssues, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_portsecurity_ease, nipper, section_ease, rate_moderate, nipper->switchportIssues, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_portsecurity_rec, nipper, section_rec, rate_none, nipper->switchportIssues, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosProxyARPIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct interfaceConfig *interfaceConfigPointer = 0;
	char tempString[nipper->maxSize];

	output_parseText(report_proxyarp_obs, nipper, section_obs, rate_none, nipper->proxyArpIssues, nipper->tableNum);
	if (nipper->proxyArpIssues > 1)
	{
		output_table(nipper, true, report_proxyarp_table, &report_interface_heading);
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->proxyArp == true) && (interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
			{
				outputFriendly(interfaceConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
				outputFriendly(interfaceConfigPointer->description, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s %s", tempString, nipper->tablerow_end);
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		output_table(nipper, false, report_proxyarp_table, &report_interface_heading);
	}
	else
	{
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->proxyArp == true) && (interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
				fprintf(nipper->reportFile, "%s.", interfaceConfigPointer->name);
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		output_newPara(nipper);
	}
	output_endsection(nipper, section_obs);
	output_parseText(report_proxyarp_impact, nipper, section_imp, rate_lowmed, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_proxyarp_ease, nipper, section_ease, rate_trivial, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_proxyarp_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosCDPIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct interfaceConfig *interfaceConfigPointer = 0;

	// Look to see if CDP has been disabled on the network interfaces
	int cdpDisabled = true;
	interfaceConfigPointer = nipper->ios->interface;
	while ((interfaceConfigPointer != 0) && (cdpDisabled == true))
	{
		if ((interfaceConfigPointer->cdp == true) && (interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0))
			cdpDisabled = false;
		interfaceConfigPointer = interfaceConfigPointer->next;
	}
	// If CDP has been disabled on all interfaces...
	if (cdpDisabled == true)
		output_parseText(report_cdp_obs, nipper, section_obs, rate_none, 1, nipper->tableNum);
	else
		output_parseText(report_cdp_obs, nipper, section_obs, rate_none, 2, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_cdp_impact, nipper, section_imp, rate_lowmed, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_cdp_ease, nipper, section_ease, rate_trivial, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_cdp_rec1, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosIPUnreachablesIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct interfaceConfig *interfaceConfigPointer = 0;
	char tempString[nipper->maxSize];

	output_parseText(report_icmpunreach_obs, nipper, section_obs, rate_none, nipper->unreachIssues, nipper->tableNum);
	if (nipper->unreachIssues == 1)
	{
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->ipUnreachables == true) && (interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
				fprintf(nipper->reportFile, "%s", interfaceConfigPointer->name);
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		fprintf(nipper->reportFile, ".");
		output_newPara(nipper);
	}
	else
	{
		output_table(nipper, true, report_icmpunreach_table, &report_interface_heading);
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->ipUnreachables == true) && (interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
			{
				outputFriendly(interfaceConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
				outputFriendly(interfaceConfigPointer->description, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_end);
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		output_table(nipper, false, report_icmpunreach_table, &report_interface_heading);
	}
	output_endsection(nipper, section_obs);
	output_parseText(report_icmpunreach_impact, nipper, section_imp, rate_low, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_icmpunreach_ease, nipper, section_ease, rate_trivial, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_icmpunreach_rec1, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosMaskReplyIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct interfaceConfig *interfaceConfigPointer = 0;
	char tempString[nipper->maxSize];

	output_parseText(report_maskreply_obs, nipper, section_obs, rate_none, nipper->maskReplyIssues, nipper->tableNum);
	if (nipper->maskReplyIssues == 1)
	{
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->ipMaskReply == true) && (interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
				fprintf(nipper->reportFile, "%s", interfaceConfigPointer->name);
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		fprintf(nipper->reportFile, ".");
		output_newPara(nipper);
	}
	else
	{
		output_table(nipper, true, report_maskreply_table, &report_interface_heading);
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->ipMaskReply == true) && (interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
			{
				outputFriendly(interfaceConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
				outputFriendly(interfaceConfigPointer->description, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_end);
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		output_table(nipper, false, report_icmpunreach_table, &report_interface_heading);
	}
	output_endsection(nipper, section_obs);
	output_parseText(report_maskreply_impact, nipper, section_imp, rate_low, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_maskreply_ease, nipper, section_ease, rate_trivial, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_maskreply_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosMOPIssue(struct nipperConfig *nipper)
{
	output_parseText(report_mop_obs, nipper, section_obs, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_mop_impact, nipper, section_imp, rate_low, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_mop_ease, nipper, section_ease, rate_noease, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_mop_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}

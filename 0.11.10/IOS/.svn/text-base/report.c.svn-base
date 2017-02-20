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

// Report IOS includes...
#include "report-aaa.c"
#include "report-access-list.c"
#include "report-clock.c"
#include "report-debug.c"
#include "report-dns.c"
#include "report-ftp.c"
#include "report-general.c"
#include "report-http.c"
#include "report-interface.c"
#include "report-keychain.c"
#include "report-line.c"
#include "report-logging.c"
#include "report-nat.c"
#include "report-ntp.c"
#include "report-passwords.c"
#include "report-router.c"
#include "report-snmp.c"
#include "report-ssh.c"
#include "report-tacacs.c"
#include "report-timeout.c"
#include "report-username.c"
#include "report-vtp.c"


void generateIOSReport(struct nipperConfig *nipper)
{
	// Variables
	struct enablePassword *enablePointer = 0;
	struct snmpGroup *snmpGroupPointer = 0;
	struct interfaceConfig *interfaceConfigPointer = 0;
	struct ospfAreaConfig *ospfAreaPointer = 0;
	struct ospfConfig *ospfPointer = 0;
	//struct eigrpConfig *eigrpPointer = 0;
	struct eigrpAutonStruct *eigrpAutonPointer = 0;
	struct lineConfig *linePointer = 0;
	struct vulnerability *vulnPointer = 0;
	struct vrrpStruct *vrrpPointer = 0;
	int tempInt = 0;
	//int tempInt2 = 0;

	// Security Report section
	if (nipper->fullReport == true)
	{

		// Software Version
		if ((nipper->versionMajor < 12) || ((nipper->versionMajor == 12) && (((nipper->deviceType != type_ios_catalyst) && (nipper->versionMinor < 4)) || ((nipper->deviceType == type_ios_catalyst) && (nipper->versionMinor < 2)))))
		{
			nipper->vulnIssues = 0;
			nipper->vulnIssueDos = false;
			nipper->vulnIssueRemote = false;
			vulnPointer = &report_vuln_ios;
			while (vulnPointer->next != 0)
			{
				checkVulnVersion(nipper, vulnPointer);
				vulnPointer = vulnPointer->next;
			}
			if (nipper->vulnIssues > 0)
				addReportSection(nipper, section_security, report_osver_title, report_osver_context, report_osver_rectext, 10, 8, 5, 3, iosVulnIssue);
		}

		// Simple Passwords
		if (nipper->simplePasswords > 1)
			addReportSection(nipper, section_security, report_dict_title1, report_dict_context, report_dict_rectext, 10, 8, 5, 3, iosDictionaryIssue);
		else if (nipper->simplePasswords > 0)
			addReportSection(nipper, section_security, report_dict_title2, report_dict_context, report_dict_rectext, 10, 8, 5, 3, iosDictionaryIssue);

		// Password Strength
		if (nipper->passwordStrengths > 1)
			addReportSection(nipper, section_security, report_strength_title1, report_strength_context, report_strength_rectext, 10, 8, 5, 3, iosStrengthIssue);
		else if (nipper->passwordStrengths > 0)
			addReportSection(nipper, section_security, report_strength_title2, report_strength_context, report_strength_rectext, 10, 8, 5, 3, iosStrengthIssue);

		// Auto configuration
		if ((nipper->ios->bootNetwork == true) || (nipper->ios->serviceConfig == true))
			addReportSection(nipper, section_security, report_configauto_title, report_configauto_context, report_configauto_rectext, 10, 8, 5, 3, iosAutoConfigIssue);

		// IP directed broadcasts
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->ipDirectBroadcast == true) && (interfaceConfigPointer->shutdown == false) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
				nipper->ipDirectedIssues++;
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		if (nipper->ipDirectedIssues > 0)
			addReportSection(nipper, section_security, report_ipdirected_title, report_ipdirected_context, report_ipdirected_rectext, 10, 8, 5, 3, iosIPDirectedIssue);

		// BGP Route Dampening
		if (nipper->ios->bgp != 0)
		{
			if (nipper->ios->bgp->dampening != true)
				addReportSection(nipper, section_security, report_bgpdamp_title, report_bgpdamp_context, report_bgpdamp_rectext, 10, 8, 5, 3, iosBGPDampeningIssue);
		}

		// OSPF Authentication
		ospfPointer = nipper->ios->ospf;
		while (ospfPointer !=0)
		{
			ospfAreaPointer = nipper->ios->ospf->ospfArea;
			if (ospfAreaPointer == 0)
				nipper->ospfAuthNoneIssues++;
			while (ospfAreaPointer != 0)
			{
				if (ospfAreaPointer->areaAuth == auth_none)
					nipper->ospfAuthNoneIssues++;
				else if (ospfAreaPointer->areaAuth == auth_clear)
					nipper->ospfAuthClearIssues++;
				else
					nipper->ospfAuthMD5++;
				ospfAreaPointer = ospfAreaPointer->next;
			}
			ospfPointer = ospfPointer->next;
		}
		if ((nipper->ospfAuthNoneIssues > 0) || (nipper->ospfAuthClearIssues > 0))
			addReportSection(nipper, section_security, report_ospfauth_title, report_ospfauth_context, report_ospfauth_rectext, 10, 8, 5, 3, iosOSPFAuthenticationIssue);

		// EIGRP
		if (nipper->ios->eigrp != 0)
		{
			//tempInt2 = 0;
			//eigrpPointer = nipper->ios->eigrp;
			//while (eigrpPointer != 0)
			//{
			//	tempInt2++;
			//	eigrpPointer = eigrpPointer->next;
			//}
			interfaceConfigPointer = nipper->ios->interface;
			while (interfaceConfigPointer != 0)
			{
				if ((interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
				{
					//tempInt = tempInt2;
					eigrpAutonPointer = interfaceConfigPointer->eigrp;
					while (eigrpAutonPointer != 0)
					{
						if ((eigrpAutonPointer->md5Auth == false) && (eigrpAutonPointer->passive != true))
							nipper->eigrpIssues++;
						eigrpAutonPointer = eigrpAutonPointer->next;
					}
					//if (tempInt > 0)
					//	nipper->eigrpIssues++;
				}
				interfaceConfigPointer = interfaceConfigPointer->next;
			}
			if (nipper->eigrpIssues > 0)
				addReportSection(nipper, section_security, report_eigrpauth_title, report_eigrpauth_context, report_eigrpauth_rectext, 10, 8, 5, 3, iosEIGRPIssue);
		}

		// RIP
		if (nipper->ios->rip != 0)
		{
			interfaceConfigPointer = nipper->ios->interface;
			while (interfaceConfigPointer != 0)
			{
				if (((interfaceConfigPointer->ripKeyChain[0] == 0) || (interfaceConfigPointer->ripAuthMode != rip_auth_md5) || (interfaceConfigPointer->ripSendVersion != rip_version2) || (interfaceConfigPointer->ripReceiveVersion != rip_version2)) && (interfaceConfigPointer->ripPassive == false) && (interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
					nipper->ripIssues++;
				interfaceConfigPointer = interfaceConfigPointer->next;
			}
			if (nipper->ripIssues > 0)
				addReportSection(nipper, section_security, report_rip_title, report_rip_context, report_rip_rectext, 10, 8, 5, 3, iosRIPIssue);
		}

		// VRRP
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			vrrpPointer = interfaceConfigPointer->vrrp;
			while (vrrpPointer != 0)
			{
				if ((interfaceConfigPointer->shutdown == false) && (vrrpPointer->shutdown == false) && (vrrpPointer->authentication != vrrp_auth_md5))
					nipper->vrrpIssues++;
				vrrpPointer = vrrpPointer->next;
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		if (nipper->vrrpIssues > 0)
			addReportSection(nipper, section_security, report_vrrp_title, report_vrrp_context, report_vrrp_rectext, 10, 8, 5, 3, iosVRRPIssue);

		// TCP Keep Alives
		if (nipper->ios->keepAlivesIn == false)
			addReportSection(nipper, section_security, report_keepalive_title, report_keepalive_context, report_keepalive_rectext, 10, 8, 5, 3, iosKeepAlivesIssue);

		// Connection Timeout
		linePointer = nipper->ios->line;
		while (linePointer != 0)
		{
			if ((linePointer->login != login_disabled) && ((linePointer->timeout == 0) || (linePointer->timeout > nipper->connectionTimeout)) && ((linePointer->absoluteTimeout == 0) || (linePointer->absoluteTimeout > nipper->connectionTimeout)) && ((linePointer->sessionTimeout == 0) || (linePointer->sessionTimeout > nipper->connectionTimeout)) && ((linePointer->execTimeout == 0) || (linePointer->execTimeout > nipper->connectionTimeout)))
				nipper->insecureTimeouts++;
			linePointer = linePointer->next;
		}
		if (nipper->insecureTimeouts > 0)
			addReportSection(nipper, section_security, report_timeout_title, report_timeout_context, report_timeout_rectext, 10, 8, 5, 3, iosTimeoutIssue);

		// Aux port
		tempInt = 0;
		linePointer = nipper->ios->line;
		while (linePointer != 0)
		{
			if ((linePointer->callback == false) && (linePointer->login != login_disabled) && (linePointer->exec == true) && (linePointer->lineType == line_aux))
				tempInt++;
			linePointer = linePointer->next;
		}
		if (tempInt > 0)
			addReportSection(nipper, section_security, report_aux_title, report_aux_context, report_aux_rectext, 10, 8, 5, 3, iosAUXPortIssue);

		// Source Routing
		if ((nipper->ios->sourceRouting != false) && (nipper->deviceType == type_ios_router))
			addReportSection(nipper, section_security, report_source_title, report_source_context, report_source_rectext, 10, 8, 5, 3, iosSourceRoutingIssue);

		// Finger
		if (nipper->ios->finger != false)
			addReportSection(nipper, section_security, report_finger_title, report_finger_context, report_finger_rectext, 10, 8, 5, 3, iosFingerIssue);

		// HTTP
		tempInt = false;
		if (nipper->ios->http == 0)
			tempInt = true;
		else if (nipper->ios->http->enabled == true)
			tempInt = true;
		if (tempInt == true)
			addReportSection(nipper, section_security, report_http_title, report_http_context, report_http_rectext, 10, 8, 5, 3, iosHTTPIssue);

		// SNMP
		if (nipper->ios->snmp != 0)
		{
			if (nipper->ios->snmp->enabled == true)
			{
				if (nipper->ios->snmp->community != 0)
					nipper->snmpIssue = 1;
				snmpGroupPointer = nipper->ios->snmp->group;
				while (snmpGroupPointer != 0)
				{
					if (snmpGroupPointer->version == snmp1)
						nipper->snmpIssue = 1;
					else if ((snmpGroupPointer->version == snmp2c) && (nipper->snmpIssue != 1))
						nipper->snmpIssue = 2;
					else if (((snmpGroupPointer->version == snmp3_no_auth) || (snmpGroupPointer->version == snmp3_auth)) && (nipper->snmpIssue == 0))
						nipper->snmpIssue = -1;
					snmpGroupPointer = snmpGroupPointer->next;
				}
			}
		}
		if (nipper->snmpIssue != 0)
			addReportSection(nipper, section_security, report_snmp_title, report_snmp_context, report_snmp_rectext, 10, 8, 5, 3, iosSNMPIssue);

		// Telnet
		tempInt = false;
		linePointer = nipper->ios->line;
		while (linePointer != 0)
		{
			if ((linePointer->telnet == true) && (linePointer->exec == true) && (linePointer->login != login_disabled))
				tempInt = true;
			linePointer = linePointer->next;
		}
		if (tempInt == true)
			addReportSection(nipper, section_security, report_telnet_title, report_telnet_context, report_telnet_rectext, 10, 8, 5, 3, iosTelnetIssue);

		// Redirects
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->ipRedirects == true) && (interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
			{
				nipper->redirectsIssues++;
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		if (nipper->redirectsIssues > 0)
			addReportSection(nipper, section_security, report_redirects_title, report_redirects_context, report_redirects_rectext, 10, 8, 5, 3, iosRedirectsIssue);

		// Access Lists
		rulesAudit(nipper);
		if (nipper->aclIssues > 0)
			addReportSection(nipper, section_security, report_accesslist_title, report_accesslist_context, report_accesslist_rectext, 10, 8, 5, 3, ciscoACLIssue);

		// uRPF verification
		if ((nipper->versionMajor > 11) && (nipper->deviceType == type_ios_router) && (nipper->deviceUse == use_edge))
		{
			// If cef hasn't been enabled...
			if (nipper->ios->cef == false)
				nipper->uRPFIssues = -1;

			// Look for interfaces without uRPF on...
			else
			{
				interfaceConfigPointer = nipper->ios->interface;
				while (interfaceConfigPointer != 0)
				{
					if ((interfaceConfigPointer->uRPF == false) && (interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
						nipper->uRPFIssues++;
					interfaceConfigPointer = interfaceConfigPointer->next;
				}
			}
		}
		if (nipper->uRPFIssues != 0)
			addReportSection(nipper, section_security, report_urpf_title, report_urpf_context, report_urpf_rectext, 10, 8, 5, 3, iosURPFIssue);

		// Switch Port Mode
		if (nipper->deviceType != type_ios_router)
		{
			interfaceConfigPointer = nipper->ios->interface;
			while (interfaceConfigPointer != 0)
			{
				if ((interfaceConfigPointer->switchportMode != sp_mode_access) && (interfaceConfigPointer->shutdown == false) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0) && (strncmp(interfaceConfigPointer->name, "Vlan", 4) != 0))
					nipper->switchportModeIssues++;
				interfaceConfigPointer = interfaceConfigPointer->next;
			}
		}
		if (nipper->switchportModeIssues > 0)
			addReportSection(nipper, section_security, report_trunking_title, report_trunking_context, report_trunking_rectext, 10, 8, 5, 3, iosTrunkingIssue);

		// Switch Port Security
		if (nipper->deviceType != type_ios_router)
		{
			interfaceConfigPointer = nipper->ios->interface;
			while (interfaceConfigPointer != 0)
			{
				if ((interfaceConfigPointer->switchportSecurity == false) && (interfaceConfigPointer->shutdown == false) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0) && (strncmp(interfaceConfigPointer->name, "Vlan", 4) != 0))
					nipper->switchportIssues++;
				interfaceConfigPointer = interfaceConfigPointer->next;
			}
		}
		if (nipper->switchportIssues > 0)
			addReportSection(nipper, section_security, report_portsecurity_title, report_portsecurity_context, report_portsecurity_rectext, 10, 8, 5, 3, iosPortSecurityIssue);

		// Logging
		if (nipper->ios->logging == 0)
			nipper->loggingIssue = -1;
		else
		{
			if (nipper->ios->logging->logging == false)
				nipper->loggingIssue = 1;
			else if ((nipper->ios->logging->logServer == 0) && (nipper->ios->logging->bufferedLogging == 0))
				nipper->loggingIssue = 2;
			else if (nipper->ios->logging->logServer == 0)
				nipper->loggingIssue = 3;
			else if (nipper->ios->logging->bufferedLogging == 0)
				nipper->loggingIssue = 4;
		}
		if (nipper->loggingIssue != 0)
			addReportSection(nipper, section_security, report_logging_title, report_logging_context, report_logging_rectext, 10, 8, 5, 3, iosLoggingIssue);

		// Proxy ARP
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->proxyArp == true) && (interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
			{
				nipper->proxyArpIssues++;
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		if (nipper->proxyArpIssues > 0)
			addReportSection(nipper, section_security, report_proxyarp_title, report_proxyarp_context, report_proxyarp_rectext, 10, 8, 5, 3, iosProxyARPIssue);

		// SSH Protocol Version
		tempInt = 0;
		linePointer = nipper->ios->line;
		while (linePointer != 0)
		{
			if ((linePointer->ssh == true) && (linePointer->exec == true) && (linePointer->login != login_disabled))
				tempInt++;
			linePointer = linePointer->next;
		}
		if (tempInt > 0)
		{
			if (nipper->ios->ssh != 0)
			{
				if (nipper->ios->ssh->protocolVersion != ssh_ver_2)
					nipper->sshIssue = 2;
			}
			else
				nipper->sshIssue = 2;
			if ((nipper->versionMajor == 12) && (nipper->versionMinor < 2))
				nipper->sshIssue = 1;
		}
		if (nipper->sshIssue != 0)
			addReportSection(nipper, section_security, report_sshproto_title, report_sshproto_context, report_sshproto_rectext, 10, 8, 5, 3, iosSSHProtocolIssue);

		// CDP
		if (nipper->ios->cdp != false)
			addReportSection(nipper, section_security, report_cdp_title, report_cdp_context, report_cdp_rectext, 10, 8, 5, 3, iosCDPIssue);

		// IP Classless Routing
		if ((nipper->ios->classlessRouting == true) && (nipper->deviceType == type_ios_router))
			addReportSection(nipper, section_security, report_classless_title, report_classless_context, report_classless_rectext, 10, 8, 5, 3, iosClasslessRoutingIssue);

		// Minimum Password Length
		if ((nipper->versionMajor == 12) && (nipper->versionMinor > 2) && (nipper->ios->passwordMinLength < 0))
			addReportSection(nipper, section_security, report_passlength_title, report_passlength2_context, report_passlength_rectext, 10, 8, 5, 3, iosPasswordLengthIssue);
		else if ((nipper->versionMajor == 12) && (nipper->versionMinor > 2) && (nipper->ios->passwordMinLength < nipper->passwordLength))
			addReportSection(nipper, section_security, report_passlength_title, report_passlength_context, report_passlength_rectext, 10, 8, 5, 3, iosPasswordLengthIssue);

		// Bootp
		if (nipper->ios->bootp == true)
			addReportSection(nipper, section_security, report_bootp_title, report_bootp_context, report_bootp_rectext, 10, 8, 5, 3, iosBootPIssue);

		// Small Servers
		if ((nipper->ios->udpSmallServers != false) || (nipper->ios->tcpSmallServers != false))
			addReportSection(nipper, section_security, report_small_title, report_small_context, report_small_rectext, 10, 8, 5, 3, iosSmallServersIssue);

		// IP unreachables
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->ipUnreachables == true) && (interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
			{
				nipper->unreachIssues++;
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		if (nipper->unreachIssues > 0)
			addReportSection(nipper, section_security, report_icmpunreach_title, report_icmpunreach_context, report_icmpunreach_rectext, 10, 8, 5, 3, iosIPUnreachablesIssue);

		// IP Mask Reply
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->ipMaskReply == true) && (interfaceConfigPointer->shutdown == false) && (strncmp(interfaceConfigPointer->ipAddress, "None", 8) != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0))
			{
				nipper->maskReplyIssues++;
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		if (nipper->maskReplyIssues > 0)
			addReportSection(nipper, section_security, report_maskreply_title, report_maskreply_context, report_maskreply_rectext, 10, 8, 5, 3, iosMaskReplyIssue);

		// Enable Secret Passwords
		enablePointer = nipper->ios->enable;
		while (enablePointer != 0)
		{
			if (enablePointer->secret == false)
				nipper->enableIssues++;
			enablePointer = enablePointer->next;
		}
		if (nipper->enableIssues > 0)
			addReportSection(nipper, section_security, report_enablesec_title, report_enablesec_context, report_enablesec_rectext, 10, 8, 5, 3, iosEnableSecretIssue);

		// Password Encryption Service
		if (nipper->ios->servicePasswordEncryption == false)
			addReportSection(nipper, section_security, report_passenc_title, report_passenc_context, report_passenc_rectext, 10, 8, 5, 3, iosPasswordEncryptionIssue);

		// Banners
		if (nipper->ios->banner == 0)
			addReportSection(nipper, section_security, report_banner_title, report_banner_context, report_banner_rectext, 10, 8, 5, 3, iosBannerIssue);

		// Domain Lookup
		if (nipper->ios->domainLookup == true)
			addReportSection(nipper, section_security, report_lookup_title, report_lookup_context, report_lookup_rectext, 10, 8, 5, 3, iosDomainLookupIssue);

		// PAD
		if (nipper->ios->pad == true)
			addReportSection(nipper, section_security, report_pad_title, report_pad_context, report_pad_rectext, 10, 8, 5, 3, iosPADIssue);

		// MOP
		tempInt = 0;
		interfaceConfigPointer = nipper->ios->interface;
		while (interfaceConfigPointer != 0)
		{
			if ((interfaceConfigPointer->mop == true) && (interfaceConfigPointer->shutdown == false) && (strcmp(interfaceConfigPointer->ipAddress, "None") != 0) && (strncmp(interfaceConfigPointer->name, "Loopback", 8) != 0) && (strchr(interfaceConfigPointer->name, '.') == 0))
			{
				tempInt++;
			}
			interfaceConfigPointer = interfaceConfigPointer->next;
		}
		if (tempInt > 0)
			addReportSection(nipper, section_security, report_mop_title, report_mop_context, report_mop_rectext, 10, 8, 5, 3, iosMOPIssue);
	}


	// In Configuration Index
	addReportSection(nipper, section_config, settings_general_title, 0, 0, 0, 0, 0, 0, iosGeneralConfig);
	addReportSection(nipper, section_config, settings_services_title, 0, 0, 0, 0, 0, 0, iosServicesConfig);
	addReportSection(nipper, section_config, settings_dns_title, 0, 0, 0, 0, 0, 0, iosDNSConfig);
	addReportSection(nipper, section_config, settings_timezone_title, 0, 0, 0, 0, 0, 0, iosTimeZoneConfig);
	if ((nipper->ios->enable != 0) || (nipper->ios->username != 0) || (nipper->ios->banner != 0))
		addReportSection(nipper, section_config, settings_users_title, 0, 0, 0, 0, 0, 0, iosUsersConfig);
	if (nipper->ios->logging != 0)
		addReportSection(nipper, section_config, settings_logging_title, 0, 0, 0, 0, 0, 0, iosLoggingConfig);
	if (nipper->ios->snmp != 0)
		addReportSection(nipper, section_config, settings_snmp_title, 0, 0, 0, 0, 0, 0, iosSNMPConfig);
	if (nipper->ios->ssh != 0)
		addReportSection(nipper, section_config, settings_ssh_title, 0, 0, 0, 0, 0, 0, iosSSHConfig);
	if (nipper->ios->ntp != 0)
		addReportSection(nipper, section_config, settings_ntp_title, 0, 0, 0, 0, 0, 0, iosNTPConfig);
	if (nipper->ios->ftp != 0)
		addReportSection(nipper, section_config, settings_ftp_title, 0, 0, 0, 0, 0, 0, iosFTPConfig);
	if (nipper->ios->http != 0)
		addReportSection(nipper, section_config, settings_http_title, 0, 0, 0, 0, 0, 0, iosHTTPConfig);
	if (nipper->ios->tacacs != 0)
		addReportSection(nipper, section_config, settings_tacacs_title, 0, 0, 0, 0, 0, 0, iosTACACSConfig);
	if ((nipper->ios->aaa !=0) && (nipper->ios->aaa->groupServer !=0))
		addReportSection(nipper, section_config, settings_aaa_title, 0, 0, 0, 0, 0, 0, iosAAAConfig);
	nipper->vrrpIssues = 0;
	interfaceConfigPointer = nipper->ios->interface;
	while (interfaceConfigPointer != 0)
	{
		if (interfaceConfigPointer->vrrp != 0)
			nipper->vrrpIssues++;
		interfaceConfigPointer = interfaceConfigPointer->next;
	}
	if ((nipper->ios->bgp != 0) || (nipper->vrrpIssues != 0) || (nipper->ios->eigrp != 0) || (nipper->ios->isis != 0) || (nipper->ios->rip != 0) || (nipper->ios->ospf != 0) || (nipper->ios->route != 0) || (nipper->ios->routeMap != 0))
		addReportSection(nipper, section_config, settings_routing_title, 0, 0, 0, 0, 0, 0, iosRoutingConfig);
	if ((nipper->passwords == true) && (nipper->ios->chain != 0))
		addReportSection(nipper, section_config, settings_keys_title, 0, 0, 0, 0, 0, 0, iosKeysConfig);
	if (nipper->ios->line != 0)
		addReportSection(nipper, section_config, settings_lines_title, 0, 0, 0, 0, 0, 0, iosLinesConfig);
	if (nipper->ios->interface != 0)
		addReportSection(nipper, section_config, settings_inter_title, 0, 0, 0, 0, 0, 0, iosInterfacesConfig);
	if (nipper->deviceType != type_ios_router)
		addReportSection(nipper, section_config, settings_vtp_title, 0, 0, 0, 0, 0, 0, iosVTPConfig);
	if ((nipper->ios->interface !=0) && (nipper->deviceType != type_ios_router))
		addReportSection(nipper, section_config, settings_switchport_title, 0, 0, 0, 0, 0, 0, iosSwitchportConfig);
	if (nipper->ios->nat !=0)
		addReportSection(nipper, section_config, settings_nat_title, 0, 0, 0, 0, 0, 0, iosNATConfig);
	if (nipper->filterList !=0)
		addReportSection(nipper, section_config, settings_accesslists_title, 0, 0, 0, 0, 0, 0, iosACLConfig);

	// Generate Report...
	generateReport(nipper);
}


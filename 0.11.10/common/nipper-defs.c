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

// This file contains common definitions...

// Defines...
#define false 0
#define true 1
#define unconfigured 2

#define LINE_SIZE 1024

#define output_text 0
#define output_html 1
#define output_latex 2
// 3 is reserved!
#define output_xml 4

#define type_ios_router 0			// Cisco IOS Router
#define type_ios_switch 1			// Cisco IOS Switch
#define type_ios_catalyst 2			// Cisco IOS Catalyst
#define type_pix_firewall 3			// Cisco PIX Firewall
#define type_asa_firewall 4			// Cisco ASA Firewall
#define type_fwsm_firewall 5		// Cisco FWSM Firewall
#define type_sos_firewall 6			// Juniper ScreenOS Firewall
#define type_fw1_firewall 7			// Checkpoint Firewall-1
#define type_nmp_catalyst 8			// Cisco NMP Catalyst
#define type_cos_catalyst 9			// Cisco CatOS Catalyst
#define type_css_filter 10			// Cisco Content Services Switch (CSS)
#define type_passport 11			// Nortel Passport
#define type_sonicwall 12			// SonicWall Firewall
#define type_nokiaip 13				// Nokia IP Firewall
#define type_bayaccelar 14			// Bay Networks Accelar

// Object types...
#define object_type_network 0
#define object_type_protocol 1
#define object_type_icmp 2
#define object_type_service 3
#define object_type_group 4
#define object_type_port 5
#define object_type_host 6
#define object_type_machinesrange 7
#define object_type_dynamicnet 8
#define object_type_gateway 9
#define object_type_gateway_cluster 10
#define object_type_cluster_member 11
#define object_type_servicerange 12
#define object_type_interface 13
#define object_type_object 14
#define object_type_any 15
#define object_type_notset 100
#define object_type_delete_me 101

// Object service operators...
#define service_oper_eq 0
#define service_oper_neq 1
#define service_oper_lt 2
#define service_oper_gt 3
#define service_oper_range 4
#define service_oper_object 5
#define service_oper_ignore 6
#define service_oper_any 6

// Object service protocols...
#define service_protocol_none 0
#define service_protocol_tcp 1
#define service_protocol_udp 2
#define service_protocol_both 3
#define service_protocol_other 4
#define service_protocol_unknown 5
#define service_protocol_dcerpc 6
#define service_protocol_rpc 7
#define service_protocol_icmp 8
#define service_protocol_tcpsub 9
#define service_protocol_gtp0 10
#define service_protocol_gtp1 11

// SNMP...
#define snmp1_2 0
#define snmp1 1
#define snmp2c 2
#define snmp3_no_auth 3
#define snmp3_auth 4
#define snmp3_priv 5

// Authentication...
#define auth_none 0
#define auth_clear 1
#define auth_md5 2

// Encryption...
#define encrypt_type7 0
#define encrypt_md5 1
#define encrypt_des56 2
#define encrypt_none 3
#define encrypt_unknown 4
#define encrypt_pix 5
#define encrypt_mschap 6
#define encrypt_ntenc 7

// Filters...
#define filter_action_drop 0
#define filter_action_reject 1
#define filter_action_accept 2
#define filter_action_bypass 3
#define filter_action_default 4
#define filter_action_remark 100

// Filter Types...
#define filter_type_source 0
#define filter_type_destination 1
#define filter_type_global 2

// Permissions...
#define perm_permit 0
#define perm_deny 1

// Device purpose...
#define use_all 0
#define use_edge 1
#define use_internal 2

// Nipper modes...
#define mode_help 0
#define mode_version 1
#define mode_process 2

// Help modes...
#define help_general 0
#define help_device_types 10
#define help_device_usage 11
#define help_report_formats 20
#define help_report_options 21
#define help_report_appendix 22
#define help_report_html 23
#define help_report_latex 24
#define help_audit_acl 30
#define help_audit_password 31
#define help_audit_misc 32
#define help_snmp 33
#define help_debug 40
#define help_config_file 50
#define help_error_params 100
#define help_error_empty_file 101
#define help_error_wrong_type 102
#define help_error_opening_file 103
#define help_error_john_file 104
#define help_error_report_file 105
#define help_error_read_timeout 106
#define help_error_base64_decode 107
#define help_error_snmp_failure 108
#define help_error_snmp_root 109

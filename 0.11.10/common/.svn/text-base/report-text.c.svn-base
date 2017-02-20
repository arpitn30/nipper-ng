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


const char *table_html_rowstart = "<tr><td>";
const char *table_html_rowmid = "</td><td>";
const char *table_html_rowend = "</td></tr>\n";
const char *table_html_itemsep = "<br>";
const char *table_xml_rowstart = "      <tablerow>\n       <tableentry><item>";
const char *table_xml_rowmid = "</item></tableentry>\n       <tableentry><item>";
const char *table_xml_rowend = "</item></tableentry>\n      </tablerow>\n";
const char *table_xml_itemsep = "</item><item>";
const char *table_text_rowstart = "";
const char *table_text_rowmid = ", ";
const char *table_text_rowend = "\n";
const char *table_text_itemsep = " ";
const char *table_latex_rowstart = "";
const char *table_latex_rowmid = "&";
const char *table_latex_rowend = "\\\\\n\\hline\n";
const char *table_latex_itemsep = " ";


struct tableHeading
{
	int password;						// Does the field represent a password (true or false)
	int width;							// Proportionate column width
	const char *heading;				// The Heading
	struct tableHeading *next;
};


// HTML Cascading Style Sheet
const char *html_css = "body {font-size: 80%; margin: 0px; padding: 0px; font-family: arial, sans-serif;}\n"
                     "  .mainbody { background-color: #EFEFEF;}\n"
                     "  .pagebody {width: 90%; margin: 0px auto; padding: 12px; background-color: #FFFFFF; border: solid 1px rgb(100,100,100);}\n"
                     "  .command {font-size: 95%; font-family: courier;}\n"
                     "  caption { caption-side : bottom; font-style : italic;}\n"
                     "  .table {clear: left; border: solid 1px rgb(150,150,150); empty-cells: show; border-collapse: collapse; background-color: rgb(233,232,244); width: 100%}\n"
                     "  .table tr {margin: 0px; padding: 0px;}\n"
                     "  .table td {padding: 2px 7px 2px 7px; border: solid 1px rgb(150,150,150); text-align: left; font-size: 100%;}\n"
                     "  .table th {margin: 0px; padding: 2px 7px 2px 7px; border: solid 1px rgb(150,150,150); empty-cells: show; text-align: left; font-size: 100%; background-color: #BEB8FB;}\n";


// ----------------------------------------------------------------------------------
// About this report Text...

// Organisation
const char *report_organisation = "This *DEVICETYPE* *DEVICENAME* report was produced by *COMPANY* on *DATE*. The report contains the following sections:";
const char *report_organisation_fw1 = "This *DEVICETYPE* report was produced by *COMPANY* on *DATE*. The report contains the following sections:";
struct tableHeading report_organisation_heading6 = {false, 1, "an appendix section detailing the software used to produce this report", 0};
struct tableHeading report_organisation_heading5 = {false, 1, "a time zones appendix section that details a number of the most commonly used time zones", &report_organisation_heading6};
struct tableHeading report_organisation_heading4 = {false, 1, "an appendix section detailing the logging severity levels used by the logging facility", &report_organisation_heading5};
struct tableHeading report_organisation_heading3 = {false, 1, "a common ports appendix section that details the TCP and UDP port numbers for the common services outlined within the report", &report_organisation_heading4};
struct tableHeading report_organisation_heading2 = {false, 1, "an abbreviations appendix section that expands any abbreviations used within the report", &report_organisation_heading3};
struct tableHeading report_organisation_heading1 = {false, 1, "a configuration report section that details the configuration settings", &report_organisation_heading2};
struct tableHeading report_organisation_heading  = {false, 1, "a security audit report section that details any identified security-related issues. Each security issue includes a description of the issue, its impact, how easy it would be to exploit and a recommendation. The recommendations include, where appropriate, the command(s) to resolve the issue", &report_organisation_heading1};

// Conventions
const char *report_conventions = "This report makes use of the text conventions outlined in Table *TABLEREF*.";
const char *report_conventions_table = "Report text conventions";
struct tableHeading report_conventions_heading1 = {false, 7, "Description", 0};
struct tableHeading report_conventions_heading  = {false, 3, "Convention", &report_conventions_heading1};
const char *report_conventions1_1 = "*TABLEITEM**COMMAND*command*-COMMAND**-TABLEITEM*";
const char *report_conventions1_2 = "*TABLEITEM*This text style represents the *DEVICETYPE* command text that has to be entered literally.*-TABLEITEM*";
const char *report_conventions2_1 = "*TABLEITEM**COMMAND**CMDUSER*string*-CMDUSER**-COMMAND**-TABLEITEM*";
const char *report_conventions2_2 = "*TABLEITEM*This text style represents the *DEVICETYPE* command text that the you have to enter.*-TABLEITEM*";
const char *report_conventions3_1 = "*TABLEITEM**COMMAND**CMDOPTION* *-CMDOPTION**-COMMAND**-TABLEITEM*";
const char *report_conventions3_2 = "*TABLEITEM*Used to enclose a *DEVICETYPE* command option.*-TABLEITEM*";
const char *report_conventions4_1 = "*TABLEITEM**COMMAND**CMDREQUIRE* *-CMDREQUIRE**-COMMAND**-TABLEITEM*";
const char *report_conventions4_2 = "*TABLEITEM*Used to enclose a *DEVICETYPE* command requirement.*-TABLEITEM*";
const char *report_conventions5_1 = "*TABLEITEM**COMMAND**CMDOR**-COMMAND**-TABLEITEM*";
const char *report_conventions5_2 = "*TABLEITEM*Divides command option or requirement choices.*-TABLEITEM*";


// ----------------------------------------------------------------------------------
// Report Text...

// Introduction
const char *report_security_intro_fw1 = "*COMPANY* performed a security audit of the *DEVICETYPE* firewall on *DATE*. This section details the findings of the security audit together with the impact and recommendations*-POSITIVE*.";
const char *report_security_intro = "*COMPANY* performed a security audit of the *DEVICETYPE* *DEVICENAME* on *DATE*. This section details the findings of the security audit together with the impact and recommendations*-POSITIVE*.";
const char *report_security_title = "Security Audit";

// Conclusions
const char *report_security_concl_fw1 = "*COMPANY* performed a security audit of the *DEVICETYPE* firewall on *DATE* and identified *POSITIVE**NUMBER* security-related issue*PLAURAL*s*-PLAURAL*. *COMPANY* determined that:*-POSITIVE**ZERO*no security-related issues.*-ZERO*";
const char *report_security_concl = "*COMPANY* performed a security audit of the *DEVICETYPE* device *DEVICENAME* on *DATE* and identified *POSITIVE**NUMBER* security-related issue*PLAURAL*s*-PLAURAL*. *COMPANY* determined that:*-POSITIVE**ZERO*no security-related issues.*-ZERO*";

// Interface Headings...
struct tableHeading report_interface_heading1 = {false, 7, "Description", 0};
struct tableHeading report_interface_heading  = {false, 3, "Interface", &report_interface_heading1};
struct tableHeading report_interfacepix_heading1 = {false, 1, "Name", 0};
struct tableHeading report_interfacepix_heading  = {false, 1, "Interface", &report_interfacepix_heading1};

const char *endottext = "*NOTEXTSTART*";

// Software Versions
const char *report_osver_title = "Software Version";
const char *report_osver_obs1 = "It is critically important that software be regularly maintained with patches and upgrades in order to help mitigate the risk of an attacker exploiting a known software vulnerability. Furthermore, additional security features and other functionality are normally added or extended with each software revision.*NEWPARA**COMPANY* determined that the *DEVICETYPE* *DEVICENAME* was running the out of date software *DEVICEVERSION*.*PLAURAL* Some of the known vulnerabilities for this software version are listed in Table *TABLEREF*.*-PLAURAL*";
const char *report_osver_obs2 = "It is worth noting that *COMPANY* used the version number detailed in the device configuration to identify the potential vulnerabilities, and patches may have already been applied. Additionally, a specific device configuration may be required in order for the device to become vulnerable.";
const char *report_osver_obs3 = "*COMPANY* identified a potential vulnerability in *DEVICEVERSION* which is described in various vulnerability databases as *NONEWPARA*";
const char *report_osver_impact1 = "*PLAURAL*The vulnerabilities listed in Table *TABLEREF* could allow an attacker to*-PLAURAL**SINGULA*The vulnerability outlined above could allow an attacker to*-SINGULA* *NONEWPARA*";
const char *report_osver_impact2 = "*NOTEXTSTART*gain remote administrative access or perform a *ABBREV*DoS*-ABBREV* attack.";
const char *report_osver_impact3 = "*NOTEXTSTART*perform a *ABBREV*DoS*-ABBREV* attack.";
const char *report_osver_impact4 = "*NOTEXTSTART*gain remote administrative access.";
const char *report_osver_impact5 = "Out of date software could contain known vulnerabilities that may allow an attacker to gain remote administrative access or perform a *ABBREV*DoS*-ABBREV* attack.";
const char *report_osver_ease = "Exploit code is widely available on the Internet for known *DEVICETYPE* vulnerabilities.";
const char *report_osver_rec = "*COMPANY* strongly recommends that the software be updated and patched to the latest software version. Furthermore, *COMPANY* recommends that the current patch policy be reviewed.";
const char *report_osver_context = "the software version was out of date";
const char *report_osver_rectext = "Update the software to the latest version";
const char *report_osver_table = "Potential software vulnerabilities";
struct tableHeading report_osver_heading2 = {false, 1, "Bugtraq ID", 0};
struct tableHeading report_osver_heading1 = {false, 1, "CVE Reference", &report_osver_heading2};
struct tableHeading report_osver_heading  = {false, 4, "Description", &report_osver_heading1};

// Dictionary-based Password
const char *report_dict_title1 = "Dictionary-based Passwords / Keys";
const char *report_dict_title2 = "Dictionary-based Password / Key";
const char *report_dict_obs = "Attackers will often have dictionaries of words that contain names, places, default passwords and other common passwords. If a password or key is likely to be contained within an attacker's dictionary, they could gain access to the system.*NEWPARA*The passwords and keys of the device *DEVICENAME* were tested against a small dictionary and *NUMBER* password*SINGULA* / key was identified. *NONEWPARA**-SINGULA**PLAURAL*s / keys were identified. These are listed in Table *TABLEREF*.*-PLAURAL*";
const char *report_dict_impact = "An attacker who was able to identify a password or key would be able to gain a level of access to the device, based on what service the password / key was used for.";
const char *report_dict_ease = "Tools are available on the Internet that can perform dictionary-based password guessing against a number of network services.";
const char *report_dict_rec = "*COMPANY* strongly recommends that the password*PLAURAL*s*-PLAURAL* identified be immediately changed to something that is more difficult to guess. *COMPANY* recommends that passwords be made up of at least *NONEWPARA*";
const char *report_dict_context = "dictionary-based passwords / keys were in use";
const char *report_dict_rectext = "Change dictionary-based passwords / keys for ones that are more complex";
const char *report_dict_table = "Dictionary-based passwords / keys";
struct tableHeading report_dict_heading3 = {true, 3, "Password", 0};
struct tableHeading report_dict_heading2 = {false, 3, "Username", &report_dict_heading3};
struct tableHeading report_dict_heading1 = {false, 2, "Service", &report_dict_heading2};
struct tableHeading report_dict_heading  = {false, 2, "Type", &report_dict_heading1};

// Password Strength
const char *report_strength_title1 = "Weak Passwords / Keys";
const char *report_strength_title2 = "Weak Password / Key";
const char *report_strength_obs = "Strong passwords tend to contain a number of different types of character, such as uppercase and lowercase letters, numbers and punctuation characters. Weaker passwords tend not to contain a mixture of character types. Additionally, weaker passwords tend to be short in length.*NEWPARA**COMPANY* identified *NUMBER* password*SINGULA* / key*-SINGULA**PLAURAL*s / keys*-PLAURAL* that did not meet the minimum password complexity requirements. *PLAURAL*These are listed in Table *TABLEREF*.*-PLAURAL**SINGULA**NONEWPARA**-SINGULA*";
const char *report_strength_impact = "If an attacker were able to gain a password or key, either through dictionary-based guessing techniques or by a brute-force method, the attacker could gain a level of access to *DEVICENAME*."; 
const char *report_strength_ease = "A number of dictionary-based password guessing and password brute-force tools are available on the Internet.";
const char *report_strength_rec = "*COMPANY* strongly recommends that the weak password*PLAURAL*s*-PLAURAL* be immediately changed to *PLAURAL*ones that are*-PLAURAL**SINGULA*one that is*-SINGULA* stronger. *COMPANY* recommends that passwords be made up of at least *NONEWPARA*";
const char *report_strength_context = "weak passwords / keys were identified";
const char *report_strength_rectext = "Change weak passwords / keys for ones that are stronger";
const char *report_strength_table = "Weak passwords / keys";
// Dictionary-based headings are used for the weak passwords table.

// Configuration Auto-Loading
const char *report_configauto_title = "Configuration Auto-Loading";
const char *report_configauto_obs = "Cisco devices are capable of loading their configuration from other network devices, rather than using a local configuration file.*NEWPARA*Although the configuration auto-loading feature is typically disabled by default on Cisco devices, *COMPANY* determined that the *DEVICENAME* had configuration auto-loading enabled.";
const char *report_configauto_impact = "The Cisco device configuration files are transmitted unencrypted over the network. An attacker who is able to monitor the network would be able to capture a copy of the device configuration. The attacker would also be able to capture any clear-text passwords or password hashes contained within the configuration file.";
const char *report_configauto_ease = "Tools are widely available on the Internet that would allow an attacker to capture network traffic and reconstruct network streams.";
const char *report_configauto_rec = "*COMPANY* recommends that, if not required, configuration auto-loading be disabled. The following Cisco *ABBREV*IOS*-ABBREV* commands can be used to disable configuration auto-loading:*NEWPARA**COMMAND*no boot network*-COMMAND**NEWLINE**COMMAND*no service config*-COMMAND*";
const char *report_configauto_context = "configuration auto-loading was configured";
const char *report_configauto_rectext = "Disable configuration auto-loading";

// IP Directed Broadcasts
const char *report_ipdirected_title = "Directed Broadcasts";
const char *report_ipdirected_obs = "*ABBREV*ICMP*-ABBREV* echo requests can be addressed to an entire network or subnet as well as to individual hosts. Disabling directed broadcasts on each individual network interface will help prevent network ping requests. Directed broadcasts are usually enabled by default on Cisco devices running *ABBREV*IOS*-ABBREV* version 11.3 and earlier.*NEWPARA**COMPANY* determined that the device *DEVICENAME* had support for directed broadcasts enabled on the network *SINGULA*interface *NONEWPARA**-SINGULA**PLAURAL*interfaces listed in Table *TABLEREF*.*-PLAURAL*";
const char *report_ipdirected_impact = "A *ABBREV*DoS*-ABBREV* attack exists that makes use of network echo requests, known as a smurf attack. An attacker would send an ICMP echo request with the victim hosts *ABBREV*IP*-ABBREV* address spoofed as the source. The hosts on the network would then reply to the echo request, flooding the victim host.";
const char *report_ipdirected_ease = "Tools are available on the Internet that can perform the smurf attack outlined above.";
const char *report_ipdirected_rec = "*COMPANY* recommends that directed broadcasts be disabled on all network interfaces. Directed broadcasts can be disabled on each individual network interface using the following command:*NEWPARA**COMMAND*no ip directed broadcast*-COMMAND*";
const char *report_ipdirected_context = "directed broadcasts were enabled";
const char *report_ipdirected_rectext = "Disable directed broadcasts on all network interfaces";
const char *report_ipdirected_table = "Interfaces with directed broadcasts enabled";

// BGP Route Dampening
const char *report_bgpdamp_title = "Border Gateway Protocol Route Flapping";
const char *report_bgpdamp_obs = "*ABBREV*BGP*-ABBREV* route flapping is a condition where routing tables are constantly being updated due to a link transitioning between up and down status. These transitions cause routing tables to be continuously updated across the infrastructure. Configuring route dampening can help mitigate against constant route flapping.*NEWPARA**COMPANY* determined that *ABBREV*BGP*-ABBREV* route dampening was not configured on *DEVICENAME*.";
const char *report_bgpdamp_impact = "Excessive route updates, caused by a link status constantly changing between up to down, can impact network routing performance. Network routing could slow with network packets being dropped, possibly causing a *ABBREV*DoS*-ABBREV* condition.";
const char *report_bgpdamp_ease = "It is possible for an attacker to send *ABBREV*BGP*-ABBREV* packets to a router to update the routing table and cause a route flapping condition. However, the attacker may need additional information in order to perform the attack, such as a *ABBREV*BGP*-ABBREV* password.";
const char *report_bgpdamp_rec = "*COMPANY* recommends that *ABBREV*BGP*-ABBREV* route dampening be configured. Additionally, there are a number of *ABBREV*BGP*-ABBREV* dampening options that can be configured. The following Cisco *ABBREV*IOS*-ABBREV* router command will enable *ABBREV*BGP*-ABBREV* route dampening:*NEWPARA**COMMAND*bgp dampening*-COMMAND*";
const char *report_bgpdamp_context = "BGP route dampening was not configured";
const char *report_bgpdamp_rectext = "Configure BGP route dampening";

// OSPF Passwords
const char *report_ospfauth_title = "OSPF Authentication";
const char *report_ospfauth_obs1 = "*ABBREV*OSPF*-ABBREV* is an *ABBREV*IGP*-ABBREV* used by routers to update routing tables. *ABBREV*OSPF*-ABBREV* packets can be configured to use one of three levels of security; no authentication, clear-text authentication and *ABBREV*MD5*-ABBREV* authentication. The clear-text authentication method is almost as insecure as no authentication, as the key is included in the packet. Using the *ABBREV*MD5*-ABBREV* authentication method the packets are signed to prevent route tampering.*NEWPARA**COMPANY* determined that*NONEWPARA*";
const char *report_ospfauth_obs2 = "*NOTEXTSTART*, although *ABBREV*MD5*-ABBREV* encryption was in use,";
const char *report_ospfauth_obs3 = "*NOTEXTSTART* *ABBREV*OSPF*-ABBREV* with both no authentication and clear-text authentication was configured on *SINGULA*process ID *NONEWPARA**-SINGULA**PLAURAL*the areas listed in Table *TABLEREF*.*-PLAURAL*";
const char *report_ospfauth_obs4 = "*NOTEXTSTART* *ABBREV*OSPF*-ABBREV* with no authentication was configured on *SINGULA*process ID *NONEWPARA**-SINGULA**PLAURAL*the areas listed in Table *TABLEREF*.*-PLAURAL*";
const char *report_ospfauth_obs5 = "*NOTEXTSTART* *ABBREV*OSPF*-ABBREV* with clear-text authentication was configured on *SINGULA*process ID *NONEWPARA**-SINGULA**PLAURAL*the areas listed in Table *TABLEREF*.*-PLAURAL*";
const char *report_ospfauth_impact = "An attacker who is able to update the routing tables could capture network traffic, perform a network-wide *ABBREV*DoS*-ABBREV* or a man-in-the-middle attack.";
const char *report_ospfauth_ease = "Once an attacker has established what the type of authentication in use, they could use the information to pose as a router and insert routes into the routing tables by sending specially crafted *ABBREV*OSPF*-ABBREV* packets. *ABBREV*OSPF*-ABBREV* packets can be captured using a variety of techniques, and tools are available on the Internet that can be used to exploit insecure *ABBREV*OSPF*-ABBREV* configurations.";
const char *report_ospfauth_rec = "*COMPANY* recommends that, if possible, all *ABBREV*OSPF*-ABBREV* areas be configured to use *ABBREV*MD5*-ABBREV*-based authentication. Message digest authentication needs to be configured for each *ABBREV*OSPF*-ABBREV* area and a key be specified on each *ABBREV*OSPF*-ABBREV* network interface. The Cisco *ABBREV*IOS*-ABBREV* command to enable *ABBREV*MD5*-ABBREV* authentication for an area is:*NEWPARA**COMMAND*area *CMDREQUIRE**CMDUSER*area id*-CMDUSER**-CMDREQUIRE* authentication *CMDOPTION*message-digest*-CMDOPTION**-COMMAND**NEWLINE*The command to configure the *ABBREV*MD5*-ABBREV* authentication key on an interface is:*NEWPARA**COMMAND*ip ospf message-digest-key *CMDREQUIRE**CMDUSER*key id*-CMDUSER**-CMDREQUIRE* md5*-COMMAND*";
const char *report_ospfauth_context = "the OSPF configuration did not include MD5 authentication for all OSPF areas";
const char *report_ospfauth_rectext = "Configure MD5 OSPF authentication on all OSPF areas";
const char *report_ospfauth_table = "OSPF areas with insecure authentication configuration";
struct tableHeading report_ospfauth_heading2 = {false, 2, "Authentication", 0};
struct tableHeading report_ospfauth_heading1 = {false, 1, "Area ID", &report_ospfauth_heading2};
struct tableHeading report_ospfauth_heading  = {false, 1, "Process ID", &report_ospfauth_heading1};

// EIGRP
const char *report_eigrpauth_title = "EIGRP Authentication";
const char *report_eigrpauth_obs1 = "Cisco developed *ABBREV*EIGRP*-ABBREV* as an enhanced version of *ABBREV*IGRP*-ABBREV*, an *ABBREV*IGP*-ABBREV* used by routers to dynamically update routing tables. Each interface where *ABBREV*EIGRP*-ABBREV* is used can be configured with *ABBREV*MD5*-ABBREV*-based authentication.*NEWPARA**COMPANY* determined that *NUMBER* *ABBREV*EIGRP*-ABBREV* interface*PLAURAL*s were*-PLAURAL**SINGULA* was*-SINGULA* configured with no authentication*PLAURAL*, these are listed in Table *TABLEREF*.*-PLAURAL**SINGULA*. Interface *NONEWPARA**-SINGULA*";
const char *report_eigrpauth_obs2 = "*NOTEXTSTART* was configured with no *ABBREV*MD5*-ABBREV* authentication.";
const char *report_eigrpauth_impact = "An attacker who is able to update the routing tables could capture network traffic, perform a network-wide *ABBREV*DoS*-ABBREV* or a man-in-the-middle attack.";
const char *report_eigrpauth_ease = "Once an attacker has established the type of authentication in use, they could use the information to pose as a router and insert routes into the routing tables by sending specially crafted *ABBREV*EIGRP*-ABBREV* packets. *ABBREV*EIGRP*-ABBREV* packets can be captured using a variety of techniques and tools are available on the Internet that can be used to exploit insecure *ABBREV*EIGRP*-ABBREV* configurations.";
const char *report_eigrpauth_rec = "*COMPANY* recommends that all *ABBREV*EIGRP*-ABBREV* interfaces be configured with *ABBREV*EIGRP*-ABBREV* *ABBREV*MD5*-ABBREV*-based authentication. Furthermore, *COMPANY* recommends that all interfaces where *ABBREV*EIGRP*-ABBREV* is not required be configured as passive. *ABBREV*EIGRP*-ABBREV* *ABBREV*MD5*-ABBREV* authentication can be configured on each interface with the following commands:*NEWPARA**COMMAND*ip authentication mode eigrp *CMDREQUIRE**CMDUSER*autonomous number*-CMDUSER**-CMDREQUIRE* md5*-COMMAND**NEWLINE**COMMAND*ip authentication key-chain eigrp *CMDREQUIRE**CMDUSER*autonomous number*-CMDUSER**-CMDREQUIRE* *CMDREQUIRE**CMDUSER*key chain*-CMDUSER**-CMDREQUIRE**-COMMAND**NEWLINE*Passive interfaces can be configured with the following *ABBREV*EIGRP*-ABBREV* router command:*NEWPARA**COMMAND*passive-interface *CMDREQUIRE**CMDUSER*interface type*-CMDUSER**-CMDREQUIRE* *CMDREQUIRE**CMDUSER*interface number*-CMDUSER**-CMDREQUIRE**-COMMAND*";
const char *report_eigrpauth_context = "the EIGRP configuration did not include MD5 authentication for all EIGRP interfaces";
const char *report_eigrpauth_rectext = "Configure MD5 authentication on all EIGRP interfaces";
const char *report_eigrpauth_table = "Interfaces with no EIGRP authentication";

// RIP
const char *report_rip_title = "RIP Authentication";
const char *report_rip_obs = "*ABBREV*RIP*-ABBREV* is a routing protocol that allows network devices to dynamically adapt to changes in the network infrastructure, enabling network devices to forward traffic using the shortest route to their destination. There are two versions of *ABBREV*RIP*-ABBREV* configurable on *DEVICETYPE* devices. *ABBREV*RIP*-ABBREV* version 2 provides a mechanism where routing updates can be authenticated, however *ABBREV*RIP*-ABBREV* version 1 provides no similar mechanism. *ABBREV*RIP*-ABBREV* version 2 supports clear-text authentication and *ABBREV*MD5*-ABBREV* authentication.*NEWPARA**COMPANY* determined that *ABBREV*RIP*-ABBREV* had been configured without encrypted authentication for sent and received updates on *NUMBER* network *SINGULA*interface *NONEWPARA**-SINGULA**PLAURAL*interfaces, these are listed in Table *TABLEREF*.*-PLAURAL*";
const char *report_rip_table = "Insecure RIP interface configurations";
const char *report_rip_tab_desc1 = "No RIP version 2 key chain or MD5 authentication was configured.";
const char *report_rip_tab_desc2 = "No RIP version 2 key chain was configured.";
const char *report_rip_tab_desc3 = "No RIP version 2 MD5 authentication was configured.";
const char *report_rip_tab_desc4 = "The interface was not configured to send and receive only RIP version 2.";
const char *report_rip_tab_desc5 = "The interface was not configured to send RIP version 2.";
const char *report_rip_tab_desc6 = "The interface was not configured to receive only RIP version 2.";
const char *report_rip_impact = "If *ABBREV*RIP*-ABBREV* updates are sent and received without encrypted authentication an attacker may be able to inject their own route into the routing table. An attacker could modify routes in order to enable the capture of network traffic or to perform a network *ABBREV*DoS*-ABBREV*.";
const char *report_rip_ease = "An attacker would have to determine what authentication, if any, was configured. Once an attacker has identified an insecure *ABBREV*RIP*-ABBREV* configuration they could attempt to pose as a router and inject routes. Tools are available on the Internet that can transmit *ABBREV*RIP*-ABBREV* updates.";
const char *report_rip_rec = "*COMPANY* recommends *ABBREV*RIP*-ABBREV* be configured with encrypted authentication for all interfaces where *ABBREV*RIP*-ABBREV* packets will be sent and received. Furthermore, *COMPANY* recommends that all interfaces where *ABBREV*RIP*-ABBREV* will not be used be configured as passive. *ABBREV*RIP*-ABBREV* version 2 can be configured with the following router command:*NEWPARA**COMMAND*version 2*-COMMAND**NEWLINE**ABBREV*RIP*-ABBREV* authentication can be configured on each interface using the following commands:*NEWPARA**COMMAND*ip rip authentication key-chain *CMDREQUIRE**CMDUSER*Key Chain*-CMDUSER**-CMDREQUIRE**-COMMAND**NEWLINE**COMMAND*ip rip authentication mode md5*-COMMAND**NEWLINE**ABBREV*RIP*-ABBREV* can be disabled on each individual interfaces using the following router command:*NEWPARA**COMMAND*passive-interface *CMDREQUIRE**CMDUSER*interface type*-CMDUSER**-CMDREQUIRE* *CMDREQUIRE**CMDUSER*interface number*-CMDUSER**-CMDREQUIRE**-COMMAND*";
const char *report_rip_context = "the RIP configuration did not include MD5 authentication for all RIP interfaces";
const char *report_rip_rectext = "Configure MD5 authentication for all RIP interfaces";

// VRRP
const char *report_vrrp_title = "VRRP Authentication";
const char *report_vrrp_obs = "*DEVICETYPE* devices support *ABBREV*VRRP*-ABBREV*, which is used for router load balancing and redundancy. One *ABBREV*VRRP*-ABBREV* group router will be a master router and *ABBREV*VRRP*-ABBREV* advertisements are sent from it to group members. The advertisements contain the priority and state of the master. If the master router becomes unavailable, an election is held to determine a new *ABBREV*VRRP*-ABBREV* master router. *ABBREV*VRRP*-ABBREV* messages can be unauthenticated or authenticated. *ABBREV*VRRP*-ABBREV* authentication uses either a clear-text password or a *ABBREV*MD5*-ABBREV* password.*NEWPARA**COMPANY* determined that *ABBREV*VRRP*-ABBREV* was configured on *DEVICENAME* without *ABBREV*MD5*-ABBREV* authentication on all *ABBREV*VRRP*-ABBREV* interfaces.";
const char *report_vrrp_impact = "An attacker could transmit *ABBREV*VRRP*-ABBREV* group messages in an attempt to become the *ABBREV*VRRP*-ABBREV* master. If an attacker were able to become the *ABBREV*VRRP*-ABBREV* group master, they could modify the network traffic route in order to capture traffic or to perform a network *ABBREV*DoS*-ABBREV*.";
const char *report_vrrp_ease = "The attacker would have to monitor *ABBREV*VRRP*-ABBREV* traffic in order to determine the *ABBREV*VRRP*-ABBREV* group, priority and the authentication method in use. The attacker would then have to transmit *ABBREV*VRRP*-ABBREV* group messages with a higher priority than the *ABBREV*VRRP*-ABBREV* master in order to become the *ABBREV*VRRP*-ABBREV* master.";
const char *report_vrrp_rec = "*COMPANY* recommends that *ABBREV*MD5*-ABBREV* authentication be configured on all *ABBREV*VRRP*-ABBREV* interfaces. *ABBREV*MD5*-ABBREV* *ABBREV*VRRP*-ABBREV* key string authentication can be configured on each *ABBREV*VRRP*-ABBREV* interface with the following command:*NEWPARA**COMMAND*vrrp *CMDREQUIRE**CMDUSER*group*-CMDUSER**-CMDREQUIRE* authentication md5 *CMDREQUIRE**CMDOPTION*key-string *CMDUSER*password*-CMDUSER**-CMDOPTION* *CMDOR* *CMDOPTION*key-chain *CMDUSER*key chain*-CMDUSER**-CMDOPTION**-CMDREQUIRE**-COMMAND*";
const char *report_vrrp_context = "the VRRP configuration did not include MD5 authentication for all VRRP interfaces";
const char *report_vrrp_rectext = "Configure MD5 authentication for all VRRP interfaces";

// TCP Keep Alives In
const char *report_keepalive_title = "Inbound TCP Connection Keep Alives";
const char *report_keepalive_obs = "Connections to a *DEVICETYPE* device could become orphaned if a connection becomes disrupted. An attacker could attempt a *ABBREV*DoS*-ABBREV* attack against a *DEVICETYPE* by exhausting the number of possible connections. *ABBREV*TCP*-ABBREV* keep alive messages can be configured to confirm that a remote connection is valid and then terminate any orphaned connections.*NEWPARA**COMPANY* determined that *ABBREV*TCP*-ABBREV* keep alive messages are not sent for connections from remote hosts.";
const char *report_keepalive_impact = "An attacker could attempt a *ABBREV*DoS*-ABBREV* by exhausting the number of possible connections.";
const char *report_keepalive_ease = "Tools are available on the Internet that can open large numbers of *ABBREV*TCP*-ABBREV* connections without correctly terminating them.";
const char *report_keepalive_rec = "*COMPANY* recommends that *ABBREV*TCP*-ABBREV* keep alive messages be sent to detect and drop orphaned connections from remote systems. *ABBREV*TCP*-ABBREV* keep alive messages can be enabled for connections from remote systems using the following command:*NEWPARA**COMMAND*service tcp-keepalives-in*-COMMAND*";
const char *report_keepalive_context = "TCP keep alive messages are not configured for inbound connections";
const char *report_keepalive_rectext = "Enable TCP keep alive messages for inbound connections";

// Timeouts
const char *report_timeout_title = "Connection Timeout";
const char *report_timeout_obs1 = "Connection timeouts can be configured for a number of the device services. If a timeout were configured on an administrative service, an administrator that did not correctly terminate the connection would have it automatically closed after the timeout expires. However, if a timeout is not configured, or is configured to be a long timeout, an unauthorised user may be able to gain access using the administrator's previously logged-in connection.*NEWPARA**COMPANY* identified *NUMBER* connection *SINGULA*setting that was*-SINGULA**PLAURAL*settings that were*-PLAURAL* not configured to timeout within *NONEWPARA*";
const char *report_timeout_obs2 = "*NOTEXTSTART**SINGULA*. *NONEWPARA**-SINGULA**PLAURAL*, these are listed in Table *TABLEREF*.*-PLAURAL*";
const char *report_timeout_impact = "An attacker who was able to gain access to a connection that had not expired, would be able to continue using that connection. A connection could be a console port on the device that was not correctly terminated or a remote administrative connection.";
const char *report_timeout_ease = "The attacker would have to gain physical access to the device to use the console port, or gain remote access to an administration machine that is attached to the port. To gain access to remote connections, an attacker would have to be able to intercept network traffic between the client and *DEVICENAME*. The attacker would then have to take over the connection, which could be very difficult with some services. Tools are available on the Internet that would facilitate the monitoring of network connections.";
const char *report_timeout_rec1 = "*COMPANY* recommends that a timeout period of *NONEWPARA*";
const char *report_timeout_rec2 = "*NOTEXTSTART* be configured for connections to the device *DEVICENAME*.";
const char *report_timeout_context = "all connections were not configured with secure connection timeout periods";
const char *report_timeout_rectext = "Configure secure connection time periods for all connections";
const char *report_timeout_table = "Connections with inadequate timeout periods";
struct tableHeading report_timeout_heading1 = {false, 3, "Timeout", 0};
struct tableHeading report_timeout_heading  = {false, 1, "Connection", &report_timeout_heading1};

// Aux Port
const char *report_aux_title = "Auxiliary Port";
const char *report_aux_obs = "The auxiliary port's primary purpose is to provide a remote administration capability. It can allow a remote administrator to use a modem to dial into the Cisco device.*NEWPARA**COMPANY* determined that the auxiliary port on the Cisco device *DEVICENAME* allowed exec connections and did not appear to have the callback feature configured.";
const char *report_aux_impact = "An attacker may discover the modem number for the device during a war-dial. If an attacker were able to connect to the device remotely, then they may be able to brute-force the login to gain access to the device.";
const char *report_aux_ease = "The attacker would have to first identify the telephone number of the device, probably through a war-dial. A modem attached to a telephone line would have to be attached directly to the Cisco device's auxiliary port. Then the attacker would be able to attach to the device in order to perform a brute-force of the login.";
const char *report_aux_rec = "*COMPANY* recommends that, if not required, the auxiliary port exec be disabled. Exec can be disabled on the aux port with the following command:*NEWPARA**COMMAND*no exec*-COMMAND**NEWLINE*If the auxiliary port is required for remote administration, the callback feature can be configured to dial a specific preconfigured telephone number.";
const char *report_aux_context = "the AUX port was configured to allow EXEC connections without the callback functionality";
const char *report_aux_rectext = "Disable the AUX port or configure the callback feature";

// Source IP Routing
const char *report_source_title = "IP Source Routing";
const char *report_source_obs = "*ABBREV*IP*-ABBREV* source routing is a feature whereby a network packet can specify how it should be routed through the network. Cisco routers normally accept and process source routes specified by a packet, unless the feature has been disabled.*NEWPARA**COMPANY* determined that *ABBREV*IP*-ABBREV* source routing was not disabled.";
const char *report_source_impact = "*ABBREV*IP*-ABBREV* source routing can allow an attacker to specify a route for a network packet to follow, possibly to bypass a Firewall device or an *ABBREV*IDS*-ABBREV*. An attacker could also use source routing to capture network traffic by routing it through a system controlled by the attacker.";
const char *report_source_ease = "An attacker would have to control either a routing device or an end point device in order to modify a packets route through the network. However, tools are available on the Internet that would allow an attacker to specify source routes. Tools are also available to modify network routing using vulnerabilities in some routing protocols.";
const char *report_source_rec = "*COMPANY* recommends that, if not required, IP source routing be disabled. *ABBREV*IP*-ABBREV* source routing can be disabled by issuing the following *ABBREV*IOS*-ABBREV* command:*NEWPARA**COMMAND*no ip source routing*-COMMAND*";
const char *report_source_context = "IP source routing was enabled";
const char *report_source_rectext = "Disable IP source routing";

// Finger
const char *report_finger_title = "Finger";
const char *report_finger_obs = "The finger service was traditionally installed by default on UNIX-based operating systems, though more recently it is disabled by default. The finger service is started by default on Cisco devices and was not explicitly disabled on *DEVICENAME*.";
const char *report_finger_impact = "A malicious user could use the finger service to gain information about users logged in to the device.";
const char *report_finger_ease = "Tools for querying the finger service are widely available on the Internet and some operating systems include the tools by default.";
const char *report_finger_rec = "*COMPANY* recommends that, if not required, the finger service be disabled. Users who do not have authenticated access to the device do not normally need to know who is logged in to the device. Users who have authenticated access to the device are able to log in and show the current users using the following Cisco *ABBREV*IOS*-ABBREV* command:*NEWPARA**COMMAND*show users*-COMMAND**NEWLINE*The following Cisco *ABBREV*IOS*-ABBREV* commands can be used to disable the finger service:*NEWPARA**COMMAND*no ip finger*-COMMAND**NEWLINE**COMMAND*no service finger*-COMMAND*";
const char *report_finger_context = "the finger service was enabled";
const char *report_finger_rectext = "Disable the finger service";

// HTTP Redirect
const char *report_httpred_title = "Administrative HTTP Redirect";
const char *report_httpred_obs = "The HTTP redirection setting redirects *ABBREV*HTTP*-ABBREV* administrative traffic to the security device to *ABBREV*HTTPS*-ABBREV* (on port 443 by default). This ensures that all web-based administration is performed using the secure *ABBREV*HTTPS*-ABBREV* protocol.*NEWPARA**COMPANY* determined that the ScreenOS device *DEVICENAME* was not configured with the *ABBREV*HTTP*-ABBREV* redirect setting. However, it should be noted that the *ABBREV*HTTP*-ABBREV* redirect setting is enabled by default on ScreenOS versions 5.1.0 or latter.";
const char *report_httpred_impact = "An attacker who was able to monitor network traffic could capture authentication credentials for the device *DEVICENAME*.";
const char *report_httpred_ease = "Network packet and password sniffing tools are widely available on the Internet. Once authentication credentials have been captured, an attacker with access to the devices management services could use them to gain access.";
const char *report_httpred_rec = "*COMPANY* recommends the *ABBREV*HTTP*-ABBREV* redirect administration setting be configured to force access to the device using the cryptographically secure *ABBREV*HTTPS*-ABBREV* protocol. The following command will set the administrative *ABBREV*HTTP*-ABBREV* redirect setting:*NEWPARA**COMMAND*set admin http redirect*-COMMAND*";
const char *report_httpred_context = "administrative HTTP access does not redirect to HTTPS";
const char *report_httpred_rectext = "Configure administrative HTTP redirect";

// HTTP
const char *report_http_title = "HyperText Transport Protocol Service";
const char *report_http_obs1 = "Recent Cisco IOS-based devices support web-based administration using the *ABBREV*HTTP*-ABBREV* protocol. Cisco web-based administration facilities can sometimes be basic but they do provide a simple method of administering remote devices. However, *ABBREV*HTTP*-ABBREV* is a clear-text protocol and is vulnerable to various packet-capture techniques.";
const char *report_http_obs2 = "Even though the *ABBREV*HTTP*-ABBREV* service had not been configured, it can be enabled by default on some Cisco devices.";
const char *report_http_obs3 = "The *ABBREV*HTTP*-ABBREV* service was not configured to restrict network access to the device using an access list. Additionally, the device used the default authentication option, using the enable password to authenticate remote users.";
const char *report_http_obs4 = "The *ABBREV*HTTP*-ABBREV* service was not configured with an access-list to restrict network access to the device.";
const char *report_http_obs5 = "The *ABBREV*HTTP*-ABBREV* service was configured to use the default authentication option, using the enable password to authenticate remote users.";
const char *report_http_obs6 = "The *ABBREV*HTTP*-ABBREV* service was configured and made use of an access-list to restrict access to the device.";
const char *report_http_impact1 = "An attacker who was able to monitor network traffic could capture authentication credentials. *NONEWPARA*";
const char *report_http_impact2 = "*NOTEXTSTART*This issue is made more serious with the enable password being used for authentication as this would give the attacker full administrative access to the device with the captured credentials. *NONEWPARA*";
const char *report_http_impact3 = "*NOTEXTSTART*However, this issue is mitigated slightly by employing an access list to restrict network access to the device.";
const char *report_http_ease1 = "Network packet and password sniffing tools are widely available on the Internet. Once authentication credentials have been captured it is trivial to use the credentials to log in using the captured credentials. *NONEWPARA*";
const char *report_http_ease2 = "Furthermore, it may be possible for an attacker to masquerade as the administrators host in order to bypass configured network access restrictions.";
const char *report_http_rec1 = "*COMPANY* recommends that, if not required, the *ABBREV*HTTP*-ABBREV* service be disabled. If a remote method of access to the device is required, consider using *ABBREV*HTTPS*-ABBREV* or *ABBREV*SSH*-ABBREV*. The encrypted *ABBREV*HTTPS*-ABBREV* and *ABBREV*SSH*-ABBREV* services may require a firmware or hardware upgrade. The *ABBREV*HTTP*-ABBREV* service can be disabled with the following *ABBREV*IOS*-ABBREV* command:*NEWPARA**COMMAND*no ip http server*-COMMAND**NEWLINE*If it is not possible to upgrade the device to use the encrypted *ABBREV*HTTPS*-ABBREV* or *ABBREV*SSH*-ABBREV* services, additional security can be configured. *NONEWPARA*";
const char *report_http_rec2 = "*NOTEXTSTART*An access list can be configured to restrict access to the device. An access list can be specified with the following command:*NEWPARA**COMMAND*ip http access-class *CMDREQUIRE**CMDUSER*access list number*-CMDUSER**-CMDREQUIRE**-COMMAND*";
const char *report_http_rec3 = "The authentication method can be changed using the following command (where the authentication method is either local, enable, tacacs or aaa):*NEWPARA**COMMAND*ip http authentication *CMDOPTION**CMDUSER*authentication method*-CMDUSER**-CMDOPTION**-COMMAND*";
const char *report_http_context = "clear-text remote web-based administration was enabled using HTTP";
const char *report_http_rectext = "Disable HTTP access to the device";

// SNMP
const char *report_snmp_title = "Simple Network Management Protocol";
const char *report_snmp_obs = "*COMPANY* determined that *ABBREV*SNMP*-ABBREV* protocol version *SINGULA*1 was configured on *DEVICENAME**-SINGULA**PLAURAL*2c was configured on *DEVICENAME**-PLAURAL**NEGATIVE*3 was configured without Auth and Priv authentication*-NEGATIVE*.";
const char *report_snmp_pix_obs = "*DEVICETYPE* devices support only *ABBREV*SNMP*-ABBREV* protocol versions 1 and 2c. *COMPANY* determined that *POSITIVE**ABBREV*SNMP*-ABBREV* was configured on *DEVICENAME*.*PLAURAL* Furthermore, *DEVICENAME* was configured to send *ABBREV*SNMP*-ABBREV* traps to other hosts.*-PLAURAL**NEGATIVE**DEVICENAME* was configured to send *ABBREV*SNMP*-ABBREV* traps to other hosts.*-NEGATIVE*";
const char *report_snmp_css_obs = "*DEVICETYPE* devices support only *ABBREV*SNMP*-ABBREV* protocol versions 1 and 2c. *COMPANY* determined that *ABBREV*SNMP*-ABBREV* was configured on *DEVICENAME*.*NEGATIVE* Furthermore, *COMPANY* determined that *DEVICENAME* was configured to send *ABBREV*SNMP*-ABBREV* traps to other hosts.*-NEGATIVE*";
const char *report_snmp_impact = "Due to the unencrypted nature of *ABBREV*SNMP*-ABBREV* protocol versions 1 and 2c, an attacker who was able to monitor network traffic could capture device configuration settings, including authentication details.";
const char *report_snmp_ease = "Network packet monitoring and capture tools are widely available on the Internet and *ABBREV*SNMP*-ABBREV* tools are included as standard with some operating systems.";
const char *report_snmp_rec = "*COMPANY* recommends that, if possible, *ABBREV*SNMP*-ABBREV* version *SINGULA*1 be disabled. Furthermore, *COMPANY* recommends that, if *ABBREV*SNMP*-ABBREV* is required, protocol version *-SINGULA**PLAURAL*2c be disabled. Furthermore, *COMPANY* recommends that, if *ABBREV*SNMP*-ABBREV* is required, protocol version *-PLAURAL*3 be configured with Auth and Priv authentication. *SINGULA**ABBREV*SNMP*-ABBREV* protocol version 1 can be disabled with the following command for each community string:*NEWPARA**COMMAND*no snmp-server community *CMDREQUIRE**CMDUSER*Community String*-CMDUSER**-CMDREQUIRE* *CMDREQUIRE**CMDOPTION*RO*-CMDOPTION* *CMDOR* *CMDOPTION*RW*-CMDOPTION**-CMDREQUIRE**-COMMAND**NEWLINE**-SINGULA**PLAURAL**ABBREV*SNMP*-ABBREV* protocol version 2c can be disabled with the following command for each community string:*NEWPARA**COMMAND*no snmp-server community *CMDREQUIRE*Community String*-CMDREQUIRE* *CMDREQUIRE**CMDOPTION*RO*-CMDOPTION* *CMDOR* *CMDOPTION*RW*-CMDOPTION**-CMDREQUIRE**-COMMAND**NEWLINE**-PLAURAL**ABBREV*SNMP*-ABBREV* version 3 Auth and Priv access can be configured with the following commands:*NEWPARA**COMMAND*snmp-server group *CMDREQUIRE**CMDUSER*Group Name*-CMDUSER**-CMDREQUIRE* v3 priv*-COMMAND**NEWLINE**COMMAND*snmp-server user *CMDREQUIRE**CMDUSER*Username*-CMDUSER**-CMDREQUIRE* *CMDREQUIRE**CMDUSER*Group Name*-CMDUSER**-CMDREQUIRE* v3 auth md5 *CMDREQUIRE**CMDUSER*Auth Keyword*-CMDUSER**-CMDREQUIRE* priv *CMDREQUIRE**CMDOPTION*3des*-CMDOPTION* *CMDOR* *CMDOPTION*aes 128*-CMDOPTION* *CMDOR* *CMDOPTION*aes 192*-CMDOPTION**-CMDREQUIRE* *CMDREQUIRE**CMDUSER*Priv Keyword*-CMDUSER**-CMDREQUIRE**-COMMAND*";
const char *report_snmp_pix_rec = "On *DEVICETYPE* devices, *ABBREV*SNMP*-ABBREV* version 3 with auth and priv authentication cannot be configured. Therefore, *COMPANY* recommends that, if not required, *ABBREV*SNMP*-ABBREV* be disabled. *NEGATIVE*Additionally, *COMPANY* recommends that, if not required, the sending of *ABBREV*SNMP*-ABBREV* traps to other hosts be disabled. *-NEGATIVE**ABBREV*SNMP*-ABBREV* access to *DEVICENAME* can be disabled with the following command:*NEWPARA**COMMAND*no snmp-server enable*-COMMAND*";
const char *report_snmp_pix2_rec = "On *DEVICETYPE* devices, *ABBREV*SNMP*-ABBREV* version 3 with auth and priv authentication cannot be configured. Therefore, *COMPANY* recommends that, if not required, the sending of *ABBREV*SNMP*-ABBREV* traps to other hosts be disabled.";
const char *report_snmp_css_rec = "On *DEVICETYPE* devices, *ABBREV*SNMP*-ABBREV* version 3 with auth and priv authentication cannot be configured. Therefore, *COMPANY* recommends that, if not required, *ABBREV*SNMP*-ABBREV* be disabled. *NEGATIVE*Additionally, *COMPANY* recommends that, if not required, the sending of *ABBREV*SNMP*-ABBREV* traps to other hosts be disabled. *-NEGATIVE**ABBREV*SNMP*-ABBREV* access to *DEVICENAME* can be disabled with the following command:*NEWPARA**COMMAND*restrict snmp*-COMMAND*";
const char *report_snmp_sos_rec = "On *DEVICETYPE* devices, *ABBREV*SNMP*-ABBREV* version 3 with auth and priv authentication cannot be configured. Therefore, *COMPANY* recommends that, if not required, *ABBREV*SNMP*-ABBREV* be disabled. *NEGATIVE*Additionally, *COMPANY* recommends that, if not required, the sending of *ABBREV*SNMP*-ABBREV* traps to other hosts be disabled. *-NEGATIVE**ABBREV*SNMP*-ABBREV* access to *DEVICENAME* can be disabled with the following command:*NEWPARA**COMMAND*unset snmp *CMDREQUIRE**CMDUSER*community*-CMDUSER**-CMDREQUIRE**-COMMAND*";
const char *report_snmp_context = "clear-text remote administration was enabled using SNMP";
const char *report_snmp_rectext = "Disable SNMP or configure SNMP v3 with auth and priv authentication";
const char *report_snmp_css_rectext = "Disable SNMP";

// Telnet
const char *report_telnet_title = "Telnet";
const char *report_telnet_obs = "Telnet is widely used to provide remote command-based access to a variety of devices and is commonly used on network devices for remote administration. However, Telnet is a clear-text protocol and is vulnerable to various packet capture techniques.*NEWPARA**COMPANY* determined that Telnet was enabled on *DEVICENAME*.";
const char *report_telnet_impact = "An attacker who was able to monitor network traffic could capture sensitive information or authentication credentials.";
const char *report_telnet_ease = "Network packet and password sniffing tools are widely available on the Internet and some of the tools are specifically designed to capture clear-text protocol authentication credentials. However, in a switched environment an attacker may not be able to capture network traffic destined for other devices without employing an attack such as *ABBREV*ARP*-ABBREV* spoofing.";
const char *report_telnet_rec1 = "*COMPANY* recommends that, if possible, Telnet be disabled. If remote administrative access to the device is required, *COMPANY* recommends that *ABBREV*SSH*-ABBREV* be configured.*SINGULA* An *ABBREV*IOS*-ABBREV* upgrade may be required to add support for *ABBREV*SSH*-ABBREV* to *DEVICENAME*. Cisco introduced *ABBREV*SSH*-ABBREV* into *ABBREV*IOS*-ABBREV* releases starting with *ABBREV*IOS*-ABBREV* version 12.0.5.S.*-SINGULA* The Telnet service can be disabled on individual lines with the following command:*NEWPARA**COMMAND*transport input none*-COMMAND**NEWLINE*The following Cisco *ABBREV*IOS*-ABBREV* command can be used to disable Telnet on individual lines, but enable *ABBREV*SSH*-ABBREV*:*NEWPARA**COMMAND*transport input ssh*-COMMAND*";
const char *report_telnet_rec2 = "Furthermore, if Telnet or *ABBREV*SSH*-ABBREV* are used for remote administration, *COMPANY* recommends that inbound *ABBREV*ACL*-ABBREV* be configured to restrict access.";
const char *report_css_telnet_rec = "*COMPANY* recommends that, if possible, Telnet be disabled. If Telnet is required, *COMPANY* recommends that filtering be implemented to restrict access. Telnet can be disabled with the following command:*NEWPARA**COMMAND*restrict telnet*-COMMAND*";
const char *report_telnet_context = "clear-text remote administration was enabled using Telnet";
const char *report_telnet_rectext = "Disable Telnet access";

// ICMP Redirects
const char *report_redirects_title = "ICMP Redirects";
const char *report_redirects_obs = "*ABBREV*ICMP*-ABBREV* redirect messages allow systems to change the route that network traffic takes. On networks with functional network routing, disabling *ABBREV*ICMP*-ABBREV* redirects will have little to no effect. *ABBREV*ICMP*-ABBREV* redirects are usually enabled by default on Cisco devices.*NEWPARA**COMPANY* determined that the device *DEVICENAME* had support for *ABBREV*ICMP*-ABBREV* redirects enabled*SINGULA* on the network interface *NONEWPARA**-SINGULA**PLAURAL* on the network interfaces listed in Table *TABLEREF**-PLAURAL*.";
const char *report_redirects_impact = "An attacker could use *ABBREV*ICMP*-ABBREV* redirect messages to route network traffic through their own router, possibly allowing them to monitor network traffic.";
const char *report_redirects_ease = "Tools are widely available that can send *ABBREV*ICMP*-ABBREV* redirect messages.";
const char *report_redirects_rec = "*COMPANY* recommends that, if not required, *ABBREV*ICMP*-ABBREV* redirects be disabled on all network interfaces. *ABBREV*ICMP*-ABBREV* redirects can be disabled on each individual network interface using the following command:*NEWPARA**COMMAND*no ip redirects*-COMMAND*";
const char *report_redirects_rec2 = "*COMPANY* recommends that, if not required, *ABBREV*ICMP*-ABBREV* redirects be disabled. *ABBREV*ICMP*-ABBREV* redirects can be disabled with the following command:*NEWPARA**COMMAND*set ip redirect disable*-COMMAND*";
const char *report_redirects_context = "ICMP redirects were not disabled for all network interfaces";
const char *report_redirects_rectext = "Disable ICMP redirects on all network interfaces";
const char *report_redirects_table = "Interfaces with ICMP redirects enabled";

// Default Firewall Policy
const char *report_defaultpolicy_title = "Default Policy";
const char *report_defaultpolicy_obs = "The *DEVICETYPE* has a default policy to determine if network traffic is permitted or denied when no rules exist that match the network traffic, or if no rules exist at all. *COMPANY* determined that the default policy was to allow the network traffic.";
const char *report_defaultpolicy_impact = "If the default policy allows network traffic, a device with no rules could enable an attacker to access devices and services which they should not be able to access. If the device was configured with rules, the attacker could access services or devices for which no blocking rule exists.";
const char *report_defaultpolicy_ease = "";
const char *report_defaultpolicy_rec = "*COMPANY* recommends that the default policy denies all network traffic. On *DEVICETYPE* the manufacturer default is to deny traffic by default, to return the device to its default setting use the following command:*NEWPARA**COMMAND*unset policy default-permit-all*-COMMAND*";
const char *report_defaultpolicy_context = "the device was configured to default to allowing all traffic";
const char *report_defaultpolicy_rectext = "Set the device to deny all traffic by default";

// Insecure FW-1 Policy Collections
const char *report_fw1policy_title = "Policy Collections";
const char *report_fw1policy_obs = "Policy collections are used to determine which network traffic is allowed or dropped in the different networks controlled by *DEVICETYPE*. *COMPANY* *NEGATIVE*determined that no policy collections were configured.*-NEGATIVE**POSITIVE*identified *NUMBER* security-related issue*PLAURAL*s with the policy collection rules, these are listed in Table *TABLEREF*.*-PLAURAL**SINGULA* with the policy collection rules. *NONEWPARA**-SINGULA**-POSITIVE*";
const char *report_fw1policy_impact = "*NEGATIVE*If no policy collections are configured the *DEVICETYPE* is redundant and simply provides the attacker with an additional network device to attack.*-NEGATIVE**POSITIVE*If policy collections are not sufficiently restrictive, an attacker may be able to access services or network devices that should not be accessible. Furthermore, an attacker who had compromised a device could install a backdoor which could listen on a network port that was not filtered.*-POSITIVE*";
const char *report_fw1policy_ease = "";
const char *report_fw1policy_rec1 = "*COMPANY* recommends that *NEGATIVE*policy collections be configured on the *DEVICETYPE*. However, if it is not required, *COMPANY* recommends that the firewall be decommisioned. If policy collections are configured, *COMPANY* recommends that:*-NEGATIVE**POSITIVE*the policy collections be reviewed and, where possible, modified to ensure that:*-POSITIVE**NONEWPARA*";
// Rec2 is used by ScreenOS, PIX and CSS as well
const char *report_fw1policy_rec2 = "*NOTEXTSTART*However, in certain circumstances, such as a public web server, a more relaxed configuration may be required to allow any host to access specific hosts and services.";
const char *report_fw1policy_context = "insecure policy collection rules were configured";
const char *report_fw1policy_rectext = "Review the insecure policy collection rules and reconfigure";
// Descriptions below are used for ScreenOS/Cisco/Passport devices (except denylog and bypass)...
const char *report_fw1policy_denylog = "policy collection does not end with a deny all and log.";
const char *report_fw1policy_anysrc = "allows access from any source to ";
const char *report_fw1policy_netsrc = "allows access from a network source to ";
const char *report_fw1policy_anysvcsrc = "allows access from any source port to ";
const char *report_fw1policy_std_anysrc = "allows access from any source.";
const char *report_fw1policy_std_netsrc = "allows access from a network source.";
const char *report_fw1policy_std_anysvcsrc = "allows access from any source port.";
const char *report_fw1policy_anydst = "allows access from ";
const char *report_fw1policy_netdst = "allows access from ";
const char *report_fw1policy_netdstsvc = "allows access from ";
const char *report_fw1policy_nolog = "does not log.";
const char *report_fw1policy_nologdenied = "does not log denied access.";
const char *report_fw1policy_reject = "responds to denied network access.";
const char *report_fw1policy_default = "was set to the default action.";
const char *report_fw1policy_bypass = "bypasses the remaining policy collection rules.";
const char *report_fw1policy_disabled = "was disabled.";
const char *report_fw1policyt_denylog = "Policy collection does not end with a deny all and log.";
// Descriptions below are used for ScreenOS/Cisco/Passport devices (except denylog and bypass)...
const char *report_fw1policyt_anysrc = "Allows access from any source to ";
const char *report_fw1policyt_netsrc = "Allows access from a network source to ";
const char *report_fw1policyt_anysvcsrc = "Allows access from any source port to ";
const char *report_fw1policyt_std_anysrc = "Allows access from any source.";
const char *report_fw1policyt_std_netsrc = "Allows access from a network source.";
const char *report_fw1policyt_std_anysvcsrc = "Allows access from any source port.";
const char *report_fw1policyt_anydst = "Allows access from ";
const char *report_fw1policyt_nolog = "Does not log.";
const char *report_fw1policyt_nologdenied = "Does not log denied access.";
const char *report_fw1policyt_reject = "Responds to denied network access.";
const char *report_fw1policyt_bypass = "Bypasses the remaining policy collection rules.";
const char *report_fw1policyt_default = "Was set to the default action.";
const char *report_fw1policyt_disabled = "Was disabled.";
const char *report_fw1policy_table = "Insecure policy collection rules";
struct tableHeading report_fw1policy_heading2 = {false, 5, "Description", 0};
struct tableHeading report_fw1policy_heading1 = {false, 1, "Rule", &report_fw1policy_heading2};
struct tableHeading report_fw1policy_heading  = {false, 2, "Collection", &report_fw1policy_heading1};
struct tableHeading report_fw1issues_heading12 = {false, 1, "policy collections end with a deny all and log", 0};
struct tableHeading report_fw1issues_heading11 = {false, 1, "logging be enabled for all policy rules", &report_fw1issues_heading12};
struct tableHeading report_fw1issues_heading10 = {false, 1, "policy rules should not have a default action", &report_fw1issues_heading11};
struct tableHeading report_fw1issues_heading9  = {false, 1, "policy rules should not be bypassed", &report_fw1issues_heading10};
struct tableHeading report_fw1issues_heading8  = {false, 1, "policy rules should not reject packets", &report_fw1issues_heading9};
struct tableHeading report_fw1issues_heading7  = {false, 1, "disabled policy rules are removed", &report_fw1issues_heading8};
struct tableHeading report_fw1issues_heading6  = {false, 1, "policy rules log denied access", &report_fw1issues_heading7};
struct tableHeading report_fw1issues_heading5  = {false, 1, "policy rules do not allow access to any destination port", &report_fw1issues_heading6};
struct tableHeading report_fw1issues_heading4  = {false, 1, "policy rules do not allow access to entire destination networks", &report_fw1issues_heading5};
struct tableHeading report_fw1issues_heading3  = {false, 1, "policy rules do not allow access to any destination", &report_fw1issues_heading4};
struct tableHeading report_fw1issues_heading2  = {false, 1, "policy rules do not allow access from any source port", &report_fw1issues_heading3};
struct tableHeading report_fw1issues_heading1  = {false, 1, "policy rules do not allow access from entire source networks", &report_fw1issues_heading2};
struct tableHeading report_fw1issues_heading   = {false, 1, "policy rules do not allow access from any source", &report_fw1issues_heading1};

// Insecure ScreenOS Policy Lists
const char *report_policy_title = "Policy Lists";
const char *report_policy_obs = "Policy lists are used to determined which network traffic is allowed and which is dropped between different zones (interzone), between interfaces in the same zone (intrazone) and the global zone. If a policy has not been configured, any network traffic is blocked by default.*NEWPARA**COMPANY* *POSITIVE*identified *NUMBER* insecure policy list rule*-POSITIVE**PLAURAL*s, these are listed in Table *TABLEREF**-PLAURAL**NEGATIVE*determined that no policies were configured*-NEGATIVE*.*SINGULA* *NONEWPARA**-SINGULA*";
const char *report_sospolicy_denylog = "policy list does not end with a deny all and log.";
const char *report_sospolicy_bypass = "bypasses the remaining policy list rules.";
const char *report_sospolicyt_denylog = "Policy list does not end with a deny all and log.";
const char *report_sospolicyt_bypass = "Bypasses the remaining policy list rules.";
// All the other descriptions are the same as FW1 ones.
const char *report_nopolicy_impact = "With no policies configured the default policy for *DEVICETYPE* will take effect. *NEGATIVE*The default policy will allow all network traffic, enabling an attacker to access devices and services which they should not be able to access.*-NEGATIVE**POSITIVE*The default policy on *DEVICETYPE* denies all network traffic.*-POSITIVE*";
const char *report_policy_impact = "If policy lists are not sufficiently restrictive, an attacker may be able to access services or network devices that should not be accessible. Furthermore, an attacker who had compromised a device could install a backdoor which could listen on a network port that was not filtered.*PLAURAL* Additionally, network traffic that is rejected instead of denied makes an attackers scans quicker as the attacker will receive a *ABBREV*TCP*-ABBREV* reset. If the traffic were denied instead, the attackers scans would be slower as they wait for a response and eventually timeout.*-PLAURAL*";
const char *report_policy_ease = "";
const char *report_nopolicy_rec1 = "*COMPANY* recommends that policies be configured to ensure that:*NONEWPARA*";
const char *report_nopolicy_rec2 = "If *DEVICENAME* is not required, *COMPANY* recommends that it be decommissioned.";
const char *report_policy_rec1 = "*COMPANY* recommends that the policy lists be reviewed and, where possible, modified to ensure that:*NONEWPARA*";
const char *report_nopolicy_context = "no policy lists were configured";
const char *report_nopolicy_rectext = "Configure a policy or decommission the device";
const char *report_policy_context = "insecure policy lists were configured";
const char *report_policy_rectext = "Review the insecure policy list rules and reconfigure";
const char *report_policy_table = "Insecure policy list rules";
struct tableHeading report_policy_heading4 = {false, 4, "Description", 0};
struct tableHeading report_policy_heading3 = {false, 1, "ID", &report_policy_heading4};
struct tableHeading report_policy_heading2 = {false, 1, "Global Zone", &report_policy_heading3};
struct tableHeading report_policy_heading1 = {false, 2, "To Zone", &report_policy_heading2};
struct tableHeading report_policy_heading  = {false, 2, "From Zone", &report_policy_heading1};
struct tableHeading report_issues_heading12 = {false, 1, "policy lists end with a deny all and log", 0};
struct tableHeading report_issues_heading11 = {false, 1, "logging be enabled for all policy rules", &report_issues_heading12};
struct tableHeading report_issues_heading10 = {false, 1, "policy rules should not be have a default action", &report_issues_heading11};
struct tableHeading report_issues_heading9  = {false, 1, "policy rules should not be bypassed", &report_issues_heading10};
struct tableHeading report_issues_heading8  = {false, 1, "policy rules should not reject packets", &report_issues_heading9};
struct tableHeading report_issues_heading7  = {false, 1, "disabled policy rules are removed", &report_issues_heading8};
struct tableHeading report_issues_heading6  = {false, 1, "policy rules log denied access", &report_issues_heading7};
struct tableHeading report_issues_heading5  = {false, 1, "policy rules do not allow access to any destination port", &report_issues_heading6};
struct tableHeading report_issues_heading4  = {false, 1, "policy rules do not allow access to entire destination networks", &report_issues_heading5};
struct tableHeading report_issues_heading3  = {false, 1, "policy rules do not allow access to any destination", &report_issues_heading4};
struct tableHeading report_issues_heading2  = {false, 1, "policy rules do not allow access from any source port", &report_issues_heading3};
struct tableHeading report_issues_heading1  = {false, 1, "policy rules do not allow access from entire source networks", &report_issues_heading2};
struct tableHeading report_issues_heading   = {false, 1, "policy rules do not allow access from any source", &report_issues_heading1};

// SonicOS Access Rules
const char *report_sonicosrules_title = "Access Rules";
const char *report_sonicosrules_obs = "*DEVICETYPE* access rules are sequential lists of allow, deny and discard rules that specify whether network traffic should be allowed or dropped. Both the deny and discard actions block the traffic that matches the rule, but a deny will notify the sender that the packet was blocked. Access rules are used to restrict access to services and network devices, preventing access to services and devices that should not be accessible.*NEWPARA**COMPANY* identified *NUMBER* security-related issue*PLAURAL*s*-PLAURAL* with the configured access rules*PLAURAL*, these are listed in Table *TABLEREF*.*-PLAURAL**SINGULA*. *NONEWPARA**-SINGULA*";
const char *report_sonicosrules_impact = "If access rules are not sufficiently restrictive, an attacker may be able to access services or network devices that should not be accessible. Furthermore, an attacker who had compromised a device could install a backdoor which could listen on a network port that was not filtered.";
const char *report_sonicosrules_ease = "";
const char *report_sonicosrules_rec = "*COMPANY* recommends that the access rules be reviewed and, where possible, modified to ensure that:*NONEWPARA*";
const char *report_sonicosrules_context = "insecure access rules were configured";
const char *report_sonicosrules_rectext = "Configure all access rules to only allow access to the hosts and services required";
struct tableHeading report_sonicosrules_heading12 = {false, 1, "access rule lists end with a deny all and log", 0};
struct tableHeading report_sonicosrules_heading11 = {false, 1, "logging be enabled for all access rules", &report_sonicosrules_heading12};
struct tableHeading report_sonicosrules_heading10 = {false, 1, "access rules should not be have a default action", &report_sonicosrules_heading11};
struct tableHeading report_sonicosrules_heading9  = {false, 1, "access rules should not be bypassed", &report_sonicosrules_heading10};
struct tableHeading report_sonicosrules_heading8  = {false, 1, "access rules should not deny packets", &report_sonicosrules_heading9};
struct tableHeading report_sonicosrules_heading7  = {false, 1, "disabled access rules are removed", &report_sonicosrules_heading8};
struct tableHeading report_sonicosrules_heading6  = {false, 1, "access rules log denied access", &report_sonicosrules_heading7};
struct tableHeading report_sonicosrules_heading5  = {false, 1, "access rules do not allow access to any destination port", &report_sonicosrules_heading6};
struct tableHeading report_sonicosrules_heading4  = {false, 1, "access rules do not allow access to entire destination networks", &report_sonicosrules_heading5};
struct tableHeading report_sonicosrules_heading3  = {false, 1, "access rules do not allow access to any destination", &report_sonicosrules_heading4};
struct tableHeading report_sonicosrules_heading2  = {false, 1, "access rules do not allow access from any source port", &report_sonicosrules_heading3};
struct tableHeading report_sonicosrules_heading1  = {false, 1, "access rules do not allow access from entire source networks", &report_sonicosrules_heading2};
struct tableHeading report_sonicosrules_heading   = {false, 1, "access rules do not allow access from any source", &report_sonicosrules_heading1};
struct tableHeading report_sonicosaccess_heading3 = {false, 4, "Description", 0};
struct tableHeading report_sonicosaccess_heading2 = {false, 1, "Rule", &report_sonicosaccess_heading3};
struct tableHeading report_sonicosaccess_heading1 = {false, 2, "To", &report_sonicosaccess_heading2};
struct tableHeading report_sonicosaccess_heading  = {false, 2, "From", &report_sonicosaccess_heading1};
const char *report_sonicosaccess_table = "Insecure access rules";
const char *report_sonicosrules_denylog = "policy list does not end with a deny all and log.";
const char *report_sonicosrulest_denylog = "Policy list does not end with a deny all and log.";

// PIX/IOS Access-Lists
const char *report_accesslist_title = "Access Control Lists";
const char *report_accesslist_obs1 = "*ABBREV*ACL*-ABBREV* are sequential lists of allow and deny *ABBREV*ACEs*-ABBREV* that specify whether network traffic should be allowed or dropped. *ABBREV*ACLs*-ABBREV* are used to restrict access to services and network devices, preventing access to services and devices that should not be accessible.*NEWPARA**COMPANY* *NEGATIVE*determined that no *ABBREV*ACL*-ABBREV* were configured on *DEVICENAME*.*-NEGATIVE**POSITIVE*identified *NUMBER* security-related issue*PLAURAL*s*-PLAURAL* with the configured *ABBREV*ACL*-ABBREV**PLAURAL*, these are listed in Table *TABLEREF**-PLAURAL*.*SINGULA* *NONEWPARA**-SINGULA**-POSITIVE*";
const char *report_accesslist_impact = "*NEGATIVE*With no *ABBREV*ACL*-ABBREV* configured*-NEGATIVE**POSITIVE*If *ABBREV*ACEs*-ABBREV* are not sufficiently restrictive*-POSITIVE*, an attacker may be able to access services or network devices that should not be accessible. Furthermore, an attacker who had compromised a device could install a backdoor which could listen on a network port that was not filtered.";
const char *report_accesslist_noacl_pix_impact = "If no *ABBREV*ACL*-ABBREV* are configured the *DEVICETYPE* is redundant and simply provides the attacker with an additional network device to attack.";
const char *report_accesslist_ease = "";
const char *report_accesslist_rec = "*COMPANY* recommends that *NEGATIVE**ABBREV*ACL*-ABBREV* be configured to restrict access to devices and services. Furthermore, *COMPANY* recommends that:*-NEGATIVE**POSITIVE*the *ABBREV*ACLs*-ABBREV* be reviewed and, where possible, modified to ensure that:*-POSITIVE**NONEWPARA*";
const char *report_accesslist_context = "insecure ACL were configured";
const char *report_accesslist_rectext = "Configure all ACL to only allow access to the hosts and services required";
const char *report_accesslist2_rectext = "Configure all ACL to only allow access to the hosts and services required and log all blocked traffic";
struct tableHeading report_aclrec_heading12 = {false, 1, "ACL end with a deny all and log", 0};
struct tableHeading report_aclrec_heading11 = {false, 1, "logging be enabled for all ACE", &report_aclrec_heading12};
struct tableHeading report_aclrec_heading10 = {false, 1, "ACE should not have a default action", &report_aclrec_heading11};
struct tableHeading report_aclrec_heading9  = {false, 1, "ACL should not be bypassed", &report_aclrec_heading10};
struct tableHeading report_aclrec_heading8  = {false, 1, "ACE should not reject packets", &report_aclrec_heading9};
struct tableHeading report_aclrec_heading7  = {false, 1, "disabled ACE are removed", &report_aclrec_heading8};
struct tableHeading report_aclrec_heading6  = {false, 1, "ACE log denied access", &report_aclrec_heading7};
struct tableHeading report_aclrec_heading5  = {false, 1, "ACE do not allow access to any destination port", &report_aclrec_heading6};
struct tableHeading report_aclrec_heading4  = {false, 1, "ACE do not allow access to entire destination networks", &report_aclrec_heading5};
struct tableHeading report_aclrec_heading3  = {false, 1, "ACE do not allow access to any destination", &report_aclrec_heading4};
struct tableHeading report_aclrec_heading2  = {false, 1, "ACE do not allow access from any source port", &report_aclrec_heading3};
struct tableHeading report_aclrec_heading1  = {false, 1, "ACE do not allow access from entire source networks", &report_aclrec_heading2};
struct tableHeading report_aclrec_heading   = {false, 1, "ACE do not allow access from any source", &report_aclrec_heading1};
const char *report_accesslist_table1 = "Insecure Access Control Entries";
const char *report_accesslist_denylog = "ACL does not end with a deny all and log.";
const char *report_accesslist_std_denylog = "ACL does not end with a deny and log.";
const char *report_accesslist_bypass = "bypasses the remaining ACEs.";
const char *report_accesslistt_bypass = "Bypasses the remaining ACEs.";
const char *report_accesslist_old = "The ACL";
const char *report_accesslist_std = "The standard ACL";
const char *report_accesslist_ext = "The extended ACL";
struct tableHeading report_accesslist_heading3 = {false, 65, "Description", 0};
struct tableHeading report_accesslist_heading2 = {false, 15, "Type", &report_accesslist_heading3};
struct tableHeading report_accesslist_heading1 = {false, 10, "Line", &report_accesslist_heading2};
struct tableHeading report_accesslist_heading  = {false, 10, "ACL", &report_accesslist_heading1};
struct tableHeading report_accesslists_heading2 = {false, 4, "Description", 0};
struct tableHeading report_accesslists_heading1 = {false, 1, "Line", &report_accesslists_heading2};
struct tableHeading report_accesslists_heading  = {false, 2, "ACL", &report_accesslists_heading1};

// Cisco CSS ACL...
const char *report_accesslist_css_obs = "*ABBREV*ACL*-ABBREV* are sequential lists of allow, deny and bypass clauses that determine whether network traffic is permitted or dropped. All *ABBREV*ACLs*-ABBREV* have a hidden deny all clause as the final clause, clause 255. *ABBREV*ACLs*-ABBREV* are used to restrict access to services and network devices, preventing access to services and devices that should not be accessible.*NEWPARA**COMPANY* *NEGATIVE*determined that no *ABBREV*ACL*-ABBREV* were configured*-NEGATIVE**SINGULA*identified *NUMBER* insecure *ABBREV*ACL*-ABBREV* clause, *NONEWPARA**-SINGULA**PLAURAL*identified *NUMBER* insecure *ABBREV*ACL*-ABBREV* clauses, these are listed in Table *TABLEREF**-PLAURAL*.";
const char *report_accesslist_css_impact = "*POSITIVE*If *ABBREV*ACL*-ABBREV* clauses are not sufficiently restrictive*-POSITIVE**NEGATIVE*With no *ABBREV*ACL*-ABBREV* configured*-NEGATIVE*, an attacker may be able to access services or network devices that should not be accessible. Furthermore, an attacker who had compromised a device could install some backdoor software which could listen on a network port that was not filtered.";
const char *report_accesslist_css_bypass = "bypasses the remaining clauses.";
const char *report_accesslistt_css_bypass = "Bypasses the remaining clauses.";
const char *report_accesslist_css_table = "Insecure ACL Clauses";
struct tableHeading report_aclrec_css_heading12 = {false, 1, "ACL end with a deny all and log", 0};
struct tableHeading report_aclrec_css_heading11 = {false, 1, "logging be enabled for all clauses", &report_aclrec_css_heading12};
struct tableHeading report_aclrec_css_heading10 = {false, 1, "clauses should not have a default action", &report_aclrec_css_heading11};
struct tableHeading report_aclrec_css_heading9  = {false, 1, "ACL should not be bypassed", &report_aclrec_css_heading10};
struct tableHeading report_aclrec_css_heading8  = {false, 1, "clauses should not reject packets", &report_aclrec_css_heading9};
struct tableHeading report_aclrec_css_heading7  = {false, 1, "disabled clauses are removed", &report_aclrec_css_heading8};
struct tableHeading report_aclrec_css_heading6  = {false, 1, "clauses log denied access", &report_aclrec_css_heading7};
struct tableHeading report_aclrec_css_heading5  = {false, 1, "clauses do not allow access to any destination port", &report_aclrec_css_heading6};
struct tableHeading report_aclrec_css_heading4  = {false, 1, "clauses do not allow access to entire destination networks", &report_aclrec_css_heading5};
struct tableHeading report_aclrec_css_heading3  = {false, 1, "clauses do not allow access to any destination", &report_aclrec_css_heading4};
struct tableHeading report_aclrec_css_heading2  = {false, 1, "clauses do not allow access from any source port", &report_aclrec_css_heading3};
struct tableHeading report_aclrec_css_heading1  = {false, 1, "clauses do not allow access from entire source networks", &report_aclrec_css_heading2};
struct tableHeading report_aclrec_css_heading   = {false, 1, "clauses do not allow access from any source", &report_aclrec_css_heading1};
struct tableHeading report_accesslist_css_heading2 = {false, 4, "Description", 0};
struct tableHeading report_accesslist_css_heading1 = {false, 1, "Clause", &report_accesslist_css_heading2};
struct tableHeading report_accesslist_css_heading  = {false, 1, "ACL", &report_accesslist_css_heading1};
const char *report_accesslist_noacl_title = "Access Control Lists Disabled";
const char *report_accesslist_noacl_context = "ACL are disabled";
const char *report_accesslist_noacl_rectext = "Enable ACL to restrict access to hosts and services";
const char *report_accesslist_disabled_css_obs = "*ABBREV*ACLs*-ABBREV* are used to restrict access to services and network devices, preventing access to services and devices that should not be accessible. However, without enabling *ABBREV*ACL*-ABBREV* all network traffic is allowed.*NEWPARA**COMPANY* determined that*POSITIVE*, although *ABBREV*ACL*-ABBREV* have been configured,*-POSITIVE* *ABBREV*ACL*-ABBREV* are disabled on *DEVICENAME*.";
const char *report_accesslist_disabled_css_impact = "With *ABBREV*ACLs*-ABBREV* disabled, an attacker could gain access to hosts and services for which they should not be able to access.";
const char *report_accesslist_disabled_css_rec = "*COMPANY* recommends that *ABBREV*ACL*-ABBREV* be enabled. Once enabled, all traffic is denied by default, so an *ABBREV*ACL*-ABBREV* should be configured to permit traffic to the device prior to enabling *ABBREV*ACL*-ABBREV*. *ABBREV*ACL*-ABBREV* can be enabled with the following *DEVICETYPE* command:*NEWPARA**COMMAND*acl enable*-COMMAND*";

// Passport filters...
const char *report_pasfilter_title = "IP Traffic Filters";
const char *report_pasfilter_obs = "*DEVICETYPE* *ABBREV*IP*-ABBREV* filter sets are sequetial lists of filters that determine whether network traffic is permitted or denied. *ABBREV*IP*-ABBREV* Filter sets are applied to *DEVICETYPE* ports, which can also be configured with a default action to drop or forward network packets. *ABBREV*IP*-ABBREV* Filter sets are used restrict access to services and network devices, preventing access to services and devices that should not be accessible.*NEWPARA**COMPANY* *NEGATIVE*determined that no filter sets were configured on *DEVICENAME*.*-NEGATIVE**POSITIVE*identified *NUMBER* insecure filter*SINGULA*.*NONEWPARA**-SINGULA**PLAURAL*s, these are listed in Table *TABLEREF*.*-PLAURAL**-POSITIVE*";
const char *report_pasfilter_impact = "*POSITIVE*If *ABBREV*IP*-ABBREV* filter sets are not sufficiently restrictive*-POSITIVE**NEGATIVE*If filter sets are not configured*-NEGATIVE*, an attacker may be able to access services or network devices that should not be accessible. Furthermore, an attacker who had compromised a device could install some backdoor software which could listen on a network port that was not filtered.";
const char *report_pasfilter_ease = "";
const char *report_pasfilter_rec = "*COMPANY* recommends that *NEGATIVE*filter sets be configured on *DEVICENAME*. Furthermore, *COMPANY* recommends*-NEGATIVE**POSITIVE*the *ABBREV*IP*-ABBREV* filter sets be reviewed and, where possible, modified to ensure*-POSITIVE* that:*NONEWPARA*";
const char *report_pasfilter_context = "insecure filters were configured";
const char *report_pasfilter_rectext = "Configure all filters to only allow access to the hosts and services required";
const char *report_pasfilter_denylog = "IP filter set does not end with a deny all and log.";
const char *report_pasfilter_bypass = "bypasses the remaining filters.";
const char *report_pasfiltert_bypass = "Bypasses the remaining filters.";
struct tableHeading report_pasfilter_heading12 = {false, 1, "IP filter sets end with a deny all and log", 0};
struct tableHeading report_pasfilter_heading11 = {false, 1, "logging be enabled for all filters", &report_pasfilter_heading12};
struct tableHeading report_pasfilter_heading10 = {false, 1, "filters should not have a default action", &report_pasfilter_heading11};
struct tableHeading report_pasfilter_heading9  = {false, 1, "IP filter sets should not be bypassed", &report_pasfilter_heading10};
struct tableHeading report_pasfilter_heading8  = {false, 1, "filters should not reject packets", &report_pasfilter_heading9};
struct tableHeading report_pasfilter_heading7  = {false, 1, "disabled filters are removed", &report_pasfilter_heading8};
struct tableHeading report_pasfilter_heading6  = {false, 1, "filters log denied access", &report_pasfilter_heading7};
struct tableHeading report_pasfilter_heading5  = {false, 1, "filters do not allow access to any destination port", &report_pasfilter_heading6};
struct tableHeading report_pasfilter_heading4  = {false, 1, "filters do not allow access to entire destination networks", &report_pasfilter_heading5};
struct tableHeading report_pasfilter_heading3  = {false, 1, "filters do not allow access to any destination", &report_pasfilter_heading4};
struct tableHeading report_pasfilter_heading2  = {false, 1, "filters do not allow access from any source port", &report_pasfilter_heading3};
struct tableHeading report_pasfilter_heading1  = {false, 1, "filters do not allow access from entire source networks", &report_pasfilter_heading2};
struct tableHeading report_pasfilter_heading   = {false, 1, "filters do not allow access from any source", &report_pasfilter_heading1};
struct tableHeading report_pasfilter_table_heading2 = {false, 4, "Description", 0};
struct tableHeading report_pasfilter_table_heading1 = {false, 1, "Filter ID", &report_pasfilter_table_heading2};
struct tableHeading report_pasfilter_table_heading  = {false, 1, "Filter Set", &report_pasfilter_table_heading1};
const char *report_pasfilter_table = "Insecure filters";

// Remote SSH Management Hosts
const char *report_sshman_title = "Remote SSH Management Hosts";
const char *report_sshman_obs = "It is possible to configure *ABBREV*SSH*-ABBREV* on *DEVICETYPE* to restrict remote administrative access to specific management addresses. However, *COMPANY* determined that the remote management of *DEVICENAME* using *ABBREV*SSH*-ABBREV* was not restricted to individual remote management *ABBREV*IP*-ABBREV* addresses.";
const char *report_sshman_impact = "If an attacker were able to determine the authentication credentials for *DEVICENAME*, due to relaxed remote management configuration they may be able to gain access using *ABBREV*SSH*-ABBREV*. Additionally, if a vulnerability were to exist in the *ABBREV*SSH*-ABBREV* service, an attacker may be able to gain access to the device due to the weak remote access restrictions.";
const char *report_sshman_ease = "";
const char *report_sshman_rec = "*COMPANY* recommends that remote management access using *ABBREV*SSH*-ABBREV* be restricted to the individual *ABBREV*IP*-ABBREV* addresses required. Access can be restricted using the following command:*NEWPARA**COMMAND*ssh *CMDREQUIRE**CMDUSER*ip address*-CMDUSER**-CMDREQUIRE* *CMDREQUIRE**CMDUSER*net mask*-CMDUSER**-CMDREQUIRE* *CMDREQUIRE**CMDUSER*interface*-CMDUSER**-CMDREQUIRE**-COMMAND*";
const char *report_sshman_context = "entire networks are allowed remote management access using SSH";
const char *report_sshman_rectext = "Restrict remote SSH management to specific hosts";

// Flood Guard
const char *report_floodguard_title = "Flood Guard";
const char *report_floodguard_obs = "The Flood Guard feature enables a *DEVICETYPE* to reclaim system resources if the circumstances occur whereby resources have been exhausted. *COMPANY* determined that the Flood Guard feature was not enabled on *DEVICENAME*.";
const char *report_floodguard_impact = "An attacker could perform a *ABBREV*DoS*-ABBREV* attack against *DEVICENAME* by consuming the *DEVICETYPE* resources with a flood of connection attempts.";
const char *report_floodguard_ease = "Tools are available on the Internet that can perform a *ABBREV*DoS*-ABBREV* attack.";
const char *report_floodguard_rec = "*COMPANY* recommends that the Flood Guard feature be enabled. Flood Guard can be enabled with the following command:*NEWPARA**COMMAND*floodguard enable*-COMMAND*";
const char *report_floodguard_context = "the flood guard feature was not enabled";
const char *report_floodguard_rectext = "Enable Flood Guard";

// Cisco Express Forwarding / Unicast Reverse Packet Forwarding
const char *report_urpf_title = "Unicast Reverse Packet Forwarding Verification";
const char *report_urpf_obs = "Any configured network packet filtering will have an impact on a device's performance and the more filtering configured, the greater the impact. Typically, additional filtering is configured to perform sanity checks on network traffic to ensure that traffic being routed through the network originates from a valid *ABBREV*IP*-ABBREV* address, this ensures that traffic entering a network does not originate from an internal *ABBREV*IP*-ABBREV* address range. Cisco provides *ABBREV*uRPF*-ABBREV* verification to perform network traffic sanity checks without the performance impact of *ABBREV*ACL*-ABBREV* network filtering. *ABBREV*uRPF*-ABBREV* verification must be enabled on each interface on which sanity checks should be performed and will automatically adjust to topology changes. *ABBREV*uRPF*-ABBREV* verification makes use of *ABBREV*CEF*-ABBREV*, which must be enabled.*NEWPARA**COMPANY* determined that *NEGATIVE**ABBREV*CEF*-ABBREV* was not enabled*-NEGATIVE**SINGULA**ABBREV*uRPF*-ABBREV* verification was not enabled on interface *NONEWPARA**-SINGULA**PLAURAL**ABBREV*uRPF*-ABBREV* verification was not enabled on the interfaces listed in Table *TABLEREF**-PLAURAL*.";
const char *report_urpf_pix_obs = "Any configured network packet filtering will have an impact on a device's performance and the more filtering configured, the greater the impact. Typically, additional filtering is configured to perform sanity checks on network traffic to ensure that traffic being passed through the *DEVICETYPE* originates from a valid *ABBREV*IP*-ABBREV* address, this ensures that traffic entering a network does not originate from an internal *ABBREV*IP*-ABBREV* address range. Cisco provides *ABBREV*uRPF*-ABBREV* verification to perform network traffic sanity checks without the performance impact of *ABBREV*ACL*-ABBREV* network filtering. *ABBREV*uRPF*-ABBREV* verification must be enabled for each interface on which sanity checks should be performed and will automatically adjust to topology changes.*NEWPARA**COMPANY* determined that *ABBREV*uRPF*-ABBREV* verification was not enabled on the interface*SINGULA**NONEWPARA**-SINGULA**PLAURAL*s listed in Table *TABLEREF**-PLAURAL*.";
const char *report_urpf_impact = "A network packet with a spoofed source address could be routed by the device, bypassing any configured *ABBREV*ACLs*-ABBREV*.";
const char *report_urpf_ease = "";
const char *report_urpf_rec = "*COMPANY* recommends that, where possible, *ABBREV*uRPF*-ABBREV* verification be enabled on all network interfaces. *ABBREV*uRPF*-ABBREV* verification can be enabled on each network interface with the following command:*NEWPARA**COMMAND*ip verify unicast reverse-path*-COMMAND**NEWPARA**NEGATIVE**ABBREV*CEF*-ABBREV* can be enabled with the following command on routers without *ABBREV*VIPs*-ABBREV*:*NEWPARA**COMMAND*ip cef*-COMMAND**NEWLINE*On routers with *ABBREV*VIPs*-ABBREV* the following command will enable *ABBREV*CEF*-ABBREV*:*NEWPARA**COMMAND*ip cef distributed*-COMMAND**NEWLINE**-NEGATIVE*It is worth noting that not all devices support *ABBREV*uRPF*-ABBREV* verification and it is best implemented only on edge routers. Furthermore, *ABBREV*uRPF*-ABBREV* verification should not be used if any of the router's interfaces participate in asymmetric routes. If it is not possible to implement *ABBREV*uRPF*-ABBREV* verification, then *COMPANY* recommends that *ABBREV*ACL*-ABBREV* be configured on edge routers to perform sanity checks on network traffic.";
const char *report_urpf_pix_rec = "*COMPANY* recommends that, where possible, *ABBREV*uRPF*-ABBREV* verification be enabled for all outside network interfaces. *ABBREV*uRPF*-ABBREV* verification can be enabled for each network interface with the following command:*NEWPARA**COMMAND*ip verify reverse-path interface *CMDREQUIRE**CMDUSER*interface*-CMDUSER**-CMDREQUIRE**-COMMAND**NEWLINE*If it is not possible to implement *ABBREV*uRPF*-ABBREV* verification, then *COMPANY* recommends that *ABBREV*ACL*-ABBREV* be configured on edge devices to perform sanity checks on network traffic.";
const char *report_urpf_context = "uRPF verification was not enabled on all interfaces";
const char *report_urpf_rectext = "Enable uRPF verification on all outside interfaces";
const char *report_urpf_table = "Interfaces without Unicast Reverse Packet Forwarding verification";

// Management IP
const char *report_mngrip_title = "Remote Management IP Address";
const char *report_mngrip_obs = "Network devices will commonly provide management services to enable remote management by network administrators. It is quite common for a modern network device to provide several different methods of securing administrative services, ranging from service configuration options to firewall rules. ScreenOS devices provide a manager-ip configuration setting that defines which hosts or networks are allowed to manage the device.*NEWPARA**COMPANY* determined that the manager-ip setting on *DEVICENAME* was configured to allow any network address to manage the device. However, it should be noted that although the manager-ip setting was not restricting access to the *DEVICENAME* administrative services, other network restrictions could still limit access to those services.";
const char *report_mngrip_impact = "An attacker who was able to connect to the management services provided by *DEVICENAME* are offered a wide variety of options that should be closed to them. The attacker could use the service to help identify the device type and version in order to identify a vulnerability or the attacker could attempt to brute-force the authentication credentials in an attempt to gain access to the device.";
const char *report_mngrip_ease = "";
const char *report_mngrip_rec = "*COMPANY* recommends that the manager-ip setting be configured to restrict remote administrative access to device services. The manager-ip setting can be configured using the following command:*NEWPARA**COMMAND*set admin manager-ip *CMDREQUIRE**CMDUSER*ip address*-CMDUSER**-CMDREQUIRE* *CMDREQUIRE**CMDUSER*net mask*-CMDUSER**-CMDREQUIRE**-COMMAND*";
const char *report_mngrip_context = "the remote administration IP addresses were not defined";
const char *report_mngrip_rectext = "Configure the remote administration IP addresses";

// Trunking
const char *report_trunking_title = "Switch Port Trunking";
const char *report_trunking_obs1 = "*DEVICETYPE* devices are able to transfer *ABBREV*VLAN*-ABBREV* packets to different network devices, extending a *ABBREV*VLAN*-ABBREV* across different physical devices. In order to extend a *ABBREV*VLAN*-ABBREV* to a different physical device, a trunk has to be created between the devices. *DEVICETYPE* devices default to allowing a trunk to be negotiated on a particular switch port if the connected device will also allow the trunk and supports a common trunking protocol.*NEWPARA**COMPANY* determined that *NUMBER* switch port*PLAURAL*s*-PLAURAL* allowed a trunk to be negotiated*PLAURAL*, these are listed in Table *TABLEREF**-PLAURAL*.*SINGULA* The switch port *NONEWPARA**-SINGULA*";
const char *report_trunking_obs2 = " allowed trunking.";
const char *report_trunking_impact = "An attacker who was able to create a trunk would gain direct access to all the *ABBREV*VLANs*-ABBREV* extended over the trunk. This would allow an attacker to bypass any network filtering between the *ABBREV*VLANs*-ABBREV*.";
const char *report_trunking_ease = "The attacker would require knowledge of network trunking. However, tools are available on the Internet that can exploit trunking vulnerabilities.";
const char *report_trunking_rec = "*COMPANY* recommends that, where possible, all switch ports be configured to provide no trunking. If trunking is required on a specific switch port, *COMPANY* recommends that the switch port be configured to trunk only the required *ABBREV*VLANs*-ABBREV*. Switch ports can be configured to provide no trunking on each interface with the following commands:*NEWPARA**COMMAND*switchport mode access*-COMMAND**NEWLINE**COMMAND*switchport nonegotiate*-COMMAND*";
const char *report_trunking_context = "trunk negotiation was not disabled on all switch ports";
const char *report_trunking_rectext = "Disable trunk negotiation on all switch ports";
const char *report_trunking_table = "Switch ports that allow trunking";

// Switch Port Security
const char *report_portsecurity_title = "Switch Port Security";
const char *report_portsecurity_obs1 = "Switch port security enables a *DEVICETYPE* to help prevent unauthorised access to the network by limiting the *ABBREV*MAC*-ABBREV* addresses allowed on specific ports. *ABBREV*MAC*-ABBREV* addresses can either be specified for a particular switch port or can be learned by the *DEVICETYPE*. When port security is configured a variety of actions can be taken when a violation occurs, such as automatically disabling the port.*NEWPARA**COMPANY* identified *NUMBER* switch port*PLAURAL*s*-PLAURAL* that had no port security configured*PLAURAL*, these are listed in Table *TABLEREF*.*-PLAURAL**SINGULA*. Switch port *NONEWPARA**-SINGULA*";
const char *report_portsecurity_obs2 = "*NOTEXTSTART* was configured with no port security.";
const char *report_portsecurity_impact = "A switch port with no configured port security could allow an attacker to attach an unauthorised device and scan other network attached devices. Depending on the security of the network attached devices, this issue could allow an attacker to perform information gathering, or potentially, gain access to vulnerable devices.";
const char *report_portsecurity_ease = "An attacker would have to gain access to a switch port with no security configured. If the switch port is not directly patched to a wall socket, the attacker would have to gain physical access to the *DEVICETYPE*.";
const char *report_portsecurity_rec = "*COMPANY* recommends that, where possible, port security be enabled on all switch ports. Furthermore, *COMPANY* recommends that all switch ports that are not used be shutdown. Switch port security with *ABBREV*MAC*-ABBREV* address learning and port shutdown on a violation can be configured on each interface with the following commands:*NEWPARA**COMMAND*switchport port-security*-COMMAND**NEWLINE**COMMAND*switchport port-security violation shutdown*-COMMAND**NEWLINE**COMMAND*switchport port-security mac-address sticky*-COMMAND**NEWLINE*Unused interfaces can be disabled with the following interface command:*NEWPARA**COMMAND*shutdown*-COMMAND*";
const char *report_portsecurity_context = "port security was not enabled on all switch ports";
const char *report_portsecurity_rectext = "Enable switch port security on all switch ports";
const char *report_portsecurity_table = "Switch ports with no port security";

// Logging
const char *report_logging_title = "Logging";
const char *report_logging_obs1 = "Logging is an essential component of a secure network configuration. Logging not only assists network administrators to identify issues when troubleshooting, but enables network administrators to react to intrusion attempts or Denial-of-Service attacks. It is therefore critical that logs be monitored, allowing administrators to take immediate action when an attack has been identified. Furthermore, system logs are a key component of a forensic investigation into past intrusions or service disruptions.";
const char *report_logging_obs2 = "*COMPANY* determined that logging had not been configured on *DEVICENAME*.";
const char *report_logging_obs3 = "*COMPANY* determined that logging had been disabled on *DEVICENAME*.";
const char *report_logging_obs4 = "*COMPANY* determined that, although logging was enabled on *DEVICENAME*, both Syslog and Buffered logging were not configured.";
const char *report_logging_obs5 = "*COMPANY* determined that, although logging was enabled on *DEVICENAME*, Syslog logging was not configured.";
const char *report_logging_obs6 = "*COMPANY* determined that, although logging was enabled on *DEVICENAME*, Buffered logging was not configured.";
const char *report_logging_impact = "An attacker could attempt to map and bypass any configured *ABBREV*ACL*-ABBREV* or to gain access to the *DEVICETYPE* without network administrators being alerted to the attempts. Furthermore, after an unauthorised intrusion into the network had been detected, it would be more difficult for an investigation to identify the source of the attack or the entry point without access to logs.";
const char *report_logging_ease = "";
const char *report_logging_rec1 = "*COMPANY* recommends that Syslog and Buffered logging be configured on *DEVICENAME*. Logging can be enabled with the following command:*NEWPARA**COMMAND*logging on*-COMMAND*";
const char *report_logging_rec2 = "To configure Syslog logging, four things need to be set; a source interface for the Syslog messages to be sent from, one or more Syslog hosts to send messages to, the Syslog logging message severity level and the Syslog facility. The following commands can be used to configure Syslog logging:*NEWPARA**COMMAND*logging source-interface *CMDREQUIRE**CMDUSER*Interface*-CMDUSER**-CMDREQUIRE**-COMMAND**NEWLINE**COMMAND*logging host *CMDREQUIRE**CMDUSER*Syslog IP address or hostname*-CMDUSER**-CMDREQUIRE**-COMMAND**NEWLINE**COMMAND*logging trap *CMDREQUIRE**CMDUSER*Logging message severity level*-CMDUSER**-CMDREQUIRE**-COMMAND**NEWLINE**COMMAND*logging facility *CMDREQUIRE**CMDUSER*Syslog facility*-CMDUSER**-CMDREQUIRE**-COMMAND*";
const char *report_logging_rec3 = "It is worth noting that older *ABBREV*IOS*-ABBREV* versions do not exclude the host parameter when specifying a host to send Syslog messages to. For older *ABBREV*IOS*-ABBREV* versions you would use the following command:*NEWPARA**COMMAND*logging *CMDREQUIRE**CMDUSER*Syslog IP address or hostname*-CMDUSER**-CMDREQUIRE**-COMMAND*";
const char *report_logging_rec4 = "Buffered logging can be configured with the following command:*NEWPARA**COMMAND*logging buffered *CMDREQUIRE**CMDUSER*Buffer Size*-CMDUSER**-CMDREQUIRE* *CMDREQUIRE**CMDUSER*Logging message severity level*-CMDUSER**-CMDREQUIRE**-COMMAND*";
const char *report_logging_context = "insufficient logging was configured";
const char *report_logging_rectext = "Configure Syslog and Buffered logging";

// Proxy ARP
const char *report_proxyarp_title = "Proxy ARP";
const char *report_proxyarp_obs = "*ABBREV*ARP*-ABBREV* is a protocol that network hosts use to translate network addresses into media addresses. Under normal circumstances, *ABBREV*ARP*-ABBREV* packets are confined to the sender's network segment. However, a Cisco router with Proxy *ABBREV*ARP*-ABBREV* enabled on network interfaces can act as a proxy for *ABBREV*ARP*-ABBREV*, responding to queries and acting as an intermediary.*NEWPARA**COMPANY* identified *NUMBER* interface*PLAURAL*s*-PLAURAL* that had Proxy *ABBREV*ARP*-ABBREV* enabled*SINGULA*, *NONEWPARA**-SINGULA**PLAURAL*. These are listed in Table *TABLEREF*.*-PLAURAL*";
const char *report_proxyarp_impact = "A router that acts as a proxy for *ABBREV*ARP*-ABBREV* requests will extend layer two access across multiple network segments, breaking perimeter security.";
const char *report_proxyarp_ease = "A Cisco device with Proxy *ABBREV*ARP*-ABBREV* enabled will proxy *ABBREV*ARP*-ABBREV* requests for all hosts on those interfaces.";
const char *report_proxyarp_rec = "*COMPANY* recommends that, if not required, Proxy *ABBREV*ARP*-ABBREV* be disabled on all interfaces. Proxy *ABBREV*ARP*-ABBREV* can be disabled on each interface with the following Cisco *ABBREV*IOS*-ABBREV* command:*NEWPARA**COMMAND*no ip proxy-arp*-COMMAND*";
const char *report_proxyarp_context = "ARP request proxying was not disabled on all network interfaces";
const char *report_proxyarp_rectext = "Disable Proxy ARP on all network interfaces";
const char *report_proxyarp_table = "Interfaces with Proxy ARP enabled";

// SSH Protocol Version
const char *report_sshproto_title = "SSH Protocol Version";
const char *report_sshproto_obs = "The *ABBREV*SSH*-ABBREV* service is commonly used for encrypted command-based remote device management. There are multiple *ABBREV*SSH*-ABBREV* protocol versions and *ABBREV*SSH*-ABBREV* servers will often support multiple versions to maintain backwards compatibility. Although flaws have been identified in implementations of version 2 of the *ABBREV*SSH*-ABBREV* protocol, fundamental flaws exist in *ABBREV*SSH*-ABBREV* protocol version 1.*NEWPARA**COMPANY* determined that support for version 1 of the *ABBREV*SSH*-ABBREV* protocol was supported on *DEVICENAME*.";
const char *report_sshproto_impact = "An attacker who was able to intercept *ABBREV*SSH*-ABBREV* protocol version 1 traffic would be able to perform a man-in-the-middle style attack. The attacker could then capture network traffic and possibly authentication credentials.";
const char *report_sshproto_ease = "Although vulnerabilities are widely known, exploiting the vulnerabilities in the *ABBREV*SSH*-ABBREV* protocol can be difficult.";
const char *report_sshproto_rec1 = "*COMPANY* recommends that the *ABBREV*SSH*-ABBREV* service be configured to support only version 2 of the *ABBREV*SSH*-ABBREV* protocol. Version 2 of the *ABBREV*SSH*-ABBREV* protocol can be configured with the following command:*NEWPARA**COMMAND*ssh version 2*-COMMAND**NEGATIVE**NEWLINE*However, it is worth noting that this command was introduced with *DEVICETYPE* software version 7.0(1) and therefore a software upgrade may be required.*-NEGATIVE*";		// PIX
const char *report_sshproto_rec2 = "*COMPANY* recommends that the *ABBREV*SSH*-ABBREV* service be configured to support only version 2 of the *ABBREV*SSH*-ABBREV* protocol. Version 2 of the *ABBREV*SSH*-ABBREV* protocol can be configured with the following command:*NEWPARA**COMMAND*ip ssh version 2*-COMMAND**SINGULA**NEWLINE*It is worth noting that *ABBREV*SSH*-ABBREV* protocol version 2 support was introduced by Cisco into *ABBREV*IOS*-ABBREV* starting with *ABBREV*IOS*-ABBREV* version 12.1(19)E. Therefore a software upgrade may be required to implement *ABBREV*SSH*-ABBREV* protocol version 2 support.*-SINGULA*";	// IOS
const char *report_sshproto_sos_rec = "*COMPANY* recommends that the *ABBREV*SSH*-ABBREV* service be configured to support only version 2 of the *ABBREV*SSH*-ABBREV* protocol. Version 2 of the *ABBREV*SSH*-ABBREV* protocol can be configured with the following command:*NEWPARA**COMMAND*set ssh version v2*-COMMAND*";
const char *report_sshproto_context = "SSH protocol version 1 was configured";
const char *report_sshproto_rectext = "Configure SSH to support only protocol version 2";

// CDP
const char *report_cdp_title = "Cisco Discovery Protocol";
const char *report_cdp_obs = "*ABBREV*CDP*-ABBREV* is a proprietary protocol that is primarily used by Cisco, but has been used by others. *ABBREV*CDP*-ABBREV* allows some network management applications and *ABBREV*CDP*-ABBREV* aware devices to identify each other on a *ABBREV*LAN*-ABBREV* segment. Cisco devices, including switches, bridges and routers are configured to broadcast *ABBREV*CDP*-ABBREV* packets by default.*SINGULA* The devices can be configured to disable the *ABBREV*CDP*-ABBREV* service or disable *ABBREV*CDP*-ABBREV* on individual network interfaces.*-SINGULA**PLAURAL* The devices can be configured to disable the *ABBREV*CDP*-ABBREV* service or disable *ABBREV*CDP*-ABBREV* on individual network interfaces.*-PLAURAL**NEWPARA**COMPANY* determined that *NEGATIVE**ABBREV*CDP*-ABBREV* was enabled.*-NEGATIVE**SINGULA*even though *ABBREV*CDP*-ABBREV* had been disabled on all active interfaces, the *ABBREV*CDP*-ABBREV* service had not been disabled.*-SINGULA**PLAURAL*the *ABBREV*CDP*-ABBREV* service had not been disabled, and additionally, had not been disabled on all the active network interfaces.*-PLAURAL*";
const char *report_cdp_impact = "*ABBREV*CDP*-ABBREV* packets contain information about the sender, such as hardware model information, operating system version and *ABBREV*IP*-ABBREV* address details. This information would allow an attacker to gain information about the configuration of the network infrastructure.";
const char *report_cdp_ease = "*ABBREV*CDP*-ABBREV* packets are broadcast to an entire network segment. An attacker could use one of the many publicly available tools to capture network traffic and view the leaked information.";
const char *report_cdp_rec1 = "*COMPANY* recommends that, if not required, the *ABBREV*CDP*-ABBREV* service be disabled on the Cisco device *DEVICENAME*. If *ABBREV*CDP*-ABBREV* is required, *COMPANY* recommends that *ABBREV*CDP*-ABBREV* be disabled on all interfaces except those that are explicitly required.*NEWPARA*The *ABBREV*CDP*-ABBREV* service can be disabled by issuing the following Cisco *ABBREV*IOS*-ABBREV* command:*NEWPARA**COMMAND*no cdp run*-COMMAND**NEWLINE**ABBREV*CDP*-ABBREV* can be disabled on individual interfaces using the following command:*NEWPARA**COMMAND*no cdp enable*-COMMAND**NEWLINE*In some configurations with *ABBREV*IP*-ABBREV* phones, deployed using either Auto Discovery or *ABBREV*DHCP*-ABBREV*, the *ABBREV*CDP*-ABBREV* service may need to be enabled. In this situation *ABBREV*CDP*-ABBREV* should be disabled on all network interfaces for which it is not required.";
const char *report_cdp_rec2 = "*COMPANY* recommends that, if not required, *ABBREV*CDP*-ABBREV* be disabled. *ABBREV*CDP*-ABBREV* can be disabled with the following command:*NEWPARA**COMMAND*set cdp disable*-COMMAND**NEWLINE**ABBREV*CDP*-ABBREV* can be disabled on individual module ports using the following command:*NEWPARA**COMMAND*set cdp disable*-COMMAND**NEWLINE*In some configurations with *ABBREV*IP*-ABBREV* phones, deployed using either Auto Discovery or *ABBREV*DHCP*-ABBREV*, the *ABBREV*CDP*-ABBREV* service may need to be enabled. In this situation *ABBREV*CDP*-ABBREV* should be disabled on all module ports for which it is not required.";
const char *report_cdp_context = "CDP was not disabled";
const char *report_cdp_rectext = "Disable CDP";

// IP Classless Routing
const char *report_classless_title = "Classless Routing";
const char *report_classless_obs = "Classless routing is enabled by default on Cisco routers. If a router has classless routing enabled and it receives a network packet for which there is no configured route, the router will forward the packet to the best destination. With classless routing disabled, the router would discard any network traffic for which no route is defined.*NEWPARA**COMPANY* determined that classless routing was enabled on *DEVICENAME*.";
const char *report_classless_impact = "Network traffic that should not be routed by the router may be routed when classless routing is enabled.";
const char *report_classless_ease = "";
const char *report_classless_rec = "*COMPANY* recommends that, if possible, classless routing be disabled. Classless routing can be disabled with the following command:*NEWPARA**COMMAND*no ip classless*-COMMAND*";
const char *report_classless_context = "classless routing was enabled";
const char *report_classless_rectext = "Disable classless routing";

// Minimum Password Length
const char *report_passlength_title = "Minimum Password Length";
const char *report_passlength_obs = "Cisco introduced an option from *ABBREV*IOS*-ABBREV* version 12.3(1) which forces user, enable, secret and line passwords to meet a minimum length. This setting was introduced to help prevent the use of short passwords such as \"cisco\".*NEWPARA**NEGATIVE**COMPANY* determined that the minimum password length functionality was disabled*-NEGATIVE**POSITIVE**COMPANY* determined that a minimum password length of *NUMBER* character*PLAURAL*s*-PLAURAL* was configured*-POSITIVE*.";
const char *report_passlength_impact = "*NEGATIVE*With no password length checking*-NEGATIVE**POSITIVE*With a small minimum password length configured*-POSITIVE*, it would be possible for a short password to be used. If an attacker were able to gain a password through dictionary-based guessing techniques or by a brute-force method, the attacker could gain a level of access to *DEVICENAME*.";
const char *report_passlength_ease = "A number of dictionary-based password guessing and password brute-force tools are available on the Internet.";
const char *report_passlength_rec = "*COMPANY* recommends that a minimum password length of at least *NUMBER* character*PLAURAL*s*-PLAURAL* be configured. The minimum password length can be configured with the following command:*NEWPARA**COMMAND*security passwords min-length *CMDREQUIRE**CMDUSER*length*-CMDUSER**-CMDREQUIRE**-COMMAND*";
const char *report_passlength_context = "an inadequate minimum password length was configured";
const char *report_passlength2_context = "no minimum password length was configured";
const char *report_passlength_rectext = "Configure a secure minimum password length";

// Bootp
const char *report_bootp_title = "BOOTP";
const char *report_bootp_obs = "*ABBREV*BOOTP*-ABBREV* is a datagram protocol that allows compatible hosts to load their operating system over the network from a *ABBREV*BOOTP*-ABBREV* server. Cisco routers are capable of acting as *ABBREV*BOOTP*-ABBREV* servers for other Cisco devices and the service is enabled by default. However, *ABBREV*BOOTP*-ABBREV* is rarely used and may represent a security risk.*NEWPARA**COMPANY* determined that *ABBREV*BOOTP*-ABBREV* was not disabled. However, it is worth noting that not all Cisco devices support *ABBREV*BOOTP*-ABBREV*.";
const char *report_bootp_impact = "An attacker could use the *ABBREV*BOOTP*-ABBREV* service to download a copy of the router's *ABBREV*IOS*-ABBREV* software.";
const char *report_bootp_ease = "Tools are available on the Internet to access *ABBREV*BOOTP*-ABBREV* servers.";
const char *report_bootp_rec = "*COMPANY* recommends that, if not required, the *ABBREV*BOOTP*-ABBREV* service be disabled. The following command can be used to disable *ABBREV*BOOTP*-ABBREV*:*NEWPARA**COMMAND*no ip bootp server*-COMMAND*";
const char *report_bootp_context = "BootP was enabled";
const char *report_bootp_rectext = "Disable BootP";

// TCP & UDP Small Servers
const char *report_small_title = "TCP and UDP Small Servers";
const char *report_small_obs1 = "Cisco devices provide a set of simple servers which are collectively known as *ABBREV*TCP*-ABBREV* small servers and *ABBREV*UDP*-ABBREV* small servers. The services provide little functionality and include chargen, echo and daytime. Cisco *ABBREV*IOS*-ABBREV* version 11.2 and older enable these services by default; newer *ABBREV*IOS*-ABBREV* versions explicitly require them to be started.";
const char *report_small_obs2 = "*COMPANY* determined that the version of *ABBREV*IOS*-ABBREV*, on the Cisco device *DEVICENAME*, enables these servers by default and they have not been explicitly disabled.";
const char *report_small_obs3 = "*COMPANY* determined that both the *ABBREV*TCP*-ABBREV* and *ABBREV*UDP*-ABBREV* small servers were not disabled.";
const char *report_small_obs4 = "*COMPANY* determined that the *ABBREV*TCP*-ABBREV* small servers were not disabled.";
const char *report_small_obs5 = "*COMPANY* determined that the *ABBREV*UDP*-ABBREV* small servers were not disabled.";
const char *report_small_impact = "Each running service increases the chances of an attacker being able to identify the device and successfully compromise it. It is good security practice to disable all unused services.";
const char *report_small_ease = "Tools are widely available to query these services and some operating systems install these tools by default.";
const char *report_small_rec = "*COMPANY* recommends that, if not required, *ABBREV*TCP*-ABBREV* and *ABBREV*UDP*-ABBREV* small servers be explicitly disabled. *ABBREV*TCP*-ABBREV* and *ABBREV*UDP*-ABBREV* small services are rarely used and are disabled by default in newer versions of Cisco *ABBREV*IOS*-ABBREV*.";
const char *report_small_rec_tcp = "*ABBREV*TCP*-ABBREV* small servers can be disabled with the following *ABBREV*IOS*-ABBREV* command:*NEWPARA**COMMAND*no service tcp-small-servers*-COMMAND*";
const char *report_small_rec_udp = "*ABBREV*UDP*-ABBREV* small servers can be disabled with the following *ABBREV*IOS*-ABBREV* command:*NEWPARA**COMMAND*no service udp-small-servers*-COMMAND*";
const char *report_small_context = "all small servers have not been disabled";
const char *report_small_rectext = "Disable all small servers";

// ICMP IP Unreachables
const char *report_icmpunreach_title = "IP Unreachables";
const char *report_icmpunreach_table = "Interfaces with IP unreachables enabled";
const char *report_icmpunreach_obs = "*ABBREV*ICMP*-ABBREV* *ABBREV*IP*-ABBREV* unreachable messages can be generated by a Cisco device when a host attempts to connect to a non-existent host, network, or use an unsupported protocol. *ABBREV*ICMP*-ABBREV* *ABBREV*IP*-ABBREV* unreachable messages will let the connecting host know that the host, network or protocol is not supported or cannot be contacted. Therefore, the host does not have to wait for a connection time-out. *ABBREV*ICMP*-ABBREV* *ABBREV*IP*-ABBREV* unreachable messages are normally enabled by default on Cisco devices and must be explicitly disabled.*NEWPARA**COMPANY* determined that the Cisco device *DEVICENAME* had *ABBREV*ICMP*-ABBREV* *ABBREV*IP*-ABBREV* unreachable messages enabled*SINGULA* on the interface *NONEWPARA**-SINGULA**PLAURAL* on the interfaces listed in Table *TABLEREF**-PLAURAL*.";
const char *report_icmpunreach_impact = "An attacker who was performing network scans to determine what services were available would be able to scan a device more quickly.";
const char *report_icmpunreach_ease = "Tools are available on the Internet that can perform a wide variety of scan types.";
const char *report_icmpunreach_rec1 = "*COMPANY* recommends that, if not required, *ABBREV*IP*-ABBREV* unreachables be disabled on all network interfaces. However, whilst disabling *ABBREV*IP*-ABBREV* unreachables will not stop scans, it does make it more difficult for an attacker. The *ABBREV*IP*-ABBREV* unreachables option is disabled or enabled individually for each network interface. It can be disabled with the following command:*NEWPARA**COMMAND*no ip unreachables*-COMMAND*";
const char *report_icmpunreach_rec2 = "*COMPANY* recommends that, if not required, *ABBREV*IP*-ABBREV* unreachables be disabled. However, whilst disabling *ABBREV*IP*-ABBREV* unreachables will not stop scans, it does make it more difficult for an attacker. The *ABBREV*IP*-ABBREV* unreachables option can be disabled with the following command:*NEWPARA**COMMAND*set ip unreachable disable*-COMMAND*";
const char *report_icmpunreach_context = "IP unreachables have not been disabled on all interfaces";
const char *report_icmpunreach_rectext = "Disable IP unreachables on all interfaces";

// ICMP Mask Reply
const char *report_maskreply_title = "ICMP Mask Reply";
const char *report_maskreply_table = "Interfaces with ICMP mask reply enabled";
const char *report_maskreply_obs = "*ABBREV*ICMP*-ABBREV* mask reply messages inform network hosts of the *ABBREV*TCP*-ABBREV*/*ABBREV*IP*-ABBREV* network mask for a network segment. This protocol can now be regarded as legacy as it has been superseded by protocols such as *ABBREV*DHCP*-ABBREV*, or hosts will already be configured with this information.*NEWPARA**COMPANY* determined that the Cisco device *DEVICENAME* had the *ABBREV*ICMP*-ABBREV* mask reply option enabled on the interface*SINGULA* *NONEWPARA**-SINGULA**PLAURAL*s listed in Table *TABLEREF*.*-PLAURAL*";
const char *report_maskreply_impact = "An attacker could use the *ABBREV*ICMP*-ABBREV* mask reply feature to gain additional information about the network configuration.";
const char *report_maskreply_ease = "Tools are available on the Internet that can perform *ABBREV*ICMP*-ABBREV* mask requests.";
const char *report_maskreply_rec = "*COMPANY* recommends that, if not required, *ABBREV*ICMP*-ABBREV* mask reply be disabled on all network interfaces. *ABBREV*ICMP*-ABBREV* mask reply can be disabled on each individual network interface using the following command:*NEWPARA**COMMAND*no ip mask-reply*-COMMAND*";
const char *report_maskreply_context = "ICMP Mask Reply is not disabled on all interfaces";
const char *report_maskreply_rectext = "Disable ICMP Mask Reply on all interfaces";

// Enable Secret Password
const char *report_enablesec_title = "Enable Secret";
const char *report_enablesec_obs = "Cisco IOS-based device enable passwords can be stored using an iterated *ABBREV*MD5*-ABBREV* hash, which is far stronger than the easily reversible Cisco type-7 encryption.*NEWPARA**COMPANY* identified *NUMBER* enable password*SINGULA* that was*-SINGULA**PLAURAL*s that were*-PLAURAL* not stored using the *ABBREV*MD5*-ABBREV* hash.";
const char *report_enablesec_impact = "An attacker could use an enable password from a Cisco device to access the device and possibly modify its configuration.";
const char *report_enablesec_ease = "An attacker who had access to the Cisco configuration file would easily be able to retrieve passwords that are stored in clear-text or using the Cisco type-7 encryption. However, an attacker who had access to a Cisco configuration file could brute-force any stronger *ABBREV*MD5*-ABBREV* passwords.";
const char *report_enablesec_rec = "*COMPANY* recommends that all enable passwords be stored using the *ABBREV*MD5*-ABBREV* hash. Enable passwords can be stored using the *ABBREV*MD5*-ABBREV* hash with the following Cisco *ABBREV*IOS*-ABBREV* command:*NEWPARA**COMMAND*enable secret*-COMMAND*";
const char *report_enablesec_context = "the enable password is not stored using the MD5 hash";
const char *report_enablesec_rectext = "Store the enable password using the MD5 hash";

// Password Encryption
const char *report_passenc_title = "Service Password Encryption";
const char *report_passenc_obs = "Cisco service passwords are stored by default in their clear-text form rather than being encrypted. However, it is possible to have these passwords stored using the reversible Cisco type-7 encryption.*NEWPARA**COMPANY* determined that the Cisco device *DEVICENAME* was not running the password encryption service that helps provide a basic level of encryption to passwords that otherwise would be stored in clear-text.";
const char *report_passenc_impact = "If a malicious user were to see a Cisco configuration that contained clear-text passwords, they could use the passwords to access the device. However, an attacker who had access to a Cisco configuration file would easily be able to reverse the passwords.";
const char *report_passenc_ease = "Even though it is trivial to reverse Cisco type-7 passwords, they do provide a greater level of security than clear-text passwords. Tools are widely available on the Internet that reverse Cisco type-7 passwords.";
const char *report_passenc_rec = "*COMPANY* recommends that the Cisco password encryption service be enabled. The Cisco password encryption service can be started with the following Cisco *ABBREV*IOS*-ABBREV* command:*NEWPARA**COMMAND*service password-encryption*-COMMAND*";
const char *report_passenc_context = "the service passwords are stored in clear-text";
const char *report_passenc_rectext = "Configure the passwords to be stored using the Cisco type-7 algorithm";

// Banner
const char *report_banner_title = "Login Banner";
const char *report_banner_obs = "A banner message can be shown to users who connect to one of the remote management services, such as Telnet. Typically banner messages will include information on the law with regard to unauthorised access to the device, warning users who do not have the authority to access the device about the consequences.*NEWPARA**COMPANY* determined that no login banner was configured.";
const char *report_banner_impact = "Attackers who have gained access to a device could avoid legal action if no banner is configured to warn against unauthorised access.";
const char *report_banner_ease = "";
const char *report_banner_rec = "*COMPANY* recommends that a banner be configured that warns against unauthorised access. Banners are configured on Cisco devices using a delimiter character. A delimiter character is specified in the banner command and is used again to mark the end of the banner. The Cisco command to add a login banner, that is presented to users prior to authentication, is:*NEWPARA**COMMAND*banner login *CMDREQUIRE**CMDUSER*delimiter*-CMDUSER**-CMDREQUIRE* *CMDUSER*The banner text*-CMDUSER* *CMDREQUIRE**CMDUSER*delimiter*-CMDUSER**-CMDREQUIRE**-COMMAND*";
const char *report_banner_context = "no login banner has been configured";
const char *report_banner_rectext = "Configure a login banner";

// IP Domain Lookup
const char *report_lookup_title = "Domain Lookups";
const char *report_lookup_obs = "Cisco *ABBREV*IOS*-ABBREV*-based devices support name lookups using the *ABBREV*DNS*-ABBREV*. However, if a *ABBREV*DNS*-ABBREV* server has not been configured, then the *ABBREV*DNS*-ABBREV* request is broadcast.*NEWPARA**COMPANY* determined that name lookups had not been disabled*SINGULA* and no *ABBREV*DNS*-ABBREV* servers had been configured*-SINGULA*.";
const char *report_lookup_impact = "An attacker who was able to capture network traffic could monitor *ABBREV*DNS*-ABBREV* queries from the *DEVICETYPE*. Furthermore, Cisco devices can connect to Telnet servers by supplying only the hostname or *ABBREV*IP*-ABBREV* address of the server. A mistyped Cisco command could be interpreted as an attempt to connect to a Telnet server and broadcast on the network.";
const char *report_lookup_ease = "It would be trivial for an attacker to capture network traffic*SINGULA* broadcast*-SINGULA* from a *DEVICETYPE*. Furthermore, network traffic capture tools are widely available on the Internet.";
const char *report_lookup_rec = "*COMPANY* recommends that domain lookups be disabled. Domain lookups can be disabled with the following command:*NEWPARA**COMMAND*no ip domain-lookup*-COMMAND**SINGULA**NEWLINE*If domain lookups are required, *COMPANY* recommends that *ABBREV*DNS*-ABBREV* be configured. *ABBREV*DNS*-ABBREV* can be configured with the following command:*NEWPARA**COMMAND*ip name-server *CMDREQUIRE**CMDUSER*IP address*-CMDUSER**-CMDREQUIRE**-COMMAND**-SINGULA*";
const char *report_lookup_context = "domain lookups were enabled";
const char *report_lookup_rectext = "Disable domain lookups";

// PAD
const char *report_pad_title = "Packet Assembler / Disassembler";
const char *report_pad_obs = "The *ABBREV*PAD*-ABBREV* service enables X.25 connections between network systems. The *ABBREV*PAD*-ABBREV* service is enabled by default on most Cisco *ABBREV*IOS*-ABBREV* devices but it is only required if support for X.25 links is necessary.*NEWPARA**COMPANY* determined that the *ABBREV*PAD*-ABBREV* service had not been disabled.";
const char *report_pad_impact = "Running unused services increases the chances of an attacker finding a security hole or fingerprinting a device.";
const char *report_pad_ease = "";
const char *report_pad_rec = "*COMPANY* recommends that, if not required, the *ABBREV*PAD*-ABBREV* service be disabled. Use the following command to disable the *ABBREV*PAD*-ABBREV* service:*NEWPARA**COMMAND*no service pad*-COMMAND*";
const char *report_pad_context = "the PAD service was enabled";
const char *report_pad_rectext = "Disable the PAD service";

// Maintenance Operations Protocol (MOP)
const char *report_mop_title = "Maintenance Operations Protocol";
const char *report_mop_obs = "*ABBREV*MOP*-ABBREV* is used with the DECnet protocol suite. *ABBREV*MOP*-ABBREV* is enabled by default on ethernet interfaces in some versions of *ABBREV*IOS*-ABBREV*.*NEWPARA**COMPANY* determined that *ABBREV*MOP*-ABBREV* had not been disabled on all ethernet interfaces.";
const char *report_mop_impact = "Running unused services increases the chances of an attacker finding a security hole or fingerprinting a device.";
const char *report_mop_ease = "";
const char *report_mop_rec = "*COMPANY* recommends that, if not required, *ABBREV*MOP*-ABBREV* be disabled on all ethernet interfaces. *ABBREV*MOP*-ABBREV* can be disabled on each interface with the following command:*NEWPARA**COMMAND*no mop enabled*-COMMAND*";
const char *report_mop_context = "MOP had not been disabled on all interfaces";
const char *report_mop_rectext = "Disable MOP on all interfaces";


// ----------------------------------------------------------------------------------
// Configuration Text...

// Introduction
const char *report_config_intro_fw1 = "This section details the configuration settings of the *DEVICETYPE* firewall.";
const char *report_config_intro = "This section details the configuration settings of the *DEVICETYPE* device *DEVICENAME*.";
const char *report_config_title = "Device Configuration";

// General
const char *settings_general_title = "General";
const char *settings_general_table = "General device settings";

// General Configuration Table Headings...
struct tableHeading settings_general_heading1 = {false, 7, "Setting", 0};
struct tableHeading settings_general_heading  = {false, 3, "Description", &settings_general_heading1};

// DNS Settings
const char *settings_dns_title = "Domain Name Settings";
const char *settings_dns_table = "Domain name settings";

// Time Zone Settings
const char *settings_timezone_title = "Time Zone Settings";
const char *settings_timezone_table = "Time zone settings";

// Administrative Settings
const char *settings_admin_title = "Administrative Settings";
const char *settings_admin_table = "Administrative settings";
const char *settings_admins_table = "Administrative users";
struct tableHeading settings_admins_heading3 = {false, 1, "Trustee", 0};
struct tableHeading settings_admins_heading2 = {false, 2, "Privilege", &settings_admins_heading3};
struct tableHeading settings_admins_heading1 = {true, 2, "Encrypted Password", &settings_admins_heading2};
struct tableHeading settings_admins_heading  = {false, 2, "Username", &settings_admins_heading1};

// Authentication Servers
const char *settings_authservers_title = "Authentication Servers";
const char *settings_authservers_table = "Authentication servers";
struct tableHeading settings_authservers_heading8 = {true, 3, "Secret / Key", 0};
struct tableHeading settings_authservers_heading7 = {false, 3, "Interface", &settings_authservers_heading8};
struct tableHeading settings_authservers_heading6 = {false, 2, "Forced Timeout", &settings_authservers_heading7};
struct tableHeading settings_authservers_heading5 = {false, 2, "Timeout", &settings_authservers_heading6};
struct tableHeading settings_authservers_heading4 = {false, 3, "Backup(s)", &settings_authservers_heading5};
struct tableHeading settings_authservers_heading3 = {false, 3, "Server", &settings_authservers_heading4};
struct tableHeading settings_authservers_heading2 = {false, 3, "Type", &settings_authservers_heading3};
struct tableHeading settings_authservers_heading1 = {false, 3, "Server Name", &settings_authservers_heading2};
struct tableHeading settings_authservers_heading  = {false, 1, "ID", &settings_authservers_heading1};

// User Accounts and Privilages
const char *settings_users_title = "User Accounts and Privilages";
const char *settings_passwords_title = "Passwords";
struct tableHeading settings_passwords_heading1 = {true, 1, "Encrypted Password", 0};
struct tableHeading settings_passwords_heading  = {false, 1, "Login", &settings_passwords_heading1};
const char *settings_enable_table = "Enable Passwords";
struct tableHeading report_enable_heading2 = {false, 1, "Encryption", 0};
struct tableHeading report_enable_heading1 = {true, 2, "Password", &report_enable_heading2};
struct tableHeading report_enable_heading  = {false, 1, "Level", &report_enable_heading1};
struct tableHeading report_enablepix_heading1 = {true, 2, "Encrypted Password", 0};
struct tableHeading report_enablepix_heading  = {false, 1, "Level", &report_enablepix_heading1};
const char *settings_users_table = "User Accounts";
struct tableHeading report_users_heading3 = {false, 1, "Encryption", 0};
struct tableHeading report_users_heading2 = {true, 1, "Password", &report_users_heading3};
struct tableHeading report_users_heading1 = {false, 2, "Privilage", &report_users_heading2};
struct tableHeading report_users_heading  = {false, 1, "Username", &report_users_heading1};
struct tableHeading report_userspix_heading3 = {true, 2, "Encrypted Password", 0};
struct tableHeading report_userspix_heading2 = {false, 1, "Encryption", &report_userspix_heading3};
struct tableHeading report_userspix_heading1 = {false, 1, "Level", &report_userspix_heading2};
struct tableHeading report_userspix_heading  = {false, 2, "Username", &report_userspix_heading1};
const char *settings_logon_password = "The configured logon password was encrypted as";
const char *settings_privs_desc = "IOS-based Cisco devices have sixteen privilage levels between 0 and 15. The enable privilage level is 15 and user exec mode is level 1. *ABBREV*IOS*-ABBREV* commands are assigned to privilage levels 1 or 15 by default. However, *ABBREV*IOS*-ABBREV* commands can be moved to other privilage levels.";
const char *settings_privs_table = "Privilages";
struct tableHeading report_privs_heading1 = {false, 2, "Command", 0};
struct tableHeading report_privs_heading  = {false, 1, "Privilage Level", &report_privs_heading1};
const char *settings_banner_desc = "Login banners should provide a warning against unauthorised access to the device. The configured banner on *DEVICENAME* was:";

// Services
const char *settings_services_title = "Services";
const char *settings_services_table = "Device services";
struct tableHeading report_services_heading1 = {false, 1, "Status", 0};
struct tableHeading report_services_heading  = {false, 2, "Service", &report_services_heading1};

// Switch Configuration
const char *settings_switch_title = "Switch Configuration";
const char *settings_switch_table = "General switch settings";

// Logging
const char *settings_logging_title = "Logging";
const char *settings_logging_table = "Logging configuration";

// CDP
const char *settings_cdp_title = "Cisco Discovery Protocol";
const char *settings_cdp_table = "Cisco Discovery Protocol configuration";

// SNMP
const char *settings_snmp_title = "Simple Network Management Protocol";
const char *settings_snmp_desc = "*ABBREV*SNMP*-ABBREV* is used to assist network administrators in monitoring and managing a wide variety of network devices. There are three main versions of *ABBREV*SNMP*-ABBREV* in use. Versions 1 and 2 of *ABBREV*SNMP*-ABBREV* are both secured with a community string and authenticate and transmit network packets without any form of encryption. *ABBREV*SNMP*-ABBREV* version 3 provides several levels of authentication and encryption. The most basic level provides a similar protection to that of the earlier protocol versions. However, *ABBREV*SNMP*-ABBREV* version 3 can be configured to provide encrypted authentication (auth) and secured further with support for encrypted data communications (priv).*NEGATIVE* However, *DEVICETYPE* currently only support *ABBREV*SNMP*-ABBREV* versions 1 and 2.*-NEGATIVE*";
const char *settings_snmp_table = "General SNMP service configuration";
const char *settings_snmp_sos_table = "SNMP configuration";
const char *settings_snmpstring_table = "SNMP community strings";
struct tableHeading settings_snmp_css_heading1 = {false, 1, "Access Type", 0};
struct tableHeading settings_snmp_css_heading  = {true, 1, "Community", &settings_snmp_css_heading1};
struct tableHeading settings_snmpstring_heading4 = {false, 1, "Enabled", 0};
struct tableHeading settings_snmpstring_heading3 = {false, 2, "Access-List", &settings_snmpstring_heading4};
struct tableHeading settings_snmpstring_heading2 = {false, 2, "View", &settings_snmpstring_heading3};
struct tableHeading settings_snmpstring_heading1 = {false, 2, "Access", &settings_snmpstring_heading2};
struct tableHeading settings_snmpstring_heading  = {true, 3, "Community", &settings_snmpstring_heading1};
struct tableHeading settings_snmpcomm_heading2 = {false, 1, "Access Type", 0};
struct tableHeading settings_snmpcomm_heading1 = {true, 1, "Community String", &settings_snmpcomm_heading2};
struct tableHeading settings_snmpcomm_heading  = {false, 1, "Community Type", &settings_snmpcomm_heading1};
const char *settings_snmpview_table = "SNMP View";
struct tableHeading settings_snmpview_heading1 = {false, 1, "Access", 0};
struct tableHeading settings_snmpview_heading  = {false, 3, "SNMP MIB", &settings_snmpview_heading1};
const char *settings_snmpgroups_table = "SNMP groups";
struct tableHeading settings_snmpgroups_heading6 = {false, 1, "ACL", 0};
struct tableHeading settings_snmpgroups_heading5 = {false, 1, "Context", &settings_snmpgroups_heading6};
struct tableHeading settings_snmpgroups_heading4 = {false, 1, "Notify View", &settings_snmpgroups_heading5};
struct tableHeading settings_snmpgroups_heading3 = {false, 1, "Write View", &settings_snmpgroups_heading4};
struct tableHeading settings_snmpgroups_heading2 = {false, 1, "Read View", &settings_snmpgroups_heading3};
struct tableHeading settings_snmpgroups_heading1 = {false, 1, "SNMP Version", &settings_snmpgroups_heading2};
struct tableHeading settings_snmpgroups_heading  = {false, 1, "Name", &settings_snmpgroups_heading1};
const char *settings_snmpgroup_table1 = "SNMP v1 group ";
const char *settings_snmpgroup_table2 = "SNMP v2c group ";
const char *settings_snmpgroup_table3 = "SNMP v3 (No Auth) group ";
const char *settings_snmpgroup_table4 = "SNMP v3 (Auth) group ";
const char *settings_snmpgroup_table5 = "SNMP v3 (Auth and Priv) group ";
const char *settings_snmpgroup_table6 = "SNMP users not in a group";
struct tableHeading settings_snmpnoauth_heading1 = {false, 1, "ACL", 0};
struct tableHeading settings_snmpnoauth_heading = {false, 1, "Username", &settings_snmpnoauth_heading1};
struct tableHeading settings_snmpauth_heading3 = {false, 1, "ACL", 0};
struct tableHeading settings_snmpauth_heading2 = {false, 1, "Auth Encryption", &settings_snmpauth_heading3};
struct tableHeading settings_snmpauth_heading1 = {true, 1, "Auth Password", &settings_snmpauth_heading2};
struct tableHeading settings_snmpauth_heading  = {false, 1, "Username", &settings_snmpauth_heading1};
struct tableHeading settings_snmppriv_heading5 = {false, 1, "ACL", 0};
struct tableHeading settings_snmppriv_heading4 = {false, 1, "Priv Encryption", &settings_snmppriv_heading5};
struct tableHeading settings_snmppriv_heading3 = {true, 1, "Priv Password", &settings_snmppriv_heading4};
struct tableHeading settings_snmppriv_heading2 = {false, 1, "Auth Encryption", &settings_snmppriv_heading3};
struct tableHeading settings_snmppriv_heading1 = {true, 1, "Auth Password", &settings_snmppriv_heading2};
struct tableHeading settings_snmppriv_heading  = {false, 1, "Username", &settings_snmppriv_heading1};
const char *settings_snmphost_table = "SNMP hosts";
struct tableHeading settings_snmphost_heading2 = {true, 1, "Community String", 0};
struct tableHeading settings_snmphost_heading1 = {false, 1, "SNMP Version", &settings_snmphost_heading2};
struct tableHeading settings_snmphost_heading  = {false, 1, "SNMP Host", &settings_snmphost_heading1};
struct tableHeading settings_snmphosts_heading5 = {false, 1, "Index", 0};
struct tableHeading settings_snmphosts_heading4 = {false, 1, "Owner", &settings_snmphosts_heading5};
struct tableHeading settings_snmphosts_heading3 = {false, 1, "Port", &settings_snmphosts_heading4};
struct tableHeading settings_snmphosts_heading2 = {false, 1, "Version", &settings_snmphosts_heading3};
struct tableHeading settings_snmphosts_heading1 = {true, 1, "Community", &settings_snmphosts_heading2};
struct tableHeading settings_snmphosts_heading  = {false, 1, "Host", &settings_snmphosts_heading1};
struct tableHeading settings_snmpPIXhosts_heading5 = {false, 1, "Access", 0};
struct tableHeading settings_snmpPIXhosts_heading4 = {false, 1, "UDP Port", &settings_snmpPIXhosts_heading5};
struct tableHeading settings_snmpPIXhosts_heading3 = {false, 1, "Version", &settings_snmpPIXhosts_heading4};
struct tableHeading settings_snmpPIXhosts_heading2 = {true, 1, "Community", &settings_snmpPIXhosts_heading3};
struct tableHeading settings_snmpPIXhosts_heading1 = {false, 1, "Address", &settings_snmpPIXhosts_heading2};
struct tableHeading settings_snmpPIXhosts_heading  = {false, 1, "Interface", &settings_snmpPIXhosts_heading1};
const char *settings_snmptrap_table = "SNMP traps";
struct tableHeading settings_snmptrap_heading = {false, 1, "SNMP Trap", 0};
struct tableHeading settings_snmptraps_heading1 = {false, 1, "Trap", 0};
struct tableHeading settings_snmptraps_heading  = {false, 1, "Status", &settings_snmptraps_heading1};
struct tableHeading settings_snmpPIXtraps_heading1 = {false, 1, "Trap", 0};
struct tableHeading settings_snmpPIXtraps_heading  = {false, 1, "Type", &settings_snmpPIXtraps_heading1};
struct tableHeading settings_snmpstring_sos_heading4 = {false, 1, "Traffic Traps", 0};
struct tableHeading settings_snmpstring_sos_heading3 = {false, 1, "Traps", &settings_snmpstring_sos_heading4};
struct tableHeading settings_snmpstring_sos_heading2 = {false, 2, "Access", &settings_snmpstring_sos_heading3};
struct tableHeading settings_snmpstring_sos_heading1 = {false, 1, "SNMP Version", &settings_snmpstring_sos_heading2};
struct tableHeading settings_snmpstring_sos_heading  = {true, 2, "Community", &settings_snmpstring_sos_heading1};
struct tableHeading settings_snmphost_sos_heading3 = {false, 2, "Interface", 0};
struct tableHeading settings_snmphost_sos_heading2 = {false, 1, "SNMP Version", &settings_snmphost_sos_heading3};
struct tableHeading settings_snmphost_sos_heading1 = {false, 2, "Community", &settings_snmphost_sos_heading2};
struct tableHeading settings_snmphost_sos_heading  = {false, 2, "Host", &settings_snmphost_sos_heading1};

// SSH
const char *settings_ssh_title = "Secure Shell";
const char *settings_ssh_table = "SSH configuration";
const char *settings_sshman_table = "SSH remote management hosts";
struct tableHeading settings_sshman_heading2 = {false, 1, "Interface", 0};
struct tableHeading settings_sshman_heading1 = {false, 1, "Netmask", &settings_sshman_heading2};
struct tableHeading settings_sshman_heading  = {false, 1, "Host", &settings_sshman_heading1};
const char *settings_sshint_table = "SSH server network interfaces";
struct tableHeading settings_sshint_heading = {false, 1, "Network Interface", 0};

// NTP
const char *settings_ntp_title = "Network Time Protocol";
const char *settings_ntp_table = "NTP configuration";
const char *settings_ntpserv_table = "NTP servers";
struct tableHeading settings_ntpserv_heading1 = {false, 1, "NTP Key Number", 0};
struct tableHeading settings_ntpserv_heading  = {false, 1, "NTP Server", &settings_ntpserv_heading1};
const char *settings_ntppeer_table = "NTP peers";
struct tableHeading settings_ntppeer_heading1 = {false, 1, "NTP Key Number", 0};
struct tableHeading settings_ntppeer_heading  = {false, 1, "NTP Peer", &settings_ntppeer_heading1};
const char *settings_ntpkeys_table = "NTP keys";
struct tableHeading settings_ntpkeys_heading2 = {true, 2, "Key", 0};
struct tableHeading settings_ntpkeys_heading1 = {false, 1, "Trusted", &settings_ntpkeys_heading2};
struct tableHeading settings_ntpkeys_heading  = {false, 1, "NTP Key Number", &settings_ntpkeys_heading1};
const char *settings_ntpaccess_table = "NTP access groups";
struct tableHeading settings_ntpaccess_heading1 = {false, 1, "Access-List Number", 0};
struct tableHeading settings_ntpaccess_heading  = {false, 1, "Access Type", &settings_ntpaccess_heading1};

// FTP
const char *settings_ftp_title = "File Transfer Protocol";
const char *settings_ftp_table = "FTP client configuration";
const char *settings_ftpint_table = "FTP client source network interfaces";

// HTTP
const char *settings_http_title = "HyperText Transfer Protocol";
const char *settings_http_table = "HTTP configuration";
const char *settings_httphosts_table = "Allowed HTTP clients";
struct tableHeading settings_httphosts_heading2 = {false, 2, "Net Mask", 0};
struct tableHeading settings_httphosts_heading1 = {false, 1, "IP Address", &settings_httphosts_heading2};
struct tableHeading settings_httphosts_heading  = {false, 1, "Interface", &settings_httphosts_heading1};

// TACACS
const char *settings_tacacs_title = "Terminal Access Controller Access Control System";
const char *settings_tacacs_table = "TACACS configuration";
const char *settings_tacacsserv_table = "TACACS servers";
struct tableHeading settings_tacacsserv_heading = {false, 1, "TACACS Server", 0};

// AAA
const char *settings_aaa_title = "Authentication, Authorization and Accounting";
const char *settings_aaa_table1 = "AAA servers for user";
const char *settings_aaa_table2 = "using RADIUS";
const char *settings_aaa_table3 = "using TACACS";
const char *settings_aaa_table4 = "using Kerberos";
struct tableHeading settings_aaa_heading4 = {false, 1, "Key Encryption", 0};
struct tableHeading settings_aaa_heading3 = {true, 1, "Key", &settings_aaa_heading4};
struct tableHeading settings_aaa_heading2 = {false, 1, "Acct Port", &settings_aaa_heading3};
struct tableHeading settings_aaa_heading1 = {false, 1, "Auth Port", &settings_aaa_heading2};
struct tableHeading settings_aaa_heading  = {false, 1, "Server", &settings_aaa_heading1};

// NAT & PAT
const char *settings_natpat_title = "NAT and PAT";
const char *settings_nat_title = "NAT";
const char *settings_natpat_desc = "*ABBREV*NAT*-ABBREV* is used to map an *ABBREV*IP*-ABBREV* address to an alternative *ABBREV*IP*-ABBREV* address and is commonly used to map internal network *ABBREV*IP*-ABBREV* addresses to Internet visible *ABBREV*IP*-ABBREV* addresses.*SINGULA* *ABBREV*PAT*-ABBREV* is similar to *ABBREV*NAT*-ABBREV*, except *ABBREV*PAT*-ABBREV* is used to map network protocols and ports. There are two different types of *ABBREV*NAT*-ABBREV* and *ABBREV*PAT*-ABBREV*, static and dynamic. Static *ABBREV*NAT*-ABBREV* and *ABBREV*PAT*-ABBREV* create a fixed translation, whereas with dynamic *ABBREV*NAT*-ABBREV* and *ABBREV*PAT*-ABBREV* each host uses a different address or port for each translation. Static *ABBREV*NAT*-ABBREV* and *ABBREV*PAT*-ABBREV* can allow a remote host to initiate a connection.*-SINGULA**PLAURAL* There are four different types of *ABBREV*NAT*-ABBREV* on *DEVICETYPE* devices, dynamic *ABBREV*NAT*-ABBREV*, static *ABBREV*NAT*-ABBREV*, port static *ABBREV*NAT*-ABBREV* and network static *ABBREV*NAT*-ABBREV*. Static *ABBREV*NAT*-ABBREV* translates one specific *ABBREV*IP*-ABBREV* address into another specific *ABBREV*IP*-ABBREV* address. Dynamic *ABBREV*NAT*-ABBREV* translates an *ABBREV*IP*-ABBREV* address into one of a pool of *ABBREV*IP*-ABBREV* addresses. Port static *ABBREV*NAT*-ABBREV* translates a specific *ABBREV*IP*-ABBREV* address and port to another specific *ABBREV*IP*-ABBREV* address and port. Finally, network static *ABBREV*NAT*-ABBREV* translates a specific network subnet to another specific network subnet.*-PLAURAL*";
struct tableHeading settings_natstatic_heading3 = {false, 1, "To", 0};
struct tableHeading settings_natstatic_heading2 = {false, 1, "From", &settings_natstatic_heading3};
struct tableHeading settings_natstatic_heading1 = {false, 1, "IPSec-ESP", &settings_natstatic_heading2};
struct tableHeading settings_natstatic_heading  = {false, 1, "Source", &settings_natstatic_heading1};
const char *settings_nat_dynamic_table = "Dynamic NAT";
struct tableHeading settings_natdynamic_heading4 = {false, 1, "To", 0};
struct tableHeading settings_natdynamic_heading3 = {false, 1, "To Type", &settings_natdynamic_heading4};
struct tableHeading settings_natdynamic_heading2 = {false, 1, "From", &settings_natdynamic_heading3};
struct tableHeading settings_natdynamic_heading1 = {false, 1, "From Type", &settings_natdynamic_heading2};
struct tableHeading settings_natdynamic_heading  = {false, 1, "Source", &settings_natdynamic_heading1};
const char *settings_nat_portstatic_table = "Port static NAT";
struct tableHeading settings_natportstat_heading5 = {false, 1, "To Port", 0};
struct tableHeading settings_natportstat_heading4 = {false, 1, "To", &settings_natportstat_heading5};
struct tableHeading settings_natportstat_heading3 = {false, 1, "From Port", &settings_natportstat_heading4};
struct tableHeading settings_natportstat_heading2 = {false, 1, "From", &settings_natportstat_heading3};
struct tableHeading settings_natportstat_heading1 = {false, 1, "Protocol", &settings_natportstat_heading2};
struct tableHeading settings_natportstat_heading  = {false, 1, "Source", &settings_natportstat_heading1};
const char *settings_nat_netstatic_table = "Network static NAT";
struct tableHeading settings_natnetstatic_heading3 = {false, 1, "Network Mask", 0};
struct tableHeading settings_natnetstatic_heading2 = {false, 1, "To Network", &settings_natnetstatic_heading3};
struct tableHeading settings_natnetstatic_heading1 = {false, 1, "From Network", &settings_natnetstatic_heading2};
struct tableHeading settings_natnetstatic_heading  = {false, 1, "Source", &settings_natnetstatic_heading1};
const char *settings_nat_static_table = "Static NAT";
struct tableHeading settings_nat_static_heading9 = {false, 1, "Max UDP", 0};
struct tableHeading settings_nat_static_heading8 = {false, 1, "Max Embrionic", &settings_nat_static_heading9};
struct tableHeading settings_nat_static_heading7 = {false, 1, "Max TCP", &settings_nat_static_heading8};
struct tableHeading settings_nat_static_heading6 = {false, 1, "Nailed", &settings_nat_static_heading7};
struct tableHeading settings_nat_static_heading5 = {false, 1, "Rand. Seq. No.", &settings_nat_static_heading6};
struct tableHeading settings_nat_static_heading4 = {false, 1, "DNS Update", &settings_nat_static_heading5};
struct tableHeading settings_nat_static_heading3 = {false, 2, "Mapped IP", &settings_nat_static_heading4};
struct tableHeading settings_nat_static_heading2 = {false, 2, "Mapped Interface", &settings_nat_static_heading3};
struct tableHeading settings_nat_static_heading1 = {false, 3, "Source", &settings_nat_static_heading2};
struct tableHeading settings_nat_static_heading  = {false, 2, "Interface", &settings_nat_static_heading1};
const char *settings_pat_static_table = "Static PAT";
struct tableHeading settings_pat_static_heading10 = {false, 1, "Max UDP", 0};
struct tableHeading settings_pat_static_heading9 = {false, 1, "Max Embrionic", &settings_pat_static_heading10};
struct tableHeading settings_pat_static_heading8 = {false, 1, "Max TCP", &settings_pat_static_heading9};
struct tableHeading settings_pat_static_heading7 = {false, 1, "Nailed", &settings_pat_static_heading8};
struct tableHeading settings_pat_static_heading6 = {false, 1, "Rand. Seq. No.", &settings_pat_static_heading7};
struct tableHeading settings_pat_static_heading5 = {false, 1, "DNS Update", &settings_pat_static_heading6};
struct tableHeading settings_pat_static_heading4 = {false, 2, "Mapped IP", &settings_pat_static_heading5};
struct tableHeading settings_pat_static_heading3 = {false, 2, "Mapped Interface", &settings_pat_static_heading4};
struct tableHeading settings_pat_static_heading2 = {false, 3, "Source", &settings_pat_static_heading3};
struct tableHeading settings_pat_static_heading1 = {false, 2, "Interface", &settings_pat_static_heading2};
struct tableHeading settings_pat_static_heading  = {false, 1, "Protocol", &settings_pat_static_heading1};

// Routing
const char *settings_routing_title = "Routing";
const char *settings_routing_desc = "A network device's routing tables can be configured with static routes or updated dynamically. Routing protocols are used by network routing devices to dynamically update the routing tables that devices use to forward network traffic to their destination. Router protocols can be split into two different categories; *ABBREV*IGPs*-ABBREV* and *ABBREV*EGPs*-ABBREV*. *ABBREV*IGPs*-ABBREV* are usually used in situations where the routing devices are all controlled by a single entity, such as within a company. *ABBREV*EGPs*-ABBREV* are usually used in situations where routing devices are managed by a number of entities, such as the Internet. Typically routing devices support a number of standard routing protocols.";
const char *settings_static_route_table = "Static routes";
struct tableHeading settings_routeIOS_heading2 = {false, 1, "Gateway", 0};
struct tableHeading settings_routeIOS_heading1 = {false, 1, "Net Mask", &settings_routeIOS_heading2};
struct tableHeading settings_routeIOS_heading  = {false, 1, "IP Address", &settings_routeIOS_heading1};
struct tableHeading settings_route_heading6 = {false, 1, "Tunelled", 0};
struct tableHeading settings_route_heading5 = {false, 1, "Tracking", &settings_route_heading6};
struct tableHeading settings_route_heading4 = {false, 1, "Metric", &settings_route_heading5};
struct tableHeading settings_route_heading3 = {false, 2, "Gateway", &settings_route_heading4};
struct tableHeading settings_route_heading2 = {false, 2, "Net Mask", &settings_route_heading3};
struct tableHeading settings_route_heading1 = {false, 2, "IP Address", &settings_route_heading2};
struct tableHeading settings_route_heading  = {false, 2, "Interface", &settings_route_heading1};
const char *settings_routemap_desc = "Route maps can be configured to implement policy-based routing or to redistribute a route from one routing protocol into another routing protocol. Multiple route maps can be configured with the same map tag (name) and a sequence number used to determine their sequence.";
const char *settings_routemap_table = "Route maps";
struct tableHeading settings_routeMap_heading2 = {false, 1, "Access", 0};
struct tableHeading settings_routeMap_heading1 = {false, 1, "Sequence", &settings_routeMap_heading2};
struct tableHeading settings_routeMap_heading  = {false, 1, "Map Tag", &settings_routeMap_heading1};

// VRRP
const char *settings_vrrp_desc = "*ABBREV*VRRP*-ABBREV* is used to provide router load balancing and redundancy against a single point of failure. A *ABBREV*VRRP*-ABBREV* master router will send advertisements to other routers in the same *ABBREV*VRRP*-ABBREV* group. If the master *ABBREV*VRRP*-ABBREV* router fails, the other routers in the *ABBREV*VRRP*-ABBREV* group hold an election to determine which router will become the new master.";
const char *settings_vrrp_table = "VRRP configuration";
struct tableHeading settings_vrrp_interface_heading9 = {false, 1, "Active", 0};
struct tableHeading settings_vrrp_interface_heading8 = {true,  2, "Password", &settings_vrrp_interface_heading9};
struct tableHeading settings_vrrp_interface_heading7 = {false, 2, "Authentication", &settings_vrrp_interface_heading8};
struct tableHeading settings_vrrp_interface_heading6 = {false, 1, "Priority", &settings_vrrp_interface_heading7};
struct tableHeading settings_vrrp_interface_heading5 = {false, 2, "Secondary IP", &settings_vrrp_interface_heading6};
struct tableHeading settings_vrrp_interface_heading4 = {false, 2, "IP Address", &settings_vrrp_interface_heading5};
struct tableHeading settings_vrrp_interface_heading3 = {false, 3, "Description", &settings_vrrp_interface_heading4};
struct tableHeading settings_vrrp_interface_heading2 = {false, 1, "VRRP", &settings_vrrp_interface_heading3};
struct tableHeading settings_vrrp_interface_heading1 = {false, 1, "VRRP Group", &settings_vrrp_interface_heading2};
struct tableHeading settings_vrrp_interface_heading  = {false, 2, "Interface", &settings_vrrp_interface_heading1};

// RIP
const char *settings_rip_desc = "*ABBREV*RIP*-ABBREV* is an *ABBREV*IGP*-ABBREV* and calculates routes using a distance vector. *ABBREV*RIP*-ABBREV* is only suitable for small networks, routing updates are sent every 30 seconds and contain the entire routing table. Furthermore, *ABBREV*RIP*-ABBREV* has a maximum distance of 15 hops. If *ABBREV*RIP*-ABBREV* routes have not been updated within three minutes the route is marked as unusable. Routes not updated within four minutes are removed.";
const char *settings_rip_table = "RIP configuration";
const char *settings_rip_interface_table = "RIP network interface configuration";
struct tableHeading settings_rip_interface_heading8 = {false, 1, "Triggered", 0};
struct tableHeading settings_rip_interface_heading7 = {false, 1, "v2 Broadcast", &settings_rip_interface_heading8};
struct tableHeading settings_rip_interface_heading6 = {false, 1, "Receive Version", &settings_rip_interface_heading7};
struct tableHeading settings_rip_interface_heading5 = {false, 1, "Send Version", &settings_rip_interface_heading6};
struct tableHeading settings_rip_interface_heading4 = {false, 1, "Key Chain", &settings_rip_interface_heading5};
struct tableHeading settings_rip_interface_heading3 = {false, 1, "Authentication", &settings_rip_interface_heading4};
struct tableHeading settings_rip_interface_heading2 = {false, 1, "IP Address", &settings_rip_interface_heading3};
struct tableHeading settings_rip_interface_heading1 = {false, 1, "Description", &settings_rip_interface_heading2};
struct tableHeading settings_rip_interface_heading  = {false, 1, "Interface", &settings_rip_interface_heading1};
const char *settings_rip_neightbor_table = "RIP neighbors";
struct tableHeading settings_rip_neightbor_heading = {false, 1, "RIP Neighbor", 0};
const char *settings_rip_networks_table = "RIP networks";
struct tableHeading settings_rip_networks_heading = {false, 1, "RIP Network", 0};

// EIGRP
const char *settings_eigrp_desc = "*ABBREV*EIGRP*-ABBREV* is an *ABBREV*IGP*-ABBREV* and is a distance vector based protocol like *ABBREV*RIP*-ABBREV*, but incorporates some features from link state protocols such as *ABBREV*OSPF*-ABBREV*. *ABBREV*EIGRP*-ABBREV* was developed by Cisco as an enhanced version of *ABBREV*IGRP*-ABBREV*. Unlike *ABBREV*RIP*-ABBREV*, *ABBREV*EIGRP*-ABBREV* transmits changes to network routes to its neighbors and is suitable for larger networks.";
struct tableHeading settings_eigrp_interface_heading7 = {false, 1, "Bandwidth", 0};
struct tableHeading settings_eigrp_interface_heading6 = {false, 2, "Key Chain", &settings_eigrp_interface_heading7};
struct tableHeading settings_eigrp_interface_heading5 = {false, 1, "MD5 Auth", &settings_eigrp_interface_heading6};
struct tableHeading settings_eigrp_interface_heading4 = {false, 1, "Passive", &settings_eigrp_interface_heading5};
struct tableHeading settings_eigrp_interface_heading3 = {false, 1, "Active", &settings_eigrp_interface_heading4};
struct tableHeading settings_eigrp_interface_heading2 = {false, 2, "IP Address", &settings_eigrp_interface_heading3};
struct tableHeading settings_eigrp_interface_heading1 = {false, 2, "Description", &settings_eigrp_interface_heading2};
struct tableHeading settings_eigrp_interface_heading  = {false, 2, "Interface", &settings_eigrp_interface_heading1};

// BGP
const char *settings_bgp_desc = "*ABBREV*BGP*-ABBREV* is an *ABBREV*EGP*-ABBREV*. *ABBREV*BGP*-ABBREV* route updates are sent from defined *ABBREV*BGP*-ABBREV* peers using *ABBREV*TCP*-ABBREV* connections.";
struct tableHeading settings_bgp_heading5 = {false, 1, "TTL Hops", 0};
struct tableHeading settings_bgp_heading4 = {false, 2, "Autonomous Number", &settings_bgp_heading5};
struct tableHeading settings_bgp_heading3 = {false, 3, "Password Encryption", &settings_bgp_heading4};
struct tableHeading settings_bgp_heading2 = {true, 3, "Password", &settings_bgp_heading3};
struct tableHeading settings_bgp_heading1 = {false, 5, "Description", &settings_bgp_heading2};
struct tableHeading settings_bgp_heading  = {false, 2, "Neibhbor", &settings_bgp_heading1};
struct tableHeading settings_bgp_interface_heading4 = {false, 1, "Passive", 0};
struct tableHeading settings_bgp_interface_heading3 = {false, 1, "Active", &settings_bgp_interface_heading4};
struct tableHeading settings_bgp_interface_heading2 = {false, 2, "IP Address", &settings_bgp_interface_heading3};
struct tableHeading settings_bgp_interface_heading1 = {false, 2, "Description", &settings_bgp_interface_heading2};
struct tableHeading settings_bgp_interface_heading  = {false, 2, "Interface", &settings_bgp_interface_heading1};

// OSPF
const char *settings_ospf_desc = "*ABBREV*OSPF*-ABBREV* protocol is an *ABBREV*IGP*-ABBREV*. *ABBREV*OSPF*-ABBREV* packets are sent when the network configuration changes, such as when a route goes down, and the packets only contain the change. Since the information sent in *ABBREV*OSPF*-ABBREV* packets is limited to any network changes, the protocol is well suited to complex network configurations.*NEWPARA*For *ABBREV*OSPF*-ABBREV* to work on a network interface it must be included within an *ABBREV*OSPF*-ABBREV* network area.";
struct tableHeading settings_ospf_network_heading2 = {false, 1, "Area ID", 0};
struct tableHeading settings_ospf_network_heading1 = {false, 2, "Network Mask", &settings_ospf_network_heading2};
struct tableHeading settings_ospf_network_heading  = {false, 2, "Network", &settings_ospf_network_heading1};
struct tableHeading settings_ospf_area_heading2 = {false, 1, "Authentication", 0};
struct tableHeading settings_ospf_area_heading1 = {false, 1, "Default Cost", &settings_ospf_area_heading2};
struct tableHeading settings_ospf_area_heading  = {false, 1, "Area ID", &settings_ospf_area_heading1};
struct tableHeading settings_ospf_interface_heading7 = {false, 1, "OSPF Mode", 0};
struct tableHeading settings_ospf_interface_heading6 = {false, 1, "Flood Reduction", &settings_ospf_interface_heading7};
struct tableHeading settings_ospf_interface_heading5 = {false, 1, "Key Encryption", &settings_ospf_interface_heading6};
struct tableHeading settings_ospf_interface_heading4 = {true, 1, "Authentication Key", &settings_ospf_interface_heading5};
struct tableHeading settings_ospf_interface_heading3 = {false, 1, "Authentication", &settings_ospf_interface_heading4};
struct tableHeading settings_ospf_interface_heading2 = {false, 1, "IP Address", &settings_ospf_interface_heading3};
struct tableHeading settings_ospf_interface_heading1 = {false, 1, "Description", &settings_ospf_interface_heading2};
struct tableHeading settings_ospf_interface_heading  = {false, 1, "Interface", &settings_ospf_interface_heading1};
struct tableHeading settings_ospf_neighbor_heading4 = {false, 1, "Database Filter", 0};
struct tableHeading settings_ospf_neighbor_heading3 = {false, 1, "Cost Number", &settings_ospf_neighbor_heading4};
struct tableHeading settings_ospf_neighbor_heading2 = {false, 1, "Poll Interval", &settings_ospf_neighbor_heading3};
struct tableHeading settings_ospf_neighbor_heading1 = {false, 1, "Priority", &settings_ospf_neighbor_heading2};
struct tableHeading settings_ospf_neighbor_heading  = {false, 2, "Host", &settings_ospf_neighbor_heading1};

// Keys and Key Chains
const char *settings_keys_title = "Key Chains and Keys";
const char *settings_keys_table = "Key chains and keys";
struct tableHeading settings_keys_heading2 = {true, 2, "Key", 0};
struct tableHeading settings_keys_heading1 = {false, 1, "Key Number", &settings_keys_heading2};
struct tableHeading settings_keys_heading  = {false, 1, "Key Chain", &settings_keys_heading1};

// Lines
const char *settings_lines_title = "Lines";
const char *settings_lines_text = "The Cisco line configuration settings are used to configure administrative access to the device. The console line type is used for accessing the Cisco device directly through a cable attached to the device's console port. The auxiliary lines are used for remote access to the device, typically through attached modems. The *ABBREV*VTY*-ABBREV* lines are used for access to the device through a remote access service such as *ABBREV*SSH*-ABBREV* or Telnet.";
const char *settings_lines_table = "Line configuration";
struct tableHeading settings_lines_heading14 = {false, 3, "Password Encryption", 0};
struct tableHeading settings_lines_heading13 = {true,  4, "Password", &settings_lines_heading14};
struct tableHeading settings_lines_heading12 = {false, 3, "Absolute Timeout", &settings_lines_heading13};
struct tableHeading settings_lines_heading11 = {false, 3, "Session Timeout", &settings_lines_heading12};
struct tableHeading settings_lines_heading10 = {false, 3, "Exec Timeout", &settings_lines_heading11};
struct tableHeading settings_lines_heading9  = {false, 2, "Timeout", &settings_lines_heading10};
struct tableHeading settings_lines_heading8  = {false, 1, "SSH", &settings_lines_heading9};
struct tableHeading settings_lines_heading7  = {false, 1, "Telnet", &settings_lines_heading8};
struct tableHeading settings_lines_heading6  = {false, 3, "Accounting", &settings_lines_heading7};
struct tableHeading settings_lines_heading5  = {false, 3, "Authorization", &settings_lines_heading6};
struct tableHeading settings_lines_heading4  = {false, 2, "Exec", &settings_lines_heading5};
struct tableHeading settings_lines_heading3  = {false, 2, "Logins", &settings_lines_heading4};
struct tableHeading settings_lines_heading2  = {false, 1, "End Line", &settings_lines_heading3};
struct tableHeading settings_lines_heading1  = {false, 1, "Start Line", &settings_lines_heading2};
struct tableHeading settings_lines_heading   = {false, 1, "Line Type", &settings_lines_heading1};

// VLANS
const char *settings_vlan_title = "VLAN Configuration";
const char *settings_vlan_table = "VLAN configuration";
struct tableHeading settings_vlan_heading8  = {false, 1, "All Routes Hops", 0};
struct tableHeading settings_vlan_heading7  = {false, 1, "Spanning Tree Hops", &settings_vlan_heading8};
struct tableHeading settings_vlan_heading6  = {false, 1, "MTU", &settings_vlan_heading7};
struct tableHeading settings_vlan_heading5  = {false, 1, "SAID", &settings_vlan_heading6};
struct tableHeading settings_vlan_heading4  = {false, 1, "Firewall Module", &settings_vlan_heading5};
struct tableHeading settings_vlan_heading3  = {false, 2, "Type", &settings_vlan_heading4};
struct tableHeading settings_vlan_heading2  = {false, 1, "Active", &settings_vlan_heading3};
struct tableHeading settings_vlan_heading1  = {false, 2, "Name", &settings_vlan_heading2};
struct tableHeading settings_vlan_heading   = {false, 1, "VLAN", &settings_vlan_heading1};

// VTP
const char *settings_vtp_title = "VTP Configuration";
const char *settings_vtp_table = "VTP configuration";

// Switchport
const char *settings_switchport_title = "Switchport Configuration";
const char *settings_switchport_table = "Switchport configuration";
struct tableHeading settings_switchport_heading6  = {false, 1, "Security Violation", 0};
struct tableHeading settings_switchport_heading5  = {false, 1, "Port Security", &settings_switchport_heading6};
struct tableHeading settings_switchport_heading4  = {false, 1, "Mode", &settings_switchport_heading5};
struct tableHeading settings_switchport_heading3  = {false, 1, "VLAN", &settings_switchport_heading4};
struct tableHeading settings_switchport_heading2  = {false, 2, "Description", &settings_switchport_heading3};
struct tableHeading settings_switchport_heading1  = {false, 1, "Active", &settings_switchport_heading2};
struct tableHeading settings_switchport_heading   = {false, 1, "Interface", &settings_switchport_heading1};

// Ports
const char *settings_ports_title = "Port Configuration";
struct tableHeading settings_ports_heading10 = {false, 1, "STP Guard", 0};
struct tableHeading settings_ports_heading9  = {false, 1, "VLAN Trunk",  &settings_ports_heading10};
struct tableHeading settings_ports_heading8  = {false, 1, "Trunk", &settings_ports_heading9};
struct tableHeading settings_ports_heading7  = {false, 1, "CDP", &settings_ports_heading8};
struct tableHeading settings_ports_heading6  = {false, 1, "Port Security", &settings_ports_heading7};
struct tableHeading settings_ports_heading5  = {false, 1, "Duplex", &settings_ports_heading6};
struct tableHeading settings_ports_heading4  = {false, 1, "Speed", &settings_ports_heading5};
struct tableHeading settings_ports_heading3  = {false, 1, "VLAN", &settings_ports_heading4};
struct tableHeading settings_ports_heading2  = {false, 1, "Status", &settings_ports_heading3};
struct tableHeading settings_ports_heading1  = {false, 2, "Name", &settings_ports_heading2};
struct tableHeading settings_ports_heading   = {false, 1, "Port", &settings_ports_heading1};


// Interfaces
const char *settings_inter_title = "Interfaces";
const char *settings_inter_table = "Interfaces";
struct tableHeading settings_interIOSswitch_heading10 = {false, 4, "MOP", 0};
struct tableHeading settings_interIOSswitch_heading9  = {false, 4, "CDP", &settings_interIOSswitch_heading10};
struct tableHeading settings_interIOSswitch_heading8  = {false, 4, "NTP", &settings_interIOSswitch_heading9};
struct tableHeading settings_interIOSswitch_heading7  = {false, 11, "IP Direct Broadcast", &settings_interIOSswitch_heading8};
struct tableHeading settings_interIOSswitch_heading6  = {false, 7, "IP Mask Reply", &settings_interIOSswitch_heading7};
struct tableHeading settings_interIOSswitch_heading5  = {false, 6, "IP Redirect", &settings_interIOSswitch_heading6};
struct tableHeading settings_interIOSswitch_heading4  = {false, 10, "IP Unreachable", &settings_interIOSswitch_heading5};
struct tableHeading settings_interIOSswitch_heading3  = {false, 6, "Proxy ARP", &settings_interIOSswitch_heading4};
struct tableHeading settings_interIOSswitch_heading2  = {false, 15, "IP Address", &settings_interIOSswitch_heading3};
struct tableHeading settings_interIOSswitch_heading1  = {false, 6, "Active", &settings_interIOSswitch_heading2};
struct tableHeading settings_interIOSswitch_heading   = {false, 15, "Interface", &settings_interIOSswitch_heading1};
struct tableHeading settings_interIOS_heading11 = {false, 4, "MOP", 0};
struct tableHeading settings_interIOS_heading10 = {false, 4, "uRPF", &settings_interIOS_heading11};
struct tableHeading settings_interIOS_heading9  = {false, 4, "CDP", &settings_interIOS_heading10};
struct tableHeading settings_interIOS_heading8  = {false, 4, "NTP", &settings_interIOS_heading9};
struct tableHeading settings_interIOS_heading7  = {false, 11, "IP Direct Broadcast", &settings_interIOS_heading8};
struct tableHeading settings_interIOS_heading6  = {false, 7, "IP Mask Reply", &settings_interIOS_heading7};
struct tableHeading settings_interIOS_heading5  = {false, 6, "IP Redirect", &settings_interIOS_heading6};
struct tableHeading settings_interIOS_heading4  = {false, 10, "IP Unreachable", &settings_interIOS_heading5};
struct tableHeading settings_interIOS_heading3  = {false, 6, "Proxy ARP", &settings_interIOS_heading4};
struct tableHeading settings_interIOS_heading2  = {false, 15, "IP Address", &settings_interIOS_heading3};
struct tableHeading settings_interIOS_heading1  = {false, 6, "Active", &settings_interIOS_heading2};
struct tableHeading settings_interIOS_heading   = {false, 15, "Interface", &settings_interIOS_heading1};
struct tableHeading settings_interSOS_heading12 = {false, 1, "Web", 0};
struct tableHeading settings_interSOS_heading11 = {false, 1, "Telnet", &settings_interSOS_heading12};
struct tableHeading settings_interSOS_heading10 = {false, 1, "SSL", &settings_interSOS_heading11};
struct tableHeading settings_interSOS_heading9  = {false, 1, "SSH", &settings_interSOS_heading10};
struct tableHeading settings_interSOS_heading8  = {false, 1, "SNMP", &settings_interSOS_heading9};
struct tableHeading settings_interSOS_heading7  = {false, 1, "Ping", &settings_interSOS_heading8};
struct tableHeading settings_interSOS_heading6  = {false, 1, "NS Management", &settings_interSOS_heading7};
struct tableHeading settings_interSOS_heading5  = {false, 1, "MTrace", &settings_interSOS_heading6};
struct tableHeading settings_interSOS_heading4  = {false, 1, "Ident Reset", &settings_interSOS_heading5};
struct tableHeading settings_interSOS_heading3  = {false, 3, "Zone", &settings_interSOS_heading4};
struct tableHeading settings_interSOS_heading2  = {false, 3, "IP Address", &settings_interSOS_heading3};
struct tableHeading settings_interSOS_heading1  = {false, 1, "Active", &settings_interSOS_heading2};
struct tableHeading settings_interSOS_heading   = {false, 3, "Interface", &settings_interSOS_heading1};
struct tableHeading settings_interpix_heading8  = {false, 10, "Out ACL", 0};
struct tableHeading settings_interpix_heading7  = {false, 10, "In ACL", &settings_interpix_heading8};
struct tableHeading settings_interpix_heading6  = {false, 5, "uRPF", &settings_interpix_heading7};
struct tableHeading settings_interpix_heading5  = {false, 7, "Security", &settings_interpix_heading6};
struct tableHeading settings_interpix_heading4  = {false, 10, "Net Mask", &settings_interpix_heading5};
struct tableHeading settings_interpix_heading3  = {false, 10, "IP Address", &settings_interpix_heading4};
struct tableHeading settings_interpix_heading2  = {false, 8, "Shutdown", &settings_interpix_heading3};
struct tableHeading settings_interpix_heading1  = {false, 15, "Name", &settings_interpix_heading2};
struct tableHeading settings_interpix_heading   = {false, 11, "Interface", &settings_interpix_heading1};


// Zones
const char *settings_zone_title = "Security Zones";
const char *settings_zone_desc = "*DEVICETYPE* security zones enable the sectioning of a network in order to apply network filtering and other security options. *DEVICETYPE* must have at least two security zones configured in order to facilitate filtering between network areas and each security zone will have at least one network interface bound to it, the global zone will use mapped or virtual *ABBREV*IP*-ABBREV*.";
const char *settings_zones_table = "Security zones";
struct tableHeading settings_zones_heading6  = {false, 2, "Virtual Router", 0};
struct tableHeading settings_zones_heading5  = {false, 2, "Tunnel", &settings_zones_heading6};
struct tableHeading settings_zones_heading4  = {false, 2, "Policy", &settings_zones_heading5};
struct tableHeading settings_zones_heading3  = {false, 1, "Block", &settings_zones_heading4};
struct tableHeading settings_zones_heading2  = {false, 1, "VLAN", &settings_zones_heading3};
struct tableHeading settings_zones_heading1  = {false, 1, "ID", &settings_zones_heading2};
struct tableHeading settings_zones_heading   = {false, 2, "Name", &settings_zones_heading1};
const char *settings_zone_table = "zone security settings";


// Policy Collections (FW1)
const char *settings_policycol_title = "Policy Collections";
const char *settings_policycol_table = "policy collection";
struct tableHeading settings_policycol_heading9 = {false, 3, "Comment", 0};
struct tableHeading settings_policycol_heading8 = {false, 1, "Log", 0};
struct tableHeading settings_policycol_heading7 = {false, 2, "Install On", &settings_policycol_heading8};
struct tableHeading settings_policycol_heading6 = {false, 2, "Through", &settings_policycol_heading7};
struct tableHeading settings_policycol_heading5 = {false, 3, "Service", &settings_policycol_heading6};
struct tableHeading settings_policycol_heading4 = {false, 3, "Destination", &settings_policycol_heading5};
struct tableHeading settings_policycol_heading3 = {false, 3, "Source", &settings_policycol_heading4};
struct tableHeading settings_policycol_heading2 = {false, 1, "Action", &settings_policycol_heading3};
struct tableHeading settings_policycol_heading1 = {false, 1, "Enabled", &settings_policycol_heading2};
struct tableHeading settings_policycol_heading  = {false, 1, "Rule", &settings_policycol_heading1};

// Access Rules/Policies (SonicOS)
const char *settings_accessrules_title = "Firewall Filtering";
struct tableHeading settings_accessrules_heading6 = {false, 1, "Fragments", 0};
struct tableHeading settings_accessrules_heading5 = {false, 3, "Service", &settings_accessrules_heading6};
struct tableHeading settings_accessrules_heading4 = {false, 3, "Destination", &settings_accessrules_heading5};
struct tableHeading settings_accessrules_heading3 = {false, 3, "Source", &settings_accessrules_heading4};
struct tableHeading settings_accessrules_heading2 = {false, 1, "Action", &settings_accessrules_heading3};
struct tableHeading settings_accessrules_heading1 = {false, 1, "Enabled", &settings_accessrules_heading2};
struct tableHeading settings_accessrules_heading  = {false, 1, "Rule", &settings_accessrules_heading1};
struct tableHeading settings_accesspolicy_heading7 = {false, 1, "Log", 0};
struct tableHeading settings_accesspolicy_heading6 = {false, 1, "Fragments", &settings_accesspolicy_heading7};
struct tableHeading settings_accesspolicy_heading5 = {false, 3, "Service", &settings_accesspolicy_heading6};
struct tableHeading settings_accesspolicy_heading4 = {false, 3, "Destination", &settings_accesspolicy_heading5};
struct tableHeading settings_accesspolicy_heading3 = {false, 3, "Source", &settings_accesspolicy_heading4};
struct tableHeading settings_accesspolicy_heading2 = {false, 1, "Action", &settings_accesspolicy_heading3};
struct tableHeading settings_accesspolicy_heading1 = {false, 1, "Enabled", &settings_accesspolicy_heading2};
struct tableHeading settings_accesspolicy_heading  = {false, 1, "Policy", &settings_accesspolicy_heading1};

// Permit Lists (NMP)
const char *settings_permit_title = "Management Service Permit Lists";
const char *settings_permit_table = "Management service permit lists";
struct tableHeading settings_permit_heading1 = {false, 1, "Permission List", 0};
struct tableHeading settings_permit_heading  = {false, 1, "Service", &settings_permit_heading1};
struct tableHeading settings_permitlist_heading1 = {false, 1, "Net Mask", 0};
struct tableHeading settings_permitlist_heading  = {false, 1, "Host", &settings_permitlist_heading1};

// Filters (Passport)
const char *settings_filter_title = "Network Filtering";
const char *settings_filter_table = "Filters not assigned to any filter sets";
struct tableHeading settings_filter_heading9 = {false, 1, "Stop", 0};
struct tableHeading settings_filter_heading8 = {false, 1, "Destination Port", &settings_filter_heading9};
struct tableHeading settings_filter_heading7 = {false, 2, "Destination", &settings_filter_heading8};
struct tableHeading settings_filter_heading6 = {false, 1, "Source Port", &settings_filter_heading7};
struct tableHeading settings_filter_heading5 = {false, 2, "Source", &settings_filter_heading6};
struct tableHeading settings_filter_heading4 = {false, 1, "Protocol", &settings_filter_heading5};
struct tableHeading settings_filter_heading3 = {false, 1, "Action", &settings_filter_heading4};
struct tableHeading settings_filter_heading2 = {false, 1, "Type", &settings_filter_heading3};
struct tableHeading settings_filter_heading1 = {false, 1, "Name", &settings_filter_heading2};
struct tableHeading settings_filter_heading  = {false, 1, "ID", &settings_filter_heading1};
struct tableHeading settings_filterset_heading8 = {false, 1, "Stop", 0};
struct tableHeading settings_filterset_heading7 = {false, 1, "Destination Port", &settings_filterset_heading8};
struct tableHeading settings_filterset_heading6 = {false, 2, "Destination", &settings_filterset_heading7};
struct tableHeading settings_filterset_heading5 = {false, 1, "Source Port", &settings_filterset_heading6};
struct tableHeading settings_filterset_heading4 = {false, 2, "Source", &settings_filterset_heading5};
struct tableHeading settings_filterset_heading3 = {false, 1, "Protocol", &settings_filterset_heading4};
struct tableHeading settings_filterset_heading2 = {false, 1, "Action", &settings_filterset_heading3};
struct tableHeading settings_filterset_heading1 = {false, 1, "Name", &settings_filterset_heading2};
struct tableHeading settings_filterset_heading  = {false, 1, "ID", &settings_filterset_heading1};

// Policies (ScreenOS Firewall Rules)
const char *settings_policies_title = "Policy Lists";
const char *settings_policies_text = "A policy is a set of rules that will determine whether traffic between security zones (interzone), between interfaces in the same zone (intrazone) or between addresses in the global zone are permitted or denied. Each interface can be assigned to a different security zone, and multiple interfaces can be assigned to a single security zone.*NEWPARA*The policy will be processed from the top to the bottom with the first policy rule that applies taking effect. If no rule matches, the default policy will take effect, which is set to deny by default on *DEVICETYPE*. Policies are applied in the following order:";
struct tableHeading settings_sospolicy_heading3  = {false, 1, "Default policy (deny by default)", 0};
struct tableHeading settings_sospolicy_heading2  = {false, 1, "Global zone policy", &settings_sospolicy_heading3};
struct tableHeading settings_sospolicy_heading1  = {false, 1, "Zone to zone policies", &settings_sospolicy_heading2};
struct tableHeading settings_sospolicy_heading   = {false, 1, "Intrazone policies (does nothing unless block intrazone traffic is enabled on the zone)", &settings_sospolicy_heading1};
struct tableHeading settings_policies_heading6  = {false, 1, "Log", 0};
struct tableHeading settings_policies_heading5  = {false, 3, "Service", &settings_policies_heading6};
struct tableHeading settings_policies_heading4  = {false, 3, "Destination", &settings_policies_heading5};
struct tableHeading settings_policies_heading3  = {false, 3, "Source", &settings_policies_heading4};
struct tableHeading settings_policies_heading2  = {false, 1, "Permission", &settings_policies_heading3};
struct tableHeading settings_policies_heading1  = {false, 1, "Disabled", &settings_policies_heading2};
struct tableHeading settings_policies_heading   = {false, 1, "ID", &settings_policies_heading1};

// Access Lists
const char *settings_accesslists_title = "Access Control List";
const char *settings_accesslist_table = "General ACL settings";
const char *settings_accesslist_css = "*DEVICETYPE* device *ABBREV*ACL*-ABBREV* are sequential lists of permit, deny or bypass clauses that are applied to a VLAN circuit. An *ABBREV*ACL*-ABBREV* is processed sequentially with the first clause that matches the incoming traffic applying. If the entire *ABBREV*ACL*-ABBREV* has been processed without a clause matching, then the traffic is denied by a hidden deny all rule. However, *ABBREV*ACL*-ABBREV* have to be enabled on *DEVICETYPE* otherwise all traffic will be permitted regardless of the *ABBREV*ACL*-ABBREV*. Once enabled, any VLAN circuits without an ACL applied will be denied by the hidden deny all rule.*NEWPARA*ACL are *NEGATIVE*disabled*-NEGATIVE**POSITIVE*enabled*-POSITIVE* on *DEVICENAME*.";
const char *settings_accesslists1 = "A Cisco *ABBREV*ACL*-ABBREV* is a sequential list of apply or deny *ABBREV*ACEs*-ABBREV* that a Cisco device will apply to network traffic. The Cisco device will check network traffic against the *ABBREV*ACL*-ABBREV* and the first *ABBREV*ACE*-ABBREV* match will determine whether the packet is accepted or rejected. If the Cisco device does not have an *ABBREV*ACE*-ABBREV* that applies then the packet is denied. *NONEWPARA*";
const char *settings_accesslists2 = "*NOTEXTSTART*When a packet is rejected after access list processing, an *ABBREV*ICMP*-ABBREV* host unreachable message is sent, unless it had been disabled.*NEWPARA*There are two different types of *ABBREV*ACLs*-ABBREV* on IOS-based Cisco devices, standard and extended. Standard *ABBREV*ACLs*-ABBREV* have an access list number between 1 and 99, extended *ABBREV*ACLs*-ABBREV* are numbered 100 or above. Standard *ABBREV*ACLs*-ABBREV* only define the source address and process the packet solely based on that. Extended *ABBREV*ACLs*-ABBREV* contain additional checks, such as destination address and network port numbers.";
const char *settings_accesslists3 = "Newer versions of Cisco firewall devices have two different types of *ABBREV*ACL*-ABBREV*, standard and extended. Standard *ABBREV*ACL*-ABBREV* are typically used to secure *ABBREV*OSPF*-ABBREV* routes, whilst extended *ABBREV*ACL*-ABBREV* are used for all other network filtering.";
const char *settings_acl_int_table = "Interfaces with ACL applied";
struct tableHeading settings_aclinter_heading4  = {false, 1, "Out ACL", 0};
struct tableHeading settings_aclinter_heading3  = {false, 1, "In ACL", &settings_aclinter_heading4};
struct tableHeading settings_aclinter_heading2  = {false, 3, "IP Address", &settings_aclinter_heading3};
struct tableHeading settings_aclinter_heading1  = {false, 1, "Active", &settings_aclinter_heading2};
struct tableHeading settings_aclinter_heading   = {false, 2, "Interface", &settings_aclinter_heading1};
const char *settings_acl_line_table = "Lines with ACL applied";
struct tableHeading settings_aclline_heading8  = {false, 1, "ACL Out", 0};
struct tableHeading settings_aclline_heading7  = {false, 1, "ACL In", &settings_aclline_heading8};
struct tableHeading settings_aclline_heading6  = {false, 1, "SSH", &settings_aclline_heading7};
struct tableHeading settings_aclline_heading5  = {false, 1, "Telnet", &settings_aclline_heading6};
struct tableHeading settings_aclline_heading4  = {false, 1, "Exec", &settings_aclline_heading5};
struct tableHeading settings_aclline_heading3  = {false, 2, "Logins", &settings_aclline_heading4};
struct tableHeading settings_aclline_heading2  = {false, 2, "End Line", &settings_aclline_heading3};
struct tableHeading settings_aclline_heading1  = {false, 2, "Start Line", &settings_aclline_heading2};
struct tableHeading settings_aclline_heading   = {false, 2, "Line Type", &settings_aclline_heading1};
struct tableHeading settings_acl_css_heading7  = {false, 1, "Log", 0};
struct tableHeading settings_acl_css_heading6  = {false, 3, "Destination Service", &settings_acl_css_heading7};
struct tableHeading settings_acl_css_heading5  = {false, 3, "Destination", &settings_acl_css_heading6};
struct tableHeading settings_acl_css_heading4  = {false, 3, "Source Service", &settings_acl_css_heading5};
struct tableHeading settings_acl_css_heading3  = {false, 3, "Source", &settings_acl_css_heading4};
struct tableHeading settings_acl_css_heading2  = {false, 1, "Protocol", &settings_acl_css_heading3};
struct tableHeading settings_acl_css_heading1  = {false, 1, "Filter", &settings_acl_css_heading2};
struct tableHeading settings_acl_css_heading   = {false, 1, "Clause", &settings_acl_css_heading1};
const char *settings_accessstd_table = "Standard ACL";
struct tableHeading settings_accessstd_heading3  = {false, 1, "Log", 0};
struct tableHeading settings_accessstd_heading2  = {false, 5, "Source", &settings_accessstd_heading3};
struct tableHeading settings_accessstd_heading1  = {false, 2, "Filter", &settings_accessstd_heading2};
struct tableHeading settings_accessstd_heading   = {false, 1, "Line", &settings_accessstd_heading1};
struct tableHeading settings_accessstdpix_heading2  = {false, 2, "Source", 0};
struct tableHeading settings_accessstdpix_heading1  = {false, 2, "Permission", &settings_accessstdpix_heading2};
struct tableHeading settings_accessstdpix_heading   = {false, 1, "Line", &settings_accessstdpix_heading1};
const char *settings_accesslists_table = "ACL";
struct tableHeading settings_accesspix_heading6  = {false, 1, "Destination Port", 0};
struct tableHeading settings_accesspix_heading5  = {false, 2, "Destination", &settings_accesspix_heading6};
struct tableHeading settings_accesspix_heading4  = {false, 1, "Source Port", &settings_accesspix_heading5};
struct tableHeading settings_accesspix_heading3  = {false, 2, "Source", &settings_accesspix_heading4};
struct tableHeading settings_accesspix_heading2  = {false, 1, "Protocol", &settings_accesspix_heading3};
struct tableHeading settings_accesspix_heading1  = {false, 1, "Permission", &settings_accesspix_heading2};
struct tableHeading settings_accesspix_heading   = {false, 1, "Line", &settings_accesspix_heading1};
const char *settings_accessext_table = "Extended ACL";
struct tableHeading settings_accessext_heading8  = {false, 11, "Options", 0};
struct tableHeading settings_accessext_heading7  = {false, 8, "Log", &settings_accessext_heading8};
struct tableHeading settings_accessext_heading6  = {false, 11, "Destination Service", &settings_accessext_heading7};
struct tableHeading settings_accessext_heading5  = {false, 17, "Destination", &settings_accessext_heading6};
struct tableHeading settings_accessext_heading4  = {false, 11, "Source Service", &settings_accessext_heading5};
struct tableHeading settings_accessext_heading3  = {false, 17, "Source", &settings_accessext_heading4};
struct tableHeading settings_accessext_heading2  = {false, 8, "Protocol", &settings_accessext_heading3};
struct tableHeading settings_accessext_heading1  = {false, 9, "Filter", &settings_accessext_heading2};
struct tableHeading settings_accessext_heading   = {false, 8, "Line", &settings_accessext_heading1};
struct tableHeading settings_accessextpix_heading8  = {false, 1, "Active", 0};
struct tableHeading settings_accessextpix_heading7  = {false, 1, "Log", &settings_accessextpix_heading8};
struct tableHeading settings_accessextpix_heading6  = {false, 1, "Destination Port", &settings_accessextpix_heading7};
struct tableHeading settings_accessextpix_heading5  = {false, 1, "Destination", &settings_accessextpix_heading6};
struct tableHeading settings_accessextpix_heading4  = {false, 1, "Source Port", &settings_accessextpix_heading5};
struct tableHeading settings_accessextpix_heading3  = {false, 1, "Source", &settings_accessextpix_heading4};
struct tableHeading settings_accessextpix_heading2  = {false, 1, "Protocol", &settings_accessextpix_heading3};
struct tableHeading settings_accessextpix_heading1  = {false, 1, "Permission", &settings_accessextpix_heading2};
struct tableHeading settings_accessextpix_heading   = {false, 1, "Line", &settings_accessextpix_heading1};

// ICMP Access
const char *settings_icmpaccess_title = "ICMP Access";
const char *settings_icmpaccess_table = "Configured security appliance ICMP restrictions";
struct tableHeading settings_icmpaccess_heading3 = {false, 1, "Interface", 0};
struct tableHeading settings_icmpaccess_heading2 = {false, 1, "ICMP Message", &settings_icmpaccess_heading3};
struct tableHeading settings_icmpaccess_heading1 = {false, 1, "Source", &settings_icmpaccess_heading2};
struct tableHeading settings_icmpaccess_heading  = {false, 1, "Action", &settings_icmpaccess_heading1};
const char *settings_icmpaccess_desc = "The default behavior of Cisco security appliances is to allow *ABBREV*ICMP*-ABBREV* packets to the security appliances interfaces, with the exception of broadcast *ABBREV*ICMP*-ABBREV* packets. Likewise *ABBREV*ICMP*-ABBREV* packets from an outside address to a protected interface will also be denied. However, it is possible to configure additional filtering to restrict other *ABBREV*ICMP*-ABBREV* traffic to the security appliance.";

// Protocol Inspection - fixup (old pix), inspect (new pix)
const char *settings_protoinspect_title = "Protocol Inspection";
const char *settings_protoinspect_desc = "Cisco firewall devices are capable of inspecting protocol traffic such as *ABBREV*DNS*-ABBREV*, *ABBREV*HTTP*-ABBREV* and *ABBREV*SMTP*-ABBREV*. This allows traffic to be filtered based on the protocol and can prevent a number of attacks. For example, the *ABBREV*SMTP*-ABBREV* filter can prevent certain *ABBREV*SMTP*-ABBREV* commands from being executed.";
const char *settings_protoinspect_table = "Protocols inspected";
struct tableHeading settings_protoinspect_heading2 = {false, 1, "Option", 0};
struct tableHeading settings_protoinspect_heading1 = {false, 1, "Inspect", &settings_protoinspect_heading2};
struct tableHeading settings_protoinspect_heading  = {false, 1, "Protocol", &settings_protoinspect_heading1};

// Gateway Cluster Objects (FW1)...
const char *settings_objects_gatewaycluster_title = "Gateway Cluster Definitions";
const char *settings_objects_gatewaycluster_table = "gateway cluster configuration";
const char *settings_objects_gatewaycluster_int_table = "gateway cluster interfaces";
const char *settings_objects_gatewaycluster_mem_table = "gateway cluster members";
struct tableHeading settings_object_gatemem_heading1 = {false, 1, "Name", 0};
struct tableHeading settings_object_gatemem_heading  = {false, 1, "Member", &settings_object_gatemem_heading1};

// Gateway Cluster Member Objects (FW1)...
const char *settings_objects_gatewayclustermem_title = "Gateways Cluster Member Definitions";
const char *settings_objects_gatewayclustermem_table = "gateway cluster member configuration";
const char *settings_objects_gatewayclustermem_int_table = "gateway cluster member interfaces";

// Gateway Objects (FW1)...
const char *settings_objects_gateway_title = "Gateways Definitions";
const char *settings_objects_gateway_table = "gateway configuration";
const char *settings_objects_gateway_int_table = "gateway interfaces";
struct tableHeading settings_object_gateinter_heading4 = {false, 1, "Net Mask", 0};
struct tableHeading settings_object_gateinter_heading3 = {false, 1, "IP Address", &settings_object_gateinter_heading4};
struct tableHeading settings_object_gateinter_heading2 = {false, 1, "Dynamic IP", &settings_object_gateinter_heading3};
struct tableHeading settings_object_gateinter_heading1 = {false, 1, "Name", &settings_object_gateinter_heading2};
struct tableHeading settings_object_gateinter_heading  = {false, 1, "Interface", &settings_object_gateinter_heading1};

// Host Objects (FW1)...
const char *settings_objects_hosts_title = "Host Definitions";
const char *settings_objects_hosts_table = "Host definitions";
struct tableHeading settings_object_host_heading2 = {false, 1, "Managed", 0};
struct tableHeading settings_object_host_heading1 = {false, 1, "IP Address", &settings_object_host_heading2};
struct tableHeading settings_object_host_heading  = {false, 1, "Host Name", &settings_object_host_heading1};

// Network Objects (FW1)...
const char *settings_objects_network_title = "Network Definitions";
const char *settings_objects_network_table = "Network object definitions";
struct tableHeading settings_object_network_heading3 = {false, 1, "Managed", 0};
struct tableHeading settings_object_network_heading2 = {false, 1, "Net Mask", &settings_object_network_heading3};
struct tableHeading settings_object_network_heading1 = {false, 1, "IP Address", &settings_object_network_heading2};
struct tableHeading settings_object_network_heading  = {false, 1, "Network Name", &settings_object_network_heading1};

// Dynamic Network Objects (FW1)...
const char *settings_objects_dynnet_title = "Dynamic Network Definitions";
const char *settings_objects_dynamicnet_table = "Dynamic network object definitions";
struct tableHeading settings_object_dynamicnet_heading  = {false, 1, "Name", 0};

// Group Objects (FW1)...
const char *settings_objects_groups_title = "Group Object Definitions";
const char *settings_objects_group_table = "object group";
struct tableHeading settings_object_group_heading4 = {false, 1, "Managed", 0};
struct tableHeading settings_object_group_heading3 = {false, 1, "Net Mask", &settings_object_group_heading4};
struct tableHeading settings_object_group_heading2 = {false, 1, "IP Address", &settings_object_group_heading3};
struct tableHeading settings_object_group_heading1 = {false, 1, "Object Type", &settings_object_group_heading2};
struct tableHeading settings_object_group_heading  = {false, 1, "Name", &settings_object_group_heading1};

// Machines Range Objects (FW1)...
const char *settings_objects_machrange_title = "Machines Range Definitions";
const char *settings_objects_machrange_table = "Machines range definitions";
struct tableHeading settings_object_machrange_heading2 = {false, 1, "Last IP", 0};
struct tableHeading settings_object_machrange_heading1 = {false, 1, "First IP", &settings_object_machrange_heading2};
struct tableHeading settings_object_machrange_heading  = {false, 1, "Range Name", &settings_object_machrange_heading1};

// Objects...
const char *settings_objects_title = "Object Groups";
const char *settings_objects_desc = "Cisco object groups can be used to group items such as *ABBREV*IP*-ABBREV* addresses, services and protocols. Object groups can be used with any Cisco security appliance command and the command will be effective for all members of the group, this can significantly simplify the devices configuration. Furthermore, object groups can be members or other object groups. There are different types of object group:";
struct tableHeading settings_objects_heading3 = {false, 0, "ICMP Types", 0};
struct tableHeading settings_objects_heading2 = {false, 0, "Networks", &settings_objects_heading3};
struct tableHeading settings_objects_heading1 = {false, 0, "Protocols", &settings_objects_heading2};
struct tableHeading settings_objects_heading  = {false, 0, "Services", &settings_objects_heading1};
const char *settings_objects_table = "object group";
struct tableHeading settings_object_heading1 = {false, 1, "Object", 0};
struct tableHeading settings_object_heading  = {false, 1, "Object Type", &settings_object_heading1};

// Services (SonicOS)...
const char *settings_sonicosservices_title = "Service Definitions";
const char *settings_sonicosservices_table = "Service definitions";
struct tableHeading settings_sonicosservices_heading3 = {false, 0, "IP Type", 0};
struct tableHeading settings_sonicosservices_heading2 = {false, 0, "Port(s)", &settings_sonicosservices_heading3};
struct tableHeading settings_sonicosservices_heading1 = {false, 0, "Name", &settings_sonicosservices_heading2};
struct tableHeading settings_sonicosservices_heading  = {false, 0, "ID", &settings_sonicosservices_heading1};

// Service Groups (FW1)...
const char *settings_fw1servicegroup_title = "Service Groups";
const char *settings_fw1servicegroup_table = "service group";
struct tableHeading settings_fw1servicegroup_heading  = {false, 0, "Name", 0};

// Services (FW1)...
const char *settings_fw1services_title = "Services";
struct tableHeading settings_fw1services_heading3 = {false, 0, "Comments", 0};
struct tableHeading settings_fw1services_heading2 = {false, 0, "Port", &settings_fw1services_heading3};
struct tableHeading settings_fw1services_heading1 = {false, 0, "Protocol", &settings_fw1services_heading2};
struct tableHeading settings_fw1services_heading  = {false, 0, "Service", &settings_fw1services_heading1};

// Address / Name Mappings
const char *settings_namemap_title = "IP Address Name Mappings";
const char *settings_namegroupmap_title = "IP Address Name Mapping Groups";
struct tableHeading settings_namemapgroup_heading1 = {false, 1, "Mapping Name", 0};
struct tableHeading settings_namemapgroup_heading  = {false, 1, "Group Name", &settings_namemapgroup_heading1};
const char *settings_namemap_table = "IP address name mappings";
struct tableHeading settings_namemap_heading1 = {false, 1, "IP Address", 0};
struct tableHeading settings_namemap_heading  = {false, 1, "Name", &settings_namemap_heading1};
struct tableHeading settings_namemapSOS_heading3 = {false, 1, "Comment", 0};
struct tableHeading settings_namemapSOS_heading2 = {false, 1, "Net Mask", &settings_namemapSOS_heading3};
struct tableHeading settings_namemapSOS_heading1 = {false, 1, "IP Address / FQDN", &settings_namemapSOS_heading2};
struct tableHeading settings_namemapSOS_heading  = {false, 1, "Name", &settings_namemapSOS_heading1};


// ----------------------------------------------------------------------------------
// Appendix Text...

const char *appendix_title = "Appendix";

// Abbreviations
const char *appendix_abbrev_title = "Abbreviations";

// Common Ports
const char *appendix_ports_title = "Common Ports";
const char *appendix_ports_table = "Common ports";
struct tableHeading appendix_ports_heading1 = {false, 1, "Port", 0};
struct tableHeading appendix_ports_heading  = {false, 2, "Service", &appendix_ports_heading1};

// Logging Levels
const char *appendix_logging_title = "Logging Severity Levels";
const char *appendix_logging_table = "Logging message severity levels";
struct tableHeading appendix_logging_heading2 = {false, 3, "Description", 0};
struct tableHeading appendix_logging_heading1 = {false, 2, "Level Name", &appendix_logging_heading2};
struct tableHeading appendix_logging_heading  = {false, 1, "Level", &appendix_logging_heading1};

// Time Zones
const char *appendix_timezones_title = "Time Zones";
const char *appendix_timezones_table = "Common time zone acronyms";
struct tableHeading appendix_timezones_heading3 = {false, 1, "UTC Offset", 0};
struct tableHeading appendix_timezones_heading2 = {false, 4, "Time Zone", &appendix_timezones_heading3};
struct tableHeading appendix_timezones_heading1 = {false, 1, "Acronym", &appendix_timezones_heading2};
struct tableHeading appendix_timezones_heading  = {false, 2, "Region", &appendix_timezones_heading1};

// Nipper Version
const char *appendix_version_title = "Nipper Details";
const char *appendix_version_desc1 = "This report was generated using Nipper version *NONEWPARA*";
const char *appendix_version_desc2 = "*NOTEXTSTART*. Nipper is an Open Source tool designed to assist security professionals and network system administrators securely configure network infrastructure devices. The latest version of Nipper can be found at the following URL:*NEWPARA*http://nipper.titania.co.uk.";


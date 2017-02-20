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

// This file contains all the code for the on-line help system...


void showHelp(int argc, char *argv[], struct nipperConfig *nipper)
{
	// Program banner...
	printf("%s%s\n%s", COL_BLUE, program_banner, RESET);

	switch (nipper->helpMode)
	{
		// General Help...
		case help_general:
			printf("Nipper is a  Network Infrastructure  Configuration Parser.  Nipper takes\n");
			printf("a network infrastructure  device configuration,  processes the  file and\n");
			printf("details security-related  issues with detailed  recommendations.  Nipper\n");
			printf("was previous known as CiscoParse.\n\n");
			printf("By default, input is retrieved from stdin and is output (in HTML format)\n");
			printf("to stdout.\n\n");

			printf("%sCommand:%s\n", COL_BLUE, RESET);
			printf("    %s%s [Options]%s\n\n", COL_GREEN, argv[0], RESET);

			printf("%sGeneral Options:%s\n", COL_BLUE, RESET);
			printf("    %s--input=<file>%s\n", COL_GREEN, RESET);
			printf("    Specifies a  device configuration  file to  process.  For CheckPoint\n");
			printf("    Firewall-1 configurations, the input should be the conf directory.\n\n");
			printf("    %s--output=<file> | --report=<file>%s\n", COL_GREEN, RESET);
			printf("    Specified an output file for the report.\n\n");
			printf("    %s--csv=<file>%s\n", COL_GREEN, RESET);
			printf("    Want to output the network filtering configuration to a CSV file?.\n\n");
			printf("    %s--version%s\n", COL_GREEN, RESET);
			printf("    Displays the program version.\n\n");

			printf("%sExample:%s\n", COL_BLUE, RESET);
			printf("    The  example   below  will   process  a   Cisco   IOS-based   router\n");
			printf("    configuration file called ios.conf  and output  the report to a file\n");
			printf("    called report.html.\n\n");
			printf("    %s%s --ios-router --input=ios.conf --output=report.html%s\n\n", COL_GREEN, argv[0], RESET);
			break;
			
		// Device Types...
		case help_device_types:
			printf("Nipper supports  a  number of  different types  of network device.  This\n");
			printf("version contains support for the following devices:\n\n");
			printf("    CMD Option      Device Type\n");
			printf("    =================================================\n");
			printf("    --ios-switch    Cisco IOS-based Switch\n");
			printf("    --ios-router    Cisco IOS-based Router (default)\n");
			printf("    --ios-catalyst  Cisco IOS-based Catalyst\n");
			printf("    --pix           Cisco PIX-based Firewall\n");
			printf("    --asa           Cisco ASA-based Firewall\n");
			printf("    --fwsm          Cisco FWSM-based Router\n");
			printf("    --catos         Cisco CatOS-based Catalyst\n");
			printf("    --nmp           Cisco NMP-based Catalyst\n");
			printf("    --css           Cisco Content Services Switch\n");
			printf("    --screenos      Juniper NetScreen Firewall\n");
			printf("    --passport      Nortel Passport Device\n");
			printf("    --sonicos       SonicWall SonicOS Firewall\n");
			printf("    --fw1           CheckPoint Firewall-1 Firewall\n");
			printf("    --nokiaip       Nokia IP Firewall\n");
			printf("    --accelar       Bay Networks Accelar\n\n");
			printf("Please note that the level of support for each type of device varies.\n\n");
			break;

		// Device Usage...
		case help_device_usage:
			printf("Nipper performs  various  checks to  ensure that  the device  type that\n");
			printf("has been  specified matches the  configuration file.  Additionally, the\n");
			printf("security issues  reported by Nipper  can depend  on what  the device is\n");
			printf("used for.\n\n");
			printf("%sAdvanced Device Options:%s\n\n", COL_BLUE, RESET);
			printf("    %s--force%s\n", COL_GREEN, RESET);
			printf("    Force Nipper to bypass any configuration type checks.\n\n");
			printf("    %s--location=<edge | internal>%s\n", COL_GREEN, RESET);
			printf("    Where is the device located.\n\n");
			printf("    %s--model=<device model>%s\n", COL_GREEN, RESET);
			printf("    Specify a device model, such as 7200VXR for a Cisco 7200VXR.\n\n");
			break;

		// Report Formats...
		case help_report_formats:
			printf("Nipper supports a number of different report formats. They are:\n\n");
			printf("    CMD Option      Report Format\n");
			printf("    =============================\n");
			printf("    --html          HTML (default)\n");
			printf("    --latex         Latex\n");
			printf("    --text          Text\n");
			printf("    --xml           XML\n\n");
			break;

		// Advanced Report Options...
		case help_report_options:
			printf("These reporting options apply to all report output.\n\n");
			printf("    %s--company-name=<name>%s\n", COL_GREEN, RESET);
			printf("    Replace the 'nipper recommends...' in the report output to something\n");
			printf("    else. So for the Acme company, it would read, 'Acme recommends...'.\n\n");
			printf("    %s--device-name=<name>%s\n", COL_GREEN, RESET);
			printf("    If a device configuration  file does not  contain a device name,  it\n");
			printf("    can be specified using this option.\n\n");
			printf("    %s--no-names%s\n", COL_GREEN, RESET);
			printf("    Convert host and network names to IP addresses where possible.\n\n");
			printf("    %s--rule-comments%s\n", COL_GREEN, RESET);
			printf("    Shows CheckPoint rule comments in the rules output.\n\n");
			printf("    %s--expand-acl%s\n", COL_GREEN, RESET);
			printf("    Expand an Access Control Lists / Filtering  object definitions. This\n");
			printf("    option will show the reality of a filtering policy.\n\n");
			break;

		// Report Options to include report sections...
		case help_report_appendix:
			printf("The following  report options  determine which sections  are included in\n");
			printf("the report output. The default is to include all sections.\n\n");
			printf("    %s--no-config%s\n", COL_GREEN, RESET);
			printf("    This option disables the configuration report section.\n\n");
			printf("    %s--no-audit%s\n", COL_GREEN, RESET);
			printf("    This option disables the security audit of the device configuration.\n\n");
			printf("    %s--no-appendix%s\n", COL_GREEN, RESET);
			printf("    Disables  the output  of  the entire  report  appendix  section.  By\n");
			printf("    default an appendix section is generated and added to the report.\n\n");
			printf("    %s--no-abbreviations%s\n", COL_GREEN, RESET);
			printf("    Disables the output of an abbreviations section in the appendix.\n\n");
			//printf("    %s--no-glossary%s\n", COL_GREEN, RESET);
			//printf("    Disables the output of a glossary section in the appendix.\n\n");
			printf("    %s--no-logging%s\n", COL_GREEN, RESET);
			printf("    Disables the output of the logging levels section in the appendix.\n\n");
			printf("    %s--no-timezones%s\n", COL_GREEN, RESET);
			printf("    Disables the output of the time zones section in the appendix.\n\n");
			printf("    %s--no-ports%s\n", COL_GREEN, RESET);
			printf("    Disables the output of a common ports section in the appendix.\n\n");
			printf("    %s--no-version%s\n", COL_GREEN, RESET);
			printf("    Disables the output of the nipper version section in the appendix.\n\n");
			break;

		// Report HTML options...
		case help_report_html:
			printf("These report options apply only to the HTML report file format.\n\n");
			printf("    %s--stylesheet=<file>%s\n", COL_GREEN, RESET);
			printf("    Supply an external Cascading Style Sheet (CSS) for use with the HTML\n");
			printf("    -based reports.  If this  option is not  supplied a  default  CSS is\n");
			printf("    embeded. The  supplied CSS  file will be  embeded within  the report\n");
			printf("    output.\n\n");
			break;

		// Report Latex Options...
		case help_report_latex:
			printf("These report options apply only to the Latex report file format.\n\n");
			printf("    %s--paper=<Latex paper size>%s\n", COL_GREEN, RESET);
			printf("    This option can be used to configure the Latex document  paper size.\n");
			printf("    The   default  paper   size  is  '%s'.   Refer  to   the  Latex\n", nipper->paperSize);
			printf("    documentation for other settings.\n\n");
			printf("    %s--documentclass=<Latex document class>%s\n", COL_GREEN, RESET);
			printf("    This option can be used to configure  the Latex document  class. The\n");
			printf("    default  document  class   is   '%s'.   Refer   to   the  Latex\n", nipper->documentClass);
			printf("    documentation for other settings.\n\n");
			break;

		// Security Auditing ACL options...
		case help_audit_acl:
			printf("These  options  only apply  to the  security  auditing  of  the  network\n");
			printf("filtering.  Checks for logging on all rules   and for any source service\n");
			printf("are disabled by default, all other rules are enabled by default.\n\n");
			printf("    %s--deny-log | --no-deny-log%s\n", COL_GREEN, RESET);
			printf("    Enable/Disable checks to ensure that  the rule lists end with a deny\n");
			printf("    all and log.\n\n");
			printf("    %s--any-source | --no-any-source%s\n", COL_GREEN, RESET);
			printf("    Enable/Disable rule checks for any source.\n\n");
			printf("    %s--network-source | --no-network-source%s\n", COL_GREEN, RESET);
			printf("    Enable/Disable rule checks for network sources.\n\n");
			printf("    %s--source-service | --no-source-service%s\n", COL_GREEN, RESET);
			printf("    Enable/Disable checks for any sources services.\n\n");
			printf("    %s--any-destination | --no-any-destination%s\n", COL_GREEN, RESET);
			printf("    Enable/Disable rule checks for any destination.\n\n");
			printf("    %s--network-destination | --no-network-destination%s\n", COL_GREEN, RESET);
			printf("    Enable/Disable rule checks for network destionations.\n\n");
			printf("    %s--destination-service | --no-destination-service%s\n", COL_GREEN, RESET);
			printf("    Enable/Disable rule checks for any destination service.\n\n");
			printf("    %s--log-rules | --no-log-rules%s\n", COL_GREEN, RESET);
			printf("    Enable/Disable checks for logging on all rules.\n\n");
			printf("    %s--disabled-rules | --no-disabled-rules%s\n", COL_GREEN, RESET);
			printf("    Enable/Disable checks for disabled rules.\n\n");
			printf("    %s--reject-rules | --no-reject-rules%s\n", COL_GREEN, RESET);
			printf("    Enable/Disable checks for reject rules.\n\n");
			printf("    %s--bypass-rules | --no-bypass-rules%s\n", COL_GREEN, RESET);
			printf("    Enable/Disable checks for bypass rules.\n\n");
			printf("    %s--default-rules | --no-default-rules%s\n", COL_GREEN, RESET);
			printf("    Enable/Disable checks for default rules.\n\n");
			printf("    %s--log-deny-rules | --no-log-deny-rules%s\n", COL_GREEN, RESET);
			printf("    Enable/Disable checks for deny and log rules.\n\n");
			break;

		// Security Auditing Password Options...
		case help_audit_password:
			printf("These options  apply to the  password security auditing.  In addition to\n");
			printf("user passwords,  other authentication strings are audited such as shared\n");
			printf("keys and SNMP community strings.\n\n");
			printf("    %s--no-passwords%s\n", COL_GREEN, RESET);
			printf("    Removes passwords  from the  output. However,  passwords are  always\n");
			printf("    checked against defaults and for password strength.\n\n");
			printf("    %s--john=<file>%s\n", COL_GREEN, RESET);
			printf("    Output the Cisco type 5  passwords in a  file that  can then  be run\n");
			printf("    through john-the-ripper.\n\n");
			printf("    %s--dictionary=<file>%s\n", COL_GREEN, RESET);
			printf("    Use a dictionary  file to  check the  passwords  and  keys  are  not\n");
			printf("    dictionary-based  words.  If this  option is  not specified  a small\n");
			printf("    number of  built-in  passwords  are  used  instead.  This option  is\n");
			printf("    not used  to break  MD5 passwords,  only compare  passwords  already\n");
			printf("    known.\n\n");
			printf("    %s--pass-length=<length>%s\n", COL_GREEN, RESET);
			printf("    Password strength  checks will check  that retrieved  passwords have\n");
			printf("    a minimum length as specified. The default is %d characters.\n\n", nipper->passwordLength);
			printf("    %s--pass-uppers=<yes|no>%s\n", COL_GREEN, RESET);
			printf("    Password strength  checks will check  that retrieved  passwords must\n");
			printf("    include uppercase characters. The default is ");
			if (nipper->passwordUppers == false)
				printf("no.\n\n");
			else
				printf("yes.\n\n");
			printf("    %s--pass-lowers=<yes|no>%s\n", COL_GREEN, RESET);
			printf("    Password strength  checks will check  that retrieved  passwords must\n");
			printf("    include lowercase characters. The default is ");
			if (nipper->passwordLowers == false)
				printf("no.\n\n");
			else
				printf("yes.\n\n");
			printf("    %s--pass-either=<yes|no>%s\n", COL_GREEN, RESET);
			printf("    Password strength  checks will check  that retrieved  passwords must\n");
			printf("    include upper or lowercase characters. The default is ");
			if (nipper->passwordEither == false)
				printf("no.\n\n");
			else
				printf("yes.\n\n");
			printf("    %s--pass-numbers=<yes|no>%s\n", COL_GREEN, RESET);
			printf("    Password strength  checks will check  that retrieved  passwords must\n");
			printf("    include numbers. The default is ");
			if (nipper->passwordNumbers == false)
				printf("no.\n\n");
			else
				printf("yes.\n\n");
			printf("    %s--pass-specials=<yes|no>%s\n", COL_GREEN, RESET);
			printf("    Password strength  checks will check  that retrieved  passwords must\n");
			printf("    include special characters. The default is ");
			if (nipper->passwordSpecials == false)
				printf("no.\n\n");
			else
				printf("yes.\n\n");
			break;

		// Other Security Auditing Options...
		case help_audit_misc:
			printf("These options apply to the security auditing.\n\n");
			printf("    %s--timeout=<seconds>%s\n", COL_GREEN, RESET);
			printf("    Specify the  number of  seconds that  connection timeouts  should be\n");
			printf("    less than or equal to.  If timeouts are  less than this,  a security\n");
			printf("    will be generated in the report. The default is %d minutes.\n\n", (nipper->connectionTimeout / 60));
			break;

#if !defined(__WIN32__)
		// Other SNMP Options...
		case help_snmp:
			printf("These  options apply  to remote  SNMP configuration retrival from  Cisco\n");
			printf("devices.  Older Cisco devices make  use of a  slightly different method.\n");
			printf("The old method works with IOS devices up to version 12.x.  Newer methods\n");
			printf("are supported with IOS version 12.0  (some with 11.2P).  This requires a\n");
			printf("local TFTP server and the snmpget command.\n\n");
			printf("    %s--cisco-ip=<ip address>%s\n", COL_GREEN, RESET);
			printf("    Specify the  IP address  of the Cisco Device  to retrieve the config\n");
			printf("    from.\n\n");
			printf("    %s--local-ip=<ip address>%s\n", COL_GREEN, RESET);
			printf("    The IP address of the host making the request. This is essential for\n");
			printf("    remote config retrival, else it will fail.\n\n");
			printf("    %s--cisco=<old | new>%s\n", COL_GREEN, RESET);
			printf("    There are two methods of retrieving  the config remotely using SNMP.\n");
			printf("    The old  method is  supported on  Cisco devices  upto  IOS 12.x, the\n");
			printf("    new method  (default) is  supported from  IOS 12.0  (11.2P  on  some\n");
			printf("    devices).\n\n");
			printf("    %s--snmp=<community>%s\n", COL_GREEN, RESET);
			printf("    The snmp community to be used with the above. A default of 'private'\n");
			printf("    will be used if not specified.\n\n");
			printf("    %s--tftproot=<directory>%s\n", COL_GREEN, RESET);
			printf("    The tftp root directory to be used for the Cisco config transfer. If\n");
			printf("    not specified a default of /tftproot/ will be used.\n\n");
			printf("    %s--cisco-file=<filename>%s\n", COL_GREEN, RESET);
			printf("    Specifies a  filename for the Cisco config file to  be saved  to. If\n");
			printf("    not specified,  then the  file will be  left in  the  tftproot  as a\n");
			printf("    random file name.\n\n");
			break;
#endif

		// The debug options (hidden)...
		case help_debug:
			printf("These are the Nipper debug options, useful for working out what has gone\n");
			printf("AWOL.  These options can  ouput a  lot of  information  and  disrupt the\n");
			printf("normal report output.\n\n");
			printf("    %s--debug%s\n", COL_GREEN, RESET);
			printf("    Outputs additional  information that most users  would not find very\n");
			printf("    helpful, but  is useful  in understanding  how the  configuration is\n");
			printf("    interpreted. Using the debug option overrides all other output.\n\n");
			printf("    %s--debug-abbreviations%s\n", COL_GREEN, RESET);
			printf("    Shows a list of all the  abbreviations that were  not processed. The\n");
			printf("    list is output  to stdout  and lists the  number of hits  each entry\n");
			printf("    has had. Not all of the items listed will be valid abbreviations.\n\n");
			printf("    %s--debug-lnp%s\n", COL_GREEN, RESET);
			printf("    Output the configuration lines not processed (to screen only).\n\n");
			break;

		// External Configuration file...
		case help_config_file:
			printf("Nipper can be configured using an external configuration file. This file\n");
			printf("can be specified on the  command line or  Nipper will load configuration\n");
#if !defined(__WIN32__)
			printf("settings from '/etc/nipper.conf'.\n\n");
#else
			printf("settings from 'nipper.ini' in the current directory.\n\n");
#endif
			printf("    %s--config=<file>%s\n", COL_GREEN, RESET);
			printf("    Specifies a Nipper configuration file.\n\n");
			break;

		case help_error_params:
			printf("%sERROR: Invalid command line options specified.%s\n\n", COL_RED, RESET);
			break;

		case help_error_empty_file:
			printf("%sERROR: The input was either an empty file or a directory.%s\n\n", COL_RED, RESET);
			break;

		case help_error_wrong_type:
			printf("%sERROR:  Nipper has  determined  that you are  attempting to  process the\n", COL_RED);
			printf("wrong type of configuration.  Refer to the DEVICES section on the online\n");
			printf("help, or alternatively, use the --force option.%s\n\n", RESET);
			break;

		case help_error_opening_file:
			printf("%sERROR: Nipper could not open the configuration file for input.%s\n\n", COL_RED, RESET);
			break;

		case help_error_snmp_failure:
			printf("%sERROR: Could not get the Cisco configuration via SNMP.%s\n\n", COL_RED, RESET);
			break;

		case help_error_snmp_root:
			printf("%sERROR: You must be the root user to get the configuration via SNMP.%s\n\n", COL_RED, RESET);
			break;

		case help_error_report_file:
			printf("%sERROR: Nipper could not open the report file for output.%s\n\n", COL_RED, RESET);
			break;

		case help_error_john_file:
			printf("%sERROR: Nipper could not open the john-the-ripper file for output.%s\n\n", COL_RED, RESET);
			break;

		case help_error_base64_decode:
			printf("%sERROR: Failed to decode the base64 configuration file encoding.%s\n\n", COL_RED, RESET);
			break;

		case help_error_read_timeout:
			if (nipper->inputName == 0)
			{
				printf("%sERROR: Failed to read from stdin, please pipe a configuration in or\n", COL_RED);
				printf("supply an input file using the --input=<file> option.%s\n\n", RESET);
			}
			else
				printf("%sERROR: A timeout occured whilst reading from the file.%s\n\n", COL_RED, RESET);
			break;
	}

	// Further Help...
	printf("%sFor additional help:%s\n", COL_BLUE, RESET);
	printf("    %s--help[=<topic>]%s\n", COL_GREEN, RESET);
	printf("    Show  the  online help  or show  the  additional  help on  the topic\n");
	printf("    specified.  The help  topics  are;  GENERAL,  DEVICES,  DEVICES-ADV,\n");
#if !defined(__WIN32__)
	printf("    SNMP,  REPORT, REPORT-ADV,  REPORT-SECT, REPORT-HTML,  REPORT-LATEX,\n");
#else
	printf("    REPORT,   REPORT-ADV,   REPORT-SECT,    REPORT-HTML,   REPORT-LATEX,\n");
#endif
	printf("    AUDIT-ACL, AUDIT-PASS, AUDIT-ADV or CONFIG-FILE.\n");
}


void stdinTimeout()
{
	// Program banner...
	printf("%s%s\n%s", COL_BLUE, program_banner, RESET);

	printf("%sERROR: Failed to read from stdin, please pipe a configuration in or\n", COL_RED);
	printf("supply an input file using the --input=<file> option.%s\n\n", RESET);

	// Further Help...
	printf("%sFor additional help:%s\n", COL_BLUE, RESET);
	printf("    %s--help[=<topic>]%s\n", COL_GREEN, RESET);
	printf("    Show  the  online help  or show  the  additional  help on  the topic\n");
	printf("    specified.  The help  topics  are;  GENERAL,  DEVICES,  DEVICES-ADV,\n");
#if !defined(__WIN32__)
	printf("    SNMP,  REPORT, REPORT-ADV,  REPORT-SECT, REPORT-HTML,  REPORT-LATEX,\n");
#else
	printf("    REPORT,   REPORT-ADV,   REPORT-SECT,    REPORT-HTML,   REPORT-LATEX,\n");
#endif
	printf("    AUDIT-ACL, AUDIT-PASS, AUDIT-ADV or CONFIG-FILE.\n");
	exit(0);
}


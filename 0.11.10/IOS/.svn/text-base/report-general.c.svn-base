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


void iosGeneralConfig(struct nipperConfig *nipper)
{
	output_table(nipper, true, settings_general_table, &settings_general_heading);
	fprintf(nipper->reportFile, "%sHostname%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->friendlyHostname, nipper->tablerow_end);
	if (nipper->version[0] != 0)
		fprintf(nipper->reportFile, "%sIOS Version%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->version, nipper->tablerow_end);
	if (nipper->ios->servicePasswordEncryption == false)
		fprintf(nipper->reportFile, "%sService Password Encryption%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sService Password Encryption%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if ((nipper->versionMajor == 12) && (nipper->versionMinor > 2))
	{
		if (nipper->ios->passwordMinLength == 0)
			fprintf(nipper->reportFile, "%sMinimum Password Length%sNone%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "%sMinimum Password Length%s%d characters%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->ios->passwordMinLength, nipper->tablerow_end);
	}
	if (nipper->deviceType == type_ios_router)
	{
		if (nipper->ios->sourceRouting == false)
			fprintf(nipper->reportFile, "%sIP Source Routing%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "%sIP Source Routing%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	}
	if (nipper->ios->bootp == unconfigured)
		fprintf(nipper->reportFile, "%sBOOTP%sUnconfigured%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else if (nipper->ios->bootp == false)
		fprintf(nipper->reportFile, "%sBOOTP%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sBOOTP%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->ios->serviceConfig == unconfigured)
		fprintf(nipper->reportFile, "%sService Config%sUnconfigured%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else if (nipper->ios->serviceConfig == false)
		fprintf(nipper->reportFile, "%sService Config%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sService Config%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->ios->keepAlivesIn == false)
		fprintf(nipper->reportFile, "%sTCP Keep Alives (In)%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sTCP Keep Alives (In)%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->ios->keepAlivesOut == false)
		fprintf(nipper->reportFile, "%sTCP Keep Alives (Out)%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sTCP Keep Alives (Out)%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->deviceType == type_ios_router)
	{
		if (nipper->ios->cef == false)
			fprintf(nipper->reportFile, "%sCisco Express Forwarding%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "%sCisco Express Forwarding%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		addAbbreviation("CEF", false);
	}
	if ((nipper->versionMajor > 11) || ((nipper->versionMajor == 11) && (nipper->versionMinor > 2)))
	{
		if (nipper->ios->gratuitousArps == false)
			fprintf(nipper->reportFile, "%sGratuitous ARPs%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "%sGratuitous ARPs%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		addAbbreviation("ARP", false);
	}
	if (nipper->deviceType == type_ios_router)
	{
		if (nipper->ios->classlessRouting == false)
			fprintf(nipper->reportFile, "%sClassless Routing%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "%sClassless Routing%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	}
	output_table(nipper, false, settings_general_table, &settings_general_heading);
	addAbbreviation("IOS", false);
	addAbbreviation("IP", false);
	addAbbreviation("BOOTP", false);
	addAbbreviation("UTC", false);
}


void iosServicesConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct lineConfig *linePointer = 0;
	int tempInt = 0;

	output_table(nipper, true, settings_services_table, &report_services_heading);
	tempInt = 0;
	linePointer = nipper->ios->line;
	while (linePointer != 0)
	{
		if (linePointer->telnet == true)
			tempInt++;
		linePointer = linePointer->next;
	}
	switch (tempInt)
	{
		case 0:
			fprintf(nipper->reportFile, "%sTelnet%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
		default:
			fprintf(nipper->reportFile, "%sTelnet%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
	}
	if (nipper->versionMajor >= 12)
	{
		if (nipper->ios->line != 0)
		{
			tempInt = 0;
			linePointer = nipper->ios->line;
			while (linePointer != 0)
			{
				if (linePointer->ssh == true)
					tempInt++;
				linePointer = linePointer->next;
			}
		}
		switch (tempInt)
		{
			case 0:
				fprintf(nipper->reportFile, "%sSSH%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
			default:
				fprintf(nipper->reportFile, "%sSSH%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
		}
		addAbbreviation("SSH", false);
	}
	if (nipper->ios->http != 0)
	{
		switch (nipper->ios->http->enabled)
		{
			case true:
				fprintf(nipper->reportFile, "%sHTTP%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
			case false:
				fprintf(nipper->reportFile, "%sHTTP%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
		}
	}
	else
		fprintf(nipper->reportFile, "%sHTTP%sUnconfigured%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	switch (nipper->ios->finger)
	{
		case unconfigured:
			fprintf(nipper->reportFile, "%sFinger%sUnconfigured%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
		case false:
			fprintf(nipper->reportFile, "%sFinger%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
		case true:
			fprintf(nipper->reportFile, "%sFinger%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
	}
	switch (nipper->ios->tcpSmallServers)
	{
		case false:
			fprintf(nipper->reportFile, "%sTCP Small Services%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
		case true:
			fprintf(nipper->reportFile, "%sTCP Small Services%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
	}
	switch (nipper->ios->udpSmallServers)
	{
		case false:
			fprintf(nipper->reportFile, "%sUDP Small Services%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
		case true:
			fprintf(nipper->reportFile, "%sUDP Small Services%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
			break;
	}
	if (nipper->ios->ntp != 0)
	{
		if (nipper->ios->ntp->enabled == true)
			fprintf(nipper->reportFile, "%sNTP%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "%sNTP%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	}
	if (nipper->ios->snmp != 0)
	{
		if (nipper->ios->snmp->enabled == true)
			fprintf(nipper->reportFile, "%sSNMP%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "%sSNMP%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	}
	if (nipper->ios->cdp == false)
		fprintf(nipper->reportFile, "%sCDP%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sCDP%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->ios->pad == true)
		fprintf(nipper->reportFile, "%sPAD%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sPAD%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	output_table(nipper, false, settings_services_table, &report_services_heading);
	addAbbreviation("CDP", false);
	addAbbreviation("PAD", false);
	addAbbreviation("NTP", false);
	addAbbreviation("SNMP", false);
	addAbbreviation("UDP", false);
	addAbbreviation("TCP", false);
	addAbbreviation("HTTP", false);
}


void iosVulnIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct vulnerability *vulnPointer = 0;
	char tempString[nipper->maxSize];

	output_parseText(report_osver_obs1, nipper, section_obs, rate_none, nipper->vulnIssues, nipper->tableNum);
	if (nipper->vulnIssues > 1)
	{
		output_table(nipper, true, report_osver_table, &report_osver_heading);
		vulnPointer = &report_vuln_ios;
		while (vulnPointer->next != 0)
		{
			if (vulnPointer->include == true)
			{
				outputFriendly(vulnPointer->description, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
				fprintf(nipper->reportFile, "%s%s%s%s", vulnPointer->cve, nipper->tablerow_mid, vulnPointer->bid, nipper->tablerow_end);
			}
			vulnPointer = vulnPointer->next;
		}
		output_table(nipper, false, report_osver_table, &report_osver_heading);
		output_parseText(report_osver_obs2, nipper, section_none, rate_none, nipper->vulnIssues, nipper->tableNum -1);
	}
	else if (nipper->vulnIssues > 0)
	{
		output_parseText(report_osver_obs3, nipper, section_none, rate_none, nipper->vulnIssues, nipper->tableNum -1);
		vulnPointer = &report_vuln_ios;
		while (vulnPointer->next != 0)
		{
			if (vulnPointer->include == true)
			{
				outputFriendly(vulnPointer->description, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "\"%s\" (", tempString);
				if (vulnPointer->cve[0] != 0)
					fprintf(nipper->reportFile, "CVE reference %s", vulnPointer->cve);
				if ((vulnPointer->cve[0] != 0) && (vulnPointer->bid[0] != 0))
					fprintf(nipper->reportFile, " and ");
				if (vulnPointer->bid[0] != 0)
					fprintf(nipper->reportFile, " Bugtraq ID %s", vulnPointer->bid);
				fprintf(nipper->reportFile, ").");
			}
			vulnPointer = vulnPointer->next;
		}
		if (nipper->outputFormat == output_xml)
			fprintf(nipper->reportFile, "</text>\n");
		output_parseText(report_osver_obs2, nipper, section_none, rate_none, nipper->vulnIssues, nipper->tableNum -1);
	}
	output_endsection(nipper, section_obs);
	if (nipper->vulnIssues > 0)
	{
		output_parseText(report_osver_impact1, nipper, section_imp, rate_high, nipper->vulnIssues, nipper->tableNum -1);
		if ((nipper->vulnIssueDos == true) && (nipper->vulnIssueRemote == true))
			output_parseText(report_osver_impact2, nipper, section_none, rate_none, nipper->vulnIssues, nipper->tableNum -1);
		else if (nipper->vulnIssueDos == true)
			output_parseText(report_osver_impact3, nipper, section_none, rate_none, nipper->vulnIssues, nipper->tableNum -1);
		else if (nipper->vulnIssueRemote == true)
			output_parseText(report_osver_impact4, nipper, section_none, rate_none, nipper->vulnIssues, nipper->tableNum -1);
		addAbbreviation("CVE", false);
		addAbbreviation("BID", false);
	}
	else
		output_parseText(report_osver_impact5, nipper, section_imp, rate_high, nipper->vulnIssues, nipper->tableNum -1);
	output_endsection(nipper, section_imp);
	output_parseText(report_osver_ease, nipper, section_ease, rate_trivial, nipper->vulnIssues, nipper->tableNum -1);
	output_endsection(nipper, section_ease);
	output_parseText(report_osver_rec, nipper, section_rec, rate_none, nipper->vulnIssues, nipper->tableNum -1);
	output_endsection(nipper, section_rec);
}


void iosAutoConfigIssue(struct nipperConfig *nipper)
{
	output_parseText(report_configauto_obs, nipper, section_obs, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_configauto_impact, nipper, section_imp, rate_high, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_configauto_ease, nipper, section_ease, rate_trivial, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_configauto_rec, nipper, section_rec, rate_trivial, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosKeepAlivesIssue(struct nipperConfig *nipper)
{
	output_parseText(report_keepalive_obs, nipper, section_obs, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_keepalive_impact, nipper, section_imp, rate_high, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_keepalive_ease, nipper, section_ease, rate_moderate, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_keepalive_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosFingerIssue(struct nipperConfig *nipper)
{
	output_parseText(report_finger_obs, nipper, section_obs, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_finger_impact, nipper, section_imp, rate_med, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_finger_ease, nipper, section_ease, rate_trivial, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_finger_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosPasswordLengthIssue(struct nipperConfig *nipper)
{
	if (nipper->ios->passwordMinLength == 0)
		output_parseText(report_passlength_obs, nipper, section_obs, rate_none, -1, nipper->tableNum);
	else
		output_parseText(report_passlength_obs, nipper, section_obs, rate_none, nipper->ios->passwordMinLength, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_passlength_impact, nipper, section_imp, rate_low, nipper->ios->passwordMinLength, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_passlength_ease, nipper, section_ease, rate_trivial, nipper->ios->passwordMinLength, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_passlength_rec, nipper, section_rec, rate_none, nipper->passwordLength, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosBootPIssue(struct nipperConfig *nipper)
{
	output_parseText(report_bootp_obs, nipper, section_obs, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_bootp_impact, nipper, section_imp, rate_low, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_bootp_ease, nipper, section_ease, rate_trivial, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_bootp_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosSmallServersIssue(struct nipperConfig *nipper)
{
	// Check for IOS version...
	int olderIOS = false;
	if ((nipper->versionMajor < 11) || ((nipper->versionMajor == 11) && (nipper->versionMinor < 3)))
		olderIOS = true;
	// Report...
	output_parseText(report_small_obs1, nipper, section_obs, rate_none, 0, nipper->tableNum);
	if (olderIOS == true)
		output_parseText(report_small_obs2, nipper, section_none, rate_none, 0, nipper->tableNum);
	else if ((nipper->ios->udpSmallServers == true) && (nipper->ios->tcpSmallServers == true))
		output_parseText(report_small_obs3, nipper, section_none, rate_none, 0, nipper->tableNum);
	else if (nipper->ios->tcpSmallServers == true)
		output_parseText(report_small_obs4, nipper, section_none, rate_none, 0, nipper->tableNum);
	else if (nipper->ios->udpSmallServers == true)
		output_parseText(report_small_obs5, nipper, section_none, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_small_impact, nipper, section_imp, rate_low, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_small_ease, nipper, section_ease, rate_trivial, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_small_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	if ((olderIOS == true) || (nipper->ios->tcpSmallServers == true))
		output_parseText(report_small_rec_tcp, nipper, section_none, rate_none, 0, nipper->tableNum);
	if ((olderIOS == true) || (nipper->ios->udpSmallServers == true))
		output_parseText(report_small_rec_udp, nipper, section_none, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosBannerIssue(struct nipperConfig *nipper)
{
	output_parseText(report_banner_obs, nipper, section_obs, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_banner_impact, nipper, section_imp, rate_low, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_banner_ease, nipper, section_ease, rate_noease, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_banner_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosPADIssue(struct nipperConfig *nipper)
{
	output_parseText(report_pad_obs, nipper, section_obs, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_pad_impact, nipper, section_imp, rate_low, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_pad_ease, nipper, section_ease, rate_noease, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_pad_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


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


void pixGeneralConfig(struct nipperConfig *nipper)
{
	// Variables...
	char tempString[nipper->maxSize];

	output_table(nipper, true, settings_general_table, &settings_general_heading);
	fprintf(nipper->reportFile, "%sHostname%s%s %s", nipper->tablerow_start, nipper->tablerow_mid, nipper->friendlyHostname, nipper->tablerow_end);
	if (nipper->domainName[0] != 0)
	{
		outputFriendly(nipper->domainName, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%sDomain Name%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
	}
	if ((nipper->version[0] != 0) && (nipper->deviceType == type_pix_firewall))
	{
		addAbbreviation("PIX", false);
		fprintf(nipper->reportFile, "%sPIX Version%s%s %s", nipper->tablerow_start, nipper->tablerow_mid, nipper->version, nipper->tablerow_end);
	}
	else if ((nipper->version[0] != 0) && (nipper->deviceType == type_asa_firewall))
	{
		addAbbreviation("ASA", false);
		fprintf(nipper->reportFile, "%sASA Version%s%s %s", nipper->tablerow_start, nipper->tablerow_mid, nipper->version, nipper->tablerow_end);
	}
	else if ((nipper->version[0] != 0) && (nipper->deviceType == type_fwsm_firewall))
	{
		addAbbreviation("FWSM", false);
		fprintf(nipper->reportFile, "%sFWSM Version%s%s %s", nipper->tablerow_start, nipper->tablerow_mid, nipper->version, nipper->tablerow_end);
	}
	if (nipper->pix->transparent == true)
		fprintf(nipper->reportFile, "%sTransparent Firewall%sYes%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sTransparent Firewall%sNo%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->pix->floodguard == true)
		fprintf(nipper->reportFile, "%sFlood Guard%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sFlood Guard%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	output_table(nipper, false, settings_general_table, &settings_general_heading);
}


void pixServicesConfig(struct nipperConfig *nipper)
{
	output_table(nipper, true, settings_services_table, &report_services_heading);
	if (nipper->pix->snmp == 0)
		fprintf(nipper->reportFile, "%sSNMP Server%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else if (nipper->pix->snmp->enabled == true)
		fprintf(nipper->reportFile, "%sSNMP Server%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sSNMP Server%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->pix->http == 0)
		fprintf(nipper->reportFile, "%sHTTPS Server%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else if (nipper->pix->http->httpServer == false)
		fprintf(nipper->reportFile, "%sHTTPS Server%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sHTTPS Server%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	output_table(nipper, false, settings_services_table, &report_services_heading);
	addAbbreviation("SNMP", false);
	addAbbreviation("HTTPS", false);
}


void pixVulnerabilityIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct vulnerability *vulnPointer = 0;
	char tempString[nipper->maxSize];

	output_parseText(report_osver_obs1, nipper, section_obs, rate_none, nipper->vulnIssues, nipper->tableNum);
	if (nipper->vulnIssues > 1)
	{
		output_table(nipper, true, report_osver_table, &report_osver_heading);
		if (nipper->deviceType == type_fwsm_firewall)
			vulnPointer = &report_vuln_fwsm;
		else
			vulnPointer = &report_vuln_pix;
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
		if (nipper->deviceType == type_fwsm_firewall)
			vulnPointer = &report_vuln_fwsm;
		else
			vulnPointer = &report_vuln_pix;
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


void pixTimeoutIssue(struct nipperConfig *nipper)
{
	// Variables...
	char tempString[nipper->maxSize];

	output_parseText(report_timeout_obs1, nipper, section_obs, rate_none, nipper->insecureTimeouts, nipper->tableNum);
	if ((nipper->connectionTimeout % 60) == 0)
	{
		numToWord(nipper->reportFile, (nipper->connectionTimeout / 60));
		fprintf(nipper->reportFile, " minutes");
	}
	else
	{
		numToWord(nipper->reportFile, nipper->connectionTimeout / 60);
		fprintf(nipper->reportFile, " minutes and ");
		numToWord(nipper->reportFile, nipper->connectionTimeout % 60);
		fprintf(nipper->reportFile, " seconds");
	}
	output_parseText(report_timeout_obs2, nipper, section_none, rate_none, nipper->insecureTimeouts, nipper->tableNum);
	if (nipper->insecureTimeouts > 1)
	{
		output_table(nipper, true, report_timeout_table, &report_timeout_heading);
		if (nipper->pix->ssh != 0)
		{
			if ((nipper->pix->ssh->timeout * 60) > nipper->connectionTimeout)
			{
				fprintf(nipper->reportFile, "%sSSH Session Timeout%s", nipper->tablerow_start, nipper->tablerow_mid);
				numToWord(nipper->reportFile, nipper->pix->ssh->timeout);
				fprintf(nipper->reportFile, " minutes%s", nipper->tablerow_end);
			}
		}
		output_table(nipper, false, report_timeout_table, &report_timeout_heading);
	}
	else
	{
		if (nipper->pix->ssh != 0)
		{
			if ((nipper->pix->ssh->timeout * 60) > nipper->connectionTimeout)
			{
				sprintf(tempString, "*NOTEXTSTART*The SSH session timeout was *NUMBER* minutes.");
				output_parseText(tempString, nipper, section_none, rate_none, nipper->pix->ssh->timeout, 0);
			}
		}
	}
	output_endsection(nipper, section_obs);
	output_parseText(report_timeout_impact, nipper, section_imp, rate_high, 0, 0);
	output_endsection(nipper, section_imp);
	output_parseText(report_timeout_ease, nipper, section_ease, rate_difficult, 0, 0);
	output_endsection(nipper, section_ease);
	output_parseText(report_timeout_rec1, nipper, section_rec, rate_none, 0, 0);
	if ((nipper->connectionTimeout % 60) == 0)
	{
		numToWord(nipper->reportFile, (nipper->connectionTimeout / 60));
		fprintf(nipper->reportFile, " minutes");
	}
	else
	{
		numToWord(nipper->reportFile, nipper->connectionTimeout / 60);
		fprintf(nipper->reportFile, " minutes and ");
		numToWord(nipper->reportFile, (nipper->connectionTimeout % 60));
		fprintf(nipper->reportFile, " seconds");
	}
	output_parseText(report_timeout_rec2, nipper, section_none, rate_none, 0, 0);
	output_endsection(nipper, section_rec);
}


void pixFloodGuardIssue(struct nipperConfig *nipper)
{
	output_parseText(report_floodguard_obs, nipper, section_obs, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_floodguard_impact, nipper, section_imp, rate_med, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_floodguard_ease, nipper, section_ease, rate_trivial, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_floodguard_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void pixURPFIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct interfacePIXConfig *interfacePIXConfigPointer = 0;
	char tempString[nipper->maxSize];

	output_parseText(report_urpf_pix_obs, nipper, section_obs, rate_none, nipper->uRPFIssues, nipper->tableNum);
	if (nipper->uRPFIssues > 1)
	{
		interfacePIXConfigPointer = nipper->pix->interface;
		output_table(nipper, true, report_urpf_table, &report_interfacepix_heading);
		while (interfacePIXConfigPointer != 0)
		{
			if ((interfacePIXConfigPointer->uRPF == false) && (interfacePIXConfigPointer->shutdown == false) && (strcmp(interfacePIXConfigPointer->ipAddress, "") != 0))
			{
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, interfacePIXConfigPointer->interface, nipper->tablerow_mid);
				fprintf(nipper->reportFile, "%s%s", interfacePIXConfigPointer->name, nipper->tablerow_end);
			}
			interfacePIXConfigPointer = interfacePIXConfigPointer->next;
		}
		output_table(nipper, false, report_urpf_table, &report_interfacepix_heading);
	}
	else if (nipper->uRPFIssues > 0)
	{
		interfacePIXConfigPointer = nipper->pix->interface;
		while (interfacePIXConfigPointer != 0)
		{
			if ((interfacePIXConfigPointer->uRPF == false) && (interfacePIXConfigPointer->shutdown == false) && (strcmp(interfacePIXConfigPointer->ipAddress, "") != 0))
			{
				outputFriendly(interfacePIXConfigPointer->interface, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s.", tempString);
			}
			interfacePIXConfigPointer = interfacePIXConfigPointer->next;
		}
		output_newPara(nipper);
	}
	output_endsection(nipper, section_obs);
	output_parseText(report_urpf_impact, nipper, section_imp, rate_med, nipper->uRPFIssues, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_urpf_ease, nipper, section_ease, rate_noease, nipper->uRPFIssues, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_urpf_pix_rec, nipper, section_rec, rate_none, nipper->uRPFIssues, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


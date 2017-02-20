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

// This file contains the code for NMP / CatOS reporting

void nmpPortsConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct moduleConfig *moduleNMPPointer = 0;
	struct portConfig *portNMPPointer = 0;
	char tempString[nipper->maxSize];
	char tempString2[nipper->maxSize];

	// Modules / Ports
	moduleNMPPointer = nipper->nmp->module;
	while (moduleNMPPointer != 0)
	{
		if (moduleNMPPointer->name[0] == 0)
			sprintf(tempString, "Module %d port configuration", moduleNMPPointer->module);
		else
			sprintf(tempString, "Module %d (%s) port configuration", moduleNMPPointer->module, moduleNMPPointer->name);
		output_table(nipper, true, tempString, &settings_ports_heading);
		portNMPPointer = moduleNMPPointer->ports;
		while (portNMPPointer != 0)
		{
			fprintf(nipper->reportFile, "%s%d%s", nipper->tablerow_start, portNMPPointer->port, nipper->tablerow_mid);
			outputFriendly(portNMPPointer->name, tempString2, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s", tempString2, nipper->tablerow_mid);
			if (portNMPPointer->enabled == true)
				fprintf(nipper->reportFile, "Enabled%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "Disabled%s", nipper->tablerow_mid);
			fprintf(nipper->reportFile, "%d%s", portNMPPointer->vlan, nipper->tablerow_mid);
			switch (portNMPPointer->speed)
			{
				case port_speed_auto:
					fprintf(nipper->reportFile, "Auto%s", nipper->tablerow_mid);
					break;
				case port_speed_10:
					fprintf(nipper->reportFile, "10Mb%s", nipper->tablerow_mid);
					break;
				case port_speed_100:
					fprintf(nipper->reportFile, "100Mb%s", nipper->tablerow_mid);
					break;
				case port_speed_1000:
					fprintf(nipper->reportFile, "1000Mb%s", nipper->tablerow_mid);
					break;
				case port_speed_auto_10_100:
					fprintf(nipper->reportFile, "10/100Mb%s", nipper->tablerow_mid);
					break;
			}
			switch (portNMPPointer->duplex)
			{
				case port_duplex_auto:
					fprintf(nipper->reportFile, "Auto%s", nipper->tablerow_mid);
					break;
				case port_duplex_half:
					fprintf(nipper->reportFile, "Half%s", nipper->tablerow_mid);
					break;
				case port_duplex_full:
					fprintf(nipper->reportFile, "Full%s", nipper->tablerow_mid);
					break;
			}
			if (portNMPPointer->portSecurity == true)
				fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
			if (portNMPPointer->cdp == true)
				fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
			switch (portNMPPointer->trunk)
			{
				case port_trunk_auto:
					fprintf(nipper->reportFile, "Auto%s", nipper->tablerow_mid);
					break;
				case port_trunk_nonegotiate:
					fprintf(nipper->reportFile, "No Negotiate%s", nipper->tablerow_mid);
					break;
				case port_trunk_on:
					fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
					break;
				case port_trunk_off:
					fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
					break;
				case port_trunk_desirable:
					fprintf(nipper->reportFile, "Desirable%s", nipper->tablerow_mid);
					break;
			}
			if (portNMPPointer->vtp == true)
				fprintf(nipper->reportFile, "On%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "Off%s", nipper->tablerow_mid);
			switch (portNMPPointer->spantreeGuard)
			{
				case port_guard_none:
					fprintf(nipper->reportFile, "Off%s", nipper->tablerow_end);
					break;
				case port_guard_default:
					fprintf(nipper->reportFile, "On%s", nipper->tablerow_end);
					break;
				case port_guard_loop:
					fprintf(nipper->reportFile, "On (loop)%s", nipper->tablerow_end);
					break;
				case port_guard_root:
					fprintf(nipper->reportFile, "On (root)%s", nipper->tablerow_end);
					break;
			}
			portNMPPointer = portNMPPointer->next;
		}
		output_table(nipper, false, tempString, &settings_ports_heading);
		moduleNMPPointer = moduleNMPPointer->next;
	}
	addAbbreviation("VLAN", false);
	addAbbreviation("STP", false);
}


void nmpCDPConfig(struct nipperConfig *nipper)
{
	output_table(nipper, true, settings_cdp_table, &settings_general_heading);
	if (nipper->nmp->cdp == true)
		fprintf(nipper->reportFile, "%sCisco Discovery Protocol%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sCisco Discovery Protocol%sGlobally Disabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	fprintf(nipper->reportFile, "%sCDP Version%s%d%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->nmp->cdpVersion, nipper->tablerow_end);
	fprintf(nipper->reportFile, "%sCDP Message Interval%s", nipper->tablerow_start, nipper->tablerow_mid);
	if (nipper->nmp->cdpInterval % 60 == 0)
	{
		numToWord(nipper->reportFile, nipper->nmp->cdpInterval / 60);
		if (nipper->nmp->cdpInterval / 60 > 1)
			fprintf(nipper->reportFile, " minutes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, " minute%s", nipper->tablerow_end);
	}
	else
	{
		numToWord(nipper->reportFile, nipper->nmp->cdpInterval / 60);
		if (nipper->nmp->cdpInterval / 60 > 1)
			fprintf(nipper->reportFile, " minutes ");
		else
			fprintf(nipper->reportFile, " minute ");
		numToWord(nipper->reportFile, nipper->nmp->cdpInterval % 60);
		if (nipper->nmp->cdpInterval % 60 > 1)
			fprintf(nipper->reportFile, " seconds%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, " second%s", nipper->tablerow_end);
	}
	fprintf(nipper->reportFile, "%sCDP TTL%s", nipper->tablerow_start, nipper->tablerow_mid);
	if (nipper->nmp->cdpHoldtime % 60 == 0)
	{
		numToWord(nipper->reportFile, nipper->nmp->cdpHoldtime / 60);
		if (nipper->nmp->cdpHoldtime / 60 > 1)
			fprintf(nipper->reportFile, " minutes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, " minute%s", nipper->tablerow_end);
	}
	else
	{
		numToWord(nipper->reportFile, nipper->nmp->cdpHoldtime / 60);
		if (nipper->nmp->cdpHoldtime / 60 > 1)
			fprintf(nipper->reportFile, " minutes ");
		else
			fprintf(nipper->reportFile, " minute ");
		numToWord(nipper->reportFile, nipper->nmp->cdpHoldtime % 60);
		if (nipper->nmp->cdpHoldtime % 60 > 1)
			fprintf(nipper->reportFile, " seconds%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, " second%s", nipper->tablerow_end);
	}
	output_table(nipper, false, settings_cdp_table, &settings_general_heading);
	addAbbreviation("CDP", false);
	addAbbreviation("TTL", false);
}


void nmpRedirectsIssue(struct nipperConfig *nipper)
{
	output_parseText(report_redirects_obs, nipper, section_obs, rate_none, -1, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_redirects_impact, nipper, section_imp, rate_med, 0, 0);
	output_endsection(nipper, section_imp);
	output_parseText(report_redirects_ease, nipper, section_ease, rate_trivial, 0, 0);
	output_endsection(nipper, section_ease);
	output_parseText(report_redirects_rec2, nipper, section_rec, rate_none, 0, 0);
	output_endsection(nipper, section_rec);
}


void nmpUnreachablesIssue(struct nipperConfig *nipper)
{
	output_parseText(report_icmpunreach_obs, nipper, section_obs, rate_none, -1, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_icmpunreach_impact, nipper, section_imp, rate_low, 0, 0);
	output_endsection(nipper, section_imp);
	output_parseText(report_icmpunreach_ease, nipper, section_ease, rate_trivial, 0, 0);
	output_endsection(nipper, section_ease);
	output_parseText(report_icmpunreach_rec2, nipper, section_rec, rate_none, 0, 0);
	output_endsection(nipper, section_rec);
}

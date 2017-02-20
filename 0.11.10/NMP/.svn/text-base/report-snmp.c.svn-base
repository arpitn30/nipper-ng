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

void nmpSNMPConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct snmpNMPCommunity *communityNMPPointer = 0;
	struct snmpNMPHost *snmpNMPHostPointer = 0;
	struct snmpTrap *snmpTrapPointer = 0;

	if (nipper->nmp->snmp->community != 0)
	{
		output_table(nipper, true, settings_snmpstring_table, &settings_snmpcomm_heading);
		communityNMPPointer = nipper->nmp->snmp->community;
		while (communityNMPPointer != 0)
		{
			if (communityNMPPointer->type == snmp_nmp_standard)
				fprintf(nipper->reportFile, "%sStandard%s", nipper->tablerow_start, nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "%sExtended%s", nipper->tablerow_start, nipper->tablerow_mid);
			if (nipper->passwords == true)
				fprintf(nipper->reportFile, "%s %s", communityNMPPointer->community, nipper->tablerow_mid);
			switch (communityNMPPointer->access)
			{
				case snmp_nmp_readonly:
					fprintf(nipper->reportFile, "Read-Only%s", nipper->tablerow_end);
					break;
				case snmp_nmp_readwrite:
					fprintf(nipper->reportFile, "Read-Write%s", nipper->tablerow_end);
					break;
				case snmp_nmp_readwrite_all:
					fprintf(nipper->reportFile, "Read-Write-All%s", nipper->tablerow_end);
					break;
			}
			communityNMPPointer = communityNMPPointer->next;
		}
		output_table(nipper, false, settings_snmpstring_table, &settings_snmpcomm_heading);
	}
	if (nipper->nmp->snmp->trap != 0)
	{
		output_table(nipper, true, settings_snmptrap_table, &settings_snmptraps_heading);
		snmpTrapPointer = nipper->nmp->snmp->trap;
		while (snmpTrapPointer != 0)
		{
			if (snmpTrapPointer->enabled == true)
				fprintf(nipper->reportFile, "%sEnabled", nipper->tablerow_start);
			else
				fprintf(nipper->reportFile, "%sDisabled", nipper->tablerow_start);
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, snmpTrapPointer->trap, nipper->tablerow_end);
			addAbbreviation(snmpTrapPointer->trap, false);
			snmpTrapPointer = snmpTrapPointer->next;
		}
		output_table(nipper, false, settings_snmptrap_table, &settings_snmptraps_heading);
	}
	if (nipper->nmp->snmp->host != 0)
	{
		output_table(nipper, true, settings_snmphost_table, &settings_snmphosts_heading);
		snmpNMPHostPointer = nipper->nmp->snmp->host;
		while (snmpNMPHostPointer != 0)
		{
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, snmpNMPHostPointer->host, nipper->tablerow_mid);
			if (nipper->passwords == true)
				fprintf(nipper->reportFile, "%s%s", snmpNMPHostPointer->community, nipper->tablerow_mid);
			fprintf(nipper->reportFile, "%d%s", snmpNMPHostPointer->version, nipper->tablerow_mid);
			fprintf(nipper->reportFile, "%d%s", snmpNMPHostPointer->port, nipper->tablerow_mid);
			fprintf(nipper->reportFile, "%s%s", snmpNMPHostPointer->owner, nipper->tablerow_mid);
			fprintf(nipper->reportFile, "%d%s", snmpNMPHostPointer->index, nipper->tablerow_end);
			snmpNMPHostPointer = snmpNMPHostPointer->next;
		}
		output_table(nipper, false, settings_snmphost_table, &settings_snmphosts_heading);
	}
	addAbbreviation("SNMP", false);
}

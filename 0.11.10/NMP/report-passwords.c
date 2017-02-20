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


void output_NMPTablePasswords(struct nipperConfig *nipper, int dictPassword)
{
	// Variables
	struct snmpNMPCommunity *communityNMPPointer = 0;
	struct snmpNMPHost *snmpNMPHostPointer = 0;
	char tempString[nipper->maxSize];

	// SNMP
	if (nipper->nmp->snmp != 0)
	{
		communityNMPPointer = nipper->nmp->snmp->community;
		while (communityNMPPointer != 0)
		{
			if (((communityNMPPointer->dictionary == true) && (dictPassword == true)) || ((communityNMPPointer->weak == true) && (dictPassword == false)))
			{
				fprintf(nipper->reportFile, "%sCommunity%sSNMP%s(", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid);
				if (communityNMPPointer->access == snmp_nmp_readonly)
					fprintf(nipper->reportFile, "read-only");
				else if (communityNMPPointer->access == snmp_nmp_readwrite)
					fprintf(nipper->reportFile, "read-write");
				else
					fprintf(nipper->reportFile, "read-write all");
				if (nipper->passwords == true)
				{
					outputFriendly(communityNMPPointer->community, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, ")%s%s%s", nipper->tablerow_mid, tempString, nipper->tablerow_end);
				}
				else
					fprintf(nipper->reportFile, ")%s", nipper->tablerow_end);
			}
			communityNMPPointer = communityNMPPointer->next;
		}
		snmpNMPHostPointer = nipper->nmp->snmp->host;
		while (snmpNMPHostPointer != 0)
		{
			if (((snmpNMPHostPointer->dictionary == true) && (dictPassword == true)) || ((snmpNMPHostPointer->weak == true) && (dictPassword == false)))
			{
				outputFriendly(snmpNMPHostPointer->host, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%sCommunity%sSNMP%sHost: %s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, tempString);
				if (nipper->passwords == true)
				{
					outputFriendly(snmpNMPHostPointer->community, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, tempString, nipper->tablerow_end);
				}
				else
					fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
			}
			snmpNMPHostPointer = snmpNMPHostPointer->next;
		}
	}
}


void output_NMPLinePasswords(struct nipperConfig *nipper, int dictPassword)
{
	// Variables
	struct snmpNMPCommunity *communityNMPPointer = 0;
	struct snmpNMPHost *snmpNMPHostPointer = 0;
	char tempString[nipper->maxSize];

	if (nipper->nmp->snmp != 0)
	{
		communityNMPPointer = nipper->nmp->snmp->community;
		while (communityNMPPointer != 0)
		{
			if (((communityNMPPointer->dictionary == true) && (dictPassword == true)) || ((communityNMPPointer->weak == true) && (dictPassword == false)))
			{
				fprintf(nipper->reportFile, "The ");
				if (communityNMPPointer->access == snmp_nmp_readonly)
					fprintf(nipper->reportFile, "read-only");
				else if (communityNMPPointer->access == snmp_nmp_readwrite)
					fprintf(nipper->reportFile, "read-write");
				else
					fprintf(nipper->reportFile, "read-write all");
				fprintf(nipper->reportFile, " SNMP community string was ");
				if (nipper->passwords == true)
				{
					outputFriendly(communityNMPPointer->community, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s.", tempString);
				}
				else
				{
					if (dictPassword == true)
						fprintf(nipper->reportFile, "dictionary-based.");
					else
						fprintf(nipper->reportFile, "weak.");
				}
			}
			communityNMPPointer = communityNMPPointer->next;
		}
		snmpNMPHostPointer = nipper->nmp->snmp->host;
		while (snmpNMPHostPointer != 0)
		{
			if (snmpNMPHostPointer->dictionary == true)
			{
				outputFriendly(snmpNMPHostPointer->host, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "The SNMP community string for the host %s was ", tempString);
				if (nipper->passwords == true)
				{
					outputFriendly(snmpNMPHostPointer->community, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s.", tempString);
				}
				else
				{
					if (dictPassword == true)
						fprintf(nipper->reportFile, "dictionary-based.");
					else
						fprintf(nipper->reportFile, "weak.");
				}
			}
			snmpNMPHostPointer = snmpNMPHostPointer->next;
		}
	}
	output_newPara(nipper);
}


void nmpPasswordsConfig(struct nipperConfig *nipper)
{
	output_table(nipper, true, settings_passwords_title, &settings_passwords_heading);
	if (nipper->nmp->enablePassword[0] != 0)
	{
		fprintf(nipper->reportFile, "%sEnable Password", nipper->tablerow_start);
		if (nipper->passwords == true)
			fprintf(nipper->reportFile, "%s%s %s", nipper->tablerow_mid, nipper->nmp->enablePassword, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
	}
	if (nipper->nmp->password[0] != 0)
	{
		fprintf(nipper->reportFile, "%sLogin Password", nipper->tablerow_start);
		if (nipper->passwords == true)
			fprintf(nipper->reportFile, "%s%s %s", nipper->tablerow_mid, nipper->nmp->password, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
	}
	output_table(nipper, false, settings_passwords_title, &settings_passwords_heading);
}


void nmpDictionaryIssue(struct nipperConfig *nipper)
{
	// Variables...
	int tempInt = 0;

	output_parseText(report_dict_obs, nipper, section_obs, rate_none, nipper->simplePasswords, nipper->tableNum);
	if (nipper->passwordStrengths > 1)
	{
		output_table(nipper, true, report_dict_table, &report_dict_heading);
		output_NMPTablePasswords(nipper, true);
		output_table(nipper, false, report_dict_table, &report_dict_heading);
	}
	else
		output_NMPLinePasswords(nipper, true);
	output_endsection(nipper, section_obs);
	output_parseText(report_dict_impact, nipper, section_imp, rate_high, nipper->simplePasswords, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_dict_ease, nipper, section_ease, rate_trivial, nipper->simplePasswords, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_dict_rec, nipper, section_rec, rate_none, nipper->simplePasswords, nipper->tableNum);
	numToWord(nipper->reportFile, nipper->passwordLength);
	fprintf(nipper->reportFile, " characters in length and contain");
	if (nipper->passwordUppers == true)
		tempInt = 1;
	else
		tempInt = 0;
	if (nipper->passwordLowers == true)
		tempInt++;
	if (nipper->passwordEither == true)
		tempInt++;
	if (nipper->passwordNumbers == true)
		tempInt++;
	if (nipper->passwordSpecials == true)
		tempInt++;
	if (nipper->passwordUppers == true)
	{
		fprintf(nipper->reportFile, " uppercase");
		if (tempInt > 2)
			fprintf(nipper->reportFile, ",");
		else if (tempInt == 2)
			fprintf(nipper->reportFile, " and");
		tempInt--;
	}
	if (nipper->passwordLowers == true)
	{
		fprintf(nipper->reportFile, " lowercase");
		if (tempInt > 2)
			fprintf(nipper->reportFile, ",");
		else if (tempInt == 2)
			fprintf(nipper->reportFile, " and");
		tempInt--;
	}
	if (nipper->passwordEither == true)
	{
		fprintf(nipper->reportFile, " either uppercase or lowercase characters");
		if (tempInt > 2)
			fprintf(nipper->reportFile, ",");
		else if (tempInt == 2)
			fprintf(nipper->reportFile, " and");
		tempInt--;
	}
	if (nipper->passwordNumbers == true)
	{
		fprintf(nipper->reportFile, " numbers");
		if (tempInt > 2)
			fprintf(nipper->reportFile, ",");
		else if (tempInt == 2)
			fprintf(nipper->reportFile, " and");
		tempInt--;
	}
	if (nipper->passwordSpecials == true)
	{
		fprintf(nipper->reportFile, " special");
		if (tempInt > 2)
			fprintf(nipper->reportFile, ",");
		else if (tempInt == 2)
			fprintf(nipper->reportFile, " and");
		tempInt--;
	}
	if (((nipper->passwordNumbers == true) && (nipper->passwordSpecials == false)) || ((nipper->passwordEither == false) && (nipper->passwordNumbers == false) && (nipper->passwordSpecials == false)))
		fprintf(nipper->reportFile, ".");
	else
		fprintf(nipper->reportFile, " characters.");
	if (nipper->outputFormat == output_xml)
		fprintf(nipper->reportFile, "</text>\n");
	output_newPara(nipper);
	output_endsection(nipper, section_rec);
}


void nmpStrengthIssue(struct nipperConfig *nipper)
{
	// Variables
	int tempInt = 0;

	output_parseText(report_strength_obs, nipper, section_obs, rate_none, nipper->passwordStrengths, nipper->tableNum);
	if (nipper->passwordStrengths > 1)
	{
		output_table(nipper, true, report_strength_table, &report_dict_heading);
		output_NMPTablePasswords(nipper, false);
		output_table(nipper, false, report_strength_table, &report_dict_heading);
	}
	else
		output_NMPLinePasswords(nipper, false);
	output_endsection(nipper, section_obs);
	output_parseText(report_strength_impact, nipper, section_imp, rate_high, 0, 0);
	output_endsection(nipper, section_imp);
	output_parseText(report_strength_ease, nipper, section_ease, rate_trivial, 0, 0);
	output_endsection(nipper, section_ease);
	output_parseText(report_strength_rec, nipper, section_rec, rate_trivial, 0, 0);
	numToWord(nipper->reportFile, nipper->passwordLength);
	fprintf(nipper->reportFile, " characters in length and contain");
	if (nipper->passwordUppers == true)
		tempInt = 1;
	else
		tempInt = 0;
	if (nipper->passwordLowers == true)
		tempInt++;
	if (nipper->passwordEither == true)
		tempInt++;
	if (nipper->passwordNumbers == true)
		tempInt++;
	if (nipper->passwordSpecials == true)
		tempInt++;
	if (nipper->passwordUppers == true)
	{
		fprintf(nipper->reportFile, " uppercase");
		if (tempInt > 2)
			fprintf(nipper->reportFile, ",");
		else if (tempInt == 2)
			fprintf(nipper->reportFile, " and");
		tempInt--;
	}
	if (nipper->passwordLowers == true)
	{
		fprintf(nipper->reportFile, " lowercase");
		if (tempInt > 2)
			fprintf(nipper->reportFile, ",");
		else if (tempInt == 2)
			fprintf(nipper->reportFile, " and");
		tempInt--;
	}
	if (nipper->passwordEither == true)
	{
		fprintf(nipper->reportFile, " either uppercase or lowercase characters");
		if (tempInt > 2)
			fprintf(nipper->reportFile, ",");
		else if (tempInt == 2)
			fprintf(nipper->reportFile, " and");
		tempInt--;
	}
	if (nipper->passwordNumbers == true)
	{
		fprintf(nipper->reportFile, " numbers");
		if (tempInt > 2)
			fprintf(nipper->reportFile, ",");
		else if (tempInt == 2)
			fprintf(nipper->reportFile, " and");
		tempInt--;
	}
	if (nipper->passwordSpecials == true)
	{
		fprintf(nipper->reportFile, " special");
		if (tempInt > 2)
			fprintf(nipper->reportFile, ",");
		else if (tempInt == 2)
			fprintf(nipper->reportFile, " and");
		tempInt--;
	}
	if (((nipper->passwordNumbers == true) && (nipper->passwordSpecials == false)) || ((nipper->passwordEither == false) && (nipper->passwordNumbers == false) && (nipper->passwordSpecials == false)))
		fprintf(nipper->reportFile, ".");
	else
		fprintf(nipper->reportFile, "characters.");
	if (nipper->outputFormat == output_xml)
		fprintf(nipper->reportFile, "</text>\n");
	output_newPara(nipper);
	output_endsection(nipper, section_rec);
}


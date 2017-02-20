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


void output_PIXTablePasswords(struct nipperConfig *nipper, int dictPassword)
{
	// Variables
	char tempString[nipper->maxSize];

	// SNMP
	if (nipper->pix->snmp != 0)
	{
		if (((nipper->pix->snmp->dictionary == true) && (dictPassword == true)) || ((nipper->pix->snmp->weak == true) && (dictPassword == false)))
		{
			fprintf(nipper->reportFile, "%sCommunity%sSNMP%sread-only", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid);
			if (nipper->passwords == true)
			{
				outputFriendly(nipper->pix->snmp->community, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, tempString, nipper->tablerow_end);
			}
			else
				fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
		}
	}
}


void output_PIXLinePasswords(struct nipperConfig *nipper, int dictPassword)
{
	// Variables
	char tempString[nipper->maxSize];
	char tempString2[nipper->maxSize];
	char tempString3[nipper->maxSize];

	// SNMP
	if (nipper->pix->snmp != 0)
	{
		if (((nipper->pix->snmp->dictionary == true) && (dictPassword == true)) || ((nipper->pix->snmp->weak == true) && (dictPassword == false)))
		{
			sprintf(tempString3, "*NOTEXTSTART*The read-only *ABBREV*SNMP*-ABBREV* community string was ");
			if (nipper->passwords == true)
			{
				outputFriendly(nipper->pix->snmp->community, tempString, nipper->maxSize, nipper->outputFormat);
				sprintf(tempString2, "%s%s.", tempString3, tempString);
			}
			else
			{
				if (dictPassword == true)
					sprintf(tempString2, "%sdictionary-based.", tempString3);
				else
					sprintf(tempString2, "%sweak.", tempString3);
			}
		}
	}

	output_parseText(tempString2, nipper, section_none, rate_none, 0, 0);
}


void pixDictionaryIssue(struct nipperConfig *nipper)
{
	// Variables...
	int tempInt = 0;

	output_parseText(report_dict_obs, nipper, section_obs, rate_none, nipper->simplePasswords, nipper->tableNum);
	if (nipper->simplePasswords > 1)
	{
		output_table(nipper, true, report_dict_table, &report_dict_heading);
		output_PIXTablePasswords(nipper, true);
		output_table(nipper, false, report_dict_table, &report_dict_heading);
	}
	else
		output_PIXLinePasswords(nipper, true);
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
		fprintf(nipper->reportFile, "characters.");
	if (nipper->outputFormat == output_xml)
		fprintf(nipper->reportFile, "</text>\n");
	output_newPara(nipper);
	output_endsection(nipper, section_rec);
}


void pixStrengthIssue(struct nipperConfig *nipper)
{
	// Variables...
	int tempInt = 0;

	output_parseText(report_strength_obs, nipper, section_obs, rate_none, nipper->passwordStrengths, nipper->tableNum);
	if (nipper->passwordStrengths > 1)
	{
		output_table(nipper, true, report_strength_table, &report_dict_heading);
		output_PIXTablePasswords(nipper, false);
		output_table(nipper, false, report_strength_table, &report_dict_heading);
	}
	else
		output_PIXLinePasswords(nipper, false);
	output_endsection(nipper, section_obs);
	output_parseText(report_strength_impact, nipper, section_imp, rate_high, nipper->passwordStrengths, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_strength_ease, nipper, section_ease, rate_trivial, nipper->passwordStrengths, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_strength_rec, nipper, section_rec, rate_trivial, nipper->passwordStrengths, nipper->tableNum);
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


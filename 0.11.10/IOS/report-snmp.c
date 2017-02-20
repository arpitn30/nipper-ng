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

void iosSNMPConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct snmpCommunity *communityPointer = 0;
	struct snmpView *snmpViewPointer = 0;
	struct snmpViewItem *snmpViewItemPointer = 0;
	struct snmpGroup *snmpGroupPointer = 0;
	struct snmpUser *snmpUserPointer = 0;
	struct snmpTrap *snmpTrapPointer = 0;
	struct snmpHost *snmpHostPointer = 0;
	char tempString[nipper->maxSize];
	char tempString2[nipper->maxSize];
	int found = false;

	output_parseText(settings_snmp_desc, nipper, section_none, rate_none, 0, 0);
	output_table(nipper, true, settings_snmp_table, &settings_general_heading);
	if (nipper->ios->snmp->enabled == true)
		fprintf(nipper->reportFile, "%sService enabled%sYes%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sService enabled%sNo%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->ios->snmp->contact[0] != 0)
	{
		outputFriendly(nipper->ios->snmp->contact, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%sContact%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
	}
	if (nipper->ios->snmp->location[0] != 0)
	{
		outputFriendly(nipper->ios->snmp->location, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%sLocation%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
	}
	fprintf(nipper->reportFile, "%sTrap Timeout%s%d seconds%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->ios->snmp->trapTimeout, nipper->tablerow_end);
	if (nipper->ios->snmp->trapSource[0] != 0)
	{
		outputFriendly(nipper->ios->snmp->trapSource, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%sTrap Source Interface%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
	}
	if (nipper->ios->snmp->tftpServerList[0] == 0)
		fprintf(nipper->reportFile, "%sTFTP Server List%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
	{
		outputFriendly(nipper->ios->snmp->tftpServerList, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%sTFTP Server List%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
	}
	output_table(nipper, false, settings_snmp_table, &settings_general_heading);
	addAbbreviation("SNMP", false);
	addAbbreviation("TFTP", false);

	if (nipper->ios->snmp->community != 0)
	{
		output_table(nipper, true, settings_snmpstring_table, &settings_snmpstring_heading);
		communityPointer = nipper->ios->snmp->community;
		while (communityPointer != 0)
		{
			fprintf(nipper->reportFile, "%s", nipper->tablerow_start);
			if (nipper->passwords == true)
			{
				outputFriendly(communityPointer->community, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s %s", tempString, nipper->tablerow_mid);
			}
			if (communityPointer->readonly == true)
				fprintf(nipper->reportFile, "Read-Only%s%s%s%s%s", nipper->tablerow_mid, communityPointer->viewName, nipper->tablerow_mid, communityPointer->accessList, nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "Read/Write%s%s%s%s%s", nipper->tablerow_mid, communityPointer->viewName, nipper->tablerow_mid, communityPointer->accessList, nipper->tablerow_mid);
			if (communityPointer->enabled == true)
				fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
			communityPointer = communityPointer->next;
		}
		output_table(nipper, false, settings_snmpstring_table, &settings_snmpstring_heading);
	}

	if (nipper->ios->snmp->group != 0)
	{
		// Groups
		snmpGroupPointer = nipper->ios->snmp->group;
		output_table(nipper, true, settings_snmpgroups_table, &settings_snmpgroups_heading);
		while (snmpGroupPointer != 0)
		{
			outputFriendly(snmpGroupPointer->groupName, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
			switch(snmpGroupPointer->version)
			{
				case snmp1:
					fprintf(nipper->reportFile, "1");
					break;
				case snmp2c:
					fprintf(nipper->reportFile, "2c");
					break;
				case snmp3_no_auth:
					fprintf(nipper->reportFile, "3 (No Auth)");
					break;
				case snmp3_auth:
					fprintf(nipper->reportFile, "3 (Auth)");
					break;
				case snmp3_priv:
					fprintf(nipper->reportFile, "3 (Auth and Priv)");
					break;
			}
			outputFriendly(snmpGroupPointer->readView, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, tempString, nipper->tablerow_mid);
			if (snmpGroupPointer->writeView[0] != 0)
			{
				outputFriendly(snmpGroupPointer->writeView, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
			}
			else
				fprintf(nipper->reportFile, " %s", nipper->tablerow_mid);
			if (snmpGroupPointer->notifyView[0] != 0)
			{
				outputFriendly(snmpGroupPointer->notifyView, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
			}
			else
				fprintf(nipper->reportFile, " %s", nipper->tablerow_mid);
			if (snmpGroupPointer->context[0] != 0)
			{
				outputFriendly(snmpGroupPointer->context, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
			}
			else
				fprintf(nipper->reportFile, " %s", nipper->tablerow_mid);
			if (snmpGroupPointer->acl[0] != 0)
			{
				outputFriendly(snmpGroupPointer->acl, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_end);
			}
			else
				fprintf(nipper->reportFile, " %s", nipper->tablerow_end);
			snmpGroupPointer = snmpGroupPointer->next;
		}
		output_table(nipper, false, settings_snmpgroups_table, &settings_snmpgroups_heading);
		addAbbreviation("OID", false);
		addAbbreviation("MIB", false);
	}

	// Users
	if (nipper->ios->snmp->user != 0)
	{
		// Group Users
		snmpGroupPointer = nipper->ios->snmp->group;
		while (snmpGroupPointer != 0)
		{
			if (nipper->ios->snmp->user != 0)
			{
				switch (snmpGroupPointer->version)
				{
					case snmp1:
					case snmp2c:
					case snmp3_no_auth:
						if (snmpGroupPointer->version == snmp1)
							sprintf(tempString, "%s%s", settings_snmpgroup_table1, snmpGroupPointer->groupName);
						else if (snmpGroupPointer->version == snmp2c)
							sprintf(tempString, "%s%s", settings_snmpgroup_table2, snmpGroupPointer->groupName);
						else if (snmpGroupPointer->version == snmp3_no_auth)
							sprintf(tempString, "%s%s", settings_snmpgroup_table3, snmpGroupPointer->groupName);
						outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
						output_table(nipper, true, tempString2, &settings_snmpnoauth_heading);
						found = false;
						snmpUserPointer = nipper->ios->snmp->user;
						while ((snmpUserPointer != 0) && (found == false))
						{
							if (strcmp(snmpUserPointer->groupName, snmpGroupPointer->groupName) == 0)
								found = true;
							else
								snmpUserPointer = snmpUserPointer->next;
						}
						while (snmpUserPointer != 0)
						{
							if (strcmp(snmpUserPointer->groupName, snmpGroupPointer->groupName) == 0)
							{
								snmpUserPointer->group++;
								outputFriendly(snmpUserPointer->userName, tempString, nipper->maxSize, nipper->outputFormat);
								fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
								if (snmpUserPointer->acl[0] == 0)
									fprintf(nipper->reportFile, " %s", nipper->tablerow_end);
								else
								{
									outputFriendly(snmpUserPointer->acl, tempString, nipper->maxSize, nipper->outputFormat);
									fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_end);
								}
							}
							snmpUserPointer = snmpUserPointer->next;
						}
						output_table(nipper, false, tempString2, &settings_snmpnoauth_heading);
						break;
					case snmp3_auth:
						sprintf(tempString, "%s%s", settings_snmpgroup_table4, snmpGroupPointer->groupName);
						outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
						output_table(nipper, true, tempString2, &settings_snmpauth_heading);
						found = false;
						snmpUserPointer = nipper->ios->snmp->user;
						while ((snmpUserPointer != 0) && (found == false))
						{
							if (strcmp(snmpUserPointer->groupName, snmpGroupPointer->groupName) == 0)
								found = true;
							else
								snmpUserPointer = snmpUserPointer->next;
						}
						while (snmpUserPointer != 0)
						{
							if (strcmp(snmpUserPointer->groupName, snmpGroupPointer->groupName) == 0)
							{
								snmpUserPointer->group++;
								outputFriendly(snmpUserPointer->userName, tempString, nipper->maxSize, nipper->outputFormat);
								fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
								if (nipper->passwords == true)
								{
									outputFriendly(snmpUserPointer->authPass, tempString, nipper->maxSize, nipper->outputFormat);
									fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
								}
								switch (snmpUserPointer->snmp3auth)
								{
									case snmp3_md5:
										fprintf(nipper->reportFile, "MD5%s", nipper->tablerow_mid);
										addAbbreviation("MD5", false);
										break;
									case snmp3_sha:
										fprintf(nipper->reportFile, "SHA%s", nipper->tablerow_mid);
										addAbbreviation("SHA", false);
										break;
								}
								if (snmpUserPointer->acl[0] == 0)
									fprintf(nipper->reportFile, " %s", nipper->tablerow_end);
								else
								{
									outputFriendly(snmpUserPointer->acl, tempString, nipper->maxSize, nipper->outputFormat);
									fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_end);
								}
							}
							snmpUserPointer = snmpUserPointer->next;
						}
						output_table(nipper, false, tempString2, &settings_snmpauth_heading);
						break;
					case snmp3_priv:
						sprintf(tempString, "%s%s", settings_snmpgroup_table4, snmpGroupPointer->groupName);
						outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
						output_table(nipper, true, tempString2, &settings_snmpauth_heading);
						found = false;
						snmpUserPointer = nipper->ios->snmp->user;
						while ((snmpUserPointer != 0) && (found == false))
						{
							if (strcmp(snmpUserPointer->groupName, snmpGroupPointer->groupName) == 0)
								found = true;
							else
								snmpUserPointer = snmpUserPointer->next;
						}
						while (snmpUserPointer != 0)
						{
							if (strcmp(snmpUserPointer->groupName, snmpGroupPointer->groupName) == 0)
							{
								snmpUserPointer->group++;
								outputFriendly(snmpUserPointer->userName, tempString, nipper->maxSize, nipper->outputFormat);
								fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
								if (nipper->passwords == true)
								{
									outputFriendly(snmpUserPointer->authPass, tempString, nipper->maxSize, nipper->outputFormat);
									fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
								}
								switch (snmpUserPointer->snmp3auth)
								{
									case snmp3_md5:
										fprintf(nipper->reportFile, "MD5%s", nipper->tablerow_mid);
										addAbbreviation("MD5", false);
										break;
									case snmp3_sha:
										fprintf(nipper->reportFile, "SHA%s", nipper->tablerow_mid);
										addAbbreviation("SHA", false);
										break;
								}
								if (nipper->passwords == true)
								{
									outputFriendly(snmpUserPointer->privPass, tempString, nipper->maxSize, nipper->outputFormat);
									fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
								}
								switch (snmpUserPointer->snmp3priv)
								{
									case snmp3_des:
										fprintf(nipper->reportFile, "DES%s", nipper->tablerow_mid);
										addAbbreviation("DES", false);
										break;
									case snmp3_3des:
										fprintf(nipper->reportFile, "3DES%s", nipper->tablerow_mid);
										addAbbreviation("3DES", false);
										break;
									case snmp3_des56:
										fprintf(nipper->reportFile, "DES 56%s", nipper->tablerow_mid);
										addAbbreviation("DES", false);
										break;
									case snmp3_aes128:
										fprintf(nipper->reportFile, "AES 128%s", nipper->tablerow_mid);
										addAbbreviation("AES", false);
										break;
									case snmp3_aes192:
										fprintf(nipper->reportFile, "AES 192%s", nipper->tablerow_mid);
										addAbbreviation("AES", false);
										break;
									case snmp3_aes256:
										fprintf(nipper->reportFile, "AES 256%s", nipper->tablerow_mid);
										addAbbreviation("AES", false);
										break;
								}
								if (snmpUserPointer->acl[0] == 0)
									fprintf(nipper->reportFile, " %s", nipper->tablerow_end);
								else
								{
									outputFriendly(snmpUserPointer->acl, tempString, nipper->maxSize, nipper->outputFormat);
									fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_end);
								}
							}
							snmpUserPointer = snmpUserPointer->next;
						}
						output_table(nipper, false, tempString2, &settings_snmpauth_heading);
						break;
				}
			}
			snmpGroupPointer = snmpGroupPointer->next;
		}

		found = false;
		snmpUserPointer = nipper->ios->snmp->user;
		while ((snmpUserPointer != 0) && (found == false))
		{
			if (snmpUserPointer->group == 0)
				found = true;
			else
				snmpUserPointer = snmpUserPointer->next;
		}
		if (snmpUserPointer != 0)
		{
			output_table(nipper, true, settings_snmpgroup_table6, &settings_snmpnoauth_heading);
			while (snmpUserPointer != 0)
			{
				if (snmpUserPointer->group == 0)
				{
					outputFriendly(snmpUserPointer->userName, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
					if (snmpUserPointer->acl[0] == 0)
						fprintf(nipper->reportFile, " %s", nipper->tablerow_end);
					else
					{
						outputFriendly(snmpUserPointer->acl, tempString, nipper->maxSize, nipper->outputFormat);
						fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_end);
					}
				}
				snmpUserPointer = snmpUserPointer->next;
			}
			output_table(nipper, false, settings_snmpgroup_table6, &settings_snmpnoauth_heading);
		}
	}

	// Views
	if (nipper->ios->snmp->view != 0)
	{
		snmpViewPointer = nipper->ios->snmp->view;
		while (snmpViewPointer != 0)
		{
			sprintf(tempString, "%s %s", settings_snmpview_table, snmpViewPointer->viewName);
			outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
			output_table(nipper, true, tempString2, &settings_snmpview_heading);
			snmpViewItemPointer = snmpViewPointer->viewItem;
			while (snmpViewItemPointer != 0)
			{
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, snmpViewItemPointer->mibId, nipper->tablerow_mid);
				if (snmpViewItemPointer->include == true)
					fprintf(nipper->reportFile, "Include%s", nipper->tablerow_end);
				else
					fprintf(nipper->reportFile, "Exclude%s", nipper->tablerow_end);
				snmpViewItemPointer = snmpViewItemPointer->next;
			}
			output_table(nipper, false, tempString2, &settings_snmpview_heading);
			snmpViewPointer = snmpViewPointer->next;
		}
		addAbbreviation("MIB", false);
	}

	if (nipper->ios->snmp->host != 0)
	{
		output_table(nipper, true, settings_snmphost_table, &settings_snmphost_heading);
		snmpHostPointer = nipper->ios->snmp->host;
		while (snmpHostPointer != 0)
		{
			outputFriendly(snmpHostPointer->host, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
			switch(snmpHostPointer->version)
			{
				case snmp1:
					fprintf(nipper->reportFile, "1");
					break;
				case snmp2c:
					fprintf(nipper->reportFile, "2c");
					break;
				case snmp3_no_auth:
					fprintf(nipper->reportFile, "3 (No Auth)");
					break;
				case snmp3_auth:
					fprintf(nipper->reportFile, "3 (Auth)");
					break;
				case snmp3_priv:
					fprintf(nipper->reportFile, "3 (Auth and Priv)");
					break;
			}
			if (nipper->passwords == true)
			{
				outputFriendly(snmpHostPointer->community, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s ", nipper->tablerow_mid, tempString);
			}
			fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
			snmpHostPointer = snmpHostPointer->next;
		}
		output_table(nipper, false, settings_snmphost_table, &settings_snmphost_heading);
	}

	if (nipper->ios->snmp->trap != 0)
	{
		output_table(nipper, true, settings_snmptrap_table, &settings_snmptrap_heading);
		snmpTrapPointer = nipper->ios->snmp->trap;
		while (snmpTrapPointer != 0)
		{
			outputFriendly(snmpTrapPointer->trap, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_end);
			snmpTrapPointer = snmpTrapPointer->next;
		}
		output_table(nipper, false, settings_snmptrap_table, &settings_snmptrap_heading);
	}
}


void iosSNMPIssue(struct nipperConfig *nipper)
{
	output_parseText(settings_snmp_desc, nipper, section_obs, rate_none, 0, nipper->tableNum);
	output_parseText(report_snmp_obs, nipper, section_none, rate_none, nipper->snmpIssue, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_snmp_impact, nipper, section_imp, rate_med, nipper->snmpIssue, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_snmp_ease, nipper, section_ease, rate_trivial, nipper->snmpIssue, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_snmp_rec, nipper, section_rec, rate_none, nipper->snmpIssue, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


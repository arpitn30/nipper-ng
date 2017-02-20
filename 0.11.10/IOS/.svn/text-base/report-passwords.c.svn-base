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


void output_IOSTablePasswords(struct nipperConfig *nipper, int dictPassword)
{
	// Variables
	struct ntpKey *ntpKeyPointer = 0;
	struct enablePassword *enablePointer = 0;
	struct usernameList *usernamePointer = 0;
	struct snmpCommunity *communityPointer = 0;
	struct snmpHost *snmpHostPointer = 0;
	struct aaaGroupServer *aaaGroupPointer = 0;
	struct aaaServer *aaaServerPointer = 0;
	struct interfaceConfig *interfaceConfigPointer = 0;
	struct bgpNeighbor *neighborPointer = 0;
	struct keyChain *keyChainPointer = 0;
	struct keyConfig *keyPointer = 0;
	struct lineConfig *linePointer = 0;
	struct vrrpStruct *vrrpPointer = 0;
	char tempString[nipper->maxSize];

	// Enable passwords
	enablePointer = nipper->ios->enable;
	while (enablePointer != 0)
	{
		if (((enablePointer->dictionary == true) && (dictPassword == true)) || ((enablePointer->weak == true) && (dictPassword == false)))
		{
			outputFriendly(enablePointer->password, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%sPassword%sEnable%sLevel %d", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, enablePointer->level);
			if (nipper->passwords == true)
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, tempString, nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
		}
		enablePointer = enablePointer->next;
	}

	// Usernames
	usernamePointer = nipper->ios->username;
	while (usernamePointer != 0)
	{
		if (((usernamePointer->dictionary == true) && (dictPassword == true)) || ((usernamePointer->weak == true) && (dictPassword == false)))
		{
			outputFriendly(usernamePointer->username, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%sPassword%sUsers%s%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, tempString);
			if (nipper->passwords == true)
			{
				outputFriendly(usernamePointer->password, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, tempString, nipper->tablerow_end);
			}
			else
				fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
		}
		usernamePointer = usernamePointer->next;
	}

	// OSPF
	interfaceConfigPointer = nipper->ios->interface;
	while (interfaceConfigPointer != 0)
	{
		if (((interfaceConfigPointer->ospfDictionary == true) && (dictPassword == true)) || ((interfaceConfigPointer->ospfWeak == true) && (dictPassword == false)))
		{
			outputFriendly(interfaceConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%sKey%sOSPF%s%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, tempString);
			if (nipper->passwords == true)
			{
				outputFriendly(interfaceConfigPointer->ospfKey, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, tempString, nipper->tablerow_end);
			}
			else
				fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
		}
		interfaceConfigPointer = interfaceConfigPointer->next;
	}

	// BGP
	if (nipper->ios->bgp != 0)
	{
		neighborPointer = nipper->ios->bgp->neighbor;
		while (neighborPointer != 0)
		{
			if (((neighborPointer->dictionary == true) && (dictPassword == true)) || ((neighborPointer->weak == true) && (dictPassword == false)))
			{
				outputFriendly(neighborPointer->host, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%sPassword%sBGP%sHost %s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, tempString);
				if (nipper->passwords == true)
				{
					outputFriendly(neighborPointer->password, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, tempString, nipper->tablerow_end);
				}
				else
					fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
			}
			neighborPointer = neighborPointer->next;
		}
	}

	// TACACS
	if (nipper->ios->tacacs != 0)
	{
		if (((nipper->ios->tacacs->dictionary == true) && (dictPassword == true)) || ((nipper->ios->tacacs->weak == true) && (dictPassword == false)))
		{
			outputFriendly(nipper->ios->tacacs->key, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%sKey%sTACACS%sN/A", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid);
			if (nipper->passwords == true)
			{
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, tempString, nipper->tablerow_end);
			}
			else
				fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
		}
	}

	// AAA
	if (nipper->ios->aaa != 0)
	{
		aaaGroupPointer = nipper->ios->aaa->groupServer;
		while (aaaGroupPointer != 0)
		{
			aaaServerPointer = aaaGroupPointer->server;
			while (aaaServerPointer != 0)
			{
				if (((aaaServerPointer->dictionary == true) && (dictPassword == true)) || ((aaaServerPointer->weak == true) && (dictPassword == false)))
				{
					outputFriendly(aaaGroupPointer->username, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%sKey%sAAA%s%s (Host: ", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, tempString);
					outputFriendly(aaaServerPointer->server, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s)", tempString);
					if (nipper->passwords == true)
					{
						outputFriendly(aaaServerPointer->key, tempString, nipper->maxSize, nipper->outputFormat);
						fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, tempString, nipper->tablerow_end);
					}
					else
						fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
				}
				aaaServerPointer = aaaServerPointer->next;
			}
			aaaGroupPointer = aaaGroupPointer->next;
		}
	}

	// NTP
	if (nipper->ios->ntp != 0)
	{
		ntpKeyPointer = nipper->ios->ntp->key;
		while (ntpKeyPointer != 0)
		{
			if (((ntpKeyPointer->dictionary == true) && (dictPassword == true)) || ((ntpKeyPointer->weak == true) && (dictPassword == false)))
			{
				outputFriendly(ntpKeyPointer->key, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%sKey%sNTP%sN/A", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid);
				if (nipper->passwords == true)
					fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, tempString, nipper->tablerow_end);
				else
					fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
			}
			ntpKeyPointer = ntpKeyPointer->next;
		}
	}

	// SNMP
	if (nipper->ios->snmp != 0)
	{
		communityPointer = nipper->ios->snmp->community;
		while (communityPointer != 0)
		{
			if (((communityPointer->dictionary == true) && (dictPassword == true)) || ((communityPointer->weak == true) && (dictPassword == false)))
			{
				fprintf(nipper->reportFile, "%sCommunity%sSNMP%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid);
				if (communityPointer->readonly == true)
					fprintf(nipper->reportFile, "read-only");
				else
					fprintf(nipper->reportFile, "read/write");
				if (nipper->passwords == true)
				{
					outputFriendly(communityPointer->community, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, tempString, nipper->tablerow_end);
				}
				else
					fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
			}
			communityPointer = communityPointer->next;
		}
		snmpHostPointer = nipper->ios->snmp->host;
		while (snmpHostPointer != 0)
		{
			if (((snmpHostPointer->dictionary == true) && (dictPassword == true)) || ((snmpHostPointer->weak == true) && (dictPassword == false)))
			{
				outputFriendly(snmpHostPointer->host, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%sCommunity%sSNMP%sHost: %s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, tempString);
				if (nipper->passwords == true)
				{
					outputFriendly(snmpHostPointer->community, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, tempString, nipper->tablerow_end);
				}
				else
					fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
			}
			snmpHostPointer = snmpHostPointer->next;
		}
	}

	// Keys
	keyChainPointer = nipper->ios->chain;
	while (keyChainPointer != 0)
	{
		keyPointer = keyChainPointer->key;
		while (keyPointer != 0)
		{
			if (((keyPointer->dictionary == true) && (dictPassword == true)) || ((keyPointer->weak == true) && (dictPassword == false)))
			{
				fprintf(nipper->reportFile, "%sKey%sKey Chain%sKey No.: %d", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, keyPointer->keyNumber);
				if (nipper->passwords == true)
				{
					outputFriendly(keyPointer->key, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, tempString, nipper->tablerow_end);
				}
				else
					fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
			}
			keyPointer = keyPointer->next;
		}
		keyChainPointer = keyChainPointer->next;
	}

	// FTP
	if (nipper->ios->ftp != 0)
	{
		if (((nipper->ios->ftp->dictionary == true) && (dictPassword == true)) || ((nipper->ios->ftp->weak == true) && (dictPassword == false)))
		{
			outputFriendly(nipper->ios->ftp->username, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%sPassword%sFTP%s%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, tempString);
			if (nipper->passwords == true)
			{
				outputFriendly(nipper->ios->ftp->password, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, tempString, nipper->tablerow_end);
			}
			else
				fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
		}
	}

	// Line
	linePointer = nipper->ios->line;
	while (linePointer != 0)
	{
		if (((linePointer->dictionary == true) && (dictPassword == true)) || ((linePointer->weak == true) && (dictPassword == false)))
		{
			fprintf(nipper->reportFile, "%sPassword%sLine%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid);
			switch (linePointer->lineType)
			{
				case line_console:
					fprintf(nipper->reportFile, "Console ");
					break;
				case line_vty:
					fprintf(nipper->reportFile, "VTY ");
					break;
				case line_aux:
					fprintf(nipper->reportFile, "AUX ");
					break;
				case line_tty:
					fprintf(nipper->reportFile, "TTY ");
					break;
			}
			if (linePointer->lineNumberEnd > 0)
				fprintf(nipper->reportFile, "lines %d - %d", linePointer->lineNumberStart, linePointer->lineNumberEnd);
			else
				fprintf(nipper->reportFile, "line %d", linePointer->lineNumberStart);
			if (nipper->passwords == true)
			{
				outputFriendly(linePointer->password, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, tempString, nipper->tablerow_end);
			}
			else
				fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
		}
		linePointer = linePointer->next;
	}

	// VRRP Authentication
	interfaceConfigPointer = nipper->ios->interface;
	while (interfaceConfigPointer != 0)
	{
		vrrpPointer = interfaceConfigPointer->vrrp;
		while (vrrpPointer != 0)
		{
			if (((vrrpPointer->dictionary == true) && (dictPassword == true)) || ((vrrpPointer->weak == true) && (dictPassword == false)))
			{
				fprintf(nipper->reportFile, "%sPassword%sVRRP%sGroup ID %d on interface %s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_mid, vrrpPointer->group, interfaceConfigPointer->name);
				if (nipper->passwords == true)
				{
					outputFriendly(vrrpPointer->authString, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, tempString, nipper->tablerow_end);
				}
				else
					fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
			}
			vrrpPointer = vrrpPointer->next;
		}
		interfaceConfigPointer = interfaceConfigPointer->next;
	}
}


void output_IOSLinePasswords(struct nipperConfig *nipper, int dictPassword)
{
	// Variables
	struct ntpKey *ntpKeyPointer = 0;
	struct enablePassword *enablePointer = 0;
	struct usernameList *usernamePointer = 0;
	struct snmpCommunity *communityPointer = 0;
	struct snmpHost *snmpHostPointer = 0;
	struct aaaGroupServer *aaaGroupPointer = 0;
	struct aaaServer *aaaServerPointer = 0;
	struct interfaceConfig *interfaceConfigPointer = 0;
	struct bgpNeighbor *neighborPointer = 0;
	struct keyChain *keyChainPointer = 0;
	struct keyConfig *keyPointer = 0;
	struct lineConfig *linePointer = 0;
	struct vrrpStruct *vrrpPointer = 0;
	char tempString[nipper->maxSize];
	char tempString2[nipper->maxSize];
	char tempString3[nipper->maxSize];

	// Enable
	enablePointer = nipper->ios->enable;
	while (enablePointer != 0)
	{
		if (((enablePointer->dictionary == true) && (dictPassword == true)) || ((enablePointer->weak == true) && (dictPassword == false)))
		{
			outputFriendly(enablePointer->password, tempString, nipper->maxSize, nipper->outputFormat);
			sprintf(tempString3, "*NOTEXTSTART*The enable password (level %d) was ", enablePointer->level);
			if (nipper->passwords == true)
				sprintf(tempString2, "%s%s.", tempString3, tempString);
			else
			{
				if (dictPassword == true)
					sprintf(tempString2, "%sdictionary-based.", tempString3);
				else
					sprintf(tempString2, "%sweak.", tempString3);
			}
		}
		enablePointer = enablePointer->next;
	}

	// Username
	usernamePointer = nipper->ios->username;
	while (usernamePointer != 0)
	{
		if (((usernamePointer->dictionary == true) && (dictPassword == true)) || ((usernamePointer->weak == true) && (dictPassword == false)))
		{
			outputFriendly(usernamePointer->username, tempString, nipper->maxSize, nipper->outputFormat);
			sprintf(tempString3, "*NOTEXTSTART*The user %s had a ", tempString);
			if (nipper->passwords == true)
			{
				outputFriendly(usernamePointer->password, tempString, nipper->maxSize, nipper->outputFormat);
				sprintf(tempString2, "%spassword %s.", tempString3, tempString);
			}
			else
			{
				if (dictPassword == true)
					sprintf(tempString2, "%sdictionary-based password.", tempString3);
				else
					sprintf(tempString2, "%sweak password.", tempString3);
			}
		}
		usernamePointer = usernamePointer->next;
	}

	// OSPF
	interfaceConfigPointer = nipper->ios->interface;
	while (interfaceConfigPointer != 0)
	{
		if (((interfaceConfigPointer->ospfDictionary == true) && (dictPassword == true)) || ((interfaceConfigPointer->ospfWeak == true) && (dictPassword == false)))
		{
			outputFriendly(interfaceConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
			sprintf(tempString3, "*NOTEXTSTART*The network interface %s was configured with ", tempString);
			if (nipper->passwords == true)
			{
				outputFriendly(interfaceConfigPointer->ospfKey, tempString, nipper->maxSize, nipper->outputFormat);
				sprintf(tempString2, "%sthe *ABBREV*OSPF*-ABBREV* key %s.", tempString3, tempString);
			}
			else
			{
				if (dictPassword == true)
					sprintf(tempString2, "%sa dictionary-based *ABBREV*OSPF*-ABBREV* key.", tempString3);
				else
					sprintf(tempString2, "%sa weak *ABBREV*OSPF*-ABBREV* key.", tempString3);
			}
		}
		interfaceConfigPointer = interfaceConfigPointer->next;
	}

	// BGP
	if (nipper->ios->bgp != 0)
	{
		neighborPointer = nipper->ios->bgp->neighbor;
		while (neighborPointer != 0)
		{
			if (((neighborPointer->dictionary == true) && (dictPassword == true)) || ((neighborPointer->weak == true) && (dictPassword == false)))
			{
				outputFriendly(neighborPointer->host, tempString, nipper->maxSize, nipper->outputFormat);
				sprintf(tempString3, "*NOTEXTSTART*The *ABBREV*BGP*-ABBREV* password for host %s was ", tempString);
				if (nipper->passwords == true)
				{
					outputFriendly(neighborPointer->password, tempString, nipper->maxSize, nipper->outputFormat);
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
			neighborPointer = neighborPointer->next;
		}
	}

	// TACACS
	if (nipper->ios->tacacs != 0)
	{
		if (((nipper->ios->tacacs->dictionary == true) && (dictPassword == true)) || ((nipper->ios->tacacs->weak == true) && (dictPassword == false)))
		{
			sprintf(tempString3, "*NOTEXTSTART*The *ABBREV*TACACS*-ABBREV* key was ");
			if (nipper->passwords == true)
			{
				outputFriendly(nipper->ios->tacacs->key, tempString, nipper->maxSize, nipper->outputFormat);
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

	// AAA
	if (nipper->ios->aaa != 0)
	{
		aaaGroupPointer = nipper->ios->aaa->groupServer;
		while (aaaGroupPointer != 0)
		{
			aaaServerPointer = aaaGroupPointer->server;
			while (aaaServerPointer != 0)
			{
				if (((aaaServerPointer->dictionary == true) && (dictPassword == true)) || ((aaaServerPointer->weak == true) && (dictPassword == false)))
				{
					outputFriendly(aaaGroupPointer->username, tempString, nipper->maxSize, nipper->outputFormat);
					sprintf(tempString2, "*NOTEXTSTART*The *ABBREV*AAA*-ABBREV* key for user %s on host ", tempString);
					outputFriendly(aaaServerPointer->server, tempString, nipper->maxSize, nipper->outputFormat);
					sprintf(tempString3, "%s%s was ", tempString2, tempString);
					if (nipper->passwords == true)
					{
						outputFriendly(aaaServerPointer->key, tempString, nipper->maxSize, nipper->outputFormat);
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
				aaaServerPointer = aaaServerPointer->next;
			}
			aaaGroupPointer = aaaGroupPointer->next;
		}
	}

	// NTP
	if (nipper->ios->ntp != 0)
	{
		ntpKeyPointer = nipper->ios->ntp->key;
		while (ntpKeyPointer != 0)
		{
			if (((ntpKeyPointer->dictionary == true) && (dictPassword == true)) || ((ntpKeyPointer->weak == true) && (dictPassword == false)))
			{
				sprintf(tempString3, "*NOTEXTSTART*The *ABBREV*NTP*-ABBREV* key was ");
				if (nipper->passwords == true)
				{
					outputFriendly(ntpKeyPointer->key, tempString, nipper->maxSize, nipper->outputFormat);
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
			ntpKeyPointer = ntpKeyPointer->next;
		}
	}

	// SNMP
	if (nipper->ios->snmp != 0)
	{
		communityPointer = nipper->ios->snmp->community;
		while (communityPointer != 0)
		{
			if (((communityPointer->dictionary == true) && (dictPassword == true)) || ((communityPointer->weak == true) && (dictPassword == false)))
			{
				sprintf(tempString3, "*NOTEXTSTART*The ");
				if (communityPointer->readonly == true)
					sprintf(tempString2, "%sread-only", tempString3);
				else
					sprintf(tempString2, "%sread/write", tempString3);
				sprintf(tempString3, "%s *ABBREV*SNMP*-ABBREV* community string was ", tempString2);
				if (nipper->passwords == true)
				{
					outputFriendly(communityPointer->community, tempString, nipper->maxSize, nipper->outputFormat);
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
			communityPointer = communityPointer->next;
		}
		snmpHostPointer = nipper->ios->snmp->host;
		while (snmpHostPointer != 0)
		{
			if (((snmpHostPointer->dictionary == true) && (dictPassword == true)) || ((snmpHostPointer->weak == true) && (dictPassword == false)))
			{
				outputFriendly(snmpHostPointer->host, tempString, nipper->maxSize, nipper->outputFormat);
				sprintf(tempString3, "*NOTEXTSTART*The *ABBREV*SNMP*-ABBREV* community string for the host %s was ", tempString);
				if (nipper->passwords == true)
				{
					outputFriendly(snmpHostPointer->community, tempString, nipper->maxSize, nipper->outputFormat);
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
			snmpHostPointer = snmpHostPointer->next;
		}
	}

	// Keys
	keyChainPointer = nipper->ios->chain;
	while (keyChainPointer != 0)
	{
		keyPointer = keyChainPointer->key;
		while (keyPointer != 0)
		{
			if (((keyPointer->dictionary == true) && (dictPassword == true)) || ((keyPointer->weak == true) && (dictPassword == false)))
			{
				sprintf(tempString3, "*NOTEXTSTART*The key chain key number %d was ", keyPointer->keyNumber);
				if (nipper->passwords == true)
				{
					outputFriendly(keyPointer->key, tempString, nipper->maxSize, nipper->outputFormat);
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
			keyPointer = keyPointer->next;
		}
		keyChainPointer = keyChainPointer->next;
	}

	// FTP
	if (nipper->ios->ftp != 0)
	{
		if (((nipper->ios->ftp->dictionary == true) && (dictPassword == true)) || ((nipper->ios->ftp->weak == true) && (dictPassword == false)))
		{
			outputFriendly(nipper->ios->ftp->username, tempString, nipper->maxSize, nipper->outputFormat);
			sprintf(tempString3, "*NOTEXTSTART*The *ABBREV*FTP*-ABBREV* password for user %s was ", tempString);
			if (nipper->passwords == true)
			{
				outputFriendly(nipper->ios->ftp->password, tempString, nipper->maxSize, nipper->outputFormat);
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

	// Line
	linePointer = nipper->ios->line;
	while (linePointer != 0)
	{
		if (((linePointer->dictionary == true) && (dictPassword == true)) || ((linePointer->weak == true) && (dictPassword == false)))
		{
			switch (linePointer->lineType)
			{
				case line_console:
					sprintf(tempString2, "*NOTEXTSTART*Console ");
					break;
				case line_vty:
					sprintf(tempString2, "*NOTEXTSTART**ABBREV*VTY*-ABBREV* ");
					break;
				case line_aux:
					sprintf(tempString2, "*NOTEXTSTART**ABBREV*AUX*-ABBREV* ");
					break;
				case line_tty:
					sprintf(tempString2, "*NOTEXTSTART**ABBREV*TTY*-ABBREV* ");
					break;
			}
			if (linePointer->lineNumberEnd > 0)
				sprintf(tempString3, "%slines %d to %d", tempString2, linePointer->lineNumberStart, linePointer->lineNumberEnd);
			else
				sprintf(tempString3, "%sline %d", tempString2, linePointer->lineNumberStart);
			if (nipper->passwords == true)
			{
				outputFriendly(linePointer->password, tempString, nipper->maxSize, nipper->outputFormat);
				sprintf(tempString2, "%s had a password of %s.", tempString3, tempString);
			}
			else
			{
				if (dictPassword == true)
					sprintf(tempString2, "%s was dictionary-based.", tempString3);
				else
					sprintf(tempString2, "%s was weak.", tempString3);
			}
		}
		linePointer = linePointer->next;
	}

	// VRRP Authentication
	interfaceConfigPointer = nipper->ios->interface;
	while (interfaceConfigPointer != 0)
	{
		vrrpPointer = interfaceConfigPointer->vrrp;
		while (vrrpPointer != 0)
		{
			if (((vrrpPointer->dictionary == true) && (dictPassword == true)) || ((vrrpPointer->weak == true) && (dictPassword == false)))
			{
				sprintf(tempString3, "*NOTEXTSTART**ABBREV*VRRP*-ABBREV* group ID %d on interface %s", vrrpPointer->group, interfaceConfigPointer->name);
				if (nipper->passwords == true)
				{
					outputFriendly(vrrpPointer->authString, tempString, nipper->maxSize, nipper->outputFormat);
					sprintf(tempString2, "%s had a password of %s.", tempString3, tempString);
				}
				else
				{
					if (dictPassword == true)
						sprintf(tempString2, "%s was dictionary-based.", tempString3);
					else
						sprintf(tempString2, "%s was weak.", tempString3);
				}
			}
			vrrpPointer = vrrpPointer->next;
		}
		interfaceConfigPointer = interfaceConfigPointer->next;
	}

	output_parseText(tempString2, nipper, section_none, rate_none, 0, 0);
}


void iosDictionaryIssue(struct nipperConfig *nipper)
{
	// Variables...
	int tempInt = 0;

	output_parseText(report_dict_obs, nipper, section_obs, rate_none, nipper->simplePasswords, nipper->tableNum);
	if (nipper->simplePasswords > 1)
	{
		output_table(nipper, true, report_dict_table, &report_dict_heading);
		output_IOSTablePasswords(nipper, true);
		output_table(nipper, false, report_dict_table, &report_dict_heading);
	}
	else
		output_IOSLinePasswords(nipper, true);
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


void iosStrengthIssue(struct nipperConfig *nipper)
{
	// Variables...
	int tempInt = 0;

	output_parseText(report_strength_obs, nipper, section_obs, rate_none, nipper->passwordStrengths, nipper->tableNum);
	if (nipper->passwordStrengths > 1)
	{
		output_table(nipper, true, report_strength_table, &report_dict_heading);
		output_IOSTablePasswords(nipper, false);
		output_table(nipper, false, report_strength_table, &report_dict_heading);
	}
	else
		output_IOSLinePasswords(nipper, false);
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
		fprintf(nipper->reportFile, "characters.");
	if (nipper->outputFormat == output_xml)
		fprintf(nipper->reportFile, "</text>\n");
	output_newPara(nipper);
	output_endsection(nipper, section_rec);
}


void iosEnableSecretIssue(struct nipperConfig *nipper)
{
	output_parseText(report_enablesec_obs, nipper, section_obs, rate_none, nipper->enableIssues, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_enablesec_impact, nipper, section_imp, rate_low, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_enablesec_ease, nipper, section_ease, rate_trivial, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_enablesec_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


void iosPasswordEncryptionIssue(struct nipperConfig *nipper)
{
	output_parseText(report_passenc_obs, nipper, section_obs, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_obs);
	output_parseText(report_passenc_impact, nipper, section_imp, rate_low, 0, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_passenc_ease, nipper, section_ease, rate_trivial, 0, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_passenc_rec, nipper, section_rec, rate_none, 0, nipper->tableNum);
	output_endsection(nipper, section_rec);
}

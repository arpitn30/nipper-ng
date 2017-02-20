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


// Process Zone Lines
void sosZoneConfig(struct nipperConfig *nipper)
{
	// Variables
	struct zoneSOS *zonePointer = 0;
	char tempString[nipper->maxSize];

	output_parseText(settings_zone_desc, nipper, section_none, rate_none, 0, 0);

	// Show zone list and basic options
	output_table(nipper, true, settings_zones_table, &settings_zones_heading);
	zonePointer = nipper->sos->zone;
	while (zonePointer != 0)
	{
		outputFriendly(zonePointer->name, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
		if (zonePointer->id == 0)
			fprintf(nipper->reportFile, "-%s", nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "%d%s", zonePointer->id, nipper->tablerow_mid);
		if (zonePointer->vlan == 0)
			fprintf(nipper->reportFile, "-%s", nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "%d%s", zonePointer->vlan, nipper->tablerow_mid);
		if (zonePointer->block == false)
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_mid);
		if (zonePointer->pbr[0] == 0)
			fprintf(nipper->reportFile, "None%s", nipper->tablerow_mid);
		else
		{
			outputFriendly(zonePointer->pbr, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
		}
		if (zonePointer->tunnel[0] == 0)
			fprintf(nipper->reportFile, "None%s", nipper->tablerow_mid);
		else
		{
			outputFriendly(zonePointer->tunnel, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
		}
		if (zonePointer->vrouter[0] == 0)
			fprintf(nipper->reportFile, "None%s", nipper->tablerow_end);
		else
		{
			outputFriendly(zonePointer->vrouter, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_end);
		}
		zonePointer = zonePointer->next;
	}
	output_table(nipper, false, settings_zones_table, &settings_zones_heading);

	// Zone security settings
	zonePointer = nipper->sos->zone;
	while (zonePointer != 0)
	{
		sprintf(tempString, "%s %s", zonePointer->name, settings_zone_table);
		output_table(nipper, true, tempString, &settings_general_heading);
		fprintf(nipper->reportFile, "%sSend TCP resets for nonsync packets%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->tcpReset == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sRelay DHCP requests to other zones%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->dhcpRelay == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sReassemble HTTP and FTP fragmented packets for ALG%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->reasembleForALG == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sGenerate attack alarms but do not block%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->alarmWithoutDrop == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sApply the security settings to tunnels%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->tunnel[0] == 0)
			fprintf(nipper->reportFile, "N/A%s", nipper->tablerow_end);
		else if (zonePointer->onTunnel == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sDrop fragmented packets%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->blockFrag == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sDrop HTTP traffic containing ActiveX%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->activeX == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sDrop HTTP traffic containing Java%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->java == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sDrop HTTP traffic containing executables%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->exe == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sDrop HTTP traffic containing ZIP files%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->zip == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sDrop HTTP traffic containing malformed URL%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->malformedUrl == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sDrop packets with illegal flags%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->flagDrop == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		if (zonePointer->icmpFlood > 0)
			fprintf(nipper->reportFile, "%sDrop ICMP traffic after%s%ld per second%s", nipper->tablerow_start, nipper->tablerow_mid, zonePointer->icmpFlood, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "%sDrop ICMP traffic flood%sNo%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sDrop ICMP traffic with fragments flag%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->icmpFrag == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sDrop ICMP frames larger than 1024%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->icmpLarge == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sDrop packets with invalid IP options%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->ipBadOptions == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sDrop packets with IP source route option%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->ipSourceRoute == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sDrop packets with no or malformed flags%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->noFlag == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sDrop IP frames with a protocol number greater than 135%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->unknownProtocol == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sDrop ping of death attacks%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->pingOfDeath == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sPrevent spoofing attacks%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->ipSpoofing == sos_spoofing_off)
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		else if (zonePointer->ipSpoofing == sos_spoofing_interface)
			fprintf(nipper->reportFile, "Based on interfaces%s", nipper->tablerow_end);
		else if (zonePointer->ipSpoofing == sos_spoofing_routing)
			fprintf(nipper->reportFile, "Based on route%s", nipper->tablerow_end);
		else if (zonePointer->ipSpoofing == sos_spoofing_zone)
			fprintf(nipper->reportFile, "Based on zone%s", nipper->tablerow_end);
		if (zonePointer->ipSweep == 0)
			fprintf(nipper->reportFile, "%sPrevent IP sweep attacks%sNo%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "%sPrevent IP sweep attacks after 10 ICMP echos%sPer %ld microseconds%s", nipper->tablerow_start, nipper->tablerow_mid, zonePointer->ipSweep, nipper->tablerow_end);
		if (zonePointer->portScan == 0)
			fprintf(nipper->reportFile, "%sPrevent port scans%sNo%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "%sPrevent port scans after 10 ports%sPer %ld microseconds%s", nipper->tablerow_start, nipper->tablerow_mid, zonePointer->portScan, nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sPrevent Land attacks%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->land == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sPrevent SYN ACK ACK attacks%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->synAckAck == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sPrevent SYN flood attacks%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->synFlood == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sDetect SYN FIN attacks%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->synFin == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sPrevent SYN frag attacks%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->synFrags == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sPrevent tear drop attacks%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->tearDrop == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sPrevent UDP floods%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->udpFlood == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sLog packets with a loose IP source route%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->ipLooseSource == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sLog packets with the record route option%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->ipRecordRoute == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sLog packets with the security option%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->ipSecurityOption == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sLog packets with the stream option%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->ipStream == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sLog packets with the strict source option%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->strictSource == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sLog packets with the timestamp option%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->ipTimestamp == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sLimit concurrent sessions%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->limitSessions > 0 )
			fprintf(nipper->reportFile, "%d sessions%s", zonePointer->limitSessions, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sDetect and modify NetBIOS attack packets%s", nipper->tablerow_start, nipper->tablerow_mid);
		if (zonePointer->winNuke == true )
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
		output_table(nipper, false, tempString, &settings_general_heading);

		zonePointer = zonePointer->next;
	}
	
	addAbbreviation("TCP", false);
	addAbbreviation("DHCP", false);
	addAbbreviation("HTTP", false);
	addAbbreviation("FTP", false);
	addAbbreviation("ALG", false);
	addAbbreviation("ICMP", false);
	addAbbreviation("IP", false);
}


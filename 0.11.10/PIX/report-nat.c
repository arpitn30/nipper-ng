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


void pixNATPATConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct staticPIX *staticPIXPointer = 0;
	char tempString[nipper->maxSize];

	output_parseText(settings_natpat_desc, nipper, section_none, rate_none, 1, 0);
	if (nipper->pix->staticNAT !=0)
	{
		output_table(nipper, true, settings_nat_static_table, &settings_nat_static_heading);
		staticPIXPointer = nipper->pix->staticNAT;
		while (staticPIXPointer != 0)
		{
			outputFriendly(staticPIXPointer->interfaceReal, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
			if (staticPIXPointer->interface == true)
				fprintf(nipper->reportFile, "Interface");
			else if (staticPIXPointer->accessList[0] != 0)
			{
				outputFriendly(staticPIXPointer->accessList, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "ACL: %s", tempString);
				addAbbreviation("ACL", false);
			}
			else if (staticPIXPointer->ipNetMaskReal[0] != 0)
				fprintf(nipper->reportFile, "%s %s", staticPIXPointer->ipReal, staticPIXPointer->ipNetMaskReal);
			else
				fprintf(nipper->reportFile, "%s", staticPIXPointer->ipReal);
			outputFriendly(staticPIXPointer->interfaceMapped, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, tempString, nipper->tablerow_mid);
			outputFriendly(staticPIXPointer->ipMapped, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
			if (staticPIXPointer->dns == true)
				fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "No%s", nipper->tablerow_mid);
			if (staticPIXPointer->randomseq == true)
				fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "No%s", nipper->tablerow_mid);
			if (staticPIXPointer->nailed == true)
				fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "No%s", nipper->tablerow_mid);
			if (staticPIXPointer->tcpMaxConnections == 0)
				fprintf(nipper->reportFile, "Unlimited%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "%d%s", staticPIXPointer->tcpMaxConnections, nipper->tablerow_mid);
			if (staticPIXPointer->embrionicConnections == 0)
				fprintf(nipper->reportFile, "Unlimited%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "%d%s", staticPIXPointer->embrionicConnections, nipper->tablerow_mid);
			if (staticPIXPointer->udpMaxConnections == 0)
				fprintf(nipper->reportFile, "Unlimited%s", nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "%d%s", staticPIXPointer->udpMaxConnections, nipper->tablerow_end);

			staticPIXPointer = staticPIXPointer->next;
		}
		output_table(nipper, false, settings_nat_static_table, &settings_nat_static_heading);
	}
	if (nipper->pix->staticPAT !=0)
	{
		output_table(nipper, true, settings_pat_static_table, &settings_pat_static_heading);
		staticPIXPointer = nipper->pix->staticPAT;
		while (staticPIXPointer != 0)
		{
			outputFriendly(staticPIXPointer->interfaceReal, tempString, nipper->maxSize, nipper->outputFormat);
			if (staticPIXPointer->protocolTcp == true)
				fprintf(nipper->reportFile, "%sTCP%s", nipper->tablerow_start, nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "%sUDP%s", nipper->tablerow_start, nipper->tablerow_mid);
			fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
			if (staticPIXPointer->interface == true)
				fprintf(nipper->reportFile, "Interface");
			else if (staticPIXPointer->accessList[0] != 0)
			{
				outputFriendly(staticPIXPointer->accessList, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "ACL: %s", tempString);
				addAbbreviation("ACL", false);
			}
			else if (staticPIXPointer->ipNetMaskReal[0] != 0)
				fprintf(nipper->reportFile, "%s %s", staticPIXPointer->ipReal, staticPIXPointer->ipNetMaskReal);
			else
				fprintf(nipper->reportFile, "%s", staticPIXPointer->ipReal);
			fprintf(nipper->reportFile, " (%s)", staticPIXPointer->portReal);
			outputFriendly(staticPIXPointer->interfaceMapped, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, tempString, nipper->tablerow_mid);
			outputFriendly(staticPIXPointer->ipMapped, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s (%s)%s", tempString, staticPIXPointer->portMapped, nipper->tablerow_mid);
			if (staticPIXPointer->dns == true)
				fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "No%s", nipper->tablerow_mid);
			if (staticPIXPointer->randomseq == true)
				fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "No%s", nipper->tablerow_mid);
			if (staticPIXPointer->nailed == true)
				fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "No%s", nipper->tablerow_mid);
			if (staticPIXPointer->tcpMaxConnections == 0)
				fprintf(nipper->reportFile, "Unlimited%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "%d%s", staticPIXPointer->tcpMaxConnections, nipper->tablerow_mid);
			if (staticPIXPointer->embrionicConnections == 0)
				fprintf(nipper->reportFile, "Unlimited%s", nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "%d%s", staticPIXPointer->embrionicConnections, nipper->tablerow_mid);
			if (staticPIXPointer->udpMaxConnections == 0)
				fprintf(nipper->reportFile, "Unlimited%s", nipper->tablerow_end);
			else
				fprintf(nipper->reportFile, "%d%s", staticPIXPointer->udpMaxConnections, nipper->tablerow_end);

			staticPIXPointer = staticPIXPointer->next;
		}
		output_table(nipper, false, settings_pat_static_table, &settings_pat_static_heading);
	}
}


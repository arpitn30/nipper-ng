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


void pixInterfaceConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct interfacePIXConfig *interfacePIXConfigPointer = 0;
	char tempString[nipper->maxSize];

	output_table(nipper, true, settings_inter_table, &settings_interpix_heading);
	interfacePIXConfigPointer = nipper->pix->interface;
	while (interfacePIXConfigPointer != 0)
	{
		fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, interfacePIXConfigPointer->interface, nipper->tablerow_mid);
		outputFriendly(interfacePIXConfigPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
		if (interfacePIXConfigPointer->shutdown == true)
			fprintf(nipper->reportFile, "Yes");
		else
			fprintf(nipper->reportFile, "No");
		fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, interfacePIXConfigPointer->ipAddress, nipper->tablerow_mid);
		fprintf(nipper->reportFile, "%s%s", interfacePIXConfigPointer->netMask, nipper->tablerow_mid);
		fprintf(nipper->reportFile, "%d%s", interfacePIXConfigPointer->security, nipper->tablerow_mid);
		if (interfacePIXConfigPointer->uRPF == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_mid);
		if (interfacePIXConfigPointer->in[0] == 0)
			fprintf(nipper->reportFile, " %s", nipper->tablerow_mid);
		else
		{
			outputFriendly(interfacePIXConfigPointer->in, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
		}
		if (interfacePIXConfigPointer->out[0] == 0)
			fprintf(nipper->reportFile, " ");
		else
		{
			outputFriendly(interfacePIXConfigPointer->out, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s", tempString);
		}
		fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
		interfacePIXConfigPointer = interfacePIXConfigPointer->next;
	}
	output_table(nipper, false, settings_inter_table, &settings_interpix_heading);
	addAbbreviation("ACL", false);
	addAbbreviation("MTU", false);
	addAbbreviation("IP", false);
}


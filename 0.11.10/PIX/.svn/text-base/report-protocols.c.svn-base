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


void pixProtocolConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct fixupList *fixupPIXPointer = 0;

	// Intro
	output_parseText(settings_protoinspect_desc, nipper, section_none, rate_none, 0, 0);
	if (nipper->pix->fixup != 0)
	{
		output_table(nipper, true, settings_protoinspect_table, &settings_protoinspect_heading);
		fixupPIXPointer = nipper->pix->fixup;
		while (fixupPIXPointer != 0)
		{
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, fixupPIXPointer->protocol, nipper->tablerow_mid);
			addAbbreviation(fixupPIXPointer->protocol, false);
			if (fixupPIXPointer->enabled == true)
				fprintf(nipper->reportFile, "Yes");
			else
				fprintf(nipper->reportFile, "No");
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, fixupPIXPointer->options, nipper->tablerow_end);
			fixupPIXPointer = fixupPIXPointer->next;
		}
		output_table(nipper, false, settings_protoinspect_table, &settings_protoinspect_heading);
	}
}


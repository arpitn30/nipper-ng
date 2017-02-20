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

void cleanup(struct nipperConfig *nipper)
{
	// Program variables...
	struct debugAbbrev *debugAbPointer = 0;
	struct johnPassword *johnPointer = 0;
	struct reportText *reportTextPointer = 0;
	struct filterObjectConfig *filterObjectPointer = 0;
	struct filterConfig *filterPointer = 0;
	struct filterListConfig *filterListPointer = 0;
	struct objectListConfig *objectListPointer = 0;
	struct objectConfig *objectPointer = 0;
	struct objectMember *memberPointer = 0;
	struct hostInterfaces *fw1InterfacePointer = 0;

	// Debug Abbreviations
	while (debugAb != 0)
	{
		debugAbPointer = debugAb->next;
		free(debugAb);
		debugAb = debugAbPointer;
	}

	// CSS from config...
	if (nipper->cssFromConfig != 0)
		free(nipper->cssFromConfig);

	// Device Model from config...
	if (nipper->deviceModelInt != 0)
		free(nipper->deviceModelInt);

	// Dict file from config...
	if (nipper->dictionaryFilename != 0)
		free(nipper->dictionaryFilename);

	// If Dict file is open...
	if (nipper->dictFile != 0)
		fclose(nipper->dictFile);

	// Filter Lists...
	while (nipper->filterList != 0)
	{
		while (nipper->filterList->filter != 0)
		{
			while (nipper->filterList->filter->source != 0)
			{
				filterObjectPointer = nipper->filterList->filter->source->next;
				free (nipper->filterList->filter->source);
				nipper->filterList->filter->source = filterObjectPointer;
			}
			while (nipper->filterList->filter->sourceService != 0)
			{
				filterObjectPointer = nipper->filterList->filter->sourceService->next;
				free (nipper->filterList->filter->sourceService);
				nipper->filterList->filter->sourceService = filterObjectPointer;
			}
			while (nipper->filterList->filter->destination != 0)
			{
				filterObjectPointer = nipper->filterList->filter->destination->next;
				free (nipper->filterList->filter->destination);
				nipper->filterList->filter->destination = filterObjectPointer;
			}
			while (nipper->filterList->filter->destinationService != 0)
			{
				filterObjectPointer = nipper->filterList->filter->destinationService->next;
				free (nipper->filterList->filter->destinationService);
				nipper->filterList->filter->destinationService = filterObjectPointer;
			}
			while (nipper->filterList->filter->through != 0)
			{
				filterObjectPointer = nipper->filterList->filter->through->next;
				free (nipper->filterList->filter->through);
				nipper->filterList->filter->through = filterObjectPointer;
			}
			while (nipper->filterList->filter->install != 0)
			{
				filterObjectPointer = nipper->filterList->filter->install->next;
				free (nipper->filterList->filter->install);
				nipper->filterList->filter->install = filterObjectPointer;
			}
			filterPointer = nipper->filterList->filter->next;
			free (nipper->filterList->filter);
			nipper->filterList->filter = filterPointer;
		}
		filterListPointer = nipper->filterList->next;
		free (nipper->filterList);
		nipper->filterList = filterListPointer;
	}

	// Object Lists and Objects...
	while (nipper->objectList != 0)
	{
		while (nipper->objectList->object != 0)
		{
			while (nipper->objectList->object->members != 0)
			{
				memberPointer = nipper->objectList->object->members->next;
				free (nipper->objectList->object->members);
				nipper->objectList->object->members = memberPointer;
			}
			while (nipper->objectList->object->interfaces != 0)
			{
				fw1InterfacePointer = nipper->objectList->object->interfaces->next;
				free (nipper->objectList->object->interfaces);
				nipper->objectList->object->interfaces = fw1InterfacePointer;
			}
			objectPointer = nipper->objectList->object->next;
			free (nipper->objectList->object);
			nipper->objectList->object = objectPointer;
		}
		objectListPointer = nipper->objectList->next;
		free (nipper->objectList);
		nipper->objectList = objectListPointer;
	}

	// Cleanup device type structures
	switch (nipper->deviceType)
	{
		case type_ios_router:
		case type_ios_switch:
		case type_ios_catalyst:
			if (nipper->ios != 0)
				cleanupIOS(nipper);
			break;

		case type_pix_firewall:
		case type_asa_firewall:
		case type_fwsm_firewall:
			if (nipper->pix != 0)
				cleanupPIX(nipper);
			break;

		case type_cos_catalyst:
		case type_nmp_catalyst:
			if (nipper->nmp != 0)
				cleanupNMP(nipper);
			break;

		case type_css_filter:
			if (nipper->css != 0)
				cleanupCSS(nipper);
			break;

		case type_sos_firewall:
			if (nipper->sos != 0)
				cleanupSOS(nipper);
			break;

		case type_bayaccelar:
		case type_passport:
			if (nipper->pas != 0)
				cleanupPAS(nipper);
			break;

		case type_nokiaip:
		case type_fw1_firewall:
			if (nipper->fw1 != 0)
				cleanupFW1(nipper);
			break;

		case type_sonicwall:
			if (nipper->sonicos != 0)
				cleanupSonicOS(nipper);
			break;
	}

	// Cleanup report text
	while (nipper->report != 0)
	{
		reportTextPointer = nipper->report->next;
		free(nipper->report);
		nipper->report = reportTextPointer;
	}

	// Cleanup John-the-ripper
	while (nipper->john != 0)
	{
		johnPointer = nipper->john->next;
		free(nipper->john);
		nipper->john = johnPointer;
	}

	// Cleanup nipper struct...
	free (nipper);
}


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
 *      2. Any code that makes use of this library MUST display the        *
 *         returned text of the Nipper::getVersion() method. Since the     *
 *         text returned includes the version details and copyright of     *
 *         the library, the sugested place to show it would be with the    *
 *         callers "about program" information.                            *
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

// Includes...
#include "../../globaldefs.h"
#include "../device.h"


void Device::numberReportSections()
{
	// Variables...
	securityIssueStruct *securityPointer = 0;
	configReportStruct *configPointer = 0;
	int sectionNumber = 1;
	int subSectionNumber = 1;

	// Sort out the numbering for the introduction report section...
	configPointer = reportIntro;
	if (configPointer != 0)
	{
		while (configPointer != 0)
		{
			configPointer->section = sectionNumber;
			configPointer->subsection = subSectionNumber;
			subSectionNumber++;
			configPointer = configPointer->next;
		}
		sectionNumber++;
	}

	// Sort out the numbering for the security report section...
	if ((config->includeSecurityAudit == true) && (securityReport != 0))
	{
		subSectionNumber = 1;
		securityPointer = securityReport;
		while (securityPointer != 0)
		{
			securityPointer->section = sectionNumber;
			securityPointer->subsection = subSectionNumber;
			subSectionNumber++;
			securityPointer = securityPointer->next;
		}
		sectionNumber++;
	}

	// Sort out the numbering for the configuration report section...
	if ((config->includeConfigurationReport == true) && (configReport != 0))
	{
		subSectionNumber = 1;
		configPointer = configReport;
		while (configPointer != 0)
		{
			configPointer->section = sectionNumber;
			configPointer->subsection = subSectionNumber;
			subSectionNumber++;
			configPointer = configPointer->next;
		}
		sectionNumber++;
	}

	// Sort out the numbering for the appendix report section...
	if ((config->includeAppendixSection == true) && (appendixReport != 0))
	{
		subSectionNumber = 1;
		configPointer = appendixReport;
		while (configPointer != 0)
		{
			configPointer->section = sectionNumber;
			configPointer->subsection = subSectionNumber;
			subSectionNumber++;
			configPointer = configPointer->next;
		}
		sectionNumber++;
	}
}


void Device::numberReportTables()
{
	// Variables...
	securityIssueStruct *securityPointer = 0;
	configReportStruct *configPointer = 0;
	paragraphStruct *paragraphPointer = 0;
	int tableNumber = 0;
	string tempString;

	configPointer = reportIntro;
	while (configPointer != 0)
	{
		paragraphPointer = configPointer->config;
		while (paragraphPointer != 0)
		{
			if (paragraphPointer->table != 0)
			{
				tableNumber++;
				paragraphPointer->table->number = tableNumber;
				if (paragraphPointer->table->reference.empty())
				{
					tempString.assign("TABLEREF");
					tempString.append(intToString(tableNumber));
					paragraphPointer->table->reference.assign(tempString.c_str());
				}
			}
			paragraphPointer = paragraphPointer->next;
		}

		configPointer = configPointer->next;
	}

	// Sort out the table numbering for the security report section...
	if (config->includeSecurityAudit == true)
	{
		securityPointer = securityReport;
		while (securityPointer != 0)
		{
			// Finding...
			paragraphPointer = securityPointer->finding;
			while (paragraphPointer != 0)
			{
				if (paragraphPointer->table != 0)
				{
					tableNumber++;
					paragraphPointer->table->number = tableNumber;
					if (paragraphPointer->table->reference.empty())
					{
						tempString.assign("TABLEREF");
						tempString.append(intToString(tableNumber));
						paragraphPointer->table->reference.assign(tempString.c_str());
					}
				}
				paragraphPointer = paragraphPointer->next;
			}
	
			// Impact...
			paragraphPointer = securityPointer->impact;
			while (paragraphPointer != 0)
			{
				if (paragraphPointer->table != 0)
				{
					tableNumber++;
					paragraphPointer->table->number = tableNumber;
					if (paragraphPointer->table->reference.empty())
					{
						tempString.assign("TABLEREF");
						tempString.append(intToString(tableNumber));
						paragraphPointer->table->reference.assign(tempString.c_str());
					}
				}
				paragraphPointer = paragraphPointer->next;
			}
	
			// Recommendation...
			paragraphPointer = securityPointer->recommendation;
			while (paragraphPointer != 0)
			{
				if (paragraphPointer->table != 0)
				{
					tableNumber++;
					paragraphPointer->table->number = tableNumber;
					if (paragraphPointer->table->reference.empty())
					{
						tempString.assign("TABLEREF");
						tempString.append(intToString(tableNumber));
						paragraphPointer->table->reference.assign(tempString.c_str());
					}
				}
				paragraphPointer = paragraphPointer->next;
			}
	
			securityPointer = securityPointer->next;
		}
	}

	// Sort out the table numbering for the configuration report section...
	if (config->includeConfigurationReport == true)
	{
		configPointer = configReport;
		while (configPointer != 0)
		{
			paragraphPointer = configPointer->config;
			while (paragraphPointer != 0)
			{
				if (paragraphPointer->table != 0)
				{
					tableNumber++;
					paragraphPointer->table->number = tableNumber;
					if (paragraphPointer->table->reference.empty())
					{
						tempString.assign("TABLEREF");
						tempString.append(intToString(tableNumber));
						paragraphPointer->table->reference.assign(tempString.c_str());
					}
				}
				paragraphPointer = paragraphPointer->next;
			}

			configPointer = configPointer->next;
		}
	}

	if (config->includeAppendixSection == true)
	{
		configPointer = appendixReport;
		while (configPointer != 0)
		{
			paragraphPointer = configPointer->config;
			while (paragraphPointer != 0)
			{
				if (paragraphPointer->table != 0)
				{
					tableNumber++;
					paragraphPointer->table->number = tableNumber;
					if (paragraphPointer->table->reference.empty())
					{
						tempString.assign("TABLEREF");
						tempString.append(intToString(tableNumber));
						paragraphPointer->table->reference.assign(tempString.c_str());
					}
				}
				paragraphPointer = paragraphPointer->next;
			}

			configPointer = configPointer->next;
		}
	}
}


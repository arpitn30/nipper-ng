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


// Goes through the security issues, re-ordering them...
void Device::reorderSecurityIssues()
{
	// Variables...
	securityIssueStruct *previousIssuePointer = 0;		// The previous issue
	securityIssueStruct *securityIssuePointer = 0;		// The current issue
	securityIssueStruct *searchIssuePointer = 0;		// The search through the issues
	securityIssueStruct *searchPreviousPointer = 0;		// The search through the issues

	securityIssuePointer = securityReport;
	while (securityIssuePointer != 0)
	{

		// Only if it is an issue
		if (securityIssuePointer->position == 3)
		{

			// Look for more significant issues...
			searchIssuePointer = securityIssuePointer->next;
			searchPreviousPointer = securityIssuePointer;
			while (searchIssuePointer != 0)
			{
				// If issue is more significant...
				if ((securityIssuePointer->overallRating < searchIssuePointer->overallRating) || ((securityIssuePointer->overallRating == searchIssuePointer->overallRating) && (securityIssuePointer->impactRating < searchIssuePointer->impactRating)) || ((securityIssuePointer->overallRating == searchIssuePointer->overallRating) && (securityIssuePointer->impactRating == searchIssuePointer->impactRating) && (securityIssuePointer->easeRating < searchIssuePointer->easeRating)) || ((securityIssuePointer->overallRating == searchIssuePointer->overallRating) && (securityIssuePointer->impactRating == searchIssuePointer->impactRating) && (securityIssuePointer->easeRating == searchIssuePointer->easeRating) && (securityIssuePointer->fixRating < searchIssuePointer->fixRating)))
				{
					searchPreviousPointer->next = searchIssuePointer->next;
					searchIssuePointer->next = securityIssuePointer;

					if (previousIssuePointer == 0)
						securityReport = searchIssuePointer;
					else
						previousIssuePointer->next = searchIssuePointer;

					securityIssuePointer = searchIssuePointer;
				}
				else
					searchPreviousPointer = searchIssuePointer;
				searchIssuePointer = searchIssuePointer->next;
			}
		}
		previousIssuePointer = securityIssuePointer;
		securityIssuePointer = securityIssuePointer->next;
	}
}

// Goes through the security audit resolving all references...
void Device::resolveRelatedIssues()
{
	// Variables...
	paragraphStruct *paragraphPointer = 0;
	securityIssueStruct *securityIssuePointer = 0;
	securityIssueStruct *searchIssuePointer = 0;
	listStruct *relatedIssuePointer = 0;
	string tempString;
	int itemCount = 0;
	bool found = false;

	// Step through each issue...
	securityIssuePointer = securityReport;
	while (securityIssuePointer != 0)
	{
		itemCount = 0;

		// Step through each related issue reference...
		relatedIssuePointer = securityIssuePointer->related;
		while (relatedIssuePointer != 0)
		{
			found = false;

			// Find if the issue exists and count them...
			searchIssuePointer = securityReport;
			while ((searchIssuePointer != 0) && (found == false))
			{
				if (relatedIssuePointer->listItem.compare(searchIssuePointer->reference) == 0)
				{
					itemCount++;
					found = true;
				}
				else
					searchIssuePointer = searchIssuePointer->next;
			}
			relatedIssuePointer = relatedIssuePointer->next;
		}

		// Create the reference list...
		if (itemCount > 0)
		{

			// Opening paragraph text...
			paragraphPointer = addParagraph(securityIssuePointer, Device::Recommendation);
			if (itemCount > 1)
				paragraphPointer->paragraph.assign(i18n("Related security issues:"));
			else
				paragraphPointer->paragraph.assign(i18n("Related security issue:"));

			// Step through each related issue reference...
			relatedIssuePointer = securityIssuePointer->related;
			while (relatedIssuePointer != 0)
			{
				found = false;

				// Add each issue to the reference list...
				searchIssuePointer = securityReport;
				while ((searchIssuePointer != 0) && (found == false))
				{
					if (relatedIssuePointer->listItem.compare(searchIssuePointer->reference) == 0)
					{
						tempString.assign(searchIssuePointer->title);
						tempString.append(" (see section *SECTIONNO*)");
						addListItem(paragraphPointer, tempString.c_str());
						addString(paragraphPointer, relatedIssuePointer->listItem.c_str());
						found = true;
					}
					else
						searchIssuePointer = searchIssuePointer->next;
				}
				relatedIssuePointer = relatedIssuePointer->next;
			}

		}

		securityIssuePointer = securityIssuePointer->next;
	}
}


// Goes through the security audit resolving all references...
void Device::resolveDependentIssues()
{
	// Variables...
	paragraphStruct *paragraphPointer = 0;
	securityIssueStruct *securityIssuePointer = 0;
	securityIssueStruct *searchIssuePointer = 0;
	listStruct *relatedIssuePointer = 0;
	string tempString;
	int itemCount = 0;
	bool found = false;

	// Step through each issue...
	securityIssuePointer = securityReport;
	while (securityIssuePointer != 0)
	{
		itemCount = 0;

		// Step through each dependent issue reference...
		relatedIssuePointer = securityIssuePointer->dependent;
		while (relatedIssuePointer != 0)
		{
			found = false;

			// Find if the issue exists and count them...
			searchIssuePointer = securityReport;
			while ((searchIssuePointer != 0) && (found == false))
			{
				if (relatedIssuePointer->listItem.compare(searchIssuePointer->reference) == 0)
				{
					itemCount++;
					found = true;
				}
				else
					searchIssuePointer = searchIssuePointer->next;
			}
			relatedIssuePointer = relatedIssuePointer->next;
		}

		// Create the reference list...
		if (itemCount > 0)
		{

			// Opening paragraph text...
			paragraphPointer = addParagraph(securityIssuePointer, Device::Recommendation);
			if (itemCount > 1)
				paragraphPointer->paragraph.assign(i18n("This issue is dependent on the following security issues:"));
			else
				paragraphPointer->paragraph.assign(i18n("This issue is dependent on the following security issue:"));

			// Step through each dependent issue reference...
			relatedIssuePointer = securityIssuePointer->dependent;
			while (relatedIssuePointer != 0)
			{
				found = false;

				// Add each issue to the reference list...
				searchIssuePointer = securityReport;
				while ((searchIssuePointer != 0) && (found == false))
				{
					if (relatedIssuePointer->listItem.compare(searchIssuePointer->reference) == 0)
					{
						tempString.assign(searchIssuePointer->title);
						tempString.append(" (see section *SECTIONNO*)");
						addListItem(paragraphPointer, tempString.c_str());
						addString(paragraphPointer, relatedIssuePointer->listItem.c_str());
						found = true;
					}
					else
						searchIssuePointer = searchIssuePointer->next;
				}
				relatedIssuePointer = relatedIssuePointer->next;
			}

		}

		securityIssuePointer = securityIssuePointer->next;
	}
}


int Device::addPasswordRequirements(paragraphStruct *paragraph)
{
	// Variables...
	int errorCode = 0;

	// Password length...
	if (config->minimumPasswordLength > 1)
		errorCode = addListItem(paragraph, i18n("are at least *NUMBER* characters in length"));
	else
		errorCode = addListItem(paragraph, i18n("are at least *NUMBER* character in length"));
	if (errorCode != 0)
		return errorCode;
	errorCode = addValue(paragraph, config->minimumPasswordLength);
	if (errorCode != 0)
		return errorCode;

	// Uppercase...
	if (config->passwordsMustIncludeUppers == true)
	{
		errorCode = addListItem(paragraph, i18n("must include uppercase characters"));
		if (errorCode != 0)
			return errorCode;
	}

	// Lowercase...
	if (config->passwordsMustIncludeLowers == true)
	{
		errorCode = addListItem(paragraph, i18n("must include lowercase characters"));
		if (errorCode != 0)
			return errorCode;
	}

	// Either case...
	if ((config->passwordsMustIncludeEitherCase == true) && (config->passwordsMustIncludeUppers == false) && (config->passwordsMustIncludeLowers == false))
	{
		errorCode = addListItem(paragraph, i18n("must include uppercase or lowercase characters"));
		if (errorCode != 0)
			return errorCode;
	}

	// Numbers...
	if (config->passwordsMustIncludeNumbers == true)
	{
		errorCode = addListItem(paragraph, i18n("must include numbers"));
		if (errorCode != 0)
			return errorCode;
	}

	// Specials...
	if (config->passwordsMustIncludeSpecials == true)
		errorCode = addListItem(paragraph, i18n("must include non-alphanumeric characters"));

	// Username...
	if (config->differentFromUsername == true)
		errorCode = addListItem(paragraph, i18n("must not contain the username/service name"));

	// Hostname...
	if (config->differentFromHostname == true)
		errorCode = addListItem(paragraph, i18n("must not contain the devices host name"));

	// Device Info...
	if (config->noDeviceInformationInPasswords == true)
		errorCode = addListItem(paragraph, i18n("must not contain device details (i.e. make, model)"));

	// Dict with substitution...
	if (config->noDictionaryCharacterSubst == true)
		errorCode = addListItem(paragraph, i18n("must not be dictionary based with character substitution (i.e. an \"i\" swapped for a \"1\")"));

	// Character sequences...
	if (config->noCharacterSequences == true)
		errorCode = addListItem(paragraph, i18n("must not contain character sequences (i.e. \"qwerty\")"));

	// Appends...
	if (config->noCommonDictionaryAppends == true)
		errorCode = addListItem(paragraph, i18n("must not be dictionary based with common characters appended (i.e. \"1\")"));

	return errorCode;
}


int Device::calcOverallRating(int impact, int ease)
{
	int rating[10][11] = {{ 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1}, // Info
	                      { 2,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2},
	                      { 3,  1,  1,  1,  1,  2,  2,  2,  2,  3,  3}, // Low
	                      { 4,  1,  1,  1,  2,  2,  2,  3,  3,  4,  4},
	                      { 5,  2,  2,  2,  3,  3,  3,  4,  4,  5,  5}, // Medium
	                      { 6,  2,  2,  3,  4,  4,  4,  5,  5,  6,  6},
	                      { 7,  3,  3,  4,  5,  5,  5,  6,  6,  7,  7}, // High
	                      { 8,  3,  4,  4,  5,  6,  6,  7,  7,  8,  8},
	                      { 9,  4,  4,  5,  6,  6,  7,  8,  9,  9,  9}, // Critical
	                      {10,  4,  4,  5,  6,  7,  8,  9,  9, 10, 10}};
	//                     NA | CHAL |  MODERATE |    EASY   | TRIVIAL
	return rating[impact - 1][ease];
}



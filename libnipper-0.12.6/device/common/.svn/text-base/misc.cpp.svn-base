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

// Includes...
#include <cstring>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "../../globaldefs.h"
#include "../device.h"


string tempIntString;
const char *Device::intToString(int value)
{
	// Variables...
	ostringstream tempString;

	// Assign...
	tempString << value;

	// Return...
	tempIntString.assign(tempString.str());
	return tempIntString.c_str();
}


string tempTimeString;
const char *Device::timeToString(int time)
{
	tempTimeString.assign("");

	// NULL
	if (time == 0)
		return "";

	// If mins are greater than 0
	if ((time / 60) > 0)
	{
		tempTimeString.assign(intToString(time / 60));
		if ((time / 60) > 1)
			tempTimeString.append(i18n(" minutes")); 
		else
			tempTimeString.append(i18n(" minute"));
		if ((time % 60) > 0)
			tempTimeString.append(" ");
	}

	// If seconds are greater than 0...
	if ((time % 60) > 0)
	{
		tempTimeString.append(intToString(time % 60));
		if ((time % 60) > 1)
			tempTimeString.append(i18n(" seconds")); 
		else
			tempTimeString.append(i18n(" second"));
	}

	return tempTimeString.c_str();
}


const char *Device::cidrToNetmask(const char *cidr)
{
	switch (atoi(cidr))
	{
		case 1:
			return "128.0.0.0";
			break;
		case 2:
			return "192.0.0.0";
			break;
		case 3:
			return "244.0.0.0";
			break;
		case 4:
			return "240.0.0.0";
			break;
		case 5:
			return "248.0.0.0";
			break;
		case 6:
			return "252.0.0.0";
			break;
		case 7:
			return "254.0.0.0";
			break;
		case 8:
			return "255.0.0.0";
			break;
		case 9:
			return "255.128.0.0";
			break;
		case 10:
			return "255.192.0.0";
			break;
		case 11:
			return "255.244.0.0";
			break;
		case 12:
			return "255.240.0.0";
			break;
		case 13:
			return "255.248.0.0";
			break;
		case 14:
			return "255.252.0.0";
			break;
		case 15:
			return "255.254.0.0";
			break;
		case 16:
			return "255.255.0.0";
			break;
		case 17:
			return "255.255.128.0";
			break;
		case 18:
			return "255.255.192.0";
			break;
		case 19:
			return "255.255.244.0";
			break;
		case 20:
			return "255.255.240.0";
			break;
		case 21:
			return "255.255.248.0";
			break;
		case 22:
			return "255.255.252.0";
			break;
		case 23:
			return "255.255.254.0";
			break;
		case 24:
			return "255.255.255.0";
			break;
		case 25:
			return "255.255.255.128";
			break;
		case 26:
			return "255.255.255.192";
			break;
		case 27:
			return "255.255.255.244";
			break;
		case 28:
			return "255.255.255.240";
			break;
		case 29:
			return "255.255.255.248";
			break;
		case 30:
			return "255.255.255.252";
			break;
		case 31:
			return "255.255.255.254";
			break;
		case 32:
			return "255.255.255.255";
			break;
		default:
			return "0.0.0.0";
			break;
	}
}


unsigned int Device::ipAddressToNum(const char *address)
{
	// Variables...
	char *addressPointer = 0;
	unsigned int returnAddress = 0;
	int tempInt = 0; 

	// If there are errors...
	if (address == 0)
		return 0;
	if (strlen(address) < 7 )
		return 0;

	// First...
	tempInt = atoi(address);
	returnAddress = returnAddress | tempInt;
	returnAddress = returnAddress << 8;

	// Second...
	addressPointer = strchr(address, '.');
	if (addressPointer == 0)
		return 0;
	addressPointer++;
	tempInt = atoi(addressPointer);
	returnAddress = returnAddress | tempInt;
	returnAddress = returnAddress << 8;

	// Third...
	addressPointer = strchr(addressPointer, '.');
	if (addressPointer == 0)
		return 0;
	addressPointer++;
	tempInt = atoi(addressPointer);
	returnAddress = returnAddress | tempInt;
	returnAddress = returnAddress << 8;

	// Forth...
	addressPointer = strchr(addressPointer, '.');
	if (addressPointer == 0)
		return 0;
	addressPointer++;
	tempInt = atoi(addressPointer);
	returnAddress = returnAddress | tempInt;

	return returnAddress;
}


void Device::lineNotProcessed(const char *line)
{
	if (config->reportFormat == Config::Debug)
		printf("%sUnprocessed Line:%s %s\n", config->COL_RED, config->COL_RESET, line);
}


int Device::addRelatedIssue(securityIssueStruct *securityIssuePointer, const char *reference)
{
	// Variables...
	listStruct *relatedIssuePointer = 0;

	// Create
	if (securityIssuePointer->related == 0)
	{
		securityIssuePointer->related = new (listStruct);
		relatedIssuePointer = securityIssuePointer->related;
	}
	else
	{
		relatedIssuePointer = securityIssuePointer->related;
		while (relatedIssuePointer->next != 0)
			relatedIssuePointer = relatedIssuePointer->next;
		relatedIssuePointer->next = new (listStruct);
		relatedIssuePointer = relatedIssuePointer->next;
	}

	// Init...
	relatedIssuePointer->next = 0;
	relatedIssuePointer->listItem.assign(reference);

	return 0;
}


int Device::addDependency(securityIssueStruct *securityIssue, const char *dependent)
{
	// Variables...
	listStruct *dependentIssuePointer = 0;

	// Create
	if (securityIssue->dependent == 0)
	{
		securityIssue->dependent = new (listStruct);
		dependentIssuePointer = securityIssue->dependent;
	}
	else
	{
		dependentIssuePointer = securityIssue->dependent;
		while (dependentIssuePointer->next != 0)
			dependentIssuePointer = dependentIssuePointer->next;
		dependentIssuePointer->next = new (listStruct);
		dependentIssuePointer = dependentIssuePointer->next;
	}

	// Init...
	dependentIssuePointer->next = 0;
	dependentIssuePointer->listItem.assign(dependent);

	return 0;
}


int Device::addRecommendation(securityIssueStruct *securityIssue, const char *recommendation, bool orAction)
{
	// Variables...
	recommendationStruct *recPointer = 0;

	if (securityIssue->recLines == 0)
	{
		securityIssue->recLines = new (Device::recommendationStruct);
		recPointer = securityIssue->recLines;
	}
	else
	{
		recPointer = securityIssue->recLines;
		while (recPointer->next != 0)
			recPointer = recPointer->next;
		recPointer->next = new (Device::recommendationStruct);
		recPointer = recPointer->next;
	}

	// Init...
	recPointer->next = 0;
	recPointer->recommendation.assign(recommendation);
	recPointer->recommendationOr = orAction;

	return 0;
}


Device::listStruct *Device::createPortList(const char *portString)
{
	// Variables...
	listStruct *listBase = 0;
	listStruct *listPointer = 0;
	int stringLength = 0;
	int stringPos = 0;
	int tempInt = 0;
	char tempChar = 0;
	string lowPart;
	string highPart;
	string module;

	stringLength = strlen(portString);
	stringLength++;
	for (stringPos = 0; stringPos < stringLength; stringPos++)
	{
		// End of item (add)...
		if ((portString[stringPos] == ',') || (portString[stringPos] == 0))
		{
			// If item on its own...
			if (lowPart.empty())
			{
				// First...
				if (listPointer == 0)
				{
					listBase = new (listStruct);
					listPointer = listBase;
				}
				else
				{
					listPointer->next = new (listStruct);
					listPointer = listPointer->next;
				}
				listPointer->next = 0;
				listPointer->listItem.assign(highPart);
			}

			// it is a list...
			else
			{
				if (lowPart.find("/") != string::npos)
				{
					module.assign(lowPart.substr(0, lowPart.find("/") + 1).c_str());
					tempInt = atoi(lowPart.substr(lowPart.find("/") + 1).c_str());
				}
				else
				{
					module.assign("");
					tempInt = atoi(lowPart.c_str());
				}
				while (tempInt <= atoi(highPart.c_str()))
				{
					// First...
					if (listPointer == 0)
					{
						listBase = new (listStruct);
						listPointer = listBase;
					}
					else
					{
						listPointer->next = new (listStruct);
						listPointer = listPointer->next;
					}
					listPointer->next = 0;
					listPointer->listItem.assign(module);
					listPointer->listItem.append(intToString(tempInt));
					tempInt++;
				}
			}
			lowPart.assign("");
			highPart.assign("");
		}

		// End of range first part...
		else if (portString[stringPos] == '-')
		{
			lowPart.assign(highPart);
			highPart.assign("");
		}

		// Add another character on...
		else
		{
			tempChar = *(portString + stringPos);
			highPart.append(1, tempChar);
		}
	}

	return listBase;
}


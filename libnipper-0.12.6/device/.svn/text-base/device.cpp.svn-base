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
#include "../globaldefs.h"
#include "errortext.h"
#include "device.h"
#include "general/general.h"
#include "administration/administration.h"
#include "authentication/authentication.h"
#include "dns/dns.h"
#include "banner/banner.h"
#include "filter/filter.h"
#include "snmp/snmp.h"
#include "interfaces/interfaces.h"


struct Device::dictionaryStruct builtindict26 = {"miniap", 0};
struct Device::dictionaryStruct builtindict25 = {"cable-docsis", &builtindict26};
struct Device::dictionaryStruct builtindict24 = {"ilmi", &builtindict25};
struct Device::dictionaryStruct builtindict23 = {"laflaf", &builtindict24};
struct Device::dictionaryStruct builtindict22 = {"violation", &builtindict23};
struct Device::dictionaryStruct builtindict21 = {"snmp-trap", &builtindict22};
struct Device::dictionaryStruct builtindict20 = {"dbsnmp", &builtindict21};
struct Device::dictionaryStruct builtindict19 = {"cascade", &builtindict20};
struct Device::dictionaryStruct builtindict18 = {"nortel", &builtindict19};
struct Device::dictionaryStruct builtindict17 = {"juniper", &builtindict18};
struct Device::dictionaryStruct builtindict16 = {"netscreen", &builtindict17};
struct Device::dictionaryStruct builtindict15 = {"rwa", &builtindict16};
struct Device::dictionaryStruct builtindict14 = {"rw", &builtindict15};
struct Device::dictionaryStruct builtindict13 = {"ro", &builtindict14};
struct Device::dictionaryStruct builtindict12 = {"master", &builtindict13};
struct Device::dictionaryStruct builtindict11 = {"super", &builtindict12};
struct Device::dictionaryStruct builtindict10 = {"network", &builtindict11};
struct Device::dictionaryStruct builtindict9  = {"cisco", &builtindict10};
struct Device::dictionaryStruct builtindict8  = {"secret", &builtindict9};
struct Device::dictionaryStruct builtindict7  = {"default", &builtindict8};
struct Device::dictionaryStruct builtindict6  = {"supervisor", &builtindict7};
struct Device::dictionaryStruct builtindict5  = {"administrator", &builtindict6};
struct Device::dictionaryStruct builtindict4  = {"admin", &builtindict5};
struct Device::dictionaryStruct builtindict3  = {"private", &builtindict4};
struct Device::dictionaryStruct builtindict2  = {"public", &builtindict3};
struct Device::dictionaryStruct builtindict1  = {"snmp", &builtindict2};
struct Device::dictionaryStruct builtindict   = {"password", &builtindict1}; 


Device::Device()
{
	// Init public...
	appendixLoggingLevels = false;
	dictionary = &builtindict;
	encryptedDictionary = 0;
	securityReport = 0;
	configReport = 0;
	reportIntro = 0;
	appendixReport = 0;
	johnPassword = 0;
	deviceType = 0;
	deviceMake = 0;
	deviceOS = 0;
	deviceModel = 0;
	supportConfigNetworkServices = true;
	isRouter = false;							// Set to true if it is a router
	isFirewall = false;							// Set to true if it is a firewall
	isSwitch = false;							// Set to true if it is a switch

	// Init configurations...
	general = 0;
	administration = 0;
	authentication = 0;
	dns = 0;
	banner = 0;
	filter = 0;
	snmp = 0;
	interfaces = 0;

	// Init Private...
	inputFile = 0;
}


void destroyParagraph(Device::paragraphStruct *paragraph)
{
	// Variables...
	Device::paragraphStruct *paragraphPointer = 0;
	Device::listStruct *stringPointer = 0;
	Device::valueList *valuePointer = 0;
	Device::headingStruct *headingPointer = 0;
	Device::bodyStruct *bodyPointer = 0;

	while (paragraph != 0)
	{
		while (paragraph->strings != 0)
		{
			stringPointer = paragraph->strings->next;
			delete paragraph->strings;
			paragraph->strings = stringPointer;
		}
		while (paragraph->values != 0)
		{
			valuePointer = paragraph->values->next;
			delete paragraph->values;
			paragraph->values = valuePointer;
		}
		while (paragraph->list != 0)
		{
			stringPointer = paragraph->list->next;
			delete paragraph->list;
			paragraph->list = stringPointer;
		}
		if (paragraph->table != 0)
		{
			while (paragraph->table->headings != 0)
			{
				headingPointer = paragraph->table->headings->next;
				delete paragraph->table->headings;
				paragraph->table->headings = headingPointer;
			}
			while (paragraph->table->body != 0)
			{
				bodyPointer = paragraph->table->body->next;
				delete paragraph->table->body;
				paragraph->table->body = bodyPointer;
			}
			delete paragraph->table;
		}
		paragraphPointer = paragraph->next;
		delete paragraph;
		paragraph = paragraphPointer;
	}
}


Device::~Device()
{
	// Variables...
	configReportStruct *configReportPointer = 0;
	securityIssueStruct *securityIssuePointer = 0;
	listStruct *relatedIssuePointer = 0;
	recommendationStruct *recPointer = 0;
	johnPasswordStruct *johnPointer = 0;

	// Delete John-the-ripper passwords...
	while (johnPassword != 0)
	{
		johnPointer = johnPassword->next;
		delete johnPassword;
		johnPassword = johnPointer;
	}

	// Delete a temporary file...
	if (!tempFileName.empty())
		unlink(tempFileName.c_str());

	// Delete Report Introduction?
	while (reportIntro != 0)
	{
		destroyParagraph(reportIntro->config);
		configReportPointer = reportIntro->next;
		delete reportIntro;
		reportIntro = configReportPointer;
	}

	// Delete Appendix Report?
	while (appendixReport != 0)
	{
		destroyParagraph(appendixReport->config);
		configReportPointer = appendixReport->next;
		delete appendixReport;
		appendixReport = configReportPointer;
	}

	// Delete Config Report?
	while (configReport != 0)
	{
		destroyParagraph(configReport->config);
		configReportPointer = configReport->next;
		delete configReport;
		configReport = configReportPointer;
	}

	// Delete Security Report?
	while (securityReport != 0)
	{
		destroyParagraph(securityReport->finding);
		destroyParagraph(securityReport->impact);
		destroyParagraph(securityReport->ease);
		destroyParagraph(securityReport->recommendation);
		while (securityReport->related != 0)
		{
			relatedIssuePointer = securityReport->related->next;
			delete securityReport->related;
			securityReport->related = relatedIssuePointer;
		}
		while (securityReport->dependent != 0)
		{
			relatedIssuePointer = securityReport->dependent->next;
			delete securityReport->dependent;
			securityReport->dependent = relatedIssuePointer;
		}
		while (securityReport->recLines != 0)
		{
			recPointer = securityReport->recLines->next;
			delete securityReport->recLines;
			securityReport->recLines = recPointer;
		}
		securityIssuePointer = securityReport->next;
		delete securityReport;
		securityReport = securityIssuePointer;
	}
}


int Device::process()
{
	// Variables...
	int returnCode = 0;

	// Open Input...
	returnCode = openInput();
	if (returnCode == 0)
	{

		returnCode = processDevice();

		// Close Input...
		fclose(inputFile);
	
		// Post processing defaults...
		setPostCommonDefaults();

		// Post device specific processing defaults...
		setPostDefaults();
	}

	return returnCode;
}


int Device::processDevice()
{
	return 0;
}


const char *Device::getErrorText(int errorCode)
{
	switch (errorCode)
	{
		case deviceerror_inputisadirectory:
			return i18n("A directory has been specified, a file was expected.");
			break;
		case deviceerror_nostdindata:
			return i18n("Timeout whilst waiting for stdin data.");
			break;
		case deviceerror_objectsfilenotfound:
			return i18n("Could not locate the required files in the input directory supplied.");
			break;
		case deviceerror_inputnotadirectory:
			return i18n("The input must be a directory, but it was not.");
			break;
		case deviceerror_memoryallocationerror:
			return i18n("There was a memory allocation error, free some memory and try again.");
			break;
		case deviceerror_inputsizeiszero:
			return i18n("The configuration file does not exist or is empty.");
			break;
		case deviceerror_noinput:
			return i18n("There is no configuration input.");
			break;
		case deviceerror_creatingtempfile:
			return i18n("Could not create a temporary file..");
			break;
		case deviceerror_openingfile:
			return i18n("Error occured while opening a file.");
			break;
		default:
			return i18n("Unknown device error.");
			break;
	}

	return "";
}


Device::configReportStruct *Device::getConfigSection(const char *reference)
{
	// Variables...
	configReportStruct *configReportPointer = 0;
	bool setup = false;

	// Create a new structure...
	if (configReport == 0)
	{
		configReport = new (Device::configReportStruct);
		configReportPointer = configReport;
		setup = true;
	}
	else
	{
		configReportPointer = configReport;
		while ((configReportPointer->next != 0) && (configReportPointer->reference.compare(reference) != 0))
			configReportPointer = configReportPointer->next;
		if (configReportPointer->reference.compare(reference) != 0)
		{
			configReportPointer->next = new (Device::configReportStruct);
			configReportPointer = configReportPointer->next;
			setup = true;
		}
	}

	// If not found...
	if (setup == true)
	{
		configReportPointer->reference.assign(reference);
		configReportPointer->section = 0;
		configReportPointer->subsection = 0;
		configReportPointer->position = 3;
		configReportPointer->config = 0;
		configReportPointer->next = 0;
	}

	return configReportPointer;
}


Device::configReportStruct *Device::getAppendixSection(const char *reference)
{
	// Variables...
	configReportStruct *appendixReportPointer = 0;
	bool setup = false;

	// Create a new structure...
	if (appendixReport == 0)
	{
		appendixReport = new (Device::configReportStruct);
		appendixReportPointer = appendixReport;
		setup = true;
	}
	else
	{
		appendixReportPointer = appendixReport;
		while ((appendixReportPointer->next != 0) && (appendixReportPointer->reference.compare(reference) != 0))
			appendixReportPointer = appendixReportPointer->next;
		if (appendixReportPointer->reference.compare(reference) != 0)
		{
			appendixReportPointer->next = new (Device::configReportStruct);
			appendixReportPointer = appendixReportPointer->next;
			setup = true;
		}
	}

	// If not found...
	if (setup == true)
	{
		appendixReportPointer->reference.assign(reference);
		appendixReportPointer->section = 0;
		appendixReportPointer->subsection = 0;
		appendixReportPointer->position = 3;
		appendixReportPointer->config = 0;
		appendixReportPointer->next = 0;
	}

	return appendixReportPointer;
}


Device::securityIssueStruct *Device::getSecurityIssue(const char *reference)
{
	// Variables...
	securityIssueStruct *securityIssuePointer = 0;
	bool found = false;

	securityIssuePointer = securityReport;
	while ((securityIssuePointer != 0) && (found == false))
	{
		if (securityIssuePointer->reference.compare(reference) == 0)
			found = true;
		else
			securityIssuePointer = securityIssuePointer->next;
	}

	return securityIssuePointer;
}


Device::securityIssueStruct *Device::addSecurityIssue()
{
	// Variables...
	securityIssueStruct *securityIssuePointer = 0;

	// Create a new structure...
	if (securityReport == 0)
	{
		securityReport = new (Device::securityIssueStruct);
		securityIssuePointer = securityReport;
	}
	else
	{
		securityIssuePointer = securityReport;
		while (securityIssuePointer->next != 0)
			securityIssuePointer = securityIssuePointer->next;
		securityIssuePointer->next = new (Device::securityIssueStruct);
		securityIssuePointer = securityIssuePointer->next;
	}

	// Init...
	securityIssuePointer->section = 0;
	securityIssuePointer->subsection = 0;
	securityIssuePointer->position = 3;
	securityIssuePointer->overallRating = 0;
	securityIssuePointer->impactRating = 0;
	securityIssuePointer->easeRating = 0;
	securityIssuePointer->fixRating = 0;
	securityIssuePointer->finding = 0;
	securityIssuePointer->impact = 0;
	securityIssuePointer->ease = 0;
	securityIssuePointer->recommendation = 0;
	securityIssuePointer->dependent = 0;
	securityIssuePointer->related = 0;
	securityIssuePointer->recLines = 0;
	securityIssuePointer->next = 0;

	return securityIssuePointer;
}


void Device::setPostCommonDefaults()
{
	if (general != 0)
		general->processDefaults(this);
	if (administration != 0)
		administration->processDefaults(this);
	if (authentication != 0)
		authentication->processDefaults(this);
	if (dns != 0)
		dns->processDefaults(this);
	if (banner != 0)
		banner->processDefaults(this);
	if (snmp != 0)
		snmp->processDefaults(this);
	if (filter != 0)
		filter->processDefaults(this);
	if (interfaces != 0)
		interfaces->processDefaults(this);
}


void Device::setPostDefaults()
{
}


bool Device::isDeviceType()
{
	return false;
}

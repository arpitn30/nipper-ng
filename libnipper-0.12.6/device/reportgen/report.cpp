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
#include <cmath>

#include "../../globaldefs.h"
#include "../device.h"
#include "../general/general.h"
#include "../administration/administration.h"
#include "../authentication/authentication.h"
#include "../dns/dns.h"
#include "../banner/banner.h"
#include "../snmp/snmp.h"
#include "../filter/filter.h"
#include "../interfaces/interfaces.h"


int Device::generateReport()
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::securityIssueStruct *securityIssuePointer2 = 0;
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	Device::bodyStruct *bodyPointer = 0;
	Device::recommendationStruct *recPointer = 0;
	int errorCode = 0;
	int overallCritical = 0;
	int overallHigh = 0;
	int overallMedium = 0;
	int overallLow = 0;
	int overallInformational = 0;
	int overallTotal = 0;
	string tempString;

	// -----------------------------------------------------------------
	// Report Introduction...
	// -----------------------------------------------------------------

	if (config->reportFormat == Config::Debug)
		printf("  %s>%s Report Introduction\n", config->COL_GREEN, config->COL_RESET);

	// Create structure...
	reportIntro = new (configReportStruct);
	configReportPointer = reportIntro;

	if (config->reportFormat == Config::Debug)
		printf("    %s*%s Report Organisation\n", config->COL_BLUE, config->COL_RESET);

	// Init...
	configReportPointer->title.assign(i18n("Organisation"));
	configReportPointer->reference.assign("ABOUTREPORTORGANISATION");
	configReportPointer->section = 0;
	configReportPointer->subsection = 0;
	configReportPointer->config = 0;
	configReportPointer->position = 3;
	configReportPointer->next = 0;

	// Paragraph...
	paragraphPointer = addParagraph(configReportPointer);
	paragraphPointer->paragraph.assign(i18n("This *DEVICETYPE* report was produced by *COMPANY* on *DATE*. The report is comprised of the following sections:"));

	// Add sections to the list
	if (config->includeSecurityAudit == true)
		addListItem(paragraphPointer, i18n("a security audit report section that details any identified security-related issues. Each security issue includes a finding, its impact, how easy it would be for an attacker to exploit and a recommendation. The recommendations include, where appropriate, the command(s) to mitigate the issue"));
	if (config->includeComplianceCheck == true)
		addListItem(paragraphPointer, i18n("a compliance audit section that details which *DEVICETYPE* configuration settings that are compiant with the configuration policy and those that are not"));
	if (config->includeConfigurationReport == true)
		addListItem(paragraphPointer, i18n("a configuration report section that details the *DEVICETYPE* configuration settings"));
	if (config->includeAppendixSection == true)
	{
		if (config->includeAbbreviations == true)
			addListItem(paragraphPointer, i18n("an abbreviations appendix section that expands any abbreviations used within the report"));
		if (config->includeNetworkPorts == true)
			addListItem(paragraphPointer, i18n("a common ports appendix section that details the *ABBREV*TCP*-ABBREV* and *ABBREV*UDP*-ABBREV* port numbers for the common services outlined within the report"));
		if (config->includeLoggingLevels == true)
			addListItem(paragraphPointer, i18n("an appendix section detailing the severity levels used by the logging facility"));
		if (config->includeTimeZones == true)
			addListItem(paragraphPointer, i18n("a time zones appendix section that details a number of the most commonly used time zones"));
		if (config->includeNipperVersion == true)
			addListItem(paragraphPointer, i18n("an appendix section detailing the software used to produce this report"));
	}

	if (config->reportFormat == Config::Debug)
		printf("    %s*%s Report Conventions\n", config->COL_BLUE, config->COL_RESET);

	// Create structure...
	configReportPointer->next = new (configReportStruct);
	configReportPointer = configReportPointer->next;

	// Init...
	configReportPointer->title.assign(i18n("Conventions"));
	configReportPointer->reference.assign("ABOUTREPORTCONVENTIONS");
	configReportPointer->config = 0;
	configReportPointer->section = 0;
	configReportPointer->subsection = 0;
	configReportPointer->position = 3;
	configReportPointer->next = 0;

	// Paragraph...
	paragraphPointer = addParagraph(configReportPointer);
	paragraphPointer->paragraph.assign(i18n("This report makes use of the text conventions outlined in Table *TABLEREF*."));

	// Table...
	errorCode = addTable(paragraphPointer, "INTRO-CONVENTIONS-TABLE");
	if (errorCode != 0)
		return errorCode;

	// Set Table title...
	paragraphPointer->table->title = i18n("Report text conventions");

	// Set Table headings...
	addTableHeading(paragraphPointer->table, i18n("Convention"), true);
	addTableHeading(paragraphPointer->table, i18n("Description"), false);

	// Add Table content...
	addTableData(paragraphPointer->table, i18n("*COMMAND*command*-COMMAND*"));
	addTableData(paragraphPointer->table, i18n("This text style represents the *DEVICETYPE* command text that has to be entered literally."));
	addTableData(paragraphPointer->table, i18n("*COMMAND**CMDUSER*string*-CMDUSER**-COMMAND*"));
	addTableData(paragraphPointer->table, i18n("This text style represents the *DEVICETYPE* command text that you have to enter."));
	addTableData(paragraphPointer->table, "*COMMAND**CMDOPTION* *-CMDOPTION**-COMMAND*");
	addTableData(paragraphPointer->table, i18n("Used to enclose a *DEVICETYPE* command option."));
	addTableData(paragraphPointer->table, "*COMMAND**CMDREQUIRE* *-CMDREQUIRE**-COMMAND*");
	addTableData(paragraphPointer->table, i18n("Used to enclose a *DEVICETYPE* command requirement."));
	addTableData(paragraphPointer->table, "*COMMAND**CMDOR**-COMMAND*");
	addTableData(paragraphPointer->table, i18n("Divides command option or requirement choices."));


	// -----------------------------------------------------------------
	// Security Report...
	// -----------------------------------------------------------------

	// Security Report?
	if (config->includeSecurityAudit == true)
	{

		if (config->reportFormat == Config::Debug)
		{
			printf("  %s>%s Security Auditing\n", config->COL_GREEN, config->COL_RESET);
			printf("    %s*%s Security Introduction\n", config->COL_BLUE, config->COL_RESET);
		}

		// Generate Security Section Introductions...
		securityIssuePointer = addSecurityIssue();
		securityIssuePointer->title.assign(i18n("Introduction"));
		securityIssuePointer->reference.assign("GEN.SECINTRO.1");
		securityIssuePointer->position = 1;
		paragraphPointer = addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("Each security issue identified by *COMPANY* is described with a finding, the impact of the issue, how easy it would be for an attacker to exploit the issue and a recommendation. Each security issue is rated based on a number of factors, each of these are described in the following sections."));
		paragraphPointer = addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraphTitle.assign(i18n("Issue Finding"));
		paragraphPointer->paragraph.assign(i18n("The issue finding describes what configuration setting *COMPANY* identified that potentially poses a security threat. In addition to the finding details, any releveant background information is also described."));
		paragraphPointer = addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraphTitle.assign(i18n("Issue Impact"));
		paragraphPointer->paragraph.assign(i18n("The impact section describes what an attacker could gain from exploiting the security issue. The impact of an issue is often defined by other configuration settings that could heighten the issue or partially mitigate it. For example, a weak password could be partially mitigated if the access gained from using it is restricted in some way. The impact is rated depending on the significance of the security threat. Table *TABLEREF* outlines the possible impact ratings and their significance."));
		// Table...
		errorCode = addTable(paragraphPointer, "SEC-INTIMPACT-TABLE");
		if (errorCode != 0)
			return errorCode;
		// Set Table title...
		paragraphPointer->table->title = i18n("Impact ratings");
		// Set Table headings
		addTableHeading(paragraphPointer->table, i18n("Rating"), false);
		addTableHeading(paragraphPointer->table, i18n("Description"), false);
		addTableData(paragraphPointer->table, "*CRITICAL*");
		addTableData(paragraphPointer->table, i18n("These issues can pose a very significant security threat. The issues that have a critical impact are typically those that would allow an attacker to gain full administrative access to the device. For a firewall device, allowing all traffic to pass through the device unfiltered would receive this rating as filtering traffic to protect other devices is the primary purpose of a firewall."));
		addTableData(paragraphPointer->table, "*HIGH*");
		addTableData(paragraphPointer->table, i18n("These issues pose a significant threat to security, but have some limitations on the extent to which they can be abused. User level access to a device and a *ABBREV*DoS*-ABBREV* vulnerability in a critical service would fall into this category. A firewall deivce that allowed significant unfiltered access, such as allowing entire subnets through or not filtering in all directions, would fall into this category. A router that allows significant modification of its routing configuration would also fall into this category."));
		addTableData(paragraphPointer->table, "*MEDIUM*");
		addTableData(paragraphPointer->table, i18n("These issues have significant limitations on the direct impact they can cause. Typically these issues would include significant information leakage issues, denial of service issues or those that provide significantly limited access. A *ABBREV*SNMP*-ABBREV* service that is secured with default or a dictionary based community string would typically fall into this rating, as would a firewall that allows unfiltered access to a range of services on a device."));
		addTableData(paragraphPointer->table, "*LOW*");
		addTableData(paragraphPointer->table, i18n("These issues represent a low level security threat. A typical issue would involve information leakage that could be useful to an attacker, such as a list of users or version details. A non-firewall device that was configured with weak network filtering would fall into this category."));
		addTableData(paragraphPointer->table, "*INFORMATIONAL*");
		addTableData(paragraphPointer->table, i18n("These issues represent a very low level of security threat. These issues include minor information leakage, unnecessary services or legacy protocols that provide no real threat to security."));
		paragraphPointer = addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraphTitle.assign(i18n("Issue Ease"));
		paragraphPointer->paragraph.assign(i18n("The ease section of each issue describes the knowledge, skill and physical access that would be required of an attacker in order to exploit it. The ease will describe if open source or commercially available tools are required for an attacker to exploit an issue. Additionally, the ease will note where an extended period of time is required to exploit the issue, such as cracking weak encryption ciphers. Each issue is rated upon how easily it can be exploited, the ratings for which are described in Table *TABLEREF*."));
		// Table...
		errorCode = addTable(paragraphPointer, "SEC-INTEASE-TABLE");
		if (errorCode != 0)
			return errorCode;
		// Set Table title...
		paragraphPointer->table->title = i18n("Ease ratings");
		// Set Table headings
		addTableHeading(paragraphPointer->table, i18n("Rating"), false);
		addTableHeading(paragraphPointer->table, i18n("Description"), false);
		addTableData(paragraphPointer->table, "*TRIVIAL*");
		addTableData(paragraphPointer->table, i18n("The issue requires little-to-no knowledge on behalf of an attacker and can be exploited using standard operating system tools. A firewall device which had a network filtering configuration that enables traffic to pass through would fall into this category."));
		addTableData(paragraphPointer->table, "*EASY*");
		addTableData(paragraphPointer->table, i18n("The issue requires some knowledge for an attacker to exploit, which could be performed using standard operating system tools or tools downloaded from the Internet. An administrative service without or with a default password would fall into this category, as would a simple software vulnerability exploit."));
		addTableData(paragraphPointer->table, "*MODERATE*");
		addTableData(paragraphPointer->table, i18n("The issue requires specific knowledge on behalf of an attacker. The issue could be exploited using a combination of operating system tools or publicly available tools downloaded from the Internet."));
		addTableData(paragraphPointer->table, "*CHALLENGING*");
		addTableData(paragraphPointer->table, i18n("A security issue that falls into this category would require significant effort and knowledge on behalf of the attacker. The attacker may require specific physical access to resources or to the network infrastructure in order to successfully exploit it. Furthermore, a combination of attacks may be required."));
		addTableData(paragraphPointer->table, "*NOTAPPLICABLE*");
		addTableData(paragraphPointer->table, i18n("The issue is not directly exploitable. An issue such as enabling legacy protocols or unnecessary services would fall into this rating category."));

		// Resolution ratings...
		paragraphPointer = addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraphTitle.assign(i18n("Issue Recommendation"));
		paragraphPointer->paragraph.assign(i18n("Each issue includes a recommendation section which describes what steps Nipper recommends should be taken in order to mitigate the issue. The recommendation will sometimes include various options, if several mitigating choices are available, and any relevant system commands."));
		paragraphPointer = addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("Directly following the recommendation, the issue dependencies and other relevant issues are referenced. The dependency issues are those that when mitigated will eliminate the described issue. For example, if the *ABBREV*SNMP*-ABBREV* is disabled it no longer matters if a view has not been configured. The relevant issues are ones that can affect the impact or the ease that the issue can be exploited."));
		paragraphPointer = addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("The recommendation includes a rating that indicates how easy an issue is to resolve, these are described in Table *TABLEREF*."));
		// Table...
		errorCode = addTable(paragraphPointer, "SEC-INTFIX-TABLE");
		if (errorCode != 0)
			return errorCode;
		// Set Table title...
		paragraphPointer->table->title = i18n("Fix ratings");
		// Set Table headings
		addTableHeading(paragraphPointer->table, i18n("Rating"), false);
		addTableHeading(paragraphPointer->table, i18n("Description"), false);
		addTableData(paragraphPointer->table, "*INVOLVED*");
		addTableData(paragraphPointer->table, i18n("The resolution of the issue will require significant resources to resolve and is likely to include disruption to network services, and possibly the modification of other network device configurations. The issue could involve upgrading the *DEVICETYPE* *ABBREV*OS*-ABBREV* and possibly modifications to the hardware."));
		addTableData(paragraphPointer->table, "*PLANNED*");
		addTableData(paragraphPointer->table, i18n("The issue resolution involves planning, testing and could cause some disruption to services. This issue could involve changes to routing protocols and changes to network filtering."));
		addTableData(paragraphPointer->table, "*QUICK*");
		addTableData(paragraphPointer->table, i18n("The issue is quick to resolve. Typically this would just involve changing a small number of settings and would have little-to-no effect on network services."));

		paragraphPointer = addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraphTitle.assign(i18n("Issue Overall Rating"));
		paragraphPointer->paragraph.assign(i18n("The previous sections describe each section that is reported for an individual issue and the rating that is associated with it, they do not describe how the overall rating is calculated. The overall security issue rating is calculated based on a combination of the impact and the ease of exploiting an issue, the recommendation rating is not included as it does not represent the significance of a security issue. The overall rating uses the same ratings as the impact, but modified by how easy it is to exploit."));
		paragraphPointer = addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("It is worth noting that *COMPANY* is unable to provide an accurate threat assessment due to a lack of information. For example, in the case where highly sensitive information is processed, a *ABBREV*DoS*-ABBREV* vulnerability poses less of a threat than the integrity of the data or an attacker gaining access to it. Similarly, for a situation where uptime is critical, a *ABBREV*DoS*-ABBREV* vulnerability could be more important than the leakage of sensitive information. The ratings provided by *COMPANY* are intended to be a guide."));

		// General Device Setting Security Issues...
		if (general != 0)
			general->generateSecurityReport(this);

		// Administration Issues...
		if (administration != 0)
			administration->generateSecurityReport(this);

		// Authentication Issues...
		if (authentication != 0)
			authentication->generateSecurityReport(this);

		// DNS Issues...
		if (dns != 0)
			dns->generateSecurityReport(this);

		// Banner Issues...
		if (banner != 0)
			banner->generateSecurityReport(this);

		// SNMP Issues...
		if (snmp != 0)
			snmp->generateSecurityReport(this);

		// Filter Issues...
		if (filter != 0)
			filter->generateSecurityReport(this);

		// Interfaces Issues...
		if (interfaces != 0)
			interfaces->generateSecurityReport(this);

		if (config->reportFormat == Config::Debug)
			printf("    %s*%s Calculating Security Issue Ratings\n", config->COL_BLUE, config->COL_RESET);

		// Calculate the overall rating...
		securityIssuePointer = securityReport;
		while (securityIssuePointer != 0)
		{
			if (securityIssuePointer->position == 3)
			{
				// Calculate Overall...
				securityIssuePointer->overallRating = calcOverallRating(securityIssuePointer->impactRating, securityIssuePointer->easeRating);

				// Overall Counts...
				if (securityIssuePointer->overallRating > 8)
					overallCritical++;
				else if (securityIssuePointer->overallRating > 6)
					overallHigh++;
				else if (securityIssuePointer->overallRating > 4)
					overallMedium++;
				else if (securityIssuePointer->overallRating > 2)
					overallLow++;
				else
					overallInformational++;
				overallTotal++;
			}
			securityIssuePointer = securityIssuePointer->next;
		}

		// Sort out issue ordering...
		if (config->reportFormat == Config::Debug)
			printf("    %s*%s Ordering Secruity Issues\n", config->COL_BLUE, config->COL_RESET);
		if (config->issueOrdering == Config::byOverallRating)
			reorderSecurityIssues();

		if (config->reportFormat == Config::Debug)
			printf("    %s*%s Security Conclusions\n", config->COL_BLUE, config->COL_RESET);

		// Conclusions...
		securityIssuePointer = addSecurityIssue();
		securityIssuePointer->title.assign(i18n("Conclusions"));
		securityIssuePointer->reference.assign("GEN.SECCONCL.1");
		securityIssuePointer->position = 4;
		paragraphPointer = addParagraph(securityIssuePointer, Device::Finding);
		if (overallTotal == 0)
			paragraphPointer->paragraph.assign(i18n("*COMPANY* performed a security audit of the *DEVICETYPE* *DEVICENAME* on *DATE* and identified no security-related issues."));
		else if (overallTotal > 0)
		{
			if (overallTotal == 1)
			{
				paragraphPointer->paragraph.assign(i18n("*COMPANY* performed a security audit of the *DEVICETYPE* *DEVICENAME* on *DATE* and identified one security-related issue. "));
				paragraphPointer = addParagraph(securityIssuePointer, Device::Finding);
				securityIssuePointer = securityReport;
				while (securityIssuePointer != 0)
				{
					if (securityIssuePointer->position == 3)
					{
						paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that "));
						paragraphPointer->paragraph.append(securityIssuePointer->conLine);
						if (overallCritical > 0)
							paragraphPointer->paragraph.append(i18n(" (rated *CRITICAL*, see section *SECTIONNO*)."));
						else if (overallHigh > 0)
							paragraphPointer->paragraph.append(i18n(" (rated *HIGH*, see section *SECTIONNO*)."));
						else if (overallMedium > 0)
							paragraphPointer->paragraph.append(i18n(" (rated *MEDIUM*, see section *SECTIONNO*)."));
						else if (overallLow > 0)
							paragraphPointer->paragraph.append(i18n(" (rated *LOW*, see section *SECTIONNO*)."));
						else
							paragraphPointer->paragraph.append(i18n(" (rated *INFORMATIONAL*, see section *SECTIONNO*)."));
						addString(paragraphPointer, securityIssuePointer->reference.c_str());
					}
					securityIssuePointer = securityIssuePointer->next;
				}
			}
			else
			{
				paragraphPointer->paragraph.assign(i18n("*COMPANY* performed a security audit of the *DEVICETYPE* *DEVICENAME* on *DATE* and identified *NUMBER* security-related issues. The most significant issue identified was rated as "));
				addValue(paragraphPointer, overallTotal);
				if (overallCritical > 0)
					paragraphPointer->paragraph.append("*CRITICAL*.");
				else if (overallHigh > 0)
					paragraphPointer->paragraph.append("*HIGH*.");
				else if (overallMedium > 0)
					paragraphPointer->paragraph.append("*MEDIUM*.");
				else if (overallLow > 0)
					paragraphPointer->paragraph.append("*LOW*.");
				else
					paragraphPointer->paragraph.append("*INFORMATIONAL*.");

				// Critical rated issues...
				if (overallCritical > 0)
				{
					paragraphPointer = addParagraph(securityIssuePointer, Device::Finding);
					if (overallCritical == 1)
						paragraphPointer->paragraph.assign(i18n("One *CRITICAL* rated security issue was identitified. *COMPANY* determined that:"));
					else
					{
						paragraphPointer->paragraph.assign(i18n("*COMPANY* identified *NUMBER* *CRITICAL* rated security issues. *COMPANY* determined that:"));
						addValue(paragraphPointer, overallCritical);
					}
					securityIssuePointer2 = securityReport;
					while (securityIssuePointer2 != 0)
					{
						if ((securityIssuePointer2->position == 3) && (securityIssuePointer2->overallRating > 8))
						{
							tempString.assign(securityIssuePointer2->conLine);
							tempString.append(" (see section *SECTIONNO*)");
							addString(paragraphPointer, securityIssuePointer2->reference.c_str());
							addListItem(paragraphPointer, tempString.c_str());
						}
						securityIssuePointer2 = securityIssuePointer2->next;
					}
				}

				// High rated issues...
				if (overallHigh > 0)
				{
					paragraphPointer = addParagraph(securityIssuePointer, Device::Finding);
					if (overallHigh == 1)
						paragraphPointer->paragraph.assign(i18n("One *HIGH* rated security issue was identified. *COMPANY* determined that:"));
					else
					{
						paragraphPointer->paragraph.assign(i18n("*COMPANY* identified *NUMBER* *HIGH* rated security issues. *COMPANY* determined that:"));
						addValue(paragraphPointer, overallHigh);
					}
					securityIssuePointer2 = securityReport;
					while (securityIssuePointer2 != 0)
					{
						if ((securityIssuePointer2->position == 3) && ((securityIssuePointer2->overallRating == 8) || (securityIssuePointer2->overallRating == 7)))
						{
							tempString.assign(securityIssuePointer2->conLine);
							tempString.append(" (see section *SECTIONNO*)");
							addString(paragraphPointer, securityIssuePointer2->reference.c_str());
							addListItem(paragraphPointer, tempString.c_str());
						}
						securityIssuePointer2 = securityIssuePointer2->next;
					}
				}

				// Medium rated issues...
				if (overallMedium > 0)
				{
					paragraphPointer = addParagraph(securityIssuePointer, Device::Finding);
					if (overallMedium == 1)
						paragraphPointer->paragraph.assign(i18n("One *MEDIUM* rated security issue was identified. *COMPANY* determined that:"));
					else
					{
						paragraphPointer->paragraph.assign(i18n("*COMPANY* identified *NUMBER* *MEDIUM* rated security issues. *COMPANY* determined that:"));
						addValue(paragraphPointer, overallMedium);
					}
					securityIssuePointer2 = securityReport;
					while (securityIssuePointer2 != 0)
					{
						if ((securityIssuePointer2->position == 3) && ((securityIssuePointer2->overallRating == 6) || (securityIssuePointer2->overallRating == 5)))
						{
							tempString.assign(securityIssuePointer2->conLine);
							tempString.append(" (see section *SECTIONNO*)");
							addString(paragraphPointer, securityIssuePointer2->reference.c_str());
							addListItem(paragraphPointer, tempString.c_str());
						}
						securityIssuePointer2 = securityIssuePointer2->next;
					}
				}

				// Low rated issues...
				if (overallLow > 0)
				{
					paragraphPointer = addParagraph(securityIssuePointer, Device::Finding);
					if (overallLow == 1)
						paragraphPointer->paragraph.assign(i18n("One *LOW* rated security issue was identified. *COMPANY* determined that:"));
					else
					{
						paragraphPointer->paragraph.assign(i18n("*COMPANY* identified *NUMBER* *LOW* rated security issues. *COMPANY* determined that:"));
						addValue(paragraphPointer, overallLow);
					}
					securityIssuePointer2 = securityReport;
					while (securityIssuePointer2 != 0)
					{
						if ((securityIssuePointer2->position == 3) && ((securityIssuePointer2->overallRating == 4) || (securityIssuePointer2->overallRating == 3)))
						{
							tempString.assign(securityIssuePointer2->conLine);
							tempString.append(" (see section *SECTIONNO*)");
							addString(paragraphPointer, securityIssuePointer2->reference.c_str());
							addListItem(paragraphPointer, tempString.c_str());
						}
						securityIssuePointer2 = securityIssuePointer2->next;
					}
				}

				// Informational rated issues...
				if (overallInformational > 0)
				{
					paragraphPointer = addParagraph(securityIssuePointer, Device::Finding);
					if (overallInformational == 1)
						paragraphPointer->paragraph.assign(i18n("One *INFORMATIONAL* rated security issue was identified. *COMPANY* determined that:"));
					else
					{
						paragraphPointer->paragraph.assign(i18n("*COMPANY* identified *NUMBER* *INFORMATIONAL* rated security issues. *COMPANY* determined that:"));
						addValue(paragraphPointer, overallInformational);
					}
					securityIssuePointer2 = securityReport;
					while (securityIssuePointer2 != 0)
					{
						if ((securityIssuePointer2->position == 3) && (securityIssuePointer2->overallRating < 3))
						{
							tempString.assign(securityIssuePointer2->conLine);
							tempString.append(" (see section *SECTIONNO*)");
							addString(paragraphPointer, securityIssuePointer2->reference.c_str());
							addListItem(paragraphPointer, tempString.c_str());
						}
						securityIssuePointer2 = securityIssuePointer2->next;
					}
				}

				// Recommendations...
				securityIssuePointer = addSecurityIssue();
				securityIssuePointer->title.assign(i18n("Recommendations"));
				securityIssuePointer->reference.assign("GEN.SECRECOM.1");
				securityIssuePointer->position = 5;
				paragraphPointer = addParagraph(securityIssuePointer, Device::Finding);
				paragraphPointer->paragraph.assign(i18n("This section is designed to assist in the mitigation of the security issues identified by collating the security issue recommendations into a single location. The recommendations are listed in Table *TABLEREF* together with the issue ratings."));

				// Table...
				errorCode = addTable(paragraphPointer, "SEC-RECOMMEN-TABLE");
				if (errorCode != 0)
					return errorCode;
				// Set Table title...
				paragraphPointer->table->title = i18n("Recommendations");
				// Set Table headings
				addTableHeading(paragraphPointer->table, i18n("Issue"), false);
				addTableHeading(paragraphPointer->table, i18n("Overall"), false);
				addTableHeading(paragraphPointer->table, i18n("Impact"), false);
				addTableHeading(paragraphPointer->table, i18n("Ease"), false);
				addTableHeading(paragraphPointer->table, i18n("Fix"), false);
				addTableHeading(paragraphPointer->table, i18n("Recommendation"), false);
				addTableHeading(paragraphPointer->table, i18n("Section"), false);

				// Table Data...
				securityIssuePointer = securityReport;
				while (securityIssuePointer != 0)
				{
					if (securityIssuePointer->position == 3)
					{

						// Issue...
						addTableData(paragraphPointer->table, securityIssuePointer->title.c_str());

						// Overall...
						if (securityIssuePointer->overallRating > 8)
							addTableData(paragraphPointer->table, "*CRITICAL*");
						else if (securityIssuePointer->overallRating > 6)
							addTableData(paragraphPointer->table, "*HIGH*");
						else if (securityIssuePointer->overallRating > 4)
							addTableData(paragraphPointer->table, "*MEDIUM*");
						else if (securityIssuePointer->overallRating > 2)
							addTableData(paragraphPointer->table, "*LOW*");
						else
							addTableData(paragraphPointer->table, "*INFORMATIONAL*");

						// Impact...
						if (securityIssuePointer->impactRating > 8)
							addTableData(paragraphPointer->table, "*CRITICAL*");
						else if (securityIssuePointer->impactRating > 6)
							addTableData(paragraphPointer->table, "*HIGH*");
						else if (securityIssuePointer->impactRating > 4)
							addTableData(paragraphPointer->table, "*MEDIUM*");
						else if (securityIssuePointer->impactRating > 2)
							addTableData(paragraphPointer->table, "*LOW*");
						else
							addTableData(paragraphPointer->table, "*INFORMATIONAL*");

						// Ease...
						if (securityIssuePointer->easeRating > 8)
							addTableData(paragraphPointer->table, "*TRIVIAL*");
						else if (securityIssuePointer->easeRating > 5)
							addTableData(paragraphPointer->table, "*EASY*");
						else if (securityIssuePointer->easeRating > 2)
							addTableData(paragraphPointer->table, "*MODERATE*");
						else if (securityIssuePointer->easeRating > 0)
							addTableData(paragraphPointer->table, "*CHALLENGING*");
						else
							addTableData(paragraphPointer->table, "*NOTAPPLICABLE*");

						// Fix...
						if (securityIssuePointer->fixRating > 7)
							addTableData(paragraphPointer->table, "*INVOLVED*");
						else if (securityIssuePointer->fixRating > 3)
							addTableData(paragraphPointer->table, "*PLANNED*");
						else
							addTableData(paragraphPointer->table, "*QUICK*");

						// Recommendation...
						recPointer = securityIssuePointer->recLines;
						while (recPointer != 0)
						{
							if (bodyPointer == 0)
								bodyPointer = addTableData(paragraphPointer->table, recPointer->recommendation.c_str());
							else
							{
								if (recPointer->recommendationOr == true)
								{
									bodyPointer = addTableData(paragraphPointer->table, i18n("or"));
									bodyPointer->newCell = false;
								}
								bodyPointer = addTableData(paragraphPointer->table, recPointer->recommendation.c_str());
								bodyPointer->newCell = false;
							}
							recPointer = recPointer->next;
						}
						bodyPointer = 0;

						// Reference...
						addString(paragraphPointer, securityIssuePointer->reference.c_str());
						addTableData(paragraphPointer->table, "*SECTIONNO*");
					}
					securityIssuePointer = securityIssuePointer->next;
				}
			}
		}
	}


	// -----------------------------------------------------------------
	// Configuration Report...
	// -----------------------------------------------------------------

	// Configuration Report?
	if (config->includeConfigurationReport == true)
	{

		if (config->reportFormat == Config::Debug)
		{
			printf("  %s>%s Configuration Report\n", config->COL_GREEN, config->COL_RESET);
			printf("    %s*%s Configuration Introduction\n", config->COL_BLUE, config->COL_RESET);
		}

		// Create Config Report Section...
		configReportPointer = getConfigSection("CONFIG-INTRODUCTION");
		// Section title...
		configReportPointer->title = i18n("Introduction");
		configReportPointer->position = 1;
		// Paragraph...
		paragraphPointer = addParagraph(configReportPointer);
		paragraphPointer->paragraph.assign(i18n("This section details the configuration settings of the *DEVICETYPE* device *DEVICENAME*."));

		// General Device Settings...
		if (general != 0)
			general->generateConfigReport(this);

		if (supportConfigNetworkServices == true)
		{
			// Device Services...
			configReportPointer = getConfigSection("CONFIG-SERVICES");
			configReportPointer->title = i18n("Network Services");
			paragraphPointer = addParagraph(configReportPointer);
			paragraphPointer->paragraph.assign(i18n("Table *TABLEREF* outlines the network services supported by *DEVICETYPE* devices and their status on *DEVICENAME*. The service settings are described in greater detail in the proceeding sections."));
			errorCode = addTable(paragraphPointer, "CONFIG-SERVICES-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("Network services");
			addTableHeading(paragraphPointer->table, i18n("Service"), false);
			addTableHeading(paragraphPointer->table, i18n("Status"), false);
		}

		// Administration settings...
		if (administration != 0)
			administration->generateConfigReport(this);

		// Authentication settings...
		if (authentication != 0)
			authentication->generateConfigReport(this);

		// DNS settings...
		if (dns != 0)
			dns->generateConfigReport(this);

		// Banner settings...
		if (banner != 0)
			banner->generateConfigReport(this);

		// SNMP settings...
		if (snmp != 0)
			snmp->generateConfigReport(this);

		// Filter settings...
		if (filter != 0)
			filter->generateConfigReport(this);

		// Interfaces settings...
		if (interfaces != 0)
			interfaces->generateConfigReport(this);
	}


	// -----------------------------------------------------------------
	// Report Appendix...
	// -----------------------------------------------------------------

	// Appendix section reporting...
	if (config->includeAppendixSection == true)
	{

		if (config->reportFormat == Config::Debug)
			printf("  %s>%s Appendix Sections\n", config->COL_GREEN, config->COL_RESET);

		// Abbreviations section...
		if (config->includeAbbreviations == true)
		{
			if (config->reportFormat == Config::Debug)
				printf("    %s*%s Abbreviations\n", config->COL_BLUE, config->COL_RESET);
			errorCode = generateAppendixAbbreviations();
			if (errorCode != 0)
				return errorCode;
		}

		// Common Ports section...
		if (config->includeNetworkPorts == true)
		{
			if (config->reportFormat == Config::Debug)
				printf("    %s*%s Common Ports\n", config->COL_BLUE, config->COL_RESET);
			if (config->includeAbbreviations != true)
			{
				errorCode = addAppendixAbbreviations();
				if (errorCode != 0)
					return errorCode;
			}
			errorCode = generateAppendixCommonPorts();
			if (errorCode != 0)
				return errorCode;
		}

		// IP Protocols section...
		if (config->includeIPProtocols == true)
		{
			if (config->reportFormat == Config::Debug)
				printf("    %s*%s IP Protocols\n", config->COL_BLUE, config->COL_RESET);
			if ((config->includeAbbreviations == false) && (config->includeNetworkPorts == false))
			{
				errorCode = addAppendixAbbreviations();
				if (errorCode != 0)
					return errorCode;
			}
			errorCode = generateAppendixUsedProtocols();
			if (errorCode != 0)
				return errorCode;
		}

		// ICMP section...
		if (config->includeICMPTypes == true)
		{
			if (config->reportFormat == Config::Debug)
				printf("    %s*%s ICMP Types\n", config->COL_BLUE, config->COL_RESET);
			errorCode = generateAppendixUsedICMPTypes();
			if (errorCode != 0)
				return errorCode;
		}

		// Logging Levels...
		if ((config->includeLoggingLevels == true) && (appendixLoggingLevels == true))
		{
			if (config->reportFormat == Config::Debug)
				printf("    %s*%s Logging Levels\n", config->COL_BLUE, config->COL_RESET);
			errorCode = generateAppendixLoggingLevels();
			if (errorCode != 0)
				return errorCode;
		}

		// Nipper details...
		if (config->includeNipperVersion == true)
		{
			if (config->reportFormat == Config::Debug)
				printf("    %s*%s Nipper Version Details\n", config->COL_BLUE, config->COL_RESET);

			configReportPointer = getAppendixSection("APPENDIX-NIPPERVER");
			configReportPointer->title = i18n("Nipper Details");
			paragraphPointer = addParagraph(configReportPointer);
			addString(paragraphPointer, nipperVersion);
			paragraphPointer->paragraph.assign(i18n("This report was generated using Nipper version *DATA*."));
			paragraphPointer = addParagraph(configReportPointer);
			paragraphPointer->paragraph.assign(i18n("Nipper is an Open Source tool designed to assist security professionals and network system administrators securely configure network infrastructure devices. More information on Nipper and how you can contribute to the project are on the projects web site *URL*http://nipper.titania.co.uk*-URL*."));
		}
	}


	// -----------------------------------------------------------------
	// Linking all the stuff together...
	// -----------------------------------------------------------------

	if (config->reportFormat == Config::Debug)
		printf("  %s>%s Indexing Generation\n", config->COL_GREEN, config->COL_RESET);

	// Sort out secton numbering...
	if (config->reportFormat == Config::Debug)
		printf("    %s*%s Numbering Report Sections\n", config->COL_BLUE, config->COL_RESET);
	numberReportSections();

	// Sort out report table numbering...
	if (config->reportFormat == Config::Debug)
		printf("    %s*%s Numbering Report Tables\n", config->COL_BLUE, config->COL_RESET);
	numberReportTables();

	// Resolve dependent security issues...
	if ((config->includeSecurityAudit == true) && (securityReport != 0))
	{
		if (config->reportFormat == Config::Debug)
			printf("    %s*%s Resolving Dependent Security Issues\n", config->COL_BLUE, config->COL_RESET);
		resolveDependentIssues();
	}

	// Resolve the related security issues...
	if ((config->includeSecurityAudit == true) && (securityReport != 0))
	{
		if (config->reportFormat == Config::Debug)
			printf("    %s*%s Resolving Related Security Issues\n", config->COL_BLUE, config->COL_RESET);
		resolveRelatedIssues();
	}

	return errorCode;
}


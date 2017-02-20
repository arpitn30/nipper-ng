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

#include "../../globaldefs.h"
#include "../device.h"
#include "../general/general.h"
#include "banner.h"


int Banner::generateConfigBannerReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s Banners\n", device->config->COL_BLUE, device->config->COL_RESET);

	// Create Config Report Section...
	configReportPointer = device->getConfigSection("CONFIG-BANNER");
	if (banner != 0)
	{
		if (banner->next != 0)
			configReportPointer->title = i18n("Logon Banner Messages");
		else
			configReportPointer->title = i18n("Logon Banner Message");
	}
	else
		configReportPointer->title = i18n("Logon Banner Message");
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraph.assign(i18n("The importance of banner messages can often be overlooked. Banner messages provide a deterrent by warning against unauthorised access. Furthermore if an attacker has gained unauthorised access to *DEVICENAME*, the banner message can act as evidence of an attackers intent. This section details the banner messages configured on *DEVICENAME*."));

	return 0;
}


int Banner::generateConfigReport(Device *device)
{
	// Variables...
	bannerStruct *bannerPointer = 0;
	bannerTextStruct *bannerTextPointer = 0;
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	int errorCode = 0;

	if (banner != 0)
	{
		generateConfigBannerReport(device);

		configReportPointer = device->getConfigSection("CONFIG-BANNER");

		bannerPointer = banner;
		while (bannerPointer != 0)
		{
			paragraphPointer = device->addParagraph(configReportPointer);
			device->addString(paragraphPointer, bannerPointer->name.c_str());
			paragraphPointer->paragraphTitle.assign(i18n("*DATA* Banner"));
			paragraphPointer->paragraph.assign(bannerPointer->description);
			if (bannerPointer->bannerFile == false)
			{
				paragraphPointer->paragraph.append("*CODE*");
				bannerTextPointer = bannerPointer->bannerText;
				while (bannerTextPointer != 0)
				{
					paragraphPointer->paragraph.append("*CODELINE*");
					paragraphPointer->paragraph.append(bannerTextPointer->bannerLine);
					paragraphPointer->paragraph.append("*-CODELINE*");
					bannerTextPointer = bannerTextPointer->next;
				}
				paragraphPointer->paragraph.append("*-CODE*");
			}
			else
			{
				paragraphPointer = device->addParagraph(configReportPointer);
				device->addString(paragraphPointer, bannerPointer->filename.c_str());
				paragraphPointer->paragraph.assign(i18n("The banner message text is stored in a file called *DATA* on *DEVICENAME*."));
			}
			if (bannerPointer->enabled == false)
			{
				paragraphPointer = device->addParagraph(configReportPointer);
				device->addString(paragraphPointer, bannerPointer->name.c_str());
				paragraphPointer->paragraphTitle.assign(i18n("Note: The *DATA* banner message is disabled."));
			}
			bannerPointer = bannerPointer->next;
		}
	}

	errorCode = generateConfigSpecificReport(device);

	return errorCode;
}


int Banner::generateSecurityReport(Device *device)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	bannerStruct *bannerPointer = 0;
	bannerTextStruct *bannerTextPointer = 0;
	string tempString;
	bool found = false;
	bool warningFound = true;
	bool foundPre = false;
	bool foundPost = false;
	int infoLeak = 0;
	int errorCode = 0;


	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s Banner Checks\n", device->config->COL_BLUE, device->config->COL_RESET);

	bannerPointer = banner;
	while (bannerPointer != 0)
	{
		warningFound = false;
		if (bannerPointer->enabled == true)
		{
			if ((bannerPointer->banner == preLogon) && ((bannerPointer->bannerText != 0) || ((bannerPointer->bannerText == 0) && (bannerPointer->bannerFile == true))))
			{
				foundPre = true;
				// Look for nasties...
				if (bannerPointer->bannerFile == false)
				{
					found = false;
					bannerTextPointer = bannerPointer->bannerText;
					while (bannerTextPointer != 0)
					{
						// Look for warning message...
						if (warningFound == false)
						{
							if (device->isInString(bannerTextPointer->bannerLine.c_str(), i18n("warning")) == true)
								warningFound = true;
							else if (device->isInString(bannerTextPointer->bannerLine.c_str(), i18n("authorised")) == true)
								warningFound = true;
							else if (device->isInString(bannerTextPointer->bannerLine.c_str(), i18n("authorized")) == true)
								warningFound = true;
							else if (device->isInString(bannerTextPointer->bannerLine.c_str(), i18n("prosecute")) == true)
								warningFound = true;
							else if (device->isInString(bannerTextPointer->bannerLine.c_str(), i18n("permission")) == true)
								warningFound = true;
							else if (device->isInString(bannerTextPointer->bannerLine.c_str(), i18n("prohibited")) == true)
								warningFound = true;
						}

						// Hostname...
						if ((device->general != 0) && (found == false))
						{
							if (!device->general->hostname.empty())
							{
								if (device->isInString(bannerTextPointer->bannerLine.c_str(), device->general->hostname.c_str()) == true)
								{
									found = true;
									bannerPointer->leak = containsHostname;
								}
							}
						}

						// Device type...
						if ((device->deviceType != 0) && (found == false))
						{
							if (device->isInString(bannerTextPointer->bannerLine.c_str(), device->deviceType) == true)
							{
								found = true;
								bannerPointer->leak = containsType;
							}
						}

						// Device Make...
						if ((device->deviceMake != 0) && (found == false))
						{
							if (device->isInString(bannerTextPointer->bannerLine.c_str(), device->deviceMake) == true)
							{
								found = true;
								bannerPointer->leak = containsMake;
							}
						}

						// Device Model...
						if ((device->deviceModel != 0) && (found == false))
						{
							if (device->isInString(bannerTextPointer->bannerLine.c_str(), device->deviceModel) == true)
							{
								found = true;
								bannerPointer->leak = containsModel;
							}
						}

						// Device OS...
						if ((device->deviceOS != 0) && (found == false))
						{
							if (device->isInString(bannerTextPointer->bannerLine.c_str(), device->deviceOS) == true)
							{
								found = true;
								bannerPointer->leak = containsOS;
							}
						}

						bannerTextPointer = bannerTextPointer->next;
					}
					if (found == true)
						infoLeak++;
					if (warningFound == false)
						bannerPointer->noWarning = true;
				}
			}
			else if ((bannerPointer->banner == postLogon) && ((bannerPointer->bannerText != 0) || ((bannerPointer->bannerText == 0) && (bannerPointer->bannerFile == true))))
				foundPost = true;
		}

		bannerPointer = bannerPointer->next;
	}


	// Check Pre-Logon banners first...
	if ((preLogonBanner == true) && (foundPre == false))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] No Pre-Logon Banner\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("No Pre-Logon Banner Message"));
		securityIssuePointer->reference.assign("GEN.BANRPREL.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("A pre-logon banner message can be configured on *DEVICETYPE* devices. Logon banners are useful for passing on information to users and, with a carefully worded legal warning, as a deterrant to a potential attacker."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that no pre-logon banner was configured on *DEVICENAME*."));

		// Issue impact...
		securityIssuePointer->impactRating = 3;			// Low
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("A pre-logon banner message is important in warning any potential attacker against unauthorised access to the *DEVICETYPE*. With a carefully worded pre-logon banner, which warns against unauthorised access, if any legal action is taken it would be easier to prove intent on behalf of the attacker."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 0;				// N/A
		paragraphPointer->paragraph.assign(i18n("Without a pre-login banner, an attacker would not be presented with a legal warning against unauthorised access prior to a logon attempt."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 3;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that a carefully worded legal banner should be configured that warns against unauthorised access to *DEVICENAME*."));
		if (strlen(configPreLogonBanner) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(configPreLogonBanner);
		}

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("no pre-logon banner message was configured"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Configure a pre-logon banner message with a carefully worded legal warning"));
	}


	// Banner Information Leakage...
	if (infoLeak > 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Banner Information Leakage\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		if (infoLeak > 1)
			securityIssuePointer->title.assign(i18n("Information Leakage In Banner Messages"));
		else
			securityIssuePointer->title.assign(i18n("Information Leakage In Banner Message"));
		securityIssuePointer->reference.assign("GEN.BANRINFO.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("A banner messages provide users with important information when they logon. Banners should also provide a warning against unauthorised access to the system."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		if (infoLeak > 1)
		{
			device->addValue(paragraphPointer, infoLeak);
			paragraphPointer->paragraph.assign(i18n("*COMPANY* identified information that an attacker could find useful in the *NUMBER* banners listed in Table *TABLEREF*."));
			errorCode = device->addTable(paragraphPointer, tempString.c_str());
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title.assign(i18n("Banners with information leakage"));
			device->addTableHeading(paragraphPointer->table, i18n("Banner"), false);
			device->addTableHeading(paragraphPointer->table, i18n("Connection"), false);
			device->addTableHeading(paragraphPointer->table, i18n("Issue"), false);
			bannerPointer = banner;
			while (bannerPointer != 0)
			{
				if (bannerPointer->leak != noInfoLeak)
				{
					device->addTableData(paragraphPointer->table, bannerPointer->name.c_str());
					if (bannerPointer->connectionType == anyConnection)
						device->addTableData(paragraphPointer->table, i18n("Any"));
					else
					{
						tempString.assign("");
						found = false;
						if ((bannerPointer->connectionType && consoleConnection) == consoleConnection)
						{
							tempString.append(i18n("Console"));
							found = true;
						}
						if ((bannerPointer->connectionType && telnetConnection) == telnetConnection)
						{
							if (found == false)
								found = true;
							else
								tempString.append(", ");
							tempString.append(i18n(""));
						}
						if ((bannerPointer->connectionType && sshConnection) == sshConnection)
						{
							if (found == false)
								found = true;
							else
								tempString.append(", ");
							tempString.append(i18n("*ABBREV*SSH*-ABBREV*"));
						}
						if ((bannerPointer->connectionType && modemConnection) == modemConnection)
						{
							if (found == false)
								found = true;
							else
								tempString.append(", ");
							tempString.append(i18n("Modem"));
						}
						device->addTableData(paragraphPointer->table, tempString.c_str());
					}
					switch (bannerPointer->leak)
					{
						case containsHostname:
							device->addTableData(paragraphPointer->table, i18n("Contains the hostname"));
							break;
						case containsMake:
							device->addTableData(paragraphPointer->table, i18n("Contains the device manufacturer name"));
							break;
						case containsModel:
							device->addTableData(paragraphPointer->table, i18n("Contains the device model"));
							break;
						case containsType:
							device->addTableData(paragraphPointer->table, i18n("Contains the device type"));
							break;
						default:
							device->addTableData(paragraphPointer->table, i18n("Contains the device *ABBREV*OS*-ABBREV*"));
							break;
					}
				}
				bannerPointer = bannerPointer->next;
			}
		}
		else
		{
			bannerPointer = banner;
			while (bannerPointer != 0)
			{
				if (bannerPointer->leak != noInfoLeak)
				{
					device->addString(paragraphPointer, bannerPointer->name.c_str());
					switch (bannerPointer->leak)
					{
						case containsHostname:
							device->addString(paragraphPointer, i18n("hostname"));
							break;
						case containsMake:
							device->addString(paragraphPointer, i18n("device manufacturer name"));
							break;
						case containsModel:
							device->addString(paragraphPointer, i18n("device model"));
							break;
						case containsType:
							device->addString(paragraphPointer, i18n("device type"));
							break;
						default:
							device->addString(paragraphPointer, i18n("device *ABBREV*OS*-ABBREV*"));
							break;
					}
					paragraphPointer->paragraph.assign(i18n("*COMPANY* identified information that an attacker could find useful in a message banner. The *DATA* banner contained the *DATA*."));
				}
				bannerPointer = bannerPointer->next;
			}
		}

		// Issue impact...
		securityIssuePointer->impactRating = 3;			// Low
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("The information leaked in the banner message could assist an attacker in identifying information about the device and could potentially lead to a targetted attack against the device."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 1;				// Trivial
		paragraphPointer->paragraph.assign(i18n("The logon banner message is returned upon connection to *DEVICENAME*."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 3;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that banner messages do not contain information that an attacker could find useful. This information includes the hostname, device make, model and any operating system details. It is also important that no information is revealed that could be used as part of a social engineering attack, such as peoples names and phone numbers. If contact details are required, *COMPANY* recommends that job titles or department names are used."));
		if (strlen(configPreLogonBanner) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(configPreLogonBanner);
		}

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("information leakage in the logon banner message"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Remove the information leakage from the logon banner message"));

		// Related issues...
		device->addRelatedIssue(securityIssuePointer, "GEN.BANRWARN.1");
	}


	// Banner Information Leakage...
	if (warningFound == false)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] No Warning In Logon Banner\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("No Warning In Logon Banner Message"));
		securityIssuePointer->reference.assign("GEN.BANRWARN.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("Logon banner messages should warn against unauthorised access to the device with a notice about any legal action that may be taken if access is obtained. *COMPANY* determined that the logon banner message did not contain an unauthorised use warning message."));

		// Issue impact...
		securityIssuePointer->impactRating = 3;			// Low
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("A carefully worded warning message could deter a casual attacker or malicious user, but not a determined attacker. It would be more difficult to prove any intent without a message warning against unauthorised access if legal action is taken against an attacker."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 0;				// N/A
		paragraphPointer->paragraph.assign(i18n("The logon banner message is returned upon connection to *DEVICENAME*."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 3;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that the banner message is modified to warn against unauthorised access to *DEVICENAME*."));
		if (strlen(configPreLogonBanner) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(configPreLogonBanner);
		}

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("no unauthorised access warning in the logon banner message"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Modify the logon banner message to include a warning against unauthorised access"));

		// Related issues...
		device->addRelatedIssue(securityIssuePointer, "GEN.BANRINFO.1");
	}


	// No Post Logon Banner...
	if ((foundPost == false) && (postLogonBanner == true))
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] No Post Logon Banner\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		securityIssuePointer->title.assign(i18n("No Post Logon Banner Message"));
		securityIssuePointer->reference.assign("GEN.BANRPOST.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("On *DEVICETYPE* devices it is possible to configure a banner message that is presented to users after they have authenticated. The post logon banner is useful for detailing the acceptable use policy and what change control procedures should be followed prior to making any changes to the devices configuration."));
		if (preLogonBanner == false)
			paragraphPointer->paragraph.assign(i18n(" Furthermore, since *DEVICETYPE* do not support any post logon banners, a legal warning should be included to warn against unauthorised access."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that no post logon banner message had been configured on *DEVICENAME*."));

		// Issue impact...
		securityIssuePointer->impactRating = 2;			// Informational
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("An acceptable use message detailing any change control procedures could help to prevent ad-hoc changes being made to the *DEVICETYPE* configuration."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 0;				// N/A
		paragraphPointer->paragraph.assign(i18n("No banner message is sent by *DEVICENAME* after a user logon occurs."));

		// Issue recommendation...
		securityIssuePointer->fixRating = 3;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that a post logon banner message is configured that details the acceptable use and change control procedure."));
		if (strlen(configPostLogonBanner) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(configPostLogonBanner);
		}

		// Conclusions text...
		securityIssuePointer->conLine.append(i18n("no post logon banner message is configured"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Configure a post logon banner message which details the acceptable use and change control policies"));
	}

	errorCode = generateSecuritySpecificReport(device);

	return errorCode;
}

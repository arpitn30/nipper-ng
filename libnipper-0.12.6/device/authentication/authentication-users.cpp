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
#include "authentication.h"


Authentication::localUserConfig *Authentication::getUser(const char *username)
{
	// Variables...
	localUserConfig *localUserPointer = 0;

	// Create
	if (localUser == 0)
	{
		localUser = new (localUserConfig);
		localUserPointer = localUser;
	}
	else
	{
		localUserPointer = localUser;
		while (localUserPointer->next != 0)
		{
			if (localUserPointer->username.compare(username) == 0)
				return localUserPointer;
			else
				localUserPointer = localUserPointer->next;
		}
		if (localUserPointer->username.compare(username) == 0)
			return localUserPointer;
		localUserPointer->next = new (localUserConfig);
		localUserPointer = localUserPointer->next;
	}

	// Init...
	localUserPointer->username.assign(username);
	localUserPointer->encryption = clearText;
	localUserPointer->aclSupported = false;
	localUserPointer->readOnly = false;
	localUserPointer->dictionaryPassword = false;
	localUserPointer->weakPassword = Device::passwordPassed;
	localUserPointer->adminAccess = false;
	localUserPointer->next = 0;

	return localUserPointer;
}


int Authentication::generateConfigLocalUserReport(Device *device)
{
	// Variables...
	Device::configReportStruct *configReportPointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	localUserConfig *localUserPointer = 0;
	int errorCode = 0;

	configReportPointer = device->getConfigSection("CONFIG-AUTH");
	paragraphPointer = device->addParagraph(configReportPointer);
	paragraphPointer->paragraphTitle.assign(i18n("Users"));
	paragraphPointer->paragraph.assign(i18n("This section details the users configured on *DEVICENAME*."));
	if (strlen(configDeviceSpecificLocalUsers) > 0)
	{
		paragraphPointer = device->addParagraph(configReportPointer);
		paragraphPointer->paragraph.append(configDeviceSpecificLocalUsers);
	}

	// Local Users Table...
	errorCode = device->addTable(paragraphPointer, "CONFIG-AUTHUSERS-TABLE");
	if (errorCode != 0)
		return errorCode;
	paragraphPointer->table->title = i18n("Configured users");
	device->addTableHeading(paragraphPointer->table, i18n("User"), false);
	device->addTableHeading(paragraphPointer->table, i18n("Password"), true);
	if (encryptionSupported == true)
		device->addTableHeading(paragraphPointer->table, i18n("Encryption"), false);
	if (privilegeLevelSupported == true)
		device->addTableHeading(paragraphPointer->table, privilegeLevelText, false);
	if (outboundACLSupported == true)
		device->addTableHeading(paragraphPointer->table, filterText, false);

	localUserPointer = localUser;
	while (localUserPointer != 0)
	{
		device->addTableData(paragraphPointer->table, localUserPointer->username.c_str());
		device->addTableData(paragraphPointer->table, localUserPointer->password.c_str());
		if (encryptionSupported == true)
		{
			switch (localUserPointer->encryption)
			{
				case clearText:
					device->addTableData(paragraphPointer->table, i18n("None"));
					break;
				case md5Encryption:
					device->addTableData(paragraphPointer->table, i18n("*ABBREV*MD5*-ABBREV*"));
					break;
				case cisco7Encryption:
					device->addTableData(paragraphPointer->table, i18n("Cisco Type 7"));
					break;
				case netscreenEncryption:
					device->addTableData(paragraphPointer->table, i18n("NetScreen"));
					break;
				case md4Encryption:
					device->addTableData(paragraphPointer->table, i18n("*ABBREV*MD4*-ABBREV*"));
					break;
				case ntEncryption:
					device->addTableData(paragraphPointer->table, i18n("*ABBREV*NT*-ABBREV*"));
					break;
				case desEncryption:
					device->addTableData(paragraphPointer->table, i18n("*ABBREV*DES*-ABBREV*"));
					break;
				default:
					device->addTableData(paragraphPointer->table, i18n("*ABBREV*AES*-ABBREV*"));
					break;
			}
		}
		if (privilegeLevelSupported == true)
			device->addTableData(paragraphPointer->table, localUserPointer->privilegeLevel.c_str());
		if (outboundACLSupported == true)
		{
			if (localUserPointer->aclSupported == true)
				device->addTableData(paragraphPointer->table, localUserPointer->outboundACL.c_str());
			else
				device->addTableData(paragraphPointer->table, i18n("N/A"));
		}
		localUserPointer = localUserPointer->next;
	}

	return errorCode;
}


int Authentication::generateUserSecurityReport(Device *device, int empty, int dictionary, int weak)
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = 0;
	Device::paragraphStruct *paragraphPointer = 0;
	localUserConfig *localUserPointer = 0;
	bool found = false;
	int errorCode = 0;

	if (empty > 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Users With No Password\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		if (empty > 1)
			securityIssuePointer->title.assign(i18n("Users Were Configured With No Password"));
		else
			securityIssuePointer->title.assign(i18n("A User Was Configured With No Password"));
		securityIssuePointer->reference.assign("GEN.AUTHNPAS.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("Authentication credentials are configured on *DEVICETYPE* devices in order to help prevent unauthorised access and to restrict the access to specific authorised users."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

		// Multiple found...
		if (empty > 1)
		{
			device->addValue(paragraphPointer, empty);
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* of the authentication credentials were configured with no password. These are listed in Table *TABLEREF*."));

			errorCode = device->addTable(paragraphPointer, "SECURITY-NOPASSWORDUSERS-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("Users with no password");
		}

		// One found...
		else
		{
			device->addValue(paragraphPointer, empty);
			paragraphPointer->paragraph.assign(i18n("*COMPANY* determined that *NUMBER* user was configured with no password. This is shown in Table *TABLEREF*."));

			errorCode = device->addTable(paragraphPointer, "SECURITY-NOPASSWORDUSER-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("User with no password");
		}

		device->addTableHeading(paragraphPointer->table, i18n("User"), false);
		if (privilegeLevelSupported == true)
			device->addTableHeading(paragraphPointer->table, privilegeLevelText, false);
		if (outboundACLSupported == true)
			device->addTableHeading(paragraphPointer->table, filterText, false);

		found = false;
		localUserPointer = localUser;
		while (localUserPointer != 0)
		{
			if (localUserPointer->password.empty())
			{
				found = true;
				device->addTableData(paragraphPointer->table, localUserPointer->username.c_str());
				if (privilegeLevelSupported == true)
					device->addTableData(paragraphPointer->table, localUserPointer->privilegeLevel.c_str());
				if (outboundACLSupported == true)
				{
					if (localUserPointer->aclSupported == true)
						device->addTableData(paragraphPointer->table, localUserPointer->outboundACL.c_str());
					else
						device->addTableData(paragraphPointer->table, i18n("N/A"));
				}
			}
			localUserPointer = localUserPointer->next;
		}

		// Issue impact...
		if (found == true)
			securityIssuePointer->impactRating = 10;		// Critical
		else
			securityIssuePointer->impactRating = 8;		// High
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("With no password configured, an attacker or malicious user could gain access to *DEVICENAME* by authenticating without providing a password. The attacker could enumerate information about the device and networks configuration. The attacker may also be able to use the device to attack other network devices."));
		if (found == true)
			paragraphPointer->paragraph.append(i18n(" Furthermore, with administrative access, the attacker could reconfigure *DEVICENAME* in order to gain access to other devices, monitor network connections or perform a *ABBREV*DoS*-ABBREV* attack."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 8;				// Easy
		paragraphPointer->paragraph.assign(i18n("The attacker would simply need to connect to an authentication service on *DEVICENAME* and would not need to provide a password. Tools to connect to authentication services are provided with most *ABBREV*OS*-ABBREV*. A number of network security testing tools can check authentication services in order to identify any weak authentication credentials."));
		if ((radiusServer != 0) || (tacacsServer != 0) || (ldapServer != 0) || (securidServer != 0) || (kerberosServer != 0) || (ntServer != 0))
		{
			securityIssuePointer->easeRating = 6;				// Easy
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			paragraphPointer->paragraph.assign(i18n("External authentication servers are configured to provide centralised remote authentication of users. This can make exploiting this issue more difficult. However, if a remote authentication service becomes unavailable, either through networking issues or a *ABBREV*DoS*-ABBREV* attack, the authentication could revert to using locally configured authentication credentials. A variety of *ABBREV*DoS*-ABBREV* tools are available on the Internet."));
		}

		// Issue recommendation...
		securityIssuePointer->fixRating = 3;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that a strong password should be immediately configured for all *DEVICETYPE* users. *COMPANY* recommends that passwords:"));
		errorCode = device->addPasswordRequirements(paragraphPointer);
		if (errorCode != 0)
			return errorCode;
		if (strlen(configAccessAuthentication) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(configAccessAuthentication);
		}

		// Conclusions text...
		if (empty > 1)
			securityIssuePointer->conLine.append(i18n("authentication credentials were configured with no password"));
		else
			securityIssuePointer->conLine.append(i18n("an authentication credential was configured with no password"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Configure strong authentication credential passwords for all accounts"));

		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHDPAS.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHWPAS.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHNTAC.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHDTAC.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHWTAC.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHNRAD.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHDRAD.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHWRAD.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHDLDA.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHWLDA.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHLETA.1");
	}


	if (dictionary > 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Users With Dictionary Based Passwords\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		if (dictionary > 1)
			securityIssuePointer->title.assign(i18n("Users Were Configured With Dictionary-Based Passwords"));
		else
			securityIssuePointer->title.assign(i18n("A User Was Configured With A Dictionary-Based Password"));
		securityIssuePointer->reference.assign("GEN.AUTHDPAS.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("Authentication credentials are configured on *DEVICETYPE* devices in order to help prevent unauthorised access and to restrict the access to specific authorised users."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

		// Multiple found...
		if (dictionary > 1)
		{
			device->addValue(paragraphPointer, dictionary);
			paragraphPointer->paragraph.assign(i18n("A dictionary of passwords was used to check the strength of the passwords for the local users on *DEVICENAME*. *COMPANY* determined that *NUMBER* of the authentication credentials were configured with a dictionary-based password. These are listed in Table *TABLEREF*."));

			errorCode = device->addTable(paragraphPointer, "SECURITY-DICTPASSWORDUSERS-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("Users with dictionary-based password");
		}

		// One found...
		else
		{
			device->addValue(paragraphPointer, dictionary);
			paragraphPointer->paragraph.assign(i18n("A dictionay of passwords was used to check the strength of the passwords for the local users on *DEVICENAME*. *COMPANY* determined that *NUMBER* user was configured with a dictionary-based password. This is shown in Table *TABLEREF*."));

			errorCode = device->addTable(paragraphPointer, "SECURITY-DICTPASSWORDUSER-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("User with a dictionary-based password");
		}

		device->addTableHeading(paragraphPointer->table, i18n("User"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Password"), true);
		if (privilegeLevelSupported == true)
			device->addTableHeading(paragraphPointer->table, privilegeLevelText, false);
		if (outboundACLSupported == true)
			device->addTableHeading(paragraphPointer->table, filterText, false);

		found = false;
		localUserPointer = localUser;
		while (localUserPointer != 0)
		{
			if (localUserPointer->dictionaryPassword == true)
			{
				found = true;
				device->addTableData(paragraphPointer->table, localUserPointer->username.c_str());
				device->addTableData(paragraphPointer->table, localUserPointer->password.c_str());
				if (privilegeLevelSupported == true)
					device->addTableData(paragraphPointer->table, localUserPointer->privilegeLevel.c_str());
				if (outboundACLSupported == true)
				{
					if (localUserPointer->aclSupported == true)
						device->addTableData(paragraphPointer->table, localUserPointer->outboundACL.c_str());
					else
						device->addTableData(paragraphPointer->table, i18n("N/A"));
				}
			}
			localUserPointer = localUserPointer->next;
		}

		// Issue impact...
		if (found == true)
			securityIssuePointer->impactRating = 9;		// Critical
		else
			securityIssuePointer->impactRating = 7;		// High
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("With access to *DEVICENAME* the attacker could enumerate information about the device and the networks configuration. The attacker may also be able to use the device to attack other network devices, possibly bypassing any access restrictions."));
		if (found == true)
			paragraphPointer->paragraph.append(i18n(" Furthermore, with administrative access, the attacker could reconfigure *DEVICENAME* in order to gain access to other devices, monitor network connections or perform a *ABBREV*DoS*-ABBREV* attack."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 7;				// Easy
		paragraphPointer->paragraph.assign(i18n("Attackers will often have access to a collection of password dictionaries and some can be downloaded from the Internet. These dictionaries are lists of well known passwords, names, places, sport teams and so on. Experienced attackers may have an extensive collection of password dictionaries that contain passwords that they have extracted whilst attacking various systems. These password dictionaries can then be used to check authentication credentials of other systems. Tools are available on the Internet that can use a password dictionary to guess the authentication credentials. Once a password has been identified, the tools to connect to authentication services are provided with most *ABBREV*OS*-ABBREV*."));
		if ((radiusServer != 0) || (tacacsServer != 0) || (ldapServer != 0) || (securidServer != 0) || (kerberosServer != 0) || (ntServer != 0))
		{
			securityIssuePointer->easeRating = 5;				// Moderate
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			paragraphPointer->paragraph.assign(i18n("External authentication servers are configured to provide centralised remote authentication of users. This can make exploiting this issue more difficult. However, if a remote authentication service becomes unavailable, either through networking issues or a *ABBREV*DoS*-ABBREV* attack, the authentication could revert to using locally configured authentication credentials. A variety of *ABBREV*DoS*-ABBREV* tools are available on the Internet."));
		}

		// Issue recommendation...
		securityIssuePointer->fixRating = 3;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that a strong password should be configured for all *DEVICETYPE* users. *COMPANY* recommends that passwords:"));
		errorCode = device->addPasswordRequirements(paragraphPointer);
		if (errorCode != 0)
			return errorCode;
		if (strlen(configAccessAuthentication) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(configAccessAuthentication);
		}

		// Conclusions text...
		if (dictionary > 1)
			securityIssuePointer->conLine.append(i18n("dictionary-based authentication credential passwords were configured"));
		else
			securityIssuePointer->conLine.append(i18n("a dictionary-based authentication credential password was configured"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Configure strong authentication credential passwords for all users"));

		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHNPAS.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHWPAS.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHNTAC.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHDTAC.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHWTAC.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHNRAD.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHDRAD.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHWRAD.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHDLDA.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHWLDA.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHLETA.1");
	}

	if (weak > 0)
	{
		if (device->config->reportFormat == Config::Debug)
			printf("    %s*%s [ISSUE] Users With Weak Passwords\n", device->config->COL_BLUE, device->config->COL_RESET);

		securityIssuePointer = device->addSecurityIssue();
		if (weak > 1)
			securityIssuePointer->title.assign(i18n("Users Were Configured With Weak Passwords"));
		else
			securityIssuePointer->title.assign(i18n("A User Was Configured With A Weak Password"));
		securityIssuePointer->reference.assign("GEN.AUTHWPAS.1");

		// Issue finding...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);
		paragraphPointer->paragraph.assign(i18n("Authentication credentials are configured on *DEVICETYPE* devices in order to help prevent unauthorised access and to restrict the access to specific authorised users."));
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Finding);

		// Multiple found...
		if (weak > 1)
		{
			device->addValue(paragraphPointer, weak);
			paragraphPointer->paragraph.assign(i18n("The passwords on *DEVICENAME* were tested in order to determine their strength against specific criteria. *COMPANY* determined that *NUMBER* of the authentication credential passwords did not meet the required criteria and are therefore considered weak. The strength criteria for passwords is listed with the recommendations. These weak passwords are listed in Table *TABLEREF*."));

			errorCode = device->addTable(paragraphPointer, "SECURITY-WEAKPASSWORDUSERS-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("Weak with dictionary-based password");
		}

		// One found...
		else
		{
			device->addValue(paragraphPointer, weak);
			paragraphPointer->paragraph.assign(i18n("The passwords on *DEVICENAME* were tested in order to determine their strength against specific criteria. *COMPANY* determined that *NUMBER* of the authentication credential passwords did not meet the required criteria and are therefore considered weak. The strength criteria for passwords is listed with the recommendations. The weak password is shown in Table *TABLEREF*."));

			errorCode = device->addTable(paragraphPointer, "SECURITY-WEAKPASSWORDUSER-TABLE");
			if (errorCode != 0)
				return errorCode;
			paragraphPointer->table->title = i18n("User with a dictionary-based password");
		}

		device->addTableHeading(paragraphPointer->table, i18n("User"), false);
		device->addTableHeading(paragraphPointer->table, i18n("Password"), true);
		if (privilegeLevelSupported == true)
			device->addTableHeading(paragraphPointer->table, privilegeLevelText, false);
		if (outboundACLSupported == true)
			device->addTableHeading(paragraphPointer->table, filterText, false);
		device->addTableHeading(paragraphPointer->table, i18n("Description"), true);

		found = false;
		localUserPointer = localUser;
		while (localUserPointer != 0)
		{
			if (localUserPointer->weakPassword != Device::passwordPassed)
			{
				found = true;
				device->addTableData(paragraphPointer->table, localUserPointer->username.c_str());
				device->addTableData(paragraphPointer->table, localUserPointer->password.c_str());
				if (privilegeLevelSupported == true)
					device->addTableData(paragraphPointer->table, localUserPointer->privilegeLevel.c_str());
				if (outboundACLSupported == true)
				{
					if (localUserPointer->aclSupported == true)
						device->addTableData(paragraphPointer->table, localUserPointer->outboundACL.c_str());
					else
						device->addTableData(paragraphPointer->table, i18n("N/A"));
				}

				switch (localUserPointer->weakPassword)
				{
					case Device::passwordShort:
						device->addTableData(paragraphPointer->table, i18n("The password was too short"));
						break;
					case Device::passwordRepeatChars:
						device->addTableData(paragraphPointer->table, i18n("Password characters were repeated too often"));
						break;
					case Device::passwordMakeup:
						device->addTableData(paragraphPointer->table, i18n("The password did not meet the minimum complexity requirements"));
						break;
					case Device::passwordUsername:
						device->addTableData(paragraphPointer->table, i18n("The username was part of the password"));
						break;
					case Device::passwordHostname:
						device->addTableData(paragraphPointer->table, i18n("The device hostname was part of the password"));
						break;
					case Device::passwordDictSubst:
						device->addTableData(paragraphPointer->table, i18n("The password was dictionary-based with character substitution"));
						break;
					case Device::passwordDictAppend:
						device->addTableData(paragraphPointer->table, i18n("The password was dictionary-based with characters appended"));
						break;
					default:
						device->addTableData(paragraphPointer->table, i18n("The password contains a common character sequence"));
						break;
				}
			}
			localUserPointer = localUserPointer->next;
		}

		// Issue impact...
		if (found == true)
			securityIssuePointer->impactRating = 6;		// Medium
		else
			securityIssuePointer->impactRating = 5;		// Medium
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Impact);
		paragraphPointer->paragraph.assign(i18n("With access to *DEVICENAME* the attacker could enumerate information about the device and the networks configuration. The attacker may also be able to use the device to attack other network devices, possibly bypassing any access restrictions."));
		if (found == true)
			paragraphPointer->paragraph.append(i18n(" Furthermore, with administrative access, the attacker could reconfigure *DEVICENAME* in order to gain access to other devices, monitor network connections or perform a *ABBREV*DoS*-ABBREV* attack."));

		// Issue ease...
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
		securityIssuePointer->easeRating = 5;				// Moderate
		paragraphPointer->paragraph.assign(i18n("Tools that can brute-force authentication credentials are available on the Internet. The attacker would typically attempt to guess the password first through a dictionary attack prior to a brute force attack. This is due to the ammount of time a brute force attack can take. However, a simple password can take an exponentially shorter period of time to determine than a complex one. Once a password has been identified, the tools to connect to authentication services are provided with most *ABBREV*OS*-ABBREV*."));
		if ((radiusServer != 0) || (tacacsServer != 0) || (ldapServer != 0) || (securidServer != 0) || (kerberosServer != 0) || (ntServer != 0))
		{
			securityIssuePointer->easeRating = 2;				// Challenging
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Ease);
			paragraphPointer->paragraph.assign(i18n("External authentication servers are configured to provide centralised remote authentication of users. This can make exploiting this issue more difficult. However, if a remote authentication service becomes unavailable, either through networking issues or a *ABBREV*DoS*-ABBREV* attack, the authentication could revert to using locally configured authentication credentials. A variety of *ABBREV*DoS*-ABBREV* tools are available on the Internet."));
		}

		// Issue recommendation...
		securityIssuePointer->fixRating = 3;				// Trivial
		paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
		paragraphPointer->paragraph.assign(i18n("*COMPANY* recommends that a strong password should be configured for all *DEVICETYPE* users. *COMPANY* recommends that passwords:"));
		errorCode = device->addPasswordRequirements(paragraphPointer);
		if (errorCode != 0)
			return errorCode;
		if (strlen(configAccessAuthentication) > 0)
		{
			paragraphPointer = device->addParagraph(securityIssuePointer, Device::Recommendation);
			paragraphPointer->paragraph.assign(configAccessAuthentication);
		}

		// Conclusions text...
		if (weak > 1)
			securityIssuePointer->conLine.append(i18n("weak authentication credential passwords were configured"));
		else
			securityIssuePointer->conLine.append(i18n("a weak authentication credential password was configured"));

		// Recommendation list text...
		device->addRecommendation(securityIssuePointer, i18n("Configure strong authentication credential passwords for all users"));

		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHNPAS.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHDPAS.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHNTAC.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHDTAC.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHWTAC.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHNRAD.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHDRAD.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHWRAD.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHDLDA.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHWLDA.1");
		device->addRelatedIssue(securityIssuePointer, "GEN.AUTHLETA.1");
	}

	return errorCode;
}


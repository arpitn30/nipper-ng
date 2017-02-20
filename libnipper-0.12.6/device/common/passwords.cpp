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
#include <string>
#include <cstring>

#include "../../globaldefs.h"
#include "../device.h"
#include "../general/general.h"


bool Device::isInString(const char *haystack, const char *needle)
{
	// Variables...
	int needleSize = 0;
	int haystackSize = 0;
	int position = 0;
	int numberOfChecks = 0;

	// Check Length...
	needleSize = strlen(needle);
	haystackSize = strlen(haystack);
	if (needleSize > haystackSize)
		return false;

	// Checks...
	numberOfChecks = haystackSize - needleSize;
	while (position < numberOfChecks)
	{
		if (strncasecmp(haystack + position, needle, needleSize) == 0)
			return true;
		position++;
	}

	return false;
}


Device::weakPasswordEnum Device::isPasswordWeak(const char *password, const char *username)
{
	// Variables...
	string tempPassword;
	size_t charPosition;
	bool contUpper = false;
	bool contLower = false;
	bool contUpperOrLower = false;
	bool contNumber = false;
	bool contSpecial = false;
	unsigned int loop = 0;
	unsigned int hitCount = 0;
	unsigned int position = 0;

	// Check length first
	if (config->minimumPasswordLength != 0)
	{
		if (config->minimumPasswordLength > strlen(password))
			return Device::passwordShort;
	}

	// Get password components
	for (loop = 0; loop < strlen(password); loop++)
	{
		// check for lowercase
		if ((password[loop] > 96) && (password[loop] < 123))
		{
			contLower = true;
			contUpperOrLower = true;
		}

		// check for upper
		else if ((password[loop] > 64) && (password[loop] < 91))
		{
			contUpper = true;
			contUpperOrLower = true;
		}

		// check for number
		else if ((password[loop] > 47) && (password[loop] < 58))
			contNumber = true;

		// check for special chars
		else
			contSpecial = true;
	}

	// Check password components
	if ((config->passwordsMustIncludeLowers == true) && (contLower == false))
		return passwordMakeup;
	if ((config->passwordsMustIncludeUppers == true) && (contUpper == false))
		return passwordMakeup;
	if ((config->passwordsMustIncludeEitherCase == true) && (contUpperOrLower == false))
		return passwordMakeup;
	if ((config->passwordsMustIncludeNumbers == true) && (contNumber == false))
		return passwordMakeup;
	if ((config->passwordsMustIncludeSpecials == true) && (contSpecial == false))
		return passwordMakeup;

	// Check Character Reuse...
	if (config->maximumRepeatedChars > 0)
	{
		for (loop = 0; loop < strlen(password); loop++)
		{
			position = loop + 1;
			hitCount = 0;
			while (password[position] != 0)
			{
				if (password[position] == password[loop])
				{
					hitCount++;
					if (hitCount > config->maximumRepeatedChars)
						return passwordRepeatChars;
				}
				position++;
			}
		}
	}

	// Check username in password...
	if ((config->differentFromHostname == true) && (username != 0))
	{
		if (isInString(password, username) == true)
			return passwordUsername;
	}

	if (general != 0)
	{
		// Check hostname in password...
		if ((config->differentFromHostname == true) && (!general->hostname.empty()))
		{
			if (isInString(password, general->hostname.c_str()) == true)
				return passwordHostname;
		}
	}

	// Check device information in password...
	if ((config->differentFromHostname == true) && (deviceModel != 0))
	{
		if (isInString(password, deviceModel) == true)
			return passwordDeviceInfo;
	}
	if ((config->differentFromHostname == true) && (deviceMake != 0))
	{
		if (isInString(password, deviceMake) == true)
			return passwordDeviceInfo;
	}

	// Check dictionary character substitutions...
	if (config->noDictionaryCharacterSubst == true)
	{
		// 1's
		if (strchr(password, '1') != 0)
		{
			tempPassword.assign(password);
			charPosition = tempPassword.find('1');
			while (charPosition != tempPassword.npos)
			{
				tempPassword.replace(charPosition, 1, 1, 'i');
				charPosition = tempPassword.find('1');
			}
			if (isDictionaryPassword(tempPassword.c_str()) == true)
				return passwordDictSubst;
			// Incl 3's
			if (strchr(password, '3') != 0)
			{
				charPosition = tempPassword.find('3');
				while (charPosition != tempPassword.npos)
				{
					tempPassword.replace(charPosition, 1, 1, 'e');
					charPosition = tempPassword.find('3');
				}
				if (isDictionaryPassword(tempPassword.c_str()) == true)
					return passwordDictSubst;
			}
			// Incl 5's
			if (strchr(password, '5') != 0)
			{
				charPosition = tempPassword.find('5');
				while (charPosition != tempPassword.npos)
				{
					tempPassword.replace(charPosition, 1, 1, 's');
					charPosition = tempPassword.find('5');
				}
				if (isDictionaryPassword(tempPassword.c_str()) == true)
					return passwordDictSubst;
			}
			// Incl 0's
			if (strchr(password, '0') != 0)
			{
				charPosition = tempPassword.find('0');
				while (charPosition != tempPassword.npos)
				{
					tempPassword.replace(charPosition, 1, 1, 'o');
					charPosition = tempPassword.find('0');
				}
				if (isDictionaryPassword(tempPassword.c_str()) == true)
					return passwordDictSubst;
			}
		}

		// 3's
		if (strchr(password, '3') != 0)
		{
			tempPassword.assign(password);
			charPosition = tempPassword.find('3');
			while (charPosition != tempPassword.npos)
			{
				tempPassword.replace(charPosition, 1, 1, 'e');
				charPosition = tempPassword.find('3');
			}
			if (isDictionaryPassword(tempPassword.c_str()) == true)
				return passwordDictSubst;
			// Incl 5's
			if (strchr(password, '5') != 0)
			{
				charPosition = tempPassword.find('5');
				while (charPosition != tempPassword.npos)
				{
					tempPassword.replace(charPosition, 1, 1, 's');
					charPosition = tempPassword.find('5');
				}
				if (isDictionaryPassword(tempPassword.c_str()) == true)
					return passwordDictSubst;
			}
			// Incl 0's
			if (strchr(password, '0') != 0)
			{
				charPosition = tempPassword.find('0');
				while (charPosition != tempPassword.npos)
				{
					tempPassword.replace(charPosition, 1, 1, 'o');
					charPosition = tempPassword.find('0');
				}
				if (isDictionaryPassword(tempPassword.c_str()) == true)
					return passwordDictSubst;
			}
		}

		// 5's
		if (strchr(password, '5') != 0)
		{
			tempPassword.assign(password);
			charPosition = tempPassword.find('5');
			while (charPosition != tempPassword.npos)
			{
				tempPassword.replace(charPosition, 1, 1, 's');
				charPosition = tempPassword.find('5');
			}
			if (isDictionaryPassword(tempPassword.c_str()) == true)
				return passwordDictSubst;
			// Incl 0's
			if (strchr(password, '0') != 0)
			{
				charPosition = tempPassword.find('0');
				while (charPosition != tempPassword.npos)
				{
					tempPassword.replace(charPosition, 1, 1, 'o');
					charPosition = tempPassword.find('0');
				}
				if (isDictionaryPassword(tempPassword.c_str()) == true)
					return passwordDictSubst;
			}
		}

		// 0's
		if (strchr(password, '0') != 0)
		{
			tempPassword.assign(password);
			charPosition = tempPassword.find('0');
			while (charPosition != tempPassword.npos)
			{
				tempPassword.replace(charPosition, 1, 1, 'o');
				charPosition = tempPassword.find('0');
			}
			if (isDictionaryPassword(tempPassword.c_str()) == true)
				return passwordDictSubst;
		}
	}

	// Check dictionary appends...
	if (config->noCommonDictionaryAppends == true)
	{
		// 1
		if (password[strlen(password) - 1] == '1')
		{
			tempPassword.assign(password);
			tempPassword.resize(tempPassword.length() - 1);
			if (isDictionaryPassword(tempPassword.c_str()) == true)
				return passwordDictAppend;
		}

		// 1!
		else if ((password[strlen(password) - 2] == '1') && (password[strlen(password) - 1] == '!'))
		{
			tempPassword.assign(password);
			tempPassword.resize(tempPassword.length() - 2);
			if (isDictionaryPassword(tempPassword.c_str()) == true)
				return passwordDictAppend;
		}

		// 12
		else if ((password[strlen(password) - 2] == '1') && (password[strlen(password) - 1] == '2'))
		{
			tempPassword.assign(password);
			tempPassword.resize(tempPassword.length() - 2);
			if (isDictionaryPassword(tempPassword.c_str()) == true)
				return passwordDictAppend;
		}

		// 123
		else if ((password[strlen(password) - 3] == '1') && (password[strlen(password) - 2] == '2') && (password[strlen(password) - 1] == '3'))
		{
			tempPassword.assign(password);
			tempPassword.resize(tempPassword.length() - 2);
			if (isDictionaryPassword(tempPassword.c_str()) == true)
				return passwordDictAppend;
		}

		// !
		if (password[strlen(password) - 1] == '!')
		{
			tempPassword.assign(password);
			tempPassword.resize(tempPassword.length() - 1);
			if (isDictionaryPassword(tempPassword.c_str()) == true)
				return passwordDictAppend;
		}
	}

	// Check for character sequences in password...
	if (config->noCharacterSequences == true)
	{
		if (strstr(password, "1234") != 0)
			return passwordCharSeq;
		if (isInString(password, "qwerty") == true)
			return passwordCharSeq;
		if (isInString(password, "abcd") == true)
			return passwordCharSeq;
	}

	return passwordPassed;
}


bool Device::isDictionaryPassword(const char *password)
{
	// Variables...
	struct Device::dictionaryStruct *dictionaryPointer = 0;

	dictionaryPointer = dictionary;
	while (dictionaryPointer != 0)
	{
		if (strcasecmp(password, dictionaryPointer->word) == 0)
			return true;
		dictionaryPointer = dictionaryPointer->next;
	}

	return false;
}


const char *Device::isEncryptedDictionaryPassword(const char *password)
{
	// Variables...
	struct Device::encryptDictionaryStruct *dictionaryPointer = 0;

	dictionaryPointer = encryptedDictionary;
	while (dictionaryPointer != 0)
	{
		if (strcmp(dictionaryPointer->hash, password) == 0)
			return dictionaryPointer->password;
		dictionaryPointer = dictionaryPointer->next;
	}

	return "";
}


void Device::addJohnPassword(const char *user, const char *password)
{
	// Variables...
	johnPasswordStruct *johnPointer = 0;

	// Create...
	if (johnPassword == 0)
	{
		johnPassword = new (johnPasswordStruct);
		johnPointer = johnPassword;
	}
	else
	{
		johnPointer = johnPassword;
		while (johnPointer->next != 0)
			johnPointer = johnPointer->next;
		johnPointer->next = new (johnPasswordStruct);
		johnPointer = johnPointer->next;
	}

	// Init...
	johnPointer->next = 0;
	johnPointer->user.assign(user);
	johnPointer->password.assign(password);
}


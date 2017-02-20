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

// This file contains the code for IOS reporting

void iosKeysConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct keyChain *keyChainPointer = 0;
	struct keyConfig *keyPointer = 0;
	char tempString[nipper->maxSize];

	output_table(nipper, true, settings_keys_table, &settings_keys_heading);
	keyChainPointer = nipper->ios->chain;
	while (keyChainPointer != 0)
	{
		keyPointer = keyChainPointer->key;
		while (keyPointer != 0)
		{
			fprintf(nipper->reportFile, "%s%s%s%d", nipper->tablerow_start, keyChainPointer->name, nipper->tablerow_mid, keyPointer->keyNumber);
			if (nipper->passwords == true)
			{
				outputFriendly(keyPointer->key, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, tempString);
			}
			fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
			keyPointer = keyPointer->next;
		}
		keyChainPointer = keyChainPointer->next;
	}
	output_table(nipper, false, settings_keys_table, &settings_keys_heading);
}

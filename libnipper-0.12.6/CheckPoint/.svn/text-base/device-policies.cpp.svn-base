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
#include <cstring>

#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "device.h"


int CheckPointDevice::processPolicyCollections(ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	policyCollections *policyPointer = 0;

	if (config->reportFormat == Config::Debug)
		printf("%sPolicy Collection Start Line:%s %s\n", config->COL_GREEN, config->COL_RESET, line);

	while ((feof(inputFile) == 0) && (command->part(0)[0] != ')'))
	{

		// Read a line from the config...
		readLine(line, lineSize);

		// Split it up into parts...
		command->setConfigLine(line);

		// New policy...
		if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0))
		{
			if (config->reportFormat == Config::Debug)
				printf("%sPolicy Start Line:%s %s\n", config->COL_GREEN, config->COL_RESET, line);

			// Create policy
			if (policies == 0)
			{
				policies = new (policyCollections);
				policyPointer = policies;
			}
			else
			{
				policyPointer = policies;
				while (policyPointer->next != 0)
					policyPointer = policyPointer->next;
				policyPointer->next = new (policyCollections);
				policyPointer = policyPointer->next;
			}

			// Init new policy...
			policyPointer->next = 0;
			policyPointer->policyName.assign(command->part(1) + 1);

			while ((feof(inputFile) == 0) && (command->part(0)[0] != ')'))
			{

				// Read a line from the config...
				readLine(line, lineSize);

				// Split it up into parts...
				command->setConfigLine(line);

				// default...
				if (strcasecmp(command->part(0), ":default") == 0)
				{
					if (config->reportFormat == Config::Debug)
						printf("%sPolicy Default Line:%s %s\n", config->COL_GREEN, config->COL_RESET, line);

					if (command->part(1)[0] == '0')
						policyPointer->active = false;
					else
						policyPointer->active = true;
				}

				// Unknown CheckPoint Structure...
				else if ((command->part(0)[0] == ':') && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
				{
					processUnknownCheckPointConfig(command, line, lineSize);
				}

				// All others...
				else if (command->part(0)[0] != ')')
					lineNotProcessed(line);
			}

			if (config->reportFormat == Config::Debug)
				printf("%sPolicy End Line:%s %s\n", config->COL_GREEN, config->COL_RESET, line);

			command->setConfigLine((char *)"");
		}

		// Unknown CheckPoint Structure...
		else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
			processUnknownCheckPointConfig(command, line, lineSize);

		// All others...
		else if (command->part(0)[0] != ')')
			lineNotProcessed(line);
	}

	if (config->reportFormat == Config::Debug)
		printf("%sPolicy Collection End Line:%s %s\n", config->COL_GREEN, config->COL_RESET, line);

	command->setConfigLine((char *)"");

	return 0;
}


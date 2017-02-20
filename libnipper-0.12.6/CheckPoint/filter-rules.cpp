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
#include <cstdlib>

#include "../globaldefs.h"
#include "../device/common/configline.h"
#include "device.h"
#include "filter.h"


bool CheckPointFilter::processDeviceRuleConfig(Device *device, ConfigLine *command, char *line, int lineSize, filterListConfig *filterListPointer, filterConfig *existingFilterPointer)
{
	// Variables...
	filterObjectConfig *objectPointer = 0;
	filterConfig *filterPointer = 0;
	bool incrementFilterPointer = true;
	bool negate = false;

	// Fix filter pointer...
	if (existingFilterPointer == 0)
		filterPointer = addFilter(filterListPointer);
	else
		filterPointer = existingFilterPointer;

	if (device->config->reportFormat == Config::Debug)
		printf("%sRule Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

	while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
	{

		// Read a line from the config...
		device->readLine(line, lineSize);

		// Split it up into parts...
		command->setConfigLine(line);

		// Admin Info...
		if ((strcasecmp(command->part(0), ":AdminInfo") == 0) && (strcmp(command->part(1), "()") != 0) && (existingFilterPointer == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sAdmin Info Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
			{

				// Read a line from the config...
				device->readLine(line, lineSize);

				// Split it up into parts...
				command->setConfigLine(line);

				// ID...
				if ((strcasecmp(command->part(0), ":chkpf_uid") == 0) && (strcmp(command->part(1), "()") != 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sAdmin ID Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					filterPointer->internalId.assign(command->part(1));
				}

				// Unknown CheckPoint Structure...
				else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
					((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

				// All others...
				else if (command->part(0)[0] != ')')
					device->lineNotProcessed(line);

			}

			if (device->config->reportFormat == Config::Debug)
				printf("%sAdmin Info End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			command->setConfigLine((char *)"");
		}

		// Action...
		else if ((strcasecmp(command->part(0), ":action") == 0) && (strcmp(command->part(1), "()") != 0) && (existingFilterPointer == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sAction Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
			{

				// Read a line from the config...
				device->readLine(line, lineSize);

				// Split it up into parts...
				command->setConfigLine(line);

				// Drop...
				if ((strcasecmp(command->part(0), ":") == 0) && (strcasecmp(command->part(1), "(drop") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sDrop Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					filterPointer->action = denyAction;
					((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);
				}

				// allow...
				else if ((strcasecmp(command->part(0), ":") == 0) && (strcasecmp(command->part(1), "(accept") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sAccept Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					filterPointer->action = allowAction;
					((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);
				}

				// Unknown CheckPoint Structure...
				else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
					((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

				// All others...
				else if (command->part(0)[0] != ')')
					device->lineNotProcessed(line);

			}

			if (device->config->reportFormat == Config::Debug)
				printf("%sAction End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			command->setConfigLine((char *)"");
		}

		// Disabled...
		else if ((strcasecmp(command->part(0), ":disabled") == 0) && (strcmp(command->part(1), "()") != 0) && (existingFilterPointer == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sDisabled Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			if (strcasecmp(command->part(1), "true") == 0)
				filterPointer->enabled = false;
			else
				filterPointer->enabled = true;
		}

		// Header Text...
		else if ((strcasecmp(command->part(0), ":header_text") == 0) && (strcmp(command->part(1), "()") != 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sRemark Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			if (existingFilterPointer != 0)
			{
				incrementFilterPointer = false;
				filterPointer = insertFilter(filterListPointer, existingFilterPointer);
			}
			filterPointer->remarkFilter = true;
			filterPointer->comment.assign(command->part(1));
		}

		// Filter Comments Text...
		else if ((strcasecmp(command->part(0), ":comments") == 0) && (strcasecmp(command->part(1), "()") != 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sComments Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			filterPointer->comment.assign(command->part(1));
		}

		// Track (log)...
		else if ((strcasecmp(command->part(0), ":track") == 0) && (strcmp(command->part(1), "()") != 0) && (existingFilterPointer == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sTracking Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
			{

				// Read a line from the config...
				device->readLine(line, lineSize);

				// Split it up into parts...
				command->setConfigLine(line);

				// Log structure
				if ((strcasecmp(command->part(0), ":") == 0) && (strcasecmp(command->part(1), "log") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sLog Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					filterPointer->log = true;
				}

				// No Log structure
				else if ((strcasecmp(command->part(0), ":") == 0) && (strcasecmp(command->part(1), "none") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sLog Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					filterPointer->log = false;
				}

				// Reference object
				else if ((strcasecmp(command->part(0), ":") == 0) && (strcasecmp(command->part(1), "(ReferenceObject") != 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sTrack Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
					{

						// Read a line from the config...
						device->readLine(line, lineSize);

						// Split it up into parts...
						command->setConfigLine(line);

						if ((strcasecmp(command->part(0), ":Name") == 0) && (strcasecmp(command->part(1), "Log") == 0))
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sLog Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							filterPointer->log = true;
						}

						else if ((strcasecmp(command->part(0), ":Name") == 0) && (strcasecmp(command->part(1), "None") == 0))
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sLog Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							filterPointer->log = false;
						}

						// Unknown CheckPoint Structure...
						else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
							((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

						// All others...
						else if (command->part(0)[0] != ')')
							device->lineNotProcessed(line);

					}

					if (device->config->reportFormat == Config::Debug)
						printf("%sTrack End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					command->setConfigLine((char *)"");
				}

				// Unknown CheckPoint Structure...
				else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
					((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

				// All others...
				else if (command->part(0)[0] != ')')
					device->lineNotProcessed(line);

			}

			if (device->config->reportFormat == Config::Debug)
				printf("%sTracking End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			command->setConfigLine((char *)"");
		}

		// Destination...
		else if ((strcasecmp(command->part(0), ":dst") == 0) && (strcmp(command->part(1), "()") != 0) && (existingFilterPointer == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sDestination Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			negate = false;

			while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
			{

				// Read a line from the config...
				device->readLine(line, lineSize);

				// Split it up into parts...
				command->setConfigLine(line);

				// Negate...
				if ((strcasecmp(command->part(0), ":op") == 0) && (strcasecmp(command->part(1), "not in") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sNegate Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					negate = true;
				}

				// Member Line
				else if ((strcasecmp(command->part(0), ":") == 0) && (command->part(1)[0] != '('))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sDestination Member Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					objectPointer = addFilterObject(filterPointer, destination);
					objectPointer->type = groupObject;
					if (negate == false)
						objectPointer->serviceOper = serviceOperEqual;
					else
						objectPointer->serviceOper = serviceOperNotEqual;
					objectPointer->name.assign(command->part(1));
				}

				// Reference object
				else if ((strcasecmp(command->part(0), ":") == 0) && (strcasecmp(command->part(1), "(ReferenceObject") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sDestination Member Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
					{

						// Read a line from the config...
						device->readLine(line, lineSize);

						// Split it up into parts...
						command->setConfigLine(line);

						if ((strcasecmp(command->part(0), ":Name") == 0) && (strcasecmp(command->part(1), "()") != 0))
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sDestination Member Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							objectPointer = addFilterObject(filterPointer, destination);
							objectPointer->type = groupObject;
							if (negate == false)
								objectPointer->serviceOper = serviceOperEqual;
							else
								objectPointer->serviceOper = serviceOperNotEqual;
							objectPointer->name.assign(command->part(1));
						}

						// Unknown CheckPoint Structure...
						else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
							((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

						// All others...
						else if (command->part(0)[0] != ')')
							device->lineNotProcessed(line);

					}

					if (device->config->reportFormat == Config::Debug)
						printf("%sDestination Member End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					command->setConfigLine((char *)"");
				}

				// compound object
				else if ((strcasecmp(command->part(0), ":compound") == 0) && (strcasecmp(command->part(1), "()") != 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sDestination Compound Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
					{

						// Read a line from the config...
						device->readLine(line, lineSize);

						// Split it up into parts...
						command->setConfigLine(line);

						if ((strcasecmp(command->part(0), ":") == 0) && (strcasecmp(command->part(1), "()") != 0))
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sDestination Compound Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							objectPointer = addFilterObject(filterPointer, destination);
							objectPointer->type = compoundObject;
							objectPointer->serviceOper = serviceOperEqual;
							objectPointer->name.assign(command->part(1) + 1);

							while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
							{

								// Read a line from the config...
								device->readLine(line, lineSize);

								// Split it up into parts...
								command->setConfigLine(line);
							
								if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
									((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

								// All others...
								else if (command->part(0)[0] != ')')
									device->lineNotProcessed(line);

							}
							command->setConfigLine((char *)"");
						}

						// Unknown CheckPoint Structure...
						else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
							((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

						// All others...
						else if (command->part(0)[0] != ')')
							device->lineNotProcessed(line);

					}

					if (device->config->reportFormat == Config::Debug)
						printf("%sDestination Compound End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					command->setConfigLine((char *)"");
				}

				// Unknown CheckPoint Structure...
				else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
					((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

				// All others...
				else if (command->part(0)[0] != ')')
					device->lineNotProcessed(line);

			}

			if (device->config->reportFormat == Config::Debug)
				printf("%sDestination End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			command->setConfigLine((char *)"");
		}

		// Source...
		else if ((strcasecmp(command->part(0), ":src") == 0) && (strcmp(command->part(1), "()") != 0) && (existingFilterPointer == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sSource Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			negate = false;

			while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
			{

				// Read a line from the config...
				device->readLine(line, lineSize);

				// Split it up into parts...
				command->setConfigLine(line);

				// Negate...
				if ((strcasecmp(command->part(0), ":op") == 0) && (strcasecmp(command->part(1), "not in") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sNegate Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					negate = true;
				}

				// Member Line
				else if ((strcasecmp(command->part(0), ":") == 0) && (command->part(1)[0] != '('))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sSource Member Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					objectPointer = addFilterObject(filterPointer, source);
					objectPointer->type = groupObject;
					if (negate == false)
						objectPointer->serviceOper = serviceOperEqual;
					else
						objectPointer->serviceOper = serviceOperNotEqual;
					objectPointer->name.assign(command->part(1));
				}

				// Reference object
				else if ((strcasecmp(command->part(0), ":") == 0) && (strcasecmp(command->part(1), "(ReferenceObject") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sSource Member Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
					{

						// Read a line from the config...
						device->readLine(line, lineSize);

						// Split it up into parts...
						command->setConfigLine(line);

						if ((strcasecmp(command->part(0), ":Name") == 0) && (strcasecmp(command->part(1), "()") != 0))
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sSource Member Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							objectPointer = addFilterObject(filterPointer, source);
							objectPointer->type = groupObject;
							if (negate == false)
								objectPointer->serviceOper = serviceOperEqual;
							else
								objectPointer->serviceOper = serviceOperNotEqual;
							objectPointer->name.assign(command->part(1));
						}

						// Unknown CheckPoint Structure...
						else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
							((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

						// All others...
						else if (command->part(0)[0] != ')')
							device->lineNotProcessed(line);

					}

					if (device->config->reportFormat == Config::Debug)
						printf("%sSource Member End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					command->setConfigLine((char *)"");
				}

				// compound object
				else if ((strcasecmp(command->part(0), ":compound") == 0) && (strcasecmp(command->part(1), "()") != 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sSource Compound Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
					{

						// Read a line from the config...
						device->readLine(line, lineSize);

						// Split it up into parts...
						command->setConfigLine(line);

						if ((strcasecmp(command->part(0), ":") == 0) && (strcasecmp(command->part(1), "()") != 0))
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sSource Compound Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							objectPointer = addFilterObject(filterPointer, source);
							objectPointer->type = compoundObject;
							objectPointer->serviceOper = serviceOperEqual;
							objectPointer->name.assign(command->part(1) + 1);

							while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
							{

								// Read a line from the config...
								device->readLine(line, lineSize);

								// Split it up into parts...
								command->setConfigLine(line);
							
								if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
									((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

								// All others...
								else if (command->part(0)[0] != ')')
									device->lineNotProcessed(line);

							}
							command->setConfigLine((char *)"");
						}

						// Unknown CheckPoint Structure...
						else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
							((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

						// All others...
						else if (command->part(0)[0] != ')')
							device->lineNotProcessed(line);

					}

					if (device->config->reportFormat == Config::Debug)
						printf("%sSource Compound End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					command->setConfigLine((char *)"");
				}

				// Unknown CheckPoint Structure...
				else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
					((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

				// All others...
				else if (command->part(0)[0] != ')')
					device->lineNotProcessed(line);

			}

			if (device->config->reportFormat == Config::Debug)
				printf("%sSource End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			command->setConfigLine((char *)"");
		}

		// Install...
		else if ((strcasecmp(command->part(0), ":install") == 0) && (strcmp(command->part(1), "()") != 0) && (existingFilterPointer == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sInstall Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
			{

				// Read a line from the config...
				device->readLine(line, lineSize);

				// Split it up into parts...
				command->setConfigLine(line);

				// Member Line
				if ((strcasecmp(command->part(0), ":") == 0) && (command->part(1)[0] != '('))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sInstall Member Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					objectPointer = addFilterObject(filterPointer, installed);
					objectPointer->type = groupObject;
					objectPointer->serviceOper = serviceOperEqual;
					objectPointer->name.assign(command->part(1));
				}

				// Reference object
				else if ((strcasecmp(command->part(0), ":") == 0) && (strcasecmp(command->part(1), "(ReferenceObject") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sInstall Member Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
					{

						// Read a line from the config...
						device->readLine(line, lineSize);

						// Split it up into parts...
						command->setConfigLine(line);

						if ((strcasecmp(command->part(0), ":Name") == 0) && (strcasecmp(command->part(1), "()") != 0))
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sInstall Member Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							objectPointer = addFilterObject(filterPointer, installed);
							objectPointer->type = groupObject;
							objectPointer->serviceOper = serviceOperEqual;
							objectPointer->name.assign(command->part(1));
						}

						// Unknown CheckPoint Structure...
						else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
							((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

						// All others...
						else if (command->part(0)[0] != ')')
							device->lineNotProcessed(line);

					}

					if (device->config->reportFormat == Config::Debug)
						printf("%sInstall Member End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					command->setConfigLine((char *)"");
				}

				// Unknown CheckPoint Structure...
				else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
					((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

				// All others...
				else if (command->part(0)[0] != ')')
					device->lineNotProcessed(line);

			}

			if (device->config->reportFormat == Config::Debug)
				printf("%sInstall End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			command->setConfigLine((char *)"");
		}

		// through...
		else if ((strcasecmp(command->part(0), ":through") == 0) && (strcmp(command->part(1), "()") != 0) && (existingFilterPointer == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sThrough Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
			{

				// Read a line from the config...
				device->readLine(line, lineSize);

				// Split it up into parts...
				command->setConfigLine(line);

				// Member Line
				if ((strcasecmp(command->part(0), ":") == 0) && (command->part(1)[0] != '('))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sThrough Member Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					objectPointer = addFilterObject(filterPointer, through);
					objectPointer->type = groupObject;
					objectPointer->serviceOper = serviceOperEqual;
					objectPointer->name.assign(command->part(1));
				}

				// Reference object
				else if ((strcasecmp(command->part(0), ":") == 0) && (strcasecmp(command->part(1), "(ReferenceObject") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sThrough Member Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
					{

						// Read a line from the config...
						device->readLine(line, lineSize);

						// Split it up into parts...
						command->setConfigLine(line);

						if ((strcasecmp(command->part(0), ":Name") == 0) && (strcasecmp(command->part(1), "()") != 0))
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sThrough Member Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							objectPointer = addFilterObject(filterPointer, through);
							objectPointer->type = groupObject;
							objectPointer->serviceOper = serviceOperEqual;
							objectPointer->name.assign(command->part(1));
						}

						// Unknown CheckPoint Structure...
						else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
							((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

						// All others...
						else if (command->part(0)[0] != ')')
							device->lineNotProcessed(line);

					}

					if (device->config->reportFormat == Config::Debug)
						printf("%sThrough Member End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					command->setConfigLine((char *)"");
				}

				// Unknown CheckPoint Structure...
				else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
					((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

				// All others...
				else if (command->part(0)[0] != ')')
					device->lineNotProcessed(line);

			}

			if (device->config->reportFormat == Config::Debug)
				printf("%sThrough End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			command->setConfigLine((char *)"");
		}

		// Services...
		else if ((strcasecmp(command->part(0), ":services") == 0) && (strcmp(command->part(1), "()") != 0) && (existingFilterPointer == 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sService Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);
			negate = false;

			while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
			{

				// Read a line from the config...
				device->readLine(line, lineSize);

				// Split it up into parts...
				command->setConfigLine(line);

				// Negate...
				if ((strcasecmp(command->part(0), ":op") == 0) && (strcasecmp(command->part(1), "not in") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sNegate Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					negate = true;
				}

				// Member Line
				else if ((strcasecmp(command->part(0), ":") == 0) && (command->part(1)[0] != '('))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sServices Member Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					objectPointer = addFilterObject(filterPointer, destinationService);
					objectPointer->type = groupObject;
					if (negate == false)
						objectPointer->serviceOper = serviceOperEqual;
					else
						objectPointer->serviceOper = serviceOperNotEqual;
					objectPointer->name.assign(command->part(1));
				}

				// Reference object
				else if ((strcasecmp(command->part(0), ":") == 0) && (strcasecmp(command->part(1), "(ReferenceObject") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sServices Member Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
					{

						// Read a line from the config...
						device->readLine(line, lineSize);

						// Split it up into parts...
						command->setConfigLine(line);

						if ((strcasecmp(command->part(0), ":Name") == 0) && (strcasecmp(command->part(1), "()") != 0))
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sServices Member Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							objectPointer = addFilterObject(filterPointer, destinationService);
							objectPointer->type = groupObject;
							if (negate == false)
								objectPointer->serviceOper = serviceOperEqual;
							else
								objectPointer->serviceOper = serviceOperNotEqual;
							objectPointer->name.assign(command->part(1));
						}

						// Unknown CheckPoint Structure...
						else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
							((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

						// All others...
						else if (command->part(0)[0] != ')')
							device->lineNotProcessed(line);

					}

					if (device->config->reportFormat == Config::Debug)
						printf("%sServices Member End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					command->setConfigLine((char *)"");
				}

				// Unknown CheckPoint Structure...
				else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
					((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

				// All others...
				else if (command->part(0)[0] != ')')
					device->lineNotProcessed(line);

			}

			if (device->config->reportFormat == Config::Debug)
				printf("%sServices End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			command->setConfigLine((char *)"");
		}

		// Unknown CheckPoint Structure...
		else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
			((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

		// All others...
		else if (command->part(0)[0] != ')')
			device->lineNotProcessed(line);
	}

	if (device->config->reportFormat == Config::Debug)
		printf("%sRule End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

	command->setConfigLine((char *)"");

	return incrementFilterPointer;
}


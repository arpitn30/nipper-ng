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


int CheckPointFilter::processDeviceServicesConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	netObjectListConfig *serviceListPointer = 0;
	netObjectListConfig *serviceGroupListPointer = 0;
	filterObjectConfig *objectPointer = 0;
	filterObjectConfig *subObjectPointer = 0;
	objectType tempType = enhancedServiceObject;

	if (device->config->reportFormat == Config::Debug)
		printf("%sServices Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

	serviceListPointer = getObjectList("Services");
	serviceListPointer->type = enhancedServiceObject;
	serviceListPointer->title = i18n("Service List");
	serviceListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices services. These services can be directly used in the policy rules or grouped into service groups.");

	while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
	{

		// Read a line from the config...
		device->readLine(line, lineSize);

		// Split it up into parts...
		command->setConfigLine(line);

		// New service...
		if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sService Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			objectPointer = addObject(serviceListPointer);
			objectPointer->name.assign(command->part(1) + 1);
			objectPointer->type = enhancedServiceObject;
			objectPointer->serviceOper = serviceOperEqual;
			tempType = enhancedServiceObject;

			while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
			{

				// Read a line from the config...
				device->readLine(line, lineSize);

				// Split it up into parts...
				command->setConfigLine(line);

				// Protocol...
				if ((strcasecmp(command->part(0), ":protocol") == 0) && (strcasecmp(command->part(1), "()") != 0) && (strcasecmp(command->part(1), "-1") != 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sProtocol Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					subObjectPointer = addObject(objectPointer, protocol);
					subObjectPointer->name.assign(device->getProtocol(atoi(command->part(1))));
					subObjectPointer->type = protocolObject;
					subObjectPointer->serviceOper = serviceOperEqual;
				}

				// Port...
				else if ((strcasecmp(command->part(0), ":port") == 0) && (strcasecmp(command->part(1), "()") != 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sDestination Port Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					subObjectPointer = addObject(objectPointer, destinationService);
					subObjectPointer->name.assign(command->part(1));
					subObjectPointer->type = portObject;
					subObjectPointer->serviceOper = serviceOperEqual;
				}

				// Source Port...
				else if ((strcasecmp(command->part(0), ":src_port") == 0) && (strcasecmp(command->part(1), "()") != 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sSource Port Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					subObjectPointer = addObject(objectPointer, sourceService);
					subObjectPointer->name.assign(command->part(1));
					subObjectPointer->type = portObject;
					subObjectPointer->serviceOper = serviceOperEqual;
				}

				// ICMP...
				else if ((strncasecmp(command->part(0), ":icmp_", 6) == 0) && (objectPointer->protocol == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sProtocol ICMP Type Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					subObjectPointer = addObject(objectPointer, protocol);
					subObjectPointer->name.assign("ICMP");
					subObjectPointer->type = protocolObject;
					subObjectPointer->serviceOper = serviceOperEqual;
					objectPointer->type = otherObject;
				}

				// Type...
				else if ((strcasecmp(command->part(0), ":type") == 0) && (strcasecmp(command->part(1), "()") != 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sProtocol Type Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					if (strcasecmp(command->part(1), "group") == 0)
					{
						tempType = serviceObject;
					}
					else if (strcasecmp(command->part(1), "other") == 0)
						objectPointer->type = otherObject;
					else if (objectPointer->protocol == 0)
					{
						subObjectPointer = addObject(objectPointer, protocol);
						subObjectPointer->name.assign(command->part(1));
					}
				}

				// Comments...
				else if ((strcasecmp(command->part(0), ":comments") == 0) && (strcasecmp(command->part(1), "()") != 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sComments Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					objectPointer->comment.assign(command->part(1));
				}

				// Group Members...
				else if ((strcasecmp(command->part(0), ":") == 0) && (strcasecmp(command->part(1), "(ReferenceObject") != 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sObject Group Member Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					subObjectPointer = addObject(objectPointer, members);
					subObjectPointer->name.assign(command->part(1));
					subObjectPointer->type = groupObject;
					subObjectPointer->serviceOper = serviceOperEqual;
				}

				// Group Members...
				else if ((strcasecmp(command->part(0), ":") == 0) && (strcasecmp(command->part(1), "(ReferenceObject") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sObject Group Member Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					subObjectPointer = addObject(objectPointer, members);
					subObjectPointer->type = groupObject;
					subObjectPointer->serviceOper = serviceOperEqual;

					while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
					{

						// Read a line from the config...
						device->readLine(line, lineSize);

						// Split it up into parts...
						command->setConfigLine(line);

						// Name...
						if (strcasecmp(command->part(0), ":Name") == 0)
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sObject Member Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							subObjectPointer->name.assign(command->part(1));
						}

						// Unknown CheckPoint Structure...
						else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
							((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

						// All others...
						else if (command->part(0)[0] != ')')
							device->lineNotProcessed(line);

					}

					if (device->config->reportFormat == Config::Debug)
						printf("%sObject Group Member End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					command->setConfigLine((char *)"");
				}

				// Unknown CheckPoint Structure...
				else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
					((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

				// All others...
				else if (command->part(0)[0] != ')')
					device->lineNotProcessed(line);

			}

			if (tempType == serviceObject)
			{
				serviceGroupListPointer = getObjectList(objectPointer->name.c_str());
				serviceGroupListPointer->type = serviceObject;
				serviceGroupListPointer->comment.assign(objectPointer->comment);
				serviceGroupListPointer->title = i18n("Service Groups");
				serviceGroupListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices service groups. Service groups ease administration by enabling services to be grouped and then the group can be used within a policy rule, rather than listing each individual service for a specific rule.");
				objectPointer->deleteMe = true;

				// Go through any added members and transfer to objects of this group...
				subObjectPointer = objectPointer->members;
				while (subObjectPointer != 0)
				{
					objectPointer = addObject(serviceGroupListPointer);
					copySourceToDestinationObjects(subObjectPointer, objectPointer);
					subObjectPointer->deleteMe = true;
					subObjectPointer = subObjectPointer->next;
				}
			}

			// Add in any source and destination ports...
			if (objectPointer->type == enhancedServiceObject)
			{
				if (objectPointer->sourcePort == 0)
				{
					subObjectPointer = addObject(objectPointer, sourceService);
					subObjectPointer->name.assign(i18n("Any"));
				}
				if (objectPointer->destinationPort == 0)
				{
					subObjectPointer = addObject(objectPointer, destinationService);
					subObjectPointer->name.assign(i18n("Any"));
				}
			}

			if (device->config->reportFormat == Config::Debug)
				printf("%sObject Service End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

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

	return 0;
}



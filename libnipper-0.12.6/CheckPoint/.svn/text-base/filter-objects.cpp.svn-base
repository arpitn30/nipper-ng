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


int CheckPointFilter::processDeviceObjectConfig(Device *device, ConfigLine *command, char *line, int lineSize)
{
	// Variables...
	netObjectListConfig *objectListPointer = 0;
	netObjectListConfig *hostGroupListPointer = 0;
	filterObjectConfig *objectPointer = 0;
	filterObjectConfig *subObjectPointer = 0;
	objectType tempType = addressBookObject;
	int tempInt = 0;

	if (device->config->reportFormat == Config::Debug)
		printf("%sObject Configs Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

	objectListPointer = getObjectList("Network Objects");
	objectListPointer->type = addressBookObject;
	objectListPointer->title = i18n("Network Host Configuration");
	objectListPointer->description = i18n("This section details the hosts and networks configured for use in the policy rules.");

	while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
	{

		// Read a line from the config...
		device->readLine(line, lineSize);

		// Split it up into parts...
		command->setConfigLine(line);

		// New object...
		if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0))
		{
			if (device->config->reportFormat == Config::Debug)
				printf("%sObject Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

			objectPointer = addObject(objectListPointer);
			objectPointer->label.assign(command->part(1) + 1);
			tempType = addressBookObject;

			while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
			{
				// Read a line from the config...
				device->readLine(line, lineSize);

				// Split it up into parts...
				command->setConfigLine(line);

				// IP Address...
				if ((strcasecmp(command->part(0), ":ipaddr") == 0) || (strcasecmp(command->part(0), ":ipaddr_first") == 0) || (strcasecmp(command->part(0), ":bogus_ip") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sIP Address Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					objectPointer->name.assign(command->part(1));
				}

				// Net Mask...
				else if ((strcasecmp(command->part(0), ":netmask") == 0) || (strcasecmp(command->part(0), ":ipaddr_last") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sNetmask Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					objectPointer->netmask.assign(command->part(1));
				}

				// Location...
				else if ((strcasecmp(command->part(0), ":location") == 0) && (strcasecmp(command->part(1), "external") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sLocation Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					objectPointer->internal = false;
				}

				// Comments...
				else if ((strcasecmp(command->part(0), ":comments") == 0) && (strcasecmp(command->part(1), "()") != 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sComments Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					objectPointer->comment.assign(command->part(1));
				}

				// Firewall...
				else if ((strcasecmp(command->part(0), ":firewall") == 0) && (strcasecmp(command->part(1), "installed") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sFirewall Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					objectPointer->firewall = true;
				}

				// Type...
				else if (strcasecmp(command->part(0), ":type") == 0)
				{
					if (strcasecmp(command->part(1), "host") == 0)
					{
						if (device->config->reportFormat == Config::Debug)
							printf("%sHost Type Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

						tempType = hostObject;
					}

					else if (strcasecmp(command->part(1), "machines_range") == 0)
					{
						if (device->config->reportFormat == Config::Debug)
							printf("%sMachines Range Type Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

						tempType = machinesRangeObject;
					}

					else if (strcasecmp(command->part(1), "dynamic_net_obj") == 0)
					{
						if (device->config->reportFormat == Config::Debug)
							printf("%sDynamic Net Type Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

						tempType = dynamicnetObject;
					}

					else if (strcasecmp(command->part(1), "group") == 0)
					{
						if (device->config->reportFormat == Config::Debug)
							printf("%sGroup Type Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

						tempType = groupObject;
					}

					else if (strcasecmp(command->part(1), "network") == 0)
					{
						if (device->config->reportFormat == Config::Debug)
							printf("%sNetwork Type Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

						tempType = networkObject;
					}

					else if (strcasecmp(command->part(1), "gateway") == 0)
					{
						if (device->config->reportFormat == Config::Debug)
							printf("%sGateway Type Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

						tempType = gatewayObject;
					}

					else if (strcasecmp(command->part(1), "gateway_cluster") == 0)
					{
						if (device->config->reportFormat == Config::Debug)
							printf("%sGateway Cluster Type Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

						// Set the object type...
						tempType = gatewayClusterObject;
					}

					else if (strcasecmp(command->part(1), "cluster_member") == 0)
					{
						if (device->config->reportFormat == Config::Debug)
							printf("%sCluster Member Type Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

						tempType = clusterMemberObject;
					}
	
					// Create a delete me object...
					else
					{
						objectPointer->deleteMe = true;
						device->lineNotProcessed(line);
					}
				}

				// Management...
				else if ((strcasecmp(command->part(0), ":management") == 0) && (strcasecmp(command->part(1), "true") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sManagement Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					objectPointer->management = true;
				}

				// Interfaces...
				else if ((strcasecmp(command->part(0), ":interfaces") == 0) && (strcasecmp(command->part(1), "()") != 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sInterfaces Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					while ((feof(device->inputFile) == 0) && (strcmp(command->part(0), ")") != 0))
					{
						// Read a line from the config...
						device->readLine(line, lineSize);

						// Split it up into parts...
						command->setConfigLine(line);

						// New Interface...
						if ((command->part(0)[0] == ':') && (strcasecmp(command->part(1), "()") != 0))
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sInterface Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							subObjectPointer = addObject(objectPointer, interfaces);
							subObjectPointer->interfaceIndex = atoi(command->part(0) + 1);
							subObjectPointer->type = interfaceObject;
							subObjectPointer->serviceOper = serviceOperEqual;

							while ((feof(device->inputFile) == 0) && (strcmp(command->part(0), ")") != 0))
							{
								// Read a line from the config...
								device->readLine(line, lineSize);

								// Split it up into parts...
								command->setConfigLine(line);

								// IP Address...
								if (strcasecmp(command->part(0), ":ipaddr") == 0)
								{
									if (device->config->reportFormat == Config::Debug)
										printf("%sInterface Address Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

									subObjectPointer->name.assign(command->part(1));
								}

								// Net Mask...
								else if (strcasecmp(command->part(0), ":netmask") == 0)
								{
									if (device->config->reportFormat == Config::Debug)
										printf("%sInterface Netmask Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

									subObjectPointer->netmask.assign(command->part(1));
								}

								// Dynamic IP...
								else if ((strcasecmp(command->part(0), ":dynamic_ip") == 0) && (strcasecmp(command->part(1), "(true)") == 0))
								{
									if (device->config->reportFormat == Config::Debug)
										printf("%sInterface Dynamic Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

									subObjectPointer->dhcp = true;
								}
								else if ((strcasecmp(command->part(0), ":dynamic_ip") == 0) && (strcasecmp(command->part(1), "(false)") == 0))
								{
									if (device->config->reportFormat == Config::Debug)
										printf("%sInterface Dynamic Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

									subObjectPointer->dhcp = false;
								}

								else if (strcasecmp(command->part(0), ":officialname") == 0)
								{
									if (device->config->reportFormat == Config::Debug)
										printf("%sInterface Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

									subObjectPointer->label.assign(command->part(1));
								}

								// Unknown CheckPoint Structure...
								else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
									((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

								// All others...
								else if (command->part(0)[0] != ')')
									device->lineNotProcessed(line);

							}

							if (device->config->reportFormat == Config::Debug)
								printf("%sInterface End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

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
						printf("%sInterfaces End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					command->setConfigLine((char *)"");
				}

				// Cluster Members...
				else if ((strcasecmp(command->part(0), ":cluster_members") == 0) && (strcmp(command->part(1), "()") != 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sCluster Members Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
					{
						// Read a line from the config...
						device->readLine(line, lineSize);

						// Split it up into parts...
						command->setConfigLine(line);

						if ((command->part(0)[0] == ':') && (strcmp(command->part(1), "()") != 0))
						{
							if (device->config->reportFormat == Config::Debug)
								printf("%sCluster Member Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

							tempInt = atoi(command->part(0) + 1);
							while ((feof(device->inputFile) == 0) && (command->part(0)[0] != ')'))
							{
								// Read a line from the config...
								device->readLine(line, lineSize);

								// Split it up into parts...
								command->setConfigLine(line);

								if ((strcasecmp(command->part(0), ":Name") == 0) || (strcasecmp(command->part(0), ":refname") == 0))
								{
									if (device->config->reportFormat == Config::Debug)
										printf("%sCluster Member Name Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

									subObjectPointer = addObject(objectPointer, members);
									subObjectPointer->name.assign(command->part(1));
									subObjectPointer->type = groupObject;
									subObjectPointer->serviceOper = serviceOperEqual;
									subObjectPointer->interfaceIndex = tempInt;
								}

								// Unknown CheckPoint Structure...
								else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
									((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

								// All others...
								else if (command->part(0)[0] != ')')
									device->lineNotProcessed(line);
							}

							if (device->config->reportFormat == Config::Debug)
								printf("%sCluster Member End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

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
						printf("%sCluster Members End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					command->setConfigLine((char *)"");
				}

				// Members...
				else if ((strcasecmp(command->part(0), ":") == 0) && (strcasecmp(command->part(1), "(ReferenceObject") != 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sObject Member Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					subObjectPointer = addObject(objectPointer, members);
					subObjectPointer->name.assign(command->part(1));
					subObjectPointer->type = groupObject;
					subObjectPointer->serviceOper = serviceOperEqual;
				}

				// Members...
				else if ((strcasecmp(command->part(0), ":") == 0) && (strcasecmp(command->part(1), "(ReferenceObject") == 0))
				{
					if (device->config->reportFormat == Config::Debug)
						printf("%sObject Members Start Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

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
						printf("%sObject Member End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

					command->setConfigLine((char *)"");
				}

				// Unknown CheckPoint Structure...
				else if ((strncmp(command->part(0), ":", 1) == 0) && (strcmp(command->part(1), "()") != 0) && (command->part(1)[0] == '('))
					((CheckPointDevice *)device)->processUnknownCheckPointConfig(command, line, lineSize);

				// All others...
				else if (command->part(0)[0] != ')')
					device->lineNotProcessed(line);
			}

			if (objectPointer->deleteMe == false)
			{
				switch (tempType)
				{
					case hostObject:
						objectPointer->serviceOper = serviceOperEqual;
						objectPointer->type = hostObject;
						break;

					case machinesRangeObject:
						objectPointer->serviceOper = serviceOperRange;
						objectPointer->type = machinesRangeObject;
						break;

					case dynamicnetObject:
						objectPointer->serviceOper = serviceOperEqual;
						objectPointer->type = dynamicnetObject;
						break;

					case networkObject:
						objectPointer->type = networkObject;
						objectPointer->serviceOper = serviceOperEqual;
						break;

					case groupObject:
						hostGroupListPointer = getObjectList(objectPointer->label.c_str());
						hostGroupListPointer->type = hostObject;
						hostGroupListPointer->comment.assign(objectPointer->comment);
						hostGroupListPointer->title = i18n("Host Groups");
						hostGroupListPointer->description = i18n("This section describes the configuration of the *DEVICETYPE* devices host groups. Host groups ease administration by enabling hosts to be grouped and the group can then be used within a policy rule, rather than listing each individual host for a specific rule.");
						objectPointer->deleteMe = true;

						// Go through any added members and transfer to objects of this group...
						subObjectPointer = objectPointer->members;
						while (subObjectPointer != 0)
						{
							objectPointer = addObject(hostGroupListPointer);
							copySourceToDestinationObjects(subObjectPointer, objectPointer);
							objectPointer->type = groupObject;
							objectPointer->serviceOper = serviceOperEqual;
							subObjectPointer->deleteMe = true;
							subObjectPointer = subObjectPointer->next;
						}
						break;

					case gatewayObject:
						// Create new list for the gateway...
						hostGroupListPointer = getObjectList(objectPointer->label.c_str());
						hostGroupListPointer->type = gatewayObject;
						hostGroupListPointer->comment.assign(objectPointer->comment);
						hostGroupListPointer->title = i18n("Gateways");
						hostGroupListPointer->description = i18n("A *DEVICETYPE* device configuration can include multiple gateway devices. This section describes the gateway device configuration.");

						// Set the object type...
						objectPointer->type = gatewayObject;
						objectPointer->serviceOper = serviceOperEqual;

						// Copy the object to the new list...
						subObjectPointer = objectPointer;
						objectPointer = addObject(hostGroupListPointer);
						copySourceToDestinationObjects(subObjectPointer, objectPointer);

						// Delete the old object (removes duplicate)
						subObjectPointer->deleteMe = true;
						break;

					case gatewayClusterObject:
						// Create new list for the gateway cluster...
						hostGroupListPointer = getObjectList(objectPointer->label.c_str());
						hostGroupListPointer->type = gatewayClusterObject;
						hostGroupListPointer->comment.assign(objectPointer->comment);
						hostGroupListPointer->title = i18n("Gateway Clusters");
						hostGroupListPointer->description = i18n("On *DEVICETYPE* devices, a cluster of gateways can be configured to provide fault tollerance and load sharing of network traffic. This section describes the configuration of the gateway clusters.");

						// Set the object type...
						objectPointer->type = gatewayClusterObject;
						objectPointer->serviceOper = serviceOperEqual;

						// Copy the object to the new list...
						subObjectPointer = objectPointer;
						objectPointer = addObject(hostGroupListPointer);
						copySourceToDestinationObjects(subObjectPointer, objectPointer);

						// Delete the old object (removes duplicate)
						subObjectPointer->deleteMe = true;
						break;

					case clusterMemberObject:
						// Create new list for the cluster member...
						hostGroupListPointer = getObjectList(objectPointer->label.c_str());
						hostGroupListPointer->type = clusterMemberObject;
						hostGroupListPointer->comment.assign(objectPointer->comment);
						hostGroupListPointer->title = i18n("Cluster Members");
						hostGroupListPointer->description = i18n("On *DEVICETYPE* devices, a cluster of gateways can be configured to provide fault tollerance and load sharing of network traffic. This section describes the configuration of the gateway cluster members.");

						// Set the object type...
						objectPointer->type = clusterMemberObject;
						objectPointer->serviceOper = serviceOperEqual;

						// Copy the object to the new list...
						subObjectPointer = objectPointer;
						objectPointer = addObject(hostGroupListPointer);
						copySourceToDestinationObjects(subObjectPointer, objectPointer);

						// Delete the old object (removes duplicate)
						subObjectPointer->deleteMe = true;
						break;

					default:
						break;
				}
			}

			// If network object is really a host...
			if (objectPointer->type == networkObject)
			{
				if (objectPointer->netmask.compare("255.255.255.255") == 0)
					objectPointer->type = hostObject;
			}

			if (device->config->reportFormat == Config::Debug)
				printf("%sObject Members End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

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
		printf("%sObject Configs End Line:%s %s\n", device->config->COL_GREEN, device->config->COL_RESET, line);

	command->setConfigLine((char *)"");

	return 0;
}


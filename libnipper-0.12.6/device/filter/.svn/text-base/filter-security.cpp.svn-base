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

#include "../../globaldefs.h"
#include "../device.h"
#include "filter.h"


int Filter::generateSecurityReport(Device *device)
{
	// Variables...
	filterListConfig *filterListPointer = 0;
	filterConfig *filterPointer = 0;
	filterConfig *searchFilterPointer = 0;
	filterObjectConfig *objectPointer = 0;
	filterObjectConfig *searchObjectPointer = 0;
	bool foundDenyAllAndLog = false;
	bool protocolMatch = false;
	bool sourceMatch = false;
	bool sourcePortMatch = false;
	bool destinationMatch = false;
	bool destinationPortMatch = false;

	if (device->config->reportFormat == Config::Debug)
		printf("    %s*%s Network Filtering Checks\n", device->config->COL_BLUE, device->config->COL_RESET);

	// Identify security issues...
	filterListPointer = filterList;
	while (filterListPointer != 0)
	{
		foundDenyAllAndLog = false;

		// Check for legacy list...
		if (filterListPointer->legacyType == true)
			addFilterIssue("GEN.FILTLEGA.1", filterListPointer);

		// Check filters...
		filterPointer = filterListPointer->filter;
		while (filterPointer != 0)
		{
			if (filterPointer->remarkFilter == false)// && ((ignoreNonTCPUDPFilters == false) || (filterIncludesTCPUDP(filterPointer) == true)))
			{
				// Init...
				sourceDetection = hostObject;
				sourcePortDetection = hostObject;
				destinationDetection = hostObject;
				destinationPortDetection = hostObject;
				containsClearText = false;
				containsDangerous = false;
				containsUnnecessary = false;

				if (filterPointer->enabled == true)
				{

					// Check out source...
					if ((device->config->checkFilterForAnySource == true) || (device->config->checkFilterForNetworkSource == true))
					{
						if (filterListPointer->to.empty())
							hostSourceSecurityChecks(device, filterPointer->source, "");
						else
							hostSourceSecurityChecks(device, filterPointer->source, filterListPointer->name.c_str());
					}

					// Source Service...
					if ((filterListPointer->sourceServiceSupported == true) && ((device->config->checkFilterForAnySourcePort == true) || (device->config->checkFilterForRangeSourcePort == true)))
					{
						if (filterListPointer->to.empty())
							serviceSourceSecurityChecks(device, filterPointer->sourceService, "", "");
						else
							serviceSourceSecurityChecks(device, filterPointer->sourceService, filterListPointer->name.c_str(), filterListPointer->to.c_str());
					}

					// Destination...
					if (filterListPointer->sourceOnly == false)
					{
						if ((device->config->checkFilterForAnyDestination == true) || (device->config->checkFilterForNetworkDestination == true))
							hostDestinationSecurityChecks(device, filterPointer->destination, filterListPointer->to.c_str());

						// Destination Service...
						if ((device->config->checkFilterForClearTextRules == true) || (device->config->checkFilterForDangerousRules == true) || (device->config->checkFilterForUnnecessaryRules == true) || (device->config->checkFilterForAnySourcePort == true) || (device->config->checkFilterForRangeSourcePort == true) || (device->config->checkFilterForAnyDestinationPort == true) || (device->config->checkFilterForRangeDestinationPort == true))
						{
							if (filterListPointer->to.empty())
								serviceDestinationSecurityChecks(device, filterPointer->destinationService, "", "");
							else
								serviceDestinationSecurityChecks(device, filterPointer->destinationService, filterListPointer->name.c_str(), filterListPointer->to.c_str());
						}
					}
				}

				// Comments
				if ((device->config->checkFilterForRulesWithoutComments == true) && (filterListPointer->filterCommentsSupported == true) && (filterPointer->comment.empty()))
					addFilterIssue("GEN.FILTCOMM.1", filterPointer, filterListPointer);

				// Disabled Rules
				if ((device->config->checkFilterForDisabledRules == true) && (filterListPointer->disabledFilterSupport == true) && (filterPointer->enabled == false))
					addFilterIssue("GEN.FILTDISA.1", filterPointer, filterListPointer);
				else
				{

					// Unused rules at the end of ACL...
					if ((device->config->checkFilterForUnusedRulesAtListEnd == true) && (foundDenyAllAndLog == true))
						addFilterIssue("GEN.FILTUNUS.1", filterPointer, filterListPointer);

					// Check for overlapping/duplicate and contradictory rules...
					if ((filterPointer->remarkFilter == false) && ((device->config->checkFilterForDuplicateRules == true) || (device->config->checkFilterForContradictRules == true)))
					{
						searchFilterPointer = filterPointer->next;
						while (searchFilterPointer != 0)
						{
							if ((searchFilterPointer->remarkFilter == false) && (filterPointer->enabled == true))
							{
								protocolMatch = false;
								sourceMatch = false;
								sourcePortMatch = false;
								destinationMatch = false;
								destinationPortMatch = false;

								// Compare protocols...
								objectPointer = filterPointer->protocol;
								if ((objectPointer->type == anyObject) || (objectPointer->serviceOper == serviceOperAny))
									protocolMatch = true;
								else
								{
									while ((objectPointer != 0) && (protocolMatch == false))
									{
										searchObjectPointer = searchFilterPointer->protocol;
										while ((searchObjectPointer != 0) && (protocolMatch == false))
										{
											// Find match...
											if ((searchObjectPointer->type == anyObject) || (searchObjectPointer->serviceOper == serviceOperAny))
												protocolMatch = true;
											else if (strcasecmp(objectPointer->name.c_str(), searchObjectPointer->name.c_str()) == 0)
												protocolMatch = true;
											searchObjectPointer = searchObjectPointer->next;
										}
										objectPointer = objectPointer->next;
									}
								}

								// Check Source / Destination interface zones (if they exist)
								if (protocolMatch == true)
								{
									if ((filterPointer->sourceZone.compare(searchFilterPointer->sourceZone) !=0) || (filterPointer->destZone.compare(searchFilterPointer->destZone) !=0))
										protocolMatch = false;
								}

								// Source...
								if (protocolMatch == true)
								{
									if (filterListPointer->to.empty())
										sourceMatch = hostOverlap(device, filterPointer->source, true, searchFilterPointer->source, true);
									else
										sourceMatch = hostOverlap(device, filterPointer->source, true, searchFilterPointer->source, true, filterListPointer->name.c_str());

									// Source Port...
									if (sourceMatch == true)
									{
										if (filterListPointer->to.empty())
											sourcePortMatch = portOverlap(device, filterPointer->sourceService, true, searchFilterPointer->sourceService, true, "", "", true);
										else
											sourcePortMatch = portOverlap(device, filterPointer->sourceService, true, searchFilterPointer->sourceService, true, filterListPointer->name.c_str(), filterListPointer->to.c_str(), true);

										// Destination...
										if (sourcePortMatch == true)
										{
											if (filterListPointer->to.empty())
												destinationMatch = hostOverlap(device, filterPointer->destination, true, searchFilterPointer->destination, true);
											else
												destinationMatch = hostOverlap(device, filterPointer->destination, true, searchFilterPointer->destination, true, filterListPointer->to.c_str());

											// Destination Port...
											if (destinationMatch == true)
											{
												if (filterListPointer->to.empty())
													destinationPortMatch = portOverlap(device, filterPointer->destinationService, true, searchFilterPointer->destinationService, true, "", "", false);
												else
													destinationPortMatch = portOverlap(device, filterPointer->destinationService, true, searchFilterPointer->destinationService, true, filterListPointer->name.c_str(), filterListPointer->to.c_str(), false);

												// An issue has occured...
												if (destinationPortMatch == true)
												{
													// Contradict issue...
													if (filterPointer->action != searchFilterPointer->action)
													{
														if (!((searchFilterPointer->next == 0) && (searchFilterPointer->source->type == anyObject) && (searchFilterPointer->sourceService->type == anyObject) && (searchFilterPointer->destination->type == anyObject) && (searchFilterPointer->destinationService->type == anyObject)))
															addFilterIssue("GEN.FILTCONT.1", filterPointer, searchFilterPointer, filterListPointer);
													}

													// Duplicate / Overlap...
													else
														addFilterIssue("GEN.FILTDUPL.1", filterPointer, searchFilterPointer, filterListPointer);
												}
											}
										}
									}
								}
							}
							searchFilterPointer = searchFilterPointer->next;
						}
					}

					switch (filterPointer->action)
					{
						case bypassAction:
						case deftAction:
						case allowAction:			// Allow Action Checks...

							// Any Source, Service, Destination and destination service
							if ((sourceDetection == anyObject) && (sourcePortDetection == anyObject) && (destinationDetection == anyObject) && (destinationPortDetection == anyObject))
								addFilterIssue("GEN.FILTAAAA.1", filterPointer, filterListPointer);

							// weak Source, Service, Destination and destination service
							else if (((sourceDetection == networkObject) || (sourceDetection == anyObject)) && ((sourcePortDetection == anyObject) || (sourcePortDetection == networkObject)) && ((destinationDetection == anyObject) || (destinationDetection == networkObject)) && ((destinationPortDetection == anyObject) || (destinationPortDetection == networkObject)))
								addFilterIssue("GEN.FILTWAAA.1", filterPointer, filterListPointer);

							// Any source, destination, destination service
							else if ((sourceDetection == anyObject) && (destinationDetection == anyObject) && (destinationPortDetection == anyObject))
								addFilterIssue("GEN.FILTAAAN.1", filterPointer, filterListPointer);

							// weak source, destination, destination service
							else if (((sourceDetection == anyObject) || (sourceDetection == networkObject)) && ((destinationDetection == anyObject) || (destinationDetection == networkObject)) && ((destinationPortDetection == anyObject) || (destinationPortDetection == networkObject)))
								addFilterIssue("GEN.FILTWAAN.1", filterPointer, filterListPointer);

							// Any Source Service, Destination and destination service
							else if ((sourcePortDetection == anyObject) && (destinationDetection == anyObject) && (destinationPortDetection == anyObject))
								addFilterIssue("GEN.FILTSAAN.1", filterPointer, filterListPointer);

							// weak Source Service, Destination and destination service
							else if (((sourcePortDetection == anyObject) || (sourcePortDetection == networkObject)) && ((destinationDetection == anyObject) || (destinationDetection == networkObject)) && ((destinationPortDetection == anyObject) || (destinationPortDetection == networkObject)))
								addFilterIssue("GEN.FILTWSAN.1", filterPointer, filterListPointer);

							// Any source, destination
							else if ((sourceDetection == anyObject) && (destinationDetection == anyObject))
								addFilterIssue("GEN.FILTANAN.1", filterPointer, filterListPointer);

							// Any source, destination service
							else if ((sourceDetection == anyObject) && (destinationPortDetection == anyObject))
								addFilterIssue("GEN.FILTANAS.1", filterPointer, filterListPointer);

							// Any destination, destination service
							else if ((destinationDetection == anyObject) && (destinationPortDetection == anyObject))
								addFilterIssue("GEN.FILTANDS.1", filterPointer, filterListPointer);

							// Any Source Service, any Destination
							else if ((sourcePortDetection == anyObject) && (destinationDetection == anyObject))
								addFilterIssue("GEN.FILTSNAN.1", filterPointer, filterListPointer);

							// Any Source Service, Destination service
							else if ((sourcePortDetection == anyObject) && (destinationPortDetection == anyObject))
								addFilterIssue("GEN.FILTASDS.1", filterPointer, filterListPointer);

							// weak source, destination
							else if (((sourceDetection == anyObject) || (sourceDetection == networkObject)) && ((destinationDetection == anyObject) || (destinationDetection == networkObject)))
								addFilterIssue("GEN.FILTWNAN.1", filterPointer, filterListPointer);

							// weak source, destination service
							else if (((sourceDetection == anyObject) || (sourceDetection == networkObject)) && ((destinationPortDetection == anyObject) || (destinationPortDetection == networkObject)))
								addFilterIssue("GEN.FILTWNAS.1", filterPointer, filterListPointer);

							// weak destination, destination service
							else if (((destinationDetection == anyObject) || (destinationDetection == networkObject)) && ((destinationPortDetection == anyObject) || (destinationPortDetection == networkObject)))
								addFilterIssue("GEN.FILTWNDS.1", filterPointer, filterListPointer);

							// weak Source Service, Destination
							else if (((sourcePortDetection == anyObject) || (sourcePortDetection == networkObject)) && ((destinationDetection == anyObject) || (destinationDetection == networkObject)))
								addFilterIssue("GEN.FILTWSNN.1", filterPointer, filterListPointer);

							// weak Source Service, Destination service
							else if (((sourcePortDetection == anyObject) || (sourcePortDetection == networkObject)) && ((destinationPortDetection == anyObject) || (destinationPortDetection == networkObject)))
								addFilterIssue("GEN.FILTWSDS.1", filterPointer, filterListPointer);

							// Any source
							else if (sourceDetection == anyObject)
								addFilterIssue("GEN.FILTANSO.1", filterPointer, filterListPointer);

							// network source
							else if (sourceDetection == networkObject)
								addFilterIssue("GEN.FILTNESO.1", filterPointer, filterListPointer);

							// Any source service
							else if (sourcePortDetection == anyObject)
								addFilterIssue("GEN.FILTANSS.1", filterPointer, filterListPointer);

							// Range source service
							else if (sourcePortDetection == networkObject)
								addFilterIssue("GEN.FILTRASS.1", filterPointer, filterListPointer);

							// Any destination
							else if (destinationDetection == anyObject)
								addFilterIssue("GEN.FILTANDE.1", filterPointer, filterListPointer);

							// Network destination
							else if (destinationDetection == networkObject)
								addFilterIssue("GEN.FILTNEDE.1", filterPointer, filterListPointer);

							// Any destinationDetection service
							else if (destinationPortDetection == anyObject)
								addFilterIssue("GEN.FILTANSE.1", filterPointer, filterListPointer);

							// range destination service
							else if (destinationPortDetection == networkObject)
								addFilterIssue("GEN.FILTRDSS.1", filterPointer, filterListPointer);

							// Log Allowed 
							if ((device->config->checkFilterLogsAllowedRules == true) && (filterListPointer->loggingSupport == true) && (filterPointer->log == false) && (logOnlyDenySupported == false))
								addFilterIssue("GEN.FILTALLO.1", filterPointer, filterListPointer);

							// Bypass
							if ((filterPointer->action == bypassAction) && (device->config->checkFilterForBypassRules == true))
								addFilterIssue("GEN.FILTBYPA.1", filterPointer, filterListPointer);

							// Default
							if ((filterPointer->action == deftAction) && (device->config->checkFilterForDefaultRules == true))
								addFilterIssue("GEN.FILTDEFT.1", filterPointer, filterListPointer);

							// Clear Text Service
							if ((containsClearText == true) && (device->config->checkFilterForClearTextRules == true))
								addFilterIssue("GEN.FILTCLEA.1", filterPointer, filterListPointer);

							// Dangerous Service
							if ((containsDangerous == true) && (device->config->checkFilterForDangerousRules == true))
								addFilterIssue("GEN.FILTDANG.1", filterPointer, filterListPointer);

							// Unnecessary Service
							if ((containsUnnecessary == true) && (device->config->checkFilterForUnnecessaryRules == true))
								addFilterIssue("GEN.FILTUNNE.1", filterPointer, filterListPointer);

							break;

						case rejectAction:			// Reject Action Checks...
						case denyAction:			// Deny Action Checks...
							// Log Denied 
							if ((device->config->checkFilterForLogDeniedRules == true) && (filterListPointer->loggingSupport == true) && (filterPointer->log == false))
								addFilterIssue("GEN.FILTDELO.1", filterPointer, filterListPointer);
							break;

							// Reject Rules...
							if ((device->config->checkFilterForRejectRules == true) && (filterPointer->action == rejectAction))
								addFilterIssue("GEN.FILTREJE.1", filterPointer, filterListPointer);

							// Deny All And Log (MAKE SURE THIS IS THE LAST CHECK!!!!)...
							if (filterPointer->source == 0)
								sourceDetection = anyObject;
							else if ((sourceDetection != anyObject) && (filterPointer->source->type == anyObject))
								sourceDetection = anyObject;
							if (filterPointer->sourceService == 0)
								sourcePortDetection = anyObject;
							else if ((sourcePortDetection != anyObject) && ((filterPointer->sourceService->type == anyObject) || (filterPointer->sourceService->serviceOper == serviceOperAny)))
								sourcePortDetection = anyObject;
							if (filterPointer->destination == 0)
								destinationDetection = anyObject;
							else if ((destinationDetection != anyObject) && (filterPointer->destination->type == anyObject))
								destinationDetection = anyObject;
							if (filterPointer->destinationService == 0)
								destinationPortDetection = anyObject;
							else if ((destinationPortDetection != anyObject) && ((filterPointer->destinationService->type == anyObject) || (filterPointer->destinationService->serviceOper == serviceOperAny)))
								destinationPortDetection = anyObject;
							if ((sourceDetection == anyObject) && (sourcePortDetection == anyObject) && (destinationDetection == anyObject) && (destinationPortDetection == anyObject))
							{
								foundDenyAllAndLog = true;
								if ((device->config->checkFilterEndsWithDenyAllAndLog == true) && (foundDenyAllAndLog == false) && (filterPointer->log == true) && (filterListPointer->loggingSupport == true) && (denyAllAndLogDefault == false) && (filterPointer->next == 0))
									addFilterIssue("GEN.FILTDAAL.1", filterListPointer);
							}

							break;

						default:
							break;
					}
				}
			}

			// Next...
			filterPointer = filterPointer->next;
		}

		filterListPointer = filterListPointer->next;
	}

	// Generate the issues themselves...
	generateSecurityReportIssues(device);

	return 0;
}


void Filter::addFilterIssue(const char *issue, filterConfig *filter, filterListConfig *filterRuleList)
{
	// Variables...
	Filter::filterIssueConfig *filterIssuePointer = 0;
	bool first = false;

	// Create...
	if (strcmp(issue, "GEN.FILTAAAA.1") == 0)
	{
		if (anyAnyAnyAny == 0)
		{
			anyAnyAnyAny = new (filterIssueConfig);
			filterIssuePointer = anyAnyAnyAny;
			first = true;
		}
		else
			filterIssuePointer = anyAnyAnyAny;
	}
	else if (strcmp(issue, "GEN.FILTWAAA.1") == 0)
	{
		if (weakWeakWeakWeak == 0)
		{
			weakWeakWeakWeak = new (filterIssueConfig);
			filterIssuePointer = weakWeakWeakWeak;
			first = true;
		}
		else
			filterIssuePointer = weakWeakWeakWeak;
	}
	else if (strcmp(issue, "GEN.FILTAAAN.1") == 0)
	{
		if (anyAnyAny == 0)
		{
			anyAnyAny = new (filterIssueConfig);
			filterIssuePointer = anyAnyAny;
			first = true;
		}
		else
			filterIssuePointer = anyAnyAny;
	}
	else if (strcmp(issue, "GEN.FILTWAAN.1") == 0)
	{
		if (weakWeakWeak == 0)
		{
			weakWeakWeak = new (filterIssueConfig);
			filterIssuePointer = weakWeakWeak;
			first = true;
		}
		else
			filterIssuePointer = weakWeakWeak;
	}
	else if (strcmp(issue, "GEN.FILTSAAN.1") == 0)
	{
		if (anyServiceAnyAny == 0)
		{
			anyServiceAnyAny = new (filterIssueConfig);
			filterIssuePointer = anyServiceAnyAny;
			first = true;
		}
		else
			filterIssuePointer = anyServiceAnyAny;
	}
	else if (strcmp(issue, "GEN.FILTWSAN.1") == 0)
	{
		if (weakServiceAnyAny == 0)
		{
			weakServiceAnyAny = new (filterIssueConfig);
			filterIssuePointer = weakServiceAnyAny;
			first = true;
		}
		else
			filterIssuePointer = weakServiceAnyAny;
	}
	else if (strcmp(issue, "GEN.FILTANAN.1") == 0)
	{
		if (anyAny == 0)
		{
			anyAny = new (filterIssueConfig);
			filterIssuePointer = anyAny;
			first = true;
		}
		else
			filterIssuePointer = anyAny;
	}
	else if (strcmp(issue, "GEN.FILTANAS.1") == 0)
	{
		if (anyAnyDestService == 0)
		{
			anyAnyDestService = new (filterIssueConfig);
			filterIssuePointer = anyAnyDestService;
			first = true;
		}
		else
			filterIssuePointer = anyAnyDestService;
	}
	else if (strcmp(issue, "GEN.FILTANDS.1") == 0)
	{
		if (destHostAndService == 0)
		{
			destHostAndService = new (filterIssueConfig);
			filterIssuePointer = destHostAndService;
			first = true;
		}
		else
			filterIssuePointer = destHostAndService;
	}
	else if (strcmp(issue, "GEN.FILTSNAN.1") == 0)
	{
		if (anyServiceAny == 0)
		{
			anyServiceAny = new (filterIssueConfig);
			filterIssuePointer = anyServiceAny;
			first = true;
		}
		else
			filterIssuePointer = anyServiceAny;
	}
	else if (strcmp(issue, "GEN.FILTASDS.1") == 0)
	{
		if (anyServiceAnyService == 0)
		{
			anyServiceAnyService = new (filterIssueConfig);
			filterIssuePointer = anyServiceAnyService;
			first = true;
		}
		else
			filterIssuePointer = anyServiceAnyService;
	}
	else if (strcmp(issue, "GEN.FILTWNAN.1") == 0)
	{
		if (weakWeak == 0)
		{
			weakWeak = new (filterIssueConfig);
			filterIssuePointer = weakWeak;
			first = true;
		}
		else
			filterIssuePointer = weakWeak;
	}
	else if (strcmp(issue, "GEN.FILTWNAS.1") == 0)
	{
		if (weakDestService == 0)
		{
			weakDestService = new (filterIssueConfig);
			filterIssuePointer = weakDestService;
			first = true;
		}
		else
			filterIssuePointer = weakDestService;
	}
	else if (strcmp(issue, "GEN.FILTWNDS.1") == 0)
	{
		if (weakDestHostAndService == 0)
		{
			weakDestHostAndService = new (filterIssueConfig);
			filterIssuePointer = weakDestHostAndService;
			first = true;
		}
		else
			filterIssuePointer = weakDestHostAndService;
	}
	else if (strcmp(issue, "GEN.FILTWSNN.1") == 0)
	{
		if (weakServiceAny == 0)
		{
			weakServiceAny = new (filterIssueConfig);
			filterIssuePointer = weakServiceAny;
			first = true;
		}
		else
			filterIssuePointer = weakServiceAny;
	}
	else if (strcmp(issue, "GEN.FILTWSDS.1") == 0)
	{
		if (weakServiceAnyService == 0)
		{
			weakServiceAnyService = new (filterIssueConfig);
			filterIssuePointer = weakServiceAnyService;
			first = true;
		}
		else
			filterIssuePointer = weakServiceAnyService;
	}
	else if (strcmp(issue, "GEN.FILTANSO.1") == 0)
	{
		if (anySourceHost == 0)
		{
			anySourceHost = new (filterIssueConfig);
			filterIssuePointer = anySourceHost;
			first = true;
		}
		else
			filterIssuePointer = anySourceHost;
	}
	else if (strcmp(issue, "GEN.FILTNESO.1") == 0)
	{
		if (netSourceHost == 0)
		{
			netSourceHost = new (filterIssueConfig);
			filterIssuePointer = netSourceHost;
			first = true;
		}
		else
			filterIssuePointer = netSourceHost;
	}
	else if (strcmp(issue, "GEN.FILTANSS.1") == 0)
	{
		if (anySourceService == 0)
		{
			anySourceService = new (filterIssueConfig);
			filterIssuePointer = anySourceService;
			first = true;
		}
		else
			filterIssuePointer = anySourceService;
	}
	else if (strcmp(issue, "GEN.FILTRASS.1") == 0)
	{
		if (rangeSourceService == 0)
		{
			rangeSourceService = new (filterIssueConfig);
			filterIssuePointer = rangeSourceService;
			first = true;
		}
		else
			filterIssuePointer = rangeSourceService;
	}
	else if (strcmp(issue, "GEN.FILTANDE.1") == 0)
	{
		if (anyDestination == 0)
		{
			anyDestination = new (filterIssueConfig);
			filterIssuePointer = anyDestination;
			first = true;
		}
		else
			filterIssuePointer = anyDestination;
	}
	else if (strcmp(issue, "GEN.FILTNEDE.1") == 0)
	{
		if (netDestination == 0)
		{
			netDestination = new (filterIssueConfig);
			filterIssuePointer = netDestination;
			first = true;
		}
		else
			filterIssuePointer = netDestination;
	}
	else if (strcmp(issue, "GEN.FILTANSE.1") == 0)
	{
		if (anyDestService == 0)
		{
			anyDestService = new (filterIssueConfig);
			filterIssuePointer = anyDestService;
			first = true;
		}
		else
			filterIssuePointer = anyDestService;
	}
	else if (strcmp(issue, "GEN.FILTRDSS.1") == 0)
	{
		if (rangeDestService == 0)
		{
			rangeDestService = new (filterIssueConfig);
			filterIssuePointer = rangeDestService;
			first = true;
		}
		else
			filterIssuePointer = rangeDestService;
	}
	else if (strcmp(issue, "GEN.FILTALLO.1") == 0)
	{
		if (allowedLogging == 0)
		{
			allowedLogging = new (filterIssueConfig);
			filterIssuePointer = allowedLogging;
			first = true;
		}
		else
			filterIssuePointer = allowedLogging;
	}
	else if (strcmp(issue, "GEN.FILTDELO.1") == 0)
	{
		if (deniedLogging == 0)
		{
			deniedLogging = new (filterIssueConfig);
			filterIssuePointer = deniedLogging;
			first = true;
		}
		else
			filterIssuePointer = deniedLogging;
	}
	else if (strcmp(issue, "GEN.FILTREJE.1") == 0)
	{
		if (filterRejects == 0)
		{
			filterRejects = new (filterIssueConfig);
			filterIssuePointer = filterRejects;
			first = true;
		}
		else
			filterIssuePointer = filterRejects;
	}
	else if (strcmp(issue, "GEN.FILTBYPA.1") == 0)
	{
		if (filterBypasses == 0)
		{
			filterBypasses = new (filterIssueConfig);
			filterIssuePointer = filterBypasses;
			first = true;
		}
		else
			filterIssuePointer = filterBypasses;
	}
	else if (strcmp(issue, "GEN.FILTDEFT.1") == 0)
	{
		if (filterDefault == 0)
		{
			filterDefault = new (filterIssueConfig);
			filterIssuePointer = filterDefault;
			first = true;
		}
		else
			filterIssuePointer = filterDefault;
	}
	else if (strcmp(issue, "GEN.FILTCOMM.1") == 0)
	{
		if (filterNoComment == 0)
		{
			filterNoComment = new (filterIssueConfig);
			filterIssuePointer = filterNoComment;
			first = true;
		}
		else
			filterIssuePointer = filterNoComment;
	}
	else if (strcmp(issue, "GEN.FILTDISA.1") == 0)
	{
		if (filterDisabled == 0)
		{
			filterDisabled = new (filterIssueConfig);
			filterIssuePointer = filterDisabled;
			first = true;
		}
		else
			filterIssuePointer = filterDisabled;
	}
	else if (strcmp(issue, "GEN.FILTCLEA.1") == 0)
	{
		if (filterClearText == 0)
		{
			filterClearText = new (filterIssueConfig);
			filterIssuePointer = filterClearText;
			first = true;
		}
		else
			filterIssuePointer = filterClearText;
	}
	else if (strcmp(issue, "GEN.FILTDANG.1") == 0)
	{
		if (filterDangerous == 0)
		{
			filterDangerous = new (filterIssueConfig);
			filterIssuePointer = filterDangerous;
			first = true;
		}
		else
			filterIssuePointer = filterDangerous;
	}
	else if (strcmp(issue, "GEN.FILTUNNE.1") == 0)
	{
		if (filterUnnecessary == 0)
		{
			filterUnnecessary = new (filterIssueConfig);
			filterIssuePointer = filterUnnecessary;
			first = true;
		}
		else
			filterIssuePointer = filterUnnecessary;
	}
	else if (strcmp(issue, "GEN.FILTLGLE.1") == 0)
	{
		if (weakLoggingLevel == 0)
		{
			weakLoggingLevel = new (filterIssueConfig);
			filterIssuePointer = weakLoggingLevel;
			first = true;
		}
		else
			filterIssuePointer = weakLoggingLevel;
	}
	else if (strcmp(issue, "GEN.FILTUNUS.1") == 0)
	{
		if (filterUnused == 0)
		{
			filterUnused = new (filterIssueConfig);
			filterIssuePointer = filterUnused;
			first = true;
		}
		else
			filterIssuePointer = filterUnused;
	}

	// If it still needs to be created...
	if (first == false)
	{
		while (filterIssuePointer->next != 0)
			filterIssuePointer = filterIssuePointer->next;
		filterIssuePointer->next = new (filterIssueConfig);
		filterIssuePointer = filterIssuePointer->next;
	}

	// init...
	filterIssuePointer->filter = filter;
	filterIssuePointer->filterRuleList = filterRuleList;
	filterIssuePointer->next = 0;
}
void Filter::addFilterIssue(const char *issue, filterConfig *filter, filterConfig *duplicate, filterListConfig *filterRuleList)
{
	// Variables...
	filterIssueConfig *filterIssuePointer = 0;
	filterDuplConfig *filterDuplPointer = 0;
	bool init = false;

	// If first...
	if (strcmp("GEN.FILTDUPL.1", issue) == 0)
	{
		if (filterDuplicate == 0)
		{
			filterDuplicate = new (filterDuplConfig);
			filterDuplPointer = filterDuplicate;
			init = true;
		}
		else
		{
			filterDuplPointer = filterDuplicate;
			while ((filterDuplPointer->next != 0) && (filterDuplPointer->filter != filter))
				filterDuplPointer = filterDuplPointer->next;
			if (filterDuplPointer->filter != filter)
			{
				filterDuplPointer->next = new (filterDuplConfig);
				filterDuplPointer = filterDuplPointer->next;
				init = true;
			}
		}
	}
	else
	{
		if (filterContradict == 0)
		{
			filterContradict = new (filterDuplConfig);
			filterDuplPointer = filterContradict;
			init = true;
		}
		else
		{
			filterDuplPointer = filterContradict;
			while ((filterDuplPointer->next != 0) && (filterDuplPointer->filter != filter))
				filterDuplPointer = filterDuplPointer->next;
			if (filterDuplPointer->filter != filter)
			{
				filterDuplPointer->next = new (filterDuplConfig);
				filterDuplPointer = filterDuplPointer->next;
				init = true;
			}
		}
	}

	if (init == true)
	{
		filterDuplPointer->filter = filter;
		filterDuplPointer->filterRuleList = filterRuleList;
		filterDuplPointer->duplicates = 0;
		filterDuplPointer->next = 0;
		filterDuplPointer->duplicates = new (filterIssueConfig);
		filterDuplPointer->duplicates->next = 0;
		filterDuplPointer->duplicates->filter = new (filterConfig);
		filterDuplPointer->duplicates->filter->remarkFilter = true;
		filterDuplPointer->duplicates->filter->number = 0;
		filterDuplPointer->duplicates->filter->next = 0;
		if (strcmp("GEN.FILTDUPL.1", issue) == 0)
			filterDuplPointer->duplicates->filter->comment.assign(i18n("The following rules duplicate or overlap"));
		else
			filterDuplPointer->duplicates->filter->comment.assign(i18n("The following rules contradict"));
	}

	// Add duplicate filter to the list
	filterIssuePointer = filterDuplPointer->duplicates;
	while (filterIssuePointer->next != 0)
		filterIssuePointer = filterIssuePointer->next;
	filterIssuePointer->next = new (filterIssueConfig);
	filterIssuePointer = filterIssuePointer->next;

	// Init
	filterIssuePointer->filter = duplicate;
	filterIssuePointer->next = 0;
}
void Filter::addFilterIssue(const char *issue, filterListConfig *filterRuleList)
{
	// Variables...
	filterListIssueConfig *filterListIssuePointer = 0;
	bool first = false;

	// Create...
	if (strcmp(issue, "GEN.FILTLEGA.1") == 0)
	{
		if (legacyLists == 0)
		{
			legacyLists = new (filterListIssueConfig);
			filterListIssuePointer = legacyLists;
			first = true;
		}
		else
			filterListIssuePointer = legacyLists;
	}
	else if (strcmp(issue, "GEN.FILTDAAL.1") == 0)
	{
		if (denyAllAndLog == 0)
		{
			denyAllAndLog = new (filterListIssueConfig);
			filterListIssuePointer = denyAllAndLog;
			first = true;
		}
		else
			filterListIssuePointer = denyAllAndLog;
	}

	// If it still needs to be created...
	if (first == false)
	{
		while (filterListIssuePointer->next != 0)
			filterListIssuePointer = filterListIssuePointer->next;
		filterListIssuePointer->next = new (filterListIssueConfig);
		filterListIssuePointer = filterListIssuePointer->next;
	}

	// init...
	filterListIssuePointer->filterRuleList = filterRuleList;
	filterListIssuePointer->next = 0;
}


int Filter::serviceSourceSecurityChecks(Device *device, filterObjectConfig *filterObject, const char *fromZone, const char *toZone)
{
	// Variables...
	netObjectListConfig *objectListPointer = 0;
	filterObjectConfig *filterObjectPointer = 0;
	filterObjectConfig *tempObjectPointer = 0;

	filterObjectPointer = filterObject;
	while (filterObjectPointer != 0)
	{
		// If it is an object group...
		if (filterObjectPointer->type == groupObject)
		{
			objectListPointer = getOnlyObjectList(filterObjectPointer->name.c_str(), fromZone);
			if (objectListPointer != 0)
			{
				serviceSourceSecurityChecks(device, objectListPointer->object, fromZone, toZone);
			}
			else
			{
				tempObjectPointer = getServiceListObject(filterObjectPointer->name.c_str());
				if (tempObjectPointer != 0)
				{
					if (tempObjectPointer->sourcePort != 0)
						serviceSourceSecurityChecks(device, tempObjectPointer->sourcePort, fromZone, toZone);
					if (tempObjectPointer->destinationPort != 0)
						serviceDestinationSecurityChecks(device, tempObjectPointer->destinationPort, fromZone, toZone);	
				}
			}
		}

		// Any object...
		else if ((filterObjectPointer->type == anyObject) && (device->config->checkFilterForAnySourcePort == true))
		{
			sourcePortDetection = anyObject;
		}

		// Enhanced Service Object...
		else if (filterObjectPointer->type == enhancedServiceObject)
		{
			if (filterObjectPointer->sourcePort != 0)
				serviceSourceSecurityChecks(device, filterObjectPointer->sourcePort, fromZone, toZone);
			if (filterObjectPointer->destinationPort != 0)
				serviceDestinationSecurityChecks(device, filterObjectPointer->destinationPort, fromZone, toZone);
		}

		// Service Object
		else if ((filterObjectPointer->type == serviceObject) || (filterObjectPointer->type == portObject))
		{
			if ((filterObjectPointer->serviceOper == serviceOperAny) && (device->config->checkFilterForAnySourcePort == true))
			{
				sourcePortDetection = anyObject;
			}
			else if ((filterObjectPointer->serviceOper != serviceOperEqual) && (filterObjectPointer->serviceOper != serviceOperAny) && (device->config->checkFilterForRangeSourcePort == true))
			{
				if (sourcePortDetection != anyObject)
					sourcePortDetection = networkObject;
			}
		}

		filterObjectPointer = filterObjectPointer->next;
	}

	return 0;
}
int Filter::serviceDestinationSecurityChecks(Device *device, filterObjectConfig *filterObject, const char *fromZone, const char *toZone, bool enumerate)
{
	// Variables...
	netObjectListConfig *objectListPointer = 0;
	filterObjectConfig *filterObjectPointer = 0;
	filterObjectConfig *tempObjectPointer = 0;
	int portNumber = 0;
	string tempString;

	filterObjectPointer = filterObject;
	while (filterObjectPointer != 0)
	{
		// If it is an object group...
		if (filterObjectPointer->type == groupObject)
		{
			objectListPointer = getOnlyObjectList(filterObjectPointer->name.c_str(), toZone);
			if (objectListPointer != 0)
			{
				serviceDestinationSecurityChecks(device, objectListPointer->object, fromZone, toZone);
			}
			else
			{
				tempObjectPointer = getServiceListObject(filterObjectPointer->name.c_str());
				if (tempObjectPointer != 0)
				{
					if (tempObjectPointer->type == enhancedServiceObject)
					{
						if (tempObjectPointer->sourcePort != 0)
							serviceSourceSecurityChecks(device, tempObjectPointer->sourcePort, fromZone, toZone);
						if (tempObjectPointer->destinationPort != 0)
							serviceDestinationSecurityChecks(device, tempObjectPointer->destinationPort, fromZone, toZone);	
					}
					else
						serviceDestinationSecurityChecks(device, tempObjectPointer, fromZone, toZone, false);
				}
			}
		}

		// Any object...
		else if ((filterObjectPointer->type == anyObject) && (device->config->checkFilterForAnyDestinationPort == true))
		{
			destinationPortDetection = anyObject;

			// Clear Text Check
			if ((device->config->checkFilterForClearTextRules == true) && (device->config->clearTextService != 0) && (containsClearText == false))
				containsClearText = true;

			// Dangerous Checks
			if ((device->config->checkFilterForDangerousRules == true) && (device->config->dangerousService != 0) && (containsDangerous == false))
				containsDangerous = true;

			// Unnecessary checks
			if ((device->config->checkFilterForUnnecessaryRules == true) && (device->config->unnecessaryService != 0) && (containsUnnecessary == false))
				containsUnnecessary = true;
		}

		// Enhanced Service Object...
		else if (filterObjectPointer->type == enhancedServiceObject)
		{
			if (filterObjectPointer->sourcePort != 0)
				serviceSourceSecurityChecks(device, filterObjectPointer->sourcePort, fromZone, toZone);
			if (filterObjectPointer->destinationPort != 0)
				serviceDestinationSecurityChecks(device, filterObjectPointer->destinationPort, fromZone, toZone);
		}

		// Service Object
		else if ((filterObjectPointer->type == serviceObject) || (filterObjectPointer->type == portObject))
		{
			if ((filterObjectPointer->serviceOper == serviceOperAny) && (device->config->checkFilterForAnyDestinationPort == true))
				destinationPortDetection = anyObject;
			else if ((filterObjectPointer->serviceOper != serviceOperEqual) && (filterObjectPointer->serviceOper != serviceOperAny) && (device->config->checkFilterForRangeDestinationPort == true))
			{
				if (destinationPortDetection != anyObject)
					destinationPortDetection = networkObject;
			}

			// Service checks...
			if (filterObjectPointer->serviceOper == serviceOperAny)
			{
				// Clear Text Check
				if ((device->config->checkFilterForClearTextRules == true) && (device->config->clearTextService != 0) && (containsClearText == false))
					containsClearText = true;

				// Dangerous Checks
				if ((device->config->checkFilterForDangerousRules == true) && (device->config->dangerousService != 0) && (containsDangerous == false))
					containsDangerous = true;

				// Unnecessary checks
				if ((device->config->checkFilterForUnnecessaryRules == true) && (device->config->unnecessaryService != 0) && (containsUnnecessary == false))
					containsUnnecessary = true;
			}
			else if (filterObjectPointer->serviceOper == serviceOperRange)
			{
				// Clear Text Check
				if ((device->config->checkFilterForClearTextRules == true) && (device->config->clearTextService != 0) && (containsClearText == false))
				{
					if (isInServiceList(device, device->config->clearTextService, filterObjectPointer->name.c_str(), filterObjectPointer->netmask.c_str()) == true)
						containsClearText = true;
				}

				// Dangerous Checks
				if ((device->config->checkFilterForDangerousRules == true) && (device->config->dangerousService != 0) && (containsDangerous == false))
				{
					if (isInServiceList(device, device->config->dangerousService, filterObjectPointer->name.c_str(), filterObjectPointer->netmask.c_str()) == true)
						containsDangerous = true;
				}

				// Unnecessary checks
				if ((device->config->checkFilterForUnnecessaryRules == true) && (device->config->unnecessaryService != 0) && (containsUnnecessary == false))
				{
					if (isInServiceList(device, device->config->unnecessaryService, filterObjectPointer->name.c_str(), filterObjectPointer->netmask.c_str()) == true)
						containsUnnecessary = true;
				}
			}
			else if (filterObjectPointer->serviceOper == serviceOperLessThan)
			{
				// Clear Text Check
				if ((device->config->checkFilterForClearTextRules == true) && (device->config->clearTextService != 0) && (containsClearText == false))
				{
					if (isInServiceList(device, device->config->clearTextService, "0", filterObjectPointer->name.c_str()) == true)
						containsClearText = true;
				}

				// Dangerous Checks
				if ((device->config->checkFilterForDangerousRules == true) && (device->config->dangerousService != 0) && (containsDangerous == false))
				{
					if (isInServiceList(device, device->config->dangerousService, "0", filterObjectPointer->name.c_str()) == true)
						containsDangerous = true;
				}

				// Unnecessary checks
				if ((device->config->checkFilterForUnnecessaryRules == true) && (device->config->unnecessaryService != 0) && (containsUnnecessary == false))
				{
					if (isInServiceList(device, device->config->unnecessaryService, "0", filterObjectPointer->name.c_str()) == true)
						containsUnnecessary = true;
				}
			}
			else if (filterObjectPointer->serviceOper == serviceOperGreaterThan)
			{
				// Clear Text Check
				if ((device->config->checkFilterForClearTextRules == true) && (device->config->clearTextService != 0) && (containsClearText == false))
				{
					if (isInServiceList(device, device->config->clearTextService, filterObjectPointer->name.c_str(), "65535") == true)
						containsClearText = true;
				}

				// Dangerous Checks
				if ((device->config->checkFilterForDangerousRules == true) && (device->config->dangerousService != 0) && (containsDangerous == false))
				{
					if (isInServiceList(device, device->config->dangerousService, filterObjectPointer->name.c_str(), "65535") == true)
						containsDangerous = true;
				}

				// Unnecessary checks
				if ((device->config->checkFilterForUnnecessaryRules == true) && (device->config->unnecessaryService != 0) && (containsUnnecessary == false))
				{
					if (isInServiceList(device, device->config->unnecessaryService, filterObjectPointer->name.c_str(), "65535") == true)
						containsUnnecessary = true;
				}
			}
			else if (filterObjectPointer->serviceOper == serviceOperEqual)
			{
				// Clear Text Check
				if ((device->config->checkFilterForClearTextRules == true) && (device->config->clearTextService != 0) && (containsClearText == false))
				{
					if (isInServiceList(device, device->config->clearTextService, filterObjectPointer->name.c_str()) == true)
						containsClearText = true;
				}

				// Dangerous Checks
				if ((device->config->checkFilterForDangerousRules == true) && (device->config->dangerousService != 0) && (containsDangerous == false))
				{
					if (isInServiceList(device, device->config->dangerousService, filterObjectPointer->name.c_str()) == true)
						containsDangerous = true;
				}

				// Unnecessary checks
				if ((device->config->checkFilterForUnnecessaryRules == true) && (device->config->unnecessaryService != 0) && (containsUnnecessary == false))
				{
					if (isInServiceList(device, device->config->unnecessaryService, filterObjectPointer->name.c_str()) == true)
						containsUnnecessary = true;
				}
			}
			else if (filterObjectPointer->serviceOper == serviceOperNotEqual)
			{
				portNumber = atoi(filterObjectPointer->name.c_str());
				if ((portNumber == 0) && (strcmp(filterObjectPointer->name.c_str(), "0") != 0))
					portNumber = device->getPort(filterObjectPointer->name.c_str());

				if (portNumber != 0)
				{
					tempString.assign(device->intToString(portNumber - 1));

					// Clear Text Check
					if ((device->config->checkFilterForClearTextRules == true) && (device->config->clearTextService != 0) && (containsClearText == false))
					{
						if (isInServiceList(device, device->config->clearTextService, "0", tempString.c_str()) == true)
							containsClearText = true;
					}

					// Dangerous Checks
					if ((device->config->checkFilterForDangerousRules == true) && (device->config->dangerousService != 0) && (containsDangerous == false))
					{
						if (isInServiceList(device, device->config->dangerousService, "0", tempString.c_str()) == true)
							containsDangerous = true;
					}

					// Unnecessary checks
					if ((device->config->checkFilterForUnnecessaryRules == true) && (device->config->unnecessaryService != 0) && (containsUnnecessary == false))
					{
						if (isInServiceList(device, device->config->unnecessaryService, "0", tempString.c_str()) == true)
							containsUnnecessary = true;
					}

					tempString.assign(device->intToString(portNumber + 1));

					// Clear Text Check
					if ((device->config->checkFilterForClearTextRules == true) && (device->config->clearTextService != 0) && (containsClearText == false))
					{
						if (isInServiceList(device, device->config->clearTextService, tempString.c_str(), "65535") == true)
							containsClearText = true;
					}

					// Dangerous Checks
					if ((device->config->checkFilterForDangerousRules == true) && (device->config->dangerousService != 0) && (containsDangerous == false))
					{
						if (isInServiceList(device, device->config->dangerousService, tempString.c_str(), "65535") == true)
							containsDangerous = true;
					}

					// Unnecessary checks
					if ((device->config->checkFilterForUnnecessaryRules == true) && (device->config->unnecessaryService != 0) && (containsUnnecessary == false))
					{
						if (isInServiceList(device, device->config->unnecessaryService, tempString.c_str(), "65535") == true)
							containsUnnecessary = true;
					}
				}
			}
		}

		if (enumerate == true)
			filterObjectPointer = filterObjectPointer->next;
		else
			filterObjectPointer = 0;
	}

	return 0;
}


// Routines to check the source and destination HOST addresses (not services)...
int Filter::hostSourceSecurityChecks(Device *device, filterObjectConfig *filterObject, const char *zone)
{
	// Variables...
	netObjectListConfig *objectListPointer = 0;
	filterObjectConfig *filterObjectPointer = 0;
	filterObjectConfig *tempObjectPointer = 0;

	filterObjectPointer = filterObject;
	while ((filterObjectPointer != 0) && (sourceDetection != anyObject))
	{
		// If it is an object group...
		if (filterObjectPointer->type == groupObject)
		{
			objectListPointer = getOnlyObjectList(filterObjectPointer->name.c_str(), zone);
			if (objectListPointer != 0)
				hostSourceSecurityChecks(device, objectListPointer->object, zone);
			else
			{
				tempObjectPointer = getAddressListObject(filterObjectPointer->name.c_str(), zone);
				if (tempObjectPointer != 0)
				{
					if ((tempObjectPointer->type == anyObject) && (device->config->checkFilterForAnySource == true))
					{
						sourceDetection = anyObject;
						return 0;
					}
					else if ((tempObjectPointer->type == networkObject) && (device->config->checkFilterForNetworkSource == true))
					{
						sourceDetection = networkObject;
					}
				}
			}
		}

		// Any object...
		else if ((filterObjectPointer->type == anyObject) && (device->config->checkFilterForAnySource == true))
		{
			sourceDetection = anyObject;
			return 0;
		}

		// Network Object
		else if ((filterObjectPointer->type == networkObject) && (device->config->checkFilterForNetworkSource == true))
			sourceDetection = networkObject;

		filterObjectPointer = filterObjectPointer->next;
	}

	return 0;
}
int Filter::hostDestinationSecurityChecks(Device *device, filterObjectConfig *filterObject, const char *zone)
{
	// Variables...
	netObjectListConfig *objectListPointer = 0;
	filterObjectConfig *filterObjectPointer = 0;
	filterObjectConfig *tempObjectPointer = 0;

	filterObjectPointer = filterObject;
	while ((filterObjectPointer != 0) && (destinationDetection != anyObject))
	{
		// If it is an object group...
		if (filterObjectPointer->type == groupObject)
		{
			objectListPointer = getOnlyObjectList(filterObjectPointer->name.c_str(), zone);
			if (objectListPointer != 0)
			{
				hostDestinationSecurityChecks(device, objectListPointer->object, zone);
			}
			else
			{
				tempObjectPointer = getAddressListObject(filterObjectPointer->name.c_str(), zone);
				if (tempObjectPointer != 0)
				{
					if ((tempObjectPointer->type == anyObject) && (device->config->checkFilterForAnyDestination == true))
					{
						destinationDetection = anyObject;
						return 0;
					}
					else if ((tempObjectPointer->type == networkObject) && (device->config->checkFilterForNetworkDestination == true))
					{
						destinationDetection = networkObject;
					}
				}
			}
		}

		// Any object...
		else if ((filterObjectPointer->type == anyObject) && (device->config->checkFilterForAnyDestination == true))
		{
			destinationDetection = anyObject;
			return 0;
		}

		// Network Object
		else if ((filterObjectPointer->type == networkObject) && (device->config->checkFilterForNetworkDestination == true))
		{
			if (destinationDetection != anyObject)
				destinationDetection = networkObject;
		}

		filterObjectPointer = filterObjectPointer->next;
	}

	return 0;
}


bool Filter::isInServiceList(Device *device, Config::protocolServiceList *serviceList, const char *startPort, const char *endPort)
{
	// Variables...
	Config::protocolServiceList *protocolServicePointer = 0;
	int lowerPort = 0;
	int upperPort = 0;

	// If pointer is empty, return
	if (serviceList == 0)
		return false;

	// If protocols have not yet been converted, do them now.
	protocolServicePointer = serviceList;
	if (protocolServicePointer->port == 0)
	{
		while (protocolServicePointer != 0)
		{
			protocolServicePointer->port = atoi(protocolServicePointer->service);
			if ((protocolServicePointer->port == 0) && (strcmp(protocolServicePointer->service, "0") != 0))
				protocolServicePointer->port = device->getPort(protocolServicePointer->service);
			protocolServicePointer = protocolServicePointer->next;
		}
	}

	// Get port number for lower port
	lowerPort = atoi(startPort);
	if ((lowerPort == 0) && (strcmp(startPort, "0") != 0))
		lowerPort = device->getPort(startPort);

	// Get port number for higher port
	if (strcmp(endPort, "") != 0)
	{
		upperPort = atoi(endPort);
		if ((upperPort == 0) && (strcmp(endPort, "0") != 0))
			upperPort = device->getPort(endPort);
	}

	// If it is a single port
	if ((upperPort == 0) && (lowerPort != 0))
	{
		protocolServicePointer = serviceList;
		while (protocolServicePointer != 0)
		{
			if (protocolServicePointer->port != 0)
			{
				if (protocolServicePointer->port == lowerPort)
					return true;
			}
			protocolServicePointer = protocolServicePointer->next;
		}
	}

	// If its multiport
	if ((upperPort != 0) && (lowerPort != 0))
	{
		protocolServicePointer = serviceList;
		while (protocolServicePointer != 0)
		{
			if (protocolServicePointer->port != 0)
			{
				if ((protocolServicePointer->port >= lowerPort) && (protocolServicePointer->port <= upperPort))
					return true;
			}
			protocolServicePointer = protocolServicePointer->next;
		}
	}

	return false;
}


bool Filter::hostOverlap(Device *device, filterObjectConfig *firstHost, bool enumFirst, filterObjectConfig *secondHost, bool enumSecond, const char *zone)
{
	// Variables...
	netObjectListConfig *objectListPointer = 0;
	filterObjectConfig *tempObjectPointer = 0;
	filterObjectConfig *objectPointer = 0;
	filterObjectConfig *searchObjectPointer = 0;
	bool tempResult = false;

	// Return errors...
	if ((firstHost == 0) || (secondHost == 0))
		return false;

	// Loop through all first hosts...
	objectPointer = firstHost;
	while (objectPointer != 0)
	{

		// Any Object...
		if ((objectPointer->type  == anyObject) || (objectPointer->serviceOper == serviceOperAny))
			return true;

		// Object Group...
		if (objectPointer->type == groupObject)
		{

			// Object list-based...
			objectListPointer = getOnlyObjectList(objectPointer->name.c_str(), zone);
			if (objectListPointer != 0)
			{
				tempResult = hostOverlap(device, objectListPointer->object, true, secondHost, true, zone);
				if (tempResult == true)
					return true;
			}

			else
			{

				// Address book-based...
				tempObjectPointer = getAddressListObject(objectPointer->name.c_str(), zone);
				if (tempObjectPointer != 0)
				{

					// If source is an address book entry, set the enumerate value to false...
					tempResult = hostOverlap(device, tempObjectPointer, false, secondHost, true, zone);
					if (tempResult == true)
						return true;
				}
			}
		}

		// first is an object
		else
		{

			// Loop through second hosts...
			searchObjectPointer = secondHost;
			while (searchObjectPointer != 0)
			{

				// If anyObject...
				if ((searchObjectPointer->type  == anyObject) || (searchObjectPointer->serviceOper == serviceOperAny))
					return true;

				// Object Group...
				if (searchObjectPointer->type == groupObject)
				{

					// Object list-based...
					objectListPointer = getOnlyObjectList(searchObjectPointer->name.c_str(), zone);
					if (objectListPointer != 0)
					{
						tempResult = hostOverlap(device, objectPointer, false, objectListPointer->object, true, zone);
						if (tempResult == true)
							return true;
					}

					else
					{

						// Address book-based...
						tempObjectPointer = getAddressListObject(searchObjectPointer->name.c_str(), zone);
						if (tempObjectPointer != 0)
						{

							// If source is an address book entry, set the enumerate value to false...
							tempResult = hostOverlap(device, objectPointer, false, tempObjectPointer, false, zone);
							if (tempResult == true)
								return true;
						}
					}
				}

				// Check first and second...
				else
				{

					// If both are hosts...
					if ((objectPointer->type == hostObject) && (searchObjectPointer->type == hostObject))
					{
						if (strcasecmp(objectPointer->name.c_str(), searchObjectPointer->name.c_str()) == 0)
							return true;
					}

					// If first is a host and second is a network...
					else if ((objectPointer->type == hostObject) && (searchObjectPointer->type == networkObject))
					{
						tempResult = compareHostRanges(device, objectPointer->name.c_str(), "255.255.255.255", searchObjectPointer->name.c_str(), searchObjectPointer->netmask.c_str());
						if (tempResult == true)
							return true;
					}

					// If first is a network and second is a host...
					else if ((objectPointer->type == networkObject) && (searchObjectPointer->type == hostObject))
					{
						tempResult = compareHostRanges(device, objectPointer->name.c_str(), objectPointer->netmask.c_str(), searchObjectPointer->name.c_str(), "255.255.255.255");
						if (tempResult == true)
							return true;
					}

					// If both are networks...
					else
					{
						tempResult = compareHostRanges(device, objectPointer->name.c_str(), objectPointer->netmask.c_str(), searchObjectPointer->name.c_str(), searchObjectPointer->netmask.c_str());
						if (tempResult == true)
							return true;
					}
				}

				// Next second host?
				if (enumSecond == false)
					searchObjectPointer = 0;
				else
					searchObjectPointer = searchObjectPointer->next;
			}
		}

		// Next first host?
		if (enumFirst == false)
			objectPointer = 0;
		else
			objectPointer = objectPointer->next;
	}

	return false;
}


bool Filter::compareHostRanges(Device *device, const char *address1, const char *netmask1, const char *address2, const char *netmask2)
{
	// Variables...
	unsigned int ipAddress = 0;
	unsigned int netmask = 0;
	unsigned int firstAddress = 0;
	unsigned int secondAddress = 0;

	// Straight check...
	if (strcmp(address1, address2) == 0)
		return true;

	// First address...
	ipAddress = device->ipAddressToNum(address1);
	netmask = device->ipAddressToNum(netmask1);

	// Get first network address...
	if ((ipAddress == 0) || (netmask == 0))
		return false;
	firstAddress = ipAddress & netmask;

	// Second Address...
	ipAddress = device->ipAddressToNum(address2);
	if (ipAddress == 0)
		return false;

	// Test first...
	if ((ipAddress & netmask) == firstAddress)
		return true;

	// Second address...
	netmask = device->ipAddressToNum(netmask2);
	if (netmask == 0)
		return false;
	secondAddress = ipAddress & netmask;

	// First address
	ipAddress = device->ipAddressToNum(address1);

	// Second test...
	if ((ipAddress & netmask) == secondAddress)
		return true;

	return false;
}


bool Filter::portOverlap(Device *device, filterObjectConfig *firstPort, bool enumFirst, filterObjectConfig *secondPort, bool enumSecond, const char *from, const char *to, bool source)
{
	// Variables...
	netObjectListConfig *objectListPointer = 0;
	filterObjectConfig *tempObjectPointer = 0;
	filterObjectConfig *tempObjectPointer2 = 0;
	filterObjectConfig *objectPointer = 0;
	filterObjectConfig *searchObjectPointer = 0;
	int firstStart = 0;
	int firstEnd = 0;
	int secondStart = 0;
	int secondEnd = 0;
	bool tempResult = false;
	bool protocolMatch = false;

	// Return errors...
	if ((firstPort == 0) || (secondPort == 0))
		return false;

	// Loop through all first ports...
	objectPointer = firstPort;
	while (objectPointer != 0)
	{

		// Any Object...
		if ((objectPointer->type  == anyObject) || (objectPointer->serviceOper == serviceOperAny))
		{
			return true;
		}

		// Object Group...
		if (objectPointer->type == groupObject)
		{

			// Object list-based...
			if (source == true)
				objectListPointer = getOnlyObjectList(objectPointer->name.c_str(), from);
			else
				objectListPointer = getOnlyObjectList(objectPointer->name.c_str(), to);
			if (objectListPointer != 0)
			{
				tempResult = portOverlap(device, objectListPointer->object, true, secondPort, true, from, to, source);
				if (tempResult == true)
					return true;
			}

			else
			{

				// Service List-based...
				tempObjectPointer = getServiceListObject(objectPointer->name.c_str());
				if (tempObjectPointer != 0)
				{

					// If source is an service list entry, set the enumerate value to false...
					tempResult = portOverlap(device, tempObjectPointer, false, secondPort, true, from, to, source);
					if (tempResult == true)
						return true;
				}
			}
		}

		// first is an object
		else
		{

			// Loop through second hosts...
			searchObjectPointer = secondPort;
			while (searchObjectPointer != 0)
			{

				// If anyObject...
				if ((searchObjectPointer->type  == anyObject) || (searchObjectPointer->serviceOper == serviceOperAny))
					return true;

				// Object Group...
				if (searchObjectPointer->type == groupObject)
				{

					// Object list-based...
					if (source == true)
						objectListPointer = getOnlyObjectList(searchObjectPointer->name.c_str(), from);
					else
						objectListPointer = getOnlyObjectList(searchObjectPointer->name.c_str(), to);
					if (objectListPointer != 0)
					{
						tempResult = portOverlap(device, objectPointer, false, objectListPointer->object, true, from, to, source);
						if (tempResult == true)
							return true;
					}

					else
					{

						// Service List-based...
						tempObjectPointer = getServiceListObject(searchObjectPointer->name.c_str());
						if (tempObjectPointer != 0)
						{

							// If source is an address book entry, set the enumerate value to false...
							tempResult = portOverlap(device, objectPointer, false, tempObjectPointer, false, from, to, source);
							if (tempResult == true)
								return true;
						}
					}
				}

				// Enhanced Service List...
				else if (objectPointer->type == enhancedServiceObject)
				{
					if (searchObjectPointer->type == groupObject)
					{

						// Object list-based...
						if (source == true)
							objectListPointer = getOnlyObjectList(searchObjectPointer->name.c_str(), from);
						else
							objectListPointer = getOnlyObjectList(searchObjectPointer->name.c_str(), to);
						if (objectListPointer != 0)
						{
							tempResult = portOverlap(device, objectPointer, false, objectListPointer->object, true, from, to, source);
							if (tempResult == true)
								return true;
						}
					}

					// Both are now enhanced service objects...
					else
					{

						// Compare protocols...
						protocolMatch = false;
						tempObjectPointer = objectPointer->protocol;
						if ((tempObjectPointer->type == anyObject) || (tempObjectPointer->serviceOper == serviceOperAny))
							protocolMatch = true;
						else
						{
							while ((tempObjectPointer != 0) && (protocolMatch == false))
							{
								tempObjectPointer2 = searchObjectPointer->protocol;
								while ((tempObjectPointer2 != 0) && (protocolMatch == false))
								{
									// Find match...
									if ((tempObjectPointer2->type == anyObject) || (tempObjectPointer2->serviceOper == serviceOperAny))
										protocolMatch = true;
									else if (strcasecmp(tempObjectPointer->name.c_str(), tempObjectPointer2->name.c_str()) == 0)
										protocolMatch = true;
									tempObjectPointer2 = tempObjectPointer2->next;
								}
								tempObjectPointer = tempObjectPointer->next;
							}
						}
						if (protocolMatch == false)
							return false;


						// Check enhanced service objects sources
						tempResult = portOverlap(device, objectPointer->sourcePort, true, searchObjectPointer->sourcePort, true, from, to, source);
						if (tempResult == false)
							return false;

						// Check enhanced service objects destinations...
						tempResult = portOverlap(device, objectPointer->destinationPort, true, searchObjectPointer->destinationPort, true, from, to, source);
						if (tempResult == true)
							return true;
					}
				}

				// Check first and second...
				else
				{

					// If both are equal...
					if ((objectPointer->serviceOper == serviceOperEqual) && (searchObjectPointer->serviceOper == serviceOperEqual))
					{
						if (strcasecmp(objectPointer->name.c_str(), searchObjectPointer->name.c_str()) == 0)
							return true;
					}

					else
					{

						if (objectPointer->serviceOper == serviceOperEqual)
						{
							firstStart = atoi(objectPointer->name.c_str());
							if ((firstStart == 0) && (strcmp(objectPointer->name.c_str(), "0") != 0))
								firstStart = device->getPort(objectPointer->name.c_str());
							firstEnd = firstStart;
						}

						else if (objectPointer->serviceOper == serviceOperLessThan)
						{
							firstStart = 1;
							firstEnd = atoi(objectPointer->name.c_str());
							if ((firstEnd == 0) && (strcmp(objectPointer->name.c_str(), "0") != 0))
								firstEnd = device->getPort(objectPointer->name.c_str());
							firstEnd--;
						}

						else if (objectPointer->serviceOper == serviceOperGreaterThan)
						{
							firstEnd = 65535;
							firstStart = atoi(objectPointer->name.c_str());
							if ((firstStart == 0) && (strcmp(objectPointer->name.c_str(), "0") != 0))
								firstStart = device->getPort(objectPointer->name.c_str());
							firstStart++;
						}

						else if (objectPointer->serviceOper == serviceOperRange)
						{
							firstStart = atoi(objectPointer->name.c_str());
							if ((firstStart == 0) && (strcmp(objectPointer->name.c_str(), "0") != 0))
								firstStart = device->getPort(objectPointer->name.c_str());
							firstEnd = atoi(objectPointer->netmask.c_str());
							if ((firstEnd == 0) && (strcmp(objectPointer->netmask.c_str(), "0") != 0))
								firstEnd = device->getPort(objectPointer->netmask.c_str());
						}

						else if (objectPointer->serviceOper == serviceOperNotEqual)
						{
							firstStart = 1;
							firstEnd = atoi(objectPointer->name.c_str());
							if ((firstEnd == 0) && (strcmp(objectPointer->name.c_str(), "0") != 0))
								firstEnd = device->getPort(objectPointer->name.c_str());
							firstEnd--;
						}

						if (searchObjectPointer->serviceOper == serviceOperEqual)
						{
							secondStart = atoi(searchObjectPointer->name.c_str());
							if ((secondStart == 0) && (strcmp(searchObjectPointer->name.c_str(), "0") != 0))
								secondStart = device->getPort(searchObjectPointer->name.c_str());
							secondEnd = secondStart;
						}

						else if (searchObjectPointer->serviceOper == serviceOperLessThan)
						{
							secondStart = 1;
							secondEnd = atoi(searchObjectPointer->name.c_str());
							if ((secondEnd == 0) && (strcmp(searchObjectPointer->name.c_str(), "0") != 0))
								secondEnd = device->getPort(searchObjectPointer->name.c_str());
							secondEnd--;
						}

						else if (searchObjectPointer->serviceOper == serviceOperGreaterThan)
						{
							secondEnd = 65535;
							secondStart = atoi(searchObjectPointer->name.c_str());
							if ((secondStart == 0) && (strcmp(searchObjectPointer->name.c_str(), "0") != 0))
								secondStart = device->getPort(searchObjectPointer->name.c_str());
							secondStart++;
						}

						else if (searchObjectPointer->serviceOper == serviceOperRange)
						{
							secondStart = atoi(searchObjectPointer->name.c_str());
							if ((secondStart == 0) && (strcmp(searchObjectPointer->name.c_str(), "0") != 0))
								secondStart = device->getPort(searchObjectPointer->name.c_str());
							secondEnd = atoi(searchObjectPointer->netmask.c_str());
							if ((secondEnd == 0) && (strcmp(searchObjectPointer->netmask.c_str(), "0") != 0))
								secondEnd = device->getPort(searchObjectPointer->netmask.c_str());
						}

						else if (searchObjectPointer->serviceOper == serviceOperNotEqual)
						{
							secondStart = 1;
							secondEnd = atoi(searchObjectPointer->name.c_str());
							if ((secondEnd == 0) && (strcmp(searchObjectPointer->name.c_str(), "0") != 0))
								secondEnd = device->getPort(searchObjectPointer->name.c_str());
							secondEnd--;
						}

						if ((firstStart != 0) && (firstEnd != 0) && (secondStart != 0) && (secondEnd != 0))
						{
							tempResult = comparePortRanges(firstStart, firstEnd, secondStart, secondEnd);
							if (tempResult == true)
								return true;

							if (objectPointer->serviceOper == serviceOperNotEqual)
							{
								firstStart = atoi(objectPointer->name.c_str());
								if ((firstStart == 0) && (strcmp(objectPointer->name.c_str(), "0") != 0))
									firstStart = device->getPort(objectPointer->name.c_str());
								firstStart++;
								firstEnd = 65535;

								if ((firstStart != 0) && (firstEnd != 0))
								{
									tempResult = comparePortRanges(firstStart, firstEnd, secondStart, secondEnd);
									if (tempResult == true)
										return true;
								}
							}

							if (searchObjectPointer->serviceOper == serviceOperNotEqual)
							{
								secondStart = atoi(searchObjectPointer->name.c_str());
								if ((secondStart == 0) && (strcmp(searchObjectPointer->name.c_str(), "0") != 0))
									secondStart = device->getPort(searchObjectPointer->name.c_str());
								secondStart++;
								secondEnd = 65535;

								if ((secondStart != 0) && (secondEnd != 0))
								{
									tempResult = comparePortRanges(firstStart, firstEnd, secondStart, secondEnd);
									if (tempResult == true)
										return true;
								}

								if (objectPointer->serviceOper == serviceOperNotEqual)
								{
									firstStart = 1;
									firstEnd = atoi(objectPointer->name.c_str());
									if ((firstEnd == 0) && (strcmp(objectPointer->name.c_str(), "0") != 0))
										firstEnd = device->getPort(objectPointer->name.c_str());
									firstEnd--;

									if ((firstStart != 0) && (firstEnd != 0))
									{
										tempResult = comparePortRanges(firstStart, firstEnd, secondStart, secondEnd);
										if (tempResult == true)
											return true;
									}
								}
							}
						}
					}
				}

				// Next second host?
				if (enumSecond == false)
					searchObjectPointer = 0;
				else
					searchObjectPointer = searchObjectPointer->next;
			}
		}

		// Next first host?
		if (enumFirst == false)
			objectPointer = 0;
		else
			objectPointer = objectPointer->next;
	}

	return false;
}


bool Filter::comparePortRanges(int firstStart, int firstEnd, int secondStart, int secondEnd)
{
	if ((firstStart >= secondStart) && (firstStart <= secondEnd))
		return true;
	if ((firstEnd >= secondStart) && (firstEnd <= secondEnd))
		return true;
	if ((secondStart >= firstStart) && (secondStart <= firstEnd))
		return true;
	if ((secondEnd >= firstStart) && (secondEnd <= firstEnd))
		return true;

	return false;
}



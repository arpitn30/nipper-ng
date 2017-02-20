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


// Output the ACL debug information...
void reportRulesDebug(struct nipperConfig *nipper)
{
	// Variables...
	struct filterObjectConfig *filterObjectPointer = 0;
	struct filterConfig *filterPointer = 0;
	struct filterListConfig *filterListPointer = 0;
	int ruleNumber = 0;

	filterListPointer = nipper->filterList;
	while (filterListPointer != 0)
	{
		printf("Filter List: %s\n", filterListPointer->name);
		printf("  Deny All And Log: %d\n", filterListPointer->denyAllAndLog);
		ruleNumber = 1;
		filterPointer = filterListPointer->filter;
		while (filterPointer != 0)
		{
			printf("  Rule: %d\n", ruleNumber);
			printf("    Enabled: %d\n", filterPointer->enabled);
			printf("    Action: %d\n", filterPointer->action);
			printf("    Protocol: %s\n", filterPointer->protocol);
			printf("    Protocol Type: %d\n", filterPointer->protocolType);
			printf("    Source:\n");
			filterObjectPointer = filterPointer->source;
			while (filterObjectPointer != 0)
			{
				printf("      Object: %s\n", filterObjectPointer->name);
				printf("        Netmask: %s\n", filterObjectPointer->netMask);
				printf("        Service Oper: %d\n", filterObjectPointer->serviceOp);
				printf("        Type: %d\n", filterObjectPointer->type);
				filterObjectPointer = filterObjectPointer->next;
			}
			printf("    Source Service:\n");
			filterObjectPointer = filterPointer->sourceService;
			while (filterObjectPointer != 0)
			{
				printf("      Object: %s\n", filterObjectPointer->name);
				printf("        Netmask: %s\n", filterObjectPointer->netMask);
				printf("        Service Oper: %d\n", filterObjectPointer->serviceOp);
				printf("        Type: %d\n", filterObjectPointer->type);
				filterObjectPointer = filterObjectPointer->next;
			}
			printf("    Destination:\n");
			filterObjectPointer = filterPointer->destination;
			while (filterObjectPointer != 0)
			{
				printf("      Object: %s\n", filterObjectPointer->name);
				printf("        Netmask: %s\n", filterObjectPointer->netMask);
				printf("        Service Oper: %d\n", filterObjectPointer->serviceOp);
				printf("        Type: %d\n", filterObjectPointer->type);
				filterObjectPointer = filterObjectPointer->next;
			}
			printf("    Destination Service:\n");
			filterObjectPointer = filterPointer->destinationService;
			while (filterObjectPointer != 0)
			{
				printf("      Object: %s\n", filterObjectPointer->name);
				printf("        Netmask: %s\n", filterObjectPointer->netMask);
				printf("        Service Oper: %d\n", filterObjectPointer->serviceOp);
				printf("        Type: %d\n", filterObjectPointer->type);
				filterObjectPointer = filterObjectPointer->next;
			}
			printf("    Through Device:\n");
			filterObjectPointer = filterPointer->through;
			while (filterObjectPointer != 0)
			{
				printf("      Object: %s\n", filterObjectPointer->name);
				printf("        Netmask: %s\n", filterObjectPointer->netMask);
				printf("        Service Oper: %d\n", filterObjectPointer->serviceOp);
				printf("        Type: %d\n", filterObjectPointer->type);
				filterObjectPointer = filterObjectPointer->next;
			}
			printf("    Install On:\n");
			filterObjectPointer = filterPointer->install;
			while (filterObjectPointer != 0)
			{
				printf("      Object: %s\n", filterObjectPointer->name);
				printf("        Netmask: %s\n", filterObjectPointer->netMask);
				printf("        Service Oper: %d\n", filterObjectPointer->serviceOp);
				printf("        Type: %d\n", filterObjectPointer->type);
				filterObjectPointer = filterObjectPointer->next;
			}
			printf("    Log: %d\n", filterPointer->log);
			printf("    Remark: %s\n", filterPointer->remark);
			printf("    Admin UID: %s\n", filterPointer->uid);
			printf("    Any Source: %d\n", filterPointer->anySource);
			printf("    Network Source: %d\n", filterPointer->networkSource);
			printf("    Any Source Service: %d\n", filterPointer->anySourceService);
			printf("    Any Destination: %d\n", filterPointer->anyDestination);
			printf("    Network Destination: %d\n", filterPointer->networkDestination);
			printf("    Any Destination Service: %d\n", filterPointer->anyDestinationService);
			filterPointer = filterPointer->next;
			ruleNumber++;
		}
		filterListPointer = filterListPointer->next;
	}
}



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


// Output a remark into the filter table...
void reportFilterRemark(struct nipperConfig *nipper, struct filterListConfig *filterListPointer, struct filterConfig *filterPointer)
{
	switch (nipper->deviceType)
	{
		case type_pix_firewall:
		case type_asa_firewall:
		case type_fwsm_firewall:
			if (filterListPointer->type == access_old)
				table_row_span(nipper, &settings_accesspix_heading, filterPointer->remark);
			else if (filterListPointer->type == access_std)
				table_row_span(nipper, &settings_accessstdpix_heading, filterPointer->remark);
			else if (filterListPointer->type == access_ext)
				table_row_span(nipper, &settings_accessextpix_heading, filterPointer->remark);
			break;
		case type_ios_router:
		case type_ios_switch:
		case type_ios_catalyst:
			if (filterListPointer->type == access_std)
				table_row_span(nipper, &settings_accessstd_heading, filterPointer->remark);
			else if (filterListPointer->type == access_ext)
				table_row_span(nipper, &settings_accessext_heading, filterPointer->remark);
			break;
		case type_css_filter:
			table_row_span(nipper, &settings_acl_css_heading, filterPointer->remark);
			break;
		case type_fw1_firewall:
		case type_nokiaip:
			table_row_span(nipper, &settings_policycol_heading, filterPointer->remark);
			break;
		case type_sos_firewall:
			table_row_span(nipper, &settings_policies_heading, filterPointer->remark);
			break;
		case type_passport:
		case type_bayaccelar:
			if (strcmp(filterListPointer->name, "**UNASSIGNED**") == 0)
				table_row_span(nipper, &settings_filter_heading, filterPointer->remark);
			else if (atoi(filterListPointer->name) < 101)
				table_row_span(nipper, &settings_filterset_heading, filterPointer->remark);
			else if ((atoi(filterListPointer->name) > 299) && (atoi(filterListPointer->name) < 1001))
				table_row_span(nipper, &settings_filter_heading, filterPointer->remark);
			break;
		case type_sonicwall:
			table_row_span(nipper, &settings_accessrules_heading, filterPointer->remark);
			break;
	}
}


// Report the source/destination
void reportSourceDestination(struct nipperConfig *nipper, struct filterObjectConfig *filterObjectPointer)
{
	// Variables...
	char tempString[nipper->maxSize];

	if (nipper->doCSV == true)
		fprintf(nipper->csvFile, "\"");

	while (filterObjectPointer != 0)
	{
		outputFriendly(filterObjectPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
	
		switch (filterObjectPointer->type)
		{
			case object_type_machinesrange:
				fprintf(nipper->reportFile, "%s - %s", tempString, filterObjectPointer->netMask);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "%s - %s", tempString, filterObjectPointer->netMask);
				break;
			case object_type_network:
				fprintf(nipper->reportFile, "%s / %s", tempString, filterObjectPointer->netMask);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "%s / %s", tempString, filterObjectPointer->netMask);
				break;
			case object_type_interface:
				fprintf(nipper->reportFile, "%s", tempString);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "%s", tempString);
				break;
			case object_type_object:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "<a href=\"#object-%s\">", tempString);
				fprintf(nipper->reportFile, "%s", tempString);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "%s", tempString);
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "</a>");
				break;
			case object_type_protocol:
				addAbbreviation(filterObjectPointer->name, false);
				fprintf(nipper->reportFile, "%s", tempString);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "%s", tempString);
				break;
			case object_type_host:
				fprintf(nipper->reportFile, "%s", tempString);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "%s", tempString);
				break;
			case object_type_any:
				fprintf(nipper->reportFile, "Any");
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "Any");
				break;
		}

		if (filterObjectPointer->next != 0)
		{
			fprintf(nipper->reportFile, "%s", nipper->tablerow_itemsep);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "; ");
		}

		filterObjectPointer = filterObjectPointer->next;
	}

	if (nipper->doCSV == true)
		fprintf(nipper->csvFile, "\"");

}


// Report objects one after another...
void reportSourceDestinationLine(struct nipperConfig *nipper, struct filterObjectConfig *filterObjectPointer)
{
	// Variables...
	char tempString[nipper->maxSize];

	if (nipper->doCSV == true)
		fprintf(nipper->csvFile, "\"");

	while (filterObjectPointer != 0)
	{
		outputFriendly(filterObjectPointer->name, tempString, nipper->maxSize, nipper->outputFormat);

		switch (filterObjectPointer->type)
		{
			case object_type_network:
				fprintf(nipper->reportFile, "%s / %s", tempString, filterObjectPointer->netMask);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "%s - %s", tempString, filterObjectPointer->netMask);
				break;
			case object_type_interface:
				fprintf(nipper->reportFile, "%s", tempString);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "%s", tempString);
				break;
			case object_type_object:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "<a href=\"#object-%s\">", tempString);
				fprintf(nipper->reportFile, "%s", tempString);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "%s", tempString);
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "</a>");
				break;
			case object_type_protocol:
				addAbbreviation(filterObjectPointer->name, false);
				fprintf(nipper->reportFile, "%s", tempString);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "%s", tempString);
				break;
			case object_type_host:
				fprintf(nipper->reportFile, "%s", tempString);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "%s", tempString);
				break;
			case object_type_any:
				fprintf(nipper->reportFile, "any address");
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "any address");
				break;
		}

		if (filterObjectPointer->next != 0)
		{
			if (filterObjectPointer->next->next == 0)
				fprintf(nipper->reportFile, " and ");
			else
				fprintf(nipper->reportFile, ", ");
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "; ");
		}

		filterObjectPointer = filterObjectPointer->next;
	}

	if (nipper->doCSV == true)
		fprintf(nipper->csvFile, "\"");

}


// Report the service
void reportService(struct nipperConfig *nipper, struct filterObjectConfig *filterObjectPointer)
{

	if (nipper->doCSV == true)
		fprintf(nipper->csvFile, "\"");

	while (filterObjectPointer != 0)
	{
		addAbbreviation(filterObjectPointer->name, false);

		if (filterObjectPointer->serviceOp == service_oper_eq)
		{
			fprintf(nipper->reportFile, "%s", filterObjectPointer->name);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "%s", filterObjectPointer->name);
		}
		else if (filterObjectPointer->serviceOp == service_oper_neq)
		{
			fprintf(nipper->reportFile, "not %s", filterObjectPointer->name);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "not %s", filterObjectPointer->name);
		}
		else if (filterObjectPointer->serviceOp == service_oper_lt)
		{
			fprintf(nipper->reportFile, "less than %s", filterObjectPointer->name);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "less than %s", filterObjectPointer->name);
		}
		else if (filterObjectPointer->serviceOp == service_oper_gt)
		{
			fprintf(nipper->reportFile, "greater than %s", filterObjectPointer->name);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "greater than %s", filterObjectPointer->name);
		}
		else if (filterObjectPointer->serviceOp == service_oper_range)
		{
			fprintf(nipper->reportFile, "%s - %s", filterObjectPointer->name, filterObjectPointer->netMask);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "%s - %s", filterObjectPointer->name, filterObjectPointer->netMask);
			addAbbreviation(filterObjectPointer->netMask, false);
		}
		else if (filterObjectPointer->serviceOp == service_oper_ignore)
		{
			fprintf(nipper->reportFile, "Any");
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "Any");
		}
		else
		{
			fprintf(nipper->reportFile, "%s", filterObjectPointer->name);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "%s", filterObjectPointer->name);
		}
	
		if (filterObjectPointer->next != 0)
		{
			fprintf(nipper->reportFile, "%s", nipper->tablerow_itemsep);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "; ");
		}

		filterObjectPointer = filterObjectPointer->next;
	}

	if (nipper->doCSV == true)
		fprintf(nipper->csvFile, "\"");

}


// Output the filter to the filter table...
void reportFilter(struct nipperConfig *nipper, int ruleNumber, struct filterListConfig *filterListPointer, struct filterConfig *filterPointer)
{
	// Variables...
	struct filterObjectConfig *filterObjectPointer = 0;
	struct objectListConfig *objectListPointer = 0;
	struct objectConfig *objectPointer = 0;
	char tempString[nipper->maxSize];

	switch (nipper->deviceType)
	{
		case type_pix_firewall:
		case type_asa_firewall:
		case type_fwsm_firewall:
			// Rule No.
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "%s<a name=\"%s-rule-%d\">%d</a>%s", nipper->tablerow_start, filterListPointer->name, ruleNumber, ruleNumber, nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "%s%d%s", nipper->tablerow_start, ruleNumber, nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "\"%s\", \"%d\", ", filterListPointer->name, ruleNumber);
			// Action...
			switch (filterPointer->action)
			{
				case filter_action_drop:
					fprintf(nipper->reportFile, "Deny%s", nipper->tablerow_mid);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "\"Deny\", ");
					break;
				case filter_action_accept:
					fprintf(nipper->reportFile, "Permit%s", nipper->tablerow_mid);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "\"Permit\", ");
					break;
			}
			// Protocol
			if (filterListPointer->type != access_std)
			{
				fprintf(nipper->reportFile, "%s%s", filterPointer->protocol, nipper->tablerow_mid);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\"%s\", ", filterPointer->protocol);
				addAbbreviation(filterPointer->protocol, false);
			}
			// Source
			reportSourceDestination(nipper, filterPointer->source);
			// Std ACL end
			if (filterListPointer->type == access_std)
			{
				fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\n");
			}
			// Old/Extended ACL
			else
			{
				fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, ", ");
				// Source Service
				reportService(nipper, filterPointer->sourceService);
				fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, ", ");
				// Destination
				reportSourceDestination(nipper, filterPointer->destination);
				fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, ", ");
				// Destination Service
				reportService(nipper, filterPointer->destinationService);
				if (filterListPointer->type != access_ext)
				{
					fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "\n");
				}
				else
				{
					fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, ", ");
					// Log
					if (filterPointer->log == true)
					{
						fprintf(nipper->reportFile, "Yes");
						if (nipper->doCSV == true)
							fprintf(nipper->csvFile, "\"Yes\", ");
					}
					else
					{
						fprintf(nipper->reportFile, "No");
						if (nipper->doCSV == true)
							fprintf(nipper->csvFile, "\"No\", ");
					}
		
					// Active
					if (filterPointer->enabled == true)
					{
						fprintf(nipper->reportFile, "%sYes%s", nipper->tablerow_mid, nipper->tablerow_end);
						if (nipper->doCSV == true)
							fprintf(nipper->csvFile, "\"Yes\"\n");
					}
					else
					{
						fprintf(nipper->reportFile, "%sNo%s", nipper->tablerow_mid, nipper->tablerow_end);
						if (nipper->doCSV == true)
							fprintf(nipper->csvFile, "\"No\"\n");
					}
				}
			}
			break;

		// IOS-based devices...
		case type_ios_router:
		case type_ios_switch:
		case type_ios_catalyst:
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "%s<a name=\"%s-rule-%d\">%d</a>%s", nipper->tablerow_start, filterListPointer->name, ruleNumber, ruleNumber, nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "%s%d%s", nipper->tablerow_start, ruleNumber, nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "\"%s\", \"%d\", ", filterListPointer->name, ruleNumber);
			switch (filterPointer->action)
			{
				case filter_action_drop:
					fprintf(nipper->reportFile, "Deny%s", nipper->tablerow_mid);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "\"Deny\", ");
					break;
				case filter_action_accept:
					fprintf(nipper->reportFile, "Permit%s", nipper->tablerow_mid);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "\"Permit\", ");
					break;
			}
			if (filterListPointer->type == access_ext)
			{
				fprintf(nipper->reportFile, "%s%s", filterPointer->protocol, nipper->tablerow_mid);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\"%s\", ", filterPointer->protocol);
				addAbbreviation(filterPointer->protocol, false);
			}
			// Source
			reportSourceDestination(nipper, filterPointer->source);
			fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, ", ");
			// Extended ACL
			if (filterListPointer->type == access_ext)
			{
				// Source Service
				reportService(nipper, filterPointer->sourceService);
				fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, ", ");
				// Destination
				reportSourceDestination(nipper, filterPointer->destination);
				fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, ", ");
				// Destination Service
				reportService(nipper, filterPointer->destinationService);
				fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, ", ");
			}
			// Log
			if (filterPointer->log == true)
			{
				fprintf(nipper->reportFile, "Yes");
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\"Yes\"");
			}
			else
			{
				fprintf(nipper->reportFile, "No");
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\"No\"");
			}
			if (filterListPointer->type == access_std)
			{
				fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\n");
			}
			else
			{
				fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, ", \"");
				if (filterPointer->established == true)
				{
					fprintf(nipper->reportFile, "Established");
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "Established");
				}
				if ((filterPointer->established == true) && (filterPointer->fragments == true))
				{
					fprintf(nipper->reportFile, ", ");
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "; ");
				}
				if (filterPointer->fragments == true)
				{
					fprintf(nipper->reportFile, "Fragments");
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "Fragments");
				}
				fprintf(nipper->reportFile, " %s", nipper->tablerow_end);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\"\n");
			}
			break;

		// Firewall-1 Filter...
		case type_fw1_firewall:
		case type_nokiaip:
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "%s<a name=\"%s-rule-%d\">%d</a>%s", nipper->tablerow_start, filterListPointer->name, ruleNumber, ruleNumber, nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "%s%d%s", nipper->tablerow_start, ruleNumber, nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "\"%s\", \"%d\", ", filterListPointer->name, ruleNumber);
			if (filterPointer->enabled == true)
			{
				fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_mid);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\"Yes\", ");
			}
			else
			{
				fprintf(nipper->reportFile, "No%s", nipper->tablerow_mid);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\"No\", ");
			}
			switch (filterPointer->action)
			{
				case filter_action_drop:
					fprintf(nipper->reportFile, "Drop%s", nipper->tablerow_mid);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "\"Drop\", ");
					break;
				case filter_action_accept:
					fprintf(nipper->reportFile, "Accept%s", nipper->tablerow_mid);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "\"Accept\", ");
					break;
				case filter_action_reject:
					fprintf(nipper->reportFile, "Reject%s", nipper->tablerow_mid);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "\"Reject\", ");
					break;
			}
			// Source...
			reportSourceDestination(nipper, filterPointer->source);
			fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, ", ");
			// Destination...
			reportSourceDestination(nipper, filterPointer->destination);
			fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, ", ");
			// Destination Service...
			reportService(nipper, filterPointer->destinationService);
			fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, ", \"");
			filterObjectPointer = filterPointer->through;
			while (filterObjectPointer != 0)
			{
				outputFriendly(filterObjectPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s", tempString);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "%s", tempString);
				if (filterObjectPointer->next != 0)
				{
					fprintf(nipper->reportFile, "%s", nipper->tablerow_itemsep);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "; ");
				}
				filterObjectPointer = filterObjectPointer->next;
			}
			fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "\", \"");
			filterObjectPointer = filterPointer->install;
			while (filterObjectPointer != 0)
			{
				outputFriendly(filterObjectPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
				fprintf(nipper->reportFile, "%s", tempString);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "%s", tempString);
				if (filterObjectPointer->next != 0)
				{
					fprintf(nipper->reportFile, "%s", nipper->tablerow_itemsep);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "; ");
				}
				filterObjectPointer = filterObjectPointer->next;
			}
			fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "\", \"");
			if (filterPointer->log == true)
			{
				fprintf(nipper->reportFile, "Yes");
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "Yes\"");
			}
			else
			{
				fprintf(nipper->reportFile, "No");
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "No\", ");
			}
			if (nipper->showACLComments == true)
			{
				fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, filterPointer->remark, nipper->tablerow_end);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, ", \"%s\"\n", filterPointer->remark);
			}
			else
			{
				fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\n");
			}
			break;

		// ScreenOS Filter...
		case type_sos_firewall:
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "%s<a name=\"%s-rule-%d\">%d</a>%s", nipper->tablerow_start, filterListPointer->name, filterPointer->id, filterPointer->id, nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "%s%d%s", nipper->tablerow_start, filterPointer->id, nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "\"%s\", \"%s\", \"%d\", ", filterListPointer->fromZone, filterListPointer->toZone, filterPointer->id);
			if (filterPointer->enabled == true)
			{
				fprintf(nipper->reportFile, "No%s", nipper->tablerow_mid);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\"No\", ");
			}
			else
			{
				fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_mid);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\"Yes\", ");
			}
			switch (filterPointer->action)
			{
				case filter_action_accept:
					fprintf(nipper->reportFile, "Permit%s", nipper->tablerow_mid);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "\"Permit\", ");
					break;
				case filter_action_drop:
					fprintf(nipper->reportFile, "Deny%s", nipper->tablerow_mid);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "\"Deny\", ");
					break;
				case filter_action_reject:
					fprintf(nipper->reportFile, "Reject%s", nipper->tablerow_mid);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "\"Reject\", ");
					break;
			}
			reportSourceDestination(nipper, filterPointer->source);
			fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, ", ");
			reportSourceDestination(nipper, filterPointer->destination);
			fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, ", ");
			reportService(nipper, filterPointer->destinationService);
			fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, ", ");
			if (filterPointer->log == true)
			{
				fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\"Yes\"\n");
			}
			else
			{
				fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\"No\"\n");
			}
			filterPointer = filterPointer->next;
			break;

		// SonicOS...
		case type_sonicwall:
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "%s<a name=\"%s-rule-%d\">%d</a>%s", nipper->tablerow_start, filterListPointer->name, ruleNumber, ruleNumber, nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "%s%d%s", nipper->tablerow_start, ruleNumber, nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "\"%s\", \"%s\", \"%d\", ", filterListPointer->fromZone, filterListPointer->toZone, ruleNumber);
			if (filterPointer->enabled == true)
			{
				fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_mid);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\"Yes\", ");
			}
			else
			{
				fprintf(nipper->reportFile, "No%s", nipper->tablerow_mid);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\"No\", ");
			}
			switch (filterPointer->action)
			{
				case filter_action_accept:
					fprintf(nipper->reportFile, "Allow%s", nipper->tablerow_mid);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "\"Allow\", ");
					break;
				case filter_action_reject:
					fprintf(nipper->reportFile, "Deny%s", nipper->tablerow_mid);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "\"Deny\", ");
					break;
				case filter_action_drop:
					fprintf(nipper->reportFile, "Discard%s", nipper->tablerow_mid);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "\"Discard\", ");
					break;
			}
			reportSourceDestination(nipper, filterPointer->source);
			fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, ", ");
			reportSourceDestination(nipper, filterPointer->destination);
			fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
			if (filterListPointer->type == access_std)
			{
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, ", \"");
				objectListPointer = getObjectListPointer(nipper, "SERVICES");
				filterObjectPointer = filterPointer->destinationService;
				while (filterObjectPointer != 0)
				{
					objectPointer = getObjectPointer(objectListPointer, filterObjectPointer->name);
					outputFriendly(objectPointer->comment, tempString, nipper->maxSize, nipper->outputFormat);
					fprintf(nipper->reportFile, "%s", tempString);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "%s", tempString);
					if (filterObjectPointer->next != 0)
					{
						fprintf(nipper->reportFile, "%s", nipper->tablerow_itemsep);
						if (nipper->doCSV == true)
							fprintf(nipper->csvFile, "; ");
					}
					filterObjectPointer = filterObjectPointer->next;
				}
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\"");
			}
			else
				reportService(nipper, filterPointer->destinationService);
			fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, ", ");
			if (filterPointer->fragments == true)
			{
				fprintf(nipper->reportFile, "Yes");
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\"Yes\"");
			}
			else
			{
				fprintf(nipper->reportFile, "No");
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\"No\"");
			}
			if (filterListPointer->type == access_std)
			{
				fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\n");
			}
			else
			{
				if (filterPointer->log == true)
				{
					fprintf(nipper->reportFile, "%sYes%s", nipper->tablerow_mid, nipper->tablerow_end);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, ", \"Yes\"\n");
				}
				else
				{
					fprintf(nipper->reportFile, "%sNo%s", nipper->tablerow_mid, nipper->tablerow_end);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, ", \"No\"\n");
				}
			}
			break;

		// Cisco CSS device...
		case type_css_filter:
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "%s<a name=\"%s-rule-%d\">%d</a>%s", nipper->tablerow_start, filterListPointer->name, filterPointer->id, filterPointer->id, nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "%s%d%s", nipper->tablerow_start, filterPointer->id, nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "\"%s\", \"%d\", ", filterListPointer->name, filterPointer->id);
			switch (filterPointer->action)
			{
				case filter_action_accept:
					fprintf(nipper->reportFile, "Permit%s", nipper->tablerow_mid);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "\"Permit\", ");
					break;
				case filter_action_drop:
					fprintf(nipper->reportFile, "Deny%s", nipper->tablerow_mid);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "\"Deny\", ");
					break;
				case filter_action_bypass:
					fprintf(nipper->reportFile, "Bypass%s", nipper->tablerow_mid);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "\"Bypass\", ");
					break;
			}
			outputFriendly(filterPointer->protocol, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "\"%s\", ", tempString);
			reportSourceDestination(nipper, filterPointer->source);
			fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, ", ");
			reportService(nipper, filterPointer->sourceService);
			fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, ", ");
			reportSourceDestination(nipper, filterPointer->destination);
			fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, ", ");
			reportService(nipper, filterPointer->destinationService);
			fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, ", ");
			if (filterPointer->log == true)
			{
				fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\"Yes\"\n");
			}
			else
			{
				fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\"No\"\n");
			}
			break;

		// Nortel Passport Devices...
		case type_passport:
		case type_bayaccelar:
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "%s<a name=\"%s-rule-%d\">%d</a>%s", nipper->tablerow_start, filterListPointer->name, filterPointer->id, filterPointer->id, nipper->tablerow_mid);
			else
				fprintf(nipper->reportFile, "%s%d%s", nipper->tablerow_start, filterPointer->id, nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "\"%s\", \"%d\", ", filterListPointer->listName, filterPointer->id);
			outputFriendly(filterPointer->remark, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "\"%s\", ", tempString);
			if (((atoi(filterListPointer->name) > 299) && (atoi(filterListPointer->name) < 1001)) || (strcmp(filterListPointer->name, "**UNASSIGNED**") == 0))
			{
				switch (filterPointer->filterType)
				{
					case filter_type_source:
						fprintf(nipper->reportFile, "Source%s", nipper->tablerow_mid);
						if (nipper->doCSV == true)
							fprintf(nipper->csvFile, "\"Source\", ");
						break;
					case filter_type_destination:
						fprintf(nipper->reportFile, "Dest%s", nipper->tablerow_mid);
						if (nipper->doCSV == true)
							fprintf(nipper->csvFile, "\"Dest\", ");
						break;
					case filter_type_global:
						fprintf(nipper->reportFile, "Global%s", nipper->tablerow_mid);
						if (nipper->doCSV == true)
							fprintf(nipper->csvFile, "\"Global\", ");
						break;
				}
			}
			switch (filterPointer->action)
			{
				case filter_action_accept:
					fprintf(nipper->reportFile, "Forward%s", nipper->tablerow_mid);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "\"Forward\", ");
					break;
				case filter_action_drop:
					fprintf(nipper->reportFile, "Drop%s", nipper->tablerow_mid);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "\"Drop\", ");
					break;
				case filter_action_default:
					fprintf(nipper->reportFile, "Default%s", nipper->tablerow_mid);
					if (nipper->doCSV == true)
						fprintf(nipper->csvFile, "\"Default\", ");
					break;
			}
			outputFriendly(filterPointer->protocol, tempString, nipper->maxSize, nipper->outputFormat);
			addAbbreviation(filterPointer->protocol, false);
			fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, "\"%s\", ", tempString);
			reportSourceDestination(nipper, filterPointer->source);
			fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, ", ");
			reportService(nipper, filterPointer->sourceService);
			fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, ", ");
			reportSourceDestination(nipper, filterPointer->destination);
			fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, ", ");
			reportService(nipper, filterPointer->destinationService);
			fprintf(nipper->reportFile, "%s", nipper->tablerow_mid);
			if (nipper->doCSV == true)
				fprintf(nipper->csvFile, ", ");
			if (filterPointer->stop == true)
			{
				fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_end);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\"Yes\"\n");
			}
			else
			{
				fprintf(nipper->reportFile, "No%s", nipper->tablerow_end);
				if (nipper->doCSV == true)
					fprintf(nipper->csvFile, "\"No\"\n");
			}
			break;
	}
}


void outputCSVHeadings(struct nipperConfig *nipper, const char *title1, const char *title2, struct tableHeading *headings)
{
	// Variables...
	struct tableHeading *headingPointer = 0;

	// first heading...
	fprintf(nipper->csvFile, "\"%s\", ", title1);

	// second heading...
	if (title2 != 0)
		fprintf(nipper->csvFile, "\"%s\", ", title2);

	// remaining headings...
	headingPointer = headings;
	while (headingPointer != 0)
	{
		fprintf(nipper->csvFile, "\"%s\"", headingPointer->heading);
		if (headingPointer->next != 0)
			fprintf(nipper->csvFile, ", ");
		else
			fprintf(nipper->csvFile, "\n");
		headingPointer = headingPointer->next;
	}
}


// Output the filter list table for the configuration section of the report
void reportRules(struct nipperConfig *nipper)
{
	// Variables...
	struct filterConfig *filterPointer = 0;
	struct filterListConfig *filterListPointer = 0;
	char tempString[nipper->maxSize];
	char tempString2[nipper->maxSize];
	int ruleNumber = 0;

	if (nipper->csvFilename != 0)
		nipper->doCSV = true;

	filterListPointer = nipper->filterList;
	while (filterListPointer != 0)
	{
		// Init rule number...
		ruleNumber = 1;

		// Output Table Start...
		switch (nipper->deviceType)
		{
			case type_pix_firewall:
			case type_asa_firewall:
			case type_fwsm_firewall:
				if (filterListPointer->type == access_old)
				{
					sprintf(tempString, "%s %s", settings_accesslists_table, filterListPointer->name);
					outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
					output_table(nipper, true, tempString2, &settings_accesspix_heading);
					if (nipper->doCSV == true)
						outputCSVHeadings(nipper, "ACL", 0, &settings_accesspix_heading);
				}
				else if (filterListPointer->type == access_std)
				{
					sprintf(tempString, "%s %s", settings_accessstd_table, filterListPointer->name);
					outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
					output_table(nipper, true, tempString2, &settings_accessstdpix_heading);
					if (nipper->doCSV == true)
						outputCSVHeadings(nipper, "ACL", 0, &settings_accessstdpix_heading);
				}
				else if (filterListPointer->type == access_ext)
				{
					sprintf(tempString, "%s %s", settings_accessext_table, filterListPointer->name);
					outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
					output_table(nipper, true, tempString2, &settings_accessextpix_heading);
					if (nipper->doCSV == true)
						outputCSVHeadings(nipper, "ACL", 0, &settings_accessextpix_heading);
				}
				break;
			case type_ios_router:
			case type_ios_switch:
			case type_ios_catalyst:
				if (filterListPointer->type == access_std)
				{
					sprintf(tempString, "%s %s", settings_accessstd_table, filterListPointer->name);
					outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
					output_table(nipper, true, tempString2, &settings_accessstd_heading);
					if (nipper->doCSV == true)
						outputCSVHeadings(nipper, "ACL", 0, &settings_accessstd_heading);
				}
				else if (filterListPointer->type == access_ext)
				{
					sprintf(tempString, "%s %s", settings_accessext_table, filterListPointer->name);
					outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
					output_table(nipper, true, tempString2, &settings_accessext_heading);
					if (nipper->doCSV == true)
						outputCSVHeadings(nipper, "ACL", 0, &settings_accessext_heading);
				}
				break;
			case type_sos_firewall:
				if (filterListPointer->global == true)
					sprintf(tempString, "Global zone policy list");
				else if (filterListPointer->name[0] == 0)
					sprintf(tempString, "Zone %s to zone %s policy list", filterListPointer->fromZone, filterListPointer->toZone);
				else
					sprintf(tempString, "%s policy list (zone %s to zone %s)", filterListPointer->name, filterListPointer->fromZone, filterListPointer->toZone);
				outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
				output_table(nipper, true, tempString2, &settings_policies_heading);
				if (nipper->doCSV == true)
					outputCSVHeadings(nipper, "From Zone", "To Zone", &settings_policies_heading);
				break;
			case type_fw1_firewall:
			case type_nokiaip:
				sprintf(tempString, "%s %s", filterListPointer->name, settings_policycol_table);
				outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
				output_table(nipper, true, tempString2, &settings_policycol_heading);
				if (nipper->doCSV == true)
					outputCSVHeadings(nipper, "Policy", 0, &settings_policycol_heading);
				break;
			case type_css_filter:
				if (filterListPointer->applyTo[0] != 0)
					sprintf(tempString2, "ACL %s (applied to %s)", filterListPointer->name, filterListPointer->applyTo);
				else
					sprintf(tempString2, "ACL %s", filterListPointer->name);
				output_table(nipper, true, tempString2, &settings_acl_css_heading);
				if (nipper->doCSV == true)
					outputCSVHeadings(nipper, "ACL", 0, &settings_acl_css_heading);
				break;
			case type_passport:
			case type_bayaccelar:
				if (strcmp(filterListPointer->name, "**UNASSIGNED**") == 0)
				{
					output_table(nipper, true, settings_filter_table, &settings_filter_heading);
					if (nipper->doCSV == true)
						outputCSVHeadings(nipper, "Filter Set", 0, &settings_filter_heading);
				}
				else if (atoi(filterListPointer->name) < 101)
				{
					sprintf(tempString2, "Global filter set %s (%s)", filterListPointer->listName, filterListPointer->name);
					output_table(nipper, true, tempString2, &settings_filterset_heading);
					if (nipper->doCSV == true)
						outputCSVHeadings(nipper, "Filter Set", 0, &settings_filterset_heading);
				}
				else if ((atoi(filterListPointer->name) > 299) && (atoi(filterListPointer->name) < 1001))
				{
					sprintf(tempString2, "Filter set %s (%s)", filterListPointer->listName, filterListPointer->name);
					output_table(nipper, true, tempString2, &settings_filter_heading);
					if (nipper->doCSV == true)
						outputCSVHeadings(nipper, "Filter Set", 0, &settings_filter_heading);
				}
				break;
			case type_sonicwall:
				
				if (filterListPointer->type == access_std)
				{
					sprintf(tempString, "From %s to %s access rules", filterListPointer->fromZone, filterListPointer->toZone);
					outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
					output_table(nipper, true, tempString2, &settings_accessrules_heading);
					if (nipper->doCSV == true)
						outputCSVHeadings(nipper, "From", "To", &settings_accessrules_heading);
				}
				else
				{
					sprintf(tempString, "From %s to %s policies", filterListPointer->fromZone, filterListPointer->toZone);
					outputFriendly(tempString, tempString2, nipper->maxSize, nipper->outputFormat);
					output_table(nipper, true, tempString2, &settings_accesspolicy_heading);
					if (nipper->doCSV == true)
						outputCSVHeadings(nipper, "From", "To", &settings_accesspolicy_heading);
				}
				break;
		}

		filterPointer = filterListPointer->filter;
		while (filterPointer != 0)
		{
			// Output filter?...
			if (filterPointer->action != filter_action_remark)
			{
				reportFilter(nipper, ruleNumber, filterListPointer, filterPointer);
				ruleNumber++;
			}

			// Output remark/comment...
			else
				reportFilterRemark(nipper, filterListPointer, filterPointer);

			// Next Filter...
			filterPointer = filterPointer->next;
		}

		// Output Table End...
		switch (nipper->deviceType)
		{
			case type_pix_firewall:
			case type_asa_firewall:
			case type_fwsm_firewall:
				if (filterListPointer->type == access_old)
					output_table(nipper, false, tempString2, &settings_accesspix_heading);
				else if (filterListPointer->type == access_std)
					output_table(nipper, false, tempString2, &settings_accessstdpix_heading);
				else if (filterListPointer->type == access_ext)
					output_table(nipper, false, tempString2, &settings_accessextpix_heading);
				break;
				case type_ios_router:
			case type_ios_switch:
			case type_ios_catalyst:
				if (filterListPointer->type == access_std)
					output_table(nipper, false, tempString2, &settings_accessstd_heading);
				else if (filterListPointer->type == access_ext)
					output_table(nipper, false, tempString2, &settings_accessext_heading);
				break;
			case type_sos_firewall:
				output_table(nipper, false, tempString2, &settings_policies_heading);
				break;
			case type_fw1_firewall:
			case type_nokiaip:
				output_table(nipper, false, tempString2, &settings_policycol_heading);
				break;
			case type_css_filter:
				output_table(nipper, false, tempString2, &settings_acl_css_heading);
				break;
			case type_passport:
			case type_bayaccelar:
				if (strcmp(filterListPointer->name, "**UNASSIGNED**") == 0)
					output_table(nipper, false, settings_filter_table, &settings_filter_heading);
				else if (atoi(filterListPointer->name) < 101)
					output_table(nipper, false, tempString2, &settings_filterset_heading);
				else if ((atoi(filterListPointer->name) > 299) && (atoi(filterListPointer->name) < 1001))
					output_table(nipper, false, tempString2, &settings_accessrules_heading);
				break;
			case type_sonicwall:
				if (filterListPointer->type == access_std)
					output_table(nipper, false, tempString2, &settings_accessrules_heading);
				else
					output_table(nipper, false, tempString2, &settings_accesspolicy_heading);
				break;
		}

		filterListPointer = filterListPointer->next;
	}

	nipper->doCSV = false;
}


// Code to report issues with common single filter issue text accross device types...
void reportCommonFilterIssues(struct nipperConfig *nipper, char *listName, char *lineStart, char *lineMid, struct filterConfig *filterPointer, int ruleNumber, struct filterListConfig *filterListPointer)
{
	// Variables...
	int useRuleNumber = false;

	// Set if rule number is to be used...
	switch (nipper->deviceType)
	{
		case type_ios_router:
		case type_ios_switch:
		case type_ios_catalyst:
		case type_pix_firewall:
		case type_asa_firewall:
		case type_fwsm_firewall:
		case type_fw1_firewall:
		case type_nokiaip:
		case type_sonicwall:
			useRuleNumber = true;
			break;

		case type_sos_firewall:
		case type_passport:
		case type_bayaccelar:
		case type_css_filter:
			useRuleNumber = false;
			break;

		case type_nmp_catalyst:
		case type_cos_catalyst:
			// It doesnt matter for these
			break;
	}

	// Bypass issue...
	if ((filterPointer->action == filter_action_bypass) && (nipper->bypassRulesIssue == true))
	{
		switch (nipper->deviceType)
		{
			case type_ios_router:
			case type_ios_switch:
			case type_ios_catalyst:
			case type_pix_firewall:
			case type_asa_firewall:
			case type_fwsm_firewall:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "%s %s %s <a href=\"#%s-rule-%d\">%d</a> %s", lineStart, listName, lineMid, filterListPointer->name, ruleNumber, ruleNumber, report_accesslist_bypass);
				else
					fprintf(nipper->reportFile, "%s %s %s %d %s", lineStart, listName, lineMid, ruleNumber, report_accesslist_bypass);
				break;
			case type_fw1_firewall:
			case type_nokiaip:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "%s %s %s <a href=\"#%s-rule-%d\">%d</a> %s", lineStart, listName, lineMid, filterListPointer->name, ruleNumber, ruleNumber, report_fw1policy_bypass);
				else
					fprintf(nipper->reportFile, "%s %s %s %d %s", lineStart, listName, lineMid, ruleNumber, report_fw1policy_bypass);
				break;
			case type_css_filter:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "%s %s %s <a href=\"#%s-rule-%d\">%d</a> %s", lineStart, listName, lineMid, filterListPointer->name, filterPointer->id, filterPointer->id, report_accesslist_css_bypass);
				else
					fprintf(nipper->reportFile, "%s %s %s %d %s", lineStart, listName, lineMid, filterPointer->id, report_accesslist_css_bypass);
				break;
			case type_passport:
			case type_bayaccelar:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "%s %s %s <a href=\"#%s-rule-%d\">%d</a> %s", lineStart, listName, lineMid, filterListPointer->name, filterPointer->id, filterPointer->id, report_pasfilter_bypass);
				else
					fprintf(nipper->reportFile, "%s %s %s %d %s", lineStart, listName, lineMid, filterPointer->id, report_pasfilter_bypass);
				break;
			case type_sos_firewall:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "%s %s %s <a href=\"#%s-rule-%d\">%d</a> %s", lineStart, listName, lineMid, filterListPointer->name, filterPointer->id, filterPointer->id, report_sospolicy_bypass);
				else
					fprintf(nipper->reportFile, "%s %s %s %d %s", lineStart, listName, lineMid, filterPointer->id, report_sospolicy_bypass);
				break;
			case type_nmp_catalyst:
			case type_cos_catalyst:
			case type_sonicwall:
				// It doesnt matter for these
				break;
		}
	}

	else if ((filterPointer->action == filter_action_reject) && (nipper->rejectRulesIssue == true))
	{
		fprintf(nipper->reportFile, "%s %s %s ", lineStart, listName, lineMid);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
		{
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
			else
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
		}
		if (useRuleNumber == true)
			fprintf(nipper->reportFile, "%d", ruleNumber);
		else
			fprintf(nipper->reportFile, "%d", filterPointer->id);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			fprintf(nipper->reportFile, "</a>");
		fprintf(nipper->reportFile, " %s", report_fw1policy_reject);
	}

	else if ((filterPointer->action == filter_action_default) && (nipper->defaultRulesIssue == true))
	{
		fprintf(nipper->reportFile, "%s %s %s ", lineStart, listName, lineMid);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
		{
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
			else
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
		}
		if (useRuleNumber == true)
			fprintf(nipper->reportFile, "%d", ruleNumber);
		else
			fprintf(nipper->reportFile, "%d", filterPointer->id);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			fprintf(nipper->reportFile, "</a>");
		fprintf(nipper->reportFile, " %s", report_fw1policy_default);
	}

	else if ((filterPointer->enabled == false) && (nipper->disabledRulesIssue == true))
	{
		fprintf(nipper->reportFile, "%s %s %s ", lineStart, listName, lineMid);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
		{
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
			else
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
		}
		if (useRuleNumber == true)
			fprintf(nipper->reportFile, "%d", ruleNumber);
		else
			fprintf(nipper->reportFile, "%d", filterPointer->id);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			fprintf(nipper->reportFile, "</a>");
		fprintf(nipper->reportFile, " %s", report_fw1policy_disabled);
	}
	
	else if (filterPointer->anySource == true)
	{
		fprintf(nipper->reportFile, "%s %s %s ", lineStart, listName, lineMid);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
		{
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
			else
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
		}
		if (useRuleNumber == true)
			fprintf(nipper->reportFile, "%d", ruleNumber);
		else
			fprintf(nipper->reportFile, "%d", filterPointer->id);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			fprintf(nipper->reportFile, "</a>");
		fprintf(nipper->reportFile, " %s", report_fw1policy_anysrc);
		reportSourceDestinationLine(nipper, filterPointer->destination);
		fprintf(nipper->reportFile, ".");
	}
	
	else if (filterPointer->networkSource == true)
	{
		fprintf(nipper->reportFile, "%s %s %s ", lineStart, listName, lineMid);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
		{
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
			else
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
		}
		if (useRuleNumber == true)
			fprintf(nipper->reportFile, "%d", ruleNumber);
		else
			fprintf(nipper->reportFile, "%d", filterPointer->id);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			fprintf(nipper->reportFile, "</a>");
		fprintf(nipper->reportFile, " %s", report_fw1policy_netsrc);
		reportSourceDestinationLine(nipper, filterPointer->destination);
		fprintf(nipper->reportFile, ".");
	}
	
	else if (filterPointer->anySourceService == true)
	{
		fprintf(nipper->reportFile, "%s %s %s ", lineStart, listName, lineMid);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
		{
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
			else
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
		}
		if (useRuleNumber == true)
			fprintf(nipper->reportFile, "%d", ruleNumber);
		else
			fprintf(nipper->reportFile, "%d", filterPointer->id);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			fprintf(nipper->reportFile, "</a>");
		fprintf(nipper->reportFile, " %s", report_fw1policy_anysvcsrc);
		reportSourceDestinationLine(nipper, filterPointer->destination);
		fprintf(nipper->reportFile, ".");
	}
	
	else if (filterPointer->anyDestination == true)
	{
		fprintf(nipper->reportFile, "%s %s %s ", lineStart, listName, lineMid);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
		{
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
			else
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
		}
		if (useRuleNumber == true)
			fprintf(nipper->reportFile, "%d", ruleNumber);
		else
			fprintf(nipper->reportFile, "%d", filterPointer->id);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			fprintf(nipper->reportFile, "</a>");
		fprintf(nipper->reportFile, " %s", report_fw1policy_anydst);
		reportSourceDestinationLine(nipper, filterPointer->destination);
		fprintf(nipper->reportFile, " to any destination.");
	}
	
	else if (filterPointer->networkDestination == true)
	{
		fprintf(nipper->reportFile, "%s %s %s ", lineStart, listName, lineMid);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
		{
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
			else
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
		}
		if (useRuleNumber == true)
			fprintf(nipper->reportFile, "%d", ruleNumber);
		else
			fprintf(nipper->reportFile, "%d", filterPointer->id);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			fprintf(nipper->reportFile, "</a>");
		fprintf(nipper->reportFile, " %s", report_fw1policy_netdst);
		reportSourceDestinationLine(nipper, filterPointer->destination);
		fprintf(nipper->reportFile, " to a network destination.");
	}
	
	else if (filterPointer->anyDestinationService == true)
	{
		fprintf(nipper->reportFile, "%s %s %s ", lineStart, listName, lineMid);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
		{
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
			else
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
		}
		if (useRuleNumber == true)
			fprintf(nipper->reportFile, "%d", ruleNumber);
		else
			fprintf(nipper->reportFile, "%d", filterPointer->id);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			fprintf(nipper->reportFile, "</a>");
		fprintf(nipper->reportFile, " %s", report_fw1policy_netdstsvc);
		reportSourceDestinationLine(nipper, filterPointer->destination);
		fprintf(nipper->reportFile, " to any destination service.");
	}
	
	else if (filterPointer->logging == true)
	{
		fprintf(nipper->reportFile, "%s %s %s ", lineStart, listName, lineMid);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
		{
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
			else
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
		}
		if (useRuleNumber == true)
			fprintf(nipper->reportFile, "%d", ruleNumber);
		else
			fprintf(nipper->reportFile, "%d", filterPointer->id);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			fprintf(nipper->reportFile, "</a>");
		fprintf(nipper->reportFile, " %s", report_fw1policy_nolog);
	}

	else if (filterPointer->logDeny == true)
	{
		fprintf(nipper->reportFile, "%s %s %s ", lineStart, listName, lineMid);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
		{
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
			else
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
		}
		if (useRuleNumber == true)
			fprintf(nipper->reportFile, "%d", ruleNumber);
		else
			fprintf(nipper->reportFile, "%d", filterPointer->id);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			fprintf(nipper->reportFile, "</a>");
		fprintf(nipper->reportFile, " %s", report_fw1policy_nologdenied);
	}
}
void reportCommonStandardFilterIssues(struct nipperConfig *nipper, char *listName, char *lineStart, char *lineMid, struct filterConfig *filterPointer, int ruleNumber, struct filterListConfig *filterListPointer)
{
	// Variables...
	int useRuleNumber = false;

	// Set if rule number is to be used...
	switch (nipper->deviceType)
	{
		case type_ios_router:
		case type_ios_switch:
		case type_ios_catalyst:
		case type_pix_firewall:
		case type_asa_firewall:
		case type_fwsm_firewall:
		case type_fw1_firewall:
		case type_nokiaip:
		case type_sonicwall:
			useRuleNumber = true;
			break;

		case type_sos_firewall:
		case type_passport:
		case type_bayaccelar:
		case type_css_filter:
			useRuleNumber = false;
			break;

		case type_nmp_catalyst:
		case type_cos_catalyst:
			// It doesnt matter for these
			break;
	}

	// Bypass issue...
	if ((filterPointer->action == filter_action_bypass) && (nipper->bypassRulesIssue == true))
	{
		switch (nipper->deviceType)
		{
			case type_ios_router:
			case type_ios_switch:
			case type_ios_catalyst:
			case type_pix_firewall:
			case type_asa_firewall:
			case type_fwsm_firewall:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "%s %s %s <a href=\"#%s-rule-%d\">%d</a> %s", lineStart, listName, lineMid, filterListPointer->name, ruleNumber, ruleNumber, report_accesslist_bypass);
				else
					fprintf(nipper->reportFile, "%s %s %s %d %s", lineStart, listName, lineMid, ruleNumber, report_accesslist_bypass);
				break;
			case type_fw1_firewall:
			case type_nokiaip:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "%s %s %s <a href=\"#%s-rule-%d\">%d</a> %s", lineStart, listName, lineMid, filterListPointer->name, ruleNumber, ruleNumber, report_fw1policy_bypass);
				else
					fprintf(nipper->reportFile, "%s %s %s %d %s", lineStart, listName, lineMid, ruleNumber, report_fw1policy_bypass);
				break;
			case type_css_filter:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "%s %s %s <a href=\"#%s-rule-%d\">%d</a> %s", lineStart, listName, lineMid, filterListPointer->name, filterPointer->id, filterPointer->id, report_accesslist_css_bypass);
				else
					fprintf(nipper->reportFile, "%s %s %s %d %s", lineStart, listName, lineMid, filterPointer->id, report_accesslist_css_bypass);
				break;
			case type_passport:
			case type_bayaccelar:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "%s %s %s <a href=\"#%s-rule-%d\">%d</a> %s", lineStart, listName, lineMid, filterListPointer->name, filterPointer->id, filterPointer->id, report_pasfilter_bypass);
				else
					fprintf(nipper->reportFile, "%s %s %s %d %s", lineStart, listName, lineMid, filterPointer->id, report_pasfilter_bypass);
				break;
			case type_sos_firewall:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "%s %s %s <a href=\"#%s-rule-%d\">%d</a> %s", lineStart, listName, lineMid, filterListPointer->name, filterPointer->id, filterPointer->id, report_sospolicy_bypass);
				else
					fprintf(nipper->reportFile, "%s %s %s %d %s", lineStart, listName, lineMid, filterPointer->id, report_sospolicy_bypass);
				break;
			case type_nmp_catalyst:
			case type_cos_catalyst:
			case type_sonicwall:
				// It doesnt matter for these
				break;
		}
	}

	else if ((filterPointer->action == filter_action_reject) && (nipper->rejectRulesIssue == true))
	{
		fprintf(nipper->reportFile, "%s %s %s ", lineStart, listName, lineMid);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
		{
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
			else
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
		}
		if (useRuleNumber == true)
			fprintf(nipper->reportFile, "%d", ruleNumber);
		else
			fprintf(nipper->reportFile, "%d", filterPointer->id);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			fprintf(nipper->reportFile, "</a>");
		if (nipper->deviceType == type_sonicwall)
			fprintf(nipper->reportFile, " %s", report_fw1policy_reject);
		else
			fprintf(nipper->reportFile, " %s", report_fw1policy_reject);
	}

	else if ((filterPointer->action == filter_action_default) && (nipper->defaultRulesIssue == true))
	{
		fprintf(nipper->reportFile, "%s %s %s ", lineStart, listName, lineMid);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
		{
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
			else
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
		}
		if (useRuleNumber == true)
			fprintf(nipper->reportFile, "%d", ruleNumber);
		else
			fprintf(nipper->reportFile, "%d", filterPointer->id);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			fprintf(nipper->reportFile, "</a>");
		fprintf(nipper->reportFile, " %s", report_fw1policy_default);
	}

	else if ((filterPointer->enabled == false) && (nipper->disabledRulesIssue == true))
	{
		fprintf(nipper->reportFile, "%s %s %s ", lineStart, listName, lineMid);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
		{
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
			else
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
		}
		if (useRuleNumber == true)
			fprintf(nipper->reportFile, "%d", ruleNumber);
		else
			fprintf(nipper->reportFile, "%d", filterPointer->id);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			fprintf(nipper->reportFile, "</a>");
		fprintf(nipper->reportFile, " %s", report_fw1policy_disabled);
	}
	
	else if (filterPointer->anySource == true)
	{
		fprintf(nipper->reportFile, "%s %s %s ", lineStart, listName, lineMid);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
		{
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
			else
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
		}
		if (useRuleNumber == true)
			fprintf(nipper->reportFile, "%d", ruleNumber);
		else
			fprintf(nipper->reportFile, "%d", filterPointer->id);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			fprintf(nipper->reportFile, "</a>");
		fprintf(nipper->reportFile, " %s", report_fw1policy_std_anysrc);
	}
	
	else if (filterPointer->networkSource == true)
	{
		fprintf(nipper->reportFile, "%s %s %s ", lineStart, listName, lineMid);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
		{
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
			else
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
		}
		if (useRuleNumber == true)
			fprintf(nipper->reportFile, "%d", ruleNumber);
		else
			fprintf(nipper->reportFile, "%d", filterPointer->id);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			fprintf(nipper->reportFile, "</a>");
		fprintf(nipper->reportFile, " %s", report_fw1policy_std_netsrc);
	}
	
	else if (filterPointer->anySourceService == true)
	{
		fprintf(nipper->reportFile, "%s %s %s ", lineStart, listName, lineMid);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
		{
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
			else
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
		}
		if (useRuleNumber == true)
			fprintf(nipper->reportFile, "%d", ruleNumber);
		else
			fprintf(nipper->reportFile, "%d", filterPointer->id);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			fprintf(nipper->reportFile, "</a>");
		fprintf(nipper->reportFile, " %s", report_fw1policy_std_anysvcsrc);
	}
	
	else if (filterPointer->logging == true)
	{
		fprintf(nipper->reportFile, "%s %s %s ", lineStart, listName, lineMid);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
		{
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
			else
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
		}
		if (useRuleNumber == true)
			fprintf(nipper->reportFile, "%d", ruleNumber);
		else
			fprintf(nipper->reportFile, "%d", filterPointer->id);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			fprintf(nipper->reportFile, "</a>");
		fprintf(nipper->reportFile, " %s", report_fw1policy_nolog);
	}

	else if (filterPointer->logDeny == true)
	{
		fprintf(nipper->reportFile, "%s %s %s ", lineStart, listName, lineMid);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
		{
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
			else
				fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
		}
		if (useRuleNumber == true)
			fprintf(nipper->reportFile, "%d", ruleNumber);
		else
			fprintf(nipper->reportFile, "%d", filterPointer->id);
		if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			fprintf(nipper->reportFile, "</a>");
		fprintf(nipper->reportFile, " %s", report_fw1policy_nologdenied);
	}
}


// Code to report issues with common multiple filter issue table text accross device types...
void reportCommonFilterTableIssues(struct nipperConfig *nipper, char *listName, struct filterConfig *filterPointer, int ruleNumber, struct filterListConfig *filterListPointer)
{
	// Variables...
	int issueFound = false;
	int useRuleNumber = false;

	// Set if rule number is to be used...
	switch (nipper->deviceType)
	{
		case type_ios_router:
		case type_ios_switch:
		case type_ios_catalyst:
		case type_pix_firewall:
		case type_asa_firewall:
		case type_fwsm_firewall:
		case type_fw1_firewall:
		case type_nokiaip:
		case type_sonicwall:
			useRuleNumber = true;
			break;

		case type_sos_firewall:
		case type_passport:
		case type_bayaccelar:
		case type_css_filter:
			useRuleNumber = false;
			break;

		case type_nmp_catalyst:
		case type_cos_catalyst:
			// It doesnt matter for these
			break;
	}

	// Bypass issue...
	if ((filterPointer->action == filter_action_bypass) && (nipper->bypassRulesIssue == true))
	{
		issueFound = true;
		switch (nipper->deviceType)
		{
			case type_ios_router:
			case type_ios_switch:
			case type_ios_catalyst:
			case type_pix_firewall:
			case type_asa_firewall:
			case type_fwsm_firewall:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "%s%s%s<a href=\"#%s-rule-%d\">%d</a>%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid, filterListPointer->name, ruleNumber, ruleNumber, nipper->tablerow_mid, report_accesslistt_bypass);
				else
					fprintf(nipper->reportFile, "%s%s%s%d%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid, ruleNumber, nipper->tablerow_mid, report_accesslistt_bypass);
				break;
	
			case type_fw1_firewall:
			case type_nokiaip:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "%s%s%s<a href=\"#%s-rule-%d\">%d</a>%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid, filterListPointer->name, ruleNumber, ruleNumber, nipper->tablerow_mid, report_fw1policyt_bypass);
				else
					fprintf(nipper->reportFile, "%s%s%s%d%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid, ruleNumber, nipper->tablerow_mid, report_fw1policyt_bypass);
				break;
	
			case type_sos_firewall:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "%s%s%s<a href=\"#%s-rule-%d\">%d</a>%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid, filterListPointer->name, filterPointer->id, filterPointer->id, nipper->tablerow_mid, report_accesslistt_css_bypass);
				else
					fprintf(nipper->reportFile, "%s%s%s%d%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid, filterPointer->id, nipper->tablerow_mid, report_accesslistt_css_bypass);
				break;
	
			case type_passport:
			case type_bayaccelar:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "%s%s%s<a href=\"#%s-rule-%d\">%d</a>%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid, filterListPointer->name, filterPointer->id, filterPointer->id, nipper->tablerow_mid, report_sospolicyt_bypass);
				else
					fprintf(nipper->reportFile, "%s%s%s%d%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid, filterPointer->id, nipper->tablerow_mid, report_pasfiltert_bypass);
				break;
	
			case type_css_filter:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "%s%s%s<a href=\"#%s-rule-%d\">%d</a>%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid, filterListPointer->name, filterPointer->id, filterPointer->id, nipper->tablerow_mid, report_accesslistt_css_bypass);
				else
					fprintf(nipper->reportFile, "%s%s%s%d%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid, filterPointer->id, nipper->tablerow_mid, report_accesslistt_css_bypass);
				break;
	
			case type_nmp_catalyst:
			case type_cos_catalyst:
			case type_sonicwall:
				// It doesnt matter for these
				break;
		}
	}

	if ((filterPointer->action == filter_action_reject) && (nipper->rejectRulesIssue == true))
	{
		if (issueFound == true)
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_itemsep, report_fw1policyt_reject);
		else
		{
			issueFound = true;
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			{
				if (useRuleNumber == true)
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
				else
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
			}
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "%d", ruleNumber);
			else
				fprintf(nipper->reportFile, "%d", filterPointer->id);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "</a>");
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, report_fw1policyt_reject);
		}
	}

	if ((filterPointer->action == filter_action_default) && (nipper->defaultRulesIssue == true))
	{
		if (issueFound == true)
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_itemsep, report_fw1policyt_default);
		else
		{
			issueFound = true;
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			{
				if (useRuleNumber == true)
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
				else
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
			}
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "%d", ruleNumber);
			else
				fprintf(nipper->reportFile, "%d", filterPointer->id);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "</a>");
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, report_fw1policyt_default);
		}
	}

	if ((filterPointer->enabled == false) && (nipper->disabledRulesIssue == true))
	{
		if (issueFound == true)
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_itemsep, report_fw1policyt_disabled);
		else
		{
			issueFound = true;
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			{
				if (useRuleNumber == true)
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
				else
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
			}
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "%d", ruleNumber);
			else
				fprintf(nipper->reportFile, "%d", filterPointer->id);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "</a>");
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, report_fw1policyt_disabled);
		}
	}

	if (filterPointer->anySource == true)
	{
		if (issueFound == true)
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_itemsep, report_fw1policyt_anysrc);
		else
		{
			issueFound = true;
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			{
				if (useRuleNumber == true)
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
				else
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
			}
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "%d", ruleNumber);
			else
				fprintf(nipper->reportFile, "%d", filterPointer->id);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "</a>");
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, report_fw1policyt_anysrc);
		}
		reportSourceDestinationLine(nipper, filterPointer->destination);
		fprintf(nipper->reportFile, ".");
	}

	if (filterPointer->networkSource == true)
	{
		if (issueFound == true)
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_itemsep, report_fw1policyt_netsrc);
		else
		{
			issueFound = true;
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			{
				if (useRuleNumber == true)
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
				else
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
			}
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "%d", ruleNumber);
			else
				fprintf(nipper->reportFile, "%d", filterPointer->id);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "</a>");
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, report_fw1policyt_netsrc);
		}
		reportSourceDestinationLine(nipper, filterPointer->destination);
		fprintf(nipper->reportFile, ".");
	}

	if (filterPointer->anySourceService == true)
	{
		if (issueFound == true)
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_itemsep, report_fw1policyt_anysvcsrc);
		else
		{
			issueFound = true;
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			{
				if (useRuleNumber == true)
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
				else
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
			}
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "%d", ruleNumber);
			else
				fprintf(nipper->reportFile, "%d", filterPointer->id);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "</a>");
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, report_fw1policyt_anysvcsrc);
		}
		reportSourceDestinationLine(nipper, filterPointer->destination);
		fprintf(nipper->reportFile, ".");
	}

	if (filterPointer->anyDestination == true)
	{
		if (issueFound == true)
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_itemsep, report_fw1policyt_anydst);
		else
		{
			issueFound = true;
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			{
				if (useRuleNumber == true)
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
				else
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
			}
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "%d", ruleNumber);
			else
				fprintf(nipper->reportFile, "%d", filterPointer->id);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "</a>");
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, report_fw1policyt_anydst);
		}
		reportSourceDestinationLine(nipper, filterPointer->source);
		fprintf(nipper->reportFile, " to any destination.");
	}

	if (filterPointer->networkDestination == true)
	{
		if (issueFound == true)
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_itemsep, report_fw1policyt_anydst);
		else
		{
			issueFound = true;
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			{
				if (useRuleNumber == true)
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
				else
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
			}
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "%d", ruleNumber);
			else
				fprintf(nipper->reportFile, "%d", filterPointer->id);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "</a>");
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, report_fw1policyt_anydst);
		}
		reportSourceDestinationLine(nipper, filterPointer->source);
		fprintf(nipper->reportFile, " to a network destination.");
	}

	if (filterPointer->anyDestinationService == true)
	{
		if (issueFound == true)
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_itemsep, report_fw1policyt_anydst);
		else
		{
			issueFound = true;
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			{
				if (useRuleNumber == true)
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
				else
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
			}
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "%d", ruleNumber);
			else
				fprintf(nipper->reportFile, "%d", filterPointer->id);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "</a>");
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, report_fw1policyt_anydst);
		}
		reportSourceDestinationLine(nipper, filterPointer->source);
		fprintf(nipper->reportFile, " to any destination service.");
	}

	if (filterPointer->logging == true)
	{
		if (issueFound == true)
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_itemsep, report_fw1policyt_nolog);
		else
		{
			issueFound = true;
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			{
				if (useRuleNumber == true)
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
				else
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
			}
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "%d", ruleNumber);
			else
				fprintf(nipper->reportFile, "%d", filterPointer->id);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "</a>");
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, report_fw1policyt_nolog);
		}
	}

	if (filterPointer->logDeny == true)
	{
		if (issueFound == true)
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_itemsep, report_fw1policyt_nologdenied);
		else
		{
			issueFound = true;
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			{
				if (useRuleNumber == true)
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
				else
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
			}
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "%d", ruleNumber);
			else
				fprintf(nipper->reportFile, "%d", filterPointer->id);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "</a>");
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, report_fw1policyt_nologdenied);
		}
	}

	// If issue found...
	if (issueFound == true)
		fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
}
void reportCommonStandardFilterTableIssues(struct nipperConfig *nipper, char *listName, struct filterConfig *filterPointer, int ruleNumber, struct filterListConfig *filterListPointer)
{
	// Variables...
	int issueFound = false;
	int useRuleNumber = false;

	// Set if rule number is to be used...
	switch (nipper->deviceType)
	{
		case type_ios_router:
		case type_ios_switch:
		case type_ios_catalyst:
		case type_pix_firewall:
		case type_asa_firewall:
		case type_fwsm_firewall:
		case type_fw1_firewall:
		case type_nokiaip:
		case type_sonicwall:
			useRuleNumber = true;
			break;

		case type_sos_firewall:
		case type_passport:
		case type_bayaccelar:
		case type_css_filter:
			useRuleNumber = false;
			break;

		case type_nmp_catalyst:
		case type_cos_catalyst:
			// It doesnt matter for these
			break;
	}

	// Bypass issue...
	if ((filterPointer->action == filter_action_bypass) && (nipper->bypassRulesIssue == true))
	{
		issueFound = true;
		switch (nipper->deviceType)
		{
			case type_ios_router:
			case type_ios_switch:
			case type_ios_catalyst:
			case type_pix_firewall:
			case type_asa_firewall:
			case type_fwsm_firewall:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "%s%s%s<a href=\"#%s-rule-%d\">%d</a>%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid, filterListPointer->name, ruleNumber, ruleNumber, nipper->tablerow_mid, report_accesslistt_bypass);
				else
					fprintf(nipper->reportFile, "%s%s%s%d%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid, ruleNumber, nipper->tablerow_mid, report_accesslistt_bypass);
				break;
	
			case type_fw1_firewall:
			case type_nokiaip:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "%s%s%s<a href=\"#%s-rule-%d\">%d</a>%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid, filterListPointer->name, ruleNumber, ruleNumber, nipper->tablerow_mid, report_fw1policyt_bypass);
				else
					fprintf(nipper->reportFile, "%s%s%s%d%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid, ruleNumber, nipper->tablerow_mid, report_fw1policyt_bypass);
				break;
	
			case type_sos_firewall:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "%s%s%s<a href=\"#%s-rule-%d\">%d</a>%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid, filterListPointer->name, filterPointer->id, filterPointer->id, nipper->tablerow_mid, report_accesslistt_css_bypass);
				else
					fprintf(nipper->reportFile, "%s%s%s%d%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid, filterPointer->id, nipper->tablerow_mid, report_accesslistt_css_bypass);
				break;
	
			case type_passport:
			case type_bayaccelar:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "%s%s%s<a href=\"#%s-rule-%d\">%d</a>%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid, filterListPointer->name, filterPointer->id, filterPointer->id, nipper->tablerow_mid, report_pasfiltert_bypass);
				else
					fprintf(nipper->reportFile, "%s%s%s%d%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid, filterPointer->id, nipper->tablerow_mid, report_pasfiltert_bypass);
				break;
	
			case type_css_filter:
				if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
					fprintf(nipper->reportFile, "%s%s%s<a href=\"#%s-rule-%d\">%d</a>%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid, filterListPointer->name, filterPointer->id, filterPointer->id, nipper->tablerow_mid, report_accesslistt_css_bypass);
				else
					fprintf(nipper->reportFile, "%s%s%s%d%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid, filterPointer->id, nipper->tablerow_mid, report_accesslistt_css_bypass);
				break;
	
			case type_nmp_catalyst:
			case type_cos_catalyst:
			case type_sonicwall:
				// It doesnt matter for these
				break;
		}
	}

	if ((filterPointer->action == filter_action_reject) && (nipper->rejectRulesIssue == true))
	{
		if (issueFound == true)
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_itemsep, report_fw1policyt_reject);
		else
		{
			issueFound = true;
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			{
				if (useRuleNumber == true)
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
				else
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
			}
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "%d", ruleNumber);
			else
				fprintf(nipper->reportFile, "%d", filterPointer->id);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "</a>");
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, report_fw1policyt_reject);
		}
	}

	if ((filterPointer->action == filter_action_default) && (nipper->defaultRulesIssue == true))
	{
		if (issueFound == true)
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_itemsep, report_fw1policyt_default);
		else
		{
			issueFound = true;
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			{
				if (useRuleNumber == true)
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
				else
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
			}
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "%d", ruleNumber);
			else
				fprintf(nipper->reportFile, "%d", filterPointer->id);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "</a>");
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, report_fw1policyt_default);
		}
	}

	if ((filterPointer->enabled == false) && (nipper->disabledRulesIssue == true))
	{
		if (issueFound == true)
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_itemsep, report_fw1policyt_disabled);
		else
		{
			issueFound = true;
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			{
				if (useRuleNumber == true)
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
				else
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
			}
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "%d", ruleNumber);
			else
				fprintf(nipper->reportFile, "%d", filterPointer->id);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "</a>");
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, report_fw1policyt_disabled);
		}
	}

	if (filterPointer->anySource == true)
	{
		if (issueFound == true)
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_itemsep, report_fw1policyt_anysrc);
		else
		{
			issueFound = true;
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			{
				if (useRuleNumber == true)
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
				else
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
			}
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "%d", ruleNumber);
			else
				fprintf(nipper->reportFile, "%d", filterPointer->id);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "</a>");
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, report_fw1policyt_std_anysrc);
		}
	}

	if (filterPointer->networkSource == true)
	{
		if (issueFound == true)
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_itemsep, report_fw1policyt_netsrc);
		else
		{
			issueFound = true;
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			{
				if (useRuleNumber == true)
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
				else
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
			}
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "%d", ruleNumber);
			else
				fprintf(nipper->reportFile, "%d", filterPointer->id);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "</a>");
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, report_fw1policyt_std_netsrc);
		}
	}

	if (filterPointer->anySourceService == true)
	{
		if (issueFound == true)
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_itemsep, report_fw1policyt_anysvcsrc);
		else
		{
			issueFound = true;
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, listName, nipper->tablerow_mid);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
			{
				if (useRuleNumber == true)
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, ruleNumber);
				else
					fprintf(nipper->reportFile, "<a href=\"#%s-rule-%d\">", filterListPointer->name, filterPointer->id);
			}
			if (useRuleNumber == true)
				fprintf(nipper->reportFile, "%d", ruleNumber);
			else
				fprintf(nipper->reportFile, "%d", filterPointer->id);
			if ((nipper->outputFormat == output_html) && (nipper->configReport == true))
				fprintf(nipper->reportFile, "</a>");
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, report_fw1policyt_std_anysvcsrc);
		}
	}

	// If issue found...
	if (issueFound == true)
		fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
}



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


void pixHTTPConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct mgmtHostsPIX *mgmtHostsPointer = 0;
	char tempString[nipper->maxSize];

	output_table(nipper, true, settings_http_table, &settings_general_heading);
	if (nipper->pix->http->httpServer == false)
		fprintf(nipper->reportFile, "%sHTTPS Server%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sHTTPS Server%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	fprintf(nipper->reportFile, "%sHTTPS Server Port%s%d%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->pix->http->httpServerPort, nipper->tablerow_end);
	if (((nipper->versionMajor == 7) && (nipper->versionMinor == 0) && (nipper->versionRevision > 0)) || ((nipper->versionMajor >= 7) && (nipper->versionMinor > 0)))
	{
		if (nipper->pix->http->requireCert == false)
			fprintf(nipper->reportFile, "%sClients Require Certificates%sNo%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sClients Require Certificates%sYes%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	}
	if (nipper->pix->http->httpRedirect == true)
	{
		fprintf(nipper->reportFile, "%sHTTP Redirect%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		fprintf(nipper->reportFile, "%sHTTP Redirect Port%s%d%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->pix->http->httpRedirectPort, nipper->tablerow_end);
	}
	else
		fprintf(nipper->reportFile, "%sHTTP Redirect%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	output_table(nipper, false, settings_http_table, &settings_general_heading);
	if (nipper->pix->http->host != 0)
	{
		output_table(nipper, true, settings_httphosts_table, &settings_httphosts_heading);
		mgmtHostsPointer = nipper->pix->http->host;
		while (mgmtHostsPointer != 0)
		{
			outputFriendly(mgmtHostsPointer->interface, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, tempString, nipper->tablerow_mid);
			outputFriendly(mgmtHostsPointer->ipAddress, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
			outputFriendly(mgmtHostsPointer->netMask, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_end);
			mgmtHostsPointer = mgmtHostsPointer->next;
		}
		output_table(nipper, false, settings_httphosts_table, &settings_httphosts_heading);
	}
}



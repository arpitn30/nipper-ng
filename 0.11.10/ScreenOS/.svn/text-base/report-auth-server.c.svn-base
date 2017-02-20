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

// This file contains code for ScreenOS Auth Servers reporting


void sosAuthServerConfig(struct nipperConfig *nipper)
{
	// Variables...
	char tempString[nipper->maxSize];
	struct authServerSOS *authServerPointer = 0;

	output_table(nipper, true, settings_authservers_table, &settings_authservers_heading);
	authServerPointer = nipper->sos->authServer;
	while (authServerPointer != 0)
	{
		fprintf(nipper->reportFile, "%s%d%s", nipper->tablerow_start, authServerPointer->id, nipper->tablerow_mid);
		outputFriendly(authServerPointer->name, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
		switch (authServerPointer->type)
		{
			case authtype_builtin:
				fprintf(nipper->reportFile, "Built-in%s", nipper->tablerow_mid);
				break;
			case authtype_radius:
				fprintf(nipper->reportFile, "RADIUS%s", nipper->tablerow_mid);
				addAbbreviation("RADIUS", false);
				break;
			case authtype_ldap:
				fprintf(nipper->reportFile, "LDAP%s", nipper->tablerow_mid);
				addAbbreviation("LDAP", false);
				break;
			case authtype_securid:
				fprintf(nipper->reportFile, "SecurID%s", nipper->tablerow_mid);
				break;
		}
		outputFriendly(authServerPointer->serverName, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
		if (authServerPointer->backup2[0] == 0)
		{
			outputFriendly(authServerPointer->backup1, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
		}
		else
		{
			outputFriendly(authServerPointer->backup1, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s, ", tempString);
			outputFriendly(authServerPointer->backup2, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
		}
		if (authServerPointer->timeout == 0)
			fprintf(nipper->reportFile, "None%s", nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "%d mins%s", authServerPointer->timeout, nipper->tablerow_mid);
		if (authServerPointer->forcedTimeout == 0)
			fprintf(nipper->reportFile, "None%s", nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "%d mins%s", authServerPointer->forcedTimeout, nipper->tablerow_mid);
		outputFriendly(authServerPointer->sourceInterface, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%s%s", tempString, nipper->tablerow_mid);
		if (nipper->passwords == true)
		{
			outputFriendly(authServerPointer->radiusSecret, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%s", tempString);
		}
		fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
		authServerPointer = authServerPointer->next;
	}
	output_table(nipper, false, settings_authservers_table, &settings_authservers_heading);
}


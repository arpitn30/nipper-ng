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


void iosLoggingConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct host *hostPointer = 0;
	char tempString[nipper->maxSize];

	if (nipper->loggingLevels == unconfigured)
		nipper->loggingLevels = true;
	output_table(nipper, true, settings_logging_table, &settings_general_heading);
	if (nipper->ios->logging->logging == true)
		fprintf(nipper->reportFile, "%sLogging%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sLogging%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	if (nipper->ios->logging->logEnable == true)
		fprintf(nipper->reportFile, "%sLog Configuration Changes%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	else
		fprintf(nipper->reportFile, "%sLog Configuration Changes%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);

	// Logging to console
	if (nipper->ios->logging->consoleLogging != false)
	{
		if (nipper->ios->logging->consoleLogging == true)
			fprintf(nipper->reportFile, "%sConsole Logging%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "%sConsole Logging%sSystem Default%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		if (nipper->ios->logging->consoleLevel == -1)
			fprintf(nipper->reportFile, "%sConsole Logging Severity Level%sDefault%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else
		{
			switch (nipper->ios->logging->consoleLevel)
			{
				case 0:
					fprintf(nipper->reportFile, "%sConsole Logging Severity Level%sEmergencies (0)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
				case 1:
					fprintf(nipper->reportFile, "%sConsole Logging Severity Level%sAlerts (1)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
				case 2:
					fprintf(nipper->reportFile, "%sConsole Logging Severity Level%sCritical (2)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
				case 3:
					fprintf(nipper->reportFile, "%sConsole Logging Severity Level%sErrors (3)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
				case 4:
					fprintf(nipper->reportFile, "%sConsole Logging Severity Level%sWarnings (4)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
				case 5:
					fprintf(nipper->reportFile, "%sConsole Logging Severity Level%sNotifications (5)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
				case 6:
					fprintf(nipper->reportFile, "%sConsole Logging Severity Level%sInformational (6)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
				case 7:
					fprintf(nipper->reportFile, "%sConsole Logging Severity Level%sDebugging (7)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
			}
		}
	}
	else
		fprintf(nipper->reportFile, "%sConsole Logging%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);

	// Syslog stuff (only works if a host is configured)
	if (nipper->ios->logging->logServer != 0)
	{
		fprintf(nipper->reportFile, "%sSyslog Logging%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		switch (nipper->ios->logging->loggingTrap)
		{
			case 0:
				fprintf(nipper->reportFile, "%sSyslog Logging Severity Level%sEmergencies (0)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
			case 1:
				fprintf(nipper->reportFile, "%sSyslog Logging Severity Level%sAlerts (1)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
			case 2:
				fprintf(nipper->reportFile, "%sSyslog Logging Severity Level%sCritical (2)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
			case 3:
				fprintf(nipper->reportFile, "%sSyslog Logging Severity Level%sErrors (3)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
			case 4:
				fprintf(nipper->reportFile, "%sSyslog Logging Severity Level%sWarnings (4)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
			case 5:
				fprintf(nipper->reportFile, "%sSyslog Logging Severity Level%sNotifications (5)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
			case 6:
				fprintf(nipper->reportFile, "%sSyslog Logging Severity Level%sInformational (6)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
			case 7:
				fprintf(nipper->reportFile, "%sSyslog Logging Severity Level%sDebugging (7)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
		}
		outputFriendly(nipper->ios->logging->facility, tempString, nipper->maxSize, nipper->outputFormat);
		fprintf(nipper->reportFile, "%sSyslog Logging Facility%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
		if (nipper->ios->logging->logCount == true)
			fprintf(nipper->reportFile, "%sSyslog Message Counting%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "%sSyslog Message Counting%sSystem Default%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		if (nipper->ios->logging->originId[0] != 0)
		{
			outputFriendly(nipper->ios->logging->originId, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%sSyslog Origin ID%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
		}
		if (nipper->ios->logging->sourceInterface[0] != 0)
		{
			outputFriendly(nipper->ios->logging->sourceInterface, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%sSyslog Source Interface%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
		}
		hostPointer = nipper->ios->logging->logServer;
		while (hostPointer != 0)
		{
			outputFriendly(hostPointer->server, tempString, nipper->maxSize, nipper->outputFormat);
			fprintf(nipper->reportFile, "%sSyslog Logging Server%s%s%s", nipper->tablerow_start, nipper->tablerow_mid, tempString, nipper->tablerow_end);
			hostPointer = hostPointer->next;
		}
	}
	else
		fprintf(nipper->reportFile, "%sSyslog Logging%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);

	// Logging to buffer
	if (nipper->ios->logging->bufferedLogging != false)
	{
		if (nipper->ios->logging->bufferedLogging == true)
			fprintf(nipper->reportFile, "%sBuffer Logging%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "%sBuffer Logging%sSystem Default%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		if (nipper->ios->logging->bufferSize == -1)
			fprintf(nipper->reportFile, "%sBuffer Size%sDefault%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else
			fprintf(nipper->reportFile, "%sBuffer Size%s%d bytes%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->ios->logging->bufferSize, nipper->tablerow_end);
		if (nipper->ios->logging->bufferLevel == -1)
			fprintf(nipper->reportFile, "%sBuffer Logging Severity Level%sDefault%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		else
		{
			switch (nipper->ios->logging->bufferLevel)
			{
				case 0:
					fprintf(nipper->reportFile, "%sBuffer Logging Severity Level%sEmergencies (0)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
				case 1:
					fprintf(nipper->reportFile, "%sBuffer Logging Severity Level%sAlerts (1)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
				case 2:
					fprintf(nipper->reportFile, "%sBuffer Logging Severity Level%sCritical (2)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
				case 3:
					fprintf(nipper->reportFile, "%sBuffer Logging Severity Level%sErrors (3)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
				case 4:
					fprintf(nipper->reportFile, "%sBuffer Logging Severity Level%sWarnings (4)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
				case 5:
					fprintf(nipper->reportFile, "%sBuffer Logging Severity Level%sNotifications (5)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
				case 6:
					fprintf(nipper->reportFile, "%sBuffer Logging Severity Level%sInformational (6)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
				case 7:
					fprintf(nipper->reportFile, "%sBuffer Logging Severity Level%sDebugging (7)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
					break;
			}
		}
	}
	else
		fprintf(nipper->reportFile, "%sBuffer Logging%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);

	// Logging to terminal lines
	if (nipper->ios->logging->monitorLogging == true)
	{
		fprintf(nipper->reportFile, "%sTerminal Line Logging%sEnabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
		switch (nipper->ios->logging->monitorLevel)
		{
			case 0:
				fprintf(nipper->reportFile, "%sTerminal Line Logging Severity Level%sEmergencies (0)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
			case 1:
				fprintf(nipper->reportFile, "%sTerminal Line Logging Severity Level%sAlerts (1)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
			case 2:
				fprintf(nipper->reportFile, "%sTerminal Line Logging Severity Level%sCritical (2)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
			case 3:
				fprintf(nipper->reportFile, "%sTerminal Line Logging Severity Level%sErrors (3)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
			case 4:
				fprintf(nipper->reportFile, "%sTerminal Line Logging Severity Level%sWarnings (4)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
			case 5:
				fprintf(nipper->reportFile, "%sTerminal Line Logging Severity Level%sNotifications (5)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
			case 6:
				fprintf(nipper->reportFile, "%sTerminal Line Logging Severity Level%sInformational (6)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
			case 7:
				fprintf(nipper->reportFile, "%sTerminal Line Logging Severity Level%sDebugging (7)%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
				break;
		}
	}
	else
		fprintf(nipper->reportFile, "%sTerminal Line Logging%sDisabled%s", nipper->tablerow_start, nipper->tablerow_mid, nipper->tablerow_end);
	output_table(nipper, false, settings_logging_table, &settings_general_heading);
}


void iosLoggingIssue(struct nipperConfig *nipper)
{
	output_parseText(report_logging_obs1, nipper, section_obs, rate_none, nipper->loggingIssue, nipper->tableNum);
	switch (nipper->loggingIssue)
	{
		case -1:
			output_parseText(report_logging_obs2, nipper, section_none, rate_none, nipper->loggingIssue, nipper->tableNum);
			break;
		case 1:
			output_parseText(report_logging_obs3, nipper, section_none, rate_none, nipper->loggingIssue, nipper->tableNum);
			break;
		case 2:
			output_parseText(report_logging_obs4, nipper, section_none, rate_none, nipper->loggingIssue, nipper->tableNum);
			break;
		case 3:
			output_parseText(report_logging_obs5, nipper, section_none, rate_none, nipper->loggingIssue, nipper->tableNum);
			break;
		case 4:
			output_parseText(report_logging_obs6, nipper, section_none, rate_none, nipper->loggingIssue, nipper->tableNum);
			break;
	}
	output_endsection(nipper, section_obs);
	output_parseText(report_logging_impact, nipper, section_imp, rate_med, nipper->loggingIssue, nipper->tableNum);
	output_endsection(nipper, section_imp);
	output_parseText(report_logging_ease, nipper, section_ease, rate_noease, nipper->loggingIssue, nipper->tableNum);
	output_endsection(nipper, section_ease);
	output_parseText(report_logging_rec1, nipper, section_rec, rate_none, nipper->loggingIssue, nipper->tableNum);
	if (nipper->loggingIssue != 4)
		output_parseText(report_logging_rec2, nipper, section_none, rate_none, nipper->loggingIssue, nipper->tableNum);
	if ((nipper->versionMajor < 12) || ((nipper->versionMajor == 12) && (nipper->versionMinor < 1)))
		output_parseText(report_logging_rec3, nipper, section_none, rate_none, nipper->loggingIssue, nipper->tableNum);
	if (nipper->loggingIssue != 3)
		output_parseText(report_logging_rec4, nipper, section_none, rate_none, nipper->loggingIssue, nipper->tableNum);
	output_endsection(nipper, section_rec);
}


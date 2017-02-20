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

void iosTimeoutIssue(struct nipperConfig *nipper)
{
	// Variables...
	struct lineConfig *linePointer = 0;
	int tempInt = 0;
	char tempString[nipper->maxSize];

	output_parseText(report_timeout_obs1, nipper, section_obs, rate_none, nipper->insecureTimeouts, nipper->tableNum);
	if ((nipper->connectionTimeout % 60) == 0)
	{
		numToWord(nipper->reportFile, (nipper->connectionTimeout / 60));
		fprintf(nipper->reportFile, " minutes");
	}
	else
	{
		numToWord(nipper->reportFile, nipper->connectionTimeout / 60);
		fprintf(nipper->reportFile, " minutes and ");
		numToWord(nipper->reportFile, nipper->connectionTimeout % 60);
		fprintf(nipper->reportFile, " seconds");
	}
	output_parseText(report_timeout_obs2, nipper, section_none, rate_none, nipper->insecureTimeouts, nipper->tableNum);
	linePointer = nipper->ios->line;
	if (nipper->insecureTimeouts > 1)
	{
		output_table(nipper, true, report_timeout_table, &report_timeout_heading);
		while (linePointer != 0)
		{
			if ((linePointer->login != login_disabled) && ((linePointer->timeout == 0) || (linePointer->timeout > nipper->connectionTimeout)) && ((linePointer->absoluteTimeout == 0) || (linePointer->absoluteTimeout > nipper->connectionTimeout)) && ((linePointer->sessionTimeout == 0) || (linePointer->sessionTimeout > nipper->connectionTimeout)) && ((linePointer->execTimeout == 0) || (linePointer->execTimeout > nipper->connectionTimeout)))
			{
				switch (linePointer->lineType)
				{
					case line_console:
						fprintf(nipper->reportFile, "%sConsole line", nipper->tablerow_start);
						break;
					case line_vty:
						fprintf(nipper->reportFile, "%sVTY line", nipper->tablerow_start);
						break;
					case line_tty:
						fprintf(nipper->reportFile, "%sTTY line", nipper->tablerow_start);
						break;
					case line_aux:
						fprintf(nipper->reportFile, "%sAuxiliary line", nipper->tablerow_start);
						break;
				}
				if (linePointer->lineNumberEnd == 0)
					fprintf(nipper->reportFile, " %d%s", linePointer->lineNumberStart, nipper->tablerow_mid);
				else
					fprintf(nipper->reportFile, "s %d to %d%s", linePointer->lineNumberStart, linePointer->lineNumberEnd, nipper->tablerow_mid);
				if ((linePointer->timeout == 0) && (linePointer->sessionTimeout == 0) && (linePointer->absoluteTimeout == 0) && (linePointer->execTimeout == 0))
					fprintf(nipper->reportFile, "No Timeout%s", nipper->tablerow_end);
				else
				{
					tempInt = 0;
					if (linePointer->timeout != 0)
					{
						if ((linePointer->timeout % 60) == 0)
							fprintf(nipper->reportFile, "Timeout: %d minutes", (linePointer->timeout / 60));
						else
							fprintf(nipper->reportFile, "Timeout: %d minutes and %d seconds", linePointer->timeout / 60, linePointer->timeout % 60);
						tempInt++;
					}
					if (linePointer->absoluteTimeout != 0)
					{
						if (tempInt > 0)
							fprintf(nipper->reportFile, ", ");
						if ((linePointer->absoluteTimeout % 60) == 0)
							fprintf(nipper->reportFile, "Absolute Timeout: %d minutes", (linePointer->absoluteTimeout / 60));
						else
							fprintf(nipper->reportFile, "Absolute Timeout: %d minutes and %d seconds", linePointer->absoluteTimeout / 60, linePointer->absoluteTimeout % 60);
						tempInt++;
					}
					if (linePointer->sessionTimeout != 0)
					{
						if (tempInt > 0)
							fprintf(nipper->reportFile, ", ");
						if ((linePointer->sessionTimeout % 60) == 0)
							fprintf(nipper->reportFile, "Session Timeout: %d minutes", (linePointer->sessionTimeout / 60));
						else
							fprintf(nipper->reportFile, "Session Timeout: %d minutes and %d seconds", linePointer->sessionTimeout / 60, linePointer->sessionTimeout % 60);
						tempInt++;
					}
					if (linePointer->execTimeout != 0)
					{
						if (tempInt > 0)
							fprintf(nipper->reportFile, ", ");
						if ((linePointer->execTimeout % 60) == 0)
							fprintf(nipper->reportFile, "Exec Timeout: %d minutes", (linePointer->execTimeout / 60));
						else
							fprintf(nipper->reportFile, "Exec Timeout: %d minutes and %d seconds", linePointer->execTimeout / 60, linePointer->execTimeout % 60);
						tempInt++;
					}
					fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
				}
			}
			linePointer = linePointer->next;
		}
		output_table(nipper, false, report_timeout_table, &report_timeout_heading);
	}
	else
	{
		while (linePointer != 0)
		{
			if ((linePointer->login != login_disabled) && ((linePointer->timeout == 0) || (linePointer->timeout > nipper->connectionTimeout)) && ((linePointer->absoluteTimeout == 0) || (linePointer->absoluteTimeout > nipper->connectionTimeout)) && ((linePointer->sessionTimeout == 0) || (linePointer->sessionTimeout > nipper->connectionTimeout)) && ((linePointer->execTimeout == 0) || (linePointer->execTimeout > nipper->connectionTimeout)))
			{
				switch (linePointer->lineType)
				{
					case line_console:
						sprintf(tempString, "*NOTEXTSTART*The console line");
						break;
					case line_vty:
						sprintf(tempString, "*NOTEXTSTART*The *ABBREV*VTY*-ABBREV* line");
						break;
					case line_tty:
						sprintf(tempString, "*NOTEXTSTART*The *ABBREV*TTY*-ABBVREV* line");
						break;
					case line_aux:
						sprintf(tempString, "*NOTEXTSTART*The auxiliary ine");
						break;
				}
				if (linePointer->lineNumberEnd == 0)
					sprintf(tempString, "%s %d", tempString, linePointer->lineNumberStart);
				else
					sprintf(tempString, "%ss %d to %d", tempString, linePointer->lineNumberStart, linePointer->lineNumberEnd);
				if ((linePointer->timeout == 0) && (linePointer->sessionTimeout == 0) && (linePointer->absoluteTimeout == 0) && (linePointer->execTimeout == 0))
					sprintf(tempString, "%s had no timeout.", tempString);
				else
				{
					sprintf(tempString, "%s ", tempString);
					tempInt = 0;
					if (linePointer->timeout != 0)
					{
						if ((linePointer->timeout % 60) == 0)
							sprintf(tempString, "%stimeout was %d minutes", tempString, (linePointer->timeout / 60));
						else
							sprintf(tempString, "%stimeout was %d minutes and %d seconds", tempString, linePointer->timeout / 60, linePointer->timeout % 60);
						tempInt++;
					}
					if (linePointer->absoluteTimeout != 0)
					{
						if (tempInt > 0)
							sprintf(tempString, "%s, ", tempString);
						if ((linePointer->absoluteTimeout % 60) == 0)
							sprintf(tempString, "%sabsolute timeout was %d minutes", tempString, (linePointer->absoluteTimeout / 60));
						else
							sprintf(tempString, "%sabsolute timeout was %d minutes and %d seconds", tempString, linePointer->absoluteTimeout / 60, linePointer->absoluteTimeout % 60);
						tempInt++;
					}
					if (linePointer->sessionTimeout != 0)
					{
						if (tempInt > 0)
							sprintf(tempString, "%s, ", tempString);
						if ((linePointer->sessionTimeout % 60) == 0)
							sprintf(tempString, "%ssession timeout was %d minutes", tempString, (linePointer->sessionTimeout / 60));
						else
							sprintf(tempString, "%ssession timeout was %d minutes and %d seconds", tempString, linePointer->sessionTimeout / 60, linePointer->sessionTimeout % 60);
						tempInt++;
					}
					if (linePointer->execTimeout != 0)
					{
						if (tempInt > 0)
							sprintf(tempString, "%s, ", tempString);
						if ((linePointer->execTimeout % 60) == 0)
							sprintf(tempString, "%sExec timeout was %d minutes", tempString, (linePointer->execTimeout / 60));
						else
							sprintf(tempString, "%sExec timeout was %d minutes and %d seconds", tempString, linePointer->execTimeout / 60, linePointer->execTimeout % 60);
						tempInt++;
					}
				}
			}
			linePointer = linePointer->next;
		}
		output_parseText(tempString, nipper, section_none, rate_none, 0, 0);
	}
	output_endsection(nipper, section_obs);
	output_parseText(report_timeout_impact, nipper, section_imp, rate_high, 0, 0);
	output_endsection(nipper, section_imp);
	output_parseText(report_timeout_ease, nipper, section_ease, rate_difficult, 0, 0);
	output_endsection(nipper, section_ease);
	output_parseText(report_timeout_rec1, nipper, section_rec, rate_none, 0, 0);
	if ((nipper->connectionTimeout % 60) == 0)
	{
		numToWord(nipper->reportFile, (nipper->connectionTimeout / 60));
		fprintf(nipper->reportFile, " minutes");
	}
	else
	{
		numToWord(nipper->reportFile, nipper->connectionTimeout / 60);
		fprintf(nipper->reportFile, " minutes and ");
		numToWord(nipper->reportFile, (nipper->connectionTimeout % 60));
		fprintf(nipper->reportFile, " seconds");
	}
	output_parseText(report_timeout_rec2, nipper, section_none, rate_none, 0, 0);
	output_endsection(nipper, section_rec);
}


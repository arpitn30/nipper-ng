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
 *      2. Any code that makes use of this library MUST display the        *
 *         returned text of the Nipper::getVersion() method. Since the     *
 *         text returned includes the version details and copyright of     *
 *         the library, the sugested place to show it would be with the    *
 *         callers "about program" information.                            *
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


#include "../globaldefs.h"
#include "report.h"


int Report::writeSecuritySection()
{
	// Variables...
	Device::securityIssueStruct *securityIssuePointer = device->securityReport;
	int errorCode = 0;

	if (securityIssuePointer != 0)
	{
		// Write section title...
		writeSectionTitle(securityIssuePointer->section, Report::securitySection);

		// Write security audit...
		while (securityIssuePointer != 0)
		{

			errorCode = writeSubSectionTitle(securityIssuePointer->section, securityIssuePointer->subsection, securityIssuePointer->title.c_str(), securityIssuePointer->reference.c_str(), Report::securitySection);
			if (errorCode != 0)
				return errorCode;	

			// Ratings...
			if (securityIssuePointer->position == 3)
			{
				switch (config->reportFormat)
				{
					case Config::HTML:
						fprintf(outFile, "<div class=\"ratings\">\n");
						fprintf(outFile, "<font class=\"overallrating\">Overall: ");
						switch (securityIssuePointer->overallRating)
						{
							case 10:
							case 9:
								writeText("*CRITICAL*");
								break;
							case 8:
							case 7:
								writeText("*HIGH*");
								break;
							case 6:
							case 5:
								writeText("*MEDIUM*");
								break;
							case 4:
							case 3:
								writeText("*LOW*");
								break;
							default:
								writeText("*INFORMATIONAL*");
								break;
						}
						fprintf(outFile, "</font><br>\nImpact: ");
						switch (securityIssuePointer->impactRating)
						{
							case 10:
							case 9:
								writeText("*CRITICAL*");
								break;
							case 8:
							case 7:
								writeText("*HIGH*");
								break;
							case 6:
							case 5:
								writeText("*MEDIUM*");
								break;
							case 4:
							case 3:
								writeText("*LOW*");
								break;
							default:
								writeText("*INFORMATIONAL*");
								break;
						}
						fprintf(outFile, "<br>\nEase: ");
						switch (securityIssuePointer->easeRating)
						{
							case 10:
							case 9:
								writeText("*TRIVIAL*");
								break;
							case 8:
							case 7:
							case 6:
								writeText("*EASY*");
								break;
							case 5:
							case 4:
							case 3:
								writeText("*MODERATE*");
								break;
							case 2:
							case 1:
								writeText("*CHALLENGING*");
								break;
							default:
								writeText("*NOTAPPLICABLE*");
								break;
						}
						fprintf(outFile, "<br>\nFix: ");
						switch (securityIssuePointer->fixRating)
						{
							case 10:
							case 9:
							case 8:
								writeText("*INVOLVED*");
								break;
							case 7:
							case 6:
							case 5:
							case 4:
								writeText("*PLANNED*");
								break;
							default:
								writeText("*QUICK*");
								break;
						}
						fprintf(outFile, "\n</div>\n");
						break;

					case Config::XML:
						fprintf(outFile, "   <rating overall=\"");
						switch (securityIssuePointer->overallRating)
						{
							case 10:
							case 9:
								fprintf(outFile, "CRITICAL");
								break;
							case 8:
							case 7:
								fprintf(outFile, "HIGH");
								break;
							case 6:
							case 5:
								fprintf(outFile, "MEDIUM");
								break;
							case 4:
							case 3:
								fprintf(outFile, "LOW");
								break;
							default:
								fprintf(outFile, "INFORMATIONAL");
								break;
						}
						fprintf(outFile, "\" impact=\"");
						switch (securityIssuePointer->impactRating)
						{
							case 10:
							case 9:
								fprintf(outFile, "CRITICAL");
								break;
							case 8:
							case 7:
								fprintf(outFile, "HIGH");
								break;
							case 6:
							case 5:
								fprintf(outFile, "MEDIUM");
								break;
							case 4:
							case 3:
								fprintf(outFile, "LOW");
								break;
							default:
								fprintf(outFile, "INFORMATIONAL");
								break;
						}
						fprintf(outFile, "\" ease=\"");
						switch (securityIssuePointer->easeRating)
						{
							case 10:
							case 9:
								fprintf(outFile, "TRIVIAL");
								break;
							case 8:
							case 7:
							case 6:
								fprintf(outFile, "EASY");
								break;
							case 5:
							case 4:
							case 3:
								fprintf(outFile, "MODERATE");
								break;
							case 2:
							case 1:
								fprintf(outFile, "CHALLENGING");
								break;
							default:
								fprintf(outFile, "NOTAPPLICABLE");
								break;
						}
						fprintf(outFile, "\" fix=\"");
						switch (securityIssuePointer->fixRating)
						{
							case 10:
							case 9:
							case 8:
								fprintf(outFile, "INVOLVED");
								break;
							case 7:
							case 6:
							case 5:
							case 4:
								fprintf(outFile, "PLANNED");
								break;
							default:
								fprintf(outFile, "QUICK");
								break;
						}
						fprintf(outFile, "\" />\n");
						break;

					default:
						break;
				}
			}

			// Finding...
			if (securityIssuePointer->position == 3)
			{
				switch (config->reportFormat)
				{
					case Config::HTML:
						fprintf(outFile, "<div class=\"finding\">\n<h5>%d.%d.1. Finding</h5>", securityIssuePointer->section, securityIssuePointer->subsection);
						break;
					case Config::XML:
						fprintf(outFile, "   <textsection type=\"finding\">\n");
						break;
					default:
						fprintf(outFile, "FINDING: ");
						break;
				}
			}
			errorCode = writeParagraph(securityIssuePointer->finding, securityIssuePointer->section, securityIssuePointer->subsection);
			if (errorCode != 0)
				return errorCode;

			// Impact...
			if (securityIssuePointer->position == 3)
			{
				switch (config->reportFormat)
				{
					case Config::HTML:
						fprintf(outFile, "</div>\n<div class=\"impact\">\n<h5>%d.%d.2. Impact</h5>", securityIssuePointer->section, securityIssuePointer->subsection);
						break;
					case Config::XML:
						fprintf(outFile, "   </textsection>\n   <textsection type=\"impact\">\n");
						break;
					default:
						fprintf(outFile, "IMPACT: ");
						break;
				}
			}
			errorCode = writeParagraph(securityIssuePointer->impact, securityIssuePointer->section, securityIssuePointer->subsection);
			if (errorCode != 0)
				return errorCode;

			// Ease...
			if (securityIssuePointer->position == 3)
			{
				switch (config->reportFormat)
				{
					case Config::HTML:
						fprintf(outFile, "</div>\n<div class=\"ease\">\n<h5>%d.%d.3. Ease</h5>", securityIssuePointer->section, securityIssuePointer->subsection);
						break;
					case Config::XML:
						fprintf(outFile, "   </textsection>\n   <textsection type=\"ease\">\n");
						break;
					default:
						fprintf(outFile, "Ease: ");
						break;
				}
			}
			errorCode = writeParagraph(securityIssuePointer->ease, securityIssuePointer->section, securityIssuePointer->subsection);
			if (errorCode != 0)
				return errorCode;

			// Recommendations...
			if (securityIssuePointer->position == 3)
			{
				switch (config->reportFormat)
				{
					case Config::HTML:
						fprintf(outFile, "</div>\n<div class=\"recommendation\">\n<h5>%d.%d.4. Recommendation</h5>", securityIssuePointer->section, securityIssuePointer->subsection);
						break;
					case Config::XML:
						fprintf(outFile, "   </textsection>\n   <textsection type=\"recommendation\">\n");
						break;
					default:
						fprintf(outFile, "Recommendation: ");
						break;
				}
			}
			errorCode = writeParagraph(securityIssuePointer->recommendation, securityIssuePointer->section, securityIssuePointer->subsection);
			if (errorCode != 0)
				return errorCode;
			if (securityIssuePointer->position == 3)
			{
				switch (config->reportFormat)
				{
					case Config::HTML:
						fprintf(outFile, "</div>\n");
						break;
					case Config::XML:
						fprintf(outFile, "   </textsection>\n");
						break;
					default:
						fprintf(outFile, " ");
						break;
				}
			}
			writeSubSectionEnd();
	
			securityIssuePointer = securityIssuePointer->next;
		}

		// Section End
		writeSectionEnd();
	}

	return errorCode;
}

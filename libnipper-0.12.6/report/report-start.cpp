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

// Includes...
#include "../globaldefs.h"
#include "../device/general/general.h"
#include "report.h"


// HTML Cascading Style Sheet
const char *builtinCSS = "* {margin: 0; padding: 0;}\n"
                         "body {font-size: 80%; margin: 10px; padding: 0px; font-family: Verdana, Helvetica, Arial, sans-serif; width: 760px; color: #333333;}\n"
                         "caption { caption-side : bottom; font-style : italic;}\n"
                         "h1 {font-size: 250%; margin-top: 10px;}\n"
                         "h2 {font-size: 200%; margin-top: 25px; margin-bottom: 0px; padding: 5px; background-color: #ECE3FD; border-top: 2px solid #BA9BD4; border-bottom: 1px solid #BA9BD4}\n"
                         "h3 {font-size: 150%; font-weight: normal; padding: 5px; background-color: #E8EDFD; margin-top: 10px; border-top: 2px solid #8080E4;}\n"
                         "h5 {font-size: 110%;}\n"
                         "p {margin-bottom: 15px; text-align: justify; }\n"
                         "div {margin-bottom: 0px; margin-top: 0px; text-align: justify; }\n"
                         "table {clear: left; border: solid 1px rgb(150,150,150); empty-cells: show; border-collapse: collapse; background-color: #F5F2FF; width: 100%; text-align: left; margin-bottom: 0px;}\n"
                         "tr.evenrow {background-color: #EDEBF8;}\n"
                         "th {background-color: rgb(150,150,150); color: #ffffff; vertical-align: top; padding: 2px;}\n"
                         "td {vertical-align: top; padding: 2px;}\n"
                         "ul {margin-left: 20px; margin-top: 0px; margin-bottom: 20px;}\n"
                         "div.ratings {float:right; width:150px; padding:7px; margin:3px; font-size:14px; font-family:arial,helvetica,sans-serif; color:black; background-color: #FDFFE2; border:1px solid #D5D274; vertical-align:top; }\n"
                         "font.critical {color: #CD0A3B; text-transform:uppercase; font-weight: bold;}\n"
                         "font.high {color: #E2A316; text-transform:uppercase; font-weight: bold;}\n"
                         "font.medium {color: #ECEC04; text-transform:uppercase; font-weight: bold;}\n"
                         "font.low {color: #9DCA02; text-transform:uppercase; font-weight: bold;}\n"
                         "font.informational {color: #41A300; text-transform:uppercase; font-weight: bold;}\n"
                         "font.trivial {color: #CD0A3B; text-transform:uppercase; font-weight: bold;}\n"
                         "font.easy {color: #E2A316; text-transform:uppercase; font-weight: bold;}\n"
                         "font.moderate {color: #ECEC04;text-transform:uppercase;  font-weight: bold;}\n"
                         "font.challenging {color: #9DCA02; text-transform:uppercase; font-weight: bold;}\n"
                         "font.notapplicable {color: #41A300; text-transform:uppercase; font-weight: bold;}\n"
                         "font.involved {color: #CD0A3B; text-transform:uppercase; font-weight: bold;}\n"
                         "font.planned {color: #ECEC04; text-transform:uppercase; font-weight: bold;}\n"
                         "font.quick {color: #41A300; text-transform:uppercase; font-weight: bold;}\n"
                         "font.overallrating {font-weight: bold; font-size:15px; padding-bottom: 5px; }\n"
                         "font.ratings {position: relative; left: 70px;}\n"
                         "#frontpage {height: 400px; background-color: #F3F3F3; border:1px solid #120E8A;}\n"
                         "div.companyname {color: #18026B; font-weight: bold; font-size: 250%; text-align: center;}\n"
                         "div.reporttitle {color: #2A2A2F; font-weight: bold; font-size: 200%; text-align: center; margin-top: 100px;}\n"
                         "div.reportdate {color: #2A2A2F; font-size: 150%; text-align: center; text-transform: uppercase}\n"
                         "#contents {margin-left: 50px;}\n"
                         "#tableindex {margin-left: 50px;}\n"
                         "pre.code {background-color: #F3F3F3; padding-top: 5px; padding-bottom: 5px; margin-top: 5px; margin-bottom: 15px; font-weight: bold;font-family: courier; font-size: 100%}\n"
                         ".cmduser {font-style: italic; font-weight: normal}\n";

// Write the start of the report. Certain report formats must start
// with certain structures...
int Report::writeReportStart()
{
	// Variables...
	FILE *cssFile = 0;
	char buffer[256];

	switch (config->reportFormat)
	{
		case Config::HTML:
			fprintf(outFile, "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">\n<html>\n <head>\n  <title>");
			writeText(reportTitle(), 0, false);
			fprintf(outFile, "</title>\n  <meta name=\"description\" content=\"%s\">\n  <meta name=\"author\" content=\"%s\">\n  <META http-equiv=\"Content-Style-Type\" content=\"text/css\">\n  <style type='text/css'>\n  <!--\n  ", reportTitle(), config->companyName);
			if (config->htmlStylesheet == 0)
				fprintf(outFile, "%s", builtinCSS);
			else
			{
				cssFile = fopen(config->htmlStylesheet, "r");
				// Read line
				while (feof(cssFile) == 0)
				{
					fgets(buffer, sizeof(buffer), cssFile);
					fprintf(outFile, "%s\n", buffer);
				}
				fclose(cssFile);
			}
			fprintf(outFile, "  --></style>\n </head>\n <body id=\"report\">\n");
			break;

		case Config::XML:
			fprintf(outFile, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<document title=\"");
			writeText(reportTitle(), 0, false);
			if (config->deviceName != 0)
			{
				fprintf(outFile, "\" device=\"");
				writeText(outputFriendly(config->deviceName), 0, false);
			}
			else if (device->general != 0)
			{
				fprintf(outFile, "\" device=\"");
				writeText(outputFriendly(device->general->hostname.c_str()), 0, false);
			}
			fprintf(outFile, "\" devicetype=\"");
			writeText(device->deviceMake, 0, false);
			if (config->deviceModel != 0)
			{
				fprintf(outFile, " ");
				writeText(config->deviceModel, 0, false);
				fprintf(outFile, " ");
			}
			else if (device->deviceModel != 0)
			{
				writeText(device->deviceModel, 0, false);
				fprintf(outFile, " ");
			}
			fprintf(outFile, "%s\" author=\"%s\">\n", device->deviceType, config->companyName);
			break;

		case Config::Latex:
			fprintf(outFile, "\\documentclass[%s]{%s}\n", config->latexPaper, config->latexDocumentClass);
			fprintf(outFile, "\\usepackage{fullpage}\n");
			fprintf(outFile, "\\usepackage{url}\n");
			fprintf(outFile, "\\author{%s}\n", outputFriendly(config->companyName));
			fprintf(outFile, "\\title{%s}\n", outputFriendly(reportTitle()));
			fprintf(outFile, "\\date{");
			writeText("*DATE*", 0, false);
			fprintf(outFile, "}\n\n\\begin{document}\n\n");
			break;

		default:
			break;
	}

	return 0;
}



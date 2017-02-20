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
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

#include "../../globaldefs.h"
#include "../errortext.h"
#include "../device.h"


int Device::openInput()
{
	// Variables...
	FILE *tempFile = 0;
	struct stat *fileStats = 0;

	// If input is SNMP...
	if ((config->snmpCommunity != 0) && (config->snmpAddress != 0))
	{ }

	// If input is stdin...
	else if (config->inputSource == 0)
	{
		inputFile = stdin;

		// Open file for output...
		tempFileName.assign(TEMP_DIR);
		tempFileName.append("delete-me-");
		tempFileName.append(intToString(rand()));
		tempFile = fopen(tempFileName.c_str(), "w");
		if (tempFile == NULL)
			return deviceerror_creatingtempfile;

		while (feof(inputFile) == 0)
			fputc(fgetc(inputFile), tempFile);

		// Close output file...
		fclose(tempFile);


		config->inputSource = (char *)tempFileName.c_str();
	}

	if (config->inputSource != 0)
	{

		// Check the file has some contents...
		fileStats = new (struct stat);
		memset(fileStats, 0, sizeof(struct stat));
		stat(config->inputSource, fileStats);
		if ((fileStats->st_mode & S_IFDIR) == S_IFDIR)
		{
			delete fileStats;
			return deviceerror_inputisadirectory;
		}
		if (fileStats->st_size == 0)
		{
			delete fileStats;
			return deviceerror_inputsizeiszero;
		}
		delete fileStats;

		// Open Input...
		inputFile = fopen(config->inputSource, "r");
		if (inputFile == NULL)
			return deviceerror_openingfile;
		setvbuf(inputFile, 0, _IONBF, 0);
	}
	else
		return deviceerror_noinput;

	return 0;
}


void Device::readLine(char *line, int lineSize)
{
	// Variables...
	int tempInt = 0;

	// Read a line
	fgets(line, lineSize, inputFile);

	// Clear the end-of-line stuff...
	tempInt = strlen(line) - 1;
	while ((tempInt >= 0) && ((line[tempInt] == '\r') || (line[tempInt] == '\n') || (line[tempInt] == ' ')))
	{
		line[tempInt] = 0;
		tempInt--;
	}
}

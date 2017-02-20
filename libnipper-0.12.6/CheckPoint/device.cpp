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

// Includes
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>
#include <cstdlib>

#include "../globaldefs.h"
#include "../device/errortext.h"
#include "device.h"
#include "../device/common/configline.h"
#include "general.h"
#include "filter.h"


CheckPointDevice::CheckPointDevice()
{
	deviceMake = "CheckPoint";
	deviceType = "CheckPoint-Based";
	deviceOS = "CheckPoint OS";

	supportConfigNetworkServices = false;

	isFirewall = true;
	policies = 0;

	general = new (CheckPointGeneral);
	filter = new (CheckPointFilter);
}


CheckPointDevice::~CheckPointDevice()
{
	// Variables...
	policyCollections *policyPointer = 0;

	delete general;
	delete filter;

	while (policies != 0)
	{
		policyPointer = policies->next;
		delete policies;
		policies = policyPointer;
	}
}


int CheckPointDevice::process()
{
	// Variables...
	policyCollections *policyPointer = 0;
	string configDirectory;
	string tempFilename;
	struct stat *fileStats = 0;
	int returnCode = 0;
	bool addedPolicies = false;

	/*
		CheckPoint files to process...

		Key:
			* tables.C - Contains a list of the other files...

		Objects:
			* objects_5_0.C
			* objects.C_41
			* objects.C

		Rules:
			* *.W files
			* rules.C

		Rules + Comments:
			* rulebases_5_0.fws
			* rulebases.fws

		Users:
			* fwauth.NDB
	*/

	// Check if input is a directory (required)...
	fileStats = new (struct stat);
	memset(fileStats, 0, sizeof(struct stat));
	stat(config->inputSource, fileStats);
	if ((fileStats->st_mode & S_IFMT) != S_IFDIR)
	{
		delete fileStats;
		return deviceerror_inputnotadirectory;
	}
	delete fileStats;

	// Add Directory slash if it does not already exist
	configDirectory.assign(config->inputSource);
#if !defined(__WIN32__)
	if (configDirectory.c_str()[configDirectory.length() - 1] != '/')
		configDirectory.append("/");
#else
	if (configDirectory.c_str()[configDirectory.length() - 1] != '\\')
		configDirectory.append("\\");
#endif

	// Process CheckPoint Object Files...
	tempFilename.assign(configDirectory);
	tempFilename.append("objects_5_0.C");
	config->inputSource = tempFilename.c_str();
	returnCode = openInput();
	if (returnCode != 0)
	{
		tempFilename.assign(configDirectory);
		tempFilename.append("objects.C_41");
		config->inputSource = tempFilename.c_str();
		returnCode = openInput();
		if (returnCode != 0)
		{
			tempFilename.assign(configDirectory);
			tempFilename.append("objects.C");
			config->inputSource = tempFilename.c_str();
			returnCode = openInput();
		}
	}
	if (returnCode != 0)
		return deviceerror_objectsfilenotfound;
	returnCode = processDevice();
	fclose(inputFile);
	if (returnCode != 0)
		return returnCode;

	// Process CheckPoint Rules Files...

	// Try policy collection first...
	policyPointer = policies;
	while (policyPointer != 0)
	{
		tempFilename.assign(configDirectory);
		tempFilename.append(policyPointer->policyName);
		tempFilename.append(".W");
		config->inputSource = tempFilename.c_str();
		returnCode = openInput();
		if (returnCode == 0)
		{
			returnCode = ((CheckPointFilter *)filter)->processWRulesDevice(this, policyPointer->policyName.c_str(), policyPointer->active);
			fclose(inputFile);
			addedPolicies = true;
		}
		policyPointer = policyPointer->next;
		returnCode = 0;
	}

	// If policies still have not been added...
	if (addedPolicies == false)
	{
		tempFilename.assign(configDirectory);
		tempFilename.append("rules.C");
		config->inputSource = tempFilename.c_str();
		returnCode = openInput();
		if (returnCode == 0)
		{
			returnCode = ((CheckPointFilter *)filter)->processRRulesDevice(this);
			fclose(inputFile);
		}
	}

	// Process CheckPoint Rules With Comments Files...
	tempFilename.assign(configDirectory);
	tempFilename.append("rulebases_5_0.fws");
	config->inputSource = tempFilename.c_str();
	returnCode = openInput();
	if (returnCode != 0)
	{
		tempFilename.assign(configDirectory);
		tempFilename.append("rulebases.fws");
		config->inputSource = tempFilename.c_str();
		returnCode = openInput();
	}
	if (returnCode == 0)
	{
		returnCode = ((CheckPointFilter *)filter)->processFRulesDevice(this);
		fclose(inputFile);
	}
	else
		returnCode = 0;

	// Process Users...

	// Post processing defaults...
	setPostCommonDefaults();

	// Post device specific processing defaults...
	setPostDefaults();

	return returnCode;
}


int CheckPointDevice::processDevice()
{
	// Variables...
	char line[1024];
	ConfigLine command;

	// The process device configuration file loop...
	while (feof(inputFile) == 0)
	{

		// Read a line from the config...
		readLine(line, sizeof(line));

		// Split it up into parts...
		command.setConfigLine(line);

		// Starting...
		if ((strcmp(command.part(0), "(") == 0) && (strcmp(command.part(1), ")") != 0))
		{
			if (config->reportFormat == Config::Debug)
				printf("%sConfig Content Starts Line:%s %s\n", config->COL_GREEN, config->COL_RESET, line);

			// The process device configuration file loop...
			while ((feof(inputFile) == 0) && (strcmp(command.part(0), ")") != 0))
			{

				// Read a line from the config...
				readLine(line, sizeof(line));

				// Split it up into parts...
				command.setConfigLine(line);

				// Network Objects Start...
				if (((strcmp(command.part(0), ":netobj") == 0) || (strcmp(command.part(0), ":network_objects") == 0)) && (strcmp(command.part(1), "()") != 0))
					filter->processDeviceConfig(this, &command, (char *)line, sizeof(line));

				// Services Start...
				else if (((strcmp(command.part(0), ":servobj") == 0) || (strcmp(command.part(0), ":services") == 0)) && (strcmp(command.part(1), "()") != 0))
					filter->processDeviceConfig(this, &command, (char *)&line, sizeof(line));

				// Policy Collections...
				else if ((strcmp(command.part(0), ":policies_collections") == 0) && (strcmp(command.part(1), "()") != 0))
					processPolicyCollections(&command, (char *)&line, sizeof(line));

				// Unknown CheckPoint Structure...
				else if ((strncmp(command.part(0), ":", 1) == 0) && (strcmp(command.part(1), "()") != 0) && (command.part(1)[0] == '('))
					processUnknownCheckPointConfig(&command, (char *)&line, sizeof(line));

				// All others...
				else if (command.part(0)[0] != ')')
					lineNotProcessed(line);
			}

			// Ending...
			if (strcmp(command.part(0), ")") == 0)
			{
				if (config->reportFormat == Config::Debug)
					printf("%sConfig Content Ends Line:%s %s\n", config->COL_GREEN, config->COL_RESET, line);

				command.setConfigLine((char *)"");
			}
		}

		// Unknown CheckPoint Structure...
		else if ((strncmp(command.part(0), ":", 1) == 0) && (strcmp(command.part(1), "()") != 0) && (command.part(1)[0] == '('))
			processUnknownCheckPointConfig(&command, (char *)&line, sizeof(line));

		// All others...
		else
			lineNotProcessed(line);
	}

	return 0;
}


int CheckPointDevice::processUnknownCheckPointConfig(ConfigLine *command, char *line, int lineSize)
{
	lineNotProcessed(line);

	while ((feof(inputFile) == 0) && (strcmp(command->part(0), ")") != 0))
	{
		// Read a line from the config...
		readLine(line, lineSize);

		// Split it up into parts...
		command->setConfigLine(line);

		if ((strncmp(command->part(0), ":", 1) == 0) && (strncmp(command->part(1), "(", 1) == 0) && (command->part(command->parts - 1)[strlen(command->part(command->parts - 1)) - 1] != ')'))
			processUnknownCheckPointConfig(command, line, lineSize);

		// All others...
		else
			lineNotProcessed(line);
	}

	command->setConfigLine((char *)"");

	return 0;
}


bool CheckPointDevice::isDeviceType()
{
	// Variables...
	string configDirectory;
	string tempFilename;
	struct stat *fileStats = 0;

	// Check if input is a directory (required)...
	fileStats = new (struct stat);
	memset(fileStats, 0, sizeof(struct stat));
	stat(config->inputSource, fileStats);
	if ((fileStats->st_mode & S_IFMT) != S_IFDIR)
	{
		delete fileStats;
		return false;
	}
	delete fileStats;

	// Add Directory slash if it does not already exist
	configDirectory.assign(config->inputSource);
#if !defined(__WIN32__)
	if (configDirectory.c_str()[configDirectory.length() - 1] != '/')
		configDirectory.append("/");
#else
	if (configDirectory.c_str()[configDirectory.length() - 1] != '\\')
		configDirectory.append("\\");
#endif

	// Process CheckPoint Object Files...
	tempFilename.assign(configDirectory);
	tempFilename.append("objects_5_0.C");
	fileStats = new (struct stat);
	memset(fileStats, 0, sizeof(struct stat));
	stat(tempFilename.c_str(), fileStats);
	if ((fileStats->st_mode & S_IFMT) != S_IFDIR)
	{
		delete fileStats;
		return true;
	}
	delete fileStats;
	tempFilename.assign(configDirectory);
	tempFilename.append("objects.C_41");
	fileStats = new (struct stat);
	memset(fileStats, 0, sizeof(struct stat));
	stat(tempFilename.c_str(), fileStats);
	if ((fileStats->st_mode & S_IFMT) != S_IFDIR)
	{
		delete fileStats;
		return true;
	}
	delete fileStats;
	tempFilename.assign(configDirectory);
	tempFilename.append("objects.C");
	fileStats = new (struct stat);
	memset(fileStats, 0, sizeof(struct stat));
	stat(tempFilename.c_str(), fileStats);
	if ((fileStats->st_mode & S_IFMT) != S_IFDIR)
	{
		delete fileStats;
		return true;
	}
	delete fileStats;

	// Process Rules Files...
	tempFilename.assign(configDirectory);
	tempFilename.append("rules.C");
	fileStats = new (struct stat);
	memset(fileStats, 0, sizeof(struct stat));
	stat(tempFilename.c_str(), fileStats);
	if ((fileStats->st_mode & S_IFMT) != S_IFDIR)
	{
		delete fileStats;
		return true;
	}
	delete fileStats;
	tempFilename.assign(configDirectory);
	tempFilename.append("rulebases_5_0.fws");
	fileStats = new (struct stat);
	memset(fileStats, 0, sizeof(struct stat));
	stat(tempFilename.c_str(), fileStats);
	if ((fileStats->st_mode & S_IFMT) != S_IFDIR)
	{
		delete fileStats;
		return true;
	}
	delete fileStats;
	tempFilename.assign(configDirectory);
	tempFilename.append("rulebases.fws");
	fileStats = new (struct stat);
	memset(fileStats, 0, sizeof(struct stat));
	stat(tempFilename.c_str(), fileStats);
	if ((fileStats->st_mode & S_IFMT) != S_IFDIR)
	{
		delete fileStats;
		return true;
	}
	delete fileStats;

	return false;
}



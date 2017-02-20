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


// Colour Console Output...
#if !defined(__WIN32__)
const char *RESET = "[0m";			// DEFAULT
const char *COL_RED = "[31m";		// RED
const char *COL_BLUE = "[34m";		// BLUE
const char *COL_GREEN = "[32m";	// GREEN
#else
const char *RESET = "";
const char *COL_RED = "";
const char *COL_BLUE = "";
const char *COL_GREEN = "";
#endif


// Temporary Directory...
#if !defined(__WIN32__)
const char *tmpDir = "/tmp/";
#else
const char *tmpDir = "";
#endif


// Read a line from the input...
void readLine(FILE *input, char *lineFromFile, int maxLength)
{
	// Variables...
	int stripPointer = 0;

	// Read line from file...
	memset(lineFromFile, 0, maxLength);
	fgets(lineFromFile, maxLength, input);

	// Clear the end-of-line stuff...
	stripPointer = strlen(lineFromFile) -1;
	while ((lineFromFile[stripPointer] == '\r') || (lineFromFile[stripPointer] == '\n') || (lineFromFile[stripPointer] == ' '))
	{
		lineFromFile[stripPointer] = 0;
		stripPointer--;
	}
}


// Checks for simple passwords
int simplePassword(char *password, struct nipperConfig *nipper)
{
	// Constants
	const char passwords[][12] = {"password", "password1", "public", "private", "admin", "cisco", "default", "secret", "juniper",
                                 "dbsnmp", "laflaf", "ILMI", "cascade", "cable-docsis", "MiniAP", "snmp-trap", "volition",
                                 "super", "master", "netscreen", "ro", "rw",
                                 ""};
	// Variables
	int loop = 0;
	char line[128];

	if ((nipper->dictFile == 0) && (nipper->dictionaryFile != 0))
		nipper->dictFile = fopen(nipper->dictionaryFile, "r");


	// Check using a Dictionary File...
	if (nipper->dictFile != 0)
	{
		// Set the dictionary at the start
		rewind(nipper->dictFile);

		// Go through the dict until a match or eof
		while (feof(nipper->dictFile) == 0)
		{
			// Read line
			readLine(nipper->dictFile, line, sizeof(line));

			if (strcmp(password, line) == 0)
				return true;
		}
	}

	// Check using the small built-in dictionary
	else
	{
		for (loop = 0; passwords[loop][0] != 0; loop++)
		{
			if (strcasecmp(password, passwords[loop]) == 0)
				return true;
		}
	}

	return false;
}


// Checks password strength
int passwordStrength(char *password, struct nipperConfig *nipper)
{
	// Variables
	int contUpper = false;
	int contLower = false;
	int contUpperOrLower = false;
	int contNumber = false;
	int contSpecial = false;
	int loop = 0;

	// Check length first
	if (strlen(password) < nipper->passwordLength)
		return false;

	// Get password components
	for (loop = 0; loop < strlen(password); loop++)
	{
		// check for lowercase
		if ((password[loop] > 96) && (password[loop] < 123))
		{
			contLower = true;
			contUpperOrLower = true;
		}

		// check for upper
		else if ((password[loop] > 64) && (password[loop] < 91))
		{
			contUpper = true;
			contUpperOrLower = true;
		}

		// check for number
		else if ((password[loop] > 47) && (password[loop] < 58))
			contNumber = true;

		// check for special chars
		else
			contSpecial = true;
	}

	// Check password components
	if ((nipper->passwordLowers == true) && (contLower == false))
		return false;

	if ((nipper->passwordUppers == true) && (contUpper == false))
		return false;

	if ((nipper->passwordEither == true) && (contUpperOrLower == false))
		return false;

	if ((nipper->passwordNumbers == true) && (contNumber == false))
		return false;

	if ((nipper->passwordSpecials == true) && (contSpecial == false))
		return false;

	return true;
}


// Return how many chars to next space character (or end of string)
int nextSpace(char *line)
{
	// Variables...
	int counter = 0;

	// The work...
	while ((line[counter] != ' ') && (line[counter] != 0))
	{
		counter++;
	}

	// Return...
	return counter;
}


// Make text Latex friendly
void stripQuotes(char *line, char *output, int maxSize)
{
	// Variables
	int loop = 0;
	int outPos = 0;

	// Init
	if (strlen(line) < maxSize)
		maxSize = strlen(line) + 1;

	// Check each character
	for (loop = 0; (loop < strlen(line)) && (loop < maxSize -1); loop++)
	{
		// If it contains one of the chars
		if (line[loop] != '\"')
		{
			// Copy
			output[outPos] = line[loop];
			outPos++;
		}
	}

	// Null terminate
	output[outPos] = 0;
}


// Make text Latex friendly
void latexFriendly(char *line, char *output, int maxSize)
{
	// Variables
	int loop = 0;
	int outPos = 0;

	// Init
	if (strlen(line) < maxSize)
		maxSize = strlen(line) + 1;

	// Check each character
	for (loop = 0; (loop < strlen(line)) && (loop < maxSize -1); loop++)
	{
		// If it contains one of the chars
		if ((line[loop] == '_') || (line[loop] == '$') || (line[loop] == '#') || (line[loop] == '&') || (line[loop] == '\\') || (line[loop] == '%'))
		{
			output[outPos] = '\\';
			outPos++;
		}

		// Copy
		output[outPos] = line[loop];

		// Increment
		outPos++;
	}

	// Null terminate
	output[outPos] = 0;
}


// Make text HTML friendly
void htmlFriendly(char *line, char *output, int maxSize)
{
	// Variables
	int loop = 0;
	int outPos = 0;

	// Init
	if (strlen(line) < maxSize)
		maxSize = strlen(line) + 1;

	// Check each character
	for (loop = 0; (loop < strlen(line)) && (loop < maxSize -1); loop++)
	{
		// If it contains one of the chars
		if (line[loop] == '<')
		{
			output[outPos] = '&';
			outPos++;
			output[outPos] = 'l';
			outPos++;
			output[outPos] = 't';
			outPos++;
			output[outPos] = ';';
			outPos++;
		}
		else if (line[loop] == '>')
		{
			output[outPos] = '&';
			outPos++;
			output[outPos] = 'g';
			outPos++;
			output[outPos] = 't';
			outPos++;
			output[outPos] = ';';
			outPos++;
		}
		else if (line[loop] == '&')
		{
			output[outPos] = '&';
			outPos++;
			output[outPos] = 'a';
			outPos++;
			output[outPos] = 'm';
			outPos++;
			output[outPos] = 'p';
			outPos++;
			output[outPos] = ';';
			outPos++;
		}

		// Copy
		else
		{
			output[outPos] = line[loop];
			outPos++;
		}
	}

	// Null terminate
	output[outPos] = 0;
}


// Break line up into its parts
struct ciscoCommand splitLine(char *line)
{
	// Variables
	int tempInt = 0;
	int offset = 0;
	int commandCount = -1;
	int quotes = false;
	struct ciscoCommand command;

	// Init
	memset(&command, 0, sizeof(struct ciscoCommand));

	// Process the line
	while ((line[tempInt] != 0) && (commandCount < 40))
	{
		// If the character is a space or a tab
		if (((line[tempInt] == 9) || (line[tempInt] == ' ')) && (quotes == false))
		{
			offset = 0;
		}

		// If the character is not a space/tab or quotes are open
		else
		{
			// Increment part counter
			if (offset == 0)
				commandCount = commandCount + 1;

			// If quote
			if ((quotes == true) && (line[tempInt] == '"'))
				quotes = false;
			else if (line[tempInt] == '"')
				quotes = true;

			// copy stuff
			if (offset < sizeof(command.part[commandCount]) - 1)
			{
				command.part[commandCount][offset] = line[tempInt];
				offset = offset + 1;
				command.part[commandCount][offset] = 0;
			}
		}
		tempInt++;
	}

	// return
	command.parts = commandCount + 1;
	return command;
}


// Add a password to the john the ripper list
void addJohnPassword(struct nipperConfig *nipper, char *username, char *password)
{
	// struct
	struct johnPassword *johnPointer;
	johnPointer = malloc(sizeof(struct johnPassword));
	memset(johnPointer, 0, sizeof(struct johnPassword));

	// Sort out pointers
	johnPointer->next = nipper->john;
	nipper->john = johnPointer;

	// Copy strings
	strncpy(johnPointer->username, username, sizeof(johnPointer->username) - 1);
	strncpy(johnPointer->password, password, sizeof(johnPointer->password) - 1);
}


// Decrypt the Cisco password-7 password
int password7(char *password, char *decoded, int size, int debug)
{
	// Declarations...
	const char xlat[] = {
		0x64, 0x73, 0x66, 0x64, 0x3b, 0x6b, 0x66, 0x6f,
		0x41, 0x2c, 0x2e, 0x69, 0x79, 0x65, 0x77, 0x72,
		0x6b, 0x6c, 0x64, 0x4a, 0x4b, 0x44, 0x48, 0x53,
		0x55, 0x42, 0x73, 0x67, 0x76, 0x63, 0x61, 0x36,
		0x39, 0x38, 0x33, 0x34, 0x6e, 0x63, 0x78, 0x76,
		0x39, 0x38, 0x37, 0x33, 0x32, 0x35, 0x34, 0x6b,
		0x3b, 0x66, 0x67, 0x38, 0x37, 0x64, 0x73, 0x66,
		0x64, 0x3b, 0x6b, 0x66, 0x6f, 0x41, 0x2c, 0x2e,
		0x69, 0x79, 0x65, 0x77, 0x72, 0x6b, 0x6c, 0x64,
		0x4a, 0x4b, 0x44, 0x48, 0x53, 0x55, 0x42, 0x73,
		0x67, 0x76, 0x63, 0x61, 0x36, 0x39, 0x38, 0x33,
		0x34, 0x6e, 0x63, 0x78, 0x76, 0x39, 0x38, 0x37,
		0x33, 0x32, 0x35, 0x34, 0x6b, 0x3b, 0x66, 0x67,
		0x38, 0x37};
	unsigned int seed = 0;
	unsigned int i = 0;
	unsigned int val = 0;

	// Output debug information?
	if (debug == true)
	{
		int loop;
		printf("  Type-7 Std: %s\n", password);
		printf("  Type-7 Hex: ");
		for (loop = 0; loop < strlen(password); loop++)
		{
			printf("%x ", password[loop]);
		}
		printf("\n");
	}

	if ((strlen(password) & 1) || (strlen(password) > size * 2))
		return(-1);

	seed = (password[0] - '0') * 10 + password[1] - '0';

	if (seed > 15 || !isdigit(password[0]) || !isdigit(password[1]))
		return(-1);

	for (i = 2 ; i <= strlen(password); i++)
	{
		if (i !=2 && !(i & 1))
		{
			decoded[i / 2 - 2] = val ^ xlat[seed++];
			val = 0;
		}
		val *= 16;

		if (isdigit(password[i] = toupper(password[i])))
		{
			val += password[i] - '0';
			continue;
		}

		if (password[i] >= 'A' && password[i] <= 'F')
		{
			val += password[i] - 'A' + 10;
			continue;
		}

		if (strlen(password) != i)
			return(-1);
	}

	decoded[++i / 2] = 0;
	return(0);
}


// Output text title
void printTextTitle(FILE *reportFile, const char *title)
{
	// Variables...
	int loop = 0;

	// Output Title...
	fprintf(reportFile, "%s\n", title);

	// Output underlining...
	for (loop = 0; loop < strlen(title); loop++)
	{
		fprintf(reportFile, "-");
	}
	fprintf(reportFile, "\n\n");
}


// Output numbers as words...
void numToWord(FILE *reportFile, int value)
{
	switch (value)
	{
		case 1:
			fprintf(reportFile, "one");
			break;
		case 2:
			fprintf(reportFile, "two");
			break;
		case 3:
			fprintf(reportFile, "three");
			break;
		case 4:
			fprintf(reportFile, "four");
			break;
		case 5:
			fprintf(reportFile, "five");
			break;
		case 6:
			fprintf(reportFile, "six");
			break;
		case 7:
			fprintf(reportFile, "seven");
			break;
		case 8:
			fprintf(reportFile, "eight");
			break;
		case 9:
			fprintf(reportFile, "nine");
			break;
		case 10:
			fprintf(reportFile, "ten");
			break;
		case 11:
			fprintf(reportFile, "eleven");
			break;
		case 12:
			fprintf(reportFile, "twelve");
			break;
		case 13:
			fprintf(reportFile, "thirteen");
			break;
		case 14:
			fprintf(reportFile, "fourteen");
			break;
		default:
			fprintf(reportFile, "%d", value);
			break;
	}
}


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


// Static NAT/PAT Structure
struct staticPIX
{
	char interfaceReal[32];				// Real Interface
	char interfaceMapped[32];			// Mapped Interface
	int protocolTcp;					// TCP = true, UDP = false (PAT ONLY)
	char ipMapped[64];					// Mapped IP
	char portMapped[10];				// Mapped Port (PAT ONLY)
	char ipReal[64];					// NAT type: Real IP Address NAT
	char portReal[10];
	char ipNetMaskReal[16];				//
	char accessList[32];				//           Access List NAT
	int interface;						//           Interface NAT
	int dns;							// Rewrite DNS records
	int nailed;							// Nailed will allow incoming connections
	int randomseq;						// Random Sequence no.'s
	int tcpMaxConnections;				// Maximum TCP connections
	int udpMaxConnections;				// Maximum UDP connections
	int embrionicConnections;			// Limit Embionic Connections (DoS protection)
	struct staticPIX *next;
};


// Seperate out the mapped and real interfaces
void seperateMapped(char *joined, char *real, int realSize, char *mapped, int mappedSize)
{
	// Variables
	int tempInt = 1;
	int tempInt2 = 0;

	// Copy real
	while ((joined[tempInt] != ',') && (tempInt < realSize))
	{
		real[tempInt - 1] = joined[tempInt];
		tempInt++;
	}

	tempInt++;

	// Copy Mapped
	while ((joined[tempInt] != ')') && (tempInt2 < mappedSize - 1))
	{
		mapped[tempInt2] = joined[tempInt];
		tempInt++;
		tempInt2++;
	}
}


// Process static NAT / PAT
void processStaticPIX(char *line, struct nipperConfig *nipper)
{
	// Variables...
	struct ciscoCommand command;
	struct staticPIX *staticPIXPointer = 0;
	int tempInt = 0;

	// Init
	command = splitLine(line);

	// NAT
	if ((strcmp(command.part[2], "tcp") != 0) && (strcmp(command.part[2], "udp") != 0))
	{
		// Debug
		if (nipper->debugMode == true)
		{
			printf("Static NAT Line: %s\n", line);
		}

		// if first
		if (nipper->pix->staticNAT == 0)
		{
			nipper->pix->staticNAT = malloc(sizeof(struct staticPIX));
			staticPIXPointer = nipper->pix->staticNAT;
		}
		else
		{
			staticPIXPointer = nipper->pix->staticNAT;
			while (staticPIXPointer->next != 0)
				staticPIXPointer = staticPIXPointer->next;
			staticPIXPointer->next = malloc(sizeof(struct staticPIX));
			staticPIXPointer = staticPIXPointer->next;
		}

		// Init
		memset(staticPIXPointer, 0, sizeof(struct staticPIX));
		staticPIXPointer->interface = false;
		staticPIXPointer->dns = false;
		staticPIXPointer->nailed = false;
		staticPIXPointer->randomseq = true;

		// Seperate Real and Mapped
		seperateMapped(command.part[1], staticPIXPointer->interfaceReal, sizeof(staticPIXPointer->interfaceReal), staticPIXPointer->interfaceMapped, sizeof(staticPIXPointer->interfaceMapped));

		// Mapped IP Address
		strncpy(staticPIXPointer->ipMapped, command.part[2], sizeof(staticPIXPointer->ipMapped) - 1);

		// Is it Interface NAT?
		if (strcmp(command.part[3], "interface") == 0)
		{
			staticPIXPointer->interface = true;
			tempInt = 4;
		}

		// Is it Access List NAT?
		else if (strcmp(command.part[3], "access-list") == 0)
		{
			strncpy(staticPIXPointer->accessList, command.part[4], sizeof(staticPIXPointer->accessList) - 1);
			tempInt = 5;
		}

		// Or a IP address NAT?
		else
		{
			strncpy(staticPIXPointer->ipReal, command.part[3], sizeof(staticPIXPointer->ipReal) - 1);
			tempInt = 4;

			// Is there a netmask?
			if (command.parts > 4)
			{
				if (strcmp(command.part[4], "netmask") == 0)
				{
					strncpy(staticPIXPointer->ipNetMaskReal, command.part[5], sizeof(staticPIXPointer->ipNetMaskReal) - 1);
					tempInt = 6;
				}
			}
		}

		// Get options
		while (tempInt < command.parts)
		{
			// DNS A record update
			if (strcmp(command.part[tempInt], "dns") == 0)
				staticPIXPointer->dns = true;

			// Limit TCP Connections
			else if (strcmp(command.part[tempInt], "tcp") == 0)
			{
				staticPIXPointer->tcpMaxConnections = atoi(command.part[tempInt + 1]);
				tempInt++;
				// Check for embrionic option
				if ((strcmp(command.part[tempInt], "udp") != 0) && (strcmp(command.part[tempInt], "norandomseq") != 0))
				{
					staticPIXPointer->tcpMaxConnections = atoi(command.part[tempInt + 1]);
					tempInt++;
				}
			}

			// Limit UDP Connections
			else if (strcmp(command.part[tempInt], "udp") == 0)
			{
				staticPIXPointer->embrionicConnections = atoi(command.part[tempInt + 1]);
				tempInt++;
			}

			// No Random Sequence Numbers
			else if (strcmp(command.part[tempInt], "norandomseq") == 0)
			{
				staticPIXPointer->randomseq = false;
				if (strcmp(command.part[tempInt+1], "nailed") == 0)
				{
					staticPIXPointer->nailed = true;
					tempInt++;
				}
			}

			tempInt++;
		}
	}

	// Static PAT
	else
	{
		// Debug
		if (nipper->debugMode == true)
		{
			printf("Static PAT Line: %s\n", line);
		}

		// if first
		if (nipper->pix->staticPAT == 0)
		{
			nipper->pix->staticPAT = malloc(sizeof(struct staticPIX));
			staticPIXPointer = nipper->pix->staticPAT;
		}
		else
		{
			staticPIXPointer = nipper->pix->staticPAT;
			while (staticPIXPointer->next != 0)
				staticPIXPointer = staticPIXPointer->next;
			staticPIXPointer->next = malloc(sizeof(struct staticPIX));
			staticPIXPointer = staticPIXPointer->next;
		}

		// Init
		memset(staticPIXPointer, 0, sizeof(struct staticPIX));
		staticPIXPointer->interface = false;
		staticPIXPointer->dns = false;
		staticPIXPointer->nailed = false;
		staticPIXPointer->randomseq = true;

		// Seperate Real and Mapped
		seperateMapped(command.part[1], staticPIXPointer->interfaceReal, sizeof(staticPIXPointer->interfaceReal), staticPIXPointer->interfaceMapped, sizeof(staticPIXPointer->interfaceMapped));

		if (strcmp(command.part[2], "tcp") == 0)
			staticPIXPointer->protocolTcp = true;
		else
			staticPIXPointer->protocolTcp = false;

		// Mapped IP Address
		strncpy(staticPIXPointer->ipMapped, command.part[3], sizeof(staticPIXPointer->ipMapped) - 1);

		// Mapped Port
		strncpy(staticPIXPointer->portMapped, command.part[4], sizeof(staticPIXPointer->portMapped) - 1);

		// Is it Interface NAT?
		if (strcmp(command.part[5], "interface") == 0)
		{
			staticPIXPointer->interface = true;
			tempInt = 6;
		}

		// Is it Access List NAT?
		else if (strcmp(command.part[5], "access-list") == 0)
		{
			strncpy(staticPIXPointer->accessList, command.part[6], sizeof(staticPIXPointer->accessList) - 1);
			tempInt = 7;
		}

		// Or a IP address NAT?
		else
		{
			strncpy(staticPIXPointer->ipReal, command.part[5], sizeof(staticPIXPointer->ipReal) - 1);
			tempInt = 7;

			// Real Port
			strncpy(staticPIXPointer->portReal, command.part[6], sizeof(staticPIXPointer->portReal) - 1);

			// Is there a netmask?
			if (command.parts > 7)
			{
				if (strcmp(command.part[7], "netmask") == 0)
				{
					strncpy(staticPIXPointer->ipNetMaskReal, command.part[8], sizeof(staticPIXPointer->ipNetMaskReal) - 1);
					tempInt = 9;
				}
			}
		}

		// Get options
		while (tempInt < command.parts)
		{
			// DNS A record update
			if (strcmp(command.part[tempInt], "dns") == 0)
				staticPIXPointer->dns = true;

			// Limit TCP Connections
			else if (strcmp(command.part[tempInt], "tcp") == 0)
			{
				staticPIXPointer->tcpMaxConnections = atoi(command.part[tempInt + 1]);
				tempInt++;
				// Check for embrionic option
				if ((strcmp(command.part[tempInt], "udp") != 0) && (strcmp(command.part[tempInt], "norandomseq") != 0))
				{
					staticPIXPointer->tcpMaxConnections = atoi(command.part[tempInt + 1]);
					tempInt++;
				}
			}

			// Limit UDP Connections
			else if (strcmp(command.part[tempInt], "udp") == 0)
			{
				staticPIXPointer->embrionicConnections = atoi(command.part[tempInt + 1]);
				tempInt++;
			}

			// No Random Sequence Numbers
			else if (strcmp(command.part[tempInt], "norandomseq") == 0)
			{
				staticPIXPointer->randomseq = false;
				if (strcmp(command.part[tempInt+1], "nailed") == 0)
				{
					staticPIXPointer->nailed = true;
					tempInt++;
				}
			}

			tempInt++;
		}
	}

}


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
#include "../../globaldefs.h"
#include "../device.h"
#include "banner.h"


Banner::Banner()
{
	banner = 0;

	// Banner settings...
	preLogonBanner = false;					// Support Banner(s) Before Logon?
	postLogonBanner = false;					// Support Banner(s) After Logon?
	configPreLogonBanner = i18n("");			// The text that explains how to config a prelogon banner, with commands...
	configPostLogonBanner = i18n("");			// The text that explains how to config a post logon banner, with commands...
}


Banner::~Banner()
{
	// Variables...
	bannerStruct *bannerPointer = 0;
	bannerTextStruct *bannerTextPointer = 0;

	// Delete banners...
	while (banner != 0)
	{
		while (banner->bannerText != 0)
		{
			bannerTextPointer = banner->bannerText->next;
			delete banner->bannerText;
			banner->bannerText = bannerTextPointer;
		}
		bannerPointer = banner->next;
		delete banner;
		banner = bannerPointer;
	}
}


Banner::bannerStruct *Banner::addBanner()												// Add a new banner...
{
	// Variables...
	bannerStruct *bannerPointer = 0;

	// Create...
	if (banner == 0)
	{
		banner = new (bannerStruct);
		bannerPointer = banner;
	}
	else
	{
		bannerPointer = banner;
		while (bannerPointer->next != 0)
			bannerPointer = bannerPointer->next;
		bannerPointer->next = new (bannerStruct);
		bannerPointer = bannerPointer->next;
	}

	// Init...
	bannerPointer->banner = preLogon;
	bannerPointer->enabled = true;
	bannerPointer->connectionType = anyConnection;
	bannerPointer->bannerText = 0;
	bannerPointer->leak = noInfoLeak;
	bannerPointer->noWarning = false;
	bannerPointer->bannerFile = false;					// The banner is a file
	bannerPointer->next = 0;

	return bannerPointer;
}


Banner::bannerStruct *Banner::getBanner(const char *name)
{
	// Variables...
	bannerStruct *bannerPointer = 0;
	bool found = false;

	bannerPointer = banner;
	while ((found == false) && (bannerPointer != 0))
	{
		if (bannerPointer->name.compare(name) == 0)
			found = true;
		else
			bannerPointer = bannerPointer->next;
	}

	return bannerPointer;
}


int Banner::addBannerLine(bannerStruct *bannerPointer, const char *line)		// Add a line to a banner...
{
	// Variables...
	bannerTextStruct *bannerTextPointer = 0;

	// Create...
	if (bannerPointer->bannerText == 0)
	{
		bannerPointer->bannerText = new (bannerTextStruct);
		bannerTextPointer = bannerPointer->bannerText;
	}
	else
	{
		bannerTextPointer = bannerPointer->bannerText;
		while (bannerTextPointer->next != 0)
			bannerTextPointer = bannerTextPointer->next;
		bannerTextPointer->next = new (bannerTextStruct);
		bannerTextPointer = bannerTextPointer->next;
	}

	// Init...
	bannerTextPointer->bannerLine.assign(line);
	bannerTextPointer->next = 0;

	return 0;
}


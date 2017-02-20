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

#ifndef ScreenOSFilter_H
#define ScreenOSFilter_H


#include "../device/filter/filter.h"


class ScreenOSFilter : public Filter
{
	public:
		ScreenOSFilter();
		~ScreenOSFilter();


	private:
		// Device specific methods...
		int processDeviceConfig(Device *device, ConfigLine *command, char *line, int lineSize);
		int processDeviceSpecificDefaults(Device *device);

		const char *intrazoneTitle;
		const char *intrazoneDescription;
		const char *interzoneTitle;
		const char *interzoneDescription;
		const char *globalzoneTitle;
		const char *globalzoneDescription;
		const char *addressObjectListTitle;
		const char *addressObjectListDescription;
		const char *serviceObjectTitle;
		const char *serviceObjectDescription;
		const char *serviceGroupObjectTitle;
		const char *serviceGroupObjectDescription;
		const char *addressGroupObjectTitle;
		const char *addressGroupObjectDescription;
		const char *predefinedObjectListTitle;
		const char *predefinedObjectListDescription;
};


#endif


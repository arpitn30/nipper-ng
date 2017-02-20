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


int Device::generateAppendixLoggingLevels()
{
	// Variables...
	configReportStruct *configPointer = 0;
	paragraphStruct *paragraphPointer = 0;
	int errorCode = 0;

	// Logging levels start...
	configPointer = getAppendixSection("APPENDIX-LOGGING");
	configPointer->title = i18n("Logging Severity Levels");
	paragraphPointer = addParagraph(configPointer);

	// The text...
	paragraphPointer->paragraph.assign(i18n("Logging message severity levels provide a way of tagging log messages with an indication of how significant the message is. Table *TABLEREF* lists the various standard logging severity levels that can be configured."));

	// Add table...
	errorCode = addTable(paragraphPointer, "APPENDIX-LOGGING-TABLE");
	if (errorCode != 0)
		return errorCode;
	paragraphPointer->table->title = i18n("Logging message severity levels");

	// Add table headings...
	addTableHeading(paragraphPointer->table, i18n("Level"), false);
	addTableHeading(paragraphPointer->table, i18n("Name"), false);
	addTableHeading(paragraphPointer->table, i18n("Description"), false);

	// Add table data...
	addTableData(paragraphPointer->table, "0");
	addTableData(paragraphPointer->table, i18n("Emergencies"));
	addTableData(paragraphPointer->table, i18n("The system is unusable."));
	addTableData(paragraphPointer->table, "1");
	addTableData(paragraphPointer->table, i18n("Alerts"));
	addTableData(paragraphPointer->table, i18n("Immediate action is required"));
	addTableData(paragraphPointer->table, "2");
	addTableData(paragraphPointer->table, i18n("Critical"));
	addTableData(paragraphPointer->table, i18n("Critical conditions"));
	addTableData(paragraphPointer->table, "3");
	addTableData(paragraphPointer->table, i18n("Errors"));
	addTableData(paragraphPointer->table, i18n("Error conditions"));
	addTableData(paragraphPointer->table, "4");
	addTableData(paragraphPointer->table, i18n("Warnings"));
	addTableData(paragraphPointer->table, i18n("Warning conditions"));
	addTableData(paragraphPointer->table, "5");
	addTableData(paragraphPointer->table, i18n("Notifications"));
	addTableData(paragraphPointer->table, i18n("Significant conditions"));
	addTableData(paragraphPointer->table, "6");
	addTableData(paragraphPointer->table, i18n("Informational"));
	addTableData(paragraphPointer->table, i18n("Informational messages"));
	addTableData(paragraphPointer->table, "7");
	addTableData(paragraphPointer->table, i18n("Debugging"));
	addTableData(paragraphPointer->table, i18n("Debugging messages"));

	return 0;
}

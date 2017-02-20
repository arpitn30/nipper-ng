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

#ifndef device_configline_H
#define device_configline_H

// Includes...
#include <string>

using namespace std;


class ConfigLine
{

  public:

	ConfigLine();
	virtual ~ConfigLine();

	/**
	 * This method sets the config file line to use when populating the data in this
	 * class.
	 *
	 * \param line   The config file line.
	 */
	virtual void setConfigLine(char *line);

	/**
	 * This method reads a line from the file and populates the data in this class.
	 *
	 * \param partNumber   Which part to return (counts from 1)
	 * \return             Returns a pointer to a string or an empty string if it
	 *                     does not exist.
	 */
	const char *part(int partNumber);

	/**
	 * The total number of parts in the config line
	 */
	int parts;


  private:
	struct ConfigLinePart
	{
		string part;
		struct ConfigLinePart *next;
	};
	struct ConfigLinePart *command;
	void deleteParts();
};


#endif

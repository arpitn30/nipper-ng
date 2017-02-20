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

#ifndef LIBNIPPER_REPORT_H
#define LIBNIPPER_REPORT_H

#include <cstdio>
#include "../device/device.h"

class Config;


class Report
{

	public:

	Config *config;
	Device *device;

	/**
	 * This method writes the report to the location specified in the Nipper
	 * configuration in the format specified.
	 *
	 * \return      It returns 0 on success, otherwise it indicates an
	 *              error of some kind. The error text can be retreived
	 *              using the Nipper::getErrorText method.
	 */
	int write();


	private:

	int writeReportStart();
	int writeFrontPage();
	int writeContentsPage();
	enum sectionEnumerator
	{
		contentsSection = 0,
		tableIndexSection = 1,
		introductionSection = 2,
		securitySection = 3,
		complianceSection = 4,
		configurationSection = 5,
		appendixSection = 6
	};
	void writeContentsSectionTitle(int sectionNumber, sectionEnumerator section);
	int writeContentsSubSectionTitle(int sectionNumber, int subSectionNumber, const char *title, const char *reference);
	int writeContentsTableIndex(int tableNumber, const char *title, const char *reference);
	int writeIntroductionPage();
	int writeSecuritySection();
	void writeComplianceSection();
	int writeConfigurationSection();
	int writeAppendixSection();
	void writeReportEnd();
	void writeSectionTitle(int sectionNumber, sectionEnumerator section);
	void writeSectionEnd();
	int writeSubSectionTitle(int sectionNumber, int subSectionNumber, const char *title, const char *reference, sectionEnumerator section);
	void writeSubSectionEnd();
	const char *reportTitle();
	const char *getReferenceNumber(const char *reference);
	const char *getStringListItem(Device::paragraphStruct *paragraph);

	/**
	 * This method writes a text to the report, with the relevent
	 * text formatting. It will look for specific text within the paragraph
	 * and replace it with report specific text. This text needs to be
	 * enclosed in *'s, the following are currently supported:
	 *
	 *   @li <b>ABBREV</b>^ Abbreviations.
	 *   @li <b>CODE</b>^ A code section.
	 *   @li <b>CODELINE</b>^ A line of code.
	 *   @li <b>COMMAND</b>^ A cli command.
	 *   @li <b>COMPANY</b> The company name used in the report, defaults to Nipper.
	 *   @li <b>CMDOPTION</b>^ Used to enclose command options.
	 *   @li <b>CMDOR</b> Used to show an alternative command option.
	 *   @li <b>CMDREQUIRE</b>^ Used to show required command information.
	 *   @li <b>CMDUSER</b>^ Used to show user supplied command information.
	 *   @li <b>DATA</b> Some data from the string list.
	 *   @li <b>DATE</b> The current date.
	 *   @li <b>DEVICENAME</b> The name of the device.
	 *   @li <b>DEVICEOS</b> The Operating System of the device.
	 *   @li <b>DEVICETYPE</b> The type of device, such as Cisco Router.
	 *   @li <b>DEVICEVERSION</b> The type of device software version, such as IOS 12.4.
	 *   @li <b>DEVICEVERSIONFULL</b> The type of device full software version, such as Cisco IOS 12.4.
	 *   @li <b>HOST</b> A host string, the value is in the string list.
	 *   @li <b>NUMBER</b> A number, the value is in the value list.
	 *   @li <b>PASSWORD</b> Used to insert a password (if passwords are enabled - from the string list).
	 *   @li <b>POWER</b>^ Used to show a number to the power of...
	 *   @li <b>SECTIONLINK</b>^ Used to link to another report section. The reference is stored in the string list.
	 *   @li <b>SECTIONNO</b> The reference is changed to a section.subsection. reference. The config/security/appendix reference is stored in the string list.
	 *   @li <b>TABLEREF</b> A table reference, and possibly link.
	 *   @li <b>URL</b>^ A link to a web site.
	 *
	 * The text formatting marked with a ^ require a start and an end. The end is
	 * the same as the start, but with a *- at the beginning.
	 *
	 * \param theText              The paragraph text string
	 * \param paragraph            A pointer to a paragraph
	 * \param expandAbbreviations  Expand an abbreviation. Usually true for paragraphs, not for table contents
	 * \param hideMarkup           Removes any markup from the output text, useful for resolving issues where
	 *                             you dont want markup to be present within other markup.
	 *
	 * \return                     Returns 0 on success, otherwise an error code is returned.
	 */
	int writeText(const char *theText, Device::paragraphStruct *paragraph = 0, bool expandAbbreviations = false, bool hideMarkup = false);

	/**
	 * This method writes a paragraph to the report.
	 *
	 * \param paragraph            A pointer to the paragraph structure
	 * \return                     Returns 0 on success, otherwise an error code is returned.
	 */
	int writeParagraph(Device::paragraphStruct *paragraph, int section, int subsection);

	/**
	 * This method writes a table to the report.
	 *
	 * \param paragraph            The paragraph that contains the table
	 * \return                     Returns 0 on success, otherwise an error code is returned.
	 */
	int writeTable(Device::paragraphStruct *paragraph);

	/**
	 * This method writes a list to the report.
	 *
	 * \param paragraph            The paragraph that contains the list
	 * \return                     Returns 0 on success, otherwise an error code is returned.
	 */
	int writeList(Device::paragraphStruct *paragraph);

	/**
	 * This method makes the output text friendly to the report format. That is
	 * it ensures that characters that could cause a problem are properly
	 * encoded.
	 *
	 * \param theText              The text to be made friendly.
	 * \return                     The output friendly text is returned.
	 */
	const char *outputFriendly(const char *theText);

	/**
	 * The report output file handle...
	 */
	FILE *outFile;

	/**
	 * Rating Colours
	 */
	const char *colour_critical;
	const char *colour_high;
	const char *colour_medium;
	const char *colour_low;
	const char *colour_informational;
};


#endif

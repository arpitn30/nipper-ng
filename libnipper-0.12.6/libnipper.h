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

#ifndef libnipper_H
#define libnipper_H


extern "C"
{

class Config;
class Device;
class Report;


/**
 * @short The main Nipper class.
 *
 * The Nipper class provides the main processing method for the processing
 * of device configurations. Use the class Config to configure Nipper prior to
 * processing and reporting.
 *
 * <b>Example:</b>\n
 *
 * \code
 *   #include &gt;libnipper/libnipper.h&lt;
 *   #include &gt;libnipper/config.h&lt;
 *   ...
 *   Nipper *nipper = 0;
 *   int errorCode = 0;
 *   ...
 *   // Create Nipper
 *   nipper = new (Nipper);
 *
 *   // Set the device configuration file for nipper to process...
 *   nipper->config->inputSource = "firewall.config";
 *
 *   // Process the configuration file...
 *   errorCode = nipper->process();
 *   if (errorCode == 0)
 *   {
 *
 *       // Generate the report from the configuration...
 *       errorCode = nipper->generateReport();
 *       if (errorCode == 0)
 *       {
 *
 *           // Output the report...
 *           errorCode = writeReport();
 *       }
 *   }
 *
 *   // If an error occured, output the error text...
 *   if (errorCode > 0)
 *       printf("Error: %s\n", nipper->getErrorText(errorCode);
 * \endcode
 *
 * \note It is a requirement of the Nipper license to output the text
 * returned by Nipper::getVersion() somewhere in the calling code. The
 * recommended location would be with the version details of the code itself.
 */
class Nipper
{

  public:

	/**
	 * \brief Get the Nipper library version
	 *
	 * This method returns the Nipper library version. The version text returned
	 * by this method MUST be displayed with version details of any software that
	 * makes use of this library.
	 *
	 * \return            The Nipper library version text.
	 */
	const char *getVersion();

	/**
	 * \brief The Nipper configuration settings
	 *
	 * Set the properties of this to configure Nipper.
	 */
	Config *config;

	/**
	 * \brief Process the device configuration file
	 *
	 * This method tells Nipper to process the configuration file based
	 * on the settings. Once the configuration has been processed a report
	 * can be generated.
	 *
	 * \return      It returns 0 on success, otherwise it indicates an
	 *              error of some kind. The error text can be retreived
	 *              using the getErrorText method.
     * \see Nipper::getErrorText
	 */
	int process();

	/**
	 * \brief Generate the report
	 *
	 * This method tells Nipper to generate a report based on the results of
	 * the configuration processing and the Nipper settings. It does not output
	 * the report.
	 * The report generation settings can be modified and generateReport run again
	 * without having to process the devices configuration again. This could be
	 * useful if you want to create seperate reports for configuration, security
	 * or any other report type.
	 *
	 * \return      It returns 0 on success, otherwise it indicates an
	 *              error of some kind. The error text can be retreived
	 *              using the getErrorText method.
     * \see Nipper::getErrorText
	 * \see Nipper::process
	 * \see Nipper::writeReport
	 */
	int generateReport();

	/**
	 * \brief Write the report to a file
	 *
	 * This method tells Nipper to write out a generated report. This does not
	 * generate the report.
	 * The report output settings can be modified and writeReport run again. This
	 * can enable the output to multiple report formats, without having to repeat
	 * any other processing.
	 *
	 * \return      It returns 0 on success, otherwise it indicates an
	 *              error of some kind. The error text can be retreived
	 *              using the getErrorText method.
     * \see Nipper::getErrorText
	 * \see Nipper::process
	 * \see Nipper::generateReport
	 */
	int writeReport();

	/**
	 * \brief Get a list of possible compliance checks
	 *
	 * DO NOT USE THIS METHOD.
	 *
	 * I know it looks interesting, but it is here for future use and has been
	 * included here to maintain API compatability.
	 */
	const char *getComplianceChecks();

	/**
	 * \brief Get the error text
	 *
	 * This method gets the error text based on the code provided.
	 *
	 * \param errorCode   The error code returned by the process method.
	 * \return            The error text for the supplied code is returned.
	 * \see Nipper::process
	 */
	const char *getErrorText(int errorCode);

	/**
	 * Constructor
	 */
	Nipper();

	/**
	 * Destructor
	 */
	~Nipper();

  private:
	Device *device;
	Report *report;
	bool processed;
	bool generated;
};

}

#endif

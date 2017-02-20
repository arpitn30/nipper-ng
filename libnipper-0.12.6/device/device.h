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

#ifndef device_H
#define device_H

//Includes...
#include <cstdio>
#include <string>

#include "../config.h"


using namespace std;

class ConfigLine;
class General;
class Administration;
class Authentication;
class DNS;
class Banner;
class Filter;
class NetObject;
class SNMP;
class Interfaces;


class Device
{
  public:

	Device();
	virtual ~Device();


	// -------------
	// Structures...
	// -------------

	struct bodyStruct
	{
		bool newCell;
		bool rowSpan;
		string cellData;
		bool referencer;
		string reference;
		struct bodyStruct *next;
	};

	struct headingStruct
	{
		string heading;
		bool password;
		struct headingStruct *next;
	};

	struct tableStruct
	{
		string title;
		int number;
		string reference;
		struct headingStruct *headings;
		struct bodyStruct *body;
	};

	struct listStruct
	{
		string listItem;
		struct listStruct *next;
	};

	struct valueList
	{
		int item;
		struct valueList *next;
	};

	struct paragraphStruct
	{
		string paragraphTitle;
		string paragraph;
		struct valueList *values;
		struct listStruct *strings;
		struct listStruct *list;
		struct tableStruct *table;
		struct paragraphStruct *next;
	};

	struct configReportStruct
	{
		unsigned int section;				// Section no.
		unsigned int subsection;			// Sub section no.
		unsigned int position;				// 1 = at start, 2 = near start, 3 = middle, 4 = near end, 5 = at end
		string title;						// Config section title
		string reference;					// Unique reference for this config section
		struct paragraphStruct *config;		// Paragraph text, table, list...
		struct configReportStruct *next;	// Next config (or 0 for no more)
	};

	struct recommendationStruct
	{
		string recommendation;
		bool recommendationOr;
		struct recommendationStruct *next;
	};

	struct securityIssueStruct
	{
		unsigned int section;				// Section no.
		unsigned int subsection;			// Sub Section no.
		unsigned int position;				// 1 = at start, 2 = near start, 3 = middle, 4 = near end, 5 = at end
		string title;						// Issue title
		string reference;					// Unique reference for this issue
		unsigned int overallRating;			// Overall Rating
		unsigned int impactRating;			// Impact Rating
		unsigned int easeRating;			// Ease Rating
		unsigned int fixRating;				// Fix rating
		paragraphStruct *finding;			// The issue Finding text
		paragraphStruct *impact;			// The issue impact text
		paragraphStruct *ease;				// The issue ease text
		paragraphStruct *recommendation;	// The issue recommendation text
		listStruct *related;				// A list of related issue unique references (they dont have to exist, that is sorted out latter)
		listStruct *dependent;				// A list of dependency issues...
		string conLine;						// The conclusion line for the conclusions section
		recommendationStruct *recLines;		// The recommendation lines for the recommendations table
		struct securityIssueStruct *next;	// Next issue (0 = no more)
	};

	struct johnPasswordStruct
	{
		string user;
		string password;
		struct johnPasswordStruct *next;
	};

	enum weakPasswordEnum
	{
		passwordPassed = 0,
		passwordShort = 1,
		passwordRepeatChars = 2,
		passwordMakeup = 3,			// character cases, numbers and specials
		passwordUsername = 4,
		passwordHostname = 5,
		passwordDeviceInfo = 6,
		passwordDictSubst = 7,
		passwordDictAppend = 8,
		passwordCharSeq = 9
	};

	struct dictionaryStruct
	{
		const char *word;
		struct dictionaryStruct *next;
	};

	struct encryptDictionaryStruct
	{
		const char *hash;
		const char *password;
		struct encryptDictionaryStruct *next;
	};


	// -------------
	// Properties...
	// -------------

	/**
	 * This will contain the libnipper version text.
	 */
	const char *nipperVersion;

	/**
	 * This will point to the libnipper config structure when the Device class is
	 * created.
	 */
	Config *config;

	/**
	 * John-the-ripper password output struct
	 */
	johnPasswordStruct *johnPassword;

	/**
	 * The configuration report.
	 */
	configReportStruct *configReport;

	/**
	 * The security report.
	 */
	securityIssueStruct *securityReport;

	/**
	 * The report introduction.
	 */
	configReportStruct *reportIntro;

	/**
	 * The report appendix.
	 */
	configReportStruct *appendixReport;

	/**
	 * This following properties all define what the device is.
	 */
	const char *deviceType;				// Device type (I.e. Router)
	const char *deviceMake;				// Device make (i.e. Cisco)
	const char *deviceOS;					// Device OS (i.e. IOS)
	const char *deviceModel;				// Device Model (i.e. 2600)
	bool isRouter;							// Set to true if it is a router
	bool isFirewall;						// Set to true if it is a firewall
	bool isSwitch;							// Set to true if it is a switch

	/**
	 * The General class contains basic details about the device, such as the devices name.
	 */
	General *general;

	/**
	 * The Administration class contains administration details about the device.
	 */
	Administration *administration;

	/**
	 * The SNMP class contains SNMP details about the device.
	 */
	SNMP *snmp;

	/**
	 * The Authentication class contains authentication details about the device.
	 */
	Authentication *authentication;

	/**
	 * The Interfaces class contains network interface details about the device.
	 */
	Interfaces *interfaces;

	/**
	 * This is the file handle of the device configuration file used for input.
	 */
	FILE *inputFile;


	// -------------
	// Methods...
	// -------------

	/**
	 * This method gets the error text based on the code provided.
	 *
	 * \param errorCode              The error code returned by the process method.
	 * \return                       The error text for the supplied code is returned.
	 */
	const char *getErrorText(int errorCode);

	/**
	 * This method makes Nipper process the device configuration file.
	 *
	 * \return      Returns 0 on success, otherwise an error code is returned.
	 */
	virtual int process();

	/**
	 * This method generates the report text from the device configuration.
	 *
	 * \return      It returns 0 on success, otherwise it indicates an
	 *              error of some kind. The error text can be retreived
	 *              using the getErrorText method.
     * \see Nipper::getErrorText
	 * \see Nipper::process
	 */
	virtual int generateReport();

	/**
	 * This method determines if the configuration is for the type of device that
	 * the class is developed to process. This can be used as part of a auto-detect
	 * the device type routine.
	 *
	 * \return      It returns true if it matches, otherwise false.
	 */
	virtual bool isDeviceType();

	/**
	 * This method converts an integer into a string.
	 *
	 * \param value              The value to return as a string.
	 * \return                   Returns the string version of the number.
	 */
	const char *intToString(int value);

	/**
	 * This method converts time into a string.
	 *
	 * \param time               The time (in seconds) to return as a string.
	 * \return                   Returns the string version of the time.
	 */
	const char *timeToString(int time);

	/**
	 * This method converts an ip address to the integer representation.
	 *
	 * \param address            The IP address / Netmask to convert.
	 * \return                   Returns the address.
	 */
	unsigned int ipAddressToNum(const char *address);

	enum abbreviationStatus
	{
		abbrevExpand = 0,
		abbrevNotFound = 1,
		abbrevFound = 2
	};
	/**
	 * This method returns whether an abbreviation was found or not and whether it should
	 * be expanded.
	 *
	 * \param abbreviation     The abbreviation
	 * \param expand           Whether the requester would like the abbreviation expanded or
	 *                         or not. If set to true, the return value will inform the caller
	 *                         that the abbreviation has not been previously expanded and can
	 *                         expand if they would like to. The caller is also informed if the
	 *                         abbreviation was not identified.
	 * \return                 Returns whether the abbreviation was found, not, or if it was found
	 *                         and the caller can expand.
	 *
	 * \see Report::getAbbreviation
	 */
	abbreviationStatus addAbbreviation(const char *abbreviation, bool expand);

	/**
	 * This method returns the expanded abbreviation.
	 *
	 * \param abbreviation     The abbreviation
	 * \return                 Returns the expanded abbreviation, or 0
	 *
	 * \see Report::addAbbreviation
	 */
	const char *getAbbreviation(const char *abbreviation);

	/**
	 * This method returns the protocol name.
	 *
	 * \param protocolNumber   The protocol number
	 * \return                 Returns the protocol name
	 */
	const char *getProtocol(int protocolNumber);

	enum paragraphType
	{
					/**  Finding  */
		Finding = 0,
					/**  Impact  */
		Impact = 1,
					/**  Ease  */
		Ease = 2,
					/**  Recommendation  */
		Recommendation = 3
	};
	/**
	 * These methods create a new paragraph structure and returns a
	 * pointer to it.
	 *
	 * \param securityIssuePointer   A Pointer to a security issue structure
	 * \param configReportPointer    A Pointer to a configuration report structure
	 * \param paragraph              The paragraph type (Device::Finding...)
	 * \return                       Pointer to a new paragraph structure.
	 */
	paragraphStruct *addParagraph(securityIssueStruct *securityIssuePointer, paragraphType paragraph);
	paragraphStruct *addParagraph(configReportStruct *configReportPointer);

	/**
	 * This method creates a new list item in the given
	 * paragraph structure.
	 *
	 * \param paragraphPointer   A Pointer to the paragraph structure the list item is to be created in.
	 * \param itemText           The list item string.
	 * \return                   Returns 0 if all is ok.
	 */
	int addListItem(paragraphStruct *paragraphPointer, const char *itemText);

	/**
	 * This method creates a new table structure in the given
	 * paragraph structure.
	 *
	 * \param paragraphPointer   A Pointer to the paragraph structure the table is to be created in.
	 * \param reference          The reference string for the table.
	 * \return                   Returns 0 if all is ok.
	 */
	int addTable(paragraphStruct *paragraphPointer, const char *reference);

	/**
	 * This method adds a heading to the table.
	 *
	 * \param tablePointer      A Pointer to the table structure.
	 * \param heading           The heading text to add to the table.
	 * \param password          Will the table column contain passwords?
	 * \return                  Returns 0 if successful.
	 */
	int addTableHeading(tableStruct *tablePointer, const char *heading, bool password);

	/**
	 * This method adds data to the table and returns a pointer to the structure.
	 * The data is added without a reference and defaults to being a new table
	 * cell each time. If other settings are required, they need to be customised
	 * using the returned structure pointer.
	 *
	 * \param tablePointer     A Pointer to the table structure.
	 * \param data             The table data to add.
	 * \return                 Returns a pointer to the new structure (if successful, else a 0)
	 */
	bodyStruct *addTableData(tableStruct *tablePointer, const char *data);

	/**
	 * This method returns a pointer to a table structure that has the reference provided.
	 *
	 * \param reference        The reference string for the table.
	 * \return                 Returns a pointer to the table, or 0 if it has not been found.
	 */
	paragraphStruct *getTableParagraphPointer(const char *reference);

	/**
	 * This method finds and returns a pointer to a config report section structure.
	 * If the structure is not found, one is created and returned.
	 *
	 * \return                 Pointer to config report structure.
	 */
	configReportStruct *getConfigSection(const char *reference);

	/**
	 * This method finds and returns a pointer to a appendix report section structure.
	 * If the structure is not found, one is created and returned.
	 *
	 * \return                 Pointer to appendix report structure.
	 */
	configReportStruct *getAppendixSection(const char *reference);

	/**
	 * This method creates a new security issue structure and returns a
	 * pointer to it.
	 *
	 * \return                 Pointer to a new security issue structure.
	 */
	securityIssueStruct *addSecurityIssue();

	/**
	 * This method gets an existing security issue structure and returns a
	 * pointer to it. (or null if it does not exist).
	 *
	 * \param reference        The reference for the security issue.
	 * \return                 Pointer to a new security issue structure.
	 */
	securityIssueStruct *getSecurityIssue(const char *reference);

	/**
	 * This method adds a value to the paragraphs value list.
	 *
	 * \param value            The integer to add.
	 * \return                 Returns 0 if ok, else an error code is returned.
	 */
	int addValue(paragraphStruct *paragraph, int value);

	/**
	 * This method adds a string to the paragraphs string list.
	 *
	 * \param paragraph        The paragraph to add the list item to.
	 * \param item             The string to add.
	 * \return                 Returns 0 if ok, else an error code is returned.
	 */
	int addString(paragraphStruct *paragraph, const char *item);

	/**
	 * This method adds a string to the paragraphs string list.
	 *
	 * \param securityIssue    The security issue to add to
	 * \param dependent        The dependency reference.
	 * \return                 Returns 0 if ok, else an error code is returned.
	 */
	int addDependency(securityIssueStruct *securityIssue, const char *dependent);

	/**
	 * This method adds a recommendation to a security issue.
	 *
	 * \param securityIssue    The security issue to add to
	 * \param recommendation   The string to add.
	 * \param orAction         Join the recommendations together with or's
	 * \return                 Returns 0 if ok, else an error code is returned.
	 */
	int addRecommendation(securityIssueStruct *securityIssue, const char *recommendation, bool orAction = false);

	/**
	 * This method adds a password requirements list to a paragraph.
	 *
	 * \param paragraph        The paragraph to add the password list to.
	 * \return                 Returns 0 if ok, else an error code is returned.
	 *
	 * \note This method adds to the string list, so make sure it is called in the
	 * order it will be processed in during the report writing phase.
	 */
	int addPasswordRequirements(paragraphStruct *paragraph);

	/**
	 * This method adds a reference to a security issues related issue list.
	 *
	 * \param securityIssuePointer      The security issue to add the reference to
	 * \param reference                 The reference
	 * \return                          Returns 0 if ok, else an error code is returned.
	 */
	int addRelatedIssue(securityIssueStruct *securityIssuePointer, const char *reference);

	/**
	 * This method adds a port to the list of common ports.
	 *
	 * \param portDescription  The port description (i.e. HTTP or FTP)
	 */
	void addPort(const char *portDescription);

	/**
	 * This method gets a port number from a ports description.
	 *
	 * \param portDescription  The port description (i.e. HTTP or FTP)
	 * \return                 The port number is returned or 0 on error.
	 */
	int getPort(const char *portDescription);

	/**
	 * This method adds a IP protocol to the list of used IP protocols.
	 *
	 * \param name  The IP protocol description (i.e. VRRP)
	 */
	void addProtocol(const char *name);
	void addProtocol(int protocolNumber);

	/**
	 * This method adds a ICMP Type to the list of used ICMP Types.
	 *
	 * \param type  The protocol type number
	 * \param name  The textual description
	 * \param code  Optional code
	 */
	void addICMPType(unsigned int type, int code = -1);
	void addICMPType(const char *name, int code = -1);

	/**
	 * This method gets an ICMP Type Description from the list.
	 *
	 * \param type  The protocol type number
	 * \param name  The textual description
	 * \param code  Optional ICMP code
	 *
	 * \return The ICMP description
	 */
	const char *getICMPType(unsigned int type, int code = -1);
	const char *getICMPType(const char *name, int code = -1);

	/**
	 * This method gets an ICMP Type Name from the list.
	 *
	 * \param type  The protocol type number
	 *
	 * \return The ICMP description
	 */
	const char *getICMPName(unsigned int type);

	/**
	 * This method checks whether the password meets the password strength
	 * requirements.
	 *
	 * \param password    The password.
	 * \return            Returns true if the password is weak.
	 *
	 * \see addPasswordIssue
	 */
	weakPasswordEnum isPasswordWeak(const char *password, const char *username = 0);

	/**
	 * This method checks whether the password is in the dictionary.
	 *
	 * \param password    The password.
	 * \return            Returns true if the password is weak.
	 *
	 * \see addPasswordIssue
	 */
	bool isDictionaryPassword(const char *password);

	/**
	 * This method checks whether the password is in the encrypted
	 * password hash dictionary.
	 *
	 * \param password    The password.
	 * \return            Returns true if the password is weak.
	 *
	 * \see addPasswordIssue
	 */
	const char *isEncryptedDictionaryPassword(const char *password);

	/**
	 * This method adds an encrypted password to the john-the-ripper password list.
	 *
	 * \param user      The username for the password (or identifying description).
	 * \param password  The encrypted password.          
	 */
	void addJohnPassword(const char *user, const char *password);

	/**
	 * This method reads a line from the input file, it strips any end of
	 * line characters.
	 *
	 * \param line                   The text buffer to put the line into.
	 * \param lineSize               The size of the text buffer.
	 */
	virtual void readLine(char *line, int lineSize);

	/**
	 * This method decodes Cisco Type 7 encoded passwords.
	 *
	 * \param encodedPassword    The encoded password.
	 * \return                   Returns a decoded password or an empty string if there was a problem.
	 */
	const char *ciscoType7Decode(const char *encodedPassword);

	/**
	 * This method converts an CIDR into a netmask string.
	 *
	 * \param cidr               The cidr to return as a netmask.
	 * \return                   Returns the netmask.
	 */
	const char *cidrToNetmask(const char *cidr);

	/**
	 * Internal debug method. Do NOT use.
	 */
	void lineNotProcessed(const char *line);

	/**
	 * Is the logging levels section to be generated (the config option also
	 * needs to be set) INTERNAL - DO NOT USE.
	 */
	bool appendixLoggingLevels;

	/**
	 * This method performs case-insensitive checks that the needle is within the haystack.
	 */
	bool isInString(const char *haystack, const char *needle);


	/**
	 * This method creates a port/interface list from the usual range/list definition.
	 * E.g. 4-8,12,14,60-72. This list contains individual entries. It is the responsibility
	 * of the caller to destroy the memory reserved by this.
	 */
	listStruct *createPortList(const char *portString);


  protected:

	// -------------
	// Properties...
	// -------------

	/**
	 * The following classes are responsible for their own individual specialities.
	 */
	DNS *dns;
	Banner *banner;
	Filter *filter;

	/**
	 * This is the name of a temporary file, if one is used as input. If this
	 * is not empty, the file is deleted when the object is destroyed.
	 */
	string tempFileName;

	/**
	 * This property disables the device network services in the configuration
	 * report. Especially for those devices that don't support them yet.
	 */
	bool supportConfigNetworkServices;

	/**
	 * The builtin dictionarys.
	 */
	dictionaryStruct *dictionary;
	encryptDictionaryStruct *encryptedDictionary;


	// ----------
	// Methods...
	// ----------

	/**
	 * This method opens a file for input (including stdin and SNMP).
	 */
	virtual int openInput();

	/**
	 * This method process the device configuration.
	 *
	 * \return                       Returns 0 on success, otherwise an error code is returned.
	 */
	virtual int processDevice();

	/**
	 * This method sets the device defaults after the configuration has
	 * been processed.
	 */
	virtual void setPostDefaults();

	/**
	 * This method decodes base64 encoded content.
	 *
	 * \param encodedString      The encoded content.
	 * \return                   Returns the decoded content or an empty string if there was a problem.
	 */
	const char *base64Decode(const char *encodedString);

	/**
	 * This method decodes URL encoded content.
	 *
	 * \param encodedString      The encoded content.
	 * \return                   Returns the decoded content or an empty string if there was a problem.
	 */
	const char *urlDecode(const char *encodedString, bool replaceFirstEquals = false);

	/**
	 * This method sets the device common defaults after the configuration has
	 * been processed.
	 */
	void setPostCommonDefaults();


  private:

	/**
	 * This method generates the abbreviations appendix section, based on the abbreviations that are
	 * marked to be included.
	 */
	int generateAppendixAbbreviations();

	/**
	 * This method generates the common ports appendix section, based on the common ports that are
	 * marked to be included.
	 */
	int generateAppendixCommonPorts();

	/**
	 * This method generates the used IP protcols appendix section, based on the ip protocols that are
	 * marked to be included.
	 */
	int generateAppendixUsedProtocols();

	/**
	 * This method generates the used ICMP Types appendix section, based on the ICMP Types that are
	 * marked to be included.
	 */
	int generateAppendixUsedICMPTypes();

	/**
	 * This method generates the logging levels appendix section, if logging levels are used within
	 * the body of the report.
	 */
	int generateAppendixLoggingLevels();

	/**
	 * Adds appendix abbreviations. It goes through the structures and generates the abbreviations.
	 * This needs to be done at the generation stage in order to generate some report appendix
	 * sections, such as the "abbreviations" and "common ports" sections. However, abbreviations
	 * in the report text are processed in the report output (as these are report output format
	 * specific).
	 */
	int addAppendixAbbreviations();

	/**
	 * This method is called by addAppendixAbbreviations() for the processing of paragraphs.
	 */
	void addAppendixParagraphAbbreviations(paragraphStruct *paragraph);

	/**
	 * This method identifies abbreviations within text adds them.
	 */
	int identifyAbbreviations(string *testString);

	/**
	 * This method checks that a character is a valid base64 character.
	 */
	int checkBase64Char(const char inputChar);

	/**
	 * This method reorders the identified security issues.
	 */
	void reorderSecurityIssues();

	/**
	 * This method assigns reference numbers to the report tables generated.
	 */
	void numberReportTables();

	/**
	 * This method assigns reference numbers to the report sections generated.
	 */
	void numberReportSections();

	/**
	 * This method resolves dependent issue reference numbers in the security report.
	 */
	void resolveDependentIssues();

	/**
	 * This method resolves related issue reference numbers in the security report.
	 */
	void resolveRelatedIssues();

	/**
	 * This method calculates the overall rating.
	 */
	int calcOverallRating(int impact, int ease);
};


#endif

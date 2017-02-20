/***************************************************************************
 *   Nipper - The network infrastructure parser                            *
 *   Copyright (C) 2006 - 2008 by Ian Ventura-Whiting (Fizz)               *
 *   fizz@titania.co.uk                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.  *
 ***************************************************************************/


using namespace std;


// Includes...
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libnipper.h"
#include "config.h"


// Global Constants...
const char *program_banner = "                     _                           ____\n"
                             "               _ __ (_)_ __  _ __   ___ _ __    / ->/|\n"
                             "              | '_ \\| | '_ \\| '_ \\ / _ \\ '__|  /<-_/ |\n"
                             "              | | | | | |_) | |_) |  __/ |     |   | /\n"
                             "              |_| |_|_| .__/| .__/ \\___|_|     |___|/\n"
                             "                      |_|   |_|\n\n"
                             "                         CLI Version 0.12.0 BETA2\n"
                             "                    http://nipper.titania.co.uk\n"
                             "            Copyright (C) 2006-2008 Ian Ventura-Whiting\n";
const char *program_version_banner = "Nipper CLI version 0.12.0 BETA2\nhttp://nipper.titania.co.uk\nCopyright (C) 2006-2008 Ian Ventura-Whiting";


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


int paramno = 0;		// Used for command parameter errors.


// Help function modes...
#define help_general 99
#define help_version 1
#define help_license 2
#define help_device_types 10
#define help_device_usage 11
#define help_report_formats 20
#define help_report_options 21
#define help_report_appendix 22
#define help_report_html 23
#define help_report_latex 24
#define help_audit_acl 30
#define help_audit_password 31
#define help_audit_misc 32
#define help_snmp 33
#define help_debug 40
#define help_config_file 50
#define help_errorheader 90
#define help_error_params 100


void showHelpFooter()
{
	// Further Help...
	printf("%sFor additional help:%s\n", COL_BLUE, RESET);
	printf("    %s--help[=<topic>]%s\n", COL_GREEN, RESET);
	printf("    Show  the  online help  or show  the  additional  help on  the topic\n");
	printf("    specified.  The help  topics  are;  GENERAL,  DEVICES,  DEVICES-ADV,\n");
	printf("    SNMP,  REPORT, REPORT-ADV,  REPORT-SECT, REPORT-HTML,  REPORT-LATEX,\n");
	printf("    AUDIT-ACL, AUDIT-PASS, AUDIT-ADV or CONFIG-FILE.\n");
}


void showHelp(int argc, char *argv[], int helpMode)
{
	// Variables...
	int tempInt = 0;

	switch (helpMode)
	{
		// License...
		case help_license:
			printf("%s%s\n%s", COL_BLUE, program_banner, RESET);
			printf("Nipper is licensed under the GPL version 3 license with two exceptions:\n");
			printf("\n");
			printf("1. Nipper cannot be used as part of a commercial product. However, it\n");
			printf("   can be licensed for use in a commercial product.\n");
			printf("2. An product that inegrates Nipper MUST display the Nipper copyright\n");
			printf("   notice.\n\n");
			printf("More information is on the Nipper web site http://nipper.titania.co.uk\n\n");
			printf("The GPL version 3 license follows:\n\n");
			printf("                    GNU GENERAL PUBLIC LICENSE\n");
			printf("                       Version 3, 29 June 2007\n");
			printf("\n");
			printf(" Copyright (C) 2007 Free Software Foundation, Inc. <http://fsf.org/>\n");
			printf(" Everyone is permitted to copy and distribute verbatim copies\n");
			printf(" of this license document, but changing it is not allowed.\n");
			printf("\n");
			printf("                            Preamble\n");
			printf("\n");
			printf("  The GNU General Public License is a free, copyleft license for\n");
			printf("software and other kinds of works.\n");
			printf("\n");
			printf("  The licenses for most software and other practical works are designed\n");
			printf("to take away your freedom to share and change the works.  By contrast,\n");
			printf("the GNU General Public License is intended to guarantee your freedom to\n");
			printf("share and change all versions of a program--to make sure it remains free\n");
			printf("software for all its users.  We, the Free Software Foundation, use the\n");
			printf("GNU General Public License for most of our software; it applies also to\n");
			printf("any other work released this way by its authors.  You can apply it to\n");
			printf("your programs, too.\n");
			printf("\n");
			printf("  When we speak of free software, we are referring to freedom, not\n");
			printf("price.  Our General Public Licenses are designed to make sure that you\n");
			printf("have the freedom to distribute copies of free software (and charge for\n");
			printf("them if you wish), that you receive source code or can get it if you\n");
			printf("want it, that you can change the software or use pieces of it in new\n");
			printf("free programs, and that you know you can do these things.\n");
			printf("\n");
			printf("  To protect your rights, we need to prevent others from denying you\n");
			printf("these rights or asking you to surrender the rights.  Therefore, you have\n");
			printf("certain responsibilities if you distribute copies of the software, or if\n");
			printf("you modify it: responsibilities to respect the freedom of others.\n");
			printf("\n");
			printf("  For example, if you distribute copies of such a program, whether\n");
			printf("gratis or for a fee, you must pass on to the recipients the same\n");
			printf("freedoms that you received.  You must make sure that they, too, receive\n");
			printf("or can get the source code.  And you must show them these terms so they\n");
			printf("know their rights.\n");
			printf("\n");
			printf("  Developers that use the GNU GPL protect your rights with two steps:\n");
			printf("(1) assert copyright on the software, and (2) offer you this License\n");
			printf("giving you legal permission to copy, distribute and/or modify it.\n");
			printf("\n");
			printf("  For the developers' and authors' protection, the GPL clearly explains\n");
			printf("that there is no warranty for this free software.  For both users' and\n");
			printf("authors' sake, the GPL requires that modified versions be marked as\n");
			printf("changed, so that their problems will not be attributed erroneously to\n");
			printf("authors of previous versions.\n");
			printf("\n");
			printf("  Some devices are designed to deny users access to install or run\n");
			printf("modified versions of the software inside them, although the manufacturer\n");
			printf("can do so.  This is fundamentally incompatible with the aim of\n");
			printf("protecting users' freedom to change the software.  The systematic\n");
			printf("pattern of such abuse occurs in the area of products for individuals to\n");
			printf("use, which is precisely where it is most unacceptable.  Therefore, we\n");
			printf("have designed this version of the GPL to prohibit the practice for those\n");
			printf("products.  If such problems arise substantially in other domains, we\n");
			printf("stand ready to extend this provision to those domains in future versions\n");
			printf("of the GPL, as needed to protect the freedom of users.\n");
			printf("\n");
			printf("  Finally, every program is threatened constantly by software patents.\n");
			printf("States should not allow patents to restrict development and use of\n");
			printf("software on general-purpose computers, but in those that do, we wish to\n");
			printf("avoid the special danger that patents applied to a free program could\n");
			printf("make it effectively proprietary.  To prevent this, the GPL assures that\n");
			printf("patents cannot be used to render the program non-free.\n");
			printf("\n");
			printf("  The precise terms and conditions for copying, distribution and\n");
			printf("modification follow.\n");
			printf("\n");
			printf("                       TERMS AND CONDITIONS\n");
			printf("\n");
			printf("  0. Definitions.\n");
			printf("\n");
			printf("  \"This License\" refers to version 3 of the GNU General Public License.\n");
			printf("\n");
			printf("  \"Copyright\" also means copyright-like laws that apply to other kinds of\n");
			printf("works, such as semiconductor masks.\n");
			printf("\n");
			printf("  \"The Program\" refers to any copyrightable work licensed under this\n");
			printf("License.  Each licensee is addressed as \"you\".  \"Licensees\" and\n");
			printf("\"recipients\" may be individuals or organizations.\n");
			printf("\n");
			printf("  To \"modify\" a work means to copy from or adapt all or part of the work\n");
			printf("in a fashion requiring copyright permission, other than the making of an\n");
			printf("exact copy.  The resulting work is called a \"modified version\" of the\n");
			printf("earlier work or a work \"based on\" the earlier work.\n");
			printf("\n");
			printf("  A \"covered work\" means either the unmodified Program or a work based\n");
			printf("on the Program.\n");
			printf("\n");
			printf("  To \"propagate\" a work means to do anything with it that, without\n");
			printf("permission, would make you directly or secondarily liable for\n");
			printf("infringement under applicable copyright law, except executing it on a\n");
			printf("computer or modifying a private copy.  Propagation includes copying,\n");
			printf("distribution (with or without modification), making available to the\n");
			printf("public, and in some countries other activities as well.\n");
			printf("\n");
			printf("  To \"convey\" a work means any kind of propagation that enables other\n");
			printf("parties to make or receive copies.  Mere interaction with a user through\n");
			printf("a computer network, with no transfer of a copy, is not conveying.\n");
			printf("\n");
			printf("  An interactive user interface displays \"Appropriate Legal Notices\"\n");
			printf("to the extent that it includes a convenient and prominently visible\n");
			printf("feature that (1) displays an appropriate copyright notice, and (2)\n");
			printf("tells the user that there is no warranty for the work (except to the\n");
			printf("extent that warranties are provided), that licensees may convey the\n");
			printf("work under this License, and how to view a copy of this License.  If\n");
			printf("the interface presents a list of user commands or options, such as a\n");
			printf("menu, a prominent item in the list meets this criterion.\n");
			printf("\n");
			printf("  1. Source Code.\n");
			printf("\n");
			printf("  The \"source code\" for a work means the preferred form of the work\n");
			printf("for making modifications to it.  \"Object code\" means any non-source\n");
			printf("form of a work.\n");
			printf("\n");
			printf("  A \"Standard Interface\" means an interface that either is an official\n");
			printf("standard defined by a recognized standards body, or, in the case of\n");
			printf("interfaces specified for a particular programming language, one that\n");
			printf("is widely used among developers working in that language.\n");
			printf("\n");
			printf("  The \"System Libraries\" of an executable work include anything, other\n");
			printf("than the work as a whole, that (a) is included in the normal form of\n");
			printf("packaging a Major Component, but which is not part of that Major\n");
			printf("Component, and (b) serves only to enable use of the work with that\n");
			printf("Major Component, or to implement a Standard Interface for which an\n");
			printf("implementation is available to the public in source code form.  A\n");
			printf("\"Major Component\", in this context, means a major essential component\n");
			printf("(kernel, window system, and so on) of the specific operating system\n");
			printf("(if any) on which the executable work runs, or a compiler used to\n");
			printf("produce the work, or an object code interpreter used to run it.\n");
			printf("\n");
			printf("  The \"Corresponding Source\" for a work in object code form means all\n");
			printf("the source code needed to generate, install, and (for an executable\n");
			printf("work) run the object code and to modify the work, including scripts to\n");
			printf("control those activities.  However, it does not include the work's\n");
			printf("System Libraries, or general-purpose tools or generally available free\n");
			printf("programs which are used unmodified in performing those activities but\n");
			printf("which are not part of the work.  For example, Corresponding Source\n");
			printf("includes interface definition files associated with source files for\n");
			printf("the work, and the source code for shared libraries and dynamically\n");
			printf("linked subprograms that the work is specifically designed to require,\n");
			printf("such as by intimate data communication or control flow between those\n");
			printf("subprograms and other parts of the work.\n");
			printf("\n");
			printf("  The Corresponding Source need not include anything that users\n");
			printf("can regenerate automatically from other parts of the Corresponding\n");
			printf("Source.\n");
			printf("\n");
			printf("  The Corresponding Source for a work in source code form is that\n");
			printf("same work.\n");
			printf("\n");
			printf("  2. Basic Permissions.\n");
			printf("\n");
			printf("  All rights granted under this License are granted for the term of\n");
			printf("copyright on the Program, and are irrevocable provided the stated\n");
			printf("conditions are met.  This License explicitly affirms your unlimited\n");
			printf("permission to run the unmodified Program.  The output from running a\n");
			printf("covered work is covered by this License only if the output, given its\n");
			printf("content, constitutes a covered work.  This License acknowledges your\n");
			printf("rights of fair use or other equivalent, as provided by copyright law.\n");
			printf("\n");
			printf("  You may make, run and propagate covered works that you do not\n");
			printf("convey, without conditions so long as your license otherwise remains\n");
			printf("in force.  You may convey covered works to others for the sole purpose\n");
			printf("of having them make modifications exclusively for you, or provide you\n");
			printf("with facilities for running those works, provided that you comply with\n");
			printf("the terms of this License in conveying all material for which you do\n");
			printf("not control copyright.  Those thus making or running the covered works\n");
			printf("for you must do so exclusively on your behalf, under your direction\n");
			printf("and control, on terms that prohibit them from making any copies of\n");
			printf("your copyrighted material outside their relationship with you.\n");
			printf("\n");
			printf("  Conveying under any other circumstances is permitted solely under\n");
			printf("the conditions stated below.  Sublicensing is not allowed; section 10\n");
			printf("makes it unnecessary.\n");
			printf("\n");
			printf("  3. Protecting Users' Legal Rights From Anti-Circumvention Law.\n");
			printf("\n");
			printf("  No covered work shall be deemed part of an effective technological\n");
			printf("measure under any applicable law fulfilling obligations under article\n");
			printf("11 of the WIPO copyright treaty adopted on 20 December 1996, or\n");
			printf("similar laws prohibiting or restricting circumvention of such\n");
			printf("measures.\n");
			printf("\n");
			printf("  When you convey a covered work, you waive any legal power to forbid\n");
			printf("circumvention of technological measures to the extent such circumvention\n");
			printf("is effected by exercising rights under this License with respect to\n");
			printf("the covered work, and you disclaim any intention to limit operation or\n");
			printf("modification of the work as a means of enforcing, against the work's\n");
			printf("users, your or third parties' legal rights to forbid circumvention of\n");
			printf("technological measures.\n");
			printf("\n");
			printf("  4. Conveying Verbatim Copies.\n");
			printf("\n");
			printf("  You may convey verbatim copies of the Program's source code as you\n");
			printf("receive it, in any medium, provided that you conspicuously and\n");
			printf("appropriately publish on each copy an appropriate copyright notice;\n");
			printf("keep intact all notices stating that this License and any\n");
			printf("non-permissive terms added in accord with section 7 apply to the code;\n");
			printf("keep intact all notices of the absence of any warranty; and give all\n");
			printf("recipients a copy of this License along with the Program.\n");
			printf("\n");
			printf("  You may charge any price or no price for each copy that you convey,\n");
			printf("and you may offer support or warranty protection for a fee.\n");
			printf("\n");
			printf("  5. Conveying Modified Source Versions.\n");
			printf("\n");
			printf("  You may convey a work based on the Program, or the modifications to\n");
			printf("produce it from the Program, in the form of source code under the\n");
			printf("terms of section 4, provided that you also meet all of these conditions:\n");
			printf("\n");
			printf("    a) The work must carry prominent notices stating that you modified\n");
			printf("    it, and giving a relevant date.\n");
			printf("\n");
			printf("    b) The work must carry prominent notices stating that it is\n");
			printf("    released under this License and any conditions added under section\n");
			printf("    7.  This requirement modifies the requirement in section 4 to\n");
			printf("    \"keep intact all notices\".\n");
			printf("\n");
			printf("    c) You must license the entire work, as a whole, under this\n");
			printf("    License to anyone who comes into possession of a copy.  This\n");
			printf("    License will therefore apply, along with any applicable section 7\n");
			printf("    additional terms, to the whole of the work, and all its parts,\n");
			printf("    regardless of how they are packaged.  This License gives no\n");
			printf("    permission to license the work in any other way, but it does not\n");
			printf("    invalidate such permission if you have separately received it.\n");
			printf("\n");
			printf("    d) If the work has interactive user interfaces, each must display\n");
			printf("    Appropriate Legal Notices; however, if the Program has interactive\n");
			printf("    interfaces that do not display Appropriate Legal Notices, your\n");
			printf("    work need not make them do so.\n");
			printf("\n");
			printf("  A compilation of a covered work with other separate and independent\n");
			printf("works, which are not by their nature extensions of the covered work,\n");
			printf("and which are not combined with it such as to form a larger program,\n");
			printf("in or on a volume of a storage or distribution medium, is called an\n");
			printf("\"aggregate\" if the compilation and its resulting copyright are not\n");
			printf("used to limit the access or legal rights of the compilation's users\n");
			printf("beyond what the individual works permit.  Inclusion of a covered work\n");
			printf("in an aggregate does not cause this License to apply to the other\n");
			printf("parts of the aggregate.\n");
			printf("\n");
			printf("  6. Conveying Non-Source Forms.\n");
			printf("\n");
			printf("  You may convey a covered work in object code form under the terms\n");
			printf("of sections 4 and 5, provided that you also convey the\n");
			printf("machine-readable Corresponding Source under the terms of this License,\n");
			printf("in one of these ways:\n");
			printf("\n");
			printf("    a) Convey the object code in, or embodied in, a physical product\n");
			printf("    (including a physical distribution medium), accompanied by the\n");
			printf("    Corresponding Source fixed on a durable physical medium\n");
			printf("    customarily used for software interchange.\n");
			printf("\n");
			printf("    b) Convey the object code in, or embodied in, a physical product\n");
			printf("    (including a physical distribution medium), accompanied by a\n");
			printf("    written offer, valid for at least three years and valid for as\n");
			printf("    long as you offer spare parts or customer support for that product\n");
			printf("    model, to give anyone who possesses the object code either (1) a\n");
			printf("    copy of the Corresponding Source for all the software in the\n");
			printf("    product that is covered by this License, on a durable physical\n");
			printf("    medium customarily used for software interchange, for a price no\n");
			printf("    more than your reasonable cost of physically performing this\n");
			printf("    conveying of source, or (2) access to copy the\n");
			printf("    Corresponding Source from a network server at no charge.\n");
			printf("\n");
			printf("    c) Convey individual copies of the object code with a copy of the\n");
			printf("    written offer to provide the Corresponding Source.  This\n");
			printf("    alternative is allowed only occasionally and noncommercially, and\n");
			printf("    only if you received the object code with such an offer, in accord\n");
			printf("    with subsection 6b.\n");
			printf("\n");
			printf("    d) Convey the object code by offering access from a designated\n");
			printf("    place (gratis or for a charge), and offer equivalent access to the\n");
			printf("    Corresponding Source in the same way through the same place at no\n");
			printf("    further charge.  You need not require recipients to copy the\n");
			printf("    Corresponding Source along with the object code.  If the place to\n");
			printf("    copy the object code is a network server, the Corresponding Source\n");
			printf("    may be on a different server (operated by you or a third party)\n");
			printf("    that supports equivalent copying facilities, provided you maintain\n");
			printf("    clear directions next to the object code saying where to find the\n");
			printf("    Corresponding Source.  Regardless of what server hosts the\n");
			printf("    Corresponding Source, you remain obligated to ensure that it is\n");
			printf("    available for as long as needed to satisfy these requirements.\n");
			printf("\n");
			printf("    e) Convey the object code using peer-to-peer transmission, provided\n");
			printf("    you inform other peers where the object code and Corresponding\n");
			printf("    Source of the work are being offered to the general public at no\n");
			printf("    charge under subsection 6d.\n");
			printf("\n");
			printf("  A separable portion of the object code, whose source code is excluded\n");
			printf("from the Corresponding Source as a System Library, need not be\n");
			printf("included in conveying the object code work.\n");
			printf("\n");
			printf("  A \"User Product\" is either (1) a \"consumer product\", which means any\n");
			printf("tangible personal property which is normally used for personal, family,\n");
			printf("or household purposes, or (2) anything designed or sold for incorporation\n");
			printf("into a dwelling.  In determining whether a product is a consumer product,\n");
			printf("doubtful cases shall be resolved in favor of coverage.  For a particular\n");
			printf("product received by a particular user, \"normally used\" refers to a\n");
			printf("typical or common use of that class of product, regardless of the status\n");
			printf("of the particular user or of the way in which the particular user\n");
			printf("actually uses, or expects or is expected to use, the product.  A product\n");
			printf("is a consumer product regardless of whether the product has substantial\n");
			printf("commercial, industrial or non-consumer uses, unless such uses represent\n");
			printf("the only significant mode of use of the product.\n");
			printf("\n");
			printf("  \"Installation Information\" for a User Product means any methods,\n");
			printf("procedures, authorization keys, or other information required to install\n");
			printf("and execute modified versions of a covered work in that User Product from\n");
			printf("a modified version of its Corresponding Source.  The information must\n");
			printf("suffice to ensure that the continued functioning of the modified object\n");
			printf("code is in no case prevented or interfered with solely because\n");
			printf("modification has been made.\n");
			printf("\n");
			printf("  If you convey an object code work under this section in, or with, or\n");
			printf("specifically for use in, a User Product, and the conveying occurs as\n");
			printf("part of a transaction in which the right of possession and use of the\n");
			printf("User Product is transferred to the recipient in perpetuity or for a\n");
			printf("fixed term (regardless of how the transaction is characterized), the\n");
			printf("Corresponding Source conveyed under this section must be accompanied\n");
			printf("by the Installation Information.  But this requirement does not apply\n");
			printf("if neither you nor any third party retains the ability to install\n");
			printf("modified object code on the User Product (for example, the work has\n");
			printf("been installed in ROM).\n");
			printf("\n");
			printf("  The requirement to provide Installation Information does not include a\n");
			printf("requirement to continue to provide support service, warranty, or updates\n");
			printf("for a work that has been modified or installed by the recipient, or for\n");
			printf("the User Product in which it has been modified or installed.  Access to a\n");
			printf("network may be denied when the modification itself materially and\n");
			printf("adversely affects the operation of the network or violates the rules and\n");
			printf("protocols for communication across the network.\n");
			printf("\n");
			printf("  Corresponding Source conveyed, and Installation Information provided,\n");
			printf("in accord with this section must be in a format that is publicly\n");
			printf("documented (and with an implementation available to the public in\n");
			printf("source code form), and must require no special password or key for\n");
			printf("unpacking, reading or copying.\n");
			printf("\n");
			printf("  7. Additional Terms.\n");
			printf("\n");
			printf("  \"Additional permissions\" are terms that supplement the terms of this\n");
			printf("License by making exceptions from one or more of its conditions.\n");
			printf("Additional permissions that are applicable to the entire Program shall\n");
			printf("be treated as though they were included in this License, to the extent\n");
			printf("that they are valid under applicable law.  If additional permissions\n");
			printf("apply only to part of the Program, that part may be used separately\n");
			printf("under those permissions, but the entire Program remains governed by\n");
			printf("this License without regard to the additional permissions.\n");
			printf("\n");
			printf("  When you convey a copy of a covered work, you may at your option\n");
			printf("remove any additional permissions from that copy, or from any part of\n");
			printf("it.  (Additional permissions may be written to require their own\n");
			printf("removal in certain cases when you modify the work.)  You may place\n");
			printf("additional permissions on material, added by you to a covered work,\n");
			printf("for which you have or can give appropriate copyright permission.\n");
			printf("\n");
			printf("  Notwithstanding any other provision of this License, for material you\n");
			printf("add to a covered work, you may (if authorized by the copyright holders of\n");
			printf("that material) supplement the terms of this License with terms:\n");
			printf("\n");
			printf("    a) Disclaiming warranty or limiting liability differently from the\n");
			printf("    terms of sections 15 and 16 of this License; or\n");
			printf("\n");
			printf("    b) Requiring preservation of specified reasonable legal notices or\n");
			printf("    author attributions in that material or in the Appropriate Legal\n");
			printf("    Notices displayed by works containing it; or\n");
			printf("\n");
			printf("    c) Prohibiting misrepresentation of the origin of that material, or\n");
			printf("    requiring that modified versions of such material be marked in\n");
			printf("    reasonable ways as different from the original version; or\n");
			printf("\n");
			printf("    d) Limiting the use for publicity purposes of names of licensors or\n");
			printf("    authors of the material; or\n");
			printf("\n");
			printf("    e) Declining to grant rights under trademark law for use of some\n");
			printf("    trade names, trademarks, or service marks; or\n");
			printf("\n");
			printf("    f) Requiring indemnification of licensors and authors of that\n");
			printf("    material by anyone who conveys the material (or modified versions of\n");
			printf("    it) with contractual assumptions of liability to the recipient, for\n");
			printf("    any liability that these contractual assumptions directly impose on\n");
			printf("    those licensors and authors.\n");
			printf("\n");
			printf("  All other non-permissive additional terms are considered \"further\n");
			printf("restrictions\" within the meaning of section 10.  If the Program as you\n");
			printf("received it, or any part of it, contains a notice stating that it is\n");
			printf("governed by this License along with a term that is a further\n");
			printf("restriction, you may remove that term.  If a license document contains\n");
			printf("a further restriction but permits relicensing or conveying under this\n");
			printf("License, you may add to a covered work material governed by the terms\n");
			printf("of that license document, provided that the further restriction does\n");
			printf("not survive such relicensing or conveying.\n");
			printf("\n");
			printf("  If you add terms to a covered work in accord with this section, you\n");
			printf("must place, in the relevant source files, a statement of the\n");
			printf("additional terms that apply to those files, or a notice indicating\n");
			printf("where to find the applicable terms.\n");
			printf("\n");
			printf("  Additional terms, permissive or non-permissive, may be stated in the\n");
			printf("form of a separately written license, or stated as exceptions;\n");
			printf("the above requirements apply either way.\n");
			printf("\n");
			printf("  8. Termination.\n");
			printf("\n");
			printf("  You may not propagate or modify a covered work except as expressly\n");
			printf("provided under this License.  Any attempt otherwise to propagate or\n");
			printf("modify it is void, and will automatically terminate your rights under\n");
			printf("this License (including any patent licenses granted under the third\n");
			printf("paragraph of section 11).\n");
			printf("\n");
			printf("  However, if you cease all violation of this License, then your\n");
			printf("license from a particular copyright holder is reinstated (a)\n");
			printf("provisionally, unless and until the copyright holder explicitly and\n");
			printf("finally terminates your license, and (b) permanently, if the copyright\n");
			printf("holder fails to notify you of the violation by some reasonable means\n");
			printf("prior to 60 days after the cessation.\n");
			printf("\n");
			printf("  Moreover, your license from a particular copyright holder is\n");
			printf("reinstated permanently if the copyright holder notifies you of the\n");
			printf("violation by some reasonable means, this is the first time you have\n");
			printf("received notice of violation of this License (for any work) from that\n");
			printf("copyright holder, and you cure the violation prior to 30 days after\n");
			printf("your receipt of the notice.\n");
			printf("\n");
			printf("  Termination of your rights under this section does not terminate the\n");
			printf("licenses of parties who have received copies or rights from you under\n");
			printf("this License.  If your rights have been terminated and not permanently\n");
			printf("reinstated, you do not qualify to receive new licenses for the same\n");
			printf("material under section 10.\n");
			printf("\n");
			printf("  9. Acceptance Not Required for Having Copies.\n");
			printf("\n");
			printf("  You are not required to accept this License in order to receive or\n");
			printf("run a copy of the Program.  Ancillary propagation of a covered work\n");
			printf("occurring solely as a consequence of using peer-to-peer transmission\n");
			printf("to receive a copy likewise does not require acceptance.  However,\n");
			printf("nothing other than this License grants you permission to propagate or\n");
			printf("modify any covered work.  These actions infringe copyright if you do\n");
			printf("not accept this License.  Therefore, by modifying or propagating a\n");
			printf("covered work, you indicate your acceptance of this License to do so.\n");
			printf("\n");
			printf("  10. Automatic Licensing of Downstream Recipients.\n");
			printf("\n");
			printf("  Each time you convey a covered work, the recipient automatically\n");
			printf("receives a license from the original licensors, to run, modify and\n");
			printf("propagate that work, subject to this License.  You are not responsible\n");
			printf("for enforcing compliance by third parties with this License.\n");
			printf("\n");
			printf("  An \"entity transaction\" is a transaction transferring control of an\n");
			printf("organization, or substantially all assets of one, or subdividing an\n");
			printf("organization, or merging organizations.  If propagation of a covered\n");
			printf("work results from an entity transaction, each party to that\n");
			printf("transaction who receives a copy of the work also receives whatever\n");
			printf("licenses to the work the party's predecessor in interest had or could\n");
			printf("give under the previous paragraph, plus a right to possession of the\n");
			printf("Corresponding Source of the work from the predecessor in interest, if\n");
			printf("the predecessor has it or can get it with reasonable efforts.\n");
			printf("\n");
			printf("  You may not impose any further restrictions on the exercise of the\n");
			printf("rights granted or affirmed under this License.  For example, you may\n");
			printf("not impose a license fee, royalty, or other charge for exercise of\n");
			printf("rights granted under this License, and you may not initiate litigation\n");
			printf("(including a cross-claim or counterclaim in a lawsuit) alleging that\n");
			printf("any patent claim is infringed by making, using, selling, offering for\n");
			printf("sale, or importing the Program or any portion of it.\n");
			printf("\n");
			printf("  11. Patents.\n");
			printf("\n");
			printf("  A \"contributor\" is a copyright holder who authorizes use under this\n");
			printf("License of the Program or a work on which the Program is based.  The\n");
			printf("work thus licensed is called the contributor's \"contributor version\".\n");
			printf("\n");
			printf("  A contributor's \"essential patent claims\" are all patent claims\n");
			printf("owned or controlled by the contributor, whether already acquired or\n");
			printf("hereafter acquired, that would be infringed by some manner, permitted\n");
			printf("by this License, of making, using, or selling its contributor version,\n");
			printf("but do not include claims that would be infringed only as a\n");
			printf("consequence of further modification of the contributor version.  For\n");
			printf("purposes of this definition, \"control\" includes the right to grant\n");
			printf("patent sublicenses in a manner consistent with the requirements of\n");
			printf("this License.\n");
			printf("\n");
			printf("  Each contributor grants you a non-exclusive, worldwide, royalty-free\n");
			printf("patent license under the contributor's essential patent claims, to\n");
			printf("make, use, sell, offer for sale, import and otherwise run, modify and\n");
			printf("propagate the contents of its contributor version.\n");
			printf("\n");
			printf("  In the following three paragraphs, a \"patent license\" is any express\n");
			printf("agreement or commitment, however denominated, not to enforce a patent\n");
			printf("(such as an express permission to practice a patent or covenant not to\n");
			printf("sue for patent infringement).  To \"grant\" such a patent license to a\n");
			printf("party means to make such an agreement or commitment not to enforce a\n");
			printf("patent against the party.\n");
			printf("\n");
			printf("  If you convey a covered work, knowingly relying on a patent license,\n");
			printf("and the Corresponding Source of the work is not available for anyone\n");
			printf("to copy, free of charge and under the terms of this License, through a\n");
			printf("publicly available network server or other readily accessible means,\n");
			printf("then you must either (1) cause the Corresponding Source to be so\n");
			printf("available, or (2) arrange to deprive yourself of the benefit of the\n");
			printf("patent license for this particular work, or (3) arrange, in a manner\n");
			printf("consistent with the requirements of this License, to extend the patent\n");
			printf("license to downstream recipients.  \"Knowingly relying\" means you have\n");
			printf("actual knowledge that, but for the patent license, your conveying the\n");
			printf("covered work in a country, or your recipient's use of the covered work\n");
			printf("in a country, would infringe one or more identifiable patents in that\n");
			printf("country that you have reason to believe are valid.\n");
			printf("\n");
			printf("  If, pursuant to or in connection with a single transaction or\n");
			printf("arrangement, you convey, or propagate by procuring conveyance of, a\n");
			printf("covered work, and grant a patent license to some of the parties\n");
			printf("receiving the covered work authorizing them to use, propagate, modify\n");
			printf("or convey a specific copy of the covered work, then the patent license\n");
			printf("you grant is automatically extended to all recipients of the covered\n");
			printf("work and works based on it.\n");
			printf("\n");
			printf("  A patent license is \"discriminatory\" if it does not include within\n");
			printf("the scope of its coverage, prohibits the exercise of, or is\n");
			printf("conditioned on the non-exercise of one or more of the rights that are\n");
			printf("specifically granted under this License.  You may not convey a covered\n");
			printf("work if you are a party to an arrangement with a third party that is\n");
			printf("in the business of distributing software, under which you make payment\n");
			printf("to the third party based on the extent of your activity of conveying\n");
			printf("the work, and under which the third party grants, to any of the\n");
			printf("parties who would receive the covered work from you, a discriminatory\n");
			printf("patent license (a) in connection with copies of the covered work\n");
			printf("conveyed by you (or copies made from those copies), or (b) primarily\n");
			printf("for and in connection with specific products or compilations that\n");
			printf("contain the covered work, unless you entered into that arrangement,\n");
			printf("or that patent license was granted, prior to 28 March 2007.\n");
			printf("\n");
			printf("  Nothing in this License shall be construed as excluding or limiting\n");
			printf("any implied license or other defenses to infringement that may\n");
			printf("otherwise be available to you under applicable patent law.\n");
			printf("\n");
			printf("  12. No Surrender of Others' Freedom.\n");
			printf("\n");
			printf("  If conditions are imposed on you (whether by court order, agreement or\n");
			printf("otherwise) that contradict the conditions of this License, they do not\n");
			printf("excuse you from the conditions of this License.  If you cannot convey a\n");
			printf("covered work so as to satisfy simultaneously your obligations under this\n");
			printf("License and any other pertinent obligations, then as a consequence you may\n");
			printf("not convey it at all.  For example, if you agree to terms that obligate you\n");
			printf("to collect a royalty for further conveying from those to whom you convey\n");
			printf("the Program, the only way you could satisfy both those terms and this\n");
			printf("License would be to refrain entirely from conveying the Program.\n");
			printf("\n");
			printf("  13. Use with the GNU Affero General Public License.\n");
			printf("\n");
			printf("  Notwithstanding any other provision of this License, you have\n");
			printf("permission to link or combine any covered work with a work licensed\n");
			printf("under version 3 of the GNU Affero General Public License into a single\n");
			printf("combined work, and to convey the resulting work.  The terms of this\n");
			printf("License will continue to apply to the part which is the covered work,\n");
			printf("but the special requirements of the GNU Affero General Public License,\n");
			printf("section 13, concerning interaction through a network will apply to the\n");
			printf("combination as such.\n");
			printf("\n");
			printf("  14. Revised Versions of this License.\n");
			printf("\n");
			printf("  The Free Software Foundation may publish revised and/or new versions of\n");
			printf("the GNU General Public License from time to time.  Such new versions will\n");
			printf("be similar in spirit to the present version, but may differ in detail to\n");
			printf("address new problems or concerns.\n");
			printf("\n");
			printf("  Each version is given a distinguishing version number.  If the\n");
			printf("Program specifies that a certain numbered version of the GNU General\n");
			printf("Public License \"or any later version\" applies to it, you have the\n");
			printf("option of following the terms and conditions either of that numbered\n");
			printf("version or of any later version published by the Free Software\n");
			printf("Foundation.  If the Program does not specify a version number of the\n");
			printf("GNU General Public License, you may choose any version ever published\n");
			printf("by the Free Software Foundation.\n");
			printf("\n");
			printf("  If the Program specifies that a proxy can decide which future\n");
			printf("versions of the GNU General Public License can be used, that proxy's\n");
			printf("public statement of acceptance of a version permanently authorizes you\n");
			printf("to choose that version for the Program.\n");
			printf("\n");
			printf("  Later license versions may give you additional or different\n");
			printf("permissions.  However, no additional obligations are imposed on any\n");
			printf("author or copyright holder as a result of your choosing to follow a\n");
			printf("later version.\n");
			printf("\n");
			printf("  15. Disclaimer of Warranty.\n");
			printf("\n");
			printf("  THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY\n");
			printf("APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT\n");
			printf("HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY\n");
			printf("OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,\n");
			printf("THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR\n");
			printf("PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM\n");
			printf("IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF\n");
			printf("ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n");
			printf("\n");
			printf("  16. Limitation of Liability.\n");
			printf("\n");
			printf("  IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING\n");
			printf("WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS\n");
			printf("THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY\n");
			printf("GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE\n");
			printf("USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF\n");
			printf("DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD\n");
			printf("PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),\n");
			printf("EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF\n");
			printf("SUCH DAMAGES.\n");
			printf("\n");
			printf("  17. Interpretation of Sections 15 and 16.\n");
			printf("\n");
			printf("  If the disclaimer of warranty and limitation of liability provided\n");
			printf("above cannot be given local legal effect according to their terms,\n");
			printf("reviewing courts shall apply local law that most closely approximates\n");
			printf("an absolute waiver of all civil liability in connection with the\n");
			printf("Program, unless a warranty or assumption of liability accompanies a\n");
			printf("copy of the Program in return for a fee.\n");
			printf("\n");
			printf("                     END OF TERMS AND CONDITIONS\n");
			break;

		// General Help...
		case help_general:
			printf("%s%s\n%s", COL_BLUE, program_banner, RESET);
			printf("Nipper is a  Network Infrastructure  Configuration Parser.  Nipper takes\n");
			printf("a network infrastructure  device configuration,  processes the  file and\n");
			printf("produces  a report  which can  include detailed a  security audit  and a\n");
			printf("configuration report.\n\n");
			printf("By default, input is retrieved from stdin and is output (in HTML format)\n");
			printf("to stdout.\n\n");

			printf("%sCommand:%s\n", COL_BLUE, RESET);
			printf("    %s%s [Options]%s\n\n", COL_GREEN, argv[0], RESET);

			printf("%sGeneral Options:%s\n", COL_BLUE, RESET);
			printf("    %s--input=<file>%s\n", COL_GREEN, RESET);
			printf("    Specifies a  device configuration  file to  process.  For CheckPoint\n");
			printf("    Firewall-1  configurations,  the  input should be the conf directory\n");
			printf("    (or the database directory).\n\n");
			printf("    %s--output=<file> | --report=<file>%s\n", COL_GREEN, RESET);
			printf("    Specified an output file for the report.\n\n");
			printf("    %s--version%s\n", COL_GREEN, RESET);
			printf("    Displays the program version.\n\n");

			printf("%sExample:%s\n", COL_BLUE, RESET);
			printf("    The  example   below  will   process  a   Cisco   IOS-based   router\n");
			printf("    configuration file called ios.conf  and output  the report to a file\n");
			printf("    called report.html.\n\n");
			printf("    %s%s --ios-router --input=ios.conf --output=report.html%s\n\n", COL_GREEN, argv[0], RESET);
			showHelpFooter();
			break;

		// Device Types...
		case help_device_types:
			printf("%s%s\n%s", COL_BLUE, program_banner, RESET);
			printf("Nipper supports  a  number of  different types  of network device.  This\n");
			printf("version contains support for the following devices:\n\n");
			printf("    CMD Option       Device Type\n");
			printf("    ====================================================\n");
			printf("    --auto           Auto-Detect Device (Default)\n");
			printf("    --3com-firewall  3Com SuperStack 3 Firewall\n");
			printf("    --accelar        Bay Networks Accelar\n");
			printf("    --cp-firewall    CheckPoint Firewall Module\n");
			printf("    --cp-management  CheckPoint Management Module\n");
			printf("    --ios-router     Cisco IOS-based Router\n");
			printf("    --ios-catalyst   Cisco IOS-based Catalyst Switch\n");
			printf("    --pix            Cisco PIX-based Firewall\n");
			printf("    --asa            Cisco ASA-based Firewall\n");
			printf("    --fwsm           Cisco FWSM-based Router\n");
			printf("    --catos          Cisco CatOS-based Catalyst\n");
			printf("    --nmp            Cisco NMP-based Catalyst\n");
			printf("    --css            Cisco Content Services Switch\n");
			printf("    --procurve       HP ProCurve Switches\n");
			printf("    --screenos       Juniper NetScreen Firewall\n");
			printf("    --nokiaip        Nokia IP Firewall\n");
			printf("    --passport       Nortel Passport Device\n");
			printf("    --nortel-switch  Nortel Ethernet Routing Switch 8300\n");
			printf("    --sonicos        SonicWall SonicOS Firewall\n\n");
			showHelpFooter();
			break;

		// Device Usage...
		case help_device_usage:
			printf("%s%s\n%s", COL_BLUE, program_banner, RESET);
			printf("Nipper performs  various  checks to  ensure that  the device  type that\n");
			printf("has been  specified matches the  configuration file.  Additionally, the\n");
			printf("security issues  reported by Nipper  can depend  on what  the device is\n");
			printf("used for.\n\n");
			printf("%sAdvanced Device Options:%s\n\n", COL_BLUE, RESET);
			printf("    %s--force%s\n", COL_GREEN, RESET);
			printf("    Force Nipper to bypass any configuration type checks.\n\n");
			printf("    %s--location=<edge | internal>%s\n", COL_GREEN, RESET);
			printf("    Where is the device located.\n\n");
			printf("    %s--model=<device model>%s\n", COL_GREEN, RESET);
			printf("    Specify a device model, such as 7200VXR for a Cisco 7200VXR.\n\n");
			printf("    %s--os-version=<device os version>%s\n", COL_GREEN, RESET);
			printf("    A device  OS version  can be provided  to Nipper  for the  security\n");
			printf("    audit. For example 12.2.12.2 or 5.10.8. Note: Do not add any spaces\n");
			printf("    and, if the version numbers are seperated, use decimal places.\n\n");
			showHelpFooter();
			break;

		// Report Formats...
		case help_report_formats:
			printf("%s%s\n%s", COL_BLUE, program_banner, RESET);
			printf("Nipper supports a number of different report formats. They are:\n\n");
			printf("    CMD Option      Report Format\n");
			printf("    =============================\n");
			printf("    --html          HTML (default)\n");
			printf("    --latex         Latex\n");
			printf("    --text          Text\n");
			printf("    --xml           XML\n\n");
			showHelpFooter();
			break;

		// Advanced Report Options...
		case help_report_options:
			printf("%s%s\n%s", COL_BLUE, program_banner, RESET);
			printf("These reporting options apply to all report output.\n\n");
			printf("    %s--company-name=<name>%s\n", COL_GREEN, RESET);
			printf("    Replace the 'nipper recommends...' in the report output to something\n");
			printf("    else. So for the Acme company, it would read, 'Acme recommends...'.\n\n");
			printf("    %s--device-name=<name>%s\n", COL_GREEN, RESET);
			printf("    If a device configuration  file does not  contain a device name,  it\n");
			printf("    can be specified using this option.\n\n");
			printf("    %s--order-by-rating%s\n", COL_GREEN, RESET);
			printf("    Order the identified security issues using the overall rating.\n\n");
			printf("    %s--order-by-config%s\n", COL_GREEN, RESET);
			printf("    Order the  identified  security  issues into  related  configuration\n");
			printf("    issues (e.g. group SNMP issues together).\n\n");
			//printf("    %s--no-names%s\n", COL_GREEN, RESET);
			//printf("    Convert host and network names to IP addresses where possible.\n\n");
			printf("    %s--rule-comments%s\n", COL_GREEN, RESET);
			printf("    Shows filter rule comments in the rules output.\n\n");
			showHelpFooter();
			break;

		// Report Options to include report sections...
		case help_report_appendix:
			printf("%s%s\n%s", COL_BLUE, program_banner, RESET);
			printf("The following  report options  determine which sections  are included in\n");
			printf("the report output. The default is to include all sections.\n\n");
			printf("    %s--no-config%s\n", COL_GREEN, RESET);
			printf("    This option disables the configuration report section.\n\n");
			printf("    %s--no-audit%s\n", COL_GREEN, RESET);
			printf("    This option disables the security audit of the device configuration.\n\n");
			printf("    %s--no-appendix%s\n", COL_GREEN, RESET);
			printf("    Disables  the output  of  the entire  report  appendix  section.  By\n");
			printf("    default an appendix section is generated and added to the report.\n\n");
			printf("    %s--no-abbreviations%s\n", COL_GREEN, RESET);
			printf("    Disables the output of an abbreviations section in the appendix.\n\n");
			printf("    %s--no-ports%s\n", COL_GREEN, RESET);
			printf("    Disables the output of the common ports section in the appendix.\n\n");
			printf("    %s--no-protocols%s\n", COL_GREEN, RESET);
			printf("    Disables the output of the IP protocols section in the appendix.\n\n");
			printf("    %s--no-icmptypes%s\n", COL_GREEN, RESET);
			printf("    Disables the output of a ICMP types section in the appendix.\n\n");
			printf("    %s--no-glossary%s\n", COL_GREEN, RESET);
			printf("    Disables the output of a glossary section in the appendix.\n\n");
			printf("    %s--no-logging%s\n", COL_GREEN, RESET);
			printf("    Disables the output of the logging levels section in the appendix.\n\n");
			printf("    %s--no-timezones%s\n", COL_GREEN, RESET);
			printf("    Disables the output of the time zones section in the appendix.\n\n");
			printf("    %s--no-version%s\n", COL_GREEN, RESET);
			printf("    Disables the output of the nipper version section in the appendix.\n\n");
			showHelpFooter();
			break;

		// Report HTML options...
		case help_report_html:
			printf("%s%s\n%s", COL_BLUE, program_banner, RESET);
			printf("These report options apply only to the HTML report file format.\n\n");
			printf("    %s--stylesheet=<file>%s\n", COL_GREEN, RESET);
			printf("    Supply an external Cascading Style Sheet (CSS) for use with the HTML\n");
			printf("    -based reports.  If this  option is not  supplied a  default  CSS is\n");
			printf("    embeded. The  supplied CSS  file will be  embeded within  the report\n");
			printf("    output.\n\n");
			showHelpFooter();
			break;

		// Report Latex Options...
		case help_report_latex:
			printf("%s%s\n%s", COL_BLUE, program_banner, RESET);
			printf("These report options apply only to the Latex report file format.\n\n");
			printf("    %s--paper=<Latex paper size>%s\n", COL_GREEN, RESET);
			printf("    This option can be used to configure the Latex document  paper size.\n");
			printf("    The   default  paper   size  is  'a4paper'.   Refer  to   the  Latex\n");
			printf("    documentation for other settings.\n\n");
			printf("    %s--documentclass=<Latex document class>%s\n", COL_GREEN, RESET);
			printf("    This option can be used to configure  the Latex document  class. The\n");
			printf("    default  document  class   is   'article'.   Refer   to   the  Latex\n");
			printf("    documentation for other settings.\n\n");
			showHelpFooter();
			break;

		// Security Auditing ACL options...
		case help_audit_acl:
			printf("%s%s\n%s", COL_BLUE, program_banner, RESET);
			printf("These  options  only apply  to the  security  auditing  of  the  network\n");
			printf("filtering. Each -- option can start with a --no-<option>  to disable the\n");
			printf("a check.\n\n");
			printf("    %s--ignore-non-tcp-udp%s\n", COL_GREEN, RESET);
			printf("    Ignores filters that do not use TCP or UDP protocols.\n\n");
			printf("    %s--filter-enabled%s\n", COL_GREEN, RESET);
			printf("    Checks that network filtering is enabled.\n\n");
			printf("    %s--filter-default-allow%s\n", COL_GREEN, RESET);
			printf("    Checks for a default filtering action to allow traffic.\n\n");
			printf("    %s--filter-any-source%s\n", COL_GREEN, RESET);
			printf("    Checks for allowing rules from any source address.\n\n");
			printf("    %s--filter-net-source%s\n", COL_GREEN, RESET);
			printf("    Checks for allowing rules from a source network address.\n\n");
			printf("    %s--filter-any-source-port%s\n", COL_GREEN, RESET);
			printf("    Checks for allowing any source port rules.\n\n");
			printf("    %s--filter-range-source-port%s\n", COL_GREEN, RESET);
			printf("    Checks for allowing a range of source ports rules.\n\n");
			printf("    %s--filter-any-dest%s\n", COL_GREEN, RESET);
			printf("    Checks for allowing any network destination address rules.\n\n");
			printf("    %s--filter-net-dest%s\n", COL_GREEN, RESET);
			printf("    Checks for allowing network destination rules.\n\n");
			printf("    %s--filter-any-dest-port%s\n", COL_GREEN, RESET);
			printf("    Checks for rules allowing any destination ports.\n\n");
			printf("    %s--filter-range-dest-port%s\n", COL_GREEN, RESET);
			printf("    Checks for rules allowing a range of destination ports.\n\n");
			printf("    %s--filter-log-allow%s\n", COL_GREEN, RESET);
			printf("    Checks that allow rules log.\n\n");
			printf("    %s--filter-log-deny%s\n", COL_GREEN, RESET);
			printf("    Checks that denied rules log.\n\n");
			printf("    %s--filter-end-log-and-deny%s\n", COL_GREEN, RESET);
			printf("    Checks that rule lists end with a deny all and log.\n\n");
			printf("    %s--filter-reject%s\n", COL_GREEN, RESET);
			printf("    Checks for rules that reject.\n\n");
			printf("    %s--filter-bypass%s\n", COL_GREEN, RESET);
			printf("    Checks for rules that bypass the filtering.\n\n");
			printf("    %s--filter-default%s\n", COL_GREEN, RESET);
			printf("    Checks for rules that allow a default action.\n\n");
			printf("    %s--filter-comments%s\n", COL_GREEN, RESET);
			printf("    Check for rules with comments\n\n");
			printf("    %s--filter-disabled%s\n", COL_GREEN, RESET);
			printf("    Checks for disabled rules.\n\n");
			printf("    %s--filter-unused%s\n", COL_GREEN, RESET);
			printf("    Checks for unused rules at the end of a rules list.\n\n");
			printf("    %s--filter-clear-text%s\n", COL_GREEN, RESET);
			printf("    Checks for rules  allowing common  clear text protocol services such");
			printf("    as Telnet, FTP and SMTP.\n\n");
			printf("    %s--filter-duplicates%s\n", COL_GREEN, RESET);
			printf("    Checks for rules that duplicate/overlapping other rules.\n\n");
			printf("    %s--filter-contradicts%s\n", COL_GREEN, RESET);
			printf("    Checks for rules that contradict other rules.\n\n");
			printf("    %s--filter-unused-lists%s\n", COL_GREEN, RESET);
			printf("    Checks for unused rule lists.\n\n");
			showHelpFooter();
			break;

		// Security Auditing Password Options...
		case help_audit_password:
			printf("%s%s\n%s", COL_BLUE, program_banner, RESET);
			printf("These options  apply to the  password security auditing.  In addition to\n");
			printf("user passwords,  other authentication strings are audited such as shared\n");
			printf("keys and SNMP community strings.\n\n");
			printf("The password strength testing options can be used with --no to disable a\n");
			printf("check.\n\n");
			printf("    %s--no-passwords%s\n", COL_GREEN, RESET);
			printf("    Removes passwords  from the  output. However,  passwords are  always\n");
			printf("    checked against defaults and for password strength.\n\n");
			printf("    %s--john=<file>%s\n", COL_GREEN, RESET);
			printf("    Output the Cisco type 5  passwords in a  file that  can then  be run\n");
			printf("    through john-the-ripper.\n\n");
			printf("    %s--dictionary=<file>%s\n", COL_GREEN, RESET);
			printf("    Use a dictionary  file to  check the  passwords  and  keys  are  not\n");
			printf("    dictionary-based  words.  If this  option is  not specified  a small\n");
			printf("    number of  built-in  passwords  are  used  instead.  This option  is\n");
			printf("    not used  to break  MD5 passwords,  only compare  passwords  already\n");
			printf("    known.\n\n");
			printf("    %s--pass-length=<length>%s\n", COL_GREEN, RESET);
			printf("    Check the minimum password length. (default is 8 characters)\n\n");
			printf("    %s--pass-uppers%s\n", COL_GREEN, RESET);
			printf("    Check that the password includes uppercase chars. (default is yes)\n\n");
			printf("    %s--pass-lowers%s\n", COL_GREEN, RESET);
			printf("    Check that the password includes lowercase chars. (default is yes)\n\n");
			printf("    %s--pass-either%s\n", COL_GREEN, RESET);
			printf("    Check that the password includes either case chars. (default is no)\n\n");
			printf("    %s--pass-numbers%s\n", COL_GREEN, RESET);
			printf("    Check that the password includes numbers. (default is yes)\n\n");
			printf("    %s--pass-specials%s\n", COL_GREEN, RESET);
			printf("    Check that the password includes special chars. (default is yes)\n\n");
			printf("    %s--pass-char-repeat=<number>%s\n", COL_GREEN, RESET);
			printf("    Check that the password does not repeat a char. (default is 3)\n\n");
			printf("    %s--pass-username%s\n", COL_GREEN, RESET);
			printf("    Check that the password is not username-based. (default is yes)\n\n");
			printf("    %s--pass-hostname%s\n", COL_GREEN, RESET);
			printf("    Check that the password is not hostname-based. (default is yes)\n\n");
			printf("    %s--pass-device-info%s\n", COL_GREEN, RESET);
			printf("    Check that the password is not based on device information,  such as\n");
			printf("    the device manufacturer or model. (default is yes)\n\n");
			printf("    %s--pass-dict-subst%s\n", COL_GREEN, RESET);
			printf("    Check  that  the  password  is   not  dictionary-based  with  common\n");
			printf("    character substitutions, such as i = 1. (default is yes)\n\n");
			printf("    %s--pass-dict-append%s\n", COL_GREEN, RESET);
			printf("    Check  that  the  password  is   not  dictionary-based  with  common\n");
			printf("    characters appended, such as 1, 123 or !. (default is yes)\n\n");
			printf("    %s--pass-char-seq%s\n", COL_GREEN, RESET);
			printf("    Check that the password does  not include common character squences,\n");
			printf("    such as 1234, abcd and qwerty. (default is yes)\n\n");
			showHelpFooter();
			break;

		// Other Security Auditing Options...
		case help_audit_misc:
			printf("%s%s\n%s", COL_BLUE, program_banner, RESET);
			printf("These options apply to the security auditing.\n\n");
			printf("    %s--timeout=<seconds>%s\n", COL_GREEN, RESET);
			printf("    Specify the  number of  seconds that  connection timeouts  should be\n");
			printf("    less than or equal to.  If timeouts are  less than this,  a security\n");
			printf("    will be generated in the report. The default is 10 minutes.\n\n");
			showHelpFooter();
			break;

		// Other SNMP Options...
		case help_snmp:
			printf("%s%s\n%s", COL_BLUE, program_banner, RESET);
			printf("These  options apply  to remote  SNMP configuration retrival from  Cisco\n");
			printf("devices.  Older Cisco devices make  use of a  slightly different method.\n");
			printf("The old method works with IOS devices up to version 12.x.  Newer methods\n");
			printf("are supported with IOS version 12.0  (some with 11.2P).  This requires a\n");
			printf("local TFTP server and the snmpget command.\n\n");
			printf("    %s--snmp-ip=<ip address>%s\n", COL_GREEN, RESET);
			printf("    Specify the  IP address  of the Cisco Device  to retrieve the config\n");
			printf("    from.\n\n");
			printf("    %s--snmp-community<community>%s\n", COL_GREEN, RESET);
			printf("    The snmp community to be used with the above. A default of 'private'\n");
			printf("    will be used if not specified.\n\n");
			showHelpFooter();
			break;

		// The debug options (hidden)...
		case help_debug:
			printf("%s%s\n%s", COL_BLUE, program_banner, RESET);
			printf("These are the Nipper debug options, useful for working out what has gone\n");
			printf("AWOL.  These options can  ouput a  lot of  information  and  disrupt the\n");
			printf("normal report output.\n\n");
			printf("    %s--debug%s\n", COL_GREEN, RESET);
			printf("    Outputs additional  information that most users  would not find very\n");
			printf("    helpful, but  is useful  in understanding  how the  configuration is\n");
			printf("    interpreted. Using the debug option overrides all other output.\n\n");
			printf("    %s--debug-abbreviations%s\n", COL_GREEN, RESET);
			printf("    Shows a list of all the  abbreviations that were  not processed. The\n");
			printf("    list is output  to stdout  and lists the  number of hits  each entry\n");
			printf("    has had. Not all of the items listed will be valid abbreviations.\n\n");
			printf("    %s--debug-lnp%s\n", COL_GREEN, RESET);
			printf("    Output the configuration lines not processed (to screen only).\n\n");
			showHelpFooter();
			break;

		// External Configuration file...
		case help_config_file:
			printf("%s%s\n%s", COL_BLUE, program_banner, RESET);
			printf("Nipper can be configured using an external configuration file. This file\n");
			printf("can be specified on the  command line or  Nipper will load configuration\n");
#if !defined(__WIN32__)
			printf("settings from '/etc/nipper.conf'.\n\n");
#else
			printf("settings from 'nipper.ini'.\n\n");
#endif
			printf("    %s--config=<file>%s\n", COL_GREEN, RESET);
			printf("    Specifies a Nipper configuration file.\n\n");
			break;

		case help_errorheader:
			printf("%s%s\n%s", COL_BLUE, program_banner, RESET);
			break;

		case help_error_params:
			printf("%s%s\n%s", COL_BLUE, program_banner, RESET);
			printf("%sERROR: Invalid command line options specified.%s\n\n", COL_RED, RESET);
			printf("COMMAND: %s", COL_GREEN);
			for (tempInt = 0; tempInt < argc; tempInt++)
			{
				if (tempInt == paramno)
#if !defined(__WIN32__)
					printf("%s%s%s ", COL_RED, argv[tempInt], COL_GREEN);
#else
					printf(">>>> %s <<<< ", argv[tempInt]);
#endif
				else
					printf("%s ", argv[tempInt]);
			}
			printf("%s\n\n", RESET);
			showHelpFooter();
			break;
	}
}


// Process the command line arguements...
int processCommandArgs(int argc, char *argv[], Nipper *nipper)
{
	// Variables...
	int argLoop = 0;
	int tempInt = 0;

	// Get program parameters...
	for (argLoop = 1; argLoop < argc; argLoop++)
	{

		// -------------------------
		//   Reporting Options...
		// -------------------------

		// Set Report Format...
		if ((strcmp("--output-format=html", argv[argLoop]) == 0) || (strcmp("--report-format=html", argv[argLoop]) == 0) || (strcmp("--html", argv[argLoop]) == 0))
			nipper->config->reportFormat = Config::HTML;
		else if ((strcmp("--output-format=xml", argv[argLoop]) == 0) || (strcmp("--report-format=xml", argv[argLoop]) == 0) || (strcmp("--xml", argv[argLoop]) == 0))
			nipper->config->reportFormat = Config::XML;
		else if ((strcmp("--output-format=latex", argv[argLoop]) == 0) || (strcmp("--report-format=latex", argv[argLoop]) == 0) || (strcmp("--latex", argv[argLoop]) == 0))
			nipper->config->reportFormat = Config::Latex;
		else if ((strcmp("--output-format=text", argv[argLoop]) == 0) || (strcmp("--report-format=text", argv[argLoop]) == 0) || (strcmp("--text", argv[argLoop]) == 0))
			nipper->config->reportFormat = Config::Text;
		else if (strcmp("--debug", argv[argLoop]) == 0)
			nipper->config->reportFormat = Config::Debug;

		// Company name specified...
		else if (strncmp("--company-name=", argv[argLoop], 15) == 0)
			nipper->config->companyName = argv[argLoop] + 15;

		// Password output...
		else if (strcmp("--no-passwords", argv[argLoop]) == 0)
			nipper->config->includePasswordsInReport = false;

		// Show host / network names instead of IP addresses (where possible)...
		else if (strcmp("--no-names", argv[argLoop]) == 0)
			nipper->config->convertNamesToAddresses = true;

		// Issue ordering...
		else if (strcmp("--order-by-rating", argv[argLoop]) == 0)
			nipper->config->issueOrdering = Config::byOverallRating;
		else if (strcmp("--order-by-config", argv[argLoop]) == 0)
			nipper->config->issueOrdering = Config::byRelatedConfiguration;

		// HTML Stylesheet...
		else if (strncmp("--stylesheet=", argv[argLoop], 13) == 0)
			nipper->config->htmlStylesheet = argv[argLoop] + 13;

		// Latex paper size...
		else if (strncmp("--paper=", argv[argLoop], 8) == 0)
			nipper->config->latexPaper = argv[argLoop] + 8;

		// Latex document class...
		else if (strncmp("--documentclass=", argv[argLoop], 16) == 0)
			nipper->config->latexDocumentClass = argv[argLoop] + 16;

		// Debug options...
		else if (strcmp("--debug-lnp", argv[argLoop]) == 0)
			nipper->config->debugLinesNotProcessed = true;
		else if (strcmp("--debug-abbreviations", argv[argLoop]) == 0)
			nipper->config->debugAbbreviations = true;

		// Include rule comments...
		else if (strcmp("--rule-comments", argv[argLoop]) == 0)
			nipper->config->includeFilterRuleComments = true;
		else if (strcmp("--no-rule-comments", argv[argLoop]) == 0)
			nipper->config->includeFilterRuleComments = false;

		// These next few change which sections are included in the
		// report output.

		// Do not perform a security audit...
		else if (strcmp("--no-audit", argv[argLoop]) == 0)
			nipper->config->includeSecurityAudit = false;

		// Perform a compliance check...
		else if (strcmp("--compliance", argv[argLoop]) == 0)
			nipper->config->includeComplianceCheck = true;

		// Do not include a configuration report...
		else if (strcmp("--no-config", argv[argLoop]) == 0)
			nipper->config->includeConfigurationReport = false;

		// Appendix...
		else if (strcmp("--no-appendix", argv[argLoop]) == 0)
			nipper->config->includeAppendixSection = false;

		// Glossary...
		else if (strcmp("--no-glossary", argv[argLoop]) == 0)
			nipper->config->includeGlossary = false;

		// Common Ports...
		else if (strcmp("--no-ports", argv[argLoop]) == 0)
			nipper->config->includeNetworkPorts = false;

		// Protocols...
		else if (strcmp("--no-protocols", argv[argLoop]) == 0)
			nipper->config->includeIPProtocols = false;

		// ICMP Types...
		else if (strcmp("--no-icmptypes", argv[argLoop]) == 0)
			nipper->config->includeICMPTypes = false;

		// Nipper Version Appendix...
		else if (strcmp("--no-version", argv[argLoop]) == 0)
			nipper->config->includeNipperVersion = false;

		// Logging Levels Appendix...
		else if (strcmp("--no-logging", argv[argLoop]) == 0)
			nipper->config->includeLoggingLevels = false;

		// Time Zone Appendix...
		else if (strcmp("--no-timezones", argv[argLoop]) == 0)
			nipper->config->includeTimeZones = false;

		// Abbreviations...
		else if (strcmp("--no-abbreviations", argv[argLoop]) == 0)
			nipper->config->includeAbbreviations = false;


		// -------------------------
		//   Main Options...
		// -------------------------

		// Input file (defaults to stdin)...
		else if ((strncmp("--input=", argv[argLoop], 8) == 0) && (strlen(argv[argLoop]) > 8))
			nipper->config->inputSource = argv[argLoop] + 8;

		// Output file (defaults to stdout)...
		else if (((strncmp("--output=", argv[argLoop], 9) == 0) || (strncmp("--report=", argv[argLoop], 9) == 0)) && (strlen(argv[argLoop]) > 9))
			nipper->config->outputDestination = argv[argLoop] + 9;

		// OS Version...
		else if ((strncmp("--os-version=", argv[argLoop], 13) == 0) && (strlen(argv[argLoop]) > 13))
			nipper->config->osVersion = argv[argLoop] + 13;

		// Remote Cisco Device IP...
		else if (strncmp("--snmp-ip=", argv[argLoop], 10) == 0)
			nipper->config->snmpAddress = argv[argLoop] + 10;

		// Remote Cisco Device SNMP read/write community...
		else if (strncmp("--snmp-community=", argv[argLoop], 17) == 0)
			nipper->config->snmpCommunity = argv[argLoop] + 17;

		// Configuration File...
		else if ((strncmp("--config=", argv[argLoop], 9) == 0) && (strlen(argv[argLoop]) > 9))
		{
			tempInt = nipper->config->setConfigFile(argv[argLoop] + 9);
			if (tempInt != 0)
			{
				showHelp(0, 0, help_errorheader);
				printf("%s\n", nipper->getErrorText(tempInt));
				showHelpFooter();
				return -1;
			}
		}

		// Set device type...
		else if ((strcmp("--ios-router", argv[argLoop]) == 0) || (strcmp("--ios", argv[argLoop]) == 0))
			nipper->config->deviceType = Config::CiscoIOSRouter;
		else if ((strcmp("--ios-switch", argv[argLoop]) == 0) || (strcmp("--ios-catalyst", argv[argLoop]) == 0))
			nipper->config->deviceType = Config::CiscoIOSCatalyst;
		else if (strcmp("--catos", argv[argLoop]) == 0)
			nipper->config->deviceType = Config::CiscoCatOSCatalyst;
		else if (strcmp("--nmp", argv[argLoop]) == 0)
			nipper->config->deviceType = Config::CiscoNMPCatalyst;
		else if (strcmp("--pix", argv[argLoop]) == 0)
			nipper->config->deviceType = Config::CiscoPIXFirewall;
		else if (strcmp("--asa", argv[argLoop]) == 0)
			nipper->config->deviceType = Config::CiscoASAFirewall;
		else if (strcmp("--fwsm", argv[argLoop]) == 0)
			nipper->config->deviceType = Config::CiscoFWSMFirewall;
		else if (strcmp("--css", argv[argLoop]) == 0)
			nipper->config->deviceType = Config::CiscoCSS;
		else if (strcmp("--3com-firewall", argv[argLoop]) == 0)
			nipper->config->deviceType = Config::ThreeComSuperStackFW;
		else if ((strcmp("--fw1", argv[argLoop]) == 0) || (strcmp("--firewall1", argv[argLoop]) == 0) || (strcmp("--cp-firewall", argv[argLoop]) == 0))
			nipper->config->deviceType = Config::CheckPointFirewall;
		else if (strcmp("--cp-management", argv[argLoop]) == 0)
			nipper->config->deviceType = Config::CheckPointManagement;
		else if (strcmp("--nokiaip", argv[argLoop]) == 0)
			nipper->config->deviceType = Config::NokiaIP;
		else if ((strcmp("--sonicwall", argv[argLoop]) == 0) || (strcmp("--sonicos", argv[argLoop]) == 0))
			nipper->config->deviceType = Config::SonicWALLSonicOS;
		else if (strcmp("--passport", argv[argLoop]) == 0)
			nipper->config->deviceType = Config::NortelPassport;
		else if (strcmp("--accelar", argv[argLoop]) == 0)
			nipper->config->deviceType = Config::BayAccelar;
		else if (strcmp("--procurve", argv[argLoop]) == 0)
			nipper->config->deviceType = Config::HPProCurve;
		else if ((strcmp("--netscreen", argv[argLoop]) == 0) || (strcmp("--screenos", argv[argLoop]) == 0))
			nipper->config->deviceType = Config::JuniperScreenOS;
		else if (strcmp("--nortel-switch", argv[argLoop]) == 0)
			nipper->config->deviceType = Config::NortelRoutingSwitch;
		else if (strcmp("--auto", argv[argLoop]) == 0)
			nipper->config->deviceType = Config::AutodetectDevice;

		// Device Model...
		else if (strncmp("--model=", argv[argLoop], 8) == 0)
			nipper->config->deviceModel = argv[argLoop] + 8;

		// Force...
		else if (strcmp("--force", argv[argLoop]) == 0)
			nipper->config->deviceTypeChecks = false;

		// Device name specified...
		else if (strncmp("--device-name=", argv[argLoop], 14) == 0)
			nipper->config->deviceName = argv[argLoop] + 14;

		// Set the devices network location...
		else if (strcmp("--location=edge", argv[argLoop]) == 0)
			nipper->config->deviceLocation = Config::Edge;
		else if (strcmp("--location=internal", argv[argLoop]) == 0)
			nipper->config->deviceLocation = Config::Internal;

		// John the ripper output...
		else if ((strncmp("--john=", argv[argLoop], 7) == 0) && (strlen(argv[argLoop]) > 7))
			nipper->config->johnFile = argv[argLoop] + 7;


		// -------------------------
		//   Auditing Options...
		// -------------------------

		// Password Policy Audit Settings...
		else if (strncmp("--pass-length=", argv[argLoop], 14) == 0)
			nipper->config->minimumPasswordLength = atoi(argv[argLoop] + 14);
		else if (strcmp("--no-pass-length", argv[argLoop]) == 0)
			nipper->config->minimumPasswordLength = 0;
		else if (strcmp("--pass-uppers", argv[argLoop]) == 0)
			nipper->config->passwordsMustIncludeUppers = true;
		else if (strcmp("--no-pass-uppers", argv[argLoop]) == 0)
			nipper->config->passwordsMustIncludeUppers = false;
		else if (strcmp("--pass-lowers", argv[argLoop]) == 0)
			nipper->config->passwordsMustIncludeLowers = true;
		else if (strcmp("--no-pass-lowers", argv[argLoop]) == 0)
			nipper->config->passwordsMustIncludeLowers = false;
		else if (strcmp("--pass-either", argv[argLoop]) == 0)
			nipper->config->passwordsMustIncludeEitherCase = true;
		else if (strcmp("--no-pass-either", argv[argLoop]) == 0)
			nipper->config->passwordsMustIncludeEitherCase = false;
		else if (strcmp("--pass-numbers", argv[argLoop]) == 0)
			nipper->config->passwordsMustIncludeNumbers = true;
		else if (strcmp("--no-pass-numbers", argv[argLoop]) == 0)
			nipper->config->passwordsMustIncludeNumbers = false;
		else if (strcmp("--pass-specials", argv[argLoop]) == 0)
			nipper->config->passwordsMustIncludeSpecials = true;
		else if (strcmp("--no-pass-specials", argv[argLoop]) == 0)
			nipper->config->passwordsMustIncludeSpecials = false;
		else if (strncmp("--pass-char-repeat=", argv[argLoop], 19) == 0)
			nipper->config->maximumRepeatedChars = atoi(argv[argLoop] + 19);
		else if (strcmp("--no-pass-length", argv[argLoop]) == 0)
			nipper->config->maximumRepeatedChars = 0;
		else if (strcmp("--pass-username", argv[argLoop]) == 0)
			nipper->config->differentFromUsername = true;
		else if (strcmp("--no-pass-username", argv[argLoop]) == 0)
			nipper->config->differentFromUsername = false;
		else if (strcmp("--pass-hostname", argv[argLoop]) == 0)
			nipper->config->differentFromHostname = true;
		else if (strcmp("--no-pass-hostname", argv[argLoop]) == 0)
			nipper->config->differentFromHostname = false;
		else if (strcmp("--pass-device-info", argv[argLoop]) == 0)
			nipper->config->noDeviceInformationInPasswords = true;
		else if (strcmp("--no-pass-device-info", argv[argLoop]) == 0)
			nipper->config->noDeviceInformationInPasswords = false;
		else if (strcmp("--pass-dict-subst", argv[argLoop]) == 0)
			nipper->config->noDictionaryCharacterSubst = true;
		else if (strcmp("--no-pass-dict-subst", argv[argLoop]) == 0)
			nipper->config->noDictionaryCharacterSubst = false;
		else if (strcmp("--pass-dict-append", argv[argLoop]) == 0)
			nipper->config->noCommonDictionaryAppends = true;
		else if (strcmp("--no-pass-dict-append", argv[argLoop]) == 0)
			nipper->config->noCommonDictionaryAppends = false;
		else if (strcmp("--pass-char-seq", argv[argLoop]) == 0)
			nipper->config->noCharacterSequences = true;
		else if (strcmp("--no-pass-char-seq", argv[argLoop]) == 0)
			nipper->config->noCharacterSequences = false;

		// Legacy options (0.11), delete at some stage in the future...
		else if (strcmp("--pass-uppers=yes", argv[argLoop]) == 0)
			nipper->config->passwordsMustIncludeUppers = true;
		else if (strcmp("--pass-uppers=no", argv[argLoop]) == 0)
			nipper->config->passwordsMustIncludeUppers = false;
		else if (strcmp("--pass-lowers=yes", argv[argLoop]) == 0)
			nipper->config->passwordsMustIncludeLowers = true;
		else if (strcmp("--pass-lowers=no", argv[argLoop]) == 0)
			nipper->config->passwordsMustIncludeLowers = false;
		else if (strcmp("--pass-either=yes", argv[argLoop]) == 0)
			nipper->config->passwordsMustIncludeEitherCase = true;
		else if (strcmp("--pass-either=no", argv[argLoop]) == 0)
			nipper->config->passwordsMustIncludeEitherCase = false;
		else if (strcmp("--pass-numbers=yes", argv[argLoop]) == 0)
			nipper->config->passwordsMustIncludeNumbers = true;
		else if (strcmp("--pass-numbers=no", argv[argLoop]) == 0)
			nipper->config->passwordsMustIncludeNumbers = false;
		else if (strcmp("--pass-specials=yes", argv[argLoop]) == 0)
			nipper->config->passwordsMustIncludeSpecials = true;
		else if (strcmp("--pass-specials=no", argv[argLoop]) == 0)
			nipper->config->passwordsMustIncludeSpecials = false;

		// Dictionary supplied...
		else if (strncmp("--dictionary=", argv[argLoop], 13) == 0)
			nipper->config->passwordDictionary = argv[argLoop] + 13;

		// Set Timeout...
		else if (strncmp("--timeout=", argv[argLoop], 10) == 0)
		{
			if (atoi(argv[argLoop] + 10) != 0)
				nipper->config->connectionTimeouts = atoi(argv[argLoop] + 10);
		}

		// Filtering Settings...
		else if (strcmp("--ignore-non-tcp-udp", argv[argLoop]) == 0)
			nipper->config->ignoreNonTCPUDPFilters = true;
		else if (strcmp("--no-ignore-non-tcp-udp", argv[argLoop]) == 0)
			nipper->config->ignoreNonTCPUDPFilters = false;
		else if (strcmp("--filter-enabled", argv[argLoop]) == 0)
			nipper->config->checkFilteringIsConfigured = true;
		else if (strcmp("--no-filter-enabled", argv[argLoop]) == 0)
			nipper->config->checkFilteringIsConfigured = false;
		else if (strcmp("--filter-default-allow", argv[argLoop]) == 0)
			nipper->config->checkFilterDefaultAllowAction = true;
		else if (strcmp("--no-filter-default-allow", argv[argLoop]) == 0)
			nipper->config->checkFilterDefaultAllowAction = false;
		else if (strcmp("--filter-any-source", argv[argLoop]) == 0)
			nipper->config->checkFilterForAnySource = true;
		else if (strcmp("--no-filter-any-source", argv[argLoop]) == 0)
			nipper->config->checkFilterForAnySource = false;
		else if (strcmp("--filter-net-source", argv[argLoop]) == 0)
			nipper->config->checkFilterForNetworkSource = true;
		else if (strcmp("--no-filter-net-source", argv[argLoop]) == 0)
			nipper->config->checkFilterForNetworkSource = false;
		else if (strcmp("--filter-any-source-port", argv[argLoop]) == 0)
			nipper->config->checkFilterForAnySourcePort = true;
		else if (strcmp("--no-filter-any-source-port", argv[argLoop]) == 0)
			nipper->config->checkFilterForAnySourcePort = false;
		else if (strcmp("--filter-range-source-port", argv[argLoop]) == 0)
			nipper->config->checkFilterForRangeSourcePort = true;
		else if (strcmp("--no-filter-range-source-port", argv[argLoop]) == 0)
			nipper->config->checkFilterForRangeSourcePort = false;
		else if (strcmp("--filter-any-dest", argv[argLoop]) == 0)
			nipper->config->checkFilterForAnyDestination = true;
		else if (strcmp("--no-filter-any-dest", argv[argLoop]) == 0)
			nipper->config->checkFilterForAnyDestination = false;
		else if (strcmp("--filter-net-dest", argv[argLoop]) == 0)
			nipper->config->checkFilterForNetworkDestination = true;
		else if (strcmp("--no-filter-net-dest", argv[argLoop]) == 0)
			nipper->config->checkFilterForNetworkDestination = false;
		else if (strcmp("--filter-any-dest-port", argv[argLoop]) == 0)
			nipper->config->checkFilterForAnyDestinationPort = true;
		else if (strcmp("--no-filter-any-dest-port", argv[argLoop]) == 0)
			nipper->config->checkFilterForAnyDestinationPort = false;
		else if (strcmp("--filter-range-dest-port", argv[argLoop]) == 0)
			nipper->config->checkFilterForRangeDestinationPort = true;
		else if (strcmp("--no-filter-range-dest-port", argv[argLoop]) == 0)
			nipper->config->checkFilterForRangeDestinationPort = false;
		else if (strcmp("--filter-log-allow", argv[argLoop]) == 0)
			nipper->config->checkFilterLogsAllowedRules = true;
		else if (strcmp("--no-filter-log-allow", argv[argLoop]) == 0)
			nipper->config->checkFilterLogsAllowedRules = false;
		else if (strcmp("--filter-log-deny", argv[argLoop]) == 0)
			nipper->config->checkFilterForLogDeniedRules = true;
		else if (strcmp("--no-filter-log-deny", argv[argLoop]) == 0)
			nipper->config->checkFilterForLogDeniedRules = false;
		else if (strcmp("--filter-end-log-and-deny", argv[argLoop]) == 0)
			nipper->config->checkFilterEndsWithDenyAllAndLog = true;
		else if (strcmp("--no-filter-end-log-and-deny", argv[argLoop]) == 0)
			nipper->config->checkFilterEndsWithDenyAllAndLog = false;
		else if (strcmp("--filter-reject", argv[argLoop]) == 0)
			nipper->config->checkFilterForRejectRules = true;
		else if (strcmp("--no-filter-reject", argv[argLoop]) == 0)
			nipper->config->checkFilterForRejectRules = false;
		else if (strcmp("--filter-bypass", argv[argLoop]) == 0)
			nipper->config->checkFilterForBypassRules = true;
		else if (strcmp("--no-filter-bypass", argv[argLoop]) == 0)
			nipper->config->checkFilterForBypassRules = false;
		else if (strcmp("--filter-default", argv[argLoop]) == 0)
			nipper->config->checkFilterForDefaultRules = true;
		else if (strcmp("--no-filter-default", argv[argLoop]) == 0)
			nipper->config->checkFilterForDefaultRules = false;
		else if (strcmp("--filter-comments", argv[argLoop]) == 0)
			nipper->config->checkFilterForRulesWithoutComments = true;
		else if (strcmp("--no-filter-comments", argv[argLoop]) == 0)
			nipper->config->checkFilterForRulesWithoutComments = false;
		else if (strcmp("--filter-disabled", argv[argLoop]) == 0)
			nipper->config->checkFilterForDisabledRules = true;
		else if (strcmp("--no-filter-disabled", argv[argLoop]) == 0)
			nipper->config->checkFilterForDisabledRules = false;
		else if (strcmp("--filter-unused", argv[argLoop]) == 0)
			nipper->config->checkFilterForUnusedRulesAtListEnd = true;
		else if (strcmp("--no-filter-unused", argv[argLoop]) == 0)
			nipper->config->checkFilterForUnusedRulesAtListEnd = false;
		else if (strcmp("--filter-clear-text", argv[argLoop]) == 0)
			nipper->config->checkFilterForClearTextRules = true;
		else if (strcmp("--no-filter-clear-text", argv[argLoop]) == 0)
			nipper->config->checkFilterForClearTextRules = false;
		else if (strcmp("--filter-duplicates", argv[argLoop]) == 0)
			nipper->config->checkFilterForDuplicateRules = true;
		else if (strcmp("--no-filter-duplicates", argv[argLoop]) == 0)
			nipper->config->checkFilterForDuplicateRules = false;
		else if (strcmp("--filter-contradicts", argv[argLoop]) == 0)
			nipper->config->checkFilterForContradictRules = true;
		else if (strcmp("--no-filter-contradicts", argv[argLoop]) == 0)
			nipper->config->checkFilterForContradictRules = false;
		else if (strcmp("--filter-unused-lists", argv[argLoop]) == 0)
			nipper->config->checkFilterForDuplicateRules = true;
		else if (strcmp("--no-filter-unused-lists", argv[argLoop]) == 0)
			nipper->config->checkFilterForDuplicateRules = false;

		// The following are legacy (0.11 and older), remove when time has passed...
		else if (strcmp("--deny-log", argv[argLoop]) == 0)
			nipper->config->checkFilterEndsWithDenyAllAndLog = true;
		else if (strcmp("--no-deny-log", argv[argLoop]) == 0)
			nipper->config->checkFilterEndsWithDenyAllAndLog = false;
		else if (strcmp("--any-source", argv[argLoop]) == 0)
			nipper->config->checkFilterForAnySource = true;
		else if (strcmp("--no-any-source", argv[argLoop]) == 0)
			nipper->config->checkFilterForAnySource = false;
		else if (strcmp("--network-source", argv[argLoop]) == 0)
			nipper->config->checkFilterForNetworkSource = true;
		else if (strcmp("--no-network-source", argv[argLoop]) == 0)
			nipper->config->checkFilterForNetworkSource = false;
		else if (strcmp("--source-service", argv[argLoop]) == 0)
			nipper->config->checkFilterForAnySourcePort = true;
		else if (strcmp("--no-source-service", argv[argLoop]) == 0)
			nipper->config->checkFilterForAnySourcePort = false;
		else if (strcmp("--any-destination", argv[argLoop]) == 0)
			nipper->config->checkFilterForAnyDestination = true;
		else if (strcmp("--no-any-destination", argv[argLoop]) == 0)
			nipper->config->checkFilterForAnyDestination = false;
		else if (strcmp("--network-destination", argv[argLoop]) == 0)
			nipper->config->checkFilterForNetworkDestination = true;
		else if (strcmp("--no-network-destination", argv[argLoop]) == 0)
			nipper->config->checkFilterForNetworkDestination = false;
		else if (strcmp("--destination-service", argv[argLoop]) == 0)
			nipper->config->checkFilterForAnyDestinationPort = true;
		else if (strcmp("--no-destination-service", argv[argLoop]) == 0)
			nipper->config->checkFilterForAnyDestinationPort = false;
		else if (strcmp("--log-rules", argv[argLoop]) == 0)
			nipper->config->checkFilterLogsAllowedRules = true;
		else if (strcmp("--no-log-rules", argv[argLoop]) == 0)
			nipper->config->checkFilterLogsAllowedRules = false;
		else if (strcmp("--disabled-rules", argv[argLoop]) == 0)
			nipper->config->checkFilterForDisabledRules = true;
		else if (strcmp("--no-disabled-rules", argv[argLoop]) == 0)
			nipper->config->checkFilterForDisabledRules = false;
		else if (strcmp("--reject-rules", argv[argLoop]) == 0)
			nipper->config->checkFilterForRejectRules = true;
		else if (strcmp("--no-reject-rules", argv[argLoop]) == 0)
			nipper->config->checkFilterForRejectRules = false;
		else if (strcmp("--bypass-rules", argv[argLoop]) == 0)
			nipper->config->checkFilterForBypassRules = true;
		else if (strcmp("--no-bypass-rules", argv[argLoop]) == 0)
			nipper->config->checkFilterForBypassRules = false;
		else if (strcmp("--default-rules", argv[argLoop]) == 0)
			nipper->config->checkFilterForDefaultRules = true;
		else if (strcmp("--no-default-rules", argv[argLoop]) == 0)
			nipper->config->checkFilterForDefaultRules = false;
		else if (strcmp("--log-deny-rules", argv[argLoop]) == 0)
			nipper->config->checkFilterForLogDeniedRules = true;
		else if (strcmp("--no-log-deny-rules", argv[argLoop]) == 0)
			nipper->config->checkFilterForLogDeniedRules = false;

		// -----------------------------------
		//   Nipper (The Program) Options...
		// -----------------------------------

		// Various Help pages or version info that has nothing to do
		// with libnipper...

		// Version
		else if (strcmp("--version", argv[argLoop]) == 0)
			return help_version;

		// License
		else if (strcmp("--license", argv[argLoop]) == 0)
			return help_license;

		// Various Help Pages...
		else if ((strcasecmp("--help", argv[argLoop]) == 0) || (strcasecmp("/?", argv[argLoop]) == 0) || (strcasecmp("--help=general", argv[argLoop]) == 0))
			return help_general;
		else if (strcasecmp("--help=devices", argv[argLoop]) == 0)
			return help_device_types;
		else if (strcasecmp("--help=SNMP", argv[argLoop]) == 0)
			return help_snmp;
		else if (strcasecmp("--help=devices-adv", argv[argLoop]) == 0)
			return help_device_usage;
		else if (strcasecmp("--help=REPORT", argv[argLoop]) == 0)
			return help_report_formats;
		else if (strcasecmp("--help=REPORT-ADV", argv[argLoop]) == 0)
			return help_report_options;
		else if (strcasecmp("--help=REPORT-SECT", argv[argLoop]) == 0)
			return help_report_appendix;
		else if (strcasecmp("--help=REPORT-HTML", argv[argLoop]) == 0)
			return help_report_html;
		else if (strcasecmp("--help=REPORT-LATEX", argv[argLoop]) == 0)
			return help_report_latex;
		else if (strcasecmp("--help=AUDIT-ACL", argv[argLoop]) == 0)
			return help_audit_acl;
		else if (strcasecmp("--help=AUDIT-PASS", argv[argLoop]) == 0)
			return help_audit_password;
		else if (strcasecmp("--help=AUDIT-ADV", argv[argLoop]) == 0)
			return help_audit_misc;
		else if (strcasecmp("--help=DEBUG", argv[argLoop]) == 0)
			return help_debug;
		else if (strcasecmp("--help=CONFIG-FILE", argv[argLoop]) == 0)
			return help_config_file;

		// If all else fails, display the help...
		else
		{
			paramno = argLoop;
			return help_error_params;
		}
	}

	// Return 0, no help.
	return 0;
}


int main(int argc, char** argv)
{
	// Variables...
	Nipper *nipper = 0;
	int returnCode = 0;

	// Init Nipper library with settings and so on
	nipper = new (Nipper);

	// Process Command Line Args
	returnCode = processCommandArgs(argc, argv, nipper);
	if (returnCode == -1)
	{ }

	// Show version...
	else if (returnCode == help_version)
	{
		printf("%s\n\n", program_version_banner);
		printf("%s\n", nipper->getVersion());
	}

	// Show help...
	else if (returnCode != 0)
		showHelp(argc, argv, returnCode);

	else
	{
		// Execute Nipper Library Processing
		returnCode = nipper->process();

		// Report on any errors
		if (returnCode != 0)
		{
			printf("%s%s\n%s", COL_BLUE, program_banner, RESET);
			printf("%s\n", nipper->getErrorText(returnCode));
			showHelpFooter();
		}
		else
		{
			returnCode = nipper->generateReport();
			if (returnCode == 0)
			{
				returnCode = nipper->writeReport();
				if (returnCode != 0)
				{
					printf("%s%s\n%s", COL_BLUE, program_banner, RESET);
					printf("%s\n", nipper->getErrorText(returnCode));
					showHelpFooter();
				}
			}
			else
			{
				printf("%s%s\n%s", COL_BLUE, program_banner, RESET);
				printf("%s\n", nipper->getErrorText(returnCode));
				showHelpFooter();
			}
		}
	}

	// Free
	delete nipper;

	return 0;
}


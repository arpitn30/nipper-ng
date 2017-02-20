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

#define i18n(String) String

#define unconfigured 0
#define off 1
#define on 2

#if !defined(__WIN32__)
#define TEMP_DIR "/tmp/"
#else
#define TEMP_DIR ""
#endif

#define MAX_SIZE 1024

// Password Testing...
#define passwordTestOk 0
#define passwordTestDefault 1
#define passwordTestDict 2
#define passwordTestWeak 3

// Error code definitions...
#define libnipper_error_noerror 0
#define libnipper_error_notprocessed 1
#define libnipper_error_nodevice 2
#define libnipper_error_notgenerated 3
#define libnipper_error_memoryalloc 4
#define libnipper_error_fileempty 5
#define libnipper_error_noreport 6
#define libnipper_error_noconfig 7
#define libnipper_error_noconfdev 8
#define libnipper_error_nooutput 9
#define libnipper_error_outofvalues 10
#define libnipper_error_outofstrings 11
#define libnipper_error_nojohn 12
#define libnipper_error_noparagraph 13
#define libnipper_error_nolist 14
#define libnipper_error_notable 15
#define libnipper_error_configfileopen 16
#define libnipper_error_detectionfailed 17
#define libnipper_error_wrongdevice 18


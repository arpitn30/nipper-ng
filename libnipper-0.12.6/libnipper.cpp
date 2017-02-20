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

// Includes...
#include "globaldefs.h"
#include "libnipper.h"
#include "config.h"
#include "report/report.h"

// Device Includes...
#include "Cisco-CSS/device.h"
#include "Cisco-Catalyst-CatOS/device.h"
#include "Cisco-Catalyst-NMP/device.h"
#include "Cisco-IOS-Catalyst/device.h"
#include "Cisco-IOS-Router/device.h"
#include "Cisco-Security-ASA/device.h"
#include "Cisco-Security-FWSM/device.h"
#include "Cisco-Security-PIX/device.h"
#include "CheckPoint-Firewall/device.h"
#include "CheckPoint-Management/device.h"
#include "Nokia-IP/device.h"
#include "HP-ProCurve/device.h"
#include "Juniper-ScreenOS/device.h"
#include "Nortel-Passport/device.h"
#include "Nortel-RoutingSwitch/device.h"
#include "BayNetworks-Accelar/device.h"
#include "SonicWALL-SonicOS/device.h"
#include "3Com-SuperStack3-Firewall/device.h"


const char *nipperVersion;

const char *Nipper::getVersion()
{
	return "libNipper version 0.12.6\nhttp://nipper.titania.co.uk\nCopyright (C) 2006-2008 Ian Ventura-Whiting\n";
}


Nipper::Nipper()
{
	// Init...
	nipperVersion = "0.12.6";
	processed = false;
	generated = false;
	config = new (Config);
	device = 0;
	report = 0;

	// Load configuration from file...
#if !defined(__WIN32__)
	config->setConfigFile("/etc/nipper.conf");
#else
	config->setConfigFile("nipper.ini");
#endif
}


Nipper::~Nipper()
{
	// Create configuration objects...
	delete config;

	if (device != 0)
		delete device;
	if (report != 0)
		delete report;
}


const char *Nipper::getErrorText(int errorCode)
{
	// If it is a device specific error (errorCode >= 100)
	if ((errorCode >= 100) && (device != 0))
		return device->getErrorText(errorCode);

	else
	{
		switch (errorCode)
		{
			case libnipper_error_wrongdevice:
				return i18n("Failed to process the configuration due to the wrong type of device. You need to specify the correct device type.");
				break;

			case libnipper_error_detectionfailed:
				return i18n("Could not automatically detect the device type. You need to specify the type of device.");
				break;

			case libnipper_error_fileempty:
				return i18n("Could not find the configuration file, the file was empty or it was not a file. Check that the configuration file is valid.");
				break;
	
			case libnipper_error_memoryalloc:
				return i18n("Could not reserve the memory. This is probably because you need more memory.");
				break;
	
			case libnipper_error_notgenerated:
				return i18n("The report has not been generated yet. You must generate the report before writing the report to an output file or stdout.");
				break;
	
			case libnipper_error_nodevice:
				return i18n("No internal device class exists. You should not see this error, if you are reading this, please file a bug report.");
				break;
	
			case libnipper_error_notprocessed:
				return i18n("The device configuration has not been processed yet. You must process the configuration before generating a report.");
				break;

			case libnipper_error_noreport:
				return i18n("Could not create a report. This could be because due to low memory conditions.");
				break;

			case libnipper_error_noconfig:
				return i18n("Config does not exist. This could be because due to low memory conditions.");
				break;

			case libnipper_error_noconfdev:
				return i18n("The config and device classes have not been set. This is an internal error, if you are seeing this text then report a bug.");
				break;

			case libnipper_error_nooutput:
				return i18n("Nipper could not open the output file for writing. Check that you have write permissions and that there is enough space.");
				break;

			case libnipper_error_noerror:
				return i18n("No error has occured. Everything is ok.");
				break;

			case libnipper_error_outofvalues:
				return i18n("Internal processing error. Out of values during the report writing.");
				break;

			case libnipper_error_outofstrings:
				return i18n("Internal processing error. Out of strings during the report writing.");
				break;

			case libnipper_error_nojohn:
				return i18n("Unable to open the specified encrypted password output file for writing.");
				break;

			case libnipper_error_noparagraph:
				return i18n("Internal processing error. Out of paragraphs during the report writing.");
				break;

			case libnipper_error_nolist:
				return i18n("Internal processing error. Out of lists during the report writing.");
				break;

			case libnipper_error_notable:
				return i18n("Internal processing error. Out of tables during the report writing.");
				break;

			case libnipper_error_configfileopen:
				return i18n("Filesystem error. Could not open the configuration file.");
				break;

			default:
				return i18n("Unknown error, could not determine the error.");
				break;
		}
	}
}


int Nipper::process()
{
	// Variables...
	int returnCode;
	bool found = false;

	// Init...
	processed = false;

	// Check config object exists...
	if (config == 0)
		return libnipper_error_noconfig;

	// Debug mode?
	if (config->reportFormat == Config::Debug)
		printf("\n%sVersion Information\n===================%s\n%s\n", config->COL_BLUE, config->COL_RESET, getVersion());

	// If device already exists...
	if (device != 0)
		delete device;

	// Create Device Type Instance
	switch (config->deviceType)
	{
		case Config::CiscoCSS:
			device = new (CiscoCSSDevice);
			device->config = config;
			break;
		case Config::CiscoCatOSCatalyst:
			device = new (CiscoCatalystCatOSDevice);
			device->config = config;
			break;
		case Config::CiscoNMPCatalyst:
			device = new (CiscoCatalystNMPDevice);
			device->config = config;
			break;
		case Config::CiscoASAFirewall:
			device = new (CiscoASADevice);
			device->config = config;
			break;
		case Config::CiscoFWSMFirewall:
			device = new (CiscoFWSMDevice);
			device->config = config;
			break;
		case Config::CiscoPIXFirewall:
			device = new (CiscoPIXDevice);
			device->config = config;
			break;
		case Config::CiscoIOSCatalyst:
			device = new (IOSCatDevice);
			device->config = config;
			break;
		case Config::CiscoIOSRouter:
			device = new (IOSRouterDevice);
			device->config = config;
			break;
		case Config::JuniperScreenOS:
			device = new (ScreenOSDevice);
			device->config = config;
			break;
		case Config::CheckPointFirewall:
			device = new (CheckPointFirewallDevice);
			device->config = config;
			break;
		case Config::CheckPointManagement:
			device = new (CheckPointManagementDevice);
			device->config = config;
			break;
		case Config::NokiaIP:
			device = new (NokiaIPDevice);
			device->config = config;
			break;
		case Config::NortelPassport:
			device = new (PassportDevice);
			device->config = config;
			break;
		case Config::NortelRoutingSwitch:
			device = new (NortelRoutingSwitchDevice);
			device->config = config;
			break;
		case Config::BayAccelar:
			device = new (BayNetworksAccelarDevice);
			device->config = config;
			break;
		case Config::HPProCurve:
			device = new (ProCurveDevice);
			device->config = config;
			break;
		case Config::SonicWALLSonicOS:
			device = new (SonicOSDevice);
			device->config = config;
			break;
		case Config::ThreeComSuperStackFW:
			device = new (SuperStack3FirewallDevice);
			device->config = config;
			break;

		case Config::AutodetectDevice:
		default:
			// Detect type...
			config->deviceType = Config::CiscoASAFirewall;
			device = new (CiscoASADevice);
			device->config = config;
			found = device->isDeviceType();
			if (found == false)
			{
				delete device;
				config->deviceType = Config::CiscoPIXFirewall;
				device = new (CiscoPIXDevice);
				device->config = config;
				found = device->isDeviceType();
			}
			if (found == false)
			{
				delete device;
				config->deviceType = Config::CiscoIOSRouter;
				device = new (IOSRouterDevice);
				device->config = config;
				found = device->isDeviceType();
			}
			if (found == false)
			{
				delete device;
				config->deviceType = Config::CiscoIOSCatalyst;
				device = new (IOSCatDevice);
				device->config = config;
				found = device->isDeviceType();
			}
			if (found == false)
			{
				delete device;
				config->deviceType = Config::JuniperScreenOS;
				device = new (ScreenOSDevice);
				device->config = config;
				found = device->isDeviceType();
			}
			if (found == false)
			{
				delete device;
				config->deviceType = Config::CheckPointManagement;
				device = new (CheckPointManagementDevice);
				device->config = config;
				found = device->isDeviceType();
			}
			if (found == false)
			{
				delete device;
				config->deviceType = Config::HPProCurve;
				device = new (ProCurveDevice);
				device->config = config;
				found = device->isDeviceType();
			}
			if (found == false)
			{
				delete device;
				config->deviceType = Config::CiscoCSS;
				device = new (CiscoCSSDevice);
				device->config = config;
				found = device->isDeviceType();
			}
			if (found == false)
			{
				delete device;
				config->deviceType = Config::CiscoFWSMFirewall;
				device = new (CiscoFWSMDevice);
				device->config = config;
				found = device->isDeviceType();
			}
			if (found == false)
			{
				delete device;
				config->deviceType = Config::CiscoCatOSCatalyst;
				device = new (CiscoCatalystCatOSDevice);
				device->config = config;
				found = device->isDeviceType();
			}
			if (found == false)
			{
				delete device;
				config->deviceType = Config::SonicWALLSonicOS;
				device = new (SonicOSDevice);
				device->config = config;
				found = device->isDeviceType();
			}
			if (found == false)
			{
				delete device;
				config->deviceType = Config::NortelPassport;
				device = new (PassportDevice);
				device->config = config;
				found = device->isDeviceType();
			}
			if (found == false)
			{
				delete device;
				config->deviceType = Config::CiscoNMPCatalyst;
				device = new (CiscoCatalystNMPDevice);
				device->config = config;
				found = device->isDeviceType();
			}
			if (found == false)
			{
				delete device;
				config->deviceType = Config::AutodetectDevice;
				device = 0;
				return libnipper_error_detectionfailed;
			}
			break;
	}
	if (device == 0)
		return libnipper_error_memoryalloc;
	device->nipperVersion = nipperVersion;

	// Process the device configuration settings...
	if (config->reportFormat == Config::Debug)
		printf("%sProcessing Config\n=================%s\n", config->COL_BLUE, config->COL_RESET);

	// Process Device Type
	returnCode = device->process();
	if (returnCode != 0)
		return returnCode;

	// Return successful processing.
	processed = true;
	return 0;
}


int Nipper::generateReport()
{
	// Variables...
	int returnCode = 0;

	// If the config has not been processed...
	if (processed == false)
		return libnipper_error_notprocessed;

	// If no device exists...
	if (device == 0)
		return libnipper_error_nodevice;

	// Write report
	if (config->reportFormat == Config::Debug)
		printf("\n%sGenerating Report\n=================%s\n", config->COL_BLUE, config->COL_RESET);

	// Generate report structures...
	returnCode = device->generateReport();

	if (returnCode == 0)
		generated = true;

	return returnCode;
}


int Nipper::writeReport()
{
	// Variables...
	int returnValue = 0;

	// Has the report been generated yet?
	if (generated == false)
		return libnipper_error_notgenerated;

	// If no device exists...
	if (device == 0)
		return libnipper_error_nodevice;

	// Check config class exists...
	if (config == 0)
		return libnipper_error_noconfig;

	// Create report class...
	report = new (Report);
	if (report == 0)
		return libnipper_error_noreport;

	// Set device and config...
	report->config = config;
	report->device = device;

	// Write report
	if (config->reportFormat == Config::Debug)
	{
		printf("\n%sWriting Report\n==============%s\n", config->COL_BLUE, config->COL_RESET);
		config->reportFormat = Config::Text;
		returnValue = report->write();
		config->reportFormat = Config::Debug;
	}
	else
		returnValue = report->write();

	delete report;
	report = 0;

	return returnValue;
}


const char *Nipper::getComplianceChecks()
{
	return "<checklist>\n</checklist>\n";
}

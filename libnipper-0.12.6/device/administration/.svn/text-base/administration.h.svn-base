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

#ifndef deviceadministration_H
#define deviceadministration_H


#include "../common/deviceconfig.h"


class Administration : public DeviceConfig
{
	public:

		Administration();
		virtual ~Administration();


	// -----------------------------------------------------------------------
	// Standard Device Class Methods...
	// -----------------------------------------------------------------------

		virtual int generateConfigReport(Device *device);
		virtual int generateSecurityReport(Device *device);


		// General options, but need to be checked by sister classes...
		bool cdpSupported;					// Is CDP supported (globally, see interfaces for per interface activation)
		bool cdpEnabled;					// Is CDP enabled


	protected:

		virtual int generateDeviceSpecificConfig(Device *device);


	// -----------------------------------------------------------------------
	// General Host Restriction Support...
	// -----------------------------------------------------------------------

		struct hostFilter
		{
			string host;
			string netmask;
			string interface;
			string access;
			struct hostFilter *next;
		};

		// Host restrictions...
		bool serviceWideHosts;				// Do all the admin services share a common host restrictions?
		bool showHostInterface;				// Show the Interface column in the host table?
		bool showHostAccess;				// Show the Access column in the host table?
		const char *serviceConfigHosts;		// Text, how to configure administrative host restrictions.
		hostFilter *serviceHosts;

		enum serviceType
		{
			allServices = 0,
			telnetService = 1,
			sshService = 2,
			httpService = 3,
			ftpService = 4,
			tftpService = 5
		};

		hostFilter *addHostFilter(enum serviceType type);


	// -----------------------------------------------------------------------
	// General...
	// -----------------------------------------------------------------------

		bool generalSettings;				// Show the general settings section?
		bool consoleEnabled;				// Is the Console port enabled?
		bool consoleSupported;				// Is a console port supported?
		bool consoleTimeoutSupported;		// Is a console timeout supported?
		int consoleTimeout;					// Console timeout
		const char *configConsoleTimeout;	// The text and commands to configure the timeout
		bool auxSupported;					// Are AUX port(s) supported?
		bool auxEnabled;					// Is AUX port(s) enabled?
		const char *configAuxPort;			// The text and commands to disable the AUX port
		bool callbackSupported;				// Is AUX port callback supported?
		bool callbackEnabled;				// Is AUX port callback enabled?
		const char *configCallback;			// The text to configure callback.
		bool connectionTimeoutSupported;	// Is a connection timeout supported?
		int connectionTimeout;				// Connection Timeout (secs)
		const char *configTimeout;			// The text and commands to configure the timeout
		bool cdpVersionSupported;			// Is CDP version supported
		int cdpVersion;						// CDP version
		const char *disableCDPText;			// The text and commands to disable CDP

		// Methods
		virtual int generateDeviceGeneralConfig(Device *device);		// A device specific config report output


	// -----------------------------------------------------------------------
	// Telnet Support...
	// -----------------------------------------------------------------------

		// Telnet settings...
		bool telnetEnabled;					// Is Telnet enabled?
		int telnetPort;						// The telnet service port
		hostFilter *telnetHosts;			// The Telnet hosts

		// Device specific options...
		bool telnetSupported;				// Is telnet supported?
		bool telnetSpecificHost;			// Does Telnet have its own access list?
		bool telnetHostsRequired;			// Is the host configuration required?
		bool showTelnetHostInterface;		// Show the Interface column in the host table?
		bool showTelnetHostAccess;			// Show the Access column in the host table?
		const char *configTelnetHostAccess;	// How access lists are configured for the telnet service
		const char *disableTelnet;			// How to disable telnet text...
		bool telnetSpecificTimeout;			// A Telnet Specific Timeout?
		int telnetTimeout;					// The Telnet Timeout (secs)
		const char *configTelnetTimeout;	// The text and commands to configure the timeout

		// Methods
		virtual int generateDeviceTelnetConfig(Device *device);		// A device specific config report output


	// -----------------------------------------------------------------------
	// TFTP Support...
	// -----------------------------------------------------------------------

		// TFTP settings...
		bool tftpEnabled;					// Is TFTP enabled?
		int tftpPort;						// The TFTP service port
		hostFilter *tftpHosts;				// The TFTP hosts

		// Device specific options...
		bool tftpSupported;					// Is TFTP supported?
		bool tftpSpecificHost;				// Does TFTP have its own access list?
		bool tftpHostsRequired;				// Is the host configuration required?
		bool showTFTPHostInterface;			// Show the Interface column in the host table?
		bool showTFTPHostAccess;			// Show the Access column in the host table?
		const char *configTFTPHostAccess;	// How access lists are configured for the TFTP service
		const char *disableTFTP;			// How to disable TFTP text...

		// Methods
		virtual int generateDeviceTFTPConfig(Device *device);		// A device specific config report output


	// -----------------------------------------------------------------------
	// FTP Support...
	// -----------------------------------------------------------------------

		// FTP settings...
		bool ftpEnabled;					// Is FTP enabled?
		int ftpPort;						// The FTP service port
		hostFilter *ftpHosts;				// The FTP hosts

		// Device specific options...
		bool ftpSupported;					// Is FTP supported?
		bool ftpSpecificHost;				// Does FTP have its own access list?
		bool ftpHostsRequired;				// Is the host configuration required?
		bool showFTPHostInterface;			// Show the Interface column in the host table?
		bool showFTPHostAccess;				// Show the Access column in the host table?
		const char *configFTPHostAccess;	// How access lists are configured for the FTP service
		const char *disableFTP;				// How to disable FTP text...
		bool ftpSpecificTimeout;			// A FTP Specific Timeout?
		int ftpTimeout;						// The FTP Timeout (secs)
		const char *configFTPTimeout;		// The text and commands to configure the timeout

		// Methods
		virtual int generateDeviceFTPConfig(Device *device);		// A device specific config report output


	// -----------------------------------------------------------------------
	// SSH Support...
	// -----------------------------------------------------------------------

		// SSH settings...
		bool sshEnabled;					// Is the SSH service enabled?
		int sshVersion;						// What is the SSH Protocol version (0 = 1 and 2)
		int sshPort;						// The SSH port number
		hostFilter *sshHosts;				// The SSH hosts

		// Device specific options...
		// SSH support
		bool sshSupported;					// Does this device support SSH?
		bool sshUpgrade;					// Do you have to upgrade?
		const char *configSSHSupport;		// How to configure SSH...
		bool sshSpecificHost;				// Does SSH have its own access list?
		bool sshHostsRequired;				// Is the host configuration required?
		bool showSSHHostInterface;			// Show the Interface column in the host table?
		bool showSSHHostAccess;				// Show the Access column in the host table?
		const char *configSSHHostAccess;	// How to configure SSH management hosts...
		bool sshSpecificTimeout;			// A SSH Specific Timeout?
		int sshTimeout;						// The SSH Timeout (secs)
		const char *configSSHTimeout;		// The text and commands to configure the timeout

		// SSH Options
		bool sftpEnabled;					// Is SFTP enabled?
		bool sftpSupported;					// Is SFTP supported?
		bool sftpUpgrade;					// Upgrade to support SFTP?
		const char *configSFTP;				// Text and commands to configure SFTP
		bool scpSupported;					// Is SCP supported?
		bool scpEnabled;					// Is SCP enabled?

		// SSH 2 support...
		bool ssh2Supported;					// Does the device support SSH version 2?
		bool ssh2upgrade;					// Do you have to upgrade...
		const char *configSSHv2Support;		// How to configure protocol version 2 support only

		// Config text...
		const char *sshConfigProtocolSupport;		// Config report text on protocol support (e.g. supports both version 1 and 2 of the protocol)

		// Methods
		virtual int generateDeviceSSHConfig(Device *device);		// A device specific config report output


	// -----------------------------------------------------------------------
	// BOOTP Support...
	// -----------------------------------------------------------------------

		bool bootPServerSupported;			// Is BOOTP supported?
		bool bootPEnabled;					// Is BOOTP enabled?
		const char *configDisableBootP;		// Config report text to disable bootp


	// -----------------------------------------------------------------------
	// Finger Support...
	// -----------------------------------------------------------------------

		bool fingerServiceSupported;		// Is the finger service supported?
		bool fingerServiceEnabled;			// Is the finger service enabled?
		const char *configDisableFinger;	// Config report text to disable finger


	// -----------------------------------------------------------------------
	// HTTP Support...
	// -----------------------------------------------------------------------

		bool httpEnabled;					// Is the HTTP service enabled?
		int httpPort;						// HTTP port
		bool httpsEnabled;					// Is the HTTPS service enabled?
		int httpsPort;						// HTTPS port
		bool httpsRedirect;					// Is HTTP to HTTPS redirect enabled?
		hostFilter *httpHosts;				// The HTTP hosts
		bool httpSpecificTimeout;			// A HTTP Specific Timeout?
		int httpTimeout;					// The HTTP Timeout (secs)
		const char *configHTTPTimeout;		// The text and commands to configure the timeout

		struct cipherConfig
		{
			string encryption;
			string authenticaton;
			int bits;
			bool ssl2;
			bool ssl3;
			bool tls1;
			struct cipherConfig *next;
		};
		cipherConfig *ciphers;				// The SSL ciphers configured
		bool defaultCiphers;

		// Device specific options...
		const char *httpLabel;				// The label given to the HTTP service (e.g. HTTP)
		const char *httpsLabel;				// The label given to the HTTPS service (e.g. HTTPS)
		bool httpSupported;					// Does this device support HTTP
		bool httpsSupported;				// Does this device support HTTPS
		bool httpsUpgrade;					// Do you have to upgrade for HTTPS?
		bool httpSpecificHost;				// Does HTTP have its own access list?
		bool httpHostsRequired;				// Is the host configuration required?
		bool showHTTPHostInterface;			// Show the Interface column in the host table?
		bool showHTTPHostAccess;			// Show the Access column in the host table?
		const char *disableHTTP;			// How to disable HTTP text...
		const char *configHTTPSSupport;		// How to configure HTTPS...
		const char *configHTTPHostAccess;	// How to configure HTTP Management hosts...
		bool cipherConfigSupported;			// Can the Ciphers be configured?
		const char *configCipherText;		// The text to configure a strong cipher.

		// Methods
		cipherConfig *addCipher();			// Add a cipher to the supported cipher list
		virtual int generateDeviceHTTPConfig(Device *device);		// A device specific config report output


	private:

		// Telnet methods...
		int generateTelnetConfig(Device *device);
		int generateTelnetSecurityIssue(Device *device, bool noWeakTelnetHosts);
		int generateTelnetHostSecurityIssue(Device *device);
		int generateTelnetWeakHostSecurityIssue(Device *device, int weakCount);

		// TFTP methods...
		int generateTFTPConfig(Device *device);
		int generateTFTPSecurityIssue(Device *device, bool noWeakTFTPHosts);
		int generateTFTPHostSecurityIssue(Device *device);
		int generateTFTPWeakHostSecurityIssue(Device *device, int weakCount);

		// FTP methods...
		int generateFTPConfig(Device *device);
		int generateFTPSecurityIssue(Device *device, bool noWeakFTPHosts);
		int generateFTPHostSecurityIssue(Device *device);
		int generateFTPWeakHostSecurityIssue(Device *device, int weakCount);

		// SSH methods...
		int generateSSHConfig(Device *device);
		int generateSSHVersionSecurityIssue(Device *device, bool noWeakSSHHosts);
		int generateSSHHostSecurityIssue(Device *device, bool sshVersion1);
		int generateSSHWeakHostSecurityIssue(Device *device, int weakCount, bool sshVersion1);

		// HTTP methods...
		int generateHTTPConfig(Device *device);
		int generateHTTPSecurityIssue(Device *device, bool noWeakHTTPHosts);
		int generateHTTPHostSecurityIssue(Device *device);
		int generateHTTPWeakHostSecurityIssue(Device *device, int weakCount);
		int generateWeakCipherSecurityIssue(Device *device, int weakCipherCount);

		// BootP methods...
		int generateBootPConfig(Device *device);
		int generateBootPSecurityIssue(Device *device);

		// Finger methods...
		int generateFingerConfig(Device *device);
		int generateFingerSecurityIssue(Device *device);

		// General methods...
		int generateGeneralConfig(Device *device);

		// AUX...
		int generateAUXSecurityIssue(Device *device);

		// CDP...
		int generateCDPSecurityIssue(Device *device);

		// Timeouts...
		int generateTimeoutSecurityIssue(Device *device);
		int generateConsoleTimeoutSecurityIssue(Device *device);
		int generateTelnetTimeoutSecurityIssue(Device *device, bool noWeakTelnetHosts);
		int generateFTPTimeoutSecurityIssue(Device *device, bool noWeakFTPHosts);
		int generateSSHTimeoutSecurityIssue(Device *device, bool noWeakSSHHosts);
		int generateHTTPTimeoutSecurityIssue(Device *device, bool noWeakHTTPHosts);

		// Management host methods...
		int generateHostsConfig(Device *device);
		int generateServiceHostSecurityIssue(Device *device);
		int generateWeakHostSecurityIssue(Device *device, int weakCount);
};


#endif

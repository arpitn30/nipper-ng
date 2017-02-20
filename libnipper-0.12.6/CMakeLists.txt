PROJECT(Nipper CXX)

CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

# Add compiler definitions (first is for development only)...
#ADD_DEFINITIONS(-Wall -g -O2)
ADD_DEFINITIONS(-O2)

# General Device
SET(device_SRC
	device/device.cpp

	# Common Device Code...
	device/common/configline.cpp
	device/common/deviceconfig.cpp
	device/common/file.cpp
	device/common/misc.cpp
	device/common/paragraph.cpp
	device/common/passwords.cpp
	device/common/tables.cpp

	# Crypto (and encoding) routines...
	device/crypto/crypto-base64.cpp
	device/crypto/crypto-ciscotype7.cpp
	device/crypto/crypto-url.cpp

	# Device reporting...
	device/reportgen/report.cpp
	device/reportgen/report-abbreviations.cpp
	device/reportgen/report-commonports.cpp
	device/reportgen/report-icmp.cpp
	device/reportgen/report-logginglevels.cpp
	device/reportgen/report-misc.cpp
	device/reportgen/report-numbering.cpp
	device/reportgen/report-protocols.cpp

	# Device configuration sections...
	device/general/general.cpp
	device/administration/administration.cpp
	device/administration/administration-bootp.cpp
	device/administration/administration-finger.cpp
	device/administration/administration-ftp.cpp
	device/administration/administration-general.cpp
	device/administration/administration-hosts.cpp
	device/administration/administration-http.cpp
	device/administration/administration-telnet.cpp
	device/administration/administration-tftp.cpp
	device/administration/administration-timeout.cpp
	device/administration/administration-ssh.cpp
	device/dns/dns.cpp
	device/dns/dns-report.cpp
	device/authentication/authentication.cpp
	device/authentication/authentication-general.cpp
	device/authentication/authentication-kerberos.cpp
	device/authentication/authentication-ldap.cpp
	device/authentication/authentication-nt.cpp
	device/authentication/authentication-radius.cpp
	device/authentication/authentication-securid.cpp
	device/authentication/authentication-tacacs.cpp
	device/authentication/authentication-users.cpp
	device/banner/banner.cpp
	device/banner/banner-report.cpp
	device/filter/filter.cpp
	device/filter/filter-filter.cpp
	device/filter/filter-filter-report.cpp
	device/filter/filter-object.cpp
	device/filter/filter-object-report.cpp
	device/filter/filter-security.cpp
	device/filter/filter-security-report.cpp
	device/interfaces/interfaces.cpp
	device/interfaces/interfaces-interface.cpp
	device/interfaces/interfaces-report.cpp
	device/interfaces/interfaces-security.cpp
	device/snmp/snmp.cpp
	device/snmp/snmp-community.cpp
	device/snmp/snmp-group.cpp
	device/snmp/snmp-host.cpp
	device/snmp/snmp-misc-issues.cpp
	device/snmp/snmp-traps.cpp
	device/snmp/snmp-user.cpp
	device/snmp/snmp-view.cpp
)

# Cisco IOS Device...
SET(iosdevice_SRC
	Cisco-IOS/iosdevice.cpp
	Cisco-IOS/general.cpp
	Cisco-IOS/administration.cpp
	Cisco-IOS/administration-line.cpp
	Cisco-IOS/administration-report.cpp
	Cisco-IOS/administration-security.cpp
	Cisco-IOS/authentication.cpp
	Cisco-IOS/banner.cpp
	Cisco-IOS/snmp.cpp
	Cisco-IOS/snmp-report.cpp
	Cisco-IOS/filter.cpp
	Cisco-IOS/dns.cpp
	Cisco-IOS/interfaces.cpp
)

# Cisco IOS Catalyst Device...
SET(ioscatdevice_SRC
	Cisco-IOS-Catalyst/device.cpp
)

# Cisco IOS Router Device...
SET(iosrouterdevice_SRC
	Cisco-IOS-Router/device.cpp
)

# Cisco CSS Device...
SET(ciscocssdevice_SRC
	Cisco-CSS/device.cpp
	Cisco-CSS/general.cpp
	Cisco-CSS/administration.cpp
	Cisco-CSS/banner.cpp
	Cisco-CSS/snmp.cpp
	Cisco-CSS/snmp-report.cpp
	Cisco-CSS/dns.cpp
	Cisco-CSS/filter.cpp
	Cisco-CSS/authentication.cpp
	Cisco-CSS/interfaces.cpp
)

# Cisco Security Device...
SET(ciscosecdevice_SRC
	Cisco-Security/device.cpp
	Cisco-Security/general.cpp
	Cisco-Security/administration.cpp
	Cisco-Security/authentication.cpp
	Cisco-Security/banner.cpp
	Cisco-Security/filter.cpp
	Cisco-Security/snmp.cpp
	Cisco-Security/dns.cpp
	Cisco-Security/interfaces.cpp
)

# Cisco Security PIX Device...
SET(ciscopixdevice_SRC
	Cisco-Security-PIX/device.cpp
	Cisco-Security-PIX/administration.cpp
)

# Cisco Security ASA Device...
SET(ciscoasadevice_SRC
	Cisco-Security-ASA/device.cpp
	Cisco-Security-ASA/administration.cpp
)

# Cisco Security FWSM Device...
SET(ciscofwsmdevice_SRC
	Cisco-Security-FWSM/device.cpp
	Cisco-Security-FWSM/administration.cpp
)

# Cisco Catalyst Device...
SET(catalystdevice_SRC
	Cisco-Catalyst/device.cpp
	Cisco-Catalyst/general.cpp
	Cisco-Catalyst/administration.cpp
	Cisco-Catalyst/authentication.cpp
	Cisco-Catalyst/banner.cpp
	Cisco-Catalyst/dns.cpp
	Cisco-Catalyst/snmp.cpp
	Cisco-Catalyst/interfaces.cpp
)

# Cisco Catalyst CatOS Device...
SET(catalystcatosdevice_SRC
	Cisco-Catalyst-CatOS/device.cpp
)

# Cisco Catalyst NMP Device...
SET(catalystnmpdevice_SRC
	Cisco-Catalyst-NMP/device.cpp
)

# CheckPoint-Based Device...
SET(checkpointdevice_SRC
	CheckPoint/device.cpp
	CheckPoint/device-policies.cpp
	CheckPoint/general.cpp
	CheckPoint/filter.cpp
	CheckPoint/filter-objects.cpp
	CheckPoint/filter-rules.cpp
	CheckPoint/filter-services.cpp
)

# CheckPoint Firewall Module Device...
SET(checkpointfirewalldevice_SRC
	CheckPoint-Firewall/device.cpp
)

# CheckPoint Management Module Device...
SET(checkpointmanagementdevice_SRC
	CheckPoint-Management/device.cpp
)

# Nokia IP Device...
SET(nokiaipdevice_SRC
	Nokia-IP/device.cpp
)

# Juniper ScreenOS Device...
SET(screenosdevice_SRC
	Juniper-ScreenOS/device.cpp
	Juniper-ScreenOS/general.cpp
	Juniper-ScreenOS/administration.cpp
	Juniper-ScreenOS/administration-report.cpp
	Juniper-ScreenOS/authentication.cpp
	Juniper-ScreenOS/banner.cpp
	Juniper-ScreenOS/snmp.cpp
	Juniper-ScreenOS/filter.cpp
	Juniper-ScreenOS/dns.cpp
	Juniper-ScreenOS/interfaces.cpp
)

# Nortel Passport Device...
SET(passportdevice_SRC
	Nortel-Passport/device.cpp
	Nortel-Passport/general.cpp
	Nortel-Passport/administration.cpp
	Nortel-Passport/banner.cpp
	Nortel-Passport/snmp.cpp
	Nortel-Passport/filter.cpp
	Nortel-Passport/interfaces.cpp
)

# Nortel Ethernet Routing Switch (8300) Device...
SET(nortelroutingswitchdevice_SRC
	Nortel-RoutingSwitch/device.cpp
)

# Bay Networks Accelar Device...
SET(bayaccelardevice_SRC
	BayNetworks-Accelar/device.cpp
)

# HP ProCurve Device...
SET(procurvedevice_SRC
	HP-ProCurve/device.cpp
	HP-ProCurve/general.cpp
	HP-ProCurve/administration.cpp
	HP-ProCurve/banner.cpp
	HP-ProCurve/snmp.cpp
	HP-ProCurve/snmp-report.cpp
	HP-ProCurve/dns.cpp
	HP-ProCurve/authentication.cpp
	HP-ProCurve/interfaces.cpp
)

# SonicWALL SonicOS Device...
SET(sonicosdevice_SRC
	SonicWALL-SonicOS/device.cpp
	SonicWALL-SonicOS/dns.cpp
	SonicWALL-SonicOS/general.cpp
	SonicWALL-SonicOS/filter.cpp
	SonicWALL-SonicOS/snmp.cpp
	SonicWALL-SonicOS/administration.cpp
	SonicWALL-SonicOS/administration-report.cpp
)

# 3Com SuperStack 3 Firewall Device...
SET(superstack3fwdevice_SRC
	3Com-SuperStack3-Firewall/device.cpp
)

# Reporting...
SET(report_SRC
	report/report.cpp
	report/report-contents.cpp
	report/report-functions.cpp
	report/report-frontpage.cpp
	report/report-introduction.cpp
	report/report-list.cpp
	report/report-section-security.cpp
	report/report-section-compliance.cpp
	report/report-section-config.cpp
	report/report-section-appendix.cpp
	report/report-start.cpp
	report/report-table.cpp
	report/report-text.cpp
	report/report-titles.cpp
)

SET(libnipper_SRC
	libnipper.cpp
	config.cpp
	${report_SRC}
	${device_SRC}
	${iosdevice_SRC}
	${ioscatdevice_SRC}
	${iosrouterdevice_SRC}
	${ciscosecdevice_SRC}
	${ciscoasadevice_SRC}
	${ciscofwsmdevice_SRC}
	${ciscopixdevice_SRC}
	${ciscocssdevice_SRC}
	${catalystdevice_SRC}
	${catalystcatosdevice_SRC}
	${catalystnmpdevice_SRC}
	${checkpointdevice_SRC}
	${checkpointfirewalldevice_SRC}
	${checkpointmanagementdevice_SRC}
	${nokiaipdevice_SRC}
	${screenosdevice_SRC}
	${passportdevice_SRC}
	${nortelroutingswitchdevice_SRC}
	${bayaccelardevice_SRC}
	${procurvedevice_SRC}
	${sonicosdevice_SRC}
	${superstack3fwdevice_SRC}
)

# TEMPORARY COMMANDS TO EASE DEVELOPMENT - DELETE...
#ADD_EXECUTABLE(nipper nipper.cpp ${libnipper_SRC})

# Build the library...
ADD_LIBRARY(nipper SHARED ${libnipper_SRC})

# Install...
INSTALL(TARGETS nipper LIBRARY DESTINATION /usr/lib)
INSTALL(FILES nipper.conf DESTINATION /etc)
INSTALL(FILES libnipper.h config.h DESTINATION /usr/include/libnipper/)
INSTALL(FILES man/nipper.conf.5 DESTINATION /usr/share/man/man5)
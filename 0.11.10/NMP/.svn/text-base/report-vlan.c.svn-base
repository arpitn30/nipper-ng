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

// This file contains the code for NMP / CatOS reporting

void nmpVLANConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct vlanConfig *vlanNMPPointer = 0;

	output_table(nipper, true, settings_vlan_table, &settings_vlan_heading);
	vlanNMPPointer = nipper->nmp->vlan;
	while(vlanNMPPointer != 0)
	{
		fprintf(nipper->reportFile, "%s%d%s", nipper->tablerow_start, vlanNMPPointer->vlan, nipper->tablerow_mid);
		fprintf(nipper->reportFile, "%s%s", vlanNMPPointer->name, nipper->tablerow_mid);
		if (vlanNMPPointer->active == true)
			fprintf(nipper->reportFile, "Yes%s", nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "No%s", nipper->tablerow_mid);
		fprintf(nipper->reportFile, "%s%s", vlanNMPPointer->type, nipper->tablerow_mid);
		if (vlanNMPPointer->firewall == -1)
			fprintf(nipper->reportFile, "None%s", nipper->tablerow_mid);
		else
			fprintf(nipper->reportFile, "%d%s", vlanNMPPointer->firewall, nipper->tablerow_mid);
		fprintf(nipper->reportFile, "%d%s", vlanNMPPointer->said, nipper->tablerow_mid);
		fprintf(nipper->reportFile, "%d%s", vlanNMPPointer->mtu, nipper->tablerow_mid);
		fprintf(nipper->reportFile, "%d%s", vlanNMPPointer->spanTreeMaxHops, nipper->tablerow_mid);
		fprintf(nipper->reportFile, "%d%s", vlanNMPPointer->allRoutesMaxHops, nipper->tablerow_end);
		vlanNMPPointer = vlanNMPPointer->next;
	}
	output_table(nipper, false, settings_vlan_table, &settings_vlan_heading);
	addAbbreviation("SAID", false);
	addAbbreviation("VLAN", false);
	addAbbreviation("MTU", false);
}


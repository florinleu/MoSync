/* Copyright (C) 2011 MoSync AB

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.
*/

/**
 * @file ViewOrganization.cpp
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Address view Layout.
 *
 **/

#include <util.h>

#include "ViewOrganization.h"
#include "ViewDefines.h"

using namespace PIM;
using namespace NativeUI;

/**
 * Constructor.
 * @param contact	The contact for which to display the field.
 */
ViewOrganization::ViewOrganization(Contact* contact):
		ViewField(contact)
{
	initData();
	createUI();
}

/**
 * Destructor.
 */
ViewOrganization::~ViewOrganization()
{
}

/**
 * Inits the data used to display this field.
 */
void ViewOrganization::initData()
{
	mTitleText = strdup(TXT_VIEW_ORGANIZATION_TITLE);
}

/**
 * Creates the view.
 */
void ViewOrganization::addBody()
{
	const char* labels[] =
	{
		"name",
		"title",
		"department",
		"location",
		"job description",
		"phonetic name",
		"symbol"
	};

	ViewField::addBody();

	for (int i=0; i<mOwner->getOrganizationsCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d. %s", i + 1, getOrganizationTypeString(mOwner->getOrganization(i)->getType()));
		if (mOwner->getOrganization(i)->getType() == ORGANIZATION_CUSTOM)
		{
			sprintf(title, "%s (%S)", title, mOwner->getOrganization(i)->getLabel());
		}
		addSubTitle(title, mOwner->getAddress(i)->isPrimary());
		DELETE(title);

		const char* datas[] =
		{
			wstrtostr(mOwner->getOrganization(i)->getName()),
			wstrtostr(mOwner->getOrganization(i)->getTitle()),
			wstrtostr(mOwner->getOrganization(i)->getDepartment()),
			wstrtostr(mOwner->getOrganization(i)->getLocation()),
			wstrtostr(mOwner->getOrganization(i)->getJobDescription()),
			wstrtostr(mOwner->getOrganization(i)->getPhoneticName()),
			wstrtostr(mOwner->getOrganization(i)->getSymbol())
		};

		addSubFields(labels, datas, sizeof(labels)/sizeof(char*));
	}
}

/**
 * Gets the name of the organization type.
 * @param type	The organization type.
 * @return 		The type name.
 */
const char* ViewOrganization::getOrganizationTypeString(eOrganizationTypes type)
{
	const char* organizationType[] =
	{
		"Work",
		"Other",
		"Custom"
	};

	return organizationType[type];
}

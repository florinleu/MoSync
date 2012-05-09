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
 * @file ViewWebsite.cpp
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Website view Layout.
 *
 **/

#include <util.h>

#include "ViewWebsite.h"
#include "ViewDefines.h"

using namespace PIM;
using namespace NativeUI;

/**
 * Constructor.
 * @param contact	The contact for which to display the field.
 */
ViewWebsite::ViewWebsite(Contact* contact):
		ViewField(contact)
{
	initData();
	createUI();
}

/**
 * Destructor.
 */
ViewWebsite::~ViewWebsite()
{
}

/**
 * Inits the data used to display this field.
 */
void ViewWebsite::initData()
{
	mTitleText = strdup(TXT_VIEW_WEBSITE_TITLE);
}

/**
 * Creates the view.
 */
void ViewWebsite::addBody()
{
	const char* labels[] =
	{
		"url",
	};

	ViewField::addBody();

	for (int i=0; i<mOwner->getWebsitesCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d. %s", i + 1, getWebsiteTypeString(mOwner->getWebsite(i)->getType()));
		if (mOwner->getWebsite(i)->getType() == WEBSITE_CUSTOM)
		{
			sprintf(title, "%s (%S)", title, mOwner->getWebsite(i)->getLabel());
		}
		addSubTitle(title, mOwner->getAddress(i)->isPrimary());
		DELETE(title);

		const char* datas[] =
		{
			wstrtostr(mOwner->getWebsite(i)->getURL())
		};

		addSubFields(labels, datas, sizeof(labels)/sizeof(char*));
	}
}

/**
 * Gets the name of the website type.
 * @param type	The website type.
 * @return 		The type name.
 */
const char* ViewWebsite::getWebsiteTypeString(eWebsiteTypes type)
{
	const char* websiteType[] =
	{
		"Homepage",
		"Blog",
		"Profile",
		"Home",
		"Work",
		"FTP",
		"Other",
		"Custom"
	};

	return websiteType[type];
}

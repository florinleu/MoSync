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
 * @file ViewSocialProfile.cpp
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief SocialProfile view Layout.
 *
 **/

#include <util.h>

#include "ViewSocialProfile.h"
#include "ViewDefines.h"
#include "ContactsScreen.h"

using namespace PIM;
using namespace NativeUI;

/**
 * Constructor.
 * @param contact	The contact for which to display the field.
 */
ViewSocialProfile::ViewSocialProfile(Contact* contact):
		ViewField(contact)
{
	initData();
	createUI();
}

/**
 * Destructor.
 */
ViewSocialProfile::~ViewSocialProfile()
{
}

/**
 * Inits the data used to display this field.
 */
void ViewSocialProfile::initData()
{
	mTitleText = strdup(TXT_VIEW_SP_TITLE);
}

/**
 * Creates the view.
 */
void ViewSocialProfile::addBody()
{
	const char* labels[] =
	{
		"url",
		"username",
		"user identifier",
		"service"
	};

	ViewField::addBody();

	for (int i=0; i<mOwner->getSocialProfilesCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d. %s", i + 1,
				ContactsScreen::getSPTypeString(
						mOwner->getSocialProfile(i)->getType(),
						mOwner->getSocialProfile(i)->getLabel()));
		addSubTitle(title, mOwner->getSocialProfile(i)->isPrimary());
		DELETE(title);

		char* service = new char[BUFF_SIZE];
		sprintf(service, "%s",
				ContactsScreen::getSPServiceString(
						mOwner->getSocialProfile(i)->getService(),
						mOwner->getSocialProfile(i)->getServiceLabel()));

		const char* datas[] =
		{
			wstrtostr(mOwner->getSocialProfile(i)->getURL()),
			wstrtostr(mOwner->getSocialProfile(i)->getUsername()),
			wstrtostr(mOwner->getSocialProfile(i)->getUserIdentifier()),
			service
		};

		addSubFields(labels, datas, sizeof(labels)/sizeof(char*));
		DELETE(service);
	}
}

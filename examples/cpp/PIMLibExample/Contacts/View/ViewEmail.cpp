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
 * @file ViewEmail.cpp
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Email view Layout.
 *
 **/

#include <util.h>

#include "ViewEmail.h"
#include "ViewDefines.h"

using namespace PIM;
using namespace NativeUI;

/**
 * Constructor.
 * @param contact	The contact for which to display the field.
 */
ViewEmail::ViewEmail(Contact* contact):
		ViewField(contact)
{
	initData();
	createUI();
}

/**
 * Destructor.
 */
ViewEmail::~ViewEmail()
{
}

/**
 * Inits the data used to display this field.
 */
void ViewEmail::initData()
{
	mTitleText = strdup(TXT_VIEW_EMAIL_TITLE);
}

/**
 * Creates the view.
 */
void ViewEmail::addBody()
{
	const char* labels[] =
	{
		"address",
	};

	ViewField::addBody();

	for (int i=0; i<mOwner->getEmailsCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d. %s", i + 1, getEmailTypeString(mOwner->getEmail(i)->getType()));
		if (mOwner->getEmail(i)->getType() == EMAIL_CUSTOM)
		{
			sprintf(title, "%s (%S)", title, mOwner->getEmail(i)->getLabel());
		}
		addSubTitle(title, mOwner->getAddress(i)->isPrimary());
		DELETE(title);

		const char* datas[] =
		{
			wstrtostr(mOwner->getEmail(i)->getAddress())
		};

		addSubFields(labels, datas, sizeof(labels)/sizeof(char*));
	}
}

/**
 * Gets the name of the email type.
 * @param type	The email type.
 * @return 		The type name.
 */
const char* ViewEmail::getEmailTypeString(eEmailTypes type)
{
	const char* emailType[] =
	{
		"Home",
		"Work",
		"Mobile",
		"Other",
		"Custom"
	};

	return emailType[type];
}

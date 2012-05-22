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
#include "ContactsScreen.h"

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
		sprintf(title, "%d. %s", i + 1, ContactsScreen::getEmailTypeString(mOwner->getEmail(i)->getType(), mOwner->getEmail(i)->getLabel()));
		addSubTitle(title, mOwner->getEmail(i)->isPrimary());
		DELETE(title);

		const char* datas[] =
		{
			wstrtostr(mOwner->getEmail(i)->getAddress())
		};

		addSubFields(labels, datas, sizeof(labels)/sizeof(char*));
	}
}

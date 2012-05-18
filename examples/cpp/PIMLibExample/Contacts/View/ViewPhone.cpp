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
 * @file ViewPhone.cpp
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Phone view Layout.
 *
 **/

#include <util.h>

#include "ContactsScreen.h"

#include "ViewPhone.h"
#include "ViewDefines.h"

using namespace PIM;
using namespace NativeUI;

/**
 * Constructor.
 * @param contact	The contact for which to display the field.
 */
ViewPhone::ViewPhone(Contact* contact):
		ViewField(contact)
{
	initData();
	createUI();
}

/**
 * Destructor.
 */
ViewPhone::~ViewPhone()
{
}

/**
 * Inits the data used to display this field.
 */
void ViewPhone::initData()
{
	mTitleText = strdup(TXT_VIEW_PHONE_TITLE);
}

/**
 * Creates the view.
 */
void ViewPhone::addBody()
{
	const char* labels[] =
	{
		"number",
	};

	ViewField::addBody();

	for (int i=0; i<mOwner->getPhonesCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d. %s", i + 1, ContactsScreen::getPhoneTypeString(mOwner->getPhone(i)->getType(), mOwner->getPhone(i)->getLabel()));
		addSubTitle(title, mOwner->getPhone(i)->isPrimary());
		DELETE(title);

		const char* datas[] =
		{
			wstrtostr(mOwner->getPhone(i)->getNumber())
		};

		addSubFields(labels, datas, sizeof(labels)/sizeof(char*));
	}
}

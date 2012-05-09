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
 * @file ViewName.cpp
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Name View Layout.
 *
 **/

#include "ViewName.h"
#include "ViewDefines.h"
#include <util.h>

using namespace PIM;

/**
 * Constructor.
 * @param contact	The contact for which to display the field.
 */
ViewName::ViewName(Contact* contact):
		ViewField(contact)
{
	initData();
	createUI();
}

/**
 * Destructor.
 */
ViewName::~ViewName()
{

}

/**
 * Inits the data used to display this field.
 */
void ViewName::initData()
{
	mTitleText = strdup(TXT_VIEW_NAME_TITLE);
}

/**
 * Creates the view.
 */
void ViewName::addBody()
{
	const char* labels[] =
	{
		"display name",
		"first name",
		"middle name",
		"last name",
		"nickname",
		"prefix",
		"suffix",
		"phonetic first",
		"phonetic middle",
		"phonetic last",
		"formatted name"
	};

	const char* datas[] =
	{
		wstrtostr(mOwner->getName()->getDisplayName()),
		wstrtostr(mOwner->getName()->getFirstName()),
		wstrtostr(mOwner->getName()->getMiddleName()),
		wstrtostr(mOwner->getName()->getLastName()),
		wstrtostr(mOwner->getName()->getNickname()),
		wstrtostr(mOwner->getName()->getPrefix()),
		wstrtostr(mOwner->getName()->getSuffix()),
		wstrtostr(mOwner->getName()->getPhoneticFirstName()),
		wstrtostr(mOwner->getName()->getPhoneticMiddleName()),
		wstrtostr(mOwner->getName()->getPhoneticLastName()),
		wstrtostr(mOwner->getName()->getFormattedName())
	};

	ViewField::addBody();
	addSubFields(labels, datas, sizeof(labels)/sizeof(char*));
}

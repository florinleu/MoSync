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
 * @file ViewID.cpp
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief ID View Layout.
 *
 **/

#include "ViewID.h"
#include "ViewDefines.h"
#include <util.h>

using namespace PIM;

/**
 * Constructor.
 * @param contact	The contact for which to display the field.
 */
ViewID::ViewID(Contact* contact):
		ViewField(contact)
{
	initData();
	createUI();
}

/**
 * Destructor.
 */
ViewID::~ViewID()
{

}

/**
 * Inits the data used to display this field.
 */
void ViewID::initData()
{
	mTitleText = strdup(TXT_VIEW_ID_TITLE);
}

/**
 * Creates the view.
 */
void ViewID::addBody()
{
	const char* labels[] =
	{
		"id"
	};

	const char* datas[] =
	{
		wstrtostr(mOwner->getID()),
	};

	ViewField::addBody();
	addSubFields(labels, datas, sizeof(labels)/sizeof(char*));
}

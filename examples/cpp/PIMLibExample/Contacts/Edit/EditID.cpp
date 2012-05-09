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
 * @file EditID.cpp
 * @author Florin Leu
 * @date 07 Mar 2012
 *
 * @brief ID Edit Layout.
 *
 **/

#include <util.h>

#include "EditID.h"
#include "EditDefines.h"

using namespace PIM;
using namespace NativeUI;

/**
 * Constructor.
 * @param contact The owner of this field.
 */
EditID::EditID(Contact* contact):
	EditField(contact)
{
	initData();
	createUI();
}

/**
 * Destructor.
 */
EditID::~EditID()
{

}

/**
 * Inits the data used to display this field.
 */
void EditID::initData()
{
	mTitleText = strdup(TXT_EDIT_ID_TITLE);
}

/**
 * Creates the view.
 */
void EditID::addBody()
{
	const char* labels[] =
	{
		"id"
	};

	const char* texts[] =
	{
		wstrtostr(mOwner->getID())
	};

	const int datas[] =
	{
		ID::DATA
	};

	EditField::addBody();
	addSubFields(labels, texts, datas, sizeof(labels)/sizeof(char*), EDIT_ID_FLAGS);
}

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
 * @file ViewNote.cpp
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Note View Layout.
 *
 **/

#include "ViewNote.h"
#include "ViewDefines.h"
#include <util.h>

using namespace PIM;

/**
 * Constructor.
 * @param contact	The contact for which to display the field.
 */
ViewNote::ViewNote(Contact* contact):
		ViewField(contact)
{
	initData();
	createUI();
}

/**
 * Destructor.
 */
ViewNote::~ViewNote()
{

}

/**
 * Inits the data used to display this field.
 */
void ViewNote::initData()
{
	mTitleText = strdup(TXT_VIEW_NOTE_TITLE);
}

/**
 * Creates the view.
 */
void ViewNote::addBody()
{
	const char* labels[] =
	{
		"text"
	};

	const char* datas[] =
	{
		wstrtostr(mOwner->getNote()->getText()),
	};

	ViewField::addBody();
	addSubFields(labels, datas, sizeof(labels)/sizeof(char*));
}

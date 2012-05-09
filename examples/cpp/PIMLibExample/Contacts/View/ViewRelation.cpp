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
 * @file ViewRelation.cpp
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Relation view layout.
 *
 **/

#include <util.h>

#include "ViewRelation.h"
#include "ViewDefines.h"

using namespace PIM;
using namespace NativeUI;

/**
 * Constructor.
 * @param contact	The contact for which to display the field.
 */
ViewRelation::ViewRelation(Contact* contact):
		ViewField(contact)
{
	initData();
	createUI();
}

/**
 * Destructor.
 */
ViewRelation::~ViewRelation()
{
}

/**
 * Inits the data used to display this field.
 */
void ViewRelation::initData()
{
	mTitleText = strdup(TXT_VIEW_RELATION_TITLE);
}

/**
 * Creates the view.
 */
void ViewRelation::addBody()
{
	const char* labels[] =
	{
		"name",
	};

	ViewField::addBody();

	for (int i=0; i<mOwner->getRelationsCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d. %s", i + 1, getRelationTypeString(mOwner->getRelation(i)->getType()));
		if (mOwner->getRelation(i)->getType() == RELATION_CUSTOM)
		{
			sprintf(title, "%s (%S)", title, mOwner->getRelation(i)->getLabel());
		}
		addSubTitle(title, mOwner->getAddress(i)->isPrimary());
		DELETE(title);

		const char* datas[] =
		{
			wstrtostr(mOwner->getRelation(i)->getName()),
		};

		addSubFields(labels, datas, sizeof(labels)/sizeof(char*));
	}
}

/**
 * Gets the name of the relation type.
 * @param type	The relation type.
 * @return 		The type name.
 */
const char* ViewRelation::getRelationTypeString(PIM::eRelationTypes type)
{
	const char* relationType[] =
	{
		"Mother",
		"Father",
		"Parent",
		"Sister",
		"Brother",
		"Child",
		"Friend",
		"Spouse",
		"Partner",
		"Manager",
		"Assistant",
		"Domestic partner",
		"Referred by",
		"Relative",
		"Custom"
	};

	return relationType[type];
}

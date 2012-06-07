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
 * @file ViewAddress.cpp
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Address view Layout.
 *
 **/

#include <util.h>

#include "ContactsScreen.h"

#include "ViewAddress.h"
#include "ViewDefines.h"

using namespace PIM;
using namespace NativeUI;

/**
 * Constructor.
 * @param contact	The contact for which to display the field.
 */
ViewAddress::ViewAddress(Contact* contact):
		ViewField(contact)
{
	initData();
	createUI();
}

/**
 * Destructor.
 */
ViewAddress::~ViewAddress()
{
}

/**
 * Inits the data used to display this field.
 */
void ViewAddress::initData()
{
	mTitleText = strdup(TXT_VIEW_ADDRESS_TITLE);
}

/**
 * Creates the view.
 */
void ViewAddress::addBody()
{
	const char* labels[] =
	{
		"street",
		"city",
		"state",
		"postal code",
		"country",
		"neighborhood",
		"po box",
		"formatted address"
	};

	ViewField::addBody();

	for (int i=0; i<mOwner->getAddressesCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d. %s", i + 1,
			ContactsScreen::getAddressTypeString(
				mOwner->getAddress(i)->getType(),
				mOwner->getAddress(i)->getLabel()
			));
		addSubTitle(title, mOwner->getAddress(i)->isPrimary());
		DELETE(title);

		const char* datas[] =
		{
			wstrtostr(mOwner->getAddress(i)->getStreet()),
			wstrtostr(mOwner->getAddress(i)->getCity()),
			wstrtostr(mOwner->getAddress(i)->getState()),
			wstrtostr(mOwner->getAddress(i)->getPostalCode()),
			wstrtostr(mOwner->getAddress(i)->getCountry()),
			wstrtostr(mOwner->getAddress(i)->getNeighborhood()),
			wstrtostr(mOwner->getAddress(i)->getPOBox()),
			wstrtostr(mOwner->getAddress(i)->getFormattedAddress())
		};

		addSubFields(labels, datas, sizeof(labels)/sizeof(char*));
	}
}

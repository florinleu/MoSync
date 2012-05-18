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
 * @file EditDelete.cpp
 * @author Florin Leu
 * @date 13 Mar 2012
 *
 * @brief Delete Button Layout.
 *
 **/

#include <pim.h>
#include <util.h>
#include "EditDelete.h"
#include "ScreenContainer.h"
#include "ConfirmDialog.h"

using namespace NativeUI;
using namespace PIM;

/**
 * Constructor.
 */
EditDelete::EditDelete(Contact* contact):
	mOwner(contact)
{
	createUI();
}

/**
 * Destructor.
 */
EditDelete::~EditDelete()
{
	DELETE(mDialog);
}

/**
 * Create the UI for delete button.
 */
void EditDelete::createUI()
{
	fillSpaceHorizontally();
	setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);

	mButton = new Button();
	mButton->fillSpaceHorizontally();
	mButton->setText("Delete");
	mButton->addButtonListener(this);

	addChild(mButton);

	mDialog = new ConfirmDialog(this);
}

/**
 * This method is called if the touch-up event was inside the
 * bounds of the button.
 * @param button The button object that generated the event.
 */
void EditDelete::buttonClicked(Widget* button)
{
	if (button == mButton)
	{
		mDialog->show();
	}
}

/**
 * Deletes the contact.
 */
void EditDelete::update()
{
	ScreenContainer::getInstance()->pop();
	mOwner->remove();
	closeContacts();
}

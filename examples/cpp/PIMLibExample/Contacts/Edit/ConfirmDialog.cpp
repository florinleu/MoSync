/* Copyright (C) 2012 MoSync AB

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
 * @file TypeDialog.h
 * @author Florin Leu
 * @date 09 May 2012
 *
 * @brief Edit type dialog.
 *
 **/

#include <NativeUI/Label.h>
#include <NativeUI/HorizontalLayout.h>
#include <NativeUI/VerticalLayout.h>

#include "ConfirmDialog.h"

#include "EditDelete.h"

#include "Utils.h"

using namespace NativeUI;

/**
 * Constructor.
 */
ConfirmDialog::ConfirmDialog(EditDelete* owner)
{
	mOwner = owner;
	createUI();
}

/**
 * Destructor.
 */
ConfirmDialog::~ConfirmDialog()
{
}

/**
 * Creates the UI for this screen.
 */
void ConfirmDialog::createUI()
{
	VerticalLayout* body = new VerticalLayout();
	body->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	body->wrapContentHorizontally();

	Label* description = new Label();
	description->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	description->setText("Are you sure?");
	body->addChild(description);

	HorizontalLayout* buttonLayout = new HorizontalLayout();
	buttonLayout->wrapContentHorizontally();

	mOKButton = new Button();
	mOKButton->wrapContentHorizontally();
	mOKButton->wrapContentVertically();
	mOKButton->setText("OK");
	mOKButton->addButtonListener(this);

	mCancelButton = new Button();
	mCancelButton->wrapContentHorizontally();
	mCancelButton->setText("Cancel");
	mCancelButton->addButtonListener(this);

	buttonLayout->addChild(mOKButton);
	buttonLayout->addChild(mCancelButton);

	body->addChild(buttonLayout);

	addChild(body);
}

/**
 * This method is called if the touch-up event was inside the
 * bounds of the button.
 * @param button The button object that generated the event.
 */
void ConfirmDialog::buttonClicked(Widget* button)
{
	if (button == mOKButton)
	{
		mOwner->update();
	}
	hide();
}

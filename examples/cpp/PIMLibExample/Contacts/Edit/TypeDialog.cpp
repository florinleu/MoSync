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
 * @file TypeDialog.cpp
 * @author Florin Leu
 * @date 09 Mar 2012
 *
 * @brief The game dialog.
 *
 **/

#include <util.h>
#include <NativeUI/VerticalLayout.h>
#include <NativeUI/HorizontalLayout.h>
#include <NativeUI/Label.h>

#include "EditField.h"
#include "Utils.h"

#include "TypeDialog.h"

using namespace NativeUI;

/**
 * Constructor.
 */
TypeDialog::TypeDialog():
	mCheckBoxesLength(0),
	mPrevCheckBox(-1)
{
	createUI();
}

/**
 * Destructor.
 */
TypeDialog::~TypeDialog()
{
	mOKButton->removeButtonListener(this);
	mCancelButton->removeButtonListener(this);
}

TypeDialog* TypeDialog::instance = NULL;

/**
 * Returns the single instance of this.
 */
TypeDialog* TypeDialog::getInstance()
{
	if (instance == NULL)
	{
		instance = new TypeDialog();
	}
	return instance;
}

/**
 * Creates the UI for this screen.
 */
void TypeDialog::createUI()
{
//	setWidth(ColorMatcher::sScreenWidth /2);
//	setPosition(ColorMatcher::sScreenWidth / 4, ColorMatcher::sScreenWidth / 4);

	VerticalLayout* layout = new VerticalLayout();
	layout->fillSpaceHorizontally();
	layout->wrapContentVertically();
	layout->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);

	mBody = new VerticalLayout();
	layout->addChild(mBody);

	HorizontalLayout* buttonLayout = new HorizontalLayout();

	mOKButton = new Button();
	mOKButton->setText("OK");
	mOKButton->addButtonListener(this);

	mCancelButton = new Button();
	mCancelButton->setText("Cancel");
	mCancelButton->addButtonListener(this);

	buttonLayout->addChild(mOKButton);
	buttonLayout->addChild(mCancelButton);
	layout->addChild(buttonLayout);

	wrapContentVertically();
	wrapContentHorizontally();
	addChild(layout);
}

/**
 * Sets the information to be displayed.
 * @param types	The field types.
 * @param index The index of this subfield.
 * @param length The number of types.
 * @param current The current type index.
 * @param label The field custom label.
 */
void TypeDialog::setFeed(EditField* owner, const int index,
		const char** types, int length, int current, const wchar* label)
{
	clearBody();

	DELETE_ARRAY(mCheckBoxes, mCheckBoxesLength);
	mCheckBoxesLength = length;
	mCheckBoxes = new CheckBox*[length];

	for (int i=0; i<length; i++)
	{
		HorizontalLayout* layout = new HorizontalLayout();

		mCheckBoxes[i] = new CheckBox();
		mCheckBoxes[i]->setState(i == current);
		mCheckBoxes[i]->addCheckBoxListener(this);
		layout->addChild(mCheckBoxes[i]);

		Label* label = new Label();
		label->setText(types[i]);
		layout->addChild(label);

		mBody->addChild(layout);
	}

	mCheckBoxes[current]->setState(true);

	mCustomLabel = new EditBox();
	mCustomLabel->fillSpaceHorizontally();
	mCustomLabel->setText(wstrtostr(label));
	mCustomLabel->setEnabled((current == (length - 1)));
	mBody->addChild(mCustomLabel);

	mOwner = owner;
	mOwnerIndex = index;
}

/**
 * Clears all children.
 */
void TypeDialog::clearBody()
{
	for (int i=mBody->countChildWidgets() - 1; i>=0; i--)
	{
		mBody->removeChild(mBody->getChild(i));
	}
}

/**
 * This method is called if the touch-up event was inside the
 * bounds of the button.
 * @param button The button object that generated the event.
 */
void TypeDialog::buttonClicked(Widget* button)
{
	if (button == mCancelButton)
	{
		hide();
	}
	else if (button == mOKButton)
	{
		for (int i=0; i<mCheckBoxesLength; i++)
		{
			if (mCheckBoxes[i]->isChecked())
			{
				mOwner->update(mOwnerIndex, i, mCustomLabel->getText());
				break;
			}
		}		;
		hide();
	}
}

/**
 * This method is called when the state of the check box was changed
 * by the user.
 * @param checkBox The check box object that generated the event.
 * @param state True if the check box is checked, false otherwise.
 */
void TypeDialog::checkBoxStateChanged(CheckBox* checkBox, bool state)
{
	if (state == true)
	{
		if (mPrevCheckBox != -1)
		{
			mCheckBoxes[mPrevCheckBox]->setState(false);
			if (mPrevCheckBox == (mCheckBoxesLength - 1))
			{
				mCustomLabel->setEnabled(false);
			}
		}

		if (checkBox == mCheckBoxes[mCheckBoxesLength - 1])
		{
			mCustomLabel->setEnabled(state);
		}

		for (int i=0; i<mCheckBoxesLength; i++)
		{
			if (checkBox == mCheckBoxes[i])
			{
				mPrevCheckBox = i;
			}
		}
	}
	else
	{
		for (int i=0; i<mCheckBoxesLength; i++)
		{
			if (mCheckBoxes[i]->isChecked())
			{
				return;
			}
		}
		mPrevCheckBox = -1;
		checkBox->setState(true);
	}
}

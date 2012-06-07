/*
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
 * @file EditEmail.cpp
 * @author Florin Leu
 * @date 22 May 2012
 *
 * @brief Email Edit Layout.
 *
 **/

#include <util.h>
#include <MAUtil/String.h>
#include <mawvsprintf.h>

#include "ContactsScreen.h"

#include "EditEmail.h"
#include "EditDefines.h"

#include "TypeDialog.h"
#include "ConfirmDialog.h"

using namespace PIM;
using namespace NativeUI;
using namespace MAUtil;

/**
 * Constructor.
 * @param contact The owner of this field.
 */
EditEmail::EditEmail(Contact* contact):
	EditField(contact)
{
	initData();
	createUI();

	mDialog = new ConfirmDialog(this);
}

/**
 * Destructor.
 */
EditEmail::~EditEmail()
{
	DELETE(mDialog);
	DELETE(mDeleteButton);
}

/**
 * Inits the data used to display this field.
 */
void EditEmail::initData()
{
	mTitleText = strdup(TXT_EDIT_EMAIL_TITLE);
	mDeleteButton = new Button*[mOwner->getEmailsCount()];
}

/**
 * Creates the view.
 */
void EditEmail::addBody()
{
	const char* labels[] =
	{
		"address",
	};

	EditField::addBody();

	for (int i=0; i<mOwner->getEmailsCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d.", i + 1);
		addSubTitle(title, i);
		addType(i, ContactsScreen::getEmailTypeString(mOwner->getEmail(i)->getType(), mOwner->getEmail(i)->getLabel()),
				mOwner->getEmail(i)->isPrimary());
		DELETE(title);

		Email* email = mOwner->getEmail(i);

		const char* texts[] =
		{
			wstrtostr(email->getAddress()),
		};

		const int datas[] =
		{
			Email::ADDRESS | (i << 8),
		};

		addSubFields(labels, texts, datas, sizeof(labels)/sizeof(char*), EDIT_EMAIL_FLAGS);
	}
}

/**
 * This method is called when an edit box loses focus.
 * The virtual keyboard is hidden.
 * Only for iphone platform.
 * @param editBox The edit box object that generated the event.
 */
void EditEmail::editBoxEditingDidEnd(EditBox* editBox)
{
	int data = *(int*)(editBox->getData());
	wchar* text = strtowstr(editBox->getText().c_str());
	printf("Edit box did end %d.", data);

	Email* email = mOwner->getEmail(data >> 8);

	switch (data & 0xFF)
	{
		case Email::ADDRESS:
			email->setAddress(text);
			break;
	}
}

/**
 * This method is called when the return button was pressed.
 * On iphone platform the virtual keyboard is not hidden after
 * receiving this event.
 * @param editBox The edit box object that generated the event.
 */
void EditEmail::editBoxReturn(EditBox* editBox)
{
	editBox->hideKeyboard();

	//fleu TODO remove this after didend is implemented
	int data = *(int*)(editBox->getData());
	wchar* text = strtowstr(editBox->getText().c_str());
	printf("Edit box did end %d %S.", data, text);

	Email* email = mOwner->getEmail(data >> 8);

	switch (data & 0xFF)
	{
		case Email::ADDRESS:
			email->setAddress(text);
			break;
	}
}

/**
 * This method is called when the state of the check box was changed
 * by the user.
 * @param checkBox The check box object that generated the event.
 * @param state True if the check box is checked, false otherwise.
 */
void EditEmail::checkBoxStateChanged(CheckBox *checkBox, bool state)
{
	int data = *(int*)(checkBox->getData());
	Email* email = mOwner->getEmail(data);
	email->setPrimary(state);
}

/**
 * This method is called if the touch-up event was inside the bounds of the button.
 * @param button The button object that generated the event.
 */
void EditEmail::buttonClicked(Widget* button)
{
	if (button == mTitle)
	{
		EditField::buttonClicked(button);
	}
	else
	{
		int data = *(int*)(button->getData());

		if (button == mDeleteButton[data])
		{
			mDialog->show();
			mCurrentSubField = data;
		}
		else
		{
			TypeDialog::getInstance()->setFeed(this, data, ContactsScreen::sEmailTypes,
					sizeof(ContactsScreen::sEmailTypes)/sizeof(char*),
					(int)mOwner->getEmail(data)->getType(),
					mOwner->getEmail(data)->getLabel());
			TypeDialog::getInstance()->show();
		}
	}
}

/**
 * Updates the type and custom label for the field.
 * @param index The index of the subfield.
 * @param type The type to set.
 * @param label The label to set.
 */
void EditEmail::update(int index, int type, String label)
{
	mOwner->getEmail(index)->setType((Email::eTypes)type);

	if (type == Email::TYPE_CUSTOM)
	{
		mOwner->getEmail(index)->setLabel(strtowstr(label.c_str())); //fleu TODO label has and extra character at the end
	}

	mTypes[index]->setText(ContactsScreen::getEmailTypeString(
			mOwner->getEmail(index)->getType(), mOwner->getEmail(index)->getLabel()));
}

/**
 * Updates the email.
 */
void EditEmail::update()
{
	mOwner->removeEmail(mCurrentSubField);
	clearBody();
	addBody();
	addChild(mBody);
}

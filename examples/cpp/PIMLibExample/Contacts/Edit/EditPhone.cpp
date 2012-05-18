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
 * @file EditPhone.cpp
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Phone Edit Layout.
 *
 **/

#include <util.h>
#include <MAUtil/String.h>
#include <mawvsprintf.h>

#include "ContactsScreen.h"

#include "EditPhone.h"
#include "EditDefines.h"

#include "TypeDialog.h"

using namespace PIM;
using namespace NativeUI;
using namespace MAUtil;

/**
 * Constructor.
 * @param contact The owner of this field.
 */
EditPhone::EditPhone(Contact* contact):
	EditField(contact)
{
	initData();
	createUI();
}

/**
 * Destructor.
 */
EditPhone::~EditPhone()
{

}

/**
 * Inits the data used to display this field.
 */
void EditPhone::initData()
{
	mTitleText = strdup(TXT_EDIT_PHONE_TITLE);
}

/**
 * Creates the view.
 */
void EditPhone::addBody()
{
	const char* labels[] =
	{
		"number"
	};

	EditField::addBody();

	for (int i=0; i<mOwner->getPhonesCount(); i++)
	{
		printf("Phone %d type %d", i, mOwner->getPhone(i)->getType());
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d.", i + 1);
		addSubTitle(title);
		addType(i, ContactsScreen::getPhoneTypeString(mOwner->getPhone(i)->getType(), mOwner->getPhone(i)->getLabel()),
				mOwner->getPhone(i)->isPrimary());
		DELETE(title);

		Phone* phone = mOwner->getPhone(i);

		const char* texts[] =
		{
			wstrtostr(phone->getNumber()),
		};

		const int datas[] =
		{
			Phone::NUMBER | (i << 8),
		};

		addSubFields(labels, texts, datas, sizeof(labels)/sizeof(char*), EDIT_ADDRESS_FLAGS);
	}
}

/**
 * This method is called when an edit box loses focus.
 * The virtual keyboard is hidden.
 * Only for iphone platform.
 * @param editBox The edit box object that generated the event.
 */
void EditPhone::editBoxEditingDidEnd(EditBox* editBox)
{
	int data = *(int*)(editBox->getData());
	wchar* text = strtowstr(editBox->getText().c_str());
	printf("Edit box did end %d.", data);

	Phone* phone = mOwner->getPhone(data >> 8);

	switch (data & 0xFF)
	{
		case Phone::NUMBER:
			phone->setNumber(text);
			break;
	}
}

/**
 * This method is called when the return button was pressed.
 * On iphone platform the virtual keyboard is not hidden after
 * receiving this event.
 * @param editBox The edit box object that generated the event.
 */
void EditPhone::editBoxReturn(EditBox* editBox)
{
	editBox->hideKeyboard();

	//fleu TODO remove this after didend is implemented
	int data = *(int*)(editBox->getData());
	wchar* text = strtowstr(editBox->getText().c_str());
	printf("Edit box did end %d.", data);

	Phone* phone = mOwner->getPhone(data >> 8);

	switch (data & 0xFF)
	{
		case Phone::NUMBER:
			phone->setNumber(text);
			break;
	}
}

/**
 * This method is called when the state of the check box was changed
 * by the user.
 * @param checkBox The check box object that generated the event.
 * @param state True if the check box is checked, false otherwise.
 */
void EditPhone::checkBoxStateChanged(CheckBox *checkBox, bool state)
{
	printf("EditPhone check box changed");
	int data = *(int*)(checkBox->getData());
	printf("Phone index = %d", data);
	Phone* phone = mOwner->getPhone(data);
	phone->setPrimary(state);
}

/**
 * This method is called if the touch-up event was inside the bounds of the button.
 * @param button The button object that generated the event.
 */
void EditPhone::buttonClicked(Widget* button)
{
	if (button == mTitle)
	{
		EditField::buttonClicked(button);
	}
	else
	{
		printf("EditPhone button clicked");
		int data = *(int*)(button->getData());
		printf("Phone index = %d", data);

		TypeDialog::getInstance()->setFeed(this, data, ContactsScreen::sPhoneTypes,
				sizeof(ContactsScreen::sPhoneTypes)/sizeof(char*),
				(int)mOwner->getPhone(data)->getType(),
				mOwner->getPhone(data)->getLabel());
		TypeDialog::getInstance()->show();
	}
}

/**
 * Updates the type and custom label for the field.
 * @param index The index of the subfield.
 * @param type The type to set.
 * @param label The label to set.
 */
void EditPhone::update(int index, int type, String label)
{
	printf("Update type for the Phone");
	mOwner->getPhone(index)->setType((Phone::eTypes)type);

	if (type == Phone::CUSTOM)
	{
		printf("Update label for the Phone");
		mOwner->getPhone(index)->setLabel(strtowstr(label.c_str())); //fleu TODO label has and extra character at the end
	}

	mTypes[index]->setText(ContactsScreen::getPhoneTypeString(
			mOwner->getPhone(index)->getType(), mOwner->getPhone(index)->getLabel()));
}

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
 * @file EditAddress.cpp
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Address Edit Layout.
 *
 **/

#include <util.h>
#include <MAUtil/String.h>
#include <mawvsprintf.h>
#include <mawstring.h>

#include "ContactsScreen.h"

#include "EditAddress.h"
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
EditAddress::EditAddress(Contact* contact):
	EditField(contact)
{
	initData();
	createUI();

	mDialog = new ConfirmDialog(this);
}

/**
 * Destructor.
 */
EditAddress::~EditAddress()
{
	DELETE(mDialog);
	DELETE(mDeleteButton);
}

/**
 * Inits the data used to display this field.
 */
void EditAddress::initData()
{
	mTitleText = strdup(TXT_EDIT_ADDRESS_TITLE);
	mDeleteButton = new Button*[mOwner->getAddressesCount()];
}

/**
 * Creates the view.
 */
void EditAddress::addBody()
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

	EditField::addBody();

	for (int i=0; i<mOwner->getAddressesCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d.", i + 1);
		addSubTitle(title, i);
		addType(i, ContactsScreen::getAddressTypeString(mOwner->getAddress(i)->getType(), mOwner->getAddress(i)->getLabel()),
				mOwner->getAddress(i)->isPrimary());
		DELETE(title);

		Address* address = mOwner->getAddress(i);

		const char* texts[] =
		{
			wstrtostr(address->getStreet()),
			wstrtostr(address->getCity()),
			wstrtostr(address->getState()),
			wstrtostr(address->getPostalCode()),
			wstrtostr(address->getCountry()),
			wstrtostr(address->getNeighborhood()),
			wstrtostr(address->getPOBox()),
			wstrtostr(address->getFormattedAddress())
		};

		const int datas[] =
		{
			Address::STREET | (i << 8),
			Address::CITY | (i << 8),
			Address::STATE | (i << 8),
			Address::POSTAL_CODE | (i << 8),
			Address::COUNTRY | (i << 8),
			Address::NEIGHBORHOOD | (i << 8),
			Address::PO_BOX | (i << 8),
			Address::FORMATTED_ADDRESS | (i << 8)
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
void EditAddress::editBoxEditingDidEnd(EditBox* editBox)
{
	int data = *(int*)(editBox->getData());
	wchar* text = strtowstr(editBox->getText().c_str());
	printf("Edit box did end %d.", data);

	Address* address = mOwner->getAddress(data >> 8);

	switch (data & 0xFF)
	{
		case Address::STREET:
			address->setStreet(text);
			break;
		case Address::CITY:
			address->setCity(text);
			break;
		case Address::STATE:
			address->setState(text);
			break;
		case Address::POSTAL_CODE:
			address->setPostalCode(text);
			break;
		case Address::COUNTRY:
			address->setCountry(text);
			break;
		case Address::NEIGHBORHOOD:
			address->setNeighborhood(text);
			break;
		case Address::PO_BOX:
			address->setPOBox(text);
			break;
	}
}

/**
 * This method is called when the return button was pressed.
 * On iphone platform the virtual keyboard is not hidden after
 * receiving this event.
 * @param editBox The edit box object that generated the event.
 */
void EditAddress::editBoxReturn(EditBox* editBox)
{
	editBox->hideKeyboard();

	//fleu TODO remove this after didend is implemented
	int data = *(int*)(editBox->getData());
	wchar* text = strtowstr(editBox->getText().c_str());
	printf("Edit box did end %d.", data);

	Address* address = mOwner->getAddress(data >> 8);

	switch (data & 0xFF)
	{
		case Address::STREET:
			address->setStreet(text);
			break;
		case Address::CITY:
			address->setCity(text);
			break;
		case Address::STATE:
			address->setState(text);
			break;
		case Address::POSTAL_CODE:
			address->setPostalCode(text);
			break;
		case Address::COUNTRY:
			address->setCountry(text);
			break;
		case Address::NEIGHBORHOOD:
			address->setNeighborhood(text);
			break;
		case Address::PO_BOX:
			address->setPOBox(text);
			break;
	}
}

/**
 * This method is called when the state of the check box was changed
 * by the user.
 * @param checkBox The check box object that generated the event.
 * @param state True if the check box is checked, false otherwise.
 */
void EditAddress::checkBoxStateChanged(CheckBox *checkBox, bool state)
{
	printf("EditAddress check box changed");
	int data = *(int*)(checkBox->getData());
	printf("Address index = %d", data);
	Address* address = mOwner->getAddress(data);
	address->setPrimary(state);
}

/**
 * This method is called if the touch-up event was inside the bounds of the button.
 * @param button The button object that generated the event.
 */
void EditAddress::buttonClicked(Widget* button)
{
	if (button == mTitle)
	{
		EditField::buttonClicked(button);
	}
	else
	{
		printf("EditAddress button clicked");
		int data = *(int*)(button->getData());

		if (button == mDeleteButton[data])
		{
			mDialog->show();
			mCurrentSubField = data;
		}
		else
		{
			TypeDialog::getInstance()->setFeed(this, data, ContactsScreen::sAddressTypes,
					sizeof(ContactsScreen::sAddressTypes)/sizeof(char*),
					(int)mOwner->getAddress(data)->getType(),
					mOwner->getAddress(data)->getLabel());
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
void EditAddress::update(int index, int type, String label)
{
	printf("Update type for the Address");
	mOwner->getAddress(index)->setType((Address::eTypes)type);

	if (type == Address::TYPE_CUSTOM)
	{
		wchar* tmp = strtowstr(label.c_str());
		printf("size %d, string %S", wcslen(tmp), tmp);
		printf("Update label for the Address");
		mOwner->getAddress(index)->setLabel(strtowstr(label.c_str())); //fleu TODO label has and extra character at the end
	}

	mTypes[index]->setText(ContactsScreen::getAddressTypeString(
			mOwner->getAddress(index)->getType(), mOwner->getAddress(index)->getLabel()));
}

/**
 * Updates the address.
 */
void EditAddress::update()
{
	mOwner->removeAddress(mCurrentSubField);
	clearBody();
	addBody();
	addChild(mBody);
}

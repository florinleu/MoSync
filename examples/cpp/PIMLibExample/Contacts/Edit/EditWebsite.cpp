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
 * @file EditWebsite.cpp
 * @author Florin Leu
 * @date 30 May 2012
 *
 * @brief Website Edit Layout.
 *
 **/

#include <util.h>
#include <MAUtil/String.h>
#include <mawvsprintf.h>

#include "ContactsScreen.h"

#include "EditWebsite.h"
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
EditWebsite::EditWebsite(Contact* contact):
	EditField(contact)
{
	initData();
	createUI();

	mDialog = new ConfirmDialog(this);
}

/**
 * Destructor.
 */
EditWebsite::~EditWebsite()
{
	DELETE(mDialog);
	DELETE(mDeleteButton);
}

/**
 * Inits the data used to display this field.
 */
void EditWebsite::initData()
{
	mTitleText = strdup(TXT_EDIT_WEBSITE_TITLE);
	mDeleteButton = new Button*[mOwner->getWebsitesCount()];
}

/**
 * Creates the view.
 */
void EditWebsite::addBody()
{
	const char* labels[] =
	{
		"url",
	};

	EditField::addBody();

	printf("##########################################Add websites");

	for (int i=0; i<mOwner->getWebsitesCount(); i++) //fleu TODO int count =
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d.", i + 1);
		addSubTitle(title, i);
		addType(i, ContactsScreen::getWebsiteTypeString(mOwner->getWebsite(i)->getType(), mOwner->getWebsite(i)->getLabel()),
				mOwner->getWebsite(i)->isPrimary());
		DELETE(title);

		Website* website = mOwner->getWebsite(i);

		const char* texts[] =
		{
			wstrtostr(website->getURL()),
		};

		const int datas[] =
		{
			Website::URL | (i << 8),
		};

		addSubFields(labels, texts, datas, sizeof(labels)/sizeof(char*), EDIT_WEBSITE_FLAGS);
	}
}

/**
 * This method is called when an edit box loses focus.
 * The virtual keyboard is hidden.
 * Only for iphone platform.
 * @param editBox The edit box object that generated the event.
 */
void EditWebsite::editBoxEditingDidEnd(EditBox* editBox)
{
	int data = *(int*)(editBox->getData());
	wchar* text = strtowstr(editBox->getText().c_str());
	printf("Edit box did end %d.", data);

	Website* website = mOwner->getWebsite(data >> 8);

	switch (data & 0xFF)
	{
		case Website::URL:
			website->setURL(text);
			break;
	}
}

/**
 * This method is called when the return button was pressed.
 * On iphone platform the virtual keyboard is not hidden after
 * receiving this event.
 * @param editBox The edit box object that generated the event.
 */
void EditWebsite::editBoxReturn(EditBox* editBox)
{
	editBox->hideKeyboard();

	//fleu TODO remove this after didend is implemented
	int data = *(int*)(editBox->getData());
	wchar* text = strtowstr(editBox->getText().c_str());
	printf("Edit box did end %d %S.", data, text);

	Website* website = mOwner->getWebsite(data >> 8);

	switch (data & 0xFF)
	{
		case Website::URL:
			website->setURL(text);
			break;
	}
}

/**
 * This method is called when the state of the check box was changed
 * by the user.
 * @param checkBox The check box object that generated the event.
 * @param state True if the check box is checked, false otherwise.
 */
void EditWebsite::checkBoxStateChanged(CheckBox *checkBox, bool state)
{
	int data = *(int*)(checkBox->getData());
	printf("Check box %d changed %d.", data, state);
	Website* website = mOwner->getWebsite(data);
	website->setPrimary(state);
}

/**
 * This method is called if the touch-up event was inside the bounds of the button.
 * @param button The button object that generated the event.
 */
void EditWebsite::buttonClicked(Widget* button)
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
			TypeDialog::getInstance()->setFeed(this, data, ContactsScreen::sWebsiteTypes,
					sizeof(ContactsScreen::sWebsiteTypes)/sizeof(char*),
					(int)mOwner->getWebsite(data)->getType(),
					mOwner->getWebsite(data)->getLabel());
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
void EditWebsite::update(int index, int type, String label)
{
	mOwner->getWebsite(index)->setType((Website::eTypes)type);

	if (type == Website::CUSTOM)
	{
		mOwner->getWebsite(index)->setLabel(strtowstr(label.c_str())); //fleu TODO label has and extra character at the end
	}

	mTypes[index]->setText(ContactsScreen::getWebsiteTypeString(
			mOwner->getWebsite(index)->getType(), mOwner->getWebsite(index)->getLabel()));
}

/**
 * Updates the website.
 */
void EditWebsite::update()
{
	mOwner->removeWebsite(mCurrentSubField);
	clearBody();
	addBody();
	addChild(mBody);
}

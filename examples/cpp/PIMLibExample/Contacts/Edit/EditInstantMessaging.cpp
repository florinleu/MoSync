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
 * @file EditInstantMessaging.cpp
 * @author Florin Leu
 * @date 01 Jun 2012
 *
 * @brief Instant Messaging Edit Layout.
 *
 **/

#include <util.h>
#include <MAUtil/String.h>
#include <mawvsprintf.h>
#include <mawstring.h>

#include <NativeUI/Label.h>
#include <NativeUI/HorizontalLayout.h>

#include "ContactsScreen.h"

#include "EditInstantMessaging.h"
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
EditInstantMessaging::EditInstantMessaging(Contact* contact):
	EditField(contact),
	bChooseProtocol(false)
{
	initData();
	createUI();

	mDialog = new ConfirmDialog(this);
}

/**
 * Destructor.
 */
EditInstantMessaging::~EditInstantMessaging()
{
	DELETE(mDialog);
	DELETE(mDeleteButton);
}

/**
 * Inits the data used to display this field.
 */
void EditInstantMessaging::initData()
{
	mTitleText = strdup(TXT_EDIT_IM_TITLE);
	mDeleteButton = new Button*[mOwner->getInstantMessagingsCount()];
}

/**
 * Ads protocol for instant messaging.
 * @param index		The index of the field.
 * @param text		The type text.
 */
void EditInstantMessaging::addProtocol(int index, const char* text)
{
	HorizontalLayout* layoutType = new HorizontalLayout();
	layoutType->wrapContentVertically();
	layoutType->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);

	Label* labelType = new Label();
	labelType->setWidth(EDIT_LABEL_WIDTH);
	labelType->setFont(mLabelFont);
	labelType->setText("protocol");
	labelType->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
	labelType->setTextVerticalAlignment(MAW_ALIGNMENT_CENTER);
	layoutType->addChild(labelType);

	Button* dataType = new Button();
	dataType->fillSpaceHorizontally();
	dataType->setText(text);
	dataType->setData(createData(index));
	dataType->addButtonListener(this);
	//dataType->setFont(mDataFont);
	layoutType->addChild(dataType);
	mProtocols.add(dataType);

	mBody->addChild(layoutType);
}

/**
 * Creates the view.
 */
void EditInstantMessaging::addBody()
{
	const char* labels[] =
	{
		"username",
	};

	EditField::addBody();

	for (int i=0; i<mOwner->getInstantMessagingsCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d.", i + 1);
		addSubTitle(title, i);
		addType(i, ContactsScreen::getIMTypeString(mOwner->getInstantMessaging(i)->getType(), mOwner->getInstantMessaging(i)->getLabel()),
				mOwner->getInstantMessaging(i)->isPrimary());
		DELETE(title);

		InstantMessaging* im = mOwner->getInstantMessaging(i);

		const char* texts[] =
		{
			wstrtostr(im->getUsername())
		};

		const int datas[] =
		{
			InstantMessaging::USERNAME | (i << 8),
		};

		addSubFields(labels, texts, datas, sizeof(labels)/sizeof(char*), EDIT_IM_FLAGS);

		addProtocol(i, ContactsScreen::getIMProtocolString(mOwner->getInstantMessaging(i)->getProtocol(), mOwner->getInstantMessaging(i)->getProtocolLabel()));
	}
}

/**
 * This method is called when an edit box loses focus.
 * The virtual keyboard is hidden.
 * Only for iphone platform.
 * @param editBox The edit box object that generated the event.
 */
void EditInstantMessaging::editBoxEditingDidEnd(EditBox* editBox)
{
	int data = *(int*)(editBox->getData());
	wchar* text = strtowstr(editBox->getText().c_str());
	printf("Edit box did end %d.", data);

	InstantMessaging* im = mOwner->getInstantMessaging(data >> 8);

	switch (data & 0xFF)
	{
		case InstantMessaging::USERNAME:
			im->setUsername(text);
			break;
	}
}

/**
 * This method is called when the return button was pressed.
 * On iphone platform the virtual keyboard is not hidden after
 * receiving this event.
 * @param editBox The edit box object that generated the event.
 */
void EditInstantMessaging::editBoxReturn(EditBox* editBox)
{
	editBox->hideKeyboard();

	//fleu TODO remove this after didend is implemented
	int data = *(int*)(editBox->getData());
	wchar* text = strtowstr(editBox->getText().c_str());
	printf("Edit box did end %d.", data);

	InstantMessaging* im = mOwner->getInstantMessaging(data >> 8);

	switch (data & 0xFF)
	{
		case InstantMessaging::USERNAME:
			im->setUsername(text);
			break;
	}
}

/**
 * This method is called when the state of the check box was changed
 * by the user.
 * @param checkBox The check box object that generated the event.
 * @param state True if the check box is checked, false otherwise.
 */
void EditInstantMessaging::checkBoxStateChanged(CheckBox *checkBox, bool state)
{
	printf("EditInstantMessaging check box changed");
	int data = *(int*)(checkBox->getData());
	printf("InstantMessaging index = %d", data);
	InstantMessaging* im = mOwner->getInstantMessaging(data);
	im->setPrimary(state);
}

/**
 * This method is called if the touch-up event was inside the bounds of the button.
 * @param button The button object that generated the event.
 */
void EditInstantMessaging::buttonClicked(Widget* button)
{
	if (button == mTitle)
	{
		EditField::buttonClicked(button);
	}
	else
	{
		printf("EditInstantMessaging button clicked");
		int data = *(int*)(button->getData());

		if (button == mDeleteButton[data])
		{
			mDialog->show();
			mCurrentSubField = data;
		}
		else if (button == mProtocols[data])
		{
			bChooseProtocol = true;
			TypeDialog::getInstance()->setFeed(this, data, ContactsScreen::sIMProtocols,
					sizeof(ContactsScreen::sIMProtocols)/sizeof(char*),
					(int)mOwner->getInstantMessaging(data)->getProtocol(),
					mOwner->getInstantMessaging(data)->getProtocolLabel());
			TypeDialog::getInstance()->show();
		}
		else
		{
			TypeDialog::getInstance()->setFeed(this, data, ContactsScreen::sIMTypes,
					sizeof(ContactsScreen::sIMTypes)/sizeof(char*),
					(int)mOwner->getInstantMessaging(data)->getType(),
					mOwner->getInstantMessaging(data)->getLabel());
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
void EditInstantMessaging::update(int index, int type, String label)
{
	printf("Update type for the InstantMessaging");

	if (bChooseProtocol)
	{
		mOwner->getInstantMessaging(index)->setProtocol((InstantMessaging::eProtocols)type);

		if (type == InstantMessaging::PROTOCOL_CUSTOM)
		{
			wchar* tmp = strtowstr(label.c_str());
			printf("size %d, string %S", wcslen(tmp), tmp);
			printf("Update protocol label for the InstantMessaging");
			mOwner->getInstantMessaging(index)->setProtocolLabel(strtowstr(label.c_str())); //fleu TODO label has and extra character at the end
		}

		mProtocols[index]->setText(ContactsScreen::getIMProtocolString(
				mOwner->getInstantMessaging(index)->getProtocol(), mOwner->getInstantMessaging(index)->getProtocolLabel()));
	}
	else
	{
		mOwner->getInstantMessaging(index)->setType((InstantMessaging::eTypes)type);

		if (type == InstantMessaging::TYPE_CUSTOM)
		{
			wchar* tmp = strtowstr(label.c_str());
			printf("size %d, string %S", wcslen(tmp), tmp);
			printf("Update label for the InstantMessaging");
			mOwner->getInstantMessaging(index)->setLabel(strtowstr(label.c_str())); //fleu TODO label has and extra character at the end
		}

		mTypes[index]->setText(ContactsScreen::getIMTypeString(
				mOwner->getInstantMessaging(index)->getType(), mOwner->getInstantMessaging(index)->getLabel()));
	}
	bChooseProtocol = false;
}

/**
 * Updates the address.
 */
void EditInstantMessaging::update()
{
	mOwner->removeInstantMessaging(mCurrentSubField);
	clearBody();
	addBody();
	addChild(mBody);
}

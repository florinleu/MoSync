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
 * @file EditSocialProfile.cpp
 * @author Florin Leu
 * @date 07 Jun 2012
 *
 * @brief Social Profile Edit Layout.
 *
 **/

#include <util.h>
#include <MAUtil/String.h>
#include <mawvsprintf.h>
#include <mawstring.h>

#include <NativeUI/Label.h>
#include <NativeUI/HorizontalLayout.h>

#include "ContactsScreen.h"

#include "EditSocialProfile.h"
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
EditSocialProfile::EditSocialProfile(Contact* contact):
	EditField(contact),
	bChooseService(false)
{
	initData();
	createUI();

	mDialog = new ConfirmDialog(this);
}

/**
 * Destructor.
 */
EditSocialProfile::~EditSocialProfile()
{
	DELETE(mDialog);
	DELETE(mDeleteButton);
}

/**
 * Inits the data used to display this field.
 */
void EditSocialProfile::initData()
{
	mTitleText = strdup(TXT_EDIT_SP_TITLE);
	mDeleteButton = new Button*[mOwner->getSocialProfilesCount()];
}

/**
 * Ads protocol for social profile.
 * @param index		The index of the field.
 * @param text		The type text.
 */
void EditSocialProfile::addService(int index, const char* text)
{
	HorizontalLayout* layoutType = new HorizontalLayout();
	layoutType->wrapContentVertically();
	layoutType->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);

	Label* labelType = new Label();
	labelType->setWidth(EDIT_LABEL_WIDTH);
	labelType->setFont(mLabelFont);
	labelType->setText("service");
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
	mServices.add(dataType);

	mBody->addChild(layoutType);
}

/**
 * Creates the view.
 */
void EditSocialProfile::addBody()
{
	const char* labels[] =
	{
		"url",
		"username",
		"user identifier",
	};

	EditField::addBody();

	for (int i=0; i<mOwner->getSocialProfilesCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d.", i + 1);
		addSubTitle(title, i);
		addType(i, ContactsScreen::getSPTypeString(mOwner->getSocialProfile(i)->getType(), mOwner->getSocialProfile(i)->getLabel()),
				mOwner->getSocialProfile(i)->isPrimary());
		DELETE(title);

		SocialProfile* sp = mOwner->getSocialProfile(i);

		const char* texts[] =
		{
			wstrtostr(sp->getURL()),
			wstrtostr(sp->getUsername()),
			wstrtostr(sp->getUserIdentifier())
		};

		const int datas[] =
		{
			SocialProfile::URL | (i << 8),
			SocialProfile::USERNAME | (i << 8),
			SocialProfile::USER_IDENTIFIER | (i << 8),
		};

		addSubFields(labels, texts, datas, sizeof(labels)/sizeof(char*), EDIT_SP_FLAGS);

		addService(i, ContactsScreen::getSPServiceString(mOwner->getSocialProfile(i)->getService(), mOwner->getSocialProfile(i)->getServiceLabel()));
	}
}

/**
 * This method is called when an edit box loses focus.
 * The virtual keyboard is hidden.
 * Only for iphone platform.
 * @param editBox The edit box object that generated the event.
 */
void EditSocialProfile::editBoxEditingDidEnd(EditBox* editBox)
{
	int data = *(int*)(editBox->getData());
	wchar* text = strtowstr(editBox->getText().c_str());
	printf("Edit box did end %d.", data);

	SocialProfile* sp = mOwner->getSocialProfile(data >> 8);

	switch (data & 0xFF)
	{
		case SocialProfile::URL:
			sp->setURL(text);
			break;
		case SocialProfile::USERNAME:
			sp->setUsername(text);
			break;
		case SocialProfile::USER_IDENTIFIER:
			sp->setUserIdentifier(text);
			break;
	}
}

/**
 * This method is called when the return button was pressed.
 * On iphone platform the virtual keyboard is not hidden after
 * receiving this event.
 * @param editBox The edit box object that generated the event.
 */
void EditSocialProfile::editBoxReturn(EditBox* editBox)
{
	editBox->hideKeyboard();

	//fleu TODO remove this after didend is implemented
	int data = *(int*)(editBox->getData());
	wchar* text = strtowstr(editBox->getText().c_str());
	printf("Edit box did end %d.", data);

	SocialProfile* sp = mOwner->getSocialProfile(data >> 8);

	switch (data & 0xFF)
	{
		case SocialProfile::URL:
			sp->setURL(text);
			break;
		case SocialProfile::USERNAME:
			sp->setUsername(text);
			break;
		case SocialProfile::USER_IDENTIFIER:
			sp->setUserIdentifier(text);
			break;
	}
}

/**
 * This method is called when the state of the check box was changed
 * by the user.
 * @param checkBox The check box object that generated the event.
 * @param state True if the check box is checked, false otherwise.
 */
void EditSocialProfile::checkBoxStateChanged(CheckBox *checkBox, bool state)
{
	printf("EditSocialProfile check box changed");
	int data = *(int*)(checkBox->getData());
	printf("SocialProfile index = %d", data);
	SocialProfile* sp = mOwner->getSocialProfile(data);
	sp->setPrimary(state);
}

/**
 * This method is called if the touch-up event was inside the bounds of the button.
 * @param button The button object that generated the event.
 */
void EditSocialProfile::buttonClicked(Widget* button)
{
	if (button == mTitle)
	{
		EditField::buttonClicked(button);
	}
	else
	{
		printf("EditSocialProfile button clicked");
		int data = *(int*)(button->getData());

		if (button == mDeleteButton[data])
		{
			mDialog->show();
			mCurrentSubField = data;
		}
		else if (button == mServices[data])
		{
			bChooseService = true;
			TypeDialog::getInstance()->setFeed(this, data, ContactsScreen::sSPServices,
					sizeof(ContactsScreen::sSPServices)/sizeof(char*),
					(int)mOwner->getSocialProfile(data)->getService(),
					mOwner->getSocialProfile(data)->getServiceLabel());
			TypeDialog::getInstance()->show();
		}
		else
		{
			TypeDialog::getInstance()->setFeed(this, data, ContactsScreen::sSPTypes,
					sizeof(ContactsScreen::sSPTypes)/sizeof(char*),
					(int)mOwner->getSocialProfile(data)->getType(),
					mOwner->getSocialProfile(data)->getLabel());
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
void EditSocialProfile::update(int index, int type, String label)
{
	printf("Update type for the SocialProfile");

	if (bChooseService)
	{
		mOwner->getSocialProfile(index)->setService((SocialProfile::eServices)type);

		if (type == SocialProfile::SERVICE_CUSTOM)
		{
			wchar* tmp = strtowstr(label.c_str());
			printf("size %d, string %S", wcslen(tmp), tmp);
			printf("Update service label for the SocialProfile");
			mOwner->getSocialProfile(index)->setServiceLabel(strtowstr(label.c_str())); //fleu TODO label has and extra character at the end
		}

		mServices[index]->setText(ContactsScreen::getSPServiceString(
				mOwner->getSocialProfile(index)->getService(), mOwner->getSocialProfile(index)->getServiceLabel()));
	}
	else
	{
		mOwner->getSocialProfile(index)->setType((SocialProfile::eTypes)type);

		if (type == SocialProfile::TYPE_CUSTOM)
		{
			wchar* tmp = strtowstr(label.c_str());
			printf("size %d, string %S", wcslen(tmp), tmp);
			printf("Update label for the SocialProfile");
			mOwner->getSocialProfile(index)->setLabel(strtowstr(label.c_str())); //fleu TODO label has and extra character at the end
		}

		mTypes[index]->setText(ContactsScreen::getSPTypeString(
				mOwner->getSocialProfile(index)->getType(), mOwner->getSocialProfile(index)->getLabel()));
	}
	bChooseService = false;
}

/**
 * Updates the address.
 */
void EditSocialProfile::update()
{
	mOwner->removeSocialProfile(mCurrentSubField);
	clearBody();
	addBody();
	addChild(mBody);
}

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
 * @file EditOrganization.cpp
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Organization Edit Layout.
 *
 **/

#include <util.h>
#include <MAUtil/String.h>
#include <mawvsprintf.h>
#include <mawstring.h>

#include "ContactsScreen.h"

#include "EditOrganization.h"
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
EditOrganization::EditOrganization(Contact* contact):
	EditField(contact)
{
	initData();
	createUI();

	mDialog = new ConfirmDialog(this);
}

/**
 * Destructor.
 */
EditOrganization::~EditOrganization()
{
	DELETE(mDialog);
	DELETE(mDeleteButton);
}

/**
 * Inits the data used to display this field.
 */
void EditOrganization::initData()
{
	mTitleText = strdup(TXT_EDIT_ORGANIZATION_TITLE);
	mDeleteButton = new Button*[mOwner->getOrganizationsCount()];
}

/**
 * Creates the view.
 */
void EditOrganization::addBody()
{
	const char* labels[] =
	{
		"name",
		"title",
		"department",
		"location",
		"job description",
		"phonetic name",
		"symbol"
	};

	EditField::addBody();

	for (int i=0; i<mOwner->getOrganizationsCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d.", i + 1);
		addSubTitle(title, i);
		addType(i, ContactsScreen::getOrganizationTypeString(mOwner->getOrganization(i)->getType(), mOwner->getOrganization(i)->getLabel()),
				mOwner->getOrganization(i)->isPrimary());
		DELETE(title);

		Organization* organization = mOwner->getOrganization(i);

		const char* texts[] =
		{
			wstrtostr(organization->getName()),
			wstrtostr(organization->getTitle()),
			wstrtostr(organization->getDepartment()),
			wstrtostr(organization->getLocation()),
			wstrtostr(organization->getJobDescription()),
			wstrtostr(organization->getPhoneticName()),
			wstrtostr(organization->getSymbol())
		};

		const int datas[] =
		{
			Organization::NAME | (i << 8),
			Organization::TITLE | (i << 8),
			Organization::DEPARTMENT | (i << 8),
			Organization::LOCATION | (i << 8),
			Organization::JOB_DESCRIPTION | (i << 8),
			Organization::PHONETIC_NAME | (i << 8),
			Organization::SYMBOL | (i << 8)
		};

		addSubFields(labels, texts, datas, sizeof(labels)/sizeof(char*), EDIT_ORGANIZATION_FLAGS);
	}
}

/**
 * This method is called when an edit box loses focus.
 * The virtual keyboard is hidden.
 * Only for iphone platform.
 * @param editBox The edit box object that generated the event.
 */
void EditOrganization::editBoxEditingDidEnd(EditBox* editBox)
{
	int data = *(int*)(editBox->getData());
	wchar* text = strtowstr(editBox->getText().c_str());
	printf("Edit box did end %d.", data);

	Organization* organization = mOwner->getOrganization(data >> 8);

	switch (data & 0xFF)
	{
		case Organization::NAME:
			organization->setName(text);
			break;
		case Organization::TITLE:
			organization->setTitle(text);
			break;
		case Organization::DEPARTMENT:
			organization->setDepartment(text);
			break;
		case Organization::LOCATION:
			organization->setLocation(text);
			break;
		case Organization::JOB_DESCRIPTION:
			organization->setJobDescription(text);
			break;
		case Organization::PHONETIC_NAME:
			organization->setPhoneticName(text);
			break;
		case Organization::SYMBOL:
			organization->setSymbol(text);
			break;
	}
}

/**
 * This method is called when the return button was pressed.
 * On iphone platform the virtual keyboard is not hidden after
 * receiving this event.
 * @param editBox The edit box object that generated the event.
 */
void EditOrganization::editBoxReturn(EditBox* editBox)
{
	editBox->hideKeyboard();

	//fleu TODO remove this after didend is implemented
	int data = *(int*)(editBox->getData());
	wchar* text = strtowstr(editBox->getText().c_str());
	printf("Edit box did end %d.", data);

	Organization* organization = mOwner->getOrganization(data >> 8);

	switch (data & 0xFF)
	{
		case Organization::NAME:
			organization->setName(text);
			break;
		case Organization::TITLE:
			organization->setTitle(text);
			break;
		case Organization::DEPARTMENT:
			organization->setDepartment(text);
			break;
		case Organization::LOCATION:
			organization->setLocation(text);
			break;
		case Organization::JOB_DESCRIPTION:
			organization->setJobDescription(text);
			break;
		case Organization::PHONETIC_NAME:
			organization->setPhoneticName(text);
			break;
		case Organization::SYMBOL:
			organization->setSymbol(text);
			break;
	}
}

/**
 * This method is called when the state of the check box was changed
 * by the user.
 * @param checkBox The check box object that generated the event.
 * @param state True if the check box is checked, false otherwise.
 */
void EditOrganization::checkBoxStateChanged(CheckBox *checkBox, bool state)
{
	printf("EditOrganization check box changed");
	int data = *(int*)(checkBox->getData());
	printf("Organization index = %d", data);
	Organization* organization = mOwner->getOrganization(data);
	organization->setPrimary(state);
}

/**
 * This method is called if the touch-up event was inside the bounds of the button.
 * @param button The button object that generated the event.
 */
void EditOrganization::buttonClicked(Widget* button)
{
	if (button == mTitle)
	{
		EditField::buttonClicked(button);
	}
	else
	{
		printf("EditOrganization button clicked");
		int data = *(int*)(button->getData());

		if (button == mDeleteButton[data])
		{
			mDialog->show();
			mCurrentSubField = data;
		}
		else
		{
			TypeDialog::getInstance()->setFeed(this, data, ContactsScreen::sOrganizationTypes,
					sizeof(ContactsScreen::sOrganizationTypes)/sizeof(char*),
					(int)mOwner->getOrganization(data)->getType(),
					mOwner->getOrganization(data)->getLabel());
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
void EditOrganization::update(int index, int type, String label)
{
	printf("Update type for the Organization");
	mOwner->getOrganization(index)->setType((Organization::eTypes)type);

	if (type == Organization::TYPE_CUSTOM)
	{
		wchar* tmp = strtowstr(label.c_str());
		printf("size %d, string %S", wcslen(tmp), tmp);
		printf("Update label for the Organization");
		mOwner->getOrganization(index)->setLabel(strtowstr(label.c_str())); //fleu TODO label has and extra character at the end
	}

	mTypes[index]->setText(ContactsScreen::getOrganizationTypeString(
			mOwner->getOrganization(index)->getType(), mOwner->getOrganization(index)->getLabel()));
}

/**
 * Updates the organization.
 */
void EditOrganization::update()
{
	mOwner->removeOrganization(mCurrentSubField);
	clearBody();
	addBody();
	addChild(mBody);
}

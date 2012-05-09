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
 * @file EditName.cpp
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Name Edit Layout.
 *
 **/

#include <util.h>
#include <MAUtil/String.h>
#include <mawvsprintf.h>

#include "EditName.h"
#include "EditDefines.h"

using namespace PIM;
using namespace NativeUI;
using namespace MAUtil;

/**
 * Constructor.
 * @param contact The owner of this field.
 */
EditName::EditName(Contact* contact):
	EditField(contact)
{
	mName = contact->getName();
	initData();
	createUI();
}

/**
 * Destructor.
 */
EditName::~EditName()
{

}

/**
 * Inits the data used to display this field.
 */
void EditName::initData()
{
	mTitleText = strdup(TXT_EDIT_NAME_TITLE);
}

/**
 * Creates the view.
 */
void EditName::addBody()
{
	const char* labels[] =
	{
		"display name",
		"first name",
		"middle name",
		"last name",
		"nickname",
		"prefix",
		"suffix",
		"phonetic first",
		"phonetic middle",
		"phonetic last",
		"formatted name"
	};

	const char* texts[] =
	{
		wstrtostr(mName->getDisplayName()),
		wstrtostr(mName->getFirstName()),
		wstrtostr(mName->getMiddleName()),
		wstrtostr(mName->getLastName()),
		wstrtostr(mName->getNickname()),
		wstrtostr(mName->getPrefix()),
		wstrtostr(mName->getSuffix()),
		wstrtostr(mName->getPhoneticFirstName()),
		wstrtostr(mName->getPhoneticMiddleName()),
		wstrtostr(mName->getPhoneticLastName()),
		wstrtostr(mName->getFormattedName())
	};

	const int datas[] =
	{
		Name::DISPLAY_NAME,
		Name::FIRST_NAME,
		Name::MIDDLE_NAME,
		Name::LAST_NAME,
		Name::NICKNAME,
		Name::PREFIX,
		Name::SUFFIX,
		Name::PHONETIC_FIRST_NAME,
		Name::PHONETIC_MIDDLE_NAME,
		Name::PHONETIC_LAST_NAME,
	};

	EditField::addBody();
	addSubFields(labels, texts, datas, sizeof(labels)/sizeof(char*), EDIT_NAME_FLAGS);
}

/**
 * This method is called when an edit box loses focus.
 * The virtual keyboard is hidden.
 * Only for iphone platform.
 * @param editBox The edit box object that generated the event.
 */
void EditName::editBoxEditingDidEnd(EditBox* editBox)
{
	int data = *(int*)(editBox->getData());
	wchar* text = strtowstr(editBox->getText().c_str());
	printf("Edit box did end %d.", data);
	switch (data)
	{
		case Name::DISPLAY_NAME:
			mName->setDisplayName(text);
			break;
		case Name::FIRST_NAME:
			mName->setFirstName(text);
			break;
		case Name::MIDDLE_NAME:
			mName->setMiddleName(text);
			break;
		case Name::LAST_NAME:
			mName->setLastName(text);
			break;
		case Name::NICKNAME:
			mName->setNickname(text);
			break;
		case Name::PREFIX:
			mName->setPrefix(text);
			break;
		case Name::SUFFIX:
			mName->setSuffix(text);
			break;
		case Name::PHONETIC_FIRST_NAME:
			mName->setPhoneticFirstName(text);
			break;
		case Name::PHONETIC_MIDDLE_NAME:
			mName->setPhoneticMiddleName(text);
			break;
		case Name::PHONETIC_LAST_NAME:
			mName->setPhoneticLastName(text);
			break;
	}
}

/**
 * This method is called when the return button was pressed.
 * On iphone platform the virtual keyboard is not hidden after
 * receiving this event.
 * @param editBox The edit box object that generated the event.
 */
void EditName::editBoxReturn(NativeUI::EditBox* editBox)
{
	editBox->hideKeyboard();

	//fleu TODO remove this after didend is implemented
	int data = *((int*)(editBox->getData()));
	wchar* text = strtowstr(editBox->getText().c_str());
	printf("Edit box return text: %S; data: %d.",text, data);
	switch (data)
	{
		case Name::DISPLAY_NAME:
			mName->setDisplayName(text);
			break;
		case Name::FIRST_NAME:
			mName->setFirstName(text);
			break;
		case Name::MIDDLE_NAME:
			mName->setMiddleName(text);
			break;
		case Name::LAST_NAME:
			mName->setLastName(text);
			break;
		case Name::NICKNAME:
			mName->setNickname(text);
			break;
		case Name::PREFIX:
			mName->setPrefix(text);
			break;
		case Name::SUFFIX:
			mName->setSuffix(text);
			break;
		case Name::PHONETIC_FIRST_NAME:
			mName->setPhoneticFirstName(text);
			break;
		case Name::PHONETIC_MIDDLE_NAME:
			mName->setPhoneticMiddleName(text);
			break;
		case Name::PHONETIC_LAST_NAME:
			mName->setPhoneticLastName(text);
			break;
	}
}

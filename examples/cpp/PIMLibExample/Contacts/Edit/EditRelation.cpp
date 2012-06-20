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
 * @file EditRelation.cpp
 * @author Florin Leu
 * @date 11 Jun 2012
 *
 * @brief Relation Edit Layout.
 *
 **/

#include <util.h>
#include <MAUtil/String.h>
#include <mawvsprintf.h>

#include "ContactsScreen.h"

#include "EditRelation.h"
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
EditRelation::EditRelation(Contact* contact):
	EditField(contact)
{
	initData();
	createUI();

	mDialog = new ConfirmDialog(this);
}

/**
 * Destructor.
 */
EditRelation::~EditRelation()
{
	DELETE(mDialog);
	DELETE(mDeleteButton);
}

/**
 * Inits the data used to display this field.
 */
void EditRelation::initData()
{
	mTitleText = strdup(TXT_EDIT_RELATION_TITLE);
	mDeleteButton = new Button*[mOwner->getRelationsCount()];
}

/**
 * Creates the view.
 */
void EditRelation::addBody()
{
	const char* labels[] =
	{
		"name"
	};

	EditField::addBody();

	for (int i=0; i<mOwner->getRelationsCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d.", i + 1);
		addSubTitle(title, i);
		addType(i, ContactsScreen::getRelationTypeString(mOwner->getRelation(i)->getType(), mOwner->getRelation(i)->getLabel()),
				mOwner->getRelation(i)->isPrimary());
		DELETE(title);

		Relation* relation = mOwner->getRelation(i);

		const char* texts[] =
		{
			wstrtostr(relation->getName()),
		};

		const int datas[] =
		{
			Relation::NAME | (i << 8),
		};

		addSubFields(labels, texts, datas, sizeof(labels)/sizeof(char*), EDIT_RELATION_FLAGS);
	}
}

/**
 * This method is called when an edit box loses focus.
 * The virtual keyboard is hidden.
 * Only for irelation platform.
 * @param editBox The edit box object that generated the event.
 */
void EditRelation::editBoxEditingDidEnd(EditBox* editBox)
{
	int data = *(int*)(editBox->getData());
	wchar* text = strtowstr(editBox->getText().c_str());
	printf("Edit box did end %d.", data);

	Relation* relation = mOwner->getRelation(data >> 8);

	switch (data & 0xFF)
	{
		case Relation::NAME:
			relation->setName(text);
			break;
	}
}

/**
 * This method is called when the return button was pressed.
 * On irelation platform the virtual keyboard is not hidden after
 * receiving this event.
 * @param editBox The edit box object that generated the event.
 */
void EditRelation::editBoxReturn(EditBox* editBox)
{
	editBox->hideKeyboard();

	//fleu TODO remove this after didend is implemented
	int data = *(int*)(editBox->getData());
	wchar* text = strtowstr(editBox->getText().c_str());
	printf("Edit box did end %d %S.", data, text);

	Relation* relation = mOwner->getRelation(data >> 8);

	switch (data & 0xFF)
	{
		case Relation::NAME:
			relation->setName(text);
			break;
	}
}

/**
 * This method is called when the state of the check box was changed
 * by the user.
 * @param checkBox The check box object that generated the event.
 * @param state True if the check box is checked, false otherwise.
 */
void EditRelation::checkBoxStateChanged(CheckBox *checkBox, bool state)
{
	int data = *(int*)(checkBox->getData());
	Relation* relation = mOwner->getRelation(data);
	relation->setPrimary(state);
}

/**
 * This method is called if the touch-up event was inside the bounds of the button.
 * @param button The button object that generated the event.
 */
void EditRelation::buttonClicked(Widget* button)
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
			TypeDialog::getInstance()->setFeed(this, data, ContactsScreen::sRelationTypes,
					sizeof(ContactsScreen::sRelationTypes)/sizeof(char*),
					(int)mOwner->getRelation(data)->getType(),
					mOwner->getRelation(data)->getLabel());
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
void EditRelation::update(int index, int type, String label)
{
	mOwner->getRelation(index)->setType((Relation::eTypes)type);

	if (type == Relation::TYPE_CUSTOM)
	{
		mOwner->getRelation(index)->setLabel(strtowstr(label.c_str())); //fleu TODO label has and extra character at the end
	}

	mTypes[index]->setText(ContactsScreen::getRelationTypeString(
			mOwner->getRelation(index)->getType(), mOwner->getRelation(index)->getLabel()));
}

/**
 * Updates the relation.
 */
void EditRelation::update()
{
	mOwner->removeRelation(mCurrentSubField);
	clearBody();
	addBody();
	addChild(mBody);
}

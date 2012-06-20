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
 * @file EditNote.cpp
 * @author Florin Leu
 * @date 06 Jun 2012
 *
 * @brief Note Edit Layout.
 *
 **/

#include <util.h>

#include "EditNote.h"
#include "EditDefines.h"

#include "ConfirmDialog.h"

using namespace PIM;
using namespace NativeUI;

/**
 * Constructor.
 * @param contact The owner of this field.
 */
EditNote::EditNote(Contact* contact):
	EditField(contact)
{
	initData();
	createUI();

	mDialog = new ConfirmDialog(this);
}

/**
 * Destructor.
 */
EditNote::~EditNote()
{
	DELETE(mDialog);
	DELETE(mDeleteButton);
}

/**
 * Inits the data used to display this field.
 */
void EditNote::initData()
{
	mTitleText = strdup(TXT_EDIT_NOTE_TITLE);
	mDeleteButton = new Button*[mOwner->getNotesCount()];
}

/**
 * Creates the view.
 */
void EditNote::addBody()
{
	const char* labels[] =
	{
		"text"
	};

	EditField::addBody();

	for (int i=0; i<mOwner->getNotesCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d.", i + 1);
		addSubTitle(title, i);
		DELETE(title);

		Note* note = mOwner->getNote(i);

		const char* texts[] =
		{
			wstrtostr(note->getText())
		};

		const int datas[] =
		{
			Note::TEXT | (i << 8),
		};

		addSubFields(labels, texts, datas, sizeof(labels)/sizeof(char*), EDIT_NOTE_FLAGS);
	}
}

/**
 * This method is called when an edit box loses focus.
 * The virtual keyboard is hidden.
 * Only for iphone platform.
 * @param editBox The edit box object that generated the event.
 */
void EditNote::editBoxEditingDidEnd(EditBox* editBox)
{
	int data = *(int*)(editBox->getData());
	wchar* text = strtowstr(editBox->getText().c_str());
	printf("Edit box did end %d.", data);

	Note* note = mOwner->getNote(data >> 8);

	switch (data)
	{
		case Note::TEXT:
			note->setText(text);
			break;
	}
}

/**
 * This method is called when the return button was pressed.
 * On iphone platform the virtual keyboard is not hidden after
 * receiving this event.
 * @param editBox The edit box object that generated the event.
 */
void EditNote::editBoxReturn(EditBox* editBox)
{
	editBox->hideKeyboard();

	//fleu TODO remove this after didend is implemented
	int data = *(int*)(editBox->getData());
	wchar* text = strtowstr(editBox->getText().c_str());
	printf("Edit box did end %d.", data);

	Note* note = mOwner->getNote(data >> 8);

	switch (data)
	{
		case Note::TEXT:
			note->setText(text);
			break;
	}
}

/**
 * This method is called if the touch-up event was inside the bounds of the button.
 * @param button The button object that generated the event.
 */
void EditNote::buttonClicked(Widget* button)
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
	}
}

/**
 * Updates the note.
 */
void EditNote::update()
{
	mOwner->removeNote(mCurrentSubField);
	clearBody();
	addBody();
	addChild(mBody);
}

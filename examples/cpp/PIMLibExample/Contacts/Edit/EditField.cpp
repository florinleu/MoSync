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
 * @file EditField.cpp
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Field View Layout.
 *
 **/

#include <NativeUI/HorizontalLayout.h>
#include <NativeUI/Label.h>
#include <NativeUI/EditBox.h>
#include <NativeUI/CheckBox.h>

#include "EditField.h"
#include "EditDefines.h"

using namespace NativeUI;
using namespace PIM;
using namespace MAUtil;

/**
 * Constructor.
 * @param contact	The contact for which to display the field.
 */
EditField::EditField(Contact* contact):
	mOwner(contact),
	mOpened(false),
	mCurrentSubField(0)
{

}

/**
 * Destructor.
 */
EditField::~EditField()
{
	mTitle->removeButtonListener(this);
	removeChild(mBody);
	DELETE(mBody);

	DELETE(mTitleText);
}

/**
 * Ads subtitle for multivalue fields.
 * @param text		The subtitle text.
 * @param index		The index of the subfield
 */
void EditField::addSubTitle(const char* text, const int index)
{
	HorizontalLayout* layout = new HorizontalLayout();

	Label* titleBar = new Label();
	titleBar->fillSpaceHorizontally();
	titleBar->setBackgroundColor(EDIT_TITLE_COLOR);
	titleBar->setFontColor(EDIT_TITLE_TEXT_COLOR);
	titleBar->setFont(mTitleFont);
	titleBar->setText(text);
	titleBar->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	layout->addChild(titleBar);

	mDeleteButton[index] = new Button();
	mDeleteButton[index]->setText("Delete");
	mDeleteButton[index]->setData(createData(index));
	mDeleteButton[index]->addButtonListener(this);
	layout->addChild(mDeleteButton[index]);

	mBody->addChild(layout);
}

/**
 * Ads type for multivalue fields.
 * @param index		The index of the field.
 * @param text		The type text.
 * @param isPrimary
 */
void EditField::addType(int index, const char* text, const bool isPrimary)
{
	HorizontalLayout* layoutType = new HorizontalLayout();
	layoutType->wrapContentVertically();
	layoutType->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);

	Label* labelType = new Label();
	labelType->setWidth(EDIT_LABEL_WIDTH);
	labelType->setFont(mLabelFont);
	labelType->setText("type");
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
	mTypes.add(dataType);

	mBody->addChild(layoutType);

	HorizontalLayout* layoutPrimary = new HorizontalLayout();
	layoutPrimary->wrapContentVertically();
	layoutPrimary->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);

	Label* labelPrimary = new Label();
	labelPrimary->setWidth(EDIT_LABEL_WIDTH);
	labelPrimary->setFont(mLabelFont);
	labelPrimary->setText("primary");
	labelPrimary->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
	labelPrimary->setTextVerticalAlignment(MAW_ALIGNMENT_CENTER);
	layoutPrimary->addChild(labelPrimary);

	CheckBox* dataPrimary = new CheckBox();
	dataPrimary->setState(isPrimary);
	dataPrimary->addCheckBoxListener(this);
	dataPrimary->setData(createData(index));

	layoutPrimary->addChild(dataPrimary);

	mBody->addChild(layoutPrimary);
}

/**
 * Ads the fields to the body of the view.
 * @param parent	The main layout of the body.
 * @param labels	The labels for the fields.
 * @param datas		The datas for the fields.
 * @param size		The number of the fields.
 * @param flags		Flags that show if this is a read only subfield.
 */
void EditField::addSubFields(const char** labels, const char** texts, const int* datas, const int size, const int flags)
{
	for (int i=0; i<size; i++)
	{
		bool enabled = ((flags >> i) & 0x1);

		HorizontalLayout* layout = new HorizontalLayout();
		layout->wrapContentVertically();
		layout->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);

		Label* label = new Label();
		label->setWidth(EDIT_LABEL_WIDTH);
		label->fillSpaceVertically();
		label->setBackgroundColor(EDIT_LABEL_COLOR);
		label->setFont(mLabelFont);
		label->setText(labels[i]);
		label->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
		label->setTextVerticalAlignment(MAW_ALIGNMENT_CENTER);
		layout->addChild(label);

		EditBox* data = new EditBox();	//fleu TODO: set input type: url, email
		data->fillSpaceHorizontally();
		data->wrapContentVertically();
		//data->setFont(mDataFont);
		//data->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
		//data->setTextVerticalAlignment(MAW_ALIGNMENT_CENTER);
		data->setEnabled(enabled);
		layout->addChild(data);

		mBody->addChild(layout);

		//data->setData(const_cast<int*>(datas[i]));
		data->setData(createData(datas[i]));
		data->addEditBoxListener(this);

		if ( (texts[i] != NULL) && (strlen(texts[i]) > 0) )
		{
			data->setText(texts[i]);
		}
		else
		{
			data->setPlaceholder(labels[i]);
		}

		addSubFieldsSpacer();
	}
}

/**
 * Creates a button used to toggle the view.
 */
void EditField::addTitle()
{
	mTitle = new Button();
	mTitle->fillSpaceHorizontally();
	mTitle->wrapContentVertically();
	mTitle->setFont(mTitleFont);
	mTitle->setText(mTitleText);
	mTitle->addButtonListener(this);
	addChild(mTitle);
}

/**
 * Creates the view.
 */
void EditField::addBody()
{
	mBody = new VerticalLayout();
}

/**
 * Clears the view.
 */
void EditField::clearBody()
{
	removeChild(mBody);
	DELETE(mBody);
//	for (int i=mBody->countChildWidgets() - 1; i>=0; i--)
//	{
//		mBody->removeChild(mBody->getChild(i));
//	}
}

/**
 * Creates a small spacer and ads it to the view body.
 */
void EditField::addSubFieldsSpacer()
{
	VerticalLayout* spacer = new VerticalLayout();
	spacer->fillSpaceHorizontally();
	spacer->setHeight(1);
	spacer->setBackgroundColor(EDIT_SPACER_COLOR);
	mBody->addChild(spacer);
}

/**
 * Create the UI for field view.
 */
void EditField::createUI()
{
	fillSpaceHorizontally();
	wrapContentVertically();

	int fontTitleSize = SCREEN_WIDTH / 35;
	int fontDataSize = SCREEN_WIDTH / 40;

	mTitleFont = maFontLoadDefault(FONT_TYPE_SANS_SERIF, FONT_STYLE_BOLD, fontTitleSize);
	mLabelFont = maFontLoadDefault(FONT_TYPE_SANS_SERIF, FONT_STYLE_NORMAL, fontDataSize);
	mDataFont = maFontLoadDefault(FONT_TYPE_SANS_SERIF, FONT_STYLE_BOLD, fontDataSize);

	addTitle();

	addBody();
}

/**
 * Creates a void* from an int.
 * @param val  The int to use.
 */
void* EditField::createData(int val)
{
	int* data = new int[1];
	data[0] = val;
	return data;
}

/**
 * Updates the type and custom label for the field.
 * @param index The index of the subfield.
 * @param type The type to set.
 * @param label The label to set.
 */
void EditField::update(int index, int type, String label)
{

}

/**
 * This method is called if the touch-up event was inside the bounds of the button.
 * @param button The button object that generated the event.
 */
void EditField::buttonClicked(Widget* button)
{
	mOpened = !mOpened;
	if (mOpened)
	{
		addChild(mBody);
	}
	else
	{
		removeChild(mBody);
	}
}

/**
 * This method is called when an edit box loses focus.
 * The virtual keyboard is hidden.
 * Only for iphone platform.
 * @param editBox The edit box object that generated the event.
 */
void EditField::editBoxEditingDidEnd(EditBox* editBox)
{
	printf("EditField edit box editing did end");
}

/**
 * This method is called when the return button was pressed.
 * On iphone platform the virtual keyboard is not hidden after
 * receiving this event.
 * @param editBox The edit box object that generated the event.
 */
void EditField::editBoxReturn(EditBox* editBox)
{
	printf("EditField edit box return");
	editBox->hideKeyboard();
}

/**
 * This method is called when the state of the check box was changed
 * by the user.
 * @param checkBox The check box object that generated the event.
 * @param state True if the check box is checked, false otherwise.
 */
void EditField::checkBoxStateChanged(CheckBox *checkBox, bool state)
{
	printf("EditField check box changed");
}

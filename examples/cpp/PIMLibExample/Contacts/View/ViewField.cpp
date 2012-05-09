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
 * @file ViewField.cpp
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Field View Layout.
 *
 **/

#include <NativeUI/HorizontalLayout.h>
#include <NativeUI/Label.h>

//#include <util.h>

#include "ViewField.h"
#include "ViewDefines.h"

using namespace NativeUI;
using namespace PIM;

/**
 * Constructor.
 * @param contact	The contact for which to display the field.
 */
ViewField::ViewField(Contact* contact):
	mOwner(contact),
	mOpened(false)
{

}

/**
 * Destructor.
 */
ViewField::~ViewField()
{
	mTitle->removeButtonListener(this);
	removeChild(mBody);
	DELETE(mBody);

	DELETE(mTitleText);
}

/**
 * Ads subtitle for multivalue fields.
 * @param text
 * @param isPrimary
 */
void ViewField::addSubTitle(const char* text, const bool isPrimary)
{
	Label* titleBar = new Label();
	titleBar->fillSpaceHorizontally();
	titleBar->setBackgroundColor(isPrimary?VIEW_TITLE_SPECIAL_COLOR:VIEW_TITLE_COLOR);
	titleBar->setFontColor(VIEW_TITLE_TEXT_COLOR);
	titleBar->setFont(mTitleFont);
	titleBar->setText(text);
	titleBar->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	mBody->addChild(titleBar);
}

/**
 * Ads the fields to the body of the view.
 * @param parent	The main layout of the body.
 * @param labels	The labels for the fields.
 * @param datas		The datas for the fields.
 * @param size		The number of the fields.
 */
void ViewField::addSubFields(const char** labels, const char** datas, const int size)
{
	for (int i=0; i<size; i++)
	{
		//if we have no data for this field, skip it.
		if ( (datas[i] != NULL) && (strlen(datas[i]) > 0) )
		{
			HorizontalLayout* layout = new HorizontalLayout();
			layout->wrapContentVertically();
			layout->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);

			Label* label = new Label();
			label->setWidth(VIEW_LABEL_WIDTH);
			label->fillSpaceVertically();
			label->setBackgroundColor(VIEW_LABEL_COLOR);
			label->setFont(mLabelFont);
			label->setText(labels[i]);
			label->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
			label->setTextVerticalAlignment(MAW_ALIGNMENT_CENTER);
			layout->addChild(label);

			Label* data = new Label();
			data->fillSpaceHorizontally();
			data->fillSpaceVertically();
			data->setBackgroundColor(VIEW_DATA_COLOR);
			data->setFont(mDataFont);
			data->setText(datas[i]);
			data->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
			data->setTextVerticalAlignment(MAW_ALIGNMENT_CENTER);
			layout->addChild(data);

			mBody->addChild(layout);

			addSubFieldsSpacer();
		}
	}
}

/**
 * Creates a button used to toggle the view.
 */
void ViewField::addTitle()
{
	mTitle = new Button();
	mTitle->fillSpaceHorizontally();
	mTitle->wrapContentVertically();
	//mTitle->setHeight(50);
	mTitle->setFont(mTitleFont);
	mTitle->setText(mTitleText);
	mTitle->addButtonListener(this);
	addChild(mTitle);
}

/**
 * Creates the view.
 */
void ViewField::addBody()
{
	mBody = new VerticalLayout();
}

/**
 * Creates a small spacer and ads it to the view body.
 */
void ViewField::addSubFieldsSpacer()
{
	VerticalLayout* spacer = new VerticalLayout();
	spacer->fillSpaceHorizontally();
	spacer->setHeight(1);
	spacer->setBackgroundColor(VIEW_SPACER_COLOR);
	mBody->addChild(spacer);
}

/**
 * Create the UI for field view.
 */
void ViewField::createUI()
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
 * This method is called if the touch-up event was inside the bounds of the button.
 * @param button The button object that generated the event.
 */
void ViewField::buttonClicked(Widget* button)
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

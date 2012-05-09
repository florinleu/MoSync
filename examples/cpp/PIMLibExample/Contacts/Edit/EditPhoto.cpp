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
 * @file EditPhoto.cpp
 * @author Florin Leu
 * @date 06 Mar 2012
 *
 * @brief Photo Edit Layout.
 *
 **/

#include <NativeUI/VerticalLayout.h>

#include "EditPhoto.h"
#include "EditDefines.h"
#include "Utils.h"
#include "MAHeaders.h"

using namespace NativeUI;
using namespace PIM;

/**
 * Constructor.
 * @param contact The owner of this field.
 */
EditPhoto::EditPhoto(Contact* contact):
	mOwner(contact)
{
	createUI();
}

/**
 * Destructor.
 */
EditPhoto::~EditPhoto()
{
	mButton->removeButtonListener(this);
	mButton->removeButtonListener(this);
}

/**
 * Create the UI for photo edit.
 */
void EditPhoto::createUI()
{
	fillSpaceHorizontally();
	wrapContentVertically();

	MAHandle handle = mOwner->getPhoto()->getHandle();
	if ((mOwner->getPhoto() == NULL) || (handle < 0))
	{
		handle = RES_CONTACTS_PHOTO;
	}

	VerticalLayout* buttonLayout = new VerticalLayout();
	buttonLayout->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);
	buttonLayout->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	mButton = new ImageButton();
	setImage(handle);
	mButton->addButtonListener(this);
	buttonLayout->addChild(mButton);

	VerticalLayout* deleteButtonLayout = new VerticalLayout();
	deleteButtonLayout->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);
	deleteButtonLayout->wrapContentHorizontally();
	mDeleteButton = new Button();
	mDeleteButton->setText("Delete");
	mDeleteButton->addButtonListener(this);
	deleteButtonLayout->addChild(mDeleteButton);

	addChild(buttonLayout);
	addChild(deleteButtonLayout);
}

void EditPhoto::setImage(const MAHandle handle)
{
	MAExtent imgSize = maGetImageSize(handle);
	mButton->setWidth(EDIT_IMAGE_WIDTH);
	mButton->setHeight(EDIT_IMAGE_WIDTH * EXTENT_Y(imgSize)/EXTENT_X(imgSize));
	mButton->setBackgroundImage(handle);
}

/**
 * This method is called if the touch-up event was inside the
 * bounds of the button.
 * @param button The button object that generated the event.
 */
void EditPhoto::buttonClicked(Widget* button)
{
	if (button == mButton)
	{
		 maImagePickerOpen();
		 MAUtil::Environment::getEnvironment().addCustomEventListener(this);
	}
	else if (button == mDeleteButton)
	{
		mOwner->getPhoto()->setHandle(-1);
		mButton->setBackgroundImage(RES_CONTACTS_PHOTO);
	}
}

/**
 * Handle widget events.
 * @param event A MoSync event data structure.
 */
void EditPhoto::customEvent(const MAEvent& event)
{
	// Get the information sent by the widget.
	MAWidgetEventData* widgetEventData = (MAWidgetEventData*) event.data;

	if ( event.type == EVENT_TYPE_IMAGE_PICKER)
	{
		if ( event.imagePickerState == 1 )
		{
			// ready, get handle
			MAHandle img = event.imagePickerItem;
			if (img > 0)
			{
				mButton->setBackgroundImage(img);
				mOwner->getPhoto()->setHandle(img);
			}
		}
	}
	MAUtil::Environment::getEnvironment().removeCustomEventListener(this);
}

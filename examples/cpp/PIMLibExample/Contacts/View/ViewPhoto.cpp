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
 * @file ViewPhoto.cpp
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Photo View Layout.
 *
 **/

#include <NativeUI/Image.h>

#include "ViewPhoto.h"

#include "ViewDefines.h"
#include "MAHeaders.h"

using namespace NativeUI;
using namespace PIM;

/**
 * Constructor.
 */
ViewPhoto::ViewPhoto(Contact* contact):
	mOwner(contact)
{
	createUI();
}

/**
 * Destructor.
 */
ViewPhoto::~ViewPhoto()
{
}

/**
 * Create the UI for photo view.
 */
void ViewPhoto::createUI()
{
	fillSpaceHorizontally();
	wrapContentVertically();
	setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);

	MAHandle handle = mOwner->getPhoto()->getHandle();
	if ((mOwner->getPhoto() == NULL) || (handle < 0))
	{
		handle = RES_CONTACTS_PHOTO;
	}
	Image* photo = new Image();
	photo->setImage(handle);
	photo->setWidth(VIEW_IMAGE_WIDTH);
	photo->setBackgroundColor(0xFF0000);
	photo->setScaleMode(IMAGE_SCALE_PRESERVE_ASPECT);

	addChild(photo);
}

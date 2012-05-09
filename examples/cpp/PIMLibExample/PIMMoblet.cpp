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
 * @file PimMoblet.cpp
 * @author Florin Leu
 * @date 07 Feb 2012
 *
 * @brief Application moblet class.
 *
 **/

#include "PIMMoblet.h"
#include "ScreenContainer.h"
#include "MainScreen.h"

int PIMMoblet::sScreenWidth;
int PIMMoblet::sScreenHeight;

/**
 * Constructor.
 */
PIMMoblet::PIMMoblet()
{
	getScreenSize();

	// Create a NativeUI screen that will hold layout and widgets.
	mScreen = new MainScreen();

	ScreenContainer::getInstance()->push(mScreen);

	//Show the screen
	ScreenContainer::getInstance()->show();
}

/**
 * Destructor.
 */
PIMMoblet::~PIMMoblet()
{
	delete mScreen;
	mScreen = NULL;
}

void PIMMoblet::getScreenSize()
{
	/// Get screen dimensions.
	MAExtent size = maGetScrSize();

	/// Extract the screen width
	sScreenWidth = EXTENT_X(size);

	/// Extract the screen height
	sScreenHeight = EXTENT_Y(size);
}

/**
 * Called when a key is pressed.
 */
void PIMMoblet::keyPressEvent(int keyCode, int nativeCode)
{
	if (MAK_BACK == keyCode || MAK_0 == keyCode)
	{
		if (ScreenContainer::getInstance()->getStackSize() <= 1)
		{
			//Exit the moblet.
			//exit();
			close();
		}
	}
}

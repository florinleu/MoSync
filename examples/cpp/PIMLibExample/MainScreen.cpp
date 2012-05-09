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
 * @file MainScreen.cpp
 * @author Florin Leu
 * @date 07 Feb 2012
 *
 * @brief Screen Container.
 *
 **/

#include "MainScreen.h"
#include "PIMMoblet.h"
#include "ScreenContainer.h"

#include "MAHeaders.h"
#include "Utils.h"

using namespace NativeUI;

/*
 * Constructor
 */
MainScreen::MainScreen()
{
	createUI();
}

/*
 * Destructor
 */
MainScreen::~MainScreen()
{
	clean();
}

/*
 * Create the user interface for main screen.
 */
void MainScreen::createUI()
{
	mMainLayout = new VerticalLayout();

	createContacts(mMainLayout);
	createEvents(mMainLayout);

	addChild(mMainLayout);

	createLoading();
}

/*
 * Create the contacts button.
 */
void MainScreen::createContacts(Widget* parent)
{
	// Create the image button and make the app listen for events coming from widgets.
	mContactsButton = new ImageButton();
	mContactsButton->setBackgroundImage(RES_CONTACTS);
	mContactsButton->addButtonListener(this);

	// Create a layout to center the button.
	mContactsLayout = new VerticalLayout();
	mContactsLayout->setHeight(PIMMoblet::sScreenHeight >> 1);
	mContactsLayout->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	mContactsLayout->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);
	mContactsLayout->addChild(mContactsButton);

	parent->addChild(mContactsLayout);
}

/*
 * Create the events button.
 */
void MainScreen::createEvents(Widget* parent)
{
	// Create the image button and make the app listen for events coming from widgets.
	mEventsButton = new ImageButton();
	mEventsButton->setBackgroundImage(RES_EVENTS);
	mEventsButton->addButtonListener(this);

	// Create a layout to center the button.
	mEventsLayout = new VerticalLayout();
	mEventsLayout->setHeight(PIMMoblet::sScreenHeight >> 1);
	mEventsLayout->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	mEventsLayout->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);
	mEventsLayout->addChild(mEventsButton);

	parent->addChild(mEventsLayout);
}

/*
 * Create the loading indicator
 */
void MainScreen::createLoading()
{
	mLoadingLayout = new RelativeLayout();
	mLoadingLayout->setBackgroundColor(LOADING_COLOR);
	mLoadingLayout->setAlpha(LOADING_ALPHA);
	mLoadingLayout->fillSpaceHorizontally();
	mLoadingLayout->fillSpaceVertically();
	mLoadingLayout->setVisible(false);

	mLoading = new ActivityIndicator();
	mLoading->show();
	mLoadingLayout->addChild(mLoading);

	addChild(mLoadingLayout);
}

/*
 * Clean everything.
 */
void MainScreen::clean()
{
	delete mMainLayout;
	mMainLayout = NULL;
}

/**
 * This method is called if the touch-up event was inside the
 * bounds of the button.
 * @param button The button object that generated the event.
 */
void MainScreen::buttonClicked(Widget* button)
{
	mLoading->setPosition((SCREEN_WIDTH - mLoading->getWidth()) >> 1, (SCREEN_HEIGHT - mLoading->getHeight()) >> 1);
	mLoadingLayout->setVisible(true);
	if (button == mContactsButton)
	{
		mContactsScreen = new ContactsScreen();
		ScreenContainer::getInstance()->push(mContactsScreen);
	}
	else if (button == mEventsScreen)
	{
		mEventsScreen = new EventsScreen();
		//ScreenContainer::getInstance()->push(mEventsScreen);
	}
	mLoadingLayout->setVisible(false);
}

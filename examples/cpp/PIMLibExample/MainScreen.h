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
 * @file MainScreen.h
 * @author Florin Leu
 * @date 07 Feb 2012
 *
 * @brief Screen Container.
 *
 **/

#ifndef __MAINSCREEN_H__
#define __MAINSCREEN_H__

#include <NativeUI/Widget.h>
#include <NativeUI/VerticalLayout.h>
#include <NativeUI/ImageButton.h>
#include <NativeUI/ButtonListener.h>
#include <NativeUI/ActivityIndicator.h>
#include <NativeUI/RelativeLayout.h>

#include "Contacts/ContactsScreen.h"
#include "Events/EventsScreen.h"

class MainScreen : public NativeUI::Screen, public NativeUI::ButtonListener
{
	public:
		MainScreen();
		~MainScreen();

		void createUI();
		void createContacts(NativeUI::Widget* parent);
		void createEvents(NativeUI::Widget* parent);
		void createLoading();
		void clean();

		void buttonClicked(NativeUI::Widget* button);

	private:
		ContactsScreen* 	mContactsScreen;
		EventsScreen* 		mEventsScreen;

		//NativeUI Elements
		NativeUI::VerticalLayout* mMainLayout;

		NativeUI::VerticalLayout* mContactsLayout;
		NativeUI::VerticalLayout* mEventsLayout;

		NativeUI::ImageButton* mContactsButton;
		NativeUI::ImageButton* mEventsButton;

		NativeUI::RelativeLayout* mLoadingLayout;
		NativeUI::ActivityIndicator* mLoading;
};

#endif /* __MAINSCREEN_H__ */

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
 * @file ContactsScreen.h
 * @author Florin Leu
 * @date 08 Feb 2012
 *
 * @brief Contacts Screen.
 *
 **/

#ifndef __CONTACTSSCREEN_H__
#define __CONTACTSSCREEN_H__

#include <NativeUI/Screen.h>
#include <NativeUI/VerticalLayout.h>
#include <NativeUI/ListView.h>
#include <NativeUI/ListViewItem.h>
#include <NativeUI/ListViewListener.h>
#include <NativeUI/ActivityIndicator.h>
#include <NativeUI/RelativeLayout.h>
#include <NativeUI/StackScreen.h>
#include <NativeUI/StackScreenListener.h>

#include <Contacts/Contact.h>

class ContactViewScreen;
class ContactEditScreen;

class ContactsScreen :
	public NativeUI::Screen,
	public NativeUI::ListViewListener,
	public NativeUI::StackScreenListener
{
	public:
		ContactsScreen();
		~ContactsScreen();

		void createUI();
		void addNavigationBar();
		void createLoading();

		void listViewItemClicked(NativeUI::ListView* listView, NativeUI::ListViewItem* listViewItem);

		/**
		 * This method is called when a screen has been popped from a stack
		 * screen.
		 * @param stackScreen The stack screen object that generated the event.
		 * @param fromScreen The screen that was popped from the stack screen.
		 * @param toScreen The screen that will be shown.
		 */
		void stackScreenScreenPopped(NativeUI::StackScreen* stackScreen,
				NativeUI::Screen* fromScreen, NativeUI::Screen* toScreen);

		/**
		 * Gets the name of the address type.
		 * @param type	The address type.
		 * @return 		The type name.
		 */
		static const char* getAddressTypeString(PIM::Address::eTypes type, const wchar* label);

		/**
		 * Gets the name of the phone type.
		 * @param type	The phone type.
		 * @return 		The type name.
		 */
		static const char* getPhoneTypeString(PIM::Phone::eTypes type, const wchar* label);

		/**
		 * Gets the name of the email type.
		 * @param type	The email type.
		 * @return 		The type name.
		 */
		static const char* getEmailTypeString(PIM::Email::eTypes type, const wchar* label);

		/**
		 * Gets the name of the website type.
		 * @param type	The website type.
		 * @return 		The type name.
		 */
		static const char* getWebsiteTypeString(PIM::Website::eTypes type, const wchar* label);

	public:
		static const char* sAddressTypes[PIM::Address::CUSTOM + 1];
		static const char* sPhoneTypes[PIM::Phone::CUSTOM + 1];
		static const char* sEmailTypes[PIM::Email::CUSTOM + 1];
		static const char* sWebsiteTypes[PIM::Website::CUSTOM + 1];

	private:
		NativeUI::VerticalLayout* mLayout;
		NativeUI::ListView* mListView;
		NativeUI::ListViewItem* mListViewItem;

		NativeUI::RelativeLayout* mLoadingLayout;
		NativeUI::ActivityIndicator* mLoading;

		ContactViewScreen* mViewScreen;
		ContactEditScreen* mEditScreen;
};

#endif /* __CONTACTSSCREEN_H__ */

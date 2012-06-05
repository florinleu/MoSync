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
 * @file ContactEditScreen.h
 * @author Florin Leu
 * @date 16 Feb 2012
 *
 * @brief Contact View Screen.
 *
 **/

#ifndef __CONTACTEDITSCREEN_H__
#define __CONTACTEDITSCREEN_H__

#include <NativeUI/Screen.h>
#include <NativeUI/StackScreen.h>
#include <NativeUI/VerticalLayout.h>
#include <NativeUI/Button.h>
#include <NativeUI/ListView.h>
#include <NativeUI/ListViewItem.h>
#include <Contacts/Contact.h>

class ContactEditScreen : public NativeUI::Screen
{
	public:
		ContactEditScreen();
		ContactEditScreen(wchar* id);
		~ContactEditScreen();

		void createUI();
		void addNavigationBar();
		bool addField(const char* title, const char** labels, const char** datas, const int size, const bool primary = false);
		void addPhoto();
		void addID();
		void addName();
		void addAddress();
		void addPhone();
		void addEmail();
		void addWebsite();
		void addInstantMessaging();
		const char* getInstantMessagingProtocolString(PIM::InstantMessaging::eProtocols protocol);
		void addNote();
		void addOrganization();
		const char* getOrganizationTypeString(PIM::eOrganizationTypes type);
		void addSocialProfile();
		const char* getSocialProfileServiceString(PIM::eSocialProfileServices service);
		const char* getSocialProfileTypeString(PIM::eSocialProfileTypes type);
		void addEvent();
		const char* getEventTypeString(PIM::eEventTypes type);
		void addRelation();
		const char* getRelationTypeString(PIM::eRelationTypes type);
		void addDeleteButton();
		void addSpacer();

		void writeData();

	private:
		PIM::Contact* mContact;
		NativeUI::VerticalLayout* mLayout;
		NativeUI::Button* mDeleteButton;
};

#endif /* __CONTACTEDITSCREEN_H__ */

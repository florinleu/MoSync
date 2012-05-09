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
 * @file ContactViewScreen.h
 * @author Florin Leu
 * @date 16 Feb 2012
 *
 * @brief Contact View Screen.
 *
 **/

#ifndef __CONTACTVIEWSCREEN_H__
#define __CONTACTVIEWSCREEN_H__

#include <NativeUI/Screen.h>
#include <NativeUI/VerticalLayout.h>
#include <Contacts/Contact.h>

class ContactViewScreen : public NativeUI::Screen
{
	public:
		ContactViewScreen();
		ContactViewScreen(wchar* id);
		~ContactViewScreen();

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
		void addNote();
		void addOrganization();
		void addSocialProfile();
		void addEvent();
		void addRelation();
		void addSpacer();

	private:
		PIM::Contact* mContact;
		NativeUI::VerticalLayout* mLayout;
};

#endif /* __CONTACTVIEWSCREEN_H__ */

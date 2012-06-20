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
 * @file ContactEditScreen.cpp
 * @author Florin Leu
 * @date 16 Feb 2012
 *
 * @brief Contact View Screen.
 *
 **/

#include <NativeUI/HorizontalLayout.h>
#include <NativeUI/Label.h>
#include <NativeUI/EditBox.h>
//#include <NativeUI/Image.h>
#include <NativeUI/NavigationBar.h>
#include <Contacts/Contact.h>
#include <util.h>
#include <pim.h>
#include <mawstring.h>

#include "ContactEditScreen.h"
#include "ContactsScreen.h"
#include "PIMMoblet.h"
#include "Utils.h"
#include "MAHeaders.h"

#include "EditPhoto.h"
#include "EditID.h"
#include "EditName.h"
#include "EditAddress.h"
#include "EditPhone.h"
#include "EditEmail.h"
#include "EditWebsite.h"
#include "EditInstantMessaging.h"
#include "EditNote.h"
#include "EditOrganization.h"
#include "EditSocialProfile.h"
#include "EditEvent.h"
#include "EditRelation.h"
#include "EditDelete.h"
#include "EditDefines.h"

using namespace NativeUI;
using namespace PIM;

ContactEditScreen::ContactEditScreen(wchar* id)
{
	mContact = new Contact();
	mContact->setID(id);
	mContact->find();
	createUI();
}

ContactEditScreen::~ContactEditScreen()
{
	delete mContact;
	mContact = NULL;
}

void ContactEditScreen::createUI()
{
	mLayout = new VerticalLayout();
	mLayout->fillSpaceHorizontally();
	mLayout->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	mLayout->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);

	addNavigationBar();

	addPhoto();

	addID();

	addName();

	addAddress();

	addPhone();

	addEmail();

	addWebsite();

	addInstantMessaging();

	addNote();

	addOrganization();

	addSocialProfile();

	addEvent();

	addRelation();

	addDeleteButton();

	mLayout->setScrollable(true);

	addChild(mLayout);
}

void ContactEditScreen::addNavigationBar()
{
	NavigationBar* navigationBar = new NavigationBar();
	navigationBar->setTitle("Details");
	mLayout->addChild(navigationBar);

	addSpacer();
}

void ContactEditScreen::addPhoto()
{
	EditPhoto* photo = new EditPhoto(mContact);

	mLayout->addChild(photo);

	addSpacer();
}

void ContactEditScreen::addID()
{
	EditID* id = new EditID(mContact);

	mLayout->addChild(id);

	addSpacer();
}

void ContactEditScreen::addName()
{
	EditName* name = new EditName(mContact);

	mLayout->addChild(name);

	addSpacer();
}

void ContactEditScreen::addAddress()
{
	EditAddress* address = new EditAddress(mContact);

	mLayout->addChild(address);

	addSpacer();
}

void ContactEditScreen::addPhone()
{
	EditPhone* phone = new EditPhone(mContact);

	mLayout->addChild(phone);

	addSpacer();
}

void ContactEditScreen::addEmail()
{
	EditEmail* email = new EditEmail(mContact);

	mLayout->addChild(email);

	addSpacer();
}

void ContactEditScreen::addWebsite()
{
	EditWebsite* website = new EditWebsite(mContact);

	mLayout->addChild(website);

	addSpacer();
}

void ContactEditScreen::addInstantMessaging()
{
	EditInstantMessaging* instantMessaging = new EditInstantMessaging(mContact);

	mLayout->addChild(instantMessaging);

	addSpacer();
}

void ContactEditScreen::addNote()
{
	EditNote* note = new EditNote(mContact);

	mLayout->addChild(note);

	addSpacer();
}

void ContactEditScreen::addOrganization()
{
	EditOrganization* organization = new EditOrganization(mContact);

	mLayout->addChild(organization);

	addSpacer();
}

void ContactEditScreen::addSocialProfile()
{
	EditSocialProfile* socialProfile = new EditSocialProfile(mContact);

	mLayout->addChild(socialProfile);

	addSpacer();
}

void ContactEditScreen::addEvent()
{
	EditEvent* event = new EditEvent(mContact);

	mLayout->addChild(event);

	addSpacer();
}

void ContactEditScreen::addRelation()
{
	EditRelation* relation = new EditRelation(mContact);

	mLayout->addChild(relation);

	addSpacer();
}

void ContactEditScreen::addDeleteButton()
{
	EditDelete* button = new EditDelete(mContact);

	mLayout->addChild(button);

	addSpacer();
}

void ContactEditScreen::addSpacer()
{
	Label* spacer = new Label();
	spacer->fillSpaceHorizontally();
	mLayout->addChild(spacer);
}

void ContactEditScreen::writeData()
{
	mContact->write();
	delete mContact;
	mContact = NULL;
}

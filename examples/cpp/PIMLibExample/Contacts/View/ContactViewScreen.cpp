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
 * @file ContactViewScreen.cpp
 * @author Florin Leu
 * @date 16 Feb 2012
 *
 * @brief Contact View Screen.
 *
 **/

#include <NativeUI/Label.h>
#include <NativeUI/NavigationBar.h>

#include "ContactViewScreen.h"

#include "ViewPhoto.h"
#include "ViewID.h"
#include "ViewName.h"
#include "ViewAddress.h"
#include "ViewPhone.h"
#include "ViewEmail.h"
#include "ViewWebsite.h"
#include "ViewInstantMessaging.h"
#include "ViewNote.h"
#include "ViewOrganization.h"
#include "ViewSocialProfile.h"
#include "ViewEvent.h"
#include "ViewRelation.h"

using namespace NativeUI;
using namespace PIM;

ContactViewScreen::ContactViewScreen(wchar* id)
{
	mContact = new Contact();
	mContact->setID(id);
	mContact->find();

	createUI();
}

ContactViewScreen::~ContactViewScreen()
{
	delete mContact;
	mContact = NULL;
}

void ContactViewScreen::createUI()
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

	mLayout->setScrollable(true);

	addChild(mLayout);
}

void ContactViewScreen::addNavigationBar()
{
	NavigationBar* navigationBar = new NavigationBar();
	navigationBar->setTitle("Details");
	mLayout->addChild(navigationBar);

	addSpacer();
}

/*
 * Ads the photo on the view.
 */
void ContactViewScreen::addPhoto()
{
	ViewPhoto* photo = new ViewPhoto(mContact);

	mLayout->addChild(photo);

	addSpacer();
}

/*
 * Ads the ID on the view.
 */
void ContactViewScreen::addID()
{
	ViewID* id = new ViewID(mContact);

	mLayout->addChild(id);

	addSpacer();
}

void ContactViewScreen::addName()
{
	ViewName* name = new ViewName(mContact);

	mLayout->addChild(name);

	addSpacer();
}

void ContactViewScreen::addAddress()
{
	ViewAddress* address = new ViewAddress(mContact);

	mLayout->addChild(address);

	//if (mContact->getAddressesCount() > 0)
	addSpacer();
}

void ContactViewScreen::addPhone()
{
	ViewPhone* phone = new ViewPhone(mContact);

	mLayout->addChild(phone);

	addSpacer();
}

void ContactViewScreen::addEmail()
{
	ViewEmail* email = new ViewEmail(mContact);

	mLayout->addChild(email);

	addSpacer();
}

void ContactViewScreen::addWebsite()
{
	ViewWebsite* website = new ViewWebsite(mContact);

	mLayout->addChild(website);

	addSpacer();
}

void ContactViewScreen::addInstantMessaging()
{
	ViewInstantMessaging* instantMessaging = new ViewInstantMessaging(mContact);

	mLayout->addChild(instantMessaging);

	addSpacer();
}

void ContactViewScreen::addNote()
{
	ViewNote* note = new ViewNote(mContact);

	mLayout->addChild(note);

	addSpacer();
}

void ContactViewScreen::addOrganization()
{
	ViewOrganization* organization = new ViewOrganization(mContact);

	mLayout->addChild(organization);

	addSpacer();
}

void ContactViewScreen::addSocialProfile()
{
	ViewSocialProfile* socialProfile = new ViewSocialProfile(mContact);

	mLayout->addChild(socialProfile);

	addSpacer();
}

void ContactViewScreen::addEvent()
{
	ViewEvent* event = new ViewEvent(mContact);

	mLayout->addChild(event);

	addSpacer();
}

void ContactViewScreen::addRelation()
{
	ViewRelation* relation = new ViewRelation(mContact);

	mLayout->addChild(relation);

	addSpacer();
}

void ContactViewScreen::addSpacer()
{
	Label* spacer = new Label();
	spacer->fillSpaceHorizontally();
	mLayout->addChild(spacer);
}

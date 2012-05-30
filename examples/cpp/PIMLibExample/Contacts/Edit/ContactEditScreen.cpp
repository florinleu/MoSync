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

//	addInstantMessaging();
//
//	addNote();
//
//	addOrganization();
//
//	addSocialProfile();
//
//	addEvent();
//
//	addRelation();

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

bool ContactEditScreen::addField(const char* title, const char** labels, const char** datas, const int size, const bool primary)
{
	bool display = false;
	for (int i=0; i<size; i++)
	{
		if ( (datas[i] != NULL) && (strlen(datas[i]) > 0) )
		{
			display = true;
		}
	}

	if (!display)
	{
		return false;
	}

	Label* titleBar = new Label();
	titleBar->fillSpaceHorizontally();
	//titleBar->setBackgroundColor(primary?EDIT_TITLE_SPECIAL_COLOR:EDIT_TITLE_COLOR);
	titleBar->setFontColor(EDIT_TITLE_TEXT_COLOR);
	titleBar->setText(title);
	titleBar->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	mLayout->addChild(titleBar);
	for (int i=0; i<size; i++)
	{
		if ( (datas[i] != NULL) && (strlen(datas[i]) > 0) )
		{
			HorizontalLayout* layout = new HorizontalLayout();
			layout->wrapContentVertically();
			layout->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);

			Label* label = new Label();
			label->setWidth(EDIT_LABEL_WIDTH);
			label->setBackgroundColor(EDIT_LABEL_COLOR);
			label->setText(labels[i]);
			label->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
			layout->addChild(label);

			EditBox* data = new EditBox();
			data->fillSpaceHorizontally();
			data->setText(datas[i]);
			data->setEnabled(false);
			layout->addChild(data);

			mLayout->addChild(layout);
		}
	}

	return true;
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
//	for (int i=0; i<mContact->getWebsitesCount(); i++)
//	{
//		char* title = new char[BUFF_SIZE];
//		sprintf(title, "%d. %s", i + 1, getWebsiteTypeString(mContact->getWebsite(i)->getType()));
//		if (mContact->getWebsite(i)->getType() == WEBSITE_CUSTOM)
//		{
//			sprintf(title, "%s (%S)", title, mContact->getWebsite(i)->getLabel());
//		}
//		const char* datas[] =
//		{
//			wstrtostr(mContact->getWebsite(i)->getURL())
//		};
//
//		addField(title, labels, datas, sizeof(labels)/sizeof(char*), mContact->getWebsite(i)->isPrimary());
//
//		DELETE(title);
//	}
//
//	if (mContact->getWebsitesCount() > 0)
//	{
//		addSpacer();
//	}
//}
//
//const char* ContactEditScreen::getWebsiteTypeString(PIM::eWebsiteTypes type)
//{
//	const char* websiteType[] =
//	{
//		"Homepage",
//		"Blog",
//		"Profile",
//		"Home",
//		"Work",
//		"FTP",
//		"Other",
//		"Custom"
//	};
//
//	return websiteType[type];
//}

void ContactEditScreen::addInstantMessaging()
{
	const char* labels[] =
	{
		"username",
		"protocol"
	};

	for (int i=0; i<mContact->getInstantMessagingsCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d. %s", i + 1, getInstantMessagingTypeString(mContact->getInstantMessaging(i)->getType()));
		if (mContact->getInstantMessaging(i)->getType() == INSTANTMESSAGING_CUSTOM)
		{
			sprintf(title, "%s (%S)", title, mContact->getInstantMessaging(i)->getLabel());
		}

		char* protocol = new char[BUFF_SIZE];
		sprintf(protocol, "%s", getInstantMessagingProtocolString(mContact->getInstantMessaging(i)->getProtocol()));

		if (mContact->getInstantMessaging(i)->getProtocol() == PROTOCOL_CUSTOM)
		{
			sprintf(protocol, "%s (%S)", protocol, mContact->getInstantMessaging(i)->getProtocolLabel());
		}

		const char* datas[] =
		{
			wstrtostr(mContact->getInstantMessaging(i)->getUsername()),
			protocol
		};

		addField(title, labels, datas, sizeof(labels)/sizeof(char*), mContact->getInstantMessaging(i)->isPrimary());

		DELETE(title);
		DELETE(protocol);
	}

	if (mContact->getInstantMessagingsCount() > 0)
	{
		addSpacer();
	}
}

const char* ContactEditScreen::getInstantMessagingProtocolString(PIM::eInstantMessagingProtocols protocol)
{
	const char* instantMessagingProtocol[] =
	{
		"AIM",
		"MSN",
		"Yahoo",
		"Skype",
		"QQ",
		"GoogleTalk",
		"ICQ",
		"Jabber",
		"Netmeeting",
		"Custom"
	};

	return instantMessagingProtocol[protocol];
}

const char* ContactEditScreen::getInstantMessagingTypeString(PIM::eInstantMessagingTypes type)
{
	const char* instantMessagingType[] =
	{
		"Home",
		"Work",
		"Other",
		"Custom"
	};

	return instantMessagingType[type];
}

void ContactEditScreen::addNote()
{
	const char* title = "Note";

	const char* labels[] =
	{
		"text"
	};

	const char* datas[] =
	{
		wstrtostr(mContact->getNote()->getText()),
	};

	if (addField(title, labels, datas, sizeof(labels)/sizeof(char*)))
	{
		addSpacer();
	}
}

void ContactEditScreen::addOrganization()
{
	const char* labels[] =
	{
		"name",
		"title",
		"department",
		"location",
		"job description",
		"phonetic name",
		"symbol"
	};

	for (int i=0; i<mContact->getOrganizationsCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d. %s", i + 1, getOrganizationTypeString(mContact->getOrganization(i)->getType()));
		if (mContact->getOrganization(i)->getType() == ORGANIZATION_CUSTOM)
		{
			sprintf(title, "%s (%S)", title, mContact->getOrganization(i)->getLabel());
		}
		const char* datas[] =
		{
			wstrtostr(mContact->getOrganization(i)->getName()),
			wstrtostr(mContact->getOrganization(i)->getTitle()),
			wstrtostr(mContact->getOrganization(i)->getDepartment()),
			wstrtostr(mContact->getOrganization(i)->getLocation()),
			wstrtostr(mContact->getOrganization(i)->getJobDescription()),
			wstrtostr(mContact->getOrganization(i)->getPhoneticName()),
			wstrtostr(mContact->getOrganization(i)->getSymbol())
		};

		addField(title, labels, datas, sizeof(labels)/sizeof(char*), mContact->getOrganization(i)->isPrimary());

		DELETE(title);
	}

	if (mContact->getOrganizationsCount())
	{
		addSpacer();
	}
}

const char* ContactEditScreen::getOrganizationTypeString(PIM::eOrganizationTypes type)
{
	const char* organizationType[] =
	{
		"Work",
		"Other",
		"Custom"
	};

	return organizationType[type];
}

void ContactEditScreen::addSocialProfile()
{
	const char* labels[] =
	{
		"url",
		"username",
		"user identifier",
		"service"
	};

	for (int i=0; i<mContact->getSocialProfilesCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d. %s", i + 1, getSocialProfileTypeString(mContact->getSocialProfile(i)->getType()));
		if (mContact->getSocialProfile(i)->getType() == SOCIALPROFILE_CUSTOM)
		{
			sprintf(title, "%s (%S)", title, mContact->getSocialProfile(i)->getLabel());
		}

		char* service = new char[BUFF_SIZE];
		sprintf(service, "%s", getSocialProfileServiceString(mContact->getSocialProfile(i)->getService()));

		if (mContact->getSocialProfile(i)->getService() == SERVICE_CUSTOM)
		{
			sprintf(service, "%s (%S)", service, mContact->getSocialProfile(i)->getServiceLabel());
		}

		const char* datas[] =
		{
			wstrtostr(mContact->getSocialProfile(i)->getURL()),
			wstrtostr(mContact->getSocialProfile(i)->getUsername()),
			wstrtostr(mContact->getSocialProfile(i)->getUserIdentifier()),
			service
		};

		addField(title, labels, datas, sizeof(labels)/sizeof(char*), mContact->getSocialProfile(i)->isPrimary());

		DELETE(title);
	}

	if (mContact->getSocialProfilesCount())
	{
		addSpacer();
	}
}

const char* ContactEditScreen::getSocialProfileServiceString(PIM::eSocialProfileServices service)
{
	const char* socialProfileService[] =
	{
		"Twitter",
		"GameCenter",
		"Facebook",
		"MySpace",
		"LinkedIn",
		"Flickr",
		"Custom"
	};

	return socialProfileService[service];
}

const char* ContactEditScreen::getSocialProfileTypeString(PIM::eSocialProfileTypes type)
{
	const char* socialProfileType[] =
	{
		"Home",
		"Work",
		"Other",
		"Custom"
	};

	return socialProfileType[type];
}

void ContactEditScreen::addEvent()
{
	const char* labels[] =
	{
		"date",
	};

	for (int i=0; i<mContact->getEventsCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d. %s", i + 1, getEventTypeString(mContact->getEvent(i)->getType()));
		if (mContact->getEvent(i)->getType() == EVENT_CUSTOM)
		{
			sprintf(title, "%s (%S)", title, mContact->getEvent(i)->getLabel());
		}

		const char* datas[] =
		{
			sprint_time(mContact->getEvent(i)->getDate())
		};

		addField(title, labels, datas, sizeof(labels)/sizeof(char*), mContact->getEvent(i)->isPrimary());

		DELETE(title);
	}

	if (mContact->getEventsCount() > 0)
	{
		addSpacer();
	}
}

const char* ContactEditScreen::getEventTypeString(PIM::eEventTypes type)
{
	const char* eventType[] =
	{
		"Birthday",
		"Anniversary",
		"Other",
		"Custom"
	};

	return eventType[type];
}

void ContactEditScreen::addRelation()
{
	const char* labels[] =
	{
		"name",
	};

	for (int i=0; i<mContact->getRelationsCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d. %s", i + 1, getRelationTypeString(mContact->getRelation(i)->getType()));
		if (mContact->getRelation(i)->getType() == RELATION_CUSTOM)
		{
			sprintf(title, "%s (%S)", title, mContact->getRelation(i)->getLabel());
		}

		const char* datas[] =
		{
			wstrtostr(mContact->getRelation(i)->getName()),
		};

		addField(title, labels, datas, sizeof(labels)/sizeof(char*), mContact->getRelation(i)->isPrimary());

		DELETE(title);
	}

	if (mContact->getRelationsCount() > 0)
	{
		addSpacer();
	}
}

const char* ContactEditScreen::getRelationTypeString(PIM::eRelationTypes type)
{
	const char* relationType[] =
	{
		"Mother",
		"Father",
		"Parent",
		"Sister",
		"Brother",
		"Child",
		"Friend",
		"Spouse",
		"Partner",
		"Manager",
		"Assistant",
		"Domestic partner",
		"Referred by",
		"Relative",
		"Custom"
	};

	return relationType[type];
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
}

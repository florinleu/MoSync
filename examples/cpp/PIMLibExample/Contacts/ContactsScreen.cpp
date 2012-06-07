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
 * @file ContactsScreen.cpp
 * @author Florin Leu
 * @date 08 Feb 2012
 *
 * @brief Contacts Screen.
 *
 **/

#include <wchar.h>
#include <mawstring.h>
#include <Contacts/Contact.h>
#include <NativeUI/NavigationBar.h>
#include <pim.h>
#include <util.h>

#include "ContactsScreen.h"
#include "ScreenContainer.h"
#include "ContactViewScreen.h"
#include "ContactEditScreen.h"
#include "Utils.h"

using namespace NativeUI;
using namespace PIM;

ContactsScreen::ContactsScreen()
{
	createUI();
}

ContactsScreen::~ContactsScreen()
{
	mListView->removeListViewListener(this);
	closeContacts();
}

void ContactsScreen::createUI()
{
	initContacts();
	Contact* contact = new Contact();

	mListView = new ListView();
	do
	{
		contact->readNext(RF_NAME);

		if (contact->getID() == NULL)
		{
			continue;
		}

		ListViewItem* listViewItem = new ListViewItem();
		if (contact->getName() != NULL)
		{
			char* displayName = wstrtostr(contact->getName()->getDisplayName());

			if ((displayName == NULL) || (strlen(displayName) == 0))
			{
				displayName = TXT_NO_NAME;
			}
			listViewItem->setText(displayName);
		}
		listViewItem->setData(wcsdup(contact->getID()));

		mListView->addChild(listViewItem);
		mListView->addListViewListener(this);
	} while (contact->getID() != NULL);

	mLayout = new VerticalLayout();

	addNavigationBar();

	mLayout->addChild(mListView);

	addChild(mLayout);
	closeContacts(); //fleu TODO remove this?

	createLoading();

	ScreenContainer::getInstance()->addStackScreenListener(this);
}

void ContactsScreen::addNavigationBar()
{
	NavigationBar* navigationBar = new NavigationBar();
	navigationBar->setTitle("Contacts");
	mLayout->addChild(navigationBar);
}

/*
 * Create the loading indicator
 */
void ContactsScreen::createLoading()
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

void ContactsScreen::listViewItemClicked(ListView* listView, ListViewItem* listViewItem)
{
	mLoading->setPosition((SCREEN_WIDTH - mLoading->getWidth()) >> 1, (SCREEN_HEIGHT - mLoading->getHeight()) >> 1);
	mLoadingLayout->setVisible(true);
	initContacts();
//	mViewScreen = new ContactViewScreen((wchar*)listViewItem->getData());
//	ScreenContainer::getInstance()->push(mViewScreen);
	mEditScreen = new ContactEditScreen((wchar*)listViewItem->getData());
	ScreenContainer::getInstance()->push(mEditScreen);
	mLoadingLayout->setVisible(false);
}

/**
 * This method is called when a screen has been popped from a stack
 * screen.
 * @param stackScreen The stack screen object that generated the event.
 * @param fromScreen The screen that was popped from the stack screen.
 * @param toScreen The screen that will be shown.
 */
void ContactsScreen::stackScreenScreenPopped(StackScreen* stackScreen, Screen* fromScreen, Screen* toScreen)
{
	if (fromScreen == mEditScreen)
	{
		mEditScreen->writeData();
	}
	if (toScreen == this)
	{
		//reload();
	}
}

/**
 * Available address types.
 */
const char* ContactsScreen::sAddressTypes[Address::TYPE_CUSTOM + 1] =
{
	"Home",
	"Work",
	"Other",
	"Custom"
};

/**
 * Gets the name of the address type.
 * @param type	The address type.
 * @return 		The type name.
 */
const char* ContactsScreen::getAddressTypeString(Address::eTypes type, const wchar* label)
{
	if (type == Address::TYPE_CUSTOM)
	{
		return wstrtostr(label);
	}

	return sAddressTypes[type];
}

/**
 * Available phone types.
 */
const char* ContactsScreen::sPhoneTypes[Phone::TYPE_CUSTOM + 1] =
{
	"Home",
	"Mobile",
	"Home fax",
	"Work fax",
	"Pager",
	"iPhone",
	"Work",
	"Callback",
	"Car",
	"Company main",
	"ISDN",
	"Other fax",
	"Radio",
	"Telex",
	"TTY TDD",
	"Work mobile",
	"Work pager",
	"Assistant",
	"MMS",
	"Other",
	"Custom"
};

/**
 * Gets the name of the phone type.
 * @param type	The phone type.
 * @return 		The type name.
 */
const char* ContactsScreen::getPhoneTypeString(Phone::eTypes type, const wchar* label)
{
	printf("getPhoneTypeString %d %S", type, label);
	if (type == Phone::TYPE_CUSTOM)
	{
		printf("return label");
		return wstrtostr(label);
	}
	return sPhoneTypes[type];
}

/**
 * Available e-mail types.
 */
const char* ContactsScreen::sEmailTypes[Email::TYPE_CUSTOM + 1] =
{
	"Home",
	"Work",
	"Mobile",
	"Other",
	"Custom"
};

/**
 * Gets the name of the email type.
 * @param type	The email type.
 * @return 		The type name.
 */
const char* ContactsScreen::getEmailTypeString(Email::eTypes type, const wchar* label)
{
	if (type == Email::TYPE_CUSTOM)
	{
		return wstrtostr(label);
	}

	return sEmailTypes[type];
}

/**
 * Available website types.
 */
const char* ContactsScreen::sWebsiteTypes[Website::TYPE_CUSTOM + 1] =
{
	"Homepage",
	"Blog",
	"Profile",
	"Home",
	"Work",
	"FTP",
	"Other",
	"Custom"
};

/**
 * Gets the name of the website type.
 * @param type	The website type.
 * @return 		The type name.
 */
const char* ContactsScreen::getWebsiteTypeString(Website::eTypes type, const wchar* label)
{
	if (type == Website::TYPE_CUSTOM)
	{
		return wstrtostr(label);
	}

	return sWebsiteTypes[type];
}

/**
 * Available IM protocols.
 */
const char* ContactsScreen::sIMProtocols[10] =
{
	MA_PIM_CONTACT_IM_PROTOCOL_AIM,
	MA_PIM_CONTACT_IM_PROTOCOL_MSN,
	MA_PIM_CONTACT_IM_PROTOCOL_YAHOO,
	MA_PIM_CONTACT_IM_PROTOCOL_SKYPE,
	MA_PIM_CONTACT_IM_PROTOCOL_QQ,
	MA_PIM_CONTACT_IM_PROTOCOL_GOOGLE_TALK,
	MA_PIM_CONTACT_IM_PROTOCOL_ICQ,
	MA_PIM_CONTACT_IM_PROTOCOL_JABBER,
	MA_PIM_CONTACT_IM_PROTOCOL_NETMEETING,
	MA_PIM_CONTACT_IM_PROTOCOL_CUSTOM
};

/**
 * Gets the name of the IM protocol.
 * @param protocol	The IM protocol.
 * @return 		The protocol name.
 */
const char* ContactsScreen::getIMProtocolString(InstantMessaging::eProtocols protocol, const wchar* label)
{
	if (protocol == InstantMessaging::PROTOCOL_CUSTOM)
	{
		return wstrtostr(label);
	}

	return sIMProtocols[protocol];
}

/**
 * Available IM types.
 */
const char* ContactsScreen::sIMTypes[InstantMessaging::TYPE_CUSTOM + 1] =
{
	"Home",
	"Work",
	"Other",
	"Custom"
};

/**
 * Gets the name of the IM type.
 * @param type	The IM type.
 * @return 		The type name.
 */
const char* ContactsScreen::getIMTypeString(InstantMessaging::eTypes type, const wchar* label)
{
	if (type == InstantMessaging::TYPE_CUSTOM)
	{
		return wstrtostr(label);
	}

	return sIMTypes[type];
}

/**
 * Available organization types.
 */
const char* ContactsScreen::sOrganizationTypes[Organization::TYPE_CUSTOM + 1] =
{
	"Work",
	"Other",
	"Custom"
};

/**
 * Gets the name of the organization type.
 * @param type	The organization type.
 * @return 		The type name.
 */
const char* ContactsScreen::getOrganizationTypeString(Organization::eTypes type, const wchar* label)
{
	if (type == Organization::TYPE_CUSTOM)
	{
		return wstrtostr(label);
	}

	return sOrganizationTypes[type];
}

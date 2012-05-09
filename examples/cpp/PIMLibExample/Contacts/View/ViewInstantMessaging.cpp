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
 * @file ViewInstantMessaging.cpp
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Instant messaging view Layout.
 *
 **/

#include <util.h>

#include "ViewInstantMessaging.h"
#include "ViewDefines.h"

using namespace PIM;
using namespace NativeUI;

/**
 * Constructor.
 * @param contact	The contact for which to display the field.
 */
ViewInstantMessaging::ViewInstantMessaging(Contact* contact):
		ViewField(contact)
{
	initData();
	createUI();
}

/**
 * Destructor.
 */
ViewInstantMessaging::~ViewInstantMessaging()
{
}

/**
 * Inits the data used to display this field.
 */
void ViewInstantMessaging::initData()
{
	mTitleText = strdup(TXT_VIEW_IM_TITLE);
}

/**
 * Creates the view.
 */
void ViewInstantMessaging::addBody()
{
	const char* labels[] =
	{
		"username",
		"protocol"
	};

	ViewField::addBody();

	for (int i=0; i<mOwner->getInstantMessagingsCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d. %s", i + 1, getInstantMessagingTypeString(mOwner->getInstantMessaging(i)->getType()));
		if (mOwner->getInstantMessaging(i)->getType() == INSTANTMESSAGING_CUSTOM)
		{
			sprintf(title, "%s (%S)", title, mOwner->getInstantMessaging(i)->getLabel());
		}
		addSubTitle(title, mOwner->getAddress(i)->isPrimary());
		DELETE(title);

		char* protocol = new char[BUFF_SIZE];
		sprintf(protocol, "%s", getInstantMessagingProtocolString(mOwner->getInstantMessaging(i)->getProtocol()));

		if (mOwner->getInstantMessaging(i)->getProtocol() == PROTOCOL_CUSTOM)
		{
			sprintf(protocol, "%s (%S)", protocol, mOwner->getInstantMessaging(i)->getProtocolLabel());
		}

		const char* datas[] =
		{
			wstrtostr(mOwner->getInstantMessaging(i)->getUsername()),
			protocol
		};

		addSubFields(labels, datas, sizeof(labels)/sizeof(char*));
		DELETE(protocol);
	}
}

/**
 * Gets the name of the instant messaging protocol.
 * @param protocol 	The instant messaging protocol.
 * @return			The protocol name.
 */
const char* ViewInstantMessaging::getInstantMessagingProtocolString(eInstantMessagingProtocols protocol)
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

/**
 * Gets the name of the instant messaging type.
 * @param type	The instant messaging type.
 * @return 		The type name.
 */
const char* ViewInstantMessaging::getInstantMessagingTypeString(eInstantMessagingTypes type)
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

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
 * @file ViewEvent.cpp
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Event view Layout.
 *
 **/

#include <util.h>

#include "ViewEvent.h"
#include "ViewDefines.h"

using namespace PIM;
using namespace NativeUI;

/**
 * Constructor.
 * @param contact	The contact for which to display the field.
 */
ViewEvent::ViewEvent(Contact* contact):
		ViewField(contact)
{
	initData();
	createUI();
}

/**
 * Destructor.
 */
ViewEvent::~ViewEvent()
{
}

/**
 * Inits the data used to display this field.
 */
void ViewEvent::initData()
{
	mTitleText = strdup(TXT_VIEW_EVENT_TITLE);
}

/**
 * Creates the view.
 */
void ViewEvent::addBody()
{
	const char* labels[] =
	{
		"date",
	};

	ViewField::addBody();

	for (int i=0; i<mOwner->getEventsCount(); i++)
	{
		char* title = new char[BUFF_SIZE];
		sprintf(title, "%d. %s", i + 1, getEventTypeString(mOwner->getEvent(i)->getType()));
		if (mOwner->getEvent(i)->getType() == EVENT_CUSTOM)
		{
			sprintf(title, "%s (%S)", title, mOwner->getEvent(i)->getLabel());
		}
		addSubTitle(title, mOwner->getAddress(i)->isPrimary());
		DELETE(title);

		const char* datas[] =
		{
			sprint_time(mOwner->getEvent(i)->getDate())
		};

		addSubFields(labels, datas, sizeof(labels)/sizeof(char*));
	}
}

/**
 * Gets the name of the event type.
 * @param type	The event type.
 * @return 		The type name.
 */
const char* ViewEvent::getEventTypeString(eEventTypes type)
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

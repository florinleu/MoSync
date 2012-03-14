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
 * @file InstantMessaging.cpp
 * @author Florin Leu
 * @date 26 Feb 2011
 *
 * @brief PIM Field Instant Messaging class.
 *
 **/

#include <conprint.h>
#include <mawstring.h>

#include "InstantMessaging.h"
#include "util.h"

namespace PIM
{
	/*
	 * Constructor
	 */
	InstantMessaging::InstantMessaging():
		mIsPrimary(false)
	{

	}

	/*
	 * Read a complete instant messaging.
	 */
	void InstantMessaging::read(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: instant messaging read");
		args.field = MA_PIM_FIELD_CONTACT_IM;
		args.bufSize = PIM_BUF_SIZE;
		if (maPimItemGetValue(&args, index) > 0)
		{
			readUsername(args.buf);
			readProtocol(args.buf);
			readProtocolLabel(args.buf);

			readType(args.item, index);
			readLabel(args.item, index);
		}
	}

	void InstantMessaging::readUsername(const MAAddress buffer)
	{
		mUsername = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_IM_USERNAME);
	}

	void InstantMessaging::readProtocol(const MAAddress buffer)
	{
		wchar* wstrProtocol = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_IM_PROTOCOL);
		char* strProtocol = wstrtostr(wstrProtocol);

		if (strcmp(strProtocol, MA_PIM_CONTACT_IM_PROTOCOL_AIM) == 0)
		{
			mProtocol = PROTOCOL_AIM;
		}
		else if (strcmp(strProtocol, MA_PIM_CONTACT_IM_PROTOCOL_MSN) == 0)
		{
			mProtocol = PROTOCOL_MSN;
		}
		else if(strcmp(strProtocol, MA_PIM_CONTACT_IM_PROTOCOL_YAHOO) == 0)
		{
			mProtocol = PROTOCOL_YAHOO;
		}
		else if (strcmp(strProtocol, MA_PIM_CONTACT_IM_PROTOCOL_SKYPE) == 0)
		{
			mProtocol = PROTOCOL_SKYPE;
		}
		else if (strcmp(strProtocol, MA_PIM_CONTACT_IM_PROTOCOL_QQ) == 0)
		{
			mProtocol = PROTOCOL_QQ;
		}
		else if (strcmp(strProtocol, MA_PIM_CONTACT_IM_PROTOCOL_GOOGLE_TALK) == 0)
		{
			mProtocol = PROTOCOL_GOOGLETALK;
		}
		else if (strcmp(strProtocol, MA_PIM_CONTACT_IM_PROTOCOL_ICQ) == 0)
		{
			mProtocol = PROTOCOL_ICQ;
		}
		else if (strcmp(strProtocol, MA_PIM_CONTACT_IM_PROTOCOL_JABBER) == 0)
		{
			mProtocol = PROTOCOL_JABBER;
		}
		else if (strcmp(strProtocol, MA_PIM_CONTACT_IM_PROTOCOL_NETMEETING) == 0)
		{
			mProtocol = PROTOCOL_NETMEETING;
		}
		else
		{
			mProtocol = PROTOCOL_CUSTOM;
		}

		DELETE(wstrProtocol);
		DELETE(strProtocol);
	}

	void InstantMessaging::readProtocolLabel(const MAAddress buffer)
	{
		mProtocolLabel = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_IM_PROTOCOL_LABEL);
	}

	void InstantMessaging::readType(const MAHandle handle, const int index)
	{
		int attribute = maPimItemGetAttributes(handle, MA_PIM_FIELD_CONTACT_IM, index);

		if (attribute >> 16)
		{
			mIsPrimary = true;

			// Remove primary value from attribute.
			attribute = (attribute & 0xFFFF);
		}

		switch (attribute)
		{
			case MA_PIM_ATTR_IM_HOME:
				mType = INSTANTMESSAGING_HOME;
				break;
			case MA_PIM_ATTR_IM_WORK:
				mType = INSTANTMESSAGING_WORK;
				break;
			case MA_PIM_ATTR_IM_CUSTOM:
				mType = INSTANTMESSAGING_CUSTOM;
				break;
			default:
				mType = INSTANTMESSAGING_OTHER;
				break;
		}
	}

	void InstantMessaging::readLabel(const MAHandle handle, const int index)
	{
		MA_PIM_ARGS args;
		args.item = handle;
		args.field = MA_PIM_FIELD_CONTACT_IM;
		args.bufSize = PIM_BUF_SIZE;

		char buf[PIM_BUF_SIZE];
		args.buf = buf;
		args.bufSize = PIM_BUF_SIZE;
		maPimItemGetLabel(&args, index);

		DELETE(mLabel);
		wchar* src = (wchar*)args.buf;
		mLabel = wcsdup(src);
	}

	/*
	 * Getter for username.
	 */
	const wchar* InstantMessaging::getUsername() const
	{
		return mUsername;
	}

	/*
	 * Setter for username.
	 */
	void InstantMessaging::setUsername(wchar* username)
	{
		mUsername = username;
	}

	/*
	 * Getter for protocol.
	 */
	const eInstantMessagingProtocols& InstantMessaging::getProtocol() const
	{
		return mProtocol;
	}

	/*
	 * Setter for protocol.
	 */
	void InstantMessaging::setProtocol(const eInstantMessagingProtocols& protocol)
	{
		mProtocol = protocol;
	}

	/*
	 * Getter for protocol label.
	 */
	const wchar* InstantMessaging::getProtocolLabel() const
	{
		return mProtocolLabel;
	}

	/*
	 * Setter for protocol label.
	 */
	void InstantMessaging::setProtocolLabel(wchar* protocolLabel)
	{
		mProtocolLabel = protocolLabel;
	}

	/*
	 * Getter for type.
	 */
	const eInstantMessagingTypes& InstantMessaging::getType() const
	{
		return mType;
	}

	/*
	 * Setter for type.
	 */
	void InstantMessaging::setType(const eInstantMessagingTypes& type)
	{
		mType = type;
	}

	/*
	 * Getter for label.
	 */
	const wchar* InstantMessaging::getLabel() const
	{
		return mLabel;
	}

	/*
	 * Setter for label.
	 */
	void InstantMessaging::setLabel(wchar* label)
	{
		mLabel = label;
	}

	/*
	 * Returns true if this is a primary instant messaging.
	 */
	const bool InstantMessaging::isPrimary() const
	{
		return mIsPrimary;
	}
} //PIM

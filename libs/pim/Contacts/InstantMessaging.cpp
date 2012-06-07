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
		mUsername(NULL),
		mProtocolLabel(NULL),
		mLabel(NULL),
		mIsPrimary(false)
	{

	}

	/**
	 * Destructor.
	 */
	InstantMessaging::~InstantMessaging()
	{
		DELETE(mUsername);
		DELETE(mProtocolLabel);
		DELETE(mLabel);
	}

	/**
	 * Reads a contact's IM.
	 * @param args The arguments needed to read the IM.
	 * @param index The index of the IM to read.
	 */
	void InstantMessaging::read(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: instant messaging read");
		args.field = MA_PIM_FIELD_CONTACT_IM;
		args.bufSize = PIM_BUF_SIZE;
		if (maPimItemGetValue(&args, index) > 0)
		{
			mUsername = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_IM_USERNAME);

			readProtocol(args.buf);
			readProtocolLabel(args.buf);

			readType(args.item, index);
			readLabel(args.item, index);
		}
	}

	/**
	 * Writes a contact's IM.
	 * @param args The values to write.
	 * @index args The index of the IM to write.
	 */
	void InstantMessaging::write(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: IM write");

		wchar* name = getProtocolName();

		args.field = MA_PIM_FIELD_CONTACT_IM;
		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeInt(args.buf, MA_PIM_CONTACT_IM_COUNT, 0);
		args.bufSize += writeWString(args.buf, mUsername, args.bufSize);
		args.bufSize += writeWString(args.buf, name, args.bufSize);
		args.bufSize += writeWString(args.buf, mProtocolLabel, args.bufSize);
		maPimItemSetValue(&args, index, getAttribute());

		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeWString(args.buf, mLabel, 0);
		maPimItemSetLabel(&args, index);

		DELETE(name);
	}

	/**
	 * Deletes a contact's IM.
	 * @param handle The handle of the contact.
	 * @param index  The index of the IM to delete.
	 */
	void InstantMessaging::remove(MAHandle handle, int index)
	{
		printf("@LIB: IM delete");

		maPimItemRemoveValue(handle, MA_PIM_FIELD_CONTACT_IM, index);
	}

	/**
	 * Reads the protocol of the IM.
	 * @param handle The handle of the contact.
	 * @param index The index of this IM.
	 */
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

	/**
	 * Reads the protocol label of the IM.
	 * @param handle The handle of the contact.
	 * @param index The index of this IM.
	 */
	void InstantMessaging::readProtocolLabel(const MAAddress buffer)
	{
		mProtocolLabel = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_IM_PROTOCOL_LABEL);
	}

	/**
	 * Reads the type of the IM.
	 * @param handle The handle of the contact.
	 * @param index The index of this IM.
	 */
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
				mType = TYPE_HOME;
				break;
			case MA_PIM_ATTR_IM_WORK:
				mType = TYPE_WORK;
				break;
			case MA_PIM_ATTR_IM_CUSTOM:
				mType = TYPE_CUSTOM;
				break;
			default:
				mType = TYPE_OTHER;
				break;
		}
	}

	/**
	 * Reads the label of the IM.
	 * @param handle The handle of the contact.
	 * @param index The index of this IM.
	 */
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

		wchar* src = (wchar*)args.buf;
		mLabel = wcsdup(src);
	}

	/**
	 * Gets the contact's IM username.
	 * @return The username of the contact.
	 */
	const wchar* const InstantMessaging::getUsername() const
	{
		return mUsername;
	}

	/**
	 * Sets the contact's IM username.
	 * @param username The value to set.
	 */
	void InstantMessaging::setUsername(const wchar* const username)
	{
		DELETE(mUsername);
		mUsername = wcsdup(username);
	}

	/**
	 * Gets the IM protocol.
	 * @return The protocol of the IM.
	 */
	const InstantMessaging::eProtocols& InstantMessaging::getProtocol() const
	{
		return mProtocol;
	}

	/**
	 * Sets the IM protocol.
	 * @param protocol The value to set.
	 */
	void InstantMessaging::setProtocol(const InstantMessaging::eProtocols& protocol)
	{
		mProtocol = protocol;
	}

	/**
	 * Gets the IM protocol label.
	 * @return The protocol label of the IM.
	 */
	const wchar* const InstantMessaging::getProtocolLabel() const
	{
		return mProtocolLabel;
	}

	/**
	 * Sets the IM protocol label.
	 * @param protocolLabel The value to set.
	 */
	void InstantMessaging::setProtocolLabel(const wchar* const protocolLabel)
	{
		DELETE(mProtocolLabel);
		mProtocolLabel = wcsdup(protocolLabel);
	}

	/**
	 * Gets the IM type.
	 * @return The type of the IM.
	 */
	const InstantMessaging::eTypes& InstantMessaging::getType() const
	{
		return mType;
	}

	/**
	 * Sets the IM type.
	 * @param type The value to set.
	 */
	void InstantMessaging::setType(const InstantMessaging::eTypes& type)
	{
		mType = type;
	}

	/**
	 * Gets the IM label.
	 * @return The label of the IM.
	 */
	const wchar* const InstantMessaging::getLabel() const
	{
		return mLabel;
	}

	/**
	 * Sets the IM label.
	 * @param label The value to set.
	 */
	void InstantMessaging::setLabel(const wchar* const label)
	{
		DELETE(mLabel);
		mLabel = wcsdup(label);
	}

	/**
	 * Checks if this is or not a primary IM.
	 * @return True if this is a primary IM.
	 */
	const bool InstantMessaging::isPrimary() const
	{
		return mIsPrimary;
	}

	/**
	 * Sets this as a primary IM.
	 * @param primary true if this is a primary IM.
	 */
	void InstantMessaging::setPrimary(const bool primary)
	{
		mIsPrimary = primary;
	}

	/**
	 * Gets the protocol string according to mProtocol.
	 * @return The protocol name.
	 */
	wchar* InstantMessaging::getProtocolName() const
	{
		const char* str = NULL;
		switch (mProtocol)
		{
			case PROTOCOL_AIM:
				str = MA_PIM_CONTACT_IM_PROTOCOL_AIM;
				break;
			case PROTOCOL_MSN:
				str = MA_PIM_CONTACT_IM_PROTOCOL_MSN;
				break;
			case PROTOCOL_YAHOO:
				str = MA_PIM_CONTACT_IM_PROTOCOL_YAHOO;
				break;
			case PROTOCOL_SKYPE:
				str = MA_PIM_CONTACT_IM_PROTOCOL_SKYPE;
				break;
			case PROTOCOL_QQ:
				str = MA_PIM_CONTACT_IM_PROTOCOL_QQ;
				break;
			case PROTOCOL_GOOGLETALK:
				str = MA_PIM_CONTACT_IM_PROTOCOL_GOOGLE_TALK;
				break;
			case PROTOCOL_ICQ:
				str = MA_PIM_CONTACT_IM_PROTOCOL_ICQ;
				break;
			case PROTOCOL_JABBER:
				str = MA_PIM_CONTACT_IM_PROTOCOL_JABBER;
				break;
			case PROTOCOL_NETMEETING:
				str = MA_PIM_CONTACT_IM_PROTOCOL_NETMEETING;
				break;
			default:
				str = MA_PIM_CONTACT_IM_PROTOCOL_CUSTOM;
				break;
		}

		return strtowstr(str);
	}

	/**
	 * Computes the website attribute.
	 * @return The website attribute.
	 */
	const int InstantMessaging::getAttribute() const
	{
		int attribute = 0;
		switch (mType)
		{
			case TYPE_HOME:
				attribute = MA_PIM_ATTR_IM_HOME;
				break;
			case TYPE_WORK:
				attribute = MA_PIM_ATTR_IM_WORK;
				break;
			case TYPE_CUSTOM:
				attribute = MA_PIM_ATTR_IM_CUSTOM;
				break;
			default:
				attribute = MA_PIM_ATTR_IM_OTHER;
				break;
		}

		attribute |= (mIsPrimary ? MA_PIM_ATTRPREFERRED : 0);

		return attribute;
	}

} //PIM

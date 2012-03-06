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
 * @file Email.cpp
 * @author Florin Leu
 * @date 24 Feb 2011
 *
 * @brief PIM Field Email class.
 *
 **/

#include <conprint.h>
#include <mawstring.h>

#include "Email.h"
#include "Phone.h"
#include "util.h"

namespace PIM
{

	/*
	 * Constructor
	 */
	Email::Email():
		mIsPrimary(false)
	{

	}

	/*
	 * Read a complete email.
	 */
	void Email::read(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: email read");
		args.field = MA_PIM_FIELD_CONTACT_EMAIL;
		args.bufSize = BUF_SIZE;
		if (maPimItemGetValue(&args, index) >= 0)
		{
			readAddress(args.buf);

			readType(args.item, index);
			readLabel(args.item, index);
		}
	}

	void Email::readAddress(const MAAddress buffer)
	{
		DELETE(mAddress);
		wchar* src = (wchar*)buffer;
		int len = wcslen(src);
		mAddress = new wchar[len + 1];
		wcsncpy(mAddress, src, len);
	}

	void Email::readType(const MAHandle handle, const int index)
	{
		int attribute = maPimItemGetAttributes(handle, MA_PIM_FIELD_CONTACT_EMAIL, index);

		if (attribute >> 16)
		{
			mIsPrimary = true;

			// Remove primary value from attribute.
			attribute = (attribute & 0xFFFF);
		}

		switch (attribute)
		{
			case MA_PIM_ATTR_EMAIL_HOME:
				mType = EMAIL_HOME;
				break;
			case MA_PIM_ATTR_EMAIL_WORK:
				mType = EMAIL_WORK;
				break;
			case MA_PIM_ATTR_EMAIL_MOBILE:
				mType = EMAIL_MOBILE;
				break;
			case MA_PIM_ATTR_EMAIL_CUSTOM:
				mType = EMAIL_CUSTOM;
				break;
			default:
				mType = EMAIL_OTHER;
				break;
		}
	}

	void Email::readLabel(const MAHandle handle, const int index)
	{
		MA_PIM_ARGS args;
		args.item = handle;
		args.field = MA_PIM_FIELD_CONTACT_EMAIL;
		args.bufSize = BUF_SIZE;

		char buf[BUF_SIZE];
		args.buf = buf;
		args.bufSize = BUF_SIZE;
		maPimItemGetLabel(&args, index);
		DELETE(mLabel);
		wchar* src = (wchar*)args.buf;
		int len = wcslen(src);
		mLabel = new wchar[len + 1];
		wcsncpy(mLabel, src, len);
	}

	/*
	 * Getter for email address.
	 */
	const wchar* Email::getAddress() const
	{
		return mAddress;
	}

	/*
	 * Setter for email address.
	 */
	void Email::setAddress(wchar* address)
	{
		mAddress = address;
	}

	/*
	 * Getter for type.
	 */
	const eEmailTypes& Email::getType() const
	{
		return mType;
	}

	/*
	 * Setter for type.
	 */
	void Email::setType(const eEmailTypes& type)
	{
		mType = type;
	}

	/*
	 * Getter for label.
	 */
	const wchar* Email::getLabel() const
	{
		return mLabel;
	}

	/*
	 * Setter for label.
	 */
	void Email::setLabel(wchar* label)
	{
		mLabel = label;
	}

	/*
	 * Returns true if this is set as the primary email.
	 */
	const bool Email::isPrimary() const
	{
		return mIsPrimary;
	}

} //PIM

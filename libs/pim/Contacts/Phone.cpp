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
 * @file Phone.cpp
 * @author Florin Leu
 * @date 22 Feb 2011
 *
 * @brief PIM Field Phone class.
 *
 **/

#include <conprint.h>
#include <mawstring.h>

#include "Phone.h"
#include "util.h"

namespace PIM
{
	/*
	 * Read a complete phone number.
	 */
	void Phone::read(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: phone read");
		args.field = MA_PIM_FIELD_CONTACT_TEL;
		//CHECK_RESULT(maPimItemGetValue(&args, 0));
		if (maPimItemGetValue(&args, index))
		{
			readNumber(args.buf);

			readType(args.item, index);
			readLabel(args.item, index);
		}
	}

	void Phone::readNumber(MAAddress const buffer)
	{
		DELETE(mNumber);
		wchar* src = (wchar*)buffer;
		int len = wcslen(src);
		mNumber = new wchar[len + 1];
		wcsncpy(mNumber, src, len);
	}

	void Phone::readType(const MAHandle handle, const int index)
	{
		int attribute = maPimItemGetAttributes(handle, MA_PIM_FIELD_CONTACT_TEL, index);
		switch (attribute)
		{
			case MA_PIM_ATTR_PHONE_HOME:
				mType = PHONE_HOME;
				break;
			case MA_PIM_ATTR_PHONE_MOBILE:
				mType = PHONE_MOBILE;
				break;
			case MA_PIM_ATTR_PHONE_HOME_FAX:
				mType = PHONE_HOME_FAX;
				break;
			case MA_PIM_ATTR_PHONE_WORK_FAX:
				mType = PHONE_WORK_FAX;
				break;
			case MA_PIM_ATTR_PHONE_PAGER:
				mType = PHONE_PAGER;
				break;
			case MA_PIM_ATTR_PHONE_IPHONE:
				mType = PHONE_IPHONE;
				break;
			case MA_PIM_ATTR_PHONE_WORK:
				mType = PHONE_WORK;
				break;
			case MA_PIM_ATTR_PHONE_CALLBACK:
				mType = PHONE_CALLBACK;
				break;
			case MA_PIM_ATTR_PHONE_CAR:
				mType = PHONE_CAR;
				break;
			case MA_PIM_ATTR_PHONE_COMPANY_MAIN:
				mType = PHONE_COMPANY_MAIN;
				break;
			case MA_PIM_ATTR_PHONE_ISDN:
				mType = PHONE_ISDN;
				break;
			case MA_PIM_ATTR_PHONE_OTHER_FAX:
				mType = PHONE_OTHER_FAX;
				break;
			case MA_PIM_ATTR_PHONE_RADIO:
				mType = PHONE_RADIO;
				break;
			case MA_PIM_ATTR_PHONE_TELEX:
				mType = PHONE_TELEX;
				break;
			case MA_PIM_ATTR_PHONE_TTY_TDD:
				mType = PHONE_TTY_TDD;
				break;
			case MA_PIM_ATTR_PHONE_WORK_MOBILE:
				mType = PHONE_WORK_MOBILE;
				break;
			case MA_PIM_ATTR_PHONE_WORK_PAGER:
				mType = PHONE_WORK_PAGER;
				break;
			case MA_PIM_ATTR_PHONE_ASSISTANT:
				mType = PHONE_ASSISTANT;
				break;
			case MA_PIM_ATTR_PHONE_MMS:
				mType = PHONE_MMS;
				break;
			case MA_PIM_ATTR_PHONE_CUSTOM:
				mType = PHONE_CUSTOM;
				break;
			default:
				mType = PHONE_OTHER;
				break;
		}
	}

	void Phone::readLabel(const MAHandle handle, const int index)
	{
		MA_PIM_ARGS args;
		args.item = handle;
		args.field = MA_PIM_FIELD_CONTACT_TEL;

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
	 * Getter for phone number.
	 */
	const wchar* Phone::getNumber() const
	{
		return mNumber;
	}

	/*
	 * Setter for phone number.
	 */
	void Phone::setNumber(wchar* const number)
	{
		mNumber = number;
	}

	/*
	 * Getter for type.
	 */
	const ePhoneTypes& Phone::getType() const
	{
		return mType;
	}

	/*
	 * Setter for type.
	 */
	void Phone::setType(const ePhoneTypes& type)
	{
		mType = type;
	}

	/*
	 * Getter for label.
	 */
	const wchar* Phone::getLabel() const
	{
		return mLabel;
	}

	/*
	 * Setter for label.
	 */
	void Phone::setLabel(wchar* const label)
	{
		mLabel = label;
	}

} //PIM

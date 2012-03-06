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
 * @file Event.cpp
 * @author Florin Leu
 * @date 27 Feb 2011
 *
 * @brief PIM Field Event class.
 *
 **/

#include <conprint.h>
#include <mawstring.h>
#include <mastdlib.h>

#include "Event.h"
#include "util.h"

namespace PIM
{

	/*
	 * Constructor
	 */
	Event::Event():
		mIsPrimary(false)
	{

	}

	/*
	 * Read a complete event.
	 */
	void Event::read(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: event read");
		args.field = MA_PIM_FIELD_CONTACT_EVENT;
		args.bufSize = BUF_SIZE;
		if (maPimItemGetValue(&args, index) >= 0)
		{
			readDate(args.buf);

			readType(args.item, index);
			readLabel(args.item, index);
		}
	}

	void Event::readDate(const MAAddress buffer)
	{
		mDate = *(int*)buffer;
	}

	void Event::readType(const MAHandle handle, const int index)
	{
		int attribute = maPimItemGetAttributes(handle, MA_PIM_FIELD_CONTACT_EVENT, index);

		if (attribute >> 16)
		{
			mIsPrimary = true;

			// Remove primary value from attribute.
			attribute = (attribute & 0xFFFF);
		}

		switch (attribute)
		{
			case MA_PIM_ATTR_EVENT_BIRTHDAY:
				mType = EVENT_BIRTHDAY;
				break;
			case MA_PIM_ATTR_EVENT_ANNIVERSARY:
				mType = EVENT_ANNIVERSARY;
				break;
			case MA_PIM_ATTR_EVENT_CUSTOM:
				mType = EVENT_CUSTOM;
				break;
			default:
				mType = EVENT_OTHER;
				break;
		}
	}

	void Event::readLabel(const MAHandle handle, const int index)
	{
		MA_PIM_ARGS args;
		args.item = handle;
		args.field = MA_PIM_FIELD_CONTACT_EVENT;
		args.bufSize = BUF_SIZE;

		char buf[BUF_SIZE];
		args.buf = buf;
		args.bufSize = BUF_SIZE;
		maPimItemGetLabel(&args, index);
		DELETE(mLabel);
		wchar* src = (wchar*)args.buf;
		mLabel = wcsdup(src);
	}

	/*
	 * Getter for date.
	 */
	const time_t& Event::getDate() const
	{
		return mDate;
	}

	/*
	 * Setter for dDate.
	 */
	void Event::setDate(const time_t& date)
	{
		mDate = date;
	}

	/*
	 * Getter for type.
	 */
	const eEventTypes& Event::getType() const
	{
		return mType;
	}

	/*
	 * Setter for type.
	 */
	void Event::setType(const eEventTypes& type)
	{
		mType = type;
	}

	/*
	 * Getter for label.
	 */
	const wchar* Event::getLabel() const
	{
		return mLabel;
	}

	/*
	 * Setter for label.
	 */
	void Event::setLabel(wchar* label)
	{
		mLabel = label;
	}

	/*
	 * Returns true if this is set as the primary phone.
	 */
	const bool Event::isPrimary() const
	{
		return mIsPrimary;
	}

} //PIM

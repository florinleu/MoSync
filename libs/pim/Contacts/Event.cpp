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
	/**
	 * Constructor.
	 */
	Event::Event():
		mLabel(NULL),
		mIsPrimary(false)
	{

	}

	/**
	 * Destructor.
	 */
	Event::~Event()
	{
		DELETE(mLabel);
	}

	/**
	 * Reads a contact's event.
	 * @param args The arguments needed to read the event.
	 * @param index The index of the event to read.
	 */
	void Event::read(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: event read");
		args.field = MA_PIM_FIELD_CONTACT_EVENT;
		args.bufSize = PIM_BUF_SIZE;
		if (maPimItemGetValue(&args, index) >= 0)
		{
			mDate = *(int*)args.buf;

			readType(args.item, index);
			readLabel(args.item, index);
		}
	}

	/**
	 * Writes a contact's event.
	 * @param args The values to write.
	 * @index args The index of the event to write.
	 */
	void Event::write(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: event write");

		args.field = MA_PIM_FIELD_CONTACT_EVENT;
		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeInt(args.buf, mDate, 0);
		maPimItemSetValue(&args, index, getAttribute());

		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeWString(args.buf, mLabel, 0);
		maPimItemSetLabel(&args, index);
	}

	/**
	 * Adds a new event to this contact.
	 */
	void Event::add(MA_PIM_ARGS& args)
	{
		args.field = MA_PIM_FIELD_CONTACT_EVENT;
		maPimItemAddValue(&args, MA_PIM_ATTR_EVENT_BIRTHDAY);
	}

	/**
	 * Deletes a contact's event.
	 * @param handle The handle of the contact.
	 * @param index  The index of the event to delete.
	 */
	void Event::remove(MAHandle handle, int index)
	{
		printf("@LIB: event delete");

		maPimItemRemoveValue(handle, MA_PIM_FIELD_CONTACT_EVENT, index);
	}

	/**
	 * Reads the type of the event.
	 * @param handle The handle of the contact.
	 * @param index The index of this event.
	 */
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
				mType = TYPE_BIRTHDAY;
				break;
			case MA_PIM_ATTR_EVENT_ANNIVERSARY:
				mType = TYPE_ANNIVERSARY;
				break;
			case MA_PIM_ATTR_EVENT_CUSTOM:
				mType = TYPE_CUSTOM;
				break;
			default:
				mType = TYPE_OTHER;
				break;
		}
	}

	/**
	 * Reads the label of the event.
	 * @param handle The handle of the contact.
	 * @param index The index of this event.
	 */
	void Event::readLabel(const MAHandle handle, const int index)
	{
		MA_PIM_ARGS args;
		args.item = handle;
		args.field = MA_PIM_FIELD_CONTACT_EVENT;
		args.bufSize = PIM_BUF_SIZE;

		char buf[PIM_BUF_SIZE];
		args.buf = buf;
		args.bufSize = PIM_BUF_SIZE;
		maPimItemGetLabel(&args, index);

		wchar* src = (wchar*)args.buf;
		mLabel = wcsdup(src);
	}

	/**
	 * Gets the contact's event date.
	 * @return The date of the contact.
	 */
	const time_t& Event::getDate() const
	{
		return mDate;
	}

	/**
	 * Sets the contact's event date.
	 * @param date The value to set.
	 */
	void Event::setDate(const time_t& date)
	{
		mDate = date;
	}

	/**
	 * Gets the event type.
	 * @return The type of the event.
	 */
	const Event::eTypes& Event::getType() const
	{
		return mType;
	}

	/**
	 * Sets the event type.
	 * @param type The value to set.
	 */
	void Event::setType(const Event::eTypes& type)
	{
		mType = type;
	}

	/**
	 * Gets the event label.
	 * @return The label of the event.
	 */
	const wchar* const Event::getLabel() const
	{
		return mLabel;
	}

	/**
	 * Sets the event label.
	 * @param label The value to set.
	 */
	void Event::setLabel(const wchar* const label)
	{
		DELETE(mLabel);
		mLabel = wcsdup(label);
	}

	/**
	 * Checks if this is or not a primary event.
	 * @return True if this is a primary event.
	 */
	const bool Event::isPrimary() const
	{
		return mIsPrimary;
	}

	/**
	 * Sets this as a primary event.
	 * @param primary true if this is a primary event.
	 */
	void Event::setPrimary(const bool primary)
	{
		mIsPrimary = primary;
	}

	/**
	 * Computes the event attribute.
	 * @return The event attribute.
	 */
	const int Event::getAttribute() const
	{
		int attribute = 0;
		switch (mType)
		{
			case TYPE_BIRTHDAY:
				attribute = MA_PIM_ATTR_EVENT_BIRTHDAY;
				break;
			case TYPE_ANNIVERSARY:
				attribute = MA_PIM_ATTR_EVENT_ANNIVERSARY;
				break;
			case TYPE_CUSTOM:
				attribute = MA_PIM_ATTR_EVENT_CUSTOM;
				break;
			default:
				attribute = MA_PIM_ATTR_EVENT_OTHER;
				break;
		}

		attribute |= (mIsPrimary ? MA_PIM_ATTRPREFERRED : 0);

		return attribute;
	}

} //PIM

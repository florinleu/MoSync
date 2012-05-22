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
	/**
	 * Constructor.
	 */
	Phone::Phone():
		mNumber(NULL),
		mLabel(NULL),
		mIsPrimary(false)
	{

	}

	/**
	 * Destructor.
	 */
	Phone::~Phone()
	{
		DELETE(mNumber);
		DELETE(mLabel);
	}

	/**
	 * Reads a contact's phone.
	 * @param args The arguments needed to read the phone.
	 * @param index The index of the phone to read.
	 */
	void Phone::read(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: phone read");
		args.field = MA_PIM_FIELD_CONTACT_TEL;
		args.bufSize = PIM_BUF_SIZE;
		if (maPimItemGetValue(&args, index) >= 0)
		{
			DELETE(mNumber);
			wchar* src = (wchar*)args.buf;
			mNumber = wcsdup(src);

			readType(args.item, index);
			readLabel(args.item, index);
		}
	}

	/**
	 * Writes a contact's phone.
	 * @param args The values to write.
	 * @index args The index of the phone to write.
	 */
	void Phone::write(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: phone write");

		args.field = MA_PIM_FIELD_CONTACT_TEL;
		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeWString(args.buf, mNumber, 0);
		maPimItemSetValue(&args, index, getAttribute());

		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeWString(args.buf, mLabel, 0);
		maPimItemSetLabel(&args, index);
	}

	/**
	 * Deletes a contact's phone.
	 * @param handle The handle of the contact.
	 * @param index  The index of the phone to delete.
	 */
	void Phone::remove(MAHandle handle, int index)
	{
		printf("@LIB: phone delete");

		maPimItemRemoveValue(handle, MA_PIM_FIELD_CONTACT_TEL, index);
	}

	/**
	 * Reads the type of the phone.
	 * @param handle The handle of the contact.
	 * @param index The index of this phone.
	 */
	void Phone::readType(const MAHandle handle, const int index)
	{
		int attribute = maPimItemGetAttributes(handle, MA_PIM_FIELD_CONTACT_TEL, index);

		if (attribute >> 16)
		{
			mIsPrimary = true;

			// Remove primary value from attribute.
			attribute = (attribute & 0xFFFF);
		}

		switch (attribute)
		{
			case MA_PIM_ATTR_PHONE_HOME:
				mType = HOME;
				break;
			case MA_PIM_ATTR_PHONE_MOBILE:
				mType = MOBILE;
				break;
			case MA_PIM_ATTR_PHONE_HOME_FAX:
				mType = HOME_FAX;
				break;
			case MA_PIM_ATTR_PHONE_WORK_FAX:
				mType = WORK_FAX;
				break;
			case MA_PIM_ATTR_PHONE_PAGER:
				mType = PAGER;
				break;
			case MA_PIM_ATTR_PHONE_IPHONE:
				mType = IPHONE;
				break;
			case MA_PIM_ATTR_PHONE_WORK:
				mType = WORK;
				break;
			case MA_PIM_ATTR_PHONE_CALLBACK:
				mType = CALLBACK;
				break;
			case MA_PIM_ATTR_PHONE_CAR:
				mType = CAR;
				break;
			case MA_PIM_ATTR_PHONE_COMPANY_MAIN:
				mType = COMPANY_MAIN;
				break;
			case MA_PIM_ATTR_PHONE_ISDN:
				mType = ISDN;
				break;
			case MA_PIM_ATTR_PHONE_OTHER_FAX:
				mType = OTHER_FAX;
				break;
			case MA_PIM_ATTR_PHONE_RADIO:
				mType = RADIO;
				break;
			case MA_PIM_ATTR_PHONE_TELEX:
				mType = TELEX;
				break;
			case MA_PIM_ATTR_PHONE_TTY_TDD:
				mType = TTY_TDD;
				break;
			case MA_PIM_ATTR_PHONE_WORK_MOBILE:
				mType = WORK_MOBILE;
				break;
			case MA_PIM_ATTR_PHONE_WORK_PAGER:
				mType = WORK_PAGER;
				break;
			case MA_PIM_ATTR_PHONE_ASSISTANT:
				mType = ASSISTANT;
				break;
			case MA_PIM_ATTR_PHONE_MMS:
				mType = MMS;
				break;
			case MA_PIM_ATTR_PHONE_CUSTOM:
				mType = CUSTOM;
				break;
			default:
				mType = OTHER;
				break;
		}
	}

	/**
	 * Reads the label of the phone.
	 * @param handle The handle of the contact.
	 * @param index The index of this phone.
	 */
	void Phone::readLabel(const MAHandle handle, const int index)
	{
		MA_PIM_ARGS args;
		args.item = handle;
		args.field = MA_PIM_FIELD_CONTACT_TEL;
		args.bufSize = PIM_BUF_SIZE;

		char buf[PIM_BUF_SIZE];
		args.buf = buf;
		args.bufSize = PIM_BUF_SIZE;
		maPimItemGetLabel(&args, index);

		DELETE(mLabel);
		wchar* src = (wchar*)args.buf;
		mLabel = wcsdup(src);
	}

	/**
	 * Gets the contact's phone number.
	 * @return The number of the contact.
	 */
	const wchar* const Phone::getNumber() const
	{
		return mNumber;
	}

	/**
	 * Sets the contact's phone number.
	 * @param number The value to set.
	 */
	void Phone::setNumber(const wchar* const number)
	{
		DELETE(mNumber);
		mNumber = wcsdup(number);
	}

	/**
	 * Gets the phone type.
	 * @return The type of the phone.
	 */
	const Phone::eTypes& Phone::getType() const
	{
		return mType;
	}

	/**
	 * Sets the phone type.
	 * @param type The value to set.
	 */
	void Phone::setType(const Phone::eTypes& type)
	{
		mType = type;
	}

	/**
	 * Gets the phone label.
	 * @return The label of the phone.
	 */
	const wchar* const Phone::getLabel() const
	{
		return mLabel;
	}

	/**
	 * Sets the phone label.
	 * @param state The value to set.
	 */
	void Phone::setLabel(const wchar* const label)
	{
		DELETE(mLabel);
		mLabel = wcsdup(label);
	}

	/**
	 * Checks if this is or not a primary phone.
	 * @return True if this is a primary phone.
	 */
	const bool Phone::isPrimary() const
	{
		return mIsPrimary;
	}

	/**
	 * Sets this as a primary phone.
	 * @param primary true if this is a primary phone.
	 */
	void Phone::setPrimary(const bool primary)
	{
		mIsPrimary = primary;
	}

	/**
	 * Computes the phone attribute.
	 * @return The phone attribute.
	 */
	const int Phone::getAttribute() const
	{
		int attribute = 0;
		switch (mType)
		{
			case HOME:
				attribute = MA_PIM_ATTR_PHONE_HOME;
				break;
			case MOBILE:
				attribute = MA_PIM_ATTR_PHONE_MOBILE;
				break;
			case HOME_FAX:
				attribute = MA_PIM_ATTR_PHONE_HOME_FAX;
				break;
			case WORK_FAX:
				attribute = MA_PIM_ATTR_PHONE_WORK_FAX;
				break;
			case PAGER:
				attribute = MA_PIM_ATTR_PHONE_PAGER;
				break;
			case IPHONE:
				attribute = MA_PIM_ATTR_PHONE_IPHONE;
				break;
			case WORK:
				attribute = MA_PIM_ATTR_PHONE_WORK;
				break;
			case CALLBACK:
				attribute = MA_PIM_ATTR_PHONE_CALLBACK;
				break;
			case CAR:
				attribute = MA_PIM_ATTR_PHONE_CAR;
				break;
			case COMPANY_MAIN:
				attribute = MA_PIM_ATTR_PHONE_COMPANY_MAIN;
				break;
			case ISDN:
				attribute = MA_PIM_ATTR_PHONE_ISDN;
				break;
			case OTHER_FAX:
				attribute = MA_PIM_ATTR_PHONE_OTHER_FAX;
				break;
			case RADIO:
				attribute = MA_PIM_ATTR_PHONE_RADIO;
				break;
			case TELEX:
				attribute = MA_PIM_ATTR_PHONE_TELEX;
				break;
			case TTY_TDD:
				attribute = MA_PIM_ATTR_PHONE_TTY_TDD;
				break;
			case WORK_MOBILE:
				attribute = MA_PIM_ATTR_PHONE_WORK_MOBILE;
				break;
			case WORK_PAGER:
				attribute = MA_PIM_ATTR_PHONE_WORK_PAGER;
				break;
			case ASSISTANT:
				attribute = MA_PIM_ATTR_PHONE_ASSISTANT;
				break;
			case MMS:
				attribute = MA_PIM_ATTR_PHONE_MMS;
				break;
			case CUSTOM:
				attribute = MA_PIM_ATTR_PHONE_CUSTOM;
				break;
			default:
				attribute = MA_PIM_ATTR_ADDR_OTHER;
				break;
		}

		attribute |= (mIsPrimary ? MA_PIM_ATTRPREFERRED : 0);

		return attribute;
	}

} //PIM

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
#include "util.h"

namespace PIM
{
	/**
	 * Constructor.
	 */
	Email::Email():
		mAddress(NULL),
		mLabel(NULL),
		mIsPrimary(false)
	{

	}

	/**
	 * Destructor.
	 */
	Email::~Email()
	{
		DELETE(mAddress);
		DELETE(mLabel);
	}

	/**
	 * Reads a contact's e-mail.
	 * @param args The arguments needed to read the e-mail.
	 * @param index The index of the e-mail to read.
	 */
	void Email::read(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: email read");
		args.field = MA_PIM_FIELD_CONTACT_EMAIL;
		args.bufSize = PIM_BUF_SIZE;
		if (maPimItemGetValue(&args, index) >= 0)
		{
			DELETE(mAddress);
			wchar* src = (wchar*)args.buf;
			mAddress = wcsdup(src);

			readType(args.item, index);
			readLabel(args.item, index);
		}
	}

	/**
	 * Writes a contact's e-mail.
	 * @param args The values to write.
	 * @index args The index of the e-mail to write.
	 */
	void Email::write(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: e-mail write");

		args.field = MA_PIM_FIELD_CONTACT_EMAIL;
		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeWString(args.buf, mAddress, 0);
		maPimItemSetValue(&args, index, getAttribute());

		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeWString(args.buf, mLabel, 0);
		maPimItemSetLabel(&args, index);
	}

	/**
	 * Deletes a contact's e-mail.
	 * @param handle The handle of the contact.
	 * @param index  The index of the e-mail to delete.
	 */
	void Email::remove(MAHandle handle, int index)
	{
		printf("@LIB: e-mail delete");

		maPimItemRemoveValue(handle, MA_PIM_FIELD_CONTACT_EMAIL, index);
	}

	/**
	 * Reads the type of the e-mail.
	 * @param handle The handle of the contact.
	 * @param index The index of this e-mail.
	 */
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
				mType = HOME;
				break;
			case MA_PIM_ATTR_EMAIL_WORK:
				mType = WORK;
				break;
			case MA_PIM_ATTR_EMAIL_MOBILE:
				mType = MOBILE;
				break;
			case MA_PIM_ATTR_EMAIL_CUSTOM:
				mType = CUSTOM;
				break;
			default:
				mType = OTHER;
				break;
		}
	}

	/**
	 * Reads the label of the e-mail.
	 * @param handle The handle of the contact.
	 * @param index The index of this e-mail.
	 */
	void Email::readLabel(const MAHandle handle, const int index)
	{
		MA_PIM_ARGS args;
		args.item = handle;
		args.field = MA_PIM_FIELD_CONTACT_EMAIL;
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
	 * Gets the contact's e-mail address.
	 * @return The address of the contact.
	 */
	const wchar* const Email::getAddress() const
	{
		return mAddress;
	}

	/**
	 * Sets the contact's e-mail address.
	 * @param number The value to set.
	 */
	void Email::setAddress(const wchar* const address)
	{
		printf("@LIB email setAddress: %S", address);
		DELETE(mAddress);
		mAddress = wcsdup(address);
	}

	/**
	 * Gets the e-mail type.
	 * @return The type of the e-mail.
	 */
	const Email::eTypes& Email::getType() const
	{
		return mType;
	}

	/**
	 * Sets the e-mail type.
	 * @param type The value to set.
	 */
	void Email::setType(const Email::eTypes& type)
	{
		mType = type;
	}

	/**
	 * Gets the e-mail label.
	 * @return The label of the e-mail.
	 */
	const wchar* const Email::getLabel() const
	{
		return mLabel;
	}

	/**
	 * Sets the e-mail label.
	 * @param state The value to set.
	 */
	void Email::setLabel(const wchar* const label)
	{
		DELETE(mLabel);
		mLabel = wcsdup(label);
	}

	/**
	 * Checks if this is or not a primary e-mail.
	 * @return True if this is a primary e-mail.
	 */
	const bool Email::isPrimary() const
	{
		return mIsPrimary;
	}

	/**
	 * Sets this as a primary e-mail.
	 * @param primary true if this is a primary e-mail.
	 */
	void Email::setPrimary(const bool primary)
	{
		mIsPrimary = primary;
	}

	/**
	 * Computes the e-mail attribute.
	 * @return The e-mail attribute.
	 */
	const int Email::getAttribute() const
	{
		int attribute = 0;
		switch (mType)
		{
			case HOME:
				attribute = MA_PIM_ATTR_EMAIL_HOME;
				break;
			case WORK:
				attribute = MA_PIM_ATTR_EMAIL_WORK;
				break;
			case MOBILE:
				attribute = MA_PIM_ATTR_EMAIL_MOBILE;
				break;
			case CUSTOM:
				attribute = MA_PIM_ATTR_EMAIL_CUSTOM;
				break;
			default:
				attribute = MA_PIM_ATTR_EMAIL_OTHER;
				break;
		}

		attribute |= (mIsPrimary ? MA_PIM_ATTRPREFERRED : 0);

		return attribute;
	}

} //PIM

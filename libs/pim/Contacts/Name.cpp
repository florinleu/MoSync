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
 * @file Name.cpp
 * @author Florin Leu
 * @date 09 Feb 2011
 *
 * @brief PIM Field Name class.
 *
 **/

#include <mawstring.h>

#include "Name.h"
#include "util.h"

#include <conprint.h>

namespace PIM
{
	/**
	 * Constructor.
	 */
	Name::Name():
		mDisplayName(NULL),
		mFirstName(NULL),
		mMiddleName(NULL),
		mLastName(NULL),
		mNickname(NULL),
		mPrefix(NULL),
		mSuffix(NULL),
		mPhoneticFirstName(NULL),
		mPhoneticMiddleName(NULL),
		mPhoneticLastName(NULL),
		mFormattedName(NULL)
	{
	}

	/**
	 * Destructor.
	 */
	Name::~Name()
	{
		DELETE(mDisplayName);
		DELETE(mFirstName);
		DELETE(mMiddleName);
		DELETE(mLastName);
		DELETE(mNickname);
		DELETE(mPrefix);
		DELETE(mSuffix);
		DELETE(mPhoneticFirstName);
		DELETE(mPhoneticMiddleName);
		DELETE(mPhoneticLastName);
		DELETE(mFormattedName);
	}

	/**
	 * Reads the contact's name.
	 * @param args The arguments needed to read the name.
	 * @return true on success.
	 */
	bool Name::read(MA_PIM_ARGS& args)
	{
		printf("@LIB: name read");
		bool isSupported = false;

		args.field = MA_PIM_FIELD_CONTACT_NAME;
		args.bufSize = PIM_BUF_SIZE;
		if (maPimItemGetValue(&args, 0) > 0)
		{
			isSupported = true;
			mDisplayName = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_NAME_DISPLAY);
			mFirstName = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_NAME_GIVEN);
			mMiddleName = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_NAME_OTHER);
			mLastName = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_NAME_FAMILY);
			mPrefix = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_NAME_PREFIX);
			mSuffix = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_NAME_SUFFIX);
			mPhoneticFirstName = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_NAME_PHONETIC_GIVEN);
			mPhoneticMiddleName = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_NAME_PHONETIC_OTHER);
			mPhoneticLastName = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_NAME_PHONETIC_FAMILY);
		}

		args.field = MA_PIM_FIELD_CONTACT_NICKNAME;
		args.bufSize = PIM_BUF_SIZE;
		if (maPimItemGetValue(&args, 0) >=0 )
		{
			isSupported = true;
			wchar* src = (wchar*)args.buf;
			mNickname = wcsdup(src);
		}

		args.field = MA_PIM_FIELD_CONTACT_FORMATTED_NAME;
		args.bufSize = PIM_BUF_SIZE;
		if (maPimItemGetValue(&args, 0) >=0)
		{
			isSupported = true;
			wchar* src = (wchar*)args.buf;
			mFormattedName = wcsdup(src);
		}

		return isSupported;
	}

	/**
	 * Writes the contact's id.
	 * @param args The values to write.
	 */
	void Name::write(MA_PIM_ARGS& args)
	{
		printf("@LIB: name write");

		args.field = MA_PIM_FIELD_CONTACT_NAME;
		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeInt(args.buf, MA_PIM_CONTACT_NAME_COUNT, 0);
		args.bufSize += writeWString(args.buf, mLastName, args.bufSize);
		args.bufSize += writeWString(args.buf, mFirstName, args.bufSize);
		args.bufSize += writeWString(args.buf, mMiddleName, args.bufSize);
		args.bufSize += writeWString(args.buf, mPrefix, args.bufSize);
		args.bufSize += writeWString(args.buf, mSuffix, args.bufSize);
		args.bufSize += writeWString(args.buf, mPhoneticLastName, args.bufSize);
		args.bufSize += writeWString(args.buf, mPhoneticFirstName, args.bufSize);
		args.bufSize += writeWString(args.buf, mPhoneticMiddleName, args.bufSize);
		args.bufSize += writeWString(args.buf, NULL, args.bufSize);
		maPimItemSetValue(&args, 0, 0);

		args.field = MA_PIM_FIELD_CONTACT_NICKNAME;
		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeWString(args.buf, mNickname, 0);
		maPimItemSetValue(&args, 0, 0);
	}

	/**
	 * Deletes a contact's name.
	 * @param handle The handle of the contact.
	 */
	void Name::remove(MAHandle handle)
	{
		printf("@LIB: name delete");

		maPimItemRemoveValue(handle, MA_PIM_FIELD_CONTACT_NAME, 0);
		maPimItemRemoveValue(handle, MA_PIM_FIELD_CONTACT_NICKNAME, 0);
	}

	/**
	 * Gets the contact's display name.
	 * @return The display name of the contact.
	 */
	const wchar* const Name::getDisplayName() const
	{
		return mDisplayName;
	}

	/**
	 * Sets the contact's display name.
	 * @param displayName The value to set.
	 */
	void Name::setDisplayName(const wchar* const displayName)
	{
		DELETE(mDisplayName);
		mDisplayName = wcsdup(displayName);
	}

	/**
	 * Gets the contact's first name.
	 * @return The first name of the contact.
	 */
	const wchar* const Name::getFirstName() const
	{
		return mFirstName;
	}

	/**
	 * Sets the contact's first name.
	 * @param firstName The value to set.
	 */
	void Name::setFirstName(const wchar* const firstName)
	{
		DELETE(mFirstName);
		mFirstName = wcsdup(firstName);
	}

	/**
	 * Gets the contact's middle name.
	 * @return The middle name of the contact.
	 */
	const wchar* const Name::getMiddleName() const
	{
		return mMiddleName;
	}

	/**
	 * Sets the contact's middle name.
	 * @param middleName The value to set.
	 */
	void Name::setMiddleName(const wchar* const middleName)
	{
		DELETE(mFirstName);
		mMiddleName = wcsdup(middleName);
	}

	/**
	 * Gets the contact's last name.
	 * @return The last name of the contact.
	 */
	const wchar* const Name::getLastName() const
	{
		return mLastName;
	}

	/**
	 * Sets the contact's last name.
	 * @param lastName The value to set.
	 */
	void Name::setLastName(const wchar* const lastName)
	{
		DELETE(mFirstName);
		mLastName = wcsdup(lastName);
	}

	/**
	 * Gets the contact's nickname.
	 * @return The nickname of the contact.
	 */
	const wchar* const Name::getNickname() const
	{
		return mNickname;
	}

	/**
	 * Sets the contact's nickname.
	 * @param nickname The value to set.
	 */
	void Name::setNickname(const wchar* const nickname)
	{
		DELETE(mFirstName);
		mNickname = wcsdup(nickname);
	}

	/**
	 * Gets the contact's prefix.
	 * @return The prefix of the contact.
	 */
	const wchar* const Name::getPrefix() const
	{
		return mPrefix;
	}

	/**
	 * Sets the contact's prefix.
	 * @param prefix The value to set.
	 */
	void Name::setPrefix(const wchar* const prefix)
	{
		DELETE(mFirstName);
		mPrefix = wcsdup(prefix);
	}

	/**
	 * Gets the contact's suffix.
	 * @return The suffix of the contact.
	 */
	const wchar* const Name::getSuffix() const
	{
		return mSuffix;
	}

	/**
	 * Sets the contact's suffix.
	 * @param suffix The value to set.
	 */
	void Name::setSuffix(const wchar* const suffix)
	{
		DELETE(mFirstName);
		mSuffix = wcsdup(suffix);
	}

	/**
	 * Gets the contact's phonetic first name.
	 * @return The phonetic first name of the contact.
	 */
	const wchar* const Name::getPhoneticFirstName() const
	{
		return mPhoneticFirstName;
	}

	/**
	 * Sets the contact's phonetic first name.
	 * @param phoneticFirstName The value to set.
	 */
	void Name::setPhoneticFirstName(const wchar* const phoneticFirstName)
	{
		DELETE(mFirstName);
		mPhoneticFirstName = wcsdup(phoneticFirstName);
	}

	/**
	 * Gets the contact's phonetic middle name.
	 * @return The phonetic middle name of the contact.
	 */
	const wchar* const Name::getPhoneticMiddleName() const
	{
		return mPhoneticMiddleName;
	}

	/**
	 * Sets the contact's phonetic middle name.
	 * @param phoneticMiddleName The value to set.
	 */
	void Name::setPhoneticMiddleName(const wchar* const phoneticMiddleName)
	{
		DELETE(mFirstName);
		mPhoneticMiddleName = wcsdup(phoneticMiddleName);
	}

	/**
	 * Gets the contact's phonetic last name.
	 * @return The phonetic last name of the contact.
	 */
	const wchar* const Name::getPhoneticLastName() const
	{
		return mPhoneticLastName;
	}

	/**
	 * Sets the contact's phonetic last name.
	 * @param phoneticLastName The value to set.
	 */
	void Name::setPhoneticLastName(const wchar* const phoneticLastName)
	{
		DELETE(mFirstName);
		mPhoneticLastName = wcsdup(phoneticLastName);
	}

	/**
	 * Gets the contact's formatted name.
	 * @return The formatted name of the contact.
	 */
	const wchar* const Name::getFormattedName() const
	{
		return mFormattedName;
	}
}

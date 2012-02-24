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

	void Name::read(MA_PIM_ARGS& args)
	{
		printf("@LIB: name read");
		args.field = MA_PIM_FIELD_CONTACT_NAME;
		//CHECK_RESULT(maPimItemGetValue(&args, 0));
		if (maPimItemGetValue(&args, 0) > 0)
		{
			readDisplayName(args.buf);
			readFirstName(args.buf);
			readMiddleName(args.buf);
			readLastName(args.buf);
			readPrefix(args.buf);
			readSuffix(args.buf);
			readPhoneticFirstName(args.buf);
			readPhoneticMiddleName(args.buf);
			readPhoneticLastName(args.buf);
		}

		args.field = MA_PIM_FIELD_CONTACT_NICKNAME;
		//CHECK_RESULT(maPimItemGetValue(&args, 0));
		if (maPimItemGetValue(&args, 0) >=0 )
		{
			readNickname(args.buf);
		}
	}

	void Name::readDisplayName(MAAddress const buffer)
	{
		mDisplayName = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_NAME_DISPLAY);
	}

	void Name::readFirstName(MAAddress const buffer)
	{
		mFirstName = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_NAME_GIVEN);
	}

	void Name::readMiddleName(MAAddress const buffer)
	{
		mMiddleName = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_NAME_OTHER);
	}

	void Name::readLastName(MAAddress const buffer)
	{
		mLastName = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_NAME_FAMILY);
	}

	void Name::readNickname(MAAddress const buffer)
	{
		DELETE(mNickname);
		wchar* src = (wchar*)buffer;
		int len = wcslen(src);
		mNickname = new wchar[len + 1];
		wcsncpy(mNickname, src, len);
	}

	void Name::readPrefix(MAAddress const buffer)
	{
		mPrefix = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_NAME_PREFIX);
	}

	void Name::readSuffix(MAAddress const buffer)
	{
		mSuffix = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_NAME_SUFFIX);
	}

	void Name::readPhoneticFirstName(MAAddress const buffer)
	{
		mPhoneticFirstName = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_NAME_PHONETIC_GIVEN);
	}

	void Name::readPhoneticMiddleName(MAAddress const buffer)
	{
		mPhoneticMiddleName = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_NAME_PHONETIC_OTHER);
	}

	void Name::readPhoneticLastName(MAAddress const buffer)
	{
		mPhoneticLastName = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_NAME_PHONETIC_FAMILY);
	}

	/*
	 * Getter for display name.
	 */
	const wchar* Name::getDisplayName() const
	{
		return mDisplayName;
	}

	/*
	 * Setter for display name.
	 */
	void Name::setDisplayName(wchar* const displayName)
	{
		mDisplayName = displayName;
	}

	/*
	 * Getter for first name.
	 */
	const wchar* Name::getFirstName() const
	{
		return mFirstName;
	}

	/*
	 * Setter for first name.
	 */
	void Name::setFirstName(wchar* const firstName)
	{
		mFirstName = firstName;
	}

	/*
	 * Getter for middle name.
	 */
	const wchar* Name::getMiddleName() const
	{
		return mMiddleName;
	}

	/*
	 * Setter for middle name.
	 */
	void Name::setMiddleName(wchar* const middleName)
	{
		mMiddleName = middleName;
	}

	/*
	 * Getter for last name.
	 */
	const wchar* Name::getLastName() const
	{
		return mLastName;
	}

	/*
	 * Setter for last name.
	 */
	void Name::setLastName(wchar* const lastName)
	{
		mLastName = lastName;
	}

	/*
	 * Getter for nickname.
	 */
	const wchar* Name::getNickname() const
	{
		return mNickname;
	}

	/*
	 * Setter for nickname.
	 */
	void Name::setNickname(wchar* const nickname)
	{
		mNickname = nickname;
	}

	/*
	 * Getter for prefix.
	 */
	const wchar* Name::getPrefix() const
	{
		return mPrefix;
	}

	/*
	 * Setter for prefix.
	 */
	void Name::setPrefix(wchar* const prefix)
	{
		mPrefix = prefix;
	}

	/*
	 * Getter for suffix.
	 */
	const wchar* Name::getSuffix() const
	{
		return mSuffix;
	}

	/*
	 * Setter for suffix.
	 */
	void Name::setSuffix(wchar* const suffix)
	{
		mSuffix = suffix;
	}

	/*
	 * Getter for phonetic first name.
	 */
	const wchar* Name::getPhoneticFirstName() const
	{
		return mPhoneticFirstName;
	}

	/*
	 * Setter for phonetic first name.
	 */
	void Name::setPhoneticFirstName(wchar* const phoneticFirstName)
	{
		mPhoneticFirstName = phoneticFirstName;
	}

	/*
	 * Getter for phonetic middle name.
	 */
	const wchar* Name::getPhoneticMiddleName() const
	{
		return mPhoneticMiddleName;
	}

	/*
	 * Setter for phonetic middle name.
	 */
	void Name::setPhoneticMiddleName(wchar* const phoneticMiddleName)
	{
		mPhoneticMiddleName = phoneticMiddleName;
	}

	/*
	 * Getter for phonetic last name.
	 */
	const wchar* Name::getPhoneticLastName() const
	{
		return mPhoneticLastName;
	}

	/*
	 * Setter for phonetic last name.
	 */
	void Name::setPhoneticLastName(wchar* const phoneticLastName)
	{
		mPhoneticLastName = phoneticLastName;
	}
}

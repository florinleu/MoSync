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

	bool Name::read(MA_PIM_ARGS& args)
	{
		printf("@LIB: name read");
		bool isSupported = false;

		args.field = MA_PIM_FIELD_CONTACT_NAME;
		args.bufSize = PIM_BUF_SIZE;
		if (maPimItemGetValue(&args, 0) > 0)
		{
			isSupported = true;
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
		args.bufSize = PIM_BUF_SIZE;
		if (maPimItemGetValue(&args, 0) >=0 )
		{
			isSupported = true;
			readNickname(args.buf);
		}

		args.field = MA_PIM_FIELD_CONTACT_FORMATTED_NAME;
		args.bufSize = PIM_BUF_SIZE;
		if (maPimItemGetValue(&args, 0) >=0)
		{
			isSupported = true;
			readFormattedName(args.buf);
		}

		return isSupported;
	}

	void Name::readDisplayName(const MAAddress buffer)
	{
		mDisplayName = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_NAME_DISPLAY);
	}

	void Name::readFirstName(const MAAddress buffer)
	{
		mFirstName = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_NAME_GIVEN);
	}

	void Name::readMiddleName(const MAAddress buffer)
	{
		mMiddleName = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_NAME_OTHER);
	}

	void Name::readLastName(const MAAddress buffer)
	{
		mLastName = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_NAME_FAMILY);
	}

	void Name::readNickname(const MAAddress buffer)
	{
		wchar* src = (wchar*)buffer;
		mNickname = wcsdup(src);
	}

	void Name::readPrefix(const MAAddress buffer)
	{
		mPrefix = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_NAME_PREFIX);
	}

	void Name::readSuffix(const MAAddress buffer)
	{
		mSuffix = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_NAME_SUFFIX);
	}

	void Name::readPhoneticFirstName(const MAAddress buffer)
	{
		mPhoneticFirstName = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_NAME_PHONETIC_GIVEN);
	}

	void Name::readPhoneticMiddleName(const MAAddress buffer)
	{
		mPhoneticMiddleName = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_NAME_PHONETIC_OTHER);
	}

	void Name::readPhoneticLastName(const MAAddress buffer)
	{
		mPhoneticLastName = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_NAME_PHONETIC_FAMILY);
	}

	void Name::readFormattedName(const MAAddress buffer)
	{
		wchar* src = (wchar*)buffer;
		mFormattedName = wcsdup(src);
	}

	void Name::write(MA_PIM_ARGS& args)
	{
		printf("@LIB: name write");

		args.field = MA_PIM_FIELD_CONTACT_NAME;
		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeInt(args.buf, 9, 0); //fleu TODO magic number
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

	/*
	 * Getter for display name.
	 */
	const wchar* const Name::getDisplayName() const
	{
		return mDisplayName;
	}

	/*
	 * Setter for display name.
	 */
	void Name::setDisplayName(const wchar* const displayName)
	{
		DELETE(mDisplayName);
		mDisplayName = wcsdup(displayName);
	}

	/*
	 * Getter for first name.
	 */
	const wchar* const Name::getFirstName() const
	{
		return mFirstName;
	}

	/*
	 * Setter for first name.
	 */
	void Name::setFirstName(const wchar* const firstName)
	{
		DELETE(mFirstName);
		mFirstName = wcsdup(firstName);
	}

	/*
	 * Getter for middle name.
	 */
	const wchar* const Name::getMiddleName() const
	{
		return mMiddleName;
	}

	/*
	 * Setter for middle name.
	 */
	void Name::setMiddleName(const wchar* const middleName)
	{
		DELETE(mFirstName);
		mMiddleName = wcsdup(middleName);
	}

	/*
	 * Getter for last name.
	 */
	const wchar* const Name::getLastName() const
	{
		return mLastName;
	}

	/*
	 * Setter for last name.
	 */
	void Name::setLastName(const wchar* const lastName)
	{
		DELETE(mFirstName);
		mLastName = wcsdup(lastName);
	}

	/*
	 * Getter for nickname.
	 */
	const wchar* const Name::getNickname() const
	{
		return mNickname;
	}

	/*
	 * Setter for nickname.
	 */
	void Name::setNickname(const wchar* const nickname)
	{
		DELETE(mFirstName);
		mNickname = wcsdup(nickname);
	}

	/*
	 * Getter for prefix.
	 */
	const wchar* const Name::getPrefix() const
	{
		return mPrefix;
	}

	/*
	 * Setter for prefix.
	 */
	void Name::setPrefix(const wchar* const prefix)
	{
		DELETE(mFirstName);
		mPrefix = wcsdup(prefix);
	}

	/*
	 * Getter for suffix.
	 */
	const wchar* const Name::getSuffix() const
	{
		return mSuffix;
	}

	/*
	 * Setter for suffix.
	 */
	void Name::setSuffix(const wchar* const suffix)
	{
		DELETE(mFirstName);
		mSuffix = wcsdup(suffix);
	}

	/*
	 * Getter for phonetic first name.
	 */
	const wchar* const Name::getPhoneticFirstName() const
	{
		return mPhoneticFirstName;
	}

	/*
	 * Setter for phonetic first name.
	 */
	void Name::setPhoneticFirstName(const wchar* const phoneticFirstName)
	{
		DELETE(mFirstName);
		mPhoneticFirstName = wcsdup(phoneticFirstName);
	}

	/*
	 * Getter for phonetic middle name.
	 */
	const wchar* const Name::getPhoneticMiddleName() const
	{
		return mPhoneticMiddleName;
	}

	/*
	 * Setter for phonetic middle name.
	 */
	void Name::setPhoneticMiddleName(const wchar* const phoneticMiddleName)
	{
		DELETE(mFirstName);
		mPhoneticMiddleName = wcsdup(phoneticMiddleName);
	}

	/*
	 * Getter for phonetic last name.
	 */
	const wchar* const Name::getPhoneticLastName() const
	{
		return mPhoneticLastName;
	}

	/*
	 * Setter for phonetic last name.
	 */
	void Name::setPhoneticLastName(const wchar* const phoneticLastName)
	{
		DELETE(mFirstName);
		mPhoneticLastName = wcsdup(phoneticLastName);
	}

	/*
	 * Getter for formatted name.
	 */
	const wchar* const Name::getFormattedName() const
	{
		return mFormattedName;
	}
}

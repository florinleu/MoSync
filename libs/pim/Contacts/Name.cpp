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

#include "Name.h"
#include "util.h"

namespace PIM
{

	void Name::read(MA_PIM_ARGS& mArgs)
	{
		mArgs.field = MA_PIM_FIELD_CONTACT_NAME;
		CHECK_RESULT(maPimItemGetValue(&mArgs, 0));

		readDisplayName(mArgs.buf);
		readFirstName(mArgs.buf);
		readMiddleName(mArgs.buf);
		readLastName(mArgs.buf);
		readPrefix(mArgs.buf);
		readSuffix(mArgs.buf);
		readPhoneticFirstName(mArgs.buf);
		readPhoneticMiddleName(mArgs.buf);
		readPhoneticLastName(mArgs.buf);

		mArgs.field = MA_PIM_FIELD_CONTACT_NICKNAME;
		CHECK_RESULT(maPimItemGetValue(&mArgs, 0));
		readNickname(mArgs.buf);
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
		wcsncpy(mNickname, (wchar*)buffer, wcslen((wchar*)buffer));
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
}

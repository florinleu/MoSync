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
 * @file ID.cpp
 * @author Florin Leu
 * @date 09 Feb 2011
 *
 * @brief PIM Field ID class.
 *
 **/

#include <conprint.h>
#include <mawstring.h>
#include "ID.h"

namespace PIM
{
	void ID::read(MA_PIM_ARGS& args)
	{
		printf("@LIB: ID read");
		args.field = MA_PIM_FIELD_CONTACT_UID;
		//CHECK_RESULT(maPimItemGetValue(&mArgs, 0));
		if (maPimItemGetValue(&args, 0))
		{
			readID(args.buf);
		}
	}

	void ID::readID(MAAddress const buffer)
	{
		wchar* src = (wchar*)buffer;
		int len = wcslen(src);
		mID = new wchar[len];
		wcsncpy(mID, src, len);
	}

	const wchar* ID::getID() const
	{
		return mID;
	}

} //PIM

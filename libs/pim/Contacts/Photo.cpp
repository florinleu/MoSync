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
 * @file Photo.cpp
 * @author Florin Leu
 * @date 23 Feb 2011
 *
 * @brief PIM Field Photo class.
 *
 **/

#include <conprint.h>
#include <mawstring.h>
#include <mastdlib.h>

#include "Photo.h"
#include "util.h"

namespace PIM
{

	void Photo::read(MA_PIM_ARGS& args)
	{
		printf("@LIB: photo read");
		args.field = MA_PIM_FIELD_CONTACT_PHOTO;
		//CHECK_RESULT(maPimItemGetValue(&args, 0));
		if (maPimItemGetValue(&args, 0) > 0)
		{
			readHandle(args.buf);
		}
	}

	void Photo::readHandle(MAAddress const buffer)
	{
		wchar* src = (wchar*)buffer;
		mHandle = atoi(wstrtostr(src));
	}

	/*
	 * Getter for photo handle.
	 */
	const MAHandle& Photo::getHandle() const
	{
		return mHandle;
	}

	/*
	 * Setter for photo handle.
	 */
	void Photo::setHandle(const MAHandle& handle)
	{
		mHandle = handle;
	}

	/*
	 * Setter for photo URL.
	 */
	void Photo::setURL(wchar* const url)
	{
		mURL = url;
	}

} //PIM

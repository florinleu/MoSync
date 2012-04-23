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
#include "util.h"

namespace PIM
{
	/**
	 * Destructor.
	 */
	ID::~ID()
	{
		DELETE(mID);
	}

	/**
	 * Reads the id.
	 * @param args The arguments needed to read the id.
	 * @return true on success.
	 */
	bool ID::read(MA_PIM_ARGS& args)
	{
		printf("@LIB: ID read");
		args.field = MA_PIM_FIELD_CONTACT_UID;
		args.bufSize = PIM_BUF_SIZE;
		CHECK_RESULT(maPimItemGetValue(&args, 0));

		readData(args.buf);

		return true;
	}

	/**
	 * Reads the id data.
	 * @param buffer The buffer to read from.
	 */
	void ID::readData(const MAAddress buffer)
	{
		wchar* src = (wchar*)buffer;
		mID = wcsdup(src);
	}

	/**
	 * Gets the contact's id.
	 * @return The ID for the contact.
	 */
	const wchar* const ID::getID() const
	{
		return mID;
	}

	/**
	 * Sets the contact's id.
	 * @param id The value to set.
	 */
	void ID::setID(const wchar* const id)
	{
		DELETE(mID);
		mID = wcsdup(id);
	}
} //PIM

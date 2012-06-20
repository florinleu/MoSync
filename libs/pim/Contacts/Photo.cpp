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

#include <mawstring.h>
#include <conprint.h>

#include "Photo.h"
#include "util.h"

namespace PIM
{
	/**
	 * Constructor.
	 */
	Photo::Photo():
		mHandle(-1),
		mURL(NULL)
	{
	}

	/**
	 * Destructor.
	 */
	Photo::~Photo()
	{
		DELETE(mURL);
	}

	/**
	 * Reads the contact's photo.
	 * @param args The arguments needed to read the photo.
	 * @return true on success.
	 */
	bool Photo::read(MA_PIM_ARGS& args)
	{
		printf("@LIB: photo read");
		args.field = MA_PIM_FIELD_CONTACT_PHOTO;
		args.bufSize = PIM_BUF_SIZE;
		CHECK_RESULT(maPimItemGetValue(&args, 0));
		mHandle = *(int*)args.buf;

		return true;
	}

	/**
	 * Writes the contact's photo.
	 * @param args The values to write.
	 */
	void Photo::write(MA_PIM_ARGS& args)
	{
		printf("@LIB: photo write");

		args.field = MA_PIM_FIELD_CONTACT_PHOTO;
		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeInt(args.buf, mHandle, 0);
		maPimItemSetValue(&args, 0, 0);

	}

	/**
	 * Deletes a contact's photo.
	 * @param handle The handle of the contact.
	 */
	void Photo::remove(MAHandle handle)
	{
		printf("@LIB: note delete");

		maPimItemRemoveValue(handle, MA_PIM_FIELD_CONTACT_PHOTO, 0);
	}

	/**
	 * Gets the contact's photo handle.
	 * @return The photo handle of the contact.
	 */
	const MAHandle& Photo::getHandle() const
	{
		return mHandle;
	}

	/**
	 * Sets the contact's photo handle.
	 * @param handle The value to set.
	 */
	void Photo::setHandle(const MAHandle& handle)
	{
		mHandle = handle;
	}

	/**
	 * Sets the contact's photo url.
	 * @param url The value to set.
	 */
	void Photo::setURL(const wchar* const url)
	{
		DELETE(mURL);
		mURL = wcsdup(url);
	}

} //PIM

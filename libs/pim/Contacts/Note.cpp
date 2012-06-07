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
 * @file Note.cpp
 * @author Florin Leu
 * @date 27 Feb 2011
 *
 * @brief PIM Field Note class.
 *
 **/

#include <mawstring.h>
#include <conprint.h>

#include "Note.h"
#include "util.h"

namespace PIM
{
	/**
	 * Constructor.
	 */
	Note::Note():
		mText(NULL)
	{
	}

	/**
	 * Destructor.
	 */
	Note::~Note()
	{
		DELETE(mText);
	}

	/**
	 * Reads the contact's name.
	 * @param args The arguments needed to read the name.
	 * @return true on success.
	 */
	bool Note::read(MA_PIM_ARGS& args)
	{
		printf("@LIB: note read");
		args.field = MA_PIM_FIELD_CONTACT_NOTE;
		args.bufSize = PIM_BUF_SIZE;
		CHECK_RESULT(maPimItemGetValue(&args, 0));

		wchar* src = (wchar*)args.buf;
		mText = wcsdup(src);

		return true;
	}

	/**
	 * Writes the contact's note.
	 * @param args The values to write.
	 */
	void Note::write(MA_PIM_ARGS& args)
	{
		printf("@LIB: note write");

		args.field = MA_PIM_FIELD_CONTACT_NOTE;
		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeWString(args.buf, mText, 0);
		maPimItemSetValue(&args, 0, 0);

	}

	/**
	 * Deletes a contact's name.
	 * @param handle The handle of the contact.
	 */
	void Note::remove(MAHandle handle)
	{
		printf("@LIB: note delete");

		maPimItemRemoveValue(handle, MA_PIM_FIELD_CONTACT_NOTE, 0);
	}

	/**
	 * Gets the contact's note text.
	 * @return The note text of the contact.
	 */
	const wchar* const Note::getText() const
	{
		return mText;
	}

	/**
	 * Sets the contact's note text.
	 * @param text The value to set.
	 */
	void Note::setText(const wchar* const text)
	{
		DELETE(mText);
		mText = wcsdup(text);
	}

} //PIM

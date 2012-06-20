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
	 * Reads a contact's note.
	 * @param args The arguments needed to read the note.
	 * @param index The index of the note to read.
	 */
	void Note::read(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: note read");
		args.field = MA_PIM_FIELD_CONTACT_NOTE;
		args.bufSize = PIM_BUF_SIZE;
		if (maPimItemGetValue(&args, index) >= 0)
		{
			wchar* src = (wchar*)args.buf;
			mText = wcsdup(src);

		}
	}

	/**
	 * Writes a contact's note.
	 * @param args The values to write.
	 * @index args The index of the note to write.
	 */
	void Note::write(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: note write");

		args.field = MA_PIM_FIELD_CONTACT_NOTE;
		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeWString(args.buf, mText, 0);
		maPimItemSetValue(&args, index, 0);

	}

	/**
	 * Adds a new note to this contact.
	 */
	void Note::add(MA_PIM_ARGS& args)
	{
		args.field = MA_PIM_FIELD_CONTACT_NOTE;
		maPimItemAddValue(&args, 0);
	}

	/**
	 * Deletes a contact's note.
	 * @param handle The handle of the contact.
	 * @param index  The index of the note to delete.
	 */
	void Note::remove(MAHandle handle, int index)
	{
		printf("@LIB: note delete");

		maPimItemRemoveValue(handle, MA_PIM_FIELD_CONTACT_NOTE, index);
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

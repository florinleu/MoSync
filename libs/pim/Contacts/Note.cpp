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

	bool Note::read(MA_PIM_ARGS& args)
	{
		printf("@LIB: note read");
		args.field = MA_PIM_FIELD_CONTACT_NOTE;
		args.bufSize = BUF_SIZE;
		CHECK_RESULT(maPimItemGetValue(&args, 0));

		readText(args.buf);

		return true;
	}

	void Note::readText(const MAAddress buffer)
	{
		DELETE(mText);
		wchar* src = (wchar*)buffer;
		int len = wcslen(src);
		mText = new wchar[len + 1];
		wcsncpy(mText, src, len);
	}

	/*
	 * Getter for text.
	 */
	const wchar* Note::getText() const
	{
		return mText;
	}

	/*
	 * Setter for text.
	 */
	void Note::setText(wchar* text)
	{
		mText = text;
	}

} //PIM

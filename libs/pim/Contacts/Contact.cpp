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
 * @file Contact.cpp
 * @author Florin Leu
 * @date 08 Feb 2011
 *
 * @brief PIM Contact class.
 *
 **/

#include "Contact.h"
#include "IX_PIM.h"
#include "util.h"

namespace PIM
{
	/*
	 * Constructor.
	 */
	Contact::Contact(MAHandle contactHandle):
			mHandle(contactHandle)
	{
	}

	/*
	 * Destructor.
	 */
	Contact::~Contact()
	{
		DELETE(mBuffer);
	}

	/*
	 * Read the Contact.
	 */
	int Contact::read()
	{
		MA_PIM_ARGS args;
		args.item = mHandle;
		mBuffer = new char[BUF_SIZE];
		args.buf = mBuffer;
		args.bufSize = BUF_SIZE;
		mName.read(args);
		return 0;
	}
}

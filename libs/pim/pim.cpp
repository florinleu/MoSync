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
 * @file pim.cpp
 * @author Florin Leu
 * @date 08 Feb 2011
 **/

#include "pim.h"
#include "util.h"
#include "Contacts/Contact.h"
#include "IX_PIM.h"

MAHandle gContactsList;

void initContacts()
{
	gContactsList = maPimListOpen(MA_PIM_CONTACTS, 0);
}

PIM::Contact readContact()
{
	//Get the contacts item handle.
	int contactHandle = maPimListNext(gContactsList);

	// Check if the new contact handle is valid.
	CHECK_RESULT(contactHandle);

	PIM::Contact c(contactHandle);
	c.read();
	return c;
}

void cleanContacts()
{
	maPimListClose(gContactsList);
}

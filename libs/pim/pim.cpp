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

#include <conprint.h>

MAHandle gContactsList = 0;

/**
 * Opens the contacts list.
 * @return true if succeeded.
 */
bool initContacts()
{
	printf("initContacts");
	if (gContactsList != 0)
	{
		closeContacts();
	}
	gContactsList = maPimListOpen(MA_PIM_CONTACTS, 0);
	if (gContactsList == MA_PIM_ERR_LIST_UNAVAILABLE)
	{
		gContactsList = 0;
		return false;
	}
	return true;
}

MAHandle getListHandle()
{
	return gContactsList;
}

void closeContacts()
{
	printf("closeContacts");
	maPimListClose(gContactsList);
	gContactsList = 0;
}

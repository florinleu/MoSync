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
 * @file EditDefines.h
 * @author Florin Leu
 * @date 14 Mar 2011
 **/

#ifndef __EDITDEFINES_H__
#define __EDITDEFINES_H__

#include"Utils.h"

#define TXT_EDIT_ID_TITLE				"ID"
#define TXT_EDIT_NAME_TITLE				"Name"
#define TXT_EDIT_ADDRESS_TITLE			"Addresses"
#define TXT_EDIT_PHONE_TITLE			"Phones"
#define TXT_EDIT_EMAIL_TITLE			"Emails"
#define TXT_EDIT_WEBSITE_TITLE			"Websites"
#define TXT_EDIT_IM_TITLE				"Instant messagings"
#define TXT_EDIT_NOTE_TITLE				"Note"
#define TXT_EDIT_ORGANIZATION_TITLE		"Organization"
#define TXT_EDIT_SP_TITLE				"Social Profile"
#define TXT_EDIT_EVENT_TITLE			"Event"
#define TXT_EDIT_RELATION_TITLE			"Relation"

#define EDIT_TITLE_COLOR 				0xFFFFFF
//#define EDIT_TITLE_SPECIAL_COLOR 		0xFF777A
#define EDIT_TITLE_TEXT_COLOR 			0x00000
#define EDIT_LABEL_COLOR 				0x222222
#define EDIT_DATA_COLOR 				0x333333
#define EDIT_SPACER_COLOR 				0x000000
//#define EDIT_LOADING_COLOR 				0x000000
//#define EDIT_LOADING_ALPHA 				(0.8)
#define EDIT_LABEL_WIDTH				(PIMMoblet::sScreenWidth / 4)
#define EDIT_IMAGE_WIDTH				(PIMMoblet::sScreenWidth / 3)

#define EDIT_ID_FLAGS					0x0
#define EDIT_NAME_FLAGS					0x3FE
#define EDIT_ADDRESS_FLAGS				0x7F
#define EDIT_PHONE_FLAGS				0x1
#define EDIT_EMAIL_FLAGS				0x1

#endif //__EDITDEFINES_H__

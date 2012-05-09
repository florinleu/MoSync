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
 * @file Utils.h
 * @author Florin Leu
 * @date 16 Feb 2011
 **/

#ifndef __UTILS_H__
#define __UTILS_H__

#include <MAP/MemoryMgr.h>
#include <Contacts/Contact.h>
#include "PIMMoblet.h"

//Usefull stuff
#define BUFF_SIZE					255

#define DELETE(a)					{deleteobject(a);}
#define DELETE_ARRAY(a,size)		{if(a != NULL){for(int i=0; i<size; i++) deleteobject(a[i]);delete (a);a=NULL;}}

#define SCREEN_WIDTH				(PIMMoblet::sScreenWidth)
#define SCREEN_HEIGHT				(PIMMoblet::sScreenHeight)

//Contacts List
#define TXT_NO_NAME					"No Name"

//Contact Edit Screen
//#define TITLE_COLOR 				0xFFFFFF
//#define TITLE_SPECIAL_COLOR 		0xFF777A
//#define TITLE_TEXT_COLOR 			0x00000
//#define LABEL_COLOR 				0x222222
//#define LABEL_COLOR 				0x222222
//#define DATA_COLOR 					0x333333
//#define SPACER_COLOR 				0x000000
#define LOADING_COLOR 				0x000000
#define LOADING_ALPHA 				(0.8)
//#define LABEL_WIDTH					(PIMMoblet::sScreenWidth / 3)
//#define IMAGE_WIDTH					(PIMMoblet::sScreenWidth / 3)

//flags
//#define NAME_FLAGS					0x3FE
//#define ADDRESS_FLAGS				0x7F

//char* wstrtostr(const wchar* wstr);

#endif //__UTILS_H__

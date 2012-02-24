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
 * @file util.h
 * @author Florin Leu
 * @date 08 Feb 2011
 **/

#ifndef __UTIL_H__
#define __UTIL_H__

#include <MAP/MemoryMgr.h>

#define CHECK_RESULT(a)

#define DELETE(a)					{deleteobject(a);}
#define DELETE_ARRAY(a,size)		{if(a != NULL){for(int i=0; i<size; i++) deleteobject(a[i]);delete (a);a=NULL;}}

#define BUF_SIZE					512 //we have a limit of 256 widechars

/**
 * Get a wchar array from a specified buffer.
 * @param buffer Contains n wchar-arrays, where n is the int value that can
 * be read from buffer address.
 * @param arrayIndex The index of the array.
 * @return A pointer to the wchar array if the arrayIndex is valid, or
 * NULL otherwise.
 */
wchar* getWCharArrayFromBuf(MAAddress const buffer, const int arrayIndex);

char* wstrtostr(const wchar* wstr);

#endif //__UTIL_H__

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
 * @file util.cpp
 * @author Florin Leu
 * @date 08 Feb 2011
 **/

#ifndef __UTIL_H__
#define __UTIL_H__

#include <ma.h>
#include <mawstring.h>
#include <MAP/MemoryMgr.h>
#include <wchar.h>

#include <conprint.h>

/**
 * Get a wchar array from a specified buffer.
 * @param buffer Contains n wchar-arrays, where n is the int value that can
 * be read from buffer address.
 * @param arrayIndex The index of the array.
 * @return A pointer to the wchar array if the arrayIndex is valid, or
 * NULL otherwise.
 */
wchar* getWCharArrayFromBuf(MAAddress const buffer, const int arrayIndex)
{
	int totalArrays = *(int*) buffer;
	char* charBuffer = (char*) buffer;
	wchar* ptr = (wchar*) (charBuffer + sizeof(int));
	int currentArrayIndex = 0;
	while ( (currentArrayIndex < totalArrays) && (currentArrayIndex != arrayIndex) )
	{
		int stringLength = wcslen(ptr) + 1;
		ptr += stringLength;
		currentArrayIndex++;
	}

	if (currentArrayIndex == arrayIndex)
	{
//		wchar* str = new wchar[wcslen(ptr) + 1];
//		wcsncpy(str, ptr, wcslen(ptr));
//		return str;
		return wcsdup(ptr);
	}
	else
	{
		return NULL;
	}
}

char* wstrtostr(const wchar* wstr)
{
	if (wstr == NULL)
	{
		return NULL;
	}
	int len = wcslen(wstr);
	char* str = new char[len + 1];
	wcstombs(str, wstr, len + 1);
	str[len] = 0;
	return str;
}

#endif //__UTIL_H__

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
	wcstombs(str, wstr, len);
	str[len] = 0;
	return str;
}

wchar* strtowstr(const char* str)
{
	if (str == NULL)
	{
		return NULL;
	}
	int len = strlen(str);
	wchar* wstr = new wchar[len + 1];
	memset(wstr, 0, (len + 1)*sizeof(wchar));
	mbstowcs(wstr, str, len + 1);
	return wstr;
}

wchar* readSubField(const MAAddress buffer, int arrayIndex) //fleu TODO
{
	return NULL;
}

int writeInt(MAAddress bufferDest, int val, int bufDestSize)
{
	*(int*)(((char*)bufferDest) + bufDestSize) = val;
	return sizeof(int);
}

int writeWString(MAAddress buffer, wchar* str, int bufDestSize)
{
	wchar* dst = (wchar*)buffer;
	dst += (bufDestSize / sizeof(wchar));
	const wchar* src = NULL;
	src = (str != NULL)?str:L"";
	int size = (wcslen(src) + 1) * sizeof (wchar);

	do
	{
		*dst = *src;
		dst++;
	}
	while (*(src++) != 0);

	return size;
}

#endif //__UTIL_H__

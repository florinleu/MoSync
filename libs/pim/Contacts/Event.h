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
 * @file Event.h
 * @author Florin Leu
 * @date 09 Feb 2011
 *
 * @brief PIM Field Event class.
 *
 **/

#ifndef __EVENT_H__
#define __EVENT_H__

namespace PIM
{

	enum eEventTypes
	{
		//The constant describes a birthday event.
		EVENT_BIRTHDAY = 0,
		//The constant describes an anniversary event.
		EVENT_ANNIVERSARY,
		//The constant describes a different event type.
		EVENT_OTHER,
		//The constant describes a custom event type.
		//The field's label can be set.
		EVENT_CUSTOM,
	};

	class Event
	{
		private:
			//The event start date.
			wchar* mDate;

			//The type of data.
			eAddressTypes mType;
			//The user defined label
			wchar* mLabel;
	};

} //PIM

#endif //__ADDRESS_H__

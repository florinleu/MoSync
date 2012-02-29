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

#include <matime.h>
#include <IX_PIM.h>

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
		public:
			Event();

			void read(MA_PIM_ARGS& args, int index);

			const time_t& getDate() const;
			void setDate(const time_t& date);

			const eEventTypes& getType() const;
			void setType(const eEventTypes& type);

			const wchar* getLabel() const;
			void setLabel(wchar* const label);

			const bool isPrimary() const;

		private:
			void readDate(MAAddress const buffer);

			void readType(const MAHandle handle, const int index);
			void readLabel(const MAHandle handle, const int index);

		private:
			//The event start date.
			int mDate;

			//The type of data.
			eEventTypes mType;
			//The user defined label
			wchar* mLabel;
			//Shows if this is a primary phone number or not.
			bool mIsPrimary;
	};

} //PIM

#endif //__ADDRESS_H__

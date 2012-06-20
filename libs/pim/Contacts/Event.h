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
	class Event
	{

		public:
			enum eTypes
			{
				//The constant describes a birthday event.
				TYPE_BIRTHDAY = 0,
				//The constant describes an anniversary event.
				TYPE_ANNIVERSARY,
				//The constant describes a different event type.
				TYPE_OTHER,
				//The constant describes a custom event type.
				//The field's label can be set.
				TYPE_CUSTOM,
			};

			enum eSubFields
			{
				//The constant describes a date.
				DATE = 0,
			};

		public:
			/**
			 * Constructor.
			 */
			Event();

			/**
			 * Destructor.
			 */
			~Event();

			/**
			 * Reads a contact's event.
			 * @param args The arguments needed to read the event.
			 * @param index The index of the event to read.
			 */
			void read(MA_PIM_ARGS& args, int index);

			/**
			 * Writes a contact's event.
			 * @param args The values to write.
			 * @index args The index of the event to write.
			 */
			void write(MA_PIM_ARGS& args, int index);

			/**
			 * Adds a new event to this contact.
			 * @param args The values to add.
			 */
			void add(MA_PIM_ARGS& args);

			/**
			 * Deletes a contact's event.
			 * @param handle The handle of the contact.
			 * @param index  The index of the event to delete.
			 */
			void remove(MAHandle handle, int index);

			/**
			 * Gets the contact's event date.
			 * @return The date of the contact.
			 */
			const time_t& getDate() const;

			/**
			 * Sets the contact's event date.
			 * @param date The value to set.
			 */
			void setDate(const time_t& date);

			/**
			 * Gets the event type.
			 * @return The type of the event.
			 */
			const eTypes& getType() const;

			/**
			 * Sets the event type.
			 * @param type The value to set.
			 */
			void setType(const eTypes& type);

			/**
			 * Gets the event label.
			 * @return The label of the event.
			 */
			const wchar* const getLabel() const;

			/**
			 * Sets the event label.
			 * @param state The value to set.
			 */
			void setLabel(const wchar* const label);

			/**
			 * Checks if this is or not a primary event.
			 * @return True if this is a primary event.
			 */
			const bool isPrimary() const;

			/**
			 * Sets this as a primary event.
			 * @param primary true if this is a primary event.
			 */
			void setPrimary(const bool primary);

		private:
			/**
			 * Reads the type of the event.
			 * @param handle The handle of the contact.
			 * @param index The index of this event.
			 */
			void readType(const MAHandle handle, const int index);

			/**
			 * Reads the label of the event.
			 * @param handle The handle of the contact.
			 * @param index The index of this event.
			 */
			void readLabel(const MAHandle handle, const int index);

			/**
			 * Computes the event attribute.
			 * @return The event attribute.
			 */
			const int getAttribute() const;

		private:
			//The event start date.
			int mDate;

			//The type of data.
			eTypes mType;
			//The user defined label
			wchar* mLabel;
			//Shows if this is a primary phone number or not.
			bool mIsPrimary;
	};

} //PIM

#endif //__EVENT_H__

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
 * @file Phone.h
 * @author Florin Leu
 * @date 09 Feb 2011
 *
 * @brief PIM Field Phone class.
 *
 **/

#ifndef __PHONE_H__
#define __PHONE_H__

#include <IX_PIM.h>

namespace PIM
{
	class Phone
	{
		public:
			enum eTypes
			{
				//The constant describes a home phone number.
				HOME = 0,
				//The constant describes a mobile phone number.
				MOBILE,
				//The constant describes a home fax phone number.
				HOME_FAX,
				//The constant describes a work fax phone number.
				WORK_FAX,
				//The constant describes a pager phone number.
				PAGER,
				//The constant describes an iPhone phone number.
				IPHONE,
				//The constant describes a work phone number.
				WORK,
				//The constant describes a callback phone number.
				CALLBACK,
				//The constant describes a car phone number.
				CAR,
				//The constant describes a company main phone number.
				COMPANY_MAIN,
				//The constant describes a ISDN phone number.
				ISDN,
				//The constant describes a other fax type phone number.
				OTHER_FAX,
				//The constant describes a radio phone number.
				RADIO,
				//The constant describes a telex phone number.
				TELEX,
				//The constant describes a TTY TDD phone number.
				TTY_TDD,
				//The constant describes a work mobile phone number.
				WORK_MOBILE,
				//The constant describes a work pager phone number.
				WORK_PAGER,
				//The constant describes an assistant phone number.
				ASSISTANT,
				//The constant describes a MMS phone number.
				MMS,
				//The constant describes a different phone number type.
				OTHER,
				//The constant describes a custom phone number type.
				//The field's label can be set.
				CUSTOM,
			};

			enum eSubFields
			{
				//The constant describes a phone number.
				NUMBER = 0,
			};

			/**
			 * Constructor.
			 */
			Phone();

			/**
			 * Destructor.
			 */
			~Phone();

			/**
			 * Reads a contact's phone.
			 * @param args The arguments needed to read the phone.
			 * @param index The index of the phone to read.
			 */
			void read(MA_PIM_ARGS& args, int index);

			/**
			 * Writes a contact's phone.
			 * @param args The values to write.
			 * @index args The index of the phone to write.
			 */
			void write(MA_PIM_ARGS& args, int index);

			/**
			 * Gets the contact's phone number.
			 * @return The number of the contact.
			 */
			const wchar* const getNumber() const;

			/**
			 * Sets the contact's phone number.
			 * @param number The value to set.
			 */
			void setNumber(const wchar* const number);

			/**
			 * Gets the phone type.
			 * @return The type of the phone.
			 */
			const eTypes& getType() const;

			/**
			 * Sets the phone type.
			 * @param type The value to set.
			 */
			void setType(const eTypes& type);

			/**
			 * Gets the phone label.
			 * @return The label of the phone.
			 */
			const wchar* const getLabel() const;

			/**
			 * Sets the phone label.
			 * @param state The value to set.
			 */
			void setLabel(const wchar* const label);

			/**
			 * Checks if this is or not a primary phone.
			 * @return True if this is a primary phone.
			 */
			const bool isPrimary() const;

			/**
			 * Sets this as a primary phone.
			 * @param primary true if this is a primary phone.
			 */
			void setPrimary(const bool primary);

		private:
			/**
			 * Reads the type of the phone.
			 * @param handle The handle of the phone.
			 * @param index The index of this phone.
			 */
			void readType(const MAHandle handle, const int index);

			/**
			 * Reads the label of the phone.
			 * @param handle The handle of the contact.
			 * @param index The index of this phone.
			 */
			void readLabel(const MAHandle handle, const int index);

			/**
			 * Computes the phone attribute.
			 * @return The phone attribute.
			 */
			const int getAttribute() const;
		private:
			//The phone number.
			wchar* mNumber;

			//The type of data.
			eTypes mType;
			//The user defined label.
			wchar* mLabel;
			//Shows if this is a primary phone number or not.
			bool mIsPrimary;
	};

} //PIM

#endif //__PHONE_H__

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
 * @file Email.h
 * @author Florin Leu
 * @date 09 Feb 2011
 *
 * @brief PIM Field Email class.
 *
 **/

#ifndef __EMAIL_H__
#define __EMAIL_H__

#include <IX_PIM.h>

namespace PIM
{
	class Email
	{
		public:
			enum eTypes
			{
				//The constant describes a home e-mail address.
				TYPE_HOME = 0,
				//The constant describes a work e-mail address.
				TYPE_WORK,
				//The constant describes a mobile e-mail address.
				TYPE_MOBILE,
				//The constant describes a different e-mail address type.
				TYPE_OTHER,
				//The constant describes a custom e-mail address type.
				//The field's label can be set.
				TYPE_CUSTOM,
			};

			enum eSubFields
			{
				//The constant describes an e-mail address.
				ADDRESS = 0,
			};

		public:
			/**
			 * Constructor.
			 */
			Email();

			/**
			 * Destructor.
			 */
			~Email();

			/**
			 * Reads a contact's e-mail.
			 * @param args The arguments needed to read the e-mail.
			 * @param index The index of the e-mail to read.
			 */
			void read(MA_PIM_ARGS& args, int index);

			/**
			 * Writes a contact's e-mail.
			 * @param args The values to write.
			 * @index args The index of the e-mail to write.
			 */
			void write(MA_PIM_ARGS& args, int index);

			/**
			 * Deletes a contact's e-mail.
			 * @param handle The handle of the contact.
			 * @param index  The index of the e-mail to delete.
			 */
			void remove(MAHandle handle, int index);

			/**
			 * Gets the contact's e-mail address.
			 * @return The address of the contact.
			 */
			const wchar* const getAddress() const;

			/**
			 * Sets the contact's e-mail address.
			 * @param address The value to set.
			 */
			void setAddress(const wchar* const address);

			/**
			 * Gets the e-mail type.
			 * @return The type of the e-mail.
			 */
			const eTypes& getType() const;

			/**
			 * Sets the e-mail type.
			 * @param type The value to set.
			 */
			void setType(const eTypes& type);

			/**
			 * Gets the e-mail label.
			 * @return The label of the e-mail.
			 */
			const wchar* const getLabel() const;

			/**
			 * Sets the e-mail label.
			 * @param state The value to set.
			 */
			void setLabel(const wchar* const label);

			/**
			 * Checks if this is or not a primary e-mail.
			 * @return True if this is a primary e-mail.
			 */
			const bool isPrimary() const;

			/**
			 * Sets this as a primary e-mail.
			 * @param primary true if this is a primary e-mail.
			 */
			void setPrimary(const bool primary);

		private:
			/**
			 * Reads the type of the e-mail.
			 * @param handle The handle of the contact.
			 * @param index The index of this e-mail.
			 */
			void readType(const MAHandle handle, const int index);

			/**
			 * Reads the label of the e-mail.
			 * @param handle The handle of the contact.
			 * @param index The index of this e-mail.
			 */
			void readLabel(const MAHandle handle, const int index);

			/**
			 * Computes the e-mail attribute.
			 * @return The e-mail attribute.
			 */
			const int getAttribute() const;

		private:
			//The email address.
			wchar* mAddress;

			//The type of data.
			eTypes mType;
			//The user defined label.
			wchar* mLabel;
			//Shows if this is a primary email or not.
			bool mIsPrimary;
	};

} //PIM

#endif //__EMAIL_H__

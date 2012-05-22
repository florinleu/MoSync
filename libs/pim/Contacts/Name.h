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
 * @file Name.h
 * @author Florin Leu
 * @date 09 Feb 2011
 *
 * @brief PIM Field Name class.
 *
 **/

#ifndef __NAME_H__
#define __NAME_H__

#include <IX_PIM.h>

namespace PIM
{
	class Name
	{
		public:
			enum eSubFields
			{
				//The constant describes a display name.
				DISPLAY_NAME = 0,
				//The constant describes a first name.
				FIRST_NAME,
				//The constant describes a middle name.
				MIDDLE_NAME,
				//The constant describes a last name.
				LAST_NAME,
				//The constant describes a nickname.
				NICKNAME,
				//The constant describes a prefix.
				PREFIX,
				//The constant describes a suffix.
				SUFFIX,
				//The constant describes a phonetic first name.
				PHONETIC_FIRST_NAME,
				//The constant describes a phonetic middle name.
				PHONETIC_MIDDLE_NAME,
				//The constant describes a phonetic last name.
				PHONETIC_LAST_NAME,
				//The constant describes a formatted name.
				FORMATTED_NAME,
			};

		public:
			/**
			 * Constructor.
			 */
			Name();

			/**
			 * Destructor.
			 */
			~Name();

			/**
			 * Reads the contact's name.
			 * @param args The arguments needed to read the name.
			 * @return true on success.
			 */
			bool read(MA_PIM_ARGS& args);

			/**
			 * Writes the contact's id.
			 * @param args The values to write.
			 */
			void write(MA_PIM_ARGS& args);

			/**
			 * Deletes a contact's name.
			 * @param handle The handle of the contact.
			 */
			void remove(MAHandle handle);

			/**
			 * Gets the contact's display name.
			 * @return The display name of the contact.
			 */
			const wchar* const getDisplayName() const;

			/**
			 * Sets the contact's display name.
			 * @param displayName The value to set.
			 */
			void setDisplayName(const wchar* const displayName);

			/**
			 * Gets the contact's first name.
			 * @return The first name of the contact.
			 */
			const wchar* const getFirstName() const;

			/**
			 * Sets the contact's first name.
			 * @param firstName The value to set.
			 */
			void setFirstName(const wchar* const firstName);

			/**
			 * Gets the contact's middle name.
			 * @return The middle name of the contact.
			 */
			const wchar* const getMiddleName() const;

			/**
			 * Sets the contact's middle name.
			 * @param middleName The value to set.
			 */
			void setMiddleName(const wchar* const middleName);

			/**
			 * Gets the contact's last name.
			 * @return The last name of the contact.
			 */
			const wchar* const getLastName() const;

			/**
			 * Sets the contact's last name.
			 * @param lastName The value to set.
			 */
			void setLastName(const wchar* const lastName);

			/**
			 * Gets the contact's nickname.
			 * @return The nickname of the contact.
			 */
			const wchar* const getNickname() const;

			/**
			 * Sets the contact's nickname.
			 * @param nickname The value to set.
			 */
			void setNickname(const wchar* const nickname);

			/**
			 * Gets the contact's prefix.
			 * @return The prefix of the contact.
			 */
			const wchar* const getPrefix() const;

			/**
			 * Sets the contact's prefix.
			 * @param prefix The value to set.
			 */
			void setPrefix(const wchar* const prefix);

			/**
			 * Gets the contact's suffix.
			 * @return The suffix of the contact.
			 */
			const wchar* const getSuffix() const;

			/**
			 * Sets the contact's suffix.
			 * @param suffix The value to set.
			 */
			void setSuffix(const wchar* const suffix);

			/**
			 * Gets the contact's phonetic first name.
			 * @return The phonetic first name of the contact.
			 */
			const wchar* const getPhoneticFirstName() const;

			/**
			 * Sets the contact's phonetic first name.
			 * @param phoneticFirstName The value to set.
			 */
			void setPhoneticFirstName(const wchar* const phoneticFirstName);

			/**
			 * Gets the contact's phonetic middle name.
			 * @return The phonetic middle name of the contact.
			 */
			const wchar* const getPhoneticMiddleName() const;

			/**
			 * Sets the contact's phonetic middle name.
			 * @param phoneticMiddleName The value to set.
			 */
			void setPhoneticMiddleName(const wchar* const phoneticMiddleName);

			/**
			 * Gets the contact's phonetic last name.
			 * @return The phonetic last name of the contact.
			 */
			const wchar* const getPhoneticLastName() const;

			/**
			 * Sets the contact's phonetic last name.
			 * @param phoneticLastName The value to set.
			 */
			void setPhoneticLastName(const wchar* const phoneticLastName);

			/**
			 * Gets the contact's formatted name.
			 * @return The formatted name of the contact.
			 */
			const wchar* const getFormattedName() const;

		private:
			//The display name of the contact.
			wchar* mDisplayName;
			//The given name of the contact.
			wchar* mFirstName;
			//The middle name of the contact.
			wchar* mMiddleName;
			//The family name of the contact.
			wchar* mLastName;
			//The nickname of the contact.
			wchar* mNickname;
			//The contact's honorific prefix, e.g. "Sir"
			wchar* mPrefix;
			//The contact's honorific suffix, e.g. "Jr"
			wchar* mSuffix;
			//The phonetic version of the given name of the contact.
			wchar* mPhoneticFirstName;
			//The phonetic version of the additional name of the contact.
			wchar* mPhoneticMiddleName;
			//The phonetic version of the family name of the contact.
			wchar* mPhoneticLastName;
			//The formatted name of the contact.
			wchar* mFormattedName;
	};

} //PIM

#endif //__NAME_H__

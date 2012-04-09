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
				DISPLAY_NAME = 0,
				FIRST_NAME,
				MIDDLE_NAME,
				LAST_NAME,
				NICKNAME,
				PREFIX,
				SUFFIX,
				PHONETIC_FIRST_NAME,
				PHONETIC_MIDDLE_NAME,
				PHONETIC_LAST_NAME,
				FORMATTED_NAME
			};

		public:
			~Name();

			bool read(MA_PIM_ARGS& args);

			void write(MA_PIM_ARGS& args);

			const wchar* const getDisplayName() const;
			void setDisplayName(const wchar* const displayName);

			const wchar* const getFirstName() const;
			void setFirstName(const wchar* const firstName);

			const wchar* const getMiddleName() const;
			void setMiddleName(const wchar* const middleName);

			const wchar* const getLastName() const;
			void setLastName(const wchar* const lastName);

			const wchar* const getNickname() const;
			void setNickname(const wchar* const nickname);

			const wchar* const getPrefix() const;
			void setPrefix(const wchar* const prefix);

			const wchar* const getSuffix() const;
			void setSuffix(const wchar* const suffix);

			const wchar* const getPhoneticFirstName() const;
			void setPhoneticFirstName(const wchar* const phoneticFirstName);

			const wchar* const getPhoneticMiddleName() const;
			void setPhoneticMiddleName(const wchar* const phoneticMiddleName);

			const wchar* const getPhoneticLastName() const;
			void setPhoneticLastName(const wchar* const phoneticLastName);

			const wchar* const getFormattedName() const;

		private:
			void readDisplayName(const MAAddress buffer);
			void readFirstName(const MAAddress buffer);
			void readMiddleName(const MAAddress buffer);
			void readLastName(const MAAddress buffer);
			void readNickname(const MAAddress buffer);
			void readPrefix(const MAAddress buffer);
			void readSuffix(const MAAddress buffer);
			void readPhoneticFirstName(const MAAddress buffer);
			void readPhoneticMiddleName(const MAAddress buffer);
			void readPhoneticLastName(const MAAddress buffer);
			void readFormattedName(const MAAddress buffer);

			int writeLastName(MAAddress buffer);

		private:
			//The display name for the contact.
			wchar* mDisplayName;
			//The given name for the contact.
			wchar* mFirstName;
			//The middle name for the contact.
			wchar* mMiddleName;
			//The family name for the contact.
			wchar* mLastName;
			//The nickname for the contact.
			wchar* mNickname;
			//The contact's honorific prefix, e.g. "Sir"
			wchar* mPrefix;
			//The contact's honorific suffix, e.g. "Jr"
			wchar* mSuffix;
			//The phonetic version of the given name for the contact.
			wchar* mPhoneticFirstName;
			//The phonetic version of the additional name for the contact.
			wchar* mPhoneticMiddleName;
			//The phonetic version of the family name for the contact.
			wchar* mPhoneticLastName;
			//The formatted name for the contact.
			wchar* mFormattedName;
	};

} //PIM

#endif //__NAME_H__

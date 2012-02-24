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

#include <maapi.h>
#include <IX_PIM.h>

namespace PIM
{

	class Name
	{
		public:
			void read(MA_PIM_ARGS& args);

			const wchar* getDisplayName() const;
			void setDisplayName(wchar* const displayName);

			const wchar* getFirstName() const;
			void setFirstName(wchar* const firstName);

			const wchar* getMiddleName() const;
			void setMiddleName(wchar* const firstName);

			const wchar* getLastName() const;
			void setLastName(wchar* const firstName);

			const wchar* getNickname() const;
			void setNickname(wchar* const firstName);

			const wchar* getPrefix() const;
			void setPrefix(wchar* const firstName);

			const wchar* getSuffix() const;
			void setSuffix(wchar* const firstName);

			const wchar* getPhoneticFirstName() const;
			void setPhoneticFirstName(wchar* const firstName);

			const wchar* getPhoneticMiddleName() const;
			void setPhoneticMiddleName(wchar* const firstName);

			const wchar* getPhoneticLastName() const;
			void setPhoneticLastName(wchar* const firstName);

		private:
			void readDisplayName(MAAddress const buffer);
			void readFirstName(MAAddress const buffer);
			void readMiddleName(MAAddress const buffer);
			void readLastName(MAAddress const buffer);
			void readNickname(MAAddress const buffer);
			void readPrefix(MAAddress const buffer);
			void readSuffix(MAAddress const buffer);
			void readPhoneticFirstName(MAAddress const buffer);
			void readPhoneticMiddleName(MAAddress const buffer);
			void readPhoneticLastName(MAAddress const buffer);

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
	};

} //PIM

#endif //__NAME_H__

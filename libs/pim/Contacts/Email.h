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

	enum eEmailTypes
	{
		//The constant describes a home e-mail address.
		EMAIL_HOME = 0,
		//The constant describes a work e-mail address.
		EMAIL_WORK,
		//The constant describes a mobile e-mail address.
		EMAIL_MOBILE,
		//The constant describes a different e-mail address type.
		EMAIL_OTHER,
		//The constant describes a custom e-mail address type.
		//The field's label can be set.
		EMAIL_CUSTOM
	};

	class Email
	{
		public:
			Email();

			void read(MA_PIM_ARGS& args, int index);

			const wchar* getAddress() const;
			void setAddress(wchar* const street); //fleu TODO is this correct?

			const eEmailTypes& getType() const;
			void setType(const eEmailTypes& type);

			const wchar* getLabel() const;
			void setLabel(wchar* const label);

			const bool isPrimary() const;

		private:
			void readAddress(MAAddress const buffer);

			void readType(const MAHandle handle, const int index);
			void readLabel(const MAHandle handle, const int index);

		private:
			//The email address.
			wchar* mAddress;

			//The type of data.
			eEmailTypes mType;
			//The user defined label
			wchar* mLabel;
			//Shows if this is a primary email or not.
			bool mIsPrimary;
	};

} //PIM

#endif //__EMAIL_H__

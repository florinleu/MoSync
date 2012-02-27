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

	enum ePhoneTypes
	{
		//The constant describes a home phone number.
		PHONE_HOME = 0,
		//The constant describes a mobile phone number.
		PHONE_MOBILE,
		//The constant describes a home fax phone number.
		PHONE_HOME_FAX,
		//The constant describes a work fax phone number.
		PHONE_WORK_FAX,
		//The constant describes a pager phone number.
		PHONE_PAGER,
		//The constant describes an iPhone phone number.
		PHONE_IPHONE,
		//The constant describes a work phone number.
		PHONE_WORK,
		//The constant describes a callback phone number.
		PHONE_CALLBACK,
		//The constant describes a car phone number.
		PHONE_CAR,
		//The constant describes a company main phone number.
		PHONE_COMPANY_MAIN,
		//The constant describes a ISDN phone number.
		PHONE_ISDN,
		//The constant describes a other fax type phone number.
		PHONE_OTHER_FAX,
		//The constant describes a radio phone number.
		PHONE_RADIO,
		//The constant describes a telex phone number.
		PHONE_TELEX,
		//The constant describes a TTY TDD phone number.
		PHONE_TTY_TDD,
		//The constant describes a work mobile phone number.
		PHONE_WORK_MOBILE,
		//The constant describes a work pager phone number.
		PHONE_WORK_PAGER,
		//The constant describes an assistant phone number.
		PHONE_ASSISTANT,
		//The constant describes a MMS phone number.
		PHONE_MMS,
		//The constant describes a different phone number type.
		PHONE_OTHER,
		//The constant describes a custom phone number type.
		//The field's label can be set.
		PHONE_CUSTOM,
	};

	class Phone
	{
		public:
			Phone();

			void read(MA_PIM_ARGS& args, int index);

			const wchar* getNumber() const;
			void setNumber(wchar* const street); //fleu TODO is this correct?

			const ePhoneTypes& getType() const;
			void setType(const ePhoneTypes& type);

			const wchar* getLabel() const;
			void setLabel(wchar* const label);

			const bool isPrimary() const;

		private:
			void readNumber(MAAddress const buffer);

			void readType(const MAHandle handle, const int index);
			void readLabel(const MAHandle handle, const int index);

		private:
			//The phone number.
			wchar* mNumber;

			//The type of data.
			ePhoneTypes mType;
			//The user defined label.
			wchar* mLabel;
			//Shows if this is a primary phone number or not.
			bool mIsPrimary;
	};

} //PIM

#endif //__PHONE_H__

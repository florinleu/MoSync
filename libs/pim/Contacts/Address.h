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
 * @file Address.h
 * @author Florin Leu
 * @date 09 Feb 2011
 *
 * @brief PIM Field Address class.
 *
 **/

#ifndef __ADDRESS_H__
#define __ADDRESS_H__

#include <IX_PIM.h>

namespace PIM
{

	enum eAddressTypes
	{
		//The constant describes a home address.
		ADDRESS_HOME = 0,
		//The constant describes a work address.
		ADDRESS_WORK,
		//The constant describes a different address type.
		ADDRESS_OTHER,
		//The constant describes a custom address type.
		//The field's label can be set.
		ADDRESS_CUSTOM,
	};

	class Address
	{
		public:
			Address();

			void read(MA_PIM_ARGS& args, int index);

			const wchar* getStreet() const;
			void setStreet(wchar* const street); //fleu TODO is this correct?

			const wchar* getCity() const;
			void setCity(wchar* const city);

			const wchar* getState() const;
			void setState(wchar* const state);

			const wchar* getPostalCode() const;
			void setPostalCode(wchar* const postalCode);

			const wchar* getCountry() const;
			void setCountry(wchar* const country);

			const wchar* getNeighborhood() const;
			void setNeighborhood(wchar* const neighborhood);

			const wchar* getPOBox() const;
			void setPOBox(wchar* const pobox);

			const eAddressTypes& getType() const;
			void setType(const eAddressTypes& type);

			const wchar* getLabel() const;
			void setLabel(wchar* const label);

			const bool isPrimary() const;

		private:
			void readStreet(MAAddress const buffer);
			void readCity(MAAddress const buffer);
			void readState(MAAddress const buffer);
			void readPostalCode(MAAddress const buffer);
			void readCountry(MAAddress const buffer);
			void readNeighborhood(MAAddress const buffer);
			void readPOBox(MAAddress const buffer);

			void readType(const MAHandle handle, const int index);
			void readLabel(const MAHandle handle, const int index);
		private:
			//The street of the address.
			//This element also includes the house number and room/apartment/flat/floor number.
			wchar* mStreet;
			//The city of the address.
			wchar* mCity;
			//The state, province, county (in Ireland), Land (in Germany),
			//departement (in France), etc. of the address.
			wchar* mState;
			//The postal code of the address.
			wchar* mPostalCode;
			//The country of the address.
			wchar* mCountry;
			//Available only on Android.
			wchar* mNeighborhood;
			//Available only on Android.
			wchar* mPOBox;

			//The type of data.
			eAddressTypes mType;
			//The user defined label
			wchar* mLabel;
			//Shows if this is a primary address or not.
			bool mIsPrimary;
	};

} //PIM

#endif //__ADDRESS_H__

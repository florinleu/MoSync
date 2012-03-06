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
			void setStreet(wchar* street);

			const wchar* getCity() const;
			void setCity(wchar* city);

			const wchar* getState() const;
			void setState(wchar* state);

			const wchar* getPostalCode() const;
			void setPostalCode(wchar* postalCode);

			const wchar* getCountry() const;
			void setCountry(wchar* country);

			const wchar* getNeighborhood() const;
			void setNeighborhood(wchar* neighborhood);

			const wchar* getPOBox() const;
			void setPOBox(wchar* pobox);

			const eAddressTypes& getType() const;
			void setType(const eAddressTypes& type);

			const wchar* getLabel() const;
			void setLabel(wchar* label);

			const wchar* getFormattedAddress() const;

			const bool isPrimary() const;

		private:
			void readStreet(const MAAddress buffer);
			void readCity(const MAAddress buffer);
			void readState(const MAAddress buffer);
			void readPostalCode(const MAAddress buffer);
			void readCountry(const MAAddress buffer);
			void readNeighborhood(const MAAddress buffer);
			void readPOBox(const MAAddress buffer);
			void readFormattedAddress(const MAAddress buffer);

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
			//The neighborhood of the address.
			wchar* mNeighborhood;
			//The PO Box of the address.
			wchar* mPOBox;
			//The formatted address.
			wchar* mFormattedAddress;

			//The type of data.
			eAddressTypes mType;
			//The user defined label
			wchar* mLabel;
			//Shows if this is a primary address or not.
			bool mIsPrimary;
	};

} //PIM

#endif //__ADDRESS_H__

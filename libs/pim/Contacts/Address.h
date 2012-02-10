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
	};

} //PIM

#endif //__ADDRESS_H__

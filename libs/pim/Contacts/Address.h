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
	class Address
	{
		public:
			enum eTypes
			{
				//The constant describes a home address.
				HOME = 0,
				//The constant describes a work address.
				WORK,
				//The constant describes a different address type.
				OTHER,
				//The constant describes a custom address type.
				//The field's label can be set.
				CUSTOM,
			};

			enum eSubFields
			{
				//The constant describes a street.
				STREET = 0,
				//The constant describes a city.
				CITY,
				//The constant describes a state.
				STATE,
				//The constant describes a postal code.
				POSTAL_CODE,
				//The constant describes a country.
				COUNTRY,
				//The constant describes a neighborhood.
				NEIGHBORHOOD,
				//The constant describes a po box.
				PO_BOX,
				//The constant describes a formatted address.
				FORMATTED_ADDRESS
			};
		public:
			/**
			 * Constructor.
			 */
			Address();

			/**
			 * Destructor.
			 */
			~Address();

			/**
			 * Reads a contact's address.
			 * @param args The arguments needed to read the address.
			 * @param index The index of the address to read.
			 */
			void read(MA_PIM_ARGS& args, int index);

			/**
			 * Writes a contact's address.
			 * @param args The values to write.
			 * @param index The index of the address to write.
			 */
			void write(MA_PIM_ARGS& args, int index);

			/**
			 * Deletes a contact's address.
			 * @param handle The handle of the contact.
			 * @param index  The index of the address to delete.
			 */
			void remove(MAHandle handle, int index);

			/**
			 * Gets the contact's street.
			 * @return The street of the contact.
			 */
			const wchar* const getStreet() const;

			/**
			 * Sets the contact's street.
			 * @param street The value to set.
			 */
			void setStreet(const wchar* const street);

			/**
			 * Gets the contact's city.
			 * @return The city of the contact.
			 */
			const wchar* const getCity() const;

			/**
			 * Sets the contact's city.
			 * @param city The value to set.
			 */
			void setCity(const wchar* const city);

			/**
			 * Gets the contact's state.
			 * @return The state of the contact.
			 */
			const wchar* const getState() const;

			/**
			 * Sets the contact's state.
			 * @param state The value to set.
			 */
			void setState(const wchar* const state);

			/**
			 * Gets the contact's postal code.
			 * @return The postal code of the contact.
			 */
			const wchar* const getPostalCode() const;

			/**
			 * Sets the contact's postal code.
			 * @param postalCode The value to set.
			 */
			void setPostalCode(const wchar* const postalCode);

			/**
			 * Gets the contact's country.
			 * @return The country of the contact.
			 */
			const wchar* const getCountry() const;

			/**
			 * Sets the contact's country.
			 * @param country The value to set.
			 */
			void setCountry(const wchar* const country);

			/**
			 * Gets the contact's neighborhood.
			 * @return The neighborhood of the contact.
			 */
			const wchar* const getNeighborhood() const;

			/**
			 * Sets the contact's neighborhood.
			 * @param neighborhood The value to set.
			 */
			void setNeighborhood(const wchar* const neighborhood);

			/**
			 * Gets the contact's po box.
			 * @return The po box of the contact.
			 */
			const wchar* const getPOBox() const;

			/**
			 * Sets the contact's po box.
			 * @param pobox The value to set.
			 */
			void setPOBox(const wchar* const pobox);

			/**
			 * Gets the contact's formatted address.
			 * @return The formatted address of the contact.
			 */
			const wchar* const getFormattedAddress() const;

			/**
			 * Gets the address type.
			 * @return The type of the address.
			 */
			const eTypes& getType() const;

			/**
			 * Sets the address type.
			 * @param type The value to set.
			 */
			void setType(const eTypes& type);

			/**
			 * Gets the address label.
			 * @return The label of the address.
			 */
			const wchar* const getLabel() const;

			/**
			 * Sets the address label.
			 * @param state The value to set.
			 */
			void setLabel(const wchar* const label);

			/**
			 * Checks if this is or not a primary address.
			 * @return True if this is a primary address.
			 */
			const bool isPrimary() const;

			/**
			 * Sets this as a primary address.
			 * @param primary true if this is a primary address.
			 */
			void setPrimary(const bool primary);

		private:
			/**
			 * Reads the type of the address.
			 * @param handle The handle of the contact.
			 * @param index The index of this address.
			 */
			void readType(const MAHandle handle, const int index);

			/**
			 * Reads the label of the address.
			 * @param handle The handle of the contact.
			 * @param index The index of this address.
			 */
			void readLabel(const MAHandle handle, const int index);

			/**
			 * Computes the address attribute.
			 * @return The address attribute.
			 */
			const int getAttribute() const;

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
			eTypes mType;
			//The user defined label.
			wchar* mLabel;
			//Shows if this is a primary address or not.
			bool mIsPrimary;
	};

} //PIM

#endif //__ADDRESS_H__

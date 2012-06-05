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
 * @file Address.cpp
 * @author Florin Leu
 * @date 20 Feb 2011
 *
 * @brief PIM Field Address class.
 *
 **/

#include <conprint.h>
#include <mawstring.h>

#include "Address.h"
#include "util.h"

namespace PIM
{
	/**
	 * Constructor.
	 */
	Address::Address():
		mStreet(NULL),
		mCity(NULL),
		mState(NULL),
		mPostalCode(NULL),
		mCountry(NULL),
		mNeighborhood(NULL),
		mPOBox(NULL),
		mFormattedAddress(NULL),
		mLabel(NULL),
		mIsPrimary(false)
	{

	}

	/**
	 * Destructor.
	 */
	Address::~Address()
	{
		DELETE(mStreet);
		DELETE(mCity);
		DELETE(mState);
		DELETE(mPostalCode);
		DELETE(mCountry);
		DELETE(mNeighborhood);
		DELETE(mPOBox);
		DELETE(mFormattedAddress);
		DELETE(mLabel);
	}

	/**
	 * Reads a contact's address.
	 * @param args The arguments needed to read the address.
	 * @param index The index of the address to read.
	 */
	void Address::read(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: address read");

		args.field = MA_PIM_FIELD_CONTACT_ADDR;
		args.bufSize = PIM_BUF_SIZE;
		if (maPimItemGetValue(&args, index) > 0)
		{
			mStreet = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_ADDR_STREET);
			mCity = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_ADDR_LOCALITY);
			mState = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_ADDR_REGION);
			mPostalCode = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_ADDR_POSTALCODE);
			mCountry = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_ADDR_COUNTRY);
			mNeighborhood = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_ADDR_NEIGHBORHOOD);
			mPOBox = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_ADDR_POBOX);

			readType(args.item, index);
			readLabel(args.item, index);
		}

		args.field = MA_PIM_FIELD_CONTACT_FORMATTED_ADDR;
		args.bufSize = PIM_BUF_SIZE;
		if (maPimItemGetValue(&args, index) >=0 )
		{
			wchar* src = (wchar*)args.buf;
			mFormattedAddress = wcsdup(src);
		}
	}

	/**
	 * Writes a contact's address.
	 * @param args The values to write.
	 * @index args The index of the address to write.
	 */
	void Address::write(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: address write");

		args.field = MA_PIM_FIELD_CONTACT_ADDR;
		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeInt(args.buf, MA_PIM_CONTACT_ADDR_COUNT, 0);
		args.bufSize += writeWString(args.buf, mPOBox, args.bufSize);
		args.bufSize += writeWString(args.buf, NULL, args.bufSize);
		args.bufSize += writeWString(args.buf, mStreet, args.bufSize);
		args.bufSize += writeWString(args.buf, mCity, args.bufSize);
		args.bufSize += writeWString(args.buf, mState, args.bufSize);
		args.bufSize += writeWString(args.buf, mPostalCode, args.bufSize);
		args.bufSize += writeWString(args.buf, mCountry, args.bufSize);
		args.bufSize += writeWString(args.buf, mNeighborhood, args.bufSize);
		maPimItemSetValue(&args, index, getAttribute());

		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeWString(args.buf, mLabel, 0);
		maPimItemSetLabel(&args, index);
	}

	/**
	 * Deletes a contact's address.
	 * @param handle The handle of the contact.
	 * @param index  The index of the address to delete.
	 */
	void Address::remove(MAHandle handle, int index)
	{
		printf("@LIB: address delete");

		maPimItemRemoveValue(handle, MA_PIM_FIELD_CONTACT_ADDR, index);
	}

	/**
	 * Reads the type of the address.
	 * @param handle The handle of the contact.
	 * @param index The index of this address.
	 */
	void Address::readType(const MAHandle handle, const int index)
	{
		int attribute = maPimItemGetAttributes(handle, MA_PIM_FIELD_CONTACT_ADDR, index);

		if (attribute >> 16)
		{
			mIsPrimary = true;

			// Remove primary value from attribute.
			attribute = (attribute & 0xFFFF);
		}

		switch (attribute)
		{
			case MA_PIM_ATTR_ADDR_HOME:
				mType = HOME;
				break;
			case MA_PIM_ATTR_ADDR_WORK:
				mType = WORK;
				break;
			case MA_PIM_ATTR_ADDR_CUSTOM:
				mType = CUSTOM;
				break;
			default:
				mType = OTHER;
				break;
		}
	}

	/**
	 * Reads the label of the address.
	 * @param handle The handle of the contact.
	 * @param index The index of this address.
	 */
	void Address::readLabel(const MAHandle handle, const int index)
	{
		MA_PIM_ARGS args;
		args.item = handle;
		args.field = MA_PIM_FIELD_CONTACT_ADDR;
		args.bufSize = PIM_BUF_SIZE;

		char buf[PIM_BUF_SIZE];
		args.buf = buf;
		args.bufSize = PIM_BUF_SIZE;
		maPimItemGetLabel(&args, index);

		wchar* src = (wchar*)args.buf;
		mLabel = wcsdup(src);
	}

	/**
	 * Gets the contact's street.
	 * @return The street of the contact.
	 */
	const wchar* const Address::getStreet() const
	{
		return mStreet;
	}

	/**
	 * Sets the contact's street.
	 * @param street The value to set.
	 */
	void Address::setStreet(const wchar* const street)
	{
		DELETE(mStreet);
		mStreet = wcsdup(street);
	}

	/**
	 * Gets the contact's city.
	 * @return The city of the contact.
	 */
	const wchar* const Address::getCity() const
	{
		return mCity;
	}

	/**
	 * Sets the contact's city.
	 * @param city The value to set.
	 */
	void Address::setCity(const wchar* const city)
	{
		DELETE(mCity);
		mCity = wcsdup(city);
	}

	/**
	 * Gets the contact's state.
	 * @return The state of the contact.
	 */
	const wchar* const Address::getState() const
	{
		return mState;
	}

	/**
	 * Sets the contact's state.
	 * @param state The value to set.
	 */
	void Address::setState(const wchar* const state)
	{
		DELETE(mState);
		mState = wcsdup(state);
	}

	/**
	 * Gets the contact's postal code.
	 * @return The postal code of the contact.
	 */
	const wchar* const Address::getPostalCode() const
	{
		return mPostalCode;
	}

	/**
	 * Sets the contact's postal code.
	 * @param postalCode The value to set.
	 */
	void Address::setPostalCode(const wchar* const postalCode)
	{
		DELETE(mPostalCode);
		mPostalCode = wcsdup(postalCode);
	}

	/**
	 * Gets the contact's country.
	 * @return The country of the contact.
	 */
	const wchar* const Address::getCountry() const
	{
		return mCountry;
	}

	/**
	 * Sets the contact's country.
	 * @param country The value to set.
	 */
	void Address::setCountry(const wchar* const country)
	{
		DELETE(mCountry);
		mCountry = wcsdup(country);
	}

	/**
	 * Gets the contact's neighborhood.
	 * @return The neighborhood of the contact.
	 */
	const wchar* const Address::getNeighborhood() const
	{
		return mNeighborhood;
	}

	/**
	 * Sets the contact's neighborhood.
	 * @param neighborhood The value to set.
	 */
	void Address::setNeighborhood(const wchar* const neighborhood)
	{
		DELETE(mNeighborhood);
		mNeighborhood = wcsdup(neighborhood);
	}

	/**
	 * Gets the contact's po box.
	 * @return The po box of the contact.
	 */
	const wchar* const Address::getPOBox() const
	{
		return mPOBox;
	}

	/**
	 * Sets the contact's po box.
	 * @param pobox The value to set.
	 */
	void Address::setPOBox(const wchar* const pobox)
	{
		DELETE(mPOBox);
		mPOBox = wcsdup(pobox);
	}

	/**
	 * Gets the contact's formatted address.
	 * @return The formatted address of the contact.
	 */
	const wchar* const Address::getFormattedAddress() const
	{
		return mFormattedAddress;
	}

	/**
	 * Gets the address type.
	 * @return The type of the address.
	 */
	const Address::eTypes& Address::getType() const
	{
		return mType;
	}

	/**
	 * Sets the address type.
	 * @param type The value to set.
	 */
	void Address::setType(const Address::eTypes& type)
	{
		mType = type;
	}

	/**
	 * Gets the address label.
	 * @return The label of the address.
	 */
	const wchar* const Address::getLabel() const
	{
		return mLabel;
	}

	/**
	 * Sets the address label.
	 * @param state The value to set.
	 */
	void Address::setLabel(const wchar* const label)
	{
		DELETE(mLabel);
		mLabel = wcsdup(label);
	}

	/**
	 * Checks if this is or not a primary address.
	 * @return True if this is a primary address.
	 */
	const bool Address::isPrimary() const
	{
		return mIsPrimary;
	}

	/**
	 * Sets this as a primary address.
	 * @param primary true if this is a primary address.
	 */
	void Address::setPrimary(const bool primary)
	{
		mIsPrimary = primary;
	}

	/**
	 * Computes the address attribute.
	 * @return The address attribute.
	 */
	const int Address::getAttribute() const
	{
		int attribute = 0;
		switch (mType)
		{
			case HOME:
				attribute = MA_PIM_ATTR_ADDR_HOME;
				break;
			case WORK:
				attribute = MA_PIM_ATTR_ADDR_WORK;
				break;
			case CUSTOM:
				attribute = MA_PIM_ATTR_ADDR_CUSTOM;
				break;
			default:
				attribute = MA_PIM_ATTR_ADDR_OTHER;
				break;
		}

		attribute |= (mIsPrimary ? MA_PIM_ATTRPREFERRED : 0);

		return attribute;
	}

} //PIM

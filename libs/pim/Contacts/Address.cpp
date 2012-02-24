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
	/*
	 * Constructor
	 */
	Address::Address():
		mIsPrimary(false)
	{

	}

	/*
	 * Read a complete address.
	 */
	void Address::read(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: address read");
		args.field = MA_PIM_FIELD_CONTACT_ADDR;
		//CHECK_RESULT(maPimItemGetValue(&args, 0));
		if (maPimItemGetValue(&args, index))
		{
			readStreet(args.buf);
			readCity(args.buf);
			readState(args.buf);
			readPostalCode(args.buf);
			readCountry(args.buf);
			readNeighborhood(args.buf);
			readPOBox(args.buf);

			readType(args.item, index);
			readLabel(args.item, index);
		}
	}

	void Address::readStreet(MAAddress const buffer)
	{
		mStreet = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_ADDR_STREET);
	}

	void Address::readCity(MAAddress const buffer)
	{
		mCity = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_ADDR_LOCALITY);
	}

	void Address::readState(MAAddress const buffer)
	{
		mState = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_ADDR_REGION);
	}

	void Address::readPostalCode(MAAddress const buffer)
	{
		mPostalCode = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_ADDR_POSTALCODE);
	}

	void Address::readCountry(MAAddress const buffer)
	{
		mCountry = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_ADDR_COUNTRY);
	}

	void Address::readNeighborhood(MAAddress const buffer)
	{
		mNeighborhood = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_ADDR_NEIGHBORHOOD);
	}

	void Address::readPOBox(MAAddress const buffer)
	{
		mPOBox = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_ADDR_POBOX);
	}

	void Address::readType(const MAHandle handle, const int index)
	{
		int attribute = maPimItemGetAttributes(handle, MA_PIM_FIELD_CONTACT_ADDR, index);

		if (attribute >> 16)
		{
			mIsPrimary == true;

			// Remove primary value from attribute.
			attribute = (attribute & 0xFFFF);
		}

		switch (attribute)
		{
			case MA_PIM_ATTR_ADDR_HOME:
				mType = ADDRESS_HOME;
				break;
			case MA_PIM_ATTR_ADDR_WORK:
				mType = ADDRESS_WORK;
				break;
			case MA_PIM_ATTR_ADDR_CUSTOM:
				mType = ADDRESS_CUSTOM;
				break;
			default:
				mType = ADDRESS_OTHER;
				break;
		}
	}

	void Address::readLabel(const MAHandle handle, const int index)
	{
		MA_PIM_ARGS args;
		args.item = handle;
		args.field = MA_PIM_FIELD_CONTACT_ADDR;

		char buf[BUF_SIZE];
		args.buf = buf;
		args.bufSize = BUF_SIZE;
		maPimItemGetLabel(&args, index);

		DELETE(mLabel);
		wchar* src = (wchar*)args.buf;
		int len = wcslen(src);
		mLabel = new wchar[len + 1];
		wcsncpy(mLabel, src, len);
	}

	/*
	 * Getter for street.
	 */
	const wchar* Address::getStreet() const
	{
		return mStreet;
	}

	/*
	 * Setter for street.
	 */
	void Address::setStreet(wchar* const street)
	{
		mStreet = street;
	}

	/*
	 * Getter for city.
	 */
	const wchar* Address::getCity() const
	{
		return mCity;
	}

	/*
	 * Setter for city.
	 */
	void Address::setCity(wchar* const city)
	{
		mCity = city;
	}

	/*
	 * Getter for state.
	 */
	const wchar* Address::getState() const
	{
		return mState;
	}

	/*
	 * Setter for state.
	 */
	void Address::setState(wchar* const state)
	{
		mState = state;
	}

	/*
	 * Getter for postalCode.
	 */
	const wchar* Address::getPostalCode() const
	{
		return mPostalCode;
	}

	/*
	 * Setter for postalCode.
	 */
	void Address::setPostalCode(wchar* const postalCode)
	{
		mPostalCode = postalCode;
	}

	/*
	 * Getter for country.
	 */
	const wchar* Address::getCountry() const
	{
		return mCountry;
	}

	/*
	 * Setter for country.
	 */
	void Address::setCountry(wchar* const country)
	{
		mCountry = country;
	}

	/*
	 * Getter for neighborhood.
	 */
	const wchar* Address::getNeighborhood() const
	{
		return mNeighborhood;
	}

	/*
	 * Setter for neighborhood.
	 */
	void Address::setNeighborhood(wchar* const neighborhood)
	{
		mNeighborhood = neighborhood;
	}

	/*
	 * Getter for pobox.
	 */
	const wchar* Address::getPOBox() const
	{
		return mPOBox;
	}

	/*
	 * Setter for pobox.
	 */
	void Address::setPOBox(wchar* const pobox)
	{
		mPOBox = pobox;
	}

	/*
	 * Getter for type.
	 */
	const eAddressTypes& Address::getType() const
	{
		return mType;
	}

	/*
	 * Setter for type.
	 */
	void Address::setType(const eAddressTypes& type)
	{
		mType = type;
	}

	/*
	 * Getter for label.
	 */
	const wchar* Address::getLabel() const
	{
		return mLabel;
	}

	/*
	 * Setter for label.
	 */
	void Address::setLabel(wchar* const label)
	{
		mLabel = label;
	}

	/*
	 * Returns true if this is set as the primary address.
	 */
	const bool Address::isPrimary()
	{
		return mIsPrimary;
	}

} //PIM

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
 * @file Website.cpp
 * @author Florin Leu
 * @date 24 Feb 2011
 *
 * @brief PIM Field Website class.
 *
 **/

#include <conprint.h>
#include <mawstring.h>

#include "Website.h"
#include "util.h"

namespace PIM
{
	/**
	 * Constructor.
	 */
	Website::Website():
		mURL(NULL),
		mLabel(NULL),
		mIsPrimary(false)
	{

	}

	/**
	 * Destructor.
	 */
	Website::~Website()
	{
		DELETE(mURL);
		DELETE(mLabel);
	}

	/**
	 * Reads a contact's website.
	 * @param args The arguments needed to read the website.
	 * @param index The index of the website to read.
	 */
	void Website::read(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: website read");
		args.field = MA_PIM_FIELD_CONTACT_URL;
		args.bufSize = PIM_BUF_SIZE;
		if (maPimItemGetValue(&args, index) >= 0)
		{
			wchar* src = (wchar*)args.buf;
			mURL = wcsdup(src);

			readType(args.item, index);
			readLabel(args.item, index);
		}
	}

	/**
	 * Writes a contact's website.
	 * @param args The values to write.
	 * @index args The index of the website to write.
	 */
	void Website::write(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: website write");

		args.field = MA_PIM_FIELD_CONTACT_URL;
		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeWString(args.buf, mURL, 0);
		maPimItemSetValue(&args, index, getAttribute());

		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeWString(args.buf, mLabel, 0);
		maPimItemSetLabel(&args, index);
	}

	/**
	 * Deletes a contact's website.
	 * @param handle The handle of the contact.
	 * @param index  The index of the website to delete.
	 */
	void Website::remove(MAHandle handle, int index)
	{
		printf("@LIB: website delete");

		maPimItemRemoveValue(handle, MA_PIM_FIELD_CONTACT_URL, index);
	}

	/**
	 * Reads the type of the website.
	 * @param handle The handle of the contact.
	 * @param index The index of this website.
	 */
	void Website::readType(const MAHandle handle, const int index)
	{
		int attribute = maPimItemGetAttributes(handle, MA_PIM_FIELD_CONTACT_URL, index);

		if (attribute >> 16)
		{
			mIsPrimary = true;

			// Remove primary value from attribute.
			attribute = (attribute & 0xFFFF);
		}

		switch (attribute)
		{
			case MA_PIM_ATTR_WEBSITE_HOMEPAGE:
				mType = HOMEPAGE;
				break;
			case MA_PIM_ATTR_WEBSITE_BLOG:
				mType = BLOG;
				break;
			case MA_PIM_ATTR_WEBSITE_PROFILE:
				mType = PROFILE;
				break;
			case MA_PIM_ATTR_WEBSITE_HOME:
				mType = HOME;
				break;
			case MA_PIM_ATTR_WEBSITE_WORK:
				mType = WORK;
				break;
			case MA_PIM_ATTR_WEBSITE_FTP:
				mType = FTP;
				break;
			case MA_PIM_ATTR_WEBSITE_CUSTOM:
				mType = CUSTOM;
				break;
			default:
				mType = OTHER;
				break;
		}
	}

	/**
	 * Reads the label of the website.
	 * @param handle The handle of the contact.
	 * @param index The index of this website.
	 */
	void Website::readLabel(const MAHandle handle, const int index)
	{
		MA_PIM_ARGS args;
		args.item = handle;
		args.field = MA_PIM_FIELD_CONTACT_URL;
		args.bufSize = PIM_BUF_SIZE;

		char buf[PIM_BUF_SIZE];
		args.buf = buf;
		args.bufSize = PIM_BUF_SIZE;
		maPimItemGetLabel(&args, index);

		wchar* src = (wchar*)args.buf;
		mLabel = wcsdup(src);
	}

	/**
	 * Gets the contact's website url.
	 * @return The url of the contact.
	 */
	const wchar* const Website::getURL() const
	{
		return mURL;
	}

	/**
	 * Sets the contact's website url.
	 * @param url The value to set.
	 */
	void Website::setURL(const wchar* const url)
	{
		DELETE(mURL);
		mURL = wcsdup(url);
	}

	/**
	 * Gets the website type.
	 * @return The type of the website.
	 */
	const Website::eTypes& Website::getType() const
	{
		return mType;
	}

	/**
	 * Sets the website type.
	 * @param type The value to set.
	 */
	void Website::setType(const Website::eTypes& type)
	{
		mType = type;
	}

	/**
	 * Gets the website label.
	 * @return The label of the website.
	 */
	const wchar* const Website::getLabel() const
	{
		return mLabel;
	}

	/**
	 * Sets the website label.
	 * @param label The value to set.
	 */
	void Website::setLabel(const wchar* const label)
	{
		DELETE(mLabel);
		mLabel = wcsdup(label);
	}

	/**
	 * Checks if this is or not a primary website.
	 * @return True if this is a primary website.
	 */
	const bool Website::isPrimary() const
	{
		return mIsPrimary;
	}

	/**
	 * Sets this as a primary website.
	 * @param primary true if this is a primary website.
	 */
	void Website::setPrimary(const bool primary)
	{
		mIsPrimary = primary;
	}

	/**
	 * Computes the website attribute.
	 * @return The website attribute.
	 */
	const int Website::getAttribute() const
	{
		int attribute = 0;
		switch (mType)
		{
			case HOMEPAGE:
				attribute = MA_PIM_ATTR_WEBSITE_HOMEPAGE;
				break;
			case BLOG:
				attribute = MA_PIM_ATTR_WEBSITE_BLOG;
				break;
			case PROFILE:
				attribute = MA_PIM_ATTR_WEBSITE_PROFILE;
				break;
			case HOME:
				attribute = MA_PIM_ATTR_WEBSITE_HOME;
				break;
			case WORK:
				attribute = MA_PIM_ATTR_WEBSITE_WORK;
				break;
			case FTP:
				attribute = MA_PIM_ATTR_WEBSITE_FTP;
				break;
			case CUSTOM:
				attribute = MA_PIM_ATTR_WEBSITE_CUSTOM;
				break;
			default:
				attribute = MA_PIM_ATTR_WEBSITE_OTHER;
				break;
		}

		attribute |= (mIsPrimary ? MA_PIM_ATTRPREFERRED : 0);

		return attribute;
	}

} //PIM

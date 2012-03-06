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
#include "Phone.h"
#include "util.h"

namespace PIM
{
	/*
	 * Constructor
	 */
	Website::Website():
		mIsPrimary(false)
	{
	}

	/*
	 * Read a complete website.
	 */
	void Website::read(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: website read");
		args.field = MA_PIM_FIELD_CONTACT_URL;
		args.bufSize = BUF_SIZE;
		if (maPimItemGetValue(&args, index) >= 0)
		{
			readURL(args.buf);

			readType(args.item, index);
			readLabel(args.item, index);
		}
	}

	void Website::readURL(const MAAddress buffer)
	{
		DELETE(mURL);
		wchar* src = (wchar*)buffer;
		mURL = wcsdup(src);
	}

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
				mType = WEBSITE_HOMEPAGE;
				break;
			case MA_PIM_ATTR_WEBSITE_BLOG:
				mType = WEBSITE_BLOG;
				break;
			case MA_PIM_ATTR_WEBSITE_PROFILE:
				mType = WEBSITE_PROFILE;
				break;
			case MA_PIM_ATTR_WEBSITE_HOME:
				mType = WEBSITE_HOME;
				break;
			case MA_PIM_ATTR_WEBSITE_WORK:
				mType = WEBSITE_WORK;
				break;
			case MA_PIM_ATTR_WEBSITE_FTP:
				mType = WEBSITE_FTP;
				break;
			case MA_PIM_ATTR_WEBSITE_CUSTOM:
				mType = WEBSITE_CUSTOM;
				break;
			default:
				mType = WEBSITE_OTHER;
				break;
		}
	}

	void Website::readLabel(const MAHandle handle, const int index)
	{
		MA_PIM_ARGS args;
		args.item = handle;
		args.field = MA_PIM_FIELD_CONTACT_URL;
		args.bufSize = BUF_SIZE;

		char buf[BUF_SIZE];
		args.buf = buf;
		args.bufSize = BUF_SIZE;
		maPimItemGetLabel(&args, index);
		DELETE(mLabel);
		wchar* src = (wchar*)args.buf;
		mLabel = wcsdup(src);
	}

	/*
	 * Getter for website URL.
	 */
	const wchar* Website::getURL() const
	{
		return mURL;
	}

	/*
	 * Setter for website URL.
	 */
	void Website::setURL(wchar* url)
	{
		mURL = url;
	}

	/*
	 * Getter for type.
	 */
	const eWebsiteTypes& Website::getType() const
	{
		return mType;
	}

	/*
	 * Setter for type.
	 */
	void Website::setType(const eWebsiteTypes& type)
	{
		mType = type;
	}

	/*
	 * Getter for label.
	 */
	const wchar* Website::getLabel() const
	{
		return mLabel;
	}

	/*
	 * Setter for label.
	 */
	void Website::setLabel(wchar* label)
	{
		mLabel = label;
	}

	/*
	 * Returns true if this is set as the primary website.
	 */
	const bool Website::isPrimary() const
	{
		return mIsPrimary;
	}

} //PIM

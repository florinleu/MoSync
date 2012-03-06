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
 * @file Organization.cpp
 * @author Florin Leu
 * @date 27 Feb 2011
 *
 * @brief PIM Field Organization class.
 *
 **/

#include <conprint.h>
#include <mawstring.h>

#include "Organization.h"
#include "util.h"

namespace PIM
{

	/*
	 * Constructor
	 */
	Organization::Organization():
		mIsPrimary(false)
	{

	}

	/*
	 * Read a complete organization.
	 */
	void Organization::read(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: organization read");
		args.field = MA_PIM_FIELD_CONTACT_ORG;
		args.bufSize = BUF_SIZE;
		if (maPimItemGetValue(&args, index) >=0 )
		{
			readName(args.buf);
		}

		args.field = MA_PIM_FIELD_CONTACT_TITLE;
		args.bufSize = BUF_SIZE;
		if (maPimItemGetValue(&args, index) >=0 )
		{
			readTitle(args.buf);
		}

		args.field = MA_PIM_FIELD_CONTACT_ORG_INFO;
		args.bufSize = BUF_SIZE;
		if (maPimItemGetValue(&args, index) > 0)
		{
			readDepartment(args.buf);
			readLocation(args.buf);
			readJobDescription(args.buf);
			readPhoneticName(args.buf);
			readSymbol(args.buf);

			readType(args.item, index);
			readLabel(args.item, index);
		}
	}

	void Organization::readName(const MAAddress buffer)
	{
		DELETE(mName);
		wchar* src = (wchar*)buffer;
		mName = wcsdup(src);
	}

	void Organization::readTitle(const MAAddress buffer)
	{
		DELETE(mTitle);
		wchar* src = (wchar*)buffer;
		mTitle = wcsdup(src);
	}

	void Organization::readDepartment(const MAAddress buffer)
	{
		mDepartment = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_ORG_INFO_DEPARTMENT);
	}

	void Organization::readLocation(const MAAddress buffer)
	{
		mLocation = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_ORG_INFO_OFFICE_LOCATION);
	}

	void Organization::readJobDescription(const MAAddress buffer)
	{
		mJobDescription = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_ORG_INFO_JOB_DESCRIPTION);
	}

	void Organization::readPhoneticName(const MAAddress buffer)
	{
		mPhoneticName = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_ORG_INFO_PHONETIC_NAME);
	}

	void Organization::readSymbol(const MAAddress buffer)
	{
		mSymbol = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_ORG_INFO_SYMBOL);
	}

	void Organization::readType(const MAHandle handle, const int index)
	{
		int attribute = maPimItemGetAttributes(handle, MA_PIM_FIELD_CONTACT_ORG, index);

		if (attribute >> 16)
		{
			mIsPrimary = true;

			// Remove primary value from attribute.
			attribute = (attribute & 0xFFFF);
		}

		switch (attribute)
		{
			case MA_PIM_ATTR_ORG_WORK:
				mType = ORGANIZATION_WORK;
				break;
			case MA_PIM_ATTR_ORG_CUSTOM:
				mType = ORGANIZATION_CUSTOM;
				break;
			default:
				mType = ORGANIZATION_OTHER;
				break;
		}
	}

	void Organization::readLabel(const MAHandle handle, const int index)
	{
		MA_PIM_ARGS args;
		args.item = handle;
		args.field = MA_PIM_FIELD_CONTACT_ORG;
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
	 * Getter for name.
	 */
	const wchar* Organization::getName() const
	{
		return mName;
	}

	/*
	 * Setter for name.
	 */
	void Organization::setName(wchar* name)
	{
		mName = name;
	}

	/*
	 * Getter for title.
	 */
	const wchar* Organization::getTitle() const
	{
		return mTitle;
	}

	/*
	 * Setter for title.
	 */
	void Organization::setTitle(wchar* title)
	{
		mTitle = title;
	}

	/*
	 * Getter for department.
	 */
	const wchar* Organization::getDepartment() const
	{
		return mDepartment;
	}

	/*
	 * Setter for department.
	 */
	void Organization::setDepartment(wchar* department)
	{
		mDepartment = department;
	}

	/*
	 * Getter for location.
	 */
	const wchar* Organization::getLocation() const
	{
		return mLocation;
	}

	/*
	 * Setter for location.
	 */
	void Organization::setLocation(wchar* location)
	{
		mLocation = location;
	}

	/*
	 * Getter for job description.
	 */
	const wchar* Organization::getJobDescription() const
	{
		return mJobDescription;
	}

	/*
	 * Setter for job description.
	 */
	void Organization::setJobDescription(wchar* jobDescription)
	{
		mJobDescription = jobDescription;
	}

	/*
	 * Getter for phonetic name.
	 */
	const wchar* Organization::getPhoneticName() const
	{
		return mPhoneticName;
	}

	/*
	 * Setter for phonetic name.
	 */
	void Organization::setPhoneticName(wchar* phoneticName)
	{
		mPhoneticName = phoneticName;
	}

	/*
	 * Getter for symbol.
	 */
	const wchar* Organization::getSymbol() const
	{
		return mSymbol;
	}

	/*
	 * Setter for symbol.
	 */
	void Organization::setSymbol(wchar* symbol)
	{
		mSymbol = symbol;
	}

	/*
	 * Getter for type.
	 */
	const eOrganizationTypes& Organization::getType() const
	{
		return mType;
	}

	/*
	 * Setter for type.
	 */
	void Organization::setType(const eOrganizationTypes& type)
	{
		mType = type;
	}

	/*
	 * Getter for label.
	 */
	const wchar* Organization::getLabel() const
	{
		return mLabel;
	}

	/*
	 * Setter for label.
	 */
	void Organization::setLabel(wchar* label)
	{
		mLabel = label;
	}

	/*
	 * Returns true if this is the primary organization.
	 */
	const bool Organization::isPrimary() const
	{
		return mIsPrimary;
	}

} //PIM

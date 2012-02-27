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
		//CHECK_RESULT(maPimItemGetValue(&args, 0));
		if (maPimItemGetValue(&args, index) >=0 )
		{
			readName(args.buf);
		}

		args.field = MA_PIM_FIELD_CONTACT_TITLE;
		//CHECK_RESULT(maPimItemGetValue(&args, 0));
		if (maPimItemGetValue(&args, index) >=0 )
		{
			readTitle(args.buf);
		}

		args.field = MA_PIM_FIELD_CONTACT_ORG_INFO;
		//CHECK_RESULT(maPimItemGetValue(&args, 0));
		if (maPimItemGetValue(&args, index))
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

	void Organization::readName(MAAddress const buffer)
	{
		DELETE(mName);
		wchar* src = (wchar*)buffer;
		int len = wcslen(src);
		mName = new wchar[len + 1];
		wcsncpy(mName, src, len);
	}

	void Organization::readTitle(MAAddress const buffer)
	{
		DELETE(mTitle);
		wchar* src = (wchar*)buffer;
		int len = wcslen(src);
		mTitle = new wchar[len + 1];
		wcsncpy(mTitle, src, len);
	}

	void Organization::readDepartment(MAAddress const buffer)
	{
		mDepartment = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_ORG_INFO_DEPARTMENT);
	}

	void Organization::readLocation(MAAddress const buffer)
	{
		mLocation = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_ORG_INFO_OFFICE_LOCATION);
	}

	void Organization::readJobDescription(MAAddress const buffer)
	{
		mJobDescription = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_ORG_INFO_JOB_DESCRIPTION);
	}

	void Organization::readPhoneticName(MAAddress const buffer)
	{
		mPhoneticName = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_ORG_INFO_PHONETIC_NAME);
	}

	void Organization::readSymbol(MAAddress const buffer)
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
	 * Getter for name.
	 */
	const wchar* Organization::getName() const
	{
		return mName;
	}

	/*
	 * Setter for name.
	 */
	void Organization::setName(wchar* const name)
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
	void Organization::setTitle(wchar* const title)
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
	void Organization::setDepartment(wchar* const department)
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
	void Organization::setLocation(wchar* const location)
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
	void Organization::setJobDescription(wchar* const jobDescription)
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
	void Organization::setPhoneticName(wchar* const phoneticName)
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
	void Organization::setSymbol(wchar* const symbol)
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
	void Organization::setLabel(wchar* const label)
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

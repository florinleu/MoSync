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
	/**
	 * Constructor.
	 */
	Organization::Organization():
		mName(NULL),
		mTitle(NULL),
		mDepartment(NULL),
		mLocation(NULL),
		mJobDescription(NULL),
		mPhoneticName(NULL),
		mSymbol(NULL),
		mLabel(NULL),
		mIsPrimary(false)
	{

	}

	/**
	 * Destructor.
	 */
	Organization::~Organization()
	{
		DELETE(mName);
		DELETE(mTitle);
		DELETE(mDepartment);
		DELETE(mLocation);
		DELETE(mJobDescription);
		DELETE(mPhoneticName);
		DELETE(mSymbol);
		DELETE(mLabel);
	}

	/**
	 * Reads a contact's organization.
	 * @param args The arguments needed to read the organization.
	 * @param index The index of the organization to read.
	 */
	void Organization::read(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: organization read");
		args.field = MA_PIM_FIELD_CONTACT_ORG;
		args.bufSize = PIM_BUF_SIZE;
		if (maPimItemGetValue(&args, index) >=0 )
		{
			wchar* src = (wchar*)args.buf;
			mName = wcsdup(src);
		}

		args.field = MA_PIM_FIELD_CONTACT_TITLE;
		args.bufSize = PIM_BUF_SIZE;
		if (maPimItemGetValue(&args, index) >=0 )
		{
			wchar* src = (wchar*)args.buf;
			mTitle = wcsdup(src);
		}

		args.field = MA_PIM_FIELD_CONTACT_ORG_INFO;
		args.bufSize = PIM_BUF_SIZE;
		if (maPimItemGetValue(&args, index) > 0)
		{
			mDepartment = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_ORG_INFO_DEPARTMENT);
			mLocation = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_ORG_INFO_OFFICE_LOCATION);
			mJobDescription = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_ORG_INFO_JOB_DESCRIPTION);
			mPhoneticName = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_ORG_INFO_PHONETIC_NAME);
			mSymbol = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_ORG_INFO_SYMBOL);

			readType(args.item, index);
			readLabel(args.item, index);
		}
	}


	/**
	 * Writes a contact's organization.
	 * @param args The values to write.
	 * @index args The index of the organization to write.
	 */
	void Organization::write(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: organization write");

		args.field = MA_PIM_FIELD_CONTACT_ORG;
		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeWString(args.buf, mName, 0);
		maPimItemSetValue(&args, index, 0);

		args.field = MA_PIM_FIELD_CONTACT_TITLE;
		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeWString(args.buf, mTitle, 0);
		maPimItemSetValue(&args, index, 0);

		args.field = MA_PIM_FIELD_CONTACT_ORG_INFO;
		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeInt(args.buf, MA_PIM_CONTACT_ORG_INFO_COUNT, 0);
		args.bufSize += writeWString(args.buf, mDepartment, args.bufSize);
		args.bufSize += writeWString(args.buf, mJobDescription, args.bufSize);
		args.bufSize += writeWString(args.buf, mSymbol, args.bufSize);
		args.bufSize += writeWString(args.buf, mPhoneticName, args.bufSize);
		args.bufSize += writeWString(args.buf, mLocation, args.bufSize);
		args.bufSize += writeWString(args.buf, NULL, args.bufSize);
		maPimItemSetValue(&args, index, getAttribute());

		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeWString(args.buf, mLabel, 0);
		maPimItemSetLabel(&args, index);
	}

	/**
	 * Deletes a contact's organization.
	 * @param handle The handle of the contact.
	 * @param index  The index of the organization to delete.
	 */
	void Organization::remove(MAHandle handle, int index)
	{
		printf("@LIB: organization delete");

		maPimItemRemoveValue(handle, MA_PIM_FIELD_CONTACT_ORG, index);
		maPimItemRemoveValue(handle, MA_PIM_FIELD_CONTACT_TITLE, index);
		maPimItemRemoveValue(handle, MA_PIM_FIELD_CONTACT_ORG_INFO, index);
	}

	/**
	 * Reads the type of the organization.
	 * @param handle The handle of the contact.
	 * @param index The index of this organization.
	 */
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
				mType = TYPE_WORK;
				break;
			case MA_PIM_ATTR_ORG_CUSTOM:
				mType = TYPE_CUSTOM;
				break;
			default:
				mType = TYPE_OTHER;
				break;
		}
	}

	/**
	 * Reads the label of the organization.
	 * @param handle The handle of the contact.
	 * @param index The index of this organization.
	 */
	void Organization::readLabel(const MAHandle handle, const int index)
	{
		MA_PIM_ARGS args;
		args.item = handle;
		args.field = MA_PIM_FIELD_CONTACT_ORG;
		args.bufSize = PIM_BUF_SIZE;

		char buf[PIM_BUF_SIZE];
		args.buf = buf;
		args.bufSize = PIM_BUF_SIZE;
		maPimItemGetLabel(&args, index);

		wchar* src = (wchar*)args.buf;
		mLabel = wcsdup(src);
	}

	/**
	 * Gets the contact's organization name.
	 * @return The organization name of the contact.
	 */
	const wchar* const Organization::getName() const
	{
		return mName;
	}

	/**
	 * Sets the contact's organization name.
	 * @param name The value to set.
	 */
	void Organization::setName(const wchar* const name)
	{
		DELETE(mName);
		mName = wcsdup(name);
	}

	/**
	 * Gets the contact's title.
	 * @return The title of the contact.
	 */
	const wchar* const Organization::getTitle() const
	{
		return mTitle;
	}

	/**
	 * Sets the contact's title.
	 * @param title The value to set.
	 */
	void Organization::setTitle(const wchar* const title)
	{
		DELETE(mTitle);
		mTitle = wcsdup(title);
	}

	/**
	 * Gets the contact's department.
	 * @return The department of the contact.
	 */
	const wchar* const Organization::getDepartment() const
	{
		return mDepartment;
	}

	/**
	 * Sets the contact's department.
	 * @param department The value to set.
	 */
	void Organization::setDepartment(const wchar* const department)
	{
		DELETE(mDepartment);
		mDepartment = wcsdup(department);
	}

	/**
	 * Gets the contact's organization location.
	 * @return The organization location of the contact.
	 */
	const wchar* const Organization::getLocation() const
	{
		return mLocation;
	}

	/**
	 * Sets the contact's organization location.
	 * @param location The value to set.
	 */
	void Organization::setLocation(const wchar* const location)
	{
		DELETE(mLocation);
		mLocation = wcsdup(location);
	}

	/**
	 * Gets the contact's job description.
	 * @return The job description of the contact.
	 */
	const wchar* const Organization::getJobDescription() const
	{
		return mJobDescription;
	}

	/**
	 * Sets the contact's job description.
	 * @param jobDescription The value to set.
	 */
	void Organization::setJobDescription(const wchar* const jobDescription)
	{
		DELETE(mJobDescription);
		mJobDescription = wcsdup(jobDescription);
	}

	/**
	 * Gets the contact's organization phonetic name.
	 * @return The organization phonetic name of the contact.
	 */
	const wchar* const Organization::getPhoneticName() const
	{
		return mPhoneticName;
	}

	/**
	 * Sets the contact's organization phonetic name.
	 * @param phoneticName The value to set.
	 */
	void Organization::setPhoneticName(const wchar* const phoneticName)
	{
		DELETE(mPhoneticName);
		mPhoneticName = wcsdup(phoneticName);
	}

	/**
	 * Gets the contact's organization symbol.
	 * @return The organization symbol of the contact.
	 */
	const wchar* const Organization::getSymbol() const
	{
		return mSymbol;
	}

	/**
	 * Sets the contact's organization symbol.
	 * @param symbol The value to set.
	 */
	void Organization::setSymbol(const wchar* const symbol)
	{
		DELETE(mSymbol);
		mSymbol = wcsdup(symbol);
	}

	/**
	 * Gets the organization type.
	 * @return The type of the organization.
	 */
	const Organization::eTypes& Organization::getType() const
	{
		return mType;
	}

	/**
	 * Sets the organization type.
	 * @param type The value to set.
	 */
	void Organization::setType(const Organization::eTypes& type)
	{
		mType = type;
	}

	/**
	 * Gets the organization label.
	 * @return The label of the organization.
	 */
	const wchar* const Organization::getLabel() const
	{
		return mLabel;
	}

	/**
	 * Sets the organization label.
	 * @param state The value to set.
	 */
	void Organization::setLabel(const wchar* const label)
	{
		DELETE(mLabel);
		mLabel = wcsdup(label);
	}

	/**
	 * Checks if this is or not a primary organization.
	 * @return True if this is a primary organization.
	 */
	const bool Organization::isPrimary() const
	{
		return mIsPrimary;
	}

	/**
	 * Sets this as a primary organization.
	 * @param primary true if this is a primary organization.
	 */
	void Organization::setPrimary(const bool primary)
	{
		mIsPrimary = primary;
	}

	/**
	 * Computes the organization attribute.
	 * @return The organization attribute.
	 */
	const int Organization::getAttribute() const
	{
		int attribute = 0;
		switch (mType)
		{
			case TYPE_WORK:
				attribute = MA_PIM_ATTR_ORG_WORK;
				break;
			case TYPE_CUSTOM:
				attribute = MA_PIM_ATTR_ORG_CUSTOM;
				break;
			default:
				attribute = MA_PIM_ATTR_ORG_OTHER;
				break;
		}

		attribute |= (mIsPrimary ? MA_PIM_ATTRPREFERRED : 0);

		return attribute;
	}

} //PIM

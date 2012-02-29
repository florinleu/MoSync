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
 * @file Relation.cpp
 * @author Florin Leu
 * @date 28 Feb 2011
 *
 * @brief PIM Field Relation class.
 *
 **/

#include <conprint.h>
#include <mawstring.h>
#include "Relation.h"

#include "util.h"

namespace PIM
{

	/*
	 * Constructor
	 */
	Relation::Relation():
		mIsPrimary(false)
	{

	}

	/*
	 * Read a complete relation.
	 */
	void Relation::read(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: relation read");
		args.field = MA_PIM_FIELD_CONTACT_RELATION;
		//CHECK_RESULT(maPimItemGetValue(&args, 0));
		if (maPimItemGetValue(&args, index))
		{
			readName(args.buf);

			readType(args.item, index);
			readLabel(args.item, index);
		}
	}

	void Relation::readName(MAAddress const buffer)
	{
		DELETE(mName);
		wchar* src = (wchar*)buffer;
		int len = wcslen(src);
		mName = new wchar[len + 1];
		wcsncpy(mName, src, len);
	}

	void Relation::readType(const MAHandle handle, const int index)
	{
		int attribute = maPimItemGetAttributes(handle, MA_PIM_FIELD_CONTACT_RELATION, index);

		if (attribute >> 16)
		{
			mIsPrimary = true;

			// Remove primary value from attribute.
			attribute = (attribute & 0xFFFF);
		}

		switch (attribute)
		{
			case MA_PIM_ATTR_RELATION_MOTHER:
				mType = RELATION_MOTHER;
				break;
			case MA_PIM_ATTR_RELATION_FATHER:
				mType = RELATION_FATHER;
				break;
			case MA_PIM_ATTR_RELATION_PARENT:
				mType = RELATION_PARENT;
				break;
			case MA_PIM_ATTR_RELATION_SISTER:
				mType = RELATION_SISTER;
				break;
			case MA_PIM_ATTR_RELATION_BROTHER:
				mType = RELATION_BROTHER;
				break;
			case MA_PIM_ATTR_RELATION_CHILD:
				mType = RELATION_CHILD;
				break;
			case MA_PIM_ATTR_RELATION_FRIEND:
				mType = RELATION_FRIEND;
				break;
			case MA_PIM_ATTR_RELATION_SPOUSE:
				mType = RELATION_SPOUSE;
				break;
			case MA_PIM_ATTR_RELATION_PARTNER:
				mType = RELATION_PARTNER;
				break;
			case MA_PIM_ATTR_RELATION_MANAGER:
				mType = RELATION_MANAGER;
				break;
			case MA_PIM_ATTR_RELATION_ASSISTANT:
				mType = RELATION_ASSISTANT;
				break;
			case MA_PIM_ATTR_RELATION_DOMESTIC_PARTNER:
				mType = RELATION_DOMESTIC_PARTNER;
				break;
			case MA_PIM_ATTR_RELATION_REFERRED_BY:
				mType = RELATION_REFERRED_BY;
				break;
			case MA_PIM_ATTR_RELATION_RELATIVE:
				mType = RELATION_RELATIVE;
				break;
			default:
				mType = RELATION_CUSTOM;
				break;
		}
	}

	void Relation::readLabel(const MAHandle handle, const int index)
	{
		MA_PIM_ARGS args;
		args.item = handle;
		args.field = MA_PIM_FIELD_CONTACT_RELATION;

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
	const wchar* Relation::getName() const
	{
		return mName;
	}

	/*
	 * Setter for name.
	 */
	void Relation::setName(wchar* const name)
	{
		mName = name;
	}

	/*
	 * Getter for type.
	 */
	const eRelationTypes& Relation::getType() const
	{
		return mType;
	}

	/*
	 * Setter for type.
	 */
	void Relation::setType(const eRelationTypes& type)
	{
		mType = type;
	}

	/*
	 * Getter for label.
	 */
	const wchar* Relation::getLabel() const
	{
		return mLabel;
	}

	/*
	 * Setter for label.
	 */
	void Relation::setLabel(wchar* const label)
	{
		mLabel = label;
	}

	/*
	 * Returns true if this is set as the primary relation.
	 */
	const bool Relation::isPrimary() const
	{
		return mIsPrimary;
	}
} //PIM

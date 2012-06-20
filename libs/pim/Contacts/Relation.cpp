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
	/**
	 * Constructor.
	 */
	Relation::Relation():
		mName(NULL),
		mLabel(NULL),
		mIsPrimary(false)
	{

	}

	/**
	 * Destructor.
	 */
	Relation::~Relation()
	{
		DELETE(mName);
		DELETE(mLabel);
	}

	/**
	 * Reads a contact's relation.
	 * @param args The arguments needed to read the relation.
	 * @param index The index of the relation to read.
	 */
	void Relation::read(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: relation read");
		args.field = MA_PIM_FIELD_CONTACT_RELATION;
		args.bufSize = PIM_BUF_SIZE;
		if (maPimItemGetValue(&args, index) >= 0)
		{
			wchar* src = (wchar*)args.buf;
			mName = wcsdup(src);

			readType(args.item, index);
			readLabel(args.item, index);
		}
	}

	/**
	 * Writes a contact's relation.
	 * @param args The values to write.
	 * @index args The index of the relation to write.
	 */
	void Relation::write(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: relation write");

		args.field = MA_PIM_FIELD_CONTACT_RELATION;
		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeWString(args.buf, mName, 0);
		maPimItemSetValue(&args, index, getAttribute());

		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeWString(args.buf, mLabel, 0);
		maPimItemSetLabel(&args, index);
	}

	/**
	 * Adds a new relation to this contact.
	 */
	void Relation::add(MA_PIM_ARGS& args)
	{
		args.field = MA_PIM_FIELD_CONTACT_RELATION;
		maPimItemAddValue(&args, MA_PIM_ATTR_RELATION_MOTHER);
	}

	/**
	 * Deletes a contact's relation.
	 * @param handle The handle of the contact.
	 * @param index  The index of the relation to delete.
	 */
	void Relation::remove(MAHandle handle, int index)
	{
		printf("@LIB: relation delete");

		maPimItemRemoveValue(handle, MA_PIM_FIELD_CONTACT_RELATION, index);
	}

	/**
	 * Reads the type of the relation.
	 * @param handle The handle of the contact.
	 * @param index The index of this relation.
	 */
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
				mType = TYPE_MOTHER;
				break;
			case MA_PIM_ATTR_RELATION_FATHER:
				mType = TYPE_FATHER;
				break;
			case MA_PIM_ATTR_RELATION_PARENT:
				mType = TYPE_PARENT;
				break;
			case MA_PIM_ATTR_RELATION_SISTER:
				mType = TYPE_SISTER;
				break;
			case MA_PIM_ATTR_RELATION_BROTHER:
				mType = TYPE_BROTHER;
				break;
			case MA_PIM_ATTR_RELATION_CHILD:
				mType = TYPE_CHILD;
				break;
			case MA_PIM_ATTR_RELATION_FRIEND:
				mType = TYPE_FRIEND;
				break;
			case MA_PIM_ATTR_RELATION_SPOUSE:
				mType = TYPE_SPOUSE;
				break;
			case MA_PIM_ATTR_RELATION_PARTNER:
				mType = TYPE_PARTNER;
				break;
			case MA_PIM_ATTR_RELATION_MANAGER:
				mType = TYPE_MANAGER;
				break;
			case MA_PIM_ATTR_RELATION_ASSISTANT:
				mType = TYPE_ASSISTANT;
				break;
			case MA_PIM_ATTR_RELATION_DOMESTIC_PARTNER:
				mType = TYPE_DOMESTIC_PARTNER;
				break;
			case MA_PIM_ATTR_RELATION_REFERRED_BY:
				mType = TYPE_REFERRED_BY;
				break;
			case MA_PIM_ATTR_RELATION_RELATIVE:
				mType = TYPE_RELATIVE;
				break;
			default:
				mType = TYPE_CUSTOM;
				break;
		}
	}

	/**
	 * Reads the label of the relation.
	 * @param handle The handle of the contact.
	 * @param index The index of this relation.
	 */
	void Relation::readLabel(const MAHandle handle, const int index)
	{
		MA_PIM_ARGS args;
		args.item = handle;
		args.field = MA_PIM_FIELD_CONTACT_RELATION;
		args.bufSize = PIM_BUF_SIZE;

		char buf[PIM_BUF_SIZE];
		args.buf = buf;
		args.bufSize = PIM_BUF_SIZE;
		maPimItemGetLabel(&args, index);

		wchar* src = (wchar*)args.buf;
		mLabel = wcsdup(src);
	}

	/**
	 * Gets the contact's relation name.
	 * @return The relation name of the contact.
	 */
	const wchar* const Relation::getName() const
	{
		return mName;
	}

	/**
	 * Sets the contact's relation name.
	 * @param name The value to set.
	 */
	void Relation::setName(const wchar* const name)
	{
		DELETE(mName);
		mName = wcsdup(name);
	}

	/**
	 * Gets the relation type.
	 * @return The type of the relation.
	 */
	const Relation::eTypes& Relation::getType() const
	{
		return mType;
	}

	/**
	 * Sets the relation type.
	 * @param type The value to set.
	 */
	void Relation::setType(const Relation::eTypes& type)
	{
		mType = type;
	}

	/**
	 * Gets the relation label.
	 * @return The label of the relation.
	 */
	const wchar* const Relation::getLabel() const
	{
		return mLabel;
	}

	/**
	 * Sets the relation label.
	 * @param label The value to set.
	 */
	void Relation::setLabel(const wchar* const label)
	{
		DELETE(mLabel);
		mLabel = wcsdup(label);
	}

	/**
	 * Checks if this is or not a primary relation.
	 * @return True if this is a primary relation.
	 */
	const bool Relation::isPrimary() const
	{
		return mIsPrimary;
	}

	/**
	 * Sets this as a primary relation.
	 * @param primary true if this is a primary relation.
	 */
	void Relation::setPrimary(const bool primary)
	{
		mIsPrimary = primary;
	}

	/**
	 * Computes the relation attribute.
	 * @return The relation attribute.
	 */
	const int Relation::getAttribute() const
	{
		int attribute = 0;
		switch (mType)
		{
			case TYPE_MOTHER:
				attribute = MA_PIM_ATTR_RELATION_MOTHER;
				break;
			case TYPE_FATHER:
				attribute = MA_PIM_ATTR_RELATION_FATHER;
				break;
			case TYPE_PARENT:
				attribute = MA_PIM_ATTR_RELATION_PARENT;
				break;
			case TYPE_SISTER:
				attribute = MA_PIM_ATTR_RELATION_SISTER;
				break;
			case TYPE_BROTHER:
				attribute = MA_PIM_ATTR_RELATION_BROTHER;
				break;
			case TYPE_CHILD:
				attribute = MA_PIM_ATTR_RELATION_CHILD;
				break;
			case TYPE_FRIEND:
				attribute = MA_PIM_ATTR_RELATION_FRIEND;
				break;
			case TYPE_SPOUSE:
				attribute = MA_PIM_ATTR_RELATION_SPOUSE;
				break;
			case TYPE_PARTNER:
				attribute = MA_PIM_ATTR_RELATION_PARTNER;
				break;
			case TYPE_MANAGER:
				attribute = MA_PIM_ATTR_RELATION_MANAGER;
				break;
			case TYPE_ASSISTANT:
				attribute = MA_PIM_ATTR_RELATION_ASSISTANT;
				break;
			case TYPE_DOMESTIC_PARTNER:
				attribute = MA_PIM_ATTR_RELATION_DOMESTIC_PARTNER;
				break;
			case TYPE_REFERRED_BY:
				attribute = MA_PIM_ATTR_RELATION_REFERRED_BY;
				break;
			case TYPE_RELATIVE:
				attribute = MA_PIM_ATTR_RELATION_RELATIVE;
				break;
			default:
				attribute = MA_PIM_ATTR_RELATION_CUSTOM;
				break;
		}

		attribute |= (mIsPrimary ? MA_PIM_ATTRPREFERRED : 0);

		return attribute;
	}

} //PIM

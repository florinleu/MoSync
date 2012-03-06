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
 * @file Relation.h
 * @author Florin Leu
 * @date 09 Feb 2011
 *
 * @brief PIM Field Relation class.
 *
 **/

#ifndef __RELATION_H__
#define __RELATION_H__

#include <IX_PIM.h>

namespace PIM
{

	enum eRelationTypes
	{
		/// The constant describes a mother relation.
		RELATION_MOTHER = 0,
		/// The constant describes a father relation.
		RELATION_FATHER,
		/// The constant describes a parent relation.
		RELATION_PARENT,
		/// The constant describes a sister relation.
		RELATION_SISTER,
		/// The constant describes a brother relation.
		RELATION_BROTHER,
		/// The constant describes a child relation.
		RELATION_CHILD,
		/// The constant describes a friend relation.
		RELATION_FRIEND,
		/// The constant describes a spouse relation.
		RELATION_SPOUSE,
		/// The constant describes a partner relation.
		RELATION_PARTNER,
		/// The constant describes a manager relation.
		RELATION_MANAGER,
		/// The constant describes a assistant relation.
		RELATION_ASSISTANT,
		/// The constant describes a domestic partner relation.
		RELATION_DOMESTIC_PARTNER,
		/// The constant describes a referred by relation.
		RELATION_REFERRED_BY,
		/// The constant describes a relative relation.
		RELATION_RELATIVE,
		/// The constant describes a custom relation type.
		RELATION_CUSTOM
	};

	class Relation
	{
		public:
			Relation();

			void read(MA_PIM_ARGS& args, int index);

			const wchar* getName() const;
			void setName(wchar* name);

			const eRelationTypes& getType() const;
			void setType(const eRelationTypes& type);

			const wchar* getLabel() const;
			void setLabel(wchar* label);

			const bool isPrimary() const;

		private:
			void readName(const MAAddress buffer);

			void readType(const MAHandle handle, const int index);
			void readLabel(const MAHandle handle, const int index);

		private:
			//The name of the relative.
			wchar* mName;

			//The type of data.
			eRelationTypes mType;
			//The user defined label
			wchar* mLabel;
			//Shows if this is a primary phone number or not.
			bool mIsPrimary;
	};

} //PIM

#endif //__RELATION_H__

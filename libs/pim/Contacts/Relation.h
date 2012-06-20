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
	class Relation
	{
		public:
			enum eTypes
			{
				/// The constant describes a mother relation.
				TYPE_MOTHER = 0,
				/// The constant describes a father relation.
				TYPE_FATHER,
				/// The constant describes a parent relation.
				TYPE_PARENT,
				/// The constant describes a sister relation.
				TYPE_SISTER,
				/// The constant describes a brother relation.
				TYPE_BROTHER,
				/// The constant describes a child relation.
				TYPE_CHILD,
				/// The constant describes a friend relation.
				TYPE_FRIEND,
				/// The constant describes a spouse relation.
				TYPE_SPOUSE,
				/// The constant describes a partner relation.
				TYPE_PARTNER,
				/// The constant describes a manager relation.
				TYPE_MANAGER,
				/// The constant describes a assistant relation.
				TYPE_ASSISTANT,
				/// The constant describes a domestic partner relation.
				TYPE_DOMESTIC_PARTNER,
				/// The constant describes a referred by relation.
				TYPE_REFERRED_BY,
				/// The constant describes a relative relation.
				TYPE_RELATIVE,
				/// The constant describes a custom relation type.
				TYPE_CUSTOM
			};

			enum eSubFields
			{
				//The constant describes a relation name.
				NAME = 0,
			};

		public:
			/**
			 * Constructor.
			 */
			Relation();

			/**
			 * Destructor.
			 */
			~Relation();

			/**
			 * Reads a contact's relation.
			 * @param args The arguments needed to read the relation.
			 * @param index The index of the relation to read.
			 */
			void read(MA_PIM_ARGS& args, int index);

			/**
			 * Writes a contact's relation.
			 * @param args The values to write.
			 * @index args The index of the relation to write.
			 */
			void write(MA_PIM_ARGS& args, int index);

			/**
			 * Adds a new relation to this contact.
			 * @param args The values to add.
			 */
			void add(MA_PIM_ARGS& args);

			/**
			 * Deletes a contact's relation.
			 * @param handle The handle of the contact.
			 * @param index  The index of the relation to delete.
			 */
			void remove(MAHandle handle, int index);

			/**
			 * Gets the contact's relation name.
			 * @return The relation name of the contact.
			 */
			const wchar* const getName() const;

			/**
			 * Sets the contact's relation name.
			 * @param name The value to set.
			 */
			void setName(const wchar* const name);

			/**
			 * Gets the relation type.
			 * @return The type of the relation.
			 */
			const eTypes& getType() const;

			/**
			 * Sets the relation type.
			 * @param type The value to set.
			 */
			void setType(const eTypes& type);

			/**
			 * Gets the relation label.
			 * @return The label of the relation.
			 */
			const wchar* const getLabel() const;

			/**
			 * Sets the relation label.
			 * @param state The value to set.
			 */
			void setLabel(const wchar* const label);

			/**
			 * Checks if this is or not a primary relation.
			 * @return True if this is a primary relation.
			 */
			const bool isPrimary() const;

			/**
			 * Sets this as a primary relation.
			 * @param primary true if this is a primary relation.
			 */
			void setPrimary(const bool primary);

		private:
			/**
			 * Reads the type of the relation.
			 * @param handle The handle of the contact.
			 * @param index The index of this relation.
			 */
			void readType(const MAHandle handle, const int index);

			/**
			 * Reads the label of the relation.
			 * @param handle The handle of the contact.
			 * @param index The index of this relation.
			 */
			void readLabel(const MAHandle handle, const int index);

			/**
			 * Computes the relation attribute.
			 * @return The relation attribute.
			 */
			const int getAttribute() const;

		private:
			//The name of the relation.
			wchar* mName;

			//The type of data.
			eTypes mType;
			//The user defined label.
			wchar* mLabel;
			//Shows if this is a primary relation or not.
			bool mIsPrimary;
	};

} //PIM

#endif //__RELATION_H__

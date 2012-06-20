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
 * @file Organization.h
 * @author Florin Leu
 * @date 09 Feb 2011
 *
 * @brief PIM Field Organization class.
 *
 **/

#ifndef __ORGANIZATION_H__
#define __ORGANIZATION_H__

#include <IX_PIM.h>

namespace PIM
{
	class Organization
	{
		public:
			enum eTypes
			{
				//The constant describes a work organization.
				TYPE_WORK = 0,
				//The constant describes a different organization type.
				TYPE_OTHER,
				//The constant describes a custom organization type.
				//The field's label can be set.
				TYPE_CUSTOM
			};

			enum eSubFields
			{
				//The constant describes a name.
				NAME = 0,
				//The constant describes a job title.
				TITLE,
				//The constant describes a department.
				DEPARTMENT,
				//The constant describes a location.
				LOCATION,
				//The constant describes a job description.
				JOB_DESCRIPTION,
				//The constant describes a phonetic name.
				PHONETIC_NAME,
				//The constant describes a symbol.
				SYMBOL
			};
		public:
			/**
			 * Constructor.
			 */
			Organization();

			/**
			 * Destructor.
			 */
			~Organization();

			/**
			 * Reads a contact's organization.
			 * @param args The arguments needed to read the organization.
			 * @param index The index of the organization to read.
			 */
			void read(MA_PIM_ARGS& args, int index);

			/**
			 * Writes a contact's organization.
			 * @param args The values to write.
			 * @param index The index of the organization to write.
			 */
			void write(MA_PIM_ARGS& args, int index);

			/**
			 * Adds a new organization to this contact.
			 * @param args The values to add.
			 */
			void add(MA_PIM_ARGS& args);

			/**
			 * Deletes a contact's organization.
			 * @param handle The handle of the contact.
			 * @param index  The index of the organization to delete.
			 */
			void remove(MAHandle handle, int index);

			/**
			 * Gets the contact's organization name.
			 * @return The organization name of the contact.
			 */
			const wchar* const getName() const;

			/**
			 * Sets the contact's organization name.
			 * @param name The value to set.
			 */
			void setName(const wchar* const name);

			/**
			 * Gets the contact's title.
			 * @return The title of the contact.
			 */
			const wchar* const getTitle() const;

			/**
			 * Sets the contact's title.
			 * @param title The value to set.
			 */
			void setTitle(const wchar* const title);

			/**
			 * Gets the contact's department.
			 * @return The department of the contact.
			 */
			const wchar* const getDepartment() const;

			/**
			 * Sets the contact's department.
			 * @param department The value to set.
			 */
			void setDepartment(const wchar* const department);

			/**
			 * Gets the contact's organization location.
			 * @return The organization location of the contact.
			 */
			const wchar* const getLocation() const;

			/**
			 * Sets the contact's organization location.
			 * @param location The value to set.
			 */
			void setLocation(const wchar* const location);

			/**
			 * Gets the contact's job description.
			 * @return The job description of the contact.
			 */
			const wchar* const getJobDescription() const;

			/**
			 * Sets the contact's job description.
			 * @param jobDescription The value to set.
			 */
			void setJobDescription(const wchar* const jobDescription);

			/**
			 * Gets the contact's organization phonetic name.
			 * @return The organization phonetic name of the contact.
			 */
			const wchar* const getPhoneticName() const;

			/**
			 * Sets the contact's organization phonetic name.
			 * @param phoneticName The value to set.
			 */
			void setPhoneticName(const wchar* const phoneticName);

			/**
			 * Gets the contact's organization symbol.
			 * @return The organization symbol of the contact.
			 */
			const wchar* const getSymbol() const;

			/**
			 * Sets the contact's organization symbol.
			 * @param symbol The value to set.
			 */
			void setSymbol(const wchar* const symbol);


			/**
			 * Gets the organization type.
			 * @return The type of the organization.
			 */
			const eTypes& getType() const;

			/**
			 * Sets the organization type.
			 * @param type The value to set.
			 */
			void setType(const eTypes& type);

			/**
			 * Gets the organization label.
			 * @return The label of the organization.
			 */
			const wchar* const getLabel() const;

			/**
			 * Sets the organization label.
			 * @param state The value to set.
			 */
			void setLabel(const wchar* const label);

			/**
			 * Checks if this is or not a primary organization.
			 * @return True if this is a primary organization.
			 */
			const bool isPrimary() const;

			/**
			 * Sets this as a primary organization.
			 * @param primary true if this is a primary organization.
			 */
			void setPrimary(const bool primary);

		private:
			/**
			 * Reads the type of the organization.
			 * @param handle The handle of the contact.
			 * @param index The index of this organization.
			 */
			void readType(const MAHandle handle, const int index);

			/**
			 * Reads the label of the organization.
			 * @param handle The handle of the contact.
			 * @param index The index of this organization.
			 */
			void readLabel(const MAHandle handle, const int index);

			/**
			 * Computes the organization attribute.
			 * @return The organization attribute.
			 */
			const int getAttribute() const;

		private:
			//The company name.
			wchar* mName;
			//The job title at the company.
			wchar* mTitle;
			//The department at this company.
			wchar* mDepartment;
			//The office location of this company.
			wchar* mLocation;
			//The job description at this company
			wchar* mJobDescription;
			//The phonetic name of this company
			wchar* mPhoneticName;
			//The symbol of this company
			wchar* mSymbol;

			//The type of data.
			eTypes mType;
			//The user defined label.
			wchar* mLabel;
			//Shows if this is a primary address or not.
			bool mIsPrimary;
	};

} //PIM

#endif //__ORGANIZATION_H__

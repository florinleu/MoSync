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
 * @file Website.h
 * @author Florin Leu
 * @date 09 Feb 2011
 *
 * @brief PIM Field Website class.
 *
 **/

#ifndef __WEBSITE_H__
#define __WEBSITE_H__

#include <IX_PIM.h>

namespace PIM
{
	class Website
	{
		public:
			enum eTypes
			{
				//The constant describes a homepage website.
				TYPE_HOMEPAGE = 0,
				//The constant describes a blog website.
				TYPE_BLOG,
				//The constant describes a profile website.
				TYPE_PROFILE,
				//The constant describes a home website.
				TYPE_HOME,
				//The constant describes a work website.
				TYPE_WORK,
				//The constant describes a FTP website.
				TYPE_FTP,
				//The constant describes a different website type.
				TYPE_OTHER,
				//The constant describes a custom website type.
				//The field's label can be set.
				TYPE_CUSTOM
			};

			enum eSubFields
			{
				//The constant describes a website url.
				URL = 0,
			};

		public:
			/**
			 * Constructor.
			 */
			Website();

			/**
			 * Destructor.
			 */
			~Website();

			/**
			 * Reads a contact's website.
			 * @param args The arguments needed to read the website.
			 * @param index The index of the website to read.
			 */
			void read(MA_PIM_ARGS& args, int index);

			/**
			 * Writes a contact's website.
			 * @param args The values to write.
			 * @index args The index of the website to write.
			 */
			void write(MA_PIM_ARGS& args, int index);

			/**
			 * Deletes a contact's website.
			 * @param handle The handle of the contact.
			 * @param index  The index of the website to delete.
			 */
			void remove(MAHandle handle, int index);

			/**
			 * Gets the contact's website url.
			 * @return The url of the contact.
			 */
			const wchar* const getURL() const;

			/**
			 * Sets the contact's website url.
			 * @param url The value to set.
			 */
			void setURL(const wchar* const url);

			/**
			 * Gets the website type.
			 * @return The type of the website.
			 */
			const eTypes& getType() const;

			/**
			 * Sets the website type.
			 * @param type The value to set.
			 */
			void setType(const eTypes& type);

			/**
			 * Gets the website label.
			 * @return The label of the website.
			 */
			const wchar* const getLabel() const;

			/**
			 * Sets the website label.
			 * @param state The value to set.
			 */
			void setLabel(const wchar* const label);

			/**
			 * Checks if this is or not a primary website.
			 * @return True if this is a primary website.
			 */
			const bool isPrimary() const;

			/**
			 * Sets this as a primary website.
			 * @param primary true if this is a primary website.
			 */
			void setPrimary(const bool primary);

		private:
			/**
			 * Reads the type of the website.
			 * @param handle The handle of the contact.
			 * @param index The index of this website.
			 */
			void readType(const MAHandle handle, const int index);

			/**
			 * Reads the label of the website.
			 * @param handle The handle of the contact.
			 * @param index The index of this website.
			 */
			void readLabel(const MAHandle handle, const int index);

			/**
			 * Computes the website attribute.
			 * @return The website attribute.
			 */
			const int getAttribute() const;

		private:
			//The website URL.
			wchar* mURL;

			//The type of data.
			eTypes mType;
			//The user defined label.
			wchar* mLabel;
			//Shows if this is a primary website or not.
			bool mIsPrimary;
	};

} //PIM

#endif //__WEBSITE_H__

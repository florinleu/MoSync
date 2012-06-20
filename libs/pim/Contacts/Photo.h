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
 * @file Photo.h
 * @author Florin Leu
 * @date 09 Feb 2011
 *
 * @brief PIM Field Photo class.
 *
 **/

#ifndef __PHOTO_H__
#define __PHOTO_H__

#include <IX_PIM.h>

namespace PIM
{
	class Photo
	{
		public:
			enum eSubFields
			{
				//The constant describes a note.
				HANDLE = 0,
			};

		public:
			/**
			 * Constructor.
			 */
			Photo();

			/**
			 * Destructor.
			 */
			~Photo();

			/**
			 * Reads the contact's photo.
			 * @param args The arguments needed to read the photo.
			 * @return true on success.
			 */
			bool read(MA_PIM_ARGS& args);

			/**
			 * Writes the contact's photo.
			 * @param args The values to write.
			 */
			void write(MA_PIM_ARGS& args);

			/**
			 * Deletes a contact's photo.
			 * @param handle The handle of the contact.
			 */
			void remove(MAHandle handle);

			/**
			 * Gets the contact's photo handle.
			 * @return The photo handle of the contact.
			 */
			const MAHandle& getHandle() const;

			/**
			 * Sets the contact's photo handle.
			 * @param handle The value to set.
			 */
			void setHandle(const MAHandle& handle);

			/**
			 * Sets the contact's photo url.
			 * @param url The value to set.
			 */
			void setURL(const wchar* const url);

		private:
			//The photo handle.
			MAHandle mHandle;
			//The photo URL.
			//Can only be set.
			wchar* mURL;
	};

} //PIM

#endif //__PHOTO_H__

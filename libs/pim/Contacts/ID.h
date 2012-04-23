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
 * @file ID.h
 * @author Florin Leu
 * @date 09 Feb 2011
 *
 * @brief PIM Field ID class.
 *
 **/

#ifndef __ID_H__
#define __ID_H__

#include <maapi.h>
#include <IX_PIM.h>

namespace PIM
{

	class ID
	{
		public:
			enum eSubFields
			{
				// The data of the id.
				DATA = 0
			};
		public:
			/**
			 * Destructor.
			 */
			~ID();

			/**
			 * Reads the contact's id.
			 * @param args The arguments needed to read the id.
			 * @return true on success.
			 */
			bool read(MA_PIM_ARGS& args);

			/**
			 * Reads the id data.
			 * @param buffer The buffer to read from.
			 */
			void readData(const MAAddress buffer);

			/**
			 * Gets the contact's id.
			 * @return The ID for the contact.
			 */
			const wchar* const getID() const;

			/**
			 * Sets the contact's id.
			 * @param id The value to set.
			 */
			void setID(const wchar* const id);

		private:
			//The ID for the contact.
			wchar* mID;
	};

} //PIM

#endif //__ID_H__

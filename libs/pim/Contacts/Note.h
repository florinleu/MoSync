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
 * @file Note.h
 * @author Florin Leu
 * @date 09 Feb 2011
 *
 * @brief PIM Field Note class.
 *
 **/

#ifndef __NOTE_H__
#define __NOTE_H__

#include <IX_PIM.h>

namespace PIM
{
	class Note
	{
		public:
			enum eSubFields
			{
				//The constant describes a note.
				TEXT = 0,
			};

		public:
			/**
			 * Constructor.
			 */
			Note();

			/**
			 * Destructor.
			 */
			~Note();

			/**
			 * Reads a contact's note.
			 * @param args The arguments needed to read the note.
			 * @param index The index of the note to read.
			 */
			void read(MA_PIM_ARGS& args, int index);

			/**
			 * Writes a contact's note.
			 * @param args The values to write.
			 * @index args The index of the note to write.
			 */
			void write(MA_PIM_ARGS& args, int index);

			/**
			 * Adds a new note to this contact.
			 * @param args The values to add.
			 */
			void add(MA_PIM_ARGS& args);

			/**
			 * Deletes a contact's note.
			 * @param handle The handle of the contact.
			 * @param index  The index of the note to delete.
			 */
			void remove(MAHandle handle, int index);

			/**
			 * Gets the contact's note text.
			 * @return The note text of the contact.
			 */
			const wchar* const getText() const;

			/**
			 * Sets the contact's note text.
			 * @param text The value to set.
			 */
			void setText(const wchar* const text);

		private:
			//The note text.
			wchar* mText;
	};

} //PIM

#endif //__NOTE_H__

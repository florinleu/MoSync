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
			void read(MA_PIM_ARGS& args);

			const wchar* getText() const;
			void setText(wchar* const text);

		private:
			void readText(MAAddress const buffer);

		private:
			//The note text.
			wchar* mText;
	};

} //PIM

#endif //__NOTE_H__

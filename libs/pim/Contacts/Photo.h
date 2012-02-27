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
			void read(MA_PIM_ARGS& args);

			const MAHandle& getHandle() const;
			void setHandle(const MAHandle& handle);

			void setURL(wchar* const url);

		private:
			void readHandle(MAAddress const buffer);

		private:
			//The photo handle.
			MAHandle mHandle;
			//The photo URL.
			//Can only be set.
			wchar* mURL;
	};

} //PIM

#endif //__PHOTO_H__

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

namespace PIM
{

	enum eWebsiteTypes
	{
		//The constant describes a homepage website.
		WEBSITE_HOMEPAGE = 0,
		//The constant describes a blog website.
		WEBSITE_BLOG,
		//The constant describes a profile website.
		WEBSITE_PROFILE,
		//The constant describes a home website.
		WEBSITE_HOME,
		//The constant describes a work website.
		WEBSITE_WORK,
		//The constant describes a FTP website.
		WEBSITE_FTP,
		//The constant describes a different website type.
		WEBSITE_OTHER,
		//The constant describes a custom website type.
		//The field's label can be set.
		WEBSITE_CUSTOM,
	};

	class Website
	{
		private:
			//The website URL.
			wchar* mURL;

			//The type of data.
			eWebsiteTypes mType;
			//The user defined label
			wchar* mLabel;
	};

} //PIM

#endif //__WEBSITE_H__

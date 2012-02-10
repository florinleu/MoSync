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

namespace PIM
{

	enum eOrganizationTypes
	{
		//The constant describes a work organization.
		ORGANIZATION_WORK = 0,
		//The constant describes a different organization type.
		ORGANIZATION_OTHER,
		//The constant describes a custom organization type.
		//The field's label can be set.
		ORGANIZATION_CUSTOM
	};

	class Organization
	{
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
			wchar* mPhoneticName;
			//The phonetic name of this company
			wchar* mNeighborhood;
			////The symbol of this company
			wchar* mSymbol;

			//The type of data.
			eOrganizationTypes mType;
			//The user defined label
			wchar* mLabel;
	};

} //PIM

#endif //__ORGANIZATION_H__

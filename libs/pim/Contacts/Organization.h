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
		public:
			Organization();

			void read(MA_PIM_ARGS& args, int index);

			const wchar* getName() const;
			void setName(wchar* name);

			const wchar* getTitle() const;
			void setTitle(wchar* title);

			const wchar* getDepartment() const;
			void setDepartment(wchar* department);

			const wchar* getLocation() const;
			void setLocation(wchar* location);

			const wchar* getJobDescription() const;
			void setJobDescription(wchar* jobDescription);

			const wchar* getPhoneticName() const;
			void setPhoneticName(wchar* phoneticName);

			const wchar* getSymbol() const;
			void setSymbol(wchar* symbol);

			const eOrganizationTypes& getType() const;
			void setType(const eOrganizationTypes& type);

			const wchar* getLabel() const;
			void setLabel(wchar* label);

			const bool isPrimary() const;

		private:
			void readName(const MAAddress buffer);
			void readTitle(const MAAddress buffer);
			void readDepartment(const MAAddress buffer);
			void readLocation(const MAAddress buffer);
			void readJobDescription(const MAAddress buffer);
			void readPhoneticName(const MAAddress buffer);
			void readSymbol(const MAAddress buffer);

			void readType(const MAHandle handle, const int index);
			void readLabel(const MAHandle handle, const int index);

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
			eOrganizationTypes mType;
			//The user defined label
			wchar* mLabel;
			//Shows if this is a primary address or not.
			bool mIsPrimary;
	};

} //PIM

#endif //__ORGANIZATION_H__

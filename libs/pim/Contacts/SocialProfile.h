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
 * @file SocialProfile.h
 * @author Florin Leu
 * @date 09 Feb 2011
 *
 * @brief PIM Field Social Profile class.
 *
 **/

#ifndef __SOCIALPROFILE_H__
#define __SOCIALPROFILE_H__

#include <IX_PIM.h>

namespace PIM
{

	enum eSocialProfileTypes
	{
		//The constant describes a home social profile.
		SOCIALPROFILE_HOME = 0,
		//The constant describes a work social profile.
		SOCIALPROFILE_WORK,
		//The constant describes a different social profile type.
		SOCIALPROFILE_OTHER,
		//The constant describes a custom social profile type.
		//The field's label can be set.
		SOCIALPROFILE_CUSTOM,
	};

	enum eSocialProfileServices
	{
		//This constant describes a Twitter service.
		SERVICE_TWITTER = 0,
		//This constant describes a Game Center service.
		SERVICE_GAMECENTER,
		//This constant describes a Facebook service.
		SERVICE_FACEBOOK,
		//This constant describes a My Space service.
		SERVICE_MYSPACE,
		//This constant describes a Linkedin service.
		SERVICE_LINKEDIN,
		//This constant describes a Flickr service.
		SERVICE_FLICKR,
		//This constant describes a custom service.
		SERVICE_CUSTOM
	};

	class SocialProfile
	{
		public:
			SocialProfile();

			void read(MA_PIM_ARGS& args, int index);

			const wchar* getURL() const;
			void setURL(wchar* url);

			const wchar* getUsername() const;
			void setUsername(wchar* username);

			const wchar* getUserIdentifier() const;
			void setUserIdentifier(wchar* userIdentifier);

			const eSocialProfileServices& getService() const;
			void setService(const eSocialProfileServices& service);

			const wchar* getServiceLabel() const;
			void setServiceLabel(wchar* serviceLabel);

			const eSocialProfileTypes& getType() const;
			void setType(const eSocialProfileTypes& type);

			const wchar* getLabel() const;
			void setLabel(wchar* label);

			const bool isPrimary() const;

		private:
			void readURL(const MAAddress buffer);
			void readUsername(const MAAddress buffer);
			void readUserIdentifier(const MAAddress buffer);
			void readService(const MAAddress buffer);
			void readServiceLabel(const MAAddress buffer);

			void readType(const MAHandle handle, const int index);
			void readLabel(const MAHandle handle, const int index);

		private:
			//The URL of the social profile.
			wchar* mURL;
			//The user name of the social profile.
			wchar* mUsername;
			//The user identifier of the social profile.
			wchar* mUserIdentifier;
			//The service of the social profile.
			eSocialProfileServices mService;
			//The user defined service.
			wchar* mServiceLabel;

			//The type of data.
			eSocialProfileTypes mType;
			//The user defined label
			wchar* mLabel;
			//Shows if this is a primary social profile or not.
			bool mIsPrimary;
	};

} //PIM

#endif //__SOCIALPROFILE_H__

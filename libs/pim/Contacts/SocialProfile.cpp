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
 * @file SocialProfile.cpp
 * @author Florin Leu
 * @date 27 Feb 2011
 *
 * @brief PIM Field Social Profile class.
 *
 **/

#include <conprint.h>
#include <mawstring.h>

#include "SocialProfile.h"
#include "util.h"

namespace PIM
{

	/*
	 * Constructor
	 */
	SocialProfile::SocialProfile():
		mIsPrimary(false)
	{

	}

	/*
	 * Read a complete social profile.
	 */
	void SocialProfile::read(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: social profile read");
		args.field = MA_PIM_FIELD_CONTACT_SOCIAL_PROFILE;
		//CHECK_RESULT(maPimItemGetValue(&args, 0));
		if (maPimItemGetValue(&args, index))
		{
			readURL(args.buf);
			readUsername(args.buf);
			readUserIdentifier(args.buf);
			readService(args.buf);
			readServiceLabel(args.buf);

			readType(args.item, index);
			readLabel(args.item, index);
		}
	}

	void SocialProfile::readURL(MAAddress const buffer)
	{
		mURL = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_SOCIAL_PROFILE_URL);
	}

	void SocialProfile::readUsername(MAAddress const buffer)
	{
		mUsername = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_SOCIAL_PROFILE_USERNAME);
	}

	void SocialProfile::readUserIdentifier(MAAddress const buffer)
	{
		mUserIdentifier = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_SOCIAL_PROFILE_USER_IDENTIFIER);
	}

	void SocialProfile::readService(MAAddress const buffer)
	{
		wchar* wstrService = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_SOCIAL_PROFILE_SERVICE);
		char* strService = wstrtostr(wstrService);

		if (strcmp(strService, MA_PIM_CONTACT_SOCIAL_PROFILE_SERVICE_TWITTER) == 0)
		{
			mService = SERVICE_TWITTER;
		}
		else if (strcmp(strService, MA_PIM_CONTACT_SOCIAL_PROFILE_SERVICE_GAMECENTER) == 0)
		{
			mService = SERVICE_GAMECENTER;
		}
		else if(strcmp(strService, MA_PIM_CONTACT_SOCIAL_PROFILE_SERVICE_FACEBOOK) == 0)
		{
			mService = SERVICE_FACEBOOK;
		}
		else if (strcmp(strService, MA_PIM_CONTACT_SOCIAL_PROFILE_SERVICE_MYSPACE) == 0)
		{
			mService = SERVICE_MYSPACE;
		}
		else if (strcmp(strService, MA_PIM_CONTACT_SOCIAL_PROFILE_SERVICE_LINKEDIN) == 0)
		{
			mService = SERVICE_LINKEDIN;
		}
		else if (strcmp(strService, MA_PIM_CONTACT_SOCIAL_PROFILE_SERVICE_FLICKR) == 0)
		{
			mService = SERVICE_LINKEDIN;
		}
		else
		{
			mService = SERVICE_CUSTOM;
		}

		DELETE(wstrService);
		DELETE(strService);
	}

	void SocialProfile::readServiceLabel(MAAddress const buffer)
	{
		mServiceLabel = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_SOCIAL_PROFILE_SERVICE_LABEL);
	}

	void SocialProfile::readType(const MAHandle handle, const int index)
	{
		int attribute = maPimItemGetAttributes(handle, MA_PIM_FIELD_CONTACT_SOCIAL_PROFILE, index);

		if (attribute >> 16)
		{
			mIsPrimary = true;

			// Remove primary value from attribute.
			attribute = (attribute & 0xFFFF);
		}

		switch (attribute)
		{
			case MA_PIM_ATTR_SOCIAL_PROFILE_HOME:
				mType = SOCIALPROFILE_HOME;
				break;
			case MA_PIM_ATTR_SOCIAL_PROFILE_WORK:
				mType = SOCIALPROFILE_WORK;
				break;
			case MA_PIM_ATTR_SOCIAL_PROFILE_CUSTOM:
				mType = SOCIALPROFILE_CUSTOM;
				break;
			default:
				mType = SOCIALPROFILE_OTHER;
				break;
		}
	}

	void SocialProfile::readLabel(const MAHandle handle, const int index)
	{
		MA_PIM_ARGS args;
		args.item = handle;
		args.field = MA_PIM_FIELD_CONTACT_SOCIAL_PROFILE;

		char buf[BUF_SIZE];
		args.buf = buf;
		args.bufSize = BUF_SIZE;
		maPimItemGetLabel(&args, index);

		DELETE(mLabel);
		wchar* src = (wchar*)args.buf;
		int len = wcslen(src);
		mLabel = new wchar[len + 1];
		wcsncpy(mLabel, src, len);
	}

	/*
	 * Getter for url.
	 */
	const wchar* SocialProfile::getURL() const
	{
		return mURL;
	}

	/*
	 * Setter for url.
	 */
	void SocialProfile::setURL(wchar* const url)
	{
		mURL = url;
	}

	/*
	 * Getter for username.
	 */
	const wchar* SocialProfile::getUsername() const
	{
		return mUsername;
	}

	/*
	 * Setter for username.
	 */
	void SocialProfile::setUsername(wchar* const username)
	{
		mUsername = username;
	}

	/*
	 * Getter for user identifier.
	 */
	const wchar* SocialProfile::getUserIdentifier() const
	{
		return mUserIdentifier;
	}

	/*
	 * Setter for user identifier.
	 */
	void SocialProfile::setUserIdentifier(wchar* const userIdentifier)
	{
		mUserIdentifier = userIdentifier;
	}

	/*
	 * Getter for service.
	 */
	const eSocialProfileServices& SocialProfile::getService() const
	{
		return mService;
	}

	/*
	 * Setter for service.
	 */
	void SocialProfile::setService(const eSocialProfileServices& service)
	{
		mService = service;
	}

	/*
	 * Getter for service label.
	 */
	const wchar* SocialProfile::getServiceLabel() const
	{
		return mServiceLabel;
	}

	/*
	 * Setter for service label.
	 */
	void SocialProfile::setServiceLabel(wchar* const serviceLabel)
	{
		mServiceLabel = serviceLabel;
	}

	/*
	 * Getter for type.
	 */
	const eSocialProfileTypes& SocialProfile::getType() const
	{
		return mType;
	}

	/*
	 * Setter for type.
	 */
	void SocialProfile::setType(const eSocialProfileTypes& type)
	{
		mType = type;
	}

	/*
	 * Getter for label.
	 */
	const wchar* SocialProfile::getLabel() const
	{
		return mLabel;
	}

	/*
	 * Setter for label.
	 */
	void SocialProfile::setLabel(wchar* const label)
	{
		mLabel = label;
	}

	/*
	 * Returns true if this is a primary instant messaging.
	 */
	const bool SocialProfile::isPrimary() const
	{
		return mIsPrimary;
	}

} //PIM

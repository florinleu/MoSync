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
	/**
	 * Constructor
	 */
	SocialProfile::SocialProfile():
		mURL(NULL),
		mUsername(NULL),
		mUserIdentifier(NULL),
		mServiceLabel(NULL),
		mLabel(NULL),
		mIsPrimary(false)
	{

	}

	/**
	 * Destructor.
	 */
	SocialProfile::~SocialProfile()
	{
		DELETE(mURL);
		DELETE(mUsername);
		DELETE(mUserIdentifier);
		DELETE(mServiceLabel);
		DELETE(mLabel);
	}

	/**
	 * Reads a contact's social profile.
	 * @param args The arguments needed to read the social profile.
	 * @param index The index of the social profile to read.
	 */
	void SocialProfile::read(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: social profile read");
		args.field = MA_PIM_FIELD_CONTACT_SOCIAL_PROFILE;
		args.bufSize = PIM_BUF_SIZE;

		if (maPimItemGetValue(&args, index) > 0)
		{
			mURL = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_SOCIAL_PROFILE_URL);
			mUsername = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_SOCIAL_PROFILE_USERNAME);
			mUserIdentifier = getWCharArrayFromBuf(args.buf, MA_PIM_CONTACT_SOCIAL_PROFILE_USER_IDENTIFIER);

			readService(args.buf);
			readServiceLabel(args.buf);

			readType(args.item, index);
			readLabel(args.item, index);
		}
	}

	/**
	 * Writes a contact's social profile.
	 * @param args The values to write.
	 * @index args The index of the social profile to write.
	 */
	void SocialProfile::write(MA_PIM_ARGS& args, int index)
	{
		printf("@LIB: social profile write");

		wchar* name = getServiceName();

		args.field = MA_PIM_FIELD_CONTACT_SOCIAL_PROFILE;
		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeInt(args.buf, MA_PIM_CONTACT_SOCIAL_PROFILE_COUNT, 0);
		args.bufSize += writeWString(args.buf, mURL, args.bufSize);
		args.bufSize += writeWString(args.buf, mUsername, args.bufSize);
		args.bufSize += writeWString(args.buf, mUserIdentifier, args.bufSize);
		args.bufSize += writeWString(args.buf, name, args.bufSize);
		args.bufSize += writeWString(args.buf, mServiceLabel, args.bufSize);
		maPimItemSetValue(&args, index, getAttribute());

		memset(args.buf, 0, PIM_BUF_SIZE);
		args.bufSize = writeWString(args.buf, mLabel, 0);
		maPimItemSetLabel(&args, index);

		DELETE(name);
	}

	/**
	 * Adds a new social profile to this contact.
	 */
	void SocialProfile::add(MA_PIM_ARGS& args)
	{
		args.field = MA_PIM_FIELD_CONTACT_SOCIAL_PROFILE;
		maPimItemAddValue(&args, MA_PIM_ATTR_SOCIAL_PROFILE_HOME);
	}

	/**
	 * Deletes a contact's social profile.
	 * @param handle The handle of the contact.
	 * @param index  The index of the social profile to delete.
	 */
	void SocialProfile::remove(MAHandle handle, int index)
	{
		printf("@LIB: social profile delete");

		maPimItemRemoveValue(handle, MA_PIM_FIELD_CONTACT_SOCIAL_PROFILE, index);
	}

	/**
	 * Reads the service of the social profile.
	 * @param buffer The buffer to read from.
	 */
	void SocialProfile::readService(const MAAddress buffer)
	{
		wchar* wstrService = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_SOCIAL_PROFILE_SERVICE);
		char* strService = wstrtostr(wstrService);

		if (strcmp(strService, MA_PIM_CONTACT_SOCIAL_PROFILE_SERVICE_TWITTER) == 0)// fleu TODO try to create a map here
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

	/**
	 * Reads the service label of the social profile.
	 * @param buffer The buffer to read from.
	 */
	void SocialProfile::readServiceLabel(const MAAddress buffer)
	{
		mServiceLabel = getWCharArrayFromBuf(buffer, MA_PIM_CONTACT_SOCIAL_PROFILE_SERVICE_LABEL);
	}

	/**
	 * Reads the type of the social profile.
	 * @param handle The handle of the contact.
	 * @param index The index of this social profile.
	 */
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
				mType = TYPE_HOME;
				break;
			case MA_PIM_ATTR_SOCIAL_PROFILE_WORK:
				mType = TYPE_WORK;
				break;
			case MA_PIM_ATTR_SOCIAL_PROFILE_CUSTOM:
				mType = TYPE_CUSTOM;
				break;
			default:
				mType = TYPE_OTHER;
				break;
		}
	}

	/**
	 * Reads the label of the social profile.
	 * @param handle The handle of the contact.
	 * @param index The index of this social profile.
	 */
	void SocialProfile::readLabel(const MAHandle handle, const int index)
	{
		MA_PIM_ARGS args;
		args.item = handle;
		args.field = MA_PIM_FIELD_CONTACT_SOCIAL_PROFILE;
		args.bufSize = PIM_BUF_SIZE;

		char buf[PIM_BUF_SIZE];
		args.buf = buf;
		args.bufSize = PIM_BUF_SIZE;
		maPimItemGetLabel(&args, index);

		wchar* src = (wchar*)args.buf;
		mLabel = wcsdup(src);
	}

	/**
	 * Gets the contact's social profile url.
	 * @return The url of the social profile.
	 */
	const wchar* const SocialProfile::getURL() const
	{
		return mURL;
	}

	/**
	 * Sets the contact's social profile url.
	 * @param url The value to set.
	 */
	void SocialProfile::setURL(const wchar* const url)
	{
		DELETE(mURL);
		mURL = wcsdup(url);
	}

	/**
	 * Gets the contact's social profile username.
	 * @return The username of the social profile.
	 */
	const wchar* const SocialProfile::getUsername() const
	{
		return mUsername;
	}

	/**
	 * Sets the contact's social profile username.
	 * @param username The value to set.
	 */
	void SocialProfile::setUsername(const wchar* const username)
	{
		DELETE(mUsername);
		mUsername = wcsdup(username);
	}

	/**
	 * Gets the contact's social profile user identifier.
	 * @return The user identifier of the social profile.
	 */
	const wchar* const SocialProfile::getUserIdentifier() const
	{
		return mUserIdentifier;
	}

	/**
	 * Sets the contact's social profile user identifier.
	 * @param userIdentifier The value to set.
	 */
	void SocialProfile::setUserIdentifier(const wchar* const userIdentifier)
	{
		DELETE(mUserIdentifier);
		mUserIdentifier = wcsdup(userIdentifier);
	}

	/**
	 * Gets the contact's social profile service.
	 * @return The service of the social profile.
	 */
	const SocialProfile::eServices& SocialProfile::getService() const
	{
		return mService;
	}

	/**
	 * Sets the contact's social profile service.
	 * @param service The value to set.
	 */
	void SocialProfile::setService(const SocialProfile::eServices& service)
	{
		mService = service;
	}

	/**
	 * Gets the contact's social profile service label.
	 * @return The service label of the social profile.
	 */
	const wchar* const SocialProfile::getServiceLabel() const
	{
		return mServiceLabel;
	}

	/**
	 * Sets the contact's social profile service label.
	 * @param serviceLabel The value to set.
	 */
	void SocialProfile::setServiceLabel(const wchar* const serviceLabel)
	{
		DELETE(mServiceLabel);
		mServiceLabel = wcsdup(serviceLabel);
	}

	/**
	 * Gets the social profile type.
	 * @return The type of the social profile.
	 */
	const SocialProfile::eTypes& SocialProfile::getType() const
	{
		return mType;
	}

	/**
	 * Sets the social profile type.
	 * @param type The value to set.
	 */
	void SocialProfile::setType(const SocialProfile::eTypes& type)
	{
		mType = type;
	}

	/**
	 * Gets the social profile label.
	 * @return The label of the social profile.
	 */
	const wchar* const SocialProfile::getLabel() const
	{
		return mLabel;
	}

	/**
	 * Sets the social profile label.
	 * @param state The value to set.
	 */
	void SocialProfile::setLabel(const wchar* const label)
	{
		DELETE(mLabel);
		mLabel = wcsdup(label);
	}

	/**
	 * Checks if this is or not a primary social profile.
	 * @return True if this is a primary social profile.
	 */
	const bool SocialProfile::isPrimary() const
	{
		return mIsPrimary;
	}

	/**
	 * Sets this as a primary social profile.
	 * @param primary true if this is a primary social profile.
	 */
	void SocialProfile::setPrimary(const bool primary)
	{
		mIsPrimary = primary;
	}

	/**
	 * Gets the service string according to mService.
	 * @return The service name.
	 */
	wchar* SocialProfile::getServiceName() const // fleu TODO try to create a map here
	{
		const char* str = NULL;
		switch (mService)
		{
			case SERVICE_TWITTER:
				str = MA_PIM_CONTACT_SOCIAL_PROFILE_SERVICE_TWITTER;
				break;
			case SERVICE_GAMECENTER:
				str = MA_PIM_CONTACT_SOCIAL_PROFILE_SERVICE_GAMECENTER;
				break;
			case SERVICE_FACEBOOK:
				str = MA_PIM_CONTACT_SOCIAL_PROFILE_SERVICE_FACEBOOK;
				break;
			case SERVICE_MYSPACE:
				str = MA_PIM_CONTACT_SOCIAL_PROFILE_SERVICE_MYSPACE;
				break;
			case SERVICE_LINKEDIN:
				str = MA_PIM_CONTACT_SOCIAL_PROFILE_SERVICE_LINKEDIN;
				break;
			case SERVICE_FLICKR:
				str = MA_PIM_CONTACT_SOCIAL_PROFILE_SERVICE_FLICKR;
				break;
			default:
				str = MA_PIM_CONTACT_IM_PROTOCOL_CUSTOM;
				break;
		}

		return strtowstr(str);
	}

	/**
	 * Computes the social profile attribute.
	 * @return The social profile attribute.
	 */
	const int SocialProfile::getAttribute() const
	{
		int attribute = 0;
		switch (mType)
		{
			case TYPE_HOME:
				attribute = MA_PIM_ATTR_SOCIAL_PROFILE_HOME;
				break;
			case TYPE_WORK:
				attribute = MA_PIM_ATTR_SOCIAL_PROFILE_WORK;
				break;
			case TYPE_CUSTOM:
				attribute = MA_PIM_ATTR_SOCIAL_PROFILE_CUSTOM;
				break;
			default:
				attribute = MA_PIM_ATTR_SOCIAL_PROFILE_OTHER;
				break;
		}

		attribute |= (mIsPrimary ? MA_PIM_ATTRPREFERRED : 0);

		return attribute;
	}

} //PIM

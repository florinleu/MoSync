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
	class SocialProfile
	{
		public:
			enum eTypes
			{
				//The constant describes a home social profile.
				TYPE_HOME = 0,
				//The constant describes a work social profile.
				TYPE_WORK,
				//The constant describes a different social profile type.
				TYPE_OTHER,
				//The constant describes a custom social profile type.
				//The field's label can be set.
				TYPE_CUSTOM
			};

			enum eServices
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

			enum eSubFields
			{
				//The constant describes a social profile URL.
				URL = 0,
				//The constant describes a social profile username.
				USERNAME,
				//The constant describes a social profile user identifier.
				USER_IDENTIFIER,
				//The constant describes a social profile service.
				SERVICE
			};

		public:
			/**
			 * Constructor.
			 */
			SocialProfile();

			/**
			 * Destructor.
			 */
			~SocialProfile();

			/**
			 * Reads a contact's social profile.
			 * @param args The arguments needed to read the social profile.
			 * @param index The index of the social profile to read.
			 */
			void read(MA_PIM_ARGS& args, int index);

			/**
			 * Writes a contact's social profile.
			 * @param args The values to write.
			 * @index args The index of the social profile to write.
			 */
			void write(MA_PIM_ARGS& args, int index);

			/**
			 * Adds a new social profile to this contact.
			 * @param args The values to add.
			 */
			void add(MA_PIM_ARGS& args);

			/**
			 * Deletes a contact's social profile.
			 * @param handle The handle of the contact.
			 * @param index  The index of the social profile to delete.
			 */
			void remove(MAHandle handle, int index);

			/**
			 * Gets the contact's social profile url.
			 * @return The url of the social profile.
			 */
			const wchar* const getURL() const;

			/**
			 * Sets the contact's social profile url.
			 * @param url The value to set.
			 */
			void setURL(const wchar* const url);

			/**
			 * Gets the contact's social profile username.
			 * @return The username of the social profile.
			 */
			const wchar* const getUsername() const;

			/**
			 * Sets the contact's social profile username.
			 * @param username The value to set.
			 */
			void setUsername(const wchar* const username);

			/**
			 * Gets the contact's social profile user identifier.
			 * @return The user identifier of the social profile.
			 */
			const wchar* const getUserIdentifier() const;

			/**
			 * Sets the contact's social profile user identifier.
			 * @param userIdentifier The value to set.
			 */
			void setUserIdentifier(const wchar* const userIdentifier);

			/**
			 * Gets the contact's social profile service.
			 * @return The service of the social profile.
			 */
			const eServices& getService() const;

			/**
			 * Sets the contact's social profile service.
			 * @param service The value to set.
			 */
			void setService(const eServices& service);

			/**
			 * Gets the contact's social profile service label.
			 * @return The service label of the social profile.
			 */
			const wchar* const getServiceLabel() const;

			/**
			 * Sets the contact's social profile service label.
			 * @param serviceLabel The value to set.
			 */
			void setServiceLabel(const wchar* const serviceLabel);

			/**
			 * Gets the social profile type.
			 * @return The type of the social profile.
			 */
			const eTypes& getType() const;

			/**
			 * Sets the social profile type.
			 * @param type The value to set.
			 */
			void setType(const eTypes& type);

			/**
			 * Gets the social profile label.
			 * @return The label of the social profile.
			 */
			const wchar* const getLabel() const;

			/**
			 * Sets the social profile label.
			 * @param state The value to set.
			 */
			void setLabel(const wchar* const label);

			/**
			 * Checks if this is or not a primary social profile.
			 * @return True if this is a primary social profile.
			 */
			const bool isPrimary() const;

			/**
			 * Sets this as a primary social profile.
			 * @param primary true if this is a primary social profile.
			 */
			void setPrimary(const bool primary);

		private:
			/**
			 * Reads the service of the social profile.
			 * @param buffer The buffer to read from.
			 */
			void readService(const MAAddress buffer);

			/**
			 * Reads the service label of the social profile.
			 * @param buffer The buffer to read from.
			 */
			void readServiceLabel(const MAAddress buffer);

			/**
			 * Reads the type of the social profile.
			 * @param handle The handle of the contact.
			 * @param index The index of this social profile.
			 */
			void readType(const MAHandle handle, const int index);

			/**
			 * Reads the label of the social profile.
			 * @param handle The handle of the contact.
			 * @param index The index of this social profile.
			 */
			void readLabel(const MAHandle handle, const int index);

			/**
			 * Gets the service string according to mService.
			 * @return The service name.
			 */
			wchar* getServiceName() const;

			/**
			 * Computes the social profile attribute.
			 * @return The social profile attribute.
			 */
			const int getAttribute() const;

		private:
			//The URL of the social profile.
			wchar* mURL;
			//The user name of the social profile.
			wchar* mUsername;
			//The user identifier of the social profile.
			wchar* mUserIdentifier;
			//The service of the social profile.
			eServices mService;
			//The user defined service.
			wchar* mServiceLabel;

			//The type of data.
			eTypes mType;
			//The user defined label
			wchar* mLabel;
			//Shows if this is a primary social profile or not.
			bool mIsPrimary;
	};

} //PIM

#endif //__SOCIALPROFILE_H__

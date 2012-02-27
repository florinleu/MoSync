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
 * @file Contact.cpp
 * @author Florin Leu
 * @date 08 Feb 2011
 *
 * @brief PIM Contact class.
 *
 **/

#include "Contact.h"
#include "IX_PIM.h"
#include "util.h"

#include <conprint.h>

namespace PIM
{
	/*
	 * Constructor.
	 */
	Contact::Contact(const MAHandle listHandle):
			mListHandle(listHandle)
	{
	}

	/*
	 * Destructor.
	 */
	Contact::~Contact()
	{
		clean();
	}

	void Contact::clean()
	{
		DELETE(mID);
		DELETE(mName);
		for (int i=0; i<mAddresses.size(); i++)
		{
			DELETE(mAddresses[i]);
		}
		mAddresses.empty();

		for (int i=0; i<mPhones.size(); i++)
		{
			DELETE(mPhones[i]);
		}
		mPhones.empty();
		DELETE(mPhoto);
//		Email** mEmail;
//		Website** mWebsite;
//		Organization** mOrganization;
//		Event** mEvent;
//		Note* mNote;
//		InstantMessaging** mInstantMessaging;
//		Relation** mRelation;
//		SocialProfile** mSocialProfile;
		DELETE(mBuffer);
	}

	/*
	 * Read the Contact.
	 */
	int Contact::readNext(int flag)
	{
		clean();
		//Get the contacts item handle.
		mHandle = maPimListNext(mListHandle);

		if (mHandle <= 0)
		{
			return 0; //fleu TODO
		}

		MA_PIM_ARGS args;
		args.item = mHandle;
		mBuffer = new char[BUF_SIZE];
		args.buf = mBuffer;
		args.bufSize = BUF_SIZE;

		mID = new ID();
		mID->read(args);

		if ((flag & RF_NAME) != 0)
		{
			mName = new Name();
			mName->read(args);
		}

		if ((flag & RF_ADDRESS) != 0)
		{
			int countValues = maPimItemFieldCount(mHandle, MA_PIM_FIELD_CONTACT_ADDR);
			for (int i=0; i<countValues; i++)
			{
				Address* address = new Address();
				address->read(args, i);
				mAddresses.add(address);
			}
		}

		if ((flag & RF_PHONE) != 0)
		{
			int countValues = maPimItemFieldCount(mHandle, MA_PIM_FIELD_CONTACT_TEL);
			for (int i=0; i<countValues; i++)
			{
				Phone* phone = new Phone();
				phone->read(args, i);
				mPhones.add(phone);
			}
		}

		if ((flag & RF_EMAIL) != 0)
		{
			int countValues = maPimItemFieldCount(mHandle, MA_PIM_FIELD_CONTACT_EMAIL);
			for (int i=0; i<countValues; i++)
			{
				Email* email = new Email();
				email->read(args, i);
				mEmails.add(email);
			}
		}

		if ((flag & RF_WEBSITE) != 0)
		{
			int countValues = maPimItemFieldCount(mHandle, MA_PIM_FIELD_CONTACT_URL);
			for (int i=0; i<countValues; i++)
			{
				Website* website = new Website();
				website->read(args, i);
				mWebsites.add(website);
			}
		}

		if ((flag & RF_INSTANTMESSAGING) != 0)
		{
			int countValues = maPimItemFieldCount(mHandle, MA_PIM_FIELD_CONTACT_IM);
			for (int i=0; i<countValues; i++)
			{
				InstantMessaging* instantMessaging = new InstantMessaging();
				instantMessaging->read(args, i);
				mInstantMessagings.add(instantMessaging);
			}
		}

		if ((flag & RF_NOTE) != 0)
		{
			mNote = new Note();
			mNote->read(args);
		}

		if ((flag & RF_ORGANIZATION) != 0)
		{
			int countValues = maPimItemFieldCount(mHandle, MA_PIM_FIELD_CONTACT_ORG);
			for (int i=0; i<countValues; i++)
			{
				Organization* organization = new Organization();
				organization->read(args, i);
				mOrganizations.add(organization);
			}
		}

		if ((flag & RF_SOCIALPROFILE) != 0)
		{
			int countValues = maPimItemFieldCount(mHandle, MA_PIM_FIELD_CONTACT_SOCIAL_PROFILE);
			for (int i=0; i<countValues; i++)
			{
				SocialProfile* socialProfile = new SocialProfile();
				socialProfile->read(args, i);
				mSocialProfiles.add(socialProfile);
			}
		}

		return 0;
	}

	/*
	 * Getter for ID field.
	 */
	const wchar* Contact::getID() const
	{
		if (mID != NULL)
		{
			return mID->getID();
		}
		return NULL;
	}

	/*
	 * Getter for name field.
	 */
	const Name* Contact::getName() const
	{
		return mName;
	}

	/*
	 * Setter for name field.
	 */
	void Contact::setName(Name* name)
	{
		mName = name;
	}

	/*
	 * Getter for the number of addresses.
	 */
	const int Contact::getAddressesCount() const
	{
		return mAddresses.size();
	}

	/*
	 * Getter for address field.
	 */
	const Address* Contact::getAddress(int index) const
	{
		return mAddresses[index];
	}

	/*
	 * Setter for address field.
	 */
	void Contact::setAddress(Address* address, int index)
	{
		mAddresses[index] = address;
	}

	/*
	 * Getter for the number of phones.
	 */
	const int Contact::getPhonesCount() const
	{
		return mPhones.size();
	}

	/*
	 * Getter for phone field.
	 */
	const Phone* Contact::getPhone(int index) const
	{
		return mPhones[index];
	}

	/*
	 * Setter for phone field.
	 */
	void Contact::setPhone(Phone* phone, int index)
	{
		mPhones[index] = phone;
	}

	/*
	 * Getter for the number of emails.
	 */
	const int Contact::getEmailsCount() const
	{
		return mEmails.size();
	}

	/*
	 * Getter for email field.
	 */
	const Email* Contact::getEmail(int index) const
	{
		return mEmails[index];
	}

	/*
	 * Setter for email field.
	 */
	void Contact::setEmail(Email* email, int index)
	{
		mEmails[index] = email;
	}

	/*
	 * Getter for the number of websites.
	 */
	const int Contact::getWebsitesCount() const
	{
		return mWebsites.size();
	}

	/*
	 * Getter for website field.
	 */
	const Website* Contact::getWebsite(int index) const
	{
		return mWebsites[index];
	}

	/*
	 * Setter for website field.
	 */
	void Contact::setWebsite(Website* website, int index)
	{
		mWebsites[index] = website;
	}

	/*
	 * Getter for the number of instant messagings.
	 */
	const int Contact::getInstantMessagingsCount() const
	{
		return mInstantMessagings.size();
	}

	/*
	 * Getter for instant messaging field.
	 */
	const InstantMessaging* Contact::getInstantMessaging(int index) const
	{
		return mInstantMessagings[index];
	}

	/*
	 * Setter for instant messaging field.
	 */
	void Contact::setInstantMessaging(InstantMessaging* instantMessaging, int index)
	{
		mInstantMessagings[index] = instantMessaging;
	}

	/*
	 * Getter for note field.
	 */
	const Note* Contact::getNote() const
	{
		return mNote;
	}

	/*
	 * Setter for note field.
	 */
	void Contact::setNote(Note* note)
	{
		mNote = note;
	}

	/*
	 * Getter for the number of organizations.
	 */
	const int Contact::getOrganizationsCount() const
	{
		return mOrganizations.size();
	}

	/*
	 * Getter for organizations field.
	 */
	const Organization* Contact::getOrganization(int index) const
	{
		return mOrganizations[index];
	}

	/*
	 * Setter for organization field.
	 */
	void Contact::setOrganization(Organization* organization, int index)
	{
		mOrganizations[index] = organization;
	}

	/*
	 * Getter for the number of social profiles.
	 */
	const int Contact::getSocialProfilesCount() const
	{
		return mSocialProfiles.size();
	}

	/*
	 * Getter for social profile field.
	 */
	const SocialProfile* Contact::getSocialProfile(int index) const
	{
		return mSocialProfiles[index];
	}

	/*
	 * Setter for social profile field.
	 */
	void Contact::setSocialProfile(SocialProfile* socialProfile, int index)
	{
		mSocialProfiles[index] = socialProfile;
	}
}

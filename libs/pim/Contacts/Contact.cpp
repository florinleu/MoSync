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

#include <mawstring.h>
#include <mawvsprintf.h>

#include "Contact.h"
#include "IX_PIM.h"
#include "util.h"
#include "pim.h"

#include <conprint.h>

using namespace MAUtil;

namespace PIM
{
	/*
	 * Constructor.
	 */
	Contact::Contact():
			mListHandle(getListHandle())
	{
	}

	/*
	 * Destructor.
	 */
	Contact::~Contact()
	{
		cleanFields();
	}

	void Contact::cleanFields(bool cleanID)
	{
		if (cleanID)
		{
			DELETE(mID);
		}
		DELETE(mName);
		DELETE_VECTOR(mAddresses);
		DELETE_VECTOR(mPhones);
		DELETE_VECTOR(mEmails);
		DELETE_VECTOR(mWebsites);
		DELETE_VECTOR(mInstantMessagings);
		DELETE(mNote);
		DELETE_VECTOR(mOrganizations);
		DELETE_VECTOR(mSocialProfiles);
		DELETE_VECTOR(mEvents);
		DELETE_VECTOR(mRelations);
		DELETE(mPhoto);

		DELETE(mBuffer);
	}

	/*
	 * Read the Contact.
	 */
	int Contact::readNext(int flag)
	{
		cleanFields();
		//Get the contacts item handle.
		mHandle = maPimListNext(mListHandle);

		if (mHandle <= 0)
		{
			return -1;
		}

		MA_PIM_ARGS args;
		initArgs(args);
		args.item = mHandle;

		readID(args);

		readFields(args, flag);

		maPimItemClose(mHandle);

		return 0;
	}

	/*
	 * Find the Contact.
	 */
	int Contact::find(int flag)
	{
		cleanFields(false);

		MA_PIM_ARGS args;
		if (!getHandle(getID(), args))
		{
			return -1;
		}

		readFields(args, flag);

		maPimItemClose(mHandle); //fleu TODO check this in the runtime

		return 0;
	}

	/*
	 * Write the Contact.
	 */
	int Contact::write(int flag)
	{
		MA_PIM_ARGS args;
		if (!getHandle(getID(), args))
		{
			return -1;
		}

		if (MATCH_FLAGS(flag, RF_NAME))
		{
			writeName(args);
		}

		if (MATCH_FLAGS(flag, RF_ADDRESS))
		{
			writeAddresses(args);
		}

		if (MATCH_FLAGS(flag, RF_PHONE))
		{
			writePhones(args);
		}

		if (MATCH_FLAGS(flag, RF_EMAIL))
		{
			writeEmails(args);
		}

		maPimItemClose(mHandle);

		return 0;
	}

	/*
	 * Remove the Contact.
	 */
	int Contact::remove()
	{
		MA_PIM_ARGS args;
		if (!getHandle(getID(), args))
		{
			return -1;
		}

		maPimItemRemove(mListHandle, mHandle);

		return 0;
	}

	void Contact::initArgs(MA_PIM_ARGS& args)
	{
		mBuffer = new char[PIM_BUF_SIZE];
		args.buf = mBuffer;
		args.bufSize = PIM_BUF_SIZE;
	}

	void Contact::readID(MA_PIM_ARGS args)
	{
		mID = new ID();
		if (!mID->read(args))
		{
			DELETE(mID);
		}
	}

	void Contact::readName(MA_PIM_ARGS args)
	{
		mName = new Name();
		if (!mName->read(args))
		{
			DELETE(mName);
		}
	}

	void Contact::readAddresses(MA_PIM_ARGS args)
	{
		int countValues = maPimItemFieldCount(mHandle, MA_PIM_FIELD_CONTACT_ADDR);
		if (countValues < 0)
		{
			return;
		}
		for (int i=0; i<countValues; i++)
		{
			Address* address = new Address();
			address->read(args, i);
			mAddresses.add(address);
		}
	}

	void Contact::readPhones(MA_PIM_ARGS args)
	{
		int countValues = maPimItemFieldCount(mHandle, MA_PIM_FIELD_CONTACT_TEL);
		if (countValues < 0)
		{
			return;
		}
		for (int i=0; i<countValues; i++)
		{
			Phone* phone = new Phone();
			phone->read(args, i);
			mPhones.add(phone);
		}
	}

	void Contact::readEmails(MA_PIM_ARGS args)
	{
		int countValues = maPimItemFieldCount(mHandle, MA_PIM_FIELD_CONTACT_EMAIL);
		if (countValues < 0)
		{
			return;
		}
		for (int i=0; i<countValues; i++)
		{
			Email* email = new Email();
			email->read(args, i);
			mEmails.add(email);
		}
	}

	void Contact::readWebsites(MA_PIM_ARGS args)
	{
		int countValues = maPimItemFieldCount(mHandle, MA_PIM_FIELD_CONTACT_URL);
		if (countValues < 0)
		{
			return;
		}
		for (int i=0; i<countValues; i++)
		{
			Website* website = new Website();
			website->read(args, i);
			mWebsites.add(website);
		}
	}

	void Contact::readInstantMessagings(MA_PIM_ARGS args)
	{
		int countValues = maPimItemFieldCount(mHandle, MA_PIM_FIELD_CONTACT_IM);
		if (countValues < 0)
		{
			return;
		}
		for (int i=0; i<countValues; i++)
		{
			InstantMessaging* instantMessaging = new InstantMessaging();
			instantMessaging->read(args, i);
			mInstantMessagings.add(instantMessaging);
		}
	}

	void Contact::readNote(MA_PIM_ARGS args)
	{
		mNote = new Note();
		if (!mNote->read(args))
		{
			DELETE(mNote);
		}
	}

	void Contact::readOrganizations(MA_PIM_ARGS args)
	{
		int countValues = maPimItemFieldCount(mHandle, MA_PIM_FIELD_CONTACT_ORG);
		if (countValues < 0)
		{
			return;
		}
		for (int i=0; i<countValues; i++)
		{
			Organization* organization = new Organization();
			organization->read(args, i);
			mOrganizations.add(organization);
		}
	}

	void Contact::readSocialProfiles(MA_PIM_ARGS args)
	{
		int countValues = maPimItemFieldCount(mHandle, MA_PIM_FIELD_CONTACT_SOCIAL_PROFILE);
		if (countValues < 0)
		{
			return;
		}
		for (int i=0; i<countValues; i++)
		{
			SocialProfile* socialProfile = new SocialProfile();
			socialProfile->read(args, i);
			mSocialProfiles.add(socialProfile);
		}
	}

	void Contact::readEvents(MA_PIM_ARGS args)
	{
		int countValues = maPimItemFieldCount(mHandle, MA_PIM_FIELD_CONTACT_EVENT);
		if (countValues < 0)
		{
			return;
		}
		for (int i=0; i<countValues; i++)
		{
			Event* event = new Event();
			event->read(args, i);
			mEvents.add(event);
		}
	}

	void Contact::readRelations(MA_PIM_ARGS args)
	{
		int countValues = maPimItemFieldCount(mHandle, MA_PIM_FIELD_CONTACT_RELATION);
		if (countValues < 0)
		{
			return;
		}
		for (int i=0; i<countValues; i++)
		{
			Relation* relation = new Relation();
			relation->read(args, i);
			mRelations.add(relation);
		}
	}

	void Contact::readPhoto(MA_PIM_ARGS args)
	{
		mPhoto = new Photo();
		if (!mPhoto->read(args))
		{
			DELETE(mPhoto);
		}
	}

	void Contact::readFields(MA_PIM_ARGS args, int flag)
	{
		if (MATCH_FLAGS(flag, RF_NAME))
		{
			readName(args);
		}

		if (MATCH_FLAGS(flag, RF_ADDRESS))
		{
			readAddresses(args);
		}

		if (MATCH_FLAGS(flag, RF_PHONE))
		{
			readPhones(args);
		}

		if (MATCH_FLAGS(flag, RF_EMAIL))
		{
			readEmails(args);
		}

		if (MATCH_FLAGS(flag, RF_WEBSITE))
		{
			readWebsites(args);
		}

		if (MATCH_FLAGS(flag, RF_INSTANTMESSAGING))
		{
			readInstantMessagings(args);
		}

		if (MATCH_FLAGS(flag, RF_NOTE))
		{
			readNote(args);
		}

		if (MATCH_FLAGS(flag, RF_ORGANIZATION))
		{
			readOrganizations(args);
		}

		if (MATCH_FLAGS(flag, RF_SOCIALPROFILE))
		{
			readSocialProfiles(args);
		}

		if (MATCH_FLAGS(flag, RF_EVENT))
		{
			readEvents(args);
		}

		if (MATCH_FLAGS(flag, RF_RELATION))
		{
			readRelations(args);
		}

		if (MATCH_FLAGS(flag, RF_PHOTO))
		{
			readPhoto(args);
		}
	}

	void Contact::writeName(MA_PIM_ARGS args)
	{
		mName->write(args);
	}

	void Contact::writeAddresses(MA_PIM_ARGS args)
	{
		int count = mAddresses.size();
		if (count < 0)
		{
			return;
		}
		for (int i=0; i<count; i++)
		{
			mAddresses[i]->write(args, i);
		}
	}

	void Contact::writePhones(MA_PIM_ARGS args)
	{
		int count = mPhones.size();
		if (count < 0)
		{
			return;
		}
		for (int i=0; i<count; i++)
		{
			mPhones[i]->write(args, i);
		}
	}

	void Contact::writeEmails(MA_PIM_ARGS args)
	{
		int count = mEmails.size();
		if (count < 0)
		{
			return;
		}
		for (int i=0; i<count; i++)
		{
			mEmails[i]->write(args, i);
		}
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
	 * Getter for ID field.
	 */
	void Contact::setID(wchar* id)
	{
		if (mID == NULL)
		{
			mID = new ID();
		}
		mID->setID(id);
	}

	/*
	 * Getter for name field.
	 */
	Name* Contact::getName() const
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

	/**
	 * Delete the given name.
	 */
	void Contact::removeName()
	{
		MA_PIM_ARGS args;
		if (getHandle(getID(), args))
		{
			mName->remove(mHandle);
			DELETE(mName);

			maPimItemClose(mHandle);
		}
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
	Address* Contact::getAddress(int index) const
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
	 * Delete the given address.
	 */
	void Contact::removeAddress(int index)
	{
		if (index < mAddresses.size())
		{
			MA_PIM_ARGS args;
			if (getHandle(getID(), args))
			{
				Address* address = mAddresses[index];
				address->remove(mHandle, index);
				mAddresses.remove(index);
				DELETE(address);

				maPimItemClose(mHandle);
			}
		}
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
	Phone* Contact::getPhone(int index) const
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
	 * Delete the given phone.
	 */
	void Contact::removePhone(int index)
	{
		if (index < mPhones.size())
		{
			MA_PIM_ARGS args;
			if (getHandle(getID(), args))
			{
				Phone* phone = mPhones[index];
				phone->remove(mHandle, index);
				mPhones.remove(index);
				DELETE(phone);

				maPimItemClose(mHandle);
			}
		}
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
	Email* Contact::getEmail(int index) const
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
	 * Delete the given e-mail.
	 */
	void Contact::removeEmail(int index)
	{
		if (index < mEmails.size())
		{
			MA_PIM_ARGS args;
			if (getHandle(getID(), args))
			{
				Email* email = mEmails[index];
				email->remove(mHandle, index);
				mEmails.remove(index);
				DELETE(email);

				maPimItemClose(mHandle);
			}
		}
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
	Website* Contact::getWebsite(int index) const
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
	InstantMessaging* Contact::getInstantMessaging(int index) const
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
	Note* Contact::getNote() const
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
	Organization* Contact::getOrganization(int index) const
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
	SocialProfile* Contact::getSocialProfile(int index) const
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

	/*
	 * Getter for the number of events.
	 */
	const int Contact::getEventsCount() const
	{
		return mEvents.size();
	}

	/*
	 * Getter for event field.
	 */
	Event* Contact::getEvent(int index) const
	{
		return mEvents[index];
	}

	/*
	 * Setter for event field.
	 */
	void Contact::setEvent(Event* event, int index)
	{
		mEvents[index] = event;
	}

	/*
	 * Getter for the number of relations.
	 */
	const int Contact::getRelationsCount() const
	{
		return mRelations.size();
	}

	/*
	 * Getter for relation field.
	 */
	Relation* Contact::getRelation(int index) const
	{
		return mRelations[index];
	}

	/*
	 * Setter for relation field.
	 */
	void Contact::setRelation(Relation* relation, int index)
	{
		mRelations[index] = relation;
	}

	/*
	 * Getter for photo field.
	 */
	Photo* Contact::getPhoto() const
	{
		return mPhoto;
	}

	/*
	 * Setter for photo field.
	 */
	void Contact::setPhoto(Photo* photo)
	{
		mPhoto = photo;
	}

	/**
	 * Finds a contact by it's id.
	 * @param id The contact's id.
	 * @param args
	 * @return true on success.
	 */
	bool Contact::getHandle(const wchar* id, MA_PIM_ARGS& args)
	{
		if ((getID() == NULL) || (wcslen(getID()) == 0))
		{
			return false;
		}

		initArgs(args);
		args.bufSize = wcslen(id)*sizeof(wchar);
		memset(args.buf, 0, PIM_BUF_SIZE);
		memcpy(args.buf, id, args.bufSize);

		mHandle = maPimListFind(mListHandle, &args); //why always search?
		args.item = mHandle;
		if (mHandle <= 0)
		{
			return false;
		}

		return true;
	}
}

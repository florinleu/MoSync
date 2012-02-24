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

		if ((flag & RF_PHOTO) != 0)
		{
			mPhoto = new Photo();
			mPhoto->read(args);
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
	 * Getter for photo field.
	 */
	const Photo* Contact::getPhoto() const
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
}

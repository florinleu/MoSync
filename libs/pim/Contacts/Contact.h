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
 * @file Contact.h
 * @author Florin Leu
 * @date 08 Feb 2011
 *
 * @brief PIM Contact class.
 *
 **/

 #ifndef __CONTACT_H__
 #define __CONTACT_H__

#include <MAUtil/Vector.h>

#include "ID.h"
#include "Name.h"
#include "Address.h"
#include "Phone.h"
#include "Photo.h"
#include "Photo.h"
#include "Email.h"
#include "Website.h"
#include "Organization.h"
#include "Event.h"
#include "Note.h"
#include "InstantMessaging.h"
#include "Relation.h"
#include "SocialProfile.h"

namespace PIM
{
	class Contact
	{
	public:
		enum ReadFlags {
			RF_NAME = 0x1,
			RF_ADDRESS = 0x2,
			RF_PHONE = 0x4,
			RF_PHOTO = 0x8,
			RF_ALL = 0xF
		};

		Contact(const MAHandle listHandle);
		~Contact();

		void clean();
		int readNext(int flag = RF_ALL);

		const wchar* getID() const;

		const Name* getName() const;
		void setName(Name* name);

		const int getAddressesCount() const;
		const Address* getAddress(int index) const;
		void setAddress(Address* address, int index);

		const int getPhonesCount() const;
		const Phone* getPhone(int index) const;
		void setPhone(Phone* phone, int index);

		const Photo* getPhoto() const;
		void setPhoto(Photo* photo);

//	int write();
//	int find();
//	int remove();

	private:
		Contact();

		ID* mID;
		Name* mName;
		MAUtil::Vector<Address*> mAddresses;
		MAUtil::Vector<Phone*> mPhones;
		Photo* mPhoto;
		MAUtil::Vector<Email*> mEmail;
		Website** mWebsite;
		Organization** mOrganization;
		Event** mEvent;
		Note* mNote;
		InstantMessaging** mInstantMessaging;
		Relation** mRelation;
		SocialProfile** mSocialProfile;

		const MAHandle mListHandle;
		MAHandle mHandle;
		char* mBuffer;
	};
}

#endif //__CONTACT_H__

/*
NAME
WP7			FirstName, LastName, MiddleName, Nickname, Title, Suffix, YomiFirstName, YomiLastName
iOS			FirstName, LastName, MiddleName, Nickname, Prefix, Suffix, FirstNamePhonetic, LastNamePhonetic, MiddleNamePhonetic
Android		GivenName, FamilyName, MiddleName, NickName, Prefix, Suffix, PhoneticGivenNAme, PhoneticMiddleName, PhoneticFamilyName, DisplayName

ADDRESS
WP7-m		AddressLine1(Street), City, StateProvince, PostalCode, CountryRegion, Building, FloorLevel, AddressLine2, IsUnknown
iOS-m		Street, City, State, ZIP, Country, CountryCode, Type, Label
Android-m	Street, City, Region, Postcode, Country, POBox, Neighborhood, FormattedAddress, Type (Label)

ORGANIZATION
WP7-m		CompanyName, JobTitle, OfficeLocation, YomiCompanyName
iOS			Organization, JobTitle, Department
Android-m	Company, Title, Department, JobDescription, Symbol, PhoneticName, OficeLocation, Type (Label)
*/

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
//	enum eErrors
//	{
//		ERR_NOT_OPENED = -1,
//		ERR_END_OF_LIST = -2,
//		ERR_INVALID_ID = -3
//	};

	enum eReadFlags {
		RF_NONE = 0,
		RF_NAME = 0x1,
		RF_ADDRESS = 0x2,
		RF_PHONE = 0x4,
		RF_EMAIL = 0x8,
		RF_WEBSITE = 0x10,
		RF_INSTANTMESSAGING = 0x20,
		RF_NOTE = 0x40,
		RF_ORGANIZATION = 0x80,
		RF_SOCIALPROFILE = 0x100,
		RF_EVENT = 0x200,
		RF_RELATION = 0x400,
		RF_PHOTO = 0x800,
		RF_ALL = 0xFFF
	};

	class Contact
	{
		public:
			Contact();
			~Contact();

			int readNext(int flag = RF_ALL);
			int find(int flag = RF_ALL);
			int write(int flag = RF_ALL);
			int remove();

			const wchar* getID() const;
			void setID(wchar* id);

			Name* getName() const;
			void setName(Name* name);
			void removeName();

			const int getAddressesCount() const;
			Address* getAddress(int index) const;
			void add(Address* address);
			void setAddress(Address* address, int index);
			void removeAddress(int index);

			const int getPhonesCount() const;
			void add(Phone* phone);
			Phone* getPhone(int index) const;
			void setPhone(Phone* phone, int index);
			void removePhone(int index);

			const int getEmailsCount() const;
			void add(Email* email);
			Email* getEmail(int index) const;
			void setEmail(Email* email, int index);
			void removeEmail(int index);

			const int getWebsitesCount() const;
			void add(Website* website);
			Website* getWebsite(int index) const;
			void setWebsite(Website* website, int index);
			void removeWebsite(int index);

			const int getInstantMessagingsCount() const;
			void add(InstantMessaging* instantMessaging);
			InstantMessaging* getInstantMessaging(int index) const;
			void setInstantMessaging(InstantMessaging* instantMessaging, int index);
			void removeInstantMessaging(int index);

			const int getNotesCount() const;
			void add(Note* note);
			Note* getNote(int index) const;
			void setNote(Note* note, int index);
			void removeNote(int index);

			const int getOrganizationsCount() const;
			void add(Organization* organization);
			Organization* getOrganization(int index) const;
			void setOrganization(Organization* organization, int index);
			void removeOrganization(int index);

			const int getSocialProfilesCount() const;
			void add(SocialProfile* socialProfile);
			SocialProfile* getSocialProfile(int index) const;
			void setSocialProfile(SocialProfile* socialProfile, int index);
			void removeSocialProfile(int index);

			const int getEventsCount() const;
			void add(Event* event);
			Event* getEvent(int index) const;
			void setEvent(Event* event, int index);
			void removeEvent(int index);

			const int getRelationsCount() const;
			void add(Relation* relation);
			Relation* getRelation(int index) const;
			void setRelation(Relation* relation, int index);
			void removeRelation(int index);

			Photo* getPhoto() const;
			void setPhoto(Photo* photo);

		private:
			void cleanFields(bool cleanID = true);
			void close();

			void initArgs(MA_PIM_ARGS& args);
			void readID(MA_PIM_ARGS args);
			void readName(MA_PIM_ARGS args);
			void readAddresses(MA_PIM_ARGS args);
			void readPhones(MA_PIM_ARGS args);
			void readEmails(MA_PIM_ARGS args);
			void readWebsites(MA_PIM_ARGS args);
			void readInstantMessagings(MA_PIM_ARGS args);
			void readNote(MA_PIM_ARGS args);
			void readOrganizations(MA_PIM_ARGS args);
			void readSocialProfiles(MA_PIM_ARGS args);
			void readEvents(MA_PIM_ARGS args);
			void readRelations(MA_PIM_ARGS args);
			void readPhoto(MA_PIM_ARGS args);

			void readFields(MA_PIM_ARGS args, int flag);

			void writeName(MA_PIM_ARGS args);
			void writeAddresses(MA_PIM_ARGS args);
			void writePhones(MA_PIM_ARGS args);
			void writeEmails(MA_PIM_ARGS args);
			void writeWebsites(MA_PIM_ARGS args);
			void writeInstantMessagings(MA_PIM_ARGS args);
			void writeNote(MA_PIM_ARGS args);
			void writeOrganizations(MA_PIM_ARGS args);
			void writeSocialProfile(MA_PIM_ARGS args);
			void writeEvent(MA_PIM_ARGS args);
			void writeRelation(MA_PIM_ARGS args);
			void writePhoto(MA_PIM_ARGS args);

			/**
			 * Finds a contact by it's id.
			 * @param id The contact's id.
			 * @param args
			 * @return true on success.
			 */
			bool getHandle(const wchar* id, MA_PIM_ARGS& args);

		private:
			ID* mID;
			Name* mName;
			MAUtil::Vector<Address*> mAddresses;
			MAUtil::Vector<Phone*> mPhones;
			MAUtil::Vector<Email*> mEmails;
			MAUtil::Vector<Website*> mWebsites;
			MAUtil::Vector<InstantMessaging*> mInstantMessagings;
			MAUtil::Vector<Note*> mNotes;
			MAUtil::Vector<Organization*> mOrganizations;
			MAUtil::Vector<SocialProfile*> mSocialProfiles;
			MAUtil::Vector<Event*> mEvents;
			MAUtil::Vector<Relation*> mRelations;
			Photo* mPhoto;

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

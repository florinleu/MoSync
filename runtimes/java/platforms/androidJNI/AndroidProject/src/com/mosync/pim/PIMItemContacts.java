package com.mosync.pim;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_FIELD_INVALID;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_FIELD_UNSUPPORTED;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_INDEX_INVALID;

import java.util.ArrayList;
import java.util.Iterator;

import com.mosync.internal.android.MoSyncError;

import android.content.ContentProviderOperation;
import android.content.ContentProviderResult;
import android.content.ContentResolver;
import android.database.Cursor;
import android.provider.ContactsContract;
import android.provider.ContactsContract.Contacts;
import android.provider.ContactsContract.RawContacts;

public class PIMItemContacts extends PIMItem {

	PIMFieldAddress mAddress;
	PIMFieldBirthday mBirthday;
	PIMFieldClass mClass;
	PIMFieldEmail mEmail;
	PIMFieldFormattedAddress mFormattedAddress;
	PIMFieldFormattedName mFormattedName;
	PIMFieldName mName;
	PIMFieldNickname mNickname;
	PIMFieldNote mNote;
	PIMFieldOrganization mOrganization;
	PIMFieldPhoto mPhoto;
	PIMFieldPhotoURL mPhotoURL;
	PIMFieldPublicKey mPublicKey;
	PIMFieldPublicKeyString mPublicKeyString;
	PIMFieldRevision mRevision;
	PIMFieldPhone mPhone;
	PIMFieldTitle mTitle;
	PIMFieldUID mUID;
	PIMFieldURL mURL;
	PIMFieldIM mIM;
	PIMFieldRelation mRelation;
	PIMFieldOrganizationInfo mOrganizationInfo;
	PIMFieldEvent mEvent;

	/**
	 * Constructor
	 */
	PIMItemContacts(boolean isNew) {
		mPIMFields = new ArrayList<PIMField>();
		mAddress = new PIMFieldAddress();
		mBirthday = new PIMFieldBirthday();
		mClass = new PIMFieldClass();
		mEmail = new PIMFieldEmail();
		mFormattedAddress = new PIMFieldFormattedAddress();
		mFormattedName = new PIMFieldFormattedName();
		mName = new PIMFieldName();
		mNickname = new PIMFieldNickname();
		mNote = new PIMFieldNote();
		mOrganization = new PIMFieldOrganization();
		mPhoto = new PIMFieldPhoto();
		mPhotoURL = new PIMFieldPhotoURL();
		mPublicKey = new PIMFieldPublicKey();
		mPublicKeyString = new PIMFieldPublicKeyString();
		mRevision = new PIMFieldRevision();
		mPhone = new PIMFieldPhone();
		mTitle = new PIMFieldTitle();
		mUID = new PIMFieldUID();
		mURL = new PIMFieldURL();
		mIM = new PIMFieldIM();
		mRelation = new PIMFieldRelation();
		mOrganizationInfo = new PIMFieldOrganizationInfo();
		mEvent = new PIMFieldEvent();
		mPIMFields.add(mAddress);
		mPIMFields.add(mBirthday);
		mPIMFields.add(mClass);
		mPIMFields.add(mEmail);
		mPIMFields.add(mFormattedAddress);
		mPIMFields.add(mFormattedName);
		mPIMFields.add(mName);
		mPIMFields.add(mNickname);
		mPIMFields.add(mNote);
		mPIMFields.add(mOrganization);
		mPIMFields.add(mPhoto);
		mPIMFields.add(mPhotoURL);
		mPIMFields.add(mPublicKey);
		mPIMFields.add(mPublicKeyString);
		mPIMFields.add(mRevision);
		mPIMFields.add(mPhone);
		mPIMFields.add(mTitle);
		mPIMFields.add(mUID);
		mPIMFields.add(mURL);
		mPIMFields.add(mIM);
		mPIMFields.add(mRelation);
		mPIMFields.add(mOrganizationInfo);
		// mPIMFields.add(mEvent);
	}

	/**
	 * Read the item with contactId.
	 * @param cr
	 * @param contactId
	 */
	void read(ContentResolver cr, String contactId) {
		DebugPrint("PIMItem.read(" + cr + ", " + contactId + ")");

		Iterator<PIMField> fieldsIt = mPIMFields.iterator();

		while (fieldsIt.hasNext()) {
			fieldsIt.next().read(cr, contactId);
		}
	}
}

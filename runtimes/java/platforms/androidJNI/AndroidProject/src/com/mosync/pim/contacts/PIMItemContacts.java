package com.mosync.pim.contacts;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;

import java.util.ArrayList;
import java.util.Iterator;

import android.content.ContentProviderOperation;
import android.content.ContentProviderResult;
import android.content.ContentResolver;
import android.provider.ContactsContract;
import android.provider.ContactsContract.RawContacts;

import com.mosync.pim.*;

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
	PIMFieldSocialProfile mSocialProfile;

	/**
	 * Constructor
	 */
	public PIMItemContacts(String id, boolean isNew) {
		super(isNew);
		DebugPrint("PIMItemContacts()");
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
		mSocialProfile = new PIMFieldSocialProfile();
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
		mPIMFields.add(mEvent);
		mPIMFields.add(mSocialProfile);
		mUID.read(id);
	}

	// /**
	// * Read the item with contactId.
	// * @param cr
	// * @param contactId
	// */
	// public void read() {
	// DebugPrint("PIMItemContacts.read()");
	//
	// Iterator<PIMField> fieldsIt = mPIMFields.iterator();
	//
	// DebugPrint("Length = " + mPIMFields.size());
	//
	// while (fieldsIt.hasNext()) {
	// fieldsIt.next().read(getID());
	// }
	// }

	protected String getID() {
		return mUID.getValue();
	}

	protected void delete(ContentResolver cr) {
		if (mState == State.ADDED) {
			return;
		}

		Iterator<PIMField> fieldsIt = mPIMFields.iterator();

		while (fieldsIt.hasNext()) {
			fieldsIt.next().close();
		}

		String id = mUID.getSpecificData(0);
		cr.delete(RawContacts.CONTENT_URI, RawContacts.CONTACT_ID + " = ?",
				new String[] { id });
	}

	/**
	 * Closes the item
	 */
	protected void close(ContentResolver cr) {
		DebugPrint("PIMItem.close()");
		ArrayList<ContentProviderOperation> ops = new ArrayList<ContentProviderOperation>();
		Iterator<PIMField> fieldsIt = mPIMFields.iterator();

		int rawContactIndex = 0;
		if (mState == State.ADDED) {
			rawContactIndex = ops.size();
			ops.add(ContentProviderOperation.newInsert(RawContacts.CONTENT_URI)
					.withValue(RawContacts.ACCOUNT_TYPE, null)
					.withValue(RawContacts.ACCOUNT_NAME, null).build());
			while (fieldsIt.hasNext()) {
				fieldsIt.next().add(ops, rawContactIndex);
			}
		} else if (mState == State.UPDATED) {
			rawContactIndex = Integer.parseInt(mUID.getSpecificData(0));
			while (fieldsIt.hasNext()) {
				fieldsIt.next().update(cr, ops, rawContactIndex);
			}
		}

		setState(State.NONE);
		try {
			ContentProviderResult[] res = cr.applyBatch(
					ContactsContract.AUTHORITY, ops);
		} catch (Exception e) {
			e.printStackTrace();
			DebugPrint("Exception: " + e.getMessage());
		}

		fieldsIt = mPIMFields.iterator();

		while (fieldsIt.hasNext()) {
			fieldsIt.next().close();
		}
	}
}

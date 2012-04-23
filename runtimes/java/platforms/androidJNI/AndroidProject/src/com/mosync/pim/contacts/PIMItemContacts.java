package com.mosync.pim.contacts;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;

import java.util.ArrayList;
import java.util.Iterator;

import android.content.ContentProviderOperation;
import android.content.ContentProviderResult;
import android.content.ContentResolver;
import android.content.OperationApplicationException;
import android.database.Cursor;
import android.os.RemoteException;
import android.provider.ContactsContract;
import android.provider.ContactsContract.Data;
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

	protected void delete() {
		DebugPrint("PIMItemContacts.delete()");
		if (mState == State.ADDED) {
			return;
		}

		Iterator<PIMField> fieldsIt = mPIMFields.iterator();

		while (fieldsIt.hasNext()) {
			fieldsIt.next().close();
		}

		try {
			Cursor cursor = getContentResolver().query(Data.CONTENT_URI,
					new String[] { Data.CONTACT_ID }, Data.LOOKUP_KEY + "=?",
					new String[] { mUID.getSpecificData(0) }, null);
			if (cursor.moveToNext()) {
				String id = cursor.getString(cursor
						.getColumnIndex(Data.CONTACT_ID));
				DebugPrint("id = " + id);
				int deleted = getContentResolver().delete(
						RawContacts.CONTENT_URI,
						RawContacts.CONTACT_ID + " = ?", new String[] { id });
				DebugPrint("deleted rows = " + deleted);
			}

			cursor.close();
			cursor = null;
		} catch (Exception e) {
		}
	}

	/**
	 * Closes the item
	 */
	protected void close() {
		DebugPrint("PIMItemContacts.close()");
		ArrayList<ContentProviderOperation> ops = new ArrayList<ContentProviderOperation>();
		Iterator<PIMField> fieldsIt = mPIMFields.iterator();

		// int rawContactIndex = 0;
		if (mState == State.ADDED) {
			DebugPrint("Add item.");
			// rawContactIndex = ops.size();
			ops.add(ContentProviderOperation.newInsert(RawContacts.CONTENT_URI)
					.withValue(RawContacts.ACCOUNT_TYPE, null)
					.withValue(RawContacts.ACCOUNT_NAME, null).build());
			while (fieldsIt.hasNext()) {
				// fieldsIt.next().add(ops, rawContactIndex);
				fieldsIt.next().add(ops, mUID.getSpecificData(0));
			}
		} else if (mState == State.UPDATED) {
			DebugPrint("Update item.");
			// Cursor cursor = getContentResolver().query(Data.CONTENT_URI,
			// new String[] { Data.CONTACT_ID }, Data.LOOKUP_KEY + "=?",
			// new String[] { mUID.getSpecificData(0) }, null);
			// if (cursor.moveToNext()) {
			// String id = cursor.getString(cursor
			// .getColumnIndex(Data.CONTACT_ID));
			//
			// try {
			// rawContactIndex = Integer.parseInt(id);
			DebugPrint("Fields = " + mPIMFields.size());
			while (fieldsIt.hasNext()) {
				fieldsIt.next().update(getContentResolver(), ops,
						mUID.getSpecificData(0));
			}
			// } catch (NumberFormatException e) {
			// DebugPrint("Cannot parse id: " + id);
			// }
			// }
		}
		setState(State.NONE);
		try {
			DebugPrint("APPLY BATCH " + ops.size());
			if (ops.size() > 0) {
				ContentProviderResult[] res = getContentResolver().applyBatch(
						ContactsContract.AUTHORITY, ops);
				DebugPrint("Result = " + res.length);
			}
		} catch (OperationApplicationException e) {
			DebugPrint("OperationApplicationException: " + e.getMessage());
			e.printStackTrace();
		} catch (RemoteException e) {
			DebugPrint("RemoteException: " + e.getMessage());
			e.printStackTrace();
		}

		fieldsIt = mPIMFields.iterator();

		while (fieldsIt.hasNext()) {
			fieldsIt.next().close();
		}
	}
}

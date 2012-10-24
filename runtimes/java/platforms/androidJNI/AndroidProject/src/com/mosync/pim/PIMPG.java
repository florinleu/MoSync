package com.mosync.pim;

import java.util.ArrayList;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONException;

import android.app.Activity;
import android.content.ContentResolver;
import android.database.Cursor;
import android.provider.ContactsContract.CommonDataKinds.Email;
import android.provider.ContactsContract.CommonDataKinds.Event;
import android.provider.ContactsContract.CommonDataKinds.Im;
import android.provider.ContactsContract.CommonDataKinds.Nickname;
import android.provider.ContactsContract.CommonDataKinds.Note;
import android.provider.ContactsContract.CommonDataKinds.Organization;
import android.provider.ContactsContract.CommonDataKinds.Phone;
import android.provider.ContactsContract.CommonDataKinds.Photo;
import android.provider.ContactsContract.CommonDataKinds.StructuredName;
import android.provider.ContactsContract.CommonDataKinds.Website;
import android.provider.ContactsContract.Contacts;
import android.provider.ContactsContract.Data;
import android.provider.ContactsContract.CommonDataKinds.StructuredPostal;

import com.mosync.internal.android.MoSyncThread;

public class PIMPG {

	Cursor mCursor;

	/**
	 * The MoSync thread object.
	 */
	private MoSyncThread mMoSyncThread;

	/**
	 * Constructor.
	 * @param thread
	 *            The MoSync thread.
	 */
	public PIMPG(MoSyncThread thread) {
		mMoSyncThread = thread;
	}

	/**
	 * @return The Activity object.
	 */
	public Activity getActivity() {
		return mMoSyncThread.getActivity();
	}

	/**
	 * @return The Content Resolver.
	 */
	public ContentResolver getContentResolver() {
		return getActivity().getContentResolver();
	}

	/**
	 * Searches for the first contact that has a specific keyword inside given
	 * fields.
	 * @param fields
	 *            The fields to search into.
	 * @param filter
	 *            The keyword to search for.
	 * @return
	 */
	public int maPIMPGContactsFind(JSONArray fields, String filter) {

		boolean reset = true;

		if (filter.length() == 0) {
			filter = "%";
		} else {
			filter = "%" + filter + "%";
		}

		if (reset) {
			if (mCursor != null) {
				mCursor.close();
			}
			mCursor = getContentResolver().query(Contacts.CONTENT_URI,
					new String[] { Contacts._ID }, null, null, null);
		}

		while (mCursor.moveToNext()) {
			getContentResolver().query(Data.CONTENT_URI,
					buildProjection(fields), buildSelection(),
					buildSelectionArgs(), Data.CONTACT_ID + " ASC");
		}

		return 0;
	}

	String[] buildProjection(JSONArray fields) {

		List<String> projection = new ArrayList<String>();
		String field;

		for (int i = 0; i < fields.length(); i++) {
			try {
				field = fields.getString(i);

				try {
					if (field.contains("id")) {
						projection.add(Data.CONTACT_ID);
					} else if (field.contains("displayName")) {
						projection.add(StructuredName.DISPLAY_NAME);
					} else if (field.contains("name")) {
						projection.add(StructuredName.DISPLAY_NAME);
						projection.add(StructuredName.FAMILY_NAME);
						projection.add(StructuredName.GIVEN_NAME);
						projection.add(StructuredName.MIDDLE_NAME);
						projection.add(StructuredName.PREFIX);
						projection.add(StructuredName.SUFFIX);
						projection.add(StructuredName.PHONETIC_FAMILY_NAME);
						projection.add(StructuredName.PHONETIC_GIVEN_NAME);
						projection.add(StructuredName.PHONETIC_MIDDLE_NAME);
					} else if (field.contains("nickname")) {
						projection.add(Nickname.NAME);
					} else if (field.contains("phoneNumbers")) {
						projection.add(Phone._ID);
						projection.add(Phone.NUMBER);
						projection.add(Phone.TYPE);
					} else if (field.contains("emails")) {
						projection.add(Email._ID);
						projection.add(Email.DATA);
						projection.add(Email.TYPE);
					} else if (field.contains("addresses")) {
						projection.add(StructuredPostal._ID);
						projection.add(StructuredPostal.POBOX);
						projection.add(StructuredPostal.STREET);
						projection.add(StructuredPostal.CITY);
						projection.add(StructuredPostal.REGION);
						projection.add(StructuredPostal.POSTCODE);
						projection.add(StructuredPostal.COUNTRY);
						projection.add(StructuredPostal.NEIGHBORHOOD);
						projection.add(StructuredPostal.TYPE);
					} else if (field.contains("ims")) {
						projection.add(Im._ID);
						projection.add(Im.DATA);
						projection.add(Im.PROTOCOL);
						projection.add(Im.TYPE);
					} else if (field.contains("organizations")) {
						projection.add(Organization._ID);
						projection.add(Organization.COMPANY);
						projection.add(Organization.DEPARTMENT);
						projection.add(Organization.JOB_DESCRIPTION);
						projection.add(Organization.SYMBOL);
						projection.add(Organization.PHONETIC_NAME);
						projection.add(Organization.OFFICE_LOCATION);
						projection.add(Organization.TYPE);
					} else if (field.contains("birthday")) {
						projection.add(Event._ID);
						projection.add(Event.START_DATE);
						projection.add(Event.TYPE);
					} else if (field.contains("note")) {
						projection.add(Note.NOTE);
					} else if (field.contains("photos")) {
						projection.add(Photo._ID);
						projection.add(Photo.PHOTO);
					} else if (field.contains("categories")) {

					} else if (field.contains("urls")) {
						projection.add(Website._ID);
						projection.add(Website.URL);
						projection.add(Website.TYPE);
					}
				} catch (UnsupportedOperationException e) {
					// adding to this List is not supported.
				} catch (ClassCastException e) {
					// the class of the object is inappropriate for this List.
				} catch (IllegalArgumentException e) {
					// the object cannot be added to this List.
				}
			} catch (JSONException e) {
				// DebugPrint
				e.printStackTrace();
			}
		}

		return projection.toArray(new String[projection.size()]);
	}

	String buildSelection() {
		return null;
	}

	String[] buildSelectionArgs() {
		return null;
	}
}

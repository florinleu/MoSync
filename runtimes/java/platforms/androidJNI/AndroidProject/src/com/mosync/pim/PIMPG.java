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
					buildProjection(fields, filter), buildSelection(),
					buildSelectionArgs(), Data.CONTACT_ID + " ASC");
		}

		return 0;
	}

	/**
	 * Build the projection for the query.
	 * @param fields
	 *            The fields to add to the projection.
	 * @param filter
	 *            The keyword to search for.
	 * @return The projection.
	 * @note TODO Special cases: fields empty, fields = "*".
	 */
	String[] buildProjection(JSONArray fields, String filter) {

		List<String> projection = new ArrayList<String>();
		List<String> selection = new ArrayList<String>();
		List<String> args = new ArrayList<String>();
		String field;

		for (int i = 0; i < fields.length(); i++) {
			try {
				field = fields.getString(i);

				try {
					if (field.contains("id")) {
						projection.add(Data.CONTACT_ID);
						selection.add("(" + Data.CONTACT_ID + " = ? )");
						args.add(filter.substring(1, filter.length() - 1));
					} else if (field.contains("displayName")) {
						projection.add(StructuredName.DISPLAY_NAME);
						selection
								.add("(" + Contacts.DISPLAY_NAME + " LIKE ? )");
						args.add(filter);
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
						selection.add("(" + StructuredName.DISPLAY_NAME
								+ " LIKE ? AND " + Data.MIMETYPE + " = ? )");
						args.add(filter);
						args.add(StructuredName.CONTENT_ITEM_TYPE);
					} else if (field.contains("nickname")) {
						projection.add(Nickname.NAME);
						selection.add("(" + Nickname.NAME + " LIKE ? AND "
								+ Data.MIMETYPE + " = ? )");
						args.add(filter);
						args.add(Nickname.CONTENT_ITEM_TYPE);
					} else if (field.contains("phoneNumbers")) {
						projection.add(Phone._ID);
						projection.add(Phone.NUMBER);
						projection.add(Phone.TYPE);
						selection.add("(" + Phone.NUMBER + " LIKE ? AND "
								+ Data.MIMETYPE + " = ? )");
						args.add(filter);
						args.add(Phone.CONTENT_ITEM_TYPE);

					} else if (field.contains("emails")) {
						projection.add(Email._ID);
						projection.add(Email.DATA);
						projection.add(Email.TYPE);
						selection.add("(" + Email.ADDRESS + " LIKE ? AND "
								+ Data.MIMETYPE + " = ? )");
						args.add(filter);
						args.add(Email.CONTENT_ITEM_TYPE);
					} else if (field.contains("addresses")) {
						projection.add(StructuredPostal._ID);
						projection.add(StructuredPostal.POBOX);
						projection.add(StructuredPostal.STREET);
						projection.add(StructuredPostal.CITY);
						projection.add(StructuredPostal.REGION);
						projection.add(StructuredPostal.POSTCODE);
						projection.add(StructuredPostal.COUNTRY);
						projection.add(StructuredPostal.NEIGHBORHOOD);
						projection.add(StructuredPostal.FORMATTED_ADDRESS);
						projection.add(StructuredPostal.TYPE);
						selection.add("(" + StructuredPostal.FORMATTED_ADDRESS
								+ " LIKE ? AND " + Data.MIMETYPE + " = ? )");
						args.add(filter);
						args.add(StructuredPostal.CONTENT_ITEM_TYPE);
					} else if (field.contains("ims")) {
						projection.add(Im._ID);
						projection.add(Im.DATA);
						projection.add(Im.PROTOCOL);
						projection.add(Im.TYPE);
						selection.add("(" + Im.DATA + " LIKE ? AND "
								+ Data.MIMETYPE + " = ? )");
						args.add(filter);
						args.add(Im.CONTENT_ITEM_TYPE);
					} else if (field.contains("organizations")) {
						projection.add(Organization._ID);
						projection.add(Organization.COMPANY);
						projection.add(Organization.DEPARTMENT);
						projection.add(Organization.JOB_DESCRIPTION);
						projection.add(Organization.SYMBOL);
						projection.add(Organization.PHONETIC_NAME);
						projection.add(Organization.OFFICE_LOCATION);
						projection.add(Organization.TYPE);
						selection.add("(" + Organization.COMPANY
								+ " LIKE ? AND " + Data.MIMETYPE + " = ? )");
						args.add(filter);
						args.add(Organization.CONTENT_ITEM_TYPE);
					} else if (field.contains("birthday")) {
						projection.add(Event._ID);
						projection.add(Event.START_DATE);
						projection.add(Event.TYPE);
					} else if (field.contains("note")) {
						projection.add(Note.NOTE);
						selection.add("(" + Note.NOTE + " LIKE ? AND "
								+ Data.MIMETYPE + " = ? )");
						args.add(filter);
						args.add(Note.CONTENT_ITEM_TYPE);
					} else if (field.contains("photos")) {
						projection.add(Photo._ID);
						projection.add(Photo.PHOTO);
					} else if (field.contains("categories")) {

					} else if (field.contains("urls")) {
						projection.add(Website._ID);
						projection.add(Website.URL);
						projection.add(Website.TYPE);
						selection.add("(" + Website.URL + " LIKE ? AND "
								+ Data.MIMETYPE + " = ? )");
						args.add(filter);
						args.add(Website.CONTENT_ITEM_TYPE);
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

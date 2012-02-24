package com.mosync.pim.contacts;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_LIST_UNAVAILABLE;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_NONE;

import android.content.ContentResolver;
import android.database.Cursor;
import android.provider.ContactsContract.Contacts;

import com.mosync.pim.*;

public class PIMListContacts extends PIMList {

	public PIMListContacts() {
		DebugPrint("PIMListContacts()");
	}

	protected PIMItem createItem() {
		PIMItemContacts p = new PIMItemContacts("", true);
		mList.add(p);
		return p;
	}

	/*
	 * Read the contacts list.
	 */
	public int read() {
		DebugPrint("PIMListContacts.read()");
		Cursor listCursor = null;
		// try to query for contacts
		try {
			listCursor = getContentResolver().query(Contacts.CONTENT_URI,
					new String[] { Contacts.LOOKUP_KEY }, null, null, null);
		} catch (Exception e) {
			return throwError(MA_PIM_ERR_LIST_UNAVAILABLE,
					PIMError.PANIC_LIST_UNAVAILABLE,
					PIMError.sStrListUnavailable);
		}

		if (listCursor == null) {
			return throwError(MA_PIM_ERR_LIST_UNAVAILABLE,
					PIMError.PANIC_LIST_UNAVAILABLE,
					PIMError.sStrListUnavailable);
		}

		// create the items
		while (listCursor.moveToNext()) {
			String contactId = listCursor.getString(listCursor
					.getColumnIndex(Contacts.LOOKUP_KEY));

			PIMItem pimItem = new PIMItemContacts(contactId, false);

			mList.add(pimItem);
		}
		listCursor.close();
		listCursor = null;

		mListIterator = 0;

		return MA_PIM_ERR_NONE;
	}
}

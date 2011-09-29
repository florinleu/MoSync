package com.mosync.pim;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;

import android.content.ContentResolver;
import android.database.Cursor;
import android.provider.ContactsContract.Contacts;

import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_LIST_UNAVAILABLE;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_NONE;

public class PIMListContacts extends PIMList {

	PIMListContacts() {
	}

	/**
	 * Read the list
	 */
	int read(ContentResolver cr) {
		DebugPrint("PIMList.read(" + cr + ")");
		// try to query for contacts
		Cursor cur;
		try {
			cur = cr.query(Contacts.CONTENT_URI, new String[] { Contacts._ID },
					null, null, null);
		} catch (Exception e) {
			return throwError(MA_PIM_ERR_LIST_UNAVAILABLE,
					PIMError.PANIC_LIST_UNAVAILABLE,
					PIMError.sStrListUnavailable);
		}

		if (cur == null) {
			return throwError(MA_PIM_ERR_LIST_UNAVAILABLE,
					PIMError.PANIC_LIST_UNAVAILABLE,
					PIMError.sStrListUnavailable);
		}

		// read each item
		while (cur.moveToNext()) {
			String contactId = cur.getString(cur.getColumnIndex(Contacts._ID));

			PIMItem pimItem = new PIMItem(false);
			pimItem.read(cr, contactId);

			mList.add(pimItem);
		}

		mListIterator = 0;

		return MA_PIM_ERR_NONE;
	}
}

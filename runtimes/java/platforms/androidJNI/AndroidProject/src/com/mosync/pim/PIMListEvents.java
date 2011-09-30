package com.mosync.pim;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;

import android.content.ContentResolver;
import android.database.Cursor;
import android.provider.ContactsContract.Contacts;

import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_LIST_UNAVAILABLE;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_NONE;

public class PIMListEvents extends PIMList {

	PIMListEvents() {
	}

	/**
	 * Read the list
	 */
	int read(Cursor cur, int index) {
		DebugPrint("PIMListEvents.read(" + cur + ", " + index + ")");
		// try to query for contacts
		if (cur == null) {
			return throwError(MA_PIM_ERR_LIST_UNAVAILABLE,
					PIMError.PANIC_LIST_UNAVAILABLE,
					PIMError.sStrListUnavailable);
		}

		cur.moveToPosition(index);

		// read each item
		int idColumn = cur.getColumnIndex("_id");
		String calId = cur.getString(idColumn);

		PIMItem pimItem = new PIMItemEvents(false);
		// pimItem.read(cur, contactId);

		mList.add(pimItem);

		mListIterator = 0;

		return MA_PIM_ERR_NONE;

		// int nameColumn = managedCursor.getColumnIndex("displayName");
		// int idColumn = managedCursor.getColumnIndex("_id");
		// do {
		// String calName = managedCursor.getString(nameColumn);
		// String calId = managedCursor.getString(idColumn);
		// // Log.i(DEBUG_TAG, "Found Calendar '" + calName + "' (ID=" +
		// // calId + ")");
		// // tv.setText("Found Calendar '" + calName + "' (ID=" + calId +
		// // ")");
		// if (calName != null) {// && calName.contains("Test")) {
		// // result = Integer.parseInt(calId);
		// }
		// } while (managedCursor.moveToNext());
		// } else {
		// // Log.i(DEBUG_TAG, "No Calendars");
		// // tv.setText("No Calendars.");
		// }
	}
}

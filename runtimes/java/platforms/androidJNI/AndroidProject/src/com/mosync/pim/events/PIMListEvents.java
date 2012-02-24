package com.mosync.pim.events;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;

import android.content.ContentResolver;
import android.database.Cursor;
import android.provider.ContactsContract.Contacts;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_LIST_UNAVAILABLE;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_NONE;

import com.mosync.pim.*;
import com.mosync.pim.contacts.PIMItemContacts;

public class PIMListEvents extends PIMList {

	protected PIMItem createItem() {
		PIMItemEvents p = new PIMItemEvents(true);
		mList.add(p);
		return p;
	}

	/**
	 * Read the list
	 */
	public int read() {
		return MA_PIM_ERR_NONE;
	}

	/**
	 * Read the list
	 */
	public int read(Cursor cur, int index) {
		DebugPrint("PIMListEvents.read(" + cur + ", " + index + ")");
		// try to query for contacts
		if (cur == null) {
			return PIMUtil.throwError(MA_PIM_ERR_LIST_UNAVAILABLE,
					PIMError.PANIC_LIST_UNAVAILABLE,
					PIMError.sStrListUnavailable);
		}

		cur.moveToPosition(index);

		// read each item
		int idColumn = cur.getColumnIndex("_id");
		String calId = cur.getString(idColumn);

		PIMItemEvents pimItem = new PIMItemEvents(false);
		pimItem.read(cur, calId);

		mList.add(pimItem);

		mListIterator = 0;

		return MA_PIM_ERR_NONE;
	}
}

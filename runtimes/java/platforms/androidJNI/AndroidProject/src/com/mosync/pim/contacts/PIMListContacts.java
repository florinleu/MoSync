package com.mosync.pim.contacts;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;

import android.content.ContentResolver;
import android.database.Cursor;
import android.provider.ContactsContract.Contacts;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_LIST_UNAVAILABLE;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_NONE;

import com.mosync.pim.*;

public class PIMListContacts extends PIMList {

	protected PIMItem createItem() {
		PIMItemContacts p = new PIMItemContacts(true);
		mList.add(p);
		return p;
	}

//	/**
//	 * Read the list
//	 */
//	public int read(ContentResolver cr) {
//		DebugPrint("PIMListContacts.read(" + cr + ")");
//		// try to query for contacts
//		Cursor cur;
//		try {
//			cur = cr.query(Contacts.CONTENT_URI, new String[] { Contacts._ID },
//					null, null, null);
//		} catch (Exception e) {
//			return PIMUtil.throwError(MA_PIM_ERR_LIST_UNAVAILABLE,
//					PIMError.PANIC_LIST_UNAVAILABLE,
//					PIMError.sStrListUnavailable);
//		}
//
//		if (cur == null) {
//			return PIMUtil.throwError(MA_PIM_ERR_LIST_UNAVAILABLE,
//					PIMError.PANIC_LIST_UNAVAILABLE,
//					PIMError.sStrListUnavailable);
//		}
//
//		// read each item
//		while (cur.moveToNext()) {
//			String contactId = cur.getString(cur.getColumnIndex(Contacts._ID));
//
//			PIMItemContacts pimItem = new PIMItemContacts(false);
//			pimItem.read(cr, contactId);
//
//			mList.add(pimItem);
//		}
//
//		mListIterator = 0;
//
//		return MA_PIM_ERR_NONE;
//	}
}

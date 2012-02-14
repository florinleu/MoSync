package com.mosync.pim;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;

import java.util.ArrayList;

import com.mosync.internal.android.MoSyncError;

import android.content.ContentResolver;
import android.database.Cursor;
import android.provider.ContactsContract.Contacts;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_NONE;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_LIST_UNAVAILABLE;

import com.mosync.pim.contacts.PIMItemContacts;


public abstract class PIMList {

	protected ArrayList<PIMItem> mList;
	protected int mListIterator;

	protected PIMList() {
		mList = new ArrayList<PIMItem>();
		mListIterator = -1;
	}

	/**
	 * @param errorCode
	 *            The error code returned by the syscall.
	 * @param panicCode
	 *            The panic code for this error.
	 * @param panicText
	 *            The panic text for this error.
	 * @return
	 */
	public int throwError(int errorCode, int panicCode, String panicText) {
		return MoSyncError.getSingletonObject().error(errorCode, panicCode,
				panicText);
	}

	Cursor listCursor = null;

	/**
	 * Read the list
	 */
	public int read(ContentResolver cr) {
		DebugPrint("PIMList.read(" + cr + ")");
		// try to query for contacts
		try {
			listCursor = cr.query(Contacts.CONTENT_URI,
					new String[] { Contacts._ID },
					null, null, null);
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

		// read each item
		for (int i = 0; i < listCursor.getCount(); i++) {
			// String contactId = listCursor.getString(listCursor
			// .getColumnIndex(Contacts._ID));

			PIMItem pimItem = new PIMItemContacts(false);
			// pimItem.read(cr, contactId);

			mList.add(pimItem);
		}

		// listCursor.close();
		// listCursor = null;

		mListIterator = 0;

		return MA_PIM_ERR_NONE;
	}

	/**
	 * Checks if we reached the end of the list.
	 */
	boolean hasNext() {
		return ((mList.size() > 0) && (mListIterator < mList.size()));
	}

	/**
	 * @return The next element in the list.
	 */
	PIMItem next(ContentResolver cr) {
		DebugPrint("@RUNTIME PIMList.next(" + cr + ")");
		PIMItem pimItem = mList.get(mListIterator);
		// read each item
		if (listCursor.moveToNext()) {
			String contactId = listCursor.getString(listCursor
					.getColumnIndex(Contacts._ID));

			if (pimItem instanceof PIMItemContacts)
			{
				((PIMItemContacts)pimItem).read(cr, contactId);
			}

			mList.set(mListIterator, pimItem);
		}
		mListIterator++;
		return pimItem;
	}

	/**
	 * @param field
	 * @return The data type of the field.
	 */
	int getFieldDataType(int field) {
		DebugPrint("PIMList.getFieldDataType(" + field + ")");
		return mList.get(0).getFieldDataType(field);
	}

	protected abstract PIMItem createItem();

	int removeItem(PIMItem item) {
		int index = -1;
		for (int i = 0; i < mList.size(); i++) {
			if (mList.get(i) == item) {
				index = i;
				break;
			}
		}
		if (index == mListIterator) {
			mListIterator--;
		}
		if (index != -1) {
			mList.remove(index);
		}
		return MA_PIM_ERR_NONE;
	}

	/**
	 * Closes the list.
	 */
	void close(ContentResolver cr) {
		DebugPrint("PIMList.close(" + cr + ")");
		try {
			mListIterator = 0;
			while (hasNext()) {
				next(cr).close(cr);
			}
			listCursor.close();
			listCursor = null;
		} catch (Exception e) {
		}
	}
}

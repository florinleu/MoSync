package com.mosync.pim;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;

import java.util.ArrayList;
import java.util.Iterator;

import android.content.ContentResolver;

public class PIMItemEvents extends PIMItem {

	public PIMItemEvents(boolean isNew) {
		setState(State.NONE);
		if (isNew) {
			setState(State.ADDED);
		}
		// mPIMFields = new ArrayList<PIMField>();
		// mAddress = new PIMFieldAddress();
		// mPIMFields.add(mAddress);
	}

	/**
	 * Read the item with contactId.
	 * @param cr
	 * @param contactId
	 */
	void read(Cursor cur, String calendarId) {
		DebugPrint("PIMItem.read(" + cr + ", " + contactId + ")");

		Iterator<PIMField> fieldsIt = mPIMFields.iterator();

		while (fieldsIt.hasNext()) {
			fieldsIt.next().read(cr, contactId);
		}
	}
}

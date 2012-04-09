package com.mosync.pim.events;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;

import java.util.ArrayList;
import java.util.Iterator;

import android.content.ContentResolver;
import android.database.Cursor;
import android.net.Uri;

import com.mosync.pim.*;
import com.mosync.pim.contacts.PIMFieldAddress;
import com.mosync.pim.contacts.PIMFieldContacts;

public class PIMItemEvents extends PIMItem {

	PIMFieldTitle mTitle;

	PIMItemEvents(boolean isNew) {
		super(isNew);
		mTitle = new PIMFieldTitle();
		mPIMFields.add(mTitle);
	}

	/**
	 * Read the item with contactId.
	 * @param cr
	 * @param contactId
	 */
	void read(Cursor cur, String calendarId) {
		DebugPrint("PIMItem.read(" + cur + ", " + calendarId + ")");

		Iterator<PIMField> fieldsIt = mPIMFields.iterator();

		while (fieldsIt.hasNext()) {
			fieldsIt.next().read(cur, calendarId);
		}
	}

	protected String getID() {
		return null;
	}

	/**
	 * Closes the item
	 */
	protected void close() {

	}
}

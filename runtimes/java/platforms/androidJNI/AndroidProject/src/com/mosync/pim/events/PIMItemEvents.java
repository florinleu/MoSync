package com.mosync.pim.events;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;

import java.util.ArrayList;
import java.util.Iterator;

import android.content.ContentResolver;
import android.database.Cursor;
import android.net.Uri;

import com.mosync.pim.*;
import com.mosync.pim.contacts.PIMFieldContact;

public class PIMItemEvents extends PIMItem {

	PIMItemEvents(boolean isNew) {
		super(isNew);
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
}

package com.mosync.pim.contacts;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;
import android.content.ContentResolver;
import android.database.Cursor;
import android.provider.ContactsContract.Data;

import com.mosync.pim.*;

public abstract class PIMFieldContacts extends PIMField {

	/**
	 * Read field
	 * @param cr
	 * @param contactId
	 */
	public void read(ContentResolver cr, String contactId) {
		DebugPrint("PIMField.read(" + cr + ", " + contactId + ")");
		Cursor cursor = cr.query(Data.CONTENT_URI, mNames, Data.CONTACT_ID
				+ "=?" + " AND " + Data.MIMETYPE + "=?",
				new String[] { String.valueOf(contactId), mStrType }, null);

		while (cursor.moveToNext()) {
			String[] val = new String[mNames.length];
			for (int i = 0; i < mNames.length; i++) {
				val[i] = new String("");
				if (!mNames[i].equals(DUMMY)) {
					int index = cursor.getColumnIndex(mNames[i]);
					if (index >= 0) {
						val[i] = cursor.getString(index);
					}
				}
			}
			mValues.add(val);
			mStates.add(State.NONE);
		}
		preProcessData();

		print();
		DebugPrint("MAX SIZE = " + MAX_SIZE);
	}
}

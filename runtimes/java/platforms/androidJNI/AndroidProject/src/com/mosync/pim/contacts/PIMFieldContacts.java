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
	public void read(String contactId) {
		if (mValues.size() > 0) {
			return;
		}
		DebugPrint("PIMFieldContacts.read(" + contactId + ")");
		Cursor cursor = getContentResolver().query(Data.CONTENT_URI, mNames,
				Data.LOOKUP_KEY + "=?" + " AND " + Data.MIMETYPE + "=?",
				new String[] { contactId, mStrType }, null);

		while (cursor.moveToNext()) {
			String[] val = new String[mNames.length];
			for (int i = 0; i < mNames.length; i++) {
				val[i] = new String("");
				if (!mNames[i].equals(DUMMY)) {
					int index = cursor.getColumnIndex(mNames[i]);
					if (index >= 0) {
						String s = cursor.getString(index);
						if (s != null) {
							val[i] = s;
						}
					}
				}
			}
			mValues.add(val);
			mStates.add(State.NONE);
		}
		preProcessData();

		print();
	}
}

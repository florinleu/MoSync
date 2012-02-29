package com.mosync.pim.contacts;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_NONE;

import static com.mosync.internal.generated.IX_PIM.MA_PIM_FIELD_CONTACT_REVISION;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_TYPE_DATE;

public class PIMFieldRevision extends PIMFieldContacts {

	/**
	 * Constructor
	 */
	public PIMFieldRevision() {
		mType = MA_PIM_FIELD_CONTACT_REVISION;
		mDataType = MA_PIM_TYPE_DATE;
	}

	protected void createMaps() {

	}

	public void read(String contactId) {
		DebugPrint("PIMFieldRevision.read(" + contactId + ")");
		print();
	}

	protected int checkForPreferredAttribute(int index) {
		return 0;
	}

	protected int getAndroidAttribute(int index) {
		return 0;
	}

	protected int setAttribute(int index, int attribute) {
		return MA_PIM_ERR_NONE;
	}

	protected char[] getLabel(int index) {
		return null;
	}

	protected void setLabel(int index, String label) {
	}

	protected boolean hasCustomLabel(int index) {
		return false;
	}

	protected char[] getData(int index) {
		return null;
	}

	protected void setData(int index, char[] buffer) {
	}

	public boolean isSupported() {
		return false;
	}

	/**
	 * Print field values.
	 */
	protected void print() {
		DebugPrint("**********REVISION*********");
		DebugPrint("Not supported");
		DebugPrint("***************************");
	}
}

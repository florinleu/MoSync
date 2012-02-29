package com.mosync.pim.contacts;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_NONE;

import static com.mosync.internal.generated.IX_PIM.MA_PIM_FIELD_CONTACT_UID;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_TYPE_STRING;

import com.mosync.pim.*;

public class PIMFieldUID extends PIMFieldContacts {

	/**
	 * Constructor
	 */
	public PIMFieldUID() {
		MAX_SIZE = 1;

		mType = MA_PIM_FIELD_CONTACT_UID;
		mDataType = MA_PIM_TYPE_STRING;

		mPermission = Permission.READ_ONLY;
	}

	protected void createMaps() {
	}

	/**
	 * Read address field.
	 */
	public void read(String contactId) {
		DebugPrint("PIMFieldUID.read(" + contactId + ")");
		mValues.add(new String[] { contactId });
		mStates.add(State.NONE);

		print();
	}

	protected int getAttributes(int index) {
		return 0;
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

	/**
	 * Gets the field's custom label.
	 * @param index
	 * @return
	 */
	protected char[] getLabel(int index) {
		return null;
	}

	/**
	 * Gets the field's custom label.
	 * @param index
	 * @return
	 */
	protected void setLabel(int index, String label) {
	}

	/**
	 * Checks to see if the given field has a custom label.
	 * @param index
	 */
	protected boolean hasCustomLabel(int index) {
		return false;
	}

	protected char[] getData(int index) {
		String val = getSpecificData(index);
		char[] buffer = new char[getDataSize(val)];
		PIMUtil.writeString(val, buffer);
		return buffer;
	}

	public String getSpecificData(int index) {
		String[] val = mValues.get(index);
		return val[0];
	}

	String getValue() {
		return getSpecificData(0);
	}

	int getDataSize(String val) {
		return val.length() + 1;
	}

	protected void setData(int index, char[] buffer) {
		String val = PIMUtil.readString(buffer);
		setSpecificData(val, index);
	}

	void setSpecificData(String data, int index) {
		mValues.set(index, new String[] { data });
	}

	/**
	 * Print field values.
	 */
	protected void print() {
		String[] val = null;
		DebugPrint("*************UID***********");
		if ((mValues == null) || (mValues.size() == 0)
				|| ((val = mValues.get(0)) == null)) {
			DebugPrint("NOT AVAILABLE");
		} else {
			DebugPrint("UID: " + val[0]);
		}
		DebugPrint("***************************");
	}
}

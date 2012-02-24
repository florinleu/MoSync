package com.mosync.pim.contacts;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;

import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_EMAIL_HOME;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_EMAIL_WORK;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_EMAIL_MOBILE;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_EMAIL_OTHER;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_EMAIL_CUSTOM;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTRPREFERRED;

import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_NONE;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_ATTRIBUTE_COMBO_UNSUPPORTED;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_FIELD_CONTACT_EMAIL;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_TYPE_STRING;

import android.provider.ContactsContract.CommonDataKinds.Email;

import com.mosync.pim.*;

public class PIMFieldEmail extends PIMFieldContacts {

	/**
	 * Constructor
	 */
	public PIMFieldEmail() {
		mType = MA_PIM_FIELD_CONTACT_EMAIL;
		mStrType = Email.CONTENT_ITEM_TYPE;
		mDataType = MA_PIM_TYPE_STRING;

		mNames = new String[] { Email.DATA, Email.TYPE, Email.LABEL,
				Email.IS_PRIMARY };
	}

	protected void createMaps() {
		// attributes
		mAttributes.put(MA_PIM_ATTR_EMAIL_HOME, Email.TYPE_HOME);
		mAttributes.put(MA_PIM_ATTR_EMAIL_WORK, Email.TYPE_WORK);
		mAttributes.put(MA_PIM_ATTR_EMAIL_MOBILE, Email.TYPE_MOBILE);
		mAttributes.put(MA_PIM_ATTR_EMAIL_OTHER, Email.TYPE_OTHER);
		mAttributes.put(MA_PIM_ATTR_EMAIL_CUSTOM, Email.TYPE_CUSTOM);
	}

	protected int checkForPreferredAttribute(int index) {
		if (Integer.parseInt(getColumnValue(index, Email.IS_PRIMARY)) != 0)
			return MA_PIM_ATTRPREFERRED;
		return 0;
	}

	/**
	 * Gets the field attribute.
	 */
	protected int getAndroidAttribute(int index) {
		String attribute = null;
		if ((attribute = getColumnValue(index, Email.TYPE)) == null) {
			return -1;
		}
		return Integer.parseInt(attribute);
	}

	/**
	 * Gets the field's custom label.
	 * @param index
	 * @return
	 */
	protected char[] getLabel(int index) {
		return getColumnValue(index, Email.LABEL).toCharArray();
	}

	/**
	 * Gets the field's custom label.
	 * @param index
	 * @return
	 */
	protected void setLabel(int index, String label) {
		setColumnValue(index, Email.LABEL, label);
	}

	/**
	 * Checks to see if the given field has a custom label.
	 * @param index
	 */
	protected boolean hasCustomLabel(int index) {
		return ((Integer.parseInt(getColumnValue(index, Email.TYPE)) == Email.TYPE_CUSTOM) ? true
				: false);
	}

	protected char[] getData(int index) {
		String val = getSpecificData(index);
		if (val == null) {
			return null;
		}
		char[] buffer = new char[getDataSize(val)];
		PIMUtil.writeString(val, buffer);
		return buffer;
	}

	String getSpecificData(int index) {
		String[] val = mValues.get(index);
		return val[0];
	}

	int getDataSize(String val) {
		return val.length() + 1;
	}

	protected void setData(int index, char[] buffer) {
		String val = PIMUtil.readString(buffer);
		setSpecificData(val, index);
	}

	void setSpecificData(String data, int index) {
		String[] val = mValues.get(index);
		val[0] = data;
		mValues.set(index, val);
	}

	protected int setAttribute(int index, int attribute) {
		if ((attribute | MA_PIM_ATTRPREFERRED) != 0) {
			setColumnValue(index, Email.IS_PRIMARY, Integer.toString(1));
		}
		attribute &= 0xFFFF;

		int ret = 0;
		if (mAttributes.containsKey(attribute)) {
			ret = mAttributes.get(attribute);
		} else {
			return MA_PIM_ERR_ATTRIBUTE_COMBO_UNSUPPORTED;
		}

		setColumnValue(index, Email.TYPE, Integer.toString(ret));

		return MA_PIM_ERR_NONE;
	}

	/**
	 * Print field values.
	 */
	protected void print() {
		DebugPrint("***********EMAIL***********");
		DebugPrint("COUNT = " + mValues.size());
		for (int i = 0; i < mValues.size(); i++) {
			String[] val = mValues.get(i);
			DebugPrint("###Email " + i);
			DebugPrint(mNames[0] + ": " + val[0]);
		}
		DebugPrint("***************************");
	}
}

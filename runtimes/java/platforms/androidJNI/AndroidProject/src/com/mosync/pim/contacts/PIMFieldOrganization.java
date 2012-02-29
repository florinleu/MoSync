package com.mosync.pim.contacts;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;

import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_ORG_WORK;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_ORG_OTHER;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_ORG_CUSTOM;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTRPREFERRED;

import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_NONE;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_ATTRIBUTE_COMBO_UNSUPPORTED;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_FIELD_CONTACT_ORG;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_TYPE_STRING;

import android.provider.ContactsContract.CommonDataKinds.Organization;
import com.mosync.pim.*;

public class PIMFieldOrganization extends PIMFieldContacts {

	/**
	 * Constructor
	 */
	public PIMFieldOrganization() {
		mType = MA_PIM_FIELD_CONTACT_ORG;
		mStrType = Organization.CONTENT_ITEM_TYPE;
		mDataType = MA_PIM_TYPE_STRING;

		mNames = new String[] { Organization.COMPANY, Organization.TYPE,
				Organization.LABEL, Organization.IS_PRIMARY };
	}

	protected void createMaps() {
		// attributes
		mAttributes.put(MA_PIM_ATTR_ORG_WORK, Organization.TYPE_WORK);
		mAttributes.put(MA_PIM_ATTR_ORG_OTHER, Organization.TYPE_OTHER);
		mAttributes.put(MA_PIM_ATTR_ORG_CUSTOM, Organization.TYPE_CUSTOM);
	}

	protected int checkForPreferredAttribute(int index) {
		try {
			if (Integer
					.parseInt(getColumnValue(index, Organization.IS_PRIMARY)) != 0)
				return MA_PIM_ATTRPREFERRED;
		} catch (NumberFormatException e) {
		}
		return 0;
	}

	/**
	 * Gets the field attribute.
	 */
	protected int getAndroidAttribute(int index) {
		String attribute = null;
		if ((attribute = getColumnValue(index, Organization.TYPE)) == null) {
			return -1;
		}
		try {
			return Integer.parseInt(attribute);
		} catch (NumberFormatException e) {
			return Organization.TYPE_OTHER;
		}
	}

	/**
	 * Gets the field's custom label.
	 * @param index
	 * @return
	 */
	protected char[] getLabel(int index) {
		return getColumnValue(index, Organization.LABEL).toCharArray();
	}

	/**
	 * Gets the field's custom label.
	 * @param index
	 * @return
	 */
	protected void setLabel(int index, String label) {
		setColumnValue(index, Organization.LABEL, label);
	}

	/**
	 * Checks to see if the given field has a custom label.
	 * @param index
	 */
	protected boolean hasCustomLabel(int index) {
		try {
			return ((Integer.parseInt(getColumnValue(index, Organization.TYPE)) == Organization.TYPE_CUSTOM) ? true
					: false);
		} catch (NumberFormatException e) {
			return false;
		}
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
			setColumnValue(index, Organization.IS_PRIMARY, Integer.toString(1));
		}
		attribute &= 0xFFFF;

		int ret = 0;
		if (mAttributes.containsKey(attribute)) {
			ret = mAttributes.get(attribute);
		} else {
			return MA_PIM_ERR_ATTRIBUTE_COMBO_UNSUPPORTED;
		}

		setColumnValue(index, Organization.TYPE, Integer.toString(ret));

		return MA_PIM_ERR_NONE;
	}

	/**
	 * Print field values.
	 */
	protected void print() {
		DebugPrint("*******ORGANIZATIONS*******");
		DebugPrint("COUNT = " + mValues.size());
		for (int i = 0; i < mValues.size(); i++) {
			String[] val = mValues.get(i);
			DebugPrint("###Organization " + i);
			DebugPrint(mNames[0] + ": " + val[0]);
		}
		DebugPrint("***************************");
	}
}

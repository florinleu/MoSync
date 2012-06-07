package com.mosync.pim.contacts;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;

import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_ORG_INFO_WORK;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_ORG_INFO_OTHER;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_ORG_INFO_CUSTOM;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTRPREFERRED;

import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_NONE;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_ATTRIBUTE_COMBO_UNSUPPORTED;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_FIELD_CONTACT_ORG_INFO;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_TYPE_STRING_ARRAY;

import android.provider.ContactsContract.CommonDataKinds.Organization;
import android.provider.ContactsContract.CommonDataKinds.StructuredPostal;

import com.mosync.pim.*;

public class PIMFieldOrganizationInfo extends PIMFieldContacts {

	/**
	 * Constructor
	 */
	public PIMFieldOrganizationInfo() {
		mType = MA_PIM_FIELD_CONTACT_ORG_INFO;
		mStrType = Organization.CONTENT_ITEM_TYPE;
		mDataType = MA_PIM_TYPE_STRING_ARRAY;

		mNames = new String[] { Organization._ID, Organization.DEPARTMENT,
				Organization.JOB_DESCRIPTION, Organization.SYMBOL,
				Organization.PHONETIC_NAME, Organization.OFFICE_LOCATION,
				Organization.TYPE, Organization.LABEL, Organization.IS_PRIMARY };
	}

	protected void createMaps() {
		// attributes
		mAttributes.put(MA_PIM_ATTR_ORG_INFO_WORK, Organization.TYPE_WORK);
		mAttributes.put(MA_PIM_ATTR_ORG_INFO_OTHER, Organization.TYPE_OTHER);
		mAttributes.put(MA_PIM_ATTR_ORG_INFO_CUSTOM, Organization.TYPE_CUSTOM);
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
		String[] val = getSpecificData(index);
		char[] buffer = new char[getDataSize(val)];
		PIMUtil.writeStringArray(val, buffer);
		return buffer;
	}

	String[] getSpecificData(int index) {
		String[] val = mValues.get(index);
		String[] ret = new String[val.length - 4];
		for (int i = 0; i < val.length - 4; i++) {
			ret[i] = val[i + 1];
		}
		return ret;
	}

	int getDataSize(String[] val) {
		int size = 4;
		for (int i = 0; i < val.length; i++) {
			if (val[i] != null) {
				size += val[i].length();
			}
			size += 1;
		}
		return size;
	}

	protected void setData(int index, char[] buffer) {
		String[] val = PIMUtil.readStringArray(buffer);
		setSpecificData(val, index);
	}

	void setSpecificData(String[] data, int index) {
		String[] val = mValues.get(index);
		for (int i = 0; i < data.length; i++) {
			val[i + 1] = data[i];
		}
		mValues.set(index, val);
	}

	protected int setAttribute(int index, int attribute) {
		setColumnValue(index, Organization.IS_PRIMARY,
				Integer.toString(((attribute & MA_PIM_ATTRPREFERRED) != 0) ? 1
						: 0));
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
		DebugPrint("*****ORGANIZATION INFO*****");
		DebugPrint("COUNT = " + mValues.size());
		for (int i = 0; i < mValues.size(); i++) {
			String[] val = mValues.get(i);
			DebugPrint("###Organization info " + i);
			for (int j = 0; j < val.length; j++) {
				DebugPrint(mNames[j] + ": " + val[j]);
			}
		}
		DebugPrint("***************************");
	}
}

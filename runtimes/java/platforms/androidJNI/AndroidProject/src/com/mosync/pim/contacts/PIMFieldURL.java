package com.mosync.pim.contacts;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;

import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_WEBSITE_HOMEPAGE;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_WEBSITE_BLOG;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_WEBSITE_PROFILE;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_WEBSITE_HOME;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_WEBSITE_WORK;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_WEBSITE_FTP;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_WEBSITE_OTHER;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_WEBSITE_CUSTOM;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTRPREFERRED;

import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_NONE;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_ATTRIBUTE_COMBO_UNSUPPORTED;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_FIELD_CONTACT_URL;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_TYPE_STRING;

import android.provider.ContactsContract.CommonDataKinds.StructuredPostal;
import android.provider.ContactsContract.CommonDataKinds.Website;

import com.mosync.pim.*;

public class PIMFieldURL extends PIMFieldContacts {

	/**
	 * Constructor
	 */
	public PIMFieldURL() {
		mType = MA_PIM_FIELD_CONTACT_URL;
		mStrType = Website.CONTENT_ITEM_TYPE;
		mDataType = MA_PIM_TYPE_STRING;

		mNames = new String[] { Website._ID, Website.URL, Website.TYPE,
				Website.LABEL, Website.IS_PRIMARY };
	}

	protected void createMaps() {
		// attributes
		mAttributes.put(MA_PIM_ATTR_WEBSITE_HOMEPAGE, Website.TYPE_HOMEPAGE);
		mAttributes.put(MA_PIM_ATTR_WEBSITE_BLOG, Website.TYPE_BLOG);
		mAttributes.put(MA_PIM_ATTR_WEBSITE_PROFILE, Website.TYPE_PROFILE);
		mAttributes.put(MA_PIM_ATTR_WEBSITE_HOME, Website.TYPE_HOME);
		mAttributes.put(MA_PIM_ATTR_WEBSITE_WORK, Website.TYPE_WORK);
		mAttributes.put(MA_PIM_ATTR_WEBSITE_FTP, Website.TYPE_FTP);
		mAttributes.put(MA_PIM_ATTR_WEBSITE_OTHER, Website.TYPE_OTHER);
		mAttributes.put(MA_PIM_ATTR_WEBSITE_CUSTOM, Website.TYPE_CUSTOM);
	}

	protected int checkForPreferredAttribute(int index) {
		try {
			if (Integer.parseInt(getColumnValue(index, Website.IS_PRIMARY)) != 0)
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
		if ((attribute = getColumnValue(index, Website.TYPE)) == null) {
			return -1;
		}
		try {
			return Integer.parseInt(attribute);
		} catch (NumberFormatException e) {
			return Website.TYPE_OTHER;
		}
	}

	/**
	 * Gets the field's custom label.
	 * @param index
	 * @return
	 */
	protected char[] getLabel(int index) {
		return getColumnValue(index, Website.LABEL).toCharArray();
	}

	/**
	 * Gets the field's custom label.
	 * @param index
	 * @return
	 */
	protected void setLabel(int index, String label) {
		setColumnValue(index, Website.LABEL, label);
	}

	/**
	 * Checks to see if the given field has a custom label.
	 * @param index
	 */
	protected boolean hasCustomLabel(int index) {
		try {
			return ((Integer.parseInt(getColumnValue(index, Website.TYPE)) == Website.TYPE_CUSTOM) ? true
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
		return val[1];
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
		val[1] = data;
		mValues.set(index, val);
	}

	protected int setAttribute(int index, int attribute) {
		if ((attribute | MA_PIM_ATTRPREFERRED) != 0) {
			setColumnValue(index, Website.IS_PRIMARY, Integer.toString(1));
		}
		attribute &= 0xFFFF;

		int ret = 0;
		if (mAttributes.containsKey(attribute)) {
			ret = mAttributes.get(attribute);
		} else {
			return MA_PIM_ERR_ATTRIBUTE_COMBO_UNSUPPORTED;
		}

		setColumnValue(index, Website.TYPE, Integer.toString(ret));

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
			DebugPrint(mNames[1] + ": " + val[1]);
		}
		DebugPrint("***************************");
	}
}

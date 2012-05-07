package com.mosync.pim.contacts;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;

import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_RELATION_MOTHER;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_RELATION_FATHER;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_RELATION_PARENT;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_RELATION_SISTER;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_RELATION_BROTHER;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_RELATION_CHILD;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_RELATION_FRIEND;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_RELATION_SPOUSE;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_RELATION_PARTNER;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_RELATION_MANAGER;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_RELATION_ASSISTANT;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_RELATION_DOMESTIC_PARTNER;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_RELATION_REFERRED_BY;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_RELATION_RELATIVE;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTR_RELATION_CUSTOM;

import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTRPREFERRED;

import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_NONE;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_ATTRIBUTE_COMBO_UNSUPPORTED;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_FIELD_CONTACT_RELATION;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_TYPE_STRING;

import android.provider.ContactsContract.CommonDataKinds.Relation;
import android.provider.ContactsContract.CommonDataKinds.StructuredPostal;

import com.mosync.pim.*;

public class PIMFieldRelation extends PIMFieldContacts {

	/**
	 * Constructor
	 */
	public PIMFieldRelation() {
		mType = MA_PIM_FIELD_CONTACT_RELATION;
		mStrType = Relation.CONTENT_ITEM_TYPE;
		mDataType = MA_PIM_TYPE_STRING;

		mNames = new String[] { Relation.NAME, Relation.TYPE, Relation.LABEL,
				Relation.IS_PRIMARY };
	}

	protected void createMaps() {
		// attributes
		mAttributes.put(MA_PIM_ATTR_RELATION_MOTHER, Relation.TYPE_MOTHER);
		mAttributes.put(MA_PIM_ATTR_RELATION_FATHER, Relation.TYPE_FATHER);
		mAttributes.put(MA_PIM_ATTR_RELATION_PARENT, Relation.TYPE_PARENT);
		mAttributes.put(MA_PIM_ATTR_RELATION_SISTER, Relation.TYPE_SISTER);
		mAttributes.put(MA_PIM_ATTR_RELATION_BROTHER, Relation.TYPE_BROTHER);
		mAttributes.put(MA_PIM_ATTR_RELATION_CHILD, Relation.TYPE_CHILD);
		mAttributes.put(MA_PIM_ATTR_RELATION_FRIEND, Relation.TYPE_FRIEND);
		mAttributes.put(MA_PIM_ATTR_RELATION_SPOUSE, Relation.TYPE_SPOUSE);
		mAttributes.put(MA_PIM_ATTR_RELATION_PARTNER, Relation.TYPE_PARTNER);
		mAttributes.put(MA_PIM_ATTR_RELATION_MANAGER, Relation.TYPE_MANAGER);
		mAttributes
				.put(MA_PIM_ATTR_RELATION_ASSISTANT, Relation.TYPE_ASSISTANT);
		mAttributes.put(MA_PIM_ATTR_RELATION_DOMESTIC_PARTNER,
				Relation.TYPE_DOMESTIC_PARTNER);
		mAttributes.put(MA_PIM_ATTR_RELATION_REFERRED_BY,
				Relation.TYPE_REFERRED_BY);
		mAttributes.put(MA_PIM_ATTR_RELATION_RELATIVE, Relation.TYPE_RELATIVE);
		mAttributes.put(MA_PIM_ATTR_RELATION_CUSTOM, Relation.TYPE_CUSTOM);
	}

	protected int checkForPreferredAttribute(int index) {
		try {
			if (Integer.parseInt(getColumnValue(index, Relation.IS_PRIMARY)) != 0)
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
		if ((attribute = getColumnValue(index, Relation.TYPE)) == null) {
			return -1;
		}
		try {
			return Integer.parseInt(attribute);
		} catch (NumberFormatException e) {
			return Relation.TYPE_CUSTOM;
		}
	}

	/**
	 * Gets the field's custom label.
	 * @param index
	 * @return
	 */
	protected char[] getLabel(int index) {
		return getColumnValue(index, Relation.LABEL).toCharArray();
	}

	/**
	 * Gets the field's custom label.
	 * @param index
	 * @return
	 */
	protected void setLabel(int index, String label) {
		setColumnValue(index, Relation.LABEL, label);
	}

	/**
	 * Checks to see if the given field has a custom label.
	 * @param index
	 */
	protected boolean hasCustomLabel(int index) {
		try {
			return ((Integer.parseInt(getColumnValue(index, Relation.TYPE)) == Relation.TYPE_CUSTOM) ? true
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
		setColumnValue(index, Relation.IS_PRIMARY,
				Integer.toString(((attribute & MA_PIM_ATTRPREFERRED) != 0) ? 1
						: 0));
		attribute &= 0xFFFF;

		int ret = 0;
		if (mAttributes.containsKey(attribute)) {
			ret = mAttributes.get(attribute);
		} else {
			return MA_PIM_ERR_ATTRIBUTE_COMBO_UNSUPPORTED;
		}

		setColumnValue(index, Relation.TYPE, Integer.toString(ret));

		return MA_PIM_ERR_NONE;
	}

	/**
	 * Print field values.
	 */
	protected void print() {
		DebugPrint("*********RELATION**********");
		DebugPrint("COUNT = " + mValues.size());
		for (int i = 0; i < mValues.size(); i++) {
			String[] val = mValues.get(i);
			DebugPrint("###Relation " + i);
			DebugPrint(mNames[0] + ": " + val[0]);
		}
		DebugPrint("***************************");
	}
}

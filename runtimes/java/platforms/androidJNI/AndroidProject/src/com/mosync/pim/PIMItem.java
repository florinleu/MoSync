package com.mosync.pim;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_FIELD_INVALID;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_FIELD_UNSUPPORTED;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_INDEX_INVALID;

import java.util.ArrayList;
import java.util.Iterator;

import android.content.ContentResolver;

public abstract class PIMItem {
	protected enum State {
		NONE, ADDED, UPDATED
	}

	protected State mState;

	protected ArrayList<PIMField> mPIMFields;

	/**
	 * Constructor
	 */
	protected PIMItem(boolean isNew) {
		DebugPrint("PIMItem(" + isNew + ")");
		setState(State.NONE);
		if (isNew) {
			setState(State.ADDED);
		}
		mPIMFields = new ArrayList<PIMField>();
	}

	// public abstract void read();

	/**
	 * @return The Content Resolver.
	 */
	public ContentResolver getContentResolver() {
		return PIMUtil.sContentResolver;
	}

	protected void setState(State state) {
		if ((mState != State.ADDED) && (state != State.NONE))
			mState = state;
	}

	/**
	 * Gets the number of fields in the item.
	 */
	int length() {
		DebugPrint("length()");

		int counter = 0;
		Iterator<PIMField> fieldsIt = mPIMFields.iterator();

		while (fieldsIt.hasNext()) {
			if (!fieldsIt.next().isEmpty())
				counter++;
		}

		return counter;
	}

	/**
	 * @param type
	 * @return The field with the given type.
	 */
	PIMField getField(int type) {
		Iterator<PIMField> i = mPIMFields.iterator();
		while (i.hasNext()) {
			PIMField p = i.next();
			if ((p != null) && (p.getType() == type)) {
				return p;
			}
		}
		return null;
	}

	/**
	 * @param index
	 * @return The type of the requested field.
	 */
	int getFieldType(int index) {
		DebugPrint("PIMItem.getFieldType(" + index + ")");
		if ((index < 0) || (index >= mPIMFields.size())) {
			return PIMUtil.throwError(MA_PIM_ERR_INDEX_INVALID,
					PIMError.PANIC_INDEX_INVALID, PIMError.sStrIndexInvalid);
		}

		return mPIMFields.get(index).getType();
	}

	/**
	 * Gets the length of a field.
	 * @param field
	 * @return The length of the given field.
	 */
	int getFieldLength(int field) {
		DebugPrint("PIMItem.getFieldLength(" + field + ")");
		PIMField pimField = getField(field);

		if (pimField == null) {
			return PIMUtil.throwError(MA_PIM_ERR_FIELD_INVALID,
					PIMError.PANIC_FIELD_INVALID, PIMError.sStrFieldInvalid);
		}
		if (!pimField.isSupported()) {
			return MA_PIM_ERR_FIELD_UNSUPPORTED;
		}

		pimField.read(getID());
		return pimField.length();
	}

	/**
	 * @param field
	 * @param index
	 * @return The attributes for the given field.
	 */
	int getFieldAttributes(int field, int index) {
		DebugPrint("getFieldAttributes(" + field + ", " + index + ")");
		PIMField pimField = getField(field);

		if (pimField == null) {
			return PIMUtil.throwError(MA_PIM_ERR_FIELD_INVALID,
					PIMError.PANIC_FIELD_INVALID, PIMError.sStrFieldInvalid);
		}
		if (!pimField.isSupported()) {
			return MA_PIM_ERR_FIELD_UNSUPPORTED;
		}

		return pimField.getAttributes(index);
	}

	/**
	 * Gets the custom label of the specified field.
	 * @param field
	 * @param index
	 * @param buffPointer
	 * @param buffSize
	 * @return
	 */
	int getFieldLabel(int field, int index, int buffPointer, int buffSize) {
		DebugPrint("getFieldLabel(" + field + ", " + index + ", " + buffPointer
				+ ", " + buffSize + ")");
		PIMField pimField = getField(field);

		if (pimField == null) {
			return PIMUtil.throwError(MA_PIM_ERR_FIELD_INVALID,
					PIMError.PANIC_FIELD_INVALID, PIMError.sStrFieldInvalid);
		}
		if (!pimField.isSupported()) {
			return MA_PIM_ERR_FIELD_UNSUPPORTED;
		}

		return pimField.getLabel(index, buffPointer, buffSize);
	}

	/**
	 * Sets the custom label of the specified field.
	 * @param field
	 * @param index
	 * @param buffPointer
	 * @param buffSize
	 * @return
	 */
	int setFieldLabel(int field, int index, int buffPointer, int buffSize) {
		DebugPrint("setFieldLabel(" + field + ", " + index + ", " + buffPointer
				+ ", " + buffSize + ")");
		PIMField pimField = getField(field);

		if (pimField == null) {
			return PIMUtil.throwError(MA_PIM_ERR_FIELD_INVALID,
					PIMError.PANIC_FIELD_INVALID, PIMError.sStrFieldInvalid);
		}
		if (!pimField.isSupported()) {
			return MA_PIM_ERR_FIELD_UNSUPPORTED;
		}

		setState(State.UPDATED);
		return pimField.setLabel(index, buffPointer, buffSize);
	}

	/**
	 * Gets the value of the specified field.
	 * @param field
	 * @param index
	 * @param buffPointer
	 * @param buffSize
	 * @return
	 */
	int getFieldValue(int field, int index, int buffPointer, int buffSize) {
		DebugPrint("PIMItem.getFieldValue(" + field + ", " + index + ", "
				+ buffPointer + ", " + buffSize + ")");

		PIMField pimField = getField(field);

		if (pimField == null) {
			return PIMUtil.throwError(MA_PIM_ERR_FIELD_INVALID,
					PIMError.PANIC_FIELD_INVALID, PIMError.sStrFieldInvalid);
		}
		if (!pimField.isSupported()) {
			return MA_PIM_ERR_FIELD_UNSUPPORTED;
		}

		pimField.read(getID());
		return pimField.getValue(index, buffPointer, buffSize);
	}

	/**
	 * Sets the value of the specified field.
	 * @param field
	 * @param index
	 * @param buffPointer
	 * @param buffSize
	 * @return
	 */
	int setFieldValue(int field, int index, int buffPointer, int buffSize,
			int attributes) {
		DebugPrint("PIMItem.setFieldValue(" + field + ", " + index + ", "
				+ buffPointer + ", " + buffSize + ", " + attributes + ")");
		PIMField pimField = getField(field);

		if (pimField == null) {
			return PIMUtil.throwError(MA_PIM_ERR_FIELD_INVALID,
					PIMError.PANIC_FIELD_INVALID, PIMError.sStrFieldInvalid);
		}
		if (!pimField.isSupported()) {
			return MA_PIM_ERR_FIELD_UNSUPPORTED;
		}

		setState(State.UPDATED);
		return pimField.setValue(index, buffPointer, buffSize, attributes);
	}

	/**
	 * Add the value to the specified field.
	 * @param field
	 * @param index
	 * @param buffPointer
	 * @param buffSize
	 * @return
	 */
	int addFieldValue(int field, int buffPointer, int buffSize, int attributes) {
		DebugPrint("addFieldValue(" + field + ", " + buffPointer + ", "
				+ buffSize + ", " + attributes + ")");
		PIMField pimField = getField(field);

		if (pimField == null) {
			return PIMUtil.throwError(MA_PIM_ERR_FIELD_INVALID,
					PIMError.PANIC_FIELD_INVALID, PIMError.sStrFieldInvalid);
		}
		if (!pimField.isSupported()) {
			return MA_PIM_ERR_FIELD_UNSUPPORTED;
		}

		return pimField.addValue(buffPointer, buffSize, attributes);
	}

	/**
	 * Removes the value of the specified field.
	 * @param field
	 * @param index
	 * @param buffPointer
	 * @param buffSize
	 * @return
	 */
	int removeFieldValue(int field, int index) {
		DebugPrint("getFieldValue(" + field + ", " + index + ")");
		PIMField pimField = getField(field);

		if (pimField == null) {
			return PIMUtil.throwError(MA_PIM_ERR_FIELD_INVALID,
					PIMError.PANIC_FIELD_INVALID, PIMError.sStrFieldInvalid);
		}
		if (!pimField.isSupported()) {
			return MA_PIM_ERR_FIELD_UNSUPPORTED;
		}

		return pimField.removeValue(index);
	}

	/**
	 * Gets the data type of the specified field.
	 * @param field
	 * @return
	 */
	int getFieldDataType(int field) {
		PIMField pimField = getField(field);

		if (pimField == null) {
			return PIMUtil.throwError(MA_PIM_ERR_FIELD_INVALID,
					PIMError.PANIC_FIELD_INVALID, PIMError.sStrFieldInvalid);
		}
		if (!pimField.isSupported()) {
			return MA_PIM_ERR_FIELD_UNSUPPORTED;
		}

		return pimField.getDataType();
	}

	protected abstract String getID();

	protected void delete() {
	}

	/**
	 * Closes the item
	 */
	protected void close() {
	}
}

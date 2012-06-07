package com.mosync.pim;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_NONE;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_FIELD_EMPTY;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_FIELD_READ_ONLY;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_FIELD_WRITE_ONLY;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_INDEX_INVALID;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_NO_LABEL;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_BUFFER_INVALID;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_FIELD_COUNT_MAX;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import android.content.ContentProviderOperation;
import android.content.ContentResolver;
import android.database.Cursor;
import android.provider.ContactsContract.Data;
import android.provider.ContactsContract.RawContacts;

public abstract class PIMField {

	protected static final String DUMMY = Data.LOOKUP_KEY;
	protected int MAX_SIZE;

	protected enum State {
		NONE, ADDED, UPDATED
	}

	protected enum Permission {
		FULL, READ_ONLY, WRITE_ONLY
	}

	protected int mType;
	protected String mStrType;
	protected int mDataType;
	protected Permission mPermission;
	protected String[] mNames;
	protected ArrayList<String[]> mValues;
	protected ArrayList<State> mStates;
	protected ArrayList<Long> mDeletedValues;
	protected Map<Integer, Integer> mAttributes;

	protected PIMField() {
		MAX_SIZE = Integer.MAX_VALUE;

		mValues = new ArrayList<String[]>();
		mStates = new ArrayList<State>();
		mDeletedValues = new ArrayList<Long>();
		mAttributes = new HashMap<Integer, Integer>();
		mPermission = Permission.FULL;

		createMaps();
	}

	/**
	 * @return The Content Resolver.
	 */
	public ContentResolver getContentResolver() {
		return PIMUtil.sContentResolver;
	}

	protected abstract void createMaps();

	public abstract void read(String contactId);

	public void read(Cursor cur, String calendarId) {
	}

	protected void preProcessData() {

	}

	protected abstract void print();

	protected boolean isEmpty() {
		return ((length() == 0) ? true : false);
	}

	int getType() {
		return mType;
	}

	protected int length() {
		return mValues.size();
	}

	/**
	 * Get field's attributes.
	 */
	protected int getAttributes(int index) {
		if (isEmpty()) {
			return PIMUtil.throwError(MA_PIM_ERR_FIELD_EMPTY,
					PIMError.PANIC_FIELD_EMPTY, PIMError.sStrFieldEmpty);
		}
		if ((index < 0) || (index >= length())) {
			return PIMUtil.throwError(MA_PIM_ERR_INDEX_INVALID,
					PIMError.PANIC_INDEX_INVALID, PIMError.sStrIndexInvalid);
		}

		int attr = getAndroidAttribute(index);

		if (attr < 0) {
			return 0;
		}

		int ret = ((Integer) PIMUtil.getKeyFromValue(mAttributes, attr))
				.intValue();

		ret |= checkForPreferredAttribute(index);

		return ret;
	}

	protected abstract int checkForPreferredAttribute(int index);

	/**
	 * Gets the field attribute.
	 */
	protected abstract int getAndroidAttribute(int index);

	/**
	 * Gets the custom label of the specified field.
	 */
	int getLabel(int index, int buffPointer, int buffSize) {
		if (isEmpty()) {
			return PIMUtil.throwError(MA_PIM_ERR_FIELD_EMPTY,
					PIMError.PANIC_FIELD_EMPTY, PIMError.sStrFieldEmpty);
		}

		if ((index < 0) || (index >= length())) {
			return PIMUtil.throwError(MA_PIM_ERR_INDEX_INVALID,
					PIMError.PANIC_INDEX_INVALID, PIMError.sStrIndexInvalid);
		}

		if (!hasCustomLabel(index)) {
			return MA_PIM_ERR_NO_LABEL;
		}

		char[] buffer = getLabel(index);
		if (buffer == null) {
			return 0;
		}

		if (buffer.length > (buffSize >> 1))
			return (buffer.length << 1);

		PIMUtil.copyBufferToMemory(buffPointer, buffer);

		return buffer.length;
	}

	/**
	 * Gets the field's custom label.
	 * @param index
	 * @return
	 */
	protected abstract char[] getLabel(int index);

	/**
	 * Sets the custom label of the specified field.
	 */
	int setLabel(int index, int buffPointer, int buffSize) {
		DebugPrint("PIMField.setLabel(" + index + ", " + buffPointer + ", "
				+ buffSize + ")");
		if (isEmpty()) {
			return PIMUtil.throwError(MA_PIM_ERR_FIELD_EMPTY,
					PIMError.PANIC_FIELD_EMPTY, PIMError.sStrFieldEmpty);
		}

		if ((index < 0) || (index >= length())) {
			return PIMUtil.throwError(MA_PIM_ERR_INDEX_INVALID,
					PIMError.PANIC_INDEX_INVALID, PIMError.sStrIndexInvalid);
		}

		if (isReadOnly()) {
			return MA_PIM_ERR_FIELD_READ_ONLY;
		}

		if (!hasCustomLabel(index)) {
			return MA_PIM_ERR_NO_LABEL;
		}

		char[] buffer = PIMUtil
				.readBufferFromMemory(buffPointer, buffSize >> 1);
		if (buffer != null) {
			setLabel(index, new String(buffer));
		}

		return MA_PIM_ERR_NONE;
	}

	/**
	 * Gets the field's custom label.
	 * @param index
	 * @return
	 */
	protected abstract void setLabel(int index, String label);

	/**
	 * Checks to see if the given field has a custom label.
	 * @param index
	 */
	protected abstract boolean hasCustomLabel(int index);

	/**
	 * Gets the value of the specified field.
	 */
	int getValue(int index, int buffPointer, int buffSize) {
		DebugPrint("PIMField.getValue(" + index + ", " + buffPointer + ", "
				+ buffSize + ")");
		if (isEmpty()) {
			return PIMUtil.throwError(MA_PIM_ERR_FIELD_EMPTY,
					PIMError.PANIC_FIELD_EMPTY, PIMError.sStrFieldEmpty);
		}

		if ((index < 0) || (index >= length())) {
			return PIMUtil.throwError(MA_PIM_ERR_INDEX_INVALID,
					PIMError.PANIC_INDEX_INVALID, PIMError.sStrIndexInvalid);
		}

		if (isWriteOnly()) {
			return MA_PIM_ERR_FIELD_WRITE_ONLY;
		}

		char[] buffer = getData(index);
		if (buffer == null) {
			return 0;
		}

		if (buffer.length > (buffSize >> 1))
			return (buffer.length << 1);

		PIMUtil.copyBufferToMemory(buffPointer, buffer);

		return buffer.length;
	}

	protected abstract char[] getData(int index);

	/**
	 * Sets the value of the specified field.
	 */
	int setValue(int index, int buffPointer, int buffSize, int attributes) {
		DebugPrint("setValue(" + index + ", " + buffPointer + ", " + buffSize
				+ ", " + attributes + ")");
		if (isReadOnly()) {
			return MA_PIM_ERR_FIELD_READ_ONLY;
		}

		if (isEmpty()) {
			String[] val = new String[mNames.length];
			while (index >= mValues.size()) {
				mValues.add(val);
				mStates.add(State.ADDED);
			}

			// return PIMUtil.throwError(MA_PIM_ERR_FIELD_EMPTY,
			// PIMError.PANIC_FIELD_EMPTY, PIMError.sStrFieldEmpty);

		}

		if ((index < 0) || (index >= length())) {
			return PIMUtil.throwError(MA_PIM_ERR_INDEX_INVALID,
					PIMError.PANIC_INDEX_INVALID, PIMError.sStrIndexInvalid);
		}

		char[] buffer = PIMUtil
				.readBufferFromMemory(buffPointer, buffSize >> 1);
		if ((buffer == null) || (buffer.length == 0)) {
			return MA_PIM_ERR_BUFFER_INVALID;
		}

		setData(index, buffer);

		if (mStates.get(index) != State.ADDED) {
			DebugPrint("###########################set state to UPDATED");
			mStates.set(index, State.UPDATED);
		}

		return setAttribute(index, attributes);
	}

	protected abstract void setData(int index, char[] buffer);

	/**
	 * Sets the value of the specified field.
	 */
	int addValue(int buffPointer, int buffSize, int attributes) {
		if (isReadOnly()) {
			return MA_PIM_ERR_FIELD_READ_ONLY;
		}

		if (length() >= MAX_SIZE) {
			return MA_PIM_ERR_FIELD_COUNT_MAX;
		}

		char[] buffer = PIMUtil
				.readBufferFromMemory(buffPointer, buffSize >> 1);
		if ((buffer == null) || (buffer.length == 0)) {
			return MA_PIM_ERR_BUFFER_INVALID;
		}

		String[] val = new String[mNames.length];
		int index = mValues.size();
		mValues.add(val);
		mStates.add(State.ADDED);

		setData(index, buffer);

		int err = MA_PIM_ERR_NONE;
		if ((err = setAttribute(index, attributes)) != MA_PIM_ERR_NONE) {
			return err;
		}

		print();

		return index;
	}

	protected abstract int setAttribute(int index, int attribute);

	/**
	 * Removes the value of the specified field.
	 */
	int removeValue(int index) {
		if (isReadOnly()) {
			return MA_PIM_ERR_FIELD_READ_ONLY;
		}

		if (isEmpty()) {
			return PIMUtil.throwError(MA_PIM_ERR_FIELD_EMPTY,
					PIMError.PANIC_FIELD_EMPTY, PIMError.sStrFieldEmpty);
		}

		if ((index < 0) || (index >= length())) {
			return PIMUtil.throwError(MA_PIM_ERR_INDEX_INVALID,
					PIMError.PANIC_INDEX_INVALID, PIMError.sStrIndexInvalid);
		}

		if (mStates.get(index) != State.ADDED) {
			mDeletedValues.add(Long.parseLong(mValues.get(index)[0]));
		}

		mValues.remove(index);
		mStates.remove(index);

		return MA_PIM_ERR_NONE;
	}

	int getDataType() {
		return mDataType;
	}

	boolean isWriteOnly() {
		return (mPermission == Permission.WRITE_ONLY);
	}

	boolean isReadOnly() {
		return (mPermission == Permission.READ_ONLY);
	}

	protected boolean isSupported() {
		return true;
	}

	/**
	 * Gets the field's value corresponding to the given column name.
	 * @param index
	 * @param name
	 * @return
	 */
	protected String getColumnValue(int index, String name) {
		String[] val = mValues.get(index);
		for (int i = 0; i < mNames.length; i++) {
			if (mNames[i].equals(name)) {
				return val[i];
			}
		}
		return null;
	}

	/**
	 * Sets the field's value corresponding to the given column name.
	 * @param index
	 * @param name
	 * @return
	 */
	protected void setColumnValue(int index, String name, String value) {
		String[] val = mValues.get(index);
		for (int i = 0; i < mNames.length; i++) {
			if (mNames[i].equals(name)) {
				val[i] = value;
				mValues.set(index, val);
				break;
			}
		}
	}

	protected void postProcessData() {

	}

	public void add(ArrayList<ContentProviderOperation> ops, String lookup) {
		if (isReadOnly()) {
			return;
		}
		DebugPrint("ADD " + mStrType);
		print();
		postProcessData();
		for (int i = 0; i < mValues.size(); i++) {
			addToDisk(ops, lookup, mNames, mValues.get(i));
		}
	}

	public void update(ContentResolver cr,
			ArrayList<ContentProviderOperation> ops, String lookup) {
		DebugPrint("Update + " + mStrType);
		if (isReadOnly()) {
			return;
		}
		postProcessData();

		DebugPrint("Values = " + mValues.size());

		for (int i = 0; i < mValues.size(); i++) {
			DebugPrint("State " + i + ": " + mStates.get(i));
			if (mStates.get(i) == State.ADDED) {
				addToDisk(ops, lookup, mNames, mValues.get(i));
			} else if (mStates.get(i) == State.UPDATED) {
				updateToDisk(ops, lookup, mNames, mValues.get(i));
			}
		}

		for (int i = 0; i < mDeletedValues.size(); i++) {
			deleteFromDisk(ops, lookup, mDeletedValues.get(i));
		}
	}

	protected void addToDisk(ArrayList<ContentProviderOperation> ops,
			String lookup, String[] names, String[] values) {
		DebugPrint("addToDisk " + lookup + "; data type: " + mStrType);

		Cursor cursor = getContentResolver().query(Data.CONTENT_URI,
				new String[] { Data.RAW_CONTACT_ID }, Data.LOOKUP_KEY + "=?",
				new String[] { lookup }, null);
		String id = null;
		if (cursor.moveToNext()) {
			id = cursor.getString(cursor.getColumnIndex(Data.RAW_CONTACT_ID));
		}

		cursor.close();

		// cursor = getContentResolver().query(
		// RawContacts.CONTENT_URI,
		// new String[] { RawContacts.ACCOUNT_TYPE,
		// RawContacts.ACCOUNT_NAME },
		// RawContacts.CONTACT_ID + "=?", new String[] { id }, null);
		//
		// String accountType = null;
		// String accountName = null;
		// if (cursor.moveToNext()) {
		// accountType = cursor.getString(cursor
		// .getColumnIndex(RawContacts.ACCOUNT_TYPE));
		// accountName = cursor.getString(cursor
		// .getColumnIndex(RawContacts.ACCOUNT_NAME));
		// }
		//
		// DebugPrint("account type = " + accountType + "; accountName = "
		// + accountName);
		//
		// cursor.close();

		// int rawContactInsertIndex = ops.size();

		// ops.add(ContentProviderOperation.newInsert(RawContacts.CONTENT_URI)
		// .withValue(RawContacts.ACCOUNT_TYPE, accountType)
		// .withValue(RawContacts.ACCOUNT_NAME, accountName).build());

		// ContentProviderOperation.Builder builder = ContentProviderOperation
		// .newInsert(Data.CONTENT_URI).withValueBackReference(
		// Data.RAW_CONTACT_ID, rawContactInsertIndex);
		ContentProviderOperation.Builder builder = ContentProviderOperation
				.newInsert(Data.CONTENT_URI).withValue(Data.RAW_CONTACT_ID, id)
				.withValue(Data.MIMETYPE, mStrType);

		builder = builder.withValue(Data.MIMETYPE, mStrType);
		boolean canBuild = false;
		for (int i = 1; i < names.length; i++) {
			DebugPrint(names[i] + ": " + values[i]);
			if ((values[i] != null) && (!names[i].equals(DUMMY))) {
				builder = builder.withValue(names[i], values[i]);
				canBuild = true;
			}
		}

		if (canBuild) {
			DebugPrint("Operation ADD");
			ops.add(builder.build());
		}
	}

	protected void updateToDisk(ArrayList<ContentProviderOperation> ops,
			String lookup, String[] names, String[] values) {
		DebugPrint("updateToDisk " + lookup + "; data type: " + mStrType);

		ContentProviderOperation.Builder builder = ContentProviderOperation
				.newUpdate(Data.CONTENT_URI).withSelection(
						Data.LOOKUP_KEY + "=?" + " AND " + Data.MIMETYPE + "=?"
								+ " AND " + Data._ID + "=?",
						new String[] { lookup, mStrType, values[0] });

		boolean canBuild = false;
		for (int i = 1; i < names.length; i++) {
			if ((values[i] != null) && (!names[i].equals(DUMMY))) {
				DebugPrint(names[i] + ": " + values[i]);
				builder = builder.withValue(names[i], values[i]);
				canBuild = true;
			}
		}

		if (canBuild) {
			DebugPrint("Operation UPDATE");
			ops.add(builder.build());
		}
	}

	void deleteFromDisk(ArrayList<ContentProviderOperation> ops, String lookup,
			long id) {
		DebugPrint("DELETE");
		ops.add(ContentProviderOperation
				.newDelete(Data.CONTENT_URI)
				.withSelection(
						Data.LOOKUP_KEY + "=?" + " AND " + Data.MIMETYPE + "=?"
								+ " AND " + Data._ID + "=?",
						new String[] { lookup, mStrType, Long.toString(id) })
				.build());
	}

	public void close() {
	}
}

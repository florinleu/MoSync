package com.mosync.pim;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;

import java.util.ArrayList;
import java.util.Iterator;

import com.mosync.internal.android.MoSyncError;

import android.content.ContentResolver;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_NONE;

public abstract class PIMList {

	protected ArrayList<PIMItem> mList;
	protected int mListIterator;

	protected PIMList() {
		DebugPrint("PIMList()");
		mList = new ArrayList<PIMItem>();
		mListIterator = -1;
	}

	/**
	 * @param errorCode
	 *            The error code returned by the syscall.
	 * @param panicCode
	 *            The panic code for this error.
	 * @param panicText
	 *            The panic text for this error.
	 * @return
	 */
	public int throwError(int errorCode, int panicCode, String panicText) {
		return MoSyncError.getSingletonObject().error(errorCode, panicCode,
				panicText);
	}

	/**
	 * @return The Content Resolver.
	 */
	public ContentResolver getContentResolver() {
		return PIMUtil.sContentResolver;
	}

	/**
	 * Read the list
	 */
	protected abstract int read();

	/**
	 * Checks if we reached the end of the list.
	 */
	boolean hasNext() {
		return ((mList.size() > 0) && (mListIterator < mList.size()));
	}

	/**
	 * @return The next element in the list.
	 */
	PIMItem next() {
		DebugPrint("PIMList.next()");

		PIMItem pimItem = mList.get(mListIterator++);

		// pimItem.read();
		// mList.set(mListIterator++, pimItem);

		return pimItem;
	}

	/*
	 * Finds the item with the specified id.
	 */
	PIMItem find(int buffPointer, int buffSize) {
		DebugPrint("PIMList.find(" + buffPointer + ", " + buffSize + ")");
		PIMItem pimItem = null;

		char[] buffer = PIMUtil
				.readBufferFromMemory(buffPointer, buffSize >> 1);

		if (buffer == null) {
			return null;
		}

		String id = new String(buffer);
		DebugPrint("String id = " + id);
		Iterator<PIMItem> iterator = mList.iterator();
		while (iterator.hasNext()) {
			pimItem = iterator.next();
			if (pimItem.getID().compareTo(id) == 0) {
				return pimItem;
			}
		}
		return null;
	}

	/**
	 * @param field
	 * @return The data type of the field.
	 */
	int getFieldDataType(int field) {
		DebugPrint("PIMList.getFieldDataType(" + field + ")");
		return mList.get(0).getFieldDataType(field);
	}

	protected abstract PIMItem createItem();

	int removeItem(PIMItem item) {
		int index = -1;
		for (int i = 0; i < mList.size(); i++) {
			if (mList.get(i) == item) {
				index = i;
				break;
			}
		}
		if (index == mListIterator) {
			mListIterator--;
		}
		if (index != -1) {
			mList.remove(index);
		}
		return MA_PIM_ERR_NONE;
	}

	/**
	 * Closes the list.
	 */
	void close() {
		DebugPrint("PIMList.close()");
		try {
			mListIterator = 0;
			while (hasNext()) {
				next().close();
			}
		} catch (Exception e) {
		}
	}
}

package com.mosync.pim;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;

import java.util.ArrayList;
import android.content.ContentResolver;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_NONE;

public abstract class PIMList {

	protected ArrayList<PIMItem> mList;
	protected int mListIterator;

	protected PIMList() {
		mList = new ArrayList<PIMItem>();
		mListIterator = -1;
	}

	/**
	 * Checks if we reached the end of the list.
	 */
	boolean hasNext() {
		return mListIterator < mList.size();
	}

	/**
	 * @return The next element in the list.
	 */
	PIMItem next() {
		return mList.get(mListIterator++);
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
	void close(ContentResolver cr) {
		DebugPrint("PIMList.close(" + cr + ")");
		mListIterator = 0;
		while (hasNext()) {
			next().close(cr);
		}
	}
}

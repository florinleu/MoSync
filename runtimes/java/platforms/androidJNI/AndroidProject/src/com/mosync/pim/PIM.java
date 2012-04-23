package com.mosync.pim;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_CONTACTS;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_EVENTS;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_HANDLE_INVALID;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_LIST_ALREADY_OPENED;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_LIST_TYPE_INVALID;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_INDEX_INVALID;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_NONE;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_LIST_UNAVAILABLE;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_ID_INVALID;

import java.util.Hashtable;

import android.app.Activity;
import android.content.ContentResolver;
import android.database.Cursor;
import android.net.Uri;
import com.mosync.internal.android.MoSyncThread;
import com.mosync.pim.contacts.*;
import com.mosync.pim.events.*;

public class PIM {

	/**
	 * The MoSync thread object.
	 */
	private MoSyncThread mMoSyncThread;

	/**
	 * PIM lists
	 */
	private Hashtable<Integer, PIMItem> mPIMItems;
	private Hashtable<Integer, PIMList> mPIMLists;
	private Hashtable<Integer, PIMListEvents> mPIMEventsList;

	boolean mIsContactListOpened = false;

	/**
	 * @return The Activity object.
	 */
	public Activity getActivity() {
		return mMoSyncThread.getActivity();
	}

	/**
	 * @return The Content Resolver.
	 */
	public ContentResolver getContentResolver() {
		return PIMUtil.sContentResolver;
	}

	/**
	 * Constructor.
	 * @param thread
	 *            The MoSync thread.
	 */
	public PIM(MoSyncThread thread) {
		mMoSyncThread = thread;
		PIMUtil.sContentResolver = getActivity().getContentResolver();
		mPIMItems = new Hashtable<Integer, PIMItem>();
		mPIMLists = new Hashtable<Integer, PIMList>();
		mPIMEventsList = new Hashtable<Integer, PIMListEvents>();
	}

	PIMList getList(int handle) {
		return mPIMLists.get(handle);
	}

	/**
	 * Returns the PIM list number depending on the listType
	 */
	public int maPimListCount(int listType) {
		DebugPrint("maPimListCount()");
		switch (listType) {
		case MA_PIM_CONTACTS:
			return 1;
		case MA_PIM_EVENTS:
			return countEventsList();
		}

		return PIMUtil.throwError(MA_PIM_ERR_LIST_TYPE_INVALID,
				PIMError.PANIC_LIST_TYPE_INVALID, PIMError.sStrListTypeInvalid);
	}

	private Cursor getCalendarManagedCursor(String[] projection,
			String selection, String path) {
		DebugPrint("getCalendarManagedCursor(" + projection + ", " + selection
				+ ", " + path + ")");
		String sortOrder = "_id";
		try {
			Uri calendars = Uri.parse("content://calendar/" + path);

			Cursor managedCursor = null;
			try {
				managedCursor = getContentResolver().query(calendars, // fleu
																		// TODO
																		// close
																		// this
																		// cursor
						projection, selection, null, sortOrder);
			} catch (IllegalArgumentException e) {
				DebugPrint("Failed to get provider at [" + calendars.toString()
						+ "]");
			}

			if (managedCursor == null) {
				// try again
				calendars = Uri.parse("content://com.android.calendar/" + path);
				try {
					managedCursor = getContentResolver().query(calendars,
							projection, selection, null, sortOrder);
				} catch (IllegalArgumentException e) {
					DebugPrint("Failed to get provider at ["
							+ calendars.toString() + "]");
				}
			}
			return managedCursor;
		} catch (Exception e) {
			return null;
		}
	}

	int countEventsList() {
		String[] projection = new String[] { "_id" };
		String selection = null;
		String path = "calendars";

		Cursor managedCursor = getCalendarManagedCursor(projection, selection,
				path);
		if (managedCursor != null) {
			int count = managedCursor.getCount();
			managedCursor.close();
			managedCursor = null;
			return count;
		} else
			return PIMUtil.throwError(MA_PIM_ERR_LIST_UNAVAILABLE,
					PIMError.PANIC_LIST_UNAVAILABLE,
					PIMError.sStrListUnavailable);
	}

	/**
	 * Opens the PIM list depending on the listType
	 */
	public int maPimListOpen(int listType, int index) {
		DebugPrint("maPimListOpen(" + listType + ", " + index + ")");
		switch (listType) {
		case MA_PIM_CONTACTS:
			return openContactsList(index);
		case MA_PIM_EVENTS:
			return openEventsList(index);
		}

		return PIMUtil.throwError(MA_PIM_ERR_LIST_TYPE_INVALID,
				PIMError.PANIC_LIST_TYPE_INVALID, PIMError.sStrListTypeInvalid);
	}

	/**
	 * @return false if the contact list is null
	 */
	boolean isContactListOpened() {
		return mIsContactListOpened;
	}

	/**
	 * Opens the contacts list.
	 */
	int openContactsList(int index) {
		DebugPrint("openContactsList(" + index + ")");
		if (index > 0) {
			return PIMUtil.throwError(MA_PIM_ERR_INDEX_INVALID,
					PIMError.PANIC_INDEX_INVALID, PIMError.sStrIndexInvalid);
		}
		// if opened, return error code
		if (isContactListOpened()) {
			return PIMUtil.throwError(MA_PIM_ERR_LIST_ALREADY_OPENED,
					PIMError.PANIC_LIST_ALREADY_OPENED,
					PIMError.sStrListAlreadyOpened);
		}

		int placeholder = PIMUtil.getThread().nativeCreatePlaceholder();
		mPIMLists.put(placeholder, new PIMListContacts());
		mIsContactListOpened = true;

		// try to read the items in the list
		// if failed, return error code
		int error = 0;
		if ((error = mPIMLists.get(placeholder).read()) < 0) {
			mPIMLists.remove(placeholder);
			// maDestroyPlaceHolder(placeholder); fleu TODO
			return error;
		}

		return placeholder;
	}

	/**
	 * @return the contact list
	 */
	PIMListEvents getEventsList(int index) {
		if (mPIMEventsList.get(index) == null) {
			mPIMEventsList.put(Integer.valueOf(index), new PIMListEvents());
		}
		return mPIMEventsList.get(index);
	}

	/**
	 * @return false if the contact list is null
	 */
	boolean isEventsListOpened(int index) {
		return ((mPIMEventsList.get(index) != null) ? true : false);
	}

	/**
	 * Opens the events list.
	 */
	int openEventsList(int index) {
		int listCount = countEventsList();
		if ((listCount > 0) && (index > listCount)) {
			return PIMUtil.throwError(MA_PIM_ERR_INDEX_INVALID,
					PIMError.PANIC_INDEX_INVALID, PIMError.sStrIndexInvalid);
		}
		DebugPrint("openEventsList()");
		// if opened, return error code
		if (isEventsListOpened(index)) {
			return PIMUtil.throwError(MA_PIM_ERR_LIST_ALREADY_OPENED,
					PIMError.PANIC_LIST_ALREADY_OPENED,
					PIMError.sStrListAlreadyOpened);
		}

		String[] projection = new String[] { "_id" };
		String selection = null;
		String path = "calendars";

		Cursor managedCursor = getCalendarManagedCursor(projection, selection,
				path);

		// try to read the items in the list
		// if failed, return error code
		int error = 0;
		if ((error = getEventsList(index).read(managedCursor, index)) < 0) {
			return error;
		}

		managedCursor.close();
		managedCursor = null;

		return (mPIMEventsList.size());
	}

	public int maPimListNext(int list) {
		DebugPrint("maPimListNext(" + list + ")");
		PIMList pimList = null;
		if ((list < 0) || ((pimList = getList(list)) == null)) {
			return PIMUtil.throwError(MA_PIM_ERR_HANDLE_INVALID,
					PIMError.PANIC_HANDLE_INVALID, PIMError.sStrHandleInvalid);
		}

		int placeholder = PIMUtil.getThread().nativeCreatePlaceholder();
		if (pimList.hasNext()) {
			mPIMItems.put(placeholder, pimList.next());
		} else {
			return MA_PIM_ERR_NONE;
		}

		return placeholder;
	}

	public int maPimListFind(int list, int buffPointer, int buffSize) {
		DebugPrint("maPimListFind(" + list + ")");
		PIMList pimList = null;
		if ((list < 0) || ((pimList = getList(list)) == null)) {
			return PIMUtil.throwError(MA_PIM_ERR_HANDLE_INVALID,
					PIMError.PANIC_HANDLE_INVALID, PIMError.sStrHandleInvalid);
		}

		int placeholder = PIMUtil.getThread().nativeCreatePlaceholder();
		PIMItem item = null;
		if ((item = pimList.find(buffPointer, buffSize)) != null) {
			mPIMItems.put(placeholder, item);
		} else {
			return PIMUtil.throwError(MA_PIM_ERR_ID_INVALID,
					PIMError.PANIC_ID_INVALID, PIMError.sStrHandleInvalid);
		}

		return placeholder;
	}

	public int maPimListClose(int list) {
		DebugPrint("maPimListClose(" + list + ")");
		PIMList pimList = null;
		if ((list < 0) || ((pimList = getList(list)) == null)) {
			return PIMUtil.throwError(MA_PIM_ERR_HANDLE_INVALID,
					PIMError.PANIC_HANDLE_INVALID, PIMError.sStrHandleInvalid);
		}

		if (pimList instanceof PIMListContacts) {
			mIsContactListOpened = false;
		}

		pimList.close();
		mPIMLists.remove(list);
		// maDestroyPlaceholder(list); fleu TODO
		pimList = null;

		// mPIMEventsList.remove(list - 1);
		// mPIMEventsList = null;

		return MA_PIM_ERR_NONE;
	}

	// fleu TODO
	public int maPimItemCount(int item) {
		DebugPrint("maPimItemCount(" + item + ")");
		PIMItem pimItem = null;
		if ((item < 0) || ((pimItem = mPIMItems.get(item)) == null)) {
			return PIMUtil.throwError(MA_PIM_ERR_HANDLE_INVALID,
					PIMError.PANIC_HANDLE_INVALID, PIMError.sStrHandleInvalid);
		}

		return pimItem.length();
	}

	// fleu TODO
	public int maPimItemGetField(int item, int n) {
		DebugPrint("maPimItemGetField(" + item + ", " + n + ")");
		PIMItem pimItem = null;
		if ((item < 0) || ((pimItem = mPIMItems.get(item)) == null)) {
			return PIMUtil.throwError(MA_PIM_ERR_HANDLE_INVALID,
					PIMError.PANIC_HANDLE_INVALID, PIMError.sStrHandleInvalid);
		}

		return pimItem.getFieldType(n);
	}

	// fleu TODO
	public int maPimItemFieldCount(int item, int field) {
		DebugPrint("maPimItemFieldCount(" + item + ", " + field + ")");
		PIMItem pimItem = null;
		if ((item < 0) || ((pimItem = mPIMItems.get(item)) == null)) {
			return PIMUtil.throwError(MA_PIM_ERR_HANDLE_INVALID,
					PIMError.PANIC_HANDLE_INVALID, PIMError.sStrHandleInvalid);
		}

		return pimItem.getFieldLength(field);
	}

	// fleu TODO
	public int maPimItemGetAttributes(int item, int field, int index) {
		DebugPrint("maPimItemGetAttributes(" + item + ", " + field + ", "
				+ index + ")");
		PIMItem pimItem = null;
		if ((item < 0) || ((pimItem = mPIMItems.get(item)) == null)) {
			return PIMUtil.throwError(MA_PIM_ERR_HANDLE_INVALID,
					PIMError.PANIC_HANDLE_INVALID, PIMError.sStrHandleInvalid);
		}

		return pimItem.getFieldAttributes(field, index);
	}

	// fleu TODO
	public int maPimItemSetLabel(int item, int field, int buffPointer,
			int buffSize, int index) {
		DebugPrint("maPimItemSetLabel(" + item + ", " + field + ", "
				+ buffPointer + ", " + buffSize + ", " + index + ")");
		PIMItem pimItem = null;
		if ((item < 0) || ((pimItem = mPIMItems.get(item)) == null)) {
			return PIMUtil.throwError(MA_PIM_ERR_HANDLE_INVALID,
					PIMError.PANIC_HANDLE_INVALID, PIMError.sStrHandleInvalid);
		}

		return pimItem.setFieldLabel(field, index, buffPointer, buffSize);
	}

	// fleu TODO
	public int maPimItemGetLabel(int item, int field, int buffPointer,
			int buffSize, int index) {
		DebugPrint("maPimItemGetLabel(" + item + ", " + field + ", "
				+ buffPointer + ", " + buffSize + ", " + index + ")");
		PIMItem pimItem = null;
		if ((item < 0) || ((pimItem = mPIMItems.get(item)) == null)) {
			return PIMUtil.throwError(MA_PIM_ERR_HANDLE_INVALID,
					PIMError.PANIC_HANDLE_INVALID, PIMError.sStrHandleInvalid);
		}

		return pimItem.getFieldLabel(field, index, buffPointer, buffSize);
	}

	public int maPimFieldType(int list, int field) {
		DebugPrint("maPimFieldType(" + list + ", " + field + ")");
		PIMList pimList = null;
		if ((list < 0) || ((pimList = getList(list)) == null)) {
			return PIMUtil.throwError(MA_PIM_ERR_HANDLE_INVALID,
					PIMError.PANIC_HANDLE_INVALID, PIMError.sStrHandleInvalid);
		}

		return pimList.getFieldDataType(field);
	}

	public int maPimItemGetValue(int item, int field, int buffPointer,
			int buffSize, int index) {
		DebugPrint("maPimItemGetValue(" + item + ", " + field + ", "
				+ buffPointer + ", " + buffSize + ", " + index + ")");
		PIMItem pimItem = null;
		if ((item < 0) || ((pimItem = mPIMItems.get(item)) == null)) {
			return PIMUtil.throwError(MA_PIM_ERR_HANDLE_INVALID,
					PIMError.PANIC_HANDLE_INVALID, PIMError.sStrHandleInvalid);
		}

		return pimItem.getFieldValue(field, index, buffPointer, buffSize);
	}

	public int maPimItemSetValue(int item, int field, int buffPointer,
			int buffSize, int index, int attributes) {
		DebugPrint("maPimItemSetValue(" + item + ", " + field + ", "
				+ buffPointer + ", " + buffSize + ", " + index + ")");
		PIMItem pimItem = null;
		if ((item < 0) || ((pimItem = mPIMItems.get(item)) == null)) {
			return PIMUtil.throwError(MA_PIM_ERR_HANDLE_INVALID,
					PIMError.PANIC_HANDLE_INVALID, PIMError.sStrHandleInvalid);
		}

		return pimItem.setFieldValue(field, index, buffPointer, buffSize,
				attributes);
	}

	public int maPimItemAddValue(int item, int field, int buffPointer,
			int buffSize, int attributes) {
		DebugPrint("maPimItemAddValue(" + item + ", " + field + ", "
				+ buffPointer + ", " + buffSize + ")");
		PIMItem pimItem = null;
		if ((item < 0) || ((pimItem = mPIMItems.get(item)) == null)) {
			return PIMUtil.throwError(MA_PIM_ERR_HANDLE_INVALID,
					PIMError.PANIC_HANDLE_INVALID, PIMError.sStrHandleInvalid);
		}

		return pimItem.addFieldValue(field, buffPointer, buffSize, attributes);
	}

	public int maPimItemRemoveValue(int item, int field, int index) {
		DebugPrint("maPimItemRemoveValue(" + item + ", " + field + ", " + index
				+ ")");
		PIMItem pimItem = null;
		if ((item < 0) || ((pimItem = mPIMItems.get(item)) == null)) {
			return PIMUtil.throwError(MA_PIM_ERR_HANDLE_INVALID,
					PIMError.PANIC_HANDLE_INVALID, PIMError.sStrHandleInvalid);
		}

		return pimItem.removeFieldValue(field, index);
	}

	public int maPimItemClose(int item) {
		DebugPrint("maPimItemClose(" + item + ")");
		PIMItem pimItem = null;
		if ((item < 0) || ((pimItem = mPIMItems.get(item)) == null)) {
			return PIMUtil.throwError(MA_PIM_ERR_HANDLE_INVALID,
					PIMError.PANIC_HANDLE_INVALID, PIMError.sStrHandleInvalid);
		}
		DebugPrint("pimItem.close()");
		pimItem.close();
		pimItem = null;

		mPIMItems.remove(item);

		return MA_PIM_ERR_NONE;
	}

	public int maPimItemCreate(int list) {
		DebugPrint("maPimItemCreate(" + list + ")");
		PIMList pimList = null;
		if ((list < 0) || ((pimList = getList(list)) == null)) {
			return PIMUtil.throwError(MA_PIM_ERR_HANDLE_INVALID,
					PIMError.PANIC_HANDLE_INVALID, PIMError.sStrHandleInvalid);
		}

		int placeholder = PIMUtil.getThread().nativeCreatePlaceholder();
		mPIMItems.put(placeholder, pimList.createItem());

		return placeholder++;
	}

	public int maPimItemRemove(int list, int item) {
		DebugPrint("maPimItemRemove(" + list + ", " + item + ")");
		PIMList pimList = null;
		if ((list < 0) || ((pimList = getList(list)) == null)) {
			return PIMUtil.throwError(MA_PIM_ERR_HANDLE_INVALID,
					PIMError.PANIC_HANDLE_INVALID, PIMError.sStrHandleInvalid);
		}
		PIMItem pimItem = null;
		if ((item < 0) || ((pimItem = mPIMItems.get(item)) == null)) {
			return PIMUtil.throwError(MA_PIM_ERR_HANDLE_INVALID,
					PIMError.PANIC_HANDLE_INVALID, PIMError.sStrHandleInvalid);
		}
		pimItem.delete();
		return pimList.removeItem(pimItem);
	}
}

package com.mosync.pim.contacts;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;
import java.util.ArrayList;

import static com.mosync.internal.generated.IX_PIM.MA_PIM_ATTRPREFERRED;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_ATTRIBUTE_COMBO_UNSUPPORTED;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_FIELD_EMPTY;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_INDEX_INVALID;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_NONE;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_FIELD_CONTACT_PHOTO;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_TYPE_INT;

import android.content.ContentProviderOperation;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.provider.ContactsContract.CommonDataKinds.Photo;
import android.provider.ContactsContract.CommonDataKinds.StructuredPostal;
import android.provider.ContactsContract.Data;

import com.mosync.pim.*;

public class PIMFieldPhoto extends PIMFieldContacts {

	/**
	 * Constructor
	 */
	public PIMFieldPhoto() {
		MAX_SIZE = 1;

		mType = MA_PIM_FIELD_CONTACT_PHOTO;
		mStrType = Photo.CONTENT_ITEM_TYPE;
		mDataType = MA_PIM_TYPE_INT;

		mNames = new String[] { Photo.PHOTO };
	}

	protected void createMaps() {
	}

	/**
	 * Read field
	 * @param cr
	 * @param contactId
	 */
	public void read(String contactId) {
		DebugPrint("PIMFieldPhoto.read(" + contactId + ")");
		Cursor cursor = getContentResolver().query(Data.CONTENT_URI, mNames,
				Data.LOOKUP_KEY + "=?" + " AND " + Data.MIMETYPE + "=?",
				new String[] { String.valueOf(contactId), mStrType }, null);

		while (cursor.moveToNext()) {
			String[] val = new String[mNames.length];
			int index = cursor.getColumnIndex(mNames[0]);

			if (index >= 0) {
				byte[] b = cursor.getBlob(index);

				if (b != null) {
					val[0] = Integer.toString(loadPhoto(b));
				}
			}
			if ((val[0] != null) && !val[0].equals("")) {
				mValues.add(val);
				mStates.add(State.NONE);
			}
		}

		cursor.close();
		cursor = null;

		print();
	}

	public int loadPhoto(byte[] buffer) {
		int photoHandle = PIMUtil.getThread().nativeCreatePlaceholder();

		Bitmap bitmap = PIMUtil.getThread().decodeImageFromData(buffer, null);

		if (bitmap != null) {
			PIMUtil.getThread().addBitmap(photoHandle, bitmap);
		}

		return photoHandle;
	}

	protected int getAttributes(int index) {
		if (isEmpty()) {
			return MA_PIM_ERR_FIELD_EMPTY;
		}
		if ((index < 0) || (index >= length())) {
			return MA_PIM_ERR_INDEX_INVALID;
		}

		int ret = checkForPreferredAttribute(index);

		return ret;
	}

	protected int checkForPreferredAttribute(int index) {
		try {
			if (Integer.parseInt(getColumnValue(index, Photo.IS_PRIMARY)) != 0)
				return MA_PIM_ATTRPREFERRED;
		} catch (NumberFormatException e) {
		}
		return 0;
	}

	protected int getAndroidAttribute(int index) {
		return 0;
	}

	protected int setAttribute(int index, int attribute) {
		setColumnValue(index, Photo.IS_PRIMARY,
				Integer.toString(((attribute & MA_PIM_ATTRPREFERRED) != 0) ? 1
						: 0));
		attribute &= 0xFFFF;

		if (attribute != 0) {
			return MA_PIM_ERR_ATTRIBUTE_COMBO_UNSUPPORTED;
		}

		return MA_PIM_ERR_NONE;
	}

	/**
	 * Gets the field's custom label.
	 * @param index
	 * @return
	 */
	protected char[] getLabel(int index) {
		return null;
	}

	/**
	 * Gets the field's custom label.
	 * @param index
	 * @return
	 */
	protected void setLabel(int index, String label) {
	}

	/**
	 * Checks to see if the given field has a custom label.
	 * @param index
	 */
	protected boolean hasCustomLabel(int index) {
		return false;
	}

	protected char[] getData(int index) {
		String val = getSpecificData(index);
		if ((val == null) || val.equals("")) {
			return null;
		}
		char[] buffer = new char[getDataSize(val)];
		int toWrite = -1;
		try {
			toWrite = Integer.parseInt(val);
		} catch (NumberFormatException e) {
		}
		PIMUtil.writeInt(toWrite, buffer, 0);
		return buffer;
	}

	String getSpecificData(int index) {
		String[] val = mValues.get(index);
		return val[0];
	}

	int getDataSize(String val) {
		return (Integer.SIZE / 8);
	}

	protected void setData(int index, char[] buffer) {
		String val = Integer.toString(PIMUtil.readInt(buffer, 0));
		setSpecificData(val, index);
	}

	void setSpecificData(String data, int index) {
		String[] val = mValues.get(index);
		val[0] = data;
		mValues.set(index, val);
	}

	protected void addToDisk(ArrayList<ContentProviderOperation> ops,
			String lookup, String[] names, String[] values) {
		DebugPrint("Photo.addToDisk " + lookup + "; data type: " + mStrType);

		Cursor cursor = getContentResolver().query(Data.CONTENT_URI,
				new String[] { Data.RAW_CONTACT_ID }, Data.LOOKUP_KEY + "=?",
				new String[] { lookup }, null);
		String id = null;
		if (cursor.moveToNext()) {
			id = cursor.getString(cursor.getColumnIndex(Data.RAW_CONTACT_ID));
		}

		cursor.close();

		ContentProviderOperation.Builder builder = ContentProviderOperation
				.newInsert(Data.CONTENT_URI)
				.withValue(Data.RAW_CONTACT_ID, id)
				.withValue(Data.MIMETYPE, mStrType);

		for (int i = 0; i < names.length; i++) {
			if (values[i] != null) {
				if (names[i].equals(Photo.PHOTO)) {
					byte[] buffer = PIMUtil.getThread()
							.getUnloadedBinaryResourceAsByteArray(
									Integer.parseInt(values[i]));
					if (buffer != null) {
						builder = builder.withValue(names[i], buffer);
					}
				} else {
					builder = builder.withValue(names[i], values[i]);
				}
			}
		}

		ops.add(builder.build());
	}

	protected void updateToDisk(ArrayList<ContentProviderOperation> ops,
			int rawContactId, String[] names, String[] values) {
		ContentProviderOperation.Builder builder = ContentProviderOperation
				.newUpdate(Data.CONTENT_URI).withSelection(
						Data.LOOKUP_KEY + "=?" + " AND " + Data.MIMETYPE + "=?"
								+ " AND " + Data._ID + "=?",
						new String[] { Integer.toString(rawContactId),
								mStrType, values[0] });

		for (int i = 1; i < names.length; i++) {
			if (values[i] != null) {
				if (names[i].equals(Photo.PHOTO)) {
					byte[] buffer = PIMUtil.getThread()
							.getUnloadedBinaryResourceAsByteArray(
									Integer.parseInt(values[i]));
					if (buffer != null) {
						builder = builder.withValue(names[i], buffer);
					}
				} else {
					// builder = builder.withValue(names[i], values[i]);
				}
			}
		}

		ops.add(builder.build());
	}

	public void close() {
		for (int i = 0; i < mValues.size(); i++) {
			if (!mValues.get(i)[0].equals("")) {
				PIMUtil.getThread().destroyResource(
						Integer.parseInt(mValues.get(i)[0]));
			}
		}
	}

	/**
	 * Print field values.
	 */
	protected void print() {
		String[] val = null;
		DebugPrint("***********PHOTO***********");
		if ((mValues == null) || (mValues.size() == 0)
				|| ((val = mValues.get(0)) == null)) {
			DebugPrint("Not available");
		} else {
			DebugPrint("Photo: " + val[0]);
		}
		DebugPrint("***************************");
	}
}

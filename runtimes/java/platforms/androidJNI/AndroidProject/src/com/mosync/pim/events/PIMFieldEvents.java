package com.mosync.pim.events;

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

import com.mosync.pim.PIMError;
import com.mosync.pim.PIMUtil;

import android.content.ContentProviderOperation;
import android.content.ContentResolver;
import android.database.Cursor;
import android.provider.ContactsContract.Data;

import com.mosync.pim.*;

public abstract class PIMFieldEvents extends PIMField {

	/**
	 * 
	 */
	public void read(Cursor cur, String calendarId) {

	}

}

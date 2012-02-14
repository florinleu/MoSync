package com.mosync.pim.contacts;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;

import com.mosync.pim.*;

public class PIMListContacts extends PIMList {

	PIMListContacts(int placeholder)
	{
		mHandle = placeholder;
	}

	protected PIMItem createItem() {
		PIMItemContacts p = new PIMItemContacts(true);
		mList.add(p);
		return p;
	}

}

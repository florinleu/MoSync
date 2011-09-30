package com.mosync.pim;

public class PIMItemEvents extends PIMItem {

	public PIMItemEvents(boolean isNew) {
		setState(State.NONE);
		if (isNew) {
			setState(State.ADDED);
		}
	}

}

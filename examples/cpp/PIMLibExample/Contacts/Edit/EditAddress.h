/* Copyright (C) 2011 MoSync AB

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.
*/

/**
 * @file EditAddress.h
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Address Edit Layout.
 *
 **/

#ifndef __EDITADDRESS_H__
#define __EDITADDRESS_H__

#include "EditField.h"

#include "Observer.h"

class EditAddress:
	public EditField,
	public Observer
{
	public:
		/**
		 * Constructor.
		 * @param contact The owner of this field.
		 */
		EditAddress(PIM::Contact* contact);

		/**
		 * Destructor.
		 */
		~EditAddress();

	protected:
        /**
         * This method is called when an edit box loses focus.
         * The virtual keyboard is hidden.
         * Only for iphone platform.
         * @param editBox The edit box object that generated the event.
         */
        void editBoxEditingDidEnd(NativeUI::EditBox* editBox);

        /**
         * This method is called when the return button was pressed.
         * On iphone platform the virtual keyboard is not hidden after
         * receiving this event.
         * @param editBox The edit box object that generated the event.
         */
        void editBoxReturn(NativeUI::EditBox* editBox);

        /**
         * This method is called when the state of the check box was changed
         * by the user.
         * @param checkBox The check box object that generated the event.
         * @param state True if the check box is checked, false otherwise.
         */
        void checkBoxStateChanged(NativeUI::CheckBox *checkBox, bool state);

        /**
         * This method is called if the touch-up event was inside the bounds of the button.
         * @param button The button object that generated the event.
         */
        void buttonClicked(Widget* button);

        /**
         * Updates the type and custom label for the field.
         * @param index The index of the subfield.
         * @param type The type to set.
         * @param label The label to set.
         */
        void update(int index, int type, MAUtil::String label);

	private:
		/**
		 * Inits the data used to display this field.
		 */
		void initData();

		/**
		 * Creates the view.
		 */
		void addBody();

		/**
		 * Updates the address.
		 */
		void update();
};

#endif /* __EDITADDRESS_H__ */

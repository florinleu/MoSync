/* Copyright (C) 2012 MoSync AB

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
 * @file TypeDialog.h
 * @author Florin Leu
 * @date 15 Mar 2012
 *
 * @brief Edit type dialog.
 *
 **/

#ifndef __TYPEDIALOG_H__
#define __TYPEDIALOG_H__

#include <NativeUI/Dialog.h>
#include <NativeUI/Button.h>
#include <NativeUI/ButtonListener.h>
#include <NativeUI/CheckBox.h>
#include <NativeUI/CheckBoxListener.h>
#include <NativeUI/EditBox.h>

class EditField;

class TypeDialog :
	public NativeUI::Dialog,
	public NativeUI::ButtonListener,
	public NativeUI::CheckBoxListener
{
	public:
		/**
		 * Returns the single instance of this.
		 */
		static TypeDialog* getInstance();

		/**
		 * Destructor.
		 */
		~TypeDialog();

		/**
		 * Sets the information to be displayed.
		 * @param types	The field types.
		 * @param index The index of this subfield.
		 * @param length The number of types.
		 * @param current The current type index.
		 * @param label The field custom label.
		 */
		void setFeed(EditField* owner, const int index,
				const char** types, int length, int current, const wchar* label);

	private:
		/**
		 * Prevent constructor.
		 */
		TypeDialog();

		/**
		 * Prevent copy contructor.
		 */
		TypeDialog(const TypeDialog&);

		/**
		 * Prevent assignment operator.
		 * @param
		 * @return
		 */
		TypeDialog& operator=(const TypeDialog&);

		/**
		 * Creates the UI for this screen.
		 */
		void createUI();

		/**
		 * Clears all children.
		 */
		void clearBody();

        /**
         * This method is called if the touch-up event was inside the
         * bounds of the button.
         * @param button The button object that generated the event.
         */
        void buttonClicked(Widget* button);

        /**
         * This method is called when the state of the check box was changed
         * by the user.
         * @param checkBox The check box object that generated the event.
         * @param state True if the check box is checked, false otherwise.
         */
        void checkBoxStateChanged(NativeUI::CheckBox* checkBox, bool state);

	private:
        static TypeDialog *instance;

        EditField* mOwner;
        int mOwnerIndex;

        NativeUI::VerticalLayout* mBody;

        NativeUI::CheckBox** mCheckBoxes;
        int mCheckBoxesLength;
        int mPrevCheckBox;
        NativeUI::EditBox* mCustomLabel;

		NativeUI::Button* mOKButton;
		NativeUI::Button* mCancelButton;
};

#endif //__TYPEDIALOG_H__

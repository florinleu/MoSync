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
 * @date 09 May 2012
 *
 * @brief Edit type dialog.
 *
 **/

#ifndef __CONFIRMDIALOG_H__
#define __CONFIRMDIALOG_H__

#include <NativeUI/Dialog.h>
#include <NativeUI/Button.h>
#include <NativeUI/ButtonListener.h>
#include <NativeUI/CheckBox.h>
#include <NativeUI/CheckBoxListener.h>
#include <NativeUI/EditBox.h>

class EditDelete;

class ConfirmDialog :
	public NativeUI::Dialog,
	public NativeUI::ButtonListener
{
	public:
		/**
		 * Constructor.
		 */
		ConfirmDialog(EditDelete* owner);

		/**
		 * Destructor.
		 */
		~ConfirmDialog();

	private:
		/**
		 * Creates the UI for this screen.
		 */
		void createUI();

        /**
         * This method is called if the touch-up event was inside the
         * bounds of the button.
         * @param button The button object that generated the event.
         */
        void buttonClicked(Widget* button);

	private:
        static ConfirmDialog *instance;

        EditDelete* mOwner;

		NativeUI::Button* mOKButton;
		NativeUI::Button* mCancelButton;
};

#endif //__TYPEDIALOG_H__

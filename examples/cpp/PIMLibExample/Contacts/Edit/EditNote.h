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
 * @file EditNote.h
 * @author Florin Leu
 * @date 06 Jun 2012
 *
 * @brief Note Edit Layout.
 *
 **/

#ifndef __EDITNOTE_H__
#define __EDITNOTE_H__

#include <NativeUI/EditBox.h>
#include "EditField.h"

class EditNote :
	public EditField
{
	public:
		/**
		 * Constructor.
		 * @param contact The owner of this field.
		 */
		EditNote(PIM::Contact* contact);

		/**
		 * Destructor.
		 */
		~EditNote();

		/**
		 * Inits the data used to display this field.
		 */
		void initData();

		/**
		 * Creates the view.
		 */
		void addBody();
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

	private:
        PIM::Note* mNote;
};

#endif // __EDITNOTE_H__

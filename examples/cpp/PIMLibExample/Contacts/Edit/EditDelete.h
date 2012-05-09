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
 * @file EditDelete.h
 * @author Florin Leu
 * @date 13 Mar 2012
 *
 * @brief Delete Button Layout.
 *
 **/

#ifndef __EDITDELETE_H__
#define __EDITDELETE_H__

#include <NativeUI/VerticalLayout.h>
#include <NativeUI/Button.h>
#include <NativeUI/ButtonListener.h>
#include <Contacts/Contact.h>

class EditDelete :
	public NativeUI::VerticalLayout,
	public NativeUI::ButtonListener
{
	public:
		/**
		 * Constructor.
		 */
		EditDelete(PIM::Contact* contact);

		/**
		 * Destructor.
		 */
		virtual ~EditDelete();

	protected:
		/**
		 * Create the UI for delete button.
		 */
		void createUI();

	private:
        /**
         * This method is called if the touch-up event was inside the
         * bounds of the button.
         * @param button The button object that generated the event.
         */
        void buttonClicked(Widget* button);

	private:
		PIM::Contact* mOwner;
		NativeUI::Button* mButton;
};

#endif // __EDITDELETE_H__

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
 * @file EditPhoto.h
 * @author Florin Leu
 * @date 06 Mar 2012
 *
 * @brief Photo Edit Layout.
 *
 **/

#ifndef __EDITPHOTO_H__
#define __EDITPHOTO_H__

#include <NativeUI/HorizontalLayout.h>
#include <NativeUI/ImageButton.h>
#include <NativeUI/Button.h>
#include <NativeUI/ButtonListener.h>
#include <Contacts/Contact.h>

class EditPhoto :
	public NativeUI::HorizontalLayout,
	public NativeUI::ButtonListener,
	public MAUtil::CustomEventListener
{
	public:
		/**
		 * Constructor.
		 * @param contact The owner of this field.
		 */
		EditPhoto(PIM::Contact* contact);

		/**
		 * Destructor.
		 */
		~EditPhoto();

		void setImage(const MAHandle handle);

        /**
         * This method is called if the touch-up event was inside the
         * bounds of the button.
         * @param button The button object that generated the event.
         */
		void buttonClicked(NativeUI::Widget* button);

		/**
		 * Handle widget events.
		 * @param event A MoSync event data structure.
		 */
		void customEvent(const MAEvent& event);

	private:
		/**
		 * Create the UI for photo edit.
		 */
		void createUI();

	private:
		PIM::Contact* mOwner;
		NativeUI::ImageButton* mButton;
		NativeUI::Button* mDeleteButton;
};

#endif // __EDITPHOTO_H__

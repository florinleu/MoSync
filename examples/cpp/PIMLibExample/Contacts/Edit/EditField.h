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
 * @file EditField.h
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Field View Layout.
 *
 **/

#ifndef __EDITFIELD_H__
#define __EDITFIELD_H__

#include <NativeUI/Button.h>
#include <NativeUI/ButtonListener.h>
#include <NativeUI/EditBox.h>
#include <NativeUI/EditBoxListener.h>
#include <NativeUI/CheckBox.h>
#include <NativeUI/CheckBoxListener.h>
#include <NativeUI/VerticalLayout.h>
#include <Contacts/Contact.h>

#include <MAUtil/String.h>

class ConfirmDialog;

class EditField :
	public NativeUI::VerticalLayout,
	public NativeUI::ButtonListener,
	public NativeUI::EditBoxListener,
	public NativeUI::CheckBoxListener
{
	public:
		/**
		 * Constructor.
		 */
		EditField(PIM::Contact* contact);

		/**
		 * Destructor.
		 */
		virtual ~EditField();


		char* mLabels[];
		char* mDatas[];

		/**
		 * Updates the type and custom label for the field.
		 * @param index The index of the subfield.
		 * @param type The type to set.
		 * @param label The label to set.
		 */
		virtual void update(int index, int type, MAUtil::String label);

	protected:
		/**
		 * Inits the data used to display this field.
		 */
		virtual void initData() = 0;

		/**
		 * Create the UI for field view.
		 */
		void createUI();

		/**
		 * Creates a void* from an int.
		 * @param val  The int to use.
		 */
		void* createData(int val);

		/**
		 * Creates the view.
		 */
		virtual void addBody();

		/**
		 * Clears the view.
		 */
		virtual void clearBody();

		/**
		 * Ads subtitle for multivalue fields.
		 * @param text		The subtitle text.
		 * @param index		The index of the subfield
		 */
		void addSubTitle(const char* text, const int index);

		/**
		 * Ads type for multivalue fields.
		 * @param index		The index of the field.
		 * @param text		The type text.
		 * @param isPrimary
		 */
		void addType(int index, const char* text, const bool isPrimary);

		/**
		 * Ads the fields to the body of the view.
		 * @param labels	The labels for the fields.
		 * @param texts		The texts for the fields.
		 * @param datas		The datas for the fields.
		 * @param size		The number of the fields.
		 * @param flags		Flags that show if this is a read only subfield.
		 */
		void addSubFields(const char** labels, const char** texts, const int* datas, const int size, const int flags);

        /**
         * This method is called when an edit box loses focus.
         * The virtual keyboard is hidden.
         * Only for iphone platform.
         * @param editBox The edit box object that generated the event.
         */
        virtual void editBoxEditingDidEnd(NativeUI::EditBox* editBox);

        /**
         * This method is called when the return button was pressed.
         * On iphone platform the virtual keyboard is not hidden after
         * receiving this event.
         * @param editBox The edit box object that generated the event.
         */
        virtual void editBoxReturn(NativeUI::EditBox* editBox);

        /**
         * This method is called when the state of the check box was changed
         * by the user.
         * @param checkBox The check box object that generated the event.
         * @param state True if the check box is checked, false otherwise.
         */
        virtual void checkBoxStateChanged(NativeUI::CheckBox *checkBox, bool state);

		/**
		 * This method is called if the touch-up event was inside the bounds of the button.
		 * @param button The button object that generated the event.
		 */
		virtual void buttonClicked(Widget* button);

	private:
		/**
		 * Creates a button used to toggle the view.
		 */
		void addTitle();

		/**
		 * Creates a small spacer and ads it to the view body.
		 */
		void addSubFieldsSpacer();

	protected:
		/**
		 * The owner of this view.
		 */
		PIM::Contact* mOwner;

		/**
		 * The text for the title bar.
		 */
		char* mTitleText;

		/**
		 * Button widget for title.
		 */
		NativeUI::Button* mTitle;

		/**
		 * Vertical layout for the body.
		 */
		NativeUI::VerticalLayout* mBody;

		/**
		 * Button widget for type.
		 */
		MAUtil::Vector<NativeUI::Button*> mTypes;

		/**
		 * Delete button widget.
		 */
		NativeUI::Button** mDeleteButton;

		/**
		 * Confirm dialog.
		 */
		ConfirmDialog* mDialog;

		/**
		 * The selected subfield.
		 */
		int mCurrentSubField;

	private:
		/**
		 * The font used for title.
		 */
		MAHandle mTitleFont;

		/**
		 * The font used for labels.
		 */
		MAHandle mLabelFont;

		/**
		 * The font used for datas.
		 */
		MAHandle mDataFont;

		/**
		 * Flag to show if the body of the widget is displayed.
		 */
		bool mOpened;
};

#endif /* __EDITFIELD_H__ */

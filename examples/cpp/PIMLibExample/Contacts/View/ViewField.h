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
 * @file ViewField.h
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Field View Layout.
 *
 **/

#ifndef __VIEWFIELD_H__
#define __VIEWFIELD_H__

#include <NativeUI/Button.h>
#include <NativeUI/ButtonListener.h>
#include <NativeUI/VerticalLayout.h>
#include <Contacts/Contact.h>

class ViewField :
	public NativeUI::VerticalLayout,
	public NativeUI::ButtonListener
{
	public:
		/**
		 * Constructor.
		 */
		ViewField(PIM::Contact* contact);

		/**
		 * Destructor.
		 */
		virtual ~ViewField();


		char* mLabels[];
		char* mDatas[];


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
		 * Creates the view.
		 */
		virtual void addBody();

		/**
		 * Ads subtitle for multivalue fields.
		 * @param text
		 * @param isPrimary
		 */
		void addSubTitle(const char* text, const bool isPrimary);

		/**
		 * Ads the fields to the body of the view.
		 * @param labels	The labels for the fields.
		 * @param datas		The datas for the fields.
		 * @param size		The number of the fields.
		 */
		void addSubFields(const char** labels, const char** datas, const int size);

	private:
		/**
		 * Creates a button used to toggle the view.
		 */
		void addTitle();

		/**
		 * Creates a small spacer and ads it to the view body.
		 */
		void addSubFieldsSpacer();

		/**
		 * This method is called if the touch-up event was inside the bounds of the button.
		 * @param button The button object that generated the event.
		 */
		void buttonClicked(Widget* button);

	protected:
		/**
		 * The owner of this view.
		 */
		PIM::Contact* mOwner;

		/**
		 * The text for the title bar.
		 */
		char* mTitleText;

	private:
		/**
		 * Button widget for title.
		 */
		NativeUI::Button* mTitle;

		/**
		 * Vertical layout for the body.
		 */
		NativeUI::VerticalLayout* mBody;

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

#endif /* __VIEWFIELD_H__ */

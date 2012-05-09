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
 * @file ViewName.h
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Name View Layout.
 *
 **/

#ifndef __VIEWNAME_H__
#define __VIEWNAME_H__

#include <Contacts/Contact.h>

#include "ViewField.h"

class ViewName :
	public ViewField
{
	public:
		/**
		 * Constructor.
		 */
		ViewName(PIM::Contact* contact);

		/**
		 * Destructor.
		 */
		~ViewName();

	private:
		/**
		 * Inits the data used to display this field.
		 */
		void initData();

		/**
		 * Creates the view.
		 */
		void addBody();
};

#endif /* __VIEWNAME_H__ */

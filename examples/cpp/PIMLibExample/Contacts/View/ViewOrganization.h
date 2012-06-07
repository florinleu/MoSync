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
 * @file ViewOrganization.h
 * @author Florin Leu
 * @date 08 Mar 2012
 *
 * @brief Organization view Layout.
 *
 **/

#ifndef __VIEWORGANIZATION_H__
#define __VIEWORGANIZATION_H__

#include <Contacts/Contact.h>

#include "ViewField.h"

class ViewOrganization :
	public ViewField
{
	public:
		/**
		 * Constructor.
		 */
		ViewOrganization(PIM::Contact* contact);

		/**
		 * Destructor.
		 */
		~ViewOrganization();

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

#endif /* __VIEWORGANIZATION_H__ */

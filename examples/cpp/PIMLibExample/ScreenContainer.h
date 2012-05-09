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
 * @file ScreenContainer.h
 * @author Florin Leu
 * @date 07 Feb 2012
 *
 * @brief Screen Container.
 *
 **/

#ifndef __SCREENCONTAINER_H__
#define __SCREENCONTAINER_H__

#include <NativeUI/StackScreen.h>

class ScreenContainer : public NativeUI::StackScreen
{
	public:
		static ScreenContainer* getInstance();
		~ScreenContainer();

	private:
		static ScreenContainer *instance;
		ScreenContainer();										// Private constructor
		ScreenContainer(const ScreenContainer&);				// Prevent copy-construction
		ScreenContainer& operator=(const ScreenContainer&);		// Prevent assignment
};

#endif /* __SCREENCONTAINER_H__ */

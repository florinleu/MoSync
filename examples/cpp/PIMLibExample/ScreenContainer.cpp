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
 * @file ScreenContainer.cpp
 * @author Florin Leu
 * @date 07 Feb 2012
 *
 * @brief Screen Container.
 *
 **/

#include "ScreenContainer.h"

/*
 * Constructor
 */
ScreenContainer::ScreenContainer()
{

}

/*
 * Copy constructor.
 */
ScreenContainer::ScreenContainer(const ScreenContainer&)
{

}

/*
 * Assignment
 */
ScreenContainer& ScreenContainer::operator=(const ScreenContainer&)
{

}

/*
 * Destructor
 */
ScreenContainer::~ScreenContainer()
{
}

ScreenContainer* ScreenContainer::instance = NULL;

/*
 * Get singleton.
 */
ScreenContainer* ScreenContainer::getInstance()
{
	if (instance == NULL)
	{
		instance = new ScreenContainer();
	}
	return instance;
}

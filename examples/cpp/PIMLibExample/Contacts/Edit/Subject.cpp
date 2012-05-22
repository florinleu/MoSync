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
 * @file Subject.h
 * @author Florin Leu
 * @date 22 May 2012
 *
 * @brief Subject class implementation.
 *
 **/

#include "Subject.h"
#include "Observer.h"

void Subject::attach(Observer *obs)
{
	views.add(obs);
}

void Subject::notify()
{
	for (int i = 0; i < views.size(); i++)
	{
		views[i]->update();
	}
}

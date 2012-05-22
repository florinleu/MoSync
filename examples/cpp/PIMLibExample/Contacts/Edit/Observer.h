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
 * @file Observer.h
 * @author Florin Leu
 * @date 22 May 2012
 *
 * @brief Observer interface.
 *
 **/

#ifndef __OBSERVER_H__
#define __OBSERVER_H__

class Subject;

class Observer
{
	public:
		//Observer(Subject *mod);
		virtual void update() = 0;

//	protected:
//		Subject *getSubject();

//	private:
//		Subject *model;
};


#endif /* OBSERVER_H_ */

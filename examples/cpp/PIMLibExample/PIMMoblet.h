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
 * @file PimMoblet.h
 * @author Florin Leu
 * @date 07 Feb 2012
 *
 * @brief Application moblet class.
 *
 **/

#ifndef __PIMMOBLET_H__
#define __PIMMOBLET_H__

#include <MAUtil/Moblet.h>

class MainScreen;

/**
 * Moblet for the PIMLibExample application.
 */
class PIMMoblet : public MAUtil::Moblet
{
public:
	/**
	 * Constructor.
	 */
	PIMMoblet();

	/**
	 * Destructor.
	 */
	~PIMMoblet();

	void getScreenSize();

	/**
	 * Called when a key is pressed.
	 */
	void keyPressEvent(int keyCode, int nativeCode);

private:
	MainScreen* mScreen;			//A Native UI screen

public:
	static int sScreenWidth;
	static int sScreenHeight;
};

#endif /* __PIMMOBLET_H__ */

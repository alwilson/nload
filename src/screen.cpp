/***************************************************************************
                                 screen.cpp
                             -------------------
    begin                : Thu Nov 25 2003
    copyright            : (C) 2003 by Roland Riegel
    email                : feedback@roland-riegel.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "screen.h"

#define NOMACROS
#include <curses.h>

int Screen::width()
{
	int width;
	int height;
	getmaxyx( stdscr, height, width );
	return width;
}

int Screen::height()
{
	int width;
	int height;
	getmaxyx( stdscr, height, width );
	return height;
}

int Screen::x()
{
	int x;
	int y;
	getyx( stdscr, y, x );
	return x;
}

int Screen::y()
{
	int x;
	int y;
	getyx( stdscr, y, x );
	return y;
}

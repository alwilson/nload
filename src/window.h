/***************************************************************************
                                  window.h
                             -------------------
    begin                : Thu Jul 04 2002
    copyright            : (C) 2002 - 2003 by Roland Riegel
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

#ifndef WINDOW_H
#define WINDOW_H

#define NOMACROS
#include <curses.h>

class Form;

class Window
{
public:
	
	Window();
	virtual ~Window();
	
	//create window and display it
	virtual void show( int x, int y, int width, int height );
	
	//hide window and destroy it
	virtual void hide();
	
	//is the window currently visible?
	virtual bool visible();
	
	//refresh window
	virtual void refresh();
	
	//clear the content of the window
	virtual void clear();
	
	//move and resize window
	virtual void resize( int x, int y, int width, int height );
	
	//return current window width
	virtual int width();
	
	//return current window height
	virtual int height();
	
	//return current distance to left screen edge
	virtual int left();
	
	//return current distance to top screen edge
	virtual int top();
	
	//return current cursor position on the x-axis
	virtual int x();
	
	//return current cursor position on the y-axis
	virtual int y();
	
	//set current cursor x position
	virtual void setX( int new_x );
	
	//set current cursor y position
	virtual void setY( int new_y );
	
	//set current cursor position
	virtual void setXY( int new_x, int new_y );
	
	//print some text to the window
	virtual void print( char* text, int new_x = -1, int new_y = -1 );
	
	//print a char to the window
	virtual void print( char text, int new_x = -1, int new_y = -1 );
	
protected:
	friend class SubWindow;
	friend class Form;
	bool m_visible;
	WINDOW* m_window;
	
};

class SubWindow : public Window
{
public:
	SubWindow( Window* parent );
	~SubWindow();
	
	//return parent window
	Window* parent();
	
	//create window and display it
	virtual void show( int x, int y, int width, int height );

private:
	friend class Form;
	Window* m_parent;

};

#endif

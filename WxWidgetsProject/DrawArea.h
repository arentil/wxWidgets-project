#pragma once

#include "Square.h"
#include "Vector2D.h"
#include <wx/wx.h>
#include <list>
#include <cstdlib>

class DrawArea
{
public:
	DrawArea(wxPanel * parent, int width, int height, int size);	//szerokosc, wysokosc
	Square * getSquare(int x, int y);			//get square by row and col
	void setColor(Square * sqr, Color color);	//set color into given square
	void changePos(int x, int y);	//how far horizontally, how far vertically
	void render(wxDC & dc);
	void paintNow();

private:
	Square *** m_area;
	wxPanel * m_parent;

	int x_min, y_min, x_max, y_max;
	int m_width, m_height;
	int m_size;
};
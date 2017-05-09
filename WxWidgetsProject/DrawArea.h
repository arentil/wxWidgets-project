#pragma once

#include "Square.h"
#include "Vector2D.h"
#include "Matrix2D.h"
#include "PriorityQueue.h"
#include <wx/wx.h>
#include <list>
#include <cstdlib>
#include <random>
#include <vector>

enum class HEURISTIC : int
{

};

class DrawArea
{
public:
	DrawArea(wxPanel * parent, int width, int height, int size);	//szerokosc, wysokosc
	Square * getSquare(int x, int y);			//get square by row and col
	void setColor(Square * sqr, Color color);	//set color into given square
	void changePos(int x, int y);	//how far horizontally, how far vertically
	float getScale();
	void setPanelSize(wxSize * panelSize);

	//GENERATING OBSTACLES
	void randomize();
	void genLabyrinth();	//TODO
	//------

	//A* METHODS
	int heuristic();
	void search();			//TODO
	void clearPath();		//TODO
	void clearWalls();		
	//------

	//COMPUTING AREA/RENDERING
	void scale(float scale, int scaleVal);
	void computeAreaToDraw();
	void render(wxDC & dc);
	void paintNow();
	//------

	void deleteArea();		//delete all squares

private:
	Square *** m_area;
	wxPanel * m_parent;
	wxSize * m_panelSize;
	std::list<Square *> toDraw;
	
	Square * start;
	Square * goal;
	Color selectedColor;
	bool allowDiagonal;

	int x_min, y_min, x_max, y_max;
	int m_width, m_height;
	int m_size;
	float m_zoom;
};
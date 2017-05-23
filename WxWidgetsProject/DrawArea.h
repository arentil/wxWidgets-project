#pragma once

#include "Square.h"
#include "Vector2D.h"
#include "Matrix2D.h"
#include "PriorityQueue.h"
#include <wx/wx.h>
#include <wx/string.h>
#include <list>
#include <cstdlib>
#include <random>
#include <vector>
#include <wx/dcbuffer.h>
#include <cmath>

enum class Heuristic : short
{
	MANHATTAN = 0,
	DIAGONAL
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
	void setShowFuncValues(bool showVals);
	void setHeuristic(Heuristic h);
	void deleteArea();			//delete all squares
	void allowDiagonal(bool allow);

	//GENERATING OBSTACLES
	void randomize();
	void genLabyrinth();	//TODO
	//------

	//A* METHODS
	int getHeuristic(Square * from, Square * to);
	void search();
	void finalPath(Square * from, Square * to); //build path
	Square * getNeighbor(Square * from, int n);
	void clearPath();
	void clearWalls();
	bool unreachableCorner(Square * from, int n);		//check if corner is between two squares, if so, skip those
	bool isUnreachable(Square * from, int n1, int n2);
	//------

	//COMPUTING AREA/RENDERING
	void scale(float scale, int scaleVal);
	void computeAreaToDraw();
	void render(wxDC & dc);
	void paintNow();
	//------
private:
	Square *** m_area;
	wxPanel * m_parent;
	wxSize * m_panelSize;
	std::list<Square *> toDraw;
	bool m_showFuncValues;
	
	Square * start;
	Square * goal;
	Color selectedColor;
	Heuristic m_heuristic;
	bool m_allowDiagonal;

	int x_min, y_min, x_max, y_max;
	int m_width, m_height;
	int m_size;
	float m_zoom;
};
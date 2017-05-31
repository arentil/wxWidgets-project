#pragma once

#include "Vector2D.h"

enum class Color 
{ 
	white = 0,	//walkable
	grey,		//obstacle
	green,		//start point
	red,		//goal point
	yellow,		//final path
	lightgreen,	//open set
	cyan		//closed set
};

class Square
{
public:
	bool onOpen;
	bool onClosed;
	bool isGoal;

	Square();
	Square(float x, float y);
	Square(Vector2D pos);
	bool operator==(Square & square) const;
	bool operator!=(Square & square) const;
	void setPos(Vector2D pos);
	void setPos(float x, float y);
	void setColor(Color colour);
	Vector2D getPos();
	Color getColor();
	void setParent(Square * square);
	Square * getParent();
	void setH(int h);
	void setG(int g);
	void setF(int f);
	int getH();
	int getG();
	int getF();

	friend class CompareForAStar;
	friend class CompareForDijkstra;

private:
	Vector2D m_pos;		//x, y of top-left corner (for drawRectangle)
	Color m_color;	//colour of square

	Square * m_parent;	//previous node for A*
	int m_h, m_g, m_f;	// functions for A*
};

class CompareForAStar
{
public:
	bool operator()(Square * node1, Square * node2)
	{
		return (node1->m_f > node2->m_f);
	}
};

class CompareForDijkstra
{
public:
	bool operator()(Square * node1, Square * node2)
	{
		return (node1->m_g > node2->m_g);
	}
};
#pragma once

#include "Vector2D.h"

enum class Color { white = 0, grey, green, red, path }; //(walkable, obstacje, start point, goal point, node in path to goal)

class Square
{
public:
	Square();
	Square(float x, float y);
	Square(Vector2D pos);
	void setPos(Vector2D pos);
	void setPos(float x, float y);
	void setColor(Color colour);
	Vector2D getPos();
	Color getColor();

	friend class Compare;

private:
	Vector2D m_pos;		//x, y of top-left corner (for drawRectangle)
	Color m_color;	//colour of square

	Square * m_previous;	//previous node for A*
	float h, g, f;			// functions for A*
};

class Compare
{
public:
	bool operator()(Square * node1, Square * node2)
	{
		return (node1->f > node2->f);
	}
};
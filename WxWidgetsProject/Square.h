#pragma once

#include "Vector2D.h"

enum Colour { white = 0, blue, green, red, path }; //(walkable, obstacje, start point, goal point, node in path to goal)

class Square
{
public:
	Square();
	Square(float x1, float y1, float x2, float y2);
	Square(Vector2D pos, Vector2D size);
	void setPos(Vector2D pos);
	void setSize(Vector2D size);
	void setColour(Colour colour);
	Vector2D getPos();
	Vector2D getSize();
	Colour getColour();

private:
	Vector2D m_pos;		//x, y of top-left corner (for drawRectangle)
	Vector2D m_size;	//width and height			  (for drawRectangle)
	Colour m_colour;	//colour of square
};

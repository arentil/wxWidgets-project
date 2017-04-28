#pragma once

#include "Vector2D.h"

enum Colour { white = 0, blue, green, red, path }; //(walkable, obstacje, start point, goal point, node in path to goal)

class Square
{
public:
	Square();
	Square(float x, float y);
	Square(Vector2D pos);
	void setPos(Vector2D pos);
	void setColour(Colour colour);
	Vector2D getPos();
	Colour getColour();

private:
	Vector2D m_pos;		//x, y of top-left corner (for drawRectangle)
	Colour m_colour;	//colour of square
};

#include "Square.h"


Square::Square()
{
	m_pos.setXY(0, 0);
	m_colour = Colour::white;
}

Square::Square(float x, float y)
{
	m_pos.setXY(x, y);
	m_colour = Colour::white;
}

Square::Square(Vector2D pos)
{
	m_pos = pos;
}

void Square::setPos(Vector2D pos)
{
	m_pos = pos;
}

void Square::setColour(Colour colour)
{
	m_colour = colour;
}

Vector2D Square::getPos()
{
	return m_pos;
}

Colour Square::getColour()
{
	return m_colour;
}
#include "Square.h"


Square::Square()
{
	m_pos.setXY(0, 0);
	m_size.setXY(0, 0);
	m_colour = Colour::white;
}

Square::Square(float x1, float y1, float x2, float y2)
{
	m_pos.getXY(x1, y1);
	m_size.getXY(x2, y2);
	m_colour = Colour::white;
}

Square::Square(Vector2D pos, Vector2D size)
{
	m_pos = pos;
	m_size = size;
}

void Square::setPos(Vector2D pos)
{
	m_pos = pos;
}

void Square::setSize(Vector2D size)
{
	m_size = size;
}

void Square::setColour(Colour colour)
{
	m_colour = colour;
}

Vector2D Square::getPos()
{
	return m_pos;
}

Vector2D Square::getSize()
{
	return m_size;
}

Colour Square::getColour()
{
	return m_colour;
}
#include "Square.h"


Square::Square()
{
	m_pos.setXY(0, 0);
	m_color = Color::white;
}

Square::Square(float x, float y)
{
	m_pos.setXY(x, y);
	m_color = Color::white;
}

Square::Square(Vector2D pos)
{
	m_pos = pos;
}

void Square::setPos(Vector2D pos)
{
	m_pos = pos;
}

void Square::setPos(float x, float y)
{
	Vector2D pos(x, y);
	setPos(pos);
}

void Square::setColor(Color colour)
{
	m_color = colour;
}

Vector2D Square::getPos()
{
	return m_pos;
}

Color Square::getColor()
{
	return m_color;
}
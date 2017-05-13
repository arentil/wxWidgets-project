#include "Square.h"


Square::Square()
{
	m_pos.setXY(0, 0);
	m_color = Color::white;
	m_parent = nullptr;
	m_h = 0;
	m_g = 0;
	m_f = 0;
	onOpen = false;
	onClosed = false;
	isGoal = false;
}

Square::Square(float x, float y)
{
	m_pos.setXY(x, y);
	m_color = Color::white;
	m_parent = nullptr;
	m_h = 0;
	m_g = 0;
	m_f = 0;
	onOpen = false;
	onClosed = false;
	isGoal = false;
}

Square::Square(Vector2D pos)
{
	m_pos = pos;
	m_color = Color::white;
	m_parent = nullptr;
	m_h = 0;
	m_g = 0;
	m_f = 0;
	onOpen = false;
	onClosed = false;
	isGoal = false;
}

bool Square::operator==(Square & square) const
{
	if (m_pos == square.getPos() &&
		m_color == square.getColor() &&
		m_h == square.getH() &&
		m_g == square.getG() &&
		m_f == square.getF())
	{
		return true;
	}
	return false;
}

bool Square::operator!=(Square & square) const
{
	return !((*this) == square);
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

void Square::setParent(Square * square)
{
	m_parent = square;
}

Square * Square::getParent()
{
	return m_parent;
}

void Square::setH(int h)
{
	m_h = h;
}
void Square::setG(int g)
{
	m_g = g;
}

void Square::setF(int f)
{
	m_f = f;
}

int Square::getH()
{
	return m_h;
}

int Square::getG()
{
	return m_g;
}

int Square::getF()
{
	return m_f;
}
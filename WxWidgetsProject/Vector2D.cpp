#include "Vector2D.h"

Vector2D::Vector2D()
{
	m_vector[0] = 0;
	m_vector[1] = 0;
	m_vector[2] = 1;
}

Vector2D::Vector2D(float x, float y)
{
	m_vector[0] = x;
	m_vector[1] = y;
	m_vector[2] = 1;
}

Vector2D::Vector2D(const Vector2D & vector)
{
	operator=(vector);
}

Vector2D & Vector2D::operator=(const Vector2D & vector)
{
	m_vector[0] = vector.getX();
	m_vector[1] = vector.getY();
	m_vector[2] = 1;
	
	return *this;
}

void Vector2D::setX(float x)
{
	m_vector[0] = x;
}

void Vector2D::setY(float y)
{
	m_vector[1] = y;
}

void Vector2D::setXY(float x, float y)
{
	m_vector[0] = x;
	m_vector[1] = y;
}

void Vector2D::getXY(float & x, float & y) const
{
	x = m_vector[0];
	y = m_vector[1];
}

float Vector2D::getX() const
{
	return m_vector[0];
}

float Vector2D::getY() const
{
	return m_vector[1];
}
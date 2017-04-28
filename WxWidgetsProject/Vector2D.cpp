#include "Vector2D.h"

Vector2D::Vector2D()
{
	m_vec[0] = 0;
	m_vec[1] = 0;
	m_vec[2] = 1;
}

Vector2D::Vector2D(float x, float y)
{
	m_vec[0] = x;
	m_vec[1] = y;
	m_vec[2] = 1;
}

Vector2D::Vector2D(const Vector2D & vec)
{
	operator=(vec);
}

Vector2D & Vector2D::operator=(const Vector2D & vec)
{
	m_vec[0] = vec[0];
	m_vec[1] = vec[1];
	m_vec[2] = vec[2];
	
	return *this;
}

float Vector2D::operator[](const int i) const
{
	if (i >= 3 || i < 0)
		throw std::out_of_range("Vector2D out of range parameter.");

	return m_vec[i];
}

void Vector2D::setXY(const float x, const float y)
{
	m_vec[0] = x;
	m_vec[1] = y;
}

void Vector2D::set(const int i, const float val)
{
	m_vec[i] = val;
}
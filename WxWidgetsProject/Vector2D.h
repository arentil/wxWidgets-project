#pragma once

class Vector2D
{
public:
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(const Vector2D & vector);
	Vector2D & operator=(const Vector2D & vector);
	void setXY(float x, float y);
	void setX(float x);
	void setY(float y);
	void getXY(float & x, float & y) const;
	float getX() const;
	float getY() const;

private:
	float m_vector[3];
};
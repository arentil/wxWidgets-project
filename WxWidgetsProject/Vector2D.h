#pragma once

#include <stdexcept>

class Vector2D
{
public:
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(const Vector2D & vec);
	Vector2D & operator=(const Vector2D & vec);
	float operator[](const int i) const;
	bool operator==(const Vector2D & vec) const;
	void setXY(const float x, const float y);
	void set(const int i, const float val);

private:
	float m_vec[3];
};
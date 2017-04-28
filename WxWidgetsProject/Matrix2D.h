#pragma once

#include "Vector2D.h"


class Matrix2D
{
public:
	Matrix2D();
	Matrix2D(float mat[3][3]);
	Vector2D operator*(const Vector2D & vec);
	

private:
	float m_mat[3][3];
};

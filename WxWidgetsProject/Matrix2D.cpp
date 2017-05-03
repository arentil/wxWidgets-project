#include "Matrix2D.h"

Matrix2D::Matrix2D()
{
	m_mat[0][0] = 0; m_mat[0][1] = 0; m_mat[0][2] = 0;
	m_mat[1][0] = 0; m_mat[1][1] = 0; m_mat[1][2] = 0;
	m_mat[2][0] = 0; m_mat[2][1] = 0; m_mat[2][2] = 0;
}


Matrix2D::Matrix2D(float mat[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_mat[i][j] = mat[i][j];
		}
	}
}

Vector2D Matrix2D::operator*(const Vector2D & vec)
{
	Vector2D ret;
	for (int i = 0; i < 3; i++)
	{
		float sum = 0;
		for (int j = 0; j < 3; j++)
		{
			sum += (m_mat[i][j] * vec[j]);
		}
		ret.set(i, sum);
	}
	return ret;
}